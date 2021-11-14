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
            cmpneq
            jmp L1
            
            ipush 1
            iret
        .L1:
            iload 0
            ipush 2
            cmpneq
            jmp L3
        .L2:
            ipush 1
            iret
        .L3:
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
