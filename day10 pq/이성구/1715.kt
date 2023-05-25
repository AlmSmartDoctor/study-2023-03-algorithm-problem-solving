import java.util.PriorityQueue

fun main(args: Array<String>) {
    val pq = PriorityQueue<Int>()

    val br = System.`in`.bufferedReader()
    val n = br.readLine().toInt()

    repeat(n){
        pq.add(br.readLine().toInt())
    }

    var total = 0

    while(pq.isNotEmpty()) {
        val num = pq.poll()

        if(pq.isNotEmpty()){
            var sum  = num + pq.poll()
            total += sum
            pq.add(sum)
        }
    }

    println(total)
}