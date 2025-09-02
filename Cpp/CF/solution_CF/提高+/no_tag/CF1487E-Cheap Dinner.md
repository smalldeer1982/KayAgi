# Cheap Dinner

## 题目描述

有 $4$ 种菜类——开胃菜，主菜，饮品和甜点。一顿晚饭由 $4$ 种菜类各一道组成。

对于第 $i$ 种菜类，共有 $n_i$ 种供选择。开胃菜、主菜、饮品和甜点价格分别为 $a_i$、$b_i$、$c_i$、$d_i$。

有些菜品不能搭配。对于开胃菜和主菜来说，有 $m_1$ 对不能搭配。对于主菜和饮品、饮品和甜点分别有 $m_2$，$m_3$ 对。

试问总价格最小的晚饭需要多少钱？

## 样例 #1

### 输入

```
4 3 2 1
1 2 3 4
5 6 7
8 9
10
2
1 2
1 1
2
3 1
3 2
1
1 1```

### 输出

```
26```

## 样例 #2

### 输入

```
1 1 1 1
1
1
1
1
1
1 1
0
0```

### 输出

```
-1```

# 题解

## 作者：绝顶我为峰 (赞：7)

无脑暴力题。

考虑合并两组菜品 $a,b$，一个显然的做法是对于每一个 $b_i$，找到能和它搭配的 $a$ 中权值最小的（记为 $a_j$） 来合并，并将 $b_i$ 权值更新为 $a_j+b_i$。

正确性显然。

然后这个东西可以用 vector+map 搞了，具体来说每一次合并之前 vector 先排序，然后每一个菜品挨个从前往后查找第一个可以匹配的即可。map 用来存限制。

时限 4s，显然可以过。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
vector<pair<int,int> > v[5];
int n[5];
map<pair<int,int>,int> mp[5];
int main()
{
    scanf("%d%d%d%d",&n[1],&n[2],&n[3],&n[4]);
    for(register int i=1;i<=4;++i)
        for(register int j=1;j<=n[i];++j)
        {
            int x;
            scanf("%d",&x);
            v[i].push_back(make_pair(x,j));
        }
    for(register int i=2;i<=4;++i)
    {
        int m;
        scanf("%d",&m);
        for(register int j=1;j<=m;++j)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            mp[i][make_pair(x,y)]=1;
        }
    }
    for(register int i=2;i<=4;++i)
    {
        sort(v[i-1].begin(),v[i-1].end());
        for(register int j=0;j<n[i];++j)
        {
            int k=0;
            while(k<n[i-1]&&mp[i][make_pair(v[i-1][k].second,v[i][j].second)])
                ++k;
            if(k==n[i-1])
                v[i][j].first=1<<30;
            else
                v[i][j].first+=v[i-1][k].first;
        }
    }
    sort(v[4].begin(),v[4].end());
    printf("%d\n",v[4][0].first>1e9? -1:v[4][0].first);
    return 0;
}
```


---

## 作者：一扶苏一 (赞：4)

## 【DP&二分】【CF1478E】 Cheap Dinner

### Analysis

考虑第 $i$ 类食物的选择只和第 $(i - 1)$ 类食物的选择有关，不难得到以下 dp：

设 $f_{i, j}$ 表示选择了第 $i$ 类食物的第 $j$ 个的当前最小花费，转移为 $f_{i, j} = \min\limits_{k = 1}^{n_{i - 1}} \{f_{i - 1, k} + a_{i, j}\}$，其中 $k$ 和 $j$ 可以同时选择。发现 $a_{i, j}$ 与 $k$ 无关，于是转移改为 $f_{i, j} = \min\limits_{k = 1}^{n_{i - 1}} \{f_{i - 1, k}\} + a_{i, j}$。这就是说，$f$ 将从能选择的上一类菜品种 $f$ 值最小的一个转移而来。

对于每类食物求完 $f$ 值后（也就是对于一个 $i$ 的所有 $f_{i, j}$ 都计算完成后），对这类所有食物按照 $f$ 的大小排序（也就是对 $f_{i, 1}, f_{i, 2}, \dots f_{i, n_i}$ 排序）结果是 $b_{i, j}$（也就是 $b_{i, j}$ 表示第 $i$ 类菜中第 $f$ 值第 $j$ 小的菜品的编号），记录每个食物的 $f$ 值是第几大的，记为 $c_{i, j}$（也就是 $c_{i, j}$ 表示编号为 $j$ 的菜品的 $f$ 值排名）。然后处理第 $i$ 和第 $(i + 1)$ 类食物之间的限制信息：对每个菜品开一个 vector，对于一个限制 $<x, y>$，在 $y$ 的 vector 中加入 $c_{i, x}$。

这样一道菜品的限制排名就都压入 vector 里了。对于一个 $f_{i + 1, j}$，它应该从上一类食物里排名尽可能小的 $f$ 转移，设 vector 里最小的没有被出现的数为 $t$，则它应该从 $f_{i, b_{i, t}}$ 转移。找最小的没有被出现的数可以通过对每个 vector 进行排序然后二分做到。

时间复杂度为 $O(n \log n)$，这里认为 $n_i$ 与 $m_i$ 同阶均为 $n$。

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

const int maxc = 5;
const int maxn = 200000;
long long INF = 0x3f3f3f3f3f3f3f3fll >> 2;

int n[maxc], m[maxc];
int a[maxc][maxn], b[maxc][maxn], c[maxc][maxn];
long long f[maxc][maxn], tmp[maxn];
std::vector<int> lim[maxc][maxn];

int main() {
  for (int i = 1; i < maxc; ++i) scanf("%d", n + i);
  for (int i = 1; i < maxc; ++i) for (int j = 1; j <= n[i]; ++j) lim[i][j].push_back(0);
  for (int i = 1; i <= n[1]; ++i) {
    scanf("%d", a[1] + i);
    b[1][i] = i;
    f[1][i] = a[1][i];
  }
  std::sort(b[1] + 1, b[1] + n[1] + 1, 
      [](const int &x, const int &y) { return f[1][x] < f[1][y]; });
  for (int j = 1; j <= n[1]; ++j) c[1][b[1][j]] = j;
  for (int i = 2; i < maxc; ++i) {
    for (int j = 1; j <= n[i]; ++j) {
      scanf("%d", a[i] + j);
      b[i][j] = j;
    }
  }
  
  for (int i = 2; i < maxc; ++i) {
    scanf("%d", m + i);
    for (int j = 1, x, y; j <= m[i]; ++j) {
      scanf("%d %d", &x, &y);
      lim[i][y].push_back(c[i - 1][x]);
    }
    for (int j = 1; j <= n[i]; ++j) {
      std::sort(lim[i][j].begin(), lim[i][j].end());
      int pos = 0;
      for (int l = 1, r = lim[i][j].size() - 1, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) if (lim[i][j][mid] == mid) {
        pos = mid; l = mid + 1;
      } else {
        r = mid - 1;
      }
      if (++pos > n[i - 1]) f[i][j] = INF;
      else f[i][j] = f[i - 1][b[i - 1][pos]] + a[i][j];
    }
    memcpy(tmp, f[i], sizeof tmp);
    std::sort(b[i] + 1, b[i] + n[i] + 1, 
        [](const int &x, const int &y) { return tmp[x] < tmp[y]; });
    for (int j = 1; j <= n[i]; ++j) c[i][b[i][j]] = j;
  }
  long long ans = f[4][b[4][1]];
  printf("%lld\n", ans > INT_MAX ? -1 : ans);
  return 0;
}
```





---

## 作者：bmatrix (赞：2)

将 $a,b,c,d$ 分别用 $a_1,a_2,a_3,a_4$ 表示。

令与第 $i$ 类食物中的第 $j$ 个冲突的第 $i-1$ 类食物的集合为 $S_{i,j}$。

首先是是人都能看出来的 DP：

令 $f_{i,j}$ 为选择第 $i$ 类食物的第 $j$ 个时所需的最小费用，显然有
$$f_{i,j}=\min_{k=1}^{k\le n_{i-1},k\notin S_{i,j}}f_{i-1,k}+a_{i,j}$$

现在问题在于这个最小值怎么求。

容易发现，$S_{i,j}$ 中的元素将序列 $a_{i-1}$ 划分成了若干区间：

![](https://cdn.luogu.com.cn/upload/image_hosting/lq4glx0i.png)

只要求出这些区间的最小值的最小值（不是语病 QAQ）就好了。

静态区间最小值？那自然是 [ST 表](https://www.luogu.com.cn/problem/P3865)！

使用 `vector` 存储上述的 $S_{i,j}$，内部排序后，挨个遍历提取区间即可。

$\min_{i=1}^{n_4}f_{4,i}$ 即为答案，如果它等于 `INF` 则证明无解。 

时间复杂度显然 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define INF 0x3fffffff
using namespace std;
typedef long long ll;
constexpr int N=1.5e5+5;
int n[5],a[5][N],lg[N],minn[N][20];
//这里直接用a代替f了
void make(int *a,int n){//以a为原数组，建立ST表的函数
    for(int i=1;i<=n;i++)minn[i][0]=a[i];
    for(int i=1;i<=lg[n];i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            minn[j][i]=min(minn[j][i-1],minn[j+(1<<(i-1))][i-1]);
}
inline int query(int l,int r){
    if(r<l)return INF;
    int len=lg[r-l+1];
    return min(minn[l][len],minn[r-(1<<len)+1][len]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    lg[0]=-1;
    for(int i=1;i<=4;i++)cin>>n[i];
    for(int i=1;i<=4;i++)
        for(int j=1;j<=n[i];j++)
            cin>>a[i][j],lg[j]=lg[j/2]+1;
    for(int i=1;i<=3;i++){
        vector<int>unfit[N];
        for(int j=1;j<=n[i+1];j++)unfit[j].push_back(0);//第0个和第n+1个肯定不能选
        int m;cin>>m;
        for(int j=1;j<=m;j++){
            int x,y;cin>>x>>y;
            unfit[y].push_back(x);
        }
        for(int j=1;j<=n[i+1];j++){
            unfit[j].push_back(n[i]+1);
            sort(unfit[j].begin()+1,unfit[j].end()-1);
            //第一个和最后一个一定在正确位置，这样可以稍微减小一点常数（并没什么用
        }
        make(a[i],n[i]);//建立ST表
        for(int j=1;j<=n[i+1];j++){
            int minn=INF;
            for(auto k=unfit[j].begin()+1;k!=unfit[j].end();k++)
                minn=min(minn,query(*(k-1)+1,*k-1));//取区间最小值
            a[i+1][j]=minn==INF?INF:a[i+1][j]+minn;//注意这里不能直接加，INF加任何数都得INF
        }
    }
    int minn=INF;
    for(int i=1;i<=n[4];i++)minn=min(minn,a[4][i]);
    cout<<(minn==INF?-1:minn)<<endl;
    return 0;
}
```
~~时限开了 4s，但是 C++ ![](https://cdn.luogu.com.cn/upload/image_hosting/kd7izyuo.png) 就跑过了~~

---

## 作者：peterwuyihong (赞：2)

不会做贪心题，于是来一个贪心题。

题意：给你四个序列 $a,b,c,d$，$a,b$ 间给定 $m_1$ 个限制，$a$ 中的 $x$ 不能和 $b$ 中的 $y$ 一起选，同样的，$b,c$，$c,d$ 间也给定 $m_2,m_3$ 限制，问从 $a,b,c,d$ 中各选一个数加起来最小是多少，如果怎么选都会违反限制，输出 $-1$。

先考虑 $a,b$ 间的怎么做。

![](https://cdn.luogu.com.cn/upload/image_hosting/fitwuq75.png)

考虑用下面的序列一个一个地更新答案。先看到了 $1$，它在 $a$ 中的限制是位置 $1,2,5$，于是我们依次找到 $[3,4],[6,6]$ 中的最小值就行了，然后看到了 $9$，$9$ 没有限制，就找到 $[1,6]$ 间的最小值，然后更新一波，把 $b$ 变成 $b'$，表示这个位置的 $b$ 加上匹配到的 $a$ 的最小值，如图，$b'=[5,10,5,10,9,5]$。

然后再做两边就行了！最后找到 $d'$ 中的最小值。

考虑要搞无解的情况，你可以整一个无匹配就把更新后的数组这个位置赋值为 $+\infty$。然后最后找到的最小值如果是 $+\infty$，哦吼，gg。

区间最小值使用 $\text{ST}$ 表维护即可，总的复杂度大概是 $n\log n+m$，记 $n=\sum n_i,m=\sum m_i$

```cpp
#define int long long
#define maxn 150010
int n1,n2,n3,n4,m;
int a[maxn];
int b[maxn];
int c[maxn];
int d[maxn];
int lg[maxn];
int f[maxn][20];
int rmq(int l,int r){
	int k=lg[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
vector<int>v[maxn];
int x,y;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n1>>n2>>n3>>n4;
	rep(i,1,n1)cin>>a[i];
	rep(i,1,n2)cin>>b[i];
	rep(i,1,n3)cin>>c[i];
	rep(i,1,n4)cin>>d[i];
	cin>>m;
	lg[0]=-1;
	rep(i,1,150000)lg[i]=lg[i>>1]+1;
	rep(i,1,n1)f[i][0]=a[i];
	rep(j,1,lg[n1])rep(i,1,n1-(1<<j)+1)
	f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	while(m--){
		cin>>x>>y;
		v[y].push_back(x);
	}
	rep(i,1,n2){
		v[i].push_back(0);
		v[i].push_back(n1+1);
		sort(all(v[i]));
		int mn=1145141919810;
		for(unsigned j=1;j<v[i].size();j++)
		if(v[i][j]!=v[i][j-1]+1)
			mn=min(mn,rmq(v[i][j-1]+1,v[i][j]-1));
		b[i]+=mn;
		v[i].clear();
	}
	rep(i,1,n2)f[i][0]=b[i];
	rep(j,1,lg[n2])rep(i,1,n2-(1<<j)+1)
	f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	cin>>m;
	while(m--){
		cin>>x>>y;
		v[y].push_back(x);
	}
	rep(i,1,n3){
		v[i].push_back(0);
		v[i].push_back(n2+1);
		sort(all(v[i]));
		int mn=1145141919810;
		for(unsigned j=1;j<v[i].size();j++)
		if(v[i][j]!=v[i][j-1]+1)
			mn=min(mn,rmq(v[i][j-1]+1,v[i][j]-1));
		c[i]+=mn;
		v[i].clear();
	}
	rep(i,1,n3)f[i][0]=c[i];
	rep(j,1,lg[n3])rep(i,1,n3-(1<<j)+1)
	f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	cin>>m;
	while(m--){
		cin>>x>>y;
		v[y].push_back(x);
	}
	rep(i,1,n4){
		v[i].push_back(0);
		v[i].push_back(n3+1);
		sort(all(v[i]));
		int mn=1145141919810;
		for(unsigned j=1;j<v[i].size();j++)
		if(v[i][j]!=v[i][j-1]+1)
			mn=min(mn,rmq(v[i][j-1]+1,v[i][j]-1));
		d[i]+=mn;
		v[i].clear();
	}
	int mn=1145141919810;
	rep(i,1,n4)mn=min(mn,d[i]);
	if(mn==1145141919810)mn=-1;
	cout<<mn;
现在是 8:38，我看我什么时候写完。
现在是 8:56，我写完了。
}
```
日了，每天一个爆〇小技巧，$\text{Ctrl-C+V}$ 但是没有改完，我粘贴 $\text{ST}$ 表没有改长度 $\text{WA}$ 了两发。

---

## 作者：shicj (赞：1)

提供一种简单的线段树写法。

首先，给出朴素的 DP，令 $dp_{i,j}$ 表示前 $i$ 种食物，第 $i$ 种选择了 $j$ 的最小花费，显然得出转移：

$$
dp_{i,j}=\min\limits_{\text{(j,k)\ is\ OK}}dp_{i-1,k}+c_{i,j}
$$

边界：

$$
dp_{1,i}=c_{1,i}
$$

接下来将取最小值的枚举优化，一种简单的想法是，以 $dp_{i-1}$ 建立线段树，每次枚举 $k$ 时，将所有不符合条件的数字设置为正无穷，处理完这个 $j$ 之后再将修改复原，这样的均摊时间复杂度为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template <typename T> struct SegmentTree{struct node{int l,r;T v,tag;}t[2000006*4];T dat[2000006];void pushup(int x){t[x].v=op(t[x*2].v,t[x*2+1].v);}void build(int x,int l,int r){t[x].l=l;t[x].r=r;if(l==r){t[x].v=dat[l];return;}int mid=(l+r)/2;build(x*2,l,mid);build(x*2+1,mid+1,r);pushup(x);}void pushdown(int x){if(t[x].tag&&t[x].l!=t[x].r){apply(x*2,t[x].tag);apply(x*2+1,t[x].tag);t[x].tag=0;}}void update(int x,int L,int R,T v){int l=t[x].l,r=t[x].r;if(L<=l&&r<=R){apply(x,v);return;}pushdown(x);int mid=(l+r)/2;if(L<=mid)update(x*2,L,R,v);if(mid+1<=R)update(x*2+1,L,R,v);pushup(x);}T query(int x,int L,int R){int l=t[x].l,r=t[x].r;if(L<=l&&r<=R){return t[x].v;}pushdown(x);int mid=(l+r)/2;T tot=tot_init;if(L<=mid)tot=q_op(tot,query(x*2,L,R));if(mid+1<=R)tot=q_op(tot,query(x*2+1,L,R));return tot;}
    ////////////////// 自定义函数区 ///////////////////
        T op(T x,T y){return min(x,y);}
        T q_op(T x,T y){return min(x,y);}
        T tot_init=0x3f3f3f3f;
        void apply(int x,T v){
            t[x].v=v;
            t[x].tag=v;
        }
    ////////////////// 自定义函数区 ///////////////////
};//区间最小值板子
SegmentTree<int>SegTree;
int n[5];
int a[5][200005];
int dp[5][200005];
int m[5];
int bx[5][200005];
int by[5][200005];
vector<int>nok[5][200005];
//nok记录不可用的点对
void solve(){
	for(int i=1;i<=4;i++){
		scanf("%lld",&n[i]);
	}
	for(int i=1;i<=4;i++){
		for(int j=1;j<=n[i];j++){
			scanf("%lld",&a[i][j]);
		}
	}
	for(int i=2;i<=4;i++){
		scanf("%lld",&m[i]);
		for(int j=1;j<=m[i];j++){
			scanf("%lld%lld",&bx[i][j],&by[i][j]);
			nok[i][by[i][j]].push_back(bx[i][j]);
		}
	}
	for(int i=1;i<=n[1];i++){
		dp[1][i]=a[1][i];
	}
	for(int i=2;i<=4;i++){
		for(int j=1;j<=n[i]*4;j++){
			SegTree.t[j].v=SegTree.t[j].tag=0;
			SegTree.t[j].l=SegTree.t[j].r=0;
		}
		for(int j=1;j<=n[i-1];j++){
			SegTree.dat[j]=dp[i-1][j];
		}
		SegTree.build(1,1,n[i-1]);
		for(int j=1;j<=n[i];j++){
			for(auto k:nok[i][j]){
				SegTree.update(1,k,k,0x3f3f3f3f);
			}
			dp[i][j]=SegTree.query(1,1,n[i-1])+a[i][j];
			for(auto k:nok[i][j]){
				SegTree.update(1,k,k,dp[i-1][k]);
			}
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n[4];i++){
		ans=min(ans,dp[4][i]);
	}
	if(ans==0x3f3f3f3f){
		printf("-1\n");
	}
	else{
		printf("%lld\n",ans);
	}
}
signed main(){
#ifdef USE_FILE_IO
	freopen("code.in","r",stdin);
	cerr<<"[File IO]"<<endl;
#endif
	int t=1;
//	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：wizardMarshall (赞：1)

## 题意

需要选择四组下标，使得 $a_{i_1}+b_{i_2}+c_{i_3}+d_{i_4}$ 的值最小。同时有几组限制，形如 $(i,j)$，意为不能同时选 $a_i$ 和 $b_j$。（或 $b_i$ 和 $c_j$，$c_i$ 和 $d_j$）

## 思路

这玩意儿一看就很像分层。如果直接建图跑最短路肯定是不行的，因为每层有 $1.5\times 10^5$ 个点，建出来大概有 $10^{10}$ 条了。而限制数（即不建的边）数量一共才 $2 \times 10^5$ 个……

既然限制较少，我们考虑反其道而行之。

如果没有限制，明显就是 $\min(a)+\min(b)+\min(c)+\min(d)$。

存在限制，考虑动态规划。$dp_{i,j}$ 表示到了第 $i$ 层第 $j$ 个点，最短路径。

可能有人会说诶你这转移不还是 $O(n^2)$ 级别的吗？

但我们可以不用上一层每个点转移到下一层每个点，只需要挑最小值就好了。而如果单单存最小值又存在限制，所以可以记录上一层的状态。

如用优先队列，当前层为第 $i$ 个点，将上一层值从小到大的状态挨个判断，只要找到没有限制的一对 $(i,j)$ 就转移，这样就保证了最优。（注意那些弹出的值最后要丢回去，因为不止 $i$ 一个点要转移）

至于时间复杂度，由于总的限制数量较少，特判弹出的也较少，所以处于可控范围。

## 代码

这里使用了两个优先队列分别记录奇数层和偶数层的（类似滚动）。

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n[5];
int a[5][150005];
int dp[5][150005];
map <pair <int, int>, bool> mp;
signed main() {
	for (int i = 1; i <= 4; i++) {
		scanf("%lld", &n[i]);
	}
	priority_queue <pair <int, int> > q1, q2;//两个优先队列
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= n[i]; j++) {
			scanf("%lld", &a[i][j]);
			if (i == 1) {//第一层，初始化dp
				dp[i][j] = a[i][j];
				q1.push({-a[i][j], j});//偷懒：优先队列按从大到小排，所以取负数
			}else {
				dp[i][j] = 1e9;
			}
		}
	}
	
	for (int i = 1; i < 4; i++) {//在读入限制时逐层判断
		int m;
		scanf("%lld", &m);
		mp.clear();
		for (int j = 1; j <= m; j++) {
			int a, b;
			scanf("%lld%lld", &a, &b);
			mp[{a, b}] = 1;//限制用mp[{i,j}]表示i层和i+1层第几个点间不能匹配
		}if (i & 1) {//清空i+1层队列（i+1要从i转移，转移好了再丢进去）
			while (!q2.empty())q2.pop();
		}
		else {
			while (!q1.empty())q1.pop();
		}
		for (int j = 1; j <= n[i + 1]; j++) {
			if (i & 1) {//奇偶分别判断，两部分相似
				vector <pair <int, int> > temp;//那些因限制弹出去的要重新进去，使其他j能够转移
				while (!q1.empty()) {
					pair <int, int> f = q1.top();
					if (!mp[{f.second, j}]) {//没有限制
						dp[i + 1][j] = min(dp[i + 1][j], -f.first + a[i + 1][j]);
						break;
					}q1.pop();temp.push_back(f);//弹出，储存
				}
				for (auto i : temp)q1.push(i);
				q2.push({-dp[i + 1][j], j});
			}else {
				vector <pair <int, int> > temp;
				while (!q2.empty()) {
					pair <int, int> f = q2.top();
					if (!mp[{f.second, j}]) {
						dp[i + 1][j] = min(dp[i + 1][j], -f.first + a[i + 1][j]);
						break;
					}q2.pop();temp.push_back(f);
				}
				for (auto i : temp)q2.push(i);
				q1.push({-dp[i + 1][j], j});//i+1层的优先队列储存dp值，用来i+2层的转移
			}
		}
	}
	int ans = 1e9;
	for (int i = 1; i <= n[4]; i++) {//最后找最小值
		ans = min(ans, dp[4][i]);
	}
	if (ans == 1e9) {//某一层限制满了导致没有可选
	    cout << -1;
	}
	else {
		cout << ans;
	}
	return 0;
}
```

---

## 作者：Leap_Frog (赞：1)

### P.S.
全场最无脑暴力做法。  

### Description.
有四种类型的物品，分别是 $A,B,C,D$，每个物品有价值。  
现在 $A$ 中有些物品和 $B$ 中不能同时选择。  
$B$ 中有些物品不能和 $C$ 中同时选择，$C$ 和 $D$ 也有。  
现在询问从 $A,B,C,D$ 中分别选一个物品，最小价值和是多少。  

### Soltuion.
首先，显然可以把 $A,B,C,D$ 分别当做 dp 的四个阶段。  
然后每次 $A$ 向 $B$ 转移，$B\rightarrow C,C\rightarrow D$。  
然后转移的条件就是不能设成边。  
我们暴枚目标节点，然后每次把被禁止不能转移的那些点设成 $+\infty$。  
然后开棵线段树维护全局最大值，支持单点修改。  
~~鬼知道为什么要写这么复杂，但是就是这样写了~~  
然后这题就做完了qaq

### Coding.
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
    x=0;char c=getchar(),f=0;
    for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
    for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    f?x=-x:x;
}
int T[600005],na,nb,nc,nd,m,a[150005],b[150005],c[150005],d[150005];
vector<int>eb[150005],ec[150005],ed[150005];int st[150005],tp;
inline void build(int x,int l,int r,int *a)
{
    if(l==r) return T[x]=a[l],void();
    build(x<<1,l,(l+r)>>1,a),build(x<<1|1,((l+r)>>1)+1,r,a),T[x]=min(T[x<<1],T[x<<1|1]);
}
inline void modif(int x,int l,int r,int dw,int dc)
{
    if(l==r) return T[x]=dc,void();
    if(dw<=((l+r)>>1)) modif(x<<1,l,(l+r)>>1,dw,dc),T[x]=min(T[x<<1],T[x<<1|1]);
    else modif(x<<1|1,((l+r)>>1)+1,r,dw,dc),T[x]=min(T[x<<1],T[x<<1|1]);
}
signed main()
{
    read(na),read(nb),read(nc),read(nd);
    for(int i=1;i<=na;i++) read(a[i]);
    for(int i=1;i<=nb;i++) read(b[i]);
    for(int i=1;i<=nc;i++) read(c[i]);
    for(int i=1;i<=nd;i++) read(d[i]);
    read(m);for(int x,y;m--;) read(x),read(y),eb[y].push_back(x);
    read(m);for(int x,y;m--;) read(x),read(y),ec[y].push_back(x);
    read(m);for(int x,y;m--;) read(x),read(y),ed[y].push_back(x);
    build(1,1,na,a);for(int i=1;i<=nb;i++)
    {
        tp=0;for(auto x:eb[i]) st[++tp]=a[x],modif(1,1,na,x,1e9+5);
        tp=0,b[i]+=T[1];for(auto x:eb[i]) modif(1,1,na,x,st[++tp]);
    }
    build(1,1,nb,b);for(int i=1;i<=nc;i++)
    {
        tp=0;for(auto x:ec[i]) st[++tp]=b[x],modif(1,1,nb,x,1e9+5);
        tp=0,c[i]+=T[1];for(auto x:ec[i]) modif(1,1,nb,x,st[++tp]);
    }
    build(1,1,nc,c);for(int i=1;i<=nd;i++)
    {
        tp=0;for(auto x:ed[i]) st[++tp]=c[x],modif(1,1,nc,x,1e9+5);
        tp=0,d[i]+=T[1];for(auto x:ed[i]) modif(1,1,nc,x,st[++tp]);
    }
    int mn=1e9+5;for(int i=1;i<=nd;i++) mn=min(mn,d[i]);
    return printf("%lld\n",mn>=1e9+5?-1:mn),0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 前言
为什么要写 dp，不是贪心就行了吗？
# 思路
我们发现题目中只有三种限制，所以我们考虑每次枚举两种之间能取得最小值然后在将两种拼起来。我们将题目中的 $4$ 种菜品设为 $A,B,C,D$ 我们发现 $(A,B),(B,C),(C,D)$ 之间有限制而 $(A,D)$ 之间没有，所以我们考虑算出每一个 $A$ 与 $B$ 组合的最小值以及每一个 $C$ 与 $D$ 能组合出的最小值，然后我们在考虑将每一个 $A,B$ 组合中的 $B$ 去与每一个 $C,D$ 组合中的 $C$ 匹配并取最小值即可（因为 $A,D$ 之间没有限制所以只要 $B,C$ 合法那么一定合法）。

现在我们只需要对每一个 $B$ 求出它能取的最小的 $A$，这个问题也很好维护只需要将与它有限制的从 $A$ 中删去即可，后面的 $C,D$ 与 $B,C$ 之间的匹配也是如此。

注意要特判删去有限制的之后集合为空的情况。
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
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n1,n2,n3,n4;
const int N=2e5+10;
int a[N],b[N],c[N],d[N];
vector<int>B1[N],B[N],C[N];
int minb[N],minc[N];
multiset<int>s;
void solve() {
	in(n1),in(n2),in(n3),in(n4);
	rep(i,1,n1) in(a[i]);
	rep(i,1,n2) in(b[i]);
	rep(i,1,n3) in(c[i]);
	rep(i,1,n4) in(d[i]),s.insert(d[i]);
	int m;
	in(m);
	rep(i,1,m) {
		int aa,bb;
		in(aa),in(bb);
		B[bb].pb(aa);
	}
	in(m);
	rep(i,1,m) {
		int bb,cc;
		in(bb),in(cc);
		B1[bb].pb(cc);
	}
	in(m);
	rep(i,1,m) {
		int cc,dd;
		in(cc),in(dd);
		C[cc].pb(dd);
	}
	rep(i,1,n3) {
		for(auto to:C[i]) s.erase(s.find(d[to]));
		if(s.size()) minc[i]=*s.begin()+c[i];
		else minc[i]=INT_MAX;
		for(auto to:C[i]) s.insert(d[to]);
	}
	s.clear();
	rep(i,1,n1) s.insert(a[i]);
	rep(i,1,n2) {
		for(auto to:B[i]) s.erase(s.find(a[to]));
		if(s.size()) minb[i]=*s.begin()+b[i];
		else minb[i]=INT_MAX;
		for(auto to:B[i]) s.insert(a[to]);
	}
	s.clear();
	int res=INT_MAX;
	rep(i,1,n3) s.insert(minc[i]);
	rep(i,1,n2) {
		for(auto to:B1[i]) s.erase(s.find(minc[to]));
		if(s.size()) res=min(res,minb[i]+*s.begin());
		for(auto to:B1[i]) s.insert(minc[to]);
	}
	if(res!=INT_MAX) printf("%lld\n",res);
	else puts("-1");
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：MvemiY (赞：0)

### 题目描述

给定四个集合 $A,B,C,D$，$A$ 和 $B$、$B$ 和 $C$、$C$ 和 $D$ 之间分别有一些互斥关系。你需要从这四个集合中分别取出一个元素使得四个元素和最小。请输出这个最小和，若无解则输出 $-1$。

### 题目分析

设 $f_{i,k}$ 表示选到集合 $k$ 且选第 $i$ 个元素的最小和。容易写出 $f_{i,k} = \min\{f_{j,k-1}\}+val_i(j \notin X_i)$，其中 $X_i$ 表示与 $i$ 互斥的元素组成的集合。

注意到 $m_1+m_2+m_3 \le 6 \times 10^5$，那么我们可以将任意 $j$ 的 $f_{j,k-1}$ 拍到权值树状数组上，再将这些 $j \in X_i$ 的 $f_{j,k-1}$ 从树状数组上扣下来，进行二分查找或树状数组二分，可以找到第一个 $sum(1,h)=1$ 的位置，$h$ 就是 $\min\{f_{j,k-1}\}$。对 $i$ 转移完毕再将 $j \in X_i$ 的 $f_{j,k-1}$ 放回权值树状数组上即可。

因为本题值域较大，需要在使用权值树状数组之前将其离散化。

时间复杂度 $O(n\log^2_2n)$，如果使用权值树状数组上二分则为 $O(n\log_2n)$。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 150010;
inline ll read(){
	ll x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}

ll n1, n2, n3, n4, m1, m2, m3, a[MAXN], b[MAXN], c[MAXN], d[MAXN], f[MAXN], f2[MAXN], fb[MAXN], ff[MAXN], tr[MAXN];
vector <int> g[MAXN];

int lowbit(int x){
	return x & -x;
}

void update(int pos, int k, int n){
	for(int i = pos; i <= n; i += lowbit(i))
		tr[i] += k;
}
int query(int pos){
	int res = 0;
	for(int i = pos; i >= 1; i -= lowbit(i))
		res += tr[i];
	return res;
}

void work(int n){
	for(int i = 1; i <= n; i++)
		tr[i] = 0;
	for(int i = 1; i <= n; i++)
		fb[i] = f[i];
	sort(fb+1, fb+1+n);
	for(int i = 1; i <= n; i++)
		ff[i] = lower_bound(fb+1, fb+1+n, f[i]) - fb;
	for(int i = 1; i <= n; i++)
		update(ff[i], 1, n);
}

ll query_ans(int n){
	int l = 1, r = n, ans = -1, mid;
	while(l <= r){
		mid = (l+r) >> 1;
		if(query(mid) >= 1)
			ans = mid, r = mid-1;
		else l = mid+1;
	}
	if(ans != -1) return fb[ans];
	return 0x3f3f3f3f3f3f3f3f;
}

int main(){
	n1 = read(), n2 = read(), n3 = read(), n4 = read();
	for(int i = 1; i <= n1; i++)
		a[i] = read();
	for(int i = 1; i <= n2; i++)
		b[i] = read();
	for(int i = 1; i <= n3; i++)
		c[i] = read();
	for(int i = 1; i <= n4; i++)
		d[i] = read();
		
	memset(f2, 0x3f, sizeof(f2));
	m1 = read();
	for(int i = 1; i <= m1; i++){
		int x = read(), y = read();
		g[y].push_back(x);
	}
	for(int i = 1; i <= n1; i++)
		f[i] = a[i];
	work(n1);
	for(int i = 1; i <= n2; i++){
		int len = g[i].size();
		for(int j = 0; j < len; j++)
			update(ff[g[i][j]], -1, n1);
		f2[i] = min(f2[i], query_ans(n1) + b[i]);
		for(int j = 0; j < len; j++)
			update(ff[g[i][j]], 1, n1);
	}
	for(int i = 1; i <= n2; i++){
		f[i] = f2[i];
		g[i].clear();
	}
	
	memset(f2, 0x3f, sizeof(f2));
	m2 = read();
	for(int i = 1; i <= m2; i++){
		int x = read(), y = read();
		g[y].push_back(x);
	}
	work(n2);
	for(int i = 1; i <= n3; i++){
		int len = g[i].size();
		for(int j = 0; j < len; j++)
			update(ff[g[i][j]], -1, n2);
		f2[i] = min(f2[i], query_ans(n2) + c[i]);
		for(int j = 0; j < len; j++)
			update(ff[g[i][j]], 1, n2);
	}
	for(int i = 1; i <= n3; i++){
		g[i].clear();
		f[i] = f2[i];
	}
	
	memset(f2, 0x3f, sizeof(f2));
	m3 = read();
	for(int i = 1; i <= m3; i++){
		int x = read(), y = read();
		g[y].push_back(x);
	}
	work(n3);
	for(int i = 1; i <= n4; i++){
		int len = g[i].size();
		for(int j = 0; j < len; j++)
			update(ff[g[i][j]], -1, n3);
		f2[i] = min(f2[i], query_ans(n3) + d[i]);
		for(int j = 0; j < len; j++)
			update(ff[g[i][j]], 1, n3);
	}
	
	ll ans = 0x3f3f3f3f3f3f3f3f;
	for(int i = 1; i <= n4; i++)
		ans = min(ans, f2[i]);
	if(ans != 0x3f3f3f3f3f3f3f3f)
		cout << ans;
	else cout << -1;
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1487E Cheap Dinner](https://www.luogu.com.cn/problem/CF1487E)

### 思路

考虑没有组合的限制，那么答案就是每组最便宜的菜价格之和。

现在有了组合的限制，我们可以从上往下每两组菜组合考虑，因为只有上下两组有限制，所以这样考虑没有问题。

比如第一组和第二组，对于第二组的一个菜 $i$，它选择的一定是除了不能选择的最小价格。此时对于第二组菜，我们有了前两组菜的综合结果。

而第三组与第一组是无关的，我们只要考虑它与第二组的限制。对于第三组的一个菜 $i$，它选择的一定是第二组中除了不能选择的最小综合价格。此时对于第三组菜，我们有了前三组菜的综合结果。

第四组也同理，这样就做完了。

最麻烦的地方在于选择最小综合价格。对于下面的一道菜，我们可以把它不能选的菜品按综合价格从小到大排列，再从小到大观察。假设检测到第 $i$ 个位置，如果这个菜品在所有菜品中顺序为 $j(j>i)$，说明有更便宜的且可以选择，而且这个菜在所有菜品中顺序为 $i$，也就找到了答案。

值得特判的地方在于如果限制的个数等于菜品总数，那么可以给这道菜的综合结果赋一个极大值。

时间复杂度 $O(\sum n+\sum m\log\sum m)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=150005,inf=1e9;
int n1,n2,n3,n4,a1[N],b1[N],c1[N],d1[N],m1,u,v,a[N],b[N],c[N],d[N];
std::pair<long long,int>f[5][N];
std::vector<int>edge[5][N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n1>>n2>>n3>>n4;
    for(int i=1;i<=n1;++i){cin>>a[i];}
    for(int i=1;i<=n2;++i){cin>>b[i];}
    for(int i=1;i<=n3;++i){cin>>c[i];}
    for(int i=1;i<=n4;++i){cin>>d[i];}
    for(int i=1;i<=n1;++i){f[1][i].first=a[i];f[1][i].second=i;}
    std::sort(f[1]+1,f[1]+n1+1);//将第一组菜价格升序排序
    for(int i=1;i<=n1;++i) a1[f[1][i].second]=i;
    cin>>m1;for(int i=1;i<=m1;++i){cin>>u>>v;edge[1][v].push_back(a1[u]);}//将编号转为次序插入
    for(int i=1;i<=n2;++i){
        if(edge[1][i].size()==n1){f[2][i].first=inf;f[2][i].second=i;continue;}//无法选择退出
        std::sort(edge[1][i].begin(),edge[1][i].end());//从小到大排序不能选的菜，这里为了方便直接次序代入
        int ans=edge[1][i].size()+1;
        for(int j=0;j<edge[1][i].size();++j)
            if(j+1<edge[1][i][j]){//如果有更便宜的且未选择
                ans=j+1;//记录答案
                break;//退出
            }
        f[2][i].first=b[i]+f[1][ans].first;f[2][i].second=i;//做出决策并记录编号
    }
    std::sort(f[2]+1,f[2]+n2+1);//接下来同理可得
    for(int i=1;i<=n2;++i) b1[f[2][i].second]=i;
    cin>>m1;for(int i=1;i<=m1;++i){cin>>u>>v;edge[2][v].push_back(b1[u]);}
    for(int i=1;i<=n3;++i){
        if(edge[2][i].size()==n2){f[3][i].first=inf;f[3][i].second=i;continue;}
        std::sort(edge[2][i].begin(),edge[2][i].end());
        int ans=edge[2][i].size()+1;
        for(int j=0;j<edge[2][i].size();++j)
            if(j+1<edge[2][i][j]){
                ans=j+1;
                break;
            }
        f[3][i].first=c[i]+f[2][ans].first;f[3][i].second=i;
    }
    std::sort(f[3]+1,f[3]+n3+1);//接下来同理可得
    for(int i=1;i<=n3;++i) c1[f[3][i].second]=i;
    cin>>m1;for(int i=1;i<=m1;++i){cin>>u>>v;edge[3][v].push_back(c1[u]);}
    for(int i=1;i<=n4;++i){
        if(edge[3][i].size()==n3){f[4][i].first=inf;f[4][i].second=i;continue;}
        std::sort(edge[3][i].begin(),edge[3][i].end());
        int ans=edge[3][i].size()+1;
        for(int j=0;j<edge[3][i].size();++j)
            if(j+1<edge[3][i][j]){
                ans=j+1;
                break;
            }
        f[4][i].first=d[i]+f[3][ans].first;f[4][i].second=i;
    }
    long long ans=f[4][1].first;//接下来取最小值作为答案
    for(int i=1;i<=n4;++i) ans=std::min(ans,f[4][i].first);
    cout<<(ans>=inf?-1:ans);
    return 0;
}
```

---

## 作者：Cutest_Junior (赞：0)

## 题解 CF1487E 【Cheap Dinner】

带点私货，这题是我在比赛还剩最后两分钟时交上去的，然后比赛结束两分钟还没跑出来，幸好最后还是 A 了，真是刺激呢。

### 题意

+ 有 $4$ 种菜类，第 $i$ 种有 $n_i$ 道菜，价格分别为 $a_{i,j}$；
+ 第 $i$ 种菜类和第 $i+1$ 种有 $m_i$ 对不能搭配，第 $i$ 个菜类第 $x_{i,j}$ 道菜和第 $i+1$ 个菜类第 $y_{i,j}$ 道菜不能搭配；
+ 每种菜类各要点一道菜，求最少总价格；
+ $1\le n_i\le150000,0\le m_i\le2\times10^5,1\le a_{i,j}\le10^8$。

### 代码

从第 $1$ 种菜类开始依次选，设 $dp_{i,j}$ 为选到第 $i$ 个菜类第 $j$ 道菜至少要花多少钱。

$dp_{i,j}=a_{i,j}+\min{dp_{i-1,k}}$，对于任意 $l$ 有 $x_{i-1,l}\ne k\operatorname{or}y_{i-1,l}\ne j$。

说人话，就是这道菜的价格加上能和它搭配的最小答案。

把不能搭配的放进 set 里，然后对前面的菜类按 dp 升序排序，依次判断是否在 set 里。

均摊复杂度 $O(n\log n)$。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

const int inf = (1 << 29) - 1;

const int N = 150005;

const int mod = 998244353;

struct Node {
	ll x, i;
} a[5][N];

bool operator < (Node a, Node b) {
	return a.x < b.x;
}

void solve() {
// 	printf("YES");
	int n[5];
// 	printf("E");
	for (int i = 1; i <= 4; ++i) {
		scanf("%lld", &n[i]);
	}
	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= n[i]; ++j) {
			scanf("%d", &a[i][j].x);
			a[i][j].i = j;
		}
	}
	for (int i = 1; i < 4; ++i) {
		sort(a[i] + 1, a[i] + n[i] + 1);
		a[i][n[i] + 1].x = inf;
		int m;
		scanf("%d", &m);
		set<int> v[N];
		for (int j = 1; j <= m; ++j) {
			int x, y;
			scanf("%d%d", &x, &y);
			v[y].insert(x);
		}
		for (int j = 1; j <= n[i + 1]; ++j) {
			for (int k = 1; k <= n[i] + 1; ++k) {
				if (v[j].find(a[i][k].i) == v[j].end()) {
					a[i + 1][j].x += a[i][k].x;
					break;
				}
			}
		}
	}
// 	printf("%d %d\n", a[3][1], a[3][2]);
	ll ans = inf;
	for (int i = 1; i <= n[4]; ++i) {
		ans = min(ans, a[4][i].x);
	}
	if (ans >= inf) {
	    printf("-1");
	}
	else {
	    printf("%lld", ans);
	}
}

int main() {
//	int t;
//	scanf("%d", &t);
//	while (t--) {
//printf("A");
		solve();
//	}
}
```

---

