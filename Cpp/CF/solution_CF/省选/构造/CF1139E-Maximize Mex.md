# Maximize Mex

## 题目描述

某学院有 $n$ 名学生和 $m$ 个社团，社团编号为 $1$ 到 $m$。每位学生有一个潜力值 $p_i$，并且是编号为 $c_i$ 的社团成员。最初，每位学生恰好属于一个社团。学院举办了一场技术节，持续接下来的 $d$ 天。技术节期间每天都会举办一次编程比赛。

每天早上，恰好有一名学生离开其所属的社团。一旦学生离开社团，就不会再加入任何社团。每天中午，院长会从每个社团中各选出一名学生（如果某个社团没有成员，则不选人），组成当天编程比赛的队伍。队伍的实力定义为队伍中所有学生潜力值的 mex。院长希望知道在接下来的 $d$ 天里，每天队伍的最大可能实力。因此，每天院长都会选择一种方案，使得队伍实力最大。

集合 $S$ 的 mex 定义为不在 $S$ 中的最小非负整数。例如，$\{0, 1, 1, 2, 4, 5, 9\}$ 的 mex 是 $3$，$\{1, 2, 3\}$ 的 mex 是 $0$，空集 $\varnothing$ 的 mex 是 $0$。

## 说明/提示

考虑第一个样例：

第一天，学生 $3$ 离开社团。现在剩下的学生是 $1$、$2$、$4$ 和 $5$。我们可以选择学生 $1$、$2$ 和 $4$，得到最大实力 $3$。注意，不能选择学生 $1$、$2$ 和 $5$，因为学生 $2$ 和 $5$ 属于同一个社团。也不能选择学生 $1$、$3$ 和 $4$，因为学生 $3$ 已经离开社团。

第二天，学生 $2$ 离开社团。现在剩下的学生是 $1$、$4$ 和 $5$。我们可以选择学生 $1$、$4$ 和 $5$，得到最大实力 $1$。

第三天，剩下的学生是 $1$ 和 $5$。我们可以选择学生 $1$ 和 $5$，得到最大实力 $1$。

第四天，剩下的学生只有 $1$。我们可以选择学生 $1$，得到最大实力 $1$。

第五天，所有社团都没有学生，因此最大实力为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3
0 1 2 2 0
1 2 2 3 2
5
3
2
4
5
1
```

### 输出

```
3
1
1
1
0
```

## 样例 #2

### 输入

```
5 3
0 1 2 2 1
1 3 2 3 2
5
4
2
3
5
1
```

### 输出

```
3
2
2
1
0
```

## 样例 #3

### 输入

```
5 5
0 1 2 4 5
1 2 3 4 5
4
2
3
5
4
```

### 输出

```
1
1
1
1
```

# 题解

## 作者：xht (赞：11)

题目地址：[CF1139E Maximize Mex](https://www.luogu.org/problemnew/show/CF1139E)

这其实是一个二分图匹配匈牙利算法的巧妙运用

考虑倒序回答

则由原来的删除改为添加

把 **potential** 值作为左部，则一共有编号为 $0~m$ 共 $m+1$ 个左部点

把 **club** 作为右部点

对每一个当前存在的对应关系添加一条对应的无向边

每次回答相当于从小到大对每一个左部点进行匹配，直到无法匹配，此时无法匹配的即为当前答案

之后每添加一条边在上次匹配后的图上继续匹配即可

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 6;
int n, m, d, a[N], b[N], c[N], ans[N], v[N], w[N], f[N];
vector<int> e[N];

bool dfs(int x) {
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y]) continue;
        v[y] = 1;
        if (!~f[y] || dfs(f[y])) {
            f[y] = x;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    cin >> d;
    for (int i = 1; i <= d; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= d; i++) w[c[i]] = 1;
    for (int i = 1; i <= n; i++)
        if (!w[i]) {
            if (a[i] > m) continue;
            e[a[i]].push_back(b[i] + m);
            e[b[i]+m].push_back(a[i]);
        }
    memset(f, -1, sizeof(f));
    for (int i = d; i; i--) {
        for (int j = ans[i+1]; j <= m; j++) {
            memset(v, 0, sizeof(v));
            if (!dfs(j)) {
                ans[i] = j;
                break;
            }
        }
        if (a[c[i]] > m) continue;
        e[a[c[i]]].push_back(b[c[i]] + m);
        e[b[c[i]]+m].push_back(a[c[i]]);
    }
    for (int i = 1; i <= d; i++) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：wjyyy (赞：5)

## 前言

我发现我有道叫[[SCOI2010]连续攻击游戏](https://www.luogu.org/problemnew/show/P1640)的题白写了..事实上大家写完那道题就可能有这道题的思路了。

[**博客传送门**](http://www.wjyyy.top/3419.html)

## 题意

有 $n$ 个学生，$m$ 个社团。每个学生属于一个社团。在接下来的 $d$ 天里，每天会有一个人退团。每天从每个社团中最多选出一个人，使得选出的人的能力值集合 $\{p_i\}$ 的 $\mathrm{mex}$ 值最大。求出每天的最大 $\mathrm{mex}$ 值。

## 题解

可能建立二分图模型是求 $\mathrm{mex}$ 的一个套路/技巧吧。反正是忘了…但是做题的时候也不知道哪些是经典，干脆以后全部好好落实。

因为每个能力值**至少**被一个社团提供，而一个社团**最多**提供一个能力值，由此构造二分图。左侧是能力值，右侧是社团。当存在一个学生能力值为 $p_i$，社团为 $c_i$ 时，从 $p_i$ 向 $c_i$ 连边。

但是学生是在动态变化的，而且只会减少人，由此每次询问的答案一定非严格递减。

但是二分图最大匹配的匈牙利算法是不支持删边的，而一次匹配（指左边的一个点）的复杂度就是 $O(m)$，每次进行复杂度高达 $O(nmd)$，显然不是我们想要的。

考虑反过来，从最终状态加学生，每次的答案一定不会减少。那么我们就假设加完前 $i$ 个学生后，此时的 $\mathrm{mex}$ 是 $t$。在二分图左侧 `Find(t)`，此时如果替换，只会替换比 $t$ 小的点，不会造成更劣答案；最终会找到一个没有匹配过的社团，令答案 $+1$。

重新加边不会影响原来算好的答案。最终反序输出即可。

时间复杂度 $O(nm+qm)$。

## Code：

写匈牙利一定要在每次 `Find()` 函数外调用 `Find()` 时清空 `used[]` 啊啊啊啊啊啊~~否则会 FST~~

```cpp
#include<cstdio>
#include<cstring>
struct edge
{
    int n,nxt;
    edge(int n,int nxt)
    {
        this->n=n;
        this->nxt=nxt;
    }
    edge(){}
}e[5050];
int head[5050],ecnt=-1;
void add(int from,int to)
{
    e[++ecnt]=edge(to,head[from]);
    head[from]=ecnt;
}
int s[5050];
bool used[5050];
bool Find(int x)
{
    if(used[x])
        return false;
    used[x]=1;
    for(int i=head[x];~i;i=e[i].nxt)
        if(s[e[i].n]==-1||Find(s[e[i].n]))
        {
            s[e[i].n]=x;
            return true;
        }
    return false;
}
int a[5050],b[5050],c[5050];
int ans[5050];
int main()
{
    memset(head,-1,sizeof(head));
    memset(s,-1,sizeof(s));
    int n,m,q;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;++i)
        scanf("%d",&b[i]);
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        scanf("%d",&c[i]);
        used[c[i]]=1;
    }
    for(int i=1;i<=n;++i)
        if(!used[i])
            add(a[i],b[i]);
    int t=0;
    for(int i=q;i>=1;--i)
    {
        memset(used,0,sizeof(used));
        while(Find(t))
        {
            ++t;
            memset(used,0,sizeof(used));
        }
        ans[i]=t;
        add(a[c[i]],b[c[i]]);
    }
    for(int i=1;i<=q;++i)
        printf("%d\n",ans[i]);
    return 0;
}
```



---

## 作者：xh39 (赞：4)

第3道黑题纪念。

前置算法:二分图最大匹配。(如果你实在不想学,请跳过这篇题解。)。

---

首先,贪心,我们应该从 $0$ 开始,能选就选。(如果不选那么 $mex$ 就是这个值了,所以选更好。)

题目中有一句话很关键,提示了算法(重点部分已加粗)

>select **one** student from **each** club.

意思是每个 $club$ 里只能选 $1$ 个学生。

于是我们想到了图的匹配(首先确定了社团为一部分节点)。

但是我们要想成为一个图,我们还需要一部分节点。

~~谔分图~~二分图匹配比较简单,所以我们尽量往二分图匹配去想。

把学生作为节点?显然不妥,题目要求的是 $mex$,把学生作为节点不好求 $mex$(无法根据匹配答案求得 $mex$)。

我们要另辟蹊径,选择能力值作为另外一部分节点。这样我们就可以枚举所有能力值看能否匹配到不同的 $club$。

不好删边,于是我们就从第 $d$ 天开始,不断加边。(如果你实在想删边或者题目要求强制在线,用邻接矩阵存图也可以。)

注:如果直接枚举,会显示[$\color{#00a}\text{Time limit exceeded on test 10}$](https://codeforces.com/contest/1139/submission/72737994)。

优化:由于答案具有单调性(**从后往前**单调递增(非严格)),所以我们不用每次都从1开始枚举,从**上一次的答案**开始枚举即可。

单调理由:加入一个 student 结果肯定不会更差,因为我们可以选原来的集合或选这个 student,结果如果更差就可以选原来的集合,保证了结果不会更差。

感觉大家听不懂,就拿样例来讲一下吧。

样例1:
```cpp
5 3
0 1 2 2 0
1 2 2 3 2
5
3
2
4
5
1
```
![](https://cdn.luogu.com.cn/upload/image_hosting/hl55otaj.png)

建议自己画图理解。

细节部分都在代码↓里了。
```cpp
#include<iostream>
using namespace std;
int a[1000005],b[1000005],zyl[1000005],ans[1000005]; //a能力b组zyl离开。 
struct xyq{ //静态邻接表(链式前向星)。
	int v,next;
}_[1000005];
int head[1000005],tot=1;
void add(int u,int v){ //加边。
	_[tot].v=v;
	_[tot].next=head[u];
	head[u]=tot;
	++tot;
}
int kkksc03[1000005]; //匹配。
bool mark[1000005]; //标记数组。防止重复走过一个点而死循环。
bool dfs(int iakioi){ //二分图最大匹配。
	int i;
	for(i=head[iakioi];i;i=_[i].next){
		if(!mark[_[i].v]){
			mark[_[i].v]=1;
			if(kkksc03[_[i].v]<0||dfs(kkksc03[_[i].v])){ //注:是<0,因为0是表示为匹配到0号节点。
				kkksc03[_[i].v]=iakioi;
				return true;
			}
		}
	}
	return false;
}
int n,m;
int Main(int l){ //主函数副本。处理每一个询问。
//	for(i=0;i<=5555;++i){ 注:我特意把这一段放上来并打上注释符号。因为我们是从上一次开始枚举的,这里不可以清空。
//		kkksc03[i]=-1;
//	}
	int i,j;
	for(i=l;i<=5001;++i){
		for(j=0;j<=m;++j){ //一定记得清空标记。
			mark[j]=0;
		}
		if(!dfs(i)){ //如果匹配不上了,说明这个能力值不可能达到。
			return i;
		}
	}
}
bool hyy[1000005]; //hyy标记student有没有离开过。
int main(){
	int d,i,ykb;
	for(i=0;i<=5555;++i){ //在之前清空。
		kkksc03[i]=-1; //为什么是-1?因为我们的节点可能是0号。所以只能清空为-1。
	}
	cin>>n>>m;
	for(i=0;i<n;++i){
		cin>>a[i];
	}
	for(i=0;i<n;++i){
		cin>>b[i];
	}
	cin>>d;
	for(i=0;i<d;++i){
		cin>>zyl[i];
		hyy[zyl[i]]=1; //离开过,标记。
	}
	for(i=1;i<=n;++i){
		if(!hyy[i]){ //如果这个student根本没离开过,所以就加入。
			add(a[i-1],b[i-1]);
		}
	}
	ans[d]=Main(0); //为什么要在循环外单独赋值?因为我们枚举范围需要用到上一个答案。
	for(i=d-1;i>=0;--i){ //倒序枚举
		add(a[zyl[i]-1],b[zyl[i]-1]); //加入student。
		ans[i]=Main(ans[i+1]);
	}
	for(i=1;i<=d;++i){ //输出存好了的答案。
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：Pengzt (赞：3)

[CF1139E](https://www.luogu.com.cn/problem/CF1139E)

翻译中有一句话：校长将会从每个社团中**各**选出一个人。

就是一些人被分为一组，从每组中选一些人出来。

这就很容易想到通过二分图的匹配。

$\operatorname{mex}$ 运算有一个显而易见的贪心：枚举每个值能否被匹配，第一个找不到的值就是答案。

由于 $\operatorname{mex}$ 运算的值域与 $n$ 同级，就可以从这方面入手。

我们从每个能力值 $p_i$ 向社团 $c_i$ 建边。

假如枚举的值为 $i$，与增广路算法相似，如果 $i$ 能再找到匹配，那么 $\operatorname{mex}$ 的值一定会大于 $i$，否则就找到了 $\operatorname{mex}$ 运算的答案。

但如果是这样的话，外层需要枚举到 $d$，内层要枚举到最大值 $V$，再加上匈牙利算法的单次的时间复杂度 ${\mathrm{O}}(m)$，就会使总时间复杂度高达 ${\mathrm{O}}(dmV)$，当然会 TLE。

考虑优化。

突然感觉与[这道题](https://www.luogu.com.cn/problem/P1640)很像，都是枚举值域，然后匹配。

于是就想到了一个玄学优化：用时间戳来优化常数。

在 CF 上交了一次，应该是数据太水，还过了。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e3, inf = 1e9 + 7;
int n, m, now, D, T;
int c[N + 5], p[N + 5], d[N + 5];
int mat[N + 5], vis[N + 5];
int cnt, head[N + 5];
struct Edge {
	int v, ti, nxt;
} e[N + 5];
int read() {
	int ret = 0, sgn = 0;
	char ch = getchar();
	while (!isdigit(ch)) sgn |= ch == '-', ch = getchar();
	while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
	return sgn? -ret: ret;
}
void add(int u, int v, int ti) {
	e[++cnt].nxt = head[u];
	e[cnt].v = v;
	e[cnt].ti = ti;
	head[u] = cnt;
}
bool dfs(int x) {
	for (int i = head[x]; i; i = e[i].nxt)
		if (e[i].ti > T && vis[e[i].v] != now) {
			vis[e[i].v] = now;
			if (mat[e[i].v] == -1 || dfs(mat[e[i].v])) { mat[e[i].v] = x; return 1; }
		}
	return 0;
}
int main() {
	n = read(), m = read();
	int W = 0;
	for (int i = 1; i <= n; i++) p[i] = read(), W = max(W, p[i]);
	for (int i = 1; i <= n; i++) c[i] = read();
	D = read();
	for (int i = 0; i <= n; i++) d[i] = inf; // 初始化到 n。
	for (int i = 1; i <= D; i++) d[read()] = i;
	for (int i = 1; i <= n; i++) add(p[i], c[i], d[i]);
	for (int i = 1; i <= D; i++) {
		T = i;
		for (int j = 0; j <= m; j++) vis[j] = mat[j] = -1; // mat[j] 的值可能为 0 (p[i] == 0)
		bool flag = 0;
		for (int j = 0; j <= W; j++) {
			now = j;
			if (!dfs(j)) {
				printf("%d\n", j);
				flag = 1;
				break;
			}
		}
		if (!flag) printf("%d\n", W + 1);
	}
	return 0;
}
```


这样卡一下应该还是不能过，时间复杂度还是没有变。

发现答案肯定是**单调不增**的，于是倒序枚举，就用一个 $ans$ 数组记录一下答案，输出即可。

时间复杂度 ${\mathrm{O}}(md)$

[评测记录](https://www.luogu.com.cn/record/101937678)

---

## 作者：bloodstalk (赞：2)

## Description
$n$ 个学生， $m$ 个社团。每个学生有一个能力值，且仅属于一个社团。这 $d$ 天内，每天从 $m$ 个社团中选人，使得选出的人的能力值的 $\text{mex}$ 最大。每天会有一个人在选人之前退团。

$d,m \leq n \leq 5000$
## Solution
巧妙建图题。

* 首先，我们可以很显然的知道要想使得 $\text{mex}$ 值最大，我们应该贪心地先选能力值小的人，直到有一个能力值不能被表示。

* 再次，我们考虑一个社团只能选一个人进行匹配、一个人和一个能力值相对应。于是我们可以将这个题抽象成一个二分图的问题：将能力值当成左部点，团体当成右部点。将一个社团里每个人的能力值和这个社团连边，跑最大图匹配即可。

* 到了这一步，我们发现这么做的复杂度是 $O(nmd)$ 的，不足以解决此题，需要进一步优化。我们发现，多一个人的情况肯定不比少一个人的情况差，因此我们可以想出从最后一天倒序考虑，从人员退出转化成人员加入，这样以后枚举能力值的时候就不需要每次从 $0$ 开始枚举了。时间复杂度降为 $O(dm)$ ，可以通过。

需要注意的一些坑点：

（1）：因为 $0$ 也可能是答案，所以 $match$ 数组每次要初始化成 $-1$ 而非 $0$ ；

（2）：题目给出的是学生先离开社团校长再选人，所以倒过来的话就是先选人再把学生加入进去。

## Code
```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 5e4 + 5;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int match[N],vis[N],k[N],use[N];
int n,m,d,ans;
stack <int> st;
struct Node{
	int p,c;
}a[N];
struct node{
	int u,v,next;
}edge[N<<1]; int head[N],num_edge;


il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il void add(int from,int to)
{
	edge[++num_edge] = (node){from,to,head[from]};
	head[from] = num_edge;
}

il bool dfs(int x)
{
	for(re int i=head[x];i;i=edge[i].next)
	{
		int y = edge[i].v;
		if(vis[y]) continue;
		vis[y] = 1;
		if(match[y] == -1 || dfs(match[y]))
		{
			match[y] = x;
			return true;
		}
	}
	return false;
}

il void Main(int id)
{
	memset(vis , 0 , sizeof vis);
	while(dfs(ans)) { ans++; memset(vis , 0 , sizeof vis);}
	st.push(ans);
	add(a[k[id]].p,a[k[id]].c);
}

signed main()
{
	memset(match , -1 , sizeof match);
	n = read() , m = read();
	for(re int i=1;i<=n;i++) a[i].p = read();
	for(re int i=1;i<=n;i++) a[i].c = read();
	d = read();
	for(re int i=1;i<=d;i++) k[i] = read() , use[k[i]] = 1;
	for(re int i=1;i<=n;i++) if(!use[i]) add(a[i].p,a[i].c);
	for(re int i=d;i>=1;i--) Main(i);
	while(!st.empty()) cout << st.top() << "\n" , st.pop();
	return 0;
}
```

此外，由于此题数据过水，直接正着来，经过一些常数优化也能过。[代码在这](https://www.luogu.com.cn/paste/zc70gl5c)，仅供参考。

---

## 作者：xixiup (赞：2)

## 思路分享

我们考虑，一个社团仅能派出一名学生，为了让题目更加好做，我们可以考虑再加入一个限制条件，我们限制每个能力值仅能派出一名学生。

那么为什么要加入这一个限制条件呢？

首先对正确性考虑，一个能力值派出更多的学生其实是对答案没有影响的，所以在正确性方面没有问题。

那么再考虑为什么要加上这个限制。思考，一个社团仅能派出一名学生，每个能力值顶多有一名学生，一名学生有一个能力值，属于一个社团。

你想到了什么？二分图的最大匹配！

我们将每个学生 $i$ 看作一条从左半边图的 $p_i$ 连向右半边图的 $c_i$ 的边，然后我们就可以对于每一个权值，我们可以对其进行匹配，若匹配成功，则进入下一个权值，若不成功，则这个权值就是这个状态的答案。

问题来了，这样需要跑 $d$ 次匈牙利，会超时。

所以我们怎么办呢？

我们可以考虑倒许处理，因为这样就可以只有增加操作而没有删除操作，所以我们就可以直接从上次的匹配开始继续匹配。

这样就可以了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=50100,maxm=maxn;
int n,m,d,vis[maxn],pd[maxn],ans[maxn];
int cnt,bg[maxn],ne[maxm],to[maxm];
int p[maxn],c[maxn],k[maxn];
void add(int x,int y){
	cnt++;
	ne[cnt]=bg[x];
	to[cnt]=y;
	bg[x]=cnt;
}
bool dfs(int x){
	for(int i=bg[x];i;i=ne[i]){
		int y=to[i];
		if(vis[y]==0){
			vis[y]=1;
			if(pd[y]==-1||dfs(pd[y])){
				pd[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
	}
	cin>>d;
	for(int i=1;i<=d;i++){
		scanf("%d",&k[i]);
		vis[k[i]]=1;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			add(p[i],c[i]);
		}
	}
	memset(pd,-1,sizeof(pd));
	int sum=0;
	for(int i=d;i>=1;i--){
		memset(vis,0,sizeof(vis));
		while(dfs(sum)==1){
			sum++;
			memset(vis,0,sizeof(vis));
		}
		ans[i]=sum;
		add(p[k[i]],c[k[i]]);
	}
	for(int i=1;i<=d;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}

```


---

## 作者：syzf2222 (赞：2)

孤立地去看每一个询问，发现问题可以这样转化：

有一些集合，取出一个数则集合占用，求最多可以取多少个从0开始的连续自然数。

先手玩一组数据：

$\{0,1,2\},\{1,2,3\},\{1,3\}$

考虑0：占用$\{0,1,2\}$

考虑1：占用$\{1,2,3\}$

考虑2：发现有2的$\{1,2,3\}$已经被占用，且占用此集合的1也可以选择$\{1,3\}$，则2抢过$\{1,2,3\}$，把$\{1,3\}$给1

考虑3：无法匹配

发现此过程类似于二分图匹配。

将$\{0,1,2,3...\}$去匹配每一个集合，集合中包含此数则连边。

那么这样得到一个$\Theta(dnm)$的优秀算法，$TLE$在第十个点。

考虑优化。

因为一个人走之后就不会再回来，考虑倒序处理。

加入一个人之后，易知答案只增不减，故复杂度降低为$\Theta(dm)$。

代码仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+10;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,d,p[maxn],c[maxn],ans[maxn];
int beg[maxn],nex[maxn],to[maxn],e;
inline void add(int x,int y){
	e++;nex[e]=beg[x];
	beg[x]=e;to[e]=y;
}
int mat[maxn],vis[maxn],pro[maxn],out[maxn];
inline int dfs(int x){
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(vis[c[t]]||out[t])continue;
		vis[c[t]]=1;
		if(mat[c[t]]==-1||dfs(mat[c[t]])){
			mat[c[t]]=x;
			return 1;
		}
	}
	return 0;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		p[i]=read();
		add(p[i],i);
	}
	for(int i=1;i<=n;i++)
		c[i]=read();
	d=read();
	for(int i=1;i<=d;i++){
		pro[i]=read();
		out[pro[i]]=1;
	}
	memset(mat,-1,sizeof(mat));
	for(int i=d;i>=1;i--){
		for(int j=ans[i+1];;j++){
			memset(vis,0,sizeof(vis));
			if(!dfs(j)){ans[i]=j;break;}
		}
		out[pro[i]]=0;
	}
	for(int i=1;i<=d;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：XRRRRcode (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1139E)

提个建议，希望本题评蓝，这不是紫题的水平。

# 题解
总体思路：首先把题目看成一个二分图，其中一侧是社团，另一侧是能力值，再将每一个学生看作二分图的无向边（连接社团和能力值）。

因为题目的前半部分容易误导大家，导致按顺序删除边难以维护二分图，所以我们直接把退出社团看作加入（显然不会改变答案，这边就不证明了），相当于把 $n$ 条边加入到二分图中，虽然逆序处理仍然很复杂但至少没有删除边那么麻烦。

维护好二分图后，剩下就简单多了（好像也不是很简单）。第$i$次询问时，使用[匈牙利算法](https://baike.baidu.com/item/匈牙利算法/9089246)深搜一下图的右侧，直到搜到未匹配的节点就是答案。

最后总结一下，先构造二分图，每次询问后搜索答案，再加入新的无向边即可。时间复杂度 $O(n^2)$，$2s$ 时间限制过得稳如泰山。

# 代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define MAXN 5005
using namespace std;
int ans[MAXN],a[MAXN],b[MAXN],M[MAXN],p[MAXN],n,m,z,f;
bool k[MAXN];
vector<int> y[MAXN];
//构造二分图
bool XYL(int c)
{
    k[c]=true;
    for(auto &x:y[c])
        if(M[x]==-1||k[M[x]]&&XYL(M[x]))
        {
            M[x]=c;
            return true;
        }
    return false;
}//匈牙利算法
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
        M[i]=-1;
    for(i=0;i<n;i++)
        scanf("%d",&p[i]);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        a[i]--;
    }
    scanf("%d",&z);
    for(i=0;i<z;i++)
    {
        scanf("%d",&b[i]);
        b[i]--;
        k[b[i]]=true;
    }
    for(i=0;i<n;i++)
    {
        if(!k[i])
            y[p[i]].push_back(a[i]);
    }
    //预处理
    while(true)
    {
        memset(k,false,sizeof(k));
        if(XYL(f)==true)
            f++;
        else break;
    }
    //第一次处理
    ans[z]=f;
    for(i=z;i--;)
    {
        j=b[i];
        y[p[j]].push_back(a[j]);
        while(true)
        {
            memset(k,false,sizeof(k));
            if(XYL(f)==true)
                f++;
            else break;
        }
        ans[i]=f;
    }
    //同理，逆序处理
    for(i=1;i<=z;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```
**拒绝抄袭，人人有责。**

蒟蒻第一次写题解，管理大大就给过叭，求求～

---

## 作者：Daniel_7216 (赞：1)

一步步拆解，先考虑当确定了多少人还在（即第几天）的时候，怎么判断是否存在一种选人方案，使得能力值集合 $S$ 中存在数字 $x$。

看一下限制和条件：

- 每个人都恰好属于一个社团。

- 每个社团选一个人。

- 一个显然的结论是，最优选择下，一种能力值最好只与一个人对应，且越多的人参赛就有越大的概率得到最大的 $mex$ 值。

- 如果没有思路的话，请回到第一条。

思路渐渐出来了。

组队的学生中出现了一个新的能力值不会对其它已存在能力值产生影响，一个社团派出了一个人不会对其它社团选人策略产生影响。这是 $0$ 要素。每个社团只能选一个人，社团里其它人不能选，这是 $1$ 要素。

故，此题本质上是一个二分图最大匹配。

把 $p_i$ 看做左部点，$c_i$ 看做右部点，对于 $i \in[1,n]$ 给 $p_i$ 和 $c_i$ 连一条边。根据刚才的分析，只需要从 $0$ 开始枚举每一个能力值并尝试匹配，第一个失配的能力值就是 $mex$ 值。

删掉一个人，就要删边，借鉴星球大战那道题的思路，从最后一天开始考虑，变成每一天新加入一个人，同时容易发现一个人的加入不会使答案变得更差，所以枚举能力值的时候不需要每一天都从 $0$ 开始枚举。

其余细节看代码。

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 5001;
int n, m, d, L;
int p[maxn], c[maxn], k[maxn], match[maxn], ans[maxn];
bool used[maxn], vis[maxn];
vector <int> G[maxn];
bool dfs(int u){
	for (int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		if (!vis[v]){
			vis[v] = true;
			if (match[v] == -1 || dfs(match[v])){
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d", &p[i]);
	}
	for (int i = 1; i <= n; i++){
		scanf("%d", &c[i]);
	}
	scanf("%d", &d);
	for (int i = 1; i <= d; i++){
		scanf("%d", &k[i]);
		used[k[i]] = true;
	}
	for (int i = 1; i <= n; i++){
		if (!used[i]){
			G[p[i]].push_back(c[i]);
		}
	}
    memset(match, -1, sizeof(match));
	for (int i = d; i >= 1; i--){
		while (true){
			memset(vis, 0, sizeof(vis));
			if (dfs(L))L++;
			else break;
		}
		ans[i] = L;
		G[p[k[i]]].push_back(c[k[i]]);
	}
	for (int i = 1; i <= d; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：whiteqwq (赞：1)

[CF1139E Maximize Mex](https://www.luogu.com.cn/problem/CF1139E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1750106)

## 题意

- $n$名学生，$m$个社团，每个学生$i$属于社团$c_i$，能力值为$p_i$；
- 学校有一个为期为$d$天的活动，第$i$天，学生$k_i$会推出社团；
- 定义一个队伍的能力值为所有学生的能力值的$mex$，即所有学生能力值组成的集合中没有出现的最小非负整数；
- 每一天学校都要从各社团选出一个人组成队伍使队伍的能力值最大，求每一天的能力值。
- 数据范围：$1\leqslant n,m\leqslant 5\cdot 10^3,0\leqslant p_i\leqslant 5\cdot 10^3$。

## 分析

考虑将每个社团抽象为一个点，每个能力值抽象为一个点，社团与所有它成员的能力值连边，那么我们可以用匈牙利算法来解决这个$mex$：每一次多取一个能力值，如果可以那么$mex$加一，否则当前$mex$就是最终答案。

可以不断删边（标记每一条边删掉就好了），然后用匈牙利做到$O((maxp\cdot n+m)\cdot d)$，但是仍然无法通过。

考虑将删边转化为加边（时间倒流），然后不难发现$mex$是递增的。

因为$mex$是递增的，所以每一次匈牙利都可以从上一次结束的位置开始，这样我们的复杂度就优化成了$O(maxp\cdot d+maxp\cdot n)$。

## 代码
```
#include<stdio.h>
#include<string.h>
const int maxn=5005,maxm=5005,maxd=5005;
int n,m,d,e,stp,ans;
int start[maxn],to[maxm],then[maxm],c[maxn],p[maxn],k[maxd],vis[maxn],match[maxn],flg[maxn],res[maxd];
inline void add(int x,int y){
	then[++e]=start[x],start[x]=e,to[e]=y;
}
int dfs(int x){
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(vis[y]==stp)
			continue;
		vis[y]=stp;
		if(match[y]==-1||dfs(match[y])){
			match[y]=x;
			return 1;
		}
	}
	return 0;
}
int main(){
	memset(match,-1,sizeof(match));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	scanf("%d",&d);
	for(int i=1;i<=d;i++){
		scanf("%d",&k[i]);
		flg[k[i]]=1;
	}
	for(int i=1;i<=n;i++)
		if(flg[i]==0)
			add(p[i],c[i]);
	for(int i=d;i>=1;i--){
		for(int j=ans;;j++){
			stp++;
			if(dfs(j)==0){
				ans=j;
				break;
			}
		}
		res[i]=ans;
		add(p[k[i]],c[k[i]]);
	} 
	for(int i=1;i<=d;i++)
		printf("%d\n",res[i]);
 	return 0;
}
```

---

## 作者：WeiFanbo (赞：0)

[题目：CF1139E](https://www.luogu.com.cn/problem/CF1139E)

值得一做的二分图好题

##  题意

给定 $n$ 个学生和 $m$ 个社团，每个学生有一个能力值，并且每个学生只属于一个社团，从每个社团中选出一名学生，他们的能力值集合为 $S$。一共有 $d$ 天，每天都会有一个学生退出社团，对于每一天，求出最大的 $mex(S)$。

##  数据范围

$1≤m≤n≤5000$ 

$0≤p_i<5000$

$1≤c_i≤m$

$1≤d≤n$

##  思路

观察到**每个学生只属于一个社团**，而题目求的集合S又是能力值 $p_i$ 的集合，那么我们考虑以能力值和社团为两个点集建二分图跑最大匹配。每一个学生相当于一条边，连接了一个能力值与一个社团。每一个退出社团的学生相当于一次删边操作。

我们发现删边操作比较难搞，那么这里就要用到一个比较经典的做法：**倒着处理删边操作**，这样一来删边就变成了加边，退出的学生相当于后来加入的学生。

具体做法就是从 $0$ 开始枚举，第一个无法匹配的节点就是我们当天的答案。

##  优化 

在这样的数据范围的限制下，如果我们对于每次加边操作都跑一次匈牙利算法，时间复杂度是不对的，下面我们考虑优化：

**显然，在一次加边操作之后能匹配的节点依然能够匹配，所以答案是单调递增的**，那么每次加边之后我们在原来的基础上找增广路，再加上前一次的答案就好。

##  code

```cpp
#include<bits/stdc++.h>
#define N 5010
using namespace std;
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int n,m,d;
int u[N],v[N]; 
//链式前向星存图 
struct node{
	int nxt;
	int to;
}edge[N];
int head[N],tot=0;
void add(int x,int y)
{
	edge[++tot].nxt=head[x];
	edge[tot].to=y;
	head[x]=tot;
}
int c[N],vis[N];
int ans[N],match[N];
bool dfs(int x)
{
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].to;
		if(!vis[y]){
			vis[y]=1;
			if(match[y]<0||dfs(match[y])){
				match[y]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		u[i]=read();
	for(int i=1;i<=n;i++)
		v[i]=read();
	d=read();
	for(int i=1;i<=d;i++){
		c[i]=read();
		vis[c[i]]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
			add(u[i],v[i]);
	int j=0;
	memset(match,-1,sizeof(match));//这里有一个细节，因为 0 也是一个节点，所以match数组应初始化为一个负数 
	for(int i=d;i>=1;i--){
		for(;j<=5000;j++){
			memset(vis,0,sizeof(vis));
			if(dfs(j))
				ans[i]++;
			else
				break;
		}
		add(u[c[i]],v[c[i]]);//加边 
		ans[i]+=ans[i+1];
	}
	for(int i=1;i<=d;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```


---

## 作者：Karry5307 (赞：0)

### 题意

有 $n$ 个学生和 $m$ 个社团，第 $i$ 个学生的能力值为 $p_i$，属于社团 $c_i$。

现在有 $d$ 个操作，每一个操作形如第 $i$ 个学生离开 $c_i$ 社团，在每一次操作之后需要求从每个社团中选一个人（社团没人就不选）组成集合的 $\text{mex}$ 的最大值。

$\texttt{Data Range:}d,m\leq n\leq 5000$

### 题解

看到这种题发现删除操作实际上是不好做的，并且倒着考虑答案具有单调性，于是时间倒流变成加入操作。

于是只需要考虑每一次加入一个值然后求最大的 $\text{mex}$，有一个很妙的 trick 是建二分图求最大匹配。

将每个能力值看成左部点，每个社团看成右部点，对于一个人 $(p_i,c_i)$ 来说，从 $p_i$ 向 $c_i$ 连边，由于一个社团最多只能与一个能力值匹配，就可以保证正确性。

接下来考虑增广。每一次从能力值为 $0$ 的点开始找增广路，如果找不到就直接返回这个就好了。

由于时间倒流之后答案具有单调性，而且因为是加边操作，原来的匹配不会更改，所以并不用从 $0$ 开始从上一次的答案开始就行了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e4+51;
struct Edge{
	ll to,prev;
};
Edge ed[MAXN<<1];
ll n,m,d,tot;
ll last[MAXN],p[MAXN],c[MAXN],x[MAXN],vis[MAXN],visr[MAXN];
ll match[MAXN],res[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
inline ll dfs(ll x)
{
	for(register int i=last[x];i;i=ed[i].prev)
	{
		if(!visr[ed[i].to])
		{
			visr[ed[i].to]=1;
			if(match[ed[i].to]==-1||dfs(match[ed[i].to]))
			{
				return match[ed[i].to]=x,1;
			}
		}
	}
	return 0;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		p[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		c[i]=read();
	}
	d=read(),memset(match,-1,sizeof(match));
	for(register int i=1;i<=d;i++)
	{
		vis[x[i]=read()]=1;
	}
	for(register int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			addEdge(p[i],5000+c[i]),addEdge(5000+c[i],p[i]);
		}
	}
	for(register int i=d;i;i--)
	{
		for(register int j=res[i+1];j<=m;j++)
		{
			memset(visr,0,sizeof(visr));
			if(!dfs(j))
			{
				res[i]=j;
				break;
			}
		}
		addEdge(p[x[i]],5000+c[x[i]]),addEdge(5000+c[x[i]],p[x[i]]);
	}
	for(register int i=1;i<=d;i++)
	{
		printf("%d\n",res[i]);
	}
}
```

---

