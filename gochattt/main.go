package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
repeat:

	selectMode, err := ScanString("Select(server, client, viewer): ")
	var ip, port, mode string
	if err != nil {
		ViewError(err)
		os.Exit(4)
	}

	if strings.HasPrefix(selectMode, "server") {
		fmt.Print("Start server on 127.0.0.1:4434 or your values (y/n): ")
		_, err := fmt.Scan(&mode)
		if err != nil {
			goto repeat
		}

		if strings.HasPrefix(mode, "y") {
			Server("127.0.0.1", "4434")
			os.Exit(0)
		}

		fmt.Print("Enter ip: ")
		_, err = fmt.Scan(&ip)
		if err != nil {
			goto repeat
		}

		fmt.Print("Enter port: ")
		_, err = fmt.Scan(&port)
		if err != nil {
			goto repeat
		}

		Server(ip, port)
	} else if strings.HasPrefix(selectMode, "client") {
		fmt.Print("Start client on 127.0.0.1:4434 or your values (y/n): ")
		_, err := fmt.Scan(&mode)
		if err != nil {
			goto repeat
		}

		if strings.HasPrefix(mode, "y") {
			ClientWithBugs("127.0.0.1", "4434")
			os.Exit(0)
		}

		fmt.Print("Enter server ip: ")
		_, err = fmt.Scan(&ip)
		if err != nil {
			goto repeat
		}

		fmt.Print("Enter server port: ")
		_, err = fmt.Scan(&port)
		if err != nil {
			goto repeat
		}

		ClientWithBugs(ip, port)
	} else if strings.HasPrefix(selectMode, "viewer") {
		fmt.Print("Start viewer on 127.0.0.1:4434 or your values (y/n): ")
		_, err := fmt.Scan(&mode)
		if err != nil {
			goto repeat
		}

		if strings.HasPrefix(mode, "y") {
			Viewer("127.0.0.1", "4434")
			os.Exit(0)
		}

		fmt.Print("Enter server ip: ")
		_, err = fmt.Scan(&ip)
		if err != nil {
			goto repeat
		}

		fmt.Print("Enter server port: ")
		_, err = fmt.Scan(&port)
		if err != nil {
			goto repeat
		}

		Viewer(ip, port)
	} else {
		goto repeat
	}
}
