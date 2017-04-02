CREATE EXTENSION plpythonu

CREATE LANGUAGE plpythonu

--Task1
CREATE FUNCTION getFullName()
  RETURNS text
AS $$
  return 'Pavlyuk Vadim Ruslanovych'
$$ LANGUAGE plpythonu;


--Task8
CREATE FUNCTION toPascalCase(str text)
  RETURNS text
AS $$
  return  ''.join(x for x in str.title() if not x.isspace())
$$ LANGUAGE plpythonu;