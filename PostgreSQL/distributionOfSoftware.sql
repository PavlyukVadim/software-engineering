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
