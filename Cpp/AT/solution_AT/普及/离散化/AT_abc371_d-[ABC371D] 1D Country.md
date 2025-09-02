# [ABC371D] 1D Country

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc371/tasks/abc371_d

数直線上に $ N $ 個の村があります。$ i $ 番目の村は座標 $ X_i $ にあり、$ P_i $ 人の村人がいます。

$ Q $ 個のクエリに答えてください。$ i $ 番目のクエリは以下の形式です。

- 整数 $ L_i,R_i $ が与えられる。座標が $ L_i $ 以上 $ R_i $ 以下の村に住んでいる村人の人数の総数を求めよ。

## 说明/提示

### 制約

- $ 1\leq\ N,Q\leq\ 2\times\ 10^5 $
- $ -10^9\leq\ X_1\ <\ X_2\ <\ \ldots\ <\ X_N\ \leq\ 10^9 $
- $ 1\leq\ P_i\leq\ 10^9 $
- $ -10^9\leq\ L_i\ \leq\ R_i\ \leq\ 10^9 $
- 入力される数値は全て整数

### Sample Explanation 1

$ 1 $ 番目のクエリについて考えます。座標が $ 1 $ 以上 $ 1 $ 以下の村は、座標 $ 1 $ にある村で、村人は $ 1 $ 人います。よって答えは $ 1 $ です。 $ 2 $ 番目のクエリについて考えます。座標が $ 2 $ 以上 $ 6 $ 以下の村は、座標 $ 3 $ にある村と座標 $ 5 $ にある村で、村人はそれぞれ $ 2 $ 人と $ 3 $ 人います。よって答えは $ 2+3=5 $ です。

## 样例 #1

### 输入

```
4
1 3 5 7
1 2 3 4
4
1 1
2 6
0 10
2 2```

### 输出

```
1
5
10
0```

## 样例 #2

### 输入

```
7
-10 -5 -3 -1 0 1 4
2 5 6 5 2 1 7
8
-7 7
-1 5
-10 -4
-8 10
-5 0
-10 5
-8 7
-8 -3```

### 输出

```
26
15
7
26
18
28
26
11```

# 题解

## 作者：XXh0919 (赞：19)

马上到我生日了，来写一波题解。

### 题意

给你一条数轴，上面的一些点有一些数值，共 $Q$ 次询问，问你每一个区间 $[L,R]$ 的数值之和是多少。

### 解法

看到题后相信大多数人想到了前缀和。前缀和部分很简单，主要就是该如何输出。因为输入的 $L$ 和 $R$ 很多是没有出现在输入中每一个点的位置，所以考虑将 $L$ 和 $R$ 给“离散化”一下。
这里的“离散化”指的是将 $L$ 和 $R$ 所对应的数值映射成一个在 $1$ 到 $N$ 范围内的一个数，不仅是因为上述原因，还因为 $L$ 和 $R$ 有可能是负数。因此要对 $L$ 和 $R$ 进行离散化。至于离散化，直接用二分函数就行了，在此就不细讲了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define IOS cin.tie(0)->sync_with_stdio(0)
using namespace std;
const int N=1e7+15;

int n,q;
int x[N];
int p[N];
int num[N];
int sum[N];

signed main(){
	IOS;
	cin>>n;
	rep(i,1,n)cin>>x[i];
	rep(i,1,n)cin>>p[i],sum[i]=sum[i-1]+p[i];
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
//      int k=r;//后面有解释
		l=lower_bound(x+1,x+n+1,l)-x;
		r=upper_bound(x+1,x+n+1,r)-x;//用 lower_bound 也可以，只不过要特判一下（如下）

//      r=lower_bound(x+1,x+n+1,r)-x;
//      if(k==x[r])cout<<sum[r]-sum[l-1]<<endl;//因为 lower_bound 在查找时可能会查到相同的位置，所以要加个判断（k 是原来 R 点的位置）
//	    else cout<<sum[r-1]-sum[l-1]<<endl;

		cout<<sum[r-1]-sum[l-1]<<endl;
	}
	return 0;
} 
```
求个赞，不过分吧？

---

## 作者：hzxphy (赞：7)

没有困难的树状数组，只有勇敢的作者。（雾

还没有树状数组的题解，赶紧来一发。

## 题目大意
给定你 $n$ 个地址，在第 $a_i$ 位置有 $p_i$ 个人。给定 $q$ 个询问，每次查询 $l_i$ 到 $r_i$ 中有多少个人。

## 思路
显然，区间问题选择树状数组。

但是太大了，怎么处理？显然，最多不重复坐标为 $n+2\times q$。所以直接把所有出现过的坐标离散化即可。
## 代码（见其他题解的二分，这里不多说）
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=2e5;
long long n,q;
long long a[MAXN+1],b[MAXN+1];
int main(){
    cin>>n;
    for(long long i=1;i<=n;i++)cin>>a[i];
    for(long long i=1;i<=n;i++){
        cin>>b[i];b[i]=b[i-1]+b[i];
    }
    cin>>q;
    while(q--){
        long long x,y;cin>>x>>y;
        long long r=upper_bound(a+1,a+1+n,y)-a-1;
        long long l=lower_bound(a+1,a+1+n,x)-a;
        if(r<l)cout<<0<<'\n';
        else{
            cout<<b[r]-b[l-1]<<'\n';
        }
    }
    return 0;
}

```
## 代码（树状数组）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long tree[600010],N,Q;
long long lowbit(long long x){
    return x&-x;
}
void update(long long x,long long d){
    while(x<=N+2*Q){
        tree[x]+=d;
        x+=lowbit(x);
    }
}
long long sum(long long x){
    long long ans=0;
    while(x>=1){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
pair<long long,pair<long long,bool> >G[600010];
long long x[200001],y[200001];
unordered_map<long long,long long>up;
int main(){
    cin>>N;
    for(long long i=1;i<=N;i++){
        cin>>G[i].first;
    }
    for(long long i=1;i<=N;i++){
        cin>>G[i].second.first;
    }cin>>Q;
    for(long long i=1;i<=Q;i++){
        cin>>G[2*i-1+N].first>>G[2*i+N].first;
        G[2*i-1+N].second.second=true;
        G[2*i+N].second.second=true;
        x[i]=G[2*i-1+N].first,y[i]=G[2*i+N].first;
    }
    sort(G+1,G+1+N+2*Q);
    long long maxp=-LLONG_MAX,X=0;
    for(long long i=1;i<=N+2*Q;i++){
        if(G[i].first==maxp){
            if(!G[i].second.second){
                update(up[G[i].first],G[i].second.first);
            }
        }
        else{
            maxp=G[i].first;X++;
            up[maxp]=X;
            if(!G[i].second.second){
                update(up[G[i].first],G[i].second.first);
            }
        }
    }
    for(long long i=1;i<=Q;i++){
        cout<<sum(up[y[i]])-sum(up[x[i]]-1)<<'\n';
    }
    return 0;
}


```

---

## 作者：hjyowl (赞：6)

### 题目大意

给定你 $n$ 个地址，在第 $a_i$ 位置有 $p_i$ 个人，给定 $m$ 个询问，每次查询位置 $l_i$ 到 $r_i$ 之间有多少个人。

### 思路

首先，把 $a$ 和 $p$ 的值捆绑在一起，然后按照 $a$ 从小到大排序。

接下来，我们把结构体里排过序的 $a$ 和 $p$ 值给分离到另外两个数组里面（这里我们假设是 $fa$ 和 $fp$ 数组），我们根据 $fp$ 数组的值用来求一个前缀和（其实这有点像离散化）。

接下来，我们在 $fa$ 中二分到第一个大于等于 $l$ 的位置和第一个小于等于 $r$ 的位置，然后直接用这一段的前缀和来计算多少个人即可。

时间复杂度：$\Theta(n\log n)$。

### 实现细节：

务必使用 $64$ 位整型。

对于二分出来的值，记得判断几个边界即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010;
struct owl{
	long long a,p;
}x[N];
long long n,m;
long long h[N];
bool cmp(owl x,owl y){
	return x.a < y.a;
}
long long a[N],s[N];
int main(){
	/*
	01
	10
	
	00
	00
	*/
	cin >> n ;
	for (long long i = 1; i <= n; i ++ ){
		cin >> x[i].a;
	}
	for (long long i = 1; i <= n; i ++ ){
		cin >> x[i].p;
	}
	sort(x + 1,x + 1 + n,cmp);
	for (long long i = 1; i <= n; i ++ ){
		a[i] = x[i].a;
		s[i] = s[i - 1] + x[i].p;
	}
	cin >> m;
	while (m -- ){
		long long l,r;
		cin >> l >> r;
		long long ll = lower_bound(a + 1,a + 1 + n,l) - a;
		if (ll == n + 1){
			cout << 0 << endl;
			continue;
		}
		long long rr = upper_bound(a + 1,a + 1 + n,r) - a - 1;
		rr = min(rr,n);
		cout << s[rr] - s[ll - 1] << endl;
	}
	return 0;
}
```

---

## 作者：wuenzi (赞：5)

### 暴力
如果你使用暴力

![](https://cdn.luogu.com.cn/upload/image_hosting/d46hqfid.png)

~~图片是我某一个题的，不是这个题的~~


### 正解
首先按照位置从左到右排序。

对于每次询问，我们可以二分一个左端点，二分一个右端点。所以，我们只用算出这部分的和即可。

如计算区间和可以使用前缀和，用 $O(n)$ 预处理，再 $O(1)$ 访问即可。

二分总复杂度为 $O(2\times \log n)$，去掉常数为 $O(\log n)$，总复杂度 $O(Q \times \log n)$。

### AC CODE
```
/*********************************************************************
    程序名:
    版权:
    作者:
    日期: 2024/9/14 20:54:29
    说明:
*********************************************************************/

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node{
	int x,y;
}a[200005];
bool cmp(node x,node y){
	return x.x<y.x;
}
int h[200005];
int q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x;
	for(int i=1;i<=n;i++)cin>>a[i].y;
	
	sort(a+1,a+n+1,cmp); //排序 
	
	for(int i=1;i<=n;i++)h[i]=h[i-1]+a[i].y;//前缀和 
	cin>>q;
	while(q--){//询问 
		int o,p;
		cin>>o>>p;
		if(o>a[n].x||p<a[1].x){
			cout<<0<<endl;
			continue;
		}
		int l=1,r=n,ans;
		while(l<=r){//二分
			int mid=(l+r)>>1;
			if(a[mid].x>=o){
				ans=mid;
				r=mid-1;
			}else l=mid+1;
		}
		int j=h[ans-1];
//		cout<<ans<<" "<<h[ans]<<endl;
		l=1,r=n,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(a[mid].x<=p){
				ans=mid;
				l=mid+1;
			}else r=mid-1;
		}
		cout<<h[ans]-j<<endl;
	}
	return 0;
}




```

---

## 作者：chenxi2009 (赞：1)

[专栏](https://www.luogu.com.cn/article/ddhlo5za)食用效果更佳。
# 题目描述

**形式化题意**

整数轴上有 $N$ 个点，从左往右的第 $i$ 个点具有一个权值 $P_i$，其位置记为 $X_i$。进行 $Q$ 次询问，第 $i$ 次询问 $[L_i,R_i]$ 之间的点权和。

# 数据范围

$1\le N\le 2\times 10^5$\
$-10^9\le X_1<X_2<\cdots X_N\le10^9$\
$1\le P_i\le10^9$\
$-10^9\le L_i\le R_i\le 10^9$\
$N\in \Z,X_i,P_i\in\Z,L_i,R_i\in\Z$

# 思路

如果 $X$ 的范围足够小，那么根据位置进行前缀和就能通过。

既然 $X$ 的范围很大，但 $N$ 的大小可以接受，那么我们可以对整点进行前缀和。即令

$$
s_i=\sum_{j=1}^{i}P_j (i\in [1,N])
$$

所以有

$$
s_i=s_{i-1}+P_i(i\in[1,N])
$$

特别地，令 $s_0=0$。

我们可以二分找到 $[L,R]$ 区间中的最后一个整点 $last_1$，再找到 $[-10^9,L)$ 中的最后一个节点 $last_2$，答案即为

$$
\sum_{i=last_2+1}^{last_1}P_i=\sum_{i=1}^{last_1}P_i - \sum_{i=1}^{last_2}P_i=s_{last1}-s_{last2}
$$

我们发现其实这个问题就是二分 + 前缀和。

时间复杂度 $O(N+Q\log N)$。若 $N$、$Q$ 同阶，则为 $O(N\log N)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x[200001],p[200001],le,ri,l,r,mid;
long long s[200001],ans;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&x[i]);
	} 
	for(int i = 1;i <= n;i ++){
		scanf("%d",&p[i]);
		s[i] = s[i - 1] + p[i];
	}
	scanf("%d",&q);
	for(int i = 1;i <= q;i ++){
		scanf("%d%d",&le,&ri);
		l = 0,r = n;
		while(l < r){
			mid = l + r + 1 >> 1;
			if(x[mid] <= ri){
				l = mid;
			}
			else{
				r = mid - 1;
			}
		}
		ans = s[l];
		l = 0,r = n;
		while(l < r){
			mid = l + r + 1 >> 1;
			if(x[mid] < le){
				l = mid;
			}
			else{
				r = mid - 1;
			}
		}
		ans -= s[l];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：AT_abc371_d [ABC371D] 1D Country

# 思路

如果我们能够计算出坐标小于或等于 $D$ 的村民数量，那么问题就可以解决，因为查询的答案可以通过 $f(R_i) - f(L_i - 1)$ 来找到，其中 $f(D)$ 是对该子问题的处理。

首先，假设 $x$ 和 $D$ 的值在 $0$ 和 $n$ 之间。在这种情况下，我们可以简单地预先计算累积和，就可以在 $O(1)$ 时间内找到答案。

但原始问题的难点在于 $x$ 和 $D$ 的绝对值很大。为了解决这个问题，我们可以使用二分查找。

通过二分查找可以找到坐标为 $D$ 或更小的最右侧的村庄。结合累积和，可以找到 $(D)$。

时间复杂度：$O(\log n)$

---

## 作者：GenesisCrystal (赞：0)

思路很奇妙

## Solution

考虑离线处理。

我们使用 map 来存储每一个位置的人的个数，因为 map 遍历只会遍历已知的，所以我们要把每一个 $l_i, r_i$ 都存进 map 里面，然后离线处理前缀和，最后再输出即可。

## Code

[Submmision](https://atcoder.jp/contests/abc371/submissions/57774553)

---

## 作者：WuMin4 (赞：0)

## 题意
给定一条数轴和 $N$ 个村庄，村庄 $i$ 在位置 $X_i$，有 $P_i$ 人。有 $Q$ 个询问，每个询问问 $L_i$ 到 $R_i$ 有多少人。  
## 思路
虽然 $X,L,R$ 的范围很大，但是 $N,Q$ 并不大，于是将位置和询问进行离散化后计算前缀和统计答案。  
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,b[600005],len,len2;
long long c[600005];
struct node{
	int x,y;
}a[200005],qu[200005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x,b[++len]=a[i].x;
	for(int i=1;i<=n;i++)
		cin>>a[i].y;
	cin>>q;
	for(int i=1;i<=q;i++)
		cin>>qu[i].x>>qu[i].y,b[++len]=qu[i].x,b[++len]=qu[i].y;
	//---离散化---
	sort(b+1,b+1+len);
	len2=unique(b+1,b+1+len)-b-1;
	for(int i=1;i<=n;i++)
		a[i].x=lower_bound(b+1,b+1+len2,a[i].x)-b;
	for(int i=1;i<=q;i++)
		qu[i].x=lower_bound(b+1,b+1+len2,qu[i].x)-b,
		qu[i].y=lower_bound(b+1,b+1+len2,qu[i].y)-b;
	//---计算前缀和---
	for(int i=1;i<=n;i++)
		c[a[i].x]+=a[i].y;
	for(int i=1;i<=600000;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=q;i++)
		cout<<c[qu[i].y]-c[qu[i].x-1]<<endl;
	return 0;
}
```

---

## 作者：SnowFlavour (赞：0)

# 题意

在一条直线上一些村庄，每个村庄有一定数量的人口。进行若干次询问，每次输出一个区间内的村民数量。

# 题解

首先考虑暴力：用前缀和维护从最开始的坐标到当前坐标的村民数量总和。也就是预处理一遍，然后每一次 $O(1)$ 查询即可。

然而这里的数据范围是：

> $-10^9<X_i<10^9$

显然，刚才的做法是不行的。注意到这里我们其实做了很多的无用功，因为虽然数据范围极大，但是大部分坐标都是空的，换句话说，就是村庄数量很少。

这种情况下，我们可以考虑只对有村庄的地方算前缀和，也就是说，利用前缀和维护从左到右第一个村庄到当前村庄的村民总数。

然而这样的话，区间查询怎么办呢？这里，提供两种思路：

1. 利用二分找到区间左端点右边的第一个村庄和右端点左边的第一个村庄。这些村庄就是答案。
2. 把这些区间也看作一个村民数为 $0$ 的村庄，然后在算前缀和的时候算上，这样就可以直接离线运算，每一次用两个端点所对应的“村庄”来计算。

好像第二种做法会简单一些，但是一个严重的问题就是输入的数据并没有排序，那么你在把这些端点排序以后，就难以确定哪一个才是你曾经插入的虚拟村庄了。

场上我最开始想到了第二种，后来没写出来就写了个二分。

注意一个[细节](https://atcoder.jp/contests/abc371/submissions/57787132)：写二分的时候要判断边界情况（即这个区间根本没有覆盖任何村庄）。

# Code

```cpp
#include<iostream>
#include<algorithm>
#include<map>
#define int long long
using namespace std;
const int N=2e5+10;
struct pps{int id,p;};
bool cmp(pps a,pps b){
	return a.id<b.id;
}
pps ps[N];
int sgm[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>ps[i].id;
	for(int i=1;i<=n;i++)cin>>ps[i].p;
	sort(ps+1,ps+n+1,cmp);
	for(int i=1;i<=n;i++)sgm[i]=sgm[i-1]+ps[i].p;
	int q;
	cin>>q;
	while(q--){
		int ll,rr;
		cin>>ll>>rr;
		int l=1,r=n;
		while(l<r){
			int mid=(l+r)>>1;
			if(ps[mid].id<ll)l=mid+1;
			else r=mid;
		}
		int dw=sgm[l-1];
		l=1,r=n;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(ps[mid].id<=rr)l=mid;
			else r=mid-1;
		}
		int up=sgm[l];
        if(ll>ps[n].id||rr<ps[1].id)cout<<0<<endl;
		else cout<<up-dw<<endl;
	}
}
```

---

## 作者：zdd6310 (赞：0)

# [ABC371D] 1D Country

## Description

给定你 $n$ 个地址，在第 $a_i$ 位置有 $p_i$ 个人。有 $m$ 个询问，每次查询位置 $[L_i,R_i]$ 之间有多少个人。

## solution

不用二分。

这边发现绝对位置无关紧要。

所以将 $a_i$，$L_i$，$R_i$ 全部放在一起离散化。

这样值域就是 $4\times 10^5$ 的。

直接记录前缀和，查询时 $O(1)$ 查询就可以了。

复杂度 $O(n\log n+q)$。

---

## 作者：Cosine_Func (赞：0)

数轴上有 $N$ 个点，坐标和权值分别为 $X_i$ 和 $P_i$。给定 $Q$ 次操作，求 $\left [ L_i,R_i \right ]$ 坐标区间内的权值和。

如果抛开数据范围，那么这就只是一道树状数组或线段树的模板题。但当你看到：

$$
-10^9\leq X_1 < X_2 < \ldots < X_N \leq 10^9
$$

如果你打出树状数组，那么就会喜提 MLE。注意到 $X$ 的排列具有严格单调递增的性质，因此可以考虑二分查找实际的左右区间并求和。这一做法的时间复杂度是 $O(N+Q\times(\log N+N))$，~和暴力做法没有实质性的时间复杂度差别~。

考虑用前缀和优化，将求和的复杂度降至 $O(1)$。注意一下二分答案的写法：

```cpp
L=0,R=n-1;
while(L<R){
	int mid=L+(R-L)/2;
	if(node[mid].x>=l)R=mid;
	else L=mid+1;
}
if(node[L].x<l)L++;
```

右区间的查询与之类似。

这个算法非常优秀，时间复杂度 $O(N+Q\times \log N)$，空间复杂度 $O(N)$，轻松通过此题。

[参考代码](https://atcoder.jp/contests/abc371/submissions/57765268)

---

