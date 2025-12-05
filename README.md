# **Project Title:** CS Carpark Management System

## **Description:**

CS Carpark is a comprehensive C-based simulation of a car parking management system. It allows users to manage carpark operations including normal and premium parking, electric vehicle charging stations, carwash bays, and dynamic pricing with discounts. This project is designed to handle real-world scenarios such as parking, moving cars, tracking occupancy, applying discounts, and handling electric vehicle charging logistics.

Key features include:

* Dynamic management of normal and premium parking spaces
* Adding and moving cars within the carpark
* Tracking parking duration and calculating total charges
* Electric vehicle charging station management with distance/cable constraints
* Carwash bay functionality
* Discounts for empty spaces
* Real-time occupancy and availability tracking

This project is ideal for learning **data structures, 2D arrays, and simulation logic** in C programming.

---

## **README.md Content:**

````markdown
# CS Carpark Management System

CS Carpark is a C-based car parking simulation program that allows users to manage a carpark with various features such as premium parking, electric vehicle charging stations, and carwash bays.

## Features

- **Parking Management:** Park cars in normal or premium spaces.
- **Dynamic Pricing:** Premium parking and discounts for empty spaces.
- **Electric Vehicle Support:** Charging stations with cable length restrictions and availability checks.
- **Carwash Bays:** Cars can use carwash facilities.
- **Occupancy Tracking:** Track number of cars, free spaces, and total occupancy.
- **Move Cars:** Move cars between spaces within the carpark.
- **Command-driven interface:** Enter single-letter commands to interact with the system.

## How to Run

1. Clone the repository:
```bash
git clone https://github.com/<your-username>/cs-carpark.git
````

2. Navigate into the project folder:

```bash
cd cs-carpark
```

3. Compile the program:

```bash
gcc cs_carpark.c -o cs_carpark -lm
```

4. Run the program:

```bash
./cs_carpark
```

## Commands

| Command | Action                             |
| ------- | ---------------------------------- |
| `P`     | Print the current carpark layout   |
| `p`     | Park a new car                     |
| `o`     | Show total occupancy               |
| `F`     | Show free spaces remaining         |
| `d`     | Apply 10% discount to empty spaces |
| `f`     | Find a car by license plate        |
| `l`     | Remove a car from the carpark      |
| `e`     | Build electric charging station    |
| `c`     | Charge an electric car             |
| `m`     | Move a car to a new space          |
| `w`     | Build carwash bay                  |

## Carpark Configuration

* **Rows:** 8
* **Columns:** 6
* **Normal Parking Rate:** $10/hour
* **Premium Parking Rate:** $50/hour
* **Electric Charging Rate:** $7/hour
* **Carwash Service Rate:** $15
