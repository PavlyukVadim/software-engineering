"use strict";

const fs = require('fs');
const path = require('path');

let inputArr = [];
let countOfOperations = 0;

const filePath = path.join(__dirname, '../data_examples/input__10000.txt');

fs.readFile(filePath, {encoding: 'utf-8'}, function(err,data){
    if (!err){
    	inputArr = data.split('\n').map((str) => Number(str)).slice(0, -1);
    	
    	console.time('time');
		
		quickSort(inputArr, 0, inputArr.length - 1);
		console.log(countOfOperations);

		console.timeEnd('time');

    }else{
        console.log(err);
    }

});


function quickSort(arr, p, r) {
	if (p < r) {
		let q = partition(arr, p, r);
		countOfOperations += r - p; 
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	} 
	return arr;
}

function partition(arr, p, r) {
	let middleIndex = Math.floor( (p + r) / 2 );
	let middleElement = arr[middleIndex];
	let valuesForResearch = [ arr[p], middleElement, arr[r]];

	let averageValue = valuesForResearch.sort((a, b) => a - b)[1];
	let indexOfAverageValue = arr.indexOf( averageValue );

	let tempElement = arr[r];
	arr[r] = arr[indexOfAverageValue];
	arr[indexOfAverageValue] = tempElement;
	

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
	tempElement = arr[r];
	arr[r] = arr[i + 1];
	arr[i + 1] = tempElement;
	return i + 1;  
}