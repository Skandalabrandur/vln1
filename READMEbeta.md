

Þegar forritið er ræst keyrir forritið mainUI.cpp og það birtir eftirfarandi
valkosti:

    A - ADMIN
    S - SALES
    B - BAKER
    D - DELIVERY
    Q - QUIT
    
Input byggist á að notandi pikkar inn þann char sem á við það menu
sem hann vill fara inn í, t.d. mundi bakari velja 'b'. Ekki skiptir máli hvort
char sé uppercase eða lowercase, forritið breytir input í lowercase áður
en eitthvað annað er keyrt.

Þegar forritið er keyrt í fyrsta sinn á tölvu notanda er "data" folderinn
tómur og þar með inniheldur kerfið engar pítsur, staðsetningar, álegg
eða neitt annað og því skal notandi initializea kerfið með því að skrá
álegg og er það hægt í gegn um ADMIN valkostinn.

Þegar ýtt er á 'a' fer mainUI.cpp í gegn um 4 if-statements til að sjá hvort
inputið passar við mögulegan valkost á skjá. 'a' samsvarar "A - ADMIN"
og þá er hreinsað af skjá með því að kalla clearscreen() fallið úr klasanum
customLibraries/UIFunctions.h. Síðan fer mainUI.cpp inn í adminUI klasann
og keyrir displayAdminMenu() sem gefur þetta á skjá:

    P - MANAGE PIZZAS
    T - MANAGE TOPPINGS
    L - MANAGE LOCATIONS
    B - BACK

Forritið keyrir hina valkostina á sama hátt með því að fara í þeirra klasa og
keyra display menu föllin.

    deliveryUI -> displayDeliveryMenu()
    salesUI -> displaySalesMenu()
    bakerUI -> displayBakerMenu()

Eftir að farið er inn í admin menu skal búa til toppings eða location. Ekki er
hægt að búa til pizzu strax þar sem ekki eru nein topping til að setja á pizzur.
Þegar valkostur er stimplaður inn leitar forritið af tilheyrandi falli

    MANAGE PIZZAS -> displayPizzaMenu()
    MANAGE TOPPINGS -> displayToppingMenu()
    MANAGE LOCATIONS -> displayLocationMenu()
    
og keyrir það. Þá fæst eitt af þessum þrem menu-um.

    C - CREATE A NEW MENU PIZZA
    L - LIST MENU PIZZAS
    D - DELETE MENU PIZZA
    B - BACK
    
    C - CREATE NEW TOPPING
    L - LIST TOPPINGS
    B - BACK
    
    C - CREATE NEW LOCATION
    L - LIST LOCATIONS
    B - BACK
    
Ekki er hægt að búa til pizzur án þess að hafa fyrst búið til topping, þannig
ef MANAGE PIZZAS -> CREATE A NEW MENU PIZZA er valið þá fæst upp
villuskilaboð um að ekki eru til nein topping og notandi beðinn um að búa
til topping áður en lengra er haldið.

Ef toppings eru til og notandi vill búa til pizzu skal velja MANAGE PIZZAS
-> CREATE A NEW MENU PIZZA. Þá kallar forritið á pizzaService klasann
og keyrir fallið createAndAppendMenuPizza(). Þá er beðið um nafn á
pizzunni (t.d. Eldórado, Meat n' Cheese, Tokyo, ...). Síðan er beðið um
fjölda áleggja sem skal setja á pizzuna, og þar eftir er birtur listi af öllum
toppings á skrá með því að fara inn í toppingService.h og kalla á fallið
listToppingsWithIndex() og notandi beðinn um að stimpla inn hvaða
topping hann vill setja á pizzuna. Fallið getToppingAt() í toppingService
klasanum sér um að taka inn input frá notanda og ná í Topping objectið
sem á við það input. Pizzan er núna geymd í data foldernum í sama file og
allar hinar menu pizzur.

Ef notandi vill sjá allar pizzur á menu getur hann valið MANAGE PIZZAS
-> LIST MENU PIZZAS þá kallar forritið á pizzaService klasann og þar inni á
listMenuPizzas() fallið. Þá er fileinn með öllum menu pizzum prentað á skjá línu eftir línu.

Ef notandi vill eyða pizzu af matseðli er hæt að velja MANAGE PIZZAS
-> DELETE MENU PIZZA, þá kallar forritið á pizzaService klasann og þar inni
á deleteMenuPizza fallið. Það fall kallar á fall sem prentar út allar pítsur á
matseðli með númerum og síðan er tekið við input frá notanda. Sú pizza er
síðan eydd úr skránni sem inniheldur allar pizzur á matseðli.

Þá skal velja MANAGE TOPPINGS -> CREATE NEW TOPPING. Þá kallar
forritið á klasann toppingService.h og þar inni fallið createNewTopping().
Það fall biður um nafn og verð á áleggi frá notanda, býr til Topping object
með Topping klasanum og vistar það í skrá í data foldernum. Nú er það
vistað og mun ekki eyðast þótt kerfið sé endurræst.

Ef MANAGE TOPPINGS -> LIST TOPPINGS er valið þá fer forritið aftur inn
í toppingService klasann og keyrir listToppings() fallið. Þá birtast öll álegg
með nafni og verði, hvert í eigin línu.

    --
    
Ef notandi velur að fara í SALES þá birtist eftirfarandi

    P - PLACE ORDER
    L - LIST ORDERS
    D - MARK ORDER AS DELIVERED
    B - BACK
    
Fyrst af öllu þarf að leggja inn pöntun. Notandi stimplar inn 'p' og þá kallar forritið á orderService klasann og þar inni á fallið createNewOrder(). Það generatear nýtt Order ID með því að bæta 1 við fjölda pantana. Siðan er notandi beðinn um nafn á viðskiptavin, staðsetningu og hvort hann vill sækja eða fá sent. Þær upplýsingar eru síðan geymdar í Order klasa.
