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


