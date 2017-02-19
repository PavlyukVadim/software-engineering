"use strict";

function radixSort(arr, digit){
	let d = 0;
	let sortedArr = [];

	for(d = digit - 1; d >= 0 ; d--) { 
		
		//countingSort
		let arrByCurrentDigit = arr.map((item) => (item + '').split('')[d] - '');
	
		let maxValueInArr = Math.max(...arrByCurrentDigit);
		let arrOfFrequency = new Array( maxValueInArr + 1).fill(0);
		let i = 0;
		
		for (i = 0; i < arrByCurrentDigit.length; i++) {
			arrOfFrequency[ arrByCurrentDigit[i] ]++;
		}

		for (i = 1; i < arrOfFrequency.length; i++) {
			arrOfFrequency[i] += arrOfFrequency[i - 1]; 
		}

		for (i = arrByCurrentDigit.length - 1; i >= 0; i--) {
			sortedArr[arrOfFrequency[arrByCurrentDigit[i]] - 1] = arr[i];
			arrOfFrequency[arrByCurrentDigit[i]]--; 
		}

		arr = sortedArr.slice(0, sortedArr.length);  
	
	}

	return 	sortedArr;
}

console.log( radixSort([123,897,127,457], 3) );