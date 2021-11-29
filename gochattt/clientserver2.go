package notmain

import (
	"bufio"
	"fmt"
	"io"
	"net"
	"os"
	"strconv"
	"strings"
)

func ViewError(err error) {
	fmt.Printf("[ERROR] - %s\n", err)
}

func CloseConn(connection net.Conn) {
	connection.Close()
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

type DataBaseUsers map[*net.Conn]string

func (users *DataBaseUsers) CheckUserName(newname string) (result bool) {
	result = true

	for _, name := range *users {
		if strings.HasPrefix(name, newname) {
			result = false
			break
		}
	}

	return result
}

func ClientTypeValidation(connection net.Conn) (bool, error) {
	var Tclient bool
	for {
		first_message, err := GetMessage(connection)
		if err != nil {
			return false, err
		}
		if strings.HasPrefix(first_message, "0") {
			Tclient = false
			break
		}
		if strings.HasPrefix(first_message, "1") {
			Tclient = true
			break
		}
		continue
	}
	return Tclient, nil
}

func ProcessUser(connection *net.Conn, users *DataBaseUsers, temporaryUserName string) {
	defer func() {
		fmt.Printf("client(%s) disconnected\n", (*users)[connection])
		for user := range *users {
			if user == connection {
				continue
			}
			(*user).Write([]byte(fmt.Sprintf("client(%s) disconnected\n", (*users)[connection])))
		}
		delete(*users, connection)
		CloseConn(*connection)
	}()

	Tclient, err := ClientTypeValidation(*connection)
	if err != nil {
		ViewError(err)
	}

	(*users)[connection] = temporaryUserName

	var str strings.Builder
	var last_name string
	for {
		data := make([]byte, 32)

		n, err := (*connection).Read(data)
		if err != nil {
			if err == io.EOF {
				break
			} else {
				ViewError(err)
				break
			}
		}
		str.Write(data)

		if n < 32 {
			if strings.HasPrefix(str.String(), "!rename") {
				if !Tclient {
					last_name = (*users)[connection]
					delete(*users, connection)
				} else {
					_, err := (*connection).Write([]byte("server: enter new user name.\n"))
					if err != nil {
						ViewError(err)
						break
					}
				}

				for {
					newname, err := GetMessage(*connection)
					if err != nil {
						ViewError(err)
						break
					}

					if users.CheckUserName(newname) {

						for user := range *users {
							if user == connection {
								continue
							}

							(*user).Write([]byte(fmt.Sprintf("server: user(%s) changed name on user(%s)", last_name, newname)))
						}

						(*connection).Write([]byte("1"))
						(*users)[connection] = newname

						break
					} else {
						_, err := (*connection).Write([]byte("0"))
						if err != nil {
							ViewError(err)
							break
						}
					}
				}
				str.Reset()
				continue
			}

			fmt.Printf("client(%s): %s", (*users)[connection], str.String())

			for host := range *users {
				if host == connection {
					continue
				}

				(*host).Write([]byte(fmt.Sprintf("client(%s): %s", (*users)[connection], str.String())))
			}

			str.Reset()
		}

	}
}

func Server(host, port string) {
	var users = make(DataBaseUsers)
	var numberOfUsers = 1
	fmt.Printf("server(%s)\n", host+":"+port)
	listener, err := net.Listen("tcp", host+":"+port)

	if err != nil {
		ViewError(err)
		os.Exit(1)
	}
	defer listener.Close()
	fmt.Println("Server listening...")

	for {
		connection, err := listener.Accept()
		if err != nil {
			ViewError(err)
			continue
		}

		go ProcessUser(&connection, &users, strconv.Itoa(numberOfUsers))
		fmt.Printf("client(%s) connected\n", strconv.Itoa(numberOfUsers))
		for host := range users {
			if *host == connection {
				continue
			}

			(*host).Write([]byte(fmt.Sprintf("client(%s) connected\n", strconv.Itoa(numberOfUsers))))
		}

		numberOfUsers++
	}
}

func ReadMessages(connection *net.Conn) {

	var str strings.Builder
	for {
		data := make([]byte, 32)
		n, err := (*connection).Read(data)
		if err != nil {
			if err == io.EOF {
				break
			} else {
				ViewError(err)
				break
			}
		}

		str.Write(data)

		if n < 32 {
			fmt.Print(str.String())
			str.Reset()
		}

	}
}

func ReadMessagesBugClient(connection *net.Conn, ch chan bool) {

	var str strings.Builder
	for {
		select {
		case <-ch:
			return
		default:
			{
				data := make([]byte, 32)
				n, err := (*connection).Read(data)
				if err != nil {
					if err == io.EOF {
						break
					} else {
						ViewError(err)
						break
					}
				}

				str.Write(data)

				if n < 32 {
					fmt.Print(str.String())
					str.Reset()
				}
			}
		}
	}
}

func GetMessage(connection net.Conn) (string, error) {
	var str strings.Builder

	for {
		data := make([]byte, 32)
		n, err := connection.Read(data)
		if err != nil {
			if err == io.EOF {
				return str.String(), nil
			}
			return "", err
		}
		str.Write(data)

		if n < 32 {
			return str.String(), nil
		}
	}
}

func ClientWithBugs(host, port string) {
	connection, err := net.Dial("tcp", host+":"+port)
	if err != nil {
		ViewError(err)
		os.Exit(3)
	}
	defer CloseConn(connection)
	channel := make(chan bool)

	connection.Write([]byte("0"))
	go ReadMessagesBugClient(&connection, channel)

	var message string
	for {
		message, err = ScanString("Enter message: ")
		if err != nil {
			ViewError(err)
			continue
		}
		if strings.HasPrefix(message, "!close") {
			break
		}

		if strings.HasPrefix(message, "!rename") {
			channel <- true

			_, err := connection.Write([]byte("!rename"))
			if err != nil {
				ViewError(err)
				break
			}

			var name string
			for {
				// name, err = ScanString("Enter new user name: ")
				// name = strings.TrimSuffix(name, "\n")
				fmt.Print("Enter new user name: ")
				fmt.Scan(&name)
				if err != nil {
					ViewError(err)
					continue
				}

				_, err = connection.Write([]byte(name))
				if err != nil {
					ViewError(err)
					break
				}
				status_data, err := GetMessage(connection)
				if err != nil {
					ViewError(err)
					break
				}

				if strings.HasPrefix(status_data, "1") {
					fmt.Println("name has been changed")
					break
				} else {
					fmt.Printf("name \"%s\" is taken\n", name)
					continue
				}

			}
			go ReadMessagesBugClient(&connection, channel)
			continue
		}

		_, err := connection.Write([]byte(message))
		if err != nil {
			ViewError(fmt.Errorf("the last message was not delivered to the server"))
			break
		}
	}

}

func Viewer(host, port string) {
	connection, err := net.Dial("tcp", host+":"+port)
	if err != nil {
		ViewError(err)
		os.Exit(3)
	}
	defer CloseConn(connection)

	ReadMessages(&connection)
}
