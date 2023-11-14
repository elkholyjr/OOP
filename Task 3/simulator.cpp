int Simulator::single_step() {
    if ((cpu.program_counter < memory.memory.size()) && !cpu.is_halted) {
        int instruction = memory.memory[cpu.program_counter];
        int opcode = (instruction >> 16) & 0xFF;
        int operand1 = (instruction >> 8) & 0xFF;
        int operand2 = instruction & 0xFF;

        // Process instruction (opcode, operand1, operand2)
        switch (opcode) {
            case 0x1:
                cpu.load_register(operand1, memory.memory[operand2]);
                break;
            case 0x2:
                cpu.load_register(operand1, operand2);
                break;
            case 0x3:
                cpu.store(operand1, operand2, memory);
                break;
            case 0x4:
                cpu.move(operand1, operand2);
                break;
            case 0x5:
                cpu.add(operand1, operand2 & 0x0F, (operand2 & 0xF0) >> 4);
                break;
            case 0xB:
                cpu.jump(operand1, operand2);
                break;
            case 0xC:
                cpu.halt();
                break;
            default:
                cerr << "Unknown opcode: " << opcode << " at instruction " << cpu.program_counter << endl;
        }
        // Increment the program counter
        ++cpu.program_counter;
        return 1;
    } else {
        return 0;
    }
}

void Simulator::clear() {
    // Reset the registers and memory
    cpu.registers = vector<int>(16, 0);
    memory.memory = vector<int>(256, 0);

    // Reset the program counter
    cpu.program_counter = 0;

    // Reset the halt flag
    cpu.is_halted = false;
}

void Simulator::print() {
    cout << "Registers:\n";
    for (int i = 0; i < cpu.registers.size(); ++i) {
        cout << "R" << i << ": " << hex << cpu.registers[i] << '\n';
    }
    cout << "\n";
}
