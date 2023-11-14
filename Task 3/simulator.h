void CPU::add(int destination, int source1, int source2) {
    registers[destination] = (registers[source1] + registers[source2]) & 0xFF;
}
