-- phpMyAdmin SQL Dump
-- version 4.3.11
-- http://www.phpmyadmin.net
--
-- Gép: 127.0.0.1
-- Létrehozás ideje: 2015. Máj 07. 12:58
-- Kiszolgáló verziója: 5.6.24
-- PHP verzió: 5.6.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Adatbázis: `bankdb`
--

-- --------------------------------------------------------

--
-- Tábla szerkezet ehhez a táblához `accounts`
--

CREATE TABLE IF NOT EXISTS `accounts` (
  `number` int(11) NOT NULL,
  `client_name` varchar(40) NOT NULL,
  `created` date NOT NULL,
  `blocked` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- A tábla adatainak kiíratása `accounts`
--

INSERT INTO `accounts` (`number`, `client_name`, `created`, `blocked`) VALUES
(111222, 'Oliver Queen', '2002-12-31', 1),
(123456, 'Sherlock Holmes', '2007-03-07', 0),
(214142, 'John Watson', '2010-01-03', 1),
(231245, 'Barry Allen', '2003-09-01', 1),
(234143, 'John Watson', '2009-07-10', 0),
(234167, 'Tony Stark', '2010-05-02', 0),
(237653, 'Sherlock Holmes', '2008-02-29', 0),
(325235, 'Oliver Queen', '2012-09-25', 0),
(325444, 'Bruce Wayne', '1997-06-15', 0),
(341984, 'Tony Stark', '2008-05-04', 0),
(343452, 'Tony Stark', '2012-12-27', 1),
(343521, 'Bruce Wayne', '2008-11-30', 0),
(345212, 'Bruce Wayne', '2005-07-13', 1),
(353253, 'Oliver Queen', '2011-02-03', 0),
(356423, 'Walter White', '2008-09-01', 1),
(532434, 'Peter Parker', '2002-08-12', 0),
(654743, 'Tony Stark', '2013-04-30', 0);

-- --------------------------------------------------------

--
-- Tábla szerkezet ehhez a táblához `clients`
--

CREATE TABLE IF NOT EXISTS `clients` (
  `name` varchar(40) NOT NULL,
  `address` varchar(60) NOT NULL,
  `phone` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- A tábla adatainak kiíratása `clients`
--

INSERT INTO `clients` (`name`, `address`, `phone`) VALUES
('Barry Allen', '10 Star Street, Central City, United States', '00120145252'),
('Bruce Wayne', 'Wayne Manor, Gotham City, United States', '00119392005'),
('John Watson', 'Baker Street 221/A, London, United Kingdom', '+4420111889'),
('Oliver Queen', '10 Glade Street, Starling City, United States', '00120125252'),
('Peter Parker', '18 Chrystie Street, New York City, United States', '00119602002'),
('Sherlock Holmes', 'Baker Street 221/B, London, United Kingdom', '+4420101888'),
('Tony Stark', 'Avengers Tower, New York City, United States', '00120081962'),
('Walter White', '308 Negra Arroyo Lane, Albuquerque, NM', '00187104737');

-- --------------------------------------------------------

--
-- Tábla szerkezet ehhez a táblához `transaction`
--

CREATE TABLE IF NOT EXISTS `transaction` (
  `id` int(11) NOT NULL,
  `date` date NOT NULL,
  `amount` int(11) NOT NULL,
  `source` int(11) NOT NULL,
  `objective` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- A tábla adatainak kiíratása `transaction`
--

INSERT INTO `transaction` (`id`, `date`, `amount`, `source`, `objective`) VALUES
(1, '2014-03-24', 5000, 654743, 345212),
(2, '2014-04-02', 10000, 532434, 237653),
(3, '2014-07-13', 15000, 343521, 123456),
(4, '2014-08-16', 5000, 343521, 654743),
(5, '2014-09-02', 2000, 234167, 341984),
(6, '2014-10-25', 1000, 532434, 123456),
(7, '2014-12-01', 20000, 111222, 343452),
(8, '2014-12-10', 3000, 231245, 234143),
(9, '2014-12-11', 7000, 356423, 231245),
(10, '2014-12-12', 9000, 654743, 325235),
(11, '2014-12-20', 17000, 353253, 214142),
(12, '2015-05-04', 8000, 234167, 341984),
(13, '2015-05-05', 3000, 325444, 214142),
(14, '2015-05-06', 9000, 325235, 237653),
(15, '2015-05-06', 9000, 237653, 325235),
(16, '2015-05-06', 20000, 341984, 325235),
(17, '2015-05-06', 9000, 234167, 654743),
(18, '2015-05-06', 9000, 654743, 234167);

-- --------------------------------------------------------

--
-- Tábla szerkezet ehhez a táblához `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `user_id` text NOT NULL,
  `password` text NOT NULL,
  `name` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- A tábla adatainak kiíratása `users`
--

INSERT INTO `users` (`user_id`, `password`, `name`) VALUES
('gitune07', 'ultronpapa', 'Gitune'),
('tamas01', '12345', 'Tamas');

--
-- Indexek a kiírt táblákhoz
--

--
-- A tábla indexei `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`number`), ADD UNIQUE KEY `number` (`number`);

--
-- A tábla indexei `clients`
--
ALTER TABLE `clients`
  ADD PRIMARY KEY (`name`);

--
-- A tábla indexei `transaction`
--
ALTER TABLE `transaction`
  ADD PRIMARY KEY (`id`), ADD UNIQUE KEY `id` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
