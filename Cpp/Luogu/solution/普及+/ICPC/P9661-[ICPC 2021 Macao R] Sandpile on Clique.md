# [ICPC 2021 Macao R] Sandpile on Clique

## 题目描述

阿贝尔沙堆模型（Abelian Sandpile Model）是一个著名的显示自组织临界性的动力学系统。自从它由 Per Bak、Chao Tang 和 Kurt Wiesenfeld 在 1987 年的一篇论文中引入以来，它已经被研究了数十年。沙堆模型的预测引起了物理学、计算机科学和数学的广泛关注，这不仅是因为它美丽的代数结构，还因为它与负载平衡和内部扩散有关的模型的应用，如去随机化。沙堆模型与许多其他模型和物理现象相关，如转子路由模型、雪崩模型。

在沙堆模型中，给定一个顶点编号从 $1$ 到 $n$ 的无向图 $G$。我们还给出了 $n$ 个整数 $a_1, a_2, \cdots, a_n$，其中 $a_i$ 表示初始时放置在顶点 $i$ 上的筹码数量。每个回合，我们将选择一个任意的顶点 $v$，使得 $v$ 上的筹码数量不小于与 $v$ 相连的边数，记为 $d_v$。对于 $v$ 的每个邻居，它将从 $v$ 接收一枚筹码。因此，$v$ 将失去 $d_v$ 枚筹码。这个过程被称为 ``firing`` 或 ``toppling``。直到没有顶点 $v$ 至少有 $d_v$ 枚筹码时，firing 才会停止。

可以证明，firing 的顺序不会影响结果。同时，也可能 firing 永远不会终止。这种情况被描述为“recurrent”。现在给定一个团和初始筹码数量，请确定这个实例是否是一个 recurrent 实例。如果不是，请分别输出每个节点的最终筹码数量。

团（也称为完全图）是一个图，其中任意两个顶点都有边相连。

## 样例 #1

### 输入

```
5
5 0 3 0 3```

### 输出

```
3 3 1 3 1```

## 样例 #2

### 输入

```
2
1 0```

### 输出

```
Recurrent```

# 题解

## 作者：小李先生 (赞：1)

# P9661题解
### 前言
看了看其他题解有用优先队列解决的这里提供一个用  **sort** 代替**优先队列**的方法。
### 题意



有一个 $n$ 个节点的完全图，如果有一个节点有 $n-1$ 以上的数值，便可以让除此节点外的节点数值 $+1$，让此节点 $-(n-1)$。

如果此操作能不断进行下去，输出 `Recurrent`，否则按照最终操作完的序列输出。
### 思路
暴力思路是一直都找当前最大的数作为“散财童子”散筹码，直到最大的数不满足大于等于 $n-1$。


为了方便找到当前最大的数 `sort` 从大到小排序。~~为什么没用**优先队列**是因为 vp 时没想到~~。然后每次操作一个数的时候都加上在这之前已经被分的筹码。这样就可以**通过预处理线性地找到当前最大的数**。然后就是简单的模拟就可以过啦。

具体详细思路和代码解释已经在下面的代码注释中呈现，欢迎不懂的评论 ~~da lian~~ 互动。
### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
const int N = 1e6+10;

ll n,m,t;
pair<ll,ll> a[N],b[N];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for( ll i = 1; i <= n; i++)	cin >> a[i].first;
	for( ll i = 1; i <= n; i++)	a[i].second = i;

	
     for(ll tt = 1; tt <= 2; tt++)//之所以是2是因为一轮操作可能无法到达 n-1 次需要两轮... 
    {
    	sort(a + 1, a + n + 1,greater<pair<ll,ll> >() );//从大到小排序优化操作流程。
    	
        ll cnt[N];
        for(ll i = 0;i <= n + 1; i++ ) cnt[i] = 0;//预处理。
        
        for( ll i = 1; i <= n; i++)
        {
            cnt[i] += cnt[i - 1];//算是一种前缀和。
            a[i].first += cnt[i];//加上在这之前已经被分的筹码。
	
            if(a[i].first >= n - 1) 
            {
                cnt[i + 1] = a[i].first / (n - 1);
                //第 i 个人给其他人分出去的筹码。
                a[i].first = a[i].first % (n - 1) - cnt[ i + 1]; 
				//因为之后每一个人都会加上被分的筹码，而实际上自己分出去的筹码自己是得不到的所以要减去。
            }
        }
        cnt[n + 1] += cnt[n] ;//代表这一轮操作中所有人分出去的筹码数量（对于某一个人）。

        for( ll i = 1; i <= n; i++)
        {
            a[i].first += cnt[n + 1] - cnt[i];
            //这一轮所有的数量减去当时已经被他所加上的数量就是——还欠他没给他加上的筹码数。
        }
    }    
    
    //如果此时还能够再进行新的一轮就说明会不断循环。
	if(a[1].first >= n - 1)	
	{
		cout << "Recurrent\n";
		return 0; 
	}
	
	//下为按原顺序输出。
	for(ll i = 1; i <= n; i++)
	{
		b[i].second =  a[i].first;
		b[i].first = a[i].second;
	}
	sort(b + 1, b + n + 1) ;
	
	for(ll i = 1; i <= n; i++)
	cout<<b[i].second <<" ";
	
	return 0;
}
```
~~第一次上传题解，希望通过。~~

---

## 作者：naroto2022 (赞：1)

# P9961 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P9661)

### 题意

给定一张 $n$ 个点的**完全图**，每个点有点权 $a_i$，每一次要选一个点满足 $a_i>=n-1$，然后令其他点的点权加一，这个点权减去 $n-1$，问操作若干次后无法操作时点权分别是多少，如果不会出现操作不了就输出 `Recurrent`。

### 思路

其实就是一道非常非常简单的模拟题。。。

当然，要动点脑筋。（不然怎么是绿。）

首先是判断无解，可以考虑把所有大于等于 $n-1$ 的部分全部取出来，最后再把这一部分贡献加回去。（注意这里取出贡献的点也要减一，这样就不用麻烦的判断贡献出自哪里，下面模拟也一样。）此时的点权排序一下若有一个小于 $i-1$ 那么就说明这一定是有解的，正确性显然。

接下来就是模拟，懂点小脑筋，考虑每个大于等于 $n-1$ 的点不要把贡献直接加给别的点，而是将每个点会产生的贡献加起来，最后统计答案的时候再加上，不然就会大大增加时间复杂度，因为在模拟的时候已经保证了一定不会不会操作不了，所以可以放心大胆的利用优先队列（从大到小排序）模拟。

于是，你就过了这道题。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#define ll long long
#define pll pair<ll,ll>
using namespace std;
const int MN=5e5+5;
ll n,a[MN],b[MN],cnt,ans[MN];
priority_queue<pll> q;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
bool pd(){//判断无解
    cnt=0;
    for(int i=1; i<=n; i++) b[i]=a[i];
    for(int i=1; i<=n; i++){
        ll num=b[i]/(n-1);
        b[i]%=(n-1);b[i]-=num;cnt+=num;
    }
    for(int i=1; i<=n; i++) b[i]+=cnt;
    sort(b+1,b+1+n);cnt=0;
    for(int i=1; i<=n; i++) if(b[i]<i-1) return false;
    return true;
}
int main(){
    n=read();
    for(int i=1; i<=n; i++) a[i]=read();
    if(pd()){printf("Recurrent\n");return 0;}
    for(int i=1; i<=n; i++) q.push({a[i],i});
    while(q.top().first+cnt>=n-1){
        pll tmp=q.top();q.pop();cnt++;
        q.push({tmp.first-n,tmp.second});
    }
    while(!q.empty()){
        pll tmp=q.top();q.pop();
        ans[tmp.second]=tmp.first+cnt;
    }
    for(int i=1; i<=n; i++) write(ans[i]),putchar(' ');
    return 0;
}
```

---

## 作者：_Kimi_ (赞：1)

# P9661题解

### 前言

这翻译的什么东西

### 题意

给一个有 $n$ 个点的完全图，每个点有一个点值。每次进行一次操作，操作是这样的：如果一个点的点权大于与它相连的边数，就另权值减去与它相连的边数，并给与它相连的点点权加一。

如果此操作能不断进行下去，输出 ```Recurrent```，否则按操作完的序列输出。

### 思路

对于 $i\in  \left \{ 1, 2, \dots n \right \} $ 有 $A[i] \ge i - 1$ 就有循环，但是会有极端数据出现，如样例二，所以先把大于 $n - 1$ 的减掉，加回去，排序，特判就没问题了。

操作用优先队列来模拟就好了，比较简单，看代码理解理解就好。

### 代码


```cpp
//code by Kimi
#include<bits/stdc++.h>
#define int long long
#define sept fixed << setprecision(4)
#define debug(x) cerr << (#x) << endl
#define pb emplace_back
#define endl '\n'
#define WA AC
using namespace std;
const int maxn = 5e5 + 10;
int n, v;
int A[maxn], B[maxn], ans[maxn];
priority_queue<pair<int, int> > q;
void check(){
	int tmp;
	for(int i = 1; i <= n; i++) B[i] = A[i];
	for(int i = 1; i <= n; i++){
        tmp = B[i] / (n - 1);
        v += tmp;
		B[i] %= (n - 1), B[i] -= tmp;
    }
    for(int i = 1; i <= n; i++) B[i] += v;
    sort(B + 1, B + n + 1);
    for(int i = 1; i <= n; i++){
    	if(B[i] < i - 1) return;
	}
	cout << "Recurrent" << endl;
	exit(0);
}
void input(){
	srand(19491001);
    ios::sync_with_stdio(0);
	cin.tie(0);
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> A[i];
	check();
	v = 0;
}
void init(){}
signed main(){
	init();
	input();
	for(int i = 1; i <= n; i++) q.push({A[i], i});
	while(q.top().first + v >= n - 1){
        int top1 = q.top().first, top2 = q.top().second;
		q.pop();
        top1 += v, top1 -= (n - 1), v++;
        q.push({top1 - v, top2});
    }
    while(q.size()){
        auto top = q.top();
		q.pop();
        ans[top.second] = top.first + v;
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：HFanGDoDM (赞：1)

## 前置知识

图论基础、[线段树](https://www.luogu.com.cn/problem/P3372)

# 题意简述

给定一张 $n$ 个点的无向 **完全图**，每个点有点权 $a_i$。执行这一过程：每一轮选定一个点，满足 $a_i\geqslant  d_i$（其中 $d_i$ 表示结点 $i$ 的度数），并将与其直接相邻的所有点的点权增加 $1$ ，将 $a_i\leftarrow a_i-d_i$。若没有这样的点可选，则该过程终止。若该过程无法终止，则称该过程是 $\texttt{recurrent}$ 的。

给定每个点的初始点权。若该过程不是 $\texttt{recurrent}$ 的，输出上述过程终止后每个点的点权。否则，输出 `Recurrent`。

**数据范围**

$2\leqslant n\leqslant 5\times 10^5$，$0\leqslant a_i\leqslant 10^9$。

# 解题思路

根据题意，模拟这一过程的前 $(n-1)$ 轮。

若 $(n-1)$ 轮后，仍存在结点的点权不小于 $n-1$，则该过程是 $\texttt{recurrent}$ 的。

否则过程结束，此时每个点的点权即为符合题意的答案。

**正确性证明**

由于该图是无向 **完全图**，故每个点的度数等于 $n-1$。

对于任意的连续 $(n-1)$ 轮操作，必然存在至少一个结点 $u$，满足该结点在这 $(n-1)$ 轮中都没有被选定。因此，**该结点在这 $(n-1)$ 轮中必然积累了 $n-1$ 的点权**。由于 $d_u=n-1$，故此时必然有 $a_u\geqslant n-1=d_u$，则点 $u$ 满足了执行该操作的条件，**可以再执行一轮操作**。

以上的连续 $(n-1)$ 轮操作 **可以平移**，即 $\forall i,i+1,i+2,...,i+n-2$ 这 $(n-1)$ 轮，都满足上述性质。因此得证：

若满足在前 $(n-1)$ 轮后，仍存在点权不小于 $n-1$ 的结点，则该过程是 $\texttt{recurrent}$ 的。

否则，由于此时不存在点权不小于 $n-1$ 的结点，故 **满足过程终止条件**，也即得证：该过程不是 $\texttt{recurrent}$ 的，最终每个点的点权即为符合题意的答案。

**具体实现**

对于前 $(n-1)$ 轮中的每一轮操作，实际上是执行这样的过程：寻找一个点权不小于 $n-1$ 的结点，将其点权减去 $n-1$，并对其他所有结点点权增加 $1$。

对于寻找的过程，我们只需要找到当前 **点权最大** 的结点即可。

最后需要查找每个点的点权。

因此，我们需要维护全局查最大值、区间加与单点查值。使用 **线段树** 维护区间加的懒标记与区间的最大值即可。

执行完 $(n-1)$ 轮，我们需要判断全局最大值是否大于或等于 $n-1$，若是，则输出 `Recurrent`，否则顺次输出每个点的点权。

**时间复杂度分析**

使用线段树执行 $(n-1)$ 轮操作，在每一轮中，查全局最大值的复杂度为 $O(1)$，区间加的复杂度为 $O(\log n)$。最后每个点单点查值的复杂度为  $O(\log n)$。

总时间复杂度 $O(n\log n)$，可以通过本题。

**参考核心代码**

下列赛时代码实际上模拟执行的轮数大于等于 $n-1$，但复杂度还是对的。

```cpp
sgt.Build(1,1,n);//这里的sgt是线段树
for(i=1;i<=n-1;i++){
	long long val=sgt.MaxAll().first,pos=sgt.MaxAll().second;
   //MaxAll()函数返回全局最大值，即mx[1]
	if(pos>1)
		sgt.AddInterval(1,1,pos-1,val/(n-1));//区间加；其实这里只执行1轮即可，加的值应为1
	if(pos<n)
		sgt.AddInterval(1,pos+1,n,val/(n-1));
	sgt.AddInterval(1,pos,pos,-(val/(n-1)*(n-1)));//同样，这里只需要执行一轮，加上-val即可
}
if(sgt.MaxAll().first>=n-1){
	printf("Recurrent");
	return 0;
}
for(i=1;i<=n;i++)
	printf("%lld ",sgt.MaxInterval(1,i,i).first);//赛时写成了区间查最大值，但和单点查值等价
```

---

## 作者：__HHX__ (赞：1)

# 大意
有一个 $n$ 个节点的完全图，如果有一个节点有 $n - 1$ 以上的数值，便可以让除此节点外的节点数值 $+1$，让此节点 $-(n - 1)$。

如果此操作能不断进行下去，输出 ``Recurrent``，否则按照最终操作完的序列输出。
# 思路
使用了**优先队列**，每次返回的一定是这些节点数值最大的。

如果最大的都无法再操作，这个图任何节点将无法操作。

当然我不可能傻傻的在操作后修改每个值，所以我就想到了可爱的**差分**。

首先我们定义一个值 $d$ 表示这些节点所滞留（加）的值，重新加入队列时，我们不可能重新定义这个值（因为其他数还要用），所以我们要把加入的数再减个 $d$ 等访问的时候正好加回来。
# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxN = 5e5 + 3;

priority_queue< pair<long long, int> > p;

pair<int, long long> ans[MaxN];

long long d;

int tot;

void Print() {
  while (p.size()) {
    ans[++tot] = {p.top().second, p.top().first + d};
    p.pop();
  }
  sort(ans + 1, ans + tot + 1);
  for (int i = 1; i <= tot; i++) {
    cout << ans[i].second << ' ';
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    p.push({x, i});
  }
  for (int i = 1; i <= n; i++) {
    pair<long long, int> tmp = p.top();
    long long s = tmp.first + d;
    d += s / (n - 1);
    if (s < n - 1) {
      Print();
      return 0;
    }
    p.pop();
    p.push({s % (n - 1) - d, tmp.second});
  }
  cout << "Recurrent";
  return 0;
}
```

---

