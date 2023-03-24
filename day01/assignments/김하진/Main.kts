typealias Array2<T> = Array<Array<T>>

inline fun <T, reified R> Array2<T>.map2(f: (T) -> R): Array2<R> =
    map { it.map(f).toTypedArray() }.toTypedArray()

fun Array2<Int>.isSafeFromJangma(gansuryang: Int): Array2<Boolean> =
    map2 { it > gansuryang }

fun Array2<Boolean>.markFalseRecursively(x: Int, y: Int) {
    if (x < 0 || y < 0 || x >= size || y >= size) {
        return
    }
    if (!this[y][x]) return

    this[y][x] = false
    markFalseRecursively(x = x + 1, y = y)
    markFalseRecursively(x = x - 1, y = y)
    markFalseRecursively(x = x, y = y + 1)
    markFalseRecursively(x = x, y = y - 1)
}

fun Array2<Boolean>.getNumberOfSafeZones(): Int {
    var numberOfSafeZones = 0

    mapIndexed { y, xs ->
        xs.mapIndexed { x, isSafe ->
            if (isSafe) {
                numberOfSafeZones++
                markFalseRecursively(x = x, y = y)
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
