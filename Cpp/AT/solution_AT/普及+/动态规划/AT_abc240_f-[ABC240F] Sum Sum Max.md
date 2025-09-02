# [ABC240F] Sum Sum Max

## 题目描述

有三个数列 $A,B,C$。

其中 $C$ 表示为 $ x_1,\ \dots,\ x_N,\ y_1,\ \dots,\ y_N $ 的形式，意思是前 $y_1$ 个数为 $x_1$,之后 $y_2$ 个数为 $x_2$……最后 $y_N$ 个数为 $x_N$。

$B$ 为 $C$ 的前缀和数组。

$A$ 为 $B$ 的前缀和数组。

求 $A$ 中最大值。

## 说明/提示

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ \sum\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^9 $
- $ |x_i|\ \leq\ 4\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ y_i\ \gt\ 0\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ \sum_{k\ =\ 1}^N\ y_k\ =\ M $

## 样例 #1

### 输入

```
3
3 7
-1 2
2 3
-3 2
10 472
-4 12
1 29
2 77
-1 86
0 51
3 81
3 17
-2 31
-4 65
4 23
1 1000000000
4 1000000000```

### 输出

```
4
53910
2000000002000000000```

# 题解

## 作者：appear_hope (赞：4)

极值：区间的最值

最大值一定是极值，但极值不一定是最大值。

贪心：对于每一段的极大值，我们为了让极大值尽可能的大，令 $i$ 为当前下标，则可以想到当 $B_i \ge 0$ 时，这一段的极大值一定包括 $i$，当 $B_i < 0$ 时，这一段的极大值不包含 $i$，而对于每一段的 $B_i$ 是单调递减或单调递增或不变，所以使用二分找到当前段的最后一个 $B_i \ge 0$ 的位置。

令 $S_i$ 表示前 $i$ 段的综合，$j$ 为当前点到第 $i$ 段的开头的距离。

$$B_i = S_{i - 1} + j \times x_i$$

$$A_i = A_{i - 1} + y_i \times B_i + \frac{(y_i + 1) \times y_i}{2} \times x_i$$

注意细节：

每一段的开头和结尾也可以是这一段的极大值，注意二分细节当 $i = 1$ 时必须选择一个点。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 5;

int T;
pair<ll, ll> a[N];
ll n, m, x, y, b[N];

void Solve(){
  cin >> n >> m;
  ll sum = 0, ans = LLONG_MIN;
  for(int i = 1; i <= n; i++){
    cin >> a[i].first >> a[i].second;
    if(i == 1){
      ans = a[i].first;
    }
    b[i] = b[i - 1] + a[i].first * a[i].second;
  }
  for(int i = 1; i <= n; i++){
    int l = 0, r = a[i].second;
    while(l < r){
      int mid = (l + r + 1) >> 1;
      b[i - 1] + 1ll * mid * a[i].first >= 0 ? l = mid : r = mid - 1;
    }
    if(b[i - 1] + 1ll * l * a[i].first >= 0 && (i == 1 && l > 1 || i > 1)){
      ans = max(ans, sum + b[i - 1] * l + 1ll * (l + 1) * l / 2 * a[i].first);
    }
    sum += b[i - 1] * a[i].second + (1 + a[i].second) * a[i].second / 2 * a[i].first;
    ans = max(ans, sum);
  }
  cout << ans << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for(cin >> T; T--; Solve()){
  }
  return 0;
}

```

---

## 作者：Expert_Dream (赞：2)

这个要做两个前缀和。

$C$ 题目已经给出，那么我们可以跟据他来求 $B$。

首先，我们可以把 $C$ 看成 $n$ 个组，每一组要不是正数要不是负数，所以导致 $B$ 在一段区间内不断增加或者不断减少，而且每一段连续增加或者连续减少的段数也只有 $n$。

然而 $A$ 却又因为 $B$ 的数值来进行增加或减少。

再来看 $B$，它的每一段同符号的区间数量只有 $2\times n$。（同符号只都是正或者都是负）举个例子，最极端的情况，此时负数，然后有一个正数的 $C$ 把他加到了正数（变了符号），那么产生了两个不同的区间。正变负也是同理。

然而，我们又可以计算每一段 $C$ 的区间对应的 $B$ 是什么时候变号的（除一下就知道了）。那么我们就可以知道 $B$ 中那些段是**全是正数**或者**全是负数**。

然后小学一年级的等差数列求和，我们就可以计算出这个 $B$ 这一段区间结束后的贡献。

然后每一次更新答案。

注意，一开始，$ans$ 要设成 $C$ 中的第一个数，因为，如果这都是负数，会把你卡掉，这样其实实际上第一个数最大，而你却算成了第一个数所在区间的最后一个数。

因此这道题做完了。

[link](https://atcoder.jp/contests/abc240/submissions/52471794)。

---

## 作者：WaterSun (赞：1)

# 思路

题目要求的是 $\max_{a = 1}^{n}\{\sum_{i = 1}^{a}\sum_{j = 1}^{a}{A_j}\}$，所以我们将 $\sum_{i = 1}^{a}\sum_{j = 1}^{a}{A_j}$ 化简一下，得：

$$
i \times A_1 + (i - 1) \times A_2 + \dots + 1 \times A_x
$$

在 $a$ 每增加 $1$ 时，这个和 $s$ 将会变为 $s + \sum_{i = 1}^{x}a_i + a_x$。

- 如果在 $x_i \geq 0$ 时，显然对于答案是有贡献的，全部加上即可。

- 如果在 $x_i < 0$ 时，显然当 $s$ 没有被减下 $0$ 时，对于答案都是有贡献的，加上即可。但是在后面需要将剩下的都要加上。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,inf = 1e18 + 10;
int T,n,m;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	T = read();
	while (T--){
		int Max = -inf,sum = 0,res = 0;
		n = read();
		m = read();
		for (re int i = 1;i <= n;i++){
			int x,y;
			x = read();
			y = read();
			if (x >= 0){
				res += sum * y + x * (y + 1) * y / 2;
				Max = max(Max,res);
			}
			else{
				int l = max(1ll,min(sum / (-x),y));//注意这里需要与 1 取 max，避免 sum / (-x) 为负数 
				int del = sum * l + x * (l + 1) * l / 2;
				Max = max(Max,res + del);
				res += sum * y + x * (y + 1) * y / 2;
				Max = max(Max,res);
			}
			sum += x * y;
		}
		printf("%lld\n",Max);
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

$b$ 数组是好求的（这里的 $b$ 数组是指将 $C$ 数组分为 $n$ 段，从第一位到每一段数最后一位的前缀和）：
$$b_i=b_{i-1}+x_i\times y_i$$

然后我们发现 $c$ 数组不好做，不可能暴力展开。

不过题目求的是最大值，所以我们可以对 $b$ 中的值进行考虑：\
令 $s$ 数组表示完整的 $b$ 数组的值。（上面的 $b$ 数组表示的仅仅是一段的）

易得，这一段 $y_i$ 个数所对应的 $s$ 值必然是递增、递减或不变三者之一的。\
考虑二分：找到最后一个 $s_i\geq 0$ 的位置。（若 $s_i<0$ 则必然不是最大值）

我们用 $Sa$ 代替 $a$ 数组（但不一定是答案），在二分得到 $res$ 后就可以用来更新答案了（这里需要特判一下是哪一段以及是否有 $s_i\geq 0$）：
$$ans=\max(ans,Sa+b_{i-1}\times res+\frac{res\times(res+1)}{2}\times x_i)$$

当然 $Sa$ 也要更新（用整一段的数据）：
$$Sa+b_{i-1}\times y_i+\frac{y_i\times(y_i+1)}{2}\times x_i$$

而 $ans$ 取 $\max(ans,Sa)$ 即可。

注意：$ans$ 最开始可以取到 $x_1$。（数据可能出现 $Sa$ 一直变小的情况）

## Code
```cpp
#include<bits/stdc++.h>

typedef int IT;
typedef long long LL;
typedef __int128 int128;
typedef double DB;
typedef long double LDB;

#define pb push_back
#define fst first
#define sec second
#define psh push
#define mkp make_pair
#define PII pair<IT,IT>
#define PLI pair<LL,IT>
#define lowbit(x) ((x)&(-x))

using namespace std;

const int N=2e5+10;

int n,m;
int x[N],y[N];

LL b[N];
LL Sa;
LL ans;

void sl_reset();
void solve(){
    sl_reset();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
    
    for(int i=1;i<=n;i++){
        if(i==1) ans=x[i];
        b[i]=b[i-1]+1ll*x[i]*y[i];
    }
    for(int i=1;i<=n;i++){
        int l=1,r=y[i],res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(b[i-1]+1ll*mid*x[i]>=0) l=mid+1,res=mid;
            else r=mid-1;
        }
        if(b[i-1]+1ll*res*x[i]>=0&&(i>1||(i==1&&res>1))){
            ans=max(ans,Sa+b[i-1]*res+1ll*res*(res+1)/2*x[i]);
        }
        Sa+=b[i-1]*y[i]+1ll*y[i]*(y[i]+1)/2*x[i];
        ans=max(ans,Sa);
    }
    printf("%lld\n",ans);
    return;
}
void sl_reset(){
    Sa=ans=0;
    for(int i=1;i<=n;i++) b[i]=0;
    return;
}

int main(){
    int T=1;
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

因为 $ N $ 相对较小，考虑将序列拆分成 $ N $ 个区间，对每个区间分类讨论。

对于每个区间，显然有 $ B_i=B_{i-1}+x_in $，$ n $ 表示当前区间的第 $ n $ 项，因为一个区间内对应的 $ x_i $ 总是相同。

则有 $ A_i=\sum B_i=A_{i-1}+B_{i-1}n+\frac{n(n+1)}{2}x_i $，这个可以通过等差数列求和公式得到。

这是一个二次函数的形式，所以极值一定在端点或者中间的情况。

如果极值在端点显然不难计算，如果极值在中间的情况因为二次函数是单峰函数，朴素三分即可，或者也可以像下面的代码一样手推一个公式直接算出极值，公式太长就不放了，见代码。

时间复杂度 $ \mathcal{O}(N\log{M}) $，可以通过。注意本题是难得一见的 ABC 多测题目，记得清空。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define p1 998244353
#define p2 1000000007
using namespace std;
#define N 200002
int t,i,n;
ll x[N],y[N],a,b,k,ans,m;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=a=b=0;
		scanf("%d%lld",&n,&m);
		for(i=1;i<=n;i++)
		{
			scanf("%lld%lld",&x[i],&y[i]);
			if(i==1) 
			ans=x[i];
			if(x[i]>=0)
			{
				a+=(b+x[i]+b+x[i]*y[i])*y[i]/2;
				ans=max(a,ans);
				b+=x[i]*y[i];
			}
			else
			{
				if(b>0) 
				k=min(b/(-x[i]),y[i]);
				else 
				k=y[i];
				ans=max(a+(b+x[i]+b+x[i]*k)*k/2,ans);
				a+=(b+x[i]+b+x[i]*y[i])*y[i]/2;
				b+=x[i]*y[i];
			}
		}
		printf("%lld\n",ans);
	}
}
```


---

