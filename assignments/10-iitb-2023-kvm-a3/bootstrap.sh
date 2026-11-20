#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
curl -fL --retry 2 'https://www.cse.iitb.ac.in/~puru/courses/spring22/a3_skeletoncode.tar.gz' -o upstream/a3_skeletoncode.tar.gz
tar -tzf upstream/a3_skeletoncode.tar.gz | head -n 50
echo 'Archive downloaded but not extracted automatically; inspect paths before extraction.'
echo 'Source collection complete. No student implementation has been added.'
