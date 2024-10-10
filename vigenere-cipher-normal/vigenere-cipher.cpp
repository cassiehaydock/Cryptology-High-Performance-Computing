#include <bits/stdc++.h>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
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

int main()
{
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

	std::chrono::nanoseconds result;
	string line;

	//read each line from the file
	for(int i = 0; i < length; i++)
	{
        //extract string and key
        string str = words[i];
        string keyword = keys[i];

		//generate keyword as the same length of str
		string key = generateKey(str, keyword);

		//time how long it takes to encrypt and decrypt str
		auto start = std::chrono::high_resolution_clock::now();
		string cipher_text = encrypt(str, key);
		string original_text = decrypt(cipher_text, key);
		auto finish = std::chrono::high_resolution_clock::now();
		//add time to the overall time
		result += std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);

		cout << " \t- Ciphertext: " << cipher_text << " \t- Decoded(original) text: " << original_text << endl;
    }

	cout << "Average time taken to encrypt and decrypt all the strings: " << result.count() / length << " nanoseconds."<< endl;

	return 0;
}
