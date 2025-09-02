# Koxia and Tree

## 题目描述

Imi has an undirected tree with $ n $ vertices where edges are numbered from $ 1 $ to $ n-1 $ . The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ . There are also $ k $ butterflies on the tree. Initially, the $ i $ -th butterfly is on vertex $ a_i $ . All values of $ a $ are pairwise distinct.

Koxia plays a game as follows:

- For $ i = 1, 2, \dots, n - 1 $ , Koxia set the direction of the $ i $ -th edge as $ u_i \rightarrow v_i $ or $ v_i \rightarrow u_i $ with equal probability.
- For $ i = 1, 2, \dots, n - 1 $ , if a butterfly is on the initial vertex of $ i $ -th edge and there is no butterfly on the terminal vertex, then this butterfly flies to the terminal vertex. Note that operations are sequentially in order of $ 1, 2, \dots, n - 1 $ instead of simultaneously.
- Koxia chooses two butterflies from the $ k $ butterflies with equal probability from all possible $ \frac{k(k-1)}{2} $ ways to select two butterflies, then she takes the distance $ ^\dagger $ between the two chosen vertices as her score.

Now, Koxia wants you to find the expected value of her score, modulo $ 998\,244\,353^\ddagger $ .

 $ ^\dagger $ The distance between two vertices on a tree is the number of edges on the (unique) simple path between them.

 $ ^\ddagger $ Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, the tree is shown below. Vertices containing butterflies are noted as bold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/b5933c313633856733c2f7b6fac2b7be83ed7851.png)There are only $ 2 $ butterflies so the choice of butterflies is fixed. Let's consider the following $ 4 $ cases:

- Edges are $ 1 \rightarrow 2 $ and $ 2 \rightarrow 3 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ doesn't move. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 1 \rightarrow 2 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ can't move to vertex $ 2 $ because it's occupied. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 2 \rightarrow 3 $ : butterflies on both vertex $ 1 $ and vertex $ 3 $ don't move. The distance between vertices $ 1 $ and $ 3 $ is $ 2 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ doesn't move, but butterfly on vertex $ 3 $ move to vertex $ 2 $ . The distance between vertices $ 1 $ and $ 2 $ is $ 1 $ .

Therefore, the expected value of Koxia's score is $ \frac {1+1+2+1} {4} = \frac {5} {4} $ , which is $ 748\,683\,266 $ after modulo $ 998\,244\,353 $ .

In the second test case, the tree is shown below. Vertices containing butterflies are noted as bold. The expected value of Koxia's score is $ \frac {11} {6} $ , which is $ 831\,870\,296 $ after modulo $ 998\,244\,353 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/c99c1f065a7b394b09acc90fcc6d66aa233890d9.png)

## 样例 #1

### 输入

```
3 2
1 3
1 2
2 3```

### 输出

```
748683266```

## 样例 #2

### 输入

```
5 3
3 4 5
1 2
1 3
2 4
2 5```

### 输出

```
831870296```

# 题解

## 作者：hejianxing (赞：7)

[题目(cf)](https://codeforces.com/problemset/problem/1770/E)

[题目(洛谷)](https://www.luogu.com.cn/problem/CF1770E)

# 题目大意

给定 $n$ 个节点的无根树，有 $k$ 个指定的节点上有蝴蝶。对每条边等概率地指定任意方向，按照边的编号顺序查找每条边，若边 $u\to v$ 满足 $u$ 有蝴蝶且 $v$ 没有蝴蝶，则蝴蝶从 $u$ 飞到 $v$. 求两只蝴蝶之间距离的期望值。

# 题解

首先要注意，求期望值的两只蝴蝶不是给定的。

显然，这个期望值的求法是每条边的贡献累加，求出所有蝴蝶两两距离和的期望值，再除以选择两只蝴蝶的方案数 $C_k^2=\frac {k(k-1)}{2}$.

先考虑一个简化的经典问题：蝴蝶不会飞的情况。

枚举每条边，若其左边有 $x$ 只蝴蝶，那么其右边有 $k-x$ 只蝴蝶，这条边将会成为 $x\times (k-x)$ 对蝴蝶之间的路径上的一条边。换一种说法，有 $x\times (k-x)$ 条路径会经过这条边。那么这条边会对总距离值贡献 $x\times (k-x)$. 也就是说简化情况下 $ans=\frac{\sum\limits_{(u,v)\in M}sum_u(k-sum_u)}{\frac{k(k-1)}{2}}$. $sum_i$ 表示 $i$ 的子树中有多少只蝴蝶。这个可以一次dfs $O(n)$ 求出。

回到原问题。如果我们知道每条边两边分别有多少蝴蝶，则贡献可求。

思考发现对于边 $(u,v)$，不管蝴蝶怎么飞，$sum$ 值的变化量最大为 $1$. 而 $sum$ 是否改变只取决于 $u$ 和 $v$ 上是否有蝴蝶。这就是说，我们需要求出 $u$ 和 $v$ 有蝴蝶的概率。设这个概率为 $p$.

考虑对于 $p_u$：

- 原来 $u$ 和 $v$ 上都有蝴蝶，则现在 $u$ 有蝴蝶的概率为 $p_u\times p_v$.
- 原来 $u$ 和 $v$ 上都没有蝴蝶，则现在 $u$ 有蝴蝶的概率为 $0$.
- 原来 $u$ 有蝴蝶，$v$ 没有，则现在 $u$ 有蝴蝶的概率为 $\frac {p_u(1-p_v)}{2}$. 因为有 $\frac 1 2$ 的概率边 $(u,v)$ 变成 $v\to u$，只有这样蝴蝶才不会从 $u$ 飞到 $v$.
- 原来 $u$ 没有蝴蝶，$v$ 有，则现在 $u$ 有蝴蝶的概率为 $\frac {(1-p_u)p_v}{2}$. 因为有 $\frac 1 2$ 的概率边 $(u,v)$ 变成 $v\to u$，只有这样蝴蝶才会从 $v$ 飞到 $u$.

对上述概率求和，得到 $u$ 有蝴蝶的概率为 $p_up_v+\frac {p_u(1-p_v)}{2}+\frac {(1-p_u)p_v}{2}=\frac {p_u+p_v}{2}$.

也就是转移时 $p_u=\frac {p_u+p_v}{2}$. 对于 $p_v$ 同理，得 $p_u=p_v=\frac {p_u+p_v}{2}$.

在修改概率前，我们就需要对边 $(u,v)$ 统计答案。

考虑如下情况：

- $u$ 和 $v$ 都有蝴蝶，贡献为 $p_u\cdot p_v\cdot sum_u\cdot (k-sum_u)$
- $u$ 和 $v$ 都没蝴蝶，贡献为 $(1-p_u)\cdot (1-p_v)\cdot sum_u\cdot (k-sum_u)$
- $u$ 有蝴蝶，$v$ 没有蝴蝶，此时有 $\frac 1 2$ 的概率蝴蝶从 $u$ 飞到 $v$，导致 $sum_u$ 少 $1$，贡献为 $p_u\cdot (1-p_v)\cdot \frac {sum_u\cdot (k-sum_u)+(sum_u-1)(k-sum_u+1)}{2}$
- $u$ 没有蝴蝶，$v$ 有蝴蝶，此时有 $\frac 1 2$ 的概率蝴蝶从 $v$ 飞到 $u$，导致 $sum_u$ 多 $1$，贡献为 $(1-p_u)\cdot p_v\cdot \frac {sum_u\cdot (k-sum_u)+(sum_u+1)(k-sum_u-1)}{2}$

对以上 $4$ 种情况求和就是边 $(u,v)$ 的贡献。

具体实现的时候可以对 $u$ 和 $v$ 限定父子关系，这样容易计算。

记得最后要除以 $\frac {k(k-1)}{2}$.

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 300005;
const LL mod = 998244353;
int n, k, cnt = 0, fir[N], nxt[N << 1], to[N << 1], fa[N];
LL ans = 0, p[N], s[N];
void ade(int u, int v) {
    cnt++, nxt[cnt] = fir[u], fir[u] = cnt, to[cnt] = v;
    cnt++, nxt[cnt] = fir[v], fir[v] = cnt, to[cnt] = u;
}
LL qpow(LL x, LL y) {
    LL sum = 1;
    while (y) {
        if (y & 1) sum = sum * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return sum;
}
void dfs(int r, int f) {
    fa[r] = f, s[r] = p[r];
    for (int i = fir[r]; i; i = nxt[i])
        if (to[i] != f)
            dfs(to[i], r), s[r] += s[to[i]];
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, x; i <= k; i++) scanf("%d", &x), p[x] = 1;
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), ade(u, v);
    dfs(1, 0);
    LL inv2 = qpow(2, mod - 2);
    for (int i = 1; i <= cnt; i += 2) {
        int u = to[i], v = to[i + 1];
        if (fa[v] != u) swap(u, v);//限定 u 为 v 的父亲
        ans = ((ans
        + p[u] * p[v] % mod * s[v] % mod * (k - s[v]) % mod
        + (1 - p[u]) * (1 - p[v]) % mod * s[v] % mod * (k - s[v]) % mod
        + (1 - p[u]) * p[v] % mod * (s[v] * (k - s[v]) % mod + (s[v] - 1) * (k - s[v] + 1) % mod) % mod * inv2 % mod
        + p[u] * (1 - p[v]) % mod * (s[v] * (k - s[v]) % mod + (s[v] + 1) * (k - s[v] - 1) % mod) % mod * inv2 % mod) % mod + mod) % mod;
        p[u] = p[v] = (p[u] + p[v]) * inv2 % mod;//概率转移
    }
    printf("%lld", (ans * qpow(1ll * k * (k - 1) / 2 % mod, mod - 2) % mod + mod) % mod);
    return 0;
}
```
# END


---

## 作者：CbrX (赞：4)

update on 2023/1/13：修改了一个错误，感谢评论区大佬指正。

赛时想法复杂了，其实正解真的非常简单。

注意到，每条边至多经过一个点，且这条边操作完之后两边的点数是不变的。

因为答案算的是距离，所以我们发现我们可以考虑每条边对于答案的贡献，也就是两边点数相乘。

为了计算点数，我们可以对其dfs算出每个点的子树点数 $s_u$。

想到这里就非常简单了。我们按照边 $1,2,\dots,n-1$ 的顺序算一下每条边端点有点的概率 $f_u$ 。

每次操作 $(u,v)$ （设 $u$ 是 $v$ 的父亲）就是 $f_u=f_v=\frac{f_u+f_v}{2}$ 。这是经过了这条边之后的概率。

在修改概率前，我们要计算这条边对于答案的贡献。

若两边都有点，则产生不了变化，贡献为 $f_u\times f_v\times (k-s_v)\times s_v$。

若两边都没有点一样产生不了变化，贡献为 $(1-f_u)\times(1-f_v)\times(k-s_v)\times s_v$。

若 $u$ 端有点，$v$ 端没有点，则有 $\frac{1}{2}$ 的概率 $u$ 端点数减少1，$v$ 端点数增加1，$\frac{1}{2}$ 的概率不变，贡献为 $f_u\times (1-f_v)\times\frac{(k-s_v)\times s_v+(k-s_v-1)\times(s_v+1)}{2}$。

若 $v$ 端有点，$u$ 段没有点，同理贡献为 $(1-f_u)\times f_v\times\frac{(k-s_v)\times s_v+(k-s_v+1)\times(s_v-1)}{2}$。

上面四个式子加起来就是这条边对于答案的贡献，累加即可。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#define N 300005
#define P 998244353
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> PII;
inline ll read(){
	ll xx=0,ff=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){xx=(xx<<1)+(xx<<3)+(ch^48);ch=getchar();}
	return xx*ff;
}
ll n,k,ans,tot=1,i2=499122177,head[N],nxt[N<<1],ver[N<<1],fa[N],sz[N],f[N];
void add(int u,int v){
	nxt[++tot]=head[u];ver[tot]=v;head[u]=tot;
}
ll qp(ll a,ll b=P-2){
	ll res=1;
	for(;b;b>>=1,a=a*a%P)if(b&1)res=res*a%P;
	return res;
}
void dfs(int u,int from){//求出子树大小
	fa[u]=from;sz[u]=f[u];
	for(int i=head[u];i;i=nxt[i])if(ver[i]!=from)dfs(ver[i],u),sz[u]+=sz[ver[i]];
}
int main(){
	n=read();k=read();
	for(int i=1;i<=k;i++)f[read()]=1;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,1);
	for(int i=2;i<=tot;i+=2){
		int u=ver[i^1],v=ver[i];
		if(fa[u]==v)swap(u,v);
		ans=((ans+f[u]*f[v]%P*sz[v]%P*(k-sz[v])%P+(1-f[u]+P)*(1-f[v]+P)%P*sz[v]%P*(k-sz[v])%P+(1-f[u]+P)*f[v]%P*(sz[v]*(k-sz[v])%P+(sz[v]-1)*(k-sz[v]+1)%P)%P*i2%P+f[u]*(1-f[v]+P)%P*(sz[v]*(k-sz[v])%P+(sz[v]+1)*(k-sz[v]-1)%P)%P*i2%P)%P+P)%P;//这一长串式子是当前边的贡献值
		f[u]=f[v]=(f[u]+f[v])*i2%P;//修改出现概率
	}
	printf("%lld\n",ans*qp(k*(k-1)/2%P)%P);//结果要除以k*(k-1)/2
	return 0;
}
```


---

## 作者：shinkuu (赞：2)

补题。记录一下这道比较典的 E。

首先最后一步随机选两个点可以直接变成 $\dfrac{\sum\limits_{i\in a}\sum\limits_{j\in a\land i<j}dis(i,j)}{C_k^2}$，只用算这个式子的期望。

然后考虑如果点固定怎么计算上面的式子。这是个很常见的 trick：枚举每条边算贡献，即记录一个点 $v$ 的子树内有多少个有标记的点 $c_v$，这个点连向父亲的边的贡献即为 $c_v\times(k-c_v)$。

考虑推广到有转移的情况。这里有一个关键的性质：$\Delta c_v$ 最大为 1，因为不在这条边上的点对 $c_v$ 明显没有贡献，而在这条边上的点最多只会产生 $1$ 的贡献。所以分 $u,v$ 有没有蝴蝶的情况讨论。设 $p_u$ 为 $u$ 点有蝴蝶的概率。则有：

- 都有标记：$p_u\times p_v\times c_v\times(k-c_v)$。即无论如何都不会对该边产生贡献。

- 都没标记：$(1-p_u)\times(1-p_v)\times c_v\times(k-c_v)$。同上。

- $u$ 有标记：$p_u\times (1-p_v)\times \dfrac{c_v\times(k-c_v)+(c_v+1)\times(k-c_v-1)}{2}$。即有 $0.5$ 的概率标记会从 $u$ 转移到 $v$。

- $v$ 有标记：$p_v\times (1-p_u)\times \dfrac{c_v\times(k-c_v)+(c_v-1)\times(k-c_v+1)}{2}$。同上。

然后还要处理标记转移后 $u,v$ 有标记的概率。也可以用类似上面的分类2方法计算。最后拆开化简得到 $p_u=p_v=\dfrac{p_u+p_v}{2}$。

枚举每条边转移即可。

code：

```cpp
int n,m,c[N],p[N],dep[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)
			continue;
		dfs(v,u);
		c[u]+=c[v];
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		c[x]=p[x]=1;
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	const int inv=qpow(2,mod-2);
	int ans=0;
	for(int i=1;i<=tot;i+=2){
		int u=e[i+1].to,v=e[i].to;
		if(dep[u]>dep[v])
			swap(u,v);
		ans=(ans+1ll*(1ll*p[u]*p[v]%mod+1ll*(1-p[u]+mod)*(1-p[v]+mod)%mod)*c[v]%mod*(m-c[v])%mod//这里用了下分配律，没有影响
			+1ll*p[u]*(1-p[v]+mod)%mod*(1ll*c[v]*(m-c[v])%mod+1ll*(c[v]+1)*(m-c[v]-1)%mod)%mod*inv%mod
			+1ll*(1-p[u]+mod)*p[v]%mod*(1ll*c[v]*(m-c[v])%mod+1ll*(c[v]-1)*(m-c[v]+1)%mod)%mod*inv%mod)%mod;
		p[u]=p[v]=1ll*(p[u]+p[v])*inv%mod;//转移概率
	}
	printf("%lld\n",1ll*ans*qpow(1ll*m*(m-1)/2%mod,mod-2)%mod);
}
```

---

## 作者：周子衡 (赞：2)

注意到统计树上若干点两两距离和有一种这样的方法：对每条边，计算这条边两端各有多少点，并把两侧点数的乘积累加到答案中。（这个做法的本质其实就是对每条边统计有多少路径经过该边。）而我们发现：对每条边来说，整个操作过程中至多只会有一只蝴蝶经过该边。也就是说，如果一开始该边的某一侧蝴蝶数为 $x$，那么全部操作结束后该侧的蝴蝶数只能是 $x-1,x,x+1$ 之一。我们只需要统计这三种情形分别的发生概率即可。

我们考虑动态维护：在每个时刻，树上每个节点上有蝴蝶的概率（下记为 $p_u$）。顺次扫描每条边，对一条边 $(u,v)$，注意到：

- 有 $\dfrac{1}{2}f_u(1-f_v)$ 的概率，$u$ 上的蝴蝶飞到 $v$ 的空位上；
- 有 $\dfrac{1}{2}f_v(1-f_u)$ 的概率，$v$ 上的蝴蝶飞到 $u$ 的空位上；
- $f'_u=f'_v=\dfrac{f_u+f_v}{2}$。

通过以上观察即可维护待求信息。时间复杂度 $O(n)$。

---

## 作者：蒟蒻君HJT (赞：1)

### Div1.5 不会 E ，警钟长鸣。

## 转化：

考虑不移动的情况，计算每条边的贡献，

$$preans = \frac{2}{k(k-1)} \sum_{x}(k-siz_x)siz_x$$

$siz_x$ 表示 $x$ 子树内的蝴蝶个数。

性质：每条边上最多只会有一只蝴蝶经过，所以每颗子树大小的可能性至多 $3$ 种；又蝴蝶的相对位置关系不会发生变化。

那么不妨直接计算每条边上的移动在 $preans$ 基础上的贡献。为此我们只需要求出每条边上发生某种方向移动的分别的概率就可以了。

## 计算：

设 $f_x$ 表示在当前时刻点 $x$ 上有蝴蝶的概率，其初始化是简单的。按顺序遍历每条边 $(u,v)$ 显然只有 $f_u$ 和 $f_v$ 可能发生变化。可以列出式子：

$$f_u=\frac{1}{2}f_uf_v+\frac{1}{2}(f_v(1-f_u)+f_u)=\frac{1}{2}(f_u+f_v)$$

$$f_v=\frac{1}{2}f_vf_u+\frac{1}{2}(f_u(1-f_v)+f_v)=\frac{1}{2}(f_v+f_u)$$

每次处理一条边对 $f_x$ 的贡献之前，用前面算好的 $f_x$ 计算边上发生某种方向移动的分别的概率，再乘上两边点的个数就做完了。细节可以看看 code 。之后再更新 $f_u$ 和 $f_v$ 。

为了方便起见，我们先忽略 $\frac{2}{k(k-1)}$ ，即始终求的是所有蝴蝶两两距离之和，最后再乘以 $\frac{2}{k(k-1)}$ 。

## 代码：

```cpp
#include <bits/stdc++.h>
const int mod = 998244353, i2 = 499122177;
inline int mul(int x, int y){
	return (int)(1ll * x * y % (1ll * mod));
}
inline int add(int x, int y){
	return x + y >= mod ? x + y - mod : x + y;
}
inline int minus(int x, int y){
	return x < y ? x - y + mod : x - y; 
}
inline int Qpow(int x, int y){
	int r = 1;
	while(y){
		if(y & 1) r = mul(r, x);
		x = mul(x, x);
		y >>= 1;
	}
	return r;
}
int n, a[300005], k, f[300005], B, fa[300005];
int u[300005], v[300005], siz[300005];
int g[300005], dep[300005], m[300005], ans = 0;
std::vector <int> ver[300005];
void dfs(int x){
	siz[x] = a[x];
	for(int i = 0; i < ver[x].size(); ++i){
		int y = ver[x][i];
		if(y == fa[x]) continue;
		dep[y] = dep[x] + 1;
		fa[y] = x;
		dfs(y);
		siz[x] += siz[y];
	}
	ans = add(ans, mul(siz[x], k - siz[x]));
	return ;
}
void solve(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; ++i){
		int x;
		scanf("%d", &x);
		a[x] = 1;
	}
	for(int i = 1; i <= n - 1; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		u[i] = x; v[i] = y;
		ver[x].push_back(y);
		ver[y].push_back(x);
	}
	dfs(1);
	for(int i = 1; i <= n; ++i) f[i] = a[i];
	for(int i = 1; i <= n - 1; ++i){
		if(fa[u[i]] == v[i]) std::swap(u[i], v[i]);
		int a = f[u[i]], b = f[v[i]];
		int p1 = mul(mul(i2, f[u[i]]), minus(1, f[v[i]]));
		int p2 = mul(mul(i2, f[v[i]]), minus(1, f[u[i]]));
		ans = add(ans, mul(p1, k - siz[v[i]] - 1));
		ans = minus(ans, mul(p1, siz[v[i]]));
		ans = add(ans, mul(p2, siz[v[i]] - 1));
		ans = minus(ans, mul(p2, k - siz[v[i]]));
		f[u[i]] = add(a, b);
		f[u[i]] = mul(f[u[i]], i2);
		f[v[i]] = f[u[i]];
	}
	B = mul(k, k - 1);
	B = mul(B, i2);
	ans = mul(ans, Qpow(B, mod - 2));
	printf("%d\n", ans);
	return ;
}
signed main(){
	int T = 1;
	while(T--) solve();
	return 0;
}
```


---

## 作者：2022dyx (赞：0)

先考虑答案的转化。随机两个关键点的期望距离可以乘上一个组合数变为任意两个关键点的距离和，而后者可以拆贡献到每条边上，对于边 $(x, y)$，不妨设 $x$ 为 $y$ 的父亲，若使 $siz_i$ 表示 $i$ 子树内关键点的个数。这条边被经过的次数就是 $siz_y(k-siz_y)$，设答案为 $f_{siz_y}$，这也就是它对答案的贡献。

在考虑关键点的移动。因为题目中给出的移动顺序，因此每条边只会被关键点经过其移动一次。设子树内关键点个数减少/增加/不变的概率分别为 $p_1,p_2,p_3$，则一条边的贡献就是 $p_1f_{siz_{y}-1}+p_2f_{siz_{y}+1}+p_3f_{siz_{y}}$，而总答案就是所有边答案之和。

那怎么求 $p$ 呢？我们可以在移动的过程中维护每个点是关键点的概率，计算即可得到 $p$ 的具体数值。

细节详见代码。
```
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
using namespace std;
constexpr int N = 3e5 + 5;
constexpr int mod = 998244353;
constexpr int inv = 499122177;
int n, k, p[N], ans, siz[N], dep[N];
vector <int> e[N];
pair <int, int> E[N];
int pw(int x, int y) { return !y ? 1 : (y & 1 ? x : 1) * pw(x * x % mod, y >> 1) % mod; }
void dfs(int x, int z) {
    for (int y : e[x]) if (y != z) {
        dep[y] = dep[x] + 1;
        dfs(y, x);
        siz[x] += siz[y];
    }
}
signed main() {
    cin.tie(0) -> sync_with_stdio(false); 
    cin >> n >> k;
    for (int i = 1, x; i <= k; ++i) cin >> x, p[x] = siz[x] = 1;   
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y, E[i] = {x, y};
        e[x].pb(y), e[y].pb(x);
    }
    dfs(1, 0);
    for (int i = 1; i < n; ++i) {
        int x = E[i].first, y = E[i].second;
        if (dep[x] > dep[y]) swap(x, y);
        int p1 = p[x] * (1 - p[y] + mod) % mod * inv % mod, p2 = (1 - p[x] + mod) * p[y] % mod * inv % mod, p3 = (1 - p1 - p2 + mod + mod) % mod;
        ans = (ans + p1 * (siz[y] + 1) % mod * (k - siz[y] - 1)) % mod;
        ans = (ans + p2 * (siz[y] - 1) % mod * (k - siz[y] + 1)) % mod;
        ans = (ans + p3 * siz[y] % mod * (k - siz[y])) % mod;
        p[x] = p[y] = (p[x] + p[y]) * inv % mod;
    }
    cout << ans * pw(k * (k - 1) / 2 % mod, mod - 2) % mod;
}
```

---

## 作者：cosf (赞：0)

## [CF1770E](https://www.luogu.com.cn/problem/CF1770E)

题目要求的距离期望，也就是所有蝴蝶两两距离的和除以 $\binom{k}{2}$。我们考虑如何求两两距离和。

对于每一条边，我们算出它左右各有多少蝴蝶（假设数量为 $x$ 和 $k - x$），那么就会有 $x(k-x)$ 种选蝴蝶的方式经过它。那么，把每一条边的 $x(k-x)$ 都加起来就是距离和了。（你想写虚树就去 [P4103](https://www.luogu.com.cn/problem/P4103)）

不过这是静态的，和题目所求差距还是有的。

根据题意可知，每条边最多只有一只蝴蝶从它的上面经过，也就是说原始的 $x$ 和实际的 $x$ 的差不会大于 $1$。令实际的 $x$ 为 $x'$，则该边对期望的贡献是 

$$
E = \sum_{i=-1}^1(x+i)(n-x-i) \cdot P(x' = x + i)
$$

这和 $E(x')\cdot(n-E(x'))$ 是不一样的。

为了计算蝴蝶通过情况的概率，我们可以维护点 $i$ 有蝴蝶的概率 $p_i$。那么对于一条边 $<u, v>$，有蝴蝶从 $u\to v$ 的概率为 $\frac{1}{2}p_u(1-p_v)$（$u$ 有蝴蝶且 $v$ 没有），从 $v \to u$ 的概率为 $\frac{1}{2}p_v(1-p_u)$，剩下的都是没有蝴蝶经过的概率。

处理完一条边后，$p_u$ 和 $p_v$ 都会变成 $\frac{p_u + p_v}{2}$。

我们顺序枚举第 $1$ 到 $n-1$ 条边，把答案加起来就可以了。

最后还要除以 $\binom{k}{2}$。由于定向时还有一个 $\frac{1}{2}$ 的系数，所以可以将其提出，最后只用除以 $k(k-1)$。

## 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 300005
#define MOD 998244353ll
#define I1 998244354ll
#define I2 499122177ll

using ll = long long;
using pii = pair<int, int>;

int siz[MAXN];
ll p[MAXN];

int fa[MAXN];

vector<int> e[MAXN];
vector<pii> ed;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

int n, k;

void dfs(int u, int f)
{
    fa[u] = f;
    siz[u] = p[u];
    for (int v : e[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u);
        siz[u] += siz[v];
    }
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
    {
        int a;
        cin >> a;
        p[a]++;
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        ed.push_back({u, v});
    }
    dfs(1, 1);
    ll res = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int u = ed[i].first, v = ed[i].second;
        if (fa[u] != v) // 只有一边的点的 siz 才是文中所谓的 x
        {
            swap(u, v);
        }
        // u to v
        ll pb = p[u] * (I1 - p[v]) % MOD;
        res = (res + pb * (siz[u] - 1) % MOD * (k - siz[u] + 1) % MOD) % MOD;
        res = (res + (I1 - pb) * siz[u] % MOD * (k - siz[u]) % MOD) % MOD;
        // v to u
        pb = (I1 - p[u]) * p[v] % MOD;
        res = (res + pb * (siz[u] + 1) % MOD * (k - siz[u] - 1) % MOD) % MOD;
        res = (res + (I1 - pb) * siz[u] % MOD * (k - siz[u]) % MOD) % MOD;
        p[u] = p[v] = (p[u] + p[v]) % MOD * I2 % MOD;
    }
    res = res * pow(k, MOD - 2, MOD) % MOD;
    res = res * pow(k - 1, MOD - 2, MOD) % MOD;
    cout << res << endl;
    return 0;
}

```


---

## 作者：TTpandaS (赞：0)

考虑三操作。

对于每条边计算其贡献，边 $x \to y$ 的贡献即为 $Siz_y\times(k-Siz_x)$，其中 $Siz_y$ 表示以 $y$ 为根节点的子树中的标记个数。

考虑期望，即在 $k$ 个点中任取两点，有 $\large k\choose 2$ 种选择情况，所有情况的贡献总和可以用 dfs $O(n)$ 求出。

考虑操作二。

仍然对于每条边计算贡献，由于每条边只会被节点经过一次，所以 $Siz_x$ 最多只会减少 $1$ 或增加 $1$。

考虑 $Siz_x$ 改变的概率。

$Siz_x$ 增加 $1$ 的情况只可能是刚才 $x$ 上有标记，$y$ 上没有标记，概率为 $\dfrac{p_x \times (1-p_y)}{2}$，其中 $p_x$ 表示 $x$ 节点有标记的概率。$Siz_x$ 减少 $1$ 的情况类似，概率为 $\dfrac{p_y \times (1-p_x)}{2}$。

当 $Siz_x$ 增加 $1$ 时，该边的贡献变为 $(Siz_y+1)\times(k-Siz_x-1)$。$Siz_x$ 减少 $1$ 时类似，该边的贡献变为 $(Siz_y-1)\times(k-Siz_x+1)$。

最后考虑在一条边更新后，$p_x$ 和 $p_y$ 的变化情况。

考虑操作一。

$p_x$ 有 $\dfrac{1}{2}$ 的概率转移到 $p_y$，$p_y$ 类似，所以 $p_x=p_y=\dfrac{p_x+p_y}{2}$。

核心代码：

```cpp
ans=(ans+siz[y[i]]*(k-siz[y[i]])%mod+p[x[i]]*(1-p[y[i]]+mod)%mod*((siz[y[i]]+1)%mod*(k-siz[y[i]]-1)%mod*qpow(2,mod-2)%mod-siz[y[i]]%mod*(k-siz[y[i]])%mod*qpow(2,mod-2)%mod+mod)%mod+p[y[i]]*(1-p[x[i]]+mod)%mod*((siz[y[i]]-1)%mod*(k-siz[y[i]]+1)%mod*qpow(2,mod-2)%mod-siz[y[i]]%mod*(k-siz[y[i]])%mod*qpow(2,mod-2)%mod+mod)%mod)%mod;
p[x[i]]=p[y[i]]=(p[x[i]]+p[y[i]])%mod*qpow(2,mod-2)%mod;
```
式子有点长，调试可能有点麻烦，建议分布写。

---

## 作者：E1_de5truct0r (赞：0)

## Part 1 做题前

首先，这道题的第三步是诈骗，直接算距离和再除以组合数即可。

其次，这道题用到一个 trick：统计树上点对距离可以对每条边算贡献，即 $\sum\limits_{i=1}^k\sum\limits_{j=1}^kdis(a_i,a_j)=\sum\limits_{(u,v) \in E,u=fa_v}(k-cnt_v)cnt_v$，其中 $a$ 为标记点数组，$cnt_v$ 表示 $v$ 子树内的标记点数量。


## Part 2 做题思路

这道题的关键：因为题目所给的是一棵树，所以每条边都是这棵树的割边，又因为一个边只会至多产生一次标记点转移，所以每条边两侧的标记点数量变化量是小于等于 $1$ 的，即 $\forall i \in E,\Delta cnt_i \leq 1$。

而且一棵树保证了不会出现一些环路等棘手情况，可以直接暴力转移。

### 边的定向

然后我们考虑一个边的定向。记 $p_x$ 为点 $x$ 成为标记点的概率，那么对于一条边 $(u,v)$：

假设其定向为 $u \rightarrow v$。

- $u$ 和 $v$ 都有：$p_u=p_up_v$。
   
- $u$ 没有，$v$ 有：$p_u=\dfrac{(1-p_u)p_v}{2}$。
  
- $u$ 有，$v$ 没有：$p_u=\dfrac{p_u(1-p_v)}{2}$。
    
- $u,v$ 都没有：$0$。
    
相加，得到 $p_u=\dfrac{p_u+p_v}{2}$。同理得到 $p_v$。

另一侧同理。

### 边的贡献

然后考虑边 $(u,v)$ 的答案。

- $u$ 和 $v$ 都有：$p_u\cdot p_v\cdot c_u \cdot (k-c_u)$

- $u$ 和 $v$ 都没有：$(1-p_u)\cdot (1-p_v)\cdot c_u \cdot (k-c_u)$。

- $u$ 有 $v$ 没有：此时有 $\dfrac{1}{2}$ 的概率变更。$\dfrac{p_u\cdot (1-p_v)\cdot c_u\cdot (k-c_u)}{2}+\dfrac{p_u \cdot (1-p_v) \cdot (c_u-1)(k-c_u+1)}{2}$。

- $u$ 没有 $v$ 有：此时有 $\dfrac{1}{2}$ 的概率变更。$\dfrac{(1-p_u) \cdot p_v \cdot c_u \cdot (k-c_u)}{2}+\dfrac{(1-p_u) \cdot p_v \cdot (c_u+1) \cdot (k-c_u-1)}{2}$。

相加即为新的贡献。

我们可以在这之前通过定根、dfs，来钦定 $u,v$ 的父子关系，令 $u$ 恒为 $v$ 的父亲，就可以更方便的转移了。每次转移就加上现在的边的贡献即可。

复杂度 $O(n)$。

---

## 作者：小木虫 (赞：0)

### Preface  
这是蒟蒻自己做的第一道期望相关题目，但是由于是 dp 所以做出来了。  
### Problem  
给你一棵树，树上有若干个点是有蝴蝶的，然后我们会根据每条边的编号依次做以下操作：  
**等概率地对这条边定向，即二分之一 $\space a\rightarrow b$，二分之一反之。**  
然后，若这条边定向之后的起始点有蝴蝶而终点没有，我们就将这只蝴蝶放到这条边的终点。  
在所有操作结束之后，随机选一个蝴蝶对，问选出蝴蝶对的距离期望。  

原题链接：https://codeforces.com/contest/1770/problem/E  

### Solution  
首先，有一个有意思的性质：由于这是一棵树，所以当一条边没有被操作的时候事实上这条边两边的点数都是确定的，这个很重要。  

一旦我们知道这个性质，我们即可推出这条边正反操作时对全局距离的影响。  
（全局距离即 $\sum_{i=1}^{i\leq k} \sum_{j=i+1}^{j\leq k} dis(a_i,a_j)$ ）

然后我们可以很简单的发现，我们只需要求出全局距离的期望 $res$，$res\times \frac{2}{k(k-1)}$ 就是答案。  

然后我们现在怎么办呢？  

显然对于一条边，我们需要知道其两边的点上面有蝴蝶的概率才好做下一步操作。  

于是我们设 $f_i$ 为点 $i$ 上有蝴蝶的概率。  

然后我们就很容易发现当我们操作边 $i$ 的时候，$res$ 会这么变化（$s_{i,0/1}$ 分别为正反操作对于全局距离的变化量）：  
$res\leftarrow res+\frac{1}{2}\times(f_{u_i}\times (1-f_{v_i}))\times s_{i,0}$  
$res\leftarrow res+\frac{1}{2}\times(f_{v_i}\times (1-f_{u_i}))\times s_{i,1}$  

然后是 $f$ 的转移：  
$v1\leftarrow \frac{1}{2} \times (f_{u_i}\times (1-f_{v_i}))$  
$v2\leftarrow \frac{1}{2} \times (f_{v_i}\times (1-f_{u_i}))$  
$f_{u_i}\leftarrow f_{u_i}+v2-v1$  
$f_{v_i}\leftarrow f_{v_i}+v1-v2$  

做完这个转移，这个题就做完了。  
code：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
const int mod=998244353;
const int inv=(mod+1)/2;
int n,k,a[N],u[N],v[N],res,sz[N],val[N],f[N],s[N][2];
vector <int> edge[N];vector <int> id[N];bool tag[N];
int h[65];
int fast_pow(int x,int y){
	h[0]=x;for(int i=1;i<=30;i++){
		h[i]=h[i-1]*h[i-1];h[i]%=mod;
	}int res=1;
	for(int i=30;i>=0;i--){
		if(y>=(1<<i)){
			y-=(1<<i);
			res*=h[i];res%=mod;
		}
	}return res;
}
void dfs(int u,int fa){
	sz[u]+=tag[u];
	for(int i=0;i<edge[u].size();i++){
		int v=edge[u][i];
		if(v==fa)continue;
		dfs(v,u);sz[u]+=sz[v];
		val[u]+=val[v]+sz[v];val[u]%=mod;
	}//cout<<u<<" "<<val[u]<<endl;
}
void calc(int x,int fa,int p,int l){
	p%=mod;if(tag[x]){
		//cout<<x<<" "<<val[x]<<" "<<l<<endl;
		res+=val[x]+l,res%=mod;
	}
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];int I=id[x][i];
		if(v==fa)continue;
		if(x==u[I]){
			s[I][0]=p+sz[x]-sz[v]-1-sz[v];
			s[I][1]=sz[v]-1-(sz[x]-sz[v])-p;
		}else{
			s[I][0]=sz[v]-1-(sz[x]-sz[v])-p;
			s[I][1]=p+sz[x]-sz[v]-1-sz[v];
		}
		calc(v,x,p+(sz[x]-sz[v]),l+(k-sz[v])+(val[x]-val[v]-sz[v]));
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=k;i++)cin>>a[i],tag[a[i]]=1,f[a[i]]=1;
	for(int i=1;i<n;i++)cin>>u[i]>>v[i];
	for(int i=1;i<n;i++){
		edge[u[i]].push_back(v[i]);
		id[u[i]].push_back(i);
		edge[v[i]].push_back(u[i]);
		id[v[i]].push_back(i);
	}
	dfs(1,0);calc(1,0,0,0);res*=inv;res%=mod;//cout<<res<<endl;
	for(int i=1;i<n;i++){
		res+=(inv*f[u[i]]%mod*(1-f[v[i]]+mod)%mod*s[i][0])%mod,res=(res+mod)%mod;
		res+=(inv*f[v[i]]%mod*(1-f[u[i]]+mod)%mod*s[i][1])%mod,res=(res+mod)%mod;
		int v1=(f[u[i]]*((1-f[v[i]]+mod)%mod)%mod*inv%mod);
		int v2=(f[v[i]]*((1-f[u[i]]+mod)%mod)%mod*inv%mod);
		f[v[i]]+=v1,f[v[i]]%=mod;f[u[i]]-=v1,f[u[i]]=(f[u[i]]+mod)%mod;
		f[u[i]]+=v2,f[u[i]]%=mod;f[v[i]]-=v2,f[v[i]]=(f[v[i]]+mod)%mod;
		//cout<<s[i][0]<<" "<<s[i][1]<<endl;
		//for(int j=1;j<=n;j++)cout<<f[j]<<" ";cout<<endl;
	}res*=fast_pow(k,mod-2);res%=mod;
	res*=fast_pow(k-1,mod-2);res%=mod;
	res*=2;res%=mod;
	cout<<res;
}
```


---

## 作者：rui_er (赞：0)

先对不好处理的部分做一个转化：任取两个蝴蝶并计算它们之间的距离，等价于所有蝴蝶两两距离的平均值。于是只需要求所有蝴蝶两两距离的和。

首先令每条边都按输入顺序定向，DFS 预处理出每条边两侧蝴蝶的数量，容易计算出初始局面下的答案。

然后按照输入顺序枚举每条边，也就是第二步的按顺序操作。我们维护 $dp$ 数组表示此时每个点有蝴蝶的概率，然后分别考虑 $u_i\to v_i$ 和 $v_i\to u_i$ 两种可能的蝴蝶移动，通过数学推导可以计算出此时每条边对答案的贡献以及新的概率。

式子不难推，但是比较长不方便列出，详见代码。

```cpp
// Problem: E. Koxia and Tree
// Contest: Codeforces - Good Bye 2022: 2023 is NEAR
// URL: https://codeforces.com/contest/1770/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 3e5+5, mod = 998244353, inv2 = 499122177;

ll n, k, a[N], U[N], V[N], vis[N], dp[N], cntV[N], cntE[N];
vector<tuple<ll, ll>> e[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
ll qpow(ll x, ll y) {
	ll ans = 1;
	for(; y; y >>= 1, x = x * x % mod) if(y & 1) ans = ans * x % mod;
	return ans;
}
ll inv(ll x) {return qpow(x, mod-2);}
void dfs(ll u, ll f) {
	cntV[u] = vis[u];
	for(auto i : e[u]) {
		ll v = get<0>(i), id = get<1>(i);
		if(v == f) continue;
		dfs(v, u);
		cntV[u] += cntV[v];
		cntE[id] = v == U[id] ? cntV[v] : k - cntV[v];
	}
}

int main() {
	scanf("%lld%lld", &n, &k);
	rep(i, 1, k) scanf("%lld", &a[i]);
	rep(i, 1, n-1) {
		scanf("%lld%lld", &U[i], &V[i]);
		e[U[i]].emplace_back(V[i], i);
		e[V[i]].emplace_back(U[i], i);
	}
	rep(i, 1, k) vis[a[i]] = 1;
	dfs(1, 0);
	ll ans = 0;
	rep(i, 1, n-1) ans = (ans + cntE[i] * (k - cntE[i]) % mod) % mod;
	rep(i, 1, n) dp[i] = vis[i];
	rep(i, 1, n-1) {
		ans = (ans + dp[U[i]] * (1 + mod - dp[V[i]]) % mod * (((cntE[i] - 1) - (k - cntE[i]) + 3 * mod) % mod) % mod * inv2 % mod) % mod;
		ans = (ans + dp[V[i]] * (1 + mod - dp[U[i]]) % mod * (((k - cntE[i] - 1) - (cntE[i]) + 3 * mod) % mod) % mod * inv2 % mod) % mod;
		ll x = dp[U[i]], y = dp[V[i]];
		dp[U[i]] = (x * inv2 % mod + x * y % mod * inv2 % mod + y * (1 + mod - x) % mod * inv2 % mod) % mod;
		dp[V[i]] = (y * inv2 % mod + x * y % mod * inv2 % mod + x * (1 + mod - y) % mod * inv2 % mod) % mod;
	}
	ans = ans * inv(k*(k-1)/2%mod) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

