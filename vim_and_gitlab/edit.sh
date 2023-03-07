#!/bin/bash

# Define the input parameters
file_path=$1
check_string=$2
replace_string=$3

# Check if the file exists
if [ ! -f "$file_path" ]; then
  echo "Error: File not found."
  exit 1
fi

# Create a backup of the original file
cp "$file_path" "${file_path}.bak"

# Replace the search string with the replace string
sed -i "" "s/$check_string/$replace_string/g" $file_path

# Log the change to src/files.log
timestamp=$(date +%Y-%m-%d)
timestamp2=$(date +%H:%M)
file_size=$(stat -f%z "$file_path" | awk '{print $1}')
sha=$(shasum -a 256 "$file_path" | awk '{print $1}')
echo "src/""$file_path - $file_size - $timestamp $timestamp2 - $sha - sha256" >> files.log

echo "Successful!"
