package main

import (
	"fmt"
	"net"
	"os"
)

type Message struct {
	sender_name string
	sender_host string
	date_time   string
	message     string
}

type DataUsers map[string]string

func ViewError(err error) {
	fmt.Printf("[ERROR] - %s\n", err)
}

func ext() {
	os.Exit(1)
}

func ListenClient(connection net.Conn) {
	defer fmt.Printf("client(%s) disconnected\n", connection.RemoteAddr().String())
	defer connection.Close()

	for {

		clientMessage := make([]byte, 4096)
		sz, err := connection.Read(clientMessage)
		if sz == 0 || err != nil {
			ViewError(err)
			break
		}

		fmt.Printf("client(%s): %s\n", connection.RemoteAddr().String(), string(clientMessage[:sz]))
		connection.Write([]byte("Thank you."))
	}
}

func main() {
	listener, err := net.Listen("tcp", "127.0.0.1:4434")
	if err != nil {
		ViewError(err)
		ext()
	}
	defer listener.Close()

	fmt.Println("Server is listerning")
	for {
		connection, err := listener.Accept()
		if err != nil {
			ViewError(err)
			ext()
		}

		fmt.Printf("client(%s) connected\n", connection.RemoteAddr().String())
		go ListenClient(connection)
	}

}
