-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Review the crime scene reports for the corresponding time and place
SELECT * FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Check the witness interviews
SELECT * from interviews WHERE year = 2023 AND month = 7 AND day = 28;

-- Check atm transactions in the date and locations for wihthdrawals
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';

-- Check the people who did those transactions in the ATM
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE ye
ar = 2023 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street'));

-- check the bakery security longs for exits past 10:30 on the day of the theft:
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10;

-- match with license plates and people
SELECT name FROM people WHERE license_plate = '1106N58' OR license_plate = '322W7JE' OR license_plate = '0NTHK55';

--Check the phone records for calls of less than 60 seconds made on that day
SELECT * FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Taylor' OR name = 'Diana' OR name = 'Kelsey');

-- Check flights leaving Fiftyville the following day in the mornign
SELECT * from flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = 8;

--check the passengers on the flight
SELECT * FROM passengers WHERE flight_id = 36;
