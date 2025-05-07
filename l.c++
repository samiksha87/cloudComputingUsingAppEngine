

192.168.1.1 - - [10/May/2025:13:55:36 +0000] "GET /index.html HTTP/1.1" 200 1024
192.168.1.2 - - [10/May/2025:14:01:22 +0000] "GET /page-not-found HTTP/1.1" 404 512
192.168.1.3 - - [11/May/2025:09:12:45 +0000] "POST /submit HTTP/1.1" 200 2048
192.168.1.1 - - [11/May/2025:10:15:30 +0000] "GET /missing-page HTTP/1.1" 404 256
import scala.io.Source

object LogFileAnalytics {
  def main(args: Array[String]): Unit = {
    // ✅ Path to your log file
    val logFile = "path/to/your/logfile.txt"

    // ✅ Read all lines from the log file
    val lines = Source.fromFile(logFile).getLines().toList

    // ✅ Extract hosts (assuming host is the first word in each log line)
    val hosts = lines.map(line => line.split(" ")(0))

    // ✅ Extract URLs (assuming URL is the 7th word in each log line, adjust index if needed)
    val urls = lines.map { line =>
      val parts = line.split(" ")
      if (parts.length > 6) parts(6) else ""
    }

    // ✅ (I) Top 10 frequent hosts
    val topHosts = hosts.groupBy(identity)
                        .mapValues(_.size)
                        .toList
                        .sortBy(-_._2)
                        .take(10)

    println("\n👉 Top 10 Frequent Hosts:")
    topHosts.foreach { case (host, count) =>
      println(s"$host: $count times")
    }

    // ✅ (II) Top 5 URLs/paths
    val topUrls = urls.groupBy(identity)
                      .mapValues(_.size)
                      .toList
                      .sortBy(-_._2)
                      .take(5)

    println("\n👉 Top 5 URLs/Paths:")
    topUrls.foreach { case (url, count) =>
      println(s"$url: $count times")
    }

    // ✅ (III) Number of unique hosts
    val uniqueHosts = hosts.distinct.size
    println(s"\n👉 Number of Unique Hosts: $uniqueHosts")
  }
}





import scala.io.Source

object LogFile404Analytics {
  def main(args: Array[String]): Unit = {
    // ✅ Path to your log file
    val logFile = "path/to/your/logfile.txt"

    // ✅ Read all lines from the log file
    val lines = Source.fromFile(logFile).getLines().toList

    // ✅ Filter lines that have 404 status code
    val error404Lines = lines.filter(line => line.contains(" 404 "))

    // (I) 👉 Count of 404 Response Codes
    val count404 = error404Lines.size
    println(s"\n👉 Total 404 Response Codes: $count404")

    // (II) 👉 Top 25 hosts causing 404 errors
    val hosts = error404Lines.map(line => line.split(" ")(0))
    val top25Hosts = hosts.groupBy(identity)
                          .mapValues(_.size)
                          .toList
                          .sortBy(-_._2)
                          .take(25)

    println("\n👉 Top 25 Hosts with 404 Errors:")
    top25Hosts.foreach { case (host, count) =>
      println(s"$host: $count times")
    }

    // (III) 👉 Unique Daily Hosts (date + host)
    val dailyHosts = lines.map { line =>
      val parts = line.split(" ")
      if (parts.length > 3) {
        val host = parts(0)
        val datePart = parts(3).substring(1, 11) // e.g., "10/May/2025"
        s"$datePart-$host"
      } else ""
    }.filter(_.nonEmpty).distinct

    val uniqueDailyHosts = dailyHosts.groupBy(identity).size
    println(s"\n👉 Number of Unique Daily Hosts: $uniqueDailyHosts")
  }
}
