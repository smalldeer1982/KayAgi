# [NWRRC 2013] Dwarf Tower

## 题目描述

小 Vasya 在玩一个新游戏叫做 Dwarf Tower。在这个游戏中有 $n$ 个不同的衣物给你的矮人。衣物从 $1$ 到 $n$ 进行编号。Vasya 想要获得编号为 $1$ 的衣物。

现在有两种方法获得一件衣物：

1. 你可以买它，第 $i$ 件物品花费 $c_i$ 元。

1. 你还可以制作它，这个游戏支持 $m$ 种制作方法。要制作一个衣物，你需要花费两个特定的衣物。

算出 Vasya 至少需要多少钱来获得一号衣物。

## 样例 #1

### 输入

```
5 3
5 0 1 2 5
5 2 3
4 2 3
1 4 5
```

### 输出

```
2
```

# 题解

## 作者：Ybll_ (赞：5)

# 题意：
$n$ 件衣服，编号为 $1$ 到 $n$，某人想要编号为 $1$ 的那一件，对于第 $a_i$ 件衣物，你可以直接购买或者用两件指定衣物 $x_i$ 和 $y_i$ 合成，求花费的最少价值。

# 思路：
一眼**dp**，很容易就可以推出公式：

$$dp_{a_i}=\min(dp_{a_i},x_i+y_i)$$

我们需要看是直接购买便宜还是合成便宜，最后直接输出 $dp_1$ 就可以了。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int id,x,y;
}a[1000005];
int n,m,dp[100005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>dp[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].id>>a[i].x>>a[i].y;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			dp[a[j].id]=min(dp[a[j].id],dp[a[j].x]+dp[a[j].y]);
		}
	}
	cout<<dp[1];
   	return 0;
}
```

---

## 作者：player_1_Z (赞：5)

~~这一题很水~~

这一题还是有一些难度的。

### 首先理解题目：

发现一件衣服的获取方式有：豪横的直接用 $c_i$ 元直接买下第 $i$ 件衣服，也可以用第 $x_i$ 件衣服和第 $y_i$ 件衣服制作第 $a_i$ 件衣服。

#### 由此推出一件衣服最少价格公式为：

```cpp
min(q[a[j]],q[b[j]]+q[c[j]])
```

#### 那么我们用一个数组把这 $n$ 件衣服的最小价格存起来再输出第 $1$ 件衣服就可以了。这样的时间复杂度就是 $O(m)$。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[100005],n,m;
int a[100005],b[100005],c[100005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>q[i];
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i];
	for(int j=1;j<=m;j++)
		q[a[j]]=min(q[a[j]],q[b[j]]+q[c[j]]);
	cout<<q[1];
	return 0;
}
```
可是这样做有可能存在制作一件衣服的材料衣服有更便宜的制作方式在后面，导致价格不是最少而出错。

#### 所以我们再套一层循环，重复计算一件衣服最少价格，这样答案就正确了，时间复杂度就是 $O(n \cdot m)$。

## 参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[100005],n,m;
int a[100005],b[100005],c[100005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>q[i];
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i];
	for(int i=1;i<=n;i++)//为避免出错而套的循环 
		for(int j=1;j<=m;j++)
			q[a[j]]=min(q[a[j]],q[b[j]]+q[c[j]]);//衣服的最少价格公式 
	cout<<q[1];
	return 0;
}
```

---

## 作者：Yxy7952 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7082)

求管理员通过 QwQ。

## 思路

我太蒻了，只能想到 $dp$，所以这篇题解主要是讲述一下这道题为什么用 $dp$ 和 $dp$ 怎么写。

### 动态规划讲解
最简单粗暴的思路是尝试所有的方案。因为时间复杂度是 $O(2^m)$ 级别的，这样的做法无法接受。

注意到这样一个事实，一个最优的方案，它的每一步决策都是最优的。

以样例为例：


```cpp
5 3
5 0 1 2 5
5 2 3
4 2 3
1 4 5
```

最优购买方案是 $2 \to 3 \to 5 \to 4 \to 1$。

以样例输出里提到的最优购买方案为例，只考虑前三步 $2 \to 3 \to 5$，不存在一个方案使购买 $5$ 花的钱比此方案花的钱更少。

而对于每一个衣物，它只有两种选择：购买或制作。因此只需要记录当前衣物的最小花钱数，用这个最小花钱数执行下一步决策，来更新后续衣物的最小花钱数。

这样做还有一个好处：我们成功缩小了问题的规模，将一个问题分成了多个规模更小的问题。要想得到第 $1$ 个衣物的最优方案，只需知道 $c_{1}$ 和 $x_{j},y_{j}$（假设这个物品能被制作，且 $a_{j}=1$）的最优方案的信息就可以了。

这时候还存在一个问题：子问题间重叠的部分会有很多，同一个子问题可能会被重复访问多次，效率还是不高。解决这个问题的方法是把每个子问题的解存储下来，通过记忆化的方式限制访问顺序，确保每个子问题只被访问一次（当然这可以自己去思考，本片不赘述）。

上面就是动态规划的一些基本思路。

接下来将具体讲述这道题的代码怎么写。

### 具体写法

设 $f(i)$ 表示获得 $i$ 号衣物花的最小钱数。$f(i)$ 就是我们所说的 **状态**，则 $f(1)$ 是最终要达到的状态，即为所求结果。

对于每个 $f(i)$，存在两种决策（如果有第二种决策的话），状态转移方程如下：

$f(i) = \begin{cases}
  c_{i} \\
  x_{j}+y_{j} & a_{j}=i \\
\end{cases}$

注意这里的第二种状态，只有当表示 $i$ 这个物品能用别的物品制作时才能进行转移。
## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m,c[100005],f[100005],a[100005],x[100005],y[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		f[i]=c[i];
	}
	for(int i=1;i<=m;i++){
		cin>>a[i]>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[a[j]]=min(f[a[j]],f[x[j]]+f[y[j]]);
			/*
			这里的做法非常巧妙。
			我们把f[i]初始化为c[i]，那么现在他的最小花钱数暂定为c[i]。
			如果它有制作方案，我们只需把原本和制作花的钱求一个最小值就行了。
			如果没有，表示这个物品只能直接购买，由于初始化原因，我们也不用再求值。 
			*/
		}
	}
	cout<<f[1];
	return 0;
}
```

---

## 作者：BruceTong (赞：3)

# 洛谷P7082 [NWRRC2013] Dwarf Tower 题解
## 题目
### 题目内容
有 $n$ 件价格分别为 $c_i$ 的衣服和 $m$ 种两两合成另一件衣服的方法，求得到 $1$ 号衣服的最小代价。
### 题意分析
将 $v_i$ 定义为得到衣服 $i$ 的最小代价，$v_i$ 初始化为 $c_i$，定义它可以由 $lson_i$ 和 $rson_i$ 合成，所以得出 $v_i=\min\{v_i,v_{lson_i}+v_{rson_i}\}$，便可以用 Dijkstra 求得答案。
## 代码
### 代码构思
我们遍历 $m$ 种合成方法，对 $i$ 进行松弛操作，将 $i$ 放入队列，然后找与编号为 $i$ 的衣服有关的合成方法，更新 $v_i$，**如果更优**，将其放入队列，对得到其它衣服最小代价进行更新，直到队列为空，输出 $v_1$ 即得到 $1$ 号衣服的最小代价。
### 代码实现
```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n,m;
int v[10010];
int s[10010][2];

vector<int> map[10010];
queue<int> q;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>v[i];
    for(int i=1;i<=m;i++){
        int a,x,y;
        cin>>a>>x>>y;
        s[a][0]=x;
        s[a][1]=y;
        //a可以由s[a][0]和s[a][1]合成
        map[x].push_back(a);
        map[y].push_back(a);
        //a的合成与x、y有关
    }
    for(int i=1;i<=n;i++){
        if(s[i][0]==0) continue;
        if(v[i]>v[s[i][0]]+v[s[i][1]]){
            v[i]=v[s[i][0]]+v[s[i][1]];
            q.push(i);
            //更新代价，加入队列
            while(!q.empty()){
                int top=q.front();
                q.pop();
                for(int nt:map[top]){
                    //遍历与top有关的合成方法，更新其代价
                    if(v[nt]>v[s[nt][0]]+v[s[nt][1]]){
                        v[nt]=v[s[nt][0]]+v[s[nt][1]];
                        q.push(nt);
                        //加入队列，继续更新
                    }
                }
            }
        }
    }
    cout<<v[1];

    return 0;
}
```


---

## 作者：violetctl39 (赞：3)

## ~~暴力碾标算~~

时间复杂度还是很不对的。

一种玄学做法。总用时4.28s。

根据题意，一个物品可以由两个特定物品得到，设 $f[i]$ 是获得一个物品的最少钱数，那么我们可以得到 $f[i]=min(f[i],f[x_i]+f[y_i])$ ， 是制作 $i$ 的特定物品。

画个图：

![](https://s4.ax1x.com/2021/12/26/TdJqnP.png)

这不就像一个树形结构嘛！

显然，由此我们发现更新一个点的最少钱数最多经过 $2n$ 次更新，况且大多数情况是没到 $2n$ 次就找到了最小值的。所以以此我们可以打个玄学大暴力，直接暴力模拟这个过程。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){f=ch=='-'?-1:f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,f[100005],a[100005],b[100005],c[100005];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)f[i]=read();
	for(int i=1;i<=m;++i)
		a[i]=read(),b[i]=read(),c[i]=read();
	for(int i=1;i<=min(5000,(int)log2(n)*500);++i)
   	//直接设一个上限，不超时就行
		for(int j=1;j<=m;++j)//暴力模拟
			f[a[j]]=min(f[a[j]],f[b[j]]+f[c[j]]);
	printf("%d\n",f[1]);
	return 0;
}
```

分享一个玄学做法，仅供参考（大佬勿喷）。



---

## 作者：TheSky233 (赞：3)

## Description

有 $n$ 件衣物，每件衣物的价格为 $c_i$，有 $m$ 条配方，其中你可以通过 $x_i$ 和 $y_i$ 来得到 $a_i$，问得到 $1$ 号衣物的最小值。

## Solution 1

思路：暴力。

我们注意到一个点从初始到最小值的这一条路径最多会被更新 $m$ 次，且大多数时候并没有到 $m$ 次，于是我们就可以写出暴力代码了。

时间复杂度：$\mathcal O(nm)$。

期望得分：$100$。

代码十分简单，不放了。

## Solution 2

思路：转图论跑最短路。

对于每一个 $\{i,c_i\}$，我们事先把它压进优先队列（小根堆）中，作为 $\text{Dijkstra}$ 起点的候选人。因为所有 $c_i \geqslant 0$，所以一开始花费最小的点不用其他合成即为最优花费。

考虑 $\text{Dijkstra}$ 的思想，随后每读入一组 $\{a_i,x_i,y_i\}$，我们就使 $x_i,y_i$ 分别与 $a_i$ 连一条边，即这两个点可以松弛 $a_i$，读完后跑 $\text{Dijkstra}$ 模板。

本题和 $\text{Dijkstra}$ 模板的最大不同点之处在于，松弛时，还要考虑和它一组的另一个材料是否被确定了最小值，如果是，则松弛，不是则跳过。

时间复杂度：$\mathcal O\left(\left(n+m\right)\log_2 n\right)$

期望得分：$100$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read(){
	int x(0); bool f(0); char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}

void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(48+x%10); 
}

const int N=1e4+5,M=1e5+5;

int n,m;
int cst[N];

struct Graph{
	int to,next,at;
}G[M<<1];

struct Dij{
	int w,to;
	friend bool operator <(Dij a,Dij b){
		return a.w>b.w;
	}
};

int head[N],cnt;
bool vis[N];

void Add(int u,int v,int at){
	G[++cnt]=(Graph){v,head[u],at}; head[u]=cnt;
}

priority_queue<Dij> q;

void Dijkstra(){
	while(!q.empty()){
		Dij f=q.top(); q.pop();
		if(vis[f.to]) continue;
		vis[f.to]=1;
		for(int i=head[f.to];i;i=G[i].next){
			int t=G[i].to;
			if(vis[G[i].at] && cst[t]>cst[f.to]+cst[G[i].at]){
				cst[t]=cst[f.to]+cst[G[i].at];
				q.push((Dij){cst[t],t});
			}
		}
	}
}

signed main(){
	n=read(); m=read();
	for(int i=1;i<=n;i++) cst[i]=read(),q.push((Dij){cst[i],i});
	for(int i=1;i<=m;i++){
		int a=read(),x=read(),y=read();
		Add(x,a,y);
		Add(y,a,x);
	}
	Dijkstra();
	write(cst[1]);
	return 0;
}
```
$\texttt{double exp:}$ [P1875](https://www.luogu.com.cn/problem/P1875)。

---

## 作者：rmxsxhl (赞：1)

很简单的题目，不知道为什么会是蓝题。

步骤很简单，好像目前也是最优解:
  1. 把所有的原材料加入队列并标记
  2. 依次取出队列中的物品，去掉标记；并看它是否可以降低另一物品的价格；如果可以并且那个物品没有标记，就把那个物品加入队列
  3. 直到队列为空
  
代码如下:
  
 ```cpp

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <deque>
#include <climits>


using namespace std;

const int kSiz = 1e4 + 10;

int N;
long long cost[kSiz];
int mark[kSiz];
vector<vector<pair<int, int> > > edge;

void read() {
    int m;
    cin >> N >> m;
    edge.resize(N + 2);
    for (int i = 1; i <= N; ++i) {
        cin >> cost[i];
    }

    int o, a, b;
    queue<int> q;
    for (int i = 1; i <= m; ++i) {
        cin >> o >> a >> b;
        edge[a].push_back({ b, o });
        edge[b].push_back({ a, o });
        if (mark[a] == 0) {
            mark[a] = 1;
            q.push(a);
        }
        if (mark[b] == 0) {
            mark[b] = 1;
            q.push(b);
        }
    }

    long long t;
    while (!q.empty()) {
        a = q.front(); q.pop();
        mark[a] = 0;
        for (auto& y : edge[a]) {
            t = cost[a] + cost[y.first];
            if (cost[y.second] > t) {
                cost[y.second] = t;
                if (mark[y.second] == 0) {
                    q.push(y.second);
                    mark[y.second] = 1;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    read();
    cout << cost[1] << endl;

    return 0;
}

```

---

## 作者：tiantianyang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7082)
### 题目大意
就是求这 $n$ 个衣服每一个的最小值。
### 思路
首先由题意可得，购买方式有：

- 我不差钱直接买，价格就是本身价值。
- 要省吃俭用一点，价格就是用来制作它的两件衣服的价格。

连起来得出最少价格是（敲黑板！重点）：

```min(c[a[i]],c[x[i]]+c[y[i]])```

最后再输出第一件衣服，就可以了。

思路通，代码实现！~~（好久，没见过这么水的蓝了）~~

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n,m;cin>>n>>m;
    int c[n+5],a[m+5],x[m+5],y[m+5];
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=m;i++) cin>>a[i]>>x[i]>>y[i];//读入 
    for(int j=1;j<=n;j++)//多套一层循环，不然会导致一些衣服最小值还未更新完 
    	for(int i=1;i<=m;i++) c[a[i]]=min(c[a[i]],c[x[i]]+c[y[i]]);//本身与花两件衣服做出的最小值 
	cout<<c[1];//求第一件衣服 
	return 0;//完美收官 
}
```

---

## 作者：MoonCake2011 (赞：1)

此题我们可以想到 dp。

dp 怎么写呢，我们可以写出状态转移方程，$dp_{a_i}=\min{(dp_{x_i}+dp_{y_i},dp_{a_i})}$。

初始化时 $dp_i=c_i$。

这样写肯定不行。
```cpp
for(int i=1;i<=m;i++)
	if(dp[a[i]]>dp[u[i]]+dp[v[i]])
			dp[a[i]]=dp[u[i]]+dp[v[i]];
```
于是我们可以用 SPFA 的迭代思想。

dp 数组最多被更新 $n-1$ 次。

唉，这不就是 bellman 算法吗？

虽然时间复杂度有亿点不对，但是因为数据水，常数小，洛谷测评姬的强大，再加上时限开的大，我们可以通过。

时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int dp[10010];
int a[100010],u[100010],v[100010];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>dp[i];
	for(int i=1;i<=m;i++)
		cin>>a[i]>>u[i]>>v[i];
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
			if(dp[a[j]]>dp[u[j]]+dp[v[j]])
				dp[a[j]]=dp[u[j]]+dp[v[j]];
	cout<<dp[1];
	return 0;
} 
```

bellman 算法还有一个优化，加上之后时限 600ms 都能卡过。

我们来看一看，如果上面代码中的一趟更新后 dp 数组没有变化，那么以后的更新肯定也没有变化（毕竟 dp 数组没有变化，对答案肯定没有影响）。

于是直接加上，用一个 `flag` 变量标记。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int dp[10010];
int a[100010],u[100010],v[100010];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>dp[i];
	for(int i=1;i<=m;i++)
		cin>>a[i]>>u[i]>>v[i];
	for(int i=1;i<n;i++){
		bool flag=0;
		for(int j=1;j<=m;j++)
			if(dp[a[j]]>dp[u[j]]+dp[v[j]])
				dp[a[j]]=dp[u[j]]+dp[v[j]],flag=1;
		if(!flag) break;
	}
	cout<<dp[1];
	return 0;
} 
```


---

## 作者：PUTONGDEYITIREN (赞：1)

# 思路
这道题是一道普通的动态规划，我们看一下题面，他说一件衣服有两种制作方式：

第一种：直接购买。

第二种：用两个衣服制作。

这种题目，我们很容易想到动态规划，那就是吧 $dp_i$ 的初始状态设为本来的价钱 $a_i$，再循环 $n$ 次，每次求这个衣服的现最小制作价钱与融合价钱的最小值。

# code

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000005],b[1000005],c[1000005],x,dp[10000005],m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>dp[i];
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) dp[a[j]]=min(dp[a[j]],dp[b[j]]+dp[c[j]]);
	cout<<dp[1]<<endl;

return 0;
}
```

---

## 作者：Emplace (赞：1)

## 题目大意
总共 $n$ 个东西，每个东西获得途径有两种。可以直接以 $c_i$ 的价格全款拿下，或者用 $b_i$ 与 $c_i$ 拼一个。
## 思路
一眼就能看出这道题能用一个超简单的动态规划。  $dp_{a_i}=\min(a_i,dp{b_i}+dp{c_i})$。但是会发现时间太慢。但我们画出一个图，会发现他就是一个树。其中 $b_i$ 和 $c_i$ 为 $ a_i $ 的子节点。而对于树，我们只需要遍历 $2n$ 遍就能将下面的全都遍历完。然后再进阶一下，用一个迭代思想，直接将 $2n$ 变成 $n$。刚刚好可以卡过去。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int dp[100010];
int a[100010],b[100010],c[100010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>dp[i];
	}
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			dp[a[j]]=min(dp[a[j]],dp[b[j]]+dp[c[j]]);
			
		}
	}
	cout<<dp[1];
	return 0;
}

```

---

## 作者：yxy666 (赞：1)

$20$ 分想法：我们利用 $dfs$ 从 $1$ 号节点往后面刷，对于每个子节点看一下有没有更好的花费。但是我们要小心，得用 $vis$ 数组标记一下那些被走过了，不然可能会出现环的情况，不停地绕来绕去。

 $100$ 分想法：我们在深入一点思考，能不能直接建边呢？思考一下，我们可以间接建边。$x,y$ 这两件衣服能拼出 $z$ 这件衣服 ，那么可以以 $x$ 和 $y$ 为中间点，建一条 $x,y,z$ 的间接建边。然后我们刷一趟单元最短路就好了啊，就是起点比较多，我们一开始把他们全都塞进队列里就好了。 $SPFA$ 和 $DIJ$ 都可以做到。单元最短路，衣服的花费就是 $dis$ 。
 
 $code$ :
 
```cpp
#include<bits/stdc++.h>
#define TT 200000
using namespace std;
const int maxn=10005,maxe=200005;
int n,m,hed,til,tot,lnk[maxn],son[maxe],another[maxe],nxt[maxe],que[maxe];
long long dis[maxn];//another是指另一件能组成的衣服
bool vis[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void ist(int x,int y,int z){another[++tot]=y;son[tot]=z;nxt[tot]=lnk[x];lnk[x]=tot;}
void spfa(){
	while(hed!=til){
		hed=(hed+1)%TT;vis[que[hed]]=0;
		for(int j=lnk[que[hed]];j;j=nxt[j]){
			if(dis[another[j]]+dis[que[hed]]>=dis[son[j]])continue;
			dis[son[j]]=dis[another[j]]+dis[que[hed]];
			if(!vis[son[j]])vis[son[j]]=1,til=(til+1)%TT,que[til]=son[j];
			int now=(hed+1)%TT;
			if(dis[que[til]]<dis[que[now]])swap(que[now],que[til]);
		}
	}
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)que[++til]=i,vis[i]=1;//把起点给塞进队列里
	for(int i=1;i<=n;i++)dis[i]=read();
	for(int i=1;i<=m;i++){
		int z=read(),x=read(),y=read();
		ist(x,y,z);ist(y,x,z);//以x或y为中间点建边
	}
	spfa();//spfa
	printf("%lld\n",dis[1]);
	return 0;
}
```


---

## 作者：__Ship_ (赞：1)

~~这道题是比较简单的。~~

题目意思是这样的：有 $n$ 件物品，每件物品 $i$ 有一个价值为 $c_i$，或者为 $x_i + y_i$ 的造价。

问 $1$ 号物品的最低造价。

这里状态题目中直接给出了，$i$ 号物品等于 $\min(m_i,m_x + m_y)$ 其中 $m$ 为第 $i$ 件物品的造价。

这就是转移方程，为什么直接用 $money$ 数组，是因为每一个服装都是当前最优，所以直接迭代是没有问题的。

然后我们从最后一号物品开始推，一直推到第一个物品就是我们的最优解。

发现很多大佬都是顺推的，不懂。


```cpp
#include<bits/stdc++.h>

using namespace std;

int n,m,a[100005],x[100005],y[100050],money[100006],t[100006];
int main(){

	cin>>n>>m;
	for(int i = 1 ; i <= n ; i++) {
		cin>>money[i];//第i件衣服的价格 
	}
	for(int i = 1 ; i <= m ; i++) {
		cin>>a[i]>>x[i]>>y[i];
	}
	for(int i = n ; i >= 1 ; i--){
		for(int j = m ; j >= 1 ; j--){
			money[a[j]]=min(money[a[j]],money[x[j]]+money[y[j]]);
			//从最后一个开始推前面我觉得比较合理,因为当前的 money[x[j]]是上一次得到的,所以说这样更合理 
		}
	}
	
	cout<<money[1];
	return 0;
}

```
放心使用

[AC记录](https://www.luogu.com.cn/record/186483165)

---

## 作者：hjyowl (赞：0)

### 题目大意

有 $n$ 个物品，第 $i$ 个物品直接购买价格为 $a_i$，有 $m$ 个关系，购买 $a_i$ 物品可以通过购买 $b_i$ 和 $c_i$ 获得。

### 思路

很明显，有一个很明显的地推公式，就是 $f_{a_i} = \min(f_{b_i}+f_{c_i},f_{a_i})$。

由于很明显做多迭代 $n$ 次，不过很明显会炸。

这里，我们呢可以考虑卡常，事实上，在平均情况下，需要迭代的次数并不多，所以说我们可以考虑不用枚举到 $n$，考虑减掉一些，只用卡到 $\frac{n}{2}$ 量级也就是 $5000$ 的范围，去给他计算，这样进行优化。

然而 $\Theta(m)$ 带一个 $5000$ 的常数恰好合适，可以卡过，然后也不会答案错误，或许是因为在随机数据下迭代次数不会太高。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010;
long long f[N];
long long a[N],b[N],c[N];
bool st[N];
long long n,m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (long long i =1 ; i <= n; i ++ ){
		cin >> f[i];
		st[i] = 1;
	}
	for (long long i = 1; i<= m; i ++ ){
		cin >> a[i] >> b[i] >> c[i];
		f[a[i]] = min(f[a[i]],f[b[i]] + f[c[i]]);
	}
	for (int i = 1; i <= 5000; i ++ ){
    	for (long long i = m; i >= 1; i -- ){
    		f[a[i]] = min(f[a[i]],f[b[i]] + f[c[i]]);
    	}
	}
	cout << f[1];
	return 0;
} 
```

---

## 作者：pies_0x (赞：0)

# P7082 [NWRRC2013] Dwarf Tower 题解
这题感觉不至于蓝，除非你打暴力。~~暴力更难打~~。

---
本题可以转化为一个另类最短路问题。

建图应该比较好想。如果 $A$ 需要 $B$ 和 $C$ 来合成，那么连一条 $B$ 到 $A$ 的单向边和一条 $C$ 到 $A$ 的单向边。  
注意，$B$ 到 $A$ 的单向边还要记录 $C$，$C$ 到 $A$ 的单向边同理。

然后跑 dijkstra。

跑之前先将每个点入堆，$dis_u$ 为 $c_u$。即每个点作为起点。

松弛操作我赛时以为是假的，不要多想。枚举当前点 $u$ 可以到的点 $v$。当然，我们建图时还记录了另一个点 $u2$，如果 $dis_v\ge dis_u+dis_{u2}$，**且 $u2$ 已经被标记，即 $dis_{u2}$ 已经确定**，才能进行松弛操作，$dis_v$ 更新为 $dis_u+dis_{u2}$。

最终答案为 $dis_1$。
## Code
```cpp
#include<cstdio>
#include<utility>
#include<vector>
#include<queue>
#include<functional>
using namespace std;

#define N 10005
#define int long long

int n,m;
vector<pair<int,int> > map[N];
int c[N];
bool vis[N];
int dis[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > heap;

int dijkstra()
{
	for(int i=1;i<=n;++i)
		dis[i]=c[i];
	for(int i=1;i<=n;++i)  // 每个点作为起点
		heap.push(make_pair(dis[i],i));
	while(heap.size())
	{
		int u=heap.top().second;heap.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		if(u==1)
			return dis[u];
		for(pair<int,int> edg:map[u])
		{
			int v=edg.first,us=edg.second;
			if(vis[us]&&dis[v]>dis[u]+dis[us])  // 不要多想，不会漏情况
				heap.push(make_pair(dis[v]=dis[u]+dis[us],v));
		}
	}
	puts("wrong");
}

signed main()
{
	// freopen("dwarf.in","r",stdin);
	// freopen("dwarf.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%lld",&c[i]);
	for(int i=1;i<=m;++i)
	{
		int u,v1,v2;
		scanf("%lld%lld%lld",&u,&v1,&v2);
		map[v1].push_back(make_pair(u,v2));
		map[v2].push_back(make_pair(u,v1));
	}
	printf("%lld",dijkstra());
	return 0;
}
```

---

## 作者：caohan (赞：0)

# 思路

很简单，容易发现，这道题有着明显的树形结构，即两个反应物为儿子，生成物为父亲的局面。则发现，每个东西只需要 $2n$ 次的更新即可，发现可以暴力，运用类记忆化的方法完成（注意迭代轮数上限的设置和卡常）。

# 代码

```cpp
#include<bits/stdc++.h>
#define inf 2100000000
using namespace std;
int f[10005];
int n,m;
int read()
{
	int x(0); bool f(0); char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
int a[100005],b[100005],c[100005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		f[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		a[i]=read();
		b[i]=read();
		c[i]=read();
	}
	for(int i=1;i<=min(5500,(int)log2(n)*500);i++)
	{
		for(int j=1;j<=m;j++)
		{
			f[a[j]]=min(f[a[j]],f[b[j]]+f[c[j]]);
		}
	}
	cout<<f[1];
	return 0;
}
```


---

## 作者：Perfonster (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P1875)

我们可以把一种制作方案看作有向图的两条边，每件衣服看作点，初始时点有点权，边无边权，这样这个问题就转化成了类似求最短路的问题。

建图：我们用类型为$\text{pair<long long,int>}$的小根堆储存$\text{\{得到这件衣服所需最小花费，这件衣服的编号\}}$。读入第$i$件衣服的价钱$cost_i$时，把$\{cost_i,i\}$压入堆中，表示跑最短路之前，得到某件衣服所需价钱即它的售价。

考虑使用$\text{Dijkstra}$的思想。每次取出一个点时，把它更新为已经确定最短路的状态。不同的是，每次松弛边操作时还要考虑合成某件新衣服所需的另一个原料，并且另一个原料也必须已经确定最短路，这样才能确保更新合成出来的衣服的最短路在这个配方中是最优解。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define maxn 10009
using namespace std;
int n,m,xx,yy,zz,head[maxn],now;
long long cost[maxn];
bool vis[maxn];
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > >q;
struct edge{
	int next,to,co;
   //e为边（配方）的结构体。e[i].to为该配方的终产品，e[i].co为该配方所需的另外一件衣服。
};
edge e[maxn*20];
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)-48+ch;
		ch=getchar();
	}
	return x;
}
void add(int x,int y,int z){//连边：x表示该边的原产品，y为另一个原产品，z为终产品
	e[++now].next=head[x];
	e[now].co=y;
	e[now].to=z;
	head[x]=now;
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		cost[i]=read();
		q.push(make_pair(cost[i],i));
	}
	for(int i=1;i<=m;i++){
		zz=read();
		xx=read();
		yy=read();
		add(xx,yy,zz);
		add(yy,xx,zz);//因为x、y哪个先更新为最短路不确定，所以一个配方要连x->z、y->z两组边。
	}
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]){
			continue;
		}
		vis[x]=true;
		for(int i=head[x];i;i=e[i].next){
			if(vis[e[i].co]&&cost[e[i].to]>cost[x]+cost[e[i].co]){//另一个产品e[i].co的vis值为true，说明已经确定最短路，可以松弛。
				cost[e[i].to]=cost[x]+cost[e[i].co];
				q.push(make_pair(cost[e[i].to],e[i].to));
			}
		}
	}
	printf("%d\n",cost[1]);//1为最终产品。
	return 0;
}
```

点个赞再走呗~

---

## 作者：Little_Cabbage (赞：0)

> 涉及知识点：动态规划。

# 解题思路

设 $dp_i$ 为得到 $i$ 最小的花费。

可以得到转移方程：$dp_{a_i} = \min(dp_{x_i} + dp_{y_i}, dp_{a_i})$。

很明显最多迭代 $n$ 次，还需要再外面套一个循化即可。

但是有些 `OJ` 没有洛谷跑得快，所以需要加一点优化。

如果当前循环没有更新任何一个数，说明当前每个数都是最优的，直接退出循环。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define fre(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

const int N = 100010;

int n, m;
int a[N], x[N], y[N], z[N];
int dp[N];

signed main() {
    IOS;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    for (int i = 1; i <= m; i ++ ) {
        int a, b, c;
        cin >> a >> b >> c;
        x[i] = a;
        y[i] = b;
        z[i] = c;
    }
    for (int i = 1; i <= n; i ++ ) dp[i] = a[i];
    for (int i = 1; i < n; i ++ ) {
        bool flag = false;
        for (int j = 1; j <= m; j ++ ) {
            if (dp[y[j]] + dp[z[j]] < dp[x[j]]) {
                dp[x[j]] = dp[y[j]] + dp[z[j]];
                flag = true;
            }
        }
        if (!flag) break;
    }
    cout << dp[1] << endl;
    return 0;
}
```

---

