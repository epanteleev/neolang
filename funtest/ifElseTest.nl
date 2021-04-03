class ifElseTest {
	def main {
		ipush 6
		ipush 5
        cmpeq
		if {
		    ldc "HelloWorld"
		    rstore 0
		    call Io::printString
	    } else {
		    ldc "Hello"
		    rstore 0
		    call Io::printString
        }
        ret
	}
}
