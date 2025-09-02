# [USACO13NOV] Empty Stalls G

## 题目描述

Farmer John's new barn consists of a huge circle of N stalls (2 <= N <= 3,000,000), numbered 0..N-1, with stall N-1 being adjacent to stall 0.

At the end of each day, FJ's cows arrive back at the barn one by one, each with a preferred stall they would like to occupy.  However, if a cow's preferred stall is already occupied by another cow, she scans forward sequentially from this stall until she finds the first unoccupied stall, which she then claims.  If she scans past stall N-1, she continues scanning from stall 0.

Given the preferred stall of each cow, please determine the smallest index of a stall that remains unoccupied after all the cows have returned to the barn.  Notice that the answer to this question does not depend on the order in which the cows return to the barn.

In order to avoid issues with reading huge amounts of input, the input to this problem is specified in a concise format using K lines (1 <= K <= 10,000) each of the form:

X Y A B

One of these lines specifies the preferred stall for XY total cows: X cows prefer each of the stalls f(1) .. f(Y), where f(i) = (Ai + B) mod N.  The values of A and B lie in the range 0...1,000,000,000.

Do not forget the standard memory limit of 64MB for all problems.

约翰的谷仓中有N(2 <= N <=3,000,000)个房间，编号0到N-1，这些房间排布成环状,编号0的和编号N-1的相邻。

每天傍晚，奶牛们一只一只排队回到谷仓，每头奶牛都有一个喜欢的房间，但是，如果它喜欢的房间已被其他奶牛占了，它会向前挨个探索其他房间（如果它探索过了N-1号房间，它会继续探索0号房间，以此继续下去）直到探到第一个没有被占用的房间，这时它会宣布占用这个房间。

告诉你每头奶牛喜欢的房间，当所有奶牛都找到房间后，剩下的没被占用的房间中，编号最小的是哪个。很明显，问题的答案与奶牛进入谷仓的顺序无关。


为避免输入内容过多。本题的输入数据采用一种简洁的方式：一共K(1 <= K <=10,000)行，每行格式如下：

X Y A B

表示有Y批奶牛，每批X头，也就是总共X\*Y只奶牛喜欢的房间号。Y批奶牛编号1到Y，第i批X头奶牛喜欢的房间号为(A\*i+B) Mod N.

A和B的取值范围为0...1,000,000,000

注意，只有64M的空间。


## 说明/提示

There are 10 stalls in the barn, numbered 0..9.  The second line of input states that 3 cows prefer stall (2\*1+4) mod 10 = 6, and 3 cows prefer stall (2\*2+4) mod 10 = 8.  The third line states that 2 cows prefer stall (0\*1+1) mod 10 = 1.  Line four specifies that 1 cow prefers stall (1\*1+7) mod 10 = 8 (so a total of 4 cows prefer this stall).


All stalls will end up occupied except stall 5. 



## 样例 #1

### 输入

```
10 3 
3 2 2 4 
2 1 0 1 
1 1 1 7 
```

### 输出

```
5 
```

# 题解

## 作者：小手冰凉 (赞：23)

这题题目中给了一个比较重要的信息

"很明显，问题的答案与奶牛进入谷仓的顺序无关。"

这句话告诉了我们这题的一个思路：将所有数据一起处理

我们可以先假设所有牛棚可以放无数个奶牛

然后一个一个往后推

这样得出的答案就是直接做的答案（当然牛棚和牛具体对应的序号是不知道的）

要注意可能爆int，以及第一遍扫过以后可能有的到了头一个牛棚，要再来一遍

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3000000;
int n;
int ans[N];
int x,y,a,b,k;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	return x*f;
}
signed main()
{
	n=read();k=read();
	while(k--){
		x=read();y=read();a=read();b=read();
		for(int i=1;i<=y;i++){
			ans[(a*i+b)%n]+=x;
		}
	}
	for(int i=0;i<n;i++){
		if(ans[i]>0)ans[(i+1)%n]+=ans[i]-1,ans[i]=1;
	}
	while(ans[0]>1)
		for(int i=0;i<n;i++){
			if(ans[i]>0)ans[(i+1)%n]+=ans[i]-1,ans[i]=1;
		}
	for(int i=0;i<n;i++)
		if(ans[i]==0){
			cout<<i<<endl;
			return 0;
		}
	return 0;
}
```

---

## 作者：不便透露 (赞：10)

一开始，没注意“ _很明显，问题的答案与奶牛进入谷仓的顺序无关。_ ”就用了并查集，侥幸过了。
fa[i]表示喜欢i号的牛，能去的房间。一开始都为i，住了一个后，变为find（i+1）。
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3*1e6+50;
bool z[maxn];
int fa[maxn];
int n,m;
int find(int a){
	if(a==fa[a])
		return a;
	return fa[a]=find(fa[a]);
}
int main(){
	scanf("%d%d",&n,&m);
	int i,j,k,t;
	int a,b,x,y;
	for(i=0;i<n;i++)
		fa[i]=i;
	fa[i]=0;
//是个环
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&x,&y,&a,&b);
		a%=n;
		b%=n;
		for(j=1;j<=y;j++){
			k=find((a*j+b)%n);
//这边k本来应该用long long
//一开始忘了，还过了，就没改
			for(t=1;t<=x;t++){
				z[k]=1;
//已有牛
				k=fa[k]=find(k+1);
//k和fa[k]不能换顺序
//更新为下一个能到的房间 
			}
		}
	}
	for(i=0;i<n;i++)
		if(!z[i])
			break;
	printf("%d",i);
	return 0;
}
```


---

## 作者：YuYuanPQ (赞：5)

# 洛谷 P3090 题解

## 题目大意

一共 $k$ 行输入，每行输入告诉我们：有 $y$ 批奶牛回谷仓，而每批奶牛有 $x$ 头。他们分别喜欢 $a \times j + b$。

## 具体做法

### 第一步

在输入的时候可以用一个数组来记录。数组中第 $i$ 个位置的值表示喜欢房间 $i$ 的奶牛总数（其实就是预处理）。

### 第二步

循环判断喜欢当前位置 $i$ 的奶牛个数是否大于 $1$。如果大于，就把当前位置的值改为 $1$，并且将数组中下一个位置的值加上当前位置的值，再减去 $1$；否则继续判断下一个位置。

## 注意事项

### 一

在预处理的时候要模 $n$，防止越界。

### 二

当数组最后一位的值比 $1$ 大时，说明需要把这一位的值放到第 $1$ 位，因此需要**再循环一次**。

## Code

```cpp
#include<bits/stdc++.h>
#define MAXN 10010
using namespace std;
int n,k;
int d[3000010];
int x,y,a,b;
long long s;
void lzy()
{
    for(int i=0;i<n-1;i++)
        {
            if(d[i]>1)
            {
                d[i+1]+=d[i];
                d[i+1]--;
                d[i]=1;
            }
        }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d%d%d",&x,&y,&a,&b);
        s=b;
        for(int j=1;j<=y;j++)
        {
            s=(s%n+a%n)%n;
            d[s]+=x;
        }
    }
    lzy();
    if(d[n-1]>1)
    {
        d[0]+=d[n-1];d[0]--;
        d[n-1]=1;
        lzy();
    }
    for(int i=0;i<n;i++)
    {
        if(!d[i])
        {
            printf("%d",i);
            break;
        }
    }
    return 0;
}
```


## 另附

### 一

如有更好做法，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。

### 二

这是我第一次写题解，如有错误请各位大佬指出。

---

## 作者：SzTC (赞：5)

分析题目，很明显在奶牛入住时分为两种情况：  
1. 它最喜爱的房间还未被入住。
2. 它最喜爱的房间已经被入住了。

对于第一种情况，只需要将房间入住即可；  
对于第二种情况，则需往后寻找，直到发现了一个空的房间为止 。 
很明显，将他后面的每一个房间都寻找过去十分浪费时间，因此可以设置两个数组 $p$  和 $q$，$p[i]$ 表示从 $i$ 号房间往**后**能够找到第一个空的房间,$q[i]$ 表示从 $i$ 号房间往**前**能够找到第一个空的房间（均不包括它本身）。在每一只奶牛入住房间时，将此房间的上一个空房间的下一空房间设置为此房间的下一个空房间,同时将此房间的下一个空房间的上一空房间设置为此房间的上一个空房间  
话说起来太乱，看张图就明白了：

![牛的选房间情况](https://cdn.luogu.com.cn/upload/image_hosting/s3s0mzf5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
绿线表示数组 $p$ 与 $q$ 原先的指向情况，蓝线表示牛入住一个房间后的指向情况  
这样一来，我们就能节省很多的时间  
具体实现，请看参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long x,y,a,b;//注意数据范围，a*y是有可能爆int的
int room[3333333];
int p[3333333];
int q[3333333];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n-1;i++)p[i]=i+1;
	p[n-1]=0;//因为是环形的，所以最后一个房间最开始要指向第一个房间
	for(int i=n-1;i>0;i--)q[i]=i-1;
	q[0]=n-1;//同上
	for(int i=1;i<=k;i++)
	{
		scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
		for(int j=1;j<=y;j++)
		{
			for(int l=1;l<=x;l++)
			{
				int t=(j*a+b)%n;//不要忘记取模
				while(room[t])//寻找下一个空房间
				{
					t=p[t];
				}
				room[t]=1;//住进这个房间
				p[q[t]]=p[t];
				q[p[t]]=q[t];//前后重新标记
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(!room[i])//寻找第一个空的房间
		{
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```


### 本篇题解到这里就结束了，欢迎大家在评论区提出意见！

---

## 作者：小柯 (赞：4)

题意:有 $n$ 头牛，每头牛有一个喜欢的位置 $like_i$ ，在为每头牛分配了 $like_i$ 以后第一个未被占用的位置（包括该位置），若不存在，则选择第一个未被占用的位置以后，第一个被剩下的位置。

分析:
若当前位置前有 $x$ 个位置未被占用，那么分两种情况：

>1.当前位置未被占用：则占用该位置。

>2.当前位置已被占用：则占用第 $x+1$ 个未被占用的位置，若不存在第 $x+1$ 个，则占用第一个未被占用的位置。

对于第一种情况，直接由数组维护每个位置的占用情况即可。

对于第二种情况，如果把所有位置看做一个序列，已被占用的为 $0$，未被占用的为 $1$，则问题可以转化：

>求 $x$ -> 求该序列的前缀和 $sum_x$。

>求第 $x+1$ 个未被占用的位置 -> 求第一个前缀和 $sum_i$ 为 $x+1$ 的位置 $i$。

很显然，这些操作就是单点修改，区间查询，查询排名，可以用权值树状数组、权值线段树、平衡树等数据结构维护。(可以用树状数组的话，当然不可能用其他的啊qwq，但是注意树状数组下标不支持 $0$，需要下标手动加一)

综上，时间复杂度为 $O(n$ $logn)$，~~勉强能卡过~~。

$code:$

```cpp
#include<iostream>
#include<cstdio>
#define maxn 3000005
#define lowbit(x) (x&-x)
using namespace std;
int n,k,cnt;
int t[maxn];
int lg[maxn];
int used[maxn];
int like[maxn];
long long x,y,a,b;
inline void add(int pos,int val){
	for(;pos<=n;pos+=lowbit(pos))t[pos]+=val;
}
inline int sum(int pos){
	int ans=0;
	for(;pos;pos-=lowbit(pos))ans+=t[pos];
	return ans;
}
inline int qry(int rank){
	int ans=0,pos=0,nxt_pos;
	for(int step=lg[n];~step;step--){
		nxt_pos=pos+(1<<step);
		if(nxt_pos<=n&&ans+t[nxt_pos]<rank)ans+=t[pos=nxt_pos];
	}
	return pos+1;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int line=1;line<=k;line++){
		scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
		for(int i=1;i<=y;i++){
			for(int j=1;j<=x;j++){
				like[++cnt]=(a*i+b)%n;
			}
		}
	}
	//for(int i=1;i<=cnt;i++)printf("%d ",like[i]);printf("/n");
	++n;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)add(i,1);
	for(int i=1;i<=cnt;i++){
		++like[i];
		if(!used[like[i]])x=like[i];
		else if((x=qry(sum(like[i])+1))==n)x=qry(1);
		//printf("%d ",x);
		used[x]=1,add(x,-1);
	}
	//printf("\n");
	printf("%d",qry(1)-1);
	return 0;
}
```


---

## 作者：wangxihan2009 (赞：2)

题目描述

有 $n$ 个牛棚，每个牛棚可以容纳一头牛。现在有 $m$ 头牛需要安排，每头牛都有一个最小需求值 $a_i$ 和一个最大需求值 $b_i$。如果一头牛被安排在一个牛棚里，那么它的需求值就是这个牛棚的容量，需要满足 $a_i \leq$ 牛棚容量 $\leq b_i$。求最少需要多少个牛棚才能安排好所有的牛。

输入格式：

第一行包含两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行包含两个整数 $a_i$ 和 $b_i$。

输出格式：

输出一个整数，表示最少需要多少个牛棚才能安排好所有的牛。

数据范围：

$1\leq n\leq 10^9$

$1\leq m\leq 10^5$

$1\leq a_i\leq b_i\leq n$

样例

输入样例：

10 3 

3 2 2 4 

2 1 0 1 

1 1 1 7 

输出样例：

5

解题思路

本题是一道贪心算法题目，有多种解法，这里给出两种不同的贪心思路。

思路一：基于区间贪心

我们可以将每个牛的需求范围看成一个区间 $[a_i,b_i]$，然后先将这些区间按照右端点从小到大排序，然后从前往后考虑每个区间，尽量使用已经安排好的牛棚来满足当前的需求，如果没有合适的牛棚，就新建一个牛棚。具体来说，我们可以使用一个堆来维护当前可用的牛棚，每次将右端点小于当前区间左端点的牛棚弹出，然后将当前区间安排在这些牛棚中的左端点最小的牛棚中。

时间复杂度：$O(m\log m)$

思路二：基于二分答案

我们可以将答案看成一个二分的答案 $x$，然后对于每个牛，将其需求范围 $[a_i,b_i]$ 中的所有牛棚按照容量从大到小排序，然后从前往后考虑这些牛棚，如果当前牛棚的容量 $\geq x$，就将当前牛安排在这个牛棚中，否则就考虑下一个牛棚。如果一个牛都无法安排，那么答案就一定小于等于 $x$。否则答案一定大于 $x$。

时间复杂度：$O(m\log^2 n)$

---

## 作者：傅思维666 (赞：2)

## 题解：

看完题思考之后觉得属于集合的维护问题，不要被标签蒙蔽，自己想一种解法就去写就好了。

用并查集可过。

设置$fa[i]$表示喜欢i号房间的牛能去的房间。这就是一个并查集的合并问题了。用一个标记数组来维护这个房间有没有被人去过，就可以开始维护全部的信息。一开始都是$fa[i]=i$，然后依题意模拟占房间的过程。如果没被人占就直接占上，如果被人占了，那么就是$fa[i]=find(i+1)$.

应该还比较好理解。

至于最后的答案维护，看代码吧。

代码：

```cpp
#include<stdio.h>
int v[3000001];
int fa[3000001];
int n,q,k;
int find(int x)
{
	if(x==fa[x])
        return x;
    return fa[x]=find(fa[x]);
}
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>='0'&&ch<='9')
        x=x*10+ch-'0',ch=nc();
   	return x*f;
}
int main()
{
	n=read();q=read();
	for(int i=0;i<n;i++)
		fa[i]=i;
	fa[n]=0;
	for(int i=1;i<=q;i++)
    {
        int a,b,x,y;
		x=read();y=read();a=read();b=read();
		a%=n;b%=n;
		for(int j=1;j<=y;j++)
        {
			k=find((a*j+b)%n);
			for(int l=1;l<=x;l++)
            {
				v[k]=1;
				k=fa[k]=find(k+1);
			}
		}
	}
	for(int i=0;i<n;i++)
		if(!v[i])
        {
            printf("%d",i);
            return 0;
        }
   	printf("%d",n);
	return 0;
}
```



---

## 作者：yydfj (赞：1)

这是本蒟蒻第三十二次写的题解，如有错误点请好心指出！

## 问题简述

有 $n$ 个房间连成一个环，编号为 $0$ 到 $n-1$，奶牛们从前往后选择它们喜欢的房间并住进去，但是一个房间只能容纳一头牛，如果它们喜欢的房间被占用，就会向后寻找最近的一个没被占用的房间并住进去，问最后没被占用的房间编号最小是多少。

## 解法综述

假设一开始每头牛都在它们喜欢的房间，那么当某一个房间的牛数超过一头时，就需要保留一头牛在该房间，剩下的都去到下一个房间，以此类推。

因为所有的房间连成一个环，需要注意在编号为 $n-1$ 的房间多出来的牛会去到编号为 $0$ 的房间，并且去到编号为 $0$ 的房间的牛数可能不够该房间容纳，还需要再模拟一遍才能将所有的牛分配到房间里。

然后从小到大遍历房间编号看该房间容纳的牛数是否为 $0$，若为 $0$ 输出该房间编号即可。

## 代码描述
```cpp
#include<cstdio>
typedef long long ll;
ll n,k,room[3000005];
void work()
{
	for(int i=0;i<n;i++)
	if(room[i]>1)//当某一个房间的牛数超过一头时
	{
		room[(i+1)%n]+=room[i]-1;//注意在编号为n-1的房间多出来的牛会去到编号为0的房间，用模数来解决
		room[i]=1;//需要保留一头牛在该房间
	}
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=k;i++)
	{
		ll x,y,a,b;
		scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
		for(int j=1;j<=y;j++) room[(a*j+b)%n]+=x;//假设一开始每头牛都在它们喜欢的房间
	}
	work();work();//模拟两遍过程，因为编号为0的房间的牛数可能会超过一头
	for(int i=0;i<n;i++)
	if(!room[i])
	{
		printf("%d",i);
		break;
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

发现每个点的下一个节点是 $i+1$，且需要维护当前序列的连通性使得复杂度不为 $O(n^2)$。  
不妨将下一个节点看为父亲节点，当节点 $i$ 被删除时，下一个就是他的父亲节点，这一操作不难想到并查集。  
于是便有「白雪皑皑」的方法维护本序列的连通性，每次修改其父亲节点从 $i$ 到 $father_{i+1}$，然后直接从 $i$ 跳到 $father_{i+1}$ 即可。  
路径压缩一下，但是不能按秩合并，不按秩合并后的并查集复杂度 $O(n \log n)$ 但是极小常数。

```cpp
const int N = 3e6 + 19;
int f[N];
int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}
signed main() {
	int n = read(), k = read();
	for (int i = 0; i < n; ++i) {
		f[i] = i;
	}
	while (k--) {
		int x, y, a, b;
		read(x, y, a, b);
		a %= n;b %= n;
		for (int i = 1; i <= y; ++i) {
			int love = (a * i + b) % n;
			for (int j = 1; j <= x; ++j) {
				love = find(love);
				f[love] = find(f[(love+1) % n]);
				love = f[love];
			}
		}
	}
	for (int i = 0; i < n; ++i) if (f[i] == i) return write(i, '\n'), 0;
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

用链表做是可以被卡成 $O(n^2)$ 的，我来介绍比较有道理的预处理做法。

我们初始在每个奶牛喜欢的位置打下标记，然后逐渐传递，传递个两轮即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e6+5;
LL n,k,x,y,a,b,ans[N];
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
		for(int j=1;j<=y;j++)ans[a*j+b]+=x;
	}
	for(int i=0;i<=n-1;i++)
	{
		if(ans[i]>1)
		{
			ans[i+1]+=ans[i]-1;
			ans[i]=1;
		}
	}
	if(ans[n]>1)
	{
		ans[0]+=ans[n];
		ans[n]=0;
	}
	for(int i=0;i<=n-1;i++)
	{
		if(ans[i]>1)
		{
			ans[i+1]+=ans[i]-1;
			ans[i]=1;
		}
	}
	for(LL i=0;i<=n-1;i++)
	{
		if(ans[i]==0)
		{
			printf("%lld",i);
			return 0;
		}
	}
	return 0;
}
```



---

## 作者：hcl156 (赞：0)

## 题意：
有很多类牛，每类牛有很多批，同种类的每一批又有相同个数的牛，他们喜欢相同一个位置；每一类的第 $i$ 批都喜欢 $A_{i}+B$ 号位置；每一个位置最终只能安放一头牛；牛中意的位置被占领后，它将向后寻找最近的没有被占领的位置进行占领。所有位置是成环的，即$1 \rightarrow 2 \rightarrow \ldots  \rightarrow n \ldots  \rightarrow 1  \rightarrow \ldots 1  \rightarrow 2  \rightarrow \ldots  \rightarrow n  \rightarrow 1  \rightarrow \ldots$ 。给出各参数，求出所有牛都有归属后，所有没有牛的位置中，编号最小的位置。
## 思想：
模拟分配位置过程即可：
先扫描一次，将能分配的位置都分配上；
同时将每个位置上多余的牛带到下一个；
将牛推到第一个位置上进行第二轮扫描；
那么最多两次循环就可以全部分配完毕；
再扫描一次，寻找最小未被占领的位置；
一共最多三次循环。$O(n)$ 绰绰有余。
## Code:

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=3000002;
int f[maxn];
int n,k;
//分配过程
void circle()
{
    for(int i=0;i<n-1;i++)
        if(f[i]>1)      
            f[i+1]+=f[i]-1,f[i]=1;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++)
    {
        int x,y,a,b,num;
        scanf("%d%d%d%d",&x,&y,&a,&b);
        num=b;
        for(int j=1;j<=y;j++)
        {
            num=(num%n+a%n)%n;
            f[num]+=x;
        }
    }
    circle();
    if(f[n-1]>1)
    {
        f[0]+=f[n-1]-1,f[n-1]=1;
        circle();
    }
    for(int i=0;i<n;i++)    
        if(!f[i])   
        {
            printf("%d",i);
            return 0;
        }
    return 0;
}
```


---

