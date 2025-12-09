#!/usr/bin/env python3
"""
Main Python Program Skeleton
"""
import math
import sys
from typing import List



def kmeans(data_points: List[List["float"]], k:int, iters: int = 400, eps: float = 0.001) -> list:
    
    # initialize centers as copies of first k points
    centers = [dp[:] for dp in data_points[:k]]

    for _ in range(iters):
        # assign points to nearest center
        clusters = {i: [] for i in range(k)}
        for point in data_points:
            min_idx = min(range(k), key=lambda i: math.dist(point, centers[i]))
            clusters[min_idx].append(point)

        # compute new centers, handle empty clusters by keeping old center
        new_centers = []
        for i in range(k):
            pts = clusters[i]
            if not pts:
                new_centers.append(centers[i][:])
            else:
                dim = len(centers[i])
                mean = [sum(p[d] for p in pts) / len(pts) for d in range(dim)]
                new_centers.append(mean)

        # check convergence (max movement)
        max_move = max(math.dist(a, b) for a, b in zip(centers, new_centers))
        centers = [c[:] for c in new_centers]
        if max_move < eps:
            return centers

    return centers
    
def main():
    """
    Main function - entry point of the program
    """

    
    data_points = []

    for line in sys.stdin:
        data_points.append([float(cr) for cr in line.split(",")])
        k = 0
    
    iters = 400
    if len(sys.argv) == 1:
        print("An Error Has Occurred")
        exit(1)
    if len(sys.argv) >= 2:
        k = int(sys.argv[1])
        if not(1<k<len(data_points)):
            print("Incorrect number of clusters!")
            exit(1)

    
    if len(sys.argv) == 3:
        iters = int(sys.argv[2])
        if not (1<iters<800):
            print("Incorrect maximum iteration!")
            exit(1)
    
    centroids = kmeans(data_points,k,iters)
    for center in centroids:
        for cr in center[:-1]:
            print(str(round(cr,4))+",",end="")
        print(str(round(center[-1],4)))

if __name__ == "__main__":
    main()
