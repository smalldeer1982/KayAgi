# Circular Dungeon

## 题目描述

You are creating a level for a video game. The level consists of $ n $ rooms placed in a circle. The rooms are numbered $ 1 $ through $ n $ . Each room contains exactly one exit: completing the $ j $ -th room allows you to go the $ (j+1) $ -th room (and completing the $ n $ -th room allows you to go the $ 1 $ -st room).

You are given the description of the multiset of $ n $ chests: the $ i $ -th chest has treasure value $ c_i $ .

Each chest can be of one of two types:

- regular chest — when a player enters a room with this chest, he grabs the treasure and proceeds to the next room;
- mimic chest — when a player enters a room with this chest, the chest eats him alive, and he loses.

The player starts in a random room with each room having an equal probability of being chosen. The players earnings is equal to the total value of treasure chests he'd collected before he lost.

You are allowed to choose the order the chests go into the rooms. For each $ k $ from $ 1 $ to $ n $ place the chests into the rooms in such a way that:

- each room contains exactly one chest;
- exactly $ k $ chests are mimics;
- the expected value of players earnings is minimum possible.

Please note that for each $ k $ the placement is chosen independently.

It can be shown that it is in the form of $ \frac{P}{Q} $ where $ P $ and $ Q $ are non-negative integers and $ Q \ne 0 $ . Report the values of $ P \cdot Q^{-1} \pmod {998244353} $ .

## 说明/提示

In the first example the exact values of minimum expected values are: $ \frac 1 2 $ , $ \frac 0 2 $ .

In the second example the exact values of minimum expected values are: $ \frac{132} 8 $ , $ \frac{54} 8 $ , $ \frac{30} 8 $ , $ \frac{17} 8 $ , $ \frac{12} 8 $ , $ \frac 7 8 $ , $ \frac 3       8 $ , $ \frac 0 8 $ .

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
499122177 0```

## 样例 #2

### 输入

```
8
10 4 3 6 5 10 7 5```

### 输出

```
499122193 249561095 249561092 873463811 499122178 124780545 623902721 0```

# 题解

## 作者：HenryHuang (赞：8)

# CF1380G Circular Dungeon

看懂样例就能做。

~~虽然我瞪了 20 分钟 菜是原罪~~

首先可以将从每一个点出发所能获得的价值相加，再除以 $n$ 就可以得到价值的期望。

所以问题转化为使从每一个点出发所能获得的价值之和最小。

有一个显而易见的结论：我们一定会将价值前 $k$ 大的宝箱变成假宝箱。

为了尽可能减小价值之和，这些假宝箱一定不会相邻，于是这 $k$ 个假宝箱把这个环分成了 $k$ 段。

为了方便起见，你可以把环断开成链，以某个假宝箱为断点，每一段都是完整的。

那么问题就变成了将真宝箱分为 $k$ 段，使得从每一个点出发所能获得的价值之和最小。

显然在同一段的点只能获得自己这一段中宝箱的价值。

考虑在同一段的每个点出发所能获得的总价值，设这一段宝箱中第 $i$ 个宝箱的价值为 $v_i$。

则有
$$
sum=\sum_{i=1}^niv_i
$$
那么显然这一段中的宝箱价值应按照降序排序才能保证总价值最小。

我们刚才考虑了一段的总价值，现在我们从总体上看，怎样能够使得价值最小？

注意到每一段的第一个数会对答案产生一次贡献，每一段的第二个数会对答案产生二次贡献，...，也就是说我们需要保证每一段的第一个数尽可能大，这样对答案的贡献才会小。

即设一共有 $k$ 段，我们可以将真宝箱中价值前 $k$ 大的宝箱放在每一段的第一个，剩余真宝箱中的前 $k$ 大放在每一段的第二个，以此类推，不足 $k$ 个可以看作用 $0$ 补齐。

这样这个题就做完了。

总时间复杂度为 $O(n\log_2n)$。

（其实你看我说这么大一堆代码超简单的）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=998244353;
const int maxn=3e5+5;
int a[maxn],sum[maxn];
int ksm(int a,int b,int p){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%p;
		b>>=1,a=1ll*a*a%p;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;++i) sum[i]=(sum[i-1]+a[i])%p;
	int inv=ksm(n,p-2,p);
	for(int k=1;k<=n;++k){
		int ans=0;
		for(int j=0,i=0;i<n;++j,i+=k)
			ans=(ans+1ll*j*(sum[min(n,i+k)]-sum[i]+p)%p)%p;
		cout<<1ll*ans*inv%p<<' ';
	}
	return 0;
}
```







---

## 作者：Twig_K (赞：3)

把期望转化为所有起始点出发的价值之和再除以 $n$，只需要最小化所有方案的价值和。

对于某个确定的 $k$，我们可以贪心分配假宝箱，**假宝箱一定是价值最大的 $k$ 个。**

非常显然，否则可以把一个价值较大的真宝箱和价值较小的假宝箱交换。

每个真宝箱对价值和的贡献，就是它的**价值**乘它被统计进答案的**次数**。而一个宝箱被统计进答案的**次数**，就等价于**环上以这个宝箱结尾的最长后缀的长度，使得这个后缀上全是真宝箱**。

价值越大的宝箱，我们希望它被统计进的次数尽可能少，于是这个问题就变成了普及组的排队接水了。

具体的，对于每个 $k$，先把最大的 $k$ 个变成假宝箱，将剩下的真宝箱**从大到小**排序后，第 $i$ 个**真宝箱**对答案的贡献就是 $\lceil \frac{i}{k} \rceil \times c_i$。

排序后预处理前缀和，外层枚举 $k$，里层枚举 $\lceil \frac{i}{k} \rceil$，不要忘记最后除以方案数 $n$，总复杂度 $O(n\log n)$。

完整代码见[提交记录](https://codeforces.com/contest/1380/submission/309902246)。

```cpp
signed main()
{
    rd(n); invn=inv(n);
    For(i,1,n) rd(c[i]);
    sort(c+1,c+1+n,greater<ll>());
    For(i,1,n) qadd(c[i],c[i-1]);

    For(K,1,n){
        ll ans=0ll;
        int num=n-K;
        for(int i=1;i<=(num+K-1)/K;i++){
            int l=(i-1)*K+1+K,r=min(i*K+K,n);
            qadd(ans,(c[r]-c[l-1]+mod)%mod*i%mod);
        }
        ans=ans*invn%mod;
        write(ans),Spc;
    } End;
    return 0;
}
```

---

## 作者：离散小波变换° (赞：2)

## 题解

虽然套了层期望的壳，但很容易发现期望值就是从每个点出发获得的收益之和，除以 $n$。

现在考虑这样一串宝箱的收益（其中 $\mathrm{Fake}$ 表示假宝箱）：

$$[b_1, b_2,b_3,\cdots b_k,\mathrm{Fake}]$$

容易发现它们的贡献为：

$$(b_1+b_2+\cdots+b_k)+(b_2+b_3+\cdots+b_k)+\cdots=b_1+2b_2+3b_3+\cdots+kb_k$$

也就是说，越靠近 $\mathrm{Fake}$，它的权重越大。并且权重就是到 $\mathrm{Fake}$ 走过的步数。容易贪心地去想，将 $b$ 数组从大到小排列（可以用邻项交换证明）。

可以进一步推广这个结论。假设一共有 $k$ 个假宝箱，那么权值为 $1$ 的宝箱数量最多有 $k$ 个（可以放在每个假宝箱后一个位置），权值为 $2$ 的宝箱最多有 $k$ 个（可以放在每个假宝箱后两个位置）……

容易贪心地去把前 $k$ 大的宝箱都设为假宝箱，这样肯定不劣。接着我们贪心地分配权值。给真宝箱前 $k$ 大的宝箱权重设为 $1$，剩下的真宝箱里前 $k$ 大的权重设为 $2$……将数列 $a$ 排序后做一个前缀和，那么就可以 $\mathcal O(1)$ 计算排名连续的宝箱的价值之和。我们暴力地分配权重，得到复杂度：

$$\mathcal O\left(\sum_i\dfrac{n-i}{i}\right)= \mathcal O\left(\sum_i\dfrac{n}{i}-n\right)=\mathcal O(n\log n)$$

那么这题就做完了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w=1,c,ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 3e5 + 3;
const int MOD  = 998244353;
int n, A[MAXN], S[MAXN], ans, t;
int pwr(int a, int b){
    int r = 1;
    while(b){
        if(b & 1) r = 1ll * r * a % MOD;
        a = 1ll * a * a % MOD, b >>= 1;
    }
    return r;
}
bool cmp(int a, int b){ return a > b; }
int main(){
    n = qread(), t = pwr(n, MOD - 2);
    up(1, n, i) A[i] = qread();
    sort(A + 1, A + 1 + n, cmp);
    up(1, n, i) S[i] = (S[i - 1] + A[i]) % MOD;
    up(1, n, i){
        int tot = 0;
        for(int l = i + 1, r = min(l + i - 1, n), c = 1;l <= n;l += i, r = min(n, l + i - 1), ++ c){
            tot = (tot + 1ll * (S[r] - S[l - 1] + MOD) * c % MOD) % MOD;
        }
        printf("%lld%c", 1ll * tot * t % MOD, " \n"[i == n]);
    }
    return 0;
}
```

---

## 作者：_lyx111 (赞：2)

# CF1380G Circular Dungeon

[link](https://codeforces.com/problemset/problem/1380/G)

## 分析

依题意得：$ans_k=\frac{\sum_{i=1}^n \text{从第}\ i\  \text{个点出发所能获得的价值}}{n}$，那么可以将问题转化为使从每一个点出发所能获得的价值之和最小

为了使它最小，空宝箱一定是价值最大的 $k$ 个宝箱且这些假宝箱一定不会相邻，所以这 $k$ 个假宝箱把这个环分成了 $k$ 段

考虑一段的总价值，设这一段中第 $i$ 个宝箱的价值为 $c'_i$，那么总价值为 $\sum_{i=1}^ni\times c'_i$，
从而可以得出这一段中的宝箱价值应按照**降序**排序才能保证总价值最小

我们总结一下，使答案最小的摆放方案是：

1. 将真宝箱中价值前 $k$ 大的放在每一段的第一个

2. 将剩余真宝箱中的前 $k$ 大的放在每一段的第二个

3. $\dots$

4. 以此类推，不足 $k$ 个用 $0$ 补齐

再总结一下假宝箱个数为 $k$ 时的算法流程：

1. 枚举每段的第 $i$ 个在 $c$ 上的区间 $i\times k+1$ ~ $min((i+1)\times k,n)$，加上它的贡献 $i\times \sum_{i\times k+1}^{min((i+1)\times k,n)} c_i$，其中 $\sum_{i\times k+1}^{min((i+1)\times k,n)} c_i$ 可以用前缀和优化

2. 输出 $\frac{\text{贡献和}}{n}$

时间复杂度：$O(n\log n)$

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=998244353,MAXN=3e5+10;
int n;
int c[MAXN],pre[MAXN]; //pre 是 c 的前缀和 
int ksm(int u,int v) //快速计算 u^v 
{
	int res=1;
	while(v)
	{
		if(v&1) res=1ll*res*u%mod;
		u=1ll*u*u%mod; v>>=1;
	}
	return res;
}
bool cmp(int x,int y) //自定义比较函数 
{
	return x>y;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	sort(c+1,c+n+1,cmp); //将数组 c 从大到小排序 
	for(int i=1;i<=n;i++)
		pre[i]=(pre[i-1]+c[i])%mod; //前缀和 
	for(int k=1;k<=n;k++) //枚举假宝箱个数 k 
	{
		int ans_k=0;
		for(int i=k,j=1;i<n;i+=k,j++) //i：当前段的左端点的左边那一位，j：对答案的贡献 
			ans_k=(ans_k+1ll*j*(pre[min(n,i+k)]-pre[i]+mod)%mod)%mod;
			//计算当前段 i~min(n,i+k) 对答案的贡献，并将其加入 ans_k 
		printf("%d ",1ll*ans_k*ksm(n,mod-2)%mod);
	}
	return 0;
}
~~~

[AC记录](https://codeforces.com/problemset/submission/1380/175125186)

## 写在最后

笔者水平有限，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正

---

