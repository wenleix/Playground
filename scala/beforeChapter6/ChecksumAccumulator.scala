class ChecksumAccumulator {
  private var sum = 0

  def add(b: Byte): Unit = {
    sum += b
  }

  def checksum(): Int = ~(sum & 0xFF) + 1
}

val ac = new ChecksumAccumulator
ac.add(15)
println(ac.checksum)

// vim: set ts=4 sw=4 et:
