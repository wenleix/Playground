
object main {
  def usedMem = {
    System.gc
    System.gc
    System.gc
    Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory()
  }

  def report(t: String, a: => Any): Any = {
    val m1 = usedMem
    val v = a
    val m2 = usedMem
    println("%s: %.2f MB".format(t, (m2 - m1) / 1024.0 / 1024))
    v
  }

  def main(args: Array[String]) {
    val range = 0 until 1024 * 1024
    report("scala.MapInt", range.map(i => i))
    report("scala.ArrayInt", Array.fill(range.length)(0))
    report("scala.Some", Array.fill(range.length)(Some(0)))
    report("scala.None", range.map(i => None))
  }
}


// vim: set ts=4 sw=4 et:
