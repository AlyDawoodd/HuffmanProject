#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#define SIZE 100000
struct Code
{
	char value;
	char code[150];
	Code* next;
	Code()
	{
		value = '\0';

		next = NULL;
	}
};





struct Node
{
	int freq;
	char value;
	Node* next;
	Node* parent;
	Node* left;
	Node* right;
	Node()
	{
		value = '/0';
		freq = 0;
		next = NULL;
		parent = NULL;
		left = NULL;
		right = NULL;
	}

};

Code* insertLast1(Code* l, char item, char x[])
{
	//Conditional Stat. to create the linked list for the first time
	if (l == NULL)
	{
		l = (Code*)malloc(sizeof(Code));	//Step 1 and 2
		l->value = item;	//Step 3
		strcpy(l->code, x);//step 4
		l->next = NULL;	//Step 5
	}
	else //General Condition
	{
		Code* it = l;

		//This while is only used to position the iterator on the last node in the L. List
		while (it->next != NULL)
			it = it->next;

		Code* tmp = (Code*)malloc(sizeof(Code));
		tmp->value = item;
		strcpy(tmp->code, x);
		tmp->next = NULL;

		it->next = tmp;
	}
	return l;
}





Node* insertLast(Node* l, char item)
{
	//Conditional Stat. to create the linked list for the first time
	if (l == NULL)
	{
		l = (Node*)malloc(sizeof(Node));	//Step 1 and 2
		l->value = item;	//Step 3
		l->next = NULL;//Step 4
		l->left = NULL;//step 5
		l->right = NULL;//step 6
		l->freq = 1;//step 7
	}
	else //General Condition
	{
		Node* it = l;

		//This while is only used to position the iterator on the last node in the L. List
		while (it->next != NULL)
			it = it->next;

		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->value = item;
		tmp->freq = 1;
		tmp->next = NULL;
		tmp->left = NULL;
		tmp->right = NULL;

		it->next = tmp;
	}
	return l;
}



Node* removeLast(Node** l, Node* item) 
{
	Node* q = *l;
	//Check if the linked list is empty !
	if (l == NULL)
		return NULL;

	//Check if there is only one node inside the linked list
	if (q->next == NULL)
	{
		item = *l;
		*l = NULL;
		//free(l);
	}
	else //General Condition
	{
		Node* it = *l;
		while (it->next->next != NULL) //Position the it on the node BEFORE the last one !
			it = it->next;

		item = it->next;

		it->next = NULL;

	}
	return item;
}



Node* find(Node* l, char item)   
{
	if (l == NULL)
		return NULL;
	else
	{
		Node* it = l;
		while (it != NULL)
		{
			if (it->value == item)
				return it;
			else
				it = it->next;
		}
	}
	return NULL;
}



Node* sort(Node* s, Node* it) {

	Node* temp = s;
	Node* prev = s;


	// if current node freq > head freq 
	// Set current node to be first node
	if (temp->freq <= it->freq)//
	{


		while (prev != NULL && prev->next != it) { // point to the node prior to the current node
			prev = prev->next;

		}
		prev->next = it->next;; // make the node prior to the current node to point to the next of the current node
		it->next = s; // set the current node to be first node
		s = it;
		return s;
	}
	// head freq> current freq
	else {

		while (temp->freq > it->freq) { // set the prev pointer
			prev = temp;// point to the prior Node to the first node's freq that has the same of the current Node or maybe the current node itself
			temp = temp->next;// point to the first node's freq that has the same freq of the current Node or maybe the current node itself

		}


		if (temp->value != it->value) {// if the temp isn't the current Node
			while (temp != NULL && temp->next != it) {
				temp = temp->next; // point the temp to the prior to the current node

			}
			temp->next = it->next; //point the prior node oft the current node to the next of it
			it->next = prev->next;  // point the next of the current Node to the the next of the prev that we set before
			prev->next = it; // point the prev next to  the current Node

		}

		return s;
	}


	return 0;



}







////////////////////////////////////QUEUE USING LINKED LIST//////////////////////
struct Queue
{
	Node* base;
	Queue()
	{

		base = NULL;
	}
};
Queue* enqueue(Queue* s, Node* item)
{

	char c = item->value;
	if (c == '\0')
	{
		if (s->base == NULL) {
			s->base = item;
			item->next = NULL;
			return s;
		}


		else if (item->freq >= s->base->freq) {//if the node parent freq is bigger than the head
			item->next = s->base;
			s->base = item;
			return s;
		}
		else// if the node parent is a middle node
		{
			Node* prev = s->base;
			Node* temp = s->base;
			while (temp->freq > item->freq) {
				prev = temp;
				temp = temp->next;
			}
			item->next = temp;
			prev->next = item;
			return s;

		}




	}
	Node* it = find(s->base, c);//Node to see if the char is already exist or not
	if (it == NULL) {//if the character isn't exist
		s->base = insertLast(s->base, c);
		return s;
	}
	else //the char is already exist
	{
		it->freq++; // add freq
		if (it == s->base) // if the current node is the header ( the biggest freq)
			return s;
		else
			s->base = sort(s->base, it);
		return s;


	}
	return NULL;

}




Node* dequeue(Queue* s, Node* item)
{
	if (s->base == NULL)
		return NULL;
	else
		item = removeLast(&s->base, item);
	return item;
}

Node* hufftree(Queue* s) {
	Node* tmp1 = NULL;
	Node* tmp2 = NULL;
	tmp1 = dequeue(s, tmp1);
	tmp2 = dequeue(s, tmp2);
	if (tmp2 == NULL)
		return tmp1;
	Node* parent = (Node*)malloc(sizeof(Node));
	parent->value = '\0';// \0 credit karim kohel
	parent->freq = tmp1->freq + tmp2->freq;
	parent->right = tmp2;
	parent->left = tmp1;
	tmp1->parent = parent;
	tmp2->parent = parent;
	parent->parent = NULL;
	return parent;



}
Node* findNode(Node* x, char y) { //idea credit amr mekki
	if (x == NULL)
		return NULL;
	if (x->value == y)
		return x;
	Node* Found = findNode(x->left, y);
	if (Found != NULL)
		return Found;
	return findNode(x->right, y);
}
void VairiableLenghtCode(Node* it, char str[]) {
	Node* tmp = it;
	Node* parent = it->parent;
	int i = 0;
	char x;
	while (parent != NULL) {
		if (parent->left == tmp) {
			x = 48; //0
			str[i] = x;
		}
		else if (parent->right == tmp)
		{
			x = 49; //1
			str[i] = x;
		}
		tmp = tmp->parent;
		parent = parent->parent;

		i++;
	}
	str[i] = '\0';
}

void reverse(char str[]) {
	char tmp;
	int i = 0;
	int j = strlen(str) - 1;
	for (i = 0; i < j; i++) {
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		j--;
	}
}

bool ifExist(char str[], char x) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == x)
			return 0;
	}
	return 1;
}

char FromBtoChar(char str[]) //binary to decimal then to char(asci)
{
	int y = 0;
	int x = 0;
	int j = 0;
	for (int i = 7; i >= 0; i--) {
		y = str[i] - '0'; 
		x = x + (pow(2, j) * y); //binary to decimal
		j++;
	}

	return x;// return the asci

}
void getcode(Code* l, char x, char tmp[]) {
	Code* it = l;
	while (it->value != x)
	{
		it = it->next;

	}

	strcpy(tmp, it->code);
}
char getchar(Code* l, char x[]) {
	Code* it = l;
	while (it->next != NULL && strcmp(it->code, x) != 0 )
	{
		it = it->next;

	}
	if (strcmp(it->code, x) == 0)
		return it->value;
	else return false;
}

void FromCHARtoB(char strc, char strb[]) { // char to decimal then decimal to binary
	int j = 0;
	int k = 0;
	int x = strc;
	if (x < 0)
		x = x + 256;//idea credit amr mekki
	for (int s = 0; s < 8; s++) {
		strb[s] = '\0';
	}
	while (x > 0) {
		strb[j] = (x % 2) + '0';
		x = x / 2;
		j++;

	}
	if (strlen(strb) < 8) {
		for (k = 0; k < 8; k++) {
			if (strb[k] == '\0')
				strb[k] = '0';
		}



	}
	reverse(strb);
}



int main()
{
	FILE* READ = fopen("input.txt", "r");
	FILE* VLC = fopen("codes.dat", "wb");
	FILE* OUT = fopen("output.dat", "wb");
	if (READ == NULL || VLC == NULL || OUT == NULL) {
		printf("file wouldn't open");
		return 0;
	}

	Code* CODE = NULL;// linked list for VLC
	Queue l1;
	Node* l2 = (Node*)malloc(sizeof(Node));
	int x = 0;
	int i = 0;
	int j = 0;
	char c;
	char strND[256] = {};
	char strFULL[SIZE] = {};
	while ((c = fgetc(READ)) != EOF) {
		if (ifExist(strND, c)) {
			strND[i] = c;
			i++;
		}
		strFULL[j] = c;
		j++;

		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->value = c;
		tmp->left = NULL;
		tmp->right = NULL;
		enqueue(&l1, tmp);
		free(tmp);
		x++;
	}
	while (l1.base->freq != x) {

		l2 = hufftree(&l1);
		enqueue(&l1, l2);
	}
	char a;
	for (int i = 0; i < strlen(strND); i++) {   //codes.dat and liked list

		a = strND[i];
		Node* tmp = NULL;

		tmp = findNode(l2, a);

		char arr[100] = {};

		VairiableLenghtCode(tmp, arr);//but we have to reverse it
		reverse(arr);
		CODE = insertLast1(CODE, a, arr);// linked list with VLC


		char arr2[100] = {};
		arr2[0] = a;
		for (int i = 0; i < strlen(arr); i++)// to put the letter beside the codes
			arr2[i + 1] = arr[i];
		fputs(arr2, VLC);
		fputc('?', VLC);// To know when to stop while decompressing

	}
	
	char w;
	char tmper[50];// string to get the code of every char
	int counter1 = 0;

	char str8[10] = {}; // string to hold 8 binary number
	char strFC[SIZE] = {}; // string hold the input string but 0s and 1s
	for (int i = 0; i < strlen(strFULL); i++) {
		w = strFULL[i];
		getcode(CODE, w, tmper); // get the code of every character of the input file from the linked list CODE
		strcat(strFC, tmper); // build the string hold the input string but 0s and 1s
	}
	int o = 0;// counter to the string of 0s and 1s
	int l = 0;//counter for the output string
	int k = 0;// counter for the sting that hold the 8 binary number
	int count = 0; // counter to count the reminder after

	for (int i = 7; i <= strlen(strFC); i = i + 8) { // loop to check that there's no reminder
		for (o = i - 7; o <= i; o++) { // loop to take every 8 number
			str8[k] = strFC[o];
			k++;

		}
		k = 0;
		w = FromBtoChar(str8); // the char that = 8 binary number
		fputc(w, OUT);
		counter1++;
	
	}

	int reminder = 0;
	
	if (strFC[o] != '\0') {
		while (strFC[o] != '\0')
		{
			str8[k] = strFC[o];
			o++;
			k++;
			count++;
		}
		reminder = 8 - count;
		if (reminder == 8)// if there is no reminder (8=0)
			reminder = 0;
		while (k < 8) {
			str8[k] = '0';
			k++;
		}

		
		w = FromBtoChar(str8);
		fputc(w, OUT);
		counter1++;
	}
	
	float ratio = ((float)strlen(strFULL) / counter1) ;
	printf("the ratio of compression = (input/output) = %f ", ratio);
	FILE* REMINDER = fopen("reminder.txt", "w");
	fputc(reminder + '0', REMINDER);

	fclose(READ);
	fclose(VLC);
	fclose(OUT);
	fclose(REMINDER);

	///////////////////////////////////////////////////////////////////////
	//DECOMPRESSION

	FILE* OUTB = fopen("output.dat", "rb");
	FILE* codes = fopen("codes.dat", "rb");
	FILE* R = fopen("reminder.txt", "rb");
	FILE* DECOMP = fopen("decompressed.txt", "w");

	j = 0;
	char strCOMPB[SIZE] = {};
	char strCOMP[9] = {};
	char strVLC[SIZE] = {};
	while ((c = fgetc(OUTB)) != EOF) {
		FromCHARtoB(c, strCOMP);
		strcat(strCOMPB, strCOMP);

	}
	j = 0;
	while ((c = fgetc(codes)) != EOF) {

		strVLC[j] = c;
		j++;
	}
	i = 0;
	reminder = fgetc(R) - '0';
	while (i < strlen(strCOMPB) - reminder)
		i++;

	strCOMPB[i] = '\0';
	int v = 0;
	int q = 0;
	char p;
	Code* codeout = NULL;
	while (strVLC[v] != '\0') {
		p = strVLC[v];
		v++;
		char strCode[100] = {};
		while (strVLC[v] != '?') {
			strCode[q] = strVLC[v];
			q++;
			v++;
		}
		codeout = insertLast1(codeout, p, strCode);
		v++;
		q = 0;

	}
	
	char g;
	char strDECOM[SIZE] = {};
	i = 0;
	j = 0;
	k = 0;
	
	while (strCOMPB[i] != '\0') {
		char strDIV[10] = {};
		strDIV[j] = strCOMPB[i];
		while (strCOMPB[i] != '\0' &&getchar(codeout, strDIV) == false) {
			j++;
			i++;
			strDIV[j] = strCOMPB[i];
		}
		g = getchar(codeout, strDIV);
		strDECOM[k] = g;
		k++;
		i++;
		j = 0;


	}

	fputs(strDECOM, DECOMP);
	fclose(DECOMP);




	_getch();
	return 1;
}