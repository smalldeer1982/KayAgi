# Divide and Equalize

## 题目描述

### 题目大意
给你一个包含 $n$ 个正整数的数组 $a$，你可以进行以下操作：
1. 选两个数$a_i$和$a_j$ （$1 ＜ i, j \le n$且$i \ne j$）
2. 选择$a_i$的一个因数$x$
3. 将$a_i$替换为$\frac{a_i}{x}$，$a_j$替换为$a_j \cdot x$

请判断是否能通过有限次操作使 $a$ 中所有元素相同（可以是$0$次）。

例如：

$a=[100,2,50,10,1]$共$5$个数，那么进行以下两次操作：
1. 选择$a_3=50,a_2=2,x=5$，则$a_3=\frac{a_3}{x}=\frac{50}{5}=10,a_2=2\cdot5=10$，$a$变为$[100,10,10,10,1]$
2. 选择$a_1=100,a_5=1,x=10$，则$a_3=\frac{a_1}{x}=\frac{100}{10}=10,a_2=1\cdot10=10$，$a$变为$[10,10,10,10,10]$

经过以上操作后，$a$里面的元素都变成了$10$

## 说明/提示

第一组样例数据已在“题目大意”中有解释。

## 样例 #1

### 输入

```
7
5
100 2 50 10 1
3
1 1 1
4
8 2 4 2
4
30 50 27 20
2
75 40
2
4 4
3
2 3 1```

### 输出

```
YES
YES
NO
YES
NO
YES
NO```

# 题解

## 作者：Unstalian (赞：6)


# Divide and Equalize

### 题目大意：

给你一个由 $n$ 个正整数组成的数组 $a$ 。你可以对它进行以下操作：

1.  选择一对元素 $a_i$ 和 $a_j$ 
2.  选择整数 $a_i$ 的除数之一，即整数 $x$ ，使得 $a_i \mod x = 0$ 
3.	用 $\frac{a_i}{x}$ 代替 $a_i$ ，用 $a_j \cdot x$ 代替 $a_j$ 

多次操作后，使得所有元素相同

### 分析：
显然这是一道数论题，我们观察到，无论怎么进行操作，总数的积**不变**；

那么操作的本质就是质因数的分解和重新分配，只需让相同**质因数**的个数是 $n$ 的倍数，就可以平均分配。

### 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
int a[maxn];
map<int,int>q;//使用map进行快速的访问
void check(int x)//质因数分解
{
	for (int i = 2;i <= sqrt(x);i ++)
	{
		while(x % i == 0)
		{
			q[i] ++;
			x /= i;
		}
	}
	if(x > 1) q[x] ++;
}
void solve()
{
	int n;
	cin >> n;
	q.clear();
	for (int i = 1;i <= n;i ++)
	{
		scanf("%d",&a[i]);
		check(a[i]);
	}
	for (auto i:q)
	{
//		cout << cnt[i]<<endl;
		int k = i.second;
		if(k % n != 0)
		{
			cout << "NO"<<endl;
			return;
		}
	}
	cout << "YES"<<endl;
	return;
}
int main()
{
	int T = 0;
	cin >> T;
	while (T --)
	{
		solve();
	}
}
```
###### 蒟蒻头回发题解，审核大大下手轻点QWQ


---

## 作者：linxuanrui (赞：1)

### 思路

不难发现，题目中的一次操作并不会改变所有数乘起来的积。

设所有数的积为 $sum$，那么假如 $\sqrt[n]{sum}$ 为整数，最后就可以满足。

令 $sum=\prod\limits_{i=1}^x{p_i}^{a_i}$，其中 $p_i$ 是互不相同的质数，$a_i$ 是整数。

此时，$\sqrt[n]{sum}=\prod\limits_{i=1}^x{p_i}^{a_i\div n}$。也就说明，当 $\forall 1\le i\le x\ a_i\bmod n=0$ 时，题目有解。

我用了欧拉筛来分解质因数，最后检查每个质因数的个数是否都是 $n$ 的倍数即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
int T,n,a[10005],t[1000005],len,minp[1000005],num[100005],tmp[10005],maxx;
bool prime[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	memset(prime,true,sizeof(prime));
	for(int i = 2;i <= 1000000;i++){
		if(prime[i])t[++len] = i,minp[i] = len;
		for(int j = 1;j <= len && t[j] * i <= 1000000;j++){
			prime[t[j] * i] = false;
			minp[t[j] * i] = min(minp[t[j]],minp[i]);
			if(i % t[j] == 0)break;
		}
	}
	while(T--){
		cin >> n;
		maxx = 0;
		int mul = 1;
		memset(num,0,sizeof(int) * (len + 1));
		for(int i = 1;i <= n;i++){
			cin >> a[i];
			maxx = max(maxx,a[i]);
			tmp[i] = a[i];
			while(tmp[i] != 1){
				num[minp[tmp[i]]]++;
				tmp[i] /= t[minp[tmp[i]]];
			}
		}
		bool flag = true;
		for(int i = 1;i <= len;i++){
			if(t[i] > maxx)break;
			flag &= (num[i] % n == 0);
		}
		cout << (flag ? "YES\n" : "NO\n");
	}
}
```

---

## 作者：haokee (赞：0)

## 题目大意

有 $n$ 个元素，第 $i$ 个元素的值是 $a_i$。对于任意一对 $(i,j)$ $(1\le i,j\le n)$，你可以选择一个整数 $x$，将 $a_i$ 乘上 $x$，将 $a_j$ 除以 $x$，最后使得所有的元素都是一个值。问你可不可以完成这个操作。

## 思路

首先找规律，我们可以发现将 $a_i$ 分解质因数后，若每一种质因子的数量都是 $n$ 的倍数的话，那么就代表可以化为同一个元素。因为如果是 $n$ 的倍数的话，那么这个质因子就可以互相传递，那么假设数量为 $s$，每一个元素就得到了 $n\div s$，就可以达到判断是否能够达到同一个元素的效果。

现在我们就需要快速分解质因数。假设我们需要分解 $x$，可以考虑分两种情况：

- $x$ 本身就是质数：直接把 $x$ 分离出来；
- $x$ 是合数：枚举 $x$ 的质因子，并直接进行分解。

然后我们使用一个 `map` 存下每一个质因子的数量，最后对 `map` 里面的值进行判断。

## 代码

```cpp
#include <iostream>
#include <map>

using namespace std;

const int kMaxN = 1e4 + 5;

int a[kMaxN], t, n;
map<int, int> f;

int main() {
  for (cin >> t; t; t--) {
    cin >> n, f.clear();
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 2; j * j <= a[i]; j++) {
        for (; a[i] % j == 0; a[i] /= j) {
          f[j]++;
        }
      }
      if (a[i] != 1) {
        f[a[i]]++;
      }
    }
    bool ans = 1;
    for (auto i : f) {
      ans &= i.second % n == 0;
    }
    cout << (ans ? "YES" : "NO") << '\n';
  }
  return 0;
}
```



---

## 作者：细数繁星 (赞：0)

[博客园体验更好！](https://www.cnblogs.com/2044-space-elevator/articles/17870885.html)

## 题目大意

每次操作任意选择三个正整数 $a_i$ ，$a_j$ 以及 $x$（$x\mid a_i$），将 $a_i$ 赋值为 $\frac{a_i}{x}$ 并将 $a_j$ 赋值为 $a_j\cdot x$。请问是否能通过若干次操作，使得 $a$ 数组任意两个数相等？

## 思路

首先我们得明白一个铁打不动的规则：就是无论你怎么操作，$a$ 数组的积不变，也就是说 $\prod_{i=1}^n a_i$ 的值是不变的。那么我们可以得出，答案就是：

$$
\sqrt[n]{\prod_{i=1}^n a_i} \in \mathbf{Z}
$$
是否为真，可是题目里 $a_i\le 10^6$，$n\le 10^4$，乘几下 `__int128` 就炸了，所以该方法行不通。

## 质因数是个好东西

我们将所有 $a_i$ 质因数分解：

$$
\sqrt[n]{\prod_{i=1}^k p_i^{c_i}}
$$
其中根号里的式子是 $a$ 的积的质因数分解形式。

所以现在就可以简化问题了，其实就是求：

$$
\forall n\mid c_i
$$
是真是否。那么现在要做的就简单了，我们只需要将所有 $a_i$ 质因数分解，将质因数的次数放入散列表里面映射，散列表里的值如果都能被 $n$ 整除，答案为真，否则为否。

代码很简单，我还用了我自己的模板，欢迎自取。

```cpp
// Problem: D. Divide and Equalize
// Contest: Codeforces - Codeforces Round 903 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1881/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Coding by 2044_space_elevator

#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
	map<int, int> primeMap;
	int n;
	cin >> n;
	rep(i, 1, n) {
		int x;
		cin >> x;
		rep(i, 2, sqrt(x)) {
			while (x % i == 0) {
				primeMap[i]++;
				x /= i;
			}
		}
		primeMap[x] += x > 1;
	}
	for (auto [trash, useful] : primeMap) {
		if (useful % n) {
			RTN
			return;
		}
	}
	RTY
	return;
}


int main() {
	int t; cin >> t; while (t--) solve();
	return 0;
}

```

---

## 作者：LHLeisus (赞：0)

[原题链接](https://codeforces.com/contest/1881/problem/D)

[更好的阅读体验](https://www.cnblogs.com/LHLeisus/p/17760984.html)

$a_i$ 和 $a_j$ 在操作前后的乘积是不变的，也就是总乘积是固定的。最后要求所有的元素相同，那也就是说所有元素的乘积 $total$ 一定满足 $\sqrt[n]{total}$ 是整数。看了看数据范围没有办法直接乘起来，于是考虑分解质因数，最后看一下每个质因子的个数是否是 $n$ 的倍数就可以了。

~~赛时代码，比较丑陋~~
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#include<map>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read();
typedef long long ll;
typedef double db;
const int N=1e4+5;
const int MAXN=1e6+5;
const int INF=0x3f3f3f3f;
int n,m,k;
int tot=0,prime[MAXN+5],cntp=0,isp[MAXN+5];
map<int,int>c;
void init(){
	FOR(i,1,MAXN) isp[i]=1;
	isp[1]=0;
	FOR(i,2,MAXN){
		if(isp[i]) prime[++cntp]=i;
		for(int j=1;j<=cntp&&i*prime[j]<=MAXN;j++){
			isp[i*prime[j]]=0;
			if(i%prime[j]==0) break;
		}
	}
}
int main()
{
	int T=read();
	init();
	while(T--){
		n=read();
		tot=0;
		c.clear();
		FOR(i,1,n){
			k=read();
			FOR(j,1,cntp){
				if(k==1) break;
				if(k%prime[j]==0){
					c[prime[j]]++;
					k/=prime[j];
					while(k%prime[j]==0&&k!=1) 
						c[prime[j]]++,k/=prime[j];
				}
			}
		}
		int f=0;
		for(auto v:c){
			if(v.se%n!=0){
				puts("NO");
				f=1;
				break;
			}
		}
		if(!f) puts("YES");
	}
	return 0;
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```

---

## 作者：_299817_ (赞：0)

## Part 0：前言
比赛一开始就先开的 D，十分钟想出来并打完了。

## Part 1：主要思路
不难发现，题目所作的操作就是我们可以将任意一个 $a_i$ 的因数从 $a_i$ 中拿出来并将其给到 $a_j$。

在这个过程中，不难发现， $\prod_{i = 1}^{i \le n} a_i$ 是不变的，而最后所有数相等的条件也就是所有数乘起来后开 $n$ 次根号后还是整数。

但是这里会出现一个问题，就是 $\prod_{i = 1}^{i \le n} a_i$ 会很大，但是我们可以发现题目给了一个条件就是 $a_i \le 10^6$ 于是我们可以分解 $a_i$ 的质因数，如果所有数的所有质因数的个数都是 $n$ 的倍数的话，那么就满足条件，否则就不满足条件。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#define rep(i, l, r) for(int i = signed(l); i <= signed(r); i++)
#define per(i, l, r) for(int i = signed(l); i >= signed(r); i--)
#define sort stable_sort
// #define map unordered_map
using namespace std;
typedef long long ll;

int T;
int n;
int a[200010];
map<int, int> mp; // 记录每个质因数的个数

void breakdown(int N) {
    for (int i = 2; i * i <= N; i++) {
        if (N % i == 0) {
            while (N % i == 0){
                N /= i;
                mp[i]++;
            }
        }
    }
    if (N != 1) {
        mp[N]++;
    }
} // 分解质因数


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        mp.clear();
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            breakdown(a[i]); // 对每个数分解质因数
        }
        bool flag = 1;
        for(auto it : mp){ // 遍历每个数，看是不是 n 的倍数
            if(it.second % n != 0){
                flag = 0;
                break;
            }
        }
        if(flag == 0){ // 输出答案
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
        }
    }
    return 0;
}
```

---

