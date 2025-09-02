# [POI 2014] ZAL-Freight

## 题目描述

The train stations in Upper Bytown and Lower Bytown are connected with a single track rail link.

It takes the train $s$ minutes to travel between them in either direction.

However, the trains departing a station have to be spaced at least one minute apart.

Moreover, at all times, all the trains on the rail link have to go in the same direction.

According to the timetable at our disposal, $n$ cargo trains destined for Lower Bytown are to pass  through the Upper Bytown.  They are to be loaded with goods in Lower Bytown and then return to  Upper Bytown.  For simplicity, we assume that loading the goods on the train takes virtually no time.

We are to determine the minimum possible time of the last train returning to Upper Bytown.

有两个城镇，从A到B需要的时间为S，然后有N辆列车需要从A到B再回来，任何时刻铁路上只能有向着同一个方向前进的列车，然后每辆列车有一个从A出发的最早出站时间，问所有列车全部回到A站的最早时间


## 说明/提示




## 样例 #1

### 输入

```
3 4
1 8 11
```

### 输出

```
20
```

# 题解

## 作者：Treaker (赞：7)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 单调队列优化DP
对于这道题，我们考虑最优的情况是什么，一定是一波过来，一波回去；再一波过来，一波回去。

那么我们来设计一下DP方程。。

设$f[i]$表示第$i$辆车所属的那波回去的最早时间，则有

$$f[i] = min(max(a[i],f[j] + i - j - 1) + 2 * S + i - j - 1)$$

转移是$O(n^2)$的，怎么优化呢，单调队列。

考虑拆掉$max$,

当$f[j] + i - j - 1 >= a[i]$时，移项得$f[j] - j >= a[i] - i + 1$，判断这个即可，单调队列维护什么呢，这种情况的值为$f[j] + i - j - 1 + 2 * S + i - j - 1$，但是$i - 1 + 2 * S + i - 1$在$i$一定时，是固定的，只需要维护$f[j] - 2 * j$即可。

另一种情况$f[j] + i - j - 1 < a[i]$，在你维护情况1弹出去的时候，就是这种情况。维护什么呢？$a[i] + 2 * S + i - j - 1$，维护$-j$，即可，也就是找那个最晚被弹出去的就行。


完整代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000005;
inline int read()
{
    int x = 0 , f = 1;  char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-')  f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}
int n , S , last , ans , head = 1 , tail;
int q[N << 1];
ll f[N] , a[N];
int main()
{
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	n = read(); S = read(); memset(f,0x3f,sizeof f);
	for(int i = 1;i <= n;i ++) a[i] = (long long)read();
	sort(a+1,a+1+n); a[0] = -1;
	for(int i = 1;i <= n;i ++) a[i] = max(a[i],a[i-1] + 1);
	for(int i = 1;i <= n;i ++)
	{
		while(head <= tail && f[q[head]] - q[head] < a[i] - i + 1) head ++;
		f[i] = min(f[i],a[i] + 2 * S + i - q[head-1] - 1);
		f[i] = min(f[i],f[q[head]] + 2 * (S + i - q[head] - 1));
		while(head <= tail && f[q[tail]] - 2 * q[tail] > f[i] - 2 * i) tail --;
		q[++tail] = i;
	}
	printf("%lld\n",f[n]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```


---

## 作者：FriedrichC (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P3580)

神仙 dp 题，蒟蒻做不出来。

十分典型的单调队列优化 dp，很好展现了这类可用单调队列优化的**序列 dp** 的性质。

## 题目性质分析
考虑问题的两条性质，我们可以简化问题：

假如我们从 $A$ 处发出了若干辆车，但是在它们都到达 $B$ 处之后，只让一部分车回来，然后再让剩下的车出发，

包括先前没回来的部分，最后所有的车也一并都要**依次回来**；

考虑发出多少车，就回来多少车的方案，相比于上述方案，先发的车先回来节约的时间，与后发的车多等待消耗的时间相互抵消，并没有让总时间增加，这就说明这两种方案是**等效**的方案，

因此，我们就可以只考虑后者，这样我们的问题就得到简化，也更容易设计状态。

## 状态设计
设 $f[i]$ 表示前 $i$ 辆车，分成若干批次往返后，**最晚回来**的列车的到达 A 处所用的**最少时间**。

我们可以画图来理解这个问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/uxwdg8pb.png)

如图，$A$ 和 $B$ 分别为到达两地的时间轴，$j$ 位置表示第 $j$ 辆车回到的时间戳，$i$ 位置表示第 $i$ 辆车发车的时间戳，$i^{\prime}$ 表示其回到的时间戳。

考虑 $i$ 的发车时间戳，$i$ 与 $j$ 之间**间隔**了 $i-j$ 辆车（包括 $i$ 自己），

由于 $j$ 回到后的**第 $0$ 时刻**就可以发新的车，又因为间隔一个单位时间就可以发一辆车，那么 $i$ 的理想发车时间戳就比 $j$ 的回到时间戳晚了 $i-j-1$ 个单位，

当然，每辆车都有其最早发车时间的限制，因此要和 $t[i]$ 取最大值。

再考虑 $i$ 的回到时间戳，对于任意一辆车，在 $A$ $B$ 之间往返的时间为 $2\times s$，同理，由于在 $B$ 等待发车时也要遵循间隔一个时间单位**顺序发车**的限制，因此 $i$ 的回到时间戳还要再晚 $i-j-1$ 个单位。

因此我们有状态转移方程：

$$f[i]=\min\{\max(t[i],f[j]+i-j-1)+2\times s+i-j-1\}$$

直接转移显然复杂度为 $O(N^2)$ 不可接受，接下来思考怎么优化。

## 转移优化
考虑转移方程的性质，在 `max` 函数中，$t[i]$ 和 $i$ 在当前转移的这轮是**定值**，$j$ 或 $f[j]$ 是需要我们不断维护的**变量**。

于是考虑将 `max` 函数分解，即分为 $t[i]>f[j]+i-j-1$ 和 $t[i]\leq f[j]+i-j-1$ 两种情况，

整理一下得到：

$f[i]=\begin{cases}\min\{t[i]+2\times s+i-j-1\} & t[i]-i+1>f[j]-j \\ \min\{f[j]+2\times (s+i-j-1)\} & t[i]-i+1\leq f[j]-j\end{cases}$

只保留变量化简得：

$f[i]=\begin{cases}\min\{-j\}+t[i]+2\times s+i-1 & t[i]-i+1>f[j]-j \\ \min\{f[j]-2\times j)\}+2\times (s+i-1) & t[i]-i+1\leq f[j]-j\end{cases}$

输入格式中写明了 $t[i]$ 的序列是**单调不降**的，又由于每辆车必须间隔一个单位时间发车，所以每辆车的 $t[i]$ 等效于 $max(t[i],t[i-1]+1)$。

做了这样一个转换后，就能保证 $t[i]-i$ 也是**单调不降**的，那么每轮转移枚举 $i$ 时，$t[i]-i$ 就在一个**单调的序列上增长**，

类似的，显然 $f[j]-j$ 也是**单调不降**的，所以我们要维护的是**连续**的一段**最值**，于是我们就可以使用**单调队列**。

具体而言，要应用单调队列，就要先把问题转换成**类滑动窗口**的问题，假如我们认定需要维护的 $f[j]-j$ 的“窗口”是**大于**等于 $t[i]-i+1$ 的区间，那我们**队首元素**弹出队列的条件就确定了。

根据我们化简后的转移方程，我们的单调队列要维护的值就是 $f[j]-2\times j$，并且维护的是一个**单调减**的队列。

那么第一种情况，也就是 $f[j]-j$ 更小的情况的转移要怎么完成呢？

其实我们每轮因不满足条件而弹出的**队首元素**就都是满足这种情况的元素，于是我们用**最后一个**弹出的队首元素更新这种情况下的 $f[i]$。

之所以用最后一个弹出的元素，是因为既然我们用了单调队列来维护，那么**最靠近队头**的元素肯定是转移的**最优解**，因此最后一个弹出的元素和当前的队首元素就分别是方程中两种情况转移的最优解。

需要说明的是，在第一种情况中，我们本来要维护的是 $-j$ 而不是 $f[j]-2\times j$，但是由于 $f[j]-2\times j$ 是**随着** $j$ 的单调变化而单调的，因此维护了 $f[j]-2\times j$ 的单调性就等效于维护了 $-j$ 的单调性。

应用了单调队列优化后，原先枚举 $j$ 的 $O(N)$ 复杂度均摊为 $O(1)$，于是总复杂度由 $O(N^2)$ 降为 $O(N)$。 
## 附上代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 1000010
using namespace std;
int q[maxn],l=1,r,f[maxn],t[maxn];
signed main()
{
    int n,s;
    cin>>n>>s;
    for(int i=1;i<=n;++i)cin>>t[i];//输入保证t[i]单调
    memset(f,0x3f,sizeof(f));
    t[0]=-1;
    for(int i=1;i<=n;++i)t[i]=max(t[i],t[i-1]+1);//保证每辆车发车间隔一秒
    for(int i=1;i<=n;++i)
    {
        while(l<=r && f[q[l]] - q[l] < t[i] - i + 1)l++;
        while(l<=r && f[q[r]]- 2 * q[r] > f[i] - 2 * i)r--;
        f[i]=min(f[i],t[i] + 2 * s + i - q[l-1] - 1);
        f[i]=min(f[i],f[q[l]] + 2 * ( s + i - q[l] - 1));
        q[++r]=i;
    }
    cout<<f[n]<<endl;
	return 0;
}

```

## 小结
本题已经充分体现了许多可以用单调队列优化的序列问题的特点：

- 转移的对象在枚举或更新时是**单调变化**的。

- 转移的来源在单调变化的**固定长度或性质**的区间。

- 需要维护的是转移来源的**最值**。

- ......
































---

## 作者：lsj2009 (赞：4)

至今没搞懂这个题为什么要单调队列……感觉这个题的题解写得都有些【数据删除】。

感觉说这题要有单调队列优化的题解都没搞清楚这题本质。

首先有个重要结论是：火车要么不回，要么一起回。

- 证明：首先如果回来的途中没有阻碍其他火车出现，那全部回来显然更优。那如果某个火车 $i$ 回来时没有阻碍其他火车发车，但是火车 $i+1$ 回来时会阻碍到其他火车发车，则每多回来一辆车，后一辆火车多延迟发车 $1$ 分钟，但是如果留到最后再回来，也会花费 $1$ 的时间，所以让他们一次性回来必然不比先把一部分放回来，最后再全部放回来劣。

根据此，我们考虑设计状态 $f_i$ 表示 $1\sim i$ 的火车全部过去且回来的最小代价。

题目保证了 $a_i$ 单调不减，为了防止 $a_{i-1}=a_i$ 而导致如果 $i-1$ 在 $a_i$ 出发后 $i$ 没法在 $a_i$ 时刻立刻出发，我们令 $a_i=\max\{a_{i-1}+1,a_i\}$。

则易得 $f_i=\min\limits_{j=0}^{i-1}\{\max\{f_j+i-j-1,a_i\}+2\times S+i-j-1\}$。

对于转移方程中那个 $\max$ 的含义：如果说途中没有那辆车是恰好卡着 $a_k$ 或者要等到 $a_k$ 再发车的，则 $j+1\sim i$ 全部到达 B 的时间取 $a_i+S$，否则取 $f_j+i-j-1+S$。

考虑 $\max$ 拆开，变换一下形式得：

$$
f_i=\begin{cases}
 & \min\{-j\}+2\cdot S+a_i+i-1 \quad\quad f_j-j< a_i-i+1\\
 & \min\{f_j-2\cdot j\}+2\cdot(S+i-1) \quad\quad f_j-j\ge a_i-i+1\\
\end{cases}
$$

然后还有一个重要结论：$f_i\ge f_{i-1}+2$，感性理解是多了一辆车一去一回时间必然增加 $2$。

同时结合我们上面推导的东西，可以得到 $-j,f_j-2\cdot j$ 均有单调性。则得到，若 $k$ 为 $f_k-k< a_i-i+1$ 最后一个 $k$，则 $k$ 为第一种决策得最优决策点，$k+1$ 为第二种决策得最优决策点，同时因为 $f_k-k$ 和 $a_i-i+1$ 均有单调性，所以 $k$ 随 $i$ 得增大而随之增大，故而双指针即可，完全不用单调队列。

复杂度 $\Theta(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e6+5;
int f[N],a[N];
signed main() {
    int n,s;
    scanf("%lld%lld",&n,&s);
	a[0]=-1;
    rep(i,1,n)
        scanf("%lld",&a[i]),chkmax(a[i],a[i-1]+1);
    cl(f,0x3f); f[0]=0;
	int p=0;
    rep(i,1,n) {
        while(p<i&&f[p]-p<a[i]-i+1)
            ++p;
        chkmin(f[i],a[i]+2*s+i-(p-1)-1);
        if(p!=i)
            chkmin(f[i],f[p]+2*(i+s-p-1));
    }
    printf("%lld\n",f[n]);
    return 0;
}
```

---

## 作者：renhao (赞：3)

# Freight

首先题目的要点是：
1.每次铁路上只能有开往一个方向的车。
2.每次两辆车间隔发车时间至少 1 $\min$

那么考虑第一辆车开到一半，然后第二辆车可以开，那么就有两种决策
第一种是第二辆车等着，第一辆车开过来了再开过去
第二种决策就是第二辆车直接跟着，然后回来

这样显然是第二种决策更优了，这样不就是模拟了吗。
这样没有考虑到了题目的第二个限制 ,~~stupid ！！！~~
那么似乎没有优秀的贪心了，但是这个$DP$经过分析变得显然。

可以发现跟着的车是一段的，那么就可以直接转移
$$
 \min(dp[i], \max (a[i],dp[j]+i-j-1)+2 \times s+i-j-1);
$$




$dp[i],a[i]$单调递增，那么就可以直接记录一个临界点。
$\Theta(n)$转移就可以了。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
int n,s;
ll dp[N],a[N];
void Min(ll &x,ll y){
    if(x==-1||x>y) x=y;	
}
int main(){
//	freopen("freight.in","r",stdin);
//	freopen("freight.out","w",stdout);
    scanf("%d %d",&n,&s);
    a[0]=-1;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        if(a[i]<=a[i-1]){
            a[i]=a[i-1]+1;
        }
    }
    memset(dp,-1,sizeof(dp));
    int j=0;
    dp[0]=0;
    for(int i=1;i<=n;i++){
        while(j<i&&dp[j]+i-j-1<=a[i]) j++;
        
        Min(dp[i],a[i]+2*s+i-(j-1)-1);
        
        if(~dp[j]&&dp[j]+i-j-1>=a[i]) Min(dp[i],dp[j]+i-j-1+2*s+i-j-1);
    }
//	cout<<dp[2]<<endl;
    cout<<dp[n]<<endl;
    return 0;
}
```

---

## 作者：肖翔 (赞：2)

显然可以考虑 $dp_{i}$ 表示第 $i$ 个车回去需要多久。

考虑转移，枚举一个 $j$，表示从 $j+1$ 到 $i$ 的车放在同一批回。

那么则有 
$$
dp_{i}=\min\{\max(dp_{j}+i-j-1,t_{i})+2\times S+i-j-1 | 0 \le j < i \}
$$

（$t_{i}$ 更大时就等到 $t_{i}$ 时刻再转移，前面的一个一个放。不然要等到前 $j$ 个弄完了再把 $j+1$ 到 $i$ 的依次放上去）

直接做是 $O(n^2) $ 的，发现 $dp_{i} $ 与 $t_{i}$ 都具有单调性，似乎大有文章。很多同学到这里直接上了单调队列，但我比较菜，想到的是二分。

首先作小变形，把 $\min$  里面的式子变得好讨论一点。
$$
dp_{i}=\min\{\max(dp_{j}-j,t_{i}-i+1)+2\times S+2\times i-j-2 | 0 \le j < i \}
$$

（$\max$ 对加减法有分配律 ~~其实不变一样好做~~ ）

为了方便，令 $a=t_{i}-i+1,b=2\times S+2\times i-2$，可以发现对于确定的 $i$，它们都是常数。

分类讨论拆开式子:

1. 当 $a \ge dp_{j}-j$，式子变成 $a+b-j$，显然在 $j$ 最大时取得最小。
而 $dp_{j}-j$ 显然也是单调的，所以二分查找最后一个小于等于 $a$ 的 $dp_{j}-j$ 即可，后代入。

2. 当 $a < dp_{j}-j $，式子变成 $dp_{j}-2\times j+b$，可以发现 $dp_{j}-2\times j$ 也是具有单调性的。该式在 $j$ 最小时取得最小，而满足条件的 $j$ 刚好是情况 $1$ 中的 $j$ 的后一个，非常美妙，直接代入。

最后对两种情况取个最小值即可。注意处理边界，并对 $t_{i}$ 相同的情况进行处理。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
int n,dp[maxn],t[maxn],s;
inline int rd(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();	
	}
	return x*f;
}
inline int find(int x,int i){
	int l=-1,r=i,mid;
	while(l+1!=r){
		mid=l+r>>1;
		if(dp[mid]-mid<=x)l=mid;
		else r=mid;
	}
	return l;
}
signed main(){
	cin>>n>>s;
	t[0]=-1;
	for(int i=1;i<=n;i++)t[i]=max(rd(),t[i-1]+1);
	for(int i=1;i<=n;i++){
		dp[i]=0x7f7f7f7f;
		int p1=find(t[i]-i+1,i),a1=0x7f7f7f7f;
		a1=t[i]-i+1+2*s+2*i-2-p1;
		int p2=p1+1,a2=0x7f7f7f7f;
		if(p2<i)a2=dp[p2]-2*p2+2*s+2*i-2;
		dp[i]=min(a1,a2);
	}
	cout<<dp[n];
}
```


---

## 作者：xtx1092515503 (赞：2)

个人DP时想傻掉了，但是最终还是用奇妙的方式实现了这个傻掉的做法，因此发一篇题解。

------------

首先，状态非常好设，$f_i$ 表示 $i$ 以及之前的所有车次全都跑回去再跑回来的最小时间即可。

本质上是一个优化DP的过程。

我们考虑最暴力的 $O(n^2)$ DP，即从一个 $f_i$ 出发，递增地枚举 $j$，并求出此时 $i\rightarrow j$ 的最小时间（因为要满足“相邻差大于等于 $1$”的限制），然后转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,a[1001000];
ll f[1001000]; 
int main(){
	scanf("%d%d",&n,&m),memset(f,0x3f,sizeof(f)),a[0]=-1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	f[0]=0;
	for(int i=0;i<n;i++){
		ll now=f[i]-1;
		for(int j=i+1;j<=n;j++){
			now++,now=max(now,1ll*a[j]);
			f[j]=min(f[j],now+2*m+(j-i-1));
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

但是，这个DP非常令人不爽，因为我们没有办法通过什么式子直接表示出 $i\rightarrow j$ 的最小代价。

这时就要祭出一个~~不怎么常见的~~应用于题目中所述的**递增序列**的小trick了：

如果一个序列 $a$ 递增，那么 $a_i-i$ 不降。

我们考虑将其应用于上述DP：

序列 $\{f_i-1,a_{i+1},a_{i+2},\dots,a_j\}$ 递增。

减一下就发现，序列 $\{f_i-i-1,a_{i+1}-(i+1),\dots,a_j-j\}$ 不降。

于是我们只需要先把整个序列转成上述 $a_i-i$ 的形式，然后最小代价就直接取区间 $\max$ 就能得出，最后再把它恢复成 $a_i$ 的形式即可。

于是我们现在便可以有一个DP的式子了：

$$f_j=\min\limits_{i<j}\Bigg\{\max\Big\{f_i-i-1,\max\{a_{i+1},\dots,a_j\}\Big\}+2(m+j)-i+1\Bigg\}$$

虽然还是 $O(n^2)$ 的DP，但是写出式子就是一大进步。

此部分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,a[1001000];
ll f[1001000]; 
int main(){
	scanf("%d%d",&n,&m),memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]-=i;
	f[0]=0;
	for(int i=0;i<n;i++){
		ll now=f[i]-i-1;
//		printf("%d\n",now);
		for(int j=i+1;j<=n;j++){
			now=max(now,1ll*a[j]);
//			printf("%d->%d:%d\n",i,j,now);
			f[j]=min(f[j],now+j+2*m+(j-i-1));
		}
	}
//	for(int i=0;i<=n;i++)printf("%lld ",f[i]);puts("");
	printf("%lld\n",f[n]);
	return 0;
}
```

现在考虑上奇怪的东西来维护了。

我们翻出式子

$$f_j=\min\limits_{i<j}\Bigg\{\max\Big\{f_i-i-1,\max\{a_{i+1},\dots,a_j\}\Big\}+2(m+j)-i+1\Bigg\}$$

提取一些东西出来

$$f_j=2(m+j)+1+\min\limits_{i<j}\Bigg\{\max\Big\{f_i-i-1,\max\{a_{i+1},\dots,a_j\}\Big\}-i\Bigg\}$$

然后里面的东西，我们可以分情况讨论。

1. $f_i-i-1\geq\max\{a_{i+1},\dots,a_j\}$

首先，$f_i$ 肯定是单调递增的，因为多一辆车你统一回来时就要多等一秒，则 $f_i$ 至少比 $f_{i-1}$ 大一。于是 $f_i-i-1$ 便是单调不降的。

所以我们便可以用two-pointers维护第一个不满足上述条件的 $j$。于是，对于所有 $k\in(i,j)$，都有 $f_i-i-1-i\rightarrow f_k$。

考虑随着 $i$ 上升， $j$ 也是单调不降的，故此部分可以上单调队列维护。

2. $f_i-i-1<\max\{a_{i+1},\dots,a_j\}$

此处有 $\max\{a_{i+1},\dots,a_k\}-i\rightarrow f_k$。根据我们上述的总结，此部分应该作用于一个后缀 $[j,n]$。

考虑位置 $j$。显然，此处必然有 $\max\{a_{i+1},\dots,a_j\}=a_j$，不然 $j$ 不可能是第一个满足上述条件的位置。故我们可以将上述条件转为

$$\max\{a_j,\dots,a_k\}-i\rightarrow f_k$$

特别地，在 $j$ 处，上式等价于

$$a_j-i\rightarrow f_j$$

考虑在 $j$ 处开一个桶 $g$ 记录所有可以转移的最大后缀是 $[j,n]$ 的 $i$ 中，最大的一个。则必有桶中的值（假如桶中有值的话）随着 $j$ 的增大不降。

我们考虑对于位置 $j$，它还从前面继承过来一个 $\max\{a_p,\dots,a_j\}-q\rightarrow f_j$。则根据我们之前的分析，假如桶中有值，必有 $\max\{a_p,\dots,a_j\}\geq a_j$ 且 $q\leq g_j$。即，$\max\{a_p,\dots,a_j\}-q\geq a_j-g_j$。

故我们可以无条件把前面继承过来的东西换成位置 $j$ 桶中的东西。当然，如果 $j$ 中桶里是空的，当然就换不了了。

则时间复杂度 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,a[1001000],g[1001000],nowa,nowb=-1;
ll f[1001000];
deque<pair<ll,int> >q;
int main(){
	scanf("%d%d",&n,&m),memset(f,0x3f,sizeof(f)),memset(g,-1,sizeof(g));
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]-=i;
//	for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
	f[0]=-2*m+1;
	for(int i=0,j=1;i<=n;i++){
		while(!q.empty()&&q.front().second<=i)q.pop_front();
		if(!q.empty())f[i]=min(f[i],q.front().first);
		
		if(g[i]!=-1)nowa=a[i],nowb=g[i];
		nowa=max(nowa,a[i]);
		if(nowb!=-1)f[i]=min(f[i],1ll*nowa-nowb);
		
		f[i]+=2*(i+m)-1;
		ll now=f[i]-i-1;
		for(j=max(i+1,j);j<=n&&now>=a[j];j++);
//		printf("%d:%d\n",now,j);
		while(!q.empty()&&q.back().first>=now-i)q.pop_back();
		q.push_back(make_pair(now-i,j));
		g[j]=max(g[j],i);
	}
//	for(int i=0;i<=n;i++)printf("%lld ",f[i]);puts("");
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：SmileMask (赞：0)

首先将 $a_{i}$ 变为离开 Lower Bytown 的时间。

考虑到操作序列一定是：

- 让一些火车到 Upper Bytown，然后再回到 Lower Bytown，即按时间排序后将火车分为若干段。

启示我们 $dp$，不妨记 $f_{i}$ 为第 $i$ 辆列车是当前这一段的结尾，枚举上一段的结尾 $j$，转移有：
$$
f_{i}=\min\limits_{j=0}^{i-1} \max(a_i,f_{j}+i-j-1) +2\times s+i-j-1
$$
$\max$ 的部分不好确定，不妨让每一部分只含有与本身相关的变量，因此转移时可转化为：
$$
f_{i}=\min\limits_{j=0}^{i-1} \max(a_i-i+1,f_j-j)+2\times s+2\times i-j-2
$$
$f_{j}-j$ 是单调递增的的，即 $f_{j+1}-(j+1) \ge f_{j}-j \Leftrightarrow f_{j+1}\ge f_{j}+1$，这里有 $f_{j+1}\ge f_{j}+2$，因为每个列车发车时间至少间隔 $2$，显然满足条件。

所以考虑二分出决策点 $k$ 满足 $f_{k}-k \le a_{i}-i+1$，转移变成：
$$
f_{i}=\min(\min\limits_{j=0}^{k} a_i+i-1+2\times s-j,\min\limits_{j=k+1}^{i-1} f_{j}-2\times j +2\times s+2\times i+2)
$$
前者显然直接取 $j=k$，后者由于 $f_{j}-2\times j$ 是单调不降的，即 $f_{j+1}-2\times (j+1) \ge f_{j}-2\times j \Leftrightarrow f_{j+1}\ge f_{j}+2$，满足条件，所以直接取 $j=k+1$ 即可。

总复杂度是 $O(n\log n)$。

---

## 作者：0xyz (赞：0)

看见还没有二分的题解，来一发。

---

讲个笑话，我场切这道题竟然是因为学校 OJ 数据太水，不过现在改过来了。

首先发现输入的 $t_i$ 可能有相等的，由于不可能有两列火车同时发车，我们把它变得递增。

考虑 DP，令 $f_i$ 代表前 $i$ 列火车回到 U 镇的最小时间。枚举上一次所有火车都回到 U 镇的是前 $j$ 列火车，从而在 U 镇和 L 镇发车的所需要的时间都是 $i-j-1$，路上的时间是 $2s$，并且第 $i$ 列火车在 U 镇发车的时间不能早于 $t_i$，得到：
$$f_i=\min\limits_{j<i}\{\max(f_j+i-j-1,t_i)+2s+i-j-1\}$$

时间复杂度 $O(n^2)$，70pts 代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=2000005;
ll n,s,t[_],f[_],x,i,j;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;
	for(i=1;i<=n;i++)cin>>x,f[i]=1e18,t[i]=max(t[i-1]+1,x);
	for(i=1;i<=n;i++)
		for(j=0;j<i;j++)f[i]=min(f[i],max(f[j]+i-j-1,t[i])+2*s+i-j-1);
	cout<<f[n]<<'\n';
	return 0;
}
```

考虑优化。改变一下式子，有
$$f_i=\min\limits_{j<i}\{\max(f_j-j,t_i-i+1)-j\}+2s+2i-2$$

因为每增加一列火车，我们要么多跑一个来回，造成 $2s$ 的增量，要么依附于前面的火车组，在 U 镇和 L 镇发车时各有至少 $1$ 的增量，从而有 $\forall i,f_i\ge f_{i-1}+2$。所以我们知道 $f_j-j$ 单调递增且 $f_j-2j$ 单调不降。这样我们二分出使得 $f_e-e\le t_i-i+1$ 的最大的 $e$。

对于 $\le e$ 的贡献点 $j$，
$$\begin{aligned}f_i&=\min\limits_{j\le e}\{t_i-i+1-j\}+2s+2i-2\\&=t_i-i+1-e+2s+2i-2\end{aligned}$$
对于 $>e$ 的贡献点 $j$，
$$\begin{aligned}f_i&=\min\limits_{j>e}\{f_j-j-j\}+2s+2i-2\\&=f_{e+1}-2(e+1)+2s+2i-2\end{aligned}$$
于是我们就有：
$$f_i=\min(t_i-i+1-e,f_{e+1}-2(e+1))+2s+2i-2$$

时间复杂度 $O(n\log n)$，100pts 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=2000005;
ll n,s,t[_],f[_],x,i,l,r,z,e;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;
	for(i=1;i<=n;i++)cin>>x,f[i]=1e18,t[i]=max(t[i-1]+1,x);
	for(i=1;i<=n;i++){
		for(l=e=0,r=i-1;l<=r;)z=l+r>>1,f[z]-z<=t[i]-i+1?e=z,l=z+1:r=z-1;
		f[i]=min(t[i]-i+1-e,f[e+1]-2*(e+1))+2*s+2*i-2;
	}
	cout<<f[n]<<'\n';
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [P3580 ZAL-Freight](https://www.luogu.com.cn/problem/P3580)

教练说这题才蓝（？

至少是我在模拟赛中第一次做出紫题……

## 思路

一个不难得到的思路是使用 dp。

在 dp 之前，我们可以先处理一下 $t_i$ 的值。

虽然题目中有给到 $t_i \le t_{i+1}$，事实上，$t_{i+1}$ 不能等于 $t_i$。所以，我们可以在输入 $t_i$ 的时候处理一下 $t_i \gets \max\{t_i, t_{i - 1} + 1\}$。

那么对于 dp，我们可以令 $f(i)$ 表示前 $i$ 辆列车完成一个循环的用时，且假定 $f(0) = 0$。那么 $f(i)$ 一定能表示为 $\min_{j = 0}^{i - 1}g(i, j)$，其中 $g$ 是一个转移方程。

那么，我们可以令 $g(i, j)$ 表示从 $f(j)$ 递推到 $f(i)$ 的用时。那么有

$$
g(i, j) = \max_{k = j + 1}^i\{k\text{ 能开始传的时间}\} + s + (i - j) + s - 1
$$

我们可以对它化简：

$$
g(i, j) = 2s - 1 + \max\{t_i, \max_{j = 0}^{i - 1}\{f(j) + i + j - 1\}\} + i - j
$$

注意到一个比较玄学的东西，就是 $f(j) \ge 2 + f(j - 1)$。要靠感官证明（？

那么我们定义一个所谓的斜率 $k(\text{something})$。

可以发现，$k(t_i) = 0$，并且有 $k(f(j)) \ge 2$。也就是说 $k(f(j) + i + j - 1) \ge 1$。那么，我们把 $\max\{t_i, f(j) + i - j - 1\} + i - j$ 画出来后一定是一个像 V 的东西。这个 V 的底端就是我们想要的。

注意到这个底端是在 $t_i$ 和 $f(j) + i - j - 1$ 非常接近的地方（如刚好大于或刚好小于）。那么我们可以用二分把这个东西算出来，把左右的值都更新一下就可以了。

最后的答案就是 $f(n)$，时间复杂度为 $O(n\log n)$

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000006

using ll = long long;

ll dp[MAXN];

int n;

ll s;
ll t[MAXN];

int main()
{
	cin >> n >> s;
	for (int i = 1; i <= n; i++)
	{
		cin >> t[i];
		t[i] = max(t[i], t[i - 1] + 1);
		dp[i] = 1145141919810ll;
	}
	for (int i = 1; i <= n; i++)
	{
		// find the first j that dp[j] + i - j + 1 is greater than t[i]
		if (dp[i - 1] < t[i]) // it doesn't exist
		{
			dp[i] = t[i] + 2 * s;
		}
		else // it does
		{
			int l = 0, r = i - 1;
			while (l < r)
			{
				int m = (l + r) >> 1;
				if (dp[m] + i - m - 1 > t[i]) // this may be what I want
				{
					r = m;
				}
				else // this isn't
				{
					l = m + 1;
				}
			}
			dp[i] = dp[l] + 2 * (i - l - 1 + s);
			if (l)
			{
				dp[i] = min(dp[i], t[i] + 2 * s + i - l);
			}
		}
	}
	cout << dp[n] << endl;
}

```


---

## 作者：JCY_ (赞：0)

[更好的阅读体验](https://www.cnblogs.com/JCY-std/p/16985938.html)

不难发现最优方案一定是把序列划成若干段，从左到右依次每段走过去再走回来。

首先遍历 $i$ 从 $2$ 到 $n$，令 $t_i = max(t_i, t_{i - 1} + 1)$，为的是使最早出发时间满足间隔至少一秒。

不难列出 dp 方程 $dp_i = \min_{1 \le j < i} \{\max\{dp_j + i - j - 1, t_i\} + 2s + i - j - 1\}$。

考虑如何进行 dp 转移，如果没有取 max 操作即为维护 $dp_j - 2j$ 的前缀最值。

对于 $j_1 < j_2$，若 $dp_{j_1} - 2j_1 \ge dp_{j_2} - 2j_2$，则从 $j_2$ 转移一定不劣于 $j_1$。

证明：

当 $\max\{dp_j + i - j - 1, t_i\} = t_i$ 时，称 $j$ 取 max 成功。

若 $j_1,j_2$ 均取 max 成功，$-j_1 > -j_2$，所以 $j_2$ 更优。

若 $j_1,j_2$ 均未取 max 成功，$dp_{j_1} - 2j_1 \ge dp_{j_2} - 2j_2$，所以 $j_2$ 更优。

若 $j_1$ 成功而 $j_2$ 未成功，$j_1$ 取 max 前已经劣于 $j_2$，取 max 只会更劣，所以 $j_2$ 更优。

若 $j_1$ 未成功而 $j_2$ 成功，$\max\{dp_{j_1} + i - {j_1} - 1, t_i\} \ge t_i$，$-j_1 > -j_2$，所以 $j_2$ 更优。

证毕。

所以最优转移一定是考虑前 $i - 1$ 个数时 $dp_j - 2j$ 的后缀最小值。

用单调栈表示，这些位置 $j$ 递增，$dp_j - 2j$ 递增，所以 $dp_j - j$ 也递增。

注意到取 max 成功的条件为 $dp_j - j \le t_i - i + 1$，对应着单调栈的一段前缀，且分界点随 $i$ 的增大单调后移。

若从取 max 成功的 $j$ 转移，$j$ 越大越优。

若从取 max 未成功的 $j$ 转移，$dp_j - 2j$ 越小越优，单调栈上即 $j$ 越小越优。

dp 转移的过程中同时维护单调栈和分界点，从取 max 成功的最大 $j$ 值和未成功的最小 $j$ 值转移。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
template <typename T>
inline void chkmax(T &x, const T &y) {
    if (x < y) x = y;
}
template <typename T>
inline void chkmin(T &x, const T &y) {
    if (y < x) x = y;
}
const int MAXN = 1e6 + 10;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, s, t[MAXN], stk[MAXN], tp;
ll dp[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) cin >> t[i];
    for (int i = 2; i <= n; ++i) chkmax(t[i], t[i - 1] + 1);
    stk[tp = 1] = 0;
    for (int i = 1, pos = 1; i <= n; ++i) {
        while (pos <= tp && dp[stk[pos]] - stk[pos] < t[i] - i + 1) ++pos;
        dp[i] = INFLL;
        if (pos <= tp)
            chkmin(dp[i], dp[stk[pos]] - stk[pos] * 2 + i * 2 + s * 2 - 2);
        if (pos > 1) chkmin(dp[i], (ll)t[i] + s * 2 + i - stk[pos - 1] - 1);
        while (tp && dp[i] - i * 2 <= dp[stk[tp]] - stk[tp] * 2) --tp;
        stk[++tp] = i, chkmin(pos, tp);
    }
    cout << dp[n] << "\n";
    return 0;
}

---

## 作者：Drot_Lee (赞：0)

## Tag:

DP，单调队列。

------

## 前置知识：

单调队列。

------
## 题解：

$O(n^2)$ 做法：

直接 DP。

可以想象一下，这个过程肯定是几个车一起去一起回来的，而且是一批一批的。

于是就有了 **状态**。

#### 状态：

F[i] 表示前 i 个车最晚回来的车的时间的最小值。

接着就是**转移**。

#### 转移：

对于前 i 个车，它肯定是在 $starttime=\max(a[i],F[j]+i-j-1)$ 时出发的，那么确定了出发时间，它回来的时间就是 $endtime=startime+2 \times s+i-j-1$ 

既然要回来的时间最少，就对 endtime 取 min。

这样转移方程就出来了：
$$
F[i]=\min(F[i],\max(F[j]+i-j-1,a[i])+2 \times S+i-j-1)
$$
#### 答案：

$F[n]$ 就是答案。

------

$O(n)$ 做法：

考虑用单调队列**优化**。

首先将 max 裂开：

1、若 $F[j]+i-j-1>=a[i]$

此时 $F[i]=F[j]+i-j-1+2 \times s+i-j-1=(F[j]-j)+2 \times (s+i-1)$，那么就要维护 F[j]-j 的最小值。

那么对第一种情况的条件移个项就变成了：$F[j]-j>=a[i]-i+1$。

因此这个就是判断条件。

2、若 $F[j]+i-j-1<a[i]$

此时 $F[i]=a[i]+2 \times S+i-j-1=(a[i]+2 \times S+i)-j$，于是就要找到 j 的最大值。

而用单调队列维护情况一的东西时，不断弹出不符合第一个条件的值，那么 j 的最大值就是最后一次弹出的地方。

------

不开 long long 见祖宗！！！

------

细节请见代码：

```cpp
/*
最近对指针比较感兴趣
只学了一点点皮毛
这个代码稍微有一点指针，应该不会造成阅读影响吧
*/
#include<bits/stdc++.h>
#define M 2000000
#define int long long
using namespace std ;
int read ()
{
	int x = 0 , f = 1 ; char ch = getchar () ;
	while ( ! isdigit ( ch ) ) { if ( ch == '-' ) f = -1 ; ch = getchar () ; }
	while ( isdigit ( ch ) ) { x = ( x << 3 ) + ( x << 1 ) + ch - 48 ; ch = getchar () ; }
	return x * f ;
}

int n , s , a [ M ] , F [ M ] , que [ M << 1 ] ; 

signed main ()
{
	n = read () , s = read () ; for ( int i = 1 ; i <= n ; i ++ ) a [ i ] = read () ; 
	sort ( a + 1 , a + 1 + n ) ; 
	memset ( F , 30 , sizeof ( F ) ) ; F [ 0 ] = 0 ; a [ 0 ] = -1 ; 
	for ( int i = 1 ; i <= n ; i ++ ) a [ i ] = max ( a [ i ] , a [ i - 1 ] + 1 ) ; 
	int *head , *tail ; 
	head = tail = ( que + 1 ) ; 
	for ( int i = 1 ; i <= n ; i ++ ) 
	{
		while ( head <= tail && F [ *head ] - *head < a [ i ] - i + 1 ) head ++ ; 
		if ( head <= tail ) F [ i ] = min ( max ( a [ i ] , F [ *head ] + i - *head - 1 ) + i - *head - 1 + 2 * s , F [ i ] ) ; 
		F [ i ] = min ( max ( a [ i ] , F [ * ( head - 1 ) ] + i - * ( head - 1 ) - 1 ) + i - * ( head - 1 ) - 1 + 2 * s , F [ i ] ) ; 
		while ( head <= tail && F [ *tail ] - 2 * ( *tail ) >= F [ i ] - 2 * i ) tail -- ; 
		* ( ++ tail ) = i ; 
	}
	cout << F [ n ] << endl ; 
	return 0 ; 
}
```
#### 后记

这是第八次交，希望能过。

过不了请告诉我具体原因，别让我抓瞎了QwQ

---

