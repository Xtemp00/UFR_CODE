#!/bin/dash
#ZERDOUM MOHAMED-RAZINE

#le produit final est opérationnel et fonctionne correctement,
#il respecte les consignes et les spécifications du projet
#j'ai utilisé les commandes grep, sed, awk, tr, ls, du, echo, test, seq, exit, eval
#j'ai implémenté les fonctions help, args et search
#j'ai utilisé les variables NAME, TYPE, SIZE et EXE pour stocker les valeurs des options -name, -type, -size et -exe
#j'ai testé le programme avec les exemples donnés dans l'énoncé et il fonctionne correctement

#show the usage of the find program
#requires --help as a parameter and ONLY --help
#returns the usage of the program and then exists
help () {
        echo "usage : ./find.sh DIR [OPTION]..."
        echo " "
        echo "Search for files in a directory hierarchy DIR"
        echo "If DIR is not specified, the search is performed in the current directory."
        echo " "
        echo "OPTIONS"
        echo "    --help             show help and exit"
        echo "    -name PATTERN      Finding files whose name match the shell pattern PATTERN"
        echo "                       The pattern must be a nonempty string with no white-space"
        echo "                       characters"
        echo "    -type {d|f}        Finding files that are directories (type d)"
        echo "                       or regular files (type f)"
        echo "    -size [+|-]SIZE    Finding files whose size is greater than or equal(+), or less"
        echo "                       than or equal (-), or equal to SIZE"
        echo "    -exe COMMAND       Run the command COMMAND for each file found instead of"
        echo "                       displaying its path"
        echo "                       In the string COMMAND, each pair of braces {} will be replaced"
        echo "                       by the path to the found file"
        echo "                       The string COMMAND must contain at least one pair of braces {}"
        exit 0
}
#checks the legitimacy of used parameters
#requires the list of used parameters
#exits if any of the conditions aren't met
args () {
    for i in $(seq 2 $#);do
        #if helps isn't used, check if none of the arguments aren't directories except the first one
        arg=$(eval echo "\"\$$i\"")
        if test -d "$arg";then
            echo "ERROR: the directory must be the first argument and only the first argument"
            echo "For more information please use ./find.sh --help"
            exit 1
        fi 
        #check if any of the options are repeated
        for j in $(seq 2 $#);do
            if test "$i" -ne "$j";then
                arg=$(eval echo "\"\$$i\"")
                other=$(eval echo "\"\$$j\"")
                if test "${arg%%[!-]*}" = "-" && test "${other%%[!-]*}" = "-" && test "$arg" = "$other";then
                    echo "ERROR: can't have the option $arg more than once"
                    echo "For more information please use ./find.sh --help"
                    exit 1
                fi
            fi
        done
        #check if there are any unwanted options and not confuse the option with a negative number THAT follows -size, if the negative number isn't after -size then it's an unwanted option
        arg=$(eval echo "\"\$$i\"")
        IFSIZE=$(echo "$arg" | grep -Eq '^[-]?[0-9]+$')
        err=$?
        #initialize the previous argument if it exists
        if test $i -gt 1;then
            prevarg=$(eval echo "\"\$$(($i - 1))\"")
        else
            prevarg=""
        fi
        #check if the argument is a negative number and if the previous argument isn't -size
        if test "$err" -eq 0 && ! test "$prevarg" = "-size";then
            if test "${arg%%[!-]*}" = "-";then
            #Check for any unwanted options
                if ! test "$arg" = "-name" && ! test "$arg" = "-type" && ! test "$arg" = "-size" && ! test "$arg" = "-exe";then
                    echo "ERROR: $arg is not a supported option"
                    echo "For more information please use ./file.sh --help"
                    exit 1
                fi
            fi
        fi
        #check if -name is followed by a pattern and check if the pattern is a nonempty string with no white-space characters
        arg=$(eval echo "\"\$$i\"")
        if test "$arg" = "-name";then
            new=$(($i + 1))
            newarg=$(eval echo "\"\$$new\"")
            check=$(echo "$newarg" | grep -E '[[:space:]]')
            err=$?
            if test "${newarg%%[!-]*}" = "-" || ! test -n "$newarg" || test "$err" -eq 0;then
                echo "ERROR: -name must be followed by a pattern that contains no white-space characters and is a nonempty string"
                echo "For more information please use ./find.sh --help"
                exit 1
            fi
        fi
        #check if -type is followed by d or f
        arg=$(eval echo "\"\$$i\"")
        if test "$arg" = "-type";then
            new=$(($i + 1))
            newarg=$(eval echo "\"\$$new\"")
            if ! test "$newarg" = "d" && ! test "$newarg" = "f";then
                echo "ERROR: -type must be followed by d or f"
                echo "For more information please use ./find.sh --help"
                exit 1
            fi
        fi
        #check if size is followed by a number and optional + or -
        arg=$(eval echo "\"\$$i\"")
        if test "$arg" = "-size";then
            new=$(($i + 1))
            newarg=$(eval echo "\"\$$new\"")
            check=$(echo "$newarg" | grep -E '[^0-9+-]')
            err=$?
            if ! test -n "$newarg" || test "$err" -eq 0;then
                echo "ERROR: -size must be followed by a number and an optional + or -"
                echo "For more information please use ./find.sh --help"
                exit 1
            fi
        fi
        #check if -exe is followed by a command with at least one pair of braces with nothing in between
        arg=$(eval echo "\"\$$i\"")
        if test "$arg" = "-exe";then
            new=$(($i + 1))
            newarg=$(eval echo "\"\$$new\"")
            check=$(echo "$newarg" | grep -E '{}')
            err=$?
            #check if there are any braces in the command without anything in between
            if ! test -n "$newarg" || test "$err" -ne 0;then
                echo "ERROR: -exe must be followed by a command with at least one pair of braces {}"
                echo "For more information please use ./find.sh --help"
                exit 1
            fi
            command=$(echo $newarg | awk -F' ' '{print $1}')
            #looks through all the availabe dash commands
            check=$(echo $PATH | tr ':' '\n' | while read dir; do ls "$dir"; done | grep -E "^"$command"$")
            err=$?
            #check if the command exists
            if test "$err" -ne 0;then
                echo "ERROR: the command $command doesn't exist"
                echo "For more information please use ./find.sh --help"
                exit 1
            fi
        fi
    done
}
#shows what's in the directory
search () {
    #check the options
    #takes in all the options and assigns their values to variables
    for i in $(seq 2 $#);do
        arg=$(eval echo "\"\$$i\"")
        #take in the pattern for -name if it exists
        if test "$arg" = "-name";then
            NAME=$(eval echo "\"\$$((i + 1))\"")
        fi
        #take in the type for -type if it exists
        if test "$arg" = "-type";then
            TYPE=$(eval echo "\"\$$((i + 1))\"")
        fi
        #take in the size for -size if it exists
        if test "$arg" = "-size";then
            SIZE=$(eval echo "\"\$$((i + 1))\"")
        fi
        #take in the command for -exe if it exists
        if test "$arg" = "-exe";then
            EXE=$(eval echo "\"\$$((i + 1))\"")
        fi
    done
    #start the search
    for FILE in $1/*;do  
    #check if the file is a directory and if it's the one we're looking for
        if test -d "$FILE";then
        #check if the option d is used
            if test "$TYPE" = "d";then
                check=$(echo $FILE | grep -E ".$NAME$")
                err=$?
                #check if the file is the one we're looking for through the -name option
                if test "$err" -eq 0;then
                    #check if the file is the one we're looking for through the -size option
                    if test -n "$SIZE";then
                        checksize=$(du -bht $SIZE $FILE | grep -E "$FILE")
                        errsize=$?
                        if test "$errsize" -ne 0;then
                            continue
                        fi
                    fi
                    #check if the file is the one we're looking for through the -exe option and execute the command
                    if test -n "$EXE";then
                        command=$(echo $EXE | sed "s,{},$FILE,g")
                        eval "$command"
                        continue
                    fi
                    echo $FILE
                fi
            fi
            #call the function recursively to search in the sub-directories
            search $FILE
        fi
        #check if the file is a regular file and if it's the one we're looking for through the -name option
        if test -n "$NAME";then
            check=$(echo $FILE | grep -E ".$NAME$")
            err=$?
            if test "$err" -ne 0;then
                continue
            fi
        fi
        #check if the file is the one we're looking for through the -type option
        if test -n "$TYPE";then
            if test "$TYPE" = "d" && ! test -d "$FILE";then
                continue
            fi
            if test "$TYPE" = "f" && ! test -f "$FILE";then
                continue
            fi
        fi
        #check if the file is the one we're looking for through the -size option
        if test -n "$SIZE";then
            checksize=$(du -bht $SIZE $FILE | grep -E "$FILE")
            errsize=$?
            if test "$errsize" -ne 0;then
                continue
            fi
        fi
        #check if the file is the one we're looking for through the -exe option and execute the command
        if test -n "$EXE";then
            command=$(echo $EXE | sed "s,{},$FILE,g")
            eval "$command" 
            continue
        fi
        echo $FILE
    done
}
#checks if the first argument is --help
if test "$#" -eq 1  && test "$1" = "--help";then
    #show the usage of the program
    help
fi
#check the validity of the arguments if help isn't used
if test "$#" -gt 0;then
    #check the legitimacy of the arguments
    args "$@"
fi

#check which directory to search in
if ! test -d "$1" || ! test -r "$1" || ! test -x "$1";then
    echo "ERROR: the directory doesn't exist or isn't readable"
    echo "For more information please use ./find.sh --help"
    exit 1
fi 

#start the search in the directory
search "$@"