#!/bin/bash

mkdir key

for i in {1..60}
do
    echo $((RANDOM%10 + 1)) > key/part${i}.key
done

echo "Generation completed"
