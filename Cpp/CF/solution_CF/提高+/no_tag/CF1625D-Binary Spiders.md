# Binary Spiders

## 题目描述

Binary Spiders are species of spiders that live on Mars. These spiders weave their webs to defend themselves from enemies.

To weave a web, spiders join in pairs. If the first spider in pair has $ x $ legs, and the second spider has $ y $ legs, then they weave a web with durability $ x \oplus y $ . Here, $ \oplus $ means bitwise XOR.

Binary Spiders live in large groups. You observe a group of $ n $ spiders, and the $ i $ -th spider has $ a_i $ legs.

When the group is threatened, some of the spiders become defenders. Defenders are chosen in the following way. First, there must be at least two defenders. Second, any pair of defenders must be able to weave a web with durability at least $ k $ . Third, there must be as much defenders as possible.

Scientists have researched the behaviour of Binary Spiders for a long time, and now they have a hypothesis that they can always choose the defenders in an optimal way, satisfying the conditions above. You need to verify this hypothesis on your group of spiders. So, you need to understand how many spiders must become defenders. You are not a Binary Spider, so you decided to use a computer to solve this problem.

## 说明/提示

Consider the examples above.

In the first example, the group of spiders is illustrated on the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625D/1010007e17d60a2fb95617e44d5646f679fa1136.png)We choose the two-legged, the ten-legged and the $ 16 $ -legged spiders. It's not hard to see that each pair may weave a web with enough durability, as $ 2 \oplus 10 = 8 \ge 8 $ , $ 2 \oplus 16 = 18 \ge 8 $ and $ 10 \oplus 16 = 26 \ge 8 $ .

This is not the only way, as you can also choose, for example, the spiders with indices $ 3 $ , $ 4 $ , and $ 6 $ .

In the second example, no pair of spiders can weave the web with durability $ 1024 $ or more, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
6 8
2 8 4 16 10 14```

### 输出

```
3
1 5 4```

## 样例 #2

### 输入

```
6 1024
1 2 3 1 4 0```

### 输出

```
-1```

# 题解

## 作者：Legitimity (赞：8)

提供一个感觉比较优美的做法（不需要分类讨论）。


------------

我们发现将这些数看成二进制数字符串后，$\operatorname{xor}$ 和 `lcp` 是很相似的；那么类比 `sa` 关于后缀之间的 `lcp` 的那个结论，我们可以发现，将这些数按字典序排序后得到 $a$ 序列，那么 $a$ 的一个子序列 $b$ 中的元素两两异或的最小值为 $\min_i\{b_i\operatorname{xor} b_{i+1} \}$。

证明：必要性显然，证一下充分性：假设存在 $i+1<j$ （相反情况同理）使得 $b_i\operatorname{xor}b_j<b_i\operatorname{xor}b_{i+1}$，并且 $b_i\operatorname{xor}b_j$ 为全局最小值，那么一定存在一个二进制位 $k$，使得任意 $k^{\prime}>k$ 满足 $b_{i,k^{\prime}}=b_{j,k^{\prime}}=b_{i+1,k^{\prime}}$ 且 $b_{i,k}=b_{j,k}\ne b_{i+1,k}$ ，又根据 $i<i+1<j$ 可得 $b_{i,k}=b_{j,k}=0,b_{i+1,k}=1$；这样以来又可得 $b_{i+1}>b_{j}$，与按字典序排序矛盾。


------------


那么我们就有了一个简单的做法，将给出的序列按二进制表示下字典序（其实就等于按数值大小）排序得到 $a$ 序列，设 $f_i$ 表示强制选 $i$ 时从区间 $[1,i]$ 最多能选几个数，转移方程为 $f_i=\max_{j<i,b_j\operatorname{xor} b_i\geq k}\{f_j\}+1$。

直接做是 $O(n^2)$ 的，放在字典树上，设 $g_x= \max_{y\in subtree(x),y\texttt{ is a leaf}}\{f_y\}$，插入时暴力维护，转移时从上向下遍历，设当前在第 $j$ 位 $x$ 节点，若 $k_j=0$，说明此时 $subtree(son_{x,b_i\operatorname{xor}1})$ 中所有数都是可以选的，令 $f_i=\max\{f_i,g_{son_{x,b_i\operatorname{xor}1}}+1\}$，然后进入 $son_{x,b_i}$ 继续处理；否则只能进入 $son_{x,b_i\operatorname{xor}1}$。

时间复杂度为 $O(n\log v)$，$v$ 为值域。



------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define ull unsigned ll
#define inf 0x3f3f3f3f
#define lowbit(x) (x&(-x))
#define eps 1e-8
const double alpha=0.73;
inline void file(){
	freopen("baka.in","r",stdin);
	freopen("baka.ans","w",stdout);
}
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	rg int ret=0,f=0;char ch=getc();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getc();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getc();}
    return f?-ret:ret;
}
struct num{ 
	int id,v; 
	num(int id=0,int v=0):id(id),v(v) {} 
	bool operator<(const num& tmp)const{ return v^tmp.v?v<tmp.v:id<tmp.id; }
}a[300005],f[300005],g[300005*32+5];
int n,k,son[300005*32+5][2],cntt=1;
inline void update(int x){
	const int v=a[x].v,id=a[x].id; int u=1;
	for(rg int i=30;~i;--i){
		if(!u) break;
		const bool chk=((k>>i)&1),to=((v>>i)&1);
		if(!chk) f[id]=max(f[id],g[son[u][to^1]]);
		u=son[u][to^chk];
	}
	if(u) f[id]=max(f[id],g[u]);
	++f[id].v;
}
inline void insert(int x){
	const int v=a[x].v,id=a[x].id; int u=1;
	const num fid=num(id,f[id].v);
	for(rg int i=30;~i;--i){
		const bool to=((v>>i)&1);
		if(!son[u][to]) son[u][to]=++cntt;
		g[u]=max(g[u],fid);
		u=son[u][to];
	}
	g[u]=max(g[u],fid);
}
signed main(){
    //file();
   	n=read(),k=read();
   	for(rg int i=1,x;i<=n;++i) x=read(),a[i]=num(i,x);
	sort(a+1,a+1+n);
	for(rg int i=1;i<=n;++i) update(i),insert(i);
	int x=g[1].id;
	if(f[x].v==1) return 0*puts("-1");
	printf("%d\n",f[x].v);
	while(x) printf("%d ",x),x=f[x].id;
	return 0;
}
/*
10 10
18 2 6 17 7 19 17 6 2 12 14
4 15 5 20 2 6 20 12 16 5
*/
```



---

## 作者：vectorwyx (赞：7)

这种问题先放到 trie 树上看看。

假设 $k$ 的最高位为 $p$，那么 trie 树上高度为 $p$ 的结点的子树相互独立（这里的高度为 $p$ 是指结点所代表二进制位为 $p$），而每个高度为 $p$ 的结点的左儿子的子树里最多选一个，右儿子的子树里也最多选一个，问题转为能否从左子树和右子树里选出两个使其异或 $\ge k$。

直接暴力找出左子树里的所有元素，对于每个元素在右子树上贪心找到与它异或起来最大的数，看看两者的异或是否 $\ge k$。时间复杂度 $O(n\log n)$。

代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=3e5+5;
int ch[N*30][2],n,num,a[N],k,root,pos,data[N*30];
vector<int> ans,g;

void insert(int &now,int x,int b){
	if(!now) now=++num;
	if(b<0) return;
	insert(ch[now][x>>b&1],x,b-1);	
}

void _dfs(int now,int b){
	if(b<0){
		g.pb(data[now]);
		return;
	}
	if(ch[now][0]) _dfs(ch[now][0],b-1);
	if(ch[now][1]) _dfs(ch[now][1],b-1);
}

int query(int now,int x,int b){
	if(b<0) return data[now];
	if(ch[now][!(x>>b&1)]) return query(ch[now][!(x>>b&1)],x,b-1);
	else return query(ch[now][x>>b&1],x,b-1);
}

void dfs(int now,int b){
	if(b==pos){
		if(!ch[now][0]&&!ch[now][1]) return;
		if(!ch[now][0]){
			_dfs(ch[now][1],b-1);
			ans.pb(g[0]);
			g.clear();
			return;
		}
		if(!ch[now][1]){
			_dfs(ch[now][0],b-1);
			ans.pb(g[0]);
			g.clear();
			return;	
		}
		_dfs(ch[now][0],b-1);
		for(int i:g){
			int w=query(ch[now][1],a[i],b-1);
			if((a[w]^a[i])>=k){
				ans.pb(i),ans.pb(w);
				goto H;
			} 		
		}
		ans.pb(g[0]);
		H:
		g.clear();
		return;
	}
	if(ch[now][0]) dfs(ch[now][0],b-1);
	if(ch[now][1]) dfs(ch[now][1],b-1);
}

signed main(){
	cin>>n>>k;
	fo(i,1,n){
		a[i]=read(),insert(root,a[i],29);
		if(!data[num]) data[num]=i;
	} 
	if(!k){
		cout<<n<<'\n';
		fo(i,1,n) cout<<i<<' ';
		return 0;
	}
	fo(i,0,29) if(k>>i&1) pos=i;
	dfs(root,29);
	if(ans.size()<=1){
		cout<<-1;
		return 0;
	}
	cout<<ans.size()<<'\n';
	for(int i:ans) cout<<i<<' ';
	return 0;
}
/*
-------------------------------------------------
*/

```


---

## 作者：oisdoaiu (赞：1)

*01trie，分讨*

---
像我这种想不到结论的菜逼，自然是不会用结论的。

考虑 01trie，找到 $k$ 二进制的第一个 $1$，和 trie 上这一层的节点。

这些节点子树内的选择是独立的，因为对于两个不同子树内选的数，前面几位异或起来一定不是 $0$，而 $k$ 前几位都是 $0$。

然后对于一个节点来说，最多只能选 $2$ 个，且选 $2$ 个的情况一定是左子树一个右子树一个，所以直接在左右子树选一对异或起来 $\ge k$ 的就好了。选不出来一对的话就在子树内随便选一个。

---
考虑 `check(int x, int y, int d)` 表示要从 $x,y$（深度 $d$）子树中各找一个数，使得异或和 $\ge k$。(返回值为一个 `pair` 表示两个数在数组中的下标)

如果 $k$ 这一位是 $0$ 且当前位异或和可以凑出 $1$，则直接返回当前位凑出 $1$ 的任意两个数就好了。

否则看当前位异或和是否能和 $k$ 一样，不能的话返回无解。

注意到上述过程 trie 上每个节点只会被访问一次，所以复杂度 $O(n\log V)$。

*注意特判 0 全部输出*

---
```cpp
#include<bits/stdc++.h>
using namespace std;

template<typename T>
inline void Read(T &n){
	char ch; bool flag=false;
	while(!isdigit(ch=getchar())) if(ch=='-')flag=true;
	for(n=ch^48; isdigit(ch=getchar()); n=(n<<1)+(n<<3)+(ch^48));
	if(flag) n=-n;
}

enum{
    MAXN = 300005
};

struct node{
    int son[2], val;
    #define lc(x) t[x].son[0]
    #define rc(x) t[x].son[1]
    #define son(x,opt) t[x].son[opt]
    #define val(x) t[x].val
    // val 表示子树内的任意一个数
}t[MAXN*32];
int rt=1, node_cnt=1;

vector<int>q[31];

int n, k;

inline void insert(int x, int id){
    int cur = rt;
    for(int i=29; ~i; i--){
        char v = x>>i&1;
        if(!son(cur,v)) son(cur,v) = ++node_cnt, q[i].push_back(son(cur,v));
        cur = son(cur,v); val(cur) = id;
        // printf("%d ",cur);
    }
    // puts("");
}

int ans[MAXN], cnt;

typedef pair<int,int> pii;
pii check(int d, int x, int y){
    // printf("check %d %d %d\n",d,x,y);
    if(d<0) return pii(val(x),val(y));
    if(k>>d&1){
        pii ans; ans.first = -1;
        if(lc(x) and rc(y)) ans = check(d-1,lc(x),rc(y));
        if(ans.first==-1 and rc(x) and lc(y)) ans = check(d-1,rc(x),lc(y));
        return ans;
    } 
    if(lc(x) and rc(y)) return pii(val(lc(x)),val(rc(y)));
    if(rc(x) and lc(y)) return pii(val(rc(x)),val(lc(y)));
    pii ans; ans.first = -1;
    if(lc(x) and lc(y)) ans = check(d-1,lc(x),lc(y));
    if(ans.first==-1 and rc(x) and rc(y)) ans = check(d-1,rc(x),rc(y));
    return ans;
}

int a[MAXN];

inline void check(){
    for(int i=1; i<=cnt; i++) for(int j=i+1; j<=cnt; j++) assert((a[ans[i]]^a[ans[j]])>=k);
}

int main(){
    // freopen("d.in","r",stdin);
    // freopen("d.out","w",stdout);
    Read(n); Read(k); q[30].push_back(1);
    // puts("?");
    for(int i=1; i<=n; i++) Read(a[i]);
    for(int i=1; i<=n; i++) insert(a[i],i);
    // for(int i=1; i<=n; i++,puts("")) for(int j=6; ~j; j--) printf("%d",a[i]>>j&1);
    if(!k){
        printf("%d\n",n);
        for(int i=1; i<=n; i++) printf("%d ",i);puts("");
        return 0;
    }
    for(int i=29; ~i; i--) if(k>>i&1){
        // printf("pos = %d\n",i);
        for(int x:q[i+1]){
            // printf("solve %d\n",x);
            pii res = check(i,x,x);
            if(res.first==-1) ans[++cnt] = val(x);
            else ans[++cnt] = res.first, ans[++cnt] = res.second;
        }
        if(cnt<2) return puts("-1"), 0;
        printf("%d\n",cnt);
        for(int j=1; j<=cnt; j++) printf("%d ",ans[j]); puts("");
        // check();
        return 0;
    }
    return 0;
}
```

---

## 作者：PersistentLife (赞：1)

博客：[CF DS题选做](https://www.luogu.com.cn/blog/302837/cf-2300-ds-ti-zuo-ti-bi-ji)

题意：给定 $n$ 个整数，$a_1,a_2,...,a_n$，并给定一个整数 $k$，求出一个最大的集合 $S$，满足 $S$ 中的元素均 $\le n$，且对于任意两个 $S$ 中的元素 $x,y$，满足两数异或和 $\ge k$。

---

分析：如果两个数异或结果的最高位比 $k$ 大，则异或结果一定 $>k$，定义 $f(x)$ 表示当 $x$ 不含有前导 $0$ 的情况下二进制位数，考虑将所有数，在二进制表示中的末尾去掉 $f(k)$ 位，并按新的数分组，若两个数处于不同组，则它们异或和一定 $>k$。

对每一组分别求解，容易发现每一组最多只能选上 $2$ 个数，如果选 $\ge 3$ 个数，就一定存在两个数，它们异或和 $<k$，因为 $k$ 的最高位上的数字一定会有 $2$ 个 $0$ 或 $2$ 个 $1$。

设目前处理的那一组的数为 $b_1,b_2,...,b_m$，即要求出是否存在两个数满足异或和 $\ge k$，即求两个数最大异或和。将数转化为二进制，依次插入 trie 中，并查询最大异或和，即每次尽量往自己相反的方向走。

注意每一组求解完成后要清空 trie，不能 memset，要一个一个删除。

时间复杂度 $O(n \log A)$。

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一个长为 $n$ 的序列 $a_i$，求出一个最长的子序列，使得子序列中的数两两异或大于等于 $k$。
### 分析
结论题。

有一个经典结论是这样的：

> $$\forall a<b<c,a\oplus c\ge\min(a\oplus b,b\oplus c)$$

先随机乱证一下：考虑 $a,b,c$ 二进制下两两的 LCP，类似 SA 的原理，由于 $b$ 的字典序被夹在中间，所以 $\text{lcp}(a,c)=\min(\text{lcp}(a,c),\text{lcp}(b,c))$，即 $a\oplus c$ 的 highbit 必然大于等于后两者中较小的那个。

于是你把原序列排序以后，就只要满足选出的子序列相邻两个数异或大于等于 $k$ 了。

这东西显然上个 DP 吧。设 $dp_i$ 表示以第 $i$ 个数结尾的最长合法子序列，转移有：
$$dp_i=\max_{1\le j\le i,a_i\oplus a_j\ge k}dp_j+1$$
暴力转移 $O(n^2)$ 的，想办法弄个 ds 优化一下。

给异或搞了个下界，是 01-trie 的常见用法。每次转移完 $dp_i$ 直接插入 $a_i$ 的决策点，为了查询时每次单侧递归保证复杂度，维护个子树最优决策就可以了。查询的时候对 $a_i$ 和 $k$ 的 bit 分讨一下，记得判是否有节点再递归。

最后注意一下输出方案应该为原序列中的位置。时间复杂度 $O(n\log V)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=3e5+5;
int n,k;
pii a[maxn];
int dp[maxn],g[maxn];
void chkmx(int &u,int v){if(dp[v]>dp[u]) u=v;}
class Bit_Trie{
public:
	int ch[maxn*30][2],tran[maxn*30],tot;
	void insert(int x,int k){
		int u=0;
		for(int i=29;i>=0;i--){
			int b=(x>>i)&1;
			if(!ch[u][b]) ch[u][b]=++tot;
			u=ch[u][b];chkmx(tran[u],k);
		}
	}
	int query(int u,int d,int x,int k){
		if(d<0) return tran[u];
		int b1=(x>>d)&1,b2=(k>>d)&1;
		int res=0;
		if(!b2){
			if(ch[u][b1^1]) chkmx(res,tran[ch[u][b1^1]]);
			if(ch[u][b1]) chkmx(res,query(ch[u][b1],d-1,x,k));
		}else{
			if(ch[u][b1^1]) chkmx(res,query(ch[u][b1^1],d-1,x,k));
		}
		return res;
	}
}tr;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i].fir=read(),a[i].sec=i;
	sort(a+1,a+n+1);
	tr.insert(0,0);
	for(int i=1;i<=n;i++){
		int t=tr.query(0,29,a[i].fir,k);
		dp[i]=dp[t]+1;g[i]=t;
		tr.insert(a[i].fir,i);
	}
	int pos=0;
	for(int i=1;i<=n;i++) chkmx(pos,i);
	if(dp[pos]<2){
		puts("-1");
		return 0;
	}
	cout<<dp[pos]<<"\n";
	while(pos) cout<<a[pos].sec<<" ",pos=g[pos];
	cout<<"\n";
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

记 $x$ 的最高位的权重为 $2^k$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0tq9h9z6.png)

如果选择 lca 为 $4,5,6,7$ 的一对点，显然不可行。

如果选择 lca 为 $1$ 的一对点，显然可行。

如果选择 lca 为 $2,3$ 的一对点，可能可行。

贪心的思路就是每个和 $2,3$ 同高的子树当中至少选择一个点，看能否选择两个点。如果和 $2,3$ 同高的子树中选了至少 $3$ 个点，因为鸽巢原理，必然有 $2$ 个点在和 $4,5,6,7$ 同高的子树当中，所以，我们任务是判断能否在和 $2,3$ 同高的子树中选择 $2$ 个点。

我们只需要找到这些点两个异或最大值即可，这是插入 trie 就可以解决的问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5, K = 35;
int n, k, a[N], x, tmp, Res, tem, id[N];
vector<int> ans;
bool flg;
struct TRIE{
    int nxt[N * K][2], x, p, idx, to[N * K];
    inline void clear(){
        for(int i = 1; i <= idx; i++) nxt[i][0] = nxt[i][1] = to[i] = 0;
        idx = 1;
    }
    inline void inesrt(int val, int id){
        p = 1;
        for(int i = tmp - 1; ~i; i--){
            x = val >> i & 1;
            if(!nxt[p][x]) nxt[p][x] = ++idx;
            p = nxt[p][x];
        }
        to[p] = id;
    }
    inline int query(int val){
        p = 1;
        int res = 0;
        for(int i = tmp - 1; ~i; i--){
            x = val >> i & 1;
            if(nxt[p][x ^ 1]) res |= 1 << i, p = nxt[p][x ^ 1];
            else p = nxt[p][x];
        }
        Res = to[p];
        return res;
    }
}T;
inline int calc(int x){
    int res = 0;
    while(x){
        res++;
        x >>= 1;
    }
    return res;
}
inline bool cmp(int x, int y){
    return a[x] < a[y];
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        id[i] = i;
    }
    if(k == 0){
        printf("%d\n", n);
        for(int i = 1; i <= n; i++) printf("%d ", i);
        return 0;
    }
    sort(id + 1, id + n + 1, cmp);
    sort(a + 1, a + n + 1);
    // for(int i = 1; i <= n; i++) printf("%d ", id[i]);puts("");
    tmp = calc(k);
    int i, j;
    // for(int i = 1; i <= n; i++) printf("%d ", a[i]);puts("");
    for(i = j = 1; i <= n; i = j){
        while(j <= n && (a[i] >> tmp) == (a[j] >> tmp)) j++;
        T.clear();
        // printf("%d %d\n", i, j);
        flg = 0;
        for(int l = i; l < j; l++){
            if(a[l] >> tmp - 1 & 1) break ;
            T.inesrt(a[l], l);
        }
        for(int l = i; l < j && T.idx > 1 && !flg; l++){
            if(!(a[l] >> tmp - 1 & 1)) continue ;
            tem = T.query(a[l]);
            // printf("%d\n", tem);
            if(tem >= k){
                flg = 1;
                ans.push_back(id[l]);
                ans.push_back(id[Res]);
            }
        }
        if(!flg){
            ans.push_back(id[i]);
        }
    }
    if(ans.size() == 1){
        puts("-1");
        return 0;
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for(int x : ans) printf("%d ", x);
    puts("");
    return 0;
}
```

---

