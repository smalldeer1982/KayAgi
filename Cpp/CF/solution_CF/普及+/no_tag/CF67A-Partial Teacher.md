# Partial Teacher

## 题目描述

A teacher decides to give toffees to his students. He asks $ n $ students to stand in a queue. Since the teacher is very partial, he follows the following rule to distribute toffees.

He looks at the first two students and gives more toffees to the student having higher marks than the other one. If they have the same marks they get the same number of toffees. The same procedure is followed for each pair of adjacent students starting from the first one to the last one.

It is given that each student receives at least one toffee. You have to find the number of toffees given to each student by the teacher such that the total number of toffees is minimum.

## 样例 #1

### 输入

```
5
LRLR
```

### 输出

```
2 1 2 1 2
```

## 样例 #2

### 输入

```
5
=RRR
```

### 输出

```
1 1 2 3 4
```

# 题解

## 作者：谦谦君子 (赞：5)

这只是一道A题（~~虽然我打了快半小时还没过样例emmm~~）
## 题目大意：
一共有N个人站成一排，对应每相邻的两个人都能确定两个人分到的糖果数谁更多，保证每个人必须至少分配一个糖的情况下，求怎样分配能够满足条件并且分配的糖果总数最少。
## 思路：
我们用一个candy[i] 表示第i个小朋友的糖果，则：

- 若字符为R，则candy[i]=candy[i-1]+1;
- 若字符为L，则candy[i]=1，此时如果candy[i-1]也是1，那么对应向前推进，candy[i-1]+1
- 若字符为=，则candy[i]=candy[i-1]


## 代码：

```
#include<bits/stdc++.h>
using namespace std;
int candy[10001];
string s;
int main()
{
	int n;
	cin>>n;
	candy[0]=1;
	cin>>s;
	s='%'+s;
	for (int i=1;i<n;i++)
	{
		if (s[i]=='=')
		{
			candy[i]=candy[i-1];
		}
		if (s[i]=='R')
		{
			candy[i]=candy[i-1]+1;
		}
		if (s[i]=='L')
		{
			candy[i]=1;
			if (candy[i-1]==1)
			{
				candy[i-1]++;
				for (int j=i-1;j>=1;j--)
				{
					if (s[j]=='=')
					{
						candy[j-1]=candy[j];
					}
					else if (s[j]=='L'&&candy[j-1]==candy[j])
					{
						candy[j-1]++;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<candy[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：0xFF (赞：4)

### 题目分析

差分约束的裸题

这题一看题干就是标准的差分约束，再仔细一看题号，等等，这题竟然是CF的A题~~A题就这么难的吗~~……
想了 $10$ 多分钟还是没有什么简单的思路，只好打了一个差分约束的板子，一遍就过了。

思路还是比较清晰的，首先设第 $i$ 个人糖果数量为 $t_i$，只需要分三种情况讨论：

- 当第 $i$ 个人和第 $i+1$ 个人糖一样多，则 $t_i - t_{i+1} \le 0$ 且 $t_{i+1}-t_i \le 0$，要连两条边。

- 当第 $i$ 个人比第 $i+1$ 个人糖多，则 $t_{i+1}-t_i\le -1$。

- 当第 $i$ 个人比第 $i+1$ 个人糖少则同理上面的情况。

只需要跑一边差分约束的板子就能过了
### code:
```cpp
#include<iostream>
#include<queue>
using namespace std;
const int maxn = 1e5 + 10;
int n,head[maxn],cnt;
struct node{
	int to,next,val;
}edge[maxn<<2];
void addedge(int u,int v,int w){
	edge[++cnt].to = v;
	edge[cnt].val  = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int dis[maxn];
bool vis[maxn];
queue<int> q;
void spfa(){
	dis[0] = 1;
	q.push(0);
	vis[0] = true;
	while(!q.empty()){
		int u = q.front();
		vis[u] = false;
		q.pop();
		for(int i=head[u];i;i=edge[i].next){
			int v = edge[i].to , w = edge[i].val;
			if(dis[v] < dis[u] + w){
				dis[v] = dis[u] + w;
				if(!vis[v]){
					q.push(v);
					vis[v] = true; 
				}
			}
		}
	} 
}
int main(){
	n = read();
	for(int i=1;i<=n;i++){
		addedge(0,i,0);
	}
	for(int i=1;i<n;i++){
		char s;
		cin >> s;
		if(s == '=') addedge(i,i+1,0) , addedge(i+1,i,0);
		else if(s == 'L') addedge(i+1,i,1);
		else if(s == 'R') addedge(i,i+1,1); 
	}
	spfa();
	for(int i=1;i<=n;i++){
		printf("%d ",dis[i]);
	}
	printf("\n");
	return 0;
}
```



---

## 作者：_Legacy (赞：3)

#### 错误样例
我们先看一个根据题意得出的错误代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[1000];//关系字符
	int b[1000],n;//成立的表
	cin >> n;
	cin >> a;
	for(int i=0;i<n;i++) b[i]=1;//原来都是1
	for(int i=0;i<n-1;i++){
		if(a[i]=='L'&&b[i]<=b[i+1]) b[i]=b[i+1]+1;
		else
			if(a[i]=='R'&&b[i+1]<=b[i]) b[i+1]=b[i]+1;
	}//根据题意得出的判断
	
	for(int i=0;i<n;i++) cout << b[i] << " ";
} 
//CF67A	
```

[听取WA声一片](https://www.luogu.com.cn/record/32717358)

##### 错误分析

首先先看一个样例：

输入：

```
5
LLLL
```
代码输出：

`2 2 2 2 1`

答案：

`5 4 3 2 1`

这是因为从左到右的顺序导致的错误：


1. 2 1 1 1 1 //L要求左>右，所以$b_1=b_2+1$
2. 2 2 1 1 1 //L要求左>右，所以$b_2=b_3+1$
3. 2 2 2 1 1 //L要求左>右，所以$b_3=b_4+1$
4. 2 2 2 2 1 //L要求左>右，所以$b_4=b_5+1$

(要是从右往左便不会这样，当然也有其他不一定的情况)

但是要是给
```
for(int i=0;i<n-1;i++){
	if(a[i]=='L'&&b[i]<=b[i+1]) b[i]=b[i+1]+1;
	else
		if(a[i]=='R'&&b[i+1]<=b[i]) b[i+1]=b[i]+1;
}
```
循环$n-1$遍则不会出现错误，因为（有做省略）：

1. 2 2 2 2 1
2. 3 3 3 2 1 //发现前三个不成立前一个大于后一个
3. 4 4 3 2 1 //发现前二个不成立前一个大于后一个
4. 5 4 3 2 1 //发现前一个不成立前一个大于后一个

#### 正确代码

（加上了关系符号为‘=’的情况）

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[1000];
	int b[1000],n;
	cin >> n;
	cin >> a;
	for(int i=0;i<n;i++) b[i]=1;
	for(int i=0;i<n;i++){
		for(int i=0;i<n-1;i++){
			if(a[i]=='L'&&b[i]<=b[i+1]) b[i]=b[i+1]+1;
			else
				if(a[i]=='R'&&b[i+1]<=b[i]) b[i+1]=b[i]+1;
				else
					if(a[i]=='='&&b[i+1]!=b[i]){
						if(b[i]>b[i+1]) b[i+1]++;
						else b[i]++;
					}			
		}
	}
	for(int i=0;i<n;i++) cout << b[i] << " ";
} 
//CF67A
```









---

## 作者：xiaorui2007 (赞：2)

## 前言
这是一个**非图论**、$O(n)$ 的题解。
## 审题
不妨让 $s_i,2\le i\le n$ 表示 $a_{i-1}$ 与 $a_i$ 的关系（**这与题中描述不一样**），设 $s_1$ 为 “R”。  
首先，因为要求和最小，所以对于每一段连续的“L”（包括与该段相邻的“=”，以下称为 L 串，类似定义 R 串，“=”优先在 R 串中），最后一个（$s_i$ 对应的 $a_i$）一定为 $1$（括号中下文大概率省略）。  
故，对于每个 R 串（除了 $s_1$），第一个一定是 $1$ 或 $2$，“=”对应 $1$，“R”对应 $2$。
## 思路
先处理每个 R 串，倒序后原 L 串变成了 R 串，再处理。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005];
string s;

int main()
{
	a[1]=1;
	cin>>n>>s;
	s="00"+s;//让字符串偏移 
	for(int i=2;i<=n;i++)//处理R串
		if(s[i]=='=')
			a[i]=max(a[i-1],1);
		else
			if(s[i]=='R')
				a[i]=max(a[i-1],1)+1;
	for(int i=n,fl=0/*因为只处理原L串，所以要记录是否在原L串*/;i>=1;i--)//倒序
		if(fl)
		{
			if(s[i+1]=='=')
				a[i]=a[i+1];
			else
				a[i]=max(a[i+1]+1,a[i]/*处理原L串R串衔接处*/);
			if(s[i]=='R')
				fl=0;//到了R串，退出
		}
		else
			if(s[i]=='L')
			{
				fl=1;
				a[i]=1;
			}
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：Fengyiwei1234 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF67A)


# 思路

我们用$\ {f}_{i}\ $表示第$\ i\ $位小朋友的糖果。

分类讨论：

1. 如果当前字符是 $\verb!=!$，那么容易得出$\ {f}_{i}={f}_{i-1}$。

1. 如果当前字符是 $\verb!R!$，那么在能确保$\ {f}_{i-1}\ $最小的情况下，${f}_{i}\ $的最小值为$\ {f}_{i-1}+1$。

1. 如果当前字符是 $\verb!L!$，那么右边比左边小，令右边是$\ 1$，但是要特判左边也等于$\ 1\ $的情况哦~~~

AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int f[10005]={1},n;
int main()
{
    string s;
    cin>>n;
    cin>>s;
    s='#'+s;
    for(int i=1;i<n;i++)
    {
        if(s[i]=='=')f[i]=f[i-1];
        else if(s[i]=='R')f[i]=f[i-1]+1;
        else if(s[i]=='L')
        {
            f[i]=1;
            if(f[i-1]==1)//特判
            {
                f[i-1]=2;
                for(int j=i-1;j>=1;j--)
                {
                    if(s[j]=='=')f[j-1]=f[j];
                    else if(s[j]=='L'&&f[j-1]==f[j])f[j-1]++;
                    else break;
                }
            }
        }
    }
    for(int i=0;i<n;i++)cout<<f[i]<<" ";
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/109887598)

---

## 作者：FrozenDream (赞：1)

~~绿题居然这么水~~

------------

### 引言：
这道题题目描述就已经很清晰了，我们直接进入正题。

------------
### 思路：
从后往前遍历字符串，$\verb!=!$ 和 $\verb!L!$ 的情况好处理，当字符为 $\verb!=!$ 时，直接把此时的 $ans_i$ 赋值为 $ans_{i+1}$,当字符为 $\verb!L!$ 时，就把此时的 $ans_i$ 赋值为 $ans_{i+1}+1$。

当字符为 $\verb!R!$ 时，就需要一点小小的特判了，我们要让此时的 $ans_i$ 尽可能的小，还要考虑它与还没有遍历到的数有没有冲突。

举个例子，当字符为 $\verb!R!$ 并且 $ans_{i+1}$ 为 $1$ 时，此时 $ans_i$ 不可能为 $0$，所以我们就要把 $ans_{i+1}$ 到 $ans_{n-1}$ 全部考虑一遍，看它们的值是否有变化，遍历的时候，当字符为 $\verb!=!$ 时，就要把此时的 $ans_{j+1}$ 赋值为 $ans_j$，因为 $ans_j$ 先调整数据，所以就把顺序反了过来；当字符为 $\verb!R!$ 并且 $ans_j \ge ans_{j+1}$ 时，显然不符合题目要求，要满足和最小，就让 $ans_{j+1}$ 比 $ans_j$ 多 $1$ 就行了；当字符为 $\verb!L!$ 时，因为它本来就满足条件，并且当两项加 $1$ 后条件也是满足的，所以不用考虑。

------------
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[1005];
string a;
int main(){
	cin>>n>>a;
	ans[n-1]=1;
	for(int i=n-2;i>=0;i--){
		if(a[i]=='='){
			ans[i]=ans[i+1];
		}else if(a[i]=='L'){
			ans[i]=ans[i+1]+1;
		}else{
			ans[i]=1;
			if(ans[i+1]==1){
				ans[i+1]=2;
				for(int j=i+1;j<n-1;j++){
					if(a[j]=='='){
						ans[j+1]=ans[j];
					}else if(a[j]=='R'){
						if(ans[j]>=ans[j+1]){
							ans[j+1]=ans[j]+1;
						}
					}
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<ans[i]<<" ";
	}
}
```

---

## 作者：Graphcity (赞：1)

## 思路

这道题可以用图论来做。

首先定义一个数组 $col$ 来标记每个数的颜色。如果出现等于号，则把相邻结点的颜色染成一样的，否则染成不一样的。这样，相等的情况就处理完了。

如果发现 $a_i > a_{i+1}$ ，那么就连一条从 $col_i$ 到 $col_{i+1}$ 的 **有向边** 即可。如果是小于，则连一条从 $col_{i+1}$ 到 $col_i$ 的边即可。边的意义是连接两个具有大于关系的数。

根据题目建的图肯定是一个有向无环图（ 因为不可能存在 $i$ 既大于 $j$ 又小于 $j$ 的情况 ），跑一遍 **拓扑排序** 即可。设 $dep_i$ 为第 $i$ 种颜色最小能够等于多少，那么就有

$$dep_i=1+\max_{Edge(i,j)}dep_j$$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1000;

struct Node
{
	int to,nxt;
} Edge[Maxn+5];
int tot,Head[Maxn+5];

inline void Addedge(int x,int y)
{
	Edge[++tot]=(Node){y,Head[x]};
	Head[x]=tot;
}

int n,nowc,col[Maxn+5];
int vis[Maxn+5],dep[Maxn+5],ind[Maxn+5]; //ind:存储入度
string s;

inline void dfs(int x) //拓扑排序
{
	if(vis[x]) return;
	dep[x]=1;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		dfs(y);
		dep[x]=max(dep[x],dep[y]+1);
	}
	vis[x]=1;
}

int main()
{
	scanf("%d",&n);
	cin>>s;
	col[n]=++nowc;
	for(register int i=n;i>1;--i)
	{
		char ch=s[i-2];
		if(ch=='L') //判断大小并染色
		{
			col[i-1]=++nowc;
			Addedge(col[i-1],col[i]);
			ind[col[i]]++;
		}
		else if(ch=='R')
		{
			col[i-1]=++nowc;
			Addedge(col[i],col[i-1]);
			ind[col[i-1]]++;
		}
		else col[i-1]=nowc;
	}
	for(register int i=1;i<=nowc;++i)
		if(!ind[i]) dfs(i);
	for(register int i=1;i<=n;++i)
		printf("%d ",dep[col[i]]);
	printf("\n");
	return 0;
}
```

---

## 作者：RainFestival (赞：1)

这道题我们可以用差分约束

当$a_i>a_{i+1}$时，从$i+1$向$i$连权值$1$的边

当$a_i<a_{i+1}$时，从$i$向$i+1$连权值$1$的边

当$a_i=a_{i+1}$时，从$i$向$i+1
$双向连权值$0$的边

由于$\forall a_i>0$，从超级源点$0$向每一个$a_i$连权值$1$的边

最后从超级源点$0$跑$spfa$最长路

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<queue>
int n,vis[1005],dis[1005],flag=0;
std::vector<int> a[1005],b[1005];
void add(int x,int y,long long v){a[x].push_back(y);b[x].push_back(v);}
void spfa(int s)
{
    std::queue<int> q;
    for (int i=0;i<=n;i++) vis[i]=0,dis[i]=-1000000000;
    dis[s]=0;vis[s]=1;q.push(s);
    while (!q.empty())
    {
        int v=q.front();q.pop();vis[v]=0;
        for (int i=0;i<a[v].size();i++) 
        {
            int u=a[v][i],s=b[v][i];
            if (dis[u]<dis[v]+s)
            {
            	dis[u]=dis[v]+s;
            	if (!vis[u]) q.push(u),vis[u]=1;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
    	char ch=' ';
		while (ch!='R'&&ch!='L'&&ch!='=') ch=getchar(); 
		if (ch=='L') add(i+1,i,1);
		if (ch=='R') add(i,i+1,1);
		if (ch=='=') add(i+1,i,0),add(i,i+1,0);
	}
    for (int i=1;i<=n;i++) add(0,i,1);
    spfa(0);
    for (int i=1;i<=n;i++) printf("%d ",dis[i]);
    printf("\n");
    return 0;
}
```

就可以了$AC$了

$QAQ$

---

## 作者：tanghairong (赞：0)

$a_i>a_{i+1}$，$a_i<a_{i+1}$，$a_i=a_{i+1}$ 之类的不等式，显然可以想到差分约束算法。

## 步骤 1：准备

先用一个超级源点 $0$，向每个点连边。

## 步骤 2：建图

#### 情况 $1$：$s_i$ 为 ```L```

即 $a_i$ 大于 $a_{i+1}$。

此时，易证令 $a_i=a_{i+1}+1$ 最优，因此从 $i+1$ 连向 $i$ 一条长度为 $1$ 的边即可。

#### 情况 $2$：$s_i$ 为 ```R```

即 $a_i$ 小于 $a_{i+1}$，亦即 $a_{i+1}$ 大于 $a_i$。

此时，易证令 $a_{i+1}=a_i+1$ 最优，因此从 $i$ 连向 $i+1$ 一条长度为 $1$ 的边即可。

#### 情况 $3$：$s_i$ 为 ```=```

即 $a_i$ 等于 $a_{i+1}$。

此时，从 $i$ 连向 $i+1$ 一条长度为 $0$ 的边，同时从 $i+1$ 连向 $i$ 一条长度为 $0$ 的边即可。

## 步骤 3：实现

以 $0$ 为起点跑一遍 SPFA 最长路即可。

## code

```
#include<iostream>
#include<queue>
using namespace std;
int n,to[100005],val[100005],nxt[100005],head[100005],cnt=0,dis[100005],vis[100005];
void add(int u,int v,int w){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
queue<int>q;
void SPFA(){
    dis[0]=1;
    q.push(0);
    vis[0]=1;
    while(!q.empty()){
        int u=q.front();
        vis[u]=0;
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i],w=val[i];
            if(dis[v]<dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v])q.push(v),vis[v]=1;
            }
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)add(0,i,0);
    for(int i=1;i<n;i++){
        char s;
        cin>>s;
        if(s=='=')add(i,i+1,0),add(i+1,i,0);
        if(s=='L')add(i+1,i,1);
        if(s=='R')add(i,i+1,1);
    }
    SPFA();
    for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
    return 0;
}
```

---

## 作者：Cuiyi_SAI (赞：0)

## 题目大意

给定一个状态数组 $s$ ,它描述了序列 $a$ 相邻两个数的相对大小关系 （对于 $s_i$，$[L]$ 表示 $a_i>a_{i+1}$，$[R]$ 表示 $a_i<a_{i+1}$，$[=]$ 表示 $a_i=a_{i+1}$）。

求一个满足 $s$ 的序列 $a$，使 $\sum\limits_{i=1}a_i$ 最小。

## 解题思路

考虑对于一个 $s_{i-1}$，

- 若其为 $=$，则 $a_i=a_{i-1}$。
- 若其为 $R$， 为了使序列之和尽量的小，$a_i$ 也当尽量小，因此有 $a_i=a_{i-1}+1$。

- 若其为 $L$，与上面同样的思路，我们应该使得 $a_i$ 最小，也就是 $a_i=1$。但是这种武断的赋值有可能会破坏原先序列 $a$ 之间的相对大小关系。

例如，如果以前的 $s$ 均为 $=$，则最优的 $a$ 应该是 $1,1,1\cdots1$，但是现在 $s_{i-1}=L$，因此 $a_i=1$，而此时的 $a$ 序列的相对大小关系显然与 $s$ 要求的不符。

因此，每当 $s_{i-1}=L$ ，我们先把 $a_i=1$，然后从后往前推，将因为 $a_i$ 改变而相对大小关系受到破会的每个 $a_{i-j}$，都逐个进行修改，以此保证 $a$ 的相对大小关系。

按照以上步骤分类讨论，我们可以得到所求的序列 $a$。

---

## CODE:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans[1010];
char a[1010];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	ans[1]=1;
	for(int i=2;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]=='L')
		{
			ans[i]=1;
			if(ans[i-1]==1)
			{
				ans[i-1]++;
				for(int j=i-1;j>=2;j--)
				{
					if(a[j]=='='&&ans[j-1]!=ans[j]) ans[j-1]=ans[j];
					else if(a[j]=='L'&&ans[j-1]<=ans[j]) ans[j-1]=ans[j]+1;
					else continue;
				}
			}
		}
		if(a[i]=='R') ans[i]=ans[i-1]+1;
		if(a[i]=='=') ans[i]=ans[i-1];
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```



---

## 作者：BreakPlus (赞：0)

### $\text{Part}1$ 差分约束做法

一看到这种可以建立不等式的题就用差分约束……

先来看一条我的笔记：

-----

求最大解的时候用最短路。设不等式为 $ a- b \le c$，连 $ b \to a$ 权值为 $c$ 的边。 $dis$ 数组初始化为 $-\infty$。

求最小解的时候用最长路。设不等式为 $ a - b \le c$，连 $ a \to b$ 权值为 $-c$ 的边。

-----


现在我们是求最小解当然用最长路。

设第 $i$ 个人糖果数量（下简称糖）为 $t_i$。

当第 $i$ 个人和第 $i+1$ 个人糖相等，则 $t_i - t_{i+1} \le 0$ 且 $t_{i+1}-t_i \le 0$ ，要连两条边。

当第 $i$ 个人比第 $i+1$ 个人糖多，则 $t_{i+1}-t_i\le -1$ 。

当第 $i$ 个人比第 $i+1$ 个人糖少同理。

连边之前我们建立一个超级源点 $0$ 号点，它连向所有人，所人的糖果数量都大于等于它。它的糖果数量为 $1$。

下面给一下参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,head[maxn],tot;
struct Edge{
	int to,w,nxt;
}edge[maxn];
void add(int u,int v,int w){
	tot++;
	edge[tot].to=v;
	edge[tot].w=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
int dis[maxn],vis[maxn]; queue<int>Q;
void longest_path(){
	dis[0]=1; Q.push(0); vis[0]=true;
	while(!Q.empty()){
		int x=Q.front(); vis[x]=false; Q.pop();
		for(int i=head[x];i;i=edge[i].nxt){
			int tmp=edge[i].to,val=edge[i].w;
			if(dis[tmp]<dis[x]+val){
				dis[tmp]=dis[x]+val;
				if(!vis[tmp]) Q.push(tmp),vis[tmp]=true;
			}
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		add(0,i,0);
	for(int i=1;i<n;i++){
		char s; cin>>s;
		if(s=='=') add(i,i+1,0),add(i+1,i,0);
		else if(s=='L') add(i+1,i,1);
		else if(s=='R') add(i,i+1,1);
	}
	longest_path();
	for(int i=1;i<=n;i++) cout<<dis[i]<<" ";
	cout<<endl;
	return 0;
}
```


### $\text{Part}2 \ \ \text{Topsort}$ 做法

写完上面的代码，发现这道题没让你判环，所以这竟然是无环的（除了相等的连边）。要用拓扑做的话要处理相等的。

有一种做法处理相等的：如果两个人的糖相等，那么互相连向互相连的边，显然问题 over（求 Hack）

具体代码没写过。

---

## 作者：Ba_creeper (赞：0)

## CF67A Partial Teacher 题解

#### 题目思路：

这道题主要思路是模拟，可以当成构造题来做。

需要注意判断在已经构造了一部分时，已经构造完毕的部分是否为最小值。

#### 题目分析：

先设 $a$ 数组来表示最终要输出的数字，则我们初始化 `a[n]=1`.

我们可以先把每个操作存进来，然后倒着往前进行操作。

当读到字符为 $=$ 时，`a[i]=a[i+1]`;

当读到字符为 $L$ 时，`a[i]=a[i+1]+1`;

当读到字符为 $R$ 时，此时不能单纯的减去1，要判断在这里我们已经构造完毕的数值是否为最小值。

如果是最小值，则 `a[i]=a[i+1]-1` ，否则，就要进行判断，若右边值是1就加1，以此类推。

#### 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
int a[1002],i,j,n;
char ch[1001];

void work(char cha) {
	if(cha=='=')
		a[i]=a[i+1];
	else if(cha=='L')
		a[i]=a[i+1]+1;
	else if(cha=='R') {
		a[i]=1;
		if (a[i+1]==1) {
			a[i+1]++;
			for (int j=i+1; j<=n; j++) {
				if (ch[j]=='=') {
					a[j+1]=a[j];
				} else if (ch[j]=='R'&& a[j+1]==a[j]) {
					a[j+1]++;
				} else {
					break;
				}
			}
		}
	}
}

int main() {
	cin>>n;
	for(i=1; i<n; ++i)
		cin>>ch[i];
	a[n]=1;
	now=n;
	for(i=n-1; i>=1; --i)
		work(ch[i]);
	for(i=1; i<=n; ++i)
		cout<<a[i]<<" ";
	return 0;
}
```



---

