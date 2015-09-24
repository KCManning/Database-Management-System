-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`DIVISIONS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`DIVISIONS` ;

CREATE TABLE IF NOT EXISTS `mydb`.`DIVISIONS` (
  `Division_ID` INT NOT NULL,
  `Div_Name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Division_ID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`VENDORS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`VENDORS` ;

CREATE TABLE IF NOT EXISTS `mydb`.`VENDORS` (
  `Vendor_ID` INT NOT NULL,
  `Ven_Name` VARCHAR(45) NOT NULL,
  `Ven_Number` INT NOT NULL,
  `Ven_Address` VARCHAR(45) NOT NULL,
  `Ven_Phone` INT NOT NULL,
  `Ven_Email` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Vendor_ID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PROGRAMMERS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`PROGRAMMERS` ;

CREATE TABLE IF NOT EXISTS `mydb`.`PROGRAMMERS` (
  `Programmer_ID` INT NOT NULL,
  `Prog_F_Name` VARCHAR(45) NOT NULL,
  `Prog_L_Name` VARCHAR(45) NOT NULL,
  `VENDORS_Vendor_ID` INT NOT NULL,
  PRIMARY KEY (`Programmer_ID`),
  INDEX `fk_PROGRAMMERS_VENDORS1_idx` (`VENDORS_Vendor_ID` ASC),
  CONSTRAINT `fk_PROGRAMMERS_VENDORS1`
    FOREIGN KEY (`VENDORS_Vendor_ID`)
    REFERENCES `mydb`.`VENDORS` (`Vendor_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`UNITS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`UNITS` ;

CREATE TABLE IF NOT EXISTS `mydb`.`UNITS` (
  `Unit_ID` INT NOT NULL,
  `Unit_Number` INT NOT NULL,
  `DIVISIONS_Division_ID` INT NOT NULL,
  PRIMARY KEY (`Unit_ID`),
  INDEX `fk_UNITS_DIVISIONS1_idx` (`DIVISIONS_Division_ID` ASC),
  CONSTRAINT `fk_UNITS_DIVISIONS1`
    FOREIGN KEY (`DIVISIONS_Division_ID`)
    REFERENCES `mydb`.`DIVISIONS` (`Division_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`CONTACTS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`CONTACTS` ;

CREATE TABLE IF NOT EXISTS `mydb`.`CONTACTS` (
  `Contact_ID` INT NOT NULL,
  `Contact_F_Name` VARCHAR(45) NOT NULL,
  `Contact_L_Name` VARCHAR(45) NOT NULL,
  `Contact_Phone` INT NOT NULL,
  `Contact_Email` VARCHAR(45) NOT NULL,
  `UNITS_Unit_ID` INT NOT NULL,
  PRIMARY KEY (`Contact_ID`),
  INDEX `fk_CONTACTS_UNITS1_idx` (`UNITS_Unit_ID` ASC),
  CONSTRAINT `fk_CONTACTS_UNITS1`
    FOREIGN KEY (`UNITS_Unit_ID`)
    REFERENCES `mydb`.`UNITS` (`Unit_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`EMPLOYEES`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`EMPLOYEES` ;

CREATE TABLE IF NOT EXISTS `mydb`.`EMPLOYEES` (
  `Employee_ID` INT NOT NULL,
  `Emp_F_Name` VARCHAR(45) NOT NULL,
  `Emp_L_Name` VARCHAR(45) NOT NULL,
  `Emp_Contact` INT NOT NULL,
  `Emp_User_Name` VARCHAR(45) NOT NULL,
  `Emp_Password` VARCHAR(45) NOT NULL,
  `Emp_Auth_Level` VARCHAR(45) NOT NULL,
  `Emp_Job_Title` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Employee_ID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`INVOICES`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`INVOICES` ;

CREATE TABLE IF NOT EXISTS `mydb`.`INVOICES` (
  `Invoice_ID` INT NOT NULL,
  `Inv_Number` INT NOT NULL,
  `Inv_Issue_Date` DATE NOT NULL,
  `Inv_Date_Received` DATE NOT NULL,
  `Inv_Date_Paid` DATE NOT NULL,
  `Inv_Terms` VARCHAR(45) NOT NULL,
  `Inv_Amount` DECIMAL(15,2) NOT NULL,
  `Inv_Rate` DECIMAL(9,2) NOT NULL,
  `Inv_Start_Date` DATE NOT NULL,
  `Inv_End_Date` DATE NOT NULL,
  `Inv_Status` VARCHAR(45) NOT NULL,
  `Inv_Accrual` VARCHAR(45) NULL,
  `Inv_Notes` VARCHAR(250) NULL,
  `VENDORS_Vendor_ID` INT NOT NULL,
  `PROGRAMMERS_Programmer_ID` INT NOT NULL,
  `EMPLOYEES_Employee_ID` INT NOT NULL,
  PRIMARY KEY (`Invoice_ID`),
  INDEX `fk_INVOICES_VENDORS_idx` (`VENDORS_Vendor_ID` ASC),
  INDEX `fk_INVOICES_PROGRAMMERS1_idx` (`PROGRAMMERS_Programmer_ID` ASC),
  INDEX `fk_INVOICES_EMPLOYEES1_idx` (`EMPLOYEES_Employee_ID` ASC),
  CONSTRAINT `fk_INVOICES_VENDORS`
    FOREIGN KEY (`VENDORS_Vendor_ID`)
    REFERENCES `mydb`.`VENDORS` (`Vendor_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_INVOICES_PROGRAMMERS1`
    FOREIGN KEY (`PROGRAMMERS_Programmer_ID`)
    REFERENCES `mydb`.`PROGRAMMERS` (`Programmer_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_INVOICES_EMPLOYEES1`
    FOREIGN KEY (`EMPLOYEES_Employee_ID`)
    REFERENCES `mydb`.`EMPLOYEES` (`Employee_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`CONTRACTS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`CONTRACTS` ;

CREATE TABLE IF NOT EXISTS `mydb`.`CONTRACTS` (
  `Contract_ID` INT NOT NULL,
  `Cont_Number` INT NOT NULL,
  `Cont_Start_Date` DATE NOT NULL,
  `Cont_End_Date` DATE NOT NULL,
  `Cont_Hourly_Rate` DECIMAL(7,2) NOT NULL,
  `Cont_Fee_Max` DECIMAL(15,2) NOT NULL,
  `Cont_Description` VARCHAR(150) NOT NULL,
  `Cont_Notes` VARCHAR(250) NULL,
  `PROGRAMMERS_Programmer_ID` INT NOT NULL,
  `UNITS_Unit_ID` INT NOT NULL,
  `CONTACTS_Contact_ID` INT NOT NULL,
  `VENDORS_Vendor_ID` INT NOT NULL,
  `EMPLOYEES_Employee_ID` INT NOT NULL,
  PRIMARY KEY (`Contract_ID`),
  INDEX `fk_CONTRACTS_PROGRAMMERS1_idx` (`PROGRAMMERS_Programmer_ID` ASC),
  INDEX `fk_CONTRACTS_UNITS1_idx` (`UNITS_Unit_ID` ASC),
  INDEX `fk_CONTRACTS_CONTACTS1_idx` (`CONTACTS_Contact_ID` ASC),
  INDEX `fk_CONTRACTS_VENDORS1_idx` (`VENDORS_Vendor_ID` ASC),
  INDEX `fk_CONTRACTS_EMPLOYEES1_idx` (`EMPLOYEES_Employee_ID` ASC),
  CONSTRAINT `fk_CONTRACTS_PROGRAMMERS1`
    FOREIGN KEY (`PROGRAMMERS_Programmer_ID`)
    REFERENCES `mydb`.`PROGRAMMERS` (`Programmer_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_CONTRACTS_UNITS1`
    FOREIGN KEY (`UNITS_Unit_ID`)
    REFERENCES `mydb`.`UNITS` (`Unit_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_CONTRACTS_CONTACTS1`
    FOREIGN KEY (`CONTACTS_Contact_ID`)
    REFERENCES `mydb`.`CONTACTS` (`Contact_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_CONTRACTS_VENDORS1`
    FOREIGN KEY (`VENDORS_Vendor_ID`)
    REFERENCES `mydb`.`VENDORS` (`Vendor_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_CONTRACTS_EMPLOYEES1`
    FOREIGN KEY (`EMPLOYEES_Employee_ID`)
    REFERENCES `mydb`.`EMPLOYEES` (`Employee_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

INSERT INTO EMPLOYEES (Emp_F_Name,Emp_L_Name,Emp_Contact,Emp_User_Name,Emp_Password,Emp_Auth_Level,Emp_Job_Title,Employee_ID)
VALUES ('Root','Access','5555555','root','admin','admin','project testing','123456789');
