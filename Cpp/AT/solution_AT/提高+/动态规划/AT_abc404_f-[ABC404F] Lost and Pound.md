# [ABC404F] Lost and Pound

## 题目描述

青木和高桥在玩一个游戏。场上有 $N$ 个按钮，其中 $1$ 个是关键按钮，剩下的 $N-1$ 个是普通按钮。

青木知道哪一个按钮是关键按钮，而高桥并不知道，也就是说，高桥无法将这 $N$ 个按钮相互区分。

在游戏中，以下事件将会被重复 $T$ 次：

1. 青木将这 $N$ 个按钮按随机的顺序摆放。
2. 高桥进行 $M$ 次操作，每次操作中他将选择一个按钮并按下它一次。在这个过程中他可以选择按下同一个按钮多次。
3. 青木告诉高桥从游戏开始至今，关键按钮被高桥按下了多少次。

高桥获胜当且仅当关键按钮在这 $T$ 轮过程中被他按下了至少 $K$ 次。请你求出当高桥以最优策略游玩游戏时，他获胜的期望，并以浮点数的形式输出。

## 说明/提示

**样例 1 解释**

这是一种可能的游戏进展（不保证在下面描述的过程中高桥采用了最佳策略）：
- 第一轮
  - 青木随机摆放了按钮，此时关键按钮放在位置 $1$。
  - 高桥选择按下位置 $1$ 和位置 $2$ 的按钮。
  - 青木告诉高桥关键按钮已经被按下 $1$ 次。
- 第二轮
  - 青木随机摆放了按钮，此时关键按钮放在位置 $3$。
  - 高桥两次选择按下位置 $3$ 的按钮。
  - 青木告诉高桥关键按钮已经被按下 $3$ 次。
- 游戏结束时，关键按钮被按下了至少 $3$ 次，所以高桥获胜了。

这组数据的标准答案是 $\frac{2}{9}$，因此对应地输出 $0.222222$ 或 $0.222223141592$ 会被认为是正确的。

By chenxi2009

## 样例 #1

### 输入

```
3 2 2 3```

### 输出

```
0.222222222222222```

## 样例 #2

### 输入

```
10 1 10 1```

### 输出

```
1.000000000000000```

## 样例 #3

### 输入

```
100 10 10 2```

### 输出

```
0.401263060761621```

# 题解

## 作者：Moya_Rao (赞：16)

~~你们的喵喵又来啦！~~

上次我写了一篇紫题题解，今天来写 ABC 404 F 的题解啦喵！

首先评价一下这个题目，嗯非常的不错啊喵，但是一眼看上去很难的感觉。一做发现其实并不难的喵，大家千万不要怕呀喵。

好的咱们来说下题意喵。

小 B 有 $n$ 个按钮，其中有一个按钮是**特殊按钮**，其他 $n-1$ 个按钮都是**普通按钮**。在视觉上是无法区分特殊按钮与普通按钮的喵！当然，小 B 是清楚的啦喵。

现在要进行 $t$ 轮游戏喵。每一轮游戏开始前，小 B 都会将这 $n$ 个按钮打乱排成一排喵。小 A 需要按下 $m$ 次按钮，他可以选择任何一个按钮并按下喵。一个按钮当然是可以在一轮中被按下多次的啦喵。

当这所有 $t$ 轮游戏结束以后，小 B 会告诉小 A 他一共按下了多少次特殊按钮呀喵。小 A 想知道，他在所有 $t$ 轮游戏结束后，按下特殊按钮的次数至少为 $k$ 的概率喵。误差不能超过 $10^{-6}$ 次方喵，不然会被判为错误答案喵！

接下来就是思路部分啦喵。有点长但很详细，大家要认真阅读哦喵。

这个题目一看就是概率 DP，是吧？那不就好办了吗喵，直接朝着这个方向去思考嘛喵！

喵，在本题中正着整是不大好弄的，因此我们反过来喵。咱们定义 $dp_{i,j}$ 表示当前游戏进行到第 $i$ 轮，距离按下特殊按钮 $k$ 次还剩 $j$ 次时的概率。当然了，咱把所有 $j<0$ 的都要缩减到 $j=0$ 的范围内，是吧喵？说是这么说，其实上却是把所有 $j>k$ 的都缩减到了 $j=k$ 的范围内呢喵！初始化 $dp_{0,k}=1$，最终答案也非常明了了吧喵，就是 $dp_{t,0}$ 喵！

好的喵，接下来一步就是状态转移了。这一步是最最重要的。

注意到按钮都是被小 B 乱序排列的，那我们在按下按钮的时候不妨假设只按下前 $len$ 个按钮，后面 $n-len$ 个按钮碰都不碰，这样是可以的，对吧喵？然后我们设第 $i$ 个按钮按下了 $a_i$ 次，也没问题吧喵？为了方便，咱们保证 $a_i \ge a_{i+1}$，还是 OK 的是吧喵？

好的叽里呱啦一大串终于是定下了分配喵。那么我们就根据每一种分配方法，来计算对应的概率就可以啦喵。

这样说也太模糊了吧喵！怎么计算概率？嘿嘿，你说到重点上来了喵！其实上很简单的，首先咱们有 $\frac{n-len}{n}$ 的概率是本轮没有按下特殊按钮的对吧，因为这个特殊按钮在后面那些本轮没有按到的按钮里面嘛喵！那这一部分就要用这个概率乘上 $dp_{i-1,j}$ 对吧喵。接下来就是那些在前面范围内的啦喵，也很简单的喵，枚举 $u$ 从 $1 \sim len$，又有 $\frac{1}{n}$ 的概率是要乘上 $dp_{i-1,\min(k,j+a_u)}$ 喵。为什么应该都清楚吧喵，因为我们这次按下了这个特殊按钮 $a_u$ 次呀喵！至于为什么要和 $k$ 取 $\min$，那是因为前面咱们说了所有 $j > k$ 都要压缩进 $j=k$ 的位置嘛喵！

那这样是不是就完成了喵？好像不对，有一步还没讲清楚喵！哪一步？就是拆分的那一步啦喵！我们的 $a$ 到底是咋整出来的喵？这也是个问题呀，对吧喵！别急喵，你听我说喵。

我们可以用一个 `vector` 类型的 `vector`（人类智慧做法哈哈），取名叫 $fp$（哈哈分配的拼音哈），然后让它来存储每一种分配方法喵。具体怎么存，怎么算喵？很简单喵，整个递归，一开始跑初始化，一个一个算就行了喵。具体来说，递归函数传上两个参数 $sum$ 和 $lst$ 喵，$sum$ 表示当前还能分配多少次，$lst$ 表示上个数分配了多少次喵。如果当前 $sum=0$，那么我们判断一下当前所存储的这种分配方法的长度是不是没有超过 $n$ 喵，因为超过 $n$ 就非法了喵。如果是符合要求的答案就扔到 $fp$ 里去喵！接下来就是递归环节了喵，枚举 $i=1 \sim \min(sum,lst)$（当然实际实现中用的是倒序枚举），这个 $i$ 就是本次所选取的次数啦喵！把它存进状态数组，继续递归就行了喵。记得回溯的时候要把这个玩意儿从状态数组里扔出去哦喵，要不然状态数组就全乱了喵！

这样，咱们就结束了本题。是不是还挺简单的喵？

最后我亮一个代码吧喵。是对照上面的思路来的喵。当然啦保证对的喵，不信看[提交记录](https://atcoder.jp/contests/abc404/submissions/65592940)嘛喵！当然请各位不要抄袭我的代码，多谢喵！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,m,k;double dp[35][35];
vector<int> now;vector<vector<int>> fp;
void Init_Makefp(int sum,int lst){
    if(!sum){
        if(now.size()<=n)
            fp.push_back(now);
        return;
    }
    for(int i=min(sum,lst);i>0;i--){
        now.push_back(i);
        Init_Makefp(sum-i,i);
        now.pop_back();
    }
    return;
}
int main(){
    cin>>n>>t>>m>>k;
    Init_Makefp(m,m);dp[0][k]=1.0;
    for(int i=1;i<=t;i++)
        for(int j=0;j<=k;j++)
            for(auto s:fp){
                double ans=dp[i-1][j]*(n-s.size());
                for(int u:s)ans+=dp[i-1][min(k,j+u)];
                dp[i][j]=max(dp[i][j],ans/n);
            }
    printf("%.10lf",dp[t][0]);
    return 0;
}
```

既然都看到这里了，还麻烦你给可爱的喵喵留下一个小小的赞吧，万分感谢喵！

---

## 作者：__vector__ (赞：6)

~~凭什么这题分值比差分约束板子的 G 低！我这种过 F 不过 G 的亏死了~~。    
### 难点  
拆答案的贡献。  
### 做法    
每次游戏都随机排列，意思其实就是每次游戏结束前，都得不到任何关于正确按钮的位置信息。    

那么，值得用于决策的信息就只剩下了当前的正确选择次数，当前剩下的游戏次数。   

首先，可以自然的想到定义 $f_{i,j}$ 代表还剩下 $i$ 次游戏可以玩，还需要选中 $j$ 次正确按钮才可以获得最终胜利。  

转移的话，考虑当前这次游戏怎么玩。  

似乎不是很好设计策略，那么来分析一下答案的贡献组成。  

本次游戏假设有 $x$ 个按钮的选中次数不为 $0$，其中第 $l$ 个按钮被选中了 $c_l$ 次。  

那么，每个按钮都有 $\frac{1}{n}$ 的概率是正确的按钮，此时状态推进到 $f_{i-1,j-c_l}$，贡献是 $\frac{1}{n}f_{i-1,j-c_l}$。  

有 $\frac{n-x}{n}$ 的概率所有 $x$ 个按钮都不是正确的按钮，贡献是 $\frac{n-x}{n}f_{i-1,j}$。  

所以，一种方案的答案就是 $\frac{1}{n}\sum\limits_{l=1}^n f_{i-1,j-c_l}+\frac{n-x}{n}f_{i-1,j}$。  

可以看出来，答案跟选择的按钮数量，每个被选择的按钮的操作次数有关，而且每个按钮的贡献都是独立的，可以累加。  

由此，可以对答案的第一项进行 dp，按钮数量也需要加入状态。  

令 $g_{i,j}$ 表示选择了 $i$ 个按钮，总共用了 $j$ 次操作，且每个按钮至少操作 $1$ 次，答案式子的第一项的最大总和是多少。    

$f_{i,j} = \max\limits_{x=0}^{\min(n,m)}{(g_{x,m}+\frac{n-x}{n}f_{i-1,j})}$。  

时间复杂度是 $O(TKM^3)$ 的，听说有人用爆搜也过了。  

[Accepted Submission](https://atcoder.jp/contests/abc404/submissions/65468380)

---

## 作者：chenxi2009 (赞：3)

## 思路
榜一同款做法。

我们考虑每一轮进行的决策，形如按一个按钮 $a_1$ 次，按另一个按钮 $a_2$ 次，按另一个按钮 $a_3$ 次......

因为每一轮按钮随机拜访，所以可以看做是无序的，我们不妨钦定按的次数是不升的，即 $a_1\ge a_2\ge a_3\ge\cdots$，那我们一轮有多少种决策呢？显然，决策数就是 $\sum a_i=M$ 且单调不升的正整数数列 $a$ 的个数，暴力搜索/搜寻资料发现 $p(M)\le p(30)=5604$。

我们考虑使用 $f_{i,j}$ 去表示还剩 $i$ 轮，已经按了 $j$ 次正确的按钮，接下来采用最优做法的获胜期望，我们对每种决策进行转移，时间复杂度为 $O(T\times K\times p(M)\times M)$，其中 $T\times K$ 是为状态数，$p(M)$ 是决策数，$M$ 是对于每种决策，有“$a_{1/2/3/\cdots}$ 对应的按钮是正确按钮”和“没有按到正确按钮”的至多 $M+1$ 种情况。

显然非常地跑不满，[最优时](https://atcoder.jp/contests/abc404/submissions/65463989)最坏点仅需 116 ms。

## 代码
```cpp
#include<bits/stdc++.h>
#define gc getchar
using namespace std;
template<typename T>void read(T &x){x = 0;int f = 1;char c = gc();while(!isdigit(c)){if(c == '-') f = -1;c = gc();}while(isdigit(c)) x = x * 10 + c - '0',c = gc();x *= f;}
int n,t,m,k,cnt,a[40],rnd,hm,tot;
long double f[40][100],mx,now;
void sch(int rst){
	if(cnt > n) return;
	if(!rst){
		now = 0;
		for(int i = 1;i <= cnt;i ++) now += (long double)1.0 * f[rnd - 1][hm + a[i]] / n;//第 i 个按钮是关键按钮 
		mx = max(mx,now + (long double)1.0 * (n - cnt) * f[rnd - 1][hm] / n);//没能按中关键按钮的情况 
		return;
	}
	for(int i = min(a[cnt],rst);i;i --) a[++ cnt] = i,sch(rst - i),cnt --;//钦定不减，进行搜索 
}
int main(){
	read(n),read(t),read(m),read(k),a[0] = 1e9;
	for(int i = 0;i <= t;i ++) for(int j = k;j <= 80;j ++) f[i][j] = 1;//边界初始化 
	for(int i = 1;i <= t;i ++){
		rnd = i;
		for(int j = 0;j < k;j ++) hm = j,mx = cnt = 0,sch(m),f[i][j] = mx; 
	}
	printf("%.20LF",f[t][0]);
	return 0;
}
```

---

## 作者：StayAlone (赞：2)

**这个题最合理的方式就是倒着 dp。**

在这个游戏之中，决策的目标是让最终获胜的概率尽量大。直接正着做不好找到等价条件，考虑倒过来。

设 $f_{i, j}$ 表示第 $i$ 轮结束后，已经成功**恰好** $j$ 次，最终能够获胜的概率。$j>k$ 的部分一律并到 $k$ 上，即 $f_{i, k}$ 表示成功大于等于 $k$ 次。显然有初值 $f_{t, k}=1$。

接下来考虑决策是什么，以及对概率的影响。由于按钮被随机排列，按哪个按钮是不重要的，重要的是按了几个不同的按钮、分别按了几次。

想到分拆数。一个决策 $c_1+c_2+\cdots+c_l=m,c_i>0$，可以认为第 $i$ 个按钮被按了 $c_i$ 次，不按 $i>l$ 的按钮。显然第 $i$ 个按钮是成功按钮的概率为 $\frac{1}{n}$，则对于该决策，有 $\frac{1}{n}$ 的概率增加 $c_i$ 的成功次数，$\frac{n-l}{n}$ 的概率不增加成功次数。

仍然注意这里的 $c_i$ 是无序的，因为按钮的编号和顺序不影响概率。

即：$f_{i, j}=\max\limits_{c_1+c_2+\cdots+c_l=m}\{\frac{1}{n}\sum\limits_{s=1}^l f_{i+1, \min(k, j+c_s)}+\frac{n-l}{n}f_{i+1, j}\}$。

答案就是 $f_{0, 0}$。

设 $P(m)$ 表示 $m$ 的分拆数，则时间复杂度为 $\mathcal O(P(m)tkm)$。

```cpp
int n, t, m, k; vector <vector <int>> dv;
vector <int> now; double f[35][35];

il void init(int s, int lst) {
    if (!s) return dv.eb(now), void();
    rep2(i, min(s, lst), 1) now.eb(i), init(s - i, i), now.pop_back();
}

int main() {
    read(n, t, m, k); init(m, m); f[t][k] = 1;
    rep2(i, t - 1, 0) rep1(j, 0, k) {
        for (auto a : dv) if (a.size() <= n) {
            double now = f[i + 1][j] * (n - a.size());
            for (auto v : a) now += f[i + 1][min(k, j + v)];
            gmax(f[i][j], now / n);
        }
    } printf("%.10lf", f[0][0]);
    return 0;
}
```

---

## 作者：Dtw_ (赞：2)

## Solution
首先考虑设 $f_{i,j}$ 表示前 $i$ 轮起码有 $j$ 次按到正确的按钮的最大概率。

我们发现并不能直接转移。但是假如说我知道了每个按钮按下的次数 $c_1,c_2,\cdots,c_n (\sum_{i=1}^{n}c_i = m)$ 那么我们就有：

$$f_{i,j} = \max \{ \frac{1}{n} \sum_{k=1}^{n}f_{i-1, j-c_k}\}$$

由于 $m \leq 30$ 所以说很多的 $c_i$ 其实都是 $0$。

然后考虑上面的转移式子，你会发现 $c_i$ 的顺序并不影响答案。所以我们可以强制把一堆 $0$ 都扔到序列的最后面，然后任意钦定一个选择 $c_i$ 的顺序（比如 $c_i\ge c_{i +1}$），然后我们就可以把上面的式子写成这个形式：

$$f_{i,j} = \max \{ \frac{1}{n} (\sum f_{i-1, j-c_k} + (n - t)f_{i - 1,j})\}$$

其中 $c_k\ge 1 (k\in[1,t])$ 且 $\sum_{k=1}^t c_k = m$。然后剩下的 $(n - t)$ 个位置的 $c_k$ 就都是 $0$ 了，那么直接算出他们的贡献即可。

然后这个拆数的复杂度我也不会证，我去网上搜了一下，发现了[这个](https://www.zhihu.com/question/450567038)，按照他的式子打了个表发现有 $1168$ 种方案。虽然可能不太对但是起码不会很大。

最终答案就是 $f_{t,k}$。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int M = 35;

int n, t, m, k;
double f[M][M];

int main()
{
    scanf("%d%d%d%d", &n, &t, &m, &k);
    for (int i = 0; i <= k; i++) f[0][i] = (!i ? 1 : 0);
    for (int i = 1; i <= t; i++) {
        for (int j = 0; j <= k; j++) {
            auto dfs = [&](auto &&self, int p, int mx, int res, double val) {
                if (p == n || !res) {
                    val += (n - p) * f[i - 1][j];
                    f[i][j] = max(f[i][j], val / n);
                    return;
                }
                for (int x = 1; x <= min(mx, res); x++) {
                    self(self, p + 1, x, res - x, val + f[i - 1][max(0, j - x)]);
                }
            };
            dfs(dfs, 0, m, m, 0);
        }
    }
    printf("%.15lf", f[t][k]);
    return 0;
}
```

---

## 作者：Handezheng (赞：1)

## 题解：AT_abc404_f [ABC404F] Lost and Pound
[题目传送门](https://www.luogu.com.cn/problem/AT_abc404_f)
### 题意
~~题面真的太粪了。~~

给定 $n$ 个按钮，包括 $1$ 个好的按钮和 $n-1$ 个坏的按钮。进行 $T$ 轮游戏，每一轮将按钮随机打乱，并按 $m$ 次按钮（同一按钮可以按多次）。$n$ 轮游戏结束后，若好的按钮被按的次数不小于 $K$ 次，获胜。求获胜的最大概率。

### 思路
每一轮游戏中，按钮都被随机打乱，我们不知道好的按钮在哪里，也不清楚每一个按钮会按几次，所以我们可以枚举（~~说了跟没说一样~~）。发现 $m\le 30$，所以**枚举可能出现的局面**，即[数的拆分](https://oi-wiki.org/math/combinatorics/partition/)。搜索发现 $p(30)=5604$。

在枚举按钮过后，可用**动态规划**解决概率问题。  
令 $f_{i,j}$ 表示到第 $i$ 轮，好的按钮至少被按了 $j$ 次的概率，初始状态为 $f_{i,0}=1$。  
在枚举了局面后，令 $cnt_e$ 表示当前局面，同一按钮被按了 $e$ 次的次数，可以得到
$$
f_{i,j} = \max_{\text {局面}}{\sum_{e=0}^{m} f_{i-1,\max(j-e,0)} \cdot \frac{cnt_e}{n}} 
$$
最终答案 $f_{T,K}$，时间复杂度 $O(T\times m \times K \times p(m))$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define db long double
#define fi first
#define se second
#define F(i,l,r) for(int i=(l); i<=(r); i++)
using namespace std;
const int N = 1e6 + 50, M = 1e3 + 50;
const int INF=0x3f3f3f3f3f3f3f3f, mod=1e9+7;

int n,T,m,K,I;
int tot,cnt[40];
db f[40][40];

inline void calc(){
	if(tot>n) return ;
	cnt[0]=n-tot;
	F(j,1,K){
		db sum=0;
		F(e,0,m)
			sum += f[I-1][max(j-e,0ll)] * cnt[e] / n;
		f[I][j] = max(f[I][j], sum);
	}
}
inline void DFS(int t,int lst){
	if(!t) calc();
	F(i,max(1ll,lst), t){
		tot++;
		cnt[i]++;
		DFS(t-i,i);
		cnt[i]--;
		tot--;
	}
}
inline void work(){
	f[I][0]=1;
	tot=0;
	DFS(m,0);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>T>>m>>K;
	f[0][0]=1;
	F(i,1,T){
		I=i;
		work();
	}
	cout<<fixed<<setprecision(20)<<f[T][K]<<'\n';

	return 0;
}
```
~~完结撒花！~~

---

## 作者：hao_zi6366 (赞：0)

最近初学概率 DP，分享一下关于本题状态细节的一些心得。

## 题意简述
青木和高桥玩一个游戏，场上有 $N$ 个按钮，其中 $1$ 个是关键按钮，剩下的 $(N-1)$ 个是普通按钮。青木知道关键按钮的位置，高桥不知道。

游戏重复 $T$ 次，每次步骤如下：

1. 青木随机摆放 $N$ 个按钮。
2. 高桥进行 $M$ 次操作，每次操作选择一个按钮按下。
3. 青木告诉高桥关键按钮被按下的次数。

高桥获胜的条件是关键按钮被按下至少 $K$ 次。

求高桥以最优策略游玩游戏时，获胜的期望。

## 题意分析

### 一、为什么使用 DP

~~AT 的概率题肯定 DP 啊~~，赛时试图推贪心策略，最后一事无成。其实题目各个按钮都一样，没有明显的贪心方向，而不用贪心的最优解问题，自然考虑 DP。

### 二、如何转移

不难想到设 $f_{i,j}$ 表示前 $i$ 场游戏，已经按下 $j$ 次胜利按钮的概率（但其实有瑕疵，后面会说）。设 $c_k$ 为当前时刻第 $k$ 个按钮按下的次数。由[全概率公式](https://oi-wiki.org/math/probability/conditional-probability/#%E6%9D%A1%E4%BB%B6%E6%A6%82%E7%8E%87)可得转移：
$$
f_{i,j}=\max{\sum_{k=1}^{n}\frac{1}{n}\times f_{i-1,j-c_k} }
$$

由于按钮都一样，本质不同的情况其实不多。可以设当前有 $x$ 个，并钦定：
$$
\forall i \in \left \{ 1, 2, \ldots, x-1 \right \} ,  c_i \geq c_{i+1}
$$
转移时暴力枚举所有情况即可，方程优化为：
$$
f_{i,j}=\max{\left ( \sum_{k=1}^{x}\frac{1}{n}\times f_{i-1,\max \left(j-c_k,0\right )}  +\frac{n-x}{n}\times f_{i-1,j}\right )  }
$$

### 三、转移细节
此时式子中有**不同寻常的一项：$f_{i-1,\max \left(j-c_k,0\right )}$**，为什么要和 $0$ 比较呢？

这就说回之前设的状态了，如果设的是：前 $i$ 场游戏，已经按下 $j$ 次胜利按钮的概率，答案其实是 $\sum_{j\ge K}{f_{T,j}}$。

为了优化转移，其实设的是：前 $i$ 场游戏，已经**至少**按下 $j$ 次胜利按钮的概率，这样算的话答案就是 $f_{T,K}$ 啦！

所以这也解释了，为什么要与 $0$ 取最大值。

最后附上代码。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define inf 0x7fffffff
typedef long long LL;
typedef long double LD;
const int N = 30+10;
namespace hao_zi{

int n,t,m,k;
LD f[N][N];
LD dfs(int now,int cnt,int lct,int id,int j){
    if(now==n+1){
        return 0;
    }
    if(cnt==m){
        return (n-now+1)*1.0l/n*f[id][j];
    }
    LD res=0;
    for(int i=1;i<=lct;i++){
        if(cnt+i<=m){
            res=std::max(res,dfs(now+1,cnt+i,i,id,j)+(i>j?1:f[id][j-i])*(1.0l/n));
        }
    }
    return res;
}
void solve(){
    std::cin>>n>>t>>m>>k;
    f[0][0]=1;
    for(int i=1;i<=t;i++){
        for(int j=0;j<=k;j++){
            f[i][j]=dfs(1,0,m,i-1,j);
        }
    }
    std::cout<<std::fixed<<std::setprecision(10)<<f[t][k];
}

}
    
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    hao_zi::solve();
    return 0;
}
```

---

## 作者：happy_zero (赞：0)

一个很自然的思路是高桥在第 $i$ 盘会选择一个按按钮的方案 $S$ 使得按下 $S$ 后期望胜率最高，因此设 $f_{i,j}$ 表示考虑第 $i\sim n$ 轮，当前按钮被按下 $j$ 次的最大期望胜率。

直接暴力枚举 $S$ 是 $n^M$ 的，但我们发现有用的 $S$ 实际上不多。由于按钮是随机排列的，因此，转移只与每个按钮被按的次数有关，具体哪一步按哪一个按钮对答案没有影响，再进一步，只与这些次数是哪些有关（相当于把次数看成一个可重集，真正有用的 $S$ 是不同的可重集的个数，其实就是拆分数）。

这个东西写个暴搜发现只有 $5604$ 种，完全可以接受。写暴搜的过程可以顺便把每种按下正确按钮次数的概率给求出来，转移时直接枚举方案 $k$ 和正确次数 $p$（第 $k$ 个方案 $p$ 个正确的概率为 $s_{k,p}$）：

$$f_{i,j}=\max_k\sum_{p=0}^M s_{k,p}\times f_{i+1,j+p}$$

写的时候会发现设 $i\sim n$ 而非 $1\sim i$ 还有个好处就是如果 $j+p\ge K$ 直接将 $1$ 带入即可，不用判断边界啥的。答案就是 $f_{0,0}$。时间复杂度 $O(MKT\times cnt)$，其中 $cnt=5604$。

```cpp
#include <bits/stdc++.h>
#define double long double
using namespace std;
const int NN = 35;
const int MM = 6005;
int ts, n, T, M, K, b[NN];
double a[MM][NN], p, f[NN][NN];
inline void dfs(int k, int s) {
	if (!s) {
		ts++; a[ts][0] = 1 - (k - 1) * p;
		for (int i = 1; i < k; i++)
			a[ts][b[i]] += p;
		return;
	}
	if (k > M || k > n) return;
	for (int j = b[k - 1]; j <= s; j++)
		b[k] = j, dfs(k + 1, s - j);
}
signed main() {
	cin >> n >> T >> M >> K; 
	p = 1.0 / n, b[0] = 1, dfs(1, M);
	for (int i = T; i >= 1; i--) {
		for (int j = K; j >= 0; j--) {
			double mx = 0;
			for (int k = 1; k <= ts; k++) {
				double sum = 0;
				for (int p = 0; p <= M; p++) {
					double pp = (j + p >= K ? 1.0 : f[i + 1][j + p]);
					sum += a[k][p] * pp;
				}
				mx = max(mx, sum);
			}
			f[i][j] = mx;
		}
	}
	printf("%.10Lf", f[1][0]);
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

###### [F - Lost and Pound](https://atcoder.jp/contests/abc404/tasks/abc404_f) 
关注两个主要变量：游戏轮数，成功次数。考虑设 $f(i,j)$ 为前 $i$ 轮成功 $j$ 次的最大概率，设 $c_k$ 为当前时刻第 $k$ 个按钮的按下次数。由有且仅有一个成功按钮，即按钮间相互独立，有
$$
f(i,j)=\max\sum_{k=1}^{n} \frac{1}{n}f(i-1,j-c_k)
$$
难以确定 $c_k$，尝试拆解式子。注意到存在大量 $c_k=0$，考虑整合计算；又注意到 $c_k$ 的顺序不影响转移，考虑钦定只按足标在 $[1,a]\ (1\le a\le m)$ 中的按钮，则 $c_k=0$ 部分的贡献为 $\frac{n-a}{n}f(i-1,j)$，于是上式化为
$$
f(i,j)=\max_{a=1}^{m}\left(\sum_{k=1}^{a} \frac{1}{n}f(i-1,j-c_k)+\frac{n-a}{n}f(i-1,j)\right)
$$
接下来考虑 $c_k\ne 0$ 部分的贡献。考虑设 $g(a,b)=\max\sum_{k=1}^{a} \frac{1}{n}f(i-1,j-c_k)$，有
$$
g(a,b)=\max_{c=1}^{\textcolor{orange}{b}} g(a-1,b-c)+\frac{1}{n}f(i-1,\textcolor{orange}{\max\{j-c,0\}})
$$
注意橙色，成功次数大于 $K$ 的情况也应被计入。最终我们有
$$
f(i,j)=\max_{a=1}^{m} \left(g(a,m)+\frac{n-a}{n}f(i-1,j)\right)
$$
时间 $\Theta(TmK^3)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cassert>
#include<queue>
#include<array>
#include<iomanip>
#if defined FIO
auto FI = freopen("1.in", "r", stdin);
auto FO = freopen("1.out", "w", stdout);
#endif
#if defined BUG
#define bug(x...) ({ x; ({}); })
#else
#define bug(x...) ({})
#endif
#define LL  long long
#define pb  push_back
#define vec vector
#define pii array<int, 2>
#define all(x) begin(x), end(x)
#define inline inline __attribute__((always_inline))
#define rep(i, l, r) for(int i = (l), i##_ = (r); i <= i##_; i++)
#define REP(i, l, r) for(int i = (l), i##_ = (r); i >= i##_; i--)
constexpr inline void tomin(auto& x,auto&& y){ if( y < x ) x = y; }
constexpr inline void tomax(auto& x,auto&& y){ if( y > x ) x = y; }
using namespace std; namespace fgo{

inline void main(){
    int N,T,M,K; cin >> N >> T >> M >> K;
    double invN = 1.0 / N;
    static double f[35];
    f[0] = 1;
    rep(i, 1, T){
        REP(j, K, 0){
            static double g[35][35];
            fill(*g, *end(g), -1e9);
            g[0][0] = 0;
            rep(a, 1, min(N, M)){
                rep(b, 1, M){
                    rep(c, 1, b){
                        tomax(g[a][b], g[a - 1][b - c] + invN * f[max(j - c, 0)]);
                    }
                }
            }
            double t = 0;
            rep(a, 1, min(N, M)){
                tomax(t, g[a][M] + (N - a) * invN * f[j]);
            }
            f[j] = t;
        }
    }
    cout << fixed << setprecision(7) << f[K];
}
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // signed CSE; cin >> CSE; while(CSE--)
    fgo::main();
}
```

---

