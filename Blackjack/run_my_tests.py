#! /usr/bin/env python

import os
import subprocess

from fnmatch import fnmatch

player_test_exe_pattern = 'Player_test[0-9][0-9]'
deck_test_exe_pattern = 'Deck_test[0-9][0-9]'

test_exes = [
    filename for filename in os.listdir('.')
    if (fnmatch(filename, player_test_exe_pattern) or
        fnmatch(filename, deck_test_exe_pattern))]

num_tests_run = 0
num_tests_passed = 0

for test in test_exes:
    return_code = subprocess.call(['./' + test])
    num_tests_run += 1
    if return_code == 0:
        num_tests_passed += 1

print '''Out of {0} tests run:
{1} tests passed,
{2} tests failed.
'''.format(num_tests_run, num_tests_passed, num_tests_run - num_tests_passed)
