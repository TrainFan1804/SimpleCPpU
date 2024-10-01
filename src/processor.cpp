/*
 * My computer's instructions:
 *
 * - load register with value (can be a register value as well)
 * - execute operation on two register (addition, substraction)
 * - store last operation value in register
 *
 * - ld [reg] [value] / decoded with 0
 * - ex [operation] [reg_one] [reg_two] / decoded with 1
 * - st [reg] / decoded with 2
 */
#include <vector>
#include <iostream>
#include <stdexcept>

class Processor
{
public:
    Processor() : _pr_ct{ 0 } 
    {
        _regs.resize(4, 0);     // init 4 register with 0 values
    }
    
    void run(const std::vector<int> &program)
    {
        _run_prg = program; 
        while(_pr_ct < _run_prg.size())
        {
            int instruction = _run_prg.at(_pr_ct);
            execute(instruction);
        }
    }

    int get_res()
    {
        return _res;
    }

private:
    int _pr_ct;  // program counter
    std::vector<int> _run_prg; // running program

    std::vector<int> _regs;  // register
    int _res; // result regier, will save result from last operation

    void execute(int instruction)
    {
        switch(instruction)
        {
        case 0:
            _regs.at(_run_prg.at(_pr_ct + 1)) = _run_prg.at(_pr_ct + 2);
            _pr_ct += 3;
            break;
        case 1:
            exe_bi_operation(instruction);
            _pr_ct += 4;
            break;
        case 2:
            _regs.at(_run_prg.at(instruction + 1)) = _res;
            _pr_ct += 2;
            break;
        default:
            throw 500;
        }
    }

    void exe_bi_operation(int instruction)
    {
        int operation = _run_prg.at(_pr_ct + 1);
        int v_fi_reg;
        int v_se_reg;

        switch (operation)
            {
            case 1:
                v_fi_reg = _regs.at(_run_prg.at(_pr_ct + 2));
                v_se_reg = _regs.at(_run_prg.at(_pr_ct + 3));
                _res = v_fi_reg + v_se_reg;
                break;
            case 2:
                v_fi_reg = _regs.at(_run_prg.at(instruction + 2));
                v_se_reg = _regs.at(_run_prg.at(instruction + 3));
                _res = v_fi_reg - v_se_reg;
                break;
            default:
                throw 501;
            }
    }
};

int main()
{
    Processor p { };
    std::vector<int> program = {
        0, 7, 20,    // LOAD R0 with value 20
        0, 1, 22,    // LOAD R1 with value 22
        1, 1, 0, 1,  // EXECUTE operation 1 to R0 and R1
        2, 2         // store result to R2
    };

    try
    {
        p.run(program);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Invalid register id\n";
        return 1;
    }
    catch(int error_code)
    {
        std::cout << "Wrong instruction\n";
        std::cout << "Error code: " << error_code << "\n";
        return 1;
    }
    
    std::cout << p.get_res() << "\n";
}

