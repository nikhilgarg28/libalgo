/**
* Team Proof
* Trie
*
* In general available is boolean array and insert, search are implemented
* Search returns 'null' if not found
*/

import java.io.*;
import java.util.*;
import java.math.*;

class node
{
	node parent;	
	node [] nxt;
	int available;
	int subt;	//number of nodes in the subtrie
	boolean terminal;
	
	node ()
	{
		nxt = new node[26];
		available = 0;
		subt = 0;
		terminal = false;
	}
}

class Trie
{
	node root;
	
	Trie()
	{
		root = new node();
	}
	
	void insert(String inp)
	{
		node curr = root;
		for(int i =0, l = inp.length(); i < l; i++)
		{
			if((curr.available & (1<<(inp.charAt(i)-'a'))) == 0)
			{
				node tmp = new node();
				tmp.parent = curr;
				curr.available += (1<<(inp.charAt(i)-'a'));
				curr.nxt[inp.charAt(i)-'a'] = tmp;
			}
			curr = curr.nxt[inp.charAt(i)-'a'];
			curr.subt++;
		}
		curr.terminal = true;
	}
	
	node search(String pref)
	{
		node curr = root;
		for(int i = 0, l = pref.length(); i < l; i++)
		{
			if((curr.available & (1<<(pref.charAt(i) - 'a'))) == 0)
			{
				return null;
			}
			curr = curr.nxt[pref.charAt(i)-'a'];
		}
		return curr;
	}
}
