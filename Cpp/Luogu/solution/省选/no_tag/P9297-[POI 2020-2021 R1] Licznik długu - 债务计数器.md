# [POI 2020/2021 R1] Licznik długu / 债务计数器

## 题目背景

**题目译自 [XXVIII Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi28-1/dashboard/) [Licznik długu](https://sio2.mimuw.edu.pl/c/oi28-1/p/lic/)。**

## 题目描述

Bajterowicza 教授指出，Bajtocji 的经济形势现在不容乐观。为了警示民众，他让 Bajtazara 公司在 Bajtocji 首都的市中心安装一块大型显示屏，用来显示 Bajtocji 现在的公共债务是多少。

Bajtocji 的公共债务由两部分组成：国内债务和国际债务。国内债务和国际债务最多可由 $n-1$ 个十进制数组成。而在显示屏上显示的是两部分债务的总和。

随着时间推移，Bajtocji 的债务状况也在不断变化。你现在需要帮助 Bajtazara 公司完成显示软件的编辑工作。

这个软件需要执行如下三种操作：

- 更改国内债务数值在某一位上的值。
- 更改国际债务数值在某一位上的值。
- 输出总公共债务在某一位上的值。

## 说明/提示

【样例解释#1】：

最初公共债务总额为 $7341+150=7491$，因此第三位上的值为 $4$。

在操作 $2$ 后，公共债务总额为 $7041+150=7191$，因此第三位上的值为 $1$。

在操作 $4$ 后，公共债务总额为 $7041+159=7200$，因此第一位上的值为 $0$，第三位上的值为 $2$。

【数据范围】：

所有测试点均满足：$2 \leq n \leq 10^5$，$1 \leq z \leq 10^5$。

|子任务编号|约束|分值|
|:-:|:-:|:-:|
|$1$|$n,z\leq5\times10^3$|$30$|
| $2$|任何时刻，国内债务和国际债务的每个位上的数字都是 $0$ 或 $5$|$20$|
| $3$|无附加约束|$50$|



## 样例 #1

### 输入

```
5 6
7341
0150
S 3
W 3 0
S 3
Z 1 9
S 1
S 3```

### 输出

```
4
1
0
2```

## 样例 #2

### 输入

```
10 100
627280304
679703557
Z 9 9
Z 2 5
S 3
S 3
W 6 2
W 9 6
Z 6 2
Z 3 9
S 7
Z 5 9
S 3
S 6
S 8
Z 3 2
W 5 1
Z 4 5
W 5 8
S 1
W 4 7
W 8 7
S 9
Z 5 7
S 8
W 5 5
S 6
W 9 9
W 8 0
S 1
S 8
W 8 7
S 9
W 2 4
W 5 7
S 4
Z 6 0
Z 8 2
W 8 2
S 2
W 5 7
W 4 7
W 1 4
W 2 9
S 3
W 8 3
W 5 2
Z 4 2
W 5 9
W 8 3
W 6 6
S 6
W 6 8
Z 7 4
S 5
W 9 9
W 9 6
S 10
W 7 8
Z 1 5
Z 3 4
S 5
S 2
W 9 9
W 3 0
Z 9 4
Z 1 1
Z 5 9
W 7 2
S 3
S 5
W 3 6
Z 4 7
S 7
Z 5 4
S 7
S 1
W 2 8
Z 1 7
W 3 6
W 8 4
S 7
Z 8 8
Z 5 0
W 8 9
W 7 1
S 2
W 2 7
S 2
W 2 5
Z 5 0
W 9 8
W 4 5
Z 2 8
S 5
S 2
Z 2 7
S 1
S 1
W 8 1
W 4 8
Z 7 2```

### 输出

```
8
8
6
2
5
0
1
6
5
5
1
8
9
2
0
6
7
6
1
6
4
5
8
6
6
5
6
4
3
0
4
1
1```

# 题解

## 作者：dream10 (赞：0)

## Preface

目前的两篇题解要么渐进复杂度不如我，要么常数不如我。

@happybob @Alex_Eon

## Hint

两个数相加，最多进几位？

修改的本质是什么？

查询的时候除了对应位置的数值，还需要知道什么？

怎么快速计算进位？

## Solution

### Step 1

发现两个数相加，最多进一位。修改也不过是改 $a_i+b_i$，查询只需要知道比当前这一位低的数中是否进位。

于是用线段树维护这段区间的 $d_i(i\in\{ 0,1\})$，表示是否被进位下是不是向前进位，合并直接复合。

难度不高，详见代码。

```
#include<bits/stdc++.h>
using namespace std;

int n,m;
const int MAXN=100010;
int a[MAXN];
int b[MAXN];
struct Node{
    int d[2];
}t[MAXN<<2];
Node operator + (Node A,Node B){
    Node C;
    C.d[0]=B.d[A.d[0]];
    C.d[1]=B.d[A.d[1]];
    return C;
}
#define mid ((L+R)>>1)
void build(int x,int L=1,int R=n){
    if(L==R){
        t[x].d[0]=a[L]+b[L]+0>=10;
        t[x].d[1]=a[L]+b[L]+1>=10;
    }else{
        build(x<<1,L,mid);
        build(x<<1|1,mid+1,R);
        t[x]=t[x<<1]+t[x<<1|1];
    }
}
void upd(int x,int pos,int L=1,int R=n){
    if(L==R){
        t[x].d[0]=a[L]+b[L]+0>=10;
        t[x].d[1]=a[L]+b[L]+1>=10;
    }else{
        if(pos<=mid)upd(x<<1,pos,L,mid);
        else upd(x<<1|1,pos,mid+1,R);
        t[x]=t[x<<1]+t[x<<1|1];
    }
}
Node res;
void qry(int x,int l,int r,int L=1,int R=n){
    if(l<=L&&R<=r){
        res=res+t[x];
    }else{
        if(l<=mid)qry(x<<1,l,r,L,mid);
        if(r>mid)qry(x<<1|1,l,r,mid+1,R);
    }
}
#undef mid
signed main(){
    cin>>n>>m;
    for(int i=2;i<=n;++i){
        char c;cin>>c;
        a[i]=c-'0';
    }
    for(int i=2;i<=n;++i){
        char c;cin>>c;
        b[i]=c-'0';
    }
    reverse(a+2,a+n+1);
    reverse(b+2,b+n+1);
    build(1);
    char op;int i,c;
    while(m--){
        cin>>op>>i;
        ++i;
        if(op=='W'){
            cin>>c;
            a[i]=c;
            upd(1,i);
        }else if(op=='Z'){
            cin>>c;
            b[i]=c;
            upd(1,i);
        }else{
            res.d[0]=0;
            res.d[1]=0;
            qry(1,1,i-1);
            printf("%d\n",(a[i]+b[i]+res.d[0])%10);
        }
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

怎么网上搜到的题解都是分块的。单 $\log$ 做法好想好写好调。

首先操作 $1$ 和 $2$ 本质等价。先计算两数之和，问题等价于有一个十进制数，要维护加减 $10^i$，询问某一位的值。

直接模拟进位退位，这个是很经典的线段树二分。线段树上维护区间最小最大值，每次加减都可以转为寻找一段中第一个不等于 $0$ 或 $9$ 的。然后还要支持区间覆盖，很容易实现。复杂度 $O(n \log n)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#include <set>
using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N], c[N], m;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, minn, maxn, tag;
	}tr[N << 2];
	void pushtag(int u, int t)
	{
		tr[u].tag = tr[u].minn = tr[u].maxn = t;
	}
	void pushdown(int u)
	{
		if (~tr[u].tag)
		{
			pushtag(u << 1, tr[u].tag);
			pushtag(u << 1 | 1, tr[u].tag);
			tr[u].tag = -1;
		}
	}
	void pushup(int u)
	{
		tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
	}
	void build(int u, int l, int r, int* c)
	{
		tr[u] = { l, r, c[r], c[r], -1 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid, c);
		build(u << 1 | 1, mid + 1, r, c);
		pushup(u);
	}
	inline int query(int u, int x)
	{
		if (tr[u].r < x) return -1;
		if (tr[u].minn == 9 && tr[u].maxn == 9) return -1;
		if (tr[u].l == tr[u].r)
		{
			return tr[u].l;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (x > mid)
		{
			return query(u << 1 | 1, x);
		}
		else
		{
			int v = query(u << 1, x);
			if (v != -1) return v;
			return query(u << 1 | 1, x);
		}
	}
	inline int query0(int u, int x)
	{
		if (tr[u].r < x) return -1;
		if (tr[u].minn == 0 && tr[u].maxn == 0) return -1;
		if (tr[u].l == tr[u].r)
		{
			return tr[u].l;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (x > mid)
		{
			return query0(u << 1 | 1, x);
		}
		else
		{
			int v = query0(u << 1, x);
			if (v != -1) return v;
			return query0(u << 1 | 1, x);
		}
	}
	inline int querypos(int u, int x)
	{
		if (tr[u].l == tr[u].r) return tr[u].minn;
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) return querypos(u << 1, x);
		return querypos(u << 1 | 1, x);
	}
	inline void update(int u, int l, int r, int c)
	{
		if (l > r) return;
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag(u, c);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, c);
		if (r > mid) update(u << 1 | 1, l, r, c);
		pushup(u);
	}
}sgt;

string s;

inline void add(int u, int x)
{
	if (!x) return;
	int res = sgt.querypos(1, u);
	if (res + x <= 9)
	{
		sgt.update(1, u, u, res + x);
		return;
	}
	int pos = sgt.query(1, u + 1);
	int rv = sgt.querypos(1, pos);
	sgt.update(1, pos, pos, rv + 1);
	sgt.update(1, u + 1, pos - 1, 0);
	sgt.update(1, u, u, res + x - 10);
}

inline void dminus(int u, int x)
{
	if (!x) return;
	int res = sgt.querypos(1, u);
	if (res >= x)
	{
		sgt.update(1, u, u, res - x);
		return;
	}
	int pos = sgt.query0(1, u + 1);
	int rv = sgt.querypos(1, pos);
	sgt.update(1, pos, pos, rv - 1);
	sgt.update(1, u + 1, pos - 1, 9);
	sgt.update(1, u, u, res + 10 - x);
}

inline void modify(int x, int v)
{
	if (v > 0) add(x, v);
	else dminus(x, -v);
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	cin >> s;
	int r = s.size() - 1;
	for (int i = 1; i < n; i++) a[i] = s[r--] - '0';
	cin >> s;
	r = s.size() - 1;
	for (int i = 1; i < n; i++) b[i] = s[r--] - '0';
	for (int i = 1; i < n; i++)
	{
		c[i] += a[i] + b[i];
		if (c[i] >= 10)
		{
			c[i + 1]++, c[i] -= 10;
		}
	}
	sgt.build(1, 1, n, c);
	while (m--)
	{
		char op;
		cin >> op;
		if (op == 'W')
		{
			int x, c;
			cin >> x >> c;
			modify(x, c - a[x]);
			a[x] = c;
		}
		else if (op == 'Z')
		{
			int x, c;
			cin >> x >> c;
			modify(x, c - b[x]);
			b[x] = c;
		}
		else
		{
			int i;
			cin >> i;
			cout << sgt.querypos(1, i) << "\n";
		}
	}
	return 0;
}
```

---

## 作者：Alex_Eon (赞：0)

#### [$\color{red}博客内食用效果更佳（点我）$](https://www.luogu.com.cn/blog/Ksy/solution-p9297)

### 主体思路：分块
### 复杂度：$O(n\sqrt n)$
### 完整思路

单点修改单点询问，这里采用分块乱搞。

对于一个块，在内部不被修改的情况下，只有上一个块进不进位会影响贡献，我们考虑直接维护上一个块进位时与不进位时，这个块的两种状态，再记录一下这个块每个状态下对不对下一个块进位。

单点修改时只会影响一个块的贡献，暴力重构即可；查询时只需从前向后跳块即可找到这个块的真实状态，直接输出即可。

### 代码实现需要注意的地方：

- 输入的字符串从左到右为高位到低位，存储的时候需要倒序存储。

### 参考代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define UN unsigned
using namespace std;
//--------------------//
//IO
inline int rd()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
//--------------------//
const int N=1e5+5,B=330;

int n,m;
char sa[N],sb[N];
int a[N],b[N];

int len,bcnt,bl[N],go[B][2],val[N][2];
int l[B],r[B];

void build(int now)//暴力重构
{
    for(int t,d=0;d<=1;d++)//枚举上一个块是否进位
    {
        t=d;
        for(int i=l[now];i<=r[now];i++)
        {
            val[i][d]=a[i]+b[i]+t;
            if(val[i][d]>=10)
                t=1,val[i][d]-=10;
            else
                t=0;
        }
        go[now][d]=t;//记录这个块要不要向下进位
    }
    return;
}

void init()//预处理信息
{
    int len=sqrt(n);
    for(int i=1;i<=n;i++)
        bl[i]=((bl[i-1]*len+1)==i)?++bcnt:bcnt;//每个点处于哪个块中
    for(int i=1;i<=bcnt;i++)
        l[i]=(i-1)*len+1,r[i]=min(len*i,n),build(i);
    return;
}

void query(int x)
{
    int t=0;
    for(int i=1;i<bl[x];i++)//从前向后跳块记录状态
        t=go[i][t];
    printf("%d\n",val[x][t]);
    return;
}
//--------------------//
int main()
{
    scanf("%d%d%s%s",&n,&m,sa+1,sb+1);
    for(int i=1;i<n;i++)
        a[i]=sa[n-i]-'0',b[i]=sb[n-i]-'0';//注意读入的时候要转倒叙
    init();
    char op[5];
    for(int x,y,i=1;i<=m;i++)
    {
        scanf("%s%d",op,&x);
        if(op[0]=='S')
        {
            query(x);
            continue;
        }
        scanf("%d",&y);
        if(op[0]=='W')
            a[x]=y;
        else
            b[x]=y;
        build(bl[x]);
    }
    return 0;
}
```

---

