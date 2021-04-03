class ConcatString {
	def main {
		ldc "Hello"
		rstore 0
		ldc "World"
		rstore 1
		call String::concat
		rstore 0
		call Io::printString	
		ret
	}
}
