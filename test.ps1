param([string]$GameData='')
$ErrorActionPreference='Stop'
Push-Location $PSScriptRoot
try {
 $m=Get-Content package/MCM/LukesActorBrowser.json -Raw | ConvertFrom-Json
 if($m.modName -ne 'LukesActorBrowser' -or $m.submenus.'0'.options.'1'.vars[0].default -ne 10){throw 'MCM identity or hotkey mismatch'}
 $tick=Get-Content package/NVSE/user_defined_functions/LukesActorBrowser/Tick.gek -Raw
 if(([regex]::Matches($tick,'rTarget.SetActorValue ')).Count -ne 30){throw 'Actor value allowlist mismatch'}
 if($tick -match 'RunScriptLine|ConsoleCommand|ForceActorValue|AddItem'){throw 'Unexpected command dispatch'}
 foreach($key in @('iType == 42 || iType == 43','iCount <= 5','Request:Session','Snapshot:Valid','IsFormValid rTarget')){if(!$tick.Contains($key)){throw "Missing validation: $key"}}
 if($GameData){& ./build/ActorCheck.exe $GameData}else{& ./build/ActorCheck.exe}
 if($LASTEXITCODE -ne 0){throw "ActorCheck failed: $LASTEXITCODE"}
 & ./build/RenderMock.exe
 if($LASTEXITCODE -ne 0){throw "RenderMock failed: $LASTEXITCODE"}
 Write-Output 'PASS: native actor controls, MCM metadata, script allowlist and rendering mocks. In-game script/GPU validation remains manual.'
} finally {Pop-Location}

& (Join-Path $PSScriptRoot 'build/ChainCheck.exe')
if ($LASTEXITCODE -ne 0) { throw "ChainCheck failed: $LASTEXITCODE" }

$bridge = Join-Path $PSScriptRoot 'package/NVSE/user_defined_functions/LukesActorBrowser'
$source = Get-Content (Join-Path $bridge 'Tick.gek') -Raw
if ($source -match 'SmallGuns|if abs ' -or $source -notmatch 'SetActorValue Guns fValue') { throw 'Invalid Fallout New Vegas actor-value syntax' }
$init = Get-Content (Join-Path $bridge 'Initialise.gek') -Raw
if ($init -match 'AuxVarSetRef[^\r\n]+ 0' -or $init -notmatch 'AuxVarErase') { throw 'Invalid auxiliary-reference clearing' }

# Catch the runtime quote regression reported at Tick.gek line 342.
foreach($file in Get-ChildItem (Join-Path $PSScriptRoot 'package/NVSE') -Recurse -File | Where-Object Extension -in @('.gek','.txt')){
 $lineNumber=0
 foreach($line in Get-Content $file.FullName){
  $lineNumber++
  $prefix=($line -split ';',2)[0]
  if(([regex]::Matches($prefix,'"')).Count % 2){throw "Unmatched runtime compiler quotes: $($file.Name):$lineNumber"}
 }
}

$m=Get-Content (Join-Path $PSScriptRoot 'package/MCM/LukesActorBrowser.json') -Raw | ConvertFrom-Json
if($m.submenus.'0'.options.'5'.vars[0].configINI -ne 'Browser:ShowTemplates' -or $m.submenus.'0'.options.'5'.vars[0].default -ne 0){throw 'Template MCM binding mismatch'}
foreach($file in @('BarlowCondensed-Bold.ttf','BarlowCondensed-OFL.txt','ShareTechMono-Regular.ttf','ShareTechMono-OFL.txt')){
 if(!(Test-Path (Join-Path $PSScriptRoot "package/NVSE/Plugins/LukesActorBrowser/Fonts/$file"))){throw "Missing bundled font/license $file"}
}

Push-Location $PSScriptRoot
try {
 & ./build/ControllerCheck.exe
 if($LASTEXITCODE -ne 0){throw "ControllerCheck failed: $LASTEXITCODE"}
} finally {Pop-Location}
