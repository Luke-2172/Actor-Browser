LUKE'S ACTOR BROWSER 1.0.12

A separate F10 menu for Fallout: New Vegas, using Luke's Item Browser's amber
three-column layout, patterned backdrop, shadow and VATS menu sounds.

REQUIREMENTS
Fallout: New Vegas 1.4.0.525; xNVSE 6.3.11+; JIP LN NVSE 56.95+.
A loaded save is required for spawning and actor-value operations.
Windows with Direct3D 9 and DirectInput 8. The included x86 native DLL uses the
static C++ runtime. No PowerShell or development tools are needed to play.
Optional settings in MCM require The Mod Configuration Menu and MCM Extender
1.63+. Neither MCM nor an ESP is required for the browser itself.

INSTALL
Install Lukes-Actor-Browser-FNV-1.0.12.zip with MO2/Vortex. NVSE and MCM belong
under the game's Data folder. Launch using xNVSE, load a save, press F10.
The DLL, INI, scripts and MCM registration have their own names and do not
replace Item Browser. Close one browser before opening the other.

SPAWN
Select a loaded plugin, then All / NPCs / Creatures. Search names, Editor IDs,
or file-local IDs. Quantity choices: 1, 3 or 5. Double-click an actor, click
SPAWN, or press Enter outside a search box. Actors appear near the player.
Spawns retain the original actor's AI, factions, hostility and attached scripts.
This creates copies; it does not move existing quest actors. Spawned copies may
persist in saves. Use a separate save when experimenting with quest NPCs.
Leveled lists and placed references are excluded; only NPC_ and CREA base forms
are accepted. Overrides resolve through the record's original master plugin.

ACTOR VALUES
Open VALUES. Select Player, Crosshair Actor or Last Spawned. For Crosshair Actor,
aim at the actor before opening F10, then click the target or Read / Capture.
The captured reference remains selected; Apply does not silently pick a new actor.
Select one of 30 values, read its base/current values, click the number field,
use Backspace to replace it, then click Apply Value. Mouse wheel scrolls the list.
Changes use SetActorValue on the selected reference. Current values may differ
from base values due to damage, equipment, effects or game scripts. The menu
reads back the engine result and reports when the requested base value was not
retained. Changes may persist in saves; there is no automatic undo.
Selections and the Last Spawned shortcut reset when a save is loaded. Resetting
those shortcuts does not delete previously spawned actors.

SETTINGS
F10 opens/closes; Esc closes or leaves Settings. Mouse speed, opacity, sounds
template visibility and override visibility are available inside the menu. FunctionKey=10 in
Data/NVSE/Plugins/LukesActorBrowser.ini sets F10; numbers 1-24 select F1-F24.
Optional MCM controls the same file. RenderScale requires restart. FontFace is no longer used.
Open sound: ui_vats_move. Close sound: ui_vats_ready.

COMPATIBILITY AND VALIDATION
This uses a renderer with cached backdrop and partial list
uploads. It still needs to capture the game's D3D device. The reported FNV Display
Tweaks incompatibility is unresolved; this release does not claim to fix it.
Graphics wrappers, co-installed overlays, actual spawning and game-side script
compilation must be tested in game. A successful DLL build or mock test cannot
establish those results. The game continues running while the overlay is open.
If missing: collect LukesActorBrowser.log, nvse.log and
Data/config/LukesActorBrowserRuntime.ini (MO2 may put these in Overwrite).

The mod uses bounded numeric requests and a fixed actor-value allowlist, not
arbitrary console commands. It checks active plugins, actor types, sessions,
targets and ranges. This is not an exhaustive security certification.

BUNDLED VECTOR FONTS
Barlow Condensed Bold: title, headings and navigation tabs.
Share Tech Mono: lists, buttons, values and explanatory text.
TTF files and SIL Open Font License notices are included under NVSE/Plugins/LukesActorBrowser/Fonts.
They load privately inside New Vegas. No Windows font installation, font mod or internet connection is required.
Text is rasterized at the selected resolution and cached. RenderScale=3 is the default; 2 uses less graphics memory.

TEMPLATE VISIBILITY
Show templates is OFF by default. Enable it in Settings or optional MCM.
It controls records containing Template in their display name or editor ID.
Normal actors inheriting template data remain available in either mode.
Some template records do not produce a visible actor when spawned.


CURRENT UPDATE: See RELEASE-1.0.12.txt for Pip-Boy colours and Xbox controller controls.


Controller gameplay isolation: see RELEASE-1.0.12.txt. Update both browsers and restart the game.

This version replaces the previous controller hook with supported APIs. Requires xNVSE 6.3.11+. See RELEASE-1.0.12.txt for compatibility details.

Controller shortcut: hold LB (left bumper) and press D-pad Right.
