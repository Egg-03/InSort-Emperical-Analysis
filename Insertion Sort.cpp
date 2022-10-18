//Made by : Egg-03
//Contributions : Sortboi by Rugino3 , BigDaddy by Rugino3 , csv appends by Rugino3
//Commented out summary.txt implementation. Not needed anymore since summary.csv has been implemented
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream> //https://stackoverflow.com/questions/22190048/how-to-write-the-content-of-an-array-into-a-text-file
#include <chrono> //https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
using namespace std;

//fucking counters
long int incr = 0;
long int decr = 0;
long int assgn = 0;
long int compare = 0;
int function_call = 0;

//main fucking function
void insort (int *Array , int arr_length)
{
	using namespace std::chrono_literals;
	int key;
	int i;
	for(int j=1 ; j<arr_length ;)
	{
		key = Array[j];
	    assgn++;
		i=j-1;
		assgn++;
		decr++;	
	    while (i>=0 && Array[i] > key)
	    {
	      compare++;
		  Array[i+1]=Array[i];
	      assgn++;
	      i=i-1;
	      assgn++;
	      decr++;
		}
	      Array[i+1]= key;
	      assgn++;
	      j++;
	      incr++;
	}    
    ofstream myfile ("2_Sorted_Array.txt");
    if (myfile.is_open())
    {
    	for (int x=0 ; x<arr_length ; x++)
	     {
		   myfile<<Array[x]<<" ";
	     }
	     myfile.close();
	}	
	else cout << "Unable to open file";	
}

int main()
{
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

	srand(time(0));
	int size , option1 , option2 , total_ops;
	string sortboi = "";
	cout<<"Please select your problem size :"<<endl<<"1. 100"<<endl<<"2. 1000"<<endl<<"3. 5000"<<endl<<"4. 10000"<<endl;
	cin>>option1;
	switch(option1)
	{
		case 1:
			size = 100;
			break;
		case 2:
		    size = 1000;
			break;
		case 3:
		    size = 5000;
			break;
		case 4:
		    size = 10000;
			break;
		default:
		cout<<"\nInvalid size.";
		return 0;				
	}
	
	int A[size];
	cout<<"Please select an option : "<<endl<<"1. Sort an Increasing order array"<<endl<<"2. Sort a Decreasing order array"<<endl<<"3. Sort a Randomly generated array"<<endl;
	cin>>option2;
	switch(option2)
	{
		case 1:
			FILE *asc;
			if(option1 == 1)
			asc = fopen("Input_Ascending_100.txt" , "r");
			else if(option1 == 2)
			asc = fopen("Input_Ascending_1000.txt" , "r");
			else if(option1 == 3)
			asc = fopen("Input_Ascending_5000.txt" , "r");
			else if(option1 == 4)
			asc = fopen("Input_Ascending_10000.txt" , "r");
			
			if(asc == NULL)
			{
				perror("Failed ");
				return 1;
			}
			else
			{
				for(int i=0 ; i<size ; i++)
			    {
				 fscanf(asc , "%d" , &A[i]);
			    }
			    fclose(asc);
			}
			sortboi = "(Ascending)" + to_string(size);
			break;
			
		case 2:
			FILE *desc;
			if(option1 == 1)
			desc = fopen("Input_Descending_100.txt" , "r");
			else if(option1 == 2)
			desc = fopen("Input_Descending_1000.txt" , "r");
			else if(option1 == 3)
			desc = fopen("Input_Descending_5000.txt" , "r");
			else if(option1 == 4)
			desc = fopen("Input_Descending_10000.txt" , "r");
			
			if(desc == NULL)
			{
				perror("Failed ");
				return 1;
			}
			else
			{
				for(int i=0 ; i<size ; i++)
			    {
				 fscanf(desc , "%d" , &A[i]);
			    }
			    fclose(desc);
			}
			sortboi = "(Descending)" + to_string(size);
			break;
		
		case 3:
			for(int i=0 ; i<size ; i++)
	        {
		      A[i] = rand()%size;
	        }
	        sortboi = "(Random)" + to_string(size);
	        break;
	    default :
		cout<<"\nIncorrect option";
		return 0;    
	}
	
    ofstream myfile ("1_Unsorted_Array.txt");
    if (myfile.is_open())
    {
    	for (int x=0 ; x<size ; x++)
	     {
		   myfile<<A[x]<<" ";
	     }
	     myfile.close();
	}
	else cout << "Unable to open file.";
	
	auto t1 = high_resolution_clock::now();
	insort(A , size); //function call lol
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms_double = t2 - t1;
	function_call++;
	cout<<endl;
	
	total_ops = incr+decr+assgn+compare+function_call ;
	/*
	ofstream summary ("Summary.txt");
    if (summary.is_open())
    {
    	summary<<"Increments : "<<incr<<endl;
	    summary<<"Decrements : "<<decr<<endl;
	    summary<<"Assignements : "<<assgn<<endl;
	    summary<<"Comparisons : "<<compare<<endl;
	    summary<<"Function Calls : "<<function_call<<endl;
	    summary<<"CPU time elapsed in insort(): "<<ms_double.count()<<" ms"<<endl;
	    summary<<"Total operations : "<<total_ops<<endl;
	    summary<<"\nNOTE : Increment counts for for loops used in printing arrays to files are excluded.";
		cout<<"Files have been generated.";	
	    summary.close();
	}
	else cout << "Unable to open file.";
	*/
	ofstream summary_csv ("Summary.csv" , ios::app);
	if (summary_csv.is_open())
    {
    	summary_csv<<sortboi<<", "<<incr<<", "<<decr<<", "<<assgn<<", "<<compare<<", "<<function_call<<", "<<ms_double.count()<<", "<<total_ops;
    	summary_csv<<endl;
	    summary_csv.close();
	}
	else cout << "Unable to open file.";
	return 0;
}
