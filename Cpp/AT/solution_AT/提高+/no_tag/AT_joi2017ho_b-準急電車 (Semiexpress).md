# 準急電車 (Semiexpress)

## 题目描述

JOI 铁路公司是 JOI 国唯一的铁路公司。

在某条铁路沿线共有$n$个站点，依次编号为$1,2,\cdots, n$。当前有两种列车服役，分别是高速列车和普通列车。

- 普通列车每站都停，对于每一个$i(1\leq i < N)$，从站点$i$到站点$i+1$用时$A$分钟。

- 高速列车只在站点$S_1,S_2,\cdots,S_M(1=S_1<S_2<\cdots<S_M=N)$停车，对于每一个$i(1\leq i < N)$，从站点$i$到站点$i+1$用时$B$分钟。

JOI 铁路公司拟定开设第三类车次：准高速列车。对于每一个$i(1\leq i < N)$，从站点$i$到站点$i+1$用时$C$分钟。准高速列车停的站点还没有决定好，但是这些站点必须满足以下要求：

- 高速列车停的所有站点准高速列车都必须停。

- 准高速列车必须停恰好$K$个站点。

JOI 铁路公司想要最大化从$1$号站点在$T$分钟内可以到的站点数目（不计$1$号站点，不计等车和换乘时间）。JOI 铁路公司想要合理地安排站点使得这个数目最大。

当合理地安排准高速列车停的站点时，从$1$号站点出发在$T$分钟内抵达的站点（$1$号站点不计）最多是多少？

## 说明/提示

所有的数据满足以下条件：

$2\leq N\leq 10^9,2\leq M\leq K\leq 3000,K\leq N$

$1\leq B < C < A \leq 10^9,1\leq T\leq 10^{18}$

$1=S_1<S_2<\cdots<S_M=N$

子任务 $1(\texttt{18 pts})$

$N\leq 3000,K-M=2,A\leq 10^6,T\leq 10^9$

子任务 $2(\texttt{30 pts})$

$N\leq 300$

子任务 $3(\texttt{52 pts})$

无特殊限制。

## 样例 #1

### 输入

```
10 3 5
10 3 5
30
1
6
10```

### 输出

```
8```

## 样例 #2

### 输入

```
10 3 5
10 3 5
25
1
6
10```

### 输出

```
7```

## 样例 #3

### 输入

```
90 10 12
100000 1000 10000
10000
1
10
20
30
40
50
60
70
80
90```

### 输出

```
2```

## 样例 #4

### 输入

```
12 3 4
10 1 2
30
1
11
12```

### 输出

```
8```

## 样例 #5

### 输入

```
300 8 16
345678901 123456789 234567890
12345678901
1
10
77
82
137
210
297
300```

### 输出

```
72```

## 样例 #6

### 输入

```
1000000000 2 3000
1000000000 1 2
1000000000
1
1000000000```

### 输出

```
3000```

# 题解

## 作者：Acfboy (赞：4)

@xtx1092515503 的题解已经说明了贪心的做法，但似乎都没有正确性证明，现在我来证一个。

> 求证: $s_i$ 到 $s_{i+1}$ 中，在高速列车 + 慢车最后能到达的地方放置准高速列车是最优的

设放置准高速列车的点和 $s_i$ 之间相距 $j$ , 最后的一个能到达的点坐标为 $f$

#### $s_i + j > f+1$ 时

此时中间会断开一段，不是连续的。

$j$ 以后能到的点个数 $s' = \lfloor \frac{T - B \times S_i - C \times j}{A} \rfloor$

由于前面能到达的点数不变，$s'$ 随着 $j$ 的增大而减小， 所以 $j = f + 2$ 时最大

#### $s_i + j \le f+1$ 时

总共能走的路程是 $s_i + j + \lfloor \frac{T-B \times S_i - C \times j}{A} \rfloor$ 

化简得 $s' = \lfloor \frac{T + S_i \times (A - B)}{A} + \frac{j \times (A - C) }{A} \rfloor$

这个随着 $j$ 增大而增大，此时 $j = f+1$ 最大

#### 综上

$j = f+1$ 和 $j = f+2$ 时，换乘准高速列车之前能走过的站数相同， $j = f+1$ 时之后能走过的显然大于等于 $j = f+2$ 时之后能走过的，所以 $j = f+1$ 时最优 

$Q.E.D$

奉上我的代码，这题 $n^2$ 可以过，我没有用优先队列，应该可以更好理解一些。

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
const int M = 3005;
int n, m, k, A, B, C, s[M], f[M], t[M], ans, T, p;
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	scanf("%lld%lld%lld", &A, &B, &C);
	scanf("%lld", &T);
	for(int i = 1; i <= m; i++) scanf("%lld", &s[i]);
	s[m+1] = s[m] + 1;
	for(int i = 1; i <= m; i++) {
		if((s[i]-1) * B > T) break;
		p ++;
		t[i] = (s[i]-1) * B;
		f[i] = s[i];
		ans += std::min((T - t[i]) / A + 1, s[i+1] - s[i]);
	}
	ans --; //1 号站不算
	k = k - m; // k 是要插入的站数
	m = p;
	for(int i = 1; i <= k; i++) {
		int max = 0ll, maxj = 0ll, to = 0ll, mto = 0ll;
		for(int j = 1ll; j <= m; j++) {
			if(f[j] >= s[j+1]) continue;
			to = (T - t[j]) / A + 1;
			if(to * C + t[j] > T) continue;
			int an = std::min((T - to * C - t[j]) / A + 1, s[j+1] - f[j] - to);
			if(an > max) {
				max = an;
				maxj = j;
				mto = to;
			}
		}
		ans += max;
		f[maxj] += mto;
		t[maxj] += mto * C;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：BDFCL (赞：4)

**Solution**

由于题目中说快车停的站次快车都要停，不妨先将$K=K-M$，表示将这些站都设好，然后考虑其他的

看到题目这么复杂，第一反应是$dp$（~~这题好像有大佬用贪心过的orz，我tcl所以推不出怎么贪心，只好用dp~~）

由于$N$很大，所以我们考虑以快车停站作为阶段$dp$

我们设$f(i, j)$表示看到快车停的第$i$站，已经建了$j$个次快车时最多能够到几站

那么大概类似于背包的，我们可以写出转移方程的大概形式：
$$
f(i, j) = \max \{f(i-1,j-x) + w(i-1,x)\}
$$
其中$w(i-1,x)$表示上一站到这一站中建设$x$个次快车站最多能够到达的车站数

下面首先考虑如何求出$w$

我们注意到，由于快车速度大于次快车速度大于慢车速度，所以我们到某一个站点的乘车方式一定是快车$\to$次快车$\to$慢车

假设我们定下了快车与次快车所需的总时间$T_0$，我们所能够到达的慢车数量应该是$\lfloor\frac{T_0}{A}\rfloor$

又由于快车的时间已经定下来了，不靠慢车所能够到达的数量也定下来了，我们只需要让所能够到达的慢车数量最大，所以我们只需让上述的$T_0$最大

显然，我们应该在前一个次快车站后乘坐慢车所能够到达的最大的车站的下一处车站处设置车站

这样，我们就可以通过一次递推求出$w$了

注意：

​	如果所能够到达的最大车站超出了下一个快车车站的话是不行的，所以要与下一个快车车站和这个次快车展之间车站数取个$\min$

​	由于我们柿子里没有算上这个次快车站，所以要$+1$

具体的操作细节比较多，需要慢慢推一推，具体的看代码吧

这样我们就可以在$O(M^2)$的时间内求出$w$了（这里由于$M,K$同价，所以包括之后时间复杂度中为了简洁，都用$M$表示）

然后我们再回到$dp$柿子，显然，这是$O(M^3)$，需要优化

我们使用瞪眼法，发现这个柿子有可能会有决策单调性

于是我们打了几张表，把样例都带进去试了试

发现他好像真的有！（我承认我菜到不会证这个东西）

于是我们就可以通过分治优化$dp$的方式在$O(M^2\log M)$内求的答案了

总的复杂度大概是$O(M^2\log M + M^2)$的

这题细节比较多，大概说个几点：

* 我们$dp$是把$1$号车站也算上了，所以要特判一下最后一号能不能走到，走不到的话答案要$-1$
* 不一定是能够走到最后几个快车站的，所以不能直接输出$f(M,K)$，而是应该将前面的取$\max$（其实找最后一个能够到达的应该也行，但懒得写）
* $T$要开$long$  $long$，所以快读也要开
* 推$w$那里是否要$+1$，$-1$细节很多，最好想清楚

**Code**

```c++
#include <bits/stdc++.h>

#define inf (ll)-1e18
#define N (int) 3005
#define ll long long

using namespace std;
ll input () {
	ll x = 0, f = 0;
	char c = getchar ();
	while (c < '0' || c > '9') f = c == '-', c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1ll) + (x << 3ll) + (c ^ 48), c = getchar ();
	return f ? - x : x ;
}

ll n, m, k;
ll A, B, C;
ll T;
ll a[N];

ll dp[N][N], w[N][N];

void DP (int id, int l, int r, int L, int R) { //分治优化DP
	if (l > r) return ;
	int mid = (l + r) >> 1;
	int pos = 0;
	for (int i = L; i <= min (mid, R); i ++) {
		if (dp[id][mid] <= dp[id-1][mid-i] + w[id-1][i]) {
			pos = i;
			dp[id][mid] = dp[id-1][mid-i] + w[id-1][i];
		}
	}
	DP (id, l, mid-1, L, pos);
	DP (id, mid+1, r, pos, R);
}

int main () {
	freopen ("car.in", "r", stdin);
	freopen ("car.out", "w", stdout);
	
	n = input (), m = input (), k = input ();
	A = input (), B = input (), C = input ();
	T = input ();
	for (int i = 1; i <= m; i ++) a[i] = input ();
	
	k -= m;
	ll tot = 0;
	ll cnt = 0;
	for (int i = 1; i <= m; i ++) {
        /* 
        暴力dp，猜决策单调性
		for (ll j = 0; j <= k; j ++) {
		 	int pos = 0;
		 	for (int x = 0; x <= j; x ++) {
		 		if (dp[i-1][j-x] + w[i-1][x] >= dp[i][j]) pos = x;
		 		dp[i][j] = max (dp[i][j], dp[i-1][j-x] + w[i-1][x]);
		 	}
			cout << pos << " ";
		}        
		cout << endl; 
        */

		DP (i, 0, k, 0, k);
	
        // 比较绕的递推w
		ll Tx = T - (a[i]-1) * B;
		if (Tx <= 0) break;
		cnt = 0;
		for (int j = 0, sum = 0; j <= k && sum+a[i] < a[i+1]; j ++, cnt ++) {
			if (Tx - C * sum < 0) break;
			if (j != 0) w[i][j] = w[i][j-1] + min ((Tx-C*sum)/ A, a[i+1]-1-sum-a[i])+1;
			else w[i][j] = min ((Tx-C*sum)/A, a[i+1]-1-sum-a[i])+1;
			sum += (Tx-C*sum)/ A + 1;
		}
		tot += cnt;
	}
	
	ll ans = 0;
	for (int i = 1; i <= m; i ++) ans = max (ans, (a[i]-1) * B <= T ? dp[i][k] : dp[i][k]-1);
	
	cout << ans << endl;
	
	return 0;
}

```

**Conclusion**

* 比较绕的最值问题——DP
* 贪心
* DP如果不会优化可以猜一下决策单调性
* 细节问题

---

## 作者：xtx1092515503 (赞：3)

贪心。

------------

我们考虑从 $1$ 号站出发到其它站的最优做法，发现一定是：

1. 坐快车到目标前最后一站停的位置

2. 坐中车到目标前最后一站停的位置

3. 坐慢车直到目标

然后它又强制中车和快车的线路重合，所以我们可以构造出如下的贪心：

1. 枚举每一个快车站，找到从这站往后坐慢车能够到的最远位置，并让答案增加，因为这些站是无论修不修中车都可以到的。

2. 尝试在上述的最远位置的下面一站修一个中车站，并求出从该中车站往后坐慢车的最远位置。这是修建一个中车站所能带来的最大收益，把它丢进一个堆里维护即可。

3. 重复步骤2，直到下面三项有至少一项发生：

- 当前的新中车站已经不可能走到

- 当前的最远位置已经超过了下一个快车站的位置

- 这已经是当前两个快车站间尝试修建的第 $k-m$ 个中车站。

明显，此方法一定是最优的；然后，贪心也是正确的，因为在两个快车站之间修建的中车站，其收益一定是递减的，故我们不会出现修了后面的一个车站却没把前面的车站修上的情形。

时间复杂度 $O\Big(m(k-m)\log(k-m)\Big)$，因为堆中只需要维护前 $(k-m)$ 个最大收益即可。最劣大约是 $1500^2\times \log 1500\approx2.25\times 10^7$ 的，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,k,a,b,c,s[3010],res;
ll T;
priority_queue<int>q;
int main(){
	scanf("%d%d%d%d%d%d%lld",&n,&m,&k,&a,&b,&c,&T);
	for(int i=1;i<=m;i++)scanf("%d",&s[i]);
	s[m+1]=n+1;
	k-=m;
	for(int i=1;i<=m;i++){
		ll tmp=s[i],rem=T-1ll*(s[i]-1)*b;
		if(rem<0)break;
		ll now=s[i]+rem/a;
//		printf("%lld %lld %lld\n",tmp,rem,now);
		res+=min(now,1ll*s[i+1]-1)-s[i]+1;
		int tms=k;
		while(tms&&rem>=0){
			tms--;
			ll qwq=(now+1-tmp)*c;
			rem-=qwq;
			if(rem<0)break;
			tmp=now+1;
			if(tmp>=s[i+1])break;
			now=tmp+rem/a;
//			printf("%lld %lld %lld\n",tmp,rem,now);
			q.push(-(min(now,1ll*s[i+1]-1)-tmp+1));
			while(q.size()>k)q.pop();
		}
	}
	while(!q.empty())res-=q.top(),q.pop();
	printf("%d\n",res-1);
	return 0;
}
```

---

## 作者：Rem_CandleFire (赞：1)

### 分析与做法

为方便起见，以下把准快车站点称作 $C$，慢车和快车站点分别叫做 $A$ 和 $B$。

在本题中，我们发现，每一段 $B_i$ 到 $B_{i+1}$ 之间都有一部分站点是通过快车加慢车就可以到达，而准快车站点建立在这一部分站点上**一定不优**。

所以考虑预处理出一个 $far_i$ 数组，表示从 $B_i$ 出发，坐慢车能到的最远站点，先把这些不用准快车就能到的计算上。

现在我们只需要考虑额外的 $C$，即令 $k=k-m$。根据第一段的分析，每加入一个 $C$，它的建造位置可以贪心地取**最前的一个不能由 $B$ 或 $C$ 坐慢车到达的点**，而从这个点开始能够到达的点也是固定的。于是考虑用一个数组记录下每一个可能的 $C$ 对答案的贡献。

根据上述分析，对每一段进行处理，得到数组 $g_{i,j}$，表示第 $i$ 段建立的第 $j$ 个 $C$ 的贡献。那么问题就变成了：在 $m$ 段里取 $k$ 个，其中第 $i$ 段最多只能取 $g_{i,j}$ 不等于 $0$ 的部分，的最大贡献。使用 DP 即可。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3005;
int n,m,k,A,B,C,ans;int t;
int far[N],P[N],dp[N][N]; 
int f[N][N];
vector<int> g[N];
void Get_g()
{
	for(int i=1;i<=m;i++)
	{
		if(t<(P[i]-1)*B) break;
		if(far[i]+1>P[i]+(t-(P[i]-1)*B)/C) continue; // 本段无额外贡献
		int x=far[i]+1,cnt=1;
		while(x<min(P[i+1]*1ll,P[i]+(t-B*(P[i]-1))/C+1)&&cnt<=k)
		{
			int sum=(t-B*(P[i]-1)-C*(x-P[i]))/A;
			if(sum<0) break;
			if(x+sum>=P[i+1]) g[i].push_back(P[i+1]-x); // 记录贡献 
			else g[i].push_back(sum+1);
			x+=sum+1; cnt++;
		}
	}
}
void DP() // 经典DP 
{
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		for(int j=1;j<=g[i].size();j++)
		{
			sum+=g[i][j-1];
			for(int p=j;p<=k;p++)
				dp[i][p]=max(dp[i][p],dp[i-1][p-j]+sum);
		}
		for(int j=0;j<=k;j++)
			dp[i][j]=max(dp[i][j],dp[i-1][j]);
	}
}
signed main()
{
	scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&m,&k,&A,&B,&C,&t);
	P[0]=1; P[m+1]=n; k-=m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&P[i]); 
		far[i]=P[i]-1;
		if(t>(P[i-1]-1)*B) far[i-1]=P[i-1]+min((t-(P[i-1]-1)*B)/A,(P[i]-P[i-1]-1)*1ll);
	}
	if(t>=(P[m]-1)*B) far[m]=n;
	else far[m]=n-1; 
	for(int i=1;i<=m;i++) 
		if(t>=(P[i]-1)*B)
			ans+=far[i]-P[i]+1; // 初始能到的点 
	Get_g();
	DP();
	int add=0;
	for(int i=k;i>=1;i--) add=max(add,dp[m][i]);
	printf("%lld\n",ans+add-1);
	return 0;
}

```

---

## 作者：chenxia25 (赞：1)

这是个挺有意思的题，虽然不难。

我们考虑先把普通列车给算进去，然后再用高速列车、准高速列车依次来松弛它。那么显然一开始位置 $i$ 的最短路为 $(i-1)a$。那么显然 $\leq t$ 的是一个前缀。

接下来把高速列车放进去。这样子这个格局就是，每个相邻高速列车之间的 gap 为一个单位，然后每个单位的前缀 $\leq t$。这很容易算出来。

然后考虑将准高速列车加进去。所有高速列车停靠站都要在准高速列车里面，那么就是说原先的大格局不会改变，只会在里面分裂。于是考虑原先的每个单位，如果想加一个准高速列车进去，那么如果加在可行前缀里面，那显然不如加在后面一位来的贡献大；如果加在后面一位的后面，那就效果是一样的，但是后面的机会可能更小，毕竟最多只能将这个 gap 填满。于是贪心地，每次在可行前缀后面一位放，然后延长前缀，这个延长操作可以用一个除法常数搞定。于是我们算出了每个 gap 填多少个准高速列车的贡献（显然每个 gap 是独立的）。

然后看似背包就可以了？但这样是三方的。我们注意到一个性质：不仅对于每个 gap 贡献随准高速列车递增，而且差分还是递减的（这个其实是显然的）。于是我们考虑将初始（不放准高速列车）的加起来，然后每放一个就是当前 gap 加上后面一个差分。这样可以看出显然最大的若干个一定是几个前缀并起来，于是贪心就可以了，每次找当前最大的 gap 的第一个。

复杂度 $\mathrm O(mk)$，**_[code](https://www.luogu.com.cn/paste/bm03lcz1)_**。

---

## 作者：729hao (赞：0)

一眼，模拟！

再看 $N$ 的范围，贪心……

------------
我们可以把所有站点分为三类：
1. $1$ 号站点
2. 只乘坐高速列车和普通列车就能在 $T$ 分钟内到达的站点
3. 只乘坐高速列车和普通列车不能在 $T$ 分钟内到达的站点

对于第 $2$ 类站点，我们没必要将它们设为准快速列车的站点，所以我们只用考虑第 $3$ 类站点。

而对于第 $3$ 类站点，最贪心的思路一定是“在高速列车 + 慢车最后能到达的地方放置准高速列车”。

@Acfboy 已经在[他的题解](https://www.luogu.com.cn/blog/Acfboy/solution-at2443)中证明了此思路的正确性，我就不再次证明了。

我们可以把所有在第 $3$ 类站点中，设置准高速列车站点能按时到达的每一个站点，算出比不设置多到达的站点数，最后求出其中贡献最大的 $(K-M)$ 个，加上第 $2$ 类站点的个数，就是最终的答案。
```cpp
if((s[pt]-1ll)*b+(i*1ll-s[pt])*c<=t){//能按时到达
	now=min((t-(s[pt]-1ll)*b-(i*1ll-s[pt])*c)/a+1,s[pt+1]*1ll-i);
	q.push(now);
}
```
但是我们忽略了两点：
+ 准高速列车站点有限制
+ 第 $3$ 类列车数量太多，挨个扫容易 TLE

因为对于任意两个第 $3$ 类站点 $i$、$i+1$ ，选择 $i$ 一定比 $i+1$ 更优，所以每次我们扫完一个站点后，下一个就扫从这个站点能按时到达的最远的站点 $+1$ ；如果扫的站点个数大于 $(K-M)$ ，就从下一个高速列车站点开始扫。
```cpp
for(i=1;i<=n;i++){
	if(i==s[pt+1]){//是高速列车站点 
		kkk=0;
		ti=(i-1ll)*b;
		if(ti>t)break;//扫到最远能到达的高速列车站点为止
		pt++;
		now=min((t-ti)/a+1,s[pt+1]*1ll-i);//只乘坐高速列车和普通列车就能在T分钟内到达的站点个数 
		ans+=now;
		i+=now-1;//下一次扫从最远站点+1开始 
	}
	else{//不是高速列车站点 
		if(kkk<k&&(s[pt]-1ll)*b+(i*1ll-s[pt])*c<=t){ 
			now=min((t-(s[pt]-1ll)*b-(i*1ll-s[pt])*c)/a+1,s[pt+1]*1ll-i);
			q.push(now);
			i+=now-1;//下一次扫从最远站点+1开始 
			kkk++;
		}
		else{
			i=s[pt+1]-1;//下一次扫从下一个高速列车站点开始 
			kkk=0;
		}
	}
}
```
看起来这段代码的复杂度是 $O(N)$ ，实际上有许多站点都是跳过了的，所以不会超时。

最后求出前 $(K-M)$ 个最大贡献，加上 $ans$ ，减去算上的 $1$ 号站点，就是最终答案。

AC 代码：
```cpp
#include<cstdio>
#include<queue>
using namespace std;
int n,m,k,a,b,c,s[3005],pt,ans,kkk,i;
long long t,ti,lt,now;
priority_queue<int>q;
int main(){
	scanf("%d %d %d",&n,&m,&k);
	scanf("%d %d %d",&a,&b,&c);
	scanf("%lld",&t);
	for(i=1;i<=m;i++){
		scanf("%d",&s[i]);
	}
	k-=m;//提前减去m个高速列车站点 
	s[m+1]=n+1;
	for(i=1;i<=n;i++){
		if(i==s[pt+1]){//是高速列车站点 
			kkk=0;
			ti=(i-1ll)*b;
			if(ti>t)break;//扫到最远能到达的高速列车站点为止
			pt++;
			now=min((t-ti)/a+1,s[pt+1]*1ll-i);//只乘坐高速列车和普通列车就能在T分钟内到达的站点个数 
			ans+=now;
			i+=now-1;//下一次扫从最远站点+1开始 
		}
		else{//不是高速列车站点 
			if(kkk<k&&(s[pt]-1ll)*b+(i*1ll-s[pt])*c<=t){ 
				now=min((t-(s[pt]-1ll)*b-(i*1ll-s[pt])*c)/a+1,s[pt+1]*1ll-i);
				q.push(now);
				i+=now-1;//下一次扫从最远站点+1开始 
				kkk++;
			}
			else{
				i=s[pt+1]-1;//下一次扫从下一个高速列车站点开始 
				kkk=0;
			}
		}
	}
	while(k&&!q.empty()){//算最大贡献 
		ans+=q.top();
		q.pop();
		k--;
	}
	printf("%d\n",ans-1);
	return 0;
}

```

---

## 作者：Day_Dreamer_H (赞：0)

# 準急電車 题解
题目还是很浅显易懂的。

首先我们要去某个站的时候肯定是从快的做到最近，再转乘做到最近，再转乘，这样时间肯定是最短的。

那我们怎么分配准快车站呢，应该是在没建站之前花费时间正好大于 $T$ 时新建一个站，这样我们转乘的时候就可以从那个准快车站再重新向外拓展，新拓展的站点就是在这里建的价值，丢进优先队列不断拿出来即可。

拓展的时候有一些小细节：不能拓展过下一个快车站那里，而且最多不能在两个快车站里面修建 $K-M$ 个站点，因为所有的快车站准快车都要停下。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k;
long long a,b,c;
long long t;
long long s[30005];
priority_queue<long long>q;
long long val,result;
int main(){
	cin>>n>>m>>k;
	cin>>a>>b>>c;
	cin>>t;
	k-=m;
	for(int i = 0;i<m;i++){
		cin>>s[i];
	}
	for(int i = 0;i<m-1;i++){
		int counter = 0,cur = s[i];
		while(cur<s[i+1]){
			counter++;
			long long lst = t-(s[i]-1)*b-(cur-s[i])*c;
			if(lst<0){
				break;
			}
			val = lst/a+1;
			if(cur+val>=s[i+1]){
				val = s[i+1]-cur;
				cur = s[i+1];
			}
			cur+=val;
			if(counter == 1){
				result+=val;
			}else{
				q.push(val);
			}
			if(counter>k+1){
				break;
			}
		}
	}
	if(t>=(n-1)*b){
		result++;
	}
	while(q.size()&&k){
		k--;
		result+=q.top();
		q.pop();
	}
	cout<<result-1<<endl;
}
```

---

