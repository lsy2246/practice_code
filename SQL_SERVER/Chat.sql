CREATE LOGIN Chat
    WITH PASSWORD = '123456';
GO

DROP DATABASE Chat;
GO

CREATE DATABASE Chat;
GO

USE Chat;
GO

CREATE USER Chat
    FOR LOGIN Chat;
GO

ALTER ROLE db_owner ADD MEMBER Chat;
GO

CREATE TABLE Account
(
    Id BIGINT PRIMARY KEY IDENTITY(1000,1),
    Password VARCHAR(50) not null,
    NetName NVARCHAR(50) ,
    State BIT default 0 CHECK(State=1 or State=0),
    UpDataTime datetime default GETDATE()
)
GO

CREATE TABLE Contacts
(
    UserId BIGINT REFERENCES Account(Id) not null ,
    ContactsId BIGINT REFERENCES Account(Id) not null,
    State BIT default 0 CHECK(State=1 or State=0),
    Remark NVARCHAR(50),
    UpDataTime datetime default GETDATE()
)
GO

CREATE TABLE History
(
    Send BIGINT REFERENCES Account(Id) NOT NULL,
    Receive BIGINT REFERENCES Account(Id) NOT NULL,
    Type NVARCHAR(50) NOT NULL,
    Content NVARCHAR(200) NOT NULL,
    Time DATETIME DEFAULT GETDATE()
)

GO

-- Account表的更新触发器
CREATE TRIGGER trg_UpdateUpDataTimeAccount
ON Account
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
    SET NOCOUNT ON;
    UPDATE Account
    SET UpDataTime = GETDATE()
    WHERE Id IN (SELECT Id FROM inserted UNION SELECT Id FROM deleted);
END;
GO


-- Contacts表的更新触发器
CREATE TRIGGER trg_UpdateUpDataTimeContacts
ON Contacts
AFTER INSERT, UPDATE
AS
BEGIN
    SET NOCOUNT ON;

    -- 更新Account表中的UpDataTime字段，仅在Contacts相关记录发生插入或更新时
    UPDATE Account
    SET UpDataTime = GETDATE()
    WHERE Id IN (SELECT UserId FROM inserted)
       OR Id IN (SELECT ContactsId FROM inserted);

    -- 更新Contacts表的Remark列为对应ContactsId的NetName
    UPDATE Contacts
    SET Remark = (SELECT NetName FROM Account WHERE Id = ContactsId)
    WHERE ContactsId IN (SELECT ContactsId FROM inserted)
       OR ContactsId IN (SELECT ContactsId FROM deleted);
END;
GO

-- History表的更新触发器
CREATE TRIGGER trg_UpdateUpDataTimeHistory
ON History
AFTER INSERT, UPDATE
AS
BEGIN
    SET NOCOUNT ON;

    -- 仅更新Account表中发送者和接收者的UpDataTime字段
    UPDATE Account
    SET UpDataTime = GETDATE()
    WHERE Id IN (SELECT Send FROM inserted)
       OR Id IN (SELECT Receive FROM inserted);
END;
GO
