-- 1
SELECT * 
FROM
	STORE
WHERE PRODUCT IN 
(
	SELECT
		PRODUCT
	FROM
		STORE
	GROUP BY
		PRODUCT
	HAVING count(SUPPLIER) > 1
)
ORDER BY PRODUCT

-- 2
SELECT *
FROM
	STORE
WHERE SHELF IN 
(
	SELECT
	  SHELF
	FROM
	  STORE
	GROUP BY
		SHELF
  HAVING sum(to_number(QUANTITY)) > 30
)
ORDER BY to_number(SHELF)

-- 3
SELECT *
FROM
	STORE
WHERE
	TO_DATE(STORE_DATE, 'dd.mm.yyyy')
		NOT BETWEEN
			TO_DATE('2011/01/01', 'yyyy/mm/dd')
				AND
			TO_DATE('2014/05/31', 'yyyy/mm/dd')

-- 4
SELECT *
FROM
	INVOICE
WHERE
	NOT
	regexp_like(E_MAIL, '^[a-z0-9.]+@[a-z0-9.]+.[a-z]+$')

-- 5
SELECT 
  in1.ID_STUFF,
  in1.STAFF_NAME,
  in1.E_MAIL,
  in2.ID_STUFF,
  in2.STAFF_NAME,
  in2.E_MAIL
FROM
	INVOICE in1
JOIN
	INVOICE in2 
  ON
  	i1.ID_STUFF = i2.ID_STUFF
	WHERE
		i1.STAFF_NAME != i2.STAFF_NAME
			OR
		i1.E_MAIL != i2.E_MAIL

-- 6
SELECT *
FROM
	STORE
WHERE
	oper_type NOT IN ('In', 'Out')

-- 7
SELECT *
FROM
	INVOICE
WHERE
	price < 1000

-- 8
SELECT *
FROM
	INVOICE
WHERE
	not regexp_like(invoice, 'INV-[0-9]')

-- 9
SELECT * 
FROM
	STORE
WHERE
	not regexp_like(product, 'TV-[0-9]')
