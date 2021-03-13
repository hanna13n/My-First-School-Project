#include <iostream.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <time.h>
int i, x, y;
char sys[] = "***WELCOME TO OUR PROJECT***";
void graphics(void);
void sound(void);
void hotel_text(void);
void sound1(void);
void start(void)
{
    clrscr();
    x = getmaxx();
    y = getmaxy();
    char password[] = "antonians", pass[20], ch = 'a';
    int p;
    gotoxy(30, 12);
    cout << "\n      Enter Password:" << endl;
    i = 0;
    gotoxy(38, 13);
    while (ch != 13)
    {
        ch = getch();
        if (ch != 13)
        {
            cout << "*";
            pass[i] = ch;
        }
        i++;
    }
    pass[i - 1] = '\0';
    p = strcmp(password, pass);
    if (p != 0)
    {
        clrscr();
        gotoxy(30, 12);
        cout << "\nAccess Denied";
        sound();
        getch();
        delay(100);
        exit(0);
    }
    outtextxy(270, 270, "HANNA NECHIKKADAN");
    outtextxy(270, 290, "BETSA ROSE DOMINIC");
    outtextxy(270, 310, "NANDANA S");
    outtextxy(270, 330, "KEERTHI N P");
    outtextxy(270, 350, "SERENE JOHN");
    outtextxy(270, 370, "VARSHA JOSE");
    settextstyle(10, 0, 1);
    outtextxy(60, 10, "ST.ANTONY'S PUBLIC SCHOOL");
    outtextxy(80, 100, "SALES MANANGEMENT SYSTEM");
    outtextxy(30, 120, "------------------------");
    outtextxy(130, 210, "PROJECT DONE BY : ");
    delay(20);
}

void sound(void)
{
    for (int hz = 20; hz < 800; hz++)
        sound(hz);
    delay(100);
    nosound();
}

class product
{
    int pno;
    char pname[20];
    char pbrand[50];
    int stock, qty;
    char war[10];
    float cost;

public:
    void getprdct()
    {
        clrscr();
        cout << "\nEnter product no.\n";
        cin >> pno;
        cout << "\nEnter product name\n";
        gets(pname);
        cout << "\nEnter product brand\n";
        gets(pbrand);
        cout << "\nEnter the no. of products\n";
        cin >> stock;
        cout << "\nEnter the warranty duration\n";
        gets(war);
        cout << "\nEnter the price per product\n";
        cin >> cost;
    }
    void write(product x)
    {
        ofstream out("eshop.dat", ios::binary | ios::app);
        out.write((char *)&x, sizeof(x));
        out.close();
    }
    void putprdct()
    {
        cout << "\t\n\n\nNumber :" << pno
             << "\t\n\n Name   :" << pname
             << "\t\n\n Brand  :" << pbrand
             << "\t\n\n Warranty:" << war
             << "\t\n\n Stock  :" << stock
             << "\t\n\n Cost   :" << cost;
    }
    void read();
    void search();
    void sellprdct();
    void createbill();
    void modify();
    void deleteprdct();
};

void product::read()
{
    clrscr();
    ifstream in("eshop.dat", ios::binary);
    product x;
    in.seekg(0, ios::end);
    int size = in.tellg();
    int no = size / sizeof(product);
    int i = 0;
    in.seekg(0);
    while (!in.eof() && (i < no))
    {
        in.read((char *)&x, sizeof(x));
        x.putprdct();
        i++;
    }
    in.close();
}
void product::search()
{
    char name[50];
    char ch;
    char brand[50];
    int f = 0;
    product x;
    char ans[10];
    ifstream in("eshop.dat", ios::binary);
    clrscr();
    cout << "\nSearch by number or name?\n";
    gets(ans);
    if (strcmpi(ans, "number") == 0)
    {
        int no;
        cout << "\nEnter the product no. to be searched\n";
        cin >> no;
        clrscr();
        while (!in.eof() && f == 0)
        {
            in.read((char *)&x, sizeof(x));
            if (no == x.pno)
            {
                x.putprdct();
                f++;
            }
        }
    }
    else if (strcmpi(ans, "name") == 0)
    {
        cout << "\nEnter the product name to be searched\n";
        gets(name);
        cout << "\nDo ypu prefer any brand?(y\\n)\n";
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            cout << "\nEnter the brand name\n";
            gets(brand);
            clrscr();
            while (!in.eof() && f == 0)
            {
                in.read((char *)&x, sizeof(x));
                if (strcmpi(x.pbrand, brand) == 0 && strcmpi(x.pname, name) == 0)
                {
                    x.putprdct();
                    f++;
                }
            }
        }
        else
        {
            while (!in.eof() && f == 0)
            {
                in.read((char *)&x, sizeof(x));
                if (strcmpi(x.pname, name) == 0)
                {
                    x.putprdct();
                    f++;
                }
            }
        }
    }
    else
        cout << "\nINVALID CHOICE!!!";
    if ((strcmpi(ans, "number") == 0 || strcmpi(ans, "name") == 0) && f == 0)
        cout << "\nSuch a product does not exist!!!";
    in.close();
}
void product::sellprdct()
{
    int sell, num, found = 0, count = 0;
    product x, dummy;
    char ans;
    fstream inout("eshop.dat", ios::binary | ios::in | ios::out);
    inout.seekg(0, ios::end);
    int size = inout.tellg();
    int no = size / sizeof(product);
    inout.seekg(0);
    clrscr();
    do
    {
        found = 0;
        int i = 0;
        cout << "\nEnter the product number to be sold\n";
        cin >> num;
        inout.seekg(0, ios::beg);
        while (!inout.eof() && found == 0 && i < no)
        {
            inout.read((char *)&x, sizeof(x));
            count++;
            i++;
            if (x.pno == num)
            {
                found++;
                if (x.stock > 0)
                {
                    cout << "\n"
                         << x.stock << " " << x.pname << " are available in the store\n";
                    cout << "\nEnter the no.of " << x.pname << " to be sold\n";
                    cin >> sell;
                    if (sell > x.stock)
                        cout << "\nOnly " << x.stock << " " << x.pname << "s are available to sell\n";
                    else
                    {
                        fstream out("bill.dat", ios::out | ios::binary | ios::app);
                        x.qty = sell;
                        x.stock = x.stock - sell;
                        cout << "\n"
                             << sell << " " << x.pname << " sold\n";
                        cout << "\n"
                             << x.stock << " more " << x.pname << " available\n";
                        inout.seekp((count - 1) * sizeof(product));
                        inout.write((char *)&x, sizeof(x));
                        out.write((char *)&x, sizeof(x));
                        out.close();
                    }
                }
                else
                    cout << "\nNo more " << x.pname << " are available in store\n";
            }
        }
        if (found == 0)
            cout << "\nSuch a product does not exist...!";
        cout << "\nDoes the customer need anymore product?(y/n)\n";
        cin >> ans;
        if (ans != 'y' && ans != 'Y')
            dummy.createbill();
    } while (ans == 'y' || ans == 'Y');
    remove("bill.dat");
}
void product::createbill()
{
    clrscr();
    float tot = 0;
    product x;
    fstream in("bill.dat", ios::binary | ios::in);
    in.seekg(0, ios::end);
    int size = in.tellg();
    int no = size / sizeof(product);
    int i = 0;
    in.seekg(0);
    cout << "\t\tThe Invoice follows...";
    cout << "\n\n\n\n          ANTONIANS ELECTRICAL APPLIANCES"
         << "\n\n              Anakkal, Kottayam"
         << "\n\n              Ph:04828-262181"
         << "\n==============================================================\n"
         << "\n\nPRODUCT" << setw(30)
         << "QTY" << setw(7)
         << "RATE" << setw(11)
         << "PRICE";
    while (!in.eof() && (i < no))
    {
        in.read((char *)&x, sizeof(x));
        cout << "\n\n " << x.pname << setw(32)
             << x.qty << setw(10)
             << x.cost * x.qty;
        tot = tot + (x.cost * x.qty);
        i++;
    }
    cout << "\n--------------------------------------------------------------------\n"
         << "\n         Grand Total=" << tot << "\n\n\n============================================THANK YOU================================================="
         << "=======================================VISIT   AGAIN :)=========================================\n\n";
}
void product::modify()
{
    float newp;
    int news;
    product x;
    char mod[20], nw[50];
    int found = 0, count = 0, no;
    fstream inout("eshop.dat", ios::in | ios::out | ios::binary);
    clrscr();
    cout << "\nEnter the product no. to be modified\n";
    cin >> no;
    while (!inout.eof() && found == 0)
    {
        count++;
        inout.read((char *)&x, sizeof(x));
        if (x.pno == no)
        {
            cout << "\n\nThe current details are\n";
            x.putprdct();
            cout << "\nEhat do you need to modify?\n";
            gets(mod);
            if (strcmpi(mod, "name") == 0)
            {
                cout << "\nEnter the new name\n";
                gets(nw);
                strcpy(x.pname, nw);
                cout << "\nThe product has been modified\n\n";
                x.putprdct();
            }
            else if (strcmpi(mod, "brand") == 0)
            {
                cout << "\nEnter the new brand\n";
                gets(nw);
                strcpy(x.war, nw);
                cout << "\nThe product has been modified\n\n";
                x.putprdct();
            }
            else if (strcmpi(mod, "cost") == 0)
            {
                cout << "\nEnter the new cost\n";
                cin >> newp;
                x.cost = newp;
                cout << "\nThe product has been modified\n\n";
                x.putprdct();
            }
            else if (strcmpi(mod, "stock") == 0)
            {
                cout << "\nEnter the no. of " << x.pname << "s to be added\n";
                cin >> news;
                x.stock = x.stock + news;
                cout << "\nThe product has been modified\n\n";
                x.putprdct();
            }
            else if (strcmpi(mod, "number") == 0)
            {
                cout << "\nEnter the new number\n";
                cin >> news;
                x.pno = news;
                cout << "\nThe product has been modified\n\n";
                x.putprdct();
            }
            else
                cout << "\nInvalid Choice!!\n";
            inout.seekp((count - 1) * sizeof(product));
            inout.write((char *)&x, sizeof(x));
            found = 1;
        }
    }
    if (found == 0)
        cout << "\nSuch a product does not exist!!\n";
    inout.close();
}

void product::deleteprdct()
{
    fstream in("eshop.dat", ios::in | ios::binary);
    fstream t_out("temp.dat", ios::out | ios::binary);
    int no, found = 0;
    product x;
    char sure;
    clrscr();
    cout << "\nEnter the product mo. to be deleted\n";
    cin >> no;
    while (!in.eof() && found == 0)
    {
        in.read((char *)&x, sizeof(x));
        if (x.pno == no)
        {
            x.putprdct();
            found++;
            cout << "\nAre you sure to delete this Product?(y/n)\n";
            cin >> sure;
            if (sure != 'y' && sure != 'Y')
                t_out.write((char *)&x, sizeof(x));
        }
        else
            t_out.write((char *)&x, sizeof(x));
    }
    if (found == 0)
        cout << "\nSuch a Product does not exist!!!";
    else if (sure == 'y' || sure == 'Y')
        cout << "\n\aThe product is deleted.";
    in.close();
    t_out.close();
    remove("eshop.dat");
    rename("temp.dat", "eshop.dat");
}
void main()
{
    clrscr();
    start();
    product p, dummy;
    int ch;
    char ans, sure;
    do
    {
        clrscr();
        cout << "\n\t\t\t ANTONIANS ELECTRICAL APPLIANCES\n"
             << "\t\t============================================================================\n"
             << "\n\t\t\t\t MAIN MENU\n"
             << "\n\t\t\t\t 1.ADD"
             << "\n\t\t\t\t 2.SEARCH"
             << "\n\t\t\t\t 3.MODIFY"
             << "\n\t\t\t\t 4.SELL"
             << "\n\t\t\t\t 5.DELETE"
             << "\n\t\t\t\t 6.VIEW ALL"
             << "\n\t\t\t\t 7.EXIT"
             << "\n\n\nEnter your choice\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            p.getprdct();
            dummy.write(p);
            break;
        case 2:
            dummy.search();
            break;
        case 3:
            dummy.modify();
            break;
        case 4:
            dummy.sellprdct();
            break;
        case 5:
            dummy.deleteprdct();
            break;
        case 6:
            dummy.read();
            break;
        case 7:
            cout << "\nAre you sure to exit(y/n)?\n";
            cin >> sure;
            if (sure == 'y' || sure == 'Y')
                exit(0);
            break;
        }
        cout << "\nDo you want to continue?(y/n)\n";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    {
        cout << "\n\n\n=======================================THANK YOU ;) ================================";
        cout << "\n\n\n\t\t         PRESS ANY KEY TO EXIT";
    }
    getch();
}