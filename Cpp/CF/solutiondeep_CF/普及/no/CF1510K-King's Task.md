# 题目信息

# King's Task

## 题目描述

The brave Knight came to the King and asked permission to marry the princess. The King knew that the Knight was brave, but he also wanted to know if he was smart enough. So he asked him to solve the following task.

There is a permutation $ p_i $ of numbers from 1 to $ 2n $ . You can make two types of operations.

1. Swap $ p_1 $ and $ p_2 $ , $ p_3 $ and $ p_4 $ , ..., $ p_{2n-1} $ and $ p_{2n} $ .
2. Swap $ p_1 $ and $ p_{n+1} $ , $ p_2 $ and $ p_{n+2} $ , ..., $ p_{n} $ and $ p_{2n} $ .

The task is to find the minimal number of operations required to sort the given permutation.

The Knight was not that smart actually, but quite charming, so the princess asks you to help him to solve the King's task.

## 说明/提示

In the first example, you can sort the permutation in three operations:

1. Make operation 1: $ 3, 6, 5, 2, 1, 4 $ .
2. Make operation 2: $ 2, 1, 4, 3, 6, 5 $ .
3. Make operation 1: $ 1, 2, 3, 4, 5, 6 $ .

## 样例 #1

### 输入

```
3
6 3 2 5 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2
3 4 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
0```

# AI分析结果

### 题目内容重写
# 国王的任务

## 题目描述

勇敢的骑士来到国王面前，请求允许他迎娶公主。国王知道骑士很勇敢，但他还想确认骑士是否足够聪明。因此，国王给骑士布置了以下任务。

给定一个从1到$2n$的排列$p_i$，你可以进行两种操作：

1. 交换$p_1$和$p_2$，$p_3$和$p_4$，……，$p_{2n-1}$和$p_{2n}$。
2. 交换$p_1$和$p_{n+1}$，$p_2$和$p_{n+2}$，……，$p_n$和$p_{2n}$。

任务是找到将给定排列排序所需的最少操作次数。

骑士其实并不那么聪明，但他很有魅力，因此公主请你帮助他解决国王的任务。

## 说明/提示

在第一个样例中，你可以通过三次操作将排列排序：

1. 进行操作1：$3, 6, 5, 2, 1, 4$。
2. 进行操作2：$2, 1, 4, 3, 6, 5$。
3. 进行操作1：$1, 2, 3, 4, 5, 6$。

## 样例 #1

### 输入

```
3
6 3 2 5 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2
3 4 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
0```

### 算法分类
搜索

### 题解分析与结论
题目要求通过两种操作将排列排序，且需要找到最少的操作次数。由于操作类型有限，且操作顺序对结果有影响，因此可以通过搜索（如BFS或DFS）来枚举所有可能的操作序列，找到最短的排序路径。

### 所选高星题解
#### 题解1：作者：zsyzsy_2012 (赞：1)
- **星级**：4星
- **关键亮点**：通过交替执行两种操作，避免了重复操作，减少了搜索空间。代码清晰，逻辑简单，易于理解。
- **核心实现思想**：交替执行操作1和操作2，每次操作后检查是否已经排序，若排序则记录操作次数，最终取最小值。
- **代码片段**：
```cpp
int x = 1145141919, y = 1145141919, id = 1, s = 0;
while(!same(a , b) || !s) {
    s++;
    if(id) {
        for(int i = 1 ; i < 2 * n ; i += 2) {
            swap(b[i] , b[i + 1]) ;
        }
    }
    else {
        for(int i = 1 ; i <= n ; i++) {
            swap(b[i] , b[n + i]) ;
        }
    }
    id ^= 1 ;
    bool g = true ;
    for(int i = 1 ; i < 2 * n ; i++) {
        if(b[i] > b[i + 1]) {
            g = false ;
            break ;
        }
    }
    if(g) {
        x = s ;
        break ;
    }
}
```

#### 题解2：作者：xuan_gong_dong (赞：0)
- **星级**：4星
- **关键亮点**：使用DFS进行搜索，通过剪枝减少了不必要的搜索，提高了效率。代码简洁，逻辑清晰。
- **核心实现思想**：通过DFS枚举所有可能的操作序列，每次操作后检查是否已经排序，若排序则记录操作次数，最终取最小值。
- **代码片段**：
```cpp
void dfs(int step,int flag){
    if(step>n||step>=Min)
        return;
    if(check()){
        Min=min(Min,step);
        return;
    }
    if(flag){
        if(step&1){
            for(int i=1;i<=n;i++)
                swap(a[i],a[i+n]);
            dfs(step+1,flag);
            for(int i=1;i<=n;i++)
                swap(a[i],a[i+n]);
            return;				
        }
        for(int i=1;i<=n;i++)
            swap(a[i*2-1],a[i*2]);
        dfs(step+1,flag);
        for(int i=1;i<=n;i++)
            swap(a[i*2-1],a[i*2]);
    }
    else	{
        if((step&1)==0){
            for(int i=1;i<=n;i++)
                swap(a[i],a[i+n]);
            dfs(step+1,flag);
            for(int i=1;i<=n;i++)
                swap(a[i],a[i+n]);
            return;				
        }
        for(int i=1;i<=n;i++)
            swap(a[i*2-1],a[i*2]);
        dfs(step+1,flag);
        for(int i=1;i<=n;i++)
            swap(a[i*2-1],a[i*2]);
    }
}
```

### 最优关键思路或技巧
1. **交替执行操作**：通过交替执行两种操作，避免了重复操作，减少了搜索空间。
2. **剪枝**：在搜索过程中，通过剪枝减少不必要的搜索，提高效率。

### 可拓展之处
类似的问题可以通过搜索算法解决，尤其是当操作类型有限且操作顺序对结果有影响时。可以通过BFS或DFS枚举所有可能的操作序列，找到最短的解决方案。

### 推荐题目
1. [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)
2. [P1074 靶形数独](https://www.luogu.com.cn/problem/P1074)
3. [P1120 小木棍](https://www.luogu.com.cn/problem/P1120)

---
处理用时：40.55秒