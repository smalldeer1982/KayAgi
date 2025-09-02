# [ABC289D] Step Up Robot

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc289/tasks/abc289_d

無限に続く階段があります。 一番下は $ 0 $ 段目で、$ 1 $ 段のぼるごとに $ 1 $ 段目、$ 2 $ 段目と続きます。

$ 0 $ 段目に階段登りロボットがいます。 階段登りロボットは、一回の動作で $ A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N $ 段ぶん階段をのぼることができます。 つまり、階段登りロボットが $ i $ 段目にいるとき、一回動作をした後は $ i+A\ _\ 1 $ 段目、$ i+A\ _\ 2 $ 段目、⋯、$ i+A\ _\ N $ 段目のいずれかにいることができます。 それ以外の段数を一回の動作でのぼることはできません。 階段登りロボットは階段を下ることもできません。

階段の $ B\ _\ 1,B\ _\ 2,\ldots,B\ _\ M $ 段目にはモチが設置されています。 モチが設置されている段へのぼるとロボットは動けなくなり、他の段に移動することができなくなります。

階段登りロボットは階段のちょうど $ X $ 段目にのぼりたいです。 階段登りロボットが階段のちょうど $ X $ 段目にのぼることが可能か判定してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq10 $
- $ 1\leq\ A\ _\ 1\lt\ A\ _\ 2\lt\cdots\lt\ A\ _\ N\leq10^5 $
- $ 1\leq\ M\leq10^5 $
- $ 1\leq\ B\ _\ 1\lt\ B\ _\ 2\lt\cdots\lt\ B\ _\ M\lt\ X\leq10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

例えば、次のようにして $ 15 $ 段目に到達することができます。 - 階段を $ 3 $ 段のぼる。ロボットは $ 3 $ 段目に移動する。 - 階段を $ 4 $ 段のぼる。ロボットは $ 7 $ 段目に移動する。 - 階段を $ 5 $ 段のぼる。ロボットは $ 12 $ 段目に移動する。 - 階段を $ 3 $ 段のぼる。ロボットは $ 15 $ 段目に移動する。

### Sample Explanation 2

どのように移動しても階段登りロボットが階段のちょうど $ 8 $ 段目にいることはできません。

## 样例 #1

### 输入

```
3
3 4 5
4
4 5 6 8
15```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4
2 3 4 5
4
3 4 5 6
8```

### 输出

```
No```

## 样例 #3

### 输入

```
4
2 5 7 8
5
2 9 10 11 19
20```

### 输出

```
Yes```

# 题解

## 作者：_zzzzzzy_ (赞：2)

## 题意
给你一个长度为 $n$ 的 $a$ 数组和一个长度为 $m$ 的陷阱数组，$b_i$ 表示 $b_i$ 处有一个陷阱。你初始在楼梯的第 $0$ 阶，你可以走 $1\le i\le n\ a_i$ 步，不能走到陷阱上，问最后能不能走到第 $x$ 阶。
## 思路
典型的 DP 题，设 $dp_{i}$ 为是否能够走到第 $i$ 个楼梯，当 $dp_i$ 为 $1$ 时用这个来转移 $n$ 个台阶。

```cpp
for(int i=0;i<=x;i++){
	if(dp[i])
		for(int j=1;j<=n;j++){
			if(!vis[i+a[j]])//不能转移到陷阱上
				dp[i+a[j]]=1;
	}
}
```

最后判断 $dp_x$ 是否为 $1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000050;
int dp[maxn],vis[maxn];
int a[maxn],b[maxn];
signed main(){
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i];}
	cin>>m;
	for(int i=1;i<=m;i++){cin>>b[i];vis[b[i]]=1;}
	int x;
	cin>>x;
	dp[0]=1;
	for(int i=0;i<=x;i++){
		if(dp[i])
			for(int j=1;j<=n;j++){
				if(!vis[i+a[j]])
					dp[i+a[j]]=1;
			}
	}
	if(dp[x])cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：zzx0102 (赞：2)

**题意**

给定 $n$ 个整数 $a_1,a_2,a_3\cdots a_n$ 和 $m$ 个整数 $b_1,b_2,b_3\cdots b_m$。

现在有一个机器人，在 $0$ 处，他每一步可以往前走 $a_i$ 步（$1\leq i\leq n$），但是它如果到了 $b_i$（$1\leq i\leq m$）的话，它就会回到原处，问机器人能否到达 $X$ 处。

这不就是个 bfs 吗？？？

直接从 $0$ 开始，然后一直往前走，每次加 $a_i$ 步，当然，如果走到 $b_i$ 了，就停下。

我们可以先标记所有 $b_i$ 的点，然后只要 $vis_i=1$ 的都结束了，不用走了，当然，走到一个 $x$ 处，也要标记。

然后如果走到 $x$，就可以了，没有走到，就不行，搞定！

当然，你也可以用 dfs 做。

代码就没用任何必要了吧。就是个普普通通的 bfs。

---

## 作者：ReeChee (赞：1)

## Problem

有一机器人初始在 $0$ 级阶梯，对于每一级阶梯，机器人可以从 $1\sim N$ 种任选一个 $i$ 走 $A_i$ 步，同时有 $M$ 个障碍在 $B_i$ 级阶梯，若走到障碍则将无法移动，问能否通过某种方案使机器人到达第 $X$ 级阶梯。

$1\leq N\leq 10$，$1\leq M\leq 10^5$，$1\leq X\leq 10^5$，$A_i$ 和 $B_i$ 严格单调递增。

## Solution

考虑使用动态规划（或可以直接称其为标记），设 $f_i$ 为能否到达第 $i$ 层阶梯。

那么初始状态为 $f_0=1$，其它均为 $0$。

考虑到 $N$ 最大仅为 $10$，故可以在每层阶梯 $i$ 直接枚举步数，若可以被之前的点走到（即 $f_{i-A_j}=1$）则 $f_i=1$，反之则 $f_i=0$，最后判断 $f_X$ 的值即可。

时间复杂度 $\mathcal{O}(NX)$。

## Code

```cpp
signed main(){
    f[0]=1;
    n=read();
    F(i,1,n) a[i]=read();
    m=read();
    F(i,1,m) isTrap[read()]=1;
    x=read();
    F(i,a[1],x) // 直接从 a[1] 开始枚举，因为前面的点不可能会被更新，且 a[i] 严格单调递增，所以无需排序。
        for (int j=1;j<=n&&i-a[j]>=0&&!f[i]&&!isTrap[i];++j) // 若枚举过程中已经使 f[i]=1 了，则无需再枚举。
            f[i]=f[i-a[j]]&1;
    puts(f[x]?"Yes":"No");
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

### 题意

一个机器人在一个台阶上，最开始它处于 $0$ 级，它每次可以选择 $a_1,a_2,a_3,\ldots,a_n$ 中任意一个数 $a_i$，然后往上跳 $a_i$ 级。第 $b_1,b_2,b_3,\ldots,b_m$ 级台阶上有陷阱，机器人不能跳到这些陷阱上。问在不跳到任何陷阱上时能否跳到第 $x$ 级。

### 解法

记忆化搜索。

我们可以用一个数组 $vis$ 表示一级台阶是否被走到过，如果走到超过 $x$ 就停止，dfs 爆枚即可。

具体见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100005;
ll n,m,x,a[maxn],b,buc[maxn],vis[maxn];
void dfs(ll pos){
	vis[pos]=1;
	if(pos>=x) return;
	for(int i=1;i<=n;i++){
		if(buc[pos+a[i]]) continue;
		if(!vis[pos+a[i]]) dfs(pos+a[i]);
	}
}
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++){
    	cin>>b;
    	buc[b]=1;
	}
    cin>>x;
    dfs(0);
    if(vis[x]) cout<<"Yes";
    else cout<<"No";
    return 0;
}
```
当然你也可以不用递归，[here](https://atcoder.jp/contests/abc289/submissions/38802239)。

[AT 赛时记录](https://atcoder.jp/contests/abc289/submissions/38802239)

---

## 作者：Crazyouth (赞：0)

**题意简述**

给定数组 $a,b$，数组 $a$ 表示机器一次可以走的所有距离，数组 $b$ 表示在所有点 $b_i$ 有陷阱，不能踩上去。现在机器在点 $0$，问它能否到达点 $x$。

**分析**

这题很明显是 dp 题。那么讲一下这题的 dp 三要素。

1. 状态。我们用 $dp_i$ 表示点 $i$ 能否到达。
1. 决策。很简单，如 $1$ 所讲，我们只需要判断 $dp_x$ 是否为 $0$ 即可。
1. 转移。首先，如果 $dp_i$ 上有陷阱，$dp_i$ 就是 $0$，否则对每个 $dp_i$ 判断 $dp_{i-a_j}$，如果有 $dp_{i-a_j}$ 为 $1$，那么 $dp_i$ 就是 $1$。

**AC Code**
```
#include <iostream>
#include <cstring>
using namespace std;
int dp[int(1e5+5)],a[11],b[int(1e5+5)];
int main()
{
	int n,m,x,tp;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>tp;
		b[tp]=1;//记录是不是陷阱
	}
	cin>>x;
	dp[0]=1;
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i>=a[j])
        	{
				if(!b[i-a[j]]&&dp[i-a[j]]==1) dp[i]=1;//状态转移方程
			}
		}
	}
	if(dp[x]) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```


---

## 作者：_dijkstra_ (赞：0)

简单博弈论。

## 思路

对于不可以踩的台阶，直接标记 $no_i = \text{true}$ 即可。

然后是简单 DP。设 $dp_i$ 表示能否到达这一步。

首先 $dp_0 = \text{true}$。然后就是暴力转移：

$$dp_i = \textbf{OR}_{j = 1}^n dp_{i - a_j}(i \ge a_j)$$

其中 $\textbf{OR}$ 表示全部数的或值。

答案就是 $dp_x$。

## 代码

```cpp
void solve()
{
    int n, m, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int x;
        scanf("%d", &x);
        no[x] = true;
    }
    scanf("%d", &x);

    dp[0] = true;
    for (int i = 1; i <= x; i++)
        for (int j = 1; j <= n; j++)
            if (i >= a[j] && !no[i - a[j]])
                dp[i] |= dp[i - a[j]];
    if (dp[x]) puts("Yes"); else puts("No");
}
```

---

## 作者：Mikefeng (赞：0)

# [ABC289D] Step Up Robot

## 题目翻译

一个机器人上台阶，每次可以上 $a_i(1\le i\le n)$ 步。有 $m$ 个台阶上有陷阱，不能上到有陷阱的台阶。问机器人能否上到第 $k$ 个台阶。

$1\le n\le 10,1\le m,k\le 10^5$

## 做法

简单 dp，每次枚举能从哪个台阶转移过来，跳过有陷阱的台阶，看最后 $f_k$ 是 $1$ 还是 $0$。

时间复杂度 $O(nk)$。

## 代码

```cpp
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int N=15;
const int M=1e5+5;
int n,m,k;
int a[N];
bool f[M],vis[M];
int main(){
	n=read();
	F(i,1,n) a[i]=read();
	m=read();
	F(i,1,m) vis[read()]=1;
	k=read();
	f[0]=1;
	F(i,1,k){
		if(vis[i]) continue;
		F(j,1,n){
			if(a[j]>i) continue;
			f[i]|=f[i-a[j]];
		}
	}
	if(f[k]) puts("Yes");
	else puts("No");
	return 0;
}
```


---

