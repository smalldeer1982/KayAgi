# [IOI 2017] The Big Prize

## 题目背景

这里是洛谷。如果有疑问，可以发帖求助。

如果你习惯于写函数式交互，以下内容可能对你有帮助：

```cpp
vector<int>ask(int i)
{
	printf("? %d\n",i);fflush(stdout);
	vector<int>ret(2);
	scanf("%d%d",&ret[0],&ret[1]);
	return ret;
}
int find_best(int n)
{
	//
}
main()
{
	int n;scanf("%d",&n);
	printf("! %d\n",find_best(n));
}
```

无论如何，你都不应引入额外的头文件。

## 题目描述

“大奖”是一个家喻户晓的 TV 游戏节目。这次你很幸运地进入到最后一轮。已知编号从 $0$ 到 $n-1$ 的 $n$ 个盒子从左到右排成一行，你就站在这排盒子的前面。每个盒子里面放有一个奖品，必须打开盒子才能看到是什么奖品。已知有 $v\leq5$ 种不同类型的奖品。这 $v$ 种类型按照奖品价值的降序从 $1$ 到 $v$ 排列。

类型 $1$ 的奖品是一块钻石，价值最高。所有盒子加起来刚好只有一块钻石。类型 $v$ 的奖品是一块棒棒糖，价值最低。为使得游戏更加激动人心，相对便宜的奖品数量远比价值昂贵的奖品数量要多。更具体一点，对于满足 $2\leq t \leq v$ 的所有 $t$，我们有： 如果类型 $t-1$ 的奖品有 $k$ 个，那么类型 $t$ 的奖品将严格多于 $k^2$ 个。

你的目标是赢得那块钻石。在游戏结束时，你必须打开一个盒子并收取盒子内的奖品。在选择要打开的盒子之前，你可以向节目主持人 Rambod 提一些问题。在每一个问题中，你选择就某个 $i$ 号盒子进行提问。Rambod 将给你一个包含两个整数的数组 $a$ 作为回答。这两个整数的意义如下：

- 在 $i$ 号盒子左面的盒子中，刚好有 $a[0]$ 个盒子中的奖品，价值比 $i$ 号盒子中的奖品价值要高。
- 在 $i$ 号盒子右面的盒子中，刚好有 $a[1]$ 个盒子中的奖品，价值比 $i$ 号盒子中的奖品价值要高。

例如，假设 $n=8$，在你的问题中，你选择就 $i=2$ 号盒子进行提问。Rambod 的回答是 $a=[1,2]$。这个回答的意义是：

- $0$ 号盒子和 $1$ 号盒子中恰好有一个盒子中的奖品比 $i$ 号盒子中的奖品更贵。
- 在 $3,4,\cdots,7$ 号盒子中恰好有 $2$ 个盒子中的奖品比 $2$ 号盒子中的奖品更贵。

你的任务就是通过问少量的问题找出包含钻石的盒子。

## 说明/提示

### 样例解释

```plain
8
3 2 3 1 3 3 2 3
```

![](https://cdn.luogu.com.cn/upload/pic/6728.png)

上图阐释了这个例子。图中上半部分给出了每个盒子中奖品的类型。图中的下半部分阐释了询问 `? 2`。

### 限制

- $3\leq n \leq200000$.
- 每个盒子中奖品的类型介于 $1$ 和 $v$ 之间（含）。
- 类型 $1$ 的奖品恰有一个。
- 对于所有 $2\leq t \leq v$，如果类型 $t-1$ 的奖品有 $k$ 个，那么类型 $t$ 的奖品将严格多于 $k^2$ 个。


### 子任务与评分

1.  （$20$ 分）恰好有 $1$ 个钻石和 $n-1$ 个棒棒糖 （所以，$v=2$）。你可以询问最多 $10000$ 次。
2.  （$80$ 分）没有附加限制。


在子任务 2 中你可以获得部分分。令 $q$ 是在这个子任务的所有测试数据上发起询问的最大次数，那么你在这个子任务上的得分将按照下表计算：

![](https://cdn.luogu.com.cn/upload/pic/6729.png)

## 样例 #1

### 输入

```
8

0 3

0 1

1 2

0 0

2 1

2 1

1 0

3 0```

### 输出

```

? 0

? 1

? 2

? 3

? 4

? 5

? 6

? 7

! 3```

# 题解

## 作者：phigy (赞：2)

设查询 $i$ 的结果是 $x_i,y_i$，那么我们可以通过 $x_i+y_i$ 的大小关系判断 $a_i$ 的大小关系。

同时对于一段 $a_i$ 相等的连续段 $x_i,y_i$ 都是一样的，也就是说我们可以二分出一个数后面第一个不同的数。

考虑 $a_i$ 最大值之外的数是少的，至多 $474$ 个。

所以直接二分出所有最大值之外的数（实际上写成分治会更好）就可以做到大约 $474\times 19=9006$，需要注意到的是我们可能需要先取 $475$ 次来知道 $a_i$ 最大值的 $x_i+y_i$。

考虑二分的常数太大了，我们强制每 $511$ 个一块，如此至多 $392$ 个块，然后每个块做二分，做到大约 $392+474\times 10=5132$。

按随机顺序取块就可以做到期望 $392+\dfrac{474}{2}\times 10=2762$。


```cpp
#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int,int> 

using namespace std;

const int REN=200000,MAXN=REN+5;
int B=293;
int n;
pii a[MAXN];
int mx;
pii ask(int i)
{
    if(a[i].first!=0||a[i].second!=0) {return a[i];}
    cout<<"? "<<i<<endl;
    cin>>a[i].first>>a[i].second;
    if(a[i].first==a[i].second&&a[i].second==0) {cout<<"! "<<i<<endl;exit(0);}
    return a[i];
}
void solve(int L,int R)
{
    ask(L);ask(R);
    if(R-L==1) {return ;}
    if(a[L]==a[R]) {return ;}
    int mid=(L+R)>>1;
    solve(L,mid);solve(mid,R);
}
signed main()
{
    int i,j,k;
    cin>>n;
    srand(114514);
    vector<int>tmp;
    for(i=0;i*B<n;i++)
    {
        int now=i*B,nxt=min(n-1,(i+1)*B);
        tmp.push_back(i);
        ask(now);ask(nxt);
        mx=max(mx,a[now].first+a[now].second);
        mx=max(mx,a[nxt].first+a[nxt].second);
    }
    random_shuffle(tmp.begin(),tmp.end());
    for(int i:tmp)
    {
        int now=i*B,nxt=min(n-1,(i+1)*B);
        if(a[now]!=a[nxt]) {solve(now,nxt);}
    }
    return 0;
}
```

---

## 作者：Aiopr_2378 (赞：1)

## 解题思路

部分内容译自英文题解 https://dmoj.ca/problem/ioi17p4。

### 子任务 1

在这个子任务中，我们可以通过简单的二分查找找到最贵重的物品。

### 子任务 2，算法一

显然可以根据询问返回的两个数之和区别当前位置的物品种类。因为第 $k$ 种类型的物品足够多，我们希望使用它当作定位器的角色，以此来查找出第 $1\sim k-1$ 种类型的物品。

首先，我们询问前 $474$ 个物品。根据题目性质，这些询问足以找到一个第 $k$ 种类型的物品。当我们找到它的时候，就可以通过它，使用二分查找，寻找到第 $1\sim k-1$ 种类的物品。这种方法需要不到 $9000$ 次查询。更具体地说，它需要 $O(\sqrt n \log n)$ 次查询。

### 子任务 2，算法二

如果我们查询物品 $i$ 和 $j$（$i < j$），并且它们都是第 $k$ 种类型的物品，我们可以找到在 $i$ 和 $j$ 之间的物品中第 $1\sim k-1$ 种类物品的数量：假设交互库告诉我们在物品 $i$ 左侧有 $x$ 个物品是 $k-1$ 种类型，还告诉我们在物品 $j$ 左侧有 $y$ 个物品时前 $k-1$ 种类型。那么，正好有 $y−x$ 个物品在 $i$ 和 $j$ 之间是前 $k-1$ 种类型的。

我们考虑整个物品序列作为一个段。通过查询物品 $i$，我们将段分成两个部分：$i$ 之前的物品和 $i$ 之后的物品（已经查询过的物品不在任何段中）。在进行二分查找时，我们可以跟踪每个段中的物品数量。如果我们之前的查询中有满足上述条件的两个物品 $i$ 和 $j$，位于一个段的左右两侧，我们可以忽略那个段并且不查询它。

找到第一个 $k$ 类型物品可以采用算法一的方法进行询问，而后分治地询问分治中心另一部分的第一个 $k$ 类型物品，即可得出两个分治子区间内各有多少 $1\sim k-1$ 类型物品。

### 子任务 2，算法三

虽然之前的解决方案可以在实现精细的情况下获得这项任务的全部分数，但我们还可以进一步优化它。想法是，对于物品 $i$ 和 $j$ 来说，它们种类一样就足以识别它们之间的前 $k-1$ 种类型的物品。此外，我们可以对每个物品由交互库的回答的值进行求和。如果物品 $i$ 和 $j$ 类型一样，则物品 $i$ 的回答问题值之和等于物品 $j$ 的回答问题值之和。因此，没有必要特别寻找第 $k$ 种类型的物品：我们进行正常的二分查找，并且如果我们找到这样的物品 $i$ 和 $j$，显示在该段中没有前 $k-1$ 种物品，我们就不再继续在该段中进行二分查找。进一步的改进是，如果 $y−x$ 等于在物品 $i$ 和 $j$ 之间识别的物品数量减去物品 $i$ 和 $j$ 中的物品数量，**我们可以忽略这对物品之间的任何段**。这种方法如果有效实现，最多需要 $4759$ 次查询，而且代码更好实现。

虽然没有严格的时间复杂度证明，但可以感性理解：由于第 $k$ 种类型的物品足够多，进行分治处理时有相当大部分分支是被剪枝掉的。而剩下的询问上界是仍然是 $O(\sqrt n \log n)$，但由于通过已知信息能剪枝掉更多的询问，三个算法的本质区别在于常数的优化。当然，如果实现不够精细，并不能获得满分，但仍然可能得到相对较高的分数。

## 参考代码

```cpp
#include<vector>
#include<iostream>
#include<set>
using namespace std;
#define MAXN 200005
vector<int> a[MAXN];
bool vis[MAXN];
set<int> s;
int ans,val[MAXN];
vector<int> ask(int i){
	printf("? %d\n",i);fflush(stdout);
	vector<int>ret(2);
	scanf("%d%d",&ret[0],&ret[1]);
	return ret;
}
void qry(int x){
    if(vis[x]) return;
    vis[x]=1;
    a[x]=ask(x);
}
void get(int x){
    qry(x);
    val[x]=a[x][0]+a[x][1];
    s.insert(x);
    if(!val[x]) ans=x;
}
void solve(int l,int r){
    get(l),get(r);
    if(r-l==1) return;
    int tmp=0;
    for(set<int>::iterator it=s.begin();it!=s.end();++it){
        if(val[l]==val[*it]&&(*it)>r&&(a[*it][0]-a[l][0]==0||a[*it][0]-a[l][0]==tmp)) return;
        if((*it)>=l&&val[*it]<val[l]) tmp++;
    }
    tmp=0;
    for(set<int>::iterator it=s.end();it!=s.end();++it){
        if(val[r]==val[*it]&&(*it)<l&&(a[*it][1]-a[r][1]==0||a[*it][1]-a[r][1]==tmp)) return;
        if((*it)<=r&&val[*it]<val[l]) tmp++;
    }
    if(val[l]==val[r]&&a[l][0]==a[r][0]) return;
    int mid=(l+r)>>1;
    solve(l,mid);
    solve(mid,r);
}
int find_best(int n){
    solve(0,n-1);
    return ans;
}
int main(){
	int n;scanf("%d",&n);
	printf("! %d\n",find_best(n));
}
```

---

