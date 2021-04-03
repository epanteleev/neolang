class PrintString {
	def main {
		ldc "HelloWorld"
		rstore 0
		call Io::printString
		ret
	}
}
