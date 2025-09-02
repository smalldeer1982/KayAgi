# [USACO23OPEN] Pareidolia P

## 题目描述

Pareidolia 是一种现象，指的是人们倾向于在并不真正存在的地方看到熟悉的图案——例如在云中看到一张脸。可以想象，由于农夫 John 经常与奶牛接触，他常常在日常物品中看到与奶牛相关的图案。例如，如果他看到字符串 `bqessiyexbesszieb`，农夫 John 的眼睛会忽略其中的一些字母，而他看到的只是 `bessiebessie`。

给定一个字符串 $s$，令 $B(s)$ 表示通过删除 $s$ 中的零个或多个字符后，能够形成的 `bessie` 的最大重复次数。在上面的例子中，$B(bqessiyexbesszieb)=2$。此外，给定一个字符串 $t$，令 $A(t)$ 表示所有连续子串 $s$ 的 $B(s)$ 之和。

农夫 John 有一个长度不超过 $2 \times 10^5$ 的字符串 $t$，且仅由字符 a-z 组成。请计算 $A(t)$，以及在 $U (1 \le U \le 2 \times 10^5)$ 次更新后 $A(t)$ 的变化情况，每次更新会修改 $t$ 中的一个字符。更新是累积的。

## 说明/提示

在没有任何更新之前，有 12 个子串恰好包含 $1$ 个 `bessie`，有 $1$ 个子串恰好包含 $2$ 个 `bessie`，因此 `bessie` 的总数为 $12 \cdot 1 + 1 \cdot 2 = 14$。

第一次更新后，$t$ 变为 `belsiebessie`。有 7 个子串恰好包含一个 `bessie`。

第二次更新后，$t$ 变为 `belsiesessie`。只有整个字符串包含 `bessie`。

输入 $2$：$|t|, U \le 300$；

输入 $3-5$：$U \le 10$；

输入 $6-13$：$|t|, U \le 10^5$；

输入 $14-21$：没有额外限制。

## 样例 #1

### 输入

```
bessiebessie
3
3 l
7 s
3 s```

### 输出

```
14
7
1
7```

# 题解

## 作者：UltiMadow (赞：10)

首先考虑对于单独的一个数列应该怎么做。

记字符串 `bessie` 为 $T$，为了方便，$T$ 的下标从 $0$ 开始。

考虑一个 dp：记 $f_{i,j}$ 为考虑前 $i$ 个字符，下一个需要匹配的是 $T$ 的第 $j$ 位的后缀个数。

那么有转移：$f_{i-1,j}\to f_{i,(j+[s_i=T_j])\bmod 6}$，$1\to f_{i,[s_i=T_0]}$，$f_{i-1,5}[s_i=T_6]\to ans$。

考虑用 cdq 分治维护这个过程，记当前分治区间为 $[l,r]$，已经计算好了 $[l,mid],(mid,r]$ 的对答案的贡献，现在需要计算横跨 $mid$ 的所有子串对答案的贡献。

对于每个区间，记录 $nxt_i$ 表示进入这个区间时下一个需要匹配 $T_i$，离开这个区间时下一个需要匹配 $T_{nxt_i}$，$cnt_i$ 表示离开区间时下一个需要匹配 $T_i$ 的后缀个数，$co_i$ 表示进入区间时下一个需要匹配 $T_i$ 的字符串在当前区间中有多少个位置可以对答案产生贡献。

合并 $[l,mid],(mid,r]$ 两个区间时，对答案的贡献即为 $\sum cnt_{[l,mid],i}co_{(mid,r],i}$，$nxt,cnt,co$ 的合并都是容易的。

这个分治的过程显然可以用线段树维护，时间复杂度 $\mathcal O(|T|n\log n)$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200010
using namespace std;
const string base="bessie";
int n,Q;
char s[MAXN];
struct tnode{
	int nxt[6],cnt[6],co[6],sum;
	tnode(char c='#',int pos=0){
		memset(nxt,0,sizeof(nxt));memset(cnt,0,sizeof(cnt));
		memset(co,0,sizeof(co));sum=0;
		if(pos){
			for(int i=0;i<6;i++)nxt[i]=(c==base[i]?(i+1)%6:i);
			cnt[nxt[0]]=1;co[5]=(c=='e'?n-pos+1:0);
		}
	}
};
tnode operator+(tnode ql,tnode qr){
	tnode ret;ret.sum=ql.sum+qr.sum;
	for(int i=0;i<6;i++){
		ret.nxt[i]=qr.nxt[ql.nxt[i]];
		ret.cnt[i]+=qr.cnt[i];ret.cnt[qr.nxt[i]]+=ql.cnt[i];
		ret.co[i]=ql.co[i]+qr.co[ql.nxt[i]];
		ret.sum+=ql.cnt[i]*qr.co[i];
	}
	return ret;
}
struct Segtree{
	tnode t[MAXN<<2];
	void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
	void build(int p,int l,int r){
		if(l==r)return (void)(t[p]=tnode(s[l],l));int mid=(l+r)>>1;
		build(p<<1,l,mid);build(p<<1|1,mid+1,r);pushup(p);
	}
	void update(int p,int l,int r,int pos,char d){
		if(l==r)return (void)(t[p]=tnode(d,l));
		int mid=(l+r)>>1;
		if(pos<=mid)update(p<<1,l,mid,pos,d);
		else update(p<<1|1,mid+1,r,pos,d);
		pushup(p);
	}
}T;
signed main(){
	scanf("%s%lld",s+1,&Q);n=strlen(s+1);
	T.build(1,1,n);
	printf("%lld\n",T.t[1].sum);
	while(Q--){
		int pos;char opt[2];scanf("%lld%s",&pos,opt);
		T.update(1,1,n,pos,opt[0]);
		printf("%lld\n",T.t[1].sum);
	}
	return 0;
}
```

---

## 作者：PosVII (赞：5)

**前言**

------------

这是一个码了 $10k$ 但是被小码量矩阵乘法动态 dp $O(V^3 n \log n)$ 吊打的彩笔。

考试时只给了一秒，动态 dp 凭什么能过啊！！！

这里是线段树 $O(V n \log n)$ 做法。

**思路**

------------

先考虑直接算一个区间的贡献，很显然可以贪心地来看，从左到右能匹配就匹配，能匹配多少就是多少。

我们先假装矩阵乘法动态 dp 是过不了的。

先想想没有修改的做法。

考虑分治，每次将 $[l,r]$ 的问题划分为 $[l,mid]$ 和 $[mid+1,r]$ 的子问题，然后再考虑两个区间合并时候的贡献。直接合并是 $O(n)$ 的，显然过不了。

考虑一下合并的过程，我们考虑把左区间的每一个后缀与右区间的每一个前缀结合，并求出这个区间的贡献。

有个很显然的贪心策略：左右两区间贪心地计算，左区间从左往右取，而右区间从右往左取，如果它们分别剩下的不完整的串能互相拼成一个完整的串就能多贡献一些。否则它们的贡献就是各自本身的贡献。

发现这些信息都是可以维护的，于是放在线段树上处理。

对于每个结点，记录以下信息：该区间本身的答案，该区间前缀/后缀的答案，该区间前缀/后缀能拼到的字符串位置，该区间如果已有一部分字符串被拼过时候能拼到的字符串位置，该区间如果已有一部分字符串被拼过时候的贡献。

有了这些信息，答案就很好求了。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename G> inline void read(G &x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=2e5+5;
char str[MAXN];
int sub[6]={0,1,2,2,3,1};
struct Segment_Tree {
	struct node {
		int l,r;
		int ls[8],rs[8],lv[8],rv[8],ln[8],rn[8];
		int lval,rval,ans;
		node() {
			for(int i=0;i<=7;++i) ln[i]=rn[i]=ls[i]=rs[i]=lv[i]=rv[i]=0;
			lval=rval=ans=0;
		}
		node(int x,int y) {
			l=x,r=y;
			for(int i=0;i<=7;++i) ln[i]=rn[i]=ls[i]=rs[i]=lv[i]=rv[i]=0;
			lval=rval=ans=0;
		}
		friend node operator+(node x,node y) {
			node z(x.l,y.r);
			z.ans=x.ans+y.ans+x.rval*(y.r-y.l+1)+y.lval*(x.r-x.l+1);
			z.rval=y.rval+x.rval,z.lval=x.lval+y.lval;
			int sum=0;
			for(int i=1;i<=5;++i) {
				sum+=y.ln[i+1];
				z.ans+=x.rn[i]*sum;
			}
			for(int i=0;i<=5;++i) {
				z.rn[y.ls[i]]+=x.rn[i];
				z.rn[i]+=y.rn[i];
				z.rval+=y.lv[i]*x.rn[i];
				z.lv[i]=x.lv[i]+y.lv[x.ls[i]];
				z.ls[i]=y.ls[x.ls[i]];
			}
			for(int i=2;i<=7;++i) {
				z.ln[x.rs[i]]+=y.ln[i];
				z.ln[i]+=x.ln[i];
				z.lval+=x.rv[i]*y.ln[i];
				z.rv[i]=y.rv[i]+x.rv[y.rs[i]];
				z.rs[i]=x.rs[y.rs[i]];
			}
			return z;
		}
	}d[MAXN<<2];
	void build(int l,int r,int p) {
		d[p]=node(l,r);
		if(l==r) {
			if(str[l]=='b') {
				d[p].ln[7]=d[p].rn[1]=1;
				for(int i=0;i<=5;++i) {
					if(i==0) d[p].ls[i]=1;
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==2) {
						d[p].rs[i]=7;
						d[p].rv[i]=1;
					}
					else d[p].rs[i]=i;
				}
			}
			else if(str[l]=='e') {
				d[p].ln[6]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) {
					if(i==1) d[p].ls[i]=2;
					else if(i==5) {
						d[p].ls[i]=0;
						d[p].lv[i]=1;
					}
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==7) d[p].rs[i]=6;
					else if(i==3) d[p].rs[i]=2;
					else d[p].rs[i]=i;
				}
			}
			else if(str[l]=='s') {
				d[p].ln[7]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) {
					if(i==2) d[p].ls[i]=3;
					else if(i==3) d[p].ls[i]=4;
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==5) d[p].rs[i]=4;
					else if(i==4) d[p].rs[i]=3;
					else d[p].rs[i]=i;
				}
			}
			else if(str[l]=='i') {
				d[p].ln[7]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) {
					if(i==4) d[p].ls[i]=5;
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==6) d[p].rs[i]=5;
					else d[p].rs[i]=i;
				}
			}
			else {
				d[p].ln[7]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) d[p].ls[i]=i;
				for(int i=2;i<=7;++i) d[p].rs[i]=i;
			}
//			cout<<l<<' '<<r<<" "<<str[l]<<"!!!!\n";
//			cout<<d[p].rn[0]<<' '<<d[p].rn[1]<<" "<<d[p].rn[2]<<" "<<d[p].rn[3]<<" "<<d[p].rn[4]<<" "<<d[p].rn[5]<<endl;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		d[p]=d[p<<1]+d[p<<1|1];
//		cout<<l<<' '<<r<<"!!!!\n";
//		cout<<d[p].rn[0]<<' '<<d[p].rn[1]<<" "<<d[p].rn[2]<<" "<<d[p].rn[3]<<" "<<d[p].rn[4]<<" "<<d[p].rn[5]<<endl;
	}
	void modify(int l,int r,int k,int p) {
		if(l==r) {
			d[p]=node(l,r);
			if(str[l]=='b') {
				d[p].ln[7]=d[p].rn[1]=1;
				for(int i=0;i<=5;++i) {
					if(i==0) d[p].ls[i]=1;
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==2) {
						d[p].rs[i]=7;
						d[p].rv[i]=1;
					}
					else d[p].rs[i]=i;
				}
			}
			else if(str[l]=='e') {
				d[p].ln[6]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) {
					if(i==1) d[p].ls[i]=2;
					else if(i==5) {
						d[p].ls[i]=0;
						d[p].lv[i]=1;
					}
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==7) d[p].rs[i]=6;
					else if(i==3) d[p].rs[i]=2;
					else d[p].rs[i]=i;
				}
			}
			else if(str[l]=='s') {
				d[p].ln[7]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) {
					if(i==2) d[p].ls[i]=3;
					else if(i==3) d[p].ls[i]=4;
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==5) d[p].rs[i]=4;
					else if(i==4) d[p].rs[i]=3;
					else d[p].rs[i]=i;
				}
			}
			else if(str[l]=='i') {
				d[p].ln[7]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) {
					if(i==4) d[p].ls[i]=5;
					else d[p].ls[i]=i;
				}
				for(int i=2;i<=7;++i) {
					if(i==6) d[p].rs[i]=5;
					else d[p].rs[i]=i;
				}
			}
			else {
				d[p].ln[7]=d[p].rn[0]=1;
				for(int i=0;i<=5;++i) d[p].ls[i]=i;
				for(int i=2;i<=7;++i) d[p].rs[i]=i;
			}
//			cout<<l<<' '<<r<<"!!!!\n";
//			cout<<d[p].rn[0]<<' '<<d[p].rn[1]<<" "<<d[p].rn[2]<<" "<<d[p].rn[3]<<" "<<d[p].rn[4]<<" "<<d[p].rn[5]<<endl;
			return;
		}
		int mid=(l+r)>>1;
		if(k<=mid) modify(l,mid,k,p<<1);
		else modify(mid+1,r,k,p<<1|1);
		d[p]=d[p<<1]+d[p<<1|1];
//		cout<<l<<' '<<r<<"!!!!\n";
//		cout<<d[p].rn[0]<<' '<<d[p].rn[1]<<" "<<d[p].rn[2]<<" "<<d[p].rn[3]<<" "<<d[p].rn[4]<<" "<<d[p].rn[5]<<endl;
	}
}SGT;
int n,m,p;
char ch;
pair<int,int> pii;
signed main() {
//	freopen("pareidolia2.in","r",stdin);
//	freopen("pareidolia.out","w",stdout);
	cin>>(str+1);n=strlen(str+1);
	SGT.build(1,n,1);
	printf("%lld\n",SGT.d[1].ans);
	read(m); 
	for(int i=1;i<=m;++i) {
		read(p);ch=getchar();
		while(ch<'a'||ch>'z') ch=getchar();
		str[p]=ch;
		SGT.modify(1,n,p,1);
		printf("%lld\n",SGT.d[1].ans);
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：4)

## 思路

首先考虑没有多次修改的情况。

不难证明对于 `bessie` 一个字符串，我们可以从某个位置依次向后找接下来的字符。所以我们可以枚举每个子串 $s_i\sim s_j$，先预处理出每个位置后面的第一个 `b,e,s,i`，然后 $O(n)$ 计算出现次数即可。复杂度 $O(n^3)$。

考虑如何优化，我们可以只枚举左端点，向右枚举的时候维护从 $s_i\sim s_j$ 中 `bessie` 出现的次数，然后累加即可。复杂度 $O(n^2)$。

考虑如何优化，计 $dp_{i,0\sim5}$ 表示以 $i$ 为后缀的字符串中，匹配到 `bessie` 的前 $0\sim5$ 位的不同位置数量，同时维护 $sum$ 表示所有前面的方案中匹配数量的总和。如果接下来的第 $i+1$，$sum$ 可以加上 $dp_{i,5}$，其他情况依次转移即可。每个位置算完后将 $sum$ 累加到答案中即可。复杂度 $O(n)$。

如果加上修改呢？不难发现 $dp_{i,0\sim5},sum,ans$ 都是可线性递推的，不难想到可以将其转化成矩阵形式，维护以上 $3$ 个量，修改直接修改矩阵即可，用线段树维护（其实就是动态 dp）。复杂度 $O(qn\log n8^3)$，可以通过。

这题其实还可以区间修改和区间查询。

## 代码

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
struct mtx{
	int a[9][9];
};
mtx mul(mtx x,mtx y){
	mtx z; for(int i=0;i<9;i++) for(int j=0;j<9;j++) z.a[i][j]=0;
	for(int i=0;i<9;i++) for(int j=0;j<9;j++) if(x.a[i][j]) for(int k=0;k<9;k++) z.a[i][k]+=x.a[i][j]*y.a[j][k];
	return z;
}
mtx makem(char c){
	mtx ret;
	for(int i=0;i<9;i++) for(int j=0;j<9;j++) ret.a[i][j]=0;
	ret.a[7][1]=1;
	ret.a[0][8]=1;
	ret.a[8][8]=1;
	if(c=='b'){
		ret.a[0][0]=1;
		ret.a[1][2]=1;
		ret.a[2][2]=1;
		ret.a[3][3]=1;
		ret.a[4][4]=1;
		ret.a[5][5]=1;
		ret.a[6][6]=1;
		ret.a[7][7]=1;
		return ret;
	}
	if(c=='e'){
		ret.a[0][0]=1;
		ret.a[1][1]=1;
		ret.a[2][3]=1;
		ret.a[3][3]=1;
		ret.a[4][4]=1;
		ret.a[5][5]=1;
		ret.a[6][0]=1;
		ret.a[6][8]=1;
		ret.a[6][1]=1;
		ret.a[7][7]=1;
		return ret;
	}
	if(c=='s'){
		ret.a[0][0]=1;
		ret.a[1][1]=1;
		ret.a[2][2]=1;
		ret.a[3][4]=1;
		ret.a[4][5]=1;
		ret.a[5][5]=1;
		ret.a[6][6]=1;
		ret.a[7][7]=1;
		return ret;
	}
	if(c=='i'){
		ret.a[0][0]=1;
		ret.a[1][1]=1;
		ret.a[2][2]=1;
		ret.a[3][3]=1;
		ret.a[4][4]=1;
		ret.a[5][6]=1;
		ret.a[6][6]=1;
		ret.a[7][7]=1;
		return ret;
	}
	ret.a[0][0]=1;
	ret.a[1][1]=1;
	ret.a[2][2]=1;
	ret.a[3][3]=1;
	ret.a[4][4]=1;
	ret.a[5][5]=1;
	ret.a[6][6]=1;
	ret.a[7][7]=1;
	return ret;
}
char c[200005];
struct sgt{
	mtx f[800005];
	void build(int i,int l,int r){
		if(l==r){
			f[i]=makem(c[l]);
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=mul(f[i*2],f[i*2+1]);
//		cout<<l<<" "<<r<<" "<<f[i].a[1][0]+f[i].a[7][0]<<" "<<f[i].a[1][8]+f[i].a[7][8]<<endl;
	}
	void change(int i,int l,int r,int pos){
		if(l==r){
			f[i]=makem(c[l]);
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos);
		else change(i*2+1,mid+1,r,pos);
		f[i]=mul(f[i*2],f[i*2+1]);
	}
}tree;
mtx ori;
signed main(){
	ori.a[0][1]=ori.a[0][7]=1;
	string s; cin>>s; int n=s.size();
	for(int i=1;i<=n;i++) c[i]=s[i-1];
	tree.build(1,1,n);
	cout<<mul(ori,tree.f[1]).a[0][8]<<"\n";
	int q; cin>>q;
	while(q--){
		int pos; char cg;
		cin>>pos>>cg;
		c[pos]=cg;
		tree.change(1,1,n,pos);
		cout<<mul(ori,tree.f[1]).a[0][8]<<"\n";
	}
	return 0;
} 
```

---

## 作者：Acee (赞：1)

分块被卡了，呜呜。

留下 `bessie` 的步骤肯定使用的贪心，但发现不好扩展。

但可以用类似的思路，设 $f_{i,j}$ 为第 $i$ 个，匹配到了第 $j$ 个的数量。

转移十分的简单，可以用矩阵乘法优化，那么带修就可以直接套个线段树即可。

代码：
```cpp
#include <bits/stdc++.h>

const int N = 2e5 + 5;
typedef long long ll;
int n;
std::string s;
struct matrix {
  ll a[9][9];
};
inline matrix mul(const matrix &x, const matrix &y) {
  matrix z;
  memset(z.a, 0, sizeof(z.a));
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j)
      if (x.a[i][j])
        for (int k = 0; k < 9; ++k)
          z.a[i][k] += x.a[i][j] * y.a[j][k];
  return z;
}
inline matrix make_matrix(char c) {
  matrix res;
  memset(res.a, 0, sizeof(res.a));
  res.a[7][1] = 1, res.a[0][8] = 1, res.a[8][8] = 1;
 if (c == 'b') {
res.a[0][0] = 1, res.a[1][2] = 1, res.a[2][2] = 1, res.a[3][3] = 1,
res.a[4][4] = 1, res.a[5][5] = 1, res.a[6][6] = 1, res.a[7][7] = 1;
return res;
  }
  if (c == 'e') {
res.a[0][0] = 1, res.a[1][1] = 1, res.a[2][3] = 1, res.a[3][3] = 1,
res.a[4][4] = 1, res.a[5][5] = 1, res.a[6][0] = 1, res.a[6][8] = 1,
res.a[6][1] = 1, res.a[7][7] = 1;
return res;
  }
  if (c == 's') {
res.a[0][0] = 1, res.a[1][1] = 1, res.a[2][2] = 1, res.a[3][4] = 1,
res.a[4][5] = 1, res.a[5][5] = 1, res.a[6][6] = 1, res.a[7][7] = 1;
return res;
  }
  if (c == 'i') {
res.a[0][0] = 1, res.a[1][1] = 1, res.a[2][2] = 1, res.a[3][3] = 1,
res.a[4][4] = 1, res.a[5][6] = 1, res.a[6][6] = 1, res.a[7][7] = 1;
return res;
  }
  res.a[0][0] = 1, res.a[1][1] = 1, res.a[2][2] = 1, res.a[3][3] = 1,
  res.a[4][4] = 1, res.a[5][5] = 1, res.a[6][6] = 1, res.a[7][7] = 1;
  return res;
}
matrix a[N], m[N << 2], res;
inline void solve() {

  memset(res.a, 0, sizeof(res.a));
  res.a[0][1] = res.a[0][7] = 1;
  // for (int i = 1; i <= bl[n]; ++i)
  // res = mul(res, p[i]);

  std::cout << mul(res, m[1]).a[0][8] << '\n';
}
void change(int p, int l, int r, int x) {
	if(l == r) return m[p] = a[l], void();
	int mid = (l + r) >> 1;
	if(x <= mid) change(p << 1, l, mid, x);
	else change(p << 1 | 1, mid + 1, r, x);
	m[p] = mul(m[p << 1], m[p << 1 | 1]);
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);
  std::cin >> s;
  n = s.size(), s = ' ' + s;
  for (int i = 1; i <= n; ++i) {
a[i] = make_matrix(s[i]);
change(1, 1, n, i);
    // std::cerr << i << '\n';
  }
  // return 0;
  int Q;
  std::cin >> Q;
  solve();
  while (Q--) {
    int id;
    char c;
    std::cin >> id >> c;
    a[id] = make_matrix(c);
    change(1, 1, n, id);
    solve();
  }
  return 0;
}
```

---

