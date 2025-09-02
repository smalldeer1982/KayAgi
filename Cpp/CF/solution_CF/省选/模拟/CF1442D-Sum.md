# Sum

## 题目描述

You are given $ n $ non-decreasing arrays of non-negative numbers.

Vasya repeats the following operation $ k $ times:

- Selects a non-empty array.
- Puts the first element of the selected array in his pocket.
- Removes the first element from the selected array.

Vasya wants to maximize the sum of the elements in his pocket.

## 样例 #1

### 输入

```
3 3
2 5 10
3 1 2 3
2 1 20```

### 输出

```
26```

# 题解

## 作者：WeLikeStudying (赞：43)

- 本来不敢发题解，只用作自己记录下（主要是作者太菜了）。
- 但作者一不小心点了一下题解键（在还没有打完的情况下），所以不得不去写啦。
- 请把我的题解置于那些大佬的下方。

**题意**
- [原题题面](https://www.luogu.com.cn/problem/CF1442D)。
- 给定 $n$ 个非负数组，每个数组的元素可以被取当且仅当该数组内小于该元素的数都被取了。
- 在这 $n$ 个数组中取 $k$ 个数，要求取的数和最大。
- $n,k\le 3000$，数组中元素总个数不大于 $10^6$，不小于 $k$。

**思路**
- 传统的动态规划是 $O(nk^2)$ 的。
- 似乎也没啥可以优化的。
- [暴力实现](https://www.luogu.com.cn/paste/3g80c3qz)，作者暴力写挂就离谱，下次用滚动数组一定要注意初始化问题，作者还忘记开长整型了 QWQ。
- 所以我们尝试发现性质：锁定非负和数组元素分别非降的性质。
![](https://cdn.luogu.com.cn/upload/image_hosting/dr3bxycf.png)
- 你会发现对于两个没有选完的数组，比较它们的最后一个元素大小，然后贪心地抛弃更小的前面的选取更大的后面的总是没错的。
- 也就是说，存在一种最优选取方案满足只有一个数组只选了一部分（与之对应的是不选或选完）。
- 理想很美好，那么难道是枚举没选完的数组然后再跑背包？$O(n^2k)$（那不就白发现性质了吗）。
- 我们转入实际实现。

**分块做法**
![](https://cdn.luogu.com.cn/upload/image_hosting/opkbfqfj.png)
- 设块长为 $x$，块数为 $\dfrac nx$。
- 对除开每块的全放进行预处理：$\Theta(\frac nx \cdot nk)=\Theta(\frac {n^2k}x)$。
- 块内枚举物品对让其他物品更新 $\Theta(\frac nx\cdot x\cdot xk)=\Theta(nkx) $。
- 总复杂度为 $\Theta(\frac {n^2k}x+nkx)$ 取 $x=\sqrt n$ 得到 $\Theta(n\sqrt nk)$ 的复杂度，应该可过。
- [代码实现](https://www.luogu.com.cn/paste/yzh38alz)。
- 作者在判断语句上犯了玄学错误（看错变量名！！）我靠，以后提交前一定要看一遍程序！！

**分治做法**
- ~~学分治也就图一乐。~~
- 作者想了想发现很妙啊，而且放在分块后面很合适。
- 我们本质上就是要求出除开每个数的 $01$ 背包。
- 之前的分块做法相当于先求出来除开每个块的 $01$ 背包，然后再求出除开每个数的 $01$ 背包，那么如果你把块分得更细呢？
- 这就是分治做法：
![](https://cdn.luogu.com.cn/upload/image_hosting/8zkrmfhi.png)
- 对于一个区间，如果我们已经算出除开该区间的背包，那么我们可以 $\Theta(nk)$ 更新除开左区间的背包（加右区间的数），同理更新左区间的背包。
- 可以列出递推式 $T(n)=2T(n/2)+nk$，它的解是 $\Theta(nk\lg n)$，这也是分治做法的时间复杂度。
- 具体实现可能较分块复杂，而且必须开 $k\lg n$ 的空间（不过对于题目条件来说这算不了啥），但可以用类似栈的方法实现。
- 作者忘记弹栈属实离谱。
- [代码实现](https://www.luogu.com.cn/paste/i2m9eir4)。
- 比分块好打属实离谱。

---

## 作者：云浅知处 (赞：25)

首先注意到一个性质：至多有一个序列没有被选满。

换句话说就是，只要选了一个序列的第一个数，那么最优方案一定是尽量把这个序列的所有数都选上。

其实证明很容易......这里简单写一下：

> - 注意到序列是不降的
> - 如果我们剩了两个序列都没有选满，假设两个序列选到的地方下一个数分别是 $x,y$
> - 如果 $x>y$，那么 $x$ 肯定比 $y$ 前面那些数都大，也就是说选上 $x$ 换掉 $y$ 前面的一个数一定更优。
> - 反之如果 $x<y$ 也是同理的。
> - 这样一直替换下去，必然会选空其中一个序列。因此不可能有两个序列都没有选满。

这样一来，我们就可以把每个序列看做一个物品，价值就是序列中所有数的和，重量则是序列的长度。

枚举没有选满的是哪个序列，以及具体选到了哪里，我们要做的相当于以下的问题：

> 给定 $n$ 个物品，对 $i=1,2,\cdots,n$，你需要求出：去掉第 $i$ 个物品后，对其他物品做背包的结果。

如果直接暴力那么复杂度是 $O(n^2k)$，过不去。

实际上这是一个经典的套路。注意到插入一个物品的复杂度是 $O(k)$，我们考虑一个分治算法：

- 对于区间 $[l,r]$，找到一个中间点 $m$。
- 先将 $[l,m]$ 中的物品插入到背包中，然后 $\text{solve}(m+1,r)$。
- 将背包还原，再将 $[m+1,r]$ 中的物品插入到背包中，然后 $\text{solve}(l,m)$。
- 这样一来，如果当前的区间是 $[l,r]$，可以发现此时背包中的物品恰为 $[1,l-1]\cup[r+1,n]$ 中的物品！
- 因此，当 $l=r$ 时我们得到的就是想要的答案。

时间复杂度是 $T(n)=2T(n/2)+O(nk)=O(nk\log n)$。

参考代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=3005;
int n,k,ans=0;
int a[MN][MN],dp[MN],tmp[20][MN],t[MN];

void solve(int l,int r,int d){
	if(l==r){
		for(int i=0;i<=t[l];i++)ans=max(ans,a[l][i]+dp[k-i]);
		return ;
	}
	int mid=(l+r)>>1;
	for(int i=0;i<=k;i++)tmp[d][i]=dp[i];
	for(int i=l;i<=mid;i++){
		for(int j=k;j>=0;j--)if(j>=t[i])dp[j]=max(dp[j],dp[j-t[i]]+a[i][t[i]]);
	}
	solve(mid+1,r,d+1);
	for(int i=0;i<=k;i++)dp[i]=tmp[d][i];
	for(int i=mid+1;i<=r;i++){
		for(int j=k;j>=0;j--)if(j>=t[i])dp[j]=max(dp[j],dp[j-t[i]]+a[i][t[i]]);
	}
	solve(l,mid,d+1);
	for(int i=0;i<=k;i++)dp[i]=tmp[d][i];
}

signed main(void){

	n=read(),k=read();
	for(int i=1;i<=n;i++){
		t[i]=read();
		for(int j=1;j<=t[i];j++){
			if(j<=k)a[i][j]=a[i][j-1]+read();
			else read();
		}
		t[i]=min(t[i],k);
	}
	solve(1,n,0);
	cout<<ans<<endl;

	return 0;
}
```

---

## 作者：pandaSTT (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/CF1442D)

[更好的阅读体验？](https://www.luogu.com.cn/blog/557117/solution-cf1442d)

# Thinking

题目范围较小，$ n,k \leq 3000 $，可以考虑背包 DP。

$ dp[j] $ 表示当前已经取出 $ j $ 次的值得最大值。
 
开始考虑状态转移。

## First

$ i $ 表示当前选择到第 $ i $ 个数组，$ j $ 表示当前选择了 $ j $ 个元素，$ l $ 表示在当前数组选择了 $ l $ 个数。

对于一个数组，只能每次取数组的第一个元素，所以我们可以用一个循环计算该数组前 $ l $ 个元素的和 。

## Frist_Coding

```cpp
  #include<bits/stdc++.h>
  #define int long long 
  using namespace std;
  const int N=3005;
  int n,k,t[N],dp[N];//dp[j]表示当前已经取出j次的值得最大值 
  vector<int> a[N];
  signed main(){
      scanf("%lld %lld",&n,&k);
      for(int i=1;i<=n;i++){
          scanf("%lld",&t[i]);
          a[i].push_back(0);
          for(int j=1;j<=t[i];j++){
              int x;
              scanf("%lld",&x);
              a[i].push_back(x);
          }
      }
      for(int i=1;i<=n;i++){
          for(int j=k;j>=0;j--){
              for(int l=min(j,t[i]);l>=0;l--){
                  int sum=0;
                  for(int p=1;p<=l;p++){
                      sum+=a[i][p];
                  }
                  dp[j]=max(dp[j],dp[j-l]+sum);
              }
          }
      }
      printf("%lld",dp[k]); 
      return 0;
  }
```


时间复杂度 $ O(n^2 k^2) $

实际得分 TLE on #4

## Next

第一种算法的时间复杂度太劣，明显需要优化。

对于优化背包 DP 最简单的方法是前缀和优化，所以在第一种算法的基础上考虑前缀和优化。

我们发现，每个 $ l $ 在查找这个数组时都会出现 $ k $ 次，所以每次都要计算该数组前 $ l $ 个元素的和会重复计算，非常浪费时间。因此我们可以在输入时预处理每个数组的前缀和。

## Next_Coding

```cpp
  #include<bits/stdc++.h>
  #define int long long 
  using namespace std;
  const int N=3005;
  int n,k,t[N],dp[N];//dp[j]表示当前已经取出j次的值得最大值 
  vector<int> sum[N];//sum[i][j]表示第i个栈栈顶的j个元素的值的和
  signed main(){
      scanf("%lld %lld",&n,&k);
      for(int i=1;i<=n;i++){
          scanf("%lld",&t[i]);
          sum[i].push_back(0);
          for(int j=1;j<=t[i];j++){
              int x;
              scanf("%lld",&x);
              sum[i].push_back(sum[i][j-1]+x);
          }
      }
      for(int i=1;i<=n;i++){
          for(int j=k;j>=0;j--){
              for(int l=min(j,t[i]);l>=0;l--){
                  dp[j]=max(dp[j],dp[j-l]+sum[i][l]);
              }
          }
      }
      printf("%lld",dp[k]); 
      return 0;
  }
```


时间复杂度 $ O(nk^2 )$

实际得分 TLE on #10

## Last

$ 2.7 \times 10^9 $ 的时间复杂度也会 TLE，因此我们需要将时间复杂度中的一个 $ k $ 或 $ n $ 去掉或转化为 $ \log $。

要想时间复杂度转化为 $ \log $，必须舍弃状态转移中的一个循环。而枚举 $ i $ 和枚举 $ j $ 的循环显然不能删除，因此只能去掉枚举 $ l $ 的循环。

让我们再观察现在的结构，会发现这样背包 DP 就变成了 01 背包！即每次选择数组都必须将本数组选择完。因此联想到如下结论：

在所有被选择的数组中，只有一个数组只选部分，其余数组全部都选完。

证明已置后。

所以，我们只需要查找只选部分的那个数组即可。

时间复杂度不允许用循环枚举只选部分的数组，因此只能用时间复杂度为 $ \log $ 的算法查找。

有什么算法能在 $ \log $ 的时间复杂度下查找？**分治！**

我们二分那个只选部分的数组在整个区间出现在左边还是右边。出现在左边，即右边区间的数组将全部被选完，01背包解决。出现在右边，同理。

当二分到区间只剩一个数组时，则此数组只选部分，同样进行一个背包 DP。

此背包 DP不需要枚举背包容量，只需枚举 $ i $ 表示此数组选择的个数，而背包容量就为 $ k-i $，用一个 ans 记录答案即可。 

## Last_Prove

令没被选择完的两个数组为 $ a,b $ 。

$ a $ 数组的选择了前 $ i $ 个， $ b $ 数组选择了前 $ j $ 个，并且  $ a_i \geq b_j $ 。

则 $ b_{j-1} \leq b_j \leq a_{i}\leq a_{i+1} $。

显然将 $ a $ 数组选择完会更优。

因此会留下一个只选择了部分的 $ b $ 数组。

时间复杂度 $ O(nk $ $\log $ $ n) $

预计得分 AC

## Last_Coding

```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int N=3005;
  int n,k,x,t[N],sum[N],ans,dp[N];
  vector<int> a[N];
  void dfs(int l,int r){
      int mid=(l+r)/2;
      if(l==r){
          int now=0;
          for(int i=0;i<=min(t[l],k);i++){
              ans=max(ans,now+dp[k-i]);
              now+=a[l][i];
          }
          return;
      }
      int f[N];
      for(int i=0;i<=k;i++){
          f[i]=dp[i];
      }
      for(int i=mid+1;i<=r;i++){
          for(int j=k;j>=t[i];j--){
              dp[j]=max(dp[j],dp[j-t[i]]+sum[i]);
          }
      }
      dfs(l,mid);
      for(int i=0;i<=k;i++){
          dp[i]=f[i];
      }
      for(int i=l;i<=mid;i++){
          for(int j=k;j>=t[i];j--){
              dp[j]=max(dp[j],dp[j-t[i]]+sum[i]);
          }
      }
      dfs(mid+1,r);
  }
  signed main(){
      scanf("%lld %lld",&n,&k);
      for(int i=1;i<=n;i++){
          scanf("%lld",&t[i]);
          for(int j=1;j<=t[i];j++){
              scanf("%lld",&x);
              a[i].push_back(x);
              sum[i]+=x;
          }
      }
      dfs(1,n);
      printf("%lld",ans);
      return 0;
  }
```

---

## 作者：yijan (赞：8)

感觉这个结论题好神仙啊，开始还以为是凸包之类的东西没想到是结论题。。

一个结论：对于一个选择 $k$ 个数的最优状态，一定不存在多于 $1$ 个序列被选了一部分。

我们设有两个序列选了一部分 $a_p,a_q$ ，同时设两个序列分别选择了 $t_p,t_q$ ，我们可以设 $a_{p,t_p+1} \le a_{q,t_q+1}$ 。

然后考虑，如果我们调整 $k$ 个数从 $p$ 到 $q$ 内，于是更改量就是
$$
\sum_{i=1}^k a_{q,t_q + i} - \sum_{i=1}^k a_{p,t_p + 1 - i}
$$
由于每个 $a$ 单增，所以 
$$
\begin{aligned}
a_{q,t_q + i} \ge a_{q,t_q + 1}\\
a_{p,t_p + 1 - i} \le a_{p,t_p + 1}
\end{aligned}
$$
所以
$$
\sum_{i=1}^k a_{q,t_q + i} - \sum_{i=1}^k a_{p,t_p + 1 - i} \ge a_{q,t_{q} + 1} - a_{p,t_p + 1} \ge 0
$$
所以我们直接设 $y = t_p$ 调整，把 $p$ 调整空即可。

所以，任意时刻只有一个数列内部被部分选择。

于是我们对除开这个数列外的其他数列跑背包，这个数列单独背包即可。除开这个物品的背包是经典套路，可以分治解决。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
#define P 1000000007
int n , k;
vi obs[3006]; ll v[3006] , w[3006];

vector<ll> dp;
ll ans = 0;
void dq( int l , int r ) {
	if( l == r ) {
		int t = 0; ll r = 0;
		for( int x : obs[l] ) {
			++ t;
			r += x;
			ans = max( ans , dp[k - t] + r );
			if( t >= k ) break;
		}
		return;
	}
	vector<ll> tmp = dp;
	int mid = l + r >> 1;
	rep( i , l , mid ) {
		for( int j = k ; j >= v[i] ; -- j ) dp[j] = max( dp[j] , dp[j - v[i]] + w[i] );
	}
	dq( mid + 1 , r );
	dp = tmp;
	rep( i , mid + 1 , r ) {
		for( int j = k ; j >= v[i] ; -- j ) dp[j] = max( dp[j] , dp[j - v[i]] + w[i] );
	}
	dq( l , mid );
}

void solve( ) {
    cin >> n >> k;
	rep( i , 1 , n ) {
		static int t;
		scanf("%d",&t);
		obs[i].resize( t );
		rep( j , 0 , t - 1 ) scanf("%d",&obs[i][j]) , w[i] += obs[i][j];
		v[i] = t;
	}
	dp.resize( k + 1 );
	dq( 1 , n );
	cout << ans << endl;
}

signed main() {
//	freopen("input","r",stdin);
//	freopen("fuckout","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}
```



---

## 作者：Cocoly1990 (赞：6)

考虑大力猜结论，思考选完 $k$ 次后最终的状态是什么？

很重要的性质是，数组是**不降的**。

可以证明的是，最终必然是若干个完全取完的数组，**至多一个取了一部分的数组**，剩下的应该完全没有动过。

感性理解一下这个结论，假设最后剩下两个数组 $a,b$，那么我们把取 $b$ 的次数拿去取 $a$（或者把取 $a$ 的次数拿去取 $b$），必然优于两者各取一部分。

从春令营讲义 ~~贺~~ 修改来的

一个显然的思路是枚举不满的数组是哪个，把剩余的每个数组缩成一个数（因为必然全选或全不选）。从前往后跑一遍背包，从后往前跑一遍背包。然后，每次枚举的时候把前后的背包合并，再枚举不满的数组选到哪个位置，剩下的在合并后的背包中查询，时间复杂度 $\mathcal{O}\left(nk^2\right)$，无法通过此题。

考虑优化，容易发现上述做法的时间复杂度瓶颈在于背包的合并，回想传统艺能，发现向背包插入物品的时间复杂度是 $\mathcal{O}\left(k\right)$ 的，所以可以想到利用这个性质。

```
//传统艺能
for(int j = maxw; j >= w; j --) 
	f[j] = max(f[j], f[j - w] + v);
```
分治能很好解决本题，对于一个区间 $\left[l,r\right]$，可以找到一个    `mid = (l + r) >> 1`，把 $\left[mid + 1,r\right]$ 的数插入到背包中，递归求解 $\left[l,mid\right]$；然后**把插入的数回退**，改为插入 $\left[l,mid\right]$ 的数，递归求解 $\left[mid + 1,r\right]$。这样当递归到 `l==r` 时，等价于 $l$ 是我们枚举到的没选满的数组，然后朴素枚举 $l$ 选到哪个位置求解即可，这样的事件复杂度是 $\mathcal{O}\left(nk\log n\right)$ 的，记得注意常数优化。

[Submission](https://codeforces.com/contest/1442/submission/143503744)









$$$$$$$$$$$$$$$$$$$$

---

## 作者：intel_core (赞：5)

首先我们手玩一下这个题的样例：

```
3 3
2 5 10
3 1 2 3
2 1 20
```

很明显，答案是 $1+20+5=26$；如果贪心来选的话答案就是 $5+10+1=16$，所以贪心连样例都过不了。

再用一组数据来举例：

```
2 6
5 1 3 5 7 9
4 2 4 6 8
```

这组数据只有两个数组，枚举两个数组中各取多少数可以知道答案是 $1+3+5+7+9+2=27$。

上面两组数据有一个共同的规律：只有一个数组是取了其中一部分数。

验证更多数据猜出结论：一定存在一种最优决策，使得其中至多一个数组只取了数组中的一部分数。

> 使用反证法证明：最优决策中如果存在两个只取了一部分的数组 $a_{1,\cdots,m},b_{1,\cdots,n}$，分别取了 $x,y$ 个 $(x<m,y<n)$。

> 如果 $a_x \ge b_y$ ，那么取 $a_1,\cdots,a_{x+1},b_1,\cdots,b_{y-1}$，比原取法多 $a_{x+1}-b_y$，又因为 $a_x \le a_{x+1}$，所以新取法总和更大，与最大性矛盾！

> $a_x \le b_y$ 时同理。

所以一定存在一种取法，只有一个数组是只取了其中一部分数。

我们直接枚举是哪一个数组，对其它的完整数组跑背包，复杂度 $O(nk^2)$，仍然不可接受。

刚才这种取法对于每个数组都重新跑背包，浪费了大量时间；我们使用类似于 $\text{CDQ}$ 分治的结构优化这个方法。

* 考虑部分取的数组在 $[l,r]$ 中的最优解。

* 如果 $l=r$，那么直接拿上层递归处理好的背包更新答案。

* 如果 $l<r$，先把 $[mid+1,r]$ 中的元素加入背包，递归计算 $[l,mid]$，再把背包复原，把 $[l,mid]$ 中的元素加入背包，递归计算 $[mid+1,r]$ 。

一共递归了 $\log n$ 层，每层把所有元素放进背包一次，$4n$ 次处理，每次处理复制 2 次数组，所以复杂度 $O(nk \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=3e3+10;
#define int long long
int n,k,ans,cnt[NR],sum[NR];
vector<int>a[NR];
#define pb push_back
#define mid ((l+r)>>1)
int f[NR][20],tmp[NR][20];

void dfs(int l,int r,int col){//部分选的数组在[l,r]中，这是第col层递归 
	if(l==r){
		for(int i=0;i<=min(k,cnt[l]);i++)ans=max(ans,f[k-i][col]+a[l][i]);//更新答案
		return;
	}
	for(int i=0;i<=k;i++)f[i][col+1]=f[i][col];
	for(int i=mid+1;i<=r;i++)//将[mid+1,r]中元素放进背包
		for(int j=k-cnt[i];j>=0;j--)f[j+cnt[i]][col+1]=max(f[j+cnt[i]][col+1],f[j][col+1]+sum[i]);
	dfs(l,mid,col+1);
	for(int i=0;i<=k;i++)f[i][col+1]=f[i][col];
	for(int i=l;i<=mid;i++)//将[l,mid]中元素放进背包
		for(int j=k-cnt[i];j>=0;j--)f[j+cnt[i]][col+1]=max(f[j+cnt[i]][col+1],f[j][col+1]+sum[i]);
	dfs(mid+1,r,col+1);
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>cnt[i];a[i].pb(0);
		for(int j=1,x;j<=cnt[i];j++)
			scanf("%lld",&x),a[i].pb(sum[i]+=x); 
	}
	dfs(1,n,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：A1443356159 (赞：5)

前面的结论与第一篇题解一样，还是只有一个数组不选满其他的都选满。

对于除开一个物品其他物品的背包，可以用分块的思想进行优化。

对于同一个块里的物品，放在一起处理。

具体地，枚举每一个块，将除开这个块内物品的其他物品做一个背包，记录下此时背包状态（就是那个dp数组）。

然后枚举**该块**的每一个物品，用**该块**中的其他物品去更新背包状态，最后更新答案。

设块的大小为 $m$，物品个数为  $n$ ，背包大小为 $k$。

复杂度就是：$\frac{n}{m}(n-m)k+mnk$

当 $m=\sqrt{n}$ 时，复杂度为 $O(n\sqrt{n}k)$ ，虽然没有分治优秀，但勉强能过。

```cpp
#include<stdio.h>
#include<vector>
#include<cstring>
#define LL long long
using namespace std;
const int N=3004;
vector<LL>pre[N];
int n,k,w[N];
LL v[N],dp[N],tmp[N],ans;
int block=40,belong[N];
LL max(LL x,LL y){return x>y?x:y;}
int min(int x,int y){return x<y?x:y;}
int read() {
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main() {
	n=read();k=read();
	for(int i=1;i<=n;++i)belong[i]=(i-1)/block+1;
	for(int i=1;i<=n;++i) {
		w[i]=read();
		pre[i].push_back(0);
		for(int j=1;j<=w[i];++j) {
			int x=read();
			v[i]+=1ll*x;
			pre[i].push_back(0);
			pre[i][j]=pre[i][j-1]+1ll*x;//处理一下没个数组的前缀和，便于统计答案
		}
	}
	for(int i=1;i<=belong[n];++i) {
		memset(dp,0,sizeof(dp));
		for(int j=1;j<=n;++j) {
			if(belong[j]==i)continue;
			for(int m=k;m>=w[j];--m)dp[m]=max(dp[m],dp[m-w[j]]+v[j]);//把块外的其他物品做一个背包
		}
		for(int m=k;m>=1;--m)tmp[m]=dp[m];
		for(int jj=(i-1)*block+1;jj<=i*block&&jj<=n;++jj) {
			for(int m=k;m>=1;--m)dp[m]=tmp[m];//记录一下块外的背包
			for(int j=(i-1)*block+1;j<=i*block&&j<=n;++j) {
				if(j==jj)continue;
				for(int m=k;m>=w[j];--m)dp[m]=max(dp[m],dp[m-w[j]]+v[j]);
			}
			for(int ii=min(pre[jj].size()-1,k);ii>=0;--ii)ans=max(ans,dp[k-ii]+pre[jj][i]);//更新答案
		}
	}
	printf("%lld",ans);
	return 0;
```

---

## 作者：tommymio (赞：5)

可以发现一个结论，存在一种最优解只剩下一个数组未被选择完毕。

设最终剩下 $m$ 个数组未被选择完毕，则可以通过 $2$ 个数组未选择完毕的证明推出 $m$ 个数组的情况。不妨设没被选择完毕的两个数组为 $a,b$，$a$ 数组的选择了前 $i$ 个，$b$ 数组选择了前 $j$ 个，并且 $a_i\leq b_j$，则有 $a_{i-1} \leq a_i \leq b_{j}\leq b_{j+1}$。显然进行微调，将 $b$ 数组先选择完毕不会更劣。

那么，考虑去除掉第 $i$ 个数组后，选择其他整个数组的最大值加上第 $i$ 个数组的值，取 $\max$ 即可。这一部分可以使用分治完成，时间复杂度为 $O(nm \log n)$

```cpp
#include<cstdio>
#include<vector>
typedef long long ll;
int n,k;
ll ans=0,f[3005];
std::vector<ll> a[3005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline ll max(const ll &x,const ll &y) {return x>y? x:y;}
inline void update(int v,ll w) {
    for(register int j=k;j>=v;--j) f[j]=max(f[j],f[j-v]+w);
}
inline void solve(int l,int r) {
    if(l==r) {
        for(register int i=0;i<=min(a[l].size()-1,k);++i) ans=max(ans,f[k-i]+a[l][i]);
        return;
    }
    int mid=l+r>>1; std::vector<ll> tmp;
    for(register int i=0;i<=k;++i) tmp.push_back(f[i]);
    for(register int i=mid+1;i<=r;++i) update(a[i].size()-1,a[i][a[i].size()-1]);
    solve(l,mid);
    for(register int i=0;i<=k;++i) f[i]=tmp[i];
    for(register int i=l;i<=mid;++i) update(a[i].size()-1,a[i][a[i].size()-1]);
    solve(mid+1,r);
    for(register int i=0;i<=k;++i) f[i]=tmp[i];
}
int main() {
    n=read();k=read();
    for(register int i=1;i<=n;++i) {
        int m=read();
        a[i].push_back(0);
        for(register int j=1;j<=m;++j) {
            a[i].push_back(a[i][j-1]+read());
        }
    }
    solve(1,n);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Mr_Wu (赞：3)

vp 的时候调 C 调了一年，结果最后发现这个 D 很简单。。。

由于这题的每个序列都有单调性，所以可以考虑对 DP 数组打表，寻找单调性。但很不幸对于 DP 数组以及最优决策点它们都没有单调性...

但是在手模的同时，可以注意到这样一件事情：至多有一个序列没有选满！即使那个没有选满的序列编号在 $k$ 增加一点点的时候就会反复变化，但事实就是这样子的！

这是不是对的呢？我们可以考虑证明，其实证明它的思路很直接，就是证明若有两个序列没有选满，则可以进行调整。设序列 $a$ 选了 $1\cdots i$，序列 $b$ 选了 $1\cdots j$，那么已知 $a_i\le a_{i+1},b_j\le b_{j+1}$，要证明去 $a_i$ 加 $b_{j+1}$ 和去 $b_j$ 加 $a_{i+1}$ 两种方案至少有一个不会更劣。那么假设都会更劣则 $a_i>b_{j+1},b_j>a_{i+1}$，但第一个条件就导出 $b_j\le b_{j+1}<a_i\le a_{i+1}$，与第二个条件矛盾！

接下来的思路就很清晰了，我们枚举那个没有选满的序列 $i$，然后钦定其它序列要么不选要么选满，这就是一个整体减去 $i$ 的背包。对于这个事情可以考虑线段树分治，对于每个物品 $i$ 将其插入 $[1,i-1]$ 与 $[i+1,n]$，在线段树上走时维护一个记录了前 $n$ 个版本的背包，由于插入一个物品是 $O(n)$ 的，所以时间复杂度是 $O(n^2\log n)$。

---

## 作者：Tony102 (赞：3)

 [Link](https://www.luogu.com.cn/problem/CF1442D)

[Blog阅读效果更佳](https://tony102.xyz/index.php/2021/02/18/cf1442d-sum/)


### Sol

贪心策略：除了一个数组不选完外，其余的数组全部选完为最优。

那么现在怎么样来选择数组。假如是全部都是选整个数组的话，我们把数组长度看成体积，整个数组的和看成价值做背包即可。现在的问题是，我们有一个数组不能全部选满，怎么做？

采用分治的办法解决。是不是我们可以把所有数组分成两项来合并答案，当我们递归进单个数组的时候对这个数组进行背包，更新答案。否则我们可以先把每次分治的左边的数组全部选满，做一次背包。拷贝下当前的dp数组，来算那个不选满的数组出现在右边的答案。再同样处理左边即可。



[Code戳这里](https://tony102.xyz/index.php/2021/02/18/cf1442d-sum/)



---

## 作者：Others (赞：1)

老师讲得很迷，还是我自己口胡出来了。

理解题意，就是在每个栈选前几个，然后

首先可以想到搞个前缀和做个分组背包，枚举每个栈，枚举选几个，再跑一遍 $k$，总复杂度 $O(n^2k)$，肯定爆。

然后就是找规律了，~~打表~~观察可以合理猜测只有一个栈没选完，证明一下：

假设有栈 $i_1,i_2$ 分别选了 $f_{i_1},f_{i_2}$ 个元素，两个栈没选的在栈顶的元素是 $a_{i_1,f_{i_1}+1},a_{i_2,f_{i_2}}$，若其中一个比另一个大，那取下另一个栈最后选的，加入这个栈的栈顶，不断操作直到这个栈选完或另一个栈都没选。但是有个误区：如果“另一个栈”后面有个 $inf$，那岂不是爆掉了？**注意**，这里的 $i_1,i_2$ 是没定的，意思是对于正常情况下，而不是存在极大或极小的情况（这里没有极小）。

综上，这个结论正确。这样我们可以把一些栈整个拿来跑背包（~~绿色，节能~~），我不假思索就拍了个还是 $O(n^2k)$ 的暴力：先枚举哪个栈选了一部分，剩下的 $O(nk)$ 跑 $01$ 背包，很符合我们之前的想法，但是哪里爆了呢？

举个例子：$n=5$，没选的栈的编号 $i$ 是 $1$，若 $i=2$ 那 $[3,5]$ 里的 $01$ 白白的多跑了一遍，这就很不爽。我们想想这里只有一个特殊的，于是可以想到以前的一道分治模板：“找不同”（找序列中唯一不同的数）。这题套个分治的话，我们将区间分成两段，先假设没选完的栈在左边，那右边肯定可以跑 $01$，然后在左边分治，总共 $\log n$ 层，每层 $n$ 个元素，每个元素 $O(k)$ 的背包，总复杂度 $O(nk\log n)$，在最后一层如果是没选完的栈就枚举一遍 $dp$ 数组，更新答案即可。

**Code**

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
template<typename zqw>void qr(zqw &x) {
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
	return ;
}
int a[3005][3005],k,n;
ll dp[3005],S[3005],sum[3005][3005],ans;
void fz(int l,int r,bool typ) {
	if(!typ) {
		for(int i=l;i<=r;i++) for(int j=k;j>=a[i][0];j--) dp[j]=max(dp[j],dp[j-a[i][0]]+S[i]);
		return ;
	}
	if(l==r) {
		for(int x=k;x>=0&&k-x<=a[l][0];x--) ans=max(ans,dp[x]+sum[l][k-x]);
		return ;
	}
	ll lxl[3005];
	for(int i=1;i<=k;i++) lxl[i]=dp[i];
	int mid=l+r>>1;
	fz(l,mid,0),fz(mid+1,r,1);
	for(int i=1;i<=k;i++) dp[i]=lxl[i];
	fz(mid+1,r,0),fz(l,mid,1);
}
int main() {
	qr(n),qr(k);
	for(int i=1;i<=n;i++) {
		qr(a[i][0]);
		for(int j=1,K=min(a[i][0],k);j<=K;j++) qr(a[i][j]),sum[i][j]=sum[i][j-1]+a[i][j],S[i]+=a[i][j];
		for(int j=1,baocho;j<=a[i][0]-k;j++) qr(baocho);
	}
	fz(1,n,1);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1442D)

## $\text{Description}$

- 给定 $n$ 个非降序列，你要取他们的前缀使得元素个数为 $k$ 且元素和最大。

- 求最大元素和。

## $\text{Solution}$

对于所有序列，显然选部分的序列个数 $\le 1$，其它全选或全不选。

考虑证明这个结论。

如果有 $2$ 个选部分的序列 $\{a_n\}$，$\{b_m\}$，不妨设 $\{a_n\}$ 选到了 $a_i$，$\{b_m\}$ 选到了 $b_j$。

不妨设 $a_i\ge b_j$。

显然我们可以把选的 $\{b_m\}$ 中的元素替换成 $\{a_n\}$ 中未选的元素。

由于数列非降，所以有 $a_{i+1}\ge a_i\ge b_j\ge b_{j-1}$，令 $i+1\to i$，$j-1\to j$。如此迭代直到 $i=n$ 或 $j=0$。

这样我们通过调整得到了更优解。结论成立。

从而有了上述结论，我们只要枚举哪个选部分，其余数列当做 $01$ 背包问题即可。

我不知道背包能不能删除物品，不太会。/kk

（如果可以能告诉我做法吗。/kel）

因此我们分治处理即可。时间复杂度 $O(nk\log n)$。

有个小 tip，寄存当前答案时记得开在函数内，别像我开在全局然后直接被后面顶掉。（然而我觉得没人会像我这样写。）

## $\text{Code}$

```cpp
const int N=3e3+5;
int n,k;
ll ans,t[N],s[N];
vector<ll> a[N],f;

#define mid ((l+r)>>1)

inline void solve(int l,int r){
//	cout<<l<<' '<<r<<endl;
//	for(re i=0;i<=k;++i) cout<<f[i]<<' ';cout<<"qaq"<<endl; 
	if(l==r){
		ll sum=0;
		for(re i=0;i<k&&i<t[l];++i) sum+=a[l][i],ans=max(ans,f[k-i-1]+sum);
//		cout<<ans<<endl;
		return ;
	}
	vector<ll> tmp=f;
	for(re i=l;i<=mid;++i)
		for(re j=k;j>=t[i];--j) f[j]=max(f[j-t[i]]+s[i],f[j]);
	solve(mid+1,r);
	f=tmp;
	for(re i=mid+1;i<=r;++i)
		for(re j=k;j>=t[i];--j) f[j]=max(f[j-t[i]]+s[i],f[j]);
	solve(l,mid);
}

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(k);f.resize(k+10);
	for(re i=1;i<=n;++i){
		rd(t[i]);ll x;
		for(re j=1;j<=t[i];++j) rd(x),a[i].pb(x),s[i]+=x;
	}
	solve(1,n);wr(ans);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2800}$
---
### 解题思路：

由于每一个数组不降，容易想到选择的情况一定是完整地选出了若干个数组，最后可能存在一个数组没有选完。

于是想到枚举出未选完的数组，并对于其它的数组做一个 $01$ 背包，最后对于每一个位置比较出最终答案。这个做法的复杂度是 $O(nk^2)$，不能接受。

分析进行背包的过程，发现这其中有大量的过程是重复进行的动态规划转移，尝试使用一种方法将这些位置的贡献保留到下一次操作中。

---
考虑分治，令当前处理区间以外的所有位置上的数组都已经被作为物品插入到背包中，每一次将当前区间的一半物品插入背包，递归另一半物品。这样处理到位置 $[x,x]$ 的时候也就是出现了其它所有位置都作为 $01$ 背包物品的情况了。

具体地，对于数组区间 $[l,r]$，将 $[mid+1,r]$ 作为 $01$ 背包的物品插入，对于 $[l,mid]$ 进行递归。在递归完成后对称的将 $[l,mid]$ 插入背包，递归 $[mid,r]$，最后对于 $[x,x]$ 单独处理。

---
这个方法的复杂度是 $O(nk\log n)$ 的，可以通过。

复杂度少了的部分就是反复将同一个数组插入的过程，原本每一个数组都需要插入 $n$ 次，而在优化后每一层递归只需要插入一次，也就是 $\log n$ 次。

---
### 代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
#define int long long
const int MAXN=3005;
int n,k,ans,size[MAXN],sum[MAXN];
vector <int> f,a[MAXN];
void dp(int l,int r){
	if(l==r){
		int SUM=0;
		for(int i=0;i<=min(k,size[l]);i++){
			SUM+=a[l][i];
			ans=max(ans,SUM+f[k-i]);
		}
		return;
	}
	vector <int> tmp=f;
	int mid=(l+r)>>1;
	for(int i=mid+1;i<=r;i++)
	for(int j=k;j>=size[i];j--)
	f[j]=max(f[j],f[j-size[i]]+sum[i]);
	dp(l,mid);
	f=tmp;
	for(int i=l;i<=mid;i++)
	for(int j=k;j>=size[i];j--)
	f[j]=max(f[j],f[j-size[i]]+sum[i]);
	dp(mid+1,r);
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&size[i]);
		a[i].resize(size[i]+1);
		for(int j=1;j<=size[i];j++)
		scanf("%lld",&a[i][j]),sum[i]+=a[i][j];
	}
	f.resize(k+1);
	dp(1,n);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Wsy_flying_forever (赞：0)

根据不降，我们首先可以发现一个性质：最优解只有一个数组是不满的   
简单证明一下，假设至少有两个数组不满。 设其中两个分别为 $a$,$b$ 。  
满足 $a_i > b_j$ ，我们容易得到 $b_{j-1}$ 、 $b_j$ 其实并没有 $a_i$ 、 $a_{i+1}$ 更优，性质得证。 
#### Part 1  
暴力枚举，时间复杂度 $\mathcal{O}(n^2k^2)$
#### Part 2  
枚举不满数组，将前后两个背包合并，时间复杂度 $\mathcal{O}(nk^2)$
#### Part 3 
我们考虑到时间复杂度的瓶颈是在于合并两个背包数组，合并复杂度 $\mathcal{O}(k^2)$ ，单次插入复杂度 $\mathcal{O}(k)$ ，我们便可以使用这个性质。 考虑分治，对于区间 $(l,r)$ ，我们可以找到一个 $mid$ ，将 $(mid+1,r)$ 的数进行背包，递归求解 $(l,mid)$ ，然后进行回溯，并对区间 $(mid+1,r)$ 执行和刚才一样的预处理和操作。 时间复杂度变为 $\mathcal{O}(nklogk)$ ，可以通过本题。  
代码如下： 
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=3e3+10;
typedef long long LL;
int n,k;
vector <int> a[maxn];
LL ans,sum[maxn],f[maxn];
int len[maxn];
inline void dfs(int l,int r) {
	if (l==r) {
		LL tsum=0;	
		ans=max(ans,f[k]);
		for (int i=1;i<=len[l];i++) {
			tsum+=a[l][i-1];
		    if (k>=i) ans=max(ans,f[k-i]+tsum);
		      else break;
		}
		return ;
	}
	int mid=(l+r)>>1;
	LL tmp[maxn];
	for (int i=0;i<=k;i++) tmp[i]=f[i];
	for (int i=mid+1;i<=r;i++) {
		for (int j=k;j>=len[i];j--)
		  f[j]=max(f[j],f[j-len[i]]+sum[i]);
	}
	dfs(l,mid);
	for (int i=0;i<=k;i++) f[i]=tmp[i];
	for (int i=l;i<=mid;i++) {
		for (int j=k;j>=len[i];j--)
		  f[j]=max(f[j],f[j-len[i]]+sum[i]);
	}
	dfs(mid+1,r);
}
int main() {
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) {
		scanf("%d",&len[i]);
		for (int j=1;j<=len[i];j++) {
			int x;
			scanf("%d",&x);
			sum[i]+=x;
			a[i].push_back(x);
		}
	}
	dfs(1,n);
	printf("%lld\n",ans);
	return 0;
} 
```


---

## 作者：do_while_true (赞：0)

要取的话一定是全取完，如果没取完一个数组 $x$ 就去取另外一个数组 $y$ 更优的话，那么把取 $x$ 的机会用到取 $y$ 上会更优，这样就变成取完 $y$ 再取 $x$，依然满足结论。

那就变成选出一些数组，把它们全取了，然后再在一个数组里面选一个前缀。

那就把数组看成物品，问题变成经典问题问删除一个物品之后的最优化背包，这个分治解决，大概就是递归 $[l,r]$ 时，把 $[l,mid]$ 插入的背包中，然后递归求解 $[mid+1,r]$，然后再返回插入前的状态，把 $[mid+1,r]$ 塞进去，递归求解 $[l,mid]$．

复杂度就是 $\mathcal{O}(nk\log n)$．

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int,int>pii;
typedef std::pair<ll,int>pli;
typedef std::pair<ll,ll>pll;
typedef std::vector<int>vi;
typedef std::vector<ll>vll;
template<typename T>T cmax(T &x, T y){ return x=x>y?x:y; }
template<typename T>T cmin(T &x, T y){ return x=x<y?x:y; }
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=3010;
int n,k;
ll ans,a[N][N];
void solve(int l,int r,vll g){
	if(l==r){
		cmax(ans,g[k]);
		for(int i=1;i<=min((int)a[l][0],k);i++)cmax(ans,a[l][i]+g[k-i]);
		return ;
	}
	vll f=g; int mid=(l+r)>>1;
	for(int i=mid+1;i<=r;i++){
		int w=a[i][0]; ll v=a[i][a[i][0]];
		for(int j=k;j>=w;j--)cmax(f[j],f[j-w]+v);
	}
	solve(l,mid,f);
	f=g;
	for(int i=l;i<=mid;i++){
		int w=a[i][0]; ll v=a[i][a[i][0]];
		for(int j=k;j>=w;j--)cmax(f[j],f[j-w]+v);
	}
	solve(mid+1,r,f);
}
signed main(){
	read(n,k);
	for(int i=1;i<=n;i++){
		read(a[i][0]);
		for(int j=1;j<=a[i][0];j++)read(a[i][j]),a[i][j]+=j==1?0:a[i][j-1];
	}
	solve(1,n,vll(k+1));
	cout << ans << '\n';
	return 0;
}
```

---

