class PrintString {
	def main = {
		LDC HelloWorld
		rSTORE 0
		CALLSTATIC Io::printString
		RET
	}
}
