import timeit
from search import *
import numpy as np
import warnings
warnings.filterwarnings("ignore")
from PIL import Image
import matplotlib.pyplot as plt

def plot_NQueens(solution):
    n = len(solution)
    board = np.array([2 * int((i + j) % 2) for j in range(n) for i in range(n)]).reshape((n, n))
    im = Image.open('/Users/amadev/Desktop/workflow/Repos/software-engineering/AI/8-queens/queen_s.png')
    height = im.size[1]
    im = np.array(im).astype(np.float) / 255
    fig = plt.figure(figsize=(7, 7))
    ax = fig.add_subplot(111)
    ax.set_title('{} Queens'.format(n))
    plt.imshow(board, cmap='binary', interpolation='nearest')
    # NQueensCSP gives a solution as a dictionary
    if isinstance(solution, dict):
        for (k, v) in solution.items():
            newax = fig.add_axes([0.064 + (k * 0.112), 0.062 + ((7 - v) * 0.112), 0.1, 0.1], zorder=1)
            newax.imshow(im)
            newax.axis('off')
    # NQueensProblem gives a solution as a list
    elif isinstance(solution, list):
        for (k, v) in enumerate(solution):
            newax = fig.add_axes([0.064 + (k * 0.112), 0.062 + ((7 - v) * 0.112), 0.1, 0.1], zorder=1)
            newax.imshow(im)
            newax.axis('off')
    fig.tight_layout()
    plt.show()


nqp = NQueensProblem(8)

#breadth_first_tree_search(nqp)

def func(nqp):
    #breadth_first_tree_search(nqp)
    bfts = depth_limited_search(nqp, 5000).solution()
    # bfts = breadth_first_tree_search(nqp).solution()
    # print(depth_limited_search(nqp))
    # plot_NQueens(bfts)

print('breadth_first_tree_search:', timeit.timeit('[func(nqp)]', globals=globals(), number=500))

nqp = NQueensProblem(8)

# def func(nqp):
#     astar = recursive_best_first_search(nqp).solution()

# print('astar_search:', timeit.timeit('[func(nqp)]', globals=globals(), number=500))

# nqp = NQueensProblem(8)

# astar = recursive_best_first_search(nqp).solution()

# plot_NQueens(astar)
