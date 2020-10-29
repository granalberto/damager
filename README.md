# Damager
The files damager.

**damager** is a command line utility for testing file alteration
  monitors ans other things. It doesn't change the file's size but
  writes a chunk of garbage instead. The garbage writen is randomly
  taken from `/dev/random` and writen on a random position within the
  file.
## Compile
`clang -std=c90 -o damager damager.c`

Or just run

`make`

## Install
The binary **damager** should be placed in `/usr/local/bin/`.

This README needs to be improved.