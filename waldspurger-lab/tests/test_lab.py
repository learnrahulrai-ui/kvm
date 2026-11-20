import os
import re
import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
def run(*args):
    return subprocess.run([str(ROOT / "build" / args[0]), *args[1:]],
                          cwd=ROOT, text=True, capture_output=True, check=True).stdout

class PaperBaselines(unittest.TestCase):
    def test_idle_memory_tax_from_paper_equation(self):
        out = run("idle_tax", "100", "100", "0.25", "50", "50", "0.75", "0.75")
        self.assertIn("idle_cost=4.000000000", out)
        self.assertIn("lower_score=A", out)
        self.assertRegex(out, r"A .*score=0\.3076923")
        self.assertRegex(out, r"B .*score=0\.5714285")

    def test_stride_six_grants(self):
        out = run("scheduler", "stride", "6", "100", "50")
        self.assertIn("A=4 B=2", out)

    def test_lottery_counts_no_claim_of_exact_ratio(self):
        out = run("scheduler", "lottery", "6000", "100", "50")
        match = re.search(r"A=(\d+) B=(\d+)", out)
        self.assertIsNotNone(match)
        self.assertEqual(sum(map(int, match.groups())), 6000)

    def test_exact_lru_curve_small_trace(self):
        out = run("mrc", "traces/six-blocks.txt", "1000")
        self.assertIn("scanned=6 selected=6 unique_selected=3", out)
        self.assertIn("1,0,6,1.000000000", out)
        self.assertIn("2,1,5,0.833333333", out)
        self.assertIn("3,3,3,0.500000000", out)

    def test_ksm_demo_no_host_change(self):
        out = run("ksm_demo", "1", "0", "0")
        self.assertIn("pages=", out)
        self.assertIn("merge=0", out)
        self.assertIn("page_bytes=", out)

    def test_bad_tax_rejected(self):
        p = subprocess.run([str(ROOT / "build/idle_tax"), "1", "1", "0.1",
                            "1", "1", "0.2", "1"], capture_output=True)
        self.assertNotEqual(p.returncode, 0)

if __name__ == "__main__":
    unittest.main()
