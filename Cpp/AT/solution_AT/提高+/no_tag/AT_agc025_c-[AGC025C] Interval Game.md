# [AGC025C] Interval Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc025/tasks/agc025_c

高橋君と青木君は数直線と区間を使ってゲームをすることにしました。 高橋君は数直線上に立っており、最初は座標 $ 0 $ にいます。 また、青木君は $ N $ 個の区間を持っており、$ i $ 個目の区間は $ [L_i,R_i] $、つまり座標が $ L_i $ 以上 $ R_i $ 以下の点からなる区間となっています。

このゲームは $ N $ 回のステップからなります。$ i $ ステップ目では以下の手順を踏みます。

- まず青木君は、$ N $ 個の区間の内、まだ選んでいない区間を一つ選び、その区間を高橋君に伝える。
- 次に高橋君は、青木君が今回選んだ区間に入るように、数直線上を移動する。

$ N $ 回のステップを終えた後、高橋君が座標 $ 0 $ まで戻ることでゲームは終了します。

高橋君がゲーム全体を通して移動する距離の合計を $ K $ としたとき、青木君は $ K $ ができるだけ大きくなるように区間を選び、 高橋君は $ K $ ができるだけ小さくなるように移動します。 このとき、最終的に高橋君の移動距離の合計 $ K $ はいくつになるでしょうか。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ -10^5\ ≦\ L_i\ <\ R_i\ ≦\ 10^5 $
- $ L_i $ と $ R_i $ は整数

### Sample Explanation 1

高橋君と青木君の行動の一例は以下のようになります。 - 青木君が $ 1 $ 番目の区間を選び、高橋君は座標 $ 0 $ から座標 $ -4 $ まで距離 $ 4 $ だけ移動する。 - 青木君が $ 3 $ 番目の区間を選び、高橋君は座標 $ -4 $ のまま動かない - 青木君が $ 2 $ 番目の区間を選び、高橋君は座標 $ -4 $ から座標 $ 3 $ まで距離 $ 7 $ だけ移動する。 - 高橋君は座標 $ 3 $ から座標 $ 0 $ まで距離 $ 3 $ だけ移動する。 このとき高橋君の移動距離の合計は $ 14 $ になってしまうので、高橋君の行動は最適ではないですが、 動き方を変えることで、移動距離の合計を $ 10 $ にすることができます。

## 样例 #1

### 输入

```
3
-5 1
3 7
-4 -2```

### 输出

```
10```

## 样例 #2

### 输入

```
3
1 2
3 4
5 6```

### 输出

```
12```

## 样例 #3

### 输入

```
5
-2 0
-2 0
7 8
9 10
-2 -1```

### 输出

```
34```

# 题解

## 作者：bugmaker3243 (赞：5)

# 基本分析

$A$ 的决策是很简单的，如果 $A$ 当前在 $pos$，需要前往 $(l,r)$，因为 $A$ 要使自己的路程最小，则有以下三种情况：

- $pos$ 在 $(l,r)$ 左侧，即 $pos<l$，则 $A$ 会前往 $l$。
- $pos$ 在 $(l,r)$ 上，即 $l\leq pos\leq r$，则 $A$ 不会动。
- $pos$ 在 $(l,r)$ 右侧，即 $r<pos$，则 $A$ 会前往 $r$。

这种走法是一种贪心的走法。

### 正确性证明

假如 $pos$ 在 $(l,r)$ 上，那么不动最优是显然的，~~你又不可能减少答案吧~~。

于是不妨设 $pos<l$，即 $pos$ 在 $(l,r)$ 左侧（右侧证明同理），那么 $A$ 这一步会向右走，代价为 $l-pos$。

考虑反证法，如果 $A$ 走到另一个位置 $x$（$l\leq x\leq r$），那么接下来这一步有两种情况：

- 向左走到 $y$，到 $l$ 总代价为 $l-pos+l-y=2l-pos-y$，到 $x$ 总代价为 $x-pos+x-y=2x-pos-y$，由于 $l\leq x$，所以 $2l-pos-y \leq 2x-pos-y$

- 向右走到 $y$，到 $l$ 总代价为 $l-pos+y-l=y-pos$，到 $x$ 总代价为 $x-pos+y-x=y-pos$，二者相等。

综上，到 $l$ 一定比到 $x$ 更优。

而 $B$ 为了让 $A$ 走的更多，肯定会**一左一右**的选区间。

- 如果当前这一步向左走，那么 $B$ 会选择 $r$ 最小的区间使 $A$ 走的多。

- 如果当前这一步向右走，那么 $B$ 会选择 $l$ 最大的区间使 $A$ 走的多。

# 具体实现

维护变量 $now$ 和两个堆 $lheap$ 和 $rheap$ 分别维护 $l$ 的最大值和 $r$ 的最小值。

每次取出第一个没有用过的区间，计算代价并标记，更新 $now$ 的值。

注意第一步有两种选择：向右或向左。只需两种都计算一遍并取大的就可以了。

# 代码（请勿抄袭）

```cpp
#include<bits/stdc++.h>
#define N 100005
#define P pair<int,int>
using namespace std;
int n,now,cnt,vst[N];
long long ans1,ans2;
struct node
{
	int l,r;
}a[N];
priority_queue<P>lheap;//维护最大l 
priority_queue<P,vector<P>,greater<P> >rheap;//维护最小r 
void init()//初始化 
{
	cnt=now=0;
	while(lheap.size()) lheap.pop();
	while(rheap.size()) rheap.pop();
	for(int i=1;i<=n;i++)
	{
		lheap.push(make_pair(a[i].l,i));
		rheap.push(make_pair(a[i].r,i));
		vst[i]=0;
	}
}
int findl()//向左走并计算代价 
{
	int res=0;
	int val=lheap.top().first,pos=lheap.top().second;
	lheap.pop();
	while(vst[pos]&&lheap.size()) val=lheap.top().first,pos=lheap.top().second,lheap.pop();
	//要一直找到第一个没有用过的区间 
	if(a[pos].l<=now&&now<=a[pos].r) return 0;//如果在里面就跳过计算 
	res=a[pos].l-now;//计算代价 
	now=a[pos].l;//更新now 
	vst[pos]=1;//打标记 
	return res;
}
int findr()//向右走并计算代价 
{
	int res=0;
	int val=rheap.top().first,pos=rheap.top().second;
	rheap.pop();
	while(vst[pos]&&rheap.size()) val=rheap.top().first,pos=rheap.top().second,rheap.pop();

	if(a[pos].l<=now&&now<=a[pos].r) return 0;
	res=now-a[pos].r;
	now=a[pos].r;
	vst[pos]=1;
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d",&a[i].l,&a[i].r);
	
	init();
	while(++cnt<=n)//第一步向左 
	{
		if(cnt&1) ans1+=findl();
		else ans1+=findr();
	}
	ans1+=abs(now);
	
	init();
	while(++cnt<=n)//第一步向右
	{
		if(cnt&1) ans2+=findr();
		else ans2+=findl();
	}
	ans2+=abs(now);
	printf("%lld",max(ans1,ans2));//两者取大的 
	return 0;
}
```

---

## 作者：xkai (赞：4)

一个经典套路是，对每个最小单位找到它对答案贡献的一个上界，然后去看是不是能同时满足所有单位的上界。

那么对于这道题，每个长度为 $1$ 的线段，最多会贡献 $2\times \operatorname{min}\{preR,sufL\}$ 次。其中 $preR$ 表示在这条线段左边的右端点的数量，$sufL$ 表示这条线段右边的左端点数量。

是否能达到这个上界？显然，每次不断地找最左的右端点，或是最右的左端点即可满足这个上界。

然后就前缀和统计即可。复杂度 $O(n+A)$。



```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200010;
int n,pre[N],suf[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n;
	suf[0+D]++,pre[0+D]++;
	for(int i=1;i<=n;i++){
		int l,r;cin>>l>>r;
		suf[l+D]++,pre[r+D]++;
	}
	for(int i=-1e5;i<=1e5;i++)pre[i+D]+=pre[i-1+D];
	for(int i=1e5;i>=-1e5;i--)suf[i+D]+=suf[i+1+D];
	ll ans=0;
	for(int i=-1e5;i<=1e5;i++)ans+=min(pre[i+D],suf[i+1+D])*2;
	cout<<ans;
}

```


---

## 作者：Time_tears (赞：3)

抢到第一篇题解。

我们可以贪心的发现 $A$ 的策略是固定的，就是每次走到区间的两个端点中离自己较近的那个，若在区间中则不动，最后走一步到 $0$ 。

那么现在就等价于 $B$ 要安排一个顺序使得 $A$ 走的距离尽量远。

我们可以贪心的来考虑，$B$ 一定是让 $A$ 走到一个 $r$ 最小的点，然后走到一个 $l$ 最大的点，然后走到一个 $r$ 最小的点......以此类推下去，因为只有这样的反复横跳能够使得 $A$ 走的距离尽量的远。

所以 $B$ 现在的策略就是：

1.让 $A$ 走到一个 $r$ 最小的点，然后走到一个 $l$ 最大的点......

2.让 $A$ 走到一个 $l$ 最大的点，然后走到一个 $r$ 最小的点......

所以根据这两种情况分别模拟两次即可，复杂度是排序的复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
long long ans1,ans2;
int n,vis[N];
struct node {
	int l,r,id;
} a[N],b[N];
bool cmp1(node x,node y) {
	return x.l>y.l;
}
bool cmp2(node x,node y) {
	return x.r<y.r;
}
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f|=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int Abs(int x) {
	return x<0?-x:x;
}
int Get(int &x,node y,int tmp=0) {
	if(y.l<=x&&x<=y.r)return 0;
	if(x<y.l)return tmp=x,x=y.l,y.l-tmp;
	return tmp=x,x=y.r,tmp-y.r;
}
int main() {
	n=read();
	for(int i=1; i<=n; ++i)a[i].l=b[i].l=read(),a[i].r=b[i].r=read(),a[i].id=b[i].id=i;
	sort(a+1,a+n+1,cmp1),sort(b+1,b+n+1,cmp2);
	int las=0,now=0,i=1,j=1;
	while(++now<=n) {
		if(now&1) {
			while(vis[a[i].id])++i;
			ans1=(ans1+Get(las,a[i])),vis[a[i].id]=1;
		} else {
			while(vis[b[j].id])++j;
			ans1=(ans1+Get(las,b[j])),vis[b[j].id]=1;
		}
	}
	ans1=ans1+Abs(las);
	for(int t=1; t<=n; ++t)vis[t]=0;
	now=las=0,i=j=1;
	while(++now<=n) {
		if(now&1) {
			while(vis[b[j].id])++j;
			ans2=(ans2+Get(las,b[j])),vis[b[j].id]=1;
		} else {
			while(vis[a[i].id])++i;
			ans2=(ans2+Get(las,a[i])),vis[a[i].id]=1;
		}
	}
	ans2=ans2+Abs(las);
	cout<<max(ans1,ans2);
	return 0;
}
```


---

## 作者：qnqfff (赞：1)

### 思路

容易发现A如果在这个区间就不会动，否则去离他近的那个端点。

而B一定会交替的选择左端点最大的区间和右端点最小的区间，因为这样子A就会重复走很多路程，但你不知道一开始是选左端点最大的还是右端点最小的，因此分成两种情况，最后取个 $\max$ 就行了。

考虑使用 $\operatorname{set}$ 维护左端点和右端点，这是简单的，每次直接更新A的位置即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,l[100010],r[100010];set<array<int,2>>L,R,_L,_R;
int calc(int now,int i){return (l[i]<=now&&now<=r[i]?0:now<l[i]?l[i]-now:now-r[i]);}
void upd(int &now,int i){(l[i]<=now&&now<=r[i]?1:now<l[i]?now=l[i]:now=r[i]);}
signed main(){
	n=read();for(int i=1;i<=n;i++) l[i]=read(),r[i]=read(),L.insert({l[i],i}),R.insert({r[i],i}),_L.insert({l[i],i}),_R.insert({r[i],i});
	int A=0,B=0,a=0,b=0;for(int i=1;i<=n;i++){
		if(i&1){int x=(*R.begin())[1],y=(*_L.rbegin())[1];A+=calc(a,x);upd(a,x);B+=calc(b,y);upd(b,y);L.erase({l[x],x});R.erase({r[x],x});_L.erase({l[y],y});_R.erase({r[y],y});}
		else{int x=(*L.rbegin())[1],y=(*_R.begin())[1];A+=calc(a,x);upd(a,x);B+=calc(b,y);upd(b,y);L.erase({l[x],x});R.erase({r[x],x});_L.erase({l[y],y});_R.erase({r[y],y});}
	}cout<<max(A+abs(a),B+abs(b));
	return 0;
}
```

---

## 作者：Conan15 (赞：0)

根据贪心，容易想到 A 的移动方式是固定的：

- 如果在线段外，每次移动到距离目标线段更近的端点。
- 如果在线段内就不移动。

考虑 B 要如何设计顺序才能让 A 移动得最远，显然根据贪心是左右反复横跳。\
但是第一步往左还是往右并不确定，所以需要枚举。\
于是用一个堆维护左右端点的最大值、最小值即可，每次取出最远的跳过去。\
注意线段不能重复访问，所以要用数组记录是否访问过。

```cpp
#include <bits/stdc++.h>
#define PII pair<int, int>
using namespace std;
const int N = 1e5 + 15;
int n, l[N], r[N];
priority_queue< PII > q[2];   // 0 右；1 左

bool st[N];
long long move(long long &now, int id) {
    if (l[id] <= now && now <= r[id]) return 0;
    int dis = 0;
    if (now < l[id]) dis = l[id] - now, now = l[id];
    if (now > r[id]) dis = now - r[id], now = r[id];
    return dis;
}

long long solve(int t) { // 0 先左；1 先右
    while (q[0].size()) q[0].pop();
    while (q[1].size()) q[1].pop();
    for (int i = 1; i <= n; i++) st[i] = 0;
    long long dis = 0, pos = 0;
    for (int i = 1; i <= n; i++)
        q[0].push({-r[i], i}), q[1].push({l[i], i});
    for (int i = 1; i <= n && q[0].size() && q[1].size(); i++) {
        if (!t) {   //往左走
            while (q[0].size()) {
                int id = q[0].top().second; q[0].pop();
                if (st[id]) continue;
                st[id] = 1;
                dis += move(pos, id);
                break;
            }
        } else {    //往右走
            while (q[1].size()) {
                int id = q[1].top().second; q[1].pop();
                if (st[id]) continue;
                st[id] = 1;
                dis += move(pos, id);
                break;
            }
        }
        t ^= 1;
    }
    return dis + abs(pos);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
    printf("%lld\n", max(solve(0), solve(1)) );
    return 0;
}
```

---

## 作者：wangyishan (赞：0)

# [AGC025C] Interval Game 题解

## [题意 Link](https://www.luogu.com.cn/problem/AT_agc025_c)

- 数轴上有 $N$ 个闭区间，第 $i$ 个闭区间为 $[L_i,R_i]$.
- A 和 B 玩游戏，A 初始在原点 $0$，每次 B 选择一个还未选过的区间，A 要走到任意一个属于该区间的点。最后 A 要回到 $0$.
- A 希望最小化自己走过的路程，B 希望最大化 A 走过的路程，在两者都采取最优策略的情况下，求 A 走过的路程。
- $1\le N\le 10^5$，$-10^5\le L_i<R_i\le 10^5$.

## 题解

这里思路有参考 [@xkai 大佬的题解](https://www.luogu.com.cn/blog/xukai250/solution-at-agc025-c),orz.

我们考虑每一个单位长度长度线段的贡献，发现最多会贡献 $2\times\min{pre,suf}$ 次，其中 $pre$ 表示左边的右端点数量，$suf$ 表示右边的左端点数量，并且一定可以到达这个上界。

这是为什么呢？

我们贪心的考虑 A 的策略，发现无外乎三种可能：
- 区间左端点在当前端点右侧，此时只需要挪动到左端点即可。
- 区间包含当前端点，此时不用动。
- 区间右端点在当前端点左侧，此时只需要挪动到右端点即可。

那么如何卡紧这个上界呢？

显然，每次不断找最左的右端点或最右的左端点即可。此时可以确保每条线段都经过了最多次。

时间复杂度 $O(t+n)$，$t$ 表示区间长度。离散化后可以到 $10^{18}$。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define D 100001
//注意坐标可能为负
const int N=200010;
int n,pre[N],suf[N];
int main(){
    cin>>n;
    suf[0+D]++,pre[0+D]++;//最后要回到起点
    for(int i=1;i<=n;i++){
        int l,r;cin>>l>>r;
        suf[l+D]++,pre[r+D]++;
    }
    for(int i=-1e5;i<=1e5;i++)pre[i+D]+=pre[i-1+D];//前缀和统计
    for(int i=1e5;i>=-1e5;i--)suf[i+D]+=suf[i+1+D];//后缀和统计
    ll ans=0;
    for(int i=-1e5;i<=1e5;i++)ans+=min(pre[i+D],suf[i+1+D])*2;
    cout<<ans;
    return 0;
}
```

---

