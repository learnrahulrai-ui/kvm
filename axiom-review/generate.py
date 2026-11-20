#!/usr/bin/env python3
"""Generate an exact source-line inventory. This is NOT a semantic proof."""
import hashlib
import json
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / "axiom-review"
BASE = "32198a0ade443b1b6c037a3a52fbc472abab801e"
NUMBERS = re.compile(r"0[xX][0-9a-fA-F]+|(?<![A-Za-z_])\d+(?:\.\d+)?")
WORDS = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")
PLAIN_TECHNICAL = set(
    "kernel page guest host scheduler lottery stride tickets fork pointer "
    "memory mapping cache reclaim refcount balloon migration source test data "
    "address proof qemu kvm numa cow ksm cpu vm pte gpa hpa api ioctl thp "
    "vfio gfp tlb filesystem syscall hypervisor entropy race deadlock "
    "livelock thread lock sharing copyonwrite hardware software process "
    "function variable state bytes value formula allocation probability "
    "reference return event device block disk timing scheduling fairness "
    "pagefault bitmap ring vmexit vmrun physical virtual".split()
)


def original_files():
    output = subprocess.check_output(
        ["git", "ls-tree", "-r", "-z", BASE], cwd=ROOT
    )
    rows = []
    for record in output.split(b"\0"):
        if not record:
            continue
        meta, name = record.split(b"\t", 1)
        mode, kind, sha = meta.decode("ascii").split()
        if kind != "blob":
            raise RuntimeError("unexpected git object type: " + kind)
        path = name.decode("utf-8")
        rows.append((path, mode, sha))
    return rows


def group_of(path):
    parts = path.split("/")
    if len(parts) == 1:
        return "_ROOT"
    if parts[0] == "assignments":
        if re.match(r"^\d\d-", parts[1]):
            return "/".join(parts[:2])
        return "assignments/_ROOT"
    if parts[0] == "bugs":
        if re.match(r"^\d\d-", parts[1]):
            return "/".join(parts[:2])
        return "bugs/_ROOT"
    if parts[0] == "research":
        return "/".join(parts[:2]) if len(parts) > 2 else "research/_ROOT"
    if parts[0] == "waldspurger-lab":
        return "waldspurger-lab"
    if parts[0] == ".github":
        return ".github"
    return parts[0] + "/_ROOT"


def git_blob_sha(data):
    prefix = b"blob " + str(len(data)).encode("ascii") + b"\0"
    return hashlib.sha1(prefix + data).hexdigest()


def code_like(path):
    return (
        Path(path).suffix in {".c", ".h", ".py", ".sh", ".yml", ".svg", ".html", ".bt"}
        or Path(path).name == "Makefile"
    )


def candidate_terms(path, text, seen):
    new = []
    for word in WORDS.findall(text):
        special = (
            code_like(path)
            or "_" in word
            or (word.isupper() and len(word) > 1)
            or word.lower() in PLAIN_TECHNICAL
        )
        if special and word not in seen:
            seen.add(word)
            new.append(word)
    return new


def inspect(path, mode, sha):
    source = ROOT / path
    data = source.read_bytes()
    actual = git_blob_sha(data)
    if actual != sha:
        raise RuntimeError(
            "SOURCE CHANGED: " + path + " expected " + sha + " actual " + actual
        )
    pre = [
        "FILE " + path,
        "GIT_BLOB " + sha,
        "MODE " + mode,
        "BYTES " + str(len(data)),
    ]
    if path.lower().endswith(".png"):
        pre += [
            "RESULT UNVERIFIED_IMAGE",
            "WHY: PNG is binary, not a sequence of source-code lines.",
            "WHY: Image pixels, captions, geometry and factual accuracy were not inspected.",
            "NEW THINGS INTRODUCED WITHOUT DERIVATION: image content unknown",
            "END_FILE",
            "",
        ]
        return pre, 0, 0, True
    try:
        content = data.decode("utf-8")
    except UnicodeDecodeError:
        pre += [
            "RESULT UNVERIFIED_BINARY: UTF-8 decoding failed.",
            "NEW THINGS INTRODUCED WITHOUT DERIVATION: binary content unknown",
            "END_FILE",
            "",
        ]
        return pre, 0, 0, True
    lines = content.split("\n")
    if lines[-1] == "":
        lines.pop()
    pre.append("SOURCE_LINES " + str(len(lines)))
    seen = set()
    all_terms = set()
    all_numbers = set()
    rejected = 0
    for number, line in enumerate(lines, 1):
        fresh = candidate_terms(path, line, seen)
        all_terms.update(fresh)
        nums = list(dict.fromkeys(NUMBERS.findall(line)))
        all_numbers.update(nums)
        if not line.strip():
            status = "NO_CLAIM"
            reason = "empty line"
        elif re.fullmatch(r"\s*[{};]+\s*", line):
            status = "STRUCTURE"
            reason = "punctuation only; prior declarations still need proof"
        else:
            status = "REJECTED"
            rejected += 1
            if number == 1:
                reason = "first line is not a proved axiom from counting"
            elif path.endswith(".svg"):
                reason = "no preceding-line derivation of SVG coordinates and geometry"
            elif code_like(path):
                reason = "no verified preceding-line derivation of code/API semantics"
            else:
                reason = "no verified preceding-line derivation of this assertion"
        pre.append(
            "L"
            + str(number).zfill(5)
            + " "
            + status
            + " TEXT="
            + json.dumps(line, ensure_ascii=True)
            + " FIRST_USE="
            + json.dumps(fresh)
            + " NUMBERS="
            + json.dumps(nums)
            + " GAP="
            + json.dumps(reason)
        )
    pre += [
        "RESULT REJECTED: line-level axiomatic proof not established; flagged="
        + str(rejected) + "/" + str(len(lines)),
        "NEW THINGS INTRODUCED WITHOUT DERIVATION: "
        + json.dumps(sorted(all_terms), ensure_ascii=True),
        "NUMBERS WITHOUT VERIFIED DERIVATION: "
        + json.dumps(sorted(all_numbers), ensure_ascii=True),
        "LIMIT: first-use names are lexical candidates, not a complete semantic analysis.",
        "END_FILE",
        "",
    ]
    return pre, len(lines), rejected, False


def generate():
    grouped = defaultdict(list)
    index = [
        "SOURCE_COMMIT " + BASE,
        "DEFINITION: a source file is the bytes in the frozen Git commit.",
        "DEFINITION: a source line ends at a newline byte.",
        "DEFINITION: REJECTED means this review has not proved the strict axiom rule.",
        "DEFINITION: NO_CLAIM is an empty line, not a passing proof.",
        "DEFINITION: UNVERIFIED_IMAGE means the PNG was not decoded or visually checked.",
        "LIMIT: lexical first-use checking cannot prove mathematical or kernel semantics.",
        "LIMIT: linked papers, bug reports, commits and external tests were not re-verified here.",
        "LIMIT: the audit files are output and excluded to prevent an infinite audit-of-audit chain.",
        "",
        "PATH | GIT_BLOB | TEXT_LINES | FLAGGED_LINES | STATUS | FOLDER",
    ]
    total_files = 0
    total_lines = 0
    total_flagged = 0
    total_binary = 0
    for path, mode, sha in original_files():
        group = group_of(path)
        report, lines, flagged, binary = inspect(path, mode, sha)
        grouped[group].extend(report)
        status = "UNVERIFIED_IMAGE" if binary else "REJECTED"
        index.append(
            " | ".join([path, sha, str(lines), str(flagged), status, group])
        )
        total_files += 1
        total_lines += lines
        total_flagged += flagged
        total_binary += int(binary)
    index += [
        "",
        "TOTAL_FILES " + str(total_files),
        "TOTAL_TEXT_FILES " + str(total_files - total_binary),
        "TOTAL_BINARY_FILES " + str(total_binary),
        "TOTAL_TEXT_LINES " + str(total_lines),
        "TOTAL_FLAGGED_LINES " + str(total_flagged),
        "NEW THINGS INTRODUCED WITHOUT DERIVATION: NONEMPTY in every substantive file.",
        "OVERALL RESULT REJECTED. This is a gap inventory, not an implementation fix.",
    ]
    result = {"axiom-review/INDEX.txt": "\n".join(index) + "\n"}
    for group, records in sorted(grouped.items()):
        header = [
            "SOURCE_COMMIT " + BASE,
            "FOLDER " + group,
            "AXIOM 1: 0 denotes no counted objects.",
            "AXIOM 2: 1 denotes one object added to 0.",
            "RULE: each new symbol needs an earlier definition.",
            "RULE: each numerical result needs an earlier calculation.",
            "RULE: a compiler result is not a proof of the subject matter.",
            "METHOD: each original source line is copied with its original line number.",
            "METHOD: FIRST_USE and NUMBERS identify candidates requiring proof.",
            "LIMIT: this is a conservative rejection, not a complete human semantic review.",
            "FOLDER_RESULT REJECTED",
            "",
        ]
        result["axiom-review/" + group + "/REVIEW.txt"] = (
            "\n".join(header + records) + "\n"
        )
    return result


def main():
    result = generate()
    check = "--check" in sys.argv[1:]
    bad = []
    for path, content in result.items():
        target = ROOT / path
        if check:
            if not target.exists() or target.read_text(encoding="utf-8") != content:
                bad.append(path)
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(content, encoding="utf-8")
    if bad:
        print("OUTDATED_AUDIT_FILES", len(bad))
        for path in bad[:20]:
            print(path)
        return 1
    print("AUDIT_FILES", len(result))
    print("SOURCE_FILES", len(original_files()))
    print("RESULT REJECTED: no mathematical or source proof claimed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
