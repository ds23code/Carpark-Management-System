// Program name: CS carpark by DS23 
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define CARPARK_ROWS 8
#define CARPARK_COLUMNS 6
#define NORMAL_PARKING_RATE 10
#define EMPTY -1
#define PREMIUM_PARKING_RATE 50
#define ELECTRIC_PARKING_RATE 7
#define DISCOUNT 0.9 //THAT MEANS 10% DISCOUNT
#define CARWASH_PARKING_RATE 15

enum space_type {
    NORMAL,
    PREMIUM,
    CARWASH_BAY,
    ELECTRIC_CHARGING_STATION
};

struct car_space {
    enum space_type type;
    int normal_parking_rate;
    int premium_parking_rate;
    int electric_parking_rate;
    int licence_plate;
    int occupied_since;
    int discount_applied;
    int cable_length;
    int charge_starttime;
    int charge_endtime;
    int in_use;
    int till_amount;
    int tot_parking_time;    
};

struct car_location {
    enum space_type type;
    int row;
    int col;
    int normal_parking_rate;
    int premium_parking_rate;
    int electric_parking_rate;
    int licence_plate;
    int occupied_since; //start
    int discount_applied;
    int cable_length;
    int charge_starttime;
    int charge_endtime;
    int in_use;
    int till_amount; 
    int tot_parking_time;
};

//Stage 1.2 - FUNCTION PROTOTYPE Setting Premium Row
void set_premium_row(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], int premium_parking_row );

// Stage 1.4 - FUNCTION PROTOTYPE Parking More Cars
int parking_slot(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no,int row,int col,int time_of_entry);

// Stage 1.5 - FUNCTION PROTOTYPE Total Occupancy
void total_occupancy(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

// Stage 2.1 - FUNCTION PROTOTYPE Free Spaces Remaining
void free_spaces_remaining(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

// Stage 2.2 - FUNCTION PROTOTYPE Discount Empty Spaces
void discount_empty_spaces(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

// Stage 2.3 - FUNCTION PROTOTYPE Find a Car
struct car_location find_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no);

// Stage 2.4 - FUNCTION PROTOTYPE Leaving A Carpark
void leaving_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no, int time_of_exit, char exit_type);

// Stage 3.1 - FUNCTION PROTOTYPE Build electric charging stations
void electric_charging(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

// Stage 3.2 - FUNCTION PROTOTYPE Charging cars
void charging_cars(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

// Stage 3.3 - FUNCTION PROTOTYPES Moving Cars
void moving_cars(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
int licence_plate_no, int row, int col, int time_of_move);

// Stage 3.4 - FUNCTION PROTOTYPES Car Wash Bays
void carwash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

// STAGE 4.2
void can_car_exit_checks(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no, int row, int col, int *exit_check);

// SUB FUNCTION PROTOTPYES THAT WILL BE USED IN VARIOUS STAGES
void available_charging_slot(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int calculate_parking_rate(struct car_location slot, int time_of_exit );
int elect_charge(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no);
int adjacent_space_check(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int row, int col);
int adjacent_carwash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int row, int col);
int check_car_slot_type(struct car_space slot);

void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_car_space(struct car_space space);

int main(void) {
    // Set up carpark. `carpark` is a 2D array of `struct car_space`s. 
    // It is `CARPARK_ROWS` x `CARPARK_COLUMNS` in size (which is 8 x 6 for this
    // assignment).
    struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS];
    struct car_location slot;
    // This will initialise all spaces in the carpark as NORMAL spaces which are 
    // all EMPTY.
    initialise_carpark(carpark);
    // TODO: Start writing code here!
    // TODO: Stage 1.1 - Carpark setup. Scan in which row of the carpark to be 
    // reserved for premium parking. The carpark should be printed once premium
    // parking is reserved.

    //THESE ARE ALL THE VARIABLES FROM ALL THE STAGES THAT WILL BE NEEDED 
    //WHEN THE USER ENTERS A COMMAND
    int premium_parking_row;
    int num_cars;
    int car_counter;
    int licence_plate_no;
    int row;
    int col;
    char user_input;
    int loop_breaker = 0;
    char scanf_return;
    int time_of_exit;
    int time_of_entry;
    int return_code = EMPTY;

    //INITIAL PRINT STATEMENT WHEN THE CODE IS EXECUTED
    printf("Welcome to CS Carpark!\n\n");
    printf("Which row of the carpark would you like to reserve for premium parking? ");
    /*USER ENTERS THE THE ROW NUMBER*/
    /*ENTERED ROW NUMBER WILL NOW BE SET TO PREMIUM ROW*/
    /*NOTE: THE PARKING RATES FOR PREMIUM ROW IS DIFFERENT FROM NORMAL, THUS
    PREMIUM RATES ARE SET IN SET_PREMIUM_ROW FUNCTION*/
    scanf("%d", &premium_parking_row);
    set_premium_row(carpark, premium_parking_row );
    /*PRINTS THE CARPARK AREA THAT SHOWS THE UPDATED PREMIUM ROW*/
    print_carpark(carpark);
    //USER ENTERS INITIAL CARS'S LICENSE PLATE NO, ROW, COL
    printf("Add all current cars to the carpark. How many cars would you like to add? ");
    scanf("%d", &num_cars);
    /*FOR LOOP RUNS UNITL ALL THE CARS THAT USER WANTED TO PARK INTITALLY ARE 
    SUCCESSFULY PARKED TO THE DESIGNATED PARKING SLOT*/
    printf("Where would you like to park each car?\n");
    for (car_counter = 0; car_counter < num_cars; car_counter++) {
        scanf("%d %d %d", &licence_plate_no, &row, &col);
        /*IF THE USER ENTERS THE ROW COL THAT IS OUT OF BOUND*/
        /*ERROR STATEMENT IS PRINTED STATING INVALID CAR SPACE*/
        if (row < 0 
        || row >= CARPARK_ROWS 
        || col < 0 
        || col >= CARPARK_COLUMNS) {
            printf("Invalid car space!\n");
        }
        /*IF THERE ARE NO ERRORS IN THE USER INPUT 
        THEN THEN CARS WILL BE PARKED TO THE DESIGNATED PARKING SLOT*/
        /*NORMAL PARKING RATE IS APPLIED TO THE CARS THAT ARE IN NORMAL ROW
        NOTE: DISCOUNT NOW IS EMPTY SINCE USER DIDNT ENTER 'd' COMMAND*/
        /*OCCUPIED SINCE WILL NOW BE SET TO ZERO, THIS ACCOUNTS FOR THE TOTAL
        DURATION THE CAR WAS IN THE CARPARK*/ 
        else {
            carpark[row][col].normal_parking_rate = NORMAL_PARKING_RATE;
            carpark[row][col].licence_plate = licence_plate_no;
            carpark[row][col].occupied_since = 0;
            carpark[row][col].discount_applied = EMPTY;
        }
    }
    /*PRINTS THE UPDATED CARKPARK SHOWING ALL THE CARS THAT HAVE BEEN PARKED
    BEFORE THE BUSSINESS STARTS*/
    print_carpark(carpark);
    printf("The carpark is now ready for business!\n");
 
    //TAKES ALL THE LETTER COMMANDS
    //IF THE INPUT IS RIGHT RELEVANT FUNCTION IS CALLED
    printf("Enter a command: ");
    /*LOOP BREAKER VARIABLE IS USED SO THAT WHEN THE USER ENTERS CTRL+D THE 
    CARPARK PROGRAM STOPS*/
    while (loop_breaker != 1) {
        scanf_return = scanf(" %c", &user_input);

        //WHEN USER ENTERS CTRL+D
        //PRINT STATEMENT WILL BE PRINTED STATING CARPARK IS CLOSED
        if (scanf_return == EOF) {
            printf("The carpark is now closed. Bye!\n");
            //THIS LOOP BREAKER EXITS FROM THE WHILE LOOP [SAME FUNC. AS BREAK]
            loop_breaker = 1;
        }
        //IF THE INPUT IS CORRECT RELEVANT 'LETTER' FUNCTIONS ARE CALLED
        else {
            //ALWAYS PRINTS THE UPDATED CARPARK
            if (user_input == 'P') {
                print_carpark(carpark);
                printf("Enter a command: "); 
            }
            // Stage 1.4 - Parking More Cars.    
            else if (user_input == 'p') {
                scanf("%d", &licence_plate_no);
                scanf("%d", &row);
                scanf("%d", &col);
                scanf("%d", &time_of_entry);
                return_code = parking_slot(carpark, licence_plate_no, 
                row, col , time_of_entry);
                //PRINTS OUT THE STATEMENT STATING THAT THE CAR IS ADDED INTO CARSPACE
                if (return_code == 0) {
                    printf("Car %04d was added into car space (%d, %d) at time %d!\n", 
                    licence_plate_no, row, col, time_of_entry);
                }    
                printf("Enter a command: "); 
            }
            // Stage 1.5 - Total Occupancy.
            else if (user_input == 'o') {
                total_occupancy(carpark);
                printf("Enter a command: ");
            }
            // Stage 2.1 - Free Spaces Remaining.
            else if (user_input == 'F') {
                free_spaces_remaining(carpark);
                printf("Enter a command: ");
            }
            // Stage 2.2 - Discount Empty Spaces.
            else if (user_input == 'd') {
                discount_empty_spaces(carpark);
                printf("Enter a command: ");
            }
            // Stage 2.3 - Find A Car.
            else if (user_input == 'f') {
                scanf("%d", &licence_plate_no);
                slot = find_car(carpark, licence_plate_no);
                if (slot.in_use == 1) {
                    printf("Car %d is parked in car space (%d, %d).\n", 
                    slot.licence_plate, slot.row, slot.col);
                }
                printf("Enter a command: ");
            }
            // Stage 2.4 - Leaving the Carpark.
            else if (user_input == 'l') {
                scanf("%d", &licence_plate_no);
                scanf("%d", &time_of_exit);
                leaving_carpark(carpark, licence_plate_no, time_of_exit, 'e');
                printf("Enter a command: ");
            }
            // Stage 3.1 - Build electric charging stations
            else if (user_input == 'e') {
                electric_charging(carpark);
                printf("Enter a command: ");
            }
            // Stage 3.2 - Charging cars
            else if (user_input == 'c') {
                charging_cars(carpark);
                printf("Enter a command: ");
            }
            // Stage 3.3 - Moving cars
            else if (user_input == 'm') {
                scanf("%d", &licence_plate_no);
                scanf("%d", &row);
                scanf("%d", &col);
                scanf("%d", &time_of_entry);
                moving_cars(carpark, licence_plate_no, row, col, time_of_entry);
                printf("Enter a command: ");
            }
            // Stage 3.4 - Carwash Bays
            else if (user_input == 'w') {
                carwash(carpark);
                printf("Enter a command: ");
            }
            // Stage 4.1 - Parking History
            // else if (user_input == 'h') {
            //     scanf("%d", &licence_plate_no);
            //     parking_history(carpark, licence_plate_no);
            //     printf("Enter a command: ");
            //}
        }
    }
    return 0;
}

// Stage 1.2 - CREATING FUNCTION Setting Premium Row
void set_premium_row(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int premium_parking_row ) {
    int parking_columns = 0;
    for (parking_columns = 0; parking_columns < CARPARK_COLUMNS; parking_columns++) {
        carpark[premium_parking_row][parking_columns].type = PREMIUM;
        carpark[premium_parking_row][parking_columns].normal_parking_rate = NORMAL_PARKING_RATE;
        carpark[premium_parking_row][parking_columns].licence_plate = EMPTY;
        carpark[premium_parking_row][parking_columns].occupied_since = 0;
    }
}

// Stage 1.4 - CREATING FUNCTION Parking More Cars.
int parking_slot(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no, int row, int col, int time_of_entry ) {

    //IF USER INPUTS ROW, COL OUTSIDE THE PARKING AREA
    //PRINTS OUT THE STATEMENT STATING THAT THE CARSPACE ENTERED IS INVALID
    if (row < 0 ||
        row >= CARPARK_ROWS ||
        col < 0 ||
        col >= CARPARK_COLUMNS) {
        printf("Invalid car space!\n");
    }


    // FOR Stage 3.1 - TRYING TO PARK ON OCCUPIED CHARGING STATION 
    //IF CHARGING STATION IS OCCUPIED [NOT EMPTY]
    //PRINTS OUT THE STATEMENT STATING THAT THE STATION IS OCCUPIED
    else if (carpark[row][col].type == ELECTRIC_CHARGING_STATION 
            && carpark[row][col].occupied_since != EMPTY) {
        printf("Cannot park on a space occupied by an electric charging station.\n");
    }
    // FOR Stage 1.4 - TRYING TO PARK ON OCCUPIED CARSPACE
    //IF THE CARSPACE IS ALREADY OCCUPIED [SOME OTHER CAR IS PARKED]
    //PRINTS OUT THE STATEMENT STATING THAT ITS OCCUPIED
    else if (carpark[row][col].licence_plate != EMPTY 
            && carpark[row][col].occupied_since != EMPTY) {
        printf("Car space is already occupied!\n");
    }
    // FOR STAGE 3.4 - WASHING CAR IN THE CARWASH BAY
    //IF CAR IS BEING PARKED AT CAR WASH BAY
    //PRINTS OUT THE STATEMENT STATING THAT THE CAR IS NOW USING THE CARWASH BAY
    else if (carpark[row][col].type == CARWASH_BAY) {
        printf("Car %d is now using the carwash bay located at (%d, %d).\n", 
        licence_plate_no, row, col);
        carpark[row][col].licence_plate = licence_plate_no;
        carpark[row][col].tot_parking_time = time_of_entry - 
        carpark[row][col].occupied_since;
        carpark[row][col].occupied_since = time_of_entry;       
        carpark[row][col].in_use = 1;
    }
    //IF THE USER INPUT IS ALL CORRECT
    //THEN THE CAR WILL BE ADDED TO THE CAR SPACE
    else {
        //THIS IS AN ADDITIONAL CHECK FOR STAGE 2.4
        //CHECKS WHETHER THE DISCOUNT APPLIED IS REVERTED
        //ONCE THE PREVIOUS CAR ON THIS CAR SPACE LEFT
        if (carpark[row][col].discount_applied == EMPTY) {
            carpark[row][col].normal_parking_rate = NORMAL_PARKING_RATE;            
        }
        carpark[row][col].licence_plate = licence_plate_no;
        carpark[row][col].tot_parking_time = time_of_entry - 
        carpark[row][col].occupied_since;
        carpark[row][col].occupied_since = time_of_entry;
        carpark[row][col].in_use = 1;
        return 0;
    }
    return -1;
}

// Stage 1.5 - CREATING FUNCTION Total Occupancy.
void total_occupancy(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    
    int num_cars = 0;
    int empty_spaces = 0;

    //FOR LOOP COUNTS THE EMPTY SPACES IN THE PARKING AREA
    //IF THE LICENSE PLATE IS EMPTY 
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate != EMPTY) {
                num_cars++;
            }
        }
    }
    //CALCULATES THE EMPTY SPACES
    empty_spaces = CARPARK_ROWS * CARPARK_COLUMNS - num_cars;
    //PRINTS THE NUMBER OF EMPTY SPACES
    printf("There are currently %d cars and %d empty car spaces in the carpark.\n", 
    num_cars, empty_spaces);
}

// Stage 2.1  - CREATING FUNCTION Free Spaces Remaining.
void free_spaces_remaining(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    
    int row, col;
    int empty_spaces = 0;

    //PRINTS OUT THE NORMAL AVAILABLE [EMPTY] SPACES
    printf("The normal car spaces that are still available are:\n");
    //FOR LOOP COUNTS THE NORMAL EMPTY SPACES IN THE PARKING AREA
    for (row = 0; row < CARPARK_ROWS; row++) {
        for (col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].type == NORMAL 
             && carpark[row][col].licence_plate == EMPTY) {
                //PRINTS OUT THE ROL, COL AND THE PARKING RATE OF EACH CARSPACE
                printf("(%d, %d): $%d\n", 
                row, col, carpark[row][col].normal_parking_rate);
                //COUNTS TOTAL NUMBER OF EMPTY SPACES
                empty_spaces++;
            }
        }
    }
    //AFTER FOR LOOP CHECKS THE WHOLE CARPARK
    //IF THERE ARE NO NORMAL EMPTY SPACES 
    //PRINTS NONE [NO EMPTY SPACES]
    if (empty_spaces == 0) {
        printf("NONE\n");
    }
    printf("\n");
    //PRINTS OUT THE PREMIUM AVAILABLE [EMPTY] SPACES
    printf("The premium car spaces that are still available are:\n");
    //FOR LOOP COUNTS THE PREMIUM EMPTY SPACES IN THE PARKING AREA
    for (row = 0; row < CARPARK_ROWS; row++) {
        for (col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].type == PREMIUM 
             && carpark[row][col].licence_plate == EMPTY) {
                //PRINTS OUT THE ROL, COL AND THE PARKING RATE OF EACH CARSPACE
                printf("(%d, %d): $%d\n", 
                row, col, carpark[row][col].premium_parking_rate);
                //COUNTS TOTAL NUMBER OF EMPTY SPACES
                empty_spaces++;
            }
        }
    }
    //IF THERE ARE NO PREMIUM EMPTY SPACES
    //AFTER FOR LOOP CHECKS THE WHOLE CARPARK
    //PRINTS NONE [NO EMPTY SPACES]
    if (empty_spaces == 0) {
        printf("NONE\n");
    }
    printf("\n");
}

// Stage 2.2 - CREATING A FUNCTION Discount Empty Spaces
void discount_empty_spaces(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {

    int row, col;

    //FOR LOOP APPLIES DISCOUNT TO ALL THE EMPTY SPACES
    for (row = 0; row < CARPARK_ROWS; row++) {
        for (col = 0; col < CARPARK_COLUMNS; col++) {            
            //FIRST CHECKS IF THE CARSPACE IS EMPTY [LICENCE PLATE EMPTY]
            if (carpark[row][col].licence_plate == EMPTY) {                
                //APPLIES DISCOUNT TO NORMAL CARSPACES
                if (carpark[row][col].type == NORMAL) {
                    carpark[row][col].normal_parking_rate *= DISCOUNT;
                    carpark[row][col].discount_applied = 1;
                }
                //APPLIES DISCOUNT TO PREMIUM CARSPACES
                if (carpark[row][col].type == PREMIUM) {
                    carpark[row][col].premium_parking_rate *= DISCOUNT;
                    carpark[row][col].discount_applied = 1;
                }
            }
        }
    }
    //PRINTS OUT THE DISCOUNT STATEMENT
    printf("A 10%% discount has been applied to all empty spaces! \n");
}

// Stage 2.3 CREATING FUNCTION Find A Car
//THIS FIND FUNCTION WILL BE USED IN VARIOUS PLACES
//IT CHECKS WHETHER THE CAR IS IN CARPARK
struct car_location find_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no ) {

    int row;
    int col;
    int car_found = 0;
    struct car_location slot;

    //FOR LOOP LOCATES A PARTICULAR CAR FROM THE CAR SPACE
    for (row = 0; row < CARPARK_ROWS; row++) {
        for (col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate != EMPTY && car_found == 0) {
                //IF THE LICENCE PLATE MATCHES WITH THE ONE IN THE CARSPACE
                if (carpark[row][col].licence_plate == licence_plate_no 
                    && carpark[row][col].type != ELECTRIC_CHARGING_STATION) {
                    //UPDATES THE SLOT IN USE VARIABLE TO 1
                    /*THIS SLOT VARIABLE IN USE WILL BE USED IN VARIOUS PLACES
                    TO DETERMINE WHETHER THE CAR IS ALLOCATED TO A SLOT OR NOT*/
                    slot.in_use = 1;
                    //ASSIGNS ALL THE CAR IDENTIFIERS TO SLOT
                    /*NOTE TO THE READER: MAKE SURE YOU HAVE A LOOK TO THE 
                    CAR IDENTIFIERS BELOW*/
                    //THIS ALL HAPPENS IN THE BACKGROUND 
                    slot.row = row;
                    slot.col = col;
                    slot.licence_plate = licence_plate_no;
                    slot.occupied_since = carpark[row][col].occupied_since;
                    slot.type = carpark[row][col].type;
                    slot.premium_parking_rate = carpark[row][col].premium_parking_rate;
                    slot.normal_parking_rate = carpark[row][col].normal_parking_rate;
                    slot.electric_parking_rate = carpark[row][col].electric_parking_rate;
                    slot.charge_endtime = carpark[row][col].charge_endtime;
                    slot.charge_starttime = carpark[row][col].charge_starttime;
                    slot.till_amount = carpark[row][col].till_amount;
                    slot.tot_parking_time = carpark[row][col].tot_parking_time;
                    //CAR FOUND VARIABLE UPDATES TO 1 AFTER THE CAR IS FOUND
                    car_found = 1;
                }
            }   
        }
    }
    //IF CAR IS NOT FOUND
    //AFTER FOR LOOP CHECKS THE WHOLE CARPARK
    //PRINTS THE CAR IS NOT FOUND
    if (car_found == 0) {
        printf("No car with licence plate number %d could be found.\n", licence_plate_no);
        slot.in_use = 0;
    }
    return slot;
}

// Stage 2.4 - CREATING FUNCTION Leaving The Carpark.
//THIS LEAVING CARPARK FUNCTION IS USED IN VARIOUS PLACES
//ONCE THE CAR LEAVES THE SPOT ALL THE 'CAR IDENTIFIERS' ARE REVERTED 
//THERE ARE TWO EXIT TPYES: TYPE 'e' and TYPE 'm'
//TPYE 'e' IS USED WHEN THE CAR IS EXITING THE CARPARK
//TYPE 'm' IS USED WHEN THE CAR IS MOVING TO A NEW CARSPACE 
void leaving_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no, int time_of_exit, char exit_type) {
    
    int total_price = 0;
    int parking_time = 0;
    struct car_location slot;
    //int row = 0;
    //int col = 0;
    //int exit_check = 0;

    //RUNS FIND FUNCTION TO CHECK IF THE CAR EXITS
    slot = find_car(carpark, licence_plate_no);
    // FOR Stage 4.2 - CHECK IF CAR CAN LEAVE
    //RUNS EXIT CHECKS RELEVANT TO STAGE 4.2
    //can_car_exit_checks(carpark, licence_plate_no, row, col, &exit_check);
    /*NOTE:AFTER RUNNING THE FIND FUNTION SLOT IN USE WAS UPDATED TO 1, 
    IF THE CAR WAS FOUND WHILE RUNNING 'FIND'*/
    //ONLY RUNS OF THE CAR IS FOUND
    if (slot.in_use == 1) {
        //CALCULATES THE PARKING TIME
        if (slot.till_amount > 0  ) {
            parking_time = time_of_exit - slot.occupied_since + slot.tot_parking_time;
        } 
        else          
            parking_time = time_of_exit - slot.occupied_since; 
        //PRINTS IF THE TIME OF EXIT ENTERED IS INVALID
        if (parking_time < 0) {
            printf("The time of exit provided is invalid.\n");
        }  
        //IF THE USER INPUT IS ALL CORRECT  
        else {
            //CALCULATES THE TOTAL PRICE
            //BASED ON THE PARKING TIME [AND IN SOME CASE IF CAR WAS CHARGING AS WELL]
            total_price = calculate_parking_rate(slot, time_of_exit) 
            + elect_charge(carpark, licence_plate_no);
            //REVERTS ALL THE FIELDS BACK TO THE ORIGINAL ONCE THE CAR LEAVES
            //CAR COULD BE MOVING TO ANOTHER SPOT
            //CAR COULD BE LEAVING THE CARPARK
            carpark[slot.row][slot.col].discount_applied = EMPTY;
            carpark[slot.row][slot.col].licence_plate = EMPTY;
            carpark[slot.row][slot.col].occupied_since = 0;
            carpark[slot.row][slot.col].normal_parking_rate = NORMAL_PARKING_RATE;
            carpark[slot.row][slot.col].premium_parking_rate = PREMIUM_PARKING_RATE;
            carpark[slot.row][slot.col].electric_parking_rate = ELECTRIC_PARKING_RATE;            
            //IF CAR IS LEAVING THE CARPARK THEN THE TOTAL PRICE IS SHOWN
            //EXIT TYPE IS E [EXITING THE CARSPACE]
            if (exit_type == 'e' ) {
                printf("Car %d was parked for %d hours. " 
                "The total price for this duration is $%d.\n", 
                licence_plate_no, parking_time, total_price );
                //TOTAL PRICE IS NOT SHOWN WHEN THE EXIT TYPE IS 'm'
                //SINCE THE CAR IS RATHER MOVING TO A NEW LOCATION  
            }
        } 
    }
}

//THIS IS A SUBFUNCTION THAT CALCULATES THE PARKING RATES BASED ON THE:
//NORMAL ROW, PREMIUM ROW, ELECTRIC CHARGING DURATION [IF USED], CARWASH [IF USED]
int calculate_parking_rate (struct car_location slot, int time_of_exit) {

    int total_price = 0;
    int elect_total_price = 0;
    int parking_time = 0;  
    
    //CALCULATES THE PARKING TIME
    //FROM THE TIME WHEN THE CAR FIRST ENTERED TO THE TIME OF EXIT
    parking_time = time_of_exit - slot.occupied_since;
    //CALCULATES THE TOTAL PRICE OF PREMIUM CARSPACE
    if (slot.type == PREMIUM) {
        total_price =  parking_time * slot.premium_parking_rate;
    }
    //CALCULATES THE TOTAL PRICE OF NORMAL CARSPACE 
    else if (slot.type == NORMAL) {
        total_price = parking_time * slot.normal_parking_rate;
    }
    //ALWAYS CHECK IF THERE IS ADDON CARWASH
    if (slot.type == CARWASH_BAY) {
        total_price = total_price + CARWASH_PARKING_RATE;
    } 
    //ADDS THE ELECTRIC CHARGING PRICES TO THE TOTAL PRICE
    //IF THE CAR DIDNT ELECTRIC CHARGE THEN NO ELECTRIC PRICE IS ADDED
    total_price = total_price + elect_total_price + slot.till_amount;
    return total_price;
}

//THIS FUNCTION ACCOUNTS FOR THE ELECTRIC CHARGING RATES
/*NOTE: ELECTRIC CHARGING TIME DURATION DIFFERS FROM OCCUPIED SINCE DURATION.
HERE IS AN EXAMPLE TO EXPLAIN THE STATEMENT ABOVE:
EXAMPLE: CAR MIGHT BE CHARGING FOR 2 HOURS BUT WAS PARKED IN THE CARSPACE 
FOR 6 HOURS.*/
int elect_charge(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no) {

    int col;
    int row;
    int elect_total_price = 0;

    //FOR LOOP CHECKS IF ENTERED LICENCE PLATE IS CHARGING
    for (row = 0; row < CARPARK_ROWS; row++) {
        for (col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].type == ELECTRIC_CHARGING_STATION && 
                carpark[row][col].licence_plate == licence_plate_no ) {
                //ELECTRIC CHARGES ARE BASED ON THE DURATION OF CHARGING
                //DURATION OF CHARGING = CHARGE ENDTIME MINUS CHARGE STARTTIME
                elect_total_price = carpark[row][col].electric_parking_rate *
                (carpark[row][col].charge_endtime - 
                carpark[row][col].charge_starttime);
            }
        }
    }
    return elect_total_price;
}

// Stage 3.1 - CREATING FUNCTION Build electric charging stations.
//THIS FUNCTION BUILDS THE ELECTRIC CHARGING STATION IN THA CARPARK
void electric_charging(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    
    int row;
    int col;
    int build_time;
    int cable_length;

    //USER ENTERS ROW, COL, BUILD TIME, CABLE LENGTH 
    scanf("%d", &row);
    scanf("%d", &col);
    scanf("%d", &build_time);
    scanf("%d", &cable_length);
    //ON THAT PARTICULAR CARSPACE ELECTRIC CHARGER IS BUILD
    //UPDATE THE TYPE TO 'CHARGER'
    carpark[row][col].type = ELECTRIC_CHARGING_STATION;
    carpark[row][col].occupied_since = 0;
    //ASSIGNS CABLE LENGHT TO CARPARK STRUCT
    carpark[row][col].cable_length = cable_length;
    //PRINTS OUT THE STATEMENT STATING THAT THE CHARGER IS BUILT 
    //ON THE ROL COL THAT THE USER ENTERED
    printf("Electric charging station has been built on space (%d, %d) "
     "at time %d with cable length of %d.\n", row, col, build_time, cable_length); 
}

// Stage 3.2 - CREATING FUNCTION Charging Cars.
//THIS FUNCTION CONNECTS THE ELECTRIC CAR TO THE CHARGING STATION
void charging_cars(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    
    int licence_plate_no;
    int charge_from;
    int charge_til;
    int row;
    int col;
    int min_distance = 99;
    int cal_distance = 0;
    int x_car = -1;
    int y_car = -1;
    int x_charger = -1;
    int y_charger = 999;
    int cable_length = 0;
    struct car_location slot;

    //USER ENTERS THE LICENCE PLATE, CHARGE START TIME, CHARGE END TIME
    scanf("%d", &licence_plate_no);
    scanf("%d", &charge_from);
    scanf("%d", &charge_til); 
    //RUNS FIND FUNCTION TO CHECK IF THE CAR EXITS
    slot = find_car(carpark, licence_plate_no);
    //AFTER RUNNING THE FIND FUNTION
    //SLOT IN USE WAS UPDATED TO 1 IF THE CAR WAS FOUND WHILE RUNNING 'FIND'
    //ONLY RUNS IF THE CAR IS FOUND
    if (slot.in_use == 1) {
        //ASSIGNS THE ROW COL OF THE CAR FOUND TO XCAR AND YCAR VARIABLES
        x_car = slot.row;
        y_car = slot.col;
        //FOR LOOP TO LOCATES THE ELECTRIC STATIONS IN THE CARPARK
        for (row = 0; row < CARPARK_ROWS; row++) {
            for (col = 0; col < CARPARK_COLUMNS; col++) {
                if (carpark[row][col].type == ELECTRIC_CHARGING_STATION &&
                   (carpark[row][col].in_use == EMPTY || 
                    carpark[row][col].charge_endtime <= charge_from)) {
                    //AFTER FINDING THE CAR CHARGER
                    //THAT PARTICULAR ROW COL IS ASSIGNED TO XCHARGER AND YCHARGER
                    x_charger = row;
                    y_charger = col;

                    //CALCULATES THE DISTANCE 
                    //FROM THE CHARGER TO THE CAR BEING CHARGED
                    cal_distance = sqrt(pow((x_charger - x_car), 2) + 
                    pow((y_charger - y_car), 2));

                    if (min_distance > cal_distance) {
                        min_distance = cal_distance;
                        cable_length = carpark[row][col].cable_length;
                    }
                }
            } 
        }
        //IF XCHARGER IS EMPTY THEN AVAILABLE CHARGING SLOT FUNCTION IS CALLED 
        if (x_charger == EMPTY ) {
            available_charging_slot(carpark);
        } 
        //PRINTS ERROR STATEMENTS STATING THAT THAT CHARGING STATION IS TOO FAR
        //SINCE THE CABLE LENGTH IS TOO FAR
        else if (min_distance >= cable_length) {
            printf("Too far away to be charged, move closer to a charging station.\n");
        }
        //IF THE CAR IS CLOSE TO THE CHARGER SO THAT CABLE CAN REACH
        //XCHARGER IS NOT EMPTY
        else {
            //ASSIGNS LICENCE PLATE AND ELECTRIC CHARGE TIMES TO STRUCT
            carpark[x_charger][y_charger].licence_plate = licence_plate_no;
            carpark[x_charger][y_charger].charge_endtime = charge_til;
            carpark[x_charger][y_charger].charge_starttime = charge_from;
            carpark[x_charger][y_charger].in_use = 1;
            //PRINTS OUT THE STATMENT STATING THAT THE CAR IS CHARGING
            printf("Car %d is being charged by the charging "
            "station located at (%d, %d).\n", licence_plate_no, x_charger, y_charger);
        }       
    }          
}

//THIS IS A SUB FUNCTION THAT CHECKS THE NEXT AVAILABLE ELECTRIC CHARGER
void available_charging_slot(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS])
{
    int next_avail_time = 999;
    int row;
    int t_row = 0;
    int col; 
    int t_col = 0;

    for (row = 0; row < CARPARK_ROWS; row++) {
        for (col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].type == ELECTRIC_CHARGING_STATION ) {
                if (next_avail_time > carpark[row][col].charge_endtime ) {
                    next_avail_time = carpark[row][col].charge_endtime;
                    t_row = row;
                    t_col = col;
                }
            }
        }
    }                    
    printf("All nearby charging stations are currently in use. " 
            "The next free charging station is (%d, %d), which will be free at time %d.\n"
            , t_row, t_col, next_avail_time);
}

// Stage 3.3 - CREATING FUNCTION Moving Cars
//THIS FUNCTION MOVES THE CAR FROM ONE LOCATION TO THE OTHER
//NOTE: CAR IS MOVING TO A NEW LOCATION THUS EXIT TYPE FOR MOVE WILL ALWAYS BE 'm'
void moving_cars(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
    int licence_plate_no, int row, int col, int time_of_move) {
    struct car_location slot;

    //IF USER INPUTS INVALID TIME OF MOVE
    //PRINTS OUT THE STATEMENT STATING THAT THE TIME PROVIDED IS INVALID
    if (time_of_move < 0) {
        printf("The move time provided is invalid.\n");
    }
    //IF USER INPUTS OUT OF BOUNDS CARSPACE 
    else if (row < 0 
        || row >= CARPARK_ROWS 
        || col < 0 
        || col >= CARPARK_COLUMNS) {
        printf("Car %04d cannot be moved to an invalid car space.\n", licence_plate_no);
    }
    //CHECKS IF THE CAR SPACE IS ALREADY BEING OCCUPIED BY OTHER CAR
    else if (carpark[row][col].licence_plate != EMPTY ) {
        //PRINTS OUT THE STATEMENT STATING THAT ANOTHER CAR IS PARKED
        printf("Car %04d could not be moved to space (%d, %d) as car %d "
        "is already parked there.\n", licence_plate_no, row, col, 
        carpark[row][col].licence_plate);
    }
    //CHECKS IF THE CAR MATCHES THE LICENCE PLATE IN THE CARPARK
    else {
        slot = find_car(carpark, licence_plate_no);
        if (slot.in_use == 1) {
            //ASSIGNS LICENCE PLATE, TIME TO MOVE, PARKING PRICE TO NEW CARSPACE
            //carpark[new_row][new_col].licence_plate =  licence_plate_no;
            //carpark[new_row][new_col].occupied_since = time_of_move;
            leaving_carpark(carpark, licence_plate_no, time_of_move, 'm');
            parking_slot(carpark, licence_plate_no, row, col, time_of_move);
            carpark[row][col].till_amount = 
            calculate_parking_rate(slot, time_of_move);
            //CALLING LEAVING CARPARK FUNCTION TO MAKE SURE THE CARSPACE VALUES
            //REVERTS BACK TO THE ORIGINAL ONCE THE CAR MOVE
            //NOTICE THAT THE EXIT TYPE HERE IS M
            //THIS MEANS THAT THE CAR IS NOT EXITING THE CARPARK
            //BUT INSTEAD MOVING TO A NEW LOCATION
            //PRINTS OUT THE STATEMENT STATING THAT THE CAR HAS BEEN MOVED
            if (carpark[row][col].type != CARWASH_BAY) {
                printf("Car %04d has been moved to space (%d, %d).\n"
                , carpark[row][col].licence_plate, row, col);
            }
        }
    }        
}

//STAGE 3.4 CREATING FUNCTION - Building Car Wash Bay
//THIS FUNCTION BUILDS THE CARWASH BAYS IN THE CARPARK
void carwash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    int row;
    int col;
    int build_time;

    // USER ENTERS ROW, COL, BUILD TIME
    scanf("%d", &row);
    scanf("%d", &col);
    scanf("%d", &build_time);
    // CHECK IF SURROUNDING SPACES ARE OCCUPIED
    //NOTE: CARWASH CAN NOT BE BUILD IF ANOTHER CAR [NOT IN THE CARWASH] IS PARKED
    if (adjacent_space_check(carpark, row, col)) {
        printf("This carwash bay cannot be built as one or more of the "
        "surrounding spaces are currently occupied.\n");
    } 
    //else if (adjacent_carwash(carpark, row, col)) {
    //     //printf("Cannot park next to a carwash bay. There are still other "
    //"spaces available in the carpark.\n");
    //} 
    else {
        // BUILD CARWASH BAY
        carpark[row][col].type = CARWASH_BAY;
        carpark[row][col].occupied_since = 0;
        printf("Carwash bay has been built on space (%d, %d) at time %d.\n", 
        row, col, build_time);
    }
}

//THIS IS A SUBFUNCTION THAT CHECKS IF SURROUNDING CARSPACE IS EMPTY
int adjacent_space_check(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int row, int col) {

    int row_check;
    int col_check;
    for (row_check = row - 1; row_check <= row + 1; row_check++) {
        for (col_check = col - 1; col_check <= col + 1; col_check++) {
            if (row_check >= 0 
             && row_check < CARPARK_ROWS 
             && col_check >= 0 
             && col_check < CARPARK_COLUMNS) {
                if (carpark[row_check][col_check].licence_plate != EMPTY &&
                    carpark[row_check][col_check].type != CARWASH_BAY) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

//THIS IS A SUBFUNCTION THAT CHECKS IF SURROUNDING CARSPACE IS CARWASH BAY
int adjacent_carwash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int row, int col) {

    int row_check;
    int col_check;
    int check = 0;
    //FOR LOOP CHECKS IF SURROUNDING CARSPACE IS CARWASH BAY
    for (row_check = row - 1; row_check <= row + 1; row_check++) {
        for (col_check = col - 1; col_check <= col + 1; col_check++) {
            if (row_check >= 0 
             && row_check < CARPARK_ROWS 
             && col_check >= 0 
             && col_check < CARPARK_COLUMNS) {
                check = check_car_slot_type(carpark[row][col]);
            }
        }
    }
    return check;
}
int check_car_slot_type(struct car_space slot)
{
    if (slot.licence_plate != EMPTY &&
        slot.type != CARWASH_BAY) {
        return 1;
    }
    // else if (slot.type == CARWASH_BAY) {
    //     return 0;
    // } 
    return 0;
}

//STAGE 4.2 - CREATING FIUNCTION Car exiting checks
void can_car_exit_checks(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
int licence_plate_no, int row, int col, int *exit_check) {
    //IF THE CARSPACE AT THE EXIT SLOT IN IS NOT EMPTY
    if (*exit_check == 0) {
        if (carpark[7][3].licence_plate != EMPTY || 
            carpark[1][col].type == ELECTRIC_CHARGING_STATION ||
            carpark[row][col].type == CARWASH_BAY) {
            printf("Car %04d is blocked and is unable to exit.\n", licence_plate_no);
            *exit_check = 1;
        }
    }
    //CHECKS IF WHOLE ROW IS EMPTY
    if (*exit_check == 0) {
        for (row = 0; row - 1 == CARPARK_ROWS; row++) {
            if (carpark[row][0].licence_plate != EMPTY &&
                carpark[row][1].licence_plate != EMPTY &&
                carpark[row][2].licence_plate != EMPTY &&
                carpark[row][3].licence_plate != EMPTY &&
                carpark[row][4].licence_plate != EMPTY &&
                carpark[row][5].licence_plate != EMPTY) {
                printf("Car %04d is blocked and is unable to exit.\n", licence_plate_no);
                *exit_check = 1;
                break;
            }
        }
    }
    //CHECKS IF WHOLE COL IS EMPTY
    if (*exit_check == 0) {
        for (col = 0; col - 1 == CARPARK_COLUMNS; col++) {
            if (carpark[0][col].licence_plate != EMPTY &&
                carpark[1][col].licence_plate != EMPTY &&
                carpark[2][col].licence_plate != EMPTY &&
                carpark[3][col].licence_plate != EMPTY &&
                carpark[4][col].licence_plate != EMPTY &&
                carpark[5][col].licence_plate != EMPTY &&
                carpark[6][col].licence_plate != EMPTY &&
                carpark[7][col].licence_plate != EMPTY) {
                printf("Car %04d is blocked and is unable to exit.\n", licence_plate_no);
                *exit_check = 1;
                break;
            }
        }
    }
    //CHECKS IF WHOLE ROW IS BLOCKING BY THE ELECTRIC CHARGER
    if (*exit_check == 0) {
        for (row = 0; row - 1 == CARPARK_ROWS; row++) {
            if (carpark[row][0].type == ELECTRIC_CHARGING_STATION &&
                carpark[row][1].type == ELECTRIC_CHARGING_STATION &&
                carpark[row][2].type == ELECTRIC_CHARGING_STATION &&
                carpark[row][3].type == ELECTRIC_CHARGING_STATION &&
                carpark[row][4].type == ELECTRIC_CHARGING_STATION &&
                carpark[row][5].type == ELECTRIC_CHARGING_STATION) {
                printf("Car %04d is blocked and is unable to exit.\n", licence_plate_no);
                *exit_check = 1;
                break;
            }
        }
    }

    //IF THE SURROUNDING SPACES OF THAT CARSPACE ARE NOT EMPTY
    if (*exit_check == 0) {
        if (adjacent_space_check(carpark, row, col)) {
            printf("Car %04d is blocked and is unable to exit.\n", licence_plate_no);
            *exit_check = 1;
        }
    }
}
 
/**
 * Initialises carpark spaces as NORMAL spaces with NORMAL_PARKING_RATE that are
 * initially EMPTY.
 * 
 * Parameters:
 *     carpark - The carpark to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            carpark[row][col].type = NORMAL;
            carpark[row][col].normal_parking_rate = NORMAL_PARKING_RATE;
            carpark[row][col].premium_parking_rate = PREMIUM_PARKING_RATE;
            carpark[row][col].electric_parking_rate = ELECTRIC_PARKING_RATE;
            carpark[row][col].licence_plate = EMPTY;
            carpark[row][col].occupied_since = 0;
            carpark[row][col].discount_applied = EMPTY;
            carpark[row][col].cable_length = EMPTY;
            carpark[row][col].charge_starttime = EMPTY;
            carpark[row][col].charge_endtime = EMPTY;
            carpark[row][col].in_use = EMPTY;
            carpark[row][col].till_amount = 0;
            carpark[row][col].tot_parking_time = 0;
        }
    }
}

/**
 * Prints all carpark spaces, displaying their type and the licence plate of 
 * any cars parked in the carpark.
 * 
 * Parameters:
 *     carpark   - The carpark to be printed
 * Returns:
 *     Nothing.
 */
void print_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    printf("-------------------------------------------------------------------\n");
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            print_car_space(carpark[row][col]);
        }
        printf("|\n");
        printf("-------------------------------------------------------------------\n");
    }
    printf("\n");
}

/**
 * Prints the type of a particular car space, as well as the licence plate of 
 * the car located at that car space.
 * 
 * Parameters:
 *     car_space         - The car space to print.
 *
 * Returns:
 *     Nothing.
 */
void print_car_space(struct car_space car_space) {
    printf("|");
    if (car_space.type == NORMAL) {
        printf(" N :");
    } else if (car_space.type  == PREMIUM) {
        printf(" P :");
    } else if (car_space.type  == CARWASH_BAY) {
        printf(" W :");
    } else if (car_space.type  == ELECTRIC_CHARGING_STATION) {
        printf(" CHARGER  ");
    }
    if (car_space.type != ELECTRIC_CHARGING_STATION) {
        if (car_space.licence_plate == EMPTY) {
            printf("      ");
        } else {
            printf(" %04d ", car_space.licence_plate);
        }
    }
    
}
