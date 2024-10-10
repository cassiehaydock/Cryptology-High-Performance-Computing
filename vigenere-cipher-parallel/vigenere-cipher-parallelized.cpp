#include <bits/stdc++.h>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <mpi.h>
using namespace std;

#define TRUE 0
#define FALSE 1

// This function generates the key until it's length is equal to the length of original text
string generateKey(string str, string key)
{
	int shorter = (str.size() < key.size()) ? TRUE : FALSE;
	int x = str.size();

	int i = 0;

	//while the key size is still not the same length as the string
	while(key.size() != str.size())
	{
		//if the key is longer than the str remove character from key until its the same length
		if(shorter == TRUE){
			key.pop_back();
		}
		//else if key is shorter, circulalry add characters
		else{
			key.push_back(key[i]);
			i++;
		}
	}

	return key;
}

// This function returns the encrypted text generated with the help of the key
string encrypt(string str, string key)
{
	string cipher_text;

	for (int i = 0; i < str.size(); i++)
	{
		// converting in range 0-25
		char x = (str[i] + key[i]) %26;

		// convert into alphabets(ASCII)
		x += 'A';

		cipher_text.push_back(x);
	}
	return cipher_text;
}

// This function decrypts the encrypted text and returns the original text
string decrypt(string cipher_text, string key)
{
	string orig_text;

	for (int i = 0 ; i < cipher_text.size(); i++)
	{
		// converting in range 0-25
		char x = (cipher_text[i] - key[i] + 26) %26;

		// convert into alphabets(ASCII)
		x += 'A';
		orig_text.push_back(x);
	}
	return orig_text;
}

int main(int argc, char *argv[]) {
	//initliaze environment
    MPI_Init(&argc, &argv);

    int rank, size;
	//get process ID
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	//print number of processes only in main process
	if(rank == 0){
		cout << "Number of processes: " << size << endl;
	}

	//how many string-key pairs
    int length = 51;
    string words[length] = {"CASSANDRAHAYDOCK", "AMBERWLEBY", "MATTHEWBROWN", "ALEXANDERBOUDREAU", "WILLIAMVANLEEWUN", "TREVORHILL", "SAMUELBARNETT", "ALLENKIM", "PRISCAONYEBUCHI", 
	"CAMRYNMOERCHEN", "THOMASRICKUS", "MARIAHJOHNSON", "KEIARACLARKE", "SEANROSE", "MARTINHO",
	"LOEMIPSUMIDKTHERESTIMJUSTTRYINGTOMAKEABIGSTRINGLOL", "HOWDYDOODAMIAMIGO", "INEEDANOTHERBIGSTRINGFORTESTINGPURPOSESDONTMINDMEJUSTTRYPINGMYTHOUGHTS",
	"DOIKNOWANYSONGLYRICS", "THEONLYSONGLRYICSICANTHINKOFRIGHTNOWAREOLDGENZSONGSLIKEPARTYINTHEUSA", "ANDIPUTMYHANDSUPTHEIRPLAYINGMYSONGANDTHEBUTTERFLIESFLYAWAY",
	"NODDINGMYHEADLIKEYEAHMOVINGMYHIPSLIKYEAH", "HEREARESOMEENGLISHSENTENCESWRITTENINALLCAPSWITHNOSPACES",
	"HELLOHOWAREYOUDOINGTODAYWHATAREYOUPROGRAMMINGON", "WHATSTHEWEATHERLIKETOMORROW", "HAVEYOUEVERBEENTOFRANCEIWOULDLIKETOVISITTHEREONEDAY", "WHATDOYOUWANTTOEATFORLUNCH",
	"HERESOMUCHFOODINTHEFRIDGEIMNOTSUREWHATTOCHOOSE", "LETSGOFORAPIZZAISTHATABADIDEA", "WHATBOOKAREYOUCURRENTLYREADING", "IFYOUHAVEANYBOOKSUGGESTIONSLETMEKNOW",
    "SOMEADDITIONALRANDOMTEXTTOFILLINSPACE", "ANOTHERRANDOMSTRINGTOADD", "ONEMORESTRINGBECAUSEWHYNOT", "YETANOTHERSTRINGFORVARIETY",
    "FIFTYENTRIESISSOMUCHFUN", "ALMOSTTHEREJUSTAFEWMORE", "MOREANDMORESTRINGSEVERYWHERE", "CANNEVERHAVETOOMANYSTRINGS",
    "STILLGOINGSTRONGWITHSTRINGS", "KEEPADDINGSTRINGSTILLWEREACH50", "ITSSIMPLYSTRINGSTASTIC", "FINALLYREACHEDHALFOFHUNDREDSTRINGS",
    "SOHAPPYTOREACHTHE50MARK", "STRINGSSTRINGSANDMORESTRINGS", "WHATSHOULDWECALLTHISSTRINGFEST", "THANKFULFORALLTHESESTRINGS",
    "WOW50STRINGSSUREISA LOT", "IMRUNNINGOUTOFSTRINGIDEAS", "MAYBESOMETHINGRANDOM", "DONEANDDUSTEDWITH50STRINGS"
	};

    string keys[length] = {"QSJION", "DNEINSRH", "NCOE", "ANUR", "ANCIP", "CNSUETR", "DKCOJRFI", "EMFJ", 
    "AJHHU", "CBNORWA", "AMODTE", "CVHR", "COBRUSMRLKWE", "VNAUTO", "NWJO",
    "AIDNRINOSN", "NADI", "NWOFIRHNJDOESNWO", "WJDOEJAOWWDDV", "BROEDUWJ", "ANNCIRMSWJEIFNWJS",
    "XCMKLJ", "DNEOIFR", "MVIEHND", "WIEORU", "DJCNEO", "XJKLOE", "QOEFN", "KDNERU",
    "LOEJR", "SJDNFO", "POERUBAU", "ZXJCN", "MVKDN", "QWIEU", "RPOWIE", "DNVKJ",
    "CNEOIR", "WIEHR", "CJNVE", "POWIEU", "PWOEIRAKOEMDOE", "AJFNE", "IEOWR", "POQIE",
    "RPOEJ", "MPOWE", "VJKDNTSAWO"};

    chrono::nanoseconds result(0);

    //distribute work among processes
    int chunk_size = length / size;
	int remainder = length % size;
    int start_index = rank * chunk_size;
	int end_index = start_index + chunk_size + (rank == size - 1 ? remainder : 0);

    for (int i = start_index; i < end_index; i++) 
	{
		//extract string and key
        string str = words[i];
        string keyword = keys[i];

		//generate keyword as the same length of str
        string key = generateKey(str, keyword);

		//time how long it takes to encrypt and decrypt str
        auto start = chrono::high_resolution_clock::now();
        string cipher_text = encrypt(str, key);
        string original_text = decrypt(cipher_text, key);
        auto finish = chrono::high_resolution_clock::now();

		//add time to overall time for that process
        result += chrono::duration_cast<chrono::nanoseconds>(finish - start);

        cout << "Process " << rank << " \t- Ciphertext: " << cipher_text << " \t- Decoded(original) text: " << original_text << endl;
    }

	MPI_Barrier(MPI_COMM_WORLD);

    // Gather results
    chrono::nanoseconds total_time(0);
    MPI_Reduce(&result, &total_time, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Average time taken to encrypt and decrypt all the strings: " << total_time.count() / length << " nanoseconds." << endl;
    }

    MPI_Finalize();

    return 0;
}
