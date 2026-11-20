#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
if [ ! -d upstream/starter/.git ]; then git clone 'https://github.com/vijay03/cs360v-f21.git' upstream/starter; fi
git -C upstream/starter rev-parse --short HEAD
echo 'Source collection complete. No student implementation has been added.'
