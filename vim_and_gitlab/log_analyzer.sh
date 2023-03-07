
#!/bin/bash

file="$1"

# Create unique files and hash sums
declare -a files
declare -a hashes

# Read input file by line
while IFS='' read -r line || [[ -n "$line" ]]; do
  # Extract path to file and hash sum from each line
  path=$(echo "$line" | awk '{print $0}')
  hash=$(echo "$line" | sort -u | awk '{print $7}')

  # Add path to files array
  if [[ ! " ${files[@]} " =~ " $path " ]]; then
    files+=("$path")
  fi

  # Add hash sum to hashes array
  if [[ ! " ${hashes[@]} " =~ " $hash " ]]; then
    hashes+=("$hash")
  fi
done < "$file"

# Count number of files containing '.txt'

sorted_unique_text=($(echo "${files[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' '))


txt_files=0
for i in "${sorted_unique_text[@]}"; do
  if [[ "$i" =~ .*\.txt ]]; then
    ((txt_files++))
  fi
done


# Output
echo "${#files[@]} $txt_files $(( ${#hashes[@]}  ))"



