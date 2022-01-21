#include <stdio.h>
#include <stdlib.h>

int enqueue();
void dequeue();
void list_node();
void gredPoint();
void calculatePointer();
void sortingList();
void linearSearch();

struct coursework
{
    int subjectNum;
    char subjectName [20][10];
    int creditHour[10];
    int gred[10];
    float gredPoint[10];
    float lastGredPoint;
    int lastCredit;
};

struct student
{
    char name[20];
    int stdID;
    float cgpa;
    float cpa;
    struct coursework coursework_detail;
    struct student *link;
};

struct student *newptr, *tempQ, *frontQ, *rearQ;

int main()
{
    char ch;
	int choice=1;
	frontQ=NULL;

	while(choice==1)
	{	printf("\n\n[-----------Menu-----------]");
		printf("\nA - Add Student Detail");
		printf("\nB - Delete Student Detail");
		printf("\nD - Display Student Detail");
		printf("\nS - Display Sorting Student Detail");
		printf("\nF - Search student data");
		printf("\nX - Exit\n");
		printf("\nEnter choice: ");
		scanf(" %c",&ch);
		ch=toupper(ch);

		switch(ch)
		{
		case 'A':enqueue();break;
		case 'B':dequeue();break;
		case 'D':list_node();break;
		case 'S':sortingList();break;
		case 'F':linearSearch();break;
		case 'X': choice=0; break;
		default: printf("\nOnly one of the above");


		}
	}
   getch();



    return 0;
}

int enqueue()
{
    printf("\n---------GRED-------------");
    printf("\n 1 - A  | 2 - A- | 3 - B+");
    printf("\n 4 - B  | 5 - B- | 6 - C+");
    printf("\n 7 - C  | 8 - C- | 9 - D+");
    printf("\n 10 - D | 11 - E | 12 - F \n");
    printf("--------------------------");

    int i;
    int choose;
    float totalGred;
    int totalcredit;

    printf("\n---------Choose----------- \n");
    printf(" (1 - input from file) \n");
    printf(" (2 - insert information manually) \n");


    printf("Insert choose number: ");
    scanf("%d", &choose);

    newptr=(struct student*)malloc(sizeof(struct student));

    if(choose==1)
    {
        FILE *input; // file declaration
        input = fopen("data2.txt", "r"); // opening the data.txt


        if(input == NULL)
        {
            printf("Error opening file");
            //exit(1);
        }
        else
        {

            fscanf(input,"%d", &newptr->coursework_detail.subjectNum);
            fscanf(input,"%s", &newptr->name);
            fscanf(input,"%d", &newptr->stdID);

            for(i=0; i<newptr->coursework_detail.subjectNum; i++)
            {
                fscanf(input,"%s", &newptr->coursework_detail.subjectName[i]);
                fscanf(input,"%d", &newptr->coursework_detail.gred[i]);
                fscanf(input,"%d", &newptr->coursework_detail.creditHour[i]);
            }

            fscanf(input,"%f", &newptr->coursework_detail.lastGredPoint);
            fscanf(input,"%d", &newptr->coursework_detail.lastCredit);

        }
        fclose(input);
    }
    else if(choose==2)
    {
        FILE *input2; // file declaration
        input2 = fopen("data1.txt", "r"); // opening the data.txt


        if(input2 == NULL)
        {
            printf("Error opening file");
            //exit(1);
        }
        else
        {
            fscanf(input2,"%f", &newptr->coursework_detail.lastGredPoint);
            fscanf(input2,"%d", &newptr->coursework_detail.lastCredit);
        }
        fclose(input2);

        totalcredit=newptr->coursework_detail.lastCredit;
        totalGred=newptr->coursework_detail.lastGredPoint;

        printf("\n %.2f", totalGred);
        printf(" \n %d \n", totalcredit);

        printf("Number of subject (max subject 10) : ");
        scanf("%d", &newptr->coursework_detail.subjectNum);
        printf("Student Name : ");
        scanf("%s", &newptr->name);
        printf("Student ID : CC ");
        scanf("%d", &newptr->stdID);

        for(i=0; i<newptr->coursework_detail.subjectNum; i++)
        {
            printf("Subject Name : ");
            scanf("%s", &newptr->coursework_detail.subjectName[i]);
            printf("Gred : ");
            scanf("%d", &newptr->coursework_detail.gred[i]);
            printf("Subject Credit : ");
            scanf("%d", &newptr->coursework_detail.creditHour[i]);
        }
    }
    newptr->link=NULL;

    if(frontQ==NULL)
    {
        frontQ=newptr;
        rearQ=newptr;
    }
    else
    {
        rearQ->link=newptr;
        rearQ=newptr;
    }

    gradePoint();

    calculatePointer();


}

void gradePoint()
{
    int i;
    int grade;
    tempQ=frontQ;
    while(tempQ != NULL)
    {
        for(i=0; i<tempQ->coursework_detail.subjectNum; i++)
        {
            grade=tempQ->coursework_detail.gred[i];

            switch(grade)
            {
                case 1:tempQ->coursework_detail.gredPoint[i]=4.00;break;
                case 2:tempQ->coursework_detail.gredPoint[i]=3.67;break;
                case 3:tempQ->coursework_detail.gredPoint[i]=3.33;break;
                case 4:tempQ->coursework_detail.gredPoint[i]=3.00;break;
                case 5:tempQ->coursework_detail.gredPoint[i]=2.67;break;
                case 6:tempQ->coursework_detail.gredPoint[i]=2.33;break;
                case 7:tempQ->coursework_detail.gredPoint[i]=2.0;break;
                case 8:tempQ->coursework_detail.gredPoint[i]=1.67;break;
                case 9:tempQ->coursework_detail.gredPoint[i]=1.33;break;
                case 10:tempQ->coursework_detail.gredPoint[i]=1.00;break;
                case 11:tempQ->coursework_detail.gredPoint[i]=0.67;break;
                case 12:tempQ->coursework_detail.gredPoint[i]=0.00;break;
            }

        }
        tempQ=tempQ->link;
    }


}

void calculatePointer()
{
    tempQ=frontQ;
    int i;
    int finalCredit;
    float finalPointer;
    float cpa;
    int totalCredit=0;
    int credit[10];
    float pointer[10];
    float totalpointer=0;
    float cgpa;

    while(tempQ != NULL)
    {

        for(i=0; i<tempQ->coursework_detail.subjectNum; i++)
        {
            credit[i]=tempQ->coursework_detail.creditHour[i];
            totalCredit+=credit[i];
        }

        for(i=0; i<tempQ->coursework_detail.subjectNum; i++)
        {
            pointer[i]=(tempQ->coursework_detail.gredPoint[i])*(tempQ->coursework_detail.creditHour[i]);
            totalpointer+=pointer[i];
        }

        cgpa=totalpointer/totalCredit;
        tempQ->cgpa=cgpa;

        finalCredit=totalCredit+(tempQ->coursework_detail.lastCredit);
        finalPointer=totalpointer+(tempQ->coursework_detail.lastGredPoint);
        cpa=finalPointer/finalCredit;
        tempQ->cpa=cpa;

        tempQ=tempQ->link;
        totalCredit=0;
        totalpointer=0;

    }

}

void dequeue()
{
    char choose[3];
    tempQ=frontQ;

    if(frontQ==NULL)
    {
        printf("\n\t\tThere is no data in the system\n");
    }
    else
    {

        frontQ=frontQ->link;
        free(tempQ);
        printf("\n Your Data has been deleted \n");
        list_node();

    }

}

void list_node()
{
    int i;
    tempQ=frontQ;

    if(tempQ==NULL)
    {
        printf("\nThe list is empty\n");
    }
    else
    {
        printf("\n---------------------------------------------\n");
        printf("\n                SEM 4 RESULTS                \n");
        printf("\n---------------------------------------------\n");

        while(tempQ!=NULL)
        {
            printf("\n---------------------------------------------\n");
            printf("Student Name: %s \n", tempQ->name);
            printf("Matric ID: CC %d \n", tempQ->stdID);
            printf("\n Subject Name Grade Credit Hour Grade Point\n");
            for(i=0; i<tempQ->coursework_detail.subjectNum; i++)
            {
                printf("  %s          %d        %d         %.2f \n", tempQ->coursework_detail.subjectName[i], tempQ->coursework_detail.gred[i], tempQ->coursework_detail.creditHour[i], tempQ->coursework_detail.gredPoint[i]);
            }
            printf("\n   CGPA: %.2f                      CPA: %.2f", tempQ->cgpa, tempQ->cpa);
            printf("\n---------------------------------------------\n");
            tempQ=tempQ->link;
        }

        printf("\n Total Students in List : %d", getCount(frontQ));
    }

}

int getCount(struct student* frontQ)
{
    if (frontQ==NULL)
        return 0;
    else
        return 1 + getCount(frontQ->link);
}

void swapNodes(struct student** head_ref, struct student* currX,
			struct student* currY, struct student* prevY)
{
	// make 'currY' as new head
	*head_ref = currY;

	// adjust links
	prevY->link = currX;

	// Swap next pointers
	struct student* temp = currY->link;
	currY->link = currX->link;
	currX->link = temp;
}

// function to sort the linked list using
// recursive selection sort technique
struct student* recurSelectionSort(struct student* frontQ)
{
	// if there is only a single node
	if (frontQ->link == NULL)
		return frontQ;

	// 'max' - pointer to store the node having
	// maximum data value
	struct student* max = frontQ;

	// 'beforeMax' - pointer to store node previous
	// to 'max' node
	struct student* beforeMax = NULL;
	struct student* ptr;

	// traverse the list till the last node
	for (ptr = frontQ; ptr->link != NULL; ptr = ptr->link) {

		// if true, then update 'max' and 'beforeMax'
		if (ptr->link->cpa > max->cpa) {
			max = ptr->link;
			beforeMax = ptr;
		}
	}

	// if 'max' and 'head' are not same,
	// swap the head node with the 'max' node
	if (max != frontQ)
		swapNodes(&frontQ, frontQ, max, beforeMax);

	// recursively sort the remaining list
	frontQ->link = recurSelectionSort(frontQ->link);

	return frontQ;
}

// function to sort the given linked list
void sort(struct student** head_ref)
{
	// if list is empty
	if ((*head_ref) == NULL)
		return;

	// sort the list using recursive selection
	// sort technique
	*head_ref = recurSelectionSort(*head_ref);
}

// function to print the linked list
void printList(struct student* frontQ)
{

	while (frontQ != NULL)
    {
        printf("\n Student ID: CC %d ", frontQ->stdID);
        printf("\n Student CGPA: %.2f ", frontQ->cgpa);
        printf("\n Student CPA: %.2f \n", frontQ->cpa);

        frontQ=frontQ->link;


        //printf("\n Total Students in List : %d", getCount(frontQ));

	}
}

void sortingList()
{
    sort(&frontQ);
    printList(frontQ);
}

void linearSearch()
{
    int i;
    int searchID;
    tempQ=frontQ;

    printf("Enter student ID: CC ");
    scanf("%d", &searchID);

    while(tempQ != NULL)
    {
        if(tempQ->stdID == searchID)
        {
            printf("\n---------------------------------------------\n");
            printf("Student Name: %s \n", tempQ->name);
            printf("Matric ID: CC %d \n", tempQ->stdID);
            printf("\n Subject Name Grade Credit Hour Grade Point\n");
            for(i=0; i<tempQ->coursework_detail.subjectNum; i++)
            {
                printf("  %s          %d        %d         %.2f \n", tempQ->coursework_detail.subjectName[i], tempQ->coursework_detail.gred[i], tempQ->coursework_detail.creditHour[i], tempQ->coursework_detail.gredPoint[i]);
            }
            printf("\n                                  CGPA: %.2f", tempQ->cgpa);
            printf("\n---------------------------------------------\n");

            return;
        }
        tempQ=tempQ->link;
    }
    printf("\nStudent ID that you enter is not in the system\n");
}





