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
text_color = '#EEEEEE'
default_node_color = '#282828'
se_node_color = '#AAAAAA'
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

def draw_nodes(anthill_data, node_color, node_size, line_color):
    nodes = {}
    for name in anthill_data['nodes']:
        if name == anthill_data['start'] or name == anthill_data['end']:
            node = draw_node(name, node_color, node_size * 2.5, line_color)
        else:
            node = draw_node(name, node_color, node_size, line_color)
        nodes[name] = node
    return (nodes)

'''
def draw_ant(pos, anthill_data, x_pos, y_pos):
    ants = []
    for ant in anthill_data['ants']:
        ants.append(plt.plot([pos['start'][0]],
                           [pos['start'][1]],
                           'g.',
                           markersize=20.0))
    return (ants)
'''
def draw_ant(ant_number, position, color):
    ant = plt.plot([position[0]], [position[1]], color, markersize=20.0)
    return (ant)

def get_ant_points(ant_number, start_pos, end_pos):
    x = np.linspace(start_pos[0], end_pos[0], num=10)
    y = np.linspace(start_pos[1], end_pos[1], num=10)
    journey = zip(x, y)
    return (journey)

def update(num, G, pos, anthill_data):
   
    #Restart:
    fig.clear()
    print(num)
    print("pos" + str(pos))
    #print(anthill_data)
    
    #Custom Looks
    node_size = 500

    # default nodes & tunnels:
    tunnels = nx.draw_networkx_edges(G, pos, edge_color=line_color, width=2.0)
    nodes = draw_nodes(anthill_data, default_node_color,
                       node_size, line_color)

    #draw all the ants at the start:
    # TODO: room1 is hard coded, whooops
    ant_number = 1
    journey = get_ant_points(ant_number, pos['start'], pos['room1'])
    for location in journey:
        draw_ant(ant_number, location, 'g.')

    #labels
    room_names = nx.draw_networkx_labels(G, pos, font_size=8,
        labels=dict([(anthill_data['start'], 'START'),
                     (anthill_data['end'], 'END')]),
        font_family='sans-serif', font_color=text_color)
  
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


    #Choose Node Positions
    pos = nx.spring_layout(G)

    #Build plot
    fig = plt.figure()

    #Animate
    ani = FuncAnimation(fig, update, frames=anthill_data['num_turns'] + 1,
                        fargs=(G, pos, anthill_data),
                        interval=1000, repeat=True)
    #Open Display Window
    plt.show()
