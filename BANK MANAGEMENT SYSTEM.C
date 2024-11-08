#include<stdio.h>
#include<conio.h>
#include<process.h>
void addcust();
void withd();
void deposit();
void disarec();
void prnlowbal();
void trandet();
void accdet();


struct cust_st
{
	int acc_no;
	char cust_nm[30];
	char f_nm[30];
	char gen;
	int bal;
};
struct tran_st
{
	int acc_no;
	char trantype;
	int amt;
};
int main()
{
	
	int choice=1;
	while(choice!=8)
	{
	
		printf("\nSelect choice from menu.\n\n 1. Accept client details.\n\n 2. Withdrawl Amount. \n\n 3.Deposit Amount.\n\n 4.Display All Record\n\n 5.Print Low Balance Report.\n\n 6.Transaction Details.\n\n 7.Account Details.\n\n 8.Exit\n\nEnter choice: ");
		scanf("%d",&choice);
		if(choice==1)
		addcust();
		else if(choice==2)
		withd();
		else if(choice==3)
		deposit();
		else if(choice==4)
		disarec();
		else if(choice==5)
		prnlowbal();
		else if(choice==6)
		trandet();
		else if(choice==7)
		accdet();
		
	}
return 0;
}
void addcust()
{
	FILE *fp;
	char flag='y';
	struct cust_st custdata;
	if((fp=fopen("dipali","a+"))==NULL)
	{
		printf("\nError opening client file");
		return;
	}
	while(flag=='y')
	{
		printf("\n\nEnter Account Number: ");
		scanf("%d",&custdata.acc_no);
		fflush(stdin);
		printf("\n\nEnter Client Name: ");
		scanf("%s",&custdata.cust_nm);
		fflush(stdin);
		printf("\n\nEnter Father's' Name: ");
		scanf("%s",&custdata.f_nm);
		fflush(stdin);
		printf("\n\nGender: ");
		scanf("%c",&custdata.gen);
		fflush(stdin);
		printf("\n\nEnter Account Balance: ");
		scanf("%d",&custdata.bal);
		fflush(stdin);
		fwrite(&custdata,sizeof(struct cust_st),1,fp);
		fflush(stdin);
		printf("\n\nAdd another? (y/n): ");
		scanf("%c",&flag);
    }
		fclose(fp);
}
   void withd()
    {
	FILE *fp1,*fp2;
	char flag='y',found,val_flag;
	struct cust_st custdata;
	struct tran_st trandata;
	int size=sizeof(struct cust_st);
	if((fp1=fopen("dipali","r+w"))==NULL)
	{
		printf("\nError opening  client file");
		return;
			}			
    if((fp2=fopen("trans","a+"))==NULL)
    {
	printf("\nError opening transaction file");
	return;
    }
    while(flag=='y')
    {
    int accno=0;
	printf("\nEnter Account Number: ");
	scanf("%d",&custdata.acc_no);
	 accno=custdata.acc_no;
	rewind(fp1);
	while((fread(&custdata,sizeof(struct cust_st),1,fp1))==1)
	{
		if(custdata.acc_no==accno)
		{
			found='y';
			printf("\nPrevious Balance : %d",custdata.bal);
			break;
		}
	}
	val_flag='n';
	
	if(found=='y')
	{
		trandata.acc_no=custdata.acc_no;
	trandata.trantype='W';		
			printf("\nEnter amount: ");
			scanf("%d",&trandata.amt);
			if(trandata.amt>custdata.bal)
			printf("\nAccount balance is %.2d.Please reenter Wthdrawl amount.",custdata.bal);
			else
						custdata.bal-=trandata.amt;
				
		fwrite(&trandata,sizeof(struct tran_st),1,fp2);
		fseek(fp1,(long) (-size),1);
		fwrite(&custdata,size,1,fp1);
	}
	else
	printf("\nThis account number does not exist.");
	
	fflush(stdin);
	printf("\nRecord another transaction? (y/n): ");
	scanf("%c",&flag);
	}

    fclose(fp1);
    fclose(fp2);
}

    void deposit()
    {
	FILE *fp1,*fp2;
	char flag='y',found,val_flag;
	struct cust_st custdata;
	struct tran_st trandata;
	int size=sizeof(struct cust_st);
	if((fp1=fopen("dipali","r+w"))==NULL)
	{
		printf("\nError opening  client file");
		return;
			}			
    if((fp2=fopen("trans","a+"))==NULL)
    {
	printf("\nError opening transaction file");
	return;
    }
    while(flag=='y')
    {
    int accno=0;
	printf("\nEnter Account Number: ");
	scanf("%d",&custdata.acc_no);
	 accno=custdata.acc_no;
	rewind(fp1);
	while((fread(&custdata,sizeof(struct cust_st),1,fp1))==1)
	{
		if(custdata.acc_no==accno)
		{
			found='y';
			printf("\nPrevious Balance : %d",custdata.bal);
			break;
		}
	}
	val_flag='n';
	
	if(found=='y')
	{
		trandata.acc_no=custdata.acc_no;
	trandata.trantype='D';		
			printf("\nEnter amount: ");
			scanf("%d",&trandata.amt);
			
			custdata.bal+=trandata.amt;
				
		fwrite(&trandata,sizeof(struct tran_st),1,fp2);
		fseek(fp1,(long) (-size),1);
		fwrite(&custdata,size,1,fp1);
	}
	else
	printf("\nThis account number does not exist.");
	
	fflush(stdin);
	printf("\nRecord another transaction? (y/n): ");
	scanf("%c",&flag);
	}

    fclose(fp1);
    fclose(fp2);
    }
     void disarec()
    {
	FILE *fp;
	struct cust_st custdata;
	if((fp=fopen("dipali","r"))==NULL)
	{
		printf("\n Display All Records: ");
		return;
	}
	int a=0;
	printf("\nReport on account balances\n\n\tSrno\tAcc.no \tName\tBalance\n");
	while((fread(&custdata,sizeof(struct cust_st),1,fp))==1)
	{
	a++;
	
			printf("\n\t%d\t%d\t\t%s\t%.2d",a,custdata.acc_no,custdata.cust_nm,custdata.bal);
}
	
	fclose(fp);
	getch();
    }
     void prnlowbal()
    {
	FILE *fp;
	struct cust_st custdata;
	char flag='n';
	if((fp=fopen("dipali","r"))==NULL)
	{
		printf("\nError opening customer file.");
		return;
	}
	int a=0;
	printf("\nReport on account balances\n\n\tSrno\tAcc.no \tName\tBalance\n");
	while((fread(&custdata,sizeof(struct cust_st),1,fp))==1)
	
	{
	a++;
	
		
			flag='y';
			printf("\n\t%d\t%d\t\t%s\t%.2d",a,custdata.acc_no,custdata.cust_nm,custdata.bal);
		
	}
	
	
	fclose(fp);
	getch();
	
}
     void trandet()
          {
	FILE *fp1;
	char flag;
	//struct cust_st custdata;
	struct tran_st trandata;
	if((fp1=fopen("trans","r"))==NULL)
	{
		printf("\nError opening client file. ");
		return;
	}
	    printf("\nTransaction Details ");
	    int a=0;
	    printf("\n\tSrno.\tAcc.No. \tType\tAmount\n");
	    while((fread(&trandata,sizeof(struct tran_st),1,fp1))==1)
	{
		a++;
		printf("\n\t%d\t%d\t\t%c\t\t%d",a,trandata.acc_no,trandata.trantype,trandata.amt);
	
}
      fflush(stdin);
	printf("\nRecord another transaction? (y/n): ");
	scanf("%c",&flag);

	fclose(fp1);
}



     void accdet()
   {
	FILE *fp1;
	char flag='y',found;
	struct cust_st custdata;
	if((fp1=fopen("dipali","r+w"))==NULL)
	{
			printf("\nError opening  client file");
		return;
	}
	int accno=0;
	printf("\nEnter Account Number: ");
	scanf("%d",&custdata.acc_no);
	 accno=custdata.acc_no; 
	rewind(fp1);
			printf("\nAccount Details: ");
	int a=0;
	
	printf("\n\n\tAcc.no\tName\tFather Name\tgender\tBalance\n");
	while((fread(&custdata,sizeof(struct cust_st),1,fp1))==1)
	{
		if(custdata.acc_no==accno)
		{
			found='y';
	
	printf("\n\n%d\t%s\t%s\t%c\t%.2d",custdata.acc_no,custdata.cust_nm,custdata.f_nm,custdata.gen,custdata.bal);
		
		}
	}

	if(flag=='n') 
	{
	
	
	        printf("\nThis account number does not exist.");
}
	  fclose(fp1);      
	}
