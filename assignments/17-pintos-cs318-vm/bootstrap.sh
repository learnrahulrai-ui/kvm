#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'https://web.eecs.umich.edu/~ryanph/jhu/cs318/fall19/project/project3.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
