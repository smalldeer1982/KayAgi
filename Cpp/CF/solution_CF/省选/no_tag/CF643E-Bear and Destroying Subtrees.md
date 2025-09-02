# Bear and Destroying Subtrees

## 题目描述

Limak is a little grizzly bear. He will once attack Deerland but now he can only destroy trees in role-playing games. Limak starts with a tree with one vertex. The only vertex has index $ 1 $ and is a root of the tree.

Sometimes, a game chooses a subtree and allows Limak to attack it. When a subtree is attacked then each of its edges is destroyed with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643E/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png), independently of other edges. Then, Limak gets the penalty — an integer equal to the height of the subtree after the attack. The height is defined as the maximum number of edges on the path between the root of the subtree and any vertex in the subtree.

You must handle queries of two types.

- 1 v denotes a query of the first type. A new vertex appears and its parent is $ v $ . A new vertex has the next available index (so, new vertices will be numbered $ 2,3,... $ ).
- 2 v denotes a query of the second type. For a moment let's assume that the game allows Limak to attack a subtree rooted in $ v $ . Then, what would be the expected value of the penalty Limak gets after the attack?

In a query of the second type, Limak doesn't actually attack the subtree and thus the query doesn't affect next queries.

## 说明/提示

Below, you can see the drawing for the first sample. Red circles denote queries of the second type.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643E/777188abb62f6899b2444c48e8d5cee93e2feb50.png)

## 样例 #1

### 输入

```
7
1 1
1 1
2 1
1 2
1 3
2 2
2 1
```

### 输出

```
0.7500000000
0.5000000000
1.1875000000
```

## 样例 #2

### 输入

```
8
2 1
1 1
1 2
1 3
1 4
2 1
1 4
2 1
```

### 输出

```
0.0000000000
0.9375000000
0.9687500000
```

# 题解

## 作者：zsplj_ (赞：11)

### 题解

我们发现即使子树很深，随机删边后深度仍然很大的概率非常小，具体地，其深度大于 $60$ 的概率远小于 $10^{-6}$，所以我们只需要考虑深度 $\leqslant 60$ 的情况即可。

设 $f(x,i)$ 为，子树 $x$ 随机删边后，其深度 $\leqslant i$ 的概率（这里的深度为点的深度，即题目要求的答案+1）。那么：
$$
f(x,i)=\prod_{c\in son(x)}\frac{1}{2}\times(f(c,i-1)+1)
$$
节点 $x$ 的子树深度期望即为：
$$
\sum_{i=1}^{60}i\times[f(x,i)-f(x,i-1)]
$$
我们认为 $f(x,60)=1$，化简上式为 $60-\sum\limits_{i=1}^{59}f(x,i)$。

新增一个节点时，会对其上面 $60$ 层的祖先造成影响，并且对于这个节点的第 $i$ 级祖先 $y$，只有 $f(y,i)$ 的值会受影响。所以对于它的某个祖先我们可以 $O(1)$ 更新其 $f$ 值的变化。

时间复杂度 $O(q\times Max_H)$，其中 $Max_H$ 我们设为 $60$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=500005;
const int D=60;

inline int read(){
	register int x=0,w=1,ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-48;
	return w*x;
}

int q,tot,fa[maxn];
double f[maxn][D+2];

int main(){
	q=read(),tot=1;
	for(int i=1;i<=D;i++)f[1][i]=1;
	for(int op,x;q--;){
		op=read(),x=read();
		if(op==1){
			vector<int> v;
			fa[++tot]=x,x=tot;
			for(int i=1;i<=D;i++)f[x][i]=1;
			for(int i=1;i<=D+1&&x;i++)v.push_back(x),x=fa[x];
			for(int i=v.size()-2;i>0;i--)
				f[v[i+1]][i+1]/=(f[v[i]][i]+1)/2.0;
			for(int i=0;i+1<v.size();i++)
				f[v[i+1]][i+1]*=(f[v[i]][i]+1)/2.0;
		}
		else{
			double ans=D-1;
			for(int i=1;i<D;i++)ans-=f[x][i];
			printf("%.10lf\n",ans);
		}
	}
	return 0;
}
```



---

## 作者：5_Lei (赞：7)

无视误差的思路确实非常厉害，但是对于我这样的蒟蒻来说，这道题的难点在于 DP 方程（捂脸）。在经过 n 个小时的挣扎后，我终于搞懂了所有疑问，特意发一篇题解来帮助和我一样的 xd。    

我们首先来看 DP 方程：  

$$
f[u][i]=\prod (\frac {1}{2} \times f[son][i-1] + \frac {1}{2}) $$

**问题一：DP 方程的含义。**  

答 ：$f[u][i]$ 表示以 $u$ 为根，深度 $\leq i$ 的概率。  

对于 $u$ 的每一条指向自己儿子的边，有二分之一的概率不断，那么我们需要让这个儿子的深度 $\leq i-1$，所以需要 $\frac {1}{2} \times f[son][i-1]$。

有二分之一的概率断掉，此时更新 $f[u][i]$ 就不需要再考虑这个断掉的儿子，直接加上二分之一即可。

**问题二：为什么加入一个新点 $x$ 后不需要把 $60$ 个祖先，从深度 $1$ 到 $60$ 挨个更新一遍**。  

答：设 $u$ 为 $x$ 的 $k$ 级祖先（$fa[x]$ 为一级，设 $y = fa[x]$，我们更新 u 只更新 $f[u][k]$ 即可。 

因为 $f[y][i] (i \geq 2)$ 相比加入 $x$ 之前，多乘了一个 $(\frac {1}{2} \times f[x][i-1] + \frac {1}{2})$，而 $f[x][i-1]$ 又都为  $1$，所以 $f[y][i]$ 不变，自然就不需要往上更新了。而 $f[x][0] = 0$，所以需要往上更新。  

**问题三：如何统计答案。**  

答：正常期望的答案统计就是概率乘事件贡献，这道题就是 $\sum _{i\leq60} (f[x][i] - f[x][i-1]) \times i$。而有些题解写的很奇怪。如下面这一段代码，其实就是将式子化简了一下，建议自己化一下式子。

**还有一个非常重要的问题，直接看代码注释吧。**

```cpp
	db ans = h-1;
    //这里减 1 ，是因为题目求的最大深度与我们DP设的最大深度不太一样，题目求的是子树最大深度，需要减 1。
	for(int i = 1 ; i <= h-1 ; i++)ans -= dp[x][i];
	printf("%.10lf\n",ans);
```


---

## 作者：ywy_c_asm (赞：4)

先考虑只询问一次的$O(n^2)$暴力咋做。

$dp[i][j]$为i的子树最大深度是j时的概率。然后如果i的子树的最大深度为j，那么，它必定有**至少一个**儿子子树的最大深度为$j-1$，那么我们考虑容斥，令$s[i][j]$为dp的前缀和，那么就是所有儿子的最大深度都小于等于j-1的概率减去都小于j-2的概率（还要算上这条边），令$p[i][j]=\prod_{ch}(\frac{s[ch][j]}2+\frac 1 2)$，即所有儿子都小于等于j的概率，要除2再加上$\frac 1 2$是因为连接儿子的边可以断，也可以不断，如果不断的话那么儿子的深度就必须$<=j$，如果断的话儿子的深度是啥就没用了，我们强制认为此时儿子深度是无限小。那么$dp[i][j]=p[i][j-1]-p[i][j-2]$。

考虑有修改咋做。这里就涉及到一个trick：**输出的答案为浮点数的时候可以考虑少算一些精度能够忽略不计的东西**，这个基本上都是在概率题上用的。我们发现$dp[i][j]$这个状态就已经是$O(n^2)$了，但是，注意到如果后一维很大的话，那么概率会到$\frac 1{2^j}$的级别，此时已经非常低了，那么我们可以只算$j<=B$时的答案，把$B$取到50差不多就能够满足时间和精度了。那么每次加点的时候暴力往上跳至多$B$个祖先，那个维护儿子乘积的p数组可以$O(1)$动态修改，每次在这个点上暴力$O(B)$更新一遍dp值即可。$O(nB^2)$。~~我最慢一个点4991ms……~~

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#define N 500010
#define lg 50
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	int fa[N];
	double s[N][lg + 2], p[N][lg + 2], dk[N];
	int deg[N], deep[N];
	void ywymain() {
	    int q = get(), gpt = 2;
	    dk[0] = 1;
	    for (register int i = 1; i <= q; i++) dk[i] = dk[i - 1] / 2;
	    for (register int i = 0; i <= lg; i++) s[1][i] = p[1][i] = 1;
	    while (q) {
	        q--;
	        int op = get(), x = get();
	        if (op == 1) {
	            int me = gpt;
	            gpt++;
	            fa[me] = x;
	            deg[x]++;
	            deep[me] = deep[x] + 1;
	            for (register int i = 0; i <= lg; i++) s[me][i] = p[me][i] = 1;
	            for (register int cur = x; cur && deep[me] - deep[cur] <= lg; cur = fa[cur]) {
	                if (fa[cur]) {
	                    for (register int i = 0; i <= lg; i++) {
	                        p[fa[cur]][i] /= ((s[cur][i] + 1) / 2);
	                    }
	                }
	                s[cur][0] = dk[deg[cur]];
	                p[fa[cur]][0] *= ((s[cur][0] + 1) / 2);
	                for (register int i = 1; i <= lg; i++) {
	                    double dp;
	                    if (i == 1)
	                        dp = p[cur][0] - s[cur][0];
	                    else
	                        dp = p[cur][i - 1] - p[cur][i - 2];
	                    s[cur][i] = s[cur][i - 1] + dp;
	                    p[fa[cur]][i] *= ((s[cur][i] + 1) / 2);
	                }
	            }
	        } else {
	            double ans = 0;
	            for (register int i = 1; i <= lg; i++) ans += (s[x][i] - s[x][i - 1]) * i;
	            printf("%.10lf\n", (double)ans);
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：CarroT1212 (赞：3)

+ 关键词：树，期望 DP，诈骗。

当一个期望题要求你输出小数而不是取模的时候可以注意一下。如果你是出题人的话你会愿意无缘无故写个 SPJ 判掉误差吗？

比如这题。首先一个点与根连起来当且仅当它们之间所有边都没有消失，概率为 $\dfrac{1}{2^{h_i}}$。这样才有可能影响到答案。

问题来了，这玩意能有多大？

当 $h_i$ 达到 $60$ 左右的时候它会直接从你输出的答案里消失，不管乘了 $n$ 还是什么的都没有用。所以你根本不用考虑 $h_i$ 更大的情况。

设 $K=60$，于是就往 $O(nK)$ 的东西想吧！求期望不得不提概率，考虑直接设 $dp_{i,j}$ 为第 $i$ 个点的子树深度为 $j$ 的概率。乘上深度即得期望。

但是发现因为深度是取所有点的最大值，直接硬算就把深度精确到个位数实在是太难了，还有算重的问题。考虑参考容斥的思路，改成设 $dp_{i,j}$ 为第 $i$ 个点的子树深度不大于 $j$ 的概率。差分乘上深度即得期望。

那么有 $dp_{i,j}=\prod\limits_{k}(\dfrac{1}{2}dp_{k,j-1}+\dfrac{1}{2})$，其中 $k$ 为 $i$ 的儿子。前一项表示 $(i,k)$ 连着，后一项表示 $(i,k)$ 断了。显然断的情况不需要考虑下面连了多远，所以直接是 $\dfrac{1}{2}$。

还没做完，有加点。那么每次就是把 $dp_{n,0\sim K}$ 全部赋成 $1$，$dp_{n,-1}$ 是 $0$。根据方程式，只有这个 $dp_{n,-1}$ 会影响到它上面祖先的 DP 值（其它的算出来都是 $1$），每次六十个，直接更新即可。

注意因为下标问题，实际写的时候要把上面所有的深度值加 $1$。

```cpp
ll q,fa[N],now[N],n;
ld dp[N][K];
int main() {
	scanf("%lld",&q);
	n=1;
	for (ll i=1;i<=60;i++) dp[n][i]=1;
	for (ll opt,x;q--;) {
		scanf("%lld%lld",&opt,&x);
		if (opt==1) {
			fa[++n]=x;
			vector<ll> v;
			for (ll i=1;i<=60;i++) dp[n][i]=1;
			for (ll i=0,p=n;i<=60&&p;i++,p=fa[p]) v.pb(p);
			for (ll i=(ll)v.size()-1;i>1;i--) dp[v[i]][i]/=dp[v[i-1]][i-1]/2.0+0.5;
			for (ll i=1;i<v.size();i++) dp[v[i]][i]*=dp[v[i-1]][i-1]/2.0+0.5;
		}
		else {
			ld res=0;
			for (ll i=1;i<=60;i++) res+=(dp[x][i]-dp[x][i-1])*(i-1);
			printf("%.15Lf\n",res);
		}
	}
	return 0;
}
```

~~但是代码跟第一篇题解是不是长得太像了点。~~

---

## 作者：Kelvin2009 (赞：1)

这是一道期望 dp 加精度剪枝。

首先考虑每条边的贡献。设一条路径的长度为 $i$，则这条路径在随机删边后的保存概率为 $(\frac{1}{2})^i$，整条路至多作出 $i\cdot(\frac{1}{2})^i$ 的贡献。

对于精度限制 $10^{-6}$，考虑数值累加，可以发现：
$$100\cdot(\frac{1}{2})^{100}\llless 10^{-20}$$ 

这意味着，长度大于 $100$ 的路径对近似值不会产生任何影响。

设 $dp_{u,i}$ 表示以 $u$ 为根的子树中，不会出现长度大于 $i$ 的路径的概率。

设 $son_u$ 为 $u$ 的儿子节点的集合，则：
$$dp_{u,i}=\displaystyle\prod_{v\in son_u}(\frac{1}{2}\cdot dp_{v,i-1}+\frac{1}{2})$$ 

考虑最大深度期望：若以 $u$ 为根的子树中最大深度为 $dep$，对于其合法概率，有：
$$P(dep)=dp_{u,dep+1}-dp_{u,dep}$$ 

可得：
$$E(dep)=dep\cdot(dp_{u,dep+1}-dp_{u,dep})$$ 

将 $E(dep)$ 累加并化简后：
$$ans_u=100*dp_{u,101}-\displaystyle\sum_{dep=1}^{100}dp_{u,dep}$$ 

即为操作 2 的输出值。


---

代码：


---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int lim=101;
const int range=5e5+5;
int pos=1,fa[range];
double dp[range][105];
int q,len,dep[range],rec[range];
int main()
{
	dep[1]=1;
	scanf("%d",&q);
	for(int i=1;i<=lim;i++) dp[1][i]=1.0;
	while(q--)
	{
		int op,u;
		scanf("%d%d",&op,&u);
		if(op==1)
		{
			len=0,pos++;
			fa[pos]=u,dep[pos]=dep[u]+1;
			rec[len]=pos;
			for(int i=1;i<=lim;i++) dp[pos][i]=1.0;
			for(int i=1;i<lim && u;i++)
			{
				rec[++len]=u;
				u=fa[u];
			}
			for(int i=len-1;i;i--)
			{
				int v=rec[i];
				dp[fa[v]][i+1]/=(dp[v][i]*0.5+0.5);
			}
			for(int i=0;i<len;i++)
			{
				int v=rec[i];
				dp[fa[v]][i+1]*=(dp[v][i]*0.5+0.5);
			}
		}
		else
		{
			double ans=1.0*(lim-1)*dp[u][lim];
			for(int i=lim-1;i;i--) ans-=dp[u][i];
			printf("%.10lf\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [CF643E](https://www.luogu.com.cn/problem/CF643E)     

发现题目不要求对答案取模，而且当深度很大（大于 60）的时候概率可以忽略不计，于是只考虑深度在 60 以内的。   

令 $dp_{i,j}$ 表示 $i$ 子树深度小于等于 $j$ 的概率，则答案等于 $61-\sum_{i=0}^{60}dp_{x,i}$。$dp_{i,j}=\prod_{u\in son(i)}{0.5\times(1+dp_{u,j-1})}$。     

当新加入一个点时，显然只会对上面最多 60 级祖先造成影响，并且每个祖先只会被影响一个 dp 值。     

具体的，第 $i$ 级祖先（父亲为第 1 级）$p_i$ 会被影响的 dp 值为 $dp_{p_i,i-1}$。因为 dp 的计算式是乘积形式，所以可以先把之前的贡献除掉，再修改为新的 dp 值。复杂度 $O(qh)$，$h$ 为设定的最大考虑深度。   

代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,tot,k1,k2,k3,k4,k5,k6,k7,k8,k9,fa[500003];
double ans,dp[500003][62];
int stk[500003],tots;
int main(){
    ios::sync_with_stdio(false);
    tot=1;
    for(int i=0;i<=60;i++)dp[1][i]=1;
    cin>>q;
    while(q--){
        cin>>k1>>k2;
        if(k1==1){
            tot++;
            fa[tot]=k2;
            tots=0;
            for(int i=tot,j=0;j<=60&&i!=0;j++,i=fa[i])stk[++tots]=i;
            for(int i=tots-1;i>1;i--)dp[stk[i+1]][i-1]/=0.5*(1.0+dp[stk[i]][i-2]);
            for(int i=0;i<=60;i++)dp[tot][i]=1;
            dp[stk[2]][0]*=0.5;
            for(int i=3;i<=tots;i++)dp[stk[i]][i-2]*=0.5*(1.0+dp[stk[i-1]][i-3]);
        }
        else{
            ans=61;
            for(int i=0;i<=60;i++)ans-=dp[k2][i];
            
            cout<<fixed<<setprecision(10)<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Leasier (赞：1)

有点诈骗喵。

------------

首先考虑暴力怎么做。

设 $dp_{u, i}$ 表示 $u$ 子树深度 $\leq i$ 的概率。

初值：$\forall u \in \operatorname{leaf}, i \geq 1$，$dp_{u, i} = 1$。

转移：$dp_{u, i} = \displaystyle\prod_{v \in son_u} \frac{dp_{v, i - 1} + 1}{2}$。

答案：$\displaystyle\sum_{i = 1} (1 - dp_{x, i})$。

考虑优化，注意到题目要求我们输出**浮点数**，由于每层向上值都会除以 $2$，则我们其实只关心 $\forall j \leq S, dp_{x, j}$，其中 $S = O(\log \frac{1}{\epsilon})$。

于是我们每次向上维护 $S$ 级父亲的 dp 值即可。时间复杂度为 $O(nS)$。

我的代码中取 $S = 60$。

代码：
```cpp
#include <stdio.h>

const int N = 5e5 + 7, M = 60;
int fa[N];
double dp[N][M + 7];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int main(){
	int q = read(), n = 1;
	for (int i = 1; i <= M; i++){
		dp[1][i] = 1.0;
	}
	for (int i = 1; i <= q; i++){
		int t = read(), x = read();
		if (t == 1){
			int u = ++n;
			double pre = 1.0;
			fa[u] = x;
			for (int j = 1; j <= M; j++){
				dp[u][j] = 1.0;
			}
			for (int j = 1, k = u; j <= M && fa[k] != 0; j++, k = fa[k]){
				double cur = dp[fa[k]][j];
				dp[fa[k]][j] *= (dp[k][j - 1] + 1.0) / (pre + 1.0);
				pre = cur;
			}
		} else {
			double ans = 0.0;
			for (int j = 1; j <= M; j++){
				ans += 1.0 - dp[x][j];
			}
			printf("%.8lf\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

很喜欢的题，套路合集。

## 思路

考虑给你一棵树你怎么计算。

记 $dp_{i,j}$ 表示 $i$ 子树深度为 $j$ 的概率。

转移时可以枚举两边的深度转移，复杂度 $O(n^3)$。

考虑优化，考虑到转移是取 $\max$，故可以分别先做前缀和，并转移，具体考虑将两个 $f,g$ 合并，先对其做前缀和得到 $f',g'$，然后不难发现答案 $h_i=f'_i\times g_i+f_i\times g'_{i-1}$。具体原因就是两种情况，一边转移的 $i\leq j$，一种 $i>j$。

此时我们可以 $O(n^2)$ 解决这个问题。

考虑到要求输出概率，故只要考虑该层以下 $50$ 层的情况。（证明见证明 $1$）

此时复杂度降低为 $O(50n)$。

考虑原问题，要求修改。记 $n$ 为节点数。

同样地，我们需要向上推 $50$ 层。对于每层都要用 $O(50)$ 的复杂度去进行 $dp$ 反演（即去掉一个子树），然后去添加该子树。$dp$ 反演可以从后往前操作，维护两个前缀和解方程即可。

则复杂度变为 $O(50^2n)$。无法通过。

考虑改变 $dp$ 状态。**考虑 $dp_{i,j}$ 表示 $i$ 子树深度小于等于 $j$ 的概率**。

大多数情况下，这种转移均可以使用改变定义为原状态前缀和的方式去优化。

此时如何转移？显然如果 $i$ 子树深度小于等于 $j$，$i$ 的每个儿子 $c$ 均必须小于等于 $j-1$，或边断掉。概率相乘即可。

这样优化有什么好处？转移时状态不是依然是 $O(50)$ 的吗？

容易观察到性质加入一个 $dep$ 层的对 $dep-1$ 层的影响只有 $0$ 和 $1$ 状态，对 $dep-2,\dots,dep-i,\dots,dep-50$ 层的影响只有 $i$ 或 $i+1$ 状态。这种情况下，反演时会变得更加方便（单点反演复杂度 $O(1)$），故总复杂度 $O(50n)$，可以通过。

### 证明 $1$

考虑在什么情况下可以给你卡到误差最大值，不难发现是 $10^4$ 条链，每条链长 $50$。

这种情况下，考虑最深的情况的概率，每条链所有边都存在概率为 $2^{-50}$，所有边都不连的概率为 $(1-2^{-50})^{10000}$。如何估算？~~计算器~~，考虑 $(1-2^x)^2$ 等于 $1-2\times2^x+2^{2x}$ 约等于 $1-2^{x+1}$，$(1-2^{50})^{10000}$ 约等于 $(1-2^{50})^{2^{17}}$ 约等于 $1-2^{50-17}$。精度误差大约在 $10^{-9}$ 级别。考虑到还要乘上深度 $50$，总误差在 $10^{-7}$ 级别，可以通过。

## 代码

```
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
using namespace std;
double dp[500005][55];
int fa[500005];
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
void endl(){
	putchar(10);
}
signed main(){
	int q=read(),cnt=1;
	for(int i=0;i<=50;i++) dp[1][i]=1;
	while(q--){
		int opt=read();
		if(opt==1){
			int f=read(); fa[++cnt]=f;
			for(int i=0;i<=50;i++) dp[cnt][i]=1;
			int now=cnt;
			vector<int> vc;
			for(int i=1;i<=50&&now;now=fa[now],i++){
				vc.push_back(now);
			}
			for(int i=vc.size()-1;i>=2;i--){
				int fp=vc[i],np=vc[i-1];
				dp[fp][i]/=(dp[np][i-1]+1)/2;
				dp[fp][i-1]/=(dp[np][i-2]+1)/2;
			}
			dp[fa[cnt]][0]/=2;
			for(int i=1;i<vc.size();i++){
				int fp=vc[i],np=vc[i-1];
				dp[fp][i]*=(dp[np][i-1]+1)/2;
				if(i>1) dp[fp][i-1]*=(dp[np][i-2]+1)/2;
			} 
		}
		else{
			int x=read();
			double ans=0;
			for(int j=1;j<=50;j++){
				(ans+=(dp[x][j]-dp[x][j-1])*j);
			}
			cout<<fixed<<setprecision(6)<<ans<<"\n";
		}
	}
	return 0;
}
```

写起来还是比较容易的。

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给你一棵初始只有根为 $1$ 的树。

共有 $q$ 次操作。

```1 x``` 表示加入一个以 $x$ 为父亲的新点。

```2 x``` 表示求以 $x$ 为根的子树期望最深深度。

每条边都有 $\dfrac{1}{2}$ 的概率断裂。

$1\leq q\leq 5\times 10^5$。

## $\text{Solution}$
这题很 CF...  
注意到，当链很长的时候不被断开的概率是极低的。  
具体的，当链长超过 $60$，对答案的影响完全可以忽略不计。  
（经过实测，其实只考虑到 $40$ 都是没问题的。  

这样本题就好办多了。  
但依然没有显然。  
由于本来答案取 $\max$ 的性质，设计 $dp_{x,i}$ 表示子树内答案小于等于 $i$ 的概率。  
那么就有转移：
$$dp_{fa,k+1}=\prod \frac{1}{2}\times (dp_{son,k}+1)$$

每次加新点对 $60$ 个祖先都只会改一层的 dp，所以直接暴力修改即可。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5e5+100;
#define ll long long
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,tim;
double dp[N][62];
int fa[N],tot=1,o=60;
void remove(int x,int k){
  if(!fa[x]||k>=o||!x) return;
  remove(fa[x],k+1);
  dp[fa[x]][k+1]/=(0.5*(dp[x][k]+1));
  return;
}
void upd(int x,int k){
  if(!fa[x]||k>=o||!x) return;
  dp[fa[x]][k+1]*=0.5*(dp[x][k]+1);
  //printf("fa=%d *=%lf\n",fa[x],0.5*(dp[x][k]+1));
  upd(fa[x],k+1);
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=o;i++) dp[1][i]=1;
  for(int i=1;i<=n;i++){
    int op=read(),x=read();
    if(op==1){
      fa[++tot]=x;x=tot;
      for(int j=1;j<=o;j++) dp[x][j]=1;
      remove(fa[x],1);
      upd(x,0);
    }
    else{
      double ans=o-1;
      for(int i=1;i<o;i++) ans-=dp[x][i];
      printf("%.10lf\n",ans);
    }
  }
  return 0;
}
/*

*/

```


---

## 作者：dd_d (赞：0)

## Sol
考虑 dp。  
记 $f_{u,i}$ 表示以 $u$ 为根的子树，最长链不超过 $i$ 的概率。很容易得出转移方程：$f_{u,i}=\prod_{v \in son(u)} \frac{1}{2}(f_{v,i-1}+1)$  
时间复杂度 $O(q^3)$。  
考虑优化。  
可以发现 $f_{u,i}$ 只与 $f_{v,i-1}$ 有关，所以对于加点操作，$v$ 的每个祖先的 DP 值只会改一个位置，暴力修改即可。  
时间复杂度 $O(q^2)$。  
用长链剖分优化上述 DP 也可以将时间复杂度降至 $O(q^2)$。    
复杂度还是不够优，考虑继续优化。  
容易发现，当链的长度很大时 $f_{u,i}$ 与 $1$ 的误差可以忽略不计。  
在本题的限制下 $i$ 的值为 $60$。  
因此，我们在 dp 时只保留前 $60$ 个状态即可。  
最后查询以 $x$ 为根的子树内的最长链的期望为 $\sum_{i=1}^{60}i \times[(f_{x,i}-f_{x,i-1})]$  
时间复杂度 $O(60 \times q)$。 可以通过本题。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=6e5+1;
int n,Q,f[N];
double dp[N][101];
signed main()
{
//	freopen("structure.in","r",stdin);
//	freopen("structure.out","w",stdout);
	n=1;
	for (int i=0;i<60;i++)
		dp[1][i]=1;
	Q=read();
	while (Q--)
	{
		int opt=read(),v=read();
		if (opt==1)
		{
			int u=++n;
			f[u]=v;
			for (int i=0;i<60;i++)
				dp[u][i]=1;
			double now=1;
			for (int i=0,x=u;f[x]!=0&&i<60;i++,x=f[x])
			{
				double NOW=dp[f[x]][i];
				dp[f[x]][i]/=1+now;
				dp[f[x]][i]*=1+(i>0?dp[x][i-1]:0);
//				printf("%.10lf\n",dp[f[x]][i]);
				now=NOW;
			}
		}
		else
		{
			double ans=0;
			for (int i=1;i<60;i++)
				ans+=(dp[v][i]-dp[v][i-1])*i;
			printf("%.10lf\n",ans);
		}
	}
}

/*
7
1 1
1 1
2 1
1 2
1 3
2 2
2 1
*/

```


---

## 作者：zzw4257 (赞：0)

评分`2700`,**看**了题解

额，dp本来就会，但看了正解关键在**无视误差**

> 维护一棵初始为空的树支持维护
>
> - 加入一个点并以$x$为父亲
> - 询问以$x$为根的子树内最深点深度的期望
>
> 其中每条边断掉概率为$\frac{1}{2}$
>
> 注明一下:所谓子树内最深点是和根相连接联通块中深度最大的点

因为$E(\max)\neq\max(E)$所以直接一维做很吃力，你发现不可能只依赖点来转化

不如把期望拆成概率

第一个技巧：问题求最大，并且每一步都要取到，设的时候不应设刚好

$f_{x,d}$表示$x$子树内最大深度$\leqslant d$的概率

则
$$
f_{x,d}=\frac{\sum_{y}f_{y,d-1}+1}{2}
$$
最大刚好为$d$的概率就是$f_{x,d}-f_{x,d-1}$

发现增加一个点只会影响到根链上的点

于是$\mathcal O(n\max{D})$

然后轻轻松松炸掉

第二个技巧：方程中隔得越远贡献越小时，并且输出浮点数时可以考虑计算误差极限

事实上对于$x$贡献其$K$级祖先量级是$\frac{1}{2^K}$级别的，在本题精度要求下$K=50$即可

```cpp
if(opt==1){
    fa[++tot]=x;
    for(i=0;i<lim;++i)f[tot][i]=1;
    pre=f[x][0];f[x][0]*=0.5;
    for(i=1;i<lim&&x;++i,x=fa[x])now=f[fa[x]][i],f[fa[x]][i]*=(0.5+0.5*f[x][i-1])/(0.5+0.5*pre),pre=now;
}
if(opt==2){for(i=ans=0;i<lim;++i)ans+=i*(f[x][i]-f[x][i-1]);printf("%.10lf\n",ans);}
```

---

