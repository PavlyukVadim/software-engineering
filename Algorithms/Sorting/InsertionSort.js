"use strict";

function insertionSort(data) {
	for(let i = 1, l = data.length; i < l; i++) {
		let key = data[i];
		let j = i - 1;
		while(j > 0 && data[j] > key) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}
	return data;
}

console.log( insertionSort([1, 5, 2, 1]) ); 