#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
if [ ! -d upstream/starter/.git ]; then git clone 'https://github.com/mit-pdos/xv6-public.git' upstream/starter; fi
git -C upstream/starter rev-parse --short HEAD
curl -fL --retry 2 'https://pages.cs.wisc.edu/~shivaram/cs537-sp19/p2b.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
