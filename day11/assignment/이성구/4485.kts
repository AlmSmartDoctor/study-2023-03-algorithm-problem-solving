import java.lang.StringBuilder
import java.util.PriorityQueue

val dx = arrayOf(0, 0, 1, -1)
val dy = arrayOf(1, -1, 0, 0)



fun main(args: Array<String>) {
    var cnt = 1
    var sb = StringBuilder()
    var br = System.`in`.bufferedReader()

    while (true) {
        var n = br.readLine().toInt()

        if (n == 0) {
            break
        }

        var matrix = Array(n) { IntArray(n) }
        var dist = Array(n) { IntArray(n) }

        for (i in 0 until n) {
            var input = br.readLine().split(" ").map { it.toInt() }
            for (j in 0 until n) {
                matrix[i][j] = input[j]
                dist[i][j] = Int.MAX_VALUE
            }
        }

        var pq = PriorityQueue<Pair<Int,Pair<Int,Int>>>(compareBy { it.first })

        pq.add(Pair(matrix[0][0],Pair(0,0)))

        dist[0][0] = matrix[0][0]
        while (pq.isNotEmpty()){
            var (cost, point) = pq.poll()
            var (x,y) = point

            for (i in 0 .. 3){
                var nx = x + dx[i]
                var ny = y + dy[i]

                if (nx < 0 || nx >= n || ny < 0 || ny >= n){
                    continue
                }

                if (dist[nx][ny] > dist[x][y] + matrix[nx][ny]){
                    dist[nx][ny] = dist[x][y] + matrix[nx][ny]
                    pq.add(Pair(dist[nx][ny],Pair(nx,ny)))
                }
            }
        }

        sb.append("Problem ${cnt++}: ${dist[n-1][n-1]}\n")
    }
    println(sb.toString())
}