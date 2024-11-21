#!/usr/bin/bash

find ../testy/ \( -name "*.gbl" -o -name "*.imp" \) -exec cargo run -- {} \; && true || break
