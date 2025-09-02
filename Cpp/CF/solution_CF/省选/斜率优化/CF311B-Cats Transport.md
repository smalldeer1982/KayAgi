# Cats Transport

## 题目描述

Zxr960115 是一个大农场主，他饲养了 $m$ 只可爱的猫咪，并雇用了 $p$ 名饲养员。农场中有一条笔直的道路，道路旁有 $n$ 座山丘，从左到右依次编号为 $1$ 到 $n$。第 $i$ 座山丘与第 $(i-1)$ 座山丘之间的距离为 $d_{i}$ 米。所有饲养员都居住在山丘 $1$。

某天，猫咪们外出玩耍。第 $i$ 只猫咪前往山丘 $h_{i}$，并在时间 $t_{i}$ 结束游玩，随后在山丘 $h_{i}$ 等待饲养员接它。饲养员必须接走所有猫咪。每位饲养员从山丘 $1$ 走向山丘 $n$，途中不在任何山丘停留，并带走途中每个山丘上所有等待的猫咪。饲养员的行走速度为 $1$ 米/单位时间，且他们的运输能力足够强，可以携带任意数量的猫咪。

例如，假设有两座山丘（$d_{2}=1$）和一只猫咪，该猫咪在时间 $3$ 结束游玩于山丘 $2$（$h_{1}=2$）。若饲养员在时间 $2$ 或时间 $3$ 离开山丘 $1$，则能接到这只猫咪；但若在时间 $1$ 离开则无法接到。若饲养员在时间 $2$ 出发，猫咪的等待时间为 $0$；若在时间 $3$ 出发，猫咪的等待时间为 $1$。

你的任务是规划每位饲养员从山丘 $1$ 出发的时间，使得所有猫咪的等待时间总和最小。

## 说明/提示

对于 $100\%$ 的数据，$2 \le n \le 10^5,\ 1 \le m \le 10^5,\ 1 \le p \le 100, 1 \le d_{i} < 10^4,1 \le h_i \le n,\ 0 \le t_i \le 10^9$。

## 样例 #1

### 输入

```
4 6 2
1 3 5
1 0
2 1
4 9
1 10
2 10
3 12
```

### 输出

```
3
```

# 题解

## 作者：ww3113306 (赞：38)

## [广告](https://www.cnblogs.com/ww3113306/p/9932521.html)
　　貌似上一篇题解讲得不是很详细，这里详细将一下题意是如何一步步转化的+单调性证明吧。
  
　　首先我们观察到山与距离其实是没有什么用的，因为对于任意一只猫，我们都可以直接算出如果有一个人要恰好接走它，需要在哪一时刻出发，我们设第i只猫对应的这个时刻为$t_{i}$.

　　注意这个$t_{i}$是我自己新定义的，跟题目中的没有关系，下面所写的t都是我现在所定义的t，而跟原题面中的t没有任何关系。

　　然后我们对t数组排个序，于是题意转化为了有m只猫，每只猫有一个权值$t_{i}$,如果出发时间大于等于$t_{i}$,则可以接到第i只猫。设出发时间为x，则接到第i只猫时，这只猫会等待$x - t_{i}$的时间。现在有p个人，要求为每个人指定一个时间使得所有猫的等待时间之和最小。

　　然后我们继续转化题意。

　　观察到每个人相当于会选择一只猫i，然后选择在$t_{i}$时刻出发，恰好接走这只猫，顺便可以接走其他可以被接走的猫。

　　为什么是每个人都必须选一只猫呢？

　　观察到如果一个人出发，没有任何一只猫是恰好被接到的，所有猫都是等了一会再被接走的，那么这个人为什么不早出发一点，恰好接走一些猫呢？这样不仅可以接走和上一种方案相同的猫，还可以减小等待时间。

　　于是现在题意转化为了有m只猫，每只猫有一个权值$t_{i}$。如果第x个人选择了第i只猫，上一个出发的人选了第j只猫，则这个人可以接走[j + 1, i]中的所有猫，并且代价为$\sum_{k = j + 1}^{i}{t_{i} - t_{k}}$。现在有p个人，要求为每个人指定一只猫使得所有猫的等待时间之和最小。

　　先化一下式子：(其中s[i]表示$\sum_{k = 1}^{i}{t[k]}$)

　　$$\sum_{k = j + 1}^{i}{t_{i} - t_{k}}$$
　　$$= \sum_{k = j + 1}^{i}{t_{i}} - \sum_{k = j + 1}^{i}{t_{k}}$$
　　$$= (i - j) t_{i} - (s[i] - s[j])$$

　　于是我们设f[i][j]表示DP到第i个人，这个人选择了第j只猫的最小代价。

　　然后暴力枚举i，j，转移的时候再暴力枚举前一个人选了哪只猫即可。

　　但是这样的复杂度是$pm^2$的，观察到我们优化到$pm$就可以过了，又注意到式子中有一个跟i相关的量和一个跟j相关的量的乘积，我们考虑一下斜率优化。

　　我们先化一波式子。

$$f[i][j] = f[i - 1][k] + (j - k) t_{j} - (s[j] - s[k])$$
$$\Rightarrow f[i][j] = f[i - 1][k] + jt_{j} - kt_{j} - s[j] + s[k]$$
$$\Rightarrow -s[k] - f[i - 1][k] = -kt_{j} + jt_{j} - s[j] - f[i][j]$$
$$\Rightarrow s[k] + f[i - 1][k] = t_{j}k - jt_{j} + s[j] + f[i][j]$$
　　代入y = kx + b可以得到$y = s[k] + f[i - 1][k], x = k, K = t_{j}, b = -jt_{j} + s[j] + f[i][j]$。

　　斜优式子已经出来了，现在就是要**证明单调性**了。

　　首先$K = t_{j}$本来就是排好序的，所以从小到大枚举j，所以每次加入的决策点$(x, y)$中的$x = j$肯定是递增的，$t_{j}$肯定也是递增的。

　　所以就可以直接上斜优了。　　

　　然而写的时候发现我对计算几何一无所知，，，凸包维护错了调了好久QAQ
  	
　　~~发现第一次写的时候证的单调性不是斜优需要的那个单调性。。。。。更新一下，现在证的应该是斜优需要的那个了~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 110
#define ac 120000
#define LL long long

int n, m, p, Head, tail, now;
LL ans;
LL f[AC][ac], d[ac], t[ac], sum[ac], s[ac];

inline int read()
{
	int x = 0;char c = getchar();
	while(c > '9' || c < '0') c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

inline void pre()
{
	n = read(), m = read(), p = read();
	for(R i = 2; i <= n; i ++) d[i] = read() + d[i - 1];//顺便统计一下前缀和
	for(R i = 1; i <= m; i ++)
	{
		LL tmp = read();
		t[i] = read() - d[tmp];	
	}
	sort(t + 1, t + m + 1);
	for(R i = 1; i <= m; i ++) sum[i] = sum[i - 1] + t[i];//这个要放在排好序之后
}

inline void upmin(LL &a, LL b){
	if(b < a) a = b;
}

inline LL Y(int k){
	return sum[k] + f[now][k];
}

inline LL cross(int a, int b, int c){//算叉积
	LL x1 = a - b, x2 = b - c, y1 = Y(a) - Y(b), y2 = Y(b) - Y(c);
	return x1 * y2 - x2 * y1;
}

inline LL cal(int x, int k){//算出y - kx,表示b的大小
	return Y(x) - t[k] * x;
}

inline void work()
{
	for(R i = 1; i <= m; i ++) 
		f[1][i] = i * t[i] - sum[i];//先算出第一个人的
	ans = f[1][m];
	for(R i = 2; i <= p; i ++)//枚举人
	{
		Head = 1, tail = 0, now = i - 1;
		s[++tail] = 0;//0也是一个决策点
		for(R j = 1; j <= m; j ++)//枚举当前选择的猫
		{
			while(Head < tail && cal(s[Head + 1], j) < cal(s[Head], j)) ++ Head;
			int x = s[Head];
			f[i][j] = f[i - 1][x] + (j - x) * t[j] - sum[j] + sum[x];
			while(Head < tail && cross(j, s[tail], s[tail - 1]) > 0) -- tail;
			s[++ tail] = j;
		}
		upmin(ans, f[i][m]);
	}
	printf("%lld\n", ans);
} 

int main()
{
	freopen("in.in", "r", stdin);
	pre();
	work();
	fclose(stdin);
	return 0;
}
```
 

---

## 作者：Imakf (赞：25)

斜优好题，与普通斜优不同之处在于多了一个维度，转移顺序不能出错.

------

对于每一只猫可以计算出何时出发的人可以正好接走它。

如此得到一个长 $m$ 的时间数组 $t[]$，将它从小到大排序。

题意变为：把数组分为 $p$ 段，每段的代价是所有数与该段最大值的差值之和。求最小代价。

令 $S[]$ 数组为 $t[]$ 数组的前缀和。

所求即 

$$dp[i][j]=\min\limits^{j-1}_{k=0}(dp[i-1][k]+t[j]*(j-k)-S[j] + S[k])$$ 

$dp[p][m]$ 的值。

**倘若我们不看段数 $p$ 的限制，方程就是:**

$$dp[i]=\min\limits^{i-1}_{j=0}(dp[j]+t[i]*(i-j)-S[i]+S[j])$$

显然为斜优柿子。

转移点 $j_2$ 比 $j_1(j_1<j_2)$ 优 的条件为

$\dfrac{S[j_1]+dp[j_1]-S[j_2]-dp[j_2]}{j_1-j_2}<t[i]$	

倘若加入段数限制，那么我们只需要在枚举 $i$ 的同时，**内层循环枚举段数转移即可**。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
using namespace std;

#define rg register
#define il inline
#define MX (100000 + 5)
#define ll long long

ll d[MX] ,t[MX] ,S[MX];
int q[101][MX];
ll dp[101][MX];
int hd[MX] ,tl[MX];

double Slope(int i ,int j1 ,int j2){
	return (1.0 * S[j1] + dp[i][j1] - S[j2] - dp[i][j2]) / (j1 - j2);
}

int main(){
	int n ,m ,p;
	cin >> n >> m >> p;
	if(p >= m)	return puts("0") ,0;
	for(int i = 2 ; i <= n ; ++i){
		cin >> d[i];
		d[i] += d[i - 1];
	}
	for(int i = 1 ,x ,p ; i <= m ; ++i){
		cin >> p >> x;
		t[i] = -d[p] + x;
	}
	sort(t + 1 ,t + 1 + m);
	for(int i = 1 ; i <= m ; ++i)
		S[i] = S[i - 1] + t[i];
	for(int i = 1 ; i <= m ; ++i){
		for(int j = 1 ; j <= min(i ,p) ; ++j){
			while(hd[j - 1] < tl[j - 1] && Slope(j - 1 ,q[j - 1][hd[j - 1]] ,q[j - 1][hd[j - 1] + 1]) <= t[i])
				++hd[j - 1];
			int tr = q[j - 1][hd[j - 1]]; 
			dp[j][i] = (dp[j - 1][tr] + t[i] * (i - tr) - S[i] + S[tr]);
			while(hd[j] < tl[j] && Slope(j ,q[j][tl[j]] ,i) < Slope(j ,q[j][tl[j] - 1] ,q[j][tl[j]]))
				--tl[j];
			q[j][++tl[j]] = i;
		}
	}
	cout << dp[p][m];
	return 0;
}
```

---

## 作者：Linshey (赞：18)

## 1.问题转化：

首先这一大堆时间乱七八糟的很麻烦，我们稍微做一个处理：
$\color{red}\text{计算出每个猫子对应的出发时间}A_{i}$,
这样接下来就方便得多了 。计算等待时间时就用实际时间和这个值相减一下就可以了

## 2.DP设计

显然地，我们可以设$f_{i, j} = $第$i$头（当然是按我们上面计算的出发时间排序的第i头）猫子、用了$j$个铲屎官的最小等候时间, 方程$f_{i, j} = min{f_{i - 1, k} + A_j * (j - k) - (S_j - S_k)}$

## 3.优化

变形：$f_{i - 1, k} + S_k = -A_j * k + f_{i, j} + S_j + A_j * j$

视决策点为：$(k, f_{i - 1, k} + S_k)$斜率优化即可。由于斜率递增，所以我们用单调队列维护半个下突壳即可

## 4.教训

对于我这个刚学OI的蒟蒻，我从这题中明白了决策点不止可以是$(j, f_j)$, 也可以是$(h(j), f_j+g(j)$之类的东东

```cpp

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 1e5 + 5;
const int maxp = 1e2 + 5;

struct Cat
{
	int h, t;
	long long st;
	bool operator <(const Cat a) const
	{
		return st < a.st;
	}
} cats[maxn];

int n, m, p, q[maxn],tail, head;

long long f[maxn][maxp], sum[maxn], d[maxn];

signed main()
{
	cin >> n >> m >> p;
	for (int i = 2; i <= n; i++)
	{
		cin >> d[i];
		d[i] += d[i - 1];
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> cats[i].h >> cats[i].t;
		cats[i].st = cats[i].t - d[cats[i].h];
	}
	sort(cats + 1, cats + m + 1);
	for (int i = 1; i <= m; i++)
	{
		sum[i] = sum[i - 1] + cats[i].st;
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= p; i++)
	{
		tail = head = 1;
		q[head] = 0;
		for (int j = 1; j <= m; j++)
		{
			while (head < tail && f[q[head]][i - 1] + sum[q[head]] - cats[j].st * q[head] > f[q[head + 1]][i - 1] + sum[q[head + 1]] - cats[j].st * q[head + 1]) head++;
			f[j][i] = f[q[head]][i - 1] + cats[j].st * (j - q[head]) - (sum[j] - sum[q[head]]);
			while (tail > head && (f[j][i - 1] + sum[j] - f[q[tail]][i - 1] - sum[q[tail]]) * (q[tail] - q[tail - 1]) < (f[q[tail]][i - 1] + sum[q[tail]] - f[q[tail - 1]][i - 1] - sum[q[tail - 1]]) * (j - q[tail]))
				tail--;
			tail++;
			q[tail] = j;
		}
	}
	printf("%lld\n", f[m][p]);
	return 0;
}
```
最后说一下，我的单调队列写错使得我调了好久

---

## 作者：flora715 (赞：10)

### 题意理解
m只猫，p个饲养员，n座山。第i~i-1座山之间的距离为di。
第i只猫去hi号山玩，玩到ti停止，开始等待饲养员。
规划每个饲养员从1号山出发的时间，使得所有猫等待时间总和最小。
### 方法分析
对于每只猫，设a[i]=t[i]-∑(j=1~hi)d[i]，即猫不等待的出发时刻。
假设饲养员在t时刻出发，接到第i只猫时，猫的等待时间为t-a[i]。
因为每个饲养员带走的一定是按照a[i]排序后的连续若干只猫【巧妙】，
所以可以把a[i]从小到大排序，求前缀和，记录在数组s中，每次用前缀和表示。
状态：f[i][j]表示**前i个饲养员带走前j只猫**的最小sum等待时间。
枚举第i个饲养员带走的猫的起始位置k，则他带走的一定是(k~j)，累计答案。
在a[j]时候出发可以让最后一只猫不等待（当前情况的最优方案），
但对此人带的其他猫的总影响为a[j]*(j-k)-(s[j]-s[k])。
```cpp
f[i][j]=min(f[i][j],f[i-1][k]+a[j]*(j-k)-(s[j]-s[k]));
```
将方程转化为：
```cpp
f[i-1][k]+s[k]=a[j]*k+f[i][j]-a[j]*j;
```
以k为横坐标，f[i-1][k]+s[k]为纵坐标建系，斜率为a[j]，截距为f[i][j]-a[j]*j。
当截距最小化时，f[i][j]取到min值。维护一个单调队列【下凸壳】。
### 代码实现
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
using namespace std;
typedef long long ll;

ll f[110][100010],g[100010]; //g数组保存斜率纵坐标f[i-1][k]+s[k]
ll s[100010],a[100010],d[100010],q[100010];

int n,m,p,x,y,head,tail;

int main(){
    cin>>n>>m>>p;
    for(int i=2;i<=n;i++){ cin>>x; d[i]=d[i-1]+x; }
    for(int i=1;i<=m;i++){ cin>>x>>y; a[i]=y-d[x]; }
    sort(a+1,a+m+1); //每人带走的一定是按照a[i]排序后的连续若干只猫
    for(int i=1;i<=m;i++) s[i]=s[i-1]+a[i];
    memset(f,0x3f,sizeof(f)); f[0][0]=0; //起点
    for(int i=1;i<=p;i++){
        for(int j=1;j<=m;j++) g[j]=f[i-1][j]+s[j];
        head=1; tail=1; q[1]=0; //注意斜率优化要从tail=1写起，且要写q[1]=0
        for(int j=1;j<=m;j++){ //[化除为乘]避免比较的误差产生
            while(head<tail&&g[q[head+1]]-g[q[head]]
                <=a[j]*(q[head+1]-q[head])) head++;
            f[i][j]=min(f[i-1][j],g[q[head]]+a[j]*(j-q[head])-s[j]); 
            //↑↑↑用min{f[i-1][k]+s[k]+a[j]*(j-k)-s[j])};更新答案
            if(g[j]>=0x3f3f3f3f3f3f3f3fll) continue; //超界
            while(head<tail&&(g[j]-g[q[tail]])*(q[tail]-q[tail-1])
                <=(g[q[tail]]-g[q[tail-1]])*(j-q[tail])) tail--;
            q[++tail]=j; //新元素入队
        }
    }
    cout<<f[p][m]<<endl; return 0;
}

```

---

## 作者：灯芯糕 (赞：8)

## 斜率优化

### 感觉这道题题面不好讲，就自翻了一个新的，希望有助于大家理解其思路：

大致意思：小 $Van$ 的家里有 $N$ 座山（山呈直线分布，第 $i-1$ 座山到第 $i $ 座山距离为 $Di$ ）。小 $Van$ 中了 $M$ 粒种子，第 $i$ 粒种子在第 $Hi$ 座山上生长，并在 $Ti$ 时刻成熟，然后从 $Ti$ 时刻开始每过一时刻失去一点新鲜度。但小 $Van$ 只雇佣了 $P$ 位农民去采摘（没成熟不采）。假设到达某一座山时采摘的时间的时间忽略不计，小 $Van$ 和他的农民都住第一座山，员工步行速度为一米每秒，请问采下所有果实失去的新鲜度最小为多少？（农民可以从负时刻出发）

$(2 ≤ n ≤ 10^5, 1 ≤ m ≤ 10^5, 1 ≤ p ≤ 10^2,1 ≤ di< 10^4,1 ≤ hi ≤ n, 0 ≤ ti ≤ 10^9)$

------

------



## $solution:$

​        这道题首先不管斜率优化，我们先观察一下题目，（第 $i$ 粒种子在第 $Hi$ 座山上生长，并在 $Ti$ 时刻成熟），我们发现这两样东西似乎都关系到了果实可以何时被采摘（而且距离不涉及后面答案的运算），所以我们将这两个条件合并，从第一座山到第 $i $ 座山的路程可以预处理出来，而这时只要用$Ti-SumD_{Hi}$ 即可相当于每粒种子都种在第一座山上了（只不过生长期变了）。

​        这时我们发现题目被简化了：小 $Van $ 种了m粒种子，第 $i$ 粒种子将在$Ti-SumD_{Hi}$时刻成熟，小 $Van  $ 只有 $P$ 次采摘机会，他采下所有果实失去的新鲜度最小为多少？        这时我们又发现生长期短的种子一定先被采掉，于是我们按时间（ $T[i]=t[i]-SumD_{Hi}$ ）排个序（为了方便，我们还要求出其前缀和 $S[i]$ ），然后便不难设出状态了！

设 $F[i][j]$ 表示用了 $i$ 次采摘机会收获了前 $j$ 种果实损失的最小新鲜度，这样我们假设第 $i$ 次采的是第 $k+1$ 到 第 $j$枚果实，因为我们已经按照生长时间拍了序，所以这 $j-k$ 枚果实一定都是在第 $j$ 枚果实成熟的那一刻采摘的，于是 $f[i][j]=f[i-1][k]+(j-k)*T[j]-(S[j]-S[k])$ 于是我们枚举所有可行 $k$ 即可完成转移： 

### $f[i][j]=min^{<j}_{k=0}(f[i-1][k]+(j-k)*T[j]-(S[j]-S[k])) $

但是看了一下数据，我们发现复杂度有点不对，于是我们考虑优化：先把与k无关的项提出来：

### $f[i][j]=[min^{<j}_{k=0}(f[i-1][k]-k*T[j]+S[k]) ]+j*T[j]-S[j]$

然后我们发现在min函数中有一个和 $k$ 与 $j$ 都有关的数，而且k是单调递增的于是我们便想到用斜率优化：将等式左边只留与k有关的项，等式右边留与j有关的项。

### $f[i-1][k]-S[k]=k*T[j]+f[i][j]-j*T[j]+S[j]$

而这就是一个以k为自变量，$f[i-1][k]-S[k]$ 为因变量的函数，我们建立对应的直角坐标系，上式即为以 $T[j]$ 为斜率，$f[i][j]-j*T[j]+S[j]$ 为截距的直线（ $j*T[j]+S[j]$ 为定值）。所以我们要让截距最小即可，于是我们维护一个下凸壳。实现：我们建立一个数组 $g[i]=f[i-1][k]-S[k]$ （其实就是纵坐标），然后我们维护一个单调队列 $q[]$ ，队列里相邻的两个元素 $i$ 和 $j$ 应满足 $i<j$  并且 $\frac{g[q[j]]-g[q[i]]}{q[j]-q[i]}$ 要单调递增。这样我们在枚举 $j$ 的时候就会将对应的斜率从后面加进去，而提取出来的时候只需要拿当前的斜率（就是枚举的j）从最前面开始比较，直到比队列里的下一个斜率小，这是队头即为最优选择。

复杂度： $O(p*m)$ 



------

------



## $code:$



```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
 
#define ll long long
#define rg register int
 
using namespace std;
 
int n,m,p;
ll d[100005]; //距离
ll t[100005]; //时间
ll s[100005]; //时间前缀和
ll g[100005]; //f[i-1][k]+s[k]
ll q[100005]; //斜率单调队列
ll f[101][100005]; //斜率优化DP
 
inline int qr(){
    register char ch; register bool sign=0; rg res=0;
    while(!isdigit(ch=getchar())) if(ch=='-')sign=1;
    while(isdigit(ch)) res=res*10+(ch^48),ch=getchar();
    return sign?-res:res;
}
 
int main(){
    //freopen("in.in","r",stdin);
    //freopen("out.out","w",stdout);
    n=qr(); m=qr(); p=qr();
    for(rg i=2;i<=n;++i) d[i]=d[i-1]+qr(); //从第一座山到这座山的距离
    for(rg i=1;i<=m;++i){
        rg x=qr(),y=qr();
        t[i]=y-d[x];
    }//每一只猫的可以被接走的时间=第一座山到它所在的那座山的距离-它玩耍的时间
    sort(t+1,t+m+1); //把这些猫按可以被接走的时间的从小到大的顺序排序
    for(rg i=1;i<=m;++i) s[i]=s[i-1]+t[i]; //时间的前缀和
    for(rg i=1;i<=m;++i) f[0][i]=(ll)1e18;
    for(rg i=1;i<=p;++i){ rg l=1,r=0; //斜率单调队列初始化
        for(rg j=1;j<=m;++j) g[j]=f[i-1][j]+s[j]; //f[i-1][k]+s[k]的预处理
        for(rg j=1;j<=m;++j){ q[++r]=j-1;
            while(l<r&&g[q[l+1]]-g[q[l]]<=t[j]*(q[l+1]-q[l]))++l;
            f[i][j]=min(f[i-1][j],g[q[l]]+(j-q[l])*t[j]-s[j]);
            if(g[j]>=big)continue;
            while(l<r&&((g[q[r]]-g[q[r-1]])*(j-q[r]))>=((g[j]-g[q[r]])*(q[r]-q[r-1])))--r;
        }
    }cout<<f[p][m]<<endl;//注意codeforces需要用cout输出
    return 0;
}
```



---

## 作者：徐致远 (赞：6)


喵喵喵，斜率优化带猫猫早早回家。

[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/05/14/%E3%80%8CCF311B%E3%80%8DCats-Transport%20-Solution/)

### 题解

首先定义：
$$
dist[i]=\sum_{j=1}^{i}{d[j]}
$$

$$
A[i]=T[i]-dist[H[i]]
$$

$$
S[i]=\sum_{j=1}^{i}{A[j]}
$$

其中要先对A数组从小到大排序再计算前缀和。这样每个饲养员带走的必定为连续的几只猫。

定义$F[i][j]$表示前$i$个饲养员带走了前$j$只猫时的最小等待时间之和。转移方程为：

$$
F[i][j]=min(F[i-1][k]+A[j]*(j-k)-(S[j]-S[k]));
$$

但是直接这样转移的话复杂度太高，考虑斜率优化。可以把转移方程写成直线的形式：

$$
F[i-1][k]+S[k]=A[j]*k+F[i][j]-A[j]*j+S[j]
$$

这样就可以把$F[i-1][k]+S[k]$看作纵坐标，$k$看作横坐标，$A[j]$看成斜率。然后用单调队列维护一个斜率递增的下凸壳就行了。

### 代码

挺短的QwQ。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100005;const LL inf=0x3F3F3F3F3F3F3F3Fll;
int n,m,P,H[maxn],D[maxn],T[maxn],A[maxn],que[maxn],hed,til;LL S[maxn],F[105][maxn];
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main()
{
	n=read();m=read();P=read();
	for(int i=2;i<=n;i++) D[i]=D[i-1]+read();
	for(int i=1;i<=m;i++)
	{
		H[i]=read();
		T[i]=read();
		A[i]=T[i]-D[H[i]];
	}
	sort(A+1,A+1+m);
	for(int i=1;i<=m;i++) S[i]=S[i-1]+A[i];
	for(int i=1;i<=m;i++) F[0][i]=inf;
	for(int i=1;i<=P;i++)
	{
		hed=til=1;que[1]=0;
		for(int j=1;j<=m;j++)
		{
			while(hed>til&&(F[i-1][que[til+1]]+S[que[til+1]]-F[i-1][que[til]]-S[que[til]])<=(LL)A[j]*(que[til+1]-que[til])) til++;
			F[i][j]=F[i-1][que[til]]+(LL)A[j]*(j-que[til])-(S[j]-S[que[til]]);
			while(hed>til&&(F[i-1][j]+S[j]-F[i-1][que[hed]]-S[que[hed]])*(que[hed]-que[hed-1])<=(F[i-1][que[hed]]+S[que[hed]]-F[i-1][que[hed-1]]-S[que[hed-1]])*(j-que[hed])) hed--;
			que[++hed]=j;
		}
	}
	printf("%lld\n",F[P][m]);
	return 0;
}
```



---

## 作者：xukuan (赞：4)

动态规划之斜率优化

### 声明

有参考[https://blog.csdn.net/hjf1201/article/details/78779660](https://blog.csdn.net/hjf1201/article/details/78779660)

文章拉到最后就是题解

### 预处理

$a_i=t_i-d_{h_i}$，a数组表示即想要恰好接上这只猫，管理员的出发时间。那么，这只猫的等待时间即为管理员出发时间与这个值的差。对a数组进行排序，这样每个管理员接走的猫一定是连续的一段。

### 状态转移方程

让$f_{i,j}$表示前$i$个铲屎官接走前$j$只猫的最少总等待时间。 

状态转移方程：$f_{i,j}=max_{k=0}^{j-1} f_{i-1,k}+a_j*(j-k)-\sum _{l=k+1}^{j-1} a_l$

这样的时间复杂度时$O(m^2*p)$的，显然会TLE的一塌糊涂

### 斜率优化

那么我们需要优化

对状态转移方程进行改写：

定义$sum_i=\sum_{j=1}^i a_j$

$f_{i,j}=f_{i-1,k}+a_j*(j-k)-(sum_j-sum_k)$

$f_{i-1,k}-(sum_j-sum_k)=a_j*(j-k)+f_{i,j}$

还原：

$y=f_{i-1,k}-(sum_j-sum_k)$

$kx=a_j*(j-k)$

$b=f_{i,j}$

得到$y=kx+b$

关于斜率优化成立的证明（**k1比k2优的满足条件**）：

$f_{i-1,k2}+a_j*(j-k2)-(sum_j-sum_{k2}) \leq f_{i-1,k1}+a_j*(j-k1)-(sum_j-sum_{k1})$

记$slope(i,j)=f_{i-1,j}+sum_j$

化简得$\frac{slope(k2)-slope(k1)}{k2-k1}≤a_j$

好了，接下来把这个东西丢进一个单调队列，维护即可

## 代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=100010,M=100010,P=110,INF=1ll<<60;
ll n,m,p,d[N],a[M],sum[M],f[P][M];
deque<ll> q;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline ll slope(ll i,ll j){
	return f[i-1][j]+sum[j];
}

int main(){
	n=read(); m=read(); p=read();
	for(ll i=2; i<=n; i++) d[i]=d[i-1]+read();
	for(ll i=1; i<=m; i++){
		ll h=read(),t=read();
		a[i]=t-d[h];
	}
	sort(a+1,a+1+m);
	for(ll i=1; i<=m; i++) sum[i]=sum[i-1]+a[i];
	for(ll i=1; i<=m; i++) f[0][i]=INF;
	for(ll i=1; i<=p; i++){
		while(!q.empty()) q.pop_front();
		for(ll j=0; j<=m; j++){
			while(q.size()>1&&slope(i,q[1])-slope(i,q[0])<=a[j]*(q[1]-q[0])) q.pop_front();
			if(!q.empty()) f[i][j]=slope(i,q[0])+a[j]*(j-q[0])-sum[j];
			while(q.size()>1&&(slope(i,j)-slope(i,q[q.size()-1]))*(q[q.size()-1]-q[q.size()-2])<=(slope(i,q[q.size()-1])-slope(i,q[q.size()-2]))*(j-q[q.size()-1])) q.pop_back();
			q.push_back(j);
		}
	}
	cout<<f[p][m]<<endl;
	return 0;
}
```

---

## 作者：米奇 (赞：3)

# 算法:斜率优化动态规划

首先，应该可以想到**贪心**

设$d[i]$为第1座山到第$i$座山的距离
$d[i]=d[i-1]+dis(i-1,i)$

设$a[i]$为接到第$i$只猫的最早出发时间及只有在$a[i]$及以后时间才可以接第$i$只猫
$a[i]=t[i]-d[i]$

我们可以把a数组**从小到大**排序,根据贪心策略,每个人肯定接走连续的一段猫(**重点**)

然后,我们就能写出$O(PM^2)$的DP了
转移方程为
$f[i][j]=min{f[i-1][k]+a[j]*(j-k)-(s[j]-s[k])}$
其中的$s[i]=s[i-1]+a[i]$

最后我们把$i$看作定量,$j$为状态变量,$k$为决策变量。
方程中的乘积项$a[j]*k$使用斜率优化

移项得$f[i-1][k]+s[k]=a[j]*k+f[i][j]-a[j]*j+s[j]$

一次函数:$y=kx+b$

在这里$y=f[i-1][k]+s[k],k=a[j],x=k,b=f[i][j]-a[j]*j+s[j]$

$f[i][j]$取最小值，及$b$要最小，所以维护一个下凸壳

其他就是斜率优化的模板了:
如果队首的斜率小于$k$就弹出，
最优解为队首，
如果加入的值不构成下凸壳，就队尾弹出

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//哈哈,c++就是好 
const int N=200005;
int l,r,n,m,p,x,y,a[N],d[N],q[N],g[N],s[N],f[105][N];
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	for(int i=2;i<=n;i++)
	{
		scanf("%lld",&x);
		d[i]=d[i-1]+x;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		a[i]=y-d[x];
	}
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++)s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=p;i++)//枚举定值i
	{
		for(int j=1;j<=m;j++)g[j]=f[i-1][j]+s[j];//y轴
		l=r=1;q[1]=0;
		for(int j=1;j<=m;j++)
		{
			while(l<r&&(g[q[l+1]]-g[q[l]])<=a[j]*(q[l+1]-q[l]))l++;
            //如果队首的斜率小于$k$就弹出
			f[i][j]=min(f[i-1][j],g[q[l]]+a[j]*j-s[j]-a[j]*q[l]);//最优解为队首	
            if(g[j]>=0x3f3f3f3f3f3f3f3fll)continue;
			while(l<r&&(g[q[r]]-g[q[r-1]])*(j-q[r])>=
			(g[j]-g[q[r]])*(q[r]-q[r-1]))r--;//如果加入的值不构成下凸壳，就队尾弹出
			q[++r]=j;
		}
	}
	cout<<f[p][m];
}
```

---

## 作者：Object_ (赞：2)

**易错点：**
- 笔者由于没有进行数据初始化（排序以及数据填充）和状态转移中的一个字母r写成了l而调试了近一个小时.

------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll INF=0x3f3f3f3f3f3f3f3f;
const int MAXN=1e5+10,MAXP=110;
ll f[MAXP][MAXN],sumD[MAXN];
ll A[MAXN],sumA[MAXN];
int q[MAXN],l,r;
int main(){
	int n,m,p;
	scanf("%d%d%d",&n,&m,&p);
	for(int i=2;i<=n;i++){
		int d;
		scanf("%d",&d);
		sumD[i]=sumD[i-1]+d;
	}
	for(int i=1;i<=m;i++){
		int h,t;
		scanf("%d%d",&h,&t);
		A[i]=t-sumD[h];
	}
	sort(A+1,A+m+1);
	for(int i=1;i<=m;i++)
		sumA[i]=sumA[i-1]+A[i];
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=p;i++){
		q[l=r=1]=0;
		for(int j=1;j<=m;j++){
			ll nowK=A[j];
			while(l<r&&f[i-1][q[l+1]]+sumA[q[l+1]]-f[i-1][q[l]]-sumA[q[l]]<nowK*(q[l+1]-q[l]))l++;
			f[i][j]=f[i-1][q[l]]+sumA[q[l]]-q[l]*A[j]+j*A[j]-sumA[j];
			while(l<r&&(f[i-1][q[r]]+sumA[q[r]]-f[i-1][q[r-1]]-sumA[q[r-1]])*(j-q[r])
						>(f[i-1][j]+sumA[j]-f[i-1][q[r]]-sumA[q[r]])*(q[r]-q[r-1]))r--;
			q[++r]=j;
		}
	}
	printf("%lld\n",f[p][m]);
	return 0;
}
```

---

