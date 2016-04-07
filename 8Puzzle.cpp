#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

/*PriorityQueue(top is the max element):
 * PriorityQueue<DataType, Compare, Eq>
 */
template<class T,class Compare=less<T>,class Eq=equal_to<T> >
class PriorityQueue{
	public:
		typedef typename vector<T>::iterator iterator;
		typedef typename vector<T>::const_iterator const_iterator;
	private:
		vector<T>data;
	public:
		PriorityQueue(){
			make_heap(data.begin(),data.end(),Compare());
		}
		PriorityQueue(const vector<T>&p):data(p){
			make_heap(data.begin(),data.end(),Compare());
		}
		bool empty()const{
			return data.empty();
		}
		bool has_element(const T&t)const{
			Eq eq=Eq();
			const_iterator i=data.begin();
			while(i!=data.end()){
				if(eq(*i,t))return true;
				++i;
			}
			return false;
		}
		void erase(iterator iter){
			data.erase(iter);
			rebalance();
		}
		iterator find_element(const T&t){
			Eq eq=Eq();
			iterator i=data.begin();
			while(i!=data.end()){
				if(eq(*i,t))return i;
				++i;
			}
			return i;
		}
		const_iterator find_element(const T&t)const{
			Eq eq=Eq();
			const_iterator i=data.begin();
			while(i!=data.end()){
				if(eq(*i,t))return i;
				++i;
			}
			return i;
		}
		void push_back(const T &t){
			data.push_back(t);
			push_heap(data.begin(),data.end(),Compare());
		}
		void rebalance(){
			make_heap(data.begin(),data.end(),Compare());
		}
		T&top(){
			return data.front();
		}
		const T&top()const{
			return data.front();
		}
		void pop_top(){
			pop_heap(data.begin(),data.end(),Compare());
			data.pop_back();
		}
		T&operator[](int i){
			return data[i];
		}
		const T&operator[](int i)const{
			return data[i];
		}
		int size()const{
			return data.size();
		}
};

class Puzzle{
	private:
		int d[3][3];
		int cr, cc;
	private:
		int getInvertedNo()const{
			//ignore 0.
			const int *k=&d[0][0];
			int n=0;
			for(int i=1;i<9;i++){
				for(int j=0;j<i;j++){
					if(k[j]==0||k[i]==0)continue;
					if(k[j]>k[i])n++;
				}
			}
			return n;
		}
	public:
		enum MoveType{UP, DOWN, LEFT, RIGHT,UNKOWN};

		int get(int r, int c)const{
			return d[r][c];
		}
		void set(int r, int c, int v){
			if (v == 0){
				cr = r;
				cc = c;
			}
			d[r][c] = v;
		}
		vector<MoveType>getValidMove(){
			vector<MoveType>ms;
			if (cr < 2)ms.push_back(UP);
			if (cr >0)ms.push_back(DOWN);
			if (cc < 2)ms.push_back(LEFT);
			if (cc >0)ms.push_back(RIGHT);
			return ms;
		}
	public:
		bool isCompatiable(const Puzzle&p)const{
			return (getInvertedNo()-p.getInvertedNo())%2==0;
		}
		bool isSolvable()const{
			return isCompatiable(getGoal());
		}
		bool move(MoveType type){
			int nr;
			int nc;
			nr = cr;
			nc = cc;
			switch (type){
				case UP:
					if (cr >= 2)return false;
					nr++;
					break;

				case DOWN:
					if (cr <= 0)return false;
					nr--;
					break;

				case LEFT:
					if (cc >= 2)return false;
					nc++;
					break;

				case RIGHT:
					if (cc <= 0)return false;
					nc--;
					break;
			}
			d[cr][cc] = d[nr][nc];
			d[nr][nc] = 0;
			cr = nr;
			cc = nc;
			return true;
		}
		void setPuzzle(int vv[9]){
			int r,c;
			int count=0;
			for (r = 0; r < 3; r++){
				for (c = 0; c < 3; c++){
					set(r, c, vv[count++]);
				}
			}
		}
		void setPuzzle(int vv[3][3]){
			int r,c;
			for (r = 0; r < 3; r++){
				for (c = 0; c < 3; c++){
					set(r, c, vv[r][c]);
				}
			}
		}
		Puzzle &getGoal()const{
			static Puzzle *goal=0;
			if (goal == 0)goal = new Puzzle();
			int r;
			int c;
			int vv[3][3] = { { 1, 2, 3 }, { 8, 0, 4 }, { 7, 6, 5 } };
			goal->setPuzzle(vv);
			return *goal;
		}
		void print()const{
			int r;
			int c;
			for (r = 0; r < 3; r++){
				for (c = 0; c < 3; c++){
					if (get(r, c) == 0){
						cout << " ";
					}else
						cout << get(r, c);
					cout<< " ";
				}
				cout << endl;
			}
			cout << endl;

		}
		void random(){
			int r;
			int c;
			int v;
			vector<int>a;
			for (int i = 0; i < 9; i++){
				a.push_back(i);
			}
			int remain = 9;
			for (r = 0; r < 3; r++){
				for (c = 0; c < 3; c++){				
					int k=rand() %remain;
					swap(a[k], a[remain-1]);
					v = a[remain-1];
					set(r, c, v);
					remain--;
				}
			}
		}
		void getPos(int v, int &pr, int &pc){
			int r, c;
			for (r = 0; r < 3; r++){
				for (c = 0; c < 3; c++){
					if (get(r, c) == v){
						pr = r;
						pc = c;
						return;
					}
				}
			}
		}
		bool operator==(const Puzzle&p)const{
			int r, c;
			for (r = 0; r < 3; r++){
				for (c = 0; c < 3; c++){
					if (get(r, c) != p.get(r, c))return false;
				}
			}
			return true;
		}
	public://static 
		static const char * moveTypeToString(Puzzle::MoveType type){
			switch (type){
				case Puzzle::UP:
					return "UP";
				case Puzzle::DOWN:
					return "DOWN";
				case Puzzle::LEFT:
					return "LEFT";
				case Puzzle::RIGHT:
					return "RIGHT";
			}
			return "UNKONW";
		}
static Puzzle::MoveType revertMoveType(Puzzle::MoveType type){
	switch (type){
		case Puzzle::UP:
			return Puzzle::DOWN;
		case Puzzle::DOWN:
			return Puzzle::UP;
		case Puzzle::LEFT:
			return Puzzle::RIGHT;
		case Puzzle::RIGHT:
			return Puzzle::LEFT;
	}
}

};

#include<map>
Puzzle::MoveType remap(char key,Puzzle::MoveType move,const char *keyMapper,bool keyToMove){
	int i;
	for(i=0;i<4;i++){
		if(keyMapper[i]==key)break;
	}
	switch (i){
		case 0:
			return Puzzle::UP;
		case 1:
			return Puzzle::DOWN;
		case 2:
			return Puzzle::LEFT;
		case 3:
			return Puzzle::RIGHT;
	}
	return Puzzle::UNKOWN;
}
void playGame(const Puzzle&pp){
	Puzzle p=pp;
	Puzzle::MoveType move = Puzzle::UNKOWN;
	Puzzle goal = p.getGoal();
	vector<Puzzle::MoveType>moves;
	map<char,Puzzle::MoveType>keyMapper;
	map<Puzzle::MoveType,char>revertKeyMapper;
	keyMapper['w']=Puzzle::UP;
	keyMapper['s']=Puzzle::DOWN;
	keyMapper['a']=Puzzle::LEFT;
	keyMapper['d']=Puzzle::RIGHT;
	for(map<char,Puzzle::MoveType>::const_iterator i=keyMapper.begin();i!=keyMapper.end();++i){
		revertKeyMapper[i->second]=i->first;
	}
	cout << "Goal:" << endl; goal.print();
	while (1){		
		cout<<"Current:"<<endl;p.print();
		if (p == goal)break;
		vector<Puzzle::MoveType>ms = p.getValidMove();
		cout << "ValidMove:";
		for (int i = 0; i < ms.size(); i++){
			cout << Puzzle::moveTypeToString(ms[i])<<"("<<revertKeyMapper[ms[i]]<<")" << ",";
		}
		cout << endl;
		cout<<"Key(b) for reverting to last step.";
		cout << endl;
		//receive input:
		cout << "Move:";
		char tmp;
		cin >> tmp;
		if(tmp=='b'){
			if(moves.empty()){
				cout<<"Warning: this is oldest step."<<endl;
			}else{
			Puzzle::MoveType last=moves.back();
			moves.pop_back();
			p.move(Puzzle::revertMoveType(last));
			}
		}else{
			move=keyMapper[tmp];
			if(p.move(move)){
				moves.push_back(move);
			}
		}
	}
	cout<<"You use "<<moves.size()<<" moves."<<endl;
	cout<<"Moves:[";
	for(int i=0;i<moves.size();i++){
		cout << Puzzle::moveTypeToString(moves[i])<< ",";
	}
	cout<<"]"<<endl;
	cout << "You win!"<<endl;
	cout<<endl;
}
//******************Solve Puzzle**********************
struct Node;
Node* newNode(const Puzzle&p);
void deleteNodeList();
struct Node{
	Node*parent;
	Puzzle::MoveType fromParentMove;
	Puzzle p;
	int g, h, f;
	Node(){g=0;calF();}
	Node(const Puzzle &pp) :p(pp){
		g=0;
		calF();
	}
	vector<Node*>getSucessive(){
		vector<Node*>ns;
		vector<Puzzle::MoveType>ms = p.getValidMove();
		Puzzle tmp;
		for (int i = 0; i < ms.size(); i++){
			tmp = p;
			tmp.move(ms[i]);
			ns.push_back(newNode(tmp));
			ns.back()->parent = this;
			ns.back()->g=this->g+1;
			ns.back()->calF();
			ns.back()->fromParentMove=ms[i];
		}
		return ns;
	}
	void calF(){
		calH2();
		f = g + h;
	}
	int calH2(){
		//cal haming distance between unhomed tile..
		int r, c;
		int pr, pc;
		Puzzle &goal = p.getGoal();
		h = 0;
		for (r = 0; r < 3; r++){
			for (c = 0; c < 3; c++){
				goal.getPos(p.get(r, c), pr, pc);
				h += abs(pr - r) + abs(pc - c);
			}
		}
	}
	int calH(){
		int r, c;
		int pr, pc;
		Puzzle &goal = p.getGoal();
		h = 0;
		for (r = 0; r < 3; r++){
			for (c = 0; c < 3; c++){
				if(goal.get(r,c)!=p.get(r,c)){
					h++;
				}
			}
		}
	}
	bool isGoal(){
		return p==p.getGoal();
	}
};
vector<Node*>nodeList;
Node* newNode(const Puzzle&p){
	Node* n=new Node(p);
	nodeList.push_back(n);
	return n;
}
void deleteNodeList(){
	while(!nodeList.empty()){
		Node*n=nodeList.back();
		nodeList.pop_back();
		delete n;
	}
}
struct NodeCmp{
	bool operator()(const Node*a,const Node *b){
		return a->f>b->f;
	}
};
struct NodeEq{
	bool operator()(const Node*a,const Node *b){
		return a->p==b->p;
	}
};
Node* AstartSearch(Node*start){
	//return goal Node.
	typedef PriorityQueue<Node*,NodeCmp,NodeEq> Queue;
	Queue open,close;
	open.push_back(start);
	start->g=0;
	start->parent=0;
	Node* c=0;
	int count=0;
	while(!open.empty()){
		c=open.top();
		if(c->isGoal())break;
		open.pop_top();
		//sort open list.
		vector<Node*>success=c->getSucessive();
		for(int i=0;i<success.size();i++){
			Node*s=success[i];
			if(close.has_element(s)){
				Queue::iterator ci=close.find_element(s);
				if((s->g)<((*ci)->g)){
					close.erase(ci);
					open.push_back(s);
				}
			}else if(open.has_element(s)){
				Queue::iterator oi=open.find_element(s);
				if((s->g)<((*oi)->g)){
					open.erase(oi);
					open.push_back(s);
				}
			}else{
				open.push_back(s);
			}
		}
		close.push_back(c);
	}
	if(c->isGoal())return c;
	return close.top();
}
vector<Node*>getPath(Node*end){
	vector<Node*>ns;
	while(end!=0){
		ns.push_back(end);
		end=end->parent;
	}
	reverse(ns.begin(),ns.end());
	return ns;
}
vector<Puzzle::MoveType>solvePuzzle(const Puzzle &p){
	vector<Puzzle::MoveType>ms;
	if(!p.isSolvable()){
		return ms;
	}
	vector<Node*>ns=getPath(AstartSearch(newNode(p)));
	for(int i=1;i<ns.size();i++){
		ms.push_back(ns[i]->fromParentMove);
	}
	deleteNodeList();
	return ms;
}
//******************End Solve Puzzle**********************

void randomPuzzle(Puzzle&p){
	srand(time(NULL));
	do{
		p.random();
	}while(!p.isSolvable());
}
Puzzle::MoveType convertMove(const char *m){
	if(strcmp(m,"UP")==0)return Puzzle::UP;
	if(strcmp(m,"LEFT")==0)return Puzzle::LEFT;
	if(strcmp(m,"RIGHT")==0)return Puzzle::RIGHT;
	if(strcmp(m,"DOWN")==0)return Puzzle::DOWN;
}
void recreatePuzzle(Puzzle&p,const char *moves[],int len){
	p=p.getGoal();
	for(int i=0;i<len;i++){
		p.move(Puzzle::revertMoveType(convertMove(moves[len-i-1])));
	}
}

void solveGame(const Puzzle&tp){
	Puzzle p=tp;
	cout<<"Solving..."<<endl;
	if(!p.isSolvable()){
		cout<<"This Puzzle is unsolveable."<<endl;
		return ;
	}
	p.print();
	cout<<endl;
	vector<Puzzle::MoveType>ms=solvePuzzle(p);
	for(int i=1;i<ms.size();i++){
		cout<<"After Action:"<<Puzzle::moveTypeToString(ms[i])<<endl;
		p.move(ms[i]);
		p.print();
		cout<<endl;
	}
	cout<<"number of moves:"<<ms.size()<<endl;
	cout << "Computer wins!"<<endl;
	cout<<endl;
}


int fact(int n){
	if(n==1)return 1;
	return n*fact(n-1);
}
void findMaxMotionPuzzle(){
	Puzzle p,maxP;
	int maxLen=0;
	int MaxRun=fact(9);
	int v[9]={0,1,2,3,4,5,6,7,8};
	int run=0;
	while(run++<MaxRun){
		if(run%100==0)printf("maxRun:%d run:%d\n",MaxRun,run);
		p.setPuzzle(v);
		next_permutation(v,v+9);
		if(!p.isSolvable()){continue;}
		int len=solvePuzzle(p).size();
		deleteNodeList();
		if(len>maxLen){
			maxLen=len;
			maxP=p;
			cout<<"maxlen:"<<maxLen<<endl;
			p.print();
		}
	}
	cout<<"Result:"<<endl;
	cout<<"MaxLen:"<<maxLen<<endl;
	maxP.print();
}
int main()
{
	Puzzle p;
	const char *moves[]={"RIGHT","UP","LEFT","UP","LEFT","DOWN","RIGHT","UP","LEFT","DOWN","DOWN","RIGHT","RIGHT","UP","LEFT","LEFT","DOWN","RIGHT","UP","LEFT","DOWN","RIGHT","RIGHT","UP","UP","LEFT","LEFT","DOWN","RIGHT","RIGHT","UP","LEFT","LEFT","DOWN","RIGHT","UP","RIGHT","DOWN","LEFT"};
	int len=39;

	recreatePuzzle(p,moves,len);


	solveGame(p);
	playGame(p);

	randomPuzzle(p);

	solveGame(p);
	playGame(p);
	//
	findMaxMotionPuzzle();
	return 0;
}
