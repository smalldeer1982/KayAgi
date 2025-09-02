# [USACO24FEB] Quantum Moochanics G

## 题目描述

在空闲时间，Bessie 喜欢涉猎实验物理。她最近发现了一对新的亚原子粒子，命名为**哞微子**和**反哞微子**。如同标准的[物质-反物质对](https://baike.baidu.com/item/%E5%8F%8D%E7%89%A9%E8%B4%A8/115035)，哞微子和反哞微子相遇时会相互湮灭并消失。但这些粒子的独特之处在于，每当 Bessie 看向它们时它们就会改变运动方向（同时保持相同的速率）。

在她最新的实验中，Bessie 将**偶数** $N$（$2\le N\le 2\cdot 10^5$）个这些粒子排成一行。这一行的左端以哞微子开始，然后在两种类型的粒子之间交替，第 $i$ 个粒子位于位置 $p_i$（$0\le p_1<\cdots <p_N\le 10^{18}$）。哞微子初始时**向右**运动而反哞微子初始时**向左**运动，其中第 $i$ 个粒子以每秒 $s_i$ 单位的恒定速率运动（$1\le s_i\le 10^9$）。

Bessie 在以下时刻进行观察：

- 首先是实验开始后 $1$ 秒。
- 然后是第一次观察后 $2$ 秒。
- 然后是第二次观察后 $3$ 秒。
- $\ldots \ldots$
- 然后是第 $n$ 次观察后 $n+1$ 秒。

在每次观察中，Bessie 都会记下哪些粒子消失了。

这个实验可能需要非常长的时间才能完成，所以 Bessie 想要首先模拟一下它的结果。根据实验设置，请帮助 Bessie 求出她何时（即**观察次数**）会观察到各个粒子消失！可以证明，所有粒子最终都会消失。

## 说明/提示

### 样例解释 1

对于第一个测试用例，Bessie 在前 $8$ 次观察中观察到以下情况：

- 哞微子（初始时向右运动）出现在位置 $2\to 0\to 3\to −1\to 4\to −2\to 5\to −3$。
- 反哞微子（初始时向左运动）出现在位置 $10\to 12\to 9\to 13\to 8\to 14\to 7\to 15$。

然后恰好在观察 $9$ 时，两个粒子在位置 $6$ 相遇并相互湮灭。

对于第二个测试用例，反哞微子的初始位置更靠右 $1$
单位，从而两个粒子在观察 $11$ 之前半秒在位置 $6.5$ 相遇。

注意我们只关心观察次数，不关心时刻或位置。

### 样例解释 2

对于第一个测试用例：

- 最左边的两个粒子恰好在观察 $1$ 时在位置 $2$ 相遇。
- 最右边的两个粒子在观察 $3$ 之前半秒在位置 $6.5$ 相遇。

### 测试点性质

- 测试点 $3$：$N=2$。
- 测试点 $4$：$N\le 2000$，且对于所有粒子，$p_i\le 10^4$。
- 测试点 $5-7$：$N\le 2000$。
- 测试点 $8-12$：没有额外限制。

## 样例 #1

### 输入

```
4
2
1 11
1 1
2
1 12
1 1
2
1 11
4 6
2
1 11
4 5```

### 输出

```
9 9
11 11
1 1
3 3```

## 样例 #2

### 输入

```
2
4
1 3 5 8
1 1 1 1
4
1 4 5 8
1 1 1 1```

### 输出

```
1 1 3 3
7 2 2 7```

# 题解

## 作者：__zhanghuanrui__ (赞：8)

# 题意概述

* 有 $n$（$n$ 为偶数）个粒子排成一行，其中从左往右数奇数位置的粒子是**哞微子**，其余的是**反哞微子**。

* 每个微子有一个位置 $p_i$ 和初速度 $s_i$（单位长度每秒）。初始时，所有**哞微子**向右运动，所有**反哞微子**向左运动。保证 $p_i$ 单调增。

* 如果一个**哞微子**和一个**反哞微子**相撞，它们就会立即湮灭而消失。

* Bessie 在这些粒子开始运动后，先会等待 $1$ 秒再去观察它们，然后**再**等待 $2$ 秒再去观察它们，然后**再**等待 $3$ 秒再去观察它们，以此类推。

* 观察可以认为是瞬间完成的。每次观察后，所有还存在的粒子都会瞬间反转自己的运动方向。

* 你需要求出对于每个粒子，它会在第几次观察时**第一次**无法被观察到（可以认为是在同一时刻，粒子先湮灭，Bessie 再观察）。

# 分析

首先，我们发现，如果两个粒子发生了湮灭，在湮灭前的瞬间它们之间一定没有其它粒子存在（否则这两个粒子会先撞上它们之间的那些粒子）。因此，我们可以先计算出相邻两个粒子发生湮灭的时间，那么第一次湮灭发生的时刻就是这些时间中的最小值。

接下来，删掉这两个湮灭的粒子，那么它们两旁的粒子（如果有的话）就变得相邻了。计算这两个粒子发生碰撞的时间，然后再和之前的还**有效**的时间一起求出最小值，就得到了第二次发生湮灭的时刻。反复这个过程，就可以得到答案。

这个过程可以用优先队列实现。那么这个问题的核心就在于，假定没有其他粒子的干扰，如何计算给定两个粒子发生湮灭的时刻。

题目描述的粒子移动方式十分诡异。对于一个**哞微子**，如果它没有湮灭，它会先向右移动 $1$ 秒，然后向左移动 $2$ 秒，再向右移动 $3$ 秒……对于**反哞微子**的情况恰好相反。

不难发现，这种移动方式等价于所有粒子同时沿自己的方向移动 $1$ 秒，然后回到原位置（假设不考虑它们的湮灭），再反方向移动 $1$ 秒，然后回到原位，再按原方向移动 $2$ 秒，然后回到原位……

也就是说，对于一个**哞微子**，在第 $2i-1$ 次观察，它相对原位置向右移动 $i \times s$ 个单位长度，在第 $2i$ 次观察，相对原位置向左移动 $i \times s$ 个单位长度，这里令 $s$ 为它的速度；对于**反哞微子**方向恰好相反。

我们要计算一个**哞微子**和一个**反哞微子**发生碰撞所需要的**观察次数** $t$。不难发现，如果**哞微子**在**反哞微子**的左边，只有可能在奇数次观察前相撞；否则就只有可能在偶数次观察前相撞。

确定了奇偶性后，我们只需要计算上文的 $i$ 的值就行了。这是一个**相遇问题**，我们要求的 $i$ 就是满足 $i \times (s_1+s_2) \ge dis$ 的最小的正整数，其中 $s_1$ 和 $s_2$ 分别为**哞微子**和**反哞微子**的速度，$dis$ 为它们间的距离。

解不等式，得到 $i = \lceil \frac{dis}{s_1+s_2} \rceil$。这样，我们就可以用 $O(1)$ 的时间复杂度得出两个粒子相撞的时刻。

还有最后一个问题，如何快速得到和一个粒子相邻的**还存在**的粒子位置？这可以用链表 $O(1)$ 做到。

结合前文的优先队列，优先队列中初始只有 $O(n)$ 个元素，最多删除 $O(n)$ 次，每次删除最多只会将 $1$ 个元素加入优先队列，因此每组测试数据的时间复杂度为 $O(n \log n)$。

# 代码

[评测记录](https://www.luogu.com.cn/record/148485364)

总时间：646 ms

单个测试点最慢时间：122 ms

占用空间：15.04 MB

```c
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;
int p[200010],v[200010];//粒子的位置和速度
int nxt[200010],pre[200010];//链表
int ans[200010];
void del(int x)//删除链表元素
{
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
}
struct info
{
	int x,y;//两个粒子的编号
	int time;//它们相撞的时刻
	bool operator < (const info a) const
	{
		return time>a.time;
	}
};
inline info Info(int x,int y,int time){return (info){x,y,time};}
priority_queue<info> q;
inline int ceil(int x,int y){return x/y+!!(x%y);}//等价于ceil(1.0*x/y)，这里是为了避免精度误差
int calc(int x,int y)//返回第 i 个粒子和第 j 个粒子相撞是在第几次观察前发生的
{
	return 2*(ceil(p[y]-p[x],v[x]+v[y]))-x%2;
}
void initialize()//初始化链表、优先队列等
{
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=n;i++) nxt[i]=i+1,pre[i]=i-1;
	while(!q.empty()) q.pop();
}
void solve()
{
	cin>>n;
	initialize();
	for(int i=1;i<=n;i++) scanf("%lld",&p[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
	for(int i=1;i<n;i++) q.push(Info(i,i+1,calc(i,i+1)));//初始时有 n-1 对可能相撞的粒子
	info tmp;
	while(!q.empty())
	{
		tmp=q.top();q.pop();//每次取出最先碰撞的粒子
		if(ans[tmp.x] || ans[tmp.y]) continue;//如果它们之一已经不存在，就跳过它
		ans[tmp.x]=ans[tmp.y]=tmp.time;
		if(pre[tmp.x]>=1 && nxt[tmp.y]<=n)//产生了一对相邻粒子
		{
			q.push(Info(pre[tmp.x],nxt[tmp.y],calc(pre[tmp.x],nxt[tmp.y])));
		}
		del(tmp.x);del(tmp.y);
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld",ans[i]);
		if(i<n) printf(" ");//USACO的评测方式是文本比较，输出多余的空格或换行都不行
	}
	if(t) printf("\n");
}
signed main()
{
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：_droplet_ (赞：5)

## 题目分析

对于某一时刻，第一个碰撞的两点只能是两个相邻的点。

此时我们可以通过双端链表存储没有湮灭的点。

通过题目描述，点的运动轨迹可以理解为先向一边 $s_i$ 单位，回到原来的点后再向另一边 $s_i$ 单位，向这一边 $2 \times s_i$ 单位，回到原来的点后再向另一边 $2 \times s_i$ 单位，以此类推，我们可以 $O(1)$ 的时间复杂度下求出任意两点的湮灭时间。

### 第一版思路

每次暴力求出任意两相邻点的湮灭时间，用双端链表删点。

### 优化

若直接暴力枚举的话只能过测试点 $1-7$，考虑用更快地方法算出湮灭时间。

注意到上方思路可转化为，每次要求一个集合的最小值，加入一个值，删除最小值，可以注意到可以用堆维护。

### 第二版思路

使用优先队列维护两相邻点湮灭时间，每次从队列重取点并加入左右点，用双端链表删点。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
struct node{
	long long vl,spd;
	int id,l,r;
	bool tn;
}a[N];
struct pq{
	int x,y;
	long long tm;
	friend bool operator<(pq a,pq b){
		return a.tm>b.tm;
	}
};
int n;
long long ans[N];
priority_queue<pq>q;

__inline long work(int x,int y){ // 任意两点的湮灭时间
	long long t=0;
    t=((a[y].vl-a[x].vl-1)/(a[x].spd+a[y].spd)+1)<<1;
    if(a[x].tn) t--;
    return t;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		while(!q.empty()) q.pop();
		memset(ans,0,sizeof(ans));
		a[0].r=1,a[n+1].l=n;
		for(int i=1;i<=n;i++) a[i].r=i+1,a[i].l=i-1;
		for(int i=1;i<=n;i++) cin>>a[i].vl,a[i].tn=i&1;
		for(int i=1;i<=n;i++) cin>>a[i].spd,a[i].id=i;
        for(int i=a[0].r;a[i].r!=n+1;i=a[i].r){
            int x=i,y=a[i].r;
			long long t=work(x,y);
            q.push({x,y,t});
        }
		while(1){
			auto [x,y,t]=q.top();
			q.pop();
			if(ans[x]||ans[y]) continue; // 若该点对其中一点已经被删，该点对不存在，舍去
			ans[x]=ans[y]=t;
			a[a[x].l].r=a[y].r;
			a[a[y].r].l=a[x].l;
			if(a[0].r==n+1) break;
			if(a[x].l==0||a[y].r==n+1) continue;
			long long nt=work(a[x].l,a[y].r);
			q.push({a[x].l,a[y].r,nt});
		}
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：4)

本题看上去有点吓人，其实没那么难。

容易发现，只会有某时相邻的两个粒子才会碰撞。考虑使用优先队列作为粒子碰撞的“事件队列”，并同时使用双向链表维护每个粒子与哪两个粒子是相邻的。

大体思路就是这样，但还有一个问题：如何计算两个粒子第几次观察后会碰撞？

对于每个粒子（以哞微子为例），先向右运动 $1$ 秒，再向左运动 $2$ 秒，再向右运动 $3$ 秒，再向左运动 $4$ 秒……拿出草稿纸画一下，其实刚才运动的本质是，Bessie 第 $1$ 次观察时位于 $p+s$，第 $2$ 次观察时位于 $p-s$，然后是 $p+2s$，然后 $p-2s$……

可以得到结论：第 $2k-1$ 次观察，位于 $p+ks$；第 $2k$ 次观察，位于 $p-ks$。反哞微子反之。给定两个粒子之间的距离，就可以解出 $k$。如果左边的是哞微子，答案就是 $2k-1$；如果左边的是反微子，答案就是 $2k$。

```cpp
// Title:  Quantum Moochanics
// Source: USACO24FEB Gold
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010;
using namespace std;

int n, pre[N], nxt[N]; ll p[N], s[N], res[N];
void del(int i)
{
	nxt[pre[i]]=nxt[i], pre[nxt[i]]=pre[i];
}
ll calc(int i, int j)
{
	return (p[j]-p[i]+s[i]+s[j]-1)/(s[i]+s[j])*2-(i&1);
}
struct crash
{
	int i, j; ll tim;
	bool operator <(crash a) const {return tim>a.tim;}
};
priority_queue<crash> q;
void solve()
{
	scanf("%d", &n);
	rep(i, 1, n) scanf("%lld", p+i), pre[i]=i-1, nxt[i]=i+1, res[i]=0;
	nxt[n]=0;
	rep(i, 1, n) scanf("%lld", s+i);
	rep(i, 1, n-1) q.push({i, i+1, calc(i, i+1)});
	while(q.size())
	{
		auto [i,j,tim]=q.top(); q.pop();
		if(res[i] || res[j]) continue;
		res[i]=res[j]=tim;
		int ii=pre[i], jj=nxt[j];
		if(ii && jj) q.push({ii, jj, calc(ii, jj)});
		del(i), del(j);
	}
	rep(i, 1, n) printf("%lld%c", res[i], " \n"[i==n]);
}

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) solve();
	
	return 0;
}
```

---

## 作者：Frozen_Ladybug (赞：2)

虽然这道题题目描述中没有提及到相同的粒子相遇后会发生什么，这种情况是不可能发生的：

- 粒子成对相遇。
- 两个粒子不可能相遇，直到它们之间的所有粒子都消失了。
- 但是，同种类型的粒子是从奇数个粒子开始的。

所以每次相遇只可能是哞微子和反哞微子相遇。

为了方便，将哞微子记为 +1，反哞微子记为 -1。

---
### P1：对于两个不同状态的粒子

两粒子相遇当且仅当它们相向而行。即在观测中，它们一定在一次奇数编号的观测中消失。

在第 $k$ 次奇数编号的观测中，一个 +1 会移动 $k\cdot s_1$ 个单位，一个 -1 会移动 $k\cdot s_2$ 个单位。即在第 $\lceil\frac{p_2-p_1}{s_1+s_2}\rceil$ 次奇数观测时，两粒子消失。

于是可以得出以下代码计算两粒子消失的时间：

```cpp
ll compute_meeting_time(int a,int b) {
    ll dist=p[b]-p[a];//间距
    ll speed_sum=s[a]+s[b];//相对速度
    return 2*((dist+speed_sum-1)/speed_sum)-(a%2==0);
}
```
---
### P2：$O(N\cdot\max\{p_i\})$ 解法

模拟即可。

---
### P3：$O(N^2)$ 解法

暴力模拟的问题在于，可能会有很长一段时间的观察，但什么也没发生（例如，如果粒子都相距很远，但速度都很低）。

更有效的算法工作如下：

- 迭代所有相邻粒子对，并使用上面的函数计算它们何时相遇。
- 选择最早相遇的一对，任意分割。
- 存储该对的答案，并将它们从粒子线中移除。
- 重复操作，直到所有颗粒都被清除。

该程序会运行 $\frac{N}{2}$ 次，每次复杂度为 $O(N)$，使得总复杂度为 $O(N^2)$。

---
### P4：$O(N\log N)$ 解法和代码

我们可以通过注意到每次迭代最多改变 4 对粒子对来进一步改进该算法。设四个粒子 $o_1,o_2,o_3,o_4$ 依次相邻。现在我们不需要挨个考虑，只需考虑 $(o_1,o_4)$ 这一组。

这样，我们可以用一个优先队列，依据相遇时间对相邻两个粒子进行排序。同时用一个映射对其进行优化，用来查找哪个粒子与其直接相邻。

这样可以将复杂度降低为 $O(N\log N)$，足够通过这道题的时间限制。

代码：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll p[200000],s[200000],ans[200000];
pair<int,int> adj[200000];
ll compute_meeting_time(int a,int b) {
    ll dist=p[b]-p[a];
    ll speed_sum=s[a]+s[b];
    return 2*((dist+speed_sum-1)/speed_sum)-(a%2==0);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=0;i<n;i++) cin>>p[i];
        for(int i=0;i<n;i++) cin>>s[i];
        for(int i=0;i<n;i++) {
            adj[i]={i-1,i+1};
            ans[i]=0;
        }
        priority_queue<pair<ll, pair<int, int>>> pq;
        for(int i=1;i<n;i++)
            pq.push({-compute_meeting_time(i-1,i),{i-1,i}});//将相邻不同粒子的相遇时间推入队列
        while(pq.size()){
            pair<ll, pair<int, int>> next_meeting=pq.top();
            pq.pop();
            ll meeting_time=next_meeting.first;//建立映射，记录相遇时间
            pair<int,int> cows=next_meeting.second;
            if(ans[cows.first]||ans[cows.second]) continue;
            ans[cows.first]=ans[cows.second]=-meeting_time;
            if(cows.first!=0&&cows.second!=n-1){
                int prv=adj[cows.first].first;
                int nxt=adj[cows.second].second;
                adj[prv].second=nxt;
                adj[nxt].first=prv;//配对后记录前后两个粒子，再把他们推入队列
                pq.push({-compute_meeting_time(prv,nxt),{prv,nxt}});
            }
        }
        for(int i=0;i<n;i++)
            cout<<ans[i]<<" \n"[i==n-1];
    }
    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：1)

突然觉的和真和 $486$ 长得好像啊。

考虑通过另外一种方式看待这种粒子的运动，先考虑**哞微子**的运动情况。

首先**哞微子**先向右边移送 $s_i$，接下来想左边移动 $2\times s_i$ 也就是移动到了左边 $s_i$ 的位置。

接下来再移动到右边 $2\times s_i$ 的位置，然后是左边 $2\times s_i$ 的位置，以此类推。

所以第 $i$ 时刻，**哞微子**的位置就是：

$$\begin{aligned}
P(i,T)=
\left\{\begin{matrix}
p_i+\dfrac{T+1}{2}\times s_i & T \text{ is odd}\\ \\
p_i-\dfrac{T}{2}\times s_i & T \text{ is even}
\end{matrix}\right.
\end{aligned}$$

同样的，**反哞微子**的位置就是：

$$\begin{aligned}
P(i,T)=
\left\{\begin{matrix}
p_i-\dfrac{T+1}{2}\times s_i& T\text{ is odd}\\ \\
p_i+\dfrac{T}{2}\times s_i& T \text{ is even}\end{matrix}\right.
\end{aligned}$$

那么考虑再只有两个不同微子 $x,y$ 且 $p_x\le p_y$ 时 $\lceil\dfrac{T}{2}\rceil$ 的值就可以计算出 $T$ 的值了。

也就是解下面不等式中 $\lceil\dfrac{T}{2}\rceil$ 的最小整数解：

$$\lceil \dfrac{T}{2}\rceil \times (s_x+s_y)\ge p_y-p_x$$

于是得到：

$$\lceil\dfrac{T}{2}\rceil=\lceil\dfrac{p_y-p_x}{s_x+s_y}\rceil$$

最后根据 $\lceil \dfrac{T}{2}\rceil$ 的值把 $T$ 计算出来就行了，具体的：

$$\begin{aligned}T=
\left\{\begin{matrix}
\lceil\dfrac{T}{2}\rceil\times 2-1& x\text{ is Mootrinos}\\ \\
\lceil\dfrac{T}{2}\rceil\times 2&\text{Otherwise}\end{matrix}\right.
\end{aligned}$$

于是我们把相邻两个微子的相遇时间丢进一个优先队列里面，动态的更新新产生的碰撞就行了。

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<bitset>
#define int long long
using namespace std;
const int N=2e5+5;
int n,ans[N],p[N],v[N],fr[N],bk[N];
struct node{int x,y,tim;friend bool operator<(const node a,const node b){return a.tim>b.tim;}}top;
int ceil(int x,int y){return x/y+!!(x%y);}
node F(int x,int y){return {x,y,ceil(p[y]-p[x],v[x]+v[y])*2-(x&1)};}
priority_queue<node>q;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i],fr[i]=i-1,bk[i]=i+1;
	for(int i=1;i<=n;i++) cin>>v[i],ans[i]=0;
	for(int i=1;i<n;i++) q.push(F(i,i+1));
	for(int i=1;i*2<=n;i++){
		do{top=q.top(),q.pop();}while(ans[top.x]||ans[top.y]);
		ans[top.x]=ans[top.y]=top.tim;
		if(fr[top.x]&&bk[top.y]!=n+1) q.push(F(fr[top.x],bk[top.y]));
		bk[fr[top.x]]=bk[top.y],fr[bk[top.y]]=fr[top.x];
	}
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：HYdroKomide (赞：1)

场上爆零时隔近半年后回来补题。

### 题意：

有一些粒子，以不同速率在数轴上移动。每一个粒子与相邻粒子以相反方向运动，相邻两个粒子碰撞会消失。每一次观察会使所有粒子方向改变，观察间隔时间呈等差数列递增，问每一个粒子在第几次观察时消失。

### 思路：

乍一看题意似乎比较劝退，不妨先观察每个粒子的运动轨迹。

对于一个正粒子，设其运动速度为 $s_i$，则它在第一次观察时到达自己初始坐标右侧 $s_i$ 距离，第二次到达初始坐标左侧 $s_i$ 距离，第三次到达初始坐标右侧 $2\times s_i$ 距离，第三次到达初始坐标左侧 $2\times s_i$ 距离，以此类推。

可以推出一个形式化的式子，在第 $k$ 次观察时：

$$
pos=\left\{
\begin{matrix}
 p_i-s_i\times \dfrac{k}{2}\ (k\bmod 2=0) \\
 \\
 p_i+s_i\times \dfrac{k+1}{2}\ (k\bmod 2=1) 
\end{matrix}
\right.
$$

对于反粒子同理，只是运动方向相反。

不考虑其它粒子的影响，当一次观察时，只要相邻两个粒子运动路径重叠，它们就会消失。我们考虑一正一反两个粒子 $i$ 和 $j$，$p_i<p_j$，可以计算出它们在不受影响的情况下何时消失。

$$
t=\left\{
\begin{matrix}
 \lceil\dfrac{a_j-a_i}{s_i+s_j}\rceil\times 2\ (i\ 是反粒子) \\
 \\
 \lceil\dfrac{a_j-a_i}{s_i+s_j}\rceil\times 2-1\ (i\ 是正粒子) 
\end{matrix}
\right.
$$

具体步骤请读者自证。

但是粒子湮灭有先后顺序问题，我们不得不采用一些方式存储它们湮灭的先后顺序。考虑使用一个堆来存储。

由于初始位置相邻的粒子肯定最先湮灭，我们不妨先将初始每对相邻粒子的湮灭时间都存入堆，存湮灭时间和两个粒子编号，以湮灭时间为关键字排序。每次查询堆顶将两个粒子删除，并将这两个粒子左右两个粒子的湮灭时间存入堆中。如果堆顶两个粒子中的一个已经删除就直接跳过本次查询。

简单来讲，可以通过一个堆，保证在每次湮灭进行之后，我们都能够知道下一个湮灭的会是谁。

但是，如果每次湮灭都暴力查找左侧最近的粒子和右侧最近的粒子，能被手造数据卡到 $O(n^2)$。因此，我们需要维护一个动态的数组，存储每个粒子当前时间左右相邻的粒子是哪一个。这样可以做到每次湮灭 $O(1)$ 修改以及 $O(1)$ 查询。

总复杂度 $O(n\log n)$。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int N=2e5+5;
int t,n,s[N],pre[N],pos[N];
long long a[N],ans[N];//注意数据范围很大，要开long long
bool vis[N];
struct COLLAPSE{
	int l,r;
	long long tim;
}time[N];
bool operator>(COLLAPSE x,COLLAPSE y){return x.tim>y.tim;}
priority_queue<COLLAPSE,vector<COLLAPSE>,greater<COLLAPSE> >q;//优先队列实现堆
int main(){
	scanf("%d",&t);
	while(t--){
		memset(vis,false,sizeof(vis));//多测清空
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),pre[i]=i-1,pos[i]=i+1;//预处理一下左右相邻的粒子
		for(int i=1;i<=n;i++)scanf("%d",&s[i]);
		pre[1]=0,pos[n]=0;//边缘设成0
		for(int i=1;i<n;i++){
			time[i].tim=ceil((double)(a[i+1]-a[i])/(double)(s[i]+s[i+1]))*2;//相邻粒子计算湮灭时间推入堆中
			time[i].l=i;
			time[i].r=i+1;
			if(i%2==1)time[i].tim--;//编号奇数为正粒子
			q.push(time[i]);
		}
		while(!q.empty()){
			COLLAPSE u=q.top();
			q.pop();
			int x=u.l,y=u.r;
			if(vis[x]||vis[y])continue;//排除其中一个粒子已经湮灭的情况
			vis[x]=vis[y]=true;
			ans[x]=ans[y]=u.tim;
			if(pre[x]>0)pos[pre[x]]=pos[y];
			if(pos[y]>0)pre[pos[y]]=pre[x];//更改左右相邻的粒子编号
			if(pos[y]!=0&&pre[x]!=0){
				long long newval=ceil((double)(a[pos[y]]-a[pre[x]])/(double)(s[pos[y]]+s[pre[x]]))*2;
				if(pre[x]%2==1)newval--;
				time[pre[x]].r=pos[y];
				time[pre[x]].tim=newval;
				q.push(time[pre[x]]);//计算并将新值推入堆中
			}
		}
		for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
		puts("");
	}
	return 0;
}
```

### THE END

---

## 作者：Error_Eric (赞：1)

### Statement

[link](https://www.luogu.com.cn/problem/P10195).

### Sol

注意到我们知道两个粒子的初始状态后可以 $O(1)$ 求出他们如果会相互湮灭，在第几个观察次数后会湮灭。

具体地，如果两者初始相向而行，则在第 $\lceil \dfrac{2(p_r-p_l)}{v_r+v_l}\rceil$ 次观察时被发现消失，否则在 $\lceil \dfrac{2(p_r-p_l)}{v_r+v_l}\rceil+1$ 次观察时被发现消失。

而湮灭只会发生在直接相邻的两个粒子之间。因此我们可以用维护一个集合，集合中的元素是「间隔」，也即所有直接相邻的粒子对。每次我们取出湮灭最早的粒子对，并且更新这对粒子湮灭后会造成的变化。

例如有 $A,B,C,D,E$ 五个粒子，初始「间隔」集合为 $(A,B)(B,C)(C,D)(D,E)$，若 $B,C$ 湮灭，那么「间隔」集合变为 $(A,D)(D,E)$。

注意到如果我们用 ``set`` 动态维护「间隔」集合和粒子集合可以做到 $O(\log n)$ 更新。那么总复杂度是 $O(\sum n\log n)$，是对的。

### Code

赛时代码，略显丑陋。~~不过全 STL 可读性应该还行罢。~~

``gap`` 为「间隔」，``gaps`` 为「间隔」集合，particles 为粒子集合。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<set>
using namespace std;
typedef long long ll;
const int _=2e5+5;
int t,n;
ll p[_],v[_],ans[_];
struct gap{
    int Lid,Rid;
    ll obsid;
    gap(int L,int R){
        Lid=L,Rid=R,
        obsid=ceil((2.0*(p[R]-p[L]))/(v[L]+v[R])-(L&1));
        if((obsid+Lid)&1) ++obsid;
    }
};
bool operator<(gap ga,gap gb){
    if(ga.obsid==gb.obsid)
        return ga.Lid<gb.Lid;
    return ga.obsid<gb.obsid;
}
set<gap>gaps;
set<int>particles;
typedef set<int>::iterator sit;
sit pre(sit sx){return --sx;}
sit suf(sit sx){return ++sx;}
void mian(){
    gaps.clear(),particles.clear(),
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>p[i];
    for(int i=1;i<=n;i++)
        cin>>v[i];
    for(int i=1;i<=n;i++){
        particles.insert(i);
        if(i^n) 
            gaps.insert({i,i+1});
    }
    while(particles.size()){
        auto u=(*gaps.begin()); 
        auto it=particles.find(u.Lid);
        gaps.erase(gaps.begin());
        if(it!=particles.begin()){
            gaps.erase({*pre(it),*it});
        }
        if(suf(suf(it))!=particles.end()){
            gaps.erase({*suf(it),*suf(suf(it))});
        }
        if(it!=particles.begin()&&suf(suf(it))!=particles.end()){
            gaps.insert({*pre(it),*suf(suf(it))});
        }
        particles.erase(u.Lid),particles.erase(u.Rid),
        ans[u.Lid]=u.obsid,ans[u.Rid]=u.obsid;
    }
    for(int i=1;i<n;i++)
        cout<<ans[i]<<' ';
    cout<<ans[n]<<endl;
}
int main(){
    ios::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)mian();
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

注意到一开始两种粒子交替出现，考虑什么样子的两个粒子可以消除。

显然，消除的两个粒子一定是连续的两个，不然一定会和他旁边的先碰到。

考虑把所有的相邻粒子加入一个小根堆，每次取出最小的元素。因为碰到了就会消除，所以用小根堆维护。

这两个粒子消除之后剩下的粒子仍然符合交替出现的性质，可以继续处理。

删除之后找前后链表维护即可。

时间复杂度 $O(T\times n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=2e5+1;
int T,n,a[N],s[N],vis[N],pre[N],suf[N],res[N];
int get_ceil(int a,int b){
	return(a+b-1)/b;
}
void Main(){
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int> >,greater<tuple<int,int,int> > >q;
    cin>>n;
    for(int i=0;i<=n;i++)
        vis[i]=res[i]=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pre[i]=i-1,suf[i]=i+1;
    }
    pre[1]=suf[n]=-1;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    for(int i=2;i<=n;i++)
        q.push(make_tuple(get_ceil(a[i]-a[i-1],s[i]+s[i-1])*2-((i-1)&1),i-1,i));
    while(!q.empty()){
//        auto[diff,i,j]=q.top();
		auto tp=q.top();int diff=get<0>(tp),i=get<1>(tp),j=get<2>(tp);
        q.pop();
        if(vis[i]||vis[j])
            continue;
        res[i]=res[j]=diff;
        vis[i]=vis[j]=1;
        if(pre[i]!=-1)
            suf[pre[i]]=suf[j];
        if(suf[j]!=-1)
            pre[suf[j]]=pre[i];
        if(pre[i]!=-1&&suf[j]!=-1){
            q.push(make_tuple(get_ceil(a[suf[j]]-a[pre[i]],s[suf[j]]+s[pre[i]])*2-(pre[i]&1),pre[i],suf[j]));
        }
    }
    for(int i=1;i<=n;i++)
        cout<<res[i]<<" \n"[i==n];
    return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr),cout.tie(nullptr); 
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

## 作者：hnczy (赞：0)

我们知道，这题的观察的情况很特殊，可以从这个角度出发，窥探性质。

假设这个点是哞微子，通过模拟容易分析出第一次观察在原点往右一个单位，第二次观察在原点往左一个单位，接着原点往左两个单位，往右两个单位。

这个性质很好，然后我们很容易知道相邻两个肯定是不同的微子，因为两个不同微子相撞后相邻的还是不同的。

这样我们就可以用 $O(1)$ 的时间复杂度来算出任意两个不同微子，相撞的时间。

这个算法也很简单，假设 `a` 为两微子中的哞微子，而 `b` 为反哞微子，则假设 $p_a <p_b $ 则 $t = 2\times \lceil \frac{p_a-p_b}{s_a+s_b} \rceil-1$ ，反之则 $t = 2\times \lceil \frac{p_a-p_b}{s_a+s_b} \rceil$。

那刚好这样的话我们可以想到用一个优先队列来维护 `t` ，将先发生的事件先处理，那此时我们需要一个能快速找到一个点的前驱和后继和单点删除的数据结构，是链表，也可以是 `set` ，反正已经是 $O(n\log n)$ ，随便用哪个不影响事件复杂度。

代码实现：

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2E5+5;
int T;
int p[N],s[N],n,ans[N];
struct P {
	int val,id1,id2;
	bool operator<(const P &a)const {
		return val>a.val ;
	}
};
priority_queue<P>q;
set<int>st;
int solve(int p1,int p2,int s1,int s2,int op) {
	if(op==-1)swap(p1,p2),swap(s1,s2);
	if(p1<p2)return 2*((p2-p1-1)/(s1+s2))+1;
	else return 2*((p1-p2-1)/(s1+s2))+2;
}
// 2*(p1-p2-1)/(s1+s2)+1
// 
//分别表示第一个数的位置,第二个数的位置,两者的速度,第一个是正的还是负的
signed main() {
	scanf("%lld",&T);
	while(T--) {
		while(!q.empty())q.pop();
		st.empty();
		scanf("%lld",&n);
		for(int i=1; i<=n; i++)
			scanf("%lld",p+i);
		for(int i=1; i<=n; i++)
			scanf("%lld",s+i);
		for(int i=1; i<n; i++){
			//cout<<solve(p[i],p[i+1],s[i],s[i+1],((i&1)?1:-1))<<endl;
			q.push({solve(p[i],p[i+1],s[i],s[i+1],((i&1)?1:-1)),i,i+1});
			st.insert(i);
		}st.insert(n);
		int cnt=0;
		while(cnt<n/2){
			int id1=q.top().id1,id2=q.top().id2,val=q.top().val;		
			q.pop();
			if(st.find(id1) == st.end() || st.find(id2)==st.end())continue;
			//cout<<id1<<" "<<id2<<endl;
			cnt++;	
			ans[id1]=val,ans[id2]=val;
			auto tmp1=st.lower_bound(id1);
			if(tmp1!=st.begin()){
				--tmp1;
				auto tmp2=st.upper_bound(id2);
				if(tmp2!=st.end())
					q.push({solve(p[*tmp1],p[*tmp2],s[*tmp1],s[*tmp2],((*tmp1&1)?1:-1)),*tmp1,*tmp2});
			}
			st.erase(id1),st.erase(id2);
		}
		for(int i=1;i<=n;i++)
			printf("%lld ",ans[i]);
		puts("");
	}
	return 0;
}
//set
```

---

## 作者：huhangqi (赞：0)

其实就是一道大水题，但是打模拟赛的时候太困了很多性质都没有想到。

首先我们可以知道两个粒子由于是按照位置顺序和种类排布的，由于两个相碰会直接消失，所以每个粒子一定只会和可以反应的粒子相碰撞。

然后看一下运动规律，相当于一个点先向一个方向移动 $s$ 以后再向反方向移动到原点另一侧 $s$ 距离位置，之后再向原先方向距离原点为 $s$ 的位置。

那么最后只需要看作两秒钟移动一段距离，再减去开始的第一步方向是否相对来判断是否需要减去 $1$ 即可。

那么我们很容易想到按照时间顺序进行处理，每个两个相邻的点的碰撞时间都已经可以被计算出来了，但是如果一个点旁边有两个点，那么如果其中一个与这个点碰撞了，那么另外一个点就不能够与这个碰撞了，可选择碰撞的目标更改了。

那么我们删除节点，查找相邻项，明显可以使用链表或者其它的数据结构来维护，而我们需要按照时间进行碰撞操作，明显可以使用一个堆来维护。

那么这样这道题目就解决了。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,p[200005],s[200005],L[200005],R[200005],ans[200005];
struct P{
	int l,r,dis;
	bool friend operator<(P a,P b){
		return a.dis>b.dis;
	}
};
priority_queue<P> q;
int calc(int x,int y){
	return (p[y]-p[x]+s[x]+s[y]-1)/(s[x]+s[y])*2-(x&1);
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>p[i];
		for(int i=1;i<=n;i++)cin>>s[i];
		for(int i=1;i<=n;i++)L[i]=i-1,R[i]=i+1,ans[i]=0;
		for(int i=1;i<n;i++)q.push({i,i+1,calc(i,i+1)});
		while(!q.empty()){
			P u=q.top();
			q.pop();
			if(ans[u.l]||ans[u.r])continue;
			ans[u.l]=ans[u.r]=u.dis;
			if(L[u.l]&&R[u.r]!=n+1)q.push({L[u.l],R[u.r],calc(L[u.l],R[u.r])});
			R[L[u.l]]=R[u.r];
			L[R[u.r]]=L[u.l];
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		puts("");
	}
	return 0;
}
``````

---

