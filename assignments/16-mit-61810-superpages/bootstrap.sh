#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
if [ ! -d upstream/starter/.git ]; then git clone 'https://github.com/mit-pdos/xv6-riscv.git' upstream/starter; fi
git -C upstream/starter fetch origin pgtbl
git -C upstream/starter checkout pgtbl
curl -fL --retry 2 'https://pdos.csail.mit.edu/6.1810/2025/labs/pgtbl.html' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
