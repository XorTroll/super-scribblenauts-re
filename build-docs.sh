#!/bin/bash

# Note: you need to define SCRIBBLETOOL / FILE1I / FILE1P somewhere before running this script
# Example:
# export SCRIBBLETOOL=.../scribbletool/build/scribbletool
# export FILE1I=.../bh2p-nitrofs/1i
# export FILE1P=.../bh2p-nitrofs/1p

rm -rf docs
mkdir -p docs

cd bh2p-docs
mkdocs build
cd ..

cp -r bh2p-docs/site/* docs/

mkdir -p docs/objgen-en
$SCRIBBLETOOL gen-obj-html -g bh2p -i $FILE1I -p $FILE1P -l en -o docs/objgen-en
