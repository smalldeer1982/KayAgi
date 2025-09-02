# [POI 2017] Reprezentacje ró?nicowe

## 题目描述

给定一个数列 $a$：
- 当 $n\le 2$ 时，$a_n=n$。
- 当 $n>2$，且 $n$ 是奇数时， $a_n=2\times a_{n-1}$。
- 当 $n>2$，且 $n$ 是偶数时，$a_n=a_{n-1}+r_{n-1}$。

其中 $r_{n-1}= \operatorname{mex}(|a_i-a_j|)(1\le i\le j\le n-1)$， $\operatorname{mex} \left\{ S\right\}$ 表示最小的不在 $S$ 集合里面的非负整数。

数列 $a$ 的前若干项依次为：

$1,2,4,8,16,21,42,51,102,112,224,235,470,486,972,990,1980$。

可以证明，对于任意正整数 $x$，只存在唯一一对整数 $(p,q)$ 满足 $x=a_p-a_q$，定义为 $\operatorname{repr}(x)$。

比如 $\operatorname{repr}(17)=(6,3)$，$\operatorname{repr}(18)=(16,15)$。
现有 $n$ 个询问，每次给定一个正整数 $x$，请求出 $\operatorname{repr}(x)$。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5$，$1\le x\le 10^9$。

## 样例 #1

### 输入

```
2
17
18```

### 输出

```
6 3
16 15```

# 题解

## 作者：木xx木大 (赞：7)

### [P5968 [POI2017]Reprezentacje ró?nicowe](https://www.luogu.com.cn/problem/P5968) 

~~第一眼，不会。看完题解，这是个sb题，我是sb~~

仔细观察题面可以发现，每出现两个数，就会有一次$\times 2$ 的操作，所以 $10^9$ 以内的数不会超过 $2 \log10^9$个。对于大小超过 $10^9$ 的数，奇数位和前一项偶数位的差也大于 $10^9$ ，因此能组成题目要求的 repr 函数的只有偶数项和前一位奇数项。

所以我们可以暴力打出 $10^9$ 以内的数（实际上只有56项）。查询时，如果在前面56项里查到了就输出。否则需要二分，在表里找到最大的小于它的数。因为 $r$ 是递增的，如果当前 $x$ 代表了一个 $r_i$，也就意味着前面的 $x-1$ 个数都已经被代表了。又因为表里有 $num$ 个，这是前56项里有的。那么 $x-num$ 就是从56项后的第几个数对有这样一个差 $x$ 。每一个数对2个数，又因为这样的计算包含了最后差等于 $x$ 的那个数对，所以答案就是$(56+(x−num)\times 2，56+(x−num)\times2−1)$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
map<ll,pair<int,int> > s;
map<ll,pair<int,int> >::iterator it;
ll a[110],b[10010];
const ll INF=1e9;
int main()
{
	int q,n,cnt=0;
	scanf("%d",&q);
	a[1]=1,a[2]=2;
	s[1]=make_pair(2,1);
	for(n=3;;n++)
	{
		if(n&1)a[n]=a[n-1]<<1;
		else for(int i=1;;i++)
		{
			if(!s.count(i))
			{
				a[n]=a[n-1]+i;
				break;
			}
		}
		for(int i=1;i<n;i++)
			s[a[n]-a[i]]=make_pair(n,i);
		if(!(n&1)&&a[n]>INF)break;
	}
	for(it=s.begin();it!=s.end();it++)
		b[++cnt]=it->first;
	while(q--)
	{
		int x;
		scanf("%d",&x);
		if(s.count(x))
			printf("%d %d\n",s[x].first,s[x].second) ;
		else 
		{
			int y=lower_bound(b+1,b+cnt+1,x)-b-1;
			printf("%d %d\n",n+(x-y)*2,n+(x-y)*2-1);
		}
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：1)

## 题目分析

这是一道思维题，很考察细节。

先说下正解的算法是打表+二分，可以先去观察下题目在继续阅读。

细节 $1 \le x \le 10^9$，这表明询问的差只有 $10^9$，然而对于奇数的操作可以直接翻倍，偶数也只增不减，不难想到很快差就爆 $10^9$ 了。

既然差到 $10^9$ 级别，那绝对是相邻两个数的差，不然差就超过 $10^9$ 了。

不妨先暴力求出序列前面的部分，记录差值，如果之前求过就直接用，否则二分位置再处理。

**注意：显然偶数增加会更小，所以要等是偶数且大于 $10^9$ 时停止暴力。**

## 重点代码

打表：

```cpp
a[2]=1+(a[1]=1),mp[1]={2,1};
for(i=3;;i++){
    if(i&1)
        a[i]=a[i-1]*2;
    else for(int j=1;;j++)
            if(!mp.count(j)){
                a[i]=a[i-1]+j;//求 r
                break;
            }
    for(int j=1;j<i;j++)
        mp[a[i]-a[j]]={i,j};//记录
    if((i&1)==0&&a[i]>inf)//爆了而且是在偶数
        break;
}
```

查询：

```cpp
if(mp.count(x))
    cout<<mp[x].first<<' '<<mp[x].second<<'\n';//之前记录
else{
    int pos=lower_bound(a+1,a+tot+1,x)-a-1;//二分求值
    cout<<i+(x-pos)*2<<' '<<i+(x-pos)*2-1<<'\n';//往后推、差是一
}
```

**注意：笔者在查询之前把差记录在了 $a$ 数组中，查询代码中 $a_i$ 就是第 $i$ 小的差**。

---

## 作者：jiangly (赞：1)

#### 题意

给定数列 $[a_1,a_2,\ldots]$，其递归定义为：$a_1=1$, $a_2=2$, $a_{2n+1}=2a_{2n}$, $a_{2n+2}=a_{2n+1}+r_n$，其中 $n\ge 1$，$r_n$ 是最小的不能表示为 $a_1,a_2,\ldots,a_{2n+1}$ 中两项的差的正整数。可以证明，任意一个正整数都能唯一的表示为数列 $a$ 中两项的差 $a_p-a_q$。给定 $n$ ($1\le n\le 10^5$) 个正整数 $x$ ($1\le x\le 10^9$)，求出这个表示。

#### 题解

由于 $a_{56}=1062283805$, $a_{57}=2a_{56}$，在这之后所有不超过 $10^9$ 的差都是 $a_{2n+2}-a_{2n+1}$ 的形式。那么求出所有 $1\le q<p\le 56$ 的答案，所有不在这些当中的数会以 $a_{58}-a_{57},a_{60}-a_{59},\ldots$ 的形式依次出现。因此每次询问二分即可。

#### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
constexpr int A[] = {0, 1, 2, 4, 8, 16, 21, 42, 51, 102, 112, 224, 235, 470, 486, 972, 990, 1980, 2002, 4004, 4027, 8054, 8078, 16156, 16181, 32362, 32389, 64778, 64806, 129612, 129641, 259282, 259313, 518626, 518658, 1037316, 1037349, 2074698, 2074734, 4149468, 4149505, 8299010, 8299049, 16598098, 16598140, 33196280, 33196324, 66392648, 66392693, 132785386, 132785432, 265570864, 265570912, 531141824, 531141876, 1062283752, 1062283805};
std::vector<std::tuple<int, int, int>> ans;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (int i = 1; i <= 56; ++i)
        for (int j = 1; j < i; ++j)
            if (A[i] - A[j] <= 1e9)
                ans.emplace_back(A[i] - A[j], i, j);
    std::sort(ans.begin(), ans.end());
    int t;
    std::cin >> t;
    while (t--) {
        int x;
        std::cin >> x;
        int k = std::lower_bound(ans.begin(), ans.end(), std::make_tuple(x + 1, 0, 0)) - ans.begin() - 1;
        auto [y, p, q] = ans[k];
        if (x != y) {
            p = 2 * (x - k + 27);
            q = p - 1;
        }
        std::cout << p << " " << q << "\n";
    }
    return 0;
}

```



---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

这道题有性质。

我们注意到，$a$ 数组的增长和 $2^n$ 同阶，显然不会让我们求出来之后优化。

那么，我们仔细想象一下 $repr(v)$ 对应的两个数都有哪些情况，显然有两大类：$p=q+1$ 和 $p>q+1$。

对于第一种情况，他就是 $r_{\dots}$。具体是什么我们不需要关心，因为根据题目中告诉我们的性质，它是用来填充第二种情况漏掉的数的。

对于第二种情况，$a_p$ 一定是比 $a_q\times2$ 更大的，毕竟 $p$ 至少比 $q$ 大 $2$，中间一定会有奇数项，乘一个 $2$。也就是说 $a_p-a_q>a_q$。

我们又注意到，$x\le10^9$，也就是说，当 $a_q>10^9$，其后面的一定不可能再通过第二类来填数了。就纯靠第一类填空。而第一类正好每两个数填一个数。因此可解。

我们只需要浅推一下其位置就行了。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif
inline int read() {
	int r = 0; char c = getchar_unlocked();
	while (c < '0' || c>'9') c = getchar_unlocked();
	while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = getchar_unlocked();
	return r;
}
inline void write(long long x) {
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 ^ 48);
}
inline void writi(long long args) {
	write(args); putchar_unlocked(10);
}
constexpr bool online = 0;
int n, m, a[1000005], sm;
signed main() {
	if (online)
		freopen("Podzielno.in", "r", stdin),
		freopen("Podzielno.out", "w", stdout);
	ios::sync_with_stdio(0);
	n = read(); m = read();
	for (int i = 0;i < n;++i)
		a[i] = read(), sm += a[i] * i;
	sm %= (n - 1); if (sm) a[sm]--;
	for (int i = 1;i <= n;++i) a[i] += a[i - 1];
	for (int i = 1, p;i <= m;++i)
		p = read(), p++, cout << ((a[n] >= p) ?
			(lower_bound(a, a + n, p) - a) : (-1)) << '\n';
	return 0;
}
//私は猫です
```

---

## 作者：lyhqwq (赞：0)

# Solution

首先观察，注意到一个非常重要的性质，数列存在乘二的操作，这预示着数列会增长的非常快速。

我们将数列的前 60 项打表，观察到数列在 57 项及以后任意相邻的由乘二操作得到的两项之差都大于 $10^9$ 。所以如果两项之差不是由前 56 项得到的，那么就一定是相邻的两项，且是 mex 。

我们考虑将前 56 项两两之差扔进 set 里，每次询问查询是否存在，如果存在暴力的去找。

否则我们二分找到 set 里最大的小于 $x$ 的数的下标 $y$，如果 x 作为新的 mex ，那么 $[1,x-1]$ 内的数一定都存在，而 set 内存在 $y$ 项，所以 56 项后有 $x-y$ 对 mex ，答案为 $
(56+2(x-y),56+2(x-y)-1)$ 。

# Code

极其丑陋。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
struct node{
	int v,p,q;
};
int n;
int a[N];
map<int,int> mp;
set<int> s;
vector<int> vec;
int mex(int x){
	for(int i=1;i<=x;i++) for(int j=1;j<=i;j++) mp[a[i]-a[j]]=1;
	for(int i=1;;i++) if(!mp[i]) return i;
}
void solve1(int x){
	for(int i=1;i<=56;i++) for(int j=1;j<i;j++) if(a[i]-a[j]==x) return printf("%lld %lld\n",i,j),void();
}
void solve2(int x){
	int y=lower_bound(vec.begin(),vec.end(),x)-vec.begin();
	printf("%lld %lld\n",56+2*(x-y),56+2*(x-y)-1);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=56;i++){
		if(i<=2) a[i]=i;
		else if(i&1) a[i]=a[i-1]*2;
		else a[i]=a[i-1]+mex(i-1);
	}
	for(int i=1;i<=56;i++) for(int j=1;j<i;j++) if(a[i]-a[j]<=1e9) s.insert(a[i]-a[j]);
	for(set<int>::iterator it=s.begin();it!=s.end();it++) vec.push_back(*it);
	while(n--){
		int x;
		scanf("%lld",&x);
		if(s.find(x)!=s.end()) solve1(x);
		else solve2(x);
	}
	return 0;
}

```

---

