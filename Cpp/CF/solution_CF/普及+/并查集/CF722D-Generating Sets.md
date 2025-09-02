# Generating Sets

## 题目描述

You are given a set $ Y $ of $ n $ distinct positive integers $ y_{1},y_{2},...,y_{n} $ .

Set $ X $ of $ n $ distinct positive integers $ x_{1},x_{2},...,x_{n} $ is said to generate set $ Y $ if one can transform $ X $ to $ Y $ by applying some number of the following two operation to integers in $ X $ :

1. Take any integer $ x_{i} $ and multiply it by two, i.e. replace $ x_{i} $ with $ 2·x_{i} $ .
2. Take any integer $ x_{i} $ , multiply it by two and add one, i.e. replace $ x_{i} $ with $ 2·x_{i}+1 $ .

Note that integers in $ X $ are not required to be distinct after each operation.

Two sets of distinct integers $ X $ and $ Y $ are equal if they are equal as sets. In other words, if we write elements of the sets in the array in the increasing order, these arrays would be equal.

Note, that any set of integers (or its permutation) generates itself.

You are given a set $ Y $ and have to find a set $ X $ that generates $ Y $ and the maximum element of $ X $ is mininum possible.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
4 5 2 3 1 
```

## 样例 #2

### 输入

```
6
15 14 3 13 1 12
```

### 输出

```
12 13 14 7 3 1 
```

## 样例 #3

### 输入

```
6
9 7 13 17 5 11
```

### 输出

```
4 5 2 6 3 1 
```

# 题解

## 作者：lgx57 (赞：1)

非常简单的贪心题目。

每一次找出最大的数，然后一直 $x \gets \lfloor \frac{x}{2}\rfloor$，直到集合中不存在 $x$，然后把 $x$ 插入到集合中。

当这样操作到 $x=0$ 时都无法插入，直接结束程序。

集合可以用 set 维护，时间复杂度：$O(n \log V)$，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'
#define pb push_back
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N=50005;
int a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	set<int> s;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		s.insert(a[i]);
	}
	while ("ljd loves xyq forever"){
		int x=(*(--s.end()));
		int num=x;
		while (x){
			if (!s.count(x)){
				s.erase(num);
				s.insert(x);
				break;
			}
			x>>=1;
		}
		if (x==0){
			s.insert(num);
			break;
		}
	}
	for (int x:s) cout<<x<<' ';
	return 0;
}
```

---

## 作者：Little_Cabbage (赞：1)

> 涉及知识点：`set`。

# 解题思路

每次让列表中最大的元素缩小两倍，保证答案最优。

如果当前的元素缩小成 $0$ 就直接跳出循环，输出这个序列。

由于序列需要支持插入、删除以及找最大值，所以这个序列可以用 `set` 来维护。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
#define db double
#define ldb long double
#define vo void
#define endl '\n'
#define il inline
#define re register
#define ve vector
#define p_q priority_queue
#define PII pair<int, int>
using namespace std;

//#define O2 1
#ifdef O2
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#endif

namespace OI {
	template <typename T>
	il T read() {
		T x = 0, f = 1;
		int ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template <typename TE>
	il void write(TE x) {
		if (x < 0) {
			x = -x;
			putchar('-');
		}
		TE sta[35];
		int top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) putchar(sta[--top] + '0');
	}
	il string read_with_string() {
		string s = "";
		char ch = getchar();
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
			s += ch;
			ch = getchar();
		}
		return s;
	}
	il void write_with_string(string s) {
		for (int i = 0; i < s.size(); i ++ ) putchar(s[i]);
	}
}
namespace COMB {
	int fact[200000];
	int Triangle[1010][1010];
	void Fact(int n, int mod) {
		fact[0] = 1;
		for (int i = 1; i <= n; i ++ ) fact[i] = ((fact[i - 1]) % mod * (i % mod)) % mod;
	}
	void Pascal_s_triangle(int n, int mod) {
		for (int i = 0; i <= n; i ++ ) Triangle[i][0] = 1;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= i; j ++ )
				Triangle[i][j] = (Triangle[i - 1][j] + Triangle[i - 1][j - 1]) % mod;
	}
	int pw(int x, int y, int mod) {
		int res = 1;
		while (y) {
			if (y & 1) res = ((res % mod) * (x % mod)) % mod;
			x = (x % mod) * (x % mod) % mod;
			y >>= 1;
		}
		return res;
	}
	int pw(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res *= x;
			x *= x;
			y >>= 1;
		}
	}
	int GCD(int x, int y, int mod) {
		return __gcd(x, y) % mod;
	}
	int LCM(int x, int y, int mod) {
		return (((x % mod) * (y % mod)) % mod / (GCD(x, y, mod) % mod)) % mod;
	}
	int C(int n, int m, int mod) {
		if (m > n || m < 0) return 0;
		return fact[n] * pw(fact[m], mod - 2, mod) % mod * pw(fact[n - m], mod - 2, mod) % mod;
	}
	int Ask_triangle(int x, int y) {
		return Triangle[x][y];
	}
}
using namespace OI;
using namespace COMB;

//#define fre 1
#define IOS 1
//#define multitest 1

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;

int n;
int a[N];
set<int> s;

il void Init() {
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
}

il void Solve() {
	for (int i = 1; i <= n; i ++ ) s.insert(a[i]);
	while (1) {
		int x = *(--s.end());
		int old = x;
		while (x && s.count(x)) x >>= 1;
		if (!x) break;
		s.erase(old);
		s.insert(x);
	}
	while (!s.empty()) {
		cout << *(--s.end()) << " ";
		s.erase(--s.end());
	}
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

---

## 作者：仗剑_天涯 (赞：1)

翻译：找一个大小为n的集合x，使得集合y中的元素都可以由集合x进行或得到，可以操作由操作得来的元素，求最大元素最小的集合x 。

算法：贪心

贪心思路：每次取出最大的数字，不断除以2，如果没有重复元素的话就结束并且放回集合里面，一直这样操作直到最大的数字无法变化为止。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[50010];
set<int> tree;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		tree.insert(a[i]);
	}
	while(1)
	{
        set<int>::iterator i=tree.end();
        i--;
        t=*i;
        while(tree.find(t)!=tree.end()&&t)
        {
            t>>=1;
        }
        if(t==0) break;
        tree.erase(i);
        tree.insert(t);
	}
    for(set<int>::iterator i=tree.begin();i!=tree.end();i++)
    {
        cout<<*i<<' ';
    }
} 
```
[原文地址](https://blog.csdn.net/ddmxynl793173/article/details/102021782)

---

## 作者：hgcnxn (赞：0)

## CF722D Generating Sets题解

### 思路

考虑将操作过程倒过来，在 $setY$ 中对任意 $y_i$ 进行多个除以 $2$ 的操作得到 $setX$。

我们对这个过程进行贪心。每一次操作选取最大的数，不断进行除以 $2$ 的操作使其变的尽量小。如果无法继续进行操作，就输出当前集合。这可以用集合维实现。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a,i;
set<int>s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	while(n--){
		cin>>a;
		s.insert(a);
	}
	while(1){
        i=*(--s.end());
        k=i;
        while(s.find(k)!=s.end()&&k)k>>=1;
        if(k==0)break;
        s.insert(k);
		s.erase(i);
	}
    for(int i:s)cout<<i<<" ";
    return 0;
}
```

---

## 作者：fire_hmz (赞：0)

本题思路:

可以用 priority_queue 存储所有数据，把最大的一直往下除，直到除不下去为止并输出。

code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> pq;
unordered_map<int, bool> v;
signed main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		v[x] = 1;
		pq.push(x);
	}
	while (1) {
		int mx = pq.top();
		while (mx >= 1 && v[mx]) {
			mx /= 2;
		}
		if (mx == 0) {
			break;
		}
		int qq = pq.top();
		pq.pop();
		v[qq] = 0;
		v[mx] = 1;
		pq.push(mx);
	}
	while (pq.size()) {
		cout << pq.top() << ' ';
		pq.pop();
	}
	return 0;
}
```

---

## 作者：d909RCA (赞：0)

### 0x00 前言

~~建议降黄。~~

---
### 0x01 前置芝士

- set

---
### 0x02 核心思路

将 set 最大元素尽量缩小两倍，但是不能到 $0$，如果到了 $0$ 就说明缩到最小了，就直接输出 set 就可以继续向下缩。

---
### 0x03 Code

```
#include <bits/stdc++.h>
using namespace std;
int a[50009],n,m,cnt;
set<int> k;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		k.insert(a[i]);
	}
	while(1)
	{
		int x=*(--k.end());
		int l=x;
		while(x&&k.count(x))
		{
			x=x>>1;
		}
		if(x==0) break ;
		k.erase(l);
		k.insert(x);
	}
	while(!k.empty())
	{
		cout<<*(--k.end())<<' ';
		k.erase(*(--k.end()));
	}
	cout<<'\n';
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

简单的题目配对简单的题解。
- 算法：贪心。
- 不断用取出的最大数除以 $2$，直到最大数无法变化。

简单的代码：
```c
set<int>::iterator i=tree.end();
        i--;t=*i;
        while(tree.find(t)!=tree.end()&&t)t>>=1;
        if(t==0) break;
        tree.xxx(i);
        tree.xxxx(t);
```

---

