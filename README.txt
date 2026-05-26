Lan-Party Tournament 
Simulator 

Acest program scris in C simuleaza gestionarea si 
desfasurarea unui turneu de E-Sports. 
Aplicatia citeste o lista de echipe, filtreaza 
participantii pentru a obține un numar optim ca si o 
putere a lui 2, si simuleaza meciurile runda cu 
runda. 

Structura Proiectului 
main.c - Punctul de intrare in aplicatie. Gestioneaza 
citirea datelor din fisiere, logica turneului si scrierea 
rezultatelor. 

LanParty.c - Contine implementarea operatiilor 
pentru structurile folosite pe parcursul programului.  

LanParty.h - Fisierul de tip header care definește 
structurile unor functii. 

Mod de functionare 

1.  Echipele sunt citite din fisierul de intrare si 
stocate  intr-o lista simplu inlantuita.  

2. Programul calculează cea mai mare putere a lui 2 
mai mica sau egala cu numarul de participanti. 
Echipele cu cel mai mic scor sunt eliminate din lista 
pana la atingerea acestui numar. 

3. Echipele calificate sunt introduse intr-o coada. 
Se extrag cate doua echipe pentru a lupta intr-un un 
meci. Echipa castigatoare primeste un punct la 
scorul general ,dar si puncte individuale pentru 
jucatori si este introdusa intr-o stiva. La finalul 
fiecarei runde, echipele din stiva sunt mutate inapoi 
in coada pentru runda urmatoare.  

4. Cand in turneu mai raman exact 8 echipe, 
acestea sunt salvate separat. La final, cele 8 echipe 
sunt inserate intr-un Arbore Binar de Cautare (BST) 
si afisate in ordine descrescatoare a punctajelor. 

Rulare 

Pentru rulare, ne vom folosi de wsl cu gcc, comanda 
folosita se va afla in Makefile urman sa rulam comanda "make build" urmata de comanda "./checker.sh"