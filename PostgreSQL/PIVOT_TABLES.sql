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
