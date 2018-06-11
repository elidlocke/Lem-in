# libraries
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Colors
bg_color = '#111111'
line_color = '#666666'
default_node_color = '#0C6CFC'
se_node_color = '#0C6CFC'
occupied_node_color = '#FC9C0C'


#Input Data
input_turns = 6
input_nodes = ['START', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'END']
input_tunnels = [('START', 'A'),
                  ('A', 'B'),
                  ('B', 'END'),
                  ('START','C'),
                  ('C','D'),
                  ('D', 'END'),
                  ('START','E'),
                  ('E', 'F'),
                  ('F', 'G'),
                  ('G', 'H'),
                  ('H', 'I'),
                  ('I', 'J'),
                  ('I', 'K'),
                  ('J', 'K'),
                  ('K', 'L'),
                  ('L', 'END')]
input_turn_locations = [['START'],
               ['START', 'A', 'C'],
               ['START', 'A', 'C', 'B', 'D'],
               ['A', 'C', 'B', 'D', 'END'],
               ['B', 'D', 'END'],
               ['END']]

input_start_node = 'START'
input_end_node = 'END'

#Graph
G = nx.Graph()
G.add_nodes_from(input_nodes)
G.add_edges_from(input_tunnels)

#Custom Looks
node_sizes = len(input_nodes) * 50
se_node_sizes = node_sizes * 1.5
input_turn_locations.append([])

#Choose Node Positions
pos = nx.spring_layout(G)

#Build plot
fig = plt.figure()

def update(num):
   
    #Restart:
    fig.clear()
    print(num)

    # Default nodes & tunnels:
    tunnels = nx.draw_networkx_edges(G, pos, edge_color=line_color, width=2.0)
    nodes = nx.draw_networkx_nodes(G, pos, node_color=default_node_color, node_size=node_sizes)
    nodes.set_edgecolor(line_color)

    # Start and End nodes
    s_node = nx.draw_networkx_nodes(G, pos, nodelist=[input_start_node], node_color=se_node_color,
               node_size=se_node_sizes)
    s_node.set_edgecolor(line_color)
    e_node = nx.draw_networkx_nodes(G, pos, nodelist=[input_end_node], node_color=se_node_color,
               node_size=se_node_sizes)
    e_node.set_edgecolor(line_color)
    if input_start_node in input_turn_locations[num]:
        s_node.set_color(occupied_node_color) 
        s_node.set_edgecolor(line_color)
    if input_end_node in input_turn_locations[num]:
        e_node.set_color(occupied_node_color)
        e_node.set_edgecolor(line_color)
    room_names = nx.draw_networkx_labels(G, pos, font_size=8,
                                         font_family='sans-serif')
  
    # Highlight occupied nodes
    # TODO: Change this to select and change the color instead of redrawing !
    occupied_nodes = nx.draw_networkx_nodes(G, pos,
                                            nodelist=[node for node in input_turn_locations[num] \
                                                      if node != input_start_node and node \
                                                      != input_end_node],
                                            node_color=occupied_node_color, node_size=node_sizes)
    if occupied_nodes:
        occupied_nodes.set_edgecolor(line_color)
    
    #set the background color
    fig.set_facecolor(bg_color)
   
    # hide the silly axis
    plt.axis('off') 


if __name__ == "__main__":
    ani = FuncAnimation(fig, update, frames=input_turns + 1, interval=1000, repeat=True)
    plt.show()
