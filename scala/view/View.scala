object View {
  def main(args: Array[String]) {
    val x = 1 to 100000000
    val y =
      for (e <- x.view if e % 2 == 0) yield e

    val t1 = System.currentTimeMillis
    var sum = 0
    for (i <- 0 until 50000000)
      sum += y(i)
    println("Time passed: " + (System.currentTimeMillis - t1) / 1000.0)
  }
}



// vim: set ts=4 sw=4 et:
