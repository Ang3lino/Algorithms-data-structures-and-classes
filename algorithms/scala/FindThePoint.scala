import scala.collection.mutable._

object FindThePoint {
    def main(args: Array[String]): Unit = {
        val amount = readLine.toInt
        var (i, p) = ( 0, new ListBuffer[(Int, Int)]() )
        var q = new ListBuffer[(Int, Int)]()
        while (i < 2 * amount) {
            val x = readLine.toInt
            val y = readLine.toInt
            if (i % 2 == 0)
                p += ((x, y))
            else 
                q += ((x, y))
            i += 1
        }
        var delta = new ListBuffer[(Int, Int)]()
        for ((pt, qt) <- (p zip q)) 
            delta += ( (qt._1 - pt._1, qt._2 - pt._2) )
        var ans = new ListBuffer[(Int, Int)]()
        for ((qt, deltat) <- (q zip delta))     
            ans += ( (qt._1 + deltat._1, qt._2 + deltat._2) )
        ans.foreach(x => println(s"${x._1}${x._2}"))
    }
}
