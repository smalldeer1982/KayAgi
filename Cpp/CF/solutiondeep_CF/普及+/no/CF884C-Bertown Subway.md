# 题目信息

# Bertown Subway

## 题目描述

The construction of subway in Bertown is almost finished! The President of Berland will visit this city soon to look at the new subway himself.

There are $ n $ stations in the subway. It was built according to the Bertown Transport Law:

1. For each station $ i $ there exists exactly one train that goes from this station. Its destination station is $ p_{i} $ , possibly $ p_{i}=i $ ;
2. For each station $ i $ there exists exactly one station $ j $ such that $ p_{j}=i $ .

The President will consider the convenience of subway after visiting it. The convenience is the number of ordered pairs $ (x,y) $ such that person can start at station $ x $ and, after taking some subway trains (possibly zero), arrive at station $ y $ ( $ 1<=x,y<=n $ ).

The mayor of Bertown thinks that if the subway is not convenient enough, then the President might consider installing a new mayor (and, of course, the current mayor doesn't want it to happen). Before President visits the city mayor has enough time to rebuild some paths of subway, thus changing the values of $ p_{i} $ for not more than two subway stations. Of course, breaking the Bertown Transport Law is really bad, so the subway must be built according to the Law even after changes.

The mayor wants to do these changes in such a way that the convenience of the subway is maximized. Help him to calculate the maximum possible convenience he can get!

## 说明/提示

In the first example the mayor can change $ p_{2} $ to $ 3 $ and $ p_{3} $ to $ 1 $ , so there will be $ 9 $ pairs: $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,1) $ , $ (2,2) $ , $ (2,3) $ , $ (3,1) $ , $ (3,2) $ , $ (3,3) $ .

In the second example the mayor can change $ p_{2} $ to $ 4 $ and $ p_{3} $ to $ 5 $ .

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
1 5 4 3 2
```

### 输出

```
17
```

# AI分析结果

### 题目内容
# 贝托镇地铁

## 题目描述
贝托镇的地铁建设已接近尾声！不久后，伯兰总统将亲自访问这座城市，视察新建的地铁。

地铁共有 $n$ 个站点。其建设遵循贝托镇交通法：
1. 对于每个站点 $i$，恰好有一趟列车从该站出发，其目的站点为 $p_{i}$，可能 $p_{i}=i$；
2. 对于每个站点 $i$，恰好存在一个站点 $j$，使得 $p_{j}=i$。

总统视察后会考量地铁的便利性。便利性指的是有序对 $(x,y)$ 的数量，其中人可以从站点 $x$ 出发，乘坐若干趟地铁列车（可能为零趟）后抵达站点 $y$（$1\leq x,y\leq n$）。

贝托镇镇长认为，如果地铁的便利性不够，总统可能会考虑任命新的镇长（当然，现任镇长不希望这种情况发生）。在总统访问这座城市之前，镇长有足够的时间重建部分地铁线路，即改变不超过两个站点的 $p_{i}$ 值。当然，违反贝托镇交通法是非常严重的，因此即使做出改变，地铁仍必须遵循该法律建设。

镇长希望通过这些改变，使地铁的便利性最大化。请帮助他计算出所能获得的最大便利性！

## 说明/提示
在第一个示例中，镇长可以将 $p_{2}$ 改为 $3$，$p_{3}$ 改为 $1$，这样就会有 $9$ 个有序对：$(1,1)$，$(1,2)$，$(1,3)$，$(2,1)$，$(2,2)$，$(2,3)$，$(3,1)$，$(3,2)$，$(3,3)$。

在第二个示例中，镇长可以将 $p_{2}$ 改为 $4$，$p_{3}$ 改为 $5$。

## 样例 #1
### 输入
```
3
2 1 3
```
### 输出
```
9
```
## 样例 #2
### 输入
```
5
1 5 4 3 2
```
### 输出
```
17
```

### 算法分类
贪心

### 综合分析与结论
这三道题解思路基本一致，都基于以下认识：根据题目条件，站点间的连接会形成若干个环，每个环内的便利度为环长的平方。通过改变不超过两个站点的指向（即交换两个值），存在将环合并或拆分的情况，由于 $(a + b)^2 > a^2 + b^2$（$a,b>0$），所以为使便利度最大，应将两个最大环长的环合并。算法要点在于先通过搜索找到各个环及环长，再对环长进行排序，将最大的两个环长合并计算便利度，加上其他环的便利度得到结果。解决难点在于理解题目条件所构成的环结构以及分析不同交换情况对便利度的影响。

### 所选的题解
 - **作者：小明小红 (赞：1)  星级：4星**
    - **关键亮点**：思路清晰，详细阐述了循环节（环）的概念、便利度的计算方式以及分类讨论交换情况，代码注释详细，还提到了对排序时间复杂度的优化思路。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,size[100009],a[100009],ans;
void dfs(ll x) {
    ans++;
    size[x]=0;
    if(size[a[x]]==1) {
        dfs(a[x]);
    }
}
int main() {
    cin>>n;
    for(ll i=1; i<=n; i++) {
        cin>>a[i];
        size[i]=1;
    }
    for(ll i=1; i<=n; i++) {
        ans=0;
        if(size[i]==1) {
            dfs(i);
        }
        size[i]=ans;
    }
    sort(size+1,size+n+1);
    ll sum=(size[n]+size[n-1])*(size[n]+size[n-1]);
    for(ll i=1; i<n-1; i++) {
        sum+=size[i]*size[i];
    }
    cout<<sum;
    return 0;
}
```
核心实现思想：通过 `dfs` 函数标记并统计每个环内元素个数，存入 `size` 数组，对 `size` 数组排序后，将最大和次大的环长合并计算便利度，再加上其他环的便利度。

 - **作者：yuheng_wang080904 (赞：1)  星级：4星**
    - **关键亮点**：简洁明了地阐述题意和思路，代码简洁，利用 `bool` 数组标记访问过的节点来求环长。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p[100005],c[100005],cnt,maxi,maxj,ans;
bool vis[100005];
void dfs(int x){
    long long res=0;
    while(!vis[x]){
        vis[x]=1;
        res++;
        x=p[x];
    }
    c[++cnt]=res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++){
        if(!vis[i])dfs(i);
    }
    sort(c+1,c+1+cnt);
    for(int i=1;i<=cnt-2;i++)ans+=c[i]*c[i];
    ans+=(c[cnt-1]+c[cnt])*(c[cnt-1]+c[cnt]);
    cout<<ans<<endl;
    return 0;
}
```
核心实现思想：`dfs` 函数通过循环和 `vis` 数组标记计算每个环的长度并存入 `c` 数组，排序后将最大和次大的环长合并计算便利度，加上其他环的便利度。

 - **作者：流绪 (赞：1)  星级：4星**
    - **关键亮点**：详细描述了理解题目条件构成环的过程，代码简洁，直接在遍历找环的过程中计算原始便利度，最后通过公式计算合并环后的便利度增加值。
    - **个人心得**：详细描述了理解题目条件中 “存在确定的一条路线” 从而确定构成环的思考过程。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100010];
int v[100010]={0};
ll b[100010];
int main()
{
    ios::sync_with_stdio(false);
    ll n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> a[i];
    ll ans=0,p=0;
    for(int i=1;i<=n;i++)
    {
        if(v[i])
            continue;
        ll cnt = 1;
        ll x = a[i];
        v[x] = 1;
        while(x!=i)
        {
            x=a[x];
            v[x] = 1;
            cnt++;
        }
        b[p++] = cnt;
        ans += cnt*cnt;
    }
    if(p==1)
        cout << ans;
    else
    {
        sort(b,b+p);
        ans += b[p-1]*b[p-2]*2;
        cout << ans;
    }
} 
```
核心实现思想：通过遍历和 `v` 数组标记计算每个环的长度并存入 `b` 数组，同时累加原始便利度，最后通过公式 `b[p - 1] * b[p - 2] * 2` 计算合并最大两个环后的便利度增加值并加到总便利度上。

### 最优关键思路或技巧
1. **环结构的识别**：根据题目条件，快速识别出站点间的连接形成环结构，这是解决问题的基础。
2. **贪心策略**：通过数学推导得出将最大的两个环合并能使便利度最大的贪心策略。
3. **搜索求环长**：利用深度优先搜索（如小明小红题解）或类似的标记遍历方式（如其他两篇题解）来计算每个环的长度。

### 可拓展思路
此类题目可拓展到更复杂的图结构，如带权图中环的相关问题，或者限制条件更多的图上操作优化问题。类似算法套路在于先分析图的结构特点，再通过数学分析得出贪心策略，最后利用合适的搜索方式来处理图结构。

### 洛谷相似题目推荐
1. **P1195 口袋的天空**：涉及图的连通性和最小生成树相关知识，与本题分析图结构特点有相似之处。
2. **P3366 最小生成树**：同样是图论中关于最小生成树的问题，锻炼对图结构的处理和算法应用能力。
3. **P2330 [SCOI2005]繁忙的都市**：也是图论中最小生成树相关题目，通过不同的条件设置，加深对图论算法的理解和应用。 

---
处理用时：62.46秒