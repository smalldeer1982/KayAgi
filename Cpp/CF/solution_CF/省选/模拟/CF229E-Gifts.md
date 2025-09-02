# Gifts

## 题目描述

很久很久以前，一位老人和妻子住在海边。一天，他前去捕鱼，捉到了一条活着的金鱼。鱼说：“老渔人！我求你放我回到海里，我会给你$n$个礼物——任何你想要的礼物！”然后鱼给了老人一张礼物的清单并附上了礼物的价值。礼物可能有相同的名称、不同的价值，也可能会有不同的名称、相同的价值。然而，不会出现名称和价值都相同的礼物。老人可以要清单上的$n$个礼物。假设清单上共有 $p$ 样与该礼物名称相同的礼物（包括自身），则该礼物不能被索要超过 $p$ 次。

老人知道，如果他索要同一个名称的礼物$s$次，那么金鱼会等概率地随机选择该名称的$s$样礼物。为了满足他贪心的妻子，他会选择价值最高的$n$样礼物。此外，如果有不同的方法选择最高价值的$n$样礼物，他会等概率地采用其中任意一个方法。

老人想知道，他能拿到$n$样价值最高的礼物的概率是多少。由于他不擅长概率论，于是就来向你求助。

## 样例 #1

### 输入

```
3 1
3 10 20 30
```

### 输出

```
1.000000000
```

## 样例 #2

### 输入

```
3 2
1 40
4 10 20 30 40
```

### 输出

```
0.166666667
```

# 题解

## 作者：Lvlinxi2010 (赞：1)

我们将所有物品按价格排序。

首先我们可以发现，如果价值第 $n$ 大的物品严格大于第 $n+1$ 大的物品，那么老人选择的方案唯一。

我们设价值第 $n$ 大的物品价值为 $v$，我们设 $cnt1$ 为前 $n$ 大需要选择的价值为 $v$ 的物品的个数，$cnt2$ 为价值为 $v$ 的物品的总数，那么老人有 $\dbinom{cnt2}{cnt1}$ 种方案，老人会等概率选择其中一个。

我们令 $dp_{i,j}$ 表示前 $i$ 种名字种选了 $j$ 个价值为 $v$ 的物品选到最大的 $n$ 个的最大概率。

令 $a_i$ 表示第 $i$ 个名字中价值严格大于 $v$ 的物品的个数（即必选的物品的个数）。

若一个名字没有价值为 $v$ 的物品：

$dp_{i,j}=dp_{i-1,j}\times \frac{1}{\tbinom{k_i}{a_i}}$

若一个名字有价值为 $v$ 的物品（依题意得没有两个名字和价格都相等的物品所以最多一个），可以选择选或不选：

$dp_{i,j}=dp_{i-1,j}\times \frac{1}{\tbinom{k_i}{a_i}}+dp_{i-1,j-1}\times \frac{1}{\tbinom{k_i}{a_i+1}}$

最后答案即 $dp_{m,cnt1}\times \frac{1}{\tbinom{cnt2}{cnt1}}$。

附上代码：


```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 1e3 + 10;

int cnt[MAXN],a[MAXN];
double f[MAXN][MAXN],C[MAXN][MAXN];
bool v[MAXN];
vector<int>G[MAXN],E;

signed main(){
	int n,m;
	scanf("%d%d",&n,&m);
	FL(i,0,MAXN-1){
		C[i][0]=C[i][i]=1;
		FL(j,1,i-1) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	FL(i,1,m){
		scanf("%d",&cnt[i]);
		FL(j,1,cnt[i]){
			int x;
			scanf("%d",&x);
			G[i].push_back(x);
			E.push_back(x);
		}
		sort(G[i].begin(),G[i].end());
	}
	sort(E.begin(),E.end(),greater<int>());
	int cnt1=0,cnt2=0,id=n-1;
	while(E[id]==E[n-1]) cnt1++,id--;
	FL(i,1,m){
		for(int j:G[i]){
			if(j>E[n-1]) a[i]++;
			if(j==E[n-1]) v[i]=1,cnt2++;
		}
	}
	f[0][0]=1;
	FL(i,1,m){
		FL(j,0,cnt1){
			f[i][j]+=f[i-1][j]/C[cnt[i]][a[i]];
			if(j&&v[i]) f[i][j]+=f[i-1][j-1]/C[cnt[i]][a[i]+1];
		}
	}
	printf("%.10lf\n",f[m][cnt1]/C[cnt2][cnt1]);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

设第 $n$ 大的物品价值为 $t$。那么所有价值大于 $t$ 的物品都需要被询问至少一次。对于所有等于 $t$ 的物品，假设有 $p$ 个，要选出 $q$ 个，那么就是相当于在 $q$ 个包含价值等于 $t$ 物品的名称中多选一个。

设 $dp_{i,j}$ 为看到第 $i$ 个名字，选出 $j$ 个多询问一次的所有方案中，选到价值最大的概率。如果一个名字不存在等于 $t$ 的物品，转移是容易的。否则分是否选择一个价值等于 $t$ 的物品分别转移到 $dp_{i,j+1}$，$dp_{i,j}$ 即可。具体见代码。代码中 `C[i][j]` 为 $\frac{1}{\binom i j}$。

总复杂度 $O(m\sum k_i)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[1005],all;
int k[1005];
double C[1005][1005];
double dp[1005][1005];
signed main(){
	for(int i=0;i<=1000;i++) C[i][0]=1;
	for(int i=1;i<=1000;i++) for(int j=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
	for(int i=0;i<=1000;i++) for(int j=0;j<=i;j++) C[i][j]=1.0/C[i][j];
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>k[i];
		for(int j=1;j<=k[i];j++){
			int x; cin>>x;
			vc[i].push_back(x);
			all.push_back(x);
		}
		sort(vc[i].begin(),vc[i].end());
	}
	sort(all.begin(),all.end()); reverse(all.begin(),all.end());
	int cnt=0,cs=0,qval=all[n-1];
	for(int i=n-1;i>=0&&all[i]==all[n-1];i--) cs++;
	for(auto v:all) if(v==qval) cnt++;
	dp[0][0]=1;
	for(int i=1;i<=m;i++){
		int xl=lower_bound(vc[i].begin(),vc[i].end(),qval)-vc[i].begin();
		int yl=upper_bound(vc[i].begin(),vc[i].end(),qval)-vc[i].begin();
		if(xl==yl){
			for(int j=0;j<=cs;j++){
				dp[i][j]+=dp[i-1][j]*C[vc[i].size()][vc[i].size()-xl];
			}
		}
		else{
			for(int j=0;j<=cs;j++){
				dp[i][j]+=dp[i-1][j]*C[vc[i].size()][vc[i].size()-yl];
				dp[i][j+1]+=dp[i-1][j]*C[vc[i].size()][vc[i].size()-xl];
			}
		}
	}
	cout<<fixed<<setprecision(10)<<dp[m][cs]*C[cnt][cs];
	return 0;
}
```

---

## 作者：liaoz123 (赞：0)

首先先给所有物品一起排个序，然后从大到小选择，如果价值为 $x$ 的物品选完后，已选物品总数仍然小于 $n$，那么可以继续选。

当已选物品达到 $n$ 时，可能会出现存在多个可供选择的物品的情况。此时我们针对这些特殊物品单独进行考虑。

由于涉及到选与不选的方案选择问题，我们考虑动态规划，设 $f_{i,j}$ 表示前 $i$ 个组中，选择了 $j$ 个特殊物品的概率。第 $i$ 组物品有 $cnt_i$ 个物品，必选的物品数量为 $c_i$。对于当前枚举到的物品组，分两种情况：

$\bullet$ 不包含特殊物品，直接乘上选必选物品的概率即可。
$$f_{i,j}=f_{i-1,j}*\frac{1}{\dbinom{cnt_i}{c_i}}$$

$\bullet$ 包含特殊物品，考虑选不选特殊物品。不选的方程同上。
$$f_{i,j}=f_{i-1,j-1}*\frac{1}{\dbinom{cnt_i}{c_i+1}}$$

最终计算出的答案包含了从所有特殊物品中，选择我们需要的个数的总概率，我还们应当除以从所有特殊物品中选择目标物品的方案数，即再除以 $\dbinom{tot}{need}$，得到最终答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int cnt[N],n,m,cc,c[N],ned,tot;
bool vis[N];
double C[N][N];
struct node{
	int id,x;
	bool operator <(const node a)const{
		return x>a.x;
	}
}a[N*N];
void pre(){
	C[0][0]=1;
	for(int i=1;i<1001;i++)
	for(int j=0;j<=i;j++){
		if(!j)C[i][j]=1;
		else C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	for(int i=0;i<1001;i++)
	for(int j=0;j<=i;j++)
	C[i][j]=1.0/C[i][j];
}
bool cmp(int x,int y){
	double dx=C[cnt[x]][c[x]+1]/C[cnt[x]][c[x]];
	double dy=C[cnt[y]][c[y]+1]/C[cnt[y]][c[y]];
	return dx>dy;
}
double f[N][N];
int main(){
	scanf("%d%d",&n,&m);pre();
	for(int i=1;i<=m;i++){
		scanf("%d",&cnt[i]);
		for(int j=1;j<=cnt[i];j++){
			int x;scanf("%d",&x);
			a[++cc].id=i,a[cc].x=x;
		}
	}
	sort(a+1,a+cc+1);
	for(int i=1;i<=n;){
		int j=i;
		while(j+1<=cc&&a[j+1].x==a[i].x)j++;
		if(j<=n){
			for(int z=i;z<=j;z++)
			c[a[z].id]++;
		}
		else{
			for(int z=i;z<=j;z++)
			vis[a[z].id]=true,tot++;
			ned=n-i+1;
			break;
		}
		i=j+1;
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++)
	for(int j=0;j<=ned;j++){
		if(!vis[i])f[i][j]+=f[i-1][j]*C[cnt[i]][c[i]];
		else{
			f[i][j]+=f[i-1][j]*C[cnt[i]][c[i]];
			f[i][j]+=f[i-1][j-1]*C[cnt[i]][c[i]+1];
		}
	}
	printf("%.10lf\n",C[tot][ned]*f[m][ned]);
	return 0;
}
```

---

## 作者：x383494 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/x383494/p/17781513.html)

## 前言

基本是官方题解的思路。

## 分析

先考虑不用纠结的情况。假设第 $n+1$ 大价值的物品的价值小于第 $n$ 大的。

此时物品名称集合可以确定。

对于每类名称，恰好拿到的概率为 $\dbinom{k_i}{a_i}^{-1}$，$a_i$ 为选择的物品数量，$k_i$ 为总数。

对于不同类名称，鱼的选择间独立。将这些概率乘起来就行了。

再考虑要纠结的情况。假设和第 $n$ 大价值的物品相同价值的是第 $l$ 到 $r$ 个，$l \le n \lt r$。

一种做法是，暴力求出所有 $\dbinom{r-l+1}{n-l+1}$ 种情况，对于它们的概率取平均值。

对于所有种情况的概率之和，可以 dp 求出。具体地，设 $dp(i,j)$ 为 $[l, l+i)$ 中的物品，选了 $j$ 个，所有合法情况的概率之和，那么 $dp(r-l+1, n-l+1)$ 即为答案。

对于一个状态 $(i,j)$，可以从 $(i-1, j)$（不选）和 $(i-1, j-1)$（选）转移来。

考虑一个名称。当我想从选 $a_i$ 个变为选 $a_i+1$ 个时，概率变化为 ${p_i \dbinom{k_i}{a_i}}{\dbinom{k_i}{a_i+1}}^{-1} = \dfrac{p_i(a_i+1)}{k_i-a_i}$，$p_i$ 是原先的概率。

最后别忘了除以情况数 $\dbinom{r-l+1}{n-l+1}$。


```cpp
#include <bits/extc++.h>
#define UP(i,s,e) for(auto i=s; i<e; ++i)
#define IT(i,s,e) for(auto i=s; i!=e; ++i)
#define pbds __gnu_pbds
using std::cin; using std::cout;
namespace m{ // }{{{
template<typename T> using Tree = pbds::tree<T, pbds::null_type, std::less<>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;
constexpr int N = 1e3, M = 1e3; int in, im; Tree<std::pair<int, int>> gift_rk;
std::vector<int> gifts[M];
int choose[M];
double dp[N+10][N+10];
double inv_binom(int x, int y){
    double ans = 1;
    UP(i, 0, y){
        ans *= (y-i)*1.0/(x-i);
    }
    return ans;
}
void work(){
    cin >> in >> im;
    UP(i, 0, im){
        int ik; cin >> ik;
        UP(j, 0, ik){
            int val; cin >> val;
            gift_rk.insert({-val, i});
            gifts[i].push_back(val);
        }
    }
    auto beg = gift_rk.lower_bound({gift_rk.find_by_order(in)->first, -1});
    auto end = gift_rk.lower_bound({gift_rk.find_by_order(in)->first, 114514});
    int len = std::distance(beg, end);
    IT(i, gift_rk.begin(), beg){
        choose[i->second]++;
        in--;
    }
    double &ans = dp[0][0]; ans = 1;
    UP(i, 0, im){
        ans *= inv_binom(gifts[i].size(), choose[i]);
    }
    auto it = beg;
    UP(i, 1, len+1){
        UP(j, 0, in+1){
            dp[i][j] = dp[i-1][j];
            if(j>0){
                dp[i][j] += dp[i-1][j-1] 
                * (choose[it->second]+1) 
                / (gifts[it->second].size() - choose[it->second]);
            }
        }
        it++;
    }
    printf("%.10lf", dp[len][in] * inv_binom(len, in));
}
} // {}}}
int main(){m::work(); return 0;}
```


---

