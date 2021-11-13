#!/bin/bash

NEOLANG_EXE="./build/bin/neolang.exe"

RED=`tput setaf 1`
GREEN=`tput setaf 2`
RESET=`tput sgr0`

function pause(){
   read -p "$*"
}

function pause(){
   read -p "$*"
}
function greeting() {
    echo -e "${GREEN}[START]: $1"
}

# check <test name> <actual> <expected>
function check() {
    if [[ "$3" == "$2" ]] 
	then
  		echo -e "\t${GREEN}[SUCCESS]${RESET}"
	else
  		echo -e "\t${RED}[FAIL]: $1${RESET}"
  		echo -e "\t${GREEN}[Expected]: $2${RESET}"
  		echo -e "\t${RED}[Actual]:${RESET} $result"
	fi
}

function runtest() {
	greeting $1
    result=$($NEOLANG_EXE $1)

	check $1 "$2" "$result"
}

function runtestInput() {
    greeting $2
    result=$(echo -e $1 | $NEOLANG_EXE $2)

	check $2 "$3" "$result"
}

runtest funtest/AddInt.nl 5
runtest funtest/PrintString.nl "HelloWorld"
runtest funtest/AddFloat.nl 5
runtest funtest/IFTest.nl "HelloWorld"
runtest funtest/ConcatString.nl "HelloWorld"
runtest funtest/ifElseTest.nl "Hello"
runtest funtest/ifElseTest1.nl "Hello hello"
runtest funtest/Point.nl 10
runtestInput 22 funtest/Fibonacci.nl 17711
runtestInput 1 funtest/Fibonacci.nl 1
runtestInput 2 funtest/Fibonacci.nl 1

pause 'Press [Enter] key to continue...'
