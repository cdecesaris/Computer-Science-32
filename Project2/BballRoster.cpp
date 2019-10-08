//Christina De Cesaris
#include "BballRoster.h"
#include<iostream>
#include<string>
using namespace std;
BballRoster::Player::Player(string fname, string lname, SomeType val){ //constructor for each new player
	m_fname = fname;
	m_lname = lname;
	m_val = val;
	next = nullptr;
	prev = nullptr;
}
BballRoster:: BballRoster() : head(nullptr), m_size(0){} //defualt constructor

BballRoster::BballRoster(const BballRoster& bbr) : head(nullptr), m_size(0) {//copy constructor 
	Player* m = bbr.head;
	if (m != nullptr) { //if bbr.head is not empty
		m_size = bbr.m_size; // set this.size to bbr.size

		head = new Player(m->m_fname, m->m_lname, m->m_val); //set it's address to a new node, copy over values of bbr.head to that node
		
		m = m->next; //point m to the next node on bbr
	} 
	//
	Player* n = head; //pointer pointing to the new.head
	while (m != nullptr) {
		if (n == head) { //if n points to the first node
			Player* p = new Player(m->m_fname, m->m_lname, m->m_val); //make a new player with address in p, copy information from the current location of m
			
			n->next = p; //link the new head node to p
			p->prev = head; //link new node's prev to head			n->next; // move along
			n=n->next; // move n to point at p's node
			m = m->next; //continue m down the bbr
		}
		else { // n is not pointing to the first node of the new list
			Player* x = new Player(m->m_fname, m->m_lname, m->m_val);
			n->next = x;
			x->prev = n;
			n = n->next;
			m = m->next;



		}
	}

} 

const BballRoster& BballRoster::operator=(const BballRoster& bbr) {
	if (this == &bbr) //ensure we are not assigning something to itself!
		return *this;
	if (!this->rosterEmpty()) { //delete any previous memory contained in this
		for (int i = 0; i < this->howManyPlayers(); i++) {
			string ftemp, ltemp;
			SomeType x;
			this->choosePlayer(i, ftemp, ltemp, x);
			this->renouncePlayer(ftemp,ltemp);
		}
		
	}
	BballRoster temp = bbr; //copy constructor
	swapRoster(temp); //swap pointers
	return *this;
} //assignment operator 

BballRoster::~BballRoster() {
	Player* m = head; //of what we are destroying
	
	while (m != nullptr) {
		Player* toDelete = m;
		m = m->next;
		delete toDelete;
	}


} //destructor

bool BballRoster::rosterEmpty() const {
	if (m_size > 0) {
		return false;
	}
	else {
		return true;
	}
}

int BballRoster::howManyPlayers() const {
	return m_size;
}

bool BballRoster::signPlayer(const std::string& firstName, const std::string&

	lastName, const SomeType& value) {
	//Player* m = head;
	if (head == nullptr) { //empty list //!= changed from == --
		 //placed in side of code --
		Player* added = new Player(firstName, lastName, value);	//--changed/ /here we don't worry about sorting becase it is the first player
		head = added;
		m_size++;

		return true; //work here is done
	}
	//otherwise we must add alpabetically
	Player* m = head;
	while (m != nullptr) {
		Player* p = new Player(firstName, lastName, value);

		
		if (m->m_lname == p->m_lname && m->m_fname == p->m_fname) { //ensure we don't have same last and first names here
			return false;
		}

		if (m->m_lname == p->m_lname) {
			//compare first names and sort accordingly
			//do the first name shibang
			if (head->m_fname > p->m_fname == true) { //means if m->firstname at head is lower aphabetically than the new node, the == true isn't needed just for me visually
				//new node becomes new head, old head is linked after 
				m->prev = p; 
				p->next = m;
				head = p;
				m_size++;
				return true; //we added our player
			}
			if (m->m_fname > p->m_fname == true) {//so is the next guy apha lower than our new guy
				//if yah, then our new guy goes on top of the old guy
				m->prev->next = p; //point the guy before old guy's next to p, has to happen before we change m-> prev its gonna be hell
				p->prev = m->prev;
				m->prev = p; // old guys prev, point to new guy
				p->next = m; //new guy next,  point to old guy
				m_size++;


				return true; //done here
			}
			else { //new guy is alpha lower than the current 
				//before moving along we have to make sure we aren't at the last node because if we are at last node and move along, m will pt at null 
				if (m->next == nullptr) {//new guy is offically at the bottom, link em to the rear!
					m->next = p;
					p->prev = m;
					m_size++;

					return true;

				}
				m = m->next;

			}

		}
		else {
			//compare last names and sort accordinly
			if (head->m_lname > p->m_lname == true) { //means if m->lastname at head is lower aphabetically than the new node, the == true isn't needed
				//new node becomes new head, old head is linked after 
				m->prev = p; 
				p->next = head;
				head = p;
				m_size++;

				return true; //we added our player
			}
			//if we get here, then our head is more apha than our new player 
			//so we must go down the list and compare our new player to all the other guys
			//m = m->next; //on to the next one
			if (m->m_lname > p->m_lname == true ) {//so is the next guy apha lower than our new guy
				//if yah, then our new guy goes on top of the old guy
				m->prev->next = p; //point the guy before old guy's next to p, has to happen before we change m-> prev its gonna be hell
				p->prev = m->prev;
				m->prev = p; // old guys prev, point to new guy
				p->next = m; //new guy next,  point to old guy
				m_size++;

				return true; //done here
			}
			else { //new guy is alpha lower than the current 
				//before moving along we have to make sure we aren't at the last node because if we are at last node and move along, m will pt at null 
				if (m->next == nullptr) {//new guy is offically at the bottom, link em to the rear!
					m->next = p;
					p->prev = m;
					m_size++;

					return true;

				}
				m = m->next;  

			}


		}
		
	}
	 
	
	
	m_size++;

	return true;
}

bool BballRoster::resignPlayer(const std::string& firstName, const std::string&
	lastName, const SomeType& value) {
	if (head == nullptr) {
		return false;
	}
	if (playerOnRoster(firstName, lastName)) {
		Player* m = head;
		while (m != nullptr) {
			if ( m != nullptr && m->m_fname == firstName && m->m_lname == lastName ) {
				m->m_val = value;
			}
			
				m = m->next;

			
		}

		return true;
	}
	else {
		return false;
	}
	
}

bool BballRoster::signOrResign(const std::string& firstName, const std::string&
	lastName, const SomeType& value) {
	
	if (playerOnRoster(firstName, lastName)) { //call resign
		resignPlayer(firstName, lastName, value);
		return true;
	}
	else {
		signPlayer(firstName, lastName, value);
		return true;

	}
}
// If full name is equal to a name currently in the list, then
	// make that full name no longer map to the value it currently
	// maps to, but instead map to the value of the third parameter;
	// return true in this case. If the full name is not equal to
	// any full name currently in the list then add it and return
	// true. In fact, this function always returns true.

bool BballRoster::renouncePlayer(const std::string& firstName, const
	std::string& lastName) {
	if (playerOnRoster(firstName, lastName)) {
		Player* m = head;
		while (m != nullptr) {

			if (m->m_lname == lastName && m->m_fname == firstName) {
				if (m == head ) {
					if (m->next == nullptr) {
						delete m; //one node
						head = nullptr;
					}
					else {
						head = head->next;
						delete m;
						m = nullptr;
					}
					m_size--;
					return true;
				}

				else if (m->next == nullptr) { //this is proabably not needed 
					m->prev->next = nullptr;
					delete m;
					head = nullptr;
					m_size--;
					return true;
				}
				else if (m->next != nullptr) {
					m->next->prev = m->prev;
					m->prev->next = m->next;
					delete m;
					m_size--;
					return true;

				}
			

				

			}
			m = m->next;
		}
		//return false;
		return true;

	}
	else {
		return false;
	}
}

bool BballRoster::playerOnRoster(const std::string& firstName, const
	std::string& lastName) const {
	Player* m = head;
	if (m == nullptr) {
		return false;
	}
	while (m != nullptr) {
		if (m->m_fname == firstName && m->m_lname == lastName) {
			return true;
		}
		m = m->next;
	}
	return false;
}

bool BballRoster::lookupPlayer(const std::string& firstName, const std::string&
	lastName, SomeType& value) const {
	if (playerOnRoster(firstName, lastName)) {
		Player* m = head;
		while (m != nullptr) {
			if (m->m_lname == lastName && m->m_fname == firstName) {
				value = m->m_val;
				return true;
			}
			m = m->next;
		}
		//return false;
	}
	return false;
}


bool BballRoster::choosePlayer(int i, std::string& firstName, std::string&
	lastName, SomeType& value) const {
	if (i < 0 || i > m_size) {
		return false;
	}
	else {
		Player* m = head;
		int count = 0;
		while (count<i && m!= nullptr) {
			m = m->next;
			count++;
		}// bring m to index of i
		if (m != nullptr)
		{
			firstName = m->m_fname;
			lastName = m->m_lname;
			value = m->m_val;
			return true;
		}

		return false;
	}
}

void BballRoster::swapRoster(BballRoster& other) {
	Player* temp = other.head;
	other.head = head;
	head = temp;

	int temp_siz = other.m_size;
	other.m_size = m_size;
	m_size = temp_siz;

}


void BballRoster::dump() const {
	Player* m = head;
	while (m != nullptr ) {
		cerr << m->m_lname << " " << m->m_fname << " " << m->m_val << endl;

		m = m->next;

	}
}
///Non member functions
bool joinRosters(const BballRoster& bbOne,
	const BballRoster& bbTwo,
	BballRoster& bbJoined) {
	bool dupes = false;
	string first, last;
	SomeType val;
	if (&bbOne == &bbJoined ) {
		BballRoster temp;//create an empty new list
		temp = bbJoined;
		joinRosters(bbOne, bbTwo, temp);
		return true;
		//ensure if we pass the same list in both bbjoined and bbone we don't accidentally loose contents
	}
	if (&bbTwo == &bbJoined) {
		BballRoster temp;//create an empty new list
		temp=bbJoined;
		joinRosters(bbOne, bbTwo, temp);
		return true;
		//bbJoined.swapRoster(temp);

		
	}
	if (!bbJoined.rosterEmpty()) { //is bbJoined empty if not make it so
		//delete all contents of bbJoined
		BballRoster temp;//create an empty new list
		bbJoined.swapRoster(temp);  //swap with bbJoined so now we have an empty list
	
		

	}
	if (!bbOne.rosterEmpty() && bbTwo.rosterEmpty()) {//if only bbOne has content then just set result to bbOne via ssianment operator 
		bbJoined = bbOne;
	}
	if (bbOne.rosterEmpty() && !bbTwo.rosterEmpty()) {//if only bbTwo has content then just set result to bbTwo via ssianment operator 
		bbJoined = bbTwo;
	}

	string dupefname, dupelname;

	//ensure both one and two are not empty
	if (!bbOne.rosterEmpty() && !bbTwo.rosterEmpty()) {
		string tempfname, templname;
		SomeType tempval;
		

		for (int i = 0; i < bbTwo.howManyPlayers(); i++) {
			bbTwo.choosePlayer(i, first, last, val); //get player from two
			bbJoined.signPlayer(first, last, val);//add to joined
		}
		for (int i = 0; i < bbOne.howManyPlayers(); i++) {
			bbOne.choosePlayer(i, first, last, val); //get player from two
			bbJoined.signPlayer(first, last, val);//add to joined
		}

		if (bbOne.howManyPlayers() < bbTwo.howManyPlayers()) {
			for (int i = 0; i < bbOne.howManyPlayers(); i++) {
				bbOne.choosePlayer(i, first, last, val);
				for (int j = 0; j < bbTwo.howManyPlayers(); j++) {
					bbTwo.choosePlayer(j, tempfname, templname, tempval);
					if (tempfname == first && templname == last && tempval != val) {
						bbJoined.renouncePlayer(tempfname, templname);
						dupes = true;
					}
				}
			}

		}
		else {
			for (int i = 0; i < bbTwo.howManyPlayers(); i++) {
				bbTwo.choosePlayer(i, first, last, val);
				for (int j = 0; j < bbOne.howManyPlayers(); j++) {
					bbOne.choosePlayer(j, tempfname, templname, tempval);
					if (tempfname == first && templname == last && tempval != val) {
						bbJoined.renouncePlayer(tempfname, templname);
						dupes = true;
					}
				}
			}

		}

	}


	if (dupes) {
		return false;
	}
	return true;
		//go down roster one, get each player's name and val one at a time
		//store those values in a temp and see if those players with those values
		//exist at all on the second list if NOT then player add vals from one to joined and add vals from two to joined
		//if we have a same name different value case, then we have to not add that name at all to joined, maybe have a continue?
		//maybe if that is the case, then we store that name in another temp, and we cehc if it is on the list when we are adding
		//if we find that name in this case, we don't added it at all, we do this for both lists so it isn't added at all
		//the last case is if we have the same name and same val twice, we only want to add the name once in this case
		//another way would be to add everything, the sign player won't allow double adds.. so that is taken care of actually
		//in this case, our issue becames same name and different value, hmm in this case actually
		//we can look into the list and if we have two players same name and different values, remove both of them.
	



}

void checkRoster(const std::string& fsearch,
	const std::string& lsearch,
	const BballRoster& bbOne,
	BballRoster& bbResult) {
	if (&bbOne == &bbResult) {//dont be passing in the same list 
		BballRoster temp;//create an empty new list
		//temp = bbResult;
		checkRoster(fsearch,lsearch, bbOne, temp);
		return; //so we don't go throught the whole shebang again and cause a mess tbh
		//ensure if we pass the same list in both bbResult and bbone we don't accidentally loose contents
	}
	if (!(bbResult.rosterEmpty())) {
		BballRoster temp;
		bbResult.swapRoster(temp); //ensure we don't ahve anything in Result
	}
	if (!bbOne.rosterEmpty()) { //if bbOne isn't empty lets go
		string first, last;
		SomeType val;
		for (int i = 0; i < bbOne.howManyPlayers(); i++) {
			bbOne.choosePlayer(i, first, last, val);
			if (fsearch == first && lsearch == last) {
				bbResult.signPlayer(first, last, val);
			}
			if (fsearch == "*" && lsearch != "*") {
				if (lsearch == last) {
					bbResult.signPlayer(first, last, val);

				}
			}
			if (fsearch != "*" && lsearch == "*") {
				if (fsearch == first) {
					bbResult.signPlayer(first, last, val);

				}
			}
			if (fsearch == "*" && lsearch == "*") {
				bbResult = bbOne;

			}
		}
	}
	
}
//returns bb result as a copy of elements which match the search elements
//look up wild card implementations if needed
//ensure bbResult is EMPTY because it cannt contain other eelements
//how about if * is first name then add all with matching last name
//if * in last name add all with matching first name
//if no star, match based on first and last add elements who match only
//if both stars are passed, then copy input list to empty


#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>
#include <type_traits>
#include "BballRoster.h"
using namespace std;
bool lookupPlayer3type(bool (BballRoster::*)(const std::string&,
	const std::string&, SomeType&) const) {
	return true;
}
bool lookupPlayer3type(bool (BballRoster::*)(const std::string&,
	const std::string&, SomeType&)) {
	return false;
}
bool lookupPlayer3type(...) { return false; }
bool choosePlayer4type(bool (BballRoster::*)(int, std::string&,
	std::string&, SomeType&) const) {
	return true;
}
bool choosePlayer4type(bool (BballRoster::*)(int, std::string&,
	std::string&, SomeType&)) {
	return false;
}
bool choosePlayer4type(...) { return false; }
std::string SOMEFNAME = std::string("123");
std::string DEFAULTFNAME = std::string();
std::string ARRAYFNAME[6] = {
std::string("10"), std::string("20"), std::string("30"),
std::string("40"), std::string("50"), std::string("60")
};
std::string SOMELNAME = std::string("321");
std::string DEFAULTLNAME = std::string();
std::string ARRAYLNAME[6] = {
std::string("11"), std::string("21"), std::string("31"),
std::string("41"), std::string("51"), std::string("61")
};
SomeType SOMEVALUE = "junk";
SomeType DEFAULTV = SomeType();
SomeType ARRAYV[6] = {
"able", "baker", "charlie", "delta", "echo", "foxtrot"
};
bool has(const BballRoster& m, const std::string& firstName,
	const std::string& lastName, const SomeType& v)
{
	SomeType v2 = DEFAULTV;
	m.lookupPlayer(firstName, lastName, v2);
	SomeType v3 = SOMEVALUE;
	m.lookupPlayer(firstName, lastName, v3);
	return v2 == v && v3 == v;
}
void testone(int n)
{
	BballRoster m;
	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	} break; case 1: {
		assert((is_same<decltype(&BballRoster::rosterEmpty),
			bool (BballRoster::*)() const>::value));
	} break; case 2: {
		assert((is_same<decltype(&BballRoster::howManyPlayers),
			int (BballRoster::*)() const>::value));
	} break; case 3: {
		assert((is_same<decltype(&BballRoster::playerOnRoster),
			bool (BballRoster::*)(const std::string, const std::string)
			const>::value) ||
			(is_same<decltype(&BballRoster::playerOnRoster), bool
			(BballRoster::*)(const std::string&, const std::string&)
				const>::value));
	} break; case 4: {
		assert(lookupPlayer3type(&BballRoster::lookupPlayer));
	} break; case 5: {
		assert(choosePlayer4type(&BballRoster::choosePlayer));
	} break; case 6: {
		assert(m.rosterEmpty());
	} break; case 7: {
		assert(m.howManyPlayers() == 0);
	} break; case 8: {
		assert(!m.resignPlayer(DEFAULTFNAME, DEFAULTLNAME,
			SOMEVALUE) && m.howManyPlayers() == 0);
	} break; case 9: {
		assert(!m.renouncePlayer(DEFAULTFNAME, DEFAULTLNAME)
			&& m.howManyPlayers() == 0);
	} break; case 10: {
		assert(!m.playerOnRoster(DEFAULTFNAME,
			DEFAULTLNAME));
	} break; case 11: {
		SomeType v = SOMEVALUE;
		assert(!m.lookupPlayer(DEFAULTFNAME, DEFAULTLNAME,
			v) && v == SOMEVALUE);
	} break; case 12: {
		SomeType v = SOMEVALUE;
		assert(!m.choosePlayer(0, DEFAULTFNAME,
			DEFAULTLNAME, v) && v == SOMEVALUE);
	} break; case 13: {
		assert(m.signPlayer(SOMEFNAME, SOMELNAME,
			SOMEVALUE));
	} break; case 14: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		assert(!m.rosterEmpty());
	} break; case 15: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		assert(m.howManyPlayers() == 1);
	} break; case 16: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		assert(m.playerOnRoster(SOMEFNAME, SOMELNAME));
	} break; case 17: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		SomeType v = DEFAULTV;
		assert(m.lookupPlayer(SOMEFNAME, SOMELNAME, v));
	} break; case 18: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		SomeType v = DEFAULTV;
		m.lookupPlayer(SOMEFNAME, SOMELNAME, v);
		assert(v == SOMEVALUE);
	} break; case 19: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			SOMEVALUE);
		SomeType v = DEFAULTV;
		assert(!m.lookupPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			v));
	} break; case 20: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		SomeType v = SOMEVALUE;
		m.lookupPlayer(ARRAYFNAME[1], ARRAYLNAME[1], v);
		assert(v == SOMEVALUE);
	} break; case 21: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		std::string f = DEFAULTFNAME;
		std::string l = DEFAULTLNAME;
		SomeType v = DEFAULTV;
		assert(m.choosePlayer(0, f, l, v));
	} break; case 22: {
		m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
		std::string f = DEFAULTFNAME;
		std::string l = DEFAULTLNAME;
		SomeType v = DEFAULTV;
		m.choosePlayer(0, f, l, v);
		assert(f == SOMEFNAME && l == SOMELNAME && v ==
			SOMEVALUE);
	} break; case 23: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(!m.rosterEmpty() && m.howManyPlayers() == 2);
	} break; case 24: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(m.playerOnRoster(ARRAYFNAME[0],
			ARRAYLNAME[0]) && m.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]));
	} break; case 25: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
	} break; case 26: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			SOMEVALUE);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE);
		assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0],
			SOMEVALUE) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE));
	} break; case 27: {
		assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]));
		assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]));
	} break; case 28: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[2]);
		assert(m.howManyPlayers() == 2);
	} break; case 29: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[2]);
		assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
	} break; case 30: {
		assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]));
		assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]));
		assert(!m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[2]));
	} break; case 31: {
		assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]));
		assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]));
		assert(!m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]));
	} break; case 32: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m.resignPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE);
		assert(m.howManyPlayers() == 3 &&
			m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) && m.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]) && m.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]));
	} break; case 33: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m.resignPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE);
		assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE) &&
			has(m, ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]));
	} break; case 34: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		assert(m.resignPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE));
	} break; case 35: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.resignPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[0]);
		assert(m.howManyPlayers() == 2 && has(m,
			ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
			has(m, ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]) && !m.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
	} break; case 36: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(!m.resignPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]) && !m.resignPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[0]));
	} break; case 37: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(!m.rosterEmpty() && m.howManyPlayers() == 2);
	} break; case 38: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
	} break; case 39: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			SOMEVALUE);
		m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE);
		assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0],
			SOMEVALUE) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE));
	} break; case 40: {
		assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]));
		assert(m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]));
	} break; case 41: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signOrResign(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[2]);
		assert(m.howManyPlayers() == 2 && has(m,
			ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]) &&
			has(m, ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]));
	} break; case 42: {
		assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]));
		assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]));
		assert(m.signOrResign(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[2]));
	} break; case 43: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE);
		assert(m.howManyPlayers() == 3 && has(m,
			ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
			has(m, ARRAYFNAME[1], ARRAYLNAME[1],
				SOMEVALUE) && has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]));
	} break; case 44: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		assert(m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1],
			SOMEVALUE));
	} break; case 45: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signOrResign(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[0]);
		assert(m.howManyPlayers() == 3 && has(m,
			ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
			has(m, ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]) && has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[0]));
	} break; case 46: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(m.signOrResign(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]));
	} break; case 47: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(m.renouncePlayer(ARRAYFNAME[1],
			ARRAYLNAME[1]));
	} break; case 48: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
		assert(!m.rosterEmpty() && m.howManyPlayers() == 1
			&& has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
			!m.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]));
	} break; case 49: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.renouncePlayer(ARRAYFNAME[0], ARRAYLNAME[0]);
		assert(!m.rosterEmpty() && m.howManyPlayers() == 1
			&& has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]) &&
			!m.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]));
	} break; case 50: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.renouncePlayer(ARRAYFNAME[0], ARRAYLNAME[0]);
		m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
		assert(m.howManyPlayers() == 0);
	} break; case 51: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
		m.renouncePlayer(ARRAYFNAME[2], ARRAYLNAME[2]);
		m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		assert(m.howManyPlayers() == 2 && has(m,
			ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
			has(m, ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]) && !m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
			!m.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[2]));
	} break; case 52: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(!m.renouncePlayer(ARRAYFNAME[2],
			ARRAYLNAME[2]) && m.howManyPlayers() == 2);
	} break; case 53: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		std::string f;
		std::string l;
		SomeType v;
		assert(!m.choosePlayer(-1, f, l, v));
	} break; case 54: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		std::string f = SOMEFNAME;
		std::string l = SOMELNAME;
		SomeType v = SOMEVALUE;
		m.choosePlayer(-1, f, l, v);
		assert(f == SOMEFNAME && l == SOMELNAME && v ==
			SOMEVALUE);
	} break; case 55: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		std::string f, l;
		SomeType v;
		assert(!m.choosePlayer(2, f, l, v));
	} break; case 56: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		std::string f = SOMEFNAME;
		std::string l = SOMELNAME;
		SomeType v = SOMEVALUE;
		m.choosePlayer(2, f, l, v);
		assert(f == SOMEFNAME && l == SOMELNAME && v ==
			SOMEVALUE);
	} break; case 57: {
		m.signPlayer(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE);
		assert(m.howManyPlayers() == 1 && has(m,
			DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE));
	} break; case 58: {
		m.resignPlayer(DEFAULTFNAME, DEFAULTLNAME,
			SOMEVALUE);
		assert(m.howManyPlayers() == 0 &&
			!m.playerOnRoster(DEFAULTFNAME, DEFAULTLNAME));
	} break; case 59: {
		m.signOrResign(DEFAULTFNAME, DEFAULTLNAME,
			SOMEVALUE);
		assert(m.howManyPlayers() == 1 && has(m,
			DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE));
	} break; case 60: {
		m.signPlayer(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE);
		m.renouncePlayer(DEFAULTFNAME, DEFAULTLNAME);
		assert(m.howManyPlayers() == 0 &&
			!m.playerOnRoster(DEFAULTFNAME, DEFAULTLNAME));
	} break; case 61: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.swapRoster(m2);
			assert(m.howManyPlayers() == 3);
		}
	} break; case 62: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.swapRoster(m2);
			assert(has(m, ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]) && has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]) &&
				has(m, ARRAYFNAME[3], ARRAYLNAME[3],
					ARRAYV[3]) && !m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]));
		}
	} break; case 63: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.swapRoster(m2);
			assert(m2.howManyPlayers() == 2);
		}
	} break; case 64: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.swapRoster(m2);
			assert(has(m2, ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]) && has(m2, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1])
				&&
				!m2.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]) && !m2.playerOnRoster(ARRAYFNAME[3],
						ARRAYLNAME[3]));
		}
	} break; case 65: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
			ARRAYV[4]);
		{
			BballRoster m2;
		m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.swapRoster(m2);
		assert(m.howManyPlayers() == 3 &&
			m2.howManyPlayers() == 5);
	}
	 break; case 66: {
	{
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		assert(m2.howManyPlayers() == 2 &&
			m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
			!m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[3]));
	}
} break; case 67: {
	{
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m2.renouncePlayer(ARRAYFNAME[1],
			ARRAYLNAME[1]);
		m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m2.renouncePlayer(ARRAYFNAME[2],
			ARRAYLNAME[2]);
		m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m2.renouncePlayer(ARRAYFNAME[0],
			ARRAYLNAME[0]);
		m2.renouncePlayer(ARRAYFNAME[3],
			ARRAYLNAME[3]);
		m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
			ARRAYV[4]);
	}
	assert(true); // no corruption so bad that
	//destruction failed
} break; case 68: {
	{
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		BballRoster m3(m2);
		m3.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m3.renouncePlayer(ARRAYFNAME[1],
			ARRAYLNAME[1]);
		m3.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m3.renouncePlayer(ARRAYFNAME[2],
			ARRAYLNAME[2]);
		m3.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m3.renouncePlayer(ARRAYFNAME[0],
			ARRAYLNAME[0]);
		m3.renouncePlayer(ARRAYFNAME[3],
			ARRAYLNAME[3]);
		m3.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
			ARRAYV[4]);
	}
	assert(true); // no corruption so bad that
	//destruction failed
} break; case 69: {
	{
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m3(m2);
		assert(m3.howManyPlayers() == 3);
	}
	} break; case 70: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		{
			BballRoster m2(m);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			assert(m2.howManyPlayers() ==
				m.howManyPlayers() + 1);
		}
	} break; case 71: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		{
			BballRoster m2(m);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			assert(m2.howManyPlayers() == 4 &&
				m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
				m2.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]));
		}
	} break; case 72: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		{
			BballRoster m2(m);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			assert(m2.howManyPlayers() == 4 &&
				m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
				!m2.playerOnRoster(ARRAYFNAME[4], ARRAYLNAME[4]));
		}
	} break; case 73: {
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m3;
			m3.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			m3.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5],
				ARRAYV[5]);
			m3 = m2;
			assert(m3.howManyPlayers() == 3 &&
				m2.howManyPlayers() == 3);
		}
	} break; case 74: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			m2 = m;
			m2.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5],
				ARRAYV[5]);
			assert(m2.howManyPlayers() ==
				m.howManyPlayers() + 1);
		}
	} break; /*case 75: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			m2.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5],
				ARRAYV[5]);
			m2 = m;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
				assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYV[2]);
					ARRAYLNAME[0]) &&
					m2.playerOnRoster(ARRAYFNAME[1],
						ARRAYLNAME[1]) &&
					m2.playerOnRoster(ARRAYFNAME[2],
						ARRAYLNAME[2]) &&
					!m2.playerOnRoster(ARRAYFNAME[3],
						ARRAYLNAME[3]))));
		}
	} break;*/ case 76: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			m2.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5],
				ARRAYV[5]);
			m2 = m;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			assert(m.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				!m.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]));
		}
	} break; case 77: {
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2 = m2;
			assert(m2.howManyPlayers() == 3);
			assert(m2.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m2.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) && m2.playerOnRoster(ARRAYFNAME[2],
						ARRAYLNAME[2]));
		}
		assert(true); // no corruption so bad that
		//destruction failed
	} break; case 78: {
		{
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2 = m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			assert(m2.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m2.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m2.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]) &&
				m2.playerOnRoster(ARRAYFNAME[3],
					ARRAYLNAME[3]));
		}
	} break; case 79: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			BballRoster m3;
			joinRosters(m, m2, m3);
			assert(m3.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m3.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m3.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]));
		} break; case 80: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		BballRoster m3;
		joinRosters(m2, m, m3);
		assert(m3.playerOnRoster(ARRAYFNAME[0],
			ARRAYLNAME[0]) &&
			m3.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]) &&
			m3.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[2]));
	} break; case 81: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			BballRoster m3;
			joinRosters(m, m2, m3);
			assert(m3.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m3.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m3.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]) &&
				m3.playerOnRoster(ARRAYFNAME[3],
					ARRAYLNAME[3]) &&
				m3.playerOnRoster(ARRAYFNAME[4],
					ARRAYLNAME[4]));
		} break; case 82: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
			ARRAYV[4]);
		BballRoster m3;
		assert(joinRosters(m, m2, m3));
	} break; case 83: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			BballRoster m3;
			m3.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[5]);
			joinRosters(m, m2, m3);
			assert(m3.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m3.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m3.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]) &&
				m3.playerOnRoster(ARRAYFNAME[3],
					ARRAYLNAME[3]) &&
				m3.playerOnRoster(ARRAYFNAME[4],
					ARRAYLNAME[4]) &&
				has(m3, ARRAYFNAME[2], ARRAYLNAME[2],
					ARRAYV[2]) &&
				!has(m3, ARRAYFNAME[2], ARRAYLNAME[2],
					ARRAYV[5]));
		} break; case 84: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
			ARRAYV[4]);
		BballRoster m3;
		m3.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[5]);
		assert(joinRosters(m, m2, m3));
	} break; case 85: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m3;
			joinRosters(m, m2, m3);
			assert(m3.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m3.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m3.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]) &&
				m3.playerOnRoster(ARRAYFNAME[3],
					ARRAYLNAME[3]));
		} break; case 86: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m3;
		assert(joinRosters(m, m2, m3));
	} break; case 87: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[4]);
			BballRoster m3;
			joinRosters(m, m2, m3);
			assert(m3.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m3.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m3.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]));
		} break; case 88: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[4]);
		BballRoster m3;
		assert(!joinRosters(m, m2, m3));
	} break; case 89: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
				ARRAYV[3]);
			m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
				ARRAYV[4]);
			joinRosters(m, m2, m);
			assert(m.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
				m.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]) &&
				m.playerOnRoster(ARRAYFNAME[3],
					ARRAYLNAME[3]) &&
				m.playerOnRoster(ARRAYFNAME[4],
					ARRAYLNAME[4]));
		} break; case 90: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3],
			ARRAYV[3]);
		m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4],
			ARRAYV[4]);
		joinRosters(m, m2, m2);
		assert(m2.playerOnRoster(ARRAYFNAME[0],
			ARRAYLNAME[0]) &&
			m2.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]) &&
			m2.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[2]) &&
			m2.playerOnRoster(ARRAYFNAME[3],
				ARRAYLNAME[3]) &&
			m2.playerOnRoster(ARRAYFNAME[4],
				ARRAYLNAME[4]));
	} break; case 91: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			checkRoster(ARRAYFNAME[1], ARRAYLNAME[1], m, m2);
			assert(!m2.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) && m2.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]));
		} break; case 92: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		checkRoster(ARRAYFNAME[1], ARRAYLNAME[1], m, m2);
		assert(!m2.playerOnRoster(ARRAYFNAME[0],
			ARRAYLNAME[0]) && m2.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]));
	} break; case 93: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			checkRoster(ARRAYFNAME[1], ARRAYLNAME[1], m, m);
			assert(!m.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) && m.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]));
		} break; case 94: {
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[2]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[1],
			ARRAYV[3]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		checkRoster("*", ARRAYLNAME[1], m, m2);
		assert(m2.playerOnRoster(ARRAYFNAME[0],
			ARRAYLNAME[1]) &&
			m2.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]) &&
			m2.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[1]) &&
			!m2.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
			!m2.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[2]));
	} break; case 95: {
			m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
				ARRAYV[0]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[0],
				ARRAYV[1]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
				ARRAYV[2]);
			m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[2],
				ARRAYV[3]);
			m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
				ARRAYV[2]);
			BballRoster m2;
			checkRoster(ARRAYFNAME[1], "*", m, m2);
			assert(m2.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[0]) &&
				m2.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[1]) &&
				m2.playerOnRoster(ARRAYFNAME[1],
					ARRAYLNAME[2]) &&
				!m2.playerOnRoster(ARRAYFNAME[0],
					ARRAYLNAME[0]) &&
				!m2.playerOnRoster(ARRAYFNAME[2],
					ARRAYLNAME[2]));
		} break; case 96: {
		string all = "*";
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0],
			ARRAYV[0]);
		m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[1],
			ARRAYV[1]);
		m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1],
			ARRAYV[2]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[1],
			ARRAYV[3]);
		m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2],
			ARRAYV[2]);
		BballRoster m2;
		checkRoster("*", "*", m, m2);
		assert(m2.playerOnRoster(ARRAYFNAME[0],
			ARRAYLNAME[1]) &&
			m2.playerOnRoster(ARRAYFNAME[1],
				ARRAYLNAME[1]) &&
			m2.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[1]) &&
			m2.playerOnRoster(ARRAYFNAME[0],
				ARRAYLNAME[0]) &&
			m2.playerOnRoster(ARRAYFNAME[2],
				ARRAYLNAME[2]));
	} break; case 97: {
			BballRoster m2 = m;
			BballRoster m3;
			checkRoster("*", "*", m2, m3);
			assert(m3.howManyPlayers() == m.howManyPlayers());
		} break; case 98: {
		BballRoster m2;
		BballRoster m3(m);
		checkRoster("*", "*", m2, m3);

		assert(m3.rosterEmpty());
	} break; case 99: {
			BballRoster m2;
			checkRoster("*", "*", m2, m2);
			assert(m2.howManyPlayers() == 0);
		} break; case 100: {
		const int NITEMS = 2000;
		for (int k = 0; k < NITEMS; k++)
			assert(m.signPlayer(std::to_string(k),
				std::to_string(k), SOMEVALUE));
		assert(m.howManyPlayers() == NITEMS);
	}
}
}
}


int main()
{
	for (int i = 100; i > 0; i--) {
		cout << "Enter test number: ";
		int n;
		cin >> n;
		testone(n);
		cout << "Passed" << endl;
	}
}