-- change table columns
ALTER TABLE contracts
DROP COLUMN IF EXISTS contract_date
CASCADE;

ALTER TABLE contracts 
ADD COLUMN year int,
ADD COLUMN month int;

-- fill table
INSERT INTO contracts ("client_id", "program_id", "quantity", "year", "month") VALUES 
  (1, 3, 1, 2007, 1),
  (1, 4, 2, 2007, 2),
  (2, 5, 3, 2008, 8),
  (2, 6, 4, 2009, 11),
  (3, 3, 2, 2007, 10);


-- output max quantity for every month
CREATE EXTENSION tablefunc;
SELECT * FROM crosstab(
  'SELECT 
    year,
    month,
    max(quantity)
  FROM contracts
  GROUP BY
    year,
    month,
    quantity
  ORDER BY 1',
  'SELECT m FROM generate_series(1,12) m'
) AS (
  year int,
  "Jan" int,
  "Feb" int,
  "Mar" int,
  "Apr" int,
  "May" int,
  "Jun" int,
  "Jul" int,
  "Aug" int,
  "Sep" int,
  "Oct" int,
  "Nov" int,
  "Dec" int
);



with contracts_max_month_quantity as (
  (SELECT * FROM crosstab(
    'SELECT 
      year,
      month,
      max(quantity)
    FROM contracts
    GROUP BY
      year,
      month,
      quantity
    ORDER BY 1',
    'SELECT m FROM generate_series(1,12) m'
  ) AS (
    year int,
    "Jan" int,
    "Feb" int,
    "Mar" int,
    "Apr" int,
    "May" int,
    "Jun" int,
    "Jul" int,
    "Aug" int,
    "Sep" int,
    "Oct" int,
    "Nov" int,
    "Dec" int
  ))
)
SELECT * FROM contracts_max_month_quantity;


with contracts_max_month_quantity as (
  (SELECT * FROM crosstab(
    'SELECT 
      year,
      month,
      max(quantity)
    FROM contracts
    GROUP BY
      year,
      month,
      quantity
    ORDER BY 1',
    'SELECT m FROM generate_series(1,12) m'
  ) AS (
    year int,
    "Jan" int,
    "Feb" int,
    "Mar" int,
    "Apr" int,
    "May" int,
    "Jun" int,
    "Jul" int,
    "Aug" int,
    "Sep" int,
    "Oct" int,
    "Nov" int,
    "Dec" int
  ))
), contracts_avr_month_price as (
  (SELECT * FROM crosstab(
    'SELECT 
      year,
      month,
      (avg(price))::int AS price
    FROM contracts
    JOIN programs
    USING(program_id)
    GROUP BY
      year,
      month,
      price
    ORDER BY 1',
    'SELECT m FROM generate_series(1,12) m'
  ) AS (
    year int,
    "Jan" int,
    "Feb" int,
    "Mar" int,
    "Apr" int,
    "May" int,
    "Jun" int,
    "Jul" int,
    "Aug" int,
    "Sep" int,
    "Oct" int,
    "Nov" int,
    "Dec" int
  ))
)
SELECT
  year,
  mq."Jan" AS "Jan MaxQnt", mp."Jan" AS "Jan AvgPrice",
  mq."Feb" AS "Feb MaxQnt", mp."Feb" AS "Feb AvgPrice",
  mq."Mar" AS "Mar MaxQnt", mp."Mar" AS "Mar AvgPrice",
FROM contracts_max_month_quantity mq
JOIN contracts_avr_month_price mp
USING(year);
