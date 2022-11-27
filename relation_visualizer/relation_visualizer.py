#!/usr/bin/python3
# -*- coding: utf-8 -*-

# import graphviz
from graphviz import Graph
from graphviz import Digraph
import glob
import re

dir = "./data"
extention = "*.txt"

def graph():
    g = Graph(format='png')
    dg = Digraph(format='png')

    path = dir + "/"
    print(path + extention)
    files = glob.glob(path + extention)
    for file in files:
        f = open(file, 'r')
        # ファイル名でnodeを追加
        # # nodeを追加
        # g.node('1')
        # lines = f.readline()
        flist = f.readlines()
        # print(flist)
        # for line in lines:
        #     print(line)
        for line in flist:
            new_str = re.search(r'test (.+).txt',line).group(1)
            print(new_str)
            # ノードを追加
            # g.node('2')
            # g.node('3')
            # # edgeを追加
            # g.edge('1', '2')
            # g.edge('2', '3')
            # g.edge('3', '1')


    # # 有向グラフ
    # dg.node('1')
    # dg.node('2')
    # dg.node('3')
    # dg.edge('1', '2')  # 1 -> 2
    # dg.edge('2', '3')  # 2 -> 3
    # dg.edge('3', '1')  # 3 -> 1

    # g.view()
    # # g.render('./graph', view=True)
    # # dg.render('./dgraph', view=True)

if __name__ == '__main__':
    graph()