/*
Assignment: Lab01-Pokemon
Author: John Shenk
Description: An SQL file for creating a table to output information about the creatures from
    the Pokemon video game franchise
Date: February 1, 2021
*/

create table pokemon 
(
    name            varchar(30),
    type_1          varchar(8),
    type_2          varchar(8),
    total           integer,
    hit_points      integer,
    attack          integer,
    defense         integer,
    special_attack  integer,
    special_defense integer,
    speed           integer,
    generation      integer,
    legendary       boolean,
        primary key (name)
);
/*CREATE TABLE*/

INSERT INTO pokemon 
Values('Marauder','Fighting',NULL,400,100,70,50,100,30,50,6,TRUE);
/*INSERT 0 1*/

SELECT name
FROM pokemon
Where legendary = TRUE and generation = 1;
/*
        name         
---------------------
 Articuno
 Zapdos
 Moltres
 Mewtwo
 MewtwoMega Mewtwo X
 MewtwoMega Mewtwo Y
(6 rows)
*/

SELECT name
FROM pokemon
WHERE speed > 150 and attack > defense;
/*
       name        
-------------------
 Ninjask
 DeoxysSpeed Forme
(2 rows)
*/

SELECT type_1,type_2
From pokemon
where speed > 40 and Speed < 45;
/*
  type_1  | type_2 
----------+--------
 Water    | 
 Poison   | 
 Psychic  | 
 Water    | 
 Rock     | Ground
 Rock     | Grass
 Dragon   | Ground
 Normal   | 
 Normal   | Flying
 Bug      | Grass
 Bug      | Grass
 Ice      | 
 Fairy    | 
 Fighting | 
 Poison   | Dragon
 Water    | 
 Ghost    | Grass
(17 rows)
*/

SELECT COUNT(*) from pokemon;
/*
 count 
-------
   801
(1 row)
*/

SELECT MAX(hit_points)
FROM pokemon
Where generation = 3;
/*
 max 
-----
 170
(1 row)
*/

SELECT name 
FROM pokemon
WHERE name like 'Z%';
/*
       name       
------------------
 Zubat
 Zapdos
 Zigzagoon
 Zangoose
 Zebstrika
 Zorua
 Zoroark
 Zweilous
 Zekrom
 Zygarde50% Forme
(10 rows)

*/

DELETE FROM pokemon WHERE name = 'Marauder';
/*
DELETE 1
*/