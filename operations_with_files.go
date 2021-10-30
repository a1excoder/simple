package main

import (
	"fmt"
	"os"
	"io"
	"bufio"
)

func Write(fname, query string) error {
	file, err := os.OpenFile(fname, os.O_WRONLY, 0666)
	if (err != nil) {
		return err
	}
	defer file.Close()
	buffer := []byte(query)
	file.Write(buffer)

	return nil
}

func Create(fname string) error {
	file, err := os.Create(fname)
	if (err != nil) {
		return err
	}

	file.Close()
	return nil
}

func Read(fname string, buffer_size int, channel chan <- []byte) error {
	file, err := os.OpenFile(fname, os.O_RDONLY, 0666)
	if (err != nil) {
		channel <- []byte(fmt.Sprintf("[ERROR] - %s\n", err))
		close(channel)
		return err
	}
	defer file.Close()
	defer close(channel)

	buffer := make([]byte, buffer_size)

	for {
		len_str, err := file.Read(buffer)
		if (err == io.EOF) {
			break
		}
		channel <- buffer[:len_str]
	}
	channel <- []byte("\n")

	return nil
}

func main() {
	GetName := func() (result string) {
		fmt.Print("Enter file name: ")
		fmt.Fscan(os.Stdin, &result)

		return
	}

	GetData := func() (string, error) {
		fmt.Print("Enter data: ")
		rdr := bufio.NewReader(os.Stdin)
		str, err := rdr.ReadString('\n')
		return str, err
	}
	var option int8

	for {
		fmt.Print("read from file: `1` write: `2` create `3` exit `0`: ")
		fmt.Fscan(os.Stdin, &option)


		switch (option) {
		case 1:
			channel := make(chan []byte)
			go Read(GetName(), 256, channel)

			for {
				data, opened := <- channel
				if (!opened) {
					break
				}
				fmt.Print(string(data))
			}
		case 2:
			fname := GetName()
			fdata, err := GetData()
			if err != nil {
				fmt.Printf("[ERROR] - %s\n", err)
				break
			}

			err = Write(fname, fdata)
			if err != nil {
				fmt.Printf("[ERROR] - %s\n", err)
				break
			}

		case 3:
			err := Create(GetName())
			if (err != nil) {
				fmt.Printf("[ERROR] - %s\n", err)
			}
		case 0:
			os.Exit(0)
		}
	}
	
}
