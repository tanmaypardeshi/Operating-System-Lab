#!/bin/bash


function create {
	extension=${1##*.}
	if [ $extension == "txt" ];
	then
		if [ -f "$1" ];
		then
			echo ""
			echo "----------------------------------------------"
			echo "File $1 exists, please continue operations"
			echo "----------------------------------------------"
			echo ""
		else
			echo ""
			echo "-----------------------------------------"
			echo "File not found"
			echo "-----------------------------------------"
			echo ""
			touch $1
			echo "========================================" >> "$1"
			echo "ID		Name    	Price" >> "$1"
			echo "========================================" >> "$1"
			echo "File created!"
			echo ""
	fi
	else
		echo ""
		echo "------------------------------------------"
		echo "Please enter .txt extension only"
		echo "------------------------------------------"
		echo ""
	fi
}

function view {
	if [ -f "$1" ];
	then
		echo ""
		echo "Contents of file are:- "
		echo "	"
		cat $1
		echo ""
		echo ""
	else
		echo "----------------------------------------------------"
		echo "Select or create a DB using option 1"
		echo "----------------------------------------------------"
	fi

}

function insert {

	if [ -f "$1" ];
	then
		read -p "Enter id of item:- " id
		read -p "Enter name of item:- " name
		read -p "Enter price of item:- " price
		echo "$id		$name	     $price" >> "$1"
		echo ""
		echo "Inserted record!"
				
	else
		echo "----------------------------------------------------"
		echo "Select or create a DB using option 1"
		echo "----------------------------------------------------"
	fi
}

function delete {

	if [ -f "$1" ];
	then
		read -p "Enter ID of item to delete:- " id
		val=($(grep -iw $id $1))
		if test -z "$val" 
		then
			echo ""
			echo "----------------------------------------------------"
			echo "Record not found!"
			echo "----------------------------------------------------"	
		else
			grep -vw $id $1 > temp.txt
			rm $1
			mv temp.txt $1
			echo ""
			echo "Deleted record successfully"
			echo ""
			view $1
		fi	
	else
		echo "----------------------------------------------------"
		echo "Select or create a DB using option 1"
		echo "----------------------------------------------------"
	fi
}

function modify {
	
	if [ -f "$1" ];
	then
		read -p "Enter ID of item to modify:- " id
		val=($(grep -iw $id $1))
		if test -z "$val" 
		then
			echo ""
			echo "----------------------------------------------------"
			echo "Record not found!"
			echo "----------------------------------------------------"
		else
			echo "Record found:"
			echo "$id		${val[1]}	     ${val[2]}"
			read -p "Enter item name:- " val[1]
			read -p "Enter item price:- " val[2]
			sed -in "/$id/d" $1
			echo "$id		${val[1]}	     ${val[2]}">> $1
			echo "Modified successfully!"
			echo ""
			view $1
		fi
	else
		echo "----------------------------------------------------"
		echo "Select or create a DB using option 1"
		echo "----------------------------------------------------"
	fi
}


echo ""
echo "Electronic items database"
echo ""


	while [ 1 ]
	do
		echo "Select an option from the following:- "
		echo ""
		echo "1. Create/Select database"
		echo "2. View details of electronic item"
		echo "3. Insert a new item"
		echo "4. Delete an item from the database"
		echo "5. Modify an existing record"
		echo "6. Exit the program"
		echo ""
		read -p  "Enter your choice:- " choice
		
		case $choice in 
			1) 
				echo ""
				echo "Create is selected"
				echo ""
				read -p "Enter filename:- " filename
				create $filename
				echo "";;
			2) 
				echo ""
				echo "View is selected"
				echo "" 
				view $filename
				echo "";;

			3) 
				echo ""
				echo "Insert is selected"
				insert $filename
				echo "";;

			4) 
				echo ""
				echo "Delete is selected"
				delete $filename
				echo "";;
			5) 
				echo ""
				echo "Modify is selected"
				modify $filename
				echo "";;
			6) 
				echo ""
				echo "Exiting program"
				echo ""
				exit;;
			*) 
				echo "Invalid choice"
				echo "";;
		esac
	done



