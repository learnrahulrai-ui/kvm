#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
if [ ! -d upstream/starter/.git ]; then git clone 'https://github.com/dpw/kvm-hello-world.git' upstream/starter; fi
git -C upstream/starter rev-parse --short HEAD
curl -fL --retry 2 'https://soumadip.github.io/courses/os-lab/content/assignments/capstone/' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
