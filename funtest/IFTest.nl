class IFTest {
    def main {
        ipush 6
	ipush 6
        cmpeq
        jmp L1
    .L2:	
        ldc "Hello"
	rstore 0
	call Io::printString
        ret
    .L1:
	ldc "HelloWorld"
	rstore 0
	call Io::printString
	ret
    }
}
