#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
# 6.1810/2025/labs/util.html explicitly identifies this course-specific source.
# mit-pdos/xv6-riscv does NOT provide the required 2025 lab branch.
if [ ! -d upstream/starter/.git ]; then
  git clone 'git://g.csail.mit.edu/xv6-labs-2025' upstream/starter
fi
git -C upstream/starter fetch origin
if ! git -C upstream/starter show-ref --verify --quiet refs/remotes/origin/pgtbl; then
  echo 'Official lab branch pgtbl missing: do not substitute base xv6.' >&2
  exit 2
fi
git -C upstream/starter switch --create course-pgtbl --track origin/pgtbl 2>/dev/null ||
  git -C upstream/starter switch course-pgtbl
git -C upstream/starter rev-parse HEAD
echo 'Use: cd upstream/starter && make grade'
