# Phoenix and Berries

## 题目描述

Phoenix is picking berries in his backyard. There are $ n $ shrubs, and each shrub has $ a_i $ red berries and $ b_i $ blue berries.

Each basket can contain $ k $ berries. But, Phoenix has decided that each basket may only contain berries from the same shrub or berries of the same color (red or blue). In other words, all berries in a basket must be from the same shrub or/and have the same color.

For example, if there are two shrubs with $ 5 $ red and $ 2 $ blue berries in the first shrub and $ 2 $ red and $ 1 $ blue berries in the second shrub then Phoenix can fill $ 2 $ baskets of capacity $ 4 $ completely:

- the first basket will contain $ 3 $ red and $ 1 $ blue berries from the first shrub;
- the second basket will contain the $ 2 $ remaining red berries from the first shrub and $ 2 $ red berries from the second shrub.

Help Phoenix determine the maximum number of baskets he can fill completely!

## 说明/提示

The first example is described above.

In the second example, Phoenix can fill one basket fully using all the berries from the first (and only) shrub.

In the third example, Phoenix cannot fill any basket completely because there are less than $ 5 $ berries in each shrub, less than $ 5 $ total red berries, and less than $ 5 $ total blue berries.

In the fourth example, Phoenix can put all the red berries into baskets, leaving an extra blue berry behind.

## 样例 #1

### 输入

```
2 4
5 2
2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
1 5
2 3```

### 输出

```
1```

## 样例 #3

### 输入

```
2 5
2 1
1 3```

### 输出

```
0```

## 样例 #4

### 输入

```
1 2
1000000000 1```

### 输出

```
500000000```

# 题解

## 作者：s_r_f (赞：18)

设答案上界为$up,$下界为$down.$

$\large up = \lfloor \frac{\sum\limits_{i=1}^{n} a_i+b_i}{k} \rfloor$

$\large down = \lfloor \frac{\sum\limits_{i=1}^{n} a_i}{k} \rfloor + \lfloor \frac{\sum\limits_{i=1}^{n} b_i}{k} \rfloor$

$up$表示我们无视限制$,$把所有的红莓和蓝莓都往篮子里放

$down$表示我们**不考虑同一棵树上的红莓和蓝莓放在一起的操作**$,$只把相同颜色的放在一起$.$

不难发现$,$ $up$和$down$之间的差不会超过$1.$

如果$up=down$就可以直接输出了$.$以下只考虑$up-down=1$的情况$.$

现在我们要解决的$,$就是判断答案是否能达到$up.$

我们令$ra=$ $(\sum\limits_{i=1}^{n} a_i)$ $mod$ $p$ $,rb=$ $(\sum\limits_{i=1}^{n} b_i)$ $mod$ $p.$

我们要判断的是$,$能否通过**同一棵树上的蓝莓和红梅放到一起**的操作来使得使用掉的$a$对$k$取模的值在$[k-rb,ra]$之间$.$

记$bool$ $dp(i,r)$表示考虑到第$i$棵树$,$当前用掉的$a$对$k$取模的值为$r,$是否可能$.$

然后直接暴力转移是$O(nk^2)$的$,$可以前缀和优化到$O(nk).$

$O(nk^2)$代码

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
const int N = 505,K = 505;
int n,k,a[N],b[N]; LL suma,sumb;
int ra,rb;
int L,R;

int dp[K],f[K];
int main(){
	int i,j,t;
	read(n),read(k); for (i = 1; i <= n; ++i) read(a[i]),read(b[i]),suma += a[i],sumb += b[i];
	if (suma / k + sumb / k == (suma + sumb) / k){ cout << (suma + sumb) / k << '\n'; return 0; }
	ra = suma % k,rb = sumb % k;
	L = k - rb,R = ra;
	dp[0] = 1;
	for (t = 1; t <= n; ++t){
		for (i = 0; i < k; ++i) f[i] = dp[i];
		for (i = 0; i < k; ++i) if (f[i])
		for (j = 1; j < k; ++j) if (j <= a[t] && k-j <= b[t]) dp[(i+j>=k)?(i+j-k):(i+j)] = 1;
		for (i = L; i <= R; ++i) if (dp[i]){ cout << (suma + sumb) / k << '\n'; return 0; }
	} 
	cout << (suma + sumb) / k - 1 << '\n'; return 0;
}
```

---

## 作者：wsyhb (赞：6)

## 题意简述

小P在花园里摘红梅和蓝莓。

他一共有 $n$ 棵树，第 $i$ 棵树上有 $a_i$ 个红梅和 $b_i$	个蓝莓。~~由于小P有强迫症，所以~~他希望一个篮子里的梅子都来自同一棵树或都是一种颜色的（或两者同时满足）。

给出篮子的最大容量 $k$，求能够被装满的篮子数量的最大值（不必用完所有梅子）。

**数据范围**：$1 \le n,k \le 500$，$0 \le a_i,b_i \le 10^9$。

PS：题面的翻译写得太好了，所以直接照搬。~~没人有意见吧。~~

## 分析 + 题解

注意到 $n,k$ 的数据范围较小，和 $a_i,b_i$ 的数据范围截然不同，但 $a_i>k$ 显然可以转化为 $a_i \le k$ 进行计算，猜测时间复杂度为 $O(n^3)$。（其中 $n$ 和 $k$ 同阶）

似乎没有显而易见的贪心解法，考虑 DP。

设 $dp[i][j]$ 表示考虑前 $i \; (1 \le i \le n)$ 棵树，是否可以使得剩余的红梅个数为 $j$。

PS：

1. “剩余的红梅”指的是装满若干个篮子后，剩余的所有红梅；**由于我们已经考虑了前 $i$ 棵树中，所有由同一棵树的树莓组成的篮子，之后的 $j$ 个红梅一定只可能出现在全为红梅的篮子中，故 $dp[i][j]$ 与 $dp[i][j \mod k]$ 等价，即 DP 状态的范围一定有 $0 \le j<k$**；

2. “是否”说明这个状态可以**用 bool 类型表示**。

若第 $i$ 棵树可以产生 $l \; (0 \le l \le a_i)$ 个额外的红梅，则需要满足**下列条件中的至少一个**：

- $(a_i-l) \mod k + b_i \ge k$

- $l = (a_i \mod k)$

**即第 $i$ 棵树有 $(a_i-l) \mod k$ 个红莓被分配到了装满的篮子，需要满足有足够多的蓝莓与之搭配，或者根本就没有这样的红莓**，即 $(a_i-l) \mod k=0$

对于所有合法的 $l$，$dp[i][j]$ 可以由 $dp[i-1][(j+k-l) \mod k]$ 转移而来。

设最小的满足 $dp[n][j]$ 为真的 $j=q$，则最终答案为 $\lfloor \dfrac{\sum_{i=1}^n (a_i+b_i)-q}{k} \rfloor$，特别地，若不存在 $q$，答案为 $0$。

PS：虽然 DP 状态中没有记录**蓝莓的剩余个数**，但它必定 $<k$，**对答案不产生影响**。（若 $\ge k$ 可以再装若干个篮子）

具体实现只需枚举 $i,j,l$，时间复杂度为 $O(nk^2)$。（~~我猜的真准^_^~~ 据说这道题还有 $O(nk)$ 的解法，此处不讲 ~~，因为我不会~~）

## 代码

如果还有什么不清楚的就看注释吧。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=500+5;
int a[max_n],b[max_n];
bool dp[max_n][max_n];//注意是 bool 类型 
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d%d",a+i,b+i);
	long long sum=0;
	for(int i=1;i<=n;++i)
		sum+=a[i]+b[i];//sum 表示总树莓个数 
	dp[0][0]=true;//初始化 
	for(int i=1;i<=n;++i)
		for(int j=0;j<=k-1;++j)
		{
			dp[i][j]|=dp[i-1][(j+k-a[i]%k)%k];//注意 l=a[i]%k 的情况要特判 
			for(int l=0;l<=min(k-1,a[i])&&!dp[i][j];++l)//由于是或运算，一旦为真就可以停止计算 
			{
				if((a[i]-l)%k+b[i]>=k)//判断 l 是否符合上文所述条件 
					dp[i][j]|=dp[i-1][(j+k-l)%k];
			}
		}
	for(int i=0;i<=k-1;++i)
	{
		if(dp[n][i])
		{
			printf("%lld\n",(sum-i)/k);//找到最小的 i，相当于上文所述的 q 
			return 0;
		}
	}
	puts("0");//未找到输出 0 
	return 0;
}
```

---

## 作者：Exp10re (赞：3)

真没有 $2400^*$ 吧。

## 解题思路

答案的一个显然的下界是 $\lfloor \frac {S_1} {K} \rfloor + \lfloor \frac {S_2} {K} \rfloor$，其中 $S_1=\sum\limits_{i=1}^n a_i$，$S_2=\sum\limits_{i=1}^n b_i$，对于下界的理解是每一种颜色都尽可能装到一个篮子里面就能得到该下界。

考虑到这一部分取完之后剩余 $R_1=S_1 \bmod K$ 个红莓，$R_2=S_2 \bmod K$ 个蓝莓，若 $R_1+R_2\lt K$ 则答案为下界，因为剩余的部分不可能再装满一篮，否则答案有一个上界 $\lfloor \frac {S_1} {K} \rfloor + \lfloor \frac {S_2} {K} \rfloor +1$。

接下来考虑如何取得上界：假设我们进行若干次选择同一棵树的操作后剩余 $C_1$ 个红莓，$C_2$ 个蓝莓，若 $(C_1 \bmod K)+(C_2 \bmod K)\lt K$ 则能取到这个上界，此时必定存在 $P$ 满足 $(C_1 \bmod K)=R_1-P$，$(C_2 \bmod K)=R_2-(K-P)$。

枚举所有可行的 $P$，考虑找到若干个操作构造 $P$。

记 $f_{i,j}$ 表示仅考虑前 $i$ 棵树，是否存在一种只取树上的果子的方案使得被取走的红莓个数模 $K$ 的值为 $j$。

边界为 $f_{0,0}=1,f_{0,i}=0$。转移可以枚举这棵树所有取果子的方案对于每一种方案 $O(K)$ 转移，方程是简单的余数 DP。

若存在 $f_{i,P}=1$ 则能取到上界，否则取不到。

时间复杂度 $O(nK^2)$，使用 bitset 可以做到 $O(\frac {nK^2} {\omega})$，但是懒得打了。

[Submission.](https://codeforces.com/contest/1348/submission/293332000)

---

## 作者：do_while_true (赞：2)

假如只把相同颜色的果子放在一起，会剩下 $\sum a\bmod k$ 个红果子，$\sum b\bmod k$ 个绿果子，这是可以构造出来的答案的下界。

剩下的红果子个数 $<k$，蓝果子个数 $<k$，果子和 $<2k$，最多会凑出一个篮子，所以答案的上界是我们可以轻易构造出的下界 $+1$．

现在要判断这个上界是否能达到，我们可以假装全部相同颜色装在一起，然后拆篮子，通过在装同一棵树上的果子来消耗掉剩余的果子。

设 $f_{i,j}$ 代表考虑前 $i$ 个树，消耗的红果子个数在模 $k$ 意义下为 $j$，那么消耗的蓝果子数就是 $(k-j)\bmod k$，是否存在一种方案。

若 $f_{i,j}=1,k-(\sum b)\bmod k\leq j\leq (\sum a)\bmod k$，那么即存在一种方案可以拆开一些篮子然后消耗掉剩余的果子来达到答案的上界。

直接 dp 的复杂度为 $\mathcal{O}(nk^2)$，可以前缀和优化优化到 $\mathcal{O}(nk)$。

```cpp
#include<iostream>
#include<cstdio>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
int Mod(int x, int y) { return x < 0 ? (x + y) : (x >= y ? (x - y) : x); }
const int N = 510;
int n, k;
int a[N], b[N];
ll sa, sb, ans, f[N], g[N];
int Sum(int l, int r) {
	if(l <= r) return g[r] - (l == 0 ? 0 : g[l-1]);
	return g[r] + g[k-1] - g[l-1];
}
signed main() {
	read(n); read(k);
	for(int i = 1; i <= n; ++i) read(a[i]), read(b[i]), sa += a[i], sb += b[i];
	ans = sa / k + sb / k; sa %= k, sb %= k;
	if(sa + sb < k) {
		printf("%lld\n", ans);
		return 0;
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < k; ++j) g[j] = f[j];
		for(int j = 1; j < k; ++j) g[j] += g[j-1];
		for(int j = 0; j < k; ++j) 
			if(!f[j]) {
				int L = j-Min(a[i], k-1), R = j-Max(0, k-b[i]);
				if(L > R) continue ;
				L = Mod(L, k); R = Mod(R, k);
				if(Sum(L, R)) f[j] = 1;
			}
		for(int j = k - sb; j <= sa; ++j)
			if(f[j]) {
				printf("%lld\n", ans+1);
				return 0;
			}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：ix35 (赞：2)

是一道 DP 题。

初步想法是用 $dp(i,x,y)$ 表示考虑前 $i$ 行，选了 $x$ 个红果子和 $y$ 个蓝果子最多能装多少篮。

然后发现如果倒过来表示，用 $dp(i,x,y)$ 表示考虑前 $i$ 行，多余 $x$ 个红果子和 $y$ 个蓝果子，这样就有 $x,y<k$，状态数为 $O(n^2k)$。

然后考虑优化状态，可以根据一些余数关系导出 $y$ 与 $x$ 的和在 $\bmod k$ 意义下是定值，所以只需要用 $dp(i,x)$ 就可以唯一表示一个状态。

正常转移的话做一个 $i$ 也是 $O(k^3)$ 的，但是可以利用同样的优化，只枚举红色果子数量，做到 $O(k^2)$ 的转移。

总的复杂度就是 $O(nk^2)$ 了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=510;
int n,k,a[MAXN],b[MAXN];
ll dp[2][MAXN],sum,ans;
int main () {
	scanf("%d%d",&n,&k);
	for (int i=0;i<k;i++) {dp[0][i]=-1e18;}
	dp[0][0]=0;
	for (int i=1;i<=n;i++) {
		for (int j=0;j<k;j++) {dp[i&1][j]=-1e18;}
		scanf("%d%d",&a[i],&b[i]);
		for (int j=0;j<k;j++){ 
			int tmp=(sum%k+k-j)%k;
			for (int l=0;l<min(k,a[i]+1);l++) {
				int tmp2=((a[i]+b[i])%k+k-l)%k;
				//cout << i << "    " << j << "  " << tmp << "    " << l << "  " << tmp2 << "    " << dp[i&1][(j+l)%k] << "    ";
				if (tmp2>b[i]) {continue;}
				dp[i&1][(j+l)%k]=max(dp[i&1][(j+l)%k],dp[(i&1)^1][j]+(j+l)/k+(tmp+tmp2)/k+(a[i]+b[i]-tmp2-l)/k);
				//cout << dp[i&1][(j+l)%k] << "    " << dp[(i&1)^1][j]+(j+l)/k+(tmp+tmp2)/k+(a[i]+b[i]-tmp2-l)/k << endl;
			}
		}
		sum+=a[i];
		sum+=b[i];
	}
	ans=0;
	for (int i=0;i<k;i++) {ans=max(ans,dp[n&1][i]);}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：chenxia25 (赞：2)

不难想到一种方案：将两种颜色分别尽力搞掉，这样两种颜色剩的个数都会 $<m$，加起来就 $<2m$，于是答案下界是这种方案的答案，上界就是再加一。我们只需要判断加一能不能做到。

我们考虑将一种颜色通过同一棵树搞掉一些，使得剩下的个数 $\bmod m$ 是我们想要的。于是我们只需要算有哪些 $x\in[0,m)$ 可以作为被搞掉的个数 $\bmod m$。这个 $\mathrm O\!\left(nm^2\right)$ 随便 DP 就好了。

---

## 作者：Mirasycle (赞：1)

最优化问题不会的话就尝试找找上下界。

这题的突破口就是寻找上下界，可以发现答案上界为 $\lfloor \frac{\sum a_i+\sum b_i}{k} \rfloor$，下界为 $\lfloor\frac{\sum a_i}{k}\rfloor+\lfloor\frac{\sum b_i}{k}\rfloor$。不难发现二者最大差为 $1$，且取决于 $ra=\sum a_i \bmod k$，$rb=\sum b_i \bmod k$。

如果 $ra+rb<k$，那么上下界相等直接输出即可。

如果 $k \le ra+rb <2k$，那么我们可以尝试用同一颗树上的果子来装篮子，使得采用这个方法用掉的 $a~b$ 满足 $ua' \bmod k \in (0,ra)$，$ub' \bmod k \in (0,rb)$，且 $ ua'+ ub' \equiv 0 (\bmod k)$。

如果此时进行 dp 的话状态数太大，我们发现 $ua~ub$ 有约束关系，那么能否使用其中一个来表示另一个。 其实是可以的，只需满足 $ua' \bmod k \in (k-rb,ra)$ 即可。

---

## 作者：Fracture_Dream (赞：1)

# 简述题意
有 $n$ 个盒子，每个盒子里有 $a_i$ 个红球和 $b_i$ 个蓝球。现有无数个可以装 $k$ 个小球的容器，规定容器里的球必须满足以下条件之一：
- 来自同一个盒子
- 颜色相同
 
不必用完所有小球，问最多能装满多少个容器。

- $1 \le n,k \le 500$
# 思路
首先注意到，用完球一定比不用完球更优，即使最后有容器没装满。

以下不妨简记，$sum1=\sum_{i=1}^{n}a_i$，$sum2=\sum_{i=1}^{n}b_i$

注意到，如果我们忽略限制，答案为 $up = \lfloor \frac{sum1+sum2}{k} \rfloor$。那么显然有：$ans \leq up$。
其次，我们忽略容器里的小球来自于同一个盒子的情况，此时答案为 $down= \lfloor \frac{sum1}{k} \rfloor + \lfloor \frac{sum2}{k} \rfloor$，那么显然有：$ans \geq down$。
注意到，$up - down \leq 1$，证明略。

因此，如果 $up=down$，那么直接输出 $down$ 即可。否则如果 $up=down+1$，我们就需要考虑最终答案能否达到上界 $up$。

我们先假装把相同颜色的球装在一起，不妨令 $ra = sum1 \bmod k$，$rb = sum2 \bmod k$。那么此时剩下了 $ra$ 个红球，$rb$ 个蓝球，那么我们现在的要做的，就是通过将同一个盒子的小球放在一起，尽可能消耗剩下的红球。

不妨假设，将同一个盒子里的球装入同一个容器，使用了 $A$ 个红球，$B$ 个蓝球，其中 $A = x1 \times k + r1$，$B = x2 \times k + k - r1$，那么这部分装满了 $x1 + x2 + 1$ 个容器。

此时还剩下 $sum1 - A$ 个红球和 $sum2 - B$ 个蓝球。
注意到：如果 $r1 \le ra$ 且 $k - r1 \le rb$ ，即 $r1 \in [k - rb,ra]$ 时，剩下的红球可以装满 $\lfloor \frac{sum1}{k} \rfloor - x1$ 个容器，剩下的蓝球可以装满 $\lfloor \frac{sum2}{k} \rfloor - x2$ 个容器，总共就可以装满 $\lfloor \frac{sum1}{k} \rfloor + \lfloor \frac{sum2}{k} \rfloor + 1$ 个容器。这不正是我们想要达到的上界嘛！

因此，我们只需要判断，能否使选择的红球数对 $k$ 取模后，范围在 $[k-rb,ra]$ 之内。这启发我们 $\text{dp}$。
不妨令 $dp_{i,r}$ 表示 **能否** 处理完前 $i$ 个盒子之后 ，选择的红球数量对 $k$ 取模后的值为 $r$。暴力 $O(nk^2)$ 转移即可。
最后，如果 $\exist i \in [k-rb,ra],dp_{n,i}=1$，那么证明我们可以达到答案的上界 $up$，输出 $up$ 即可。否则输出 $down$ 即可。

# 代码
~~非常非常非常非常非常非常非常非常~~非常抽象的一道题，但是代码挺好写的，这里放的是官解的代码。

```cpp
//Solution 1
#include <bits/stdc++.h>
using namespace std;

int N,K;
int a[505],b[505];
bool dp[505][505];  //number of shrubs considered, "extra" red berries

int main(){
  cin>>N>>K;
  long long totA=0,totB=0;
  for (int i=1;i<=N;i++){
    cin>>a[i]>>b[i];
    totA+=a[i];
    totB+=b[i];
  }
  dp[0][0]=true;
  for (int i=1;i<=N;i++){
    for (int j=0;j<K;j++){
      //leave a[i]%K extra red berries
      dp[i][j]=dp[i-1][(j-a[i]%K+K)%K];
      for (int l=0;l<=min(K-1,a[i]);l++){
	//check if we can leave l extra red berries
	if ((a[i]-l)%K+b[i]>=K)
	  dp[i][j]|=dp[i-1][(j-l+K)%K];
      }
    }
  }
  long long ans=0;
  for (int i=0;i<K;i++){
    if (dp[N][i])
      ans=max(ans,(totA+totB-i)/K);
  }
  cout<<ans<<endl;
}
```

---

## 作者：睿智的憨憨 (赞：0)

# CF1348E Phoenix and Berries 解题报告

设 $\sum a[i] = k_1 \times K + r_1, \sum b[i] = k_2 \times K + r_2$。

那么答案的上界为 $mx = \left\lfloor\frac{\sum a[i] + \sum b[i]}{K}\right\rfloor = k_1 + k_2 + \left\lfloor\frac{r_1 + r_2}{K}\right\rfloor$。

如果只考虑在篮子里装同一种颜色的情况，而不考虑装同一棵树中的梅子，那么答案至少为 $mn = k_1 + k_2$，发现 $mx - mn \le 1$！

当 $mx = mn$ 时，就可以直接输出 $mx$ 了。

现在考虑什么时候 $mx = mn + 1 = k_1 + k_2 + 1$。

最优操作可以看作先用同一棵树上的红蓝梅子装满篮子，最后扫尾时用同种颜色可以不同树的梅子装满篮子。

设只用同一棵树上的红蓝梅子装篮子时用了 $A$ 个红梅，$B$ 个蓝梅，其中 $A = x_1 \times K + y,B = x_2 \times K + (K - y)$，则这部分装满了 $x_1 + x_2 + 1$ 个篮子。于是，当且仅当 $y \le r_1,(K - y) \le r_2$ 时有 $ANS = (x_1 + x_2 + 1) + (k_1 - x_1) + (k_2 - x_2) = k_1 + k_2 + 1 = mx$，
所以我们希望最后的 $y$ 在 $[K - r_2, r_1]$ 区间内。

然后就可以设计出 dp 状态：$f[i][j]$ 表示考虑了前 $i$ 棵树，用的红梅子数量模 $K$ 为 $j$ 是否可行。直接转移是 $O(nk^2)$，已经可以通过了。如果想精益求精可以再加一个前缀和优化，做到 $O(nk)$。

这里贴上 $O(nk)$ 的代码，15ms 也是成功成为全谷最优解：

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 510;

int n, K, a[N], b[N];
ll tota, totb, mn, mx;
//f[i][j]：考虑了前 i 棵树，用的红梅个数模 K 为 j 是否可行 
bool f[N][N];
//s 是 f 的前缀和数组 
int s[N][N];

int main(){
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; i++){
		scanf("%d %d", &a[i], &b[i]);
		tota += a[i], totb += b[i];
		mx += a[i] + b[i];
	}
	mx /= K, mn = tota / K + totb / K;
	if (mx == mn){
		printf("%lld\n", mx);
		return 0;
	}
	//初值 
	f[0][0] = true;
	for (int i = 0; i < K; i++)
		s[0][i] = 1;
	//dp
	for (int i = 1; i <= n; i++){
		for (int j = 0; j < K; j++){
			f[i][j] = f[i - 1][j];//不用这棵树 
			int l = max(0, K - b[i]), r = min(a[i], K - 1);//红梅模 K 的范围为[l,r]，是取不到[0,l)的，需要仔细想一想 
			if (l <= r){
				if (j < r && s[i - 1][j - max(l, j + 1) + K] - s[i - 1][j - r + K - 1] > 0)
					f[i][j] = true;
				if (j >= l && s[i - 1][j - l] - (j > r ? s[i - 1][j - r - 1] : 0) > 0)
					f[i][j] = true;
			}
			if (j)
				s[i][j] = s[i][j - 1] + f[i][j];
			else
				s[i][j] = f[i][j];
		}
	}
	//答案 
	totb %= K, tota %= K;
	ll ans = mn;
	for (int i = K - totb; i <= tota; i++)
		if (f[n][i])
			ans = mx;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

贪心地，所有莓都要用完。

不妨定义 $f_{i,x,y}$ 表示前 $i$ 棵树操作完后，红莓和蓝莓的数量。容易发现因为都用完了，所以 $x,y$ 是可以互推的，状态就只剩 $O(n^2)$ 了。

然后容易发现对于同一棵树，最多只有 $1$ 个篮子会出现来自同一棵树的不同颜色。否则一定有一种颜色的出现次数 $\ge n$，然后就可以在这种颜色中取 $n$ 个出来，这显然是等价的。

于是可以 $O(n)$ 枚举这个篮子中每种颜色的数目，剩下的直接算就行了。

用记搜实现较为方便，注意常数。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define endl '\n'
using namespace std;
const int N=505;
int n,k,a[N],b[N];
LL f[N][N];
LL dfs(int now,int x,int y){
	if(now==n+1) return 0;
	if(~f[now][x]) return f[now][x];
	f[now][x]=dfs(now+1,(x+a[now])%k,(y+b[now])%k)+(x+a[now])/k+(y+b[now])/k;
	for(int i=1;i<k;++i) if(a[now]>=i&&b[now]>=k-i) f[now][x]=max(f[now][x],dfs(now+1,(x+a[now]-i)%k,(y+b[now]-(k-i))%k)+(x+a[now]-i)/k+(y+b[now]-(k-i))/k+1);
	return f[now][x];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i]>>b[i];
	memset(f,-1,sizeof(f));
	cout<<dfs(1,0,0)<<endl;
	return 0;
}
```

---

## 作者：红黑树 (赞：0)

1. 首先可以观察到，每一组 $(a_i,b_i)$ 肯定是尽可能凑成若干组 $k$ 的，我们发现最终的 $(a_i,b_i)$ 假如去除了内部凑齐的 $k$ 之后，$a_i,b_i<k$。于是考虑一个 dp，记 $f_{i,x,y}$ 表示考虑了前 $i$ 个种类，当前剩下的 $a$ 颜色有 $x<k$ 个，$b$ 颜色有 $y<k$ 个。

   那么可以 dp 转移，每次枚举 $(a_i,b_i)$ 中我们保留 $j$ 个 $a$ 颜色不选，那么就会保留 $k-j$ 个 $b$ 颜色不选。然后就可以 $\mathcal{O}\left(nk^3\right)$ 转移了。

   但是我们发现，实际上，知道了 $i,x$ 之后，$y=\left(\sum\limits_{j=1}^i (a_j+b_j)-x\right)\bmod k$。所以可以把状态中 $y$ 这一维去掉，最终变成 $\mathcal{O}\left(nk^2\right)$，可以通过本题 $n,k\le 500$ 的数据。

   

2. 考虑一个加强，$n,k\le 2000$，那么只有 $\mathcal{O}\left(nk\right)$ 之类的做法可以通过了。容易发现上面的做法没啥优化前途，只能考虑另一个思考角度了。

   考虑我们答案最终可能的取值，我们发现，如果像上述做法一样，尽可能同种类内的匹配，那么它其实是不好考虑的。因为每个种类最终遗留下来的余数数量级是 $\mathcal{O}\left(nk\right)$ 的。

   所以我们考虑换一个角度，优先满足同颜色的匹配。那么如果全部都匹配同颜色的，那么得出 $L=\left\lfloor\frac{\sum\limits_{i=1}^n a_i}{k}\right\rfloor+\left\lfloor\frac{\sum\limits_{i=1}^n b_i}{k}\right\rfloor$，如果记 $ra = \sum\limits_{i=1}^n a_i\bmod k,rb = \sum\limits_{i=1}^n b_i\bmod k$，那么如果 $ra+rb\ge k$，我们就可以考虑通过拆一些配齐的同颜色组，然后用一些同种类组替代。

3. 不难想到一种 dp，顺次考虑所有数对 $(a_i,b_i)$，记 $f_{i,x}$ 表示前 $i$ 组中最终拆出来用于同类配对的 $a$ 颜色数量在模 $k$ 意义下有 $i$ 个是否可行，那么如果最终存在一个 $f_{n,x}=1,x\in[k-rb,ra]$，那么就说明可以从原先的答案下界  $L$ 增加一组新的，否则答案就是 $L$。

4. dp 转移，考虑怎样的 $f_{i-1,y}$ 可以转移到 $f_{i,x}$。

   * $y=x$，那么
   * $y<x$，那么选了 $x-y$ 个 $i$ 种类的 $a$ 颜色球和 $i$ 种类的 $b$ 颜色球配对，由于要恰好凑成一对 $k$，就是说从 $a_i$ 中取了 $x-y$ 个球，从 $b_i$ 中取了 $k-x+y$ 个球。那么满足 $x-y\le a_i,k-x+y\le b_i$ 这两个额外条件即可，整理即得 $y\in[x-a_i,x+b_i-k]$。
   * $y>x$，那么选了 $x-y+k$ 个 $i$ 种类的 $a$ 颜色球和 $i$ 种类的 $b$ 颜色球配对，由于要恰好凑成一对 $k$，就是说从 $a_i$ 中取了 $x-y+k$ 个球，从 $b_i$ 中取了 $y-x$ 个球。那么满足 $x-y+k\le a_i,y-x\le b_i$ 这两个额外条件即可，整理即得 $y\in[x-a_i+k,x+b_i]$。

   我们发现这是区间转移的，所以可以考虑对 $f_i$ 做前缀和优化，这样 $f_{i,x}$ 的转移就是 $\mathcal{O}\left(1\right)$ 的，时空复杂度均为 $\mathcal{O}\left(nk\right)$。

   当然区间转移也可以用 bitset 维护位移之类的来做，是 $\mathcal{O}\left(\frac{nk^2}{\omega}\right)$，可以通过，但我认为是完全不优美的，理应卡掉才对！

   ```cpp
   void FALLING() {
      int n, k; cin >> n >> k;
      V<int> a(n + 1, 0), b(n + 1, 0);
      int sa = 0, sb = 0; ll ans = 0;
      FOR (i, 1, n) {
         cin >> a[i] >> b[i];
         sa += a[i], ans += sa / k, sa %= k;
         sb += b[i], ans += sb / k, sb %= k;
      }
    
      V<V<bool>> f(n + 1, V<bool>(k, 0));
      V<V<int>> g(n + 1, V<int>(k + 1, 0));
      f[0][0] = 1, g[0].assign(k + 1, 1), g[0][0] = 0;
      FOR (i, 1, n) {
         auto calc = [&] (int l, int r) -> bool {
            return l > r ? 0 : (g[i - 1][r + 1] - g[i - 1][l] > 0);
         };
         FOR (x, 0, k - 1) {
            f[i][x] = f[i - 1][x];
            if (!f[i][x]) f[i][x] = calc(std::max(0, x - a[i]), std::min(x, x + b[i] - k));
            if (!f[i][x]) f[i][x] = calc(std::max(x + 1, x - a[i] + k), std::min(k - 1, x + b[i]));
            g[i][x + 1] = g[i][x] + f[i][x];
         }
      }
      FOR (x, k - sb, sa)
         if (f[n][x]) { ans++; break; }
      cout << ans << "\n";
      return ;
   }
   ```

---

