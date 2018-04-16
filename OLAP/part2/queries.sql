-- 1
SELECT
	p."product_id",
	sum(o."quantity" * p."price") AS total
FROM
	"Sales" s
JOIN
	"Orders" o
	ON
		s."order_id" = o."order_id"
	JOIN "Product" p
		ON
			p."product_id" = o."product_id"
GROUP BY p."product_id"
ORDER BY p."product_id";

-- 2
SELECT
	"name" 
FROM
	"Company"
WHERE
	"company_id" NOT IN
(
	SELECT
		p."company_id"
	FROM
		"Sales" s
	JOIN "Orders" o
		ON
			o."order_id" = s."order_id"
		JOIN "Product" p
			ON
				p."product_id" = o."product_id"
)

-- 3
SELECT DISTINCT
	"name",
	"product_id"
FROM
	"Product"
WHERE
	"product_id"
	IN
(
	SELECT o."product_id"
	FROM "Sales" s
	JOIN "Orders" o ON o."order_id" = s."order_id"
	Where o."product_id" NOT IN
	(
		SELECT o."product_id"
		FROM "Sales" s
		JOIN "Orders" o ON o."order_id" = s."order_id"
		WHERE EXTRACT(month FROM TO_DATE(s."sale_date", '/dd/mm/yy')) > 6
	)
);

-- 4
SELECT *
FROM
(
	SELECT
		c."client_id",
		c."full_name",
		count("order_id") AS "count"
	FROM "Sales" s 
	JOIN "Clients" c ON c."client_id" = s."client_id"
	GROUP BY c."client_id", c."full_name"
	ORDER BY "count" DESC
)
WHERE rownum <= 5;

-- 5
SELECT
	st."full_name",
	st."staff_id"
FROM
	"Staff" st
JOIN
	"Sales" sl ON st."staff_id" = sl."staff_id"
JOIN
	"Orders" ord ON ord."order_id" = sl."order_id"
GROUP BY
	st."full_name",
	st."staff_id"
HAVING
	SUM(ord."quantity")
		IN (
			SELECT * FROM (
				SELECT SUM(ord."quantity")
				FROM
					"Staff" st
				JOIN
					"Sales" sl ON st."staff_id" = sl."staff_id"
				JOIN
					"Orders" ord ON ord."order_id" = sl."order_id"
				GROUP BY st."staff_id"
				ORDER BY SUM(ord."quantity")
				DESC
			)
			WHERE rownum = 1
		)

-- 6
SELECT * FROM (
	SELECT
		st."full_name",
		st."staff_id",
		count(*) as sum
	FROM
		"Staff" st
	JOIN
		"Sales" sl ON st."staff_id" = sl."staff_id"
	JOIN
		"Orders" ord ON ord."order_id" = sl."order_id"
	GROUP BY st."full_name", st."staff_id"
	ORDER BY sum
	DESC
)
WHERE rownum <= 3

-- 7
SELECT
	avg(p."price" * o."quantity")
FROM
	"Sales" s
JOIN
	"Orders" o ON o."order_id" = s."order_id"
JOIN
	"Product" p ON p."product_id" = o."product_id";

-- 8
SELECT
	"staff_id",
	AVG("count")
FROM
(
	SELECT
		s."staff_id",
		s."sale_date",
		count("order_id") AS "count"
	FROM "Sales" s
	GROUP BY s."staff_id", s."sale_date"
)
GROUP BY "staff_id";

-- 9
SELECT
	"shelf"
FROM
(
	SELECT
		"shelf",
		count("product_id") AS "count"
	FROM
		"Store"
	GROUP BY "shelf"
)
WHERE "count" = 1;

-- 10
SELECT *
FROM
(
	SELECT *
	FROM
	(
		SELECT
			p."product_id",
			p."price" AS koef ,
			'the most expensive' AS title
		FROM
			"Sales" s
		JOIN "Orders" o ON o."order_id" = s."order_id"
		JOIN "Product" p ON p."product_id" = o."product_id"
		ORDER BY p."price" DESC
	)
	WHERE rownum = 1
)
UNION
(
	SELECT
		p."product_id",
		"sum",
		'the most popular'
	FROM "Product" p
	JOIN
	(
		SELECT
			o."product_id",
			sum(o."quantity") AS "sum"
		FROM "Sales" s 
		JOIN "Orders" o ON o."order_id" = s."order_id"
		GROUP BY o."product_id"
		ORDER BY "sum" DESC
	) q
	ON p."product_id" = q."product_id"
	WHERE rownum = 1
)
