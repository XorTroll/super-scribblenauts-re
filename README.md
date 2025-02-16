# Super Scribblenauts (EU) reverse-engineering

This repository contains my reverse-engineering work of the *European version* of **Super Scribblenauts** (game code `BH2P`): ASM-hacking, documenting game logic/formats, command-line utilities and hopefully a proper object/adjective editor ;)

- [Super Scribblenauts (EU) reverse-engineering](#super-scribblenauts-eu-reverse-engineering)
  - [ASM-hacking](#asm-hacking)
  - [Libraries](#libraries)
  - [Command-line utility](#command-line-utility)
  - [Credits](#credits)

## ASM-hacking

The [ASM-hacking tests](asmhacks) serve as examples on how to inject custom code in the game, using generated [headers](re-export/include) and [symbols](re-export/mkds-eu-decomp-symbols.x) of my reverse-engineering work on this game.

## Libraries

In order to make any PC tools, [libobjectnaut](libobjectnaut) are C++ libraries to work with game formats. Any further tools in this repository are made thanks to these base libraries.

Like the tools themselves, these libraries are in a very early stage, and only a handful of formats are implemented there.

## Command-line utility

For practical purposes (to make my life easier) I made a simple command-line tool, [bh2putil](bh2putil).

It currently has the following (very limited) features:

- Print a specific file (by providing its file ID, more in [the RE docs](https://xortroll.github.io/super-scribblenauts-re/)) as a text file, printing all its messages

- Print list of objects/adjectives of a given language

You will need [CMake](https://cmake.org/) in order to compile it, without any external dependencies other than standard C++.

## Credits

- [GBATEK](https://problemkaputt.de/gbatek.htm) for its great (although sometimes limited/outdated) DS docs

- [Pokémon Diamond decompilation](https://github.com/pret/pokediamond) as a helpful reference for already (partially) understood DS SDK code

- ['Hacking Nintendo DS' EnHacklopedia page](https://doc.kodewerx.org/hacking_nds.html) as the only (and great) specifications I found regarding DS cheat codes

- [NCPatcher](https://github.com/TheGameratorT/NCPatcher) as a great tool for simplifying the process of making DS ASM hacks
