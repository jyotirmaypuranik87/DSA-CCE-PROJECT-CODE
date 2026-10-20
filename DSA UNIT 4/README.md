## Develop a Leaderboard Application Using an AVL Tree

## Problem Statement

To develop a leaderboard application using an AVL tree in C++ that inserts scores, displays the search path, identifies the first unbalanced node, performs suitable rotations, and displays the final leaderboard in descending order.

## Project Description

The Leaderboard Application Using an AVL Tree is a C++-based application designed to manage and rank scores efficiently using a self-balancing Binary Search Tree (AVL Tree). The application accepts multiple scores from the user and inserts them into the AVL tree while maintaining its balance.

Whenever a new score is entered, the program displays the search path followed to find its correct insertion position. After insertion, it calculates the height and balance factor of the nodes to detect any imbalance in the tree. If an imbalance occurs, the program identifies the first unbalanced node and applies the appropriate rotation, such as LL, RR, LR, or RL, to restore the tree's balance.

The application displays the leaderboard in descending order, with the highest score first. It also prevents duplicate scores and generates a final leaderboard showing each score along with its rank. This makes the application useful for understanding how scores can be organized and ranked using tree-based data structures.

The project demonstrates important data structure concepts, including AVL tree insertion, recursion, height calculation, balance factor calculation, tree rotations, and in-order traversal. It also helps students understand how self-balancing trees maintain efficient searching and insertion operations.

## Objectives

1. To implement an AVL tree using C++.
2. To insert scores while maintaining the balance of the tree.
3. To display the search path for each score insertion.
4. To identify the first unbalanced node.
5. To apply LL, RR, LR, and RL rotations when required.
6. To display scores in descending order.
7. To generate a final leaderboard with ranks.
8. To prevent duplicate score entries.

## Main Features

- Dynamic score insertion.
- Search path display.
- Automatic imbalance detection.
- AVL tree rotations.
- Duplicate score prevention.
- Highest-to-lowest leaderboard display.
- Final ranking table.

## Applications

- Online gaming competitions.
- Student marks and ranking systems.
- Sports tournaments.
- Coding competitions.
- Player performance tracking.

## Conclusion

The project provides an effective way to manage and rank scores using an AVL tree. It maintains tree balance through rotations, displays the insertion search path, and generates a leaderboard in descending order. The project helps develop practical knowledge of self-balancing binary search trees and their applications in score management and ranking systems.