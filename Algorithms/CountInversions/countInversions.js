function sortAndCountInv(arr, p, r) {	
	if (p == r) {
		return 0;
	}
	var	q = Math.floor( (p + r) / 2 );
	console.log(p, q, r, arr.slice(p - 1, q), arr.slice(q, r));
	var x = sortAndCountInv(arr, p, q);
	var y = sortAndCountInv(arr, q + 1, r);
	var z = mergeAndCountSplitInv(arr, p, q, r);			
	return x + y + z;
}

function mergeAndCountSplitInv(arr, p, q, r) {
	var lArr = arr.slice(p - 1, q);
	var rArr = arr.slice(q, r);
	console.log(arr);
	var c = 0;

	lArr.push(1/0);
	rArr.push(1/0);

	var i = 0, j = 0;
	for (var k = p - 1; k < r; k++) {
		if (lArr[i] <= rArr[j]) {
			arr[k] = lArr[i];
			i++;
		}
		else{
			arr[k] = rArr[j];
			j++;
			c = c + (lArr.length - i - 1);	
		}
	}
	return c;
	//console.log(p, q, r, arr, lArr, rArr);
}

//console.log( sortAndCountInv(arr, 1, arr.length) );


var str618 = "78 96 1 7 22 80 81 30 40 52 8 45 31 17 65 55 76 33 88 75 50 37 32 34 5 60 26 43 92 41 57 63 44 67 54 47 12 53 77 87 83 13 49 79 35 66 99 74 72 70 15 39 28 73 84 95 24 71 97 9 19 94 36 48 62 3 86 21 10 64 82 98 38 18 20 91 16 42 2 68 59 29 27 100 85 14 90 56 89 25 46 58 69 51 23 93 61 4 11 6";
var str1 = "92 3 36 84 51 7 100 10 69 2 23 27 68 19 1 42 59 57 39 55 89 9 11 88 85 86 31 47 12 28 16 24 41 71 44 91 5 29 37 94 4 87 25 76 49 30 6 72 22 46 79 15 35 56 67 62 73 97 13 77 93 80 60 96 48 14 66 20 32 74 54 8 78 52 83 45 75 17 34 98 95 63 58 38 61 18 53 33 90 43 82 81 99 26 64 40 70 65 21 50";

var arr618 = str618.split(' ').map((el) => el - '');
var arr1 = str1.split(' ').map((el) => el - '');

var invStruct = [];
arr618.forEach((number, i, arr) => {
	invStruct.push({index: number, value: arr1[i]});
})

invStruct.sort((a, b) => {
	return a.index - b.index;
})

var normalizedArr = invStruct.map((el) => el.value);

console.log( sortAndCountInv(normalizedArr, 1, normalizedArr.length) );