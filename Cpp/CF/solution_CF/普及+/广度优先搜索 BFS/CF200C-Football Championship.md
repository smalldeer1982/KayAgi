# Football Championship

## 题目描述

这个题目是说，Berland的国家队成功加入一场足球联赛的半决赛。下面是球赛的规则：

**·** 两队比赛，比赛结束后哪支队伍进的球比对方队伍多，哪方获胜。

**·** 胜利得3分，平局两队各得1分，失败不得分（得0分）。

**·** 这四队中得到第一或第二的队伍进入下一轮。

每个队伍的名次是由总得分来算的：分越多，名次越高。如果两个队伍有同样的分，以下列方式来决定高低（越靠前的规则越优先考虑，如果还是不能分出高低，再往下判断。下列第一个权重最高）：

**·** 每个队的进球数减去失球数，得到的结果越高排名就越高。

**·** 总进球数越高，排名就越高。

**·** 如果以上都不行的话，则以字典序排列。

现在还有一场比赛未打。一共6场比赛，已知前五场的队伍与得分。某个队伍和Berland还没交战。教练想让你找到如此X:Y（X是Berland的得分，Y是另一只球队的得分），可以满足下列条件：

**·** X>Y，Berland得赢；

**·** Berland赢后，得进前二名；

**·** 如果不止一种答案，尽可能让X-Y小；

**·** 如果还是有很多答案（不止一个），你应该让Y尽可能小。

## 样例 #1

### 输入

```
AERLAND DERLAND 2:1
DERLAND CERLAND 0:3
CERLAND AERLAND 0:1
AERLAND BERLAND 2:0
DERLAND BERLAND 4:0
```

### 输出

```
6:0
```

## 样例 #2

### 输入

```
AERLAND DERLAND 2:2
DERLAND CERLAND 2:3
CERLAND AERLAND 1:3
AERLAND BERLAND 2:1
DERLAND BERLAND 4:1
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：Jerrywang09 (赞：1)

### 先说几句

很好的枚举法、STL 练习题。再说几句，感觉题目有点像，就是让 Berland 队和另一个队踢假球，使得 Berland 队成功晋级。但是，这场假球要做得尽可能真。带着这样的理解会更容易理解题意。

### 解题思路

在已知的场次中，把每个队伍的各种得分统计好。使用结构体更好地存储得分信息。如下。

```cpp
struct node
{
	string name;	// 名称
	int score;		// 得分
	int jsq;		// 净胜球
	int zsq;		// 总进球数
	node()			// 初始化
	{
		score=jsq=zsq=0;
	}
};
```

有结构体，就一定有比较函数。按照题目描述写，不是很难。

```cpp
bool cmp(node a, node b)
{
	if(a.score!=b.score)		// 1.得分
		return a.score>b.score;
	if(a.jsq!=b.jsq)			// 2.净胜球
		return a.jsq>b.jsq;
	if(a.zsq!=b.zsq)			// 3.总进球数
		return a.zsq>b.zsq;
	return a.name<b.name;		// 4.队名字典序
}
```

接下来进入主函数。输入时，用 map 嵌套 struct 记录每个队伍的详细信息。先使用 $cnt$ 统计比赛次数，就可以知道 Berland 的对手是谁。

然后，枚举对手得分 $y$ 和净胜球数 $d$，则 Berland 得分 $x=y+d$。拷贝一个新 map，改变双方得分信息，提取出 vector，排序，检查 Berland 的排名。如果循环完了没有解，输出 `IMPOSSIBLE`。

$y$ 和 $d$ 的枚举范围在 $100$ 以内即可。

### 奉上代码

```cpp
// 200C Football Championship
#include <bits/stdc++.h>
#define var long long
#define SIZE 200010
#define debug(x) cout<<#x<<":"<<x<<endl;
using namespace std;

struct node
{
	string name;
	int score;
	int jsq;
	int zsq;
	node()
	{
		score=jsq=zsq=0;
	}
};

bool cmp(node a, node b)
{
	if(a.score!=b.score)
		return a.score>b.score;
	if(a.jsq!=b.jsq)
		return a.jsq>b.jsq;
	if(a.zsq!=b.zsq)
		return a.zsq>b.zsq;
	return a.name<b.name;
}

int main()
{
	map<string, node> m;
	map<string, int> cnt;
	for(int i=0; i<5; i++)
	{
		string s1, s2; cin>>s1>>s2;
		cnt[s1]++; cnt[s2]++;
		m[s1].name=s1;
		m[s2].name=s2;
		int x, y;
		scanf("%d:%d", &x, &y);
		m[s1].zsq+=x;
		m[s2].zsq+=y;
		m[s1].jsq+=x-y;
		m[s2].jsq+=y-x;
		if(x>y)
			m[s1].score+=3;
		if(y>x)
			m[s2].score+=3;
		if(x==y)
		{
			m[s1].score++;
			m[s2].score++;
		}
	}
	string another;
	for(auto x:cnt)
		if(x.first!="BERLAND" && x.second==2)
		{
			another=x.first;
			break;
		}		
	/*
	for(auto x:m)	
	{
		cout<<x.second.name<<endl
			<<x.second.score<<endl
			<<x.second.jsq<<endl
			<<x.second.zsq<<endl
			<<endl;
	}
	*/
	for(int d=1; d<=100; d++)
		for(int y=0; y<=100; y++)	
		{
			//debug(d);
			int x=y+d;
			auto nm=m;
			nm["BERLAND"].score+=3;
			nm["BERLAND"].jsq+=d;
			nm[another].jsq+=-d;
			nm["BERLAND"].zsq+=x;
			nm[another].zsq+=y;
			vector<node> v;
			for(auto t:nm)
				v.push_back(t.second);
			sort(v.begin(), v.end(), cmp);
			if(v[0].name=="BERLAND" || v[1].name=="BERLAND")
			{
				cout<<x<<':'<<y;
				return 0;
			}
		}
	puts("IMPOSSIBLE");

    return 0;
}
```

---

## 作者：PDAST (赞：0)

一道非常非常非常恶心的大模拟，笔者一次 AC 后差点昏了过去。
## 题意
Berland 来到了某足球比赛的半决赛，半决赛采用积分淘汰制，赢了得 $3$ 分，输了不得分，平局各得 $1$ 分，排名规则是先按积分、再按净胜球、接着按进球数、最后按字典序排序。比赛已经进行了 $5$ 场，还有一场是 Berland 与另一支球队的比赛，Berland 将会用一些奇怪的手段使自己在这一局获胜， Berland 的教练想使 Berlan 进入前两名，他需要在最后一场得几分？或是不可能？
## 思路
思路比较简单，但写得真的很折磨，码量接近两千。先统计每个球队的得分、进球情况还有比赛场数，给 Berland 加上 $3$ 分，接着排序，找到 Berland 位于第几，最后一场与哪一个队踢，再枚举最后一场的得分情况，取最合理的值，最后输出就行，需要提醒的是，前面需要特判 Berland 加上 $3$ 分后位于第一或第二的情况与加上 $3$ 分后达不到第二名的情况。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Team{
	int point,gotball,inball,flag;
};
map<string,Team>mp;
string team[5],name="BERLAND",st1,st2;
int k;
bool cmp(string A,string B){
	if(mp[A].point==mp[B].point){
		if(mp[A].gotball==mp[B].gotball){
			if(mp[A].inball==mp[B].inball)return A<B;
			return mp[A].inball>mp[B].inball;
		}
		return mp[A].gotball>mp[B].gotball;
	}
	return mp[A].point>mp[B].point;
}
void doit(string a,string b,int num1,int num2){
	mp[a].inball+=num1;
	mp[b].inball+=num2;
	mp[a].gotball+=num1-num2;
	mp[b].gotball+=num2-num1;
}
void redo(string a,string b,int num1,int num2){
	mp[a].inball-=num1;
	mp[b].inball-=num2;
	mp[a].gotball-=num1-num2;
	mp[b].gotball-=num2-num1;
}
int main() {
	mp[name].point+=3;
	for(int i=1;i<=5;i++){
		int a,b;
		cin>>st1>>st2;
		scanf("%d:%d",&a,&b);
		if(!mp[st1].flag)team[++k]=st1;	
		if(!mp[st2].flag)team[++k]=st2;
		if(a>b)mp[st1].point+=3;
		if(a<b)mp[st2].point+=3;
		if(a==b){
			mp[st1].point++;
			mp[st2].point++;
		}
		doit(st1,st2,a,b);
		mp[st1].flag++;
		mp[st2].flag++;
	}
	sort(team+1,team+5,cmp);
	int f1;
	for(int i=1;i<=4;i++)if(team[i]!=name&&mp[team[i]].flag==2)f1=i;
	if(team[1]==name||team[2]==name){
		cout<<"1:0";
		return 0;
	}
	if(mp[name].point<mp[team[2]].point){
		cout<<"IMPOSSIBLE";
		return 0;
	}
	int a=200,b=100;
	for(int i=1;i<=100;i++){
		for(int j=0;j<i;j++){
			doit(name,team[f1],i,j);
			string tmp[5]={"",team[1],team[2],team[3],team[4]};
			sort(tmp+1,tmp+5,cmp);
			if(tmp[1]==name||tmp[2]==name){
				if(i-j<a-b){
					a=i;
					b=j;
				}
				if(i-j<=a-b&&j<b){
					a=i;
					b=j;
				}
			}
			redo(name,team[f1],i,j);
		}
	}
	cout<<a<<":"<<b;
	return 0;
}
```

---

## 作者：TheSky233 (赞：0)

## Description

一道没什么好说的小模拟。

[题目传送门](https://www.luogu.com.cn/problem/CF200C)。

## Solution

定义一个结构体存储每支队伍的赢球、输球个数和比分，然后按照题意进行比赛。

最后一场比赛，找到那个和 $\tt Berland$ 还没交战过的队伍，然后从 $1$ 到 $100$ 暴力枚举一下两队比分，模拟最后一场比赛之后排名即可。

### Tips

关于为什么可以暴力从 $1$ 枚举到 $100$ 来挑选答案。

题目中说 $goal_1$ 和 $goal_2$ 都是 $0 \sim 9$ 的正整数，五场比赛后最大进球数显然不会超过 $100$。

## Code

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

struct Node{
	int win,lose,rating;
	string name;
};

unordered_map<string,Node> Team;
set<string> record,fight;
vector<Node> rate;

void Judge(string name1,string name2,int rate1,int rate2){
	Team[name1].name=name1,Team[name2].name=name2;
	Team[name1].win+=rate1,Team[name2].win+=rate2;
	Team[name2].lose+=rate1,Team[name1].lose+=rate2;
	if(rate1>rate2) Team[name1].rating+=3;
	if(rate1==rate2) Team[name1].rating+=1,Team[name2].rating+=1;
	if(rate1<rate2) Team[name2].rating+=3;
	record.insert(name1); record.insert(name2); 
}

void ReadMatch(){
	for(int i=1;i<=5;i++){
		string fst,sec;
		int pts1,pts2;
		cin>>fst>>sec;
		scanf("%d:%d",&pts1,&pts2);
		Judge(fst,sec,pts1,pts2);
		if(fst=="BERLAND") fight.insert(sec);
		if(sec=="BERLAND") fight.insert(fst); 
	}
	for(auto it=record.begin();it!=record.end();it++) rate.push_back(Team[*it]);
}

void OutRank(vector<Node> v){//调试用
	puts("");
	int cnt=0;
	for(int i=0;i<v.size();i++){
		printf("Rate %d:\t",++cnt);
		cout<<v[i].name<<'\t';
		printf("%d\t %d\t %d \n",v[i].rating,v[i].win,v[i].lose);
	}
}

void Sort(vector<Node> &v){//进行一轮排序
	sort(v.begin(),v.end(),[](Node A,Node B){
		if(A.rating!=B.rating) return A.rating>B.rating;
		if(A.win-A.lose!=B.win-B.lose) return A.win-A.lose>B.win-B.lose;
		if(A.win!=B.win) return A.win>B.win;
		return A.name<B.name;
	});
}

int VecFind(vector<Node> &v,string name){//等价于vector中自带的find函数
	for(int i=0;i<v.size();i++)
		if(v[i].name==name) return i;
	return -1;
}

int FindRival(vector<Node> v){//找那个没和它打过的
	for(auto it=record.begin();it!=record.end();it++)
		if(*it!="BERLAND" && !fight.count(*it)) return VecFind(v,*it);
	return -1;
}

bool Check(int Ber,int Rival,int Fst,int Sec,vector<Node> v){//判断进行这场比赛后Berland对能否进前二
	v[Ber].win+=Fst,v[Rival].win+=Sec;
	v[Ber].lose+=Sec,v[Rival].lose+=Fst;
	v[Ber].rating+=3;
	Sort(v);
	if(VecFind(v,"BERLAND")<=1) return true;
	return false;
}

void LastFight(){
	int Berland=VecFind(rate,"BERLAND");
	if(Berland<=1){
		printf("1:0");
		exit(0);
	}
	if(rate[Berland].rating+3<rate[1].rating){
		printf("IMPOSSIBLE");
		exit(0);
	}
	
	int Rival=FindRival(rate);//rival 敌人
	
	for(int Less=1;Less<=100;Less++){
		for(int X=1;X<=100;X++){
			if(X-Less<0) continue;
			if(Check(Berland,Rival,X,X-Less,rate)){
				printf("%d:%d",X,X-Less);
				exit(0);
			}
		}
	}
}

int main(){
	ReadMatch();
	Sort(rate);
//	OutRank(rate);
	LastFight();
	return 0;
}
```

注：因为用了很多的 STL，例如 `set`、`unordered_map`、`vector`，所以常数会稍大一点。

---

## 作者：JerryMao (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF200C)

这题就是一个恶心的模拟题啊。（~~我太蒻了~~）

首先读入，用 istringstream 会比较方便，记录下每一个对的分数，净胜球，总球数和名字，然后找到 `BERLAND` 和另外一个队，sort 一下，如果已经出线了就 `1:0`，否则枚举两队的比分（~~到100就够了，假球不能太假，虽然这样还是太假~~），然后暴力 sort 就好了。~~sort完记得回溯，本蒟蒻就是这么WA的。~~

代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define rep(i,n) for(int i=0;i<n;i++)
#define Rep(i,x,n) for(int i=x;i<n;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define all(v) v.begin(),v.end()
#define itr_ iterator
#define p_b push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fr first
#define sc second
#define m_p make_pair
#define fill(a,b) memset(a,b,sizeof(a))
#define debug(x) cout<<#x<<":"<<x<<endl;
#define setp setprecision
#define over(x) {cout<<x<<endl; return ;}
using namespace std;
const ll INF=0x3f3f3f3f;
const ll mod=1000000007;
const ld eps=1e-14;//头懒得删了

struct team{
	int score,d,tot;
	int rated;
	string name;
} t[4];//用struct存球队信息
map<string,int> mp;
int cur=0;
set<string> st;
bool cmp(team x,team y){
	if(x.score>y.score) return 1;
	if(y.score>x.score) return 0;
	if(x.d>y.d) return 1;
	if(y.d>x.d) return 0;
	if(x.tot>y.tot) return 1;
	if(y.tot>x.tot) return 0;
	return x.name<y.name;
}//cmp函数

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	rep(i,5){//恶心的读入
		string ta,tb;
		cin>>ta>>tb;
		int a,b;
		string ss;
		cin>>ss;
		rep(i,ss.size()){
			if(ss[i]==':') ss[i]=' ';
		}
		istringstream s(ss);
		int sca,scb;
		s>>sca>>scb;
		if(st.find(ta)==st.end()) mp[ta]=cur++;
		if(st.find(tb)==st.end()) mp[tb]=cur++;
		st.insert(ta),st.insert(tb);
		a=mp[ta],b=mp[tb];
		t[a].rated++,t[b].rated++;
		t[a].name=ta,t[b].name=tb;
		t[a].tot+=sca,t[b].tot+=scb;t[a].d+=sca-scb,t[b].d+=scb-sca;
		if(sca>scb) t[a].score+=3;
		else if(scb>sca) t[b].score+=3;
		else t[a].score+=1,t[b].score+=1;
	}
	sort(t,t+4,cmp);
	team berland,other;
	rep(i,4){//找到BERLAND和他的对手
		if(t[i].name=="BERLAND") berland=t[i];
		if(t[i].name!="BERLAND"&&t[i].rated!=3) other=t[i];
	}
   //分类讨论
	if(berland.score+3>t[1].score){
		printf("1:0\n");
	}
	if(berland.score+3==t[1].score){
		int ansb=2*INF,anso=INF;
		rep(i,4){
			if(t[i].name=="BERLAND") t[i].score+=3;
		}
		int goal=0,goal2=0;
		for(goal2=0;goal2<100;goal2++){
			for(goal=goal2+1;goal<100;goal++){
				rep(i,4){
					if(t[i].name=="BERLAND") t[i].d+=goal-goal2,t[i].tot+=goal;
					if(t[i].name==other.name) t[i].d+=goal2-goal,t[i].tot+=goal2;
				}
				sort(t,t+4,cmp);
				if(t[0].name=="BERLAND"||t[1].name=="BERLAND"){
					if(goal-goal2<ansb-anso||(goal-goal2<ansb-anso&&goal2<anso)){
						ansb=goal,anso=goal2;
					}
					rep(i,4){
						if(t[i].name=="BERLAND") t[i].d-=goal-goal2,t[i].tot-=goal;
						if(t[i].name==other.name) t[i].d-=goal2-goal,t[i].tot-=goal2;
					}
					sort(t,t+4,cmp);
					break;
				}
				rep(i,4){
					if(t[i].name=="BERLAND") t[i].d-=goal-goal2,t[i].tot-=goal;
					if(t[i].name==other.name) t[i].d-=goal2-goal,t[i].tot-=goal2;
				}
				sort(t,t+4,cmp);
			}
		}
		printf("%d:%d\n",ansb,anso);
	}
	if(berland.score+3<t[1].score){
		printf("IMPOSSIBLE\n");
	}
	return 0;
}

```

---

