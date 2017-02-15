"use strict";

function quickSort(arr, p, r) {
	if (p < r) {
		let q = partition(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	} 
	return arr;
}

let arr = [1, 5, 3, 7, 8, 10, 8, 3];
console.log( quickSort(arr, 0, arr.length - 1) );