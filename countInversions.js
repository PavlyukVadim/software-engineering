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

console.log( sortAndCountInv(arr, 1, arr.length) );