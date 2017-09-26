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

