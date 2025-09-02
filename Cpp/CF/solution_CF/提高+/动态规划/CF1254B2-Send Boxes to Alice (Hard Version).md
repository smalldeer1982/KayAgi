# Send Boxes to Alice (Hard Version)

## 题目描述

有 $n$ 个盒子，每个盒子有 $a_i$ 个糖果，你每一次可以将第 $i$ 个盒子里的糖果放到第 $i-1$ 或 $i+1$ 个盒子中（如果盒子存在）。最后要存在一个整数 $k(k>1)$，使得每个盒子的糖果数量都被 $k$ 整除 （注意盒子可以为空），问最小操作数。

## 说明/提示

$1 \le n \le 10^6$

$0 \le a_i \le 10^6$

## 样例 #1

### 输入

```
3
4 8 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
3 10 2 1 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
0 5 15 10
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1
1
```

### 输出

```
-1
```

# 题解

## 作者：Kelin (赞：7)

## 题意
$n$盒排成一列的糖果盒，第$i$盒有$a_i$个糖果

每次可以取出某一盒一颗糖果放到相邻的糖果盒里

问使得所有盒子的里的糖果数均能被某个$k(k>1)$整除的最少移动次数

---

## [题解](https://mp.csdn.net/mdeditor/103181464)

设糖果总数的$Sum$（显然$Sum=1$无解）

符合条件的$k$一定满足$k\mid Sum$

考虑对于一个$k$如何求解最少的移动次数

首先肯定要将所有的$a_i$对$k$取余

对于一个$a_i$可以将$a_i$颗糖果全部向后挪，于是$a_{i+1}=(a_{i+1}+a_i)\mod k$

也可以从后面挪$k-a_i$颗糖果到$a_i$上，于是$a_{i+1}=a_{i+1}-(k-a_i)\equiv a_{i+1}+a_i \mod k$

设$S_i=\sum_{k=1}^ia_i \mod k$，那么$Ans=\sum_{i=1}^n\min(S_i,k-S_i)$

通过上面可以发现如果如果$k_1\mid Sum,k_2\mid Sum$，且$k=k_1k_2\mid Sum$

那么$k$的答案一定不会比$k_1,k_2$优，所以只需要枚举$Sum$的质因子即可

题目当中$Sum\le10^{12}$，而$2\times3\times5\times\ldots\times37>10^{12}$，所以计算次数不会太多

时间复杂度为$O(n\times Sum$质因子个数$+\sqrt{Sum})$

```cpp
using ll=long long;
inline ll Calc(ll p){
	ll Cnt=0,Tmp=0;
	for(int i=1;i<=n;++i)
		Cnt=(Cnt+a[i])%p,Tmp+=min(Cnt,p-Cnt);
	return Tmp;
}
inline void Sol(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i),Sum+=a[i];
	if(Sum<2)
		return(void)puts("-1");
	Ans=-1ull>>1;
	for(int i=2;(ll)i*i<=Sum;++i)
		if(Sum%i==0){
			while(Sum%i==0)Sum/=i;
			Ans=min(Ans,Calc(i));
		}
	if(Sum>1)
		Ans=min(Ans,Calc(Sum));
	printf("%d\n",Ans);
}
```

---

## 作者：Licykoc (赞：3)

reference：Codeforces Tutorial。

先来考虑固定 $k$ 时怎么做。设 $b_i = \sum_{j = 1}^{i} a_j$，发现：

$$\forall 1 \le i \le n ,{k \mid a_i} \Longleftrightarrow \forall 1 \le i \le n, k \mid b_i$$

同时可以发现：

1. 将 $a_i$ 取出 $1$ 并放入 $a_{i+1}$ 这个操作等价于 $b_i \gets b_i - 1$。

2. 将 $a_{i+1}$ 取出 $1$ 放入 $a_i$ 等价于 $b_i \gets b_i + 1$。

那么当固定 $k$ 时，答案：

$$ans = \sum_{i=1}^n \min(b_i \bmod k, k - b_i \bmod k)$$

至此，本题关键已经解决。

对于 `Easy Version` 我们只需 $O(\sqrt{b_n})$ 枚举 $k$，对所有情况取 $\min$ 即可。

而对于 `Hard Version` 需要观察到，所有的合数 $k$ 都是没有必要的，将其替换成其最小质因子答案不会变劣。于是我们只需枚举 $b_n$ 的质因子即可。

参考实现：

```cpp
#include <bits/stdc++.h>
#define int long long 

using namespace std;

using int64 = long long;

const int inf = 5e18 + 10;

signed main () {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;

  cin >> n;

  vector<int> a(n + 1);
  int sum = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum += a[i];
  }

  if (sum == 1) {
    cout << -1 << '\n';
    return 0;
  }

  int res = inf;
  vector<int> factor;

  factor.emplace_back(sum);
  for (int i = 2; i * i <= sum; ++i) {
    if (sum % i == 0) {
      factor.emplace_back(i);
      while (sum % i == 0) {
        sum /= i;
      }
    }
  }
  if (sum > 1) {
    factor.emplace_back(sum);
  }

  auto calc = [&](int x) -> int{
    vector<int> b(n + 1);
    int res = 0;

    for (int i = 1; i <= n; ++i) {
      b[i] = b[i - 1] + a[i] % x;
      b[i] %= x;
      res += min(b[i], x - b[i]);
    }

    return res;
  };

  for (int x : factor) {
    res = min(res, calc(x));
  }

  cout << (res == inf ? -1 : res) << '\n';
}
```


---

## 作者：laboba (赞：2)

感觉挺简单的吧，也就一个绿或黄？蓝有点假了

思路：

枚举 $k$ 并判断此时的最小答案。记  $S= \sum_{i=1}^na_i$
由于 $k$ 可以取到 $n\times a$ ，直接枚举复杂度爆炸。不难想到,$k$ 可以取的值必须是 $S$ 的因数，因为最后每个位置上的 $a[i]$ 都是 $k$ 的倍数，它们的和即 $S$ 自然也是 $k$ 的倍数。进一步的，对于每一种方案和对应的 $k$，令 $k$ 取其每一个非 $1$ 的因数时，这种方案仍然满足题意，所以最小的答案必定在 $k$ 为 $S$ 的质因数时取到。

接下来考虑如何判断对于一个固定的 $k$ 的最小答案。采用贪心的策略：若 $a[i]\bmod k\leq k/2$，则将 $a[i]\bmod k$ 给到 $a[i+1]$，否则从 $a[i+1]$ 取 $k-a[i]\bmod k$，答案为每一步所移动的值之和。 

感性证明：对于每一个 $a[i]$，显然处理完它与 $a[i+1]$ 之间的关系后它对后面的数就无法造成影响了，所以我们对每一个 $a[i]$ 都贪心取到可以取的最小值并将影响累加给 $a[i+1]$ 的策略是正确的。

复杂度：$O(n\times \log(S))$

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1001000;
int a[N];
long long b[N];
long long p[20];//2*3*5......*37>10^12>=S,质因数个数必然小于20 
int tot;
int main(){
	int n;
	long long sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
	for(long long i=2;i*i<=sum;i++){
		if(sum%i)continue;
		p[++tot]=i;
		while(sum%i==0)sum/=i;
	}
	if(sum>1)p[++tot]=sum;//分解质因数并存入p数组 
	long long ans=-1;//无解输出-1 
	for(int i=1;i<=tot;i++){
		sum=0;
		for(int j=1;j<=n;j++)b[j]=a[j];
		for(int j=1;j<n;j++){
			if(!b[j]%p[i])continue;
			//处理每一位的答案和影响，不取模也是可以的 
			//有a[i]给a[i+1]和a[i+1]给a[i]两种可行操作，取较小值 
			if(b[j]%p[i]<=p[i]/2)sum+=b[j]%p[i],b[j+1]+=b[j]%p[i];
			else sum+=p[i]-b[j]%p[i],b[j+1]+=b[j]%p[i];
		}
		ans=ans==-1?sum:min(ans,sum);
	}
	printf("%lld",ans);
}
```


---

## 作者：y2823774827y (赞：1)

[My blog](https://www.cnblogs.com/y2823774827y/p/11895446.html)

## 题意
> n个数字的序列a，将i位置向j位置转移x个(a[i]-x,a[j]+x)的花费为$x\times |i-j|$，最终状态可行的条件为所有a[i]均被K整除(K>1)，求最小花费

## 做法
$sum=\sum\limits a$，则$K|sum$

- 有$K1|sum,K2|sum$，若$K1|K2$，则转移到被K1整除比转移到K2更优。这个是显然的，所以最终可能成为最优解的K个数为$logsum\le 40$

对于一个枚举到的K，将$b[i]=a[i]\% K$

对于b不为0的位置，我们类似贪心得考虑

- 仅有前面一个位置pre不合法：因为如果有两个，在之前我们可以合成一个

- 如果b[i]可以与前一个补满(b[i]可能还会有多余的)，考虑从i转移到pre优还是pre转移到i优

- 如果b[i]不能补满前一个，这个时候我们考虑如果能补满会补到哪里，然后更新一下pre

## Code
比赛时调了好久，码风有点奇怪

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long ll;
const LL maxn=1e6+9;
const ll inf=0x3f3f3f3f3f3f3f3f;
LL Read(){
	LL x(0),f(1); char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1; c=getchar();
	}
	while(c>='0' && c<='9'){
		x=(x<<3)+(x<<1)+c-'0'; c=getchar();
	}return x*f;
}
LL n,T,tot;
ll sum;
LL a[maxn],b[maxn];
ll bel[maxn];
bool Check(ll x){
	for(LL i=1;i<=tot;++i) if(x%bel[i]==0) return false;
	return true;
}
int main(){
	n=Read();
	for(LL i=1;i<=n;++i) a[i]=Read(),sum+=a[i];
	
	
	/*srand(time(NULL));
	n=1000000;
	for(LL i=1;i<=n;++i) a[i]=rand()%1000001,sum+=a[i];
	printf("%lld\n",sum);*/

	for(LL i=2,up=sqrt(sum);i<=up;++i) if(sum%i==0){
	
		if(Check(i)) bel[++tot]=i;
		if(Check(sum/i)) bel[++tot]=sum/i;
	}
	if(Check(sum)) bel[++tot]=sum;
//	printf("%d\n",tot);
	if(sum==0 || sum==1){
		puts("-1"); return 0;
	}
	if(!tot){
		puts("0"); return 0;
	}
	ll ans(inf);
	for(LL k=1;k<=tot;++k){
		ll x(bel[k]),nw(0),ret(0);
		LL l(1),pre(0);
		for(LL i=1;i<=n;++i){
		    b[i]=a[i]%x;
			if(!b[i]) continue;
			if(nw){
				if(x-nw>b[i]){
					if((x-nw)*(i-pre)>nw*(i-pre)) ret+=nw*(i-pre),pre=i;
					else ret+=b[i]*(i-pre);
					nw+=b[i];
				}else{
					ret+=(std::min(x-nw,nw))*(i-pre);
					nw=b[i]-(x-nw);
					if(nw) pre=i;
				}
				continue;
			}
			nw=b[i];
			pre=i;
		}
		ans=std::min(ans,ret);
//		printf("(%lld,%lld)\n",x,ret);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

# Send Boxes to Alice (Hard Version)

[题面](https://www.luogu.com.cn/problem/CF1254B2)

## 思路

**Motivation 1：我不想做幽默的，没有方向的调整，我想知道 $p$ 具体是多少，以此让我有目的的调整。**

我们考虑枚举 $p(k\ne 1)$，$p$ 是原数组总和的因数。显然 $p$ 一定是这种数，但是实际上 $p$ 还是有太多的选择了，我们先考虑以下 $p$ 固定的情况，看看有没有性质可以利用。

**Motivation 2：一次改变两个格子？我想找到一种更方便的等价问题。**

如何可以把相邻的 $+a,-a$，这个操作，变为一个格子上的操作呢？没错，对于后面原本 $-a$ 的格子，如果它是前缀和，那么 $+a,-a$ 就会抵消。于是我们可以考虑前缀和。

现在，操作变为了单个格子 $+a,-a$。再来讨论与原问题的关联性，先来考虑必要性，如果 $1$ 到 $n$ 的数，全部满足被 $p$ 整除，前缀和 $sum$ 的每个格子都被 $p$ 整除吗？显然的。那充分性呢？如果 $sum$ 的每个格子都被 $p$ 整除，原数组的每个格子都被 $p$ 整除吗？实际上，我们可以这样想：$sum_{1}$ 即为原数组的元素 $1$，即元素 $1$ 被 $p$ 整除，接下来的 $sum_{2}$ 是 $sum_{1}$ 加上原数组的第二个元素，因为 $sum_{1}$ 被 $p$ 整除，所以第二个元素也被 $p$ 整除，以此类推。

现在我们发现这个前缀和的转化问题和原问题等价，但是实际上，我们还有一个东西，我们需要考虑，就是原数组不能为负，那么 $\exists \;i\in [1,n],sum_{i}>sum_{i+1}$ 就不能成立。

我们可以贪心点，对于 $sum_{i}$ 如果想让它被 $p$ 整除，就可以让它减少 $sum_{i} \mod p$，或者增加 $p-sum_{i} \mod p$，取最小值。

这个策略满足上文的条件，因为 $sum_{i+1}$ 原来是大于等于 $sum_{i}$ 的，如果 $sum_{i}$ 的决策是减少，不管 $sum_{i+1}$ 是什么决策，都不会小于 $sum_{i}$，如果 $sum_{i}$ 的决策是增加，那么如果 $sum_{i+1}$ 的决策是增加，一定大于等于 $sum_{i}$（必然是贴近最近的比它大的 $p$ 的倍数），如果是减少。那么 $sum_{i+1}$ 必然则大于等于 $sum_{i}$ 贴近的 $p$ 的倍数，才会做出这个决策，所以减少后也不会小于 $sum_{i}$。

我们已经讨论了，当 $p$ 固定时，我们答案就是 $\sum_{i=1}^{n} \min(sum_{i}\mod p,p-sum_{i} \mod p)$。再看看有没有什么性质能减少 $p$ 的枚举范围，当 $a$ 被 $b$ 整除时，$p=b$ 在上式的所有计算必定不优于 $p=a$ 的计算。所以我们只需要考虑元素和的质因数即可。

代码很好写，这就是构造题。

```cpp
// Problem: B2. Send Boxes to Alice (Hard Version)
// Contest: Codeforces - Codeforces Round 601 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1254/B2
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int a[N], s[N], n, tt;
int ev(int x) {
    int sum = 0;
    upp(i, 1, n) { sum += min(s[i] % x, x - s[i] % x); }
    return sum;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int ans = INF;
    cin >> n;
    upp(i, 1, n) cin >> a[i], s[i] = s[i - 1] + a[i];
    int sum = s[n];
    map<int, bool> st;
    vector<int> fac;
    upp(i, 2, sum / i) {
        while (sum % i == 0) {
            sum /= i;
            if (!st[i]) {
                fac.pb(i);
                st[i] = 1;
            }
        }
    }
    if (sum != 1) fac.pb(sum);
    upp(i, 0, (int)fac.size() - 1) { ans = min(ans, ev(fac[i])); }
    if (ans == INF)
        cout << "-1" << endl;
    else
        cout << ans << endl;
    return 0;
}
```

---

