CREATE DATABASE BANKSYSTEM;

USE BANKSYSTEM;

CREATE TABLE AccountInfo
(
    AccountId INT PRIMARY KEY IDENTITY (1,1),
    NetName   NVARCHAR(50)       NOT NULL,
    Password  NVARCHAR(50)       NOT NULL,
    Name      NVARCHAR(5)        NOT NULL,
    IdCard    VARCHAR(18) UNIQUE NOT NULL,
    OpenTime  datetime default getdate()
)

CREATE TABLE State
(
    StateId INT PRIMARY KEY,
    Name    VARCHAR(50) unique not null
)


CREATE TABLE BankCard
(
    Id        VARCHAR(18) PRIMARY KEY,
    Password  VARCHAR(6) NOT NULL,
    Money     money                          default 0 check (Money >= 0),
    OpenTime  smalldatetime                  default getdate(),
    AccountId INT REFERENCES AccountInfo (AccountId),
    StateId   INT REFERENCES State (StateId) DEFAULT 1,
    WhyState  NVARCHAR(50)
)

CREATE TABLE Bill
(
    Id     INT PRIMARY KEY IDENTITY (1,1),
    BankId VARCHAR(18) REFERENCES BankCard (Id) NOT NULL,
    Money  money    default 0,
    Source VARCHAR(50)                              NOT NULL,
    Mod    VARCHAR(10)                              NOT NULL CHECK (Mod = 'Input' OR Mod = 'Output'),
    State  VARCHAR(10)                              NOT NULL CHECK (State = 'True' or State = 'False'),
    Time   datetime default getdate()
)
