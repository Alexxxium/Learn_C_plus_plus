
#include "Class.h"


void sas1() {

    Array ary{ 1, 3, 5 };
    Array ar(ary);
    Array arr = ar;
    arr = ar;
    arr = { 0, 8 };
    arr = { 0, 8 };
    arr.out_array();
}

void sas2() {
                                            
    {                                       // начало области видимости

        Child child(0, 1, 2);               // сначала сработает конструктор главного родителя (от старшего к младшему)
        std::cout <<
            child.getPP() << ' ' <<         // родительский метод (самый старший)
            child.getP() << ' ' <<          // родительский метод
            child.getC() << '\n';           // дочерний метод

        std::cout << '\n';
        child.Parent_Parent::out();         // вызов родительского метода через оператор области видимости
        std::cout << '\n';
        child.Parent::out();
        std::cout << '\n';
        child.out();
        std::cout << '\n';
    }                                       // конец области видимости
                                            // сначала сработает деструктор самого младшего дочернего класса (от младшего к старшему)
}

void sas3() {

    Public_child child_pub("Alex", 21, 30, 1);
    Private_child child_priv("Kate", 22, 25, 4);
    Protect_child child_prtct("Roy", 23, 47, 7);

    //child_pub.group = 24;             // protected->protected - нет прямого доступа
    //child_pub.people = 39;            // private->нет доступа 
    child_pub.now_date = 17;            // public->public - открытый доступ

    //child_priv.group = 5;             // protected->private - нет прямого доступа
    //child_priv.people = 28;           // private->нет доступа
    //child_priv.now_data = 3;          // public->private - закрытый доступ

    //child_prtct.group = 1;            // protected->protected - закрытый доступ
    //child_prtct.people = 26;          // private->нет доступа
    //child_prtct.now_data = 12;        // public->protected - закрытый доступ

}

void sas4() {
    
    /*
    *   Переопределение методов родительского класса в дочерним, позволяет использовать альтернативную, перегруженную версию,
    *   игнорируя родительскую. Подходит для быстрого переписания исходного класса, используя дочерний!
    * 
    *   Множественное наследование может вызвать неоднозначность, если совпадают имена членов или методов,
    *   а также может возникнуть ситуация "алмаза смерти", когда у родителей дочернего класса есть свой, общий, другой родитель
    */

    const Light_operation values1(4, 5);
    const Binari_operation values2(5, 7);

    //value2.del();                             // мы закрыли доступ к этому методу

    std::cout <<
        values1.sum() << '\n' <<
        values2.sum() << '\n' <<
        values2.mul() << '\n';                  // используем родительскую версию, т.к. мы открыли доступ через using-объявление

}



void sas5() {

    /*
    *   При создании объекта класса Child сначала выполняется построение части Parent, а затем уже части Child. 
    *   Помните, что тип отношений в наследовании — «является». Поскольку Child «является» Parent, то логично, что Child содержит часть Parent.
    *   Поскольку Child имеет часть Parent, то указатель или ссылка класса Parent может указывать на Child!
    * 
    *   Если мы создадим ссылку или указатель класса Parent, то они могут видеть только члены класса Parent 
    *   (и члены любых других классов, которые наследует Parent). Таким образом, указатель/ссылка класса Parent не может увидеть Child::getName(). 
    *   Следовательно, вызывается Parent::getName(), а rParent и pParent сообщают, что они относятся к классу Parent, а не к классу Child.
    * 
    *   В таком случае, это отличная замена перегрузки функции, ведь мы можем создать необходимый функционал в родительском классе,
    *   для объединения всех или нужных дочерних объектов. На практикке нам достаточно ссылаться на дочерний объект, не зная родительского
    *   Такие решения называются конченными!
    * 
    *   Виртуальная функция - это особый тип функции, которая, при её вызове, выполняет «наиболее» дочерний метод, 
    *   который существует между родительским и дочерними классами. Это свойство еще известно, как полиморфизм.
    *   Дочерний метод вызывается тогда, когда совпадает сигнатура (имя, типы параметров и является ли метод константным)
    *   и тип возврата дочернего метода с сигнатурой и типом возврата метода родительского класса. 
    *   Такие методы называются переопределениями (или «переопределенными методами»).
    * 
    *   (!) Warnning: 
    * 
    *       Сигнатура виртуального метода дочернего класса должна полностью соответствовать сигнатуре виртуального метода родительского класса. 
    *       Если у дочернего метода будет другой тип параметров, нежели у родительского, то вызываться этот метод не будет.
    * 
    *       Если вы будете вызывать виртуальную функцию из конструктора класса Parent при том, что дочерняя часть создаваемого объекта еще не была создана,
    *       то вызвать дочерний метод вместо родительского будет невозможно, так как объект child для работы с методом класса Child еще не будет создан. 
    *       В таких случаях, в языке C++ будет вызываться родительская версия метода.
    *       Аналогично и с деструкторами (разрушение инвертированно созданию дочерней иерархии)!
    *       
    *       (+)
    * 
    *      ***** Ресурснозатратная операция! *****
    */
    
    Cat exm_cat("Cat");
    Animal *exmpl = &exm_cat;                                       // указатель класса Animal, указывает на Cat, т.к. Cat наследует Animal
    Animal an(exm_cat);
    Animal *anml = &an;
    
    // Animal f("tedd_deireadh");                                   // конструктор в поле доступа protected: -> инициализируем родительский класс только через дочерние

    Cat cat("Boosi");                                               // имеют доступ к родительскому объекту
    Dog dog("Anais");

    Cat &ref_ct = cat;                                              
    Cat *ptr_ct = &cat;

    std::cout <<                                                    // все идентично
        cat.get_name() << '\t' << cat.speak() << '\n' <<
        ref_ct.get_name() << '\t' << ref_ct.speak() << '\n' <<
        ptr_ct->get_name() << '\t' << ptr_ct->speak() << '\n';

    Animal &ref_cat = cat;                                          // ссылка на родительский класс (кл.сл.: является) объекта Cat!!!!!!
    Animal *ptr_cat = &cat;

    std::cout << '\n' <<
        cat.get_name() << '\t' << cat.speak() << '\n' <<
        ref_cat.get_name() << '\t' << ref_cat.speak() << '\n' <<    // здесь мы уже в области видимости родителя, т.е. Animal
        ptr_cat->get_name() << '\t' << 
        ptr_cat->Cat::Animal::speak() << '\n';                      // так под капотом выглядит обращение к родителю (ссылаемся ЧЕРЕЗ дочерний объект к родительскому)

    Cat cat1("Kate"), cat2("Koozi"), cat3("Barsik");
    Dog dog1("Woolf"), dog2("Dog"), dog3("Shnoopy");

    report(ref_cat);                                                // функция вывода Animal (как альтернатива перегрузке функции)
                                                                    // функцианал родительского класса может служить функцией для всех дочерних объектов
                                                                    
    Animal *arry[] = { &cat1, &cat2, &cat3, &dog1, &dog2, &dog3 };  // массив указателей на Animal, адресуясь на дочерний объект (композиция???)

    for (int i = 0; i < 6; ++i)
        report(arry[i]);                                            // перегруженная версия
    std::cout << '\n';



    
    /* С использованием виртуальных функций */

    Cat cat_0("Musi");
    Dog dog_0("Bobi");

    Animal cat_1(cat_0);
    Animal dog_1(dog_0);

    Animal &ref_c(cat_0);
    Animal *ptr_d(&dog_0);

    cat_0.get_info();
    dog_0.get_info();
    std::cout << "\nAnimals:\n";

    cat_1.get_info();                           // Not info, т.к. это обычный объект, который не знает о существовании дочернего
    dog_1.get_info();

    ref_c.get_info();                           // здесь мы уже знаем о существовании дочернего класса, т.к. ссылаемся через него к родителю
    ptr_d->get_info();                          // идет потбор нужной вртуальной функции к самому дочернему классу


}

void sas6() {

    Chld obj;
    GPrnt &ref = obj;
    ref.get_this()->get_this(); 

}

void sas7() {

    /*
    *   Связывание — это процесс, который используется для конвертации идентификаторов (таких как имена переменных или функций) в адреса.
    *   Хотя связывание используется как для переменных, так и для функций
    * 
    *   Раннее связывание (или «статическая привязка») означает, что компилятор (или линкер) может напрямую связать имя идентификатора 
    *   (например, имя функции или переменной) с машинным адресом. Помните, что все функции имеют свой уникальный адрес. 
    *   Поэтому, когда компилятор (или линкер) встречает вызов функции, он заменяет его инструкцией машинного кода, которая сообщает процессору перейти к адресу функции.
    * 
    *   Позднее связывание (или «динамическая привязка»). В языке C++ для выполнения позднего связывания используются указатели на функции. 
    *   Вкратце, указатель на функцию — это тип указателя, который указывает на функцию вместо переменной. Функция, 
    *   на которую указывает указатель, может быть вызвана через указатель и оператор вызова функции.
    * 
    *   Виртуальная таблица в языке С++ — это таблица поиска функций для выполнения вызовов функций в режиме позднего (динамического) связывания. 
    *   Виртуальную таблицу еще называют «vtable», «таблицей виртуальных функций» или «таблицей виртуальных методов».
    * 
    *   1. Любой касс, который исользует виртуальные функции, имеет свою собственную виртуальную таблицу и скрытый указатель на нее
    *   2. У всех последующих дочерних классов также будет свой указатель на виртуальную таблицу
    *
    * 
    *   Чистая виртуальная функция - виртуальная функция без определения, подразумевается, что будет использоваться переопредление в дочернем классе.
    *   Однако, все же можно реалезовать ее определение, как определение по умолчанию, для этого необходимо прописать тело функции вне тела класса, 
    *   в гдобальной области видимости, через оператор области видимости
    * 
    *   Если в классе есть хотя бы одна чистая виртуальная функция, то этот класс называется абстрактным
    *   Абстрактный класс - класс, объекты которого создавать нельзя!
    * 
    *   Интерфейс — это класс, который не имеет переменных-членов и все методы которого являются чистыми виртуальными функциями! 
    *   Интерфейсы еще называют «классами-интерфейсами» или «интерфейсными классами».
    * 
    *   Абстрактные классы имеют виртуальные таблицы, которые могут использоваться, если у вас есть указатель или ссылка на абстрактный класс. 
    *   Запись чистой виртуальной функции в виртуальной таблице обычно содержит либо нулевой указатель, либо указывает на общую функцию, 
    *   которая выводит ошибку (иногда эта функция называется __purecall), если не было обнаружено переопределения.
    * 
    *   (!) Warnning!
    *       
    *       Не забываем использовать виртуальные деструкторы при работе с интерфейсными классами и с сылками и указателями на родительские классы!
    * 
    *   Виртуальный базовый класс — это класс, объект которого является общим для использования всеми дочерними классами.
    */

    C1 obj;
    Batya *ptr = &obj;
    ptr->func1();       // 1. компилятор переходит к нужной виртуальный таблице (С2) через скрытый указатель, указывающий на нашу таблицу (у каждого класса свой указатель на vtable)
                        // 2. компилятор прошерстит таблицу и найдет нужную версию func1, а именно С2::func1
                        // 3. в дочернем объекте всегда существует vtable, если есть virtual funcs у наследуемого класса, т.к. дочерний класс "является" частью родительского
                        // 4. напоследок: адресная арифметика для классов идентична обычной -> следующий адрес объекта больше предыдущего на число байт памяти класса

    std::string nm1("Mars"), nm2("Neptun"), loc("Sun system");
    Mars sas(nm1, loc);
    std::cout << sas.x_ray_fon();           // используем самое дочернее определение

    Neptun nep(nm2, loc);
    std::cout << nep.x_ray_fon() << "\n\n"; // используем определение по умолчанию
   
    class Interface {                       // пример интерфейсного класса
    public:
       
        void out(){}
        virtual int sas() { return 0; }
        // и т.д.
    };

    Copier temp;    // головной родитель у этого класса (наследник еще двух классов) виртуальный, т.е. один для всех дочерних классов

}

void sas8() {

    /*
    *   Обрезка объектов - явление, которое возникает при коприровании каких-то определенных (родительских) частей объекта, другая же часть (дочерния) отбрасывается
    * 
    *   std::reference_wrapper — это класс, который работает как ссылка, но позволяет выполнять операции присваивания и копирования и совместим с std::vector
    *
    *   1. std::reference_wrapper находится в заголовочном файле functional
    *   2. При создании объекта класса std::reference_wrapper, этот объект не может быть анонимным 
    *      (поскольку анонимные объекты имеют область видимости выражения, что может привести к висячей ссылке)
    *   3. Для получения объекта из std::reference_wrapper используется метод get()
    * 
    */

    Sun sun;
    Dad &ref = sun;     // указывает на дочерний класс, который наследует часть Dad (доступ к Sun через виртуальные функции)
    Dad *ptr = &sun;    // ссылаемся на родительский класс через дочерний (доступ к Sun через виртуальные функции)
    Dad dad = sun;      // копируется только часть родителя Dad!

    ref.get_name();     // Sun -> есть более дочерняя функция
    ptr->get_name();    // Sun -> есть более дочерняя функция
    dad.get_name();     // Dad -> часть Sun отрезалась, вызывается один единственный метод Dad::get_name() Warnning!: можно случайно передать аргумент в функцию по значению

    
    std::vector<Dad> vec;
    vec.push_back(Dad());
    vec.push_back(Sun());           // обрезка ананимного объекта Sun -> берем только часть Dad

    std::cout << std::endl;
    for (int i = 0; i < vec.size(); ++i)
        vec[i].get_name();

    std::vector<Dad*> ptrvec;       // вектор указателей
    ptrvec.push_back(new Dad());
    ptrvec.push_back(new Sun());    // никакой обрезки объекта нет!

    std::cout << std::endl;
    for (int i = 0; i < ptrvec.size(); ++i)
        ptrvec[i]->get_name();      // так же работает через виртуальные функции

    Dad obj1;
    Sun obj2;
    std::vector<std::reference_wrapper<Dad>> vector;    // std::reference_wrapper — это класс, который работает как ссылка, 
                                                        // но позволяет выполнять операции присваивания и копирования
                                                        // объект std::reference_wrapper не может быть анонимным!
    vector.push_back(obj1);
    vector.push_back(obj2);

    std::cout << std::endl;
    for (int i = 0; i < vector.size(); ++i)
        vector[i].get().get_name();                     // для получения объекта из std::reference_wrapper используется метод get()
        
}

void sas9() {

    /*
    *   Приведением к базовому типу - конвертация указателя/ссылки на дочерний класс в родительский, что и делают виртуальные функции
    *   Приведением к дочернему типу - аналогично наоборот
    *   Оператор dynamic_cast - оператор, который срабатывает перед компиляции и конвертирует соответствующие параметры, static_cast - во время компиляции
    * 
    *   Не работает при:
    * 
    *   1.  Наследование типа private или типа protected.
    *   2.  Классы, которые не объявляют или не наследуют классы с какими-либо виртуальными функциями (и, следовательно, не имеют виртуальных таблиц)
    *       Для работы достаточно объявить, например, виртуальный деструктор
    *   3.  Случаи, связанные с виртуальными базовыми классами (на сайте Microsoft вы можете посмотреть примеры таких случаев и их решения)
    */

    Iphone XR;
    Apple *ios = &XR;

    ios->Apple::get_name();     // родительский метод
    ios->get_name();            // дочерний метод
    std::cout << std::endl;

    Apple *app(&XR);                            // указатель класса Apple на объект Iphone (дочерняя часть от нас скрыта)
    Iphone *ph = dynamic_cast<Iphone*>(app);    // преобразовываем указатель класса Apple на класс Iphone (родительская часть скрыта, адочерняя открыта)
    
    ph->Apple::get_name();      // родительский метод
    ph->get_name();             // дочерний метод
    ph->get_Iphone();           // дочерний метод
    ph->get_Apple();            // тоже родительский метод!

    std::cout << std::endl;

    Apple *apple = dynamic_cast<Apple*>(ph);    // обратная конвертация
    apple->Iphone::Apple::get_name();           // путь к методу (для дочерних методов вызов закрыт, даже через оператор области видимости) из-за конвертации (?)
    apple->get_name();          // виртуальный метод -> дочерний        
    apple->get_Apple();         // родительский метод

    std::cout << std::endl;

    Apple *ptrapp = new Apple();                        // указатель на объект Apple (указатель не знает о дочерней части)
    Iphone *ptrphone = dynamic_cast<Iphone*>(ptrapp);   // конвертируем Apple -> Iphone, что невозможно без части Iphone
    if (!ptrphone) std::cout << "nullptr\n";            // dynamic_cast вернул нулевой указаетль!
    //ptrphone->out();              // не работает! т.к. метод использует член, которого сейчас у нас нет!
    //ptrphone->get_name();         // не работает! т.к. метод является виртуальным (переопределением) и берется из виртуальной таблицы (которой у нас нет из-за нулевого указателя)
    ptrphone->get_Apple();          // работает! т.к. метод не взаимодействует с какими либо объектами и членами
    ptrphone->get_Iphone();         // аналогично
   
    std::cout << std::endl;


    Iphone *phone = static_cast<Iphone*>(ph);           // аналогично и через static_cast, но без проверки
    phone->get_Apple();
    phone->get_Iphone();
    phone->get_name();

    Iphone *p = static_cast<Iphone*>(ptrapp);           // указатель на объект Apple (указатель не знает о дочерней части)
    if (p) std::cout << "not null\n";                   // указатель не нулевой, т.к. оператор static_cas не делает проверки!
    std::cout << std::endl;

    Apple &ref0 = XR;
    Iphone &ref = dynamic_cast<Iphone&>(ref0);          // аналогично и ссылками!
}

void sas10() {

    Box1 sas;
    Box2 sys;
    std::cout << sas << sys;

}

int main()
{
    //sas1();
    //sas2();
    //sas3();
    //sas4();
    //sas5();
    //sas6();
    //sas7();
    //sas8();
    //sas9();
    sas10();

    /**********************************************
    * 
    *   Комрозиция (************)
    *   
    *       Композиция - взаимодействие между частями программы (классами) от главной, основной, управляющей части программы к меньшей, автономной, не подчиняющейся пользователю 
    *   части программы, которая отвечает за определенный алгоритм действий, которые так же могут включать в себя менее иерархически важные части. Каждая такая часть 
    *   строго пренадлежит и подчиняется только своей композиции (в привычном нашем смысле), поэтому она так и называется
    *   По логике, композиция "чать корабля - чать команды"
    * 
    *       Отношения в композиции — это отношения части-целого. В отношениях внутри композиции объект несет ответственность за существование частей.
    *   Чаще всего это означает, что часть создается при создании объекта и уничтожается при его уничтожении. Но в более широком смысле это означает,
    *   что объект управляет временем жизни части таким образом, что пользователь, который использует объект, не должен участвовать в этом.
    *   И, наконец, часть не знает о существовании целого.
    * 
    *   Для реализации композиции объект и часть должны иметь следующие отношения:
    *
    *   1. Часть (член) является частью объекта (класса)
    *
    *   2. Часть (член) может принадлежать только одному объекту (классу) в моменте
    *
    *   3. Часть (член) существует, управляемая объектом (классом)
    *
    *   4. Часть (член) не знает о существовании объекта (класса)
    *
    *   Варианты композиции:
    *
    *       Хотя в большинстве композиций создание/удаление частей происходит непосредственно при создании/удалении самой композиции,
    *   есть вариации композиции, где правила несколько видоизменены, например:
    *
    *   1. Композиция может отложить создание некоторых из своих частей до тех пор, пока они не понадобятся. 
    *   Например, строковый класс может не создавать динамический массив символов до тех пор, пока пользователь
    *   не предоставит данные, которые эта строка могла бы хранить
    *
    *   2. Композиция может предпочесть использовать часть, которая была предоставлена ей в качестве входных данных, а не создавать эту часть самостоятельно
    *
    *   3. Композиция может делегировать уничтожение своих частей другому объекту (например, процедуре сбора мусора)
    *
    *   4. Ключевым моментом является то, что композиция должна управлять своими частями самостоятельно, без вмешательства пользователя композиции
    * 
    *   (!) Хорошим правилом является то, что один класс должен выполнять одну конкретную задачу (как в примере с функциями).
    *   Этой задачей может быть хранение, манипулирование данными или координация подклассов
    * 
    ***********************************************  
    * 
    *   Агрегация (************)
    * 
    *       Агрегация - та же композиция, только иерархически младшие части существуют отдельно от главного объекта и могут принадлежать и подчиняться любому другому,
    *   скрытно от пользователя, по логике "имеет" некоторые части, которые подчиняются еще и другим управляющим объектам
    * 
    *       Как и в случае с подтипом композиция, отношения в агрегации также являются отношениями части-целого и однонаправленные. 
    *   Однако, в отличие от композиции, части могут принадлежать более чем одному целому в моменте, 
    *   и целое не управляет существованием и продолжительностью жизни частей. При создании/уничтожении агрегации,
    *   целое не несет ответственности за создание/уничтожение своих частей.
    * 
    *   Для реализации агрегации целое и его части должны соответствовать следующим отношениям:
    *
    *   1. Часть (член) является частью целого (класса)
    *
    *   2. Часть (член) может принадлежать более чем одному целому (классу) в моменте
    *
    *   3. Часть (член) существует, не управляемая целым (классом)
    *
    *   4. Часть (член) не знает о существовании целого (класса)
    *   
    * 
    *   Реализация агрегации:
    *   
    *       Поскольку агрегация подобна композиции, так как обе состоят из отношений части-целого, то они реализуются почти одинаково, 
    *   а разница между ними в основном семантическая. В композиции мы добавляем части к целому, используя обычные переменные-члены 
    *   (или указатели, когда в классе происходит динамическое выделение/освобождение памяти).
    *   
    *   1. Используются указатели/ссылки, которые указывают/ссылаются на части вне класса.
    *
    *   2. Класс не несет ответственности за создание/уничтожение своих частей.
    * 
    *   (!) Хотя агрегации могут быть чрезвычайно полезными, они также потенциально опасны. 
    *   Поскольку в агрегации автоматически не осуществляется освобождение памяти, которую могут занимать части, то 
    *   это должны контролировать вы сами. Если вы забыли выполнить очистку (освободить память), думая, что это должен сделать класс,
    *   то тогда произойдет утечка памяти, поэтому следует быть осторожным.
    * 
    ***********************************************
    * 
    *   Ассоциация (************)
    * 
    *       Ассоциация - отношение объектов, иерархически независимыми между собой, для взятия информации (однонаправленно, двунаправленно или косвенно)
    *   В языке C++ ассоциация — это отношения между двумя классами на уровне классов. 
    *   То есть, первый класс сохраняет прямую или косвенную связь со вторым классом через переменную-член.
    *   
    *       В отличие от композиции или агрегации, где часть является частью целого, в ассоциации объекты между собой никак не связаны. 
    *   Подобно агрегации, первый объект может принадлежать сразу нескольким объектам одновременно и не управляется ими. 
    *   Однако, в отличие от агрегации, где отношения однонаправленные, в ассоциации отношения могут быть как однонаправленными, 
    *   так и двунаправленными (когда оба объекта знают о существовании друг друга)
    * 
    *   В ассоциации два несвязанных объекта должны соответствовать следующим отношениям:
    *
    *   1. Первый объект (член) не связан со вторым объектом (классом)
    *
    *   2. Первый объект (член) может принадлежать одновременно сразу нескольким объектам (классам)
    *
    *   3. Первый объект (член) существует, не управляемый вторым объектом (классом)
    *
    *   4. Первый объект (член) может знать или не знать о существовании второго объекта (класса)
    * 
    *   Реализация ассоциации
    *   
    *   1. Объекты могут получать информацию из каждого ассоциативного объекта
    * 
    *   2. Ассоциация может быть двунаправленной: оба объекта могут менять друг друга
    * 
    *   3. Ассоциация может быть косвенной: Обращение к объекту происходит не напрямую, 
    *   а через идентификатор или через какой-то программный алгоритм действий
    *   
    *   (!) По логике, ассоциация "использует" какой-то объект для достижения каких-то целей
    * 
    ***********************************************
    * 
    *   Зависимость (************)
    * 
    *       Зависимость возникает, когда один объект обращается к функционалу другого объекта для выполнения определенного задания.
    *   Эти отношения слабее отношений в ассоциации, но всё же любое изменение объекта, 
    *   который предоставляет свой функционал зависимому объекту, может стать причиной сбоя работы зависящего объекта. Зависимость всегда является однонаправленной.
    * 
    *       Зависимости обычно не представлены на уровне классов, то есть зависимый объект не связан со вторым объектом через переменную-член. 
    *   Зависимый объект обычно создается при необходимости (например, открытие файла для записи данных) или передается в функцию в качестве параметра 
    *   (например, как std::ostream, участвующий в перегрузке оператора <<)
    */

}


