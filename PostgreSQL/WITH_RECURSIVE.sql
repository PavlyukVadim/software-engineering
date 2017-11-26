CREATE TABLE convertedPrograms (
  converted_program_id bigserial PRIMARY KEY,
  program_id bigint references programs("program_id"),
  program_parent_id bigint references programs("program_id")
);

INSERT
INTO convertedPrograms (program_id, program_parent_id)
VALUES
  (11, 10),
  (12, 10),
  (13, 10),
  (14, 10),
  (15, 11),
  (16, 11),
  (17, 15),
  (18, 15),
  (19, 11),
  (20, 10);
