# [AGC052D] Equal LIS

## 题目描述

给定一个 $1$ 到 $N$ 的整数的排列 $P_1,\ P_2,\ \dots,\ P_N$。请判断是否可以将其分成两个子序列，使得这两个子序列的最长上升子序列的长度相等。

形式化地说，目标是找到满足以下所有条件的两个整数序列 $a,\ b$：

- $a,\ b$ 都是 $P$ 的子序列。
- 每个整数 $i=1,2,\cdots,N$ 恰好只在 $a$ 或 $b$ 中出现一次。
- （$a$ 的最长上升子序列的长度）$=$（$b$ 的最长上升子序列的长度）。

请判断目标是否可以达成。

有 $T$ 组测试数据，请分别作答。

## 说明/提示

### 数据范围

- $1\leq T\leq 2\times 10^5$
- $1\leq N\leq 2\times 10^5$
- $P_1,\ P_2,\ \dots,\ P_N$ 是 $1$ 到 $N$ 的一个排列。
- 所有测试数据中 $N$ 的总和不超过 $2\times 10^5$。

### 样例解释 1

将 $[1,\ 3,\ 5,\ 2,\ 4]$ 分为 $[1,\ 5]$ 和 $[3,\ 2,\ 4]$，两者的最长上升子序列长度均为 $2$。对于 $[2,\ 3,\ 4,\ 5,\ 6,\ 1]$，无法分成两个最长上升子序列长度相等的子序列。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1
1
2
2 1
3
1 2 3
5
1 3 5 2 4
6
2 3 4 5 6 1```

### 输出

```
NO
YES
NO
YES
NO```

# 题解

## 作者：huangzirui (赞：5)

记 $f(x)$ 表示以 $x$ 结尾的 $\text{LIS}$ 最大长度。

考虑如果原序列的 $\text{LIS}=2k$，那么只要按照是否有 $f(x)\leqslant k$ 分成两类即可。

否则令 $\text{LIS}=2k+1$，此时我们尝试能否把原序列分成两份，每份的 $\text{LIS}$ 长度是 $k+1$。

容易发现，只要原序列中存在一个元素，它不在被选出的某个最长 $\text{LIS}$ 中，且存在一个长度为 $k+1$ 的上升子序列包括它，那么就能构造。

记一个满足如上条件的元素为 $a_x$，包含 $a_x$ 的一个上升子序列为 $a_{p_1},\cdots,a_{p_{k+1}}$。我们按如下的方式分配：

首先我们把个长度为 $k+1$ 的上升子序列全选入第一个序列。

对于某个其他的元素 $y$，如果满足 $f(y)\not=f(a_{p_i})$，我们就把它选入第二个序列。否则如果 $f(y)=f(a_x)$，我们也把它放进第二个序列。其他的情况我们就把它放进第一个序列。

考虑第一个序列，显然存在长度为 $k+1$ 的上升子序列，然而只存在 $k+1$ 种不同的 $f$，因此其 $\text{LIS}$ 为 $k+1$。

同理可以知道第二个序列的 $\text{LIS}$ 也为 $k+1$。

如果不存在这样的 $a_x$，则显然无解。

---

## 作者：云浅知处 (赞：3)

考虑原序列的 LIS 为 $L$，显然分出的两个子序列，LIS 较大的那一个至少为 $\lceil\frac{L}{2}\rceil$。

如果 $L$ 是偶数，我们算出 $f(i)$ 表示以 $i$ 结尾的 LIS 长度，然后把 $f(i)\le \frac{L}{2}$ 的都放进第一个子序列。那么第一个子序列的 LIS 长度恰好为 $\frac{L}{2}$，考虑第二个子序列，发现其 LIS 长度也恰好是 $\frac{L}{2}$（因为一个上升子序列的 $f$ 一定是严格递增的，而第二个子序列中所有的 $f$ 都在 $(\frac{L}{2},L]$ 之间，所以 LIS $\le \frac{L}{2}$；另一方面显然全局 LIS 的后一半都在这个子序列内，所以可以取到）。

现在考虑 $L$ 是奇数怎么做。设 $L=2K+1$，那么两个子序列的 LIS 长度需要至少为 $K+1$。于是任取一个长度为 $2K+1$ 的 LIS，这两个子序列中至少有一个得包含至少一个不在这个 LIS 中的数。

那么我们只要能选出一个长度为 $2K+1$ 的 LIS，并找到一个不在这个 LIS 中的数，满足存在一个长度为 $K+1$ 的上升子序列包含它，设这个数是 $x$，我们做如下的构造：

- 设 $i_1,i_2,\cdots,i_{K+1}$ 为这个上升子序列的下标。首先把 $i_1,i_2,\cdots,i_{K+1}$ 都放进第一个子序列。
- 接下来对于某个 $j$，如果 $f(j)$（以 $j$ 结尾的最长上升子序列长度）和某个 $f(i_p)$（$1\le p\le K+1$）都不同，或者 $f(j)=f(x)$ 且 $j\neq x$，我们就把他放在第二个子序列；否则，我们把它放进第一个子序列。

现在考虑第一个子序列，其 LIS 长度一定 $\ge K+1$；由于其中的 $f$ 值只有 $K+1$ 种，因此一定凑不出来长度为 $K+2$ 的上升子序列，于是其 LIS 长度恰为 $K+1$。考虑第二个子序列，由于全局 LIS 中剩下的 $K+1$ 个数都在这里面，因此其 LIS 长度也至少为 $K+1$；同时这里的 $f$ 值也只剩下 $K+1$ 种，因此构造成立。

现在考虑怎么判断这个条件是否成立，那么相当于除去 LIS 里面的 $2K+1$ 个数之外，还得至少存在一个数，包含它的最长上升子序列长度 $\ge K+1$。

我们算出 $w_i$ 表示包含下标 $i$ 的最长上升子序列长度，那么只要 $w_i\ge K+1$ 的数至少有 $2K+2$ 个，就能找到一种方案；否则一定无解。对于 $w$ 的计算，算出 $f_i,g_i$ 表示以 $i$ 结尾、开头的 LIS 长度，则 $w_i=f_i+g_i-1$。

$f,g$ 容易使用数据结构优化计算。综上，本题在 $O(N\log N)$ 时间内解决。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=2e5+5;
int n;
struct BIT{
	int c[N];
	void clear(){for(int i=1;i<=n;i++)c[i]=0;}
	int lowbit(int x){return x&(-x);}
	void mdf(int x,int v){for(int i=x;i<=n;i+=lowbit(i))cmax(c[i],v);}
	int qmax(int x){int res=0;for(int i=x;i;i-=lowbit(i))cmax(res,c[i]);return res;}
}T;

void solve(){
	n=read();vector<int>a(n+1);
	for(int i=1;i<=n;i++)a[i]=read();

	vector<int>f(n+1),g(n+1),w(n+1);
	for(int i=1;i<=n;i++)f[i]=T.qmax(a[i])+1,T.mdf(a[i],f[i]);T.clear();
	for(int i=n;i>=1;i--)g[i]=T.qmax(n-a[i]+1)+1,T.mdf(n-a[i]+1,g[i]);T.clear();

	int L=0;
	for(int i=1;i<=n;i++)w[i]=f[i]+g[i]-1,cmax(L,w[i]);
	if(L%2==0)return puts("YES"),void();

	int cnt=0;
	for(int i=1;i<=n;i++)if(w[i]>=(L+1)/2)cnt++;
	if(cnt>=L+1)puts("YES");
	else puts("NO");
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	int tt=read();while(tt--)solve();

	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

主播主播，你的讨论太吃脑子了，有没有更容易理解的方法？

有的兄弟，有的！

考虑使用 Dilworth 定理来刻画 LIS。使用 Dilworth 定理的好处是，如果你构造的集合恰有一个长度为 $k$ 的上升子序列，且恰好能分成不超过 $k$ 条下降子序列，那么知道了其 LIS 恰好为 $k$。

当原序列的 LIS 是偶数的时候，设 $m$ 为 LIS 长度。那么原序列划分为 $m$ 条反链，你选出 $\dfrac{m}{2}$ 个反链放到一个集合即可。

当原序列的 LIS 是奇数的时候，那么必然有一个不在原序列的 LIS 上（可能存在多个 LIS，随便选一个就行）的点 $u$，使得他在集合 $A$ 的 LIS 中。

显然要求经过 $u$ 的 LIS 长度至少为 $\dfrac{m+1}{2}$。而发现这样一定有解，因为你随便选出 $\dfrac{m-1}{2}$ 个在经过 $u$ 的 LIS 上的数，选出他们所在的反链，然后加上孤点 $u$。容易证明这是充要的。

代码（带上了构造方案，因为模拟赛考的是这个）

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,tot,p[MAXN],lst[MAXN],rev[MAXN],ans[MAXN],ar[MAXN],bel[MAXN],cov[MAXN];
vector<int> chain[MAXN];
void mark(int u,int col) {
	ans[u]=col;
	if(lst[u]) mark(lst[u],col);
	return ;
}
void get(int u,int id) {
	chain[id].push_back(u);
	if(lst[u]) get(lst[u],id);
	return ;
}
pair<int,int> tr[MAXN]; int f[MAXN],g[MAXN],frm[MAXN],nxt[MAXN],flg[MAXN];

void update(int pos,pair<int,int> mx) {while(pos<=n) tr[pos]=max(tr[pos],mx),pos+=pos&-pos;return ;}
pair<int,int> query(int pos) {pair<int,int> mx={-1,0};while(pos) mx=max(mx,tr[pos]),pos-=pos&-pos;return mx;}
vector<int> get_lis(void) {
	ffor(i,1,n) tr[i]={-1,0};
	ffor(i,1,n) {
		f[i]=1,frm[i]=0;
		auto pr=query(p[i]);
		if(pr.first>=1) f[i]=pr.first+1,frm[i]=pr.second;
		update(p[i],{f[i],i});
	}
	int mx=*max_element(f+1,f+n+1);
	vector<int> res;
	ffor(u,1,n) if(f[u]==mx) {
		while(u) res.push_back(u),u=frm[u];
		reverse(res.begin(),res.end());
		return res;
	}
}
void calc_nxt(void) {
	ffor(i,1,n) tr[i]={-1,0};
	roff(i,n,1) {
		g[i]=1,nxt[i]=n+1;
		auto pr=query(n-p[i]+1);
		if(pr.first>=1) g[i]=pr.first+1,nxt[i]=pr.second;
		update(n-p[i]+1,{g[i],i});
	}
	return ;
}
int main() {
	freopen("newzealand.in","r",stdin);
	freopen("newzealand.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>p[i],rev[p[i]]=i,ans[i]=0,lst[i]=0;
		tot=0;
		ffor(i,1,n) {
			int id=lower_bound(ar+1,ar+tot+1,p[i])-ar;
			if(id==tot+1) ++tot,ar[tot]=p[i];
			else lst[i]=rev[ar[id]],ar[id]=p[i];
		}
		if(tot%2==0) {
			ffor(i,1,tot) {
				if(i<=tot/2) mark(rev[ar[i]],0);
				else mark(rev[ar[i]],1);
			}
			cout<<"YES\n";
			ffor(i,1,n) cout<<ans[i]<<' ';
			cout<<'\n';
			continue ;
		}
		ffor(i,1,tot) chain[i].clear(),get(rev[ar[i]],i);
		ffor(i,1,tot) for(auto id:chain[i]) bel[id]=i;
		
		auto vc=get_lis();
		ffor(i,1,n) flg[i]=0;
		for(auto id:vc) flg[id]=1;
		
		calc_nxt();
		int eq=0;
		ffor(i,1,n) if(!flg[i]&&f[i]+g[i]-1>=(tot+1)/2) {
			vector<int> Z;
			int u=frm[i];
			while(u) Z.push_back(u),u=frm[u];
			u=nxt[i];
			while(u<=n) Z.push_back(u),u=nxt[u];
			cout<<"YES\n";
			ffor(j,1,(tot-1)/2) {
				int id=bel[Z[j-1]];
				for(auto c:chain[id]) ans[c]=1;
			}
			ans[i]=1;
			ffor(j,1,n) cout<<ans[j]<<' '; cout<<'\n',eq=1;
			break ;
		}
		if(!eq) cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：2)

模拟赛考了这题的加强版，我被肘飞了。模拟赛那题除了要判定是否合法之外，还要求构造。感觉还是有迹可循的啊。

这题一个很重要的 Trick 就是 LIS 的分层，我们设 $f_i$ 表示以 $p_i$ 结尾的 LIS 的长度。然后按照 $f_i$ 进行分组，值相同的在一组。可以发现 $f_i$ 相同的元素内部不会形成 LIS，它们的结构形如若干逆序对，如果是顺序对的话，就会有一个 $f$ 值更新另外一个导致它们的 $f$ 值不同。

本质是 Dilworth 定理，紫色的为最长链。淡蓝色的若干反链，同一条淡蓝色线上的 $f$ 值相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/b9eks6fa.png)

令 LIS 长度为 $2k/2k+1$。

这个时候我们就可以轻松解决 LIS 为偶数的情况了，因为这样子的蓝线个数也为偶数，随便选 $k$ 组放在一起，另外 $k$ 组放在一起。由于组内不会产生贡献，所有两个部分的 LIS 都是 $k$。

对于 LIS 为 $2k+1$ 的情况有点难做，考虑让两组的长度都是 $k+1$。可是我们只能划分出 $k$ 组合上 $k+1$ 的情况。于是考虑“借”一个元素来完成这个构造，如果如图深蓝色部分的选择，我们选择 $k$ 条浅蓝色的链的全部元素，然后借用另一条浅蓝色线上的一个元素就行了，这样子这一个子序列的 LIS 为 $k+1$，另一个子序列由于包含了 $k+1$ 组，所以 LIS 也为 $k+1$。

选择的这个元素必须满足其所在组的大小 $>1$（否则我们取完这个元素之后，这个组就空了，没法贡献给另外一个子序列了），且存在一个长度为 $k+1$ 的上升子序列包含它。当然如果不存在这个元素那就无解了。

使用树状数组维护 LIS，时间复杂度 $O(n\log n)$。以下代码包含了构造两个子序列的部分。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb emplace_back
#define mp make_pair
using namespace std;
const int maxn=2e5+10;
void cmin(int &x,int y){ x=x<y?x:y; }
void cmax(int &x,int y){ x=x>y?x:y; }
vector<int> vec; int ban[maxn];
int n,vis[maxn],p[maxn],f[maxn],g[maxn],cnt[maxn];
struct BIT{
	int c[maxn];
	int lowbit(int x){ return x&-x; }
	void init(){ for(int i=1;i<=n;i++) c[i]=0; }
	void modify(int x,int v){ for(;x<=n;x+=lowbit(x)) cmax(c[x],v); }
	int query(int x){ int res=0; for(;x;x-=lowbit(x)) cmax(res,c[x]); return res; }
}t;
void init(){ for(int i=1;i<=n;i++) vis[i]=cnt[i]=ban[i]=0; }
void solve(){
	cin>>n; init(); t.init(); int len=0;
	for(int i=1;i<=n;i++){
		cin>>p[i];
		f[i]=t.query(p[i])+1; 
		t.modify(p[i],f[i]);
		cmax(len,f[i]);
	}
	if(len%2==0){
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++)
			if(f[i]<=len/2) cout<<0<<" ";
			else cout<<1<<" "; cout<<endl;
		return ;
	}
	t.init(); int k=(len+1)/2;
	for(int i=n;i>=1;i--){
		g[i]=t.query(n-p[i]+1)+1;
		t.modify(n-p[i]+1,g[i]); 
	}
	for(int i=1;i<=n;i++)
		if(f[i]+g[i]-1==len) cnt[f[i]]++;
	int id=0;
	for(int i=1;i<=n;i++){
		if(f[i]+g[i]-1==len&&cnt[f[i]]==1) continue;
		if(f[i]+g[i]-1>=k) id=i;
	}
	if(!id){ cout<<"NO"<<endl; return ; }
	cout<<"YES"<<endl; 
	int L=f[id]-min(f[id],k)+1,R=g[id]-(k-min(f[id],k));
	ban[f[id]]=1;
	int cur=f[id]-1; vis[id]=1;
	for(int i=id-1;i>=1&&cur>=L;i--)
		if(f[i]==cur) cur--,vis[i]=1,ban[f[i]]=1;
	cur=g[id]-1;
	for(int i=id+1;i<=n&&cur>=R;i++)
		if(g[i]==cur) cur--,vis[i]=1,ban[f[i]]=1;
	for(int i=1;i<=n;i++)
		if(vis[i]) cout<<0<<" ";
		else if(!ban[f[i]]) cout<<1<<" ";
		else if(f[i]==f[id]) cout<<1<<" ";
		else cout<<0<<" "; cout<<endl;
}
int main(){
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：PassName (赞：2)

# AGC052D 题解

[题目传送门 AGC052D](https://www.luogu.com.cn/problem/AT_agc052_d)

## question
给定长为 $n$ 的排列，求是否可以分割成两个 LIS 长度相等的子序列。

## solution
对于一个序列是否能分成两个 LIS 长度相等子序列。我们要注意审题，他说的是两个**长度相等的**对吧。

也就是说，当对于是整体最长上升子序列长度 $len$，$len$ 为偶数，即 `!(len % 2)` 的时候，这个显然是有解的。

然后呢？先不要着急考虑奇数的情况，对于刚才偶数的情况还没有处理完，这个 $len$ 怎么计算呢。设 $f_i$ 是以 $i$ 为结尾的最长上升子序列长度，那么不难得出：

$$len=\max_{1 \le i \le n} f_i$$

计算出 $len$，就解决了偶数的情况。

接下来考虑奇数情况。$g_i$ 表示以 $i$ 为开头的最长上升子序列长度,我们不妨设 $len = 2 \times x + 1$，$x∈N_+$

两个子序列的最长上升子序列长度至少是 $x + 1$，那么，是不是个 最长上升子序列之外的元素，存在某个长为 $x + 1$ 的上升子序列覆盖着它呢？

设这个上升子序列 $P$：$P_1,P_2 \cdots P_{k+1}$

对于一个序列，满足 $f_i≠f_{p_k}, f_i=f_{j≠i}$ 且 $k \le x+1$ 的是选取序列，剩下的为剩余序列。

对于无论是选取序列还是剩余序列，我们发现，有不超过 $x + 1$ 个不同的以 $i$ 为结尾的最长上升子序列长度对吧。所以，对于选取序列，最长上升子序列长度是要不小于 $x + 1$ 的，并且剩余序列的最长上升子序列长度同样要不小于 $x + 1$。

所以，求出 $f_i,g_i$，如果 $f_i + g_i \ge len \div 2 + 2$，累计一次答案，如果最后累计结果 $cnt > len$，那么就有解，否则无解。

时空复杂度 $O(n$ $\log$ $n)$

## code
```cpp
int T, n;
int p[N], id[N];
int f[N], g[N];

signed main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (rint i = 1; i <= n; i++)
        {
			cin >> p[i];
		}
        
		for (rint i = 1; i <= n; i++) id[i] = n + 1;
        
        int len = 0;
        
        for (rint i = 1; i <= n; i++)
        {
            f[i] = lower_bound(id + 1, id + n + 1, p[i]) - id;
            id[f[i]] = p[i];
            len = max(len, f[i]);
        }
        if (!(len % 2))
        {
            puts("YES");
            continue;
        }
        
        for (rint i = 1; i <= n; i++) id[i] = n + 1;
        
        for (rint i = n; i != 0; i--)
        {
            g[i] = lower_bound(id + 1, id + n + 1, n - p[i]) - id;
            id[g[i]] = n - p[i];
        }
        
        int cnt = 0;
        for (rint i = 1; i <= n; i++)
        {
			if ((f[i] + g[i]) >= (len / 2 + 2))
			{
				cnt++;
			}
		}
            
        if (cnt > len)
        {
            puts("YES");			
		}
        else
        {
            puts("NO");			
		}
    }
    
    return 0;
}
```

---

