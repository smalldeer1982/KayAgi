# Constructing the Array

## 题目描述

You are given an array $ a $ of length $ n $ consisting of zeros. You perform $ n $ actions with this array: during the $ i $ -th action, the following sequence of operations appears:

1. Choose the maximum by length subarray (continuous subsegment) consisting only of zeros, among all such segments choose the leftmost one;
2. Let this segment be $ [l; r] $ . If $ r-l+1 $ is odd (not divisible by $ 2 $ ) then assign (set) $ a[\frac{l+r}{2}] :=         i $ (where $ i $ is the number of the current action), otherwise (if $ r-l+1 $ is even) assign (set) $ a[\frac{l+r-1}{2}] := i $ .

Consider the array $ a $ of length $ 5 $ (initially $ a=[0,       0, 0, 0, 0] $ ). Then it changes as follows:

1. Firstly, we choose the segment $ [1; 5] $ and assign $ a[3] := 1 $ , so $ a $ becomes $ [0, 0, 1, 0, 0] $ ;
2. then we choose the segment $ [1; 2] $ and assign $ a[1] :=         2 $ , so $ a $ becomes $ [2, 0, 1, 0, 0] $ ;
3. then we choose the segment $ [4; 5] $ and assign $ a[4] :=         3 $ , so $ a $ becomes $ [2, 0, 1, 3, 0] $ ;
4. then we choose the segment $ [2; 2] $ and assign $ a[2] :=         4 $ , so $ a $ becomes $ [2, 4, 1, 3, 0] $ ;
5. and at last we choose the segment $ [5; 5] $ and assign $ a[5] := 5 $ , so $ a $ becomes $ [2, 4, 1, 3, 5] $ .

Your task is to find the array $ a $ of length $ n $ after performing all $ n $ actions. Note that the answer exists and unique.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
1
2
3
4
5
6```

### 输出

```
1 
1 2 
2 1 3 
3 1 2 4 
2 4 1 3 5 
3 4 1 5 2 6```

# 题解

## 作者：tbdsh (赞：2)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1353d)

[洛谷原题传送门](/problem/cf1353d)

[CF 原题传送门](https://codeforces.com/contest/1353/problem/d)

$t$ 组数据。每组数据给定一个长度为 $n$ 的全 $0$ 序列 $a$。

你要进行 $n$ 次操作，每次操作 $i$ 找到一个 $a$ 中最长的全 $0$ 区间。（如果有长度相同的，则选取左端点最小的。）

令该区间的左端点为 $l$，右端点为 $r$。将 $a_{\left\lfloor\frac{(l+r)}{2}\right\rfloor}\gets i$ 。

最后输出这个序列。

# 分析
因为每次要找一个最长的区间，所以我们考虑使用优先队列（`priority_queue`）实现。

每次取出当前序列中长度最大且左端点最小的区间进行修改。

然后再把更小的两个区间扔进优先队列中即可。

时间复杂度：$O(n\log_2 n)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, q, a[MAXN];
struct Node{
  int l, r;
  bool operator<(const Node &i)const{
    return r - l + 1 == i.r - i.l + 1 ? l > i.l : r - l + 1 < i.r - i.l + 1;//定义重载运算符。但注意优先队列默认大根堆，所以符号需要反着来。
  }
};

void Solve(){
  for (int i = 1; i <= n; i++){
    a[i] = 0;
  }
  int cnt = 1;
  cin >> n;
  priority_queue<Node> b;
  b.push({1, n});
  while (b.size()){
    auto x = b.top();
    b.pop();
    if (x.l > x.r){
      continue;
    }
    int mid = (x.l + x.r) >> 1;
    a[mid] = cnt++;
    b.push({x.l, mid - 1});
    b.push({mid + 1, x.r});
  }
  for (int i = 1; i <= n; i++){
    cout << a[i] << " \n"[i == n];
  }
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：osfly (赞：1)

大家好，我非常喜欢线段树，所以我用线段树通过了此题。

注意到题目要求动态维护最左的最长全 $0$ 子串，使用线段树维护即可。

每一个节点维护该区间最长全 $0$ 前缀（lmax），最长全 $0$ 后缀（rmax），最长全 $0$ 子串（maxn）以及其该子串左右端点（lpos，rpos）。

显然有：

$$
\begin{aligned}
lmax_k&=lmax_{lson}+lmax_{rson}\times[lmax_{lson}=len_{lson}]\\
rmax_k&=rmax_{rson}+rmax_{lson}\times[rmax_{rson}=len_{rson}]\\
maxn_k&=\max(maxn_{lson},rmax_{lson}+lmax_{rson},maxn_{rson})
\end{aligned}
$$

其中，当命题 $p$ 成立时，$[p]=1$，否则 $[p]=0$。

注意 `maxn` 的更新顺序。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=2e5+10;

int T;
int n;

struct seg
{
	struct node
	{
		int l,r,len;
		int maxn,lmax,rmax;
		int lpos,rpos;
	}t[N<<2];
	#define ls (k<<1)
	#define rs (k<<1|1)
	#define L t[k].l
	#define R t[k].r
	#define mid ((L+R)>>1)
	void pushup(int k)
	{
		t[k].lmax=t[ls].lmax;
		if(t[ls].lmax==t[ls].len) t[k].lmax+=t[rs].lmax;
		t[k].rmax=t[rs].rmax;
		if(t[rs].rmax==t[rs].len) t[k].rmax+=t[ls].rmax;
		
		t[k].maxn=0;
		if(t[ls].maxn>t[k].maxn)
		{
			t[k].maxn=t[ls].maxn;
			t[k].lpos=t[ls].lpos,t[k].rpos=t[ls].rpos;
		}
		if(t[ls].rmax+t[rs].lmax>t[k].maxn)
		{
			t[k].maxn=t[ls].rmax+t[rs].lmax;
			t[k].lpos=mid-t[ls].rmax+1;
			t[k].rpos=mid+t[rs].lmax;
		}
		if(t[rs].maxn>t[k].maxn)
		{
			t[k].maxn=t[rs].maxn;
			t[k].lpos=t[rs].lpos,t[k].rpos=t[rs].rpos;
		}
	}
	void build(int k,int l,int r)
	{
		L=l,R=r,t[k].len=r-l+1;
		if(L==R)
		{
			t[k].maxn=t[k].lmax=t[k].rmax=1;
			t[k].lpos=t[k].rpos=l;
			return ;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(k);
	}
	void update(int k,int x)
	{
		if(L==R)
		{
			t[k].maxn=t[k].lmax=t[k].rmax=0;
			t[k].lpos=t[k].rpos=0;
			return ;
		}
		if(x<=mid) update(ls,x);
		if(x>mid) update(rs,x);
		pushup(k);
	}
	#undef ls
	#undef rs
	#undef L
	#undef R
	#undef mid
}tree;

int ans[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		tree.build(1,1,n);
		for(int i=1;i<=n;i++)
		{
			int L=tree.t[1].lpos,R=tree.t[1].rpos;
			int pos=(L+R-(R-L)%2)>>1;
			ans[pos]=i;
			tree.update(1,pos);
		}
		
		for(int i=1;i<=n;i++) printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1353D)

---

一开始，这个序列全都为 $0$，后来，我总算学会了如何去操作序列。

我们取最长的全为 $0$ 的一段子序列，有重复的优先取最左边的。

所以我们可以用优先队列来维护，直接暴力。

```cpp
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

struct node {
	int l,r,len;
	bool operator < (const node &x) const {
		if (len == x.len) return l > x.l;
		else return len < x.len;
	}
};

const int maxn = 2e5;

priority_queue<node> q;

int times,n,a[maxn];

int main () {
	read(times);
	while (times --) {
		read(n);
		q.push(node{1,n,n - 1 + 1});
		for (int i = 1 ; i <= n ; ++ i) {
			node now = q.top();
			q.pop();
			int mid = (now.l + now.r) >> 1;
			a[mid] = i;
			q.push(node{now.l,mid - 1,(mid - 1 - now.l + 1)});
			q.push(node{mid + 1,now.r,(now.r - (mid + 1) + 1)});
		}
		for (int i = 1 ; i <= n ; ++ i) {
			print(a[i]),putchar(' ');
		}
		putchar('\n');
	}
	return 0;
} 
```

---

## 作者：45dino (赞：1)

每次拿出一个序列，拆成两半，放回去。

而且这个序列要最长最靠右。

可以直接用优先队列解决。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct seg{
	int l,r;
	bool operator<(const seg &x)const
	{
		int lena=r-l+1,lenb=x.r-x.l+1;
		if(lena==lenb)
			return l>x.l;
		return lena<lenb;
	}
};
int t,n,ans[200001];
priority_queue<seg> q;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		q.empty();
		scanf("%d",&n);
		q.push((seg){1,n});
		for(int i=1;i<=n;i++)
		{
			seg t=q.top();
			q.pop();
			ans[(t.l+t.r)/2]=i;
			if(t.l<=(t.l+t.r)/2-1)
				q.push((seg){t.l,(t.l+t.r)/2-1});
			if((t.l+t.r)/2+1<=t.r)
				q.push((seg){(t.l+t.r)/2+1,t.r});
		}
		for(int i=1;i<=n;i++)	
			cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：几何之舞丶 (赞：1)

注意到编号的顺序与区间长度有关，所以考虑如何快速地找到当前满足条件的区间就可以了。。
看数据范围，可以带一个log
这里可以考虑用优先队列封装pair或者封装结构体来实现就好了。

复杂度O（n log n），跑1e6没什么问题。

挺有意思的一道题目

具体细节写在代码里了。
代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<algorithm>
#define N 100005
#define INF 0x7fffffff
#define inf 0x3f
#define int long long
#define ll long long
#define lson (now<<1)
#define rson (now<<1|1)
#define pii pair<int ,int >
#define pushup1(now)  tr[now].sum=(tr[lson].sum+tr[rson].sum);
#define pushup2(now)  tr[now].sq=(tr[lson].sq+tr[rson].sq);
using namespace std;
const int mod=100000000;
inline ll read() {
	ll now=0;
	char c=getchar();
	ll f=1;
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		now=(now<<1)+(now<<3)+(c^48);
		c=getchar();
	}
	return f*now;
}

int n,m,t;
struct tmp1 //运算符重载<
  {
      int x,id;
      tmp1(int a,int b) {x = a;id=b;}
     bool operator<(const tmp1& a) const
	      {
        if(x==a.x)return id>a.id;
			return x<a.x;
     }
 };
priority_queue<tmp1> s;
int a[200005];
signed main(){
	//freopen("test.in","r",stdin);
	t=read();
	while(t--){
		n=read();
		memset(a,0,sizeof(a));//初始化
		s.push(tmp1(n,1));
		int step=1;
		while(!s.empty()){
			int l=s.top().id;
			int r=l+s.top().x-1;
			s.pop();
		//	cout<<l<<" "<<r<<endl;
			if((l+r)%2){ //判断奇数偶数
				int mid=(l+r-1)>>1;
				a[mid]=step;step++;
				if(l==r)continue;
				if(l<mid)
				s.push(tmp1(mid-l,l));
				if(mid<r)//判断
				s.push(tmp1(r-mid,mid+1));//压队列
			}
			else{
				int mid=(l+r)>>1;
				a[mid]=step;step++;
				if(l==r)continue;
				if(l<mid)
				s.push(tmp1(mid-l,l));
				if(mid<r)
				s.push(tmp1(r-mid,mid+1));
			}
		}
		for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
} 
```


---

## 作者：do_while_true (赞：1)

直接用优先队列模拟即可。

把区间封装成一个结构体，然后放到优先队列里面，重载运算符按**区间大小,左端点前后**排序，每次取出队头的元素，填上数之后把这个区间分裂成两个小区间，注意当这个区间长度为 $1$ 时不能再分裂，长度为 $2$ 时只能分离出一个。

[$\mathcal{Code}$](https://codeforces.com/contest/1353/submission/80151969)

---

