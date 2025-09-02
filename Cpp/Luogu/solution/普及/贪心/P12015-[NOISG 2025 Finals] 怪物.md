# [NOISG 2025 Finals] 怪物

## 题目描述

Penguinland 是一条无限的数轴，上面有 $n$ 只怪物。第 $i$ 只怪物最初位于数轴上的位置 $a[i]$，其生命值为 $h[i]$。保证没有两只怪物具有相同的初始位置。

今天，企鹅 Brian 想要打败所有的怪物！为了打败它们，Brian 在某些位置埋下了 $k$ 颗地雷。第 $j$ 颗地雷位于位置 $x[j]$。引爆一颗地雷会**立即摧毁所有**站在该位置的怪物，并且每颗地雷可以被引爆任意次数。然而，每次引爆的代价是 $1$ 美元。保证没有两颗地雷被埋在相同的位置。

除了引爆地雷，Brian 还可以执行两种操作：

- 将一只怪物向左或向右移动 $1$ 个单位距离。
- 增加或减少一只怪物的生命值 $1$。

每次操作的代价是 $1$ 美元。

如果一只怪物的生命值降至 $0$ 或者它被地雷摧毁，则认为该怪物被打败。请帮助 Brian 找出打败所有怪物所需的最小代价（以美元计）。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq n, k \leq 200\,000$
- 对于所有 $1 \leq i \leq n$，有 $1 \leq a[i], h[i] \leq 10^9$
- 对于所有 $1 \leq i \leq k$，有 $1 \leq x[i] \leq 10^9$
- 对于所有 $i \neq j$，有 $a[i] \neq a[j]$
- 对于所有 $i \neq j$，有 $x[i] \neq x[j]$

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $14$ | $k = 1$ |
| $2$ | $6$ | $k = 2$ |
| $3$ | $10$ | $n, k \leq 18$ |
| $4$ | $30$ | $n, k \leq 3000$ |
| $5$ | $29$ | $h[i] = 10^9$ |
| $6$ | $11$ | 无 |

### 样例 1 解释

此样例适用于子任务 $1, 3, 4, 6$。

有 $n = 3$ 只怪物和 $k = 1$ 颗地雷。Brian 可以：

- 将怪物 $1$ 的生命值减少至 $0$，花费 $2$ 美元。
- 将怪物 $2$ 向右移动 $1$ 个单位（位置从 $4$ 变为 $5$），花费 $1$ 美元。
- 引爆位置 $5$ 处的地雷，击败怪物 $2$ 和怪物 $3$，花费 $1$ 美元。

总花费为 $2 + 1 + 1 = 4$ 美元。

### 样例 2 解释

此样例适用于子任务 $2, 3, 4, 6$。

有 $n = 5$ 只怪物和 $k = 2$ 颗地雷。Brian 可以：

- 将怪物 $5$ 的生命值减少至 $0$，花费 $1$ 美元。
- 引爆地雷 $2$，击败怪物 $3$，花费 $1$ 美元。
- 将怪物 $2$ 向右移动 $1$ 个单位（位置从 $6$ 变为 $7$），花费 $1$ 美元。
- 将怪物 $4$ 向右移动 $3$ 个单位（位置从 $4$ 变为 $7$），花费 $3$ 美元。
- 引爆地雷 $1$，击败怪物 $1, 2, 4$，花费 $1$ 美元。

总花费为 $1 + 1 + 1 + 3 + 1 = 7$ 美元。

### 样例 3 解释

此样例适用于子任务 $3, 4, 6$。


## 样例 #1

### 输入

```
3 1
2 2
4 5
5 4
5```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2
7 7
6 3
10 4
4 4
9 1
7 10```

### 输出

```
7```

## 样例 #3

### 输入

```
10 5
19 10
5 3
1 2
3 6
17 2
20 3
8 2
12 3
14 2
15 1
40 13 37 14 6```

### 输出

```
23```

# 题解

## 作者：__xxy_free_ioi__ (赞：5)

# P12015 \[NOISG 2025 Finals] 怪物

~~毒瘤~~

## 解法

易得，此题为贪心。

我们来想想贪心的策略，首先，我们很显然的可以想到一个解法：在有怪物地雷肯定是要引爆的。计算每一只怪物移动到附近地雷的代价（加上引爆代价），如果它小于等于这只怪物的生命值 $h_i$，那么我们就选择移动并引爆，否则直接敲死即可。但是，这样明显是错误的，我们不应该将怪物移动到地雷上就引爆，应该看看有没有其他怪物也要移动到这里，一起引爆，能省更多的钱，那么我们就需要定义一个数组 $st$ 来表示这里是否已经有怪物了。至于为啥是小于等于 $h_i$ 呢，原因是你占一个地雷说不定可以让其他怪物更少花费便可以被杀死。而判断移动到附近地雷的代价，我们只要将 $x$ 数组排序，使用 lower\_bound 即可。

这样，我们的代码就初具雏形了，欸，交上去怎么只要 14 pts？仔细想想，发现是想漏了一种情况，比如说：
![](https://cdn.luogu.com.cn/upload/image_hosting/1fc6ki7g.png?x-oss-rocess=image/resize,m_lfit,h_170,w_225)

这种怪物处于中间（并且两边移动花费（包括引爆费用）相同，移动花费小于怪物生命值）的情况又怎么办呢？哦，我们应该将怪物的位置也进行排序，这样，前面的已经全部处理完了，我们只需要考虑后面的，自然是向后移动啦！

## 代码

理清了思路，代码就很好写了。

```
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;

struct Monster {
    int a, h;
    bool operator< (const Monster& W) {return a < W.a;}
} monsters[N];

int n, k, res;
int x[N], st[N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> monsters[i].a >> monsters[i].h;
    for (int i = 1; i <= k; i++) cin >> x[i];

    sort(x + 1, x + k + 1);
    sort(monsters + 1, monsters + n + 1);
    
    for (int i = 1; i <= n; i++) {
        int a = monsters[i].a;
        int p = lower_bound(x + 1, x + k + 1, a) - x;
        if (a == x[p]) st[p] = 1;
    }
    for (int i = 1; i <= n; i++) {
        int a = monsters[i].a, h = monsters[i].h;
        int p = lower_bound(x + 1, x + k + 1, a) - x;
        int c1 = a - x[p - 1], c2 = x[p] - a,
            t1 = !st[p - 1], t2 = !st[p];
        if (p == 1) {
            if (c2 + t2 <= h) st[p] = 1;
            res += min(h, c2);
        } else if (p == k + 1) {
            if (c1 + t1 <= h) st[p - 1] = 1;
            res += min(h, c1);
        } else if (c1 + t1 < c2 + t2) {
            if (c1 + t1 <= h) st[p - 1] = 1;
            res += min(h, c1);
        }  else {
            if (c2 + t2 <= h) st[p] = 1;
            res += min(h, c2);
        }
    }

    for (int i = 1; i <= k; i++) 
        res += st[i];
    
    cout << res << '\n';

    return 0;
}
```

---

## 作者：shijingteng (赞：3)

这道题要我们求出打败所有怪物所花费的代价最小，很容易想到贪心，对于每一只怪物，我们有以下两种方法打败它：

1. 一直将它的血量减少 $1$，直到它的血量为 $0$。
2. 将怪物移动到距离它最近的地雷处，用地雷将其打败。

明确了思路，我们只需要将这两种情况所需的代价取最小值，然后加到答案中就可以了。但是，有一种特殊的情况，就是如果我们选择移动怪物，而且怪物离它左右两边最近的地雷的距离相等。这样，我们就需要选择一边，使得最终答案最小。

为了处理这种情况，我们可以在选择的时候优先选择右边，这通常能让之后仍在右侧的怪物复用这个地雷，从而总体更省钱。反之若优先选左侧，左侧通常不会帮助右边未处理的怪物。

除此之外，还要新增一个数组，用来记录各个位置的地雷有没有爆炸过，若某个位置的地雷没有爆炸过，则所需的代价就要增加 $1$。

### 具体代码：
```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn=200000+10;
typedef long long ll;
struct monster{
	ll a,h;
}p[maxn];
ll n,k,x[maxn],ans;
bool vis[maxn];
bool cmp(monster x,monster y){
	return x.a<y.a;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>p[i].a>>p[i].h;
	for(int i=1;i<=k;i++) cin>>x[i];
	sort(p+1,p+n+1,cmp);
	sort(x+1,x+k+1);
	for(int i=1;i<=n;i++){
		ll loc=p[i].a,h=p[i].h,dis1=LLONG_MAX,dis2=LLONG_MAX;
		ll pos=lower_bound(x+1,x+k+1,loc)-x;
		if(pos<=k){
			dis1=x[pos]-loc;
			if(!vis[pos]) dis1++;
		}
		if(pos-1>=1){
			dis2=loc-x[pos-1];
			if(!vis[pos-1]) dis2++;
		}
		ans+=min(min(dis1,dis2),h);
		if(min(dis1,dis2)<=h){
			if(dis1<=dis2&&pos<=k) vis[pos]=1;
			else if(dis1>dis2&&pos-1>=1) vis[pos-1]=1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Mr_Az (赞：3)

# [P12015 [NOISG 2025 Finals] Monsters](https://www.luogu.com.cn/problem/P12015)

### Algorithm:

贪心。

### Solution:

场上写了一个小时，无脸见人。

首先炸弹肯定在移动完怪兽后才引爆，我们也不会增加怪物血量。

所以我们把所有的怪物分为两部分，一部分是直接被扣光血量的，一部分是被炸弹炸死。记 $d_i$ 为第 $i$ 只怪兽距离最近的炸弹的距离，那么有：

1. $h_i \le d_i$：直接扣光，代价 $+d_i$。
2. $h_i>d_i$：走到炸弹上，代价 $+h_i$。

但是我们需要对第二种情况进行讨论，因为可能怪兽距离前后的炸弹距离一致，那么我们只要按以下贪心策略选择即可，记 $pre$ 为前一个炸弹的编号，$nxt$ 为后一个炸弹的编号，$f_i$ 为这个编号上的炸弹有没有被选择。

1. 将所有的怪物按照坐标进行排序。
2. 如果 $f_{pre}=1$，则不需要操作，直接走到前一个炸弹位置即可。
3. 如果 $f_{pre}=0$，则选择走到后一个炸弹，让 $f_{nxt}=1$，代价 $+1$。

正确性显然，二分查找前后炸弹。

代码很丑，别看了。

### Code:

```cpp
namespace Mr_Az{
	int T=1;
	const int N=2e5+8;
	int n,k,ans;
	int x[N];
	bool f[N];
	struct node{
		int a,h;
		bool operator<(const node &A)const{return a<A.a;}
	}a[N];
	inline void solve(){
		read(n,k);
		f[0]=1;
		for(rint i=1;i<=n;i++) read(a[i].a,a[i].h);
		for(rint i=1;i<=k;i++) read(x[i]);
		sort(a+1,a+n+1);sort(x+1,x+k+1);
		for(rint i=1;i<=n;i++){
			int nxt=upper_bound(x+1,x+k+1,a[i].a)-x,pre=nxt-1;
			int pr=a[i].a-x[pre],nx=x[nxt]-a[i].a;
			if(pre==0) pre=0,pr=INF;
			if(x[nxt]<a[i].a) nxt=0,nx=INF;
			if(a[i].h<=min(pr,nx)) ans+=a[i].h;
			else{
				ans+=min(pr,nx);
				if(pr<nx){if(!f[pre]) f[pre]=1,ans++;}
				else if(pr>nx){if(!f[nxt]) f[nxt]=1,ans++;}
				else{
					if(!f[pre]&&!f[nxt]) f[nxt]=1,ans++;
				}
			}
		}
		printf("%lld\n",ans);
	}
	inline void mian(){if(!T) read(T);while(T--) solve();}
}
```

---

## 作者：wang6w6 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P12015)

# 思路
算法是**二分**和**贪心**。

先把怪物和地雷坐标**排序**。

我们先分情况讨论如何打死怪物，由题意知可分为两种，即直接减生命值，用地雷炸死。

第一种，显然，如果怪物自身生命值小于或等于距离怪物最近的地雷的距离，就直接减去。

第二种，我们可以再分为两种情况，即距离左右两端地雷的距离不等或**相等**，前者可以看距离哪个短就走到哪个地雷再标记一下，而后者如果左边的地雷被标记了就优先到左边的，否则就到右边的并标记，这样可以利用之前被标记的地雷，减少花费。

其中的左右距离相等很难想到，要细心。

至于二分，我们可以使用 upper_bound 函数，它可以在已排序的范围内查找第一个**大于**给定值的元素，以便于我们找到怪兽左右边的地雷的坐标。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5;
ll n,k,x[N],l,r,lx,rx,ans,cnt,vis[N];
struct stu{
	ll a,h;//要注意a是坐标，h是生命值！！！ 
}d[N];
bool cmp(stu a,stu b){
	return a.a<b.a;
}
int main(){
	cin>>n>>k;
	for(ll i=1;i<=n;i++){
		cin>>d[i].a>>d[i].h;
	}
	for(ll i=1;i<=k;i++){
		cin>>x[i];
	}
	sort(d+1,d+1+n,cmp);//排序 
	sort(x+1,x+1+k);
	for(ll i=1;i<=n;i++){
		r=upper_bound(x+1,x+1+k,d[i].a)-x;//在已排序的范围内查找第一个大于给定值的元素
		l=r-1;//左右地雷的坐标 
		lx=d[i].a-x[l];
		rx=x[r]-d[i].a;//距离左右地雷的距离
		if(x[l]<=0) lx=1e18;//防止越界 
		if(x[r]<=0) rx=1e18;
		if(min(rx,lx)>=d[i].h){//第一种情况 
			ans+=d[i].h;
		}else if(rx!=lx){//第二种情况 
			if(rx>=lx){
				ans+=lx;
				vis[l]=1;
			}else{
				ans+=rx;
				vis[r]=1;
			}
		}else{//左右相等 
			if(vis[l]==1){
				ans+=lx;
			}else{
				ans+=rx;
				vis[r]=1;
			}
		}
//		cout<<lx<<" "<<rx<<' '<<ans<<"\n";
	}
	for(ll i=1;i<=k;i++){
		ans+=vis[i];//引爆被标记的的地雷 
	}
	cout<<ans;
	return 0;
}
//1 2 3 4 5
//		*
//  2   5 4
```
完结撒花。

---

## 作者：guoshengyu1231 (赞：2)

# 前言
这道题看似是一道非常简单的贪心，但我觉得这里需要注意的地方有许多。别看是一道黄题，我可是调了将近两个小时。
# 思路
思路其实很简单，其实就是贪心。看看一个怪物是选择把血扣光快还是移到地雷处快。如果光这一个限制那这题还是很简单的，关键是我们可以选择将所有怪物聚集在一起然后一起炸死。那这会对我们解题有什么影响呢？试想一下，如果一个怪物来到一个地雷处，但是这个位置已经有怪物了。那我们是不是能省下一次爆炸的代价。那既然省下了一次爆炸的代价，那是不是会较大程度的影响我们贪心的算法。答案是否定的，因为只会省下**一**次，是**一**次。就因为是一次，他最多只会从大于变成等于，不会瞬间从大于变成小于。对于每一个怪物，他能省下**一**次爆炸的代价，对于他与自己血的比较根本无伤大雅。所以这一点还是很好判断的，具体详见代码。
# 代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn=2e5+5;
const int INF=1145145145;
int n,m,x[maxn],a[maxn],d[maxn];
int dis[maxn],to[maxn];
bool vis[maxn];
//dis：与地雷的最近距离，to：与哪个地雷最近
//vis：哪些地雷要引爆
ll ans;
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>x[i]>>a[i];
    for(int i=1;i<=m;i++) cin>>d[i];
    sort(d+1,d+m+1);
    d[0]=-INF;d[m+1]=INF;//边界
    for(int i=1;i<=n;i++)
     {
        int t=lower_bound(d,d+m+2,x[i])-d;//查询与他距离较近的地雷
        ll d1=abs(d[t]-x[i]);
        ll d2=abs(d[t-1]-x[i]);
        if(d1<d2){to[i]=t;dis[i]=d1;}
             else{to[i]=t-1;dis[i]=d2;}//比较那个更近。
     }
    for(int i=1;i<=n;i++)
     if(dis[i]+1<=a[i]){ans+=dis[i];vis[to[i]]=true;}
                   else{ans+=a[i];}
    for(int i=1;i<=m;i++) 
     if(vis[i]) ans++;
    cout<<ans;
    return 0;
}
```
当你愉快的提交这份代码，发现只有[14分](https://www.luogu.com.cn/record/212418236)。这又是怎么回事呢？你下意识的认为，不是洛谷的错，是你自己的错。于是你开始思考自己到底错那里了。你绞尽脑汁的想了很久，忽然意识到了一点，那就是我们不仅要保证对怪物操作的代价尽可能的小，还要是引爆地雷的代价尽可能的小。举个例子，有一只怪物，他来到自己左右两个地雷的距离都一样，但是其中一个地雷还没有怪物，如果我们此时来到这个地雷，是不是又要为这只怪物专门引爆一个地雷？但如果另外一个地雷已经打算引爆了，那来到那个地雷，就不需要再花费 $1$ 代价来引爆地雷。这对我们计算的影响也不大，因为也就节省一次爆炸的代价，我们不需要用很复杂的代码来平衡两者的代价，只需要用一个布尔数组 $f$ 来记录哪些怪物与左右两个地雷的距离是相等的，而这些怪物再进行特殊处理。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
const int INF=1145141919810;
int n,m,x[maxn],a[maxn],d[maxn];
int dis[maxn],to[maxn];
bool vis[maxn],f[maxn];
int ans;
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>x[i]>>a[i];
    for(int i=1;i<=m;i++) cin>>d[i];
    sort(d+1,d+m+1);
    d[0]=-INF;d[m+1]=INF;
    for(int i=1;i<=n;i++)
     {
        int t=lower_bound(d,d+m+2,x[i])-d;
        int d1=abs(d[t]-x[i]);
        int d2=abs(d[t-1]-x[i]);
        if(d1<d2){to[i]=t;dis[i]=d1;}
             else{to[i]=t-1;dis[i]=d2;}
        if(d1==d2) f[i]=true;//特殊对待
        }
    for(int i=1;i<=n;i++)
     {
     if(f[i]) continue;
     if(dis[i]+1<=a[i]){ans+=dis[i];vis[to[i]]=true;}
                   else{ans+=a[i];}
     }
    //特殊处理
    for(int i=1;i<=n;i++) 
    if(f[i])
     {
         if(dis[i]+1>a[i]){ans+=a[i];continue;}//这句千万不能忘记！
         ans+=dis[i];
         if(!vis[to[i]]) vis[to[i]+1]=true;
         }
    for(int i=1;i<=m;i++) 
     if(vis[i]) ans++;
    cout<<ans;
    return 0;
}
```
此时费尽千辛万苦改好代码的你，认为自己已是万事俱备，只差把代码提交上去了。你兴冲冲地将代码提交上去，等着自己的评测结果。结果出来了，恭喜你，成功获得了[61分](https://www.luogu.com.cn/record/212440667)的好成绩。于是你开始思考自己究竟哪里还有错。你回头想了想自己的思路是否有问题，可你发现自己的思路简直是井然有序，天衣无缝，根本挑不出毛病。这么完美的思路怎么可能有错，你开始怀疑是不是评测系统针对自己。等等！有序……哦！你开始恍然大悟，是的，既然是贪心，那肯定是需要考虑最值，既然要考虑最值，那肯定是得让数据变得有序。你仿佛发现了自己代码的漏洞，你随手写了一个数据：

```cpp
2 3
7 1145
3 1145
1 5 9
```
这里本应该输出 $5$，但自己的代码却输出 $6$。 $\\$ 
你很快就知道了原因，因为在你考虑在位置 $7$ 上的地雷时还没有考虑在位置 $3$ 上的地雷。由于在上述代码中我们在判断的时候是默认选右边的地雷的，所以应该按位置从左往右考虑，这样前面的考虑完了那后面的就不用再考虑前面的选择了，自然是选右边的啦！
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
const int INF=1145141919810;
int n,m,d[maxn];
int dis[maxn],to[maxn];
bool vis[maxn],f[maxn];
int ans;
struct node{
    int x,h;
}a[maxn];    
bool cmp(node a,node b)
{
    return a.x<b.x;
}    
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].h;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=m;i++) cin>>d[i];
    sort(d+1,d+m+1);
    d[0]=-INF;d[m+1]=INF;
    for(int i=1;i<=n;i++)
     {
        int t=lower_bound(d,d+m+2,a[i].x)-d;
        int d1=abs(d[t]-a[i].x);
        int d2=abs(d[t-1]-a[i].x);
        if(d1<d2){to[i]=t;dis[i]=d1;}
             else{to[i]=t-1;dis[i]=d2;}
        if(d1==d2) f[i]=true;     
        }
    for(int i=1;i<=n;i++)
     {
     if(f[i]) continue;
     if(dis[i]+1<=a[i].h){ans+=dis[i];vis[to[i]]=true;}
                   else{ans+=a[i].h;}
     }  
    for(int i=1;i<=n;i++) 
    if(f[i])
     {
         if(dis[i]+1>a[i].h){ans+=a[i].h;continue;}
         ans+=dis[i];
         if(!vis[to[i]]) vis[to[i]+1]=true;
         }
    for(int i=1;i<=m;i++) 
     if(vis[i]) ans++;
    cout<<ans;
    return 0;
}
```
终于，你怀着忐忑的心，提交了代码，皇天不负有心人，这次，你终于得了[100分](https://www.luogu.com.cn/record/212430969)。你简直高兴得整晚睡不着觉，~~话说做出一道黄题你高兴啥呢~~。

---

## 作者：KomeijiReimu (赞：1)

https://www.luogu.com.cn/problem/P12015

肯定是能一次炸死的怪物越多越好，因此对于炸弹附近的怪物我们需要想办法把他们移到最近的炸弹处。

贪心地考虑，如果移动这个怪物的花费小于在原地直接干死这个怪物的花费，那么移动这个怪物肯定是划算的。因此对于每个怪物，我们重复进行这个判断过程，把符合条件的怪物引到炸弹的位置，在最后引爆这个炸弹（也就是炸弹最多只用引爆一次）就能够找到最小的团灭花费。

不过这个过程有很多细节需要考虑：

一个是引爆炸弹也是有一块钱代价的，因此如果有一个怪物距两个炸弹的距离相同，那么为了节省炸弹成本肯定是**优先考虑最终一定会被引爆的那个**。
- 举例来说：怪物 A 站在炸弹 1 的位置，怪物 B 血量为 10 ，与炸弹 1 和炸弹 2 的距离都是 5 。由于炸弹 1 的位置有怪兽，因此炸弹 1 **一定会被引爆**，这样怪物 B 选炸弹 1 和炸弹 2 的最终成本分别是 6 和 7 。

通过上面的例子，我们知道如果选择了炸弹 2，由于最终要多引爆一个炸弹，因此花费要多出 1 。在比较的过程中，为了方便，我们可以**把引爆成本算到距离成本上**，也就是直接把到炸弹 1 和炸弹 2 的距离看作是 5 和 6，这样就能直观对比。

另一个是如果一个怪物在**转换成本后**和两个炸弹的距离依旧相同，那么我们该怎么选。为此我们可以把怪物序列按照他们的位置升序排列，一个怪物与其前面的炸弹 A 和后面的炸弹 B 距离相同，它选择哪个都可以，但是下一个怪物要么选择炸弹 B ，要么选择更靠后的炸弹，**绝无可能选择炸弹 A** 。所以如果下一个怪物想要选择炸弹 B，那么炸弹 B 要是已经确定一定会被引爆就是最好的情况。既然前面的怪物选 A 选 B 无所谓，那么不如选 B ，这样可以帮助后面的怪物激活这颗炸弹。

细节和流程如上。能否确定最终会被引爆用一个 $\displaystyle st[i]$ 记录，代表第 $\displaystyle i$ 个炸弹会被引爆。从位置开始从小到大判断怪物，为了找到离这个怪物最近的炸弹位置，我们也得给炸弹按照位置排序，用二分来找。
```cpp
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const long long N = 2e5 + 10;

pair<long long, long long> a[N];
long long x[N];
bool st[N];
long long n, k;
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;

    for (long long i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;

    for (long long i = 0; i < k; i++)
        cin >> x[i];

    sort(a, a + n);
    sort(x, x + k);

    for (long long i = 0; i < n; i++) {
        // 有怪物的炸弹一定会被引爆，先把1的引爆成本加上
        long long p = lower_bound(x, x + k, a[i].first) - x;
        if (a[i].first == x[p] and !st[p]) {
            st[p] = true;
            ans++;
        }
    }

    for (long long i = 0; i < n; i++) {
        long long p = lower_bound(x, x + k, a[i].first) - x;
        // 只有一个炸弹的选择
        if (p == 0) {
            long long d = abs(x[p] - a[i].first);
            if (d <= a[i].second) {
                // 如果这个炸弹没有提前确定要引爆，那么要先激活，把引爆成本加上
                if (!st[p]) {
                    st[p] = true;
                    ans++;
                }
                ans += d;
            } else
                ans += a[i].second;
        } else if (p == k) {
            long long d = abs(x[p - 1] - a[i].first);
            if (d <= a[i].second) {
                if (!st[p - 1]) {
                    st[p - 1] = true;
                    ans++;
                }
                ans += d;
            } else
                ans += a[i].second;
        } else {
            // 考虑前后炸弹的距离，并且把引爆成本算到距离成本上
            long long pred =
                st[p - 1] ? a[i].first - x[p - 1] : a[i].first - x[p - 1] + 1;
            long long nextd = st[p] ? x[p] - a[i].first : x[p] - a[i].first + 1;
            // 优先选择后面的炸弹
            if (nextd <= pred) {
                if (nextd <= a[i].second) {
                    // 这里标记无所谓之前是什么状态，因为成本已经算到距离上了
                    st[p] = true;
                    ans += nextd;
                } else
                    ans += a[i].second;
            } else {
                if (pred <= a[i].second) {
                    st[p - 1] = true;
                    ans += pred;
                } else
                    ans += a[i].second;
            }
        }
    }

    cout << ans;

    return 0;
}
```

---

## 作者：Chengqijun2012 (赞：1)

一道很不错的题目，~~（本蒟蒻磕了1个多小时）~~ 以此发篇题解纪念一下。

本题的**形式化解题目标**是：得出消灭所有的怪物**最少**需要用的钱数。

从题目中可得，要消灭一只怪物只有两种方式：
- 用地雷炸死（下称炸死）。
- 减少怪物的生命值（下称用钱砸死）。

怎么解题呢？仔细观察题目可以发现：如果怪物站在地雷上，那么炸死怪物所用的钱数总是小于或等于用钱砸死怪物所用的钱数。因此我们要尽可能让怪物被炸死，当怪物不在地雷上时，我们就要花钱让怪物走到地雷上。但是当怪物的血量比它与离它最近的地雷的距离还要少时，我们就可以直接用钱砸死它。

因此我们可以用一个 $ans$ 最少需要的钱数。然后遍历每个怪物，并找出离它最近的两个地雷，用 $lenl$ 和 $lenr$ 分别存它与两个地雷的距离。如果怪物的血量比 $lenl$ 和 $lenr$ 都要少时，我们就可以直接用钱砸死它，也就是 $ans$ 加上怪物的血量。否则，我们就让 $ans$ 加上 $\min(lenl, lenr)$，但是如果这个地雷还没有怪物，$ans$ 就还要加上引爆地雷用的 $1$ 美元。

思路有了，那怎么找地雷呢？如果直接遍历，不仅代码复杂 ~~（别问我怎么知道）~~，而且复杂度是 $O(n^{2})$ ，这显然是无法承受的。于是我们可以考虑先把怪物和地雷分别按位置排序，再二分找地雷，这样时间复杂度就是 $O(n\log n)$，不会超时。

前置芝士：[lower_bound & upper_bound](https://blog.csdn.net/qq_63586399/article/details/136726979)。

AC Code：
```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>
#define ll long long
#define P pair<int, int>
#define MP make_pair
#define PU push_back
using namespace std;
const int N = 200000 + 5;
ll n, k, x[N], cnt[N], ans;      //x存地雷的坐标，cnt存每个地雷上怪物的个数

struct ghost{
	ll a, h;      //存怪物的坐标和血量
}p[N];

inline bool cmp(ghost a, ghost b){
	return a.a < b.a;
}

int main(){
//	freopen("water.in.txt", "r", stdin);
//	freopen("water.out.txt", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> k;
	for(ll i = 1; i <= n; i++) cin >> p[i].a >> p[i].h;
	for(ll i = 1; i <= k; i++) cin >> x[i];
	sort(p + 1, p + 1 + n, cmp);
	sort(x + 1, x + 1 + k);
	for(ll i = 1; i <= n; i++){      //遍历每只怪物
		ll pos = lower_bound(x + 1, x + 1 + k, p[i].a) - x;      //二分找第一个大于这只怪物坐标的地雷
		if(pos == 1){      //注意！！！要特判pos为1的情况，因为这时候左边没有地雷，不用pos-1
			if(abs(p[i].a - x[pos]) >= p[i].h) ans += p[i].h;
			else{
				ans += abs(p[i].a - x[pos]);
				if(!cnt[pos]) ans++;
				cnt[pos]++;
			}
			continue;
		}
		ll len = 0, lenl = abs(p[i].a - x[pos - 1]), lenr = abs(p[i].a - x[pos]);
		if(min(lenl, lenr) >= p[i].h) ans += p[i].h;
		else{
			if(lenl < lenr){
				len = lenl;
				if(!cnt[pos - 1]) ans++;
				cnt[pos - 1]++;
			}
			else if(lenl > lenr){
				len = lenr;
				if(!cnt[pos]) ans++;
				cnt[pos]++;
			}
			else if(lenl == lenr){      //如果距离相等，优先选择已经有怪物的地雷，可以节省引爆用的1美元
				if(!cnt[pos] && !cnt[pos - 1]) ans++;
				if(!cnt[pos - 1]){
					len = lenr;
					cnt[pos]++;
				}
				else if(!cnt[pos]){
					len = lenl;
					cnt[pos - 1]++;
				}
				else{
					len = lenr;
					cnt[pos]++;
				}
			}
			ans += len;
		}
	}
	cout << ans << "\n";
	return 0;
}
```
完结撒花！！！

---

## 作者：Whitecate (赞：1)

贪心的思路比较好想，但是细节比较多。

考虑贪心。对于第 $i$ 只怪物，我们只有两种操作，一个是将它的生命减到 $0$，代价是 $h[i]$，另一种是移到最近的地雷第 $pos$ 个，此时移动的代价是 $a[i]-x[pos]$。显然取这两个操作的最小值。

由于是引爆一次地雷会炸掉所有怪物，所以我们选择最后炸地雷。

还有一个细节。在怪物到它左右的两个地雷都相同且这两个地雷中只有一个有怪物时，我们要移动到有怪物的一个，这样可以少引爆一个地雷，少花费 $1$ 美元。

最后送给大家一句话：十年 OI 一场空，不开 long long 见祖宗。

上代码！


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
struct node
{
long long s,h;
}mon[200005];
long long x[200005];
int grid[200005];
bool cmp1(node a,node b){
    return a.s < b.s;
}
bool cmp2(int a,int b){
    return a < b;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> mon[i].s >> mon[i].h;
    }
    for(int i = 1; i <= k; i++){
        cin >> x[i]; 
    }
    sort(mon+1,mon+n+1,cmp1);
    sort(x+1,x+k+1,cmp2);
    //可以思考一下下面两行的作用。
    x[k+1] = 1e18;
    x[0] = -1e18;
    long long ans=0;
    for(int i = 1; i <= n; i++){
        int pos = lower_bound(x+1,x+k+2,mon[i].s) - x;
        int ed = min(x[pos] - mon[i].s,mon[i].s-x[pos-1]);
        if(ed >= mon[i].h){
            ans += mon[i].h;
            continue;
        }
        if(x[pos] - mon[i].s == mon[i].s - x[pos-1]){
            if(grid[pos] == grid[pos-1]){
                grid[pos] = 1;
                ans += ed;
                continue;
            }
            if(grid[pos]){
                ans += ed;
                continue;
            }
            if(grid[pos-1]){
                ans += ed;
                continue;
            }
        }
        else if(x[pos] - mon[i].s > mon[i].s - x[pos-1]){
            grid[pos-1] = 1;
            ans += ed;
            continue;
        }
        else{
            grid[pos] = 1;
            ans += ed;
            continue;
        }
    }
    for(int i = 1; i <= k; i++){
        if(grid[i]){
            ans++;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：哈哈人生 (赞：1)

# 题外话
闲得无聊写发题解。

# 思路
容易想到贪心。一个怪物被打败只有两种方式，移到地雷上引爆，或者生命值归零。地雷我们不妨留到最后引爆，这样只会花费一美元。先把地雷和怪物的位置排序。移动怪物肯定要移到左右最近的地雷上，这个可以用二分很快的知道花费。而生命值归零花费的代价一定是 $h_i$ 美元。对于每个怪物可以分开算花费，如果生命值归零的代价最小，那就用生命值归零的方法打败这个怪物。否则用移动的方式，移动可以左右两个方向，选其中的代价小的方向去移。其代价别忘了最后还要算上引爆的那个花费一美元。当然，如果这个已经地雷已经引爆过了就不用算了，因为我们可以把地雷最后才引爆，这个要用数组标记一下。若两方向代价一样，我们选择往右移并标记引爆，因为这样对后面的怪物会少一个引爆的代价。

这题看起来贪心很多种情况，实则仔细想想会发现有许多种情况是无论采用哪种击败怪物的方式花费是一致的，可以任意选择。我上面所说的贪心方案只不过是把那些不得不慎重选择的情况说出来罢了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct A{
	int wz,xl;
}a[200005];
bool cmp(A a,A b){
	return a.wz<b.wz;
}
int n,k,x[200005],b[200005];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i].wz>>a[i].xl;
	for(int i=1;i<=k;i++)cin>>x[i];
	sort(a+1,a+n+1,cmp);
	sort(x+1,x+k+1);
	int ans=0;
	for(int i=1;i<=n;i++){
		int y=lower_bound(x+1,x+k+1,a[i].wz)-x,u=1e18,v=1e18;
		if(y<=k){
			u=x[y]-a[i].wz;
			if(!b[y])u++;
		}
		if(y-1>=1){
			v=a[i].wz-x[y-1];
			if(!b[y-1])v++;
		}
		if(a[i].xl<min(u,v))ans+=a[i].xl;
		else if(u<=v)b[y]=1,ans+=u;
		else b[y-1]=1,ans+=v;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：haoyan1103 (赞：1)

很明显的贪心题。
## 思路
首先题目给了三种操作：
- 将一只怪物向左或向右移动 $1$ 个单位距离。
- 减少一只怪物的生命值 $1$。
- 引爆地雷。

每次操作的代价是 $1$ 美元。

那么贪心我们只需要考虑两种情况取最小值：
- 将一只怪物移到离它最近的地雷，引爆地雷。
- 直接将怪物杀死。

我们可以将所有怪物移到地雷后一起引爆。

再用二分查找，寻找离它最近的地雷。

最后统计答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,ans=0;
struct node
{
	int a,h;
}num[200005];
int x[200005];
bool t[200005];//记录地雷上有没有怪物
bool cmp(node x,node y){return x.a<y.a;}
signed main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>num[i].a>>num[i].h;
	for(int i=1;i<=k;i++)cin>>x[i];
	sort(num+1,num+n+1,cmp);//排序后才能贪心,二分
	sort(x+1,x+k+1);
	for(int i=1;i<=n;i++)
	{
		int id=lower_bound(x+1,x+k+1,num[i].a)-x;//二分
		int l,r;
		(id>=2?l=num[i].a-x[id-1],l+=(!t[id-1]):l=1e18);//怪物离左边地雷的距离
        (id<=k?r=x[id]-num[i].a,r+=(!t[id]):r=1e18);//怪物离右边地雷的距离
		if(num[i].h<min(l,r))ans+=num[i].h;//直接将怪物杀死
		else if(r<=l)ans+=r,t[id]=1;//离右边地雷近
		else ans+=l,t[id-1]=1;//离左边地雷近
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Davis1 (赞：0)

第一眼看见题目，就知道杀死一只怪物有两种方案，一是原地扣血而死，另一种就是带到炸弹上引爆炸弹而死，而我们怎么弄死一只怪物，对于其它的怪物没有影响（顶多就是节省一个引爆炸弹的钱），所以我们（~~自然~~）就想到了：**贪心**。

首先是原地流血致死，花的钱就是怪物的血量。

然后是带到炸弹上炸死，有两部分费用：一是使它走到炸弹上用的钱，二是引爆炸弹的钱。引爆炸弹的钱是一美元，但是看到多个怪物可以一次炸死，我们就可以贪一下引爆炸弹的钱，只要在某一个炸弹第一次被踩到时添加引爆炸弹的钱，后面的怪物踩到就不用花这个冤枉钱了（因为后面的怪物可以跟前面的一起炸，只要保证有花引爆钱就行了，不用管什么时候花的）。但是一个怪物左右两边与它相邻的炸弹最多有两个（其它不与它相邻的肯定不优，不考虑），要走到哪一个呢？肯定是比较一下带到它们那里引爆的费用，取最小的就行了。注意两点，一是有的怪物可能只有一个炸弹与它相邻（那就是在最左边那个炸弹的左边或最右边炸弹的右边时）；二是每当确定要把一个怪物带到某个炸弹上时，要考虑要不要加引爆钱，也就是这个炸弹上是否已经有怪物了。

然后把答案加上这两种答案的最小值就行了。

然后，你就发现了，计算第二种方案时，某一个怪物左右两边相邻的炸弹位置怎么找？遍历的话看数据点有点悬，所以再找方法。找右边那个炸弹其实就是在找**第一个坐标大于等于这个怪物的坐标**的炸弹，然后~~灵光一现~~就想到了二分（即 [lower_bound 函数](https://blog.csdn.net/weixin_45031801/article/details/137544229)）。。。怎么想到的先别管，先看代码。


```cpp
#include<bits/stdc++.h>
#define int long long//开long long 
using namespace std;
const int N=250001;
int n,k;
struct mon{//怪物信息 
	int a,h;//a是位置，h是血量 
} m[N];
int x[N];//地雷位置 
bool ha[N];//d[i]=1表示第i个地雷已经有怪物了 
int ans;
int cmp(mon x,mon y){
	return x.a<y.a;
}
signed main(){
	cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>m[i].a>>m[i].h;
	for(int i=1; i<=k; i++) cin>>x[i];
	sort(x+1,x+1+k);
	sort(m+1,m+1+n,cmp);
	//二分要排序 
	for(int i=1; i<=n; i++){
		int now=m[i].a,last=lower_bound(x+1,x+1+k,now)-x;
		//now是现在怪物的位置，
		//last是第一个坐标大于等于这个怪物的坐标的地雷的编号，用lower_bound函数可以简化代码
		int zha,kou=m[i].h;
		//zha是用地雷炸死的总费用，kou是原地扣血致死的费用
		if(last==1){//特殊情况，只有一个炸弹与它相邻 
			zha=(!ha[1])+abs(x[1]-now);
			//炸死的费用是这个炸弹到这个怪物的距离，如果之前这个炸弹好没有怪物，就＋1（引爆的费用，即！ha[1]） 
			ha[1]=(zha<=kou)?1:ha[1];
			//如果炸死的费用更优，就说明要把怪物带到这个炸弹上炸死，那么这个炸弹上就有了怪物了，ha数组要改变，如果选扣血致死则不变 
			ans+=min(zha,kou);//答案加上最优方案 
			continue;
		}
		int left=last-1;//left表示左边相邻的这个炸弹的编号，就是右边相邻炸弹的编号-1 
		int near=(abs(now-x[left])+(!ha[left]))<(abs(x[last]-now)+(!ha[last]))?left:last;
		//near表示带到第near个炸弹上炸死的费用更少 
		zha=(!ha[near])+abs(now-x[near]);
		ha[near]=(zha<=kou)?1:ha[near];
		ans+=min(zha,kou);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：F_L_Bird (赞：0)

# P12015 题解

## 一、总体思路

读题后不难想到该题是贪心题，明显，对于每一只怪兽，考虑两种操作：直接将其消灭或者将其放到地雷上再引爆地雷。

明显，对于一只怪兽来说，只需要考虑离他最近的两颗地雷，其他的选择很明显都是不更优的，证明如下：

如果存在一个策略，需要将怪兽（不妨称该怪兽为 A）移动到更远的距离（不妨称该策略为 $P$），那么这个策略的唯一优势是将 A 移动到另一个地雷处与其他怪兽一起击杀。但是移动得更远意味着需要更多的花费，哪怕只需要移动一次就可以将 A 移动到另一个地雷处，击杀他的代价也一定不会下降。

对于其他的怪兽，完全可以为了这些怪兽多引爆一个炸弹，此时该策略相对于 $P$ 一定不劣。

所以，这题的大致思路就是贪心的处理掉每一只怪兽，计算击杀每只怪兽的代价之和即可。

## 二、代码细节

如果你看了思路后写的代码交上去花花绿绿，那么以下细节需要注意：

首先，应该对怪兽和地雷都进行排序，在选择的时候如果遇到两颗地雷的距离都相同且两颗地雷上都没有另外的怪兽时，将怪兽放到后面的地雷一定不劣。

证明也很简单，如果两个地雷上都没有其他的怪兽而前面的怪兽已经处理过的话，将怪兽放到后面的地雷会为剩下怪物的处理省下一点代价（哪怕不省也肯定不亏的嘛）。

最后，本题值域较大，记得开 Long Long。

## 三、标程（尽量别看，自己的才是最好的）

码风较为臃肿，各位大佬轻喷 QAQ。


```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

bool boom[200005];		//标记第i颗地雷是否要被引爆
int n,k,x[200005];		//x[i]记录第i颗地雷的位置
const int INF = 0x3f3f3f3f,NEINF = INF * -1;

struct Monster{			//定义表示怪兽的结构体
	int a,h;
	bool operator < (const Monster &m) const	//定义“小于”运算符方便排序
	{
		return a < m.a;
	}
}monster[200005];		//记录第i只怪兽的位置和血量

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	for(int i = 1;i <= n;i += 1)
	{
		cin>>monster[i].a>>monster[i].h;
	}
	for(int i = 1;i <= k;i += 1)
	{
		cin>>x[i];
	}
	sort(x + 1,x + 1 + k);		//对怪兽和地雷进行排序
	sort(monster + 1,monster + 1 + n);
	int cost1,cost2,cost3,pos1,pos2;	//三个cost分别表示直接击杀、引到左边地雷、引到右边地雷的代价，两个pos表示前后地雷的下标
	long long ans = 0;
	for(int i = 1;i <= n;i += 1)
	{
		pos1 = upper_bound(x + 1,x + 1 + k,monster[i].a) - x - 1;	//upper_bound找出第一个位置在第i只怪兽右边的地雷，减一表示在该怪兽左边的地雷
		pos2 = pos1 + 1;
		cost1 = monster[i].h;
		cost2 = (pos1 == 0 ? INF : abs(x[pos1] - monster[i].a) + !boom[pos1]);	//如果左边/右边没有地雷就将代价设为正无穷，同时考虑引爆地雷的价值
		cost3 = (pos2 == k + 1 ? INF : abs(x[pos2] - monster[i].a) + !boom[pos2]);
		if(cost3 <= cost2 && cost3 <= cost1)		//处理哪些地雷要被引爆，优先引爆右边的地雷
		{
			boom[pos2] = true;
		}
		else if(cost2 <= cost3 && cost2 <= cost1)
		{
			boom[pos1] = true;
		}
		ans += min(cost1,min(cost2,cost3));		//计算价值
	}
	cout<<ans;		//输出
	return 0;
}
```

到此完结撒花 ✿✿ヽ(°▽°)ノ✿

---

