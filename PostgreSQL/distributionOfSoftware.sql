-- distribution of software
-- creating tables

CREATE TABLE clients (
  client_id bigserial PRIMARY KEY,
  second_name character(15) NOT NULL,
  full_name character(40) NOT NULL,
  address character(20) NOT NULL,
  company character(20) NOT NULL
);

CREATE TABLE programs (
  program_id bigserial PRIMARY KEY,
  program_name character(15) NOT NULL,
  program_version character(40) NOT NULL,
  price double precision NOT NULL
);

CREATE TABLE contracts (
  contract_id bigserial PRIMARY KEY,
  client_id bigint references clients("client_id"),
  program_id bigint references programs("program_id"),
  contract_date date 
);

CREATE TABLE deliveries (
  delivery_id bigserial PRIMARY KEY,
  contract_id bigint references contracts("contract_id"),
  delivery_date date 
);


-- function for generation random data 
CREATE OR REPLACE FUNCTION get_random_data(arr text[])
  RETURNS text AS
$$
BEGIN
  RETURN arr[floor(random() * array_length(arr, 1)) + 1];
END
$$ LANGUAGE plpgsql;


-- function for generation data about clients
CREATE OR REPLACE FUNCTION generate_data_for_clients()
  RETURNS void AS
$$
DECLARE
  second_name text := get_random_data(ARRAY['Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 'Davis', 'Miller', 'Wilson', 'Moore', 'Taylor']);
  first_name text := get_random_data(ARRAY['Anthony', 'Daniel', 'Angel', 'Alexander', 'Jacob', 'Michael', 'Ethan', 'Jose', 'Jesus', 'Joshua']);
  address text := get_random_data(ARRAY[
    '783 E. Fairground',
    '8839 E. Heritage',
    '82 Ridgeview',
    '71 N. Baker Lane',
    '9680 Edgemont',
    '7868 Manor',
    '87 Miller Street',
    '59 Bohemia Lane',
    '622 Roberts',
    '6 Saxton Street'
  ]);
  company text;
BEGIN
  SELECT 'company#' || count(*) + 1 into company From clients;
  INSERT INTO clients ("second_name", "full_name", "address", "company")
  VALUES (second_name, first_name, address, company);
END
$$ LANGUAGE plpgsql;

SELECT * FROM generate_data_for_clients();


-- function for filling clients
CREATE OR REPLACE FUNCTION fill_clients_table(n int)
  RETURNS void AS
$$
BEGIN
  FOR i IN 0 .. n
  LOOP
    PERFORM generate_data_for_clients();
  END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM fill_clients_table(20);


-- function for filling programs
CREATE OR REPLACE FUNCTION generate_data_for_programs()
  RETURNS void AS
$$
DECLARE
  program_name text := get_random_data(ARRAY['ClanLib', 'Crystal Space', 'HOOPS 3D', 'Horde3D', 'Irrlicht', 'Java 3D', 'Java FX', 'JMonkey']);
  program_version text := round(random() * 9)::text || '.'  || round(random() * 9)::text || '.' || round(random() * 9)::text;
BEGIN
  INSERT INTO programs ("program_name", "program_version", "price")
  VALUES (program_name, program_version, random() * 100);
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION fill_programs_table(n int)
  RETURNS void AS
$$
BEGIN
  FOR i IN 0 .. n
  LOOP
    PERFORM generate_data_for_programs();
  END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM fill_programs_table(20)


-- fill table contracts
INSERT INTO contracts ("client_id", "program_id", "contract_date") VALUES 
  (1, 3, NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  (1, 4, NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  (2, 5, NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  (2, 6, NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days'),
  (3, 3, NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days');


-- fill table deliveries
INSERT INTO deliveries ("contract_id", "delivery_date") VALUES 
  (2, NOW() + (random() * (NOW() + '90 days' - NOW())) + '90 days'),
  (3, NOW() + (random() * (NOW() + '90 days' - NOW())) + '90 days'),
  (4, NOW() + (random() * (NOW() + '90 days' - NOW())) + '90 days'),
  (5, NOW() + (random() * (NOW() + '90 days' - NOW())) + '90 days'),
  (6, NOW() + (random() * (NOW() + '90 days' - NOW())) + '90 days');


-- task 1.1
SELECT program_name, max(price)
FROM programs 
GROUP BY program_name
HAVING max(price) > 50
ORDER BY max(price)
DESC;


-- task 1.2
SELECT
  "delivery_id", 
  "contract_date",
  "delivery_date",
  "delivery_date"::timestamp - "contract_date"::timestamp AS "time of delivering"
FROM deliveries
JOIN contracts
USING("contract_id");


-- task 1.3
SELECT * 
FROM programs
WHERE "program_name"
SIMILAR TO '(I|J)%';


-- task 1.4
SELECT
  "contract_id",
  coalesce("delivery_id", -1) as "delivery_id"
FROM deliveries
RIGHT JOIN contracts
USING("contract_id");


-- task 2.1
SELECT "program_id", "program_name"
FROM programs
JOIN contracts
USING("program_id")
GROUP BY program_id
HAVING count(*) = (
  SELECT "program_id"
  FROM programs
  JOIN contracts
  USING("program_id")
  GROUP BY program_id
  ORDER BY count(*) 
  DESC
  LIMIT 1);


-- task 2.2
SELECT "contract_date", sum("price")
FROM contracts
JOIN programs
USING("program_id")
GROUP BY "contract_date"
HAVING "contract_date" = '2017-09-27'


-- task 2.3
SELECT "full_name"
FROM clients
GROUP BY "full_name"
HAVING "full_name" NOT IN 
(SELECT "full_name"
FROM clients
JOIN contracts
USING("client_id")
JOIN programs
USING("program_id")
WHERE "program_name" = 'Horde3D')
ORDER BY "full_name"


-- task 2.4
SELECT "contract_id"
FROM deliveries
RIGHT JOIN contracts
USING("contract_id")
WHERE "delivery_id" IS NULL;


-- task 2.5
SELECT "program_name"
FROM programs
JOIN contracts
USING("program_id")
WHERE "contract_id" IN (
  SELECT "contract_id"
  FROM deliveries
  RIGHT JOIN contracts
  USING("contract_id")
  WHERE "delivery_id" IS NULL
)
GROUP BY "program_name"

