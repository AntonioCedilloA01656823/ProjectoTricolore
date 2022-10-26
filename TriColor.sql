CREATE SCHEMA `tricolor`;

CREATE TABLE `tricolor`.`duenio` (
  `id` int,
  `area_code` int,
  `duenio_nombre` varchar(255),
  `created_at` datetime,
  `admin_id` int
);

CREATE TABLE `tricolor`.`users` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `full_name` varchar(255),
  `created_at` datetime,
  `area_code` int
);

CREATE TABLE `tricolor`.`order_per_pizza` (
  `order_id` int,
  `pizza_id` int,
  `quantity` int DEFAULT 1
);

CREATE TABLE `tricolor`.`orders` (
  `id` int PRIMARY KEY,
  `user_id` int UNIQUE NOT NULL,
  `status` varchar(255),
  `created_at` datetime
);

CREATE TABLE `tricolor`.`pizza` (
  `id` int PRIMARY KEY,
  `name` varchar(255),
  `duenio_id` int NOT NULL,
  `price` int,
  `status` ENUM ('out_of_stock', 'in_stock', 'running_low'),
  `created_at` datetime DEFAULT "now()"
);

ALTER TABLE `tricolor`.`duenio` ADD FOREIGN KEY (`admin_id`) REFERENCES `tricolor`.`users` (`id`);

ALTER TABLE `tricolor`.`order_per_pizza` ADD FOREIGN KEY (`order_id`) REFERENCES `tricolor`.`orders` (`id`);

ALTER TABLE `tricolor`.`order_per_pizza` ADD FOREIGN KEY (`pizza_id`) REFERENCES `tricolor`.`pizza` (`id`);

ALTER TABLE `tricolor`.`pizza` ADD FOREIGN KEY (`duenio_id`) REFERENCES `tricolor`.`duenio` (`id`);
