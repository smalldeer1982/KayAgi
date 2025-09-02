# 题目信息

# The Number of Imposters

## 题目描述

Theofanis started playing the new online game called "Among them". However, he always plays with Cypriot players, and they all have the same name: "Andreas" (the most common name in Cyprus).

In each game, Theofanis plays with $ n $ other players. Since they all have the same name, they are numbered from $ 1 $ to $ n $ .

The players write $ m $ comments in the chat. A comment has the structure of " $ i $ $ j $ $ c $ " where $ i $ and $ j $ are two distinct integers and $ c $ is a string ( $ 1 \le i, j \le n $ ; $ i \neq j $ ; $ c $ is either imposter or crewmate). The comment means that player $ i $ said that player $ j $ has the role $ c $ .

An imposter always lies, and a crewmate always tells the truth.

Help Theofanis find the maximum possible number of imposters among all the other Cypriot players, or determine that the comments contradict each other (see the notes for further explanation).

Note that each player has exactly one role: either imposter or crewmate.

## 说明/提示

In the first test case, imposters can be Andreas $ 2 $ and $ 3 $ .

In the second test case, imposters can be Andreas $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ .

In the third test case, comments contradict each other. This is because player $ 1 $ says that player $ 2 $ is an imposter, and player $ 2 $ says that player $ 1 $ is a crewmate. If player $ 1 $ is a crewmate, then he must be telling the truth, so player $ 2 $ must be an imposter. But if player $ 2 $ is an imposter then he must be lying, so player $ 1 $ can't be a crewmate. Contradiction.

## 样例 #1

### 输入

```
5
3 2
1 2 imposter
2 3 crewmate
5 4
1 3 crewmate
2 5 crewmate
2 4 imposter
3 4 imposter
2 2
1 2 imposter
2 1 crewmate
3 5
1 2 imposter
1 2 imposter
3 2 crewmate
3 2 crewmate
1 3 imposter
5 0```

### 输出

```
2
4
-1
2
5```

# AI分析结果

### 题目内容中文重写
# 冒名顶替者的数量

## 题目描述
西奥法尼斯开始玩一款名为 “Among them” 的新网络游戏。然而，他总是和塞浦路斯玩家一起玩，而他们都有相同的名字：“安德烈亚斯”（塞浦路斯最常见的名字）。

在每一局游戏中，西奥法尼斯会和 $n$ 个其他玩家一起玩。由于他们都有相同的名字，所以他们从 $1$ 到 $n$ 进行编号。

玩家们在聊天中发表 $m$ 条评论。一条评论的结构为 “$i$ $j$ $c$”，其中 $i$ 和 $j$ 是两个不同的整数，$c$ 是一个字符串（$1 \le i, j \le n$；$i \neq j$；$c$ 要么是 “imposter”（冒名顶替者），要么是 “crewmate”（船员））。这条评论意味着玩家 $i$ 说玩家 $j$ 具有角色 $c$。

冒名顶替者总是说谎，而船员总是说真话。

帮助西奥法尼斯找出所有其他塞浦路斯玩家中冒名顶替者的最大可能数量，或者确定这些评论是否相互矛盾（详见注释）。

请注意，每个玩家恰好有一个角色：要么是冒名顶替者，要么是船员。

## 说明/提示
在第一个测试用例中，冒名顶替者可能是安德烈亚斯 $2$ 和 $3$。

在第二个测试用例中，冒名顶替者可能是安德烈亚斯 $1$、$2$、$3$ 和 $5$。

在第三个测试用例中，评论相互矛盾。这是因为玩家 $1$ 说玩家 $2$ 是冒名顶替者，而玩家 $2$ 说玩家 $1$ 是船员。如果玩家 $1$ 是船员，那么他一定说的是真话，所以玩家 $2$ 一定是冒名顶替者。但如果玩家 $2$ 是冒名顶替者，那么他一定在说谎，所以玩家 $1$ 不可能是船员。这就产生了矛盾。

## 样例 #1
### 输入
```
5
3 2
1 2 imposter
2 3 crewmate
5 4
1 3 crewmate
2 5 crewmate
2 4 imposter
3 4 imposter
2 2
1 2 imposter
2 1 crewmate
3 5
1 2 imposter
1 2 imposter
3 2 crewmate
3 2 crewmate
1 3 imposter
5 0
```

### 输出
```
2
4
-1
2
5
```

### 算法分类
并查集

### 综合分析与结论
这些题解主要围绕如何利用并查集或图论的方法来解决玩家身份判断及冒名顶替者最大数量计算的问题。大部分题解采用扩展域并查集，将每个玩家的两种身份（船员和冒名顶替者）分别用不同的节点表示，通过合并操作来维护玩家之间的关系；部分题解使用图论的思想，通过建图、dfs 染色来确定每个连通块中玩家的身份。

各题解的思路核心都是根据玩家之间的陈述关系来确定玩家身份的关联，难点在于处理矛盾情况（即一个玩家不能既是船员又是冒名顶替者）以及如何统计冒名顶替者的最大数量。

### 所选题解
- **PragmaGCC（5星）**
  - **关键亮点**：思路清晰，代码简洁高效。使用扩展域并查集，通过合并操作维护玩家身份关系，最后统计每个集合中冒名顶替者和船员数量的最大值累加得到结果。
  - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
char s[N];
int T, n, m;
int fa[N << 1], siz[N << 1];
int find(int x) { 
    if (x == fa[x]) return x;
    fa[x] = find(fa[x]);
    siz[fa[x]] += siz[x];
    siz[x] = 0;
    return fa[x];
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return ;
    siz[fx] += siz[fy]; siz[fy] = 0;
    fa[fy] = fx;
}
int main(void) {
    for (scanf("%d", &T); T; T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n << 1; i++) fa[i] = i, siz[i] = i <= n;
        for (int i = 1, x, y; i <= m; i++) {
            scanf("%d%d%s", &x, &y, s);
            if (s[0] == 'c') merge(x, y), merge(x + n, y + n);
            else merge(x, y + n), merge(y, x + n);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (find(i) == find(i + n)) {ans = -1; break;} 
            ans += max(siz[find(i)], siz[find(i + n)]);
            siz[find(i)] = siz[find(i + n)] = 0; 
        }
        printf("%d\n", ans);
    }
}
```
- **智子（4星）**
  - **关键亮点**：思路详细，类比经典题目，对扩展域并查集的使用解释清晰，代码结构清晰。
  - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 200000 + 5;
int f[MAXN * 2], vis[MAXN * 2], cnt[MAXN * 2];
int n, m, p;
int find(int k) {
    return k == f[k] ? k : f[k] = find(f[k]);
}
int main() {
    int T;
    cin >> T;
    while(T--) {
        char s[20];
        memset(vis, 0, sizeof(vis));
        memset(cnt, 0, sizeof(cnt));
        memset(f, 0, sizeof(f));
        cin >> n >> m;
        for(int i = 1; i <= n * 2; i++) {
            f[i] = i;
        }
        for(int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y >> s;
            if(s[0] == 'c') {
                f[find(x)] = f[find(y)];
                f[find(x + n)] = find(y + n);
            } else {
                f[find(x)] = find(y + n);
                f[find(x + n)] = find(y);
            }
        }
        bool flag = true;
        for(int i = 1; i <= n; i++) {
            if(find(i) == find(i + n)) {
                flag = false; 
            }
        }
        if(!flag) {
            cout << -1 << endl;
            continue;
        }
        p = 0;
        for(int i = 1; i <= n * 2; i++) {
            if(i > n) {
                cnt[find(i)]++; 
            }
        }
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(vis[find(i)] || vis[find(i + n)]) {
                continue; 
            }
            ans += max(cnt[find(i)], cnt[find(i + n)]); 
            vis[find(i)] = true;
            vis[find(i + n)] = true; 
        }
        cout << ans << endl;
    }
    return 0;
}
```
- **leexzq（4星）**
  - **关键亮点**：对每条对话的含义分析清晰，代码实现简洁，使用扩展域并查集解决问题。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
using namespace std;
const int N=2e5+10,M=5e5+10;
int fa[N*2],siz[N*2],n,m,a[M],x[M],y[M],b[M];
int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
void merge(int x,int y)
{
    if(x==y)return;
    fa[x]=y,siz[y]+=siz[x];
}
int solve(int ans=0)
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1,b[i]=0;
    for(int i=n+1;i<=2*n;i++)fa[i]=i,siz[i]=0,b[i]=0;
    for(int i=1;i<=m;i++)
    {
        string s;
        cin>>x[i]>>y[i]>>s;
        if(s[0]=='i')a[i]=1;
        else a[i]=0;
    }
    for(int i=1;i<=m;i++)
    {
        int x1=get(x[i]),y1=get(y[i]),x2=get(x[i]+n),y2=get(y[i]+n);
        if(a[i]==1)
        {
            if(x1==y1||x2==y2)return -1;
            merge(y2,x1),merge(x2,y1);
        }
        else
        {
            if(x1==y2||x2==y1)return -1;
            merge(x1,y1),merge(x2,y2);
        }
    }
    for(int i=1;i<=n;i++)
    {
        int x1=get(i),x2=get(i+n);
        if(!b[x1]&&!b[x2])ans+=max(siz[x1],siz[x2]),b[x1]=b[x2]=1;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--)cout<<solve()<<endl;
}
```

### 最优关键思路或技巧
- **扩展域并查集**：将每个玩家的两种身份（船员和冒名顶替者）分别用不同的节点表示，通过合并操作维护玩家之间的身份关系，方便处理矛盾情况和统计数量。
- **异或思想**：部分题解利用异或来描述玩家之间的身份关系，将玩家的身份用 $01$ 表示，边权表示两端点身份的异或和，通过 dfs 染色来确定每个连通块中玩家的身份。

### 可拓展之处
同类型题如 [NOI2001 食物链](https://www.luogu.com.cn/problem/P2024)，都是利用并查集处理具有多种关系的元素之间的关联问题。类似算法套路还有带权并查集，通过维护节点与根节点的某种权值关系来解决问题。

### 推荐洛谷题目
1. [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)
2. [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)
3. [P1196 [NOI2002] 银河英雄传说](https://www.luogu.com.cn/problem/P1196)

### 个人心得
题解中无明显个人心得内容。 

---
处理用时：104.02秒