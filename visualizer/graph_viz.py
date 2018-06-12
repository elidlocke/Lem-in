# libraries
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import os
from matplotlib.animation import FuncAnimation
import argparse
from read_input import parse

# Colors
bg_color = '#111111'
line_color = '#282828'
default_node_color = '#0C6CFC'
se_node_color = '#0C6CFC'
highlight_color = '#FC9C0C'
# v modify to be 50% of highlight on white and back bg
odd_ant_color = "#8E590A"
even_ant_color = '#FDBA55'

def highlight_node(node, highlight_color):
    node.set_color(highlight_color) 
    node.set_edgecolor(line_color)

def draw_node(node_name, node_color, node_size, line_color):
    node_list = []
    node_list.append(node_name)
    node = nx.draw_networkx_nodes(G, pos, nodelist=node_list, node_color=node_color,
               node_size=node_size)
    node.set_edgecolor(line_color)
    return (node)

def draw_nodes(node_names, node_color, node_size, line_color):
    nodes = {}
    for name in node_names:
        node = draw_node(name, node_color, node_size, line_color)
        nodes[name] = node
    return (nodes)

def get_odd_ants(anthill_data):
    odd_ants = []
    all_ants = []
    for turn in range(0,anthill_data['num_turns']):
        for ant_move in anthill_data['turns'][turn]:
            if ant_move[1] != anthill_data['start'] and \
               ant_move[0] not in all_ants:
                if turn % 2 == 1:
                    odd_ants.append(ant_move[0])
                all_ants.append(ant_move[0])
    return (odd_ants)

def update(num, random_int, anthill_data):
   
    #Restart:
    fig.clear()
    odd_ants = get_odd_ants(anthill_data)
    print(num)
    #print(anthill_data)

    # default nodes & tunnels:
    tunnels = nx.draw_networkx_edges(G, pos, edge_color=line_color, width=2.0)
    nodes = draw_nodes(anthill_data['nodes'], default_node_color,
                       node_sizes, line_color)

    # start and end nodes
    s_node = draw_node(anthill_data['start'], se_node_color,
                       se_node_sizes, line_color)
    e_node = draw_node(anthill_data['end'], se_node_color,
                       se_node_sizes, line_color)
    
    # highlight occupied nodes
    if num < anthill_data['num_turns']:
        current_node_names = [x[1] for x in anthill_data['turns'][num]]
        if anthill_data['start'] in current_node_names:
            highlight_node(s_node, highlight_color)
        if anthill_data['end'] in current_node_names:
            highlight_node(e_node, highlight_color)
        for move in anthill_data['turns'][num]:
            if move[0] in odd_ants: 
                highlight_node(nodes[move[1]], odd_ant_color)
            else:
                highlight_node(nodes[move[1]], even_ant_color)

    #labels
    room_names = nx.draw_networkx_labels(G, pos, font_size=8,
        labels=dict([(anthill_data['start'], 'START'),
                     (anthill_data['end'], 'END')]),
        font_family='sans-serif')
  
    #set the background color
    fig.set_facecolor(bg_color)
   
    # hide the silly axis
    plt.axis('off') 


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

    #Get data
    anthill_data = parse(args.map, args.solution)
    
    #Graph
    G = nx.Graph()
    G.add_nodes_from(anthill_data['nodes'])
    G.add_edges_from(anthill_data['tunnels'])

    #Custom Looks
    node_sizes = len(anthill_data['nodes']) * 50
    se_node_sizes = node_sizes * 1.5

    #Choose Node Positions
    pos = nx.spring_layout(G)

    #Build plot
    fig = plt.figure()
    
    #Animate :D
    #should delete this random int but why cant i pass just the dict into the
    #fargs? It keeps getting unpacked into 7 items :(
    random_int = 5
    ani = FuncAnimation(fig, update, frames=anthill_data['num_turns'] + 1,
                        fargs=(random_int, anthill_data),
                        interval=1000, repeat=True)
    #Open Display Window
    plt.show()
