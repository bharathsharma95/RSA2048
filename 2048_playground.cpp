#include <iostream>
#define AP_INT_MAX_W 4096
#include <ap_int.h>

using namespace std;

ap_uint<2048> temp_arr[20] = {0};
ap_uint<2048> a_arr[20] = {0};
ap_uint<2048> b_arr[20] = {0};
ap_uint<2048> x_arr[20] = {0};
ap_uint<2048> y_arr[20] = {0};

int test();

ap_uint<2048> modinv(ap_uint<2048> a, ap_uint<2048> m);
ap_uint<2048> modexp(ap_uint<2048> base, ap_uint<2048> exp, ap_uint<2048> n_modulus);

int test()
{
	ap_uint<1024> p = "203956878356401977405765866929034577280193993314348263094772646453283062722701277632936616063144088173312372882677123879538709400158306567338328279154499698366071906766440037074217117805690872792848149112022286332144876183376326512083574821647933992961249917319836219304274280243803104015000563790123";
	ap_uint<1024> q = "531872289054204184185084734375133399408303613982130856645299464930952178606045848877129147820387996428175564228204785846141207532462936339834139412401975338705794646595487324365194792822189473092273993580587964571659678084484152603881094176995594813302284232006001752128168901293560051833646881436219";

	cout<< "p is:" << p << "\n";
	cout<< "q is:" << q << "\n";

	ap_uint<2048> n = p * q;							//n
	cout << "n is: " << n << "\n";

	ap_uint<1024> p_1 = p-1;
	ap_uint<1024> q_1 = q-1;

	ap_uint<2048> phi_n = p_1 * q_1;					//phi_n
	cout << "phi_n is: " << phi_n << "\n";

	ap_uint<2048> e = 65521;							//e
	cout << "e is: " << e << "\n";

	ap_uint<2048> m = 65;								//m
	cout << "m is: " << m << "\n";


	cout << "\n****************************************************************************\n";
	ap_uint<2048> d = modinv(e,phi_n);					//d
	cout << "d is: " << d << "\n";
	cout << "****************************************************************************\n";


	ap_uint<2048> C = modexp(m,e,n);					//Cipher  = m^e mod n
	cout << "C is: " << C << "\n";


	ap_uint<1024> M = modexp(C,d,n);					//Message = C^d mod n
	cout << "M is: " << M << "\n";

	cout << "\n\n";

	return 0;
}



ap_uint<2048> modinv(ap_uint<2048>a, ap_uint<2048>b)
{

	ap_uint<16> count = 0;
	ap_uint<2048> temp = 0;
	//cout<< "\n******************************************\n\n";

	a_arr[count] = a;
	b_arr[count] = b;
	//ap_uint<2048> b_0 = b;
	//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
	//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";
	//count++;


	while(a!=0)
	{
		temp = a;
		temp_arr[count] = temp;

		a = b%a;
		a_arr[count+1] = a;

		b = temp;
		b_arr[count+1] = b;

		//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
		//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";
		count++;
	}

	//b_arr[0] = b_0;
	//cout << "here b_arr[0] : " << b_arr[0] << "\n\n";

	//count is 13 until now

	// when a == 0; setting values of pointers '*x = 0' and '*y = 1'

	ap_uint<2048> gcd = b;
	cout << "returning b_arr[" << count << "] as gcd : " << gcd << "\n";

	x_arr[count] = 0; y_arr[count] = 1;

	cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";
	cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
	cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
	cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";


	count--;
	//cout << "after count-- , count is : " << count << "\n\n";


	// updating the values of pointers x & y from recursive calls (from while loop)

		while(count!=0)
		{

			ap_uint<2048> b_arr_temp = b_arr[count];
			ap_uint<2048> a_arr_temp = a_arr[count];

			ap_uint<2048> X_arr_count_plus1;
			ap_uint<2048> Y_arr_count_plus1;
			X_arr_count_plus1 = x_arr[count+1];
			Y_arr_count_plus1 = y_arr[count+1];

				//calculating *x= y1 - ((b/a) * x1);
				ap_uint<2048> X_arr_count_temp;
				ap_uint<2048> helper1 = (b_arr_temp/a_arr_temp);
				ap_uint<2048> helper2 = (helper1 * X_arr_count_plus1);
				X_arr_count_temp = Y_arr_count_plus1 - helper2;

					x_arr[count] = X_arr_count_temp;
					cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";

					//calculating *y=x1
				ap_uint<2048> Y_arr_count_temp;
				Y_arr_count_temp = x_arr[count+1];

					y_arr[count] = Y_arr_count_temp;
					cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
					cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
					cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";

			count--;
		}



	// When count == 0  --> START

			ap_uint<2048> b_arr_temp = b_arr[count];
			ap_uint<2048> a_arr_temp = a_arr[count];

			ap_uint<2048> X_arr_count_plus1;
			ap_uint<2048> Y_arr_count_plus1;

			X_arr_count_plus1 = x_arr[count+1];
			Y_arr_count_plus1 = y_arr[count+1];


				ap_uint<2048> X_arr_count_temp;
				ap_uint<2048> helper1 = (b_arr_temp/a_arr_temp);
				ap_uint<2048> helper2 = (helper1 * X_arr_count_plus1);
				X_arr_count_temp = Y_arr_count_plus1 - helper2;

					x_arr[count] = X_arr_count_temp;
					cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";

				ap_uint<2048> Y_arr_count_temp;
				Y_arr_count_temp = x_arr[count+1];

					y_arr[count] = Y_arr_count_temp;
					cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
					cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
					cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";


	// when count == 0 --> END




		ap_uint<2048> res;
		if (gcd != 1)
		        cout << "Inverse doesn't exist\n\n\n";
	    else
	    {
	        // phi_n is added to handle negative x
	    	ap_uint<2048> phi_n = "108479011759769393727176308457457051185868202028229648190667018102389154815514421272511788818630907941383004277918921724359698326811100798212287777156373854025160462416970207713010402684330377900249272920821196418994434689542195444008546643909734553918562196237000260811736016995830450094506601223180147858950956587456142088984506552341531162604414254688475101937100559489682831333211096112168725062086504041204843134019133603758846576614652942033865449245668774162405791562411624527881923723225419272555390469703102501835262272692412213406592437962333835647493323944496886794067260314259844881438596";
	    	ap_uint<2048> x_arr_temp = x_arr[count];
	    	//cout << "x_arr_temp : " << x_arr_temp << "\n";
	    	//cout << "phi_n : " << phi_n << "\n";
	    	//ap_uint<2048> helper1 = x_arr_temp % phi_n;
	    	//ap_uint<2048> helper2 = ((x_arr_temp % phi_n) + phi_n);

	        res = ((x_arr_temp % phi_n) + phi_n) % phi_n;
	        //cout << "Modular multiplicative inverse is " << res <<"\n\n\n";
	    }


		return res;
}



ap_uint<2048> modexp(ap_uint<2048> base, ap_uint<2048> exp, ap_uint<2048> n_modulus)
{
	ap_uint<2048> Res = 1;
	    while (exp > 0)
	    {
	        if (exp % 2 == 1)
	        	{
	            	Res = (Res * base) % n_modulus;
	        	}
	        exp = exp >> 1;
	        base = (base * base) % n_modulus;
	    }

	return Res;
}

