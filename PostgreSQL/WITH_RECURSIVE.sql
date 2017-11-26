CREATE TABLE convertedPrograms (
  converted_program_id bigserial PRIMARY KEY,
  program_id bigint references programs("program_id"),
  program_parent_id bigint references programs("program_id")
);
