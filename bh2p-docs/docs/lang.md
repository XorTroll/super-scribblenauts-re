# Languages

The game has its own set of values for storing the active gameplay language:

| Language | Value |   |   |   |
|----------|-------|---|---|---|
| English  | 0     |   |   |   |
| Dutch    | 1     |   |   |   |
| French   | 2     |   |   |   |
| German   | 3     |   |   |   |
| Italian  | 4     |   |   |   |
| Spanish  | 5     |   |   |   |

The values are almost equal to DS firmware values, but `0` and `1` are different (in DS firmware, `0` corresponds to Japanese and `1` to English).

There is no support for Japanese (probably since the entire writing/word/object/adjective system would have needed to be entirely remade for Japanese writing), and there is support for Dutch language, despite DS(i) consoles never providing support for it.

The game has an option for changing the language (although it initially defaults to the console language, converting the firmware value to this values), so Dutch can be chosen there by the end user.
