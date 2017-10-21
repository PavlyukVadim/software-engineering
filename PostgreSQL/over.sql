--Tables: contracts and programs from DB 'distributionOfSoftware'


--output quantity of every programs in contracts

SELECT DISTINCT 
  "program_id",
  count(*) OVER (PARTITION BY "program_id" ORDER BY "program_id" DESC) AS quantity
FROM contracts 
JOIN programs
USING("program_id") 
ORDER BY "program_id";

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

SELECT
  "program_id",
  MAX(contract_date)
FROM contracts
JOIN programs
USING("program_id") 
GROUP BY "program_id"
ORDER BY "program_id"


--
