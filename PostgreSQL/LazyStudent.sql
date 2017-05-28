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
  ClientID BIGSERIAL primary key,
  SecondName character(20) not null,
  FirstName character(20) not null,
  Phone character(15) not null,
  Email character(20) not null,
  RegDate date not null default now()
);

CREATE TABLE Tutors (
  TutorID BIGSERIAL primary key,
  SecondName character(20) not null,
  FirstName character(20) not null,
  UnitPrice real not null
);

CREATE TABLE Subjects (
  SubjectID BIGSERIAL primary key,
  SecondName character(20) not null
);

CREATE TABLE Tutor_Subjects (
  SubjectsID bigint references Subjects("subjectid"),
  TutorID bigint references Tutors("tutorid")
);

CREATE TABLE Tutor_Votes (
  TutorID bigint references Tutors("tutorid"),
  ClienID bigint references Clients("clientid"),
  Rating numeric CHECK (Rating between 0 and 10) 
);


--Task5
