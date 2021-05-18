-- Criando banco de dados 
DROP DATABASE IF EXISTS avaliacaoODAW;

CREATE DATABASE avaliacaoODAW; 

USE avaliacaoODAW;

-- Criando Table usuario
DROP TABLE IF EXISTS usuario;

CREATE TABLE `usuario` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(45) NOT NULL,
  `senha` varchar(45) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

-- Inserindo usuario admin
INSERT INTO `avaliacaoODAW`.`usuario`(`id`,`login`,`senha`)VALUES('1', 'admin', 'admin');

-- Criando Table usuario
DROP TABLE IF EXISTS despesa;

CREATE TABLE `despesa` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tipo` int(5) NOT NULL,
  `descricao` varchar(128) NOT NULL,
  `valor` float(25,2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;