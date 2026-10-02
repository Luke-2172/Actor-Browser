param([string]$GameData='')
$ErrorActionPreference = 'Stop'
& (Join-Path $PSScriptRoot 'test.ps1') -GameData $GameData
$package = Join-Path $PSScriptRoot 'package'
foreach ($file in @('NVSE/Plugins/LukesActorBrowser.dll','NVSE/Plugins/LukesActorBrowser/zlib1.dll')) {
    if (!(Test-Path -LiteralPath (Join-Path $package $file))) { throw 'Run build.cmd before packaging' }
}
$out = Join-Path $PSScriptRoot 'dist'
New-Item -ItemType Directory -Force $out | Out-Null
Add-Type -AssemblyName System.IO.Compression
$path = Join-Path $out 'Lukes-Actor-Browser-FNV-1.0.12.zip'
$stream = [IO.File]::Open($path,[IO.FileMode]::Create)
$zip = [IO.Compression.ZipArchive]::new($stream,[IO.Compression.ZipArchiveMode]::Create)
try {
    foreach ($file in Get-ChildItem $package -Recurse -File) {
        if ($file.Extension -notin @('.dll','.ini','.txt','.gek','.json','.ttf')) { continue }
        $relative = $file.FullName.Substring($package.Length+1).Replace('\','/')
        [IO.Compression.ZipFileExtensions]::CreateEntryFromFile($zip,$file.FullName,$relative,[IO.Compression.CompressionLevel]::Optimal) | Out-Null
    }
} finally { $zip.Dispose(); $stream.Dispose() }
Write-Output $path




