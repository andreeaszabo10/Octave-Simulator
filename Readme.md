Copyright Szabo Cristina-Andreea 2022-2023

# Octave Simulator

Task 1: Operatia "L"
- se adauga o noua matrice in memorie, am folosit un vector tridimensional
- fiecare matrice nou adaugata va avea un index, un numar de linii si coloane
- am stocat dimensiunile si suma in 3 vectori: "linii", "cols" si "suma"
- am creat un vector v care retine indecsii matricelor -> ajuta la sortare
- am alocat memorie cu malloc daca este prima matrice, altfel am folosit realloc
- am alocat pentru matricea cu indexul introdus "lin" linii si "col" coloane
- am citit o matrice cu dimensiunile "lin" si "col" cu functia "citire"
- am incercat sa implementez si programare defensiva

Task 2: Operatia "D"
- se introduce un index de la tastatura
- se efectueaza operatia doar daca exista in lista o matrice cu acel index
- daca nu exista, se afiseaza un mesaj de eroare
- indexul reprezinta matricea pentru care se afiseaza dimensiunile
- afisez dimensiunile stocate in vectorii "linii" si "cols"
 
 Task 3: Operatia "P"
- se introduce un index de la tastatura
- trebuie afisata matricea care are acel index
- se efectueaza operatia doar daca exista in lista o matrice cu acel index
- daca nu exista, se afiseaza un mesaj de eroare
- afisez cu doua for-uri matricea, folosindu-ma de dimensiunile stocate

Task 4: Operatia "C"
- se introduce un index de la tastatura
- se efectueaza operatia doar daca exista in lista o matrice cu acel index
- daca nu exista, se afiseaza un mesaj de eroare
- am citit numarul de linii dupa care se face redimensionarea: "lin"
- am citit intr-un vector indicii liniilor pentru redimensionare
- am facut acelasi lucru pentru coloane, cu un alt vector
- am creat o copie a matricei mat in maux
- am eliberat memoria matricei mat de la indexul corespunzator
- am alocat memorie pentru aceeasi matrice, pentru noile dimensiuni: lin si col
- am adaugat elementele luate prin combinatii de indicii de linii si coloane
- aceste elemente erau stocate in copia "maux"

Task 5: Operatia "M"
- se introduc 2 indecsi de la tastatura: matricele care trebuie inmultite
- daca nu exista vreo matrice cu oricare din indecsi -> mesaj de eroare
- daca dimensiunile nu fac posibila inmultirea -> alt mesaj de eroare
- in functia pentru operatia M aloc memorie pentru matricea rezultat
- pentru asta cresc indexul ca sa arat ca introduc o matrice noua
- noua matrice va avea numarul de linii al primei matrice
- de asemenea, va avea numarul de coloane al celei de-a doua matrice
- efectuez inmultirea cu functia "inmultire"
- am luat 3 for-uri, primul cu i de la 0 la liniile primei matrice, al doilea cu j de la 0 la coloanele celei de-a doua si al treilea cu k de la 0 la coloanele primei matrici
- in for-ul cu k fac ca fiecare element al noii matrice care are coordonatele i si j sa primeasca suma dintre produsele elementelor cu coordonatele i si k (pentru prima matrice) si k si j (pentru a doua)
- la final am marit index-ul in main ca sa arat ca a fost introdusa o matrice

TasK 6: Operatia "O"
- la aceasta operatie folosesc vectorul suma in care am retinut suma elementelor fiecarei matrice la operatia "L"
- pentru a ordona matricele crescator in functie de sumele elementelor lor am folosit vectorul "v" in care am stocat indecsii matricelor
- am utilizat 2 for-uri unul de la i la numarul de matrice - 1 (adica idx) si altul de la j la numarul de matrice total (adica idx + 1)
- daca suma matricei cu indexul i e mai mare decat suma matricei cu indexul j, interschimb valorile indecsilor, sumelor si dimensiunile celor 2 matrice
- pentru toate operatiile in rest am folosit mat[v[index]] in loc de mat[index] ca sa tin cont de noua ordine a matricelor
- vectorul v retine noua ordine

Task 7: Operatia "T"
- se introduce un index de la tastatura
- se efectueaza operatia doar daca exista in lista o matrice cu acel index
- daca nu exista, se afiseaza un mesaj de eroare
- iau o matrice auxiliara in care retin matricea pe care trebuie sa o transpun si o matrice care sa retina transpusa, amandoua alocate dinamic
- eliberez memoria matricei care trebuie sa fie transpusa, apoi ii aloc memorie astfel: numarul nou de linii va fi numarul vechi de coloane, iar numarul nou de coloane va fi numarul vechi de linii
- am calculat transpusa cu 2 for-uri in care elementul din transpusa de coordonate j si i (for-urile sunt de la i la numarul vechi de coloane si de la j la numarul vechi de linii) devine elementul cu coordonatele i si j al copiei matricei
- tot cu 2 for-uri la fel ca cele de sus am facut ca elementul cu coordonatele i si j al matricei principale sa ia valoarea elementului cu coordonatele i si j al transpusei
- am eliberat memoria pentru transpusa si matricea auxiliara

Task 8: Operatia "R"
- se introduce un index de la tastatura
- se efectueaza operatia doar daca exista in lista o matrice cu acel index
- daca nu exista, se afiseaza un mesaj de eroare
- se afiseaza mesaje de eroare si daca matricea nu e patratica sau puterea e negativa
- am luat o matrice care sa retina rezultatul ridicarii si una care sa retina elementele matricei principale si cu ajutorul careia se va efectua ridicarea
- pentru algoritmul de ridicare la putere iau fiecare bit al exponentului, daca acesta este 1 matricea rezultat devine produsul dintre ea si matricea auxiliara, apoi matricea auxiliara devine produsul inmultirii ei cu ea insasi
- exponentul este impartit la 2 pentru a lua urmatorul bit
- toate acestea se intampla intr-un while care se opreste cand exponentul devine mai mic sau egal cu 0
- matricea principala va primi elementele matricei rezultat

Task 9: Operatia "F"
- se citeste de la tastatura indexul matricei care trebuie eliminata
- se efectueaza operatia doar daca exista in lista o matrice cu acel index
- daca nu exista, se afiseaza un mesaj de eroare
- daca matricea care trebuie eliberata e ultima din lista ii eliberez memoria
- altfel, schimb matricele, incepand de la matricea care trebuie eliberata
- cu un for care porneste de la j = indexul matricei care trebuie eliminata pana la numarul de matrice minus 1 mut toate matricele de la acel index incolo cu o pozitie inainte
- mai intai eliberez memoria pentru matricea indicata de j(adica v[j]) apoi ii aloc memorie dupa dimensiunile urmatoarei matrice din lista si ii atribui elementele acesteia
- cand ajung la ultima matrice, doar ii eliberez memoria, pentru ca nu mai are ce matrice sa vina in locul ei

Task 10: Operatia "S"
- se introduc 2 indecsi de la tastatura: matricele care trebuie inmultite
- daca nu exista vreo matrice cu oricare din indecsi -> mesaj de eroare
- daca dimensiunile nu fac posibila inmultirea -> alt mesaj de eroare
- aloc memorie pentru noua matrice si o matrice auxiliara care retine rezultatul
- in functia strassen am implementat algoritmul astfel: daca matricele sunt de 1 pe 1 matricea rezultat va primi inmultirea celor 2 elemente ale matricelor
- altfel, impart cele 2 matrice care trebuie inmultite in cate 4 cadrane cu ajutorul a 8 matrice auxiliare, calculez cele 7 matrice m1, m2, m3, etc. cu formulele date apeland recursiv functia strassen de fiecare data cand trebuie sa fac inmultirea unor matrice
- cele 4 cadrane sunt matrice care au dimensiunile matricelor care trebuie inmultite impartite la 2
- daca unul din factorii inmultirii este o suma sau diferenta, l-am calculat folosind ori funtia de adunare, ori cea de scadere (in care efectuez adunarea sau scaderea unor matrice)
- rezultatele acestor 2 functii au fost retinute in niste matrice auxiliare, memoria acestora fiind eliberata dupa folosirea lor in apelurile functiei strassen de la calculul celor 7 matrice (m1, m2...)
- apoi am calculat dupa formula cu ajutorul functiei adunare cele 4 cadrane ale matricei rezultat retinute in matricele c1, c2, c3, c4
- la final am reconstruit matricea rezultat utilizand 2 seturi de cate 4 for-uri cu ajutorul carora am unit cele 4 cadrane in ordine
- matricea principala primeste elementele matricei rezultat
- eliberez memoria matricei rezultat

Task 11: Operatia "Q"
- aceasta operatie consta in eliberarea tuturor resurselor
- eliberez memoria pentru fiecare vector folosit: suma, linii, cols si v
- eliberez folosind doua for-uri mai intai coloanele fiecarei matrice, apoi liniile, apoi toti indecsii
