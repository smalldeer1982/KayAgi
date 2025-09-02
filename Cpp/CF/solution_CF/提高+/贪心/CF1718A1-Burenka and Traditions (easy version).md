# Burenka and Traditions (easy version)

## 题目描述

This is the easy version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55```

### 输出

```
2
2
0
2
4
7
4```

# 题解

## 作者：Zeardoe (赞：10)

题意：现有 $a$ 数组。每次你可以选择一个区间 $[l,r]$ 和一个整数 $x$ ，花费 $\lceil \frac{(r-l+1)}2\rceil$ 的代价，将其中所有数与 $x$ 取异或。问：至少需要多少代价，才能使 $a$ 数组所有元素均为 $0$ ？

观察：本题关键在于，其实只有两种基本操作（拆操作，找操作的本质）：

选择一个元素，将它异或上 $x$。
选择连续的两个元素，将它们异或上 $x$。
**每次操作的代价为 $1$**（好性质）

其余所有操作均可由以上基本操作组成，且代价不会升高。

分析：对于一个数组，一个上界是 $n$，也就是对每个元素都执行第一个操作。
另外，对于一串 $a_l \oplus ... \oplus a_r = 0$ 的 $[l,r]$，连续执行第二种操作可以省去一次操作过程。

因此，我们可以通过把序列划分成若干个孤点和若干个**极短的**异或为 $0$ 的连续子串，如：
```plain
11
27 27 34 32 2 1822 31 23 56 52 4
```
划分为
```
[27,27] [34,32,2] 1822 [31,23,56,52,4]
```

每划分一个子串，都可以减少 $1$ 的答案。

怎么找子串呢？上一个子串的结尾及其之前的数均不可再次包含在另一个子串中，对于上一个子串的结尾之后的数（在寻找范围内），（假设第一个数的下标为 $1$），我们用 map 记录其前缀异或和，若区间 $[l,r]$ 的异或和为 $0$，那么区间 $[1,l]$ 的异或和等于 $[1,r]$ 的异或和，也就是在计算出 $r$ 的前缀异或和的时候发现 map 中有此数据，那么就代表找到了一个这样的子串。

注意 $0$ 的代价为 $0$，应该立刻划分成孤点。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    //think twice,code once.
    //think once,debug forever.
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int ans = n;
        map<int, int> mp;
        mp[0] = 1;
        int tmp = 0;
        f(i, 1, n) {
            int a; cin >> a; tmp ^= a;
            if(mp.count(tmp)){
                ans--; mp.clear(); mp[0] = 1; tmp = 0;
            }
            else {
                mp[tmp] = 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1HB4y1L7qy)

### 2 思路

本题解按照困难难度撰写。

设 $dp_i$ 为解决从 $1$ 到 $i$ 所需要的时间。$dp_0=0$。

可以发现，若 $a_i=0$，$dp_i=dp_{i-1}$。

否则可以单独操作 $a_i$。$dp_i=dp_{i-1}+1$。

但是我们可以考虑另外一种情况。

设 $sum_i$ 为 $i$ 的前缀异或和。可以发现，如果 $sum_i=sum_l$ 且 $0\le l<i$，那么从 $a_{l+1}$ 到 $a_i$ 可以通过操作 $i-l-1$ 次来全部变成 $0$。具体来讲，是 $[l+1,l+2],[l+2,l+3],...,[i-1,i]$ 的操作。

那么 $dp_i$ 可以被更新为 $dp_l+i-l-1$。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
#define max_n 100000
#define inf 0x3f3f3f3f
int t;
int n;
int a[max_n+2];
int dp[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1718A2_1.in","r",stdin);
	freopen("CF1718A2_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int i=1;i<=n;++i)dp[i]=inf;
		dp[0]=0;
		map<int,int>r;
		for(int i=1,sum=0,l;i<=n;++i){
			if(!a[i]){
				dp[i]=dp[i-1];
				r[sum]=i;
				continue;
			}
			dp[i]=min(dp[i],dp[i-1]+1);
			sum^=a[i];
			if(r.count(sum)){
				l=r[sum];
				dp[i]=min(dp[i],dp[l]+(i-l-1));
			}
			else{
				if(!sum)dp[i]=min(dp[i],i-1);
			}
			r[sum]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/84141619)

By **dengziyue**

---

## 作者：_Lazy_whr_ (赞：0)

显然贪心。

每次的代价是是区间长度除以 $2$ 再向上取整，也就是说每一步只会是取当前这个位置或是向后一个。

那么最坏情况下，操作次数会是 $n$，考虑如何将多余步骤减去。

容易发现，当一个区间 $[L, R]$ 满足 $a_L \oplus a_{L + 1} \oplus a_{L + 2} \oplus ... \oplus a_{R - 1} \oplus a_R = 0$ 时，就可以由每两个数进行一次操作 $2$，由此减少一次操作。

然而异或可以用前缀来维护，所以每一次发现当前的前缀和与之前有相等就相当于找到了起点，记录答案即可。

[AC Link](https://codeforces.com/problemset/submission/1718/309058550)

---

## 作者：FireRain (赞：0)

# 思路

首先可以将题目的操作转化为：

1. 将一个数 $a_i$ 异或一个常数 $k$。

2. 将连续两个数 $a_i,a_{i + 1}$ 同时异或一个常数 $k$。

那么，你发现最坏情况下，操作次数是 $n$。那么考虑如何将多余步骤给减去。

发现，如果一个区间 $[l,r]$，$\oplus_{i = l}^{r}a_i = 0$，就可以由每两个数进行一次操作 2，进而减少一次操作。

然后使这种区间的数量尽可能多即可。用 `map` 记录，简单贪心一下就好。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,ans,arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int cnt = 0;
    map<int,bool> vis;
    n = ans = read(); vis[0] = true;
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= n;i++){
        cnt ^= arr[i];
        if (vis[cnt]){
            vis.clear(); vis[0] = true;
            ans--; cnt = 0;
        }
        else vis[cnt] = true;
    }
    printf("%d\n",ans);
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

既然是贪心题，那么就不卖关子了，直接上困难版做法了。

一看到怎么有特色的花费，我们就要考虑一下了。很显然可以知道 $2n,2n-1$ 长的区间的花费是一样的。进一步地，$a(2n)+b(2n)$ 和 $(a+b)(2n)$（此次省略乘号）的花费也是一样的。于是我们就可以把各种操作变成两个基本操作的组合。

- 操作 $1$：选择一个长度为 $2$ 的区间操作，费用为 $1$。

- 操作 $2$：选择一个长度为 $1$ 的区间操作，费用为 $1$。

这固然是一个很好的开端。可是我们接下来该怎么样呢？难道我们要贪心地选择长度为 $2$ 的区间操作吗？可是我们的操作是把区间内的数都异或一个 $x$，贪心的选择长度为 $2$ 的区间操作，不代表和选择长度为 $1$ 的区间的操作数和一样。

换一个说法，就是对于一个区间 $[l,r]$，如果我们只执行操作 $2$，那么一定可以保证执行 $r-l+1$ 次后全 $0$，但是如果是执行了操作 $1$ 呢？要想执行的操作数小于 $r-l+1$ 貌似是一种很**特殊的情况**。

继续想下去，我们也许会想得很复杂……实际上，我们只有一种贪心的方法，那就是抓住上面的**特殊情况**来考虑。那就是对于区间 $[l,r]$，如果请假内的异或和为 $1$，那么我们就可以执行 $r-l$ 次操作 $1$ 而不是执行 $r-l+1$ 次操作 $2$。并且这样一定保证两种情况的结果都是区间 $[l,r]$ 的数字全变成了 $0$（我们分别对 $(l,l+1),(l+1,l+2),\dots,(r-1,r)$ 执行操作 $1$）。

提一下，如果区间 $[l,r]$ 的异或和为 $0$，且这个区间可以划分为若干个异或和为 $0$ 的子区间，那么我们选择继续划分。想想就知道了，因为每一个异或和为 $0$ 的区间都实际上可以减少一次我们的操作。

注意有一些数无论在哪个区间内都不可以使得异或和为 $0$，我们把这些数字单独提出来执行操作 $2$。对于 $0$，我们也单独提出来，不操作（但是不可以删去）。

---

那么怎么样找到异或和为 $0$ 的区间呢？我们知道异或和加法在前缀累计方面很像。记前缀异或和数组为 $qz$，若 $qz_r=qz_l$，那么说明 $[l+1,r]$ 的异或和就是 $0$。用 map 匹配实现即可，若学过 BSGS，就马上会明白（没错非常喜欢 BSGS 虽然有时比喻不当）。

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
const int INF=1e18+5;
const int MOD=998244353;

int n,ans;

signed main() {
    int t=rd;
    while(t--) {
        map<int, int> mp;
        
    	n=ans=rd;
        mp[0] = 1;
        int qz = 0;//前缀异或和
        for(int i=1;i<=n;i++) {
            int a=rd;
			qz^=a;
            if(mp[qz]){
                ans--; 
				mp.clear(); 
				mp[0] = 1; qz = 0;
            }
            else mp[qz] = 1;
        }
        cout<<ans<<endl;
    }
    return 0;
}

```




---

## 作者：ricky_lin (赞：0)

[更好的阅读体验](https://www.cnblogs.com/rickylin/p/CF1718.html#cf1718a-burenka-and-traditions)

我们显然可以发现我们只用考虑进行区间长度为 $1$ 或者 $2$ 的操作（其他情况下，可以由长度为 $1$ 和 $2$ 的区间等价拼得）。

我们又发现，正常情况下显然操作次数为 $n$，那什么时候才能减少操作次数呢？

- 我们发现，一个长为 $k$ 的异或和为 $0$ 的区间显然只需要 $n-1$ 个长度为 $2$ 的区间解决，代价是 $n-1$ 的。

然后我们就可以每次找到极小的异或和为 $0$ 的区间的个数，最后答案即为 $n-k$。

备注：**"极小"**  意为不和其他的异或和为 $0$ 的区间有交集。

如何找这些区间呢，异或和为 $0$ 区间 $[l,r]$ 显然有一个性质：$l-1$ 的前缀和 和  $r$ 的前缀和相等。

基于这个性质，我们可以在 `map/set` 里面存放所有的前缀和，如果前缀和在之前出现过那么就有一个这样的区间，每次成功匹配后将 `map/set` 清空即可(为了满足**极小**)。

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 1e5 + 8;
int T,n;
int a[NN];
int pre[NN];

void solve(){
	set<int> s;
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	s.insert(0);
	int ans = n;
	for(int i = 1; i <= n; ++i){
		pre[i] = pre[i-1] ^ a[i];
		if(s.count(pre[i])){
			--ans;
			s.clear();
			pre[i] = 0;
		}
		s.insert(pre[i]);
	}
	printf("%d\n",ans);
}

int main(){
	scanf("%d",&T);
	while(T--){
		solve();
	}
}
```

---

