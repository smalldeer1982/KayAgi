# [GCJ 2022 #2] Saving the Jelly

## 题目描述

Jolly 先生正在教编号为 1 到 $\mathbf{N}$ 的 $\mathbf{N}$ 个孩子踢足球（或称 soccer，针对美国读者）。他习惯在比赛场地上放置糖果，每个孩子一颗。比赛结束后，每个孩子可以拿走并吃掉一颗作为奖励。

孩子们在比赛后很累，所以每个孩子都想拿离自己最近的糖果（使用欧几里得距离计算）。这可能导致冲突——如果同一颗糖果是多个孩子最近的。为避免这种情况，比赛结束后所有孩子停在原地，Jolly 先生会依次点名。当被点到名时，孩子会拿走离自己最近的糖果（当然，只能选未被拿走的糖果）。当有多颗糖果距离最近且相同时，Jolly 先生可以决定孩子拿哪一颗。

![](https://cdn.luogu.com.cn/upload/image_hosting/h3px6piy.png)

这个方法一直很有效，但今天出问题了！Jolly 先生在布置糖果时，不小心把他准备在孩子们回家后享用的蓝莓果冻也放在了场地上。现在场上有 $\mathbf{N}$ 个孩子和 $\mathbf{N}+1$ 颗糖果。糖果编号为 1 到 $\mathbf{N}+1$，其中 1 号是 Jolly 先生的蓝莓果冻。是否存在一种点名顺序，使得最后剩下的糖果正好是蓝莓果冻？

## 说明/提示

**样例解释**

样例 #1 如上图所示。每个孩子到两颗非果冻糖果的距离相等。解决方案中，Jolly 先生让 2 号孩子拿 2 号糖果，1 号孩子拿 3 号糖果，成功保留 1 号糖果（蓝莓果冻）。

样例 #2 中，唯一的孩子离蓝莓果冻比其他糖果更近，Jolly 先生无法保住果冻。

样例 #3 展示了一种可能的解，实际上可以任意顺序点名。

样例 #4 中注意孩子可能位置重合、糖果可能位置重合、孩子和糖果也可能位置重合。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$
- 所有坐标的绝对值不超过 $10^{9}$

**测试集 1（10 分，可见判定）**

- 时间限制：10 秒
- $1 \leq \mathbf{N} \leq 10$

**测试集 2（18 分，隐藏判定）**

- 时间限制：45 秒
- $1 \leq \mathbf{N} \leq 1000$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2
-3 0
-1 0
3 0
-2 -1
-2 1
1
0 0
1 1
2 2
3
10 0
-10 0
0 0
0 5
-1 0
5 0
0 -5
2
3 4
3 4
5 7
3 4
5 7```

### 输出

```
Case #1: POSSIBLE
2 2
1 3
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
3 2
2 4
1 3
Case #4: POSSIBLE
1 2
2 3```

# 题解

## 作者：zzy0618 (赞：1)

## 大体思路

先不考虑最近的要求，确定可行性。设 $dis(x,y)$ 为小孩 $x$ 与 糖果 $y$ 的距离（蓝色果冻为 $1$ 号），如果 $dis(x,y)\le dis(x,1)$，那么 $x$ 向 $y$ 连一条边。然后有一张二分图，通过匈牙利算法可以判断是否每个小孩都能拿到糖，这样可以判断可行性，但是不能求出每次都能取最近糖果的方案。

关于最近的话，笔者自己在匈牙利时，按照从近到远的顺序匹配，然后就过了？

大概想一下证明。我们一直按照最小的来，如果两小孩碰一起了就会形成一条增广路，而我们开始的小孩本来就是可以直接匹配删掉的，所以删掉后继续匹就可以了。

最终输出时只要是最短的就直接输出，否则扔到最后，等别人拿完了再看情况。

## Code

注意 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define eb emplace_back
using namespace std;
const int N=1005;
int n,X,ans;
int vis[N],match[N],mat[N];
vector<int> e[N];
struct node{int x,y;}a[N],b[N];
int dis(int i,int j){return (a[i].x-b[j].x)*(a[i].x-b[j].x)+(a[i].y-b[j].y)*(a[i].y-b[j].y);}
bool cmp(int x,int y){return dis(X,x)<dis(X,y);}
int dfs(int x){
	for(int y:e[x]){
		if(vis[y])continue;vis[y]=1;
		if(!match[y]||dfs(match[y]))
			return match[y]=x,1;
	}return 0;
}void solve(){
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i].x>>a[i].y;
    for(int i=1;i<=n+1;++i)
        cin>>b[i].x>>b[i].y;
    for(int i=1;i<=n;++i){
        int d=dis(i,1);X=i;
        for(int j=2;j<=n+1;++j)
            if(dis(i,j)<=d)
                e[i].eb(j);
        sort(e[i].begin(),e[i].end(),cmp);
    }
    for(int i=1;i<=n;++i)
		memset(vis,0,sizeof(vis)),ans+=dfs(i);
	cout<<(ans==n?"POSSIBLE":"IMPOSSIBLE")<<'\n';
    if(ans==n){
        queue<int> q;
        for(int i=1;i<=n;++i)
            reverse(e[i].begin(),e[i].end()),
            mat[match[i+1]]=i+1,q.push(i);
        memset(vis,0,sizeof(vis));
        while(q.size()){
            int x=q.front();q.pop();
            while(vis[e[x].back()])
                e[x].pop_back();
            if(dis(x,e[x].back())==dis(x,mat[x])){
                cout<<x<<' '<<mat[x]<<'\n',vis[mat[x]]=1;
            }else q.push(x);
        }
    }ans=0;
    for(int i=1;i<=n+1;++i)
        e[i].clear(),match[i]=mat[i]=0;
}signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    for(int i=1;i<=t;++i)
        cout<<"Case #"<<i<<": ",solve();
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

有点厉害的结论题。放一下官方题解做法。

去掉那个强制不被选的点（下文称「关键点」）后，我们相当于要按题意规则找出一个完美匹配。

下面我们称「孩子」为「一类点」，「糖果」为「二类点」。

首先显然，对于一个一类点 $x$，只可能会和比关键点更近的二类点匹配。我们考虑将可以匹配的两点进行连边。

显然的一个必要条件是，这个连边后形成的图 $G$ 应当存在一个完美匹配。

下面证明这个条件也是充要的。

假设我们已经有了一个匹配，并且存在 $G$ 中没有的边。

首先去掉一些一类点，这些点满足其匹配的是最近的二类点。

然后剩下的都是匹配的非最近二类点的一类点，其中可能含有 $G$ 不存在的边。

我们随便找一个一类点 $u$，按以下方式找出一个环：
1. 从 $u$ 走到与 $u$ 匹配的二类点 $v$；
2. 从 $v$ 走到距离其最近的一类点 $u'$；
3. 将 $u'$ 作为新的 $u$，回到第一步。

这样下去，我们会得到一个偶环。这个偶环的边是选择和未选择的边交替的。而这些未选择的边恰好都是最短的边，如果我们不去选择目前选择的边，而去选择这些未选择的边，那么，这些新的边就又都是在 $G$ 中出现的了，而且也仍然是合法的方案。

于是我们证明了无论如何只要存在答案就一定会有 $G$ 的完美匹配，也就是条件是充要的。

于是我们找出二分图的完美匹配即可。

时间复杂度 $O(n^2\sqrt n)$。

---

