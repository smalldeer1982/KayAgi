# [PA 2020] Skierowany graf acykliczny

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 5 [Skierowany graf acykliczny](https://sio2.mimuw.edu.pl/c/pa-2020-1/dag/)**

正如名字所示，有向无环图（*Directed Acyclic Graph*，简称 DAG）是一个无环的有向图。

如果我们在这样一个图中选择两个节点，我们可以计算出这些节点之间存在多少条不同的有向路径。如果其中一条路径包含一条边而另一条不包含这条边，我们就认为这两条路径是不同的。

你的任务是构造一个 $n$ 个节点（编号从 $1$ 到 $n$）的有向无环图，其中从节点 $1$ 到节点 $n$ 正好有 $k$ 条路径。你的图最多可以有 $100$ 个节点，每个节点最多可以有两条出边，而且不能包含重边（即如果一个节点有两条出边，它们必须通向不同的节点）。可以证明，对于每一个满足输入中约束条件的 $k$，都可以构造一个满足条件的图。

## 说明/提示

#### 样例 1 解释

下图展示了输出中 $6$ 个节点的有向无环图，从 $1$ 到 $6$ 有三条路径：$1\to 3\to 2\to 6,1\to 3\to 6$ 和 $1\to 5\to 6$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hinzei5g.png)

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le k\le 10^9$，$2\le n\le 100$。

## 样例 #1

### 输入

```
3```

### 输出

```
6
3 5
6 -1
2 6
2 6
6 -1
-1 -1```

# 题解

## 作者：mayike (赞：11)

### [题目传送门](https://www.luogu.com.cn/problem/P9101)

一道思维题。

## 思路

由于每个点只能连两条出边，而不同路径数又是从前面累加的(这里规定编号从小到大，更方便，毕竟谁也不喜欢乱编号吧)，$k \le 10^9$。

我突发奇想可以用二进制来累加成 $k$，具体如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/202u0dsz.png)

一个点有且至少一条，至多两条入边，即为路径数的累加。以此，对于节点 $i$ 为奇数，$i,i+1$ 的路径数皆为 $2^{(i+1)/2-1}$，那么，对于前 $2 \times i$ 个数，可以让第 $2 \times i + 1$ 个数至多累加成 $2^i-1$ 条不同路径数，那么也就可以累加成 $1$ 到 $2^i-1$ 之间的所有数(知道 $2^0 + 2^1 + 2^2 + \dots + 2^n$ 与 $1$ 到 $2^n$ 之间的关系的应该明白)。所以，即使当 $k=10^9$ 时，$i=31$ 也能使路径条数累加到 $k$，此时 $\min(n)=62 \le 100$ 显然是满足的。并且连边的规律我们自然也懂了。 

### ~~点个赞再走啊~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll k,sum[101],cnt,num,n,ab,a[101]; 
int main(){
//	freopen("s.in","r",stdin);
//	freopen("s.out","w",stdout);
    scanf("%lld",&k);
    if(k==1){
    	cout<<2<<'\n'<<2<<' '<<-1<<'\n'<<-1<<' '<<-1;
    	exit(0);
	}sum[1]=1;
	num=cnt=1;
	while(num*2-1<k){
		num*=2;
		sum[++cnt]=num;
	}ab=k,n=cnt*2+1;
	for(int i=cnt;i;i--)
		if(ab>=sum[i])ab-=sum[i],a[i*2]=1;
	cout<<n<<'\n';
	for(int i=1;i<=n;i++)
		if(i==n)
			cout<<-1<<' '<<-1;
		else if(i==n-2||i==n-1)
		    cout<<i+1<<' '<<-1<<'\n';
		else
			if(i%2==0)
				if(!a[i])cout<<i+1<<' '<<-1<<'\n';
				else cout<<i+1<<' '<<n<<'\n';
			else cout<<i+1<<' '<<i+2<<'\n';
	return 0;
}
```

---

## 作者：_3Zinc_ (赞：3)

本蒟蒻再这道黄题上磕磕碰碰，写过后~~面目狰狞~~快乐无比，遂作此篇。

这道题其实并不难，但是唯一的题解写得过分简略，所以分享一下自己的做法。首先假设 $k=10$，从这一个样例入手。当然，一个符合该约束条件的图长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/mp261bw1.png)

（注意！一个点最多有两条出边，但是可能有**许多条入边**！）

看着非常乱是不是？但是如果稍作整理……

![](https://cdn.luogu.com.cn/upload/image_hosting/ogpc1h0r.png)

（蓝色边与黑色边表示实际存在的边）

现在看起来是不是清晰多了？其实上下两张图的点集与边集是一模一样的。

观察一下，可以发现图由两部分组成：其中上面一部分（从点 $2$ 到点 $13$ 的所有路径上的点），由一条条交叉的边组成。可以发现，从这个部分中的某一个点向终点（点 $13$）走，总是 $2^i$ 种走法。这个 $i$ 由这个点到终点的距离决定，如从点 $2$ 走到点 $13$，有 $2^3$ 种走法；而从 $3$ 或 $4$ 开始走到 $13$，则有 $2^2$ 种走法。所以，这样一个部分的每一个点都可以看做**表示 $2^i$ 种走到终点的方法**。

接下来看第二部分：从点 $1$ 到点 $12$。所以……这部分表示什么呢？

首先，任何一个题目给出的 $k$ 都可以分解成 $2^{x1}+2^{x2}+2^{x3}+\cdots$（即分解为二进制），那么从点 $1$ 引出一条出边，指向第一部分中某个表示 $2^{x1}$ 种走法的点，这样方案数就加 $2^{x1}$；同理，可以引出一条出边去 $2^{x2},2^{x3},\cdots$ 种走法的点。但由于每个点至多有两条出边，所以要划分成一条链，从这条链上去指向第一部分中的点。

（图中灰色边就是可以选择的边，即连向某个第一部分点的边）

估计一下空间，$k \leq 10^9$，大概是 $2^30$，也就是说第一部分和第二部分加起来大约 $30 \times 3=90$ 个点，符合题目要求（实际我的代码中用了 $91$ 个点）。时间复杂度在 $\mathcal{O}(\log_2^n)$ 的级别，时间完全充裕。

最后说一下代码：首先，我把 $k$ 进行了二进制分解（STEP1），然后通过 $k$ 的二进制位数来确定第一部分有多少个点并建立第一部分的图（STEP2），接着通过 $k$ 的二进制来建出第二部分并向第一部分连边（STEP3），最后输出（STEP4）。如果理解了上述内容，除了一些细节并无什么难度；或者也可以稍微参考一下我的代码。

代码写得又长又臭，凑合着看吧（由于代码实现的不好，所以需要进行 $k=1$ 的特判）：

```cpp
#include <bits/stdc++.h>
using namespace std;

int k,n,bit[32],cnt,res;
int path[105][2],d1,d2,pos;

int main() {
	scanf("%d",&k);
	if(k==1) {
		printf("2\n2 -1\n-1 -1\n");
		return 0;
	}
	memset(path,-1,sizeof(path));
	//--------STEP1--------
	for(;k;k>>=1) bit[++cnt]=k&1;
//	printf("%d\n",cnt);
	//--------STEP2--------
	path[2][0]=d1=3,path[2][1]=d2=4;	
	for(int i=1;i<cnt-1;i++) {
		path[d1][0]=path[d2][0]=d1+2;
		path[d1][1]=path[d2][1]=d2+2;
		d1+=2,d2+=2;
	}
	//--------STEP3--------
	path[1][0]=pos=d2+1,res=2;
	for(int i=cnt;i>0;i--) {
		if(i>1) path[pos][0]=pos+1;
		if(bit[i]) path[pos][1]=res;
		res+=2,pos++;
	}
	//--------STEP4--------
	path[d1][0]=pos,path[d2][0]=pos;
	printf("%d\n",pos);
	for(int i=1;i<=pos;i++) printf("%d %d\n",path[i][0],path[i][1]);
	return 0;
} 
```

求轻喷。完。

---

## 作者：_•́へ•́╬_ (赞：3)

## 思路

按位处理。

举个 $21$ 的例子。

![图挂了](https://cdn.luogu.com.cn/upload/image_hosting/wk7e0ryr.png)

上半部分用来不断乘二，下半部分用来不断加一。

## code

```cpp
#include<stdio.h>
int n,m,i,x,y,z,l[111],r[111];
main()
{
	scanf("%d",&m);
	if(m==1){printf("2\n2 -1\n-1 -1");return 0;}
	for(i=1;i<=100;l[i]=r[i]=-1,++i);
	l[1]=2;r[1]=3;
	n=4;x=2;y=0;z=3;for(i=30;!(m>>i&1);--i);
	for(--i;i>=0;--i)
	{
		l[x]=l[y]=n;r[x]=r[y]=n+1;x=n++;y=n++;
		if(m>>i&1)l[z]=y,r[z]=n,z=n++;
	}
	l[x]=n;r[y]=n;
	printf("%d\n",n);
	for(int i=1;i<=n;printf("%d %d\n",l[i],r[i]),++i);
}
```



---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
先看数据范围，$k$ 这么大那肯定不能暴力搜索了，我们唯一的做法就只有构造了。
## 2. 题目做法
我们首先要想，怎样用仅有的 $100$ 个点，来建一个从 $1$ 点到 $n$ 点有几亿条路径的图。  
题目的限制条件较多，每个点最多两条出边，且不能有重边，不能有环，且终点必须为 $n$。我们可以尝试构造以下简单图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/rml04ybn.png)  
这样构造图，能到达点 $1$ 到 $5$ 的路径数分别为 $1,1,2,3,5$。相信大家已经发现了，这是一个斐波拉契数列。  
经过计算，斐波拉契数列的第 $45$ 项已经刚好超过了 $k$ 的最大值，那么我们只需要计算斐波拉契数列的前 $44$ 位就行了。  
大数表示出来后，我们再想如何将这些大数凑成 $k$，数列可以表示任何小于等于它总和的数，但用多个数列表示是肯定不行的，我们只有 $100$ 个点。  
举个例子，如果我们要表示 $6$，那么我们就要找出数列中的数，如 $5$ 和 $1$，我们可以尝试进行以下构造：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jqe5emwo.png)  
我们在点 $2$ 与点 $3$ 之间建一个新点，将新点的另一条边连向终点，这样就可以将路径数加 $1$，这样便可以涵盖所有情况。  
如此便可完成此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int a[N],k,n,ed,t;
queue<int>s;
int z[N][2];
int main()
{
	k=read();
	a[1]=1;
	for(int i=2;i<=44;i++)
		a[i]=a[i-1]+a[i-2];
	for(int i=44;i>=1;i--)
	{
		if(a[i]<=k)
		{
			k-=a[i];
			s.push(i);
			n++;
			if(!ed)
				ed=i;
		}
	}
	n+=ed;
	for(int i=1;i<ed;i++)
		z[i][0]=i+1,z[i][1]=i+2;
	s.pop();//弹出队头，防止重复计算 
	z[ed-1][1]=-1;
	z[ed][0]=n,z[ed][1]=-1;
	z[n][0]=-1,z[n][1]=-1;
	for(int i=ed+1;i<n;i++)
	{
		t=s.front();
		s.pop();
		z[t][0]=i,z[i][0]=t+1,z[i][1]=n;
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",z[i][0],z[i][1]);
	return 0;
}
```

---

## 作者：FBW2010 (赞：1)

# 题目描述

[传送门](https://www.luogu.com.cn/problem/P9101)

给定一个有向无环图中从 $1$ 到 $n$ 有多少条路径，并且每个点的出度小于等于 $2$，构造一个满足要求且结点数小于等于 $100$ 的图。

# 思路

~~Ps：为什么这么难想的一道题会是黄题啊。~~

首先结点数只有 $100$ 个，而 $k$ 的范围却是小于 $10^9$，意思就是我们要用尽可能少的节点使 $1$ 到 $n$ 的路径条数最多。由于一个节点的出度最多只有二，我们可以构造出结构类似于这样这样的一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/srxm57gv.png)

此时到 $4$ 的方案有 $2^1$ 个，到 $7$ 的方案有 $2^2$ 个，到 $10$ 的方案有 $2^3$ 个。以此类推，当方案数有 $10^9$ 时，结点数也不会超过 $100$。

但 $k$ 不可能都是 $2$ 的幂，不过我们可以把 $k$ 写成若干个 $2$ 的幂相加，其实就是把 $k$ 转化为二进制。例如 $13$ 转化为二进制就是 $1101$，也就是 $2^0+2^2+2^3$。此时，我们可以先构造出方案数为 $2^3$ 的图，对于多的 $2^0$ 与 $2^2$，我们只需要找到两个节点，使得到这两个节点的方案分别为 $2^0$ 与 $2^2$，再将这两个节点与终点相连即可。不过像上图那样 $8$ 与 $9$ 连到 $10$ 会有重边，此时可以在 $10$ 后再加一个节点作终点即可。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/anmp3272.png)

# 代码

下面就展示我~~又臭又长~~的代码吧，仅供参考。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int k,cnt,a[105],l[105],r[105];
int main(){
	scanf("%d",&k);
	int p=0;
	while(k){
		a[++p]=k%2;
		k/=2;
	}
	cnt=1;
	int x=1,y;
	for(int i=1;i<p;i++){
		y=++cnt;
		l[x]=++cnt;
		l[cnt]=y;
		r[x]=++cnt;
		l[cnt]=y;
		x=y;
	}
	l[x]=++cnt;
	x=cnt;
	y=1;
	for(int i=1;i<p;i++){
		y=l[y];
		if(a[i])r[y]=x;
		y=l[y];
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		if(l[i])printf("%d ",l[i]);
		else printf("-1 ");
		if(r[i])printf("%d\n",r[i]);
		else printf("-1\n");
	}
	return 0;
}
```

---

