# Little Pigs and Wolves

## 题目描述

在一个大小为$n*m$的二维网格里有几只猪和几只狼，这个网格里每一个单元只包含一只猪或一只狼。

如果猪和狼在同一条公共边上，则我们就说他们相邻。因为小猪怕狼，所以每只猪旁边只可能会有一只狼，但是每只狼旁边可能会有好几头猪。

狼将选择其中与其相邻的一头并吃掉，此过程将不再重复。也就是说，一头狼只能吃一头猪，而小猪在被吃掉后会消失且不能被别的狼吃。

求最多有多少只猪会被狼吃掉。

## 样例 #1

### 输入

```
2 3
PPW
W.P
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
P.W
.P.
W.P
```

### 输出

```
0
```

# 题解

## 作者：Eason_AC (赞：2)

## Content
有一张 $n\times m$ 的地图，其中，$\texttt{P}$ 代表小猪，$\texttt{W}$ 代表狼。如果狼的上下左右有一头以上的小猪，那么它会吃掉其中相邻的任意一头小猪（**此过程不再重复**）。求有多少头小猪会被狼吃掉。

**数据范围：$1\leqslant n,m\leqslant 10$。**
## Solution
如果 $n,m$ 的范围很大，那么 @123456zmy 巨佬的 $\texttt{Dinic}$ 算法无疑是一个绝佳的选择。

然而，这题目中 $n,m$ 的范围实在小到可怜，我们为什么不直接暴力模拟呢？如果仔细看题的话不难发现，这道题目实质上就是想问你有多少匹狼能够吃到小猪。所以，我们可以记录下来每一匹狼的位置，然后遍历每个狼的上下左右是否会有小猪，有的话那么这匹狼就能够吃到一头小猪，记录答案之后输出就好了。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
int n, m, xwolf[107], ywolf[107], cnt, ans;
char s[17][17];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= m; ++j)
			if(s[i][j] == 'W')	xwolf[++cnt] = i, ywolf[cnt] = j;
	}
	for(int i = 1; i <= cnt; ++i)
		for(int j = 0; j < 4; ++j)
			if(s[xwolf[i] + dx[j]][ywolf[i] + dy[j]] == 'P') {
				ans++;
				break;
			}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：123456zmy (赞：2)

题意：  
在一个 $n*m$ 的地图上，'W'表示狼，'P'表示猪，每只狼可以吃它周围的猪，每只猪只能被吃一次，每只狼也只吃一只猪，问一次最多会有几只猪被吃。
___
~~这不就是二分图匹配的板题，Ctrl+C过来就好了。~~

源点向每只狼连流量为 $1$ 的边，确保每只狼只会吃一只猪；每只狼向四周的猪连流量为 $1$ 的边，如果这条边上有流量则表示这只狼吃了这只猪；每只猪再向汇点连流量为 $1$ 的边，确保每只猪只会被吃一次，建完图跑网络流。

代码：(Dinic，~~码风极度邪教~~)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,t,a[200001],a1[200001],a2[10001],a5[200001],ans,a4[10001],an;
bool vis[10001];
string _s[15];
queue<int> q,q1;
bool bfs()
{
	memset(a4,0,sizeof(a4));
	q=q1;
	int a3,q2=1;
	q.push(s);
	while(!q.empty())
	{
		a3=a2[q.front()];
		while(a3)
		{
			if(a4[a[a3]]==0&&a5[a3]&&a[a3]!=s)
			{
				++q2;
				a4[a[a3]]=a4[q.front()]+1;
				q.push(a[a3]);
			}
			a3=a1[a3];
		}
		q.pop();
	}
	return (bool)a4[t];
}
long long dfs(int i,long long w)
{
	if(i==t)
	{
		ans+=w;
		return w;
	}
	if(a4[i]>=a4[t])return 0;
	vis[i]=1;
	int a3=a2[i],w1=0,w2;
	while(a3)
	{
		if(w==0)
		{
			vis[i]=0;
			return w1;
		}
		if(vis[a[a3]]==0&&a4[a[a3]]==a4[i]+1)
		{
			w2=dfs(a[a3],min(w,(long long)a5[a3]));
			w1+=w2;
			a5[a3]-=w2;
			w-=w2;
			a5[a3^1]+=w2;
		}
		a3=a1[a3];
	}
	vis[i]=0;
	return w1;
}
void add(int u,int v,int w)
{
	++an;
	a[an<<1]=v;
	a1[an<<1]=a2[u];
	a2[u]=an<<1;
	a[an<<1|1]=u;
	a1[an<<1|1]=a2[v];
	a2[v]=an<<1|1;
	a5[an<<1]=w;
}
int main()
{
	s=111;t=112; 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)cin>>_s[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	{
		if(_s[i][j-1]=='W')
		{
			add(s,i*10+j-1,1);
			if(_s[i][j]=='P')add(i*10+j-1,i*10+j,1);
			if(_s[i][j-2]=='P')add(i*10+j-1,i*10+j-2,1);
			if(_s[i+1][j-1]=='P')add(i*10+j-1,i*10+10+j-1,1);
			if(_s[i-1][j-1]=='P')add(i*10+j-1,i*10-10+j-1,1);
		}
		else if(_s[i][j-1]=='P')add(i*10+j-1,t,1);
	}
	while(bfs())dfs(s,0x3f3f3f3f3f3f3f3f);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：juruojjl_ (赞：1)

一开始没看懂题意以为要拿很深奥的方法去解~~蒟蒻也不懂什么是网络流~~

诶？$n,m$小于等于10？

跑一遍数组不就好了
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0;
char matrix[15][15];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>matrix[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(matrix[i][j]!='W') continue;  //如果不是狼就跳过
			if(matrix[i+1][j]=='P'||matrix[i-1][j]=='P'||matrix[i][j+1]=='P'||matrix[i][j-1]=='P') ans++;  //只能吃一头猪，所以只需要+1就好了
		}
	cout<<ans;
	return 0;
}
```

# 拓展部分：

等会

虽然说这个代码交上去AC了

但是！！！

如果你们拿上面那个代码去运行的话

看下面的数据：

```
3 3
...
WPW
...
```

虽然题目说了一只猪旁边不可能有几只狼

但我们还需要考虑上面那种情况

万一哪一天有人给你出了这么道题目呢？

你会发现运行上面的样例结果是2！

但是实际上运行结果应该是1！

>也就是说，一头狼只能吃一头猪，而小猪在被吃掉后会消失且不能被别的狼吃。

所以我们应该标记一下被吃掉的猪

处理上面那种情况的正解如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0;
char matrix[15][15];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>matrix[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(matrix[i][j]!='W') continue;
			if(matrix[i+1][j]=='P')
			{
				ans++;
				matrix[i+1][j]='.';
			}
			else if(matrix[i-1][j]=='P')//一定要用else if!!!否则就和上面的情况一样了！
			{
				ans++;
				matrix[i-1][j]='.';
			}
			else if(matrix[i][j+1]=='P')
			{
				ans++;
				matrix[i][j+1]='.';
			}
			else if(matrix[i+1][j]=='P')
			{
				ans++;
				matrix[i][j-1]='.';
			}
		}
	cout<<ans;
	return 0;//结束
}
```

---

## 作者：PersistentLife (赞：1)

我有个疑问：这题要跑 Dinic 吗？

其实不要的，因为每一只猪的旁边只有一只狼，所以不用考虑两头狼“抢食物”那种情况，如下面的例子：

```
3 3
WpP
.W.
..W
```

我特地将一个 `P` 小写了，这是让大家很容易看出这头猪很“无助”，因为它会被两头狼“抢”着吃，123456zmy 大佬的代码是可以处理这种情况的。

我们再看一眼题目：there will be at most one wolf adjacent to each little pig，翻译过来就是一只猪的旁边（上下左右）只有一只狼，所以开数组统计就行啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
char g[15][15];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
			cin>>g[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(g[i][j]!='W') continue;
			if(g[i+1][j]=='P'||g[i-1][j]=='P'||
			g[i][j+1]=='P'||g[i][j-1]=='P') ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

一个问题的解答（如果不想看的话可以跳过）：

Q：网络流算法怎么解决？

A：我们新增一个源点 $S$ 和汇点 $T$，将 $S$ 与每只狼连边，将每一只狼与每一只与其相邻的猪连边，将每一只猪与 $T$ 连边，所有边的流量为 $1$ 且为有向边，然后跑最大流（EK 和 Dinic 均可），此时每一只猪只能被一只狼吃，因为每只猪猪和汇点通过的流量最大为 $1$，如果有两只狼去吃的话，那么流量为 $2$，此时就可以把这种“吃法”舍去，所以这个最大流算法是正确的。

---

## 作者：精神小伙！ (赞：0)

## 思路

由于 $ n $，$ m $ 的范围很小，只需要模拟即可。

遍历每个狼周围的四个格子里有没有小猪，有的话就把答案加一，最后输出累加后的结果。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
char s[20][20];
int main()
{
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	    for(int j=1;j<=m;++j)
	        cin>>s[i][j];
	for(int i=1;i<=n;++i)
	    for(int j=1;j<=m;++j)
	    {
	    	if(s[i][j]=='W') 
	    	    if(s[i+1][j]=='P'||s[i-1][j]=='P'
				||s[i][j+1]=='P'||s[i][j-1]=='P') ans++;
		}
	cout<<ans<<endl;
	return 0; 
}
```

---

## 作者：Tipsy_bamboo (赞：0)

## 思路
由于数据范围很小我们可以直接模拟。把整个地图里的每一个点都遍历一遍，如果这一个点是狼，而且周围四个格子里有小猪，那么答案就加一。因为题目保证了每个小猪周围四个格子里最多出现一只狼，所以不会出现一只狼吃完了，另一只狼就没有了的情况。使这一题的复杂度大大降低。
## 代码奉上（千万不要抄袭）
```cpp
#include<bits/stdc++.h>
using namespace std;
int pg[15][15];
int main()
{
	int n, m, ns = 0;
	string s;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		cin >> s;
		for(int j = 0; j < m; ++j) 
		{
			switch(s[j])
			{
				case 'W':
					pg[i][j + 1] = 2;
					break;
				case 'P': 
					pg[i][j + 1] = 1;
					break;
				default:
					pg[i][j + 1] = 0;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(pg[i][j] == 2 && (pg[i - 1][j] == 1 || pg[i][j - 1] == 1 || pg[i][j + 1] == 1 || pg[i + 1][j] == 1)) ++ns;
		}
	}
	printf("%d", ns);
	return 0;
}
```

---

## 作者：dang_dang (赞：0)

今天，我将用Python语言来完成这道题。
# 基础理解
### 题意分析
这道题要求输入一个$n * m$大小的矩阵，其中，```P```代表猪而```W```代表狼。狼会吃与它有**相邻边的猪。**此时，题目还还告诉我们，一头猪身边最多只能有1头狼，所以不用考虑有关到底这头猪该被那一头狼吃的问题。这就是为啥它是这样简单的原因！
### 简化版题意：
输入一个$n * m$大小的一个列表，问列表中，有几个```P```元素旁边有```W```字符
### 思路
然后，就是一些思路，本人亲测，暴力是可以全部AC的。我们用一个数组，$arr[i][j]$就是在第$i$行$j$列是猪、狼或空。

顺便说一句，输入数据的时候可以考虑使用map()函数来进行输入,如"x,y=map(int,array)"
其中，int可以代表任意一种数据类型（对象），只要它可以强制转换array中的每一个数据。
# 最后是代码
## Python3

```python
from sys import exit
n,m=map(int,input().split())
arr=[]
for i in range(n):
    arr.append([])
    string=input()
    for j in range(m):
        arr[i].append(string[j]) ##输入数据
eaten=0
for i in range(n):
    for j in range(m):
        if arr[i][j]=="W": ##这里有狼底下的是判断程序，判断狼的身边是否有猪，
            if i<n-1:
                if arr[i+1][j]=="P":
                    eaten+=1
                    arr[i+1][j]='.'##那个点的猪被吃掉了，把该点变成空
                    continue
            if i>0:
                if arr[i-1][j]=="P":
                    eaten+=1
                    arr[i-1][j]='.'
                    continue
            if j<m-1:
                if arr[i][j+1]=="P":
                    eaten+=1
                    arr[i][j+1]='.'
                    continue
            if j>0:
                if arr[i][j-1]=="P":
                    eaten+=1
                    arr[i][j-1]='.'
                    continue
print(eaten) ##输出最后的结果
exit(0) ##进程结束
```
## 顺便再发一下C++的代码
```	cpp
#include<iostream>
using namespace std;
#define MAXN 11
char arr[MAXN][MAXN];
int main() 
{
	int n,m;
	int eaten=0;
	cin>>n>>m;
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) 
	{
		cin>>arr[i][j]; //输入，没啥好讲的 
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(arr[i][j]!='W') //这里只讨论狼 
			{
				continue;
			}
			if(i+1<n) if(arr[i+1][j]=='P')
			{
				eaten++;
				arr[i+1][j]='.';
				continue;
			}
			if(i-1>=0) if(arr[i-1][j]=='P')
			{
				eaten++;
				arr[i-1][j]='.';
				continue;
			}
			
			if(j+1<m) if(arr[i][j+1]=='P')
			{
				eaten++;
				arr[i][j+1]='.';
				continue;
			}
			if(j-1>=0)if(arr[i][j-1]=='P')
			{
				eaten++;
				arr[i][j-1]='.';
				continue;
			}
		}
	}
	cout<<eaten;
	return 0;
	
}

---

