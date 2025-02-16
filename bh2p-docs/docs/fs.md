# Game filesystem

## Game files

These are all the files present in the game's Nitro FS:

- `dwc/utility.bin`: DWC utility data file, present in any DS games using Download Play

- `audio.sdat`: [SDAT sound data file](https://problemkaputt.de/gbatek.htm#dssoundfilessdatsounddataarchive) (format used by most DS games)

- `audio.sadl`: C header file with SDAT sound index values: likely left by mistake, just a regular header file included in the code when compiling

    > Note: for quite a lot of DS games, these kind of intermediate-build files are mistakengly left in the Nitro FS

- `1i` and `1p`: these files contain everything else in the game, in a custom filesystem format explained below

## Filesystem format

The files `1i` and `1p` together contain a filesystem, in a unique format used by this game (even the original Scribblenauts did it differently, storing files plainly in the Nitro FS).

There is a total of `33383` files in the release game. Files contain no names, they are referred to by their index (file `0`, file `1` ... up to file `33382`). There are only a few files where the file indices are hardcoded in-game, while various other formats internally contain other sub-file indices for other content.

The file `1i` contains all the file offsets. It has the following binary format:

```c
u32 file_count;
u32 file_offsets[file_count + 1];
```

There is an additional offset, which (at least in the release game) is just the repeated previous offset. This is likely done so that for the `i`-th file, the file size can always be computed as:

```c
u32 file_size_i = file_offsets[i + 1] - file_offsets[i];
```

The game does indeed compute file sizes this way, expecting that intentional extra offset to be contained in `1i`.

Various files are empty in the release game (the file offset is the same as the next file offset, thus the file has size `0`).

File offsets found in `1i` are absolute offsets of file `1p`, which contains file data. Each file data is ended by a byte indicating whether it is compressed:

```c
// ...

// current offset: file_offsets[i]
u8 file_i_data[file_size_i];
u8 file_i_comp_type; // 0 if plaintext, 1 if LZ77-compressed

// current offset: file_offsets[i+1]
u8 file_ip1_data[file_size_ip1];
u8 file_ip1_comp_type;

// ...
```

> Note: unlike other file formats (from the SDK iself, and so on), binary formats specific to this game are not designed with any alignment/padding considerations, as can be seen by this filesystem data format (the final byte is always put after file data)

The release game has various different functions to read file data. Some functions read the entire data in an allocated buffer, while in other places, file reading is done "manually" by pretty much making raw reads to `1p`.