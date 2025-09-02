# [ABC272E] Add and Mex

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc272/tasks/abc272_e

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。

以下の操作を $ M $ 回行ってください。

- 各 $ i\ (1\leq\ i\ \leq\ N) $ について、 $ A_i $ に $ i $ を加算する。その後 $ A $ に含まれない最小の非負整数を求める。

## 说明/提示

### 制約

- $ 1\leq\ N,M\ \leq\ 2\times\ 10^5 $
- $ -10^9\leq\ A_i\leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ 1 $ 回目の操作では、数列 $ A $ は $ (-1\ +\ 1,\ -1\ +2\ ,-6+3)\ =\ (0,1,-3) $ になります。 $ A $ に含まれない最小の非負整数は $ 2 $ です。 $ 2 $ 回目の操作では、数列 $ A $ は $ (0\ +\ 1,\ 1\ +2\ ,-3+3)\ =\ (1,3,0) $ になります。 $ A $ に含まれない最小の非負整数は $ 2 $ です。 $ 3 $ 回目の操作では、数列 $ A $ は $ (1\ +\ 1,\ 3\ +2\ ,0+3)\ =\ (2,5,3) $ になります。 $ A $ に含まれない最小の非負整数は $ 0 $ です。

## 样例 #1

### 输入

```
3 3
-1 -1 -6```

### 输出

```
2
2
0```

## 样例 #2

### 输入

```
5 6
-2 -2 -5 -7 -15```

### 输出

```
1
3
2
0
0
0```

# 题解

## 作者：linxuanrui (赞：4)

模拟赛打的题目。想了挺久才想出来。

显然，$a$ 的 $\operatorname{mex}$ 始终都在 $[0,n]$ 的范围内。因此，当 $a_i$ 不满足 $0\le a_i\le m$ 时，对整个序列的 $\operatorname{mex}$ 就没有贡献，就不必计算。

时间复杂度分析：

因为 $a_i$ 对 $\operatorname{mex}$ 有贡献的次数肯定不超过 $\dfrac{n}{i}$，所以总的时间复杂度就是 $\mathcal{O}(\sum\limits_{i=1}^n\dfrac{n}{i})$，化简可得 $\mathcal{O}(n\times H_n)$，（其中 $H$ 为调和级数 $\dfrac{1}{1}+\dfrac{1}{2}+\cdots+\cdots+\dfrac{1}{n}$，约为 $\log n$）。因此，最后的时间复杂度就是 $\mathcal{O}(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,m,a[N],lst1,lst2;
vector<int> v[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    for(int i = 1;i <= n;i++){
        lst1 = (a[i] >= 0 ? 0ll : (-a[i] + i - 1) / i),lst2 = max((n - a[i]) / i,0ll);
        for(int j = max(lst1,0ll);j <= lst2 && j <= m;j++){
            v[j].push_back(a[i] + j * i);
        }
    }
    for(int i = 1;i <= m;i++){
		sort(v[i].begin(),v[i].end());
		int now = 0;
        for(int j = 0;j < v[i].size();j++){
            if(v[i][j] == now){
                now++;
            }
        }
        cout << now << endl;
    }
}
```

---

## 作者：Register_int (赞：2)

正解很离谱，就是暴力……  
对于序列中的每一个数，当他被操作到数值 $\ge n$ 时，就对数列的 $\operatorname{mex}$ 没有任何贡献了。另外，负数对于序列也没有贡献。所以，有用的状态实际上就只有 $O(n+\dfrac n2+\dfrac n3+\cdots+1)=O(n\ln n)$ 种。暴力记录状态即可。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m, a[MAXN];

vector<int> v[MAXN];

bool vis[MAXN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		int k = max((-a[i] - 1) / i, 0) + 1; a[i] += k * i;
		for (int j = k; j <= m; j++) {
			if (a[i] >= n) break;
			v[j].push_back(a[i]), a[i] += i;
		}
	}
	for (int i = 1, p; i <= m; i++) {
		for (auto x : v[i]) vis[x] = 1;
		for (int j = 0; j <= n; j++) {
			if (!vis[j]) { p = j; break; }
		}
		for (auto x : v[i]) vis[x] = 0;
		printf("%d\n", p);
	}
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

没脑子的题目。

对于一个长度为 $n$ 的序列 $A$，若对于所有的 $a_i$，都有 $a_i\ge 0$，则这个序列的 mex 是在 $[0,n]$ 的。

打暴力预处理就行了。对于每一个 $i$，找到第一个 $j$，使得 $a_i+i\times j\ge 0$。然后从 $j$ 枚举到 $m$，如果中途的 $a_i$ 加起来的值增长到超过 $n$，则没有继续下去的意义了，退出枚举。这玩意的复杂度是 $O(\frac{n}{1}+\frac{n}{2}+\dots+\frac{n}{n})$ 的，大约 $O(n \log n)$。

暴力预处理完了就暴力找答案，复杂度和预处理一样。

注：模拟赛赛时找 $j$ 的时候用的二分，标记数组用的 map，复杂度可能比上面分析的大一些。（但是赛时的时候把 $\frac{n}{1}+\frac{n}{2}+\dots+\frac{n}{n}$ 算成 $n^2$ 了……）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=3e5+10;
int n,m,a[N];
map<int,int> vis[N];

il void solve(){
	cin>>n>>m;
	for(re int i=1;i<=n;++i) cin>>a[i];
	for(re int i=1;i<=n;++i){
		int l=1,r=m,tim=m+1;
		while(l<=r){
			int mid=l+r>>1;
			if(a[i]+mid*i>=0) tim=mid,r=mid-1;
			else l=mid+1;
		}
		a[i]+=(tim-1)*i;
		for(;tim<=m;++tim){
			a[i]+=i;if(a[i]>n) break;
			vis[tim][a[i]]=1;
		}
	}
	for(re int i=1;i<=m;++i)
		for(re int j=0;j<=n;++j)
			if(!vis[i][j]){cout<<j<<"\n";break;}
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：lsj2009 (赞：1)

### Problem

link-><https://atcoder.jp/contests/abc272/tasks/abc272_e>。

### Solution

容易发现，每次计算答案时，当时为负数的值是不会用到的，所以我们可以记录下每个元素第一次变成非负数的操作数哪次，记为 $l_i$，具体计算方法是解不等式 $l_i\cdot i+a_i\ge 0$，需要注意 $a_i$ 本身就为非负数的情况。

然后给出一个引理：每一次操作中大于 $n$ 的值是不用计算的。分两类讨论：第一种，那一轮没有数从负数变为非负数，而由于每个数都会变化，所以答案一定为 $0$，而 $0<n$；第二种，那一轮存在数从负数变为非负数，则考虑鸽巢原理，那次变换后，前几个小的数的值依次为 $0,1,2,\dots$。我们考虑构造出这样的情况，首先因为原来已经是非负数的每个数都已经发生变化，所以类似于 $0$ 的值一定会空缺出来，而由新晋的非负数顶替，而新晋的非负数值最大为 $-1+n=n-1$，所以答案一定在 $[0,n]$ 之间，我们无需理会大于 $n$ 的值。

所以我们可以记录下每个元素第一次变成大于 $n$ 的操作数哪次，记为 $r_i$，具体计算方法是解不等式 $r_i\cdot i+a_i>\le n$，需要注意 $a_i$ 本身就大于 $n$ 的情况。

则我们把每个 $a_i+ix,l_i\le x\le r_i$  加入序列 $\alpha_x$ 中。可以证明，$\sum\limits_{i=1}^m |\alpha_i|$ 渐进于 $O(n\log n)$，因为调和数 $\sum\limits_{i=1}^n r_i-l_i+1$ 最大为 $\sum\limits_{i=1}^n \frac{n}{i}$。

所以复杂度为 $O(n\log n)$。

### Code

``` cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define int long long
#define PII pair<int,int>
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5;
int n,m;
vector<int> vec[N];
signed main() {
	scanf("%lld%lld",&n,&m);
	rep(i,1,n) {
		int x;
		scanf("%lld",&x);
		int l=min(m+1,(int)ceil(-1.0*x/i)),r=min(m,(int)floor(1.0*(n-x)/i)+2);
		if(x>=0)
			l=1;
		if(x>n)
			r=0;
//		printf("(%lld,%lld) : [%lld,%lld]\n",i,x,l,r);
		rep(j,l,r)
			vec[j].push_back(x+j*i);
	}
	rep(i,1,m) {
		sort(vec[i].begin(),vec[i].end());
		int last=-1,len=vec[i].size();
		rep(j,0,len-1) {
			if(vec[i][j]==last+1)
				++last;
			else if(vec[i][j]!=last)
				break;
		}
		printf("%lld\n",last+1);
	}
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## [ABC272E] Add and Mex 题解

### 思路分析

显然，我们有一个 $O(nm)$ 的暴力。

显然，也过不去。

但是对于每一个数 $x$，只有 $x \in [0, n - 1]$ 的时候才会对答案产生贡献。

- $x < 0$，显然，这和 $\operatorname{mex}$ 无关。
- $x > n - 1$，显然，即使前面的 $n - 1$ 个数全部产生贡献，仍然缺少 $n - 1$ 这个数，再大也没有贡献了。

然后我们就有了一个看起来还是很暴力的做法：对于每一个数计算其产生贡献的区间，只在这个区间里统计他的贡献。

但是分析可得，这个做法的复杂度是正确的。

显然，对于 $i \in [1, n]$，第 $i$ 个数在**有可能**产生贡献的区间的长度是 $\lfloor \dfrac{n}{i}\rfloor$。

即：$\sum_{i = 1}^{n} \dfrac{n}{i} = n \times H_{i} = n \ln n$（其中 $H$ 为调和级数，$H_n$ 约为 $n \ln n$）。

显然，区间只有这么多，时间复杂度不可能高于这个。

然后再使用 `set` 维护所有询问可能有贡献的数，最后直接扫一遍算出来即可。

总的时间复杂度为：$O(n \ln n \log n) \approx O(5 \times 10 ^ 7)$，可通过此题。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <set>
constexpr int MaxN = 2e5 + 5;
int n, m;
int p[MaxN];
std::set<int> set[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        set[i].insert(0x3f3f3f3f);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        int l, r;
        if (p[i] >= 0)
        {
            l = 1;
        }
        else
        {
            l = (-p[i] + i - 1) / i;
        }
        r = std::min(m, (n - p[i] + i - 1) / i);
        for (int j = l; j <= r; j++)
        {
            set[j].insert(i * j + p[i]);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int cnt = 0;
        for (auto val : set[i])
        {
            if (cnt != val)
            {
                printf("%d\n", cnt);
                break;
            }
            cnt++;
        }
    }
    return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

首先因为有 $n$ 个数，那么这个数列的 $\mathrm{mex}$ 一定是 $\in [0,n]$ 的，因为 $n$ 个数肯定不能覆盖一个长度为 $n+1$ 的区间对吧。

然后因为 $\mathrm{mex} \in [0, n]$，所以不在 $[0,n]$ 范围内的数无法对 $\mathrm{mex}$ 造成影响

那么可以考虑没有 $m$ 限制的时候，$a_i$ 大小就不受限制了，但是有一点就是，$a_i > n$ 时候再怎么样也没用了，所以 $a_i > n$ 时候直接退出。

不过因为 $a_i$ 有负数，而负数一直都是满足 $a_i \leq n$ 的，这个需要提前计算它使它变为一个非负数。

然后考虑一个非负数加加加直到超过 $n$ 的次数，从 $1 \sim n$ 分别是：$n,\frac{n}{2},\frac{n}{3},\ldots,\frac{n}{n-1},1$，由调和级数可得一共是 $n \ln n$ 次。

于是可以暴力算加几次时候所有 $\in [0,n]$ 的 $a_i$ 值，到时候对于每个 $j \in [1,m]$ 排个序算一下就行。

复杂度 $O(n \ln n \log n)$，可以通过。

```cpp
vector<int> g[201010];
void solve() {
	int n, m; read(n, m);
	for (int i = 1; i <= n; ++i) {
		int x = read();
		int cnt = 1; x += i; 
		if (x < 0) {
			cnt += (-x) / i;
			x += cnt * i - i;
		}
		if (x < 0) {
			++cnt; x += i;
		}
		for (;cnt <= m; ++cnt) {
			if (x > n) break;
			g[cnt].eb(x);
			x += i;
		}
	}
	for (int i = 1; i <= m; ++i) {
		sort(g[i].begin(), g[i].end());
		int len = g[i].size();
		for (int x = 0, y = 0; x <= n; ++x) {
			if (y >= len || g[i][y] != x) {
				write(x, '\n');
				break;
			}
			for (; y < len && g[i][y] == x; ++y) ;
		}
	}
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc272-e)

[洛谷原题传送门](/problem/at_abc272_e)

[AtCoder 原题传送门](https://atcoder.jp/contests/abc272/tasks/abc272_e)

给定一个长度为 $n$ 的数列 $a$ 和操作数 $m$。

每次操作对数组中的每个数字 $a_i\gets a_i+i$。

每次操作完后输出数组 $a$ 中最小的没有出现的**非负整数**。（下记这个值为 $\operatorname{mex}(a)$。）

# 分析
不难发现，一个长度为 $n$ 的数列的 $\operatorname{mex}(a)$ 的取值 $x$ 一定满足 $0\le x\le n$。

那么，如果数组中的一个值 $a_i >n$，就不可能对答案产生贡献。

同时，如果一个值 $a_i<0$，在 $a_i\ge0$ 前这个数也不会对答案产生贡献。

那么，一个数组中的数在最坏情况下会对答案产生几次贡献呢？

若数组一个长度为 $N$ 的数组 $a=\{1,2,3,\dots,N\}$，那么每个元素总共会对答案产生 $\dfrac{N}{1}+\dfrac{N}{2}+\dfrac{N}{3}+\dots+\dfrac{N}{N}=N\log_2 N$ 次贡献。

同时，每个元素对答案产生贡献的操作轮数也一定是一个**区间**。所以，这一部分代码不会超时。

那么，我们就可以预处理出每个元素对答案产生贡献的区间操作轮数，每次暴力找答案即可。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, m;
int a[MAXN], minn;
struct Node{
  int l, r;
} b[MAXN];
int finda(int x, int y){
  int l = 1, r = m + 1;
  while (l < r){
    long long mid = (l + r) >> 1;
    if (y + 1ll * mid * x >= 0){
      r = mid;
    }else {
      l = mid + 1;
    }
  }
  return l;
}
int findb(int x, int y){
  int l = 0, r = m;
  while (l < r){
    int mid = (l + r + 1) >> 1;
    if (y + 1ll * mid * x < n){
      l = mid;
    }else {
      r = mid - 1;
    }
  }
  return l;
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  set<int> c[MAXN];
  for (int i = 1; i <= n; i++){
    cin >> a[i];
    if (a[i] > n){
      b[i] = {0, 0};
      continue;
    }
    b[i].l = finda(i, a[i]);
    b[i].r = findb(i, a[i]);//使用二分查找合法区间。
    for (int j = b[i].l; j <= b[i].r; j++){
      c[j].insert(a[i] + i * j);//把对应操作轮数的值扔进 set 中。
    }
  }
  for (int i = 1; i <= m; i++){
    int cnt = 0;
    c[i].insert(n + 1);//插入极大值，避免答案不输出的情况。
    for (auto v : c[i]){//暴力找答案。
      if (v != cnt){
        cout << cnt << '\n';
        break;
      }
      cnt++;
    }
  }
  return 0;
} 
```

---

## 作者：Ferm_Tawn (赞：0)

首先，让我们考虑，给定长度为 $N$ 的序列 $A$ ，一个简单的问题是找到 $A$ 中不包含的最小非负整数。

显然，答案显然在 $0$ 和 $N$ 之间，因此我们可以忽略 $A$中的负元素和大于 $N$ 的元素，因为它不会影响答案。

基于这个观察，我们也可以解决原来的问题。如果我们不能忽略某个值，那么让我们称之为重要值。那么有多少个重要值？

当 $i = 1$ ， 有 $N$ 个重要值。

当 $i = 2$ ,  有 $\dfrac{N}{2}$ 个重要值。

以此类推，共有 $N \log N$ 个重要值。

故时间复杂度为 $O(N \log N)$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , x;
set<int> vec[200005];
int main(){
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++){
		cin >> x;
		int l = (x >= 0 ? 1 : (-x + i - 1) / i);
		while(l <= m && x + i * l <= n){
			vec[l].insert(x + i * l);
			l++;
		} 
	}
	for(int i = 1 ; i <= m ; i++){
		for(int j = 0 ; j <= n ; j++){
			if(!vec[i].count(j)){
				cout << j << endl;
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：Hanx16Kira (赞：0)

# [ABC272E] Add and Mex

[Luogu ABC272E](https://www.luogu.com.cn/problem/AT_abc272_e)

[Atcoder ABC272E](https://atcoder.jp/contests/abc272/tasks/abc272_e)

## Solution

此题中，$\text{mex}$ 有一个很好的性质，就是最后答案的 $\text{mex}$ 一定是在 $[0,n]$ 这个区间内的。这很好证明，因为将前 $n$ 个数依次放到 $[0,n-1]$ 的位置可以让 $\text{mex}$ 最大，而此时的 $\text{mex}$ 最大就是 $n$。因此可以考虑暴力枚举的做法。

对于数列中的每一个数，枚举可能在 $[0,n]$ 的范围的有多少种情况。很明显如果一个数每次操作的增量为 $\Delta x$ 的话，那么在 $[0,n]$ 中就有 $\displaystyle \frac{n}{\Delta x}$ 种情况。如果对于每一个数都这么求一遍的话，那么会发现总的次数其实就是调和级数 $\displaystyle \sum \limits_{i=1}^n \frac{n}{i}=\mathcal O(n\log n)$，因此时间复杂度是有保证的。

代码实现上，我用了 `set` 来维护每一轮生成出来的数。生成完后直接枚举每一个 `set` 中的元素来求 $\text{mex}$，时间均摊下来是 $\mathcal O(m\log n)$ 的，所以总时间复杂度是 $\mathcal (n+m)\log n$。

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof a)
//#define int long long
using namespace std;
template<typename T> void read(T &k)
{
	k=0;T flag=1;char b=getchar();
	while (!isdigit(b)) {flag=(b=='-')?-1:1;b=getchar();}
	while (isdigit(b)) {k=k*10+b-48;b=getchar();}
	k*=flag;
}
template<typename T> void write(T k) {if (k<0) {putchar('-'),write(-k);return;}if (k>9) write(k/10);putchar(k%10+48);}
template<typename T> void writewith(T k,char c) {write(k);putchar(c);}
set<int> s[200005];
int n,m;
int a[200005];
signed main()
{
	read(n),read(m);
	for (int i=1;i<=n;i++) read(a[i]);
	for (int i=1;i<=n;i++)
	{
		int st=ceil((0-a[i])*1.0/i); // 计算下界，上界为 m
		for (int j=max(st,1);j<=m;j++)
		{
			int curVal=a[i]+j*i;
			if (curVal>n) break; // 如果生成出来大于n就可以舍去了，因为不可能对答案产生贡献
			s[j].insert(curVal);
		}
	}
	for (int i=1;i<=m;i++)
	{
		int temp=-1;bool flag=0;
		for (auto it:s[i]) // 遍历set中的元素来求 mex
		{
			if (it-1>temp) {writewith(temp+1,'\n');flag=1;break;}
			temp=it;
		}
		if (!flag) writewith(temp+1,'\n');
	}
	return 0;
}
```

---

