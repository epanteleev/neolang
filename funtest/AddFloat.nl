class AddFloat {
	def main {
        fpush 2.0
		fpush 3.0
        fstore 0
		fstore 1
		call AddFloat::add
		fstore 0 
		call Io::printFloat
		ret
	}

	def add {
		fload 1
		fload 0
		fadd
		fret
	}
}
