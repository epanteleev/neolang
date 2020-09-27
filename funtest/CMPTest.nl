class CMPTest {
	def main = {
		iPUSH 6
		iPUSH 6
		IF_EQ L
		LDC HelloWorld
		rSTORE 0
		CALLSTATIC Io::printString
	.L:
		LDC Hello
		rSTORE 0
		CALLSTATIC Io::printString
		RET
	}
}
