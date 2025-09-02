# [AGC029C] Lexicographic constraints

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc029/tasks/agc029_c

$ N $ 個の文字列が一列に並んでおり、どの隣り合う $ 2 $ つの文字列に対しても、 左に書いてある文字列の方が右に書いてある文字列よりも辞書順で小さいことが分かっています。 つまり、左から $ i $ 番目の文字列を $ S_i $ としたときに、辞書順で $ S_1\ <\ S_2\ <\ ...\ <\ S_N $ が成り立っています。

$ S_i $ の長さが $ A_i $ であると分かっているとき、$ S_1,S_2,...,S_N $ に含まれる文字の種類数として考えられる最小の値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ A_i $ は整数

### Note

文字列は英字アルファベットからなる必要はない。無限に多くの文字があり、辞書式順序がそれらについて定まっているとして良い。

### Sample Explanation 1

例えば、$ S_1= $`abc`, $ S_2= $`bb`, $ S_3= $`c` のときは$ S_1,S_2,...,S_N $ に含まれる文字の種類数は $ 3 $ になります。 しかし、文字列をうまく選ぶと、文字の種類数を $ 2 $ にすることができます。

## 样例 #1

### 输入

```
3
3 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
2 3 2 1 2```

### 输出

```
2```

# 题解

## 作者：CYJian (赞：12)

以下讨论中，我们将第 $i$ 个字符串表示为 $S_i$。

首先，若钦定字符集大小为 $k$，我们就将第 $i$ 个字符串看成一个长度为 $|S_i|$ 的 $k$ 进制数。

不难发现，这个最小的合法字符集大小 $k$ 是可二分找到的。

我们考虑二分答案之后，如何判断 $k$ 合法。

那么考虑相邻两个串 $S_i$ 和 $S_{i+1}$。

若 $|S_i|<|S_{i+1}|$，则 $S_i$ 是 $S_{i+1}$ 的前缀就能满足  $S_{i}<S_{i+1}$。则只需要在 $S_i$ 后一直补 `a` 至长度 $|S_{i+1}|$ 就能转移成最优的 $S_{i+1}$。

若 $|S_i|\ge |S_{i+1}|$，则需要让 $S_{i+1}$ 的末尾 $+1$ 才能满足 $S_{i} < S_{i+1}$。也就是，让 $S_{i}$ 舍弃掉长度为 $|S_{i}|-|S_{i+1}|$ 的后缀，然后再让最后一个字符 $+1$，然后如果发现字符等于 `a`$+k$  就将这一位置为 `a`，然后进位到前一位。

如果直接暴力维护所有的长度，显然不能通过。

我们考虑用一个栈维护不是 `a` 的位置。这样的位置显然最多只有 $O(n)$ 个。然后每次进位也就只需要暴力进位，因为进位次数显然不超过 $n$ 次。

如果发现第一个位置产生了进位，那么这个 $k$ 就一定不合法。反之，如果进行到最后，没有产生进位，那么这个 $k$ 就合法。简单判断就行了。

$\rm Code$：

```cpp
struct Node {
	int v, c;

	Node() {}
	Node(int v, int c):v(v), c(c) {}
};

int n;
int top;
int a[200010];
Node sta[200010];

inline void insert(int v, int x) {
	while(sta[top].v > v) --top;
	if(sta[top].v == v) sta[top].c++;
	else sta[++top] = Node(v, 1);
	if(top > 1 && sta[top].c == x) --top, insert(v - 1, x);
}

inline int chk(int x) {
	sta[top = 1] = Node(0, 0);
	for(int i = 2; i <= n; i++)
		if(a[i] <= a[i - 1]) insert(a[i], x);
	return sta[1].c == 0;
}

int main() {
	n = ri;
	for(int i = 1; i <= n; i++) a[i] = ri;

	int ct = 0;
	for(int i = 2; i <= n; i++) ct += a[i] > a[i - 1];
	if(ct == n - 1) return puts("1"), 0;
    
	int l = 2, r = n, res = 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(chk(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	} printf("%d\n", res);
	return 0;
}
```

---

## 作者：Martian148 (赞：5)

### link

[[AGC029C] Lexicographic constraints](https://www.luogu.com.cn/problem/AT4502)

按顺序给你一些字符串的的长度，分别为S1,S2,S3....,Sn，要你构造一个最小的字符集使得你可以用这一个字符集表示出这n个字符串并且 使得这些字符串是按照字典序从小到大依次排列的。

### solve

我们发现直接构造很难，如果我们知道答案再来验证就很简单了。

通过观察，这道题是满足二分性质的，于是考虑二分答案。

我们可以把串看成是 $N$ 进制的数，对于 $a[i]>a[i-1]$ 只需要在前面放 $0$ 就好了，对于 $a[i]≤a[i-1]$ ,我们需要找到长度小于等于 $a[i]$ 的串，然后在后面 $+1$ 就好了，其中模拟的过程可以用 $map$ 来实现。

### code

```cpp
#include<cstdio>
#include<map>
using namespace std;
const int maxn=2e5+5;
int N,a[maxn],ans,F=0;
map<int,int> mp;
bool check(int up){
	mp.clear();
	for(int i=2;i<=N;i++)if(a[i-1]>=a[i]){
		while(!mp.empty()){
			int t=mp.rbegin()->first;
			if(t>a[i]) mp.erase(t);
			else break;
		}
		int j=a[i];
		while(mp[j]+1==up) mp.erase(j),j--;
		if(j==0)return false;
		mp[j]++;
	}
	return true;
}
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
//	freopen("AT4434.in","r",stdin);
//	freopen("AT4434.out","w",stdout);
	N=read();
	for(int i=1;i<=N;i++)a[i]=read(),F|=(a[i]<=a[i-1]);
	if(!F)return printf("1\n"),0;
	int L=2,R=N;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid))ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xht (赞：3)

## [Lexicographic constraints](https://atcoder.jp/contests/agc029/tasks/agc029_c)

### 题意

- 有 $n$ 个字符串 $s_{1\dots n}$，对于 $i \in [1,n-1]$，满足 $s_i < s_{i+1}$。
- 现在你不知道 $s_{1\dots n}$，但你知道 $s_i$ 的长度为 $a_i$。
- 求最小的字符集大小，可以构造出合法的 $s_{1\dots n}$。
- $n \le 2 \times 10^5$，$a_i \le 10^9$。

### 题解

显然答案具有可二分性，先二分答案。

如果 $a_i > a_{i-1}$，则就是在 $s_{i-1}$ 的基础上后面加一堆 $a_i - a_{i-1}$ 个 $1$；否则，就是砍掉 $s_{i-1}$ 中 $> a_i$ 的部分然后 $+1$。

用栈维护 $s$ 中的每个相同字符连续段以及 $+1$ 操作，根据势能分析复杂度为 $\mathcal O(n)$。

总时间复杂度 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 2e5 + 7, M = 31;
int n, a[N], p[N], c[N], s[N], t;

inline void add(int x, int k) {
	if (x == p[t]) c[t] += k, s[t] += k;
	else p[++t] = x, c[t] = k, s[t] = c[t] + s[t-1];
}

inline bool add1(int m) {
	if (t == 1 && p[t] == m) return 0;
	if (p[t] != m) {
		if (c[t] == 1) --t, add(p[t+1] + 1, 1);
		else --c[t], --s[t], add(p[t] + 1, 1);
	} else {
		int k = c[t--];
		if (c[t] == 1) --t, add(p[t+1] + 1, 1);
		else --c[t], --s[t], add(p[t] + 1, 1);
		add(1, k);
	}
	return 1;
}

inline bool pd(int m) {
	t = 0, add(1, a[1]);
	for (int i = 2; i <= n; i++)
		if (a[i] > a[i-1]) add(1, a[i] - a[i-1]);
		else {
			while (s[t] > a[i]) --t;
			if (s[t] < a[i]) add(p[t+1], a[i] - s[t]);
			if (!add1(m)) return 0;
		}
	return 1;
}

int main() {
	rd(n), rda(a, n);
	int l = 1, r = n;
	while (l < r) {
		int d = (l + r) >> 1;
		if (pd(d)) r = d;
		else l = d + 1;
	}
	print(l);
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

首先二分答案转化为合法性判定问题。接下来我们尝试构造合法解。

如果字符集大小为 $mid$，我们可以将字符串看成一个 $mid$ 进制的数字。从 $a_{i-1}$ 代表的字符串到 $a_i$ 代表的字符串中，分类讨论：

- $a_{i-1}<a_i$，只需要在最后面补字符 `a` 即可。在进制数层面就是在最后补上若干个 0。

- $a_{i-1}\ge a_i$，那么我们就必须要在前面 $a_i$ 位就要比 $a_{i-1}$ 的字符串大。首先缩减长度，将字符串缩成 $a_i$ 位。如果把字符串看成进制数，那么接下来就在它的最后一位加一。如果发现进位到了首位还得再进一次，那么就是不合法的。

注意特判一下 $mid=1$ 的情况。利用 map 暴力模拟缩减和进位过程，时间复杂度 $O(n\log^2n)$。线段树也可以用类似的方法实现。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,a[Maxn+5];

inline int Check(int mid)
{
    map<int,int> mp; int l=0; mp[1]=0;
    For(i,1,n)
    {
        if(l<a[i]) l=a[i];
        else
        {
            if(mid==1) return 0;
            for(auto it=prev(mp.end());;it--)
            {
                if(it==mp.begin()) break;
                if(it->first>a[i]) it=mp.erase(it);
                else break;
            }
            int it=a[i]; l=a[i],mp[l]++;
            while(mp[it]==mid)
            {
                if(it==1) return 0;
                mp[it]=0,mp[it-1]++,it--;
            }
        }
    }
    return 1;
}

int main()
{
    n=read();
    For(i,1,n) a[i]=read();
    int l=1,r=n;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(Check(mid)) r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
    return 0;
}
```

---

## 作者：_maze (赞：0)

- 首先随便想个暴力，对于 $a_i > a_{i -1}$，我们直接往字符串的末尾加上一些最小的字符。对于 $a_i \le a_{i - 1}$，我们保留前缀之后随便加一个位置的 $1$。

- 发现这个随便的位置不是很好找，于是想到用二分**转枚举为判断**。二分最大的字符（可以转化为数字）$x$，每次我们只往最后一位加一，这相当于在 $x$ 进制下做一个加法。

- 注意二分的判断错误的条件，当第一位产生进位时，前面已经没有位置了，于是无解。

- 注意到 $a_i$ 很大，直接做加法会炸。我们不妨**去除重复状态**，只记录不为 $0$ 的数，如果这些数中没有加一的数就添一个数进来。这样由于每次最多添一个数，所以空间复杂度为 $O(n)$。时间复杂度为 $O(n\log n)$。这里的 $\log$ 来自二分。

- 实现的细节写在代码里了。

```cpp
/*
教学局，必拿下
更新分三步走：删后缀，进位，加数。
于是我们需要一个支持查询，删除，加入，更改值，下标还很大的东西。很容易想到 map。
将 map 的 first 作位，second 存值，直接更新即可。
注意到只有当 a[i]>=a[i-1] 时才会更新，所以把超过的后缀删掉这一步可以直接从最后开始删。因为里面加入的元素 first 递增。
这样理论复杂度会上升一个 log，应该还是能过的，但我被卡了 －_－b
注意到上上行的发现，想到用栈代替 map，果然快的一批
*/

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;
const long long N = 2e5+5, mod = 998244353;

int n;
int a[N];

#define id first
#define w second
bool check(int x) {
	stack<pair<int, int>> sta;
	for (int i = 2; i <= n; ++i) 
		if (a[i] <= a[i - 1]) {
            while (!sta.empty()) {
                int l = sta.top().id;
                if (l > a[i]) sta.pop();
                else break;
            }
            int l = a[i];
            while (((!sta.empty() && sta.top().id == l && sta.top().w + 1 == x) || x == 1) && l > 0) {
				if (!sta.empty()) sta.pop();
				--l;
			} 
            if (l == 0) 
				return false;
			int val = 0;
			if (!sta.empty() && sta.top().id == l) val = sta.top().w;
			++val;
			if (!sta.empty() && sta.top().id == l) sta.pop();
			sta.push(make_pair(l, val));
		}
	return true;
}
#undef id
#undef w

signed main(){
	freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	int l = 1, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid) == true) r = mid;
		else l = mid + 1;
	}

    cout << l << endl;
	
	return 0;
}
```

---

