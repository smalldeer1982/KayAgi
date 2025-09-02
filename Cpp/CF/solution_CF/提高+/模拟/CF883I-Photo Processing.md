# Photo Processing

## 题目描述

Evlampiy has found one more cool application to process photos. However the application has certain limitations.

Each photo $ i $ has a contrast $ v_{i} $ . In order for the processing to be truly of high quality, the application must receive at least $ k $ photos with contrasts which differ as little as possible.

Evlampiy already knows the contrast $ v_{i} $ for each of his $ n $ photos. Now he wants to split the photos into groups, so that each group contains at least $ k $ photos. As a result, each photo must belong to exactly one group.

He considers a processing time of the $ j $ -th group to be the difference between the maximum and minimum values of $ v_{i} $ in the group. Because of multithreading the processing time of a division into groups is the maximum processing time among all groups.

Split $ n $ photos into groups in a such way that the processing time of the division is the minimum possible, i.e. that the the maximum processing time over all groups as least as possible.

## 说明/提示

In the first example the photos should be split into 2 groups: $ [40,50] $ and $ [110,120,130] $ . The processing time of the first group is $ 10 $ , and the processing time of the second group is $ 20 $ . Maximum among $ 10 $ and $ 20 $ is $ 20 $ . It is impossible to split the photos into groups in a such way that the processing time of division is less than $ 20 $ .

In the second example the photos should be split into four groups, each containing one photo. So the minimal possible processing time of a division is $ 0 $ .

## 样例 #1

### 输入

```
5 2
50 110 130 40 120
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4 1
2 3 4 1
```

### 输出

```
0
```

# 题解

## 作者：moosssi (赞：5)

这道题看题中说的：最大价值最小，就可以知道要用二分，每次二分出来一个 $mid$ 判断是否满足条件即可，主要的是怎样去判断

首先因为题目只要求分组，不需要具体方案，可以将输入的数排序，然后定义一个 $f[i]$ 存的是前 $i$ 个数能满足条件的最后一个数的位置，那么只需判断  $f[n]$ 是否等于 $n$ 

如何转移：从前往后枚举，因为要求每组至少 $m$ 个数，对于当前的第 $i$ 个数，要使每个数都明确得分到一个组，看 $f[i-m]$ 存的前一位，即没分到组的第一个数，如果 $a[i]-a[t+1]$ 小于 $mid$ 则可以分为一组更新 $f[i]=i$ (具体见代码）


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,a[N],ans,f[N];
bool check(int x){
	memset(f,0,sizeof(f));
	int pos=0;
	for(int i=m;i<=n;i++){//从m开始要满足每组至少m个数 
		int t=f[i-m];  
		if(a[i]-a[t+1]<=x)pos=i;//这里需要自己认真体会 
		f[i]=pos;
	}
	if(f[n]==n)return 1;
	else return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);//排序 
	int l=0,r=a[n]-a[1];//注意左右端点 
	while(l<=r){//二分板子 
		int mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：zythonc (赞：4)

~~才30万的数据怎么能阻挡我们n^2的算法~~

看到数据先排除 $O(n^2)$ 算法

考虑这道题让我们求什么

将 $n$ 个数分成 $t$ 组，每组物品数不得少于 $m$ 个，问每组里最大的数减去最小的数的最大值最小可能是多少

如果我们可以将这道题转化为：**给定一个值，让我们求能否有合法的解决方案满足条件**，那么我们可以做到线性复杂度，但是我们并没有这个值

所以啥算法可以通过不断地限制值来得到答案呢？

**二分**

接下来讲讲线性check算法

我们设 $dp[i]$ 表示位置在 $i$ 之前的数包括 $i$ 是否可以找到一个合法的分组方案

因为我们只要找到合法的分组方案，不用关心它具体是怎么分的，所以这里用滑动窗口来维护

然后只要 $dp[n]=1$ 就可以了

具体可以看代码注释

```
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 300100
using namespace std;
int v[N],dp[N],deq[N],n,m,l,ql,qr,i;
inline bool check(int v){
	l=1,ql=0,qr=0;
	dp[0]=1;
//初始化
	for(i=1;i<=n;++i){
		dp[i]=0;
//check函数会被多次调用，所以先重置
		if(i-m>=0&&dp[i-m]) deq[qr++]=i-m;
//if防止数组下标为负，因为每组至少有m个
//所以i-m+1 ~ i这段区间里的值并不能转移
		while(::v[i]-::v[l]>v) l++;
//通过值来限制左指针
		while(deq[ql]+1<l&&ql<qr) ql++;
//只要ql<qr，就说明区间内有位置o满足dp[o]=1
		if(ql<qr) dp[i]=1;
//转移
	}
	return dp[n];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;++i) cin>>v[i];
	sort(v+1,v+n+1);
	int l=0,r=v[n]-v[1],mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	if(check(l)) cout<<l;
	else cout<<l+1;
}
```

---

## 作者：_Felix (赞：3)

### 题意
给出 $n$ 个数，让你分组，每组最少 $m$ 个
规定每组的价值是组里面最大数-最小数 要求使得最大价值最小
$n,m\le3\times 10^5$

### 分析

容易想到二分最大价值。这是一只log的，关键是如何将 check 控制在 $O(n)$

容易想到 $O(n^2)$ 的dp来check

先把a从小到大排序，之后
$f_i|=f_j \ (j\in [0,i-m])$

---

可以证明，每次转移 $f_i$ 的 $j$ 是单调递增的。

证明：

1. 求 $f_{i-1}$ 在 $[0,i-1-m]$ 找不到 $f_j=1$ ，就直接在$[i-m,i-m]$ 找即可。（之前的已经找过了，而且也不会发生 $a_i-a_j\le mid$ 而 $a_{i-1}-a_j> mid$的情况。）
2. 对于求 $f_{i-1}$ 的时候找到的第一个 $f_j=1$，直接继续在 $[j,i-m]$ 找。（之前的已经找过了，而且也不会发生 $a_i-a_j\le mid$ 而 $a_{i-1}-a_j> mid$的情况。）

所以用一个 $pl$ 维护上一次转移扫到的地方，就可以保证 $O(n)$

---

总复杂度 $O(n\log n)$

```cpp
bool check(int x){
    memset(f,0,sizeof(f)); f[0]=1;
    int pl=1,pr;
    for(int i=1;i<=n;i++){
        while(a[i]-a[pl]>x) pl++;
        pr=i-m+1;
        for(int j=pl;j<=pr;j++){
            if(f[j-1]){
                f[i]=1; break;
            } else pl++;
        }
    }
    return f[n];
}
```

---

## 作者：__stick (赞：1)

# 题意
给出 $n$ 个数，要求将它们分成若干组，要求每一组的个数不小于 $k$ ，每组的权值为组内数最大值减最小值问所有组权值的最小值是多少。

# 思路

不难想到排序，因为想要最小化每组中的最小值，那每组中的数必然是挨着的，比如 $5$ 个数被分为 $[1,3][4,5][9]$ ，假设我们交换了$3,5$ 必然造成两个组的权值都增加，这明显是不优的，因此我们只需要考虑连续区间即可，减少了难度。

然后看着题干中最大值最小这几个字又在暗示我们使用二分（几乎都是），我们试着二分答案，二分这个最大的权值  $mid$，问题就简单化了，现在就要判断能否在满足当前最大差值的情况下分组。

定义 $F_i$ 表示区间 $[1,i] $ 内的数能否合法分组，$n$ 个数分别为 $a_1,a_2,\cdots,a_n$，看看如何转移。我们需要在区间 $[0,i-k]$ 之间找到一个合法的分组，即 $F_j=1$ 并且 $a_i-a_{j+1} \le mid$ 如果有那就说明合法，如果找不到，那就说明不合法。但这样复杂度是 $O(nk)$ 的，不能接受。

再想一想，由于数组 $a$ 是单调的，即 $a_i \le a_i+1,
i\in[1,n-1]$ 那对于当前决策点 $i$ 我们发现 $j$ 这个位置是最靠前的满足要求位置，那对于下一个决策点 $i+1$ 来说，小于等于 $j$ 的决策点一定不合法，因为 $a_i-a_j>mid,a_{i+1} \ge a_i$ ，两室相加可得 $a_{i+1} \ge a_j$ 因此 $a_{j+1} $ 一定是最靠前的可能满足 $i+1$ 决策点的位置，因此我们维护一个指针 $l$ 表示当前决策点最靠前的合法位置在哪，然后每次这个 $l$ 都是只增不减的，所以可以做到 $O(n)$ 判断是否合法。

所以我们就在 $O(n \log n )$ 的时间内解决了问题。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=3e5+10;
int a[MAXN];
bool F[MAXN];
int n,m;
inline bool pd(int x)
{
	F[0]=1;
	fill_n(F+1,n,0);
	int l=1,r=0;
	for(int i=1;i<=n;i++)
	{
		while(a[i]-a[l]>x)l++;
		r=i-m+1;
		while(!F[l-1]&&l<=r)l++;
		if(l<=r)F[i]=1;//若果不是因为 l>r 退出的则说明找到了一个合法的 F[l]  
	}
	return F[n];
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	int l=0,r=1e9,mid,ans;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(pd(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

首先，考虑一种比较裸的O(n^2)思路：

先把整个表变成有序表，然后就可以转移了


[思路](C:\Users\ZJW\Desktop\Luogu\无标题.png)

一维dp和O(n)转移
用dp值表示答案，用i表示dp推进的层数
任和一点的值可由上一次分组转移过来
dp 初始化为 INF 表示若不满足分组条件不能转移

[dp方程](‪C:\Users\ZJW\Desktop\Luogu\方程.png)

**dp[i] = min(dp[i],max(dp[i-k-j],A[i]-A[i-k-j+1])**

dp[i] 表示拓展到了第 i 个数  分组过程由第二层循环决定 
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 3e5+10;
#define INF 0x3f3f3f3f
 
typedef long long int ll;
 
ll A[MAXN];
ll dp[MAXN];
int n,k;
int main()
{
    scanf("%d%d",&n,&k);  
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&A[i]);
	}
    for(int i = 1;i <= n;i++) dp[i] = INF;
    sort(A+1,A+1+n);
    for(int i = 1;i <= n;i++){
    	for(int j = 0;i-k-j+1 > 0 && i-k-j+1 < i;j++){
    		dp[i] = min(dp[i],max(dp[i-k-j],A[i]-A[i-k-j+1]));//dp[i] 表示拓展到了第 i 个数分组过程由第二层循环决定 
		}
	}
	if(dp[n] != INF)printf("%lld",dp[n]);
    else printf("0");
	return 0;
}




```         
正解，看到最大值最小，则答案基本上具有单调性，可以考虑二分答案

[思路](‪C:\Users\ZJW\Desktop\Luogu\无标题2.png)

考虑增加pl和pr两个指针，使分组中的数满足最大值减最小值小于mid和且分组大小最小为k的限制，指针两个指针线性推进，这样就可以使其二分过程是线性的
这就可以降为O(nlogn)的复杂度


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long 
using namespace std;
const int MAXN = (int)3e5+10;
#define INF 0x3f3f3f3f

ll A[MAXN];
ll dp[MAXN];
int n,k;
ll l,r;
bool check(int mid){
	for(int i = 1;i <= n;i++){dp[i] = 0;}
	dp[0] = 1;
	int pl = 1,pr;
	for(int i = 1;i <= n;i++){
		while(A[i] - A[pl] > mid) pl++;
		pr = i - k + 1;
		for(int j = pl;j <= pr;j++){
			if(dp[j - 1]){
				dp[i] = 1;
				break;
			}
			else pl++;//千万不要忘了加 
		}
	}
	//for(int i = 1;i <= n;i++) printf("%d ",dp[i]);
	//printf("\n");
	return dp[n];
}

int main()
{
    scanf("%d%d",&n,&k);  
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&A[i]);
        r = max(A[i],r);
	}
    for(int i = 1;i <= n;i++) dp[i] = INF;
    sort(A+1,A+1+n);
	while(l <= r){
		int mid = (l + r) / 2;
		if(check(mid)){r = mid - 1;}
		else{l = mid + 1;}
	}
	printf("%lld",l);
	return 0;
}



       
```             

---

## 作者：Arghariza (赞：0)

~~推销自己的 [dp记录](https://www.luogu.com.cn/blog/EnderLittleBlog/stupidDP)~~

原题链接 : [CF883I Photo Processing](https://www.luogu.com.cn/problem/CF883I)

Difficulty : 1900

~~真就每次二分都写挂呗。~~

最大价值最小，考虑二分答案。

把 $a_i$ 从小到大排序的话，你会发现你选的组一定是连续的，不然不优。

于是令 $dp_i$ 表示仅考虑 $1$ 到 $i$ 一共 $i$ 个数是否有可行的分组。

那么 $dp_i\gets dp_{j}(j\in\{0,1,...,i-m\},a_i-a_{j+1}\le \lim)$。

$lim$ 即为你二分的答案。

但这样显然过不了，考虑优化，首先你发现最小的 $j$ 使得 $a_i-a_j\le\lim$ 是单调不降的，$j$ 的上限也是单增的，滑动窗口即可。

就是搞一个双向队列，如果 $dp_{i-m}$ 为 `true` 的话就从右边加进来 $i-m$，然后一直弹出左边不符合的（即不满足 $a_i-a_{j+1}\le lim$），最后如果队列里面还剩下可以转移的位置那么 $dp_i=1$ 了。

由于左指针的移动次数最多 $O(n)$，所以 check 的复杂度是 $O(n)$ 的。

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 3e5 + 300;
int n, m, l, r, ans, a[maxn], dp[maxn], q[maxn];

bool check(int lim) {
    int hd = 1, tl = 0, p = 1;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i - m >= 0 && dp[i - m]) q[++tl] = i - m;
        while (a[i] - a[p] > lim) p++;
        while (q[hd] + 1 < p && hd <= tl) hd++;
        if (hd <= tl) dp[i] = 1;
    }
    return dp[n];
}

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    sort(a + 1, a + n + 1);
    l = 0, r = a[n] - a[1];
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    write(ans);
    return 0;
}
```

---

## 作者：_edge_ (赞：0)

这题目是思维的 DP。

首先有一种纯粹的 $O(n^2)$ 的 DP，我想不出什么可以优化的地方。。

就是 $f_i$ 表示当前是以 $i$ 为结尾的分组最大值最小为多少，然后暴力枚举最后一组就可以了。

这好像并不是正解 (

我们考虑 最大值最小 的性质，显然可以得到越大，就越容易满足。

由此我们考虑二分这个答案。

然后你会发现这个 check 里面的东西也是一个 $O(n^2)$ 的 DP ，但相比之前的要稍微简化一点。

状态就是 $f_i$ 表示以 $i$ 为结尾的分组，是否满足条件。

然后我们枚举 $j$，范围是 $0 \le j \le i-m$，这里可能会有一点小小的偏差。

然后我们会发现这个 $a$ 序列肯定是从小到大排最优。

于是最大值减去最小值即为 $a_i - a_{j+1}$，若满足条件那么就是 $a_i - a_{j+1} \le x$，然后，然后我们又发现，这个 $j$ 是有单调性的。

什么意思呢？就是说当你这个 $i$ 增加的时候，如果你这个 $j$ 不变，那么你是有可能不符合的，至少你是不可能更优的。

于是我们发现这个 $j$ 它其实具有单调性，就是你当前 $f_i$ 是成立的，那么你 $f_{i+1}$ 必定是从一个大于等于 $j$ 的地方转移过来。

由此我们可以使用双指针来维护，注意当前第一组我进行的特殊的处理。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int INF=3e5+5;
int n,m,a[INF],f[INF];
bool check(int xx) {

        // f[0]=1; int l=0;

        for (int i=1; i<=n; i++)
                f[i]=0;
        for (int i=m; i<=n; i++)
                if (a[i]-a[1]<=xx) f[i]=1;
        int l=1;
        for (int i=m; i<=n; i++) {
                int r=i-m+1;
                // cout<<a[i]-a[l]<<"\n";
                while (a[i]-a[l]>xx && l<=r) l++;
                for (; l<=r; l++)
                        if (f[l-1]) {f[i]=1; break;}
                // cout<<l<<" "<<r<<" "<<i<<" "<<xx<<" "<<f[i]<<"\n";
                // int l=0,r=i-m;
                // for (int j=l; j<=r; j++)
                //         if (a[i]-a[j]<=xx) f[i]|=f[j];
                // 40 50 110 120 130
        }
        return f[n];
}
signed main()
{
        scanf("%lld %lld",&n,&m);
        for (int i=1; i<=n; i++)
                scanf("%lld",&a[i]);
        sort(a+1,a+1+n);
        // cout<<check(20)<<"\n";
        int l=0,r=2e9,ans=0;
        while (l<=r) {
                int Mid=(l+r)>>1;
                if (check(Mid)) r=(ans=Mid)-1;
                else l=Mid+1;
                // cout<<l<<" "<<r<<"\n";
        }
        cout<<ans<<"\n";
        return 0;
}

```

如有问题还请指出。

---

