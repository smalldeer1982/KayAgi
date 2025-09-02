# Guard Duty (medium)

## 题目描述

Princess Heidi decided to give orders to all her $ K $ Rebel ship commanders in person. Unfortunately, she is currently travelling through hyperspace, and will leave it only at $ N $ specific moments $ t_{1},t_{2},...,t_{N} $ . The meetings with commanders must therefore start and stop at those times. Namely, each commander will board her ship at some time $ t_{i} $ and disembark at some later time $ t_{j} $ . Of course, Heidi needs to meet with all commanders, and no two meetings can be held during the same time. Two commanders cannot even meet at the beginnings/endings of the hyperspace jumps, because too many ships in one position could give out their coordinates to the enemy.

Your task is to find minimum time that Princess Heidi has to spend on meetings, with her schedule satisfying the conditions above.

## 说明/提示

In the first example, there are five valid schedules: $ [1,4],[6,7] $ with total time 4, $ [1,4],[6,12] $ with total time 9, $ [1,4],[7,12] $ with total time 8, $ [1,6],[7,12] $ with total time 10, and $ [4,6],[7,12] $ with total time 7. So the answer is 4.

In the second example, there is only 1 valid schedule: $ [1,2],[3,4],[5,6] $ .

For the third example, one possible schedule with total time 6 is: $ [1,3],[4,5],[14,15],[23,25] $ .

## 样例 #1

### 输入

```
2 5
1 4 6 7 12
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 6
6 3 4 2 5 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 12
15 7 4 19 3 30 14 1 5 23 17 25
```

### 输出

```
6
```

# 题解

## 作者：MY（一名蒟蒻） (赞：9)

[CF958E2 Guard Duty (medium)](https://www.luogu.com.cn/problem/CF958E2)

## 0. 不知所言

题解区没人用 `set`，我来补这个空缺。

是个 5 倍经验，这个是后话了。

## 1. 分析

题目告诉我们要选择的是连续的区间，且区间不能共端点。

也就是说，对于一个点，左右两边的区间最多只能选一个。

由于区间的顺序和大小都一定，我们可以用一个点代替一个区间，每个点有代价，即为区间的长度。问题转化为选 $k$ 个不相邻的点，使得代价最小。以下“点”的表述全都为问题转化后的意思。

考虑普通的贪心，目前的选择会影响之后的决策集合，局部最优并不能得出全局最优。

注意到一个性质，如果不选代价最小的点 $i$， $i-1$ 和 $i+1$ 必选，否则一定不优。我一定有办法可以从这个方案中选一个代价大的点丢了换成 $i$。

## 2. 更进一步

从全局的角度考虑，我们希望可以撤销以前的选择，从而使目前的答案更优。

也就是反悔贪心。

由刚才的性质我们发现，撤销一个选择必然带来另外的点被选。于是我们得出一个算法雏形。

记代价为 $d$。

首先选择 $d_i$ 最小的点 $i$，然后在序列中删除 $i$、$i-1$ 和 $i+1$ 三个点，之后在原来的位置插入一个代价为 $d_{i-1}+d_{i+1}-d_i$ 的点。

重复以上过程 $k$ 次，就得到了最终的答案。

我们每次插入的点为撤销之前的选择提供了可能，是一种等价的做法。每一次插入点后我们得到的是一个新的序列，面对的是同样的问题，所以不用管具体是怎么加加减减的，没必要和自己费那劲，手玩下样例或者小数据也可知上述做法的正确。

## 3. 实现

对于以上的算法，我们需要实现
1. 单点插入删除，需要知道左右节点
2. 查询最小值

~~显然上平衡树~~查询最值可以用小根堆，懒惰插入删除。

这里用 `set` 做了，本质就是平衡树。

建立链表，链表中节点与平衡树映射即可。

删除避免麻烦可以加两个哨兵。代码中充斥着偷懒的味道。

## 4. Talk is cheap, show me the code.

建议大家自己实现，遇到困难可以参考一下。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <set>

using namespace std;

const int N=5e5+10;
typedef long long ll;
typedef pair <ll,int> PLLI;

int l[N],r[N];
ll d[N];
set <PLLI> s;

int del(int i) {//返回左节点 
	r[l[i]]=r[i]; l[r[i]]=l[i];
	set <PLLI> :: iterator it=s.find({d[i],i});
	s.erase(it);
	return l[i];
}

int main()
{
//  freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	int n,k;
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++) scanf("%lld",&d[i]);
	sort(d+1,d+1+n);
	for(int i=1;i<n;i++)
	{
		d[i]=d[i+1]-d[i];
		l[i]=i-1; r[i]=i+1;
		s.insert({d[i],i});
	}
	int id;
	d[0]=d[n]=1e16;
	s.insert({d[0],0}); s.insert({d[n],n});
	r[0]=1; l[n]=n-1;
	ll ans=0,x;
	for(int i=1;i<k;i++)
	{
		ans+=(x=(*s.begin()).first); id=(*s.begin()).second;
		int lid=l[id],rid=r[id],pos=del(del(del(r[id])));//偷懒
		s.insert({d[id]=d[lid]-d[id]+d[rid],id});
		l[r[pos]]=id; r[id]=r[pos];
		r[pos]=id; l[id]=pos;
	}
	printf("%lld\n",ans+(*s.begin()).first);
//  fclose(stdin); fclose(stdout);
    return 0;
}
```

## 5. 后话

是的还没完，还记得说好的 5 倍经验吗？

1. [CF958E2 Guard Duty (medium)](https://www.luogu.com.cn/problem/CF958E2)
2. [P3620 [APIO/CTSC2007] 数据备份](https://www.luogu.com.cn/problem/P3620)
3. [P1484 种树](https://www.luogu.com.cn/problem/P1484)
4. [P1792 [国家集训队]种树](https://www.luogu.com.cn/problem/P1792)
5. [SP1553 BACKUP - Backup Files](https://www.luogu.com.cn/problem/SP1553)

还有发现的可以评论下呀~

***Thanks for your reading!***

---

## 作者：皎月半洒花 (赞：6)

另一个老哥是真莽，$nk=5\cdot 10^5*5\cdot 10^3=2.5e9$ 这都能 `2995ms` 给爆过去，orzorz

发现题解区好像没有正常复杂度的，于是这里给出一个正常一点的带权二分做法。

_____


考虑一般 $dp$ 的话就是 $f_{i,j}$ ，这个地方由于不限制一定要取满，所以就可以有如下转移：
$$
f_{i,j}=\min\{f_{i-1,j},f_{i-2,j-1}+len(i-1,i)\}
$$
似乎常数小一点，暴力 $O(nk)$ 也是可以过的。于是就直接wqs二分一下，注意到由于此时最优的决策一定是少选，所以每选一次就需要减去 $mid$ 来维护这个限制。于是最后复杂度 $n\log V$ 。

需要注意的是，由于用了 $cnt_i$ 记录转移到 $i$ 这个状态至少要分成多少段，所以这个地方还是牵扯到一个，如果我可以有 $6/7/8$ 三种划分方式转移到最优解，那么到底应该用哪个。很显然的是要么用 $max$ 要么用 $min$，这取决于二分的方式。如果是取 $max$ 的话，那么可能 $cnt_n>m$ ；取 $min$ 的话则会 $\leq m$ 。所以根据这个调整代码细节就好了。

```cpp
ll res ;
ll f[N] ;
int m, n ;
int df[N] ;
int cnt[N] ;
int base[N] ;

bool check(int x){
	x *= -1 ;
	for (int i = 2 ; i <= n ; ++ i){
		if (f[i - 1] < f[i - 2] + df[i] + x)
			f[i] = f[i - 1], cnt[i] = cnt[i - 1] ; 
		else f[i] = f[i - 2] + (ll)df[i] + (ll)x, cnt[i] = cnt[i - 2] + 1 ;
		if (f[i - 1] == f[i - 2] + df[i] + x) cnt[i] = max(cnt[i - 1], cnt[i - 2] + 1) ;
	}
	res = f[n] - (ll)x * m ; return (bool)(cnt[n] >= m) ;
}
int main(){
	cin >> m >> n ; 
	for (int i = 1 ; i <= n ; ++ i) 
		scanf("%d", &base[i]) ; 
	sort(base + 1, base + n + 1) ; 
	for (int i = 1 ; i <= n ; ++ i) 
		df[i] = base[i] - base[i - 1] ;
	int l = 0, r = 1e9, mid, ans ; 
	while (l <= r){
		mid = (l + r) >> 1 ; 
//		cout << l << " " << r << endl ; 
		if (check(mid)) ans = mid, r = mid - 1 ;
		else l = mid + 1 ;
	}	
	check(ans) ; cout << res << endl ; return 0 ;
}
```



---

## 作者：reyik (赞：3)

$dp$

显然先排序，然后把相邻两个时间点的差算出来变成一个时间段

然后$dp[i][j]$表示到了第$i$个时间段，面姬到第$j$个人的答案

$dp[i][j]$有两种转移

$1.$这一个时间段没有面姬人，那么就是$dp[i-1][j]$

$2.$这一个时间段面姬了人，那么就是$dp[i-2][j-1]$

然后取$min$

code

```cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#define Rint register int
using namespace std;
int n,k;
const int inf=1e9+7;
int a[500005],d[500005];
int f[4][5005];
int main() {
        scanf("%d%d",&k,&n);
        for (Rint i=1;i<=n;++i) scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        for (Rint i=1;i<n;++i) d[i]=a[i+1]-a[i];
        memset(f,inf,sizeof(f));
        f[1][1]=d[1];
        for (int i=2;i<n;++i) {
                for (int j=1;j<=min((i+1)/2,k);++j) {
                        f[i%3][j]=min(f[(i-1)%3][j],f[(i-2)%3][j-1]+d[i]);
                }
        }
        printf("%d\n",f[(n-1)%3][k]);
        return 0;
}


```

---

## 作者：DengDuck (赞：2)

直觉告诉我们应该从大到小排一个序，然后选相邻的数字，这样代价最小，且这一点显然，在此不证明。

我们用差分处理出相邻的数字形成区间的价值，然后我们发现这里相邻的区间占有相同的点，不可同时选择，也就是相邻的区间不可选择。

那这个反悔贪心就很显然了。

首先用一个链表来维护数列，然后，每次贪心的选择最小的数字，并标记左右不可用。

但是这个贪心显然是错的，我们再直接将这三个数字合并为一个，价值为 $a_L+a_R-a_i$，意思大家应该懂。

显然这个数字，选择它相当于改选 $a_i$ 两边的数字，这就是我们的反悔了。

注意这里是最小值，所以你需要搞一个小根堆，而且左右边界要附一个较大的值。

需要注意的是，其实这里我们选择的数字不一定是答案方案中的数字，而是我们不断启用反悔机制，不断算上减量，得到最终答案。



```cpp
#include<bits/stdc++.h>
#define LL long long
#define T pair<LL,LL>
using namespace std;
priority_queue<T,vector<T>,greater<T> >p;
const LL N=1e6;
LL n,k,a[N],L[N],R[N],len,vis[N],ans;
int main()
{
	scanf("%lld%lld",&k,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++)
	{
		a[i]=a[i+1]-a[i]; 
		p.push({a[i],i});
		L[i]=i-1,R[i]=i+1;
	} 
	a[0]=a[n]=1e18;
	len=n;
	for(int i=1;i<=k;i++)
	{
		while(!p.empty()&&vis[p.top().second]==1)p.pop();
		LL t=p.top().second,v=p.top().first;
		ans+=v;
		p.pop();
		LL l=L[t],r=R[t];
		vis[t]=1,vis[l]=1,vis[r]=1;
		a[++len]=a[r]+a[l]-a[t];
		L[len]=L[l],R[len]=R[r],R[L[l]]=len,L[R[r]]=len;
		p.push({a[len],len});
	}
	printf("%lld",ans);
} 
```


---

## 作者：离散小波变换° (赞：2)

彩笔不会反悔贪心，彩笔也没细想斜率优化，彩笔只会面向数据范围做题。

## 题解

首先将 $t$ 排序去重。一个比较贪心的想法是选择 $t_i-t_{i-1}$ 最小的区间，但是这样可能会使得答案不合法。楼上有反悔贪心的做法来处理冲突，这里面向数据范围提供另外一个做法。

注意到虽然 $n$ 很大，但是 $k$ 相较而言要小得多。我们将 $[t_{i-1},t_i]$ 按照区间长度进行排序，大胆猜想，只有前 $3k$ 小的区间是真正重要的。证明：假设我们选择了一个排名在 $3k$ 开外的一个区间 $\alpha$，那么前 $3k$ 小的区间只选择了不超过 $k-1$ 个。而 $k-1$ 个区间最多只能使得另外 $2k-2$ 个区间不能被选，也就是说，这前 $3k$ 个区间里肯定至少有一个区间还是可以选择的。那么将 $\alpha$ 替换成该区间一定不劣。

那么我们只考虑这前 $3k$ 小的区间对应的端点。将这不超过 $6k$ 个端点去重排序，得到一组新的 $t'$，规模明显缩小。

记 $f_{i,j}$ 表示在前 $i$ 个点中，在选择了 $[t'_{i-1},t'_i]$ 这个区间的情况下，总共选了 $j$ 个区间，花费的最小代价。容易得到状态转移方程：

$$f_{i,j}=\min_{k\le i-2}\{f_{k,j-1}+(t'_i-t'_{i-1})\}=\min_{k\le i-2}\{f_{k,j-1}\}+(t'_i-t'_{i-1})$$

容易维护 $h_{i,j}=\min_{k\le i}\{f_{k,j}\}$。那么直接暴力转移复杂度为 $\mathcal O(k^2)$，可以通过。滚动数组一下可以将总空间复杂度降至 $\mathcal O(n+k)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 1e9;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 5e5 + 3;
const int MAXT = 1e6 + 3;
const int MAXM = 5e3 + 3;
int n, m, k, T[MAXN], P[MAXN], F[3][MAXM], H[3][MAXM];
tuple <int, int, int> G[MAXN];
int main(){
    k = qread(), n = qread();
    up(1, n, i) T[i] = qread();
    sort(T + 1, T + 1 + n);
    n = unique(T + 1, T + 1 + n) - T - 1;
    up(1, n - 1, i){
        G[i] = {T[i + 1] - T[i], i, i + 1};
    }
    sort(G + 1, G + 1 + n - 1);
    up(1, min(n - 1, 3 * k), i){
        int a = get<1>(G[i]);
        int b = get<2>(G[i]);
        P[++ m] = T[a];
        P[++ m] = T[b];
    }
    sort(P + 1, P + 1 + m);
    m = unique(P + 1, P + 1 + m) - P - 1;
    up(1, k, i) F[0][i] = H[0][i] = INF;
    up(1, k, i) F[1][i] = H[1][i] = INF;
    up(1, k, i) F[2][i] = H[2][i] = INF;
    int ans = INF;
    up(2, m, i){
        int a = i % 3, b = (i + 2) % 3, c = (i + 1) % 3;
        up(1, k, j){
            F[a][j] = H[c][j - 1] + P[i] - P[i - 1];
        }
        up(1, k, j)
            H[a][j] = min(H[b][j], F[a][j]);
        ans = min(ans, F[a][k]);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：STL_qwq (赞：2)

因为要代价尽可能小所以我们将数组排序后两两构造。

对数组 $t$ 排序后构造差分数组，这个问题就转化成了对于一个差分数组 $s$，选了 $s_i$ 就不能选 $s_{i-1}$ 和 $s_{i+1}$（因为要求区间没有交集），求选 $k$个元素后元素和最小的问题。

这就很明显看出反悔贪心了。

对于这类问题，我们有一个通法：

比较选 $s_i$ 或 $s_{i-1},s_{i+1}$ 哪个更优。

那要怎么比较呢？

就是我们在选了 $s_i$ 后把 $s_i$ 改为 $s_{i-1}+s_{i+1} -s_i$。

为啥？因为我们选完 $s_i$ 后把 $s_{i}$ 按照上面的步骤更新，如果现在 $s_i$ 还是全局最优就说明我选完 $s_i$ 还得选另外一个大的且代价大于选 $s_{i-1}+s_{i+1}$，所以不如选 $s_{i-1}+s_{i+1}$ 而不选 $s_i$，而我们选多一次 $s_i$ 后答案的增加量就变为 $s_i+s_{i-1}+s_{i+1}-s_i$ 也即 $s_{i-1}+s_{i+1}$（大家一开始不理解可以手模一下就清楚了），这样就实现了反悔。

我这里用的是优先队列处理最小值，链表增减元素。

最后注意一下在用双向链表反悔时注意我们是选了两端的，所以应该与两端的两端相连（具体看代码）。

### AC Code

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

#define ll long long
const int N=5e5+10;
const ll inf=0x3f3f3f3f; 
ll n,k,t[N],ans;
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > >q;
//STL的优先队列加个pair 
struct liSt{
	ll fro,nxt,val;
}li[N];//链表 
bool vis[N];//标记一个节点能不能选 
#define MK(x,y) make_pair(x,y)

void init(){li[0].val=li[n].val=inf;}
//防止两端影响答案，应该可以不要但加上总是好的 

void insert(ll node){
	li[node].fro=li[li[node].fro].fro;
	li[node].nxt=li[li[node].nxt].nxt;
	li[li[node].fro].nxt=node;
	li[li[node].nxt].fro=node; 
}//反悔，相当于选了两边而不选中间 

int main(){
	scanf("%lld %lld",&k,&n);
	init();
	for(int i=0;i<n;i++)
		scanf("%lld",&t[i]);
	//为了方便构造差分数组所以下标从0开始存 
	sort(t,t+n); 
	for(int i=1;i<n;i++){
		li[i].val=t[i]-t[i-1];
		q.push(MK(li[i].val,i));
		li[i].fro=i-1;
		li[i].nxt=i+1; 
	}
	while(k--){
		while(vis[q.top().second]) q.pop();
		ll opt=q.top().second;
		ll d=q.top().first;
		ans+=d;
		vis[li[opt].fro]=vis[li[opt].nxt]=1;
		q.pop();
		li[opt].val=li[li[opt].fro].val+li[li[opt].nxt].val-li[opt].val;
		//要求区间没有交集，所以差分数组选了一个头尾就不能选了 
		q.push(MK(li[opt].val,opt));
		insert(opt);
	}
	printf("%lld",ans);
	return 0;
} 
```
 ### _Thanks for reading!_ 

---

## 作者：longlinyu7 (赞：1)

# 题目分析
先将所有时间点从大到小排序，做一个差分数组 $s$，记录每一段小区间的长度，根据题目要求可知，$s_i$ 和 $s_{i+1}$，$s_{i}$ 和 $s_{i-1}$ 不能同时选择。

**那么问题就转化为，在 $n$ 个数中，选择 $k$ 个两两不相邻的数字，使得和最小。**

# 思路

先考虑使用小根堆，记录权值和编号，每次取出最小值，判断是否合法。

但其实这样是错误的，万一选取两边的数字比中间的数字更优呢，上述方法是考虑不到这种情况的。

那怎么做呢，建立一种反悔机制，就是**反悔贪心**。

假设选取了 $s_i$，将 $i$ 节点的值为 $s_{i+1}+s_{i-1}-s_i$，并删去 $s_{i+1}$ 和 $s_{i-1}$ 这两个节点。

为什么要这么做呢，假设在某一次操作中选取 $s_{i+1}$ 和 $s_{i-1}$  要比 $s_i$ 要更优，我们先选择了 $s_i$，但是在后来，又选择了新加入的节点，总体就是 $s_{i-1}+s_{i+1}-s_i + s_i=s_{i-1}+s_{i+1}$，就相当于是把加入 $s_i$ 这个行为给撤销了，加入了 $s_{i+1}$ 和 $s_{i-1}$。

这样就建立了一个完美的反悔机制。

# 做法

怎么实现删除某一个节点，可以使用 $vis$ 数组，并建立前驱与后继数组，

初始化。

```
pre[i]=i-1;
suc[i]=i+1;
```

在删除某一个点时，将该点的前驱与后继之间建立联系，并用 $vis$ 数组标记，不在访问它。

最后，需要注意一下头部与尾部的细节。

# code
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+5;
const int INF=2147483647;
ll n,k,a[N],s[N],pre[N],suc[N],vis[N];
ll ans;
struct node{
    ll num,val;
};
priority_queue<node,vector<node>,greater<node> >q;
bool operator>(node a,node b){
    return a.val>b.val;
}
// 在s数组中，选取k个数字，要求两两不相邻，使得选去的数字和最小。
void Delete(int x){
    pre[suc[x]]=pre[x];
    suc[pre[x]]=suc[x];
}
int main(){
    cin>>k>>n; 
    for(int i=1;i<=n;i++){
        cin>>a[i];
        
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        s[i]=a[i]-a[i-1];
        pre[i]=i-1;
        suc[i]=i+1;
        q.push((node){i,s[i]});
    }
    // 这两行很重要
    s[1]=s[n+1]=INF;        // 第一项前面没有配对的，无法选择
    vis[1]=vis[n+1]=1;
    while(k--){
        if(q.empty())break;
        node tmp=q.top();
        q.pop();
        while(vis[tmp.num]){
            tmp=q.top();
            q.pop();
        }
        ans+=tmp.val;
        int x=tmp.num;
        vis[pre[x]]=vis[suc[x]]=1;// 将前驱和后继都记录，不再访问
        s[x]=s[pre[x]]+s[suc[x]]-s[x];
        q.push((node){x,s[x]});  //加入新的东西
        Delete(pre[x]);
        Delete(suc[x]);
    }
    cout<<ans;


    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

# 思路分析

我们能获得一种显然错误的贪心思路：用 `priority_queue` 将所有区间存下来，每次取出最大值，判断是否可行，可行就加上，然后两边的设为不可行。

例如一种情况会轻松的卡掉这个思路：$15\space28\space15\space1$。按照这个思路，会选出 $28$ 和 $1$，实际上应该选两个 $15$。

这时候我们建立反悔机制：选出 $a_i$ 时，将其设置为 $a_{i-1}+a_{i+1}-a_i$，并将这个值入队。这时候，我们就有机会反悔，再次选择 $a_i$，这时候，我们的作用效果相当于选了 $a_{i-1}$ 和 $a_{i+1}$。

唯一的问题就是快速标记可行与否。我们可以用链表记录每一个元素前后的可行元素的下标，快速标记查询。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int v, p;
	node(int vi = 0, int pi = 0) {
		v = vi, p = pi;
	}
	friend bool operator<(const node& l, const node& r) {
		return l.v > r.v;
	}
}tmp; priority_queue<node>pq;
int n, m, a[1000005], ans, pre[1000005], nxt[1000005], lst[1000005], v, lts; bool vis[1000005];
signed main() {
	ios::sync_with_stdio(false);
	cin >> m >> n;
	for (int i = 0; i < n; ++i) cin >> lst[i];
	sort(lst, lst + n); lts = lst[0];
	for (int i = 1; i < n; ++i) {
		a[i] = lst[i] - lts;
		lts = lst[i]; pre[i] = i - 1; nxt[i] = i + 1;
		pq.push(node(a[i], i));
	}
	a[0] = a[n] = 0x3f3f3f3f;
	for (int i = 1; i <= m; ++i) {
		while (vis[pq.top().p]) pq.pop();
		tmp = pq.top(); pq.pop();
		ans += tmp.v;
		vis[pre[tmp.p]] = vis[nxt[tmp.p]] = 1;
		a[tmp.p] = a[pre[tmp.p]] + a[nxt[tmp.p]] - a[tmp.p];
		pq.push(node(a[tmp.p], tmp.p));
		pre[tmp.p] = pre[pre[tmp.p]];
		nxt[tmp.p] = nxt[nxt[tmp.p]];
		nxt[pre[tmp.p]] = tmp.p;
		pre[nxt[tmp.p]] = tmp.p;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Code_星云 (赞：1)

和数据备份一模一样的贪心题。

由于本题中的时间为正数，所以每次选相邻段是最优的。又由于不能相交，也就是说不能共用端点，不就是妥妥的反悔贪心吗？

具体地，用链表来维护即可。然后由于是取最小值，所以要把两端的值先赋值为正无穷。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<utility>
#include<queue>
using namespace std;
#define int long long
typedef pair<int, int> pii;
#define mp make_pair
#define px first
#define py second

const int N = 500005;
const int inf = 1e18;
struct node{
	int l, r, val;
}p[N];
int n, k, ans = 0, a[N];
bool ban[N] = {false};
priority_queue<pii, vector<pii>, greater<pii> > q;

void del(int x){
	p[x].l = p[p[x].l].l;
	p[x].r = p[p[x].r].r;
	p[p[x].l].r = x;
	p[p[x].r].l = x;
}
signed main(){
	scanf("%lld %lld", &k, &n);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 1; i < n; i ++){
		 p[i].val = a[i + 1] - a[i];
		 p[i].l = i - 1;
		 p[i].r = i + 1;
		 q.push(mp(p[i].val, i));
	}
	p[0].val = p[n].val = inf;
	for(int i = 1; i <= k; i ++){
		while(q.size() && ban[q.top().py]) q.pop();
		int id = q.top().py, val = q.top().px; q.pop();
		ans += val;
		ban[p[id].l] = ban[p[id].r] = true;
		p[id].val = p[p[id].l].val + p[p[id].r].val - p[id].val;
		q.push(mp(p[id].val, id));
		del(id);
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Others (赞：1)

这题和[数据备份](https://www.luogu.com.cn/problem/P3620)是一道题，很经典的“反悔贪心”。

先读题，将这道题转化一下（得排序），将时段长度作为选择对象，就成了这个样子：

~~~~
在 n-1 个时间段里选择 k 个不相邻的时间段，使得时间跨度总和最小。
~~~~

~~其实这样看来还有很多道经验。~~

第一眼其实很多人都会想到 $dp$，但是发现空间和时间都爆了，仔细想发现空间可以滚动，所以只有时间爆掉，但是还是不行，$O(nk)$ 的下限是突破不了的。

所以考虑贪心。这题想到贪心后脑子里就会很自然的冒出一个 "hack" 数据，大概是下面这个样子：

```
4 2
1 8 9 17
```

转化下来就成了这样：

`7 1 8`

如果按照最基础的贪心策略选最小的，也就是中间的 $1$，那这样左右两边的就不能选了，但是正解显然要选，这里就要用到反悔贪心了。

我们要选两边的，丢掉中间的，然后总数只加一，而且中间的之前已经选了，所以就会蹦出来一个东西：$a_{i+1}+a_{i-1}-a_i$，这时两边的不能选，这东西只能怼进 $a_i$ 里，而如果选了 $a_{i+1}$ 和 $a_{i-1}$ 后，$a_{i+2}$ 和 $a_{i-2}$ 都不能选，而此时你处理的对象是 $a_i$，所以在 $a_i$ 的指针域里存了应该是 $i+2$ 和 $i-2$，这样就可以不断地向外扩张。

最后讲一下我的实现：因为我是先做的一道和这题一样的环形背景下的题目，所以我强行构了个“超级点”使他是一个环（方便套代码）qwq。

最后贴个极丑码风的 Code。

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename zqw>void qr(zqw &x){
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
}
int n,m,a[500005],tot,flag[500005],nxt[500005],lst[500005],s[500005];
struct node{
	int id,x;
	bool operator<(const node &p)const{
		return x>p.x;
	}
};
priority_queue<node> qu;
int main() {
	qr(m),qr(n);
	qr(s[0]);
	n--;
	for(int i=1;i<=n;i++) {
		qr(s[i]);
	}
	sort(s,s+n+1);
	for(int i=1;i<=n;i++) {
		a[i]=abs(s[i]-s[i-1]);
		qu.push((node){i,a[i]});
		nxt[i]=(i==n?0:i+1);
		lst[i]=(i==1?0:i-1);
	}
	a[0]=1e9;
	qu.push((node){0,1000000000});
	while(m--){
		node tmp=qu.top();
		qu.pop();
		if(flag[tmp.id]) {
			m++;
			continue;
		}else{
			flag[nxt[tmp.id]]=flag[lst[tmp.id]]=1;
			tot+=a[tmp.id];
//			cout << tmp.id << " " << a[tmp.id] << endl;
			a[tmp.id]=a[nxt[tmp.id]]+a[lst[tmp.id]]-a[tmp.id];
			qu.push((node){tmp.id,a[tmp.id]});
			lst[tmp.id]=lst[lst[tmp.id]];
			nxt[tmp.id]=nxt[nxt[tmp.id]];
			nxt[lst[tmp.id]]=tmp.id;
			lst[nxt[tmp.id]]=tmp.id;
		}
	}
	cout << tot;
	return 0;
}
```


---

## 作者：wlxhkk (赞：1)

### ~~好好的题能用 $O(nk)$ 卡过去干嘛还要斜率凸优化呢？~~ 
先对时刻进行排序

设 $dp_{i,j}$ 表示前$i$个时刻选$j$个区间的最小代价，则有如下转移：
$$
dp_{i,j}=\min\{dp_{i-1,j},dp_{i-2,j-1}+a[i]-a[i-1]\}
$$
发现如果没有$k$个区间的限制，此题就可以用$O(n)$的时间跑过去，所以考虑消除此限制。

这时候就可以用$WQS$二分（斜率凸优化）来解决（不会的可以先学习一下）

每次我们都在选区间的时候将代价减去一个$m$，二分$m$使$dp_{n}$的结果刚好落在$k$上

感性理解一下，当要选的区间越多时，我们就不得不去选那些代价更大的区间，导致总代价的增长速度越来越快。因此$F(x)=dp_{n,x}$的图像是下凸的。(当然你也可以用朴素$dp$来打表判断)

因此当你发现直线$y=kx$与下凸包的交点横坐标大于$k$时，你应该减小$m$

时间复杂度 $O(n\log V)$

#### 代码：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500005],s[500005];
int f[500005],ch[500005];
int n,k,m;
bool check(int x){
    for(int i=2;i<=n;i++){
    	int t1=f[i-2]+ch[i]-x;
    	if(f[i-1]<t1) f[i]=f[i-1],s[i]=s[i-1];
    	else if(f[i-1]>t1) f[i]=t1,s[i]=s[i-2]+1;
    	else f[i]=f[i-1],s[i]=max(s[i-1],s[i-2]+1);
	}
	return s[n]>=k;
}
signed main(){
	cin>>k>>n;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    int l=0,r=0;
    for(int i=2;i<=n;i++) ch[i]=a[i]-a[i-1];
    r=a[n]-a[1];//奇技淫巧，斜率不可能大于a[n]-a[1];
    while(l<=r){
    	int mid=(l+r)>>1;
    	if(check(mid)) m=mid,r=mid-1;
    	else l=mid+1;
	}
	check(m);
    cout<<f[n]+m*k;
}
```

---

## 作者：OtterZ (赞：0)

# 题意
已知 $n$ 个坐标，要在里面选 $2 \times k$ 的坐标，得到最小的 $\sum_{i = 1}^{k}{a_{i \times 2} - a_{i \times 2 - 1}}$。

# 上二分
对于要选正好 $k$ 对的情况，我们试证明函数下凸，证明的话只需要构建费用流，根据算法 `SSP` 性质即可。

由此，我们得到了 `WQS` 二分可做此题的结论。

# 二分怎么做
接下来考虑 `WQS` 二分怎么做。

对于求取 $k$ 对坐标求最小 $\sum{a_{2 \times i} - a_{2 \times i - 1}}$ 函数 $\operatorname{g}(k)$，以及斜率为 $x$ 的 $\operatorname{g}(k)$ 的切线的截距 $\operatorname{f}(x)$ 和切点横坐标 $\operatorname{h}(x)$，根据 $\operatorname{h}(x)$ 单增的性质，我们二分一个斜率 $x$，得到答案 $\operatorname{f}(x) + x \times k$，就解决了这道题。

对于 $\operatorname{f}(x)$，我们设 $dp_{x,0}$ 为考虑前 $x$ 个，没选第 $x$ 个坐标的情况，$dp_{x,1}$ 为选第 $x$ 个坐标的情况，数组 $dp_{i,j}$ 为有两个数的变量，表示选的坐标的贡献的为第一关键字，表示坐标对数量的为第二关键字，则：

$$
\begin{cases}
dp_{i,0} = \max{dp_{i - 1,0},dp_{i - 1,1}}\\
dp_{i,1} = dp_{i - 1,0} + (-x + t_i - t_{i - 1},1)
\end{cases}
$$

有 $dp_{n + 1,0} = (\operatorname{f}(x),\operatorname{h}(x))$。

于是我们得到一个 $O(n\log n)$ 的解。

# 上代码


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,t[500009];
long long dp[500009][2],tp[500009][2],ans1,ans2;
void check(long long x){
	dp[1][0] = 0;
	tp[1][0] = 0;
	dp[1][1] = 9e16;
	for(int i = 2; i <= n + 1; i ++){
		if(dp[i - 1][0] < dp[i - 1][1] || (dp[i - 1][0] == dp[i - 1][1] && tp[i - 1][0] < tp[i - 1][1])){
			dp[i][0] = dp[i - 1][0];
			tp[i][0] = tp[i - 1][0];
		}
		else{
			dp[i][0] = dp[i - 1][1];
			tp[i][0] = tp[i - 1][1];
		}
		dp[i][1] = dp[i - 1][0] + t[i] - t[i - 1] - x;
		tp[i][1] = tp[i - 1][0] + 1;
	}
	ans1 = dp[n + 1][0],ans2 = tp[n + 1][0];
}
int main(){
	scanf("%d %d",&k,&n);
	for(int i = 1; i <= n; i ++){
		scanf("%d",&t[i]);
	}
	sort(t + 1,t + n + 1);
	//for(int i = 1; i <= n; i ++)
	//	printf("%d ",t[i]);
	//puts("");
	t[n + 1] = t[n];
	long long l = -1e9 - 7,r = 1e9 + 7;
	while(l + 1 < r){
		long long mid = r - (r - l >> 1);
		ans1 = ans2 = 0;
		check(mid);
		//printf("  %lld %lld %lld\n",mid,ans1,ans2);
		if(ans2 > k)
			r = mid;
		else
			l = mid;
	}
	//printf("%d\n",l);
	ans1 = ans2 = 0;
	check(l);
	printf("%lld\n",ans1 + 1ll * l * k);
	return 0;
}
```

---

## 作者：luxiaomao (赞：0)

## 堆 + 链表 + 反悔贪心

用来练练反悔贪心还是不错的，~~更何况还能水题解呢~~~

本题解主要补充题解区堆解法的不足。

## 分析

题意十分明确，这里无需进一步解释了。

首先我们注意到，题目要求的是使区间代价和**最小**，那么我们可以证明：只要选取两个相邻节点之间的小区间，如果有一个区间横跨三个甚至以上各节点，很容易证明选取它将不是最优的。

因此，我们很容易就将 $\dfrac{n(n+1)}{2}$ 个区间降成了 $n-1$ 个区间，不过相信这么简单的东西大家还是能够轻松推出来的，接下来进入本题重点。

题目要求：

> 保证这 $k$ 个连续的区间没有交集，且代价总和最小。

然后为了方便起见，我们将一个区间视为一个点，将区间的代价视为这个点的点权。

结合我们上面的结论，其实题面已经被我们剖析成了:

> 给出一条链上 $n-1$ 个带权的点，求选取 $k$ 个不相邻的点，使得点权之和最小。

是不是很熟悉呢？再加上 $n \le 5 \times 10^5$ 的~~凉心~~良心数据范围，我们成功将一道紫题转化成了一道非常普通的反悔贪心。

（~~什么？能够刷到这道题的你竟然没有听过反悔贪心？踢去[板子题](https://www.luogu.com.cn/problem/P1484)面壁思过~~）

根据个人的习惯，我采取了优先队列实现堆的贪心、数组实现双向链表。

## Code Time

思路讲解就到这里啦~接下来是你们最爱的环节~

看 AC 代码和注释讲解。

```cpp

#include<bits/stdc++.h>
#define int long long//别忘了数据范围
using namespace std;

int n,k;
int a[500500]; //先存区间分界的坐标，再来存每个区间的代价
int l[500500],r[500500]; 

bool vis[500500];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q; 
//别忘了要取最小值，所以用小根堆
signed main()
{
	scanf("%lld%lld",&k,&n);
	for(int i = 1;i <= n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+1+n);//排序，使得点的坐标递增，方便接下来处理
	
	for(int i = 1;i < n;i++)
	{
		a[i] = a[i+1] - a[i];
		l[i] = i-1,r[i] = i+1;
		q.push(make_pair(a[i],i));
	}
	a[0] = a[n] = 1e18;//注意取最小值，为了防止把这两个点取进去，要初始化为极大值
	l[0] = 1,r[n] = n-1;
	
	int sum = 0;
	for(int i = 1;i <= k;i++)//这一段是反悔贪心的板子代码
	{
		while(!q.empty() && vis[q.top().second])q.pop();
		int x = q.top().first,p = q.top().second;
		q.pop();
		
		sum += x;
		a[p] = a[l[p]] + a[r[p]] - a[p];
		q.push(make_pair(a[p],p));
		
		int L = l[p],R = r[p];
		vis[L] = vis[R] = 1;
		l[p] = l[L],r[l[L]] = p;
		r[p] = r[R],l[r[R]] = p;
	}
	printf("%lld",sum);
	return 0^_^0;//卖个萌
}
```

未压行 45 行的码量，还有个人觉得算清晰的码风 QAQ。

如果有疑问欢迎私信我哇~

---

## 作者：Comentropy (赞：0)

~~正当我苦苦搜寻一道题水估值的时候~~

我回忆起来有一次遇见了五倍经验题。这些题其实都是同一种做法。

## 分析
我们可以先用点代表区间，新的点的权值就是原先相邻两个“时间点”的权值差。于是我们就将问题转化成选择不相邻的 $k$ 个点是的权值和最小。于是如果选择一个点 $i$，就无法选择 $i-1$ 和 $i+1$。

我们很容易联想到贪心，但是考虑到朴素地进行贪心可能无法得到全局最优解。我们需要一个策略帮助我们处理后效性的影响——反悔贪心。

于是考虑撤销之前的操作，我们选择当前一个权值最小的点 $i$，权值为 $w_i$。之后，我们将 $i$，$i-1$，$i+1$ 合并成一个权值为 $w_{i-1}+w_{i+1}-w_i$ 的点。并持续维护点权最小值，进行普通贪心即可（重复 $k$ 次）。

简单说明一下上述做法的正确性。

首先对于一个点 $i$ 被选中并进行上述操作，可以发现它的相邻元素已经被合并，我们仍然可以选择 $i-1$ 和 $i+1$ 的其它相邻元素。

对于其权值，$(w_{i-1}+w_{i+1}-w_i)+w_i = w_{i-1}+w_{i+1}$，等价于只选两个点的情况，此时再进行合并操作，使得可选不可选分明，如上一步说明。

最后，它占用的次数相同，即你仍然通过此操作最后能恰达成 $k$ 次迭代的答案。

## 实现
如上所说，我们只需要用堆维护最小值，用链表完成删除与合并的操作即可（这样可以快速知道左右节点）。代码如下。
```cpp
// CF958E2 & SP1553 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
typedef pair<LL,int> PII;
const int N=5e5+500; // 以 CF 为基准 
const LL INF=1e16;
struct node{
	LL val;
	int l,r;
}a[N];	// 存间隙的值 
priority_queue<PII, vector<PII>, greater<PII> > q; 
bool vis[N]; 
int n,k;
LL res=0;

inline void update(int x){
	a[x].l=a[a[x].l].l;
	a[x].r=a[a[x].r].r;
	a[a[x].l].r=x;
	a[a[x].r].l=x;
	return ;
}
inline bool cmp(node x,node y){
	return x.val<y.val;
}
int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i].val);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<n;i++){
		a[i].val=a[i+1].val-a[i].val;
		a[i].l=i-1,a[i].r=i+1;
		q.push(make_pair(a[i].val,i));
	}
	
	a[0].val=a[n].val=INF;
	for(int i=1;i<=k;i++){
		while(!q.empty()&&vis[q.top().second])
			q.pop();
		auto t=q.top();q.pop();
		res+=t.first;
		int u=t.second;
		vis[a[u].l]=vis[a[u].r]=true;
		a[u].val=a[a[u].l].val+a[a[u].r].val-a[u].val;	// 反悔 
		q.push(make_pair(a[u].val,u));
		update(u);	// 实际上删的是两边 
	} 
	printf("%lld",res);
	return 0;
}
```


---

