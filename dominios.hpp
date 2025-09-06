class Capacidade {
    private:
        static const int LIMITE = 4;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};

class Cartao {
    private:
        static const int LIMITE = 16;
        int valor;
        bool validar(int); // algoritmo de Luhn
    public:
        bool setValor(int);
        int getValor();
};

class Codigo {
    private:
        static const int LIMITE = 10;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

class Data {
    private:
        string MES;
        int DIA;
        int ANO;
        bool validar(int, string, int);
    public:
        bool setValor(int, string, int);
        Data getValor();
}


class Dinheiro {
    private:
        const int MAX = 1000000;
        const int MIN = 1;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};

class Email {
    private:
        static const int LIM = 64;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

class Endereco {
    private:
        const int MIN = 5;
        const int MAX = 30;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

class Nome {
    private:
        const int MIN = 5;
        const int MAX = 20;
        string valor;
        bool validar(string); 
    public:
        bool setValor(string);
        string getValor();
};

class Numero {
   private:
        const int MIN = 1;
        const int MAX = 999;
        int valor;
        bool validar(int);

   public:
        bool setValor(int);
        int getValor(int); 
};

class Ramal {
    private:
        const int MIN = 0;
        const int MAX = 50;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};

class Senha {
    private:
        const int TAMANHO = 5;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

class Telefone {
    private:
        const int TAMANHO = 15;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};


