import scala.io.Source

object WordCount {
    def main(args: Array[String]): Unit = {
        val filename = "input.txt"
        val wordCounts = countWords(filename)
        wordCounts.foreach { case (word, count) =>
            println(s"$word: $count")
        }
    }

    def countWords(filename: String): Map[String, Int] = {
        val source = Source.fromFile(filename)
        val wordCounts = source.getLines()
            .flatMap(_.split(" "))
            .foldLeft(Map.empty[String, Int].withDefaultValue(0)) { (counts, word) =>
                counts.updated(word.toLowerCase, counts(word.toLowerCase) + 1)
            }
        source.close()
        wordCounts
    }
}
