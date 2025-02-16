# Input dictionary files

This page describes the various file formats that together form a list/table/dictionary containing object/adjective entries.

## Nomenclature

In order to avoid any mixups with objects, adjectives and so on, the following terms are used throughout this docs:

- *Input*: generic term describing either objects or adjectives (note that they may even individually contain multiple words, like `ROCKET LAUNCHER`), as in the literal input typed in Maxwell's notebook.

- *Object* and *Adjective*: these are rather self explanatory, the two kinds of inputs the game supports.

- *Match*: actual object/adjective entry: the same input might correspond to multiple matches, like `AMAZON` can be either the rainforest or the native people.

- *Description*: additional text used by the game to distinguish matches: for example, `AMAZON` can be either `PLACE` or `PERSON`, as just mentioned above. The text is displayed in-game in parentheses, as in like `AMAZON (PLACE)`.

> Note: all these names are obviously unofficial, as well as the file format naming used below (and pretty much in the overall documentation)

## Files

For each language, both for objects and adjectives (separately), the game stores dictionary data in three different but related files (four for objects):

- Input list file: contains the actual input entries.

- "Lookup" offset list file: contains offsets to entries in the input list file.

- "Match" offset list file: contains offsets to entries in the input list file.

  - Both offset list files have the same format, and essentially order/index inputs in different orderings. The "lookup" file lists them in alphabetical order, while the "match" file lists them in a somewhat arbitrary ordering, even containing empty input entries (see below).

> Note: the "match" list seems to contain input entries as the developers kept creating and adding them, since they seem to be clustered around particular topics: for instance, the first blob of non-empty inputs are all musical instruments, and similar topics arise throughout the list. Moreover, the empty input entries probably correspond to old/dev/beta/testing inputs that were discarded throughout development.

- Match description list file (only for objects): contains description texts for inputs with multiple matches.

> Note: despite having remarkably different roles in the game logic, objects and adjectives are treated together here since they practically share the same formats described in this page. In fact, game code contains four functions to get the hardcoded file ID for each file according to the system language, where for the three common object/adjective files, the functions take a `bool is_object` argument whether to return object or adjective dictionary file IDs.

> Note: file IDs for lookup offset list files are far beyond the other mentioned files (for all languages), which might suggest that this list/ordering was added late into development.

### Input list file format

#### Character dictionary

The file starts with a "character dictionary" section:

```c
u8 char_dict_len;
char char_dict[char_dict_len];
u32 input_entry_count;
u32 input_entry_start_offset_2d_table[char_dict_len * char_dict_len];
```

The character dictionary consists on a list of characters, that inputs below may start with: for instance, "ABCDEFG...".

The dictionary is followed by the total number of input entries (coming after this section), and by a bi-dimensional array with entries for each character in the dictionary consisting on 32-bit absolute offsets of input entries below.

For instance, if the dictionary had five characters "ABCDE", the bi-dimensional table would be an array of `5*5 = 25` 32-bit offsets, and it shall be understood in the following way:

|   | A                                       | B                | C                | D                | E                |
|---|-----------------------------------------|------------------|------------------|------------------|------------------|
| A | Offset to first input with name "AA..." | Same for "AB..." | Same for "AC..." | Same for "AD..." | Same for "AE..." |
| B | Same for "BA..."                        | Same for "BB..." | Same for "BC..." | Same for "BD..." | Same for "BE..." |
| C | Same for "CA..."                        | Same for "CB..." | Same for "CC..." | Same for "CD..." | Same for "CE..." |
| D | Same for "DA..."                        | Same for "DB..." | Same for "DC..." | Same for "DD..." | Same for "DE..." |
| E | Same for "EA..."                        | Same for "EB..." | Same for "EC..." | Same for "ED..." | Same for "EE..." |

Thus, the offset to the table offset for a two-letter prefix `MN...` is calculated by (as the game itself computes):

```
u32 offset_offset(MN) = (0x01 + 0x01 * Character count + 0x04) + 0x04 * (index(M) * <character-count> + index(N));
```

Where `index(X)` corresponds to the index of the letter `X` in the dictionary above (in game code, such an index is computed by a searching loop over dictionary characters).

This system is likely intended for a quick lookup of inputs based on the first two letters of the input text.

#### Input entry

Each input entry follows the following format (and follow one after each other without any alignment/padding, as per usual with other file formats):

```c
u8 total_entry_size;
u8 input_text_len;
char input_text[input_text_len];
u16 lookup_list_idx;
u16 unk_zero;
u8 match_count;
u16 file_id_per_match[match_count];
u16 match_list_idx_per_match[match_count];
u16 unk_per_match[match_count];
```

> TODO: is total entry size used by the game?

> Note: keep in mind that the way fields are stored for each match is not the usual one! all the fields are laid out as individual arrays (unlike regular behaviour when having an array of plain data structures, for instance)

### Input offset list file format

These files just contain `u32` absolute input entry offsets for their corresponding input list file.

The offset count doesn't have to match the actual input/total match count, since the files may contain invalid offsets: any zero-offset makes no sense as a file. The game explicitly checks that `offset != 0` when reading inputs, which shows that any zero-offsets indeed correspond to invalid/empty input entries in this lists.

For "match" offset lists, note that the offset might point to a different input. For instance, there is an input entry for `BOG` with a single match, and that match's entry in the "match" list offset file points to a different input entry, the one for `SWAMP`: this obviously serves as a multi-word mechanism, so that multiple inputs can be dealt with a single root input (think `PASTA`, and then many kinds of pasta like `MACARONI`, `FUSILLI`, `RIGATONI` merely point to `PASTA`), since the game ultimately seems to load object/adjective data based on "match" list offset entries.

### Match description list file format

#### Character dictionary

This format also starts with a character dictionary + offset lookup table, similar to input list files:

```c
u8 char_dict_len;
char char_dict[char_dict_len];
u32 desc_entry_start_offset_table[char_dict_len];
```

Unlike with input list files, no total entry count is provided, and the lookup table is one-dimensional, providing lookup based on the first character of the input text.

> Note: the game never loads these files entry by entry in order to find the description of the matches of a given input: instead, it jumps to the first-letter offset by the lookup table, and then compares the input name to each description entry, checking entry by entry (which is why there is no real need of an "entry count" field) until it is found

#### Description entry

Each input entry follows the following format (and follow one after each other without any alignment/padding, as per usual):

```c
u8 input_text_len;
char input_text[input_text_len];
u8 match_desc_count;
u16 unk_per_match[match_count];
u8 match_desc_len_per_match[match_count];
char match_desc_per_match[match_desc_len_per_match][match_count];
```

## Input dictionaries

### Objects

| Language | Input list file ID | "Lookup" offset list file ID | "Match" offset file ID | Match description list file ID |
|----------|--------------------|------------------------------|------------------------|--------------------------------|
| English  | 13220              | 32173                        | 13251                  | 13236                          |
| Dutch    | 13228              | 32171                        | 13250                  | 13235                          |
| French   | 13225              | 32175                        | 13253                  | 13238                          |
| German   | 13219              | 32176                        | 13255                  | 13240                          |
| Italian  | 13227              | 32177                        | 13256                  | 13241                          |
| Spanish  | 13221              | 32180                        | 13262                  | 13246                          |
| Unknown  | 24063              | 32172                        | 24064                  | 24073                          |

### Adjectives

| Language | Input list file ID | "Lookup" offset list file ID | "Match" offset file ID |
|----------|--------------------|------------------------------|------------------------|
| English  | 13267              | 32161                        | 13282                  |
| Dutch    | 13275              | 32159                        | 13281                  |
| French   | 13272              | 32163                        | 13284                  |
| German   | 13266              | 32164                        | 13290                  |
| Italian  | 13274              | 32165                        | 13291                  |
| Spanish  | 13268              | 32168                        | 13295                  |
| Unknown  | 24074              | 32160                        | 24075                  |
