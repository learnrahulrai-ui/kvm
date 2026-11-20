#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'http://williamwjs.github.io/assets/482_Project_3.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
