-- SimpleERP ERP System
-- Copyright (C) 2021 Miguel Nischor
--
-- File: Create_TCustomer.sql
-- Description: SQL script for TCustomer table creation
-- Author: Miguel Nischor <miguel@nischor.com.br>
USE `serp`

CREATE TABLE IF NOT EXISTS `tcustomer`
(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(80) NOT NULL,
  `address` VARCHAR(80),
  `phone` VARCHAR(15),
  `email` VARCHAR(80),
  `city` VARCHAR(80),
  `state` VARCHAR(80),
  `gender` CHAR(1) ENUM(`m``f`),
  `cpf` CHAR(11),
  `rg` VARCHAR(16),
  PRIMARY KEY `pk_id`(`id`)
) ENGINE = InnoDB;