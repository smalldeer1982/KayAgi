# Winner

## 题目描述

在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。


保证在比赛结束时至少有一个玩家的分数为正。

## 样例 #1

### 输入

```
3
mike 3
andrew 5
mike 2
```

### 输出

```
andrew
```

## 样例 #2

### 输入

```
3
andrew 3
andrew 2
mike 5
```

### 输出

```
andrew
```

# 题解

## 作者：Honor誉 (赞：26)

# map 映射练手题
# CF2A
有关这一题，其实是一道非常水的map，没有学过的同学可以去百度搜来学习一下。不过，我在这里也介绍一下。

1，如何开一个map。

这里需要引用c++ stl库
```cpp
#include<map>
using namespace std;
map<作为数组名称的变量类型，储存的变量类型> mp;
int cnt;
string s;
```
2，如何使用map.

举个例子，需要储存以一个字符串为名字的int数组。

mp[s]=++cnt;

然后做这题就需要知道这些，其他细节在代码中有。
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int> mp,mpp;
int n,a[100001],maxn=-99999999;
string s[100001],s1;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>s[i]>>a[i];
        mp[s[i]]+=a[i];//记录数值
    }
    for(int i=1;i<=n;i++)
    {
        maxn=max(maxn,mp[s[i]]);//取最大
    }
    for(int i=1;i<=n;i++)//谁先到达maxn的就取谁
    {
        mpp[s[i]]+=a[i];
        if(mp[s[i]]==maxn&&mpp[s[i]]>=maxn)
        {
            s1=s[i];
            break;
        }
    }
    cout<<s1<<endl;
    return 0;
} 
```

---

## 作者：sandwich (赞：8)

#### 这一题的话练得是~~简单~~的图
大家的想法都很接近

但是，还是有很多坑

这就多亏了讨论区的dalao，帮我解决了很多的难题
以下是一些有用的数据
```cpp
8 
d 13
c 12 
a 1 
a 1 
a 1 
b 10 
d -12 
a 9
正解:c 
```

```cpp
5
a 4
b 6
a 2
b -2
b 2
正解:b
```
```cpp
4
a 4
b 6
a 2
b -2
正解:a
```
@blackzoo @StudyingFather 

所有的疑问这些数据基本都能解决
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,k[1001],maxn=-100000000000;
string x[1001];
map<string,int> m;
map<string,int> a;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
    	cin>>x[i]>>k[i];
    	m[x[i]]+=k[i];
    	a[x[i]]+=k[i]; 
	}
	for(i=1;i<=n;i++)
	{
		maxn=max(maxn,m[x[i]]);
	    m[x[i]]=0;
	}
	for(i=1;i<=n;i++)
	{
		m[x[i]]+=k[i];
		if(m[x[i]]>=maxn&&a[x[i]]==maxn) {cout<<x[i];return 0;}
                //这里需要注意，m[x[i]]之后不能用=，因为题目的意思
		//是那么其中首先获得至少(重点) m 分的玩家胜利 
	}
	return 0;
}
```


---

## 作者：_Blue_ (赞：5)

首先我们要做这题，先要掌握相关的**知识点**有:  
[Map 映射](baidu.com)  
因为担心重复解法通不过，于是我就用了**iterator**迭代器和**Pair**双元结构体这些玩意，可能会更麻烦一些，但是也不失为一种**高端写法** 。   
然后我们就可以开始快乐地写代码啦！  
老规矩，先上代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<string,int>Pair;
typedef pair<int,int>PPair;
map<int,Pair> q;
map<string,PPair> p;
int n;
int m;
int main(){
   scanf("%d",&n);
   for(int i=1;i<=n;i++){
       string x;int v;
       cin>>x>>v;
       q[i].first=x;
       q[i].second=v;
       p[x].first+=v;
   } 
   for(map<string,PPair>::iterator it=p.begin();it!=p.end();it++){
       m=max(p[it->first].first,m);
   }
   for(int i=1;i<=n;i++){
       p[q[i].first].second+=q[i].second;
       if(p[q[i].first].second>=m&&p[q[i].first].first==m){
           cout<<q[i].first<<endl;
           return 0;
       }
   }
   
}
```  
这题不难，重点在于**正确理解题意** 。~~(我就没有理解然后找了半天错误~~  
看看，题目是怎么说的？  
>在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在“名称和得分”行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
>   

这个很好理解，拿个map映射就可以做了  
于是我们这样定义：  
```cpp
typedef pair<int,int>PPair;
map<string,PPair> p;
```
  
其中**p[ ].first**记录的是最终得分。  
然后呢？  
>如果在比赛结束时只有一名玩家分数最多，他就是获胜者。如果两名或两名以上的玩家在比赛结束时都有最大的分数 m，那么其中首先获得至少 m 分的玩家胜利。
>  

也就是说，我们要先求出这个值m，然后重新对所有人进行得分的计算，并且**获胜者满足**：  
- 最终得分等于m
- 得分最早达到m（注意！是达到，即大于等于）   
  
  
于是我们进行迭代操作，将每个回合重新计算一次，如果发现有人满足以上两个条件，它就是**Winner**。  

 ```cpp
for(int i=1;i<=n;i++){
       p[q[i].first].second+=q[i].second;
       if(p[q[i].first].second>=m&&p[q[i].first].first==m){
           cout<<q[i].first<<endl;
           return 0;
       }
   }
```  
好啦！快去切了这题吧！
  
  
--------------------------------
**Update:**  
  之前版面有些粗糙，于 _2019.12.11_ 修改，望通过

---

## 作者：purple7 (赞：5)

之前看到那么多大佬都用的是map，而没学过STL的我，为大家提供一发用结构体做的题解。  
第一次做的时候没有考虑到负数，所以WA了最后一个点。所以对思路进行修正。

思路如下：   
分两次寻找和记录。  
1. 在已经记录的人的分数里面搜索，如果找到这个人的名字，就将他的分数增加。如果没找到，就记录他的名字和第一次的分数。    
2. 在最后已经确定下来的分数里面寻找最大值 $maxn$。  
3. 同过程1，再寻找和记录一次，如果在加分的过程中，这个人的最后已经确定的分数等于他现在的分数并且他现在的分数等于 $maxn$，那他就是我们要寻找的人了，输出他的名字，结束程序。    
##### 下面附上代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ac{
	long long sum=0;//这里的sum和下文的cnt是记录这个人的得分。
	string s;//记录这个人的名字
}a[10001];//两个结构体，结构体a记录第一次加分的情况，结构体b记录第二次加分的情况。
struct ak{
	long long cnt=0;
	string g;
}b[10001];
int main()
{
	int m[100000];//两个数组记录输入便于第二次的查找。
	string k[10000];
	long long maxn=INT_MIN;//maxn即为最大值
	int n;
	cin>>n;
	string p;
	int top=0;//top是指针，记录当前有多少个人
	bool flag;
	for(int i=1;i<=n;i++)
	{
		flag=false;//flag用来记录能否找到这个人。
		cin>>k[i]>>m[i];
		for(int j=1;j<=top;j++)
		{
			if(k[i]==a[j].s)
			{
				a[j].sum+=m[i];
				flag=true;
				break;
			}//在已有的人里找，找的到就加他的分数。
		}
		if(!flag)
		{
			a[++top].s=k[i];
			a[top].sum+=m[i];
		}//找不到总人数top就加1，记录他的分数和名字
	}
	for(int i=1;i<=top;i++)
	{
		maxn=max(a[i].sum,maxn);
	}//在最后已经确定的分数里面寻找最大值
	int zok=0;//这里的zok同上文的top作用是一样的。
	for(int i=1;i<=n;i++)
	{
		flag=false;
		for(int j=1;j<=zok;j++)
		{
			if(k[i]==b[j].g)
			{
				flag=true;
				b[j].cnt+=m[i];
				if(a[j].sum==maxn&&b[j].cnt>=maxn)
				{
					 cout<<a[j].s<<endl;
					 return 0;//这里的作用和第一次查找一样，只是多了这个步骤，如果这个人最后的分数最大，并且他现在的分数大于等于最大值，就输出他的名字。
				}
			}
			
		}
		if(!flag)
			{
				b[++zok].cnt+=m[i];
				b[zok].g=k[i];
				if(a[zok].sum==maxn&&b[zok].cnt>=maxn)
				{
					cout<<a[zok].s;
					return 0;
				}//千万注意第一次定义的时候也要判定！
			}
	}
	return 0;
}

```
题解到此结束，谢谢观看

---

## 作者：Idoyt (赞：5)

我看题解只有一份所以，本蒟蒻来发一份stl的代码，还请大佬们斧正QwQ
```cpp
#include<cstdio>
#include<iostream>
#include<map>
#include<string>
using namespace std;
int n,maxn,p;
struct node 
{
	string name;
	int grade;
}q[1005];
map <string,int> m,t;//映射qwq
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>q[i].name;
		scanf("%d",&q[i].grade);
		m[q[i].name]+=q[i].grade;
	}
	for(int i=1;i<=n;i++)if(m[q[i].name]>maxn)maxn=m[q[i].name];
	for(int i=1;i<=n&&!p;i++)
	{
		t[q[i].name]+=q[i].grade;
		if(m[q[i].name]==maxn&&t[q[i].name]>=maxn)p=i;
	}
	cout<<q[p].name;
	return 0;
}
```

---

## 作者：Loner_Knowledge (赞：4)

此题是一道字符串模拟题

---

此题的题意就是计算出最高分后，在最后得分为最高分的玩家们中，找那个过程分数最先大于等于最高分的玩家并输出他的名字。


此题的坑点在于**最先得到的分数大于等于最高分**这里，这代表在计算完最高分后还需要再重新进行一遍加分的过程，在过程中寻找答案。


可以用STL中的`map`来做，只需要`map<string,int>`就可以方便的写出代码，但如果不用STL就需要自定义指针。


非STL代码


```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int Inf=0x7FFFFFFF;
struct Map {
    int sum;
    int t;
    char *p_s;
}M[1002];        //这是一个栈，存储玩家名称和玩家的最后分数与过程分数
struct Data {
    char str[35];
    int score;
    Map *p_M;
}D[1002];
bool Check(const char *a,const char *b) {    //这是一个比较字符串的函数，如果不写也可以用strcmp代替
    if(strlen(a)!=strlen(b))
        return 0;
    for(int i=0;a[i];++i)
        if(a[i]!=b[i])
            return 0;
    return 1;
}
int main() {
    int n,m=0,Max=-Inf,p=0;        //Max取负数是由于有负数数据
    scanf("%d",&n);
    for(int i=1,j;i<=n;++i) {
        scanf("%s%d",D[i].str,&D[i].score);
        for(j=1;j<=m;++j)
            if(Check(M[j].p_s,D[i].str))    //在栈中查找
                break;
        D[i].p_M=&M[j];            //更新指针
        M[j].p_s=D[i].str;        //更新指针
        M[j].sum+=D[i].score;    //更新总分数
        if(j>m)        //如果j>m代表当前栈内没有该玩家
            ++m;    //入栈
    }
    for(int i=1;i<=m;++i)
        if(M[i].sum>Max)
            Max=M[i].sum;    //在总分数计算完后寻找最大值
    for(int i=1;i<=n&&!p;++i) {
        D[i].p_M->t+=D[i].score;
        if(D[i].p_M->sum==Max&&D[i].p_M->t>=Max)    //在最后得分为最高分的玩家中，寻找过程分数最先大于等于最高分的玩家
            p=i;    //一旦赋值为i，i必定非零，由于循环的!p条件自动跳出循环
    }
    printf("%s",D[p].str);
    return 0;
}
```

STL代码


```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;        //皆同上所述
const int Inf=0x7FFFFFFF;
struct Data {
    string str;
    int score;
}D[1002];
map<string,int> m,t;
int main() {
    int n,Max=-Inf,p=0;
    scanf("%d",&n);
    for(int i=1,num;i<=n;++i) {
        cin>>D[i].str;
        scanf("%d",&D[i].score);
        m[D[i].str]+=D[i].score;
    }
    for(int i=1;i<=n;++i)
        if(m[D[i].str]>Max)
            Max=m[D[i].str];
    for(int i=1;i<=n&&!p;++i) {
        t[D[i].str]+=D[i].score;
        if(m[D[i].str]==Max&&t[D[i].str]>=Max)
            p=i;
    }
    cout<<D[p].str;
    return 0;
}
```

---

---

## 作者：jojoxie (赞：3)

看到题解里基本都是用STL做的，于是我来发一个不用STL的做法（也可以理解为C语言的做法）。

看到数据范围$n<=1000$于是很开心，我们要做的就是非常暴力地去做。

![](https://cdn.luogu.com.cn/upload/pic/46014.png)

emm。。。这只是个草图。

那么我们来愉快地看下代码

```
#include <stdio.h>
#include <string.h>

int a[1005], f[1005], f2[1005];//a数组记录每局游戏的加分，
//f数组记录每个人的最终得分，
//f2数组用于最大值不止一个时，记录每个人过程中的得分
char d[1005][40], mp[1005][40];

int main(){
	int n, m = 0;//m记录有几个人
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		scanf("%s%d", mp[i], &a[i]);
		int j;
		for(j=1; j<=m; j++){
			if(!strcmp(mp[i], d[j])){//如果mp[i]与d[j]是同样的字符串（即这个人的分数已经有记录了）
				f[j] = f[j] + a[i];//加上本局得分
				break;
			}
		}
		if(j == m + 1){//如果从未对这个人进行记录
			m++;//人数增加
			strcpy(d[m], mp[i]);//将字符串mp[i]赋值给字符串d[m]
			f[m] = a[i];
		}
	}
	
	int ans = 1;//记录最大值出现次数
	int ma, maxn = 0;//ma为最大值编号，maxn为最大值
	for(int i=1; i<=m; i++){
		if(f[i] > maxn){
			maxn = f[i];
			ma = i;
			ans = 1;
		}
		else{
			if(f[i] == maxn){
				ans++;
			}
		}
	}
	if(ans == 1){//如果最大值只出现一次
		printf("%s\n", d[ma]);//直接输出
	}
	else{
		for(int i=1; i<=n; i++){//回顾游戏过程（也就是把分重新算一遍）
			for(int j=1; j<=m; j++){//与开头类似的做法
				if(!strcmp(d[j], mp[i])){
					f2[j] = f2[j] + a[i];
					if(f2[j] >= maxn && f[j] == maxn){
                    //如果此人当前分数大于等于最大值，并且最终分数为最大值
						printf("%s\n", d[j]);//他就是获胜者
						return 0;
					}
				}
			}
		}
	}
	
	return 0;
}
```

---

## 作者：HyperLuXury (赞：1)

大家都用了C++，其实C++做这道题很方便，可以直接MAP映射，pascal就比较麻烦，不过也可以做，核心思想就是：先读入，读入的同时把这个人的名字存在a数组中，分数存在b数组中，c数组和d数组比较难懂，c[i,j]代表第i个人的第j次操作是排在第c[i,j]个的，d[i,j]代表第i个人的第j次操作的值是d[i,j]，代码如下：
```pascal
var n,i,j,x,y,w,max1,max2:longint;s,s1:string;
c,d:array[1..1000,0..1000] of longint;
b,e:array[1..1000] of longint;
a:array[1..1000] of string;
function find(s:string):longint;//此函数的作用是寻找s这个名字在a数组的第几个，找不到则返回0
var i:longint;
begin
for i:=1 to w do
  if a[i]=s then
    exit(i);
exit(0);
end;
begin
readln(n);
for i:=1 to n do
  begin
  readln(s);
  s1:=copy(s,pos(' ',s)+1,length(s)-pos(' ',s));
  delete(s,pos(' ',s),length(s)-pos(' ',s)+1);val(s1,x);y:=find(s);
  if y=0 then
    begin
    inc(w);a[w]:=s;b[w]:=x;c[w,0]:=1;c[w,1]:=i;d[w,0]:=1;d[w,1]:=b[w];//找不到，新添加一个人
    end
  else
    begin
    inc(c[y,0]);inc(d[y,0]);b[y]:=b[y]+x;c[y,c[y,0]]:=i;d[y,c[y,0]]:=b[y];//找到了，在原有基础上继续操作
    end;
  end;
for i:=1 to n do
  if b[i]>max1 then
    max1:=b[i];
for i:=1 to n do
  for j:=1 to d[i,0] do
    if d[i,j]>=max1 then
      begin
      e[i]:=c[i,j];break;
      end;
max1:=0;
for i:=1 to n do
  if b[i]>max1 then
    begin
    s:=a[i];max1:=b[i];max2:=e[i];
    end
  else if (b[i]=max1) and (e[i]<max2) then
    begin
    s:=a[i];max1:=b[i];max2:=e[i];
    end;
writeln(s);
end.

```


---

## 作者：xiaohuang (赞：1)

[更好的阅读体验](https://xiaohuang888.github.io/2019/07/20/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces2A%20Winner)

### Description in Chinese

在`Berland`流行着纸牌游戏“`Berlogging`”，这个游戏的赢家是根据以下规则确定的：在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在“名称和得分”行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。如果在比赛结束时只有一名玩家分数最多，他就是获胜者。如果两名或两名以上的玩家在比赛结束时都有最大的分数$m$，那么其中首先获得至少$m$分的玩家胜利。开始时，每个玩家都是$0$分。保证在比赛结束时至少有一个玩家的分数为正。

### Solution

把每个人的得分存到$\texttt{map}$里，然后求出最大得分，再寻找最先到达最大得分的人，即为获胜者。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>

using namespace std;

const int INF = 0x3f3f3f3f, MAXN =  1005;
int n, a[MAXN];
string name[MAXN];
map<string, int> Map1, Map2;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> name[i] >> a[i];
        Map1[name[i]] += a[i];
    }//映射到map里
    int Max = -INF;
    for (int i = 0; i < n; i++)
        if (Map1[name[i]] > Max) Max = Map1[name[i]];//求出最大得分
    for (int i = 0; i < n; i++) {
        Map2[name[i]] += a[i];
        if (Map2[name[i]] >= Max && Map1[name[i]] >= Max) {
            cout << name[i] << endl;//输出最先到最大得分的人
            return 0;
        }
    }
    return 0;
}
```

---

