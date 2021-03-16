# Echo

    echo "Hello Wolrd"

# Variable

    W=7
    echo "variable w = $W"

# For loop

    #!/bin/bash
    for i in 1 2 3 4 5
        do
            echo "Welcome $i times"
    done

OR

    #!/bin/bash
    for i in {1..5}
        do
            echo "Welcome $i times"
    done

OR

    #!/bin/bash
    echo "Bash version ${BASH_VERSION}..."
    for i in {0..10..2}
        do 
            echo "Welcome $i times"
    done

# IF statement

    if [ $Var1 -gt 100 ]
    then
        echo "Hey that\'s a large number."
        pwd
    fi
OR

    if [[ $VAR -gt 10 ]]
    then
        echo "The variable is greater than 10."
    else
        echo "The variable is equal or less than 10."
    fi

OR

    if [[ $VAR -gt 10 ]]
    then
        echo "The variable is greater than 10."
    elif [[ $VAR -eq 10 ]]
    then
        echo "The variable is equal to 10."
    else
        echo "The variable is less than 10."
    fi

# User Input 

    read Var
    echo "$Var"

# Arithemtic

    #Using expr with backtick
    Val1=`expr 30 / 10`
    echo $Val1
    
    #Using expr within command substitute
    Val2=$( expr 30 - 10 )
    echo $Val2

    # Using 'let' command
    let Val3=9*3
    echo $Val3
    
    # Using 'let' command
    let "Val4 = 8 / 3"
    echo $Val4

    # Using argument value in arithmetic operation
    let "Val5 = 50 + $Var1"
    echo $Val5

    # Calculate the mathematical expression
    Val6=$((10*5+15))
    echo $Val6
    
    # Using post or pre increment/decrement operator
    Val7=41
    ((Val7++))
    echo $Val7
    ((--Val7))
    echo $val7
    
    # Using shorthand operator
    (( val7 += 60 ))
    echo $val7
    
    # Dividing 40 by 6
    (( Val8 = 40/6 ))
    echo $val8

    # Dividing 55 by 3 with bc only
    echo "55/3" | bc
    
    # Dividing 55 by 3 with bc and -l option
    echo "55/3" | bc -l

# Logical Operator

    if [[ $varA == 1 && ($varB == "t1" || $varC == "t2") ]]; then



