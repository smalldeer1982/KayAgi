# [JRKSJ R4] risrqnis

## 题目描述

给你一个长度为 $n$ 的序列 $a_{1\sim n}$，有 $q$ 次操作，初始有 $m$ 个空集 $S_{1\sim m}$，共有两种操作，如下：

- `1 l r k`，将 $l\sim r$ 加入集合 $S_k$，即 $S_k\gets S_k\cup\{x|x\in[l,r]\cap \N\}$；
- `2 l r k`，查询对于所有 $l\le i\le r$ 的 $a_i$ 中有多少个在集合 $S_k$ 中，即查询 $\displaystyle\sum_{i=l}^r[a_i\in S_k]$。

## 说明/提示

### 数据规模
| $\text{Subtask}$ | $n,q\le$ | $m\le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^6$ | $1$ | $30$ |
| $2$ | $5\times 10^3$ | $3\times 10^5$ | $15$ |
| $3$ | $10^5$ | $10^5$ | $15$ |
| $4$ | $3\times 10^5$ | $10^9$ | $40$ |

对于 $100\%$ 的数据，$1\le n,q\le 10^6$，$1\le m\le 10^9$，$1\le a_i\le 10^9$。

操作 $1$ 中 $1\le l\le r\le 10^9$，操作 $2$ 中 $1\le l\le r\le n$。所有操作中 $1\le k\le m$。

**没有一个 $\text{Subtask}$ 取到所有数据范围的最大值，各个 $\text{Subtask}$ 都有自己的限制。请阅读数据范围表。**

**本题输入文件较大，请使用恰当的读入方式。**
****

深夜，上条当麻的手机响起了收信声。随即，他来到了邮件所写的地方。第七学区的铁桥。

上条到达的时候，发信人早已经等在那了。

「御坂吗……？」

「你忘记的东西。」

她说着丢了什么过来。上条单手接住，发现那是个青娃的手机挂件。他沉入北水洋的时候这东西就应该不见了啊。它用来系到手机上的挂绳当初都粉碎了，现在却换成了其他颜色的绳子。

「好不容易找回来的，别再弄丢了哦。」

「不好意思。」

上条道了声谢，将它再次系到了手机上。

见状，美琴微微一笑。

那是似乎终于把什么东西回归原状而松了一口气的表情。

「我想你这个家伙应该不会一直呆在一个地方的吧…接下来该不会你又要去哪？」 

「算是吧。」

上条叹了口气。

「老实说虽然我一副淡定的表情，但实际上我也对究竟发生了什么一头雾水，只知道元凶的名字而已。不过这场骚动已经波及到了学园都市，而正在追查学园都市的我也被卷入其中，被我追查的学园都市同样被卷入……所以我也没办法置之不理了。」

美琴找他似乎就只是为了送挂饰而已。上条将手机放进了口袋。

既然没有了话题，那也只能分别了。

「再见了。」上条说道。

转身背对着美琴，准备离开铁桥，

准备离开这个由科学常识构筑的学园都市，大步迈向外面的领域，而少年的手，却被美琴抓住了。 

确确实实地，紧紧拉住想要飘然离开的少年。

在静止的上条耳边，传来了美琴的声音。

「但，这次你不会是一个人了。」 

![114514](https://cdn.luogu.com.cn/upload/image_hosting/0rezlv6r.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

## 样例 #1

### 输入

```
5 10 2
5 4 3 2 1
2 1 5 1
2 1 5 2
1 2 3 1
1 2 3 2
2 1 4 1
2 1 4 2
1 1 4 1
1 1 4 2
2 1 5 1
2 3 5 2```

### 输出

```
0
0
2
2
4
3```

# 题解

## 作者：abruce (赞：11)

因为是和出题人截然不同的做法，且常数更为优秀，所以就以博客的形式挂了出来。欢迎大家提出更为优秀的做法。  

首先考虑 $m=1$。我们发现，每个数最多只会被加入 $S$ 一次，所以我们可以均摊分析。考虑用一个并查集维护在值域上所属 $1$ 区间最右端点，然后每次暴力把一个数赋值成 $1$ 加入树状数组就可以了，查询直接区间求和。时间复杂度 $O(n\log n)$。  
但是 $m$ 较大的时候，对于每一个 $S_k$，我们都要将势能归零，这会非常慢。因为 $S_k$ 独立，考虑对 $S_k$ 的操作次数进行根号分治：  

对于操作次数大于 $\sqrt{q}$ 的 $k$，我们考虑用上面的方法。但是发现修改是 $O(\sqrt{n}\log n)$ 查询是 $O(\log n)$ 的很不平衡，所以考虑根号平衡，即把树状数组换成 $O(1)$ 区间修改，$O(\sqrt{n})$ 单点查询的分块，这一部分复杂度 $O(n\sqrt{q}+q\sqrt{n})$。（当然这里是把并查集的复杂度忽略了的，据 dqstz 大佬分析，用 ODT 而不是并查集可以达到严格复杂度）  

对于操作次数小于 $\sqrt{q}$ 的 $k$，我们发现一个好处是加入的区间所形成的值域连续段数量不会超过 $\sqrt{q}$。所以我们在查询的时候可以对每个值域连续段查询询问的区间在这个连续段内有多少个，这相当于一个二维数点。但是离线下来后我们不能用树状数组维护，因为这会使修改是 $O(\log n)$ 查询是 $O(\sqrt{n}\log n)$ 的很不平衡。所以我们一样的用一个 $O(\sqrt{n})$ 单点修改，$O(1)$ 区间查询的分块，这一部分复杂度 $O(n\sqrt{n}+q\sqrt{q})$。但是发现空间复杂度达到了 $O(n\sqrt{n})$  级别，于是我们可以离线询问的区间，然后给那需要用到它的询问加上贡献，这样就可以达到线性空间。  

综上，令 $n,q$ 同阶，复杂度 $O(n\sqrt{n})$。注意 $m=1$ 特判。代码仅供参考。  

```cpp
#include<bits/stdc++.h>
#define fi first
#define sc second
using namespace std;
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
const int maxn=3e5+5,maxm=666,mxn=1e6+5;
int n,q,m,lp[maxm],rp[maxm],bel[maxn],sqrtn,sn,ans[maxn],a[mxn],b[mxn],op[maxn],qc,nowk;
typedef pair<int,int> pi;
pi id[mxn];
namespace sub0 {
	int c[mxn],f[mxn];
	int getf(int x) {
		return f[x]==x?x:f[x]=getf(f[x]);
	}
	void add(int x) {
		while(x<=n)c[x]++,x+=x&(-x);
	}
	int ask(int x) {
		int sum=0;
		while(x)sum+=c[x],x-=x&(-x);
		return sum;
	}
	void solve() {
		int op,l,r;
		for(int i=1; i<=n+1; i++)f[i]=i;
		while(q--) {
			op=read(),l=read(),r=read(),read();
			if(op==1) {
				l=lower_bound(b+1,b+n+1,l)-b,r=upper_bound(b+1,b+n+1,r)-b-1;
				int x=getf(l);
				while(x<=r)add(id[x].sc),f[x]=f[x+1],x=getf(x+1);
			} else printf("%d\n",ask(r)-ask(l-1));
		}
	}
}
struct quest {
	int op,l,r,k,id;
	friend bool operator<(const quest a,const quest b) {
		return a.k==b.k?a.id<b.id:a.k<b.k;
	}
} p[maxn];
namespace sub1 {
	struct node {
		int l,r,st;
		node() {}
		node(int l,int r,int st) {
			this->l=l,this->r=r,this->st=st;
		}
		friend bool operator<(const node a,const node b) {
			return a.l<b.l;
		}
	} st[maxn];
	struct edge {
		int next,op,l,r;
	} e[maxn*4];
	int h[maxn],cnt,s1[maxn],s2[maxm],top;
	set<node> s;
	typedef set<node>::iterator iter;
	void add(int x) {
		int b=bel[x];
		for(int i=x; i<=rp[b]; i++)s1[i]++;
		for(int i=b+1; i<=sn; i++)s2[i]++;
	}
	int ask(int x) {
		if(!x)return 0;
		return s1[x]+s2[bel[x]];
	}
	void addedge(int x,int op,int l,int r) {
		e[++cnt]=(edge) {
			h[x],op,l,r
		},h[x]=cnt;
	}
	void ins(int l,int r,int t) {
		st[++top]=node(l,r,t);
	}
	void ers(int l,int r,int t) {
		for(int i=1; i<=top; i++)
			if(st[i].l==l&&st[i].r==r) {
				addedge(r,1,st[i].st,t),addedge(l-1,-1,st[i].st,t);
				for(int j=i; j<top; j++)st[j]=st[j+1];
				top--;
				break;
			}
	}
	void solve1(int L,int R) {
		s.clear(),top=0;
		iter il,ir;
		for(int w=L; w<=R; w++) {
			int op=p[w].op,l=p[w].l,r=p[w].r;
			if(op==1) {
				l=lower_bound(b+1,b+n+1,l)-b,r=upper_bound(b+1,b+n+1,r)-b-1;
				if(l>r)continue;
				if(s.empty())goto shik;
				il=s.lower_bound(node(l,0,0)),ir=s.upper_bound(node(r,0,0));
				if(il!=s.begin()) {
					iter tmp=il;
					tmp--;
					if(tmp->r>=l)il--;
				}
				if(ir==s.begin()||(--ir)->r<l)goto shik;
				l=min(l,il->l),r=max(r,ir->r);
				while(il!=ir)ers(il->l,il->r,w),il=s.erase(il);
				ers(ir->l,ir->r,w),s.erase(ir);
shik:
				ins(l,r,w),s.insert(node(l,r,w));
			}
		}
		for(int i=1; i<=top; i++)addedge(st[i].r,1,st[i].st,R),addedge(st[i].l-1,-1,st[i].st,R),st[i].l=st[i].r=st[i].st=0;
	}
	void solve() {
		for(int u=1; u<=n; u++) {
			add(id[u].sc);
			for(int i=h[u]; i; i=e[i].next) {
				int l=e[i].l,r=e[i].r,o=e[i].op;
				for(int j=l; j<=r; j++)
					if(p[j].op==2)ans[p[j].id]+=o*(ask(p[j].r)-ask(p[j].l-1));
			}
		}
	}
}
namespace sub2 {
	int f[maxn],s1[maxn],s2[maxm];
	int getf(int x) {
		return f[x]==x?x:f[x]=getf(f[x]);
	}
	void add(int x) {
		s1[x]++,s2[bel[x]]++;
	}
	int ask(int l,int r) {
		int x=bel[l],y=bel[r],sum=0;
		if(x==y) {
			for(int i=l; i<=r; i++)sum+=s1[i];
			return sum;
		}
		for(int i=l; i<=rp[x]; i++)sum+=s1[i];
		for(int i=lp[y]; i<=r; i++)sum+=s1[i];
		for(int i=x+1; i<y; i++)sum+=s2[i];
		return sum;
	}
	void solve(int L,int R) {
		for(int i=1; i<=n+1; i++)f[i]=i;
		memset(s1,0,sizeof(s1)),memset(s2,0,sizeof(s2));
		for(int w=L; w<=R; w++) {
			int op=p[w].op,l=p[w].l,r=p[w].r;
			if(op==1) {
				l=lower_bound(b+1,b+n+1,l)-b,r=upper_bound(b+1,b+n+1,r)-b-1;
				int x=getf(l);
				while(x<=r)add(id[x].sc),f[x]=f[x+1],x=getf(x+1);
			} else ans[p[w].id]=ask(l,r);
		}
	}
}
int main() {
	n=read(),q=read(),m=read(),sqrtn=sqrt(n),sn=(n+sqrtn-1)/sqrtn;
	for(int i=1; i<=n; i++)a[i]=read(),id[i]=pi(a[i],i),b[i]=a[i];
	sort(id+1,id+n+1),sort(b+1,b+n+1);
	if(m==1)sub0::solve();
	else {
		for(int i=1; i<=sn; i++)lp[i]=(i-1)*sqrtn+1,rp[i]=min(i*sqrtn,n);
		for(int i=1; i<=n; i++)bel[i]=(i-1)/sqrtn+1;
		for(int i=1; i<=q; i++)op[i]=p[i].op=read(),p[i].l=read(),p[i].r=read(),p[i].k=read(),p[i].id=i;
		sort(p+1,p+q+1);
		for(int l=1,r; l<=q; l=r+1) {
			r=l;
			while(p[r+1].k==p[l].k)r++;
			nowk=p[l].k;
			if(r-l+1>=sqrt(q))sub2::solve(l,r);
			else sub1::solve1(l,r);
		}
		sub1::solve();
		for(int i=1; i<=q; i++)if(op[i]==2)printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：cyffff (赞：7)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8146)
## 题意
给你一个长度为 $n$ 的序列 $a$，有 $q$ 次操作，初始有 $m$ 个空集 $S$，共有两种操作：

- `1 l r k`，$S_k\gets S_k\cup\{x|l\le x\le r\}$；
- `2 l r k`，查询 $\displaystyle\sum_{i=l}^r[a_i\in S_k]$。

数据范围：
- 对于 $30\%$ 的数据，$n,q\le10^6$，$m=1$；
- 对于 $70\%$ 的数据，$n,q\le 3\times 10^5$，$m\le 10^9$。

## 题解
### $\text{Algorithm 1}$
称所有 $a_i\in S$ 的 $i$ 的数 $i$ 为“合法结点”。

考虑算出每次插入操作后每个数是不是合法结点，查询时统计区间的合法结点数的个数即可。

考虑将原序列排序，得到序列 $b$，对于一次插入操作，在 $b$ 上二分找到第一个 $\ge l$ 的数 $L$，最后一个 $\le r$ 的数 $R$，将 $[L,R]$ 中的数的原位置标记为合法结点。考虑使用树状数组，标记合法结点后可以直接查询。

现在遇到了一个问题：一个数可能会被多次标记合法结点，导致复杂度出错。

考虑使用[并查集惰性删除](https://www.luogu.com.cn/discuss/372365)的简单 trick，删除一个数 $i$ 时，将集合 $i$ 合并至集合 $i+1$，对于一个本次新标记的点 $i$，下一个需要标记的点为 $\text{find}(i+1)$。容易发现，这样每个数都不会被重复标记。

由于每个数都只会被标记一次（可以看作势能分析），时间复杂度为 $O((n+q)\log n)$，期望得分 $30\text{pts}$。

有 $m$ 个集合时，时间复杂度实质上是 $O((nm+q)\log n)$。
### $\text{Algorithm 2}$

很显然，$m$ 是不重要的，因为显然可以离散化至 $O(q)$。

令 $m=q=O(n)$。

首先可以发现每个集合的操作是互不影响的，可以分别考虑。

需要进行 $O(n)$ 组以下的操作：
- 将值域中 $[l,r]$ 间的数的权值推平 $1$
- 询问编号 $[l,r]$ 间数的权值和

先用 set 维护颜色段均摊（ODT）将区间推平转为区间加，可以发现转完的操作数是 $O(n)$ 的。

考虑序列分块，每个块维护一个值域上的前缀和，整块打标记很好打，只需要将答案加上 $pre_r-pre_{l-1}$ 即可。考虑散块怎么做，问题即为区间加单点求值，注意到要 $O(1)$ 查询，不能用权值树状数组之流，于是拿个值域分块过来直接做就行了。

于是乎得到了一个时空 $O(n\sqrt n)$ 的算法，但这样你只能得 $30\text{pts}$，因为空间不够优秀。

考虑降空间复杂度至 $O(n)$。考虑 simple trick 离线逐块处理。直接逐块处理散块时复杂度可能会退化为 $O(n^2)$，注意将整块贡献与散块贡献分开计算。整块贡献要先枚举块再枚举集合，散块贡献很 simple。

如果你被卡常，过不了，可以尝试调一个合适的块长。

得到了一个时间 $O(n\sqrt n)$，空间 $O(n)$ 的算法。期望得分 $70\text{pts}$。

将两部分结合起来即可。

代码实现可以找我要。
### $\text{Bonus}$

有根号分治做法，也可以线性空间，具体看 $\texttt{abruce}$ 题解。

跑得比序列分块快多了。

再见 qwq~

---

## 作者：hrgd (赞：7)

提供一个思路直接的其他做法。

首先特判 $m=1$ 此时可以直接用 $\text{set}$ 维护还没有加入的 $a$ 数组内的数，修改直接暴力加入，然后用线段树维护即可。

其他情况 3e5 明示根号。

令 $b$ 为 $a$ 排序的结果。

对于集合大小根号分治：

大集合考虑沿用上面的做法，但是会多一个 $\log$。于是我们将值域分块，散块暴力，整块判断一下是否存在没有加入的数，如果没有就暴力加入所有数，然后线段树改成一个 $O(1)-O(\sqrt n)$ 的分块。

小集合考虑操作只有根号个，所以值域可以分成 $O(\sqrt n)$ 段，每一段的加入时间一定相同，我们先预处理出这些值域段以及在 $b$ 中的区间。加入一个段的时候，我们将 $b$ 序列分块，散块暴力加入（仍然是 $O(1)-O(\sqrt n)$ 的分块），整块打标记，在询问的时候枚举每个整块计算贡献。

但是你会发现计算整块贡献的时候需要 $O(n\sqrt n)$ 空间，我赛时就被卡空间了！！！1

我们可以对于每个值域块，将其在序列中出现位置排序，然后建一个分散层叠，使用分散层叠 $O(\sqrt n+\log n)$ 大力计算询问区间左端点和右端点在每个值域块的后继即可做到线性空间。

代码很丑也很长，就不放了。



---

