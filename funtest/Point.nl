class Point {
    field i32: x
    field i32: y

    def init {
        rload 0
        ipush 5
        putfield x
        rload 0
        ipush 5
        putfield y
        rload 0
        rret
    }

    def sum {
        rload 0
        dup
        getfield x
        swap
        getfield y
        iadd
        iret
    }
    
    def main {
        new Point
        rstore 0
        call Point::init
        rstore 0
        call Point::sum
        istore 0
        call Io::printInt
        ret
    }
}
