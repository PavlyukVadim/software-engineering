--Task1
CREATE OR REPLACE FUNCTION count_rows(schema text, tablename text) returns integer
AS
$body$
declare
  result integer;
  query varchar;
BEGIN
  query := 'SELECT count(1) FROM ' || schema || '.' || tablename;
  execute query into result;
  return result;
END;
$body$
language plpgsql;

SELECT 
  table_schema,
  table_name, 
  count_rows(table_schema, table_name)
FROM information_schema.tables
WHERE 
  table_schema not in ('pg_catalog', 'information_schema') 
  AND table_type='BASE TABLE'
ORDER BY 3 DESC


--Task2
CREATE OR REPLACE FUNCTION grantReadingToEverybody() RETURNS integer AS $$
DECLARE
  userData RECORD;
BEGIN
  RAISE NOTICE 'Start';
  FOR userData IN SELECT * FROM pg_shadow LOOP
    EXECUTE format('GRANT SELECT ON ALL TABLES IN SCHEMA public TO %I', userData.usename);
  END LOOP;
  RAISE NOTICE 'Done';
  RETURN 1;
END;
$$ LANGUAGE plpgsql;


--Task3
--Since FOR loops automatically use a cursor internally to avoid memory problems
CREATE OR REPLACE FUNCTION denyAllForTestUser() RETURNS integer AS $$
DECLARE
  tableData RECORD;
BEGIN
  FOR tableData IN SELECT table_name FROM information_schema.tables 
    WHERE table_schema NOT IN ('pg_catalog', 'information_schema') 
    AND table_type='BASE TABLE' AND table_name ~ '^prod_' LOOP
    EXECUTE format('DENY ALL ON %I TO TestUser', tableData.table_name);
  END LOOP;
  RETURN 1;
END;
$$ LANGUAGE plpgsql;


--Task4
CREATE TYPE productinfo AS (productname character varying(40), quantity smallint, totalprice real);
--Function for getting all products by orderId or 1 product by orderId, productId
CREATE OR REPLACE FUNCTION getProductsByOrderId(orderId integer, productId integer) RETURNS SETOF productinfo as
$$
BEGIN
   IF productId IS NULL THEN
   RETURN QUERY
  	SELECT "ProductName", "Quantity"::smallint, ("Quantity" * order_details."UnitPrice" * (1 - "Discount"))::real as "totalprice" FROM order_details
		  LEFT JOIN products USING("ProductID") 
		  WHERE order_details."OrderID" = orderId;
   ELSE 
	RETURN QUERY
  	SELECT "ProductName", "Quantity"::smallint, ("Quantity" * order_details."UnitPrice" * (1 - "Discount"))::real as "totalprice" FROM order_details
		  LEFT JOIN products USING("ProductID") 
		  WHERE order_details."OrderID" = orderId And order_details."ProductID" = productId;
   END IF;
END
$$ language 'plpgsql';

CREATE OR REPLACE FUNCTION getAllProductsByOrderIds() RETURNS SETOF productinfo as
$$
DECLARE
  r order_details%rowtype;
BEGIN
    FOR r IN
	 SELECT * FROM order_details
    LOOP
	 RETURN NEXT getProductsByOrderId(r."OrderID"::integer, r."ProductID"::integer); 
    END LOOP;
    RETURN;
END
$$ language 'plpgsql';

SELECT * From getProductsByOrderId(11083)
SELECT * From getAllProductsByOrderIds()


--Task5
--In postgresql we don't have access to all tables. 
--We should change connection every time to have access to particular db. 
--We can do it in function, but it won't be independent way.
CREATE OR REPLACE FUNCTION changeConnection() RETURNS integer as
$$
DECLARE
  tableData RECORD;
BEGIN
    FOR tableData IN SELECT table_name FROM information_schema.tables 
	WHERE table_schema NOT IN ('pg_catalog', 'information_schema') 
	AND table_type='BASE TABLE' LOOP
    EXECUTE format('TRUNCATE %I', tableData.table_name);
    END LOOP;
    RETURN 1;
END
$$ language 'plpgsql';
SELECT * FROM changeConnection();


--Task6
CREATE OR REPLACE FUNCTION validation_phone() RETURNS trigger as
$$
BEGIN
    NEW."Phone" = regexp_replace(NEW."Phone", '[^0-9]', '', 'g');
    return NEW;
END
$$ language 'plpgsql';

CREATE trigger validation_phone_trigger
before INSERT on customers
    for each row
    execute procedure validation_phone();


--Task7
CREATE OR REPLACE FUNCTION validation_discount() RETURNS trigger as
$$
DECLARE
  price real;
BEGIN
    price = SUM("Quantity" * "UnitPrice") FROM order_details
		WHERE "OrderID" = NEW."OrderID";
    IF (TG_OP = 'INSERT') THEN
        UPDATE order_details
		SET "Discount" = CASE
							WHEN price > 100 THEN 0.05
							WHEN price > 500 THEN 0.15
							WHEN price > 1000 THEN 0.25
							ELSE 0
			 			END
 		WHERE "OrderID" = NEW."OrderID";
		RETURN NEW;
    END IF;
    RETURN NULL; -- result is ignored since this is an AFTER trigger
END
$$ language 'plpgsql';

CREATE trigger validation_discount_trigger
after INSERT on order_details
    for each row
    execute procedure validation_discount();

INSERT into order_details ("OrderID", "ProductID", "UnitPrice", "Quantity", "Discount") values
	(11083, 1, 20, 3, 0),
	(11083, 2, 20, 3, 0);
SELECT * from order_details;


--Task8
CREATE TABLE Contacts (
    ContactId bigint not null,
    LastName character(255) not null,
    FirstName character(255) not null,
    PersonalPhone character(15),
    WorkPhone character(15),
    Email character(20),
    PreferableNumber character(15)
);

CREATE OR REPLACE FUNCTION set_preferable_number() RETURNS trigger as
$$
BEGIN
    NEW."preferablenumber" = COALESCE(NEW."workphone", NEW."personalphone"); 
    return NEW;
END
$$ language 'plpgsql';

CREATE trigger set_preferable_number_trigger
before INSERT on Contacts
    for each row
    execute procedure set_preferable_number();


--Task9
SELECT * INTO OrdersArchive FROM Orders
DELETE FROM OrdersArchive

ALTER TABLE OrdersArchive
ADD COLUMN "DeletionDateTime" date, 
ADD COLUMN "DeletedBy" character(20);

CREATE OR REPLACE FUNCTION save_in_archive() RETURNS trigger as
$$
BEGIN
    INSERT into OrdersArchive SELECT OLD.*, now(), user;
    return NULL;
END
$$ language 'plpgsql';

CREATE trigger save_in_archive_trigger
after DELETE on Orders
    for each row
    execute procedure save_in_archive();

DELETE FROM Orders Where "OrderID" = 11077;
SELECT * FROM OrdersArchive;


--Task10
CREATE TABLE TriggerTable1 (
    TriggerId BIGSERIAL PRIMARY KEY not null,
    TriggerDate date not null
);

CREATE TABLE TriggerTable2 (
    TriggerId BIGSERIAL PRIMARY KEY not null,
    TriggerDate date not null
);

CREATE TABLE TriggerTable3 (
    TriggerId BIGSERIAL PRIMARY KEY not null,
    TriggerDate date not null
);

CREATE OR REPLACE FUNCTION trigger_function1() RETURNS trigger as
$$
BEGIN
    INSERT into TriggerTable2 ("triggerdate") values(now());
    return NULL;
END
$$ language 'plpgsql';

CREATE OR REPLACE FUNCTION trigger_function2() RETURNS trigger as
$$
BEGIN
    INSERT into TriggerTable3 ("triggerdate") values(now());
    return NULL;
END
$$ language 'plpgsql';

CREATE OR REPLACE FUNCTION trigger_function3() RETURNS trigger as
$$
BEGIN
    INSERT into TriggerTable1 ("triggerdate") values(now());
    return NULL;
END
$$ language 'plpgsql';

CREATE trigger trigger1
after INSERT on TriggerTable1
    for each row
    execute procedure trigger_function1();

CREATE trigger trigger2
after INSERT on TriggerTable2
    for each row
    execute procedure trigger_function2();

CREATE trigger trigger3
after INSERT on TriggerTable3
    for each row
    execute procedure trigger_function3();

INSERT into TriggerTable1 ("triggerdate") values(now());
SELECT * from TriggerTable1
SELECT * from TriggerTable1
SELECT * from TriggerTable3
--Nothing happened (insertion only in TriggerTable1)
--To prevent endless insertions in every table 
--postgreSQL doesn't execute insertion in table TriggerTable2.
