# 题目信息

# Morning Jogging

## 题目描述

The 2050 volunteers are organizing the "Run! Chase the Rising Sun" activity. Starting on Apr 25 at 7:30 am, runners will complete the 6km trail around the Yunqi town.

There are $ n+1 $ checkpoints on the trail. They are numbered by $ 0 $ , $ 1 $ , ..., $ n $ . A runner must start at checkpoint $ 0 $ and finish at checkpoint $ n $ . No checkpoint is skippable — he must run from checkpoint $ 0 $ to checkpoint $ 1 $ , then from checkpoint $ 1 $ to checkpoint $ 2 $ and so on. Look at the picture in notes section for clarification.

Between any two adjacent checkpoints, there are $ m $ different paths to choose. For any $ 1\le i\le n $ , to run from checkpoint $ i-1 $ to checkpoint $ i $ , a runner can choose exactly one from the $ m $ possible paths. The length of the $ j $ -th path between checkpoint $ i-1 $ and $ i $ is $ b_{i,j} $ for any $ 1\le j\le m $ and $ 1\le i\le n $ .

To test the trail, we have $ m $ runners. Each runner must run from the checkpoint $ 0 $ to the checkpoint $ n $ once, visiting all the checkpoints. Every path between every pair of adjacent checkpoints needs to be ran by exactly one runner. If a runner chooses the path of length $ l_i $ between checkpoint $ i-1 $ and $ i $ ( $ 1\le i\le n $ ), his tiredness is $ $$$\min_{i=1}^n l_i, $ $  i. e. the minimum length of the paths he takes.</p><p>Please arrange the paths of the  $ m$$$ runners to minimize the sum of tiredness of them.

## 说明/提示

In the first case, the sum of tiredness is $ \min(2,5) + \min(3,3) + \min(4,1) = 6 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517B/81bbf44dba6a58e8432744a5a3d75d6c54d8fb12.png)In the second case, the sum of tiredness is $ \min(2,4,3) + \min(3,1,5) = 3 $ .

## 样例 #1

### 输入

```
2
2 3
2 3 4
1 3 5
3 2
2 3
4 1
3 5```

### 输出

```
2 3 4
5 3 1
2 3
4 1
3 5```

# AI分析结果

### 题目内容重写（中文）

#### 晨跑

**题目描述**

2050年的志愿者们正在组织“奔跑！追逐朝阳”活动。活动将于4月25日早上7:30开始，跑步者将完成围绕云栖小镇的6公里跑道。

跑道上有$n+1$个检查点，编号为$0, 1, ..., n$。跑步者必须从检查点$0$开始，并在检查点$n$结束。每个检查点都不能跳过——跑步者必须从检查点$0$跑到检查点$1$，然后从检查点$1$跑到检查点$2$，依此类推。请查看注释部分的图片以获取更清晰的说明。

在任意两个相邻的检查点之间，有$m$条不同的路径可供选择。对于任意$1\le i\le n$，跑步者从检查点$i-1$跑到检查点$i$时，可以从$m$条路径中选择一条。第$j$条路径的长度为$b_{i,j}$，其中$1\le j\le m$且$1\le i\le n$。

为了测试跑道，我们有$m$个跑步者。每个跑步者必须从检查点$0$跑到检查点$n$一次，并经过所有检查点。每对相邻检查点之间的每条路径必须被恰好一个跑步者跑过。如果一个跑步者选择的路径长度为$l_i$，那么他的**疲累值**为$\min_{i=1}^n l_i$，即他所跑过的路径中最短的长度。

请安排跑步者的路径，使得他们的疲累值之和最小。

**说明/提示**

在第一个样例中，疲累值之和为$\min(2,5) + \min(3,3) + \min(4,1) = 6$。

在第二个样例中，疲累值之和为$\min(2,4,3) + \min(3,1,5) = 3$。

**样例 #1**

**输入**

```
2
2 3
2 3 4
1 3 5
3 2
2 3
4 1
3 5
```

**输出**

```
2 3 4
5 3 1
2 3
4 1
3 5
```

### 算法分类
贪心

### 题解分析与结论

题目要求安排$m$个跑步者的路径，使得他们的疲累值之和最小。疲累值定义为每个跑步者所跑路径中的最小长度。通过贪心策略，我们可以将前$m$小的路径长度分配给不同的跑步者，从而最小化疲累值之和。

### 所选题解

#### 题解1：BorisDimitri (赞：14)
**星级：5星**
**关键亮点：**
- 思路清晰，直接通过排序和贪心策略解决问题。
- 代码结构清晰，易于理解。
- 通过将前$m$小的路径长度分配给不同的跑步者，确保疲累值之和最小。

**核心代码：**
```cpp
sort(tired+1,tired+idx+1,cmp);

for(int j=1;j<=m;j++)//放置前m小的在不同的行里
{
    ans[tired[j].row][j] = tired[j].value;
}

for(int i=m+1;i<=idx;i++)
    for(int k=1;k<=m;k++)
        if(ans[tired[i].row][k] == 0) 
        {
            ans[tired[i].row][k] = tired[i].value;
            break;
        }
```

#### 题解2：我梦见一片焦土 (赞：1)
**星级：4星**
**关键亮点：**
- 通过排序和贪心策略解决问题，思路与题解1类似。
- 代码实现较为简洁，但可读性稍逊于题解1。

**核心代码：**
```cpp
sort(b,b+n*m,cmp);///small-->big
for(int i=0;i<n;i++)
{
    for(int j=0;j<m;j++)
    {
        if(b[j].x==i)
        cout<<b[j].num<<" ";///find the j column's minn value
        else cout<<a[i][c[i]++]<<" ";///大到小输出 
    }
    cout<<endl;
}
```

### 最优关键思路或技巧
- **贪心策略**：将前$m$小的路径长度分配给不同的跑步者，确保疲累值之和最小。
- **排序**：通过排序快速找到前$m$小的路径长度。

### 可拓展之处
- 类似问题可以扩展到其他需要分配资源以最小化某种代价的场景，如任务调度、资源分配等。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得
- **调试经历**：在实现过程中，确保前$m$小的路径长度被正确分配到不同的跑步者是关键，需要仔细检查代码逻辑。
- **顿悟感想**：通过贪心策略，可以有效地将问题简化，避免复杂的动态规划或搜索算法。

---
处理用时：35.28秒