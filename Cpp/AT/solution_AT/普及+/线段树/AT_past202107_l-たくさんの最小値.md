# たくさんの最小値

## 题目描述

维护一个长为 $n$ 的数组 $a$。对其进行 $q$ 次操作。第 $i$ 次操作输入三个整数 $t_i,x_i,y_i$。按如下规则操作：

- $t_i=1$ 时：将 $a_{x_i}$ 的值改为 $y_i$。此时，$1 \le x_i \le n$，$0 \le y_i \le 10^9$。
- $t_i=2$ 时：找出 $[x_i,y_i]$ 区间内的最小值，将其记为 $p$，输出所有满足以下两个条件的整数 $j$：
> - $x_i \le j \le y_i$；
>
> - $a_j=p$。
- 此时，$1 \le x_i \le y_i \le n$。

## 样例 #1

### 输入

```
6 7
3 20 3 10 15 10
2 1 6
2 4 5
1 3 10
1 1 1000000000
2 1 6
1 5 0
2 1 6```

### 输出

```
2 1 3 
1 4 
3 3 4 6 
1 5```

# 题解

## 作者：fkxr (赞：6)

~~我非常喜欢暴力数据结构，所以用分块把这题过了~~

[题目](https://www.luogu.com.cn/problem/AT_past202107_l)中有两种操作：

一种是区间查询最小值个数和每个的下标，考虑分块维护块内每个最小值的下标，每次查询先算出区间的最小值，看块内的最小值是否等于最小值，如果小于那答案就加上块内每个最小值的下标，块外元素暴力求解。

另一种是单点修改，注意到某个值的更改之关系到它所在的块，只用暴力扫一遍就行。

Code：
```
#include <bits/stdc++.h>
using namespace std;
int n,m,len,id[200005];
bool x[1003];
struct node{
    int a,id;
};
int a[200005];
vector <node>e[1003];//块内每个最小值的值，下标
int minn=0;
inline void cm(int l,int r){//[r,l]之间的最小值
    int q=id[l];
    int w=id[r];
    if(q==w){
        for(int i=l;i<=r;++i){
            minn=min(minn,a[i]);
        }
        return;
    }
    for(int i=l;id[i]==q;++i){
        minn=min(minn,a[i]);
    }
    for(int i=r;id[i]==w;--i){
        minn=min(minn,a[i]);
    }
    for(int i=q+1;i<w;++i){
        minn=min(minn,e[i][0].a);
    }
}

inline void Q(int l,int r){//查询
    minn=1147483647;
    cm(l,r);
    vector <int>ans;//记录答案
    int q=id[l],w=id[r];
    if(q==w){
        for(int i=l;i<=r;++i){
            if(a[i]==minn){
                ans.push_back(i);
            }
        }
    }else{
        for(int i=l;id[i]==q;++i){
            if(a[i]==minn){
                ans.push_back(i);
            }
        }
        for(int i=q+1;i<w;i++){
            for(auto j:e[i]){
                if(j.a!=minn){//没有区间最小值
                    break;
                }
                ans.push_back(j.id);
            }
        }
        for(int i=w*len;id[i]==w&&i<=r;++i){
            if(a[i]==minn){
                ans.push_back(i);
            }
        }
    }
    cout<<ans.size();
    putchar(' ');
    for(auto i:ans){
        cout<<i+1;//某人数组下标从1开始
        putchar(' ');
    }
    putchar('\n');
}
inline int rr(){//快读
    int a=0;
    char ch=getchar();
    for(;!(ch>='0'&&ch<='9');){
        ch=getchar();
    }
    for(;ch>='0'&&ch<='9';){
        a=(a<<1)+(a<<3)+(ch^48);
        ch=getchar();
    }
    return a;
}
signed main() {
    n=rr(),m=rr();
    len=sqrt(n);
    int t=len+min(1,n-len*len);//块数
    for(int i=0;i<n;++i){
        a[i]=rr();
        id[i]=i/len;
    }
    for(int idd=0;idd<t;++idd){
        e[idd].clear();
        e[idd].push_back({a[idd*len],idd*len});
        for(int i=idd*len+1;id[i]==idd;i++){
            if(e[idd].size()==0){//数组没数，直接成为最小值
                e[idd].push_back({a[i],i});
                continue;
            }
            if(a[i]<e[idd][0].a){//找到更小的值
                e[idd].clear();
                e[idd].push_back({a[i],i});
                continue;
            }
            if(a[i]==e[idd][0].a){//和最小值一样
                e[idd].push_back({a[i],i});
                continue;
            }
        }
    }
    for(;m--;){
        int op,l,r;
        op=rr(),l=rr(),r=rr();
        if(op==1){
            a[l-1]=r;
            int idd=id[l-1];//同上
            e[idd].clear();
            e[idd].push_back({a[idd*len],idd*len});
            for(int i=idd*len+1;id[i]==idd;i++){
                if(e[idd].size()==0){
                    e[idd].push_back({a[i],i});
                    continue;
                }
                if(a[i]<e[idd][0].a){
                    e[idd].clear();
                    e[idd].push_back({a[i],i});
                    continue;
                }
                if(a[i]==e[idd][0].a){
                    e[idd].push_back({a[i],i});
                    continue;
                }
            }
        }else{
            Q(l-1,r-1);
        }
    }
	return 0;
}
//显然修改和查询都是O(sqrt(n))的，所以整体时间复杂度为O(能过)，O(nsqrt(n))

```
[通过记录](https://www.luogu.com.cn/record/185586571)

---

## 作者：The_foolishest_OIer (赞：5)

## Solve

一道非常适合新手的线段树的题（[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_l#submit)）。

### Part 1

建树部分还是比较好写的，自上向下的建树。

参考代码：


```cpp
void build (int o,int l,int r){
	if (l == r) sum[o] = a[r];
	else{
		int mid = (l + r) >> 1; // 取中间值
		build (o * 2,l,mid); // 建立左子树
		build (o * 2 + 1,mid + 1,r); // 建立右子树
		sum[o] = min(sum[o * 2],sum[o * 2 + 1]);
	}
}
```

### Part 2

单点修改的话，我们可以判断，当中间值在要修改的位置右边时，往左子树上找，否则往右子树上找。

如果 $l$ 和 $r$ 的值相等的时候，就说明我们找到了这个点，直接将这个点修改为 $y_i$。

参考代码：


```cpp
void update (int o,int l,int r){
	if (l == r) sum[o] = y; // 修改
	else{
		int mid = (l + r) >> 1;
		if (x <= mid) update(o * 2,l,mid); // 遍历左子树
		else update (o * 2 + 1,mid + 1,r); // 遍历右子树
		sum[o] = min(sum[o * 2],sum[o * 2 + 1]);
	}
}
```

### Part 3-1

查询最小值也是比较好写的，如果这个区间完全被要查找的区间覆盖，直接返回该区间的最小值。

如果中间值在 $x_i$ 的右边时，遍历左子树，如果中间值在 $y_i$ 的左边时，遍历右子树。

参考代码：


```cpp
int query (int o,int l,int r){
	if (x <= l && r <= y) return sum[o]; // 如果这个区间完全被要查找的区间覆盖，直接返回值
	int mid = (l + r) >> 1;
	int ans = INF;
	if (x <= mid) ans = min(ans,query(o * 2,l,mid)); // 遍历左子树
	if (y > mid) ans = min(ans,query(o * 2 + 1,mid + 1,r)); // 遍历右子树
	return ans;
}
```

### Part 3-2

查询区间内多重最小值的位置是本题最大的难点。

当这个区间完全被要查找的区间覆盖，直接判断该区间的最小值是不是所求的值。

当这个区间长度为 $1$ 时，记录这个位置。

否则继续遍历左右子树。

参考代码：


```cpp
void find (int o,int l,int r){
	if (x <= l && r <= y && sum[o] != p){ // 判断
		return;
	}
	if (l == r){ // 记录
		m++;
		s[m] = l;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) find(o * 2,l,mid);
	if (y > mid) find(o * 2 + 1,mid + 1,r);
}
```

### Part 4

主函数里基本上就是写一些读入和输出，每次操作前记得初始化。

### AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 * 4 + 100;
const int INF = 2e9 + 100;
int a[maxn],sum[maxn],op,x,y,p;
int n,q,m;
int s[maxn];
void build (int o,int l,int r){
	if (l == r) sum[o] = a[r];
	else{
		int mid = (l + r) >> 1;
		build (o * 2,l,mid);
		build (o * 2 + 1,mid + 1,r);
		sum[o] = min(sum[o * 2],sum[o * 2 + 1]);
	}
}
void update (int o,int l,int r){
	if (l == r) sum[o] = y;
	else{
		int mid = (l + r) >> 1;
		if (x <= mid) update(o * 2,l,mid);
		else update (o * 2 + 1,mid + 1,r);
		sum[o] = min(sum[o * 2],sum[o * 2 + 1]);
	}
}
int query (int o,int l,int r){
	if (x <= l && r <= y) return sum[o];
	int mid = (l + r) >> 1;
	int ans = INF;
	if (x <= mid) ans = min(ans,query(o * 2,l,mid));
	if (y > mid) ans = min(ans,query(o * 2 + 1,mid + 1,r));
	return ans;
}
void find (int o,int l,int r){
	if (x <= l && r <= y && sum[o] != p){
		return;
	}
	if (l == r){
		m++;
		s[m] = l;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) find(o * 2,l,mid);
	if (y > mid) find(o * 2 + 1,mid + 1,r);
}
int main(){
	cin >> n >> q;
	for (int i = 1 ; i <= n ; i++) cin >> a[i];
	build (1,1,n);
	for (int i = 1 ; i <= q ; i++){
		cin >> op >> x >> y;
		if (op == 1){
			update (1,1,n);
		}else{
			m = 0;
			p = query (1,1,n);
			find (1,1,n);
			cout << m << ' ';
			for (int j = 1 ; j <= m ; j++) cout << s[j] << ' ';
			cout << endl;
		}
	}
	return 0;
} 
```

感谢你的收看！

---

## 作者：sfb1363II (赞：4)

## Solution
用线段树维护区间最小值。
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,q;
int tot,res[N];
struct tree{
    int l,r,pre;
}t[N<<2];//线段树
void build(int p,int l,int r){//建树
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        cin>>t[p].pre;
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    t[p].pre=min(t[p<<1].pre,t[p<<1|1].pre);
}
void change(int p,int x,int k){//单点修改
    if(t[p].l==t[p].r){
        t[p].pre=k;
        return;
    }
    int mid=(t[p].l+t[p].r)>>1;
    if(x<=mid) change(p<<1,x,k);
    else change(p<<1|1,x,k);
    t[p].pre=min(t[p<<1].pre,t[p<<1|1].pre);
}
int ask(int p,int l,int r){//区间查询
    if(t[p].l>=l&&t[p].r<=r)
        return t[p].pre;
    int res=1e9,mid=(t[p].l+t[p].r)>>1;
    if(l<=mid) res=min(res,ask(p<<1,l,r));
    if(r>mid) res=min(res,ask(p<<1|1,l,r));
    return res;
}
void find(int p,int l,int r,int k){//查找
    if(t[p].pre<=k){
        if(t[p].l==t[p].r){
            res[++tot]=t[p].l;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(l<=mid) find(p<<1,l,r,k);
        if(r>mid) find(p<<1|1,l,r,k);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    build(1,1,n);
    while(q--){
        int opt;
        cin>>opt;
        if(opt==1){
            int x,y;
            cin>>x>>y;
            change(1,x,y);
        }
        else{
            int x,y;
            cin>>x>>y;
            int t=ask(1,x,y);
            tot=0;
            find(1,x,y,t);
            cout<<tot<<" ";
            for(int i=1;i<=tot;i++)
                cout<<res[i]<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Wsl886 (赞：3)

## 分析题意

共有两个操作。

第一个操作是单点修改。

第二个是查询区间最小值并找出它的下标。

就是一道线段树板子题，唯一的不同就在于有一个 find 函数，它是根据数值找下标。

## 下面给出参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
struct node{
	int l;
	int r;
	int mi;
}tr[N*4]; 
int a[N];

void pushup(int u)
{
	tr[u].mi=min(tr[u<<1].mi,tr[u<<1|1].mi);
}

void build(int u,int l,int r)
{
	tr[u]={l,r};
	if(l==r)
	{
		tr[u].mi=a[l];  
	}
	else
	{
		int mid=(l+r)>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		pushup(u);
	}

}

void modify(int u,int x,int d)
{
	if(tr[u].l==tr[u].r) {
		tr[u].mi=d; 
		return;
	}
	else
	{
		int mid=(tr[u].l+tr[u].r)>>1;
		if(x<=mid) modify(u<<1,x,d);
		else modify(u<<1|1,x,d);
		pushup(u);
	}
}

int query(int u,int l,int r)
{
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].mi;
	int mid=(tr[u].l+tr[u].r)>>1;
	int v=1e9+10;
	if(l<=mid) v=min(v,query(u<<1,l,r));
	if(r>mid) v=min(v,query(u<<1|1,l,r));
	return v;
}

int k,s[N];
void find(int u,int l,int r,int p)
{
	if(l<=tr[u].l&&tr[u].r<=r&&tr[u].mi!=p)
	{
		return;
	}
	if(tr[u].l==tr[u].r&&tr[u].mi==p)
	{
		s[++k]=tr[u].l;
		return;
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid) find(u<<1,l,r,p);
	if(r>mid) find(u<<1|1,l,r,p);
}

int main(){
	int n,q;
	cin>>n>>q;

	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}	
	build(1,1,n);
		for(int i=1;i<=q;i++)
	{
		int t,x,y;
		cin>>t>>x>>y;
		if(t==1)
		{
			modify(1,x,y);
		}
		else
		{
			int p=query(1,x,y);
			k=0;
			find(1,x,y,p);
			cout<<k<<" ";
			for(int j=1;j<=k;j++) cout<<s[j]<<" ";
			cout<<"\n";
		}
	}
	return 0;
}

```

### 结尾
每一个故事都应有一个完美的结局。
欢迎大佬指出错误。

---

## 作者：SamHH0912 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_l)

### Solution

使用线段树维护数组 $a$。主函数部分的参考代码会在文末完整展示。

### Part 0：输入数组，建树

本题解展示的参考代码中使用“自上而下”的顺序建树。下面是 `build` 函数的参考代码：

```cpp
const int N=200007;
int a[N];
struct node{int l,r,Min;}t[N<<2];//区间左、右端点和最小值

#define L(x) x<<1//左儿子编号
#define R(x) x<<1|1//右儿子编号

inline void Push_U(int x){//更新区间最小值
	t[x].Min=min(t[L(x)].Min,t[R(x)].Min);
}

inline void build(int x,int l,int r){//递归建树
	t[x]={l,r,0};
	if(l<r){//若区间长大于 1
		int mid=(l+r)>>1;
		build(L(x),l,mid),build(R(x),mid+1,r);
		Push_U(x);
	}
	else t[x].Min=a[l];//否则直接填上
}
```

### Part 1：单点修改

尽管本题是单点修改和区间查询，但笔者鉴于树状数组较难操作，所以选用了线段树这一数据结构。

单点修改的函数很简单：若区间长为 $1$，则直接修改即可；否则，求出左儿子和右儿子的区间，分别判断是否包含了位置 $x$。若包含，则选择该儿子并继续递归，直至区间长为 $1$ 为止。**请时刻记住，在修改函数中，返回时必须更新当前节点的最小值。**

下面是参考代码：

```cpp
inline void modify(int pos,int x,int y){
	if(t[pos].l==t[pos].r) {t[pos].Min=y;return;}
	int mid=(t[pos].l+t[pos].r)>>1;
	if(x<=mid) modify(L(pos),x,y);
	else modify(R(pos),x,y);
	Push_U(pos);
}
```

### Part 2：查询区间内多重最小值的位置

本题的关键部分，~~也是笔者曾经 WA 过一次的地方。~~

考虑分成两步求多重最小值的位置：求区间最小值，求区间内多重最小值位置。

#### Step 1：求区间内最小值

直接上参考代码。

```cpp
inline int Min(int pos,int l,int r){
	if(l<=t[pos].l&&t[pos].r<=r) return t[pos].Min;
	int mid=(t[pos].l+t[pos].r)>>1,res=1e9+7;
	if(l<=mid) res=min(res,Min(L(pos),l,r));
	if(r>mid) res=min(res,Min(R(pos),l,r));
	return res;
}
```

#### Step 2：求区间内多重最小值位置

若当前节点所表示的区间完全被所求区间包含，则立即判断该区间内最小值是否为所求区间内最小值，若不是，则立即返回。

当当前区间长度为 $1$ 时，将该区间所表示的位置编号直接加入 $j$ 数组中即可。

若未到上两种情况，则继续递归。

参考代码如下：

```cpp
int m,j[N];

inline void check(int pos,int l,int r,int val){
	if(l<=t[pos].l&&t[pos].r<=r&&t[pos].Min!=val)
	  return;
  if(t[pos].l==t[pos].r){
		j[++m]=t[pos].l;
		return;
	}
	int mid=(t[pos].l+t[pos].r)>>1;
	if(l<=mid) check(L(pos),l,r,val);
	if(r>mid) check(R(pos),l,r,val);
}
```

### 主函数

主函数内需要完成上面的函数中没有完成的内容，包括：

- Part 0 中，在建树之前输入 $n,q$ 和 $a$ 数组；
- 每次操作前，输入 $t,x,y$；
- Part 2 的两个函数都运行完毕后，输出 $m$ 和 $j$ 数组。

参考代码如下：

```cpp
int main(){
	int n=I(),q=I();//笔者写了快读
	for(int i=1;i<=n;i++) a[i]=I();
	build(1,1,n);//建树
	while(q--){
		int t=I(),x=I(),y=I();
		if(t==1) modify(1,x,y);//修改
		else{
			m=0;int p=Min(1,x,y);//将 m 归零，求最小值
			check(1,x,y,p);//求多重最小值位置
			printf("%d ",m);//输出 m
			for(int i=1;i<=m;i++)
				printf("%d ",j[i]);//输出 j 数组
			puts("");//换行
		}
	}
	return 0;
}
```

总而言之，本题是一道不错的线段树练习题。

经笔者尝试，分块在本题时间限制下无法通过。

**感谢您的阅读！**

---

## 作者：Running_a_way (赞：2)

[cnblogs](https://www.cnblogs.com/Running-a-way/p/18004129/sol-AT_past202107_l)

### Solution

题目来源：AT_past202107_l（[in AtCoder](https://atcoder.jp/contests/past202107-open/tasks/past202107_l) | [in luogu](https://www.luogu.com.cn/problem/AT_past202107_l)）

用线段树维护区间最小值。单点修改很好写，我们看怎么区间寻找最小值位置。

对于每次询问，我们先求出所查询区间 $[x_i, y_i]$ 的最小值 $p$，然后写一个寻找函数。对于当前区间 $[l, r]$，分以下情况来看：

1. 如果当前区间长度 $> 1$、并且并**不包含在所查询区间内**（即 $l < x_i$ 或 $r > y_i$），我们像正常线段树一样递归查找其在所查询区间内的左右子区间。
2. 如果当前区间长度 $> 1$、并且在查询区间内（即 $x_i \le l$ 且 $r \le y_i$），则该区间的最小值**至少**为 $p$。我们递归寻找其最小值为 $p$ 的左右子区间即可。
3. 如果当前区间长度**恰为** $1$，则**若当前位置的数是 $p$**，则该位置为答案，统计起来。

这部分代码如下：

```cpp
void fnd(int l, int r, int k, int L, int R, ll x) {
    if(l == r) {
        if(minn[k] == x) v.push_back(l);
        return;
    }
    int mid = (l + r) >> 1;
    if(L <= l && r <= R) {
        if(minn[ls(k)] == x) fnd(l, mid, ls(k), L, R, x);
        if(minn[rs(k)] == x) fnd(mid + 1, r, rs(k), L, R, x); 
        return;
    }
    if(L <= mid) fnd(l, mid, ls(k), L, R, x);
    if(mid < R) fnd(mid + 1, r, rs(k), L, R, x);
}
```

为啥上文中情况 $3$ 要加粗「当前位置的数是 $p$」呢？我们可以发现，存在查询区间 $[x_i, y_i]$ 与当前区间 $[l, r]$ 仅交于一个数的情况。这样递归下去会发现，我们最后递归到了那个相交的位置，但这个位置却不一定是 $p$。所以我们要特判一下。

不过这个递归过程还是有点麻烦了，可以参考 @[SamHH0902](https://www.luogu.com.cn/user/793807) 的实现方式。虽然我感觉我的更好想一点。

建议参考代码理解。code：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define ls(a) ((a) << 1)
#define rs(a) ((a) << 1 | 1)
using namespace std;

#define ll long long
#define INF 2e9
const int N = 200010;
int n, q;
ll a[N];
ll minn[N * 4];
vector<ll> v;

void pushup(int k) {
    minn[k] = min(minn[ls(k)], minn[rs(k)]);
}

void build(int l, int r, int k) {
    minn[k] = INF;
    if(l == r) {
        minn[k] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, ls(k)), build(mid + 1, r, rs(k));
    pushup(k);
}

void upd(int l, int r, int k, int x, ll c) {
    if(l == r) {
        minn[k] = c;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) upd(l, mid, ls(k), x, c);
    else upd(mid + 1, r, rs(k), x, c);
    pushup(k);
}

ll query(int l, int r, int k, int L, int R) {
    if(L <= l && r <= R) {
        return minn[k];
    }
    int mid = (l + r) >> 1; ll res = INF;
    if(L <= mid) res = min(res, query(l, mid, ls(k), L, R));
    if(mid < R) res = min(res, query(mid + 1, r, rs(k), L, R));
    return res;
}

void fnd(int l, int r, int k, int L, int R, ll x) {
    if(l == r) {
        if(minn[k] == x) v.push_back(l);
        return;
    }
    int mid = (l + r) >> 1;
    if(L <= l && r <= R) {
        if(minn[ls(k)] == x) fnd(l, mid, ls(k), L, R, x);
        if(minn[rs(k)] == x) fnd(mid + 1, r, rs(k), L, R, x); 
        return;
    }
    if(L <= mid) fnd(l, mid, ls(k), L, R, x);
    if(mid < R) fnd(mid + 1, r, rs(k), L, R, x);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, n, 1);
    while(q--) {
        int op; scanf("%d", &op);
        if(op == 1) {
            int x, y; scanf("%d%d", &x, &y);
            upd(1, n, 1, x, y);
        } else {
            int l, r; scanf("%d%d", &l, &r);
            v.clear();
            ll m = query(1, n, 1, l, r);
            fnd(1, n, 1, l, r, m);
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            printf("%d ", (int) v.size());
            for (int i = 0; i < (int)v.size(); i++) printf("%lld ", v[i]);
            printf("\n");
        }
    }
    return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

什么线段树，都不如分块（

---

我们发现维护区间最小值是 naive 的，直接维护可以做到预处理 $O(n\sqrt n)$，查询 $O(\sqrt n)$，修改 $O(1)$ 的优秀复杂度。

但是维护最小值出现的位置就很不 naive 了，此时如果暴力扫整个区间很不优，所以我们继续套用分块的思想，拿个容器把某个块内的最小值出现的位置统计起来。当我们查询时，我们考虑**从左往右**地扫。考虑更新方式，有 $3$ 种情况：

1. 当前块的最小值或元素小于当前维护到的最小值。那么之前维护到的答案不作数，重新统计。

2. 当前块的最小值或元素等于当前维护到的最小值。那么它**可能**是答案之一，扔到一个容器内即可。

- 如果当前扫到的是一个元素，那么只需要把下标扔到容器里就可以。

- 如果是一个块，那么我们就把已经维护好的元素扔到容器内。

3. 当前块的最小值或元素大于当前维护到的最小值。发现它没用，它不可能做贡献。

从左往右扫就不会导致容器内元素无序，输出的时候就不用排序了。~~虽然你排个序也不会超时。~~

接下来考虑修改。我们发现修改直接暴力重构块是 $O(\sqrt n)$ 的，所以直接重构块可过。

```cpp

int n;
int q;
int a[1000086];
class Block{
	public:
		int len;
		int mnn[10086];//块内最小值
		int id[1000086];//块的编号
		int ll[10086];
		int rr[10086];//左右端点
		std::vector<int>e[10086];//维护最小值的位置
		inline void ini(){
			memset(mnn,0x3f,sizeof mnn);
			len=sqrt(n);
			a[0]=INT_MAX;
			int mnid=0;//某个块内最小值出现的位置
			for(int i=1;i<=n;i++){
				id[i]=(i-1)/len+1;
				mnn[id[i]]=std::min(mnn[id[i]],a[i]);
				if(id[i]-id[i-1]){
					ll[id[i]]=rr[id[i-1]]+1;
					rr[id[i]]=std::min(id[i]*len,n);
					mnid=0;
				}
				if(a[mnid]>a[i])
					mnid=i;
			}//预处理
			for(int i=1;i<=(n/len+((n%len)?1:0));i++)
				for(int j=ll[i];j<=rr[i];j++)
					if(a[j]==mnn[i])
						e[i].push_back(j);
			return;
		}
		inline void ask(int l,int r){
			int st=id[l];
			int ed=id[r];
			if(st==ed){//暴力扫
				int minn=INT_MAX;
				std::vector<int>qwq;
				qwq.clear();
				for(int i=l;i<=r;i++)
					minn=std::min(minn,a[i]);
				for(int i=l;i<=r;i++)
					if(a[i]-minn);
					else
						qwq.push_back(i);
				std::cout<<qwq.size()<<" ";
				for(int j:qwq)
					std::cout<<j<<" ";
				puts("");
			}
			else{
				int minn=INT_MAX;
				std::vector<int>qwq;
				qwq.clear();
				for(int i=l;id[i]==st;i++){
					if(a[i]<minn){
						minn=a[i];
						qwq.clear();
					}
					if(a[i]==minn)
						qwq.push_back(i);
				}
				for(int i=st+1;i<ed;i++){
					if(mnn[i]<minn){
						minn=mnn[i];
						qwq.clear();
					}
					if(minn==mnn[i])
						for(int j:e[i])//整块最小值更新就把之前预处理的答案扔进来
							qwq.push_back(j);
				}
				for(int i=ll[ed];i<=r;i++){
					if(a[i]<minn){
						minn=a[i];
						qwq.clear();
					}
					if(a[i]==minn)
						qwq.push_back(i);
				}
				std::cout<<qwq.size()<<" ";
				for(int i:qwq)
					std::cout<<i<<" ";
				puts("");
			}
		}
		inline void cg(int ii,int x){
			int st=id[ii];
			mnn[st]=INT_MAX;		
			a[ii]=x;
			e[st].clear();
			for(int i=ll[st];i<=rr[st];i++)
				mnn[st]=std::min(mnn[st],a[i]);
			for(int i=ll[st];i<=rr[st];i++)
				if(a[i]==mnn[st])
					e[st].push_back(i);
			return;//暴力重构
		}
}blk;
int main(){
	n=read();
	q=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	blk.ini();
	while(q--){
		int op;
		int l,r;
		op=read();
		l=read();
		r=read();
		if(op-1)
			blk.ask(l,r);//询问
		else
			blk.cg(l,r);//修改
	}
	return 0;
}
```

至此，你已经可以通过此题，但是可以追求更优的复杂度。

考虑查询操作，我们发现如果整块的最小值在查询区间里呈递减，且块内的元素恰均为块内最小值，那么我们的复杂度不亚于暴力。可以考虑先求出询问区间最小值，再将最小值为区间最小值的块预处理出来的答案输出。尽管这只是常数上的优化。

我们发现修改的复杂度每次是 $O(\sqrt n)$ 的，与我们事先说好的 $O(1)$ 要差上不少。容易发现每次修改有以下 $3$ 种情况：

1. 修改到了最小值，把最小值修改的更大了。此时只能暴力重构块。

2. 没有修改到最小值，不会对答案做贡献，不管它。

3. 修改到了最小值，把最小值修改的更小了。此时作废之前预处理的答案，此时的答案只有当前元素。

如果你用的容器很优秀，它可以做到 $O(1)$ 清空，那么你的修改操作会更快。具体的，如果**数据随机**，那么均摊复杂度大概为 $O(\frac{1}{V})$，带上一个常数。反正就是修改的均摊复杂度是常数级别就对了（雾

这部分的代码就不放了，反正改改预处理和修改就行。

---

## 作者：Ybw0731 (赞：1)

这是一道线段树好题。~~本蒟蒻刚学线段树。~~

# STEP1
首先第一件事就是建树。不过这还是很好理解的，我们每次进入一个节点，看他是不是叶子结点。如果是，那么就在树中存入这个节点。如果不是叶子结点，那么去遍历左右子树，最后回来把这个节点更新为左右子树的最小值。
```cpp
void build(int o,int l,int r){
	if(l==r){
    sum[o]=a[l];
    return;
  }
  int mid=(l+r)/2;
  build(o*2,l,mid);
  build(o*2+1,mid+1,r);
  sum[o]=min(sum[o*2],sum[o*2+1]);//push_up
}
```
# STEP2
这一题是一个单点修改，那么我们就可以看这个结点在左子树还是在右子树上。找到那个结点后，把那个结点修改为要更新的数，最后回来把这个节点更新为左右子树的最小值。
```cpp
void update(int o,int l,int r){
	if(l==r){
	    sum[o]=y;
	    return;
	}
	int mid=(l+r)/2;
	if(x<=mid)update(o*2,l,mid);
	else update(o*2+1,mid+1,r);
	sum[o]=min(sum[o*2],sum[o*2+1]);//push_up
}
```
# STEP3.1
接下来是区间查询。当这个区间已经被完全覆盖，就返回这个节点的值。否则看这个区间是在左子树还是右子树。

```cpp
int query(int o,int l,int r){
	if(x<=l&&r<=y)return sum[o];
	int mid=(l+r)/2,ans=INF;//INF是一个自定义的最大值
	if(x<=mid)ans=min(ans,query(o*2,l,mid));//在左子树
	if(y>mid)ans=min(ans,query(o*2+1,mid+1,r));//在右子树
	return ans;//无需push_up
}
```
# STEP3.2
光有这些还不够，不然他是评不上绿的。
查询区间内多重最小值的位置是本题评绿的原因（不然只有黄题难度）。当这个结点为叶子结点时，记录这个位置。否则继续遍历左右子树。


真这么简单吗？


不，还有一个剪枝，详见代码。
# 代码时间到
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5*4+100;//注意开四倍大小
const int INF=2e9+100;//极大值
int a[maxn],sum[maxn],op,x,y,p;
int n,q,m;
int s[maxn];//树
void build(int o,int l,int r){//建树
	if(l==r){
	    sum[o]=a[r];
	    return;
	}
	int mid=(l+r)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	sum[o]=min(sum[o*2],sum[o*2+1]);//push_up
}
void update(int o,int l,int r){//单点修改
	if(l==r){
	    sum[o]=y;
	    return;
	}
	int mid=(l+r)/2;
	if(x<=mid)update(o*2,l,mid);
	else update(o*2+1,mid+1,r);
	sum[o]=min(sum[o*2],sum[o*2+1]);//push_up
}
int query(int o,int l,int r){//区间查询
	if(x<=l&&r<=y)return sum[o];
	int mid=(l+r)/2,ans=INF;
	if(x<=mid)ans=min(ans,query(o*2,l,mid));
	if(y>mid)ans=min(ans,query(o*2+1,mid+1,r));
	return ans;
}
void find(int o,int l,int r){
	if(x<=l&&r<=y&&sum[o]!=p)return;//剪枝，如果这个区间被覆盖，直接判断该区间的最小值是不是所需的值。
	if(l==r){
		m++;
		s[m]=l;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)find(o*2,l,mid);
	if(y>mid)find(o*2+1,mid+1,r);
}
int main(){
	cin>>n>>q;
	for(int i=1;i<= n;i++)cin>>a[i];
	build (1,1,n);
	for (int i=1;i<=q;i++){
		cin>>op>>x>>y;
		if(op==1)update(1,1,n);
		else{
			m=0;//初始化
			p=query(1,1,n);
			find(1,1,n);
			cout<<m<<' ';
			for(int j=1;j<=m;j++)cout<<s[j]<<' ';
			cout<<endl;//不加换行见祖宗
		}
	}
	return 0;
}
```
## 完结撒花
~~留个赞再走呗。~~

---

## 作者：Vegetableless (赞：1)

没有分块题解，来交一发。

一道分块板子。

题目中有两种操作，第一种单点修改，第二种区间查询有多少个值为最小值。

我们考虑分块暴力维护区间最小值。

对于单点修改，我们在更改完 $a_{x_i}$ 之后暴力扫一遍 $x_i$ 所在块内，更新块内最小值。

```cpp
#include<bits/stdc++.h>
#define pb push_back
constexpr int N = 2e5 + 5;
constexpr int INF = 1e9 + 7;

using std :: vector;
using std :: min;
using std :: cerr;

inline int read(){
	char ch = getchar();
	int x = 0;
	bool f = 0;
	
	while(!isdigit(ch)) f = (ch == '-') , ch = getchar();
	while(isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48) , ch = getchar();
	
	return f ? -x : x;
}

inline void write(int x){
	int w[101] , top = 0;
	
	if(!x) putchar('0');
	if(x < 0) putchar('-') , x = -x;
	while(x)
		w[++top] = x % 10 , x /= 10;
	while(top)
		putchar(w[top] ^ 48) , top --;
	putchar(' ');
}

int n , q , minn[N] , bl[N] , block , a[N] , ans[N];

vector<int > vec[N];//vec 数组维护每个块内值为最小值的 x[i]

inline void Modify(int p , int x){//单点修改
	a[p] = x; vec[bl[p]].clear(); minn[bl[p]] = INF;
	for(int i = (bl[p] - 1) * block + 1;i <= min(n , bl[p] * block);++i){
		if(a[i] < minn[bl[i]]){
			minn[bl[i]] = a[i];
			vec[bl[i]].clear();
			vec[bl[i]].pb(i);
		}
		
		else if(a[i] == minn[bl[i]]) vec[bl[i]].pb(i);
	}
	
	return;
}

/*
由于修改可能会影响到块内最小值（例如将最小值更改为更大的数），
所以我们整体扫一遍来更新块内的最小值及为这个值的数的下标。
*/

inline void Query(int l , int r){//区间查询
	int mn = INF , sz = 0;
	
	for(int i = l;i <= min(r , bl[l] * block);++i) {
		if(a[i] < mn){
			mn = a[i];
			sz = 1;
			ans[1] = i;
		}
		
		else if(a[i] == mn) ans[++sz] = i;
	}
	
	if(bl[l] != bl[r]) {
		for(int i = (bl[r] - 1) * block + 1;i <= r;++i){
			if(a[i] < mn){
				mn = a[i];
				sz = 1;
				ans[1] = i;
			}
		
			else if(a[i] == mn) ans[++sz] = i;
		}
	}
	
	for(int i = bl[l] + 1;i < bl[r];++i) {
		if(minn[i] < mn){
			mn = minn[i];
			sz = 0;
			for(int j : vec[i]) ans[++sz] = j;
		}
		
		else if(minn[i] == mn) for(int j : vec[i]) ans[++sz] = j;
	}
	
	write(sz); std :: sort(ans + 1 , ans + 1 + sz);//要按照递增输出。
	
	for(int i = 1;i <= sz;++i) write(ans[i]);
	
	putchar(10);
	return;
}//查询时，遇到更小值就要将 ans 清空，并且更新 mn。

int main(){
	n = read() , q = read();
	
	block = std :: sqrt(n);
	
	for(int i = 1;i <= block + 1;++i) minn[i] = INF;
	
	for(int i = 1;i <= n;++i){
		a[i] = read();
		bl[i] = (i - 1) / block + 1;
		if(a[i] < minn[bl[i]]){
			minn[bl[i]] = a[i];
			vec[bl[i]].clear();
			vec[bl[i]].pb(i);
		}
		
		else if(a[i] == minn[bl[i]]) vec[bl[i]].pb(i);
	}
	
	for(int i = 1;i <= q;++i){
		int opt = read();
		if(opt == 1){
			int p = read() , x = read();
			Modify(p , x);
		}
		else {
			int l = read() , r = read();
			Query(l , r);
		}
	}
	return 0;
}

/*
因为输出 j 的总个数不超过 2e5，
询问扫块内是 sqrt(n) 的，
但是答案只会遍历 2e5 次，也就是最多输出 2e5 个。
那么实际总体复杂度是 O(q sqrt(n) + 2e5)
也就是 O(q sqrt(n)) 的
读入输出记得优化
*/
```

时间复杂度为 $O(Q \sqrt{N})$。

---

## 作者：Crazyouth (赞：1)

## 分析

题目的本质都是模拟。

相信各位大佬都是会求动态区间最小值的，这里不再赘述。我们考虑用线段树二分加速模拟寻找最小值下标的过程。把一个区间 $[x,y]$ 分成许多小区间，如果某一区间 $[l,r]$ 的大小为 $1$，那么它必定是符合条件的（因为我们不会搜索 $[x,y]$ 外的区间）；如果另外某个区间 $[s,t]$ 完全被 $[x,y]$ 包含，但它的最小值不是 $[x,y]$ 的最小值，那么 $[s,t]$ 内的数一定全部都不满足条件。这里我用的 set 去储存符合条件的数，因此复杂度为 $O(q \log^2 n)$。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],mn[N<<2];
set<int> st;
void build(int s,int t,int p)
{
	if(s==t)
	{
		mn[p]=a[s];
		return;
	}
	int m=s+t>>1;
	build(s,m,p<<1);
	build(m+1,t,p<<1|1);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
void upd(int k,int s,int t,int p,int x)
{
	if(s==t&&t==k)
	{
		mn[p]=x;
		return;
	}
	int m=s+t>>1;
	if(k<=m) upd(k,s,m,p<<1,x);
	else upd(k,m+1,t,p<<1|1,x);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
int qmin(int l,int r,int s,int t,int p)
{
	if(l<=s&&t<=r) return mn[p];
	int m=s+t>>1;
	int ret=1e9;
	if(l<=m) ret=qmin(l,r,s,m,p<<1);
	if(r>m) ret=min(qmin(l,r,m+1,t,p<<1|1),ret);
	return ret; 
}
void getmin(int l,int r,int s,int t,int p,int v)
{
	if(l<=s&&t<=r&&mn[p]!=v) return;
	if(s==t)
	{
		st.insert(s);
		return;
	}
	int m=s+t>>1;
	if(l<=m) getmin(l,r,s,m,p<<1,v);
	if(r>m) getmin(l,r,m+1,t,p<<1|1,v);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,n,1);
	while(q--)
	{
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1) upd(x,1,n,1,y);
		else
		{
			int minn=qmin(x,y,1,n,1);
			st.clear();
			getmin(x,y,1,n,1,minn);
			cout<<st.size()<<' ';
			for(auto i:st) cout<<i<<' ';
			cout<<'\n';
		}
	}
	return 0;
}

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_past202107_l)

用线段树维护区间最小值即可。和模板唯一区别就是要查找 $j$，使：$x\le j\le y$，$a_j=p$。

[不会线段树的可以去这里看看](https://www.luogu.com.cn/problem/solution/P3372)。

查找的思路、代码：

当这个区间完全被要查找的区间覆盖，直接判断该区间的最小值是不是所求的值。

当这个区间长度为 1 时，记录这个位置。

否则，继续遍历左、右子树。

```cpp
void find(int p,int l,int r,int x,int y,int z){//查找 
	if(x<=l&&y>=r&&tree[p].pre!=z){//判断
		return;
	}
	if(l==r){//记录答案
		ans[++k]=l;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid){//遍历左子树
		find(p*2,l,mid,x,y,z);
	}
	if(y>mid){//遍历右子树
		find(p*2+1,mid+1,r,x,y,z);
	}
}
```

整体代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define endl '\n'
#define inf INT_MAX 
using namespace std;
const int N=1e6+7;
const int M=1e6+7;
const int mod=1e9+9;
const double eps=1e-6;
struct Tree{
	int pre;
}tree[4*N];
int a[N];
void push_up(int p){//上传 
	tree[p].pre=min(tree[p*2].pre,tree[p*2+1].pre);
}
void build(int p,int l,int r){//建树 
	if(l==r){
		tree[p].pre=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);//建立左子树
	build(p*2+1,mid+1,r);//建立右子树
	push_up(p);
}
void update(int p,int l,int r,int x,int y){//单点修改 
	if(l==r){//直接改
		tree[p].pre=y;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid){//遍历左子树
		update(p*2,l,mid,x,y);
	}else{//遍历右子树
		update(p*2+1,mid+1,r,x,y);
	}
	push_up(p);
}
int query(int p,int l,int r,int x,int y){//区间查询 
	if(x<=l&&y>=r){//这个区间被要查找的区间完全覆盖，直接返回
		return tree[p].pre;
	}
	int mid=(l+r)/2;
	int ans=inf;//否则遍历左、右子树
	if(x<=mid){//左子树
		ans=min(ans,query(p*2,l,mid,x,y));
	}
	if(y>mid){//右子树
		ans=min(ans,query(p*2+1,mid+1,r,x,y));
	}
	return ans;
}
int ans[N],k;
void find(int p,int l,int r,int x,int y,int z){//查找 
	if(x<=l&&y>=r&&tree[p].pre!=z){//判断
		return;
	}
	if(l==r){//记录答案
		ans[++k]=l;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid){//遍历左子树
		find(p*2,l,mid,x,y,z);
	}
	if(y>mid){//遍历右子树
		find(p*2+1,mid+1,r,x,y,z);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,m;
	cin >>n>>m;
	for(int i=1;i<=n;i++){
		cin >>a[i];
	} 
	build(1,1,n);
	while(m--){
		int op;
		cin >>op;
		if(op==1){
			int x,y;
			cin >>x>>y;
			update(1,1,n,x,y);
		}else{
			k=0;
			int x,y;
			cin >>x>>y;
			int t=query(1,1,n,x,y);
			find(1,1,n,x,y,t);
			cout<<k<<" ";
			for(int i=1;i<=k;i++)cout<<ans[i]<<" ";
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

几乎是线段树板子题了，只多了一个查询 $\min \limits _ {l \le i \le r} a _ i$ 在区间 $[l, r]$ 里出现的次数和位置的操作。

我们可以考虑采用类似线段树的方法，从根节点开始搜：

- 如果这个区间完全被要查找的区间覆盖，直接判断该区间的最小值是不是所求的值，不是就直接 `return`。
- 如果这个区间的左右端点相同，记录下答案然后直接 `return`。
- 否则直接接着遍历左子树和右子树。

```cpp
void find(int i = 1, int l = 1, int r = n) {
	if(l >= x && y >= r) {
		if(tree[i] != min) return ;
	}
	if(l == r) {
		ans[++len] = l;
		return ;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) find(i << 1, l, mid);
	if(y > mid) find((i << 1) + 1, mid + 1, r);
}
```

其他部分就是板子，所以就不放代码了。

---

## 作者：Daniel_xu (赞：0)

# 题意简述
[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_l)\
给定一个长度为 $n$ 的数组 $a$ 和 $m$ 组修改或询问，对于每一个询问，求出数组 $a$ 在区间 $[l,r]$ 之间的所有最小值的下标。
# 大致思路
由于本题与区间修改与求最值相关，考虑使用线段树实现较快速的修改与查询。现在的问题就是如何在知道某个数的情况下，求一个区间里这个数的所有出现位置的下标。\
由于数字总量较小，但是每一个 $a_{i}$ 的范围较大，所以考虑使用 unordered_map 存储每一个数及其出现位置。对于每一个数，为了方便地求出这个数在一个区间里所有出现位置的下标，可使用 set 进行存储，使用 lower_bound 与 upper_bound 找到该数在一个区间里的左右边界，在此之内遍历并输出。\
总共时间复杂度 $O(n+m \log n)$。
# 写代码前的前置知识
关于线段树的单点修改与区间查询，建议看一看[线段树-OIWiki](https://oi-wiki.org/ds/seg/)，做一做 [P1198 [JSOI2008] 最大数](https://www.luogu.com.cn/problem/P1198)。\
另外，可以看一看 [unordered_map](https://www.runoob.com/cplusplus/cpp-libs-unordered_map.html) 和 [set](https://www.runoob.com/cplusplus/cpp-libs-set.html)。\
以上内容引用[洛谷](https://www.luogu.com.cn)、[OI Wiki](https://www.oi-wiki.org)、[菜鸟教程](https://www.runoob.com/)。
# AC 代码

```cpp
#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
using namespace std;
const int N=2e5+5;
struct Node{//线段树 
	int l,r;
	int Min;
}tr[N<<2];

int a[N];
//umap & set 存储每个数及其出现位置 
unordered_map<int,set<int> > mp;

//线段树基本模板 
void pushup(int u){
	tr[u].Min=min(tr[u<<1].Min,tr[u<<1|1].Min);
}

void build(int u,int l,int r){
	if(l==r){
		tr[u]=Node{l,r,a[l]};
		return;
	}
	tr[u]=Node{l,r};
	int mid=l+r>>1; 
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}

void modify(int u,int x,int d){
	if(tr[u].l==tr[u].r){
		tr[u].Min=d;
		return;
	} 
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid)modify(u<<1,x,d);
	else modify(u<<1|1,x,d);
	pushup(u);
} 

int query(int u,int l,int r){
	if(l<=tr[u].l && tr[u].r<=r){
		return tr[u].Min;
	}
	int mid=tr[u].l+tr[u].r>>1;
	int res=2e9;
	if(l<=mid)res=min(res,query(u<<1,l,r));
	if(r>mid)res=min(res,query(u<<1|1,l,r));
	return res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]].insert(i);//初始化 
	}
	build(1,1,n);
	int op,x,y;
	while(m--){
		cin>>op>>x>>y;
		if(op==1){//更新 
			modify(1,x,y);
			mp[a[x]].erase(x);
			a[x]=y;
			mp[a[x]].insert(x);
		}else{//查询 
			vector<int> ans;
			int res=query(1,x,y);
			//获得左、右边界 
			auto s=mp[res].lower_bound(x),t=mp[res].upper_bound(y);
			for(auto it=s;it!=t;it++){
				ans.push_back(*it);
			//输出 
			cout<<ans.size();
			for(int num:ans){
				cout<<" "<<num;
			}
			cout<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：Walrus (赞：0)

首先看到两个操作，可以明白这是一个可支持单点修改区间查询的数据结构，显然会想到线段树。

这题的难点在于，在我们知道区间最小值 $mn$ 时，如何找到在此区间内所有 $a_j=mn$ 的 $j$。

先给出除了寻找操作的代码部分：
```cpp
struct SegmentTree {
	struct node {
		int l, r, mn, add;

#define l(p) t[p].l
#define r(p) t[p].r
#define mn(p) t[p].mn
#define add(p) t[p].add
	} t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid l(p) + r(p) >> 1

	void pushup(int p) {
		mn(p) = min(mn(ls), mn(rs));
	}

	void build(int p, int l, int r) {
		l(p) = l, r(p) = r;
		if(l == r)
			return mn(p) = a[l], void();
		int Mid = l + r >> 1;
		build(ls, l, Mid), build(rs, Mid + 1, r), pushup(p);
	}


	void pushdown(int p) {
		if(add(p))
			mn(ls) = mn(rs) = add(p), add(ls) = add(rs) = add(p), add(p) = 0;
	}

	void change(int p, int l, int r, int x) {
		if(l <= l(p) && r(p) <= r)
			return mn(p) = x, add(p) = x, void();
		if(l <= mid)
			change(ls, l, r, x);
		if(r > mid)
			change(rs, l, r, x);
		pushup(p);
	}

	int ask(int p, int l, int r) {
		if(l <= l(p) && r(p) <= r)
			return mn(p);
		int val = INT_MAX;
		if(l <= mid)
			val = min(val, ask(ls, l, r));
		if(r > mid)
			val = min(val, ask(rs, l, r));
		return val;
	}
} SGT;
```

由于线段树可支持区间最小查询，所以当我们找到 $p$ 代表的 $[l(p),r(p)]$ 区间时，同样也可以知道其左半部分和右半部分的最小值，故有一个 trick：如果 $p$ 的左右部分（即 $p\times 2$ 和 $p\times2+1$）代表的区间的最小值不为 $mn$，则此部分对答案一定没有贡献，则可以跳过此区间。这样的话就可以暴力到叶节点，直接记录所有值为 $mn$ 的位置然后暴力输出即可。

有点势能线段树的意思，复杂度不好说，大概是 $O(N\log N)$，有不同意见可以交流。

完整代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

vector<int> ans;
int n, q, op, l, r, a[N], x, res;

struct SegmentTree {
	......
	void print(int p, int l, int r, int x) {
		if(l(p) == r(p)) {
			if(mn(p) == x)
				++res, ans.push_back(l(p));
			return;
		}
		if(l <= l(p) && r(p) <= r) {
			if(mn(ls) == x)
				print(ls, l, r, x);
			if(mn(rs) == x)
				print(rs, l, r, x);
			return;
		}
		if(l <= mid)
			print(ls, l, r, x);
		if(r > mid)
			print(rs, l, r, x);
	}
} SGT;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	SGT.build(1, 1, n);
	while(q--) {
		cin >> op >> l >> r;
		if(op == 1)	SGT.change(1, l, l, r);
		else {
			int Mn = SGT.ask(1, l, r);
			SGT.print(1, l, r, Mn);
			cout << res << ' ';
			sort(ans.begin(), ans.end());
			for(auto x : ans)
				cout << x << ' ';
			ans.clear(), res = 0;
			cout << '\n';
		}
	}
	return 0;
}
```

---

## 作者：dvsfanjo (赞：0)

# 题解：AT_past202107_l たくさんの最小値

## 思路

用线段树维护区间最小值，在线段树中操作即可。

## 线段树

### 建树

对于区间 $[l,r]$ 的最小值必定是两个子区间最小值的最小值，当 $l=r$ 时 $a_l$ 是区间最小值。

```cpp
void build(ll l, ll r, ll id)
{
	if (l == r)
	{
		t[id] = a[l];
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls(id));
	build(mid + 1, r, rs(id));
	t[id] = min(t[ls(id)], t[rs(id)]);
	return;
}
```

### 单点修改

要修改的位置在哪个子区间就修改哪个区间，当 $l=r$ 时直接修改即可。

```cpp
void change(ll l, ll r, ll id, ll w, ll v)
{
	if (l > r)
		return;
	if (l > w or r < w)
		return;
	if (l == r and l == w)
	{
		t[id] = v;
		return;
	}
	ll mid = (l + r) >> 1;
	change(l, mid, ls(id), w, v);
	change(mid + 1, r, rs(id), w, v);
	t[id] = min(t[ls(id)], t[rs(id)]);
	return;
}
```

### 求最小

如果当前区间被所查询区间覆盖，就直接返回区间最小值，否则搜索子区间。

```cpp
ll mn(ll l, ll r, ll id, ll x, ll y)
{
	if (y < l or x > r or l > r)
		return 2e9;
	if (x <= l and r <= y)
		return t[id];
	ll mid = (l + r) >> 1, as = 2e9;
	as = min(as, mn(l, mid, ls(id), x, y));
	as = min(as, mn(mid + 1, r, rs(id), x, y));
	return as;
}ll mn(ll l, ll r, ll id, ll x, ll y)
{
	if (y < l or x > r or l > r)
		return 2e9;
	if (x <= l and r <= y)
		return t[id];
	ll mid = (l + r) >> 1, as = 2e9;
	as = min(as, mn(l, mid, ls(id), x, y));
	as = min(as, mn(mid + 1, r, rs(id), x, y));
	return as;
}
```

### 求下标

如果当前区间的最小值比所查询的最小值大，那么这个区间内必然没有答案，否则继续搜索到 $l=r$ 为止。

```cpp
ll fnd(ll l, ll r, ll id, ll x, ll y, ll v)
{
	if (y < l or x > r or l > r or t[id] > v)
		return 0;
	if (l == r)
	{
		if (t[id] == v)
		{
			ans[++tot] = l;
			return 1;
		}
		return 0;
	}
	ll mid = (l + r) >> 1, as = 0;
	as += fnd(l, mid, ls(id), x, y, v);
	as += fnd(mid + 1, r, rs(id), x, y, v);
	return as;
}
```

### 主函数

按照题目写就可以了。

## AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
ll t[N * 4], a[N], n, q, op, x, y, ans[N], tot;
ll ls(ll id) {return id << 1;}
ll rs(ll id) {return ls(id) + 1;}
void build(ll l, ll r, ll id)
{
	if (l == r)
	{
		t[id] = a[l];
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls(id));
	build(mid + 1, r, rs(id));
	t[id] = min(t[ls(id)], t[rs(id)]);
	return;
}
void change(ll l, ll r, ll id, ll w, ll v)
{
	if (l > r)
		return;
	if (l > w or r < w)
		return;
	if (l == r and l == w)
	{
		t[id] = v;
		return;
	}
	ll mid = (l + r) >> 1;
	change(l, mid, ls(id), w, v);
	change(mid + 1, r, rs(id), w, v);
	t[id] = min(t[ls(id)], t[rs(id)]);
	return;
}
ll mn(ll l, ll r, ll id, ll x, ll y)
{
	if (y < l or x > r or l > r)
		return 2e9;
	if (x <= l and r <= y)
		return t[id];
	ll mid = (l + r) >> 1, as = 2e9;
	as = min(as, mn(l, mid, ls(id), x, y));
	as = min(as, mn(mid + 1, r, rs(id), x, y));
	return as;
}
ll fnd(ll l, ll r, ll id, ll x, ll y, ll v)
{
	if (y < l or x > r or l > r or t[id] > v)
		return 0;
	if (l == r)
	{
		if (t[id] == v)
		{
			ans[++tot] = l;
			return 1;
		}
		return 0;
	}
	ll mid = (l + r) >> 1, as = 0;
	as += fnd(l, mid, ls(id), x, y, v);
	as += fnd(mid + 1, r, rs(id), x, y, v);
	return as;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, n, 1);
	while (q--)
	{
		cin >> op >> x >> y;
		if (op == 1)
			change(1, n, 1, x, y);
		else if (op == 2)
		{
			tot = 0;
			ll k = fnd(1, n, 1, x, y, mn(1, n, 1, x, y));
			cout << k << ' ';
			for (int i = 1; i <= tot; i++)
				cout << ans[i] << ' ';
			cout << '\n';
		}
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_l)

## 思路

看到单点修改，区间查询，首先想到线段树。操作一和操作二的查询最小值都非常简单，主要的难点是操作二的后一部分。

我们考虑再次查找这个区间。如果当前线段的最小值大于目标值，那么这条线段上肯定不存在目标点，退出即可。如果持续递归到叶子结点，那么这个点肯定是目标点（已求出目标区间的最小值，那么目标区间所覆盖的线段上**任意节点值一定不会比这个值小**）。这时我们直接用一个数组记录结果即可。

- 记得有多组询问，清空下标变量。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){//快读。
	ll k=0,flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	return k*flag;
}
const int N=2e5+10;
int n,q,ans[N],cnt;
struct node{
	int l,r,mi;
}tr[N<<2];
void build(int i,int l,int r){//建树。
	tr[i].l=l;
	tr[i].r=r;
	if(l==r){
		tr[i].mi=read();
		return ;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	tr[i].mi=min(tr[i<<1].mi,tr[i<<1|1].mi);
	return ;
}
void change(int i,int x,int k){//单点修改。
	if(tr[i].l==tr[i].r){
		tr[i].mi=k;
		return ;
	}
	int mid=tr[i].l+tr[i].r>>1;
	if(x<=mid)change(i<<1,x,k);
	else change(i<<1|1,x,k);
	tr[i].mi=min(tr[i<<1].mi,tr[i<<1|1].mi);
	return ;
}
int query(int i,int l,int r){//找最小值。
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].mi;
	int mid=tr[i].l+tr[i].r>>1,res=1e9;//记得赋极大值。
	if(l<=mid)res=min(res,query(i<<1,l,r));
	if(mid<r)res=min(res,query(i<<1|1,l,r));
	return res;
}
void find(int i,int l,int r,int p){//找值。
	if(tr[i].mi>p)return ;//比最小值大，肯定没有。
	if(tr[i].l==tr[i].r){
		ans[++cnt]=tr[i].l;//将结果存入数组。
		return ;
	}
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)find(i<<1,l,r,p);
	if(mid<r)find(i<<1|1,l,r,p);
	return ;
}
signed main(){ 
	cin>>n>>q;
	build(1,1,n);
	while(q--){
		int op=read(),x=read(),y=read();
		if(op==1)change(1,x,y);
		else{
			int p=query(1,x,y);
			cnt=0;//记得清零。
			find(1,x,y,p);
			printf("%d ",cnt);
			for(int i=1;i<=cnt;++i)printf("%d ",ans[i]);
			putchar('\n');
		}
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/164597791)

---

