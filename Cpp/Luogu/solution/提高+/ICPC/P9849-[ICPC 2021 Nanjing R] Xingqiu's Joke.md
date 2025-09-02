# [ICPC 2021 Nanjing R] Xingqiu's Joke

## 题目描述

有 $T$ 个盒子，每盒子上有一个锁，锁上有两个整数 $a$ 和 $b$。你可以对这个锁做若干次以下 3 种操作：

- $a$ 和 $b$ 分别减去 $1$
- $a$ 和 $b$ 分别增加 $1$
- $a$ 和 $b$ 分别除以它们共同的素数因子

如果 $a$ 或 $b$ 或两者都变为 $1$，盒子就会解锁。请你编写一个程序，计算每个盒子的锁打开的最少步骤数量。

## 样例 #1

### 输入

```
5
4 7
9 8
32 84
11 35
2 1
```

### 输出

```
2
7
5
4
0
```

# 题解

## 作者：CashCollectFactory (赞：5)

这一套 ICPC 的问题全是关于原神的诶，重云不可爱，但还是必须交一份题解来宠爱重云呢~

## 题目大意

给出两个正整数 $a,b$，每次可以进行三种操作：都加一，都减一和都除以一个它们共同的质数因子，判断最少多少次能使得其中一个数为 $1$。

## 题目分析

一眼看上去就是深度优先搜索吧？

总的来说，如果不进行除法操作，那么 $a$ 与 $b$ 的差值是固定的，如果存在一个数能够整除 $a$ 和 $b$，那么一定也能整除它们的差值，那么就可以将其差值进行质因子分解，将 $a$ 和 $b$ 中的较小数加或减到距离质因子最小的数，对 $a$，$b$ 及差值同时除质因子，以此反复即可，当无质因子时就只能一直减了。

如果只使用前两种操作，那么 $\delta = a - b$ 的值是不变的，而且 $a$ 和 $b$ 的公共质因数一定也是 $\delta$ 的质因数。而且当我们想除以一个质因数 $g$ 时，我们一定会先通过前两种操作来到最近的 $g|a$ 且 $g|b$ 的状态然后直接除 $g$ （先加减 $k$ ，再除 $g$ ，再加减 $1$ 肯定优于加减 $2k$ ）。



因此记 $f(a, \delta)$ 表示从 $(a, a + \delta)$ 得到 $1$ 的步数，枚举 $\delta$ 的质因数 $g$ ， $f(a, \delta)$ 可以由 $f(\lfloor\frac{a}{g}\rfloor, \frac{\delta}{g})$ 和 $f(\lceil\frac{a}{g}\rceil, \frac{\delta}{g})$ 转移得到。因此状态的第二维只有 $\delta$ 的因数个。



但状态的第一维如果和除以因数的顺序有关，那状态数又超了。但无需担心，实际上对于整数 $x$ 和 $a_1, a_2, \cdots, a_k$ ，$x$ 以任意顺序被 $a_i$ 进行整数除法（无论上取整或下取整），结果至多只有两种。因此总的状态数仍然是因数级别的。

通过以下方式完成证明：

若 $x$ 以任意顺序被 $a_i$ 进行下取整的整除得到的结果是 $k_1$ ，进行上取整的整除得到的结果是 $k_2$ ，那么

$k_1\prod\limits_{i=1}^n a_i \le x \le (k_1 + 1)\prod\limits_{i=1}^n a_i - 1$

$(k_2 - 1)\prod\limits_{i=1}^n a_i + 1 \le x \le k_2\prod\limits_{i=1}^n a_i$

该式可通过数学归纳法证明。

上面两个式子可以看作长度为 $(\prod\limits_{i=1}^n a_i - 1)$ 的两个区间，显然只有当 $k_2 + 1 = k_1$ 或 $k_2 = k_1$ 时两个区间才有交集。

由于以任意顺序进行全部上取整的整除得到的结果一定是最大的，进行全部下取整的整除得到的结果一定是最小的，那么上下整除混合得到的结果自然在两者中间。该性质得证。

## 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,a,b,t;
vector<int>v;
unordered_map<int,int>level;
int gethash(int b,int c) {//哈希
    return b*1e9+c;
}
int DFS(int b,int c) {
    if(b==1)return 0;
    if(c==1)return b-1;//差值为1，只能一直减
    if(level[gethash(b,c)])return level[gethash(b,c)];//记忆化搜索
    int mn=b-1;//至少需要的次数
    for(auto i:v)//遍历所有的质因子
        if(c%i==0) {//如果还没有除过
            int ans=b%i;//获得差距
            mn=min({mn,ans+1+DFS(b/i,c/i),i-ans+1+DFS(b/i+1,c/i)});
            //分别是b大于i的情况和b小于i的情况，+1是因为进行了一次除
        }
    return level[gethash(b,c)]=mn;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >>t;
    while(t--) {
        cin >>a>>b;
        if(a<b)swap(a,b);//强制b为小值
        int c=a-b;
        v.clear();
        for(int i=2; i<=c/i; i++)
            if(c%i==0) {//获得质因子
                v.push_back(i);
                while(c%i==0)c/=i;
            }
        if(c>1)v.push_back(c);//最后除剩的也是质因子
        cout <<DFS(b,a-b)<<endl;//记忆化搜索
    }
    return 0;
}
```

---

## 作者：WZwangchongming (赞：1)

重云行秋可爱捏！但是没有芙芙可爱！


---

Solution：

我们可以先不妨设 $a<b$。

假设下一次 $a$ 和 $b$ 共同的素数因子为 $p$，那么最佳策略肯定是通过操作一或者操作二将 $a$ 变成 $\lfloor \frac{a}{p} \rfloor p$。

操作一和操作二都不会改变 $b-a$ 的值，又因为 $p \mid b$ 且 $p \mid a$，所以 $p \mid (b-a)$ 即 $p$ 一定是 $b-a$ 的某个质因子。于是考虑记搜，状态定义为 $\text{dfs}(a,b-a)$。因为每次进行操作 $3$ 之后，$b-a$ 也会除 $p$，因此 $b-a$ 的状态数最多是对数级别的。记忆化，只枚举了质因子，每次 $a$ 会变成 $\lfloor \frac{a}{p} \rfloor$ 和 $\lceil \frac{a}{p} \rceil$，所以这样做的复杂度不大，通过本题绰绰有余。


---

Main code：

```cpp
map <pii, int> m;
int dfs(int now, int diff) {
	if(now == 1) return 0;
	if(f.count({now, diff})) return f[{now, diff}];
	int x = diff, ans = now - 1;
	for(int i = 2; i * i <= x; i++)
		if(x % i == 0) {
			int nxt = now / i * i;
			ans = min(ans, dfs(nxt / i, diff / i) + now - nxt + 1);
			nxt = (now + i - 1) / i * i;
			ans = min(ans, dfs(nxt / i, diff / i) + nxt - now + 1);
			while(x % i == 0) x /= i;
		}
	if(x > 1) {
		int nxt = now / x * x;
		ans = min(ans, dfs(nxt / x, diff / x) + now - nxt + 1);
		int nxt = now / x * x;
		ans = min(ans, dfs(nxt / x, diff / x) + nxt - now + 1);
	}
	return f[{now, diff}] = ans;
}
```

---

## 作者：gan_ge (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9849)


---

用动态规划理解一下：

我们先忽略点恶臭的操作三，只看操作一、二，这道题就变成了一道严格弱于红题的究极水题，我们只需要输出 $\min(a,b)-1$ 即可。

然后再看回操作三：$a$ 和 $b$ 分别除以它们共同的素数因子。

如果我们选择三号操作，我们有两种选择：

1.向下减至 $a$ 和 $b$ 共有某个素数因子；

2.向上加至 $a$ 和 $b$ 共有某个素数因子；

但我们如何选择素数因子呢？

这时我们可以回想起一个性质：$\forall{d\mid a,d\mid b}$，可证 $d\mid(a-b)$。

因此我们先处理出 $a,b$ 差值的所有质因子，然后在处理时枚举讨论。同时由于差值不会上升，我们只需记录 $a$（令 $a$ 为较小值）和差值，设计状态 $dp_{i,j}$ 表示在 $a$ 值为 $i$，差值为 $j$ 时打开盒子最小步数，状态转移方程为：

$dp_{i,j}=\min\lparen i-1,i\bmod k+1+dp_{\lfloor\frac{i}{k}\rfloor,\frac{j}{k}},k-i\bmod k+1+dp_{\lceil\frac{i}{k}\rceil,\frac{j}{k}}\rparen,\lparen k$ 为 $j$ 的质因子 $\rparen$

$i-1$ 为直接减下去的贡献。

$i\bmod k+1+dp_{\lfloor\frac{i}{k}\rfloor,\frac{j}{k}}$ 为向下减使得 $a$ 能整除 $k$ 的贡献。

$k-i\bmod k+1+dp_{\lceil\frac{i}{k}\rceil,\frac{j}{k}}$ 为向上加使得 $a$ 能整除 $k$ 的贡献。

由于差值的质因数很少，实际转移次数不多，时间能够保证。但 $a$ 的值和差值可能很大，所以不能用数组而用map。

附代码：
```
#include<bits/stdc++.h>
using namespace std;
vector<int> vec;
map<pair<int,int>,int> dp;
int solve(int a,int d){
    if(a==1) return 0;
    if(d==1) return a-1;
    if(dp[{a,d}]) return dp[{a,d}];
    int res=a-1;
    for(auto i:vec)
        if(d%i==0)
            res=min(res,min(a%i+1+solve(a/i,d/i),i-a%i+1+solve(a/i+1,d/i)));
    return dp[{a,d}]=res;
}
int T,a,b;
int main(){
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>T;
    while(T--){
        vec.clear(),dp.clear();
        cin>>a>>b;
        if(a>b) swap(a,b);
        int delt=b-a;
        for(int i=2;i*i<=delt;i++){
            if(delt%i==0){
                vec.push_back(i);
                while(delt%i==0) delt/=i;
            }
        }
        if(delt>1) vec.push_back(delt);
        cout<<solve(a,b-a)<<"\n";
    }
    return 0;
}
```

---

## 作者：abensyl (赞：1)

[P9849 [ICPC2021 Nanjing R] Xingqiu's Joke](https://www.luogu.com.cn/problem/P9849)。

## 思路

题目的关键就是：利用三种操作，使用最少的操作次数使得 $a$ 变成 $b$ 的倍数（不妨令 $a>b$，如果不满足，可以把 $a$ 和 $b$ 直接交换一下，是不影响答案的，下面描述过程中全部默认 $a>b$）。

无论进行什么操作，显然由于开始时 $a\neq b$，所以在操作过程中也都不可能有 $a=b$ 的情况出现，并且，如果在初始时 $a>b$，那么在整个操作过程中都有 $a>b$，最终也肯定是 $b$ 被变为了 $1$，可以分三种情况讨论一下，证明是非常简单的。

那么，$a$ 是 $b$ 的倍数，则可表示为 $\gcd(a,b)=b$，根据辗转相减法，可以知道 $\gcd(a,b)=\gcd(b,a-b)$，前提是 $a\neq b$，这一点刚才已经证明了。

有了这个，我们继续来看前两种操作，这两种操作涉及 $a$ 和 $b$ 同时 $\pm 1$，这个操作显然不会影响 $a-b$ 的值。

那么，考虑深度优先搜索，考虑对于 $a-b$ 的因子进行顺序上的枚举，每次递归去查找它的上下最小和最大整出这个因子的数字，然后进行加减操作即可。

注意递归的终止条件，如果 $a-b=1$ 则应输出 $b-1$，如果 $b=1$ 则直接返回即可。

采用记忆化搜索提升效率，可以轻松通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e9+7;
unordered_map<int,int> dp,vc;
int hsh(int a,int b) { return a*INF+b; }
void sep(int x) {
	vc.clear();
	for(int i=2;i*i<=x;++i) {
		if(x%i) continue;
		int zc=0;
		while(x%i==0) x/=i,++zc;
		vc[i]=zc;
	} if(x!=1) vc[x]=1;
}
int get(int a,int b) {
	int res=b-1;
	if(a-b==1) return b-1;
	if(b==1) return 0;
	if(dp[hsh(a,b)]) return dp[hsh(a,b)];
	for(auto c:vc) {
		if(c.second==0) continue;
		vc[c.first]--;
		int zc=b/c.first;
		int up=b-zc*c.first,dw=(zc+1)*c.first-b;
		int pr=zc*c.first,pl=(zc+1)*c.first;
		int res1=up+get((a-up)/c.first,(b-up)/c.first)+1;
		int res2=dw+get((a+dw)/c.first,(b+dw)/c.first)+1;
		res=min({res,res1,res2});
		vc[c.first]++;
	} dp[hsh(a,b)]=res;
	return res;
}
void solve() {
	int a,b;
	cin>>a>>b;
	sep(abs(a-b));
	cout<<get(max(a,b),min(a,b))<<'\n';
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

[代码和 AC 记录](https://codeforces.com/gym/103470/submission/235728554)。

---

## 作者：xiao7_Mr_10_ (赞：0)

我居然找到了一个月前考试的原题。

首先我们显然发现对于一个二元组 $(a,b)$ 它的答案等价于二元组 $(b,a)$ 的答案。

所以我们不妨设询问为二元组 $(a,b)$ 其中 $a \le b$。

为了解决操作三的麻烦，我们想办法先把操作一和二的影响消除，此时因为有 $a\le b$，所以我们不妨设 $d=b-a$。然后把这个二元组**重新表示**为 $(a,d)$，等价于记录二元组 $(a,a+d)$ 的答案。

这样我们就消除了前两个操作的问题，因为 $d$ 是相对不变的。接下来我们考虑分析状态总数以及时间复杂度。

显然发现对于操作三，如果我们同时除以一个数 $x$，那么满足 $d \mid x$ 即可。所以后者 $d$ 的状态数不超过**因数级别**。

再考虑前者 $a$ 相对的取值个数，我们发现它的取值实际上只和除以哪些数以及其顺序有关。

注意到如果除以的数的集合是一样的，那么 $a$ 的取值只有至多两种，显然易得。

所以写个记忆化就过去了，时间复杂度有保障。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mkp make_pair
const int N=1e6+5,maxn=1e5;
int t,a,b,vis[N],prime[N],cnt;
map <pair<int,int>,int> mp;
void init(){
	for(int i = 2;i <= maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j = 1;j <= cnt&&prime[j]*i <= maxn;j++){
			vis[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}int st[N],top;
int dfs(int x,int y){
	if(x==1)return 0;
	if(y==1)return x-1;
	if(mp.find(mkp(x,y))!=mp.end())return mp[mkp(x,y)];int ans=x-1;
	for(register int i = 1;i <= top;i++){
		if(y%st[i]==0){
			ans=min(ans,dfs(x/st[i],y/st[i])+x%st[i]+1);
			ans=min(ans,dfs((x+st[i]-1)/st[i],y/st[i])+st[i]-x%st[i]+1);
		}
	}return mp[mkp(x,y)]=ans;
}
void work(){
	cin >> a >> b;top=0;
	if(a>b)swap(a,b);int val=b-a;
	for(int i = 1;prime[i]*prime[i] <= val;i++){
		if(val%prime[i]==0){
			st[++top]=prime[i];
			while(val%prime[i]==0)val/=prime[i]; 
		}
	}
	if(val!=1)st[++top]=val;
	cout << dfs(a,b-a) << "\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> t;init();
	while(t--)work();
	return 0;
}//tlh赐予我力量吧!
```

---

## 作者：Fimlty (赞：0)

LTF大佬的题解未免~~抽象~~高端了一点，我想再说几句。

**部分引用了 @SDLTF_凌亭风 的代码，稍作了修改。**

------------

我们考虑如何能使用 $opt3$。

定义 $dp_{i,j}$ 是 $a = i, a - b = j$ 时，使 $a = 1$ 的最少操作次数，这样我们的求解函数就能写出来了。

我们递归求答案时，要使用下面的代码：
```cpp
int solve(int a, int c) {
	if (a == 1)return 0;
	if (c == 1)return a - 1;
	if (dp[{a, c}])return dp[{a, c}];
	int res = a - 1;
	for (int i : frac)
		if (c % i == 0)
			res = min({ res, a % i + 1 + solve(a / i,c / i), 
				i - a % i + 1 + solve(a / i + 1, c / i) });
	return dp[{a, c}] = res;
}
```
令 $c = a - b$,

$frac$ 是 $c$ 的素因数数组，我们每次枚举一个因数 $i$，这个时候有两种转移的方法。

- 使用 $op1$ 让 $a$ 变成 $i$ 的倍数 $a + a \mod i$
- 使用 $op2$ 让 $a$ 变成 $i$ 的倍数 $a -i + a \mod i$

无论用哪种操作，$c$ 始终会变成 $ \frac{c}i$，再加上记忆化可以满足时间复杂度需求。

## 代码
```cpp
#include<iostream>
#include<vector>
#include<map>
using namespace std;
vector<int>frac;
map<pair<int, int>, int>dp;
int solve(int a, int c) {
	if (a == 1)return 0;
	if (c == 1)return a - 1;
	if (dp[{a, c}])return dp[{a, c}];
	int res = a - 1;
	for (int i : frac)
		if (c % i == 0)
			res = min({ res, a % i + 1 + solve(a / i,c / i), 
				i - a % i + 1 + solve(a / i + 1, c / i) });
	return dp[{a, c}] = res;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--) {
		frac.clear();
		int a, b; cin >> a >> b;
		if (a > b)swap(a, b);
		int delta = b - a, i = 2;
		for (; i * i <= delta; i++)
			if (delta % i == 0) {
				frac.push_back(i);
				while (delta % i == 0)delta /= i;
			}
		if (delta != 1)frac.push_back(delta);
		cout << solve(a, b - a) << '\n';
	}
}
```



---

## 作者：SDLTF_凌亭风 (赞：0)

重云宝宝很可爱，所以写了这篇题解。

我们先关注前两个看起来比较友善的操作。记两个数分别为 $a, b$，令 $\delta = a - b$，不难发现前两个操作都不会对 $\delta$ 产生影响。只有在第三个操作的时候，假设他们的一个质公因数为 $p$，则有，$\delta \leftarrow \frac{\delta}{p}$。

那这又有什么用呢？我们考虑 $(a,b)$ 最终变成了 $(1,x)$ 这样子，令 $\zeta = |\delta| - |x - 1|$，并把 $\zeta$ 的质因数分解形式写成 $\zeta = \sum p_i^{k_i}$ 的形式，其中 $p_i$ 为质因子。

那么 $(a,b)$ 一定是通过 $\sum k_i$ 次除法操作得到的。于是我们暴力转移一下：记 $f(a,\delta)$ 为 $(a,\delta)$ 转移为 $(1,x)$ 的最小步数，那我们就可以从 $f(\lfloor \dfrac{a}{p} \rfloor, \dfrac{\delta}{p})$ 和 $f(\lceil \dfrac{a}{p} \rceil, \dfrac{\delta}{p})$ 转移过来。代码非常好写，跑得飞快。

```cpp
#include <bits/stdc++.h>
#define tra(x, y) (x * 1e9 + y)
using namespace std;

vector<int> fact;
unordered_map<long long, int> f;
int dfs(int a, int c) {
	if(a == 0) return 0x3f3f3f3f;
	if(a == 1) return 0;
	if(c == 1) return a - 1;
	if(f[tra(a, c)]) return f[tra(a, c)];
	int res = a - 1;
	for(auto p : fact) if(!(c % p)) res = min({res, (a % p) + 1 + dfs(a / p, c / p) , p - (a % p) + 1 + dfs(a / p + 1, c / p)});
	return f[tra(a,c)] = res;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	for(int a, b, delta; T; -- T) {
		f.clear(), fact.clear(), cin >> a >> b;
		if(a > b) swap(a, b);
		delta = b - a;
		for(int i = 2; i * i <= delta; ++ i) {
			if(!(delta % i)) {
				fact.push_back(i);
				while(!(delta % i)) delta /= i;
			}
		}
		if(delta != 1) fact.push_back(delta);
		cout << dfs(a, b - a) << '\n';
	}
}
```

---

