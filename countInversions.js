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

console.log( sortAndCountInv(arr, 1, arr.length) );