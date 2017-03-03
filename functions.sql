-- Task 1
-- 1.1 Count number of rows in table that have more than 2147483647 records
-- PostgreSQL 
SELECT count(*) FROM table_name;
-- MSSQL
SELECT COUNT_BIG(*) FROM [Northwind].[dbo].[table_name]
-- 1.2 Count Number of characters in your surname
SELECT char_length('Pavlyuk') as "Number of characters in 'Pavlyuk'"
-- 1.3 Replace ' ' to '_'
SELECT replace('Pavlyuk Vadim Ruslanovych', ' ', '_')
-- 1.4 Generate e-mail 
SELECT left("surname", 2) || left("firstname", 4) || '@Pavlyuk' AS 'E-mail' FROM table_name
-- 1.5 Day of the week by date
SELECT to_char(timestamp '1998-08-30' ,'Day')
--
-- Task 2
-- 2.1
SELECT * FROM Products AS PR
RIGHT JOIN Categories AS CT ON 
		 'pr.CategoryID' = 'ct.CategoryID'
RIGHT JOIN Suppliers AS SP ON
		 'sp.SupplierID' = 'pr.SupplierID'
-- 2.2
SELECT * FROM Orders
WHERE "ShippedDate" IS NULL AND
      "OrderDate" BETWEEN '1998-04-01' AND timestamp '1998-04-01' + '1 months' - interval '1 days'
-- 2.3

SELECT DISTINCT "LastName", "FirstName"
FROM Employees AS EMP
LEFT JOIN EmployeeTerritories AS ET 
          ON 'et.EmployeeID' = 'emp.EmployeeID'
LEFT JOIN Territories AS T 
          ON 't.TerritoryID' = 'et.TerritoryID'
LEFT JOIN Region AS R 
          ON 'r.RegionID' = 't.RegionID'
WHERE 'r.RegionDescription' = 'Northern' 

-- 2.4
SELECT (SUM("UnitPrice" * (1 - "Discount") * "Quantity") )
FROM Order_Details AS OD
LEFT JOIN Orders AS O 
          ON 'o.OrderID' = 'od.OrderID'
WHERE date_part('day', 'o.OrderDate') % 2 = 1

-- 2.5

SELECT "ShipAddress" FROM Orders 
WHERE "OrderID" = (SELECT "OrderID" FROM Order_Details
                   GROUP BY "OrderID"
                   ORDER BY SUM("UnitPrice" * (1 - "Discount") * "Quantity") DESC
                   fetch first 1 rows only)
