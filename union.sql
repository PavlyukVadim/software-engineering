--Task 1.1

SELECT 'Pavlyuk' AS Name
UNION SELECT 'Vadim Ruslanovych'


--Task 1.2

DO $$
BEGIN
  IF ((SELECT "studentID" 
      FROM students
      WHERE "surname" = 'Pavlyuk') > ALL (SELECT "studentID" 
					  FROM students 
					  WHERE NOT "surname" = 'Pavlyuk')) THEN
   RAISE NOTICE ';-)';
  ELSE
   RAISE NOTICE ':-D';
  END IF;
END $$;


--Task 1.3
DO $$
DECLARE
   id integer = 1; 
   name text = '';
   surname text = ''; 
BEGIN
  WHILE (id < (SELECT count("StudentID") from studentsIP51 where "sex" = 'F')) LOOP
    IF (id in (SELECT "StudentID" from studentsIP51 where "sex" = 'F'))) THEN
      name = (SELECT "StudentName" from studentsIP51 where "StudentID" = id);
      surName = (SELECT "StudentSurname" from studentsIP51 where "StudentID" = id);
      IF (NOT name IN (SELECT "StudentName" from studentsIP52)) THEN 
        RAISE NOTICE 'name: (%) surname: (%)', name, surname;
      END IF;
      id = id + 1;
    END IF;
  END LOOP;
END $$;


--Task 1.4

SELECT *, CASE "ProductID" 
  WHEN 0 THEN 'NULL'
  WHEN 1 THEN 'ONE'
  WHEN 2 THEN 'TWO'
  WHEN 3 THEN 'THREE'
  WHEN 4 THEN 'FOUR'
  WHEN 5 THEN 'FIVE'
  WHEN 6 THEN 'SIX'
  WHEN 7 THEN 'SEVEN'
  WHEN 8 THEN 'EIGHT'
  WHEN 9 THEN 'NINE'
  ELSE "ProductID"::text
END AS "ProductID" 
FROM products


--Task 1.5

SELECT "ProductName", "CategoryName" FROM products, categories;


--Task 2.1

--Task 2.2

SELECT "Country" FROM Customers
UNION
SELECT "Country" FROM Employees
UNION
SELECT "ShipCountry" FROM Orders
ORDER BY "Country"


--Task 2.3

SELECT "LastName", "FirstName", count (*) AS NumberOfOrders FROM Employees AS e
JOIN Orders AS o ON (o."EmployeeID" = e."EmployeeID") 
WHERE o."OrderDate" BETWEEN '1998-01-01' AND '1998-03-31' 
GROUP BY e."LastName", e."FirstName";


--Task 2.4


--Task 2.5

SELECT "ProductName" FROM products
WHERE "ProductName" NOT IN (SELECT pr."ProductName" FROM Products AS pr
  JOIN Order_Details AS od ON (od."ProductID" = pr."ProductID")
  JOIN Orders AS o ON (o."OrderID" = od."OrderID")
  JOIN Employees AS e ON (e."EmployeeID" = o."EmployeeID")
  JOIN EmployeeTerritories AS et ON (et."EmployeeID" = e."EmployeeID")
  JOIN Territories AS t ON (t."TerritoryID" = et."TerritoryID")
  JOIN Region AS r ON (r."RegionID" = t."RegionID")
  WHERE r."RegionDescription" = 'Southern'
)
