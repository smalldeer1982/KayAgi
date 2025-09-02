# Peanuts

## 题目描述

拥有神奇豆茎的 Jack 最近收集了许多花生。最终，他得到了 $n$ 袋花生，这些花生袋从左到右依次编号为 $1$ 到 $n$。第 $i$ 袋中有 $a_i$ 个花生。

Jack 和他的童年好友 Alice 决定围绕这些花生玩一个游戏。首先，Alice 会将这些花生袋分成若干个盒子；每个盒子必须包含至少一个连续的花生袋，并且每个花生袋只能属于一个盒子。与此同时，Alice 不会改变盒子的顺序，也就是说，盒子的编号按照其中花生袋的编号递增排列。

之后，Alice 和 Jack 将轮流进行操作，Alice 先手。

每一回合，当前玩家必须从最左边的非空盒子（即最左边至少有一个非空花生袋的盒子）中的某一个花生袋中取出正数个花生。换句话说，只有当前面所有盒子都已经没有花生时，玩家才能从更右边的盒子中取花生。无法进行有效操作的玩家判负。

由于 Alice 可以自行决定如何分盒，她确信自己能够获胜。因此，她想知道有多少种分盒方式可以保证她获胜（假设双方都采取最优策略）。你能帮她计算这个方案数吗？

由于答案可能非常大，请输出对 $998\,244\,353$ 取模后的结果。

## 说明/提示

在第一个测试用例中，Alice 获胜的唯一分盒方式是将花生袋分为两个盒子：$([1, 2], [3])$（第一个盒子包含第 1 和第 2 袋，第二个盒子包含第 3 袋）。Alice 通过从第二袋取走所有花生获胜，剩下 $([1], [3])$。Jack 被迫从第一个盒子中唯一的袋子取花生，Alice 就能取走第二个盒子剩下的花生。

在第二个测试用例中，Alice 获胜的分盒方式有 $([1], [2, 3, 1])$、$([1, 2, 3, 1])$、$([1, 2], [3], [1])$ 和 $([1, 2], [3, 1])$。

在第三个测试用例中，无论 Alice 如何分盒，她都能获胜。

在第四个测试用例中，无论 Alice 如何分盒，她都无法获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3
1 2 3
4
1 2 3 1
5
1 1 1 1 1
2
1 1
10
1 2 3 4 5 6 7 8 9 10```

### 输出

```
1
4
16
0
205```

# 题解

## 作者：2020HZ06 (赞：3)

翻译：

给定长为 $n$ 的数组 $a$。Alice 先将数组划分成若干段。Alice 与 Jack 轮流操作，Alice 先手。

在每一轮中，当前玩家将属于**最左边**非空段的一个元素减去某个**正数**，且不能减成负数。不能操作的人输。

计算 Alice 能取胜的划分方案数对 $998244353$ 取模的值。

$1\le t\le 10^4,1\le n\le 10^6,1\le a_i\le 10^9$

考虑只分成一段的情况。这就是一个 nim 游戏，Alice 获胜当且仅当 $\bigoplus_{i=1}^n a_i\neq 0$。如果分成两段，若后一段先手必败，则前一段需满足先手必胜。如果后一段先手必胜，两人都想让自己在第一段输，这就是经典的**反常游戏**。

反 nim 游戏的必胜条件：

- $a_i$ 全部等于 $1$ 时 $n$ 为奇数则先手必败，否则必胜。

- 当存在 $a_i>1$ 时，异或和不为 $0$ 时先手必胜，否则必败。证明：

  - A：当只有一个 $a_i>1$ 时，异或和显然不为 $0$，先手直接转移到 $a_i=1/0$ 的局面必胜。
  - 当存在至少两个 $a_i>1$ 时
    - B：异或和不为 $0$：类似 nim 游戏一步转移到 C。注意如果只有两个 $a_i>1$ 且正好减少了其中一个，那么由于异或和为 $0$ 还是存在两个 $a_i>1$。
    - C：异或和为 $0$：可以一步转移到 B 或者 A（视情况）。
  
  在 B、C 循环中，总会有一个 C **只能**一步转移到 A。因此 C 先手必败，B 先手必胜。

有了上述结论，推广至 $k$ 段。第 $k$ 段是 nim 游戏，要是先手必胜，那么 $k-1$ 段就是反 nim 游戏，否则就是 nim 游戏。注意到 nim 游戏和反 nim 游戏的胜负条件**仅在 $a_i$ 全为 $1$ 时不同。**

考虑 dp。设 $f_{i,0/1}$ 为考虑前 $i$ 个数，分段后最后一段是 nim 游戏/反 nim 游戏，整盘游戏 **Alice 必胜**的方案数。最后要求 $f_{n,0}$。

$f_{i,0}$ 的转移：最后一段先手必胜：$f_{j,1}\to f_{i,0}$。必败：$f_{j,0}\to f_{i,0}$。

$f_{i,1}$ 的转移是一样的。就是先手必胜的判断不同。时间复杂度 $O(n^2)$，考虑优化。预处理异或前缀和，$\bigoplus_{k=j+1}^ia_k=0$ 相当于 $s_i\oplus s_j=0$，也就是 $s_i=s_j$。离散化后用桶处理即可。问题在于反 nim 游戏的转移。假设从 $pos+1$ 到 $i$ 的 $a$ 全部是 $1$，$pos$ 以前的 $j$ 可以和 nim 游戏一样转移。$j\in [pos,i-1]$ 则 $(i-j)\bmod 2=0$ 先手必胜，否则必败。奇偶位置分开转移即可。时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
const int N=1000005; 
int t,n,a[N],b[N],c[N];
const ll mod=998244353;
ll f[N][2],buc[N][2],Buc[N][2],w[2][2],g,G;//g,buc 对应 nim 游戏，G,Buc 对应反 nim 游戏，w 是奇偶分开贡献
void add(ll &x,ll y){
	(x+=y)%=mod;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),c[i]=a[i],a[i]^=a[i-1],b[i]=a[i];
		sort(b+1,b+n+1);
		int m=unique(b,b+n+1)-b-1;
		for(int i=1;i<=n;i++) a[i]=lower_bound(b,b+m+1,a[i])-b;
		for(int i=0;i<=m;i++) buc[i][0]=buc[i][1]=Buc[i][0]=Buc[i][1]=0;
		buc[0][1]=1,g=1,f[0][1]=1;
		G=0;
		w[0][0]=0,w[0][1]=1,w[1][0]=w[1][1]=0;
		int pos=0;
		for(int i=1;i<=n;i++){
			f[i][0]=(g-buc[a[i]][1]+mod+buc[a[i]][0])%mod;
			if(c[i]>1){
				while(pos<i){//类似双指针
					int j=pos;
					add(Buc[a[j]][0],f[j][0]);
					add(Buc[a[j]][1],f[j][1]),add(G,f[j][1]);
					pos++;
				}
				w[0][0]=w[0][1]=w[1][0]=w[1][1]=0;
			}
			f[i][1]=(G-Buc[a[i]][1]+mod+Buc[a[i]][0])%mod;
			add(f[i][1],w[i&1][1]),add(f[i][1],w[!(i&1)][0]);
			add(buc[a[i]][0],f[i][0]);
			add(buc[a[i]][1],f[i][1]),add(g,f[i][1]);
			add(w[i&1][0],f[i][0]),add(w[i&1][1],f[i][1]);
		}
		printf("%lld\n",f[n][0]);
	}
	return 0;
}
```

---

## 作者：ForgotMe (赞：2)

为什么官方题解写了这么大一坨，给一个不需要脑子的做法。

注意到这个游戏非常像 nim 游戏，但是有挨着取的限制，还是有所不同。

直接粗暴的定义 $dp_{i,0/1}$ 表示将 $[i,n]$ 分成若干段使得先手必败/必胜的方案数。

考虑如何转移，枚举一个 $j$ 表示将 $[i,j]$ 分成一段。注意现在已经知道了 $[j+1,n]$ 的胜负情况。

- $[j+1,n]$ 后手必胜，那么对于 $[i,j]$ 这一段，先手肯定是想让最后取石子的人是自己，从而让自己在 $[j+1,n]$ 成为后手。同样地：后手也是想让最后取石子的人是自己。那么只需考虑 $[i,j]$ 这一段石子的胜负，这是一个显然的 nim 游戏，判断这一段的异或和是否为 $0$ 即可，不为 $0$ 说明先手可以在 $[j+1,n]$ 这一段成为后手，否则不行。


- $[j+1,n]$ 先手必胜，跟上一种情况唯一不同的点在于**规则变为了不能取的就算赢了**（即先手会想让在即在 $[i,j]$ 这一段最后取石子的不是自己，从而让自己成为接下来的先手）。这是**反常 nim 游戏**，下面给出其结论与证明。

首先先看结论：

定义 N 态为先手必胜，P 态为先手必输，$a_i$ 为第 $i$ 堆石子的个数。

- 对于所有石子数都为 $1$ 的情况，当堆数为偶数时为 N 态，否则为 P 态。

- 至少存在一个 $a_i>0$，令 $T$ 为所有石子堆数的异或和，如果 $T\ne 0$，那么为 N 态，否则为 P 态。

一个关键的事实是反常 nim 游戏仍然为有向无环图上的游戏，与 nim 游戏的不同在于没有后继的状态为必赢状态。于是仍然可以采用数学归纳法证明上述结论，并且以下事实成立：

一个局面为 N 态的充要条件是有至少一条出边连接至 P 态。
一个局面为 P 态的充要条件是每一条出边都连接到 N 态。

第一种情况显然成立。

对于第二种情况，需要分类讨论。

- 先证明 $T\ne 0$ 时是 N 态。当只有一个 $a_i>1$ 时，先手可以把这堆石子变为 0/1，得到的两个状态必有一个为 P 态，得证。当至少有两个 $a_i>1$ 时，发现一定能找到一个 $a_i$ 有 $T=a_i\oplus y(y\in[0,a_i-1])$，只需让 $a_i$ 的二进制表示下满足在 $T$ 的最高位也为 $1$，这个等式说明先手可以通过操作一堆石子使得 $T$ 变为 $0$，也就是转移到 P 态。

- 再证明 $T=0$ 时是 P 态。首先不可能存在只有一个 $a_i>1$ 的情况，此时 $T$ 一定不可能为 $0$。剩下的情况就非常好证明了，因为操作后新的 $T$ 不可能为 $0$，所以每一条出边连接的都是 N 态。

综上结论得证。

于是得到了一个 $\mathcal{O}(n^2)$ 的做法，优化是容易的，对于 $[j+1,n]$ 后手必胜情况的转移，开个 map 以前缀异或和为下标统计一下和即可，对于 $[j+1,n]$ 先手必胜情况的转移，这个要麻烦一点，要特殊判断 $a_i=1$ 的极长连续段，不过处理方式都是一样的。

时间复杂度 $\mathcal{O}(n\log n)$。

贴个写的很丑的代码：https://www.luogu.com.cn/paste/cvsb45rz

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2032F)

**题目大意**

> 给定 $a_1\sim a_n$，先手先将 $a_1\sim a_n$ 分成若干个连续段，然后两个人从左到右依次在每个连续段内部做 Nim 游戏，求有多少分段策略使得先手必胜。
>
> 数据范围：$n\le 10^6$。

**思路分析**

考虑如何判定一个局面是先手必胜还是后手必胜，从最后一个连续段开始，先手肯定要赢下这个游戏。

那么这个游戏如果先手必胜，则先手要输掉前面那个游戏，使得他能在这个游戏中成为先手，否则先手要赢下前面那个游戏。

因此从后往前就能推断出想要获胜的人要在每个游戏中赢还是输。

于是可以 dp，$f_{i,0/1}$ 表示 $a[i,n]$ 的分段已经确定，想获胜要输 / 赢 $a_{i-1}$ 所处的游戏。

转移系数就是 $a[i,j)$ 构成的游戏先手有没有必胜 / 必败策略。

先手有必胜策略就是 Nim 博弈，即异或和 $\ne 0$。

先手有必败策略则是 Anti-Nim 博弈，判定条件是 $\max a_i>1$ 时异或和 $\ne 0$，或者所有 $a_i=1$ 时异或和 $=0$。

因此暴力 dp 可以做到 $\mathcal O(n^2)$。

优化转移只需要对异或前缀和开桶，特殊讨论 $\max a[i,j)=1$ 的情况。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
int n,a[MAXN],s[MAXN];
ll f[MAXN][2],g[MAXN][2];
//f[i][0/1]: fill [i,n], lose/win game at i-1
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	vector <int> vals{0};
	for(int i=n;i>=1;--i) vals.push_back(s[i]=s[i+1]^a[i]);
	sort(vals.begin(),vals.end()),vals.erase(unique(vals.begin(),vals.end()),vals.end());
	for(int i=1;i<=n+1;++i) s[i]=lower_bound(vals.begin(),vals.end(),s[i])-vals.begin()+1;
	g[s[n+1]][1]=g[0][1]=f[n+1][1]=1;
	int h[2]={0,0};
	for(int i=n,j=n+1;i>=1;--i) {
		if(a[i]>1) {
			h[0]=h[1]=0;
			for(;j>i;--j) {
				g[s[j]][0]=(g[s[j]][0]+f[j][0])%MOD;
				g[0][0]=(g[0][0]+f[j][0])%MOD;
			}
		}
		f[i][1]=(f[i][1]+g[s[i]][1])%MOD;
		f[i][0]=(f[i][0]+g[0][1]+MOD-g[s[i]][1])%MOD;
		f[i][1]=(f[i][1]+g[s[i]][0])%MOD;
		f[i][0]=(f[i][0]+g[0][0]+MOD-g[s[i]][0])%MOD;
		f[i][1]=(f[i][1]+h[(i+1)&1])%MOD;
		f[i][0]=(f[i][0]+h[i&1])%MOD;
		g[s[i]][1]=(g[s[i]][1]+f[i][1])%MOD;
		g[0][1]=(g[0][1]+f[i][1])%MOD;
		h[i&1]=(h[i&1]+f[i][0])%MOD;
	}
	cout<<f[1][0]<<"\n";
	for(int i=0;i<=n+1;++i) {
		a[i]=s[i]=f[i][0]=f[i][1]=g[i][0]=g[i][1]=0;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

先考虑这样一个问题，给你一个划分，求出先手能否胜利。

不妨设盒子之间构成了 $k$ 局游戏，我们从后往前考虑每一局游戏，假若只考虑第 $[i+1,k]$ 局游戏，已知先手必败还是必胜，那么第 $i$ 局游戏双方的策略就是使得自己取完石子或者对方取完石子，也就是第 $i$ 局游戏是一个 Nim 游戏或者反常 Nim 游戏，反常 Nim 游戏的结论是存在不为 $1$ 的石子堆时结论与正常 Nim 游戏一样，否则结论与正常 Nim 游戏相反。

那么计数方案呼之欲出了，不妨 $suf_i$ 表示 $a_i$ 的后缀异或和，$spec_i$ 在从后往前扫时动态维护，当 $[i,j)$ 内 $a$ 的值都为 $1$ 时 $spec_j = suf_j \oplus 1$，否则 $spec_j = suf_j$，，由于一个值只会被改一次，所以这里可以记下连续最长 $1$ 段然后暴力改。这样的好处是 $[i,j)$ 做反常 Nim 游戏时先手胜利条件就是 $suf_i \not = spec_j$。设计状态 $dp_{i,0/1}$ 表示 $[i,n]$ 先手胜利或者失败的方案，总方案是好求的，所以这里只考虑 $dp_{i,0}$ 的转移，先手要胜利，要么 $[i,j)$ 是一个正常 Nim 游戏先手胜利且 $[j,n]$ 后手胜利，要么 $[i,j)$ 是一个反常 Nim 游戏先手胜利且 $[j,n]$ 先手胜利，用 map 把 dp 数组挂到 $spec,suf$ 上即可做到 $O(n \log n)$。

代码很短。


```cpp
#include<bits/stdc++.h>
const int mod = 998244353;
using namespace std;
const int maxn = 1e6+114;
//[i,j) 正常 Nim 先手胜 [j,n] 先手败
//suf[i]!=suf[j]
int sum0;//先手败
map<int,int> mp;//sum[j]=x 且 [j,n] 先手败的方案
//[i,j) 反常 Nim 先手胜 [j,n] 先手胜
map<int,int> sp;//spex[j]=x 且 [j,n] 先手胜的方案
//suf[i]!=spec[j] 对于连续 1 spec[i]=suf[i]^1 其余 spec[i]=suf[i]
int dp[maxn];//先手胜的方案
int sum1;//先手胜
int spec[maxn],suf[maxn],n;
int cnt;//[i,j) 内全部是 1
void work(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>suf[i];
    suf[n+1]=0;
    for(int i=n;i>=1;i--) suf[i]^=suf[i+1];
    sum0=1;
    mp[0]=1;
    cnt=n+1;
    for(int i=n;i>=1;i--){
        spec[i]=suf[i]^1;
        if((suf[i]^suf[i+1])!=1){
            for(int j=i+1;j<=min(n,cnt);j++){
                sp[spec[j]]=(1ll*sp[spec[j]]+mod-dp[j])%mod;
                spec[j]^=1;
                sp[spec[j]]=(1ll*sp[spec[j]]+dp[j])%mod;
            }
            cnt=i;
        }
        dp[i]=(1ll*sum0+mod-mp[suf[i]])%mod;
        dp[i]=(1ll*dp[i]+sum1+mod-sp[suf[i]])%mod;
        int other=(1ll*sum0+sum1+mod-dp[i])%mod;
        sum0=(1ll*sum0+other)%mod;
        sum1=(1ll*sum1+dp[i])%mod;
        mp[suf[i]]=(1ll*mp[suf[i]]+other)%mod;
        mp[spec[i]]=(1ll*mp[spec[i]]+dp[i])%mod;
    }
    cout<<dp[1]<<'\n';
    mp.clear();
    sp.clear();
    cnt=0;
    for(int i=1;i<=n;i++) dp[i]=suf[i]=spec[i]=0;
    sum0=sum1=0;
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}

```

---

## 作者：superl61 (赞：0)

[题目传送门](https://codeforces.com/contest/2032/problem/F)

[更好的阅读体验](https://www.cnblogs.com/superl61/p/18560820) 

## 分析

本题如果只有一个盒子，因为最后一个操作的人是赢家，所以就是 **Nim 游戏**，先手必胜的充要条件是**所有 $a_i$ 异或和不为 $0$。**

再考虑有两个盒子，显然最后一段必须是 Nim 游戏，我们试着从最后一段的状态反推出前一段的情况。

- 如果**后一段满足先手必败**，Alice 想要赢就必须让 Jack 成为后一段的先手。也就是说**前一段需满足先手必胜**。
- 如果**后一段满足先手必胜**，Alice 想要赢就必须让 Jack 拿走前一段的最后一堆，这样她就可以趁机成为第二段的先手。即**前一段需满足先手必败**。

> 说明一下，上述所说的所有**先手必胜或必败**都是针对一个盒子内的先手。之所以这么想，就是把盒与盒之间独立出来，这样才可能挖掘出 dp 需要的**最优子结构**。

说回来，上述第二种情况中，Alice 和 Jack 都想让自己在第一局输掉，这是**反常游戏（取走最后一颗棋子的人是败者）**，先手必胜的条件有所不同：

- 若 $a_i$ 全为 $1$，先手必胜当且仅当个数为偶数。

- 否则，需满足 $a_i$ 异或和不为 $0$。

否则就是先手必败。

掌握了两个盒子的情况怎么合并，我们就可以开始设计 dp 状态了。

## 状态设计

记 $f_{i, 0 / 1}$ 表示前 $i$ 个数，最后一段是 Nim​ 还是反常游戏，**整局游戏**先手必胜的方案数。

>注意：不同游戏结尾，其必胜含义不同。

答案：$f_{n, 0}$，理由同上，最后一段必须是 Nim 游戏。

$f_{i, 0}$ 的转移：最后一段先手必胜，从 $f_{i, 1}$ 转移；最后一段必败，从 $f_{i, 0}$ 转移。

$f_{i, 1}$ 的转移：最后一段先手必胜，从 $f_{i, 0}$ 转移；最后一段必败，从 $f_{i, 1}$ 转移。

直接做是 $O(n^2)$ 的，考虑如何优化。

总的来说，胜负有两个因素决定：异或和是否为 $0$、全 $1$ 情况下的奇偶性。

- 对于异或和，判断一段异或和是否为 $0$，可以处理异或前缀和 $s_i$，则转化成 $s_i$ 是否和 $s_j$ 相等。因此可以用桶存下每种 $s_i$ 能转移的贡献，类似的桶优化 dp 技巧也出现在了 [CSP-S 2024 染色](https://www.luogu.com.cn/problem/P11233)，具体实现可参考[我的这篇博客](https://www.cnblogs.com/superl61/p/18511688)。
- 对于全 $1$ 的奇偶性，简单统计就可以了。遇到全 $1$ 的时候，第一种情况就暂时不更新，等全 $1$ 中断后再把这一段更新进桶里面，有点类似**双指针**。

值域过大，用 map 可以做到 $O(n\log n)$，用哈希表或许可以 $O(n)$ 解决。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i(l);i<=(r);++i)
#define G(i,r,l) for(int i(r);i>=(l);--i)
#define int ll
using namespace std;
using ll = long long;
const int N = 1e6 + 105;
const int mod = 998244353;
int T, n, sum[2];
int a[N], f[N][2], sm[2][2], s[N];
map<int, pair<int, int> >mp;
signed main(){
	cin >> T;
	F(o, 1, T){
		mp.clear();
		cin >> n;
		F(i, 1, n) {
			cin >> a[i];
			s[i] = s[i - 1] ^ a[i];
			if(!mp.count(s[i])) mp[s[i]] = {0, 0};
		}
		f[0][1] = 1;
		mp[0] = {0, 0};
		sm[0][0] = sm[1][0] = sm[1][1] = 0;
		sm[0][1] = 1;
		sum[0] = sum[1] = 0;
		int pos = 0;
		F(i, 1, n){
			if(a[i] == 1){
				(f[i][0] += (sum[1] - mp[s[i]].second) + mp[s[i]].first + mod) %= mod;
				(f[i][1] += (sum[1] - mp[s[i]].second) + mp[s[i]].first + mod) %= mod;	
				if(i & 1){
					(f[i][0] += sm[0][1] + sm[1][0]) %= mod;
					(f[i][1] += sm[1][1] + sm[0][0]) %= mod;
				}
				else{
					(f[i][0] += sm[1][1] + sm[0][0]) %= mod;
					(f[i][1] += sm[0][1] + sm[1][0]) %= mod;
				}
				pos = min(pos, i);
				(sm[i & 1][0] += f[i][0]) %= mod;
				(sm[i & 1][1] += f[i][1]) %= mod;
			}
			else{
				F(j, pos, i - 1) {
					(mp[s[j]].first += f[j][0]) %= mod;
					(mp[s[j]].second += f[j][1]) %= mod;
					(sum[0] += f[j][0]) %= mod;
					(sum[1] += f[j][1]) %= mod;
				}
				(f[i][0] += (sum[1] - mp[s[i]].second) + mp[s[i]].first + mod) %= mod;
				(f[i][1] += (sum[1] - mp[s[i]].second) + mp[s[i]].first + mod) %= mod;
				(mp[s[i]].first += f[i][0]) %= mod;
				(mp[s[i]].second += f[i][1]) %= mod;
				(sum[0] += f[i][0]) %= mod;
				(sum[1] += f[i][1]) %= mod;
				sm[0][0] = sm[0][1] = sm[1][0] = sm[1][1] = 0;
				pos = N;
			}
		}
		cout << f[n][0] << ' ' << f[n][1] << '\n'; // Alice 要拿最后一个赢，因此是正常的Nim游戏
		F(i, 1, n) f[i][0] = f[i][1] = 0;
	}
	return fflush(0), 0;
}
```

---

## 作者：Petit_Souris (赞：0)

首先需要解决的问题是，给定一个局面，求先手是否必胜。我们发现，组和组之间是独立的，我们只关心每组最后不能操作的人是谁（他将作为下一组的先手）。所以我们可以倒过来求解。如果我们需要抢到先手，那么相当于在这组中必须让对面拿走最后一个物品，否则在这组中必须让自己拿到最后一个物品。这实际上对应了反 Nim 游戏和 Nim 游戏的先手必胜情况。

对于 Nim 游戏的局面 $[a_1,a_2,\dots a_k]$，我们熟知当 $a_1\oplus a_2\oplus \dots \oplus a_k\neq 0$ 时先手必胜，否则后手必胜。

对于反 Nim 游戏的局面 $[a_1,a_2,\dots a_k]$，我们熟知当 $\forall i,a_i=1$ 时，若 $k$ 为偶数先手必胜，否则后手必胜；当 $\exist i, a_i\neq 1$ 时，若 $a_1\oplus a_2\oplus \dots \oplus a_k\neq 0$ 先手必胜，否则后手必胜。

那么有一个简单的 $\mathcal O(n^2)$ DP 做法：设 $f_{i,0/1}$ 表示 $[i,n]$ 这段后缀，分成若干组，先手必胜 / 后手必胜的方案数。转移时枚举 $[i,j]$ 分一段，对于 $f_{j+1,*}$，如果先手必胜，做反 Nim 游戏，否则做 Nim 游戏。容易用前缀和 + 哈希表优化到 $\mathcal O(n)$，可以通过。注意要把 $1$ 的连续段拿出来特殊处理。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,Mod=998244353;
ll T,n,a[N],suf[N],nxt[N],dp[N][2],S[2];
unordered_map<ll,ll>mp[2];
ll MP(ll id,ll x){
    if(mp[id].count(x))return mp[id][x];
    return 0;
}
void solve(){
    n=read();
    rep(i,1,n)a[i]=read();
    rep(i,0,n+1)suf[i]=0,dp[i][0]=dp[i][1]=0;
    per(i,n,1)suf[i]=suf[i+1]^a[i];
    mp[0].clear(),mp[1].clear();
    S[0]=S[1]=0;
    per(i,n,1){
        if(!suf[i])dp[i][1]=1;
        else dp[i][0]=1;
        if(a[i]==1){
            ll j=i;
            while(j>1&&a[j-1]==1)j--;
            ll tmp[2][2];memset(tmp,0,sizeof(tmp));
            tmp[0][(i+1)&1]=dp[i+1][0];
            tmp[1][(i+1)&1]=dp[i+1][1];
            per(k,i,j){
                if(!suf[k])dp[k][1]=1;
                else dp[k][0]=1;
                dp[k][0]=(dp[k][0]+S[0]-MP(0,suf[k])+Mod)%Mod;
                dp[k][1]=(dp[k][1]+MP(0,suf[k]))%Mod;
                if(suf[k]!=suf[i+1])dp[k][0]=(dp[k][0]-dp[i+1][0]+Mod)%Mod;
                else dp[k][1]=(dp[k][1]-dp[i+1][0]+Mod)%Mod;
                dp[k][0]=(dp[k][0]+S[1]-MP(1,suf[k])+Mod)%Mod;
                dp[k][1]=(dp[k][1]+MP(1,suf[k]))%Mod;
                if(suf[k]!=suf[i+1])dp[k][0]=(dp[k][0]-dp[i+1][1]+Mod)%Mod;
                else dp[k][1]=(dp[k][1]-dp[i+1][1]+Mod)%Mod;
                dp[k][0]=(dp[k][0]+tmp[0][k&1])%Mod;
                dp[k][1]=(dp[k][1]+tmp[1][k&1])%Mod;
                dp[k][0]=(dp[k][0]+tmp[1][(k&1)^1])%Mod;
                dp[k][1]=(dp[k][1]+tmp[0][(k&1)^1])%Mod;
                tmp[0][k&1]=(tmp[0][k&1]+dp[k][0])%Mod;
                tmp[1][k&1]=(tmp[1][k&1]+dp[k][1])%Mod;
            }
            per(k,i,j){
                mp[0][suf[k]]=(mp[0][suf[k]]+dp[k][0])%Mod;
                mp[1][suf[k]]=(mp[1][suf[k]]+dp[k][1])%Mod;
                S[0]=(S[0]+dp[k][0])%Mod;
                S[1]=(S[1]+dp[k][1])%Mod;
            }
            i=j;
            continue;
        }
        dp[i][0]=(dp[i][0]+S[0]-MP(0,suf[i])+Mod)%Mod;
        dp[i][1]=(dp[i][1]+MP(0,suf[i]))%Mod;
        dp[i][0]=(dp[i][0]+S[1]-MP(1,suf[i])+Mod)%Mod;
        dp[i][1]=(dp[i][1]+MP(1,suf[i]))%Mod;
        mp[0][suf[i]]=(mp[0][suf[i]]+dp[i][0])%Mod;
        mp[1][suf[i]]=(mp[1][suf[i]]+dp[i][1])%Mod;
        S[0]=(S[0]+dp[i][0])%Mod;
        S[1]=(S[1]+dp[i][1])%Mod;
    }
    write(dp[1][0]),putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

