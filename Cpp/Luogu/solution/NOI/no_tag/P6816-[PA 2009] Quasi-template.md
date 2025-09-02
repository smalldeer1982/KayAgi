# [PA 2009] Quasi-template

## 题目描述

定义一个串 $s$ 能匹配 $S$ 当且仅当 $s$ 能可超出头尾地覆盖
$S$ 且长度不超过 $S$，且 $s$ 必须是 $S$ 的子串。

如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/gpq807qg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

给定 $S$ ，求不同的 $s$ 的个数以及长度最短的 $s$，如有多解，输出字典序最小的。

## 说明/提示

符合条件的串：
aaaabaabaaab, aaaabaabaaaba, aaabaaba, aaabaabaa, aaabaabaaa, aaabaabaaaba, aabaa, aabaabaa, aabaabaaa, abaabaaa.

$S$ 的长度 $\leq 2\times 10^5$

## 样例 #1

### 输入

```
aaaabaabaaaba```

### 输出

```
10
aabaa```

# 题解

## 作者：dottle (赞：24)

此题题面翻译有误，应还有一个限制： $s$ 是 $S$ 是子串。~~在你看到这道题之前题面可能~~已经被修改了。

考虑怎样的子串 $s$ 可以匹配原串，条件有三个：

1.  考虑子串在 $S$ 中的所有出现位置，两个位置的间距不应大于 $|s|$。
2.  设 $s$ 第一次出现的左端点为 $l$，则 $l$ 左侧的部分再加 $l$ 右侧的一部分应是 $s$ 的一个后缀。 
3.  设 $s$ 最后一次出现的右端点为 $r$，则 $r$ 右侧的部分再加 $r$ 左侧的一部分应是 $s$ 的一个前缀。 

后两个条件是类似的，但是后续的处理方法不太相同，因此拆开写。 


---




首先考虑第一个条件，子串的出现位置这一问题引导我们想到 SAM，再加上“最大间距”这一条件，一个自然的想法是使用 SAM +线段树合并求出 $endpos$ 集合。线段树合并时，维护出此时所有间距中最大的一个。

依次考虑所有等价类，再考虑此等价类中有多少种符合题目条件的子串，我们就可以不重不漏地求出所有答案。现在我们考察 SAM 的一个节点，对于此节点对应的等价类，我们已经求出了以下信息：

-   首次出现的位置 $L$ 和末次出现的位置 $R$。
-   两次出现的最小间距 $x$。
-   此等价类对应的最小长度 $l_{min}$ 和最大长度 $l_{max}$。

接下来，将以样例中 $endpos=\{7,10\}$ （即 `aabaa` 所在的等价类）为例分析。 

考虑第一个条件，则有约束：

-   此等价类中合法子串的长度至少为 $x$。

考虑第二个条件，我们会猜想，是不是子串的长度越大越好呢？确实如此，因为超出部分可以超过 $S$ 的开头，不会使匹配失效。也就是说，我们只需要求出这个长度的最小值。考虑我们用当前的子串的后缀尽可能地匹配一段前缀，设匹配到的前缀长度为 $a$，则应当有 $a\ge L-len$。例子中 $a=2$，$L=7$，若 $len<5$，则中间会空一段子串无法匹配。观察这个 $a$ 的定义，发现它其实是 $1\sim L$ 这段前缀的 border。因此：

-   此等价类中合法子串的长度至少为 $L-border_L$。

考虑第三个条件，这时候是不是子串的长度越大越好呢？思考之后可以发现不一定，其与前缀的区别是超出部分仍然在 $S$ 中，可能会使匹配失效。因此，我们需要单独研究怎样的串才是满足第三个条件的。

不妨将等价类中的某一个子串单独提出来，考虑如何判断它是否合法。例如现在考虑 $R=10,len=5$ 的子串，即判断 `aabaa` 能否匹配 `aba`，注意此时向前超出的部分也需要判断是否合法，所以我们可以把他们拼在一起，变成了 `aabaaaba`，这其实是一个原串的后缀。这时不妨倒过来思考，考虑对于一个后缀，在 $R$ 满足什么条件的时候，这个后缀才是合法的。用这个串来重新描述 $R$ 的合法条件：前缀 $R$ 在截去一段后缀后，等于一个后缀 $i\le R+1$。前缀截取掉后缀以后还是前缀，也就是说条件就变成了：一个前缀可以完全匹配一个后缀，这就是 border！那么我们猜想，当 $R\ge n- border_i$ （$border_i$ 代表 $i$ 这个后缀的 border）时，$i$ 这个后缀是合法的。但是这个猜想有一个自然的反例：若 $border_i$ 大于后缀 $i$ 长度的一半，那么这个结论是有问题的。例如对于后缀 `aabaabaab`，$R=3$ 并不合法。然而，此反例是不可能成立的。注意我们选取的 $R$ 是等价类中最后的位置，因此如果 $border_i$ 大于 $i$ 长度的一半，那么以下两个条件就不可能同时满足：

1.  $R$ 在后缀 $i$ 的前一半。
2.  $i\sim R$ 属于当前考虑的等价类。

对于前一种情况，$i$ 的计算不存在问题；对于后一种情况，$i$ 根本不会被计算到。因此，我们的猜想是可以用来计算的。

最后，我们把所有条件整合到一起：

1.  子串的长度有三个下界：SAM 中求出的下界；$L-border_L$；最大间距 $x$。
2.  子串的长度有一个上界：SAM 中求出的上界。
3.  子串的起始位置 $i$ 有限制：$R\ge n-border_i$。

---

现在，我们已经考虑好了所有的条件约束。现在可以开始设计代码实现了：

1.  SAM + 线段树合并。需要求的东西上面已经列出。
2.  正串反串分别 KMP。正串用来求条件 $2$ 的约束，反串用来求条件 $3$ 的约束。
3.  考虑每一个等价类如何统计满足条件的点：这相当于是求一段区间中小于等于 $x$ 的元素的数量。可以离线树状数组，也可以在线主席树。

到此，我们就解决了问题的第一个部分。

接下来考虑第二部分，如何求出最短的解呢？

1.  考虑每一个等价类，相当于要求出一段区间内最后一个小于等于 $x$ 的元素的位置，这个也可以用主席树解决。
2.  若两个串长度相等，怎么比较它们的字典序？可以用 SA，也可以二分 + Hash 解决。



这样，我们就解决了这道题目。

---


总结一下这道题。首先考虑到用直观的语言描述题目的条件，然后尝试将其改写成容易约束的形式，最后再根据条件书写代码。其中的思考过程并非独立，大多都都是对题目性质的综合思考。例如第三个条件我们转化后的约束的正确性不仅来自 border 的性质，还来源于我们先前的 SAM 的性质。这种综合地观察性质，发现困难的问题的特殊性质，而非简单地套模板的思考过程是很有价值的。

---

## 作者：_SeeleVollerei_ (赞：7)

模拟赛赛时独立做出来很不容易，而且是赛时直接写对了，但是因为最后一步犯傻 T 了，很可惜。

来讲一下正解，顺便和多哥同页合影。

因为要枚举子串，所以先把原串放到 SAM 上处理。

先不考虑左右凸出来的部分，只考虑中间一直叠的部分，那么考虑每个串的 endpos 集合。把 endpos 的位置记为 $p_{[1,m]}$，那么对于 $1\le i<m$，$p_{i+1}-p_i\le len$。

然后 endpos 集合是可以线段树合并做的，这个是 SAM 经典用法。

现在相当于要维护 $\max_{1\le i<m}\{p_{i+1}-p_i\}$，这个线段树是好做的，每个点维护它的最大值，以及最小和最大的 $p_i$ 即可。因为只涉及单点修改，所以只用考虑 update，所以很简单。

考虑两边凸出来的部分。前缀相当于要求一个类似 border 的东西，大概就是最长的长度满足子串的后缀与原串的前缀匹配。但是我们发现子串的后缀一定是这个子串在 SAM 上结点的某个祖先。进一步地，就是深度最深的满足是原串前缀的祖先。

这样前缀的 border 就好做了。我们假设不管后缀，那么现在已经可以根据结点代表的等价类以及 border 的限制求出合法的串的两个端点的两个区间。

后缀怎么做？我们把原串反过来再跑一次就好了。

怎么把前后缀结合起来？

先镜像一下，弄出后缀在原串中对应的区间。

那么只要一个串同时前缀和后缀同时满足条件，这个串就是合法的。

现在的子问题转化为有很多对区间加，$[[l_1,r_1],[l_2,r_2]]$ 满足 $l_1\le r_1\le l_2\le r_2$，求有多少对 $[l,r]$ 的值为 2。

这个看似要多的数据结构，实际上这就是个差分，以 $[l_1,r_1]$ 为下标，存一个 vector 表示往后要加入/删除这个 $[l_2,r_2]$ 即可。

最后就是从前往后扫一遍了，然后用线段树维护对 $[l_2,r_2]$ 的区间加，全局求最大值，全局求最大值个数。

求合法子串个数迎刃而解了。压力来到求最小字典序这边。

这个其实很简单了，考虑扫的过程中，对于每一个左端点，在线段树上二分一个最小的右端点满足值为 2，那么每个左端点的最优串就出来了。

比大小考虑二分加哈希，二分第一个不同的字符即可。

总的复杂度为 $O(n\log n)$。

放个很丑的代码，但是你会发现我用线段树的函数名和参数名写了个差分？因为我一开始也直接莽线段树了。以及有一个和搜索不沾边的名为 Dfs 的函数，也是我一开始打算遍历线段树的。

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef pair<int,int> pr;
const int N=2e5+5;
const int Z=26;
const int Mod=1e9+7;
int ch[N<<1][Z],las=1,tot=1,len[N<<1],fa[N<<1],pos[N<<1];
char s[N];
int n;
inline void Insert(int k){
	int c=s[k]-'a';
	int u=las;
	int x=las=++tot;
	pos[x]=k;
	len[x]=len[u]+1;
	while(u&&!ch[u][c]){
		ch[u][c]=x;
		u=fa[u];
	}
	if(!u) fa[x]=1;
	else{
		int v=ch[u][c];
		if(len[v]==len[u]+1) fa[x]=v;
		else{
			int y=++tot;
			fa[y]=fa[v];
			for(int i=0;i<Z;i++)
				ch[y][i]=ch[v][i];
			fa[v]=fa[x]=y;
			len[y]=len[u]+1;
			while(u&&ch[u][c]==v){
				ch[u][c]=y;
				u=fa[u];
			}
		}
	}
	return ;
}
inline int Max(int x,int y){
	return x>y?x:y;
}
inline int Min(int x,int y){
	return x<y?x:y;
}
inline void Cmax(int&x,int y){
	if(y>x) x=y;
	return ;
}
inline void Cmin(int&x,int y){
	if(y<x) x=y;
	return ;
}
int tol[N*50],tor[N*50],mx[N*50],lc[N*50],rc[N*50],tott,root[N<<1];
inline void Update(int u){
	if(lc[u]) tol[u]=tol[lc[u]];
	else tol[u]=tol[rc[u]];
	if(rc[u]) tor[u]=tor[rc[u]];
	else tor[u]=tor[lc[u]];
	mx[u]=Max(Max(mx[lc[u]],mx[rc[u]]),tol[rc[u]]-tor[lc[u]]);
	return ;
}
inline void Change(int&u,int ll,int rr,int p){
	if(!u) u=++tott;
	if(ll==rr){
		tol[u]=tor[u]=ll;
		mx[u]=0;
		return ;
	}
	int mid=ll+rr>>1;
	if(mid>=p) Change(lc[u],ll,mid,p);
	else Change(rc[u],mid+1,rr,p);
	return Update(u);
}
inline int Merge(int u,int v,int ll,int rr){
	if(!u||!v) return u+v;
	int now=++tott;
	if(ll==rr){
		tol[now]=tor[now]=ll;
		mx[now]=0;
		return now;
	}
	int mid=ll+rr>>1;
	lc[now]=Merge(lc[u],lc[v],ll,mid);
	rc[now]=Merge(rc[u],rc[v],mid+1,rr);
	Update(now);
	return now;
}
int Head[N<<1],Nxt[N<<1],ver[N<<1],cnt_edge=-1;
inline void Add(int u,int v){
	++cnt_edge;
	ver[cnt_edge]=v;
	Nxt[cnt_edge]=Head[u];
	Head[u]=cnt_edge;
	return ;
}
inline void Add_Edge(int u,int v){
	Add(u,v);
	//Add(v,u);
	return ;
}
inline void Clear(){
	memset(ch,0,sizeof(ch));
	memset(fa,0,sizeof(fa));
	memset(len,0,sizeof(len));
	memset(pos,0,sizeof(pos));
	memset(Head,-1,sizeof(Head));
	tott=0;
	tot=las=1;
	cnt_edge=-1;
	return ;
}
struct SGT{
	vector<pr>add[N],sub[N];
	inline void Insert(int u,int ll,int rr,int l1,int r1,int l2,int r2){
		add[l1].push_back(make_pair(l2,r2));
		sub[r1+1].push_back(make_pair(l2,r2));
		return ;
	}
}pre,suf;
inline void DfsPre(int u,int las){
	if(pos[u]) Change(root[u],1,n,pos[u]);
	for(int i=Head[u];i!=-1;i=Nxt[i]){
		int v=ver[i];
		if(pos[u]) DfsPre(v,pos[u]);
		else DfsPre(v,las);
		root[u]=Merge(root[u],root[v],1,n);
	}
	int rt=root[u];
	int nd=mx[rt];
	int mnlen=Max(len[fa[u]]+1,nd);
	int mnr=tol[rt];
	int mxlen=len[u];
	if(pos[u]){
		mxlen--;
		if(len[u]>=mnlen&&2*len[u]>=mnr) pre.Insert(1,1,n,1,1,len[u],len[u]);
	}
	if(las){
		int border=las;
		Cmax(mnlen,mnr-border);
		if(mnlen<=mxlen) pre.Insert(1,1,n,mnr-mxlen+1,mnr-mnlen+1,mnr,mnr);
	}
	return ;
}
inline void DfsSuf(int u,int las){
	if(pos[u]) tol[u]=tor[u]=pos[u];
	else tol[u]=n+1,tor[u]=0;
	for(int i=Head[u];i!=-1;i=Nxt[i]){
		int v=ver[i];
		if(pos[u]) DfsSuf(v,pos[u]);
		else DfsSuf(v,las);
		Cmin(tol[u],tol[v]);
		Cmax(tor[u],tor[v]);
	}
	int mnlen=len[fa[u]]+1;
	int mnr=tol[u];
	int mxlen=len[u];
	int l=n-tor[u]+1;
	if(pos[u]){
		mxlen--;
		if(len[u]>=mnlen&&2*len[u]>=mnr) suf.Insert(1,1,n,l,l,l+len[u]-1,l+len[u]-1);
	}
	if(las){
		int border=las;
		Cmax(mnlen,mnr-border);
		if(mnlen<=mxlen) suf.Insert(1,1,n,l,l,l+mnlen-1,l+mxlen-1);
	}
	return ;
}
inline void Init(){
	scanf("%s",s+1);
	n=strlen(s+1);
	return ;
}
struct SGT1{
	int mxx[N<<2],mxcnt[N<<2],tag[N<<2];
	inline void Addcnt(int u,int value){
		mxx[u]+=value;
		tag[u]+=value;
		return ;
	}
	inline void PushDown(int u){
		if(tag[u]==0) return ;
		Addcnt(u<<1,tag[u]);
		Addcnt(u<<1|1,tag[u]);
		tag[u]=0;
		return ;
	}
	inline void Update(int u){
		mxx[u]=Max(mxx[u<<1],mxx[u<<1|1]);
		mxcnt[u]=0;
		if(mxx[u<<1]==mxx[u]) mxcnt[u]+=mxcnt[u<<1];
		if(mxx[u<<1|1]==mxx[u]) mxcnt[u]+=mxcnt[u<<1|1];
		return ;
	}
	inline void Build(int u,int ll,int rr){
		if(ll==rr){
			mxcnt[u]=1;
			return ;
		}
		int mid=ll+rr>>1;
		Build(u<<1,ll,mid);
		Build(u<<1|1,mid+1,rr);
		return Update(u);
	}
	inline void Modify(int u,int ll,int rr,int ql,int qr,int value){
		if(ll>=ql&&rr<=qr) return Addcnt(u,value);
		PushDown(u);
		int mid=ll+rr>>1;
		if(mid>=ql) Modify(u<<1,ll,mid,ql,qr,value);
		if(mid<qr) Modify(u<<1|1,mid+1,rr,ql,qr,value);
		return Update(u);
	}
	inline int Find(int u,int ll,int rr){
		if(ll==rr) return ll;
		PushDown(u);
		int mid=ll+rr>>1;
		if(mxx[u<<1]==2) return Find(u<<1,ll,mid);
		return Find(u<<1|1,mid+1,rr);
	}
}sgt;
LL ans;
int ansfr,anslen;
inline void AddEnd(int u,int value){
	for(int i=0;i<pre.add[u].size();i++){
		int fr=pre.add[u][i].first;
		int se=pre.add[u][i].second;
		sgt.Modify(1,1,n,fr,se,1);
	}
	for(int i=0;i<suf.add[u].size();i++){
		int fr=suf.add[u][i].first;
		int se=suf.add[u][i].second;
		sgt.Modify(1,1,n,fr,se,1);
	}
	for(int i=0;i<pre.sub[u].size();i++){
		int fr=pre.sub[u][i].first;
		int se=pre.sub[u][i].second;
		sgt.Modify(1,1,n,fr,se,-1);
	}
	for(int i=0;i<suf.sub[u].size();i++){
		int fr=suf.sub[u][i].first;
		int se=suf.sub[u][i].second;
		sgt.Modify(1,1,n,fr,se,-1);
	}
	return; 
}
inline int addv(int x,int y){
	int s=x+y;
	if(s>=Mod) s-=Mod;
	return s;
}
inline int subv(int x,int y){
	int s=x-y;
	if(s<0) s+=Mod;
	return s;
}
inline void add(int&x,int y){
	x=addv(x,y);
	return ;
}
inline void sub(int&x,int y){
	x=subv(x,y);
	return ;
}
int hsh[N],pw[N];
inline int Get(int ll,int rr){
	return subv(hsh[rr],1ll*hsh[ll-1]*pw[rr-ll+1]%Mod);
}
inline void Dfs(int u,int ll,int rr){
	for(int i=1;i<=n;i++){
		AddEnd(i,114514);
		if(sgt.mxx[1]!=2) continue ;
		ans+=sgt.mxcnt[1];
		int mnr=sgt.Find(1,1,n);
		int len=mnr-i+1;
		if(len<anslen){
			anslen=len;
			ansfr=i;
		}
		else if(len==anslen){
			int l=1,r=len;
			while(l<r){
				int mid=l+r>>1;
				if(Get(ansfr,ansfr+mid-1)==Get(i,i+mid-1)) l=mid+1;
				else r=mid;
			}
			if(s[ansfr+l-1]>s[i+l-1]) ansfr=i;
		}
	}
	return ;
}
inline void Solve(){
	memset(Head,-1,sizeof(Head));
	memset(tor,0x3f,sizeof(tor));
	for(int i=1;i<=n;i++)
		Insert(i);
	for(int i=2;i<=tot;i++)
		Add_Edge(fa[i],i);
	DfsPre(1,0);
	reverse(s+1,s+n+1);
	Clear();
	for(int i=1;i<=n;i++)
		Insert(i);
	for(int i=2;i<=tot;i++)
		Add_Edge(fa[i],i);
	DfsSuf(1,0);
	reverse(s+1,s+n+1);
	pw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=26ll*pw[i-1]%Mod;
		hsh[i]=addv(26ll*hsh[i-1]%Mod,s[i]-'a');
	}
	sgt.Build(1,1,n);
	anslen=n+1;
	Dfs(1,1,n);
	printf("%lld\n",ans);
	for(int i=1;i<=anslen;i++)
		putchar(s[ansfr+i-1]);
	putchar('\n');
	return ;
}
int main(){
	Init();
	Solve();
	return 0;
}
```

---

## 作者：Richard_Whr (赞：3)

为啥大家都用了一万种算法啊，让人一看就不想写的样子。

给出一个只用 $\operatorname{SAM}$ 的简单做法。

题目中要求了 $s$ 本质不同，且是 $S$ 的子串，自然想到在 $\operatorname{SAM}$ 中考虑一个节点上的等价类，尝试刻画满足条件的限制。

一个等价类是固定了 $\operatorname{endpos}$ 集合，长度属于 $[L,R]$ 的一类拥有共同后缀的子串。

最容易看出是的限制串的长度不能小于， $\operatorname{endpos}$ 集合里面，相邻两项之差的最大值，即 $Len \ge \max(p_i-p_{i-1})$，相当于对串长的下界 $\operatorname{chkmax}$。对于 $\max(p_i,p_{i-1})$ 可以在 $\operatorname{SAM}$ 上跑线段树合并的时候求出来。

然后就是考虑首尾的问题，相对棘手一点。

先考虑前缀，注意到一定是等价类结点的一段后缀去匹配原串的一段后缀，那我们对于每个串处理出来他的后缀能匹配的最长前缀 $f_u$ 即可。

这个可以找到每个前缀在后缀树上的结点，设前缀的长度为 $k$，则后缀树上这个结点的子树的 $f_u$ （不包括这个节点，因为你能匹配的原串前缀长度显然不能超过当前子串串长）都可以和 $k$ $\operatorname{chkmax}$。

这样做完之后要求每个等价类 $u$ 里面的串长：$Len \ge firstpos-f_u$，仍然是对串长下界进行 $\operatorname{chkmax}$。

然后我们现在会前缀了限制了，发现后缀超麻烦，不过如果反过来就又是前缀了，但是这样做如何把两个限制集成到字串上又是问题。

我们考虑每个子串在他第一次出现的时候被检查是否合法，这样可以不重不漏。把所有限制达到二维平面上，最终我们数有几对 $(l,r)$ 合法即可。比如刚才处理前缀部分时，后缀自动机上一个结点的限制可以处理为 $r=firstpos,l \in [firstpos-R+1,firstpos-L+1]$ 的部分是合法的。

此时对于后缀部分，在和前缀一样处理出 $L,R$ 后，由于我们倒着建的 $\operatorname{SAM}$，因此需要把限制打到：$l = n-lastpos+1,r \in [n-(lastpos-L+1)+1,n-(lastpos-R+1)+1]$ 上面。

容易发现上面的限制在二维平面上都是矩形，我们要做的就是求矩形并的面积，直接扫描线就好了。

最后是处理长度最小下字典序最小的合法串，扫描线扫右端点的时候在线段树上二分一个最靠后的合法左端点。

然后求这 $n$ 个串里面长度最小下字典序最小的。

比较字典序需要求后缀 $\operatorname{Lcp}$，相当于反串的 $$\operatorname{SAM}$$ 上两个点 $\operatorname{Lca}$ 的最大长度。

如果你嫌 $\operatorname{SAM}$ 还得写 $\operatorname{Lca}$ 那你可以直接二分哈希，我就是这样写的。

温馨提示：凉心出题人卡掉了启发式合并的 $O(n \log^2 n)$ 做法，还是要写线段树合并的。

```cpp
#include<bits/stdc++.h>
#define x first
#define y second 
using namespace std;
typedef long long LL; 
typedef unsigned long long ULL;
const int N=4e5+10,M=26,B=131;
typedef pair<int,int> PII;
typedef tuple<int,int,int> I3;
char s[N];
ULL p[N],h[N];
int n;
vector<I3> vec[N];

inline ULL get(int l,int r)
{
	return h[r]-h[l-1]*p[r-l+1];
}

void Hash()
{
	p[0]=1;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*B;
	for(int i=1;i<=n;i++) h[i]=h[i-1]*B+s[i];
}

inline int Lcp(int x,int y)
{
	int l=1,r=min(n-x+1,n-y+1),ans=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(get(x,x+mid-1)==get(y,y+mid-1)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

struct Node
{
	int ch[M];
	int fa,len;
}tr[N];
vector<int> e[N];
int pos[N];
int bd[N];
int last,tot;
void init()
{
	last=tot=1;
}
void insert(int c,int x)
{
	int p=last,u=last=++tot;
	tr[u].len=tr[p].len+1;
	pos[u]=x;
	while(p && !tr[p].ch[c]) tr[p].ch[c]=u,p=tr[p].fa;
	if(!p) tr[u].fa=1;
	else
	{
		int q=tr[p].ch[c];
		if(tr[q].len==tr[p].len+1) tr[u].fa=q;
		else
		{
			int nq=++tot;
			tr[nq]=tr[q];
			tr[nq].len=tr[p].len+1;
			while(p && tr[p].ch[c]==q) tr[p].ch[c]=nq,p=tr[p].fa;
			tr[q].fa=tr[u].fa=nq;
		}
	}
}
void build()
{
	for(int i=2;i<=tot;i++) e[tr[i].fa].push_back(i);
}
void clear()
{
	for(int u=1;u<=tot;u++) e[u].clear(),pos[u]=bd[u]=0,memset(tr[u].ch,0,sizeof tr[u].ch),tr[u].fa=tr[u].len=0;
	last=tot=1;
}

#define Ls T[u].l
#define Rs T[u].r
struct SGT
{
	int l,r;
	int mx,Lp,Rp;
}T[N*20];
int S[N];
int idx;

inline void Up(int u)
{
	if(!Ls) return T[u].mx=T[Rs].mx,T[u].Lp=T[Rs].Lp,T[u].Rp=T[Rs].Rp,void(0);
	if(!Rs) return T[u].mx=T[Ls].mx,T[u].Lp=T[Ls].Lp,T[u].Rp=T[Ls].Rp,void(0);
	T[u].mx=max(T[Ls].mx,T[Rs].mx);
	T[u].mx=max(T[u].mx,T[Rs].Lp-T[Ls].Rp);
	T[u].Lp=T[Ls].Lp,T[u].Rp=T[Rs].Rp;
}

int merge(int u,int v)
{
	if(!u || !v) return u+v;
	Ls=merge(Ls,T[v].l);
	Rs=merge(Rs,T[v].r);
	Up(u);
	return u;
}

void Insert(int &u,int l,int r,int p)
{
	if(!u) u=++idx;
	if(l==r) T[u].Lp=T[u].Rp=p;
	else
	{
		int mid=l+r>>1;
		if(p<=mid) Insert(Ls,l,mid,p);
		else Insert(Rs,mid+1,r,p);
		Up(u);
	}
}

void Add_range(int l1,int r1,int l2,int r2)
{
	vec[l1].push_back({l2,r2,1});
	vec[r1+1].push_back({l2,r2,-1});
}

void Dfs_pre(int u)
{
	int bod=bd[u];
	if(pos[u]) bd[u]=pos[u],Insert(S[u],1,n,pos[u]);
	for(auto v:e[u])
	{
		bd[v]=bd[u];
		Dfs_pre(v);
		S[u]=merge(S[u],S[v]);
	}	
	int fp=(T[S[u]].Lp),nd=T[S[u]].mx;
	int L=max(tr[tr[u].fa].len+1,max(nd,fp-bod)),R=tr[u].len;
	
	if(L<=R) Add_range(fp,fp,fp-R+1,fp-L+1);
}

int mx[N],mn[N];
void Dfs_suf(int u)
{
	mx[u]=0,mn[u]=N+1;
	int bod=bd[u];
	if(pos[u]) bd[u]=pos[u],mx[u]=mn[u]=pos[u];
	for(auto v:e[u])
	{
		bd[v]=bd[u];
		Dfs_suf(v);
		mx[u]=max(mx[u],mx[v]);
		mn[u]=min(mn[u],mn[v]);
	}
	int lp=mx[u],fp=mn[u];
	int L=max(tr[tr[u].fa].len+1,fp-bod),R=tr[u].len;
	if(L<=R) Add_range(n-(lp-L+1)+1,n-(lp-R+1)+1,n-(lp)+1,n-(lp)+1);
} 

#define ls u*2
#define rs u*2+1
struct Tree
{
	int l,r;
	int mx,mc;
	int add;
}Tr[N*4];

void build(int u,int l,int r)
{
	Tr[u]={l,r,0,r-l+1,0};
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
}

inline void pushup(int u)
{
	Tr[u].mx=max(Tr[ls].mx,Tr[rs].mx),Tr[u].mc=0;
	if(Tr[ls].mx>=Tr[u].mx) Tr[u].mc+=Tr[ls].mc;
	if(Tr[rs].mx>=Tr[u].mx) Tr[u].mc+=Tr[rs].mc;
}

inline void Add(int u,int c)
{
	Tr[u].mx+=c,Tr[u].add+=c;
}

void pushdown(int u)
{
	if(!Tr[u].add) return;
	Add(ls,Tr[u].add),Add(rs,Tr[u].add),Tr[u].add=0;
}

void modify(int u,int l,int r,int c)
{
	if(Tr[u].l>=l && Tr[u].r<=r) Add(u,c);
	else
	{
		pushdown(u);
		int mid=Tr[u].l+Tr[u].r>>1;
		if(l<=mid) modify(ls,l,r,c);
		if(r>mid) modify(rs,l,r,c);
		pushup(u);
	}
}

int find(int u)
{
	if(Tr[u].l==Tr[u].r) return Tr[u].r;
	pushdown(u);
	if(Tr[rs].mx>=2) return find(rs);
	return find(ls);
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>(s+1);
	n=strlen(s+1);
	
	Hash();
	
	init();
	for(int i=1;i<=n;i++) insert(s[i]-'a',i);
	build();
	
	Dfs_pre(1);
	clear();
	
	for(int i=n;i>=1;i--) insert(s[i]-'a',n-i+1);
	build();
	
	Dfs_suf(1); 
	
	build(1,1,n);
	
	LL res=0;
	PII Ans={0,n+1};
	for(int i=1;i<=n;i++)
	{
		for(auto [l,r,c]:vec[i]) modify(1,l,r,c);
		if(Tr[1].mx>=2) 
		{
			res+=Tr[1].mc;
			int l=find(1),r=i; 
			if(Ans.y-Ans.x>r-l) Ans={l,r};
			else if(Ans.y-Ans.x==r-l)
			{
				int t=Lcp(Ans.x,l);
				if(t<r-l+1 && s[Ans.x+t]>s[l+t]) Ans={l,r}; 
			}
		}
	}
	cout<<res<<"\n";
	
	auto [l,r]=Ans;
	for(int i=l;i<=r;i++) cout<<s[i];
	cout<<"\n";
	
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# P6816 题解



[Problem Link](https://www.luogu.com.cn/problem/P6816)



## 题目大意

> 对于一个字符串 $T$ 的一个子串 $M$，如果 $M$ 满足 $T$ 中的每个字符都至少被 $M$ 的某一次出现所覆盖，则称 $M$ 是 $T$ 的一个 Template。
>
> 对于 $T$ 的一个子串 $M$，如果存在一个字符串 $S$ 使得 $M$ 是 $S$ 的一个 Template 且 $T$ 是 $S$ 的一个子串，则称 $M$ 是 $T$ 的一个 Quasi-Template。
>
> 给定长度为 $n$ 的字符串 $S$，求 $S$ 有多少个本质不同的 Quasi-Template，并输出所有这样的 Quasi-Template 中最短的一个（多个输出字典序最小者）。
>
> 数据范围：$n\le 2\times 10^5$。



## 思路分析

先考虑如何计数 $S$ 的所有 Template，考虑一个本质的做法：对 $S$ 建立后缀自动机，用线段树合并维护每个等价类 $p$ 的 $\mathrm{Endpos}$ 集合 $E_p$，我们只需要求出 $|M|=len$ 的范围即可。

首先由于 $S_n$ 要被覆盖，因此 $n\in E_p$，其次我们知道任意两个相邻的 Endpos 之间都要被 Template 覆盖，因此设 $g$ 为所有相邻的 Endpos 之间的最大距离，那么我们知道 $len\ge g$，同理，为了覆盖 $S_1$ 得到 $len\ge \min\{E_p\}$，显然 $g$ 和 $\min\{E_p\}$ 可以在线段树合并的过程中轻松维护。

因此根据如上的限制，我们可以把 $len$ 的区间写成 $[\max\{g,\min\{E_p\},\mathrm{len}(\mathrm{link}(p))+1\},\mathrm{len}(p)]$，得到 $len$ 的区间后，容易证明任意一个长度都是合法的。



接下来回到原问题上：

为例覆盖相邻两个 Endpos 之间的字符，我们依然有 $len\ge g$，设第一个和最后一个 Endpos 分别是 $L$ 和 $R$，我们只需要满足前后缀的限制即可。



先考虑前缀上的限制：

此时还剩 $S[1\dots L-len]$ 未被 $M$ 覆盖，因此要有一个 $x\ge L-len$ 使得 $S[1\dots x]$ 要是 $M$ 的一个后缀，又因为 $M=S[L-len+1\dots L]$，因此 $S[1\dots x]$ 要是 $S[1\dots L]$ 的一个 Border。

注意到此时我们根据贪心可以把这个限制写成 $L-len\le \min(len,\mathrm{Border}(S[1\dots L]))$，因此得到：$len\ge \lceil L/2\rceil$ 且 $len\ge \mathrm{Border}(S[1\dots L])$，显然预处理出 $S$ 的前缀 kmp 即可解决。



然后考虑后缀上的限制：

同理我们得到 $n-R\le \min(len,\mathrm{Border}(S[R-len+1\dots n]))$，先处理 $len\le n-R$ 的限制，最后可以规约到如下两个条件：

- $len\in [lo,hi]$，其中 $lo,hi$ 是我们对这个等价类根据上述过程算出来的长度范围限制。
- $\mathrm{Border}(S[R-len+1\dots n])\ge n-R$。 



注意到在第一个条件的限制下，合法的 $R-len+1$ 被缩减到了区间 $[R-hi+1,R-lo+1]$ 中，我们只需要数在这个区间内有多少个 $x$ 满足 $\mathrm{Border}(S[x\dots n])\ge n-R$ 即可，预处理出后缀 kmp 然后用主席树维护二维数点即可，当然也可以进行离线二维数点减小常数。



接下来考虑第二问，前面的过程都一样，首先我们考虑如何求出最短的一个字符串，显然我们要在 $x$ 对应的区间中维护最大的满足这样条件的 $x$，用 ST 表搭配二分即可解决。

最后我们要解决按字典序排序的问题，快速比较两个子串的字典序等价于快速求出两个子串的 $\mathrm{lcp}$，显然可以用 ST 表维护后缀数组解决。



综上所述，我们需要实现如下的数据结构 / 字符串结构：

- 后缀自动机 + 线段树合并（维护 Endpos 等价类）。
- kmp + 主席树 + ST 表（维护对后缀的限制）。
- 后缀数组 +ST 表（快速比较字典序）。

仔细实现每一个部分即可。

时间复杂度 $\mathcal O(n\log n)$。



## 代码呈现

[Code Links](https://pastebin.ubuntu.com/p/ZnRr5kR8jp/)

---

