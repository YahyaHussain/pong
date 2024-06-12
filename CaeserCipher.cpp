#include <bits/stdc++.h>

using namespace std;

int main()	{
	cout << "Plain text: ";
	string pt;
	cin >> pt;
	cout << "Key: ";
	int key;
	cin >> key;
	string ct = "";
	for (int i = 0; i < pt.size(); i++)	{
		ct += (((pt[i] - 'a') + key) % 26) + 'a';
	}
	cout << "Cipher: " << ct << endl;
	string r_pt = "";
	for (int i = 0; i < ct.size(); i++)	{
		r_pt += (((ct[i] - 'a') - key + 26) % 26) + 'a';
	}
	cout << "Decrypt: " << r_pt << endl;
}