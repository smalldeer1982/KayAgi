# Iris and Game on the Tree

## 题目描述

给定一棵根为 $1$，每个点有 $0$ 或 $1$ 的点权的有根树，对于所有叶子定义权值为：取出根到它的路径上所有点的点权形成的 $01$ 串，其中 $10$ 子串的出现次数减去 $01$ 子串的出现次数。不认为根为叶子。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006A/66d8f9cca162bbc9b7dcbbd0c66de4a705cfbe4e.png)

如图，绿点的点权为 $1$，白点的点权为 $0$，根到 $5$ 的串为 $10110$，其中有 $2$ 个 $10$，$1$ 个 $01$，故 $5$ 的权值为 $1$。

一棵树的分数被定义为：具有非零权值的叶子的数量。

有些点权尚未确定，A 与 B 在玩游戏，她们轮流将一个未确定点的点权改为 $0$ 或 $1$。先手的 A 希望最大化树的分数，后手的 B 希望最小化之，二人均采取最优策略，求最后树的分数。

## 说明/提示

$1 \leq t \leq 5 \cdot 10^4$，$2 \leq \sum n \leq 2 \cdot 10^5$。

translated by uid 443664

## 样例 #1

### 输入

```
6
4
1 2
1 3
4 1
0101
4
1 2
3 2
2 4
???0
5
1 2
1 3
2 4
2 5
?1?01
6
1 2
2 3
3 4
5 3
3 6
?0????
5
1 2
1 3
1 4
1 5
11?1?
2
2 1
??```

### 输出

```
2
1
1
2
1
0```

# 题解

## 作者：I_will_AKIOI (赞：4)

这场主打一个极限，最后一分钟过了该题直接逆天改命了，故写题解纪念。

手玩样例可得出一个结论：**若根节点颜色和叶子节点相同，则叶子结点权值为 $0$，否则不为 $0$**。这也很好理解：可以把根到叶子的字符串比作爬山的过程，$1$ 就是山顶，$0$ 就是山谷，那么 $01$ 就是上山，$10$ 就是下山。如果你想让上山和下山的次数相等，那么你爬完这座山过后的高度显然要和你初始的高度一样。

我们先给树做一遍 dfs，$cnt_0$ 表示叶节点 $0$ 的出现个数，$cnt_1$ 表示 $1$ 出现个数，$cnt_2$ 表示问号的出现个数，$s_i$ 表示第 $i$ 个节点的颜色。接着就是分类讨论。如根节点已被染色，那么 Iris 肯定会染和根节点相反的颜色，Dora 会染和根节点相同的颜色。由于 Iris 先操作，因此答案要向上取整，也就是 $cnt_{1-s_1}+\big\lfloor \frac{cnt_2+1}{2} \big\rfloor$。

如果根节点未被染色，由于 Iris 先操作，那么他肯定先把根节点染成叶子结点出现次数**更多**的颜色。但是叶子结点现在变成 Dora 先操作了。因此 Dora 会染和根相同的颜色来减少答案。因此答案就是 $\max(cnt_0,cnt_1)+\big\lfloor \frac{cnt_2}{2} \big\rfloor$。

但是其中有一个特例，如果 $cnt_0=cnt_1$，那么二人无论谁先染色，都对自己不利。因为一旦染完就换对方走了，对方就会利用你染的颜色来改变答案。因此他们就会先染除了根和叶子之外还没染色的节点。因此我们在 dfs 时多统计一个 $cnt_3$，表示除了根和叶子之外还没染色的节点个数。如果 $cnt_3$ 为奇数，那么全部染色完之后就是 Dora 先操作。答案就是 $\max(cnt_0,cnt_1)+\big\lfloor \frac{cnt_2+1}{2} \big\rfloor$，否则答案就是 $\max(cnt_0,cnt_1)+\big\lfloor \frac{cnt_2}{2} \big\rfloor$。

```cpp
#include<bits/stdc++.h>
#define N 100005
#pragma GCC optimize("O3")
using namespace std;
int n,cnt[4];
vector<int>v[N];
char c[N];
void dfs(int k,int fa)
{
  if(v[k].size()==1&&k!=1)//度为1且当前节点不是1，是叶子结点
  {
    if(c[k]=='0') cnt[0]++;
    if(c[k]=='1') cnt[1]++;
    if(c[k]=='?') cnt[2]++;
  }
  else if(k!=1&&c[k]=='?') cnt[3]++;//不是根和叶子的未染色节点
  for(int now:v[k])
  {
    if(now==fa) continue;
    dfs(now,k);
  }
  return;
}
void solve()
{
	cin>>n;
  for(int i=1;i<=n;i++) v[i].clear();
  for(int i=1;i<n;i++)
  {
    int x,y;
    cin>>x>>y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  for(int i=1;i<=n;i++) cin>>c[i];
  cnt[0]=cnt[1]=cnt[2]=cnt[3]=0;
  dfs(1,0);
  if(c[1]=='?')//分类讨论
  {
    if(cnt[0]==cnt[1]) cout<<max(cnt[0],cnt[1])+(cnt[2]+(cnt[3]&1))/2<<"\n";
    else cout<<max(cnt[0],cnt[1])+cnt[2]/2<<"\n";
  }
  else cout<<cnt[1-(c[1]-'0')]+(cnt[2]+1)/2<<"\n";
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

