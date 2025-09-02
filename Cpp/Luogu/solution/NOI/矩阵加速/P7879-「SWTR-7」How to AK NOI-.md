# 「SWTR-7」How to AK NOI?

## 题目背景

#### 一些关于字符串的定义与约定详见「帮助 / 提示」部分。

#### 请不要恶意卡评测。

---

小 A 正在读一篇文章 ——《如何优雅地 AK NOI？》

## 题目描述

不幸的是，这篇文章是用英语写的。小 A 的视力很糟糕，同时词汇量也很小。

具体地，这篇文章可以用一个字符串 $t$ 表示。同时给出另一个字符串 $s$：小 A 所有认识的单词，都是 $s$ 的**长度不小于 $k$ 的**子串。

一段文字 $T$ 被称为「可读懂的」，当且仅当其能被分割成若干个小 A 读得懂的单词。例如当 $k=2$，$s=\texttt{abcd}$ 时，$\texttt{abcd/abc}$ 和 $\texttt{cd/ab/bc/bcd}$ 就是可读懂的，而 $\texttt{abcc}$ 和 $\texttt{tzcaknoi}$ 就是不可读懂的。

接下来，小 A 会进行 $q$ 次行动：

- Type 1：擦亮眼睛。具体地，小 A 会选择文章 $t$ 的一个子串 $t[l:r]$，并将其修改为字符串 $x\ (|x|=r-l+1)$。
- Type 2：阅读文章。具体地，小 A 会选择文章 $t$ 的一个子串 $t[l:r]$ 并进行阅读。**对于每次 Type 2 的操作，你需要告诉小 A 他能不能看懂这段文字**。能够读懂则输出 `Yes`，否则输出 `No`。

## 说明/提示

**「数据范围与约定」**

记 $n=|s|$，$m=|t|$，$L=\sum |x|$。

| Subtask |    $n\leq$     | $m\leq$ | $L\leq$ | $q\leq$ | $k\leq$ |   分值    |
| :-----: | :------------: | :-----: | :-----: | :-----: | :-----: | :-------: |
| 0 |  |  |  |  |  | 0 point |
|    1    |      $70$      |  $70$   |         |  $70$   |         | 10 points |
|    2    |     $200$      |  $200$  |         |  $200$  |         | 10 points |
|    3    |     $10^3$     | $10^3$  |         | $10^3$  |         | 10 points |
|    4    |                |         |         |         |   $1$   | 10 points |
|    5    | $2\times 10^5$ | $10^5$ |   $0$   | $2\times 10^4$  |   $5$   | 15 points |
|    6    | $2\times 10^5$ | $10^5$  | $5\times 10^4$  | $2\times 10^4$  |   $5$   | 10 points |
|    7    |  |         |         |         |   $6$   | 15 points |
|    8    |                |         |         |         |         | 20 points |

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^6$，$1\leq L\leq 3\times 10^5$，$1\leq m\leq 2\times 10^5$，$1\leq q\leq 10^5$，$1\leq k\leq 8$。    保证 $|x|=r-l+1$，且字符集为 $[\texttt{a,i}]$。

---

Subtask 0 是样例及 **Hack 数据**。

- Subtask 0 ~ 3 时间限制 1s。
- Subtask 4 ~ 6 时间限制 1.5s。
- Subtask 7 时间限制 3s。
- Subtask 8 时间限制 4.5s。

**「子任务依赖」**

**本题使用子任务依赖**。

简单地说，如果 Subtask a 依赖于 Subtask b，那么**只有你通过 Subtask b 的全部测试点时，Subtask a 才会计入总分**。

- Subtask 1 依赖于 Subtask 0。
- Subtask 2 依赖于 Subtask 0,1。
- Subtask 3 依赖于 Subtask 0,1,2。
- Subtask 6 依赖于 Subtask 0,5。
- Subtask 7 依赖于 Subtask 0,5,6。
- Subtask 8 依赖于 Subtask 0~7。

**保证 Subtask 0 的 Hack 数据符合 Subtask 1,2,3,6,7,8 的所有限制**。

**「帮助 / 提示」**

字符串 $t'$ 是 $t$ 的子串，当且仅当我们能够从 $t$ 的开头和结尾删除若干个字符（可以不删除）并得到 $t'$。  
定义 $t[l:r]$ 表示 $t_lt_{l+1}\cdots t_{r-1}t_r$ 所形成的字符串。

读入文件较大，请注意 IO 优化。

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) E。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[tzc_wk](https://www.luogu.com.cn/user/115194)。

## 样例 #1

### 输入

```
0
bbccabcacbcbac
cbcacbcabbcabca
3
17
2 1 2
2 1 4
2 1 6
2 2 15
2 6 15
2 9 15
1 4 13 babbccabbd
2 1 11
2 1 12
2 1 15
2 5 11
1 13 15 cab
2 3 12
2 7 10
2 11 15
2 10 14
2 9 14```

### 输出

```
No
No
Yes
Yes
Yes
Yes
Yes
No
No
No
No
Yes
No
No
Yes```

# 题解

## 作者：万弘 (赞：9)

 $ k $ 足够小是解题的关键.

 $ \text{Lemma 1:} $  若存在方案,则至少有一种方案不选择长度超过 $ 2k $ 的串.

考虑长度超过 $ 2k $ 的串一定能拆成两个至少为 $ k $ 的串即可.

考虑对每个 $ T_i $ 处理出 $ l_i $ 表示最大的 $ l $ 使得 $ T[i,i+l-1] $ 是 $ S $ 的子串,而由L1,超过 $ 2k $ 时可以直接认为是 $ 2k $ .通过对 $ S $ 建SAM,这部分复杂度是 $ O(nk) $ .

对于询问,考虑从左往右匹配, $ f(i) $ 表示 $ T[l,i] $ 这个前缀能否匹配.对于 $ T_i $ ,可以转移到 $ [i+k-1,i+l_i-1] $ .

那么考虑类似动态dp,对 $ i $ 构造矩阵
$$
\begin{bmatrix}
0 & 0 & 0& \cdots &1& 1& 1&\cdots& 0&0\\
1 & 0 & 0&\cdots& 0 & 0 & 0&\cdots & 0& 0\\
0 & 1 & 0 &\cdots& 0 & 0 & 0&\cdots & 0& 0\\
\vdots\\
0& 0 & 0&\cdots& 0 & 0 & 0 &\cdots & 1 &0
\end{bmatrix}
$$
~~这效果还不如直接口述~~

口述一下就是,第一行 $ [k-1,l_i-1] $ 这些是 $ 1 $ 别的是0,第 $ i(i>1) $ 行仅有第 $ i-1 $ 列是1.

原理很简单,要么转移到 $ [i+k-1,i+l_i-1] $  要么前移一步.

用线段树维护,每次暴力修改  $ O(L) $ 个位置,复杂度是 $ O(L\log m\  \text{Mul}(2k)+q\log m\ \text{VMul}(2k)) $ ,其中 $ \text{Mul}(2k) $ 表示大小为 $ 2k\times 2k $ 的矩阵乘法复杂度,本题中可以通过压位做到 $ 4k^2 $ , $ \text{VMul} $ 表示大小为 $ 1\times 2k $ 的行向量乘 $ 2k\times 2k $ 的矩阵的复杂度,可以压位做到 $ 2k $ .

或者用分块维护, $ O(L\ \text{Mul}(2k)+q\sqrt m\ \text{VMul}(2k)) $ .

或者用分块+线段树维护.

下面代码使用线段树,正确性和复杂度均正确,但仍需要一些常数优化,仅供参考.

```
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long ll;
typedef unsigned un;
typedef unsigned long long ull;
typedef std::pair<int,int> pii;
int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();
	return f*x;
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
template<typename T> bool umin(T& a,T t){if(a>t)return a=t,1;return 0;}
template<typename T> bool umax(T& a,T t){if(a<t)return a=t,1;return 0;}
/**********/
const int MAXN = 6000011;
struct SAM
{
	int t[MAXN][9],pre[MAXN],len[MAXN],last,tot;
	SAM(){last=tot=1;}
	void extend(int w)
	{
		int pos=last,cur=++tot;
		len[cur]=len[pos]+1,last=cur;
		while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
		if(!pos){pre[cur]=1;return;}
		int nxt=t[pos][w];
		if(len[nxt]==len[pos]+1)pre[cur]=nxt;
		else
		{
			int tmp=++tot;
			len[tmp]=len[pos]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
			pre[tmp]=pre[nxt],pre[cur]=pre[nxt]=tmp;
			while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
		}
	}
}sam;
struct Bmatrix
{
	un a[16];
	Bmatrix(){memset(a,0,sizeof a);}
	Bmatrix(un* tp){memcpy(a,tp,sizeof a);}
	inline Bmatrix operator* (const Bmatrix& you)
	{
		static un tp[16];
		memset(tp,0,sizeof tp);
		for(int i=0;i<16;++i)
			for(int k=0;k<16;++k)
				if(a[i]&(1u<<k))tp[i]|=you.a[k];
		return tp;
	}
	void see()
	{
		puts("See:");
		for(int i=0;i<16;++i)
		{
			for(int j=0;j<16;++j)printf("%d",a[i]>>j&1);
			puts("");
		}
	}
}a[200011];
int lf[200011];
Bmatrix getmat(int s,int t)
{
	static un tp[16];
	memset(tp,0,sizeof tp);
	if(s<=t)tp[0]=((1u<<(t+1))-1)^((1u<<s)-1);
	for(int i=1;i<16;++i)tp[i]=1u<<(i-1);
	return tp;
}
int n;
struct Segment_Tree
{
	static const int MAXN = 200011;
	Bmatrix t[MAXN<<2|1];
#define rt t[num]
#define tl t[num<<1]
#define tr t[num<<1|1]
	void init(un l=1,un r=n,un num=1)
	{
		if(l==r){rt=a[l];return;}
		un mid=(l+r)>>1;
		init(l,mid,num<<1),init(mid+1,r,num<<1|1);
		rt=tl*tr;
	}
	void modify(un pos,un l=1,un r=n,un num=1)
	{
		if(l==r){rt=a[l];return;}
		un mid=(l+r)>>1;
		if(pos<=mid)modify(pos,l,mid,num<<1);
		else modify(pos,mid+1,r,num<<1|1);
		rt=tl*tr;
	}
	un res;
	void Query(un ql,un qr,un l=1,un r=n,un num=1)
	{
		if(ql<=l&&r<=qr)
		{
			//printf("[%u,%u]\n",l,r);
			//rt.see();
			un f=0;
			for(int i=0;i<16;++i)
				if(res&(1u<<i))f|=rt.a[i];
			res=f;
			return;
		}
		un mid=(l+r)>>1;
		if(ql<=mid)Query(ql,qr,l,mid,num<<1);
		if(qr>mid)Query(ql,qr,mid+1,r,num<<1|1);
	}
}sgt;
char s[MAXN],t[200011];
int main()
{
	int tasknumber=read();
	scanf("%s%s",s+1,t+1);
	int k=read(),q=read();
	int sn=strlen(s+1);
	for(int i=1;i<=sn;++i)sam.extend(s[i]-'a');
	n=strlen(t+1);
	for(int i=1;i<=n;++i)
	{
		int u=1,j=0;
		for(;j<k+k&&i+j<=n;++j)
		{
			u=sam.t[u][t[i+j]-'a'];
			if(!u)break;
		}
		a[i]=getmat(k-1,j-1);
		lf[i]=j;
		//a[i].see();
	}
	sgt.init();
	while(q--)
	{
		int op=read();
		if(op==1)
		{
			int l=read(),r=read();
			char pre=t[r+1];
			scanf("%s",t+l);
			t[r+1]=pre;
			for(int i=max(1,l-k-k);i<=r;++i)
			{
				int u=1,j=0;
				for(;j<k+k&&i+j<=n;++j)
				{
					u=sam.t[u][t[i+j]-'a'];
					if(!u)break;
				}
				if(j!=lf[i])a[i]=getmat(k-1,j-1),lf[i]=j,sgt.modify(i);
			}
		}
		else
		{
			int l=read(),r=read();
			sgt.res=1;
			sgt.Query(l,r);
			puts(sgt.res&1?"Yes":"No");
		}
	}
	return 0;
}
```



---

## 作者：tzc_wk (赞：5)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P7879)

~~orz 一发出题人（话说我 AC 这道题的时候，出题人好像就坐在我的右侧呢/cy/cy）~~

考虑一个很 naive 的 DP，$dp_i$ 表示 $[l,i]$ 之间的字符串是否可以被识别，转移就枚举上一段的终止为止，然后 SAM/哈希判断子串是否在 $s$ 中出现过。

注意到一个事实：所有长度 $>2k$ 的字符串都可以由长度 $\ge k$ 的字符串拼成，也就是说只有长度在 $[k,2k]$ 的字符串是有用的，故每次转移只用枚举 $k+1$ 个转移点。注意到 $k$ 的数据范围很小，因此我们可以考虑矩阵优化转移，即对于大小分别为 $n\times m$ 和 $m\times k$ 的矩阵 $A,B$，定义其乘积 $C$ 满足 $C_{i,j}=\text{or}_{t=1}^mA_{i,t}\land B_{t,j}$，那么
$$
\begin{bmatrix}
dp_{i}&dp_{i-1}&\cdots&dp_{i-2k+1}
\end{bmatrix}
=
\begin{bmatrix}
dp_{i-1}&dp_{i-2}&\cdots&dp_{i-2k}
\end{bmatrix}
\times
\begin{bmatrix}
g_1&1&0&0&\cdots&0\\
g_2&0&1&0&\cdots&0\\
g_3&0&0&1&\cdots&0\\
\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\
g_{2k-1}&0&0&0&\cdots&1\\
g_{2k}&0&0&0&\cdots&0
\end{bmatrix}
$$
其中 $g_j$ 表示 $[i-j+1,i]$ 是否为 $s$ 的子串。

显然每次修改一个区间最多改变 $r-l+1+2k$ 个位置的转移矩阵，因此我们有一个很自然的想法：线段树维护矩阵乘积，每次暴力修改线段树对应的位置的值，求一个位置的转移矩阵可用 SAM。查询就求一遍区间矩阵乘积，这样复杂度大概是 $(L+qk)·k^3\log n+qk^3\log n$，显然无法通过，不过这里矩阵每个元素都是 0/1，因此可以用位运算加速实现 $k^2$ 矩阵乘法，这样复杂度可达到 $(L+qk)·k^2\log n+qk^2\log n$，还是无法通过。再观察到每次修改是一段区间，因此考虑对**这一段区间上的叶子节点到根节点路径的并上的节点**，重新计算它们转移矩阵的乘积，这样假设待重构的区间长度为 $len$，每次重构需要进行矩阵乘法的次数大概是 $\sum\limits_{n}\lfloor\dfrac{len}{n}\rfloor=\mathcal O(len)$ 级别的，这样加号前面的 $\log n$ 可以省去，复杂度就达到了 $(L+qk)·k^2+qk^2\log n$，可以通过。

```cpp
const int MAXN=3e6;
const int MAXM=3e5;
const int MAXP=6e6;
const int MAXK=16;
int n,m,k,qu;char s[MAXN+5],t[MAXM+5];
int ch[MAXP+5][9],len[MAXP+5],lnk[MAXP+5],cur=1,ncnt=1;
void extend(char c){
	int id=c-'a',nw=++ncnt,p=cur;
	len[nw]=len[cur]+1;cur=nw;
	while(p&&!ch[p][id]) ch[p][id]=nw,p=lnk[p];
	if(!p) return lnk[nw]=1,void();
	int q=ch[p][id];
	if(len[q]==len[p]+1) return lnk[nw]=q,void();
	int cl=++ncnt;len[cl]=len[p]+1;
	lnk[cl]=lnk[q];lnk[q]=lnk[nw]=cl;
	for(int i=0;i<9;i++) ch[cl][i]=ch[q][i];
	while(p&&ch[p][id]==q) ch[p][id]=cl,p=lnk[p];
}
struct mat{
	int a[MAXK+2];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat &rhs){
		mat res;
		for(int i=0;i<k*2;i++) for(int j=0;j<k*2;j++)
			if(a[i]>>j&1) res.a[i]|=rhs.a[j];
		return res;
	}
	void print(){
		for(int i=0;i<k+k;i++) for(int j=0;j<k+k;j++)
			printf("%d%c",a[i]>>j&1,"\0\n"[j==k+k-1]);
	}
};
int lf[MAXM+5],used[MAXM*4+5];
mat calc(int l){
	mat ret;
	for(int i=0;i+1<k+k;i++) ret.a[i]|=1<<i+1;
	int curp=1;
	for(int i=1;i<=min(l,k+k);i++){
		if(!ch[curp][t[l-i+1]-'a']) break;
		curp=ch[curp][t[l-i+1]-'a'];
		if(i>=k) ret.a[i-1]|=1;
	}
//	printf("calc %d\n",l);
//	ret.print();
	return ret;
}
namespace segtree{
	struct node{int l,r;mat v;} s[MAXM*4+5];
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;
		if(l==r){s[k].v=calc(l),lf[l]=k;return;}
		int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
		s[k].v=s[k<<1].v*s[k<<1|1].v;
	}
	void rebuild(int k){
		if(!used[k]) return;used[k]=0;
		if(s[k].l==s[k].r) return;
		rebuild(k<<1);rebuild(k<<1|1);
		s[k].v=s[k<<1].v*s[k<<1|1].v;
	}
	mat query(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r) return s[k].v;
		int mid=s[k].l+s[k].r>>1;
		if(r<=mid) return query(k<<1,l,r);
		else if(l>mid) return query(k<<1|1,l,r);
		else return query(k<<1,l,mid)*query(k<<1|1,mid+1,r);
	}
}
void rebuild(int l,int r){
	static char buf[MAXM+5];scanf("%s",buf+1);
	for(int i=l;i<=r;i++) t[i]=buf[i-l+1];
	for(int i=l;i<=min(r+k+k,m);i++){
		for(int j=lf[i];j;j>>=1) used[j]=1;
		segtree::s[lf[i]].v=calc(i);
	} segtree::rebuild(1);
}
int main(){
//	freopen("passage.in","r",stdin);
//	freopen("passage.out","w",stdout);
	scanf("%*d%s%s%d%d",s+1,t+1,&k,&qu);
	n=strlen(s+1);m=strlen(t+1);
	for(int i=n;i;i--) extend(s[i]);
	segtree::build(1,1,m);
	while(qu--){
		int opt;scanf("%d",&opt);
		if(opt==1){
			int l,r;scanf("%d%d",&l,&r);
			rebuild(l,r);
		} else {
			int l,r;scanf("%d%d",&l,&r);
			mat v=segtree::query(1,l,r);
			printf("%s\n",(v.a[0]&1)?"Yes":"No");
//			v.print();
		}
	}
	return 0;
}
```



---

## 作者：qiuzx (赞：1)

## 题意

给定字符串 $s,t$，以及正整数 $k$，定义一个串是好的，当且仅当它是 $s$ 的某个长度不小于为 $k$ 的子串。有 $q$ 次操作，将 $t[l,r]$ 修改为某个串 $x$，或查询是否能够将 $t[l,r]$ 拆分成若干个好的串拼接起来。$n=|s|\le 3\times 10^6,m=|t|\le 2\times 10^5,L=\sum|x|\le 3\times 10^5,q\le 10^5,k\le 8,\Sigma\le 10$。

## 思路

首先有一个很关键的性质，即只有长度至多是 $2k$ 的串是有用的。这是因为若一个串是好的，则它所有长度不小于 $k$ 的子串也是好的。那么如果我们拆出了一个长度 $>2k$ 的串，一定能将它拆成两个长度更小的好串。所以若存在拆分方案，则必然存在每个拆出来的串长度 $\le 2k$ 的拆分方案。这样我们可以写出一个暴力的 dp，若记 $p_i$ 表示 $t$ 以 $i$ 结尾的子串中是 $s$ 子串的最长长度，记 $dp_i$ 表示仅考虑前 $i$ 个字符，是否能够恰好划分完。则 $dp_i$ 可以从 $dp_{[i-p_i,i-k]}$ 转移而来。根据我们刚刚的结论，$p_i>2k$ 是没有意义的，所以和 $2k$ 取 $\min$ 即可。

先考虑 $p_i$ 怎么在有修改的情况下快速求，由于 $p_i$ 至多为 $2k$，所以可以暴力从小到大枚举 $p_i$，而在 $p_i$ 增加的时候，可以在 $s$ 反串的 SAM 上走转移边来判断是否是子串。而一次修改只会影响到 $[l,r+2k]$ 的 $p_i$，所以我们可以 $O(n\Sigma)$ 预处理 SAM，$O(Lk+qk^2)$ 求 $p_i$，这样这部分已经是可以接受的复杂度了。

下面考虑怎么优化这个暴力的 dp。我们可以将这个转移看作一个有向图，需要判断 $s\to t$ 是否存在路径。而这个有向图的性质就是所有边两侧点编号之差的绝对值不超过 $2k$，这样就可以想到一个类似矩阵乘法的优化过程。具体来说，对于一个区间 $[l,r]$，我们对于所有 $i\in [l,l+2k)$ 和所有 $j\in (r-2k,r]$，维护 $i$ 能否走到 $j$。合并两个区间 $[l_1,r_1],[l_2,r_2](l_2=r_1+1)$ 时，首先处理出所有 $j\in (r_1-2k,r_1]$ 和 $i\in[l_2,l_2+2k)$ 能否通过边走到（注意可以在内部走多步），然后按照矩阵乘法的方式合并即可。这样朴素实现的合并过程复杂度为 $O(k^3)$。在原题中，可以使用线段树维护区间对应的矩阵，总复杂度 $O((L+qk)k^3\log m)$，显然无法通过。

则我们需要优化这个合并过程。注意到矩阵中所有元素都是 $01$，并且我们需要做的是一个类似把一些矩阵或起来的操作，所以可以使用一个二进制数 $mask_i$ 表示 $i\in [l,l+2k)$ 能否到达 $r-j$，若可以则这一位是 $1$。这样这是一个 $2k$ 位的二进制数，考虑使用这个来进行合并。我们先枚举 $i\in[l_1,l_1+2k)$，然后枚举 $j\in [l_2,l_2+2k)$，这样若我们知道 $i$ 能到 $j$，则令 $mask_i$ 或上 $mask_j$ 即可。而为了判定 $i$ 能否到 $j$，我们从左往右枚举 $j$，则我们需要对一段区间 $[j-r,j-l]$ 判断 $i$ 能够到这个区间中的任意一个位置。我们实时维护 $i$ 能够到达位置的集合（用一个二进制数表示），则直接按位与一下就可以得到结果。求完 $j$ 之后再更新这个集合即可。这样我们就有一个 $O(k^2)$ 合并的方法。总复杂度少了一个 $k$，变成 $O((L+qk)k^2\log m)$，但还是不足以通过。

注意到现在的瓶颈在 $qk^3\log n$ 这里，但为了修改一个元素去在线段树上修改 $k$ 个元素是很浪费的一件事。所以我们不要把修改想象成单点修改，而是在线段树上将整个修改区间修改了。具体来说，我们就按照正常的区间修改的方式找到这个修改区间对应的线段树节点，只不过这里我们不返回，而是继续向下直到叶子。到叶子之后就按照正常的过程修改即可。这样一次修改若修改区间长度为 $x$，则访问的节点数是 $x,\lceil\frac x2\rceil,\lceil\frac {\lceil\frac x2\rceil}2\rceil,\cdots$，这样所有操作访问的节点数之和就是 $O(L+qk+q\log m)$，所以总复杂度变为 $O((L+qk+q\log m)k^2)$，可以通过。

需要注意的细节是合并区间长度 $<2k$ 时，使用刚刚的合并方法可能会出现问题，此时直接 $O(k^2)$ 暴力求每个位置的答案即可。

[代码](https://www.luogu.com.cn/paste/43xe6fet)

---

