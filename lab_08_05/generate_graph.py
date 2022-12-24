import random as r
import sys

file = open("graph.txt", "w")

num_verteces = int(sys.argv[1])

file.write(str(num_verteces))

step = 1

total_edges = list()

for cur_vertex in range(num_verteces):

    for j in range(2):
        next_vertex = cur_vertex + step

        if (next_vertex < num_verteces):
            total_edges.append((cur_vertex, next_vertex))
            file.write("\n" + str(cur_vertex) + " " + str(next_vertex))
        else:
            break

        step += 1

    step -= 1

if (3 <= num_verteces <= 7):
    cur_vertex = num_verteces // 2

    for i in range(1, num_verteces):
        if ((cur_vertex, i) not in total_edges and (i, cur_vertex) not in total_edges and i != cur_vertex):
            total_edges.append((cur_vertex, i))
            file.write("\n" + str(cur_vertex) + " " + str(i))
elif (num_verteces > 7):
    cur_vertex = r.randint(0, num_verteces - 1)

    num_edges = r.randint(0, 5)

    i = 0
    while (i <= num_edges):
        next_vertex = r.randint(0, num_verteces - 1)

        if (next_vertex != cur_vertex and (cur_vertex, next_vertex) not in total_edges and (next_vertex, cur_vertex) not in total_edges):
            total_edges.append((cur_vertex, next_vertex))
            file.write("\n" + str(cur_vertex) + " " + str(next_vertex))

            i += 1

file.close()