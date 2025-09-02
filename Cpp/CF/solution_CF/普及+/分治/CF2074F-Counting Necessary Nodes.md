# Counting Necessary Nodes

## 题目描述

四叉树是一种树形数据结构，其中每个节点最多有四个子节点，每个节点对应一个正方形区域。

形式化地说，对于所有非负整数 $k, a, b \ge 0$ 的元组，存在且仅存在一个节点对应以下区域 $^{\text{∗}}$：

$$[a \cdot 2^k, (a+1) \cdot 2^k] \times [b \cdot 2^k, (b+1) \cdot 2^k]$$

所有区域大小超过 $1 \times 1$ 的节点都包含四个子节点，这些子节点对应将原区域四等分后的四个子区域；而区域为 $1 \times 1$ 的节点对应树的叶节点。

![](https://espresso.codeforces.com/05c9383ea0ee1fdfd6e33aa7d780936c2ac69a4b.png)

图中展示了部分节点对应的区域。颜色较深的区域更接近叶节点。

Frontman 厌恶一个普遍的误解——当区域内包含 $n$ 个叶节点时，四叉树可以在 $\mathcal{O}(\log n)$ 时间内完成范围查询。事实上，有时需要查询远多于 $\mathcal{O}(\log n)$ 个区域，极端情况下时间复杂度甚至为 $\mathcal{O}(n)$。因此，Frontman 设计了此题来教育你关于该数据结构的最坏情况。

粉色士兵们给定了一个有限区域 $[l_1, r_1] \times [l_2, r_2]$，其中 $l_i$ 和 $r_i$（$l_i < r_i$）为非负整数。请找出最少需要选择多少个节点，使得这些节点对应区域的并集**恰好**等于给定区域。这里，两个点集被认为是不同的，当且仅当存在一个点属于其中一个集合但不属于另一个。

$^{\text{∗}}$ 区域是具有实数坐标的点集。点 $(x, y)$ 属于区域 $[p, q] \times [r, s]$ 当且仅当 $p \le x \le q$ 且 $r \le y \le s$。此处 $\times$ 形式上指[集合的笛卡尔积](https://en.wikipedia.org/wiki/Cartesian_product)。

## 说明/提示

第一个测试用例中，给定区域为 $[0, 1] \times [1, 2]$。存在一个节点对应该区域，选择该节点即可，答案为 $1$。

第二个测试用例中，给定区域为 $[0, 2] \times [0, 2]$。存在一个节点对应该区域，选择该节点即可，答案为 $1$。

第三个测试用例中，给定区域为 $[1, 3] \times [1, 3]$。不存在对应该区域的节点。但可以通过选择以下 $4$ 个叶节点构造出相同区域：
- 对应 $[1, 2] \times [1, 2]$ 的叶节点；
- 对应 $[1, 2] \times [2, 3]$ 的叶节点；
- 对应 $[2, 3] \times [1, 2]$ 的叶节点；
- 对应 $[2, 3] \times [2, 3]$ 的叶节点。

可以证明无法用少于 $4$ 个节点构造出该区域，因此答案为 $4$。

第四个测试用例中，给定区域为 $[0, 2] \times [1, 5]$。可以通过选择以下 $5$ 个节点构造出相同区域：
- 对应 $[0, 1] \times [1, 2]$ 的叶节点；
- 对应 $[1, 2] \times [1, 2]$ 的叶节点；
- 对应 $[0, 2] \times [2, 4]$ 的非叶节点；
- 对应 $[0, 1] \times [4, 5]$ 的叶节点；
- 对应 $[1, 2] \times [4, 5]$ 的叶节点。

可以证明无法用少于 $5$ 个节点构造出该区域，因此答案为 $5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
0 1 1 2
0 2 0 2
1 3 1 3
0 2 1 5
9 98 244 353```

### 输出

```
1
1
4
5
374```

# 题解

## 作者：未来姚班zyl (赞：2)

四叉树是骗人的，$x$ 和 $y$ 各自都是线段树的形式，两维提取出来然后暴力算即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,m
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){if(b<0)b+=mod;((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){add(b,mod);return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int l,r,Ll,Rr;
int s[N],tp,S[N],Tp,ty;
inline void query(int x,int l,int r,int Ll,int Rr){
	if(OK)return ty?s[++tp]=r-l+1:S[++Tp]=r-l+1,void();
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	query(lc,Ll,Rr),query(rc,Ll,Rr);
}
inline void Main(){
	l=read(),r=read(),Ll=read(),Rr=read();
	tp=Tp=0;
	ty=0,query(1,0,(1<<20)-1,l,r-1),ty=1,query(1,0,(1<<20)-1,Ll,Rr-1);
	int ans=0;
	rep(i,1,tp)rep(j,1,Tp)ans+=max(s[i],S[j])/min(s[i],S[j]);
	cout <<ans<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}

```

---

