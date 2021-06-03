class Fibonacci {
	def main {
		call Io::readInt
		istore 0
		call Fibonacci::fibonacci
        istore 0
        call Io::printInt
		ret	
	}

	def fibonacci {
		iload 0
		ipush 1
        cmpeq
        if {
            ipush 1
            iret
        }
        iload 0
        ipush 2
        cmpeq
        if {
            ipush 1
            iret
        }
        iload 0
        iload 0
        ipush 2
        isub
        istore 0
        call Fibonacci::fibonacci
        swap
        ipush 1
        isub
        istore 0
        call Fibonacci::fibonacci
        iadd
		iret
	}
}
