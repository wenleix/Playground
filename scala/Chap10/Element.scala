abstract class Element {
  def contents: Array[String]
  def height: Int = contents.length
  def width: Int = 
    if (height == 0) 0 else contents(0).length

  def beside(that: Element): Element = {
    val newContents = 
      for (
        (line1, line2) <- this.contents zip that.contents
      ) yield line1 + line2
    
  }
}

class ArrayElement(
  override val contents: Array[String]
) extends Element

class LineElement(s: String) extends ArrayElement(Array(s)) {
  override def width: Int = s.length
  override def height: Int = 1
}

class UniformElement(
  ch: Char,
  override val width: Int,
  override val height: Int
) extends Element {
  private val line = ch.toString * width
  override def contents: Array[String] = Array.fill(height)(line)
}

// vim: set ts=4 sw=4 et:
