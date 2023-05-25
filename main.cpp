
#include <cstring>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

enum Direction
{
    NORTH = 0,
    WEST = 1,
    SOUTH = 2,
    EAST = 3
};

class Location
{
public:
    int x, y;
    int dir;

    Location(int i, int j)
    {
        x = i;
        y = j;
        // Initially direction set to -1 -- no direction tried.
        dir = -1;
    }
};

char dirToChar(int d)
{
    switch (d)
    {
    case NORTH:
        return 'N';
    case WEST:
        return 'W';
    case SOUTH:
        return 'S';
    case EAST:
        return 'E';
    default:
        return 'X';
    }
}

// output a Location object.
ostream &operator<<(ostream &os, const Location &n)
{
    os << '(' << n.x << ", " << n.y << ", " << dirToChar(n.dir) << ") ";
    return os;
}

// Output a stack object.
ostream &operator<<(ostream &os, stack<Location> my_stack)
{
    // use copy parameter to copy entire stack. Needed because this
    // function destroys the stack as it prints it.
    while (!my_stack.empty())
    {
        Location n = my_stack.top();
        os << n;
        my_stack.pop();
    }
    return os;
}

// Space for maze -- 100x100 is maximum.
char maze[100][100];
// Keep track of locations that have been visited.
bool visited[100][100];

// Size of the maze.
int numRows, numCols;

// Starting location
int startX, startY;
// Location of the goal.
int goalX, goalY;

/*
 * read the maze from the given file, into the maze variable.
 * the maze file starts with a line containing the number of rows and cols.
 * Maze has a character for each location:
 * S = start
 * G = goal
 * _ = hallway (empty space)
 * X = wall
 * While reading the maze, store the starting point and goal into the
 * global variables.
 * @return true if the file exists and can be read. False otherwise.
 */
bool readMazeFromFile(string fName)
{
    ifstream fin(fName);
    fin >> numRows;
    fin >> numCols;
    char location;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            fin >> location;
            maze[i][j] = location;
            if (location == 'S')
            {
                startX = i;
                startY = j;
            }
            if (location == 'G')
            {
                goalX = i;
                goalY = j;
            }
        }
    }
    fin.close();

    return true;
}

bool isReachable()
{
    stack<Location> st;
    st.push(Location(0, 0));
    cout << "push on stack. Stack is now " << st << endl;
    while (!st.empty())
    {
        Location current_loc = st.top();
        st.pop();
        if (current_loc.x == goalX && current_loc.y == goalY)
        {
            st.push(current_loc);
            cout << "FINAL PATH " << st << endl;
            return true;
        }
        visited[current_loc.x][current_loc.y] = true;
        current_loc.dir = current_loc.dir + 1;
        if (current_loc.dir == NORTH)
        {
            if (current_loc.x > 0 &&
                (!visited[current_loc.x - 1][current_loc.y]) &&
                (maze[current_loc.x - 1][current_loc.y] != 'X'))
            {
                st.push(current_loc);
                st.push(Location(current_loc.x - 1, current_loc.y));
                cout << "push on stack. stack is now " << st << endl;
                continue;
            }
            else
            {
                current_loc.dir += 1;
            }
        }
        if (current_loc.dir == WEST)
        {
            if (current_loc.y > 0 &&
                (!visited[current_loc.x][current_loc.y - 1]) &&
                (maze[current_loc.x][current_loc.y - 1] != 'X'))
            {
                st.push(current_loc);
                st.push(Location(current_loc.x, current_loc.y - 1));
                cout << "push on stack. stack is now " << st << endl;
                continue;
            }
            else
            {
                current_loc.dir += 1;
            }
        }
        if (current_loc.dir == SOUTH)
        {
            if (current_loc.x < numRows - 1 &&
                (!visited[current_loc.x + 1][current_loc.y]) &&
                (maze[current_loc.x + 1][current_loc.y] != 'X'))
            {
                st.push(current_loc);
                st.push(Location(current_loc.x + 1, current_loc.y));
                cout << "push on stack. stack is now " << st << endl;
                continue;
            }
            else
            {
                current_loc.dir += 1;
            }
        }
        if (current_loc.dir == EAST)
        {
            if (current_loc.y < numCols - 1 &&
                (!visited[current_loc.x][current_loc.y + 1]) &&
                (maze[current_loc.x][current_loc.y + 1] != 'X'))
            {
                st.push(current_loc);
                st.push(Location(current_loc.x, current_loc.y + 1));
                cout << "push on stack. stack is now " << st << endl;
                continue;
            }
            else
            {
                current_loc.dir += 1;
            }
        }
    }

    return false;
}

// Driver code
int main()
{
    string fileName;

    // Read in maze
    cout << "Enter the name of the file containing the maze: ";
    cin >> fileName;

    if (!readMazeFromFile(fileName))
    {
        cerr << "Could not read given filename" << endl;
        exit(-1);
    }

    // Initially setting the visited array to false
    memset(visited, false, sizeof(visited));

    if (isReachable())
    {
        cout << "Path Found!" << '\n';
    }
    else
        cout << "No Path Found!" << '\n';

    return 0;
}