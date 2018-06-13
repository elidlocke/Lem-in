# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ant.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enennige <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 13:52:11 by enennige          #+#    #+#              #
#    Updated: 2018/06/12 19:57:40 by enennige         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import numpy as np

class   Ant:

    def __init__(self, number, node_path=None,
                 journey=None, color='g.'):
        self.number = number
        self.node_path = node_path
        self.journey = journey
        self.color = color


    def set_node_path(self, anthill_data):
        self.node_path = []
        started = False
        self.node_path.append(anthill_data['start'])
        for turn in anthill_data['turns']:
            for move in turn:
                if move[0] == str(self.number):
                    self.node_path.append(move[1])
                    started = True
            if started == False:
                self.node_path.append(anthill_data['start'])

    def set_location(self, pos, anthill_data):
        location = pos[anthill_data['start']]
        self.current_location = location

    def set_journey(self, pos, num_steps, anthill_data):
        location_list = []
        for i in range(len(self.node_path)):
            if i != 0:
                start_pos = pos[self.node_path[i - 1]]
                end_pos = pos[self.node_path[i]]
                x = np.linspace(start_pos[0], end_pos[0], num=num_steps)
                y = np.linspace(start_pos[1], end_pos[1], num=num_steps)
                location_list.extend(list(zip(x, y)))
            i += 1
        self.journey = location_list


