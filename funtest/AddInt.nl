class AddInt {
	def main {
		ipush 2
		ipush 3
		istore 0
		istore 1
		call AddInt::add
		ret	
	}

	def add {
		iload 1
		iload 0
		iadd
		istore 0
		call Io::printInt
		ret
	}
}
