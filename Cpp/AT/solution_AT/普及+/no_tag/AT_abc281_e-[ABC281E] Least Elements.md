# [ABC281E] Least Elements

## 题目描述

给定一个序列 $A$，对于每个 $1 \le i \le N - M + 1$，将 $A_i A_{i + 1} \cdots A_{i + M - 1}$ **从小到大**排序后（不影响原序列），求出 $\displaystyle ans_i = \sum\limits_{j=i}^{i+k-1} A_j$。

## 说明/提示

$1 \le K \le M \le N \le 2 \times 10^5$

$1 \le A_i \le 10^9$

## 样例 #1

### 输入

```
6 4 3
3 1 4 1 5 9```

### 输出

```
5 6 10```

## 样例 #2

### 输入

```
10 6 3
12 2 17 11 19 8 4 3 6 20```

### 输出

```
21 14 15 13 13```

# 题解

## 作者：hcywoi (赞：4)

## $\mathcal Solution$

本题的思路类似于对顶堆。

用两个 multiset 来维护。

$S_1$ 为第一个 multiset；

$S_2$ 为第二个 multiset。

$S_1$ 维护前 $K$ 个值，$S_2$ 维护预选的值。

当进入一个数 $x$，则将 $x \in S_2$。

1. 如果 $\mathrm{length}(S_1) < K$，则将 $S_2$ 的最小值加入 $S_1$。

2. 判断 $S_2$ 的最小值，即 $S_2$ 的开头，与 $S_1$ 的最大值，即 $S_1$ 的结尾，判断大小关系，如果小于，则替换。

3. 输出 $\mathrm{ans}_i$。

4. 在运行完以上操作后，如果 $i \ge m$ 时，将 $A_{i - M + 1}$ 删除，即判断 $A_{i - M + 1}$ 所在的集合将他删除。

5. 重复 $\mathit{1} \sim \mathit{4}$ 操作。

### $\mathcal Code$

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#define x first
#define y second
#define IOS ios::sync_with_stdio(false)
#define cit cin.tie(0)
#define cot cout.tie(0)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int N = 200010, M = 100010, MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int n, m, k;
int w[N];

void solve()
{
	cin >> n >> m >> k;
	
	multiset<int> S;
	multiset<int> S2;
	for (int i = 1; i <= n; i ++ ) cin >> w[i];
	
	LL res = 0;
	for (int i = 1; i <= n; i ++ )
	{
		S2.insert(w[i]);
		while (S.size() < k && S2.size()) res += *S2.begin(), S.insert(*S2.begin()), S2.erase(S2.begin());
		while (S2.size() && (*S2.begin()) < (*S.rbegin())) // 维护序列
		{
			res -= *S.rbegin();
			res += *S2.begin();
			S2.insert(*S.rbegin());
			S.erase(S.find(*S.rbegin()));
			S.insert(*S2.begin());
			S2.erase(S2.begin());
		}
		if (i >= m)
		{
			cout << res << ' ';
			int x = w[i - m + 1];
			if (S.find(x) != S.end()) res -= x, S.erase(S.find(x)); // 只有在 S 集合中才需要减。
			else S2.erase(S2.find(x));
		}
	}
}

int main()
{
	IOS;
	cit, cot;
	int T = 1;
//	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：FFTotoro (赞：3)

## 前言

赛时做出了 E 却没做出 D。

## 解法

首先用一个 `std::vector`（记为 $b$） 存储前 $M$ 个数，排序后取前 $k$ 大，这就是第一个询问的答案，记为 $c$。

对于接下来每一个询问，我们只需用 `lower_bound` 函数二分出需要删除的那个数（设为 $r$）的位置，并判断删掉它会不会对答案有影响。如果有影响，那么 $c\leftarrow c+b_{K+1}-r$ 并删除它。

然后考虑插入一个新的数，设为 $p$。同样地，用 `insert` 结合 `upper_bound` 插入后再次查询排名（有一大佬指出，`insert` 函数插入常数极小），考虑对答案有没有影响，如果有影响，那么 $c\leftarrow c+p-b_{K+1}$。

每次询问输出处理过的 $c$ 即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,m,k,c=0; cin>>n>>m>>k;
  vector<int> a(n),b;
  for(auto &i:a)cin>>i;
  for(int i=0;i<m;i++)b.emplace_back(a[i]);
  sort(b.begin(),b.end());
  for(int i=0;i<k;i++)c+=b[i]; // 先处理出第一个答案
  cout<<c<<' ';
  for(int i=1;i<=n-m;i++){
    auto l=lower_bound(b.begin(),b.end(),a[i-1]); // 查询需要删除的数的 rank
    if(l-b.begin()<k)c+=b[k]-*l; b.erase(l); // 有影响
    b.insert(upper_bound(b.begin(),b.end(),a[i+m-1]),a[i+m-1]); // 插入
    auto r=lower_bound(b.begin(),b.end(),a[i+m-1]); // 插入后查询 rank
    if(r-b.begin()<k)c+=a[i+m-1]-b[k]; // 有影响
    cout<<c<<' ';
  }
  cout<<endl;
  return 0;
}
```

---

## 作者：lfxxx (赞：3)

具题意可知，我们需要动态维护一个区间 （这里看成一个集合） 内的以下操作：

1. 删除一个数
2. 加入一个数
3. 前 $k$ 个数之和。

显然可以使用平衡树。

但是这里我们使用树状数组上倍增。

开两个树状数组，一个用来求排名，另一个求小于 $x$ 的所有数。

所以，只要离散化后即可通过，复杂度 $O(n \log n)$ 。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=4e5+100;
const int cnt = 1e6;
int tree[2][1000000];
inline int lowbit(int x)
{
    return x&-x;
}
inline void add(int x,int val,int type)
{
	if(x==0){
		return ;
	}
    while(x<=cnt)
    {
        tree[type][x]+=val;
        x+=lowbit(x);
    }
}
inline int pre(int x,int type)
{
    int res=0;
    while(x!=0)
    {
        res+=tree[type][x];
        x-=lowbit(x);
    }
    return res;
}
int ask(int l,int r,int type)
{
	if(l>r||l==0) return 0;
    return pre(r,type)-pre(l-1,type);
}
inline int kth(int k,int type)
{
    int r=0,t=0;
    for(int i=20,x,y;i>=0;i--)
    {
        if((x=r+(1<<i))>cnt) continue;
        if((y=t+tree[type][x])<k) r=x,t=y;
    }
    return r+1;
}
int a[maxn];
int op[maxn];
int y[maxn];
int p[maxn];
int n,m,k;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	op[i]=a[i];
    	y[i]=a[i];
    }
    sort(op+1,op+n+1);
    for(int i=1;i<=n;i++){
    	a[i]=lower_bound(op+1,op+n+1,a[i])-(op+1)+1;
    	p[a[i]]=y[i];
    }
    for(int i=1;i<=m;i++){
    	add(a[i],1,0);
    	add(a[i],y[i],1);
    }
    for(int i=0;i+m<=n;i++){
    	int sum=kth(k,0);
    	int res=ask(1,sum-1,1);
    	int cnt=ask(1,sum-1,0);
    	res+=(k-cnt)*p[sum];
    	cout<<res<<'\n';
    	add(a[1+i],-1,0);
    	add(a[1+i],-y[1+i],1);
    	add(a[i+m+1],1,0);
    	add(a[i+m+1],y[i+m+1],1);
    }
    return 0;
}
```


---

## 作者：sixrc (赞：2)

这题有很多种解法。

第一种，看到求前 $k$ 大值之和，不管三七二十一直接上主席树。不会可以见 [P3834 【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)。维护两个 tag：子树内有多少个数，子树内所有数字之和，查询的时候直接线段树上二分即可。这种做法的好处是不用动脑子，并且在赛时可以直接复制模板。

第二种，观察到区间长度一定，那么主席树其实是比较多余的。其实只用维护一棵线段树，就是当前区间的权值线段树。同样的，权值线段树上维护两个 tag：子树内有多少个数，子树内所有数字之和。考虑从 $[l,r]$ 转移到 $[l+1,r+1]$，实际上只用在权值线段树上把 $a_l$ 删去，加上 $a_r$ 即可。查询的时候同样在这棵线段树上二分即可。

除此之外好像还有别的解法，也许还可以维护第 $k$ 大数从而避免使用线段树（？这里就先介绍线段树的两种解法。

---

## 作者：DengDuck (赞：1)

赛时思路是平衡树。

这是一个滑动窗口问题，每一次滑动时，有一个数字走，有一个数字加入。

对于离开的数字，和加入的数字，我们需要考虑它对答案是否有贡献，以对答案进行更新。

我们根据题意得有贡献的数字就是排名是前 $k$ 的。

因此我们总结，我们需要删除，加入，查询排名，这个过程利用平衡树维护，时间复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read() {//快读
    char c = getchar();
    long long f = 1;
    long long sum = 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') {
        f = -1;
        c = getchar();
    }
    do {
        sum = (sum << 3) + (sum << 1) + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    return sum * f;
}
struct node;//AVL平衡树
typedef node *tree;
struct node {
    long long num, sz, h, liv, cnt;
    tree lc, rc;
    node() : num(0), h(1), sz(1), cnt(1), lc(NULL), rc(NULL){};
    node(long long x) : num(x), h(1), sz(1), cnt(1), lc(NULL), rc(NULL){};
};
 
tree t(NULL);
 
inline long long siz(tree &x) {
    if (x == NULL)
        return 0;
    return x->sz;
}
inline long long hig(tree &x) {
    if (x == NULL)
        return 0;
    return x->h;
}
inline void update(tree &x) {
    x->sz = siz(x->lc) + siz(x->rc) + x->cnt;
    x->h = max(hig(x->lc), hig(x->rc)) + 1;
}
 
inline void zig(tree &x) {
    tree k;
    k = x->rc;
    x->rc = k->lc;
    k->lc = x;
    update(k),update(x);
    x = k;
}
inline void zag(tree &x) {
    tree k;
    k = x->lc;
    x->lc = k->rc;
    k->rc = x;
    update(k),update(x);
    x = k;
} 
inline void zagzig(tree &x) {
    zig(x->lc);
    zag(x);
}
inline void zigzag(tree &x) {
    zag(x->rc);
    zig(x);
}
void ins(tree &x, long long t) {
    if (x == NULL) {
        x = new node(t);
        return;
    }
    if (x->num == t) {
        (x->cnt)++;
        update(x);
        return;
    }
    if (x->num < t) {
        ins(x->rc, t);
        update(x);
        if (hig(x->rc) - hig(x->lc) == 2) {
            if (t > (x->rc->num))
                zig(x);
            else
                zigzag(x);
        }
    } else {
        ins(x->lc, t);
        update(x);
        if (hig(x->lc) - hig(x->rc) == 2) {
            if (t < (x->lc->num))
                zag(x);
            else
                zagzig(x);
        }
    }
    update(x);
}
void del(tree &x, long long t) {
    if (x == NULL)
        return;
    if (x->num < t) {
        del(x->rc, t);
        update(x);
        if (hig(x->lc) - hig(x->rc) == 2) {
            if (hig(x->lc->lc) >= hig(x->lc->rc))
                zag(x);
            else
                zagzig(x);
        }
    } else if (x->num > t) {
        del(x->lc, t);
        update(x);
        if (hig(x->rc) - hig(x->lc) == 2) {
            if (hig(x->rc->rc) >= hig(x->rc->lc))
                zig(x);
            else
                zigzag(x);
        }
    } else {
        if (x->cnt > 1) {
            x->cnt--;
            update(x);
        } else if (x->lc && x->rc ) {
            tree k = x->rc;
            while (k->lc) k = k->lc;
            x->cnt = k->cnt, x->num = k->num;
            k->cnt = 1;
            del(x->rc, k->num);
            update(x);
            if (hig(x->lc) - hig(x->rc) == 2) {
                if (hig(x->lc->lc) >= hig(x->lc->rc))
                    zag(x);
                else
                    zagzig(x);
            }
        } else {
            if (x->lc != NULL)
                x = x->lc,x->lc=NULL;
            else if (x->rc != NULL)
                x = x->rc,x->rc=NULL;
            else
                x = NULL;
            return;
        }
    }
    update(x);
}
long long rk(tree &x, long long t) {
	if(x==NULL)return 1;
    if (x->num == t)
        return siz(x->lc) + 1;
    if (x->num < t)
        return siz(x->lc) + x->cnt + rk(x->rc, t);
    return rk(x->lc, t);
}
long long val(tree &x, long long t) {
    if(x==NULL)return -1;
    if (siz(x->lc) >= t)
        return val(x->lc, t);
    if (siz(x->lc) + (x->cnt) >= t)
        return x->num;
    return val(x->rc, t - (x->cnt) - siz(x->lc));
}
long long n,m,k,a[1000005],sum;
int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
    }
    for(int i=1;i<=m;i++)
    {
        long long kth=val(t,k);
        if(kth==-1)sum+=a[i];//不足k个，直接上
        else if(kth>a[i])sum=sum-kth+a[i];//替换
        ins(t,a[i]);
    }
    cout<<sum<<' ';
    for(int i=m+1;i<=n;i++)
    {
        long long lrk=rk(t,a[i-m]);//得到排名
        del(t,a[i-m]);
        if(lrk<=k)
        {
            sum-=a[i-m];
            if(val(t,k)!=-1)sum+=val(t,k);
            else//不存在kth，此时必须添加ai
            {
                sum+=a[i];
                ins(t,a[i]);
                cout<<sum<<' ';
                continue;
            }
        }
        
        long long kth=val(t,k);
        if(kth>a[i])sum=sum-kth+a[i];//同上
        ins(t,a[i]);
        cout<<sum<<' ';
    }
}
```

---

## 作者：honglan0301 (赞：0)

## 题意简述
给定 $n\ (n\leq2\times10^5)$ 个数的数列，求出对于每个 $i\ (i<=n-m+1,m\leq n)$，区间 $[i,i+m-1]$ 前 $k\ (k\leq m)$ 小的和。

## 题目分析
正解应该是用两个 multiset 维护当前区间的前 $k$ 小和剩下的数，从 $i=1$ 向后递推，我是复制了一份划分树板子，原理相同。

注意到从 $i$ 推到 $i+1$ 时，区间内仅有 $a_i,a_{i+m}$ 这两个数发生了变化，对其分类讨论。

如果 $a_i$ 在原来的前 $k$ 小中，则只需要比较 $a_{i+m}$ 与 $[i,i+m-1]$ 的第 $k+1$ 小的大小，让答案减掉 $a_i$ 加上较小的数。

如果 $a_i$ 不在原来的前 $k$ 小中，就比较 $a_{i+m}$ 与 $[i,i+m-1]$ 的第 $k$ 小的大小，如果前者更小就让答案减掉后者加上前者。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define int long long
 
using namespace std;
 
const int maxn = 200010;
int tree[20][maxn],sorted[maxn],nleft[20][maxn],cc[maxn];

void build(int l,int r,int dep){if(l==r)return;int mid=(l+r)>>1;int same=mid-l+1;int smid=sorted[mid];for(int i=l;i<=r;i++){if(tree[dep][i]<smid){same--;}}int lpos=l,rpos=mid+1;for(int i=l;i<=r;i++){nleft[dep][i]=(i==l)?0:nleft[dep][i-1];if(tree[dep][i]<smid||tree[dep][i]==smid&&same>0){tree[dep+1][lpos++]=tree[dep][i];nleft[dep][i]++;if(tree[dep][i]==smid){same--;}}else{tree[dep+1][rpos++]=tree[dep][i];}}build(l,mid,dep+1);build(mid+1,r,dep+1);}int search(int L,int R,int l,int r,int dep,int k){if(L==R){return tree[dep][R];}int mid=(L+R)>>1;int ly=(l==L)?0:nleft[dep][l-1];int cnt=nleft[dep][r]-ly;if(k<=cnt){int newl=L+ly;int newr=L+nleft[dep][r]-1;return search(L,mid,newl,newr,dep+1,k);}else{int newl=mid+1+(l-L-ly);int newr=newl+r-l-cnt;return search(mid+1,R,newl,newr,dep+1,k-cnt);}}
//上面是压过行的划分树板子
signed main()
{
	int n,m,k;
	cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
    	cin>>tree[0][i];
       	sorted[i]=tree[0][i];
    }
    sort(sorted+1,sorted+n+1);
    int nowsum=0;
    for(int i=1;i<=m;i++)
    {
    	cc[i]=tree[0][i];
    }
    sort(cc+1,cc+m+1);
    for(int i=1;i<=k;i++)
    {
    	nowsum+=cc[i];
    }
    cout<<nowsum<<endl;
    build(1,n,0);
    for(int i=2;i<=n-m+1;i++)//递推，分类讨论
    {
     	int lastk=search(1,n,i-1,i+m-2,0,k);
     	if(tree[0][i-1]<=lastk)
     	{
     		nowsum-=tree[0][i-1];
     		if(m==k)
     		{
     			nowsum+=tree[0][i+m-1];
     		}
     		else
     		{
     			int lastqq=search(1,n,i-1,i+m-2,0,k+1);
     			if(tree[0][i+m-1]<lastqq)
     			{
     				nowsum+=tree[0][i+m-1];
     			}
     			else
     			{
     				nowsum+=lastqq;
     			}
     		}
     	}
     	else
     	{
     		if(tree[0][i+m-1]<=lastk)
     		{
     			nowsum-=lastk;
     			nowsum+=tree[0][i+m-1];
     		}
     	}
       	cout<<nowsum<<endl;
    }
	return 0;
}
```


---

## 作者：wizardMarshall (赞：0)

$\large start$

[博客食用效果更佳](https://www.luogu.com.cn/blog/wizardMarshall/solution-at-abc281-e)

------

### 思路

数据范围：

$1 \le K \le M \le N \le 2 \times 10^5$

所以说，我们只能写在线性时间或 $O(nlogn)$ 内的算法。

一个区间一个区间来坑定是来不及滴，我们注意到这个区间和上一个区间的最小值序列其实没有多大差别，所以我们可以先算出第一个，然后一个一个推。

这道题我们可以建立两个 `set`（鄙人不才，不会写线段树smd，就献上蒟蒻神器 STL 吧），一个 `st` 存储当前区间中前 `k` 小的数，另一个 `ss` 存储其他的数。

我们一开始可以先求出第一个区间的前 `k` 大值。

然后，我们开始枚举左端点为 $[2,n-m+1]$。我们先处理被淘汰的元素，如果在 `st` 里有就把 `st` 里的踢出去（由于有重复元素**只踢一个**），否则 `ss` 里的踢出去。

然后处理新元素，如果小于 `st` 中的最大值就加入 `st`，否则加入 `ss`。注意：**这里不用管 `st` 元素的数量**。

随后，我们开始处理数量。由于最多相差2个元素，所以就可以判断把 `st` 的元素移到 `ss` ，或者是把 `ss` 的移到 `st`。这样就解决了问题。

每次 `st` 出现变动都要更新答案总和。

-----

### CODE：

```c
//防抄袭删开头，但是关键部分还是在的
#define int long long
signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }for (int i = 1; i <= m; i++) {
        t[i] = a[i];
    }sort(t + 1, t + m + 1);
    int nowsum = 0;
    for (int i = 1; i <= k; i++) {
        nowsum += t[i];
        st.insert(t[i]);
    }for (int i = k + 1; i <= m; i++) {
        ss.insert(t[i]);
    }cout << nowsum << " ";
    for (int i = 2; i <= n - m + 1; i++){
        if (!st.empty() && a[i - 1] <= *(--st.end())) {
            st.erase(st.lower_bound(a[i - 1]));
            nowsum -= a[i - 1];
        }else if(!ss.empty()){
            ss.erase(ss.lower_bound(a[i - 1]));
        }if (!st.empty() && a[i + m - 1] < *(--st.end())) {
            st.insert(a[i + m - 1]);
            nowsum += a[i + m - 1];
        }else {
            ss.insert(a[i + m - 1]);
        }if (st.size() > k) {
            nowsum -= *(--st.end());
            ss.insert(*(--st.end()));
            st.erase((--st.end()));
        }else if (!ss.empty() && st.size() < k) {
            nowsum += *ss.begin();
            st.insert(*ss.begin());
            ss.erase(ss.begin());
        }printf("%lld ", nowsum);
    }return 0;
}

```

-----

### PS:

在每次删除元素或者是判断的时候，一定要先判断这个 `set` 或者其他数据类型是否非空。否则会 $\textcolor{purple}{RE}$。本人亲测$\textcolor{purple}{RE}$一个点调了一天，最后还是求助万能谷民才A了这道题。

-----


$\large end$

---

## 作者：FyFive (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/Fy5-FyFive/articles/16976501.html)
#### 简要题意
> 求一个序列 $A$ 中每一个长为 $M$ 的连续段内前 $K$ 小的数之和。
>
> 按顺序输出每一个和。
>
> $1\leq K \leq M \leq N \leq 2 \times 10^5$，$1 \leq A_i \leq 10^9$。
#### Step 1
首先考虑 $K=M$ 时怎么做：

这个很简单，直接把 $M$ 个数加起来就行了。

然后是 $M=N$ 时：

同样也很简单，直接排序取前 $K$ 小的 $K$ 个数加起来输出。
#### Step 2
当 $K \neq M \neq N$ 时，直接排序是 $O(n^2\log n)$ 的，显然不可能过。

于是考虑从上一个连续段转移到下一个连续段。

现在处理完了上一个连续段之后，设当前段左端点为 $i$ $(1<i\leq N-M+1)$。

不难看出，相对于上一个段，只需要删掉第 $i-1$ 个数并加入第 $i+1$ 个段就是当前段了。

考虑这一删一增对答案的影响：

首先，如果删/增的数字不在前 $K$ 个的范围内，显然是不会产生任何影响的。

对于在前 $K$ 个以内的情况，直接删除并加上原来的 $K+1$ 位置上的数、直接插入并减去现在的 $K+1$ 位置上的数是可行的。在删、插 $O(1)$ 的前提下复杂度 $O(n\log n)$。

这里我直接用的 vector 自带的 insert() 和 erase()，最慢点 1.28s 还是冲过去了。

优化的话可以考虑用块状链表替代 vector，然后 $O(\sqrt{n})$ 删插，应该是可以稳过的。
#### more
正解貌似是线段树，不过我没打。(其实就是懒……)
#### Code
（vector，无优化）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,a[200005];
vector<int>s;
int fid(int x)
{
    int l=0,r=s.size()-1;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(s[mid]>=x) r=mid;
        else l=mid+1;
    }
    return l;
}//找到x所在的位置
int fidl(int x)
{
    if(x>s[s.size()-1]) return s.size();
    int l=0,r=s.size()-1;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(s[mid]>=x) r=mid;
        else l=mid+1;
    }
    return l;
}//找到x应该插入的位置
signed main()
{
    int sum=0;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=m;i++) s.push_back(a[i]);
    sort(s.begin(),s.begin()+m);
    for(int i=0;i<k;i++) sum+=s[i];
    printf("%lld\n",sum);
    if(k==m)
    {
        for(int i=2;i<=n-m+1;i++)
        {
            sum-=a[i-1];
            sum+=a[i+m-1];
            printf("%lld\n",sum);
        }
    }
    else
    {
        for(int i=2;i<=n-m+1;i++)
        {
            int zt1,zt2;
            zt1=fid(a[i-1]);
            s.erase(s.begin()+zt1);
            if(zt1<k) sum-=a[i-1],sum+=s[k-1];
            zt2=fidl(a[i+m-1]);
            if(zt2<k) sum-=s[k-1],sum+=a[i+m-1];
            s.insert(s.begin()+zt2,a[i+m-1]);
            printf("%lld\n",sum);
        }
    }
    return 0;
}
```

---

## 作者：Register_flicker (赞：0)

vector 可过赛时数据。

用 vector 存长度为$M$的序列，每次输出把后一个数插入进去，删除第一个数。

先把第一个长度为$M$的序列放到 vector 里，然后排序，把第一个输出算出来。之后每个输出前把前一个删掉，后一个插入到排序好的位置（可以用 lower_bound），判断以下情况：

如果新加进去的数在$K$个里面，把上一个的答案加上那个数。然后再判断如

否则就判断如果去掉的数在$K$里面，答案减去去掉的数，加上 vector 的第$K$个数。

把每个答案输出即可。

### 代码
```
#include<iostream>
#include<cmath>
#include<math.h>
#include<stdio.h>
#include<cstdlib>
#include<cstdio>
#include<string.h>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
long long n,m,k,a[200002],ans,ddd,bbb;
vector<long long> v;
int main()
{
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<m;i++)
	{
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	for(int i=0;i<k;i++)
	{
		ans+=v[i];
	}
	cout<<ans<<' ';
	for(int i=1;i+m-1<n;i++)
	{
		bbb=lower_bound(v.begin(),v.end(),a[i-1])-v.begin();
		v.erase(lower_bound(v.begin(),v.end(),a[i-1]));
		ddd=lower_bound(v.begin(),v.end(),a[i+m-1])-v.begin();
		v.insert(lower_bound(v.begin(),v.end(),a[i+m-1]),a[i+m-1]);
		if(ddd<k)
		{
			ans+=a[i+m-1];
			if(bbb>=k)
			{
				ans-=v[k];
			}
			else
			{
				ans-=a[i-1];
			}
		}
		else
		{
			if(bbb<k)
			{
				ans-=a[i-1];
				ans+=v[k-1];
			}
		}
		cout<<ans<<' ';
	}
}
```
寄

---

