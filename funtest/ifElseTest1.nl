class ifElseTest1 {
	def main {
	    ipush 6
  	    ipush 6
            cmpneq
            jmp L2
	.L1:
            ipush 4
            ipush 4
            cmpeq
            jmp L3
        .L3:       
            ldc "Hello hello"
	    rstore 0
	    call Io::printString
            goto L2
        .L4:
	    ldc "Hello"
	    rstore 0
	    call Io::printString
        .L2:
            ret
	}
}
