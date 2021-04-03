class ifElseTest1 {
	def main {
		ipush 6
		ipush 6
        cmpeq
		if {
            ipush 4
            ipush 4
            cmpeq
            if {
                ldc "Hello hello"
		        rstore 0
		        call Io::printString
            }
	    } else {
		    ldc "Hello"
		    rstore 0
		    call Io::printString
        }
        ret
	}
}
