/* John Shenk */
/* Lab 02: CD (basic) */

/* PROBLEM 1 BEGIN */
create table track(
    trkid       integer,
    trknum      integer,
    trktitle    varchar(30),
    trklength   numeric(3, 2),
    cdid        integer,
        primary key (trkid),
        foreign key (cdid) references cd 
);

create table cd(
    cdid            integer,
    cdblid          varchar(15),
    cdtitle         varchar(15),
    cdyear          integer,
    lbltitle        varchar(12),
        primary key (cdid),
        foreign key (lbltitle) references label
);

create table label(
    lbltitle        varchar(12),
    lblstreet       varchar(30),
    lblCity         varchar(10),
    lblState        varchar(2),
    lblpostcode     varchar(5),
    lblnation       varchar(3),
        primary key (lbltitle)
);
/* PROBLEM 1 END */

/* PROBLEM 2 BEGIN */
SELECT trktitle, cdtitle, trklength
from track, cd
    order by cdtitle, trklength, trktitle;
/* PROBLEM 2 END */

/* PROBLEM 3 BEGIN */
select trktitle, trklength
from 
where id = track.cdid;
/* PROBLEM 3 END */

/* PROBLEM 4 BEGIN */
SELECT 'Replace this entire line with your answer';
/* PROBLEM 4 END */

/* PROBLEM 5 BEGIN */
SELECT 'Replace this entire line with your answer';
/* PROBLEM 5 END */

/* PROBLEM 6 BEGIN */
SELECT 'Replace this entire line with your answer';
/* PROBLEM 6 END */

/* PROBLEM 7 BEGIN */
SELECT 'Replace this entire line with your answer';
/* PROBLEM 7 END */

/* PROBLEM 8 BEGIN */
SELECT 'Replace this entire line with your answer';
/* PROBLEM 8 END */

/* PROBLEM 9 BEGIN */
SELECT 'Replace this entire line with your answer';
/* PROBLEM 9 END */
