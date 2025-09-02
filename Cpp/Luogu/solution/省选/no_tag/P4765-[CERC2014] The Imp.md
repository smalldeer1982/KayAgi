# [CERC2014] The Imp

## 题目描述

你带着一些来之不易的金币来到了 Ye Olde 魔法商店，想要购买一些妙不可言的魔术物品。商店里有 $n$ 个魔术实体，每个实体都锁在一个特殊的魔术宝箱中。第 $i$ 个宝箱（和其中的实体）的售价为 $c_i$个金币，而其中实体的价值相当于 $v_i$ 个金币。你作为曾经完整钻研了《Ye Olde 魔法目录》的顶级做题家，当然毫无疑问地记住了每个盒子和其中实体的售价和价值。

然而像你这样的凡人，只能安全地携带一件魔法实体。因此，你想要得到最宝贵的一个。你本可以直接得到它的——如果不是因为调皮而又神奇的小恶魔的话。

小恶魔可以使用魔法，从而将某一个魔术宝箱内的实体转化为毫无价值的灰尘。当然，他会在你购买一个魔术宝箱后立即对其使用该魔法，这样你就为这个宝箱付了钱而没能得到里面的实体。因此，你被迫另买一个，再买一个……

小恶魔拥的魔力最多可以用来使用 $k$ 次魔法。当然，他可以不用完这 $k$ 次魔法，而你也可以随时空手走开（尽管这是一个奇耻大辱）。但是，如果你成功地买到了到一个实体（而没有被变成灰尘），则你必须保留该实体并离开商店。

你的目标是最大化你的收益（所购实体的价值减去支付的所有费用（包括购买当前实体和之前的灰尘）），而小恶魔则希望将其最小化。如果你和小恶魔都使用最佳策略，那么你的收益将会相当于多少金币？

## 说明/提示

$1\le n\le1.5\times10^5,0\le k\le9,0\le v_i,c_i\le10^6$。

## 样例 #1

### 输入

```
1
3 1
10 5
8 1
20 12```

### 输出

```
7```

# 题解

## 作者：qvzeyang (赞：8)

首先，需要先得出一个结论，购买物品需要依照一个贪心的策略，购买的顺序需要按照 $v_i$ 升序，证明如下。   

设 $v_1\le v_2$，则依照升序的代价即 $\min(v_1-c_1,v_2-c_1-c_2)$，而如果交换两个物品，按照降序购买，代价则为 $\min(v_2-c_2,v_1-c_1-c_2)$，由于 $v_1\le v_2$，所以易得 $v_1-c_1-c_2 \le \min(v_1-c_1,v_2-c_1-c_2)$。证得，购买顺序应按照 $v_i$ 升序进行。  

之后便是 DP 的转移，可以发现，从最后一件商品向前转移更为简单，为了下标的方便，这里将 $v_i$ 降序排列从 $1$ 向 $n$ 枚举转移。  

设`dp[i][j]`，表示从 $1$ 开始选到了 $i$，一共用了 $j$ 次魔法。易得使用 0 次魔法时`dp[i][0]=max(dp[i-1][0],v[i]-c[i])`。   

进行转移，可得`dp[i][j]=max(dp[i-1][j],min(v[i]-c[i],dp[i-1][j-1]-c[i])`。  
分析这个转移方程，`dp[i-1][j]`意味着并不选 $i$ 这件物品，`min(v[i]-c[i],dp[i-1][j-1])`表示小恶魔选取的更优秀的选项，即对于购买者更小的获利，其分别表示将 $i$ 这件物品设为购买的最后一件、对购买的 $i$ 物品使用魔法。最终答案为`dp[n][k]`。代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
	#define int long long
int read(){int d=1,k=0;char c=getchar();
while(!(c>='0' and c<='9' or c=='-'))c=getchar();if(c=='-')d=-1,c=getchar();
while(c>='0' and c<='9')k=(k<<3)+(k<<1)+(c^48),c=getchar();return d*k;}
int dp[200000][10],n,k;
struct node{int value,cost;}a[1000000];
int cmp(node x,node y){return x.value>y.value;}
signed main(){
	int T=read();
	while(T--){
		n=read(),k=read();
		for(int i=1;i<=n;i++)a[i].value=read(),a[i].cost=read();
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)dp[i][0]=max(dp[i-1][0],a[i].value-a[i].cost);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++){
				dp[i][j]=max(dp[i-1][j],min(dp[i-1][j-1]-a[i].cost,a[i].value-a[i].cost));
			}
		}
		printf("%lld\n",dp[n][k]);
	} 
	return 0;
}
```

---

## 作者：shiroi (赞：4)

## 题意简述

你现在正在购买物品。现在共有 $n$ 个物品，每个物品有两个属性 $v_i,c_i$ ，分别表示物体的成本和价格。商家有 $k$ 次机会在你买完物品付完钱后立刻让你的物品消失来使你的净收入尽可能低。可以无限量购买物品，但每种最后只能拿一个。

你需要求出最多能得到多少钱。

## 解题思路

观察题目可以发现双方都保证是最优策略，可以看成已知所有的策略 $(s_1,s_2...s_{k+1})$ 。

对于买东西的最优策略$(s_1,s_2...s_{k+1})$，我们可以发现 $v_{s_i}<v_{s_{i+1}}$ 。如果交换则必定会得到更坏的结果。

因此可以考虑按 $v$ 值排序，定义 $f_{i,j}$ 表示从 $j$ 到 $n$ 中选择物品，对方最多使用i次魔法的收益。

可以推导出状态转移方程为$f_{i,j}= max(f_{i,j+1},min(v_i-c_i,-c_i+ f_{i-1,j+1}))$。最后结果即为 $f_{k,0}$。 

具体实现见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

const int MAXN = 150005;
struct Node {int v,c;} a[MAXN];
int f[MAXN][10];
int n,k;

bool operator<(Node a,Node b)
{return a.v>b.v;}

int main(int argc, char const *argv[])
{
	int T=read();
	while(T--)
	{
		n=read(); k=read();
		for(int i=1; i<=n; ++i)
			a[i].v=read(),a[i].c=read();
		sort(a+1,a+n+1);
		for(int i=1; i<=n; i++)
			f[i][0]=max(f[i-1][0],a[i].v-a[i].c);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=k; j++)
				f[i][j]=max(f[i-1][j],min(a[i].v-a[i].c,f[i-1][j-1]-a[i].c));
		printf("%d\n", f[n][k]);
	}
	return 0;
}
```

---

## 作者：zzx0102 (赞：3)

模拟赛 T3，但是 $n\le 10^5,k\le 20$ 只有 $80$ 分。A_zjzj 是这样的。

很容易想到这个题复杂度是 $O(nk)$ 的。

首先有个结论：对于所有要选的货物，$v_i$ 不严格单调递增。

考虑两个货物，价格分别是 $v_1,v_2$，$v_1<v_2$，升序的代价是 $\min(v_1-c_1,v_2-c_1-c_2)$，降序的代价是 $\min(v_1-c_1-c_2,v_2-c_2)$。

很显然 $v_1-c_1$ 和 $v_2-c_1-c_2$ 都比 $v_1-c_1-c_2$ 大，所以升序更优。

我们考虑设计 dp，令 $dp_{i,j}$ 表示前 $i$ 个货物被毁了 $j$ 个的最大利润，很显然先手可以选或不选，如果选了小恶魔可以选择毁掉或不毁掉，所以容易写出转移式。

$$
dp_{i,j}=\max(dp_{i-1,j},\min(dp_{i-1,j-1}-c_i,v_i-c_i))
$$

注意 $dp_{i,0}=v_i-c_i$，复杂度 $\mathcal{O}(nk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline
#define int long long
namespace SlowIO {
	const int SZ = (1 << 20) + 1;
	char buf[SZ], *p1 = buf, *p2 = buf;
	char buffer[SZ];
	int op1 = -1;
	const int op2 = SZ - 1;
	I char gc() {
		if(p1 != p2) return *p1++;
		return p1 == (p2 = (p1 = buf) + fread(buf, 1, SZ - 1, stdin)) ? EOF : *p1++;
	}
	I void flush() {
		fwrite(buffer, 1, op1 + 1, stdout);
		op1 = -1;
	}
	I void pc(const char &x) {
		if(op1 == op2) flush();
		buffer[++op1] = x;
	}
	I int read() {
		int x = 0, f = 1; char ch = gc();
		while(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(!x) {pc('0'); return ;}
		char s[25];
		int tot = 0;
		while(x || !tot) {
			s[tot++] = x % 10 + 48;
			x/=10;
		}
		while(tot--) pc(s[tot]);
	}
} using namespace SlowIO;
const int N = 150010;
int n, m;
int dp[N][22];
struct node {
	int A, B;
} a[N], b[N];
bool cmp(node a, node b) {
	return a.B > b.B;
}
signed main() {
	int T = read();
	while(T--) {
		n = read(), m = read();
		for(int i = 1; i <= n; i++) a[i].B = read(), a[i].A = read();
		sort(a + 1, a + 1 + n, cmp);
		for(int i = 1; i <= n; i++) {
			dp[i][0] = max(dp[i - 1][0], a[i].B - a[i].A);
			for(int j = 1; j <= m; j++) {
				dp[i][j] = max(dp[i - 1][j], min(dp[i - 1][j - 1] - a[i].A, a[i].B - a[i].A));
			}
		}
		write(dp[n][m]); pc('\n');
	}
	flush();
	return 0;
}
```

但是模拟赛题的数据被 A_zjzj 加强成了 $k\le n$，所以这个代码只有 $80$ 分。（当然你判个 $v_i=c_i$ 的情况，能有 $85$ 分）

正解是反悔贪心。

继续沿用前面的结论：对于所有要选的货物，$v_i$ 不严格单调递增。

考虑二分答案。

只要我们能够选出选出 $m+1$ 个物品，满足每个物品的售价减去前面所有物品的代价大于等于答案就行了。

然后如果物品可行就直接加，否则考虑反悔，和前面加入的最贵的弹出去。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 150010;
int n, m;
struct node {
	int A, B;
} a[N];
bool cmp(node a, node b) {
	return a.B < b.B;
}
bool chk(int mid) {
	priority_queue<int> q;
	while(!q.empty()) q.pop();
	int sum = 0, cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i].B - a[i].A - sum >= mid) {
			cnt++;
			sum += a[i].A;
			q.push(a[i].A);
		}
		else {
			if(!q.empty() && q.top() > a[i].A) {
				sum -= q.top();
				sum += a[i].A;
				q.pop(); q.push(a[i].A);
			}
		}
		if(cnt == m + 1) return 1;
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(0);
	int T; cin >> T;
	while(T--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) cin >> a[i].B >> a[i].A;
		sort(a + 1, a + 1 + n, cmp);
		int l = 1, r = 1e18, ans = 0;
		while(l <= r) {
			int mid = l + r >> 1;
			if(chk(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		cout << ans << '\n';
	}
	return 0;
} 
```

---

## 作者：弦巻こころ (赞：3)

方程不难,关键是状态如何设置

首先我们发现,我们最后选择商品的顺序一定是按照价值从小到大选择.(至于为啥我还没想明白 ()

所以我们先将物品按价值排序

设$f[i][j]$为从$i$~$n$个数中选了$j$件物品的最大价值

为什么不是$1$~$i$选$j$件而是$i$~$n$选$j$件呢.

因为如果你将状态设置为$1$~$i$的话,你并不知道该从那个$k$转移,因为每个$k$的$min$与$sum c$不同,而且你也不知道该保留那个$k$转移过来的值.

但如果我们考虑从后往前dp,也就是状态设置成$i$~$n$的情况,每个新选的数会对之前的所以值产生统一的$-ci$的贡献,因此我们只需要求一个后缀最大值,再与当前的$vi$取$min$即可.

转移方程为

$f[i][j]=min(f[i-1][j+1],q[j].v)-q[j].c;$

然后再取个后缀最大值就好了

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=151414;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
int t,n,k,kkr,f[19][N];
struct ask{int v,c;}q[N];
bool cmp(ask a,ask b){return a.v==b.v?a.c<b.c:a.v<b.v;}
int main(){
	scanf("%d",&t);while(t--){
	scanf("%d%d",&n,&k);memset(f,0x3f,sizeof(f));
	rep(i,1,n)scanf("%d%d",&q[i].v,&q[i].c);
	sort(q+1,q+n+1,cmp);kkr=0;
	rep(i,1,k+1)per(j,n-i+1,1){
		f[i][j]=min(f[i-1][j+1],q[j].v)-q[j].c;
		if(j<n-i+1)f[i][j]=max(f[i][j+1],f[i][j]);
	}rep(i,1,n-k)kkr=max(f[k+1][i],kkr);
	printf("%d\n",kkr);
}}

---

## 作者：Sad_Rex (赞：2)

**一：首先我们需要证明贪心**：

因为只能拿一个，且选了不能换。所以，明显如果我从 $v_i$中最小的开始拿明显小恶只要不用魔法，你则并不是最大化收益。所以我们要 $v_i$ 升序排列。

**二：我们要写出 DP 状态**：

我们设 $dp[i][j]$ 为前 $1$ 到 $i$ 件宝箱，小恶用了 $j$ 次魔法中最大化收益。

**三： DP 的转移**：

**若小恶不用魔法**则 $dp[i][j]=\max(dp[i-1][j],v[i]-c[i])$

明显若第 $i$ 件物品是最优的则 $dp[i][j]=v[i]-c[i]$ 

反之则 $dp[i][j]=dp[i-1][j]$ 。

**若小恶使用魔法**则 $dp[i][j]=dp[i-1][j-1]-c[i]$ ，表示上一天的最大化收益减今天的花费。

**所以**转移式为 $dp[i][j]=\max(dp[i-1][j],\min(dp[i-1][j-1]-c[i],v[i]-c[i])$

**四：边界**:

明显当 $j$ 为 $0$ 时 $dp[i][j]=\max(dp[i-1][j],v[i]-c[i])$ 。

以下是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int  long long
#define kg putchar(' ')
#define endl puts("")
inline int read(){
	int vis=1,ans=0;
	char x=getchar();
	while(x<'0'||x>'9'){
		if(x=='-')vis=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9'){
		ans=ans*10+x-'0';
		x=getchar();
	}
	return vis*ans;
}
inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
int T=read(),n,k;
const int N=2*1e5+9,K=10;
struct node{
	int v,c;
}a[N];
bool cmp(node a,node b){
	return a.v>b.v;//为了下标方便使用降序 
}
int dp[N][K];
signed main(){
	while(T--){
		n=read(),k=read();
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)a[i].v=read(),a[i].c=read();
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)dp[i][0]=max(dp[i-1][0],a[i].v-a[i].c);//边界 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++){
				dp[i][j]=max(dp[i-1][j],min(a[i].v-a[i].c,dp[i-1][j-1]-a[i].c));//转移 
			}
		}
		print(dp[n][k]),endl;
	}
	return 0;
}

```
**五:解释贪心**：

![](https://cdn.luogu.com.cn/upload/image_hosting/zpg03fbg.png?x-oss-process=image/resize,m_lfit,h_1700,w_2025)
如果你先选第一个，则小鬼不用魔法，你失败了。此时价值为 $2$ ，但最大价值为 $8$。

---

## 作者：juruo999 (赞：2)

# P4765 [CERC2014]The Imp

[传送门](https://www.luogu.com.cn/problem/P4765)

*这篇题解较长，更加注重体现思维过程。*

这道题主要难在发现最优决策的性质。

性质：**凡人购买宝箱的顺序一定是按 $v$ 递增的**。（不一定要选 $v$ 最小的宝箱，但是选出的宝箱序列中 $v$ 一定递增）

其他题解中已经给出了形式化证明，接下来给出一种直观的理解方式。

首先我们发现，凡人最多只能开 $k+1$ 个宝箱，**假设凡人已经想好了要依次开哪些宝箱，那么恶魔可以决定凡人实际上开了前几个宝箱**。

如果购买宝箱的时候不按 $v$ 单调递增，则一定有相邻的一对宝箱满足前面的宝箱价值大于后面的，在图中标注为绿色与橙色。

![示意图 1](https://cdn.luogu.com.cn/upload/image_hosting/qz8em63r.png)

对于上面的情况，恶魔让你拿走橙色的宝箱肯定对恶魔更有利，因为橙色的宝箱价值更小，而且你花的钱会更多，收益更少。

交换这两个宝箱后，你发现：如果恶魔拿走橙色宝箱，那么你需要花的钱更少，收益相同；如果恶魔拿走绿色宝箱，那么你获得的价值更多，花的钱相同。不管怎样，肯定对你更有利。

所以凡人购买宝箱的顺序一定是按 $v$ 递增的。

把宝箱按 $v$ 降序排序，考虑 DP。设 $f_{i,j}$ 为考虑前 $i$ 个宝箱，恶魔有 $j$ 次魔法时的最大收益。讨论是否选择第 $i$ 个宝箱作为**第一个**购买的宝箱（因为前面的宝箱都比它价值大）。

如果选择这个宝箱，则恶魔可以选择让你拿走宝箱，结束游戏，也可以把宝箱里的物品变没，让你再来一次。恶魔会选择其中使你收益较小的一个。

我们可以得到以下的转移方程：

$$
f_{i,j}=\max\left\{ f_{i-1,j},\min\left\{f_{i-1,j-1}-c_i,v_i-c_i\right\} \right \}
$$

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N=150005;

int n,k;

struct Node{
    ll v,c;
    bool operator<(const Node& o)const{
        return v>o.v;	// 按 v 降序排序
    }
}a[N];
ll f[N][12];

void work(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].c;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) f[i][0]=max(f[i-1][0],a[i].v-a[i].c);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            f[i][j]=max(f[i-1][j],min(f[i-1][j-1],a[i].v)-a[i].c);
        }
    }
    cout<<f[n][k]<<"\n";
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _;cin>>_;while(_--){
        work();
    }
    return 0;
}
```

---

## 作者：Loser_Syx (赞：2)

考虑一套已经选定了的方案，其总价值为 $\sum c_i$，因为 $c_i \geq 0$，所以我但凡买个某个东西一定是会有收益的，那么小恶魔也一定会去尝试使用魔法，所以于一个长度为 $len$ 的方案，小恶魔拿走其中 $len-1$ 个物品后，剩下的一个一定得是 $v_i$ 最大的才能止损，前面的顺序其实无关紧要，但是为了 dp 时枚举 $v_i$ 最大时需要从大到小排序。

定义 dp 状态 $dp_{i,j}$ 为选到第 $i$ 个物品，最多使用 $j$ 次魔法后的最大价值。

不使用魔法显然只能拿 $i$ 这个物品，所以 $dp_{i,0}=v_i-c_i$。  
使用 $j$ 次魔法时还需要考虑如果我以 $dp_{i,0}$ 作为开头是否会比他更好一些和与前面方案比较，则 $dp_{i,j}=\max(dp_{i-1,j-1},\min(dp_{i,0},dp_{i,j-1}-c_i))$，此处 $dp_{i,0}$ 等价于 $v_i-c_i$。

复杂度 $O(tnk)$。

```cpp
const int N=2e5+19;
int dp[N][15];
struct node {
	int v, c;
	bool operator<(const node&a)const{
		return v>a.v;
	} 
} a[N];
void solve() {
	int n=read(),k=read();
	for (int i=1;i<=n;++i) read(a[i].v,a[i].c);
	sort(a+1,a+1+n);
	for (int i=1;i<=n;++i) dp[i][0]=max(a[i].v-a[i].c,dp[i-1][0]);
	for (int i=1;i<=n;++i) for (int j=1;j<=k;++j) dp[i][j]=max(dp[i-1][j],min(a[i].v-a[i].c,dp[i-1][j-1]-a[i].c));
	write(dp[n][k],'\n');
}
```

---

## 作者：Vae_L (赞：1)

硬控我 2 小时。

起初以为是博弈论，完全不会。

发现由于只能带走一件物品，所以凡人的策略其实是确定的，将数组按照 $v_{i}$ 升序排序后一个一个选择买还是不买。

证明：我们考虑带走的物品具有的性质，即它一定是你带走的序列的收益最大值，因为如果选择的序列确定，那么代价也就确定了，自然是收益越大越好。

所以我们只需要考虑恶魔的策略，可以 dp。

设 $dp_{i,j}$ 代表前 $i$ 个，恶魔用了 $j$ 次魔法的最大收益，注意，此时为从小到大排序。

于是有如下转移：$dp_{i,j}=\max(dp_{i-1,j},min(dp_{i-1,j-1}-c_{i},?))$。

打了问号的地方代表我不知道怎么转移（大雾）

我们先解释这个方程，如果不买当前物品就是 $dp_{i-1,j}$，如果选了，则恶魔在两个策略中选一个最优的使用。

但是，会发现一个很严重的问题，就是我们根本不知道，如果恶魔不把宝物变成灰我们的收益是多少，因为此时我们并不知道前面我们花了多少代价。

所以倒着转移，因为后面的花的代价对前面根本没有影响。

转移就是：$dp_{i,j}=\max(dp_{i-1,j},min(dp_{i-1,j-1}-c_{i},v_{i}-c_{i}))$。

后面那一项就是我们把当前物品带走的收益。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,k,t,dp[150005][15];
struct node{
	int v,c;
}a[150005];
bool cmp(node a,node b)
{
	return a.v<b.v;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].c;
		sort(a+1,a+n+1,cmp);
		memset(dp,0,sizeof dp);
		for(int i=n;i>=1;i--) dp[i][0]=max(dp[i+1][0],a[i].v-a[i].c);
		for(int i=n;i>=1;i--)
		{
			for(int j=1;j<=k;j++)
			{
				dp[i][j]=max(dp[i+1][j],min(dp[i+1][j-1]-a[i].c,a[i].v-a[i].c));
			}
		}
		cout<<dp[1][k]<<"\n";
	}
	return 0;
}

---

## 作者：Loop1st (赞：1)

提供一个爆标做法，可以过 $\mathcal{O}(n \log n \log V)$, 思路源自 @A_zjzj.

首先同样的，要按 $v_i$ 升序排序，然后考虑二分答案，这里不同的是，要记的是当前选择的物品最多能抵挡多少次魔法使得答案仍然满足二分的大小，那么反悔贪心，遇到不能的，可以把前面的一个换掉，显然不劣。

有一些细节，比如 int128.

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int N = 2e5 + 10, mod = 998244353;
template<typename T>
void dbg(const T &t) { cerr << t << endl; }
template<typename Type, typename... Types>
void dbg(const Type& arg, const Types&... args) {
    #ifdef ONLINE_JUDGE
        return ;
    #endif
    cerr << arg << ' ';
    dbg(args...);
}
#define fi first
#define se second
int T, n, m;
pll a[N];
bool cmp(const pll &A , const pll &B) {
	return A.se < B.se;
}
bool check(ll x) {
	int cnt = 0;
	__int128 sum = 0;
	priority_queue<ll>q;
	for (int i = 1; i <= n; i++) {
		if (a[i].se - a[i].fi - sum >= x) {
			cnt++;
			sum += a[i].fi;
			q.push(a[i].fi);
		} else {
			if (!q.empty() && q.top() > a[i].fi) {
				sum -= q.top() - a[i].fi;
				q.pop();
				q.push(a[i].fi);
			}
		}
	}
	return cnt > m;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i].se >> a[i].fi; // 顺序与一般不同
		sort(a + 1, a + n + 1, cmp);
		ll L = 0, R = 1e18 + 1e10; // 这里如果写 1e18 + 1 要改成 (ll)1e18 + 1 否则精度问题会识别成 1e18
		while (L + 1 < R) {
			ll mid = (L + R) >> 1;
			if (check(mid)) L = mid;
			else R = mid;
		}
		cout << L << '\n';
	}
    return 0;
}
~~~

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P4765)

首先应该注意到双方都最优策略的情况下，双方都能够穷举所有情况并能看穿对方的决策，最终必然达成均衡状态，所以等价于你先选一个序列，然后恶魔再选择用几次魔法。

然后考虑这个序列怎么选。比较直观的一点是你肯定要先选 $v_i$ 较小的，即你选出的序列按 $v_i$ 升序排列。

这个很容易证明，如果 $v_1<v_2$，那么按照先 1 后 2 顺序贡献是 $\min(v_1-c_1,v_2-c_2-c_1)$，先 2 后 1 顺序贡献是 $\min(v_2-c_2,v_1-c_1-c_2)=v_1-c_1-c_2$，显然前者要优于后者。

所以实际上就是你选 $k+1$ 个物品然后看恶魔用几次魔法。

正常设置状态肯定是 $f_{i,j}$ 表示前 $i$ 个物品用了 $j$ 次魔法的答案。

考虑怎么转移。转移的意义是考虑第 $i$ 个物品能否作为第一个购买的，所以这个显然应该按 $v_i$ 降序来转移。（因为如果按照 $v_i$ 升序你只能维护最后一个）

然后转移方程就是 $f_{i,j}=\max(f_{i-1,j},\min(f_{i-1,j-1}-c_i,v_i-c_i))$。

初始化 $f_{i,0}=\max(f_{i-1,0},v_i-c_i)$。

单次时间复杂度 $O(nk)$。


```cpp
//行吧这题还要求放代码到底图啥呢搞不懂审核机制
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
#define ld long double
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
int t,n,k;
ll dp[150005][10];
struct node
{
	ll c,v;
}a[150005];
bool cmp(node a,node b)
{
	back a.v>b.v;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read(),k=read();
		for(ri i=1;i<=n;i++)
			a[i].v=read(),a[i].c=read();
		sort(a+1,a+n+1,cmp);
		dp[1][0]=max(0ll,a[1].v-a[1].c);
		for(ri i=2;i<=n;i++)
			dp[i][0]=max(dp[i-1][0],a[i].v-a[i].c);
		for(ri i=1;i<=n;i++)
			for(ri j=1;j<=min(i,k);j++)
				dp[i][j]=max(dp[i-1][j],min(dp[i-1][j-1]-a[i].c,a[i].v-a[i].c));
		cout<<dp[n][k]<<"\n";
	}
	back 0;
}
```

---

## 作者：Exber (赞：1)

## 题意
- #### 给你 $n$ 个物品，每个物品的价格是 $c_{i}$，买它可以获得 $v_{i}$ 的价值。
- #### 但是商家很坏，他可以把任意 $k$ 件你买的物品价值变为0。
- #### 求你可以获得的最大收益（总价值-总价格）。

## 做法
可以用动态规划来做。

设一个数组 $dp$，$dp_{i,j}$ 存买前 $i$ 件物品，商家使坏了 $j$ 次所得的最大收益，那么要么就不买第 $i$ 件物品，$dp_{ij}=dp_{i-1,j}$，要么就买第 $i$ 件物品，此时所获得的收益就是 $\min(dp_{i-1,j-1},v_i-c_i)$，所以最后的状态转移方程就是 $dp_{i,j}=\max(dp_{i-1,j},\min(dp_{i-1,j-1},v_i-c_i))$。

另外，收益最大化的选择顺序一定是按 $v$ 值从大到小选择的，所以要先排个序。
## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct node
{
	int v,c; // 价值，价格 
}a[1000005];

int t,n,k,dp[1000005][14]; // dp[i][j] 表示买前 i 件物品，商家使坏了 j 次所得的最大收益 

bool cmp(node x,node y)
{
	return x.v>y.v; 
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a[i].v,&a[i].c); 
		}
		sort(a+1,a+n+1,cmp); // 按 v 值从大到小排序 
		for(int i=1;i<=n;i++)
		{
			// 商家不使坏的情况（dp 数组初始化） 
			dp[i][0]=max(dp[i-1][0],a[i].v-a[i].c); // 选或者不选 
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=k;j++)
			{
				dp[i][j]=max(dp[i-1][j],min(a[i].v-a[i].c,dp[i-1][j-1]-a[i].c)); // 状态转移 
			}
		}
		printf("%d\n",dp[n][k]);
	}
	return 0;
}
```


---

## 作者：Iscream2001 (赞：1)

刚开始看题以为是博弈论，实际上不是。。。

当选择一个元素的时候，有可能会是收益消失却仍要支付代价。。。

假设我们已经选好了几个要选的元素。。设为(v1,c1),(v2,c2)....

容易发现最优的顺序一定是按照v从小到大排序。。

当然对方为了使收益最小，此时的手就是min(vi-sum(cj) (j<=i))

既然已经知道了某种方案的价值，那我们考虑要构造出收益不小于k的解，只要保证min(vi-sum(cj) (j<=i))不小于k即可

将全部元素按照v排序后，二分k，判断能否构造即可。。。由于k很小，就不用什么数据结构，直接暴力维护就可以了。。。

代码什么的不存在的。。。

---

## 作者：FReQuenter (赞：0)

我们考虑当选定购买一个集合 $(p_1,p_2,\cdots,p_{m(m\le k)})$ 时，双方的决策是怎样的。

显然分两个部分：“你”重排这个集合和小恶魔决策。

对于特定重排方案后半部分是一定的：

$$\sum_{x=1}^{m}\min\{v_x-c_1-c_2-\cdots-c_x\}$$

那么怎么知道如何重排好呢？我们从 $m=2$ 的情况入手：

$$\max\{\min\{v_1-c_1,v_2-c_1-c_2\},\min\{v_2-c_2,v_1-c_1-c_2\}\}$$

外面是“你”的决策，里面是小恶魔的决策。

观察这个 $\max$ 比大小的时候和 $c_i$ 无关，只和 $v_1,v_2$ 有关。

所以得证“你”的重排策略就是按 $v$ 从小到大排序。因为 $v_i<v_j(i<j)$ 一定比 $v_i>v_j$ 优。

接下来考虑如何选择集合。

我们使用 dp。$f_{i,j}$ 表示当前从 $1$ 到 $i$，使用了 $j$ 次魔法。然后发现不能从前往后转移。因为不知道哪些 $c_i$ 产生贡献。所以把序列倒过来。

$$f_{i,j}=\max\{f_{i-1,j},\min\{f_{i-1,j-1}-c_{i},v_{i}-c{i}\}\}$$

外面是“你”的决策，里面是小恶魔的决策。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,f[150005][10];
struct node{
	int v,c;
}a[150005];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].c;
		sort(a+1,a+n+1,[](node a,node b){
			return a.v>b.v;
		});
		for(int i=1;i<=n;i++){
			f[i][0]=max(f[i-1][0],a[i].v-a[i].c);
			for(int j=1;j<=k;j++){
				f[i][j]=max(f[i-1][j],min(a[i].v-a[i].c,f[i-1][j-1]-a[i].c));
			}
		}
		cout<<f[n][k]<<'\n';
	}
}
```

---

## 作者：CmsMartin (赞：0)

[更好的阅读体验](http://cmsblog.top/archives/cerc2014theimp)

## 题目传送门

[题目传送门](https://www.luogu.com.cn/problem/P4765)

## 思路

Lemma. **按照 $v_i$ 升序购买一定最优。**

Proof. 设先后购买的为 $(v_1,c_1),(v_2,c_2)$ 其中 $v_1 \le v2$。此时的答案为 $\min(v_1 - c_1, v_2 - c_1 - c_2)$。假设不这样买，那么答案为 $\min(v_2 - c_2, v_1 - c_1 - c_2) = v_1 - c_1 - c_2 \le \min(v_1 - c_1, v_2 - c_1 - c_2)$，证毕。

然后就可以将 $v_i$ 排个序，假设 $f_{i,j}$ 表示买 $1 \sim i$ 的 物品，恶魔使用了 $j$ 次 magic 的收益。

那么有：

$$f_{i,j} = \max(f_{i - 1,j},\min(f_{i-1,j-1}-c_i,v_i-c_i))$$

但是，这样有个问题，就是你不知道前面的哪些 $c_i$ 是有贡献的，所以要将 $v_i$ 按倒序排序，再这样跑动态规划。

时间复杂度：$\Theta(nk)$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1.5e5 + 10;
#define V first
#define C second
long long T, Dp[MAXN][15], N, K;
pair<long long, long long> Num[MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> T;
	while (T--) {
		cin >> N >> K;
		for (int i = 1; i <= N; i++) {
			cin >> Num[i].V >> Num[i].C;
		}
		sort(Num + 1, Num + 1 + N, [](auto a, auto b) {
			return a.V > b.V;
		});
		for (int i = 1; i <= N; i++) {
			Dp[i][0] = max(Dp[i - 1][0], Num[i].V - Num[i].C);
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= K; j++) {
				Dp[i][j] = max(Dp[i - 1][j], min(Dp[i - 1][j - 1] - Num[i].C, Num[i].V - Num[i].C));
			}
		}
		cout << Dp[N][K] << endl;
	}
	return 0;
}
```

---

## 作者：AxDea (赞：0)

发现两边的最优策略都建立在对方的最优策略之上，恶魔方的策略是选择加排序，凡人方的策略是排序。

凡人方选择完毕后，恶魔方要么烧掉这个物品，要么就让凡人逃跑，这样就发现恶魔方的选择是非常依赖于凡人方的，所以凡人方的决策也可以看作选择加排序。

设凡人方最优策略的选择的排列是 $p$ ，那么最终的最优解就是：
$$
\max_p \min_{t\le k} \left\{v_{p_t} - \sum_{i = 1} ^ t c_{p_i}\right\}
$$
发现对于不同的 $p_1,p_2,\ldots,p_t$ ，只有将这 $t$ 个物品按 $v$ 从小到大排序后，才是最优解。

所以对于凡人方选择的序列 $p$ ，一定是对于 $v$ 单调不减的。

后面就简单了，对于恶魔方的两种策略设计 DP ，先对每个物品对于 $v$ 数组从小到大排序，考虑恶魔两种策略对于总体的贡献，烧掉 $i$ 物品后，为 $-c_i$ 加上后续的贡献，若不释放魔法，则为 $v_i - c_i$ 。

这样设 $f_{i, j}$ 表示考虑排序后后 $i$ 个物品，使用了 $j$ 次魔法的最优解，结合上述策略，可以列出方程：
$$
f_{i, j} = \max \{f_{i - 1, j}, \min\{f_{i - 1, j - 1} - c_i, v_i - c_i\}\}
$$


---

## 作者：dengjunhaodejia09 (赞：0)

首先，这个人肯定是先选价值小的，再选价值大的，因为越到后面代价越大，就要把价值大的放在后面。

那么我们按照价值从小到大处理，设 $dp_{i,j}$ 表示从一到 $i$ 选了 $j$ 次的最优价值。发现不知道前面删了哪些不好处理，考虑逆序。按价值从大到小，设 $dp_{i,j}$ 表示从一到 $i$ 选了 $j$ 次的最优价值。那么便有的转移式
```cpp
if(j==0){
  dp[i][j]=max(dp[i-1][j],a[i].v-a[i].c);
}else{
  dp[i][j]=max(dp[i-1][j],min(dp[i-1][j-1]-a[i].c,a[i].v-a[i].c));
}
```
此时答案便是 $dp_{n,k}$ ,考虑若是转移不到 $k$ 因为初值均为0，则是答案的平移。

---

