alter table T_USERLOGSTAT
   drop constraint FK_T_USERLO_REFERENCE_T_USERIN;

alter table T_USERLOGSTAT
   drop constraint FK_T_USERLO_REFERENCE_T_INTERC;

drop table T_USERLOGSTAT cascade constraints;

/*==============================================================*/
/* Table: T_USERLOGSTAT                                         */
/*==============================================================*/
drop   sequence SEQ_USERLOG;
create sequence SEQ_USERLOG increment by 1 minvalue 1 nocycle;
create table T_USERLOGSTAT 
(
   username           varchar2(30)         not null,
   intername          varchar2(30)         not null,
   ddatetie           date                 not null,
   rpc                number(8),
   keyid              number(15)           not null,
   constraint PK_USERLOGSTAT primary key (username, intername, ddatetie)
);

comment on column T_USERLOGSTAT.username is
'用户名。';

comment on column T_USERLOGSTAT.intername is
'接口代码。';

comment on column T_USERLOGSTAT.ddatetie is
'统计时段，精确到小时。';

comment on column T_USERLOGSTAT.rpc is
'数据行数，调用接口时返回数据的总行数。';

comment on column T_USERLOGSTAT.keyid is
'记录编号，从与本表同名的序列生成器中获取。';

alter table T_USERLOGSTAT
   add constraint FK_T_USERLO_REFERENCE_T_USERIN foreign key (username)
      references T_USERINFO (username);

alter table T_USERLOGSTAT
   add constraint FK_T_USERLO_REFERENCE_T_INTERC foreign key (intername)
      references T_INTERCFG (intername);
