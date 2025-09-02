# [AGC008E] Next or Nextnext

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_e

長さ $ N $ の数列 $ a $ が与えられます。 $ 1 $ から $ N $ までの整数の順列 $ p $ であって、次の条件を満たすものは何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

- 各 $ 1\ <\ =\ i\ <\ =\ N $ について、$ p_i\ =\ a_i $ または $ p_{p_i}\ =\ a_i $ の少なくとも一方が成り立つ。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10^5 $
- $ a_i $ は整数である。
- $ 1\ <\ =\ a_i\ <\ =\ N $

### Sample Explanation 1

次の $ 4 $ 通りです。 - $ (1,\ 2,\ 3) $ - $ (1,\ 3,\ 2) $ - $ (3,\ 2,\ 1) $ - $ (2,\ 1,\ 3) $ たとえば $ (1,\ 3,\ 2) $ は、$ p_1\ =\ 1 $, $ p_{p_2}\ =\ 2 $, $ p_{p_3}\ =\ 3 $ となっています。

### Sample Explanation 2

次の $ 1 $ 通りです。 - $ (2,\ 1) $

### Sample Explanation 3

次の $ 2 $ 通りです。 - $ (2,\ 3,\ 1) $ - $ (3,\ 1,\ 2) $

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
3
2 1 1```

### 输出

```
2```

## 样例 #4

### 输入

```
3
1 1 1```

### 输出

```
0```

## 样例 #5

### 输入

```
13
2 1 4 3 6 7 5 9 10 8 8 9 11```

### 输出

```
6```

# 题解

## 作者：litble (赞：12)

我尽力修复了，但图片还是老是挂，可以戳一下博客链接看图QAQ......

[戳我＝￣ω￣＝](https://blog.csdn.net/litble/article/details/83118814)

litble不生产题解，litble只是官方题解的翻译工，以下图都是从官方题解搬过来的，果然官方题解的图画的就是好~

我们考虑最终的那个排列$p$，建一个图，将点$i$向点$p_i$连边。因为这是个排列，所以每个点出度入度都为$1$，所以一定由若干环构成。

![环](https://img-blog.csdn.net/20181017214320502?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

考虑其中的一个环，我们擦掉它的所有边，然后将$i$向$a_i$连边，可以知道$a_i$是它前面一个节点或者前面的前面一个节点。

有四种情况。

1. 所有$i$的$a_i$都是它的前面一个节点，则环保持不变。

2. 所有$i$的$a_i$都是它前面的前面的节点，且环为奇环，则环变成同构的另一个环

3. 所有$i$的$a_i$都是它前面的前面的点，且原环为偶环，则这个环会被拆成两个相同大小的环。

4. 有的是前面一个节点，有的又是前面的前面，则变成了一棵由一个环和若干指向环的链构成的基环内向树。

![情况1](https://img-blog.csdn.net/2018101721433430?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

![情况2](https://img-blog.csdn.net/20181017214442629?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

![情况3](https://img-blog.csdn.net/20181017214623958?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

![情况4](https://img-blog.csdn.net/20181017214732598?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

行吧，现在我们手头上只有由$a$构成的那张图，没有由$p$构成的那张图，所以我们就要反过来考虑了。

首先我们找到所有的环，先记录每个大小的环有多少个，那么每种大小可以单独考虑，DP一下，决策就是这种大小的第$k$个环是和前面的环合并呢，还是单独组成$p$图中的环。最后用乘法原理乘起来这些东西。

对于一棵基环内向树，我们考虑相邻两个“脚”（即挂在环上的链），将“脚”往环里面塞，并且要求还是一条边与它指着的节点中间最多只能插一个节点。大致如下图：

![基环树](https://img-blog.csdn.net/20181017215131588?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

这个脚可以塞到树里的位置，就是到下一个脚之间的边，假设这些边有$l_2$条，这个脚的长度为$l_1$，那么：

若$l_2<l_1$，有0种方案。

若$l_2=l_1$，有1种方案。

若$l_2>l_1$，有2种方案。

也可以用乘法原理搞，就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
const int mod=1e9+7,N=100005;
int n,ans;
int a[N],du[N],cir[N],vis[N],footL[N],sum[N],f[N];
int qm(int x) {return x>=mod?x-mod:x;}
void workcir(int x) {
	int now=0,fr=0,ed=0,frL=0;
	//fr:第一个有脚的位置，ed:上一个找到的有脚的位置
	//frL:第一个脚的长度，now:当前节点是从x开始走环走到的第几个点
	while(cir[x]) {
		++now,cir[x]=0;
		if(footL[x]) {
			if(!fr) ed=fr=now,frL=footL[x];
			else {//塞脚
				int kl=(footL[x]<now-ed)+(footL[x]<=now-ed);
				ans=1LL*ans*kl%mod,ed=now;
			}
		}
		x=a[x];
	}
	if(!fr) ++sum[now];//是简单环
	else {//考虑第一个脚
		int kl=(frL<now-ed+fr)+(frL<=now-ed+fr);
		ans=1LL*ans*kl%mod;
	}
}
void work() {
	for(RI i=1;i<=n;++i) {
		if(du[i]) continue;
		int x=i,len=0;while(!cir[x]) x=a[x],++len;
		footL[x]=len;//算挂在每个点上的脚长
	}
	ans=1;
	for(RI i=1;i<=n;++i) if(cir[i]) workcir(i);
	for(RI i=1;i<=n;++i) {//对每一种长度的简单环做DP
		if(!sum[i]) continue;
		f[0]=1;
		for(RI j=1;j<=sum[i];++j) {
			if(i>1&&(i&1)) f[j]=qm(f[j-1]+f[j-1]);//情况1,2
			else f[j]=f[j-1];//情况1
			if(j>1) f[j]=qm(f[j]+1LL*f[j-2]*(j-1)%mod*i%mod);//情况3
		}
		ans=1LL*ans*f[sum[i]]%mod;
	}
}
int main()
{
	n=read();
	for(RI i=1;i<=n;++i) a[i]=read(),++du[a[i]];
	for(RI i=1;i<=n;++i) {
		if(vis[i]) continue;
		int x=i;while(!vis[x]) vis[x]=i,x=a[x];
		if(vis[x]!=i) continue;//说明i在一个脚上
		while(!cir[x]) cir[x]=1,x=a[x];//给环打上是环标记
	}
	for(RI i=1;i<=n;++i)//判无解
		if((cir[i]&&du[i]>2)||(!cir[i]&&du[i]>1)) {puts("0");return 0;}
	work();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：AThousandSuns (赞：6)

在我的博客园看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/11737606.html)

神仙题。

排列计数，一种常见的做法是 $i$ 向 $p_i$ 连边。

然而这里这个就逼迫我们只能从 $i$ 向 $a_i$ 连边。

不过没关系，考虑从 $i$ 向 $p_i$ 连边的图（为方便叫 $G_1$）和从 $i$ 向 $a_i$ 连边的图（为方便叫 $G_2$）的区别。

首先 $G_1$ 中每个点入度和出度都是 $1$，**所以是一堆环构成的。**

考虑一个环：（下面建议画图，懒的建议看 litble 学姐的[博客](https://blog.csdn.net/litble/article/details/83118814)，~~自己不敢直接把图拿过来~~）
- 如果上面所有点都满足 $p_i=a_i$，那么这个环在 $G_2$ 中也出现了，长得一样。
- 如果上面所有点都满足 $p_{p_i}=a_i$，且这个环长度为**奇数**，那么有一个相同长度的环在 $G_2$ 中出现了，但是长得不一样。
- 如果上面所有点都满足 $p_{p_i}=a_i$，且这个环长度为**偶数**，那么有两个长度都为这个环长度的一半的环在 $G_2$ 中出现了。
- 如果上面的点又有满足 $p_i=a_i$ 的，又有满足 $p_{p_i}=a_i$ 的，那么会有一个点数相同的基环内向树在 $G_2$ 中出现。（这种情况比较复杂，等会再说）

现在知道了 $G_2$ ，问 $G_1$ 的方案数。

环和基环树独立。先看环。

令长度为 $i$ 的环有 $cnt_i$ 个。每个环要么是单独在 $G_1$ 中出现，要么是与另一个环拼成一个大环在 $G_1$ 中出现。

枚举与别的环一起拼的环的个数 $2j$，那么把下面这些全步乘起来：
- $j\ne 0$ 时，先选出这些环，$\binom{cnt_i}{2j}$；
- $j\ne 0$ 时，然后想象成是个二分图，枚举左边的环是哪些，再把右边的环分给左边的环。注意实际上没有顺序，所以要再除掉一堆 $2$。$\frac{\binom{2j}{j}j!}{2^j}$；
- $j\ne 0$ 时，每对环有 $i$ 种拼法，$i^j$；
- $i$ 为奇数**且 $i\ne 1$ 时，**没有与别的环拼起来的环可以以两种形态在 $G_1$ 中出现，$2^{cnt_i-2j}$。

再看基环树。基环树之间也相互独立。

挂在基环树上的一堆链要压到环上。图的话，建议继续看学姐的博客。

抓比较重要的几点来说：1、每条链不能重叠，所以压链的话不能超过上一个有链的点。2、如果不考虑 1 中的限制，每条链有两种压法，上面的第一个点在 $G_1$ 中直接连向 $u$ 和两步连向 $u$。

所以说，每条链的压法只有 $0,1,2$，且互相独立。直接乘起来。

一些无解情况也可以很简单判了：在环上的点入度 $\le 2$，不在环上的点入度 $\le 1$。联想一下基环树的方案数算法应该很好理解。

时间复杂度 $O(n\log n)$，如果有闲心也可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010,mod=1000000007,inv2=500000004;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,a[maxn],deg[maxn],ans=1,stk[maxn],tp,q[maxn],h,r,len[maxn],seq[maxn],tot,cnt[maxn];
int fac[maxn],inv[maxn],invfac[maxn];
bool vis[maxn],ins[maxn],cyc[maxn];
void dfs(int u){
	if(vis[u]){
		if(ins[u]){
			ROF(i,tp,1){
				cyc[stk[i]]=true;
				if(stk[i]==u) break;
			}
		}
		return;
	}
	vis[u]=ins[u]=true;
	stk[++tp]=u;
	dfs(a[u]);
	ins[u]=false;
}
bool dfs2(int u){
	if(vis[u]) return true;
	vis[u]=true;
	seq[++tot]=len[u];
	return dfs2(a[u]) && !len[u];
}
inline int C(int n,int m){
	return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
inline int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
	return ans;
}
int main(){
	n=read();
	FOR(i,1,n) a[i]=read(),deg[a[i]]++;
	FOR(i,1,n) dfs(i);
	FOR(i,1,n) if(cyc[i] && deg[i]>=3|| !cyc[i] && deg[i]>=2) return puts("0"),0;
	h=1;r=0;
	FOR(i,1,n) if(!deg[i]) q[++r]=i;
	while(h<=r){
		int u=q[h++];
		len[a[u]]=len[u]+1;
		if(!cyc[a[u]]) q[++r]=a[u];
	}
	MEM(vis,0);
	FOR(i,1,n) if(cyc[i] && !vis[i]){
		tot=0;
		if(dfs2(i)) cnt[tot]++;
		else{
			int pre=0;
			FOR(j,1,tot) if(seq[j]){
				if(pre){
					int at=j-seq[j];
					if(at<pre) return puts("0"),0;
					if(at>pre && tot>=2) ans=2*ans%mod;
				}
				pre=j;
			}
			FOR(j,1,tot) if(seq[j]){
				int at=j-seq[j]+tot;
				if(at<pre) return puts("0"),0;
				if(at>pre && tot>=2) ans=2*ans%mod;
				break;
			}
		}
	}
	fac[0]=fac[1]=inv[1]=invfac[0]=invfac[1]=1;
	FOR(i,2,n){
		fac[i]=1ll*fac[i-1]*i%mod;
		inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
		invfac[i]=1ll*invfac[i-1]*inv[i]%mod;
	}
	FOR(i,1,n) if(cnt[i]){
		int s=0;
		FOR(j,0,cnt[i]/2){
			int x=1ll*C(cnt[i],2*j)*C(2*j,j)%mod*fac[j]%mod;
			if(j) x=1ll*x*qpow(inv2,j)%mod*qpow(i,j)%mod;
			if(i%2==1 && i!=1) x=1ll*x*qpow(2,cnt[i]-2*j)%mod;
			s=(s+x)%mod;
		}
		ans=1ll*ans*s%mod;
	}
	printf("%d\n",ans);
}
```

---

## 作者：tzc_wk (赞：3)

[Atcoder 题面传送门](https://atcoder.jp/contests/agc008/tasks/agc008_e) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT2267)

~~震惊，我竟然能独立切掉 AGC E 难度的思维题！~~

hb：nb tea 一道

感觉此题就是找性质，找性质，再找性质（

首先看到排列有关的问题，我们可以很自然地将排列拆成一个个**置换环**，即我们建一张图 $G$，对于 $i\in[1,n]$ 连边 $i\to p_i$，那么题目的要求就可以转化为：对于每个点 $i$，它置换环上下一步或者下下步为 $a_i$。

做出这个简单的转化后，就可以发现一个非常 trivial 的性质：

> Observation $1$. 如果存在三个及以上的 $i$ 满足 $a_i=x$，那么答案肯定是 $0$

证明显然，因为只有 $x$ 上一个或者上上个才能在两步之内到达 $i$。

这给我们一个启发，我们可以建一张新的图 $G'$，对于每个 $i$ 连边 $i\to a_i$，那么这个图满足每个点的入度 $\le 2$，每个点的出度为 $1$。我们还可以发现，$\forall i$，$i,a_i$ 在 $G$ 中肯定是在同一个置换环内的，因此 $G'$ 连通块的情况和 $G$ 连通块的情况是大体相同的。因此我们可以观察得出性质：

> Observation $2$. 对于某个 $G$ 中某个环 $C$，除了 $|C|$ 为偶数并且并且每个 $a_i$ 都是 $i$ 向后两步的位置的情况除外，其他情况 $C$ 中的元素在 $G'$ 的基图中依然连通。

说人话，就是对于绝大部分情况，原来在同一个连通块中的元素后来依然在一个连通块中，唯一一个例外是如果**置换环的大小 $siz$ 为偶数**，并且每个 $a_i$ 都是 $i$ 向后两步的位置，这种情况原来的置换环会分裂为两个大小为 $\dfrac{siz}{2}$ 的置换环。

简单证明一下，对于一个置换环而言，如果存在某个 $i$ 满足 $a_i$ 是 $i$ 的下一步位置，那么如果置换环大小为 $2$ 结论显然成立，否则设 $j$ 为 $i$ 上一个位置，那么 $a_j$ 必然是 $i$ 或 $a_i$ 中的一个，那么我们就可以将 $j$ 加入 $i$ 所在的连通块，再考虑 $j$ 的上一个位置 $k$，$a_k$ 必然也是 $i$ 或 $j$ 中的一个，如此归纳下去即可得证。也就是说置换环分裂的情况只可能是每个 $a_i$ 都是 $i$ 往后两格的位置，而如果置换环大小为奇数，简单画张图即可发现，最后建出来的必然还是一个与原置换环大小相同的环。得证。

---

这又给我一个启发：不妨来观察一下 $G'$ 中每个连通块的形态。我又画了几张图，发现了以下性质：

> Observation $3$. $G'$ 一定是一个基环内向森林，并且每个不在基环树上的点都形成一条条链

~~证明不会~~

![](https://cdn.luogu.com.cn/upload/image_hosting/wd0i7tum.png)

我们考虑再来看一下这个环和这些链有啥性质，以上图为例，按照之前的推论，$G'$ 的每个连通块一定是由一个环（我们称之为**主环**），和一些以主环上某个点为结尾的链（如果某条链以环上某个点 $x$ 结尾，那么我们就称这条链是挂在 $x$ 上的），我们假设挂在 $i$ 上的链的长度为 $b_i$——我们显然在 BFS 求出每个连通块的环的同时求出 $b_i$。

那么问题就来了，$G'$ 里面这个主环和原来的置换环有什么关系呢？

方便起见，我们将主环上的点按原来置换环上的顺序依次编号 $c_1,c_2,\cdots,c_k$。

> Obseration $4$. 主环一定是由 $c_1$ 沿着置换环每次跳 $1$ 格或两格，跳 $k$ 步之后形成的。

证明显然，因为置换环上相邻两个点 $c_i,c_{i+1}$ 必然满足 $c_{i+1}$ 是 $c_i$ 下一个节点，或者 $c_{i+1}$ 是 $c_i$ 下下个节点，所以每次必然是跳 $1$ 步或 $2$ 步。

知道了这个性质之后，我们就有对于 $k<$ 置换环大小 $|C|$ 的情况，跳 $k$ 步跳的总长度必然在 $k$ 和 $2k$ 之间，又因为它最后回到了原点，因此总长度必然是 $|C|$ 的整数倍，而 $2k<2|C|$，因此跳的总长度只可能是 $|C|$，这样一来我们可以将连通块分为三类：

- $2k<|C|$，此时就算每步跳 $2$ 格也达不到一周，总方案数就是 $0$。

- $|C|<2k<2|C|$，这种情况比较复杂我们过会儿讨论。

- $2k=2|C|$，即 $k=|C|$，此时该连通块就是一个环，那么我们记 $num_i$ 为有多少个这样的大小为 $i$ 的连通块，那么对于每个环而言，它在原排列 $p$ 中有三种可能：

  - 保持不变，即 $p$ 中也存在一个和该置换环一模一样的置换环
  - 如果 $i>1$ 且为奇数，那么存在一个长度等于 $i$ 的置换环，满足从环上某个点开始每次跳两步得到的环与原连通块相同。
  - 和另一个大小为 $i$ 的置换环拼成一个长度为 $2i$ 的置换环，假设我们已经选出了这两个置换环 $C_1,C_2$，那么我们固定住 $C_1$ 的某个位置，置换环 $C_1$ 放置的位置就确定了，此时 $C_2$ 可以随意旋转，有 $i$ 种可能。举个栗子，置换环 $(1,2,3,4)$ 和 $(5,6,7,8)$ 拼在一起有 $(1,5,2,6,3,7,4,8),(1,6,2,7,3,8,4,5),(1,7,2,8,3,5,4,6),(1,8,2,5,3,6,4,7)$ 四种可能（梦回 P4709？）

  因此考虑枚举有多少对长度为 $i$ 的置换环拼在一起，记这个数为 $j$，那么选出这 $j$ 对置换环的方案数为 $\dfrac{1}{j!}\prod\limits_{k=0}^{j-1}\dbinom{num_i-2k}{2}$，这 $j$ 对置换环拼在一起的方案数为 $i^j$，安放剩余置换环的方案数为 $t^{num_i-2j}$，其中 $t$ 表示每个置换环在原排列中的方案数，如果 $i>1$ 且 $i$ 为奇数那么 $t=2$，否则 $t=1$，因此总贡献为 $i^j\times t^{num_i-2j}\dfrac{1}{j!}\prod\limits_{k=0}^{j-1}\dbinom{num_i-2k}{2}$，这个东西显然可以在枚举 $j$ 的同时维护，时间复杂度 $\mathcal O(n\log n)$ 或 $\mathcal O(n)$，~~取决于你的心情~~。

---

到这里我们已经解决了本题的大部分情况，还剩最棘手的一种情况没有解决——那就是 $|C|<2k<2|C|$，即图是一个纯正的基环树（大雾）的情况。

考虑这些链是哪里来的，观察一会儿可以发现：

> Observation $5$. 对于一个主环上的点 $c_x$ 引出的长度为 $len$ 的链，它在原置换环上有以下两种情况（其中蓝线为 $G'$ 中的边，绿边为 $G$ 中的边（注：下图中的 $C_{x-len+1}$ 应为 $C_{x-len+2}$，$C_{x-len},C_{x-len-1}$ 也同理应该变为 $C_{x-len+1},C_{x-len}$，传上去之后才发现有问题，懒得改了/cy）：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/r9rk6ah7.png)
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/dgzvh1yu.png)

~~说人话~~用数学语言来表述，也就是说假设这条链上 $len$ 个点为 $p_1,p_2,p_3,\cdots,p_{len}$，那么有以下可能：

- $p_1$ 夹在 $c_x,c_{x-1}$ 中间，$p_2$ 夹在 $c_{x-1},c_{x-2}$ 中间，……，$p_{len}$ 夹在 $c_{x-len+1},c_{x-len}$ 中间
- $c_x,c_{x-1}$ 中间没有点，$p_1$ 夹在 $c_{x-1},c_{x-2}$ 中间，$p_2$ 夹在 $c_{x-2},c_{x-3}$ 中间，……，$p_{len}$ 夹在 $c_{x-len},c_{x-len-1}$ 中间

我们给 $c_i,c_{i-1}$ 中间边的状态（中间夹了多少个点）量化为一个数组 $e_i$，那么显然 $e_i\le 2$，否则 $c_i$ 就不是 $c_{i-1}$ 的下个点或下下个点了，此时以下两种排列的方案就可以表述为：

- 令 $e_x,e_{x-1},e_{x-len+1}$ 加 $1$
- 强制令 $e_x=0$，并令 $e_{x-1},e_{x-2},\cdots,e_{x-len}$ 加 $1$

不难发现这相当于一个环上的区间覆盖问题，第一种方案可以视作覆盖了区间 $[x-len+1,x]$，第二种方案可视作覆盖了区间 $[x-len,x]$，每个点覆盖的区间不能相交。

这样还是不太好直接下手，因为它是一个环，直接 $dp$ 显然会出现后效性。不过我们可以很自然地想到断环成链，即找到环上第一个 $b_i\ne 0$ 的点 $ps$，枚举 $ps$ 覆盖的区间（$[ps-b_{ps}+1,ps]$ or $[ps-b_{ps},ps]$），这样就可以视作链上的 $dp$ 了，$dp_i$ 表述考虑链上 $ps\sim i$ 的点的放置方案，转移就实时维护上一个 $b_j\ne 0$ 的点 $j$，分情况讨论：

- $j\ge i-b_i+1$，$dp_j=0$，因为无论覆盖 $[i-b_i+1,i]$ 还是 $[i-b_i,i]$ 都会与上一个区间有交
- $j=i-b_i$，$dp_j=dp_i$，因为只能覆盖 $[i-b_i+1]$
- $j<i-b_i$，$dp_j=2dp_i$

具体实现时，不需真的建出 $dp$ 数组，由于 $dp_i$ 只与上一个 $j$ 的 $dp$ 值有关，因此可以维护一个变量表示上一个位置的 $dp$ 值，复杂度 $\mathcal O(\text{环的大小})$，而由于 $\sum\text{环的大小}$ 为 $\mathcal O(n)$，因此这部分复杂度是 linear 的。

---

于是这题就真的做完了，复杂度 $n\log n$ or $\mathcal O(n)$

细节多得一批……程序下面放了两组 hack 数据，是我在与 std 对拍过程中曾经错过的数据。

```cpp
const int MAXN=1e5;
const int MOD=1e9+7;
const int INV2=5e8+4;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,a[MAXN+5],in[MAXN+5],deg[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	for(int i=(ifac[0]=ifac[1]=1)+1;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int bel[MAXN+5],comp=0,siz[MAXN+5],cyc[MAXN+5],b[MAXN+5];
bool vis[MAXN+5];
void dfscomp(int x){
	if(bel[x]) return;bel[x]=comp;
	for(int e=hd[x];e;e=nxt[e]) dfscomp(to[e]);
}
vector<int> c[MAXN+5];
void findcyc(int x){
	if(vis[x]) return;c[bel[x]].pb(x);
	vis[x]=1;findcyc(a[x]);
}
int num[MAXN+5],way[MAXN+5];
int main(){
	scanf("%d",&n);init_fac(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),in[a[i]]++;
	for(int i=1;i<=n;i++) deg[i]=in[i];
	for(int i=1;i<=n;i++) adde(i,a[i]),adde(a[i],i);
	for(int i=1;i<=n;i++) if(in[i]>=3) return puts("0"),0;
	for(int i=1;i<=n;i++) if(!bel[i]) comp++,dfscomp(i);
	for(int i=1;i<=n;i++) siz[bel[i]]++,b[i]=1;
	queue<int> q;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();vis[x]=1;
		if(!--in[a[x]]) q.push(a[x]),b[a[x]]+=b[x];
	}
	for(int i=1;i<=n;i++) if(vis[i]&&deg[i]==2) return puts("0")&0;
	for(int i=1;i<=n;i++) if(!vis[a[i]]&&vis[i]) b[a[i]]+=b[i];
	for(int i=1;i<=n;i++) b[i]--;
	for(int i=1;i<=n;i++) if(!vis[i]) findcyc(i);
	for(int i=1;i<=comp;i++) cyc[i]=c[i].size();
	int ans=1;
	for(int i=1;i<=comp;i++){
		if(siz[i]==cyc[i]){num[siz[i]]++;continue;}
		if(siz[i]==2){way[i]=1;continue;}
		if((cyc[i]<<1)<siz[i]) return puts("0")&0;
		int ps=-1,len=-1;
		for(int j=0;j<c[i].size();j++){
			int x=c[i][j];
			if(b[x]){ps=j;len=b[x];break;}
		} assert(~ps);
		int pre=ps,pre_dp=1;
		for(int j=ps+1;j<c[i].size()+ps;j++){
			int id=c[i][j%c[i].size()];
			if(b[id]){
				int cur_dp=0;
				if(j<ps-len+1+c[i].size()){
					if(j-b[id]+1>pre) cur_dp=pre_dp;
					if(j-b[id]>pre) cur_dp=(cur_dp+pre_dp)%MOD;
				} pre_dp=cur_dp;pre=j;
			}
		} way[i]=(way[i]+pre_dp)%MOD;
		if(len!=cyc[i]){
			pre=ps;pre_dp=1;
			for(int j=ps+1;j<c[i].size()+ps;j++){
				int id=c[i][j%c[i].size()];
				if(b[id]){
					int cur_dp=0;
					if(j<ps-len+c[i].size()){
						if(j-b[id]+1>pre) cur_dp=pre_dp;
						if(j-b[id]>pre) cur_dp=(cur_dp+pre_dp)%MOD;
					} pre_dp=cur_dp;pre=j;
				}
			} way[i]=(way[i]+pre_dp)%MOD;
		} ans=1ll*ans*way[i]%MOD;
	}
	for(int i=1;i<=n;i++){
		int mul=1,sum=0;
		for(int j=0;(j<<1)<=num[i];j++){
			sum=(sum+1ll*mul*qpow(((i&1)&&(i^1))?2:1,num[i]-(j<<1))%MOD*ifac[j])%MOD;
			mul=1ll*mul*(num[i]-(j<<1))%MOD*(num[i]-(j<<1)-1)%MOD*INV2%MOD*i%MOD;
		} ans=1ll*ans*sum%MOD;
	} printf("%d\n",ans);
	return 0;
}
/*
6
2 3 1 1 4 4
*/
/*
6
2 3 1 1 4 5
*/
```



---

## 作者：DaiRuiChen007 (赞：2)

# AGC008E 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc008_e)

**题目大意**

> 给定一个数组 $a_1\sim a_n$，求多少个排列 $p_1\sim p_n$ 对于所有 $i$ 满足 $a_i\in\{p_i,p_{p_i}\}$。
>
> 数据范围：$n\le 10^5$。

**思路分析**

观察 $p_i$ 对应的环：若所有 $a_i$ 全取 $p_i$ 则是原来的环，若所有 $a_i$ 取 $p_{p_i}$ 则是 $\sqrt p$，可能是一个同等大小的环，也有可能是一个被切成两半的环，这取决于环长的奇偶性。

接下来考虑不全取 $p_i/p_{p_i}$ 的情况，首先可以证明一定是一个连通块，否则必然全取 $p_{p_i}$，观察后能够发现得到的 $i\to a_i$ 构成一个基环内向树，并且环外只有单链。

考虑对于一个基环内向树如何还原 $p_i$，考虑记 $i$ 点延长的链长为 $L$，$i$ 点到前一个有延长链的环上节点距离为 $L'$，若 $L>L'$ 显然无解，若 $L<L'$，则链顶可以选择放在 $i-1\to i$ 或 $i-2\to i-1$ 上，否则选择唯一。

然后考虑环的还原，显然同大小的一起考虑，设大小为 $k$ 的有 $s$ 个，枚举合并的对数能够得到方案数：$\sum_{j=0}^{2j\le s}\binom{s}{2j}\times (2j-1)!!\times k^j\times ([k>1\text{ and }2\nmid k]+1)^{s-2j}$。其中 $\binom{s}{2j}$ 是选拼环的元素，$(2j-1)!!=(2j-1)(2j-3)\cdots$ 是配对的方案数，$k^j$ 是每个环合成的方案数，而且当 $k>1,2\nmid k$ 时，每个奇环有两种分解方式（$a_i\gets p_i/p_{p_i}$）。

每个连通块模拟讨论即可。

时间复杂度 $\mathcal O(n\log P)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5,MOD=1e9+7;
int a[MAXN],cnt[MAXN],ans=1;
vector <int> G[MAXN];
bool vis[MAXN],inc[MAXN];
int len[MAXN],nxt[MAXN];
inline void solve(int s) {
	while(!vis[s]) vis[s]=true,s=a[s];
	vector <int> cyc{s};
	for(int t=a[s];t^s;t=a[t]) cyc.push_back(t);
	reverse(cyc.begin(),cyc.end());
	int tot=cyc.size();
	for(int i:cyc) inc[i]=true;
	bool isc=true;
	for(int i:cyc) {
		if(G[i].size()>2) puts("0"),exit(0);
		if(G[i].size()<2) continue;
		isc=false;
		int j=G[i][inc[G[i][0]]];
		len[i]=1;
		while(!G[j].empty()) {
			if(G[j].size()>1) puts("0"),exit(0);
			vis[j]=true,++len[i],j=G[j][0];
		}
		vis[j]=true;
	}
	if(isc) return ++cnt[tot],void();
	for(int i=tot-1;~i;--i) nxt[i]=len[cyc[i]]?0:nxt[(i+1)%tot]+1;
	for(int i=tot-1;~i;--i) nxt[i]=len[cyc[i]]?0:nxt[(i+1)%tot]+1;
	for(int i=0;i<tot;++i) if(len[cyc[i]]) {
		int rest=nxt[(i+1)%tot]+1;
		if(len[cyc[i]]<rest) ans=ans*2%MOD;
		else if(len[cyc[i]]>rest) puts("0"),exit(0);
	}
}
int fac[MAXN],inv[MAXN],f[MAXN];
inline int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
	return ret;
}
inline int binom(int n,int m) {
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=fac[0]=inv[0]=1;i<=n;++i) inv[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i=f[0]=1;i<=n;++i) f[i]=f[i-1]*(2*i-1)%MOD;
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),G[a[i]].push_back(i);
	for(int s=1;s<=n;++s) if(!vis[s]) solve(s);
	for(int i=1;i<=n;++i) if(cnt[i]) {
		int sum=0;
		for(int j=0;2*j<=cnt[i];++j) {
			int bas=(i%2==1&&i>1)?2:1;
			sum=(sum+binom(cnt[i],2*j)*f[j]%MOD*ksm(i,j)%MOD*ksm(bas,cnt[i]-2*j)%MOD)%MOD;
		}
		ans=ans*sum%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：2)

写一下我的思考路径。

首先考虑 $a_i$ 形成一个排列的话怎么做。我们发现假如 $a_i$ 恰好形成一个置换环，那么如果 $n>1$ 且 $n$ 为奇数那么答案就是 $2$（可以 $p_{p_i}=a_i$），否则就是 $1$。

然后我们发现 $a$ 所形成的不同置换环之间还可以合并。而可以合并的两个置换环的充要条件是两者大小相等。因为我们合并两个环 $x_1\to \dots\to x_m$ 和 $y_1\to \dots\to y_m$，最后一定是形如 $x_1\to y_i\to x_2\to y_{i+1}\to\dots\to x_m\to y_{i-1}$ 的大环，如果大小不相等会出问题。然后我们也能求出合并后的方案数为 $m$，即环的大小。

所以对于每个环的大小我们都做一次 DP，$f_i$ 表示 $i$ 个大小为 $m$ 的环，可随意合并的方案数，于是 $f_i=p\times f_{i-1}+m\times(i-1)\times f_{i-2}$，其中 $p$ 为上面所说过的不合并时一个大小为 $m$ 的环的答案。

然后考虑有重复的 $a_i$ 的情况。首先考虑由 $E=\{(i,a_i)\}$ 组成的有向图，我们取出所有弱连通块。这个弱连通块只可能是基环树或环。通过上面的推理我们也可以得知基环树是无法和环合并的。所以可以分开独立考虑。如果这个弱连通块是一个环，那么上面已经说过了。否则就是一棵根向基环树，所以我们独立考虑每一棵基环树。

这里我画了很多种情况。一个可以尽可能保证讨论到位的办法可能就是写个暴力然后看看有哪些情况吧。

对于一棵基环树，我们发现它有解的一个必要条件是把环拆掉后会形成几条链。于是我们来看一条链的影响。手动模拟可知（假如环上点标号为 $1,\dots,k$），一条挂在 $x$ 节点上的长 $r$ 的链（假如链上点标号为 $k+1,\dots,k+r$）有两种处理方式：第一种是 $p_{k+1}=x,p_{x-1}=k+1,p_{k+2}=x-1,p_{x-2}=k+2,\dots,p_{x-r}=k+r$，第二种是 $p_{x-1}=x,p_{k+1}=x-1,p_{x-2}=k+1,\dots,p_{x-r-1}=k+r$。

于是对答案的贡献可以这样计算：对于挂了长 $r$ 的链的节点 $x$，如果它之前 $k+1$ 个点都没挂链，那么贡献是 $2$；如果只有 $k$ 个点没挂链，那么贡献是 $1$；否则就无解了。

可能有些小细节。

https://atcoder.jp/contests/agc008/submissions/40485618

---

## 作者：ducati (赞：1)

感觉这题评了 $\color {red} \text {3559}$ 的主要原因是代码容易写挂，思路其实挺自然的。

## Description

[传送门](https://www.luogu.com.cn/problem/AT_agc008_e)

## Solution

$\forall i \in [1,n]$，连一条 $i$ 到 $a_i$ 的边，得到内向基环树森林。

先考虑各连通块均为环怎么做。考虑排列 $p$ 中的置换环 $t_1 \to t_2 \to \cdots \to t_k \to t_1(p_{t_1}=p_{t_2},p_{t_2}=p_{t_3},\cdots,p_{t_k}=p_{t_1})$，若从 $t_1$ 开始，每次往后走一或两步，经过环上各点恰一次，且最终返回 $t_1$，只有以下两种不同的走法：

- 依次经过 $t_1,t_2,\cdots,t_k$
- 依次经过 $t_1,t_3,t_5,\cdots,t_2,t_4,\cdots$。**要求** $k$ **为奇数**，且 $k>1$（防止与第一种重复）

换言之，对于环 $G=(V,E)$，若 $p$ 中存在置换环点集等于 $V$（不妨称为一类环），则方案数为 $1+[|V| \equiv 1 \pmod 2, |V| > 1]$。否则，若 $G$ 仅属于 $p$ 中某置换环的一部分（称为二类环），则其必定由两个等长的环拼接而成；具体来说，若两个环 $x_1 \to x_2 \to \cdots \to \cdots \to x_k \to x_1$，$y_1 \to y_2 \to \cdots \to y_k \to y_1$ 长度均为 $k$，则可拼接得恰好 $k$ 种不同的置换环，例如 $x_1 \to y_1 \to x_2 \to y_2 \to \cdots \to x_k \to y_k \to x_1$ 等等。

令 $buc_i$ 表示长度 $=i$ 的环数。由于每种环长是独立的，可分开计算。枚举长度 $=i$ 的二类环个数 $j$（显然 $j$ 为偶数），预处理出 $f$ 表示将若干不同的物品两两配对的方案数，则贡献为

$${buc_i \choose j} (1+[i \equiv 1 \pmod 2, i > 1])^{buc_i-j} f_j i^{\frac j 2})$$

再考虑存在非环连通块怎么做。令某棵基环树的环为 $c_1 \to c_2 \to \cdots \to c_l \to c_1$，考虑该树对应的置换环，则 $(c_1,c_2),(c_2,c_3),\cdots,(c_l,c_1)$ 间，分别至多插入一个点。从而，环挂着的所有树，都必须形如一条链，否则无解。

考虑 $c_p$ 挂着的链，可将该链依次插到 $c_{p-1},c_{p-2},\cdots$ 之后，也可将 $c_{p-1}$ 之后留空并插入 $c_{p-2},c_{p-3},\cdots$ 之后。每条链都会占据环上的一个连续段 $[L,R]$，$R$ 固定，$L$ 有两种相邻位置可选，要求各段两两无交。对每条链计算方案数 $wys(wys \in [0,2])$，将答案乘上 $wys$ 即可。

时间复杂度 $O(n)$。

## Code

```cpp
include <bits/stdc++.h>
define int long long
using namespace std;
const int N=1e5+5,mod=1e9+7;

int read(){
	int s=0,w=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,ans,a[N],pw[N],ord[N],buc[N],f[N],fac[N],ifac[N],tw[N];
int vis[N],frt[N],occ[N],ssz[N],on_cir[N]; vector<int> GA[N];
int quick_power(int x,int y){
	int res=1;
	for (;y;y>>=1,(x*=x)%=mod) {if(y&1)(res*=x)%=mod;}
	return res;
}
void Fail(){puts("0"),exit(0);}
void init(){
	f[0]=fac[0]=1;
	for (int i=2;i<=n;i+=2)  f[i]=((i-1)*f[i-2])%mod;
	for (int i=1;i<=n;i++)  fac[i]=(fac[i-1]*i)%mod;
	ifac[n]=quick_power(fac[n],mod-2);
	for (int i=n-1;~i;i--)  ifac[i]=(ifac[i+1]*(i+1))%mod;
}
int Binom(int x,int y){return (fac[x]*ifac[y]%mod*ifac[x-y])%mod;}
int dfs_sz(int u,int F){
	int cnt_son=0,sz=(F>0);
	for (int v:GA[u]){
		if ((v^F)&&!on_cir[v])  sz+=dfs_sz(v,u),cnt_son++;
	}
	if (cnt_son>1)  Fail();
	return sz;
}
signed main(){
	n=read(),ans=pw[0]=tw[0]=1,init();
	for (int i=1;i<=n;i++)  GA[a[i]=read()].emplace_back(i);
	for (int i=1;i<=n;i++)if(!vis[i]){
		int x=i,len=0,typ=0;
		while (!vis[x])  vis[x]=i,x=a[x];
		if (vis[x]^i)  continue;
		while (!on_cir[x])  on_cir[x]=1,x=a[x],ord[++len]=x;
		for (int j=1;j<=len;j++)  frt[j]=((j==1)?len:(j-1)),occ[j]=0;
		for (int j=1;j<=len;j++){
			ssz[j]=dfs_sz(ord[j],0);
			if (ssz[j])  occ[frt[j]]++,typ=1;
		}
		if (!typ) {buc[len]++;continue;}
		for (int j=1;j<=len;j++)if(ssz[j]){
			int l=j,sum=0,wys=0;
			for (int t=1;t<=ssz[j];t++)  sum+=occ[l=frt[l]];
			if (sum==1)  wys++;
			if (sum+occ[frt[l]]==1)  wys++;
			if (!wys)  Fail();
			else if (wys>1)  (ans<<=1)%=mod;
		}
	}
	for (int s=1;s<=n;s++)if(buc[s]){
		int ctb=1+((s>1)&&(s&1)),cnt=buc[s],res=0;
		for (int j=1;j<=cnt;j++)  pw[j]=(pw[j-1]*ctb)%mod;
		for (int j=1;(j<<1)<=cnt;j++)  tw[j]=(tw[j-1]*s)%mod;
		for (int j=0;j<=cnt;j+=2)  (res+=Binom(cnt,j)*pw[cnt-j]%mod*f[j]%mod*tw[j>>1])%=mod;
		(ans*=res)%=mod;
	}
	return cout<<ans,0;
}
```


---

## 作者：Otomachi_Una_ (赞：0)

e. **[[AGC008E] Next or Nextnext](https://atcoder.jp/contests/agc008/tasks/agc008_e)（7）**

好题！

我们观察一个环，构建新图每个边连向 $p_i$ 或 $p_{p_i}$ 的大概可能的形状：

- 情况一：全部连 $p_i$，没有改变。
- 情况二：全部连 $p_{p_i}$，如果 $n$ 是奇数则形成另一种环，$n$ 是偶数形成两个环。

下面会说明只有以上两种情况会形成环。于是环的部分可以直接 dp 计算。要么一个环独立或交叉形成，或者和另一个环拼接而成。

下面我们讨论基环树的情况。

- 情况三：有 $p_i$ 也有 $p_{p_i}$。我们先证明一些猜的引理：

  > 引理 1：形成的图必然是基环树。
  >
  > 证明：因为图是 $i\to p_i$ 所以形成基环树森林，假设存在 $u\to p_u$，则对于 $p_v=u$ 的 $v$，$v$ 指向 $u$ 或 $p_u$，即 $v$ 和 $u$ 也联通。归纳下去即可。

  > 引理 2：基环树森林当中非环连通块必然是链。如下图当中，红色部分为非环边，那么红色部分是若干链组成。
  >
  > ![](https://cdn.luogu.com.cn/upload/image_hosting/km57xs28.png)
  >
  > 证明：否则，存在非环点 $u$ 使得 $u\to p_{p_u},p_u\to p_{p_u}$ 且 $u,p_u,p_{p_u}$ 不在环上。由于有 $p_u\to p_{p_u}$，根据引理 $1$ 我们知道环必然经过 $p_u,p_{p_u}$ 之间的一点。矛盾！

上面的引理告诉我们：

- 新图是一颗基环树。
- 非环部分是若干的链。

我们剩下的任务就是把链“塞”回到环当中。下面展现了仅有的两种塞链的方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/i4vcoddf.png)
这告诉我们如果当前点有 $l(l>0)$ 的外链，且距离上一个需要塞的地方为 $l_0$，那么：

- $l<l_0$：有 $2$ 种方案。
- $l=l_0$：有 $1$ 种方案。
- $l>l_0$：无解。

至此我们完成了本题。码量有点小大。

[submission](https://atcoder.jp/contests/agc008/submissions/43694112)

---

## 作者：Orion545 (赞：0)

# 广告

[蒟蒻のblog](https://www.cnblogs.com/dedicatus545/p/9715671.html)

# 思路

## p到a

首先，本题中如果对于所有的$i$，连边$<i,p_i>$，那么可以得到一批环

那么这个题另外一点就是，可以变成连边$<i,p_{p_i}>$

我们分多种情况来讨论

### 情况1：啥也没变

就是啥也没变

### 情况2：全都变了

这时考虑奇环和偶环

对于一个奇环，全部变了以后，它还是一个环，但是不是同构的

对于一个偶环，全换了以后，它会变成两个环，分别是全部奇数节点和全部偶数节点

### 情况3：变了一部分

此时容易发现，变出去的部分应该会这样：

$<i,p_i>$变成$<i,p_{p_i}>$，则$p_i$变成环上外挂的一个节点

这样一直讨论下去可以得到，最终我们会得到一棵环套树，并且每一棵树都只有可能是一条链

对于每一条链我们这样考虑：

如果链形如这样：

![](http://images.cnblogs.com/cnblogs_com/dedicatus545/1199264/o_1.png)

那么肯定ans=0，因为这个长度为2的链没有2条环边配合他

如果恰好相等，那么这条链只有一种情况

如果不相等，那么这条链会有两种情况：放在这一段环的最开始和最末尾

此时它对答案贡献一个乘2

## a到p

讨论完以后，我们回到问题本身，发现我们拿到了的是$a$不是$p$

所以我们要求的实际上就是这个$<i,a_i>$图反推回去的方案数

那么，我们把环和环套树分开处理

显然环套树就是按照上面的讨论，乘1乘2或者乘0

对于所有长度相同的环，我们需要考虑它们两两合并的情况

此时可以用数学方法很快求出

具体一点来说，如果有$n$个长度为$L$的环，那么它们的贡献就是

$\sum_{t=0}^{\lfloor \frac{n}{2}\rfloor} L^n f(t*2) C(n,2*t) $

如果$n$是大于1的奇数还要再乘以2（因为此时可以像上面说的那样自我同构一下）

其中$f(2*t)$ 表示的是 $2*t$个数互相配对的方案数

最后把所有长度的环的贡献乘起来，再乘上每个环套树的贡献，就是答案了

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define MOD 1000000007
using namespace std;
inline int read(){
	int re=0,flag=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(isdigit(ch)) re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
	return re*flag;
}
ll f[200010],finv[200010],meth[200010];
ll qpow(ll a,ll b){
	ll re=1;
	while(b){
		if(b&1) re=(re*a)%MOD;
		a=a*a%MOD;b>>=1;
	}
	return re;
}
void init(){
	ll i,len=200000;
	f[0]=f[1]=finv[0]=finv[1]=1;
	for(i=2;i<=len;i++) f[i]=f[i-1]*i%MOD;
	finv[len]=qpow(f[len],MOD-2);
	for(i=len;i>2;i--) finv[i-1]=finv[i]*i%MOD;
}
int n,a[200010],vis[200010],cir[200010],cntcir=0,in[200010],bst[200010],siz[200010];
ll ans=1;
vector<int>s;
vector<int>nd[200010];
bool cmp(int l,int r){
	return siz[l]<siz[r];
}
ll C(ll x,ll y){
	return f[x]*finv[y]%MOD*finv[x-y]%MOD;
}
int main(){
	n=read();int i,j;ll tmp,c,cc;
	init();
	meth[0]=1;
	for(i=1;i<=n;i++) meth[i]=C(i*2,i)*f[i]%MOD*qpow(qpow(2,MOD-2),i)%MOD;

	for(i=1;i<=n;i++) a[i]=read(),in[a[i]]++;
	for(i=1;i<=n;i++){//取出环
		j=i;
		while(!vis[j]) vis[j]=i,j=a[j];
		if(vis[j]^i) continue;
		cntcir++;
		while(!cir[j]){
			cir[j]=cntcir,nd[cntcir].push_back(j),siz[cntcir]++,j=a[j];
		}
	}
	memset(vis,0,sizeof(vis));
	for(i=1;i<=n;i++){//判断环套树，以及外挂树是不是都是链
		if(in[i]) continue;
		j=i;
		while(!cir[j]&&!vis[j]) j=a[j];
		if(vis[j]){
			puts("0");return 0;
		}
		bst[cir[j]]=1;tmp=cir[j];
		j=i;c=0;
		while(!cir[j]) cir[j]=tmp,c++,vis[j]=1,j=a[j];
		vis[j]=c;
	}
	for(i=1;i<=cntcir;i++){//环套树处理
		if(!bst[i]){s.push_back(i);continue;}
		for(j=0;j<nd[i].size();j++) if(vis[nd[i][j]]) break;
		tmp=j;
		do{
			c=j;cc=1;
			j--;
			(j+=(int)nd[i].size());
			j%=(int)nd[i].size();
			for(;!vis[nd[i][j]];j--,j=((j<0)?j+nd[i].size():j)) cc++;
			if(vis[nd[i][c]]>cc){
				puts("0");return 0;
			}
			if(vis[nd[i][c]]<cc) (ans*=2)%=MOD;
		}while(tmp!=j);
	}
	sort(s.begin(),s.end(),cmp);
	for(i=0;i<s.size();i+=c){
		j=i;tmp=0;
		while(siz[s[j]]==siz[s[i]]&&j<s.size()) j++;
		c=j-i;
		for(j=0;j<=c/2;j++){
			(tmp+=C(c,2*j)*meth[j]%MOD*qpow(siz[s[i]],j)%MOD*qpow(2,(c-2*j)*(siz[s[i]]!=1)*(siz[s[i]]&1))%MOD)%=MOD;
		}
		ans=ans*tmp%MOD;
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Kevin090228 (赞：0)

考虑边 $i\rightarrow a_i$ 组成的有向图，它一定是一个基环树森林。

我们注意到，若一个基环树满足存在一个点，有至少两个非环上的点连向它，答案就为 $0$。

两个长度为 $n$ 的环还可以合并，合并的方案有 $n$ 种。一个基环树上的方案是容易计算的。然后随便乘法原理计数一下即可。

注意一个细节：长度为大于 $1$ 的奇数的一个单环有两种方案：一步一跳和两步一跳。

时间复杂度 $O(n)$。

---

