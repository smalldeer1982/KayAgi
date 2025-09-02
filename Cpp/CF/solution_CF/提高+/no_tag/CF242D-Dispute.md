# Dispute

## 题目描述

Valera has $ n $ counters numbered from $ 1 $ to $ n $ . Some of them are connected by wires, and each of the counters has a special button.

Initially, all the counters contain number $ 0 $ . When you press a button on a certain counter, the value it has increases by one. Also, the values recorded in all the counters, directly connected to it by a wire, increase by one.

Valera and Ignat started having a dispute, the dispute is as follows. Ignat thought of a sequence of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Valera should choose some set of distinct counters and press buttons on each of them exactly once (on other counters the buttons won't be pressed). If after that there is a counter with the number $ i $ , which has value $ a_{i} $ , then Valera loses the dispute, otherwise he wins the dispute.

Help Valera to determine on which counters he needs to press a button to win the dispute.

## 样例 #1

### 输入

```
5 5
2 3
4 1
1 5
5 3
2 1
1 1 2 0 2
```

### 输出

```
2
1 2
```

## 样例 #2

### 输入

```
4 2
1 2
3 4
0 0 0 0
```

### 输出

```
3
1 3 4
```

# 题解

## 作者：water_tomato (赞：10)

这题真的很有趣
## 题意
有 $n$ 个计数器和 $m$ 条电线，每个计数器都对应着一个额定值 $a_i$ ，初始时所有计数器的值均为 $0$ ,现在你可以按若干个计数器上的按钮，每次按按钮可以使该计数器以及与该计数器通过电线相连的计数器的值都 $+1$ ，每个计数器最多只能按一次。当你进行这样的操作若干次后，若有一个计数器上的值与该计数器的额定值一样，你就失败了。需要输出**任意**一种方案使你可以获胜。若无法获胜，输出 $-1$。

## 解析
当你得知该题的解法之后会恍然大悟——原来这么朴素！

我们用一个数组 $b$ 存储计数器当前的值，只需要寻找当前存不存在 $b_i=a_i$ 的情况，若存在，按按钮 $i$ 即可。

而这显然可以由队列实现。

### 正确性证明：
初始时所有按钮都没有被按过，当出现 $b_i=a_i$ 的情况时，我们按下按钮 $i$ 后，按钮 $i$ 的 $b_i$ 就大于 $a_i$ 了，而由于后续的操作**只能使 $b_i$ 增大**，所以 $b_i$ 不可能再一次等于 $a_i$ ，因此我们保证了任何按钮最多只按下一次。也由此可知，一定有一种方案可以获胜，不必考虑 $-1$ 的情况（根本不存在无法获胜的情况）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],b[N],head[N],cnt;
int ans[N],tot;
struct edge{
	int to,next;
}e[N<<1];
inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
queue<int> q;
inline void work(){
	while(!q.empty()){
		int u=q.front();
		q.pop();
		ans[++tot]=u;
		b[u]++;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			b[v]++;
			if(b[v]==a[v]){
				q.push(v);
			}
		}
	}
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	} 
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(!a[i]) q.push(i);
	}
	work();
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```


---

## 作者：Graph_Theory (赞：0)

### 思路

一个按钮不是必须按的，只有 $cnt_i=a_i$ 时才需要。

结论就是把 $cnt_i=a_i$ 的丢进队列里面，如果更新了 $i$ 点的连接的其他节点 $j$ 导致 $cnt_j=a_j$ 之后就再把 $j$ 丢进去。然后再按一遍 $j$，循环下去。

有一个我觉得很重要的点似乎大部分题解都跳过了，或者就是一句话带过了。大概是这样的：当有一个点 $i$ 是 $cnt_i=a_i$ 那么我们按下了这一个节点后，$cnt_i>a_i$ 了，因为按钮是一直加的，所以他所连接的其他节点即使再一次更新到了这个节点 $i$，还是满足 $cnt_i>a_i$。所以这道题是一定有解的。

### 代码

```cpp
#include <bits/stdc++.h>
#define maxn 100001
#define int long long
using namespace std;

int a[maxn],cnt[maxn],n,m;
vector<int> e[maxn];
queue<int> q;
queue<int> ans;

signed main()
{
	cin>>n>>m;
	for(int u,v;m;m--) cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		if(a[i]==0) q.push(i);
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		ans.push(x);
		cnt[x]++;
		for(auto to:e[x])
			if(++cnt[to]==a[to]) q.push(to);
	}
	cout<<ans.size()<<endl;
	while(!ans.empty()) cout<<ans.front()<<" ",ans.pop();
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

考虑简单拓扑排序。钦定 $b_i$ 为 $i$ 点当前被触发的次数。首先若初始不存在 $a_i=b_i$ 的点则不需要执行，否则每一次仅入队 $a_i=b_i$ 的点，然后将其全部更新一遍，并带动其余结点的触发次数。若其余结点 $j$ 在触发之后满足 $a_j=b_j$ 则也将其入队。因为一个点若 $a_i<b_i$ 则不会再出现 $a_i=b_i$ 的情况所以这样贪心正确。时间复杂度为 $O(n)$，可以通过。

```cpp
int a[N], b[N], id[N];
vector<int> z[N], v;
void run() {
    int n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        z[x].eb(y), z[y].eb(x);
    }
    for (int i = 1; i <= n; ++i) a[i] = read();
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (a[i] == b[i]) q.push(i);
    while (q.size()) {
        int t = q.front(); q.pop();
        v.eb(t); ++b[t];
        for (auto &g : z[t])
            if (++b[g] == a[g]) q.push(g);
    }
    iota(id + 1, id + n + 1, 1ll);
    if (count_if(id + 1, id + n + 1, [&](auto l) {
        return a[l] == b[l];
    })) cout << "-1\n";
    else {
        cout << v.size() << '\n';
        for_each(v.begin(), v.end(), [&](auto x) { cout << x << ' '; }); cout << '\n';
    }
}
```

---

## 作者：Zhao_daodao (赞：0)

# solution
感觉恶意评分。

题意比较简洁，就不再赘述了。

## first step
首先思考一下：对于每一个 $a_i=0$ 的节点 $i$，这个节点一定会被按到。

如果它不被按到，那么此时 $cnt=a_i=0$，不符合题意。

如果其它节点让它的 $cnt\ne0$，此时可以不按它，但是按它不会让答案变得更劣。
## second step
非常容易想到，对于每一个节点，如果被按到后 $cnt=a_i$，就把它放进队列里面，等到再次把它拿出来按。

对于无解的情况，无非就是一个节点重新被按到，记录 $vis$ 数组，又再次出现直接输出 `-1` 即可。
# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
struct node{
    int nxt,to;
}e[MAXN<<1];
int head[MAXN],tot;
void add(int u,int v){
    e[++tot].nxt=head[u];
    e[tot].to=v;
    head[u]=tot;
}
int n,m;
struct Point{
    int cnt;
}a[MAXN];
vector<int>vec;
queue<int>q;
int vis[MAXN];
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++)
        cin>>a[i].cnt;
    for(int i=1;i<=n;i++)
        if(!a[i].cnt)q.push(i);
    while(!q.empty()){
        int u=q.front();
        if(vis[u]){
            cout<<"-1";
            exit(0);
        }
        vis[u]=1;
        vec.push_back(u);
        q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!(--a[v].cnt))q.push(v);
        }
    }
    cout<<vec.size()<<"\n";
    for(int i=0;i<vec.size();i++)
        cout<<vec[i]<<" ";
}
```

---

## 作者：MspAInt (赞：0)

[CF242D](https://www.luogu.com.cn/problem/CF242D)

显然只有计数器值等于 $a_i$ 时需要操作。

而我们进行一次操作后，目前点一定永久合法，因为此后计数器只会变大。

其他点会受到影响吗？不会。因为操作后计数器小于 $a_i$ 不需要操作，大于 $a_i$ 更不用管，等于的时候，操作一下即可。

把初始非法的点入队操作。操作后，如果其相邻点变得非法则入队，然后将自己出队。最后输出队内曾经的元素。

每个点最多操作一次，总次数不超过 $n$。

Code（$\Theta(n+m)$）:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,a[N],q[N],top,bot=1;
vector<int>e[N];
signed main(){
    //freopen("dispute.in","r",stdin);
    //freopen("dispute.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=m;i++){
        scanf("%d%d\n",&x,&y);
        e[x].push_back(y);e[y].push_back(x);
    }
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)if(!a[i])q[++top]=i;
    while(bot<=top){
        int u=q[bot++];a[u]--;
        for(int v:e[u]){
            a[v]--;
            if(!a[v])q[++top]=v;
        }
    }
    printf("%d\n",top);
    for(int i=1;i<=top;i++)printf("%d ",q[i]);
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/115438878)

---

## 作者：shinkuu (赞：0)

之前做过类似题的，但是这次又降智了，记录一下。

构造方法和楼上一样，具体讲一下为什么一定有解：

- 如果该点没有被选过。

说明此时计数器 $b_i$ 一定 $<a_i$，否则我们就会去选择它。

- 如果该点被选择过。

说明此时 $b_i$ 已经 $>a_i$，不会再比 $a_i$ 小，否则我们就不会选这个点。

综上，在这种构造下，不管有没有选到一个点，都不会有 $b_i=a_i$。得证。

然后用类似拓扑的思路实现即可。

code：

```cpp
int n,m,c[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
queue<int> q;
vector<int> ans;
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		if(!c[i])
			q.push(i);
	}
	while(q.size()){
		int u=q.front();
		q.pop();
		ans.eb(u);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!--c[v])
				q.push(v);
		}
	}
	printf("%d\n",ans.size());
	for(int i:ans)
		printf("%d ",i);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：xiangshengtao (赞：0)

## 题意
每次可以按一个点（每个点只能按一次），那么与它相连的点和它本身都会 $+1$，最后要使每个点的分值不等于所对应的   $a_{i}$。
## 思路
这题有点像拓扑，这题的核心思想是：如果目前加的分数已经等于 $a_{i}$，那么它就可以入队（队列指可以加的点），因为后面只会越加越大，所以无论怎么加都不可能再等于 $a_{i}$ 了。
## 注意
最开始 $a_{i}$ 等于 $0$ 的都可以入队，因为后面只会越加越大，所以无论怎么加都不可能再等于 $a_{i}$ 了。
### 还有一个注意点，$-1$ 不用管它，因为无论如何他总是会有方案的。
## 程序
```
#include<bits/stdc++.h>
using namespace std;
int n,m,i,x,y,fir[100010],nxt[200010],to[200010],ans,f[100010],a[100010],b[100010],fx,fy,t;
queue<int>q;
void add(int u,int v){
	to[++t]=v;
	nxt[t]=fir[u];
	fir[u]=t;
}
int main(){
	scanf("%d%d",&n,&m);
	for (i=1;i<=m;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	for (i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if (!a[i]) q.push(i);//当a[i]=0时，直接入队
	}
	while (!q.empty()){
		fx=q.front();q.pop();
		b[fx]++;//b数组指分值
		f[fx]=1;//需要按
		for (i=fir[fx];i;i=nxt[i]){
			fy=to[i];
			b[fy]++;
			if (b[fy]==a[fy]) q.push(fy);//分值已经等于a[i]，入队
		}
	}
	for (i=1;i<=n;i++) ans+=f[i];
	printf("%d\n",ans);
	for (i=1;i<=n;i++)
		if (f[i])
			printf("%d ",i);//当它需要按，输出节点编号
	return 0;
}

```


---

## 作者：NatsumeHikaru (赞：0)

[更好的阅读体验](https://hikaru.com.cn/hikaru/266/)
#### Description

[here](https://codeforces.com/problemset/problem/242/D)

#### Solution

首先，考虑一下绝对不会出现无解的情况，只要出现 $cnt_i=a_i$ ，我们按下 $i$ 即可，此时 $cnt_i>a_i$ ，且 $cnt_i$ 永远也不会等于 $a_i$ ，所以通过若干次调整即可得到方案，可以使用一个队列来维护按按钮的顺序。

#### Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=100010,M=200010;

int n,m;
int h[N],to[M],ne[M],idx;
int a[N];
int cnt[N],tot,ans[N];
int q[N],hh=1,tt=1;

inline void add(int u,int v){
	to[idx]=v,ne[idx]=h[u],h[u]=idx++;
}

void work(){
	while(hh < tt){
		int t=q[hh++];
		ans[++tot]=t;
		cnt[t]++;
		for(int i=h[t];~i;i=ne[i]){
			int j=to[i];
			cnt[j]++;
			if(cnt[j] == a[j])
				q[tt++]=j;
		}
	}
}

int main(){
	memset(h,-1,sizeof h);
	scanf("%d%d",&n,&m);
	while(m--){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b),add(b,a);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(!a[i]) q[tt++]=i;
	}

	work();

	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d ",ans[i]);
	return 0;
}
```



---

