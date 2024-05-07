#!/bin/bash

#Check if the number of arguments is not equal to 2
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# Extract arguments
writefile="$1"
writestr="$2"

# Check if writefile is specified 
if [ -z "$writefile" ]; then 
    echo "Please specify string to write to the file"
    exit 1
fi

# Create a directory if it doesn't exist
mkdir -p "$(dirname "$writefile")"

# Write the string to the file
echo "$writestr" > "$writefile"

# Check if the file was created successfully 
if [ $? -ne 0 ]; then
    echo "Error: Failed to create the file $writefile"
    exit 1
fi

echo "File $writefile created successfully with content:"
echo "$writestr"
