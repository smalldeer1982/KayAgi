# 题目信息

# Pipes

## 题目描述

You are given a system of pipes. It consists of two rows, each row consists of $ n $ pipes. The top left pipe has the coordinates $ (1, 1) $ and the bottom right — $ (2, n) $ .

There are six types of pipes: two types of straight pipes and four types of curved pipes. Here are the examples of all six types:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/f58b589c4b7a5370d2912a5690db68318ac884a6.png) Types of pipes You can turn each of the given pipes $ 90 $ degrees clockwise or counterclockwise arbitrary (possibly, zero) number of times (so the types $ 1 $ and $ 2 $ can become each other and types $ 3, 4, 5, 6 $ can become each other).

You want to turn some pipes in a way that the water flow can start at $ (1, 0) $ (to the left of the top left pipe), move to the pipe at $ (1, 1) $ , flow somehow by connected pipes to the pipe at $ (2, n) $ and flow right to $ (2, n + 1) $ .

Pipes are connected if they are adjacent in the system and their ends are connected. Here are examples of connected pipes:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/c302dc3fb9fa832083fc1da665e39051a6975a62.png) Examples of connected pipes Let's describe the problem using some example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/af0d45bfd33558aed14bb2874c96920e8db881d3.png) The first example input And its solution is below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/108e6e3757d5df308ece8023b08c503aa013af65.png) The first example answer As you can see, the water flow is the poorly drawn blue line. To obtain the answer, we need to turn the pipe at $ (1, 2) $ $ 90 $ degrees clockwise, the pipe at $ (2, 3) $ $ 90 $ degrees, the pipe at $ (1, 6) $ $ 90 $ degrees, the pipe at $ (1, 7) $ $ 180 $ degrees and the pipe at $ (2, 7) $ $ 180 $ degrees. Then the flow of water can reach $ (2, n + 1) $ from $ (1, 0) $ .

You have to answer $ q $ independent queries.

## 说明/提示

The first query from the example is described in the problem statement.

## 样例 #1

### 输入

```
6
7
2323216
1615124
1
3
4
2
13
24
2
12
34
3
536
345
2
46
54
```

### 输出

```
YES
YES
YES
NO
YES
NO
```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由管道组成的系统。它由两行组成，每行有 $n$ 个管道。左上角的管道坐标为 $ (1, 1) $，右下角的管道坐标为 $ (2, n) $。

共有六种类型的管道：两种直管和四种弯管。以下是所有六种类型的示例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/f58b589c4b7a5370d2912a5690db68318ac884a6.png)

你可以将每个给定的管道顺时针或逆时针旋转 $90$ 度任意次数（包括零次），因此类型 $1$ 和 $2$ 可以互相转换，类型 $3, 4, 5, 6$ 也可以互相转换。

你希望通过旋转某些管道，使得水流可以从 $ (1, 0) $（左上角管道的左侧）开始，流入 $ (1, 1) $ 的管道，通过连接的管道流到 $ (2, n) $ 的管道，并最终流到 $ (2, n + 1) $。

如果两个管道在系统中相邻且它们的端口相连，则它们是连通的。以下是连通管道的示例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/c302dc3fb9fa832083fc1da665e39051a6975a62.png)

让我们通过一个例子来描述这个问题：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/af0d45bfd33558aed14bb2874c96920e8db881d3.png)

这是第一个示例输入，其解决方案如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/108e6e3757d5df308ece8023b08c503aa013af65.png)

如图所示，水流用蓝色的线表示。为了得到答案，我们需要将 $ (1, 2) $ 的管道顺时针旋转 $90$ 度，$ (2, 3) $ 的管道旋转 $90$ 度，$ (1, 6) $ 的管道旋转 $90$ 度，$ (1, 7) $ 的管道旋转 $180$ 度，$ (2, 7) $ 的管道旋转 $180$ 度。然后水流可以从 $ (1, 0) $ 流到 $ (2, n + 1) $。

你需要回答 $q$ 个独立的查询。

### 算法分类
模拟

### 题解分析与结论

该题的核心在于模拟水流的流动过程，通过旋转管道使得水流能够从起点流到终点。由于管道可以旋转，因此可以将管道类型简化为两种：直管和弯管。大多数题解都采用了模拟的方法，通过逐列检查管道的类型来决定水流的走向。

### 精选题解

#### 题解1：作者：pzc2004 (赞：6)
**星级：5星**
**关键亮点：**
- 将管道类型简化为两种，直管和弯管，大大简化了问题。
- 使用DFS模拟水流的流动过程，代码简洁且高效。
- 通过递归实现水流的流动，逻辑清晰。

**核心代码：**
```cpp
void dfs(int x, int y) {
    if(x==n && y==2 && a[x+n]==2){ans=1;return;}
    if(a[x+(y-1)*n]==2)dfs(x+1,y);
    if(a[x+(y-1)*n]>=3 && a[x+(y-1)*n]<=6) {
        if(y==1) {
            if(a[x+n]>=3 && a[x+n]<=6) {
                if(x==n){ans=1;return;}
                dfs(x+1,2);
            }
        } else {
            if(a[x]>=3 && a[x]<=6)dfs(x+1,1);
        }
    }
}
```

#### 题解2：作者：minVan (赞：2)
**星级：4星**
**关键亮点：**
- 从终点出发，逆向模拟水流的流动过程，思路独特。
- 通过递归实现水流的流动，逻辑清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
bool dfs(int x, int y, int nx, int ny) {
    if(x == 1 && y == 0) return 1;
    if(y == 0) return 0;
    if(s[x][y] <= '2') {
        if(x == nx) return dfs(x, y - 1, x, y);
        else return 0;
    } else {
        if(x == nx) return dfs(x % 2 + 1, y, x, y);
        else return dfs(x, y - 1, x, y);
    }
}
```

#### 题解3：作者：serverkiller (赞：1)
**星级：4星**
**关键亮点：**
- 直接模拟水流的流动过程，逐列检查管道类型。
- 通过状态变量记录当前所在行，逻辑清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
for (int i = 1; i <= n; i++) {
    if (state == 1) {
        if (a[state][i] == 1 || a[state][i] == 2) continue;
        else if (a[state+1][i] >= 3 && a[state+1][i] <= 6) {
            state = 2;
            continue;
        } else {
            flag = 0;
            break;
        }
    } else {
        if (a[state][i] == 1 || a[state][i] == 2) continue;
        else if (a[state-1][i] >= 3 && a[state-1][i] <= 6) {
            state = 1;
            continue;
        } else {
            flag = 0;
            break;
        }
    }
}
```

### 最优关键思路
将管道类型简化为直管和弯管，通过模拟水流的流动过程，逐列检查管道类型来决定水流的走向。这种方法大大简化了问题，使得代码更加简洁高效。

### 拓展思路
类似的问题可以通过将复杂问题简化，找到问题的核心规律，然后通过模拟或递归等方法来解决。例如，迷宫问题、路径规划问题等都可以采用类似的思路。

### 推荐题目
1. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

---
处理用时：45.43秒