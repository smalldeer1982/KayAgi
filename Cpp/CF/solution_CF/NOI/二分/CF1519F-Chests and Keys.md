# Chests and Keys

## 题目描述

Alice and Bob play a game. Alice has got $ n $ treasure chests (the $ i $ -th of which contains $ a_i $ coins) and $ m $ keys (the $ j $ -th of which she can sell Bob for $ b_j $ coins).

Firstly, Alice puts some locks on the chests. There are $ m $ types of locks, the locks of the $ j $ -th type can only be opened with the $ j $ -th key. To put a lock of type $ j $ on the $ i $ -th chest, Alice has to pay $ c_{i,j} $ dollars. Alice can put any number of different types of locks on each chest (possibly, zero).

Then, Bob buys some of the keys from Alice (possibly none, possibly all of them) and opens each chest he can (he can open a chest if he has the keys for all of the locks on this chest). Bob's profit is the difference between the total number of coins in the opened chests and the total number of coins he spends buying keys from Alice. If Bob's profit is strictly positive (greater than zero), he wins the game. Otherwise, Alice wins the game.

Alice wants to put some locks on some chests so no matter which keys Bob buys, she always wins (Bob cannot get positive profit). Of course, she wants to spend the minimum possible number of dollars on buying the locks. Help her to determine whether she can win the game at all, and if she can, how many dollars she has to spend on the locks.

## 说明/提示

In the first example, Alice should put locks of types $ 1 $ and $ 3 $ on the first chest, and locks of type $ 2 $ and $ 3 $ on the second chest.

In the second example, Alice should put locks of types $ 1 $ and $ 2 $ on the first chest, and a lock of type $ 3 $ on the second chest.

## 样例 #1

### 输入

```
2 3
3 3
1 1 4
10 20 100
20 15 80```

### 输出

```
205```

## 样例 #2

### 输入

```
2 3
3 3
2 1 4
10 20 100
20 15 80```

### 输出

```
110```

## 样例 #3

### 输入

```
2 3
3 4
1 1 4
10 20 100
20 15 80```

### 输出

```
-1```

# 题解

## 作者：myyes (赞：71)

## [CF1519F](https://www.luogu.com.cn/problem/CF1519F) 胸和钥匙

cf edu 的题，果然是相当的规范！我很喜欢哈！好题难得！大家一定要珍惜哈！

还是一个钥匙-锁模型哈！题目就是说有一些胸和一些钥匙，你要花钱给每个胸上上几把锁锁起，让另一个师傅来开锁。另一个师傅买钥匙是要花点钱哈！买到了钥匙就能随便开相应的锁。把胸上所有锁都开开以后他可以拿到胸里头的钱哈。那就问你要怎么花最少的钱上锁才能让这个师傅挣不到钱喃？

我们先来看一下这个师傅是啷们做起得。我们把钥匙和胸连出来一个二分图咩！他要用左边的钥匙去开右边的锁，我们要让他赚不到钱，就是找不出来一个找钥匙的方案让它在胸里面挣到的钱减去钥匙的钱超过零。这个是不是有点像我们滴这个洞洞（Hall）定理咩？你看哈，这个钱的问题有点恼火，那我把这个图拗一下，每个点上是好多钱我就给他拆出来几个点，左右都是这样的哈，该连的边还是都给他连起！那我们可以发现哈，这个挣不到钱的条件就相当于右边找得到一个完美匹配了得咩。没学过洞洞定理和二分图匹配的同学可以下来找我给你讲一下咩！其实二分图匹配还是很简单滴哈，就是一个坐板凳的问题得咩。

那我们啷们算答案喃？我们枚举当前的胸上匹配了左边哪些点，花费就是要加那些至少用了一次的那些哈。那到这里我们发现就这里就是一个坐板凳滴问题了得咩！坐板凳的话我们首先就是要搞清楚哪边是人哪边是板凳哈。我们的目标是让胸都能匹配到起一个钥匙，那么就把胸当人，钥匙就是板凳，搜到右边的某个胸的时候，就去安排它去坐哪些板凳。我们写搜索就是要先写个能跑滴，再写个能过滴哈。你发现你的代码时间成本比较高，出题人糙了个数据把你嘿嗑到起了，那就需要剪枝了哈。那这个题我们需要啷们剪枝喃？首先我们可以剪去不用的状态哈，也就是说其实我们只用关心每个钥匙用了好多个，只把这个个数记下来就可以了！然后我们就可以设计一个记忆化了得咩！我们把板凳编码成一个数，然后记录到一个数组后头，这下是不是就可以重复利用答案了咩！编码解码也是搜索中很重要的技巧哈！然后还有一个剪枝是记录一下每个胸拆出来的点里头还剩到起好多个点没有匹配哈，每次匹配的时候都不能超过这个界，那么我们就在搜索的过程中就能保证每个胸没用多了哈。另外一个剪枝是如果我们搜到一个本来就是无解的状态，我们就直接跳过不搜了就可以了得咩。像这样子剪了枝过后，你就可以发现我们的程序跑得风快哈，一哈就直接过了哈！

代码放到这里了咩！大家自己咩一咩咩！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[8],b[8],c[8][8],s[8],f[8][66666];
 void sit(int u,int t,int seat,int g,int x,int y)
  {if(u>m){
  	if(t==a[x]){f[x][seat]=min(f[x][seat],f[x-1][y]+g);
 }
 return;}
 if(f[x-1][y]!=0x3f3f3f3f)
{
  for(int i=0;i<=100;i++)
  {if(t+i>a[x])break;
 if(i+y/s[u-1]%(b[u]+1)>b[u])
  {break ;}
  int q;
   if(i)q=c[x][u];
 else q=0;
 sit(u+1,t+i,seat+i*s[u-1],g+q,x,y);
}}
  }
int main()
 {
  scanf("%d%d",&n,&m);
 for(int i=1;i<=n;i++)scanf("%d",&a[i]);
 for(int i=1;i<=m;i++) scanf("%d",&b[i]);
  for(int i=1;i<=n;i++)
  {for(int j=1;j<=m;j++)scanf("%d",&c[i][j]);
  }
 s[0]=1;
 for(int i=1;i<7;i++)s[i]=s[i-1]*(b[i]+1);
  memset(f,0x3f,sizeof f);
f[0][0]=0;
 for(int i=1;i<=n;i++)
for(int j=0;j<s[m];j++)
  {
 sit(1,0,j,0,i,j);
   }
int an=0x3f3f3f3f;
 for(int i=0;i<s[m];i++)an=min(an,f[n][i]);
   if(an==0x3f3f3f3f)
 {cout<<"-1";}
 else{cout<<an;}
  return 0;
  }
```

---

## 作者：Acetyl (赞：30)

## 题意

有 $n$ 个宝箱，$m$ 种钥匙，第 $i$ 个宝箱中有 $a_i$ 金币，获取第 $j$ 个钥匙需要 $b_j$  金币，第 $j$ 个钥匙能开第 $j$ 种锁。一个宝箱上可以有多道锁，打开这个宝箱需要拥有每一道锁对应的钥匙。现在另一个人需要给这些宝箱上锁，给第 $i$ 个宝箱上第 $j$ 种锁需要 $c_{i,j}$ 块钱，问至少需要用多少块钱给宝箱上锁，才能让第一个人无论怎么操作花费的金币数量都大于等于从宝箱中获得的金币数量。数据范围 $n,m≤6$，$a_i, b_i≤4$。

## 思路

首先，形式化描述，我们需要以下条件成立：设 $L_x$  为第 $x$ 个宝箱上所有的锁的集合，则对于每个宝箱集合 $S$，都要满足：

$$\sum_{i\in S}a_i\le \sum_{j\in (\bigcup_{i\in S}L_i )}b_j$$

这个式子的形式长得很像[霍尔定理](https://oi-wiki.org/graph/graph-matching/graph-match/#_4)，所以考虑将原问题转化为二分图匹配的问题。

对于每个宝箱 $i$，将这个宝箱拆成 $a_i$ 个点，同时，对于每个锁，将这个锁拆成 $b_i$ 个点，如果宝箱 $i$ 上有锁 $j$，则将宝箱 $i$ 拆出的所有点连一条边到锁 $j$ 拆出的所有点，得到一个二分图，其中宝箱拆成的点在二分图的左部，则要求这个图的左部存在完美匹配（即左部每个点都能和右部的一个点匹配，且匹配点互不相同），下面只需要构造出这个完美匹配即可。

考虑 dp：设 $f(i,mask)$ 表示考虑到第 $i$ 个宝箱拆成的点，右部每个锁拆成的点中还没被匹配的个数（按照五进制压缩成 $mask$），最少需要花费的钱是多少。转移的时候，枚举当前宝箱对应的每一个点都匹配上了哪个锁拆成的点，如果匹配上了至少一个锁 $j$ 拆成的点，则花费的钱需要加上 $c_{i,j}$ 。最后，取 $f(n, *)$ 的最小值即为答案。

时间复杂度 $\mathcal O(n⋅5^{2n})$，常数非常小，可以通过。

## 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, a) for (int i = 0; i < (a); ++i)
#define cont(i, a) for (int i = 1; i <= (a); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c) for (int i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define parse(it, x) for (auto &it : (x))
#define pub push_back
#define pob pop_back
#define emb emplace_back
#define mak make_pair
#define mkt make_tuple
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
 
const int maxk = 20005;
int n, m;
int a[7], b[7];
int c[7][7];
int dp[7][maxk];
int mii[7];
 
vector<int> inline decode(int x) {
    vector<int> res;
    loop(i, m) res.pub(x % 5), x /= 5;
    return res;
}
 
int inline encode(const vector<int> &x) {
    int res = 0;
    range(i, m - 1, 0, -1) res = res * 5 + x[i];
    return res;
}
 
void inline dfs(int i, vector<int> arr, int val, int now, int cst, int rem) {
    if (now == m) {
        if (rem) return;
        int id = encode(arr);
        dp[i + 1][id] = min(dp[i + 1][id], val + cst);
        return;
    }
    dfs(i, arr, val, now + 1, cst, rem);
    loop(j, min(arr[now], rem) + 1) {
        arr[now] -= j;
        dfs(i, arr, val, now + 1, cst + c[i][now], rem - j);
        arr[now] += j;
    }
}
 
int main() {
    scanf("%d%d", &n, &m);
    loop(i, n) scanf("%d", a + i);
    loop(i, m) scanf("%d", b + i);
    loop(i, n) loop(j, m) scanf("%d", c[i] + j);
    mii[0] = 1;
    cont(i, m) mii[i] = 5 * mii[i - 1];
    int ini = encode(vector<int>(b, b + m));
    memset(dp, Inf, sizeof(dp));
    dp[0][ini] = 0;
    loop(i, n) loop(j, mii[m]) {
        if (dp[i][j] >= Inf) continue;
        vector<int> arr = decode(j);
        dfs(i, arr, dp[i][j], 0, 0, a[i]);
    }
    int ans = *min_element(dp[n], dp[n] + maxk);
    printf("%d\n", ans == Inf ? -1 : ans);
    return 0;
}
```

*本题解写于 OneNote，手动转换为 Markdown，如有格式问题请立即指出，谢谢。*


---

## 作者：tzc_wk (赞：10)

[Codeforces 题目传送门](https://codeforces.com/contest/1519/problem/F) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1519F)

难度终于出来了……又独立切掉一道 *3200，凯信（所以我已经独立切掉三道 *3200 了？）

首先考虑我们已经知道了每个宝箱上有哪些锁，怎样求 Bob 的最大利益，这显然就是一个最大权闭合子图的模板，我们将箱子看作左部点，钥匙看作右部点，对于每个箱子 $i$ 我们连一条 $S$ 到该箱子表示的点，容量为 $a_i$ 的边，对于每个钥匙 $j$ 我们连一条该钥匙所表示的点到 $T$，容量为 $b_i$ 的边，最后对于每个箱子 $i$ 上挂有的锁 $j$ 连一条箱子 $i$ 表示的点到钥匙 $j$ 表示的点，容量为 $\infty$ 的边，根据最小割那套理论最大利益就是 $\sum a_i$ 减去建出图来的最小割即最大流即可。我们希望最大利益 $\le 0$，故最大流需 $\ge\sum a_i$，而显然与源点相连的点的边的总流量都只有 $\sum a_i$，故所有与源点相连的边必须满流。

因此题目转化为，最少需要花费多少的代价在左部点与右部点间连边，使得得到的图跑完最大流后所有与源点相连的边都满流，直接用贪心之类的方法显然是不可行的，不过注意到此题数据范围出乎意料地小——$a_i\le 4,n\le 6$，也就是说所有与源点相连的边的流量总共最多只有 $(4+1)^6=15625$ 种可能，我们考虑以此为状态设计 $dp$，我们记 $dp_{i,j}$ 表示已经连好了前 $i$ 个右部点相关的边，当前所有与源点相连的边的流量的状态为 $j$ 的最小花费（注：在下文中，为了表述方便，我们用一个 $n$ 元组 $(x_1,x_2,\cdots,x_n)$ 表示这样的状态 $j$，$x_i$ 表示源点与 $i$ 相连的边的流量），考虑转移，我们考虑 $i+1$ 到汇点的 $b_{i+1}$ 的流量的来源，假设 $j\to i+1$ 的边流了 $y_j$ 的流量，那么需要的代价 $C=\sum\limits_{j=1}^n[y_j>0]\times c_{j,i+1}$，总转移方程为 $dp_{i+1,(x_1+y_1,x_2+y_2,\cdots,x_n+y_n)}\leftarrow dp_{i,(x_1,x_2,\cdots,x_n)}+C$，至于这个 $y_j$ 怎么处理，再套个背包类的 $dp$ 当然是没问题的，不过由于 $b_i$ 数据范围也很小，因此可以直接无脑暴搜 $y_i$，显然 $y_i$ 的个数是与划分数有关的，根据隔板原理暴搜次数最多是 $\dbinom{9}{4}+\dbinom{8}{3}+\dbinom{7}{2}+\dbinom{6}{1}+\dbinom{5}{0}=210$，是不会出问题的。最后输出 $dp_{n,(a_1,a_2,\cdots,a_n)}$ 即可

最后是这个状态怎么处理，我的做法是将 $(x_1,x_2,\cdots,x_n)$ 进行八进制压缩压成一个 $2^{18}$ 以内的数再重新编号，如果用 `vector` 保存复杂度会多一个 $n$，~~不知道能不能跑得过（大雾~~

总复杂度 $15625\times 6^2\times 210$，不过似乎跑得飞快？最慢的一个点才跑了 31ms。

```cpp
const int MAXN=6;
const int MAXP=15625;
int n,m,a[MAXN+3],b[MAXN+3],c[MAXN+3][MAXN+3];
ll dp[MAXN+3][MAXP+5];
int rid[MAXP+5],id[1<<18];
int idnum=0;
void dfs(int x,int cur){
	if(x==n+1){rid[++idnum]=cur;id[cur]=idnum;return;}
	for(int i=0;i<=a[x];i++) dfs(x+1,cur+(i<<(3*(x-1))));
}
void dfs2(int x,int t,int msk,int lft,ll val){
	if(!lft||x==n+1){chkmin(dp[t][id[msk]],val);return;}
	for(int i=0;i<=min(a[x]-(msk>>(3*(x-1))&7),lft);i++){
		dfs2(x+1,t,msk+(i<<(3*(x-1))),lft-i,val+(i>0)*c[x][t]);
	}
}
int main(){
	scanf("%d%d",&n,&m);int sa=0,sb=0;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sa+=a[i];
	for(int i=1;i<=m;i++) scanf("%d",&b[i]),sb+=b[i];
	if(sa>sb) return puts("-1"),0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&c[i][j]);
	dfs(1,0);memset(dp,63,sizeof(dp));dp[0][id[0]]=0;
	for(int i=0;i<m;i++){
		vector<int> pos;
		for(int l=1;l<=idnum;l++){
			if(dp[i][l]>=0x3f3f3f3f3f3f3f3fll) continue;
			dfs2(1,i+1,rid[l],b[i+1],dp[i][l]);
		}
	} int lst=0;for(int i=1;i<=n;i++) lst|=(a[i]<<(3*(i-1)));
	if(dp[m][id[lst]]<0x3f3f3f3f3f3f3f3fll) printf("%lld\n",dp[m][id[lst]]);
	else puts("-1");
	return 0;
}
```



---

## 作者：lzqy_ (赞：4)

重铸状态数 DP 荣光！！！！！！

这个数据范围一看就不是 poly 做法，考虑状态数 DP。

用意念感知一下，这玩意儿的状态数不会收敛到一个能接受的复杂度内，但似乎也没爆太多。

一个最基础的想法是记录下 $(2^{m}-1)$ 种上锁状态里，每种状态 $S$ 和它所有子集所支配的宝箱价值之和。只要任意一个状态的价值不超过其代价就可以丢掉。

这样显然是过不去的，考虑优化状态。

- 答案的一个上界是每个宝箱都用 $m$ 把钥匙锁。容易发现这个上界同时也适用于所有前缀状态。因此，可以边转移边更新目前最优答案，丢掉已经劣于最优答案的状态。

- 转移前用限制步数的爆搜迭代最优答案。这个爆搜是有启发性的，对 $b$ 多 random 几次会比提高限制步数来的有用。

然后就过了。我认为在这个数据范围下已经卡不掉我的做法了！

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=10;
const int maxs=1<<6;
const int maxm=500010;
const int mod=998244353;
const int inf=1<<30;
const int p=1e7+7;
const int base=37;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
il void chkmin(int &x,int y){if(y<x)x=y;}
int c[maxn][maxn];
int cst[maxn][maxs],tot[maxs];
int a[maxn],b[maxn];
int n,m,state,lim=inf;
struct info{
	int v[maxs];
	int val(int sum=0){
		for(int s=0;s<state;s++)
			sum=(1ll*sum*base+v[s])%mod;
		return sum%p;
	}
	bool operator ==(info a)const{
		for(int s=0;s<state;s++)
			if(v[s]!=a.v[s]) return 0;
		return 1;
	}
};
struct edge{
	info v;
	int to;
}e[2][maxm];
int head[2][p],ecnt[2];
int suf[maxn];
int f[2][maxm];
int nw[maxs];
int id[maxn];
int B[maxn],C[maxn][maxn];
bool cmp1(int x,int y){
	return b[x]<b[y];
}
bool cmp2(int x,int y){
	return b[x]>b[y];
}
bool cmp3(int x,int y){
	return x<y;
}
int Find(int t,info x){
	int v=x.val();
	for(int i=head[t][v];i;i=e[t][i].to)
		if(e[t][i].v==x) return i;
	e[t][++ecnt[t]].v=x,e[t][ecnt[t]].to=head[t][v],head[t][v]=ecnt[t];
	return ecnt[t];
}
int step;
void dfs(int x,int w=0){
	step++;
	if(step>1e5)
		return ;
	if(x==n+1){
		lim=min(lim,w);
		return ;
	}
	for(int s=1;s<state&&step<1e5;s++){
		bool fl=1;
		for(int t=s;t<state;t=(t+1)|s){
			nw[t]+=a[x];
			if(nw[t]>tot[t]) fl=0;
		}
		if(fl) dfs(x+1,w+cst[x][s]);
		for(int t=s;t<state;t=(t+1)|s)
			nw[t]-=a[x];
	}
	return ;
}
void init(){
	for(int i=1;i<=m;i++) B[id[i]]=b[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			C[i][id[j]]=c[i][j];
	for(int i=1;i<=m;i++) b[i]=B[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			c[i][j]=C[i][j];
	for(int s=0;s<state;s++){
		tot[s]=0;
		for(int i=1;i<=m;i++)
			if(s&(1<<i-1)) tot[s]+=b[i];	
	}
	for(int i=1;i<=n;i++)
		for(int s=0;s<state;s++){
			cst[i][s]=0;
			for(int j=1;j<=m;j++)
				if(s&(1<<j-1))
					cst[i][s]+=c[i][j];
		}
	step=0,dfs(1);
}
int main(){
	n=read(),m=read();
	state=1<<m;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) b[i]=read();
	for(int i=1;i<=m;i++) id[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			c[i][j]=read();
	sort(id+1,id+1+m,cmp1),init();
	sort(id+1,id+1+m,cmp2),init();
	for(int i=1;i<=10;i++)
		random_shuffle(id+1,id+1+m),init();
	sort(id+1,id+1+m,cmp3),init();
	int sum=0;
	for(int i=1;i<=n;i++) sum+=a[i];
	if(sum>tot[state-1]) return printf("-1\n"),0;
//	printf("lim=%d\n",lim);
	for(int i=n;i;i--) 
		suf[i]=suf[i+1]+cst[i][state-1];
	info t,M;
	memset(t.v,0,sizeof(t.v));
	memset(f,127,sizeof(f));
	f[0][Find(0,t)]=0;
	for(int i=1;i<=n;i++){
		int i1=i-1&1,i2=i&1;
//		printf("!!!%d\n",ecnt[i1]);
		for(int j=1;j<=ecnt[i1];j++){
			t=e[i1][j].v;
			for(int s=1;s<state;s++){
				M=t; bool fl=1;
				for(int t=s;t<state;t=(t+1)|s){
					M.v[t]+=a[i];
					if(M.v[t]>tot[t]) fl=0;
				}
				if(fl&&f[i1][j]+cst[i][s]<lim) 
					chkmin(f[i2][Find(i2,M)],f[i1][j]+cst[i][s]);
				if(fl)lim=min(lim,f[i1][j]+cst[i][s]+suf[i+1]);
			}
		}
		for(int j=1;j<=ecnt[i1];j++)
			f[i1][j]=inf,head[i1][e[i1][j].v.val()]=0;
		ecnt[i1]=0;
	}

	int ans=lim;
	for(int j=1;j<=ecnt[n&1];j++)
		chkmin(ans,f[n&1][j]);
	if(ans==inf) ans=-1;
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：Richard_Whr (赞：3)

考虑刻画 Alice 能赢的局面：

设每一个箱子 $i$ Alice 配的锁的集合为 $N(i)$，则 Bob 的最大收益是：

$$\max_{s}\{\sum\limits_{i \in s}a_i - \sum\limits_{j \in \cup_{i\in s} N(i)}b_j\}$$

能赢当且仅当这个最大收益 $\le 0$。

很像最大权闭合子图的式子，考虑从网络流的角度思考这件事。

对于 Bob 来说可以建立最小割模型来获得最优解。

具体的是源点连向箱子，流量为 $a$；

箱子连向配的锁，流量为 $\infty$；

锁连汇点，流量为 $b$；

然后 Alice 的目标就是让最小割为 $\sum a_i$，也就是全部割的是源点出发的边，进一步，所有源点连箱子的边都满流。

有了这个关键性质，局面变得明朗了许多。

只需要满足满流的基础上最小化 $\sum c$ 即可。

一个一个的考虑每个箱子，这个流量值域非常小，考虑直接把所有锁的流量状态压下来，这个有 $(4+1)^6=15625$ 种，然后对每个箱子看成背包，每个锁看成有数量限制的物品，如果选了至少一个那就要算上贡献。这部分做背包即可，单次背包复杂度为 $a_i \times m \times \sum b_i$，总体复杂度是 $O(n \times m \times V^2\times 5^6) \approx 1.5 \times 10^7$，可以接受。

状压这个流量集合其实就是编码解码高维矩形，具体实现可以看代码，自认为比较简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7,M=5,S=1.6e4,Inf=1e9;
int f[N+1][N][M][S];
int B[N];
int n,m;
int a[N],b[N];
int c[N][N];
int cnt[N];

void Chkmin(int &a,int b)
{
	if(a>b) a=b;
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	B[0]=1;
	for(int i=1;i<=m;i++) cin>>b[i],B[i]=B[i-1]*(b[i]+1);
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
		}
	}
	
	memset(f,0x3f,sizeof f);
	f[1][0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int s=0;s<B[m];s++)
		{
			for(int j=1;j<=m;j++) cnt[j]=(s%B[j])/B[j-1];
			for(int j=1;j<=m;j++)
			{
				for(int k=0;k<=a[i];k++)
				{
					for(int t=0;t+cnt[j]<=b[j] && t+k<=a[i];t++)//流量 
					{
						int ns=s+t*B[j-1],cost=(t>0)*c[i][j];
						Chkmin(f[i][j][k+t][ns],f[i][j-1][k][s]+cost);
					}
				}
			} 
		}
		for(int s=0;s<B[m];s++)
		{
			f[i+1][0][0][s]=f[i][m][a[i]][s];
		}
	}
	int res=Inf;
	for(int s=0;s<B[m];s++) res=min(res,f[n+1][0][0][s]);
	
	if(res>=Inf) res=-1;
	cout<<res<<"\n";
	
	return 0;
}
```

---

## 作者：清尘 (赞：3)

[My Blog](https://www.cnblogs.com/whx666/p/CF1519F.html)

前半部分和另一篇题解基本相同

首先用式子来表示题意，即花费最小代价上锁以下条件成立：设 $L_x$ 为宝箱 $x$ 上锁的集合，则对于任意的打开的宝箱集合 $S$，都要满足：$\sum\limits_{i\in S}a_i\le\sum\limits_{j\in (\bigcup_{i\in S}L_i )}b_j$

这个东西形如[HALL定理](https://www.cnblogs.com/Yuzao/p/9185379.html)，而定理说的是点的数量关系，那么可以把 $a_i,b_j$ 都看成点的数量，也就是进行拆点，然后转化为二分图上的问题。将每个宝箱 $i$ 拆成 $a_i$ 个点作为二分图的左部点；将每个锁 $j$ 拆成 $b_j$ 个点作为右部点。若宝箱 $i$ 上有锁 $j$，则将 $i$ 拆出的所有点向锁 $j$ 拆出的所有点连边，得到一个二分图。条件就是让这个图的左部点存在完美匹配

考虑 dp：设 $f_{i,j}$ 表示处理到宝箱 $i$ 拆成的点，每个锁拆成的右部点中还没被匹配的个数（用五进制压缩成 $j$），最少需要花费的代价。转移时枚举当前宝箱对应的每个点匹配了哪个锁的点，加上这些锁的代价。$f_{n,*}$ 的最小值即为答案。

这样复杂度可以做到 $O(n·5^{2n})$，由于有 continue 跑不满已经可以快速通过了。但保险起见，我们可以进一步优化这个 dp。

设 $f_{i,j,k}$ 表示处理到宝箱 $i$，右部点剩余状态 $j$，宝箱 $i$ 还有 $k$ 个点未匹配。先枚举 $i,j,k$，转移的时候不用直接枚举右部匹配点的集合，只要遍历每个锁，再枚举从这个锁拿了几个点来转移。虽然在转移的过程中会出现“重复付钱”，但最优解显然会避开这种情况，对答案没有影响。

复杂度 $O(n·5^{n}·4·m·4)=O(16n^2·5^{n})$，但在实际测试中没啥差别，二者都飞一样快

```cpp
#include <bits/stdc++.h>
using namespace std;
void read (int &x) {
    char ch = getchar(); x = 0; while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
} const int N = 8, M = 15625;
int n, m, a[N], b[N], c[N][N], f[N][M][5];
int v[M][N], p[N] = {0, 1, 5, 25, 125, 625, 3125};
void get (int x) {
    for (int i = m, t = x; i >= 1; --i) v[x][i] = t / p[i], t %= p[i];
}
void Min (int &x, const int y) { if (y < x) x = y; }
signed main() {
    read (n), read (m);
    for (int i = 1; i <= n; ++i) read (a[i]);
    for (int i = 1; i <= m; ++i) read (b[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) read (c[i][j]);
    int mx = 0;
    for (int i = 1; i <= m; ++i) mx += p[i] * b[i];
    for (int i = 0; i <= mx; ++i) get (i);
    memset (f, 0x3f, sizeof (f)); int inf = f[0][0][0];
    f[1][mx][a[1]] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = mx; j >= 0; --j) {
            for (int k = a[i]; k >= 0; --k) {
                if (f[i][j][k] >= inf) continue;
                for (int o = 1; o <= m; ++o)
                    for (int u = 1; u <= v[j][o] && u <= k; ++u) {
                        Min (f[i][j - p[o] * u][k - u], f[i][j][k] + c[i][o]);
                    }
            }
            Min (f[i + 1][j][a[i + 1]], f[i][j][0]);
        }
    int res = inf;
    for (int i = 0; i <= mx; ++i) res = min (res, f[n + 1][i][0]);
    printf ("%d\n", res == inf ? -1 : res);
}
```







---

## 作者：小超手123 (赞：2)

### 题意：

给定 $n,m$ 表示存在 $n$ 个宝箱和 $m$ 把钥匙，第 $i$ 把钥匙需要 $b_i$ 元，第 $i$ 个宝箱内部有 $a_i$ 元。

现在进行一场游戏，Bob 是本场游戏的玩家，而 Alice 则是场景布置者，Alice 可以给每个宝箱上一些锁（第 $j$ 种锁需要第 $j$ 种钥匙打开）

如果 Bob 可以购买一些钥匙，然后打开一些宝箱，使得 Bob 的收益大于 $0$，那么 Bob 就赢得了游戏，反之 Alice 获得了胜利。

现在 Alice 打算布置宝箱上的锁，第 $i$ 个宝箱上放置第 $j$ 种锁的花费为 $c_{i,j}$，请帮助 Alice 找到一种布置锁的方案，使得花费最小，且 Alice 将取得胜利。

$n,m\le 6,a_i,b_i\le 4,c_{i,j}\le 10^7$

特别的，一个箱子上可以放置若干把锁，Bob 需打开所有锁才能获得内部的钱。

### 分析：

先考虑如果给定了所有宝箱的布置锁的方案求 Bob 所得到的最大利益。

考虑网络流，连边 $S \rightarrow i(w=a_{i}),\ i \rightarrow j(w=+\infty),\ j \rightarrow T(w=b_{j})$，其中 $i$ 表示箱子，$j$ 表示锁。那么最大利益即为 $(\sum a_{i})-Mincut$，具体证明见 [P2762 太空飞行计划问题](https://www.luogu.com.cn/problem/P2762)。

这题显然不能枚举所有所有宝箱的布置锁的方案，那怎么做呢？

如果想要 Bob 获利为 $0$，即必须让他割 $S$ 到所有箱子的边。

这题的突破口在于**网络中的最大流量应使 $S$ 到所有箱子的边达到满流**，否则最小割一定不是 $S$ 到所有箱子的边。

知道了这点就很简单了，注意到 $a_{i},b_{i} \le 4$，随便 dp 一下即可。

比如我们可以记 $f_{i,j,k,l}$ 表示考虑到第 $i$ 个箱子（该箱子残余流量为 $l$），此时所有钥匙的残余流量集合为 $j$，目前在考虑是否要走 $i \rightarrow k$ 这条边。

状态数是 $6 \times 5^6 \times 6 \times 4=2.5 \times 10^5$，不会爆空间。

需要注意的是考虑是否要走 $i \rightarrow k$ 这条边时，我们还需要枚举其流量，不能无脑全流。

时间复杂度为 $O(nmw^2 \times (w+1)^m)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 10
using namespace std;
int n, m, ans = 1e18;
int a[N], b[N], c[N][N], cnt;
vector<int>now, z, p[100005], r;
int f[8][16000][7][7];
map<vector<int>, int>num;
void dfs(int k) {
	if(k > m) {
		p[++cnt] = z;
		num[z] = cnt;
		for(int i = 1; i <= n + 1; i++)
		for(int j = 1; j <= m; j++)
		for(int l = 0; l <= 4; l++)
			f[i][cnt][j][l] = 1e18;
		return;
	}
	for(int i = 0; i <= b[k]; i++) {
		z.push_back(i);
		dfs(k + 1);
		z.pop_back();
	}
}
void upd(int &x, int y) {
	x = min(x, y);
}
signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i], now.push_back(b[i]);
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++) cin >> c[i][j];
	dfs(1);
	f[1][num[now]][1][a[1]] = 0;
	for(int i = 1; i <= n; i++) {
		for(int k = 1; k <= m; k++) {
			for(int j = 1; j <= cnt; j++) {
				for(int l = 0; l <= a[i]; l++) {
					if(k != m) {
						upd(f[i][j][k + 1][l], f[i][j][k][l]);
						int use = min(l, p[j][k - 1]);
						r = p[j];
						for(int v = 1; v <= use; v++) {
							r[k - 1] -= v;
							upd(f[i][num[r]][k + 1][l - v], f[i][j][k][l] + c[i][k]);
							r[k - 1] += v;
						}
					}
					else {
						if(l == 0) upd(f[i + 1][j][1][a[i + 1]], f[i][j][k][l]);
						else if(p[j][k - 1] >= l) {
							r = p[j];
							r[k - 1] -= l;
							upd(f[i + 1][num[r]][1][a[i + 1]], f[i][j][k][l] + c[i][k]);
						}
					}
				}
			}
		}
	}
	for(int i = 1; i <= cnt; i++) ans = min(ans, f[n + 1][i][1][0]);
	if(ans == 1e18) cout << -1;
	else cout << ans;
	return 0;
}
```

---

## 作者：lalaouye (赞：1)

这是一个初学 hall 定理的萌新写的题解，然而我一开始并没有用 hall 定理做这道题。

首先这道题显然是 hall 定理的形式，但是我注意到了所有值都很小，只有关于答案的数很大，~~自然~~想到搜索。

考虑直接爆搜，重要的是先判无解，然后考虑爆搜每条边是否要连，那么我们将边权从小到大排序搜索，然后在修改时，我们只需最多 $2^5$ 次枚举，为了优化常数我们可以在这里状压并进行一些预处理，具体可以看代码。

然后如果当前要修改的状态已经全部满足条件了，显然使用这条边是不优的，直接跳过即可。

然后再来个经典的答案剪枝，就可以飞快草过这道题了（其实本人也没想到直接能过，还以为要再多一点优化才行呢）。

代码：

````
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i (l); i <= (r); ++ i)
#define rrp(i, l, r) for (int i (r); i >= (l); -- i)
#define pii pair <int, int>
#define eb emplace_back
#define ls p << 1
#define rs ls | 1
using namespace std;
constexpr int N = 1e5 + 5, B = 71, P = 1042702009;
typedef unsigned long long ull;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + ch - 48;
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int n, m;
int a[7], b[7];
int c[6][6];
int now[1 << 7];
int pre[N];
bool ok[1 << 7], ak[6];
bool g[1 << 7][1 << 7];
class edge {
  public:
    int u, v, w;
  friend bool operator < (const edge &a, const edge &b) {
    return a.w < b.w;
  }
} e[7 * 7];
int tot, cnt;
int S, T;
int ans = 2e9;
int ct[1 << 7][7];
int h[1 << 7][7];
void dfs (int Now, int ret) {
  if (ret >= ans) return ;
  if (cnt == (1 << (m + 1)) - 1) {
    ans = ret; return ;
  }
  if (ret + e[Now].w >= ans) return ;
  if (Now > tot) return ;
  int u = e[Now].u, v = e[Now].v;
  bool flag = 0;
  rep (i, 0, (1 << m) - 1) {
    int s = h[i][u];
    bool fl = g[s][now[s]];
    flag &= g[s][now[s]];
    now[s] |= 1 << v;
    if (g[s][now[s]] && ! fl) ++ cnt;
    ++ ct[s][v];
  }
  if (! flag) dfs (Now + 1, ret + e[Now].w);
  rep (i, 0, (1 << m) - 1) {
    int s = h[i][u];
    if (! -- ct[s][v]) {
      bool fl = g[s][now[s]];
      now[s] ^= 1 << v;
      if (fl && ! g[s][now[s]]) -- cnt;
    } 
  }
  dfs (Now + 1, ret);
}
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd (), m = rd ();
  S = (1 << n) - 1, T = (1 << m) - 1;
  -- n, -- m;
  int s1 = 0, s2 = 0;
  rep (i, 0, n) a[i] = rd (), s1 += a[i];
  rep (i, 0, m) b[i] = rd (), s2 += b[i];
  if (s1 > s2) return puts ("-1") * 0; 
  swap (a, b), swap (n, m);
  swap (S, T);
  rep (s, 0, S) {
    rep (t, 0, T) {
      int sum = 0;
      rep (i, 0, n) if (s >> i & 1) sum += a[i];
      rep (j, 0, m) if (t >> j & 1) sum -= b[j];
      g[t][s] = sum >= 0;
      // cout<<s<<" "<<t<<" "<<g[t][s]<<endl;
    }
  }
  rep (i, 0, (1 << m) - 1) {
    rep (u, 0, m) {
      h[i][u] = (((i >> u) << 1 | 1) << u) | (i & ((1 << u) - 1));
    }
  }
  rep (i, 0, m) rep (j, 0, n) e[++ tot] = (edge) {i, j, rd ()};
  sort (e + 1, e + tot + 1);
  dfs (1, 0);
  if (ans == 2e9) return puts ("-1") * 0;
  cout << ans;
}
````

还没完呢，毕竟我是来学 hall 定理的。我开始没有想到怎么 dp，因为我以为 dp 时还要用到 hall 定理的性质，然而这题并非如此，这题中的 hall 定理只是将题目转化为了二分图最大匹配问题，而通过 $a_i,b_i$ 很小可以注意到使用状压 dp，直接设 $f_{i,S}$ 表示左部已经匹配到了 $i$，右部每个钥匙还剩多少点未匹配即可进行转移，写个记搜即可~

---

## 作者：Phartial (赞：1)

好题难得！大家一定要珍惜哈！

假设 Alice 已经确定了每个箱子上哪些锁，那么 Bob 的决策就可以描述为：他想要打开集合 $T$ 里的箱子，而这需要购买 $\bigcup_{x\in T}N(x)$ 中的所有钥匙（其中 $N(x)$ 为第 $x$ 个箱子上的锁的集合），那么 Alice 获胜当且仅当对任意 $T$，都有：

$$
\sum_{i\in T}a_i\le\sum_{i\in\bigcup_{x\in T}N(x)}b_i
$$

这和 Hall 定理的形式很像，考虑到值域很小，我们可以把代价拆成点，并用二分图进行刻画。具体的，将一个价值为 $a_i$ 的箱子拆成 $a_i$ 个左部点，将一个费用为 $b_i$ 的锁拆成 $b_i$ 个右部点，如果第 $i$ 个箱子上了第 $j$ 种锁，就将第 $i$ 个箱子对应的 $a_i$ 个左部点和第 $j$ 个箱子对应的 $b_j$ 个右部点两两连边。那么 Alice 获胜当且仅当对任意 $T\subseteq L$（$L$ 是左部点集），都有 $|T|\le|\bigcup_{x\in T}N(x)|$。容易证明这和上面的判定是等价的。

于是由 Hall 定理，这等价于这张二分图的左部点存在完美匹配。

考虑 dp。设 $f(i,s)$ 表示现在已经匹配上了前 $i$ 个箱子对应的所有左部点，且第 $j$ 种锁对应的右部点已经被用了 $s_j$ 个时的最小代价。转移时，枚举第 $i+1$ 个箱子的 $a_{i+1}$ 个左部点分别匹配到了哪种锁，由此可以计算出这个箱子上了哪些锁，从而计算出代价。更新 $s$ 并转移到新状态即可。最终答案为 $\min\limits_sf(n,s)$。

$s$ 可以使用 $v+1$ 进制压缩存储。空间复杂度为 $\mathcal{O}(nv^m)$，时间复杂度为 $\mathcal{O}(nv^m{v+m\choose m})$。

```cpp
#include <iostream>

using namespace std;

const int kN = 6, kB = 5, kV = 15625;
const int kP[kN] = {1, 5, 25, 125, 625, 3125};

int n, m, a[kN], b[kN], c[kN][kN];
int f[kN][kV];
bool v[kN][kV];

int F(int, int);
int D(int x, int s, int i, int k) {  // 正在匹配第 x 个箱子，锁的使用情况是 s，已经决策了前 i 把锁，还有 k 个左部点要匹配
  if (i == m) {
    return k ? 1e9 : F(x + 1, s);
  }
  int _c = s / kP[i] % kB, f = D(x, s, i + 1, k);
  for (int j = 1; j <= min(k, b[i] - _c); ++j) {
    f = min(f, D(x, s + j * kP[i], i + 1, k - j) + c[x][i]);
  }
  return f;
}
int F(int x, int s) {
  if (x == n) {
    return 0;
  }
  if (v[x][s]) {
    return f[x][s];
  }
  v[x][s] = 1;
  return f[x][s] = D(x, s, 0, a[x]);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> c[i][j];
    }
  }
  int v = F(0, 0);
  cout << (v == 1e9 ? -1 : v);
  return 0;
}
```

---

## 作者：IdnadRev (赞：1)

咋能 3200 的。

写出判定的式子：

$$\forall_S\sum_{x\in S}a_x\leqslant \sum_{x\in N(S)}b_x$$

$N(S)$ 即 $S$ 集合每个点邻域的并集，这是 Hall 定理的形式，我们把点权拆点即可变为 Hall 定理（假设一个左部点拆成了 $a_i$ 个点，那么这些点选择一部分一定不优于全选，因此拆点正确）。

于是我们反向使用 Hall 定理将限制转化成左部的完美匹配，使用状压 dp 即可，只需记录左部考虑到哪里了，右边每个原始点拆的点用了多少个，每个左部点的转移再用 dp 从前往后考虑每个右部点即可。

时间复杂度 $O(nmk^2k^n)$，其中 $k=\max \max(a_i,b_i)=4$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10,maxs=16005,maxk=5,inf=0x3f3f3f3f;
int n,m,ans,S;
int a[maxn],b[maxn],c[maxn][maxn],mul[7]= {0,1,5,25,125,625,3125},f[maxn][maxk][maxs];
inline void chkmin(int &x,int y) {
	if(x>y)
		x=y;
}
inline int get(int s,int k) {
	return s/mul[k]%5;
}
int main() {
	scanf("%d%d",&n,&m),ans=2e9;
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	for(int i=1; i<=m; i++)
		scanf("%d",&b[i]),S+=mul[i]*b[i];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			scanf("%d",&c[i][j]);
	memset(f,0x3f,sizeof(f));
	f[1][a[1]][0]=0;
	for(int i=1; i<=n; i++) {
		for(int j=a[i]; j>=0; j--)
			for(int s=S; s>=0; s--)
				if(f[i][j][s]!=inf)
					for(int u=1; u<=m; u++)
						for(int v=1; v<=j&&v+get(s,u)<=b[u]; v++)
							chkmin(f[i][j-v][s+v*mul[u]],f[i][j][s]+c[i][u]);
		for(int j=0; j<=S; j++) {
			if(i<n)
				chkmin(f[i+1][a[i+1]][j],f[i][0][j]);
			else chkmin(ans,f[i][0][j]);
		}
	}
	if(ans>=inf)
		puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```

---

## 作者：OtterZ (赞：0)

# 题意
给定锁的价格，箱子里的钱，以及给箱子上锁的成本，问至少要多少成本能使用钥匙开箱无论如何都不会赚。  
数据范围：

$$
n,m \le 6,a_i,b_i\le 4,c_{i,j}\le 10^7
$$

# 解法
首先,有解当且仅当存在方案，使：$ \sum b_i \ge \sum a_i$

有一种~~神奇的~~想法，就是让箱子里的每块钱和买钥匙的每块钱一一匹配，下证：  

对于将至少一个箱子里的金币匹配到一个钥匙的一个金币，我们相当于将箱子上对应的锁，当要打开的每个箱子的每个金币与钥匙的金币匹配时，解锁钥匙用的金币至少的总价格最少为箱子的价格，因为每个钥匙的金币都只能匹配一个箱子的金币。

根据这个想法，我们用个记忆化搜索，就可以在 $15\text{ ms}$ 内卡过。

# 记忆化搜索怎么做
我们的可以以每个钥匙匹配的金币数作状态压缩，因为根据数据范围，每个钥匙对应钱数不多于 $4$ 个，可以用 $5$ 进制存储，另外，钥匙至多只有 $6$ 个，状压后状态对应的五进制数不大于 $5 ^ 6 = 15625$。

对于开始匹配第 $i$ 个箱子，我们每个状态接下来的匹配不受状态数之外的过去匹配方式影响，故而可以记忆化。

对于每个箱子的匹配，枚举所有状态，即有序枚举每个钥匙有多少钱匹配到箱子对应的钱，只需保证方式合法即可。

# 注意事项

~~搜索的细节巨少~~

# 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,a[9],b[9],sma,smb;
int c[9][9];
int mem[9][15625];//记忆化
int u[9];
int srh2(int x,int o,int u);
int srh(int x){
	int bt = 1,s = 0;
	for(int i = 1; i <= m; i ++){
		s += bt * u[i];
		bt *= 5;
	}
	if(x == n + 1){
		return mem[x][s] = 0; 
	}
	if(mem[x][s] != 0x3f3f3f3f)
		return mem[x][s];
	return mem[x][s] = srh2(x,1,a[x]);
}
int srh2(int x,int o,int up){
	//printf("%d %d %d\n",x,o,up);
	if(up == 0)
		return srh(x + 1);
	if(o == m + 1 && up != 0){
		return 0x3f3f3f3f;
	}
	int ans = 0x3f3f3f3f;
	for(int i = o; i <= m; i ++){
		for(int j = 1; j <= b[i] - u[i] && j <= up; j ++){
			u[i] += j;
			ans = min(ans,srh2(x,i + 1,up - j) + c[x][i]);
			u[i] -= j; 
		}
	}
	ans = min(ans,srh2(x,m + 1,up));
	return ans;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&a[i]),sma += a[i];
	int o = 1,als = 0;
	for(int j = 1; j <= m; j ++){
		scanf("%d",&b[j]);
		als += b[j] * o;
		o *= 5;
		smb += b[j];
	}
	if(smb < sma){
		printf("-1\n");
		return 0;
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++)
			scanf("%d",&c[i][j]);
	}
	memset(mem,0x3f3f3f3f,sizeof(mem));
	mem[n + 1][als] = 0;
	printf("%d\n",srh(1));
	return 0;
}
```


---

## 作者：Gordon_Song (赞：0)

条件的形式化柿子样子长得很像 Hall 定理，因此建出二分图，左部点为 $a_i$ 个 $i ( 1 \leq i \leq n ) $，右部点为 $b_j$ 个 $j (1 \leq j \leq m) $。

于是问题转化为让现在建出的二分图左部存在完美匹配。

观察到数据范围异常地小，因此考虑状压 dp，存储第 $i$ 个锁拆成的点还有多少个没有与左边匹配（即还可用），当前已经考虑了前 $j$ 个箱子且它们都已匹配完毕的最小花费。

转移的时候使用 dfs 暴力枚举，时间复杂度 $O(n\times 5^n)$。

[link](https://codeforces.com/contest/1519/submission/277671715)。

---

