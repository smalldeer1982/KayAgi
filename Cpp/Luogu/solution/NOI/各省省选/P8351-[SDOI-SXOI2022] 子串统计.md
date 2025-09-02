# [SDOI/SXOI2022] 子串统计

## 题目描述

小 D 四岁半的时候学会了后缀自动机。

你有一个字符串 $S$，长度为 $n$。初始时，$T_0=S$。每次你可以从删除 $T_i$ 的开头或结尾的字符得到新的字符串 $T_{i + 1}$，经过 $n-1$ 次操作之后，我们会得到只有一个字符的串 $T_{n - 1}$，根据每次删除的选择，一共有 $2^{n - 1}$ 种可能的操作序列。注意，虽然可能会有一次操作，删除开头或结尾的字符得到相同的串，但是我们仍然把它当成两种不一样的操作序列。

对于一个串 $T$，我们记 $\operatorname{\textit{occ}}(T)$ 表示 $T$ 在 $S$ 中作为子串的出现次数，比如 $\operatorname{\textit{occ}}(\texttt{aaa},\texttt{aaaabaaa})=3$。

对于一个操作序列，记它贡献是

$$\prod_{i = 1}^{n - 1} \operatorname{\textit{occ}}(T_i)$$

求出所有操作序列的贡献和，由于答案很大，请输出答案对 $998244353$ 取模的结果。

## 说明/提示

### 数据规模与约定

本题共 $20$ 个测试点。

- 对于测试点 $1\sim 5$，满足 $|S| \le 5000$。
- 对于测试点 $6\sim 8$，满足 $S$ 的每个字符均从 $\texttt a$ 和 $\texttt b$ 中等概率独立随机生成。
- 对于测试点 $9\sim 14$，满足 $|S| \le 6 \times 10^4$。

对于所有数据，$1 \le |S| \le 10^5$。$S$ 中只有小写英文字母。

## 样例 #1

### 输入

```
zzz
```

### 输出

```
24
```

## 样例 #2

### 输入

```
abbab
```

### 输出

```
53
```

## 样例 #3

### 输入

```
见附加样例文件中的 ex_substring3.in```

### 输出

```
见附加样例文件中的 ex_substring3.out```

# 题解

## 作者：zhoukangyang (赞：25)

[来 cnblogs 里看。](https://www.cnblogs.com/zkyJuruo/p/16403110.html)

题出的好！难度不适中，覆盖知识点广，题目又着切合实际的背景，解法比较自然。

给出题人点赞 ！

## 题意 

> 给定长度为 $n$ 的字符串 $s$。你有一个字符串 $t = s$，你每次操作可以在前面或在后面删除一个字符，直到字符串中只有一个字符。设每次操作后得到的字符串分别是 $a_1,a_2,..,a_{n-1}$，那么这种操作的权值就是 $\prod_{1 \le i < n} occ(a_i)$。其中 $occ(a)$ 表示字符串 $a$ 在 $s$ 中的出现次数。求对于所有操作序列的权值和。

> 数据范围：$n \le 10^5$

## 题解

首先考虑一下有哪些本质不同的串，满足从左边或右边删除一个字符，能使得在整个串中出现的次数变大了。称这样的串为 "好串"。

不妨仅考虑从左删除一个字符，有多少出现次数变了：只有 $\text{parent tree}$ 的节点 $x$ 上，长度恰好为 $maxlen_{fa_x}+1$ 的串。因此满足这种条件的串只有 $\Theta(n)$ 个。

我们把 "好串" 和 "好串" 从前或从后删除一个字符后得到的串称为 "关键串"。我们已经知道了出现次数不同的串之间的转移了，因此现在我们只用关心出现次数相同的关键串之间的转移了。

我们只关心每个串第一次出现时的**位置**。由于每个串在整个串中出现的次数相同，因此这样做，串间的包含关系不变。

接下来我们就可以写一份暴力了，可以直接树状数组暴力枚举每个串 $[l,r]$ 的子串 $[x,y]$，从 $[l,r]$ 走到 $[x,y]$ 的权值是 $\binom{x-l+r-y}{x-l} c^{r-l+1} c^{-(y-x)}$。这样可以拿到 $40$ 分。

考虑优化。我们显然可以把 $c^{r-l+1} c^{-(y-x)}$ 直接在两个区间处直接处理掉，因此我们就只用考虑从 $[l,r]$ 走到 $[x,y]$ 的方案数了。

直接算方案数很难算，我们不妨先打个表看看关键串出现的位置有没有什么规律：

![](https://cdn.luogu.com.cn/upload/image_hosting/178du4t2.png)

可以发现，对于每种颜色的每一块，围成的区域很规整。可以看作是一个长度为 $m$ 的序列 $a$ 满足 $a_{i} \le a_{i+1}$，表示有 $i$ 列，第 $i$ 列从上到下有连续 $a_i$ 个元素。

为什么是这个形状的呢？首先容易发现如果一个点下面和右边都在连通块内，那么这个点也在连通块内。

其次就是这个图形满足只有一个点是 "极点" 的（也就是满足上面和右边都不在连通块内），这个可以考虑如果存在两个，这两个同时包含串 $t$，而这两个串不相交，说明串 $t$ 的出现次数并不一样。因此就只有一个 "极点" 了。

------

接下来考虑怎么求解。我们要从右上角的元素转移到左下角边界上的元素。这个东西可以用类似 gym102978J 的分治算法，每次取出 $mid$ 划分，中间用 $4$ 次卷积转移，然后分裂成两个问题。具体如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xolc055d.png)

时间复杂度 $\Theta(n \log^2 n)$。

---

## 作者：Mobius127 (赞：3)

[题传](https://www.luogu.com.cn/problem/P8351)

细节好多/px

考虑 naive 的 $O(n^{2})$ DP，设 $f_{[l, r]}$ 表示当前串为 $[l, r]$ 的路径权值和，答案即为 $\sum f_{[i, i]}$。

我们考虑[基本子串结构](https://www.luogu.com.cn/blog/Tomori-Nao/xue-xi-bi-ji-ji-ben-zi-chuan-jie-gou)，注意到本题本质上在统计从点阵左上角到 $y=x$ 的所有路径经过的点的 $\operatorname{occ}$ 乘积的和。贡献分布在 $y=x$ 上不好算，考虑将路径全部反向统计到左上角 $(1, n)$。

若将 $f$ 刷表出来，一个等价类 $a$ 在图上出现的若干位置 $G(a)$ 全部相等，所以考虑将等价类之间的包含关系建出一张 DAG 倒拓扑序处理等价类，得到了一个常数略小的 $O(n^{2})$ 做法。

发现我们的复杂度瓶颈在于等价类内部的 $f$ 转移，而对于不同等价类之间的转移需要用的只有等价类的上边界和左边界。

考虑分治求每个等价类代表的阶梯图的左边界和上边界，每次我们选择长宽中更长的一部分折半，根据下面的部分切出一条平行于另一边的线，将所求的 $f$ 数组划分为三个部分，两个阶梯状的子图递归解决。

![](https://cdn.luogu.com.cn/upload/image_hosting/6m525kdm.png)

处理完子问题后，对于中间的矩形 $(a, b)-(c, d)$ 部分，我们得到其右边界和下边界的 $f$，我们希望快速得到上边界和左边界。设 $k$ 为等价类 $a$ 的出现次数。

下边界转移到上边界：

$$f_{b, y}\binom{y-x+b-a}{b-a}k^{y-x+b-a}\to f_{a, x}(x\le y)$$

展开：

$$f_{b, y}\frac{(y-x+b-a)!}{(b-a)!(y-x)!}k^{y-x+b-a}\to f_{a, x}$$

不难发现这是个减法卷积的形式。

下边界转移到左边界：

$$f_{b, y}\binom {x-a+d-y}{x-a}k^{x-a+d-y}\to f_{x, b}$$

$$f_{b, y}\frac {(x-a+d-y)!}{(x-a)!(d-y)!}k^{x-a+d-y}\to f_{x, b}$$

同样也可以减法卷积，右边界的转移同理。

于是一层分治 + 4 次卷积即可，卷积的长度不超过等价类行数和列数和（不超过 $2n$），复杂度 $O(n\log ^2 n)$。

实现细节：阶乘和 $k$ 的幂的处理要到两倍，递归后得到的数组其实是右边界右边一列 + 下边界下一列，注意 +1 之类的边界问题。

[Code](https://loj.ac/s/1932443)

我的写法常数相当大，通过预处理单位根的幂可以在 2s 内极限在 lg 过。[Code2](https://loj.ac/s/1932546)。



---

## 作者：FZzzz (赞：0)

建出 SAM，记点 $u$ 中包含 $[L_u,R_u]$ 长度的串，endpos 集大小为 $c_u$。在 SAM 的 DAG 结构中，我们称 $c_u=c_v$ 的边 $(u,v)$ 为“关键边”。

以下不加证明地给出一些结论：
> 每个点至多有一条关键的入边和一条关键的出边，且这条出边一定是这个点唯一的出边。所以关键边形成了若干条链（以下所说的所有“链”都指这样的链），剩下的边的起点都是某条链的链尾。

> 对于点 $v$，所有连向它的点 $u$ 的 $[L_u,R_u]$ 互不相交，且并集为 $[L_v-1,R_v-1]$。且若 $(u,v)$ 是关键边，则 $R_u=R_v-1$。

> 对于某条链的链尾 $u$，$u$ 包含的所有串都是某个 startpos 等价类中的最长串，故所有这样的 $u$ 的 $[L_u,R_u]$ 的长度之和为 $O(n)$。

有这些基本就够了，接下来我们回到题目。首先把删字符改为加字符。考虑当前串在 SAM 上所属的节点 $u$。在右侧加字符就相当于在自动机上走一步；在左侧加字符就是，若当前长度等于 $R_u$，则走到 $u$ 在 link 树上的某个儿子，否则不动。

对于一条链，记它的长度为 $m$，第 $i$ 个节点是 $s_i$。考虑走出和走入这条链时的状态。走出它时要么是在 $s_m$ 处，长度为 $[L_{s_m},R_{s_m}]$，然后在右侧加字符；要么是在某个 $s_i$ 处且长度为 $R_{s_i}$，然后在左侧加字符。走入它时如果是走到 $s_i$，则长度要么是 $L_{s_i}$，要么是 $[L_{s_i},L_{s_{i-1}}]$（若 $i=1$ 则是 $[L_{s_1},R_{s_1}]$）。所以走入和走出都是 $m+R_{s_m}-L_{s_m}+1$ 种情况。

如果对于每种走入的情况，我们已经知道了所有方案中已经产生的贡献之和，现在我们欲对每种走出的情况求出这个值。画一个表格，第 $i$ 列第 $j$ 行表示当前在 $s_i$ 节点，长度为 $R_{s_i}-j+1$，那么它会长成一个阶梯状。

比如，若 $m=4$，$[L_{s_1},R_{s_1}]=[3,3]$，$[L_{s_2},R_{s_1}]=[2,4]$，$[L_{s_3},R_{s_3}]=[2,5]$，$[L_{s_4},R_{s_4}]=[3,6]$，则它会长成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/r2nfadkg.png)

在这个图中，在左侧加字符就是往上走，在右侧加字符就是往右走。相当于从左下轮廓线的某个位置以某个初始贡献走入，每一步可以往右或往上走，走过一个格子会把贡献乘上 $c_{s_m}$，要求的是对于右上轮廓线的每个位置，从这个位置走出的所有方案的贡献之和。

这可以用分治解决。用这样两条线把这个阶梯分成三个部分，左上和右下分治下去解决，然后右上部分的贡献可以用四次 FFT 计算。

至此我们得到了一个可以解决原问题的完整算法：按 $c$ 值从大到小处理每条链，对它运行上面的分治算法，然后把结果计入到其他一些链的初始输入中。处理每条链的时间复杂度是 $O((m+R_{s_{m}}-L_{s_m})\log^2n)$，而所有 $R_{s_m}-L_{s_m}$ 之和为 $O(n)$，故总时间复杂度为 $O(n\log^2n)$。

------------
对 OI 界前沿（？）科技有一些了解的选手可能已经看出，上面的阶梯与 xtq 23 年集训队论文《一类基础子串数据结构》中描述的结构极为相似。事实上，上文中的一条链就是一个基本子串结构。如果我们直接把题目中的过程画在平面上，然后考察它经过了哪些基本子串结构，我们可以更加直观快捷地得到一个与上述做法等价的算法。

另外，如果我们把每条链缩起来，就可以得到一个类似于 xyx 20 年集训队论文《浅谈压缩后缀自动机》中描述的压缩后缀自动机的结构，在此基础上加上走 link 树边的转移就是文中描述的对称压缩后缀自动机。

对压缩 SAM 和基本子串结构有兴趣的读者可以自行阅读上述两篇论文，本文开头的几个结论也可以在论文中找到等价的形式及其证明。

~~然而我其实没有今年的论文啊，有没有老哥给我一份。~~

这篇题解实际上就是用普通的 SAM 强行凑出了上述两种字符串数据结构 ~~重复造轮子~~，对这两种数据结构不了解的选手在需要用到它们的问题（一般需要同时处理前缀和后缀关系）中可以参考这篇题解中的处理方式。但是有精力的话还是建议直接把它们学了。

------------
最后附上代码，似乎是目前洛谷和 loj 的最短解。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const ll mod=998244353,g=3,invg=332748118;
ll ksm(ll a,ll b){
	ll c=1;
	while(b){
		if(b%2==1) c=c*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return c;
}
using poly=vector<ll>;
vector<int> rev;
vector<ll> w,w2;
ll invn;
void init(int n){
	rev.resize(n);
	for(int i=1;i<n;i++) rev[i]=rev[i>>1]>>1|(i&1?n>>1:0);
	w.resize(n);
	for(int i=1;i<n;i*=2){
		ll wn=ksm(g,(mod-1)/(i*2));
		w[i]=1;
		for(int j=1;j<i;j++) w[i+j]=w[i+j-1]*wn%mod;
	}
	w2.resize(n);
	for(int i=1;i<n;i*=2){
		ll wn=ksm(invg,(mod-1)/(i*2));
		w2[i]=1;
		for(int j=1;j<i;j++) w2[i+j]=w2[i+j-1]*wn%mod;
	}
	invn=ksm(n,mod-2);
}
poly FFT(poly F,bool flag){
	int n=F.size();
	if(n!=(int)rev.size()) init(n);
	for(int i=0;i<n;i++) if(i<rev[i]) swap(F[i],F[rev[i]]);
	for(int i=1;i<n;i*=2) for(int j=0;j<n;j+=i*2)
		for(int k=j;k<j+i;k++){
			ll t=F[k+i]*(flag?w:w2)[i+k-j]%mod;
			F[k+i]=(F[k]-t+mod)%mod;
			F[k]=(F[k]+t)%mod;
		}
	if(!flag) for(int i=0;i<n;i++) F[i]=F[i]*invn%mod;
	return F;
}
poly operator *(poly A,poly B){
	int n=A.size(),m=B.size(),len=1;
	while(len<n+m-1) len*=2;
	A.resize(len);
	B.resize(len);
	A=FFT(A,1);
	B=FFT(B,1);
	for(int i=0;i<len;i++) A[i]=A[i]*B[i]%mod;
	A=FFT(A,0);
	A.resize(n+m-1);
	return A;
}
const int maxn=1e5+5;
int n;
char s[maxn];
int sz=1,lst=1,len[maxn*2],fa[maxn*2],nxt[maxn*2][26];
vector<int> e[maxn*2];
void extend(int c){
	int u=++sz;
	len[u]=len[lst]+1;
	int p=lst;
	while(p&&!nxt[p][c]){
		nxt[p][c]=u;
		p=fa[p];
	}
	if(!p) fa[u]=1;
	else{
		int q=nxt[p][c];
		if(len[q]==len[p]+1) fa[u]=q;
		else{
			int v=++sz;
			len[v]=len[p]+1;
			fa[v]=fa[q];
			memcpy(nxt[v],nxt[q],sizeof(nxt[v]));
			while(p&&nxt[p][c]==q){
				nxt[p][c]=v;
				p=fa[p];
			}
			fa[u]=fa[q]=v;
		}
	}
	lst=u;
}
int cnt[maxn*2];
void dfs(int u){
	for(int v:e[u]){
		dfs(v);
		cnt[u]+=cnt[v];
	}
}
int pre[maxn*2];
ll fac[maxn*2],ifac[maxn*2];
ll inv(int x){
	return ifac[x]*fac[x-1]%mod;
}
poly a[maxn*2];
ll b[maxn*2];
pair<poly,poly> solve(vector<poly> a,poly b,int c){
	int n=a.size();
	if(n==1){
		if(!a[0].size()) return {{},{b[0]}};
		int m=a[0].size();
		a[0][0]=(a[0][0]+b[0])%mod;
		for(int i=1;i<m;i++) a[0][i]=(a[0][i]*ksm(inv(c),i)%mod+a[0][i-1])%mod;
		for(int i=0;i<m;i++) a[0][i]=a[0][i]*ksm(c,i+1)%mod;
		return {a[0],{a[0].back()}};
	}
	int m=n/2;
	auto p=solve(vector<poly>(a.begin(),a.begin()+m),poly(b.begin(),b.begin()+m),c);
	poly d=p.first,e=p.second;
	int s=d.size();
	if(!s){
		p=solve(vector<poly>(a.begin()+m,a.end()),poly(b.begin()+m,b.end()),c);
		for(ll i:p.second) e.push_back(i);
		return {p.first,e};
	}
	poly F(s),G(s+n-m-1);
	for(int i=0;i<s;i++) F[i]=d[i]*ifac[s-i-1]%mod;
	for(int i=0;i<s+n-m-1;i++) G[i]=fac[i]*ksm(c,i+1)%mod;
	F=F*G;
	e.resize(n);
	for(int i=0;i<n-m;i++) e[m+i]=F[s+i-1]*ifac[i]%mod;
	F.resize(s);
	G.resize(s);
	for(int i=0;i<s;i++) F[i]=d[i];
	for(int i=0;i<s;i++) G[i]=fac[n-m+i-1]*ifac[i]%mod*ksm(c,n-m+i)%mod;
	F=F*G;
	for(int i=0;i<s;i++) d[i]=F[i]*ifac[n-m-1]%mod;
	p=solve(vector<poly>(a.begin()+m,a.end()),poly(b.begin()+m,b.end()),c);
	poly d2=p.first,e2=p.second;
	F.resize(n-m);
	G.resize(s+n-m-1);
	for(int i=0;i<n-m;i++) F[i]=e2[i]*ifac[n-m-i-1]%mod;
	for(int i=0;i<s+n-m-1;i++) G[i]=fac[i]*ksm(c,i+1)%mod;
	F=F*G;
	for(int i=0;i<s;i++) d[i]=(d[i]+F[n-m+i-1]*ifac[i]%mod)%mod;
	F.resize(n-m);
	G.resize(n-m);
	for(int i=0;i<n-m;i++) F[i]=e2[i];
	for(int i=0;i<n-m;i++) G[i]=fac[s+i-1]*ifac[i]%mod*ksm(c,s+i)%mod;
	F=F*G;
	for(int i=0;i<n-m;i++) e[m+i]=(e[m+i]+F[i]*ifac[s-1]%mod)%mod;
	for(ll i:d) d2.push_back(i);
	return {d2,e};
}
void solve(int u){
	vector<int> s;
	while(u){
		s.push_back(u);
		u=pre[u];
	}
	reverse(s.begin(),s.end());
	u=s.back();
	int n=s.size();
	vector<poly> a2(n);
	poly b2(n);
	for(int i=0;i<n;i++){
		a2[i]=a[s[i]];
		b2[i]=b[s[i]];
	}
	auto p=solve(a2,b2,cnt[u]);
	poly c=p.first,d=p.second;
	for(int i=0;i<26;i++){
		int v=nxt[u][i];
		if(!v) continue;
		for(int j=0;j<(int)c.size();j++)
			a[v][j+len[fa[u]]-len[fa[v]]+1]=c[j];
	}
	for(int i=0;i<n;i++)
		for(int v:e[s[i]]) b[v]=(b[v]+d[i])%mod;
	if(cnt[u]==1) printf("%lld\n",c.back());
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		extend(s[i]-'a');
		cnt[lst]=1;
	}
	for(int i=2;i<=sz;i++) e[fa[i]].push_back(i);
	dfs(1);
	vector<int> s;
	for(int i=2;i<=sz;i++){
		int c=0;
		while(c<26&&cnt[nxt[i][c]]!=cnt[i]) c++;
		if(c==26) s.push_back(i);
		else pre[nxt[i][c]]=i;
	}
	sort(s.begin(),s.end(),[](int x,int y){
		return cnt[x]>cnt[y];
	});
	for(int i=2;i<=sz;i++)
		a[i].resize((pre[i]?len[fa[pre[i]]]+1:len[i])-len[fa[i]]);
	for(int i=0;i<26;i++) if(nxt[1][i]) a[nxt[1][i]][0]=1;
	fac[0]=1;
	for(int i=1;i<=n*2;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n*2]=ksm(fac[n*2],mod-2);
	for(int i=n*2-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
	for(int u:s) solve(u);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

