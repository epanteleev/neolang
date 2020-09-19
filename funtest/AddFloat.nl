class AddFloat {
	def main = {
		fPUSH 2
		fPUSH 3
		fSTORE 0
		fSTORE 1
		CALLSTATIC AddFloat::add	
	}

	def add = {
		fLOAD 1
		fLOAD 0
		fADD
		fSTORE 0
		CALLSTATIC Io::printFloat
		RET
	}
}
