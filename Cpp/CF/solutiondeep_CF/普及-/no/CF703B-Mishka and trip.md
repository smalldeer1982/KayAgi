# 题目信息

# Mishka and trip

## 题目描述

Little Mishka is a great traveller and she visited many countries. After thinking about where to travel this time, she chose XXX — beautiful, but little-known northern country.

Here are some interesting facts about XXX:

1. XXX consists of $ n $ cities, $ k $ of whose (just imagine!) are capital cities.
2. All of cities in the country are beautiful, but each is beautiful in its own way. Beauty value of $ i $ -th city equals to $ c_{i} $ .
3. All the cities are consecutively connected by the roads, including $ 1 $ -st and $ n $ -th city, forming a cyclic route $ 1—2—...—n—1 $ . Formally, for every $ 1<=i&lt;n $ there is a road between $ i $ -th and $ i+1 $ -th city, and another one between $ 1 $ -st and $ n $ -th city.
4. Each capital city is connected with each other city directly by the roads. Formally, if city $ x $ is a capital city, then for every $ 1<=i<=n,i≠x $ , there is a road between cities $ x $ and $ i $ .
5. There is at most one road between any two cities.
6. Price of passing a road directly depends on beauty values of cities it connects. Thus if there is a road between cities $ i $ and $ j $ , price of passing it equals $ c_{i}·c_{j} $ .

Mishka started to gather her things for a trip, but didn't still decide which route to follow and thus she asked you to help her determine summary price of passing each of the roads in XXX. Formally, for every pair of cities $ a $ and $ b $ ( $ a&lt;b $ ), such that there is a road between $ a $ and $ b $ you are to find sum of products $ c_{a}·c_{b} $ . Will you help her?

## 说明/提示

This image describes first sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703B/f56e7113e4ecabd1250712cc69d300125f300e0b.png)

It is easy to see that summary price is equal to $ 17 $ .

This image describes second sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703B/e184cc93e6f4812674986a147f81ce08dfb70d8b.png)

It is easy to see that summary price is equal to $ 71 $ .

## 样例 #1

### 输入

```
4 1
2 3 1 2
3
```

### 输出

```
17```

## 样例 #2

### 输入

```
5 2
3 5 2 2 4
1 4
```

### 输出

```
71```

# AI分析结果

### 题目翻译
# 米什卡的旅行

## 题目描述
小米什卡是一位伟大的旅行者，她去过许多国家。在思考这次该去哪里旅行后，她选择了XXX——一个美丽但鲜为人知的北方国家。

以下是关于XXX的一些有趣事实：

1. XXX由 $n$ 个城市组成，其中 $k$ 个（想象一下！）是首都城市。
2. 这个国家的所有城市都很美丽，但每个城市都有其独特的美。第 $i$ 个城市的美丽值等于 $c_{i}$。
3. 所有城市都通过道路依次相连，包括第1个和第 $n$ 个城市，形成一个环形路线 $1—2—...—n—1$。形式上，对于每一个 $1\leq i < n$，在第 $i$ 个和第 $i + 1$ 个城市之间有一条道路，在第1个和第 $n$ 个城市之间也有一条道路。
4. 每个首都城市都直接与其他每个城市通过道路相连。形式上，如果城市 $x$ 是首都城市，那么对于每一个 $1\leq i\leq n$ 且 $i\neq x$，在城市 $x$ 和 $i$ 之间都有一条道路。
5. 任意两个城市之间最多只有一条道路。
6. 通过一条道路的价格直接取决于它连接的城市的美丽值。因此，如果在城市 $i$ 和 $j$ 之间有一条道路，通过它的价格等于 $c_{i}·c_{j}$。

米什卡开始收拾旅行用品，但还没有决定走哪条路线，因此她请你帮助她确定XXX中每条道路的总通行价格。形式上，对于每一对城市 $a$ 和 $b$（$a < b$），如果在 $a$ 和 $b$ 之间有一条道路，你要找出所有乘积 $c_{a}·c_{b}$ 的和。你会帮助她吗？

## 说明/提示
此图描述了第一个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703B/f56e7113e4ecabd1250712cc69d300125f300e0b.png)

很容易看出总价格等于 $17$。

此图描述了第二个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703B/e184cc93e6f4812674986a147f81ce08dfb70d8b.png)

很容易看出总价格等于 $71$。

## 样例 #1
### 输入
```
4 1
2 3 1 2
3
```
### 输出
```
17
```

## 样例 #2
### 输入
```
5 2
3 5 2 2 4
1 4
```
### 输出
```
71
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是先处理普通城市形成环的边权和，再处理省会城市与其他城市相连的边权和，同时要注意去重边。各题解的主要区别在于处理省会城市边权和时的具体实现方式。

- **思路对比**：大部分题解都是先计算普通城市环的边权和，再针对省会城市，通过减去重复计算的边权来得到最终结果。部分题解采用了不同的方式来处理重复边，如使用布尔数组标记省会城市，或者直接在计算中减去重复的边权。
- **算法要点**：多数题解使用布尔数组标记省会城市，用变量记录所有城市的权值和以及已处理的省会城市的权值和，通过这些信息来计算边权和。
- **解决难点**：主要难点在于处理省会城市与其他城市相连的边时，避免重复计算。各题解通过不同的方式解决这个问题，如在计算边权和时减去相邻城市和已处理的省会城市的边权。

### 高评分题解
- **peppaking8（4星）**
    - **关键亮点**：思路清晰，详细阐述了空间和时间复杂度的优化过程，代码注释详细。
    - **个人心得**：无
- **jixuan（4星）**
    - **关键亮点**：思路简洁明了，代码实现较为清晰，时间复杂度分析准确。
    - **个人心得**：无
- **xiaoyuchenp（4星）**
    - **关键亮点**：明确指出了题目中的坑点，思路和代码都比较清晰。
    - **个人心得**：无

### 重点代码
#### peppaking8的代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
int n,m,val[N],sum,nowsum,ans=0;
bool is_cap[N];
int first_num(int k){
    if(k==1) return n;
    return k-1;
}
int last_num(int k){
    if(k==n) return 1;
    return k+1;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&val[i]);sum+=val[i];
        ans+=val[i]*val[i-1];
    }
    ans+=val[1]*val[n];
    for(int i=1;i<=m;i++){
        int capi;
        scanf("%lld",&capi);
        is_cap[capi]=true;
        nowsum+=val[capi];
        ans+=val[capi]*(sum-nowsum);
        if(!is_cap[first_num(capi)]) ans-=val[capi]*val[first_num(capi)];
        if(!is_cap[last_num(capi)]) ans-=val[capi]*val[last_num(capi)];
    }
    printf("%lld\n",ans);
    exit(0);
}
```
**核心实现思想**：先计算普通城市环的边权和，用 `sum` 记录所有城市的权值和，`nowsum` 记录已处理的省会城市的权值和。对于每个省会城市，计算其与其他非省会城市的边权和，同时减去与相邻城市的重复边权。

#### jixuan的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,sum,ssum,ans;
int c[100010],id[100010],f[100010];
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)
    {
        ans+=c[i]*c[i%n+1];
        sum+=c[i];
    }
    for(int i=1;i<=k;i++)
    {
        cin>>id[i];
        f[id[i]]=1;
        int lf=id[i]-1,rt=id[i]+1,t=ssum;
        if(lf==0)lf=n;
        if(rt==n+1)rt=1;
        if(f[lf]==1)t-=c[lf];
        if(f[rt]==1)t-=c[rt];
        ans+=c[id[i]]*sum;
        ans-=c[id[i]]*(c[rt]+c[lf]+c[id[i]]);
        ans-=c[id[i]]*t;
        ssum+=c[id[i]];
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：先计算普通城市环的边权和以及所有城市的权值和 `sum`。对于每个省会城市，计算其与所有城市的边权和，减去与相邻城市和已处理的省会城市的重复边权，用 `ssum` 记录已处理的省会城市的权值和。

#### xiaoyuchenp的代码
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define pre(x) (x==1? n:x-1)
#define next(x) (x==n? 1:x+1)
using namespace std;
int n,k;
int c[MAXN],id;
long long ans,sum;
bool iscap[MAXN];

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++){
        ans+=c[i]*c[pre(i)];
        sum+=c[i];
    }
    for(int i=1;i<=k;i++){
        cin>>id;
        iscap[id]=true;
        sum-=c[id];
        long long tmp=sum*c[id];
        if(!iscap[pre(id)])tmp-=c[pre(id)]*c[id];
        if(!iscap[next(id)])tmp-=c[next(id)]*c[id];
        ans+=tmp;
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：先计算普通城市环的边权和以及所有城市的权值和 `sum`。对于每个省会城市，计算其与其他非省会城市的边权和，减去与相邻城市的重复边权。

### 最优关键思路或技巧
- 使用布尔数组标记省会城市，方便判断是否为省会城市。
- 用变量记录所有城市的权值和以及已处理的省会城市的权值和，避免重复计算。
- 在计算边权和时，减去重复计算的边权，确保结果的正确性。

### 拓展思路
同类型题或类似算法套路：
- 其他图论问题，如计算图的边权和、最短路径等。
- 处理图中重复边或避免重复计算的问题。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 个人心得摘录与总结
- **ylch**：作者表示这是一道很有难度的思维题，写题解的过程中自己也被绕进去，花费了六个小时才写出来，通过写题解理顺了思路，加深了对题目的理解。总结就是这类思维题需要仔细思考，避免陷入逻辑误区。

---
处理用时：64.90秒