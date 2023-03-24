// 현재 상태: BFS를 안 쓰고 특이하게 풀다가 틀림

fun <T, R> List<List<T>>.map2(f: (T) -> R): List<List<R>> = map { it.map(f) }

fun <K, V> emptyMutableMap() = emptyMap<K, V>().toMutableMap()

fun List<List<Int>>.isSafeFromJangma(gansuryang: Int): List<List<Boolean>> =
    map2 { it > gansuryang }

fun List<List<Boolean>>.getNumberOfSafeZones(): Int {
    var numberOfSafeZones = 0
    val isCountedMap = emptyMap<Int, MutableMap<Int, Boolean>>().toMutableMap()

    isCountedMap[-1] = emptyMutableMap<Int, Boolean>()
    forEachIndexed { index, _ ->
        isCountedMap[index] = emptyMutableMap<Int, Boolean>()
    }
    isCountedMap[size] = emptyMutableMap<Int, Boolean>()

    mapIndexed { y, xs ->
        xs.mapIndexed { x, isSafe ->
            if (isSafe) {
                if (isCountedMap[y]!![x] != true) {
                    numberOfSafeZones++
                }
                isCountedMap[y]!![x] = true
                isCountedMap[y]!![x + 1] = true
                isCountedMap[y]!![x - 1] = true
                isCountedMap[y + 1]!![x] = true
                isCountedMap[y - 1]!![x] = true
            }
        }
    }

    return numberOfSafeZones
}

val size = readln().toInt()
val zone = (1..size).map { readln().split(" ").map { it.toInt() } }

val maxGansuryang = zone.flatten().max()

val gansuryangs = 0..maxGansuryang

val maxNumberOfSafeZones = gansuryangs.maxOfOrNull { gansuryang ->
    zone
        .isSafeFromJangma(gansuryang)
        .getNumberOfSafeZones()
} ?: 0

println(maxNumberOfSafeZones)
