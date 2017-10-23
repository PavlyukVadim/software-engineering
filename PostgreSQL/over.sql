--Tables: contracts and programs from DB 'distributionOfSoftware'

-- add column quantity to table contracts
ALTER TABLE contracts
ADD COLUMN quantity integer;

UPDATE contracts
SET "quantity" = "contract_id" * floor(random() * 10 + 1)

--output quantity of every programs in contracts

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


-- output date of last order of every program

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

-- output avg sum of program between 1 preceding and 1 following
CREATE VIEW "table-with-total-sum" AS
    SELECT
  *,
  floor("price" * "quantity" * 100) / 100 as "total_sum"
FROM contracts 
JOIN programs
USING("program_id");


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
ORDER BY "program_id"
--------------------

