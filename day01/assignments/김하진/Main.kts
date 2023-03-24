inline fun <T, reified R> Array<Array<T>>.map2(f: (T) -> R): Array<Array<R>> =
    map { it.map(f).toTypedArray() }.toTypedArray()

fun Array<Array<Int>>.isSafeFromJangma(gansuryang: Int): Array<Array<Boolean>> =
    map2 { it > gansuryang }

fun Array<Array<Boolean>>.recursivelyMarkFalse(x: Int, y: Int) {
    if (x < 0 || y < 0 || x >= size || y >= size) {
        return
    }
    if (this[y][x] == false) return

    this[y][x] = false
    recursivelyMarkFalse(x = x + 1, y = y)
    recursivelyMarkFalse(x = x - 1, y = y)
    recursivelyMarkFalse(x = x, y = y + 1)
    recursivelyMarkFalse(x = x, y = y - 1)
}

fun Array<Array<Boolean>>.getNumberOfSafeZones(): Int {
    var numberOfSafeZones = 0

    mapIndexed { y, xs ->
        xs.mapIndexed { x, isSafe ->
            if (isSafe) {
                numberOfSafeZones++
                recursivelyMarkFalse(x = x, y = y)
            }
        }
    }

    return numberOfSafeZones
}

fun main() {
    val size = readln().toInt()
    val zone = (1..size).map { readln().split(" ").map { it.toInt() }.toTypedArray() }.toTypedArray()

    val maxGansuryang = zone.maxOfOrNull { it.max() }!!

    val gansuryangs = 0..maxGansuryang

    val maxNumberOfSafeZones = gansuryangs.maxOfOrNull { gansuryang ->
        zone
            .isSafeFromJangma(gansuryang)
            .getNumberOfSafeZones()
    } ?: 0

    println(maxNumberOfSafeZones)
}

main() // Kotlin Script
