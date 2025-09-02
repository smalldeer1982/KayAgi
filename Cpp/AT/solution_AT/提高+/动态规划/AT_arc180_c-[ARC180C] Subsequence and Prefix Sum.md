# [ARC180C] Subsequence and Prefix Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_c

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます．

あなたは以下の操作をちょうど $ 1 $ 回行います．

- $ A $ の (連続とは限らない) 非空な部分列を選び，それを累積和で置き換える． より正確に述べれば，まず $ 1\ \leq\ i_1\ <\ i_2\ <\ \cdots\ <\ i_k\ \leq\ N $ を満たす添字の列 $ (i_1,i_2,\cdots,i_k) $ を選ぶ． 列の長さ $ k $ ($ 1\ \leq\ k\ \leq\ N $) も自由に選べる． その後，各 $ j $ ($ 1\ \leq\ j\ \leq\ k $) について，$ A_{i_j} $ の値を $ \sum_{1\ \leq\ x\ \leq\ j}\ A_{i_x} $ で置き換える． この置き換えはすべて同時に行う．
 
操作後の $ A $ としてあり得る数列の個数を $ 10^9+7 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ -10\ \leq\ A_i\ \leq\ 10 $
- 入力される値はすべて整数
 
### Sample Explanation 1

操作後の $ A $ としてありうるのは以下の $ 4 $ 通りです． - $ A=(1,1,2) $: $ k=1 $, $ (i_1)=(1) $ とすれば達成できます． - $ A=(1,2,2) $: $ k=2 $, $ (i_1,i_2)=(1,2) $ とすれば達成できます． - $ A=(1,1,3) $: $ k=2 $, $ (i_1,i_2)=(1,3) $ とすれば達成できます． - $ A=(1,2,4) $: $ k=3 $, $ (i_1,i_2,i_3)=(1,2,3) $ とすれば達成できます．

## 样例 #1

### 输入

```
3
1 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 -1 1 -1```

### 输出

```
8```

## 样例 #3

### 输入

```
5
0 0 0 0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
40
2 -2 1 3 -3 -1 -2 -3 0 -1 -2 0 -3 0 0 2 0 -1 2 -2 -2 -1 3 -2 -2 -2 2 3 2 -3 0 -2 2 1 3 0 -1 0 -2 -3```

### 输出

```
420429545```

# 题解

## 作者：Phartial (赞：9)

题意：给你一个长度为 $N$ 的序列 $A$，你需要选出 $A$ 的恰好一个非空子序列，然后将这一子序列替换为其前缀和。求能得到多少种本质不同的序列，对 $10^9+7$ 取模。

$N\le 100$，$-10\le A_i\le 10$.

不知道为啥感觉想起来比 B 顺一些……

考虑 dp。设 $f(i,j)$ 表示只考虑序列 $A$ 的前 $i$ 项，且选出的子序列和为 $j$ 的方案数。

转移只需要考虑 $A_i$ 要不要选进子序列，非常和谐。

但是有一个问题：这个 dp 会把值相同但位置不同的情况视作两种，但实际上只有一种（考虑 `0 1 1 2`，选 $(1,2,4)$ 和 $(1,3,4)$ 得到的序列是一样的，但在 dp 中会被记作两种）。

核心问题在于当前面的子序列和为 $0$ 时，当前位选的表现和不选的表现是一样的，但它们又会对之后造成不同的影响。考虑将选的情况切割出来，单独记一个状态 $g(i)$ 表示当前选出的子序列除最后一个外的和为 $0$，且最后一个为 $i$，那么我们就可以从 $f(i-1,0)$ 转移到 $g(A_i)$，或者从 $g(j)$ 转移回 $f(i,j+A_i)$。

时间复杂度 $\Theta(N \sum A)$，不小心爆标了/tx.

[code](https://atcoder.jp/contests/arc180/submissions/55205342).

---

## 作者：Neil_Qian (赞：3)

## [ARC180C] Subsequence and Prefix Sum 题解

### 题目描述

给出一个序列，选出任意一个子序列，将其前缀和填入原序列。

$n\le 100,-10\le a_i\le 10$。

### 解决方案

注意到值域极小，前缀和产生的贡献完全可以进行统计，因此记 $dp_{i,j}$ 表示讨论到位置 $i$，前缀和为 $j$ 的方案数。为了方便，令此时必选 $i$。转移非常简单。

但这样有一个巨大的问题，如果 $j=0$，有些方案会重复，需要单独讨论。在往后更新的时候，在枚举转移到哪一个的基础上再枚举一个类似中转点的东西，并且它不为零，这样就避免了重复。但时间复杂度会到 $O(n^4V)$，可能会超时，因此考虑每次右移 $k$ 的时候，记录 $app_i$ 表示 $i$ 是否出现即可。这样时间复杂度为 $O(n^3V^2)$，可以通过。

另外，还可以什么都不干。这也是一种方案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;
const int N=102,MOD=1e9+7;ll n,a[N],dp[N][20*N],ans;
inline ll& f(int i,int j){return dp[i][j+1005];}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<=n;i++){
		if(!i){
			for(int j=-1002;j<=1002;j++)f(i,j)=(j!=0?0:1);
		}
		for(int j=-1002;j<=1002;j++)if(f(i,j)){
			if(j!=0){
				for(int k=i+1;k<=n;k++)(f(k,j+a[k])+=f(i,j))%=MOD;
			}
			else{
				bool app[25];memset(app,0,sizeof(app));
				for(int k=i+1;k<=n;k++){
					for(int l=-10;l<=10;l++)if(app[l+12])(f(k,j+l+a[k])+=f(i,j))%=MOD;
					if(a[k]!=0)app[a[k]+12]=1;
				}
			}
			if(i)(ans+=f(i,j))%=MOD;
		}
	}
	return cout<<(ans+1)%MOD<<"\n",0;
}
```

---

## 作者：_lmh_ (赞：3)

一个很显然的想法是 dp，设 $f_{i,j}$ 代表前 $i$ 个数，目前选的东西总和为 $j$ 的方案数。

转移也显得很对，但是在 $j=0$ 时会出问题。

原因是 $j=0$ 代表下一次选择数的时候不会对它造成影响。同时，考虑如下输入：

```
4
0 1 1 2
```

如果选择了 0 1 2 的话，这个 dp 会把两种选择方案全部算进去，但你无法分辨具体选的是哪一种。

所以开一个 $g$ 数组记录目前总和为 $j$ 且上一次总和为 0 的方案数。考虑到一个总和为 0 的方案下一次选的数只要值相同那么选哪一个没有区别，所以每次给 $g_{a_i}$ 赋值 $g_0$，再给 $g_0$ 赋值 $f_{i,0}$ 就行了。（其他的 $g$ 值直接转移到 $f$ 上面去。）

其余细节可以参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=107,MOD=1e9+7;
ll n,F[N][2007],a[N],G[2007],sum,ans;
ll *f[N],*g;
void add(ll& x,ll y){x+=y;if (x>=MOD) x-=MOD;}
int main(){
	g=G+1003;
	for (int i=0;i<N;++i){
		f[i]=F[i]+1003;
	}
	cin>>n;
	f[0][0]=g[0]=1;
	for (int i=1;i<=n;++i){
		cin>>a[i];
		for (int j=-sum;j<=sum;++j){
			add(f[i][j],f[i-1][j]);
			if (j) {add(f[i][j+a[i]],f[i-1][j]);add(f[i][j+a[i]],g[j]);}
		}
		g[a[i]]=g[0];g[0]=f[i][0];
		sum+=abs(a[i]);
	}
	for (int i=-sum;i<=sum;++i) add(ans,f[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：liyixin0514 (赞：1)

# [Subsequence and Prefix Sum](https://www.luogu.com.cn/problem/AT_arc180_c)

$n$ 才 $100$，$a_i$ 才 $20$，显然 DP。

设 $f_{i,j}$ 表示第 $i$ 个数，前 $i$ 个数前缀和为 $j$ 的方案数。

显然，$f_{0,0}=1$。

留意到如果 $j=0$，那么加入和不加入第 $i$ 个数，最终的答案序列是一样的，因此此时加入第 $i$ 个数对答案是没有贡献的，但是加入后会对之后的前缀和产生影响，会影响之后的序列。因此 $f_i$ 不能统计答案，而 $f_{i+1}$ 应该统计这种情况。

我们设 $g_k$ 表示这种情况，也就是加入 $k$ 后前缀和为 $k$ 的方案数。

当 $j\ne 0$ 时，$f_{i,j+a_i}$ 不仅要统计前一位前缀和为 $j$ 的方案数，还应统计之前某一位没有计入答案但是对前缀和产生影响的情况，即 $g_j$。

转移方程如下：

- 第 $i$ 个数不加入前缀和中：$f_{i,j}\gets f_{i-1,j}$
- 第 $i$ 个数加入前缀和中：$[j\ne 0]\ f_{i,j+a_i}\gets f_{i-1,j}+g_j$
- 枚举完 $j$ 之后：$g_{a_i}\gets f_{i-1,0}$

答案即为 $\sum_j f_{n,j}$

因为值有负数，所以下标需要调整，注意细节。

综上，时间复杂度 $O(n^2V)$。

## Code

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
using namespace std;
typedef long long ll;
const int N=101,mod=1e9+7,M=1001;
int n,a[N],b[N];
ll dp[N][2010];
ll g[2010];
void add(ll &a,ll b){
	a=(a+b)%mod;
}
int main(){
	sf("%d",&n);
	for(int i=1;i<=n;i++){
		sf("%d",&a[i]);
		b[i]=b[i-1]+a[i];
	}
	dp[0][M]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=M<<1;j++){
			add(dp[i][j],dp[i-1][j]);
			if(j!=M){
				add(dp[i][j+a[i]],dp[i-1][j]+g[j]);
			}
		}
		g[a[i]+M]=dp[i-1][M];
	}
	ll ans=0;
	for(int i=0;i<=M<<1;i++) add(ans,dp[n][i]);
	pf("%lld\n",ans);
}
```

---

## 作者：ClearluvXL (赞：0)

# C - Subsequence and Prefix Sum

## 思路

靠考虑到值域很小，所以我们能把前 $i$ 个数前缀和为 $j$ 给表示出来，只不过需要注意到负数下标，可以开个 map 搞定。

现在只需要考虑是否将第 $i$ 个位置放入前缀即可。

但是这样会算重复的答案，如样例 1 `1 1 2`，选 $(1,2),(1,3)$，其实是一个效果的。也就是说，如果统计到当前的前缀和为 $0$ 的话，那么之后加上相同的数后，对后面的数的方案相当于只有一种有效。

为了避免上述情况，我们开一个 $g$ 数组，来统计和为 $j$，且到上一个时前缀和是 $0$ 的方案数，这样我们就能避免重复的了。

至于每次的转移 $f$ 就从 $g$ 转移即可。并且将新的 $g_{a_{i}}=f_{i-1,0}$。

## 代码

```c++
#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N=110;
const int mod=1e9+7;

typedef long long ll;
typedef pair<int,int> pii;

int n;
int a[N];
map<int,ll> f[N],g;


int main(){
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	
	ios::sync_with_stdio(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	f[0][0]=1;
	
	for(int i=1;i<=n;i++){
		for(int j=-1000;j<=1000;j++){
			f[i][j]+=f[i-1][j];//不选i时
			if(j) {//前缀和不为 0时 
				f[i][j+a[i]]+=f[i-1][j]+g[j]; 
			}
			f[i][j+a[i]]%=mod;
		}
		g[a[i]]=f[i-1][0];
		g[a[i]]%=mod;
	}	
	
	ll ans=0;
	
	for(int j=-1000;j<=1000;j++){
		ans+=f[n][j];
		ans%=mod;
	}
	
	cout<<ans<<endl;
}//end
```

---

## 作者：TTpandaS (赞：0)

先考虑选出的数之和不为 $0$ 的情况。 

如果选出的数之和的方案不同，那么变化后的 $A$ 一定不同。因此定义 $dp_{i,j}$ 表示前 $i$ 个数中，选择了第 $i$ 个数后总和为 $j$ 的方案数。那么 $dp_{i,j}= \sum_{k=1}^{i-1}dp_{k,j-a_i}$。

接着考虑选出的数之和为 $0$ 的情况。

如果当前的和为 $0$，那么上一个数如果取相同的值，但是位置不同，是无法区分的。所以每次从大到小寻找第一个使得上一次的和为 $0$ 的 $k$，那么在 $dp_{i,j}$ 加上它对答案的贡献，在统计答案时都不统计 $j=0$ 的方案数即可。

还有一点。如果 $j=a_i$，那么所有 $a_k=0$ 都是不用统计的。

---

