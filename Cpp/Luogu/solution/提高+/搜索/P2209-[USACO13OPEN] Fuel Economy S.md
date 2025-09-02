# [USACO13OPEN] Fuel Economy S

## 题目描述

Farmer John has decided to take a cross-country vacation. Not wanting his cows to feel left out, however, he has decided to rent a large truck and to bring the cows with him as well!

The truck has a large tank that can hold up to G units of fuel (1 <= G <= 1,000,000).  Unfortunately, it gets very poor mileage: it consumes one unit of fuel for every unit of distance traveled, and FJ has a total of D units of distance to travel along his route (1 <= D <= 1,000,000,000).

Since FJ knows he will probably need to stop to refill his tank several times along his trip, he makes a list of all the N fuel stations along his route (1 <= N <= 50,000).  For each station i, he records its distance X\_i from the start of the route (0 <= X\_i <= D), as well as the price Y\_i per unit of fuel it sells (1 <= Y\_i <= 1,000,000).

Given this information, and the fact that FJ starts his journey with exactly B units of fuel (0 <= B <= D), please determine the minimum amount of money FJ will need to pay for fuel in order to reach his destination. If it is impossible for him to reach the destination, please output -1. Note that the answer to this problem may not fit into a standard 32-bit integer.


Farmer John 决定去一次跨国旅游度假。为了不让他的奶牛们感到被抛弃，他决定租一辆大卡车来带他的奶牛们一起旅行。


这辆卡车有一个很大的油箱，可以装下 $G$ 个单位的油（$1 \le G \le {10}^6$），不幸的是，卡车的耗油量也很大，卡车每运动一个单位的距离，就要消耗一个单位的油。Farmer John 要在他的旅程中走 $D$ 个单位的距离。（$1 \le D \le {10}^9$）


因为 FJ 直到他可能要几次在旅途中停下，给油箱加油，所以他把在旅途沿路上的 $N$ 个加油站的记录做成了表格。对于第 $i$ 个加油站，他记录了加油站与起点的距离 $X_i$（$0 \le X_i \le D$），以及加油站中每单位油的价格 $Y_i$（$1 \le Y_i \le {10}^6$）。

已知以上所给的信息，以及 FJ 在路途开始时拥有的燃油的数量 $B$（$0 \le B \le D$），请计算出 FJ 到达目的地时花费的油费用的最小值。如果 FJ 无法到达旅途的终点，那么请输出 `-1`。本题的答案可能无法使用 32 位整数储存。


## 说明/提示

样例解释：FJ 先移动 $2$ 个单位，然后停下购买 $2$ 个单位的油（要花费 $40 \times 2$）。然后一直前进到距离起点 $5$ 个单位的地方，此时油箱为空。这时向油箱里加满油（要花费 $7 \times 10$）。再向前走 $5$ 个单位，加 $2$ 个单位的油（花费 $12 \times 2$）。最后一直走到终点。此时总花费是 $174$。


## 样例 #1

### 输入

```
4 10 3 17
2 40
9 15
5 7
10 12```

### 输出

```
174
```

# 题解

## 作者：xuxinyu (赞：14)

上次的忘了粘代码，管理员可以覆盖掉上一篇吗


来篇C++


首先，我们可以特判掉不能到达的情况，这样可以减小代码复杂度


不能到达的情况有三：


1、第一个加油站到起点的距离>初始油量


2、终点到最后一个加油站的距离>油箱容量


3、途中存在相邻加油站的距离>油箱容量


前提是你排好序了


为了避免代码中进行到终点的特判，可以在终点增加一个价格为0的加油站


接下来，我们需要维护当前在哪个加油站，当前剩余油量，接下来去哪个加油站


然后贪心


假设当前在now加油站


1、假设在能跑到的范围内，第一个价格比他便宜的加油站to，就在当前加油站加油，加到恰好能跑到to


2、在能跑到的范围内，没有价格比他便宜的加油站，就在now加满油，跑到能跑到的范围内，价格最便宜的加油站


注意，在1中不是跑到范围内最便宜的加油站，而是只要遇到一个比now便宜，就跑过去


跑到最便宜的只能拿40分


    
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,G,B,D;
void read(int &x)
{
    x=0; char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) { x=x*10+c-'0'; c=getchar(); }
}
struct node
{
    int d,p;
}e[50005];
int dis[50005],price[50005];
int findmin(int s,int lim)
{
    int now=s+1,to=50003;
    while(now<=N)
    {
        if(dis[now]-dis[s]>lim) return to;
        if(price[now]<price[s]) return now;
        if(price[now]<price[to]) to=now;
        now++;
    }
}
bool cmp(node a,node b)
{
    return a.d<b.d;
}
int main()
{
    read(N);read(G);read(B);read(D);
    for(int i=1;i<=N;i++) read(e[i].d),read(e[i].p);
    sort(e+1,e+N+1,cmp);
    for(int i=1;i<=N;i++) 
    {
        dis[i]=e[i].d; price[i]=e[i].p;
        if(dis[i]-dis[i-1]>G) { printf("-1"); return 0; }
    }
    if(dis[1]>B || D-dis[N]>G) { printf("-1"); return 0; }
    price[50003]=2e9;
    int now=0,to;
    to=findmin(now,B);
    if(now>N) { printf("0"); return 0; }
    now=to;
    int nowB=B-dis[to];
    LL ans=0;
    if(dis[N]==D) price[N]=0;
    else
    {
        N++; dis[N]=D; price[N]=0;
    }
    while(now<N)
    {
        to=findmin(now,G);
        if(price[to]>price[now]) 
        {
            ans+=1ll*(G-nowB)*price[now];
            nowB=G-dis[to]+dis[now];
        }
        else
        {
            ans+=1ll*(dis[to]-dis[now]-nowB)*price[now];
            nowB=0;
        }
        now=to;
    }
    printf("%lld",ans);
}
```

---

## 作者：红黑树 (赞：11)

## 题意
有一条直线公路，给定汽车的油箱容量、初始油量和 $N$ 个加油站的位置与单价，求到达终点的最少费用。

## 思路
由于移动是连续的，所以不妨先将加油站按照位置进行排序，这样更加便于处理。

从起点到达终点可能会需要多次加油，所以问题的关键就在于要求出到达每个加油站时需要加多少油。显然，应该在尽可能便宜的加油站加油，基于这个想法，不难得到一个贪心策略：

对于当前到达的加油站，要判断是否加油，主要取决于之后更便宜的最近加油站 $j$ 的位置：
1. 如果油箱的容量足够从 $i$ 到 $j$，那就只需要确保油足够到达 $j$ 即可，因为 $j$ 不仅更靠后，价格还更低，没有在 $i$ 加更多油的必要。所以我们加到油足够，然后直接到 $j$。
2. 如果油箱的容量不足以从 $i$ 到 $j$，说明路途中还需要加油，且价格还要更贵，所以肯定要在当前站把油加满，移动到 $i + 1$ 再说。

我们可以按顺序来考虑每个加油站，并用栈维护一个价格递增的序列，每次要添加一个新加油站时，将栈尾价格不低于当前的都退栈，再将新加油站加入，这个新加油站就是所有退栈加油站的最近更便宜的加油站。

由于起点不能加油，所以我们可以先移动到第一个加油站，然后令终点单价为 $0$，并贪心求解即可。

## 复杂度
### 时间
* 排序 $\mathcal O(N \log N)$
* 计算每个加油站最近的更便宜加油站 $\mathcal O(N)$
* 贪⼼移动 $\mathcal O(N)$
* 总时间复杂度为 $\mathcal O(N \log N)$

### 空间
* 记录加油站 $\mathcal O(N)$

## 代码
```cpp
#include <algorithm>
#include <icecream>

using namespace std;
using LL = long long;

const int kMaxN = 5e4 + 2;

struct E {                                                // 加油站
  int x, y, p;                                            // 位置、价格、最近的更优加油站
  bool operator<(const E &_e) const { return x < _e.x; }  // 按照坐标排序
} e[kMaxN];
int a[kMaxN], n, g, b, d, m;

LL C() {                     // 计算答案
  LL r = 0;                  // 初始化答案
  b -= e[1].x;               // 先移动到第1个站
  for (int i = 1; i < n;) {  // 从位置1开始直到n
    if (b < 0) {             // 油箱容量不足
      return -1;             // 无解
    }
    if (e[e[i].p].x - e[i].x <= g) {            // 当前油箱容量足够到达更优站
      LL v = max(0, e[e[i].p].x - e[i].x - b);  // 需要加的油
      r += v * e[i].y;                          // 累加费用
      b += v - (e[e[i].p].x - e[i].x);          // 消耗油量
      i = e[i].p;                               // 移动到更优站
    } else {                                    // 不足以到达更优站
      r += 1LL * (g - b) * e[i].y;              // 加满油的费用
      b = g - (e[i + 1].x - e[i].x);            // 移动后剩下的油量
      i++;                                      // 移动到下个相邻站
    }
  }
  return b < 0 ? -1 : r;
}

int main() {
  cin >> n >> g >> b >> d;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].x >> e[i].y;
  }

  sort(e + 1, e + 1 + n);

  e[++n] = {d};                              // 加入终点
  for (int i = 1; i <= n; i++) {             // 计算每个站的最近更优站
    for (; m && e[i].y <= e[a[m]].y; m--) {  // 当前站比之前的更优则删除栈尾
      e[a[m]].p = i;                         // 记录
    }
    a[++m] = i;  // 加入当前站
  }
  cout << C();
  return 0;
}
```

---

## 作者：HyyypRtf06 (赞：8)

~~一看觉得这题好像只有俩C++，其中一个还是优队，那我就写一篇易懂一点的题解吧~qvq！~~

思路是**贪心**没跑了，那么我们就要考虑几种情况：

为了花钱**最少**，所以当然是要选择**尽量便宜**的加油站：

![](https://cdn.luogu.com.cn/upload/image_hosting/7efgd0vg.png)

**上面只是个参考图。**

假定当前位处于$1$号加油站。

让我们看几种情况：

$a>b>c$

此时如果可以跑到$2$号加油站就**不要**在$1号$加油站加油，为什么？因为如果你能跑到$2$号加油站你就可以加更便宜的油，没必要加$1$号加油站更贵的油。由此可以得到一条贪心策略：  
#### 如果有一个加油站比它下一个加油站的油贵且你目前的油足够跑到下一个加油站，则直接跑过去，不在这个加油站加油。
同理，看参考图。当你跑到$2$号加油站之后如果发现剩下的油足以跑到$3$号加油站，就跑过去。则贪心策略可以简化成这样：

### 如果你用光你所有的油能跑到一个比当前所处的加油站便宜的加油站，就跑过去。

那这个时候某些同学就问了：那如果有两个，三个，甚至更多的加油站满足上面你说的这个条件呢？跑哪个呢？

**肯定去最便宜的那个鸭！这样才能花费最少。如果有两个及以上的加油站都是最便宜的，那就无所谓跑到哪个里面去了。因为单价都是最便宜的。**

**Tip:此处不是加满油跑过去，而是不加油跑过去。**

--------
--------
--------

$a<b<c$

有便宜的，自然就有贵的嘛。贵的就很好理解了。

**想象**~~脑补~~**一下：**

假设你是个美术特长生（画素描贼耗铅笔），原本铅笔的价格都是1元10支，而你因为某些渠道得知了铅笔的价格会在几天后疯狂飙升。那么，你是会选择买回大板大板的铅笔备用还是等到缺铅笔而且价格高很多的时候再去买铅笔？我相信如果所有人都会选择买回大板大板的铅笔备用。再看回这个题，我想信你们一定都能得到一个策略：

### 如果你加满油之后都无法跑到一个比现在处于的加油站便宜的加油站，那干脆直接加满油跑到所有能跑到的加油站中最便宜的加油站去看看。

**Tip:在同一个位置可能出现两个及以上的加油站，请注意！**

注意判断终点！

AC code

```cpp
//如果还有哪边不明白的可以选择把我的注释输出复原，然后就可以看到各个变量的运行状况惹！（看我多好qvq
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#define dis first
#define prc second
using namespace std;

typedef long long ll;
const int MAXN=1e6+5;
ll n,g,b,d,ans;
pair<long long,long long> a[MAXN];

void input(void){
	cin>>n>>g>>b>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].dis>>a[i].prc;
	}
	a[0]=make_pair(0,10000000LL);
	a[n+1]=make_pair(d,0LL);
}

bool dfs(ll k){
//puts("-----------------------------------------------------------------");
	if(a[k].dis==-1){                       //重复
		return dfs(k+1);
	}
	const ll now=a[k].dis;
//cout<<"k:"<<k<<endl;
//cout<<"now:"<<now<<endl;
//cout<<"b:"<<b<<endl;
//cout<<"ans:"<<ans<<endl;
	if(k==n+1){
		return true;
	}
	ll kk=k;
	while(kk<=n){                        //最优的加油站
		kk++;
		if(a[kk].dis-now>g){
			break;
		}
		if(a[kk].prc<=a[k].prc){                              //下一个比这一个便宜的的加油站
			ll add=a[kk].dis-now-b;
			if(add<0){
				add=0;
			}
//cout<<"下一个较优的加油站是："<<kk<<endl;
//cout<<"加的油量是："<<add<<endl;
			ans+=a[k].prc*add;
			b+=add;
			b-=a[kk].dis-now;
			return dfs(kk);
		}
	}
//----------------------------------------------------------------------------------------
//cout<<"kk:"<<kk<<endl;
//cout<<"目标加油站离这里的距离："<<a[kk].dis-now<<endl;
	long long MIN=2e18;
	long long MIN_NUMBER;
	for(int i=k+1;i<kk;i++){
		if(MIN>=a[i].prc){
			MIN=a[i].prc;
			MIN_NUMBER=i;
		}
	}
//cout<<"下一个最优加油站是："<<MIN_NUMBER<<endl;
//cout<<"需要加的油量是："<<g-b<<endl;
	ans+=(g-b)*a[k].prc;
	b=g;
	b-=a[MIN_NUMBER].dis-now;
	return dfs(MIN_NUMBER);
}

int main(){
	input();
	sort(a+1,a+1+n);
	for(int i=0;i<n+1;i++){
		if(a[i+1].dis-a[i].dis>g){
			puts("-1");
			return 0;
		}
	}
	dfs(0);
	cout<<ans<<endl;
	return 0;
}
```

### 如果还是有不懂的欢迎私信提问，会在最迟12h内给您答复~qvq




---

## 作者：船酱魔王 (赞：5)

## 题意回顾

一条公路，你要从起点跑到终点，油箱大小和初始油量给定，加油站的位置和价格给定。求最小代价，站点数不超过 $ 5 \times 10^4 $。

## 分析

考虑贪心，因为容量的限制无法直接贪心，参考 CSP-J 2023 T2 的反悔贪心思想。

考虑我们可以加一个虚空油箱，就是需要油如果没有的话先从虚空油箱取用，到达下一个加油站前先跨越时空考虑在哪个加油站能把现在的虚空油箱加满。

注意时时刻刻不能超过油箱的上限，因此跨越时空加油时要根据前缀加油和耗油，以及初始油的空缺量算出这个位置最多加多少以免油箱爆掉，可以用树状数组单点修改一个时刻的加油量和前缀查询某时刻之前的总加油量。

寻找怎么填补虚空油箱，可以开一个 `set` 存储所有还能加油的加油站，如果一个加油站不能加油了的话删除掉，时间复杂度均摊 $ O(n \log n) $。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#define ll long long
using namespace std;
const int N = 5e4 + 5;
int n, g, b, d;// point, contain, begin, distance
struct node {
    int dis;
    int pri;
} a[N];
bool cmp(node p1, node p2) {
    return p1.dis < p2.dis;
}
bool operator<(node p1, node p2) {
    if(p1.pri != p2.pri) return p1.pri < p2.pri;
    return p1.dis < p2.dis;
}
ll c[N];
int lowbit(int x) {
    return x & (-x);
}
void update(int x, int v) {
    for(int i = x; i <= n; i += lowbit(i)) c[i] += v;
}
ll query(int x) {
    ll res = 0;
    for(int i = x; i >= 1; i -= lowbit(i)) res += c[i];
    return res;
}
set<node> ms;//dis->id, pri->price
int main() {
    scanf("%d%d%d%d", &n, &g, &b, &d);
    for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].dis, &a[i].pri);
    sort(a + 1, a + n + 1, cmp);
    bool ok = true;
    for(int i = 1; i <= n; i++) ok &= ((i == 1 && a[i].dis <= b) || (i > 1 && a[i].dis - a[i - 1].dis <= g));
    if(!ok) {puts("-1");return 0;}
    int now = b;
    ll ans = 0;
    a[n + 1].dis = d, a[n + 1].pri = 0;
    for(int i = 1; i <= n + 1; i++) {
        now -= a[i].dis - a[i - 1].dis;
        while(now < 0) {
            set<node>::iterator it = ms.begin();
            ll ub = a[it -> dis].dis - query(it -> dis) + g - b;
            if(now + ub >= 0) {
                ans -= (ll)now * (it -> pri);
                update(it -> dis, -now);
                now = 0;
                break;
            } else {
                now += ub;
                ans += (ll)ub * (it -> pri);
                update(it -> dis, ub);
                for(int j = it -> dis; j >= 1; j--) {
                    if(ms.find((node){j, a[j].pri}) == ms.end()) break;
                    ms.erase((node){j, a[j].pri});
                }
            }
        }
        ms.insert((node){i, a[i].pri});
    }
    printf("%lld\n", ans);
    return 0;
}

```

---

## 作者：Sol1 (赞：5)

这个问题直接贪心没有任何思路，所以可以想到需要引入一个反悔的过程。在本题中，引入这个过程就是：加油暂不需要付钱，记录下来加的每一单位油的价格，每次烧掉一单位油的时候再支付对应的油钱。

那么现在有一个非常直观的策略：由于加油不用不需付钱，所以不妨直接到每一个位置都加满，然后每一单位行程都烧最便宜的一单位油。最后没有烧的油相当于原样退还给加油站。写一遍发现样例 1 输出 $333$。

这是因为还存在一种没有考虑到的情况：有可能某一加油站价格较高，而离它很近的后面的一个加油站价格较低，然后再跑很远才能到下一个加油站。此时，在这一加油站加满实际上浪费了容量，不如只加到可以跑到下一个加油站，然后再加满。

考虑到原算法本质上只在最后到终点的时候进行了反悔的操作，中途都没有把加过的油退还；不妨在中途引入这个过程，即对于油箱中高于当前油价的油全部退掉，以这一加油站的油进行替代。

这样很明显是正确的，因为一直没用过的油不加也不会有任何影响。

同时由于加入的一定是油箱中的最大值，删除的一定是油箱中最大值或最小值，所以开一个双端队列来维护，结合基数排序就可以做到严格 $O(n)$ 了。

以下是代码，笔者懒了并没有写基数排序，所以仍然是 $O(n\log n)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[(1<<21)+5], *p1 = buf, *p2 = buf;

inline int qread() {
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

pair <long long, long long> que[2000010];
int n, qhd = 1000005, qtl = 1000005, g, b, d;
pair <long long, long long> a[1000005];
long long ans = 0;

inline void Read() {
	n = qread(); g = qread(); b = qread(); d = qread();
	for (int i = 1;i <= n;i++) {
		a[i].first = qread(); a[i].second = qread();
	}
}

inline bool Move(int dis) {
	while (qhd != qtl && dis) {
		if (que[qhd].second <= dis) {
			b -= que[qhd].second;
			dis -= que[qhd].second; ans += que[qhd].first * que[qhd].second;
			qhd++;
		} else {
			b -= dis;
			que[qhd].second -= dis; ans += dis * que[qhd].first;
			dis = 0;
		}
	}
	return dis == 0;
}

inline void PopGas(int cost) {
	while (qhd != qtl && que[qtl - 1].first >= cost) {
		b -= que[qtl - 1].second;
		qtl--;
	}
	que[qtl++] = make_pair(cost, g - b); b = g;
}

inline void Solve() {
	a[++n] = make_pair(d, 0);
	que[qtl++] = make_pair(0, b);
	for (int i = 1;i <= n;i++) {
		if (!Move(a[i].first - a[i - 1].first)) {
			puts("-1");
			return;
		}
		PopGas(a[i].second);
	}
	printf("%lld", ans);
}

int main() {
	Read();
	sort(a + 1, a + n + 1);
	Solve();
	return 0;
}
```

---

## 作者：John_yangliwu (赞：5)

### 思路
贪心反悔。

#### （一）判断无解情况

无解情况有 $3$ 种：
1. $B$ 单位的油到不了第一个加油站；
2. 在第 $i$ 个加油站加满油到不了第 $i+1$ 个加油站 $(1\le i< N)$；
3. 在第 $N$ 个加油站加满油到不了终点。

为了方便，我们把终点也理解成一个加油站，这样就可以把 $2$，$3$ 两种情况合并了。

#### （二）怎样贪心，怎样反悔
对于第 $i$ 个加油站，为了到达第 $i+1$ 个加油站（或终点），我们都要先加满油（**贪心**）。

如果发现第 $i+1$ 个加油站的油比第 $i$ 个加油站的油便宜，那么就把在第 $i$ 个加油站买的多余的油，即从第 $i$ 个走到第 $i+1$ 个不需要的油，全部退掉（**反悔**）。

还有一个疑点：我们在两个加油站之间走的时候，应该用那些油呢？
显然，便宜的油优先用，因为越贵的油越容易退掉，而退掉的油越多我们的花费就越小（**贪心**）。

那么，我们就需要一个存油的数据结构，需要支持以下操作：
1. 取出最便宜的油
2. 加一种油
3. 取出最贵的油

我们发现，**单调队列**可以胜任。

时间复杂度：$O(N)$，由于使用单调队列，所以严格线性。

期望得分：$100pts$。

---
### Tips:
别忘了开 long long。


---
### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 5e4 + 5;
int N, G, B, D;
struct node {//加油站结构体
	int x, y;
	node(int x = 0, int y = 0): x(x), y(y){}
	bool operator < (const node& n1) const {
		return x < n1.x;
	}
} n[MAXN];

struct gas {//油结构体
	int p, m;
	gas(int p = 0, int m = 0): p(p), m(m){}
};

gas q[MAXN];//存油的单调队列
int l = 0, r = -1;

ll work(int len) {//走len个单位距离
	ll ans = 0;
	while(len > 0) {
		if(q[l].m > len) {//不用光最便宜的油就可以走完len
			ans += len * 1ll * q[l].p;
			q[l].m -= len;
			len = 0;
		}
		
		else {//需要用光最便宜的油
			ans += q[l].m * 1ll * q[l].p;
			len -= q[l].m;
			++l;
		}
	}
	return ans;
}

int main() {
	cin >> N >> G >> B >> D;
	for(int i = 1; i <= N; i++) {
		cin >> n[i].x >> n[i].y;
	}
	n[++N] = node(D, 0);//把终点也理解成加油站，油价格为0
	sort(n + 1, n + 1 + N);
	for(int i = 1; i <= N; i++) {//判断无解
		if(i == 1 && n[i].x >= B || i > 1 && n[i].x - n[i - 1].x > G) {
			cout << -1 << endl; return 0;
		}
	}
	
	q[++r] = gas(0, B);
	ll ans = 0;
	int M = B;//M是现在邮箱里油的总量
	for(int i = 1; i <= N; i++) {
		ans += work(n[i].x - n[i - 1].x);//从第i-1个加油站走到第i个加油站
		M -= n[i].x - n[i - 1].x;
		
		if(i == N) {
			cout << ans << endl; return 0;
		}
		
		while(l <= r && q[r].p > n[i].y) {//反悔，退掉比较贵的油
			M -= q[r].m;
			--r;
		}
		
		q[++r] = gas(n[i].y, G - M);//加油
		M = G;//加满了
	}
	
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/45743815)

---
$\large\text{THE END}$

---

## 作者：Erina (赞：4)

## P2209

优先队列~~裸~~题, 其实贪也可以, 只是有点麻烦......

每一次直接把油加满, 优先用最便宜的油, 之后每次到一个站把更贵的油全部卖掉, 换成这个站的.

最后额外加一个站点就可以了.

提一下一些小坑:

1. 要开`long long`
2. 终点不是$n$, 是$d$
3. $b$是开始时的油量

放一下代码......

```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {// 快读背板就好了
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
int n, g, b, d;
typedef pair<int, int>mp;
mp srt[100005];
mp huaji[100005];
int l, r;
long long price;
int main() {
	n = read(), g = read(), b = read(), d = read();
	for (int i = 1; i <= n; i++) {
		srt[i].first = read();
		srt[i].second = read();
	}
   srt[n + 1] = mp(d, 0);
	sort(srt + 1, srt + n + 2);
	l = r = 1, huaji[1] = { b,0 };
	int oil = b;
	for (int i = 1; i <= n + 1; i++) {
		int ldis = srt[i].first - srt[i - 1].first;
		oil -= ldis;
		if (oil < 0)
        cout << -1, exit(0);// 不能到达, 直接挂掉
		while (ldis) {// 尽可能使用最便宜的油
			int minn = min(ldis, huaji[l].first);
			ldis -= minn, huaji[l].first -= minn;
			if (!huaji[l].first)l++;
		}
		while (huaji[r].second > srt[i].second && r >= l) {//最贵的油卖掉
			oil -= huaji[r].first;
			price -= 1ll * huaji[r].first * huaji[r].second;
			r--;
		}
		huaji[++r] = mp(g - oil, srt[i].second);
		price += 1ll * (g - oil) * srt[i].second;
		oil = g;//灌满油
	}
	cout << price;//最后加了一个节点会直接卖光不用特判
}
```


---

## 作者：FishingStar (赞：3)

单调队列

直接进入正题

考虑爆搜 O(n ^ 2) 显然不可行，那么我们就要换成较为高级的算法喽。

首先读入，然后油分层，以价值分层。

 到达一个加油站时(不是第一个加油站)，我们让背包里的油是满的，那么如果手里的满油还是过不去，那就怎么都过不去了。又如果手里最贵的油比现加油站加的油还要贵，那么我们可以这么想：如果把它反悔卖了，不会有影响，因为那部分是过剩的。消耗时首先消耗最便宜的油。

如果发现过不去了，那么就输出负一

上代码

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
struct gs{
    long long dis, val;
};
struct gas{
    long long gas, val;
};
gs s[100005];

int cmp(gs x, gs y){
    return x.dis < y.dis;
}

int main(){
    long long n, g, b, d;
	cin >> n >> g >> b >> d;//n个加油站，g个单位的油 ，已经有b个单位的油，d终点的距离 
	for(long long i = 1; i <= n; i++){//读入 
        cin >> s[i].dis >> s[i].val;//读入 
	}
	sort(s + 1, s + n + 1, cmp);//排序 
	deque<gas> q;//单调队列 
	long long k = 1;//循环变量 
	long long gas_val = 0;//钱 
	gas st; 
	st.gas = b;//第一次的免费油 
	st.val = 0;//第一次的免费 
	q.push_back(st);//读入 
	while(k <= n){// 
		long long z;
		if(k == 1){
	        z = b;//第一次用给的油 
	    } else {
	        z = g;//之后都用满的油
		}
	    long long l = s[k].dis - s[k - 1].dis;//距离上次的距离
	//	cout << z << "/" << l << endl; 
	    while(!q.empty() && l > 0){//如果 l 就是距离还没跑完就继续，如果都没油了就结束等会-1 
	        if(l >= q.front().gas){ //就烧掉全部 
	        	l -= q.front().gas;//距离少了一些 
	        	z -= q.front().gas;//现在烧掉了一些 
	            q.pop_front();
		    } else {//烧掉当前最便宜油的一部分 
		        q.front().gas -= l;//那一层油减少了 
		        z -= l;// 烧掉一部分
				l = 0;//距离0 
			}
		}
		if(l > 0){//如果油烧完然后就死了 
		    cout << -1;
		    return 0;
		}
	//	cout << z << " ";
		while(!q.empty() && q.back().val > s[k].val){//油没换完 
		    gas_val -= q.back().val * q.back().gas;//开支减少 
		    z -= q.back().gas;//这时候的油也减少 
		    q.pop_back();//杀掉这个油 
		}
	//	cout << z << " "; 
		struct gas cnt;//遇到要买的 
	    cnt.gas = g - z;//买多少当前的油 
	    cnt.val = s[k].val; 
		gas_val += cnt.gas * cnt.val;//最后的总开支加上 
		q.push_back(cnt);//加入这种油 
	//	cout << gas_val << endl;//测试 
	    k++;//下一个加油站 
	}
	long long l = d - s[n].dis;//最后走多远 
    while(!q.empty() && l > 0){//如果 l 就是距离还没跑完就继续，如果都没油了就结束等会-1 
        if(l >= q.front().gas){ //就烧掉全部 
        	l -= q.front().gas;
            q.pop_front();
	    } else {//烧掉当前最便宜油的一部分 
	        q.front().gas -= l;
			l = 0;//距离0 
	        break;
		}
	}
	if(l > 0){//如果油烧完然后就死了 
	    cout << -1;
	    return 0;
	}
//	cout << gas_val << endl;; 
	while(!q.empty()){//变现 
		gas_val -= q.front().val * q.front().gas;
		q.pop_front();
	}
	cout << gas_val;
    return 0;
}

```
注意按距离排序加油站，不然会有奇奇怪怪的事情发生

---

## 作者：Lokawa (赞：2)

贪心
大致思路楼上有讲

不多说先上代码

```pascal
var
n,g,t,d,c,sum,k:int64;
m,mi,i,j:longint;
a,b:array[1..100000]of int64;
procedure kp(l,r:longint);
var i,j,t,mid:longint;
begin
  i:=l;
  j:=r;
  mid:=a[(l+r) div 2];
  repeat
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      t:=b[i]; b[i]:=b[j]; b[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if i<r then kp(i,r);
  if l<j then kp(l,j);
end;//按距离快排
begin
readln(n,g,t,d);
for i:=1 to n do readln(a[i],b[i]);
kp(1,n);
i:=1;
a[n+1]:=d;
m:=100000;
mi:=m;
a[m]:=maxlongint;
b[m]:=maxlongint;
while a[i]<=t do
begin
  if b[i]<b[m] then m:=i;
  inc(i);
end;//在能到达的情况下找最便宜的加油站
if m=mi then
begin
  writeln(-1);
  close(input);
  close(output);
  halt;
end;//第一个都不能到达的话直接输出-1
i:=m;
k:=t-a[i];
while i<=n do
begin
  m:=mi;
  j:=i+1;
  c:=0;
  while a[j]<a[i]+g do
  begin
    if b[j]<b[m] then m:=j;//还是在能到达的情况下找最便宜的加油站
    if b[j]<b[i] then
    begin
      sum:=sum+(a[j]-a[i]-k)*b[i];
      c:=1;
      k:=0;
      break;
    end;//如果后面最便宜的加油站比当前的便宜，那么只要加满足够到达那个加油站的油
    inc(j);
  end;
  if m=mi then
  begin
    writeln(-1);
    close(input);
    close(output);
    halt;
  end;//不能到达输出-1
  if c=0 then
  begin
    sum:=sum+(g-k)*b[i];
    k:=g-(a[m]-a[i]);
  end;//如果能到达的最便宜加油站还不如当前的便宜，那么就在当前加油站加满油
  i:=m;
end;
writeln(sum);
end.
```
蒟蒻第一次发题解有错误欢迎指出QWQ


---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候已经熟读题意

我们可以先总结出来三个不可能到达的情况:

$1.$从起点到第一个加油站的距离用初始油箱不能到达

$2.$中间的两个加油站之间的距离之差大于油箱的总容量

$3.$最后一个加油站到终点之间的距离之差大于油箱的总容积

易知，只要不满足上面的三种情况，其它情况都可以到达终点

接下来，我们只要考虑如何优化最大值

假设我们当前已经来到了加油站$i$，当前的距离为$v$

我们可以分两种情况进行讨论

$1.$在接下来的$i+v$的距离里面当前节点的价格是最少的一个

我们可以在当前节点直接加满，然后可以直接加满油继续枚举

$2.$在接下来的$i+v$的距离里面当前节点的价格不是最少的一个

我们可以在当前节点加油加到刚刚好可以到达最小值的那个点，在最小值的那个点
加满油即可

最后直接输出答案即可

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
struct node{
	int x,y;
}e[50010];
int n,g,b,d;
int dis[50010];
int pr[50010];
inline bool cmp(node a,node b){
	return a.x<b.x;
}
inline int findmin(int s,int sum){
	int now;
	int tto;
	now=s+1;
	tto=50005;
	while(now<=n)
		{
			if(dis[now]-dis[s]>sum)
				return tto;
			if(pr[now]<pr[s])
				return now;
			if(pr[now]<pr[tto])
				tto=now;
			++now;
		}
}
inline void init(){
	sort(e+1,e+n+1,cmp);
	for(register int i=1;i<=n;++i)
		{
			dis[i]=e[i].x;
			pr[i]=e[i].y;
			if(dis[i]-dis[i-1]>g)
				{
					write(-1);
					return;
				}
		}
	if(dis[1]>b)
		{
			write(-1);
			return;
		}
	if(d-dis[n]>g)
		{
			write(-1);
			return;
		}
	pr[50005]=2e9;
	int now=0;
	int to;
	to=findmin(now,b);
	if(now>n)
		{
			write(0);
			return;
		}
	now=to;
	int noww;
	noww=b-dis[to];
	int ans=0;
	if(dis[n]==d)
		pr[n]=0;
	else
		{
			++n;
			dis[n]=d;
			pr[n]=0;
		}
	while(now<n)
		{
			to=findmin(now,g);
			if(pr[to]>pr[now])
				{
					ans+=(g-noww)*pr[now];
					noww=g-dis[to]+dis[now];
				}
			else
				{
					ans+=(dis[to]-dis[now]-noww)*pr[now];
					noww=0;
				}
			now=to;
		}
	write(ans);
	return;
}
signed main(){
	n=read();
	g=read();
	b=read();
	d=read();
	for(register int i=1;i<=n;++i)
		{
			e[i].x=read();
			e[i].y=read();
		}
	init();
	return 0;
}
```


---

## 作者：66666a (赞：1)

本题为贪心

大致思想：当该点价格较贵，你只需要加能到下个点的油，否则你需要加能到你能力范围内最便宜的点的油。

```cpp
var
n,g,t,d,c,sum,k:int64;
m,m1,i,j:longint;
a,b:array[1..100000]of int64;
procedure kp(l,r:longint);
var i,j,t,m1d:longint;
begin
i:=l;
j:=r;
m1d:=a[(l+r) div 2];
repeat
while a[i]<m1d do inc(i);
while a[j]>m1d do dec(j);
if i<=j then
begin
t:=a[i]; a[i]:=a[j]; a[j]:=t;
t:=b[i]; b[i]:=b[j]; b[j]:=t;
inc(i);
dec(j);
end;
until i>j;
if i<r then kp(i,r);
if l<j then kp(l,j);
end;
begin
assign(input,'fuel.in');
assign(output,'fuel.out');
reset(input);
rewrite(output);
readln(n,g,t,d);
for i:=1 to n do readln(a[i],b[i]);
kp(1,n);
i:=1;
a[n+1]:=d;
m:=100000;
m1:=m;
a[m]:=maxlongint;
b[m]:=maxlongint;
while a[i]<=t do
begin
if b[i]<b[m] then m:=i;
inc(i);
end;
if m=m1 then
begin
writeln(-1);
close(input);
close(output);
halt;
end;
i:=m;
k:=t-a[i];
while i<=n do
begin
m:=m1;
j:=i+1;
c:=0;
while a[j]<a[i]+g do
begin
if b[j]<b[m] then m:=j;
if b[j]<b[i] then
begin
sum:=sum+(a[j]-a[i]-k)*b[i];
c:=1;
k:=0;
break;
end;
inc(j);
end;
if m=m1 then
begin
writeln(-1);
close(input);
close(output);
halt;
end;
if c=0 then
begin
sum:=sum+(g-k)*b[i];
k:=g-(a[m]-a[i]);
end;
i:=m;
end;
writeln(sum);
close(input);
close(output);
end.
```

---

