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

-- Output children by parent ID
PREPARE getChildrenByParentID (int) AS
  WITH RECURSIVE r AS (
    SELECT "program_id"
    FROM programs
    JOIN convertedPrograms
    USING("program_id")
    WHERE program_parent_id = $1
    UNION
    SELECT programs.program_id
    FROM programs
    JOIN convertedPrograms
      ON programs.program_id = convertedPrograms.program_id
    JOIN r
      ON convertedPrograms.program_parent_id = r.program_id
  )
  SELECT * FROM r;
    
EXECUTE getChildrenByParentID(10);
