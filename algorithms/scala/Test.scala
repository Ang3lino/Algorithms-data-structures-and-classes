import scalaz._, Scalaz._
 
object Test {
    def main(args: Array[String]): Unit = {
        val p = (1, 2)
        val q = (2, 4)
        val sum = p |+| q
        println(sum)
    }
}