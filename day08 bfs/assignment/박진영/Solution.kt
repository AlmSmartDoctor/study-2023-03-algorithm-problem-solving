class Solution {

    data class State(val x: Int, val y: Int) { // x,y ball의 좌표
        fun goal(goal: IntArray): Boolean {
            return goal[1] == x && goal[0] == y
        }
    }


    fun hasPath(maze: Array<IntArray>, start: IntArray, destination: IntArray): Boolean {
        val visitedMap = mutableMapOf<State, Boolean>()
        val q = ArrayDeque<State>()

        val h = maze.size
        val w = maze[0].size
        fun State.reachableState(): List<State> {
            var t : Int = x
            var s : State
            val res : MutableList<State> = mutableListOf()
            //check left kick
            for (i in x.downTo(0)) {
                if(maze[y][i] == 1) break
                t = i
            }
            s = State(t,y)
            if(visitedMap[s] == null)  res.add(s)

            //check right kick
            for (i in x until w) {
                if(maze[y][i] == 1) break
                t = i
            }
            s = State(t,y)
            if(visitedMap[s] == null)  res.add(s)

            //check up kick
            for (i in y.downTo(0)) {
                if(maze[i][x] == 1) break
                t = i
            }
            s = State(x,t)
            if(visitedMap[s] == null)  res.add(s)

            //check down kick
            for (i in y until h) {
                if(maze[i][x] == 1) break
                t = i
            }
            s = State(x,t)
            if(visitedMap[s] == null)  res.add(s)

            return res
        }

        q.addLast(State(y = start[0], x = start[1]))
        var res = false
        while (q.isNotEmpty()) {
            val currentState = q.removeFirst()
            if (currentState.goal(destination)) {
                res = true
                break
            }
            if (visitedMap[currentState] == true) continue

            visitedMap[currentState] = true
            val states =  currentState.reachableState()
            q.addAll(states)
        }

        return res
    }
}
