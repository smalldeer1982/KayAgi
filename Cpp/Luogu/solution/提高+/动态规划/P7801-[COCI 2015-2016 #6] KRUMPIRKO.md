# [COCI 2015/2016 #6] KRUMPIRKO

## 题目描述

$\text{Mr. Potato}$ 开了两家新店卖土豆。他买了 $N$ 袋土豆，其中第 $i$ 袋价值为 $c_i$，袋里有 $a_i$ 个土豆。他打算把这 $N$ 袋土豆整袋整袋地分在两个店里。

在每家店中，土豆的平均价格等于这家店里**所有袋的土豆的总价比上土豆的个数**。（注意是个数而不是袋数！）

设 $P_1$ 为第一家店的土豆平均价格，$P_2$ 为第二家店的土豆平均价格。$\text{Mr. Potato}$ 希望在至少有一家店里土豆袋数**正好等于 $L$ 袋**的情况下，最小化 $P_1\times P_2$ 的值。

## 说明/提示

**【数据范围】**

对于 $30\%$ 的数据，$2\le N\le 20$。

对于 $100\%$ 的数据，$2\le N\le 100$，$1\le L< N$，$1\le a_i\le 100$，$1\le c_i\le 10^6$，$\sum\limits_{i=1}^{N} a_i\le 500$。

**【题目来源】**

**题目译自 [COCI 2015-2016](https://hsin.hr/coci/archive/2015_2016/) [CONTEST #6](https://hsin.hr/coci/archive/2015_2016/contest6_tasks.pdf) T5 KRUMPIRKO**。

**本题分值按 COCI 原题设置，满分 $140$**。

## 样例 #1

### 输入

```
3 1
3 2 1
1 2 3```

### 输出

```
0.556```

## 样例 #2

### 输入

```
3 2
2 2 2
3 3 3```

### 输出

```
2.250```

# 题解

## 作者：ybe2007 (赞：12)

一开始拿到题，除了爆搜肯定是没有什么思路的。于是我们考虑先推一下式子，看看能否通过适当的转化用高效的算法求解。

题目要求 ${(P_1 \times P_2)}_{\min}$，那么我们考虑将结果用另一种表现形式呈现。

$P_1 \times P_2= \dfrac{x}{y} \times \dfrac{\sum{c_i}-x}{\sum{a_i}-y}=\dfrac{x\times \sum{c_i}-x^2}{y\times \sum{a_i}-y^2}$，其中 $x$ 表示选取的土豆总价值，$y$ 表示选取的土豆总个数（对于一家店而言）。

观察到 $n,\sum{a_i}$ 均较小，那么考虑动态规划，开一个三维的 $\text{dp}$ 数组 $f_{i,j,k}$ 表示前 $i$ 袋土豆，选择 $j$ 袋，选取土豆总个数为 $k$ 时的情况。题目要求最小值，但是发现转移过程中似乎直接记录 ${(x\times sumc-x^2)}_{\min}$ 是不可行的。

但是观察到这个式子是一个二次函数的表达式，二次项系数为负，开口朝下，那么对于这样一个单峰函数很显然其最小值在 $x$ 取极值时取到，因此我们开 $f,g$ 两个数组，记录 $x$ 的最小值和最大值，那么转移方程与最后求解的答案就很明显了。具体可以看看代码。

当然第一维可以用滚动数组压掉，算是一个小优化吧。

答案的计算可能会溢出 $\text{int}$，中间记得强制转化一下。

```cpp
#include<bits/stdc++.h>
#define N 105
using namespace std;
int n,l;
int f[2][N][505],g[2][N][505];
int a[N],c[N],suma,sumc;
int main()
{
	scanf("%d%d",&n,&l);
	l=min(l,n-l);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),suma+=a[i];
	for(int i=1;i<=n;i++) scanf("%d",&c[i]),sumc+=c[i];
	memset(f,0x3f,sizeof(f)),memset(g,-0x3f,sizeof(g));
	f[0][0][0]=g[0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=min(i,l);j++)
		{
			for(int k=0;k<=suma;k++)
			{
				f[i&1][j][k]=f[i-1&1][j][k],g[i&1][j][k]=g[i-1&1][j][k];
				if(k>=a[i]&&j)
				{
					f[i&1][j][k]=min(f[i&1][j][k],f[i-1&1][j-1][k-a[i]]+c[i]);
					g[i&1][j][k]=max(g[i&1][j][k],g[i-1&1][j-1][k-a[i]]+c[i]);
				}
			}
		}
	}
	double ans=1e16;
	for(int i=1;i<=suma;i++)
	{
		if(f[n&1][l][i]<1e9) ans=min(ans,1ll*f[n&1][l][i]*(sumc-f[n&1][l][i])*1.0/(1ll*i*(suma-i)));
		if(g[n&1][l][i]>-1e9) ans=min(ans,1ll*g[n&1][l][i]*(sumc-g[n&1][l][i])*1.0/(1ll*i*(suma-i)));
	}
	printf("%.3lf\n",ans);
}
```

---

## 作者：DPair (赞：7)

先考虑答案是什么
$$
ans=\min\left\{{x((\sum c_i)-x)\over y((\sum a_i)-y)}\right\}
$$
$$
= {(\sum c_i)x-x^2\over (\sum a_i)y-y^2}
$$
注意到这道题 $\sum a_i$ 较小

考虑设 $f[i][j][k]$ 表示处理了前 $i$ 个数，选了 $j$ 袋，且个数为 $k$ 的最小的 $sx-x^2$

发现 $sx-x^2$ 这东西挺难维护，不过我们又发现这是一个单峰函数

因此维护一个最小的 $x$ 一个最大的 $x$ 即可，必然合法且最小值必在其中，最后枚举 $j$ 算答案就行了

转移方程是
$$
f[i][j][k]=\min/\max \{f[i-1][j][k], f[i-1][j-1][k-a[i]]+c[i]\}
$$
显然第一维就可以滚掉了，不滚掉应该也没关系

复杂度应该是 $O(nm\sum a_i)$ 的，能过

```cpp
const int MAXN = 105;
int n, m, a[MAXN], c[MAXN];

int f[MAXN][505], g[MAXN][505], s, t;

signed main(){
    read(n, m); read(a + 1, a + n + 1); read(c + 1, c + n + 1);
    memset(f, -1, sizeof(f)); memset(g, -1, sizeof(g)); rep(i, 1, n) s += a[i], t += c[i];
    f[0][0] = g[0][0] = 0; rep(i, 1, n) per(j, mn(m, i), 1) per(k, s - 1, a[i]) {
        if(~f[j - 1][k - a[i]]) {
            if(~f[j][k]) chmin(f[j][k], f[j - 1][k - a[i]] + c[i]), chmax(g[j][k], g[j - 1][k - a[i]] + c[i]);
            else f[j][k] = f[j - 1][k - a[i]] + c[i], g[j][k] = g[j - 1][k - a[i]] + c[i];
        }
    } double ans = 1e12; rep(i, 1, s - 1) if(~f[m][i]) chmin(ans, mn(1.0 * (t - f[m][i]) * f[m][i], 1.0 * (t - g[m][i]) * g[m][i]) / (1.0 * (s - i) * i));
    printf("%.3lf\n", ans);
}
```



---

## 作者：小杨小小杨 (赞：3)

### 闲话
模拟赛碰到的题，磕磕绊绊写了个把小时也是吐血了。

同学写了个模拟退火被我卡了哈哈哈。

### 思路

仔细说说我是怎么一步一步推出正解的吧，感觉有点像假算法引导正解。

最初的暴力算法必然是搜索，这里不过多赘述。

题目要求计算 $P1 \times P2$ 的最小值，将 $P1$ 和 $P2$ 分别用分式表示，能够发现两者的分母相加正好是所有 $a_i$ 的和，而两者的分母相加正好是 $c_i$ 的和。

考虑到直接计算 $P1$ 和 $P2$ 的乘积最小值较为困难，又联系到上面将 $P1$ 和 $P2$ 分别用分式表示，能两者的分母相加和分子相加都为已知的定值这一特点，观察数据范围发现 $a_i$ 总和很小，考虑分开枚举分母，由小学的数学经验得知当两个数和是定值的时候，其中一个取尽可能小，另一个取尽可能大，此时乘积最小。

所以考虑用背包维护对于每一个 $A$ 时最小的 $C$ ，然后枚举取最小即可。

接着加上要求必须要有一个店铺有 $L$ 袋这个要求，发现数据小，直接加一重循环暴力修改。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3;
struct Node{int a,c;}x[N];
int n,l,dp[N][N],mi[2][N][N],suma,sumc,t,h;
double mis;
signed main(){
	scanf("%lld%lld",&n,&l);
	for (int i=1;i<=n;i++) scanf("%lld",&x[i].a),suma+=x[i].a;
	for (int i=1;i<=n;i++) scanf("%lld",&x[i].c),sumc+=x[i].c;
	memset(dp,0x3f,sizeof(dp));
	int inf=dp[0][0];dp[0][0]=0;
	for (int k=1;k<=n;k++){
		for (int j=0;j<=suma;j++){
			h=-1;
			for (int i=1;i<=n;i++)
				if (j>=x[i].a&&mi[1-t][j-x[i].a][i]==0&&dp[k][j]>dp[k-1][j-x[i].a]+x[i].c) dp[k][j]=dp[k-1][j-x[i].a]+x[i].c,h=i;
			if (h==-1) continue;
			for (int i=1;i<=n;i++) mi[t][j][i]=mi[1-t][j-x[h].a][i];
			mi[t][j][h]=1;
		}
		t=1-t;for (int j=0;j<=suma;j++) for (int i=1;i<=n;i++) mi[t][j][i]=mi[1-t][j][i];
	}
	mis=1.0*1e12;
	for (int i=1;i<=suma;i++){
		if (dp[l][i]!=inf) mis=min(mis,(1.0*dp[l][i]*(sumc-dp[l][i])/(1.0*i*(suma-i))));
		if (dp[n-l][i]!=inf) mis=min(mis,(1.0*dp[n-l][i]*(sumc-dp[n-l][i])/(1.0*i*(suma-i))));
	}
	printf("%.3lf",mis);
	return 0;
}
```

---

## 作者：TempestMiku (赞：3)

## 前言

### [P7801](https://www.luogu.com.cn/problem/P7801)

随机跳题跳到这个题。然后看了一下是求 $P1\times P2$ 最小值，并且 $N\le 100$，于是我们直接拿出玄学神器：模拟退火。

## 思路

不会[模拟退火](https://blog.csdn.net/qq_53893431/article/details/126776594)的可以先去做一下
[P1337 平衡点 / 吊打XXX](https://www.luogu.com.cn/problem/P1337)。

当你学会了模拟退火之后，随便设计一个估价函数即对于一个排列求出 $P1\times P2$ 的最小值，然后退火随机交换序列前 $l$ 个数中的一个和 $(l+1) \sim n$ 中的一个数，并且求出能量，根据概率接受劣解，当快到时限的时候直接退出即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void WritE(int x){
        if(x<0) putchar('-'),x=-x;
        if(x>9) WritE(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        WritE(x);
        puts("");
    }
    inline void Write(int x){
        WritE(x);
        putchar(' ');
    }
}
using namespace Testify;
int n,l;
const int N=105;
int a[N],c[N];
int now[N];
mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
inline int radom(int l,int r){
    return rd()%(r-l+1)+l;
}
inline double energy(){
    double P1=0,P2=0;
    double Sum1=0,Sum2=0;
    for(register int i=1;i<=n;i++){
        if(i<=l){
            P1+=c[now[i]];
            Sum1+=a[now[i]];
        }
        else{
            P2+=c[now[i]];
            Sum2+=a[now[i]];
        }
    }
    return (P1/Sum1)*(P2/Sum2);
}
double ans;
inline void SA(){
    double T=3000;
    while(T>1e-15){
        int ra=radom(1,l);
        int rb=radom(l+1,n);
        swap(now[ra],now[rb]);
        double e=energy();
        double delta=e-ans;
        if(delta<0){
            ans=e;
        }
        else if(exp(-delta/T)*RAND_MAX<radom(0,RAND_MAX)){
            swap(now[ra],now[rb]);
        }
        T*=0.995;
    }
}
signed main(void){
    n=read(),l=read();
    for(register int i=1;i<=n;i++){
        a[i]=read();
        now[i]=i;
    }
    for(register int i=1;i<=n;i++){
        c[i]=read();
    }
    ans=energy();
    while((double)clock()/CLOCKS_PER_SEC<0.99){
        SA();
    }
    printf("%.3lf",ans);
    return 0;
}
```


---

## 作者：c_y_y (赞：2)

# [P7801 [COCI2015-2016#6] KRUMPIRKO 题解](https://www.luogu.com.cn/problem/P7801)

Upd on 2024/10/5：修改了一些笔误。

>~~如果一道题想不到任何可以解决的办法的话，那么它大概率会是 **dp**。~~

___
考虑 dp。

此时我们发现，如果我们真的用一个 $f$ 数组记录的就是答案的话，那么转移就很麻烦。因为**平均数不能单纯的相加减**！  

但是，题目中的数据范围有一个非常不正常的地方:

$$
\sum_{i = 1}^{n} a_{i} \le 500
$$
因此，大胆猜测**枚举分母，去 dp 分子的最值**。

而且，$N \le 100$，$a_{i} \le 100$，可以用三维的数组进行三维的转移，时间复杂度大概率是 $O(n^3)$ 的。

不妨令第一家选了 $L$ 袋。设 $f[i][j][k]$ 表示对于第一家而言，前 $i$ 袋选了 $j$ 袋土豆，获得了 $k$ 个土豆时价值的**最值**。此时我们不知道取价值的最大值还是最小值。

那么看看答案是什么。
$$
P_{1} \times P_{2} = \frac{x}{y} \times \frac{sum_c - x}{sum_a - y} = \frac{x \cdot (sum_c - x)}{y \cdot(sum_a - y)}
$$

其中，$sum_c = \sum c_i$，$sum_a = \sum a_i$，$x$ 为第一家选取的土豆的总价值，$y$ 为第一家选取的土豆数量。

由于我们枚举分母，故只用看分子的多项式。这是一个形如 $y=-x^2+sx$ 的二次函数。它的开口方向朝下。

我们的目标是求 $P_{1} \times P_{2}$ 的**最小值**，根据图像法，他的最小值一定取到**两侧**，也就是 $x_{min}$ 和 $x_{max}$！

因此，维护两个数组 $f$ 和 $g$ 分别取维护最大值和最小值，枚举时 $ans$ 取较小值即可。

___
似乎还有几个问题没有解决。

第一个问题是，状态转移方程是什么。  
这个类似于 01 背包，选择取与不取两个状态。具体见代码

还有一个问题是，空间只有 64MB，不能开三维数组！

这个也不难理解，第一维的转移只涉及到 $i$ 和 $i-1$ 两个状态，故可以像 01 背包通过倒序枚举砍掉第一维。空间就不会爆了。

记得开 long long，会爆 int。

### Code（要整治码风了）:
```
#include <bits/stdc++.h>
using namespace std;
const int N = 210, K = 510;
long long f[N][K], g[N][K], a[N], c[N];
int main() {
	int n, l;
	cin >> n >> l;
	long long suma = 0, sumc = 0;
	for(int i = 1; i <= n; i++) cin >> a[i], suma += a[i];
	for(int i = 1; i <= n; i++) cin >> c[i], sumc += c[i];
	memset(f,-0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	int inf = g[0][0];
	f[0][0] = g[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = min(i, l); j >= 0; j--)
			for(int k = suma; k >= a[i]; k--)
				if(j > 0){
					f[j][k] = max(f[j][k], f[j - 1][k - a[i]] + c[i]);
					g[j][k] = min(g[j][k], g[j - 1][k - a[i]] + c[i]);
				}
	double ans = 1e16+10;
	for(long long i = 1; i < suma; i++){
		if(f[l][i] > -inf) ans = min(ans, f[l][i] * (sumc - f[l][i]) * 1.0 / i / (suma - i));
		if(g[l][i] < inf) ans = min(ans, g[l][i] * (sumc - g[l][i]) * 1.0 / i / (suma - i));
	}
	printf("%.3lf", ans);
	return 0;
}
```

---

## 作者：rainygame (赞：2)

首先有一个店的土豆袋数为 $L$，那么另一个一定为 $N-L$。

令 $l=\min\{L,N-L\}$，即土豆袋数最小的那一组的数量。

考虑最后枚举土豆数量最小的那组的土豆数量 $i$，那么答案为：

$$
\min\limits_{i=1}^{\sum a-1}(\dfrac{f_{l,i}}{i}\times \dfrac{\sum c-f_{l,i}}{\sum a-i}) \ (i \ \text{可以被一些}\ a_j\ \text{凑出来})
$$

$f_{i,j}$ 表示选择了 $i$ 袋土豆共 $j$ 个土豆的最小总价。

为什么是最小呢？因为根据“和一定差大积小”的原理，$i$ 和 $\sum a-i$ 是固定的，分子就需要尽量地“差大”。我们钦定了 $l$ 那组是更小的，那么就需要 $f_{l,i}$ 最小才可以使得 $(\sum c-f_{l,i})-f_{l,i}$ 尽量大。

容易发现 $f$ 其实就是背包，然后就是板子了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 101

int n, l, suma, sumc;
int a[MAXN], c[MAXN];
int f[MAXN][501];
double ans(1e16);

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> l;
    l = min(l, n-l);
    for (int i(1); i<=n; ++i){
        cin >> a[i];
        suma += a[i];
    }
    for (int i(1); i<=n; ++i){
        cin >> c[i];
        sumc += c[i];
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i(1); i<=n; ++i){
        for (int j(suma); j>=a[i]; --j){
            for (int k(n); k>=1; --k) f[k][j] = min(f[k][j], f[k-1][j-a[i]]+c[i]);
        }
    }

    for (int i(1); i<suma; ++i){
        if (f[l][i] == 0x3f3f3f3f3f3f3f3f) continue;
        ans = min(ans, ((double)f[l][i]/i)*((double)(sumc-f[l][i])/(suma-i)));
    }

    printf("%.3lf", ans);

    return 0;
}

```


---

## 作者：chenwenmo (赞：1)

[P7801 [COCI 2015/2016 #6] KRUMPIRKO](https://www.luogu.com.cn/problem/P7801)

Tag：DP

考虑能不能直接 DP，发现不好计算。

发现答案是分数的形式，考虑 01分数规划，但分子分母并不是关于 $a_i$ 和 $c_i$ 的一次多项式，因此也不行。

首先这个题目的答案有两个未知数，不太好处理，我们把它变换为：
$$
\frac{s_1(c)\cdot(s(c)-s_1(c))}{s_1(a)\cdot(s(a)-s_1(a))}
$$

其中 $s_1$ 表示填入第一家商店的物品的某个属性之和，$s$ 表示总和。那么 $s$ 是常数，于是就只有一个未知量了。

现在还有一个问题，我们不能和平常一样，固定一些已经选出的物品，然后考虑新增的物品，因为这样取 $\min$ 转移的局部最优解，不代表全局最优。

这时候你会发现题目还有一个性质没用上：$\sum a_i\le 500$。

我们直接枚举 $s_1(a)$，因为它比较小。然后考虑 $s_1(a)$ 固定时，怎么取到最小答案：由于分母固定，那么要求分子尽量小，而我们发现分子是一个开口向下的二次函数，显然在 $s_1(c)$ 取到 $\min$ 或 $\max$ 时该函数取到最小。

于是现在问题就转换为：求选择 $L$ 个物品，使得它们的 $a_i$ 之和为 $s_1(a)$，并且 $c_i$ 之和最大或最小。

这个可以直接 DP，设 $f(i,j,k)$ 表示考虑前 $i$ 个物品，选了 $j$ 个，$a_i$ 之和为 $k$ 的最大 $c_i$ 之和，最小同理。然后空间可能会爆，用滚动数组转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using UI = unsigned int;
using ULL = unsigned long long;
using DB = double;
using LDB = long double;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
#define CP(x) complex<x>
#define fst first
#define snd second
#define popcnt(i) __builtin_popcount(i)

const int N = 1e2 + 5, V = 5e2 + 5;
const LL INF = 2e18;

int n, m;
LL suma, sumb, a[N], b[N], f[2][N][V], g[2][N][V];
// f: max, g: min

LDB val(LL sa, LL sb) {
	if (sb == INF || sb == -INF) return INF;
	return (DB)(sumb - sb) * sb / ((suma - sa) * sa);
}

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		suma += a[i];
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &b[i]);
		sumb += b[i];
	}
	int cur = 0;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= suma; j++) {
			f[0][i][j] = -INF;
			g[0][i][j] = INF;
		}
	}
	f[0][0][0] = g[0][0][0] = 0;
	for (int i = 1; i <= n; i++) {
		cur ^= 1;
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= suma; k++) {
				f[cur][j][k] = f[cur ^ 1][j][k];
				if (j && k >= a[i] && f[cur ^ 1][j - 1][k - a[i]] != -INF) {
					f[cur][j][k] = max(f[cur][j][k], f[cur ^ 1][j - 1][k - a[i]] + b[i]);
				}
				g[cur][j][k] = g[cur ^ 1][j][k];
				if (j && k >= a[i] && g[cur ^ 1][j - 1][k - a[i]] != INF) {
					g[cur][j][k] = min(g[cur][j][k], g[cur ^ 1][j - 1][k - a[i]] + b[i]);
				}
			}
		}
	}
	LDB ans = INF;
	for (int i = 0; i <= suma; i++) {
		ans = min({ans, val(i, f[cur][m][i]), val(i, g[cur][m][i])});
	}
	printf("%.3Lf\n", ans);
}

int main() {
	solve();
	return 0;
}
```

---

## 作者：Hanzelic (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/P7801)

~~自从模拟赛看到一位神拿模拟退火拿到最高分后就开始爱生模拟退火了。~~

这道题应该是模拟退火的裸题，我们只需要提前划分成 $1$ 到 $l$ 一组，剩下的 $l+1$ 到 $n$ 一组，剩下直接模拟退火就行了，交了几遍就过了。

### 代码
```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
#define M 155
using namespace std;
inline int read(){
	int f(1),x(0);char c=getchar();
	for(;c<48;c=getchar())if(c=='-')f=-1;
	for(;c>=48;c=getchar())x=(x<<3)+(x<<1)+c-'0';
	return f*x;
}
int n,m,l;
int a[M],c[M],a1[M],c1[M];
double al,cl,an,cn,ans;
mt19937 rd(random_device{}());
int radom(int l,int r){return rd()%(r-l+1)+l;}
double energy(){
	double sa=0,sc=0,ca=0,cs=0;
	for(int q=1;q<=l;q++){
		sa+=a1[q];
		sc+=c1[q];
	}
	for(int q=l+1;q<=n;q++){
		ca+=a1[q];
		cs+=c1[q];
	}
	return sa/sc*ca/cs;
}
inline void SA(){
	double T=3000;
	while(T>1e-15){
		int x=radom(1,l),y=radom(l+1,n);
		for(int q=1;q<=n;q++){
			a1[q]=a[q];
			c1[q]=c[q];
		}
		swap(a1[x],a1[y]);
		swap(c1[x],c1[y]);
		double e=energy();
		int delta=e-ans;
		if(delta<0){
			ans=e;
			swap(a[x],a[y]);
			swap(c[x],c[y]);
		}
		else if(exp(-delta/T)*RAND_MAX<radom(0,RAND_MAX)){
			swap(a[x],a[y]);
			swap(c[x],c[y]);
		}
		T*=0.995;
	}
}
signed main(){
	n=read(),l=read();
	for(int q=1;q<=n;q++){
		a[q]=read();
	}
	for(int q=1;q<=n;q++){
		c[q]=read();
	}
	for(int q=1;q<=l;q++){
		al+=a[q];
		cl+=c[q];
	}
	for(int q=l+1;q<=n;q++){
		an+=a[q];
		cn+=c[q];
	}
	ans=al/cl*an/cn;
	while((double)clock()/CLOCKS_PER_SEC<0.99){
		SA();
	}
	printf("%.3lf\n",ans);
	return 0;
}
```


---

## 作者：SuperCowHorse (赞：0)

> 终于有模拟赛能让我发挥的题了。

---

看到这个数据范围，$n\le100$，很容易想到模拟退火。

于是我们先把前 $L$ 袋土豆放在第一个商店里，每次退火时，在 $[1,L]$ 随机一个数 $x$，在 $[L+1,n]$ 随机一个数 $y$，交换 $x,y$。如果答案更优，则更新答案；如果不优，则以一定的概率接受当前情况。

好像就是模拟退火板子题，哎嘿~

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=105;
int n,L,suma[2],sumc[2];struct node{int c,a;}a[maxn];
inline double Calc(){
	ll res=1ll*sumc[0]*1ll*sumc[1];
	ll sre=1ll*suma[0]*1ll*suma[1];
	return res*1.0/sre;
}
double ans;
const double eps=1e-10;
const double dl=0.99707;
inline int rnd(int l,int r){//随机
	return rand()%(r-l+1)+l;
}
inline void SA(){//模拟退火
	double t=2009;
	while(t>eps){
		int x=rnd(1,L),y=rnd(L+1,n);
		suma[0]+=a[y].a-a[x].a;sumc[0]+=a[y].c-a[x].c;
		suma[1]+=a[x].a-a[y].a;sumc[1]+=a[x].c-a[y].c;
		double now=Calc();double del=now-ans;
		if(del<0){
			ans=now;
			swap(a[x],a[y]);
		}
		else if(double(exp(-del/t)*1.0*RAND_MAX)>rand()){
			swap(a[x],a[y]);
		}
		else{
			suma[0]-=a[y].a-a[x].a;sumc[0]-=a[y].c-a[x].c;
			suma[1]-=a[x].a-a[y].a;sumc[1]-=a[x].c-a[y].c;
		}
		t*=dl;
	}
}
signed main(){
// 	freopen("krumpirko.in","r",stdin);
// 	freopen("krumpirko.out","w",stdout);
	srand(time(0));
	scanf("%d%d",&n,&L);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].a);
		suma[i>L]+=a[i].a;//小技巧：P1*P2=sumc[0]*sumc[1]/suma[0]/suma[1]，这样可以 O(1) 计算贡献
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].c);
		sumc[i>L]+=a[i].c;
	}
	ans=Calc();
	while(double(clock())<double(CLOCKS_PER_SEC)*0.97) SA();//卡时
	printf("%.3lf",ans);
	return 0;
}
```

---

希望 NOIP 有这种题。

NOIP2024 rp++。

---

## 作者：forever_nope (赞：0)

设：

$$
A=\sum_{i=1}^na_i
$$

$$
C=\sum_{i=1}^nc_i
$$

设 $F(x,y)$ 表示买了 $x$ 袋共 $y$ 个土豆的最小花费。

我们第一个商店买 $L$ 袋，枚举土豆数量，则答案可以表示为：

$$
\min_{i=1}^{A-1}\left(\dfrac{F(l,i)}{i}\times\dfrac{C-F(l,i)}{A-i}\right)
$$

注意到 $A\le500$ 可以直接枚举，因此问题转化为求 $F(x,y)$。

注意到这个形式很背包，于是考虑加上状态。

设 $G(i,x,y)$ 表示前 $i$ 袋土豆，买 $x$ 袋 $y$ 个土豆的最小花费：

$$
G(i,x,y)=\min\{G(i-1,x,y),G(i-1,x-1,y-a_i)+c_i\}
$$

这样做时间复杂度是 $\mathcal O(N^2A)$ 可以接受。

空间上，滚动数组优化可以加上，但是没必要可以不加，下面代码加了。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"

using ll = long long;

#define int ll

constexpr int N = 110;
constexpr int V = 510;

int n, l;
int a[N], A;
int c[N], C;

int G[N][V];

void Main() {
	cin >> n >> l;
	l = min(l, n-l);
	for (int i = 1; i <= n; ++i)
		cin >> a[i], A += a[i];
	for (int i = 1; i <= n; ++i)
		cin >> c[i], C += c[i];
	memset(G, 0x3f, sizeof G);
	G[0][0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = n; j >= 1; --j)
			for (int k = A; k >= a[i]; --k)
				G[j][k] = min(G[j][k], G[j - 1][k - a[i]] + c[i]);
	auto F = [] (int i, int j) {
		return G[i][j];
	};
	double ans = 1e18;
	for (int i = 1; i < A; ++i)
		if (F(l, i) != 0x3f3f3f3f3f3f3f3f)
			ans = min(ans, (F(l, i) * 1.0 / i) * ((C - F(l, i)) * 1.0 / (A - i)));
	printf("%.3lf\n", ans);
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	return Main(), 0;
}


```

---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P7801)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18379569)。

## 题意简述

给出长度为 $n$ 的序列 $c$ 和 $a$，选出一个大小为 $l$ 下标集合 $\mathcal{T}$，使 $i \in \mathcal{T}$ 的 $c_i$ 之和比上 $a_i$ 之和，乘上 $i \not \in \mathcal{T}$ 的 $c_i$ 之和比上 $a_i$ 之和最小。形式化地说，求：

$$
\large \min _ {\mathcal{T} \subseteq \{ i \} _ {i = 1} ^ {n} \land |\mathcal{T}| = l} \cfrac{\sum \limits _ {i \in \mathcal{T}} c_i}{\sum \limits _ {i \in \mathcal{T}} a_i} \cfrac{\sum \limits _ {i \not \in \mathcal{T}} c_i}{\sum \limits _ {i \not \in \mathcal{T}} a_i} 
$$

$1 \leq l \lt n \leq 100$，$1 \leq a_i \leq 100$，$1 \leq c_i \leq 10^6$，$\sum a_i \leq 500$。

## 题目分析

发现要用背包，具体地，我们 DP 当前选到第几个，$\mathcal{T}$ 中已经有了几个元素的某些信息。如果直接记录 $\cfrac{\sum c_i}{\sum a_i}$ 并不正确，也不能转移。发现 $a_i$ 之和很小，题目再暗示我们可以枚举它，把它记录到状态里。那么我们 DP 背包的价值就是有关 $\sum c_i$ 的信息。

应该找一找性质，推一推式子。不妨记 $A = \sum \limits _ {i = 1} ^ n a _ i$，$C = \sum \limits _ {i = 1} ^ n c _ i$，选出的 $c_i$，$a_i$ 之和分别为 $C'$，$A'$。我们答案就是 $\min \cfrac{C'(C - C')}{A'(A - A')}$。对于一个枚举了的 $A'$，分母显然是定值，我们求的就是分子 $C'(C - C')$ 的最小值。发现，这是关于 $C'$ 的二次函数，我们希望求 $\min f(C') = -C'^2 + CC'$。这个函数开口朝下，~~没有最小值~~，取到最小值当然就在最小的 $C'$ 或者最大的 $C'$ 时取到。这样我们 DP 记的值就是选出的 $C'$ 的最大 / 最小值。为了方便，我们可以钦定我们求的这部分 $C' < C - C'$，即钦定 $l < n - l$，这样只用记录最小值。

总结一下，我们可以记 $f_{i, j, k}$ 表示考虑前 $i$ 个，选出了 $j$ 个，$A' = k$ 时 $C'$ 的最小值。有两种转移：

1. 不放到 $\mathcal{T}$ 中。
    易得 $f_{i, j, k} = \min \{ f_{i, j, k}, f_{i - 1, j, k} \}$。
1. 放到 $\mathcal{T}$ 中。
    易得 $f_{i, j, k} = \min\{ f_{i, j, k},  f{i - 1, j - 1, k - a_i} \}$。

边界显然是 $f_{0, 0, 0} = 0$，其他 $f_{i, j, k} = \infty$。

答案就是 $\min \cfrac{f_{n, l, A'}(C - f_{n, l, A'})}{A'(A - A')}$。

时空复杂度：$\Theta(nlA)$。滚一滚，空间优化到 $\Theta(nA)$。

## 代码

不小心跑到[最优解](https://www.luogu.com.cn/record/174669637)。

```cpp
#include <cstdio>
#include <cstring>

const int N = 105;

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int n, m, A[N], C[N];
int dp[N][505];

long long son = 1, mon = 0;
inline void check(long long a, long long b) {
    if (a * mon < b * son) son = a, mon = b;
}

int sum1, sum2;

signed main() {
    scanf("%d%d", &n, &m), m = min(m, n - m);
    for (int i = 1; i <= n; ++i) scanf("%d", &A[i]), sum1 += A[i];
    for (int i = 1; i <= n; ++i) scanf("%d", &C[i]), sum2 += C[i];
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int i = 1, s = 0; i <= n; ++i) {
        s += A[i];
        for (int t = min(m, i), ted = max(1, m - (n - i)); t >= ted; --t)
        for (int j = A[i]; j <= s; ++j)
            dp[t][j] = min(dp[t][j], dp[t - 1][j - A[i]] + C[i]);
    }
    for (int k = 1; k <= sum1 - 1; ++k) {
        if (dp[m][k] == 0x3f3f3f3f) continue;
        check(1ll * dp[m][k] * (sum2 - dp[m][k]), 1ll * k * (sum1 - k));
    }
    printf("%.3lf", 1. * son / mon);
    return 0;
}
```

## 后记 & 反思

一道很水的背包题，从设计状态到思考记录什么的过程，再到最后的转移方程都十分自然。但是考场上不知道为什么没去推只用记录 $C'$ 的最值，而是用了 `bitset` 瞎搞。

---

