#include <graphics.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdio> // for sprintf

using namespace std;

// Window and sorting config
const int WIN_WIDTH = 1000;
const int WIN_HEIGHT = 600;
const int NUM_BARS = 5;
const double DELAY = 500; // smaller delay for smooth visuals

// Color config
const int COLOR_CURRENT = GREEN;
const int COLOR_COMPARING = RED;
const int COLOR_DEFAULT = WHITE;

vector<int> arr(NUM_BARS);

// Double buffering variables
int activePage = 0;

// Draw all bars (to the active page) with numbers
void drawBars(int current = -1, int comparing = -1)
{
    // Switch to active page
    setactivepage(activePage);
    setvisualpage(1 - activePage); // Show the other page while drawing here
    cleardevice();

    int barWidth = WIN_WIDTH / NUM_BARS;

    for (int i = 0; i < NUM_BARS; i++)
    {
        int barHeight = arr[i];
        int x1 = i * barWidth;
        int y1 = WIN_HEIGHT - barHeight;
        int x2 = x1 + barWidth - 2;
        int y2 = WIN_HEIGHT;

        // Coloring logic
        if (i == current)
            setfillstyle(SOLID_FILL, COLOR_CURRENT);
        else if (i == comparing)
            setfillstyle(SOLID_FILL, COLOR_COMPARING);
        else
            setfillstyle(SOLID_FILL, COLOR_DEFAULT);

        bar(x1, y1, x2, y2);

        // Draw number on top of bar
        setcolor(WHITE); // Text color
        char numStr[10];
        sprintf(numStr, "%d", arr[i]); // Convert int to string
        int textX = x1 + (barWidth - textwidth(numStr)) / 2;
        int textY = y1 - 20; // Slightly above the bar
        outtextxy(textX, textY, numStr);
    }

    // Flip pages
    activePage = 1 - activePage;
    delay(DELAY);
}

// Bubble Sort with visualization
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
    drawBars(); // Final sorted
}

int main()
{
    // Seed randomness
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize random bars
    for (int i = 0; i < NUM_BARS; i++)
    {
        arr[i] = rand() % (WIN_HEIGHT - 50) + 50;
    }

    initwindow(WIN_WIDTH, WIN_HEIGHT, "Bubble Sort Visualization");

    bubbleSort();

    getch();
    closegraph();
    return 0;
}
