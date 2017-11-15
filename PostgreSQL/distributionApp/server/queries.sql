CREATE TABLE contracts (
  contract_id bigserial PRIMARY KEY,
  client_id bigint references clients("client_id"),
  program_id bigint references programs("program_id"),
  contract_date date 
);

CREATE TABLE contracts_wo_programs (
  contract_id bigserial PRIMARY KEY,
  client_id bigint references clients("client_id"),
  contract_date date
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
  company text := 'company#' || '_' || second_name;
BEGIN
  INSERT INTO clients ("second_name", "full_name", "address", "company")
  VALUES (second_name, first_name, address, company);
END
$$ LANGUAGE plpgsql;

SELECT * FROM generate_data_for_clients();


-- function for filling clients
CREATE OR REPLACE FUNCTION fill_clients_table(n int)
  RETURNS bigint AS
$$
DECLARE
  number_of_clients bigint;
BEGIN
  FOR i IN 1 .. n
  LOOP
    PERFORM generate_data_for_clients();
  END LOOP;
  SELECT count(*) INTO number_of_clients FROM clients;
  RETURN number_of_clients;
END;
$$ LANGUAGE plpgsql;

-- SELECT * FROM fill_clients_table(20);


CREATE OR REPLACE FUNCTION generate_data_for_contracts_wo_programs(number_of_clients bigint)
  RETURNS void AS
$$
DECLARE
  contract_date date := (NOW() + (random() * (NOW() + '90 days' - NOW())) + '30 days');
  client_id bigint := ceil(random() * number_of_clients);
BEGIN
  INSERT INTO contracts_wo_programs ("client_id", "contract_date")
  VALUES (client_id, contract_date);
END
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION fill_contracts_wo_programs_table(n int)
  RETURNS bigint AS
$$
DECLARE
  number_of_clients bigint;
  number_of_contracts bigint;
BEGIN
  SELECT floor(random() * count(*)) + 1 into number_of_clients From clients;
  FOR i IN 1 .. n
  LOOP
    PERFORM generate_data_for_contracts_wo_programs(number_of_clients);
  END LOOP;
  SELECT count(*) INTO number_of_contracts FROM contracts_wo_programs;
  RETURN number_of_contracts;
END;
$$ LANGUAGE plpgsql;

-- reset tabels
CREATE OR REPLACE FUNCTION reset_tabels() RETURNS void AS $$
  BEGIN
    DELETE FROM deliveries;
    DELETE FROM contracts_wo_programs;
    DELETE FROM clients;
    ALTER SEQUENCE clients_client_id_seq RESTART WITH 1;
    ALTER SEQUENCE contracts_wo_programs_contract_id_seq RESTART WITH 1;
  END;
$$ LANGUAGE plpgsql;

-- query without index
SELECT * 
  FROM contracts_wo_programs
  JOIN clients
  USING (client_id)
  WHERE contract_date
    between NOW() and (NOW() + INTERVAL '30 DAY')

-- index for prev query
CREATE INDEX on contracts_wo_programs(contract_date)
