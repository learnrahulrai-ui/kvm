#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'https://www.cs.unc.edu/~porter/courses/comp790/s20/lab6b.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
