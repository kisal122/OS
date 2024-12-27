#!/bin/bash
# Script to hash a 4-digit input using SHA-256

if [ $# -ne 1 ]; then
    echo "Usage: $0 <4-digit-number>"
    exit 1
fi

input=$1
echo -n $input | sha256sum | awk '{print $1}' > hash_output.txt
echo "Hash saved to hash_output.txt"

