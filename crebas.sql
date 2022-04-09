drop table T_ZHOBTCODE1 cascade constraints;

/*==============================================================*/
/* Table: T_ZHOBTCODE1                                          */
/*==============================================================*/
drop   sequence SEQ_ZHOBTCODE1;
create sequence SEQ_ZHOBTCODE1 increment by 1 minvalue 1 nocycle;
create table T_ZHOBTCODE1 
(
   obtid              varchar2(10)         not null,
   cityname           varchar2(30)         not null,
   provname           varchar2(30)         not null,
   lat                number(8)            not null,
   lon                number(8)            not null,
   height             number(8)            not null,
   upttime            date                 default sysdate not null,
   keyid              number(15)           not null,
   constraint PK_ZHOBTCODE1 primary key (obtid),
   constraint ZHOBTCODE1_KEYID unique (keyid)
);

comment on column T_ZHOBTCODE1.obtid is
'站点代码';

comment on column T_ZHOBTCODE1.cityname is
'城市名称';

comment on column T_ZHOBTCODE1.provname is
'省名称';

comment on column T_ZHOBTCODE1.lat is
'纬度，单位：0.01度。';

comment on column T_ZHOBTCODE1.lon is
'经度，单位：0.01度。';

comment on column T_ZHOBTCODE1.height is
'海拔高度，单位：0.1米。';

comment on column T_ZHOBTCODE1.upttime is
'更新时间。';

comment on column T_ZHOBTCODE1.keyid is
'记录编号，从与本表同名的序列生成器中获取。';
