#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "state.h"
#include "prioqueue.h"

void solveMaze(Maze maze) {
  Direction dir[6]={UP, DOWN, NORTH, EAST, SOUTH, WEST};
  Pqueue fringe;
  Position pos, goal;
  State state, successor;
    int i, priority, visitCount = 0, pushCount = 0;
  
  getPosition(maze, &pos);
  getGoal(maze, &goal);

  getMazeState(&state, maze);
  priority = random();
  setStatePriority(&state, priority);
  
  initPqueue(&fringe);
  pushPqueue(&fringe, state);
    pushCount++;
    
  while (!isEmptyPqueue(fringe) && !isSolved(maze)) {
    topPqueue(fringe, &state);
    popPqueue(&fringe);
     visitCount++;
    setMazeState(&maze, state);    
    printState(state);
    for (i=0; i<6; i++) {
      if (canMoveTo(maze, dir[i])) {
        /* make move in direction dir[i] */
        makeMove(&maze, dir[i]);
        /* show result */
#if 0
        printf("makeMove %s\n", convertDirectionToString(dir[i]));
        printMaze(maze);
#endif
        /* get new state (i.e. is a successor) */
        getMazeState(&successor, maze);
        /* show new state */
#if 0
        printState(successor);
#endif
        /* set priority of successor an put it in the fringe */
        priority = random();
        setStatePriority(&successor, priority);
        pushPqueue(&fringe, successor);
        pushCount++;
        /* undo move */
        setMazeState(&maze, state);
      }
    }
  }
  if (isSolved(maze)) {
   printf ("MAZE SOLVED: Path=");
   printPathWithNewline(maze.path);
  } else {
	  printf ("NO PATH FOUND\n");
  }
    
    printf("Number of nodes visited: %d Number of nodes inserted in the fringe: %d \n",visitCount, pushCount);
}

void solveMazeBFS(Maze maze) {
    Direction dir[6]={UP, DOWN, NORTH, EAST, SOUTH, WEST};
    Pqueue fringe;
    Position pos, goal;
    State state, successor;
    int i, priority=100, visitCount = 0, pushCount = 0;
    
    getPosition(maze, &pos);
    getGoal(maze, &goal);
    
    getMazeState(&state, maze);
    setStatePriority(&state, priority);
    
    initPqueue(&fringe);
    pushPqueue(&fringe, state);
    pushCount++;
    
    while (!isEmptyPqueue(fringe) && !isSolved(maze)) {
        topPqueue(fringe, &state);
        popPqueue(&fringe);
        visitCount++;
        setMazeState(&maze, state);
        //printState(state);
        for (i=0; i<6; i++) {
            if (canMoveTo(maze, dir[i])) {
                /* make move in direction dir[i] */
                makeMove(&maze, dir[i]);
                /* show result */
#if 0
                printf("makeMove %s\n", convertDirectionToString(dir[i]));
                printMaze(maze);
#endif
                /* get new state (i.e. is a successor) */
                getMazeState(&successor, maze);
                /* show new state */
#if 0
                printState(successor);
#endif
                /* set priority of successor an put it in the fringe */
                priority--;
                setStatePriority(&successor, priority);
                pushPqueue(&fringe, successor);
                pushCount++;
                /* undo move */
                setMazeState(&maze, state);
            }
        }
    }
    if (isSolved(maze)) {
        printf ("MAZE SOLVED: Path=");
        printPathWithNewline(maze.path);
    } else {
        printf ("NO PATH FOUND\n");
    }
    
    printf("Number of nodes visited: %d Number of nodes inserted in the fringe: %d \n",visitCount, pushCount);
}


void solveMazeDFS(Maze maze) {
    Direction dir[6]={UP, DOWN, NORTH, EAST, SOUTH, WEST};
    Pqueue fringe;
    Position pos, goal;
    State state, successor;
    int i, priority=0, visitCount = 0, pushCount = 0;
    
    getPosition(maze, &pos);
    getGoal(maze, &goal);
    
    getMazeState(&state, maze);
    setStatePriority(&state, priority);
    
    initPqueue(&fringe);
    pushPqueue(&fringe, state);
    pushCount++;
    
    while (!isEmptyPqueue(fringe) && !isSolved(maze)) {
        topPqueue(fringe, &state);
        popPqueue(&fringe);
        visitCount++;
        setMazeState(&maze, state);
        printState(state);
        for (i=0; i<6; i++) {
            if (canMoveTo(maze, dir[i])) {
                /* make move in direction dir[i] */
                makeMove(&maze, dir[i]);
                /* show result */
#if 0
                printf("makeMove %s\n", convertDirectionToString(dir[i]));
                printMaze(maze);
#endif
                /* get new state (i.e. is a successor) */
                getMazeState(&successor, maze);
                /* show new state */
#if 0
                printState(successor);
#endif
                /* set priority of successor an put it in the fringe */
                priority++;
                setStatePriority(&successor, priority);
                pushPqueue(&fringe, successor);
                pushCount++;
                /* undo move */
                setMazeState(&maze, state);
            }
        }
    }
    if (isSolved(maze)) {
        printf ("MAZE SOLVED: Path=");
        printPathWithNewline(maze.path);
    } else {
        printf ("NO PATH FOUND\n");
    }
    
    printf("Number of nodes visited: %d Number of nodes inserted in the fringe: %d \n",visitCount, pushCount);
}


void solveMazeIDA(Maze maze) {
    Direction dir[6]={UP, DOWN, NORTH, EAST, SOUTH, WEST};
    Pqueue fringe;
    Position pos, goal;
    State state, successor;
    int i, priority=0, visitCount = 0, pushCount = 0, x, depth=0;
    
    getPosition(maze, &pos);
    getGoal(maze, &goal);
    
    
    while(!isSolved(maze)){
        depth++;
        x=0;
        getMazeState(&state, maze);
        setStatePriority(&state, priority);
        initPqueue(&fringe);
        pushPqueue(&fringe, state);
        pushCount++;
        //printf(" \n\n\n");
        //printf("%d \t", depth);
        while (!isEmptyPqueue(fringe) && !isSolved(maze)) {
            topPqueue(fringe, &state);
            popPqueue(&fringe);
            visitCount++;
            setMazeState(&maze, state);
            //printState(state);
            //printf("%d ",getStatePriority(state));
            x = getStatePriority(state);
            //printf(" %d \t", x);
            for (i=0; i<6; i++) {
                if (canMoveTo(maze, dir[i]) && (getStatePriority(state)<depth)) {
                    /* make move in direction dir[i] */
                    makeMove(&maze, dir[i]);
                    /* show result */
#if 0
                    printf("makeMove %s\n", convertDirectionToString(dir[i]));
                    printMaze(maze);
#endif
                    /* get new state (i.e. is a successor) */
                    getMazeState(&successor, maze);
                    /* show new state */
#if 0
                    //printState(successor);
#endif
                    /* set priority of successor an put it in the fringe */
                    setStatePriority(&successor, x+1);
                    pushPqueue(&fringe, successor);
                    pushCount++;
                    /* undo move */
                    setMazeState(&maze, state);
                }
            }
        }
    }
    if (isSolved(maze)) {
        printf ("MAZE SOLVED: Path=");
        printPathWithNewline(maze.path);
    } else {
        printf ("NO PATH FOUND\n");
    }
    printf("Number of nodes visited: %d Number of nodes inserted in the fringe: %d \n",visitCount, pushCount);
}


void solveMazeAStar(Maze maze) {
    Direction dir[6]={UP, DOWN, NORTH, EAST, SOUTH, WEST};
    Pqueue fringe;
    Position pos, goal;
    State state, successor;
    int i, priority=1, visitCount = 0, pushCount = 0;
    
    getPosition(maze, &pos);
    getGoal(maze, &goal);
    
    getMazeState(&state, maze);
    setStatePriority(&state, priority);
    
    initPqueue(&fringe);
    pushPqueue(&fringe, state);
    pushCount++;
    
    while (!isEmptyPqueue(fringe) && !isSolved(maze)) {
        topPqueue(fringe, &state);
        popPqueue(&fringe);
        visitCount++;
        setMazeState(&maze, state);
        printState(state);
        for (i=0; i<6; i++) {
            if (canMoveTo(maze, dir[i])) {
                /* make move in direction dir[i] */
                makeMove(&maze, dir[i]);
                /* show result */
#if 0
                printf("makeMove %s\n", convertDirectionToString(dir[i]));
                printMaze(maze);
#endif
                /* get new state (i.e. is a successor) */
                getMazeState(&successor, maze);
                /* show new state */
#if 0
                printState(successor);
#endif
                /* set priority of successor an put it in the fringe */
                priority = heuristic(goal,successor);
                setStatePriority(&successor, priority);
                pushPqueue(&fringe, successor);
                pushCount++;
                /* undo move */
                setMazeState(&maze, state);
            }
        }
    }
    if (isSolved(maze)) {
        printf ("MAZE SOLVED: Path=");
        printPathWithNewline(maze.path);
    } else {
        printf ("NO PATH FOUND\n");
    }
    
    printf("Number of nodes visited: %d Number of nodes inserted in the fringe: %d \n",visitCount, pushCount);
}

int heuristic(Position goal, State successor){
    Position pos;
    getStatePosition(successor,&pos);
    int distance = abs(goal.x - pos.x) + abs(goal.y - pos.y) + abs(goal.z - pos.z);
    distance += getStatePathLength(successor);
    distance *= -1;
    
    return distance;
}


int main(int argc, char *argv[]) {
  Maze maze;
  Position pos, goal;
  
  readMazeFromFile(&maze, "maze3D.txt");

  getPosition(maze, &pos);
  printf ("The initial position is ");
  printPositionWithNewline(pos);

  getGoal(maze, &goal);
  printf ("The goal is at ");
  printPositionWithNewline(goal);

  printMaze(maze);

  solveMazeIDA(maze);
  
  return EXIT_SUCCESS;
}
