--Tables: contracts and programs from DB 'distributionOfSoftware'

-- add column quantity to table contracts
ALTER TABLE contracts
ADD COLUMN quantity integer;

UPDATE contracts
SET "quantity" = "contract_id" * floor(random() * 10 + 1)


-- 1. output quantity of every programs in contracts

SELECT DISTINCT 
  "program_id",
  count(*) OVER (PARTITION BY "program_id" ORDER BY "program_id" DESC) AS quantity
FROM contracts 
JOIN programs
USING("program_id") 
ORDER BY "program_id";
-------------------
SELECT DISTINCT 
  "program_id",
  count(*) AS quantity
FROM contracts 
JOIN programs
USING("program_id") 
GROUP BY "program_id"
ORDER BY "program_id" 


-- 2. output date of last order of every program

SELECT * 
FROM (
  SELECT 
    "program_id",
    "contract_date",
    rank() OVER (PARTITION BY "program_id" ORDER BY "contract_date" DESC) AS rank
  FROM contracts
  JOIN programs
  USING("program_id")
  ORDER BY "program_id"
) top_by_contract_date
WHERE contract_date_rank < 2;
---------------------
SELECT
  "program_id",
  MAX(contract_date)
FROM contracts
JOIN programs
USING("program_id") 
GROUP BY "program_id"
ORDER BY "program_id"
--


-- 3. output avg sum of program between 1 preceding and 1 following

CREATE VIEW "table-with-total-sum" AS
 SELECT
  "program_id",
  "contract_id",
  "contract_date",
  ROW_NUMBER() OVER (ORDER BY "program_id", "contract_id") AS "row_count",
  floor("price" * "quantity" * 100) / 100 as "total_sum"
FROM contracts 
JOIN programs
USING("program_id")
GROUP BY "program_id", "contract_id",  "contract_date", "price", "quantity"
ORDER BY "program_id", "contract_id";


SELECT DISTINCT 
  "program_id",
  "contract_id",
  "contract_date",
  avg("total_sum") OVER (
    PARTITION BY "program_id"
    ORDER BY "contract_date"
    ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING
  ) AS "avg_total_sum"
FROM "table-with-total-sum"
ORDER BY "program_id", "contract_id"
--------------------
SELECT DISTINCT 
  t1."program_id",
  t1."contract_id",
  t1."contract_date",
  avg(t2."total_sum") AS "avg_total_sum"
FROM "table-with-total-sum" as t1, "table-with-total-sum" as t2
WHERE t2."row_count" BETWEEN t1."row_count" - 1 AND t1."row_count" + 1
      AND t2."program_id" = t1."program_id"
GROUP BY t1."program_id", t1."contract_id", t1."contract_date"
ORDER BY t1."program_id", t1."contract_id"


-- 4. output avg sum by each program
SELECT DISTINCT 
  "program_id",
  "contract_id",
  "contract_date",
  avg("total_sum") OVER (
    PARTITION BY "program_id"
    RANGE CURRENT ROW
  ) AS "avg_total_sum"
FROM "table-with-total-sum"
ORDER BY "program_id", "contract_id"
---------------------
SELECT DISTINCT 
  t1."program_id",
  t1."contract_id",
  t1."contract_date",
  avg(t2."total_sum") AS "avg_total_sum"
FROM "table-with-total-sum" as t1, "table-with-total-sum" as t2
WHERE t2."program_id" = t1."program_id"
GROUP BY t1."program_id", t1."contract_id", t1."contract_date"
ORDER BY t1."program_id", t1."contract_id"


-- 5.6. output avg sum of first and last programs
SELECT AVG("total_sum") FROM (
  SELECT
    "total_sum","program_id", "contract_date",
    LAG("total_sum", 1) OVER (Order by "program_id", "contract_date") AS "prev-sum",
    LEAD("total_sum", 1) OVER (Order by "program_id", "contract_date") AS "next-sum"
  FROM "table-with-total-sum"
) AS t
WHERE "prev-sum" IS NULL OR "next-sum" IS NULL
-------------------
SELECT
  AVG("total_sum")
FROM (
  SELECT * FROM (
    SELECT
      "total_sum",
      "program_id",
      "contract_date"
    FROM "table-with-total-sum"
    ORDER BY
      "program_id" ASC,
      "contract_date" ASC
    LIMIT 1
  ) AS t_with_first
  UNION 
  SELECT * FROM (
    SELECT
      "total_sum",
      "program_id",
      "contract_date"
    FROM "table-with-total-sum"
    ORDER BY
      "program_id" DESC,
      "contract_date" DESC
    LIMIT 1
  ) t_with_last
) AS t


-----------------------
-- Denormalized table by 1 form 
CREATE TABLE d_contracts (
  contract_id bigserial PRIMARY KEY,
  second_client_name character(15) NOT NULL,
  program_name character(15) NOT NULL,
  price character(40) NOT NULL,
  contract_date date 
);

INSERT INTO d_contracts
  ("second_client_name", "program_name", "price", "contract_date")
VALUES 
  ('Smith', 'ClanLib', '100', NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  ('Williams', 'HOOPS', '100 100 100', NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  ('Johnson', 'Horde3D', '20 20', NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  ('Brown', 'Irrlicht', '100', NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days')


-- for normalization add column 'quantity'
ALTER TABLE d_contracts
ADD COLUMN quantity integer

UPDATE d_contracts
SET "quantity" = CASE "price"
  WHEN '100' THEN 1
  WHEN '20 20' THEN 2
  WHEN '100 100 100' THEN 3
  ELSE 0 END

UPDATE d_contracts
SET "price" = CASE "price"
  WHEN '100' THEN '100'
  WHEN '20 20' THEN '20'
  WHEN '100 100 100' THEN '100'
  ELSE 0 END


-- for normalization to 2 form we need to separate client info and
-- info about program to another tables
CREATE TABLE d_clients (
  client_id bigserial PRIMARY KEY,
  second_name character(15) NOT NULL,
  full_name character(40) NOT NULL,
  address character(20) NOT NULL,
  company character(20) NOT NULL
);

INSERT INTO d_clients
  ("second_name", "full_name", "address", "company")
VALUES 
  ('Smith', 'Anthony Smith', '783 E. Fairground', 'company1'),
  ('Williams', 'Daniel Smith', '9680 Edgemont', 'company2'),
  ('Johnson', 'Angel Smith', '7868 Manor', 'company3'),
  ('Brown', 'Jacob Smith', '59 Bohemia Lane', 'company4')

CREATE TABLE d_programs (
  program_id bigserial PRIMARY KEY,
  program_name character(15) NOT NULL,
  program_version character(40) NOT NULL,
  price double precision NOT NULL
);

INSERT INTO d_programs
  ("program_name", "program_version", "price")
VALUES 
  ('ClanLib', '9.4.1', 100),
  ('HOOPS', '5.7.8', 200),
  ('Horde3D', '9.7.7', 300),
  ('Irrlicht', '8.0.1', 100)

ALTER TABLE d_contracts
DROP COLUMN "second_client_name",
DROP COLUMN "program_name",
DROP COLUMN "price"

