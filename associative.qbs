import qbs



CppApplication {
    Depends { name: "Qt"; submodules: ["core"] }
    Depends { name:"cpp" }

    cpp.cxxFlags: [ "-std=c++14" ]
    name : "test"

    Group {
        files: ["range.h", "main.cpp"]
    }

    Properties {
        condition:true
        Depends { name:"cpp" }
        cpp.includePaths: ["range-v3/include"]
    }
}
