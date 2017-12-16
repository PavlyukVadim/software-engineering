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
  -- (11, 17);


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


-- Output parents by child ID
PREPARE getParentsByChildID (int) AS
  WITH RECURSIVE r AS (
    SELECT "program_parent_id"
    FROM convertedPrograms
    WHERE program_id = $1
    UNION
    SELECT convertedPrograms.program_parent_id
    FROM convertedPrograms
    JOIN r
      ON convertedPrograms.program_id = r.program_parent_id
  )
  SELECT * FROM r;

EXECUTE getParentsByChildID(17);


-- Output children by parent ID with level
PREPARE getChildrenByParentIDWithLevel (int) AS
  WITH RECURSIVE r AS (
    SELECT "program_id", 1 AS level
    FROM programs
    JOIN convertedPrograms
    USING("program_id")
    WHERE program_parent_id = $1
    UNION
    SELECT programs.program_id, r.level + 1 AS level
    FROM programs
    JOIN convertedPrograms
      ON programs.program_id = convertedPrograms.program_id
    JOIN r
      ON convertedPrograms.program_parent_id = r.program_id
  )
  SELECT * FROM r;
    
EXECUTE getChildrenByParentIDWithLevel(10);


-- add cycle
INSERT
INTO convertedPrograms (program_id, program_parent_id)
VALUES
  (11, 17);


PREPARE getChildrenByParentID (int) AS
  WITH RECURSIVE r AS (
    SELECT
      "program_id",
      "program_parent_id",
      1 AS level,
      0 AS is_cycle
    FROM programs
    JOIN convertedPrograms
    USING("program_id")
    WHERE program_parent_id = $1
    UNION
    SELECT
      programs.program_id,
      convertedPrograms.program_parent_id,
      r.level + 1 AS level,
      (CASE
        WHEN r.program_id = convertedPrograms.program_parent_id
        AND r.program_parent_id = convertedPrograms.program_id 
        THEN 1
        ELSE 0
        END
      ) AS is_cycle
    FROM programs
    JOIN convertedPrograms
      ON programs.program_id = convertedPrograms.program_id
    JOIN r
      ON convertedPrograms.program_parent_id = r.program_id
    WHERE r.is_cycle = 0
  )
  SELECT * FROM r;

EXECUTE getChildrenByParentID(10);


-- For every child output list of parents
WITH RECURSIVE r AS (
  SELECT DISTINCT
    "program_id",
    "program_name"::text AS npath,
    "program_parent_id"::text || '/' || "program_id"::text AS path,
    "program_parent_id",
    0 AS is_cycle
  FROM programs
  JOIN convertedPrograms
  USING("program_id")
  UNION
  SELECT
    programs.program_id,
    r.npath || '/' || programs.program_name AS npath,
    r.path || '/' || programs.program_id AS path,
    convertedPrograms.program_parent_id,
    (CASE
      WHEN r.program_id = convertedPrograms.program_parent_id
      AND r.program_parent_id = convertedPrograms.program_id 
      THEN 1
      ELSE 0
      END
    ) AS is_cycle
  FROM programs
  JOIN convertedPrograms
    ON convertedPrograms.program_id = programs.program_id
  JOIN r
    ON convertedPrograms.program_parent_id  = r.program_id
  WHERE r.is_cycle = 0
)
SELECT program_id, npath FROM r;

