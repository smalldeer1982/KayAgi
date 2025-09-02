# Queue in the Train

## 题目描述

There are $ n $ seats in the train's car and there is exactly one passenger occupying every seat. The seats are numbered from $ 1 $ to $ n $ from left to right. The trip is long, so each passenger will become hungry at some moment of time and will go to take boiled water for his noodles. The person at seat $ i $ ( $ 1 \leq i \leq n $ ) will decide to go for boiled water at minute $ t_i $ .

Tank with a boiled water is located to the left of the $ 1 $ -st seat. In case too many passengers will go for boiled water simultaneously, they will form a queue, since there can be only one passenger using the tank at each particular moment of time. Each passenger uses the tank for exactly $ p $ minutes. We assume that the time it takes passengers to go from their seat to the tank is negligibly small.

Nobody likes to stand in a queue. So when the passenger occupying the $ i $ -th seat wants to go for a boiled water, he will first take a look on all seats from $ 1 $ to $ i - 1 $ . In case at least one of those seats is empty, he assumes that those people are standing in a queue right now, so he would be better seating for the time being. However, at the very first moment he observes that all seats with numbers smaller than $ i $ are busy, he will go to the tank.

There is an unspoken rule, that in case at some moment several people can go to the tank, than only the leftmost of them (that is, seating on the seat with smallest number) will go to the tank, while all others will wait for the next moment.

Your goal is to find for each passenger, when he will receive the boiled water for his noodles.

## 说明/提示

Consider the example.

At the $ 0 $ -th minute there were two passengers willing to go for a water, passenger $ 1 $ and $ 5 $ , so the first passenger has gone first, and returned at the $ 314 $ -th minute. At this moment the passenger $ 2 $ was already willing to go for the water, so the passenger $ 2 $ has gone next, and so on. In the end, $ 5 $ -th passenger was last to receive the boiled water.

## 样例 #1

### 输入

```
5 314
0 310 942 628 0
```

### 输出

```
314 628 1256 942 1570 
```

# 题解

## 作者：叶ID (赞：9)

题目链接：[CF1239C Queue in the Train](https://www.luogu.org/problem/CF1239C)

【广告】[在个人博客食用](https://toxic2018.ml/1895/)风味更佳

****

### 题目标题

火车上的队列

### 题意简述

火车上有一排座位，标号 $1..n$ 。座位上的每个人需要去接开水~~烧方便面（题目这么说的）~~。每个人接开水都一致地需要 $p$ 分钟，而走动的时间可忽略不计。第 $i$ 个人从第 $t_i$ 分钟开始，就会打算去接开水。

同一时刻只能有一人在接水，因此，自然会出现排队的情况。

然而人们都不想排队。第 $i$ 个人会关注第 $1$ 到 $i-1$ 个座位（如果这些座位是空的，那么座位上的人肯定是在接水或者排队）。即，第 $i$ 个人会在第 $t_i$ 分钟后的，`(`第 $i$ 到第 $i-1$ 个座位都不是空的`)`的最早时间离开座位，去接水或者排队。

另外，还有一个潜规则：如果在同一时刻，有多个人可以离开座位，那么只有坐在编号最小的座位上的人会离开座位，其他的则继续等待。

现在，你需要计算每个人接完水的时刻。

****

### 解题思路

这题题目中存在很多要维护的东西，比如，正在等待的人的集合、队列中的人的集合（包括正在接水的那个），以及当前时间。如果使用普通的模拟做法，则较为难写。如果将时间离散化，按照时刻处理，同样非常难处理。

那么，我们可以使用“事件化”的办法进行模拟。

此处定义“事件”是一个三元组 $(time,type,id)$ 。其中， $time$ 表示事件发生的时间， $type$ 表示事件类型（$0$ 表示接水完成，离开接水的队列；$1$ 表示开始等待）， $id$ 则表示事件的对象（即，受影响的人的编号）。

一开始，有 $n$ 个事件，即，对于所有 $1 \leq i \leq n$ 的 $(t_i,1,i)$。我们将这 $n$ 个事件放入事件队列。

我们还需要维护以下内容：

- $wait$ ，表示当前正在等待的人的集合（这些人还在座位上）。维护的数据结构需要支持以下操作（因此选择使用优先队列）：
  - 取出最小值。对于任何等待队列中的人可以进入接水队列的情景，一定是最小值优先。
  - 删除最小值。当一个人进入了接水队列，就不再属于等待队列。
  - 插入值。当处理到 $type = 1$ 的事件时，对应的人要进入等待队列。
- $q$ ，表示当前接水队列中的人的集合（包括正在排队和正在接水的）。需要支持以下操作（因此选择使用set）：
  - 删除指定值。当处理 $type = 0$ 的事件时，需要将指定的值从队列中移除
  - 取出最小值。如果等待队列中编号最小的人编号比接水队列中的最小编号还要小，这个人才能进入接水队列。
  - 插入值。如果等待队列中编号最小的人编号比接水队列中的最小编号还要小，这个人就要进入接水队列。
- $currtime$ ，当前正在处理的事件发生的时间。
- $emptytime$ 。在不会再有人进入接水队列的情况下，预计接水队列将会为空的时刻。或者说，最后一个进入接水队列的人完成接水的时刻。

随后，我们从事件队列中取出最早发生的事件，并将其删除（我们认为，$type = 0$ 的事件总是在 $type = 1$ 的事件之前进行（原因见下文），并且，对于 $type = 1$ 的事件，$id$ 小的先进行）。随后，我们对这个事件进行处理。

- 如果 $type = 0$，那么直接从接水队列中将对应的人删除
- 如果 $type = 1$，那么将指定的人加入等待队列

在处理完一个事件后，要么是接水队列改变，要么是等待队列改变。这些改变可能会引起当前等待队列中编号最小的人编号比接水队列中的最小编号还要小。那么，这时候，等待队列中编号最小的人就需要进入接水队列。这个人进去之后，等待队列的最小编号必定要大于接水队列的最小编号，因此无需继续判断。

一个人$t$从等待队列进入接水队列后，显然，他完成接水的时刻是 $max(currtime,emptytime) + p$ 。因此，我们要添加一个事件 $(max(currtime,emptytime) + p,0,t)$ ，然后将 $emptytime$ 更新为 $max(currtime,emptytime) + p$ 。此时，我们就可以进行答案的统计，因为我们知道了编号为$t$的人接水结束的时间。

因此只要反复处理事件，直到事件队列为空，我们就求得了所有答案。

### 总结

问题：为什么要使用上文提到的，对事件的排序方式呢？

如果 $type = 1$ 的操作先于 $type = 0$ 的执行，你会发现，你愉快地被样例叉掉了。因为，如果先执行 $type = 1$ ，那么在判断等待队列中的人是否能进入接水队列时，原本已经接水完成，要离开接水队列的人却没有即使离开，会导致影响判断。而如果在 $type = 1$ 时，$id$ 大的先执行，则会违反题目中提到的“潜规则”。

总结：本题中，进入等待队列和离开接水队列的事件有着共同之处，那就是，①必须按照时间顺序交替处理，②处理完毕后，都必须检查等待队列的人能否进入接水队列。另外，我们需要求接水队列的最小值。如果使用队列`std::queue`处理，则相当麻烦，而使用事件化的方式处理离开接水队列的事件，则完美地避免了使用队列，方便了最小值的统计。

### 代码

```cpp
// status: [Accepted][unofficial]
// oj:     [Codeforces]

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int MAXN = 100005;
int n,tt;
int t[MAXN];
int ans[MAXN];

// 事件
struct Event {
    int time; // 发生时间
    int type; // 类型
    int id;   // 影响到的人
    Event() {}
    Event(int _time,int _type,int _id) {time=_time;type=_type;id=_id;}
    bool operator<(const Event &other) const {
        if(time != other.time) return time > other.time; // 此处的排序必须反过来，因为优先队列是从大到小排列的。
        if(type != other.type) return type < other.type;
        return id > other.id;
    }
};

// 事件队列
priority_queue<Event> ev;
// 接水队列
set<int> q;
// 等待队列。使用模板 greater<int>，以使得编号小的人先被取出。
priority_queue<int,vector<int>,greater<int> > wait;

signed main() {
    ios::sync_with_stdio(false);

    cin>>n>>tt;
    for(int i=1;i<=n;i++) {
        cin>>t[i];
        // 创建一开始的n个事件
        ev.push(Event(t[i],true,i));
    }

    int currtime = 0;
    int emptytime = 0;
    while(!ev.empty()) {
        Event c = ev.top(); ev.pop();
        currtime = c.time;
        if(c.type == 0) {
            // cerr<<currtime<<": "<<c.id<<" left the queue."<<endl;
            q.erase(c.id);
        }
        else {
            // cerr<<currtime<<": "<<c.id<<" became waiting."<<endl;
            wait.push(c.id);
        }

        // 这是等待队列中的人进入接水队列的条件
        while(!wait.empty() && (q.empty() || wait.top() < *q.begin())) {
            int p = wait.top();wait.pop();
            // cerr<<currtime<<": "<<p<<" entered the queue."<<endl;
            q.insert(p);
            // 计算这个人接水完毕的时刻
            int et = max(currtime, emptytime) + tt;
            // 创建这个人离开接水队列的事件
            ev.push(Event(et,false,p));
            // 更新emptytime
            emptytime = et;
            // 统计答案
            ans[p] = et;
        }
    }

    for(int i=1;i<=n;i++) {
        if(i>1) cout<<' ';
        cout<<ans[i];
    }
    cout<<endl;
}

```

评测记录：[R25487378](https://www.luogu.org/record/25487378)


---

## 作者：kukuchiu (赞：7)

# 这是一道很明显的 DP + 大模拟 的题。

* 我们可以考虑按时间顺序模拟整个过程。

* 我们自然的想法是开一个队列来维护排队的人，再开一个容器来维护想要喝水的人。由于每次去排队的都是想要喝水的人中编号最小的那个人，所以这个容器实际上是一个小根堆，队列中维护想要喝水的人的编号。

* 由于一个人只有但比他编号小的人都坐在自己的座位上时才会去排队，所以这个队列实际上是单调递减的。

* 当一个人想去喝水时，将其加入堆中。当新增的想去喝水的人都加入堆中后，将想去喝水的编号最小的人（堆顶元素）与队尾的人的编号比较来就定其是否会去排队。

* 当一个人喝完水后，若队列为空，则将想去喝水的编号最小的人（堆顶元素）加入队列。

* 时间复杂度为 $O(n$ $log$ $n)$ ，不会超时，请你放心！

---

## 作者：xukuan (赞：5)

div1的C题考了一道STL的应用，这让我很惊讶

我们开：
- 优先队列pq，pair<time,id>表示在time时刻第id个用户会想到要接水
- 集合s，表示想要接水的人
- q队列，表示能接水的人

每次处理的时候：q队列为空或当前那个人的id更小就push到q里面，否则insert到集合s里面。出队后如果q为空就把集合最小的push进队列

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=100010;
ll n,m,ans[N];
priority_queue<pair<ll,ll> > pq;
queue<ll> q;
set<ll> s;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

int main(){
	n=read(); m=read();
	for(ll i=1; i<=n; i++){
		ll x=read();
		pq.push(make_pair(-x,-i));
	}
	ll now=0;
	for(ll i=1; i<=n; i++){
		if(q.empty()&&s.empty()) now=-pq.top().first;
		now+=m;
		while(!pq.empty()&&-pq.top().first<=now){
			if(q.empty()||-pq.top().second<q.back()) q.push(-pq.top().second);
			else s.insert(-pq.top().second);
			pq.pop();
		}
		ans[q.front()]=now;
		q.pop();
		while(q.empty()&&!s.empty()){
			q.push(*s.begin());
			s.erase(s.begin());
		}
	}
	for(ll i=1; i<=n; i++){
		write(ans[i]);
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：WLHW (赞：4)

[在此使用更佳哦](https://blog.csdn.net/qq_40032278/article/details/102671368)
(￣▽￣)~*
- 定义一个事件集合 $a$ 储存$<time,id>$ 表示：在 $time$ 时刻，第 $id$ 个人会想接水（可以用优先队列进行升序排序）
- 定义一个 $want$ 集合（可以用 $set$），表示进入等待状态的人
- 定义一个 $q$ 队列，表示能够接水的人。
- 每一次处理事件时（以 $p$ 为梯度的处理）
	 - 若队列为空，则 $push$ 进队列
	 - 或者当前事件的 $id$ 小于队列末尾的人的 $id$ ，则 $push$ 进队列（编号比队列末尾的人小，说明上一次等待状态的人延续下来，他们的编号一定小于当前编号，所以当前第一个接水的是当前编号）
	 - 否则 $insert$ 到 $want$ 中。
- 出队后，若队列为空则把 $want$ 集合里编号最小的 $push$ 进队列。

```cpp
#include <bits/stdc++.h>
using namespace std;
priority_queue< pair<int,int> > a; // 事件集合
queue<int> b; // 当前在队列中的人
set<int> d; // 想进队列的人 (等待状态)
long long h[1000010];
int main()
{
	int i,j,n,p,x;
	long long now=0;
	scanf("%d%d",&n,&p);
	for(i=1; i<=n; i++) scanf("%d",&x),a.push(make_pair(-x,-i));
	for(i=1; i<=n; i++)
	{
		if(b.empty()&&d.empty()) now=-a.top().first;
		now+=p;
		while(!a.empty()&&-a.top().first<=now)
		{
			if(b.empty()||-a.top().second<b.back()) b.push(-a.top().second);
			else d.insert(-a.top().second);
			a.pop();
		}
		h[b.front()]=now;
		b.pop();
		if(b.empty()&&!d.empty()) 
		{
			b.push(*d.begin());
			d.erase(d.begin());
		}
	}
	for(i=1; i<=n; i++) printf("%lld ",h[i]);
	return 0;
}
```


---

## 作者：ny_jerry2 (赞：3)

## 前言
奇怪的 STL 应用题，但说实话比较考验思维。

## 思路
显然，对于每一个时刻，都有这三类人：

- $noidea$：还没有进入等待队列的想法（就是没有到去接水的时间）。
- $want$：想去接水但是不能到队列里面去。
- $wait$：已经在等待的队列里面了。

对于第一个，我们用一个小根堆，来存他们想加入队列的时间，因为显然优先考虑想先去接水的人。同时要存储人的编号，因为你后面总会把这些人插到 $want$ 或者 $wait$ 里面去。如果想加入等待队列的时间一样，优先考虑编号小的。  

对于第二个，同样用一个小根堆，这个是存编号。因为大家都想要去接水了，就要优先考虑编号小的。

对于第三个用一个普通队列即可。因为顺序已经定下来了，不可能去插队吧。而且题目中说了**正在饮水机旁排队的所有人形成一个先进先出的队列**。

这里就一个性质：等待队列里的数单调递减。  
很简单，因为题目中说了只有比自己编号小的都没去自己才有资格去。  
这个性质比较重要。

以下设 $now$ 表示当前的时间。

最开始把所有元素都加入到 $noidea$ 中，然后开始迭代。

考虑等待队列空了，有两种情况：

- 如果 $want$ 没空，让 $want$ 中编号最小的人插入到队列里面中。
- $want$ 也空了，就从 $noidea$ 中取出堆顶元素，插入到队列中，并让 $now$ 等于堆顶元素想去接水的时间，因为中间肯定会出现空闲期，等空闲期结束了自然是这个人去接水。

每一次更新：$now \to now + p$，并取出队列的队头元素，他的接水时间就是 $now$。

然后考虑 $noidea$中的元素，每一次找到堆顶，如果堆顶想加入的时间已经小于等于了 $now$ ，他就应该离开 $noidea$。此时又分两种情况：

- 该元素编号大于了等待队列末尾元素。加入的话不满足上面说的性质，所以加到 $want$ 里面去。
- 否则就可以直接加到等待队列的末尾。

最后踢掉队头元素，因为他已经被考虑过了，所以对之后的过程就没有贡献了。  

时间复杂度：$O(n \log n)$。

## 代码
```
#include<iostream>
#include<queue>
#define pii pair<long long,int>
int n;
const int N=3e5+10;
long long a[N],m;
using namespace std;
priority_queue<int,vector<int>,greater<int>> want;//想排队但是进不来 
priority_queue<pii,vector<pii>,greater<pii>> noidea;//根本就没想去排队 
queue<int> wait;//在队列中了 
long long now,ans[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		noidea.push({a[i],i});
	}
	for(int i=1;i<=n;i++){
		if(wait.empty()){//如果队列已经空了 
			if(want.size()){//看看有没有想要进来的 
				wait.push(want.top());//加入编号最小的人 
				want.pop();//弹出 
			}else{//没有想要进来的人 
				wait.push(noidea.top().second);//硬拉一个不想来的人 
				now=noidea.top().first;
				noidea.pop();
			}
		}
		now+=m;
		ans[wait.front()]=now;//时间 
		while(noidea.size()&&now>=noidea.top().first){//是否到了排队的时候 
			if(wait.back()>noidea.top().second){//看看满不满足单调性 
				wait.push(noidea.top().second);
			}else{
				want.push(noidea.top().second);
			}
			noidea.pop();//考虑完了就删除。 
		}
		wait.pop();//踢掉 
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<' ';//输出时间 
	}
}
```

---

## 作者：_RainCappuccino_ (赞：1)

> $\texttt {TAG}$：模拟，优先队列的应用

考虑题目需要实现什么：

1. 对于每个人，有一个想要接水的时间，如果到了这个时间，他会尝试进入接水队列。

2. 如果接水队列中存在一个人 $i$，且 $i$ 小于这个人的编号，那么不能入队，当接水队列中不存在 $i$ 小于这个人的编号的**一瞬间**（刚好接完水也可以）会尝试入队。

3. 如果同一瞬间有多个人尝试入队，编号较小的入队。

我们发现需要维护三种人：

1. $q$：还不考虑接水的人。
2. $q_2$：考虑接水但没办法接水的人。
3. $wait$：在接水队列中的人。

设当前时间为 $now$，考虑每次人员迁移：

1. 如果接水队列没有人，先尝试将 $q_2$ 中元素最小的人加入 $wait$ 队列中，如果 $q_2$ 中没有等待的人，将不考虑接水的人中 $t_i$ 最小的人进入接水队列，$now$ 更新为 $t_i$，相当于跳过一段空档期。

2. 将接水队列的队首出队，得到起接到水的时间 $now + p$，然后考虑在队首接水期间，是否会有人变迁所属队列。

    1. $q$ 中满足 $t_i \le now + p$ 的人，将尝试进入 $wait$ 中，如果满足 $wait$ 的队尾的编号大于该点编号，那么可以直接进入等待队列。（因为等待队列中的人的编号显然是单调递减的）
    2. 否则，将其加入 $q_2$。


当所有人都已经接到水，那么结束这个过程。

为了维护 $t_i$ 最小，实现时使用小根堆维护即可。

为了维护 $q_2$ 编号最小元素，实现时使用小根堆维护即可，因为不用考虑顺序，他们都是在接水队列为空时一起尝试进队。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 10;
typedef long long ll;
typedef pair<int, int> pi;
int n, p;
int t[N], ans[N];
priority_queue<pi, vector<pi>, greater<pi> > q;
priority_queue<int, vector<int>, greater<int> > q2; // 可以走但是 1 ~ i - 1 还没走
queue<int> wait;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> p;
	for (int i = 1; i <= n; i ++) cin >> t[i], q.push({t[i], i});
	int now = 0;
	while (1) {	
		if (wait.empty() && !q2.empty()) wait.push(q2.top()), q2.pop(); // wait 序列单调递减
		if (wait.empty()) now = q.top().first, wait.push(q.top().second), q.pop();
		now += p;
		ans[wait.front()] = now;
		while (!q.empty() && now >= q.top().first) {
			if (wait.back() > q.top().second) wait.push(q.top().second), q.pop();
			else q2.push(q.top().second), q.pop();
		}
		
		wait.pop();
		if (q2.empty() && wait.empty() && q.empty()) break;
	}
	for (int i = 1; i <= n; i ++) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}
```

---

## 作者：天才颓废学家 (赞：1)

个人认为这道题的主要难点是理解题意。理解题意之后，代码难度并不高。下面给出几个笔者认为容易出现理解错误的点。  
\* 注：下文以“喝水点”代指“打算喝水的时间点”。
+ ```没人喜欢排队。``` 不意味着不会有人排队，而是只有不知道有人正在接水的人即**空位左边的人**会去排队。  
因此，我们不能对于整个数列进行 $n$ 轮的寻找，而是要优先在**当前接水者（或最后一个排队的人）的前面**找时间最小的人。  
+ ```如果有多人同时要去喝水，那么位置靠左的人会先起身。``` 这句话的意思是**仅有最左侧的人会去排队**而非其在队列中相对靠前。  
所以下一个去倒水的人一定是“喝水点”小于等于当前倒水者倒水完成时间中**编号最小者**。当然，如果所有人的“喝水点”都大于当前倒水者倒水完成时间，那就选“喝水点”最早的那一个。

------------

理解清楚题目意思后，写出来就不难了，考虑用线段树维护**区间中小于等于 $k$ 的数中的最小编号**和**区间最小值**。为避免重复倒水，可以在查询到点后直接将其“倒水点”赋值为无穷大。这样可以少写一个 update。

---

## 作者：intel_core (赞：0)

Div1.C 居然考了 STL 应用，我表示很不理解。

题目问的是每个人吃到泡面的时间，那就只需求出每个人接水的时间即可。

开两个优先队列，一个存还不想接水的人，一个存想接水的人。

想接水的优先队列按照人的编号排序，不想接水的优先队列按照接水的时间排序。

每次处理完一个接水的人之后把不想接水的优先队列中到接水时间的那些人扔进节水人的队列里。

如果当前没人想接水，直接跳到下一个想接水的人。

复杂度 $O(n \log n)$。

---

## 作者：Llf0703 (赞：0)

[更好的阅读体验](https://llf0703.com/p/cf-1248.html#equeueinthetrain)

## 题意

有 $n(\le 10^5)$ 个人坐火车，每个人有个想吃泡面的时间点 $t_i$ ，所有人接水所需的时间都是 $p$ 。

在某一时刻 $T$，如果第 $i$ 个人的 $t_i\geq T$ ，且编号 $< i$ 的人都没去接水，那么它就会去排队。特别的，如果有多个人同时想接水，那么编号小的先去。

$\forall i$ ，求 $i$ 接完水的时间。

## 题解

每一次找到 $t_i\geq T$ 且 $i$ 最小的人，假设为 $x$ ，让它去接水。更新 $T$ 后，在 $[1,x]$ 中不断找 $t_i\geq T$ 且 $i$ 最小的 $x$ 去接水，并更新 $T$ 。

不断重复此过程直到所有人都接了水。找最小可以用线段树维护区间最小值。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define mp make_pair
#define ha 1000000007
#define ui unsigned ll
#define pii pair<ll,ll>
#define pid pair<ll,double>

using namespace std;

inline ll read()
{
    char ch=getchar(); ll f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

const int N=100005;
struct Tree {
    ll left,right,mn;
} tree[N<<2];
ll n,p,t[N],ans[N];

inline void pushup(ll x) { tree[x].mn=min(tree[x<<1].mn,tree[x<<1|1].mn); }

void build(ll x,ll l,ll r)
{
    tree[x].left=l;
    tree[x].right=r;
    tree[x].mn=1e9;
    if (r-l==1) tree[x].mn=t[l];
    else
    {
        ll mid=(l+r)>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid,r);
        pushup(x);
    }
}

void update(ll x,ll l,ll r,ll delta)
{
    if (l<=tree[x].left && r>=tree[x].right) tree[x].mn=t[l]=delta;
    else
    {
        ll mid=(tree[x].left+tree[x].right)>>1;
        if (l<mid) update(x<<1,l,r,delta);
        if (r>mid) update(x<<1|1,l,r,delta);
        pushup(x);
    }
}

ll query(ll x,ll delta) //找 <=delta 的最小编号
{
    if (tree[x].left+1==tree[x].right) return tree[x].left;
    if (tree[x<<1].mn<=delta) return query(x<<1,delta);
    else return query(x<<1|1,delta);
}

ll query2(ll x,ll r) //在 [1,r] 中找最小值的编号
{
    if (tree[x].left>r) return -1;
    if (tree[x].left+1==tree[x].right) return tree[x].left;
    if (tree[x<<1].mn<=tree[x<<1|1].mn) return query2(x<<1,r);
    ll rt=query2(x<<1|1,r);
    if (rt==-1 || t[rt]>=tree[x<<1].mn) return query2(x<<1,r);
    return rt;
}

signed main()
{
    n=read(); p=read();
    for (ll i=1;i<=n;i++) t[i]=read();
    build(1,1,n+1);
    for (ll i=0,cur=0;i<n;)
    {
        cur=max(cur,tree[1].mn); //让当前时刻来到数列最小值
        ll x=query(1,cur);
        ans[x]=cur+=p; i++; //让 x 去接水
        update(1,x,x+1,1e18); //t[x]=inf ，防止重复选取
        for (;x>0;) //不断重复此过程
        {
            x=query2(1,x);
            if (t[x]>cur) break;
            ans[x]=cur+=p; i++;
            update(1,x,x+1,1e18);
        }
    }
    for (ll i=1;i<=n;i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

