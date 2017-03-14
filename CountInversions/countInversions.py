import math

def mergeAndCountSplitInv(arr, p, q, r):
    lArr = arr[p - 1 : q]
    rArr = arr[q : r]
    lArr.append(float("inf"))
    rArr.append(float("inf"))

    c = i = j = 0 
    k = p - 1
    
    while k < r:
        if lArr[i] <= rArr[j]:
            arr[k] = lArr[i]
            i += 1
        else:
            arr[k] = rArr[j]
            j += 1
            c = c + (len(lArr) - i - 1)
        k += 1
    return c


def sortAndCountInv(arr, p, r):	
    if p == r: 
        return 0
    q = int(math.floor((p + r) / 2))
    x = sortAndCountInv(arr, p, q)
    y = sortAndCountInv(arr, q + 1, r)
    z = mergeAndCountSplitInv(arr, p, q, r)
    return x + y + z


def sortBySecondCell(arr):
    return arr[1]

        
def countInversions(rows, fRow, sRow):
    tempArr = []
    i = 0
    for number in rows[fRow - 1]:
       tempArr.append([number, rows[sRow - 1][i]])
       i += 1
    tempArr.sort(key=sortBySecondCell)
    tempArr = map(lambda x:x[0], tempArr)
    result = sortAndCountInv(tempArr, 1, len(tempArr))
    return result 

    
def countAllInversions(rows, bRow):
    i = 0
    result = []
    while (i < len(rows)):
        if (i != bRow - 1):
            result.append([i + 1, countInversions(rows, bRow, i + 1)])
        else: result.append([i + 1, ' '])
        i += 1
        result.sort(key=sortBySecondCell)
    return result


def main(inputFile, outputFile):
    f = open(inputFile, 'r')    
    metaData = f.readline()[:-1].split(' ')
    metaData = map(lambda x:int(x), metaData)    
    numberOfRows = metaData[0]
    rows = []
    i = 0
    while(i < numberOfRows):
        row = f.readline()[:-1].split(' ')
        row.pop(0)
        rows.append(map(lambda x:int(x), row))
        i += 1
    f.close()
    result = countAllInversions(rows, 1)    
    f = open(outputFile, 'w')
    f.write('1\n')
    i = 0
    while(i < len(result)):
        f.write(str(result[i][0]) + ' ' + str(result[i][1]) + '\n')
        i += 1
    f.close()    
    print result
    
main('data_examples/input_10_5.txt', 'countInversions_output.txt')