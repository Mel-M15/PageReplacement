#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

// LRU Page Replacement Algorithm
void LRU(int pages[], int n, int capacity) {
    // Set to keep track of pages currently in memory
    unordered_set<int> s;
    // store the index of pages
    queue<int> indexes;
    // Counts the page faults
    int page_faults = 0;

    // Loop through each page in the array
    for (int i = 0; i < n; i++) {
        // There is space in memory
        if (s.size() < capacity) {
            if (s.find(pages[i]) == s.end()) {
                s.insert(pages[i]);
                indexes.push(pages[i]);
                page_faults++;
            }
            else {
                indexes.push(pages[i]);
            }
        }
        else {
            // There is not enough space in memory
            if (s.find(pages[i]) == s.end()) {
                int least_recently_used = indexes.front();
                indexes.pop();
                s.erase(least_recently_used);

                s.insert(pages[i]);
                indexes.push(pages[i]);
                page_faults++;
            }
            else {
                indexes.push(pages[i]);
            }
        }

        // Prints the required information through each step of simulation
        cout << "Step " << i + 1 << ": Page fault (" << pages[i] << ") - Page Table: {";
        for (auto it = s.begin(); it != s.end(); ++it) {
            cout << *it;
            if (next(it) != s.end()) cout << ", ";
        }
        cout << "}, Frames: [";
        queue<int> temp = indexes;
        while (!temp.empty()) {
            cout << temp.front();
            temp.pop();
            if (!temp.empty()) cout << ", ";
        }
        cout << "], Faults: " << page_faults << endl;
    }

    cout << "Total Page Faults: " << page_faults << endl;
}

// Predicts which page to replace
int predictPage(int page[], vector<int>& frames, int pageNumber, int pageIndex)
{
    int result = -1, farthestPage = pageIndex;
    // Loops through the frames to predict which page will not be used for the most amount of time
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = pageIndex; j < pageNumber; j++)
        {
            if (frames[i] == page[j])
            {
                if (j > farthestPage)
                {
                    farthestPage = j;
                    result = i;
                }
                break;
            }
        }

        if (j == pageNumber)
            return i;
    }

    if (result == -1)
        return 0;
    else
        return result;
}

// Searches if a page is present in the frames
bool searchPage(int key, vector<int>& frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        // if the frame is found, return true
        if (frames[i] == key)
            return true;
    }

    return false;
}

// Optimal Page Replacement Algorithm
void find(int page[], int pageNumber, int frameNumber)
{
    // Stores the frames
    vector<int> frames;
    // Counts the page faults
    int hit = 0;
    // Counts what the current step is
    int step = 1;

    // Loops through each page
    for (int i = 0; i < pageNumber; i++)
    {
        // Page is already present
        if (searchPage(page[i], frames))
        {
            hit++;
            continue;
        }

        // There is enough space to add the page
        if (frames.size() < frameNumber)
        {
            frames.push_back(page[i]);
        }
        else
        {
            // frame is full
            int j = predictPage(page, frames, pageNumber, i + 1);
            frames[j] = page[i];
        }

        // Prints the required information through each step of simulation
        cout << "Step " << step << ": Page fault (" << page[i] << ") - Page Table: {";
        for (int k = 0; k < frames.size(); k++) {
            if (k > 0) cout << ", ";
            cout << frames[k];
        }
        cout << "}, Frames: [";
        for (int k = 0; k < frames.size(); k++) {
            if (k > 0) cout << ", ";
            cout << frames[k];
        }
        cout << "], Faults: " << i + 1 << endl;
        step++;
    }
    cout << "Total Page Faults: " << pageNumber - hit << endl;
}

// FIFO Page Replacement Algorithm
int fifo(int pages[], int n, int capacity) {
    // Queue to store the pages
    queue<int> pageQueue; 
    // Set to keep track of pages currently in memory
    unordered_set<int> pageSet;
    int PF = 0; // Counts the page faults

    // Loop through each page in the array
    for (int i = 0; i < n; i++) {
        // There is space in memory
        if (pageSet.size() < capacity) {
            if (pageSet.find(pages[i]) == pageSet.end()) {
                pageSet.insert(pages[i]);
                PF++;
                pageQueue.push(pages[i]);
            }
        }
        else {
            // There is not enough space in memory
            if (pageSet.find(pages[i]) == pageSet.end()) {
                int val = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(val);
                pageSet.insert(pages[i]);
                pageQueue.push(pages[i]);
                PF++;
            }
        }

        // Prints the required information through each step of simulation
        cout << "Step " << i + 1 << ": Page fault (" << pages[i] << ") - Page Table: {";
        for (int j = 1; j <= i + 1; j++) {
            if (j != 1) cout << ", ";
            cout << j;
        }
        cout << "}, Frames: [";
        for (int j = 0; j < pageQueue.size(); j++) {
            if (j != 0) cout << ", ";
            cout << pageQueue.front();
            pageQueue.push(pageQueue.front());
            pageQueue.pop();
        }
        cout << "], Faults: " << PF << endl;
    }

    return PF;
}

int main() {
    int pages[] = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 }; // Page reference string
    int capacity = 4; // Number of frames
    int n = sizeof(pages) / sizeof(pages[0]);

    // LRU Algorithm
    cout << "For LRU Algorithm:" << endl;
    LRU(pages, n, capacity);
    cout << endl;

    // Optimal Algorithm
    cout << "For Optimal Algorithm:" << endl;
    find(pages, n, capacity);
    cout << endl;

    // FIFO Algorithm
    cout << "For FIFO Algorithm:" << endl;
    int totalFaults = fifo(pages, n, capacity);
    cout << "Total Page Faults: " << totalFaults << endl;

    return 0;
}