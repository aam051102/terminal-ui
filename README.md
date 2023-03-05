# Terminal UI
Generates unicode for a terminal user interface based on HTML-like input.
Just a fun exercise. Not intended as a complete project for real use.

## Setup
Clone repository.
Install Conan on the device.
Navigate via terminal to the cloned repository and execute `conan install . --build missing -s compiler.runtime=MTd` (downloads debug modules).
Then download Premake5, copy premake5.exe to the root directory and execute `premake5 vs2022`.
