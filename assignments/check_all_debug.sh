#!/usr/bin/env bash
# Build every checked-in assignment scaffold, never a student TODO solution.
set -uo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPILER="${CC:-gcc}"
FLAGS="-std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic"
printf 'compiler=%s\n' "$("$COMPILER" --version | head -n 1)"
printf 'flags=%s\n' "$FLAGS"
printf 'host=%s\n' "$(uname -a)"
printf '%-37s %-8s %-8s %-10s %-12s %-14s\n' 'folder' 'compile' 'smoke' 'debug' 'build_ms' 'peak_rss_kib'
errors=0
built=0
for dir in "$ROOT"/[0-9][0-9]-*; do
  [ -d "$dir" ] || continue
  name="$(basename "$dir")"
  cd "$dir" || exit 2
  make clean >/dev/null 2>&1
  start_ns="$(date +%s%N)"
  /usr/bin/time -f '%M' -o .compile_maxrss     make all CC="$COMPILER" CFLAGS="$FLAGS" >.compile.stdout 2>.compile.stderr
  result=$?
  end_ns="$(date +%s%N)"
  build_ms=$(((end_ns-start_ns)/1000000))
  rss="$(cat .compile_maxrss 2>/dev/null || printf '?')"
  compile='PASS'
  smoke='NOT-RUN'
  debug='NO'
  if [ "$result" -ne 0 ]; then
    compile='FAIL'
    errors=$((errors+1))
    sed -n '1,50p' .compile.stderr >&2
  else
    built=$((built+1))
    if ! make smoke >.smoke.stdout 2>.smoke.stderr; then
      smoke='FAIL'
      errors=$((errors+1))
      sed -n '1,50p' .smoke.stderr >&2
    else smoke='PASS'; fi
    if ! ./build/logic_drill --status >.logic.stdout 2>.logic.stderr; then
      echo "$name: logic drill failed to execute" >&2
      errors=$((errors+1))
    else
      checked="$(grep -c '^slot=' .logic.stdout || true)"
      if [ "$checked" -ne 20 ]; then
        echo "$name: expected 20 C logic tests, saw $checked" >&2
        errors=$((errors+1))
      fi
      tail -n 1 .logic.stdout | sed "s/^/$name: /"
      if ./build/logic_drill >.logic.check 2>.logic.checkerr; then
        if ! grep -q '^pass=20 blank=0 fail=0
    for exe in build/*; do
      [ -f "$exe" ] && [ -x "$exe" ] || continue
      if ! readelf -S "$exe" | grep -q '.debug_info'; then debug='NO'; errors=$((errors+1)); fi
    done
  fi
  printf '%-37s %-8s %-8s %-10s %-12s %-14s\n' "$name" "$compile" "$smoke" "$debug" "$build_ms" "$rss"
done
cd "$ROOT" || exit 2
# Additional starter programs: compile and link, do not execute targets that
# require KVM hardware or a guest libvirt daemon.
libvirt_count=0
if pkg-config --exists libvirt; then
  for dir in 07-gatech-6210-vm-coordinator 09-iitb-cs695-libvirt-pa2; do
    if "$COMPILER" $FLAGS $(pkg-config --cflags libvirt)        "$ROOT/$dir/src/libvirt_inventory.c"        $(pkg-config --libs libvirt) -o "$ROOT/$dir/build/inventory"; then
      echo "$dir libvirt_inventory LINK PASS"
      libvirt_count=$((libvirt_count+1))
    else
      echo "$dir libvirt_inventory LINK FAIL" >&2
      errors=$((errors+1))
    fi
  done
else
  echo 'libvirt-dev absent: two libvirt inventories NOT TESTED'
fi
printf 'RESULT folders_built=%d libvirt_linked=%d failures=%d\n' "$built" "$libvirt_count" "$errors"
if [ "$built" -ne 22 ]; then exit 1; fi
if [ "$errors" -ne 0 ]; then exit 1; fi
 .logic.check; then
          echo "$name: test exited 0 without all 20 PASS" >&2
          errors=$((errors+1))
        fi
      else
        if ! grep -Eq '^pass=[0-9]+ blank=[0-9]+ fail=[0-9]+
    for exe in build/*; do
      [ -f "$exe" ] && [ -x "$exe" ] || continue
      if ! readelf -S "$exe" | grep -q '.debug_info'; then debug='NO'; errors=$((errors+1)); fi
    done
  fi
  printf '%-37s %-8s %-8s %-10s %-12s %-14s\n' "$name" "$compile" "$smoke" "$debug" "$build_ms" "$rss"
done
cd "$ROOT" || exit 2
# Additional starter programs: compile and link, do not execute targets that
# require KVM hardware or a guest libvirt daemon.
libvirt_count=0
if pkg-config --exists libvirt; then
  for dir in 07-gatech-6210-vm-coordinator 09-iitb-cs695-libvirt-pa2; do
    if "$COMPILER" $FLAGS $(pkg-config --cflags libvirt)        "$ROOT/$dir/src/libvirt_inventory.c"        $(pkg-config --libs libvirt) -o "$ROOT/$dir/build/inventory"; then
      echo "$dir libvirt_inventory LINK PASS"
      libvirt_count=$((libvirt_count+1))
    else
      echo "$dir libvirt_inventory LINK FAIL" >&2
      errors=$((errors+1))
    fi
  done
else
  echo 'libvirt-dev absent: two libvirt inventories NOT TESTED'
fi
printf 'RESULT folders_built=%d libvirt_linked=%d failures=%d\n' "$built" "$libvirt_count" "$errors"
if [ "$built" -ne 22 ]; then exit 1; fi
if [ "$errors" -ne 0 ]; then exit 1; fi
 .logic.check; then
          echo "$name: check failed without expected per-case result" >&2
          errors=$((errors+1))
        fi
      fi
    fi
    debug='YES'
    for exe in build/*; do
      [ -f "$exe" ] && [ -x "$exe" ] || continue
      if ! readelf -S "$exe" | grep -q '.debug_info'; then debug='NO'; errors=$((errors+1)); fi
    done
  fi
  printf '%-37s %-8s %-8s %-10s %-12s %-14s\n' "$name" "$compile" "$smoke" "$debug" "$build_ms" "$rss"
done
cd "$ROOT" || exit 2
# Additional starter programs: compile and link, do not execute targets that
# require KVM hardware or a guest libvirt daemon.
libvirt_count=0
if pkg-config --exists libvirt; then
  for dir in 07-gatech-6210-vm-coordinator 09-iitb-cs695-libvirt-pa2; do
    if "$COMPILER" $FLAGS $(pkg-config --cflags libvirt)        "$ROOT/$dir/src/libvirt_inventory.c"        $(pkg-config --libs libvirt) -o "$ROOT/$dir/build/inventory"; then
      echo "$dir libvirt_inventory LINK PASS"
      libvirt_count=$((libvirt_count+1))
    else
      echo "$dir libvirt_inventory LINK FAIL" >&2
      errors=$((errors+1))
    fi
  done
else
  echo 'libvirt-dev absent: two libvirt inventories NOT TESTED'
fi
printf 'RESULT folders_built=%d libvirt_linked=%d failures=%d\n' "$built" "$libvirt_count" "$errors"
if [ "$built" -ne 22 ]; then exit 1; fi
if [ "$errors" -ne 0 ]; then exit 1; fi
