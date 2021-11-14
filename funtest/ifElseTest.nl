class ifElseTest {
	def main {
            ipush 6
	    ipush 5
            cmpneq
	    jmp L2
	.L1:
            ldc "HelloWorld"
	    rstore 0
	    call Io::printString
	    goto L3
        .L2:
	    ldc "Hello"
	    rstore 0
	    call Io::printString
        .L3:
            ret
	}
}
