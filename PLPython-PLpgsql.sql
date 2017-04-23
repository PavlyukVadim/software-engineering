CREATE EXTENSION plpythonu

CREATE LANGUAGE plpythonu




--Task1
CREATE FUNCTION getFullName()
  RETURNS text
AS $$
  return 'Pavlyuk Vadim Ruslanovych'
$$ LANGUAGE plpythonu;

--Task1.2
CREATE FUNCTION myFullName() RETURNS text AS $$
DECLARE
  fullname text := 'Pavlyuk Vadim Ruslanovych';
BEGIN
  RETURN fullname;
END;
$$ LANGUAGE plpgsql;

SELECT myFullName();


--Task2
CREATE OR REPLACE FUNCTION filterByGender(char(1)) RETURNS SETOF text AS
$BODY$
DECLARE
  r employees%rowtype;
BEGIN
    FOR r IN
	  SELECT * FROM employees
    LOOP
      IF $1 = 'M' AND r."TitleOfCourtesy" IN ('Mr.', 'Dr.') THEN 
	      RETURN NEXT r."FirstName"  || ' ' || r."LastName"; 
	    ELSIF $1 = 'F' AND r."TitleOfCourtesy" IN ('Mrs.', 'Ms.') THEN
	      RETURN NEXT r."FirstName" || ' ' || r."LastName"; 
	    ELSIF NOT($1 = 'F' OR $1 = 'M') THEN
	      RETURN NEXT 'Invalid data';  
	      EXIT;    
      END IF;
    END LOOP;
    RETURN;
END
$BODY$
LANGUAGE plpgsql;

SELECT * FROM filterByGender('F');


--Task3
CREATE OR REPLACE FUNCTION getOrdersByPeriod(fromDate text DEFAULT '', toDate text DEFAULT '') RETURNS SETOF Orders AS
$BODY$
DECLARE
  r orders%rowtype;
BEGIN
  IF (fromDate <> '' AND toDate <> '') THEN
		FOR r IN
		  SELECT * FROM orders
		LOOP
	    IF r."OrderDate" BETWEEN fromDate::date AND toDate::date THEN
        RETURN NEXT r; 
	    END IF;
		END LOOP;
		RETURN;
  ELSE
		FOR r IN
	    SELECT * FROM orders
		LOOP
	    IF date_part('day', r."OrderDate"::timestamp) = date_part('day', NOW()) THEN
	      RETURN NEXT r; 
	    END IF;
		END LOOP;
		RETURN;	
  END IF;
END
$BODY$
LANGUAGE plpgsql;

SELECT * FROM getOrdersByPeriod('1996-07-04', '1996-07-10');


--Task4
﻿CREATE TYPE result("ProductName" character varying(40), "CategoryName" character varying(15));

CREATE OR REPLACE FUNCTION getProductsByCategories(integer DEFAULT 0, integer DEFAULT 0, integer DEFAULT 0, integer DEFAULT 0, integer DEFAULT 0) RETURNS SETOF result AS
$BODY$
BEGIN
  RETURN QUERY
  	SELECT "ProductName", "CategoryName" FROM Products
		  LEFT JOIN categories USING("CategoryID") 
		  WHERE "CategoryID" IN ($1, $2, $3, $4, $5) Order By "CategoryID";
END;
$BODY$
LANGUAGE plpgsql;

SELECT * FROM getProductsByCategories(1, 2, 3, 4);


--Task5
--Example
ALTER FUNCTION tenMostExpensiveProducts(integer, ...) SET allData = (SELECT ..., "CompanyName", "CategoryName" FROM ... LEFT JOIN categories USING("CategoryID") 
	LEFT JOIN suppliers USING("SupplierID")); 
/* ... - relevant fields in tenMostExpensiveProducts*/


--Task6
CREATE OR REPLACE FUNCTION concatDataOfEmployees(TitleOfCourtesy character varying(25), FirstName character varying(10), LastName character varying(20)) RETURNS character varying(55) AS
$BODY$
BEGIN
  RETURN TitleOfCourtesy || ' ' || FirstName || ' ' || LastName;
END;
$BODY$
LANGUAGE plpgsql;

SELECT concatDataOfEmployees('Dr.', 'Yevhen', 'Nedashkivskyi');


--Task7
CREATE OR REPLACE FUNCTION getFinalPrice(UnitPrice double precision, Quantity integer, Discount double precision) RETURNS double precision AS
$BODY$
BEGIN
  RETURN UnitPrice * Quantity * (1 - Discount);
END;
$BODY$
LANGUAGE plpgsql;


--Task8
CREATE FUNCTION toPascalCase(str text)
  RETURNS text
AS $$
  return  ''.join(x for x in str.title() if not x.isspace())
$$ LANGUAGE plpythonu;


--Task9
CREATE OR REPLACE FUNCTION getEmployeeInfo(country char(20)) RETURNS SETOF employees AS
$BODY$
BEGIN
  RETURN QUERY
    SELECT * FROM Products WHERE "Country" = country;
END;
$BODY$
LANGUAGE plpgsql;


--Task10
CREATE OR REPLACE FUNCTION getCustomers(company char(40)) RETURNS SETOF customers AS
$BODY$
BEGIN
  RETURN QUERY
		SELECT * FROM customers
			WHERE "CompanyName" = company
END;
$BODY$
LANGUAGE plpgsql;
