create database QLSV --T?o CSDL sinh viên
use QLSV --S? d?ng CSDL
go
Create Table Sinhvien
(
MaSV int identity primary key,
TenSV Nvarchar(30) not null,
GT NVarchar (5) default 'Nam',
Ngaysinh Date check (Ngaysinh<getdate()),
Que Nvarchar(50) not null,
Lop Nvarchar (10)
)

 select * from Sinhvien;
 --select * from Sinhvien where Lop='L01';

 insert into sinhvien (TenSV,Ngaysinh,Que,Lop) 

values (N'Ph?m Trung Tính','01/05/1993',N'Qu?ng Ninh','L02')