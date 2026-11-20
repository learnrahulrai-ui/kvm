#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'https://www.cse.iitb.ac.in/~cs695/pa/pa2.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
