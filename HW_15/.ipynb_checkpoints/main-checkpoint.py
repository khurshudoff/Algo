import random as rd
import numpy as np

from MST import find_MST
from optimal import find_optimal
from find_way import return_way

def create_point():
    return (rd.random() * 10, rd.random() * 10)

def dist(e1, e2):
    e1 = np.array(e1)
    e2 = np.array(e2)
    return np.sqrt(np.sum((e1-e2) ** 2))

def experiments(_range, n_iter):
    res = []
    
    for N in _range:
        arr = []
        for it in range(n_iter):

            points = np.array([create_point() for _ in range(N)])    
            edges = []
            for idx1, e1 in enumerate(points):
                for idx2, e2 in enumerate(points):
                    if idx1 == idx2:
                        continue
                    edges.append((dist(e1, e2), idx1, idx2))

            arr.append((find_optimal(N, edges)[0], return_way(N, find_MST(N, len(edges), edges))[0]))

        _opt = np.array(arr).T[0]
        _mst = np.array(arr).T[1]

        res.append((N, np.mean(_mst - _opt), np.std(_mst - _opt)))
        
    return res

for N, mean, std in experiments(range(2,11), 10):
    print('N = {0:2d}: mean = {1:6.3f}, std={2:.3f}'.format(N, mean, std))