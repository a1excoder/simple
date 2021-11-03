package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

func ViewError(err error) {
	fmt.Printf("[ERROR] - %s\n", err)
}

func ScanString() (string, error) {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Enter message: ")
	message, err := reader.ReadString('\n')
	if err != nil {
		return "", err
	}

	return message, nil
}

func ext() {
	os.Exit(1)
}

func CloseConn(connection net.Conn) {
	connection.Close()
}

func main() {
	connection, err := net.Dial("tcp", "127.0.0.1:4434")
	if err != nil {
		ViewError(err)
		ext()
	}
	defer CloseConn(connection)

	for {
		str, err := ScanString()
		if err != nil {
			ViewError(err)
			continue
		}

		if strings.HasPrefix(str, "!close") {
			CloseConn(connection)
			break
		}
		connection.Write([]byte(str))

		serverMessage := make([]byte, 4096)
		sz, err := connection.Read(serverMessage)
		if sz == 0 || err != nil {
			ViewError(err)
		}
		fmt.Printf("server(%s): %s\n", connection.RemoteAddr().String(), serverMessage[:sz])
	}
}
