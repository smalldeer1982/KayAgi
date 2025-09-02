# Magical Permutation

## 题目描述

Kuro 刚刚学习了排列，他非常兴奋地想要创造一种新的排列类型。他选择了 $n$ 个互不相同的正整数，并将它们全部放入集合 $S$ 中。现在他定义了一种“魔法排列”，其定义如下：

- 是 $0$ 到 $2^x - 1$ 的一个排列，其中 $x$ 是一个非负整数。
- 排列中任意两个相邻元素的按位异或结果属于集合 $S$。

由于 Kuro 对魔法排列非常感兴趣，他想要构造最长的魔法排列。换句话说，他想要找到最大的非负整数 $x$，使得存在一个 $0$ 到 $2^x - 1$ 的魔法排列。由于他在这个领域还是新手，他希望你帮他找到这个 $x$ 的值，并给出对应的魔法排列。

## 说明/提示

在第一个样例中，$0, 1, 3, 2$ 是一个魔法排列，因为：

- $0 \oplus 1 = 1 \in S$
- $1 \oplus 3 = 2 \in S$
- $3 \oplus 2 = 1 \in S$

其中 $\oplus$ 表示按位异或运算。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
2
0 1 3 2 ```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
2
0 2 1 3 ```

## 样例 #3

### 输入

```
4
1 2 3 4
```

### 输出

```
3
0 1 3 2 6 7 5 4 ```

## 样例 #4

### 输入

```
2
2 4
```

### 输出

```
0
0 ```

## 样例 #5

### 输入

```
1
20
```

### 输出

```
0
0 ```

## 样例 #6

### 输入

```
1
1
```

### 输出

```
1
0 1 ```

# 题解

## 作者：duyi (赞：12)

[欢迎来我的博客，获得更好的阅读体验！](https://www.cnblogs.com/dysyn1314/p/13640005.html)

## CF1163E Magical Permutation

## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1163/E)

给定一个，含有$n$个互不相同正整数的集合$S$。

我们称一个排列是合法的，当且仅当同时满足如下两个条件：

1. 这是一个$0,1,\dots ,2^x-1$的排列，其中$x$是一个非负整数。
2. 排列里，任意相邻两数的异或值，都出现在$S$中。

请求出，最长的合法排列。换句话说，请你找到一个最大的$x$，并构造出一个长度为$2^x$的合法排列。

数据范围：$1\leq n\leq 2\times 10^5$，$S$集合里的数$\leq2\times 10^5$。

## 本题题解

设$S$里最大的数为$M$。

如果排列的二进制下最高位，超过了$S$里最大的数（即$2^{x-1}>M$），那么这样的排列一定是不合法的。因为最高位一定会出现在异或值中，但它无法被$S$里的数表示出来。因此，满足条件的$x$不超过$\log_2M+1$。于是我们考虑枚举所有$x$，判断它是否可行。

**引理**：一个$x$可行当且仅当，$0,1,\dots,2^x-1$都能被表示为$S$的一个子集的异或和。

> **证明-必要性**：
>
> 考虑一个合法的排列，$p_0,p_1,\dots ,p_{2^x-1}$，设$p_t=0$。
>
> 首先，$p_t$就是一个空集的异或和，所以对$p_t$显然满足条件。
>
> 因为排列合法，所以在$p_{t+1},p_{t+2},\dots ,p_{2^x-1}$中，每个数和它前面一个数的异或值，都属于$S$。具体来说，设$c_i=p_{i-1}\operatorname{xor}p_{i}$，则$\forall i>t:c_i\in S$，因此$p_{t+1},p_{t+2},\dots ,p_{2^x-1}$都能被表示为一段连续的$c_i$的异或和，也就是$S$里若干个数的异或和。
>
> 类似地，在$p_{t-1},p_{t-2},\dots,p_0$中，每个数和它后面一个数的异或值，都属于$S$。设$d_i=p_{i}\operatorname{xor}p_{i+1}$，则$\forall i<t:d_i\in S$，因此$p_{t-1},p_{t-2},\dots,p_0$都能被表示为一段连续的$d_i$的异或和，也就是$S$里若干个数的异或和。

由此就证明了：【$0,1,\dots,2^x-1$都能被表示为$S$的一个子集的异或和】是一个长度为$2^x$的排列合法的必要条件。枚举$x$后，我们可以通过对$S$建线性基，看线性基前$x$位是否填满，来检查$x$是否满足这个必要条件。

接下来要证明充分性，相当于把这个排列构造出来。也正是题目要我们做的事情。

现在我们知道，$0,1,\dots,2^x-1$都能被表示为$S$的一个子集的异或和。根据线性基的理论，对$S$建线性基后，$S$的每个子集，都对应线性基的一个子集，它们异或和相等。所以$0,1,\dots,2^x-1$每个数，都能被表示为：【$S$里，用来建线性基的，这$x$个数】的一个子集。并且每个数对应的子集互不相同：用来建线性基的有$x$个数，正好形成$2^x$个子集，和每个值一一对应。

通过线性基，我们能求出，每个值对应了哪个子集。前面说了，这些子集互不相同。于是把它们用二进制表示为$0,1,\dots,2^x-1$。

那么问题转化为，把$0,1,\dots,2^x-1$（所有子集）重新排列，使得任意相邻两个数，只有一位二进制为不同。这就是格雷码的定义，可以采用[「CSP-S 2019」格雷码](https://loj.ac/problem/3208)这题题面里介绍的构造方法。

时间复杂度$O(n\log n+n\log M+M)$。

参考代码：

```cpp
//problem:
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN=2e5,LOG=18;
int n;
uint s[MAXN+5];
uint mask_to_val[MAXN+5];
struct LinerBase{
	int size;
	uint base[MAXN+5],mask[MAXN+5],val[MAXN+5];
	void insert(const uint& v){
		uint t=v;
		uint ma=0;
		for(int i=LOG;i>=0;--i) if((t>>i)&1) {
			if(!base[i]){
				base[i]=t;
				++size;
				ma|=(1<<(size-1));
				mask[i]=ma;
				val[size]=v;
				return;
			}
			else{
				t^=base[i];
				ma^=mask[i];
			}
		}
	}
	uint query_mask(const uint& v){
		uint t=v;
		uint ma=0;
		for(int i=LOG;i>=0;--i) if((t>>i)&1) {
			assert(base[i]);
			t^=base[i];
			ma^=mask[i];
		}
		return ma;
	}
}B;
vector<uint> get_gray(uint x){
	if(x==0){
		vector<uint> res(1,0);
		return res;
	}
	vector<uint> res=get_gray(x-1);
	uint len=(1u<<(x-1));
	for(uint i=0;i<len;++i){
		res.push_back(res[len-1-i] | (1u<<(x-1)));
	}
	return res;
}
int main() {
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s[i];
	}
	sort(s+1,s+n+1);
	int j=0;
	int x=-1;
	for(int i=0;i<=LOG;++i){
		while(j+1<=n && s[j+1]<(1u << i)){
			++j;
			B.insert(s[j]);
		}
		if(B.size==i) x=i;
	}
	assert(x!=-1);
	for(uint i=0;i<(1u<<x);++i){
		mask_to_val[B.query_mask(i)]=i;
	}
//	cerr<<x<<endl;
//	for(uint i=0;i<(1u<<x);++i)
//		cerr<<mask_to_val[i]<<" ";
//	cerr<<endl;
	vector<uint> v=get_gray(x);
	cout<<x<<endl;
	for(uint i=0;i<(1u<<x);++i){
		cout<<mask_to_val[v[i]]<<" ";
	}
	cout<<endl;
	return 0;
}
```



---

## 作者：Islauso (赞：7)

## 题目大意

给出一个集合 $S$，构造一个排列 $a$，其长度为 $2^x$，要求 $\forall i,a_i\in [0,2^x-1]$ 且 $a_i\oplus a_{i+1}\in S$，在满足这个条件的情况下要求 $x$ 尽量大。

## 思路

这个题我们分成两部分来做，即如何求出 $x$ 和如何构造这个序列。

### Part 1

首先根据题目可以看出，任意一个合法的 $x$，它应该满足对于所有 $a_i\in [0,2^x-1]$，我们可以用 $S$ 中的任意多个数异或起来得到 $a_x$。

为什么呢，这样想，对于长度为 $2^x$ 的排列 $a$，里面总有一个数为 $0$，由于相邻两个数的异或值是 $S$ 中的一个数，所以与这个 $0$ 相邻的两个数都是 $S$ 中的数，而与这两个数相邻的两个数都能被表示为 $S$ 中的两个数异或起来，以此类推，最终可以得知所有的数都可以被表示为 $S$ 中任意多个数异或起来。

我们知道，$S$ 中任意多个数相互异或所得到的数一定也能被表示为 $S$ 的线性基中任意多个数相互异或所得到的数，所以这个排列中的所有数一定也能被表示为 $S$ 的线性基中任意多个数异或起来，由于线性基的性质，线性基中不同的异或组合异或出的数都是不一样的，所以这个线性基一定能异或出正好 $2^x$ 个数，也就是 $0$ 到 $2^x-1$ 这些数。

说了这么多，我们如何确定最大的 $x$ 使得排列 $a$ 一定存在呢？很简单，我们直接求出 $S$ 的线性基，然后看第一个为 $0$ 的 $base_i$ 是第几个就行了，由于存在这样一个为 $0$ 的 $base_i$，就会导致某些最高位为 $i$ 的数没法异或出来，所以这个 $i$ 一定就是最大的 $x$。

但有一个问题，我们看这样一组数据：

```
2
4 5
```

不难求出，这个 $S$ 的线性基为$\{1,4\}$，这样的话第一个为 $0$ 的 $base_i$ 就是 $base_1$ 了，所以我们的程序就会误认为 $x$ 应该取 $1$，但显然这样是不合法的。

这个 bug 出现的主要原因在于我们可以通过把较高位异或掉来异或出一个最高位较低的数，但显然我们想要的并不是这样的，因为我们并不能通过异或把两个数的最高位变高，那么怎么解决呢。

很简单，我们在插入时枚举一下 $x$，只插入那些小于 $2^x$ 的数就行了，代码如下。

```cpp
void insert(int x)
{
	int t = x;
	for(int i = 20; i >= 0; i--)
		if((x>>i)&1)
			if(!bas[i])
			{
				bas[i] = x;
				a[++k] = t;//这里的 a 数组在 part 2 里面会有用，k 可以理解为是统计有多少个 base 不为 0
				break;
			}
			else
				x ^= bas[i];
}
```

```cpp
sort(s+1, s+1+n);
for(int i = 0, j = 1; i <= 20 && j <= n; i++)
{
    while(s[j] < (1<<i) && j <= n)
        insert(s[j++]);
    if(k == i)
        m = i;
}
```

### Part 2

很多大佬都说这一部分很简单，所以讲得不太详细，但由于我比较菜，所以我觉得这里才是最难的部分。

构造 $a$ 的方法很多，一种方法是用格雷码来构造，然而采用这类方法的大佬大多没有给出这样做的原因，还有一种是用遍历一棵二叉树的方法，我这里采用较为暴力的办法，即直接 DFS。

在 Part 1 的代码里面，我们用一个 a 数组存了插入线性基的数，而这些数正是我们相邻两个数异或起来所得到的值的集合（也就是说我们把构造出来的排列中相邻两个数异或一下，只能得到这些数），当然不这样构造应该也是可以的，这只是我们构造出来的排列的一个性质罢了，因为如果一个数没有被插入到线性基中，那只有可能是它能被其他的数异或出来，所以我们只需要这些数就能异或出 $2^x$ 个数了。

参考代码

```cpp
void dfs(int x, int num)
{
	printf("%d ", num);
	if(x == (1<<m))
		exit(0);
	vis[num] = 1;
	for(int i = 1; i <= k; i++)
		if(!vis[num^a[i]])
			dfs(x+1, num^a[i]);
}
```

这样看起来很不靠谱，理论上来说应该是 $O(n^{\log M})$ 的，但实际上，由于这 $x$ 个数可以肯定能正好异或出这 $2^x$ 个数，所以应该不存在回溯的情况，也就是说，这个算法的时间复杂度实际上是 $O(n\log M)$ 的，并且经过 CF 的实际验证，这样确实不会回溯。

因此，这个算法的总时间复杂度为 $O(n\log n+n\log M+n\log M)$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
	char buf[1<<23],*p1=buf,*p2=buf;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
	#define isdigit(c) (c>=48&&c<=57)
	#define isalpha(c) ((c>=65&&c<=90)||(c>=97&&c<=122))
	template<typename T> inline void read(T &x)
	{
		x=0;
		register int f=1;
		register char ch=getchar();
		while(!isdigit(ch))
			ch=getchar();
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^48);
			ch=getchar();
		}
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args)
	{
		read(t);read(args...);
	}
}
using namespace IO;
const int N = 2e5+10, inf = 0x3f3f3f3f;
int n, m, k, s[N], vis[N*10], bas[20], a[20];
void insert(int x)
{
	int t = x;
	for(int i = 20; i >= 0; i--)
		if((x>>i)&1)
			if(!bas[i])
			{
				bas[i] = x;
				a[++k] = t;
				break;
			}
			else
				x ^= bas[i];
}
void dfs(int x, int num)
{
	printf("%d ", num);
	if(x == (1<<m))
		exit(0);
	vis[num] = 1;
	for(int i = 1; i <= k; i++)
		if(!vis[num^a[i]])
			dfs(x+1, num^a[i]);
}
int main()
{
	read(n);
	for(int i = 1; i <= n; i++)
		read(s[i]);
	sort(s+1, s+1+n);
	for(int i = 0, j = 1; i <= 20 && j <= n; i++)
	{
		while(s[j] < (1<<i) && j <= n)
			insert(s[j++]);
		if(k == i)
			m = i;
	}
	printf("%d\n", m);
	k = 0;
	memset(bas, 0, sizeof(bas));
	for(int i = 1; i <= n; i++)
		if(s[i] < (1<<m))
			insert(s[i]);
	dfs(1, 0);
	return 0;
}
```

格雷码的那种思路是真心看不懂，也没有一个大佬做出详细的解释，遍历二叉树的思路还比较好懂，并且常数也比我这个小，但个人觉得我这个方法还要好懂一点（（（

---

## 作者：jun头吉吉 (赞：6)

# 题目大意
给出数组$S$,请你构造一组长为$2^x$数$d$,使得：
$$∀i\in[0,2^x-2],d_i\oplus d_{i+1}\in S$$
式中的$x$要求最大,$d_i\in [0,2^x-1]$且无重复
# 题解
一道线性基的神仙构造题

首先我们知道，若x可行，则$S_i\in[0,2^x-1]$所构造出的线性基的$0\to x-1$位必须排满，这是为什么呢

经过~~仔细严谨细致的推理~~对样例的观察，我们发现，第一位肯定是0

我们假设已经构造出了$d$数组,和两两的$\oplus$值$a$
```
0      d[1]    d[2]...   d[(1<<x)-1]
   a[1]    a[2] ... a[(1<<x)-1]
```
（$a_i\in S$）

辣么$d_i=a_1\oplus a_2\oplus...\oplus a_i$

如果线性基中$1\to x-1$位未填满，则说明当前已选的$S$无法构造出最高位为某一些值的数，一共有$0\to 2^x-1$共$2^x$个数，$2^x$个位置，有些数构造不出来，又不允许重复，很显然此时的$d$是不可能存在的

#### 那如何证明当$1\to x-1$位填满时，$d$就一定存在呢？

我们假设已经把$S_{k_0},S_{k_1},...,S_{k_{x-1}}$放进线性基中，根据线性基的性质，这些数无法$\oplus$出0，也无法异或出相同的数，并且一共有$2^x$种异或方法（每个数异或或不异或），$2^x$个不同的值，值的范围为$[0,2^x-1]$，因此我们可以把$S_{k_0},S_{k_1},...,S_{k_{x-1}}$按一定顺序排列，使得异或出$d$

很显然，对于$S_{k_i}$是否异或，会生成两组截然不同的答案，因此我们可以像下图一样插入值

![](https://cdn.luogu.com.cn/upload/image_hosting/1sggn7mv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样前面的值不异或$x$,后面的值异或$x$,就成功的构造出了$a$,插入的过程可以写$dfs$,像下面这样：
```cpp
inline void dfs(int dep){
	if(dep==-1)return;
	dfs(dep-1);
	ans[++m]=w[dep];
	dfs(dep-1);
}
```
于是我们就可以愉快地用$a$数组构造出$ans$了

~~是不是很简单啊~~
```cpp
#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
const int maxn_wei=30;
vector<int> w;
struct node{
	//线性基板子
	int b[maxn_wei];
	void insert(int x){
		int tmp=x;
		for(int i=maxn_wei-1;i>=0;i--){
			if(!(x&(1<<i)))continue;
			if(!b[i]){
				b[i]=x;
				w.push_back(tmp);
				return ;
			}
			x^=b[i];
		}
	}
}Base;
const int maxn=2e7+100;
int n,s[maxn];
int ans[maxn],m;
inline void dfs(int dep){
	if(dep==-1)return;
	dfs(dep-1);
	ans[++m]=w[dep];
	dfs(dep-1);
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++)
		read(s[i]);
	sort(s+1,s+1+n);
	int k=0;
	for(int j=1,i=1;i<maxn_wei;i++){
		for(;j<=n&&s[j]<(1<<i);j++)Base.insert(s[j]);
		if(w.size()==i)k=i;
	}
	printf("%d\n",k);
	dfs(k);ans[0]=0;
	for(int i=0;i<(1<<k);i++){
		ans[i]^=ans[i-1];
		printf("%d ",ans[i]);
	}
}
```

---

## 作者：CYJian (赞：4)

一道魔改线性基好题啊=-=

细节挺多的...

---

我们看到这道题要搞出一个最长的序列, 使得 $[0, 2^x-1]$ 内的数都出现了, 并且相邻的数的异或要出现在给出的 $S$ 集合中.

那么相当于是要找出一个 $S$ 的一个大小为 $x$ 的子集, 满足将这 $x$ 个数的二进制位拆开看做一个 $x$ 维向量, 这 $x$ 个向量线性无关. 因为保证了这一点之后我们一定能构造出一种遍历 $[0, 2^x-1]$ 的方案.

先讲讲构造的方法. 我们可以把 $[0, 2^x-1]$ 这些数做二进制拆分, 如果第 $i$ 位上有 $1$ , 那么我们就将这个位置上的数异或上一个 $v_i$ (设 $v_i$ 表示线性基中第 $i$ 位的数的原数值, 且每个位置上一开始都为 $0$), 这样的话, 我们得到的数列就一定是满足要求的数列了.

然后就是怎么搞出想要的线性基了...

首先如果我们按照最原始的方法搞线性基:

```cpp
inline void insert(int x) {
	int tmp = x;
    for(int i = 30; i >= 0; i--) {
    	if((x >> i) & 1) {
        	if(a[i]) {
            	x ^= a[i];
            } else {
            	a[i] = x;
                v[i] = tmp;
                break;
            }
        }
    }
}
```

那么就会原地起爆...下面给一个栗子:

```plain
3
100000 100001 1
```

如果这样搞, 那么我们得到的 $v_0 = 100001$ , 然后就会得到 $x=0$...

但是我们有一个 $1$ 的话, 我们就可以构造出一组 $x=1$ 的解...

所以需要改造一下: 如果当前第 $i$ 个位置上有值了, 那么就比较一下 $v_i$ 的大小关系, 选择 $v_i$ 小的放在线性基里, 大的拿出来往下扔.

```cpp
inline void insert(int x) {
	int tmp = x;
    for(int i = 30; i >= 0; i--) {
    	if((x >> i) & 1) {
        	if(a[i]) {
            	if(tmp < v[i]) swap(x, a[i]), swap(tmp, v[i]);
            	x ^= a[i];
            } else {
            	a[i] = x;
                v[i] = tmp;
                break;
            }
        }
    }
}
```

然后, 有一些小坑点需要注意一下:

1. 如果你觉得找到第一个 $a_i=0$ 的 $i$ 去作为答案的话, 那就错了...需要考虑小于 $i$ 的位置上的 $v_j$ 是否小于 $2^i$
2. 如果你的写法中把构造答案的数列用数组存下来的话, 请开大到 $>2^{18}$, 否则会 `RE`

然后就可以通过此题了...

下面是代码的主体部分: 

```cpp

const int MAXN = 200100;

int a[33];
int v[33];

inline void insert(int x) {
	int t = x;
	for(int i = 30; i >= 0; i--) {
		if((x >> i) & 1) {
			if(a[i]) {
				if(t < v[i])
					swap(a[i], x),
					swap(t, v[i]);
				x ^= a[i];
			}
			else {
				a[i] = x;
				v[i] = t;
				break;
			}
		}
	}
}

int cnt;
int Xor[MAXN << 1];

inline void dfs(int x) {
	if(x < 0) return ;
	dfs(x - 1);
	Xor[++cnt] = v[x];
	dfs(x - 1);
}

int main() {
#ifndef ONLINE_JUDGE
	FILE("");
#endif
	int n; gi(n);
	for(int i = 1; i <= n; i++) {
		int v; gi(v); insert(v);
	}
	if(!a[0]) {
		print(0), pc('\n');
		print(0), pc('\n');
		return 0;
	}
	for(int i = 0; i <= 30; i++) {
		if(!a[i]) {
			int unable = 1;
			while(unable) {
				--i; int mx = 1 << (i + 1); unable = 0;
				for(int j = 0; j <= i; j++)
					if(v[j] >= mx) unable = 1;
			}
			print(i + 1), pc('\n');
			dfs(i);
			int val = 0; print(0);
			for(int j = 1; j <= cnt; j++)
				pc(' '), print(val ^= Xor[j]);
			pc('\n'); return 0;
		}
	}
	return 0;
}
```

---

## 作者：SFlyer (赞：2)

很少在 duel 的时候遇到惊艳我的 2400 了。正好把我不熟的整合了一下。

- 首先假设我们 $S$ 可以自己定，如果要满足 $0\sim 2^x-1$ 的，$|S|$ 最小是多少？

|S| 最小是 $x$。考虑 $S=\{0,1,2,\cdots ,2^{x-1}\}$。然后我们 $0,1,3,2,\cdots$ 构造序列。容易证明 $|S|$ 不可能更小。

一点要注意的是，$0,1,3,2,\cdots$ 是格雷码。

- 给定 $S$，怎么判断一个 $x$ 合不合法？

其实也就是 $S$ 中的集合能不能表示所有 $0\sim 2^x-1$，并且不重不漏。

一个显然的条件是 $S$ 中有用的数插入线性基中，线性基大小 $=x$。

然后发现这个是冲要条件：

- 首先，所有 $0\sim 2^x-1$ 可以用线性基中若干个数 $\oplus$ 得到。

- 其次，根据线性基的定义：没有两个子集异或相等，所以 $0\sim 2^x-1$ 的数都可以以唯一方式表示出来。定义这个数的编号为：一个二进制串，每一位表示选不选这个线性基中的数。

- 因为有 $2^x$ 个数，而线性基最多能表示 $2^x$ 个数，所以数和编号是双射关系。

- 因为是不重不漏的 $000,001,010,011,\cdots$，所以可以构成一个格雷码。

那么构造也简单了：可以直接暴力搜索，一定有答案。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 4e5+5;

int n,a[N],b[20],c[20],cnt,mx;

void ins(ll x){
	ll y=x;
	for (int i=19; i>=0; i--){
		if (x>>i&1){
			if (!b[i]){
				b[i]=x;
				c[i]=y;
				cnt++;
				return;
			}
			else{
				x^=b[i];
			}
		} 
	} 
}

int vis[N];

void dfs(int u){
	cout<<u<<" ";
	vis[u]=1;
	for (int i=0; i<mx; i++){
		if (!vis[c[i]^u]){
			dfs(c[i]^u);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<=n; i++){
		cin>>a[i];
	}
	for (int i=19; i>=0; i--){
		cnt=0;
		for (int j=0; j<20; j++) b[j]=c[j]=0;
		for (int j=1; j<=n; j++){
			if (a[j]<=(1<<i)-1){
				ins(a[j]);
			}
		}
		if (cnt==i){
			mx=i;
			cout<<i<<"\n";
			dfs(0);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：233L (赞：1)

前情提要：有注释代码。

## Part1 找到  $x$

对于一个 $0$ 到 $2^x-1$ 的排列，相邻两数的异或和一定会出现二进制下的最高位，即  $2^{x-1}$。为什么？只考虑这一位，一定有相邻的两个数，一个是 $0$，另一个是 $1$，异或起来就是 $1$ 了。（一定有 $0$ 和 $1$ 的交界）

由此得到如果一个 $x$ 是可行的，那么 $S$ 中最大的数一定不小于 $2^{x-1}$。又因为 $S_i \in [1,2 \times 10^5]$，所以 $2^{x-1} \le 2 \times 10^5$，$x \le 13$。

引理：如果一个 $x$ 是可行的，那么 $[0,2^x)$ 中每个数一定都能被 $S$ 中若干个数异或表示。（必要条件）~~第一篇题解写的很详细，这里就不证了。~~由此联想到线性基，求出 $S$ 的线性基，如果 $\forall i \in [0,x),p_i$ 都有值，就说明这个 $x$ 是可行的……吗？（是否充分？）

看一组例子：$S=\{4,5\}$，其线性基可以是：$p_0=1,p_2=4$，但显然 $x=1$ 并不可行。为什么？一个 $0$ 到 $2^x-1$ 的排列，异或值最大也就是 $2^x-1$，所以 $S$ 里大于等于 $2^x$ 的元素是不作数的。为此，我们可以对 $S$ 进行升序排序，枚举可能的 $x$。

### 代码实现

``` cpp
sort(a+1,a+n+1);
for(int i=0,j=1;j<=n;i++){//i用来枚举x，j是枚举下标
	while(a[j]<(1<<i)&&j<=n)
		lb.insert(a[j]),j++;//插入[0,2^i)内的数 
	if(lb.siz==i)x=i;//1~i的基都有了，更新x（siz是线性基中基的个数，详见完整代码）
}
```

## Part2 构造排列

我们已经知道，$[0,2^x)$ 中每个数都能被 $S$ 中若干个数异或表示，记 $A_i$ 为 $S$ 的一个子集，且 $A_i$ 中的元素的异或和为 $i$。如果 $i$ 和 $j$ 在排列中相邻，因为 $(i \oplus j) \in S$，那么 $A_i$ 和 $A_j$ 就只有一个元素的区别（一个集合比另一个集合多一个元素，其他部分都一样，这样异或起来就是多出来的那个元素）。把 $A$ 都用二进制状压表示，那么 $A_i$ 和 $A_j$ 就只有 1 位不同，而[格雷码](https://oi-wiki.org/misc/gray-code/)就是这样一个排列。([P5657 \[CSP-S2019\] 格雷码](https://www.luogu.com.cn/problem/P5657)给出了一种构造方式）

为了求出 $A$，我们在构造线性基时增设一个数组 ```md```，```md[i]``` 用二进制状压表示 ```p[i]``` 这个基由哪几个插入线性基的数异或得到，每个数都可以拆成若干个基的异或和，再拆成若干个插入到线性基的数，就得到 $A$。构造好格雷码后，每一位输出与这个格雷码相等的 $A_i$ 对应的 $i$ 即可。

## 上代码

```cpp
#include<bits/stdc++.h>
#define N 200004
#define L 20
using namespace std;
int n;
int a[N],b[N];
struct Lb{
	int siz;
	int p[L],md[L];
	//md[i] p[i]这个基是异或上哪些数（插入到线性基的原数）得到的 
	//第i（从0开始）个插入到线性基的数在状压时表示为(1<<i) 
	inline void insert(int x){
		int m=0;
		for(int i=L-1;~i;i--)
			if(x&(1<<i)){
				if(!p[i]){
					p[i]=x;
					md[i]=m|(1<<siz);
					siz++;
					break;
				}
				x^=p[i];
				m^=md[i];
			}
	}
	inline int query(int x){//查询x是怎么被异或表示的 
		int res=0;
		for(int i=L-1;~i;i--)
			if(x&(1<<i))x^=p[i],res^=md[i];
		return res;
	}
}lb;

inline int read(){
	int x=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
	return x;
}
vector<int> getGrey(int x){//表示要构造长度为2^x的格雷码 
	if(!x){
		vector<int>res(1,0);
		return res;
	}
	vector<int>res=getGrey(x-1);
	//递归，先构造出左半边
	for(int i=1,bound=(1<<(x-1));i<=bound;i++)
		res.push_back(res[bound-i]|bound);
	return res;
}//构造格雷码的实现借鉴了duyi大佬的方法 
int main(){
	int x; 
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=0,j=1;j<=n;i++){//i用来枚举x，j是枚举下标
		while(a[j]<(1<<i)&&j<=n)
			lb.insert(a[j]),j++;//插入[0,2^i)内的数 
		if(lb.siz==i)x=i;//1~i的基都有了，更新x 
	}
	
	//现在要求[0,2^x)中的每个数是怎么被线性基异或表示的 
	for(int i=0;i<(1<<x);i++)
		b[lb.query(i)]=i;//以A_i为下标，存储i，求出格雷码后能方便地找到对应的i
	
	vector<int>arr=getGrey(x);//构造格雷码 
	printf("%d\n",x);
	for(int i:arr)printf("%d ",b[i]); 
}
```

如果觉得我哪里没讲清楚请在讨论区提出，我会尽量改善。谢谢收看sto

---

## 作者：__ycx2010__ (赞：0)

### 思路

枚举 $x$，由于 $S_i \leq 2\times 10^5$，所以 $x$ 为 $O(\log V)$ 级别。

将所有 $S_i < 2^x$ 的数加入线性基中，我们有结论，$x$ 成立当且仅当，所有 $i\in[0,2^x)$ 都可以被线性基表示出。

先证必要性，发现如果有一个合法排列，那么我们一定可以使它的第一项变为 $0$，于是显而易见整个排列都可以被线性基表示。

再证明充分性，如果线性基满足了条件，那么线性基里肯定恰有 $x$ 个数，且刚好组成了 $[0,2^x)$，将每个数都用一个 $x$ 位二进制表示，意为它等于线性基中这些数的异或和，于是使用格雷码即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

struct base_line {
	int a[30] = {0}, b[30] = {0};
	void add(int x, int id) {
		for (int i = 20; i >= 0; i -- ) {
			if (x >> i & 1) {
				if (!a[i]) {
					a[i] = x, b[i] = id;
					break;
				} else {
					x ^= a[i];
					id ^= b[i];
				}
			}
		}
	} int ask(int x) {
		int res = 0;
		int p = 0;
		if (x == 993) p = 1;		
		for (int i = 20; i >= 0; i -- )
			if (x >> i & 1) {
				if (!a[i]) return 0;
				else {
					x ^= a[i];
					res ^= b[i];
				}
			}
		return res;
	}
}a, nw;

int main() {
	int n, tot = 0;
	scanf("%d", &n);
	vector<int> num;
	for (int i = 1; i <= n; i ++ ) {
		int x; scanf("%d", &x);
		num.pb(x);
	}
	sort(num.begin(), num.end());
	int j = 0, x = 0;
	for (int i = 1; i <= 20; i ++ ) {
		while (j < n && num[j] < (1 << i)) {
			if (!nw.ask(num[j])) {
				tot ++ ;
				nw.add(num[j], 1 << tot - 1);
			}
			j ++ ;
		}
		if (tot == i) {
			x = i;
		}
	}
	tot = 0;
	int jj = 0;
	while (jj < num.size() && num[jj] <= (1 << x) - 1) {
		if (!a.ask(num[jj])) {
			tot ++ ;
			a.add(num[jj], 1 << tot - 1);
		}
		jj ++ ;
	}
	vector<int> mark((1 << x) + 5);
	for (int i = 0; i < (1 << x); i ++ ) {
		mark[a.ask(i)] = i;
	}
	printf("%d\n", x);
	vector<int> gcode;
	gcode.pb(0);
	for (int i = 1; i <= x; i ++ ) {
		int len = (int)gcode.size();
		for (int j = len - 1; j >= 0; j -- ) gcode.pb(gcode[j] ^ (1 << i - 1));
	}
	for (int i = 0; i < (1 << x); i ++ ) printf("%d ", mark[gcode[i]]);
	return 0;
}
```

---

## 作者：raincity (赞：0)

## 题目描述

给定 $n$ 元集合 $S$，求最大的 $x$ 和一个 $0\sim2^x-1$ 的排列，满足排列中相邻两项的异或和属于 $S$。

## 分析

结论：一个 $x$ 可行，当且仅当 $0\sim2^x-1$ 均可以表示为 $S$ 的一个子集中元素的异或和。

必要性：设第 $i$ 个数是 $S$ 的子集 $s_i$ 中元素的异或和，下证 $s_i$ 一定存在。因为 $p$ 是一个排列，所以只要 $s_i$ 均存在，$0\sim2^x-1$ 就都可以表示为 $S$ 的一个子集中元素的异或和。

设 $v_i=p_i\operatorname{xor}p_{i+1}$，$p_k=0$，则 $s_k=\varnothing$。因为 $v_k\in S$，所以

$
s_{k+1}=\left\{
\begin{array}{l}
s_k-\{v_k\},v_k\in s_k \\
s_k\cup\{v_k\},v_k\not\in s_k \\
\end{array}
\right.
$

故 $s_{k},s_{k+1},\ldots s_n$ 都存在，同理 $s_{k},s_{k-1},\ldots s_1$ 也存在，即 $s_i$ 均存在。

充分性：设 $i$ 为 $S$ 的子集 $t_i$ 中元素的异或和，则 $t_{p_i}$ 和 $t_{p_{i+1}}$ 之间恰好差了一个数，也就是说，它们的二进制表示刚好有一位分别为 $0$ 和 $1$，其他位都相等，（不）容易发现格雷码就符合要求。

所以，判断的时候，只需要把 $S$ 中 $<2^x$ 的数插入线性基，并记录线性基中表示每一位的数在 $S$ 中是第几个，如果线性基是满的那就有解，按照格雷码构造（如果这一位为 $1$ 那么把 $S$ 中对应的数异或上）即可。

## 实现

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 2e5 + 5, B = 19;
int n, s[N], p[B], id[B], c[1 << B];

template <class T>
void read(T &ret) {
  ret = 0;
  char ch = getchar();
  bool vis = false;
  while (!isdigit(ch) && ch != '-') ch = getchar();
  if (ch == '-') vis = true, ch = getchar();
  while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
  if (vis) ret = -ret;
}

template <class T, class... Args>
void read(T &ret, Args &...rest) {
  read(ret), read(rest...);
}

int main() {
  read(n);
  for (int i = 1; i <= n; i++) read(s[i]);
  for (int x = B; x >= 0; x--) {
    memset(p, 0, sizeof(p));
    for (int i = 1; i <= n; i++) {
      if (s[i] >= 1 << x) continue;
      int cur = s[i];
      for (int j = x - 1; j >= 0; j--)
        if (cur >> j & 1) {
          if (!p[j]) {
            p[j] = cur, id[j] = i;
            break;
          }
          cur ^= p[j];
        }
    }
    bool ok = true;
    for (int i = 0; i < x && ok; i++) ok &= p[i] != 0;
    if (ok) {
      printf("%d\n", x);
      for (int i = 0; i < x; i++)
        for (int j = 0; j < 1 << i; j++)
          c[j + (1 << i)] = c[(1 << i) - j - 1] | (1 << i);
      for (int i = 0; i < 1 << x; i++) {
        int cur = 0;
        for (int j = 0; j < x; j++)
          if (c[i] >> j & 1) cur ^= s[id[j]];
        printf("%d ", cur);
      }
      break;
    }
  }
  return puts(""), 0;
}

```

---

