# Bug in Code

## 题目描述

XX公司的代码出问题了！！老板十分生气，为了有个说法，他决定选出两个背黑锅的人。

现在有n个人，每个人都会选出两个背黑锅的人，老板想要让决定背黑锅的两个人的支持数（就是有几个人想让这个人背黑锅）之和大于等于P。请问有多少种选择方案（顺序无关）

## 样例 #1

### 输入

```
4 2
2 3
1 4
1 4
2 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
8 6
5 6
5 7
5 8
6 2
2 1
7 3
1 3
1 4
```

### 输出

```
1
```

# 题解

## 作者：Merge_all (赞：0)

# Solution
定义 $cnt_i$ 表示有多少个人想要 $i$ 背锅，$gp_{i, j}$ 表示有多少相同的人想要让 $i$ 和 $j$ 一起背锅。

考虑当前答案的构成：
$$ans = \sum_{i = 1} ^ n \sum_{j = 1} ^ n cnt_i + cnt_j - gp_{i, j} \ge p, (i \neq j)$$ 

先不考虑有重复的部分：

$$\sum_{i = 1} ^ n \sum_{j = 1} ^ n cnt_i + cnt_j \ge p, (i \neq j)$$

很明显可以先让 $cnt$ 按从小到大进行排序以后二分处理。

问题就是如何处理相同的部分。

很明显，答案一定是上面这个不重复式子的子集，那么不好直接求出子集，就可以考虑将子集的补集减去：

$$ans = (\sum_{i = 1} ^ n \sum_{j = 1} ^ n cnt_i + cnt_j \ge p) - (\sum_{i = 1} ^ n \sum_{j = 1} ^ n cnt_i + cnt_j - gp_{i, j} < p), (i \neq j)$$

如何快速求出这个子集的补集？这个时候就可以直接到 $gp$ 中找出 $i, j$，然后进行判断即可。

代码很短，写了不到 20 行。

---

## 作者：LZYAC (赞：0)

## 思路

先暴力。考虑枚举 $i$ 和 $j$ 来算，很明显 $(i,j)$ 对于整体的贡献是 $a_i+a_j-b_{i,j}$ 而其中的 $a_i$ 表示想让第 $i$ 个人背锅的人的个数，而 $b_{i,j}$ 则是想让 $i$ 和 $j$ 一起背锅的人的个数。

开不出二维数组，所以用 map 就可以了。最多有 $n$ 个人所以空间复杂度是 $O(n)$ 的。

但是这样是 $O(n^2)$ 会超时。考虑优化。我们要算的抽象出来是 $a_i+a_j-b_{i,j} \ge p$ 的个数，所以正难则反可以用 $a_i+a_j \ge p$ 的个数减去 $a_i+a_j \ge p$ 且 $a_i+a_j-b_{i,j} < p$ 的个数就是答案了。

$n^2$ 会爆 int 所以开 long long 就好了。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<pair<int,int> ,int > mp;
int n,p,ans,r,t1,t2,a[300010],b[300010];
signed main(){
	scanf("%lld%lld",&n,&p);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&t1,&t2);
		a[t1]++;a[t2]++;
		b[t1]++;b[t2]++;
		if(t1>t2) swap(t1,t2);
		mp[{t1,t2}]++;
	}
	sort(b+1,b+1+n);
	r=n;
	for(int i=1;i<=n;i++){
		while(1){
			if(r<=i||b[r]+b[i]<p) break;
			r--;
		}
		ans=ans+n-max(r,i); 
	}
	for(auto it:mp){
		if(a[it.first.first]+a[it.first.second]>=p&&a[it.first.first]+a[it.first.second]-it.second<p){
			ans--;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Acc_Robin (赞：0)

## CF421D Bug in Code 题解

[更高更妙的阅读体验](https://accrobin.github.io/2021/09/12/solver/CF421D%20Bug%20in%20Code/)

传送门：[洛谷](https://www.luogu.com.cn/problem/CF421D) [CodeForces](https://codeforces.com/problemset/problem/421/D)

### 题意

有 $n$ 个人，每个人都会选出两个背黑锅的人。现在需要选出两个背黑锅的人，使得想让这两人背黑锅的人数和大于等于 $m$，问方案数。

注意，若 $A$ 想让 $B,C$ 背黑锅，那么想让 $B,C$ 两人背黑锅的人数和是 $1$ 而不是 $2$。

### 题解

考虑建图。

如果直接按题意连接有向边，发现有去重的问题。

如何才能让同一个人的投票可以更轻松地去重？

若 $i$ 想让 $x,y$ 背黑锅，那么连无向边边 $x-y$。

令 $d(x)$ 表示 $x$ 的度数，$f(x,y)$ 表示 $x,y$ 之间的重边个数。

那么问题就转化成了有多少对 $(u,v)$ 使得 $d(u)+d(v)-f(u,v)\ge m$。

先去掉所有重边，令 $u,v$ 的边权为 $f(u,v)$，若 $u,v$ 间没有边，则边权为 $0$。

将所有点按照 $d$ 升序排序，按顺序枚举点，假设当前枚举到点 $i$，那么需要首先二分出使 $d(j)$ 最小的满足 $d(j)+d(i)\ge m$ 的 $j$，然后取其中与 $i$ 有连边的，进一步判断是否满足 $d(i)+d(j)-f(i,j)\ge m$。

### 复杂度分析

预处理边权、按 $d$ 排序以及枚举时二分的复杂度都是 $O(n\log n)$，之后枚举所有连边的复杂度为 $O(m)=O(2n)=O(n)$，所以总复杂度就是 $O(n\log n)$​​。

### 代码

```代码
#include<bits/stdc++.h>
using namespace std;
#define EB emplace_back
namespace Acc{
	using ll=long long;
	const int N=3e5+9;
	vector<pair<int,int>>G[N],e;
	int d[N],ord[N];
	ll r;
	void work(){
		int n,m,i,x,y,z;
		for(cin>>n>>m,i=1;i<=n;++i)cin>>x>>y,e.EB(x,y),e.EB(y,x),++d[x],++d[y],ord[i]=i;
		auto cmp=[](int x,int y){return d[x]>d[y];};
		sort(begin(e),end(e)),sort(ord+1,ord+n+1,cmp),e.EB(x=y=0,0);
		for(auto[u,v]:e)if(u==x && v==y)++z;else{
			if(x)G[x].EB(y,z);
			x=u,y=v,z=1;
		}
		for(x=1;x<=n;r+=z,++x){
			*d=m-d[x],z=upper_bound(ord+1,ord+n+1,0,cmp)-ord-1-(m<=d[x]<<1);
			for(auto[y,w]:G[x])z-=(d[x]+d[y]>=m && d[x]+d[y]-w<m);
		}
		cout<<r/2<<'\n';
	}
}
int main(){return Acc::work(),0;}

```



---

## 作者：开始新的记忆 (赞：0)

这道题是我在VJ上比赛时做到的，原题链接：http://codeforces.com/problemset/problem/421/D

这道题我看第一眼就想到把每个人都有多少人选进行记录。（这很容易想）然后WA了……

我百思不得其解，于是乎在疯狂造数据的时候，终于发现本题一大坑点：去重 。因为如果有两个人都选的是同样的两个人，那么当枚举到这两个人时，会多算（可以举个例子看看）。

e.g: 

5 3

1 2

1 2

3 4

3 5

4 5

用一开始的思想来看，计数的数组应该是这样的：2 2 2 2 2，无论怎么选，都可以满足老板的要求，可是如果选1和2的话，同意的人只有两个，不满足大于等于3的条件。

去重过程  x和y分别表示每个人的预测，（x<y），同样的一组预测x和y出现了c次，假如cnt[x]+cnt[y]>=y&&cnt[x]+cnt[y]-c<p，则ans--。

代码如下:

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define FFF 300005
int cnt[FFF],to[FFF];
struct node {
    int x,y;
}f[FFF];
bool cmp(node a,node b){
    if(a.x==b.x)
        return a.y<b.y;
    else
        return a.x<b.x;
}
int main()
{
    int n,p;
    scanf("%d%d",&n,&p);
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&f[i].x,&f[i].y);
        if(f[i].x>f[i].y)
        {
            int t=f[i].x;
            f[i].x=f[i].y;
            f[i].y=t;
        }
        cnt[f[i].x]++;
        cnt[f[i].y]++;
    }
    for(int i=1;i<=n;i++)to[i]=cnt[i];
    long long ans=0,now=n;
    sort(cnt+1,cnt+n+1);
    for(int i=1;i<=n;i++) {
        if(cnt[i]>=p)
            ans+=n-1;
        else{
            while(cnt[now]>=p-cnt[i])
                now--;
            if(cnt[now+1]+cnt[i]>=p){
                if(cnt[now+1]>cnt[i])
                    ans+=n-now;
                else
                    ans+=n-now-1;
            }
        }
    }
    ans/=2;
    sort(f,f+n,cmp);
    node tmp;
    tmp.x=tmp.y=0;
    memset(cnt,0,sizeof(cnt));
    int c=0;
    for(int i=0;i<n;i++)
    {
        if(tmp.x==f[i].x&&tmp.y==f[i].y)
            c++;
        else
        {
            if(tmp.x&&to[tmp.x]+to[tmp.y]>=p&&to[tmp.x]&&to[tmp.x]+to[tmp.y]-c<p)
                ans--;
            tmp.x=f[i].x;
            tmp.y=f[i].y;
            c=1;
        }
    }
    if(to[tmp.x]+to[tmp.y]>=p&&to[tmp.x]&&to[tmp.x]+to[tmp.y]-c<p)
        ans--;
    cout<<ans<<endl;
    return 0;
}
```


---

