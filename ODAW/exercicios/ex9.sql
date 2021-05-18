-- Criando BD
create database odawbd;

USE odawbd

-- Criando tabela

CREATE TABLE pessoa (ID int auto_increment primary key,name varchar(255), cpf varchar(11), rg varchar(10));

-- Visualizando tabela

show columns FROM pessoa;

-- Inserindo dados

INSERT INTO pessoa (name, cpf, rg) VALUES ( "Vinicius Gasparini", "12312378903", "9632587" ), ( "Paulo Gasparini", "99988877765", "1234567" ); 

-- Visualizando dados

SELECT * FROM pessoa;

-- Atualizando dados

UPDATE pessoa SET cpf = '09584682903' WHERE rg = '9632587'; 

-- Visualizando dados

SELECT * FROM pessoa;

-- Removendo dados

DELETE FROM pessoa WHERE (ID=1);

-- Visualizando dados

SELECT * FROM pessoa;

-- Apagando tabela dados

DROP TABLE pessoa;

-- Apagando BD

drop database odawbd;