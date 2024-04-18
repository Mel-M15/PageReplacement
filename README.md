# PageReplacement README
Please run this PageReplacement project in C++.

# Overview
This C++ program implements different page replacement algorithms in order to analyze their performance concerning the number of page faults.

# Functionality
The page replacement algorithm has the following functionality:
1. LRU (Least Recently Used) Page Replacement Algorithm: discards the least recently used pages from the memory when the system needs to bring in new pages.
2. Optimal Page Replacement Algorithm: finds which page will not be used for the longest amount of time and replaces that page when the system needs memory for a new page.
3. FIFO (First in first out) Page Replacement Algorithm: discards the oldest pages in memory when a new page needs to be brought into memory. There is a queue of pages and when a new page needs to be brought into memory, the page that was the first to be brought into memory will be removed from memory.
4. The total number of page faults that occur for each algorithm will be calculated.
5. In addition, the program will calculate the number of page faults that occur at each step during the execution of the program.

# Instructions for Execution
1. Run this program in C++.
2. There is no user input to be entered to run the program.
3. Run the program and verify that LRU, Optimal, and FIFO algorithms calculate the total number of page faults that occur. For each of the three algorithms, the program will output the number of page faults that occur during each step of the simulation. 
