#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int size = 7;

class Place
{
public:
    char **places;
    int price;
    Place(int price=100)
    {
        this->places = new char*[size];
        for(int i=0;i<size;i++)
            places[i] = new char[size];
        this->price = price;
        for(int i = 0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                places[i][j] = 'O';
            }
        }
    }

    int get_price(int row, int col)
    {
        return price * row + col * 5;
    }

    void get_places()
    {
        cout << "Цены указаны в скобках к месту" << endl;
        for(int i = 0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                cout << places[i][j]<< "("<< get_price(i,j) << ")" << " ";
            }
            cout << endl;
        }
    }

    void set_place(int row, int col)
    {
        places[row][col] = 'X';
    }

    void set_place_char(int row, int col, char temp_place)
    {
        places[row][col] = temp_place;
    }
};

class Theater
{
public:
    string name;
    string address;
    Place *places;
    Theater(string name, string address)
    {
        this->name = name;
        this->address = address;
        this->places = new Place();
    }

    void get_info()
    {
        cout << name << " " << address << endl;
    }
};

class Booking
{
public:
    string phone;
    string name_client;
    int quantity_tickets;
    Place *places;
    Booking(string phone, string name_client, int quantity_tickets)
    {
        this->phone = phone;
        this->name_client = name_client;
        this->quantity_tickets = quantity_tickets;
        places = new Place();
    }

    void get_booking()
    {
        cout << name_client << " " << phone << " " << quantity_tickets << endl;
    }
};

class TicketOffice{
public:
    string name_show;
    string genre;
    string date;
    int duration;
    vector<Theater> theaters;
    vector<Booking> clients;
    TicketOffice(string name_show, string genre, string date, int duration)
    {
        this->name_show = name_show;
        this->genre = genre;
        this->date = date;
        this->duration = duration;
    }

    void add_theater()
    {
        string name;
        string address;
        cout << "Название театра: ";
        cin >> name;
        cout << "Адрес театра: ";
        cin >> address;
        theaters.push_back(Theater(name, address));
        cout << "Театр добавлен!" << endl;
    }

    void get_info()
    {
        cout << name_show << " " << genre << " " << date << " " << duration << endl;
    }

    void get_theaters()
    {
        for(int i=0;i<theaters.size();i++)
        {
            cout << i << " ";
            theaters[i].get_info();
        }
    }

    void get_clients()
    {
        for(int i=0;i<clients.size();i++)
        {
            clients[i].get_booking();
        }
    }

    void add_booking()
    {
        string phone;
        string name_client;
        int quantity_tickets;
        cout << "Имя клиента: ";
        cin >> name_client;
        cout << "Мобильный телефон: ";
        cin >> phone;
        cout << "Выберите театр " << endl;
        get_theaters();
        cout << "Номер театра: ";
        int number_theater;
        cin >> number_theater;
        cout << "Количество билетов: ";
        cin >> quantity_tickets;
        clients.push_back(Booking(phone, name_client, quantity_tickets));
        cout << "Выберите места для бронирования(О-свободно, Х-занято)" << endl;
        theaters[number_theater].places->get_places();
        for(int i=0;i<quantity_tickets;i++)
        {
            cout << "Ряд: ";
            int row;
            cin >> row;
            cout << "Место: ";
            int col;
            cin >> col;
            theaters[number_theater].places->set_place(row, col);
        }
        clients[clients.size()].places = theaters[number_theater].places;
        cout << "Бронь создана!" << endl;
    }
};

int select_show(vector<TicketOffice>&office)
{
    cout << "Выберите спектакль" << endl;
    for(int i=0;i<office.size();i++)
    {
        cout << i << " ";
        office[i].get_info();
    }
    cout << "Номер: ";
    int number;
    cin >> number;
    return number;
}

void add_show(vector<TicketOffice>&office)
{
    string name_show;
    string genre;
    string date;
    int duration;
    cout << "Название спектакля: ";
    cin >> name_show;
    cout << "Жанр: ";
    cin >> genre;
    cout << "Дата: ";
    cin >> date;
    cout << "Продолжительность: ";
    cin >> duration;
    office.push_back(TicketOffice(name_show, genre, date, duration));
    cout << "Спектакль добавлен!" << endl;
}

void import_data(vector<TicketOffice>&office)
{
    ifstream ticket_office("ticket_office.txt");
    while(!ticket_office.eof())
    {
        string name_show;
        string genre;
        string date;
        int duration;
        ticket_office >> name_show;
        ticket_office >> genre;
        ticket_office >> date;
        ticket_office >> duration;
        office.push_back(TicketOffice(name_show, genre, date, duration));
    }
    office.pop_back();
    ticket_office.close();

    int counter;

    ifstream theaters("theaters.txt");
    counter = 0;
    while(!theaters.eof())
    {
        theaters >> counter;
        string name;
        string address;
        theaters >> name;
        theaters >> address;
        office[counter].theaters.push_back(Theater(name, address));
    }
    office[counter].theaters.pop_back();
    theaters.close();

    ifstream places("places.txt");
    while(!places.eof())
    {
        counter = 0;
        int theatr;
        places >> counter >> theatr;
        for(int row = 0;row<size;row++)
        {
            for(int col=0;col<size;col++)
            {
                char temp_place;
                places >> temp_place;
                office[counter].theaters[theatr].places->set_place_char(row, col, temp_place);
            }
        }
    }
    places.close();

    ifstream clients("clients.txt");
    counter = 0;
    while(!clients.eof())
    {
        int theatr;
        clients >> counter >> theatr;
        string phone;
        string name_client;
        int quantity_tickets;
        clients >> name_client;
        clients >> phone;
        clients >> quantity_tickets;
        office[counter].clients.push_back(Booking(phone, name_client, quantity_tickets));
        office[counter].clients[office[counter].clients.size()].places = office[counter].theaters[theatr].places;
    }
    office[counter].clients.pop_back();
    clients.close();

    cout << "Данные загружены!" << endl;
}

void export_data(vector<TicketOffice>&office)
{
    ofstream ticket_office("ticket_office.txt");
    ofstream theaters("theaters.txt");
    ofstream clients("clients.txt");
    ofstream places("places.txt");
    for(int i=0;i<office.size();i++)
    {
        ticket_office << office[i].name_show << " " << office[i].genre << " " <<
        office[i].date << " " << office[i].duration << endl;
        for(int j=0;j<office[i].theaters.size();j++)
        {
            theaters << j << " " << office[i].theaters[j].name << " " <<
            office[i].theaters[j].address << endl;
        }
        for(int j=0;j<office[i].theaters.size();j++)
        {
            places << i << j << " ";
            for(int row = 0;row<size;row++)
            {
                for(int col=0;col<size;col++)
                {
                    places << office[i].theaters[j].places->places[row][col] << " ";
                }
            }
            places << endl;
        }
        for(int j=0;j<office[i].clients.size();j++)
        {
            clients << i << j << " " << office[i].clients[j].name_client << " " <<
            office[i].clients[j].phone << " " <<  office[i].clients[j].quantity_tickets << endl;
        }
    }
    ticket_office.close();
    theaters.close();
    clients.close();
    places.close();
    cout << "Данные выгружены!" << endl;
}

void main_menu()
{
    vector<TicketOffice>office;
    while(true)
    {
        cout << endl;
        cout << "\tМеню" << endl;
        cout << "1)Добавить спектакль" << endl;
        cout << "2)Показать все спектакли" << endl;
        cout << "3)Добавить театр" << endl;
        cout << "4)Показать все театры" << endl;
        cout << "5)Добавить бронь" << endl;
        cout << "6)Показать все брони" << endl;
        cout << "7)Выгрузить данные" << endl;
        cout << "8)Загрузить данные" << endl;
        cout << "9)Выход" << endl;
        cout << "> ";
        int answer;
        cin >> answer;
        switch (answer) {
            case 1:
            {
                add_show(office);
                break;
            }
            case 2:
            {
                for(int i=0;i<office.size();i++)
                {
                    office[i].get_info();
                }
                break;
            }
            case 3:
            {
                int number = select_show(office);
                office[number].add_theater();
                break;
            }
            case 4:
            {
                for(int i=0;i<office.size();i++)
                {
                    office[i].get_theaters();
                }
                break;
            }
            case 5:
            {
                int number = select_show(office);
                office[number].add_booking();
                break;
            }
            case 6:
            {
                for(int i=0;i<office.size();i++)
                {
                    office[i].get_clients();
                    cout << endl;
                }
                break;
            }
            case 7:
            {
                vector<TicketOffice>temp;
                export_data(temp);
                office = temp;
                break;
            }
            case 8:
            {
                import_data(office);
                break;
            }
            case 9:{
                exit(0);
            }
            default:
            {
                break;
            }
        }
    }
}

int main()
{
    main_menu();
    return 0;
}