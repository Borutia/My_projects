

class Convert_numbers(object):
    def converter_decimal_to_binary(self, decimal):
        decimal_binary = decimal
        print("DECIMAL TO BINARY: ", end="")
        return bin(decimal_binary)[2::]

    def converter_binary_to_decimal(self, binary):
        decimal = 0
        for digit in binary:
            if digit == "0" or digit == "1":
                decimal = decimal * 2 + int(digit)
            else:
                return "INVALID"
                break
        print("BINARY TO DECIMAL: ", end="")
        return decimal


def menu():
    while True:
        try:
            num = Convert_numbers()
            print()
            print("1) Decimal to Binary Number")
            print("2) Binary to Decimal Number")
            print("3) Exit")
            select = int(input("answer: "))
            if select == 1:
                number = int(input("input decimal number: "))
                result = num.converter_decimal_to_binary(number)
                print(result)
            elif select == 2:
                number = input("input binary number: ")
                result = num.converter_binary_to_decimal(number)
                print(result)
            elif select == 3:
                return "EXIT"
        except:
            print("command error! input again")


if __name__ == "__main__":
    print("This program for convert from decimal to binary and vice versa")
    menu()
