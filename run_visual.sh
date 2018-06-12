#!/bin/bash
map_file_path=$1
[ $# -eq 0 ] && { echo "Usage: $0 map"; exit 1; }

./lemin < $map_file_path | python3 visualizer/graph_viz.py $map_file_path
