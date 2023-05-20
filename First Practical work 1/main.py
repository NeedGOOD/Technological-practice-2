from datetime import datetime
import json
import os

class Info:
    def __init__(self, route='', time='', seats_on_bus=0, sticket_price=None):
        if not route: self.route = input("Маршрут: ")
        else: self.route = route
        if not time: self.time = self.inputTime()
        else: self.time = time
        if not seats_on_bus: self.seats_on_bus = self.seats()
        else: self.seats_on_bus = seats_on_bus
        if sticket_price == None: self.sticket_price = self.price()
        else: self.sticket_price = sticket_price

    def inputTime(self):
        while True:
            try:
                date_str = input("Введіть дату та час в форматі РРРР-ММ-ДД ГГ:ХХ: ")
                date_obj = datetime.strptime(date_str, "%Y-%m-%d %H:%M")
                return date_obj.strftime("%Y-%m-%d %H:%M")
            except ValueError:
                print("Ви ввели неправильний формат дати та/або часу.")

    def seats(self):
        while True:
            seats_on_bus = int(input("Вільних місць: "))
            if seats_on_bus >= 0: return seats_on_bus
            else: print("Ви ввели неправильний формат введення.")

    def price(self):
        while True:
            sticket_price = int(input("Вартість квитка: "))
            if sticket_price >= 0: return sticket_price
            else: print("Ви ввели неправильний формат введення.")

    def checkInfoX(self):
        price = "Безкоштовно" if self.sticket_price == 0 else self.sticket_price
        print(f"{self.route:<15}{self.time:<20}{self.seats_on_bus:<15}{price:<13}")

    def buySeats(self):
        while True:
            print("Скільки ви хочете купити місць?")
            buy_seats = int(input("~ "))
            if self.seats_on_bus < buy_seats:
                os.system('cls')
                print("Ви ввели неправильний формат введення.")
                continue
            if buy_seats > 0:
                self.seats_on_bus -= buy_seats
                product = buy_seats * self.sticket_price
                return (buy_seats, product)
            else:
                os.system('cls')
                print("Ви ввели неправильний формат введення.")

class BoughtSeats:
    def __init__(self, route: str, time: str, bought_tickets: int, product_tickets: int):
        self.route = route
        self.time = time
        self.bought_tickets = bought_tickets
        self.product_tickets = product_tickets
    
    def checkBoughtTickets(self):
        product = "Безкоштовно" if self.product_tickets == 0 else self.product_tickets
        print(f"{self.route:<15}{self.time:<20}{self.bought_tickets:<17}{product:<25}")

def inputMenu():
    while True:
        print("Виберіть вивід інформації по:")
        print("1. Маршруту;")
        print("2. Датою.")
        menu = int(input("~ "))
        if menu in (1, 2): return menu
        else:
            os.system('cls')
            print("Ви ввели неправильний формат введення.")

def saveFile(json_data, file_name):
    with open(f'./{file_name}.json', 'w', encoding='utf-8') as f:
        f.write(json_data)

def loadingFile(file_name):
    try:
        with open(f'./{file_name}.json', 'r', encoding='utf-8') as f:
            read = json.load(f)
            for data in read:
                if file_name == "table data":
                    infos.append(Info(
                        route=data["route"],
                        time=data["time"],
                        seats_on_bus=data["seats"],
                        sticket_price=data["price"]
                    ))
                elif file_name == "tickets data":
                    seats.append(BoughtSeats(
                        route=data["route"],
                        time=data["time"],
                        bought_tickets=data["bought"],
                        product_tickets=data["product"]
                    ))
    except:
        return

if __name__ == "__main__":
    work = True
    info = ()

    infos: list[Info] = []
    seats: list[BoughtSeats] = []

    loadingFile("table data")
    loadingFile("tickets data")

    os.system('cls')
    while work:
        try:
            print("Меню:")
            print("1. Додати нові рейси;")
            print("2. Перегляд списку рейсів;")
            print("3. Купівля квитків;")
            print("4. Перегляд списку купляних квитків;")
            print("5. Збереження даних;")
            print("6. Вихід.")
            menu = int(input("~ "))

            os.system('cls')
            match menu:
                case 1:
                    while True:
                        try:
                            print("Скільки ви хочете додати нових рейсів?")
                            print("Щоб вийти введіть \"0\".")
                            new_reis = int(input("~ "))
                            if new_reis == 0:
                                os.system('cls')
                                break
                            if new_reis < 1:
                                os.system('cls')
                                print("Ви ввели неправильний формат введення.")
                                continue
                            for i in range(new_reis):
                                os.system('cls')
                                print(f"{i + 1}-й рейс")
                                new_info = Info()
                                infos.append(new_info)
                            os.system('cls')
                            print("Всі нові рейси додані.")
                            input("Натисніть Enter для продовження...")
                            os.system('cls')
                            break
                        except ValueError:
                            os.system('cls')
                            print("Ви ввели неправильний формат введення.")
                case 2:
                    if len(infos) != 0:
                        menu_sort = inputMenu()
                        for i in range(len(infos)):
                            if menu_sort == 1:
                                infos.sort(key = lambda x: x.time)
                                infos.sort(key = lambda x: x.route)
                            elif menu_sort == 2: infos.sort(key = lambda x: x.time)
                        os.system('cls')
                        print(f"{'#':<5}{'Маршрут':<15}{'Дата та час':<20}{'Вільних місць':<15}{'Квиток':<10}")
                        for i in range(len(infos)):
                            print(f"{i + 1:<5}", end="")
                            infos[i].checkInfoX()
                    else:
                        print("Таблиця порожня.")
                    input("Натисніть Enter для продовження...")
                    os.system('cls')
                case 3:
                    while True:
                        if len(infos) != 0:
                            try:
                                print("На який \"#\" рейсу ви хочете купити квиткі?")
                                print("Щоб вийти введіть \"0\".")
                                number = int(input("~ "))
                                if number == 0:
                                    os.system('cls')
                                    break
                                elif number < 0:
                                    os.system('cls')
                                    print("Ви ввели неправильний формат введення.")
                                    continue
                                os.system('cls')
                                for i in range(len(infos)):
                                    if number - 1 == i and infos[i].seats_on_bus == 0:
                                        print("Місць більше немає.")
                                        input("Натисніть Enter для продовження...")
                                        break
                                    if number - 1 == i:
                                        info = infos[i].buySeats()
                                        new_info = BoughtSeats(infos[i].route, infos[i].time, info[0], info[1])
                                        seats.append(new_info)
                                        os.system('cls')
                                        print(f"Вартість {info[0]} квитків становитиме {info[1]} гривень.")
                                        input("Натисніть Enter для продовження...")
                                os.system('cls')
                                break
                            except (ValueError, NameError, IndexError):
                                os.system('cls')
                                print("Ви ввели неправильний формат введення.")
                        else:
                            print("Немає даних.")
                            input("Натисніть Enter для продовження...")
                            os.system('cls')
                            break
                case 4:
                    if len(seats) != 0:
                        print(f"{'#':<5}{'Маршрут':<15}{'Дата та час':<20}{'Купляні квитки':<17}{'Вартість всіх квитків':<25}")
                        for i in range(len(seats)):
                            print(f"{i + 1:<5}", end="")
                            seats[i].checkBoughtTickets()
                    else:
                        print("Таблиця порожня.")
                    input("Натисніть Enter для продовження...")
                    os.system('cls')
                case 5:
                    first_table = second_table = False

                    if len(infos) != 0:
                        first = [{'route': p.route, 'time': p.time, 'seats': p.seats_on_bus, 'price': p.sticket_price} for p in infos]
                        first_json_data = json.dumps(first, ensure_ascii=False, indent=4)
                        saveFile(first_json_data, "table data")
                        first_table = True

                    if len(seats) != 0:
                        second = [{'route': p.route, 'time': p.time, 'bought': p.bought_tickets, 'product': p.product_tickets} for p in seats]
                        second_json_data = json.dumps(second, ensure_ascii=False, indent=4)
                        saveFile(second_json_data, "tickets data")
                        second_table = True

                    if not first_table and second_table: print("Дані не збережені, таблички пусті.")

                    if first_table and second_table:
                        print("Всі таблички збережені.")
                        first_table = False
                        second_table = False

                    if first_table: print("Збережена тільки перша табличка.")

                    input("Натисніть Enter для продовження...")
                    os.system('cls')
                case 6:
                    print("Програма завершена.")
                    work = False
                case _:
                    os.system('cls')
                    print("Ви ввели неправильний формат введення.")
        except ValueError:
            os.system('cls')
            print("Ви ввели неправильний формат введення.")