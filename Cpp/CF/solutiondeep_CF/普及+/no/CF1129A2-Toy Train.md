# 题目信息

# Toy Train

## 题目描述

Alice received a set of Toy Train™ from Bob. It consists of one train and a connected railway network of $ n $ stations, enumerated from $ 1 $ through $ n $ . The train occupies one station at a time and travels around the network of stations in a circular manner. More precisely, the immediate station that the train will visit after station $ i $ is station $ i+1 $ if $ 1 \leq i < n $ or station $ 1 $ if $ i = n $ . It takes the train $ 1 $ second to travel to its next station as described.

Bob gave Alice a fun task before he left: to deliver $ m $ candies that are initially at some stations to their independent destinations using the train. The candies are enumerated from $ 1 $ through $ m $ . Candy $ i $ ( $ 1 \leq i \leq m $ ), now at station $ a_i $ , should be delivered to station $ b_i $ ( $ a_i \neq b_i $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1129A2/553bfb305c93eff18c75fbd09eed41cc245d82d0.png)The blue numbers on the candies correspond to $ b_i $ values. The image corresponds to the $ 1 $ -st example.The train has infinite capacity, and it is possible to load off any number of candies at a station. However, only at most one candy can be loaded from a station onto the train before it leaves the station. You can choose any candy at this station. The time it takes to move the candies is negligible.

Now, Alice wonders how much time is needed for the train to deliver all candies. Your task is to find, for each station, the minimum time the train would need to deliver all the candies were it to start from there.

## 说明/提示

Consider the second sample.

If the train started at station $ 1 $ , the optimal strategy is as follows.

1. Load the first candy onto the train.
2. Proceed to station $ 2 $ . This step takes $ 1 $ second.
3. Deliver the first candy.
4. Proceed to station $ 1 $ . This step takes $ 1 $ second.
5. Load the second candy onto the train.
6. Proceed to station $ 2 $ . This step takes $ 1 $ second.
7. Deliver the second candy.
8. Proceed to station $ 1 $ . This step takes $ 1 $ second.
9. Load the third candy onto the train.
10. Proceed to station $ 2 $ . This step takes $ 1 $ second.
11. Deliver the third candy.

Hence, the train needs $ 5 $ seconds to complete the tasks.

If the train were to start at station $ 2 $ , however, it would need to move to station $ 1 $ before it could load the first candy, which would take one additional second. Thus, the answer in this scenario is $ 5+1 = 6 $ seconds.

## 样例 #1

### 输入

```
5 7
2 4
5 1
2 3
3 4
4 1
5 3
3 5
```

### 输出

```
10 9 10 10 9 
```

## 样例 #2

### 输入

```
2 3
1 2
1 2
1 2
```

### 输出

```
5 6 
```

# AI分析结果

### 题目内容中文重写
# 玩具火车

## 题目描述
爱丽丝从鲍勃那里收到了一套玩具火车。它由一列火车和一个连接着 $n$ 个车站的铁路网络组成，车站从 $1$ 到 $n$ 编号。火车一次占据一个车站，并以环形方式在车站网络中行驶。更准确地说，如果 $1 \leq i < n$，火车在经过车站 $i$ 后将立即前往车站 $i + 1$；如果 $i = n$，则前往车站 $1$。按照上述规则，火车行驶到下一个车站需要 $1$ 秒。

鲍勃在离开前给爱丽丝布置了一个有趣的任务：使用火车将最初位于某些车站的 $m$ 颗糖果运送到各自独立的目的地。糖果从 $1$ 到 $m$ 编号。糖果 $i$（$1 \leq i \leq m$）目前位于车站 $a_i$，应被运送到车站 $b_i$（$a_i \neq b_i$）。

蓝色的糖果编号对应 $b_i$ 的值。该图对应第一个示例。火车的容量是无限的，并且可以在一个车站卸下任意数量的糖果。但是，在火车离开一个车站之前，最多只能从该车站装载一颗糖果。你可以选择该车站的任意一颗糖果。移动糖果所需的时间可以忽略不计。

现在，爱丽丝想知道火车运送所有糖果需要多长时间。你的任务是为每个车站找出，如果火车从该车站出发，运送所有糖果所需的最短时间。

## 说明/提示
考虑第二个样例。

如果火车从车站 $1$ 出发，最优策略如下：

1. 将第一颗糖果装载到火车上。
2. 前往车站 $2$。此步骤需要 $1$ 秒。
3. 卸下第一颗糖果。
4. 前往车站 $1$。此步骤需要 $1$ 秒。
5. 将第二颗糖果装载到火车上。
6. 前往车站 $2$。此步骤需要 $1$ 秒。
7. 卸下第二颗糖果。
8. 前往车站 $1$。此步骤需要 $1$ 秒。
9. 将第三颗糖果装载到火车上。
10. 前往车站 $2$。此步骤需要 $1$ 秒。
11. 卸下第三颗糖果。

因此，火车完成任务需要 $5$ 秒。

然而，如果火车从车站 $2$ 出发，它需要先移动到车站 $1$ 才能装载第一颗糖果，这将多花费 $1$ 秒。因此，在这种情况下的答案是 $5 + 1 = 6$ 秒。

## 样例 #1

### 输入
```
5 7
2 4
5 1
2 3
3 4
4 1
5 3
3 5
```

### 输出
```
10 9 10 10 9 
```

## 样例 #2

### 输入
```
2 3
1 2
1 2
1 2
```

### 输出
```
5 6 
```

### 算法分类
贪心

### 综合分析与结论
题解采用贪心算法，核心思路是对于每个有糖果的点，先取要走步数多的糖果，留到最后的是该点为起点要走步数最少的糖果。通过计算每个点的最少步数和糖果数量，得出从每个车站出发运送所有糖果的最短时间。算法要点在于计算每个点的最少步数 `mn[i]` 和糖果数量 `sum[i]`，并根据公式 `(sum[j] - 1) * n + mn[j] + (j - i + n) % n` 计算结果。解决的难点在于理解贪心策略的正确性，即优先处理走步数多的糖果能使总时间最短。

### 所选的题解
- 作者：luo_shen (赞：1)，4星。关键亮点：思路清晰，通过贪心策略解决问题，代码实现简洁明了。

### 重点代码及核心实现思想
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,mn[5010],sum[5010];
int main(){
    memset(mn,0x3f,sizeof(mn));
    cin>>n>>m;
    for(int i=1;i<=m;i++){//(i-j+n)%n表示在环上从x走到y所需步数
        cin>>x>>y;
        mn[x]=min(mn[x],(y-x+n)%n);
        sum[x]++;//处理出每个点的mn[i]和sum[i]
    }
    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=1;j<=n;j++){
            if(!sum[j])continue;
            int s=(sum[j]-1)*n+mn[j]+(j-i+n)%n;
            ans=max(ans,s);
        }
        cout<<ans<<' ';
    }
    return 0;
}
```
核心实现思想：首先初始化 `mn` 数组为一个较大的值，然后读取输入，计算每个点的最少步数 `mn[i]` 和糖果数量 `sum[i]`。接着对于每个车站，遍历所有有糖果的点，根据公式计算从该车站出发运送所有糖果的最短时间，取最大值作为最终结果。

### 关键思路或技巧
- 贪心策略：优先处理走步数多的糖果，留到最后的是该点为起点要走步数最少的糖果。
- 环形距离计算：使用 `(y - x + n) % n` 计算在环上从 $x$ 走到 $y$ 所需的步数。

### 可拓展之处
同类型题或类似算法套路：在环形路径上进行任务分配和时间计算的问题，都可以考虑使用贪心策略，优先处理耗时多的任务，以达到总时间最短的目的。

### 推荐洛谷题目
- P1090 合并果子：同样使用贪心策略，每次合并重量最小的两堆果子，使总代价最小。
- P1223 排队接水：按照接水时间从小到大排序，使所有人的等待时间总和最小。
- P2123 皇后游戏：需要根据一定的规则对数据进行排序，然后使用贪心策略求解。 

---
处理用时：38.97秒