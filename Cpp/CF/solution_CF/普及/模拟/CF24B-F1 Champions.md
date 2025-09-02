# F1 Champions

## 题目描述

Formula One championship consists of series of races called Grand Prix. After every race drivers receive points according to their final position. Only the top 10 drivers receive points in the following order 25, 18, 15, 12, 10, 8, 6, 4, 2, 1. At the conclusion of the championship the driver with most points is the champion. If there is a tie, champion is the one with most wins (i.e. first places). If a tie still exists, it is chosen the one with most second places, and so on, until there are no more place to use for compare.

 Last year another scoring system was proposed but rejected. In it the champion is the one with most wins. If there is tie, champion is the one with most points. If a tie still exists it is proceeded the same way as in the original scoring system, that is comparing number of second, third, forth, and so on, places.

You are given the result of all races during the season and you are to determine the champion according to both scoring systems. It is guaranteed, that both systems will produce unique champion.

## 说明/提示

It is not guaranteed that the same drivers participate in all races. For the championship consider every driver that has participated in at least one race. The total number of drivers during the whole season is not more then $ 50 $ .

## 样例 #1

### 输入

```
3
3
Hamilton
Vettel
Webber
2
Webber
Vettel
2
Hamilton
Vettel
```

### 输出

```
Vettel
Hamilton
```

## 样例 #2

### 输入

```
2
7
Prost
Surtees
Nakajima
Schumacher
Button
DeLaRosa
Buemi
8
Alonso
Prost
NinoFarina
JimClark
DeLaRosa
Nakajima
Patrese
Surtees
```

### 输出

```
Prost
Prost
```

# 题解

## 作者：_Give_up_ (赞：9)

## 题目思路

这道题的存储很麻烦，排序就很简单了。

定义一个结构体，分别为选手的名字，得分和得到各排名的个数。

```cpp
struct rec
{
	string name;
	int sum;
	map <int,int> mp;
};

rec a[N];
```


有多少选手我们是不知道的，所以我们需要先用 set 去重，去重过程中要把输入的东西记录下来，因为后面需要把输入再用一遍，那怎么记录呢，还是一个结构体。

```cpp
struct recc
{
	int n;
	string s[60];
};

recc q[25];
```
接下来去重。

```cpp
set <string> se;
for (int i=1;i<=t;i++)
{
	q[i].n=read();
	for (int j=1;j<=q[i].n;j++)
	{
		cin >> q[i].s[j];
		se.insert(q[i].s[j]);
	}
}
```
我们的 $a$ 数组并不能直接用选手的名字来查询，所以要把每名选手定一个编号，这里的编号也需要记录，就用一个 map 来记录吧，选手的个数用 $n$ 表示。
```cpp
int n=0;
map <string,int> p;
for (set <string>::iterator it=se.begin();it!=se.end();it++)
{
	p[a[++n].name=*it]=n;
}
```
然后往 $a$ 数组里存储，我们事先定好 $z$ 数组记录从第一名往后的得分，前十名有分数，后面都是 $0$。

```cpp
int z[110] = {0,25,18,15,12,10,8,6,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
```
接下来就需要用到我们之前的 $q$ 数组了，遍历一遍 $q$ 数组，然后把各个选手的得分记录下来。还需要之前的 $p$，将选手名字对应的编号作为数组的下标，排名用结构体 $rec$ 里的 mp 记录，第一名就是 `mp[1]++;`，第二名就是 `mp[2]++`，第 $j$ 名就是 `mp[j]++`。

```cpp
for (int i=1;i<=t;i++)
{
	for (int j=1;j<=q[i].n;j++)
	{
		a[p[q[i].s[j]]].sum += z[j];
		a[p[q[i].s[j]]].mp[j]++;
	}
}
```
排序就简单了。
```cpp
bool cmp(rec a,rec b)
{
	if (a.sum==b.sum)//得分相等
	{
		for (int i=1;i<=55;i++)
			if (a.mp[i]!=b.mp[i]) return a.mp[i]>b.mp[i];//看后面的排名
	}
	else return a.sum>b.sum;
}
```
这是按方法一排序。
***
```cpp
bool cmp2(rec a,rec b)
{
	if (a.mp[1]==b.mp[1])//得到第一名的次数是否相等
	{
		if (a.sum==b.sum)//如果得分也相等
		{
			for (int i=2;i<=55;i++)
				if (a.mp[i]!=b.mp[i]) return a.mp[i]>b.mp[i];//看后面的排名
		}
		return a.sum>b.sum;
	}
	return a.mp[1]>b.mp[1];//不相等就按从大到小
}
```
这是按方法二排序。


## 最后给出完整代码

```cpp
#include<bits/stdc++.h>
#define N 55

using namespace std;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
	{
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

struct rec
{
	string name;
	int sum;
	map <int,int> mp;
};

rec a[N];
int z[110] = {0,25,18,15,12,10,8,6,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
map <string,int> p;

struct recc
{
	int n;
	string s[60];
};

recc q[25];

bool cmp(rec a,rec b)
{
	if (a.sum==b.sum)
	{
		for (int i=1;i<=55;i++)
			if (a.mp[i]!=b.mp[i]) return a.mp[i]>b.mp[i];
	}
	else return a.sum>b.sum;
}

bool cmp2(rec a,rec b)
{
	if (a.mp[1]==b.mp[1])
	{
		if (a.sum==b.sum)
		{
			for (int i=2;i<=55;i++)
				if (a.mp[i]!=b.mp[i]) return a.mp[i]>b.mp[i];
		}
		return a.sum>b.sum;
	}
	return a.mp[1]>b.mp[1];
}

int main()
{
	int t=read();
	set <string> se;
	for (int i=1;i<=t;i++)
	{
		q[i].n=read();
		for (int j=1;j<=q[i].n;j++)
		{
			cin >> q[i].s[j];
			se.insert(q[i].s[j]);
		}
	}
	int n=0;
	for (set <string>::iterator it=se.begin();it!=se.end();it++)
	{
		p[a[++n].name=*it]=n;
	}
	for (int i=1;i<=t;i++)
	{
		for (int j=1;j<=q[i].n;j++)
		{
			a[p[q[i].s[j]]].sum += z[j];
			a[p[q[i].s[j]]].mp[j]++;
		}
	}
	sort(a+1,a+n+1,cmp);
	cout << a[1].name << endl;
	sort(a+1,a+n+1,cmp2);
	cout << a[1].name << endl;
	return 0; 
}
```


---

## 作者：wmrqwq (赞：5)

# 原题链接

[CF24B F1 Champions](https://www.luogu.com.cn/problem/CF24B)

# 题目简述

现在有 $n$ 场赛车比赛，每场比赛有 $m$ 名选手，其中前 $10$ 名选手可分别拿到不同的分数，求得分最高的人和第一次数最多的人，如果次数相同就按排在第 $2$ 的次数排序，直到比较出来为止；如果得分相同的按排在第 $2$ 的次数排序，直到比较出来为止。

# 解题思路

因为本题的数据范围较小，所以直接开一个结构体：
```cpp
struct node 
{
	string id;//id代表每名选手的名字
	int sum,cs[110];//sum表示每名选手的得分，cs[i]表示每名选手拿到第i+1名的次数
}a[110];
```
然后按照题意来定义两个cmp：
```cpp
bool cmp1(node x,node y) 
{
	if(x.sum==y.sum) //如果第x个人与第y个人的得分相同
		for(int i=1;i<=50;i++) //那么就依次比x与y的排名
		{
			if(x.cs[i]!=y.cs[i])//如果x与y的排名次数不同
				return x.cs[i]>y.cs[i];//返回结果
		}
	else 
		return x.sum>y.sum;//如果两人得分不同，直接返回结果
}
```
```cpp
bool cmp2(node x,node y) 
{
	if(x.cs[1]==y.cs[1]) //如果第x个人与第y个人的得了第一名的次数相同
	{
		if(x.sum==y.sum) //如果两人得分相同
		{
			for(int i=2;i<=50;i++) //就依次比较得了2~50名的次数
				if(x.cs[i]!=y.cs[i])//如果两人次数不相同
					return x.cs[i]>y.cs[i];//返回结果
		}
		else 
			return x.sum>y.sum;//否则返回结果
	}
	else 
		return x.cs[1]>y.cs[1];//否则返回结果
}
```
最后按照题意模拟即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k=0,pd,fs[110]={25,18,15,12,10,8,6,4,2,1};//k表示到目前为止一共有几位选手
string s;
#define QwQ return 0;
struct node 
{
	string id;//id代表每名选手的名字
	int sum,cs[110];//sum表示每名选手的得分，cs[i]表示每名选手拿到第i+1名的次数
}a[110];
bool cmp1(node x,node y) 
{
	if(x.sum==y.sum) //如果第x个人与第y个人的得分相同
		for(int i=1;i<=50;i++) //那么就依次比x与y的排名
		{
			if(x.cs[i]!=y.cs[i])//如果x与y的排名次数不同
				return x.cs[i]>y.cs[i];//返回结果
		}
	else 
		return x.sum>y.sum;//如果两人得分不同，直接返回结果
}
bool cmp2(node x,node y) 
{
	if(x.cs[1]==y.cs[1]) //如果第x个人与第y个人的得了第一名的次数相同
	{
		if(x.sum==y.sum) //如果两人得分相同
		{
			for(int i=2;i<=50;i++) //就依次比较得了2~50名的次数
				if(x.cs[i]!=y.cs[i])//如果两人次数不相同
					return x.cs[i]>y.cs[i];//返回结果
		}
		else 
			return x.sum>y.sum;//否则返回结果
	}
	else 
		return x.cs[1]>y.cs[1];//否则返回结果
}
int main() 
{
	cin>>t;
	while(t--) //共进行了t场比赛
	{
		cin>>n;
		for(int i=1;i<=n;i++) 
		{
			cin>>s;//输入选手名称
		    pd=0;//将判断设为0
			for(int j=1;j<=k;j++) 
				if(a[j].id==s) //如果这位选手之前参加过了比赛
				{
					a[j].cs[i]++;//将这位选手得了第i+1名的次数加上一
					a[j].sum+=fs[i-1];//将这位选手的得分加上对应的名次的得分
					pd=1;//将判断设为一
				}
			if(!pd)//如果这位选手之前没有参加过比赛
			{
				k++;//那么将参加比赛过的选手数量增加一
				a[k].cs[i]++;//将这位选手得了第i+1名的次数加上一
				a[k].sum+=fs[i-1];//将这位选手的得分加上对应的名次的得分
				a[k].id=s;//将第k个id设为这个选手的名字
			}
		}
	}
	sort(a+1,a+k+1,cmp1);//利用cmp1排序
	cout<<a[1].id<<endl;//输出排在第一名选手的名字
	sort(a+1,a+k+1,cmp2);//利用cmp2排序
	cout<<a[1].id<<endl;//输出排在第一名选手的名字
    QwQ;//华丽的结束
}//clbzdq
```



---

## 作者：Minecraft万岁 (赞：5)

这题难度主要是一些坑点 列举一下   
$\text{First}$ 虽然只有前 $10$ 名有成绩 但是只要有排名就一定要算 也就是说 **排名的统计数组至少开到 $51$**   
$\text{Second}$ 输入的人数可以是互不重复的 也就是说 **不同** 的人名可能达到 $1000$  
~~细节比较毒瘤~~  
我们其实只要手写 $sort$ 的 $cmp$ 就可以做了  
奉上代码 


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<set>     //stl 多好啊 
#include<map>
using namespace std;
typedef long long ll;
int sco[55]={0,25,18,15,12,10,8,6,4,2,1};//数组下标从 0 开始 比较坑  
set<string> s;//记录人名 
map<string,int> mp;//用人名映射到 a[] 的下标  
struct node
{
	string name;//名字 
	int t[55];//统计不同排名的次数 
	int tot;//总共得分 
}a[1005];
int t;//几场比赛 
int n,m;
string x;//读入的名字 
int hp;//人的总数 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)
{
	if(_x<0) return -_x;
	else return _x;
}
inline bool cmp1(node p,node q)//方案1 
{
	if(p.tot!=q.tot) return p.tot>q.tot;//分数不同按分数排 
	for(int i=1;i<=50;i++)//分数相同按名次次数排 
		if(p.t[i]!=q.t[i]) return p.t[i]>q.t[i];//找到不同就可以排了 
}
inline bool cmp2(node p,node q)//方案2 
{
	if(p.t[1]!=q.t[1]) return p.t[1]>q.t[1];//先按 第一名的次数排 
	if(p.tot!=q.tot) return p.tot>q.tot;//再按分数拍 
	for(int i=2;i<=50;i++)//然后再按照 2~50 名的次数排 
		if(p.t[i]!=q.t[i]) return p.t[i]>q.t[i];//找到不同就可以排了 
}
int main()
{
	read(n); 
	while(n--)
	{
		read(m); 
		for(int i=1;i<=m;i++)//这里的 i 可以直接当做名次 
		{
			cin>>x;
			if(!s.count(x))//之前没有出现过 
			{
				a[++hp].name=x;//新加一个人 
				s.insert(x);//把这个人扔到 s 里面 下次再出现就不用新建了 
				mp[x]=hp;//建立映射 这个人的信息存在 a[] 的下标 
			}	
			a[mp[x]].tot+=sco[i];//直接用mp[x]访问x这个人的信息下标 
			a[mp[x]].t[i]++;
		}
	}
	sort(a+1,a+hp+1,cmp1);//第一种 
	cout<<a[1].name;puts("");
	sort(a+1,a+hp+1,cmp2);//第二种 
	cout<<a[1].name;puts("");
	return 0;
}



```


---

## 作者：liupan2010 (赞：4)

数据很小，可以暴力水过。

[题目传送门](https://www.luogu.com.cn/problem/CF24B)

定义一个结构体用来存选手数据。

```cpp
struct node{
	string name;									//名字 
	int pts=0,rank_time[55]={0};					//分数，拿到第 x 名的次数
}player[1001];
```

定义一个 ```find``` 函数用来查找该选手是否被数据记录过。

```cpp
void find(string s,int rank){
	bool flag=false;
	for(int i=1;i<=all;i++){						//找到了 
		if(s==player[i].name){
			player[i].rank_time[rank]++;			//拿到第 rank 名的次数加一
			player[i].pts+=score[rank];				//加上得分 
			flag=true;
			return;
		}
	}
	if(flag!=true){									//没找到 
		all++;										//总人数加一 
		player[all].name=s;							//记录名字 
		player[all].rank_time[rank]++;				//记录拿到第 rank 名的次数 
		player[all].pts+=score[rank];				//记录分数 
	}
}
```

再定义两个 ```cmp``` 函数。

```cpp
bool cmp1(node a,node b){
	if(a.pts!=b.pts){
		return a.pts>b.pts;							//根据分数比较 
	}
	else{
		int x=1;
		while(a.rank_time[x]==b.rank_time[x]){
			x++;
		}
		return a.rank_time[x]>b.rank_time[x];		//根据排名次数比较 
	}
}
bool cmp2(node a,node b){
	int x=1;
	if(a.rank_time[x]!=b.rank_time[x]){
		return a.rank_time[x]>b.rank_time[x];		//根据排名次数比较 
	}
	else{
		if(a.pts!=b.pts){
			return a.pts>b.pts;						//根据分数比较 
		}
		else{
			while(a.rank_time[x]==b.rank_time[x]){	 
				x++;
			}
			return a.rank_time[x]>b.rank_time[x];	//继续根据排名次数比较
		}
	}
}
```

剩下的就比较简单了，根据这些函数完善程序就可以了。

最后附上全部代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,all;
string s;
int score[55]={0,25,18,15,12,10,8,6,4,2,1,0};		//得分表 
struct node{
	string name;									//名字 
	int pts=0,rank_time[55]={0};					//分数，拿到第 x 名的次数
}player[1001];
void find(string s,int rank){
	bool flag=false;
	for(int i=1;i<=all;i++){						//找到了 
		if(s==player[i].name){
			player[i].rank_time[rank]++;			//拿到第 rank 名的次数加一
			player[i].pts+=score[rank];				//加上得分 
			flag=true;
			return;
		}
	}
	if(flag!=true){									//没找到 
		all++;										//总人数加一 
		player[all].name=s;							//记录名字 
		player[all].rank_time[rank]++;				//记录拿到第 rank 名的次数 
		player[all].pts+=score[rank];				//记录分数 
	}
}
bool cmp1(node a,node b){
	if(a.pts!=b.pts){
		return a.pts>b.pts;							//根据分数比较 
	}
	else{
		int x=1;
		while(a.rank_time[x]==b.rank_time[x]){
			x++;
		}
		return a.rank_time[x]>b.rank_time[x];		//根据排名次数比较 
	}
}
bool cmp2(node a,node b){
	int x=1;
	if(a.rank_time[x]!=b.rank_time[x]){
		return a.rank_time[x]>b.rank_time[x];		//根据排名次数比较 
	}
	else{
		if(a.pts!=b.pts){
			return a.pts>b.pts;						//根据分数比较 
		}
		else{
			while(a.rank_time[x]==b.rank_time[x]){	 
				x++;
			}
			return a.rank_time[x]>b.rank_time[x];	//继续根据排名次数比较
		}
	}
}
int main(){
	cin>>n;
	while(n--){
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>s;
			find(s,i);								//查找 
		}
	}
	sort(player+1,player+all+1,cmp1);				//排序再输出 
	cout<<player[1].name<<endl;
	sort(player+1,player+all+1,cmp2);
	cout<<player[1].name;
	return 0;
} 
```

---

## 作者：B_lhx (赞：2)

[CF24B F1 Champions](https://www.luogu.com.cn/problem/CF24B)
==

前置芝士：排序，模拟

思路：模拟题目的过程

```
#include<bits/stdc++.h>
using namespace std;
int scl[55]={25,18,15,12,10,8,6,4,2,1};//分数表，必须开到55，要不第12名会没分wa掉的
int n,m;//n和m
int len=0;//选手表长度
struct node{//选手结构体
	string name;//选手名字
	int score;//选手得分
	int p[105];//选手名次，第i项表示该选手第i名得过几次
}a[10005];//选手列表
int myfind(string u,int j){//查找函数（选手姓名字符串和名次）
	for(int i = 0;i<len;i++){//循环
		if(a[i].name==u){//如果名字对上了
			a[i].p[j]++;//名次++
			a[i].score+=scl[j];//添加对应的分数
			return 1;//返回找到了
		}
	}
	return 0;//没找到
}
bool cmpa(node x,node y){//排序a
	if(x.score!=y.score){//如果分数不相等
		return x.score>y.score;//大的优先
	}
	int o=0;//计数器
	while(x.p[o]==y.p[o]&&o<=50){//第o名得的次数相等
		o++;//计数器++
	}
	return x.p[o]>y.p[o];//返回第o名比对手多
}
bool cmpb(node x,node y){//排序b
	if(x.p[0]!=y.p[0]){//如果得第一名次数不相等
		return x.p[0]>y.p[0];//多的优先
	}else if(x.score!=y.score){//如果分数不相等
		return x.score>y.score;//大的优先
	}
	int o=0;//计数器
	while(x.p[o]==y.p[o]&&o<=50){//第o名得的次数相等
		o++;//计数器++
	}
	return x.p[o]>y.p[o]; //返回第o名比对手多
}
int main(){//主函数
	cin>>n;//输入n
	for(int i = 0;i<n;i++){//循环输入比赛结果
		cin>>m;//输入比赛选手数量
		if(len==0){//如果开始时选手列表长度为0
			len=m;//长度变成n
		}
		for(int j = 0;j<m;j++){//循环
			string ss;//定义字符串
			cin>>ss;//输入
			if(!myfind(ss,j)){//如果没找到这个名字
				a[len].name=ss;//新名字出现了！
				a[len].p[j]++;//场次+1
				a[len].score+=scl[j];//加上对应的分数
				len++;//选手数量++
			}
		}
	}
	sort(a,a+len,cmpa);//排序a
	cout<<a[0].name<<endl;//输出第一项的名字
	sort(a,a+len,cmpb);//排序b
	cout<<a[0].name;//输出第一项的名字
	return 0;
}
```


---

## 作者：黑影洞人 (赞：2)

题意：

输出两种排序方法中排在第 $1$ 的人的名字 
- 方法一 先按得分排序，得分相同的按排在第 $1$ 的次数排序(多的排在前面)，如果次数相同就按排在第 $2$ 的次数排序，直到比较出来为止。

- 方法二 先按排在第 $1$ 的次数排序，次数相同的话按得分高低排序 得分相同的按排在第 $2$ 的次数排序，还是相同的按排在第 $3$ 的次数排序，直到比较出来为止。

对于每个人，我们给他开一个结构体，名称，排名次数的数组，总积分。

```cpp
struct node{
	string s;
	int a[N],p;
}a[N];
```
人的名字是字符串，那么他的下标如何计算呢？

很多选手喜欢使用 STL 自带的 `map`，我用推荐用哈希。

储存量比较小，于是我们不用使用哈希链表，直接构造哈希函数 + 计数即可。

```cpp
struct hash_table{
	int cnt[19260818],tot,p=50833;
	int hs(string s){
		int l=s.length();
		int res=0;
		for(int i=0;i<l;i++)res=(res*p%md+(s[i]-'0')%md)%md;
		return res;
	}
	int& operator[](string s){
		int x=hs(s);
		return cnt[x];
	}
}hs;
int sets(string s){return hs[s]?hs[s]:hs[s]=++tot;}
```
很好，现在我们可以写排序函数了。

- 排序1 先按得分排序，得分相同的按排在第 $1$ 的次数排序(多的排在前面)，如果次数相同就按排在第 $2$ 的次数排序，直到比较出来为止。

```cpp
bool cmp1(node a,node b){
	if(a.p==b.p){
		for(int i=1;i<=50;i++){//m<=50，直接比50个排名即可
			if(a.a[i]>b.a[i])return 1;
			if(a.a[i]==b.a[i])continue;
			if(a.a[i]<b.a[i])return 0;
		}
		return a.p>b.p;
	}return a.p>b.p;
}
```

- 排序2 先按排在第 $1$ 的次数排序，次数相同的话按得分高低排序 得分相同的按排在第 $2$ 的次数排序，还是相同的按排在第 $3$ 的次数排序，直到比较出来为止。

```cpp
bool cmp2(node a,node b){
	if(a.a[1]==b.a[1]){
		if(a.p==b.p){
			for(int i=2;i<=50;i++){
				if(a.a[i]<b.a[i])return 0;
				if(a.a[i]==b.a[i])continue;
				if(a.a[i]>b.a[i])return 1;
			}
			return a.p>b.p;
		}return a.p>b.p;
	}return a.a[1]>b.a[1];
}
```

对于输入的名字，我们可以这样处理：
```cpp
int sets(string s){return hs[s]?hs[s]:hs[s]=++tot;}
```
主函数：
```cpp
scanf("%d",&n);
for(int i=1;i<=n;i++){
	scanf("%d",&m);
	for(int j=1;j<=m;j++){
		string s;
		cin>>s;
		int k=sets(s);
		a[k].s=s;
		a[k].p+=ge[j];
		a[k].a[j]++;
	}
}
```
最后，我们排序两次，找到两个第一名即可。


```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define N 114
#define md 19260817
#define int long long
using namespace std;
int ge[51]={0,25,18,15,12,10,8,6,4,2,1};
int n,m,tot;
struct hash_table{
	int cnt[19260818],tot,p=50833;
	int hs(string s){
		int l=s.length();
		int res=0;
		for(int i=0;i<l;i++)res=(res*p%md+(s[i]-'0')%md)%md;
		return res;
	}
	int& operator[](string s){
		int x=hs(s);
		return cnt[x];
	}
}hs;
int sets(string s){return hs[s]?hs[s]:hs[s]=++tot;}
struct node{
	string s;
	int a[N],p;
}a[N];
bool cmp1(node a,node b){
	if(a.p==b.p){
		for(int i=1;i<=50;i++){
			if(a.a[i]>b.a[i])return 1;
			if(a.a[i]==b.a[i])continue;
			if(a.a[i]<b.a[i])return 0;
		}
		return a.p>b.p;
	}return a.p>b.p;
}
bool cmp2(node a,node b){
	if(a.a[1]==b.a[1]){
		if(a.p==b.p){
			for(int i=2;i<=50;i++){
				if(a.a[i]<b.a[i])return 0;
				if(a.a[i]==b.a[i])continue;
				if(a.a[i]>b.a[i])return 1;
			}
			return a.p>b.p;
		}return a.p>b.p;
	}return a.a[1]>b.a[1];
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&m);
		for(int j=1;j<=m;j++){
			string s;
			cin>>s;
			int k=sets(s);
			a[k].s=s;
			a[k].p+=ge[j];
			a[k].a[j]++;
		}
	}
	sort(a+1,a+tot+1,cmp1);
	cout<<a[1].s<<endl;
	sort(a+1,a+tot+1,cmp2);
	cout<<a[1].s;
	return 0;
}


```
管理员同志审核题解辛苦了。



---

## 作者：LRL65 (赞：2)

直接按题意模拟即可。

但是要注意：**虽然成绩只算前十名，但是场次是算所有的。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k=0,b[55]={25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
struct node {
	string name;
	int df,cnt[55];
}a[55];
bool cmp1(node c,node d) {//第一种排序方法
	if(c.df==d.df) {
		for(int i=1;i<=50;i++) {
			if(c.cnt[i]!=d.cnt[i])return c.cnt[i]>d.cnt[i];
		}
	}
	else return c.df>d.df;
}
bool cmp2(node c,node d) {//第二种排序方法
	if(c.cnt[1]==d.cnt[1]) {
		if(c.df==d.df) {
			for(int i=2;i<=50;i++) {
				if(c.cnt[i]!=d.cnt[i])return c.cnt[i]>d.cnt[i];
			}
		}
		else return c.df>d.df;
	}
	else return c.cnt[1]>d.cnt[1];
}
int main() {
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1;i<=n;i++) {
			string s;
			cin>>s;
			bool flag=false;
			for(int j=1;j<=k;j++) {//以前参加过比赛
				if(a[j].name==s) {
					a[j].cnt[i]++;
					a[j].df+=b[i-1];
					flag=true;
				}
			} 
			if(!flag)k++,a[k].cnt[i]++,a[k].df+=b[i-1],a[k].name=s;//没参加过比赛
		}
	}
	sort(a+1,a+k+1,cmp1);
	cout<<a[1].name<<endl;
	sort(a+1,a+k+1,cmp2);
	cout<<a[1].name<<endl;
    return 0;
}
```


---

## 作者：Foreverxxx (赞：1)

~~样例输出不是头哥，差评。~~

我们需要记录以下几个信息：

$1.$ 每名选手的编号。

$2.$ 每名选手的成绩。

$3.$ 每名选手每一种排名的次数。

我们考虑用一个结构体记录选手的信息，结构体内记录选手的名称、得分以及每个排名的次数。

由于选手名称的输入是在比赛结果中输入的，所以我们考虑开一个 ``map`` 记录每名选手的编号，如果这名选手没有出现过，那么新建一个节点，``map`` 对应的编号即节点的编号 ，然后统计成绩以及排名的次数，如果这名选手已经出现过，那么通过 ``map`` 找到对应的节点编号，然后进行记录。

对于两种排序，我们均用自定义 ``sort`` 函数实现。

第一种排序，首先判断总分是否相同，如果不同则总分多的在前，如果总分相同，则从 $1$ 到 $50$ 枚举排位，只要枚举到某个排名的次数不同，则排名次数更多的在前。

第二种排序，首先判断第一名的次数，如果相同则再判断总分，如果总分仍然相同则像第一种排序那样枚举排位即可；如果总分不同则总分高的在前。特别地，如果第一名的次数就不相同，则第一名次数多的在前。

每次排序结束后输出第一名车手的名称即可。

### 一些细节

$1.$ 每场比赛的排名的数量并不一定相同（很多人退赛？）。

$2.$ 排名必须比较到 $50$，不能只比较到 $10$。

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sss=0,www=1;
	char chh=getchar();
	while(chh<'0'||chh>'9'){
		if(chh=='-') www=-1;
		chh=getchar();
	}
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss*www;
}
const int score[]={0,25,18,15,12,10,8,6,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int n,m; string racer;
map<string,int> vis;
struct node{
	string people;
	int score,cnt[55];
}a[1005]; int tot=0;
bool cmp1(const node& x,const node& y){
	if(x.score==y.score){
		for(register int i=1;i<=50;i++){
			if(x.cnt[i]!=y.cnt[i]) return x.cnt[i]>y.cnt[i];
		}
	}
	return x.score>y.score;
}
bool cmp2(const node& x,const node& y){
	if(x.cnt[1]==y.cnt[1]){
		if(x.score==y.score){
			for(register int i=2;i<=50;i++){
				if(x.cnt[i]!=y.cnt[i]) return x.cnt[i]>y.cnt[i];
			}
		}
		return x.score>y.score;
	}
	return x.cnt[1]>y.cnt[1];
}
signed main(){
	n=read();
	while(n--){
		m=read();
		for(register int i=1;i<=m;i++){
			cin>>racer;
			if(!vis[racer]){
				vis[racer]=++tot;
				a[tot].people=racer;
				a[tot].cnt[i]++;
				a[tot].score+=score[i];
			}
			else {
				int pos=vis[racer];
				a[pos].cnt[i]++;
				a[pos].score+=score[i];
			}
		}
	}
	sort(a+1,a+tot+1,cmp1); cout<<a[1].people<<"\n";
	sort(a+1,a+tot+1,cmp2); cout<<a[1].people<<"\n";
	return 0;
}
```

---

## 作者：happybob (赞：1)

## 题意

根据题意模拟排序，自己看吧。

## 解法

蓝题模拟，确实很容易。

搞个 `map` 记录每个人得分以及每个人的排名出现次数，`cmp` 函数很容易写，非常容易。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#include <set>
using namespace std;

constexpr int N(1e4 + 5);
int t, n;

map<pair<string, int>, int> p;
map<string, int> score;

int idx = 0;

set<string> st;
string a[N];

bool cmp1(string a, string b)
{
	if (score[a] ^ score[b]) return score[a] > score[b];
	for (int i = 1; i <= 50; i++)
	{
		if (p[make_pair(a, i)] ^ p[make_pair(b, i)]) return p[make_pair(a, i)] > p[make_pair(b, i)];
	}
	return true;
}

bool cmp2(string a, string b)
{
	if (p[make_pair(a, 1)] ^ p[make_pair(b, 1)]) return p[make_pair(a, 1)] > p[make_pair(b, 1)];
	if (score[a] ^ score[b]) return score[a] > score[b];
	for (int i = 2; i <= 50; i++)
	{
		if (p[make_pair(a, i)] ^ p[make_pair(b, i)]) return p[make_pair(a, i)] > p[make_pair(b, i)];
	}
	return true;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			string s;
			cin >> s;
			p[make_pair(s, i)]++;
			/*
			* 25, 18, 15, 12, 10, 8, 6, 4, 2, 1
			*/
			if (i == 1) score[s] += 25;
			else if (i == 2) score[s] += 18;
			else if (i == 3) score[s] += 15;
			else if (i == 4) score[s] += 12;
			else if (i == 5) score[s] += 10;
			else if (i == 6) score[s] += 8;
			else if (i == 7) score[s] += 6;
			else if (i == 8) score[s] += 4;
			else if (i == 9) score[s] += 2;
			else if (i == 10) score[s] += 1;
			st.insert(s);
		}
	}
	for (auto it = st.begin(); it != st.end(); ++it)
	{
		a[++idx] = *it;
	}
	sort(a + 1, a + idx + 1, cmp1);
	cout << a[1] << endl;
	sort(a + 1, a + idx + 1, cmp2);
	cout << a[1] << endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF24B)

本题就是 sort + cmp ， 但是坑点较多， ~~我就 WA 了 3 次~~ 。

坑 $1$ ：当排名大于 $10$ 时，分数不加，但排名还是要算的。

坑 $2$ ：题目中给出的两种方法不能看错，不然就 ……

具体细节见代码。

###   AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,t,i;
string s;
struct F1{string name;int score,rank[60];}a[1010];//20*50=1000
set<string>f;
map<string,int>f1;
int sc[11]={0,25,18,15,12,10,8,6,4,2,1};//分数数组 
bool cmp1(F1 a,F1 b){                   //第一种方法 
	if(a.score!=b.score)return a.score>b.score;
	else {
		for(int i=1;i<=50;i++)
			if(a.rank[i]!=b.rank[i])return a.rank[i]>b.rank[i];
	}
}
bool cmp2(F1 a,F1 b){                   //第二种方法 
	if(a.rank[1]!=b.rank[1])return a.rank[1]>b.rank[1];
	if(a.score!=b.score)return a.score>b.score;
	for(int i=2;i<=50;i++)
		if(a.rank[i]!=b.rank[i])return a.rank[i]>b.rank[i];
}
//这两种就按题目说的做，不会错 
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(i=1;i<=n;i++){
			cin>>s;
			if(!f.count(s)){
				f.insert(s);
				a[++t].name=s;
				f1[s]=t;        //这三句话是为数组服务的 
			}
			if(i<=10)a[f1[s]].score+=sc[i]; //if(i<=10)  要加特判 
			a[f1[s]].rank[i]++;
		}
	}
	sort(a+1,a+t+1,cmp1);    
	cout<<a[1].name<<"\n";
	sort(a+1,a+t+1,cmp2);
	cout<<a[1].name<<"\n";    //sort+输出 
	return 0;//！！！完结撒花！！！
}

```

---

## 作者：Eason_AC (赞：1)

## Content
有 $n$ 场已经进行完的赛车比赛，每场比赛给出前 $m$ 名的名字。在每场比赛中，前 $10$ 名的选手分别可以获得 $25,18,15,12,10,8,6,4,2,1$ 分，其他名次的选手不得分。现在给出两种排序方式：

1. 先按照得分降序排序，如果得分相同，按照得到第一名的次数降序排序，如果还是相同，就按照得到第二名的次数降序排序，以此类推，直到比较出来为止。
2. 先按照得到第一名的次数降序排序，如果次数相同，按照得分降序排序，如果还是相同，就按照得到第二名的次数降序排序，以此类推，直到比较出来为止。

请求出按照两种排序方式排序之后分别得出来的第一名。

**数据范围：$1\leqslant n\leqslant 20,1\leqslant m\leqslant 50$。**
## Solution
结构体排序好题。

我们开个结构体，把每个人的名字、得分以及得到的名次的次数情况储存下来：
```cpp
struct player {
	string name;
	int score, ranking[57];
}a[1007], b[1007];

```
然后就是如何通过输入储存了，我们还是利用 $\texttt{map}$ 将每个人的名字映射到其编号上，每出现一个新的名字，就新开一个空间来存储，并统计这个人的分数和排名情况。

那么为什么要开两组结构体呢？这样好方便排序，所以我们再复制一组相同的结构体，然后按照上面的两个排序方式排序即可，可以写两个 $\texttt{cmp}$ 函数，然后直接按照上面的方式模拟即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

const int getscore[51] = {0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
map<string, int> vis;
int n, cnt;
string names;
struct player {
	string name;
	int score, ranking[57];
}a[1007], b[1007];

bool cmp1(const player& p1, const player& p2) {
	if(p1.score != p2.score) return p1.score > p2.score;
	else
		for(int i = 1; i <= 50; ++i)
			if(p1.ranking[i] != p2.ranking[i]) return p1.ranking[i] > p2.ranking[i];
}
bool cmp2(const player& p1, const player& p2) {
	if(p1.ranking[1] != p2.ranking[1]) return p1.ranking[1] > p2.ranking[1];
	else if(p1.score != p2.score) return p1.score > p2.score;
	else
		for(int i = 2; i <= 50; ++i)
			if(p1.ranking[i] != p2.ranking[i]) return p1.ranking[i] > p2.ranking[i];
}

int main() {
	scanf("%d", &n);
	while(n--) {
		int m;
		scanf("%d", &m);
		for(int i = 1; i <= n; ++i) {
			cin >> names;
			if(!vis[names]) {
				vis[names] = ++cnt;
				a[vis[names]].name = names;
			}
			a[vis[names]].score += getscore[i];
			a[vis[names]].ranking[i]++;
		}
	}
	for(int i = 1; i <= cnt; ++i) b[i] = a[i];
	sort(a + 1, a + cnt + 1, cmp1);
	sort(b + 1, b + cnt + 1, cmp2);
	cout << a[1].name << endl << b[1].name;
	return 0;
}

```

---

## 作者：kimi0705 (赞：1)

用 map 存下**名字到编号的映射**，用结构体存对应编号的名字、得到第 $i$ 名的次数和总分数，再按题意进行排序，在输出第一名的名字即可。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100;
const int score[N] = {0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1}; // 分数
struct node {
	string name; // 名字（为了最后输出名字）
	int Cnt[N] = {}, sum_score = 0;
} man[N];//人的信息
int n, m, cnt = 0;
map<string, int> id; // 名字到编号的映射。
/*
  方法一
  先按 得分排序
  得分相同的 	按排在第1的次数排序
				按排在第2的次数排序
				直到比较出来为止
  方法二
  先按排在第1的次数排序
  次数相同的话按得分高低排序
  得分相同的按排在第2的次数排序
  还是相同的按排在第3的次数排序
 */
bool Cmp1(node x, node y) {
	if (x.sum_score == y.sum_score) {
		for (int i = 1; i < N; i++) { // 一位一位的比
			if (x.Cnt[i] != y.Cnt[i]) {
				return x.Cnt[i] > y.Cnt[i];
			}
		}
	}
	return x.sum_score > y.sum_score;
}
bool Cmp2(node x, node y) {
	if (x.Cnt[1] != y.Cnt[1]) return x.Cnt[1] > y.Cnt[1];
	if (x.sum_score != y.sum_score) return x.sum_score > y.sum_score;
	for (int i = 2; i <= N; i++) {
		if (x.Cnt[i] != y.Cnt[i]) {
			return x.Cnt[i] > y.Cnt[i];
		}
	}
}
signed main() {
	cin >> n;
	while (n--) { // 多次比赛
		cin >> m;
		for (int i = 1; i <= m; i++) {
			string name;
			cin >> name;
			if (!id[name]) {
				id[name] = ++cnt; // 没有出现记上名字
				man[cnt].name = name; // 名字
				man[cnt].Cnt[i]++; // 第 i 名的cnt++
				man[cnt].sum_score += score[i];//加上分数
			} else {
				int Id = id[name]; // 找到编号
				man[Id].Cnt[i]++; // 第 i 名的cnt++
				man[Id].sum_score += score[i]; // 加上分数
			}
		}
	}
	sort(man + 1, man + cnt + 1, Cmp1); // 第一种
	cout << man[1].name << '\n';
	sort(man + 1, man + cnt + 1, Cmp2); // 第二种
	cout << man[1].name << '\n';
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

$\color{cyan}\texttt{Difficulty: 1500}$

超级逆天评分。

模拟，但是细节很多。

首先因为每一个人的名字是一个字符串所以需要离散化一下。

对于每一个人记录 $element_i$ 表示这个人有多少次排名 $i$，然后记录 $sum$ 表示这个人的总得分。

然后 `sort` 直接按照题意进行排序即可。

注意离散化的时候不能重复。

其他细节见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int arr[233] = {0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
int ty[233];
string s[233][233];
struct Node
{
    int sum, element[233], id;
    Node ()
    {
        sum = id = 0;
        memset(element, 0, sizeof element);
    }
} z[233];
map<string, int> id;
string ven[233];
signed main()
{
    int n, m;
    cin >> n;
    set<string> se;
    for (int i = 1; i <= n; i++)
    {
        cin >> ty[i];
        for (int j = 1; j <= ty[i]; j++)
        {
            cin >> s[i][j];
            se.insert(s[i][j]);
        }
    }
    int tot = 0;
    for (auto &j : se)
        id[j] = ++tot, ven[tot] = j, z[tot].id = tot;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= ty[i]; j++)
        {
            z[id[s[i][j]]].sum += arr[j];
            z[id[s[i][j]]].element[j]++;
        }
    }
    sort(z + 1, z + tot + 1, [&](const Node &lhs, const Node &rhs)
    {
        if (lhs.sum != rhs.sum)
            return lhs.sum > rhs.sum;
        for (int i = 1; ; i++)
            if (lhs.element[i] != rhs.element[i])
                return lhs.element[i] > rhs.element[i];
    });
    cout << ven[z[1].id] << '\n';
    sort(z + 1, z + tot + 1, [&](const Node &lhs, const Node &rhs)
    {
        if (lhs.element[1] != rhs.element[1])
            return lhs.element[1] > rhs.element[1];
        if (lhs.sum != rhs.sum)
            return lhs.sum > rhs.sum;
        for (int i = 2; ; i++)
            if (lhs.element[i] != rhs.element[i])
                return lhs.element[i] > rhs.element[i];
    });
    cout << ven[z[1].id] << '\n';
    return 0;
}
```



---

## 作者：linjunye (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF24B)
#### 先列举一些坑点
1. 就算没有进前十，也要记录第几名。
2. 可能名字没有一个重复的，也就是说名字数是可以有一千个，所以记录名字的数组至少是这样的：
```cpp
string s[1000];
```
---
#### 代码讲解
处理得分表：
```cpp
const int H[60]={0,25,18,15,12,10,8,6,4,2,1,0};		// 第一名的得分为H[1] 
```
定义几个变量：
```
int m,n,z;string s;
```

定义一个结构体:
```cpp
struct XS{ 
	string na;int T[60],d;		//d是得分，T[]是拿过的名次 
}a[1010];
```

按题意进行两次排序：

```cpp
bool cmp1(XS a,XS b){		//排序一 
	if(a.d==b.d){	//如果分数相等
		int w=1;		//从a.T[1]开始比较 
		while(a.T[w]==b.T[w])w++;
		return a.T[w]>b.T[w];
	}
	return a.d>b.d;
}
bool cmp2(XS a,XS b){		//排序二 
	if(a.T[1]==b.T[1]){		//如果第一项相等
		if(a.d==b.d){	//	如果分数相等
			int w=2;
			while(a.T[w]==b.T[w])w++;		//从a.T[2]开始比较 
			return a.T[w]>b.T[w];
		}
		return a.d>b.d;
	}
	return a.T[1]>b.T[1];
}
```

主函数——记录选手各项内容：
```cpp
int main(){
	cin>>n;
	while(n--){
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>s;
			if(!M[s]){	//此选手没有被记录过 
        		z++;	//人数加一 
        		memset(a[z].T,0,sizeof(a[z].T));	//各项内容清空 
				a[z].na=s;	//将此选手加入数组中 
        		a[z].T[i]++;	//第i名拿的次数加一 
    			a[z].d+=H[i];	//加上得分 
        		M[s]=1;		//记录此名字 
			}
			else{		//被记录过 
				for(int j=1;j<=z;j++){
					if(s==a[j].na){		//找到了 
						a[j].T[i]++;	//第i名拿的次数加一 
						a[j].d+=H[i];	//加上得分
						break;	//退出搜索 
       				}
       			}	
			}
		}
	}
	sort(a+1,a+z+1,cmp1);cout<<a[1].na<<endl;		//输出第一种排序后的第一名 
	sort(a+1,a+z+1,cmp2);cout<<a[1].na;			//输出第二种排序后的第一名 
    return 0;
}
```
#### 最后是~~码量够长的~~完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct XS{ 
	string na;int T[60],d;		//d是得分，T[]是拿过的名次 
}a[1010];
const int H[60]={0,25,18,15,12,10,8,6,4,2,1,0};		// 第一名的得分为H[1] 
int m,n,z;string s;
map<string,int>M;		// M用来统计这个人是否出现过 
bool cmp1(XS a,XS b){		//排序一 
	if(a.d==b.d){	//如果分数相等
		int w=1;		//从a.T[1]开始比较 
		while(a.T[w]==b.T[w])w++;
		return a.T[w]>b.T[w];
	}
	return a.d>b.d;
}
bool cmp2(XS a,XS b){		//排序二 
	if(a.T[1]==b.T[1]){		//如果第一项相等
		if(a.d==b.d){	//	如果分数相等
			int w=2;
			while(a.T[w]==b.T[w])w++;		//从a.T[2]开始比较 
			return a.T[w]>b.T[w];
		}
		return a.d>b.d;
	}
	return a.T[1]>b.T[1];
}
int main(){
	cin>>n;
	while(n--){
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>s;
			if(!M[s]){	//此选手没有被记录过 
        		z++;	//人数加一 
        		memset(a[z].T,0,sizeof(a[z].T));	//各项内容清空 
				a[z].na=s;	//将此选手加入数组中 
        		a[z].T[i]++;	//第i名拿的次数加一 
    			a[z].d+=H[i];	//加上得分 
        		M[s]=1;		//记录此名字 
			}
			else{		//被记录过 
				for(int j=1;j<=z;j++){
					if(s==a[j].na){		//找到了 
						a[j].T[i]++;	//第i名拿的次数加一 
						a[j].d+=H[i];	//加上得分
						break;	//退出搜索 
       				}
       			}	
			}
		}
	}
	sort(a+1,a+z+1,cmp1);cout<<a[1].na<<endl;		//输出第一种排序后的第一名 
	sort(a+1,a+z+1,cmp2);cout<<a[1].na;			//输出第二种排序后的第一名 
    return 0;
}
```
（共创美好洛谷，切勿复制粘贴）

---

## 作者：zjr0330 (赞：0)

这一题我们先读题，发现他已经把两个方案告诉我们了。再看看数据范围，也很小。这时我们便想到了大水之算法：模拟！

首先我们定义亿个变量，变量如下：

```cpp
const int N = 1e4 + 5;    
int t, n, pll[10] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};    //记录1~10名的加分。
int l = 0;
string ans[N];    //排名名字
set<string> st;
map<string, int> sc;    //排名得分
map<pair<string, int>, int> p;
```

接下来，我们依次实现这两种排序。

### 方法一

方法一：先按得分排序。得分相同的按排在第 $1$ 的次数排序，如果次数相同就按排在第 $2$ 的次数排序，直到比较出来为止。

他要求我们按得分先排，然后再按出现次数排。这样，我们模拟实现，代码如下：

```cpp
bool ssort(string a, string b) {
		if (sc[a] ^ sc[b]) return sc[a] > sc[b];    //先排得分
		for (int i = 1; i < 51; i++) if (p[make_pair(a, i)] ^ p[make_pair(b, i)]) return p[make_pair(a, i)] > p[make_pair(b, i)];
		return true;
	}
```

### 方法二

方法二：先按排在第 $1$ 的次数排序，次数相同的话按得分高低排序，得分相同的按排在第 $2$ 的次数排序，直到比较出来为止。

这一种方法是先排出现次数，再排得分。如果得分相同就排出现次数第二的，直到排完。

这一种方法也很好模拟，代码如下：

```cpp
bool sssort(string a, string b) {
		if (p[make_pair(a, 1)]^p[make_pair(b, 1)])return p[make_pair(a, 1)] > p[make_pair(b, 1)];    //先排次数
		if (sc[a] ^ sc[b]) return sc[a] > sc[b];    //再排得分
		for (int i = 2; i < 51; i++) if (p[make_pair(a, i)] ^ p[make_pair(b, i)]) return p[make_pair(a, i)] > p[make_pair(b, i)];
		return true;
	}
```

排完后，我们就可以快乐的输出了，输出部分如下：

```cpp
sort(ans + 1, ans + l + 1, ssort);
cout << ans[1] << endl;
sort(ans + 1, ans + l + 1, sssort);
cout << ans[1] << endl;
```

下面给出完整代码：

```cpp
#include<bits/stdc++.h>
namespace bl {
#define mk(a,b) make_pair(a,b)
	using namespace std;
	const int N = 1e4 + 5;    
	int t, n, pll[10] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};    //记录1~10名的加分。
	int l = 0;
	string ans[N];    //排名名字
	set<string> st;
	map<string, int> sc;    //排名得分
	map<pair<string, int>, int> p;
	bool ssort(string a, string b) {
		if (sc[a] ^ sc[b]) return sc[a] > sc[b];    //先排得分
		for (int i = 1; i < 51; i++) if (p[mk(a, i)] ^ p[mk(b, i)]) return p[mk(a, i)] > p[mk(b, i)];
		return true;
	}
	bool sssort(string a, string b) {
		if (p[mk(a, 1)]^p[mk(b, 1)])return p[mk(a, 1)] > p[mk(b, 1)];    //先排次数
		if (sc[a] ^ sc[b]) return sc[a] > sc[b];    //再排得分
		for (int i = 2; i < 51; i++) if (p[mk(a, i)] ^ p[mk(b, i)]) return p[mk(a, i)] > p[mk(b, i)];
		return true;
	}
}
int main() {
	using namespace bl;
	string s;
	cin >> t;
	for (int nb = 0; nb < t; nb++) {
		cin >> n;
		for (int nm = 1; nm <= n; nm++) {
			cin >> s;
			p[mk(s, nm)]++;
			if (nm <= 10)sc[s] += pll[nm - 1];
			st.insert(s);
		}
	}
	for (auto i = st.begin(); i != st.end(); ++i) ans[++l] = *i;
	sort(ans + 1, ans + l + 1, ssort);
	cout << ans[1] << endl;
	sort(ans + 1, ans + l + 1, sssort);
	cout << ans[1] << endl;
	return 0;
}
```

~~相信大家会定义命名空间吧，在这里就不多讲了。。。~~

---

## 作者：Fislett (赞：0)

# 题意
已知 $n$ 场比赛前 $m$ 名的名字，每场比赛前 $10$ 名各有不同的分数，求以下两种排名方法排名第一的人的名字。

1. 按照分数排序，若分数相同，第 $1$ 次数多的优先，若第 $1$ 次数相同，第 $2$ 次数多的优先，直至比出为止。
1. 先按排在第 $1$ 的次数多的优先，次数相同则按照分数排序，分数相同的按照第 $2$ 的次数排序，直至比出为止。

# 解题方法
数据范围很小，我们模拟即可。

首先，存储的问题我们用结构体解决。
```cpp
struct node
{
	string name; //名字 
	int score, rk[51]; //得分以及各个排名的次数 
} a[1005];
```
第一种比较函数（按照分数排序，若分数相同，第 $1$ 次数多的优先，若第 $1$ 次数相同，第 $2$ 次数多的优先，直至比出为止）。
```cpp
bool cmp(node a, node b)
{
	if (a.score != b.score) return a.score > b.score; //按分数排序 
	for (int j = 1; j <= 50; j ++) if (a.rk[j] != b.rk[j]) return a.rk[j] > b.rk[j]; //从大到小按照排名次数排序 
}
```
第二种比较函数（先按排在第 $1$ 的次数排序，次数相同则按照分数排序，分数相同的按照第 $2$的次数排序，还相同的按排在第 $3$ 的次数排序，直至比出为止）。
```cpp
bool csp(node a, node b)
{
	if (a.rk[1] != b.rk[1]) return a.rk[1] > b.rk[1]; //按第1的次数排序 
	if (a.score != b.score) return a.score > b.score; //按分数排序 
	for (int j = 2; j <= 50; j ++) if (a.rk[j] != b.rk[j]) return a.rk[j] > b.rk[j]; //从大到小按照排名次数排序 
}
```
至于楼上楼下的几位大佬，为什么要用两次快排呢？这不是平白无故的给时间复杂的加上一个 $log$ 吗？两次循环直接取最优的那个不香吗？
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	string name; //名字 
	int score, rk[51]; //得分以及各个排名的次数 
} a[1005];
int n, cnt, f[51] = {0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1}, i;
bool find(string s)
{
	for (int j = 1; j <= cnt; j ++)
		if (a[j].name == s)
		{
			a[j].score += f[i];
			a[j].rk[i] ++;
			return true;
		}
	return false;
}
bool cmp(node a, node b)
{
	if (a.score != b.score) return a.score > b.score; //按分数排序 
	for (int j = 1; j <= 50; j ++) if (a.rk[j] != b.rk[j]) return a.rk[j] > b.rk[j]; //从大到小按照排名次数排序 
}
bool csp(node a, node b)
{
	if (a.rk[1] != b.rk[1]) return a.rk[1] > b.rk[1]; //按第1的次数排序 
	if (a.score != b.score) return a.score > b.score; //按分数排序 
	for (int j = 2; j <= 50; j ++) if (a.rk[j] != b.rk[j]) return a.rk[j] > b.rk[j]; //从大到小按照排名次数排序 
}
int main()
{
	scanf("%d", &n);
	while (n --)  
	{
		int m;
		scanf("%d", &m);
		for (i = 1; i <= m; i ++)
		{
			string s;
			cin >> s;
			if (!find(s))
			{
				a[++ cnt].name = s;
				a[cnt].score = f[i];
				a[cnt].rk[i] = 1;
			}
		}
	}
	node ans = a[1];
	for (int j = 2; j <= cnt; j ++) if (cmp(a[j], ans)) ans = a[j]; //第一种方法比较 
	cout << ans.name << endl;
	ans = a[1];
	for (int j = 2; j <= cnt; j ++) if (csp(a[j], ans)) ans = a[j]; //第二种方法比较 
	cout << ans.name;
}
```
本小学蒟蒻的第一篇蓝题题解，请大家多多关照。
管理员同志过年审题解辛苦了！

---

## 作者：ztytql (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF24B)

## Solution
由于需要存储的数据很多，且类型不一样，所以考虑建立一个结构体，分别存储赛车手的姓名，排名（使用数组存储）以及得分。

考虑插入数据。一个比较显然的思路为：先从头到尾扫一遍结构体，如果发现了赛车手的姓名，那么就直接将这位赛车手的排名以及得分进行更新，否则就新建这位赛车手的信息。

对于排序操作，可以模拟出两个 ```cmp``` 函数，直接 ```sort``` 即可。

总复杂度为 $O(tm),$ 具体详见代码。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int score[60] = {0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1}; // 存储 rk 1-50 的得分，不填默认为 0

struct champions // 定义结构体
{
	int score; // 得分
	int rk[1010]; // rk[i] 表示第 i 名出现了几次
	string name; // 姓名
}dr[1010];

int t, m, pos = 0; // pos 为当前结构体存储位置，类似指针

bool find(string name, int rank, int score) // 判断名字是否出现过
{
	for (int i = 1 ; i <= pos ; i ++)
		if (dr[i].name == name)
		{
			dr[i].score += score;
			dr[i].rk[rank] ++;
			return true;
		} // 在判断的同时更新数据
	return false;
}

void add(string name, int rank, int score) // 新建一个赛车手
{
	dr[++ pos].name = name;
	dr[pos].score += score;
	dr[pos].rk[rank] ++;
	return;
}

bool cmp1(champions x, champions y) // 原题中第一种排序方式
{
	if (x.score != y.score)
		return x.score > y.score; // 先比较积分
	for (int i = 1 ; i <= 50 ; i ++)
		if (x.rk[i] != y.rk[i])
			return x.rk[i] > y.rk[i]; // 再比较排名
}

bool cmp2(champions x, champions y) // 原题中第二种排序方式
{
	if (x.rk[1] != y.rk[1]) return x.rk[1] > y.rk[1]; // 先比较第一名出现的次数
	if (x.score != y.score) return x.score > y.score; // 再比较积分
	for (int i = 2 ; i <= 50 ; i ++)
		if (x.rk[i] != y.rk[i])
			return x.rk[i] > y.rk[i]; // 最后比较 2-50 名的排名
}

signed main()
{
	cin >> t;
	while (t --)
	{
		string str;
		cin >> m;
		for (int i = 1 ; i <= m ; i ++)
		{
			cin >> str;
			if (!find(str, i, score[i])) // 是否出现过
				add(str, i, score[i]); // 如果没出现过，则添加
		}
	}
	sort(dr + 1, dr + pos + 1, cmp1); // 第一次排序
	cout << dr[1].name << endl;
	
	sort(dr + 1, dr + pos + 1, cmp2); // 第二次排序
	cout << dr[1].name << endl;
	
    return 0;
}
```

---

## 作者：Dehydration (赞：0)

### 前言：

蓝题有点水了，最多黄题哈。

[problem](https://www.luogu.com.cn/problem/CF24B)。


### 思路：

只需要学会结构体排序和一点点模拟本事就可以了。


因为数据范围很小，所以用结构体存入名字，分数和名次，用模拟处理这写东西，输入名字就在结构体里面搜索有无存在，没有存在就新存一遍名字。最后再用 `sort` 排序，用 `cmp` 改变条件即可。

坑点在代码中，输入的部分代码：

```
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>m;
		for(int j=1;j<=m;j++)
		{
			cin>>S;
			f=0;
			for(int k=1;k<=cnt;k++)
			{
				if(S==a[k].mz)
				{
					a[k].rki[j]++;
					a[k].sum+=score[j];
					f=1;
					break;
				}
			}
			if(!f)//如果没有这个名字，需要特判存入名字
			{
				a[++cnt].mz=S;
				a[cnt].sum+=score[j];
				a[cnt].rki[j]++;
			}
		}
	}
```

然后就是两个排序的简单代码，运用 ```cmp``` 写就好了。


```
bool cmp1(fk x,fk y)//第一种
{
	if(x.sum!=y.sum)return x.sum>y.sum;//先分数
	int Ji=1;
	while(x.rki[Ji]==y.rki[Ji])Ji++;//再名字
	return x.rki[Ji]>y.rki[Ji];
}
bool cmp2(fk x,fk y)//第二种
{
	if(x.rki[1]!=y.rki[1])return x.rki[1]>y.rki[1];
	if(x.sum!=y.sum)return x.sum>y.sum;
	int Ji=1;;
	while(x.rki[Ji]==y.rki[Ji])Ji++;
	return x.rki[Ji]>y.rki[Ji];//同1，顺序反了而已
}
```

这样就可以了，十分简单。

### 代码：

```
#include<bits/stdc++.h>
#define M 2e5+5
using namespace std;
int score[51]={0,25,18,15,12,10,8,6,4,2,1},n,m,cnt;
bool f;
struct fk
{
	int sum,rki[51];
	string mz;
};
fk a[51];
string S;
bool cmp1(fk x,fk y)
{
	if(x.sum!=y.sum)return x.sum>y.sum;
	int Ji=1;
	while(x.rki[Ji]==y.rki[Ji])Ji++;
	return x.rki[Ji]>y.rki[Ji];
}
bool cmp2(fk x,fk y)
{
	if(x.rki[1]!=y.rki[1])return x.rki[1]>y.rki[1];
	if(x.sum!=y.sum)return x.sum>y.sum;
	int Ji=1;;
	while(x.rki[Ji]==y.rki[Ji])Ji++;
	return x.rki[Ji]>y.rki[Ji];
}
int main()
{
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>m;
		for(int j=1;j<=m;j++)
		{
			cin>>S;
			f=0;
			for(int k=1;k<=cnt;k++)
			{
				if(S==a[k].mz)
				{
					a[k].rki[j]++;
					a[k].sum+=score[j];
					f=1;
					break;
				}
			}
			if(!f)
			{
				a[++cnt].mz=S;
				a[cnt].sum+=score[j];
				a[cnt].rki[j]++;
			}
		}
	}
	sort(1+a,1+cnt+a,cmp1);
	cout<<a[1].mz<<'\n';
	sort(1+a,1+cnt+a,cmp2);
	cout<<a[1].mz;
	return 0;
}
```

---

