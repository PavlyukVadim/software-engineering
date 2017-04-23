--Task1
CREATE DATABASE pavlyuk
  WITH OWNER = vadim
       ENCODING = 'UTF8'
       TABLESPACE = pg_default
       LC_COLLATE = 'ru_RU.UTF-8'
       LC_CTYPE = 'ru_RU.UTF-8'
       CONNECTION LIMIT = -1;


--Task2
CREATE TABLE Student (
    StudentId bigint not null,
    SecondName character(255) not null,
    FirstName character(255) not null,
    Sex character(1) not null
);

--Task3
ALTER TABLE Student
ADD PRIMARY KEY (StudentId);


--Task4
ALTER TABLE Student 
ADD COLUMN StudentId BIGSERIAL PRIMARY KEY;


--Task5
ALTER TABLE Student 
ADD COLUMN BirthDate date


--Task6
ALTER TABLE Student 
ADD COLUMN CurrentAge character(25);

CREATE OR REPLACE FUNCTION student_age() RETURNS trigger AS
  $$BEGIN
    NEW.CurrentAge := age(current_date::timestamp, NEW.Birthdate::timestamp);
    RETURN NEW;
  END;
$$LANGUAGE plpgsql;
CREATE TRIGGER student_age BEFORE INSERT OR UPDATE ON student FOR EACH ROW EXECUTE PROCEDURE student_age();


--Task7
ALTER TABLE Student
ADD CHECK (sex = 'f' OR sex = 'm');


--Task8
INSERT INTO Student ("secondname", "firstname", "sex", "birthdate")
VALUES ('Pavlyuk', 'Vadim', 'm', '30-08-1998');

INSERT INTO Student ("secondname", "firstname", "sex", "birthdate")
VALUES ('Mykolayenko', 'Maxim', 'm', '30-08-1998');
 
INSERT INTO Student ("secondname", "firstname", "sex", "birthdate")
VALUES ('Paterylo', 'Vlad', 'm', '30-08-1998');


--Task9
CREATE VIEW vMaleStudent AS
SELECT *
FROM Student
WHERE "sex" = 'm';

CREATE VIEW vFemaleStudent AS
SELECT *
FROM Student
WHERE "sex" = 'f';


--Task10
ALTER TABLE Student ALTER COLUMN StudentId TYPE smallint;
--cannot alter type of a column used by a view or rule