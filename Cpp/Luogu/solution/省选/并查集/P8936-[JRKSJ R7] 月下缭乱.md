# [JRKSJ R7] 月下缭乱

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/xkd5zhgk.png?x-oss-process=image)

轻快的音乐声坚定了你做一道简单题的决心。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

你有一个长度为 $n$，初值全为 $0$ 的序列 $a$。

你有长为 $m$ 的操作序列，其中第 $i$ 次有三个参数 $l_i,r_i,x_i$，表示令 $\forall j\in[l_i,r_i] ,a_j\gets\max(a_j,x_i)$。

令 $\text{sol}(l,r)$ 表示依次操作第 $l$ 至第 $r$ 个操作后的 $a$ 序列。

你需要回答有多少对 $(l,r)$ 满足 $1\le l\le r\le m$ 且 $\text{sol}(l,r)=\text{sol}(1,m)$。

记 $f_i$ 为有多少 $i\le k\le m$ 满足 $\text{sol}(i,k)=\text{sol}(1,m)$，你还需要输出 $\displaystyle\bigoplus_{i=1}^m f_i\times i$ 与 $\displaystyle\sum_{i=1}^m f_i\times i$ 的值。

所有答案都需要对 $2^{32}$ 取模后输出。

## 说明/提示

Idea：cyffff，Solution：Ntokisq / abruce，Code：cyffff，Data：cyffff

**月下缭乱 - 月見静華 vs. LUNARiUM (Insane14.8)**

**本题输入输出文件较大，请使用恰当的输入输出方式。**

### 样例解释

对于样例 $2$，最终 $a$ 序列的值为 $\{2,2,3\}$。不难发现，进行 $[1,4],[1,5],[2,5],[3,5],[4,5]$ 内的操作都可以使得 $a$ 与进行所有操作后 $a$ 序列的值相同。答案为 $5$。$f$ 序列的值为 $\{2,1,1,1,0\}$。

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n,m\le$ | 特殊限制 | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $100$ | 无 | $10$ |
| $2$ | $10^4$ | 无 | $20$ |
| $3$ | $3\times10^5$ | 保证 $l_i=r_i$ | $10$ |
| $4$ | $3\times10^5$ | 保证 $x_i=1$ | $10$ |
| $5$ | $3\times10^5$ | 无 | $20$ |
| $6$ | $10^6$ | 无 | $30$ |

对于 $100\%$ 的数据，$1\le n,m\le10^6$，$1\le l_i\le r_i\le n$，$1\le x_i\le m$。
### 特殊评分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i\in\{1,3,4\}$，您只需答对子任务 $i$ 即可获得子任务 $i$ 的分数。
- 对于子任务 $i\in\{2,5,6\}$，您需要答对所有 $j\in[1,i]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。

## 样例 #1

### 输入

```
5 5
1 3 1
2 4 1
2 3 1
1 3 1
1 4 1
```

### 输出

```
9 2 20```

## 样例 #2

### 输入

```
3 5
1 3 2
1 1 1
2 2 2
3 3 3
1 3 2
```

### 输出

```
5 7 11```

# 题解

## 作者：min_inf (赞：5)

老早扔进 to-do list 吃灰的东西拿出来做了一下，不知道为什么有紫以及为什么题解做法都这么神秘。

考虑最终的序列 $a$，对于一个位置 $i$，$\operatorname{sol}(l,r)=\operatorname{sol}(1,m)$ 时 $\exists j \in [l,r],l_j \le i \le r_j \land x_j = a_i$。

考虑枚举这个值 $j$，把所有 $a_i=j$ 的地方都提出来，对所有 $x_i=j$ 的区间双指针一遍，用线段树维护位置最小被覆盖到的次数，$\ne 0$ 即为满足要求。

$O(n \log n)$。

```cpp
namespace KnownError_{
    constexpr int N = 1e6+5;
    int n,m,R[N];
    struct opt{int l,r,id;};
    vector<opt> ve[N];
    int fa[N];
    int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    int mn[N<<1],tg[N<<1];
    void setp(int u,int L,int R,int x,int v,int t){
        if(L==R){mn[u]=v-t;return;}
        t+=tg[u];
        int M=L+R>>1,ls=M<<1,rs=M<<1|1;
        if(x<=M)setp(ls,L,M,x,v,t);
        else setp(rs,M+1,R,x,v,t);
        mn[u]=min(mn[ls],mn[rs])+tg[u];
    }
    void add(int u,int L,int R,int l,int r,int x){
        if(r<L||R<l||r<l)return;
        if(l<=L&&R<=r){mn[u]+=x,tg[u]+=x;return;}
        int M=L+R>>1,ls=M<<1,rs=M<<1|1;
        add(ls,L,M,l,r,x);
        add(rs,M+1,R,l,r,x);
        mn[u]=min(mn[ls],mn[rs])+tg[u];
    }
    void main(){
        cin>>n>>m;
        rep(i,1,m){
            int l,r,x;
            cin>>l>>r>>x;
            ve[x].push_back({l,r,i});
        }
        iota(R+1,R+m+1,1);
        iota(fa+1,fa+n+2,1);
        fill(mn+1,mn+2*n,1e9);
        per(i,m,1){
            vector<opt> now;
            vector<int> pt;
            for(auto o:ve[i])if(find(o.l)<=o.r)now.push_back(o);
            if(now.empty())continue;
            for(auto o:now){
                int p=find(o.l);
                while(p<=o.r){
                    pt.push_back(p);
                    fa[p]=p+1,p=find(p);
                }
            }
            for(auto j:pt)setp(1,1,n,j,0,0);
            int cnt=now.size();
            int p=0;
            repn(j,cnt){
                while(p<cnt&&!mn[1])add(1,1,n,now[p].l,now[p].r,1),++p;
                int pos=j?now[j-1].id+1:1;
                R[pos]=max(R[pos],mn[1]?now[p-1].id:m+1);
                add(1,1,n,now[j].l,now[j].r,-1);
            }
            R[now.back().id+1]=max(R[now.back().id+1],m+1);
            for(auto j:pt)setp(1,1,n,j,1e9,0);
        }
        ui ans1=0,ans2=0,ans3=0;
        rep(i,1,m){
            R[i]=max(R[i],R[i-1]);
            ui f=m-R[i]+1;
            ans1+=f;
            ans2^=f*(ui)i;
            ans3+=f*(ui)i;
        }
        cout<<ans1<<' '<<ans2<<' '<<ans3<<'\n'; 
    }
}
```


---

## 作者：yanbinmu (赞：2)

## 分析

我们可以考虑将每个颜色分开处理，处理出每个颜色需要至少几个操作，使得整个区间被覆盖。

而这个我们可以使用类似时间戳的方法来维护。

如果两个操作都可以覆盖一个点，那我们显然优先用比较靠前的那个。

这启发我们，使用线段树，对于某个点，维护可以操作这个点的最小操作编号。

对于所有点，我们统计这个最小值的最大值，那么所得到的编号就是我们所需要的最大编号（右端点）。

而所有颜色取最大值，就是这个左端点所需的最小右端点。

而显然的，所有比这个右端点大的右端点都是可行的。

## 代码

因为出题人卡空间，所以使用 `new` 和 `delete` 节省空间。

```C++
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 6;

struct Tree {
	int *t;
	void init(size_t n) {
		t = new int[n * 4]();
	}
	void modify(int k, int l, int r, int x, int y, int d) {
		if(l > y || r < x) return ;
		if(x <= l && r <= y) { 
			t[k] = max(t[k], d);
			return ;
		}
		modify(k << 1, l, (l + r) / 2, x, y, d);
		modify(k << 1 | 1, (l + r) / 2 + 1, r, x, y, d);
		t[k] = max(t[k], min(t[k << 1], t[k << 1 | 1]));
	}
	int query(int k, int l, int r, int x, int y) {
		if(l > y || r < x) return 0x3f3f3f3f;
		if(x <= l && r <= y) {
			return t[k];
		}
		return max(t[k], min(query(k << 1, l, (l + r) / 2, x, y), query(k << 1 | 1, (l + r) / 2 + 1, r, x, y)));
	}
	~Tree() {
		delete[] t;
	}
}tree;

int l[N], r[N], x[N];

struct pack {
	Tree tree;
	vector<int> scc;
};

unordered_map<int, pack> mp;
multiset<unsigned> st;
unsigned sum, X, mul;

inline int read() {
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	int n, m;
	n = read();
	m = read();
//	cin >> n >> m;
	{
		tree.init(n);
		for(int i = m;i >= 1;i -- ) {
			l[i] = read();
			r[i] = read();
			x[i] = read();
//			cin >> l[i] >> r[i] >> x[i];
			tree.modify(1, 1, n, l[i], r[i], x[i]);
		}
		for(int i = 1;i <= n;i ++ ) {
			mp[tree.query(1, 1, n, i, i)].scc.push_back(i);
		}
	}

	for(auto &i : mp) {
		i.second.tree.init(i.second.scc.size());
		if(i.first) {
			st.insert(0);
		}
	}
	for(int i = 1;i <= m;i ++ ) {
		if(mp[x[i]].scc.size() != 0) {
			st.erase(st.find(mp[x[i]].tree.t[1]));
			
			mp[x[i]].tree.modify(1, 1, mp[x[i]].scc.size(), lower_bound(mp[x[i]].scc.begin(), mp[x[i]].scc.end(), l[i]) - mp[x[i]].scc.begin() + 1, upper_bound(mp[x[i]].scc.begin(), mp[x[i]].scc.end(), r[i]) - mp[x[i]].scc.begin() + 1 - 1, i);
			
			st.insert(mp[x[i]].tree.t[1]);
		}
		
        sum += *st.begin();
        X ^= (*st.begin()) * (m - i + 1);
        mul += (*st.begin()) * (m - i + 1);
	}
	cout << sum << " " << X  << " " << mul;	
	return 0;
} 
```

---

## 作者：苏联小渣 (赞：2)

声明：这是一个比较暴力的思路，不保证每时每刻都能通过，也不保证不被 hack。hack 掉了跟我说一声。

首先统计区间可以双指针，因为 $l$ 增加 $r$ 一定单调不减，这是因为少取 $\max$ 一定不比多取 $\max$ 优。具体方法就是对于每个 $l$ 移动指针找到最小的 $r$ 使得进行 $[l,r]$ 之间的操作后可以得到最终序列，将 $m-r+1$ 统计如答案，再将 $l$ 删去。然后我们可以用一个常见的思路把最终的 $a$ 序列求出来，具体方法可以见 [P8024 [ONTAK2015] Stumilowy sad](https://www.luogu.com.cn/problem/P8024)。这样的话我们就可以通过最终的 $a$ 序列来判断进行了某些操作后的序列是否和最终的相同。

双指针统计答案的时候考虑把区间取 $\max$ 转化为区间加。考虑最终的序列 $a$，对 $a$ 里面每个不同的值开一棵线段树，对于这个值在序列里面所有出现过的位置，在线段树上开一个相应的结点。每个结点维护一个 tag。对于一次取 $\max$ 的操作 $\{L,R,x\}$，把 $x$ 这棵线段树的 $[L,R]$ 区间的 tag 全部加一。考虑一棵线段树 $T$，它所包含的结点里面，每一个结点都达到 $T$（也就是说，所有在最终序列里面满足 $a_i=T$ 的 $i$ 这个位置，都通过若干次取 $\max$ 次操作达到 $T$）的充要条件是没有一个结点的 tag 为 $0$。所以维护一个全局 $\min$，如果每一棵线段树的全局 $\min$ 都不为 $0$，那这个操作区间 $[l,r]$ 就是合法的。

以样例 $2$ 为例，最终序列是 $\{2,2,3\}$。所以开两棵线段树：第一棵，是 $2$ 这棵，在这棵线段树上开 $1,2$ 两个结点；第二棵，是 $3$ 这棵，开 $3$ 这个结点。初始时，$2,3$ 这两棵线段树的全局 $\min$ 都是 $0$。当 $l=1$ 时，我们这样移动指针：

- $r=1,\{L,R,x\}=\{1,3,2\}$。在 $2$ 这棵线段树上将区间 $[1,3]$ 加一。由于这棵线段树上只有 $1,2$ 两个结点，所以现在这棵线段树的全局 $\min$ 为 $1$，但是第三棵的全局 $\min$ 为 $0$，所以不合法；

- $r=2,\{L,R,x\}=\{1,1,1\}$。$1$ 这棵线段树不存在，跳过；

- $r=3,\{L,R,x\}=\{2,2,2\}$。在 $2$ 这棵线段树上将区间 $[2,2]$ 加一。此时这棵线段树上全局 $\min$ 依然为 $1$，但是第三棵的全局 $\min$ 为 $0$，所以不合法；

- $r=4,\{L,R,x\}=\{3,3,3\}$。在 $3$ 这棵线段树上将区间 $[3,3]$ 加一。此时这棵线段树上全局 $\min$ 为 $1$，并且第 $2$ 棵的也是 $1$，合法。

所以对于 $l=1,r=4$ 是最小的 $r$。所以对于 $l=1$，有 $m-r+1=2$ 个右端点可以选择。后面的操作类似。

这样做时间复杂度是 $O(m (\log m+\log n))$，时间大常数，空间是 $O(n \log m)$，带了一个 $4$ 的常数，完美地被卡了。

思考空间会怎么被卡。如果 $a$ 序列中每个数出现次数都极少，那么开的结点数就更趋近 $n \log m$；反过来，如果 $a$ 序列中所有数都趋近相同，那么总空间复杂度就是趋近 $O(n)$ 的。所以我们可以套路的使用阈值分治的方法，设定一个阈值 $B$，对于出现次数 $\le B$ 的使用暴力加暴力求 $\min$，出现次数 $>B$ 的用上面的线段树方法。这样时间复杂度是 $O(m(\log m+\log n+B))$ 的，空间复杂度不会算，但是肯定比上面的优。实测在 $B=5,10$ 都可以通过，不过比较极限。如果 $B$ 再开大一点可能就需要一些卡常技巧。

代码放[剪贴板](https://www.luogu.com.cn/paste/9m6f44iy)里面了。

---

## 作者：cyffff (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8936)
## 题意
你有一个长度为 $n$，初值全为 $0$ 的序列 $a$。

你有长为 $m$ 的操作序列，其中第 $i$ 次有三个参数 $l_i,r_i,x_i$，表示令 $\forall j\in[l_i,r_i] ,a_j\gets\max(a_j,x_i)$。

令 $\text{sol}(l,r)$ 表示依次操作第 $l$ 至第 $r$ 个操作后的 $a$ 序列。

你需要回答有多少对 $(l,r)$ 满足 $1\le l\le r\le m$ 且 $\text{sol}(l,r)=\text{sol}(1,m)$。

$1\le n,m\le 10^6$。
## 题解
### $n,m\le3\times 10^5$
与正解无关。这一部分分是口胡的，不知道对不对/能不能优化。

对每个位置维护一个 `multiset`，对于一次操作，将 $x_i$ 插入到 $l_i\sim r_i$ 的集合中。线段树维护。一个结点代表的区间的最大值就是其到根的路径上所有结点维护的集合的最大值的最大值。

考虑双指针，右移左指针会把一个区间的集合删掉一个数，如果是唯一最大值则不断右移指针直至重新加入相同的数。考虑找到相同 $x$ 的，包含此区间的下一次操作即可。二分。

时间复杂度可能是 $n\log^2n$（假设 $n,m$ 同阶）。
### $n,m\le 10^6$
令 $i$ 为右端点，考虑最大的左端点 $l_i$ 满足 $\text{sol}(l_i,i)=\text{sol}(1,m)$。

从大到小考虑 $x$，由于是和全局操作相等，每次只需要考虑操作 $1\sim m$ 后 $a_i=x$ 的位置。接下来仅考虑 $x_i=x$ 的操作。

用并查集把所有操作 $1\sim m$ 后 $a_i=x$ 的位置 $i$ 提出来（或者你直接求出最后的序列）。把每个操作的左右端点放到这些位置上二分出对应的区间。重新编号序列和操作。

考虑维护 $t_i$ 为最大的数使得仅考虑 $x_i=x$ 的操作，$[t_i,i]$ 的操作区间并能覆盖全局（这些位置）。使用颜色段均摊或者线段树，第 $i$ 个操作把 $[l_i,r_i]$ 推平为 $i$，操作完第 $i$ 个操作，$t_i$ 即为现在序列中的最小值。由于 $t_i$ 有单调性，维护一个指针往后扫即可。

设考虑的第 $i$ 个操作在原操作序列中的位置为 $id_i$，则对于 $[id_k,id_{k+1})$ 的操作，有且仅有 $k$ 一个 $x_i=x$ 的操作，必然要取到 $t_k$ 使得所有最终等于 $x$ 的数符合要求。所以 $\forall i\in[id_k,id_{k+1}),l_i\gets\min(l_i,t_k)$，注意还需要 $\forall i\in[1,id_{1}),l_i\gets0$。

由于 $t$ 的单调性，可以直接看为对前缀取 $\min$，在 $id_{k+1}-1$ 处标记一下，最后做一个后缀 $\min$ 即可。

最终答案是 $\sum_{i=1}^n l_i$。得到题目中的 $f_i$ 只需要再做一遍后缀和即可。

时间复杂度 $O(n\log n)$，瓶颈在于排序、二分、颜色段均摊。可以通过神秘数据结构做到 $O(n\log\log n)$，但不很有趣。

代码（仅供参考）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e6+10;
int n,m,lp[N],f[N],cnt[N],sf[N],s2[N];
struct oper{
	int l,r,id;
}a[N];
vector<oper>by[N];
int fa[N];
inline int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
struct node{
	int l;
	mutable int r,v;
	node(int L=0,int R=-1,int V=0){ l=L,r=R,v=V; }
	inline friend bool operator<(const node &a,const node &b){
		return a.l<b.l;
	}
};
set<node>tr;
#define sit set<node>::iterator
inline sit split(int p){
	sit it=tr.lower_bound(node(p));
	if(it!=tr.end()&&it->l==p)
	    return it;
	--it;
	int mr=it->r,mv=it->v;
	it->r=p-1;
	return tr.insert(node(p,mr,mv)).first;
}
inline void update(int l,int r,int c){
	sit itr=split(r+1),itl=split(l);
	for(sit it=itl;it!=itr;++it){
		cnt[it->v]-=(it->r)-(it->l)+1;
		cnt[c]+=(it->r)-(it->l)+1;
	}
	tr.erase(itl,itr);
	tr.insert(node(l,r,c));
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)
		a[i].l=read(),a[i].r=read(),a[i].id=i,
		by[read()].push_back(a[i]);
	for(int i=1;i<=m+1;i++)
		sf[i]=2e9;
	for(int i=1;i<=n+1;i++)
		fa[i]=i;
	for(int i=m;i>=1;i--){
		if(!by[i].size()) continue;
		vector<int>p;p.clear();
		for(auto j:by[i])
			for(int k=find(j.l);k<=j.r;k=find(k))
				p.push_back(k),fa[k]=k+1;
		int u=p.size(),ml=0;
		if(!p.size()) continue;
		tr.clear();tr.insert(node(1,u+1,0));
		sort(p.begin(),p.end());
		cnt[0]=u;
		for(int j=1;j<=by[i].size();j++)
			cnt[j]=0;
		sf[by[i][0].id-1]=min(sf[by[i][0].id-1],0);
		for(int t=0;t<by[i].size();t++){
			oper j=by[i][t];
			int pl=lower_bound(p.begin(),p.end(),j.l)-p.begin()+1;
			int pr=upper_bound(p.begin(),p.end(),j.r)-p.begin();
			if(pl<=pr) update(pl,pr,t+1);
			while(cnt[ml]==0) ml++;
			if(t!=by[i].size()-1) sf[by[i][t+1].id-1]=min(sf[by[i][t+1].id-1],ml?by[i][ml-1].id:0);
			else sf[m]=min(sf[m],ml?by[i][ml-1].id:0);
		}
	}
	for(int i=m;i>=1;i--)
		sf[i]=min(sf[i],sf[i+1]);
	for(int i=1;i<=m;i++)
		s2[sf[i]]++;
	for(int i=m;i>=1;i--)
		s2[i]+=s2[i+1];
	unsigned a1=0,a2=0,a3=0;
	for(unsigned i=1;i<=m;i++)
		a1+=s2[i],a2^=s2[i]*i,a3+=s2[i]*i;
	write(a1),putc(' '),write(a2),putc(' '),write(a3);
	flush();
}
```
再见 qwq~

---

## 作者：yyyyxh (赞：0)

~~出题人你空间时间卡得好啊！~~

看起来和标程不太一样，考虑对操作的区间 $[l_i,r_i]$ 的下标进行扫描线而不是对操作的值扫。用 $m$ 个 `set` 动态维护 $x_i$ 对应的操作的下标集合，再用一个可删堆来维护当前所有操作 $x_i$ 的最大值。这样的话 $\text{sol}(l,r)=\text{sol}(1,m)$ 必须满足 $[l,r]$ 至少包含一个 $x_i$ 为当前最大值的操作。

动态维护题目中要求的 $f_i$，发现题目中要我们支持若干个形如 $\forall i\in [l,r],f_i\leftarrow \max(f_i,r)$ 的操作，满足 $x_r$ 为当前最大值或者 $m+1$。

每个时间点当前最大值的个数之和是 $O(n^2)$ 的，但我们发现当你操作了一个 `set` 里的所有值后，后面再去操作这个 `set` 剔除掉跟之前重复的操作，只需要操作这个 `set` 新删去的点现在的前驱后继即可。也就是说，本质不同的对 $f_i$ 的区间取 `max` 操作在 $O(n)$ 级别。

注意到对 $f_i$ 的区间取 `max` 反正可以离线，干脆用扫描线+可删堆减少常数。

复杂度是 $O(n\log n)$，空间复杂度 $O(n)$。

然后你发现在出题人的精心策划下 $O(n)$ 个 `set` 被卡的又 M 又 T。

去掉所有的 `vector`，换用 $O(n)$ 个树状树组维护前驱后继才卡过去。

```cpp
#include <bits/stdc++.h>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
typedef unsigned int ui;
typedef pair<int,int> pii;
const int N=1000003;
int n,m,rk;
int a[N],id[N],len[N],sz[N],lg[N];
pii sins[N],sdel[N],ains[N];
priority_queue<int> que;
int *del[N],base[N],cnt[N];
int *tr[N],trbase[N];
int *od[N],odbase[N];
bitset<N> add;
void upd(int p,int x,int v){
	sz[p]+=v;
	for(int i=id[x];i<=len[p];i+=(i&-i)) tr[p][i-1]+=v;
}
int qry(int p,int x){
	int res=0;
	for(int i=id[x];i;i^=(i&-i)) res+=tr[p][i-1];
	return res;
}
int loc(int p,int v){
	int x=0;
	for(int i=(1<<lg[len[p]]);i;i>>=1)
		if(x+i<=len[p]&&tr[p][x+i-1]<v) v-=tr[p][(x+=i)-1];
	return od[p][x];
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;++i){
		sins[i]=pii(read(),i);
		sdel[i]=pii(read()+1,i);
		id[i]=++len[a[i]=read()];
	}
	del[1]=base;tr[1]=trbase;od[1]=odbase;lg[0]=-1;
	for(int i=1;i<m;++i){
		del[i+1]=del[i]+len[i];
		tr[i+1]=tr[i]+len[i];
		od[i+1]=od[i]+len[i];
	}
	for(int i=1;i<=m;++i) od[a[i]][id[i]-1]=i,lg[i]=lg[i>>1]+1;
	int ix=1,dx=1;
	sort(sins+1,sins+m+1);
	sort(sdel+1,sdel+m+1);
	for(int i=1;i<=n;++i){
		while(ix<=m&&sins[ix].first<=i){
			int x=sins[ix++].second;
			if(!sz[a[x]]) que.emplace(a[x]);
			upd(a[x],x,1);
		}
		while(dx<=m&&sdel[dx].first<=i){
			int x=sdel[dx++].second;
			upd(a[x],x,-1);
			del[a[x]][cnt[a[x]]++]=x;
		}
		while(!que.empty()&&!sz[que.top()]) que.pop();
		if(que.empty()) continue;
		int mx=que.top();
		if(add[mx]){
			for(int t=0;t<cnt[mx];++t){
				int val=qry(mx,del[mx][t]);
				int rig=m+1,lef=0;
				if(val<sz[mx]) rig=loc(mx,val+1);
				if(val) lef=loc(mx,val);
				ains[++rk]=pii(lef+1,rig);
			}
		}
		else{
			int las=0;
			for(int i=1;i<=sz[mx];++i){
				int x=loc(mx,i);
				ains[++rk]=pii(las+1,x);
				las=x;
			}
			ains[++rk]=pii(las+1,m+1);add.set(mx);
		}
		cnt[mx]=0;
	}
	while(!que.empty()) que.pop();
	unsigned int fa=0,fb=0,fc=0;
	ix=1;sort(ains+1,ains+rk+1);
	for(int i=1;i<=m;++i){
		while(ix<=rk&&ains[ix].first<=i) que.emplace(ains[ix++].second);
		while(!que.empty()&&que.top()<=i) que.pop();
		int tmp=i;
		if(!que.empty()) tmp=que.top();
		unsigned int res=m+1-tmp;
		fa+=res;fb^=res*i;fc+=res*i;
	}
	printf("%u %u %u\n",fa,fb,fc);
	return 0;
}

```

---

