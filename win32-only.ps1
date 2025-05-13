# check if rustc is installed
if (Get-Command rustc -ErrorAction SilentlyContinue) {
    Write-Host "Rust is already installed."
} else {
    Write-Host "Rust is not installed. Installing Rust..."
    # Download and install rustup
    $rustupUrl = "https://win.rustup.rs"
    $rustupInstaller = "$env:TEMP\rustup-init.exe"
    Invoke-WebRequest -Uri $rustupUrl -OutFile $rustupInstaller
    Start-Process -FilePath $rustupInstaller -ArgumentList "-y" -Wait
    Remove-Item $rustupInstaller
}

# check if msvc and cl are installed
if (Get-Command cl -ErrorAction SilentlyContinue) {
    Write-Host "MSVC is already installed."
} else {
    Write-Host "MSVC is not installed. Installing MSVC..."
    # Download and install Visual Studio Build Tools
    $vsBuildToolsUrl = "https://aka.ms/vs/17/release/vs_buildtools.exe"
    $vsBuildToolsInstaller = "$env:TEMP\vs_buildtools.exe"
    Invoke-WebRequest -Uri $vsBuildToolsUrl -OutFile $vsBuildToolsInstaller
    Start-Process -FilePath $vsBuildToolsInstaller -ArgumentList "--quiet --wait --norestart --nocache --installPath C:\BuildTools" -Wait
    Remove-Item $vsBuildToolsInstaller
}

# check if cmake is installed
if (Get-Command cmake -ErrorAction SilentlyContinue) {
    Write-Host "CMake is already installed."
} else {
    Write-Host "CMake is not installed. Installing CMake..."
    # Download and install CMake
    $cmakeUrl = "https://cmake.org/files/v3.24/cmake-3.24.2-windows-x86_64.msi"
    $cmakeInstaller = "$env:TEMP\cmake.msi"
    Invoke-WebRequest -Uri $cmakeUrl -OutFile $cmakeInstaller
    Start-Process -FilePath msiexec.exe -ArgumentList "/i $cmakeInstaller /quiet /norestart" -Wait
    Remove-Item $cmakeInstaller
}

# check if we are on Windows on ARM (can't run on win-arm)
if ($env:PROCESSOR_ARCHITECTURE -eq "ARM") {
    Write-Host "Running on Windows on ARM. Exiting..."
    exit
}

# check if we are on Windows 10 or later
if ([System.Environment]::OSVersion.Version.Major -lt 10) {
    Write-Host "This script requires Windows 10 or later. Exiting..."
    exit
}
# check if we are on 64-bit Windows
if ([System.Environment]::Is64BitOperatingSystem -eq $false) {
    Write-Host "This script requires 64-bit Windows. Exiting..."
    exit
}

rustc --version
cl --version
cmake --version

Function Get-VisualStudioPath {
    $vswherePath = "$env:ProgramFiles(x86)\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswherePath) {
        & $vswherePath -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
    } else {
        Write-Host "Visual Studio Installer not found."
        return $null
    }
}
$vsPath = Get-VisualStudioPath
if ($vsPath) {
    Write-Host "Visual Studio path: $vsPath"
} else {
    Write-Host "Visual Studio not found."
}

Function build {
    $buildDir = "build"
    $installDir "C:\LemonC"

    rustc ./src/lemoncc.rs -o $buildDir/lemoncc.exe
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Rust build failed."
        exit 1
    }
    Write-Host "Rust build succeeded."

    copy-item -Path $buildDir/lemoncc.exe -Destination $installDir
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Copying lemoncc.exe failed."
        exit 1
    }
    Write-Host "Copying lemoncc.exe succeeded."
    copy-item -Path .\include\Lemon.h -Destination $installDir\include
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Copying Lemon.h failed."
        exit 1
    }
    Write-Host "Copying Lemon.h succeeded."
}

Function install {
    $installDir = "C:\LemonC"
    if (Test-Path $installDir) {
        Write-Host "LemonC is already installed."
    } else {
        New-Item -ItemType Directory -Path $installDir
        Write-Host "LemonC installed at $installDir."
    }
}

build
install
Write-Host "Build and installation completed."