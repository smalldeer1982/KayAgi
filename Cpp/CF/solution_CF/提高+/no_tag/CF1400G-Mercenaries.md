# Mercenaries

## 题目描述

Polycarp plays a (yet another!) strategic computer game. In this game, he leads an army of mercenaries.

Polycarp wants to gather his army for a quest. There are $ n $ mercenaries for hire, and the army should consist of some subset of them.

The $ i $ -th mercenary can be chosen if the resulting number of chosen mercenaries is not less than $ l_i $ (otherwise he deems the quest to be doomed) and not greater than $ r_i $ (he doesn't want to share the trophies with too many other mercenaries). Furthermore, $ m $ pairs of mercenaries hate each other and cannot be chosen for the same quest.

How many non-empty subsets does Polycarp need to consider? In other words, calculate the number of non-empty subsets of mercenaries such that the size of this subset belongs to $ [l_i, r_i] $ for each chosen mercenary, and there are no two mercenaries in the subset that hate each other.

The answer may be large, so calculate it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3 0
1 1
2 3
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1
1 1
2 3
1 3
2 3```

### 输出

```
2```

# 题解

## 作者：tzc_wk (赞：17)

upd on 2021.7.21：修了个 typo

先祭一个，div2 打过的最高纪录（要是我拿小号打就是 official rk 3）

![](https://cdn.luogu.com.cn/upload/image_hosting/p2hjl8q5.png)

~~我现场竟然 A 了这道题，incredible！~~

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1400G) & [Codeforces 题面传送门](https://codeforces.ml/contest/1400/problem/G)

楼下的大佬用了一种类似于图论的做法，然鹅我不会/kk，wtcl

注意到 $m$ 的数据范围非常小，所以我们不妨用**容斥原理**解决这个这个问题。

通俗地讲，就是拿总方案数减去有限制不满足的情况就是答案。而计算不合法的情况，可以把**有1条限制不满足的方案数**加起来。但是这样会算重，故还要扣掉**2条限制不满足的方案数**，这样会导致**3条限制不满足的情况被多减了一遍**，以此类推。

具体地讲，假设所有限制组成的集合为 $S$，那么总方案数的表达式就是：

$$ans=\sum_{T \subseteq S}(-1)^{|T|}\times cnt(T)$$

其中 $cnt(T)$ 表示集合 $T$ 里的限制都不满足的情况数。

这样子枚举是 $\mathcal O(2^m)$ 的，故接下来我们的任务就是计算 $cnt(T)$。

先从简单情况入手——计算**总方案数**，即，不考虑限制的情况下的方案数。我们枚举**选中的集合的大小** $x$，那么 $l_i \leq x \leq r_i$ 的 $i$ 都可以选入集合。我们有假设 $s_x$ 个符合条件的数，那么，用组合数可以计算得，这种情况对答案的贡献为 $\dbinom{s_x}{x}$。

接下来再考虑加上限制的情况，很明显，**与这些限制相关的元素必须都被选中**，假设有 $c$ 个这样的元素。我们还是枚举**选中的集合的大小** $x$，由于这 $c$ 个元素无论如何都是要选中的，故 $x$ 必须属于这 $c$ 个区间的**交集**，设其为 $[L,R]$。由于 $s_x$ 个可选的数中有 $c$ 个已经确定下来了，故这一部分对答案的贡献为 $\dbinom{s_x-c}{x-c}$。

这样我们就有 $cnt(T)=\sum\limits_{x=L}^R\dbinom{s_x-c}{x-c}$

暴力计算肯定会 T，不过注意到 $c \in [0,2m]$，故可以对**每个 $c$ 都计算跑前缀和**，这样可以 $\mathcal O(1)$ 计算出答案。

然后用上面的表达式计算出答案就可以了。

怎样计算 $s_x$，最好的方法当然是**差分**。不过线段树、BIT 亦可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define pb			push_back
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define y1			y1010101010101
#define y0			y0101010101010
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-') neg=-1;
		c=getchar();
	}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x*neg;
}
int n=read(),m=read();
int cf[300005],l[300005],r[300005],cnt[300005],a[25],b[25];
const int MOD=998244353;
int fac[300005],inv[300005];
int qpow(int x,int e){
	int ans=1;while(e){if(e&1) ans=ans*x%MOD;x=x*x%MOD;e>>=1;} return ans;
}
inline void prework(){
	fac[0]=1;for(int i=1;i<=300000;i++) fac[i]=fac[i-1]*i%MOD;
	for(int i=0;i<=300000;i++) inv[i]=qpow(fac[i],MOD-2);
}
int sum[300005][45];
inline int getc(int x,int y){
	if(x<y||x<0||y<0) return 0;
	return fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}
signed main(){
	prework();
	fz(i,1,n){
		l[i]=read(),r[i]=read();
		cf[l[i]]++;cf[r[i]+1]--;
	}
	int num=0;
	fz(i,1,n){num+=cf[i];cnt[i]=num;}
	fz(i,1,m) a[i]=read(),b[i]=read();
	fz(i,0,40){
		fz(j,1,n){
			sum[j][i]=(sum[j-1][i]+getc(cnt[j]-i,j-i))%MOD;
		}
	}
//	cout<<sum[3][1]<<" "<<sum[1][1]<<endl;
	int ans=0;
	for(int i=0;i<(1<<m);i++){
		int _l=1,_r=n;
		set<int> st;
		fz(j,1,m){
			if(i>>(j-1)&1){
				_l=max(_l,l[a[j]]);_r=min(_r,r[a[j]]);st.insert(a[j]);
				_l=max(_l,l[b[j]]);_r=min(_r,r[b[j]]);st.insert(b[j]);
			}
		}
		if(_l>_r) continue;
		int calc=(sum[_r][st.size()]-sum[_l-1][st.size()]+MOD)%MOD;
		int cnt1=__builtin_popcount(i);
		if(cnt1&1) ans=(ans-calc+MOD)%MOD;
		else ans=(ans+calc)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
```

最后来总结一下这题为什么可以想到容斥原理：对于任意一条限制，若要满足它，有 **$3$ 种可能的情况**（选 A、选 B、都不选）；而要不满足，只有 **$1$ 种情况**（都选）。

故对于这类数据范围很小，而从**正面计算比较困难**的题目，可以想到容斥原理，用反面计算。

---

## 作者：MspAInt (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/CF1400G)

先考虑 $m=0$，预处理出准备拿 $i$ 个人时最多能拿多少个人 $cnt_i$，则答案是 $\sum_{i=1}^{n}{{cnt_i}\choose{i}}$。这个是多次修改最后查询，差分即可。

再考虑一般情况，$m\le20$ 明示了 $2^m$，考虑容斥：枚举限制的子集，把选择了它们的方案数减去。我们设 $s_{i,j}$ 表示选 $i$ 个人，其中有 $j$ 个被限制人必须选的方案数，显然 $s_{i,j}={{cnt_i-j}\choose{i-j}}$。然后总人数要在这些限制人的区间的交里，所以对 $s$ 做一下前缀和就可以求得了。

Code:

```
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10,mod=998244353;
int n,m,l[N],r[N],s[N][50],ans,f[N],a[N],b[N],inv[N];

int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		y>>=1;x=1ll*x*x%mod;
	}
	return ret;
}
int C(int x,int y){
	if(x<y||x<0||y<0)return 0;
	return 1ll*f[x]*inv[x-y]%mod*inv[y]%mod;
}

signed main(){
	scanf("%d%d",&n,&m);
	f[0]=1;inv[0]=1;
	for(int i=1;i<=n;i++)f[i]=1ll*f[i-1]*i%mod,inv[i]=qpow(f[i],mod-2);
	for(int i=1;i<=n;i++)scanf("%d%d",&l[i],&r[i]);
	for(int i=1;i<=n;i++)s[l[i]][0]++,s[r[i]+1][0]--;
	for(int i=1;i<=n;i++)s[i][0]+=s[i-1][0];
	for(int i=1;i<=n;i++)
		for(int j=m*2;j>=0;j--)s[i][j]=(s[i-1][j]+C(s[i][0]-j,i-j))%mod;
	for(int i=1;i<=m;i++)scanf("%d%d",&a[i],&b[i]);
	for(int i=0;i<(1<<m);i++){
		set<int>t;
		int L,R;L=1;R=n;
		for(int j=1;j<=m;j++)if(i>>j-1&1){
			L=max(L,l[a[j]]);L=max(L,l[b[j]]);
			R=min(R,r[a[j]]);R=min(R,r[b[j]]);
			t.insert(a[j]);t.insert(b[j]);
		}
		if(L>R)continue;
		int cnt=t.size();
		if(__builtin_popcount(i)&1)ans=((ans-s[R][cnt]+s[L-1][cnt])%mod+mod)%mod;
		else ans=((ans+s[R][cnt]-s[L-1][cnt])%mod+mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
} 
```

[record](https://www.luogu.com.cn/record/153500644)

---

## 作者：ZigZagKmp (赞：6)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)
## 题意简述
有$n$个人和$m$对敌对关系，每一个人有一个条件区间$[l_i,r_i]$。

定义一个合法的选择$\{S\}$，当且仅当对于$\{S\}$中的所有人$i$，$l_i\le |S| \le r_i$，且$\{S\}$中所有人互不敌对。

求有多少种合法的选择，答案对$998244353$取模。

$1\le n\le 3\times 10^5$，$0\le m\le \min\{20,\frac{n(n-1)}{2}\}$，$1\le l_i\le r_i\le n$。
### 算法考察
计数，容斥，组合数，前缀和
## 算法分析
看到$m$的范围很小，不难想到容斥。

容斥敌对关系的集合，在这个集合内的敌对关系的人必选，其余人任意，乘上容斥系数即为最后答案。

现在我们要解决的问题转变为：一部分人必选，且最后选择的总人数符合要求的方案数。

先考虑特殊情况，如果没有人必选，那么我们枚举最后选择的总人数$i$，枚举每一个人讨论是否可以被选择，假设有$x_i$个人可以被选择，则答案为$C_{x_i}^i$，这个做法可以通过前缀和优化$O(1)$求出。

再考虑一般情况，假设有$a$个人必选，不难发现最后可能合法的选择大小一定是这$a$个人条件区间的交集，若干个区间的交集最多一个区间，因此我们枚举再这个区间内枚举最后选择的总人数$i$，假设总共有$x_i$个人可以被选择，则答案为$C_{x_i-a}^{i-a}$。我们发现$x_i$是一个固定的值，而因为敌对关系最多$20$对，因此最多有$40$个人可能会必选，因此我们可以对每一个$a$预处理组合数，再使用前缀和优化，$O(1)$求出答案。

本算法时间复杂度为$O(mn+2^m)$。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define mod 998244353
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int ksm(int B,int P,int Mod){int ret=1;while(P){if(P&1)ret=1ll*ret*B%Mod;B=1ll*B*B%Mod;P>>=1;}return ret;}
struct node{
	int l,r;
}a[maxn];
int d1[25],d2[25];
int n,m;
int ans;
int frac[maxn],frinv[maxn];
int C(int x,int y){//求组合数，注意可能出现x<0,y<0的情况
	if(x<y)return 0;
	if(x<0||y<0)return 0;
	return frac[x]*frinv[y]%mod*frinv[x-y]%mod;
}
map<int,int>mp;
int siz[1<<21],LG[1<<21];
int s[maxn][45];
int calc(int S){
	mp.clear(); 
	int l=1,r=n;
	int ai;
	for(int ss=S;ss;ss-=(ss&(-ss))){
		int x=LG[(ss&(-ss))]+1;
		mp[d1[x]]=1;mp[d2[x]]=1;
		l=max(l,max(a[d1[x]].l,a[d2[x]].l));
		r=min(r,min(a[d1[x]].r,a[d2[x]].r));
	}
	ai=mp.size();//求区间和必选人数
	if(l>r)return 0;
	else return s[r][ai]-s[l-1][ai];
}
signed main(){
	read(n);read(m);
	frac[0]=1;
	for(int i=1;i<=n;i++)frac[i]=1ll*frac[i-1]*i%mod;
	frinv[n]=ksm(frac[n],mod-2,mod);
	for(int i=n-1;~i;i--)frinv[i]=1ll*frinv[i+1]*(i+1)%mod;
	LG[1]=0;
	for(int i=2;i<(1<<20);i++)LG[i]=LG[i>>1]+1;
	siz[0]=1;
	for(int i=1;i<(1<<20);i++)siz[i]=-siz[i-(i&(-i))];
	//一堆预处理，frac,frinv用于快速求组合数，siz求容斥系数，LG求log向下取整
	for(int i=1;i<=n;i++)read(a[i].l),read(a[i].r);
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		d1[i]=x;d2[i]=y;
	}
	for(int i=1;i<=n;i++){
		s[a[i].l][0]++;s[a[i].r+1][0]--;
	}
	for(int i=1;i<=n;i++)s[i][0]+=s[i-1][0];//一次前缀和求出所有x_i
	for(int i=1;i<=n;i++){
		for(int j=1;j<=40;j++){
			s[i][j]=C(s[i][0]-j,i-j);//计算所有答案
		}
		s[i][0]=C(s[i][0],i);
	}
	for(int j=0;j<=40;j++){
		for(int i=1;i<=n;i++){
			s[i][j]=(s[i-1][j]+s[i][j])%mod;//再一次前缀和求出答案
		}
	}
	for(int i=0;i<(1<<20);i++){
		ans=(ans+siz[i]*calc(i))%mod;//容斥计算
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}

```

---

## 作者：Suiseiseki (赞：4)

官方题解太神了没看懂（其实就是菜qwq）。

下面讲一下我的思路。

如果$m=0$，那么我们可以枚举最后选多少个佣兵，然后一个简单的组合数解决问题。

那么我们发现$m$非常小，这提示我们可以把所有和限制搭上边的佣兵单独拎出来算，现在我们需要知道的就是有限制的佣兵中钦定有些佣兵不可以选，另一些选出若干个的方案数，这很明显应当用状压 DP 解决，然而一个尴尬的事情发生了，$m\leq 20$意味着最多会有$40$个有限制的佣兵，$2^{40}$妥妥地爆掉了。

似乎陷入了绝境……

换一种思维方式，考虑到如果一个佣兵有限制，但是能够限制他的佣兵在我们枚举的选取的总人数中一个都不符合要求，那么这个佣兵可以暂时地归类到普通佣兵里，这启示我们可以不压缩佣兵，而选择压缩佣兵之间的限制，这个显然是可以做的。

那么，这一题就做完了，最后形式化地描述一下算法的思路流程，先预处理出$2^m$个限制的选取集合中选取佣兵的个数为$0$~$m$次的方案数，然后枚举我们选多少个佣兵，将所有符合条件且有限制的佣兵统计出来，并且统计出它们之间的连边，如果一个佣兵没有佣兵与他相连，就将其加到普通佣兵的个数中去，时间复杂度$O(2^m\cdot m^2+nm)$。

代码：（写得貌似很丑）[My Blog](https://www.cnblogs.com/withhope/p/13568562.html)

---

## 作者：bruhify (赞：1)

做法似乎和现有题解都不一样。不用容斥。

先考虑 $m=0$ 时怎么做。直接枚举最终选了多少个元素，前缀和预处理每种可能下的合法元素数量 $cnt_i$，则答案为 $\sum\limits_{i=1}^{n} \binom{cnt_i}{i}$。

注意到 $m$ 很小，所以考虑把限制涉及到的元素全都拉出来单独建成一个图，剩下的点套用上述做法，最后将两个背包合并即可。问题转化成了对于每个 $k$ 和每种最终元素个数 $c$，求一般图上有多少个由合法点组成的，大小为 $k$ 的独立集。这个可以状压 dp 做到对于单个 $c$ 的复杂度为 $O(2^{siz})$，$siz$ 为图上点数。

当然不能对于每个 $c \in [1,n]$ 都跑一遍状压。你不难发现对于有限制的点这个集合，绝大多数 $c$ 的取值都对应了同一种点的合法状态。本质不同的 $c$ 只有 $\leq 4m$ 种，所以这部分的复杂度为 $O(m2^{siz})$。但是你发现 $siz$ 最大可以达到 $2m$，这个做法就寄了。吗？

由于这个图中每个连通块是独立的，可以对于每个连通块分别算状压 dp，将最终的结果背包合并。而对于每个连通块均有 $|V| \leq |E|+1$，总共的状压计算量为 $\sum 2^{V_i} \leq \sum 2^{E_i+1} \leq 2^{m+1}$，复杂度正确。

最终复杂度 $O(m2^m+nm+\operatorname{poly}(m))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;

int n,m,maxs,csiz;

int L[300005],R[300005];

map<pair<int,int>,bool> E;

int fa[300005],sub[300005];

int get(int x) {
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}

void merge(int u,int v) {
	u=get(u),v=get(v);
	if(sub[u]<sub[v]) swap(u,v);
	if(u!=v) fa[v]=u,sub[u]+=sub[v];
}

int fac[300005],ifac[300005];

int pow_mod(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=1LL*res*a%mod;
		a=1LL*a*a%mod;
		b>>=1;
	}
	return res;
}

int C(int a,int b) {
	if(a<0 || b<0 || a<b) return 0;
	return 1LL*fac[a]*ifac[b]%mod*ifac[a-b]%mod;
}

int cnt[300005];

int f[85][42],g[42];

int dp[(1<<21)+5];

vector<int> vc[42];

int ans=0;

inline void add(int &a,int b) {
	a=(a+b>=mod)?a+b-mod:a+b;
}

vector<int> cti;

int G[22],F[(1<<21)];

int lowbit(int x) {
	return x&-x;
}

void calc(const vector<int> &v,int cur) {
	int siz=v.size();
	memset(G,0,sizeof(int)*siz),memset(g,0,sizeof(int)*siz);
	for(int i=0;i<siz;i++) {
		for(int j=i+1;j<siz;j++) {
			int t=E.count({v[i],v[j]}) || E.count({v[j],v[i]});
			G[i]|=t<<j,G[j]|=t<<i;
		}
	}
	for(int i=1;i<(1<<siz);i++) F[i]=F[i^lowbit(i)]|G[31^__builtin_clz(lowbit(i))];
	memset(dp,0,sizeof(int)*(1<<siz));
	dp[0]=1;
	for(int i=0;i<siz;i++) {
		if(cur<L[v[i]] || R[v[i]]<cur) continue;
		for(int j=0;j<(1<<i);j++) {
			if((F[j]>>i)&1) continue;
			add(dp[j|(1<<i)],dp[j]);
		}
	}
	for(int i=0;i<(1<<siz);i++) add(g[__builtin_popcount(i)],dp[i]);
}

int main() {
	scanf("%d %d",&n,&m);
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1LL*fac[i-1]*i%mod;
	ifac[n]=pow_mod(fac[n],mod-2);
	for(int i=n-1;i>=0;i--) ifac[i]=1LL*ifac[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++) scanf("%d %d",&L[i],&R[i]),fa[i]=i,sub[i]=1;
	for(int i=1;i<=m;i++) {
		int a,b;
		scanf("%d %d",&a,&b);
		E[{a,b}]=1,merge(a,b);
		cti.push_back(L[a]),cti.push_back(R[a]+1),cti.push_back(L[b]),cti.push_back(R[b]+1);
	}
	cti.push_back(0),cti.push_back(n),sort(cti.begin(),cti.end()),cti.erase(unique(cti.begin(),cti.end()),cti.end()),csiz=cti.size();
	for(int i=1;i<=n;i++) {
		if(get(i)==i && sub[i]==1) cnt[L[i]]++,cnt[R[i]+1]--;
		else vc[get(i)].push_back(i);
	}
	for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
	for(int T=0;T<csiz;T++) f[T][0]=1;
	for(int i=1;i<=n;i++) {
		if(vc[i].empty()) continue;
		int siz=vc[i].size();
		for(int T=0;T<csiz;T++) {
			calc(vc[i],cti[T]);
			for(int j=maxs;j>=0;j--) {
				if(f[T][j]==0) continue;
				for(int k=siz;k>=1;k--) add(f[T][j+k],1LL*f[T][j]*g[k]%mod);
			}
		}
		maxs+=siz;
	}
	int pos=0;
	for(int i=1;i<=n;i++) {
		while(pos+1<csiz && cti[pos+1]<=i) pos++;
		for(int j=0;j<=maxs && j<=i;j++) add(ans,1LL*f[pos][j]*C(cnt[i],i-j)%mod);
	}
	printf("%d",ans);
	return 0;
}

```


---

## 作者：JackMerryYoung (赞：0)

# 前言

跳题。

# 正文

考虑一下没有冲突的版本，发现是个简单容斥。正难则反，我们考虑枚举不合法的方案，这里将其视作一个集合即可。为了不重复计数，我们考虑枚举有 $i$ 个人的集合，枚举有 $j$ 个人是不合法的，上界是有 $i$ 个人的集合的最多不合法的人个数（拿个线段树维护一下即可）。

现在考虑有冲突的版本。我们考虑单纯的容斥。发现冲突数目比较少，启示我们可以状压。我们可以考虑把每个状态都算出来，这里说一下状态设计：每一个状态中的第 $j$ 位为 $1$ 表示必须满足冲突的人同时出现。这个东西可以使用类似前面的思路的 $\mathcal{O}(N \cdot M)$ 预处理。

然后容斥出了点小问题：我们发现如果删了敌对者为奇数的情况，那么显然会被多删，因此要加上去敌对者为偶数的情况。注意预处理组合数（不然会超时）。

# 代码

``` cpp
#include <bits/stdc++.h>
#define ll long long
#define MOD (998244353)
using namespace std;

ll N, M, ans; 
ll l[300005], r[300005], a[300005], b[300005], fac[300005], inv[300005];
ll fail[300005], sum[300005][45];

#define lson ((p << 1) | 0)
#define rson ((p << 1) | 1)
#define mid  ((l + r) >> 1)

struct SegmentTree {
	ll sum, lazytag_sum;
} tree[1200005];

void push_down(ll p, ll l, ll r)
{
	tree[lson].lazytag_sum += tree[p].lazytag_sum;
	tree[rson].lazytag_sum += tree[p].lazytag_sum;
	tree[lson].sum += (mid - (l + 0) + 1) * tree[p].lazytag_sum;
	tree[rson].sum += (r - (mid + 1) + 1) * tree[p].lazytag_sum;
	tree[p].lazytag_sum = 0;
}

void merge(ll p)
{
	tree[p].sum = tree[lson].sum + tree[rson].sum;
}

void modify_add(ll l, ll r, ll lll, ll rrr, ll val, ll p)
{
	if(lll <= l && rrr >= r)
	{
		tree[p].lazytag_sum += val;
		tree[p].sum += val * (r - l + 1);
		return;
	}
	
	if(tree[p].lazytag_sum) push_down(p, l, r);
	if(lll <= mid + 0) modify_add(l, mid + 0, lll, rrr, val, lson);
	if(rrr >= mid + 1) modify_add(mid + 1, r, lll, rrr, val, rson);
	merge(p);
}

ll query_sum(ll l, ll r, ll x, ll p)
{
	if(l == r)
		return tree[p].sum;
		
	if(tree[p].lazytag_sum) push_down(p, l, r);
	if(x <= mid + 0) return query_sum(l, mid + 0, x, lson);
	if(x >= mid + 1) return query_sum(mid + 1, r, x, rson);
}

ll qpow(ll a, ll k)
{
	if(k == 1) return a % MOD;
	ll tmp = qpow(a, k >> 1) % MOD;
	if(k & 1) return (((tmp * tmp) % MOD) * a) % MOD;
	else return (tmp * tmp) % MOD;
}

ll C(ll m, ll n)
{
	if(m < n || m < 0 || n < 0) return 0;
	else return (((fac[m] * inv[n]) % MOD) * inv[m - n]) % MOD;
}

signed main()
{
	scanf("%lld %lld", &N, &M);
	fac[0] = 1;
	for(ll i = 1; i <= 300000; ++ i)
		fac[i] = (fac[i - 1] * i) % MOD;
		
	for(ll i = 0; i <= 300000; ++ i)
		inv[i] = qpow(fac[i], MOD - 2) % MOD;
		
	for(ll i = 1; i <= N; ++ i)
		scanf("%lld %lld", &l[i], &r[i]), modify_add(1, N, l[i], r[i], 1, 1);
		
	for(ll i = 1; i <= N; ++ i)
		fail[i] = query_sum(1, N, i, 1); 
	
	for(ll i = 1; i <= M; ++ i)
		scanf("%lld %lld", &a[i], &b[i]);
	
	for(ll i = 0; i <= 40; ++ i)
		for(ll j = 1; j <= N; ++ j)
			sum[j][i] = (sum[j - 1][i] + C(fail[j] - i, j - i)) % MOD;
	
	set<ll> uni;
	for(ll i = 0; i < (1 << M); ++ i)
	{
		ll maxl = 1, minr = N;
		uni.clear();
		for(ll j = 1; j <= M; ++ j)
			if(i & (1 << (j - 1)))
				maxl = max(maxl, max(l[a[j]], l[b[j]])), minr = min(minr, min(r[a[j]], r[b[j]])), uni.insert(a[j]), uni.insert(b[j]);
				
		if(maxl > minr) continue;
		ll sz = uni.size(), tmp = (((sum[minr][sz] - sum[maxl - 1][sz]) % MOD) + MOD) % MOD;
		ans = (((ans + tmp * ((__builtin_popcount(i) & 1) ? -1 : 1)) % MOD) + MOD) % MOD;
	}
	
	printf("%lld\n", ans);
	return 0;
}
```

# 后言

终于会数数了好开心。

看见差分，我：你说得对，但是我会 ~~跑酷~~ 线段树。

---

## 作者：happybob (赞：0)

思路很自然。

如果 $m=0$，先对 $l$ 和 $r$ 做个前缀和状物，直接枚举 $\left| S \right|$，里面套个组合数就行。

$m>0$ 时，考虑容斥。直接按照上面的做法是 $O(2^m n)$ 的，不能通过。注意到对于容斥中的枚举的每个状态，其实是确定了 $\left| S \right|$ 的一个范围，每个范围内的取值是一个关于枚举状态中涉及的点数的组合数。用 $O(nm)$ 的复杂度预处理这个组合数的前缀和就能做到 $O(nm + 2^m m)$ 了。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <numeric>
#include <array>
using namespace std;

using ll = long long;

constexpr int N = 3e5 + 5;
constexpr ll MOD = 998244353ll;

int n, m;
array<int, N> l, r, s, s2;
array<int, N> u, v, tot;

array<ll, N> fac, ifac;
array<bool, N> vis;

array<array<ll, 45>, N> sf;
ll ans;

inline ll qpow(ll a, ll b)
{
	ll res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

inline ll binom(int n, int m)
{
	return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	fac[0] = 1ll;
	for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[N - 1] = qpow(fac[N - 1], MOD - 2ll);
	for (int i = N - 2; i >= 0; i--) ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> l[i] >> r[i];
		s[r[i]]++;
		s2[l[i]]++;
	}
	for (int i = 1; i < N; i++) s[i] += s[i - 1], s2[i] += s2[i - 1];
	auto query = [&](int x)
		{
			// l<=x<=r
			return (s[n] - s[x - 1]) - (s2[n] - s2[x]);
		};
	for (int i = 1; i <= m; i++)
	{
		cin >> u[i] >> v[i];
	}
	for (int i = 1; i <= n; i++)
	{
		// |S| = i
		int cnt = query(i);
		if (cnt < i)
		{
			tot[i] = -1;
			continue;
		}
		tot[i] = cnt;
	}
	for (int i = 1; i <= n; i++)
	{
		sf[i] = sf[i - 1];
		if (tot[i] == -1) continue;
		for (int y = 0; y <= min(40, i); y++)
		{
			sf[i][y] = (sf[i][y] + binom(tot[i] - y, i - y)) % MOD;
		}
	}
	for (int S = 0; S < (1 << m); S++)
	{
		// 钦定集合 S 内必选
		int nc = 0;
		int l = 1, r = n;
		for (int j = 1; j <= m; j++)
		{
			if ((S >> (j - 1)) & 1)
			{
				int x = u[j], y = v[j];
				l = max({ l, ::l[x], ::l[y] });
				r = min({ r, ::r[x], ::r[y] });
				if (!vis[x]) nc++, vis[x] = 1;
				if (!vis[y]) nc++, vis[y] = 1;
			}
		}
		for (int j = 1; j <= m; j++)
		{
			if ((S >> (j - 1)) & 1)
			{
				int x = u[j], y = v[j];
				vis[x] = vis[y] = 0;
			}
		}
		l = max(l, nc);
		if (l > r) continue;
		ll val = (sf[r][nc] - sf[l - 1][nc] + MOD) % MOD;
		if (popcount((unsigned int)S) % 2 == 0) ans = (ans + val) % MOD;
		else ans = (ans - val + MOD) % MOD;
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：睿智的憨憨 (赞：0)

## 解法分析

$m$ 非常小，**并且容易满足不符合条件时的情况**，这启发我们对 $m$ 对敌对关系容斥。

设现在容斥中要求 $k$ 对敌对关系必须成立。由此可以得出一定要选的人的集合 $P$ 和 $|S|$ 的可行区间 $[L,R]$。然后枚举除了 $P$ 中的人外还要挑选 $i$ 个人（必须满足 $L \le i+|P| \le R$），这 $i$ 个人中的任意一个人 $x$ 都得满足 $l_x \le i+|P| \le r_x$。可以暴力求出人数 $cnt$，方案数为 $\binom{cnt-|P|}{i}$。但这样太慢了，其实这是可以预处理的，用差分记录经过每个点的区间数量即可。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define lowbit(x) (x&(-x))
using namespace std;
const int N = 300010, mod = 998244353;

int n, m, l[N], r[N], u[N], v[N], d[N], tot[N];
ll fac[N] = {1}, inv[N] = {1};
ll s[45][N], ans;

ll fpow(ll x, ll k){
	if (!k)
		return 1;
	ll t = fpow(x, k / 2);
	if (k & 1)
		return t * t % mod * x % mod;
	return t * t % mod;
}
ll mmi(ll x){
	return fpow(x, mod - 2);
}
ll C(int n, int m){
	if (n < m)
		return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod; 
}

int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d %d", &l[i], &r[i]);
		d[l[i]]++, d[r[i] + 1]--;
	}
	for (int i = 0; i < m; i++)
		scanf("%d %d", &u[i], &v[i]);
	
	for (int i = 1; i <= n; i++)
		tot[i] = tot[i - 1] + d[i];
	
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = mmi(fac[n]);
	for (int i = n - 1; i >= 1; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	
	for (int x = 0; x <= 2 * m; x++)
		for (int i = max(x, 1); i <= n; i++)
			s[x][i] = (s[x][i - 1] + C(tot[i] - x, i - x)) % mod;
	
	for (int S = 0; S < (1 << m); S++){
		int L = 1, R = n, x = 0, g = 1;
		static bool f[N];
		for (int i = 0; i < m; i++)
			if ((S >> i) & 1){
				g = -g;
				if (!f[u[i]])
					x++;
				if (!f[v[i]])
					x++;
				f[u[i]] = f[v[i]] = true;
				if (l[u[i]] > R || r[u[i]] < L){
					L = n + 1;
					break;
				}
				L = max(L, l[u[i]]), R = min(r[u[i]], R);
				if (l[v[i]] > R || r[v[i]] < L){
					L = n + 1;
					break;
				}
				L = max(L, l[v[i]]), R = min(r[v[i]], R);
			}
		if (L <= R)
			ans = ((ans + g * (s[x][R] - s[x][L - 1]) % mod) % mod + mod) % mod;
		for (int i = 0; i < m; i++)
			if ((S >> i) & 1)
				f[u[i]] = f[v[i]] = false;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

