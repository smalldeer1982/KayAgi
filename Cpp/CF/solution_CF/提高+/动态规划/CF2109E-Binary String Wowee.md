# Binary String Wowee

## 题目描述

Mouf 觉得主题太无聊了，所以他决定这道题不使用任何主题。

给定一个长度为 $n$ 的二进制$^{\text{∗}}$字符串 $s$。你需要精确执行 $k$ 次以下操作：
- 选择一个下标 $i$（$1 \le i \le n$）满足 $s_i = \mathtt{0}$；
- 然后翻转$^{\text{†}}$所有 $s_j$（$1 \le j \le i$）。

你需要计算执行所有 $k$ 次操作的可能方式数量。

由于答案可能非常大，请输出其对 $998\,244\,353$ 取模的结果。

如果在任何步骤中选择的下标不同，则认为两个操作序列是不同的。

$^{\text{∗}}$ 二进制字符串是指仅由字符 $\mathtt{0}$ 和 $\mathtt{1}$ 组成的字符串。

$^{\text{†}}$ 翻转二进制字符是指将其从 $\mathtt{0}$ 变为 $\mathtt{1}$ 或反之。

## 说明/提示

**第一个测试用例解释：**
所有可能的操作序列如下：
1. $\mathtt{\color{red}{0}10} \xrightarrow{i = 1} \mathtt{110}$
2. $\mathtt{\color{red}{010}} \xrightarrow{i = 3} \mathtt{101}$

**第二个测试用例解释：**
所有可能的操作序列如下：
1. $\mathtt{\color{red}{0}00} \xrightarrow{i = 1} \mathtt{\color{red}{1}00} \xrightarrow{i = 2} \mathtt{010}$
2. $\mathtt{\color{red}{0}00} \xrightarrow{i = 1} \mathtt{\color{red}{1}00} \xrightarrow{i = 3} \mathtt{011}$
3. $\mathtt{\color{red}{00}0} \xrightarrow{i = 2} \mathtt{\color{red}{11}0} \xrightarrow{i = 3} \mathtt{001}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3 1
010
3 2
000
5 4
01001
8 8
11001100
20 20
10010110101101010110```

### 输出

```
2
3
10
27286
915530405```

# 题解

## 作者：EricWan (赞：2)

讲一讲目前的最短。<https://codeforces.com/contest/2109/submission/320369063>

复制我的代码的人耗子尾汁。

495 字符。

首先，看到数据范围，直接考虑 DP，但是发现后面的 filp 会影响前面的 filp，考虑反着 DP。

设 $f_{i,j}$ 为有关 $[i,n]$ 的所有 $j$ 次 filp 已经处理完的方案数。初始化 $f_{n+1,0}=1$，答案为 $f_{1,k}$。

转移是比较麻烦的，只有当后面将一个数 flip 为 $0$ 的时候才能翻它。因此将后面的 filp 操作看作一堆点，那么 $i$ 位置的 filp 操作就是再这些点的一些位置插入几个点。

```
1#2#3#4#5#6#7#8#9#A#B#
o     o o         o
```

井号是后面的 filp，数字是空的编号，圈是关于 $i$ 的 flip。

简单模拟我们就会发现，第一次插的空的奇偶性与 $s_i$ 有关，然后每隔偶数个空，可以再插一个。直接对这个东西组合计数并不容易，考虑继续 DP。

我们定义 $g_{i,j}$ 为：再 $i$ 个空中挑选 $j$ 个空，满足这些空的编号为 $v_{1\dots j}$ 且 $v_1\bmod2=1$，$(v_i-v_{i-1})\bmod2=1$ 的方案数。

$f$ 的转移就可以被写为

$$f_{i,j}=\sum_{k=0}^{j}f_{i+1,j-k}\times g_{[s_i=0]+j-k,k}$$

$g$ 的计算就比较简单了，直接照着定义模拟即可。

压完之后的代码。

```cpp
#import<bits/stdc++.h>
#define I int64_t
#define R[805][805]
#define P for(I
I M=119<<23|1;
using namespace std;I D R,F R{{1}},S R;I n,k;string s;int main(){P i=1;i^502;i++)P j=i-1;j>=0;j-=2)P k=1;k^502;k++)(F[i][k]+=F[j][k-1])%=M;P i=0;i^502;i++){S[0][i]=F[0][i];P j=1;j^502;j++)(S[j][i]=S[j-1][i]+F[j][i])%=M;}I T;cin>>T;while(T--){cin>>n>>k>>s;memset(D,0,1<<22);D[n+1][0]=1;P i=n;i;i--)P j=0;j<=k;j++)P N=0;N<=49-s[i-1]+j;N++)(D[i][j+N]+=D[i+1][j]*S[49-s[i-1]+j][N])%=M;cout<<D[1][k]<<endl;}}
```

我知道卡代码长度很没有意义，但是值的注意的是，我这样设置两个 DP 虽然可能会增加代码长度，但是竟然甩 rk2 一百多字符。

---

## 作者：ax_by_c (赞：0)

考虑一个操作序列 $a_1,\dots,a_k$ 是否合法。

要求 $\forall i,2\mid(\sum_{j=1}^{i-1}[a_j\ge a_i]+s_{a_i})$。

那么显然是从大到小 DP，设 $f_{i,j}$ 为 $a_x\ge i,\lvert a\rvert=j$ 的合法方案数。

不想思考了，再搞一个 DP 算一下得了。设 $g_{p,x,y}$ 表示 $s_i=p$ 时，$x$ 个 $i$ 和 $y$ 个 $>i$ 的组合方法，转移显然，可以预处理出来。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=998244353;
const int N=1005;
int n,k;
char s[N];
ll f[N][N],g0[N][N],g1[N][N];
void slv(){
    scanf("%d %d",&n,&k);
    scanf("%s",s+1);
    rep(i,0,n)rep(j,0,n){
        g0[i][j]=0;
        if(i==0&&j==0){
            g0[i][j]=1;
            continue;
        }
        if(j)g0[i][j]=(g0[i][j]+g0[i][j-1])%mod;
        if(i&&(!((i+j-1)&1)))g0[i][j]=(g0[i][j]+g0[i-1][j])%mod;
    }
    rep(i,0,n)rep(j,0,n){
        g1[i][j]=0;
        if(i==0&&j==0){
            g1[i][j]=1;
            continue;
        }
        if(j)g1[i][j]=(g1[i][j]+g1[i][j-1])%mod;
        if(i&&((i+j-1)&1))g1[i][j]=(g1[i][j]+g1[i-1][j])%mod;
    }
    rep(i,0,n+1)rep(j,0,n+1)f[i][j]=0;
    f[n+1][0]=1;
    per(i,n+1,2)rep(j,0,k)rep(x,0,k-j){
        if(s[i-1]=='0')f[i-1][j+x]=(f[i-1][j+x]+f[i][j]*g0[x][j]%mod)%mod;
        else f[i-1][j+x]=(f[i-1][j+x]+f[i][j]*g1[x][j]%mod)%mod;
    }
    printf("%lld\n",f[1][k]);
}
void main(){
	int T=1;
	// int csid=0;scanf("%d",&csid);
    scanf("%d",&T);
    while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：冷却心 (赞：0)

/bangbangt 题。

注意到操作某个位置不会对它后面产生影响，所以我们从后往前枚举每个位置操作了多少次，插入操作序列。记 $f_{i,j}$ 表示对 $i$ 及其以后的位置操作了 $j$ 次，得到的操作序列个数。那么我们枚举当前位操作了 $k$ 次，有转移：

$$ f_{i + 1,j} \times g_{j,k,s_i} \rightarrow f_{i,j+k}. $$

其中辅助数组 $g_{j,k,0/1}$ 表示在原长 $j$ 操作序列中插入 $k$ 个当前位，并且当前位置最初的状态是 $0/1$。这个其实是个组合数，但可以直接 dp。有两种转移：

- $g_{i,j,t} \leftarrow g_{i-1,j,t}$，表示插入一个后面的位置，显然没有任何限制。
- $g_{i,j,t} \leftarrow g_{i,j-1,t}$，当且仅当 $j>0$ 以及 $t + i + j \equiv 1 \pmod 2 $，表示插入一个当前位，限制是当前位必须为 $0$，或者说操作完为 $1$。

然后初始状态 $g_{0,0,0}=g_{0,0,1}=g_{0,1,0}=1$。然后最终答案为 $f_{1,k}$。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 510;
const LL MOD = 998244353;
int n, K; char S[N]; LL F[N][N], G[2][N][N];

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for (int t = 0; t < 2; t ++) {
		G[t][0][0] = 1; G[t][0][1] = (!t);
		for (int i = 1; i <= 500; i ++) for (int j = 0; j <= 500; j ++) {
			G[t][i][j] = G[t][i - 1][j];
			if (j && (t ^ i ^ j) & 1) G[t][i][j] = (G[t][i][j] + G[t][i][j - 1]) % MOD;
		}
	}
	int _; cin >> _;
	while (_ --) {
		cin >> n >> K >> (S + 1); 
		for (int i = 1; i <= n + 1; i ++) for (int j = 0; j <= K; j ++) F[i][j] = 0;
		F[n + 1][0] = 1;
		for (int i = n; i >= 1; i --) for (int j = 0; j <= K; j ++) for (int k = 0; j + k <= K; k ++)
			F[i][j + k] = (F[i][j + k] + F[i + 1][j] * G[S[i] - '0'][j][k] % MOD) % MOD;
		cout << F[1][K] << "\n";
	}
	return 0;
}
```

---

