# Text list file

## File format

Files containing texts/messages have the following format:

```c
u8 text_count_per_lang;
{
    char text_1[...];
    char '\n';
    char text_2[...];
    char '\n';
    // ...
} texts_english;
{
    // ...
} texts_dutch;

// ...
```

There is an initial byte containing the number of texts (per language). The remaining contents are all text strings, separated by newlines (character `0x0A` or `'\n'`). No further separation is done to indicate which strings belong to which language, they are all in order: all English strings, followed by all Dutch strings and so on (see [languages](../lang.md)) for each language.

Note that, like with filesystem offsets, the last string will also end in a newline (basically, the newline is the ending indicator for every string).

## Text format / escapes

A unique property of Super Scribblenauts' strings is that they are all always uppercase (take a look at every single dialog/message/button when playing the game).

This is, in fact, somewhat intentional or taken advantage of: certain lowercase characters are internally parsed as special operations on the string:

| Character | Action                    | Example text |   |   |
|-----------|---------------------------|--------------|---|---|
| c         | Center                    | cDEMOc       |   |   |
| i         | Use alternative font      | iDEMOi       |   |   |
| l         | Use large "default" font  | lDEMOl       |   |   |
| m         | Use medium "default" font | mDEMOm       |   |   |
| n         | Align left                | nDEMOn       |   |   |
| o         | Align right               | oDEMOo       |   |   |

Note that, by default, the start "default" font is used (see [fonts](font.md)).

There is still no clear difference between texts that only start with the escape characters (like "ciHELLO") as opposed to texts that start and end with it (like "ciHELLOic", or maybe even "ciHELLOci"...?).

## Text list files

> TODO
