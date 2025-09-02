# Alphabet Permutations

## 题目描述

You are given a string $ s $ of length $ n $ , consisting of first $ k $ lowercase English letters.

We define a  $ c $ -repeat of some string $ q $ as a string, consisting of $ c $ copies of the string $ q $ . For example, string "acbacbacbacb" is a $ 4 $ -repeat of the string "acb".

Let's say that string $ a $ contains string $ b $ as a subsequence, if string $ b $ can be obtained from $ a $ by erasing some symbols.

Let $ p $ be a string that represents some permutation of the first $ k $ lowercase English letters. We define function $ d(p) $ as the smallest integer such that a $ d(p) $ -repeat of the string $ p $ contains string $ s $ as a subsequence.

There are $ m $ operations of one of two types that can be applied to string $ s $ :

1. Replace all characters at positions from $ l_{i} $ to $ r_{i} $ by a character $ c_{i} $ .
2. For the given $ p $ , that is a permutation of first $ k $ lowercase English letters, find the value of function $ d(p) $ .

All operations are performed sequentially, in the order they appear in the input. Your task is to determine the values of function $ d(p) $ for all operations of the second type.

## 说明/提示

After the first operation the string $ s $ will be abbbbba.

In the second operation the answer is $ 6 $ -repeat of abc: ABcaBcaBcaBcaBcAbc.

After the third operation the string $ s $ will be abbcbba.

In the fourth operation the answer is $ 5 $ -repeat of cba: cbAcBacBaCBacBA.

Uppercase letters means the occurrences of symbols from the string $ s $ .

## 样例 #1

### 输入

```
7 4 3
abacaba
1 3 5 b
2 abc
1 4 4 c
2 cba
```

### 输出

```
6
5
```

# 题解

## 作者：FZzzz (赞：3)

单次询问：我们考虑一个贪心：如果两个挨在一起的字符，他们的顺序与在模板串里的顺序是相同的，那么我们必然把它放在同一个循环节里，否则就会使答案增加一。这个做法的正确性显然。

无修改：每次遍历一遍文本串非常吃亏，所以我们对每一对字符计算贡献。预处理出每两个字符在文本串中一前一后出现的次数，则我们可以平方枚举模板串中的字符对并计算贡献。

原题：我们用线段树维护上一个做法中所提到的数组。

时间复杂度 $O(k^2n+k^2m\log n)$，注意本题中 $n$ 与 $m$ 并不同阶。
```cpp
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5,maxk=10+5;
int n,m,k;
char s[maxn],t[maxk];
struct node{
	int l,r;
	node* ch[2];
	int lv,rv,cnt[maxk][maxk],setv;
	void pushup(){
		lv=ch[0]->lv;
		rv=ch[1]->rv;
		for(int i=0;i<k;i++) for(int j=0;j<k;j++)
			cnt[i][j]=ch[0]->cnt[i][j]+ch[1]->cnt[i][j];
		cnt[ch[0]->rv][ch[1]->lv]++;
	}
	node(int l,int r):l(l),r(r),setv(-1){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
			pushup();
		}
		else{
			lv=rv=s[r]-'a';
			memset(cnt,0,sizeof(cnt));
		}
	}
	void pushtag(int k){
		setv=k;
		lv=rv=k;
		memset(cnt,0,sizeof(cnt));
		cnt[k][k]=r-l;
	}
	void pushdown(){
		if(setv>=0){
			ch[0]->pushtag(setv);
			ch[1]->pushtag(setv);
			setv=-1;
		}
	}
	void modify(int ql,int qr,int k){
		if(ql<=l&&qr>=r) pushtag(k);
		else{
			pushdown();
			if(ql<=ch[0]->r) ch[0]->modify(ql,qr,k);
			if(qr>=ch[1]->l) ch[1]->modify(ql,qr,k);
			pushup();
		}
	}
}*rt;
inline char readchar(){
	char c=getchar();
	while(isspace(c)) c=getchar();
	return c;
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	k=readint();
	scanf("%s",s+1);
	rt=new node(1,n);
	while(m--){
		int opt=readint();
		if(opt==1){
			int l,r;
			l=readint();
			r=readint();
			rt->modify(l,r,readchar()-'a');
		}
		else{
			scanf("%s",t);
			int ans=1;
			for(int i=0;i<k;i++) for(int j=0;j<=i;j++)
				ans+=rt->cnt[t[i]-'a'][t[j]-'a'];
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：1)

solution of CF610E Alphabet Permutations

## 解题思路

先只考虑操作 2，发现往 $s$ 中插入字符使得符合条件并不好维护，考虑转化。

因为给出的 $t$ 是**排列**，不难发现在每一个循环节中每种字符**只会存在一次而且必须存在**。考虑对这一性质进行转化。

考虑 $s$ 的相邻两个字符 $s_i$ 和 $s_{i+1}$，什么情况下这两个字符会安排在同一个循环节内，不给答案产生贡献：发现 $s_i$ 在 $t$ 中的位置在 $s_{i+1}$ 之前。这是一个充要条件。

考虑对这个东西进行维护。因为有区间推平操作，很容易想到对 $s$ 建立线段树维护。具体地，对于线段树上的每个区间 $[l,r]$，维护矩阵 $w(p,q)$，表示 $s[l,r]$ 中每一对相邻的字符，类型为 $s_i=p,s_{i+1}=q$ 有多少个，这个矩阵是 $O(k^2)$ 的。合并操作也是容易的，记录每个区间左右位置的字符，合并时再加上跨过左右儿子的那一对就好，合并操作也是 $O(k^2)$ 的。

分析时间复杂度，发现 $n,k$ 并不同阶，预处理（建树）的复杂度为 $O(nk^2)$，操作的复杂度为 $O(qk^2\log n)$，总复杂度为 $O(k^2(q\log n+n))$。

## 参考代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 200005
#define mid ((tree[p].l+tree[p].r)>>1)
#define ls (p<<1)
#define rs (p<<1|1)
struct node{
    int l,r,f[12][12];
    int pre,suf;
    char tag;
    int &operator()(int x,int y){return f[x][y];}
}tree[MAXN<<2];
int n,m,k;
char s[MAXN];
void update(int p){
    for(int i=1;i<=k;i++) for(int j=1;j<=k;j++){
        tree[p](i,j)=tree[ls](i,j)+tree[rs](i,j);
    }
    tree[p](tree[ls].suf,tree[rs].pre)++;
    tree[p].pre=tree[ls].pre;
    tree[p].suf=tree[rs].suf;
}
void build(int l,int r,int p){
    tree[p].l=l,tree[p].r=r;
    if(l==r){
        tree[p].pre=tree[p].suf=s[l]-'a'+1;
        return;
    }
    build(l,mid,ls);
    build(mid+1,r,rs);
    update(p);
}
void pushdown(int p){
    if(tree[p].tag){
        int t=tree[p].tag;
        tree[ls].pre=tree[ls].suf=t;
        tree[rs].pre=tree[rs].suf=t;
        memset(tree[ls].f,0,sizeof(tree[ls].f));
        memset(tree[rs].f,0,sizeof(tree[rs].f));
        tree[ls](t,t)=tree[ls].r-tree[ls].l;
        tree[rs](t,t)=tree[rs].r-tree[rs].l;
        tree[ls].tag=tree[rs].tag=t;
        tree[p].tag=0;
    }
}
void modify(int l,int r,int t,int p){
    if(l<=tree[p].l&&r>=tree[p].r){
        tree[p].pre=tree[p].suf=t;
        memset(tree[p].f,0,sizeof(tree[p].f));
        tree[p](t,t)=tree[p].r-tree[p].l;
        tree[p].tag=t;
        return;
    }
    pushdown(p);
    if(l<=mid) modify(l,r,t,ls);
    if(r>mid) modify(l,r,t,rs);
    update(p);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>k>>(s+1);
    build(1,n,1);
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int l,r;char ch;
            cin>>l>>r>>ch;
            modify(l,r,ch-'a'+1,1);
        }
        else{
            string tmp;
            cin>>tmp;
            int ans=n;
            for(int i=0;i<k-1;i++){
                for(int j=i+1;j<k;j++){
                    ans-=tree[1](tmp[i]-'a'+1,tmp[j]-'a'+1);
                }
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：shinkuu (赞：1)

简单题。想到怎么计数就结束了。

重点就是怎么样计算循环次数。肯定是不能枚举一遍，双指针去数的。

但是发现 $t$ 有一个很好的性质：**它是 $[1,k]$ 内字符的排列**。说明每个字符在 $t$ 中只会出现一次。然后发现，可以按照最长公共子序列那题类似的思路，根据 $t$ 内字符的位置为权值，求上升子段个数，这和循环次数是等价的。

而这个东西就很好求了，可以记录 $\forall x,y,s_i=x,s_y=i$ 的个数，然后每次枚举 $x,y$，看权值大小关系算。

还要求区间推平，这种上颜色段均摊显然是很合适的。复杂度大概是 $O(m\log n+k^2m)$ 的，好像优于其他题解（可能有误，请指出）？目前只略逊于一个 zkw 线段树。优势是思路清晰，不容易写挂。

code：

```cpp
int n,m,k,c[13][13];
char s[N];
struct CHtree{
	struct node{
		int l,r,k;
		node(int _l=0,int _r=0,int _k=0):l(_l),r(_r),k(_k){}
		bool operator<(const node &rhs)const{return l<rhs.l;}
	};
	set<node> st;
	void init(){
		rep(i,1,n)st.insert(node(i,i,s[i]-'a'));
	}
	il auto split(int pos){
		if(pos==n+1)return st.end();
		auto it=st.lower_bound(node(pos,0,0));
		if(it!=st.end()&&it->l==pos)return it;
		node tmp=*--it;
		st.erase(it);
		st.insert(node(tmp.l,pos-1,tmp.k));
		return st.insert(node(pos,tmp.r,tmp.k)).fi;
	}
	il void assign(int l,int r,int k){
		auto itr=split(r+1),itl=split(l);
		for(auto it=itl;it!=itr;it++){
			c[it->k][it->k]-=(it->r)-(it->l);
			if(it!=st.begin())c[prev(it)->k][it->k]--;
		}
		if(itr!=st.end())c[prev(itr)->k][itr->k]--;
		st.erase(itl,itr);
		auto it=st.insert(node(l,r,k)).fi;
		c[k][k]+=r-l;
		if(it!=st.begin())c[prev(it)->k][k]++;
		if(it!=--st.end())c[k][next(it)->k]++;
	}
}C;
void Yorushika(){
	scanf("%d%d%d%s",&n,&m,&k,s+1);
	C.init();
	rep(i,2,n)c[s[i-1]-'a'][s[i]-'a']++;
	while(m--){
		int op=read(),x,y;char t[13];
		if(op==1){
			scanf("%d%d%s",&x,&y,t);
			C.assign(x,y,t[0]-'a');
		}else{
			scanf("%s",t);
			int ans=0;
			rep(i,0,k-1)rep(j,0,i)ans+=c[t[i]-'a'][t[j]-'a'];
			printf("%d\n",ans+1);
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：泠小毒 (赞：1)

# Alphabet Permutations
给定一个长度为n（n<200000）的字符串s,有两种指令：

1.将区间[L,R]内的字符变为ch

2.给定长度为k（1<=k<=10）的字符串排列t，向s串中添加字符，使得s以t为模式循环，求最少的循环次数

最多20000条指令
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190515/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190515.html)
## 解法
建一棵线段树，在每个节点里放一个k^2的数组，记录两个ch直接相连的情况，操作1就是区间修改

至于询问，记录一下每个字母在模式串中的出现位置，即rk，当rk[i]>rk[j]时ans+=[1][i][j]

即当一个字母在另一个字母的后面时，与它相连的另一个字母一定会跳转到下一个模式串，即1的贡献
## ac代码
```cpp
#include<bits/stdc++.h>
#define mem(a) memset(a,0,sizeof(a))
#define mid ((l+r)>>1)
using namespace std;
char ch;
int n,m,k,c,l,r,ans,rk[10],a[800010][10][10],tg[800010],lc[800010],rc[800010];
void f(int x,int c,int len){mem(a[x]),a[x][c][c]=len-1,lc[x]=rc[x]=tg[x]=c;}
void down(int x,int l,int r){if(tg[x]>-1)f(x<<1,tg[x],mid-l+1),f(x<<1|1,tg[x],r-mid);}
void upd(int x)
{
	int l=x<<1,r=x<<1|1;
	for(int i=0;i<k;i++)for(int j=0;j<k;j++)a[x][i][j]=a[l][i][j]+a[r][i][j];
	a[x][rc[l]][lc[r]]++,lc[x]=lc[l],rc[x]=rc[r];
}
void build(int x,int l,int r)
{
	if(l==r){scanf(" %c",&ch),lc[x]=rc[x]=ch-'a';return;}
	build(x<<1,l,mid),build(x<<1|1,mid+1,r),upd(x);
}
void modify(int x,int l,int r,int p,int q,int d)
{
	if(l>=p&&r<=q){f(x,d,r-l+1);return;}else if(l>q||r<p)return;
	down(x,l,r),tg[x]=-1,modify(x<<1,l,mid,p,q,d),modify(x<<1|1,mid+1,r,p,q,d),upd(x);
}
int main()
{
	memset(tg,-1,sizeof(tg)),scanf("%d%d%d",&n,&m,&k),build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&c),ans=0;
		if(c==1)scanf("%d%d %c",&l,&r,&ch),modify(1,1,n,l,r,ch-'a');
		else
		{
			for(int i=0;i<k;i++)scanf(" %c",&ch),rk[ch-'a']=i;
			for(int i=0;i<k;i++)for(int j=0;j<k;j++)if(rk[i]>=rk[j])ans+=a[1][i][j];
			printf("%d\n",ans+1);
		}
	}
	return 0;
}
```

---

## 作者：tommymio (赞：0)

注意到模式串循环一次只会给每个字母至多 $1$ 的贡献。并且如果主串中两个字母连续出现，在模式串对应两个字母也是连续出现，那可以用 $1$ 个循环模式串匹配掉这两个字母。因为如果不这么做，循环次数 $+1$，会使解更劣。

于是想到维护主串中相邻两个字母的出现次数。根据之前的结论，如果在主串中相邻两个字母在模式串中一后一前出现，就会使得循环次数 $+1$。使用线段树维护并统计答案即可。时间复杂度为 $O(nk^2+mk^2\log n)$。

```cpp
/* stuff you should look for
	Something interesting tip copied from _kubic
	* int overflow, array bounds, uppercase/lowercase
	* special cases (n=1?)
	* do sth. instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH  
*/
#include<cstdio>
class SegmentTree {
	#define ls p<<1
	#define rs p<<1|1
	int n,K,buc[800005][10][10],chl[800005],chr[800005],tag[800005];
public:
	inline void pushup(int p) {
		for(register int i=0;i<K;++i) for(register int j=0;j<K;++j) buc[p][i][j]=buc[ls][i][j]+buc[rs][i][j];
		++buc[p][chr[ls]][chl[rs]]; chl[p]=chl[ls]; chr[p]=chr[rs]; 
	}
	inline void build(int p,int l,int r,char *s) {
		tag[p]=-1;
		if(l==r) {
			for(register int i=0;i<K;++i) for(register int j=0;j<K;++j) buc[p][i][j]=0; 
			chl[p]=chr[p]=s[l]-'a'; return;
		}
		int mid=l+r>>1; build(ls,l,mid,s); build(rs,mid+1,r,s); pushup(p);
	} 
	inline void init(int n,int k,char *s) {this->n=n; this->K=k; build(1,1,n,s);}
	inline void work(int p,int l,int r,const int& val) {
		tag[p]=val;
		for(register int i=0;i<K;++i) for(register int j=0;j<K;++j) buc[p][i][j]=0; 
		buc[p][val][val]=r-l; chl[p]=val; chr[p]=val; return;
	}
	inline void spread(int p,int l,int r) {
		int mid=l+r>>1;
		if(tag[p]!=-1) {work(ls,l,mid,tag[p]); work(rs,mid+1,r,tag[p]); tag[p]=-1;}
	} 
	inline void _modify(int p,int L,int R,int l,int r,const int& val) {
		if(L<=l&&r<=R) {work(p,l,r,val);return;}
		int mid=l+r>>1; spread(p,l,r);
		if(L<=mid) _modify(ls,L,R,l,mid,val);
		if(R>mid) _modify(rs,L,R,mid+1,r,val);
		pushup(p);
	}
	inline void modify(int L,int R,const char& val) {_modify(1,L,R,1,n,val-'a');}
	inline int getPair(int x,int y) {return buc[1][x][y];}
}SGT;
char s[200005],tmp[15];
int rev[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	int n=read(),Q=read(),K=read();
	scanf("%s",s+1); SGT.init(n,K,s);
	while(Q--) {
		int op=read();	
		if(op==1) {
			int l=read(),r=read();
			scanf("%s",tmp);
			SGT.modify(l,r,tmp[0]);
		}
		else {
			scanf("%s",tmp);
			int ans=1;
			for(register int i=0;i<K;++i) rev[tmp[i]-'a']=i;
			for(register int i=0;i<K;++i) {
				for(register int j=0;j<K;++j) {
					if(rev[i]>=rev[j]) ans+=SGT.getPair(i,j);
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：xzCyanBrad (赞：0)

这是一个分块题解，时间洛谷前十（不劣于线段树解法），空间是线段树解法的千分之一。好像薄纱除了 ODT 以外所有的解法。（振臂高呼：卡掉 ODT！空间开到 1M！）

## 1. 如何计数？

考虑如果给定的排列就是 $\texttt{a}\sim\texttt{j}$，那么如何单组 $\Theta(n)$ 计算答案？

方法很简单：扫一遍 $s$ 串，当 $s_i\ge s_{i+1}(0\le i<\text{len}(s)-1)$ 时使答案累加，最后输出答案加一即可。

为什么能这样？我们可以把字母看成一个折线图。最后应该是每组 $10$ 个字母一轮一轮这么过，组内一直上升，直到从 $\texttt{j}$ 变成下一组的 $\texttt{a}$ 时才下降回来。当 $s_i\ge s_{i+1}$ 时，说明在这里折线图没有上升，说明他们不能被分在一组内（一组内必须单调上升）。因此这是一个断点。

故我们数出断点的个数就是上面的“答案”。显然断点加一就是段数（比如一根木棒切 $x$ 刀变成 $(x+1)$ 根木棒）。

## 2. 如何维护？

我们已经有了个 $\Theta(nm)$ 的解法。不难发现我们可以维护所有的 $v_{p,q}$，表示 $s_i=p\land s_{i+1}=q$ 的 $i$ 的个数。这样我们可以做到任意排列了：枚举所有 $(p,q)$，如果 $p$ 不在 $q$ 前面，那么答案就加上 $v_{p,q}$。不难发现它的特殊情况就是上面【1】中的算法的优化。

上面的算法是个静态算法，复杂度 $\Theta(mk^2)$。

考虑如何支持区间修改。我们可以维护 $v_{p,q}$ 的一个单点值 $v'_{i,p,q}$ 表示 $s_{i,i+1}$ 的 $v_{p,q}$，不难发现 $\forall i,\sum_{(p,q)}v_{i,p,q}=1$。修改的时候，直接修改 $v'_{i,p,q}$（区间推平成 $0$ 或 $1$），最后就是  $v_{p,q}=\sum_{0\le i<\text{len}(s)-1}v'_{i,p,q}$。

发现 500M 的内存卡的好紧（线段树的空间复杂度为 $\Theta(nk^2)$，还有至少四倍常数），所以不敢冒险写线段树，可能会被卡。

考虑分块。定义 $V_{b,p,q}=\sum_{i\in \text{block}(b)}v'_{i,p,q}$。发现这样子我们区间推平就是小块暴力，然后大块直接把它的 $V$ 全部变成 $0$，除了 $V_{b,p,q}$ 变成 $B=|\text{block}(b)|$。

时间复杂度为 $\Theta(mB+\frac{mnk^2}B)$（注意到散块的暴力只用一加一减）。可以令 $B=k\sqrt n$，这样复杂度为 $\Theta(mk\sqrt n)$，实测 $B=1500$ 最快。这个复杂度只比线段树解法慢四五倍。而且因为常数小，其实跑得还更快。

空间复杂度为 $\Theta(n+\frac {nk^2}B)=\Theta(n+k\sqrt n)$，几乎就是线性。交上去的空间是以 KB 为单位计算的。

## 3. 如何实现？

说着简单，实现真的非常困难！

首先，我们应该明确块与块之间的关系。比如 $i,i+1$ 跨两个块时，我们答案算给谁？我的方式是算给左边的块。然后就是我们更新的时间顺序，应该是先下传推平标记，再删除散块无用答案，再处理整块，再加入散块的新答案。（大家可以想想为啥要这样）

还有一个事情是也需要更新 $l-1$ 的答案，因为 $l-1,l$ 也被修改了。

代码：

```cpp
constexpr int B=1500;

int n,q,k,cnt[14][14],val[140][14][14],id[14];
char s[200010],tag[20010];

inline int bel(int x){return (x-1)/B+1;}
inline int L(int x){return (x-1)*B+1;}
inline int R(int x){return x*B;}

void totL(int i,char c){
  if (i!=1){
    --val[bel(i-1)][s[i-1]^96][s[i]^96];
    --cnt[s[i-1]^96][s[i]^96];
    ++val[bel(i-1)][s[i-1]^96][c^96];
    ++cnt[s[i-1]^96][c^96];
  }
}

void chgf(int i){
  if (i!=n){
    --val[bel(i)][s[i]^96][s[i+1]^96];
    --cnt[s[i]^96][s[i+1]^96];
  }
}

void chg(int i){
  // cout<<s[i]<<' '<<c<<' '<<cnt[1][2]<<'\n';
  if (i!=n){
    ++val[bel(i)][s[i]^96][s[i+1]^96];
    ++cnt[s[i]^96][s[i+1]^96];
  }
}

void down(int id){
  rep(i,L(id),R(id))s[i]=tag[id];
  tag[id]=0;
}

void chk(int id){
  if (id>0&&id<=bel(n)-1&&tag[id])down(id);
}

void chkx(int p){
  chk(bel(p-1));
  chk(bel(p));
  chk(bel(p+1));
}

void bfdel(int l,int r){
  // cout<<l<<' '<<r<<' '<<c<<'\n';
  chkx(l),chkx(r);
  // cout<<cnt[1][1]<<'\n';
  rep(i,l,r)chgf(i);
}
void bfadd(int l,int r){
  // cout<<l<<' '<<r<<' '<<c<<'\n';
  chkx(l),chkx(r);
  // cout<<cnt[1][1]<<'\n';
  rep(i,l,r)chg(i);
}

void add(int l,int r,char c){
  // cout<<cnt[2][2]<<'\n';
  if (bel(l)+1>=bel(r)){
    chkx(l);
    totL(l,c);
    bfdel(l,r);
    rep(i,l,r)s[i]=c;
    bfadd(l,r);
    return ;
  }
  // cout<<cnt[1][1]<<'\n';
  chkx(l);
  totL(l,c);
  bfdel(l,R(bel(l)));
  bfdel(L(bel(r)),r);
  rep(i,bel(l)+1,bel(r)-1){
    tag[i]=c;
    rep(c1,1,10)rep(c2,1,10){
      cnt[c1][c2]-=val[i][c1][c2];
      val[i][c1][c2]=0;
    }
    val[i][c^96][c^96]=R(i)-L(i)+1;
    cnt[c^96][c^96]+=val[i][c^96][c^96];
    // cout<<val[i][2][2]<<'\n';
    // cout<<val[i][2][2]<<'\n';
    // cout<<i<<' '<<cnt[c^96][c^96]<<'\n';
  }
  // cout<<cnt[1][1]<<'\n';
  rep(i,l,R(bel(l)))s[i]=c;
  rep(i,L(bel(r)),r)s[i]=c;
  bfadd(l,R(bel(l)));
  bfadd(L(bel(r)),r);
}

int main() {
  scanf("%d%d%d%s",&n,&q,&k,s+1);
  rep(i,1,n-1)++cnt[s[i]^96][s[i+1]^96];
  // cout<<cnt[1][2]<<'\n';
  rep(i,1,n-1)++val[bel(i)][s[i]^96][s[i+1]^96];
  while (q--){
    int o;
    scanf("%d",&o);
    if (o==1){
      int l,r;
      char u[2],c;
      scanf("%d%d%s",&l,&r,u);
      c=u[0];
      add(l,r,c);
    }else{
      char u[15];
      scanf("%s",u+1);
      int res=1;
      // rep(i,1,k)rep(j,1,k)
        // cout<<cnt[i][j]<<" \n"[j==k];
      rep(i,1,k)id[u[i]^96]=i;
      rep(i,1,k)rep(j,1,k)if (id[i]>=id[j])
        res+=cnt[i][j];
      printf("%d\n",res);
    }
  }
  return 0;
}
```

---

