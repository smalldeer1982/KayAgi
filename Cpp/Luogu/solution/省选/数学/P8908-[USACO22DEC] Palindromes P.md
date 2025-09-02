# [USACO22DEC] Palindromes P

## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）正在参加一年一度的蹄球锦标赛！UCFJ 队的 $N(1 \le N \le 7500)$ 头奶牛以微弱优势击败了 Farmer Nhoj 的队伍，赢得了蹄球比赛的金牌。

奶牛们已经为颁奖典礼排好了队。她们希望 FJ 拍摄 $\dfrac{N(N+1)}{2}$ 张合影，为队伍的每个连续子段拍摄一张。

然而，FJ，作为球队的主帅，对于奶牛们应该如何列队十分讲究。具体地说，他拒绝为一个子段拍照，除非它形成一个**回文串**，即对于所有不超过子段长度的正整数 $i$，从子段左端开始的第 $i$ 头奶牛的品种必须与从子段右端开始的第 $i$ 
头奶牛的品种相同。每头奶牛的品种是更赛牛（Guernsey）或荷斯坦牛（Holstein）之一。

对于队伍的 $\dfrac{N(N+1)}{2}$ 个连续子段的每一个，计算将该子段重新排列成回文串所需的最小换位次数（如果不可能这样做则为 $−1$）。单次换位是在子序列中取两头相邻的奶牛并交换。输出所有这些次数之和。

注意对每个连续子段所需的换位次数是独立计算的（奶牛们会在照片拍摄之间返回她们的起始位置）。 

## 说明/提示

### 样例 1 解释

前四个连续子段是 $\texttt{G}$，$\texttt{GH}$，$\texttt{GHH}$ 和 $\texttt{GHHG}$。$\texttt{G}$ 和 $\texttt{GHHG}$ 都已经是回文串，因此它们对总和的贡献为 $0$。$\texttt{GHH}$ 可以使用一次换位重新排列成回文串，因此它对总和的贡献为 $1$。$\texttt{GH}$ 不能使用任意次数的换位重新排列成回文串，因此它对总和的贡献为 $−1$。

$\texttt{HHGG}$ 是另一个对总和有贡献的连续子段。这个子段可以使用两次换位重新排列成回文串。 

### 测试点性质

除样例外有十五个测试点，满足 $N \in \{ 100,200,500,1000,2000,5000,5000,5000,5000,5000,7500,7500,7500,7500,7500\}$ 各一。

## 样例 #1

### 输入

```
GHHGGHHGH```

### 输出

```
12```

# 题解

## 作者：vectorwyx (赞：27)

先考虑对于整个数组怎么求出最小代价。

首先如果 $0,1$ 均出现了奇数次那么它不可能重排为回文串，直接贡献 $-1$。否则令 $m$ 表示 $1$ 的个数，考虑每个 $1$ 最终去到了哪。假设最初 $1$ 所在位置构成的序列 $a$，最终 $1$ 所在位置构成的序列为 $b$，那么这是一个类似匹配的问题，贪心，把 $a,b$ 从小到大排序后 $\sum |a_i-b_i|$ 即为答案。

$a$ 是固定的，现在的问题是如何设置 $b$ 使得 $\sum |a_i-b_i|$ 最小。注意到 $b_{i}+b_{m-i+1}=r-l+2$，那只要确定了 $b$ 的前半边就确定了整个 $b$。于是每次可以匹配掉首尾的一对元素，不难想到 dp，记 $f(i,j)$ 表示当前推到 $i$ 这个位置匹配掉了 $j$ 对 $1$ 的最小代价，转移是 $f(i,j)=\min(f(i-1,j),f(i-1,j-1)+|i-a_i|+|n-i+1-a_{m-i+1}|)$。最终答案为 $f_{n/2,m/2}$。当然在 $m$ 为奇数时需要特殊处理中心点，它的贡献恒为 $|\frac{n+1}{2}-a_{\frac{m+1}{2}}|$。至此我们得到了一个 $O(n^4)$ 的做法，可以通过前三个点。

接下来优化这个 dp，有个显然的想法是对每个 $a_i(i\le \frac{m}{2})$ 取匹配点 $i$ 使得 $|i-a_i|+|n-i+1-a_{m-i+1}|$ 最小，问题在于这样取出来的 $b_i$ 可能不单调。注意到 $|i-a_i|+|n-i+1-a_{m-i+1}|=|i-a_i|+|i-(n+1-a_{m-i+1})|$，那么当 $i$ 落在 $[a_i,n+1-a_{m-i+1}]$ 时式子取得最小值。考虑 $a$ 的前半边是否落在 $\frac{n}{2}$ 左边，如果是，令 $b_i=a_i$ 即满足条件。否则，令 $b_i=n+1-a_{m-i+1}$ 则满足条件。那么答案即为 $\sum_i |a_i+a_{m-i+1}-(n+1)|$，不需要 dp。复杂度变为 $O(n^3)$，可以通过前五个点。

然后转为枚举 $a_i,a_{m-i+1}$ 计算它们配对产生的贡献。还是记 $a$ 为整个数组中 $1$ 的位置序列，如果两个位置 $a_i,a_j$ 想要配对的话首先有 $l\le a_i,r\ge a_j$，同时如果 $j-i+1$ 为奇数那么 $r-l+1$ 应当也为奇数。对于每个合法的 $l,r$，$a_i,a_j$ 的贡献为 $|a_i+a_j-(l+r)|$。如果事先知道所有 $[l,r]$ 的信息是不是就好办了，不难发现 $i,j$ 对应的信息可以由 $i-1,j+1$ 递推而来。那么考虑从 $a$ 的每段前缀以及每段后缀出发，每次砍掉首尾的两个元素，把新产生的 $[l,r]$ 加进一个数据结构里。而这里新产生的 $[l,r]$ 其实就是 $l\in(a_{i-1},a_i],r\in[a_j,a_{j+1})$ 对应的所有区间，于是可以枚举 $l+r$ 简单地算出 $l+r$ 的出现次数，然后一并插入数据结构。

现在看看这个数据结构需要支持什么：维护一个可重集，支持：插入 $c$ 个 $x$，查询所有 $\le x$ 的元素之和以及元素个数。由于 $x\le 2n$，只需要用一个树状数组。复杂度 $O(n^2\log n)$。有一个细节是让出现次数较少的值作为 $1$，这样可以省去一半的常数。

代码如下：（码字不易，能不能点个赞再走QAQ）
```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=7505,inf=1e9;
int cnt;ll sum;
namespace BIT{
int n;
pair<int,ll> tr[N<<1];
#define lbit(x) (x&(-x))
void upd(int c,int k){//插入 c 个 k 
//	printf("upd(%d,%d)\n",c,k);
	sum+=(ll)c*k;cnt+=c;
	int x=k;
	while(x<=n){
		tr[x].fi+=c,tr[x].se+=(ll)c*k;
		x+=lbit(x);
	}
}
int ask_cnt(int x){
	int ret=0;
	while(x){
		ret+=tr[x].fi;
		x-=lbit(x);
	}
	re ret;
}
ll ask_sum(int x){
	ll ret=0;
	while(x){
		ret+=tr[x].se;
		x-=lbit(x);
	}
	re ret;
}
void clear(){fo(i,1,n) tr[i]=mk(0,0);}
}
using BIT::upd;
using BIT::ask_cnt;
using BIT::ask_sum;
using BIT::clear;


int a[N],n,c0[N],c1[N],b[N],m,pos[N],ct;
ll ans;

inline void play(int l,int r,int L,int R,bool fl){
	r-=l,R-=L;
	fo(x,0,r+R) if(!fl||(x+l+L)%2==0){
		int lx=max(0,x-R),rx=min(x,r);
//		int c=fl?(rx/2-(lx-1)/2):(rx-lx+1);
		int c=(rx-lx+1);
		upd(c,x+l+L);
	}
}

void shrink(int l,int r){
	int fl=(r-l+1)&1;
	sum=0;cnt=0;
	clear();
	while(l<=r){
//		printf("[%d,%d]\n",l,r);
//		fo(j,pos[l-1]+1,pos[l]) fo(k,pos[r],pos[r+1]-1) 
//			if(!fl||((k-j+1)&1)) upd(1,j+k),sum+=j+k,cnt++;
		play(pos[l-1]+1,pos[l],pos[r],pos[r+1]-1,fl);
		int x=pos[l]+pos[r];
		ll val=sum-2*ask_sum(x)+(ll)x*(2*ask_cnt(x)-cnt);
//		printf("cnt=%d sum=%lld x=%d val=%lld\n",cnt,sum,x,val);
		if(l==r){
			assert(val%2==0);
			ans+=val/2;
		}else ans+=val;
//		printf("now ans=%lld\n",ans);
		l++,r--;
	}	
}

signed main(){
	int ch=getchar();while(ch!='G'&&ch!='H') ch=getchar();
	while(ch=='G'||ch=='H') a[++n]=ch=='G',ch=getchar();
	{
		int c=0;fo(i,1,n) c+=a[i];
		if(c>n/2) fo(i,1,n) a[i]^=1;
	}
	BIT::n=2*n;
//	cout<<n<<'\n';out(a,1,n);
	fo(i,1,n){
		c0[i]=c0[i-1]+(a[i]==0);
		c1[i]=c1[i-1]+(a[i]==1);
	}
	fo(i,1,n) if(a[i]) pos[++ct]=i;
	pos[ct+1]=n+1;
//	cout<<"pos:";out(pos,0,ct+1);
	fo(i,1,ct) shrink(1,i);
	fo(i,2,ct) shrink(i,ct);
	fo(l,1,n) fo(r,l+1,n){
		int x=c0[r]-c0[l-1],y=c1[r]-c1[l-1];
		if((x&1)&&(y&1)) ans--;
	}	
	cout<<ans;
	return 0;
}
}
/*
GHHGGHHGH
-------------------------------------------------
12
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：point_fish (赞：9)

# 题意
给出只包含两种字符的字符串 $ s $，可以相邻交换，求把它所有子串变成回文串的代价。

$ len \le 7500 $

# 推导

对于一个子串 $ s $，由于只有两种字符，其中一种字符满足回文性质后，另一种字符也满足回文，我们这里只考虑字符 $ G $。

- 我们不会交换两个相同的字符，交换相同字母字符，则字符串不变，不优。

- 在不交换两个相同字符的情况下，相同字符的顺序不变。也就是说，对于一个子串，第一个 $ G $ 对应的是最后一个 $ G $，第二个 $ G $ 对应的是倒数第二个 $ G $。以此类推，除了奇数长度的最中间位置，其他字符都是一一对应的。

- 在一个子串 $ s[L,R] $ 中，一对满足回文的位置分别为 $ L+x $ 和 $ R-x $，满足回文的两个位置 $ l $ 和 $ r $ 满足 $ l+r=L+R $，即确定子串位置时，一对相同的字符使之交换到回文位置的代价是 $ |l+r-L-R| $。

回到原问题，只考虑 $ G $，可以发现答案的贡献只与子串位置和一对对应字符的位置。

选定一个或两个相邻的 $ G $，令其为子串的中心，计算只包含已经选定的 $ G $，用维护好的 $ l+r $ 统计答案，或 $ H $。同时向左右扩展下一个 $ G $，再将这两个 $ G $ 的位置 $ l $ 和 $ r $ 的和扔进树状数组维护，由于求的是绝对值，还要维护一下 $ l+r $ 和的个数，算那些大于或小于 $ L+R $ 的个数，总复杂度 $ O(n^{2}\log n) $。

# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=7505;
char a[maxn];
int G[maxn],cnt,len,c[maxn];
struct tree{
	ll c[maxn<<1];
	ll lowbit(int x){return x&-x;}
	inline void add(int x,int y){
		for(int i=x;i<=2*len;i+=lowbit(i))
			c[i]+=y;
	}
	inline ll ask(int x){
		ll sum=0;
		for(int i=x;i;i-=lowbit(i))
			sum+=c[i];
		return sum;
	}
	inline void clear(){
		memset(c, 0, sizeof(c));
	}
}tr1,tr2;
int main(){
	scanf("%s",a+1);
	len=strlen(a+1);
	for(int i=1;i<=len;i++)
		if(a[i]=='G') G[++cnt]=i;//G是 G出现的位置 
	G[0]=0;G[cnt+1]=len+1;
	ll ans=0,sum=0,ansl=0;
	for(int i=1;i<=cnt;++i){	
		int lt=i,rt=i;
		while(lt>=1 && rt<=cnt){
			int qwq = G[lt] + G[rt];
			if(lt!=i) tr1.add(qwq, qwq),tr2.add(qwq,1),sum+=qwq,ansl++;
			for(int l=G[lt];l>G[lt-1];--l)
				for(int r=G[rt];r<G[rt+1];++r){
					if(!((r-l+1)&1)) {ans--;continue;}
					int mid=l+r;
					ll p=tr2.ask(mid-1),q=tr1.ask(mid-1);
					ans+=abs(((l+r)>>1)-G[i]);
					ans+=(p*mid-q)+(sum-q)-(ansl-p)*mid;
				}
			--lt;++rt;
		}
		sum=0;ansl=0;
		tr1.clear();
		tr2.clear();//不同G为中心的子串G的数据是不同的 
	}
	for(int i=1;i<cnt;i++){	
		int lt=i,rt=i+1;
		while(lt>=1 && rt<=cnt){
			int qwq = G[lt] + G[rt]; 
			tr1.add(qwq, qwq),tr2.add(qwq,1);
			sum+=qwq;ansl++;
			for(int l=G[lt];l>G[lt-1];--l)
				for(int r=G[rt];r<G[rt+1];++r){
					int mid=l+r;
					ll p=tr2.ask(mid-1),q=tr1.ask(mid-1);
					ans+=(p*mid-q+(sum-q)-(ansl-p)*mid);
				}
			--lt;++rt;
		}
		sum=0;ansl=0;
		tr1.clear();
		tr2.clear();
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Lynkcat (赞：6)

考虑给你一个字符串怎么算答案。

考虑把字符串抽象一下，把 1 两两配对，由于最后限制中点在正中间，那么若中点在右侧就把左边的 1 往左移，否则就把右边的 1 往右移。现在我们得到了一个答案的上界。

事实上这也是答案的下界，考虑把式子写出来然后发现是类似 $|x-l|+|r-x|=|x-l|+|x-r|$ 这样两个绝对值函数相加的形式，最优值取在两者之间。

那么现在就有一个 $O(n^2 \log n)$ 的简单做法，也就是说枚举中间的 $1$ 在哪儿，然后每次左边添加一个 $1$，右边添加 $1$，然后去枚举当前状态下合法的 $[l,r]$，然后用树状数组维护比当前中点大的中点的个数以及位置的和，还有比之小的中点位置的和。

发现一件事，就是说上述过程中满足 $l$ 在一段区间，$r$ 在一段区间，那么 $mid$ 也在一段区间上。那么考虑固定 $mid$，然后算满足中点在 $mid$ 的 $[l,r]$ 的答案都是一样的。然后接下来令 $mid$ 往右移一位，然后会发现贡献的变化只和当前 $mid$ 处的信息有关，所以开个桶能做到 $O(1)$ 实现 $mid$ 左移 $1$ 与右移 $1$ 以及信息查询与更新。把指针的移动全都摊到对应的 $[l,r]$ 上就能做到 $O(n^2)$ 的复杂度。

事实上可以不用固定 $mid$，直接枚举也能把复杂度摊成 $O(n^2)$。

代码实现极其简洁：

```c++
// Lynkcat.
// Problem: P8908 [USACO22DEC] Palindromes P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8908
// Memory Limit: 256 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e9
#define mod 998244353
// #define int ll
#define N 7505 
using namespace std;
int f[N][N];
long long cnt[2*N];
ll n;
ll a[N];
ll mid,ans;
ll lf,rt;
inline void mover()
{
	rt-=cnt[mid];
	lf+=cnt[mid];
	ans+=lf-rt;
	mid++;
}
inline void movel()
{
	ans+=rt-lf;
	mid--;
	lf-=cnt[mid];
	rt+=cnt[mid];
}
void BellaKira()
{
	string st;
	cin>>st;
	n=st.size();
	poly g;
	g.push_back(0);
	for (int i=1;i<=n;i++)
		if (st[i-1]=='G') a[i]=0;
		else a[i]=1,g.push_back(i);
	g.push_back(n+1);
	for (int i=1;i+1<g.size();i++)
	{
		for (int j=1;j<=2*n;j++) cnt[j]=0;
		mid=2*g[i];
		ans=0;
		lf=0,rt=0;
		for (int l=0;i-l>=1&&i+l+1<g.size();l++)
		{
			int o=(g[i-l]+g[i+l]);
			if (l!=0)
			{
				cnt[o]++;
				if (o>=mid)
				{
					rt++;
					ans+=o-mid;
				} else
				{
					lf++;
					ans+=mid-o;
				}
			}
			for (int x=g[i-l-1]+1;x<=g[i-l];x++)
				for (int y=g[i+l];y<g[i+l+1];y++)
				{
					int o=(x+y);
					while (mid<o)
					{
						mover();
					}
					while (mid>o)
					{
						movel();
					}
					f[x][y]+=ans+abs(o/2-g[i]);
				}
		}
	}
	for (int i=1;i+1<g.size();i++)
	{
		for (int j=1;j<=2*n;j++) cnt[j]=0;
		mid=2*g[i];
		ans=0;
		lf=0,rt=0;
		for (int l=0;i-l>=1&&i+l+2<g.size();l++)
		{
			int o=(g[i-l]+g[i+l+1]);
			cnt[o]++;
			if (o>=mid)
			{
				rt++;
				ans+=o-mid;
			} else
			{
				lf++;
				ans+=mid-o;
			}
			for (int x=g[i-l-1]+1;x<=g[i-l];x++)
				for (int y=g[i+l+1];y<g[i+l+2];y++)
				{
					int o=(x+y);
					while (mid<o)
					{
						mover();
					}
					while (mid>o)
					{
						movel();
					}
					f[x][y]+=ans;
				}
		}
	}
	ans=0;
	for (int i=1;i<=n;i++)
	{
		int x=0,y=0;
		for (int j=i;j<=n;j++)
		{
			if (a[j]==0) x^=1;
			else y^=1;
			if (x&&y) f[i][j]=-1;
			ans+=f[i][j];
		}
	}
	cout<<ans<<'\n';
}
signed main()
{
	IOS;
	cin.tie(0);
	int T=1;
	while (T--)
	{
		BellaKira();
	}
}
```



---

## 作者：蒟蒻君HJT (赞：5)

## 转化：

考虑对一个子串 $[L,R]$ 的答案的计算方法。

1. 如果长度为偶数，而每种颜色都是奇数个，那么答案为 $-1$ ，显然。

2. 否则总是有解的。 那么我们可以暴力枚举 $L,R$ 把 $-1$ 先判掉。

问题是：有解的情况下，怎么操作答案最小？

首先我们不可能交换相邻的相同的颜色，可以得出结论：假设我们仅考虑蓝色，我们的操作必然是首尾配对蓝色，然后如果中间剩余了一个无法配对的蓝色的话把它放到正中间（由于长度为奇数，所以存在正中间）。

进一步得出：一定存在某一种最优的操作方案，使得配对的两个颜色至少一个不移动。可以感性理解一下。

那么假设有 $x$ 个蓝色，从小到大第 $x$ 个蓝色的位置是 $s_x$ ，我们的答案就是： 

$$|\frac{L+R}{2}-s_{\frac{x+1}{2}}|+\sum_{i=1}^{\lfloor \frac{x}{2}\rfloor}|s_i+s_{x-i+1}-L-R|$$

前者是对中心位置的计算，可以在第一次暴力的时候顺便搞掉。

求和符号的计算比较恶心：一是有绝对值符号，二是要求配对的两个蓝色才有贡献，这就对 $L,R$ 又提出了要求。

## 计算：

解决方案是：我们在计算的时候不想改变 $s$ 的配对的情况，这样就可以把 $s_i+s_{x-i+1}$ 看作一个整体，所以我们枚举中心的一个或者两个 $s$ ，然后向两边暴力均匀扩展。

每次假设我们在扩展 $s_a$ 和 $s_b$ ，则我们先把 $s_a+s_b$ 加入数据结构中，进而枚举 $L\in[s_{a-1}+1,s_a]$ 和 $R\in[s_{b},s_{b+1}-1]$ 的答案。

接下来（我觉得）比较神秘：将 $s_i+s_{x-i+1}$ 扔到 BIT 里维护区间个数和区间和，直接暴力枚举 $(L,R)$ ，单次 $\mathcal{O}(\log n)$ 计算 $(L,R)$ 的答案，总复杂度是 $\mathcal{O}(n^2\log n)$ 可以通过。为什么枚举 $(L,R)$ 的次数是 $\mathcal{O}(n^2)$ 呢？因为在每次中心点不同的情况下，同一对 $(L,R)$ 只会枚举 $\mathcal{O}(1)$ 次。所以这样的枚举看起来很暴力，实际上是没问题的，而我没搞出来的原因就是寄在这一步复杂度分析上。

## 代码：

```cpp
#include <bits/stdc++.h>
int n, cnt = 0, c[7505];
struct Fenwick{
	int C[15005];
	inline int lowbit(int x){
		return x & -x;
	}
	inline int ask(int x){
		int r = 0;
		for(; x; x -= lowbit(x)) r += C[x];
		return r;
	}
	inline void modify(int x, int y){
		for(; x <= 2 * n; x += lowbit(x)) C[x] += y;
		return ;
	}
	inline void _clear(){
		for(int i = 1; i <= 2 * n; ++i) C[i] = 0;
		return ;
	} 
}tr1, tr2;
long long ans = 0ll;
char s[7505];
int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int uuu = 0;
	for(int i = 1; i <= n; ++i) uuu += (s[i] == 'G');
	if(uuu > n / 2) for(int i = 1; i <= n; ++i) s[i] = (s[i] == 'G') ? 'H' : 'G';
	for(int L = 1; L <= n; ++L){
		cnt = 0;
		for(int R = L; R <= n; ++R){
			if(s[R] == 'G') c[++cnt] = R;
			if(cnt % 2 && (R - L + 1) % 2 == 0) ans += -1ll;
			else if(cnt % 2) ans += 1ll * abs((L + R) / 2 - c[cnt / 2 + 1]);
		}
	}
	cnt = 0;
	for(int i = 1; i <= n; ++i) if(s[i] == 'G') c[++cnt] = i;
	c[cnt + 1] = n + 1;
	for(int i = 1; i <= cnt; ++i){
		tr1._clear();
		tr2._clear();
		int g = 0;
		for(int j = 1; i - j >= 1 && i + j <= cnt; ++j){
			int p = c[i - j] + c[i + j];
			tr1.modify(p, 1);
			tr2.modify(p, p);
			g += p;
			for(int L = c[i - j - 1] + 1; L <= c[i - j]; ++L){
				for(int R = c[i + j]; R <= c[i + j + 1] - 1; ++R){
					if((R - L + 1) % 2 == 0) continue;
					int s1 = tr1.ask(L + R), s2 = tr2.ask(L + R);
					ans += 1ll * s1 * (L + R) - 1ll * s2;
					ans -= 1ll * (j - s1) * (L + R) - 1ll * (g - s2);
				}
			}
		}
	}
	for(int i = 1; i <= cnt - 1; ++i){
		tr1._clear();
		tr2._clear();
		int g = 0;
		for(int j = 0; i - j >= 1 && i + 1 + j <= cnt; ++j){
			int p = c[i - j] + c[i + 1 + j];
			tr1.modify(p, 1);
			tr2.modify(p, p);
			g += p;
			for(int L = c[i - j - 1] + 1; L <= c[i - j]; ++L){
				for(int R = c[i + 1 + j]; R <= c[i + 1 + j + 1] - 1; ++R){
					int s1 = tr1.ask(L + R), s2 = tr2.ask(L + R);
					ans += 1ll * s1 * (L + R) - 1ll * s2;
					ans -= 1ll * (j + 1 - s1) * (L + R) - 1ll * (g - s2);
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：Petit_Souris (赞：2)

$n=7500$ 怎么被题解区一篇篇 $\mathcal O(n^2\log n)$ 快刀斩乱麻冲过去了......还是讲一下 $\mathcal O(n^2)$ 的正解吧。

首先考虑如何求解单个字符串。显然，当长度为偶数，且两种字符均出现奇数次时无解，否则必有解。

最优的移动方法是拉出所有字符 `G`，把这些位置两两配对，每次移动可以让两个位置的中点移动 $0.5$ 步，要使中点移到整个串的中点，因此距离为 $|n+1-p_x-p_y|$。如果 `G` 有奇数个，中间那个得恰好移到中点上，距离为 $|\frac{n+1}{2}-p_x|$。

直接暴力可以做到 $\mathcal O(n^3)$。

思考如何优化。我们可以枚举中心，可能是一个 `G`，也可能是两个相邻的 `G`，并依次向两侧扩展，做扫描线。比如现在扩展到了 $p_x$ 和 $p_y$，我们可以顺带计算出 $l\in[p_{x-1}+1,p_x]$，$r\in[p_y,p_{y+1}-1]$ 的所有 $[l,r]$ 的答案。

$(x,y)$ 对 $[l,r]$ 的贡献为 $|l+r-p_x-p_y|$。那么扫描线的过程中，维护所有 $p_x+p_y$ 的各个值的数量和总和，查询的时候拆开绝对值分类即可。用树状数组容易做到 $\mathcal O(n^2\log n)$，因为每个区间只会被枚举一次，所以复杂度正确。

既然都已经均摊了，能不能把树状数组也均摊掉？想了一下发现显然可以，直接维护一个指针表示目前扫到的 $l+r$，那么对于枚举一个 $l$，右端点至多移动 $2(p_{y+1}-p_y)$ 次，$x$ 变化时造成的总移动至多 $2n$ 次，因此总指针移动次数还是 $\mathcal O(n^2)$ 的。而移动一位显然容易 $\mathcal O(1)$ 修改，所以总复杂度为 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
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
const ll N=7.5e3+9;
int n,a[N],pos[N],cnt,sum[N][2];
ll ans,totsum;
char s[N];
int scnt[N<<1],totcnt;
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    scanf("%s",s+1),n=strlen(s+1);
    rep(i,1,n){
        rep(j,0,1)sum[i][j]=sum[i-1][j];
        if(s[i]=='G')sum[i][0]++,pos[++cnt]=i;
        else sum[i][1]++;
    }
    rep(i,1,n){
        rep(j,i,n){
            int c0=sum[j][0]-sum[i-1][0];
            if((c0&1)&&((j-i)&1))ans--;
        }
    }
    rep(i,1,cnt){
        memset(scnt,0,sizeof(scnt));
        totcnt=totsum=0;
        int u=i,v=i,ptr=-1,curcnt=0;
        ll cursum=0;
        while(u>=1&&v<=cnt){
            if(u!=v){
                int val=pos[u]+pos[v];
                scnt[val]++,totcnt++,totsum+=val;
                if(val<=ptr)curcnt++,cursum+=val;
            }
            int pl=(u==1?1:pos[u-1]+1);
            int pr=(v==cnt?n:pos[v+1]-1);
            rep(p,pl,pos[u]){
                rep(q,pos[v],pr){
                    while(ptr<p+q)ptr++,curcnt+=scnt[ptr],cursum+=scnt[ptr]*ptr;
                    while(ptr>p+q)curcnt-=scnt[ptr],cursum-=scnt[ptr]*ptr,ptr--;
                    if((q-p+1)&1){
                        ans+=abs((p+q)/2-pos[i]);
                        ans+=curcnt*(p+q)-cursum;
                        ans+=(totsum-cursum)-(totcnt-curcnt)*(p+q);
                    }
                }
            }
            u--,v++;
        }
    }
    rep(i,1,cnt-1){
        memset(scnt,0,sizeof(scnt));
        totcnt=totsum=0;
        int u=i,v=i+1,ptr=-1,curcnt=0;
        ll cursum=0;
        while(u>=1&&v<=cnt){
            int val=pos[u]+pos[v];
            scnt[val]++,totcnt++,totsum+=val;
            if(val<=ptr)curcnt++,cursum+=val;
            int pl=(u==1?1:pos[u-1]+1);
            int pr=(v==cnt?n:pos[v+1]-1);
            rep(p,pl,pos[u]){
                rep(q,pos[v],pr){
                    while(ptr<p+q)ptr++,curcnt+=scnt[ptr],cursum+=scnt[ptr]*ptr;
                    while(ptr>p+q)curcnt-=scnt[ptr],cursum-=scnt[ptr]*ptr,ptr--;
                    ans+=curcnt*(p+q)-cursum;
                    ans+=(totsum-cursum)-(totcnt-curcnt)*(p+q);
                }
            }
            u--,v++;
        }
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：IamZZ (赞：2)

**P组练习总结#5**

又是一道转移太过抽象的题目，脑水都快用完了……

但是真的太巧妙了，想不到啊！

### 题目大意

FJ 的奶牛们用牛蹄打球（真会玩），险胜了 FN 的奶牛们~~谁开球谁输，都发不过去~~，现在，作为金牌球队，他们要合影留念！

$n(n\le 7500)$ 头奶牛排成了一排，每一头都是 `G` 或 `H` 中的一种品种，用一个长度为 $n$ 的字符串表示。

FJ 现在要给所有 $\frac{n(n+1)}{2}$ 个奶牛子段拍照，但作为摄影师的他有独特的品味，他拒绝给不是回文串的子段拍照。

一次操作可以交换两个相邻的奶牛，你现在需要将所有的子段单独取出来，用最少的操作将其排成回文串，让拍照可以快乐的进行。

你的任务是对所有子段的最小操作数求和，如果一个子段非法，计最小操作数为 -1。

### 解题思路（部分分）

这题考虑先从部分分入手，嘿嘿。

思考一下，最小的操作数满足一些什么优秀的性质呢？

首先，两个相邻的奶牛若是同种品种，绝不会交换，想想吗，**简直是如换**。

这告诉我们，对于所有的子段，内部**同种奶牛**的顺序是不会改变的，第一个 `G` 永远是第一个。

不变的顺序，带来的是确定的对应关系，若有 $c$ 个 `G`，第一个绝对对应第 $c$ 个，其他同理。

有了这个条件，有什么用？

我们可以有以下推论：当前区间是 $[l,r]$，设第 $k+1$ 对 `G` 位置分别是 $a,b(a<b)$，$a,l$ 之间的 `H` 数应该与 $b,r$ 之间的相等时，$a,b$ 才能对称。

$a-l+1-k$ 是 $a$ 之前的 `H` 数，$r-b+1-k$ 是 $b$ 之后的，因此，让 $a,b$ 对称的最小操作数：$|(a-l+1-k)-(r-b+1-k)|=|(a+b)-(l+r)|$。

解释一下，如果让 $a$ 交换一步，可以让 $a$ 前的 `H` 数量 $\pm1$，我们一步一步逼近 $b$ 的数量，因此需要二者差值这么多次操作。

对于奇回文串而中间刚好有奇数个 `G` 时，对中间的处理稍稍有点不同，这时只需要计算排中间那个 `G` 距离 $\frac{l+r}{2}$ 的距离就好了~

至于偶回文串而且有奇数个 `G` 时，很遗憾，这是非法的，-1 解决。

这样我们很容易想到 $\Theta(n^3)$ 的暴力做法，枚举 $l,r$，暴力跑一遍 $l$ 到 $r$，找到中间对称的，算就完了，比较简单。

### 参考代码（部分分）

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=7505;
int n,c,t[N];
ll s;
char ch[N];
int main()
{
	int i,j,k;
	scanf("%s",ch+1);
	n=strlen(ch+1);
	for(i=1;i<=n;++i)
	{
		for(j=i;j<=n;++j)
		{
			c=0;
			for(k=i;k<=j;++k)//找点
			{
				if(ch[k]=='G')
				  ++c,t[c]=k; 
			}
			if((j-i+1)%2==0&&(c&1))//非法
			{
				s=s-1;
				continue; 
			}
			for(k=1;k<=c/2;++k)
			  s=s+abs((t[k]-i)-(j-t[c-k+1]));//算对称的贡献
			if(c&1)//特殊中间点
			  s=s+abs((i+j)/2-t[c+1>>1]);
		}
	}
	printf("%lld",s);
	return 0;
}
```

### 解题思路（正解）

暴力的复杂度仍然是不够优秀的，我们发现，在算多个子段的时候，同一对 `G` 可能多次计算，从这里入手，我们可以优化。

我们发现，若是奇数个 `G`，我只需要固定中间的那个位置，左右都是依次排开对称的，对吧？

偶数个也是同理，我们找到最中间的那一对，其他的对应关系也都是确定的了，这样，我们找到中间的一对，就可以分别左右扫一遍，计算这些子段的答案。

而且，因为每个子段只会处理一次，所以复杂度仍然是 $\Theta(n^2)$ 的。

现在问题是，怎么样在扫描的过程中快速处理出子段答案？

若当前区间是 $[l,r]$，其中有 $c$ 对 `G`，设 $F_{l+r}=\sum_{j=1}^k|(a_j+b_j)-(l+r)|$，易得 $F_{l+r}$ 就是区间的答案。

我们还有辅助数组 $d_{l+r}=F_{l+r+1}-F_{l+r}$，这是这道题最难想的地方，乍一看这个 $d$ 很难处理，但是 $d$ 的变化规律其实非常的简单！

我们想想，$d_{l+r+1}$  与 $d_{l+r}$ 有什么关系？那些原本 $a_j+b_j>l+r+1$ 的，会对 $F_{l+r}$ 贡献 -1，而对于 $a_j+b_j<l+r+1$ 来说，会贡献 +1。

这两种情况对 $d$ 都没有影响，关键点你也一定能看出来，那就是 $a_j+b_j=l+r+1$ 时，它的贡献从 -1 变成了 +1，相当于 $d+2$。

也就是说，我们可以引入一个桶来记录 $a_j+b_j$，$t_v$ 表示 $a_j+b_j=v$ 的对数，$d$ 就很好处理了，$d+2t_{l+r+1}$。

### 具体实现（正解）

巧妙，继承上一次的子段信息，维护之后的，真的是充分的使用了时间。

先枚举中间的那一对 `G`，然后枚举字段中的对数，计入 $t$，确定之后，满足对数限制的子段是从这一对的左端点开始，不能到前面一个 `G` 的位置，右端同理。

我们只需要在这样两个区间之间扫描子段答案就好了。

固定左端点，右端点不断增加，带的是 $l+r$ 不断 +1，同时更新 $F,d$，同时将更新出的 $F$ 加进答案。

这是我们右端点到了极限，我们先将 $F,d$ 还原，这是左端点需要减一，所以 $l+r$ 会减一，记得立刻更新 $F,d$。

对于中间是一个 `G` 的操作类似，只不过，不能将中间的那一个加入 $F$ 算贡献，要单独算距离 $\frac{l+r}2$。

哦对，所有非法的也在中间是 `G` 时计算，若 $r-l+1$ 是偶数，这个区间就是非法的，答案 -1。

到此，我们就可以用 $\Theta(n^2)$ 的复杂度计算答案啦（好妙的转移），完结撒花(●'◡'●)！

### 参考代码（正解）

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=7505;
int n,c,t[N],u,v,x,y,e[N<<1];
ll s,f,d;
char ch[N];
int main()
{
	int i,j,k,l,r;
	scanf("%s",ch+1);
	n=strlen(ch+1);
	for(i=1;i<=n;++i)
	{
		if(ch[i]=='G')
		  ++c,t[c]=i;
	}
	for(i=1;i<=c;++i)
	{
		for(k=1;k<=n<<1;++k)//清空桶
		  e[k]=0;
		f=0,d=0;
		for(k=0;i>k&&j+k<=c;++k)//奇数回文串
		{
			u=t[i-k],x=(i-k==1?0:t[i-k-1]);
			v=t[i+k],y=(i+k==c?n+1:t[i+k+1]);
			if(u^v)
			  ++e[u+v],++d;//加入桶，中间那个不算
			for(l=u;l>x;--l)//左端点枚举
			{
				for(r=v;r<y;++r)//右端点枚举
				{
					if(r-l+1&1)//奇数回文串，中心是 i 
					  s=s+f+abs((l+r>>1)-t[i]);
					else//不成样子
					  --s;
					f=f+d,d=d+(e[l+r+1]<<1);//时刻更新F，d
				}
				for(r=y;r>=v;--r)//回退操作
				  d=d-(e[l+r]<<1),f=f-d;//记住，l-1了，所以要把d，f多减一位 
			}
			for(r=v;r<y;++r)//处理完的区间之后还有用，为后面加上
			  f=f+d,d=d+(e[l+r+1]<<1);
		}
		if(i==c)
		  continue;
		j=i+1;
		for(k=1;k<=n<<1;++k)
		  e[k]=0;
		f=0,d=0;
		for(k=0;i>k&&j+k<=c;++k)//偶数回文串，一样的啦~
		{
			u=t[i-k],x=(i-k==1?0:t[i-k-1]);
			v=t[j+k],y=(j+k==c?n+1:t[j+k+1]);
			++e[u+v],++d;
			for(l=u;l>x;--l)
			{
				for(r=v;r<y;++r)
				{
					s=s+f;
					f=f+d,d=d+(e[l+r+1]<<1);
				}
				for(r=y;r>=v;--r)
				  d=d-(e[l+r]<<1),f=f-d;
			}
			for(r=v;r<y;++r)
			  f=f+d,d=d+(e[l+r+1]<<1);
		}
	}
	printf("%lld",s);
	return 0;
}
```



---

## 作者：向日葵小班 (赞：2)

### 做这一题要有这样的思路:考虑每对字符的贡献。

因为不会交换两个相同的字符，所以单独看一种字符的话，最后一定是第一个对最后一个，第二个对倒数第二个。

然后一对相同字符贡献是 $\left\vert a_j+a_i-2mid\right\vert$。

按照这个结论继续下去。

不妨以字符 $G$ 来考虑。

考虑固定最中间一个或两个字符，此时字符的对应关系已经确定。
向两边枚举当前计算的最外边的一对字符 $a_l,a_r$ 然后此时有贡献的只有里面若干对字符。

此时恰好包含这些字符的范围就是 $(a_{l-1},a_l]-[a_r,a_{r+1})$，枚举左右端点计算子串的贡献（可以发现每个子串只会被枚举恰好 $1$ 次）。


由于我们的贡献是 $|a_i+a_j-2mid|$，记下所有的$a_i+a_j$，取绝对值就是要计算有多少比 $2mid$ 大，有多少比 $2mid$ 小。
 
容易用数据结构做到单 $\log$。

但是也可以用类似于莫队移动指针的形式计算贡献增减，这样可以做到 $O(1)$。

总复杂度 $O(n^2)$。







---

## 作者：SegTree (赞：1)

题意：给定 $01$ 串，定义 $f(T)$ 为通过交换相邻字符使得 $T$ 回文的最小操作次数，如果不可能则 $f(T)=-1$。求所有子区间的 $f(T)$ 之和。$n\le 7500$。

首先考虑给定 $T$ 如何计算 $f(T)$。先判掉 $-1$。记 $pos_i$ 表示第 $i$ 个 $1$ 的出现位置，记 $pos'_i$ 为操作后第 $i$ 个 $1$ 出现位置。则答案为 $\sum |pos_i-pos'_i|$。

记 $m$ 为 $T$ 中 $1$ 的个数，$n=|T|$，那么有 $pos'_i+pos'_{m-i+1}=|T|+1$，产生的贡献为 $|pos_i-pos'_i|+|pos_{m-i+1}-(|T|+1-pos'_{i})|=|pos_i-pos'_i|+|pos'_i-(-pos_{m-i+1}+|T|+1)|$，取最小值时等于 $|pos_i-(-pos_{m-i+1}+|T|+1)$。

直接暴力枚举子区间计算 $f(T)$，时间复杂度 $O(n^3)$。考虑优化。

考虑枚举“中心点”，这样 $pos_i+pos_{m-i+1}$ 是不会发生变化的。此时问题等价于在 $S$ 中插入 $x$，查询 $\sum_{y\in S}|x-y|$，使用树状数组维护即可。时间复杂度 $O(n^2\log n)$。

---

## 作者：Purslane (赞：0)

# Solution

按部就班做题吧。

先想想怎么暴力算一个序列的答案。不妨设 $\rm G$ 出现了偶数次。发现只需要将相应的 $\rm G$ 移到我们需要的位置即可。

假设 $\rm G$ 的两个对应位置是 $p_1$ 和 $p_2$，我们要移到 $x$ 和 $n-x+1$，则答案是 $|p_1-x|+|p_2-(n-x+1)|$，有一个下界是 $|n+1-p_1-p_2|$。而显然存在这样的构造使得每一对数都卡到了下界（看 $\rm G$ 前半段还是后半段在最终序列的同一半边即可。其实我自己做题的时候这一步走了一些弯路，最后灵机一动发现有统一形式）。

直接写个暴力能过 $\rm 36$ 分。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10;
int n;
string S; 
ll ans;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S;
	ffor(i,1,n) {
		vector<int> a,b;
		ffor(jj,i,n) {
			if(S[jj]=='G') a.push_back(jj);
			else b.push_back(jj);
			if(a.size()%2==0) {ffor(j,0,(int)a.size()/2-1) ans+=abs(i+jj-a[j]-a[a.size()-j-1]);}
			else if(b.size()%2==0) {ffor(j,0,(int)b.size()/2-1) ans+=abs(i+jj-b[j]-b[b.size()-j-1]);}
			else ans--;
		}
	}
	cout<<ans;
	return 0;
}
```

比如我们固定 $\rm G$ 去算，发现可以直接枚举整个序列的中心，往两边不断扩展。只有向可重集 $S$ 中插入元素，查询 $\sum_{u \in S} |u-v|$ 两种操作，直接使用树状数组维护即可，复杂度 $O(n^2 \log n)$。

由于有很多线段之类的东西，自带小常数。

哦如果区间中颜色全部相同要特判一下。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=7500+10;
int n,ans[MAXN][MAXN];
string S;
int cnt[MAXN<<1],sum[MAXN<<1],acnt,asum;
void update(int pos,int v) {acnt++,asum+=v;while(pos<=n+n) cnt[pos]++,sum[pos]+=v,pos+=pos&-pos;return ;}
pair<int,int> query(int pos) {int c=0,s=0;while(pos) c+=cnt[pos],s+=sum[pos],pos-=pos&-pos;return {c,s};}
int calc(int val) {
	auto pr=query(val);
	return asum-2*pr.second+(-acnt+2*pr.first)*val;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	memset(ans,-1,sizeof(ans));
	cin>>S,n=S.size(),S="&"+S;
	vector<int> a,b;
	a.push_back(0),b.push_back(0);
	ffor(i,1,n) if(S[i]=='H') a.push_back(i); else b.push_back(i);
	a.push_back(n+1),b.push_back(n+1);
	ffor(i,1,n) ans[i][i]=0;
	ffor(i,1,(int)a.size()-3) {
		int l=i,r=i+1;
		acnt=asum=0,memset(cnt,0,sizeof(cnt)),memset(sum,0,sizeof(sum));
		while(l>=1&&r<a.size()-1) {
			update(a[l]+a[r],a[l]+a[r]);
			ffor(ll,a[l-1]+1,a[l]) ffor(rr,a[r],a[r+1]-1) ans[ll][rr]=calc(ll+rr);
			l--,r++;
		}
	}
	ffor(i,1,(int)b.size()-3) {
		int l=i,r=i+1;
		acnt=asum=0,memset(cnt,0,sizeof(cnt)),memset(sum,0,sizeof(sum));
		while(l>=1&&r<b.size()-1) {
			update(b[l]+b[r],b[l]+b[r]);
			ffor(ll,b[l-1]+1,b[l]) ffor(rr,b[r],b[r+1]-1) ans[ll][rr]=calc(ll+rr);
			l--,r++;
		}
	}
	ffor(i,0,a.size()-2) ffor(l,a[i]+1,a[i+1]-1) ffor(r,l,a[i+1]-1) ans[l][r]=0;
	ffor(i,0,b.size()-2) ffor(l,b[i]+1,b[i+1]-1) ffor(r,l,b[i+1]-1) ans[l][r]=0;
	long long res=0;
	ffor(i,1,n) ffor(j,i,n) res+=ans[i][j];
	cout<<res;
	return 0;
}
```

不过这太不牛了，能做到 $O(n^2)$ 吗？

发现在查询的过程中，所需要的值的移动量之和为 $O(n^2)$。那么直接使用类似莫队的技巧，直接微调即可。代码懒得写。

---

