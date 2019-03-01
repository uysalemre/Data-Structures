# mail-assigner-data-structures
This is a data structures project that assigns mail adresses for newcomers of a school and gives opportunity of add remove update operations for emails. 

write a program which assigns e-mail address for ITU’s new students. 

The  program  accepts  one  input  file  named  as:  “newStudentsList.txt”.  The  file  contains  new students’ names and surnames. You have to read the file and create a circular linked list which must be sorted alphabetically by surname.Then, youhave to create doubly linked lists for everysurname  in  the  surnameMap.  Each  doubly  linked  list  consists  of  nodes  of “studentInfo”
structure which represent the people with same surname. Definition of the structures are:

structsurnameMap (contains surname information and related pointers).

structstudentInfo (contains name, surname and email information and related pointers).

You have to implement the  following  methods with  appropriate  arguments  for new students’ operations  which  are  not  in  the  file. (We will test  your  functions manually usingall  the operations and a different “newStudentsList.txt” file.)

createList():Creates surnameMapcircular linked list.

insertAll():Inserts all records and information from any file to the lists.

insertNewRecord():Inserts a new record takes information as input parameter.

deleteStudent(): Deletes the studenthaving the given information (this information is taken as parameter) from  studentInfo  list. If  all records  having  the  same  surname,  are  deleted,  then delete that surname node from the surnameMap list. 

deleteSurnameNode():Deletes the surname node having the given “input_surname”. Please be careful  that  if  this  surname  node  has  its  own  studentInfo  list,  you  should  firstly  delete studentInfo nodes.

updateList():If a student changes his/her name/surname, update the variable onthelists.

writeToFile() : Writes the latest version of the list with the expected format to “emailList.txt” as 
an output. 

*The lists should be sorted after insert, delete and update operations. 

For example:  Creation of

1 record has been addedwhich is 

Program assigns ak@itu.edu.tr

1 record has been addedwhich is 

Program assigns aka@itu.edu.tr

1 record has been addedwhich is 

Program assigns akal@itu.edu.tr

1 record has been addedwhi

Program assigns ake@itu.edu.tr

1 record has been addedwhich is again 

Program assigns akali@itu.edu.tr

1 record has been addedwhich is again 

Program assigns akali2@itu.edu.tr

ofthelist with records from the file.

1 record has been addedwhich is “Ali AK”.

@itu.edu.traddress for thegiven request. 

1 record has been addedwhich is “Alp AK”.

aka@itu.edu.traddress for the given request.

1 record has been addedwhich is “Alper AK”.

akal@itu.edu.traddress for the given request.

1 record has been addedwhich is “Ece AK”.

@itu.edu.traddress for the given request. 

1 record has been addedwhich is again “Ali AK”.

akali@itu.edu.traddress for the given request.

record has been addedwhich is again “Ali AK”.

@itu.edu.traddress for the given request.
