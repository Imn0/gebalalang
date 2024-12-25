// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterGbl",
    products: [
        .library(name: "TreeSitterGbl", targets: ["TreeSitterGbl"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterGbl",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                // NOTE: if your language has an external scanner, add it here.
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterGblTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterGbl",
            ],
            path: "bindings/swift/TreeSitterGblTests"
        )
    ],
    cLanguageStandard: .c11
)
