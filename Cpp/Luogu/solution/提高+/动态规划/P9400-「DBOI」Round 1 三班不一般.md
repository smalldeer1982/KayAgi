# 「DBOI」Round 1 三班不一般

## 题目背景

HQ 是传奇颜值中学的一位尽职尽责的后勤部教师，同时也是宿舍的管理成员，负责管理开关灯。

对于他来说，最令人厌烦的的就是极不一般的三班的一群猴子乱玩自己宿舍和别人宿舍的灯，但是却没法当场发现并抓捕始作俑者。

## 题目描述

HQ 需要管理 $n$ 个宿舍的灯，第 $i$ 个宿舍的同学因为有着传奇颜值而十分挑剔，只能忍受亮度为 $[l_i,r_i]$ 的灯。每个宿舍的灯的亮度可以在对应的可忍受范围内肆意调节。

今天陈添润决定成为总司令，对所有宿舍的灯进行调节，为了防止被 HQ 当场抓捕，他不能让 HQ 发觉宿舍的灯太过刺眼，当连续 $a$ 个宿舍的灯亮都大于 $b$ 的时候，宿舍的灯就刺眼了。$\color{white}\text{不可以，总司令}$

因此，帮助陈添润数一数一共有多少灯泡调节方案能满足宿舍不刺眼，答案对 $998244353$ 取模。

## 说明/提示

### 样例解释

对于样例 $1$，只有两种方案： $\{3,3,2\}$  或者 $\{3,3,3\}$ 能满足条件。

对于样例 $3$，请将答案对 $998244353$ 取模。

### 数据范围

**本题采用捆绑测试。**

对于所有数据，满足 $1\le n\le 2\cdot 10^5$，$1\le a\le n+1$，$1\le b\le 10^9$，$1\le l_i\le r_i\le 10^9$。

| $\textrm{Subtask}$ | $n,(a-1)\le$ | $l_i,r_i,b\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $20$ | 无 | $10$ |
| $2$ | $2\cdot 10^5$ | $10^9$ | $a=n+1$ | $10$ |
| $3$ | $2\cdot 10^5$ | $10^9$ | $a=1$ | $10$ |
| $4$ | $10^3$ | $10^9$ | 无 | $30$ |
| $5$ | $2\cdot 10^5$ | $10^9$ | 无 | $40$ |


## 样例 #1

### 输入

```
3 1 3
3 4
3 3
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
5 2 5
2 4
1 6
5 10
1 1
5 6```

### 输出

```
186```

## 样例 #3

### 输入

```
12 9 66
41 76
33 61
10 25
84 86
20 49
43 59
26 56
44 71
48 79
1 35
27 83
49 76```

### 输出

```
358014651```

# 题解

## 作者：xiezheyuan (赞：10)

## 简要题意

有一个序列 $S$，第 $i$ 个位置可以取 $[l_i,r_i]$ 中的数，但是不能存在一个长度大于等于 $a$ 且所有数大于 $b$ 的子串。求满足条件的 $S$ 数量，对 $998,244,353$ 取模。

$1 \leq n \leq 2\times10^5,1 \leq l_i,r_i,b \leq 10^9$

## 思路


### 朴素的 dp

这道题不应该评绿吧……我觉得评个紫都不过分……

我们考虑 dp，设 $f(i,j)$ 表示以第 $i$ 个数结尾，构成了一个长度为 $j$ 的所有数大于 $b$ 的子串。

然后分情况讨论。令 $g(x,l,r)$ 表示 $[l,r]$ 中大于 $x$ 的数字数量。当 $j=0$ 时，$i-1$ 构成了长度为多少的子串就无所谓了，也就是说：

$$
f(i,0)=(r_i-l_i+1-g(b,l_i,r_i))\cdot\sum_{k=0}^{a-1}f(i-1,k)
$$
当 $j\neq 0$ 时，只有一种转移，也就是 $i-1$ 构成了一个长度为 $j-1$ 的子串。也就是说：

$$
f(i,j)=f(i-1,j-1)\cdot g(b,l_i,r_i)
$$
时间复杂度 $O(n^2)$。[你应该可以拿到 40 分](https://www.luogu.com.cn/record/113187177)。

### 奇怪的 dp 优化

首先这玩意显然可以滚动数组。

然后考虑这个 dp 的数据结构意义。对于 $f(i,0)$，本质上是一个区间 $[0,a-1]$ 求和。而 $j\neq 0$，由于 $f(,j)$ 由 $f(,j-1)$ 转移过来，因此可以看成整体向右平移 $1$ 位（多的一个数直接扔掉），然后区间 $[1,a-1]$ 乘 $g(b,l_i,r_i)$（注意顺序）。

理一下维护 dp 数组需要支持的操作：

- 区间乘
- 区间求和
- 单点修改
- 区间位移

前三个线段树都可以胜任，但是第四个……我们可以考虑使用文艺平衡树。

（题目主人公叫做 HQ，是不是在提醒我们使用 FHQ-Treap？)

## 代码

注意 FHQ-Treap 的乘法标记默认值要为 $1$！

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

long long n,a,b;
const int N = 2e5+5;
struct student{
	long long l,r;
} s[N];
int SUPER_BIG = -1;
const int mod = 998244353;
typedef int LL;
LL mul(LL a, LL b, LL P=mod){
	LL L = a * (b >> 25LL) % P * (1LL << 25) % P;
	LL R = a * (b & ((1LL << 25) - 1)) % P;
	return (L + R) % P;
}

int M(int x){
	return (x%mod+mod)%mod;
}

int bad_way(int x){
	if(s[x].l>b) return M(s[x].r-s[x].l+1);
	else if(s[x].r<b) return 0;
	else return M(s[x].r-b);
}


namespace FHQTreap{
	const int SIZE = 2e6+5;
	int son[SIZE][2];
	int val[SIZE],rk[SIZE],siz[SIZE],root,points,tag[SIZE],add[SIZE];
	int sumt[SIZE];
	mt19937 randomer(time(0));
	
#define ls(i) (son[(i)][0])
#define rs(i) (son[(i)][1])
	
	void pushup(int i){
// 		val[ls(i)]=M(val[ls(i)]);add[ls(i)]=M(add[ls(i)]);sumt[ls(i)]=M(sumt[ls(i)]);
// 		val[rs(i)]=M(val[rs(i)]);add[rs(i)]=M(add[rs(i)]);sumt[rs(i)]=M(sumt[rs(i)]);
		siz[i]=siz[ls(i)]+siz[rs(i)]+1;
		sumt[i]=M(sumt[ls(i)]+M(sumt[rs(i)]+val[i]));
	}
	
	void pushdown(int i){
// 		val[ls(i)]=M(val[ls(i)]);add[ls(i)]=M(add[ls(i)]);sumt[ls(i)]=M(sumt[ls(i)]);
// 		val[rs(i)]=M(val[rs(i)]);add[rs(i)]=M(add[rs(i)]);sumt[rs(i)]=M(sumt[rs(i)]);
		if(add[i]!=1){
			add[i]=M(add[i]);
// 			val[ls(i)]=M(val[ls(i)]);add[ls(i)]=M(add[ls(i)]);sumt[ls(i)]=M(sumt[ls(i)]);
// 			val[rs(i)]=M(val[rs(i)]);add[rs(i)]=M(add[rs(i)]);sumt[rs(i)]=M(sumt[rs(i)]);
			add[ls(i)]*=add[i];sumt[ls(i)]*=add[i];val[ls(i)]*=add[i];
			add[rs(i)]*=add[i];sumt[rs(i)]*=add[i];val[rs(i)]*=add[i];	
			val[ls(i)]=M(val[ls(i)]);add[ls(i)]=M(add[ls(i)]);sumt[ls(i)]=M(sumt[ls(i)]);
			val[rs(i)]=M(val[rs(i)]);add[rs(i)]=M(add[rs(i)]);sumt[rs(i)]=M(sumt[rs(i)]);
			add[i]=1;
		}
	}
	
	int newnode(int v,int weight=randomer()){
		val[++points]=M(v);
		rk[points]=weight;
		siz[points]=1;
		add[points]=1;
		return points;
	}
	
	void split(int p,int v,int &left,int &right){
		if(!p){
			left=right=0;
			return;
		}
		pushdown(p);
		if(siz[ls(p)]<v){
			left=p;
			split(rs(p),v-siz[ls(p)]-1,rs(left),right);
		}
		else{
			right=p;
			split(ls(p),v,left,ls(right));
		}
		pushup(p);
	}
	
	int merge(int left,int right){
		if(!left||!right){
			if(left)return left;
			else if(right)return right;
			else return 0;
		}
		pushdown(left);
		pushdown(right);
		if(rk[left]<rk[right]){
			ls(right)=merge(left,ls(right));
			pushup(right);
			return right;
		}
		else{
			rs(left)=merge(rs(left),right);
			pushup(left);
			return left;
		}
	}
	
	void update(int l,int r,int v){
		int left=0,mid=0,right=0;
		split(root,r,left,right);
		split(left,l-1,left,mid);
		v=M(v);
// 		add[mid]=M(add[mid]);val[mid]=M(val[mid]);sumt[mid]=M(sumt[mid]);
		add[mid]=mul(add[mid],v);val[mid]=mul(val[mid],v);sumt[mid]=mul(sumt[mid],v);
		add[mid]=M(add[mid]);val[mid]=M(val[mid]);sumt[mid]=M(sumt[mid]);
		root=merge(left,merge(mid,right));
	}
	
	int query(int l,int r){
		int left=0,mid=0,right=0,ret=0;
		split(root,r,left,right);
		split(left,l-1,left,mid);
		ret=M(sumt[mid]);
		root=merge(left,merge(mid,right));
		return ret;
	}
	
	void right_move(){
		int A = newnode(0),B,C;
		split(root,a-1,B,C);
		root=merge(A,B);
	}
	
	void assign(int p,int v){
		int A,B=newnode(v),C,D;
		split(root,p-1,A,C);
		split(C,p,D,C);
		root=merge(A,merge(B,C));
	}
}
using namespace FHQTreap;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>a>>b;
	root=merge(root,newnode(1));
	for(int i=2;i<=a;i++) root=merge(root, newnode(0));
	for(int i=1;i<=n;i++) cin>>s[i].l>>s[i].r;
	for(int i=1;i<=n;i++){
		int sum=query(1,a)%mod;
		sum = M(sum * (M(s[i].r-s[i].l+1)-bad_way(i)));
		right_move();
		update(2,a,bad_way(i));
		assign(1,sum);
	}
	int ans = 0;
	for(int i=1;i<=a;i++) ans = M(ans+query(i,i));
	cout<<((long long)(ans%mod));
	return 0;
}
```


---

## 作者：Xy_top (赞：9)

E 题居然比 C D 都要简单？

我的做法和题解里的做法不一样，麻烦了许多。

首先看到连续的几盏灯刺眼就不行了，当然能够想到动态规划，设 $f[i][j]$ 为看到第 $i$ 个宿舍，末尾有连续 $j$ 个灯刺眼，且前面的灯都合法的方案数。

当前这盏灯，可以刺眼也可以不刺眼，刺眼：

$f[i][j]=f[i - 1][j - 1]\times\text{当前灯刺眼的方案数}$。

不刺眼的话，前面再多连续的刺眼都废了，所以：

$f[i][0] = (f[i - 1][1] + f[i - 2][2] + \cdots + f[i - 1][a - 1]) \times \text{当前灯不刺眼的方案数}$。

然后就能得到 $O(n^2)$ 的做法了：

```cpp
#include <iostream>
#define int long long
using namespace std;
int n, a, b;
int l[200005], r[200005];
int f[1005][1005];//前 i 盏，末尾有连续 j 盏刺眼 
const int mod = 998244353;
int fun (int x, int y, int z) {
	if (y <= z) return 0;
	if (x <= z) return y - z;
	return y - x + 1;
}
int fun_ (int x, int y, int z) {//x 到 y 中小于等于 z 的数的个数 
	if (x > z) return 0;
	return min (y, z) - x + 1;
}
signed main () {
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i ++) cin >> l[i] >> r[i];
	if (a == n + 1) {
		long long ans = 1;
		for (int i = 1; i <= n; i ++) {
			ans *= long (r[i] - l[i] + 1);
			ans %= mod;
		}
		cout << ans << "\n";
	} else if (a == 1) {
		long long ans = 1;
		for (int i = 1; i <= n; i ++) {
			if (l[i] > b) ans = 0;
			else ans *= long (min (r[i], b) - l[i] + 1);
			ans %= mod;
		}
		cout << ans << "\n";
	} else {
		long long ans = 0;
		f[0][0] = 1;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j < a; j ++) {
				f[i][j] = f[i - 1][j - 1] * fun (l[i], r[i], b) % mod;
			}
			for (int j = 0; j < a; j ++) {
				f[i][0] += f[i - 1][j];
				if (f[i][0] > mod) f[i][0] -= mod;
			}
			f[i][0] = f[i][0] * fun_ (l[i], r[i], b) % mod;
		}
		for (int i = 0; i < a; i ++) ans = (ans + dp[n][i]) % mod;
		cout << ans << "\n";
	}
	return 0;
}
```

接着来考虑怎么优化呢？我试了半天，这个东西不能用斜率，不能用四边形不等式，好像没啥好优化的，这时就要转换状态了。

根据正难则反的经典套路，我们再设 $F[i]$ 为到第 $i$ 个宿舍，刺眼的方案数，就发现可以了。

为了不重复的统计每一个刺眼的方案，如果一个方案有多个连续的 $a$ 盏刺眼的灯，它只会被第一个连续 $a$ 个刺眼的灯来统计。

所以：$F[i] = F[i - 1] \times \text{当前这个灯乱填(前面已经不满足了加上这个也不满足)}$

$+\text{最近 a 个全部刺眼的方案数}\times \text{第 i - a 个不刺眼的方案数 (或者第 i - a 个是 0 号宿舍)}\times \text{(i - a - 1 以及再之前的灯都不刺眼的方案数)}$。

乱搞的方案数显然是 $r[i] - l[i] + 1$，后面呢？

最近 $a$ 个灯全部刺眼和第 $a - 1$ 个灯不刺眼也好弄，而 $i-a-1$ 以及前面的灯都不刺眼的方案数，其实就是 $f[i - a - 1]$。

$f$ 怎么求呢？根据刚刚的正难则反，显然 $f$ 等于全部乱填减去不合法的方案数。

状态转移方程：

$f[i] = luangao[i] - F[i]$

$F[i] = F[i - 1] \times (r[i] - l[i] + 1) + ciyan[i] \times inv (ciyan[i - a] \times buciyan (l[i - a], r[i - a], a) \times f[i - a - 1])$，其中 $buciyan (l, r, k)$ 求的是 $l$ $r$ 中有多少数小于等于 $k$。

其实把 $f$ 的方程带回 $F$ 更简单了，可以自己试下。

初始化细节很多，大家仔细看下。状态转移方程较麻烦，不过代码还行：

```cpp
#include <iostream>
#define int long long
using namespace std;
int n, a, b;
int l[200005], r[200005];
int f[200005], F[200005];
int luangao[200005];
int ciyanfangan[200005], zero[200005];
const int mod = 998244353;
int ciyande (int x, int y, int z) {
	if (y <= z) return 0;
	if (x <= z) return y - z;
	return y - x + 1;
}
int buciyande (int x, int y, int z) {
	if (x > z) return 0;
	return min (y, z) - x + 1;
}
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
int inv (int x) {return q_pow (x, mod - 2);}
signed main () {
	cin >> n >> a >> b;
	luangao[0] = 1;
	for (int i = 1; i <= n; i ++) {
		cin >> l[i] >> r[i];
		luangao[i] = luangao[i - 1] * (r[i] - l[i] + 1) % mod;
		if (ciyande (l[i], r[i], b) == 0) zero[i] = 1;
		zero[i] += zero[i - 1];
	}
	for (int i = 1; i + a - 1 <= n; i ++) {
		if (zero[i + a - 1] - zero[i - 1] != 0) continue;
		if (ciyanfangan[i - 1] != 0) {
			ciyanfangan[i] = ciyanfangan[i - 1] * inv (ciyande (l[i - 1], r[i - 1], b) ) % mod * ciyande (l[i + a - 1], r[i + a - 1], b) % mod;
			continue;
		}
		ciyanfangan[i] = 1;
		for (int j = i; j <= i + a - 1; j ++) ciyanfangan[i] = ciyanfangan[i] * ciyande (l[j], r[j], b) % mod;
	}
	for (int i = 0; i < a; i ++) f[i] = luangao[i];
	f[0] = 1;
	F[a] = ciyanfangan[1];
	f[a] = ( (luangao[a] - F[a]) % mod + mod) % mod;
	for (int i = a + 1; i <= n; i ++) {
		F[i] = (F[i - 1] * (r[i] - l[i] + 1) % mod + f[i - a - 1] * ciyanfangan[i - a + 1] % mod * buciyande (l[i - a], r[i - a], b) % mod);
		f[i] = ( (luangao[i] - F[i]) % mod + mod) % mod;
	}
	cout << f[n] << "\n";
	return 0;
}
```


---

## 作者：Phobia (赞：6)

显然有这样一个想法，设 $f(i,j)$ 表示前 $i$ 个位置，以第 $i$ 个灯结尾的最大连续灯泡亮度大于 $b$ 的子串长度为 $j$ 和法的方案数。

转移方程：

$$f(i,0)=\begin{cases}(\min(b,r_i)-l_i+1)\sum_{j=0}^{a-1}f(i-1,j),&l_i\le b\\0,&l_i>b.\end{cases}$$

$$f(i,j)=\begin{cases}(r_i-\min(b,l_i-1))f(i-1,j-1),&r_i>b\\0,&r_i\le b.\end{cases}(0<j<a)$$

直接转移显然不行，但观察到 $f(i)$ 和 $f(i-1)$ 之间的存在继承关系，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/z6d81ilk.png)

相当于在 $f(i-1)$ 前面插入一个数和在后面删除一个数，然后再批量处理，故想到使用数据结构维护。

此时已经可以使用平衡树或块状链表维护，注意到至多向前插入 $n$ 个元素，考虑开一颗线段树维护一个长度为 $n+a$ 的数组，再用两个变量记录当前维护的左端点和右端点，初始在最右边，转移时将左、右端点往左移动一个单位。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 200005, mod = 998244353;

int n, a, b;

int tre[maxn * 8], mul[maxn * 8], m, pl, pr; // pl, pr 维护 f 数组第二维对应线段树上的编号范围

int read()
{
    int ret = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        ;
    for (; isdigit(ch); ch = getchar())
        ret = (ret << 3) + (ret << 1) + (ch & 15);
    return ret;
}

void build(int root, int l, int r)
{
    mul[root] = 1;
    if (l < r)
    {
        int mid = l + r >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
    }
}

void push_down(int root)
{
    if (mul[root] != 1)
    {
        tre[root << 1] = (i64)tre[root << 1] * mul[root] % mod;
        mul[root << 1] = (i64)mul[root << 1] * mul[root] % mod;
        tre[root << 1 | 1] = (i64)tre[root << 1 | 1] * mul[root] % mod;
        mul[root << 1 | 1] = (i64)mul[root << 1 | 1] * mul[root] % mod;
        mul[root] = 1;
    }
}

void modify(int root, int l, int r, int x, int v)
{
    if (l == r)
    {
        tre[root] = v;
        return;
    }
    int mid = l + r >> 1;
    push_down(root);
    if (x <= mid)
        modify(root << 1, l, mid, x, v);
    else
        modify(root << 1 | 1, mid + 1, r, x, v);
    tre[root] = (tre[root << 1] + tre[root << 1 | 1]) % mod;
}

void multiply(int root, int l, int r, int x, int y, int v)
{
    if (x <= l && r <= y)
    {
        tre[root] = (i64)tre[root] * v % mod;
        mul[root] = (i64)mul[root] * v % mod;
        return;
    }
    int mid = l + r >> 1;
    push_down(root);
    if (x <= mid)
        multiply(root << 1, l, mid, x, y, v);
    if (mid < y)
        multiply(root << 1 | 1, mid + 1, r, x, y, v);
    tre[root] = (tre[root << 1] + tre[root << 1 | 1]) % mod;
}

int sum(int root, int l, int r, int x, int y)
{
    if (l > y || r < x)
        return 0;
    if (x <= l && r <= y)
        return tre[root];
    int mid = l + r >> 1;
    push_down(root);
    return (sum(root << 1, l, mid, x, y) + sum(root << 1 | 1, mid + 1, r, x, y)) % mod;
}

int main()
{
    n = read(), a = read() - 1, b = read();
    m = n + a + 1, pr = n + a + 1, pl = n + 1;
    build(1, 1, m);
    modify(1, 1, m, pl, 1);
    for (int i = 1; i <= n; ++i)
    {
        int l = read(), r = read();
        if (l <= b)
            modify(1, 1, m, pl - 1, (i64)(min(b, r) - l + 1) * sum(1, 1, m, pl, pr) % mod);
        if (r > b)
            multiply(1, 1, m, pl, pr, r - max(b, l - 1));
        else
            multiply(1, 1, m, pl, pr, 0); // 这里等价于区间修改为 0
        --pl, --pr;
    }
    printf("%d\n", sum(1, 1, m, pl, pr));
    return 0;
}
~~~

~~数据结构优化 dp 实锤了。~~

---

## 作者：MichaelWong (赞：5)

# P9400 「DBOI」Round 1 三班不一般

当我看到 “动态规划” 与 “线段树” 这两个 tag 同时出现的时候，我就知道这道题也不一般。

## 题意简述

- $n$ 个宿舍，每个宿舍的灯可以在 $[l_i,r_i]$ 内调节；
- 连续 $a$ 盏灯亮度超过 $b$ 则为刺眼；
- 求不刺眼的所有方案数，对 $998244353$ 取模。

## 解法分析

### DP

可以确定这是一个 DP，首先我们设计状态。$dp(i,j)$ 表示第 $i$ 个宿舍是连续的第 $j$ 个亮度超标的宿舍，此时的方案数；特别地，$dp(i,0)$ 表示第 $i$ 个宿舍的亮度并没有超标。分析状态数 $i_{max} \cdot j_{max} = n \cdot a \simeq 4 \times 10^{10}$，这可太大了，我们开不下。所以考虑 **滚动** 一下，相信大家对这个优化都不陌生。

用 $dp_i$ 表示当前宿舍是连续第 $i$ 个刺眼的宿舍，可以写出转移方程如下：

$$dp_0 = \begin{cases}
0 ,& l > b \\
\left[ \min (b,r_i) - l_i +1 \right] \cdot \sum \limits_{j=0}^{a-1} dp_j ,& l \leq b
\end{cases}$$
$$dp_i = \begin{cases}
0 ,& r \leq b\\
\left[ r_i - \max (b+1,l_i) +1 \right] \cdot dp_{i-1} ,& r>b 
\end{cases}$$

初值：$dp_0 = 1$，目标：$\sum \limits_{i=0}^{a-1} dp_i$。

朴素地按照这个转移方程写，复杂度在 $O(n^2)$ 左右。这显然不是我们想要的，$n^2 \simeq 4 \times 10^{10}$，必然会 T，所以我们考虑一下如何让它更快一点。

### 线段树优化

观察转移方程，我们会发现一个惊人的性质：

- $dp_0$ 是上个阶段所有方案数的和 $\times \left[ \min (b,r_i) - l_i +1 \right]$
- $\forall i \neq 0, \ dp_i$ 转移时的乘数都是一个数：$\left[ r_i - \max (b+1,l_i) +1 \right]$。

一个是区间和，一个是区间乘，我们因而想到了处理区间的利器——线段树。

于是考虑使用线段树优化状态转移，用线段树的 **值域** 对应 $dp$ 的 **下标**。接着就会遇到两个问题：

- $dp_0$ 放在哪？
- $\forall i \neq 0, \ dp_i$ 的转移都是依靠 $dp_{i-1}$，怎么实现这个 **区间移动**？

我就想了一个及其骚的方法。

- 考虑开一个值域 $[1,a]$ 的线段树，而我们需要的下标值域是 $[0,a-1]$，所以空出来的那个位置就留给 $dp_0$，即把它放在 $a$ 的位置。
- 如果每一次状态转移后区间不移动，上一个阶段的 $dp_{a-1}$ 在为此阶段的 $dp_0$ 提供贡献以后就 **没用** 了，因为 $dp_a$ 是 **非法的**；而上个阶段的 $dp_0$ 就会转移为 $dp_1$。
- 所以考虑 **区间不移动**，维护线段树中 $dp_0$ 的位置 $pos$，每次都占据上一阶段 $dp_{a-1}$ 的位置，相当于每个阶段左移一位。于是只需要区间和与区间乘，相当于整个区间代表的 $dp_i$ 下标一直在 **滚动**。

问题迎刃而解。我们最后梳理一下过程：

1. 赋初值：$pos \gets a, dp_0 \gets 1$；

1. 对于每一个阶段：
	- 上一阶段的 $dp_{a-1}$ 失效，所以 $dp_0$ 的位置向左移一位，即 $pos \gets pos-1$；
    
    	注意到 $pos$ 可能左移到 $0$，所以 **如果** $pos=0,\ pos \gets a$，使 $pos$ 重新回到区间最左边。

	- **如果** $l \leq b$，查询 $[1,a-1]$ 的区间和 $\times \left[ \min (b,r_i) - l_i +1 \right]$ 赋值给 $dp_0$；

      **否则** $dp_0$ 单点修改为 $0$。
      
	- **如果** $r	> b$，对 $[1,pos-1] \cup [pos+1,a]$ 区间 $\times \left[ r_i - \max (b+1,l_i) +1 \right]$；
    
    	**否则** $[1,pos-1] \cup [pos+1,a]$ 区间覆盖为 $0$。
        
1. 最后输出 $[1,a]$ 的 $dp$ 的和。

## 代码实现

综上所述，我们的线段树需要支持如下操作：

- 区间乘
- 单点修改
- 区间覆盖
- 区间（单点）查询

然后根据上面的流程来实现即可。注意因为模数过大所以还是需要 `long long`。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ls x<<1
#define rs x<<1|1
#define pii std::pair<int,int>
#define fsp(x) std::fixed<<std::setprecision(x)
#define forE(u) for(int p=head[u],v=to[p];p;p=next[p],v=to[p])
const int N=2e5+5,mod=998244353;
ll sum[N<<2],lazy[N<<2],cvr[N<<2];
void pushup(int x) { sum[x]=(sum[ls]+sum[rs])%mod; }
void pushdown(int x) {
	if(cvr[x]) return sum[ls]=sum[rs]=0,cvr[ls]=cvr[rs]=1,cvr[x]=0,lazy[x]=1,void();
	sum[ls]=sum[ls]*lazy[x]%mod,sum[rs]=sum[rs]*lazy[x]%mod;
	lazy[ls]=lazy[ls]*lazy[x]%mod,lazy[rs]=lazy[rs]*lazy[x]%mod;
	lazy[x]=1;
}
void modify(int x,int l,int r,int pos,int k) { // 单点覆盖 
	if(r<l) return;
	if(l==r) return sum[x]=k,void();
	int mid=l+r>>1; pushdown(x);
	if(pos<=mid) modify(ls,l,mid,pos,k);
	else modify(rs,mid+1,r,pos,k);
	pushup(x);
}
void modify(int x,int L,int R,int l,int r,ll k) { // 区间乘 
	if(r<l||R<L) return;
	if(l<=L && r>=R) return sum[x]=sum[x]*k%mod,lazy[x]=lazy[x]*k%mod,void();
	int M=L+R>>1; pushdown(x);
	if(l<=M) modify(ls,L,M,l,r,k);
	if(r>M) modify(rs,M+1,R,l,r,k);
	pushup(x);
}
void cover(int x,int L,int R,int l,int r) { // 区间以零覆盖 
	if(r<l||R<L) return;
	if(l<=L && r>=R) return sum[x]=0,cvr[x]=1,void();
	int M=L+R>>1; pushdown(x);
	if(l<=M) cover(ls,L,M,l,r);
	if(r>M) cover(rs,M+1,R,l,r);
	pushup(x);
}
ll query(int x,int l,int r,int pos) { // 单点查询 
	if(r<l) return 0;
	if(l==r) return sum[x];
	int mid=l+r>>1; pushdown(x);
	if(pos<=mid) return query(ls,l,mid,pos);
	else return query(rs,mid+1,r,pos);
}
ll query(int x,int L,int R,int l,int r) { // 区间查询 
	if(r<l||R<L) return 0;
	if(l<=L && r>=R) return sum[x];
	int M=L+R>>1,ans=0; pushdown(x);
	if(l<=M) ans=(ans+query(ls,L,M,l,r))%mod;
	if(r>M) ans=(ans+query(rs,M+1,R,l,r))%mod;
	return ans%mod;
}
ll n,a,b,l,r,pos;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);
	std::cin>>n>>a>>b;
	pos=a,modify(1,1,a,pos,1);
	for(int i=1;i<=n;++i) {
		std::cin>>l>>r; --pos;
		if(!pos) pos=a; ll val;
		if(l<=b) val=(std::min(b,r)-l+1)*query(1,1,a,1,a)%mod,modify(1,1,a,pos,val);
		else modify(1,1,a,pos,0);
		if(r>b) val=(r-std::max(b+1,l)+1)%mod,modify(1,1,a,1,pos-1,val),modify(1,1,a,pos+1,a,val);
		else cover(1,1,a,1,pos-1),cover(1,1,a,pos+1,a);
	}
	std::cout<<query(1,1,a,1,a)%mod<<'\n';
	return 0;
}
```

本题解毕。

---

## 作者：liangbowen (赞：5)

[blog](https://www.cnblogs.com/liangbowen/p/17837354.html)。很 naive 的题，写这篇题解，主要是现有题解都用的线段树 / 平衡树，让我感到很难绷。

---

一眼 DP。$dp_{i,j}$ 表示前 $i$ 个宿舍，现在有连续 $j$ 个灯亮大于 $B$，方案数。

+ $dp_{i,0}=\max(\min(B, r_i) - l_i + 1, 0)\cdot\sum\limits_{j=0}^{A-1} dp_{i-1,j}$。
+ $dp_{i,j}=dp_{i-1,j-1}\cdot\max(r_i-\max(B+1,l_i)+1,0)$。初始化 $dp_{0,0}=1$。
+ $O(n^2)$，期望 $40$ 分。

这看起来随便优化啊！记 $v_i=\max(r_i-\max(B+1,l_i)+1,0)$。

+ 处理 $s_i=\sum\limits_{j=0}^{A-1} dp_{i,j}$。你会 $O(1)$ 算 $dp_{i,0}$ 了。
+ $s_i=\sum\limits_{j=0}^{A-1} dp_{i,j}=dp_{i-1,0}+\sum\limits_{j=1}^{A-1} \Large(\normalsize dp_{i-1,j-1}\cdot v_i\Large)\normalsize=dp_{i-1,0}+v_i\cdot\sum\limits_{j=0}^{A-2} dp_{i-1,j}=\color{red}dp_{i-1,0}+v_i\cdot(s_{i-1}-dp_{i-1,A-1})$。你会 $O(1)$ 算 $s_i$ 了。
+ 观察红色部分，你只需要会算 $dp_{i,0}$ 与 $dp_{i,A}$。
+ $dp_{i,A}=v_i\cdot dp_{i-1,A-1}=v_i\cdot v_{i-1}\cdot dp_{i-2,A-2}=\cdots=(\prod\limits_{j=i-A}^A v_j)\cdot dp_{i-A,0}$。在线维护 $\prod v_j$ 即可，可以边增加边用逆元删除。

综上你会线性了。注意数组越界，以及 $0$ 没有逆元，请特殊处理。

[code](https://www.luogu.com.cn/paste/2vajw78m)，时间复杂度 $O(n)$（其实还要算上求逆元的复杂度，不管了）。

[删除注释后仅 1KB](https://www.luogu.com.cn/record/135485285)，加上快读后[无压力跑进 $70$ 毫秒](https://www.luogu.com.cn/record/135485265)，目前速度仅次于出题人。


---

## 作者：_luanyi_ (赞：2)

不是很懂为什么大家觉得这题需要各种高级的 dp 做法。

阅读题面，发现可以算出每个点不刺眼的方案数 $s_i$ 和刺眼的方案数 $t_i$。

令 $f_i$ 表示考虑了前 $i$ 个点，且第 $i$ 个点不刺眼的方案数。令 $s_{n+1}=1,t_{n+1}=0$ 则答案为 $f_{n+1}$。

边界 $f_0=1$。考虑转移，枚举上一个不刺眼的点的位置 $j$，可得
$$
f_i=s_i\sum\limits_{j=i-a}^{i-1}f_j\prod\limits_{k=j+1}^{i-1}t_k
$$
其实 $j$ 的下界要和 $0$ 取一个 $\max$。

发现求和的部分很可以线段树优化，每次 $i$ 右移 $1$ 时相当于一个区间乘 $t_i$，那么就做完了，复杂度 $O(n\log n)$。

需要一棵单点修改，区间乘，区间求和线段树。

```cpp
// 省略了码头，线段树，变量定义和初始化

signed main () {
	// 省略了读入，计算 s 和 t 数组，代码中分别为 s0 和 s1
    
	++n; s0[n] = 1;
	upd (0, n, 1, 0, 1); f[0] = 1;
	fq (i, 1, n) {
		f[i] = query (i-a, i-1, 0, n, 1) * s0[i]; // query 计算区间和
		update (0, n, 0, n, 1, s1[i]); // update 区间乘操作
		upd (0, n, 1, i, f[i]); // upd 单点修改操作
	}
	cout << f[n] << endl;
	return 0;
}
```

---

## 作者：Hooch (赞：2)

定义一个方案中的区间 $[i,j]$ 合法，则 $[i,j]$ 中没有长度为 $a$，每个灯泡亮度都大于 $b$ 的子串。

设 $f_{i,j}$ 表示考虑前 $i$ 个位置，以第 $i$ 个灯结尾的最大连续灯泡亮度大于 $b$ 的子串长度为 $j$，$[1,i]$ 合法的方案数。$g_i$ 表示考虑前 $i$ 个灯，第 $i$ 个灯亮度小于等于 $b$ 且 $[1,i]$ 合法的方案总数。

最后答案是 $g_n+\sum\limits_{k=0}^{a-2}f_{n,k}$。

令 $up_i,down_i$ 分别表示第 $i$ 个灯亮度大于和小于等于 $b$ 的取值总数，则 $up_i = \max\{0, r_i-\max\{b+1,l_i\}+1\}$， $down_i=\max\{0, \min\{r_i,b\}-l_i+1\}$

转移：

$$
\begin{aligned}
&f_{i,0}=g_{i-1}\cdot up_i\\
&f_{i,j}=f_{i-1,j-1}\cdot up_i\\
&g_i=(g_{i-1}+\sum\limits_{k=0}^{a-2}f_{i-1,k})\cdot down_i
\end{aligned}
$$

可以发现：$f_{i,j}=g_{i-j-1}\cdot \prod\limits_{k=i-j}^i up_k$。所以我们不用专门转移 $f，$只用维护 $\sum\limits_{k=0}^{a-2}f_{i-1,k}$ 就可以了。

令 $\textrm{M}(x,y)$ 表示 $\prod\limits_{i=x}^yup_i$，则：

$$
\begin{aligned}
\sum\limits_{k=0}^{a-2}f_{i-1,k}=&g_{i-2}\cdot \textrm{M}(i-1,i-1)+\\
&g_{i-3}\cdot\textrm{M}(i-2,i-1)+\cdots\\
&g_{i-a}\cdot\textrm{M}(i-a+1,i-1)
\end{aligned}
$$

当从 $i$ 转移到 $i+1$ 时，它的值会有如下变化：

1. 减去 $g_{i-a}\cdot \textrm{M}(i-a+1,i-1)$。
2. 加上 $g_{i-1}$。
3. 乘上 $up_i$。

这样即可 $\mathcal{O}(1)$ 维护 $\sum\limits_{k=0}^{a-2}f_{i-1,k}$ 的值，可以 $\mathcal{O}(n)$ 求出 $g$。总时间复杂度 $\mathcal{O}(n\log p)$，瓶颈在于求 $\textrm{M}$。

[code](https://www.luogu.com.cn/paste/gc7sgpsm)

---

## 作者：ADNAP (赞：1)

### DP
用 $dp_{i,j}$ 来表示当前考虑了前 $i$ 个宿舍，当前连续 $j$ 个宿舍的灯亮大于 $b$。

我们可以得到以下转移方程：

当 $1 \le j \le a-1$ 时：
$$dp_{i,j}=dp_{i-1,j-1} \times (r_i - \max(b,l_i-1))$$

当 $j=0$ 时：
$$dp_{i,0}=\Sigma_{j=0}^{a-1}(dp_{i-1,j} \times (\min(b,r_i)-l_i+1))$$

### 优化
#### 滚动数组(但是加了线段树之后没用上)
如果我们之间开 $dp$ 数组，大小为 $n^2$，不满足数据范围。

观察到 $dp$ 转移方程中，当前宿舍的方案数只需由前一个宿舍的方案数与当前宿舍的有关信息即可得到。与再往前的宿舍无关，因此我们可以使用滚动数组。

#### 线段树优化
对于 $1 \le j \le a-1$ 时，我们发现转移过程中相乘的值都相等，可以转换成区间乘。

对于 $j=0$ 时，我们则需要维护区间和。

另外，我们发现第一个方程中 $j$ 的状态由 $j-1$ 转移得到。第二个方程又新加入了一个状态。在线段树上的体现就是整体向后移，最后一个状态删去，又在最前面加上一个值。

实现的时候可以定义两个指针，表示计算得到当前宿舍方案数的区间。建树时多建 $n$ 个点，每次完成转移后头尾指针都向前移动一位，原来最后的点就被删去，最前面加入新值。**注意在线段树上转移的时候先插入新点，否则后面的值都已被修改**。

### CODE
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+1e2;
const ll Mod=998244353;
ll n,a,b;
ll k;
struct Range
{
    ll l,r;
}s[N];
// ll dp[2][N];
ll ans;
struct Tree
{
    ll l,r;
    ll add;
    ll mul;
    ll sum;
}tr[N<<3];
void pushup(ll u)
{
    tr[u].sum=(tr[u<<1].sum+tr[u<<1|1].sum)%Mod;
}
void build(ll u,ll l,ll r)
{
    tr[u].l=l,tr[u].r=r;
    tr[u].add=0,tr[u].mul=1;
    if(l==r)
    {
        if(l==n)tr[u].sum=1;
        else tr[u].sum=0;
        // if(l>=n)tr[u].sum=dp[0][l-n]%Mod;
        return ;
    }
    ll mid=(l+r)>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    pushup(u);
}
void pushdown(ll u)
{
    if(tr[u].mul!=1)
    {
        tr[u<<1].sum=tr[u<<1].sum*tr[u].mul%Mod;
        tr[u<<1].add=tr[u<<1].add*tr[u].mul%Mod;
        tr[u<<1].mul=tr[u<<1].mul*tr[u].mul%Mod;
        tr[u<<1|1].sum=tr[u<<1|1].sum*tr[u].mul%Mod;
        tr[u<<1|1].add=tr[u<<1|1].add*tr[u].mul%Mod;
        tr[u<<1|1].mul=tr[u<<1|1].mul*tr[u].mul%Mod;
        tr[u].mul=1;
    }
    if(tr[u].add!=0)
    {
        tr[u<<1].sum+=tr[u].add*(tr[u<<1].r-tr[u<<1].l+1),tr[u<<1].sum%=Mod,tr[u<<1].add+=tr[u].add,tr[u<<1].add%=Mod;
        tr[u<<1|1].sum+=tr[u].add*(tr[u<<1|1].r-tr[u<<1|1].l+1),tr[u<<1|1].sum%=Mod,tr[u<<1|1].add+=tr[u].add,tr[u<<1|1].add%=Mod;
        tr[u].add=0;
    }
}
void modify_mul(ll u,ll l,ll r)
{
    if(tr[u].l>r||tr[u].r<l)return ;
    if(l<=tr[u].l&&tr[u].r<=r)
    {
        tr[u].sum=tr[u].sum*k%Mod;
        tr[u].add=tr[u].add*k%Mod;
        tr[u].mul=tr[u].mul*k%Mod;
        return ;
    }
    pushdown(u);
    modify_mul(u<<1,l,r);
    modify_mul(u<<1|1,l,r);
    pushup(u);
}
ll query(ll u,ll l,ll r)
{
    if(tr[u].l>r||tr[u].r<l)return 0;
    if(l<=tr[u].l&&tr[u].r<=r)return tr[u].sum%Mod;
    pushdown(u);
    return (query(u<<1,l,r)+query(u<<1|1,l,r))%Mod;
}
void modify_add(ll u,ll l,ll r)
{
    if(tr[u].l>r||tr[u].r<l)return ;
    if(l<=tr[u].l&&tr[u].r<=r)
    {
        tr[u].add+=k,tr[u].add%=Mod;
        tr[u].sum+=k*(tr[u].r-tr[u].l+1)%Mod,tr[u].sum%=Mod;
        return ;
    }
    pushdown(u);
    modify_add(u<<1,l,r);
    modify_add(u<<1|1,l,r);
    pushup(u);
}
signed main()
{
    cin>>n>>a>>b;
    for(ll i=1;i<=n;i++)
        cin>>s[i].l>>s[i].r;
    // dp[0][0]=1;
    build(1,0,n+a-1);
    ll head=n,tail=n+a-1;
    //0 a-1
    for(ll i=1;i<=n;i++)
    {
        head--;
        //-1 a-1
        if(b-s[i].l+1>0)
        {
            k=query(1,head+1,tail)*(min(b,s[i].r)-s[i].l+1)%Mod;
            modify_add(1,head,head);
            // for(ll j=0;j<a;j++)
            //     dp[1][0]+=dp[0][j]*(min(b,s[i].r)-s[i].l+1)%Mod,dp[1][0]%=Mod;
        }
        //-1  a-1
        tail--;
        //-1 a-2
        if(s[i].r>b)
        {
            k=(s[i].r-max(b,s[i].l-1))%Mod;
            modify_mul(1,head+1,tail);
            // for(ll j=1;j<a;j++)
            //     dp[1][j]=dp[0][j-1]*(s[i].r-max(b,s[i].l-1))%Mod;
        }
        else
        {
            k=0;
            modify_mul(1,head+1,tail);
        }
        // memcpy(dp[0],dp[1],sizeof dp[0]);
        // memset(dp[1],0,sizeof dp[1]);
    }
    //0 a-1
    ans=query(1,head,tail);
    // for(ll j=0;j<a;j++)ans=(ans+dp[0][j])%Mod;
    cout<<ans;
}
```

---

## 作者：harmis_yz (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/8qahaaun)。

原来这叫整体 DP。

## 分析

考虑 DP。定义状态函数 $f_{i,j}$ 表示前 $i$ 个数，最后的 $j$ 个数大于 $b$ 的方案数。那么对于第 $i$ 个宿舍，有 $\max(0,r_i-\max(l_i-1,b))$ 种方案大于 $b$，$r_i-l_l+1-\max(0,r_i-\max(l_i-1,b))$ 种方案不超过 $b$。如果这个宿舍大于 $b$，有：$f_{i,j}=f_{i-1,j-1}\times \max(0,r_i-\max(l_i-1,b))$。如果不超过 $b$，显然连续大于 $b$ 的数量变成 $0$ 了，有：$f_{i,0}=\sum\limits_{j=0}^{a-1}f_{i-1,j}\times (r_i-l_i+1-\max(0,r_i-\max(l_i-1,b)))$。

不难发现，除了 $j=0$ 的情况，其它所有的转移方程都是整体往后移动 $1$ 然后乘上 $\max(0,r_i-\max(l_i-1,b))$。这里有个简单的做法，因为我们的 $j$ 是后 $j$ 个数的意思，所以可以视作距离 $i$ 为 $j$ 的一个位置。那么整体往后移动就可以看作是将 $[i-a+1,i-1]$ 的 DP 值整体乘上了 $\max(0,r_i-\max(l_i-1,b))$。然后 $i$ 这个位置的值为 $[i-a,i-1]$ 更新之前的值的和乘上 $r_i-l_i+1-\max(0,r_i-\max(l_i-1,b))$。

这个直接线段树维护可以做到 $O(n\log n)$。

## 代码

```cpp
il void up(int u){
	tr[u].s=(tr[ls(u)].s+tr[rs(u)].s)%p;
	return ;
}
il void down(int u){
	if(tr[u].tag==1) return ;
	tr[ls(u)].tag=tr[ls(u)].tag*tr[u].tag%p,
	tr[rs(u)].tag=tr[rs(u)].tag*tr[u].tag%p;
	tr[ls(u)].s=tr[ls(u)].s*tr[u].tag%p,
	tr[rs(u)].s=tr[rs(u)].s*tr[u].tag%p;
	return tr[u].tag=1,void(0); 
}
il void build(int u,int l,int r){
	tr[u].tag=1,tr[u].l=l,tr[u].r=r;
	if(l==r) return ;
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	return ;
}
il void modify1(int u,int x,int y){
	if(tr[u].l==tr[u].r) return tr[u].s=y,void(0);
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid) modify1(ls(u),x,y);
	else modify1(rs(u),x,y);
	return up(u),void(0);
}
il void modify2(int u,int l,int r,int x){
	if(l>r) return ;
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].tag=tr[u].tag*x%p,
		tr[u].s=tr[u].s*x%p;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify2(ls(u),l,r,x);
	if(mid< r) modify2(rs(u),l,r,x);
	return up(u),void(0);
}
il int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u].s;
	down(u);
	int mid=tr[u].l+tr[u].r>>1,sum=0;
	if(l<=mid) sum=(sum+query(ls(u),l,r))%p;
	if(mid< r) sum=(sum+query(rs(u),l,r))%p;
	return up(u),sum;
}

il void solve(){
	n=rd,a=rd,b=rd;
	build(1,0,n);
	modify1(1,0,1);
	for(re int i=1;i<=n;++i){
		int l=rd,r=rd;
		int x=max(0ll,r-max(l-1,b)),y=r-l+1-x;
		int sum=query(1,max(0ll,i-a),i-1);
		modify2(1,max(0ll,i-a+1),i-1,x);
		modify1(1,i,sum*y%p);
	}
	printf("%lld\n",query(1,max(0ll,n-a+1),n));
    return ;
}
```

---

## 作者：sad_lin (赞：0)

### [P9400 「DBOI」Round 1 三班不一般](https://www.luogu.com.cn/problem/P9400)

看到方案数想到 dp，因为有两个变量：每个灯与连续 $a$ 个超过 $b$ 的灯，所有我们的状态就设为 $f_{i,j}$ 为到第 $i$ 个灯形成了长度为 $j$ 的连续超过 $b$ 的灯。

$h(x,l,r)$ 表示第 $x$ 个灯合法亮度的个数，$g(x,l,r)$ 表示第 $x$ 个灯不合法亮度的个数。

对于 $j=0$ 即到我们这个灯合法，那么上一个的所有长度都可以转移过来：

$$
f_{i,0}=h(i,l_i,r_i)\times \sum_{k=0}^{a-1} f_{i-1,k}
$$

对于 $j\neq 0$ 只能从上一个 $j-1$ 转移过来：

$$
f_{i,j}=g(i,l_i,r_i)\times f_{i-1,j-1}
$$

这样时间复杂度是 $O(n^2)$。

可以发现我们有一个状态方案数的区间和，同时我们发现的状态是会继承的，对于 $f_{i-1}$ 我们乘了一个数然后转移到 $f_{i}$，同时 $f_{i}$ 乘一个数转移到 $f_{i+1}$，这是一个区间乘和整体平移的过程，每次相当于**前面加一个数后面删一个数**，这样的话其实就能在**线段树上滚动**。

于是我们要用线段树实现：

- 区间求和。

- 区间乘。

- 单点修改。

- 区间平移。

其中区间平移可以不断平移固定的线段树的区间即可实现，程序时间复杂度为 $O(n\log n)$。

---

