import qbs 1.0
import qbs.File
import qbs.FileInfo
import qbs.ModUtils

Module {
    condition: qbs.hostOS.contains("windows") && qbs.targetOS.contains("windows")

    property path toolchainInstallPath: qbs.getNativeSetting(registryKey, "InstallFolder")
    property path toolchainInstallRoot: qbs.getNativeSetting(registryKey, "InstallRoot")
    property string version: qbs.getNativeSetting(registryKey, "ProductVersion")
    property var versionParts: version ? version.split('.').map(function(item) { return parseInt(item, 10); }) : []
    property int versionMajor: versionParts[0]
    property int versionMinor: versionParts[1]
    property int versionPatch: versionParts[2]
    property int versionBuild: versionParts[3]

    property string compilerName: "candle.exe"
    property string compilerPath: compilerName
    property string linkerName: "light.exe"
    property string linkerPath: linkerName

    property string warningLevel: "normal"
    PropertyOptions {
        name: "warningLevel"
        allowedValues: ["none", "normal", "pedantic"]
    }

    property bool debugInformation: qbs.debugInformation
    property bool treatWarningsAsErrors: false
    property bool verboseOutput: false
    PropertyOptions {
        name: "verboseOutput"
        description: "display verbose output from the compiler and linker"
    }

    property bool visualStudioCompatibility: true
    PropertyOptions {
        name: "visualStudioCompatibility"
        description: "whether to define most of the same variables as " +
                     "Visual Studio when using the Candle compiler"
    }

    property bool enableQbsDefines: true
    PropertyOptions {
        name: "enableQbsDefines"
        description: "built-in variables that are defined when using the Candle compiler"
    }

    property pathList includePaths
    PropertyOptions {
        name: "includePaths"
        description: "directories to add to the include search path"
    }

    property stringList defines
    PropertyOptions {
        name: "defines"
        description: "variables that are defined when using the Candle compiler"
    }

    property stringList compilerFlags
    PropertyOptions {
        name: "compilerFlags"
        description: "additional flags for the Candle compiler"
    }

    property stringList linkerFlags
    PropertyOptions {
        name: "linkerFlags"
        description: "additional flags for the Light linker"
    }

    property stringList cultures
    PropertyOptions {
        name: "cultures"
        description: "the list of localizations to build the MSI for; leave undefined to build all localizations"
    }

    property stringList extensions: type.contains("wixsetup") ? ["WixBalExtension"] : [] // default to WiX Standard Bootstrapper extension

    // private properties
    property string targetSuffix: {
        if (type.contains("msi")) {
            return windowsInstallerSuffix;
        } else if (type.contains("wixsetup")) {
            return executableSuffix;
        }
    }

    property string executableSuffix: ".exe"
    property string windowsInstallerSuffix: ".msi"

    property string registryKey: {
        var knownVersions = [ "4.0", "3.9", "3.8", "3.7", "3.6", "3.5", "3.0", "2.0" ];
        var keyNative = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Installer XML\\";
        var keyWoW64 = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows Installer XML\\";

        for (i in knownVersions) {
            if (qbs.getNativeSetting(keyNative + knownVersions[i], "ProductVersion"))
                return keyNative + knownVersions[i];
            if (qbs.getNativeSetting(keyWoW64 + knownVersions[i], "ProductVersion"))
                return keyWoW64 + knownVersions[i];
        }
    }

    validate: {
        if (!toolchainInstallPath)
            throw "wix.toolchainInstallPath is not defined. Set wix.toolchainInstallPath in your profile.";

        if (!toolchainInstallRoot)
            throw "wix.toolchainInstallRoot is not defined. Set wix.toolchainInstallRoot in your profile."

        if (!version)
            throw "wix.version is not defined. Set wix.version in your profile.";

        if (!/^[0-9]+(\.[0-9]+){1,3}$/.test(version)) {
            throw "wix.version is in an invalid format; it must be of the form x.y.z.w " +
                    "where x, y, z and w are positive integers.";
        }
    }

    setupBuildEnvironment: {
        var v = new ModUtils.EnvironmentVariable("PATH", ";", true);
        v.prepend(toolchainInstallPath);
        v.prepend(toolchainInstallRoot);
        v.set();
    }

    // WiX Include Files
    FileTagger {
        patterns: ["*.wxi"]
        fileTags: ["wxi"]
    }

    // WiX Localization Files
    FileTagger {
        patterns: ["*.wxl"]
        fileTags: ["wxl"]
    }

    // WiX Source Files
    FileTagger {
        patterns: ["*.wxs"]
        fileTags: ["wxs"]
    }

    Rule {
        id: candleCompiler
        inputs: ["wxs"]

        Artifact {
            fileTags: ["wixobj"]
            fileName: ".obj/" + product.name + "/" + input.baseDir.replace(':', '') + "/" + FileInfo.baseName(input.fileName) + ".wixobj"
        }

        prepare: {
            var i;
            var args = ["-nologo"];

            if (ModUtils.moduleProperty(product, "warningLevel") === "none") {
                args.push("-sw");
            } else {
                if (ModUtils.moduleProperty(product, "warningLevel") === "pedantic") {
                    args.push("-pedantic");
                }

                if (ModUtils.moduleProperty(product, "treatWarningsAsErrors")) {
                    args.push("-wx");
                }
            }

            if (ModUtils.moduleProperty(product, "verboseOutput")) {
                args.push("-v");
            }

            var arch = product.moduleProperty("qbs", "architecture");
            if (!["x86", "x86_64", "ia64", "arm"].contains(arch)) {
                // http://wixtoolset.org/documentation/manual/v3/xsd/wix/package.html
                throw("WiX: unsupported architecture '" + arch + "'");
            }

            // QBS uses "x86_64", Microsoft uses "x64"
            if (arch === "x86_64") {
                arch = "x64";
            }

            // Visual Studio defines these variables along with various solution and project names and paths;
            // we'll pass most of them to ease compatibility between QBS and WiX projects originally created
            // using Visual Studio. The only definitions we don't pass are the ones which make no sense at all
            // in QBS, like the solution and project directories since they do not exist.
            if (ModUtils.moduleProperty(product, "visualStudioCompatibility")) {
                var toolchain = product.moduleProperty("cpp", "toolchain");
                if (toolchain && toolchain.contains("msvc")) {
                    var vcDir = product.moduleProperty("cpp", "toolchainInstallPath").replace(/[\\/]bin$/i, "");
                    var vcRootDir = vcDir.replace(/[\\/]VC$/i, "");
                    args.push("-dDevEnvDir=" + FileInfo.toWindowsSeparators(FileInfo.joinPaths(vcRootDir, 'Common7/IDE')));
                }

                var buildVariant = ModUtils.moduleProperty(product, "buildVariant");
                if (buildVariant === "debug") {
                    args.push("-dDebug");
                    args.push("-dConfiguration=Debug");
                } else if (buildVariant === "release") {
                    // VS doesn't define "Release"
                    args.push("-dConfiguration=Release");
                }

                var productTargetExt = ModUtils.moduleProperty(product, "targetSuffix");
                if (!productTargetExt) {
                    throw("WiX: Unsupported product type '" + product.type + "'");
                }

                var builtBinaryFilePath = FileInfo.joinPaths(product.buildDirectory, product.destinationDirectory, product.targetName + productTargetExt);
                args.push("-dOutDir=" + FileInfo.toWindowsSeparators(FileInfo.path(builtBinaryFilePath))); // in VS, relative to the project file by default

                args.push("-dPlatform=" + arch);

                args.push("-dProjectName=" + project.name);

                args.push("-dTargetDir=" + FileInfo.toWindowsSeparators(FileInfo.path(builtBinaryFilePath))); // in VS, an absolute path
                args.push("-dTargetExt=" + productTargetExt);
                args.push("-dTargetFileName=" + product.targetName + productTargetExt);
                args.push("-dTargetName=" + product.targetName);
                args.push("-dTargetPath=" + FileInfo.toWindowsSeparators(builtBinaryFilePath));
            }

            var includePaths = ModUtils.moduleProperty(product, "includePaths");
            for (i in includePaths) {
                args.push("-I" + includePaths[i]);
            }

            var enableQbsDefines = ModUtils.moduleProperty(product, "enableQbsDefines")
            if (enableQbsDefines) {
                var map = {
                    "project.": project,
                    "product.": product
                };

                for (var prefix in map) {
                    var obj = map[prefix];
                    for (var prop in obj) {
                        var val = obj[prop];
                        if (typeof val !== 'function' && typeof val !== 'object' && !prop.startsWith("_")) {
                            args.push("-d" + prefix + prop + "=" + val);
                        }
                    }
                }

                // Helper define for alternating between 32-bit and 64-bit logic
                if (arch === "x64" || arch === "ia64") {
                    args.push("-dWin64");
                }
            }

            // User-supplied defines
            var defines = ModUtils.moduleProperty(product, "defines");
            for (i in defines) {
                args.push("-d" + defines[i]);
            }

            // User-supplied flags
            var flags = ModUtils.moduleProperty(product, "compilerFlags");
            for (i in flags) {
                args.push(flags[i]);
            }

            args.push("-out");
            args.push(FileInfo.toWindowsSeparators(output.filePath));
            args.push("-arch");
            args.push(arch);

            var extensions = ModUtils.moduleProperty(product, "extensions");
            for (i in extensions) {
                args.push("-ext");
                args.push(extensions[i]);
            }

            args.push(FileInfo.toWindowsSeparators(inputs.wxs[0].filePath));

            var cmd = new Command(ModUtils.moduleProperty(product, "compilerPath"), args);
            cmd.description = "compiling " + FileInfo.fileName(inputs.wxs[0].filePath);
            cmd.highlight = "compiler";
            cmd.workingDirectory = FileInfo.path(output.filePath);
            return cmd;
        }
    }

    Rule {
        id: lightLinker
        multiplex: true
        inputs: ["wixobj", "wxl"]

        Artifact {
            condition: product.type.contains("wixsetup")
            fileTags: ["wixsetup", "application"]
            fileName: product.destinationDirectory + "/" + product.targetName + ModUtils.moduleProperty(product, "executableSuffix")
        }

        Artifact {
            condition: product.type.contains("msi")
            fileTags: ["msi"]
            fileName: product.destinationDirectory + "/" + product.targetName + ModUtils.moduleProperty(product, "windowsInstallerSuffix")
        }

        Artifact {
            condition: product.moduleProperty("qbs", "debugInformation") // ### QBS-412
            fileTags: ["wixpdb"]
            fileName: product.destinationDirectory + "/" + product.targetName + ".wixpdb"
        }

        prepare: {
            var i;
            var primaryOutput;
            if (product.type.contains("wixsetup")) {
                primaryOutput = outputs.wixsetup[0];
            } else if (product.type.contains("msi")) {
                primaryOutput = outputs.msi[0];
            } else {
                throw("WiX: Unsupported product type '" + product.type + "'");
            }

            var args = ["-nologo"];

            if (ModUtils.moduleProperty(product, "warningLevel") === "none") {
                args.push("-sw");
            } else {
                if (ModUtils.moduleProperty(product, "warningLevel") === "pedantic") {
                    args.push("-pedantic");
                }

                if (ModUtils.moduleProperty(product, "treatWarningsAsErrors")) {
                    args.push("-wx");
                }
            }

            if (ModUtils.moduleProperty(product, "verboseOutput")) {
                args.push("-v");
            }

            args.push("-out");
            args.push(FileInfo.toWindowsSeparators(primaryOutput.filePath));

            if (ModUtils.moduleProperty(product, "debugInformation")) {
                args.push("-pdbout");
                args.push(FileInfo.toWindowsSeparators(outputs.wixpdb[0].filePath));
            } else {
                args.push("-spdb");
            }

            var extensions = ModUtils.moduleProperty(product, "extensions");
            for (i in extensions) {
                args.push("-ext");
                args.push(extensions[i]);
            }

            for (i in inputs.wxl) {
                args.push("-loc");
                args.push(outputs.wxl[i].filePath);
            }

            if (product.type.contains("msi")) {
                var cultures = ModUtils.moduleProperty(product, "cultures");
                args.push("-cultures:"
                    + (cultures && cultures.length > 0 ? cultures.join(";") : "null"));
            }

            // User-supplied flags
            var flags = ModUtils.moduleProperty(product, "linkerFlags");
            for (i in flags) {
                args.push(flags[i]);
            }

            for (i in inputs.wixobj) {
                args.push(inputs.wixobj[i].filePath);
            }

            var cmd = new Command(ModUtils.moduleProperty(product, "linkerPath"), args);
            cmd.description = "linking " + FileInfo.fileName(primaryOutput.filePath);
            cmd.highlight = "linker";
            cmd.workingDirectory = FileInfo.path(primaryOutput.filePath);
            return cmd;
        }
    }
}
