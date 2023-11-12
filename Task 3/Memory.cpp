class Memory {
private:
    vector<int> data;

public:
    Memory(int size = 256) : data(size, 0) {}

    int read(int address) const {
        if (address >= 0 && address < data.size()) {
            return data[address];
        }
        return 0; // Return 0 for out-of-bounds access (you can handle this differently if needed)
    }

    void write(int address, int value) {
        if (address >= 0 && address < data.size()) {
            data[address] = value;
        }
    }
};
