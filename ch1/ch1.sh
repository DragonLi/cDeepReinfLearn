#!/bin/sh

#  ./randhandgen 1 2 3 > input.txt
#  ./j < input.txt > test1.log
./randhandgen 1 2 3 | ./j > test1.log

# cargo build -Z unstable-options --out-dir .

# ./target/debug/ch1 randhandgen 1 2 3 > input.txt
# ./target/debug/ch1 j < input.txt > test2.log

./target/debug/ch1 randhandgen 1 2 3 | ./target/debug/ch1 j > test2.log
