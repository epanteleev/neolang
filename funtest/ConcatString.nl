class ConcatString {
	def main = {
		LDC Hello
		rSTORE 0
		LDC World
		rSTORE 1
		CALLSTATIC String::concat
		rSTORE 0
		CALLSTATIC Io::printString	
		RET
	}
}
