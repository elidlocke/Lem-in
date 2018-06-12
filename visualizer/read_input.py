import argparse
import os
import re
import sys

from pprint import pprint


def parse_map(cfg, map_path):
    patterns = {
        'tunnels': re.compile(r'^([\d\w]+)-([\d\w]+)\n$'),
        'nodes': re.compile(r'^([\d\w]+) \d+ \d+\n$'),
        'start': re.compile(r'^##start\n$'),
        'end': re.compile(r'^##end\n$'),
        'ants': re.compile(r'^(\d+)\n$')
    }

    with open(map_path, 'r') as f:
        for line in f:
            for pattern, case in patterns.items():
                for match in case.findall(line):
                    if pattern in ['start', 'end']:
                        node = next(f)
                        while node.startswith("#"):
                            node = next(f)
                        match = patterns['nodes'].search(node)
                        cfg[pattern] = match.groups(1)[0]
                        cfg['nodes'].append(match.groups()[0])
                    elif pattern is 'ants':
                        cfg[pattern] = match
                    else:
                        cfg[pattern].append(match)

    return cfg


def parse_sol(cfg, sol_path):
    re_turns = re.compile(r'L([\d\w]+)-([\d\w]+)')

    if not sol_path:
        iterator = sys.stdin.read().splitlines()
    else:
        with open(sol_path, 'r') as f:
            iterator = f.readlines()

    for line in iterator:
        entry = re_turns.findall(line)
        if entry:
            cfg['num_turns'] += 1
            cfg['turns'].append(entry)

    if not cfg['num_turns']:
        return None
    return cfg


def parse(map_path, sol_path=None):
    cfg = {
        'tunnels': [],
        'nodes': [],
        'turns': [],
        'start': None,
        'end': None,
        'ants': None,
        'num_turns': 0,
    }
    return parse_sol(parse_map(cfg, map_path), sol_path)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("map", help="Path to map file", type=str)
    parser.add_argument("-s", "--solution",
                        help="File path to solution", type=str)
    args = parser.parse_args()

    if not os.path.exists(args.map):
        raise IOError("Map file not found")

    if args.solution and not os.path.exists(args.solution):
        raise IOError("Solution file not found")

    pprint(parse(args.map, args.solution))
