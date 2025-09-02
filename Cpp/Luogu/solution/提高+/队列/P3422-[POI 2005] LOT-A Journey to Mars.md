# [POI 2005] LOT-A Journey to Mars

## 题目背景

Byteazar 决定去火星参加一个空间站旅行。

## 题目描述

火星的所有空间站都位于一个圆上，Byteazar 在其中一个空间站登陆然后开始绕圈旅行。  

旅行需要耗费油料，一升油料只能跑 $1$ 米，每个空间站可以补给的油料都有所不同。 

Byteazar 每到一个空间站便可以把该空间站的油料全部拿走（他的油箱是没有容量限制的）。但是如果走到某个时候突然没油了那么旅行便失败了。

Byteazar 需要决定要在哪个地方登陆使得他能顺利访问完所有的空间站后回到他当初登陆的地方，他登陆后可以选择两个方向中的任意一个进行旅行。

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，$3\le n\le10^6$，$p_i\ge0$，$d_i>0$，$\sum d_i\le2\times10^9$。

## 样例 #1

### 输入

```
5
3 1
1 2
5 2
0 1
5 4
```

### 输出

```
TAK
NIE
TAK
NIE
TAK```

# 题解

## 作者：LittleMoMol (赞：28)

## P3422 [POI2005]LOT-A Journey to Mars 题解

### 前言
了解过单调队列嘛？如果还没有的话，建议做完 [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886) 再做此题。

[更好的阅读体验](https://www.cnblogs.com/LittleMoMol-kawayi/p/solution-LuoGu-P3422.html)

### 思路

#### No. 1 破环成链

首先题目给的是环，自然要破环成链，我最喜欢的一种方式是，复制一份，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/wyzof94z.png)

淡黄色为每次遍历经过的点，可以发现，和环形的遍历是等价的。

#### No. 2 怎么想到用单调队列的？

$p_i$ 存下第 $i$ 个加油站的油量，$d_i$ 表示第 $i$ 个加油站和第 $(i+1) \operatorname{mod}\ n$ 个加油站的距离（模 $n$ 的原因是最后一个加油站和第一个加油站是相邻的），以下图为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/r96t2176.png)

下面展示分析问题的过程

- 先以顺时针为例，如果想要转完一圈，就必须保证每一步都可以到达下一个加油站，比如：想要从第一个加油站走到第二个加油站，就必须满足 $p_1 - d_1 \ge 0$，类似地，想要从第一个加油站走到第三个加油站，就必须满足 $p_1 - d_1 \ge 0$ 且 $p_1 + p_2 - d_1 - d_2 \ge 0$，可知如果想走完一圈，也就是从第一个加油站走到第 $n$ 个加油站，就必须满足 $\forall\  k \in [1,n],\  \sum\limits _{i=1}^{k}p_i - \sum\limits _{i=1}^{k}t_i \ge 0$

- 那么如何快速求出式子呢，你一定最先想到前缀和，那么我们令 $s_i$ 表示 $\sum\limits _{j=1}^{i}p_j - \sum\limits _{j=1}^{i}t_j$。那么对于第 $i$ 个加油站，只需要满足 $\forall\  k \in [i,i + n],\ s_k - s_{i-1} \ge 0$。

- 你会发现每一个前缀和都要判断，有没有一种方法，使得只用判断一次呢？可以发现，只需要让所有的 $s_k$ 中最小的那个满足 $s_k - s_{i-1} \ge 0$ 即可。

- 也就是说，当前最大的问题是如何快速找到最小的 $s_k$，于是就很自然地想到了单调队列，用一个单调队列维护前缀和的最小值。

#### No. 3 细节多
|顺时针|逆时针|
|--------------------------|--------------------------|
| 从后往前遍历（原因见后文）。 | 从前往后遍历（原因见后文）。 |
| $s_i = p_i - d_i$ | $s_i = p_i - d_{i-1},\ d_0 = d_n$ |
| 维护 $s_k$ 的最小值（原因见后文）。 | 维护 $s_k$ 的最大值（原因见后文）。 |
| 先出队再更新。 | 先更新再出队。 |
| 当遍历到 $i \le n$ 的加油站再更新答案。 | 当遍历到 $i > n$ 的加油站再更新答案。 |

对于第一条：顺时针维护该点往后的 $n$ 个点的前缀和，所以要从后往前遍历；逆时针维护该点往前的 $n$ 个点的前缀和，所以要从前往后遍历

对于第三条，放一个图，就能明白了


![](https://cdn.luogu.com.cn/upload/image_hosting/jtywesdr.png)

### Code
```cpp
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 2e6 + 10;

int n;
int p[N], d[N];
LL s[N];
int q[N];
bool ans[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> p[i] >> d[i];
	
	//顺时针
	for (int i = 1; i <= n; i ++ )
		s[i] = s[i + n] = p[i] - d[i]; //对应细节2
	for (int i = 1; i <= n * 2; i ++ )
		s[i] += s[i - 1];
	
	int hh = 0, tt = -1;
	for (int i = n * 2; i; i -- ) //对应细节1
	{
		if (hh <= tt && q[hh] >= i + n) hh ++ ;
		while (hh <= tt && s[q[tt]] >= s[i]) tt -- ; //对应细节3，细节4
		q[ ++ tt] = i;
		if (i <= n)  //对应细节5
		{
			if (s[q[hh]] - s[i - 1] >= 0) ans[i] = true;
		}
	}
	
	//逆时针
	d[0] = d[n];  //对应细节2
	for (int i = 1; i <= n; i ++ )
		s[i] = s[i + n] = p[i] - d[i - 1]; //对应细节2
	for (int i = 1; i <= n * 2; i ++ )
		s[i] += s[i - 1];
	
	hh = 0, tt = -1;
	for (int i = 1; i <= n * 2; i ++ ) //对应细节1
	{
		if (hh <= tt && q[hh] < i - n) hh ++ ;
		if (i > n)  //对应细节5
		{
			if (s[i] - s[q[hh]] >= 0) ans[i - n] = true;
		}
		while (hh <= tt && s[q[tt]] <= s[i]) tt -- ; //对应细节3，细节4
		q[ ++ tt] = i;
	}
	
	for (int i = 1; i <= n; i ++ )
		if (ans[i]) cout << "TAK" << endl;
		else cout << "NIE" << endl;
	
	return 0;
}
```

### 后语
我在写这篇题解的时候有一个小插曲，让我 debug 了好长时间，在此分享一下

错误的写法
```cpp
while (hh <= tt && s[q[tt] <= s[i]]) tt -- ;
```

正确的写法
```cpp
while (hh <= tt && s[q[tt]] <= s[i]) tt -- ;
```

可太难调了捏~

制作不易，盼君一赞。

完结撒花！！

---

## 作者：JYTS (赞：9)

~~随机跳题跳到的~~

跟早上跳到的[这题](https://www.luogu.org/problemnew/show/P1714)差不多。大概就是很简单的思维再加上数据结构维护一下。~~(其实就是线段树战胜单调队列)~~

~~**上面都是废话**~~

暴力部分就不讲了就是模拟 复杂度 $O(n^2)$

这个时候我们发现其实就是求 某一段区间内燃料之和-距离之和是否小于$0$，这一部分就可以很快乐地用前缀和搞一下，(当然由于是个环当然要把数据拆下环)。即
> $s[j]-s[i] >=0$

因为通过枚举的话前缀$s[i]$是一定的，如果可以访问完自$i$开始的一圈的话，那么最小的$s[j]$就一定大于等于$s[i]$。所以维护个区间最小的$s[j]$就可用到 _线段树_ 啦。

这样打完以为自己~~一发入魂~~，结果发现好像选取起点时还可以往左边走，那么再反过来再搞个前缀和线段树就可以啦。
复杂度$O(nlogn)$

代码 ~~很丑你们讲究看吧~~: 
```cpp
#include <bits/stdc++.h>
using namespace std;
int read()
{
    int sum=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch<='9'&&ch>='0'){sum=sum*10+ch-'0';ch=getchar();}
    return sum;
}
const int N = 1e6+10;
int data[N],dist[N],n;
long long qianzhui[N];
struct node
{
   int l,r;
   long long mi;
}a[N*8],t[N*8];
void pushup(int p)
{
    a[p].mi=min(a[p*2].mi,a[p*2+1].mi);
}
void build(int p,int l,int r)
{
    a[p].l=l,a[p].r=r;
    if(l==r){a[p].mi=qianzhui[l];return;}
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    pushup(p);
}
long long query(int p,int l,int r)
{
    if(a[p].l==l&&a[p].r==r)return a[p].mi;
    int mid=(a[p].l+a[p].r)>>1;
    if(r<=mid)return query(p*2,l,r);
    else if(l>mid)return query(p*2+1,l,r);
    else return min(query(p*2,l,mid),query(p*2+1,mid+1,r));
}
void pushup1(int p)
{
    t[p].mi=min(t[p*2].mi,t[p*2+1].mi);
}
long long qianzhui1[N];
void build1(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    if(l==r){t[p].mi=qianzhui1[l];return;}
    int mid=l+r>>1;
    build1(p*2,l,mid);
    build1(p*2+1,mid+1,r);
    pushup1(p);
}
long long query1(int p,int l,int r)
{
    if(t[p].l==l&&t[p].r==r)return t[p].mi;
    int mid=(t[p].l+t[p].r)>>1;
    if(r<=mid)return query1(p*2,l,r);
    else if(l>mid)return query1(p*2+1,l,r);
    else return min(query1(p*2,l,mid),query1(p*2+1,mid+1,r));
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)data[i]=read(),dist[i]=read(),qianzhui[i]=qianzhui[i-1]-dist[i]+data[i];
    for(int i=n+1;i<=n*2-1;i++)qianzhui[i]=qianzhui[i-1]-dist[i-n]+data[i-n];
    for(int i=1;i<n;i++)qianzhui1[i]=qianzhui1[i-1]+data[n-i+1]-dist[n-i];
    qianzhui1[n]=qianzhui1[n-1]+data[1]-dist[n];
    for(int i=n+1;i<=n*2-1;i++)qianzhui1[i]=qianzhui1[i-1]+data[2*n-i+1]-dist[2*n-i];
    build(1,1,n*2-1);
    build1(1,1,n*2-1);
    for(int i=1;i<=n;i++)
    {
        if(query(1,i,i+n-1)>=qianzhui[i-1])printf("TAK\n");
        else if(query1(1,n-i+1,n-i+n)>=qianzhui1[n-i])printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}
```
好像数据没卡$long$ $long$.....

---

## 作者：jzzcjb (赞：9)

这个题其实没那么nan，只要按照正常思路“模拟”一遍就可以了。

首先考虑一个问题：跑一圈都是跑的相同的一圈，为什么有的点开始就能跑完，有的点开始就跑不完呢。

比如第3个点跑不完，是“NIE”。第1个点能跑完，是“TAK”。

第3个点跑不完，一定是在半路上某两个点中间死掉了。如果我们给每个点设一个“濒死值”，表示刚到某个点，还没有拿这个点的油时，油的剩余量。死掉了就是中间有某个点的“濒死值”小于0了。

而从第1个点跑过来时汽油还有些剩余，正是这些“剩余”，帮它度过了那两个点之间的艰难岁月。

只要度过了最黑暗的一段，其他的就都不是问题了。

**因此，问题转化为了，每个点在初始没有结余的情况下，能否熬过以它开始的一圈中汽油最少的一段（濒死值最小的一个点）。**

所以可以从1开始暴力模拟一遍，求出以1为起点的每个点的“濒死值”。因为是环，所以可以在n后面再补一段1~n。把这段长为
2*n
的路走一遍。
看一下每个点走到自己对应的点的路上最小的濒死值的最小值是否大于这个点的剩余（也就是这个点的濒死值），就可以判断是否能从这个点开始走完一圈了。

**现在，唯一的问题变为了，如何在一个长为 $2n$ 的序列中，求出一些长为 $n$ 的段的最小值。**

是不是和某个题的题面出奇的相似，这不就是[滑动窗口](https://www.luogu.org/problemnew/show/P1886)（一道绿牌题，没做过的可以先去水了它）的题面么，而且这两道题连数据范围都一样，这个暗示.......

至此，这道题就被完美解决了。

思路：预处理+单调队列。还有一点，因为可以从两个方向走，所以还要做一遍反向的从 $2n$ 跑到 $1$ 。预处理也要反向预处理一遍，注意下标，容易懵　。

蒟蒻不会函数不会传参，只能傻傻的写两遍，又臭又长的。
### 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,h,t;
int v[2001000];//油量 
int d[2001000];//离下一个点的距离 
int a[2001000];//濒死值 
int b[2001000];//以它开始的n个数中濒死值最小的点 
int q[2001000];//队列 
bool ans[2001000];//答案 
int main(){//所有加了"//"的地方都是两遍做不一样的地方，要好好理解，理解不了就都输出出来看一下 
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>v[i]>>d[i],
	v[i+n]=v[i],d[i+n]=d[i];
	
	//正向 
	for(int i=1,s=0;i<=n+n;i++)//
		a[i]=s,s+=v[i]-d[i];//
	h=0,t=0;
	for(int i=1;i<=n+n;i++)//
	{
		while(h<t&&a[i]<=a[q[t-1]])
		t--;
		q[t++]=i;
		while(h<t&&q[t-1]-q[h]>=n)//
		h++;
		b[i-n]=a[q[h]];//
	}
	for(int i=1;i<=n;i++)
	ans[i]|=(b[i]-a[i]>=0);//
	
	//反向 
	for(int i=n+n,s=0;i>=1;i--)//
		a[i]=s,s+=v[i]-d[i-1];//
	h=0,t=0;
	for(int i=n+n;i>=1;i--)//
	{
		while(h<t&&a[i]<=a[q[t-1]])
		t--;
		q[t++]=i;
		while(h<t&&q[h]-q[t-1]>=n)//
		h++;
		b[i]=a[q[h]];//
	}
	for(int i=1;i<=n;i++)
	ans[i]|=(b[i]-a[i+n]>=0);//
	
	for(int i=1;i<=n;i++)
	cout<<(ans[i]?"TAK":"NIE")<<endl;
}
/*
9
5 1
6 8
4 4
9 9
9 8
3 1
2 1
3 1
3 8
*/
```

---

## 作者：Pengzt (赞：8)

[P3422](https://www.luogu.com.cn/problem/P3422)

一道有点意思的题。

看到是一个环，先破环为链，即 $a_{n+i}=a_i, b_{n+i}=b_i$，此时就只需要跳到 $x+n$ 而无需判环了。

如果顺时针走：

令 $sum_i = \sum\limits_{j=1}^{i}{a_j-b_j}$，当能从 $x$ 跳到 $x+n$ 时，有

$$sum_{x-1} \le sum_x, sum_{x-1} \le sum_{x+1}, \dots, sum_{x-1} \le sum_{x+n-1}$$

变形一下：

$$sum_{x-1} \le \min\limits_{x \le i < x+n}\{sum_i\}$$

求长度不变区间的最小值，可以使用单调队列。

逆时针就反着再做一遍。

代码：

```cpp
#include<bits/stdc++.h>

using ll = long long;
using pii = std::pair<int, int>;

const int N = 1e6 + 5;
int n, hd, tl; 
int a[N << 1], b[N << 1], c[N << 1], q[N << 1];
int ta[N], tb[N], ans[N], flag[N];
ll s[N << 1];

void solve() {
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + c[i];
	for (int i = 1; i <= n; i++) s[i + n] = s[i + n - 1] + c[i];
	for (int i = 1, hd = 1, tl = 0; i <= n * 2; i++) {
		if (hd <= tl && q[hd] < i - n + 1) hd++;
		while (hd <= tl && s[q[tl]] >= s[i]) tl--;
		q[++tl] = i;
		if (i >= n)
			ans[i - n + 1] = s[q[hd]];
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i] >> b[i];
		a[i + n] = a[i], b[i + n] = b[i];
		c[i + n] = c[i] = a[i] - b[i];
	}
	solve();
	for (int i = 1; i <= n; i++)
		if (ans[i] >= s[i - 1])
			flag[i] = 1;
	for (int i = 1; i <= n; i++)
		c[i] = a[n - i + 1] - b[((n - i ? n - i : n))];
	solve();
	for (int i = 1; i <= n; i++)
		if (ans[i] >= s[i - 1])
			flag[n - i + 1] = 1;
	for (int i = 1; i <= n; i++)
		std::cout << (flag[i] ? "TAK" : "NIE") << "\n";
	return 0;
}
```

---

## 作者：Alex_Wei (赞：7)

> [P3422 [POI2005]LOT-A Journey to Mars](https://www.luogu.com.cn/problem/P3422)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

POI 真的很喜欢出 [单调队列](https://www.cnblogs.com/alex-wei/p/DP_Involution.html)！一开始看错题，以为可以来回走，以为是个神题，想了两个小时 ……

首先破环成链，考虑从 $i$ 开始顺时针方向 $i\to i + 1\to i + 2 \to \cdots \to i + n - 1 \to i + n$ 能不能走到，也就是要满足 $p_i \geq d_i$，$p_i + p_{i + 1}\geq d_i + d_{i + 1}$ …… **前缀和** 优化一下即对于每个 $k\in [i, i + n - 1]$，都要有 $p_k - p_{i - 1} \geq d_k - d_{i - 1}$，稍做变形得到 $p_{i - 1} - d_{i - 1} \leq \min\limits_{i\leq k < i + n} p_{i - 1} - d_{i - 1}$，经典的滑动窗口。

对于逆时针方向，同理要有 $d_{i - 1} - p_i \leq \min\limits_{i - n\leq k < i} d_{k - 1} - p_k$（手动模拟一下容易得到），也是滑动窗口。时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}

#define ll long long
const int N = 2e6 + 5;
ll n, q[N], p[N], d[N], ans[N], v1[N], v2[N];
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) p[n + i] = p[i] = read(), d[n + i] = d[i] = read();
	for(int i = 1; i <= n << 1; i++) p[i] += p[i - 1], d[i] += d[i - 1];
	for(int i = 1; i <= n << 1; i++) v1[i] = p[i] - d[i], v2[i] = d[i - 1] - p[i];
	for(int i = 1, hd = 1, tl = 0, r = 0; i <= n; i++) {
		while(hd <= tl && d[hd] < i) hd++;
		while(r < i + n - 1) {
			while(hd <= tl && v1[r + 1] <= v1[d[tl]]) tl--;
			d[++tl] = ++r;
		} ans[i] = v1[i - 1] <= v1[d[hd]]; 
	} for(int i = n << 1, hd = 1, tl = 0, l = i; i > n; i--) {
		while(hd <= tl && d[hd] >= i) hd++;
		while(l > i - n) {
			while(hd <= tl && v2[l - 1] <= v2[d[tl]]) tl--;
			d[++tl] = --l;
		} ans[i - n] |= v2[i] <= v2[d[hd]];
	} for(int i = 1; i <= n; i++) puts(ans[i] ? "TAK" : "NIE");
	return 0;
}
```

---

## 作者：Lagerent (赞：5)


- update:2022.7.8 改变了公式的陈述方式，更加清晰。 感谢 [aaaaaaaawsl](https://www.luogu.com.cn/user/307940) 建议

[题目传送门](https://www.luogu.com.cn/problem/P3422)

[博客食用更佳](https://www.luogu.com.cn/blog/477674/solution-p3422)

此题分别计算顺时针和逆时针的情况，推荐一种单调队列优化的做法(~~自认为蛮简单的~~)。

**顺时针**

首先我们拆环成链(数组开2倍)。

附图：

![](https://cdn.luogu.com.cn/upload/image_hosting/u2hytrll.png?x-oss-process=image/resize,m_lfit,h_330,w_1010)

$o_i$ 表示油量，$d_i$表示距离。

 $$s_i = \sum_{a = 1}^{i}o_i - d_i$$ 

**那么问题就转化为：** 判断一圈路径上是否每个 $o_i - d_i$ 都大于 $0$，我们仅需找到最小的并判断即可。

等价于在区间 $[i, i + n - 1]$ 中，对于其中任意的点 $j$ $(i \le j \le i + n - 1)$，有 $s_j - s_{i - 1} \ge 0$, 即 $i$ 固定，找到 $s_j$ 的最小值即可。

注意：

在枚举点 $i$ 时需要倒序遍历。

为什么呢？

枚举到点i时我们需要其后的 $n$ 个数据才能判断，换言之，$i$ 依赖于其后的 $n$ 个数据，只有后面的求出后才能判断 $i$ 点能否满足题意。

**Code**

```cpp
for(int i = 1; i <= n; i ++ ) s[i] = s[i + n] = o[i] - d[i];
    for(int i = 1; i <= 2 * n; i ++ ) s[i] += s[i - 1];
    
    q[0] = 2 * n + 1;
    int hd = 0, tl = 0;
    for(int i = 2 * n; i >= 1; i -- ) {
        while(hd <= tl && q[hd] > i + n - 1) hd ++ ;
        if(i < n) 
            if(s[q[hd]] - s[i - 1] >= 0) 
                ans[i] = true;
        while(hd <= tl && s[q[tl]] >= s[i - 1]) tl -- ;
        q[ ++ tl] = i - 1;
    }
```

**逆时针**

附图

![](https://cdn.luogu.com.cn/upload/image_hosting/mifw95mp.png?x-oss-process=image/resize,m_lfit,h_330,w_1010)

此时每个点的剩余油量会发生变化: $o_i - d_{i - 1}$(看图理解） 。

注意初始化：$d_0 = d_n$ (第一个点消耗的是第 $n$ 点的油)。

与顺时针同理，在 $[i - n +1, i]$ 区间内, 对于任意 $j$ $(i - n + 1 \le j \le i)$, $s_j - s_{i + 1} \ge 0$ 。

注意：此时需要正向枚举 $i$。

**Code**

```cpp
 d[0] = d[n];
    for(int i = 1; i <= n; i ++ ) s[i] = s[i + n] = o[i] - d[i - 1];
    for(int i = 1; i <= 2 * n; i ++ ) s[i] += s[i - 1];
    
    q[0] = 0;
    hd = 0, tl = 0;
    
    for(int i = 0; i <= 2 * n - 1; i ++ ) {
        while(hd <= tl && q[hd] < i - n + 1) hd ++ ;
        if(i + 1 > n) 
            if(s[i + 1] - s[q[hd]] >= 0)
                ans[i - n + 1] = true;
        while(hd <= tl && s[q[tl]] <= s[i + 1]) tl -- ;
        q[ ++ tl] = i + 1;
    }
 ```
 
 **时间复杂度**  $ O(n)$。
 
 让我们来看完整代码:
 
 ```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e6 + 10;

LL s[N << 1];
int o[N], d[N], n, q[N];
bool ans[N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ) scanf("%d%d", &o[i], &d[i]);
    
    for(int i = 1; i <= n; i ++ ) s[i] = s[i + n] = o[i] - d[i];
    for(int i = 1; i <= 2 * n; i ++ ) s[i] += s[i - 1];
    
    q[0] = 2 * n + 1;
    int hd = 0, tl = 0;
    for(int i = 2 * n; i >= 1; i -- ) {
        while(hd <= tl && q[hd] > i + n - 1) hd ++ ;
        if(i < n) 
            if(s[q[hd]] - s[i - 1] >= 0) 
                ans[i] = true;
        while(hd <= tl && s[q[tl]] >= s[i - 1]) tl -- ;
        q[ ++ tl] = i - 1;
    }
    
    d[0] = d[n];
    for(int i = 1; i <= n; i ++ ) s[i] = s[i + n] = o[i] - d[i - 1];
    for(int i = 1; i <= 2 * n; i ++ ) s[i] += s[i - 1];
    
    q[0] = 0;
    hd = 0, tl = 0;
    
    for(int i = 0; i <= 2 * n - 1; i ++ ) {
        while(hd <= tl && q[hd] < i - n + 1) hd ++ ;
        if(i + 1 > n) 
            if(s[i + 1] - s[q[hd]] >= 0)
                ans[i - n + 1] = true;
        while(hd <= tl && s[q[tl]] <= s[i + 1]) tl -- ;
        q[ ++ tl] = i + 1;
    }
    
    for(int i = 1; i <= n; i ++ )
        if(ans[i]) puts("TAK");
        else puts("NIE");
        
    return 0;
}
```

The End.


---

## 作者：Yaha (赞：3)

## 单调队列+前缀和

因为是环，原序列复制一遍放后面，这个不多赘述。

从1号点出发，方案不合法，当且仅当1号点后到n+1号点的途中存在至少一个点$sum(oil)-sum(d)<0$，也就是该点油不够用，其中$sum(oil)$和$sum(d)$为前缀和。

问题可以转变为，存在一个点$sum(oil-d)<0$时，从1号点出发的方案不合法。这两种是等价的。

也就是说，如果所有的$sum(oil-d)>=0$，方案合法。

此时我们再考虑起点不为1的方案。设起点为i，如果i~i+n-1这些点中所有的$sum_{(oil-d)}[j]-sum_{(oil-d)}[i-1]>=0$，方案合法；如果有一个不满足，方案就不合法。

那么，如果i~i+n-1中，最小的sum都满足呢？说明方案合法。如果不满足，说明方案不合法。说明，判断一种方案是否合法，只需要知道i~i+n-1中最小的sum。

显然，单调队列。

至于跑另一个方向，直接将整个序列翻转就行。

详情见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int amou=2e6+9;
int oil[amou],d[amou],sum[amou],temp[amou],q[amou],n,head,tail=-1;
bool is[amou];//标记是否合法
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&oil[i],&d[i]);
		sum[i]=sum[i-1]+oil[i]-d[i];
	}
	for(int i=n+1;i<=2*n;i++)
		sum[i]=sum[i-1]+oil[i-n]-d[i-n];
	for(int i=2*n-1;i>=1;i--)
	{
		while(head<=tail&&q[head]>=i+n) head++;
		while(head<=tail&&sum[q[tail]]>=sum[i]) tail--;
		q[++tail]=i;
		if(i<=n&&sum[q[head]]>=sum[i-1]) is[i]=1;
	}
	memset(sum,0,sizeof sum);
	memset(q,0,sizeof q);
	head=0,tail=-1;
	for(int i=1;i<=n;i++)
	{
		if(i!=n) temp[i]=oil[n-i+1]-d[n-i];//相当于翻转
		else temp[i]=oil[n-i+1]-d[n];
		sum[i]=sum[i-1]+temp[i];
	}
	for(int i=n+1;i<=2*n;i++)
		sum[i]=sum[i-1]+temp[i-n];
	for(int i=2*n-1;i>=1;i--)
	{
		while(head<=tail&&q[head]>=i+n) head++;
		while(head<=tail&&sum[q[tail]]>=sum[i]) tail--;
		q[++tail]=i;
		if(i<=n&&sum[q[head]]>=sum[i-1]) is[n-i+1]=1;//标记翻转前的编号
	}
	for(int i=1;i<=n;i++)
	{
		if(is[i]) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
```


---

## 作者：tanghairong (赞：2)

## P3422 思路

### 暴力模拟

对于每一个登陆点 $s$，依次顺时针和逆时针逐一模拟，若没有足够的油以支撑到下一个空间站，直接退出。

有一个注意点，顺时针模拟时对于当前的位置 $i$，走过的距离是 $d_{i-1}$ 而不是 $d_i$，而逆时针模拟时则是 $d_i$。

比如我现在在 $2$ 位置，若是顺时针模拟，就应该判断目前的 $sum$ 和 $d_1$ 的大小，若 $sum$ 小于 $d_1$ 就说明不能到达 $2$ 号空间站。

时间复杂度 $O(n^2)$，显然超时，可得70points。

```cpp
#include<iostream>
#define int long long
using namespace std;
int p[2000005],d[2000005];
signed main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p[i],&d[i]);
        p[i+n]=p[i];d[i+n]=d[i];
    }
    for(int s=1;s<=n;s++){
        int sum=p[s],flag=0;
        for(int i=s+1;i<=s+n;i++){
            sum-=d[i-1];
            if(sum<0){flag=1;break;}
            sum+=p[i];
        }
        if(flag==0){printf("TAK\n");continue;}
        sum=p[s],flag=0;
        for(int i=s+n-1;i>=s;i--){
            sum-=d[i];
            if(sum<0){flag=1;break;}
            sum+=p[i];
        }
        if(flag==0){printf("TAK\n");continue;}
        printf("NIE\n");
    }
    return 0;
}
```

### 正解：单调队列

本题解主要提供如何得出单调队列做法的推导步骤，对于单调队列的实现不多展开，其他的题解或模板[P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)已经有了非常详尽的解释。

1. 设从 $i$ 号空间站开始，顺时针旅行。

若要走通，即到达每一个空间站时油都够，必须满足：

$ 
\begin{cases}
p_i\ge d_i
\\
p_i+p_{i+1}\ge d_i+d_{i+1}
\\
\cdots\cdots
\\
p_i+\cdots+p_{i+n-1}\ge d_i+\cdots+d_{i+n-1}
\end{cases}
$

将不等式右边的移项至左边并适当调整顺序，可得：

$
\begin{cases}
p_i-d_i\ge 0
\\
(p_i-d_i)+(p_{i+1}-d_{i+1})\ge 0
\\
\cdots\cdots
\\
(p_i-d_i)+\cdots+(p_{i+n-1}-d_{i+n-1})\ge 0
\end{cases}
$

我们似乎看出了一点前缀和的影子。

令 $pre1_i$ 为 $p_i-d_i$ 的前缀和，则有：

$
\begin{cases}
pre1_i-pre1_{i-1}\ge0
\\
pre1_{i+1}-pre1_{i-1}\ge0
\\
\cdots\cdots
\\
pre1_{i+n-1}-pre1_{i-1}\ge0
\end{cases}
$

即：

$\min(pre1_i,\cdots,pre1_{i+n-1})\ge0$

在一个长度为 $2\times n$ 的数组（破环为链了）中求出任意一段长度为 $n$ 的数据的最大值，单调队列是最好的实现方式。

求出 $p_i-d_i$ 的前缀和 $pre1_i$，将 $pre1$ 数组带入双端队列 ```deque``` 中进行单调队列的模板操作即可（具体实现看代码）

2. 设从 $i$ 号空间站开始，逆时针旅行

注意：为防止越界，本部分定为从 $i+n$ 号空间站开始，至 $i$ 号空间站结束（也是经过了破环为链的）。

若要走通，必须满足：

$
\begin{cases}
p_{i+n}\ge d_{i+n-1}
\\
p_{i+n}+p_{i+n-1}\ge d_{i+n-1}+d_{i+n-2}
\\
\cdots\cdots
\\
p_{i+n}+\cdots+p_{i+1}\ge d_{i+n-1}+\cdots+d_i
\end{cases}
$

结合上面的模拟可知，从 $k$ 号空间站到 $k-1$ 号空间站，经过的距离是 $d_{k-1}$，有了这个就不难理解了。

同上，移项并适当调整顺序，可得：

$
\begin{cases}
p_{i+n}-d_{i+n-1}\ge0
\\
(p_{i+n}-d_{i+n-1})+(p_{i+n-1}-d_{i+n-2})\ge0
\\
\cdots\cdots
\\
(p_{i+n}-d_{i+n-1})+\cdots+(p_{i+1}-d_i)\ge0
\end{cases}
$

我们似乎看出了一点后缀和的影子。

（这里不用前缀和是因为这里是后端平齐而第一部分是前端平齐）

令 $pre2_i$ 为 $p_i-d_{i-1}$ 的后缀和，可得到：

$pre2_i=pre2_{i+1}+p_i-d_{i-1}(1\leq i\leq 2\times n)$

因为是后缀和，所以 $pre2_i\le pre2_j(i>j)$

则有：

$
\begin{cases}
pre2_{i+n}-pre2_{i+n+1}\ge0
\\
pre2_{i+n-1}-pre2_{i+n+1}\ge0
\\
\cdots\cdots
\\
pre2_{i+1}-pre2_{i+n+1}\ge0
\end{cases}
$

即：

$\min(pre2_{i+1},\cdots,pre2_{i+n})\ge pre2_{i+n+1}$

又是一个单调队列的板子。与第一种情况基本相同，再打一遍单调队列即可，不做过多分析了，具体见代码。

## code

几个注意点：

+ 由于有了破环为链，数组开 $2\times n$大小

+ 两遍单调队列中间记得清空队列并重新初始化（在本代码中体现为：1.插入第一个元素的序号和 $pre$ 值 2.$i=2$）

+ 注意理解 $pre1$ 和 $pre2$ 计算方法的异同

```cpp
#include<iostream>
#include<queue>
using namespace std;
int pre1[2000005],pre2[2000005],p[2000005],d[2000005];
int ans1[2000005],ans2[2000005];
deque<pair<int,int> >q; 
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i]>>d[i],p[i+n]=p[i],d[i+n]=d[i];
    for(int i=1;i<=2*n;i++)pre1[i]=pre1[i-1]+p[i]-d[i];
    for(int i=2*n;i>0;i--)pre2[i]=pre2[i+1]+p[i]-d[i-1];
    q.push_back(make_pair(1,pre1[1]));
    int i=2;
    while(!q.empty()){
        if(i>2*n)break;
        while(!q.empty()&&i-q.front().first+1>n)q.pop_front();
        while(!q.empty()&&pre1[i]<=q.back().second)q.pop_back();
        q.push_back(make_pair(i,pre1[i]));
        if(i>=n)ans1[i-n+1]=q.front().second;
        i++;
    }
    q.clear();
    q.push_back(make_pair(1,pre2[1]));
    i=2;
    while(!q.empty()){
        if(i>2*n)break;
        while(!q.empty()&&i-q.front().first+1>n)q.pop_front();
        while(!q.empty()&&pre2[i]<=q.back().second)q.pop_back();
        q.push_back(make_pair(i,pre2[i]));
        if(i>=n)ans2[i-n+1]=q.front().second;
        i++;
    }
    for(int s=1;s<=n;s++){
        if(ans1[s]>=pre1[s-1]||ans2[s+1]>=pre2[s+n+1])cout<<"TAK"<<endl;
        else cout<<"NIE"<<endl;
    }
    return 0;
}

---

## 作者：nekko (赞：2)

对于圆（环）上的问题，一般都可以转换成序列上的问题（比如说合并石子）

对于这道题，将环复制一下然后从(1,n)连接处断开，成为[1,2,3...,n,1,2,3,...n]这样的一个序列

然后问题就转换成了对于每一个点，是否能向右走n步（这里只讨论向右走，向左走同理，但需要注意d[]所表示的意义）

这就可以使用类似于记忆化搜索的东西了（其实也可以当成并查集），另f[i][0/1]表示i往右走最远能到达哪里(1)，并且此时剩下多少燃油(0)，然后这个就类似于dp＋贪心的转移了

思路很直接，但是实现的时候略微感觉mengbier，强烈建议独立code&submit，如果WA了的话可以写一个暴力（暴力比正解难写系列）

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 2100000;

int f[N][2], p[N], d[N], n, ans[N];

// <剩余燃料,最远到达位置>

void calc(bool flag) {
    memset(f, 0, sizeof(f));
    f[2 * n][0] = p[2 * n];
    f[2 * n][1] = 2 * n;
    for(int i = 2 * n - 1 ; i >= 1 ; -- i) {
        f[i][0] = p[i];
        f[i][1] = i;
        while(f[i][0] >= d[f[i][1]] && f[i][1] + 1 <= 2 * n) {
            f[i][0] = f[f[i][1] + 1][0] + f[i][0] - d[f[i][1]];
            f[i][1] = f[f[i][1] + 1][1];
        }
    }
    if(flag) {
        for(int i = 1 ; i <= n ; ++ i) {
            ans[i] |= (f[i][1] - i >= n);
        }
    } else {
        for(int i = 1 ; i <= n ; ++ i) {
            ans[n - i + 1] |= (f[i][1] - i >= n);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &p[i], &d[i]);
        p[i + n] = p[i];
        d[i + n] = d[i];
    }
    calc(1);
    reverse(p + 1, p + 1 + 2 * n);
    reverse(d + 1, d + 1 + 2 * n);
    d[2 * n + 1] = d[1];
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        d[i] = d[i + 1];
    }
    calc(0);
    for(int i = 1 ; i <= n ; ++ i) {
        if(ans[i]) {
            puts("TAK");
        } else {
            puts("NIE");
        }
    }
    return 0;
}
```

---

## 作者：luogu_gza (赞：1)

智商不够，数据结构来凑。

发现题目需要满足的就是

$$\min\{s_j\} \geq s_i$$

这个东西就很好维护了，枚举 $s_i$，然后套个不带修改的线段树即可。

注意，两个方向都要建一遍线段树，所以我封装了一下。

我觉得这东西 zkw 也可以维护，代码甚至短一截。

[广告](https://www.luogu.com.cn/blog/gza/poi20012005-post)

Code:

```cpp
// Problem: P3422 [POI2005] LOT-A Journey to Mars
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3422
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define MT int TTT=R;while(TTT--)
#define pc putchar
#define R read()
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a,b) for(int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
namespace IO
{
	inline int read()
	{
	    int x=0;
	    char ch=getchar();
	    bool f=0;
	    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
	    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	    if(f) x=-x;
	    return x;    
	}
	template<typename T> inline void write(T x)
	{
	    if(x<0)
	    {
	        pc('-');
	        x=-x;
	    }
	    if(x>9) write(x/10);
	    pc(x%10+'0');
	}
};
namespace math
{
	inline int gcd(int a,int b)
	{
		return b?gcd(b,a%b):a;
	}
	inline int qmi(int a,int b,int p)
	{
		int res=1;
		while(b)
		{
			if(b&1) res=res*a%p;
			a=a*a%p;
			b>>=1;
		}
		return res;
	}
	inline int inv(int a,int p)
	{
		return qmi(a,p-2,p);
	}
	const int MAXN=2e6+10;
	int my_fac[MAXN],my_inv[MAXN];
	void init_binom(int mod)
	{
		my_fac[0]=1;fo(i,1,min(MAXN,mod)-1) my_fac[i]=my_fac[i-1]*i%mod;
		my_inv[min(MAXN,mod)-1]=qmi(my_fac[min(MAXN,mod)-1],mod-2,mod);rep(i,min(MAXN,mod)-2,0) my_inv[i]=my_inv[i+1]*(i+1)%mod;
	}
	int binom(int a,int b,int mod)
	{
		return my_fac[a]*my_inv[b]%mod*my_inv[a-b]%mod;
	}
}
using namespace IO;
using namespace math;

#define now tr[u]
#define ls tr[u<<1]
#define rs tr[u<<1|1]
const int N=1e6+10;
int n;
int p[N],d[N],s[N],S[N];
struct SegmentTree{
	struct Node{
		int l,r,d;
	}tr[N<<2];
	void pushup(int u)
	{
		now.d=min(ls.d,rs.d);
	}
	void build(int u,int l,int r,int typ)
	{
		if(l==r) tr[u]={l,r,typ==1?s[l]:S[l]};
		else
		{
			tr[u]={l,r};
			int mid=l+r>>1;
			build(u<<1,l,mid,typ),build(u<<1|1,mid+1,r,typ);
			pushup(u);
		}
	}
	int query(int u,int l,int r)
	{
		if(tr[u].l==l&&tr[u].r==r) return tr[u].d;
		else
		{
			int mid=now.l+now.r>>1;
			if(r<=mid) return query(u<<1,l,r);
			else if(l>mid) return query(u<<1|1,l,r);
			else return min(query(u<<1,l,mid),query(u<<1|1,mid+1,r));
		}
	}
}tr1,tr2;
signed main(){
	n=R;
	fo(i,1,n) p[i]=R,d[i]=R,s[i]=s[i-1]+p[i]-d[i];
	fo(i,n+1,2*n) s[i]=s[i-1]+p[i-n]-d[i-n];
	fo(i,1,n-1) S[i]=S[i-1]+p[n-i+1]-d[n-i];
	S[n]=S[n-1]+p[1]-d[n];
	fo(i,n+1,2*n-1) S[i]=S[i-1]+p[2*n-i+1]-d[2*n-i];
	tr1.build(1,1,n*2-1,1);
	tr2.build(1,1,n*2-1,2);
	fo(i,1,n)
	{
		if(tr1.query(1,i,i+n-1)>=s[i-1]) puts("TAK");
		else if(tr2.query(1,n-i+1,2*n-i)>=S[n-i]) puts("TAK");
		else puts("NIE");
	}
}

```

---

## 作者：Bulyly (赞：1)

### 优先队列优化

- 对于环的处理，参考区间 DP 可以将环破坏成链。

- 考虑每个加油站的贡献即 $p-d$，维护贡献的前缀和。

- 对于每一种合法情况，路上的任意前缀恒不小于 $0$。

- 对于方向，正反跑两边就行。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

typedef long long LL;

const int N=1e6+10,M=N<<1;

int n;
int p[M],d[M];
LL a[M],s[M];
bool f[N];
deque<int> q;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)  scanf("%d%d",&p[i],&d[i]);
	
	for(int i=1;i<=n;i++)  a[i]=a[n+i]=p[i]-d[i];
	for(int i=1;i<=n<<1;i++)  s[i]=s[i-1]+a[i];
	q.push_back(0);
	bool fg=0;
	for(int i=1;i<=n<<1;i++)
	{
		while(q.size() && i-q.front()>n)  q.pop_front();
		while(q.size() && s[q.back()]>=s[i])  q.pop_back();
		q.push_back(i);
		if(i>=n && s[q.front()]-s[i-n]>=0) f[i-n+1]=1;  
	}
	
	d[0]=d[n],q.clear();
	for(int i=1;i<=n;i++)  a[i]=a[n+i]=p[n-i+1]-d[n-i];
	for(int i=1;i<=n<<1;i++)  s[i]=s[i-1]+a[i];
	q.push_back(0);
	for(int i=1;i<=n<<1;i++)
	{
		while(q.size() && i-q.front()>n)  q.pop_front();
		while(q.size() && s[q.back()]>=s[i])  q.pop_back();
		q.push_back(i);
		if(i>=n && s[q.front()]-s[i-n]>=0)  f[n<<1-i]=1;  
	}
	
	for(int i=1;i<=n;i++)
	{
        if(f[i]) puts("TAK");
        else puts("NIE");
    }
	return 0;
}
```
完结撒花~


---

## 作者：Fool_Fish (赞：1)

首先我们有一个非常暴力的思路：每一个站的油减去它到下一个站的距离是什么？

可以抽象的理解为这个站对本次旅行的油的贡献

如果贡献为正，说明走了这一个站后油不会减，反而会增加

如果贡献为负，则相反，是在减油

如果连续经过了几个站，这些站的“贡献”让现在的油减的小于零了，那么就一定行不通了对吧

所以我们对从头开始像某一个方向，对上面说的东西求一个前缀和 $sum$，如果到某一个地方这个前缀和变成了负的，就说明不行了

即：问题就变成了枚举起点i，判断在经过的车站中是否存在一个车站j，使得$sum[j]-sum[i]<0$，如果是，那么就不合法。

但是这个算法的时间复杂度是$O(n^2)$的。

所以我们移一下项，变为判断$sum[j]<sum[i]$，所以就是判断对于每一个起点$i$，其经过车站中$sum[j]$的最小值是否小于$sum[i]$。

因此我们可以用一个单调队列来维护一个前缀和的最小值，时间复杂度降低到了$O(n)$。

具体的实现可以参考一下代码

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int MAXN=1e6+5;
#define int long long
int a[MAXN*2],b[MAXN*2],c[MAXN*2],ans[MAXN*2][2];
int sum1[MAXN*2];
int sum2[MAXN*2];
int n,head,tail;
int q[MAXN*2];
signed main(){
    scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld %lld",&a[i],&b[i]);
		a[i+n]=a[i];
		b[i+n]=b[i];
		c[i+n]=c[i]=b[i-1];
	}
    c[1]=c[n+1]=b[n];
    for(int i=1;i<=n*2;i++){
    	sum1[i]=sum1[i-1]+a[i]-b[i];
	}
	for(int i=n*2;i>=1;i--){
		sum2[i]=sum2[i+1]+a[i]-c[i];
	}
	int head=1,tail=1;
    head=tail=1;
	q[head]=0;
    for(int i=1;i<=n*2;i++){
        while(head<=tail&&q[head]+n+1<=i){
			ans[q[head++]+1][0]=0;
		}
        while(head<=tail&&sum1[q[tail]]>sum1[i]){
			ans[q[tail--]+1][0]=1;
		}
        q[++tail]=i;
    }
    head=tail=1;
	q[tail]=n*2+1;
    for(int i=n*2;i>=1;i--){
        while(head<=tail&&q[head]-n-1>=i){
			ans[q[head++]-1][1]=0;
		}
        while(head<=tail&&sum2[q[tail]]>sum2[i]){
			ans[q[tail--]-1][1]=1;
		}
        q[++tail]=i;
    }
    for(int i=1;i<=n;i++){
        if(ans[i][0]&ans[i+n][1]) puts("NIE");
        else puts("TAK");
    }
    return 0;
}
```

---

## 作者：hanyuchen2019 (赞：0)

校内模拟赛出了这题，被虐哭了/kk

**注**：下文中 $(x,y)$ 表示从 $x$ 号站走到 $y$ 号站（包括走到 $y$ 的下一个点所耗的油）所剩油量。

### part 1

首先把这个环展开成长度为 $2n$ 的链，问题就转化成了 $\forall 1\le i\le n$，$[i,n+i-1]$ 这个区间内的问题。

为了方便叙述，先只考虑正着走的情况。

题目要求油箱中的油是否耗尽，相当于维护旅行中油量的最小值，判断其是否 $<0$，也就是维护 $(i,i),(i,i+1)...(i,n+i-1)$ 的最小值。

我们可以先从 $1$ 号站走到 $2n$ 号站，一路上统计剩余油量（数组 $s$）。这样，就可以通过 $(x,y)=(1,y)-s_{x-1}$ 的方式快速求值。

于是，我们可以把要求的东西转换为 $[(1,i)-s_{x-1}],[(1,i+1)-s_{x-1}],...,[(1,n+i-1)-s_{x-1}]$。

然后再把 $s_{x-1}$ 提出来，就发现原问题变成了求 $[i,n+i-1]$ 的区间最小值是否大于等于 $s_{x-1}$。

### part 2

维护这个东西，除了用[滑动窗口](/problem/P1886)（大部分题解的做法），还可以直接线段树大力出奇迹。

有个巨坑的地方：线段树开 $4$ 倍空间，但别忘了由于原环被复制了两倍，一共要开 $8\times10^6$ 的数组。

### part 3

这题很恶心的地方在于反过来的部分。

首先把 $p$ 数组正常翻转，但由于 $d_i$ 表示的是 $i$ 这个点到**下一个**点的距离，所以翻转的下标要 $-1$。

还有一个坑点：统计答案的时候要翻转回来。

### part 4


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	//略
}
int n,a[2000005],b[1000005];
ll s[2000005];
ll tr[8000005];
void pushup(int u)
{
	tr[u]=min(tr[u<<1],tr[(u<<1)+1]);
}
void build(int l,int r,int u)
{
	if(l==r)
	{
		tr[u]=s[l];
		return;
	}
	int m=l+r>>1;
	build(l,m,u*2);
	build(m+1,r,u*2+1);
	pushup(u);
}
ll query(int L,int R,int l,int r,int u)
{
	if(L<=l&&r<=R)return tr[u];
	int m=(l+r)>>1;
	ll ans=INT_MAX;
	if(L<=m)ans=min(ans,query(L,R,l,m,u*2));
	if(R>=m+1)ans=min(ans,query(L,R,m+1,r,u*2+1));
	return ans;
}
bool f[1000005];
int main()
{
	int n=read();
	for(int i=1;i<=n;++i)a[i]=read(),b[i]=read();
	for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i]-b[i];
	for(int i=1;i<=n;++i)s[i+n]=s[i+n-1]+a[i]-b[i];
	build(1,2*n,1);//记得乘2
	for(int i=1;i<=n;++i)
		if(query(i,i+n-1,1,2*n,1)>=s[i-1])f[i]=1;
	
	for(int i=1;i<n-i+1;++i)swap(a[i],a[n-i+1]);
	for(int i=1;i<n-i;++i)swap(b[i],b[n-i]);//翻转-1
	for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i]-b[i];
	for(int i=1;i<=n;++i)s[i+n]=s[i+n-1]+a[i]-b[i];
	build(1,2*n,1);
	for(int i=1;i<=n;++i)
		if(query(i,i+n-1,1,2*n,1)>=s[i-1])f[n-i+1]=1;
	for(int i=1;i<=n;++i)
	{
		if(f[i])puts("TAK");
		else puts("NIE");
	}
	return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：0)

## 前言

[传送门](https://www.luogu.com.cn/problem/P3422)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-p3422)

长沙市一中暑假第一次思维训练。

#### 前置芝士

[前缀和](hhttps://zhuanlan.zhihu.com/p/117569086)

[单调队列](https://oi.wiki/ds/monotonous-queue/)

# 思路

在考试过程中突然发现与[好消息，坏消息](https://www.luogu.com.cn/problem/P2629)题目大致相同，不同之处只有这个可以往逆时针方向走，以此确定本题算法——**前缀和与单调队列**。

首先我们可以算出每一个站点可以拿到的油 $p_i - d_i$，也就是油量 $-$ 到下一站的距离，然后我们就将其围成一个环，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/1u1mf2wj.png)

这样在我们随意选取以 $x$ 开头的长度为 $n$ 的一段，这时候也就算我们走完一圈 。而我们所要知道的就是在这一段之中，有没有油量 $\le 0$ 的时候，我们可以使用前缀和算取某一段区间的油量的总合。

我们要把每一段都算一遍吗？不对，只需要用最小的减去当前的，如果最小的不行，那此方案肯定是不行的。

如何维护最小值呢？我们可以使用单调队列维护，接下来就可以写代码了。

# AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,p[2000010],d[2000010],sum[2000010];

bool ans[2000010];

signed main(){
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)
		scanf("%lld%lld",p + i,d + i);
	for(int i = 1;i < n;i++){
		sum[i + n] = sum[i] = p[i] - d[i];
	}
	for(int i = 1;i < 2 * n;i++){
		sum[i] += sum[i - 1];
	}
	deque<int>q;
	for(int i = 2 * n - 1;i;i--){
        while(!q.empty() && q.front() >= i + n)q.pop_front();
        while(!q.empty() && sum[q.back()] >= sum[i]) q.pop_back();
        q.push_back(i);
		if(i <= n){
			if(sum[q.front()] >= sum[i - 1]){
				ans[i] = 1;
			}
		}
	}

    d[0] = d[n];
    for(int i = 1;i < n;i++){
		sum[i + n] = sum[i] = p[i] - d[i - 1];
	}
	for(int i = 1;i < 2 * n;i++){
		sum[i] += sum[i - 1];
	}
    deque<int>x;
	for(int i = 1;i < n * 2;i++){
        while(!x.empty() && x.front() < i - n)x.pop_front();
		if(i > n){
			if(sum[x.front()] <= sum[i]){
				ans[i - n] = 1;
			}
		}
        while(!x.empty() && sum[x.back()] <= sum[i]) x.pop_back();
        x.push_back(i);
	}
    for(int i = 1;i <= n;i++){
        if(ans[i]){
            cout<<"TAK"<<endl;
        }else{
            cout<<"NIE"<<endl;
        }
    }
} 
```

---

## 作者：oscar (赞：0)

【POI补全计划#6 POI2005 LOT】

先考虑从1号点开始时如何判定能否绕一圈

发现只要对油量和路程的差求一下前缀和看一下2~n+1号空间站中有没有剩余油量小于0的位置（假设走到n+1号空间站自动瞬移到1号空间站）

又发现从第k个空间站出发相当于不管前面k-1个空间站，查询 k+1~n+1号空间站剩余油量 和 （1~k号空间站剩余油量 + n+1号空间站剩余油量） 是否有小于0的

这个信息可以通过一开始1号点出发的信息和k号空间站的前缀和处理出来，于是预处理一下从1号空间站开始时的那个前缀和的前缀min和后缀min就可以O(1)查询了

条件大概长这样

```cpp
mins[i+1]-delta>=0&&sum[n+1]-delta>=0&&sum[n+1]-delta+minp[i]>=0
```
（其中mins为前缀和的后缀min，minp为前缀和的前缀min，delta为第i个空间站的前缀和，sum[n+1]是所有油量总和减去所有路程总和）

最后反向处理一遍，判断沿编号减小方向走能不能回来就好了

~~不要忘了第i行的那个距离代表的是i~i+1间的距离，如果像我一样变换坐标算的话要重排一下距离~~

最后照例贴代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1000010;
int len[MAXN],fuel[MAXN],sum[MAXN],minp[MAXN],mins[MAXN],ans[MAXN];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&fuel[i],&len[i]);
    memset(minp,0x7f,sizeof(minp));
    memset(mins,0x7f,sizeof(mins));
    for(int i=1;i<=n;++i)
    {
        sum[i+1]=sum[i]+fuel[i]-len[i];
        if(minp[i]>sum[i+1])minp[i+1]=sum[i+1];
        else minp[i+1]=minp[i];
    }
    for(int i=n+1;i>1;--i)
    {
        if(mins[i+1]>sum[i])mins[i]=sum[i];
        else mins[i]=mins[i+1];
    }
    int delta;
    for(int i=1;i<=n;++i)
    {
        delta=sum[i];
        if(mins[i+1]-delta>=0&&sum[n+1]-delta>=0&&sum[n+1]-delta+minp[i]>=0)ans[i]|=1;
    }
    int tmp=len[n];
    for(int i=n;i>=1;--i)
        len[i]=len[i-1];
    len[1]=tmp;
    for(int i=1;i<n-i+1;++i)
    {
        swap(fuel[i],fuel[n-i+1]);
        swap(len[i],len[n-i+1]);
    }
    memset(minp,0x7f,sizeof(minp));
    memset(mins,0x7f,sizeof(mins));
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;++i)
    {
        sum[i+1]=sum[i]+fuel[i]-len[i];
        if(minp[i]>sum[i+1])minp[i+1]=sum[i+1];
        else minp[i+1]=minp[i];
    }
    for(int i=n+1;i>1;--i)
    {
        if(mins[i+1]>sum[i])mins[i]=sum[i];
        else mins[i]=mins[i+1];
    }
    for(int i=1;i<=n;++i)
    {
        delta=sum[i];
        if(mins[i+1]-delta>=0&&sum[n+1]-delta>=0&&sum[n+1]-delta+minp[i]>=0)ans[n-i+1]|=1;
    }
    for(int i=1;i<=n;++i)
    {
        if(ans[i])printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}
```
update@2017.9.14

增加标题，增加部分详细描述


---

