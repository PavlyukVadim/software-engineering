--Task1
create or replace function count_rows(schema text, tablename text) returns integer
as
$body$
declare
  result integer;
  query varchar;
begin
  query := 'SELECT count(1) FROM ' || schema || '.' || tablename;
  execute query into result;
  return result;
end;
$body$
language plpgsql;

select 
  table_schema,
  table_name, 
  count_rows(table_schema, table_name)
from information_schema.tables
where 
  table_schema not in ('pg_catalog', 'information_schema') 
  and table_type='BASE TABLE'
order by 3 desc


--Task2
CREATE OR REPLACE FUNCTION grantReadingToEverybody() RETURNS integer AS $$
DECLARE
  userData RECORD;
BEGIN
  RAISE NOTICE 'Start';
  FOR userData IN SELECT * FROM pg_shadow LOOP
    EXECUTE format('GRANT SELECT ON ALL TABLES IN SCHEMA public TO %I', userData.usename);
  END LOOP;
  RAISE NOTICE 'Done';
  RETURN 1;
END;
$$ LANGUAGE plpgsql;


--Task3
--Since FOR loops automatically use a cursor internally to avoid memory problems
CREATE OR REPLACE FUNCTION denyAllForTestUser() RETURNS integer AS $$
DECLARE
  tableData RECORD;
BEGIN
  FOR tableData IN SELECT table_name FROM information_schema.tables 
    WHERE table_schema NOT IN ('pg_catalog', 'information_schema') 
    AND table_type='BASE TABLE' AND table_name ~ '^prod_' LOOP
    EXECUTE format('DENY ALL ON %I TO TestUser', tableData.table_name);
  END LOOP;
  RETURN 1;
END;
$$ LANGUAGE plpgsql;


--Task6
CREATE OR REPLACE FUNCTION validation_phone() RETURNS trigger as
$$
BEGIN
    NEW."Phone" = regexp_replace(NEW."Phone", '[^0-9]', '', 'g');
    return NEW;
END
$$ language 'plpgsql';

CREATE trigger validation_phone_trigger
before INSERT on customers
    for each row
    execute procedure validation_phone();

