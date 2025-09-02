# William The Oblivious

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609E/0e83a16b376d35306235c93a9bc0616a224b28a1.png)Before becoming a successful trader William got a university degree. During his education an interesting situation happened, after which William started to listen to homework assignments much more attentively. What follows is a formal description of the homework assignment as William heard it:

You are given a string $ s $ of length $ n $ only consisting of characters "a", "b" and "c". There are $ q $ queries of format ( $ pos, c $ ), meaning replacing the element of string $ s $ at position $ pos $ with character $ c $ . After each query you must output the minimal number of characters in the string, which have to be replaced, so that the string doesn't contain string "abc" as a subsequence. A valid replacement of a character is replacing it with "a", "b" or "c".

A string $ x $ is said to be a subsequence of string $ y $ if $ x $ can be obtained from $ y $ by deleting some characters without changing the ordering of the remaining characters.

## 说明/提示

Let's consider the state of the string after each query:

1. $ s =  $ "aaaaccccc". In this case the string does not contain "abc" as a subsequence and no replacements are needed.
2. $ s =  $ "aaabccccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "aaaaccccc". This string does not contain "abc" as a subsequence.
3. $ s =  $ "ababccccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ aaaaccccc". This string does not contain "abc" as a subsequence.
4. $ s =  $ "ababacccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaaaacccc". This string does not contain "abc" as a subsequence.
5. $ s =  $ "bbabacccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "bbacacccc". This string does not contain "abc" as a subsequence.
6. $ s =  $ "bbababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "bbacacccc". This string does not contain "abc" as a subsequence.
7. $ s =  $ "bbabcbccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "bbcbcbccc". This string does not contain "abc" as a subsequence.
8. $ s =  $ "baabcbccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "bbbbcbccc". This string does not contain "abc" as a subsequence.
9. $ s =  $ "aaabcbccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacccccc". This string does not contain "abc" as a subsequence.
10. $ s =  $ "aaababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacacccc". This string does not contain "abc" as a subsequence.
11. $ s =  $ "aaababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacacccc". This string does not contain "abc" as a subsequence.
12. $ s =  $ "aaababbcc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaababbbb". This string does not contain "abc" as a subsequence.

## 样例 #1

### 输入

```
9 12
aaabccccc
4 a
4 b
2 b
5 a
1 b
6 b
5 c
2 a
1 a
5 a
6 b
7 b```

### 输出

```
0
1
2
2
1
2
1
2
2
2
2
2```

# 题解

## 作者：GSH_gsh (赞：24)

### 题意

给你一个长为 $n$ 的字符串，只包含 `abc` 三种字符。$q$ 次操作，每次把一个位置的字符改成给定字符，询问当前串至少修改几次满足不包含子序列 `abc`。修改指把一个位置的字符修改成 `a`、`b`、`c` 三种字符之一。

$1\le n,q\le 10^5$。

### 题解

用线段树维护六个东西：
- 区间 `a`，`b`，`c` 的数量 $a,b,c$
- 区间不存在 `ab`，`bc`，`abc` 最少需要改变几个位置 $ab,bc,abc$

合并：
- $a_k=a_l+a_r$
- $b_k=b_l+b_r$
- $c_k=c_l+c_r$
- $ab_k=\min(a_l+ab_r,ab_l+b_r)$
- $bc_k=\min(b_l+bc_r,bc_l+c_r)$
- $abc_k=\min(abc_l+c_r,ab_l+bc_r,a_l+abc_r)$

每次查询 $abc_{rt}$ 就是答案。

时间复杂度 $O(q\log n)$。

[code](https://codeforces.com/contest/1609/submission/137286126)

---

## 作者：I_am_Accepted (赞：9)

### 题意简述

**注意：以下阐述中“字符”均在字符集 $\sum=\{\mathtt{"a","b","c"}\}$ 之内讨论。**

最初给一个长度为 $n$ 的字符串。

$q$ 次操作，每次先修改单个位置的字符，再询问全局最少要修改几个位置上的字符使得整个序列没有 $\mathtt{"abc"}$ 这个子序列。

### 题目分析

像这种**关于颜色模式子序列（颜色少，模式子序列短）**的题目一般想到**矩阵乘法**（不是一般的乘法，后面会说）。

具体地，用一个线段树维护整个序列，树上每一个节点存一个 $3\times 3$ 的矩阵：

$$\begin{pmatrix}
A&AB&ABC
\\
\infty&B&BC
\\
\infty&\infty&C
\end{pmatrix}$$

其中（下面的括号为断句）：

* $A$ 为使得（该线段树节点管辖的区间内）（没有 $\mathtt{"a"}$ 这个子序列）的（最小修改次数）。

* $AB$ 为使得（该线段树节点管辖的区间内）（没有 $\mathtt{"ab"}$ 这个子序列）的（最小修改次数）。

* $\dots$

* $C$ 为使得（该线段树节点管辖的区间内）（没有 $\mathtt{"c"}$ 这个子序列）的（最小修改次数）。

而且这里的矩阵乘法 $XY=Z$ 定义为：

$$z_{i,j}=\min\limits_{k=1}^{3}(x_{i,k}+y_{k,j})$$

发现她满足结合律（证明留给读者）。

对于一个线段树上的节点来说，设她的矩阵为 $F$，她的两个儿子的矩阵分别为 $L,R$，则：

$$F=LR$$

那我们就可以开开心心线段树合并了。

实时答案为线段树树根矩阵 $(1,3)$ 的值（即 $ABC$）。

时间复杂度：

* 单次修改 $O(|\sum|^3\log n)$

* 单次询问 $O(1)$

总共 $O(q|\sum|^3\log n)$。

### Details

我的矩阵用 `struct` 存储，每一维从 $0$ 开始标号。

### Code

[Link](https://codeforces.com/contest/1609/submission/137346877)

---

## 作者：DaiRuiChen007 (赞：6)

# CF1609E - William the Oblivious 题解

## 题目大意

给定一个长度为 $n$ 的字符串 $S$ ，且只包含 `a`，`b`，`c` 三种字符。

进行 $q$ 次操作，每一次将其中某一个位置上的字符修改为 `a`，`b`，`c` 之一，对于每次修改操作，求出至少要改变多少个字符才能使得得到的新字符串中不包含**子序列** `abc`。

数据范围保证：$n,q\le10^5$。

## 思路分析

考虑套单修区查线段树模板（这题甚至不需要区查）。

问题是如何进行 Push_Up 操作。

用对于某个节点，用 $a$，$b$，$c$，$ab$，$bc$，$abc$ 分别表示让这个区间不包含子序列 `a`，`b`，`c`，`ab`，`bc`，`abc` 至少需要改变多少个字符。

约定用 $L$ 表示当前节点的左儿子， $R$ 当前节点的表示右儿子，$N$ 表示当前节点。

注意到 $a$，$b$，$c$ 的值等价于区间内的 `a`，`b`，`c` 字符的数量，所以可以直接写出 Push_Up （就是区间和）。
$$
\begin{cases}
N_a=L_a+R_a\\
N_b=L_b+R_b\\
N_c=L_c+R_c
\end{cases}
$$
接下来考虑 $ab$ 和 $bc$ 的 Push_Up。

以 $ab$ 为例。

要让整个区间中没有子序列 `ab`，可以从 `a` 的位置和 `b` 的位置分别讨论，一共有三种情况。

1. `a`，`b` 都在左区间内。
2. `a` 在左区间内，`b` 在右区间内。
3. `a`，`b` 都在右区间内。

从第二种情况入手，如果不存在第二类的子序列 `ab`，只有两种可能：左区间没有 `a` 或右区间没有 `b`。

1. 如果左区间没有 `a`，那么自然也不存在第一类子序列 `ab`，只需要使右区间没有 `ab` 即可。
2. 如果右区间没有 `b`，那么自然也不存在第三类子序列 `ab`，只需要使左区间没有 `ab` 即可。

那么这两种情况的最小代价分别是 $L.a+R.ab$ 和 $L.ab+R.b$，由于要求的是最小代价，所以在这两者中取个最小值即可。

如此类比 $bc$ 的 Push_Up 也是一样的，可以得到这两个值的 Push_Up 公式
$$。
\begin{cases}
N.ab=\min(L.a+R.ab,L.ab+R.b)\\
N.bc=\min(L.b+R.bc,L.bc+R.c)
\end{cases}
$$
接下来在考虑 $abc$ 是如何 Push_Up 的。

类似 $ab$ 的分析，我们将子序列 `abc` 的构成也拆成左右两部分，共四种情况。

1. `abc` 都在左区间内。
2. `ab` 在左区间内，`c` 在右区间内。
3. `a` 在左区间内，`bc` 在右区间内。
4. `abc` 都在右区间内。

继续类比 $ab$ 的分析，以第二、三类子序列 `abc` 为切入点进行分析，得到两种可能的情况，分别是。

1. 左区间没有 `a`，此时第一、二、三类子序列 `abc` 肯定全部都没有，那么只需要保证右区间没有 `abc` 即可。
2. 右区间没有 `c`，此时第二、三、四类子序列 `abc` 肯定全部都没有，那么只需要保证左区间没有 `abc` 即可。

这两种情况的分别最小贡献分别是 $L.a+R.abc$ 和 $L.abc+R.c$ 。

不过和 $ab$ 不同的是，`abc` 这个子序列可以左区间有 `a`，右区间有 `c`。

这个时候，还是以第二、三类子序列 `abc` 入手，简单地合并一下，得到：

想要使区间内没有第二或第三类子序列 `abc`，需要满足的条件就是左区间的 `a` 和右区间的 `c` 中间再没有字符 `b` 了。

我们把这个条件再拆开来~~（怎么那么多事呢）~~，得到了两个条件：

1. 左区间内没有子序列 `ab`。
2. 右区间内没有子序列 `bc`。

所以这种情况的代价就是 $L.ab+R.bc$。

综上，我们得到了 $abc$ 的三种转移方式，取最小值就得到了 $abc$ 的 Push_Up 公式：
$$
N.abc=\min(L.a+R.abc,L.abc+R.c,L.ab+R.bc)
$$
最后总结一下，把六个值的 Push_Up 公式整合起来，再翻译成代码，就得到了这道题目线段树建树的核心——PushUp 函数。

```cpp
inline void PushUp(int pos) {
//tree[]是线段树,left(pos)表示左儿子,right(pos)表示右儿子
tree[pos].a=tree[left(pos)].a+tree[right(pos)].a;
tree[pos].b=tree[left(pos)].b+tree[right(pos)].b;
tree[pos].c=tree[left(pos)].c+tree[right(pos)].c;
tree[pos].ab=min(tree[left(pos)].ab+tree[right(pos)].b,tree[left(pos)].a+tree[right(pos)].ab);
tree[pos].bc=min(tree[left(pos)].bc+tree[right(pos)].c,tree[left(pos)].b+tree[right(pos)].bc);
tree[pos].abc=min(tree[left(pos)].ab+tree[right(pos)].bc,
                  min(tree[left(pos)].a+tree[right(pos)].abc,tree[left(pos)].abc+tree[right(pos)].c));
}
```

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1;
char s[MAXN];
class SegementTree {
    //线段树模板
	private:
		struct node {
			int a,b,c,ab,bc,abc;
		}	tree[MAXN<<2];
		inline int left(int x) {
			return x<<1;
		}
		inline int right(int x) {
			return x<<1|1;
		}
		inline void PushUp(int pos) {
			tree[pos].a=tree[left(pos)].a+tree[right(pos)].a;
			tree[pos].b=tree[left(pos)].b+tree[right(pos)].b;
			tree[pos].c=tree[left(pos)].c+tree[right(pos)].c;			tree[pos].ab=min(tree[left(pos)].ab+tree[right(pos)].b,tree[left(pos)].a+tree[right(pos)].ab);
tree[pos].bc=min(tree[left(pos)].bc+tree[right(pos)].c,tree[left(pos)].b+tree[right(pos)].bc);
tree[pos].abc=min(tree[left(pos)].ab+tree[right(pos)].bc,                     min(tree[left(pos)].a+tree[right(pos)].abc,tree[left(pos)].abc+tree[right(pos)].c));
		}
	public:
		inline void Build(int l,int r,int pos) {
			if(l==r) {
				switch(s[l]) {
					case 'a': ++tree[pos].a; break;
					case 'b': ++tree[pos].b; break;
					case 'c': ++tree[pos].c; break;
				}
				return ;
			}
			int mid=(l+r)>>1;
			Build(l,mid,left(pos));
			Build(mid+1,r,right(pos));
			PushUp(pos);
			return ;
		}
		inline void Modify(int u,int l,int r,int pos,char ch) {
			if(l==r) {
				tree[pos].a=tree[pos].b=tree[pos].c=0;
				s[l]=ch;
				switch(s[l]) {
					case 'a': ++tree[pos].a; break;
					case 'b': ++tree[pos].b; break;
					case 'c': ++tree[pos].c; break;
				}
				return ;
			}
			int mid=(l+r)>>1;
			if(u<=mid) Modify(u,l,mid,left(pos),ch);
			else Modify(u,mid+1,r,right(pos),ch);
			PushUp(pos);
			return ;
		}
		inline int Query() {
             //整段区间的答案
			return tree[1].abc;
		}
}	S;
signed main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,q;
	cin>>n>>q>>(s+1);
	S.Build(1,n,1);
	while(q--) {
		int v;
		char ch;
		cin>>v>>ch;
		S.Modify(v,1,n,1,ch);
		cout<<S.Query()<<'\n';
	}
	return 0;
}
```



---

## 作者：StillEmpty (赞：3)

评分虚高。很多类似的dp都只有黄，放到线段树上就紫了吗（

做法显然线段树。

这题的难点显然在维护个啥、怎么合并信息。我们一步步分析。

我们要求的：根节点无 `abc` 需要删几个，我们称这个数为 `nabc`。（以下 `nab` 等同理）

所以显然，我们需要知道一种方法，**让一个节点的 `nabc` 可以由两个子节点的什么变量算出来。** 

我们很容易想到分类讨论。

1. 左子节点没有 `a`：`ls.cnta + rs.nabc`（`cnta` 表示 `a` 的数量，以下同理），显然
2. 左子节点可以有 `a` 但是没有子序列 `ab`：`ls.nab + rs.nbc`。你可能会问，可能 `ls.nab` 的构造方案没有 `a` 。但没关系，如果 `ls.nab` 的构造方案没有 `a`，**说明 `ls.nab + rs.nbc` 就不是使 `nabc` 最小的构造方案。**![1](https://cdn.luogu.com.cn/upload/image_hosting/ui3kgl2p.png)可以形象理解一下，图中 $[1,40]$ 是不同的方案，我们要找到其中代价最小的，而每个圈都可以找到圈中代价最小的。那么最终代价最小的就是各圈的最小代价。也就是说，一个决策方案被覆盖多边是可以的。
3. 左子节点可以有子序列 `ab`，但是不允许有子序列 `abc`：`ls.nabc + rs.cntc`，理由同上。

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef const int& cint;

const int N = 1e5;
int n, q;
char str[N+1];
struct node {
	int l, r, a, b, c, ab, bc, abc;
} t[N*4+1];
inline int ls(cint o) {return o<<1;}
inline int rs(cint o) {return (o<<1)|1;}

inline void pushup(cint odx) {
	node &o = t[odx], &l = t[ls(odx)], &r = t[rs(odx)];
	o.a = l.a+r.a; o.b = l.b+r.b; o.c = l.c+r.c;
	o.ab = min(l.a+r.ab, l.ab+r.b);
	o.bc = min(l.b+r.bc, l.bc+r.c);
	o.abc = min(min(l.abc+r.c, l.a+r.abc), l.ab+r.bc);
}
void build(cint o, cint l, cint r) {
	t[o].l = l; t[o].r = r;
	if(l == r) {
		if(str[l] == 'a') {
			++t[o].a;
		}
		else if(str[l] == 'b') ++t[o].b;
		else ++t[o].c;
		return;
	}
	int mid = l+r>>1;
	build(ls(o), l, mid); build(rs(o), mid+1, r);
	pushup(o);
}
void modify(cint o, cint p) {
	if(t[o].l == t[o].r) {
		t[o].a = t[o].b = t[o].c = 0;
		if(str[t[o].l] == 'a') {
			t[o].a = 1;
		}
		else if(str[t[o].l] == 'b') t[o].b = 1;
		else t[o].c = 1;
		return;
	}
	int mid = t[o].l+t[o].r>>1;
	if(p <= mid) modify(ls(o), p);
	else modify(rs(o), p);
	pushup(o);
}

int main() {
	scanf("%d%d%s", &n, &q, str+1);
	build(1, 1, n);
	while(q--) {
		int p; char ch; scanf("%d %c", &p, &ch);
		str[p] = ch; modify(1, p);
		printf("%d\n", t[1].abc);
	}
	return 0;
}
```

---

## 作者：Yahbim (赞：2)

### 题意

给你一个长为 $n$ 的字符串，只包含 $a,b,c$ 三种字符。$q$ 次操作，每次把一个位置的字符改成给定字符，询问当前串至少修改几次满足不包含子序列 $abc$。修改指把一个位置的字符修改成 $a,b,c$ 三种字符之一。

$1\le n,q\le 10^5$。

### 题解

线段树维护。

维护六个信息：

`a`,`b`,`c`,`ab`,`bc`,`abc`。

皆表示使区间内没有子序列等于该字符（串）的最小操作次数。

首先，`abc` 恒小于等于 `ab` 恒小于等于 `a`，以此类推。所以可以用 `abc` 达到合法就尽量用 `abc`。

若想使合并后不存在 $abc$，需要满足三个要求：左儿子无 $abc$（记为条件 1），右儿子无 $abc$（记为条件 2），左右儿子合并后不产生 $abc$（记为条件 3）。

重点考虑区间合并时两个区间互相的影响。

如果合并后产生了 $abc$，那它有一些特征：$a$ 在左儿子，$c$ 在右儿子，$b$ 的话左右都有可能。

考虑一种操作方案：把左儿子的 $a$ 全部删掉。显然这样可以使条件 1 和条件 3 得到满足。若使条件 2 也得到满足，只需保证右儿子内部无 $abc$ 即可。此种方案的费用为 $a_{ls}+abc_{rs}$。

如果此种方案不为最优方案，那么最优方案中左儿子至少保留了一个 $a$。再考虑把右儿子的 $c$ 全部删掉。同理，此种方案的费用为 $abc_{ls}+c_{rs}$。

如果还没有找到最优方案，那么最优方案中，左儿子至少保留了一个 $a$，同时右儿子也至少保留了一个 $c$。那么此时某一个方案合法的充要条件为：左儿子不构成任何一组 $ab$，右儿子不构成任何一组 $bc$。于是此时最优方案的费用就是 $ab_{ls}+bc_{rs}$。

综上，所有情况下最优方案的费用为 $\text{min}\{a_{ls}+abc_{rs},abc_{ls}+c_{rs},ab_{ls}+bc_{rs}\}$。 

线段树维护即可。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

namespace IO{
    int read(){
		int ret=0;char ch=getchar();
        while(!isdigit(ch)) ch=getchar();
        while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
        return ret;
    }
    void abswrite(int x){if(x>9) abswrite(x/10);putchar(x%10+'0');}
    void write(int x){abswrite(x),putchar('\n');}
}using IO::read;using IO::write;

int n,q;char ch[N];

namespace segment_tree{
    #define ls (u<<1)
    #define rs (u<<1|1)
    int a[N<<2],b[N<<2],c[N<<2],ab[N<<2],bc[N<<2],abc[N<<2],st;
    void pushup(int u){
        a[u]=a[ls]+a[rs],b[u]=b[ls]+b[rs],c[u]=c[ls]+c[rs];
        ab[u]=min(a[ls]+ab[rs],ab[ls]+b[rs]);
        bc[u]=min(b[ls]+bc[rs],bc[ls]+c[rs]);
        abc[u]=min(min(a[ls]+abc[rs],abc[ls]+c[rs]),ab[ls]+bc[rs]);
    }
    void build(){
        st=pow(2,(int)ceil(log2(n+2)));
        for(int i=1,u=st+1;i<=n;++i,++u)
            ch[i]=='a'?a[u]=1:ch[i]=='b'?b[u]=1:c[u]=1;
        for(int u=st-1;u;--u) pushup(u);
    }
    void modify(int p){
        a[st+p]=b[st+p]=c[st+p]=0,ch[p]=='a'?a[st+p]=1:ch[p]=='b'?b[st+p]=1:c[st+p]=1;
        for(int u=(st+p)>>1;u;u>>=1) pushup(u);
    }
    int query(){return abc[1];}
    #undef ls
    #undef rs
}namespace tr=segment_tree;   

signed main(){
    n=read(),q=read();
    for(int i=1;i<=n;++i)
		while(!islower(ch[i])) ch[i]=getchar();
    tr::build();
    for(int i=1;i<=q;++i){
        int p=read();ch[p]=getchar();
        tr::modify(p),write(tr::query());
    }
    return 0;
}

//~kawaii~
```



---

## 作者：添哥 (赞：1)

单点修改+区间查询，容易想到万能的线段树。

~~种~~六棵线段树，令 $tree_{1...6}$ 分别等于：

- 让这个区间不包含子序列 a 至少需要改变多少个字符。
- 让这个区间不包含子序列 b 至少需要改变多少个字符。
- 让这个区间不包含子序列 c 至少需要改变多少个字符。
- 让这个区间不包含子序列 ab 至少需要改变多少个字符。
- 让这个区间不包含子序列 bc 至少需要改变多少个字符。
- 让这个区间不包含子序列 abc 至少需要改变多少个字符。

$P.S.$ 其实 $tree_{1...3}$ 等价于区间中 a,b,c 的数量。

$pushup$ 函数：

- $tree_{rt_1}=tree_{l_1}+tree_{r_1}$
- $tree_{rt_2}=tree_{l_2}+tree_{r_2}$
- $tree_{rt_3}=tree_{l_3}+tree_{r_3}$
- $tree_{rt_4}=min(tree_{l_1}+tree_{r_4},tree_{l_4}+tree_{r_2})$
- $tree_{rt_5}=min(tree_{l_2}+tree_{r_5},tree_{l_5}+tree_{r_3})$
- $tree_{rt_6}=min(tree_{l_1}+tree_{r_6},tree_{l_4}+tree_{r_5},tree_{l_6}+tree_{r_3})$

## CODE:
```cpp
#include<iostream>
using namespace std;
long long tree[400005][7];//四倍空间
char a[100005];
void push_up(int i)
{
    tree[i][1]=tree[i*2][1]+tree[i*2+1][1];
    tree[i][2]=tree[i*2][2]+tree[i*2+1][2];
    tree[i][3]=tree[i*2][3]+tree[i*2+1][3];
    tree[i][4]=min(tree[i*2][1]+tree[i*2+1][4],tree[i*2][4]+tree[i*2+1][2]);
    tree[i][5]=min(tree[i*2][2]+tree[i*2+1][5],tree[i*2][5]+tree[i*2+1][3]);
    tree[i][6]=min(tree[i*2][6]+tree[i*2+1][3],min(tree[i*2][4]+tree[i*2+1][5],tree[i*2][1]+tree[i*2+1][6]));
}
void build(int l,int r,int i)//建树
{
    if(l==r)
    {
        tree[i][(int)(a[l-1]-'a'+1)]=1;
    }
    else
    {
        int mid=(l+r)/2;
        build(l,mid,i*2);
        build(mid+1,r,i*2+1);
        push_up(i);
    }
}
void set(int l,int r,int k,int i,char s)//单点修改
{
    if(k<l||r<k)
    {
        return;
    }
    else if(l!=r)
    {
        int mid=(l+r)/2;
        set(l,mid,k,i*2,s);
        set(mid+1,r,k,i*2+1,s);
        push_up(i);
    }
    else
    {
        tree[i][1]=0;
        tree[i][2]=0;
        tree[i][3]=0;
        tree[i][(int)(s-'a'+1)]=1;
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    cin>>a;
    build(1,n,1);
    while(m--)
    {
        int x;
        char ch;
        cin>>x>>ch;
        set(1,n,x,1,ch);
        cout<<tree[1][6]<<endl;//反正都知道是1~n的区间，懒的再写函数了
    } 
    return 0;
}
```
复杂度 $O(qlogn)$ ，自带大常数，但跑3000ms还是绰绰有余滴qwq。

---

## 作者：zztqwq (赞：1)

提供一个比较蠢但是比较好想的做法（

考虑单组询问怎么做。设 $f(i,0/1/2)$ 表示前 $i$ 个字符当前 无 $\texttt{a}$ / 有 $\texttt{a}$ 无 $\texttt{ab}$ / 有 $\texttt{ab}$ 无 $\texttt{abc}$ 的最少修改次数，有转移：
$$
\begin{aligned}f(i,0)&=f(i-1,0)+[s_i=\texttt{a}]\\f(i,1)&=\min\{f(i-1,0)+[s_i\not=\texttt{a}],f(i-1,1)+[s_i=\texttt{b}]\}\\f(i,2)&=\min\{f(i-1,1)+[s_i\not=\texttt{b}],f(i-1,2)+[s_i=\texttt{c}]\}\end{aligned}
$$
这是一个 min+ 矩阵乘法的形式，即向量 $\left[\begin{matrix}f(i-1,0) & f(i-1,1) & f(i-1,2)\end{matrix}\right]$ 乘上一个：
$$
\left[\begin{matrix}[s_i=\texttt{a}] & [s_i\not= \texttt{a}] & +\infty\\+\infty  & [s_i=\texttt{b}] & [s_i\not=\texttt{b}]\\+\infty & +\infty & [s_i=\texttt{c}]\end{matrix}\right]
$$
那么修改就相当于是改一个矩阵，查询就是查矩阵连乘起来之后 $f(n,0/1/2)$ 三个值的最小值，线段树维护矩阵乘积即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
void write(int n)
{
	if(n<0){putchar('-');n=-n;}
	if(n>9)write(n/10);
	putchar(n%10^48);
}
const int inf=0x3f3f3f3f,N=1e5+10;
struct mat{
	int a[3][3];
	mat(){for(int i=0;i<3;i++)for(int j=0;j<3;j++)a[i][j]=inf;}
	void init(){for(int i=0;i<3;i++)a[i][i]=0;}
	mat operator*(const mat &x)const
	{
		mat ans;
		for(int k=0;k<3;k++)for(int i=0;i<3;i++)for(int j=0;j<3;j++)
		ans.a[i][j]=min(ans.a[i][j],a[i][k]+x.a[k][j]);
		return ans;
	}
}x[3];
char s[N];
struct sgt{
	mat t[N<<2];
	void build(int p,int l,int r)
	{
		if(l==r)return t[p]=x[s[l]-'a'],void();
		int mid=(l+r)>>1;
		build(p*2,l,mid),build(p*2+1,mid+1,r);
		t[p]=t[p*2]*t[p*2+1]; 
	}
	void modify(int p,int l,int r,int qx,int d)
	{
		if(l==r)return t[p]=x[d],void();
		int mid=(l+r)>>1;
		if(qx<=mid)modify(p*2,l,mid,qx,d);
		else modify(p*2+1,mid+1,r,qx,d);
		t[p]=t[p*2]*t[p*2+1];
	}
	mat query(int p,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)return t[p];
		int mid=(l+r)>>1;mat ans;ans.init();
		if(ql<=mid)ans=ans*query(p*2,l,mid,ql,qr);
		if(qr>mid)ans=ans*query(p*2+1,mid+1,r,ql,qr);
		return ans;
	}
}T;
int main()
{
	for(int t=0;t<3;t++)
	{
		x[t].a[0][0]=(t==0);
		x[t].a[0][1]=(t!=0);
		x[t].a[1][1]=(t==1);
		x[t].a[1][2]=(t!=1);
		x[t].a[2][2]=(t==2);
	}
	int n=read(),q=read();
	scanf("%s",s+1);
	T.build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int x=read();char ss[5];scanf("%s",ss);
		T.modify(1,1,n,x,ss[0]-'a');
		mat ans=T.query(1,1,n,1,n);
		printf("%d\n",min(min(ans.a[0][0],ans.a[0][1]),ans.a[0][2]));
	}
	return 0;
}
//zzt qwq
```



---

## 作者：Yansuan_HCl (赞：0)

**23.1.7 fix typo.**

不带修可以显然 dp：设 $f[i][0/1/2]$ 分别表示字符串中不含 `a`、含 `a` 无 `b`、含 `ab` 无 `c` 所需的最小操作次数，则有：

$$\begin{aligned}f[i][0]&=f[i-1][0]+[s_i=a]\\f[i][1] &= \min\{f[i-1][1]+[s_i=b], f[i-1][0]+[s_i \neq a]\} \\ f[i][2] &= \min\{f[i-1][2]+[s_i=c], f[i-1][1] + [s_i \neq b]\} \end{aligned}$$

注意本题的操作是修改而非删除。

发现 $f$ 的值只和 $f[i-1]$ 有关。若带上修改，则可以考虑动态 dp. 把转移方程写成矩阵：

$$\left[\begin{matrix}

[s_i=a] & [s_i \neq a] & \infty \\
\infty &[s_i=b] & [s_i \neq b] \\
\infty & \infty & [s_i=c]

\end{matrix}\right]$$

则最终的答案就是 $\left[ \begin{matrix} 1 & \infty &\infty \end{matrix} \right]$ 左乘（此处定义为广义矩阵乘法）以所有转移矩阵，可以用线段树维护单点改整体查。

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il inline
#define pii pair<int, int>
#define pil pair<int, long long>
#define pll pair<long long, long long>
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
// typedef __int128_t i128;
// typedef __uint128_t u128;
template <typename T>
using BS = basic_string<T>;

template <typename T>
il int rd(T& s) {
	int c = getchar();
    // if (c == EOF) return -1;
	T f = 1; s = 0;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
        c = getchar();
		// if (c == EOF) return -1;
	}
	while (c >= '0' && c <= '9') {
		s = (s << 1) + (s << 3) + (c ^ 48);
		c = getchar();
	}
	s *= f;
    return 0;
}
template <typename T, typename... Args>
il int rd(T& x1, Args&... args) { return rd(x1) || rd(args...); }
template <typename T>
il void pr(T s, bool fg = true) {
    if (s < 0) { printf("-"); s = -s; }
    if (!s) {
        if (fg) printf("0");
        return;
    }
    pr(s / 10, false);
    printf("%d", (signed)(s % 10));
}
template <typename... Args>
il int meow(const char* fmt, const Args&... args)
	{ return fprintf(stderr, fmt, args...); }

const int N = 100005;
template <int N, int M>
struct Matrix {
	int m[N][M];
	Matrix() { memset(m, 0x3f, sizeof(m)); }
	int* operator[](int x) { return m[x - 1] - 1; }
};
template <int N, int K, int M>
Matrix<N, M> operator * (Matrix<N, K>& l, Matrix<K, M>& r) {
	Matrix<N, M> m;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			for (int k = 1; k <= K; ++k)
				m[i][j] = min(m[i][j], (l[i][k] + r[k][j]));
	return m;
}

Matrix<3, 3> tr[N << 2];
#define mid ((l + r) >> 1)
#define LS (p << 1)
#define RS ((p << 1) | 1)
int n, q;
void update(int x, Matrix<3, 3>& v, int p = 1, int l = 1, int r = n) {
	if (l == r) { tr[p] = v; return; }
	if (x <= mid) update(x, v, LS, l, mid);
	else update(x, v, RS, mid + 1, r);
	tr[p] = tr[LS] * tr[RS];
}

Matrix<3, 3> gen(char ch) {
	Matrix<3, 3> ts;
	ts[1][1] = ch == 'a';
	ts[1][2] = ch != 'a';
	ts[2][2] = ch == 'b';
	ts[2][3] = ch != 'b';
	ts[3][3] = ch == 'c';
	return ts;
}

int main() {
	rd(n, q);
	char s[N]; scanf("%s", s + 1);
	U (i, 1, n) {
		Matrix<3, 3> trs = gen(s[i]);
		update(i, trs);
	}
	while (q--) {
		int x; char c; scanf("%d %c", &x, &c);
		Matrix<3, 3> trs = gen(c);
		update(x, trs);
		Matrix<1, 3> ans; ans[1][1] = 0;
		ans = ans * tr[1];
		printf("%d\n", min(ans[1][1], min(ans[1][2], ans[1][3])));
	}
	return 0;
}
```

---

