"use strict";

function quickSort(arr, p, r) {
	if (p < r) {
		let q = partition(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	} 
	return arr;
}

function partition(arr, p, r) {
	let bearingElement = arr[r];
	let i = p - 1;
	for (let j = p; j < r; j++) {
		if ( arr[j] <= bearingElement) {
			i++;
			let tempElement = arr[i];
			arr[i] = arr[j];
			arr[j] = tempElement;
		}
	}
	let tempElement = arr[r];
	arr[r] = arr[i + 1];
	arr[i + 1] = tempElement;
	console.log(arr);
	return i + 1;  
}

let arr = [1, 5, 3, 7, 8, 10, 8, 3];
console.log( quickSort(arr, 0, arr.length - 1) );