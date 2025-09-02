# Many Games

## 题目描述

Recently, you received a rare ticket to the only casino in the world where you can actually earn something, and you want to take full advantage of this opportunity.

The conditions in this casino are as follows:

- There are a total of $ n $ games in the casino.
- You can play each game at most once.
- Each game is characterized by two parameters: $ p_i $ ( $ 1 \le p_i \le 100 $ ) and $ w_i $ — the probability of winning the game in percentage and the winnings for a win.
- If you lose in any game you decide to play, you will receive nothing at all (even for the games you won).

You need to choose a set of games in advance that you will play in such a way as to maximize the expected value of your winnings.

In this case, if you choose to play the games with indices $ i_1 < i_2 < \ldots < i_k $ , you will win in all of them with a probability of $ \prod\limits_{j=1}^k \frac{p_{i_j}}{100} $ , and in that case, your winnings will be equal to $ \sum\limits_{j=1}^k w_{i_j} $ .

That is, the expected value of your winnings will be $ \left(\prod\limits_{j=1}^k \frac{p_{i_j}}{100}\right) \cdot \left(\sum\limits_{j=1}^k w_{i_j}\right) $ .

To avoid going bankrupt, the casino owners have limited the expected value of winnings for each individual game. Thus, for all $ i $ ( $ 1 \le i \le n $ ), it holds that $ w_i \cdot p_i \le 2 \cdot 10^5 $ .

Your task is to find the maximum expected value of winnings that can be obtained by choosing some set of games in the casino.

## 说明/提示

In the first example, you can choose the first and third games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_3}{100}\right) \cdot (w_1 + w_3) = \left(\frac{80}{100}\cdot \frac{50}{100}\right) \cdot (80 + 200) = 112 $ .

In the second example, you can choose the first and second games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_2}{100}\right) \cdot (w_1 + w_2) = \left(\frac{100}{100}\cdot \frac{100}{100}\right) \cdot (1 + 1) = 2 $ .

In the third example, you can choose only the second game. In this case, the expected value of winnings will be $ \frac{p_2}{100} \cdot w_2 = \frac{2}{100} \cdot 1000 = 20 $ .

## 样例 #1

### 输入

```
3
80 80
70 100
50 200```

### 输出

```
112.00000000```

## 样例 #2

### 输入

```
2
100 1
100 1```

### 输出

```
2.00000000```

## 样例 #3

### 输入

```
4
1 100
2 1000
2 100
3 1```

### 输出

```
20.00000000```

## 样例 #4

### 输入

```
5
34 804
78 209
99 191
61 439
90 79```

### 输出

```
395.20423800```

# 题解

## 作者：LKY928261 (赞：11)

~~闲话：赛时卡 C 卡太久了没来得及做，第二天和同学讨论了才做出来。~~

感谢 @[dxbt](https://www.luogu.com.cn/user/189410) 与 @[liuhengxi](https://www.luogu.com.cn/user/222088) 提供了主要解题思路。

## Solution

### Part 1

将所有 $(p_i,w_i)$ 二元组按照 $p_i$ 进行分组。

首先 $p_i=100$ 的不会影响收益倍率，一定是全部选上，读入时特判掉。

而当两个二元组的 $p_i$ 相等时，我们会优先选择 $w_i$ 较大的。所以每一组内部一定是按 $w_i$ 从大往小选。

由于选择的顺序不影响贡献，不妨钦定先把 $p_i=p$（$1 \le p \le 99$）的组全部选完。假设该组内的最优选择方案是选 $w_i$ 的前 $k$ 大，选出的 $w_i$ 的和为 $s$，最小值为 $mn$。

既然最优，那么从选出的数中删除任意一个都一定不优于原方案。而删数时删最小值更优，于是：

$$
\begin{aligned}
(p\%)^k \times s &> (p\%)^{k-1} \times (s-mn)\\
&\ge (p\%)^{k-1} \times \frac{k-1}{k} \cdot s
\end{aligned}
$$

得到 $p\% > \frac{k-1}{k}$，即 $k < \frac{1}{1-p\%}=\frac{100}{100-p}$。

所以 $p_i<100$ 中选出的总个数 $m$ 不超过 $\sum_{p=1}^{99}\lfloor\frac{100}{100-p}\rfloor=481$。

这部分在代码实现上就是把每个 $w_i$ 扔进对应 $p_i$ 的大根堆，然后在第 $p$ 个堆中取出前最多 $\lfloor\frac{100}{100-p}\rfloor$ 个作为候选。

### Part 2

考虑 01 背包，$w_i$ 表示物品重量，$p_i$ 为权值，总权值为选中物品的权值之积，要求最大化总权值。

跑完背包后，枚举每个 $\sum w_i$，乘上对应的权值再取最大值即可。注意这里不要忘记把 $p_i=100$ 的加回来。

时间复杂度 $O(mW)$，其中 $W$ 为背包值域。

但你注意到一个问题：这个 $W$ 是不是还是太大了？

其实你造几组数据再感性理解一下就会发现最后的 $\sum w_i$ 实际是不大的。那么只要能求出这个上界就能缩小 $W$ 了。

设选出的物品里 $\sum w_i = s$，$\prod (p_i\%) = t$。

根据最优性，从中删去一个物品 $(p,w)$ 一定不优。故：

$$
\begin{aligned}
t \times s &\ge \frac{t}{p\%} \times (s-w)\\
p\% \cdot s &\ge s-w\\
s &\le \frac{w}{1-p\%}
\end{aligned}
$$

题目保证了 $w \cdot p \le 2 \times 10^5$，变形得 $w \le \frac{2 \times 10^5}{p}$，代入得：

$$
s \le \frac{w}{1-p} \le \frac{(\frac{2 \times 10^5}{p})}{1-p\%} = \frac{2 \times 10^7}{p(100-p)}
$$

当 $p$ 取 $1$ 或 $99$ 时，上式取最大值 $\frac{2 \times 10^7}{99}$，即 $s<202021$。

这样就能直接把 $W$ 缩小到一个可接受的范围内了。

事实上把 $W$ 开小到 $2 \times 10^5$ 也能过，但我不会证也不会 hack，不过也不影响做题就是了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=210000;
ll n,x,y,k,a[500],i,j;double s,d[_];priority_queue<ll>b[101];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;d[0]=1;
	for(i=0;i<n;i++){
		cin>>x>>y;
		if(x==100)k+=y;else b[x].push(y);
	}
	for(i=1;i<=99;i++){
		for(y=100/(100-i);y&&b[i].size();y--){
			x=b[i].top(),b[i].pop();
			for(j=_;j-->x;)d[j]=max(d[j],d[j-x]*i/100);
		}
	}
	for(i=0;i<_;i++)s=max(s,(i+k)*d[i]);
	cout<<setprecision(7)<<fixed<<s<<'\n';
}
```

---

## 作者：HaneDaniko (赞：5)

一个比较明显的暴力思路是，如果我们钦定选定的物品的价值，那么可以比较容易地由背包 DP 算出能达到这个钦定值的最大概率。

从 $[0,\sum w_i]$ 枚举所有可能的价值，暴力跑若干次背包，可以通过高达六个测试点。

一个比较简单的优化是，你发现你根本就不用钦定选定价值，直接跑一遍背包就能把所有答案跑出来，但是因为太简单了，仍然只有六个测试点的高分。

因此我们再上几个优化。

第一个优化是对我们枚举上界的优化。

推一遍式子，考虑设当前 $\prod \frac{p_i}{100}=x,\sum w_i=y$，当加入物品 $(p,w)$ 时对答案有正贡献，当且仅当：

$$\begin{aligned}xy&\lt x\times \frac{p}{100}\times (y+w)\\y&\lt \frac{p}{100}(y+w)\\(1-\frac{p}{100})y&\lt\frac{p}{100}w\\y&\lt\frac{pw}{100-p}\end{aligned}$$

由于题目规定 $pw\le 2\times 10^5$，而 $100-p$ 的下界是 $1$（详见优化 $2$，$p=100$ 的物品已经被我们特判掉了），因此加入物品 $(p,w)$ 时对答案有正贡献的一个必要条件是 $\sum\limits w_i\le 2\times 10^5$。

这样我们就将答案区间 从 $[0,\sum w_i]$ 降到 $[0,2\times 10^5]$ 了。

但是复杂度还是不对，我们再考虑其他优化。

第二个优化是，我们贪心地想，选择 $p_i=100$ 的 $i$ 一定是最优的，因此我们可以提前将 $p_i=100$ 的 $i$ 全部选上，这样既压缩了答案区间也减少了物品数量。

第三个优化是，我们观察剩下的 $p_i\neq 100$ 的物品，如果我们将 $p_i$ 相同的 $i$ 分成同一组，并且让每一组内按照 $w_i$ 降序排列，根据贪心思路，当 $p$ 相同的时候，应该是 $w$ 越大越好，最终答案一定是形如从每个 $p_i$ 的组内选出一个前缀。

和刚才的思路类似，现在我们钦定我们选择的物品的 $p_i$ 都为 $p$，如果我们在当前 $p$ 的组内选择的数量从 $k$ 增加到 $k+1$，答案更优当且仅当（这里给每个概率挂分母太麻烦了，在下面几个式子里钦定 $p=\frac{p_i}{100}$）。

$$\begin{aligned}p^k\times \sum\limits_k w\lt p^{k+1}\times(w_{k+1}+\sum\limits_k w)\end{aligned}$$

由于新加入的 $w_{k+1}$ 不大于已有的任何一个数，因此有 $k\times w_{k+1}\le\sum\limits_k w_i$，因此：

$$p^k\times \sum\limits_k w\le p^{k+1}\times\frac{k+1}{k}\times\sum\limits_k w_i$$

$$\frac{k}{k+1}\lt p$$

$$k\lt kp+p$$

$$k\lt \frac{p}{1-p}$$

这个式子意味着只有前 $\frac{p}{1-p}$ 个物品有可能成为最优解。

因此将可能成为最优解的物品拿出来跑一边背包即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int p[200001],w[200001];
struct item{
    int w,p;
}a[200001];
int cnt=0;
long long orians;
long double f[200001];
long double ans;
vector<int>v[101];
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
    	cin>>p[i]>>w[i];
    	v[p[i]].push_back(w[i]);
    	if(p[i]==100) orians+=w[i];
	}
    for(int i=1;i<=100;++i){
        sort(v[i].begin(),v[i].end(),greater<int>());
    }
	for(int i=1;i<=99;++i){
        int tot=0;
	    for(int j=0;j<=(int)v[i].size()-1;++j){
	    	if(tot>100/(100-i)) break; 
	    	a[++cnt]={v[i][j],i};
            tot++;
		}
	};
	f[0]=1;
	for(int i=1;i<=cnt;++i){
	    for(int j=200000;j>=a[i].w;--j){
	        f[j]=max(f[j],f[j-a[i].w]*a[i].p/100.0);
        }
    }
	for(int i=0;i<=200000;++i){
        ans=max(ans,f[i]*(orians+i));
    }
	printf("%.8Lf",ans);
}
```

---

## 作者：SwordDance (赞：4)

因为做过类似的 trick，很快就做出来了，可惜要上晚自习赛时没打。

根据人类直觉，选择的物品一定不会很多，我们考虑把这一性质具体化。

根据 $p_i$ 分组，考虑一组最多选多少个。显然，$w_i$ 相等时，选出的物品数最多。那么记 $\frac{p_i}{100}=p$ ( $p_i\ne 100$ )， 最多选 $n$ 个，有如下式子：

$$p^{n+1}\times w\times (n+1)-p^n\times w \times n<0$$

含义为选 $n+1$ 个物品劣于选 $n$ 个物品。
将两边公共项去除，得：

$$p\times n+p-n<0$$

$$n< \frac{p}{1-p}$$

$$n<-1+\frac{1}{1-p}$$

也就是每一组最多选的物品数。注意到这个式子是调和级数，也就是说总共可能选取的物品数一定小于 $1000$。 (实际上不到 $500$)

同时，注意到题目另一个神秘条件 $p_i\times w_i<2\times 10^5$，由上式推出的 $p_i$ 组至多选不到 $p_i$ 个，所以最优解选出的 $\sum w_i <2\times 10^5$，记 $f_j$ 为 $\sum w_i=j$ 时的 $\prod \frac{p_i}{100}$ 的最大值，特判掉 $p_i=100$ 的情况，跑 $01$ 背包即可。

[类似的 trick。](https://www.luogu.com.cn/problem/P11058)

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
const int N=2e5+3;
int n,p,w,num,a[N],b[N];
LL sum;
LD f[N],ans;
vector<int>v[102];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d%d",&p,&w);
    	v[p].emplace_back(w);
    	if(p==100) sum+=w;
	}
	for(int i=1;i<=99;i++){
	    sort(v[i].begin(),v[i].end());
	    int x=100/(100-i);
	    for(int j=v[i].size()-1;j>=0;j--){
	    	if(v[i].size()-j>x) break; 
	    	a[++num]=v[i][j];
	    	b[num]=i;
		}
	};
	f[0]=1;
	for(int i=1;i<=num;i++)
	    for(int j=N-3;j>=a[i];j--)
	        f[j]=max(f[j],f[j-a[i]]*b[i]/100);
	for(int i=0;i<=N-3;i++) ans=max(ans,f[i]*(sum+i));
	printf("%.10Lf",ans);
	return 0;
}

```

---

## 作者：win114514 (赞：4)

赛时被创四了。

### 思路

考虑我们什么时候合并会比原来优。

例如，我们现在要合并 $p_1,w_1$ 和 $p_2,w_2$，同时保证，$w_1\ge w_2$。

那么有：

$$
\frac{p_1}{100}\times w_1\le \frac{p_1}{100}\times \frac{p_2}{100}\times (w_1+w_2)\\
\frac{p_2}{100}\times w_2\le \frac{p_1}{100}\times \frac{p_2}{100}\times (w_1+w_2)
$$

转换一下：

$$
\frac{p_1}{100}\times (\frac{p_2}{100}\times (w_1+w_2)-w_1)\ge 0\\
\frac{p_2}{100}\times (\frac{p_1}{100}\times (w_1+w_2)-w_2)\ge0
$$

由于 $p1,p2\ge 1$。

$$
\frac{p_2}{100}\times (w_1+w_2)-w_1\ge 0\\
\frac{p_1}{100}\times (w_1+w_2)-w_2\ge0
$$

所以：

$$
\frac{100-p_2}{100}w_1\le \frac{p_2}{100}w_2\\
\frac{p_1}{100}w_1\ge \frac{100-p_1}{100}w_2
$$

消掉系数。

$$
\frac{(100-p_1)w_2}{p_1}\le w_1\le \frac{p_2w_2}{100-p_2}\\
$$


这个不等式可以推出 $w_1\le p_2w_2$。

这告诉我们当 $w$ 的和超过 $p_2w_2$ 时，合并一定不优。

那么去掉 $p=100$ 的情况，所有选出的 $w$ 一定小于等于 $4\times 10^5$。

这种情况下，我们可以做一个背包。

复杂度是 $O(nV)$ 的。

接着，我们可以发现，有很多二元组是没有用的。

具体来说，对于 $p$ 相同的二元组，我们按 $w$ 从大到小排序以后。我们采用的一定是一段前缀。

而这一堆前缀的总和也没有很多，大约是 $99\times \ln99$。

因此我们可以在加入一个二元组的时候判断一下是否对背包产生了贡献，如果没有，那么之后相同的 $p$ 就没有必要加入背包了。

### Code

```cpp
/*
  ! 前途似海，来日方长。
  ! Created: 2024/10/20 18:08:39
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using pii = pair<int, int>;

bool ST;
const int N = 1e6 + 10;
const int mod = 998244353;

int n, m, vs[N];
double sm;
double ns;
double f[N];
struct Node {
  int p, w;
  inline bool operator<(const Node&tmp) const { return w > tmp.w; } 
} d[N];

signed main() {
  JYFILE19();
  cin >> n;
  fro(i, 1, n) cin >> d[i].p >> d[i].w;
  sort(d + 1, d + n + 1);
  f[0] = 1;
  fro(i, 1, n) {
    if (d[i].p == 100) sm += d[i].w;
    else {
      if (vs[d[i].p]) continue;
      int h = d[i].p * d[i].w / (100 - d[i].p);
      double r = d[i].p / 100.;
      bool flag = 0;
      pre(j, h, 0)
        if (f[j + d[i].w] < f[j] * r)
          f[j + d[i].w] = f[j] * r, flag = 1;
      if (flag == 0) {
        vs[d[i].p] = 1;
      }
    }
  }
  fro(i, 0, 400000) ns = max(ns, (i + sm) * f[i]);
  printf("%.9lf\n", ns);
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 32;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}
```

---

## 作者：Acoipp (赞：3)

挺有趣的 DP 剪枝。

考虑直接暴力，我们发现 $p$ 和 $w$ 至少要记录一维才能够转移，显然不能记 $p$，于是我们记 $f_{j}$ 表示 $w$ 的和为 $j$ 的时候，$\prod_{i} \frac {p_i}{100}$ 的最大值是多少。

除此之外，还有一个显然的贪心，如果我们相同的 $p_i$ 选了 $k$ 个，那么这 $k$ 个一定是按照 $w_i$ 从大到小排序的前 $k$ 个。

只有上面两个方向不好优化，并且题目中的 $p_iw_i \le 2\times 10^5$ 还没有用到，于是我们考虑最终答案的形态，假如最终选择了若干 $(p_i,w_i)$，假如删去一个能够使其变大，设删去 $(p_j,w_j)$ 使整个答案变大，那么我们要满足：

$$
\frac{\prod_i \frac{p_i}{100}}{\frac{p_j}{100}} (\sum_{i} w_i-w_j) \ge \prod_i \frac{p_i}{100} \sum_i w_i
$$

化简一下，有：

$$
(100-p_j) (\sum_{i} w_i-w_j) \ge  p_jw_j
$$

当 $p_j=100$ 的时候，显然无论如何 $j$ 必选，又因为右边最高取到 $2 \times 10^5$，所以当左边取到 $2 \times 10^5$ 的时候，这个方法一定不优。

因此，$\sum w$ 的范围一定不超过 $2 \times 10^5$，于是我们可以直接 DP 优化，不过直接这么做的话时间复杂度是 $O(n^2)$。

考虑优化，因为之前提到相同的 $p$ 只会选前面几个，所以按照这个直接优化即可，即选中的 $w$ 不能超过 $2 \times 10^5$ 且如果 $(p_i,w_i)$ 被选中，转移的下标不会超过 $p_iw_i$。

按照这个即可通过本题，时间复杂度不太会分析，但是取到上界是远远跑不满的。

---

## 作者：xyin (赞：3)

感觉这道题的优化真神奇，没见过。

首先考虑最暴力的做法，设 $f_{i,j}$ 表示考虑了前 $i$ 个物品，权值为 $j$ 时的最大概率，（肯定不能反过来设啊，所有 $p_i$ 相乘数组都开不下）然后跑 01 背包。但是 $\sum\limits w_i$ 太大了，我们还是做不了。

接下来就是一堆优化：

1. 这是一个贪心，考虑当 $p_i=100$ 的时候，我们肯定得选，因为答案一定能变得更优，所以我们在读入的时候直接把 $p_i=100$ 的判掉就好。

2. 考虑什么样的物品能使贡献增大，设当前的 $\prod\limits \cfrac{p_i}{100}=X,\sum\limits w_i=Y$，加进来的物品概率为 $P$，权值为 $W$，则一定满足下面这个式子：

   $$\begin{aligned}XY &\le X\times \cfrac{P}{100}\times (Y+W)\\
            Y&\le \cfrac{P}{100}\times (Y+W)\\
            Y&\le \cfrac{P}{100}\times Y+\cfrac{P}{100}\times W\\
            \cfrac{100-P}{100}\times Y&\le \cfrac{P}{100}\times W\\
            Y&\le \cfrac{PW}{100-P}
            \end{aligned}$$

   把这个式子带进数据范围，我们能得到 $\sum w_i\le 2\times 10^5$ 的时候，加进来物品才能有正贡献，这样我们就能跑 $O(n^2)$ 的 DP 了。

3. 这又是一个贪心，我们发现 $p_i$ 的值域很小，考虑当 $p_i$ 相等的时候，我们一定是选择更大的 $w_i$，才能让答案变得更优。所以我们对于相同的 $p_i$ 按 $w_i$ 从大到小排序后，一定是选择一个前缀，统计到答案中。但是这貌似对我们的 DP 没有任何优化，那接下来再来考虑这个前缀的特性。

4. 考虑当 $p_i$ 相同的时候，从大到小贪心的选一个前缀，但什么时候答案一定有正贡献呢？设在概率为 $P=\cfrac{p_i}{100}$ 时选了前 $k$ 个物品，此时的权值和为 $\sum w$，第 $k+1$ 个物品的权值为 $W$，则一定满足下面这个式子：

   $$P^k\times \sum w\le P^{k+1}\times (\sum w+W)$$

    由于我们从大到小排序后 $\sum w$ 一定要 $\ge k\times W$，则 $W\le \cfrac{\sum w}{k}$，所以带进去得：

   $$\begin{aligned}P^k\times \sum w&\le P^{k+1}\times \sum w\times (\cfrac{k+1}{k})\\
            \cfrac{1}{P}&\le \cfrac{k+1}{k}\\
            k&\le P\times k+P\\
            (1-P)\times k&\le P\\
            k&\le \cfrac{P}{1-P}\\
            k&\le \cfrac{p_i}{100-p_i}
            \end{aligned}$$

   写个代码从 $p_i\in[0,99]$ 跑一遍，发现总和居然是 $\le 500$ 的！
        
总结以上思路，$p_i$ 的取值范围很小，何不把所有 $p_i$ 相等的分组，同组内只能选前 $k=\cfrac{p_i}{100-p_i}$ 个，然后再去跑 01 背包呢？复杂度为 $O(2\times 10^5\times 500)$。

[代码放在这儿仅供参考](https://www.luogu.com.cn/paste/5r7cxx5x)

---

## 作者：WRuperD (赞：2)

# CF2023D Many Games 题解

[本文在我的博客同步发表。](https://wruperd.github.io/post/2024-10-22-solution-cf2023d/)

非常像我会做的题目。要是我打 CF 的时候不去吃完饭，不打摆感觉还是非常有机会做出来的。

首先考虑什么样的物品才能使答案增大。不妨设当前的 $\prod\limits_i {p_i\over 100} = X,\sum\limits_i w_i = Y$。

$$ \begin{align} 
XY <& X {p_i \over 100} (Y+w_x) \\
Y <& {p_i \over 100} (Y+w_x) \\
Y <& {p_i \over 100} Y+{p_i \over 100}w_x \\
(1-{p_i \over 100})Y <& {p_i \over 100}w_x \\
Y <& {{p_i \over 100}w_x \over (1-{p_i \over 100})} \\
Y <& {p_i \cdot w_x \over (100-p_i)} \\

\end{align}$$

所以我们得出结论当当前重量大于 $2.1 \cdot 10^5$ 左右时必然不会有新增的物品。（赛时怎么到这里就直接莽上去了qwq）。   

如果你按照 $p_i$ 分组，按照 $w_i$ 从大到小排序的话，我们每次一定是取一段前缀。猜想这个前缀的长度并不长，原因也比较简单，就是考虑当前加进去 $w$ 要更优。 

$$ \begin{align} 
p^k \cdot W &< p^{k+1} \cdot (W+minw) \\
 &\leq p^{k+1} \cdot W {k+1\over k} \\
 p &> {k+1 \over k} \\
 kp & > k+1\\
 k & > {1\over p-1} \\
 k & < {100 \over 100 - p_i} \\
\end{align}$$

所以你照着取一起下物品总数是极少的。最后你直接做一个背包就行了。

```cpp
// Problem: Many Games
// URL: https://www.luogu.com.cn/problem/CF2023D
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 21e4 + 10;
double f[MAX];

priority_queue <int> que[MAX];

void solve(){
	int n = read();
	double preans = 0;
	for(int i = 1; i <= n; i++){
		int p = read(), w = read();
		if(p == 100){
			preans += w;
		}else{
			que[p].push(w);
		}
	}
	f[0] = 1.0;
	for(int i = 1; i <= 99; i++){
		int lim = 100 / (100 - i) + 1;
		while(!que[i].empty() and lim--){
			int u = que[i].top();
			que[i].pop();
			for(int j = MAX - 10; j >= u; j--){
				f[j] = max(f[j], f[j - u] * (double)(i) / 100.0);
			}
		}
	}
	double ans = 0;
	for(int i = 0; i < MAX; i++){
		ans = max(ans, double(i + preans) * f[i]);	
	}
	printf("%.7f\n", ans);
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：weirdoX (赞：2)

## CF2023 - D. Many Games

先让 $p$ 除以 $100$，相当于给你两个数组 $p, w$，然后要选择下标集合 $S$，使得：

**$p$ 的积乘上 $w$ 的和**最大化。

注意到 $p_i$ 是整数，并且 $1\le p_i \le 100$。

那么容易想按照 $p_i$ 分类。

然后 $w_i$ 对于固定 $p$ 一定是选择排序后的最大值后缀。

目前 $(P,Q)$，考虑选择 $i$：
$$
P\cdot W \to P\cdot p_i\times(W+w_i)
$$
一定是后面的式子大于前面的式子才会选择，考虑做比例，那么不等式就是：
$$
p_i+\frac{p_i\cdot w_i}{W} > 1\\
p_i\cdot w_i>(1-p_i)\cdot W
$$
把 $p$ 再乘回去：
$$
p_i\cdot w_i>(100-p_i)\cdot W
$$
题意有：$p_i\cdot w_i \le 2\cdot 10^5$。

所以 $W$ 最后不会很大，只会在 $2\cdot 10^5$ 以内。

然后我们考虑按 $p_i$ 分类。

假设选择了某个 $p_i$ $c$  个，然后考虑选入的最小的值是 $w_i$，考虑它不能删除时：

令：$q_i=p_i/100$：
$$
P\cdot q_i^c\times(W+w_i\cdot c+\Delta) > P\cdot q_i^{c-1}\times(W+w_i\cdot(c - 1) + \Delta)\\
q_i\cdot(W+w_i\cdot c+\Delta) > W+w_i\cdot(c - 1) + \Delta\\
(q_i-1)\cdot w_i\cdot c > (W + \Delta)(1-q_i) -w_i
$$
然后只需要考虑 $\Delta=0$ 的情况，限制更加严格：
$$
(q_i-1)\cdot w_i\cdot c > W(1-q_i) -w_i\\
c < -\frac{W}{w_i}+\frac{1}{1-q_i}<\frac{100}{100-p_i}
$$
也就是说对于一种概率 $p_i$ 的物品，最多选择 $\frac{100}{100-p_i}$ 个
$$
\sum_{i=0}^{99}\frac{100}{100-p_i} = 100\ln 100\approx482
$$
然后对于概率等于 $100$ 的物品无脑全部选入即可。

这里直接用 $dp_{i,j}$ 表示考虑完前 $i$ **种**物品，目前 $W=j$ 时的最大的 $P$。

最终复杂度就是 $O(2\cdot 10^5\times 482)$。

[代码](https://codeforces.com/contest/2023/submission/287289545)

---

## 作者：Pengzt (赞：1)

# Many Games

[题目链接](https://www.luogu.com.cn/problem/CF2023D)。[cnblogs](https://www.cnblogs.com/Pengzt/p/18667684)。

### Problem

给你 $n$ 个物品，每个物品有一个概率 $p_i$ 和权值 $w_i$。如果选中某个物品 $i$，那么有 $p_i\%~(1\le p_i\le 100)$ 的概率中奖并获得 $w_i$， 然后假设你选了一个集合 $S$，当且仅当集合内的物品**都中奖了**，才能获得集合内的 $\displaystyle\sum_{i\in S} w_i$。定义一个集合的价值 $f(S)$ 为
$$
\forall i\in S, \Big(\prod_i\frac{p_i}{100}\Big)\cdot\Big(\sum_{i}w_i\Big)
$$
求 $f(S)$ 的最大值。

数据范围：$1 \le n \le 2 \times 10^5$，$1 \le w_i, p_i\cdot w_i \le 2 \times 10^5$。

### Sol

首先 $p_i = 100$ 的点是一定会选的。然后如果 $p_i$ 相同的话，我一定是从大到小的选择 $w_i$。然后感觉一下，如果 $w_i$ 相差不大的话，概率越小的数选的个数也会越少，不然一定不优。考虑具体的分析一下这个东西。不妨令当前的物品的概率为 $p$（此时 $p \in (0, 1)$），物品的价值为 $\large\frac{w_{max}}{100p}$（更小肯定更劣），集合中暂时没有数（有数的话影响会更大，因为它会使之前的值变小）。设这类物品选了 $x$ 个，则 $f$ 为 $p^x \cdot x \cdot \frac{w_{\max}}{100p} = p^{x - 1}x\frac{w_{\max}}{100}$。于是这个东西就只和 $p^{x - 1}x$ 有关。不妨令 $g(x) = p^{x - 1}x$，则 $g'(x) = p^{x - 1}\ln(p)x + p^{x - 1}$。当 $p^{x - 1} + xp^{x - 1} \ln p = 0$ 时 $g(x)$ 有最大值。$p^{x - 1} = -p^{x - 1}\times x\ln p$。$x \ln p = -1$ 时有最小值。则 $x = \frac{1}{\ln \frac{1}{p}}$。当 $p = 0.99$ 时有最大值 $100$。最后直接把每个 $p$ 对应的元素全部拉出来跑一遍背包即可。然后这个东西的个数只有五百个左右就做完了。

这道题 `double` 是够用的，`long double` 可能会比较卡时间。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
mt19937_64 eng(time(0) ^ clock());
template <typename T>
T rnd(T l, T r) { return eng() % (r - l + 1) + l; }
typedef double ld;
int n;
int w[200005];
ld f[300005];
vector<int> p[105];
int main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= n; ++i) {
		scanf("%d%d", &x, w + i);
		p[x].emplace_back(w[i]);
	}
	f[0] = 1;
	for (int i = 1; i < 100; ++i) {
		sort(p[i].begin(), p[i].end(), greater<int> ());
		int lim = ceil(1 / log((ld) 100 / i));
		while ((int) p[i].size() > lim)
			p[i].pop_back();
		for (int j : p[i])
			for (int k = 300000; k >= j; --k)
				f[k] = max(f[k], f[k - j] * i / 100);
	}
	ll s = 0;
	for (int i : p[100]) s += i;
	ld ans = 0;
	for (int i = 0; i <= 300000; ++i)
		ans = max(ans, f[i] * (i + s));
	printf("%.8lf\n", ans);
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：1)

~~我去，没看见 $p_i$ 是整数，这我做个集贸啊。~~\
先把 $p_i$ 转成真实的概率，每个物品选或不选，考虑背包来处理，想要得出转移的信息，必须要知道上一个的概率和价值，等价值概率越大越好，等概率价值越大越好。\
概率肯定不能作为状态，所以设 $f_{i,j}$ 表示前 $i$ 个物品，选出的价值是 $j$ 时的最大概率，转移 $f_{i,j}=\max(f_{i-1,j},f_{i-1,j-w_i}p_i)$。
这时直接暴力 DP 的复杂度是 $\mathcal{O}(n\sum w_i)$ 的，现在来深挖一下题目的性质。\
答案的形态很优美，具有单调性，无论少选一个还是多选一个都不优，形如单峰的样子。\
首先，概率为 $1$ 的一定选，否则，对于同等概率，肯定选价值大的更优，根据单调性，选的一定是一个前缀最大值，考虑得出最多能选多少个，如果价值都一样，那么选的一定最多，否则小的会影响大的贡献，停止选择更早，设选择 $i$ 个的时候，第一次比上一次劣，概率是 $p$，价值是 $w$。
$$
\begin{aligned}
&p^iwi<p^{i-1}w(i-1)\\
&pi<i-1\\
&(1-p)i>1\\
&i>\frac{1}{1-p}
\end{aligned}
$$
所以最多选择 $\frac{1}{1-p}$，所有的概率加和是一个调和级数，也就是说，真正有用的数不超过 $700$ 左右，这样 DP 的复杂度上界为 $\mathcal{O}(700\sum w_i)$，但是值域还是很大，题目还有一个性质没用 $p_iw_i\le 2\times 10^5$，转成真实概率之后就成了 $p_iw_i\le 2\times 10^3$。\
还是根据答案的单调性，设 $i$ 答案的个数加一，设 $sum$ 表示当前价值和，$p$ 表示当前概率，假设删掉了 $j$ 物品。
$$
\begin{aligned}
&psum<\frac{p}{p_j}(sum-w_j)\\
&p_jsum<sum-w_j\\
&(1-p_j)sum>w_j\\
&sum>\frac{w_j}{1-p_j}\\
\end{aligned}
$$
所以最大的价值和不大于 $\frac{w_j}{1-p_j}$，这个最大是 $2\times 10^5$，所以值域的范围也得出来了，这时复杂度已经完全正确了，实际上远远不到这个上界，直接 01 背包就行了。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int R(int n){return myrand()%n+1;}
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10,mod=998244353,inf=1e9;
inline void Min(int &x,int y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
int n,num,a[N],sum;
double f[N],b[N],ans;
std::vector<int> v[105];
signed main(){
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    n=read();for(int i=1;i<=n;++i){
        int p=read(),w=read();
        if(p==100){sum+=w;continue;}
        v[p].eb(w);
    }
    for(int i=1;i<100;++i){
        if(v[i].size()==0)continue;
        double la=0,p=1,sm=0,gai=i*1.0/100;
        std::sort(v[i].begin(),v[i].end(),std::greater<int>());
        for(int j=0;j<v[i].size();++j){
            p*=gai;sm+=v[i][j];
            if(sm*p<la)break;
            la=sm*p;
            a[++num]=v[i][j],b[num]=gai;
        }
    }
    f[0]=1;
    for(int i=1;i<=num;++i)for(int j=N-10;j>=a[i];--j)f[j]=std::max(f[j],f[j-a[i]]*b[i]);
    for(int i=0;i<=N-10;++i)ans=std::max(ans,f[i]*(i+sum));
    printf("%.15lf\n",ans);
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2023D)

**题目大意**

> 给定 $n$ 个物品 $(p_i,w_i)$，选出若干个元素，最大化 $\prod p_i\sum w_i$，其中 $p_i=1\%\sim 100\%$。
>
> 数据范围：$n\le 2\times 10^5,w_i\times p_i\le 2000$。

**思路分析**

记 $P=\prod p_i,S=\sum w_i$。

设 $p_i=p$ 的元素选择了 $k$ 个，那么删去最小值后的权值不优于当前方案，故 $p^kS> p^{k-1}\dfrac{k-1}kS$，从而 $k<\dfrac{1}{1-p}$。

因此可以把元素个数优化到 $P\ln P$ 级别，其中 $P=100$。

从最优解中删除一个元素，不可能更优，故：$PS>\dfrac{P}{p_i}(S-w_i)$，从而 $S<\dfrac{w_i}{1-p_i}$，由于 $w_ip_i\le 2000$。

因此 $w_i\le \dfrac{2000}{(1-p_i)p_i}$，在 $p_i=1\%$ 时取到最小值，大约为 $\mathcal O(VP)$ 级别，其中 $B=2000$。

然后按 $S$ 暴力背包即可。

时间复杂度 $\mathcal O(n\log n+VP^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ld long double
using namespace std;
const int MAXN=2e5+5,Q=100;
vector <int> A[105];
int n,p[MAXN],w[MAXN];
ld f[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&p[i],&w[i]),A[p[i]].push_back(i);
	vector <int> it;
	for(int p=1;p<Q;++p) {
		sort(A[p].begin(),A[p].end(),[&](int i,int j){ return w[i]>w[j]; });
		int c=min((int)A[p].size(),Q/(Q-p)+1);
		for(int i=0;i<c;++i) it.push_back(A[p][i]);
	}
	f[0]=1;
	for(int i:it) for(int j=MAXN-1;j>=w[i];--j) {
		f[j]=max(f[j],f[j-w[i]]*p[i]/100);
	}
	ld s=0,z=0;
	for(int i:A[Q]) s+=w[i];
	for(int j=0;j<MAXN;++j) z=max(z,(j+s)*f[j]);
	printf("%.20Lf",z);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

水题解/se

首先肯定去利用概率只有 $100$ 种这个条件。

首先概率为 $100\%$ 的肯定选。然后对同种概率的肯定优先选价值最高的。那么显然可以注意到选的数量很少，不然概率会接近于 $0$。具体有多小呢，设 $f(x)=P^xx$，那么最大值在 $f'(x)=\ln PP^xx+P^x=0$ 即 $x=\dfrac{1}{\ln\frac 1P}$ 处取到。

$\sum_{i=1}^{99} \dfrac{1}{\ln\frac{100}{i}}$ 比较小。做个背包就行了。

---

