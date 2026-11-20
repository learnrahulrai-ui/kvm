#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'https://csapp.cs.cmu.edu/2e/cachelab.pdf' -o upstream/assignment.pdf
echo 'Source collection complete. No student implementation has been added.'
