#!/usr/bin/python

import re, string, sys

for line in sys.stdin:
	po = re.search( r'Po ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) (.*)', line, re.M|re.I )
	if po and po.group(2) == po.group(4) and po.group(3) == po.group(5) and po.group(6) == sys.argv[1]:
		print("Po", po.group(1), po.group(2), po.group(3), po.group(4), po.group(5), sys.argv[2], po.group(7), " # patched")
	else:
		sys.stdout.write(line)
