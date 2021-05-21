#!/bin/bash

sam build

#aws s3 sync ./html-build/HTML5 s3://pioneer-0 --delete \
#    --exclude "*" \
#    --include "*.js" \
#    --include "*.wasm" \
#    --include "*.data" \
#    --include "*.html" \
#    --include "Utility.js" \
#    --include ".htaccess"
