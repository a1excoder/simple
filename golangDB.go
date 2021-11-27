package main

import (
	"bufio"
	"database/sql"
	"fmt"
	"os"

	_ "github.com/mattn/go-sqlite3"
)

type Car struct {
	id    int
	name  string
	model string
	ruler string
}

func main() {
	db, err := sql.Open("sqlite3", "first.db")
	if err != nil {
		ViewError(err)
		os.Exit(1)
	}
	defer db.Close()

	var slct_code int
	var id int64
	car_struct := Car{}
	for {
		fmt.Print("add(1), get(2), get_all(3), update(4), delete(5), close(6): ")
		_, err = fmt.Scanf("%d", &slct_code)
		if err != nil {
			fmt.Println(err)
			continue
		}
		switch slct_code {
		case 1:
			_, err = car_struct.SetCar()
			if err != nil {
				fmt.Println(err)
				continue
			}

			res, err := db.Exec("insert into car (name, model, ruler) values ($1, $2, $3)", car_struct.name, car_struct.model, car_struct.ruler)
			if err != nil {
				fmt.Println(err)
				continue
			}

			id, err = res.LastInsertId()
			if err != nil {
				fmt.Println(err)
				continue
			}
			fmt.Printf("your car id: %d\n", id)
		case 2:
			fmt.Print("Enter car id: ")
			fmt.Scanf("%d", &id)

			row := db.QueryRow("select * from car where id = $1", id)
			err = row.Scan(&car_struct.id, &car_struct.name, &car_struct.model, &car_struct.ruler)
			if err != nil {
				fmt.Println(err)
				continue
			}

			car_struct.ViewCarData()
		case 3:
			rows, err := db.Query("select * from car")
			if err != nil {
				fmt.Println(err)
				continue
			}

			for rows.Next() {
				err := rows.Scan(&car_struct.id, &car_struct.name, &car_struct.model, &car_struct.ruler)
				if err != nil {
					fmt.Println(err)
					break
				}
				car_struct.ViewCarData()
				fmt.Println()
			}
		case 4:
			fmt.Print("Enter car id: ")
			fmt.Scanf("%d", &id)
			_, err = car_struct.SetCar()
			if err != nil {
				fmt.Println(err)
				continue
			}

			_, err := db.Exec("update car set name = $1, model = $2, ruler = $3 where id = $4",
				car_struct.name, car_struct.model, car_struct.ruler, id)
			if err != nil {
				fmt.Println(err)
				continue
			}

			fmt.Printf("car %d updated\n", id)
		case 5:
			fmt.Print("Enter car id: ")
			fmt.Scanf("%d", &id)

			_, err := db.Exec("delete from car where id = $1", id)
			if err != nil {
				fmt.Println(err)
			}

			fmt.Printf("car %d deleted\n", id)
		case 6:
			db.Close()
			os.Exit(0)
		default:
			fmt.Println("command code not found, please repeat")
			continue
		}
	}
}

func (car_struct Car) ViewCarData() {
	fmt.Printf("id: %d\n\tname: %s\n\t\tmodel: %s\n\t\t\truler: %s\n",
		car_struct.id, car_struct.name, car_struct.model, car_struct.ruler)
}

func ViewError(err error) {
	fmt.Printf("[ERROR] - %s\n", err)
}

func ScanString(text string) (string, error) {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print(text)
	message, err := reader.ReadString('\n')
	if err != nil {
		return "", err
	}

	return message, nil
}

func (myCar *Car) SetCar() (*Car, error) {
	var err error

	myCar.name, err = ScanString("Enter name: ")
	if err != nil {
		return nil, err
	}

	myCar.model, err = ScanString("Enter model: ")
	if err != nil {
		return nil, err
	}

	myCar.ruler, err = ScanString("Enter ruler: ")
	if err != nil {
		return nil, err
	}

	return myCar, nil
}

/*
CREATE TABLE "car" (
	"id"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT,
	"model"	TEXT,
	"ruler"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
);
*/
