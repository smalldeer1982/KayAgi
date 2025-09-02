# Make k Equal

## 题目描述

You are given the array $ a $ consisting of $ n $ elements and the integer $ k \le n $ .

You want to obtain at least $ k $ equal elements in the array $ a $ . In one move, you can make one of the following two operations:

- Take one of the minimum elements of the array and increase its value by one (more formally, if the minimum value of $ a $ is $ mn $ then you choose such index $ i $ that $ a_i = mn $ and set $ a_i := a_i + 1 $ );
- take one of the maximum elements of the array and decrease its value by one (more formally, if the maximum value of $ a $ is $ mx $ then you choose such index $ i $ that $ a_i = mx $ and set $ a_i := a_i - 1 $ ).

Your task is to calculate the minimum number of moves required to obtain at least $ k $ equal elements in the array.

## 样例 #1

### 输入

```
6 5
1 2 2 4 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
7 5
3 3 2 1 1 1 3```

### 输出

```
4```

# 题解

## 作者：syksykCCC (赞：9)

如果一个数组中已经有一种数 $\ge k$ 个了，那么答案一定是 $0$。

否则的话，显然我们最终要凑的数字一定是数组当中的一个数。

所以我们就可以枚举这个数。

数组先排个序，分三种情况，一种是只动左边，一种是只动右边，还有一种是两边都动。

如果只动前面，把 $a_1 \sim a_i$ 全部弄成 $a_i$ 需要多少步？

答案是 $i \cdot a_i- \sum\limits_{j=1}^{i}a_j$。

但是这样就一共有了 $i$ 个 $a_i$。如果 $i = k$，那么正好；如果 $i < k$，那么是不符合条件的；如果 $i > k$，可以发现，我们又浪费了一部分，即多了 $i - k$ 个，那么怎么办呢？很简单，让这 $i - k$ 个保持在 $a_{i} - 1$ 就好了，所以用：


$$i \cdot a_i- \left(\sum_{j=1}^{i}a_j\right) - (i - k)$$

来更新答案。

只动后面同理，条件是 $n - i + 1 \ge k$，用：

$$\left(\sum_{j=i}^{n}a_j \right)- (n - i + 1) \cdot a_i - \left((n - i + 1) - k\right)$$

来更新答案。

如果同时 $i<k$ 且 $n-i+1<k$，那么两边就都要动了，这时相等的数的个数恰好为 $n$，很显然，把上面两个式子拼起来即可，用：

$$i \cdot a_i- \left(\sum_{j=1}^{i}a_j\right) +\left(\sum_{j=i}^{n}a_j \right)- (n - i + 1) \cdot a_i - (n-k)$$

来更新答案。

$\sum\limits_{j=1}^{i}a_j$ 和 $\sum\limits_{j=i}^{n}a_j$ 可以预处理，所以时间复杂度是 $\mathcal O(n)$。

代码供参考。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, k, a[N], pre[N], suf[N], ans = LLONG_MAX, cnt[N];
signed main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
	for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[i];
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == a[i - 1]) cnt[i] = cnt[i - 1] + 1;
		else cnt[i] = 1;
		if(cnt[i] >= k) return puts("0") && 0;
	} 
	for(int i = 1; i <= n; i++)
	{
		if(i >= k) ans = min(ans, i * a[i] - pre[i] - (i - k));
		if(n - i + 1 >= k) ans = min(ans, suf[i] - (n - i + 1) * a[i] - (n - i + 1 - k));
		ans = min(ans, i * a[i] - pre[i] + suf[i] - (n - i + 1) * a[i] - (n - k));
	} 
	cout << ans << endl;
	return 0;
}
```

---

## 作者：WYXkk (赞：3)

首先排个序，不影响答案。

假如有一个数已经超过了 $k$ 个，那么可以直接输出 $0$ 结束了。

否则的话，我们来如下考虑：

首先，肯定是把所有数都放在某个本来就有的数处最优。

设 $pre_i$ 是 $a_i$ 的前缀和，$suf_i$ 是 $a_i$ 的后缀和，那么，把 $a_1,a_2,\cdots,a_i$ 全部变成 $a_i$ 的代价就是 $ia_i-pre_i$，而把 $a_i,a_{i+1},\cdots,a_n$ 都变成 $a_i$ 的代价是 $suf_i-(n-i+1)a_i$。

我们先考虑尽量只推一边过来，比如把最小的推过来，这个时候我们得到了 $i$ 个一样的数。

假如 $i\ge k$，那么我们发现我们好像多推了一些，因此我们可以把 $i-k$ 个放在 $a_i-1$ 处，此时代价便为 $ia_i-pre_i-(i-k)$。

否则，我们少推了一些，便还得把 $a_{i+1},\cdots,a_n$ 也推过来，此时代价就是 $(ia_i-pre_i)+(suf_i-(n-i+1)a_i)-(n-k)$。

把最大的推过来同理。对所有数取最小值即可。

（貌似可以贪心？反正没想过）

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const int N=200005;
ll a[N],pre[N],suf[N],cnt[N];
int main()
{
	int n,k;
	rd(n);rd(k);
	F(i,1,n) rd(a[i]);
	sort(a+1,a+n+1);
	F(i,1,n) pre[i]=pre[i-1]+a[i];
	F(i,1,n) pre[i]=a[i]*i-pre[i];
	UF(i,n,1) suf[i]=suf[i+1]+a[i];
	UF(i,n,1) suf[i]-=a[i]*(n-i+1);
	F(i,1,n) cnt[i]=(a[i]==a[i-1]?cnt[i-1]+1:1);
	ll ans=0x3f3f3f3f3f3f3f3f;
	F(i,1,n) if(cnt[i]>=k) {printf("0\n");return 0;}
	F(i,1,n)
	{
		if(i<k) ans=min(ans,pre[i]+suf[i]-(n-k));
		else ans=min(ans,pre[i]-(i-k));
		if(i>n-k+1) ans=min(ans,suf[i]+pre[i]-(n-k));
		else ans=min(ans,suf[i]-(n-i+1-k));
	}
	cout<<ans<<endl;
	return 0;
}	
```



---

## 作者：12345678hzx (赞：2)

## 题目大意
有一个长度是 $n$ 的数组，每次操作，你可以将最大的数减一，或将最小的数加一，求用多少次操作能使数组中有大于等于 $k$ 个数一样。
## 思路
首先，观察可得一个性质，$k$ 个数一样的肯定是数组中的一个数，否则容易证明答案不是最优的。

知道了这个性质后，我们就可以枚举这个数，对于每一个数，有三种情况，第一种是只用自增操作，第二种是只用自减操作，第三种是两种都用。

如果只用第一种操作，则答案为 $i \times a_i-\sum^i_{j=1}a_j$，只用第二种操作也同理。

第三种操作其实就类似前缀和拼后缀和，将第一二种情况拼起来就好了。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

long long n,k,a[200005],sum[200005],x[200005],y[200005],cnt,ans=1e18;
int main() { 
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(long long i=1;i<=n;i++) x[i]=x[i-1]+a[i];
	for(long long i=n;i;i--) y[i]=y[i+1]+a[i];
	for(long long i=1;i<=n;i++) {
		if(a[i]!=a[i-1]) sum[++cnt]=1;
		else sum[cnt]++;
		if(sum[cnt]>=k) {
			printf("0");
			return 0;
		}
	}
	for(long long i=1;i<=n;i++) {
		if(i>=k) ans=min(ans,i*a[i]-x[i]-(i-k));
		if(n-i+1>=k) ans=min(ans,y[i]-(n-i+1)*a[i]-(n-i+1-k));
		ans=min(ans,i*a[i]-x[i]+y[i]-(n-i+1)*a[i]-(n-k));
	} 
	printf("%lld",ans);
    return 0;
}
```

---

