# Dictionary files

This page describes the various file formats that together form a list/table/dictionary containing object/adjective entries.

## Nomenclature

In order to avoid any mixups with objects, adjectives and so on, the following terms are used throughout this docs:

> Note: the following names/terms come from debug symbols found in Scribblenauts Remix releases, but since the underlying formats are virtually identical (and the engine code is also almost identical) it is safe to assume these were used with Super Scribblenauts as well.

- *Object* / *Adjective*: these are rather self explanatory, the two kinds of inputs the game supports.

- *Word*: generic term describing either objects or adjectives (note that they may even individually contain multiple "words", like `ROCKET LAUNCHER`), as in the invidual input pieces typed in Maxwell's notebook.

- *Meaning*: used occasionally since the same input might correspond to multiple matches, like `AMAZON` can be either the rainforest or the native people.

- *Detail*: additional text used by the game to distinguish matches: for example, `AMAZON` can be either `PLACE` or `PERSON`, as just mentioned above. The text is displayed in-game in parentheses, as in like `AMAZON (PLACE)`.

## Files

For each language, both for objects and adjectives (separately), the game stores dictionary data in four different but related files (the last one containing details, only used for objects):

- Dictionary file: contains the actual word entries.

- "Word offset" and "Jump offset" file: contain offsets to word entries in the dictionary file.

  Both offset list files have the same format, and essentially order/index words in different orderings. The "word table" file lists them in alphabetical order, while the "jump table" file lists them in a somewhat arbitrary ordering, even containing empty word entries (see below).

> Note: the "jump table" list seems to contain (offsets to) word entries as the developers kept creating and adding them, since they seem to be clustered around particular topics: for instance, the first blob of non-empty words are all musical instruments, and similar topics arise throughout the list. Moreover, the empty word entries probably correspond to old/dev/beta/testing words that were discarded throughout development.

- Details file (only for objects): contains detail texts for words with multiple meanings.

> Note: despite having remarkably different roles in the game logic, objects and adjectives are treated together here since they practically share the same formats described in this page. In fact, game code contains four functions to get the hardcoded file ID for each file according to the system language, where for the three common object/adjective files, the functions take a `bool is_object` argument whether to return object or adjective dictionary file IDs.

> Note: file IDs for word table list files are far beyond the other mentioned files (for all languages), which might suggest that this table was added later into development.

> Note: offset indices in the jump table are known as **object IDs** or **adjective IDs** throughout the game code, and offset indices in the word table are known as **word IDs**.

### Dictionary file format

#### Character dictionary

The file starts with a "character dictionary" section:

```c
u8 char_dict_len;
char char_dict[char_dict_len];
u32 word_count;
u32 word_entry_start_offset_2d_table[char_dict_len * char_dict_len];
```

The character dictionary consists on a list of characters, that words below may start with: for instance, "ABCDEFG...".

The dictionary is followed by the total number of words (coming after this section), and by a bi-dimensional array with entries for each character in the dictionary consisting on 32-bit absolute offsets of word entries below.

For instance, if the dictionary had five characters "ABCDE", the bi-dimensional table would be an array of `5*5 = 25` 32-bit offsets, and it shall be understood in the following way:

|   | A                                      | B                | C                | D                | E                |
|---|----------------------------------------|------------------|------------------|------------------|------------------|
| A | Offset to first word with name "AA..." | Same for "AB..." | Same for "AC..." | Same for "AD..." | Same for "AE..." |
| B | Same for "BA..."                       | Same for "BB..." | Same for "BC..." | Same for "BD..." | Same for "BE..." |
| C | Same for "CA..."                       | Same for "CB..." | Same for "CC..." | Same for "CD..." | Same for "CE..." |
| D | Same for "DA..."                       | Same for "DB..." | Same for "DC..." | Same for "DD..." | Same for "DE..." |
| E | Same for "EA..."                       | Same for "EB..." | Same for "EC..." | Same for "ED..." | Same for "EE..." |

Thus, the offset to the table offset for a two-letter prefix `MN...` is calculated by (as the game itself computes):

```
u32 offset_offset(MN) = (0x01 + 0x01 * Character count + 0x04) + 0x04 * (index(M) * <character-count> + index(N));
```

Where `index(X)` corresponds to the index of the letter `X` in the dictionary above (in game code, such an index is computed by a searching loop over dictionary characters).

This system is likely intended for a quick lookup of words based on the first two letters of the word name.

#### Word entry

Each word entry follows the following format (and follow one after each other without any alignment/padding, as per usual with other file formats):

```c
u8 total_entry_size;
u8 name_len;
char name[name_len];
u16 word_id;
u16 unk_zero;
u8 meaning_count;
u16 file_id_per_meaning[meaning_count];
u16 obj_adj_id_per_meaning[meaning_count];
u16 unk_per_meaning[meaning_count];
```

> TODO: is total entry size used by the game?

> Note: keep in mind that the way fields are stored for each meaning is not the usual one! all the fields are laid out as individual arrays (unlike regular behaviour when having an array of plain data structures, for instance)

### Jump / Word table file format

These files just contain `u32` absolute word entry offsets for their corresponding dictionary file.

The offset count doesn't have to match the actual word/total meaning count, since the files may contain invalid offsets: any zero-offset makes no sense as a file. The game explicitly checks that `offset != 0` when reading words, which shows that any zero-offsets indeed correspond to invalid/empty word entries in this lists.

For jump table offsets, the offset might point to a different word. For instance, there is an word entry for `BOG` with a single meaning, and that meaning's entry in the jump table file points to a different word entry, the one for `SWAMP`: this pretty much serves as a synonym mechanism, so that multiple words can be dealt with a single root word (think of `PASTA`, and then many kinds of pasta like `MACARONI`, `FUSILLI`, `RIGATONI` merely point to `PASTA`), since the game ultimately seems to load object/adjective data based on their object/adjective IDs.

### Details file format

#### Character dictionary

This format also starts with a character dictionary + offset lookup table, similar to dictionary files:

```c
u8 char_dict_len;
char char_dict[char_dict_len];
u32 detail_entry_start_offset_table[char_dict_len];
```

Unlike with dictionary files, no total entry count is provided, and the lookup table is one-dimensional, providing lookup based on the first character of the word name.

> Note: the game never loads these files entry by entry in order to find the detail text of the meanings of a given word: instead, it jumps to the first-letter offset by the lookup table, and then compares the word name to each detail entry, checking entry by entry (which is why there is no real need of an "entry count" field) until it is found.

#### Detail entry

Each detail entry follows the following format (and follow one after each other without any alignment/padding, as per usual):

```c
u8 word_name_len;
char word_name[word_name_len];
u8 meaning_count;
u16 unk_obj_id_per_meaning[meaning_count];
u8 detail_text_len_per_meaning[meaning_count];
char detail_text_per_meaning[detail_text_len_per_meaning][meaning_count];
```

## Dictionary file IDs

### Objects

| Language | Dictionary file ID | Word table file ID | Jump table file ID | Details file ID |
|----------|--------------------|--------------------|--------------------|-------------|
| English  | 13220              | 32173              | 13251              | 13236       |
| Dutch    | 13228              | 32171              | 13250              | 13235       |
| French   | 13225              | 32175              | 13253              | 13238       |
| German   | 13219              | 32176              | 13255              | 13240       |
| Italian  | 13227              | 32177              | 13256              | 13241       |
| Spanish  | 13221              | 32180              | 13262              | 13246       |
| Unknown  | 24063              | 32172              | 24064              | 24073       |

### Adjectives

| Language | Dictionary file ID | Word table file ID | Jump table file ID |
|----------|--------------------|--------------------|--------------------|
| English  | 13267              | 32161              | 13282              |
| Dutch    | 13275              | 32159              | 13281              |
| French   | 13272              | 32163              | 13284              |
| German   | 13266              | 32164              | 13290              |
| Italian  | 13274              | 32165              | 13291              |
| Spanish  | 13268              | 32168              | 13295              |
| Unknown  | 24074              | 32160              | 24075              |
