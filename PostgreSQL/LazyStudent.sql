--Task1
CREATE DATABASE "LazyStudent"
  WITH OWNER = vadim
       ENCODING = 'UTF8'
       TABLESPACE = pg_default
       LC_COLLATE = 'ru_RU.UTF-8'
       LC_CTYPE = 'ru_RU.UTF-8'
       CONNECTION LIMIT = -1;


--Tasks2-4
CREATE TABLE Clients (
  ClientID bigserial primary key,
  SecondName character(20) not null,
  FirstName character(20) not null,
  Phone character(15) not null,
  Email character(20) not null,
  RegDate date not null default now()
);

CREATE TABLE Tutors (
  TutorID bigserial primary key,
  SecondName character(20) not null,
  FirstName character(20) not null,
  UnitPrice real not null
);

CREATE TABLE Subjects (
  SubjectID bigserial primary key,
  SecondName character(20) not null
);

CREATE TABLE Tutor_Subjects (
  SubjectsID bigint references Subjects("subjectid"),
  TutorID bigint references Tutors("tutorid")
);

CREATE TABLE Tutor_Votes,  (
  TutorID bigint references Tutors("tutorid"),
  ClienID bigint references Clients("clientid"),
  Rating numeric CHECK (Rating between 0 and 10) 
);


--Task5
CREATE TABLE Partners (
  CompanyID bigserial primary key,
  CompanyName character(20) not null,
  UnitPrice real not null
);


--Task6
CREATE TABLE Orders (
  OrderID BIGSERIAL primary key,
  ClientID bigint references Clients("clientid"),
  Status character(1) not null,
  Discount real not null,
  TutorID bigint references Tutors("tutorid"),
  CompanyID bigint references Partners("companyid"),
  OrderDate date not null default now(),
  NumberOfLessons integer not null default 1
);


--Task7
CREATE ROLE admin WITH CREATEDB CREATEROLE;
CREATE ROLE chief LOGIN;
CREATE ROLE employee LOGIN;

GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO admin;
GRANT SELECT, UPDATE, INSERT, DELETE ON ALL TABLES IN SCHEMA public TO chief;
GRANT SELECT, UPDATE, INSERT ON Orders, Partners, Tutor_Votes, 
                                Tutor_Subjects, Subjects, Tutors,
                                Clients TO employee;


--Task8
CREATE TABLE Basket(
  DeletedData json not null,
  TableName character(20) not null,
  DeletingDate date not null,
  Performer character(20) not null,
  DataID bigserial primary key not null
);

CREATE OR REPLACE FUNCTION save_in_basket() RETURNS trigger as
$$
BEGIN
  INSERT into Basket SELECT row_to_json(OLD), TG_TABLE_NAME, now(), user;
  return NULL;
END
$$ language 'plpgsql';

CREATE trigger save_in_basket_trigger
after DELETE on Orders
  for each row
  execute procedure save_in_basket();

CREATE trigger save_in_basket_trigger
after DELETE on Clients
  for each row
  execute procedure save_in_basket();

CREATE trigger save_in_basket_trigger
after DELETE on Tutors
  for each row
  execute procedure save_in_basket();
--...


--Task9
CREATE OR REPLACE FUNCTION validation_order_discount() RETURNS trigger as
$$
DECLARE
  regDate date;
  dateDiff real;
  discount real;
BEGIN
  select into regDate Clients."regdate" from Clients where "clientid" = NEW."clientid";
  select into dateDiff (DATE_PART('year', now()) - DATE_PART('year', regDate));
  case
    WHEN dateDiff > 4 THEN discount := 15;
    WHEN dateDiff > 3 THEN discount := 11;
    WHEN dateDiff > 2 THEN discount := 8;
    WHEN dateDiff > 1 THEN discount := 5;
    ELSE discount := 0;
  end case;
  NEW."discount" = discount; 
  return NEW;
END
$$ language 'plpgsql';

CREATE trigger validation_discount_trigger
before insert on ordersSELECT * from orders
  for each row
  execute procedure validation_order_discount();


--Task10
CREATE TABLE Discounts (
  CompanyID bigint references Partners("companyid"),
  Discount real not null,
  DiscountDate date not null,
  Period date not null
);
