# UPDATEIT - Update the array !

## 题目描述

你有一个 $n$ 个元素的数组，初始全为 $0$，编号为 $0,\dots,n-1$。  
你需要对其做 $u$ 次修改操作。每个修改操作你需要把区间 $[l,r]$ 内的元素加上一个值 $val$。  
之后，会有 $q$ 次查询，每次查询下标为 $i$ 的数。

## 样例 #1

### 输入

```
1
5 3
0 1 7
2 4 6
1 3 2
3
0
3
4```

### 输出

```
7
8
6```

# 题解

## 作者：Kano_zyc (赞：6)

## 闲话

看到大家都用的线段树或者差分，就连唯一一篇分块也极其抽象。就让本蒟蒻来~~详细~~讲解一下（笑）。

## 分块の介绍

首先，什么是分块呢？我来引用一下 wiki 上的话：“通过对原数据的适当划分，并在划分后的每一个块上预处理部分信息，从而较一般的暴力算法取得更优的时间复杂度。”

那么具体如何划分呢？对于一个长度为 $n$ 的序列，我们一般以 $\sqrt{n}$ 的长度为一整块，和一些散块，最后暴力处理每个块即可。放张图辅助理解一下。

![114514](https://cdn.luogu.com.cn/upload/image_hosting/f1da0iwm.png)

相信大家都已经发现分块的本质了吧，他就是一个度数为 $\sqrt{n}$，只有三层的树（记住这一点，后面学线段树时更好理解）。我再来放张图。

![114](https://cdn.luogu.com.cn/upload/image_hosting/o1trc920.png)

## 分块的基本代码

既然已经理解了分块，让我们来看一下代码实现。

首先，我们需要建立分块序列（为了防止某些人复制粘贴，这里放图片）。

![1145](https://cdn.luogu.com.cn/upload/image_hosting/l1pd9b0e.png)

然后，执行修改操作即可。这里讲个思路，只有两点要讲。

- 每次修改只有更新 $\sqrt{n}$ 个 size 为 $1$ 的节点以及几个 size 为 $\sqrt{n}$ 的节点。

- 注意我们不用维护那个 size 为 $n$ 的根节点的信息。

代码实现呢也非常简单，如果你看懂了上面的内容，相信你一定会写此题。我就不贴代码了。

再见！


---

## 作者：pfrig729 (赞：3)

看到这题题解有很多是用差分做的，其实也可以用 **分块** 做。

分块基础可以看 https://zhuanlan.zhihu.com/p/42089861。

在本题中，我们将所有数分成 $\sqrt{n}$ 个区间，对于每次修改，如果包括了整个区间，我们就直接将整个区间修改，最后查询时加上，如果是零散的区间，那么就修改单值。

详细解释看注释。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,sqr,a[50005],b[50005],d[500005];
void add(int x,int y,int z)
{
	for(int i=x;i<=min(y,b[x]*sqr);i++)//b[x]*sqr是x所在区间的最后一个数
	{
		a[i]+=z;
	}
	if(b[x]!=b[y])
	{
		for(int i=(b[y]-1)*sqr+1;i<=y;i++)//(b[y]-1)*sqr+1是y所在区间的最后一个数
		{
			a[i]+=z;
		}
	}
	for(int i=b[x]+1;i<=b[y]-1;i++)//此循环内的都是完整区间
	{
		d[i]+=z;//d[i]表示i这个区间里所有的数都要加上的值
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n,u,q;
		memset(a,0,sizeof a);//记得初始化
		memset(d,0,sizeof d);
		scanf("%d%d",&n,&u);
		sqr=sqrt(n);
		for(int i=1;i<=n;i++)
		{
			b[i]=(i-1)/sqr+1;//b[i]表示i在哪个区间(sqrt(n)为一个区间)
		}
		while(u--)
		{
			int l,r,c;
			scanf("%d%d%d",&l,&r,&c);
			add(l,r,c);
		}
		scanf("%d",&q);
		while(q--)
		{
			int i;
			scanf("%d",&i);
			printf("%d\n",a[i]+d[b[i]]);
		}
	}
	return 0;
}
```

---

## 作者：xu222ux (赞：3)

# [UPDATEIT - Update the array !](https://www.luogu.com.cn/problem/SP16487)

## 思路

本题是一道差分的板子。

由于此题修改和查询是分开的，所一很容易想到差分。

说一下什么是差分数组。差分数组的前缀和数组是原数组，然后会发现这个差分数组有一个性质，就是区间加可以只改动两个数就可以改动他们之间的所有数。

写法详见代码。

## ACcode

```cpp
//建议评黄
#include<bits/stdc++.h>
using namespace std;
int n,q;
int c[10005];
int main(){
	int t;cin>>t;
	while(t--){
		cin>>n>>q;
		memset(c,0,sizeof(c));
		while(q--){
			int l,r,f;cin>>l>>r>>f;
			c[l]+=f,c[r+1]-=f;//差分修改
		}
		for(int i=1;i<=n;i++)c[i]+=c[i-1];//求出原数组
		cin>>q;
		while(q--){
			int query;cin>>query;
			cout<<c[query]<<endl;//输出不多说了
		}
	}
	return 0;
} 
```

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/SP16487)

## 题目大意
给定一组有 $n$ 元素的序列，刚开始全部为 $0$，将该序列进行多次操作，每次对一个区间 $[l,r]$ 内的数加上 $val$。此外，还需要单点修改，即给定 $i$，输出修改后的 $a_i$。

## 解题思路
这道题~~似乎~~差分，线段树，分块都可以，但本蒟蒻只会差分，那么就讲一下差分做法。

差分数组与前缀和数组的形式是类似的，那么我们可以利用差分数组的性质。差分数组的性质是什么呢？

- **差分数组的前缀和数组就是原数组**。

由于这道题修改查找分开，所以我们先修改，再求前缀和。还有一点就是，区间加上一个固定值时，**只需修改两个元素**（即两个端点），因此这道题的区间加我们可以写成：
```cpp
a[l]+=val,a[r+1]-=val;
```
继而，在输出时，利用差分数组性质得到原数组即可（具体见代码）！

## AC Code：
```cpp
#include<bits/stdc++.h>//万能
using namespace std;
int t,a[100054];
int main()
{
	int n,u,l,r,val,q,i;//定义，同题意
	cin>>t;
	while(t--)
	{
		cin>>n>>u;
		memset(a,0,sizeof a);//初始化
		//for(i=1;i<=n;i++)
		//	a[i]=0;
		while(u--)
		{
			cin>>l>>r>>val;
			a[l]+=val;
			a[r+1]-=val;//区间差分修改，两个端点即可
		}
		for(i=1;i<=n;i++)
			a[i]+=a[i-1];//前缀和，得出原数组
		cin>>q;
		while(q--)
		{
			cin>>i;
			cout<<a[i]<<"\n";//输出即可
		}
	}
	return 0;//好习惯
}

```
#### 拒绝代码抄袭，创建和谐洛谷！

---

## 作者：chl090410 (赞：0)

## The Solution to SP16487 UPDATEIT - Update the array !

### Description

有一个全部为 $0$ 的数组，现在先对几个给定的区间加上一个特定的值，之后有 $q$ 次查询，每次查询数组中下标为 $i$ 的元素的值。

### Solution

因为 $1\le n\le10^4,1\le u\le10^5$，所以暴力修改是会超时的。

而题目中说先修改再查询，所以考虑[差分](https://oi-wiki.org/basic/prefix-sum/)。

我们先举个例子，设 $a$ 数组（下标从 $0$ 开始）中的元素分别为 $a,b,c,d,e$，其差分数组 $b$ 则为 $a,b-a,c-b,d-c,e-d$。

现在我们给 $[1,3]$ 中的元素都加上 $3$，则 $a$ 数组变为 $a,b+3,c+3,d+3,e$，$b$ 数组变为 $a,b-a+3,c-b,d-c,e-d-3$，可以看出，$b_1$ 加了 $3$，而 $b_{4}$，即 $b_{3+1}$ 减了 $3$。

类似，若 $a$ 数组的 $[l,r]$ 区间加了 $k$，则 $b_l+k,b_{r+1}-k$ 即可。

而修改完后再对 $b$ 数组求前缀和就可得到修改后的 $a$ 数组。之后对于查询，直接 $O(1)$ 输出即可。

总时间复杂度 $O(n+u+q)$，就不会超时了。

### 完整代码如下:

```
#include<bits/stdc++.h>
using namespace std;
int n,m,t,l,r,k,q,p;
int a[10005],b[10005];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=0;i<n;i++){
			a[i]=0;
			b[i]=0;
		}
		for(int i=1;i<=m;i++){
			cin>>l>>r>>k;
			b[l]+=k;
			b[r+1]-=k;
		}
		for(int i=0;i<n;i++){
			a[i]=a[i-1]+b[i];
		}
		cin>>q;
		for(int i=1;i<=q;i++){
			cin>>p;
			cout<<a[p]<<endl;
		}
	}
	return 0;
}

---

## 作者：Weekoder (赞：0)

# SP16487 UPDATEIT - Update the array ! 题解
## 题目大意
需要设计一种数据结构并维护一个序列，初始时全部为 $0$，有多次操作，每次选择一个区间 $[l,r]$ 并将区间内的数全部加上 $val$。还需要支持单点查询，即给出 $i$，求修改过后的 $a_i$。
## 分析
其实上面所述的数据结构就是差分。差分数组 $D$ 的定义是：$D_i=a_i-a_{i-1}$。他和前缀和很像，因为上面的式子移项过后就变成了和前缀和一样的形式：$a_i=a_{i-1}+D_i$，并且差分数组做两次前缀和后也会得到原数组的前缀和数组，做一次前缀和会得到原数组。

前缀和可以以 $O(1)$ 的速度查询区间和，以 $O(n)$ 的速度进行单点修改，而差分相反。差分可以以 $O(n)$ 的速度查询区间和，以 $O(1)$ 的速度进行单点修改。但是差分数组可以预处理，一口气进行多个单点查询。这里题目要求的区间修改，单点查询正好符合差分的运用。差分中将区间 $[l,r]$ 全部加上 $val$ 可以写成这样：
```cpp
d[l] += val, d[r + 1] -= val;
```
在输出时，我们利用差分数组的性质，对差分数组做一遍前缀和得到原数组就可以了。
# $\text{Code:}$
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

int T, d[N];

int main() {
    cin >> T;
    while (T --) {
        memset(d, 0, sizeof d);
        int n, u;
        cin >> n >> u;
        while (u --) {
            int l, r, val;
            cin >> l >> r >> val;
            d[l] += val, d[r + 1] -= val;
        }
        for (int i = 1; i <= n; i++) d[i] += d[i - 1];
        int q; cin >> q;
        while (q --) {
            int i; cin >> i;
            cout << d[i] << "\n";
        }
    }
    return 0;
}
```

---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

这是一道差分板子题。

差分数组的前缀和数组就是原数组，而且连续区间加上一个数的时候只需修改两个元素即可。这一题的修改和查找是分开的，也就是说我们可以全部修改完之后再进行求前缀和操作。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=10005;
int c[N];
int main() {
	int t;
	cin>>t;
	while(t--) {
		int n,u,q;
		cin>>n>>u;
		for(int i=1; i<=n; i++)
			c[i]=0;	//差分数组初始化全为 0
		while(u--) {
			int l,r,f;
			cin>>l>>r>>f;
			s[l]+=f;	//修改操作
			s[r+1]-=f;
		}
		for(int i=1; i<=n; i++)
			s[i]+=s[i-1]; //前缀和操作，求出原数组
		cin>>q;
		while(q--) {
			int idx;
			cin>>idx;
			cout<<s[idx]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：shredded_beef_qwq (赞：0)

## 具体思路
这道题是给我们 $ u $ 个区间，让我们将这 $ u $ 个区间中的所有数都加上每次修改给定的 $ val $，但如果这题我们用暴力枚举每个区间的话会超时，那么我们第一时间就想到了用差分，所以我们这题使用差分解决。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[10010];
int main(){
	int t;
	cin>>t;
	int n,u;
	while(t--){
		memset(sum,0,sizeof(sum));
		cin>>n>>u;
		int l,r,val;
		for(int i=1;i<=u;i++){
			cin>>l>>r>>val;
			sum[l]+=val;
			sum[r+1]-=val;
		}
		for(int i=1;i<=n;i++) sum[i]+=sum[i-1];
		int q,i;
		cin>>q;
		while(q--){
			cin>>i;
			cout<<sum[i]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：xhz0311 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP16487)
### 思路分析
由于修改和查询是分开的，也即他们不会交替出现，因此想到差分。这题差分板子。

定义差分数组：   
对给定的数组 $a$，它的差分数组 $d$ 满足：$d_{0}=a_{0}$，$d_{i}=a_{i}-a_{i-1} (i>0)$。这样，$d$ 的前缀和即为 $a$。

容易发现，对 $a$ 的一个区间中每一个数加（或减）一个数仅需对差分数组的两个区间端点做修改。

初始时 $a$ 为全 $0$，因此 $d$ 也为全 $0$。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,q,d[10005],l,r,v,ask;
int main()
{
	int T;
    cin>>T;
	while(T--)
    {
		cin>>n>>q;
		memset(d,0,sizeof(d));//多测要清空
		while(q--)
        {
			cin>>l>>r>>v;
			d[l]+=v,d[r+1]-=v;//仅用修改两个端点
		}
		for(int i=1;i<=n;i++)
        {
        	d[i]+=d[i-1];//差分数组的前缀和即为原数组
        }
		cin>>q;
		while(q--)
        {
			cin>>ask;
			cout<<d[ask]<<endl;
		}
	}
	return 0;
} 
```

### 闲话
~~感谢 exlg 的随机功能帮我找能写题解的水题。~~

---

## 作者：封禁用户 (赞：0)

将一段连续的区间加上一个数，自然想到差分。

建议评级：黄

## 思路

这其实就是一道差分板子题:

在每一组数据中先把差分数组 $d$ 初始化为 $0$。

每一组相加操作中进行如下操作：

- $x_{l}=x_{l}+val$

- $x_{r+1}=x_{r+1}-val$

这样就完成了差分数组的修改。

我们可以通过前缀和让差分数组变成原数组，方式如下：

$x_{i}=x_{i}+x_{i-1}$

为了让大家更好的理解这个过程，[我](https://www.luogu.com.cn/user/1015780)就把样例的差分数组 $d$ 的模拟过程给大家表现出来：

- 最开始

| 下标 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 数值 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

- 三次修改过程

| 下标 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 数值 | 7 | 0 | -7 | 0 | 0 | 0 | 0 |

| 下标 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 数值 | 7 | 0 | -1 | 0 | 0 | -6 | 0 |

| 下标 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 数值 | 7 | 2 | -1 | 0 | -2 | -6 | 0 |

- 通过前缀和得到原数组

| 下标 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 数值 | 7 | 9 | 8 | 8 | 6 | 0 | 0 |

## $\color{#52C41A}\texttt{AC}$ $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int d[10005];
int main(){
	int t,n,u,l,r,v,q,ccf;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&u);
		memset(d,0,sizeof(d));
		while(u--){
			scanf("%d%d%d",&l,&r,&v);
			d[l]+=v,d[r+1]-=v;
		}
		for(int i=1;i<=n;++i){
			d[i]+=d[i-1];
		}scanf("%d",&q);
		while(q--){
			scanf("%d",&ccf);
			printf("%d\n",d[ccf]);
		}
	}
	return 0;
} 
```

码字不易，管理求过。

---

## 作者：guozhetao (赞：0)

## 思路
区间查询，自然就想到差分。大佬的[线段树](https://www.luogu.com.cn/blog/Setsugesuka/solution-sp16487)我看不懂，我就用差分来解决这道题。

我们用
### 首先如何修改部分数组的每个数值？
我们很容易地发现修改部分数组中，区间中每一个数字和前后数字的差只有第一个和最后一个变了。我们可以先将数组 $x$ 设为全部为 $0$（全是 $0$ 的数组相减后自然全部为 $0$），每次修改我们将数组进行如下处理：
- $x_l \gets x_l + val$
- $x_{r + 1} \gets x_{r + 1} - val$ 
这样就修改了差分数组。
### 差分数组如何变成原数组？
对于数组中的每一个数字，我们只要从 $1$ 到 $n - 1$ 把 $x_i + x_{i - 1}$，就得到了原数组（前缀和）。

## 代码

[洛谷上AC记录](https://www.luogu.com.cn/record/97790425)
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<queue>
#include<map>

using namespace std;
int x[10005];
// 快读
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while (ch < '0' or ch > '9'){if (ch == '-') f = -1;ch = getchar();}
	while (ch >= '0' and ch<='9'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}
//快写
inline void write(int x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
	return;
}
//输出char
void writec(char x) {
	putchar(x);
	return;
}
int main() {
	int t = read();
	while(t--) {
		int n = read(),u = read();
		//初始化查分数组
		for(int i = 0;i < n;i++) x[i] = 0;
		//修改 
		while(u--) {
			int l = read(),r = read(),val = read();
			x[l] += val;
			x[r + 1] -= val;
		}
		//前缀和复原数组 
		for(int i = 1;i < n;i++) x[i] += x[i - 1];
		//输出 
		int q = read();
		while(q--) {
			int i = read();
			write(x[i]),writec('\n');
		}
	}
    return 0;
}

```
[差分模板题目](https://www.luogu.com.cn/problem/U69096)
## Update
2022/12/22 完成题解

2022/12/24 修改题解（感谢[大佬](https://www.luogu.com.cn/user/28910)指导指出，将 $x1$ 改成 $x_l$）

---

## 作者：TheSky233 (赞：0)

## Desciption

给定一个序列 $a$，要求支持两种操作：

1. 把 $[l,r]$ 中的每个元素加上 $v$。

2. 查询 $a_i$。

## Solution

树状数组模板题，与[树状数组 2](https://www.luogu.com.cn/problem/P3368) 极为相似。

我们只需要维护一个 $a$ 数组的差分树状数组 $t$，使得 $t_i=a_i-a_{i-1}$，区间修改时把 $t_l$ 加上 $v$，$t_{r+1}$ 减去 $v$，查询时查询 $t_i$ 的前缀和即可。

时间复杂度：$\mathcal O(n \log n)$。

当然，由于这题是先修改后查询，也可使用静态差分数组做到 $\mathcal O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
using ll = long long;
const int N = 10000 + 5;

ll n,q,t;

struct fenwick{
	ll tree[N];
	void init(int n){memset(tree,0,(n+5)*(sizeof(tree[0])));}
	void update(int x,ll v){while(x<=n) tree[x]+=v,x+=lowbit(x);}
	ll query(ll x){ll sum=0; while(x) sum+=tree[x],x-=lowbit(x); return sum;}
	ll range(int l,int r){return query(r)-query(l-1);}
}tr;

void so1ve();

int main(){
	scanf("%lld",&t);
	while(t--) so1ve();
}

void so1ve(){
	scanf("%lld%lld",&n,&q);
	tr.init(n);
	while(q--){
		int l,r; ll v;
		scanf("%d%d%lld",&l,&r,&v);
		++l; ++r;
		tr.update(l,v);
		tr.update(r+1,-v);
	}
	scanf("%lld",&q);
	while(q--){
		int x;
		scanf("%d",&x);
		++x;
		printf("%lld\n",tr.query(x));
	}
}
```

---

## 作者：Setsugesuka (赞：0)

因为区间修改和单点查询是分开的，我们很容易想到用差分数组去解决这个问题，于是我写了一棵线段树。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e4+10;

int t;
int ans[MAXN<<2],lazy[MAXN<<2];
int n,q;

inline void pushup(int rt)
{
    ans[rt]=ans[rt<<1]+ans[rt<<1|1];
}

inline void pushdown(int rt,int ln,int rn)
{
    if(lazy[rt])
    {
        ans[rt<<1]+=lazy[rt]*ln;
        ans[rt<<1|1]+=lazy[rt]*rn;
        lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        lazy[rt]=0;
    }
}

void change(int L,int R,int C,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        ans[rt]+=(r-l+1)*C;
        lazy[rt]+=C;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(rt,mid-l+1,r-mid);
    if(L<=mid)
        change(L,R,C,l,mid,rt<<1);
    if(R>mid)
        change(L,R,C,mid+1,r,rt<<1|1);
    pushup(rt);
}

int query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
        return ans[rt];
    int mid=(l+r)>>1,ret=0;
    pushdown(rt,mid-l+1,r-mid);
    if(L<=mid)
        ret+=query(L,R,l,mid,rt<<1);
    if(R>mid)
        ret+=query(L,R,mid+1,r,rt<<1|1);
    return ret;
}

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&q);
        memset(ans,0,sizeof(ans));
        memset(lazy,0,sizeof(lazy));
        while(q--)
        {
            int l,r,val;
            scanf("%d %d %d",&l,&r,&val);
            l++,r++;
            change(l,r,val,1,n,1);
        }
        scanf("%d",&q);
        while(q--)
        {
            int l;
            scanf("%d",&l);
            l++;
            cout<<query(l,l,1,n,1)<<endl;
        }
    }
    return 0;
}
```


---

