#include <graphics.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>

using namespace std;

// Window and sorting config
const int WIN_WIDTH = 1000;
const int WIN_HEIGHT = 600;
const int NUM_BARS = 10;
const double DELAY = 300; // Delay for visuals

// Color config
const int COLOR_CURRENT = GREEN;
const int COLOR_COMPARING = RED;
const int COLOR_DEFAULT = WHITE;

vector<int> arr(NUM_BARS);

// Double buffering variables
int activePage = 0;

// Draw all bars (with numbers)
void drawBars(int current = -1, int comparing = -1)
{
    setactivepage(activePage);
    setvisualpage(1 - activePage);
    cleardevice();

    int barWidth = WIN_WIDTH / NUM_BARS;

    for (int i = 0; i < NUM_BARS; i++)
    {
        int barHeight = arr[i];
        int x1 = i * barWidth;
        int y1 = WIN_HEIGHT - barHeight;
        int x2 = x1 + barWidth - 2;
        int y2 = WIN_HEIGHT;

        // Color logic
        if (i == current)
            setfillstyle(SOLID_FILL, COLOR_CURRENT);
        else if (i == comparing)
            setfillstyle(SOLID_FILL, COLOR_COMPARING);
        else
            setfillstyle(SOLID_FILL, COLOR_DEFAULT);

        bar(x1, y1, x2, y2);

        // Draw number on bar
        setcolor(YELLOW);
        string num = to_string(arr[i]);
        outtextxy(x1 + barWidth / 4, y1 - 20, const_cast<char*>(num.c_str()));
    }

    activePage = 1 - activePage;
    delay(DELAY);
}

// Bubble Sort
void bubbleSort()
{
    for (int i = 0; i < NUM_BARS - 1; i++)
    {
        for (int j = 0; j < NUM_BARS - i - 1; j++)
        {
            drawBars(j, j + 1);
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    drawBars();
}

// Selection Sort
void selectionSort()
{
    for (int i = 0; i < NUM_BARS - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < NUM_BARS; j++)
        {
            drawBars(minIndex, j);
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(arr[i], arr[minIndex]);
            drawBars(i, minIndex);
        }
    }
    drawBars();
}

// Insertion Sort
void insertionSort()
{
    for (int i = 1; i < NUM_BARS; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            drawBars(j, j + 1);
            j--;
        }
        arr[j + 1] = key;
        drawBars(j + 1);
    }
    drawBars();
}

// Merge Sort Helper: merge two halves
void merge(int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        drawBars(l + i, m + 1 + j);
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        drawBars(k);
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        drawBars(k);
    }
}

// Merge Sort Recursive
void mergeSort(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

// Quick Sort Helper: partition
int partition(int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        drawBars(j, high);
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    drawBars(i + 1, high);
    return (i + 1);
}

// Quick Sort Recursive
void quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}
int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize random bars
    for (int i = 0; i < NUM_BARS; i++)
    {
        arr[i] = rand() % (WIN_HEIGHT - 100) + 50;
    }

    // Show menu first (console only)
    cout << "Choose Sorting Algorithm:\n";
    cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\nEnter choice: ";
    int choice;
    cin >> choice;

    // NOW open the window after taking choice
    initwindow(WIN_WIDTH, WIN_HEIGHT, "Sorting Visualization");

    // Call the chosen sort
    switch (choice)
    {
    case 1: bubbleSort(); break;
    case 2: selectionSort(); break;
    case 3: insertionSort(); break;
    case 4: mergeSort(0, NUM_BARS - 1); drawBars(); break;
    case 5: quickSort(0, NUM_BARS - 1); drawBars(); break;
    default: cout << "Invalid choice\n"; break;
    }

    getch();
    closegraph();
    return 0;
}
