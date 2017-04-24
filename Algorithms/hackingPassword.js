"use strict";

const fs = require('fs');
const path = require('path');

const filePath = path.join(__dirname, './data_examples/database_1000.txt');

let inputArr = [];
let sortedArr = [];

fs.readFile(filePath, {encoding: 'utf-8'}, function(err,data){
    if (!err){

    	inputArr = data.split('\n').slice(0, -1);
    	sortedArr = radixSort(inputArr, 3);		

        let firstStr = sortedArr[0];
        let lastStr = sortedArr[sortedArr.length - 1];
        let letter = mostPopularLetter(sortedArr);

        console.log(`${firstStr}${letter}${lastStr}`);

    } else {
        console.log(err);
    }

});


function radixSort(arr, digit){
    let d = 0;
    let sortedArr = [];

    for(d = digit - 1; d >= 0 ; d--) { 
        
        //countingSort
        let arrByCurrentDigit = arr.map((item) => item.charCodeAt(d) - 97);
        let maxValueInArr = 'z'.charCodeAt(0) - 97;
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
    return sortedArr;
}


function mostPopularLetter(arr) {
    let str = arr.join('');
    let i = 0; 
    let freq = [];

    for (i = 0; i < str.length; i++) {
        freq[str[i].charCodeAt(0) - 97] = freq[str[i].charCodeAt(0) - 97] + 1 || 1;
    }

    let max = Math.max(...freq);
    let index = freq.indexOf(max);
    let letter = String.fromCharCode(index + 97);

    return letter;
}