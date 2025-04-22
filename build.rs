use std::env;
use std::path::PathBuf;
use std::path::Path;

fn main() {
    
    // Tell cargo to tell rustc to link the system bzip2
    // shared library.
    println!("cargo:rustc-link-lib=bz2");
    
    // Tell cargo to tell rustc to link our own wrapper library
    // Tell cargo to look for shared libraries in the specified directory
    println!("cargo:rustc-link-search=.");
    println!("cargo:rustc-link-lib=ramulatorwrapper");
    println!("cargo:rustc-link-arg=-Wl,-rpath,/usr/scratch/anazareth8/ramulator-example");
    
    println!("cargo:rustc-link-search=/usr/scratch/anazareth8/ramulator2");
    println!("cargo:rustc-link-lib=ramulator");
    println!("cargo:rustc-link-arg=-Wl,-rpath,/usr/scratch/anazareth8/ramulator2");

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let header_dir = "/usr/scratch/anazareth8/ramulator2/src";
    let header_dir = Path::new(header_dir);
    
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header("call_ramulator.h")
        // Allow bindgen to find headers in the specified directory
        .clang_arg(format!("-I{}", header_dir.to_str().unwrap()))
        .clang_arg(format!("-I{}", "/usr/scratch/anazareth8/ramulator2/build/yaml-cpp/include" ))
        .clang_arg(format!("-I{}", "/usr/scratch/anazareth8/spdlog/include" ))
        // Specify C++20
        // .clang_arg("-std=c++20")
        // TEMPORARY HACK
        // .clang_arg("-isystem/opt/rh/gcc-toolset-13/root/usr/lib/gcc/x86_64-redhat-linux/13/include")
        // Block standard library types, if not needed
        .blocklist_type("std::.*")  
        // Block va_list if problematic
        .blocklist_type("va_list") 
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        // Generate bindings to virtual functions
        .vtable_generation(true)
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");

}