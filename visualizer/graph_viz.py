import argparse
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx
import os

from ant import Ant
from matplotlib.animation import FuncAnimation
from read_input import parse

# Colors
bg_color = '#111111'
line_color = '#282828'
text_color = '#EEEEEE'
default_node_color = '#282828'
ant_colors = ['#b61515', '#B66615', '#B6B615', '#66B615', '#15B615', '#15B666',
              '#15B6B6', '#1515B6', '#6615B6', '#B615B6', '#B61566']


def highlight_node(node, highlight_color):
    node.set_color(highlight_color)
    node.set_edgecolor(line_color)


def draw_node(node_name, node_color, node_size, line_color):
    node_list = []
    node_list.append(node_name)
    node = nx.draw_networkx_nodes(
        G,
        pos,
        nodelist=node_list,
        node_color=node_color,
        node_size=node_size)
    node.set_edgecolor(line_color)
    return (node)


def draw_nodes(anthill_data, node_color, node_size, line_color):
    nodes = {}
    for name in anthill_data['nodes']:
        if name == anthill_data['start'] or name == anthill_data['end']:
            node = draw_node(name, node_color, node_size * 2.5, line_color)
        else:
            node = draw_node(name, node_color, node_size, line_color)
        nodes[name] = node
    return (nodes)


def draw_ant(position, color):
    ant = plt.plot([position[0]], [position[1]],
                   color=color, marker='.', markersize=20.0)
    return (ant)


def update(num, G, pos, num_steps, anthill_data, ants):

    fig.clear()
    node_size = 500

    # default nodes & tunnels:
    tunnels = nx.draw_networkx_edges(G, pos, edge_color=line_color, width=2.0)
    nodes = draw_nodes(anthill_data, default_node_color,
                       node_size, line_color)

    # draw all the ants:
    for ant in ants:
        if num < len(ant.journey):
            draw_ant(ant.journey[num], ant.color)
    # labels
    room_names = nx.draw_networkx_labels(G,
                                         pos,
                                         font_size=8,
                                         labels=dict([(anthill_data['start'],
                                                       'START'),
                                                      (anthill_data['end'],
                                                       'END')]),
                                         font_family='sans-serif',
                                         font_color=text_color)

    # set the background color
    fig.set_facecolor(bg_color)

    # hide the axis
    plt.axis('off')


def make_ants(G, pos, num_steps, anthill_data):
    ants = []
    for ant_num in range(1, int(anthill_data['ants']) + 1):
        ant = Ant(ant_num)
        ant.set_node_path(anthill_data)
        ant.set_location(pos, anthill_data)
        ant.set_journey(pos, num_steps, anthill_data)
        ant.color = ant_colors[ant_num % 11]
        ants.append(ant)
    return (ants)


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

    anthill_data = parse(args.map, args.solution)

    # Graph
    G = nx.Graph()
    G.add_nodes_from(anthill_data['nodes'])
    G.add_edges_from(anthill_data['tunnels'])
    pos = nx.spring_layout(G)

    # Set how fast the ants travel
    num_steps = 10
    ants = make_ants(G, pos, num_steps, anthill_data)

    # Build plot
    fig = plt.figure()

    # Animate
    ani = FuncAnimation(
        fig,
        update,
        frames=anthill_data['num_turns'] *
        num_steps,
        fargs=(
            G,
            pos,
            num_steps,
            anthill_data,
            ants),
        interval=350,
        repeat=True)
    # Open display window
    plt.show()
