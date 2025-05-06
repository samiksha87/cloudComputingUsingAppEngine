import org.apache.spark.sql.SparkSession

object WordCountSpark {
  def main(args: Array[String]): Unit = {
    val spark = SparkSession.builder()
      .appName("Word Count")
      .master("local[*]")
      .getOrCreate()

    val sc = spark.sparkContext
    val inputFile = "input.txt" // Replace with your file path

    val lines = sc.textFile(inputFile)
    val words = lines.flatMap(_.split("\\s+"))
    val wordCounts = words.map(word => (word, 1)).reduceByKey(_ + _)

    wordCounts.collect().foreach { case (word, count) =>
      println(s"$word -> $count")
    }

    spark.stop()
  }
}
