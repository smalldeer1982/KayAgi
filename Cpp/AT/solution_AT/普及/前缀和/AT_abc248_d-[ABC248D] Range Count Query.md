# [ABC248D] Range Count Query

## 题目描述

给定一个长度为$N$的序列 $A=(A 
1
​	
 ,…,A 
N
​	
 )$ 
以及$Q$组询问，每组询问包括： $L,R,X$ 
三个整数。

请你求出在 $A 
L
​	
 , …,A 
R
​	
$
中，值等于 $X$ 的数有多少个。

## 说明/提示

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- 对于每一组询问， $ 1\le\ L\ \leq\ R\ \leq\ N,\ 1\ \leq\ X\ \leq\ N $
- 输入数据均为整数

## 样例 #1

### 输入

```
5
3 1 4 1 5
4
1 5 1
2 4 3
1 5 2
1 3 3```

### 输出

```
2
0
0
1```

# 题解

## 作者：FFTotoro (赞：3)

本题可以使用二分算法。

具体地，用一个二维数组 $v$ 来存储每个数在数列中的位置。例如，数列为 $1,2,3,2,6$，那么 $v_2=\{2,4\}$。

每次询问，就用二分算法找到 $v_X$ 中大于等于 $L$ 的第一个数以及**大于** $R$ 的第一个数。将两个数的下标相减，即为区间中包含 $X$ 的个数。二分可以使用 `lower_bound` 和 `upper_bound` 实现。

放代码：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int a[200001];
vector<int> v[200001];
int main(){
    ios::sync_with_stdio(false);
    int n; cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],v[a[i]].push_back(i);
    int q; cin>>q;
    while(q--){
        int l,r,x,c=0; cin>>l>>r>>x;
        int ll=lower_bound(v[x].begin(),v[x].end(),l)-v[x].begin(),\
            rr=upper_bound(v[x].begin(),v[x].end(),r)-v[x].begin();
        cout<<rr-ll<<endl;
    }
    return 0;
}
```

---

## 作者：chengning0909 (赞：1)

# abc 248 d

[AT 链接](https://atcoder.jp/contests/abc248/tasks/abc248_d)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc248_d)

## 题意

给定一个长度为 $n$ 的序列 $A$，有 $Q$ 次询问，每次询问给定三个整数 $l, r, x$，请你求出在 $A_l \sim A_r$ 中有多少个值等于 $x$ 的数。

## 思路

### 暴力

每次询问直接暴力从 $l$ 循环到 $r$，统计数量。

### 正解

对于每个 $i \ (1 \le x \le n)$，都用一个 `vector` 记录它的所有出现位置，我们把这个 `vector` 称为 $pos_i$，并且需要保证每个 $pos_i$ 内部是单调的。

对于每次询问，二分查找 $pos_x$ 中第一个大于等于 $l$ 和第一个大于 $r$ 的数，并将两个的下标相减即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, a[N], q, l, r, x;
vector<int> pos[N];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pos[a[i]].push_back(i);
  }
  cin >> q;
  for (int i = 1; i <= q; i++) {
    cin >> l >> r >> x;
    auto _r = upper_bound(pos[x].begin(), pos[x].end(), r);
    auto _l = lower_bound(pos[x].begin(), pos[x].end(), l);
    cout << _r - _l << '\n';
  }
  return 0;
}
```

---

## 作者：yhylivedream (赞：0)

考虑用二分来求解。

## 【思路】：

对于每一个 $1$ 到 $n$ 的数，都用一个向量来存其每次出现的下标，而查询时用二分查找，查第一个大于等于 $l$ 和大于 $r$ 的位置，相减既是答案，因为其中间的必符合要求。

这里的二分查找不必手写，可以调用 STL 中的函数：

- `bin_search(数组名 + 1, 数组名 + 元素个数 + 1, 查找元素)`：如果给定数组中有查找元素，返回最早出现的下标，否则返回 $-1$。

- `lower_bound(数组名 + 1, 数组名 + 元素个数 + 1, 查找元素) - 数组名`：查找第一个大于等于查找元素的值的下标。

- `upper_bound(数组名 + 1, 数组名 + 元素个数 + 1, 查找元素) - 数组名`：查找第一个大于（注意没有等于）查找元素的值的下标。

## 【代码】：

懒得贴了，完结撒花。

---

## 作者：loser_seele (赞：0)

你说得对，但是我太菜了想不到正解，于是就套了个板子。

参考 [这题](https://www.luogu.com.cn/blog/Karry5307/solution-sp3266) 的思路，观察到区间内 $ =x $ 的数相当于 $ >x-2 $ 的答案减去 $ >x-1 $ 的答案（转化为 $ \geq x-1 $ 减去 $ \geq x $，是一个前缀和的形式，这是显然的）。如果将所有数集体 $ +1 $ （为了方便处理负下标），那么就转化为 $ >x-1 $ 的答案减去 $ >x $ 的答案。于是套用这题的板子即可。

那么考虑这题怎么做，借鉴了 [卡老师的题解](https://www.luogu.com.cn/blog/Karry5307/solution-sp3266)，离线做法。不懂的也可以翻这篇。

首先插入所有数，然后将所有大于 $ x $ 的数插入进来统计答案。因为朴素做法要支持删除操作所以困难，但可以不删除，按 $ x $ 的大小排序后从小到大插入即可，这样就不需要删除了。

单点修改区间求和，这里用了 LCT 实现，时间复杂度 $ \mathcal{O}(m\log{n}) $，可以通过。注意非正数下标的处理即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=4e5+51;
const int maxn=4e5+10;
const ll mod=1e9;
int n,q,u,v,c;
char op;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]])%mod;
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]])%mod;
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]])%mod,val[ch[x][0]]=(val[ch[x][0]]*mul[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]*mul[x])%mod,add[ch[x][0]]=(add[ch[x][0]]*mul[x])%mod;
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]])%mod,val[ch[x][1]]=(val[ch[x][1]]*mul[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]*mul[x])%mod,add[ch[x][1]]=(add[ch[x][1]]*mul[x])%mod;
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x])%mod,val[ch[x][0]]=(val[ch[x][0]]+add[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]])%mod;
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x])%mod,val[ch[x][1]]=(val[ch[x][1]]+add[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]])%mod;
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }
    void final_mul(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = val[v] * c % mod;
      sum[v] = sum[v] * c % mod;
      mul[v] = mul[v] * c % mod;
    }
    void final_add(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = (val[v] + c) % mod;
      sum[v] = (sum[v] + siz[v] * c % mod) % mod;
      add[v] = (add[v] + c) % mod;
    }
    int query1(int u,int v)
    {
    if(v==0)
    return 0;
    makeroot(u), access(v), splay(v);
    return sum[v];
    }
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
    void cut(int u,int v)
    {
    makeroot(u);
      access(v);
      splay(v);
      if (ch[v][0] == u && !ch[u][1]) 
      ch[v][0] = fa[u] = 0;
    }
    bool query2(int u,int v)
    {
    return find(u) == find(v);
    }
}st;
int find(int x)
{
return st.find(x);
}
void merge(int u,int v)
{
st.link(u,v);
}
void clean(int n)
{
for(int i=1;i<=n;i++)
st.clear(i),st.maintain(i),st.splay(i);
}//main
struct Item{
	ll val,id;
	inline bool operator <(const Item &rhs)const
	{
		return val>rhs.val;
	}
};
struct Query{
	ll l,r,val,id;
	inline bool operator <(const Query &rhs)const
	{
		return val>rhs.val;
	}
};
Item it[MAXN];
Query qry[MAXN];
ll qcnt,l,r,x,ptr;
ll res[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read();
    clean(4e5);
    for(int i=1;i<=4e5-1;i++)
    merge(i,i+1);
	for(register int i=1;i<=n;i++)
	{
		x=read(),x++,it[i]=(Item){x,i};
	}
	qcnt=read();
    qcnt*=2;
	for(register int i=1;i<=qcnt;i++)
	{
		l=read(),r=read(),x=read(),qry[i]=(Query){l,r,x,i};
        i++;
        int lstl=l,lstr=r,lstx=x;
        l=lstl,r=lstr,x=lstx,x++,qry[i]=(Query){l,r,x,i};
        //cout<<l<<' '<<r<<' '<<x<<'\n';
	}
    //=x -> (>x-1) - (>x)
	sort(it+1,it+n+1),sort(qry+1,qry+qcnt+1),ptr=1;
	for(register int i=1;i<=qcnt;i++)
	{
		while(it[ptr].val>qry[i].val)
		{
			st.final_add(it[ptr].id,it[ptr].id,1),ptr++;
		}
		res[qry[i].id]=st.query1(1,qry[i].r)-st.query1(1,qry[i].l-1);
	}
	for(register int i=1;i<=qcnt;i+=2)
	{
		printf("%d\n",res[i]-res[i+1]);
	}
}

```


---

## 作者：WaterSun (赞：0)

# 思路

其实很简单，我们可以将所有数值相同的值的下标存入一个 `vector` 里面。因为，我们既然要查找 $X$，不妨把所有值为 $X$ 的下标存在一起，方便查找。（可以在输入的时候完成）

我们不妨在每一个数值后面添加一个哨兵，然后二分查找第一个大于等于 $l$ 的数和第一个大于等于 $r + 1$ 的数，再把两数相减即为答案。

这时候，哨兵的作用就体现出来了，如果我们的第二个数取到了哨兵，那么说明 $l \sim r$ 是在最后的，我们将它设为 $\operatorname{size}(v_x) + 1$ 即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,inf = 1e6 + 10;
int n,q,Max;
vector<int> v[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		Max = max(Max,x);
		v[x].push_back(i);
	}
	for (re int i = 1;i <= Max;i++) v[i].push_back(inf);//哨兵 
	q = read();
	while (q--){
		int l,r,x;
		l = read();
		r = read();
		x = read();
		int a = lower_bound(v[x].begin(),v[x].end(),l) - v[x].begin();//二分查找 
		int b = lower_bound(v[x].begin(),v[x].end(),r + 1) - v[x].begin();//这里貌似也可以用 upper_bound 
		if (b == inf) b = v[x].size() + 1;//取到哨兵 
		printf("%d\n",b - a);//输出结果 
	}
	return 0;
}
```

---

## 作者：Lemonlwl (赞：0)

## AT_abc248_d [ABC248D] Range Count Query 题解
### 题意：
给定一个长度为 $N$ 的序列，对于 $Q$ 次询问，在 $L$ 到 $R$ 的范围内查找 $X$ 的个数。

------------

### 分析：
本题枚举显然超时，应该使用二分查找的方法。

1. 将序列中的每一个数当作下标，把这个数所对应的下标存进 ```vector``` 数组中，即记录每个数出现的次数以及位置。

1. 接下来用二分查找的方法查找每一个数所对应的下标即 ```vector``` 里第一个大于 $R$ 的值和第一个大于等于 $L$ 的值，然后将两个地址相减就能得到在 $L$ 到 $R$ 的范围内的这个数的下标个数，即这个数在此范围内出现的次数。

```upper_bound(l,r,x)```：在从 $l$ 到 $r$ 的范围内查找第一个大于 $x$ 的值的地址。

```lower_bound(l,r,x)```：在从 $l$ 到 $r$ 的范围内查找第一个大于等于 $x$ 的值的地址。

------------

附上 [AC](https://www.luogu.com.cn/record/118226516) 代码：
```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n,q,t;
vector<int> v[1000005];  //用来存储每个数每次出现的下标。
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t;
		v[t].push_back(i);  //将这个数出现的下标存进vector。
	}  //输入。
	cin>>q;
	while(q--){  //q次询问。
		int l,r,x;
		cin>>l>>r>>x;
		cout<<upper_bound(v[x].begin(),v[x].end(),r)-lower_bound(v[x].begin(),v[x].end(),l)<<endl;
		//这个数在l到r的范围内下标的个数，即出现的次数。
	}
	return 0;
}
```


---

