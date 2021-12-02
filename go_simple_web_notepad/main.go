package main

import (
	"database/sql"
	"fmt"
	"html/template"
	"net/http"
	"os"
	"strconv"

	_ "github.com/mattn/go-sqlite3"
)

type Note struct {
	Id    int
	Title string
	Query string
}

const fname = "./notes.db"

func main() {
	file, err := os.Open(fname)
	var db *sql.DB
	var count int
	if err != nil {
		db, err = sql.Open("sqlite3", fname)
		db.Exec(`CREATE TABLE "notes" (
			"id"	INTEGER NOT NULL UNIQUE,
			"title"	TEXT,
			"query"	TEXT,
			PRIMARY KEY("id" AUTOINCREMENT)
		);`)
	} else {
		file.Close()
		db, err = sql.Open("sqlite3", fname)
	}
	if err != nil {
		panic(err)
	}
	defer db.Close()

	http.HandleFunc("/", func(rw http.ResponseWriter, r *http.Request) {
		tmpl, err := template.ParseFiles("./templates/index.html")
		if err != nil {
			panic(err)
		}

		row := db.QueryRow("select count(*) from notes")
		err = row.Scan(&count)
		if err != nil {
			panic(err)
		}

		Notes := make([]Note, count, count)
		temp_id := 0

		rows, err := db.Query("select * from notes order by id desc")
		if err != nil {
			panic(err)
		}

		for rows.Next() {
			err := rows.Scan(&Notes[temp_id].Id, &Notes[temp_id].Title, &Notes[temp_id].Query)
			if err != nil {
				break
			}
			temp_id++
		}

		tmpl.Execute(rw, Notes)
	})

	http.HandleFunc("/addnote", func(rw http.ResponseWriter, r *http.Request) {
		title, query := r.FormValue("title"), r.FormValue("query")

		if title == "" || query == "" {
			fmt.Fprint(rw, "<p style=\"color: red;\">title or query not found.<br><a href=\"/\">back</a></p>")
		} else {
			_, err := db.Exec("insert into notes (title, query) values ($1, $2)", title, query)
			if err != nil {
				fmt.Fprint(rw, "<p style=\"color: red;\">%w.<br><a href=\"/\">back</a></p>", err)
			} else {
				fmt.Fprint(rw, "<p style=\"color: green;\">your note was added.<br><a href=\"/\">back</a></p>")
			}
		}
	})

	http.HandleFunc("/deletenote", func(rw http.ResponseWriter, r *http.Request) {
		note_id, err := strconv.Atoi(r.FormValue("id"))
		var temp_id int
		if err != nil {
			fmt.Fprint(rw, err)
		} else {
			row := db.QueryRow("select id from notes where id = $1", note_id)
			err := row.Scan(&temp_id)
			if err != nil {
				fmt.Fprint(rw, "<p style=\"color: red;\">note not found.<br><a href=\"/\">back</a></p>")
			} else {
				_, err = db.Exec("delete from notes where id = $1", note_id)
				if err != nil {
					fmt.Fprint(rw, "<p style=\"color: red;\">note wasn't deleted.<br><a href=\"/\">back</a></p>")
				} else {
					fmt.Fprint(rw, "<p style=\"color: green;\">note was deleted.<br><a href=\"/\">back</a></p>")
				}
			}

		}
	})

	http.HandleFunc("/updatenote", func(rw http.ResponseWriter, r *http.Request) {
		note_id, err := strconv.Atoi(r.FormValue("id"))
		TempNote := Note{}
		if err != nil {
			fmt.Fprint(rw, err)
		} else {
			row := db.QueryRow("select * from notes where id = $1", note_id)
			err := row.Scan(&TempNote.Id, &TempNote.Title, &TempNote.Query)
			if err != nil {
				fmt.Fprint(rw, "<p style=\"color: red;\">note not found.<br><a href=\"/\">back</a></p>")
			} else {

				tmpl, err := template.ParseFiles("./templates/update.html")
				if err != nil {
					panic(err)
				}
				tmpl.Execute(rw, TempNote)
			}
		}
	})

	http.HandleFunc("/updatenote/success", func(rw http.ResponseWriter, r *http.Request) {
		note_id, err := strconv.Atoi(r.FormValue("id"))
		note_title, note_query := r.FormValue("title"), r.FormValue("query")
		var temp_id int
		if err != nil {
			fmt.Fprint(rw, err)
		} else {
			row := db.QueryRow("select id from notes where id = $1", note_id)
			err := row.Scan(&temp_id)
			if err != nil {
				fmt.Fprint(rw, "<p style=\"color: red;\">note not found.<br><a href=\"/\">back</a></p>")
			} else {
				_, err := db.Exec("update notes set title = $1, query = $2 where id = $3", note_title, note_query, note_id)
				if err != nil {
					fmt.Fprint(rw, "<p style=\"color: red;\">note wasn't updated.<br><a href=\"/\">back</a></p>")
					fmt.Print(err)
				} else {
					fmt.Fprintf(rw, "<p style=\"color: green;\">note id(%d) was updated.<br><a href=\"/\">back</a></p>", temp_id)
				}
			}
		}
	})

	fmt.Fprintln(os.Stdout, "Server is listening...")
	http.ListenAndServe(":8080", nil)
}
