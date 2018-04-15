-- Create the user 
create user USER
identified by "OLAP"
  default tablespace USERS
  temporary tablespace TEMP
  profile DEFAULT;
-- Grant/Revoke role privileges 
grant connect to USER;
grant resource to USER;
-- Grant/Revoke system privileges 
grant unlimited tablespace to USER;
