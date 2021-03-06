// AUTHOR alexander.oleinik alxndr@bu.edu
// single_parts
#include <iostream>
#include <iomanip>

using namespace std;


typedef unsigned int raw32; 


struct Single_Parts {
	raw32 fraction : 23;
	raw32 exponent : 8;
	raw32 sign : 1;
};

const raw32 MASK_SIGN = 1U << 31;
const raw32 MASK_BEXP = 0xffU << 23;
const raw32 MASK_FRAC = 0x7fffffU;
// print out the parts of the structure Single_Parts
void print_sp(Single_Parts sp) 
{ 
  if (sp.sign==1)
		 cout << "negative"  << endl;
  else 
  		cout << "positive" << endl;

 cout << hex  
      << setfill('0') 
      << "expo: " << sp.exponent << endl
      << "frac: " << sp.fraction << endl
      << dec;
}

Single_Parts take_apart(float d)
{
	Single_Parts sp;
	raw32 x = *reinterpret_cast<raw32*>(&d);
	sp.sign = (x & MASK_SIGN) >> 31;
	sp.exponent = (x & MASK_BEXP) >> 23;
	sp.fraction = (x & MASK_FRAC);
	return sp;
}

float build(Single_Parts sp)
{
	return *reinterpret_cast<float*>(&sp);
}

// define Single_Parts, build(), and take_apart() for float
int main()
{
        int EXAMPLES = 5;
	float num_from_build;

	float numbers[EXAMPLES]={1.0/3,2,1.3e10,3e11,6};
	
	// show the structure of the numbers 
	for (int i=0;i<EXAMPLES;i++)
	{   
		// take apart the numbers, then re-build to test that it works.
		
		Single_Parts s = take_apart(numbers[i]);
	 	num_from_build = build(s);

	 	cout << endl;
	    print_sp(s);
	 	cout << numbers[i] << " " << num_from_build  << endl;
	}

    // example of a weird number, negative zero.
    double neg_zero{-0.0};

    cout << endl; 
    cout << neg_zero << endl;

    print_sp(take_apart(neg_zero));

    return 0;
}
