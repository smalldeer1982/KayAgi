# [POI 2007] EGZ-Driving Exam

## 题目描述

**译自 POI 2007 Stage 3. Day 2「[Egzamin na prawo jazdy](https://szkopul.edu.pl/problemset/problem/nLSrpyeJ1JnFGbBORYVVavIQ/site/?key=statement)」**

Byteotian 驾驶考试所在的区域有 $n$ 条互相平行的自南向北的道路，每条道路长为 $m$ 米，且在同一条水平线上开始、结束。另有 $p$ 条自东向西或自西向东的道路，连接两条相邻的自南向北的道路。注意可能有两条自东向西的道路和自西向东的道路重合，相当于一条双向道路。

![](https://cdn.luogu.com.cn/upload/pic/6981.png)

上图为 $n=4,m=3,p=5$ 的例子。

考生可以选择一条自南向北的道路作为起始点，且从该道路开始必须能到达其它所有的道路。

你需要添加至多 $k$ 条东西向的道路，使得满足条件的起始点最多。

## 样例 #1

### 输入

```
4 3 5 2
2 0 0
2 2 1
3 3 1
1 1 1
3 3 0```

### 输出

```
2```

# 题解

## 作者：Ark_ (赞：5)

能从$i$走到所有跑道 相当于 能从$i$走到$1$和$n$.
边反向后就相当于 能从$1$和$n$走到$i$.

为了方便叙述,把$1$\~$n$叫做x坐标,$1$\~$(m+1)$叫做y坐标.

然后我们将图**上下翻转**($y$坐标)后,能从$1$走到$i$的话一定会经过$i-1$条向右的边,且这些边的$y$坐标不下降.

那么我们设$fl[i]$表示从$1$走到$i$最小加边数量,那么有
$fl[i]=i-1-LIS$

这里的$LIS$是x坐标在$1$~$(i-1)$的边的$y$坐标形成的最长不下降子序列长度.

这个东西可以$O(nlogn)$预处理出来,同时我们反着处理一遍向左的边就能处理出从$n$走到$i$的最小加边数量$fr[i]$.

最终答案一定是一段连续的区间$[i,j]$.因为如果两个满足答案的位置不相邻,体现在边的$y$坐标序列上就是两座山峰,中间的值也一定可以形成山峰.如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190328185259756.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0lrZTk0MDA2Nzg5Mw==,size_16,color_FFFFFF,t_70)
假设两座山峰为$L,R$.那么对于在$[L,R]$中的点,如果在M左边就取①上的点,如果在M右边就取②上的点,这样也一定能够形成总长为$n$的山峰.

所以说要求的就是区间$[i,j]$满足$fr[i]+fl[j]<=k$的最长区间长度.

由于$fr[i]$递减,$fl[i]$递增,那么枚举$i$增加的时候,为了让区间长度尽量大,$j$也一定不会变小.那么就开个变量存一下当前$j$的位置然后往后面挪动就行了.$O(n)$

总时间复杂度$O(nlogn)$.

注意这道题要减去原本就能够被$1,n$都到达的跑道的数量.
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
char cb[1<<15],*cs=cb,*ct=cb;
#define getc() (cs==ct&&(ct=(cs=cb)+fread(cb,1,1<<15,stdin),cs==ct)?0:*cs++)
template<class T>inline void read(T &res) {
	char ch; int flg = 1; for(;!isdigit(ch=getc());)if(ch=='-')flg=-flg;
	for(res=ch-'0';isdigit(ch=getc());res=res*10+ch-'0'); res*=flg;
}
const int MAXN = 100005;
int n, m, p, k, T[MAXN], fl[MAXN], fr[MAXN];
vector<pair<int,int> >el[MAXN], er[MAXN];
inline void chkmax(int &x, int y) { if(y > x) x = y; };
inline void upd(int x, int val) {
	while(x <= m) chkmax(T[x], val), x += x&-x;
}
inline int qsum(int x) { int re = 0;
	while(x) chkmax(re, T[x]), x -= x&-x;
	return re;
}
int main() {
	read(n), read(m), read(p), read(k); ++m;
	for(int i = 1, x, y, z; i <= p; ++i) {
		read(x), read(y), read(z); y = m-y;
		if(z) el[x+1].push_back(make_pair(y, 0));
		else er[x].push_back(make_pair(y, 0));
		//这里的z=1和z=0两种边,将哪一种看作向左的边其实无所谓(图的左右翻转不影响答案)
		//只要题目中给出的不同的两种边相对关系固定就行
	}
	int LIS = 0;
	for(int i = 2; i <= n; ++i) {
		
		for(int j = 0, siz = el[i].size(); j < siz; ++j)
			chkmax(LIS, el[i][j].second = qsum(el[i][j].first) + 1);
		fl[i] = i - 1 - LIS;
		for(int j = 0, siz = el[i].size(); j < siz; ++j)
			upd(el[i][j].first, el[i][j].second);
	}
	for(int i = 1; i <= m; ++i) T[i] = 0;
	LIS = 0;
	for(int i = n-1; i >= 1; --i) {
		for(int j = 0, siz = er[i].size(); j < siz; ++j)
			chkmax(LIS, er[i][j].second = qsum(er[i][j].first) + 1);
		fr[i] = n - i - LIS;
		for(int j = 0, siz = er[i].size(); j < siz; ++j)
			upd(er[i][j].first, er[i][j].second);
	}
	int j = 1, ans = 0, cnt = 0;
	for(int i = 1; i <= n; ++i) {
		while(j <= n && fr[i] + fl[j] <= k) ++j;
		chkmax(ans, j - i);
		if(!fl[i] && !fr[i]) ++cnt;
	}
	//printf("ans = %d\n", ans);
	printf("%d\n", ans-cnt);
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：3)

树状数组优化 DP。

显然，如果 $i$ 能到 $1$，那么 $j(1\le j<i)$ 也能到 $1$；

同理，如果 $i$ 能到 $n$，那么 $j(i<j\le n)$ 也能到 $n$。

定义 $l_i$ 表示从 $i$ 到 $1$ 至少要加多少条边，$r_i$ 表示从 $i$ 到 $n$ 至少要加多少条边。

答案为 $\left[\max\limits_{i=1}^{n}\max\limits_{j=1}^{n}[r_j\le k-l_i]i-j+1\right]-\sum\limits_{i=1}^{n}[l_i=r_i=0]$。用一个指针维护就可以了。

考虑将 $l,r$ 分开求。

我们从上到下，从左到右枚举每一条边，转移方程为 $l_i=\min\limits_{j=1}^{i-1}(l_j+i-j-1)$。将贡献拆一下，用树状数组维护 $(l_i-i)$ 的前缀最小值，每次算完后更新树状数组即可。$r_i$ 同理。

复杂度 $O(n\log n)$。注意初始值等细节。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,len,m,k,ta,tb,c[N],f[N],g[N];
struct node{int x,h;node(int x=0,int h=0):x(x),h(h){}}a[N],b[N];
inline bool cmp(node x,node y){return x.h==y.h?x.x<y.x:x.h>y.h;}
inline bool cmp2(node x,node y){return x.h==y.h?x.x>y.x:x.h>y.h;}
inline int lbt(int x){return x&(-x);}
inline void upd(int i,int v){for(;i<=n;i+=lbt(i))c[i]=min(c[i],v);}
inline int get(int i){int res=1e9;for(;i;i-=lbt(i))res=min(res,c[i]);return res;}
int main(){
  cin>>n>>len>>m>>k;
  for(int i=1;i<=m;++i){
    int x=read(),w=read(),d=read();++w;
    if(!d)a[++ta]=node(x,w);
    else b[++tb]=node(x+1,w);
  }
  sort(a+1,a+ta+1,cmp2);sort(b+1,b+tb+1,cmp);
  memset(c,-1,sizeof(c));
  for(int i=1;i<=n;++i)f[i]=i-1;
  for(int i=1;i<=tb;++i){
    int x=b[i].x;
    f[x]=get(x-1)+x-1;
    upd(x,f[x]-x);
  }
  for(int i=1;i<=n;++i)f[i]=min(f[i],get(i-1)+i);
  memset(c,-1,sizeof(c));
  for(int i=1;i<=n;++i)g[i]=n-i;
  for(int i=1;i<=ta;++i){
    int x=n-a[i].x+1;
    g[a[i].x]=get(x-1)+x-1;
    upd(x,g[a[i].x]-x);
  }
  for(int i=1;i<=n;++i)g[i]=min(g[i],get(n-i)+n-i+1);
  int tmp=0;
  for(int i=1;i<=n;++i){
    if(!f[i]&&!g[i]){
      ++tmp;
    }
  }
  int cur=1,ans=0;
  for(int i=1;i<=n;++i){
    int t=k-f[i];
    while(cur<=n&&g[cur]>t)++cur;
    ans=max(ans,i-cur+1-tmp);
  }
  cout<<ans<<endl;
  return 0;
}

```


---

## 作者：Alex_Wei (赞：1)

> [P3463 [POI2007]EGZ-Driving Exam](https://www.luogu.com.cn/problem/P3463)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/poi.html)。

关键性质：如果 $i$ 能到最左边，那么 $i - 1$ 也能。因此，能够到达所有道路的初始位置一定是一段区间 $[l, r]$，满足 $1\sim r$ 能到最左边但 $r + 1$ 不能，且 $l \sim n$ 能到最右边但 $l - 1$ 不能。

设 $pre_i$ 表示使 $1\sim i$ 能到最左边，最少需要修建多少条路。明眼人可以看出这是 $i$ 减去 $1\sim i$ 的 LDS，但是我没有看出来（大雾）。提供一个新的思路：考虑枚举从 $i$ 向左边的所有道路，设其高度为 $k$，我们设 $f_{i, k}$ 表示 $i\to i - 1$ 走的道路的高度为 $k$ 时，走到 $1$ 最少需要新建多少条路。再枚举下一步走的 **原有** 的道路是哪一条，有转移方程
$$
f_{i, k} = \min_{1\leq j < i\land  p \geq k} f_{j, p} + (i - j - 1)
$$
初始值 $f_{1, m} = 0$。后面的 $i - j - 1$ 是因为根据定义，从 $i - 1$ 到 $j$ 走的都不是原有道路，因此要新建 $i - j - 1$ 条道路。$p \geq k$ 的原因显然。将贡献拆成 $(f_{j, p} - j) + (i - 1)$，变成一个经典的二维数点，$i$ 的有序性（从小到大枚举位置）自然地使用扫描线，把问题降了一维。我们需要支持单点修改，以及查询后缀最小值。由于查的是后缀，信息不需要可减，所以树状数组维护即可。而 $pre_i$ 显然就是 $\min f_{i, k}$。

对于 $suf_i$ 同理，转移方程变成了 $f_{i, k} = \min\limits_{i < j \leq n \land p\geq k} f_{j, p} + (j - i - 1)$，同样用 BIT 维护。

根据一开始的结论，区间 $[l, r]$ 合法当且仅当 $suf_l + pre_r \leq k$，因为向左边和向右边的道路独立，$suf_l$ 和 $pre_r$ 只是做简单的加法。注意到 $pre$ 具有单调不降，$suf$ 具有单调不升的性质，因此考虑按从小到大的顺序枚举 $r$，合法的 $l$ 随着 $r$ 的递增，显然单调不减，只需用指针维护即可，该部分时间复杂度线性。

总时间复杂度是树状数组的线性对数。实际上 LIS/LDS 和我的动态规划应该是在干同一件事情 qwq，只不过我想复杂了。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}
#define sor(x) sort(x.begin(), x.end())
const int N = 1e5 + 5;
int n, m, p, k, ans, origin, pre[N], suf[N];
vector <int> lft[N], rt[N];
struct BIT {
	int c[N];
	void init() {memset(c, 0x3f, N << 2);}
	void modify(int x, int v) {while(x) c[x] = min(c[x], v), x -= x & -x;}
	int query(int x) {int s = N; while(x <= m + 1) s = min(s, c[x]), x += x & -x; return s;}
} tr;

int main() {
	cin >> n >> m >> p >> k;
	for(int i = 1; i <= p; i++) {
		int n = read(), m = read(), d = read();
		if(d) lft[n + 1].push_back(m + 1); else rt[n].push_back(m + 1);
	} for(int i = 1; i <= n; i++) sor(lft[i]), sor(rt[i]);
	for(int i = (tr.init(), tr.modify(m + 1, -1), 2); i <= n; i++) {
		for(int it : lft[i]) tr.modify(it, tr.query(it) - 1);
		pre[i] = tr.query(1) + i;
	} for(int i = (tr.init(), tr.modify(m + 1, n), n - 1); i; i--) {
		for(int it : rt[i]) tr.modify(it, tr.query(it) - 1);
		suf[i] = tr.query(1) - i;
	} for(int i = 1; i <= n; i++) origin += !pre[i] && !suf[i];
	for(int i = 1, l = 1; i <= n; i++) {
		while(l <= i && pre[i] + suf[l] > k) l++;
		ans = max(ans, i - l + 1);
	} cout << ans - origin << endl;
	return 0;
}
```

---

## 作者：VioletIsMyLove (赞：1)

部分内容为了方便出自Ark_的题解，因为其实都差不多。
能从 $i$ 走到所有跑道相当于能从i走到 $$1 和 $n$,边反向后就相当于能从 $1$ 和 $n$ 走到 $i$ ;

为了方便叙述,把 $1-n$ 叫做 $x$ 坐标,$1-(m+1)$ 叫做 $y$ 坐标.

然后我们将图上下翻转( $y$ 坐标)后,能从 $1$ 走到 $i$ 的话一定会经过前 $i-1$ 条向右的边,且这些边的 $y$ 坐标不下降（从左往右看）.

那么我们设 $F[0][i]$ 表示从 $1$ 走到 $i$ 最少加边数量,那么有 $F[0][i]=i-1-LIS$；

这里的 $LIS$ 是 $x$ 坐标在 $1-(i-1)$ 的边的 y 坐标形成的最长不下降子序列长度.

$LIS$ 可以 $O(nlogn)$ 预处理出来,同时我们反着处理一遍向左的边就能处理出从 $n$ 走到 $i$ 的最小加边数量 $F[1][i]$.

其实 $F[0][i]$ 的值从左往右看是单调不降的，$F[1][i]$ 的值从右往左看也依然是单调不降的

最后一趟 $O(n)$ 的枚举即可，因为 $F[1][i]$ 单调不降(从后往前看)，所以再上一次的基础之上就OK。

Code:

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,m,p,k,Ans,tot,T[maxn],F[2][maxn],son[2][maxn],nxt[2][maxn],lnk[2][maxn],cnt[2],opt[2][maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+ch-'0',ch=getchar();
	return ret*f;
}
void add_e(int a,int x,int y){son[a][++cnt[a]]=y;nxt[a][cnt[a]]=lnk[a][x];lnk[a][x]=cnt[a];}
void add(int x,int val){
	for (;x<=m;x+=x&-x) T[x]=max(T[x],val);
}
int Ask(int x){
	int re=0;
	for (;x;x-=x&-x) re=max(re,T[x]);
    return re;
}
int main() {
    n=read(),m=read()+1,p=read(),k=read();
    for (int i=1;i<=p;i++) {
        int x=read(),y=m-read(),z=read();
        if (z) add_e(0,x+1,y);else add_e(1,x,y);
    }
    int LIS=0;
    for (int i=2;i<=n;i++){
    	for (int j=lnk[0][i];j;j=nxt[0][j]) LIS=max(LIS,opt[0][son[0][j]]=Ask(son[0][j])+1);
        F[0][i]=i-1-LIS;
        for (int j=lnk[0][i];j;j=nxt[0][j]) add(son[0][j],opt[0][son[0][j]]);
    }
    memset(T,0,sizeof T);LIS=0;
    for (int i=n-1;i;i--){
    	for (int j=lnk[1][i];j;j=nxt[1][j]) LIS=max(LIS,opt[1][son[1][j]]=Ask(son[1][j])+1);
        F[1][i]=n-i-LIS;
        for (int j=lnk[1][i];j;j=nxt[1][j]) add(son[1][j],opt[1][son[1][j]]);
    }
    int j=0,L,R;
    for (int i=1;i<=n;i++) {
        while (j<n&&F[1][i]+F[0][j+1]<=k) j++;//此处优化的原理F[1][i]>=F[1][i+1],故j从上一次继续就OK，满足i的所有j，依然满足i+1
        if (j-i+1>Ans) Ans=j-i+1,L=i,R=j;//肯定挑选一块连续区间的大的啊 
    }
    for (int i=L;i<=R;i++) Ans-=!F[0][i]&&!F[1][i];
    printf("%d\n",Ans);
    return 0;
}
```


---

## 作者：Adove (赞：1)

能到达所有路的充要条件是能到达左右两端的路

用vector反向建边对每条路左右分别求个最长不上升子序列

预处理出每条路向左向右分别需要多建多少路才能到达最左端和最右端

然后跑个$\Theta(n)$的尺取法就可以了

本题最长不上升子序列用vector+zkw线段树比二分更加好想？

原来标程的`solve`函数尺取时出锅~~（但是居然AC了~~

~~感谢我自己回来看题解发现看不懂~~

现在这题解是真题解了

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
#include"vector"
using namespace std;

const int MAXN=1<<17;

int n,m,P,K,np;
int f[2][MAXN];
int tree[MAXN<<1];
struct rpg{bool kd;int h,fl,fr;};
vector<rpg> vec[MAXN];

int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
	return x;
}

void calcl()
{
	for(int i=1;i<n;++i){
		for(int j=0;j<vec[i].size();++j){
			if(!vec[i][j].kd){
				int l=MAXN+vec[i][j].h-1,r=MAXN+m+2,maxn=0;
				while(l^r^1){
					if(~l&1) maxn=max(maxn,tree[l^1]);
					if(r&1) maxn=max(maxn,tree[r^1]);
					l>>=1;r>>=1;
				}vec[i][j].fl=maxn+1;
			}
		}for(int j=0;j<vec[i].size();++j){
			if(!vec[i][j].kd){
				for(int k=MAXN+vec[i][j].h;k;k>>=1){
					tree[k]=max(tree[k],vec[i][j].fl);
				}
			}
		}int l=MAXN,r=MAXN+m+2,maxn=0;
		while(l^r^1){
			if(~l&1) maxn=max(maxn,tree[l^1]);
			if(r&1) maxn=max(maxn,tree[r&1]);
			l>>=1,r>>=1;
		}f[0][i+1]=maxn;
	}return;
}

void calcr()
{
	for(int i=n;i>1;--i){
		for(int j=0;j<vec[i].size();++j){
			if(vec[i][j].kd){
				int l=MAXN+vec[i][j].h-1,r=MAXN+m+2,maxn=0;
				while(l^r^1){
					if(~l&1) maxn=max(maxn,tree[l^1]);
					if(r&1) maxn=max(maxn,tree[r^1]);
					l>>=1;r>>=1;
				}vec[i][j].fr=maxn+1;
			}
		}for(int j=0;j<vec[i].size();++j){
			if(vec[i][j].kd){
				for(int k=MAXN+vec[i][j].h;k;k>>=1){
					tree[k]=max(tree[k],vec[i][j].fr);
				}
			}
		}int l=MAXN,r=MAXN+m+2,maxn=0;
		while(l^r^1){
			if(~l&1) maxn=max(maxn,tree[l^1]);
			if(r&1) maxn=max(maxn,tree[r&1]);
			l>>=1,r>>=1;
		}f[1][i-1]=maxn;
	}return;
}

void init()
{
	n=read(),m=read(),P=read(),K=read();
	for(int i=1;i<=P;++i){
		int x=read(),y=read(),z=read();
		if(z) vec[x].push_back((rpg){z^1,y+1});
		else vec[x+1].push_back((rpg){z^1,y+1});
	}calcl();memset(tree,0,sizeof(tree));calcr();
	for(int i=1;i<=n;++i) f[0][i]=i-f[0][i]-1,f[1][i]=n-i-f[1][i];
	return;
}

void solve()
{
	int ans=0,ct=0,cnt=0;
	for(int i=1;i<=n;++i){
		while(ct+1<=n&&f[1][i]+f[0][ct+1]<=K){
			++ct;
			if(!f[0][ct]&&!f[1][ct]) ++cnt;
		}ans=max(ans,ct-i+1-cnt);
		if(!f[0][i]&&!f[1][i]) --cnt;
	}printf("%d\n",ans);
	return;
}

int main()
{
	init();
	solve();
	return 0;
}
```

---

