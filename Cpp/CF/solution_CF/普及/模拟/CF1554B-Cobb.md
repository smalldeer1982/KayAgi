# Cobb

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ and an integer $ k $ . Find the maximum value of $ i \cdot j - k \cdot (a_i | a_j) $ over all pairs $ (i, j) $ of integers with $ 1 \le i < j \le n $ . Here, $ | $ is the [bitwise OR operator](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 说明/提示

Let $ f(i, j) = i \cdot j - k \cdot (a_i | a_j) $ .

In the first test case,

- $ f(1, 2) = 1 \cdot 2 - k \cdot (a_1 | a_2) = 2 - 3 \cdot (1 | 1) = -1 $ .
- $ f(1, 3) = 1 \cdot 3 - k \cdot (a_1 | a_3) = 3 - 3 \cdot (1 | 3) = -6 $ .
- $ f(2, 3) = 2 \cdot 3 - k \cdot (a_2 | a_3) = 6 - 3 \cdot (1 | 3) = -3 $ .

So the maximum is $ f(1, 2) = -1 $ .

In the fourth test case, the maximum is $ f(3, 4) = 12 $ .

## 样例 #1

### 输入

```
4
3 3
1 1 3
2 2
1 2
4 3
0 1 2 3
6 6
3 2 0 0 5 6```

### 输出

```
-1
-4
3
12```

# 题解

## 作者：¶凉笙 (赞：6)

## [题解] CF1554B Cobb

> [传送门](https://www.luogu.com.cn/problem/CF1554B)

### 题意

给出一个长度为 $n$ 的数列，求出 $i\times j-k\times (a_i|a_j)$ 的最大值。

### 解题报告

严格做法其它题解已经讲的很明白了，来一个玄学做法。

考场上就感觉这个东西肯定不是全扫过一遍的。

我们可以把结果分成两项来看：$i\times j$ 和 $k\times (a_i|a_j)$。

我们希望前一部分尽量大，后一部分尽量小，考虑到 **一个数按位或上另一个数数值不会减小**，所以如果当前答案 $ans\leq i\times (i-1)-k\times a_i$，那么就没必要往前扫描找到最大值。

否则的话，往前扫描更新 $ans$。

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T>
inline T read(){
	T x=0;char ch=getchar();bool fl=false;
	while(!isdigit(ch)){if(ch=='-')fl=true;ch=getchar();}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
	}
	return fl?-x:x;
}
#define read() read<int>()
#define LL long long
const int maxn = 1e6 + 10;
int T,n;
LL a[maxn],ans,k;
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	T=read();
	while(T--){
		ans=-0x7fffffffffffffff;
		n=read();k=read<LL>();
		for(int i=1;i<=n;i++)a[i]=read<LL>();
		for(int i=n;i>1;i--){
			if(ans<1LL*i*(i-1)-k*a[i]){
				for(int j=i-1;j>=1;j--)ans=max(ans,1LL*i*j-k*(a[i]|a[j]));
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：5)

这道题是一个思维题。

我们可以发现，$i\times j$ 最大可以是 $n^2$ 级别的，而 $k$ 最大只有 $100$，$a_i$ 最大只有 $n$，这两个数的异或不会超过 $2\times n$。也就是说，后面减去的数最大只有 $200\times n$ 这个级别的。

所以 $i$ 和 $j$ 越大，产生最大值的概率就会越大。

因为 $n^2$ 的增长速度 比 $200\times n$ 的增长速度要快得多，所以我们只用枚举后面的 $200$ 个左右的数字，就可以求出答案了。

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[1000010];

int main()
{
    int T;
    cin >> T;
    while (T --)
    {
        int n, k;
        scanf ("%d%d", &n, &k);
        for (int i = 1; i <= n; i ++)
            scanf ("%lld", &a[i]);
        int pass = max(1, n - 248);
        long long ans = -100000000000000LL;
        for (int i = n; i >= pass; i --)
            for (int j = n; j >= pass; j --)
                if (i != j)
                    ans = max(ans, 1LL * i * j - k * (a[i] | a[j]));
        cout << ans << endl;
    }
    return 0;
}

```


---

## 作者：NXYorz (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF1554B)

---------
### 题目大意
给定序列 $a_n$ 和 $k$, 其中 $0 \le a_i \le n$。
令 $1\le i < j \le n$, 最大化 $i \times j - k \times (a_i | a_j)$。

--------
### 分析
发现 $ i\times j \le j\times (j - 1)=j^2-j,0\le a_i|a_j \le2n$。

固定 $j$, 考虑什么样的 $i$ 可以对答案做出贡献。

先找一个中间值，当 $i=j-1$ 时，$i \times j - k \times (a_i | a_j) \ge j\times (j-1)=j^2 - j - k\times 2n$

放缩一下: $i \times j - k \times (a_i | a_j) \le i\times j $

令 $i\times j \ge j^2 - j - k\times 2n$, 方程两边同时除以 $j$，得到 $i \ge j - 1 - \dfrac{k\times 2n}{j}\ge j-1-2k$
 
所以对于一个 $j$ ,只有符合 $j-1-2k\le i < j$ 的 $i$ 才会有可能对答案做出贡献。

复杂度 $O(nk)$。

---
### $\texttt{Code}$

```cpp
#include<cstdio>

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const ll inf = 1LL << 62;

int t,n,k;
int a[N];

inline ll max(ll x , ll y)
{return x > y ? x : y;}

void work()
{
    scanf("%d%d",&n,&k);
    for(int i = 1; i <= n; i++)
        scanf("%d",&a[i]);
    ll ans = -inf;
    for(ll j = 1; j <= n; j++)
        for(ll i = max(1 , j - 2 * k); i < j; i++)
            ans = max(ans , i * j - k * (a[i] | a[j]));
    printf("%lld\n",ans); return;
}

int main()
{
  //  freopen("aa.in","r",stdin);
    scanf("%d",&t);
    while(t--) work();
}
```

---

## 作者：Computer1828 (赞：3)

观察两项的值域。

$i\cdot j \in [2,n(n-1)]$

$k\cdot (a_i \texttt{ or } a_j) \in [0,2kn]$

前者在 $i$ 和 $j$ 较大时远大于后者。

假如把 $i$ 和 $j$ 放到 $n-1$ 和 $n$，那么此时最小的答案应该是 $n(n-1) - 2kn = n^2-2kn-n$，这里记为 $s$。

再假如把 $j$ 放到 $n$，若此时的 $i$ 可以更新 $s$，即 $in-0 = in > s = n^2-2kn-n$，解得 $i > n-2k-1$，也就是 $i\geq n-2k$。

所以只需让 $i$ 和 $j$ 在 $[n-2k,n]$ 暴力就行，复杂度 $O(Tk^2)$。

---

## 作者：wind_whisper (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1554B)  
## Description
给定一个长度为 $n$ 的数列 $a_{1...n}$ 和 $k$，求 $\max i \times j-k\times (a_i | a_j)$  .
$n\leq 10^5,k\leq \min(n,100)$.
## Solution
注意到，$k$ 很小，而 $a_i|a_j$ 的大小不超过 $2n$ ，所以答案应该不小于 $n\times(n-1)-2nk$.  
顺着这个思路走，可以发现，对于一个固定的 $i$，其可能转移为最大答案的 $j$ 应该是很有限的.
形式化的，应该有：
$$i\times (n-j)\leq 2nk$$
左边是由于 $j$ 变小，前面的乘积会损失的量，显然不应该超过 $2nk$.  
移一下项，就有：
$$(n-j) \leq \frac{2nk}{i}$$
那么我们枚举 $i$，再枚举 $j$，枚举的总次数就不会超过：
$$\sum_{i\leq n} \frac{2nk}{i}=kn \log_2{n}$$
可以通过.  
（上面只是我们分析最差复杂度的过程，代码中当 $i\times j \leq ans$ 就直接跳出就行了）
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=1e9+7;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,k;
ll a[N];
ll mx;
inline ll calc(int i,int j){
  return 1ll*i*j-1ll*k*(a[i]|a[j]);
}
int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    n=read();k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    mx=calc(n-1,n);
    for(int i=1;i<=n;i++){
      for(int j=n;j>i&&1ll*i*j>mx;j--){
	//printf("%d %d\n",i,j);
	mx=max(mx,calc(i,j));
      }
    }
    printf("%lld\n",mx);
  }
  return 0;
}

```



---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/problemset/problem/1554/B)

比赛结束后问了大半圈都没有看到有和我做法一样的。

我大概是比赛时唯一用 dp 做的人吧。虽然最后数组开小挂了两发就是了。

cf 前半小时来篇题解加 rp，希望这场 div2 可以上橙。

##### 题意：

给定长度为 $n$ 的非负整数序列 $a$ 还有常数 $k$，试找出 $\max\{i\,\times j-k(a_i | a_j) \mid i<j\}$ 的值。

其中 $\mid$ 被定义为二进制下的或运算。

Data range：$1\le a_i \le 10^5,k \le 100$。

##### 分析：

虽然明眼人都知道 $k \le 100$ 是关键，但是这题确实存在

**不依赖 $k$，理论上可以在 $O(nm\log n)$ 的时间内拓展到选的是 $m$ 个数** 的解法。

容易尝试枚举 $a_i | a_j$ 的值 $val$。确定了值以后，我们就需要找到最大的一对下标 $i,j$，满足 $a_i | a_j = val$。

考虑这个东西是不好计算的，但是考虑一个事情，如果我们设 $f(S)$ 是 $a$ 中二进制位**被 $S$ 包含**的元素最大的两个下标。我们枚举所有 $f(S)$ 构成的点对，那么答案一定在这些点对里面。

考虑对其进行证明：对于一对点对 $(x,y)$ 而言，它们一定会被 $f(x | y)$ 考虑到，而就算有 $f(v > (x|y))$ 考虑到了它们，由于我们求的是最大值，也一定不会影响答案。

然后考虑快速计算 $f$，这里利用了类似 sos dp 的技巧，首先初始化每个 $f(a_i)$，然后从小往大枚举，对于每个 $x$，枚举 $x$ 中未出现的二进制位，加上以后得到新的状态 $y$ 然后用 $f(x)$ 更新 $f(y)$。考虑这其实是一个类似归并排序的过程，所以如果我们是选 $m$ 个数，理论上可以做到 $O(m)$ 合并答案。本题可以忽略合并常数。复杂度显然是 $O(n \log n)$ 的。

最后枚举 $val$ 的过程就是 trival 的了。

也不知道有没有讲明白，赛场上莫名想到这个做法，比赛开始了半小时才通过，但是代码非常简单。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=1e5+10,MAXL=(1<<18)+10,LIM=(1<<18);
ll T,n,k,a[MAXN],ans=-1e18,tmp[5];
pi f[MAXL];
void update(pi& p1,pi p2){
	tmp[0]=p1.fr;tmp[1]=p2.fr;tmp[2]=p1.se;tmp[3]=p2.se;
	sort(tmp,tmp+4);
	p1.fr=tmp[3];
	if(tmp[2]!=tmp[3])p1.se=tmp[2];
	else if(tmp[1]!=tmp[3])p1.se=tmp[1];
	else p1.se=tmp[0];
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		rep(i,1,n){
			cin>>a[i];
		}
		ans=-1e18;
		rep(i,0,Min(LIM,n*3)){
			f[i]=mp(-1e9,-1e9);
		}
		/*
		rep(i,0,3){
			printf("%lld %lld")
		}
		*/
		rep(i,1,n){
			update(f[a[i]],mp(i,-1e9));
		}
		rep(i,0,Min(LIM,n*3)){
			rep(j,0,17){
				if(i&(1<<j))continue;
				if((i|(1<<j))> 3*n)continue;
				int k=(i|(1<<j));
				update(f[k],f[i]);
			}
		}
		rep(i,0,Min(LIM,n*3)){
			if(f[i].fr==-1e9 || f[i].se==-1e9)continue;
			ans=Max(ans,(ll)f[i].fr*f[i].se-k*i);
		}
		cout<<ans<<endl;
	}
	

	return 0;
}
/*
4
3 3
1 1 3
*/
```

---

## 作者：Zhl2010 (赞：0)

## 题目概括

给定长度为 $n$ 的序列 $a$ 和一个正整数 $k$，求出 $\max(i\cdot j-k\cdot(a_i \operatorname{or} a_j))$。

## 思路

首先想到暴力，但肯定要 `TLE`。

我们先将原式拆分成两个部分，$i\cdot j$ 和 $k\cdot(a_i \operatorname{or} a_j)$。

我们想要 $i\cdot j$ 大，$k\cdot(a_i \operatorname{or} a_j)$ 小。

看看数据范围，$k \le 100$，且 $0 \le a_i \le n$，所以 $k\cdot(a_i \operatorname{or} a_j)$ 不会超过 $200 \cdot n$。

但是 $i\cdot j$ 可能会很大，所以我们让 $i$ 和 $j$ 在 $n$ 到 $\max(1,n-250)$ 之间（应该是 $n-200$，但这样把稳），因为再小就不是最优情况了。

所以用上述方法时间复杂度正确，能过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[1000010];
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,k;
		cin>>n>>k;
		for (int i=1;i<=n;i++)scanf("%lld",&a[i]);
		long long ans=-LONG_LONG_MAX;
		for (int i=n;i>=max(1ll,n-250ll);i--){
			for(int j=n;j>=max(1ll,n-250ll);j--){
				if (i!=j){
					ans=max(ans,i*j-k*(a[i]|a[j]));
				}
			}
		}  
		cout<<ans<<endl;
	}
	return 0;
}
```

---

