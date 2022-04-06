drop index IDX_ZHOBTMIND1_3;

drop index IDX_ZHOBTMIND1_2;

drop index IDX_ZHOBTMIND1_1;

drop table T_ZHOBTMIND1 cascade constraints;

/*==============================================================*/
/* Table: T_ZHOBTMIND1                                          */
/*==============================================================*/
drop   sequence SEQ_ZHOBTMIND1;
create sequence SEQ_ZHOBTMIND1 increment by 1 minvalue 1 nocycle;
create table T_ZHOBTMIND1 
(
   obtid              varchar2(10)         not null,
   ddatetime          date                 not null,
   t                  number(8),
   p                  number(8),
   u                  number(8),
   wd                 number(8),
   wf                 number(8),
   r                  number(8),
   vis                number(8),
   upttime            date                 default sysdate not null,
   keyid              number(15)           not null,
   constraint PK_ZHOBTMIND1 primary key (obtid, ddatetime),
   constraint ZHOBTMIND1_KEYID unique (keyid)
);

comment on column T_ZHOBTMIND1.obtid is
'站点代码。';

comment on column T_ZHOBTMIND1.ddatetime is
'数据时间，精确到分钟。';

comment on column T_ZHOBTMIND1.t is
'湿度，单位：0.1摄氏度。';

comment on column T_ZHOBTMIND1.p is
'气压，单位：0.1百帕。';

comment on column T_ZHOBTMIND1.u is
'相对湿度，0-100之间的值。';

comment on column T_ZHOBTMIND1.wd is
'风向，0-360之间的值。';

comment on column T_ZHOBTMIND1.wf is
'风速：单位0.1m/s。';

comment on column T_ZHOBTMIND1.r is
'降雨量：0.1mm。';

comment on column T_ZHOBTMIND1.vis is
'能见度：0.1米。';

comment on column T_ZHOBTMIND1.upttime is
'更新时间。';

comment on column T_ZHOBTMIND1.keyid is
'记录编号，从与本表同名的序列生成器中获取。';

/*==============================================================*/
/* Index: IDX_ZHOBTMIND1_1                                      */
/*==============================================================*/
create unique index IDX_ZHOBTMIND1_1 on T_ZHOBTMIND1 (
   ddatetime ASC,
   obtid ASC
);

/*==============================================================*/
/* Index: IDX_ZHOBTMIND1_2                                      */
/*==============================================================*/
create index IDX_ZHOBTMIND1_2 on T_ZHOBTMIND1 (
   ddatetime ASC
);

/*==============================================================*/
/* Index: IDX_ZHOBTMIND1_3                                      */
/*==============================================================*/
create index IDX_ZHOBTMIND1_3 on T_ZHOBTMIND1 (
   obtid ASC
);
