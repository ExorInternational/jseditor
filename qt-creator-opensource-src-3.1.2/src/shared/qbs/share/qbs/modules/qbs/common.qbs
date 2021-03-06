import qbs 1.0
import qbs.FileInfo

Module {
    property string buildVariant: "debug"
    property bool enableDebugCode: buildVariant == "debug"
    property bool debugInformation: (buildVariant == "debug")
    property string optimization: (buildVariant == "debug" ? "none" : "fast")
    property stringList hostOS: getHostOS()
    property string hostOSVersion: {
        if (hostOS.contains("osx")) {
            return getNativeSetting("/System/Library/CoreServices/ServerVersion.plist", "ProductVersion") ||
                   getNativeSetting("/System/Library/CoreServices/SystemVersion.plist", "ProductVersion");
        } else if (hostOS.contains("windows")) {
            var version = getNativeSetting("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows NT\\CurrentVersion", "CurrentVersion");
            return version + "." + hostOSBuildVersion;
        }
    }

    property string hostOSBuildVersion: {
        if (hostOS.contains("osx")) {
            return getNativeSetting("/System/Library/CoreServices/ServerVersion.plist", "ProductBuildVersion") ||
                   getNativeSetting("/System/Library/CoreServices/SystemVersion.plist", "ProductBuildVersion");
        } else if (hostOS.contains("windows")) {
            return getNativeSetting("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuildNumber");
        }
    }

    readonly property var hostOSVersionParts: hostOSVersion ? hostOSVersion.split('.').map(function(item) { return parseInt(item, 10); }) : []
    readonly property int hostOSVersionMajor: hostOSVersionParts[0] || 0
    readonly property int hostOSVersionMinor: hostOSVersionParts[1] || 0
    readonly property int hostOSVersionPatch: hostOSVersionParts[2] || 0

    property stringList targetOS: hostOS
    property string pathListSeparator: hostOS.contains("windows") ? ";" : ":"
    property string pathSeparator: hostOS.contains("windows") ? "\\" : "/"
    property string profile
    property stringList toolchain
    property string architecture

    property string endianness
    PropertyOptions {
        name: "endianness"
        allowedValues: ["big", "little", "mixed"]
        description: "endianness of the target platform"
    }

    property bool install: false
    property string installDir
    property string installPrefix: ""
    property path sysroot

    PropertyOptions {
        name: "buildVariant"
        allowedValues: ['debug', 'release']
        description: "name of the build variant"
    }

    PropertyOptions {
        name: "optimization"
        allowedValues: ['none', 'fast', 'small']
        description: "optimization level"
    }

    validate: {
        if (!architecture) {
            throw new Error("qbs.architecture is not set. "
                  + "You might want to re-run 'qbs setup-toolchains'.");
        }

        var canonicalArch = canonicalArchitecture(architecture);
        if (architecture !== canonicalArch) {
            throw "qbs.architecture '" + architecture + "' is invalid. " +
                  "You must use the canonical name '" + canonicalArch + "'";
        }

        if (hostOS.contains("windows") || hostOS.contains("osx")) {
            if (!hostOSVersion) {
                throw "Could not detect host operating system version; " +
                        "verify that system files or registry have not been " +
                        "tampered with.";
            }

            if (!/^[0-9]+(\.[0-9]+){1,3}$/.test(hostOSVersion)) {
                throw "qbs.hostOSVersion is in an invalid format; it must be of the form x.y or " +
                        "x.y.z or x.y.z.w where x, y, z and w are positive integers.";
            }

            if (!hostOSBuildVersion) {
                throw "Could not detect host operating system build version; " +
                        "verify that system files or registry have not been " +
                        "tampered with.";
            }
        }
    }
}
