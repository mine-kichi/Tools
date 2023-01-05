#!/usr/bin/python3
# -*- coding: utf-8 -*-

import networkx as nx
import plotly.graph_objects as go
import numpy

def graph():

    G = nx.Graph()

    G.add_node(1)
    G.add_node(2)
    G.add_node(3)
    G.add_node(4)
    G.add_node(5)
    G.add_edge(1, 2)
    G.add_edge(2, 3)
    G.add_edge(1, 3)
    G.add_edge(1, 4)
    G.add_edge(1, 5)

    pos = nx.spring_layout(G, k=0.3, seed=1)

    for node in G.nodes():
        G.nodes[node]["pos"] = pos[node]

    node_x = []
    node_y = []
    for n in G.nodes():
        x, y = G.nodes[n]["pos"]
        node_x.append(x)
        node_y.append(y)

    edge_x = []
    edge_y = []
    for e in G.edges():
        x0, y0 = G.nodes[e[0]]["pos"]
        x1, y1 = G.nodes[e[1]]["pos"]
        edge_x.append(x0)
        edge_y.append(y0)
        edge_x.append(x1)
        edge_y.append(y1)
        edge_x.append(None)
        edge_y.append(None)


    nodes = go.Scatter(
        x=node_x,
        y=node_y,
        mode="markers",
        marker=dict(size=40, line=dict(width=2)),
    )
    edges = go.Scatter(
        x=edge_x,
        y=edge_y,
        mode="lines",
        line=dict(width=2),
    )

    fig = go.Figure(data=[edges, nodes])
    fig.write_html("./file.html", auto_open=True)

if __name__ == '__main__':
    graph()