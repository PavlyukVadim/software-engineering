function mergeSort(arr, p, r) {
	var q;
	if (p < r) {
		q = Math.floor( (p + r) / 2 );
		//console.log('MergeLeft')
		mergeSort(arr, p, q);
		//console.log('MergeRight')	
		mergeSort(arr, q + 1, r);
		//console.log('Merge')
		merge(arr, p, q, r);			
	}
	return arr;
}

function merge(arr, p, q, r) {
	var lArr = arr.slice(p - 1, q);
	var rArr = arr.slice(q, r);
	
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
		}
	}
	//console.log(p, q, r, arr, lArr, rArr);
}
var arr = [1,5,8,5,4,5,11];
console.log( mergeSort(arr, 1, arr.length) );