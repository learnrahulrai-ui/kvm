#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
if [ ! -d upstream/starter/.git ]; then git clone 'https://github.com/dpw/kvm-hello-world.git' upstream/starter; fi
git -C upstream/starter rev-parse --short HEAD
curl -fL --retry 2 'https://www.cse.iitb.ac.in/~cs695/pa/pa1.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
