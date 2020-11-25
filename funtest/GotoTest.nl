class GotoTest {
	def main = {
		iPUSH 6
		iPUSH 6
		IF_EQ L
	.LL: 
		LDC WORLD
		rSTORE 0
		CALLSTATIC Io::printString
		RET
	.L:
		LDC Hello
		rSTORE 0
		CALLSTATIC Io::printString
		GOTO LL
		RET
	}
}
