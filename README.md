# Luke's Actor Browser 1.0.12

ESP-free Fallout: New Vegas actor spawner and actor-value editor. F10 by default.
Uses a native x86 C++ D3D9/DirectInput overlay and JIP-compiled GECK functions.
The runtime does not execute PowerShell. PowerShell scripts only test and package.

See package/README.txt for requirements, controls, limits and installation.

## Build
Install Visual Studio C++ x86 build tools and a Windows SDK. Run build.cmd,
then powershell -ExecutionPolicy Bypass -File test.ps1 and package.ps1.
The included third_party/libz.a is the x86 zlib build dependency; its license
is included. No Bethesda assets or MCM framework binaries are redistributed.
No project-wide source license has been selected.

## Design
src/catalog.h reads only NPC_ and CREA records with bounded record/decode sizes.
src/actorvalues.h defines the UI's 30 actor values and allowed ranges.
package/NVSE/user_defined_functions/LukesActorBrowser/Tick.gek contains matching
fixed command branches; edit both when adding a value. Requests use a separate
runtime INI, session validation and Pending-last publication. The script resolves
forms using their originating plugin, validates targets and reads results back.

## Validation
ActorCheck checks F10, filters, finite values, request bounds, snapshot gating,
scrolling and all page rendering. RenderMock checks D3D targets and partial uploads.
The build and these tests do not compile GECK scripts or execute the game. In-game
verification is still required, including co-installation with Item Browser.
FNV Display Tweaks compatibility remains unresolved.

## References
https://geckwiki.com/index.php/ActorValue
https://geckwiki.com/index.php/SetActorValue
https://geckwiki.com/index.php/PlaceAtMe
https://geckwiki.com/index.php/AuxiliaryVariableSetRef
https://geckwiki.com/index.php/Form_Type_IDs

## Bundled vector fonts
Headings use Barlow Condensed Bold; body, buttons and values use Share Tech Mono.
Both TTFs and their SIL Open Font License notices are included in package/NVSE/Plugins/LukesActorBrowser/Fonts.
src/vectorfonts.h registers them privately in the game process and creates cached grayscale glyph atlases at each requested pixel size.
src/vanillafonts.h supplies the glyph layout/compositor; its legacy game-asset loader is no longer used by the menu.
No Windows font installation or external font mod is required.

## Templates
Browser:ShowTemplates defaults to 0. The in-menu Settings toggle and optional MCM both read/write it.
When off, records with Template in the display name or editor ID are hidden.
When on, these records are listed and can be requested for spawning. Some templates may not produce a visible actor.
Normal template inheritance alone does not hide an actor.

## 1.0.7 startup fix
Fonts are read through the process filesystem and registered from memory for MO2 compatibility. Missing fonts fall back to system fonts. See package/RELEASE-1.0.7.txt.


## Pip-Boy colour and controller update
See package/RELEASE-1.0.7.txt for the new controls, colour synchronisation, author credit and validation limits.


## Supported control APIs (1.0.12)
See package/RELEASE-1.0.12.txt for the controller-hook removal, xNVSE 6.3.11 requirement, restoration behaviour and shared JIP button-flag limitation. Existing DirectInput and renderer hooks remain.
