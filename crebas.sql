drop index IDX_ZHOBTMIND_HIS_3;

drop index IDX_ZHOBTMIND_HIS_2;

drop index IDX_ZHOBTMIND_HIS_1;

drop table T_ZHOBTMIND_HIS cascade constraints;

/*==============================================================*/
/* Table: T_ZHOBTMIND_HIS                                       */
/*==============================================================*/
create table T_ZHOBTMIND_HIS 
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
   constraint PK_ZHOBTMIND_HIS primary key (obtid, ddatetime),
   constraint ZHOBTMIND_HIS_KEYID unique (keyid)
);

comment on column T_ZHOBTMIND_HIS.obtid is
'站点代码。';

comment on column T_ZHOBTMIND_HIS.ddatetime is
'数据时间，精确到分钟。';

comment on column T_ZHOBTMIND_HIS.t is
'湿度，单位：0.1摄氏度。';

comment on column T_ZHOBTMIND_HIS.p is
'气压，单位：0.1百帕。';

comment on column T_ZHOBTMIND_HIS.u is
'相对湿度，0-100之间的值。';

comment on column T_ZHOBTMIND_HIS.wd is
'风向，0-360之间的值。';

comment on column T_ZHOBTMIND_HIS.wf is
'风速：单位0.1m/s。';

comment on column T_ZHOBTMIND_HIS.r is
'降雨量：0.1mm。';

comment on column T_ZHOBTMIND_HIS.vis is
'能见度：0.1米。';

comment on column T_ZHOBTMIND_HIS.upttime is
'更新时间。';

comment on column T_ZHOBTMIND_HIS.keyid is
'记录编号，从与本表同名的序列生成器中获取。';

/*==============================================================*/
/* Index: IDX_ZHOBTMIND_HIS_1                                   */
/*==============================================================*/
create unique index IDX_ZHOBTMIND_HIS_1 on T_ZHOBTMIND_HIS (
   ddatetime ASC,
   obtid ASC
);

/*==============================================================*/
/* Index: IDX_ZHOBTMIND_HIS_2                                   */
/*==============================================================*/
create index IDX_ZHOBTMIND_HIS_2 on T_ZHOBTMIND_HIS (
   ddatetime ASC
);

/*==============================================================*/
/* Index: IDX_ZHOBTMIND_HIS_3                                   */
/*==============================================================*/
create index IDX_ZHOBTMIND_HIS_3 on T_ZHOBTMIND_HIS (
   obtid ASC
);
