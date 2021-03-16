## Hive - Create Database

    CREATE DATABASE|SCHEMA [IF NOT EXISTS] <database name>

    hive> CREATE DATABASE [IF NOT EXISTS] userdb;

    hive> CREATE SCHEMA userdb;

    hive> SHOW DATABASES;
    default
    userdb





## Hive - Drop Database

    DROP DATABASE StatementDROP (DATABASE|SCHEMA) [IF EXISTS] database_name [RESTRICT|CASCADE];

    hive> DROP DATABASE IF EXISTS userdb;

    hive> DROP DATABASE IF EXISTS userdb CASCADE;

    hive> DROP SCHEMA userdb;





## Hive - Create Table

    CREATE [TEMPORARY] [EXTERNAL] TABLE [IF NOT EXISTS] [db_name.] table_name [(col_name data_type [COMMENT col_comment], ...)] [COMMENT table_comment] [ROW FORMAT row_format] [STORED AS file_format]

    COMMENT 'Employee details'
    FIELDS TERMINATED BY '\t'
    LINES TERMINATED BY '\n'
    STORED IN TEXT FILE

    hive> CREATE TABLE IF NOT EXISTS employee ( eid int, name String, salary String, destination String) COMMENT 'Employee details' ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t' LINES TERMINATED BY '\n' STORED AS TEXTFILE;

    OK
    Time taken: 5.905 seconds
    hive>

    LOAD DATA [LOCAL] INPATH 'filepath' [OVERWRITE] INTO TABLE tablename [PARTITION (partcol1=val1, partcol2=val2 ...)]

    hive> LOAD DATA LOCAL INPATH '/home/m/Documents/sample.txt' OVERWRITE INTO TABLE employee;

    OK
    Time taken: 15.905 seconds
    hive>





## Hive - Alter Table

    ALTER TABLE name RENAME TO new_name
    ALTER TABLE name ADD COLUMNS (col_spec[, col_spec ...])
    ALTER TABLE name DROP [COLUMN] column_name
    ALTER TABLE name CHANGE column_name new_name new_type
    ALTER TABLE name REPLACE COLUMNS (col_spec[, col_spec ...])

    hive> ALTER TABLE employee RENAME TO emp;

    hive> ALTER TABLE employee CHANGE name ename String;
    hive> ALTER TABLE employee CHANGE salary salary Double;

    hive> ALTER TABLE employee ADD COLUMNS ( dept STRING COMMENT 'Department name');

    hive> ALTER TABLE employee REPLACE COLUMNS ( eid INT empid Int, ename STRING name String);





## Hive - INSERT ... VALUES, UPDATE, DELETE, and MERGE

> **INSERT**

    INSERT INTO TABLE tablename [PARTITION (partcol1=val1, partcol2=val2 ...)] VALUES values_row [, values_row...] 

    CREATE TABLE students (name VARCHAR(64), age INT, gpa DECIMAL(3,2)) CLUSTERED BY (age) INTO 2 BUCKETS STORED AS ORC; 

    INSERT INTO TABLE students VALUES ('fred flintstone', 35, 1.28), ('barney rubble', 32, 2.32); 

    CREATE TABLE pageviews (userid VARCHAR(64), link STRING, source STRING) PARTITIONED BY (datestamp STRING) CLUSTERED BY (userid) INTO 256 BUCKETS STORED AS ORC; 

    INSERT INTO TABLE pageviews PARTITION (datestamp = '2014-09-23') VALUES ('jsmith', 'mail.com', 'sports.com'), ('jdoe', 'mail.com', null); 

    INSERT INTO TABLE pageviews PARTITION (datestamp) VALUES ('tjohnson', 'sports.com', 'finance.com', '2014-09-23'), ('tlee', 'finance.com', null, '2014-09-21'); 

> **UPDATE**

    UPDATE tablename SET column = value [, column = value ...] [WHERE expression]; 

    UPDATE students SET name = null WHERE gpa <= 1.0; 

> **DELETE**

    DELETE FROM tablename [WHERE expression]; 

    DELETE FROM students WHERE gpa <= 1,0; 

    MERGE

    MERGE INTO customer USING (SELECT * FROM new_customer_stage) SUB ON sub.id = customer.id
        -	when matched then update set name = sub.name, state = sub.new_state
        -	when not matched then insert values (sub.id, sub.name, sub.state);





## Hive - Drop Table

    DROP TABLE [IF EXISTS] table_name;

    hive> DROP TABLE IF EXISTS employee;

    OK
    Time taken: 5.3 seconds
    hive>

    hive> SHOW TABLES;
    emp
    ok
    Time taken: 2.1 seconds
    hive>





## Hive - Partitioning

    ALTER TABLE table_name ADD [IF NOT EXISTS] PARTITION partition_spec [LOCATION 'location1'] partition_spec [LOCATION 'location2'] ...; 
    partition_spec:
    : (p_column = p_col_value, p_column = p_col_value, ...)

    hive> ALTER TABLE employee ADD PARTITION (year='2012') location '/2012/part2012';

    ALTER TABLE table_name PARTITION partition_spec RENAME TO PARTITION partition_spec;

    hive> ALTER TABLE employee PARTITION (year='1203') RENAME TO PARTITION (Yoj='1203');

    ALTER TABLE table_name DROP [IF EXISTS] PARTITION partition_spec, PARTITION partition_spec,...;

    hive> ALTER TABLE employee DROP [IF EXISTS] PARTITION (year='1203');





## Hive - Built-in Operators

    hive> SELECT * FROM employee WHERE Id=1205;

    hive> SELECT 20+30 ADD FROM temp;

    hive> SELECT * FROM employee WHERE Salary>40000 && Dept=TP;





## Hiveql Select...Where

    SELECT [ALL | DISTINCT] select_expr, select_expr, ... FROM table_reference [WHERE where_condition] [GROUP BY col_list] [HAVING having_condition] [CLUSTER BY col_list | [DISTRIBUTE BY col_list] [SORT BY col_list]] [LIMIT number]; 

    hive> SELECT * FROM employee WHERE salary>30000;





## Hiveql Select...Order By

    SELECT [ALL | DISTINCT] select_expr, select_expr, ... FROM table_reference [WHERE where_condition] [GROUP BY col_list] [HAVING having_condition] [ORDER BY col_list]] [LIMIT number];

    hive> SELECT Id, Name, Dept FROM employee ORDER BY DEPT;





## Hiveql Group By

    SELECT [ALL | DISTINCT] select_expr, select_expr, ... FROM table_reference [WHERE where_condition] [GROUP BY col_list] [HAVING having_condition] [ORDER BY col_list]] [LIMIT number];

    hive> SELECT Dept,count(*) FROM employee GROUP BY DEPT;





## Hiveql Joins

    join_table:
    table_reference JOIN table_factor [join_condition] | table_reference {LEFT|RIGHT|FULL} [OUTER] JOIN table_reference join_condition | table_reference LEFT SEMI JOIN table_reference join_condition | table_reference CROSS JOIN table_reference [join_condition]

    hive> SELECT c.ID, c.NAME, c.AGE, o.AMOUNT FROM CUSTOMERS c JOIN ORDERS o ON (c.ID = o.CUSTOMER_ID);

    hive> SELECT c.ID, c.NAME, o.AMOUNT, o.DATE FROM CUSTOMERS c LEFT OUTER JOIN ORDERS o ON (c.ID = o.CUSTOMER_ID);

    hive> SELECT c.ID, c.NAME, o.AMOUNT, o.DATE FROM CUSTOMERS c RIGHT OUTER JOIN ORDERS o ON (c.ID = o.CUSTOMER_ID);

    hive> SELECT c.ID, c.NAME, o.AMOUNT, o.DATE FROM CUSTOMERS c FULL OUTER JOIN ORDERS o ON (c.ID = o.CUSTOMER_ID);





## Hive - Built-in Functions

    hive> SELECT round(2.6) from temp;

    3.0

    hive> SELECT floor(2.6) from temp;

    2.0

    hive> SELECT ceil(2.6) from temp

    3.0





## Hive - View and Indexes

    CREATE VIEW [IF NOT EXISTS] view_name [(column_name [COMMENT column_comment], ...) ] [COMMENT table_comment] AS SELECT ...

    hive> CREATE VIEW emp_30000 AS SELECT * FROM employee WHERE salary>30000;

    DROP VIEW view_name

    hive> DROP VIEW emp_30000;

    CREATE INDEX index_name ON TABLE base_table_name (col_name, ...) AS 'index.handler.class.name' [WITH DEFERRED REBUILD] [IDXPROPERTIES (property_name=property_value, ...)] [IN TABLE index_table_name] [PARTITIONED BY (col_name, ...)] [ [ ROW FORMAT ...] STORED AS ... | STORED BY ... ] [LOCATION hdfs_path] [TBLPROPERTIES (...)]

    hive> CREATE INDEX inedx_salary ON TABLE employee(salary) AS 'org.apache.hadoop.hive.ql.index.compact.CompactIndexHandler';

    DROP INDEX <index_name> ON <table_name>

    hive> DROP INDEX index_salary ON employee;