class AddInt {
	def main = {
		iPUSH 2
		iPUSH 3
		iSTORE 0
		iSTORE 1
		CALLSTATIC AddInt::add
		RET	
	}

	def add = {
		iLOAD 1
		iLOAD 0
		iADD
		iSTORE 0
		CALLSTATIC Io::printInt
		RET
	}
}
