#!/bin/bash

NEOLANG_EXE="./build/bin/neolang.exe"

RED=`tput setaf 1`
GREEN=`tput setaf 2`
RESET=`tput sgr0`

function runtest() {
    echo -e "${GREEN}[START]: $1"
	result=$($NEOLANG_EXE $1)

	if [[ "$result" == "$2" ]] 
	then
  		echo -e "\t${GREEN}[SUCCESS]${RESET}"
	else
  		echo -e "\t${RED}[FAIL]: $1${RESET}"
  		echo -e "\t${GREEN}[Expected]: $2${RESET}"
  		echo -e "\t${RED}[Actual]:${RESET} $result"
	fi
}

runtest funtest/AddInt.nl 5
runtest funtest/PrintString.nl "HelloWorld"
runtest funtest/AddFloat.nl 59
runtest funtest/CMPTest.nl "Hello"
runtest funtest/ConcatString.nl "HelloWorld"



