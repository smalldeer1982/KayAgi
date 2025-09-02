# 题目信息

# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1
```

### 输出

```
3
1
4
```

# AI分析结果

### 题目翻译
# 浇灌花园

## 题目描述
现在是冬天，Max 觉得是时候给花园浇水了。

花园可以用 $n$ 个连续的花坛表示，编号从 $1$ 到 $n$。有 $k$ 个花坛装有水龙头（第 $i$ 个水龙头位于花坛 $x_{i}$ 处），如果打开水龙头，水就会开始流向相邻的花坛。如果打开位于花坛 $x_{i}$ 处的水龙头，那么 $1$ 秒后，花坛 $x_{i}$ 会被浇到水；$2$ 秒后，区间 $[x_{i}-1,x_{i}+1]$ 内的花坛（如果存在）会被浇到水；$j$ 秒后（$j$ 为整数），区间 $[x_{i}-(j - 1),x_{i}+(j - 1)]$ 内的花坛（如果存在）会被浇到水。在这期间，情况不会有变化，例如，我们不能说 $2.5$ 秒后区间 $[x_{i}-2.5,x_{i}+2.5]$ 会被浇到水，在那一刻只有区间 $[x_{i}-2,x_{i}+2]$ 会被浇到水。

![花园示例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) 测试 $1$ 中的花园。白色表示没有水龙头的花坛，红色表示有水龙头的花坛。
![花园示例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) 打开水龙头 $2$ 秒后的测试 $1$ 中的花园。白色表示未浇水的花坛，蓝色表示已浇水的花坛。

Max 想同时打开所有的水龙头，现在他想知道，从他打开一些水龙头到整个花园都被浇到水，最少需要经过多少秒。帮他找到答案！

## 说明/提示
第一个样例包含 $3$ 个测试用例：
1. 有 $5$ 个花坛，水龙头在第 $3$ 个花坛。如果打开它，$1$ 秒后只有第 $3$ 个花坛会被浇到水；$2$ 秒后，区间 $[1,3]$ 内的花坛会被浇到水；$3$ 秒后，所有花坛都会被浇到水。
2. 有 $3$ 个花坛，每个花坛都有一个水龙头。如果打开所有水龙头，$1$ 秒后所有花坛都会被浇到水。
3. 有 $4$ 个花坛，只有一个水龙头在第 $1$ 个花坛。例如，浇到第 $4$ 个花坛需要 $4$ 秒。

## 样例 #1
### 输入
```
3
5 1
3
3 3
1 2 3
4 1
1
```
### 输出
```
3
1
4
```

### 综合分析与结论
这些题解主要围绕计算同时打开所有水龙头后，浇灌整个花园所需的最少时间展开，主要有两种思路方向：
1. **数学计算**：通过分析水龙头之间的距离，计算每个区域的浇灌时间，取最大值得到结果。
2. **搜索算法**：使用 BFS 或 DFS 模拟浇水过程，记录每个位置被浇灌的时间，最终找出最大时间。

### 算法要点与难点对比
|思路|算法要点|解决难点|
|----|----|----|
|数学计算|计算第一个水龙头到最左侧、最后一个水龙头到最右侧以及相邻水龙头间区域的浇灌时间，取最大值|合理处理边界情况和相邻水龙头间距离的计算|
|搜索算法|BFS 或 DFS 模拟浇水过程，记录每个位置被浇灌的时间|确保不重复计算已浇灌位置，正确处理多组数据的初始化|

### 题解评分与选择
|作者|评分|关键亮点|
|----|----|----|
|nenugdi|4星|思路清晰，代码简洁，直接通过数学计算得出结果，避免了复杂的搜索过程|
|codesonic|4星|使用 BFS 算法模拟浇水过程，代码规范，注释清晰，便于理解|
|CHIS_fy|3星|使用 DFS 算法模拟，适合初学者理解，但代码复杂度相对较高|

### 所选题解
- **nenugdi（4星）**
    - **关键亮点**：思路清晰，代码简洁，通过数学计算直接得出结果。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int i,j,t,n,k,x,pre,maxn;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        cin>>pre;
        maxn=pre;
        for(i=2;i<=k;i++)
        {
            cin>>x;
            maxn=max(maxn,(x-pre)/2+1);
            pre=x;
        }
        maxn=max(maxn,n-pre+1);
        cout<<maxn<<endl;
    }
    return 0;
}
```
    - **核心思想**：除第一个和最后一个龙头外，其他龙头间区域的覆盖时间是两个龙头距离除 2 再加 1，分别计算第一个龙头到最左侧、最后一个龙头到最右侧以及相邻龙头间区域的浇灌时间，取最大值。
- **codesonic（4星）**
    - **关键亮点**：使用 BFS 算法模拟浇水过程，代码规范，注释清晰。
    - **核心代码**：
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=210;
int x[maxn];
bool vis[maxn];
struct node {
    int s,dep;
};
queue<node> q;
int ans=-1;
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        memset(vis,0,sizeof(vis));
        int n,k;
        scanf("%d%d",&n,&k);
        for(int i=1; i<=k; i++) {
            int t;
            scanf("%d",&t);
            node temp;
            temp.s=t;
            temp.dep=1;
            q.push(temp);
            vis[temp.s]=1;
        }
        while(!q.empty()) {
            node x=q.front();
            q.pop();
            ans=max(ans,x.dep);
            if(x.s-1>0&&!vis[x.s-1]) {
                node temp;
                temp.s=x.s-1;
                temp.dep=x.dep+1;
                vis[x.s-1]=1;
                q.push(temp);
            }
            if(x.s+1<=n&&!vis[x.s+1]) {
                node temp;
                temp.s=x.s+1;
                temp.dep=x.dep+1;
                vis[x.s+1]=1;
                q.push(temp);
            }
        }
        printf("%d\n",ans);
        ans=-1;
    }
    return 0;
}
```
    - **核心思想**：将每个水龙头所在方格入队，使用 BFS 算法模拟浇水过程，记录每个节点被搜索到的时间，找出最大时间。

### 最优关键思路或技巧
- **数学计算思路**：通过分析问题的本质，将问题转化为计算水龙头间距离和边界距离，避免了复杂的模拟过程，提高了效率。
- **BFS 思路**：使用队列进行广度优先搜索，能够按层次模拟浇水过程，确保每个位置被正确处理。

### 拓展思路
同类型题或类似算法套路：
- 多个光源照亮整个区域，计算最少需要的时间或光源强度。
- 多个信号源覆盖整个区域，计算最少需要的时间或信号强度。

### 洛谷相似题目推荐
1. P1141 01迷宫：通过搜索算法解决区域覆盖问题。
2. P1332 血色先锋队：使用 BFS 算法计算最短时间。
3. P1605 迷宫：经典的搜索算法题目，可加深对搜索算法的理解。

### 个人心得摘录与总结
- **LordLaffey**：在使用 BFS 算法时，一定要记得清空队列，否则可能会导致结果错误。
- **Qiancy1427**：在实现暴力搜索算法时，要注意变量的使用，避免因变量错误导致结果错误。

---
处理用时：44.18秒