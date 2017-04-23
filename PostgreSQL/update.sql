/*Task 1*/
/*If primary key was created as serial*/
INSERT INTO Employees ("LastName", "FirstName", "Title")
VALUES ('Pavlyuk', 'Vadim', 'Intern');

/*In other case*/
CREATE SEQUENCE employee_sequence
 start 1
 increment 1

INSERT INTO Employees ("EmployeeID", "LastName", "FirstName", "Title")
VALUES (nextval('employee_sequence'), 'Pavlyuk', 'Vadim', 'Intern')


/*Task 2*/
UPDATE Employees
SET "Title" = 'Director'
WHERE "LastName" = 'Pavlyuk'


/*Task 3*/
SELECT * INTO OrdersArchive FROM Orders


/*Task 4*/
TRUNCATE TABLE OrdersArchive


/*Task 5*/
INSERT INTO OrdersArchive SELECT * FROM Orders


/*Task 6*/
DELETE FROM OrdersArchive
WHERE "ShipCity" = 'Berlin'


/*Task 7*/
INSERT INTO Products ("ProductName")
VALUES('Vadim'),('Ip-51');


/*Task 8*/
UPDATE Products
SET 'Discontinued' = 1
WHERE "ProductID" NOT IN (SELECT "ProductID" FROM order_details)


/*Task 9*/
DROP TABLE OrdersArchive


/*Task 10*/
DROP DATABASE Northwind
