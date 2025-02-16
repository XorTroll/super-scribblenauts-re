#!/bin/bash

rm -rf docs
mkdir -p docs

cd bh2p-docs
mkdocs build
cd ..

cp -r bh2p-docs/site/* docs/
