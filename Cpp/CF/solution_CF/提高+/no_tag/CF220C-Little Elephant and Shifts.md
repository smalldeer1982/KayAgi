# Little Elephant and Shifts

## 题目描述

The Little Elephant has two permutations $ a $ and $ b $ of length $ n $ , consisting of numbers from 1 to $ n $ , inclusive. Let's denote the $ i $ -th $ (1<=i<=n) $ element of the permutation $ a $ as $ a_{i} $ , the $ j $ -th $ (1<=j<=n) $ element of the permutation $ b $ — as $ b_{j} $ .

The distance between permutations $ a $ and $ b $ is the minimum absolute value of the difference between the positions of the occurrences of some number in $ a $ and in $ b $ . More formally, it's such minimum $ |i-j| $ , that $ a_{i}=b_{j} $ .

A cyclic shift number $ i $ $ (1<=i<=n) $ of permutation $ b $ consisting from $ n $ elements is a permutation $ b_{i}b_{i+1}...\ b_{n}b_{1}b_{2}...\ b_{i-1} $ . Overall a permutation has $ n $ cyclic shifts.

The Little Elephant wonders, for all cyclic shifts of permutation $ b $ , what is the distance between the cyclic shift and permutation $ a $ ?

## 样例 #1

### 输入

```
2
1 2
2 1
```

### 输出

```
1
0
```

## 样例 #2

### 输入

```
4
2 1 3 4
3 4 2 1
```

### 输出

```
2
1
0
1
```

# 题解

## 作者：__ikun__horro__ (赞：1)

## Solution

我们先来观察样例 #2：

```
4
2 1 3 4
3 4 2 1
```

先求出 $b$ 数组每一次滚动和 $a$ 数组每个数位置的差值（不取绝对值）：

| 轮数 \ 数字 | $\bm 1$ | $\bm 2$ | $\bm 3$ | $\bm 4$ |
| :-: | :-: | :-: | :-: | :-: |
| $\bm 1$ | $-2$ | $-2$ | $\color{red} 2$ | $2$ |
| $\bm 2$ | $-1$ | $-1$ | $\color{red} -1$ | $\color{blue} 3$ |
| $\bm 3$ | $0$ | $\color{green} 0$ | $0$ | $\color{blue} 0$ |
| $\bm 4$ | $1$ | $\color{green} -3$ | $1$ | $1$ |

容易发现，每两轮相邻的操作间，$n-1$ 个数字加上 $1$，还有一个数字减去了 $(n-1)$。

我们可以用一个 $\text {mutiset}$ 维护所有的位置差值。而且大部分的数字都是加上 $1$ 的，所以我们可以用一个偏移量 $d$，第 $i$ 轮的偏移量 $d=i-1$。使用 $x-d$ 来维护 $x$ 这个数，这样每轮只需要将一个数减去 $n$。

| 轮数 \ 数字 | $\bm 1$ | $\bm 2$ | $\bm 3$ | $\bm 4$ |
| :-: | :-: | :-: | :-: | :-: |
| $\bm 1$ | $-2$ | $-2$ | $\color{red} 2$ | $2$ |
| $\bm 2$ | $-2$ | $-2$ | $\color{red} -2$ | $\color{blue} 2$ |
| $\bm 3$ | $-2$ | $\color{green} -2$ | $-2$ | $\color{blue} -2$ |
| $\bm 4$ | $-2$ | $\color{green} -4$ | $-2$ | $-2$ |

这样，我们每一轮只需取出一个最接近 $-d$ 的数 $x$，输出 $| x+d |$ 即可。

那么每次到底要让哪一个数减去 $n$ 呢？观察一下，第 $i$ 轮就让 $b_i$ 所对应的数减去 $n$。这样就做完了。

注意：$\text{multiset}$ 去掉数字时 $\text{erase}$ 函数里要放指针，否则会删除值相同的所有的数。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N], p[N];
multiset<int> mango;

inline void sol() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		p[a[i]] = i;
	}

	auto calc = [=] (int x) {
		return p[b[x]] - x;
	};

	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		mango.insert(calc(i));
	}

	for (int i = 1; i <= n; i++) {
		int delta = i - 1;

		// for (auto i : mango) {
		// 	cout << i << " ";
		// }
		// cout << "\n";
		// for (auto i : mango) {
		// 	cout << i + delta << " ";
		// }
		// cout << "\n";

		auto it = mango.lower_bound(-delta);
		int Min = 0x3f3f3f3f3f3f3f3f;

		if (it != mango.end()) {
			Min = min(Min, abs(*it + delta));
		}
		if (it != mango.begin()) {
			Min = min(Min, abs(*(--it) + delta));
		}

		cout << Min << "\n";

		it = mango.lower_bound(calc(i));

		if (it != mango.end()) mango.erase(it);
		mango.insert(calc(i) - n);

		// cout << "del " << calc(i) + delta << "\n";
		// cout << "add " << calc(i) - n + delta + 1 << "\n";
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	// init();
	int T = 1;
	// cin >> T;
	while (T--) sol();
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

另一篇太神仙了没看懂，写一个人能看的懂的。

观察到对于一次循环移动，一个元素要么距离 $ -1 $，要么被循环移动到序列的最后，于是可以考虑开一个集合维护当前的距离，先把询问离线下来，然后按顺序回答询问，每次二分当前的最短距离，然后倒着遍历一遍，考虑之前的最小值能更新当前距离的情况，正反遍历一遍即可。

因为涉及到二分以及指针的移动。于是考虑用到 set 实现，时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int to[101000];
int dif[101000];
int ans[101000];
int main()
{
    int n,i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        int a;
        scanf("%d",&a);
        to[a]=i;
    }
    for(i=1;i<=n;i++)
    {
        int a;
        scanf("%d",&a);
        dif[i]=to[a]-i;
        ans[i]=101000;
    }
    ans[0]=101000;
    set<int> XD;
    for(i=1;i<=n;i++)
    {
        XD.insert(dif[i]);
        auto it=XD.lower_bound(n-i);
        if(it!=XD.end())
        ans[i]=min(ans[i],abs(*it-(n-i)));
        if(it!=XD.begin())
        {
            it--;
            ans[i]=min(ans[i],abs(*it-(n-i)));
        }
    }
    XD.clear();
    for(i=n;i>=1;i--)
    {
        XD.insert(dif[i]);
        auto it=XD.lower_bound(-(i-1));
        if(it!=XD.end())
        ans[i-1]=min(ans[i-1],abs(*it+(i-1)));
        if(it!=XD.begin())
        {
            it--;
            ans[i-1]=min(ans[i-1],abs(*it+(i-1)));
        }
    }
    ans[0]=min(ans[0],ans[n]);
    for(i=0;i<n;i++)
    printf("%d\n",ans[i]);
}
```


---

## 作者：2018ty43 (赞：1)

### 题意
在排列 $b$ 的滚动过程中，维护排列 $a$ 与 $b$ 每个相同的数的距离的最小值。
### 思路
可以发现对于每个数，对答案的贡献是一个三条以内线段的函数，可以直接把线段截距与定义域预处理，用扫描线加优先队列分别维护滚动过程斜率 $\pm1$ 直线的截距。  
具体细节看代码。
### 代码
```
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
int n;
int a[100009],A[100009],b[100009];
struct T
{
	int b,l,r;
	bool operator<(const T&aa)const
	{
		return this->b>aa.b;
	}
};
std::priority_queue<T>qu1;//up，斜率 +1
std::vector<T>q1;
std::priority_queue<T>qu2;//down，斜率 -1
std::vector<T>q2;
bool CC(T aa,T bb)
{
	return aa.l<bb.l;
}
int min(int u,int v)
{
	return (u<v)?u:v;
}
int main()
{
	scanf("%d",&n);
	for(int i(1);i<=n;++i)scanf("%d",a+i),A[a[i]]=i;
	for(int i(1);i<=n;++i)
	{
		scanf("%d",b+i);
		//预处理出三条线段的截距与定义域
		if(A[b[i]]>i)
		{
			q1.push_back((T){A[b[i]]-i,0,i-1});
			q2.push_back((T){i+n-A[b[i]],i,i+n-A[b[i]]});
			if(A[b[i]]!=i+1)q1.push_back((T){A[b[i]]-i-n,i+n-A[b[i]]+1,n-1});
		}
		else
		{
			if(A[b[i]]<i)
			{
				q2.push_back((T){i-A[b[i]],0,i-A[b[i]]});
				if(A[b[i]]!=1)q1.push_back((T){A[b[i]]-i,i-A[b[i]]+1,i-1});
				if(i!=n)q2.push_back((T){n-A[b[i]]+i,i,n-1});
			}
			else
			{
				q1.push_back((T){0,0,i-1});
				if(i!=1)q2.push_back((T){n,i,n-1});
			}
		}
	}
	std::sort(q1.begin(),q1.end(),CC);
	std::sort(q2.begin(),q2.end(),CC);
	for(int i(0),j(0),k(0);i<n;++i)
	{
		while(j<q1.size()&&q1[j].l<=i)
		{
			qu1.push(q1[j]);
			++j;
		}
		while(k<q2.size()&&q2[k].l<=i)
		{
			qu2.push(q2[k]);
			++k;
		}
		//超过定义域的删除
		while(!qu1.empty()&&qu1.top().r<i)qu1.pop();
		while(!qu2.empty()&&qu2.top().r<i)qu2.pop();
		int ans(0x7f7f7f7f);
		if(!qu1.empty())ans=min(ans,qu1.top().b+i);
		if(!qu2.empty())ans=min(ans,qu2.top().b-i);
		printf("%d\n",ans);
	}
	return (0-0)/1.;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给两个 $1$ 到 $n$ 的排列，当 $a_i=b_j$ 时，距离 $d=|i-j|$，每次将序列 $b$ 左移一位，开头第一个数移到最后一个。移动 $n-1$ 次，求每次移动后的距离最小值。
## 分析
一次函数线段树。

$b$ 不断循环左移,判断每次最小的 $|i-j|$，$a_i=b_j$。仔细观察发现，每个 $b_i$ 移动时，$|i-j|$ 呈现多个一次函数图像。可以用线段树来维护这些一次函数图像，线段树维护一次函数，当两个函数在区间没有交点时判断哪个在图像较下的位置，然后覆盖。当有交点时，保留最优，将另一条传下去。
## 代码

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define maxn 100005
#define INF 0x7fffffff

struct TreeNodeType {
    int l,r,k,b,mid;
    
    bool if_;
};
struct TreeNodeType tree[maxn<<2];

int n,ai[maxn],p[maxn],X;

inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}

void tree_build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r,tree[now].mid=l+r>>1;
    if(l==r) return ;
    tree_build(now<<1,l,tree[now].mid);
    tree_build(now<<1|1,tree[now].mid+1,r);
}

double com(int k1,int b1,int k2,int b2)
{
    if(k1==k2) return 0;
    return (double)(b2-b1)/(double)(k1-k2);
}

void tree_down(int now,int k,int b)
{
    if(!tree[now].if_)
    {
        tree[now].if_=true,tree[now].k=k,tree[now].b=b;
        return ;
    }
    double x=com(k,b,tree[now].k,tree[now].b);
    if(x<=tree[now].l||x>=tree[now].r)
    {
        double mid=(double)(tree[now].l+tree[now].r)/2;
        if(mid*k+b<mid*tree[now].k+tree[now].b) tree[now].k=k,tree[now].b=b;
        return ;
    }
    if(x<=tree[now].mid)
    {
        if(k>tree[now].k) tree_down(now<<1,k,b);
        else
        {
            tree_down(now<<1,tree[now].k,tree[now].b);
            tree[now].k=k,tree[now].b=b;
        }
    }
    else
    {
        if(k<tree[now].k) tree_down(now<<1|1,k,b);
        else
        {
            tree_down(now<<1|1,tree[now].k,tree[now].b);
            tree[now].k=k,tree[now].b=b;
        }
    }
}

void tree_add(int now,int l,int r,int k,int b)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        if(tree[now].if_)
        {
            if(k==tree[now].k&&b==tree[now].b); 
            else tree_down(now,k,b);
        }
        else tree[now].if_=true,tree[now].k=k,tree[now].b=b;
        return ;
    }
    if(l>tree[now].mid) tree_add(now<<1|1,l,r,k,b);
    else if(r<=tree[now].mid) tree_add(now<<1,l,r,k,b);
    else
    {
        tree_add(now<<1,l,tree[now].mid,k,b);
        tree_add(now<<1|1,tree[now].mid+1,r,k,b);
    }
}

void tree_query(int now,int to)
{
    if(tree[now].if_) X=min(X,tree[now].k*to+tree[now].b);
    if(tree[now].l==tree[now].r) return ;
    if(to<=tree[now].mid) tree_query(now<<1,to);
    else tree_query(now<<1|1,to);
}

int main()
{
    in(n);int pos,debug;
    for(int i=1;i<=n;i++) in(ai[i]);
    for(int i=1;i<=n;i++) in(pos),p[pos]=i;
    tree_build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        if(i<p[ai[i]])
        {
            tree_add(1,1,p[ai[i]]-i+1,-1,p[ai[i]]+1-i);
            if(i!=1) tree_add(1,p[ai[i]]-i+2,p[ai[i]],1,i-p[ai[i]]-1);
            if(p[ai[i]]!=n) tree_add(1,p[ai[i]]+1,n,-1,n-i+p[ai[i]]+1);
        }
        if(i>p[ai[i]])
        {
            tree_add(1,1,p[ai[i]],1,i-p[ai[i]]-1);
            tree_add(1,p[ai[i]]+1,p[ai[i]]+n-i+1,-1,n-i+p[ai[i]]+1);
            if(i-p[ai[i]]>1) tree_add(1,p[ai[i]]+n-i+2,n,1,i-n-p[ai[i]]-1);
        }
        if(i==p[ai[i]])
        {
            tree_add(1,1,i,1,-1);
            if(i!=n) tree_add(1,i+1,n,-1,n+1);
        }
    }
    for(int i=1;i<=n;i++) X=INF,tree_query(1,i),printf("%d\n",X);
    return 0;
}
```

---

