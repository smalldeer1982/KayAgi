# [SDCPC 2023] Building Company

## 题目描述

您是一家建筑公司的老板。一开始，公司共有 $g$ 类员工，每一类员工都属于一个工种。第 $i$ 类员工的工种编号为 $t_i$，共有 $u_i$ 人。

市场上共有 $n$ 项工程等待承接。想要承接第 $i$ 项工程，您的公司需要满足 $m_i$ 项要求，其中第 $j$ 项要求您的公司至少有工种编号为 $a_{i, j}$ 的员工 $b_{i, j}$ 人。承接该工程后，您的公司将会更加有名，并吸引 $k_i$ 类员工加入公司，其中第 $j$ 类员工的工种编号为 $c_{i, j}$，共有 $d_{i, j}$ 人。

您可以按任意顺序承接任意数量的工程，每项工程最多只能被承接一次。求最多能承接多少工程。

请注意：员工不是消耗品。承接一项工程后，员工的数量不会减少。

## 样例 #1

### 输入

```
2 2 1 1 2
5
1 3 1
0
2 1 1 2 1
2 3 2 2 1
3 1 5 2 3 3 4
1 2 5
3 2 1 1 1 3 4
1 1 3
0
1 3 2```

### 输出

```
4```

# 题解

## 作者：CashCollectFactory (赞：5)

## 题目大意

公司里有多种员工，每种员工数量已知。现在有若干个工程待完成，完成每项工程都对各类员工的数目有一定最低要求，且完成每项工程后都会获得一定数目新员工的奖励。求**能完成的最多工程数**。

## 题目分析

由于员工不是消耗品,显然越多越好，且获得员工的时机并不影响以后工程的完成，因此该问题显然满足无后效性。那么贪心算法就已经呼之欲出了！我们只要不停的遍历所有工程，遇到可完成的就直接完成并累加员工数，当任何工程都无法完成时，则输出已完成的工程数，最终的时间复杂度为 $ n^3 $。面对十的五次方规模的数据，显然难以忍受。接下来考虑优化！
## 解法优化

标签思想是 OI 界的重要思想之一，本题更是体现的淋漓尽致。观察到保证 $m_i$ 与 $k_i$ 之和均不超过 $10^5$，我们应当以此为着手点进行代码迭代，发力数据规模痛点，对题目需求进行归因分析，从而打出一套组合拳，完成对此题目的降维打击！


具体而言，我们为每一个员工类型开一个标签，数组用于维护这些标签，标签中则存储所有对该类员工有需求的工程序号与需求数量。当该类员工数值有所更新时，在维护得到已达到的为需求数目。此外，我们还需要一个计数数组来记录每个工程的待满足需求数，当待满足要求数为零时，说明该工程已可实施，则可将其放入一个栈或队列中，从而通过维护这个栈或队列来统计答案。注意到 $1 \le t_i, u_i \le 10^9$，我们难以开如此巨大的数组，所以考虑离散化或 ```unorder_map```。 最终复杂度为 $O(n)$，采用离散化的话则是 $O(n \log n)$，其他具体的实现细节可以移步代码实现，里边的注释还是挺详细的！

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
struct tagy{
    int gongcid,wnum;
    bool operator < (const tagy &x) const {
        return (wnum==x.wnum) ? gongcid<x.gongcid : wnum<x.wnum;
    }//注意这里的小于号重载
    tagy(int G,int W){
        gongcid=G,wnum=W;
    }
};
//构建一个标签结构体，分别记录各个工程序号及需求员工数量。
struct rwd{
    int kd,nm;
    rwd(int K,int N){
        kd=K,nm=N;
    }
};
//构建一个奖励结构体，用于在处理可实施工程时候更新员工数量。
int n,m,tn1,tn2,ans;
int cnt[500005];//记录每个工程的待满足需求量
unordered_map<int,int> ar; //记录每种员工目前的数量
stack<int> s;//维护目前可实施的全部工程
map<int,set<tagy> > tgm; 
vector<rwd> v[500005];
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&tn1,&tn2);
        ar[tn1]=tn2;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&n);
        int t=0;
        while(n--){
            scanf("%d%d",&tn1,&tn2);
            if(ar[tn1]>=tn2) continue; //若已满足，则忽略。
            tgm[tn1].insert(tagy(i,tn2));
            t++;
        }
        if(!t) s.push(i);
        cnt[i]=t;
        scanf("%d",&n);
        while(n--){
            scanf("%d%d",&tn1,&tn2);
            v[i].push_back(rwd(tn1,tn2));
        }
    }
    while(s.size()){
        ans++; n=s.top(); s.pop();
        for(int i=0;i<v[n].size();i++){
            ar[v[n][i].kd]+=v[n][i].nm;
            while(1){
            	if(tgm[v[n][i].kd].size()==0) break; 
                set<tagy>::iterator IT;
                IT=tgm[v[n][i].kd].begin();
                if((IT->wnum) > ar[v[n][i].kd]) break;
                cnt[IT->gongcid]--;
                if(cnt[IT->gongcid]==0) s.push(IT->gongcid);
                tgm[v[n][i].kd].erase(IT);
            }
        }
    }
    cout<<ans;
    return 0;
}
```

需要注意的是，本参考代码使用了 unordered_map，因此需要 C++11 及以上版本。

（~~PS.记得雁过留声啊~~）

---

## 作者：WhitD (赞：2)

（~~首先你需要认真阅读题面~~）。
## 思路
一个明显的策略是：如果有可以承接的工程，我们一定会承接它（因为承接工程永远不会减少你的员工，承接工程后一定是有收益的）。

可以很快想到最朴素的暴力做法：直接枚举一遍 $n$ 个工程看可不可以承接，如果可以承接，那就加上新员工后继续枚举，直到没有可以承接的工程或者所有工程都承接完了。但是这样做显然会超时。

考虑如何优化上述暴力算法。

举个例子吧：有三个工程，第一个工程可以承接，承接完会给编号一的员工，第二个工程要求更多编号一的员工，第三个工程要求更多编号二的员工。事实上承接完第一个工程后我们只能去考虑第二个工程能否承接，因为给的员工只有编号一，我们一定不会满足第三个工程的条件（要求编号二）。

也就是说当我们承接一个工程时，只需要继续考虑通过新添加的员工可以满足条件的那些工程就可以了。可以用堆来维护每项工程还有多少条件没有满足，并维护一个队列，所有要求都被满足的工程将加入队列。从队列中取出一个工程代表我们承接了它、可以添加新员工，当编号为 $x$ 的员工加入公司后，我们只需要查找含有与 $x$ 有关的条件的工程并判断它是否可以加入队列。

（关于员工编号值域很大的问题，可以用 `map`）。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define ll long long
#define p_ priority_queue<pi,vector<pi>,greater<pi>>
using namespace std;
const int N=100005;
int g,n,t[N],u[N],m[N],ans;
vector<pi> a[N];
queue<int> q;
map<int,ll> tot;
map<int,p_> um;
void add(int t,int u)
{
	ll &v=tot[t];v+=u;
	p_ &_q=um[t];
	while(!_q.empty())
	{
		pi i=_q.top();
		if(i.first>v)
			break;
		_q.pop();
		if(!(--m[i.second]))
			q.push(i.second);
	}
}
int main()
{
	cin>>g;
	for(int i=1;i<=g;i++)
		cin>>t[i]>>u[i];
	cin>>n;
	for(int i=1,k;i<=n;i++)
	{
		cin>>m[i];
		if(!m[i])
			q.push(i);
		for(int j=1,a,b;j<=m[i];j++)
			cin>>a>>b,um[a].push(pi(b,i));
		cin>>k;
		for(int j=1,c,d;j<=k;j++)
			cin>>c>>d,a[i].push_back(pi(c,d));
	}
	for(int i=1;i<=n;i++)
		add(t[i],u[i]);
	while(!q.empty()&&(++ans))
	{
		int x=q.front();
		q.pop();
		for(auto i:a[x])
			add(i.first,i.second);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：LIUYC_C (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P9557)

思路太巧妙了，必须写发题解。

题意首先就击溃了挺多的人，希望读者还是可以耐着性子读题，了解题目大概结构后再看题解。

## 大体思路：

### 暴力：

首先不难想到一种显然的 $n^3$ 做法，首先得到公司的初始工种和该工种工人数目，接下来，我们有 $n$ 个工程，我们直接对这 $n$ 个工程遍历一遍，看对于第 $i$ 个工程，它所提到的 $m_{i}$ 项要求我当前是否全部都满足，若满足，我直接加上该工程的 $k_{i}$ 项贡献，并把答案加一，代表我多接了一个工程，然后再次遍历一遍，直到没有任何可以接的工程为止。

想到这里，你就对题目的整体框架已经有了一个初步的认识。

### 接下来考虑优化：

我们在暴力做法中，花费了大量的时间去寻找满足所有限制条件的工程，这样显然是很蠢的，我们不妨把每个工程的所有限制条件拆开成若干个单独考虑。

#### 具体操作：

首先，我们引入一个限制总数 $m_{i}$，对于每一个工程都会有一个限制总数，代表第 $i$ 个工程我要满足 $m_{i}$ 个限制条件。 

那么对于第 $i$ 个工程的，第 $m_{i,j}$ 项要求，要工种编号为 $a_{j}$ 的员工，那么考虑贪心，我们肯定是取出这 $n$ 个工程中要这个工种的人数最少的工程来更新，看我们当前公司的这个工种人数够不够，够了，就意味着这个工程的限制总数可以减一，然后，对于每一个工种都这样去更新工程的限制总数。

当工程的限制总数减为 $0$ 时，就可以接手这个工程，并获得新的员工，再次去更新其他工程的限制总数。



这样一看不就很像拓扑排序吗？

在拓扑中我们是把入度为 $0$ 的节点入队，在此题中则是把限制总数为 $0$ 的工程入队。

每一次取出最小的人数，可以用优先队列实现，再进行拓扑排序。

虽然此题乍一看没有任何拓扑的影子，但却处处是拓扑的影子。

处处不是你，处处都是你。

### 代码实现：

首先对于数组，观察到要存的东西作为下标来说很大，考虑离散化，定义为哈希表就好。
```cpp
#define int long long//好习惯（不是）
const int N=101010;
typedef pair<int,int> PLL;

unordered_map<int,int> has;//表示当前公司的种类为si的工人有多少个

unordered_map<int,priority_queue<PLL,vector<PLL>,greater<PLL> >>hashs;
//小根堆，每次取出n个工程中，种类为si的工人数量最少的，PLL里first存的
//是工人数，second存的是第i个工程

int n,g;

int idx=0;
int zl[N];//存种类的 和idx st配合使用。
unordered_map<int,int> st;

int xz[N];//限制总数

vector<PLL> gx[N];//第i个工程的贡献，PLL种类和数量



```
然后常规读入。

```cpp
  
  cin>>g; 
  for(int i=1;i<=g;i++){
    int x,y;
    cin>>x>>y;
    has[x]+=y;
  }
  
  cin>>n;
  for(int i=1;i<=n;i++){
    int m;
    cin>>m;
    xz[i]=m;

    for(int j=1;j<=m;j++){
      int x,y;
      cin>>x>>y;
      hashs[x].push({y,i});
      if(!st[x]){
        st[x]=true;
        zl[++idx]=x;
      }
    }

    int k;
    cin>>k;
    for(int j=1;j<=k;j++){
      int x,y;
      cin>>x>>y;
      if(!st[x]){
        st[x]=true;
        zl[++idx]=x;
      }
      gx[i].push_back({x,y});
    }
  }
    
```

然后先做一遍这个操作，看一开始有多少工程我已经可以接手了。

```cpp
     for(int i=1;i<=idx;i++){//枚举出现的种类
     	if(hashs[zl[i]].size()){
         int t=hashs[zl[i]].top().second;//第i个工程
         int sl=hashs[zl[i]].top().first;//数量
         while(sl<=has[zl[i]]&&hashs[zl[i]].size()){
             xz[t]--;
             hashs[zl[i]].pop();
             t=hashs[zl[i]].top().second;
             sl=hashs[zl[i]].top().first;
         }
     	}
    }

    //然后入队
    for(int i=1;i<=n;i++){
    	if(xz[i]==0){
      	  q.push(i);
    	}
     }
```

随后进行一个拓扑排序，大体操作和上面差不多。
```cpp
void topu(){
  while(q.size()){
    int p=q.front();
    q.pop();
    ans++;//出一次队答案加一
    
    idx=0;
    for(auto u:gx[p]){
      zl[++idx]=u.first;//这里是个优化，我只用关心更新了的种类
      has[u.first]+=u.second;
    }
    
    
    for(int i=1;i<=idx;i++){
     if(hashs[zl[i]].size()){
        int t=hashs[zl[i]].top().second;
        int sl=hashs[zl[i]].top().first;
        while(sl<=has[zl[i]]&&hashs[zl[i]].size()){
            xz[t]--;
            if(xz[t]==0){//为0入队
                q.push(t);
            }
            hashs[zl[i]].pop();
            t=hashs[zl[i]].top().second;
            sl=hashs[zl[i]].top().first;
        }
     }
    }
  }
}
```

### 最终代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=101010;
#define int long long
typedef pair<int,int> PLL;
unordered_map<int,int> has;
unordered_map<int,priority_queue<PLL,vector<PLL>,greater<PLL> >> hashs;
int n,g;
int zl[N];
unordered_map<int,int> st;
int idx=0;
int xz[N];

queue<int> q;
vector<PLL> gx[N];
int alright[N];

int ans=0;

int cnt=0;

void topu(){
  while(q.size()){
    int p=q.front();
    q.pop();
    ans++;
    
    idx=0;
    for(auto u:gx[p]){
      zl[++idx]=u.first;
      has[u.first]+=u.second;
    }
    
    
    for(int i=1;i<=idx;i++){
     if(hashs[zl[i]].size()){
        int t=hashs[zl[i]].top().second;
        int sl=hashs[zl[i]].top().first;
        while(sl<=has[zl[i]]&&hashs[zl[i]].size()){
            xz[t]--;
            if(xz[t]==0){
                q.push(t);
            }
            hashs[zl[i]].pop();
            t=hashs[zl[i]].top().second;
            sl=hashs[zl[i]].top().first;
        }
     }
    }
  }
}

signed main(){
  ios::sync_with_stdio(false);

  cin>>g; 
  for(int i=1;i<=g;i++){
    int x,y;
    cin>>x>>y;
    has[x]+=y;
  }
  
  cin>>n;
  for(int i=1;i<=n;i++){
    int m;
    cin>>m;
    xz[i]=m;

    for(int j=1;j<=m;j++){
      int x,y;
      cin>>x>>y;
      hashs[x].push({y,i});
      if(!st[x]){
        st[x]=true;
        zl[++idx]=x;
      }
    }

    int k;
    cin>>k;
    for(int j=1;j<=k;j++){
      int x,y;
      cin>>x>>y;
      if(!st[x]){
        st[x]=true;
        zl[++idx]=x;
      }
      gx[i].push_back({x,y});
    }

  }
    
    
    
  
    for(int i=1;i<=idx;i++){
     if(hashs[zl[i]].size()){
        int t=hashs[zl[i]].top().second;
        int sl=hashs[zl[i]].top().first;
        while(sl<=has[zl[i]]&&hashs[zl[i]].size()){
            xz[t]--;
            hashs[zl[i]].pop();
            t=hashs[zl[i]].top().second;
            sl=hashs[zl[i]].top().first;
        }
     }
    }

    
  for(int i=1;i<=n;i++){
    if(xz[i]==0){
      q.push(i);
    }
  }

  topu();

  cout<<ans<<endl;

  return 0;
} 
```
时间复杂度为：$O(n\log n)$，优先队列乘上拓扑排序。







---

## 作者：happy_lazier (赞：1)

题中有一个很容易想到的地方便是每个任务如果完成，那么在之后便不用管这个任务了，而对于每个任务而言，只有在它每个限制均被完成之后才会返回收益，那么考虑如何快速地检测限制是否被完成，要注意到单单对于某一种员工来说，可能有多个任务在这种员工上有限制，那么不妨先达到较小的限制，再满足较大的，考虑开 $2n$ 个优先队列来取出当前对于这个员工，有限制且限制最小的任务，然后在其限制均完成后获得它的价值，最后的答案便是限制均被完成的任务数量。
  
（注意：没有限制的任务需要提前将其收益取走。）
  
  [代码](https://www.luogu.com.cn/paste/wqx5no8f)

---

## 作者：Auto_Accepted (赞：1)

对于每个工程，按照不同工种去逐个维护。当一个工程的所有工种都满足要求的时候，将它放入优先队列。

然后当一个工程被取出时，我们去看他的奖励。对于每个工种分别处理，如果别的需要这个工种的工程里这个工种满足了要求，则这个工程的需求数目减去一，需求数量变为 $0$ 的工程继续入队，最后输出在队列中被取出的工程数即可。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair <int , int>
#define pu push
#define pb push_back
int t[1000005] , u[1000005] , m[1000005] , k[1000005] , g , n , ans;
map < int , int > w;
map < int , priority_queue < PII , vector < PII > , greater < PII > > > tmp;
vector < PII > pepole[1000005];
deque <int> q;
signed main(){
    cin >> g;
    for(int i = 1;i <= g;i++){
        cin >> t[i] >> u[i];
    }
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> m[i];
        int u , v;
        for(int j = 1;j <= m[i];j++){
            cin >> u >> v;
            tmp[u].pu(make_pair(v , i));
        }
        cin >> k[i];
        for(int j = 1;j <= k[i];j++){
            cin >> u >> v;
            pepole[i].pb(make_pair(u , v));
        }
    }
    for(int i = 1;i <= n;i++){
        if(!m[i]){
            q.pb(i);
        }
    }
    for(int i = 1;i <= g;i++){
        w[t[i]] += u[i];
        int p = w[t[i]];
        while(tmp[t[i]].size()){
            PII f = tmp[t[i]].top();
            if(f.first > p){
                break;
            }
            tmp[t[i]].pop();
            m[f.second]--;
            if(!m[f.second]){
                q.pb(f.second);
            }
        }
    }
    for(int i = 0;i < q.size();i++){
        for(auto ttmp : pepole[q[i]]){
            w[ttmp.first] += ttmp.second;
            int p = w[ttmp.first];
            while(!tmp[ttmp.first].empty()){
                PII f = tmp[ttmp.first].top();
                if(f.first > p){
                    break;
                }
                tmp[ttmp.first].pop();
                m[f.second]--;
                if(!m[f.second]){
                    q.pb(f.second);
                }
            }
        }
    }
    cout << (q.size());
    return 0;
}
```


---

## 作者：Kedit2007 (赞：1)

题意比较复杂，这里不作复述。[P9557 原题链接](https://www.luogu.com.cn/problem/P9557)。


### 思路

首先考虑如何存储每个种类的员工的数量，由于工种编号值域比较大，可以采用 `map` 或者 `unordered_map` 进行存储，以工种为键、目前该工种人数为值。

接下来，考虑某一个工种的人数增加造成的影响。当一个工种的人数增加时，所有需要这个工种的工程都有机会变得可以承接。考虑再用一个 `map`，以工种为键、需要该工种的工程对应的需求为值。例如，对于这样三个工程：

1. 需要工种 $1$ 人数至少为 $1$；需要工种 $2$ 人数至少为 $2$。
2. 需要工种 $2$ 人数至少为 $2$。
3. 需要工种 $2$ 人数至少为 $4$；需要工种 $3$ 人数至少为 $1$。

可以考虑如此存储：

|    工种 $1$    |    工种 $2$    |    工种 $3$    |
| :----------: | :----------: | :----------: |
| 工程 $1$ 需求 $1$ | 工程 $1$ 需求 $2$ | 工程 $3$ 需求 $1$ |
|             | 工程 $2$ 需求 $2$ |              |
|             | 工程 $3$ 需求 $4$ |              |

这样，在每次更新一个工种的人数时，就可以检查是否有工程的需求被满足。我们只需要记录每一项工程还有多少个需求没有被满足，即可快速得出在增加一个工种的人数时，有哪些需求被满足，进而有哪些工程变得可以承接。

### 实现

有了思路后，我们一步步考虑如何实现。

首先，将思路中需要的存储容器开好。由于一个工种的人数总是会先满足人数较少的需求，可以考虑对需求进行排序或使用优先队列进行维护，以减小查找满足需求的时间复杂度。下面的代码中使用了优先队列。

在这份代码中，优先队列存的是一个 `pair<int, int>`。第一个元素代表需求的人数，第二个元素代表需求来自哪个工程。两者顺序不能颠倒，因为我们需要对需求人数进行排序。

```cpp
template<typename T> // 小根堆别名
using inv_pque = priority_queue<T, vector<T>, greater<T>>;

map<int, int> cnt; // 每个工种的人数
map<int, inv_pque<pair<int, int>>> creq; // 每个工种对应的需求，对应思路中的表格
vector<int> reqleft(n); // 每个工程还剩下多少个需求需要满足
```

接下来一步步处理每个工程。对于每个工程，首先将需求一个个加到表中：

```cpp
int m; // 需求个数
cin >> m;
reqleft[i] = m; // 记录初始需求个数
for (int j = 0; j < m; j++)
{
    int a, b;
    cin >> a >> b;
    creq[a].push({b, i}); // 将需求加入表格中
}
```

接着，记录一下每个工程承接后的奖励：

```cpp
// 用于存储奖励的数组定义
// n 为工程个数
vector<vector<pair<int, int>>> rewards(n)


// 对于每个工程
int k; // 奖励个数
cin >> k;
rewards[i].resize(k);
for (auto& p : rewards[i])
{
    cin >> p.first >> p.second;
}
```

处理完工程后，就可以着手处理“增加工种人数”的操作了。由于队首永远是人数需求最小的需求，我们只需要不断比较队首的大小，直到没有需求或者队首需求不被满足即可，这个循环的条件在这里暂时不给出，可以参考结尾的完整程序。

对于每个新被满足的需求，将其对应工程的剩余需求个数减一，若更改后对应工程的剩余需求个数减至 $0$，则代表该工程已经可以承接。相关代码：

```cpp
int rid = creq[x].top().second; // 对应的工程编号
creq[x].pop(); // 退出优先队列
reqleft[rid]--; // 减少工程的剩余需求个数
if (reqleft[rid] == 0)
{
    // 这个工程可以承接了
}
```

最后就只需要不断承接能够承接的工程，获得对应的奖励，并更新能够承接的工程即可。

有一个小细节，在上面给出的代码实现中，需要在一开始先处理没有任何需求的工程，因为它们永远不可能被加到表格中任何一个地方，也就不可能在更新时被认为“可以承接”。

至于最初已有的员工，只需要在处理完所有工程后一个个工种地执行“增加工种人数”操作即可。

### 完整参考代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

template<typename T>
using inv_pque = priority_queue<T, vector<T>, greater<T>>;

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int g;
    cin >> g;
    map<int, int> cnt;
    map<int, inv_pque<pair<int, int>>> creq;
    deque<int> avail;
    for (int i = 0; i < g; i++)
    {
        int t, u;
        cin >> t >> u;
        cnt[t] += u;
    }
    
    int n;
    cin >> n;
    vector<int> reqleft(n);
    
    vector<vector<pair<int, int>>> rewards(n);
    
    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m;
        reqleft[i] = m;
        for (int j = 0; j < m; j++)
        {
            int a, b;
            cin >> a >> b;
            creq[a].push({b, i});
        }
        if (m == 0)
        {
            avail.push_back(i);
        }
        int k;
        cin >> k;
        rewards[i].resize(k);
        for (auto& p : rewards[i])
        {
            cin >> p.first >> p.second;
        }
    }
    
    auto update = [&](int x)
    {
        while (!creq[x].empty() && creq[x].top().first <= cnt[x])
        {
            int rid = creq[x].top().second;
            creq[x].pop();
            reqleft[rid]--;
            if (reqleft[rid] == 0)
            {
                avail.push_back(rid);
            }
        }
    };
    
    for (const auto& p : cnt)
    {
        update(p.first);
    }
    
    int ans = 0;
    while (!avail.empty())
    {
        ans++;
        int ord = avail.front();
        avail.pop_front();
        for (const auto& p : rewards[ord])
        {
            cnt[p.first] += p.second;
            update(p.first);
        }
    }
    
    cout << ans << '\n';
}
```

---

## 作者：FwbAway (赞：1)

首先采用贪心策略：能选择的全部选择，不能选择的择优选择。

暴力思路：枚举一遍 $n$ 个工程后，判断员工是否承接后还可以进行下一次承接，如果剩最后一次择最优承接。逐步枚举剩下的所有工程，直到不能承接。

但我们可以想到去设置一个 $q$ 队列，将所有**满足条件**的工程加入队列 $q$，我们肯定取所有中工程最少的工作来更新 $q$ 中的值，所以这就是一个贪心策略。

我们可以考虑离散化后的拓扑，也可以考虑图形动态规划，但是最好的方法还是用队列保存所有可能然后加以判断，和其他题解不同的是，$q$ 中存的数可以使用优先队列来存储，自定义一下小于号的排序方式即可。

我们每承接一个工程，考虑下一个员工承接哪个工程或者不承接，直接进行判断即可，用一个桶记录员工编号，可以使用结构体保存输入，否则自定义小于号可能会有一些麻烦，但是也可以接受。

总结：每一次取出最小代价的一个工程，放入队列，进行判断员工的可行性，用桶存储员工编号，如果用图形动态规划考虑离散化，不用则直接队列模拟。

---

## 作者：Your_Name (赞：0)

## 题解
观察到一个性质，员工数不会变小，那么之前满足条件的项目后面也可以接，因此贪心地考虑，能承包就承包，一定是最优的。

所以我们如果暴力的话显然是 $O(n^3)$，会超时，那么我们考虑优化。

其实，我们只要动态维护每个项目当前有几个部门满足要求，那么如果满足的要求数就是这个项目总要求数，这个项目就可以被承包。

发现对于每个项目的某个要求只有在对应部门加了人才有可能改变，所以我们每次维护哪些部门被改变了，再去对应部门的所有要求里找有没有原来没满足现在满足的项目。

于是我们用小根堆维护每个部门的所有要求，每次暴力弹直到这个要求不能被满足。因为不会重复入队且题目保证 $\sum m_i\le10^5$，所以复杂度是对的。

最后注意要离散化。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const int N = 3e5 + 10;//离散化之后最多这么多部门
unordered_map<LL, LL> ma;//离散化用的
LL g, n, idx, a[N], x, y, m[N], k[N], ans;
LL now[N];//这个项目目前被满足了多少个要求。
priority_queue<PII, vector<PII>, greater<PII>>q[N];
vector<vector<PII>> xm;
queue<LL> sol;
vector<LL> s;//改了的部门
void work(){
    for(auto i : s){
        while(!q[i].empty() && q[i].top().first <= a[i]){
            LL u = q[i].top().second;
            now[u] ++;
            if(now[u] >= m[u])sol.push(u);
            q[i].pop();
        }
    }
    s.clear();
}
void make(){
    while(!sol.empty()){
        LL u = sol.front();
        sol.pop();
        ans ++;
        for(auto i : xm[u - 1]){
            a[i.first] += i.second;
            s.push_back(i.first);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> g;
    for(LL i = 1; i <= g; i ++){
        cin >> x >> y;
        if(ma[x] == 0)ma[x] = ++ idx;
        a[ma[x]] = y;
        s.push_back(ma[x]);
    }
    cin >> n;
    for(LL i = 1; i <= n; i ++){
        cin >> m[i];
        if(m[i] == 0)sol.push(i);//这里要特判
        for(LL j = 1; j <= m[i]; j ++){
            cin >> x >> y;
            if(ma[x] == 0)ma[x] = ++ idx;
            q[ma[x]].push({y, i});
        }
        cin >> k[i];
        vector<PII> z;
        z.push_back({0, 0});
        for(LL j = 1; j <= k[i]; j ++){
            cin >> x >> y;
            if(ma[x] == 0)ma[x] = ++ idx;
            z.push_back({ma[x], y});
        }
        xm.push_back(z);
    }
    work();
    while(!sol.empty()){
        make();
        work();
    }
    cout << ans;
    return 0;
}
```
 _完结撒花。_

---

## 作者：_299817_ (赞：0)

## Part 0：前言
码量不大的模拟。

## Part 1：思路
首先这题应该有个很显然的贪心，就是如果我们可以做完这个项目，那么这个项目一定要做，因为做完之后员工的数量不会减少，这样我们就能做更多的项目了。

但是这有一个问题，如果我们做完了这个项目，收获完员工之后，我们似乎要重新再扫描一遍所有项目，看看哪些项目可以做。

但是很显然这样做时间复杂度是不满足题目要求的。

我们对于每个项目，去记录下它还有哪几种的员工人数满足条件，当我们做完一个项目之后，只考虑得到的员工的那些种类，看看这些种类加上这些员工能不能满足条件，如果我们发现我们记录的一个项目的员工人数已经满足了条件，我们就可以去做这些项目。

具体来说，就是我们把所有的项目需要的不同种类的员工丢进不同的优先队列里面，然后记录每个项目还有多少种员工没有满足条件，当我们收获员工的时候，去访问对应员工种类的那些优先队列，看看我们还能满足多少个要求，当一个项目的每个种类的员工全都满足条件之后，我们就把它推进队列里面，然后重复以上操作。

思想很像 BFS。

然后这里员工种类是 $10^9$ 级别的，你可以选择离散化或者使用 `map`，笔者这里是使用的 `map`。

## Part 2：代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#include<cstdint>
using namespace std;
#define rep(i, l, r) for(i32 i = (i32)(l); i <= (i32)(r); i++)
#define per(i, l, r) for(i32 i = (i32)(l); i >= (i32)(r); i--)
#define FILEIO(INNAME, OUTNAME) freopen(INNAME".in", "r", stdin), freopen(OUTNAME".out", "w", stdout)
#define sort stable_sort
#define map unordered_map
#ifdef QwQ_ATM
    #define Debug(x) cout << "---------- #Debug " << x << " ----------" << endl
    #define DDebug(s, x) cout << s << x
    #define Output(x) cout << x
#else
    #define Debug(x) 1
    #define DDebug(s, x) 1
    #define Output(x) 1
    #define endl '\n'
    #include<bits/stdc++.h>
#endif
#define int long long
typedef pair<int, int> pii;
using i32 = int32_t;
using i64 = int64_t;

const int MAXN = 100010;

// 快读快写。
inline int read(){
    int quick_read2 = 1, quick_read1 = 0;
    char quick_read3 = getchar();
    while(quick_read3 < '0' || quick_read3 > '9'){
        if(quick_read3 == '-') quick_read2 = -1;
        quick_read3 = getchar();
    }
    while(quick_read3 >= '0' && quick_read3 <= '9') quick_read1 = quick_read1 * 10 + quick_read3 - '0', quick_read3 = getchar();
    quick_read1 *= quick_read2;
    return quick_read1;
}

inline void write(int quick_write1){
    if(quick_write1 < 0) putchar('-'), quick_write1 = -quick_write1;
    if(quick_write1 > 9) write(quick_write1 / 10);
    putchar(quick_write1 % 10 + '0');
    return;
}

int g, n;
map<int, priority_queue<pii, vector<pii>, greater<pii>>> pq; // 不同项目的每个种类的员工需要个，使用优先队列存储。
map<int, int> usr; // 我们现在每个项目有多少给员工。
vector<pii> gget[MAXN]; // 每个项目得到的员工。
int cnt[MAXN]; // 每个项目还有多少种员工没有满足条件。
int ans; // 答案。

i32 main(){
    #ifdef QwQ_ATM
        FILEIO("input", "output");
    #endif
    cin >> g;
    rep(i, 1, g) usr[read()] = read();
    cin >> n;
    queue<int> q; // 类似于 BFS，使用队列。
    rep(i, 1, n){
        int m = cnt[i] = read();
        bool flag = true; // 用来判断我们最开始可不可以做这个项目。
        vector<int> c(m + 1), d(m + 1);
        rep(j, 1, m){
            c[j] = read(), d[j] = read();
            if(usr[c[j]] < d[j]) flag = false;
            else cnt[i]--;
        }
        if(flag) q.push(i), cnt[i] = 0; // 如果可以就直接推进队列。
        else{ rep(j, 1, m){ if(usr[c[j]] < d[j]) pq[c[j]].push({d[j], i}); } } // 如果不可以做那就记录还有哪些种类的员工不够。
        int k = read();
        while(k--) gget[i].push_back({read(), read()}); // 记录每个项目得到的员工。
    }
    while(!q.empty()){ // 进行 BFS。
        int u = q.front();
        q.pop(), ans++;
        for(auto p : gget[u]){ // 看看我们这些项目能得到哪些员工
            int v = p.first, w = p.second;
            usr[v] += w;
            while(!pq[v].empty() && usr[v] >= pq[v].top().first){ // 对我们得到的员工种类进行处理。
                int x = pq[v].top().second;
                pq[v].pop(), cnt[x]--;
                if(cnt[x] == 0) q.push(x); // 这里表示项目 x 的所有的条件都满足了，我们就可以把它推进队列。
            }
        }
    }
    write(ans), putchar('\n'); // 输出。
    return 0;
}
```

---

