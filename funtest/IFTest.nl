class IFTest {
	def main {
		ipush 6
		ipush 6
        cmpeq
		if {
		    ldc "HelloWorld"
		    rstore 0
		    call Io::printString
            ret
	    }
		ldc "Hello"
		rstore 0
		call Io::printString
		ret
	}
}
