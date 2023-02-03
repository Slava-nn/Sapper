import qbs

Application {
    name: "Sapper"
    files: ["*.cpp", "*.h"]
    Depends { name : "cpp" }
    qbs.install: true
    qbs.installDir: "sapper"
    qbs.installPrefix: ""
}