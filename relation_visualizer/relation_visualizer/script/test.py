#!/usr/bin/python3
# -*- coding: utf-8 -*-

import networkx as nx
import plotly.graph_objects as go
import numpy
import glob
import re
import os
import plotly

dir = "./data"
extention = "*.txt"


def graph():

    G = nx.Graph()
    node_name = []
    custom_data = []

    path = dir + "/"
    files = glob.glob(path + extention)
    for file in files:
        f = open(file, 'r')
        # ファイル名でnodeを追加
        ## 拡張子等を抜いたファイル名だけ抜き出す
        basename_without_ext = os.path.splitext(os.path.basename(file))[0]
        # print(basename_without_ext)
        G.add_node(basename_without_ext)
        node_name.append(basename_without_ext)
        custom_data.append(file)
        flist = f.readlines()
        for line in flist:
            new_str = re.search(r'test (.+).txt',line).group(1)
            # print(new_str)
            G.add_edge(basename_without_ext,new_str)

    pos = nx.spring_layout(G, k=0.3, seed=1)
    for node in G.nodes():
        G.nodes[node]["pos"] = pos[node]

    #  tmp
    G.nodes["aaa"]["node_info"] = {
        "name": "node-1",
        "id": 1,
        "description": "This is the test node 1",
    }
    G.nodes["bbb"]["node_info"] = {
        "name": "node-2",
        "id": 2,
        "description": "This is the test node 2",
    }
    G.nodes["ccc"]["node_info"] = {
        "name": "node-3",
        "id": 3,
        "description": "This is the test node 3",
    }
    #

    node_x = []
    node_y = []
    node_info = []
    for n in G.nodes():
        x, y = G.nodes[n]["pos"]
        node_x.append(x)
        node_y.append(y)
        node_info.append(G.nodes[n]["node_info"])
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
        mode="markers+text",
        customdata=custom_data,
        textposition='top center',
        texttemplate=node_name,
        textfont=dict(size=15),
        marker=dict(size=40, line=dict(width=2)),
    )
    edges = go.Scatter(
        x=edge_x,
        y=edge_y,
        mode="lines",
        line=dict(width=2),
    )
    fig = go.Figure(
        data=[edges, nodes],
        layout=go.Layout(
            showlegend=False,
            xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            plot_bgcolor="rgba(0,0,0,0)",
            paper_bgcolor="rgba(0,0,0,0)",
            clickmode="select+event",
        ),
    )

    # Load JavaScript
    with open("./script/plotly_click.js") as f:
        plotly_click_js = f.read()

    # Create <div> element
    plot_div = plotly.io.to_html(
        fig,
        include_plotlyjs=True,
        post_script=plotly_click_js,
        full_html=False,
    )

    # Build HTML
    html_str = """
    <html>
    <head>
    </head>
    <body>
    <div id="plotly-node-info">
    <p>**Node Information**</p>
    </div>
    {plot_div}
    </body>
    </html>
    """.format(
        plot_div=plot_div
    )

    # Write out HTML file
    with open("./file.html", "w") as f:
        f.write(html_str)

    # fig.write_html("./file.html", auto_open=True)

if __name__ == '__main__':
    graph()