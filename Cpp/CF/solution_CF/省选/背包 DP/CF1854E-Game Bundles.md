# Game Bundles

## 题目描述

Rishi is developing games in the 2D metaverse and wants to offer game bundles to his customers. Each game has an associated enjoyment value. A game bundle consists of a subset of games whose total enjoyment value adds up to $ 60 $ .

Your task is to choose $ k $ games, where $ 1 \leq k \leq 60 $ , along with their respective enjoyment values $ a_1, a_2, \dots, a_k $ , in such a way that exactly $ m $ distinct game bundles can be formed.

## 说明/提示

In the first sample, any subset of size $ 3 $ is a game bundle. There are $ 4 $ such subsets.

## 样例 #1

### 输入

```
4```

### 输出

```
4
20 20 20 20```

## 样例 #2

### 输入

```
722```

### 输出

```
15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1```

## 样例 #3

### 输入

```
1```

### 输出

```
1
60```

# 题解

## 作者：EnofTaiPeople (赞：17)

这说明你的能力还不足以上 Grandmaster。

题意给定 $m$，需要构造长度为 $n$ 的序列 $a_i$，使得该序列恰好有 $m$ 个子序列的和为 $60$，要求 $n,a_i\le60$，保证 $m\le10^{10}$。

题面没有无解选项，说明本题一定有解，而且容易发现解的数量很多。

很明显对于 $a_i>30$ 的，最多在子序列中出现 $1$ 次，考虑**随机选取** $a_i\le30$ 的序列，设 $f_k$ 表示和为 $k$ 的子序列个数，我们选取最长的前缀使得 $f_{60}\le m$，然后发现增加一个 $a_i>30$ 能得到的贡献为 $f_{60-a_i}$，而在随机情况下 $f$ 均匀分布，于是新增的 $a_i>30$ 的可以按 $f_{60-a_i}$ 从大到小依次考虑，最后选取的个数还在 $\log m$ 的级别，可以接受。

因为有时候当 $a_i$ 较小时，$f$ 的增长率会更高，于是可以每次随机一个 $lim$，在对于每个 $a_i$ 在 $[1,lim]$ 内随机选取。

然后就可以通过了，AC 记录：

https://codeforces.com/contest/1854/submission/216344540

---

## 作者：Leasier (赞：6)

来点神秘乱搞。

------------

若没有数组长度的限制，一个神秘的想法是从小到大加数，对于当前这个数加到再加一个就超出 $m$ 为止。

由于每加一个 $60$ 方案数会恰好加 $1$，**在忽略 $k \leq 60$ 的前提下**一定可以让方案数最终为 $m$。

但这样做的 $k$ 不太靠谱，随手测了一个 $m = 10^{10}$，发现这样构造出的 $k = 223$……

注意到这样做的话，一开始就会凑出 $60$ 个 $1$ 使其存在一种方案，而为了在一开始构造出较大的基数，我们不应该一直加 $1$。

于是我们不妨钦定最终每个数出现次数 $\leq 5$，然后就过了。~~我也不知道这为啥能过啊。~~

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 60, M = 5;
int ans[N + 7];
ll dp[N + 7];

int main(){
	int k = 0;
	ll m;
	scanf("%lld", &m);
	dp[0] = 1;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M && dp[N] + dp[N - i] <= m; j++){
			ans[++k] = i;
			for (int x = N; x >= i; x--){
				dp[x] += dp[x - i];
			}
		}
	}
	printf("%d\n", k);
	for (int i = 1; i <= k; i++){
		printf("%d ", ans[i]);
	}
	return 0;
}
```

---

## 作者：Chenyanxi0829 (赞：2)

设 $f_i$ 为当前序列和为 $i$ 的子序列的个数，$sum$ 表示当前序列中和为 $60$ 的子序列个数。

新加一个数 $x$ 时 $sum$ 就会增加 $f_{60-x}$，那么就可以考虑每次选 $f_{60-x}$ 最大且 $sum+f_{60-x}\le m$ 的 $x$ 添加到序列末尾并更新所有 $f_i$。但是因为一开始只有 $f_0=1$，所以每次都会选 $60$，序列长度就是 $m$ 了。解决方法是一开始先随机一个长度为 $10$ 的且 $sum\le m$ 的序列，如果中途就满足要求了就直接退出，这样再按照之前的方法加数就不会每次都选 $60$ 了。可即使这样序列长度还是有可能 $>60$，所以需要重复多次上面的操作，如果序列长度 $>60$ 就重做一遍，这样就没问题了。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

long long m, c[100], ma, y;
vector<int> k;
int a, cnt;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  mt19937 rnd(time(0));
  cin >> m, y = m;
  for (; 1;) {
    c[0] = 1;
    for (; m && k.size() < 60;) {
      if (++cnt <= 10) {
        do {
          a = rnd() % 60 + 1;
        } while (c[60 - a] > m);
      } else {
        ma = -1;
        for (int i = 1; i <= 60; i++) {
          (c[60 - i] <= m && c[60 - i] > ma) && (ma = c[60 - i], a = i);
        }
      }
      m -= c[60 - a], k.push_back(a);
      for (int i = 60; i >= a; i--) {
        c[i] += c[i - a];
      }
    }
    if (!m) {
      cout << k.size() << '\n';
      for (int i : k) {
        cout << i << ' ';
      }
      exit(0);
    }
    m = y;
    fill(c, c + 61, 0);
    k.clear();
    cnt = 0;
  }
  return 0;
}
```

---

## 作者：tzc_wk (赞：2)

都这么会乱搞的吗/xia

随机生成若干 $<30$ 的数直到它们当中和为 $60$ 的子集个数 $>k$ 为止。删去最后一个元素。然后考虑贪心确定 $>30$ 的部分，具体方法是按照 $dp_{60-x}$ 从大到小贪心选，如果剩余子集个数 $\ge dp_{60-x}$ 就在序列中加入 $x$。如此随机化直到找到符合要求的序列为止。

证明的话不会，不过感性理解一下你随机出来的这个序列的 $dp_{60-x}$ 应该近似于一个等比数列，有点类似于类比进制表示，所以你能随机出符合要求的序列的概率是很大的。

```cpp
ll k;int ord[35],a[65];mt19937 rng(time(0));
int main(){
	scanf("%lld",&k);
	if(k<=60){printf("%lld\n",k);for(int i=1;i<=k;i++)printf("60 ");return 0;}
	for(int i=1;i<=30;i++)ord[i]=i+30;
	while(1){
		static ll dp[65];memset(dp,0,sizeof(dp));
		int lim=rng()%29+1,n=0;dp[0]=1;
		while(n<=60){
			n++;a[n]=rng()%lim+1;
			if(dp[60]+dp[60-a[n]]>k){--n;break;}
			for(int i=60;i>=a[n];i--)dp[i]+=dp[i-a[n]];
		}ll rk=k-dp[60];
		sort(ord+1,ord+31,[&](int x,int y){return dp[60-x]>dp[60-y];});
		for(int i=1;i<=30;i++)while(n<60&&rk>=dp[60-ord[i]])a[++n]=ord[i],rk-=dp[60-ord[i]];
		if(!rk){
			printf("%d\n",n);
			for(int i=1;i<=n;i++)printf("%d%c",a[i]," \n"[i==n]);
			return 0;
		}
	}
	return 0;
}
```



---

## 作者：Doqe (赞：1)

绷不住了。

盲猜 $n$ 个人里面会有 $O(\frac n {\log n})$ 种解法。

首先发现本质不同的序列很多，随便估个 $\binom {120}{60}$，所以答案很宽。

接着大胆猜想一定有一堆比较小的数。

预处理 $n\le 40$，$a_i \le 4$ 的表，这个速度可以忽略不计。

然后找到集合个数最大的且小于 $m$ 的序列。

考虑往后添加数，大胆猜想只需要 $O(\log m)$ 次，记得添加完重新计算 dp 以防止信息过时。

交一发 WA 了，那就多选几个打表的较优秀的序列。

然后 AC，绷不住了。

对了，其实打表还可以更少一点，而且不一定要找多个，代码不保熟，**仅供参考**。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long F[65];
int n,a[65];
map< long long,vector<int> >M;
void ck(int n)
{
    memset(F,0,sizeof F);F[0]=1;
    for(int i=1;i<=n;++i)
    {
        int w=a[i];
        for(int i=60-w;~i;--i)F[i+w]+=F[i];
    }
    if(M[F[60]].size()>n||!M[F[60]].size())
    M[F[60]]=vector<int>(a+1,a+n+1);
}
void ck(vector<int>&a)
{
    memset(F,0,sizeof F);F[0]=1;
    for(int i=0;i<a.size();++i)
    {
        int w=a[i];
        for(int i=60-w;~i;--i)F[i+w]+=F[i];
    }
}
void dfs(int x)
{
    if(x==n+1)return ck(n);
    for(int i=a[x-1];i<=4;i++){a[x]=i;dfs(x+1);}
    ck(x-1);
}
pair<long long,vector<int>>sta[110];
int top,p[65];
bool cmp(int a,int b){return F[a]>F[b];}
long long m;
int main()
{
    cin>>m;n=40;a[0]=1;dfs(1);pair<long long ,vector<int>>awa;
    for(auto &x:M)
    	{if(x.first>m)break;++top;if(top>100)top=1;sta[top]=x;}
    for(;;--top,(!top)&&(top==100))
    {
        vector<int>tmp=awa.second;ck(awa.second);m-=F[60];
        while(m)
        {
            for(int i=1;i<60;++i)p[i]=i;
            sort(p+1,p+60,cmp);int op=0;
            for(int ii=1;ii<=60;++ii)
            {
                int i=p[ii];
                if(F[i]&&F[i]<=m)
                {
                    tmp.push_back(60-i),m-=F[i];
                    op=1;break;
                }
            }
            if(!op)while(m)tmp.push_back(60),--m;else ck(tmp);
        }
        if(tmp.size()>60)continue;printf("%u\n",tmp.size());
        for(int i:tmp)printf("%d ",i);puts("");
        return 0;
    }
}
```

---

## 作者：fireinice (赞：0)

# CF1854E Game Bundles题解

> 给定一个正整数 $m\le 10^{10}$，请你构造一个数组 $a$，长度为 $k$，满足 $\forall 1\le i\le k\le 60,1\le a_i\le 60$，且恰好存在 $m$ 个集合 $S\subset\{1,2,\dots,k\}$，$\sum\limits_{i\in S}a_i=60$。

因为子集和非常多，能看出可能的解应该非常多，而这个问题看上去很没有靠谱的做法，考虑乱搞。

于是想到我放 $x$ 个小于 $60-x$ 的数，这样贡献只能由 $1$ 和一个其他数产生，也就是用 $\binom{x}{i}$ 去凑 $m$，于是从小到大枚举 $x$，爆搜剩下的数，加上朴素的可行性最优性剪枝，发现 testcase 46 搜不出来。问题基本上是，假设用了大量的 $1$，那么搜到细节处时微调的能力就很弱了，因为一调就至少动 $x-1$，导致会和 $m$ 很接近但差一点点。

于是再加上 $2$，放 $x$ 个 $1$ 和 $2$ 满足它们的和小于 $60$，dp 算出 $f_i$ 表示用 $1,2$ 凑出 $i$ 的方案数，但是枚举 $1,2$ 太慢了，直接枚举总数 $x$，随一个 $2$ 的个数，可以搜出只有 $1$ 的部分。但是搜的慢会 T。

最后想到，从小往大枚举 $x$ 是很劣的，因为刚刚可行（存在一种方案大于 $m$）的部分在 $m$ 附近的解的数量比较少，所以改成从大到小枚举 $x$，通过。

```cpp
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#define int long long
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int N = 10010, M = 10000;
int arr[100];
map<ll, int> st;
bool done = false;
ll f[100], d[100];
int tcnt, mx;

void dfs(int i, ll s, int k, int li) {
    if (done)
        return;
    if (s > f[d[li]] * (60 - k - i))
        return;
    if (s == 0) {
        cout << i + k - 1 << endl;
        for (int j = 1; j < i; j++)
            cout << arr[j] << " ";
        for (int j = 1; j <= k - tcnt; j++)
            cout << 1 << " ";
        for (int j = 1; j <= tcnt; j++)
            cout << 2 << " ";
        cout << endl;
        done = true;
    }
    if (i >= 60 - k)
        return;
    for (int j = li; j >= 0; j--) {
        arr[i] = 60 - d[j];
        ll ns = s - f[d[j]];
        if (ns == s || ns < 0 || st.count(ns) && st[ns] <= i)
            continue;
        st[ns] = i;
        dfs(i + 1, ns, k, j);
    }
}
bool cmp(int a, int b) {
    return f[a] < f[b];
}
ll bino[100][100];
ll binom(int n, int k) {
    if (k > n)
        return 0;
    return bino[n][k];
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll m;
    cin >> m;
    for (int i = 0; i <= 60; i++) {
        for (int j = 0; j <= 60; j++) {
            if (j == 0) {
                bino[i][j] = 1;
                continue;
            }
            if (i == 0) {
                bino[i][j] = 0;
                continue;
            }
            bino[i][j] = bino[i - 1][j] + bino[i - 1][j - 1];
            if (bino[i][j] > m)
                bino[i][j] = m + 1;
        }
    }
    for (int i = 60; i >= 1; i--) {
        for (int _ = 1; _ <= 10; _++) {
            int j = rand() % i;
            if (i + j > 60)
                continue;
            f[0] = 1;
            memset(d, 0, sizeof(d));
            mx = 0;
            int dcnt = 0;
            for (int k = 1; k < 60 - i - j; k++) {
                __int128 x = 0;
                for (int l = 0; l <= min(k / 2, j); l++) {
                    x = x + (__int128)binom(j, l) * binom(i - j, k - 2 * l);
                }
                f[k] = (x > m ? m + 1 : x);
                mx = max(mx, f[k]);
                if (f[k])
                    d[k] = k, dcnt = k;
            }
            sort(d + 1, d + 1 + dcnt, cmp);
            tcnt = j;
            if (mx * (60 - i) < m)
                continue;
            dfs(1, m, i, dcnt);
            if (done)
                return 0;
            st.clear();
        }
    }
    return 0;
}
```

---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17316432.html)，第 $12$ 题。

第一次独立切的 **div1 E** 好耶！令 $B=60$。
  
遇到这种题先想 $\texttt{SPJ}$ 怎么写。发现 $m=[x^B]\prod\limits_{i=1}^k (1+x^{a_i})$。于是暴力 $O(B^2)$ 判即可。
  
令 $f(k,a)=[x^B]\prod\limits_{i=1}^k (1+x^{a_i})$。接下来开始乱搞。
  
注意到若 $a_i$ 取到比较小但又没有很小的时候 $f(k,a)$ 会比较大。
  
我们把前 $20$ 个数在 $[1,10]$ 中随机，发现这时 $f(20,a)\ge 10^4$ 是较为容易满足的。
  
随机 $T=10^6$ 次，若 $f(20,a)\ge 10^4$，这时我们考虑往 $a$ 后补 $1$（其实 $0$ 貌似也行），让其的 $f$ 最接近 $m$ 但小于等于 $m$。
  
之后我们考虑 $\times (1+x^t)$ 对 $B$ 次项的贡献，发现是加上 $B-t$ 次项，于是我们每次找到离 $m-[x^B]f$ 最近但小于等于它的位置 $w$，加入 $B-w$ 即可。发现进行 $15$ 次是个比较优秀的上界，随机出来的大数都能过。
  
若 $m$ 比较小，我们先对 $m\le 5\times 10^3$ 打表，而后随机测试发现 $m\ge 2\times 10^5$ 时才能稳定得出结果。
  
若 $5000<m<2\times10^5$，则考虑随机拿出拿出 $[1,500]$ 中的解数组 $a$，把上界从 $10^4\to 500$ 继续用上述算法即可。具体细节看代码。
  
事实上这样能在 $1s$ 跑过 $T=10^4$ 的多测，很优秀。

代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
#define int LL
namespace C
{
	int b[65],c[65];
	inline void add(int x)
	{
		for(int i=0;i<=60;i++) c[i]=b[i];
		for(int i=x;i<=60;i++) b[i]+=c[i-x];
	}
	inline int chk(int n,int *a)
	{
		memset(b,0,sizeof(b));memset(c,0,sizeof(c));b[0]=1;
		for(int i=1;i<=n;i++) add(a[i]);return b[60];
	}
}
const int N=1e6+5;
int n,a[65],v[N],L[5005],c[5005][65];
mt19937 rnd(time(0));
#define wr cout<<m<<"\n";for(int k=1;k<=m;k++) cout<<a[k]<<" "
inline void init()
{
	const int nn=1e5;int cnt=0;
	for(int j=1;j<=6;j++)
	{
		n=j*10;
		for(int T=1;T<=nn;T++)
		{
			for(int i=1;i<=n;i++) a[i]=rnd()%60+1;
			int t=C::chk(n,a);if(t>5000) continue;
			if(!v[t])
			{
				v[t]=1;L[t]=n;cnt++;
				for(int i=1;i<=n;i++) c[t][i]=a[i];if(cnt==5000) return;
			}
		}
	}
}
inline void sol(int ed)
{
	if(ed<=5000)
	{
		for(int i=1;i<=L[ed];i++) a[i]=c[ed][i]; 
		cout<<L[ed]<<"\n";for(int i=1;i<=L[ed];i++) cout<<a[i]<<" ";return;
	}
	int UP=(ed<=(2e5)?500:10000);
	for(int T=1,m,l;T<=1000000;T++)
	{
		if(!UP){l=rnd()%500+1;for(int i=1;i<=L[l];i++) a[i]=c[l][i];m=L[l];}
		else{for(int i=1;i<=20;i++) a[i]=rnd()%10+1;m=20;}
		if(C::chk(m,a)>=UP)
		{
			while(C::b[60]+C::b[59]<=ed) C::add(a[++m]=1);
			for(int j=1;j<=15;j++)
			{
				if(C::b[60]==ed){wr;return;}int w=0;
				for(int i=1;i<60;i++) if(C::b[i]+C::b[60]<=ed&&C::b[i]>C::b[w]) w=i;C::add(a[++m]=60-w);
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int ed;cin>>ed;(ed<=(2e5))&&(init(),1);sol(ed);
	return 0;
}

```

---

