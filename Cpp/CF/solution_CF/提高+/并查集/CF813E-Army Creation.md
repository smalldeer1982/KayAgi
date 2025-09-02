# Army Creation

## 题目描述

As you might remember from our previous rounds, Vova really likes computer games. Now he is playing a strategy game known as Rage of Empires.

In the game Vova can hire $ n $ different warriors; $ i $ th warrior has the type $ a_{i} $ . Vova wants to create a balanced army hiring some subset of warriors. An army is called balanced if for each type of warrior present in the game there are not more than $ k $ warriors of this type in the army. Of course, Vova wants his army to be as large as possible.

To make things more complicated, Vova has to consider $ q $ different plans of creating his army. $ i $ th plan allows him to hire only warriors whose numbers are not less than $ l_{i} $ and not greater than $ r_{i} $ .

Help Vova to determine the largest size of a balanced army for each plan.

Be aware that the plans are given in a modified way. See input section for details.

## 说明/提示

In the first example the real plans are:

1. $ 1 2 $
2. $ 1 6 $
3. $ 6 6 $
4. $ 2 4 $
5. $ 4 6 $

## 样例 #1

### 输入

```
6 2
1 1 1 2 2 2
5
1 6
4 3
1 1
2 6
2 6
```

### 输出

```
2
4
1
3
2
```

# 题解

## 作者：Memory_of_winter (赞：14)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/9978777.html)

**题目大意：**有$n$个数，$q$次询问，每次询问$[l,r]$中最多可以选多少个数使得相同的数最多有$k$个。（$k$在同个测试点中相同）

**题解：**$k$不变，可以预处理出每个数前面的第$k$个相同的数在哪，对于询问区间$[l,r]$，若前面的第$k$个数的位置小于$l$，则可以选择这个数。于是用主席树维护一段值域中数的个数即可



**C++ Code：**

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#define maxn 100010
#define N (maxn * 20)
std::vector<int> pos[maxn];
int n, k, m;
int rt[maxn], V[N], lc[N], rc[N], idx;

void insert(int &rt, int l, int r, int num) {
	lc[++idx] = lc[rt], rc[idx] = rc[rt], V[idx] = V[rt] + 1, rt = idx;
	if (l == r) return ;
	int mid = l + r >> 1;
	if (num <= mid) insert(lc[rt], l, mid, num);
	else insert(rc[rt], mid + 1, r, num);
}
int query(int L, int R, int l, int r, int num) {
	if (r <= num) return V[R] - V[L];
	int mid = l + r >> 1, ans = 0;
	ans = query(lc[L], lc[R], l, mid, num);
	if (num > mid) ans += query(rc[L], rc[R], mid + 1, r, num);
	return ans;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		pos[x].push_back(i);
		int sz = pos[x].size();
		if (sz > k) sz = pos[x][sz - k - 1];
		else sz = 0;
		rt[i] = rt[i - 1];
		insert(rt[i], 0, n, sz);
	}
	scanf("%d", &m);
	int last = 0;
	while (m --> 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + last) % n + 1, r = (r + last) % n + 1;
		if (l > r) std::swap(l, r);
		printf("%d\n", last = query(rt[l - 1], rt[r], 0, n, l - 1));
	}
	return 0;
}

```



---

## 作者：DPair (赞：4)

也是分块，但与另一篇题解实现似乎不太一样。

（~~可能是另一篇我没看懂？~~）

似乎比较好懂。

## 【思路】
~~都说了是分块了~~

首先我们把序列分成 $\sqrt{n}$ 个长度为 $\sqrt{n}$ 的块，这个应该不需要多说。

对于每一个块，我们维护两个东西： $sig[i][x]$ 表示 **前** $i$ **块** 中数字 $x$ 出现的次数。$num[i][j]$ 表示从块 $i$ 一直到块 $j$ 可以选出的数的数量。由于 $k$ 一开始就给定了，这两个数组都是唯一确定的。

现在考虑怎么处理出这两个数组。

对于 $sig$ 数组是比较好处理的，我们记录一个数组 $cnt$ 表示目前位置每一个数的出现次数，然后从 $1$ 到 $n$ 扫一遍，每扫到一个块尾就更新上去。由于块数是 $O(\sqrt{n})$ 的，总复杂度 $O(n\sqrt{n})$ 。

然后是 $num[i][j]$ 数组，我们其实可以把它看成已知 $num[i][j-1]$ 然后处理 $j$ 这个 **散块** 。所以把它和询问一起讲。

然后直接上询问。

首先是一个散块的情况，这个直接暴力不需要多说了吧。一次询问复杂度上界 $O(\sqrt{n})$ 。

唯一一个实现细节就是散块记录出现次数时需要一个 $cnt$ 数组，这个要手动一个一个 $O(\sqrt{n})$ 撤销而不能 $memset$ ，因为 $memset$ 是 $O(n)$ 的。

然后考虑整块带散块。

我们不难发现，由于我们已经预处理好了整块的信息（先这么假设），我们只需要处理两个散块的信息即可。

考虑如何处理散块。

我们只需要在 **扫到的** 数的 $cnt$ 基础上加上一个 $sig$ 处理出的整块信息即可。

这样就可以等效于 **暴力处理完中间的整块后再来处理散块** ，有点类似于打标记的思想。

然后也是需要手动一个一个撤销，以保证单次操作 $O(\sqrt{n})$ 的复杂度。

然后预处理的时候直接套散块的处理方式即可，这部分复杂度应该是 $O(\sqrt{n}\sqrt{n}\sqrt{n})=O(n\sqrt{n})$

然后 $q, n$ 同阶。

所以总复杂度是 $O(n\sqrt{n})$ ，$10^5$ 的数据范围完全没问题。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}

int n, m;
#define MAXN 100005
#define block 333
const int B = MAXN / block + 5;
int a[MAXN];
int sig[B][MAXN], cnt[MAXN];
int num[B][B];
int ans;
int bel[MAXN], fst[B], lst[B];
int main(){
    read(n);read(m);
    for (register int i = 1;i <= n;i ++) read(a[i]);
    for (register int i = 1;i <= n;i ++){
        bel[i] = (i - 1) / block + 1;
        if(!fst[bel[i]]) fst[bel[i]] = i;
        lst[bel[i]] = i;
    }
    for (register int i = 1;i <= n;i ++){//预处理sig数组
        cnt[a[i]] ++;
        if(i == lst[bel[i]]){
            for (register int j = 1;j <= n;j ++) sig[bel[i]][j] = cnt[j];
        }
    }
    memset(cnt, 0, sizeof(cnt));
    for (register int i = 1;i <= bel[n];i ++){//预处理num数组
        for (register int j = i;j <= bel[n];j ++){
            num[i][j] = num[i][j - 1];
            for (register int k = fst[j];k <= lst[j];k ++){
                cnt[a[k]] ++;
                if(sig[j - 1][a[k]] - sig[i - 1][a[k]] + cnt[a[k]] <= m) num[i][j] ++;
            }
            for (register int k = fst[j];k <= lst[j];k ++) cnt[a[k]] --;
        }
    }
    int q;read(q);
    while(q --){
        int l, r;read(l);read(r);
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if(l > r) swap(l, r);
        int L = bel[l], R = bel[r];
        ans = 0;
        if(L == R){
            for (register int i = l;i <= r;i ++){
                cnt[a[i]] ++;
                if(cnt[a[i]] <= m) ans ++;
            }
            for (register int i = l;i <= r;i ++) cnt[a[i]] --;
            fprint(ans, 10);
        }
        else{
            ans = num[L + 1][R - 1];
            for (register int i = l;i <= lst[L];i ++){
                cnt[a[i]] ++;
                if(sig[R - 1][a[i]] - sig[L][a[i]] + cnt[a[i]] <= m) ans ++;
            }
            for (register int i = fst[R];i <= r;i ++){
                cnt[a[i]] ++;
                if(sig[R - 1][a[i]] - sig[L][a[i]] + cnt[a[i]] <= m) ans ++;
            }
            for (register int i = l;i <= lst[L];i ++) cnt[a[i]] --;
            for (register int i = fst[R];i <= r;i ++) cnt[a[i]] --;
            fprint(ans, 10);
        }
    }
}
```

---

## 作者：mrsrz (赞：4)

分块。

记录每个数的前缀出现次数。

令$F[i][j]$表示块$i$到$j$之间出现次数大于$k$的数的**种数**。

$G[i][j]$表示块$i$到$j$之间出现次数大于$k$的数的**总数**。

这个显然可以递推出来。预处理时间复杂度$O(n\sqrt n)$。

然后对于询问，处理边角出现的数在边角的出现次数。

然后，分如下情况：

1. 一个数在块内出现次数不超过$k$，加上边角的出现次数就大于$k$。
2. 一个数在块内出现次数不超过$k$，加上边角的出现次数仍然不超过$k$。
3. 一个数在块内出现次数就超过了$k$，在边角出现。

分别处理一下即可。剩下的用预处理出的$F$和$G$很容易得到答案。

大概具体实现时，先算出块内出现次数不超过$k$的数的总数（中间块的总大小减去$G$的值）。

然后边角处理一下，再加上$F$的值乘$k$即可（最多选$k$个）。

时间复杂度$O(n\sqrt n)$。

~~成功跑到最慢~~

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
#define N 100005
#define siz 317
struct istream{
	inline istream&operator>>(int&d){
		static int c;
		while(!isdigit(c=getchar()));
		for(d=0;isdigit(c);c=getchar())d=(d<<3)+(d<<1)+(c^'0');
		return*this;
	}
}cin;
int n,k,a[N],L[N],R[N],bel[N],blocks,cnt[320][N],m,tot[N];
int F[320][320],G[320][320];
std::vector<int>v;
void block_init(){
	blocks=(n-1)/siz+1;
	for(int i=1;i<=blocks;++i)
	L[i]=R[i-1]+1,R[i]=i*siz;R[blocks]=n;
	for(int i=1;i<=blocks;++i){
		memcpy(cnt[i],cnt[i-1],sizeof*cnt);
		for(int j=L[i];j<=R[i];++j){
			bel[j]=i;
			++cnt[i][a[j]];
		}
		for(int j=1;j<=1e5;++j)if(cnt[i][j]-cnt[i-1][j]>k)++F[i][i],G[i][i]+=cnt[i][j]-cnt[i-1][j];
	}
	static bool vis[N];
	for(int i=1;i<blocks;++i){
		for(int j=i+1;j<=blocks;++j){
			int&F=::F[i][j],&G=::G[i][j];
			F=::F[i][j-1],G=::G[i][j-1];
			for(int p=L[j];p<=R[j];++p)
			if(cnt[j][a[p]]-cnt[i-1][a[p]]>k&&!vis[a[p]]){
				vis[a[p]]=1;
				if(cnt[j-1][a[p]]-cnt[i-1][a[p]]<=k){
					++F;
					G+=cnt[j][a[p]]-cnt[i-1][a[p]];
				}else G+=cnt[j][a[p]]-cnt[j-1][a[p]];
			}
			for(int p=L[j];p<=R[j];++p)vis[a[p]]=0;
		}
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	block_init();
	int ans=0;
	for(cin>>m;m--;){
		int l,r;
		cin>>l>>r;
		l=(l+ans)%n+1,r=(r+ans)%n+1;
		if(l>r)l^=r^=l^=r;
		ans=0;
		if(bel[l]==bel[r]){
			for(int i=l;i<=r;++i)++tot[a[i]];
			for(int i=l;i<=r;++i){
				if(tot[a[i]]>k)ans+=k;else
				ans+=tot[a[i]];
				tot[a[i]]=0;
			}
			printf("%d\n",ans);
		}else{
			int Lblo=bel[l],Rblo=bel[r];
			for(int i=l;i<=R[Lblo];++i)++tot[a[i]];
			for(int i=L[Rblo];i<=r;++i)++tot[a[i]];
			int full=R[Rblo-1]-R[Lblo]-G[Lblo+1][Rblo-1];
			for(int i=l;i<=R[Lblo];++i)
			if(tot[a[i]]){
				if(tot[a[i]]+cnt[Rblo-1][a[i]]-cnt[Lblo][a[i]]>k){
					if(cnt[Rblo-1][a[i]]-cnt[Lblo][a[i]]<=k){
						full-=cnt[Rblo-1][a[i]]-cnt[Lblo][a[i]];
						ans+=k;
					}
				}else ans+=tot[a[i]];
				tot[a[i]]=0;
			}
			for(int i=L[Rblo];i<=r;++i)
			if(tot[a[i]]){
				if(tot[a[i]]+cnt[Rblo-1][a[i]]-cnt[Lblo][a[i]]>k){
					if(cnt[Rblo-1][a[i]]-cnt[Lblo][a[i]]<=k){
						full-=cnt[Rblo-1][a[i]]-cnt[Lblo][a[i]];
						ans+=k;
					}
				}else ans+=tot[a[i]];
				tot[a[i]]=0;
			}
			ans+=F[Lblo+1][Rblo-1]*k+full;
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：chen_qian (赞：2)

首先求的就是这个式子:

$$\sum_{i=1}^{100000} \min(cnt_{i},k)$$

$cnt_i$ 表示数 $i$ 在区间出现次数。

考虑所有的 $cnt_i$ 都小于 $k$ 的情况，发现答案就是区间长度。

那么一般的情况，我们只要相同的保留 $k$ 个。特化到 $k=1$ 的情况，这就是区间数颜色。区间数颜色最经典的思路就是记录前驱然后数点。这里我们就记录前驱，只不过记录前 $k$ 个，记作 $pre_i$。现在把一个点看成 $(i,pre_i)$。接着考虑使用主席树，发现我们不好像区间数颜色一样那样数，所以可以考虑用总答案减去多的一部分，所以找的就是满足 $i\in[l,r]$ 且 $pre_i\in[l,r]$ 的点的数量，直接主席树即可。
```
#include<bits/stdc++.h>
#define N 100005
#define pb push_back
using namespace std;
int n,k,a[N];
vector<int> v[N];
int pre[N];
int root[N],ls[N<<5],rs[N<<5],tot,sum[N<<5];
void modify(int &p,int q,int l,int r,int x){
    p=++tot;
    ls[p]=ls[q],rs[p]=rs[q],sum[p]=sum[q]+1;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(x<=mid) modify(ls[p],ls[q],l,mid,x);
    else modify(rs[p],rs[q],mid+1,r,x);
}
int query(int p,int q,int l,int r,int ql,int  qr){
    //if(!q) return 0;
    if(ql<=l&&qr>=r) return sum[q]-sum[p];
    int mid=(l+r)>>1,res=0;
    if(ql<=mid) res+=query(ls[p],ls[q],l,mid,ql,qr);
    if(qr>mid) res+=query(rs[p],rs[q],mid+1,r,ql,qr);
    return res;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        v[a[i]].pb(i);
    }
    for(int i=1;i<=100000;i++){
        if(v[i].size()<k) continue;
        for(int j=k;j<v[i].size();j++){
            pre[v[i][j]]=v[i][j-k];
        }
    }
    for(int i=1;i<=n;i++){
        //cout<<i<<' '<<pre[i]<<endl;
        modify(root[i],root[i-1],0,n,pre[i]);
    }
    int q;
    scanf("%d",&q);
    int lastans=0;
    while(q--){
        int l,r;
        scanf("%d%d",&l,&r);
        l=(l+lastans)%n+1;
        r=(r+lastans)%n+1;
        if(l>r) swap(l,r);
        //cout<<l<<' '<<r<<endl;
        printf("%d\n",lastans=r-l+1-query(root[l-1],root[r],0,n,l,r));
    }
    return 0;
}
```


---

## 作者：_soul_ (赞：2)

由于 k 是给定的，我们设第 i 个元素往后数 k 个和它相同的元素到达的位置为 bi；特殊地，如果第 i 个数后面和它相同的数字少于 k 个，那么 $b_i$=n+1。

简单观察可以发现，我们要统计的就是区间 [l,r] 内有多少个 $b_i$ 满足 $b_i$>r。

直接对 $b_i$ 建立主席树，统计区间内权值范围在 [r+1,n+1] 的数的个数即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int a[MAXN],prek[MAXN],root[MAXN],num[MAXN],ans1,ans2;
int tot,nn,m,x,y,n,k,last;
vector <int> c[MAXN];
struct rec{
	int val,ls,rs;
}q[MAXN*30];
int build(int l,int r){
	int now=++tot;
	if (l==r) return now;
	int mid=(l+r)>>1;
	q[now].ls=build(l,mid); q[now].rs=build(mid+1,r);
	return now;
} 
int insert(int pre,int l,int r,int k){
	int now=++tot;
	q[now]=q[pre]; ++q[now].val; 
	//printf("%d %d\n",now,q[now].val);
	if (l==r) return now;
	int mid=(l+r)>>1;
	if (k<=mid) q[now].ls=insert(q[pre].ls,l,mid,k); else q[now].rs=insert(q[now].rs,mid+1,r,k);
	return now;
}
int query(int rt1,int rt2,int l,int r,int k){
	//printf("%d %d %d %d %d\n",rt1,rt2,l,r,k);
	if (r<=k) return q[rt2].val-q[rt1].val;
	int mid=(l+r)>>1,ans=0;
	ans=query(q[rt1].ls,q[rt2].ls,l,mid,k);
	if (k>mid) ans+=query(q[rt1].rs,q[rt2].rs,mid+1,r,k);
	//printf("ans=%d\n",ans);
	return ans;
}
int main(){
	//freopen(".in","r",stdin);
	scanf("%d%d",&n,&k); 
	for (int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		c[a[i]].push_back(i);
		if (c[a[i]].size()>k) prek[i]=c[a[i]][c[a[i]].size()-k-1]; else prek[i]=0;
	}	
	root[0]=build(0,n); 
	for (int i=1;i<=n;++i){
		root[i]=insert(root[i-1],0,n,prek[i]);
	} 
	scanf("%d",&m); last=0;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y); 
		x=(x+last)%n+1;  y=(y+last)%n+1;
		if (x>y) swap(x,y);
		last=query(root[x-1],root[y],0,n,x-1);   
		printf("%d\n",last);
	}
	return 0;
}
```


---

## 作者：VitrelosTia (赞：1)

纪念单杀 *2200，~~不过刚刚做完 HH 的项链。~~

先简单介绍一下区间数颜色的主席树解法。

考虑对于一个颜色，记录它上一次出现的位置（特别地，第一次出现就是 0）把它作为权值放到主席树上，对于一次查询，答案就是权值 $[0, l - 1]$ 在版本 `r` 减去版本 `l - 1` 的数量，含义是在询问区间内有多少个数是第一次出现的。

然后我们发现这个题和区间数颜色竟然是非常类似的，只不过区间数颜色要求区间内只能出现一次，而这里区间内可以出现 $k$ 次，那么我们把一个数前 $k$ 次出现的作为权值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define test cerr << "test"
#define print(x) cerr << #x << " = " << x << '\n'
#define printarr(x, n) for (int i = 1; i <= n; i++) cerr << #x << "[" << i << "] = " << x[i] << '\n'
typedef long long ll;

const int N = 1e5 + 5;
int n, k, Q, a[N]; vector <int> v[N];

namespace BetaTree {
#define mid ((l + r) >> 1)
	struct Seg { int ls, rs, cnt; } s[N << 6];
	int tot, T[N], L = 0, R = N - 1;
	void update(int &pos, int pre, int l, int r, int k) {
		pos = ++tot; s[pos] = s[pre]; s[pos].cnt++;
		if (l == r) return;
		k <= mid ? update(s[pos].ls, s[pre].ls, l, mid, k) : update(s[pos].rs, s[pre].rs, mid + 1, r, k);
	}
	int query(int x, int y, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return s[y].cnt - s[x].cnt;
		return (ql <= mid ? query(s[x].ls, s[y].ls, l, mid, ql, qr) : 0) + (qr > mid ? query(s[x].rs, s[y].rs, mid + 1, r, ql, qr) : 0);
	}
} using namespace BetaTree;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> k;
	for (int i = 1, c; i <= n; i++) {
		cin >> c;
		int p = v[c].size() < k ? 0 : v[c][v[c].size() - k];
//		printf ("p %d = %d\n", i, p);
		update(T[i], T[i - 1], L, R, p);
		v[c].push_back(i);
	}
	cin >> Q; for (int l, r, lst = 0; Q--; ) {
		cin >> l >> r; l = (l + lst) % n + 1, r = (r + lst) % n + 1; if (l > r) swap(l, r);
//		printf ("l = %d, r = %d\n", l, r);
		cout << (lst = query(T[l - 1], T[r], L, R, 0, l - 1)) << '\n';
	}
	return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：0)

一道可持久化线段树的好题。

### 题意
有一个含有 $n$ 个数的序列 $A$。共有 $q$ 次询问，每次询问 $[l,r]$ 内最多可以选多少个数,满足同一个数的出现次数不超过 $k$?

### 分析

通过题意得知，当前版本的答案和上一个版本的答案是有关联的，所以强制在线的话，我们可以直接使用主席树完成这个问题

我们可以保存当前位置的数字 $i$ 在哪个位置上出现，也就是说 $num$ 保存的的是在 $i$ 前出现并且比 $i$ 小的第 $k$ 个数，然后记录 $pos$ 位置上存的是哪个数字。

如果该数字的位置出现在左子树中，那就说明右子树是完整的，所以右子树直接复制前一个版本，左子树进行操作。

相反，如果该数字的位置出现在右子树中，那就说明左子树是完整的，那就在右子树中操作。

所以每一个 $[l,r]$ 区间对应的就是根为 $root_{l-1}$ 和 $root_{r}$ 这两个主席树上，动态开点维护小区间里的数就好。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long 
#define ls lson[now]
#define rs rson[now]
#define mid ((l+r)>>1)
const int maxn=5e5+10;
int sum[maxn<<5],lson[maxn<<5],rson[maxn<<5];//32
int tot;
int n,k;
void pushup(int now){
	sum[now]=sum[ls]+sum[rs];
}
void build(int &now,int pre,int l,int r,int pos,int w){
	now=++tot;
	sum[now]=sum[pre];
	ls=lson[pre],rs=rson[pre];
	if(l==r){
		sum[now]+=w;
		return;
	}
	if(pos<=mid){
		build(ls,lson[pre],l,mid,pos,w);
	}else{
		build(rs,rson[pre],mid+1,r,pos,w);
	}
	pushup(now);
}
int query(int now,int l,int r,int L,int R){
	if(!now){
		return 0;
	}
	if(L<=l&&r<=R){
		return sum[now];
	}
	int ans=0;
	if(L<=mid){
		ans+=query(ls,l,mid,L,R);
	}
	if(R>mid){
		ans+=query(rs,mid+1,r,L,R);
	}
	return ans;
}
vector <int> num[maxn];//存i在哪个pos上出现 
int a[maxn];//存pos上是什么数字 
int m,dex[maxn];
int ans=0;
int root[maxn];//版本 
void add(int &x,int ADD,int modd){
	x=(x+ADD)%modd+1;
}
signed main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		int x;
		cin >> x;
		num[x].push_back(i);
		a[i]=x; 
	}
	m=1e5;
	for(int i=1;i<=n;i++){
		++dex[a[i]];
		if(dex[a[i]]>k){
			build(root[m+i],root[i-1],1,n,num[a[i]][dex[a[i]]-k-1],-1);
		}else{
			root[m+i]=root[i-1];
		}
		build(root[i],root[m+i],1,n,i,1);
	}
	int q;
	cin >> q;
	ans=0;
	while(q--){
		int l,r;
		cin >> l >> r; 
		add(l,ans,n);
		add(r,ans,n);
		if(l>r){
			swap(l,r);
		}
		ans=query(root[r],1,n,l,n);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：N_Position (赞：0)

## 题目大意
给定一个区间，设 $cnt_i$ 为数字 $i$ 在这个区间中出现的次数，求 $\sum\min(cnt_i,k)$。
## 题目分析
设 $lastk_i$ 表示与这个数相等的前第 $k$ 个数的位置。
考虑从前往后选数，因为每个数最多出现 $k$ 次，我们只需要考虑 $lastk_i$ 是否选过，即 $lastk_i$ 是否小于等于 $l-1$，若小于等于，意味着值为 $a_i$ 的数选的次数目前还小于 $k$，可以继续选这个数。

所以问题变成了求 $\sum_{i=l}^{r}lastk\leq l-1$，显然可以使用可持久化线段树。

## 代码实现
时间复杂度 $O(n\log n)$，注意开 $32$ 倍空间。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
vector<int> v[N];
vector<int> lk[N];
int a[N],lastk[N],root[N];
int tot = 0;
struct node{
	int sum;
	int lson,rson;
}tree[N<<5];
void update(int p){
	tree[p].sum = tree[tree[p].rson].sum + tree[tree[p].lson].sum;
}
int build(int l,int r){
	int p = ++tot;
	if(l == r){
		tree[p].sum = 0;
		return p;
	}
	int mid = (l+r)>>1;
	tree[p].lson = build(l,mid);
	tree[p].rson = build(mid+1,r);
	update(p);
	return p;
}
int change(int now,int x,int l,int r){
	int p = ++tot;
	tree[p] = tree[now];
	tree[p].sum = tree[p].sum + 1;
	if(l == r){
		return p;
	}
	int mid = (l+r)>>1;
	if(x <= mid){
		tree[p].lson = change(tree[p].lson,x,l,mid);
	}else{
		tree[p].rson = change(tree[p].rson,x,mid+1,r);
	}
	update(p);
	return p;
}
int query(int now,int l,int r,int ll,int rr){
	int mid = (l+r)>>1;
	if(l == ll && r == rr){
		return tree[now].sum;
	}
	if(rr <= mid){
		return query(tree[now].lson,l,mid,ll,rr);
	}else if(ll > mid){
		return query(tree[now].rson,mid+1,r,ll,rr);
	}else{
		return query(tree[now].lson,l,mid,ll,mid) + query(tree[now].rson,mid+1,r,mid+1,rr);
	}
}
int main(){
	int n,q,maxn = -1,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		v[a[i]].push_back(i);
//		cerr<<":"<<a[i]<<' '<<i<<endl;
		maxn = max(maxn,a[i]);
	}
	scanf("%d",&q);
	for(int i=1;i<=maxn;i++){
		for(int j=k;j<v[i].size();j++){
			lastk[v[i][j]] = v[i][j-k];
		}
	}
	for(int i=1;i<=n;i++){
		lk[lastk[i]].push_back(i);
	}
	root[0] = build(1,n);
	for(int i=0;i<=n;i++){
		for(int j=0;j<lk[i].size();j++){
			root[i] = change(root[i],lk[i][j],1,n);
		}
		root[i+1] = root[i];
	}
	int last_ans = 0;
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x = (x+last_ans)%n+1;
		y = (y+last_ans)%n+1;
		if(x > y){
			swap(x,y);
		}
		last_ans = query(root[x-1],1,n,x,y);
		printf("%d\n",last_ans);
	}
	return 0;
}
```

---

## 作者：LCat90 (赞：0)

题外话，如果不强制在线可以用莫队做。

容易想到如果区间内一个数 $x$ 的数量不大于 $k$，我们就可以把这些 $x$ 全部选上。问题就在于当这个数量大于 $k$ 的时候怎么处理。

注意到 $k$ 为定值，显然可以预处理出位置 $i$ 所对应的值 $x$ 在前面第 $k-1$ 个数的下标 $pre_i$。如果这个 $pre_i$ 大于了 $l$，说明这个数是能选到的距离 $i$ 最远的数了，其他的数都不行了。反向思考，如果我们从 $l$ 选到 $r$，选的数值为 $x$，如果我们遇到了一个 $j$ 使得 $pre_j\ge l$，说明前面已经选了 $k$ 个以上的数了，这个数以及后面的数都不能再选了。

按照这个思路，得出计算方法：计算区间中满足 $pre_i<l$ 的元素数量。

于是我们可以建立一棵可持久化权值线段树，维护版本之间的区间和即可。**注意**：特判 $x$ 前面没有 $k$ 个 $x$ 的情况。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
int n, a[N], Root[N], k, cnt, q, dfn[N], siz[N], d[N];
vector <int> G[N];
struct node {
	int l, r, ls, rs, sum;
} T[N * 30];
void pushup(int p) { T[p].sum = T[T[p].ls].sum + T[T[p].rs].sum; }
int build(int l, int r) {
	int p = ++cnt; T[p].l = l, T[p].r = r;
	if(l == r) {
		T[p].sum = 0;
		return p;
	}
	int mid = l + r >> 1;
	T[p].ls = build(l, mid);
	T[p].rs = build(mid + 1, r);
	pushup(p);
	return p;
}
int Newnode(int x) {
	T[++cnt] = T[x];
	return cnt;
}
int update(int rt, int x, int y) {
	rt = Newnode(rt);
	if(T[rt].l == T[rt].r) {
		T[rt].sum += y;
		return rt;
	}
	int mid = T[rt].l + T[rt].r >> 1;
	if(x <= mid) T[rt].ls = update(T[rt].ls, x, y);
	else T[rt].rs = update(T[rt].rs, x, y);
	pushup(rt);
	return rt;
}
int query(int x1, int x2, int l, int r) {
	if(T[x1].l >= l and T[x1].r <= r) return T[x1].sum - T[x2].sum;
	int mid = T[x1].l + T[x1].r >> 1, ans = 0;
	if(mid >= l) ans += query(T[x1].ls, T[x2].ls, l, r);
	if(mid < r) ans += query(T[x1].rs, T[x2].rs, l, r);
	return ans;
} 
vector <int> in[N]; int pre[N];
signed main() {
	cin >> n >> k;
	Root[0] = build(0, n);
	for(int i = 1;i <= n; ++i) {
		scanf("%d", &a[i]);
		in[a[i]].pb(i);
		int len = in[a[i]].size(), sb = 0;
		if(len - k - 1 >= 0) sb = in[a[i]][len - k - 1];
//		else sb = in[a[i]][0];
		Root[i] = update(Root[i - 1], sb, 1);
//		cout << sb << " ";
	}
	cin >> q; 
	int lst = 0;
	while(q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		l = (l + lst) % n + 1; r = (r + lst) % n + 1;
		if(l > r) swap(l, r);
//		cout << l << " " << r << "\n";
		lst = query(Root[r], Root[l - 1], 0, l - 1);
		printf("%d\n", lst);
	}
	return 0;
}
/*
预处理出前 k 个的位置 
*/
```

---

## 作者：spdarkle (赞：0)

首先注意到，$k$ 为定值。

显然可以对每一个值进行贪心考虑。

在能取的情况下，对于同一个值，我们必定是自右向左取。

于是我们考虑对于每一个 $r$ 维护位置 $x$ 是否可以取。

可以记录每个数出现的位置，设 $pre_i$ 为 $i$ 前 $k$ 个等于 $a_i$ 的数的出现位置，没有就设为 $0$。

那么 $r$ 相对于 $r-1$，只有 $r$ 这个位置变成可取，并且 $pre_r$ 变成不可取。

这可以使用可持久化线段树简单维护区间和做到。

```cpp
#include<iostream>
#include<vector>
using namespace std;
#define N 505050
int s[N<<5],lc[N<<5],rc[N<<5],n,m,q,k,num,rt[N];
void insert(int &x,int p,int l,int r,int pos,int k){
	x=++num;s[x]=s[p],lc[x]=lc[p],rc[x]=rc[p];
	if(l==r){
		s[x]+=k;
		return ;
	}
	int mid=l+r>>1;
	if(pos<=mid)insert(lc[x],lc[p],l,mid,pos,k);
	else insert(rc[x],rc[p],mid+1,r,pos,k);
	s[x]=s[lc[x]]+s[rc[x]];
}
int find(int x,int l,int r,int L,int R){
	if(!x)return 0;
	if(L<=l&&r<=R)return s[x];
	int mid=l+r>>1,res=0;
	if(L<=mid)res+=find(lc[x],l,mid,L,R);
	if(mid<R)res+=find(rc[x],mid+1,r,L,R);
	return res; 
} 
vector<int>g[N];int id[N],a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;m=1e5+5;
	for(int i=1;i<=n;i++){
		int x;cin>>x;g[x].push_back(i);a[i]=x;
	} 
	for(int i=1;i<=n;i++){
		++id[a[i]];
		if(id[a[i]]>k){
			insert(rt[m+i],rt[i-1],1,n,g[a[i]][id[a[i]]-k-1],-1);
		}
		else rt[m+i]=rt[i-1];
		insert(rt[i],rt[m+i],1,n,i,1);
	}
	cin>>q;int lst=0;
	while(q--){
		int l,r;cin>>l>>r;
		l=(l+lst)%n+1,r=(r+lst)%n+1;
		if(l>r)swap(l,r);
		lst=find(rt[r],1,n,l,n);
		cout<<lst<<"\n";
	}
}
```





---

## 作者：_acat_ (赞：0)

## 题目大意

给定一个长度为 $n$ 的序列。

每次询问一个区间 $[l,r]$，相同的数最多只能取 $k$ 个，问总共能取几个数。

题目要求强制在线

## Sol

考虑这样一个问题，询问一个区间中有几个不同的数。

即 $k=1$ 并且离线的情况。

**但是**

本题要求强制在线。

考虑可持久化线段树。

$T_l$ 存的是 $last_i<l$ 的 $i$，在 $i$ 的位置上 $+1$. 这样每次在 $T_l$ 这棵树上查询 $[l,r]$ 的区间和即可。

对于每个数最多可以算 $k$ 次，只需要处理出 $lastk_i$ 即可。（即 $i$ 前面第 $k$ 次出现 $a_i$ 的位置）

时间复杂度 $O(n \log n)$。

---

## 作者：AChun (赞：0)

# CF813E题解

[题目传送门](https://www.luogu.com.cn/problem/CF813E)

### SOL：

本题有两个难点

$1$.如何控制 $l$~$r$ 中每个数的重复次数不超过$k$。

$2$.如何做到在线询问在线回答。


首先，对于第一个问题，我们用 $vector$ 数组来维护在$x$之前出现的第$k$个与$x$的数值相同的数的位置 $lastk[x]$。

然后，面对在线区间问题，考虑主席树。
对于 $0$~$n$ 建立根为 $root[i]$ 的主席树，维护前$i$个数所对应的  $lastk[a[i]]$ 在此区间内的出现情况。
 
此时，对于每一个 $l$~$r$ 区间中的数，若它的 $lastk[x]$ 的位置在 $0$ ~ $l-1$ 的区间内，则它一定没有在 $l$~$r$ 中出现过$k$次，其实，相当于把条件中相同数值的连续性，转化为了单点中离散的单纯限制。

最后，在根为 $root[l-1]$ 与 $root[r]$ 的树上，求区间 $0$ ~ $l-1$ 上的出现次数即可。

### CODE：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define N 101010 
using namespace std;
int n,m,k,q,bas,top;
int root[N],a[N];
vector<int> last[N];
struct node{
	int l,r,sum;
}t[N<<5];

int build(int p,int l,int r){
	p=++top;
	if(l==r) return p;
	int mid=(l+r)>>1;
	t[p].l=build(t[p].l,l,mid);
	t[p].r=build(t[p].r,mid+1,r);
	return p;
}
int update(int p,int l,int r,int x){ 
	t[++top]=t[p];p=top;
	t[p].sum++;
	if(l==r) return p;
	int mid=(l+r)>>1;
	if(x<=mid) t[p].l=update(t[p].l,l,mid,x);
	else t[p].r=update(t[p].r,mid+1,r,x);
	return p;
}
int query(int u,int v,int l,int r,int f,int to){
	if(f<=l&&r<=to){
		return t[v].sum-t[u].sum;
	} 
	int mid=(l+r)>>1,ans=0;
	if(f<=mid){
		ans+=query(t[u].l,t[v].l,l,mid,f,to);	
	}if(to>mid){
		ans+=query(t[u].r,t[v].r,mid+1,r,f,to);
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	root[0]=build(1,0,n);
	for(int i=1;i<=n;i++){
		last[a[i]].push_back(i);
		int Size=last[a[i]].size();
		if(Size>k){
			root[i]=update(root[i-1],0,n,last[a[i]][Size-k-1]);
		}else{
			root[i]=update(root[i-1],0,n,0);
		}
	}
	int l,r;
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&l,&r);
		l=(l+bas)%n+1,r=(r+bas)%n+1;
		if(l>=r) swap(l,r);
		bas=query(root[l-1],root[r],0,n,0,l-1);
		printf("%d\n",bas);
	}
	return 0;
}


```




---

## 作者：TernaryTree (赞：0)

HH 的项链 扩展 + 强制在线版。纪念我真正意义上第一次学会主席树/ll，wtcl。

记录每个点前面第 $k$ 个与其相同的位置 $lst_i$，若不存在则为 $0$。然后查询就是查询一段 $[l,r]$ 里面 $lst_i\le l-1$ 的数，这个使用权值主席树实现即可。

时间复杂度 $\Theta((n+q)\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid (l + r >> 1)

using namespace std;

const int maxn = 1e5 + 10;
const int m = 1e5;
const int maxd = 22;

int n, k, q;
int l, r, ans;
int a[maxn];
int lst[maxn];
vector<int> p[maxn];

struct Node {
	int l, r, v;
	Node() = default;
};

Node tr[maxn * maxd];
int rt[maxn];
int cnt;

void build(int &u, int l, int r) {
	u = ++cnt;
	if (l == r) return;
	build(tr[u].l, l, mid);
	build(tr[u].r, mid + 1, r);
	tr[u].v = tr[tr[u].l].v + tr[tr[u].r].v;
}

void update(int &u, int pre, int l, int r, int p) {
	u = ++cnt;
	tr[u] = tr[pre];
	if (l == r) {
		tr[u].v++;
		return;
	}
	if (p <= mid) update(tr[u].l, tr[pre].l, l, mid, p);
	else update(tr[u].r, tr[pre].r, mid + 1, r, p);
	tr[u].v = tr[tr[u].l].v + tr[tr[u].r].v;
}

int query(int u, int pre, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return tr[u].v - tr[pre].v;
	int res = 0;
	if (ql <= mid) res += query(tr[u].l, tr[pre].l, l, mid, ql, qr);
	if (qr > mid) res += query(tr[u].r, tr[pre].r, mid + 1, r, ql, qr);
	return res;
}

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (p[a[i]].size() < k) lst[i] = 0;
		else lst[i] = p[a[i]][p[a[i]].size() - k];
		p[a[i]].push_back(i);
	}
	build(rt[0], 0, m);
	for (int i = 1; i <= n; i++) update(rt[i], rt[i - 1], 0, m, lst[i]);
	cin >> q;
	while (q--) {
		cin >> l >> r;
		l = (l + ans) % n + 1;
		r = (r + ans) % n + 1;
		if (l > r) swap(l, r);
		cout << (ans = query(rt[r], rt[l - 1], 0, m, 0, l - 1)) << endl;
	}
	return 0;
}
```

---

