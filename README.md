# samp-multicp

[![sampctl](https://img.shields.io/badge/sampctl-samp--multicp-2f2f2f.svg?style=for-the-badge)](https://github.com/LuminouZ307/samp-multicp)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Read This

This script is actually inspired from [here](https://github.com/TShoKT/multiple-checkpoints-samp),
but i made my own version and using some library like YSI.

## Installation

Simply install to your project:

```bash
sampctl package install LuminouZ307/samp-multicp
```

Include in your code and begin using the library:

```pawn
#include <multicp>
```

## Usage

### Functions

* `SetPlayerMultiCP(playerid, Float:x, Float:y, Float:z, bool:autodisable = false, color = MULTICP_DEFAULT_COL)` :

  * Sets player checkpoint.
  
  * playerid = The player ID you wan't sets the checkpoint.
  * x = x position.
  * y = y position.
  * z = z position.
  * autodisable = if autodisable is true, when you entering the checkpoint it will automatically disabled.
  * color = checkpoint colour (default is red).

* `DisablePlayerMultiCP(playerid, cpid)` :

  * Remove player checkpoint.

* `IsPlayerInMultiCP(playerid, cpid)` :

  * Check if player in a checkpoint.

* `DisablePlayerAllMultiCP(playerid)` :

  * Remove player all checkpoints.

### Callbacks

* `OnPlayerLeaveMultiCP(playerid, cpid)` :

  * Detect when player leaving checkpoint.

* `OnPlayerEnterMultiCP(playerid, cpid)` :

  * Detect when player entering checkpoint.


## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```
