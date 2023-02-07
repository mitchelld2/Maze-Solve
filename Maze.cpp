//
// Maze solution
// Author: Max Benson
// Date: 08/16/2021
//

#include "Grid.h"
#include "Stack.h"
#include "Queue.h"
#include "Set.h"
#include "CursesWindow.h"
#include "Maze.h"

/**
* Attempt to solve the maze using a breadth first algorithm
* @param maze the maze that we want to solve
* @param solution out parameter used to return solution if it is found
* @param pwindow if not nullptr, used to animate the solution process
* @return true if solution can be found, false otherwise
*/
bool SolveMaze(const Grid& maze, Stack<GridLocation>& solution, CursesWindow* pwindow)
{
    GridLocation start(0, 0);
    if(!maze[start])  //1. If the upper left square is a wall, return _false_.
    {
        return false;
    }
    Queue<Stack<GridLocation>> paths;   //2. Initialize the queue to the path of length 1 that contains the upper left square.
    Set<GridLocation> visited;  //3. Initialize the set of grid locations that you have reached (visited) to contain just the upper left grid location.
    Stack<GridLocation> path;

    visited.Add(start);

    path.Push(start);
    paths.Enqueue(path);

    while(!paths.IsEmpty())     //4. Loop until the queue is empty
    {
        path = paths.Dequeue();   //  a.  Dequeue a path

        //  b.  Add this code to display the path momentarily when program is run with -visualize flag:
        if (pwindow)
        {
            pwindow->ShowPath(path, false);
        }
        //c.  Generate set of the valid moves from the _GridLocation_ at the end of the path (i.e. the top item of the stack)
        Set<GridLocation> valid = GenerateValidMoves(maze, path.Peek());

        //	d.  For each valid move in this set which is not in the set of visited grid locations
        for(size_t i = 0; i < valid.Size(); i++)
        {
            if(!visited.Contains(valid.Get(i)))
            {
                Stack<GridLocation> newPath = path;
                newPath.Push(valid.Get(i));
                GridLocation end(maze.NumberRows()-1,maze.NumberCols()-1);

                if(CheckSolution(maze, newPath) && newPath.Peek() == end)
                {
                    solution = newPath;
                    return true;
                }
                else
                {
                    paths.Enqueue(newPath);
                    visited.Add(valid.Get(i));
                }
            }
        }
    }
    return false;   //5. If you end up here, you didn't find a solution, so you better return false
}

/**
* Generate set of grid locations adjacent to "loc" that are within the maze and not walls
* @param maze the maze that we want to solve
* @param loc grid location that we want to move from
* @return set of valid moves
*/
Set<GridLocation> GenerateValidMoves(const Grid& maze, const GridLocation& loc)
{
    Set<GridLocation> val;

    GridLocation north(loc.Row()-1, loc.Col()); //north
    GridLocation east(loc.Row(), loc.Col()+1);  //east
    GridLocation south(loc.Row()+1, loc.Col());  //south
    GridLocation west(loc.Row(), loc.Col()-1);  //west

    if(maze.IsWithinGrid(north) && maze[north])    //north
    {
        val.Add(north);
    }
    if(maze.IsWithinGrid(east) && maze[east])    //east
    {
        val.Add(east);
    }
    if(maze.IsWithinGrid(south) && maze[south])    //south
    {
        val.Add(south);
    }
    if(maze.IsWithinGrid(west) && maze[west])    //west
    {
        val.Add(west);
    }
    return val;
}

/**
* Check whether a purported solution is really a solution
* @param maze the maze that we want to solve
* @param path solution to check
* @return true it solves the maze, false it doesn't
*/
bool CheckSolution(const Grid& maze, Stack<GridLocation> path)
{
    bool first = true;
    GridLocation isGood;
    Stack<GridLocation> forPrev = path;
    GridLocation prev;
    GridLocation end(maze.NumberRows()-1,maze.NumberCols()-1);

    while(!path.IsEmpty())
    {
        isGood = path.Pop();    //1. Remove the next grid location from the path
        if(!maze.IsWithinGrid(isGood) || !maze[isGood])
        {
            return false;   //2. If the grid location is outside the grid or a wall, return false
        }
        if(first && isGood != end)
        {
            //3. If this is the first iteration of the loop return false if the grid location isn't the lower right corner
            return false;
        }
        else if(!first)//4. If this is not the first iteration, return false if the grid location from the previous iteration of the loop is not one of the valid moves from the current grid location
        {
            prev = forPrev.Pop();
            if(!GenerateValidMoves(maze, isGood).Contains(prev))
            {
                return false;
            }
        }
        first = false;
    }
    return true;
}