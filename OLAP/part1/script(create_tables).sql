/*==============================================================*/
/* DBMS name:      ORACLE Version 11g                           */
/* Created on:     15.04.2018 22:16:27                          */
/*==============================================================*/


alter table "Category"
   drop constraint FK_CATEGORY_REFERENCE_CATEGORY;

alter table "Invoice"
   drop constraint FK_INVOICE_REFERENCE_SALES;

alter table "Orders"
   drop constraint FK_ORDERS_RELATIONS_PRODUCT;

alter table "Position"
   drop constraint FK_POSITION_REFERENCE_POSITION;

alter table "Product"
   drop constraint FK_PRODUCT_REFERENCE_CATEGORY;

alter table "Product"
   drop constraint FK_PRODUCT_RELATIONS_COMPANY;

alter table "Sales"
   drop constraint FK_SALES_RELATIONS_CLIENTS;

alter table "Sales"
   drop constraint FK_SALES_RELATIONS_ORDERS;

alter table "Sales"
   drop constraint FK_SALES_RELATIONS_STAFF;

alter table "Staff"
   drop constraint FK_STAFF_REFERENCE_POSITION;

alter table "Store"
   drop constraint FK_STORE_RELATIONS_PRODUCT;

alter table "Store"
   drop constraint FK_STORE_RELATIONS_STAFF;

drop table "Category" cascade constraints;

drop table "Clients" cascade constraints;

drop table "Company" cascade constraints;

drop table "Invoice" cascade constraints;

drop table "Orders" cascade constraints;

drop table "Position" cascade constraints;

drop table "Product" cascade constraints;

drop table "Sales" cascade constraints;

drop table "Staff" cascade constraints;

drop table "Store" cascade constraints;

/*==============================================================*/
/* Table: "Category"                                            */
/*==============================================================*/
create table "Category" 
(
   "category_id"        integer              not null,
   "parent_id"          integer,
   "name"               varchar(50)          not null,
   constraint PK_CATEGORY primary key ("category_id")
);

/*==============================================================*/
/* Table: "Clients"                                             */
/*==============================================================*/
create table "Clients" 
(
   "client_id"          integer              not null,
   "full_name"          varchar(50)          not null,
   "phone"              varchar(15)          not null,
   EMAIL                varchar(50)          not null,
   constraint PK_CLIENTS primary key ("client_id")
);

/*==============================================================*/
/* Table: "Company"                                             */
/*==============================================================*/
create table "Company" 
(
   "company_id"         integer              not null,
   "name"               varchar(50)          not null,
   "address"            varchar(100)         not null,
   constraint PK_COMPANY primary key ("company_id")
);

/*==============================================================*/
/* Table: "Invoice"                                             */
/*==============================================================*/
create table "Invoice" 
(
   "invoice_id"         integer              not null,
   "sale_id"            integer,
   "invoice_code"       varchar(10)          not null,
   "invoice_data"       DATE                 not null,
   constraint PK_INVOICE primary key ("invoice_id")
);

/*==============================================================*/
/* Table: "Orders"                                              */
/*==============================================================*/
create table "Orders" 
(
   "order_id"           integer              not null,
   "product_id"         integer              not null,
   "quantity"           integer              not null,
   constraint PK_ORDERS primary key ("order_id")
);

/*==============================================================*/
/* Table: "Position"                                            */
/*==============================================================*/
create table "Position" 
(
   "position_id"        INTEGER              not null,
   "chief_id"           INTEGER,
   "title"              VARCHAR(50)          not null,
   "salary"             NUMERIC(6, 2)        not null,
   constraint PK_POSITION primary key ("position_id")
);

/*==============================================================*/
/* Table: "Product"                                             */
/*==============================================================*/
create table "Product" 
(
   "product_id"         integer              not null,
   "company_id"         integer              not null,
   "category_id"        integer              not null,
   "name"               varchar(50)          not null,
   "code"               varchar(11)          not null,
   "price"              numeric(6,2)         not null,
   "production_date"    varchar(8),
   "expiration_date"    varchar(8),
   constraint PK_PRODUCT primary key ("product_id")
);

/*==============================================================*/
/* Table: "Sales"                                               */
/*==============================================================*/
create table "Sales" 
(
   "sale_id"            integer              not null,
   "staff_id"           integer              not null,
   "client_id"          integer              not null,
   "order_id"           integer              not null,
   "sale_date"          varchar(8)           not null,
   constraint PK_SALES primary key ("sale_id")
);

/*==============================================================*/
/* Table: "Staff"                                               */
/*==============================================================*/
create table "Staff" 
(
   "staff_id"           integer              not null,
   "position_id"        INTEGER,
   "full_name"          varchar(30)          not null,
   EMAIL                varchar(50)          not null,
   constraint PK_STAFF primary key ("staff_id")
);

/*==============================================================*/
/* Table: "Store"                                               */
/*==============================================================*/
create table "Store" 
(
   "store_id"           integer              not null,
   "staff_id"           integer              not null,
   "product_id"         integer              not null,
   "shelf"              integer              not null,
   "quantity"           integer              not null
      constraint CKC_QUANTITY_STORE check ("quantity" >= 1),
   constraint PK_STORE primary key ("store_id")
);

alter table "Category"
   add constraint FK_CATEGORY_REFERENCE_CATEGORY foreign key ("parent_id")
      references "Category" ("category_id");

alter table "Invoice"
   add constraint FK_INVOICE_REFERENCE_SALES foreign key ("sale_id")
      references "Sales" ("sale_id");

alter table "Orders"
   add constraint FK_ORDERS_RELATIONS_PRODUCT foreign key ("product_id")
      references "Product" ("product_id");

alter table "Position"
   add constraint FK_POSITION_REFERENCE_POSITION foreign key ("chief_id")
      references "Position" ("position_id");

alter table "Product"
   add constraint FK_PRODUCT_REFERENCE_CATEGORY foreign key ("category_id")
      references "Category" ("category_id");

alter table "Product"
   add constraint FK_PRODUCT_RELATIONS_COMPANY foreign key ("company_id")
      references "Company" ("company_id");

alter table "Sales"
   add constraint FK_SALES_RELATIONS_CLIENTS foreign key ("client_id")
      references "Clients" ("client_id");

alter table "Sales"
   add constraint FK_SALES_RELATIONS_ORDERS foreign key ("order_id")
      references "Orders" ("order_id");

alter table "Sales"
   add constraint FK_SALES_RELATIONS_STAFF foreign key ("staff_id")
      references "Staff" ("staff_id");

alter table "Staff"
   add constraint FK_STAFF_REFERENCE_POSITION foreign key ("position_id")
      references "Position" ("position_id");

alter table "Store"
   add constraint FK_STORE_RELATIONS_PRODUCT foreign key ("product_id")
      references "Product" ("product_id");

alter table "Store"
   add constraint FK_STORE_RELATIONS_STAFF foreign key ("staff_id")
      references "Staff" ("staff_id");


/*==============================================================*/
/* AUTO INCREMENTS                                              */
/*==============================================================*/

CREATE SEQUENCE sq_Category
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Category before INSERT ON "Category" FOR each row
BEGIN
  SELECT sq_Category.NEXTVAL
  INTO :new."category_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Clients
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Clients before INSERT ON "Clients" FOR each row
BEGIN
  SELECT sq_Clients.NEXTVAL
  INTO :new."client_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Company
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Company before INSERT ON "Company" FOR each row
BEGIN
  SELECT sq_Company.NEXTVAL
  INTO :new."company_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Invoice
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Invoice before INSERT ON "Invoice" FOR each row
BEGIN
  SELECT sq_Invoice.NEXTVAL
  INTO :new."invoice_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Orders
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Orders before INSERT ON "Orders" FOR each row
BEGIN
  SELECT sq_Orders.NEXTVAL
  INTO :new."order_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Position
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Position before INSERT ON "Position" FOR each row
BEGIN
  SELECT sq_Position.NEXTVAL
  INTO :new."position_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Product
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Product before INSERT ON "Product" FOR each row
BEGIN
  SELECT sq_Product.NEXTVAL
  INTO :new."product_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Sales
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Sales before INSERT ON "Sales" FOR each row
BEGIN
  SELECT sq_Sales.NEXTVAL
  INTO :new."sale_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Staff
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Staff before INSERT ON "Staff" FOR each row
BEGIN
  SELECT sq_Staff.NEXTVAL
  INTO :new."staff_id"
  FROM dual;
END;


CREATE SEQUENCE sq_Store
START WITH 1 
INCREMENT BY 1 
NOMAXVALUE;

CREATE OR REPLACE TRIGGER tr_Store before INSERT ON "Store" FOR each row
BEGIN
  SELECT sq_Store.NEXTVAL
  INTO :new."store_id"
  FROM dual;
END;
