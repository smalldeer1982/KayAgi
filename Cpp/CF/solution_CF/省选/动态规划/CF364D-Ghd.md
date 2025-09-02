# Ghd

## 题目描述

John Doe offered his sister Jane Doe find the gcd of some set of numbers $ a $ .

Gcd is a positive integer $ g $ , such that all number from the set are evenly divisible by $ g $ and there isn't such $ g' $ $ (g'>g) $ , that all numbers of the set are evenly divisible by $ g' $ .

Unfortunately Jane couldn't cope with the task and John offered her to find the ghd of the same subset of numbers.

Ghd is a positive integer $ g $ , such that at least half of numbers from the set are evenly divisible by $ g $ and there isn't such $ g' $ $ (g'>g) $ that at least half of the numbers from the set are evenly divisible by $ g' $ .

Jane coped with the task for two hours. Please try it, too.

## 样例 #1

### 输入

```
6
6 2 3 4 5 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
5 5 6 10 15
```

### 输出

```
5
```

# 题解

## 作者：Acestar (赞：15)

>**题意简述：**
>
>输入 $n\ (1≤n≤10^6)$ 及 $n$ 个整数 $a_1,a_2,...a_n\ (1≤a_i≤10^{12})$, 请从中取出 $\lceil \frac{n}{2} \rceil$ 个数，使得它们的 $gcd$ (最大公约数) 最大，输出最大的 $gcd$。

本题用到要随机化，需要随机化10次，再多就有可能 $T$ 了，这样出错的概率就是 $1-\frac{1}{2^{10}}$，也就是 $\frac{1}{1024}$，但是说实话这个概率真的不低，我第一次提交就 $WA$ 了。

每次随机化，从输入的数中取出一个数 $x$，然后进行因数分解，用 $d$ 数组**从小到大**存 $x$ 的因数，再用 $cnt_i$ 表示输入的 $n$ 个数中有几个数含有因数 $d_i$，最后直接**从大到小**判断每个 $d_i$，如果 $cnt_i×2≥n$，也就是含有 $d_i$ 这个因数的数的个数 $≥\lceil \frac{n}{2} \rceil$ 那么 $d_i$ 就是最终要求的答案。

在求 $cnt_i$ 时，要把 $n$ 个数枚举一遍，每次找到 $gcd(x,a_i)$ 在 $d$ 数组中的位置 $pos$ 然后 $cnt_{pos}++$。

```cpp
for(int i=1; i<=n; i++)
{
	int pos=lower_bound(d+1,d+1+siz,gcd(x,a[i]))-d;	//找到d数组中第一个>=gcd(x,a[i])的数的位置。
	cnt[pos]++;
}
```

做完这个之后，还要知道如果 $d_j\mod d_i=0$，那么 $cnt_i+=cnt_j$，因为上一步我们只对 $gcd$ 进行了计数，然而我们要对每个因数进行计数。

最后，题目上提到建议使用`%I64d`，我也不太清楚这个，应该是只能在`Windows`上用，但是不用应该也没关系，用 $long\ long$ 就可以了。

代码~~应该还算简洁~~

```cpp
#include<iostream>
#include<cstdio>
#include<time.h>
#include<stdlib.h>
#include<cmath>
#include<algorithm>
#include<cstring> 
#define ll long long

using namespace std;

const int maxn=1e6+10;
int n,siz;
ll d[maxn],a[maxn],cnt[maxn];

ll gcd(ll x,ll y)	//最大公因数 
{
	return !y?x:gcd(y,x%y);
}

int random(int l,int r)	//在l~r的范围内随机化取数 
{
	return (ll)rand()*rand()%(r-l+1)+1;
}

void divide(ll x)	//对x进行分解因数 
{
	siz=0;
	for(ll i=1; i*i<=x; i++)
		if(x%i==0)
		{
			d[++siz]=i;
			if(x/i!=i) d[++siz]=x/i;
		}
}

int main()
{
	srand(time(NULL));	//随机化种子 
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%I64d",&a[i]);
	ll ans=0;
	for(int cas=1; cas<=10; cas++)
	{
		ll x=a[random(1,n)];
		divide(x);
		sort(d+1,d+1+siz);	//排序，这样才能用二分 
		memset(cnt,0,sizeof(cnt));
		for(int i=1; i<=n; i++)
		{
			int pos=lower_bound(d+1,d+1+siz,gcd(x,a[i]))-d;	//找到d数组中第一个>=gcd(x,a[i])的数的位置。
			cnt[pos]++;
		}
		for(int i=1; i<=siz; i++)
			for(int j=i+1; j<=siz; j++)
				if(d[j]%d[i]==0)
					cnt[i]+=cnt[j];
		for(int i=siz; i>=1; i--)
			if(cnt[i]*2>=n)	//第一个符合题意的，同时也是最大的 
			{
				ans=max(ans,d[i]);
				break;
			}
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：KSkun (赞：5)

本题解同步发布在我的博客：[[CF364D]Ghd 题解 | KSkun's Blog](https://ksmeow.moe/ghd_cf364d_sol/)，欢迎来逛~

# 题解
参考资料：[CFR 364 D. Ghd ( Random, Math ) - 0w1](http://h0rnet.hatenablog.com/entry/2017/04/28/CFR_364_D__Ghd_%28_Random%2C_Math_%29)

随机化的题目，直接求显然不好办，n的数据范围看着就吓人，直观感觉像$O(n \log n)$。

我们知道这个数字一定是这个数列中某个数的因数，因此我们需要选择一个数求它与其他数的最大公因数。这些公因数中的一个就是答案。求一遍公因数是$O(n \log n)$的。

对于求出来的公因数，我们去从大到小找一个会成为超过一半数的因数的数字。具体做法是，选择一个因数，去找比它大的因数，如果它能整除大因数，说明大因数对应的数字也可以被这个数整除，应当把加到这个数的计数上。这个过程直观看上去是$O(n^2)$的，但是实际上我们不会对比当前最优解还小的因数计算，并且当计数超过n的一半的时候就可以停止计数并计入答案，在这样的处理下我们可以让这个计数的时间变得可接受。

答案肯定是这些数字中超过一半数的因数，因此每一次随机找到正确解的概率超过0.5。我们考虑重复找解的过程多次，这里我使用10次（超过10次似乎会TLE 18）。

# 代码
```cpp
// Code by KSkun, 2018/3
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include <map>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1;
	char c = fgc();
	while(c < '0' || c > '9') {
		if(c == '-') neg = -1;
		c = fgc();
	}
	while(c >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		c = fgc();
	}
	return res * neg;
}

const int MAXN = 1000005;

inline LL gcd(LL a, LL b) {
	LL t;
	while(b) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int n;
LL a[MAXN];

int main() {
	srand(time(NULL));
	n = readint();
	for(int i = 1; i <= n; i++) {
		a[i] = readint();
	}
	LL ans = 1;
	for(int rep = 1; rep <= 10; rep++) {
		int rnd = (rand() * RAND_MAX + rand()) % n + 1;
        // 下面我们需要处理出a[rnd]和其他数的gcd，答案可能就是这些gcd中的一个，map里first存gcd，second存该gcd的出现次数
		std::map<LL, int> fact;
		for(int i = 1; i <= n; i++) {
			LL t = gcd(a[i], a[rnd]);
			if(!fact.count(t)) fact[t] = 1;
			else fact[t]++;
		}
        // 从大到小来判断每个gcd是否能成为答案
		std::map<LL, int>::iterator it = fact.end();
		do {
			it--;
			if((*it).first <= ans) continue;
			int cnt = 0;
            // 能被当前答案整除的因数对应的原数肯定能够被当前答案整除，统计能被当前答案整除的数字个数
			for(std::map<LL, int>::iterator it1 = it; it1 != fact.end() && cnt << 1 < n; it1++) {
				if(!((*it1).first % (*it).first)) {
					cnt += (*it1).second;
				}
			}
            // 如果能被当前答案整除的数字个数比一半多，当前答案还比已经得到的最优解更优，那么更新最优解
			if(cnt << 1 >= n) ans = (*it).first;
		} while(it != fact.begin());
	}
    // CF推荐I64d输出long long
	printf("%I64d", ans);
	return 0;
}
```

---

## 作者：过往梦魇之殇 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF364D)

随机化 ~~（入门题）~~

**解题思路：**

随机从集合中抽取十次（出错概率为$1/1024$）

每次将抽出来的数进行因式分解，将约数从小到大存储入$num$数组中；

再用$cnt$数组存储每个约数出现个数，从大到小看，如果$cnt_i>=n/2$，那么$num_i$就是要求的最终要求的答案。

其他具体细节看代码实现。

**代码展示：**

```cpp
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<complex>
#include<climits>
#define re register
#define in inline
#define pi acos(-1.0)
#define inf 2147483640
#define cd complexdouble
using namespace std;
in int read()
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
in void write(int X)
{
    if(X<0)putchar('-'),X=-X;
    if(X>=10)write(X/10);
    putchar(X%10+'0');
}
const int maxn=1e6+10;
int n,a[maxn],ans,tot,num[maxn],cnt[maxn];
int gcd(int x,int y){
	if(!y){
		return x;
	}
	return gcd(y,x%y);
}
void fenjie(int x){
	tot=0;
	for(re int i=1;i*i<=x;++i){
		if(x%i==0){
			num[++tot]=i;
			if(x/i!=i){
				num[++tot]=x/i;
			}
		}
	}
}
int main()
{
	n=read();
	for(re int i=1;i<=n;++i){
		a[i]=read();
	}
	for(re int T=1;T<=10;++T){
		memset(cnt,0,sizeof(cnt));
		int x=a[rand()%n+1];
		fenjie(x);
		sort(num+1,num+tot+1);
		for(re int i=1;i<=n;++i){
			int qwq=lower_bound(num+1,num+tot+1,gcd(x,a[i]))-num;
			++cnt[qwq];
		}
		for(re int i=1;i<=tot;++i){
			for(re int j=i+1;j<=tot;++j){
				if(num[j]%num[i]==0){
					cnt[i]+=cnt[j];
				}
			}
		}
		for(re int i=tot;i>=1;--i){
			if(2*cnt[i]>=n){
				ans=max(ans,num[i]);
			}
		}
	}
	write(ans);
    return 0;
}
```

> $Thanks$ $For$ $Watching!$

---

## 作者：Milmon (赞：2)

[Milmon Page 链接：https://molmin.github.io/problem?id=35#solution](https://molmin.github.io/problem?id=35#solution)

考虑令一个数一定选择，那么我们枚举它的因数，对每个是因数倍数的数进行统计，判断是否存在一个数量 $\geq\dfrac n2$ 即可。

时间复杂度：找出所有因数 $\Theta(n)$，排序 $\Theta(n\log n)$，统计 $\Theta(n+d^2(n))$，总时间复杂度 $\Theta(n\log n+d^2(n))$。

那么随机选取 $x$ 个数如上计算，由于每个数不被选中的概率是 $\dfrac 12$，故这样的随机化算法有 $\dfrac 1{2^x}$ 的概率出错。那么 $x$ 取到 $12$ 左右即可 AC。

由于这里 $n$ 最大到 $10^6$，直接使用 `rand()` 容易挂，改为 `((long long)rand()<<31)|rand()` 较为保险。

[Code 链接：https://molmin.github.io/problem?id=35#code](https://molmin.github.io/problem?id=35#code)

---

## 作者：FjswYuzu (赞：2)

观看题目范围。我们似乎并没有什么优秀并且正确的算法。仔细读了一下 $\operatorname{ghd}$ 的定义：

> （翻译后）序列中有**一半**的数能够整除的最大的数。


这个一半大有用途。既然是一半，我们任选一个数中间的某个因子作为 $\operatorname{ghd}$，出现正确答案的概率就是 $\dfrac{1}{2}$。多做几次（比如 $10$ 次）就能使错误率大幅度降低。

于是我们 $O(\sqrt n)$ 去分解因数，然后通过 dp 转移能够被这个数的因数整除的数有多少，我们就能够计算了。设这个数有 $k$ 个因数，dp 的时间复杂度就是 $O(k^2)$ 的。

时间复杂度 $O(p(\sqrt n +k^2))$，其中 $p$ 是你选择的数的个数，$k$ 定义如上。

注意到，`rand()` 是非常愚蠢的。我们采用 C++11 的 `random` 库生成随机数即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-')  f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
    return x*f;
}
void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int n,a[1000005],ghd=1;
int fac[1000005],cnt,rear[1000005],cot[1000005];
signed main(){
    srand(time(NULL));
    default_random_engine e(rand());
    n=read();
    uniform_int_distribution<int> range(1,n);
    for(int i=1;i<=n;++i)   a[i]=read();
    for(int p=1;p<=min(10ll,n);++p)
    {
        memset(fac,0,sizeof fac);
        memset(cot,0,sizeof cot);
        cnt=0;
        int tmp=a[range(e)];
        for(int i=1;i*i<=tmp;++i)
        {
            if(tmp%i==0)
            {
                fac[++cnt]=i;
                if(tmp/i!=i)    fac[++cnt]=tmp/i;
            }
        }
        sort(fac+1,fac+1+cnt);
        for(int i=1;i<=n;++i)
        {
            rear[i]=lower_bound(fac+1,fac+1+cnt,gcd(a[i],tmp))-fac;
            ++cot[rear[i]];
        }
        for(int i=1;i<=cnt;++i)	for(int j=i+1;j<=cnt;++j)	if(fac[j]%fac[i]==0)	cot[i]+=cot[j];
        for(int i=cnt;i;--i)	if(2*cot[i]>=n)	ghd=max(ghd,fac[i]);
    }
    write(ghd);
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

容易发现对于每个数，均有至少一半的概率在所求子集内。

随机钦定若干个数，每次假设这个数在子集内，求出其所有因子是多少个原序列数的因子。如果大于一半与答案取 $\max$。

错误率是 $(\frac{1}{2})^k$，其中 $k$ 为选出数个数。本题中使用 $10$ 即可通过。

一个小细节是，直接对于每个因子和每个数比时间复杂度会炸。求出每个数与钦定的数的 $\gcd$ 后做一遍高维前缀和即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
mt19937 rng(time(0));
int a[1000005],n;
int prm[1000005],top=0;
unordered_map<int,int> cnt;
int maxv;
void qry(int val){
	int oval=val;
	vector<int> vc;
	for(int i=1;i*i<=val;i++){
		if(val%i==0){
			vc.push_back(i);
			if(i!=val/i) vc.push_back(val/i);
		}
	}
	cnt.clear();
	sort(vc.begin(),vc.end()); reverse(vc.begin(),vc.end());
	top=0;
	for(int i=2;i*i<=val;i++){
		if(val%i==0){
			prm[++top]=i;
			while(val%i==0) val/=i;
		}
	}
	if(val!=1) prm[++top]=val;
	for(int i=1;i<=n;i++){
		cnt[__gcd(oval,a[i])]++;
	}
	for(int j=1;j<=top;j++){
		for(auto v:vc){
			if(v%prm[j]==0){
				cnt[v/prm[j]]+=cnt[v];
			}
		}
	}
	for(auto v:vc){
		if(cnt[v]>=(n+1)/2) maxv=max(maxv,v);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
	for(int j=1;j<=10;j++){
		int pos=rng()%n+1;
		qry(a[pos]);
	}
	cout<<maxv;
	return 0;
}
```

---

## 作者：Meteor_ (赞：1)

# CF364D Ghd 题解

## 题目大意

给定一个长度为 $n$ 的序列 ，你需要从中选出一个元素个数不少于 $\left\lceil{\frac{n}{2}}\right\rceil$ 的子序列，使得这个子序列中所有元素的 $\gcd$ 最大。

## 分析

数据范围吓人。

$10^6$，但是根本想不到什么 $O(n \log n)$ 或 $O(n)$ 的算法。然后就开始想其他技巧。

刚开始想的是什么 $\gcd$ 的性质，但是显然没有什么结果（我赛时就想到这里，然后寄了）。

注意到子序列元素个数比较大，可能比较容易从这入手，所以我们进一步从 $\left\lceil{\frac{n}{2}}\right\rceil$ 这里分析。

## 题解

既然我们选至少一半，那么就意味着每一个数都有 $\frac{1}{2}$ 的几率被选进最终答案的子集。我们可以考虑随机枚举几个数，假设我们枚举了 $m$ 个数，那么至少有一个数在答案的子集里的概率为 $1 - \frac{1}{2^m}$。这个概率其实蛮大的。

然后我们去想对于每一个枚举的数，我们怎么算可能的答案。

如果这个数在最终的子集里，那么意味着最终的 $\gcd$ 一定是这个数的一个因数。所以我们考虑枚举这个数的所有因数，然后算每个因数在原序列中的出现位置，最后从大到小找到第一个出现次数大于等于 $\left\lceil{\frac{n}{2}}\right\rceil$ 的数，并与我们最终的 $ans$ 取 $\max$。

实现方面的话，记 $cnt_i$ 表示第 $i$ 个因数在原序列中出现的次数。我们先对所有因数排序，然后从 $1$ 到 $n$ 枚举原序列的数，与我们当前随机出来的数求 $\gcd$，求出来以后在存因数的那个数组里 $\operatorname{lower\_bound}$ 找（二分也行），使其 $cnt + 1$。但是这样明显是不对的，因为如果两个数的 $\gcd$ 为 $3$，那么不仅 $3$ 的出现次数加一，$6, 9$ 这一类数的出现次数也会多一次。所以我们最后求完 $cnt$ 后再枚举一遍因数那个数组，然后对于每个因数 $i$，再去枚举一遍小于它的因数 $j$，如果 $i \bmod j = 0$，那么令 $cnt_i$ 加上 $cnt_j$，这才是最终的 $cnt$。

总时间复杂度 $O(n \log d + d^2)$ 差不多。$d$ 代表因数个数，其实蛮小的，对于 $10^{12}$ 以内的数，最多的因数个数也才 $6720$。$m$ 就是我代码里的 $T$，我取的 $10$，一发 AC 了，$3.5s$，没什么问题。

## 代码

如果你能看懂我用的随机化更好，看不懂就用普通的 $rand()$ 函数就行。

```cpp
#include <bits/stdc++.h>
#define int long long
#define M 1000005
#define mod 1000000007
#define time() chrono::system_clock::now().time_since_epoch().count()

using namespace std;

inline int read() {
    int x = 0, s = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')
            s = -s;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * s;
}

void write(int x) {
    if(x < 0)  {
        x = ~(x - 1);
        putchar('-');
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}

int n, a[M], ans, d[M >> 2], cnt[M >> 2];

signed main() {
    n = read();
    for(int i = 1; i <= n; ++ i)
        a[i] = read();
    int T = 10;
	default_random_engine e;
	uniform_int_distribution<int> Z(1, n);
	srand(time());
	e.seed(rand());
    for(int t = 1; t <= T; ++ t) {
        int r = Z(e);
        int len = 0;
        int x = a[r];
        int sq = sqrt(x);
        for(int i = 1; i <= sq; ++ i)
            if(x % i == 0)
                d[++ len] = i, cnt[len] = 0, d[++ len] = x / i, cnt[len] = 0;
        if(sq * sq == x)
            -- len;
        stable_sort(d + 1, d + 1 + len);
        for(int i = 1; i <= n; ++ i)
            ++ cnt[lower_bound(d + 1, d + 1 + len, __gcd(x, a[i])) - d];
        for(int i = 1; i <= len; ++ i)
            for(int j = i + 1; j <= len; ++ j)
                if(d[j] % d[i] == 0)
                    cnt[i] += cnt[j];
        for(int i = len; i >= 1; -- i) {
            if(cnt[i] * 2 >= n) {
                ans = max(ans, d[i]);
                break;
            }
        }
    }
    write(ans);
}

/*
10
1 2 3 4 5 6 7 8 9 10
*/
```

---

## 作者：541forever (赞：1)

# CF364D

因为其要求此集合大小至少为一半，因此当我们随机一个 $a_i$ 时，它有二分之一的概率处于此集合中。那么，若它处于此集合中，则答案一定是它的约数之一，跟根据下面这张表
![](https://cdn.luogu.com.cn/upload/image_hosting/deen64zm.png)

我们知道值在 $10^{12}$ 次方以内的数最多有 $6720$ 个约数，我们随机一个数 $a_i$ 后，先将其所有约数存下来，再算出其每个约数作为其它数约数的次数，判断是否大于 $\lceil {n \over 2} \rceil$。但我们不能暴力算每个约数作为其他数约数的出现次数，实现时，我们可以先算出其他数与 $a_i$ 的 $\gcd$，设其为 $g$，在 $g$ 上打上加一的标记并在最后一起算，若一个约数的出现次数大于 $\lceil {n \over 2} \rceil$，则将其与当前的答案取 $\max$，时间上大概可以支持你随 $12$ 次左右，正确性为 ${1\over 2^{12}}$，交上 $1,2$ 次便能通过。

[Code](https://codeforces.com/contest/364/submission/216698589)

---

## 作者：tzc_wk (赞：1)

> #### Codeforces 364D

> 题意：给出一个大小为 $n$ 的可重集合 $S$，定义 $ghd(S)=\max gcd(S')\ (S' \subset S,|S'| \geq \frac{n}{2})$，$gcd(S)$ 为 $S$ 中所有数的最大公约数。

> $1 \leq n \leq 10^6$，$1 \leq a_i \leq 10^{12}$

一道谔题

题目看起来似乎无法用一般的方法解出来。不过仔细观察可以发现，每个数有 $\frac{1}{2}$ 的概率被选中。那么我们不难想到随机化。我们随机化 $10$ 次左右，这样出错的概率就会变成 $1-\frac{1}{2^{10}}$，就基本上可以 AC 了。

至于每次随机化就随便挑选出一个数，枚举它的所有因子 $x$，然后判断最多能够挑选的集合的大小是否超过 $S$ 的一半，如果超过就更新答案。

代码：

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),a[1000005],b[1000005],cnum,ans=0;
pii f[1000005];
inline void solve(){
	cnum=0;
	int t=(rand()*RAND_MAX+rand())%n+1;
	fz(i,1,n)	b[i]=__gcd(a[t],a[i]);
	sort(b+1,b+n+1);
	fz(i,1,n){
		if(b[i]!=b[i-1]){
			f[++cnum].fi=b[i];
			f[cnum].se=0;
		}
		f[cnum].se++;
	}
	fz(i,1,cnum){
		fz(j,1,i-1){
			if(f[i].fi%f[j].fi==0){
				f[j].se+=f[i].se;
			}
		}
	}
	fz(i,1,cnum){
		if(f[i].se>=(n+1)/2){
			ans=max(ans,f[i].fi);
		}
	}
}
signed main(){
	srand(993244853);
	fz(i,1,n)	a[i]=read();
	int M=11;
	while(M--)	solve();
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Limit (赞：1)

玄学题... ... ...~~数论题... ... ...~~

题面给出了Ghd的定义..大概就是一个数列中超过一半的数的gcd的最大值...

看起来就像二分...但没有找出单调性

那就要拿出万能的随机化了

大概随机个10次,错误率大概就只有1/1000了QAQ

```cpp
#include<bits/stdc++.h>
using namespace std;
const int randomsum=10;//随机十次
unsigned long long seed1,seed2;
void randomize(unsigned long long c,unsigned long long b)//自己写的随机化模板
{
    seed1=c+b;
    seed2=b*c%468562482981;//膜一个不知道是啥的数
}
unsigned long long random()//某dalao用的随机数方法
{
    seed1^=seed2<<12;
    seed2^=seed1>>9;
    seed1^=seed2<<6;
    seed2^=seed1<<12;
    seed2^=seed1<<3;
    seed1=~seed1;
    seed2=~seed2;
    seed1^=seed2^=seed1^=seed2;
    return seed1;
}
long long gcd(long long a,long long b)//gcd
{
    if(b==0)return a;
    return gcd(b,a%b);
}
long long llmax(long long a,long long b)//long long取max
{
    if(a>b)return a;else return b;
}
long long num[1000005];
int N;
long long a[1000005],b[1000005],c[1000005],answer=1,half;
void solve()
{
    long long QAQ=num[(int)(random()%N+1)];//随机一个序列中的数
    int i,j;
    for(i=1;i<=N;i++)
    a[i]=gcd(num[i],QAQ);//所有数都和这个数取一次gcd
    sort(a+1,a+N+1);//拍一遍序
    int top=0;
    for(i=1;i<=N;i++)//去重,并记录个数
    {
        if(a[i]!=a[i-1])
        {b[++top]=a[i];c[top]=0;}
        c[top]++;
    }
    long long sum=0,now=-1;
    for(i=1;i<=top;i++)//枚举answer
    {
        sum=0;
        for(j=1;j<=top;j++)
        if(b[j]%b[i]==0)sum+=c[j];
        if(sum>=half)now=b[i];//判断answer是否成立
    }
    answer=llmax(answer,now);//与最终答案取大值
}
int main()
{
    randomize(time(0),time(0));//随机初始化
    scanf("%d",&N);
    int i;
    a[0]=-1;
    half=(N+1)/2;//一半的大小
    for(i=1;i<=N;i++)
    scanf("%lld",&num[i]);
    for(i=1;i<=randomsum;i++)
    solve();
    printf("%lld",answer);
    return ~0;//QAQ
}
```
//因为CF的数据有一百多....1023^100/1024^100大约0.9
所以有大约10%的概率会错...如果是WA而不是TLE可以再交几次试试


---

## 作者：Loser_Syx (赞：0)

首先明确一点，如果一个数是 Ghd，那么在长度为 $n$ 的数组内至少有 $\lceil\frac{n}{2}\rceil$ 个数是它的倍数。换而言之，随机选一个数他的因子包含 Ghd 的概率是 $\frac{1}{2}$。

自然地想到随机 $t$ 个 $a_i$，那么都不包含 Ghd 作为因子的概率只有 $\frac{1}{2^t}$，当 $t$ 较大时错误率就会很小。

那么现在就转化成了，对于每个 $a_i$ 枚举它的因子，判断是否满足条件，但是朴素的 $O(tn\sqrt {a_i})$ 比较拙劣，可以考虑把每个大因子的答案传给小因子，这样复杂度变成了 $O(t\sqrt{a_i}+t\times d^2(a_i))$，其中 $d(a_i)$ 表示 $a_i$ 的因子个数。

[code](https://codeforces.com/contest/364/submission/304343159)。

---

## 作者：Arghariza (赞：0)

做法大同小异，但不知道为啥我跑这么慢而且还容易被卡。/kk

由于这题看上去和概率一点关系都没有并且 CF 标签中有 `probabilities`，不难想到随机。

由于答案子集大小至少为 $n$ 的一半，我们每次随机一个数 $a_i$，它在最终答案集合里的概率为 $\frac{1}{2}$。然后接下来我们考虑硬点 $a_i$ 在答案集合里面的最大可能 $\gcd$。

注意到此时答案一定为 $a_i$ 的因数，不超过 $6720$ 种。所以我们可以直接枚举 $a_i$ 的因数 $d$，然后统计包含这个因数 $d$ 的 $a_j$ 的个数，如果个数 $\ge \frac{n}{2}$ 就更新答案。注意到 $d\mid a_j,d\mid a_i\Leftrightarrow d\mid \gcd(a_i,a_j)$，并且 $\gcd(a_i,a_j)\mid a_i$，于是只需要对 $\gcd(a_i,a_j)$ 开 `unordered_map` 就可以统计出包含某个因数 $d$ 的 $a_j$ 的个数，复杂度为 $O(d^2(a_i))$。

所以总复杂度为 $O(T(n\log A+d^2(A)))$，$A$ 为值域。取 $T=20$ 有大概率通过，因为我被卡常了，所以手写哈希替换 `unordered_map`。

```cpp
// Problem: Ghd
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF364D
// Memory Limit: 250 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define pb emplace_back
#define mt make_tuple
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

mt19937 rnd(time(0));
const int N = 1e6 + 100;
const int K = 1e7 + 7;

int n, tot, tote, hd[K], c[N];
ll mx, a[N], vl[N], s[N];
struct ed { int to, nxt; ll w; } e[K];
vector<int> pos;

int gt(ll x) {
	int p = x % K; pos.pb(p);
	for (int i = hd[p]; i; i = e[i].nxt)
		if (e[i].w == x) return e[i].to;
	vl[++tot] = x, e[++tote] = (ed) { tot, hd[p], x }, hd[p] = tote;
	return tot;	
}

ll calc(ll x) {
	for (int i : pos) hd[i] = 0;
	for (int i = 1; i <= tot; i++) c[i] = s[i] = vl[i] = 0;
	tot = tote = 0, pos.clear();
	for (int i = 1; i <= n; i++) c[gt(__gcd(a[i], x))]++;
	for (int i = 1; i <= tot; i++)
		for (int j = 1; j <= tot; j++)
			if (vl[i] % vl[j] == 0)
				s[j] += c[i];
	ll res = 0;
	for (int i = 1; i <= tot; i++)
		if (s[i] >= (n + 1) / 2) res = max(res, vl[i]);
	return res;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) 
		cin >> a[i], mx = max(mx, a[i]);
	ll res = 0;
	for (int T = ((mx <= 1e7) ? 21 : 12); T; T--) 
		res = max(res, calc(a[rnd() % n + 1]));
	cout << res << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

输入 $n\ (1≤n≤10^6)$ 及 $n$ 个整数 $a_1,a_2,...a_n\ (1≤a_i≤10^{12})$, 请从中取出 $\lceil \dfrac{n}{2} \rceil$ 个数，使得它们的 $\gcd$ 最大，输出最大的 $\gcd$。

# 题目分析

随机在 $a$ 集合中选取一个数 $x$，求出 $x$ 的所有因数，升序放在 $p$ 数组中。令 $cnt[i]$ 表示 $a$ 集合中有几个数的因数含有 $p[i]$。所以在集合 $p$ 中二分预处理，$\mathcal{O(m^2)}$ 迭代出（$m$ 是因数个数） $cnt$ 数组不难（但是复杂度较高），处理结束后，若存在 $cnt[i]*2\ge n$ 则更新答案即可。

通过测试可以发现随机 $11$ 次不行最多 $10$ 次（当然是越多越好）。

至于随机化，`rand` 值域太小，虽然可以通过相乘的方式处理但是我们有更方便的写法：`mt19937` $\&$ `uniform_int_distribution<int>`。语法见代码。

# 代码

```cpp
//2022/4/17
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>
#define int long long
#define Rand uniform_int_distribution<int>
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int N = 1e6 + 5;
int a[N],p[N],cnt[N];//cnt[i]:a 集合中有几个数的因数含有 p[i] 
int n,idx;
inline int gcd(int a,int b) {
	return b == 0 ? a : gcd(b,a % b);
}
inline void solve(int x) {
	idx = 0;
	for (register int i = 1;i * i <= x; ++ i) {
		if (x % i == 0) {
			p[++ idx] = i;
			if (i * i != x) p[++ idx] = x / i;
		}
	}
	sort(p + 1,p + idx + 1); 
}
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	mt19937 rand(time(0));
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	int ans = 0;
	for (register int cas = 1;cas <= 10; ++ cas) {
		mst(cnt,0);
		Rand now(1,n);
		int x = a[now(rand)];
		solve(x);
		for (register int i = 1;i <= n; ++ i) {
			int at = lower_bound(p + 1,p + idx + 1,gcd(x,a[i])) - p;
			cnt[at] ++;
		}
		for (register int i = 1;i <= idx; ++ i) {
			for (register int j = i + 1;j <= idx; ++ j) {
				if (p[j] % p[i] == 0) {
					cnt[i] += cnt[j];
				}
			}
		}
		for (register int i = idx;i >= 1; -- i) {
			if (cnt[i] * 2 >= n) {
				ans = max(ans,p[i]);
				break;
			}
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：0)

[Ghd](https://www.luogu.com.cn/problem/CF364D)

由于要求数量超过一半，因此可以考虑随机化，每次有 $\dfrac{1}{2}$ 的概率正确。

具体实现时，先将随机的数的因数存下来，记为 $d_i$。

记 $m_i=\gcd(a_i,x)$，则 $pos_i$ 为 $\min_i(m_i\le d_i)$，令 $cnt_i$ 为 $i$ 在 $\gcd$ 中的出现次数，初始时 $cnt_{pos_i}=1$,（这一过程类似离散化），$cnt_i=\sum_{d_i|d_j}cnt_j$，直接转移即可。

我们取阈值 $w=10$，错误概率为 $2^{-10}$。

[Code](https://netcut.cn/p/4b5131ee0f7a47c3)

---

## 作者：Lumos壹玖贰壹 (赞：0)

#### ~~神奇~~随机化
###### ~~靠脸过题~~

##### Problem
给n个数($a[i]$)，要从中选出$\lceil {n \over 2} \rceil$个数,求它们的gcd的最大值
##### Soloution
普通想法很难有做法，因为最后要选的数较多，考虑随机化

1. 我们rand一个数x，那么它在最终答案里的概率$\ge{1\over2}$。
2. 将x分解因式(因为最后$\lceil{n\over2}\rceil$个数的的gcd一定是x的因子)记在num[ ]里，把num[ ]快排一下保证升序。
3. 开一个cnt[i]表示x的第i个因子是多少个数的因子。求出x与$a_i$的gcd，找到对应的$num_i$，在$cnt_i+1$
4. **注意：** num中的数并不一定互质，相反，合数因子一定是由小合数因子和质数构成的。但我们之前只在最大公因数的cnt中加了1。所以，如果$nun_i$是$num_j$的因数，那么$cnt_i$+=$cnt_j$;
5. 从大到小枚举x的每个因子。如果$cnt_i*2\ge n$，那么$ans=max(ans,num_i)$
6. 再rand一次(总共rand十次)

**强调：因为rand自身缺陷(数据范围)，最后一个点可以被卡掉(带种子也没用)，所以取rand的时候用rand×rand%n+1**

本人被卡掉了10次，改了后过了。如果有问题欢迎指出

##### Code
```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
ll n,a[1000005],num[1000005],cnt[1000005],tot=0;
inline ll rd(){
	ll res=0,f=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=1;
	for(;isdigit(ch);ch=getchar()) res=(res<<3)+(res<<1)+ch-48;
	return f?-res:res;
}
inline void work(ll x){
	tot=0;
	for(ri i=1;i<=sqrt(x)+1;i++){
		if(x%i==0){
			num[++tot]=i;
			if(i*i!=x) num[++tot]=x/i;
		}
	}
}
ll gcd(ll a,ll b){
	if(!b) return a;
	return gcd(b,a%b);
}
int main(){
	srand(time(NULL));
	n=rd();
	for(ri i=1;i<=n;i++) a[i]=rd();
	ll ans=0;
	for(ri j=1;j<=10;j++){
		memset(cnt,0,sizeof(cnt));
		int p=rand()*rand()%n+1;
		work(a[p]);
		sort(num+1,num+tot+1);
		for(ri i=1;i<=n;i++)
			cnt[lower_bound(num+1,num+tot+1,gcd(a[i],a[p]))-num]++;
		for(ri i=1;i<=tot;i++)
			for(ri j=i+1;j<=tot;j++)
				if(num[j]%num[i]==0) cnt[i]+=cnt[j];
		for(ri i=tot;i>=1;i--)
			if(cnt[i]*2>=n){
				ans=max(ans,num[i]);
				break;
			}
	}
	printf("%lld\n",ans);
	return 0;
}

```
完结撒花

---

