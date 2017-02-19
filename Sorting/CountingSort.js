"use strict";

function countingSort(arr) {
	let maxValueInArr = Math.max(...arr);
	let arrOfFrequency = new Array( maxValueInArr + 1).fill(0);
	let i = 0;
	
	for (i = 0; i < arr.length; i++) {
		arrOfFrequency[ arr[i] ]++;
	}

	for (i = 1; i < arrOfFrequency.length; i++) {
		arrOfFrequency[i] += arrOfFrequency[i - 1]; 
	}

	let sortedArr = [];
	for (i = arr.length - 1; i >= 0; i--) {
		sortedArr[arrOfFrequency[arr[i]] - 1] = arr[i];
		arrOfFrequency[arr[i] - 1]--; 
	}	
	return 	sortedArr;
}

console.log( countingSort([1,10,9,8]) );