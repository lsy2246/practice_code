#!/bin/bash

for file in /etc/nginx/sites-available/*;do
	base=$(basename "$file")
	ln -s "$file" "/etc/nginx/sites-enabled"
done
