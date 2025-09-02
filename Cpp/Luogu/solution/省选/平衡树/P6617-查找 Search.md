# 查找 Search

## 题目背景

>   也许，同学间最好的结局就是朋友吧。

$\mu ry$ 是一个可爱的女孩子。

在她所住的小区里有排成一排的 $n$ 个垃圾桶，从左至右第 $i$ 个垃圾桶里都装着编号为 $a_i$ 的垃圾。

$\mu ry$ 不喜欢无序，于是就想把社区里编号和为 $w$ 的垃圾都清在一起。

但是调皮的 $\text{LeverImmy}$ 可能会把某个垃圾桶里的垃圾偷换成另一种。

生气的 $\mu ry$ 想考考 $\text{LeverImmy}$ 一个区间 $[l, r]$ 内是否存在编号和为 $w$ 的垃圾。

但 $\text{LeverImmy}$ 也不会解决这个问题，于是他找到了聪明的你。


## 题目描述

给定 $n$ 个垃圾桶，你需要维护一个数据结构，支持以下操作：

-   `1 pos val` 表示将 第 $pos$ 个垃圾桶里的垃圾的编号换成 $val$；

-   `2 l r` 询问在 $[l\oplus cnt, r\oplus cnt]$ 内是否存在垃圾编号和为 $w$ 的 **两个** 垃圾桶。

其中 $\oplus$ 表示异或运算，$cnt$ 表示在 **此次询问之前**，答案为 `Yes` 的个数。

对于每个操作 2，若存在请输出 `Yes`，不存在请输出 `No`。

值得注意的是，对于所有询问， $w$ 为 **同一个数**。


## 说明/提示

本题采用 **捆绑测试**，开启 **O2优化**。

$\text{Subtask 1 (7 pts)}:$ 保证 $1 \le n, m, w \le 2\cdot10^3$，**时限 $1\text{s}$**；

$\text{Subtask 2 (20 pts)}:$ 保证 $1 \le n, m, w \le 1\cdot10^5$，$opt = 2$，**时限 $2\text{s}$**；

$\text{Subtask 3 (30 pts)}:$ 保证 $1 \le n, m, w \le 1\cdot10^5$，**时限 $2\text{s}$**；

$\text{Subtask 4 (43 pts)}:$ 没有特殊限制，**时限 $4\text{s}$**；

对于所有数据， $1 \le n, m, w \le 5\cdot10^5$，$0 \le a_i \le w$。

数据保证对于每个操作，$1 \le pos \le n$，$0 \le val \le w$，$1 \le l \le r \le n$。

由于输入输出量较大，建议使用更快的输入输出方式。

---

#### 输入 #1 解释

第一次操作，询问区间 $[1, 4]$ 中是否有两个数加起来为 $6$，显然有$a_1 + a_4 = 6$，因此输出 `Yes`；

第二次操作，修改 $a_4$ 为 $1$，则序列变为 $[1, 3, 2, 1, 5, 6]$；

第三次操作，询问区间 $[1, 4]$ 中是否有 **两个** 数加起来为 $6$，无，因此输出 `No`。

第四次操作，询问区间 $[2, 6]$ 中是否有两个数加起来为 $6$，显然有 $a_4 + a_5 = 6$，因此输出 `Yes`。


## 样例 #1

### 输入

```
6 4 6
1 3 2 5 5 6
2 1 4
1 4 1
2 0 5
2 3 7```

### 输出

```
Yes
No
Yes```

## 样例 #2

### 输入

```
10 20 10
9 3 6 3 3 3 3 1 4 9
1 3 9
1 6 9
2 3 10
1 3 9
2 4 4
1 1 7
1 1 3
1 5 6
1 3 9
2 4 7
1 2 7
2 6 8
1 6 10
2 2 9
1 7 9
2 3 1
1 3 5
1 5 6
1 9 10
1 3 6```

### 输出

```
Yes
No
No
No
Yes
Yes
```

# 题解

## 作者：FZzzz (赞：25)

比较显然地：定义一个位置的前驱为这个位置之前第一个与这个位置加起来等于 $w$ 的位置，没有则为 $0$，则答案为区间内所有数前驱的最大值是否大于等于 $l$。

然后发现这样的话修改就炸了，因为有很多数的前驱会改变。

然后有一个比较巧妙的转化，就是如果一个数的前驱比它前面第一个与他相同的位置要小，则我们直接把这个位置的前驱设为零。可以发现这样是对的。

这个大概是我赛时的思路，然后我就极其 naive 地以为这样也没法直接修改……

事实上可以直接修改。发现新定义的前驱会改变的位置最多只有五个：这个位置，这个位置原来后面第一个与他相同的位置，这个位置原来后面第一个与他相加得 $w$ 的位置，这个位置后来后面第一个与他相同的位置，这个位置后来后面第一个与他相加得 $w$ 的位置。

直接用 `set` 维护每个值出现的位置，然后在线段树上修改即可。
```cpp
#include<algorithm>
#include<set>
#include<vector>
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
const int maxn=5e5+5;
int n,m,w,a[maxn];
set<int> s[maxn];
typedef set<int>::iterator iter;
struct node{
	int l,r;
	node* ch[2];
	int mx;
	void pushup(){
		mx=max(ch[0]->mx,ch[1]->mx);
	}
	node(int l,int r):l(l),r(r),mx(0){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
			pushup();
		}
	}
	void modify(int x,int k){
		if(l==r) mx=k;
		else{
			if(x<=ch[0]->r) ch[0]->modify(x,k);
			else ch[1]->modify(x,k);
			pushup();
		}
	}
	int query(int ql,int qr){
		if(ql<=l&&qr>=r) return mx;
		else{
			int ans=0;
			if(ql<=ch[0]->r) ans=max(ans,ch[0]->query(ql,qr));
			if(qr>=ch[1]->l) ans=max(ans,ch[1]->query(ql,qr));
			return ans;
		}
	}
}*rt;
int pre(int x){
	iter it1=s[a[x]].lower_bound(x),it2=s[w-a[x]].lower_bound(x);
	if(it2==s[w-a[x]].begin()) return 0;
	else if(it1==s[a[x]].begin()) return *--it2;
	else if(*--it1>*--it2) return 0;
	else return *it2;
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	w=readint();
	for(int i=1;i<=n;i++) a[i]=readint();
	rt=new node(1,n);
	for(int i=1;i<=n;i++){
		rt->modify(i,pre(i));
		s[a[i]].insert(i);
	}
	int cnt=0;
	while(m--){
		int op=readint();
		if(op==1){
			int x,k;
			x=readint();
			k=readint();
			vector<int> res;
			iter it=s[a[x]].upper_bound(x);
			if(it!=s[a[x]].end()) res.push_back(*it);
			it=s[w-a[x]].upper_bound(x);
			if(it!=s[w-a[x]].end()) res.push_back(*it);
			s[a[x]].erase(x);
			s[a[x]=k].insert(x);
			res.push_back(x);
			it=s[a[x]].upper_bound(x);
			if(it!=s[a[x]].end()) res.push_back(*it);
			it=s[w-a[x]].upper_bound(x);
			if(it!=s[w-a[x]].end()) res.push_back(*it);
			for(int i=0;i<(int)res.size();i++) rt->modify(res[i],pre(res[i]));
		}
		else{
			int l,r;
			l=readint()^cnt;
			r=readint()^cnt;
			if(rt->query(l,r)>=l){
				cnt++;
				printf("Yes\n");
			}
			else printf("No\n");
		}
	}
	return 0;
}
```

---

## 作者：zhylj (赞：14)

**题解**

考虑记最小的满足 $j>i$ 且 $a_i + a_j = w$ 的 $j$ 为 $\operatorname{nxt}_i$，则询问的条件等价于：

$$
\min_{i=l}^r \operatorname{nxt}_i \le r
$$

并且，由于必有 $\operatorname{nxt}_i > i$，所以对于 $i > r$ 恒有 $\operatorname{nxt}_i > r$ 成立，故条件等价于：

$$
\min_{i=l}^n \operatorname{nxt}_i \le r
$$

可以发现这等价于取后缀最小值，所以对于 $\operatorname{nxt}_i$ 相同的所有 $i$，我们只需要统计最大的 $i$ 的 $\operatorname{nxt}_i$ 即可。这样我们修改一个点就只影响了常数个位置的 $\operatorname{nxt}_i$。用线段树维护后缀最小值、``std::set`` 维护前驱后继的查询即可做到 $\mathcal O(n\log n)$ 的时间复杂度。

一个小 Trick 是可以把 $v$ 和 $w-v$ 维护在同一个 ``std::set`` 里面，然后影响的仍然只会是前驱后继。

**代码**

```cpp
const int kN = 5e5 + 5, kInf = 0x3f3f3f3f;

int n, m, w, a[kN], nxt[kN];
std::set <int> S[kN];

int seg[kN << 3];
void Update(int o) { seg[o] = std::min(seg[o << 1], seg[o << 1 | 1]); }
void Build(int o, int l, int r) {
	if(l < r) {
		int mid = (l + r) >> 1;
		Build(o << 1, l, mid);
		Build(o << 1 | 1, mid + 1, r);
		Update(o);
	} else seg[o] = nxt[l];
}
int Query(int o, int l, int r, int p) {
	if(p <= l) return seg[o];
	int mid = (l + r) >> 1, ret = kInf;
	if(p <= mid) ret = std::min(ret, Query(o << 1, l, mid, p));
	ret = std::min(ret, Query(o << 1 | 1, mid + 1, r, p));
	return ret;
}
void Modify(int o, int l, int r, int p) {
	if(l == r) seg[o] = nxt[p];
	else {
		int mid = (l + r) >> 1;
		if(p <= mid) Modify(o << 1, l, mid, p);
		else Modify(o << 1 | 1, mid + 1, r, p);
		Update(o);
	}
}

int main() { 
	int T = 1; //rd(T);
	while(T--) {
		memset(seg, 0x3f, sizeof(seg));
		memset(nxt, 0x3f, sizeof(nxt));
		rd(n, m, w);
		for(int i = 1; i <= n; ++i) {
			rd(a[i]);
			S[std::min(a[i], w - a[i])].insert(i);
		}
		for(int i = 0; i <= w / 2; ++i) S[i].insert(n + 1);
		for(int i = 1; i <= n; ++i) {
			int v = std::min(a[i], w - a[i]);
			auto it = S[v].upper_bound(i);
			nxt[i] = a[*it] + a[i] == w ? *it : n + 1;
		}
		Build(1, 1, n);
		int cnt = 0;
		while(m--) {
			int opt, x, y; rd(opt, x, y);
			if(opt == 1) {
				int v_a = std::min(a[x], w - a[x]), v_y = std::min(y, w - y);
				S[v_a].erase(x);
				auto it = S[v_a].lower_bound(x);
				if(it != S[v_a].begin()) {
					int tmp = *(it--);
					nxt[*it] = a[tmp] + a[*it] == w ? tmp : n + 1;
					Modify(1, 1, n, *it);
				}
				a[x] = y;
				S[v_y].insert(x);
				it = S[v_y].upper_bound(x);
				nxt[x] = a[*it] + a[x] == w ? *it : n + 1;
				Modify(1, 1, n, x);
				it = S[v_y].lower_bound(x);
				if(it != S[v_y].begin()) {
					int tmp = *(it--);
					nxt[*it] = a[tmp] + a[*it] == w ? tmp : n + 1;
					Modify(1, 1, n, *it);
				}
			} else if(opt == 2) {
				x ^= cnt; y ^= cnt;
				bool flag = Query(1, 1, n, x) <= y;
				cnt += flag;
				printf(flag ? "Yes\n" : "No\n");
			}
		}
	} return 0;
}
```

---

## 作者：Zxsoul (赞：14)

# P6617 查找 Search 题解

**考查方向**
> $\texttt{set}$ 的应用和线段树基本操作，较大的思维量

**分析题目**

读完题目应该发现相加之和等于 $w$ 的两个垃圾桶是必须处理的，我们从**做贡献**的角度去考虑，对于位置 $i$ ，倘若后面又若干个数与之相加之和是 $w$ 的数，且 $i$ 是**和**后面所有数可以做出贡献的最近的一个数。那么要想做出贡献，只能是和 $i$ 距离是最近的一个位置，其他的都不做贡献。

**思路**

思考方向和 [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972) 十分相似，可以说是双倍经验。这样我们用 $nxt_i$ 表示 $i$ 点往后一个与之相加是 $w$ 的位置，先不考虑修改，那么答案就是：
$$
\min_{l}^{r}nxt_i\le r
$$
解释一下什么意思，只要在区间 $[l,r]$ 中位置最小的后缀匹配成功 $nxt_i$ 在区间内，那么就可产生贡献。这个可以用线段树维护区间最小值操作。

再考虑修改，对于位置 $i$ 被修改，可能产生什么影响？
- 自身被修改，重新找到自己的后缀匹配位置（也许找不到）
- 原来数的后缀匹配位置受到影响，需要重新找到和前面匹配的位置（也许这个数没有）
- 在位置 $i$ 前面的数拥有的后缀匹配位置可能需要更新，因为新的数在 $i$ 中出现

对于上面的问题，都可以用 $\texttt{set}$ 维护前驱后记。然后就完成了

值得一说的是：`int last=*(it--); ` 此操作是先赋值再更新，各位不要理解错了。

备注：思路来源于题解区，在我看来更好理解 qwq    


```c
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e5+10;
const int B = 5e5+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
#define root 1,n,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int a[B];
int nxt[B];
namespace Seg
{
    struct node
    {
        int l,r;
        int sum;
        int minx;
        node() {l=r=sum=minx=0;}
        void init(int l_,int r_) {l=l_,r=r_,sum=nxt[l];minx=nxt[l];};
    }z[B<<2];
    node operator +(const node &l, const node &r)
    {
        node p; p.l=l.l, p.r=r.r; p.minx=min(l.minx,r.minx);
        return p; 
    } 
    void update(int rt) {z[rt]=z[rt<<1]+z[rt<<1|1];}
    void build(int l,int r,int rt)
    {
        if (l==r) {z[rt].init(l,r); return;}
        int m=l+r>>1;
        build(lson), build(rson); update(rt); 
    }
    void modify(int l,int r,int rt,int x)
    {
        if (l==r) {z[rt].minx=nxt[x];return;}
        int m=l+r>>1;
        if (x<=m) modify(lson,x);
        if (x>m) modify(rson,x);
        update(rt);
    }
    node query(int l,int r,int rt,int nowl,int nowr)
    {
        if (nowl<=l && r<=nowr) return z[rt];
        int m=l+r>>1;
        if (nowl<=m)
        {
            if (m<nowr) return query(lson,nowl,nowr)+query(rson,nowl,nowr);
            return query(lson,nowl,nowr); 
        }
        return query(rson,nowl,nowr);
    }
} 
int n,m,w;
set<int> se[B];
int cnt;
#define tpy set<int>::iterator
int main()
{
    n=read(),m=read(),w=read();
    for (int i=1;i<=n;i++) 
    {
        a[i]=read();
        se[min(a[i],w-a[i])].insert(i);
    }
    for (int i=0;i<=w/2;i++) se[i].insert(n+1);
    for (int i=1;i<=n;i++)
    {
        tpy it=se[min(a[i],w-a[i])].upper_bound(i);
        nxt[i]=(a[*it]+a[i]==w) ? *it : n+1; 
    }
    Seg::build(root);
    while (m--)
    {
        int opt=read();
        if (opt==1)
        {
            int x=read(),y=read();
            se[min(a[x],w-a[x])].erase(x);
            tpy it=se[min(a[x],w-a[x])].lower_bound(x);//改原来后面 
            if (it!=se[min(a[x],w-a[x])].begin())
            {
                int last=*(it--); //这里是先赋值再--  所以下面的 *it 表示是前一个位置 
                nxt[*it]=(a[last]+a[*it]==w) ? last : n+1;//
                Seg::modify(root,*it); 
            } 
            a[x]=y;
            se[min(y,w-y)].insert(x);
            it=se[min(y,w-y)].upper_bound(x);
            nxt[x]=(a[*it]+a[x]==w) ? *it : n+1;
            Seg::modify(root,x);
            it=se[min(y,w-y)].lower_bound(x);
            if (it!=se[x].begin())
            {
                int tmp=*(it--);
                nxt[*it]=a[tmp]+a[*it]==w ? tmp : n+1;
                Seg::modify(root,*it);
            }  
        }
        else if (opt==2)
        {
            int x=read(),y=read();
            x^=cnt; y^=cnt;
            if (Seg::query(root,x,y).minx<=y)
            {
                cnt++;
                printf("Yes\n");
            }    
            else printf("No\n");
        }
    }
}
```

若有不符合规矩的地方请管理员大大详细点出，我认真修改，望通过。

---

## 作者：Mu_leaf (赞：8)

## [思路]

先考虑如果没有修改操作，那么直接记录当前这个数的前驱即可。

- 前驱的定义：在这个数前面第一个且和为 $w$ 的数的位置。

那加上修改操作呢？

显然我们如果继续使用刚才对前驱的定义一次修改的可能会影响 $O(n)$ 级别的数。很巧的转换：如果第 $x$ 个数的前驱位置在前一个与 $x$ 相同的数前面，则该前驱为 $0$。显然是对的。

那么我们修改一次的操作只会影响 $5$ 个位置的数：

在这令 $x$ 为当前位置改之前的数，$y$ 为改之后的数。

- 当前位置。
- 后面第一个与 $x$ 相同的数。
- 后面第一个与 $x$ 相加和为 $w$ 的数。
- 后面第一个与 $y$ 相同的数。
- 后面第一个与 $y$ 相加和为 $w$ 的数。

考虑的每个数的前驱可以 $O(\log n)$ 算出来，于是可以要查询某个数的前驱时再找到这个数的前驱，虽然常数大，但会好写很多。

# Code:
--
```cpp
#include <bits/stdc++.h>
// #define int long long
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>
	void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T,typename ...Args>
	void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>
	void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>
	void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);putch('\n');}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N=5e5+5;
int n,m,w;
int a[N],vis[N],cnt,pre[N],op[N];
set<int> s[N];
struct SGT{
	int tr[N<<2];
	
	void pushup(int x){tr[x]=max(tr[ls],tr[rs]);}
	void build(int x,int l,int r){
		if(l==r){
			tr[x]=pre[l];
			return;
		}
		build(ls,l,mid);build(rs,mid+1,r);
		pushup(x);
	}
	void change(int x,int l,int r,int k,int v){
		if(l==r){
			tr[x]=v;
			return;
		}
		if(k<=mid) change(ls,l,mid,k,v);
		else change(rs,mid+1,r,k,v);
		pushup(x);
	}
	int query(int x,int l,int r,int lt,int rt){
		if(l>=lt && r<=rt){
			return tr[x];
		}
		int ans=0;
		if(lt<=mid) ans=max(ans,query(ls,l,mid,lt,rt));
		if(rt >mid) ans=max(ans,query(rs,mid+1,r,lt,rt));
		return ans;
	}
}t;
int fpre(int x){
    auto it1=s[a[x]].lower_bound(x),it2=s[w-a[x]].lower_bound(x);
    if(it2==s[w-a[x]].begin()) return 0;
    if(it1==s[a[x]].begin()) return *(--it2);
	--it1,--it2;
    if(*it1>*it2) return 0;
    return *it2;    
}
signed main(){
	read(n,m,w);
	for(int i=1;i<=n;i++){
		read(a[i]),t.change(1,1,n,i,fpre(i)),s[a[i]].insert(i);
	}
	// for(int i=1;i<=n;i++) cout << fpre(i) << "\n";
	for(int i=1,opt,x,y;i<=m;i++){
		read(opt,x,y);
		if(opt==1){
			// if(a[x]==y) continue;
			vector<int> upd;
            
            //nxtx 后面第一个与它原本相同的数
            auto it=s[a[x]].upper_bound(x);
            if(it!=s[a[x]].end()){
                upd.push_back(*it);
            }  
            //nxtx
            //nxtw-x 后面第一个和它原本相加为w的数
            it=s[w-a[x]].upper_bound(x);
            if(it!=s[w-a[x]].end()){
                upd.push_back(*it);
            }
            //nxtw-x
            //x 本身
            s[a[x]].erase(x);
            s[a[x]=y].insert(x);
            upd.push_back(x);
            //x
            //nxtx 后面第一个与它改后相等的数
            it=s[a[x]].upper_bound(x);
            if(it!=s[a[x]].end()){
                upd.push_back(*it);
            }
            //nxtx
            //nxtw-x 后面第一个与它改后相加为w的数
            it=s[w-a[x]].upper_bound(x);
            if(it!=s[w-a[x]].end()) upd.push_back(*it);
            //nxtw-x
            for(auto p:upd){
                t.change(1,1,n,p,fpre(p));
            }
		}else{  
 			x^=cnt,y^=cnt;
			if(t.query(1,1,n,x,y)>=x) cnt++,put("Yes");
			else put("No");
		}
	}
	flush();
	return 0  ;
}
/*
10 14 10
1 2 3 4 5 6 7 8 9 0
1 6 2
1 4 8
1 5 2
1 5 8
2 4 5
1 4 2
1 3 8
1 7 2
1 6 8
1 5 5
1 5 2
1 5 8
1 4 5
2 4 6
*/
```

---

## 作者：sprads (赞：5)

数据结构部分不难，重点在修改的讨论上，有点像 [P5278](https://www.luogu.com.cn/problem/P5278)。

定义一下两种关系：

- “补”表示与数 $x$ 相加为 $w$。

- “等”表示与数 $x$ 相等。

首先思考**没有修改操作**怎么做：对于每一个数记录 $v_i$ 表示它的**补前驱**。询问区间 $[l,r]$，就转化为询问 $[l,r]$ 中 $v$ 的最大值是否大于等于 $l$。这样就是一个 RMQ 问题了。

但是有修改操作后，可能有**很多数**的补前驱发生变化。进一步转化 $v_i$：对于一个数 $b$，若它**的补前驱的补后驱**仍是这个数，（即 $b$ 的补前驱要在 $b$ 的等前驱后面）我们才维护 $v_i$，否则让 $v_i=0$，显然此时仍然最优。

这样需要修改 $v$ 值的数就能够大大减少。

稍微分析一下，若改变 $a_x$ 的值为 $y$，则在位置 $x$ 上，只有 $a_x$ 的补后驱、等后驱，$y$ 的补后驱、等后驱和 $x$ 的 $v$ 值发生改变。

用值域个 `set` 维护不同数出现的位置，即可修改 $v$ 值（用 $b$ 的补前驱要在 $b$ 的等前驱后面这个性质维护，将同一件事重复五次就好了）。

```cpp
#include<bits/stdc++.h>
#define lson id * 2
#define rson id * 2 + 1
#define mid (l + r) / 2
using namespace std;
const int N = 500005;
set<int> s[N];
set<int>::iterator it; 
int n,m,w,a[N],v[N],Max[4*N];
int rd(){
	int x = 0;char ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
void build(int id,int l,int r){//平凡的线段树建树
	if(l == r){
		Max[id] = v[l];
		return;
	}
	build(lson,l,mid);
	build(rson,mid + 1,r);
	Max[id] = max(Max[lson],Max[rson]);
}
void update(int id,int l,int r,int x,int k){//平凡的线段树单点修改
	if(l == r){
		Max[id] = k;
		return;
	}
	if(x <= mid)
		update(lson,l,mid,x,k);
	else
		update(rson,mid + 1,r,x,k);
	Max[id] = max(Max[lson],Max[rson]);
}
int query(int id,int l,int r,int x,int y){//平凡的线段树询问区间最值
	if(x <= l && r <= y)
		return Max[id];
	int res = 0;
	if(x <= mid)
		res = max(res,query(lson,l,mid,x,y));
	if(y > mid)
		res = max(res,query(rson,mid + 1,r,x,y));
	return res;
}
void calc(int x,int y){//修改v值
	set<int>::iterator i = s[y].find(x);//i是y的等前驱
	set<int>::iterator j = s[w - y].upper_bound(x - 1);//j是y的补前驱
	if(j != s[w - y].begin()){//判断j的位置是否大于等于i，注意特判等前驱或补前驱不存在的情况
		if(i == s[y].begin())
			j--,v[x] = *j,update(1,1,n,x,*j);
		else if(*(--i) <= *(--j))
			v[x] = *j,update(1,1,n,x,*j);
		else v[x] = 0,update(1,1,n,x,0);
	}
	else v[x] = 0,update(1,1,n,x,0);
}
int main(){
	n = rd(),m = rd(),w = rd();
	for(int i = 1;i <= n;i++){
		a[i] = rd();
		if(!s[w - a[i]].empty() && (s[a[i]].empty() || *(--s[w - a[i]].end()) >= *(--s[a[i]].end())))//求一开始的v值
			v[i] = *(--s[w - a[i]].end());
		s[a[i]].insert(i);
	}
	build(1,1,n);
	int op,x,y,t = 0;
	while(m--){
		op = rd();
		if(op == 1){
			x = rd(),y = rd();
			set<int>::iterator k = ++s[a[x]].find(x);
			set<int>::iterator l = s[w - a[x]].upper_bound(x);//k是a[x]的等后驱，l是a[x]的补后驱
			s[a[x]].erase(x),s[y].insert(x);//set修改不能调换位置
			if(k != s[a[x]].end())//修改k
				calc(*k,a[x]);
			if(l != s[w - a[x]].end())//修改l
				calc(*l,w - a[x]);
			a[x] = y;
			k = ++s[a[x]].find(x);
			l = s[w - a[x]].upper_bound(x);//k是y的等后驱，l是y的补后驱
			if(k != s[a[x]].end())
				calc(*k,a[x]);
			if(l != s[w - a[x]].end())
				calc(*l,w - a[x]);
			calc(x,a[x]);
		}
		else{
			x = rd() ^ t,y = rd() ^ t;
			if(query(1,1,n,x,y) >= x)//询问
				puts("Yes"),t++;
			else puts("No");
		}
	}
	return 0;
}
```


---

## 作者：kkxacj (赞：3)

#### 思路

首先发现只有存在 $x,w-x$ 都在 $l$ 到 $r$ 里有才行。

发现每次修改只会改变一个数。

考虑对于每个数 $a_i$ 求出一个 $j$ 使得 $i \le j,a_j=w-a_i$，且 $j-i$ 最小。

可以用平衡树维护值为 $i$ 的数的所有位置，这样就可以支持删除，加入和查询了。

不过我们不能对于每个数都去求，不然修改后可能会更改很多东西。

所以对于每个数，如果 $i$ 到 $j$ 之间还存在 $z$ 使得 $a_i=a_z$，那么在这里就可以不算贡献，赋为 $n+1$ 即可。

显然这样做对答案没有影响。

对于修改，直接把**离它最近的前面一个值为 $w-a_i$ 的数** 和 **离它最近的前面一个值为 $w$ 的数** 更改贡献，给它自己更改贡献，把**离它最近的前面一个值为 $w-z$ 的数** 和 **离它最近的前面一个值为 $z$ 的数** 更改贡献即可。

然后线段树维护区间最小值，如果最小值 $ans \le r$ 那么就可行，否则不可行。

**code**
```cpp
#include<bits/stdc++.h>
#define mid ((c[p].l+c[p].r)>>1)
#define ls (p<<1)
#define rs ((p<<1)+1)
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 3e6+10;
int n,m,w,b[N],root[N],d[N],o,o1,l1,ans,cnt,x,y,z,op,mi;
struct w1
{
	int siz,v,key,l,r;
}a[N];
struct w2
{
	int l,r,mi;
}c[N];
inline void push_up(int x){a[x].siz = a[a[x].l].siz+a[a[x].r].siz+1;}
inline int add(int x)
{
	a[++cnt].siz = 1;
	a[cnt].v = x;
	a[cnt].key = rand();
	return cnt;
}
inline int merge(int l,int r)
{
	if(!l || !r) return l+r;
	if(a[l].key <= a[r].key)
	{
		a[l].r = merge(a[l].r,r);
		push_up(l);
		return l;
	}
	else
	{
		a[r].l = merge(l,a[r].l);
		push_up(r);
		return r;
	}
}
inline void spilt(int p,int x,int &l,int &r)
{
	if(!p) 
	{
		l = r = 0;
		return;
	}
	if(a[p].v <= x)
	{
		l = p;
		spilt(a[p].r,x,a[l].r,r);
	}
	else
	{
		r = p;
		spilt(a[p].l,x,l,a[r].l);
	}
	push_up(p);
	return;
}
inline int check(int x,int y)
{
	if(a[a[x].l].siz + 1 == y) return a[x].v;
	if(a[a[x].l].siz + 1 > y) return check(a[x].l,y);
	else return check(a[x].r,y-a[a[x].l].siz-1);
}
inline void build(int p,int l,int r)
{
	c[p].l = l,c[p].r = r;
	if(l == r)
	{
		int x,x1;
		spilt(root[w-b[l]],l,o,o1);
		x = check(o1,1);
		root[w-b[l]] = merge(o,o1);
		spilt(root[b[l]],l,o,o1);
		x1 = check(o1,1);
		root[b[l]] = merge(o,o1);
		if(x1 >= x) c[p].mi = x;
		else c[p].mi = 1e8;
	//	printf("最小值：%d，范围l=%d,r=%d\n",c[p].mi,c[p].l,c[p].r);
		return;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	c[p].mi = min(c[ls].mi,c[rs].mi);
	//printf("最小值：%d，范围l=%d,r=%d\n",c[p].mi,c[p].l,c[p].r);
}
inline void change(int p,int l)
{
	if(c[p].l == c[p].r && c[p].l == l)
	{
		int x,x1;
		//printf("最小值：%d，范围l=%d,r=%d\n",c[p].mi,c[p].l,c[p].r);
		spilt(root[w-b[l]],l,o,o1);
		x = check(o1,1);
		root[w-b[l]] = merge(o,o1);
		spilt(root[b[l]],l,o,o1);
		x1 = check(o1,1);
		root[b[l]] = merge(o,o1);
		if(x1 >= x) c[p].mi = x;
		else c[p].mi = 1e8;
		//printf("最小值：%d，范围l=%d,r=%d\n",c[p].mi,c[p].l,c[p].r);
		return;
	}
	if(l <= mid) change(ls,l);
	else change(rs,l);
	c[p].mi = min(c[ls].mi,c[rs].mi);
}
inline void query(int p,int l,int r)
{
	if(l <= c[p].l && c[p].r <= r)
	{
		mi = min(mi,c[p].mi);
		return;
	}
	if(l <= mid) query(ls,l,r);
	if(mid < r) query(rs,l,r);
}
signed main()
{
	read(n),read(m),read(w);
	srand(time(0));
	for(int i = 1;i <= n;i++) 
	{
		read(b[i]);
		spilt(root[b[i]],i-1,o,o1);
		root[b[i]] = merge(merge(o,add(i)),o1);
	}
	for(int i = 0;i <= 5e5;i++) 
	{
		spilt(root[i],n,o,o1);
		root[i] = merge(merge(o,add(n+1)),o1);
	}
	build(1,1,n);
	for(int i = 1;i <= m;i++)
	{
		read(x),read(y),read(z);
		if(x == 1)
		{
			int fx = w-b[y];
			spilt(root[b[y]],y-1,o,o1);
			spilt(o1,y,o1,l1);
			o1 = merge(a[o1].l,a[o1].r);
			root[b[y]] = merge(merge(o,o1),l1);
			
			int fy = b[y],bj = 0;
			b[y] = z;
			spilt(root[b[y]],y-1,o,o1);
			root[b[y]] = merge(merge(o,add(y)),o1);
			change(1,y);
			
			spilt(root[fy],y-1,o,o1);
			if(o != 0) bj=check(o,a[o].siz),root[fy] = merge(o,o1),change(1,bj);
			else root[fy] = merge(o,o1);
			
			
			spilt(root[fx],y-1,o,o1);
			if(o != 0) bj=check(o,a[o].siz),root[fx] = merge(o,o1),change(1,bj);
			else root[fx] = merge(o,o1);
			
			
			fx = w-b[y];
			spilt(root[fx],y-1,o,o1);
			if(o != 0) bj=check(o,a[o].siz),root[fx] = merge(o,o1),change(1,bj);
			else root[fx] = merge(o,o1);
		}
		else
		{
			y ^= op,z ^= op;
			mi = 1e8;
			query(1,y,z);
			if(mi <= z) pc('Y'),pc('e'),pc('s'),op++;
			else pc('N'),pc('o');
			pc('\n');
		}
	}
	flush();
	return 0;
}
/*
spilt(root,y-1,f1,f2);	
print(check(f1,a[f1].siz)),pc('\n');
root = merge(f1,f2); 
*/
```

---

## 作者：scp020 (赞：3)

# P6617 查找 Search 题解

真的肝死我了，这破题调了好长时间。还是颇有思维量的一道题。

## 解法

### 引入

我这道题的思路源自 P5278 那题。那道题可转换为若干子问题，其中之一就是让我们求区间内有无重复数字。

我们可以维护对于每个位置左边第一个与该位置值相同的位置，记作 $pre_i$。如果不存在该位置，则记为 $-1$。

$[l,r]$ 中存在相等的数字当且仅当 $\exist x \in [l,r]$，使得 $l \le pre_x$。

显然初始化这个 $pre$ 数组可以做到线性，现在考虑如何维护修改。

我们考虑维护一个集合 $s_i$，其中包含所有值等于 $i$ 的位置。如果将 $a_x$ 的值修改为 $y$，这个操作即为在 $s_{a_x}$ 中删除 $x$，在 $s_y$ 中插入 $x$。这个过程最多只影响 $3$ 个位置的 $pre$，即为 $x$，$x$ 右面第一个等于 $a_x$ 的位置，$x$ 右面第一个等于 $y$ 的位置。过程如图，黑笔为原来的 $pre$ 情况，红笔为修改后的 $pre$ 情况。字有点丑，见笑了。

![作图](https://cdn.luogu.com.cn/upload/image_hosting/gzdkvf5w.png)

### 迁移

将那道题的思想继承到这道题上。

还是维护数组 $pre$，但是意义有所不同。这里的 $pre$ 维护的是每个位置左边第一个与该位置值相加等于 $w$ 的位置。如果不存在该位置，则记为 $-1$。

需要注意的是，我们这次维护的 $pre$ 需要满足 $\forall i,j \in [1,n],pre_i \neq pre_j$。否则我们的时间复杂度是错的。如图，假若我们将所有的红色点的 $pre$ 都设为绿色点，那么当绿色点的值修改时我们需要修改每个红色点的 $pre$ 值。这么修改时间复杂度可以是 $\mathcal{O}(n)$ 的。

![作图](https://cdn.luogu.com.cn/upload/image_hosting/715z7v21.png)

我们可以改进这个问题。因为如果有一个位置 $x \in [l,r]$ 满足 $pre_x \in [l,r]$，那对于 $k \ge x,pre_k = pre_x$，这些 $pre_k$ 都是无效的，不会对答案产生影响。相反，如果有一个位置 $x \in [l,r]$ 不满足 $pre_x \in [l,r]$，那对于 $k \ge x,pre_k = pre_x$，这些 $pre_k$ 也都是无效的，不会对答案产生影响。所以对于每个值，最多只会有一个 $pre$ 值等于它。这些无效的值设为 $-1$ 即可。

我们可以额外维护一个 $ed$ 数组来维护这个值是否已经“被使用”。

这里我们只需要考虑在每次修改中需要更改的位置有哪些。如图，红色点即为可能需要修改的值。最多有 $5$ 个。

![作图](https://cdn.luogu.com.cn/upload/image_hosting/itatsn66.png)

知道了该修改哪些点了，我们就可以比较暴力地修改了。对于每个需要修改的位置 $x$，我们先把 $ed_{pre_x}$ 给解除一下，因为我们后续要进行修改。然后在 $s_{a_x}$ 中查找 $x$ 左边第一个与该位置值相同的位置，进行修改即可。

线段树只是个辅助维护 $pre$ 的工具，在本题中不是重点，不过多介绍了。线段树维护区间 $pre$ 最大值。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
	#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
	#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
	char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
	inline void read(int &x,char c=Getchar())
	{
		bool f=c!=45;
		x=0;
		while(c<48 or c>57) c=Getchar(),f&=c!=45;
		while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
		x=f?x:-x;
	}
	inline void write(int x)
	{
		if(x<0) Putchar(45),x=-x;
		if(x>=10) write(x/10),x%=10;
		Putchar(x^48);
	}
	inline void write(std::string st)
	{
		for(int i=0;i<st.size();i++) Putchar(st[i]);
	}
};
using namespace fast_IO;
int n,m,w,a[500010],pre[500010],ed[500010];
std::unordered_map< int,std::set<int> > mp;
struct node
{
	int mpre;
	node *lc,*rc;
	inline void pushup()
	{
		mpre=std::max(lc->mpre,rc->mpre);
	}
};
class seg_tree
{
	#define ls l,mid
	#define rs mid+1,r
private:
	node *root;
	inline node *build(int l,int r)
	{
		node *rt=new node;
		if(l==r) rt->mpre=pre[l];
		else
		{
			int mid=(l+r)/2;
			rt->lc=build(ls),rt->rc=build(rs),rt->pushup();
		}
		return rt;
	}
	inline void fix(node *rt,const int &pos,const int &val,int l,int r)
	{
		if(l==r)
		{
			rt->mpre=val;
			return;
		}
		int mid=(l+r)/2;
		if(pos<=mid) fix(rt->lc,pos,val,ls);
		else fix(rt->rc,pos,val,rs);
		rt->pushup();
	}
	inline int ask(node *rt,const int &L,const int &R,int l,int r)
	{
		if(L<=l && r<=R) return rt->mpre;
		int mid=(l+r)/2,ret=0;
		if(L<=mid) ret=std::max(ret,ask(rt->lc,L,R,ls));
		if(R>mid) ret=std::max(ret,ask(rt->rc,L,R,rs));
		return ret;
	}
public:
	inline void build()
	{
		root=build(1,n);
	}
	inline void fix(const int &pos,const int &val)
	{
		fix(root,pos,val,1,n);
	}
	inline int ask(const int &L,const int &R)
	{
		return ask(root,L,R,1,n);
	}
};
seg_tree tree;
std::vector< std::pair<int,int> > v;
inline void addget(const int &val,const int &it)
{
	if(pre[it]!=-1) ed[pre[it]]=0;
	v.push_back(std::make_pair(val,it));
}
inline void getpre(const int &val,const int &it)
{
	if(mp[w-val].empty())
	{
		pre[it]=-1,tree.fix(it,pre[it]);
		return;
	}
	std::set<int>::iterator it2=mp[w-val].lower_bound(it);
	if(it2==mp[w-val].begin()) pre[it]=-1,tree.fix(it,pre[it]);
	else
	{
		it2--;
		if(ed[*it2])
		{
			if(ed[*it2]>=it) pre[ed[*it2]]=-1,tree.fix(ed[*it2],pre[ed[*it2]]),ed[*it2]=it,pre[it]=*it2,tree.fix(it,pre[it]);
			else pre[it]=-1,tree.fix(it,pre[it]);
		}else ed[*it2]=it,pre[it]=*it2,tree.fix(it,pre[it]);
	}
}
inline void deladd()
{
	for(int i=0;i<v.size();i++) getpre(v[i].first,v[i].second);
	v.clear();
}
int main()
{
	// freopen("example.in","r",stdin);
	// freopen("example.out","w",stdout);
	read(n),read(m),read(w);
	for(int i=1;i<=n;i++) read(a[i]);
	std::set<int>::iterator it1,it2,it3;
	for(int i=1,prev;i<=n;i++)
	{
		if(!mp[w-a[i]].size()) pre[i]=-1;
		else
		{
			prev=*(--mp[w-a[i]].end());
			if(ed[prev]) pre[i]=-1;
			else pre[i]=prev,ed[prev]=i;
		}
		mp[a[i]].insert(i);
	}
	tree.build();
	for(int i=1,op,l,r,ans=0;i<=m;i++)
	{
		read(op),read(l),read(r);
		if(op==1)
		{
			it1=mp[a[l]].find(l),it2=mp[w-a[l]].lower_bound(l);
			if(it2!=mp[w-a[l]].end()) addget(w-a[l],*it2);
			if(it1!=mp[a[l]].end())
			{
				it1++;
				if(it1!=mp[a[l]].end()) addget(a[l],*it1);
			}
			if(pre[l]!=-1) ed[pre[l]]=0;
			mp[a[l]].erase(l),mp[r].insert(l),a[l]=r;
			it1=mp[a[l]].find(l),it2=mp[w-a[l]].lower_bound(l),addget(a[l],*it1);
			if(it2!=mp[w-a[l]].end()) addget(w-a[l],*it2);
			if(it1!=mp[a[l]].end())
			{
				it1++;
				if(it1!=mp[a[l]].end()) addget(a[l],*it1);
			}
			deladd();
		}else
		{
			l^=ans,r^=ans;
			if(tree.ask(l,r)>=l) write("Yes\n"),ans++;
			else write("No\n");
		}
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```


---

## 作者：_AyachiNene (赞：3)

# 思路：
比较好想的一道题。考虑什么样的点对能尽可能让多的区间得到贡献，显然，对于每一个右端点，去找离他最近的左端点是最优的。两个数相加为 $w$ 这个条件就有很强的性质了，不难发现，每个数有且只有一种能与它搭配后和为 $w$ 的数，考虑维护这个关系。不妨先把这些数分类，把所有数分成 $\frac{w}{2}$ 类，每一类 $x$ 只维护 $x$ 和 $w-x$。如果把这些点都提出来，以一个点为右端点就相当于在提出来的区间上查前驱，且要支持插入删除，用个平衡树就好了。对于修改，只会改到这个数的后继直接改就行。查询用一个线段树，维护每个数为右端点时，最大的左端点，维护个最大值，和给的区间判下就行。
# Code:
不是很会用 set，手写的平衡树还可以跑最优解第一页，看个乐就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'A'||ch>'Z')ch=getch();while(ch>='A'&&ch<='Z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m,w;
int a[114514<<3],b[114514<<3];
namespace Elaina
{
	int t[114514<<5];
	#define ls (root<<1)
	#define rs (root<<1|1)
	#define mid (l+r>>1)
	void insert(int x,int v,int l=1,int r=n,int root=1)
	{
		if(l==r)
		{
			t[root]=v;
			return;
		}
		if(x<=mid) insert(x,v,l,mid,ls);
		else insert(x,v,mid+1,r,rs);
		t[root]=max(t[ls],t[rs]);
	}
	int query(int x,int y,int l=1,int r=n,int root=1)
	{
		if(l>=x&&r<=y) return t[root];
		int res=0;
		if(x<=mid) res=max(res,query(x,y,l,mid,ls));
		if(y>mid) res=max(res,query(x,y,mid+1,r,rs));
		return res;
	}
	#undef ls 
	#undef rs
	#undef mid
}
namespace Chtholly
{
	struct node
	{
		int l,r,val,id,rnd;
	}t[114514<<3];
	int fw[114514<<3],top;
	inline void init(int p){for(int i=1;i<=p;i++) fw[++top]=i;}
	struct fhqt
	{
		int root;
		inline int New(int id,int x)
		{
			int cnt=fw[top--];
			t[cnt].val=x;
			t[cnt].id=id;
			t[cnt].rnd=rand();
			t[cnt].l=t[cnt].r=0;
			return cnt;
		}
		void split(int p,int v,int &x,int &y)
		{
			if(!p) x=y=0;
			else
			{
				if(t[p].id<=v) x=p,split(t[p].r,v,t[p].r,y);
				else y=p,split(t[p].l,v,x,t[p].l);
			}
		}
		int merge(int x,int y)
		{
			if(!x||!y) return x|y;
			if(t[x].rnd<t[y].rnd) 
			{
				t[x].r=merge(t[x].r,y);
				return x;
			}
			else
			{
				t[y].l=merge(x,t[y].l);
				return y;
			}
		}
		inline void insert(int id,int x)
		{
			int a,b;
			split(root,id,a,b);
			root=merge(a,merge(New(id,x),b));
		}
		inline void del(int id)
		{
			int a,b,c;
			split(root,id,b,c);
			split(b,id-1,a,b);
			fw[++top]=b;
			root=merge(a,c);
		}
		inline node pre(int id)
		{
			int a,b;
			split(root,id-1,a,b);
			int p=a;
			while(t[p].r) p=t[p].r;
			node res=t[p];
			if(!a) res.val=1919810;
			root=merge(a,b);
			return res;
		}
		inline node nxt(int id)
		{
			int a,b;
			split(root,id,a,b);
			int p=b;
			while(t[p].l) p=t[p].l;
			node res=t[p];
			if(!b) res.val=1919810;
			root=merge(a,b);
			return res;
		}
	}ft[114514<<3];
}
#define seg Elaina
#define fhq Chtholly
inline void update(int x)
{
	if(!x) return;
	fhq::node p=fhq::ft[b[x]].pre(x);
	if(p.val+a[x]==w) seg::insert(x,p.id);
	else seg::insert(x,0);
}
int main()
{
	read(n,m,w);
	fhq::init(n);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		if(a[i]<=w/2) fhq::ft[a[i]].insert(i,a[i]),b[i]=a[i];
		else fhq::ft[w-a[i]].insert(i,a[i]),b[i]=w-a[i];
		update(i);
	}
	int lastans=0;
	while(m--)
	{
		int op,x,y;
		read(op,x,y);
		if(op==1)
		{
			fhq::node nx=fhq::ft[b[x]].nxt(x);
			fhq::ft[b[x]].del(x);
			update(nx.id);
			a[x]=y,b[x]=(a[x]<=w/2?a[x]:w-a[x]);
			fhq::ft[b[x]].insert(x,a[x]);
			nx=fhq::ft[b[x]].nxt(x);
			update(x);update(nx.id);
		}
		else
		{
			x^=lastans,y^=lastans;
			if(seg::query(x,y)>=x) ++lastans,put("Yes\n");
			else put("No\n");
		}
	}
	flush();
}
```

---

## 作者：lizhous (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/P6617)

~~貌似是暴力？~~**这是一个较暴力的做法**

## 题意
支持单点修改，查询区间内是否存在两数相加为 $w$。强制在线。

## 分析
我们首先想到，假如我们知道一个数 $i$ 往前最近的位置 $j$ 满足 $a_i+a_j=w$，我们只需要知道区间 $[l,r]$ 内是否存在一个 $i$ 对应的 $j$ 满足 $l\le i,j \le r$，就知道询问的结果了。

继续考虑查询。枚举 $i$ 显然慢，我们发现只要最大的 $j$ 满足 $l\le j$，则答案为`Yes`。此处是一个单修区查的线段树。接下来考虑如何维护 $j$。

到这我就不会了，所以我考虑一个暴力。由于 $w$ 固定，值域小，想到暴力修改。开值域个`set`。第 $i$ 个`set`存储所有值为 $i$ 的数的位置。每次修改操作，暴力枚举`set`中的数并修改。注意一下越界问题即可。时间复杂度 $O(nm\log n)$????

维护见代码，注释很详细。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<queue>
#define int long long
using namespace std;
int n,m,a[1000001],mi[6000001],lmi[1000001]/*表示往前最近的位置j，与线段树同步的数组，减小复杂度*/,ton[1000001],w,cnt;
set<int> fun[1000001];
//以下为线段树
void add(int o,int l,int r,int x,int y)
{
	if(l==r)
	{
		mi[o]=y;
		return;
	}
	int mid=r+l>>1;
	if(x<=mid) add((o<<1),l,mid,x,y);
	else add((o<<1)+1,mid+1,r,x,y);
	mi[o]=max(mi[(o<<1)],mi[(o<<1)+1]);
}
int get(int o,int l,int r,int x,int y)
{
	if(x>r || y<l) return 0;
	if(x<=l&&y>=r) return mi[o];
	int mid=l+r>>1;
	return max(get(o<<1,l,mid,x,y),get((o<<1)+1,mid+1,r,x,y));
}
//以上为线段树
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&w);
	for(int i=1; i<=n; i++)
	{
		scanf("%lld",&a[i]);
		lmi[i]=ton[w-a[i]]; //第一次处理用桶
		ton[a[i]]=i; //更新桶
		add(1,1,n,i,lmi[i]); //更新线段树
		fun[a[i]].insert(i); //更新set
	}
	for(int i=1,opt,x,y; i<=m; i++)
	{
		scanf("%lld%lld%lld",&opt,&x,&y);
		if(opt==1)
		{
			set<int>::iterator iw=fun[a[x]].lower_bound(x); //先找到下一个值相等的
			int fua;
			if(iw==fun[a[x]].begin()) fua=0; //找上一个
			else
			{
				iw--;
				fua=*iw; //上一个位置记录
			}

			iw=fun[w-a[x]].lower_bound(x) //枚举每个当前答案
			while(iw!=fun[w-a[x]].end()&&lmi[*iw]==x) //扫set
			{
				lmi[*iw]=fua; //更新为前一个相同值
				add(1,1,n,*iw,fua); //线段树更新
				iw++; //指针往后
			}

			fun[a[x]].erase(x); //set中删除
			a[x]=y; //数组更新
			fun[a[x]].insert(x); //set插入
			iw=fun[w-a[x]].lower_bound(x); //扫描每个影响的set
			while(iw!=fun[w-a[x]].end()&&lmi[*iw]<x) //扫set
			{
				lmi[*iw]=x; //更新数组
				add(1,1,n,*iw,x); //更新线段树
				iw++; //指针往后
			}
			
			iw=fun[w-a[x]].lower_bound(x); //更新当前的前一个
			if(iw==fun[w-a[x]].begin()) lmi[x]=0; //往前更新
			else
			{
				iw--;
				lmi[x]=*iw;
			}
			add(1,1,n,x,lmi[x]); //线段树更新
		}
		else
		{
			x^=cnt;
			y^=cnt;
			if(get(1,1,n,x,y)<x) //如果存在
			{
				printf("No\n");
			}
			else
			{
				cnt++;
				printf("Yes\n");
			}
		}
	}
}
```

---

## 作者：syk666 (赞：1)

首先很自然的思路：

对于每个位置维护它最近的，与其和为 $ w $ 的前驱。

那么对于查询区间 $ l,r $ 来说，只要区间内存在一个数的前驱 $ \ge $ $ l $ 即可，这个可以用线段树维护。

但有个问题就是，如果修改了一个位置，前驱是这个位置的数可能达到 $ n $ 级别，直接爆炸。

所以修改前驱定义：

令当前位置为 $ pos $ ，前驱为 $ pre $ 。

满足  $ a_{pos}+a_{pre}=w $ 且 $ (pre,pos) $ 之间不存在与  $ a_{pos} $ 和 $ a_{pre} $ 相等。

进一步的说：我们可以定义这种关系为 **双向** 的，两两匹配在某一时刻是一定的，而若某个位置没有被匹配的话，一定也不会被答案选到，那么赋值为 $ 0 $ 即可。

那么接下来细说如何考虑修改对这些双向关系的影响：

假设 $ a_{pos} =val $ ，设原  $ a_{pos} =x$ 。

### 1. $ a_{pos} $ 的原后继

即在 $ pos $ 之后，下一个出现的 $ a_{pos} $ 的位置。


考虑这种情况：$ w-x....x....x $ 

对于中间这个 $ x $ 删掉之后，原后继可能又有机会重新进行一次匹配。

### 2.$ a_{pos} $ 的新定义后继

根据前面定义，其新后继值为 $ w-x $ 。

对于中间的 $ x $ 被修改了，可能出现几种情况：

##### (1) 一开始 $ w-x $ 未与 $ x $ 不具备双向关系

即  $ x $ 到 $ w-x $ 之间还存在 $ x $ ，$ x $ 找到的 $ w-x $ 仅仅是单向的，而 $ w-x $ 的前驱并不是 $ pos $ ，再进行一次匹配也不影响。

##### (2) 一开始 $ w-x $ 未与 $ x $ 具备双向关系

那么重新进行一次匹配即可。

### 3. 被修改后的 $ a_{pos} $

即自己被修改了，当然这个位置前驱也被修改。

具体情况类似 $ 2 $ ，直接匹配。

如何匹配后面会提到。

### 4.  被修改后的 $ a_{pos} $ 的原后继 

因为可能出现这种情况：

$  ....w-val......val(pos).....val $

那么新冒出来的 $ pos $ 会抢掉原后继的匹配，所以要修改。

### 5.  被修改后的 $ a_{pos} $ 的新定义后继

如情况 $ 2 $ 。

就只有这 $ 5 $ 情况，容易漏的就是 $ 1 ,4 $

然后就是匹配过程：

```cpp
void match(int pos,int posl){
    
    int v=a[pos];
    int pre=get_pre(w-a[pos],pos);
    if(pre==-1||(pre<posl&&posl!=-1)) {
        t.change(1,1,n,pos,0);
        return ;
    }
    int nxt=get_nxt(a[pos],pre);
    if(nxt<pos&&nxt!=-1){
        t.change(1,1,n,pos,0);
        return ;
    }
    t.change(1,1,n,pos,pre);
}
```


$ posl $ 即 $ a_{pos} $ 这个数上一个位置，显然不能越过与自己相同的数。

$ pre $ 即新定义前驱的位置。

如果没有前驱，或者 $ (pre,pos) $ 之间存在 $ a_{pos} $，那么也显然构成不了双向关系。

接着判断 $ pre $ 是否与 $ pos $ 形成对应关系，则找离 $ pre $ 的后继是否为 $ pos $ 。（但其实可加可不加）

如果构成关系，就直接在线段数上单点修改前驱即可。

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
using namespace std;
const int N=1e6+5;
int n,m,w;
int a[N];
map<int,int> id;
int idx=0;
set<int> s[N];
int yes=0;
struct Seg{
    int maxx[N<<4];
    void pushup(int p){
        maxx[p]=max(maxx[p*2],maxx[p*2+1]);
    }
    void change(int p,int l,int r,int pos,int val){
        if(l==r){
            maxx[p]=val;
            return ;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) change(p*2,l,mid,pos,val);
        else change(p*2+1,mid+1,r,pos,val);
        pushup(p);
    }
    int query(int p,int l,int r,int x,int y){
        if(x<=l&&r<=y){
            return maxx[p];
        }
        int mid=(l+r)>>1,res=0;
        if(x<=mid) res=max(res,query(p*2,l,mid,x,y));
        if(y>mid) res=max(res,query(p*2+1,mid+1,r,x,y));
        return res;
    }
}t;
int get_pre(int val,int pos){
    if(id[val]==0) return -1;
    auto it=s[id[val]].lower_bound(pos);
    if(it==s[id[val]].begin()) return -1;
    it--;
    return (*it);
}
int get_nxt(int val,int pos){
    if(id[val]==0) return -1;
    auto it=s[id[val]].upper_bound(pos);
    if(it==s[id[val]].end()) return -1;
    return (*it);
}
void match(int pos,int posl){
    int v=a[pos];
    int pre=get_pre(w-a[pos],pos);
    if(pre==-1||(pre<posl&&posl!=-1)) {
        t.change(1,1,n,pos,0);
        return ;
    }
    int nxt=get_nxt(a[pos],pre);
    if(nxt<pos&&nxt!=-1){
        t.change(1,1,n,pos,0);
        return ;
    }
    t.change(1,1,n,pos,pre);
}
int main(){
    scanf("%d%d%d",&n,&m,&w);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(id[a[i]]==0){
            id[a[i]]=++idx;
        }
        match(i,get_pre(a[i],i));
        s[id[a[i]]].insert(i);
    }
    int dp=0;
    while(m--){
        int op,pos,val;
        int l,r;
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d",&pos,&val);
            vector<int> v;
            v.clear();
            v.push_back(get_nxt(w-a[pos],pos));
            v.push_back(get_nxt(a[pos],pos));
            s[id[a[pos]]].erase(pos);
            a[pos]=val;
            if(id[a[pos]]==0)
                id[a[pos]]=++idx;
            s[id[a[pos]]].insert(pos);
            v.push_back(pos);
            v.push_back(get_nxt(w-a[pos],pos));
            v.push_back(get_nxt(a[pos],pos));
            match(v[0],get_pre(a[v[0]],v[0]));
            match(v[1],get_pre(a[v[1]],v[1]));
            match(v[2],get_pre(a[v[2]],v[2]));
            match(v[3],get_pre(a[v[3]],v[3]));
            match(v[4],get_pre(a[v[4]],v[4]));
        }else{
            scanf("%d%d",&l,&r);
            l^=yes,r^=yes;
            if(t.query(1,1,n,l,r)>=l){
                puts("Yes");
                yes++;
            }else{
                puts("No");
            }
        }
    }
    return 0;
}

/*
6 4 6
1 3 2 5 5 6
2 1 4
1 4 1
2 0 5
2 3 7

10 100000 10
1 2 3 4 5 6 7 8 9 0
1 6 2
1 4 8
1 5 2
1 5 8
2 4 5
1 4 2
1 3 8
1 7 2
1 6 8
1 5 5
1 5 2
1 5 8
1 4 5
2 4 6
*/

```


---

## 作者：ダ月 (赞：1)

### 题目分析：

我们记前驱为权值 $x$ 距离 $w-x$ 最近的点（在原序列 $a_i$ 上时 $w-x$ 应该在 $x$ 的前面）的位置。我们可以开值域个 `set` 记录每个权值出现过的位置，前驱只要在上面二分就行。

有一个结论，对于 $[x_1,y_1]\in[x_2,y_2]$，并且 $a_{x_1}+a_{y_1}=a_{x_2}+a_{y_2}=w$，那么 $[x_2,y_2]$ 是无意义的。你要想，这是一个存在性问题。如果 $(x_1,y_1)$ 满足了$a_{x_1}+a_{y_1}$，那么区间 $[x_2,y_2]$ 也肯定存在这对数。

因此，对于询问操作，我们只需要维护每一个前驱所在的位置的最大值是否不小于 $l$ 即可。可以用线段树来维护。

对于修改操作，显然，暴力修改会改动 $n$ 个数据。但是细细得想一想，前驱为该数的数有且仅有一个。所以在每次修改的时候，我们只用修改当前数的前驱，为以该数为前驱的数的前驱即可。

时间复杂度：$O(n\log n)$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+10;
#define pd(x) push_back(x)
#define rz(x,y) x.resize(y)
#define all(x) x.begin(),x.end()
#define First(x) (*x.begin())
#define End(x) (*x.end())
#define Avail(x,y) (x.find(y)==x.end())
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}ll readLL(){
		ll x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}void GStr(char *c,bool Ban_Space=true){
		c[0]=0;int p=0;
		while(c[p]!='\n'&&(c[p]!=' '||Ban_Space))c[++p]=getchar();
		c[p]='\0';
	}string Gstr(bool Ban_Space=true,int Pr_Space=1){
		string s;char c=0;
		for(int i=1;i<=Pr_Space;i++)s+=' ';
		while(c!='\n'&&(c!=' '||Ban_Space))c=getchar(),s+=c;s.pop_back();s+='\0';
		return s;
	}
	char readChar(){
		char c=' ';
		while(c==' '&&c=='\n')c=getchar();
		return c;
	}void write(int x){
		if(!x)return;
		write(x/10);
		putchar(x%10+'0');
	}void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
	void Wc(char c){putchar(c);}
	void writell(ll x){
		if(!x)return;
		write(x/10);
		putchar(x%10+'0');
	}void Outputll(ll x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else writell(x);}
	void WLll(ll x){Outputll(x);putchar('\n');}
	void WSll(ll x){Outputll(x);putchar(' ');}
	void Wstr(string s){for(int i=0;i<s.size();i++)Wc(s[i]);}
	void Wstr(char *s){int l=strlen(s);for(int i=0;i<l;i++)Wc(s[i]);}
	#define PS putchar(' ')
	#define Pn putchar('\n');
}
//==============================================================================
set<int> s[N];
int n,m,w,a[N];
int tr[N<<2];
void pushup(int rt){tr[rt]=max(tr[rt<<1],tr[rt<<1|1]);}
void change(int rt,int l,int r,int x,int y){
	if(l==r)return tr[rt]=y,void();
	int mid=l+r>>1;
	if(x<=mid)change(rt<<1,l,mid,x,y);
	else change(rt<<1|1,mid+1,r,x,y);
	pushup(rt);
}int query(int rt,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tr[rt];
	int mid=l+r>>1;int ans=0;
	if(x<=mid)ans=max(ans,query(rt<<1,l,mid,x,y));
	if(y>mid)ans=max(ans,query(rt<<1|1,mid+1,r,x,y));
	return ans;
}int Gpr(int x){
	auto p1=s[a[x]].lower_bound(x),p2=s[w-a[x]].lower_bound(x);
	if(p2==s[w-a[x]].begin())return 0;
	if(p1==s[a[x]].begin())return *--p2;
	return *--p1>*--p2?0:*p2;
}int cnt=0;
void Pd(vector<int> &v,int x,int y){
	auto p=s[x].upper_bound(y);
	if(p!=s[x].end())v.pd(*p);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d%d",&n,&m,&w);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		change(1,1,n,i,Gpr(i));
		s[a[i]].insert(i);
	}
	int lat=0;
	while(m--){
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt==1){
			vector<int> v;
			Pd(v,a[x],x);Pd(v,w-a[x],x);
			s[a[x]].erase(x);a[x]=y;
			s[a[x]].insert(x);v.pd(x);
			Pd(v,a[x],x);Pd(v,w-a[x],x);
			for(auto p:v)change(1,1,n,p,Gpr(p));
		}else{
			x^=lat,y^=lat;
			if(query(1,1,n,x,y)>=x)puts("Yes"),lat++;
			else puts("No");
		}
	}return 0;
}
```


---

## 作者：寒鸽儿 (赞：1)

感觉是分类讨论题，可能代码写繁了。  
### 题意  
强制在线，单点修改，区间查询是否存在两数之和等于 $w$ （全局固定）。  

$1 \leq n, q, w \leq 10^5, 0 \leq a_i \leq w$ 。  
### 题解

若不带修，区间维护前一个和当前数相等的数值，区间 $\max$ 和 $l$ 比较即可。

带修维护这个东西是困难的，但是我们回答的是判定性的问题。 

对于以某个数值为前驱的两个数，显然包含靠后一者的区间也一定包含前者者，因而我们只需要统计这样的点对是否存在：一个数与前面最近的数之和为 $w$ ，且二者之间不包含与这个数字相等的数值。  

这个东西的维护是简单的，考虑一个数值删去的影响，先看它是否挡住了后面的数值，再看是否存在以它为前面一个点的点对。插入一个数值的影响是考虑它是否会挡住其它数，以及它是否与其它数构成点对。  

$2x = w$ 的情况用上述方法处理也不会出问题。当然也可以特判之后用一条链特殊处理。  

### 代码(写的好丑)
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define itra set<int>::iterator

using namespace std;

const int maxn = 5e5 + 10, inf = 0x3f3f3f3f;
set<int> s[maxn];
int a[maxn], b[maxn];

struct segTree {
    int mx[maxn << 2];
    void update(int p) { mx[p] = max(mx[p<<1], mx[p<<1|1]); }
    void build(int p, int lp, int rp) {
        if(lp == rp) { mx[p] = b[lp]; return; }
        int mid = (lp + rp) >> 1;
        build(p<<1, lp, mid); build(p<<1|1, mid + 1, rp);
        update(p);
    }
    void modify(int p, int lp, int rp, int x, int v) {
        if(lp == rp) { mx[p] = v; return; }
        int mid = (lp + rp) >> 1;
        if(x <= mid) modify(p<<1, lp, mid, x, v);
        if(x > mid) modify(p<<1|1, mid+1, rp, x, v);
        update(p);
    }
    int qry(int p, int lp, int rp, int l, int r) {
        if(l <= lp && rp <= r) return mx[p];
        int mid = (lp + rp) >> 1, ans = -inf;
        if(l <= mid) ans = qry(p<<1, lp, mid, l, r);
        if(r > mid) ans = max(ans, qry(p<<1|1, mid + 1, rp, l, r));
        return ans;
    }
} stre;

int main() {

    if(fopen("yl.in", "r")) {
        freopen("yl.in", "r", stdin);
        freopen("yl.out", "w", stdout);
    }

    int n, m, w, opt, x, y;
    scanf("%d %d %d", &n, &m, &w);
    rep(i,0,w) s[i].insert(0), s[i].insert(n + 1);
    rep(i,1,n) {
        scanf("%d", a + i);
        if(a[i] * 2 == w) {
            itra it = s[a[i]].lower_bound(i);
            -- it; b[i] = *it;
        } else {
            itra it = s[w - a[i]].lower_bound(i);
            -- it;
            itra pre = s[a[i]].upper_bound(i);
            -- pre;
            b[i] = *it < *pre ? 0 : *it;
        }
        stre.modify(1, 0, n + 1, i, b[i]);
        s[a[i]].insert(i);
    }
    stre.build(1, 0, n + 1);
    int cnt = 0;
    rep(qr,1,m) {
        scanf("%d %d %d", &opt, &x, &y);
        if(opt == 1) {
            if(a[x] == y) continue;
            s[a[x]].erase(s[a[x]].find(x));
            itra nexw = s[w - a[x]].lower_bound(x);
            itra prew = nexw; -- prew;
            itra nexx = s[a[x]].lower_bound(x);
            itra prex = nexx; -- prex;
            if(b[*nexw] == x) {
                b[*nexw] = *prew < *prex ? *prex : 0;
                stre.modify(1, 0, n + 1, *nexw, b[*nexw]);
            }
            if(*nexx < *nexw && b[x] != 0 && b[x] != n + 1) {
                b[*nexx] = *prew;
                stre.modify(1, 0, n + 1, *nexx, b[*nexx]);
            }
            nexw = s[w - y].upper_bound(x);
            prew = nexw; -- prew;
            itra nexy = s[y].upper_bound(x);
            itra prey = nexy; -- prey;
            b[x] = *prew > *prey ? *prew : 0;
            stre.modify(1, 0, n + 1, x, b[x]);
            if(*nexy > *nexw) {
                b[*nexw] = x; stre.modify(1, 0, n + 1, *nexw, x);
            } else {
                b[*nexy] = 0; stre.modify(1, 0, n + 1, *nexy, 0);
            }
            s[y].insert(x);
            a[x] = y;
        } else {
            x ^= cnt; y ^= cnt;
            if(stre.qry(1, 0, n + 1, x, y) >= x) ++ cnt, puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
~~水题~~。
# 思路
看完题意之后发现 $w$ 一定所以可以考虑用一棵线段树维护第 $i$ 个数前第一个等于 $w-a_i$ 的值的下标然后每次修改时只需要改变原数后面的那一个与他相加为 $w$ 的数的值与修改后能与 $a_i$ 相加为 $w$ 的数的值以及自己（这个用 set 维护即可）。

但是我们发现他会错两个点，而原因为我们发现对于修改一个值 $i$ 在 $i$ 之后可能有多个值存的值都为 $i$，所以我们考虑将每一个点存的值改一下定义，我们将每一个值存为 $i$ 之前第一个不小于 $i$ 之前第一个与 $a_i$ 相等的位置的 $w-a_i$ 的位置，所以我们发现这样每次修改最多修改 $5$ 个位置的值（$i$，值为 $w-a_i$ 的第一个大于 $i$ 的位置，$i$ 之后第一个等于 $a_i$ 的位置，值为 $w-x$ 的第一个大于 $i$ 的位置以及 $i$ 之后第一个值为 $x$ 的位置）。而这一系列的操作均可用 set 来维护。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,m,w;
const int N=5e5+10;
struct node{
	int l,r;
	int Max;
}tr[N<<2];
int a[N];
il void up(int x) {
	tr[x].Max=max(tr[x<<1].Max,tr[x<<1|1].Max);
}
set<int>s[N];
il void build(int u,int l,int r) {
	tr[u]={l,r};
	if(l==r) {
		auto it=s[w-a[l]].lower_bound(l);
		if(it!=s[w-a[l]].begin()) {
			it--;
			auto it1=s[a[l]].lower_bound(l);
			if(it1!=s[a[l]].begin()) {
				it1--;
				if((*it1)<=(*it)) tr[u].Max=(*it);
			}else tr[u].Max=(*it);
		}
		return ;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	up(u);
}
il void modify(int u,int x) {
	if(tr[u].l==tr[u].r) {
		if(!s[w-a[x]].size()) {
			tr[u].Max=false;
			return ;
		}
		auto it=s[w-a[x]].lower_bound(x);
		tr[u].Max=false;
		if(it!=s[w-a[x]].begin()) {
			it--;
			auto it1=s[a[x]].lower_bound(x);
			if(it1!=s[a[x]].begin()) {
				it1--;
				if((*it1)<=(*it)) tr[u].Max=(*it);
			}else tr[u].Max=*it;
		}
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=x) modify(u<<1,x);
	else modify(u<<1|1,x);
	up(u);
}
il int Ans(int u,int l,int r) {
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u].Max;
	int mid=tr[u].l+tr[u].r>>1;
	int res=0;
	if(mid>=l) res=Ans(u<<1,l,r);
	if(mid<r) res=max(res,Ans(u<<1|1,l,r));
	return res;
}
fire main() {
	in(n),in(m),in(w);
	int cnt=false;
	rep(i,1,n) in(a[i]),s[a[i]].insert(i);
	build(1,1,n);
	while(m--) {
		int opt;
		in(opt);
		if(opt==1) {
			int i,x;
			in(i),in(x);
			s[a[i]].erase(i);
			if(s[w-a[i]].size()) {
				auto it=s[w-a[i]].upper_bound(i);
				if(it!=s[w-a[i]].end()) modify(1,*it);
			}
			if(s[a[i]].size()) {
				auto it=s[a[i]].lower_bound(i);
				if(it!=s[a[i]].end()) modify(1,*it);
			}
			a[i]=x; 
			s[x].insert(i);
			modify(1,i);
			if(s[w-x].size()) {
				auto it=s[w-a[i]].upper_bound(i);
				if(it!=s[w-a[i]].end()) modify(1,*it);
			}
			if(s[x].size()) {
				auto it=s[x].upper_bound(i);
				if(it!=s[x].end()) modify(1,*it);
			}
		}else {
			int l,r;
			in(l),in(r);
			l^=cnt,r^=cnt;
			if(Ans(1,l,r)>=l) {
				cnt++;
				printf("Yes\n");
			}else printf("No\n");
		}
	}
	return false;
}
```
暂时的最优解。

---

## 作者：C_Pos_Princess (赞：0)

## 题意
# 查找 Search

## 题目背景

>   也许，同学间最好的结局就是朋友吧。

$\mu ry$ 是一个可爱的女孩子。

在她所住的小区里有排成一排的 $n$ 个垃圾桶，从左至右第 $i$ 个垃圾桶里都装着编号为 $a_i$ 的垃圾。

$\mu ry$ 不喜欢无序，于是就想把社区里编号和为 $w$ 的垃圾都清在一起。

但是调皮的 $\text{LeverImmy}$ 可能会把某个垃圾桶里的垃圾偷换成另一种。

生气的 $\mu ry$ 想考考 $\text{LeverImmy}$ 一个区间 $[l, r]$ 内是否存在编号和为 $w$ 的垃圾。

但 $\text{LeverImmy}$ 也不会解决这个问题，于是他找到了聪明的你。

## 题目描述

给定 $n$ 个垃圾桶，你需要维护一个数据结构，支持以下操作：

-   `1 pos val` 表示将 第 $pos$ 个垃圾桶里的垃圾的编号换成 $val$；

-   `2 l r` 询问在 $[l\oplus cnt, r\oplus cnt]$ 内是否存在垃圾编号和为 $w$ 的 **两个** 垃圾桶。

其中 $\oplus$ 表示异或运算，$cnt$ 表示在 **此次询问之前**，答案为 `Yes` 的个数。

对于每个操作 2，若存在请输出 `Yes`，不存在请输出 `No`。

值得注意的是，对于所有询问， $w$ 为 **同一个数**。

## 题解

既然我们只需要判断是否存在这样两个垃圾桶，我们只需要这两步：
- 对于每个值维护一个 $set$，然后记录一下后面与当前值配对的数字最近的位置。
- 查询的时候查询当前区间内的最小值是否在区间内即可。

假设当前数字为 $x$，那我们将 $x$ 与 $w-x$ 的值都放在一个 $set$ 里面，注意按照下标从小到大，然后每个数字查一下他后面那个数字（相邻）是否满足条件。

注意这里只查后面相邻的一个位置，而不是满足条件的位置，仔细想想这样就已经足够了。

### 代码

```cpp
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
using namespace std;
struct node {
	int l, r;
	int sum;
	int minn;
} tr[N << 2];
int a[N];
int nxt[N];
void pushup(int rt) {
	tr[rt].minn = min(tr[rt << 1].minn, tr[rt << 1 | 1].minn);
}
void build(int rt, int l, int r) {
	tr[rt].l = l;
	tr[rt].r = r;
	if (l == r) {
		tr[rt].sum = nxt[l];
		tr[rt].minn = nxt[l];
		return;
	}
	int mid = l + r >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}

void update(int rt, int x, int val) {
	if (tr[rt].l == tr[rt].r) {
		tr[rt].minn = val;
		return;
	}
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (x <= mid) update(rt << 1, x, val);
	else update(rt << 1 | 1, x, val);
	pushup(rt);
}

int query(int rt, int l, int r) {
	if (l <= tr[rt].l && r >= tr[rt].r) {
		return tr[rt].minn;
	}
	int ans = 1e9;
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (l <= mid) ans = min(ans, query(rt << 1, l, r));
	if (r > mid) ans = min(ans, query(rt << 1 | 1, l, r));
	return ans;
}

int n, m;
set<int> st[N];
int cnt;
int w;

int main() {
	read(n, m);
	read(w);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		st[min(a[i], w - a[i])].insert(i);
	}
	for (int i = 0; i <= w / 2; i++) st[i].insert(n + 1);
	for (int i = 1; i <= n; i++) {
		set<int>::iterator it = st[min(a[i], w - a[i])].upper_bound(i);
		nxt[i] = (a[*it] + a[i] == w) ? *it : n + 1;
	}
	build(1, 1, n);
	while (m--) {
		int op;
		read(op);
		if (op == 1) {
			int x, y;
			read(x, y);
			st[min(a[x], w - a[x])].erase(x);
			set<int>::iterator it = st[min(a[x], w - a[x])].lower_bound(x);
			if (it != st[min(a[x], w - a[x])].begin()) {
				int last = *(it--);
				nxt[*it] = (a[last] + a[*it] == w) ? last : n + 1;
				update(1, *it, nxt[*it]);
			}
			a[x] = y;
			st[min(y, w - y)].insert(x);
			it = st[min(y, w - y)].upper_bound(x);
			nxt[x] = (a[*it]+a[x] == w)?*it:n+1;
			update(1,x,nxt[x]);
			it = st[min(y,w-y)].lower_bound(x);
			if (it != st[x].begin()) {
				int tmp = *(it--);
				nxt[*it] = (a[tmp] + a[*it] == w) ? tmp : n + 1;
				update(1, *it, nxt[*it]);
			}
		} else if (op == 2) {
			int x,y;
			read(x,y);
			x^=cnt,y^=cnt;
			if(query(1,x,y)<=y){
				cnt++;
				puts("Yes");
			}else{
				puts("No");
			}	
		}
	}


	return 0;
}

```

---

