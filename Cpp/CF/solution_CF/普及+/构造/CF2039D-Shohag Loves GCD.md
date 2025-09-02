# Shohag Loves GCD

## 题目描述

Shohag 拥有一个整数 $n$ 和一个包含 $m$ 个不同整数的集合 $S$。请帮助他找到字典序最大*的整数数组 $a_1, a_2, \ldots, a_n$，使得对于每个 $1 \le i \le n$ 有 $a_i \in S$ ，并且满足对所有 $1 \le i < j \le n$ 有 $a_{\gcd(i, j)} \neq \gcd(a_i, a_j)$†，或者说明不存在这样的数组。

*一个数组 $a$ 如果在第一个不同的位置上比数组 $b$ 有更大的元素，则称其为字典序大于数组 $b$（假设两个数组长度相同）。

†$\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

## 说明/提示

在第一个测试用例中，数组中的每个元素都属于给定的集合 $S = \{3, 4, 6\}$，并且数组的所有索引对都满足必要的条件。特别是对于对 $(2, 3)$，有 $a_{\gcd(2, 3)} = a_1 = 6$ 而 $\gcd(a_2, a_3) = \gcd(4, 4) = 4$，因此它们不相等。尽管存在其他满足条件的数组，但这个是其中字典序最大的。

在第三个测试用例中，由于我们只能使用数组 $a = [2, 2]$，但对于该数组，对于对 $(1, 2)$，有 $a_{\gcd(1, 2)} = a_1 = 2$ 而 $\gcd(a_1, a_2) = \gcd(2, 2) = 2$，因此它们相等，这是不允许的！所以没有解决方案。

## 样例 #1

### 输入

```
3
6 3
3 4 6
1 1
1
2 1
2```

### 输出

```
6 4 4 3 4 3 
1 
-1```

# 题解

## 作者：TianTianChaoFang (赞：3)

# 思路  

这个题其实只需要考虑一件事：记答案数组为 $a$，对于两个不同下标 $i$ 和 $j$，当 $\gcd(i,j) = \min(i,j)$ 时，我们只需要让 $a_{\max(i,j)} < a_{\min(i,j)}$ 即可。

证明：任意两个数 $x,y$，一定有 $\gcd(x,y) \leq \min(x,y)$。   
第一种情况，如果 $\gcd(i,j) = \min(i,j)$，显而易见按上述构造是满足题意的，因为 $a_{\gcd(i,j)} = a_{\min(i,j)} = \max(a_i,a_j) \neq \gcd(a_i,a_j)$。  
第二种情况，如果 $\gcd(i,j) \neq \min(i,j)$，那么 $\gcd(i,j) < \min(i,j) $，记 $c = \gcd(i,j)$，则 $\gcd(i,c) = c$ 并且 $\gcd(j,c) = c$，此时问题转化为第一种情况。  
证毕。  

答案要最大字典序，那首先就把原集合元素从大到小排列来贪心求解。  
对 $1$ 到 $n$ 中的每一个答案数组下标唯一分解一下，记当前下标为 $i$，分解出来的素数为 $k$。  
因为除掉的数越少，前置下标包含的因子一定越多，求得的答案肯定越能满足前面所有的下标。  
所以只需要对每一个答案数组下标用除掉一个素数的前置下标来转移就行了。  
我们用 $ans_i$ 来表示答案数组下表为 $i$ 的位置的对应的集合中的元素下标，则有转移方程 $ans_i = \max\{ans_{i / k} + 1\}$。 
而这个过程可以直接预处理，因为我们只需要得到每一个答案数组的下标对应的一个集合内部的下标。  

时间复杂度：$O(n\sqrt{n})$。  

# AC CODE

```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 2e18
#define ull unsigned long long
#define ls o << 1
#define rs o << 1 | 1

using namespace std;

const int N = 1e5 + 9;
int a[N];
int ans[N];
int n, m;

bool check()
{
	for(int i = 1;i <= n;i ++)
		if(ans[i] > m)return false;//只要下标超出了集合的大小，就无解
	return true;
}

void solve()
{
	cin >> n >> m;
	for(int i = 1;i <= m;i ++)cin >> a[i];
	reverse(a + 1, a + m + 1);//将集合元素从大到小排列
	
	if(check())
	{
		for(int i = 1;i <= n;i ++)cout << a[ans[i]] << " \n"[i == n];
	}
	else cout << -1 << '\n';
}

void init()//预处理每个答案数组的下标对应的集合下标
{
	ans[1] = 1;
	for(int i = 2;i < N;i ++)
	{
		int tmp = i;
		for(int j = 2;j * j <= tmp;j ++)
		{
			if(tmp % j == 0)
			{
				ans[i] = max(ans[i], ans[i / j] + 1);
				while(tmp % j == 0)tmp /= j;
			}
		}
		
		if(tmp > 1)ans[i] = max(ans[i], ans[i / tmp] + 1);
	}
}

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

	init();

    int t = 1;cin >> t;
    while(t --)solve();

    return 0;
}

```

---

## 作者：lgx57 (赞：1)

简单题。

注意到答案与数根本没有关系，从而想到先把数从大到小排序。

接下来我们一个一个填数，由于字典序要最大，所以第一位肯定填最大的数。

注意到 $\gcd(x,y) \le \min(x,y)$，于是可以在此基础上构造。令 $ans_i=\text{比 } \displaystyle\max_{j \mid i,j <i} ans_j \text{ 小的第一个数}$。容易证明，这个构造合法并且是字典序最大的。

于是我们用 $O(n \sqrt n)$ 的复杂度解决了这个问题。

```cpp
void sol(){
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=n;i++) ans[i]=0;
	for (int i=1;i<=m;i++) cin>>a[i];
	sort(a+1,a+m+1,greater<int>());
	ans[1]=1;
	for (int i=2;i<=n;i++){
		int ma=0;
		for (int j=1;j*j<=i;j++){
			if (i%j==0){
				ma=max(ma,max(ans[j],ans[i/j]));
			}
		}
		ans[i]=ma+1;
		if (ans[i]>m) return cout<<-1<<endl,void();
	}
	for (int i=1;i<=n;i++) cout<<a[ans[i]]<<' ';
	cout<<endl;
}
```

---

## 作者：littlebug (赞：1)

## Solution

这里讲一个 $O(n)$ 赛时做法，不过纯靠猜结论。

先把 $s$ 降序排序。

手推了半天，发现限制条件跟 $s$ 内的数根本没关系，只跟大小有关系。又发现 $a_2,a_3,a_5,a_7,\ldots = s_2$，把下标拿出来，就成了 $2,3,5,7,9,11,\ldots$，发现差分一下分别是 $1,2,2,2,2,\ldots$，类似地发现填 $s_3$ 的是 $4,6,10,14,18,22,\ldots$，差分一下为 $2,4,4,4,4,\ldots$，以此类推。

特意写了个暴力拍了下，发现这是错的。例如在填 $s_2$ 的数里，$a_3,a_9$ 不能相同。然后想到了把不是质数的都往后推一格（即填 $s$ 中的下一个数），即 $a_3$ 填 $s_3$，$a_9$ 填 $s_3$。

但是发现还是错的，比如说 $a_3,a_9,a_{27}$ 又不行了，所以想到不是质数的往后推它的质因数个数 $-1$ 格。

但是但是发现还是错的，有的数推的格数太多了，原因是把例如填 $s_3$ 的 $a_4,a_6,a_{10},a_{14},\ldots$ ，它们共有的那个质因数 $2$ 也算进去了，于是之需要减去乘 $2$ 的次数就可以了。

记得判无解，~~我不会说我因为把判无解注释掉而次一发罚时的~~。

时间复杂度 $O(n)$，赛后发现好像轻微爆标。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<bitset>
#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;

const int MAXN=2e5+5;
int n,m,s[MAXN<<2],a[MAXN<<2];

bitset <MAXN> isp;
vector <int> ps;
int fac[MAXN];

inline void get_primes(int n)
{
    vector<int>().swap(ps);
    isp&=0;
    for(int i=2;i<=n;++i)
    {
        if(!isp[i]) ps.emplace_back(i),fac[i]=1;
        for(int j=0;j<ps.size() && i*ps[j]<=n;++j)
        {
            isp[i*ps[j]]=1,fac[i*ps[j]]=fac[i]+1;
            if(!(i%ps[j])) break;
        }
    }

    rep(i,0,n+1) isp[i]=!isp[i];
}

il void solve(int __Ti)
{
    cin>>n>>m;
    rep(i,0,n+1) a[i]=0;
    rep(i,1,m) cin>>s[i];
    sort(s+1,s+m+1,greater<int>());

    if(m==1) return cout<<(n==1 ? s[1] : -1)<<'\n',void();

    a[1]=s[1];
    int j=2,st=2,pos,qwq=0; // qwq 是乘 2 的次数
    while(st<=n && j<=m)
    {
        a[st]=s[j];
        for(pos=st+st/2;pos<=n;pos+=st)
        {
            if(isp[pos*2/st]) a[pos]=s[j];
            else a[pos]=s[j+fac[pos]-1-qwq];
        }
        st<<=1,++j,++qwq;
    }

    rep(i,1,n) if(!a[i]) return cout<<-1<<'\n',void();
    rep(i,1,n) cout<<a[i]<<' '; cout<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);

    get_primes(2e5);

    int __T; cin>>__T; rep(__Ti,1,__T) solve(__Ti);
    return 0;
}
```

---

## 作者：Luke_li (赞：1)

## 序言
tag：数论；构造；贪心；1700*


为了证明我A了这道题，贴一个提交记录：[CF提交记录](https://codeforces.com/contest/2039/submission/293601317)

吐槽：线性筛写错了，调了2小时（悲

## 题目大意


给定一个整数 $n$ 和一个包含 $m$ 个不同整数的集合 $S$。请找到**字典序最大**的整数数组 $a_1, a_2, \ldots, a_n$，使得对于每个 $1 \le i \le n$ 有 $a_i \in S$，并且满足对所有 $1 \le i < j \le n$ 有 $a_{\gcd(i, j)} \neq \gcd(a_i, a_j)$，或者说明不存在这样的数组。

## 解法

### I
乍一看不好做，但是我们注意到以下结论：

1. 如果 $x\mid y$ 那么 $a_x\nmid a_y$。由题意推出。
2. $a_1=S_{\max}$，为了字典序最大。如果这么做会导致后面的不合法，不这么做也不会合法。

### II
结合以上两点，我们有一种贪心：
1. 将 $S$ 倒序排序。
2. $a_1$ 选 $S_1$，然后后面的所有 $1\mid i$ (也就是所有 $i>1$）位置都不能选择 $S_1$ 填入。
3. $a_2$ 选择能选的最大的数字（也就是 $S_2$），然后禁止后面所有 $2\mid i$ 位置选择 $S_2$ 填入。
4. 以此类推。每个位置选择目前自己能填的最大的数即可。

### III
先证明这种贪心的正确性：

- 显然，如果我们在位置 $x$ 不填能填的最大的数字 $S_c$，相当于是允许了 $x\mid i$ 的位置填 $S_c$。
- 如果旧的方案非法，那么新的方案仍然非法，因为 $S_c$ 和 $x$ 位置新填的数还是会占用。
- 因为我们想要让字典序最大，所以这么做答案肯定不优秀。

### IV

然后讲讲做法：

- 显然 $i$ 位置会被禁止填入一系列数：$S_1,S_2,...,S_k$，这是 $S$ 数组的一个前缀。

- 设第 $i$ 个位置被禁止填入的数字有 $k_i$ 个，那么这个位置就会填入 $S_{k_i+1}$。容易发现， $k_i=(\max\limits_{p\mid i}^{p<i}k_p)+1$。

- 更进一步地，$k_i$ 的值就是 $i$ 最多能分解为多少整数相乘。答案就是 $i$ 的素因子个数（重复的算多个）。

使用欧拉筛筛一遍就可以了。


### V
时间复杂度：$O(n)$ 

~~比官解那个 $O(n\log n)$ 的埃氏筛要好到不知道哪里去了~~

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=3e5+10;
ll n,m;
ll a[N],f[N];//f[i]表示：i的质因子个数（可重）+1
bool pd[N];
vector<ll> prime; 
void xxs(ll lim)
{
	f[1]=1;
	for(ll i=2;i<=lim;i++)
	{
		if(!pd[i])
		{
			f[i]=2;
			prime.push_back(i);
		}
		for(ll j=0;j<(ll)prime.size() && prime[j]*i<=lim;j++)
		{
			pd[prime[j]*i]=1;
			f[prime[j]*i]=f[i]+1;
			if(i%prime[j]==0)
				break;
		}
	}
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	ll T;
    cin>>T;
    xxs(3e5);//线性筛
    while(T--)
    {
    	cin>>n>>m;
    	for(ll i=m;i>=1;i--)//因为是字典序最大，所以优先取后面的
    		cin>>a[i];
		if(floor(log2(n))+1>m)
		{
			cout<<-1<<"\n";
		}
		else
		{
			for(ll i=1;i<=n;i++)
			{
				cout<<a[f[i]]<<" ";
			}
			cout<<"\n";
		}
	}
    return 0;
}
```

---

## 作者：_lmh_ (赞：1)

首先我们拉出一个序列 $1=b_1\le b_2\le b_3\le \cdots \le b_k$ 使得对于所有的 $1\le i<k$，$b_i|b_{i+1}$，那么显然这些 $a_{b_i}$ 各不相同。（如果 $a|b$，则 $\gcd(a,b)=a$）

考虑对每个数搞出以它为结尾的最长的这样的一条链，在这条 $\{b_i\}$ 上必须有 $\frac{b_{i+1}}{b_i}$ 为质数，否则不优。这样我们就可以预处理最长反链的长度——只需要把这个数除以它的最小质因子，拼到那条链上就行。

所以我们可知，在这样的一条链上，第 $i$ 个数恰好有 $i-1$ 个质因子。令 $x$ 的质因子个数为 $c_x$。

如果存在一条 $k>m$ 的链自然无解，否则假设 $S$ 中元素从大到小为 $A_1...A_m$，则令 $a_i=A_{c_i+1}$。考虑证明它是最优的序列。

归纳证明。$n=1$ 显然。

假设 $n=k$ 时已经证明前面的最优，考虑 $n=k+1$，找出它所在的最长的一条链 $b_1\cdots b_l$，那么由构造可知，$c_{b_i}$ 取遍了 $0\sim l-1$ 且 $l=c_{k+1}$，因此 $i<l$ 的 $a_{b_i}$ 已经取遍了 $A_1 \sim A_{c_{k+1}}$。这样的情况下，$a_{k+1}$ 不能和其中任意一个相同，最大只能取到 $A_{c_{k+1}+1}$。

证明这种构造合法。对于 $x|y$ 且 $x<y$，有 $a_x>a_y$，所以 $\forall x<y,a_{gcd(x,y)}>a_y\ge \gcd(a_x,a_y)$，自然合法。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,m,a[N],ans[N],cnt[N],mx[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	for (int i=2;i<N;++i){
		cnt[i]=1;
		for (int j=2;j*j<=i;++j) if (i%j==0){
			cnt[i]=cnt[i/j]+1;break;
		}
		mx[i]=max(mx[i-1],cnt[i]);
	}
	cin>>T;
	while(T--){
		cin>>n>>m;
		for (int i=1;i<=m;++i) cin>>a[i];
		sort(a+1,a+1+m);
		if (mx[n]>=m){cout<<"-1\n";continue;}
		for (int i=1;i<=n;++i) cout<<a[m-cnt[i]]<<' ';cout<<'\n';
	}
	return 0;
}
```

---

## 作者：zengziqvan (赞：1)

**大家好，我非常喜欢图论，所以我用差分约束 A 了这道题。**

发现对于任意一个点 $i$，其倍数 $k\times i,k>1$ 与其 $\gcd$ 值一定为 $i$。

故这些 $k\times i$ 位置填的数字一定不等于 $i$ 位置填的数字。

又因为字典序最大，所以不可能存在 $k\times i$ 填的数字比 $i$ 大的情况。

考虑 $\gcd(x,y)=i$ 中 $x,y$ 都不是 $i$ 的点对的情况，此时 $x,y$ 一定是 $i$ 的倍数，已经在上面的情况考虑过了。所以 $x,y$ 填的数字一定小于 $i$ 位置填的数字，所以 $a_{\gcd(x,y)}$ 一定不等于 $\gcd(a_x,a_y)$。

综上，我们直接枚举 $i$ 及其倍数，建差分约束跑拓扑排序即可。

时间复杂度 $\Theta(n\times \sum_{i=1}^n \frac{1}{i})=\Theta(n\log n)$。

[复杂度证明](https://www.cnblogs.com/zengziquan/p/18306405)

```c++
const int N=1e5+10;
int n,a[N],m,deg[N],ok,dis[N];
vector<int>e[N];
void topsort() {
	queue<int>q;
	FOR(i,1,n) {
		if(!deg[i]) q.push(i),dis[i]=0;
	}
	while(q.size()) {
		int x=q.front();q.pop();
		for(int y:e[x]) {
			dis[y]=min(dis[x]-1,dis[y]);
			if(!(--deg[y])) q.push(y);
		}
	}
	FOR(i,1,n) if(deg[i]) 
		ok=1;
}
void solve() {
	cin>>n>>m;ok=0;
	FOR(i,1,m) a[i]=read();
	FOR(i,1,n) {
		for(int j=i<<1;j<=n;j+=i) {
			e[i].pb(j);
			++deg[j];
		}
	}
	topsort();
	int Mn=0;
	FOR(i,1,n) cmin(Mn,dis[i]);
	FOR(i,1,n) dis[i]-=Mn,++dis[i];
	FOR(i,1,n) cmax(Mn,dis[i]);
	if(Mn>m) ok=1;
	if(ok) puts("-1");
	else {
		int mx=Mn;Mn=1000000;
		FOR(i,1,n) cmin(Mn,m-dis[i]);
		FOR(i,1,n) dis[i]+=Mn;
		sort(a+1,a+m+1);
		FOR(i,1,n) cout<<a[dis[i]]<<" ";
		puts("");
	}
	FOR(i,1,n) deg[i]=dis[i]=0,e[i].clear();
}
main() {
	int t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：hgcnxn (赞：1)

## CF2039D Shohag Loves GCD题解

### 备注

定义 $f(x)$ 为 $x$ 的质因子个数（这里的质因子可以重复，比如 $4$ 有两个质因子）。特别的，$f(1)=0$。

### 题目大意

给定 $n$，$m$ 及一个有 $m$ 个数的集合 $S$，构造一个长度为 $n$ 的数组 $a$ 满足以下条件，或报告无解：

- $\forall\ 1 \le i \le n$，$a_i \in S$
- $\forall\ 1 \le i < j \le n$，$a_{\gcd(i,j)} \ne \gcd(a_i,a_j)$

### 思路

题目条件好像令人无从下手，那么我们就从最特殊的地方，即 $\gcd(i,j)=i$ 开始研究。

此时，我们不妨设 $j=ti$：

当 $\gcd(i,j) = i$ 时：
$$a_{\gcd(i,j)} = a_i$$
$$a_i \ne \gcd(a_i,a_j)$$
于是我们得到了一条重要结论：
$$a_i \ne a_{ti}$$
接下去，我们将 $i$ 分解质因数：
$$i= \prod\limits_{k=1}^{f(i)}p_k$$
观察 $1$，$\prod\limits_{k=1}^1p_k$，$\prod\limits_{k=1}^2p_k \ldots \prod\limits_{k=1}^{f(i)}p_k$ 这 $f(i)$ 个数，将其中的第 $k$ 个数记为 $s_k$，则由前文的结论，我们可知 $a_{s_1}$，$a_{s_2}$ $\ldots$ $a_{s_{f(i)+1}}$ 互不相等！

**所以，$m$ 一定要大于 $\max{f(i)}$。**

下面构造出当 $m$ 不小于 $\max{f(i)}$ 的方案：

**对于第 $i$ 个位置，$a_i$ 取 $S$ 中第 $f(i)+1$ 大的元素即可。**

因为 $i\ne j$，所以 $f(\gcd(i,j))<\max(f(i),f(j))$，那么 $a_{\gcd(i,j)}>\min(a_i,a_j)$，显然满足条件。

至此，本题做完了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[100005],f[100005],ans[100005],mx;
void g(){
	for(int i=2;i<=100000;i++){
		if(f[i]==0){
			f[i]=i;
			for(int j=i;j<=100000/i;j++)if(f[i*j]==0)f[i*j]=i;
		}
		ans[i]=ans[i/f[i]]+1;
	}
}
bool cmp(int x,int y){return x>y;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	g();
	while(t--){
		cin>>n>>m;
		for(int i=0;i<m;i++)cin>>a[i];
		mx=0;
		for(int i=1;i<=n;i++)mx=max(mx,ans[i]);
		if(mx>=m){
			cout<<"-1\n";
			continue;
		}
		sort(a,a+m,cmp);
		for(int i=1;i<=n;i++)cout<<a[ans[i]]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

限制是关于 $i,j,\gcd(i,j)$ 的形式，观察到限制数量太多了，于是考虑对于有关 $\gcd$ 的限制利用 $i,i \times j$ 的限制去刻画或者缩放。

不难发现所有 $i,i \times j$ 要满足 $a_{i \times j}$ 不是 $a_i$ 的倍数，我们发现这个条件满足后任意 $i,j$ 也会满足 $a_{\gcd(i,j)}$ 不是 $a_i,a_j$ 的因数，所有限制都被满足。

等于说在位置 $i$ 放了 $x$ 后，所有形如 $i \times j$ 且 $j>1$ 的位置都不能放 $x$ 的倍数。

我们尝试再弱化下限制，我们声称，最优方案中假若位置 $i$ 放了 $x$，那么位置 $i$ 一定受到了不能放 $x \times j$ 其中 $j>1$ 的限制，原因就是填 $x \times j$ 对后面肯定更优。

那么限制等价于位置 $i$ 填了 $x$ 后位置 $i \times j$ 其中 $j>1$ 不能填 $x$，因为不能填 $x$ 的倍数的限制前面已经生效了，所以对于存在方案这件事而言每个位置上填什么都无所谓，因此直接从前往后每次把能填的最大的填进去，构造到最优方案即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
map<int,int> vis[maxn];
int n,m;
int S[maxn];
int a[maxn];
void work(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>S[i];
    for(int i=1;i<=n;i++){
        int p=m;
        while(vis[i][S[p]]==1&&p>0) p--;
        if(p==0){
            cout<<"-1\n";
            for(int j=1;j<=n;j++) vis[j].clear();
            return ;
        }
        a[i]=S[p];
        for(int j=2;i*j<=n;j++) vis[i*j][S[p]]=1;
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    cout<<'\n';
    for(int j=1;j<=n;j++) vis[j].clear();
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}

```

---

## 作者：Binah_cyc (赞：0)

看见这道题第一件事就应该转化题意，主要是下标带 $\gcd$ 实在是太不牛。

先给结论，满足原题要求的充要条件为 $\forall i,j \in [1,n],i|j,a_i \not | a_j$。

先证必要性。

证明：对于 $i | j$，$\gcd(i,j)=i$。又因为 $a_{\gcd(i,j)} \not = \gcd(a_i,a_j)$，所以 $a_i \not | a_j$。

再证充分性。

证明：对于$i \not | j$，设 $k = \gcd(i,j)$，可得 $a_k \not | a_i,a_k \not | a_j$。由此可得 $k \not | \gcd(a_i,a_j)$。

因此，我们只需要基于这个条件构造合法的方案即可。

将给定的元素从大到小排序，由贪心可知 $a_1 = s_1$。同时，所有 $1 | i$，都应满足 $a_i \not | a_1$。因为 $a_1$ 是最大的元素，所以它等价于 $a_i \not = a_1$。

然后，考虑 $a_2$，因为 $a_2 \not = a_1$，所以 $a_2 = s_2$。同样的，所有 $2 | i$，都应满足 $a_i \not = a_2$。

以此类推，我们可以得到每一个数的限制条件。

代码实现上，可以预处理每一个数的约数，然后暴力计算当前的数。复杂度为调和级数，复杂度为 $O(n \log^2 n)$，使用哈希表可以优化成 $O(n \log n)$。代码使用哈希表实现。

```c
// Problem: D. Shohag Loves GCD
// Contest: Codeforces - CodeTON Round 9 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/2039/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
constexpr int N=3e5+5;
int _,n,m,a[N],ans[N];
vector<int> fac[N];

__gnu_pbds::gp_hash_table<int,bool> vis;//使用pbds自带的哈希表
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	sort(a+1,a+m+1,[](int x,int y){return x>y;});
	for(int i=1;i<=n;i++)
	{
		vis.clear();
		ans[i]=0;
		for(auto x:fac[i]) vis[ans[x]]=1;
		for(int j=1;j<=m;j++) if(!vis[a[j]]){ans[i]=a[j];break;}
		if(!ans[i]) return cout<<-1<<'\n',void();
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<'\n';
}

signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	for(int i=1;i<=300000;i++) for(int j=2;i*j<=300000;j++) fac[i*j].push_back(i);
	cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

从给定集合中选数并构造序列 $\{a_i\}$，需要满足 $a_{\gcd (i,j)} \neq \gcd(a_i,a_j) \mid \forall 1 \le i < j \le n$ 并且构造出的序列字典序最大。

不妨从反面分析，考虑满足 $a_{\gcd (i,j)} = \gcd (a_i,a_j)$。当 $i \mid j$ 时，$\gcd (i,j) = i$，$a_i \mid a_j$。进一步的，当 $i \nmid j$ 时，是否也存在一个 $i$，满足 $a_{\gcd (i,j)} = \gcd (a_i,a_j)$ 呢？

假设存在这个 $i$，我们设 $g = \gcd (i,j)$，那么 $a_g = \gcd (a_i,a_j)$ 且 $g < i$。由于 $g \mid i$，等价于 $g = \gcd (g,i)$，由上面的结论可知 $a_{\gcd (g,i)} = \gcd (a_g,a_i)$。此时与题目的条件不符合，故假设不成立。

所以说在构造 $a_i$ 时，只需要考虑序列以 $i$ 的因数（且小于 $i$）为下标的数，预处理因数即可。在构造的时候，我们可以将所有以 $i$ 的因数为下标的数放入 $\mathrm{set}$ 中，然后从最大的数开始，查找到第一个未出现在集合中的数即可退出循环。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int M = 1e5; 
const int MOD = 1e9 + 7;
inline int read ();
vector <int> ans,p[MAX];
int t,n,m,a[MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	for (int i = 1;i <= M;++i)
		for (int j = i + i;j <= M;j += i) p[j].push_back (i);//j 的因数 
	t = read ();
	while (t--)
	{
		n = read ();m = read ();
		for (int i = 1;i <= m;++i) a[i] = read ();
		sort (a + 1,a + 1 + m);ans.clear ();
		for (int i = 1;i <= n;++i)
		{
			set <int> invaild;
			for (auto item : p[i]) invaild.insert (ans[item - 1]);
			for (int j = m;j;--j)
			{
				if (invaild.find (a[j]) == invaild.end ())
				{
					ans.push_back (a[j]);
					break;
				}
			}
			if (ans.size () != i) break;
		} 
		if (ans.size () != n) puts ("-1");
		else {for (auto item : ans) printf ("%d ",item);puts ("");} 
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：Exp10re (赞：0)

爆标爆标。

## 解题思路

考虑 $\operatorname{gcd}$ 的两个性质：$\Omega(\operatorname{gcd} (x,y))\leq \min(\Omega(x),\Omega(y))$，以及 $\operatorname{gcd} (x,y)\leq \min(x,y)$，其中 $\Omega(x)$ 表示 $x$ 的质因子个数（即对 $x$ 质因数分解后各个质因子的次数和）。

记 $f(n)$ 表示：对于长为 $n$ 的数列，$m\geq f(n)$ 时无论 $S$ 为何值均有解，即 $f(n)$ 为对于长为 $n$ 的数列的 $m$ 的下界。

---

### 引理

$f(n)=\max\limits_{1\leq i \leq n}\Omega(i)+1$。

### 证明

考虑到 $\forall 1\leq x\leq n,a_x \ne a_k (k\mid x)$ 是题目中性质成立的必要条件。

记 $S_x=\{a_k \mid (k\mid x)\}$，$c_x=|S_x|$，即 $c_x$ 表示全部合法情况下 $x$ 所有因子的最小不同 $a_x$ 个数，则有 $c_x=\max\limits_{k\mid x} c_k+1$，边界为 $c_1=1$。

根据这个定义不难注意到 $c_x=\Omega(x)+1$，而又有 $f(n)=\max\limits_{1\leq i \leq n}c_i$，故 $f(n)=\max\limits_{1\leq i \leq n}\Omega(i)+1$ 得证。

---

得到下界后考虑如何构造 $a$ 取得该下界：

- 若 $m\lt f(n)$ 显然无解。
- 否则，$a_i=S_{m-\Omega(i)}$。

不考虑正确性的情况下这样的构造显然可以取得下界。

接下来考虑正确性证明：任取 $1\leq i \lt j \leq n$，我们需要 $\operatorname{gcd}(a_i,a_j)=\operatorname{gcd}(S_{m-\Omega(i)},S_{m-\Omega(j)})\ne a_{\operatorname{gcd}(i,j)}=S_{m-\Omega({\operatorname{gcd}}(i,j))}$。

根据上面 $\operatorname{gcd}$ 的第一条性质，有 $m-\Omega({\operatorname{gcd}}(i,j))\geq m-\min(\Omega(i),\Omega(j))$，又有 $S$ 升序，故 $S_{m-\Omega({\operatorname{gcd}}(i,j))}\geq \min(S_{m-\Omega(i)},S_{m-\Omega(j)})$。又根据上面 $\operatorname{gcd}$ 的第一条性质，有 $\min(S_{m-\Omega(i)},S_{m-\Omega(j)})\geq \operatorname{gcd}(S_{m-\Omega(i)},S_{m-\Omega(j)})$，联立可得 $S_{m-\Omega({\operatorname{gcd}}(i,j))}\geq \min(S_{m-\Omega(i)},S_{m-\Omega(j)})\geq \operatorname{gcd}(S_{m-\Omega(i)},S_{m-\Omega(j)})$，若这两个大于等于号其中一个无法取相等，原条件成立。

考虑对第一个大于等于号下手：即我们尝试证明当 $i\ne j$ 时 $\Omega({\operatorname{gcd}}(i,j))\ne \max(\Omega(i),\Omega(j))$。

证明不难：若 $\Omega(i)\ne\Omega(j)$ 上式显然成立，而若 $\Omega(i)=\Omega(j)$ 要想上式成立当且仅当 $i=j$，故 $\Omega({\operatorname{gcd}}(i,j))\ne \max(\Omega(i),\Omega(j))$ 得证。

综上，该构造方案的正确性得证，线性筛 $\Omega(x)$ 时间复杂度 $O(n)$，其余部分时间复杂度 $O(n)$，故总时间复杂度是 $O(n)$ 的。

---

## 作者：sbno333 (赞：0)

首先注意到不是每个数都相同，根据样例可得。

首先将 $S$ 排序，考虑怎么安排数。

对于同一种数，其所有位置必须互不为倍数，否则代入要求可得自己这种数就会造成不可挽回的后果，如果互不为倍数，此时发现自己不会和自己冲突。

如果不想不同种类数的影响，考虑贪心放置，最大放第一个，然后次大放在所有会放在第 $2$ 个位置，此时 $2$ 的倍数放不了，然后放 $3$，$3$ 的倍数放不了，最后放在所有质数位置，考虑第三大数，除了质数以外最小肯定是两个质因子的位置，考虑继续放置，三个质因子的位置会发生倍数，所以都放在两个质数位置，于是，容易证明，对于 $k$ 大，放在 $k-1$ 个质数组成的位置。

考虑数与数的影响两个数的最大公约数一定小于等于最小的那个数，要是冲突就是在质因子比小的那个的质因子还多的位置，但是 $a_{\gcd(i,j)}$ 又是质因子比少的更少（或不变），然后质因子少的就是大，二者不可能为一个数，得证。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int s[1000009];
int a[1000009];
int q[1000009];
bool vis[1000009];
int inn;
int sm[1000009];
void _main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n+10;i++){
		a[i]=0;
	}
	for(int i=0;i<=m+10;i++){
		s[i]=0;
	}
	for(int i=1;i<=m;i++){
		cin>>s[i];
	}
	sort(s+1,s+1+m);
	for(int i=1;i<=m/2;i++){
		swap(s[i],s[m-i+1]);
	}
	for(int i=1;i<=n;i++){
		if(sm[i]+1>m){
			cout<<-1<<endl;
			return;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<(a[i]=s[sm[i]+1])<<" ";
	}
	cout<<endl;
}
signed main(){
	vis[1]=1;
	sm[1]=0;
	for(int i=2;i<=1000000;i++){
		if(!vis[i]){
			q[++inn]=i;
			sm[i]=1;
		}
		for(int j=1;j<=inn&&q[j]*i<=1000000;j++){
			vis[i*q[j]]=1;
			sm[i*q[j]]=sm[i]+1;
			if(i%q[j]==0){
				break;
			}
		}
	}
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
} 
```

---

