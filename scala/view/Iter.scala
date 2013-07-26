object Iter {
  def main(args: Array[String]) {
    val x = 1 to 100000000
    val y =
      for (e <- x.iterator if e % 2 == 0) yield e

    val t1 = System.currentTimeMillis
    var sum = 0
    for (yy <- y) sum += yy
    println("Time passed: " + (System.currentTimeMillis - t1) / 1000.0)
  }
}



// vim: set ts=4 sw=4 et:
