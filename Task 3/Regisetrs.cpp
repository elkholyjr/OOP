class Register {
private:
    int value;

public:
    Register() : value(0) {}

    int getValue() const {
        return value;
    }

    void setValue(int newValue) {
        value = newValue;
    }
};
