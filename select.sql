--Task1
--Print firstname, middlename, lastname
SELECT 'Vadim' AS FirstName,
	   'Ruslanovych' AS MiddleName,
	   'Pavlyuk' AS LastName

--Task2
--All data from Products
SELECT * FROM products

--Task3
--select all that are discontinued from products
SELECT * FROM products
WHERE "Discontinued" = 1

--Task4
--All unique customers cities
SELECT DISTINCT "City" FROM Customers

--Task5
--select all companynames in decreasing way
SELECT DISTINCT "CompanyName" FROM Suppliers
ORDER BY "CompanyName" DESC

--TASK6
--get all orders, change columns for numbers
SELECT "OrderID" AS "1",
       "ProductID" AS "2",
       "UnitPrice" AS "3",
       "Quantity" AS "4",
       "Discount" AS "5"
FROM order_details

--Task7
--all contact names that begin with the letter P,V,R 
SELECT "ContactName" FROM Customers
WHERE "ContactName" SIMILAR TO '(V|P|R)%'

--Task8
--select all orders where _ is detected in address
SELECT * FROM Orders 
WHERE "ShipAddress" LIKE '% %'

--Task9
--select all products that start with % or _ and end on 'm'
SELECT "ProductName" FROM Products
WHERE "ProductName" SIMILAR TO '(\%|\_)m'