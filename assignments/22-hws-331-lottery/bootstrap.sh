#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p upstream
if [ ! -d upstream/starter/.git ]; then git clone 'https://github.com/remzi-arpacidusseau/ostep-projects.git' upstream/starter; fi
git -C upstream/starter rev-parse --short HEAD
curl -fL --retry 2 'https://math.hws.edu/~bridgeman/courses/331/s26/projects/xv6-scheduling.html~' -o upstream/assignment.html
echo 'Source collection complete. No student implementation has been added.'
