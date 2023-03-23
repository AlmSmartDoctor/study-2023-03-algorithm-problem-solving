

fun main(args: Array<String>) {

    val mutableList = MutableList<MutableList<String>>(4) {
        mutableListOf()
    }
    for(i in 0 until 5){
        val s = readln()
        s.split(' ')
            .forEachIndexed { index, string ->
                mutableList[index].add(string)
            }
    }

    val x = fixClock(mutableList)

    println(x)
}

val numbers = listOf(
    listOf(
        "###",
        "#.#",
        "#.#",
        "#.#",
        "###",
    ),
    listOf(
        "..#",
        "..#",
        "..#",
        "..#",
        "..#",
    ),
    listOf(
        "###",
        "..#",
        "###",
        "#..",
        "###",
    ),
    listOf(
        "###",
        "..#",
        "###",
        "..#",
        "###",
    ),
    listOf(
        "#.#",
        "#.#",
        "###",
        "..#",
        "..#",
    ),
    listOf(
        "###",
        "#..",
        "###",
        "..#",
        "###",
    ),
    listOf(
        "###",
        "#..",
        "###",
        "#.#",
        "###",
    ),
    listOf(
        "###",
        "..#",
        "..#",
        "..#",
        "..#",
    ),

    listOf(
        "###",
        "#.#",
        "###",
        "#.#",
        "###",
    ),

    listOf(
        "###",
        "#.#",
        "###",
        "..#",
        "###",
    ),
)

val intList = numbers.map { number ->
    number.map {
        it.toCharArray().map { char -> if (char == '#') 1 else 0 }
    }
}

fun fixClock(clock: List<List<String>>): String {
    val time = clock.map { wrong ->
        var minVal: Int = 9
        for (i in intList.indices) {
            val x = intList[i].reduce { acc, ints -> acc + ints }
            val y = wrong
                .reduce { acc, strings -> acc + strings }
                .map { char -> if (char == '#') 1 else 0 }
            if(checkSame(y, x)){
                minVal = i
                break
            }
        }
        minVal
    }
    return  "${time[0]}${time[1]}:${time[2]}${time[3]}"
}

fun checkSame(wrongNumber: List<Int>, number: List<Int>): Boolean {
    return wrongNumber.mapIndexed { index, i -> i.or(number[index]) }
        .foldIndexed(true) { index, acc, i ->
            if (!acc) false
            else i == number[index]
        }
}