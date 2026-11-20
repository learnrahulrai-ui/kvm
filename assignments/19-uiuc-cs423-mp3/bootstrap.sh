#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'https://courses.grainger.illinois.edu/cs423/sp2021/mp/mp3/index.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
