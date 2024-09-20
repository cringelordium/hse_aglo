package main

import (
	"fmt"
	"strconv"
)

func RemoveOneDigitMax(num int) int {
	s := strconv.Itoa(num)
	maxNum := 0

	for i := 0; i < len(s); i++ {

		newStr := s[:i] + s[i+1:]

		newNum, _ := strconv.Atoi(newStr)

		if newNum > maxNum {
			maxNum = newNum
		}
	}

	return maxNum
}

func main() {
	var n int
	fmt.Scan(&n)

	numbers := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&numbers[i])
	}

	for _, num := range numbers {
		fmt.Println(RemoveOneDigitMax(num))
	}
}
