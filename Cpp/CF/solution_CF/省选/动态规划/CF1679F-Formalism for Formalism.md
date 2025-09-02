# Formalism for Formalism

## 题目描述

### 题意简述

给出正整数 $n$，所有不足 $n$ 位（十进制）的数用前导零补充。

给出 $m$ 组**无序**数对 $(u_i,v_i)$，若一个数字的相邻两位数 $x,y$ 满足 $(x,y)$ 存在于这 $m$ 组数对中，则可以交换 $x,y$ 的位置。若 $A$ 可以通过若干次（包含零次）交换得到 $B$，则认为 $A$ 和 $B$ 是等价的。

求出最大整数 $k$，使得存在一组非负整数 $x_1,x_2,\ldots,x_k(0\leq x_i<10^n)$ 满足对于任意 $1\leq i<j\leq k$，$x_i$ 与 $x_j$ 不等价。

## 样例 #1

### 输入

```
1
0```

### 输出

```
10```

## 样例 #2

### 输入

```
2
1
0 1```

### 输出

```
99```

## 样例 #3

### 输入

```
2
9
0 1
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9```

### 输出

```
91```

# 题解

## 作者：william555 (赞：16)

考虑在每一堆本质相同的串中找出字典序最小的一个作为“代表串”，那么答案就等于无法通过操作使得字典序变小的串的数量。

如果存在一个数对 $(u_i,v_i)$，那么我们就称 $u_i$ 和 $v_i$ 是可交换的

考虑什么样的串满足要求，考虑从前往后一个一个位置地填数。假设现在填的数是 $a_i$ ，找到极长的一个后缀 $a_j \sim a_{i-1} $ ，使得 $ a_i $ 可以和后缀中的每一个数都是可交换的，发现如果后缀中存在一个数大于 $ a_i $，那么当前这个串就可以通过操作使字典序变小，否则就不行。

先证明充分性：  
因为 $a_i$ 和后缀中所有数都是可交换的，如果存在某个数 $a_k$ 大于 $a_i$，那么就直接把 $a_i$ 交换到 $a_k$ 前面，字典序就变小了。

再证必要性：
考虑反证，假设有一个位置没有比自己大的可交换的数，但是却可以通过将这个数前移使字典序变小。考虑最后的一个与 $a_i$ 无法交换的数 $a_k$ ，因为 $a_i$ 交换后放在 $a_k$ 之后不会使字典序变小，那就必须要 $a_k$ 之前的交换到 $a_k$ 之后与 $a_i$ 交换，但是这时 $a_k$ 的位置就会前移，字典序反而会变大。

整理一下，现在想要求的就是：每一个位置都没有比自己大的可交换位置的串的数量。

那么如何计算答案？

考虑状压dp，设 $f_{i,s}$ 表示当前填到第i位，$a_i$ 不能填集合 $s$ 之内的的数，的方案数。

预处理出每一个 $s$ 末尾填 $i$ 以后会转移到的集合 $to_{s,i}$ 。然后直接枚举第 $i$ 位填什么来dp。

时间复杂度 $O (n*2^{10}*10)$ ，dp过程中适当剪枝，跑得飞快。

```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline void Add(int &a,int b){a+=b;if(a>=mod)a-=mod;}
int n,m;
bool mp[10][10];
int f[2][1<<10];
int to[1<<10][10];
int main(){
	cin>>n;
	cin>>m;
	while(m--){
		int x,y;
		cin>>x>>y;
		mp[x][y]=mp[y][x]=1;
	}
	f[0][0]=1;
	for(int s=0;s<1<<10;s++){
		for(int i=0;i<10;i++){
			if(s&(1<<i)){
				to[s][i]=-1;
				continue;
			}
			for(int j=0;j<10;j++){
				if(!mp[i][j])continue;
				if(j>i||s&(1<<j))to[s][i]|=1<<j;
			}
		}
	}
	int p=0;
	for(int i=1;i<=n;i++,p^=1){
		for(int s=0;s<1<<10;s++){
			if(!f[p][s])continue;
			for(int i=0;i<10;i++){
				int t=to[s][i];
				if(t!=-1)Add(f[p^1][t],f[p][s]);
			}
			f[p][s]=0;
		}
	}
	int ans=0;
	for(int s=0;s<1<<10;s++)Add(ans,f[p][s]);
	cout<<ans;
	return 0;
}
```


---

## 作者：eEfiuys (赞：2)

**Difficulty: \*2600**  
Duel 的时候花了 27min47s 把对面秒了。

显然有若干个等价类，所以只需要对等价类计数就好。  
每个等价类只取最小的数作为代表，所以就是要求出，有多少个 $n$ 位数，使得它**不能通过操作变得更小**。

设 $ok_{u,v}=\text{true}$ 表示输入中**不存在**无序对 $(u,v)$。  
考虑什么时候可以在下一位填一个 $k$，就是，填上 $k$ 之后，往前一直能换就换，过程中不能碰到一个大于 $k$ 的。  
所以当这一位填了 $x$ 之后：
- 所有 $ok_{x,k}=\text{true}$ 的 $k$ 都可以填在下一位（这里面包括 $x=k$），
- 所有 $ok_{x,k}=\text{false} \ \wedge \ k<x$ 的 $k$ 都不能填在下一位，
- 所有 $ok_{x,k}=\text{false} \ \wedge \ k>x$ 的 $k$，这一位能填的下一位也可以，这一位不能填的下一位也不行。

立即有 $f_{i,sta}$ 表示，现在填完了从高到低前 $i$ 位，下一位能填的数的集合为 $sta$，有多少种方案。枚举下一位填的数 $k$，即得 $sta'$，转移即可。  
令 $w=10$，时间复杂度 $O(n\cdot 2^w \cdot w)$。

### Code Time！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int inf=0x3f3f3f3f3f3f3f3f;
const int mod=998244353;
const int N=50005,M=55;
inline void add(int &a,int b){a=(a+b)%mod;}
int n,m,ans,ed=1023;
bool ok[M][M];
int cur,f[2][1024];
int rst[N],jia[N];
void solve(){
    cin>>n>>m;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            ok[i][j]=1;
    for(int i=1,u,v;i<=m;i++)cin>>u>>v,ok[v][u]=0,ok[u][v]=0;
    for(int i=0;i<10;i++){
        rst[i]=ed;
        for(int j=0;j<i;j++)
            if(!ok[i][j])rst[i]^=(1<<j);
        for(int j=0;j<10;j++)
            if(ok[i][j])jia[i]|=(1<<j);
    }
    cur=0,f[cur][ed]=1;
    for(int i=1;i<=n;i++){
        cur^=1,memset(f[cur],0,sizeof(f[cur]));
        for(int j=0;j<=ed;j++){
            if(!f[cur^1][j])continue;
            f[cur^1][j]%=mod;
            for(int k=0;k<10;k++){
                if(!((j>>k)&1))continue;
                int jj=(j&rst[k])|jia[k];
                f[cur][jj]+=f[cur^1][j];
            }
        }
    }
    for(int i=0;i<=ed;i++)add(ans,f[cur][i]);
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    int aqx=1;
    while(aqx--)solve();
    return 0;
}
```

---

## 作者：irris (赞：2)

## Preface

> dp / 状态压缩 / 去重计数

$*7$，$1400$。感觉是个很简单的好题！！为啥 duel 了半个小时才过，不能要了。

## Solution

考虑钦定一些事情，比如说我们在每个可以交换的等价类里找到一个字典序最小的数 $a$ 并对其计 $1$ 的数。

duel 时想了一些很唐的东西，但是后来突然发现其实不用记录太多信息。具体地，因为我们要求 $a$ 字典序最小，考虑其不最小会发生什么。一定存在数位 $1 \leq i < j \leq n$ 满足 $a_j < a_i$ 且 $j$ **能够交换到** $i$。

邻项交换是一个好东西，这代表了 $j$ 能一直和 $(j-1), (j-2), \ldots, i$ 交换，那么这个信息看起来就是小到能够记录的：毕竟 $j$ 只有 $10$ 种，对于每一种，我们可以直接记录它最远能换到哪里——可以优化到这一段后缀的最小值——可以进一步优化到后缀最小值是否小于 $j$，也即下一个字符能否是 $j$。

据此设计 dp：$f_{i, s}$ 表示已经填入了 $i$ 个字符，下一位能够放置的数的集合是 $s$。转移时枚举 $u \in s$，我们要对 $s$ 进行更新：对于那些 $0 \leq v < u$ 且 $(u, v)$ 能够交换的 $v$，将其从 $s$ 中去除；对于 $(u, v)$ 不能够交换的 $v$，将其向 $s$ 中加入，即可。容易位运算做到 $\mathcal O(1)$。

时间复杂度 $\mathcal O(n \cdot 2^DD)$，其中 $D = 10$ 是进制大小。

## Code

核心代码：

```cpp
for (int i = 0; i < D; ++i) 
	for (int j = 0; j < i; ++j) if (g[i][j]) must_ban[i] |= (1 << j);
for (int i = 0; i < D; ++i) 
	for (int j = 0; j < D; ++j) if (!g[i][j]) must_ok[i] |= (1 << j);
for (int i = 0; i < D; ++i) 
	add(f[1][(Z - 1) ^ must_ban[i]], 1);
for (int i = 1; i < N; ++i) for (int s = 0; s < Z; ++s) 
  for (int n = 0; n < D; ++n) if ((s >> n) & 1) 
    add(f[i + 1][(s & (~must_ban[n])) | must_ok[n]], f[i][s]);
```

---

## 作者：xzy090626 (赞：0)

首先考虑转化问题，对于每组两两可以相互直接或者间接转化的串，我们用一个串来代表它们。显然字典序最小的那个串是一个比较自然的想法。那么现在问题变成：找到这样的字典序不能被转化到更小的等价串的数字串个数。

考虑什么样的串满足条件。对于一个串任意的位置 $i$，如果存在一个 $j<i$ 满足 $a_i<a_j$ 且 $[j,i]$ 中的临项数字都能交换，那就说明它可以被进一步转化成字典序更小的串，也就不合法。

于是考虑状压 dp。设 $f_{i,S}$ 表示当前填到第 $i$ 位，且 $S$ 中的数**不能填**的方案数。那转移的时候就要枚举当前的 $S$，再枚举填的数是 $x\notin S$。那我们还要算一下转移到的 $S^\prime$ 是什么。

枚举 $y\in[0,9]$ 是否在新的集合中，显然与 $x$ 不能交换的一定可以不在新集合中；那么对于剩下的 $y$，枚举 $x< y \leq 9$，既然 $(x,y)$ 可以交换，那接下来不可以填它（因为 $x$ 可以把 $y$ 换掉），加入 $S^\prime$ 中；否则一定可以填。对于 $0\leq y \leq x$，如果 $S$ 不含有 $y$，那么显然是随便填的，否则也不能填。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 7;
const int mod = 998244353;
int a[16][16];
int n,m;
int dp[2][1<<10],f[1<<10][10];
int ans;
void add(int &x,int y){
	x += y;
	if(x>=mod) x -= mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		a[u][v] = a[v][u] = 1;
	}
	dp[0][0] = 1;
	for(int i=1;i<=n;++i){
		memset(dp[i%2],0,sizeof dp[i%2]);
		for(int j=0;j<(1<<10);++j){
			for(int x=0;x<=9;++x){
				if((j&(1<<x))) continue;
				int s = 0;
				for(int y=0;y<=9;++y){
					if(!a[x][y]) continue;
					if(y>x || (j&(1<<y))) s |= 1<<y;
				}
				add(dp[i%2][s],dp[1^i%2][j]);
			}
		}
	}
	for(int i=0;i<1024;++i) add(ans,dp[n%2][i]);
	cout<<ans;
	return 0;
}
```


一点总结：虽然是 \*2700 的 div.2 F，但其实看上去做完也没有那么难。主要的思路瓶颈和难点就在于最小字典序的这个套路，以及这个非常优雅的 dp 状态的设计。

---

