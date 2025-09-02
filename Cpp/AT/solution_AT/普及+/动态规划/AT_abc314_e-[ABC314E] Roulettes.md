# [ABC314E] Roulettes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc314/tasks/abc314_e

$ N $ 台のルーレットがあります。 $ i $ 番目 $ (1\leq\ i\leq\ N) $ のルーレットには $ P\ _\ i $ 個の整数 $ S\ _\ {i,1},S\ _\ {i,2},\ldots,S\ _\ {i,P\ _\ i} $ が書かれており、$ C\ _\ i $ 円支払うことで $ 1 $ 回プレイできます。 $ i $ 番目のルーレットを $ 1 $ 回プレイすると、$ 1 $ 以上 $ P\ _\ i $ 以下の整数 $ j $ が一様ランダムに選ばれ、$ S\ _\ {i,j} $ ポイントを得ることができます。

ルーレットで得られるポイントは、過去の結果と独立に決まります。

高橋くんは、ポイントを $ M $ ポイント以上獲得したいです。 高橋くんは、$ M $ ポイント以上獲得するまでに支払う金額をなるべく小さくするように行動します。 ただし、高橋くんはルーレットをプレイするたびこれまでのルーレットの結果を見て次にプレイするルーレットを選ぶことができます。

高橋くんがポイントを $ M $ ポイント以上獲得するまでに支払う金額の期待値を求めてください。

より厳密な定義より厳密には、次のようになります。 高橋くんがルーレットを選ぶ戦略を決めるごとに、その戦略で $ M $ ポイント以上獲得するまでに支払う金額の期待値 $ E $ が次のように定義されます。

- 自然数 $ X $ に対して、その戦略に従って高橋くんが $ M $ ポイント以上獲得するか、ルーレットを $ X $ 回プレイするまでに支払う金額の期待値を $ f(X) $ とする。$ E=\displaystyle\lim\ _\ {X\to+\infty}f(X) $ とする。

この問題の条件のもとで、高橋くんがどのような戦略をとっても $ \displaystyle\lim\ _\ {X\to+\infty}f(X) $ が有限の値になることが証明できます。 高橋くんが $ E $ を最小にするような戦略をとったときの $ E $ の値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 100 $
- $ 1\leq\ M\leq\ 100 $
- $ 1\leq\ C\ _\ i\leq\ 10\ ^\ 4\ (1\leq\ i\leq\ N) $
- $ 1\leq\ P\ _\ i\leq\ 100\ (1\leq\ i\leq\ N) $
- $ 0\leq\ S\ _\ {i,j}\leq\ M\ (1\leq\ i\leq\ N,1\leq\ j\leq\ P\ _\ i) $
- $ \displaystyle\sum\ _\ {j=1}^{P\ _\ i}S\ _\ {i,j}\gt0\ (1\leq\ i\leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

例えば、高橋くんはルーレットを次のようにプレイすることができます。 - $ 50 $ 円を支払ってルーレット $ 2 $ をプレイする。$ S\ _\ {2,4}=8 $ ポイントを得る。 - $ 50 $ 円を支払ってルーレット $ 2 $ をプレイする。$ S\ _\ {2,1}=1 $ ポイントを得る。 - $ 100 $ 円を支払ってルーレット $ 1 $ をプレイする。$ S\ _\ {1,1}=5 $ ポイントを得る。得たポイントの合計が $ 8+1+5\geq14 $ ポイントとなったため、終了する。 この例では、$ 14 $ ポイントを得るまでに $ 200 $ 円を支払っています。 出力と真の値の相対誤差もしくは絶対誤差が $ 10\ ^\ {-5} $ 以下のとき正答と判定されるため、`215.9112` や `215.9155` などと出力しても正解になります。

### Sample Explanation 2

$ 100 $ ポイントが出るまでルーレット $ 2 $ を回し続けるのが最適です。

## 样例 #1

### 输入

```
3 14
100 2 5 9
50 4 1 2 4 8
70 5 2 4 2 8 8```

### 输出

```
215.913355350494384765625```

## 样例 #2

### 输入

```
2 100
1 2 1 2
10 6 0 0 0 0 0 100```

### 输出

```
60```

## 样例 #3

### 输入

```
20 90
3252 9 0 4 2 7 3 2 3 2 4
2147 1 1
4033 8 0 4 1 7 5 2 5 0
3795 6 6 6 2 3 2 2
3941 7 2 4 4 7 2 0 5
2815 6 2 1 0 5 2 2
3020 2 3 6
3858 9 4 2 7 3 0 4 4 6 5
4533 10 3 6 4 0 6 4 4 2 7 7
4198 8 6 7 0 6 3 6 5 6
3739 8 2 7 1 5 1 4 4 7
2465 4 1 4 0 1
4418 9 7 6 2 4 6 1 5 0 7
5450 12 0 4 4 7 7 4 4 5 4 5 3 7
4196 9 1 6 5 5 7 2 3 6 3
4776 9 2 2 7 3 6 6 1 6 6
2286 3 3 5 6
3152 3 4 1 5
3509 7 0 6 7 0 1 0 3
2913 6 0 1 5 0 5 6```

### 输出

```
45037.072314895291126319493887599716```

# 题解

## 作者：AC_love (赞：23)

更新：感谢 [lnwhl](https://www.luogu.com.cn/user/451328) 指出本文一处笔误，我复制粘贴的时候把分子分母写反了没有注意到（捂脸）

--------

题意：有 $N$ 个转盘，第 $i$ 个转盘上有 $P_i$ 个数 $S_{i,1}$ 到 $S_{i,P_i}$，每玩一次转盘会从中随机选取一个数作为这次的得分，每玩一次这个转盘花费 $C_i$ 元。

求总得分为 $M$ 时，花费钱数的期望。

--------

赛时做了一个小时只写出一个错误的贪心，我们不妨从这个失败的贪心出发，聊聊期望类题目的正解做法。

--------

错误思路：

我们不妨考虑如下的贪心策略：

计算出每个转盘上所有数的平均值作为玩一次这个转盘得数的期望，再除以每个转盘玩一次的价格，找到其中的最大值，用 $M$ 除以这个最大值得到答案。

部分代码：

```cpp
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> c[i] >> p[i];
		for(int j = 1; j <= p[i]; j = j + 1)
		{
			cin >> s;
			if(s > m)
				s = m;	// 赛时写的一个毫无卵用的优化
			sum[i] += s;
		}
		ave[i] = sum[i] / double(p[i]);
		ave[i] /= c[i];
	}
	sort(ave + 1, ave + 1 + n, cmp);
	cout << m / ave[1];
```

这应该算是一个很多人都可能会考虑到的贪心策略了，但是其正确性究竟怎样呢？

考虑这样的数据：

```
N = 2
M = 100
第一个轮盘玩一次 100 元
0 0 0 0 100
第二个轮盘玩一次 100 元
0 0 0 0 0 0 0 1000
```

可以计算出，下面的轮盘玩一次平均获得 $125$ 元，而上面的轮盘每玩一次平均仅获得 $20$ 元，但是显然更优解是选择玩上面的轮盘。

为什么？

记不记得我们初中时候学过：平均值很多时候不能反映一组数据的真实情况，因为其很容易被极端值影响。

那有人说了：去掉一个最大值，去掉一个最小值，你看行不行？

当然不行啊！一堆 $0$ 中间插了一个 $100$，你把最大值 $100$ 干掉了，你看看这个盘子里还剩个啥。

所以这个题贪心来做很难找到一种合适的贪心策略，这个时候，我们就回忆起了——

~~暴力搜索~~

DP！

--------

正解：我们设 $dp_i$ 表示获得 $i$ 得分所用的钱的期望值。

不难想到，由于最后我们希望得到一个最优解，一定要最小化这个期望值，所以我们初始化时全部设成一个大数。

那么接下来考虑如何转移：

不难想起背包问题中我们的转移方程：

$$dp_i = \max(dp_i, dp_{i-v}+w)$$

（完全背包问题的转移方程）

那么这道题其实也很类似，只不过在做常规背包问题的时候我们是有选取某件物品的资格的，但是现在我们不能选特定的物品了，只能听天由命，让概率说话。

所以针对一个轮盘上的某个数 $p_k$，如果我们选到了它，就会让此时的期望值变成 $dp_{\max(0,i - p_k)}$。

但是需要注意，如果 $p_k = 0$，那么期望值转移回了 $dp_i$ 自己，这一步做得毫无意义，所以我们需要特判一下 $p_k = 0$ 的情况。

于是，我们只需要实现定义一个变量 $d$ 记录一下这个过程中我们的期望值的和，之后我们再除以有意义情况的个数，就得到了每次选到有意义情况时的期望。

以下，为了称呼方便，我们把 $s_{j,k} = 0$ 称为无意义情况，反之称为有意义情况。

这一部分代码如下：

```cpp
			d = 0;
			int z = 0;
			for(int k = 1; k <= p[j]; k = k + 1)
			{
				// 为了称呼方便，我们把 s[j][k] == 0 称为无意义情况，反之称为有意义情况 
				if(s[j][k] == 0)
					z ++;	// z 表示 0 的个数 
				else d += dp[max(0, i - s[j][k])];	// 此时 d 表示有意义情况总共的期望值 
			}
			d /= (p[j] - z);	// 此时 d 表示有意义情况平均的期望值 
```

然而，并不是每次操作都能选到有意义的情况，因为无意义情况个数为 $z$，所以有意义情况个数位 $p_j - z$，总情况数为 $p_j$，则不难理解选取到有意义情况的概率为 $\dfrac{p_j-z}{p_j}$。

而每玩一次都需要 $C_i$ 元，因此选到有意义的情况的代价应该是 $C_i \times \dfrac{p_j}{p_j-z}$。

那么我们就得到了状态转移的完整代码：

```cpp
	for(int i = 1; i <= m; i = i + 1)
	{
		double d;
		dp[i] = 1145141919810;
		for(int j = 1; j <= n; j = j + 1)
		{
			d = 0;
			int z = 0;
			for(int k = 1; k <= p[j]; k = k + 1)
			{
				// 为了称呼方便，我们把 s[j][k] == 0 称为无意义情况，反之称为有意义情况 
				if(s[j][k] == 0)
					z ++;	// z 表示 0 的个数 
				else d += dp[max(0, i - s[j][k])];	// 此时 d 表示有意义情况总共的期望值 
			}
			d /= (p[j] - z);	// 此时 d 表示有意义情况平均的期望值 
			d += c[j] * p[j] / double(p[j] - z);	// 同时，选到有意义情况需要付出一定代价
			// 每玩一次需要 c[j] 元，其中选到有意义情况的机会是 (p[j] - z) / p[j] 
			// 所以平均每次选到有意义情况的代价为 c[j] * p[j] / (p[j] - z) 
			dp[i] = min(dp[i], d);
			// 取每一个轮盘中的最小值 
		}
	}
```

结合前面的输入输出，以下是完整 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, c[114], p[114], s[114][114];
double dp[114];
int main()
{
//	freopen("a.txt", "r", stdin);
	cin >> n >> m;
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> c[i] >> p[i]; 
		for(int j = 1; j <= p[i]; j = j + 1)
			cin >> s[i][j];
	}
	for(int i = 1; i <= m; i = i + 1)
	{
		double d;
		dp[i] = 1145141919810;
		for(int j = 1; j <= n; j = j + 1)
		{
			d = 0;
			int z = 0;
			for(int k = 1; k <= p[j]; k = k + 1)
			{
				// 为了称呼方便，我们把 s[j][k] == 0 称为无意义情况，反之称为有意义情况 
				if(s[j][k] == 0)
					z ++;	// z 表示 0 的个数 
				else d += dp[max(0, i - s[j][k])];	// 此时 d 表示有意义情况总共的期望值 
			}
			d /= (p[j] - z);	// 此时 d 表示有意义情况平均的期望值 
			d += c[j] * p[j] / double(p[j] - z);	// 同时，选到有意义情况需要付出一定代价
			// 每玩一次需要 c[j] 元，其中选到有意义情况的机会是 p[j] / (p[j] - z) 
			// 所以平均每次选到有意义情况的代价为 c[j] * p[j] / (p[j] - z) 
			dp[i] = min(dp[i], d);
			// 取每一个轮盘中的最小值 
		}
	}
	cout << dp[m];
	return 0; 
}
```

完美 ~ 撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：zac2010 (赞：7)

假若 $\forall S_{i,p_i}>0$，显然可以直接 $\text{DP}$：

* 状态：$f_i$ 表示至少得 $i$ 分的期望代价。

* 转移：

  $$
  f_i=\min_{j=1}^n(C_j+\frac{1}{p_j}\sum_{k=1}^{p_j}f_{\max(i-S_{j,k},0)})
  $$

* 答案：$f_m$

然而题目只说 $S_{i,p_i}\geq 0$，也就是说可能存在 $S_{i,p_i}=0$ 的情况。

对于一个转盘（数组） $i$，我们令 $cnt_i=\sum_{i=1}^{p_i}[S_{i,p_i}=0]$，那么这个转盘等价于一个 $C_j=C_i\times\frac{p_i}{p_i-k_i}$，且去掉了所有 $0$ 的转盘。

问题得以解决。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 110;
int n, m, cnt;
double f[N], c[N], p[N];
vector<int> s[N];
int main(){
    scanf("%d%d", &n, &m);
    FL(i, 1, n){
        scanf("%lf%lf", &c[i], &p[i]), cnt = 0;
        FL(j, 1, p[i]){
            int x; scanf("%d", &x), cnt += (!x);
            if(x) s[i].emplace_back(x);
        }
        p[i] -= cnt; if(p[i]) c[i] *= (p[i] + cnt) / p[i];
    }
    FL(i, 1, m) f[i] = 1e18;
    FL(i, 1, m){
        FL(j, 1, n) if(p[j]){
            double cost = c[j];
            for(int &x: s[j])
                cost += f[max(0, i - x)] / p[j];
            f[i] = min(f[i], cost);
        }
    }
    printf("%lf", f[m]);
    return 0;
}
```



---

## 作者：Eibon (赞：4)

本题最优解捏TWT。

##

概率 dp，设 $F[i]$ 表示当前是 $i$，到达分数 $M$ 的状态最小值，因为概率 dp 一般采用反设，这里也同理。

初始化，将 $F[0]$ 到 $F[M-1]$ 赋为极大值。

则转移方程为 

$$F[j] = C[i] + \dfrac{\sum_{k=1}^{P[i]} {F[j + S[i][k]]}}{P[i]}$$

发现 $S[i][k]$ 可能为 $0$，这就会导致转移时从自己转移到自己。

不妨设轮盘 $i$ 上有 $cnt[i]$ 个值为 $0$ 的数。

则上式可化为

$$F[j] = C[i] + \dfrac{cnt[i] \times F[j] + \sum_{k=1}^{P[i]-cnt[i]} {F[j + S[i][k]]}}{P[i]}$$

注意，此时式中所有的 $S[i][k]$ 均不为 $0$。

进行化简

$$\dfrac{P[i]-cnt[i]}{P[i]} \times F[j] = C[i] + \dfrac{\sum_{k=1}^{P[i]-cnt[i]} {F[j + S[i][k]]}}{P[i]}$$

$$F[j] = \dfrac{C[i] \times P[i] + \sum_{k=1}^{P[i]-cnt[i]}{F[j + S[i][k]]}}{P[i]-cnt[i]}$$

转移即可，时间复杂度 $O(N \times M \times P)$。
### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=205+5;
int n,m,num;
int c[101],p[101],s[101][101],cnt[101];
double dp[201];
signed main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
		scanf("%d%d",&c[i],&p[i]);
		for(int j=1;j<=p[i];j++){
			scanf("%d",&s[i][j]);
			if(!s[i][j]){
				cnt[i]++;
			}
		}
	}
	fill(dp,dp+m,1e20);
	for(int j=m-1;j>=0;j--){
		for(int i=1;i<=n;i++){
			double sum=0;
			sum+=((double)c[i]*p[i]/(p[i]-cnt[i]));
			for(int k=1;k<=p[i];k++){
				if(s[i][k]){
					sum+=((double)dp[j+s[i][k]]/(p[i]-cnt[i]));
				}
			}
			dp[j]=min(dp[j],sum);
		}
	}
	printf("%.6lf\n",dp[0]);
	return 0;
}
//dyyyyds
```

---

## 作者：rzh123 (赞：3)

用 $f_v$ 表示得 $v$ 分需要的最小期望代价，每次枚举选每一个数列取最小值转移。  

当 $S_{i,j}\neq 0$ 时，需要 $C_i$ 代价，之后还需要得 $\max\{0,v-S_{i,j}\}$ 分，最小期望代价为 $f_{\max\{0,v-S_{i,j}\}}$，这样的概率是 $\frac{1}{P_i}$，这部分的期望代价是 $\sum\limits_{j=1}^{P_i}\frac{1}{P_i}\times(C_i+f_{\max\{0,v-S_{i,j}\}})$，取最小值转移到 $f_v$，就可以过样例 $1$ 了。  

上面的做法在样例 $2$ 就会有问题，因为出现了 $S_{i,j}=0$ 的情况，按照上面的方法会出现自己转移到自己。  

设 $S_{i,1},S_{i,2},\cdots,S_{i,P_i}$ 中 $0$ 的数量为 $t$，自己转移到自己的情况出现的概率是 $\frac t{P_i}$，它们的期望代价是 $\frac t{P_i}\times(C_i+f_v)$。  

选第 $i$ 个数列时总的转移方程：  

$$f_v=\frac{t}{P_i}\times(C_i+f_v)+\sum\limits_{1\le j\le P_i,S_{i,j}\neq 0}\frac{1}{P_i}\times(C_i+f_{\max\{0,v-S_{i,j}\}})$$  

把左边括号展开，含 $f_v$ 的放到左边，得到：  

$$f_v=\dfrac{\frac t{P_i}\times C_i+\sum\limits_{1\le j\le P_i,S_{i,j}\neq 0}\frac{1}{P_i}\times(C_i+f_{\max\{0,v-S_{i,j}\}})}{1-\frac{t}{P_i}}$$  

取最小值转移  

$$f_v=\min\limits_{i=1}^N\left( \dfrac{\frac t{P_i}\times C_i+\sum\limits_{1\le j\le P_i,S_{i,j}\neq 0}\frac{1}{P_i}\times(C_i+f_{\max\{0,v-S_{i,j}\}})}{1-\frac{t}{P_i}}\right)$$  

```cpp
#include <bits/stdc++.h>
using namespace std;
using lf=long double;
constexpr int N=205;
int n,m;
int c[N],p[N],s[N][N];
long double f[N];
signed main(){
    cin>>n>>m;
    for(int i{1};i<=n;++i){
        cin>>c[i]>>p[i];
        for(int j{1};j<=p[i];++j){
            cin>>s[i][j];
        }
    }
    f[0]=0;
    for(int i{1};i<=m;++i){
        f[i]=1e99;
        for(int j{1};j<=n;++j){
            int c0{0};
            long double ss{0};
            for(int k{1};k<=p[j];++k){
                if(s[j][k]==0)
                    ++c0;
                else
                    ss+=1.0l/p[j]*(f[max(0,i-s[j][k])]+c[j]);
            }
            ss+=1.0l*c0/p[j]*c[j];
            ss/=(1.0l-1.0l*c0/p[j]);
            f[i]=min(f[i],ss);
        }
    }
    long double ans{f[m]};
    cout<<fixed<<setprecision(10)<<ans<<endl;
    return 0;
}
```

---

## 作者：123zbk (赞：2)

概率 dp 好题。

考虑反设。$dp_i$ 表示还差 $i$ 得到 $M$ 分的最小期望代价。

转移：如果选到第 $i$ 个转盘，有 $\dfrac{1}{p_i}$ 的概率转到数列里的每一个数。此时代价需要加上 $c_i$。
$$dp_j=c_i+\dfrac{\sum_{k = 1}^{p_i}dp_{j+s_{i,k}}}{p_i}$$

发现存在 $s_{i,k}=0$ 的情况，此时会从 $dp_j$ 转移到 $dp_j$。

那么我们进行化简，设对于第 $i$ 个轮盘上有 $cnt_i$ 个 $0$。

将 $s_{i,k}=0$ 的单独考虑。
$$dp_j=c_i+\dfrac{cnt_i\times dp_j+\sum_{k = 1}^{p_i-cnt_i}dp_{j+s_{i,k}}}{p_i}$$

化简，将 $dp_j$ 都移到左边：
$$\dfrac{p_i-cnt_i}{p_i}\times dp_j=c_i+\dfrac{\sum_{k = 1}^{p_i-cnt_i}dp_{j+s_{i,k}}}{p_i}$$

所以：
$$dp_j=\dfrac{c_i\times p_i+ \sum_{k = 1}^{p_i-cnt_i}dp_{j+s_{i,k}}}{p_i-cnt_i}$$

答案是 $dp_0$。复杂度 $O(N\times M\times P)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=101;
int n,m,c[maxn],p[maxn],a[maxn][maxn],cnt[maxn];
double dp[201],sum;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&c[i],&p[i]);
        for(int j=1;j<=p[i];j++)
        {
            scanf("%d",&a[i][j]);
            if(not a[i][j])
            {
                cnt[i]++;
            }
        }
    }
    fill(dp,dp+m,1e20);//初始化
    for(int j=m-1;j>=0;j--)
    {
        for(int i=1;i<=n;i++)
        {
            sum=1.0*c[i]*p[i]/(p[i]-cnt[i]);
            for(int k=1;k<=p[i];k++)
            {
                if(a[i][k]!=0)
                {
                    sum+=1.0*dp[j+a[i][k]]/(p[i]-cnt[i]);
                }
            }
            dp[j]=min(dp[j],sum);
        }
    }
    printf("%.6lf",dp[0]);
    return 0;
}
```

---

## 作者：233L (赞：2)

参考了官方题解。

记 $e_i$ 表示已经有了 $i$ 分，要拿到至少 $M$ 的期望代价。$e_0$ 就是答案，对于 $i \ge M,e_i=0$。

转移，枚举每个轮盘，枚举每种可能就好了。
$$
e_i=\min_{j=1}^N C_j+\frac{1}{P_j} \sum_{k=1}^{P_j} e_{i+S_{j,k}}
$$
$i$ 从大到小转移，我认为这里有完全背包的感觉，每个轮盘都可以被选无限次。

做好了……吗？注意到 $S_{i,j}$ 可以为 $0$，但我们并不希望 $e_i$ 的转移式中出现 $e_i$。

于是考虑把 $S_{i,j}=0$ 的都干掉，再修改对应的 $C_i$，使期望不变。假设轮盘 $i$ 中有 $Z_i$ 个值为 $0$，期望选 $X_i$ 次拿到一个非 $0$ 值，列出方程 $X_i=1+\frac{Z_i}{P_i}X_i$，易得 $X_i=\frac{P_i-Z_i}{P_i}$。$P_i \gets P_i-Z_i,C_i \gets C_i \times X_i$。

~~~
#include<bits/stdc++.h>
using namespace std;
const int N=104;
const int C=1e6+4; 
int n,m;
int p[N];
int a[N][N];
double c[N],e[N<<1];
//e[i] 初始有i分，到至少m分花费的期望代价 

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>p[i];
		for(int j=1;j<=p[i];j++)cin>>a[i][j];
		sort(a[i]+1,a[i]+p[i]+1,greater<int>{});
		int j=p[i];
		while(!a[i][j])j--;
		c[i]*=1.0*p[i]/j,p[i]=j;
		//除掉0的 
	}
	for(int i=0;i<m;i++)e[i]=1e18;
	for(int i=m-1;~i;i--)
		for(int j=1;j<=n;j++){//枚举轮盘 
			double sum=0;
			for(int k=1;k<=p[j];k++)//枚举每种情况
				sum+=e[i+a[j][k]];
			e[i]=min(e[i],c[j]+sum/p[j]);
		}
	printf("%.6lf",e[0]);
}
~~~

---

## 作者：梦应归于何处 (赞：2)

## 题目大意

有 $N$ 个转盘。第 $i$ 个转盘上有 $P_i$ 个整数 $S_{i,1},S_{i,2},\dots, S_{i,P_i}$，每次转一次第 $i$ 个转盘需要支付 $C_i$ 元。当你转第 $i$ 个转盘一次，转盘会等概率的出现 $1,2,\dots, P_i$ 中的一个整数 $j$，然后你获得 $S_{i,j}$ 分。每次转转盘的得分是相互独立的。现在有一个人想要至少获得 $M$ 分。在获得至少 M 分之前，这个人的策略是最小化他支付的总钱数。在每次转转盘过后，他会根据已有的得分结果选择转哪个转盘。请求出这个人至少获得 $M$ 分所需支付的钱数的期望。

## Solution

我们先复习一下期望，假设我们要求得到 $X$ 分的期望，我们先设 $P$ 为转到 $X$ 的概率，$C$ 代表转出的数字和为 $X$ 要花费的钱数，则期望就是 $C \times P$。

这道题我们考虑 DP。

我们设 $dp_i$ 为已经得到了数字和为 $i$ 的期望。

然后就变成背包问题了。

详情请看代码。

~~~cpp
#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
using namespace std;
ll c[200], p[200];
double f[200];
ll s[200][200];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> c[i] >> p[i];
		for (int j = 1; j <= p[i]; j++) {
			cin >> s[i][j];
		}
	}
	for (int i = 1; i <= m; i++) {
		f[i] = 1e9;//初始化要初始化最大，后面要取最小值
	}
	for (int k = 1; k <= m; k++) {
		for (int i = 1; i <= n; i++) {
			double t = c[i] * p[i];//假设每个都转到了一次
			ll cnt = 0;//cnt代表要选几个数
			for (int j = 1; j <= p[i]; j++) {
				if (s[i][j]) {// 这里如果s[i][j]为0，那没有必要去买。
					t += f[max(0ll, k - s[i][j])];
					cnt++;
				}
			}
			f[k] = min(f[k], t / cnt);//这里是去求概率
		}
	}
	printf("%.30lf", f[m]);//输出答案多输出一点
	return 0;
}

~~~

---

## 作者：WhileTrueRP (赞：0)

# AT_abc314_e

## 题目大意

有 $N$ 个数列，第 $i$ 个数列的中有 $P_i$ 个数，分别是 $S_{i,1},S_{i,2},\cdots,S_{i,P_i}$。  

高桥每次可以选一个数列 $i$，付出 $C_i$ 的代价，得到从 $S_{i,1},S_{i,2},\cdots,S_{i,P_i}$ 中**等概率随机**的一个数的得分，每次选择时随机抽到哪个数与之前的选择无关。  

现在他要得至少 $M$ 分，每一次他可以根据之前的结果决定选择哪个数列，求他得至少 $M$ 分需要的最小期望代价。输出与答案的相对误差或绝对误差不超过 $10^{-5}$ 则视为正确。

## 分析

比较容易想到作为完全背包求解，但是复杂度过大。

正解为期望 DP。

设 $f_i$ 表示积分大于 $i$ 时的期望花费，易知 $\forall x\in[-\infty,0],f_x=0$。

容易得到转移方程 $f_i=\min_{i=1}^N(c_i+\frac{1}{P_i}\times\sum_j^{P_i}f_{i-S_{i,j}})$。

发现当 $S_{i,j}=0$ 时，无法转移。

考虑将每选到 $S_{i,j}=0$ 时，相当于 $C_i$ 变大了。

所以设 $cnt_i$ 表示 $\sum_{j}^{P_i}[S_{i,j}\neq0]$。

显然 $C_i=C_i\times P_i\div cnt_i$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int s[N][N],cnt[N];
double c[N],f[N];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int t,x;
		scanf("%lf%d",&c[i],&t);
		for(int j=1;j<=t;j++){
			scanf("%d",&x);
			if(x){
				s[i][++cnt[i]] = x;
			}
		}
		c[i] = c[i]*t/cnt[i];
	}
	for(int i=1;i<=m;i++){
		f[i] = 1e18+5;
		for(int j=1;j<=n;j++){
			double sum = 0;
			for(int k=1;k<=cnt[j];k++){
				if(i-s[j][k] >= 0){
					sum += f[i-s[j][k]];
				}
			}
			f[i] = min(f[i],c[j] + 1.0/cnt[j]*sum);
		}
	}
	printf("%.6lf",f[m]);
}
```

---

## 作者：qwq___qaq (赞：0)

暴力出奇迹，瞎搞秒数据。

贪心策略显然，即每次选择期望花费最小的轮盘。

对于一个轮盘，考虑背包 dp：设 $dp_{i}$ 表示当前分数为 $i$ 的期望花费，容易想到如下的转移：

$$dp_{i}\gets\dfrac{1}{P_i}(dp_{i-S_{i}}+C_i)$$

然后，你就光荣地过了第一个样例，但是在第二个样例就死掉了，为什么呢？

注意到 $S_i\ge0$，那么当 $S_i=0$ 时，如果采用记忆化搜索就会循环调用，TLE。

那么我们令选择非零的数的期望花费是 $dp'_i$，同时令序列中 $0$ 的数量是 $x$，那么有：

$$dp_{i}\gets\sum\limits_{i=0}^{\infty}(\dfrac{x}{P})^i\dfrac{P-x}{P}dp'_i$$

因为 $\sum S>0$，所以 $x<P$。那么注意到 $\lim\limits_{i\to\infty}(\dfrac{x}{P})^i\to0$，那么在 $i$ 比较大的时候这个式子是趋近于 $0$ 的，不需要考虑，于是我们就考虑 $i$，并且在不会 TLE 的范围内枚举尽量多的 $i$。

以运行效率 $10^8$，并且极限值 $n=100$ 来算，记忆化需要 $O(n)$，枚举轮盘需要 $O(n)$，那么满打满算 $i$ 至少可以跑到 $10^4$。但是因为评测机效率更高的原因，应该可以跑更大，但是赛时直接调到 $i\le 10^4$ 就一遍过了。

赛后试了试，枚举上界取 $10^3$ 都过不了。

[代码中是用记忆化搜索实现的](https://atcoder.jp/contests/abc314/submissions/44532661)

---

