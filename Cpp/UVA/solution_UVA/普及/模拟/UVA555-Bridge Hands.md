# Bridge Hands

## 题目描述

一副扑克牌，除去大小王后还有 $52$ 张。

我们定义扑克牌的大小比较为：

如果花色不同，则梅花 $<$ 方块 $<$ 黑桃 $<$ 红桃。

此处，我们将梅花写作 $\text{C}$，方块写作 $\text{D}$，黑桃写作 $\text{S}$，红桃写作 $\text{H}$。

如果花色相同，则 $2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < \text{J} < \text{Q} < \text{K} < \text{A}$。

此处我们将 $10$ 写作 $\text{T}$，$\text{J}$、$\text{Q}$、$\text{K}$、$\text{A}$保持原来的写法。

一张牌由其花色和牌点组成，即，红桃 $10$ 被我们表示成 $\text{HT}$，黑桃 $4$ 被我们表示成 $\text{S4}$，以此类推。

注意，以上有涉及到字母的均为大写字母。

现在有一种四个人的游戏是用一副去掉大小王后的扑克牌玩的。四个人分别被表示成南，西，北，东。每一轮都有一个庄家，发牌时从庄家的顺时针方向下一位选手开始发牌，然后按顺时针发牌直至牌被发光，此时每个人手里的牌数相同，为 $13$ 张。

此处默认：南的顺时针方向一位是西，西的顺时针方向一位是北，北的顺时针方向一位是东，东的顺时针方向一位是南。南、西、北、东分别用 $\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 来表示。

现在给定牌堆和庄家，请求出每位玩家的手牌**排序后**的结果。排序方法参照上部。

## 样例 #1

### 输入

```
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#```

### 输出

```
S: C3 C5 C7 CT CJ D9 DT DJ S3 SK H2 H9 HT
W: C2 C4 CK D4 D5 D6 DQ DA S4 S8 ST SJ H8
N: C6 C8 C9 CA D8 S9 SA H4 H5 H6 H7 HJ HA
E: CQ D2 D3 D7 DK S2 S5 S6 S7 SQ H3 HQ HK```

# 题解

## 作者：canwen (赞：2)

提交 UVA 的题注意要先登录 UVA，不然服务器不稳定。

## 分析
简单模拟。

先将各自的牌转换成编号，然后模拟发牌的过程，最后排序就做完了。

注意多测清空。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define pb push_back
#define mk make_pair
#define fst first
#define snd second
#define pc putchar('\n')
inline int in(){
	int k=0,kk=1;char a=getchar();
	while(!isdigit(a)){
		if(a=='-') kk=-1;
		a=getchar();
	}
	while(isdigit(a))
		k=(k<<3)+(k<<1)+a-'0',a=getchar();
	return k*kk;
}
inline void put(int a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) put(a/10);
	putchar('0'+a%10);
}

struct node{
	int a,b; // 花色 & 牌数
};
vector <node> e[5];
map <char,int> hua,num,guest;
map <int,char> hua2,num2;
bool cmp(node a, node b){
	// 排序
	if(a.a==b.a) return a.b < b.b;
	else return a.a < b.a;
}
// C D S H --> 1 2 3 4 花色
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	hua['C'] = 1, hua['D'] = 2, hua['S'] = 3, hua['H'] = 4;
	hua2[1] = 'C', hua2[2] = 'D', hua2[3] = 'S', hua2[4] = 'H';
	_rep(i,2,9) num['0'+i] = i-1;
	num['T'] = 9, num['J'] = 10, num['Q'] = 11, num['K'] = 12, num['A'] = 13;
	_rep(i,1,8) num2[i] = '1'+i;
	num2[9] = 'T', num2[10] = 'J', num2[11] = 'Q', num2[12] = 'K', num2[13] = 'A';
	guest['S'] = 1;
	guest['W'] = 2;
	guest['N'] = 3;
	guest['E'] = 4;
	// 以上处理牌号
	char c;
	while(cin>>c&&c!='#'){
		string s1,s2;
		cin >> s1 >> s2;
		int now = guest[c];
		now = (now + 1) % 5;
		if(now == 0) now = 1;
		s1 += s2;
		_reps(i,0,s1.size()-1,i+=2){
			e[now].pb((node){hua[s1[i]],num[s1[i+1]]});
			now = (now+1) % 5;
			if(!now) now = 1;
		}
		_rep(i,1,4) sort(e[i].begin(),e[i].end(),cmp);
		_rep(i,1,4){
			if(i==1) cout << 'S';
			if(i==2) cout << 'W';
			if(i==3) cout << 'N';
			if(i==4) cout << 'E';
			cout << ": ";
			_rep(j,0,e[i].size()-1)
				if(j != e[i].size()-1) cout << hua2[e[i][j].a] << num2[e[i][j].b] << " ";
				else cout << hua2[e[i][j].a] << num2[e[i][j].b];
			cout << endl;
		}
		_rep(i,1,4) e[i].clear();
	}
	return 0;
}
```

---

## 作者：__Kyw666__ (赞：1)

## 题意解释

这题是个大模拟，有点烦人，再加上 UVA 逆天的输入输出，所以不是很容易。\
接下来进入正题：给你一副去掉大小王的扑克牌以及抓牌顺序，要求输出每人手上的牌，并排序。

## 思路分析

就是模拟。\
有几个坑点：

1. 抓牌从给出选手的下一位开始记录，如图所示：![](https://cdn.luogu.com.cn/upload/image_hosting/7k4cfpnv.png)
2. 输出顺序为“南西北东”，固定不变。
3. 输出格式注意。
4. 多测不清空，**爆零两行泪。**

## 代码实现

给出部分代码：

```cpp
int to_num1(char a)//花色 
{
	if(a=='C') return 1;
	if(a=='D') return 2;
	if(a=='S') return 3;
	return 4;
}
int to_num2(char a)//数值 
{
	if(a=='T') return 10;
	if(a=='J') return 11;
	if(a=='Q') return 12;
	if(a=='K') return 13;
	return a-'0';
}
bool cmp(string x,string y)
{
	if(x[0]!=y[0]) return to_num1(x[0])<to_num1(y[0]);//先比较花色 
	return to_num2(x[1])<to_num2(y[1]);//后比较数值 
}
void string_sort(string a)//排序 
{
	int cnt=0;
	string s[15]={""};
	for(int i=0;i<a.size();i+=2)
		s[++cnt]=a.substr(i,2);//用数组来存，方便排序 
	sort(s+1,s+cnt+1,cmp);
	for(int i=1;i<cnt;i++)//输出 
		cout<<s[i]<<" ";
	cout<<s[cnt];//最后一个后面没有空格 
}
```

结束！

---

## 作者：jcf666 (赞：1)

# 题目大意
以庄家后面那一位开始顺时针分牌，分完之后按顺序输出每个人分到的每张牌。
# 解题思路
并没有要用什么高深的算法，其实就是一个大模拟题目，主要难点在代码编写。

定义一个套结构体的动态数组 $a$ 存储这四个人拥有的卡牌，储存一下题目中四个人对应的编号，定义变量 $now$ 去记录一下当时应该把牌分配给那个人，存完之后记得排序输出。

**注意输出的格式，并且一定要把数组清空。**

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
char c,m[]={'S','W','N','E'};
unordered_map<char,int>man;
struct Node{
	char hua,num;
};
int calc(char c){//自定义函数计算，方便比较
	if(c=='C')return 1;
	if(c=='D')return 2;
	if(c=='S')return 3;
	if(c=='H')return 4;
	if(c=='T')return 10;
	if(c=='J')return 11;
	if(c=='Q')return 12;
	if(c=='K')return 13;
	if(c=='A')return 14;
	return c-'0';
}
vector<Node>a[4];
bool cmp(Node a,Node b){
	return calc(a.hua)<calc(b.hua)||a.hua==b.hua&&calc(a.num)<calc(b.num);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	man['S']=0;
	man['W']=1;
	man['N']=2;
	man['E']=3;
	while(cin>>c&&c!='#'){
		int now=(man[c]+1)%4;
		cin>>s1>>s2;
		s1+=s2;
		for(int i=0;i<s1.size();i+=2){//存入
			a[now].push_back({s1[i],s1[i+1]});
			now=(now+1)%4;
		}
		for(int i=0;i<4;i++){//输出
			sort(a[i].begin(),a[i].end(),cmp);
			cout<<m[i]<<": ";
			for(int j=0;j<a[i].size();j++){
				if(j)cout<<" ";
				cout<<a[i][j].hua<<a[i][j].num;
			}
			cout<<"\n";
			a[i].clear();//初始化
		}
		
	}
	return 0;
}
```

---

## 作者：luoyebushiye (赞：1)

### 思路

我认为可以建个三维数组并进行操作，本质上像一个文件夹，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/okfjl5l2.png)
---

### 其他

关于本题的一些坑点其他题解已经说的很清楚了，所以不过多说明。

---
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[5][100][20]={'0'};//玩家方向，花色，点数 
	char b[5]={'.','S','W','N','E'};//南->西->北->东，1->2->3->4 
	char c[5]={'.','C','D','S','H'};//梅花 方块 黑桃 红桃
	char i;
	int num;
	while(cin>>i&&i!='#'){
		memset(a,'0',10000);
		num=0;
		//多测清空 
		if(i==b[1])
			num=2;
		else if(i==b[2])
			num=3;
		else if(i==b[3])
			num=4;
		else if(i==b[4])
			num=1;
		//寻找庄家的下一位 
		for(int n=1;n<=52;n++){//我们可以将扑克进行一个标记，如下 
			char x,y;
			int f=0;
			cin>>x>>y;
			if(x=='C')
				f=1;
			else if(x=='D')
				f=2;
			else if(x=='S')
				f=3;
			else if(x=='H')
				f=4;
			if(num==1){//选手方向 
				if(y=='T')//x为花色，y为点数 
					a[1][f][10]=y;
				else if(y=='J')
					a[1][f][11]=y;
				else if(y=='Q')
					a[1][f][12]=y;
				else if(y=='K')
					a[1][f][13]=y;
				else if(y=='A')
					a[1][f][14]=y;
				else
					a[1][f][y-'0']=y;
				num=2;//南->西 
			}
			else if(num==2){
				if(y=='T')
					a[2][f][10]=y;
				else if(y=='J')
					a[2][f][11]=y;
				else if(y=='Q')
					a[2][f][12]=y;
				else if(y=='K')
					a[2][f][13]=y;
				else if(y=='A')
					a[2][f][14]=y;
				else
					a[2][f][y-'0']=y;
				num=3;//西->北 
			}
			else if(num==3){
				if(y=='T')
					a[3][f][10]=y;
				else if(y=='J')
					a[3][f][11]=y;
				else if(y=='Q')
					a[3][f][12]=y;
				else if(y=='K')
					a[3][f][13]=y;
				else if(y=='A')
					a[3][f][14]=y;
				else
					a[3][f][y-'0']=y;	
				num=4;//北->东 
			}
			else if(num==4){
				if(y=='T')
					a[4][f][10]=y;
				else if(y=='J')
					a[4][f][11]=y;
				else if(y=='Q')
					a[4][f][12]=y;
				else if(y=='K')
					a[4][f][13]=y;
				else if(y=='A')
					a[4][f][14]=y;
				else
					a[4][f][y-'0']=y;		
				num=1;//东->南 
			}
		}
		for(int s1=1;s1<=4;s1++){//判断是否不为'0'，是的话就输出 
			cout<<b[s1]<<":";
			for(int s2=1;s2<=4;s2++){
				for(int s3=1;s3<=14;s3++){
					if(a[s1][s2][s3]!='0')
						cout<<" "<<c[s2]<<a[s1][s2][s3];
				}
			}
			cout<<'\n';
		}
	}

	return 0;
}
```

---

## 作者：昒昕 (赞：1)

**简要题意**

给你发牌人和 $52$ 张牌的序列，顺时针发牌，输出排序后的四个玩家的手牌。

**题目分析**

很直观的大模拟。

可以预置牌点转换和数字优先级转换的数组，方便排序。这里用的是 `unordered_map` 容器，它的内部用哈希实现，key 值定义为 `char` 型，会跟方便读取。

每个玩家的手牌可以用大小为 $4$ 的 `set` 容器存储，这样用数组会更方便，而且 `set` 可以不用考虑排序。

而题目规定的是先按花色，再按牌点从小到大排序，需要重载小于运算符。


```cpp
#include <bits/stdc++.h>
using namespace std;

unordered_map<char,int> chg,name; unordered_map<char,int> :: iterator mit;
// chg 是花色、牌点和大小的转换，用来排序；name 是东南西北和对应数字的转换，方便数组存储
char player[4]={'S','W','N','E'}; //各玩家的名字，用于输出
struct cmp {
    char s,t; //s 为花色 spade，t 为牌点
    bool operator <(const cmp &A) const { //重载小于号，让 set 按此处定义的优先级排序
        return chg[this->s]<chg[A.s]||(chg[this->s]==chg[A.s]&&chg[this->t]<chg[A.t]);
        //先比花色，如果花色一样比牌点
    }
};
set <cmp> v[4]; set <cmp> :: iterator it; //v[0~3] 代表东南西北四个玩家的牌
void init() { //初始化各种优先级的转换
    name['S']=0; name['W']=1; name['N']=2; name['E']=3;
    chg['C']=1; chg['D']=2; chg['S']=3; chg['H']=4;
    chg['T']=10; chg['J']=11; chg['Q']=12; chg['K']=13; chg['A']=14;
    for (int i=2;i<=9;i++) chg[char(i+'0')]=i;
}
int main() { //前面做完了一系列预置，主程序就十分简单啦
    char c,s,t; init();
    while (cin >>c&&c!='#') { //如果读入到 # 就跳出循环
        for (int i=0;i<4;i++) v[i].clear(); //多测一定要清空
        int p=name[c]; //发牌人
        for (int i=1;i<=52;i++) {
            cin >>s>>t;
            v[p=(p+1)%4].insert((cmp){s,t}); //模拟发牌
        }
        for (int i=0;i<4;i++) {
            cout <<player[i]<<":";
            for (it=v[i].begin();it!=v[i].end();it++) { //按 cmp 重载的顺序输出
                cout <<" "<<(*it).s<<(*it).t;
            }
            cout <<endl; //注意，UVA 题目不能有多余空格，否则会算 PE
        }
    }
    return 0;
}
```

---

## 作者：charleshe (赞：1)

大模拟。

考虑到牌的比较级实在太为复杂，这里可以用 `map` 来存储键值对，方便排序。

由于存在多组数据，每个人的手牌可以用 `vector` 来存储，方便排序也方便清空。

接下来，考虑步骤：

1. 输入庄家的编号以及牌堆，同时表示 $4$ 个玩家的手牌的 `vector` 全部清空。

1. 从庄家顺时针下一位的玩家开始发牌，此处用一个循环来不停的发 $54$ 张牌，直至牌堆清空。

1. 利用题目给定的排序方法进行排序，注意排序时优先考虑花色，其次考虑点数。

1. 按南西北东的顺序输出每个人的牌。

这些就是模拟的大部。此外还有些细节：

- 多测清空，不然会爆零。

- 注意 `vector` 的排序方式是 `sort(v.begin(),v.end(),cmp);`，而不是 `sort(v,v+v.size(),cmp);` 或其他更离谱的操作。

- 注意 UVA 鬼畜的输出，每行末尾不能有多余空格，在最后的最后还需要一个换行。

处理了这些，代码便好写了。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
vector<string> v[5];
bool cmp(string a,string b){
	map<char,int> mp;
	mp['C']=1;
	mp['D']=2;
	mp['S']=3;
	mp['H']=4;
	mp['2']=1;
	mp['3']=2;
	mp['4']=3;
	mp['5']=4;
	mp['6']=5;
	mp['7']=6;
	mp['8']=7;
	mp['9']=8;
	mp['T']=9;
	mp['J']=10;
	mp['Q']=11;
	mp['K']=12;
	mp['A']=13;//将每种花色或点数利用键值对赋得另一个值，方便排序
	if(a[0]!=b[0]) return mp[a[0]]<mp[b[0]];//注意先考虑花色
	else return mp[a[1]]<mp[b[1]];
}
char c;
string s,t;
int main(){
	cin>>c;
	while(c!='#'){//以＃为结束
		v[1].clear();
		v[2].clear();
		v[3].clear();
		v[4].clear();多测不清空，爆零两行泪
		cin>>s>>t;
		s+=t;
		int cnt;
		switch(c){
			case 'E':cnt=1;break;
			case 'S':cnt=2;break;
			case 'W':cnt=3;break;
			case 'N':cnt=4;break;
		}//找出庄家的顺时针下一位玩家，并从他开始发牌
		for(int i=0;i<104;i++){//注意每两个字符是一张牌，所以牌堆大小是104不是52
			string rt="";
			rt+=s[i];
			rt+=s[i+1];
			v[cnt].push_back(rt);
			cnt++;
			if(cnt>4) cnt-=4;
			i++;
		}
		sort(v[1].begin(),v[1].end(),cmp);
		sort(v[2].begin(),v[2].end(),cmp);
		sort(v[3].begin(),v[3].end(),cmp);
		sort(v[4].begin(),v[4].end(),cmp);//对四个牌堆均进行排序
		string ppp[5]={"","S:","W:","N:","E:"};
		for(int i=1;i<=4;i++){
			cout<<ppp[i]<<" ";
			for(int ii=0;ii<12;ii++) cout<<v[i][ii]<<" ";//注意行末不能有空格
			cout<<v[i][12]<<endl;
		}
		cin>>c;
	}
	return 0;
}
```


---

## 作者：fly_and_goal (赞：0)

# 题目大意
给你 $52$ 张牌的发牌顺序，顺时针发牌，输出排序后的四个玩家的手牌。
# 思路
用优先队列做，把字母全部变成数字去排序，输出时转换一下即可（其实就是一道大模拟），换句话说：对于每组数据，用四个优先队列存好，最后输出即可。
# 注意
- 要关注初始是从谁开始发牌（会影响答案的）。
- 注意输出顺序。
- 花色优先，牌大小其次。
- 多组数据，注意清空。

---

## 作者：Leopard_cats (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA555)

~~这题平常喜欢打牌的应该更容易理解题目。~~

# 思路分析

读完题之后发现，就是一道模拟题，码量不算大。

看到题目中要求对手牌排序后输出，就想到了用**优先队列**去做，这里我优先队列的排序思路是：**把字母全部变成数字去排序**，这样比较方便，只需要输入输出的时候转换一下就好了。这一点具体见代码。

因此整题的思路就是：对于每堆牌，先从头到尾跑一遍，用四个优先队列把牌依次存好，再整体输出即可。

#### 然后就是模拟的细节问题了：

1. 不要忽略题目里面的**庄家**，这个对发牌顺序有直接影响。
2. 不要忽略题目要求的**输出顺序**。
3. 注意排序是**花色优先，再按牌面大小排序**。
4. **输出的时候行末不要带空格**~~（UVA 特性，需要特别注意一下）~~。否则会 `Presentation error`。
5. 多组数据要注意**清空**，这里我用优先队列是输出一个弹出一个，所以输出好了就是清空了。

然后就是愉快的写题啦~

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct pai{
	ll color,num;
}a;
struct compare{
	bool operator()(pai l,pai r){
		if (l.color==r.color) return l.num>r.num;
		return l.color>r.color;
	}
};
priority_queue <pai, vector<pai>, compare> q[5]; //存牌的优先队列，先按花色再按大小排列，compare定义见上 
char c;
string s1,s2,s;
ll tmp,k,start,temp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>c; //庄家 
	while (c!='#'){
		cin>>s1;
		cin>>s2;
		s=' '+s1+s2; //这里把两行牌放进一行里考虑 
		tmp=1; // 当前取到的牌 
		if (c=='S') start=3;
		if (c=='W') start=4;
		if (c=='N') start=1;
		if (c=='E') start=2;
		//庄家先抽牌，start表示先抽牌的人 
		for (ll i=1;i<=13;i++){
			for (int j=start;j<=start+3;j++){
				//a表示当前抽到的牌 
				if (s[tmp]=='C') a.color=1;
				if (s[tmp]=='D') a.color=2;
				if (s[tmp]=='S') a.color=3;
				if (s[tmp]=='H') a.color=4;
				//花色改数字存储 
				if (s[tmp+1]>='2' && s[tmp+1]<='9') a.num=s[tmp+1]-48;
				if (s[tmp+1]=='T') a.num=10;
				if (s[tmp+1]=='J') a.num=11;
				if (s[tmp+1]=='Q') a.num=12;
				if (s[tmp+1]=='K') a.num=13;
				if (s[tmp+1]=='A') a.num=14;
				//牌面大小改数字存储 
				temp=j%4; //当前抽牌的人 
				if (temp==0) temp=4;
				q[temp].push(a);
				tmp+=2;
			}
		}
		for (ll i=2;i<=5;i++){
			k=i%4;
			if (k==0) k=4;
			if (k==1) cout<<"E: ";
			if (k==2) cout<<"S: ";
			if (k==3) cout<<"W: ";
			if (k==4) cout<<"N: ";
			//同上，当前输出抽到的牌的人 
			while (!q[k].empty()){
				a=q[k].top();
				q[k].pop();
				if (a.color==1) cout<<'C';
				if (a.color==2) cout<<'D';
				if (a.color==3) cout<<'S';
				if (a.color==4) cout<<'H';
				//花色数字转回字母 
				if (a.num>=2 && a.num<=9) cout<<a.num;
				if (a.num==10) cout<<'T';
				if (a.num==11) cout<<'J';
				if (a.num==12) cout<<'Q';
				if (a.num==13) cout<<'K';
				if (a.num==14) cout<<'A';
				//牌面大小数字转回字母 
				if (!q[k].empty()) cout<<' '; //行末不要有空格，会WA 
			}
			cout<<'\n';
		}
		cin>>c;
	}
}
```

---

