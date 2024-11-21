import openai
import argparse

openai.api_key = "YOUR_API_KEY"

def compile(input_file, output_file):

    additional_text = """
    this is the language grammar

    program_all  -> procedures main

procedures   -> procedures PROCEDURE proc_head IS declarations BEGIN commands END   
             | procedures PROCEDURE proc_head IS BEGIN commands END                 
             | 

main         -> PROGRAM IS declarations BEGIN commands END 
             | PROGRAM IS BEGIN commands END 

commands     -> commands command 
             | command 

command      -> identifier := expression;                                   
             | IF condition THEN commands ELSE commands ENDIF               
             | IF condition THEN commands ENDIF                             
             | WHILE condition DO commands ENDWHILE                         
             | REPEAT commands UNTIL condition;                             
             | FOR pidentifier FROM value TO value DO commands ENDFOR       
             | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR   
             | proc_call;                                                   
             | READ identifier;                                             
             | WRITE value;                                                 

proc_head    -> pidentifier ( args_decl )   

proc_call    -> pidentifier ( args )                

declarations -> declarations, pidentifier           
             | declarations, pidentifier[num:num]   
             | pidentifier                          
             | pidentifier[num:num]                 

args_decl    -> args_decl, pidentifier
             | args_decl, T pidentifier
             | pidentifier
             | T pidentifier

args         -> args, pidentifier   
             | pidentifier          

expression   -> value           
             | value + value    
             | value - value    
             | value * value    
             | value / value    
             | value % value    

condition    -> value = value   
             | value != value   
             | value > value    
             | value < value    
             | value >= value   
             | value <= value   

value        -> num             
             | identifier       

identifier   -> pidentifier                 
             | pidentifier[pidentifier]     
             | pidentifier[num]             

and these are avaible assembly instructions and specification 


k - program counter 
memory p_i : i = 0,1,2,3,..., 2^62 not initialized 
p_0 is accumulator 



GET i ; reads number from user and puts it in p_i, k += 1 ; cost 100
PUT i ; prints number in p_i, k += 1 ; cost 100

LOAD i ; p_0 = p_i, k += 1; cost 10
STORE i ; p_i = p_0, k += 1; cost 10
LOADI i ; p_0 = p_{p_i}, k += 1; cost 20
STOREI i ; p_{p_i} = p_0, k += 1; cost 20

ADD i ; p_0 += p_i, k += 1 ; cost 10
SUB i ; p_0 -= p_i, k += 1 ; cost 10
ADDI i ; p_0 += p_{p_i}, k += 1 ; cost 20
SUBI i ; p_0 -= p_{p_i}, k += 1 ; cost 20

SET x ; p_0 = x, k += 1; cost 50
HALF ; p_0 = floor(p_0 / 2), k += 1; cost 5

JUMP j ; k += j ; cost 1
JPOS j ; p_0 > 0 ? k += j : k +=1 ; cost 1
JZERO j ; p_0 == 0 ? k += j : k +=1 ; cost 1
JNEG j ; p_0 < 0 ? k += j : k +=1 ; cost 1

RTRN i ; k = p_i ; 10
HALT ; stops program ; cost 0


plese compile the program below, wirte any errors. 
    """

    try:
        with open(input_file, 'r', encoding='utf-8') as file:
            prompt = file.read().strip()

        full_prompt = f"{additional_text}\n\n{prompt}"

        response = openai.ChatCompletion.create(
            model="gpt-4",  
            messages=[{"role": "user", "content": full_prompt}]
        )

        response_text = response['choices'][0]['message']['content']

        with open(output_file, 'w', encoding='utf-8') as file:
            file.write(response_text)

        print(f"Response written to {output_file}")

    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    parser = argparse.ArgumentParser(description="compiles a program")
    parser.add_argument("input_file", help="")
    parser.add_argument("output_file", help="")

    
    args = parser.parse_args()

    compile(args.input_file, args.output_file, args.additional_text)

if __name__ == "__main__":
    main()
