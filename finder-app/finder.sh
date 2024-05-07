#!/bin/bash

#check if the number of arguments is not equal to 2
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

#Extract arguments
filesdir="$1"
searchstr="$2"

#Check if filesdir exists and is a directory
if [ ! -d "$filesdir" ]; then
    echo "$filesdir is not a directory or does not exist"
    exit 1
fi

#Find files containing the search string and count matching lines
num_files=$(find "$filesdir" -type f | wc -l)
num_matches=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Print results
echo "The number of files are $num_files and the number of matching lines are $num_matches"
