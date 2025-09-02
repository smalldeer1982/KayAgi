# [NFLSPC #6] 啊，忘记了。

## 题目背景

> 好像忘了什么事…… 算了，想必不是什么重要的事吧。

## 题目描述



你在你的电脑上发现了 $n$ 份文本。冥冥之中，你没来由地感觉这似乎全都是一份记录的复制。

- 首先，原始记录是一个长度未知（甚至可以为空）的字符串，称作 **记录串**。对于一份复制，其将记录串切成了三段 **可以为空** 的字符串 **片段**。**每份复制中切割方案不保证相同**。你暂且将这三份 **片段** 依次称作 **前面**，**中间** 和 **后面**。
- 某些复制中的某些片段可能被忘记了。具体而言，前面有可能被替换为 `QIANMIANWANGLE`，中间有可能被替换为 `ZHONGJIANWANGLE`，后面有可能被替换为 `HOUMIANWANGLE`；在发生替换的场合，表示这一段片段被 **完全遗忘** 了；否则，表示该片段被 **完整保存**。
- 你有一种预感，记录串中的所有字符都是 **小写英文字符**。
- $n$ 份复制不一定自洽。

你的目标是，寻找初始的记录串。这个记录串需要满足所有字符均是小写英文字符。你希望其匹配尽量多的复制串。

- 记录串与复制串匹配的要求是，存在记录串的一种划分，使得其中记录串的三段与复制串的三段分别相同，或者复制串中这段划分忘了（此时本段划分中，记录串为任何可以为空的小写英文字符串均合法）。

你希望求出该记录串能匹配的最多复制串数目。**至于记录串本身，你感觉它并不是很重要，所以你不需要求出它**。

> / 我，毋畏遗忘 /

## 说明/提示

### 样例 1 解释

你希望这个串是 `nflsalgonflspcqidong`。你确信，不会再有其它串比它更匹配现存的记录了。

### 数据范围与约定

对于所有数据，保证输入的所有字符串长度之和不超过 $5\times 10 ^ 5$。

- 子任务 1（$30$ 分）：保证所有复制的 “后面” 段都是 `H`。
- 子任务 2（$70$ 分）：无特殊限制。

Source：NFLSPC #6 K by Troverld

## 样例 #1

### 输入

```
3
nflsalgo Z H
Q nflspc H
Q Z qidong
```

### 输出

```
3
```

# 题解

## 作者：xtx1092515503 (赞：3)

出题人的一些碎碎念：

- 这道题在出题组内部代号是原神 III，而 P9934 的内部代号是原神 I。（猜猜看原神 II 在哪里？或许以后有机会见到。或许你见到的有可能是原神 IV！）
- 这道题的英文名称是 `oblivion`。（而未能出场的原神 II 的英文名称是 `lethe`。虽然本人也是原神 I 的出题人，但因为原神 I 的题解是 Alex_Wei 写的所以在这里提一句，原神 I 的英文名称是 `forget`。）
- 这道题代码写起来非常答辩。（原神 I 同理）
- 感谢 Alex_Wei 验题（原神 I 同理）。不然两题会出 1064 个锅。
- 题面里埋了 Ave Mujica 的梗。（什么？你还没看过 MyGO？？？）
- 原神 I 的题面里 neta 了泰戈尔的一首诗，和 *君の名は* 的 PV。
- ~~在现场赛时，出题人不小心下发了本题的数据——但是是 debug 过程中输出有误的数据。这下真成提答题了。~~
- 出题人写了 `20` 个不同的 `gen`。（原神 I 则写了 `10` 个）
- 出题人认为本题的思维难度是蓝，而原神 I 的思维难度是黄。原神 I 评蓝是 Alex_Wei 的锅。
- 样例很弱真的很抱歉。我什么都不会做的。

------

首先考虑记录串未匹配任何前、中、后均确定的复制串的场合。此时，将与其匹配的复制串分类（其中，小写字母表示其是确定串，大写字母表示其忘了）：

- `qZH`、`qzH`：这两类限制了记录串拥有某个前缀，称作 `a*` 的前缀类。
- `QZh`、`Qzh`：这两类限制拥有某个后缀，称作 `*b` 的后缀类。
- `qZh`：这类限制同时拥有某个前缀和某个后缀，称作 `a*b` 的前后缀类。
- `QzH`：这类限制拥有某个中缀，称作 `*m*` 的中缀类。
- `QZH` 完全没有限制，可匹配任何记录串。
- `qzh` 是前中后均确定的复制串，在这种场合不需考虑。

于是我们只需考虑 `a*,*b,a*b,*m*` 四类即可。

然后发现，对于前后缀的限制，我们只需确定记录串中最长的前缀 `A` 和最长的后缀 `B`，然后所有 `a*`（其中 `a` 是 `A` 的前缀）、`*b`（其中 `b` 是 `B` 的后缀）、`a*b`（其中 `a` 是 `A` 前缀、`b` 是 `B` 后缀）都能产生贡献。同时，我们可以将所有 `*m*` 塞在 `AB` 之间。此时所有的 `*m*` 都可以产生贡献。

于是我们只需找到最优的 `A,B` 即可。

对于 `a*,*b,a*b` 三类，建立前缀 trie 树和后缀 trie 树，一对 `AB` 对应了前缀树上的一条路径和后缀树上的一条路径，`a*` 是前缀树上一个点、`*b` 是后缀树上一个点、`a*b` 是前缀、后缀上一对点。`AB` 对应路径上所有点都能产生贡献。

考虑对于前缀树上每个点，维护以其作为 `A` 时，后缀树上每个点作为 `B` 时的答案。这可以通过在前缀树上扫描，并维护一棵以后缀树上点为下标的线段树进行。

`a*` 意味着在前缀树上一棵子树内的答案全体增加一，`*b` 意味着后缀树上一棵子树的答案全体加一：这两个是容易的。`a*b` 相当于在前缀树上扫描到某个点时，在它的子树中的流程有后缀树上一棵子树的答案全体加一。其可以被拆成在进入子树时增加、在离开子树时减少，而增加、减少就可以用上述的线段树维护。

------

然后就要考虑匹配了前中后均确定的串的场合。我们可以枚举这个串（记作 `s`），仍然考虑分类讨论每类串的贡献：

- `a*`：如果 `a` 是 `s` 前缀则产生贡献。
- `*b`：如果 `b` 是 `s` 后缀则产生贡献。
- `a*b`：`a` 是前缀、`b` 是后缀产生贡献。需要注意的是，`a,b` 不能重叠。
- `*m*`：`m` 是子串。
- `QZH` 仍然直接算答案。
- `qzh` 要用哈希或 trie 算出 `s` 出现几次。

于是我们仍然只需考虑前四类。

前两类直接在前缀 trie、后缀 trie 上统计即可。第三类介绍两种方法：

- 法一：直接使用前述的线段树，但是这样 `a,b` 出现重叠的场合也会被计算。因此，还要扣除这种情况：但这是简单的，我们可以枚举 `a*b`，然后找到出现重叠的场合（此时有 `a` 的一个后缀等于 `b` 的一个前缀，也即其是 `b#a`（其中 `#` 是占位符）这个串的 `border`，可以使用 KMP 或哈希找到），然后用哈希表示出此时的串的哈希值扔到桶里，然后对于 `s` 寻找这个桶里的计数即可。这是出题人的做法。
- 法二：对于 `s`，枚举 `s` 的一个前缀作为 `a`（其为前缀 trie 上一个节点），然后考虑其对应的 `b`（为后缀树上一条路径）。在前缀树上的这个节点处，挂了很多 `a*b` 的对，所以应该把此处挂着的 `a*b` 扔到线段树上作子树加，然后后缀树上单点求和即可。这个做法需要把询问离线，在前缀树上每个节点处统计所有与它有关的答案。这是验题人 Alex_Wei 的做法。

最后，第四类涉及到这样一个问题：

- 给定若干模板串。给定若干询问，每次给定询问串，询问有多少个模板串在询问串中至少出现一次。

存在一种 chenxia25 提供的、比较复杂的后缀数组解法，但是这里我们使用一种比较简洁的 AC 自动姬解法：

- 将模板串建 ACAM，然后询问串在上面跑，其跑的流程中访问了若干节点。这些节点在 fail 树上形成的虚树内部节点，统计其中包含多少个模板串即可。
- 这可以通过按照 dfn 序排序后，求出相邻节点 LCA 来统计答案。

令 $S=\sum s_i$，则复杂度 $S|\Sigma|+S\log S$，其中 $|\Sigma|$ 是字符集大小。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,res;
char ss[500100];
int S[500100][3],s0,p[500100][3];
bool fgt[500100][3];
struct Trie{
int ch[500100][26],cnt;
Trie(){cnt=1;memset(ch,0,sizeof(ch));}
int insert(int l,int r){
	// printf("insert:(%d)%d,%d\n",&cnt,l,r);
	int x=1;
	if(l<r){
		for(int i=l;i<r;i++){
			if(!ch[x][ss[i]-'a'])ch[x][ss[i]-'a']=++cnt;
			x=ch[x][ss[i]-'a'];
		}
	}else{
		for(int i=l-1;i>=r;i--){
			if(!ch[x][ss[i]-'a'])ch[x][ss[i]-'a']=++cnt;
			x=ch[x][ss[i]-'a'];
		}
		// for(int i=l-1;i>=r;i--)putchar(ss[i]);puts("");
	}
	return x;
}
}pt,st;
int amt[500100];
int pre[500100],suf[500100];
vector<int>v[500100],u[500100];
int dfn[500100],sz[500100],rev[500100],tot;
void dfs_dfn(int x){
	dfn[x]=++tot,rev[tot]=x,sz[x]=1;
	for(int i=0,y;i<26;i++)if(y=st.ch[x][i])dfs_dfn(y),sz[x]+=sz[y];
}
int num[500100],mun[500100];
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
struct SegTree{
	int tag,mx;
}seg[2001000];
void ADD(int x,int y){seg[x].tag+=y,seg[x].mx+=y;}
void pushup(int x){seg[x].mx=max(seg[lson].mx,seg[rson].mx)+seg[x].tag;}
void build(int x,int l,int r){
	if(l==r)seg[x].mx=mun[rev[l]];
	else build(lson,l,mid),build(rson,mid+1,r),pushup(x);
}
void rangeadd(int x,int l,int r,int L,int R,int V){
	if(l>R||r<L)return;
	if(L<=l&&r<=R)return ADD(x,V);
	rangeadd(lson,l,mid,L,R,V),rangeadd(rson,mid+1,r,L,R,V),pushup(x);
}
int query(int x,int l,int r,int L,int R){
	if(l>R||r<L)return 0xc0c0c0c0;
	if(L<=l&&r<=R)return seg[x].mx;
	return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R))+seg[x].tag;
}
int dfs_solve(int x){
	for(auto y:v[x])rangeadd(1,1,st.cnt,dfn[y],dfn[y]+sz[y]-1,1);
	for(auto y:u[x])amt[y]=query(1,1,st.cnt,dfn[suf[y]],dfn[suf[y]]+sz[suf[y]]-1)+num[x];
	int ret=seg[1].mx+num[x];
	// printf("%d:%d,%d\n",x,seg[1].mx,num[x]);
	for(int i=0,y;i<26;i++)if(y=pt.ch[x][i])ret=max(ret,dfs_solve(y));
	for(auto y:v[x])rangeadd(1,1,st.cnt,dfn[y],dfn[y]+sz[y]-1,-1);
	return ret;
}
int cnt=1;
struct ACAM{
	int ch[26],fail,num;
}t[500100];
void insert(int l,int r){
	int x=1;
	for(int i=l;i<r;i++){
		if(!t[x].ch[ss[i]-'a'])t[x].ch[ss[i]-'a']=++cnt;
		x=t[x].ch[ss[i]-'a'];
	}
	t[x].num++;
}
void build(){
	static int q[500100],l,r;
	for(int i=0;i<26;i++)
		(t[1].ch[i]?t[q[r++]=t[1].ch[i]].fail:t[1].ch[i])=1;
	while(l!=r){
		int x=q[l++];
		for(int i=0;i<26;i++)
			(t[x].ch[i]?t[q[r++]=t[x].ch[i]].fail:t[x].ch[i])=t[t[x].fail].ch[i];
	}
}
vector<int>w[500100];
int dep[500100],anc[500100][20];
int LCA(int x,int y){
	if(dep[x]>dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[x]<=dep[y]-(1<<i))y=anc[y][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(anc[x][i]!=anc[y][i])x=anc[x][i],y=anc[y][i];
	return t[x].fail;
}
void dfs_count(int x){
	dfn[x]=++tot;
	anc[x][0]=t[x].fail;for(int i=1;i<20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(auto y:w[x])t[y].num+=t[x].num,dep[y]=dep[x]+1,dfs_count(y);
}
const int mod1=1e9+9,mod2=1004535809;
const int bs1=131,bs2=137;
int p1[500100],p2[500100];
struct Hash{
	int x,y,len;
	Hash(int X,int Y,int Z){x=X,y=Y,len=Z;}
	Hash(){x=y=len=0;}
	Hash(char c){x=y=c,len=1;}
	friend Hash operator+(const Hash&u,const Hash&v){
		return Hash((1ll*u.x*p1[v.len]+v.x)%mod1,(1ll*u.y*p2[v.len]+v.y)%mod2,u.len+v.len);
	}
	friend bool operator<(const Hash&u,const Hash&v){
		if(u.len!=v.len)return u.len<v.len;
		if(u.x!=v.x)return u.x<v.x;
		if(u.y!=v.y)return u.y<v.y;
		return false;
	}
	friend bool operator==(const Hash&u,const Hash&v){
		if(u.len!=v.len)return false;
		if(u.x!=v.x)return false;
		if(u.y!=v.y)return false;
		return true;
	}
	void print()const{printf("(%d,%d)",x,y);}
};
map<Hash,int>mp;
int main(){
	// freopen("oblivion.in","r",stdin);
	// freopen("oblivion.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)for(int j=0;j<3;j++){
		scanf("%s",ss+(p[i][j]=s0));
		if(ss[s0]=='E')S[i][j]=0;
		else{
			if(j==0&&ss[s0]=='Q')fgt[i][j]=true;
			if(j==1&&ss[s0]=='Z')fgt[i][j]=true;
			if(j==2&&ss[s0]=='H')fgt[i][j]=true;
			s0+=(S[i][j]=strlen(ss+s0));
		}
	}
	p[n+1][0]=s0;
	p1[0]=p2[0]=1;
	for(int i=1;i<=s0;i++)p1[i]=1ll*p1[i-1]*bs1%mod1,p2[i]=1ll*p2[i-1]*bs2%mod2;
	memset(pre,-1,sizeof(pre));
	memset(suf,-1,sizeof(suf));
	for(int i=1;i<=n;i++)if(!fgt[i][0]){
		int pos;
		if(fgt[i][1])pos=p[i][1];
		else if(fgt[i][2])pos=p[i][2];
		else pos=p[i+1][0];
		pre[i]=pt.insert(p[i][0],pos);
	}
	for(int i=1;i<=n;i++)if(!fgt[i][2]){
		int pos;
		if(fgt[i][1])pos=p[i][2];
		else if(fgt[i][0])pos=p[i][1];
		else pos=p[i][0];
		suf[i]=st.insert(p[i+1][0],pos);
	}
	int all=0;
	for(int i=1;i<=n;i++)if(fgt[i][0]&&fgt[i][2])all++;
	for(int i=1;i<=n;i++){
		if(pre[i]!=-1&&suf[i]==-1)num[pre[i]]++;
		if(pre[i]==-1&&suf[i]!=-1)mun[suf[i]]++;
		if(pre[i]!=-1&&suf[i]!=-1){
			if(fgt[i][1])v[pre[i]].push_back(suf[i]);
			else u[pre[i]].push_back(i);
		}
	}
	for(int i=1;i<=pt.cnt;i++)for(int j=0;j<26;j++)if(pt.ch[i][j])num[pt.ch[i][j]]+=num[i];
	for(int i=1;i<=st.cnt;i++)for(int j=0;j<26;j++)if(st.ch[i][j])mun[st.ch[i][j]]+=mun[i];
	dfs_dfn(1);
	build(1,1,st.cnt);
	res=max(res,dfs_solve(1)+all);
	all=0;
	for(int i=1;i<=n;i++)if(fgt[i][0]&&fgt[i][2]){
		if(fgt[i][1])all++;
		else insert(p[i][1],p[i][2]);
	}
	for(int i=1;i<=n;i++)if(!fgt[i][0]&&fgt[i][1]&&!fgt[i][2]){
		static Hash h1[500100],h2[500100];
		h1[p[i][0]]=h2[p[i+1][0]]=Hash();
		for(int j=p[i][0];j<p[i][1];j++)h1[j+1]=h1[j]+ss[j];
		for(int j=p[i+1][0]-1;j>=p[i][2];j--)h2[j]=ss[j]+h2[j+1];
		Hash H1,H2;
		for(int len=1;len<=S[i][0]&&len<=S[i][2];len++){
			H1=ss[p[i][1]-len]+H1;
			H2=H2+ss[p[i][2]+len-1];
			if(H1==H2)
				// (h1[p[i][1]]+h2[p[i][2]+len]).print(),puts("");
				mp[h1[p[i][1]]+h2[p[i][2]+len]]++;
		}
	}
	build();
	for(int i=2;i<=cnt;i++)w[t[i].fail].push_back(i);
	tot=0;dfs_count(1);
	for(int i=1;i<=n;i++)if(!fgt[i][0]&&!fgt[i][1]&&!fgt[i][2]){
		vector<int>vec={1};
		int x=1;
		for(int j=p[i][0];j<p[i+1][0];j++)
			x=t[x].ch[ss[j]-'a'],
			vec.push_back(x);
		sort(vec.begin(),vec.end(),[](const int&x,const int&y){return dfn[x]<dfn[y];});
		amt[i]+=t[1].num;
		for(int j=1;j<vec.size();j++)amt[i]+=t[vec[j]].num-t[LCA(vec[j-1],vec[j])].num;
		Hash hs;
		for(int j=p[i][0];j<p[i+1][0];j++)hs=hs+ss[j];
		mp[hs]--;
		amt[i]-=mp[hs];
		res=max(res,amt[i]+all);
	}
	printf("%d\n",res);
	return 0;
}
```



---

