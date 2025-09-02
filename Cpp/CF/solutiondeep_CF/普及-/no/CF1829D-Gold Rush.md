# 题目信息

# Gold Rush

## 题目描述

Initially you have a single pile with $ n $ gold nuggets. In an operation you can do the following:

- Take any pile and split it into two piles, so that one of the resulting piles has exactly twice as many gold nuggets as the other. (All piles should have an integer number of nuggets.)

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829D/7d414b1e40fe9f84ac7152f64f7f831c73043b5b.png)One possible move is to take a pile of size $ 6 $ and split it into piles of sizes $ 2 $ and $ 4 $ , which is valid since $ 4 $ is twice as large as $ 2 $ .

 Can you make a pile with exactly $ m $ gold nuggets using zero or more operations?

## 说明/提示

The first test case is pictured in the statement. We can make a pile of size $ 4 $ .

In the second test case, we can perform the following operations: $ \{\color{red}{9}\} \to \{\color{red}{6},3\} \to \{4,2,3\} $ . The pile that is split apart is colored red before each operation.

In the third test case, we can't perform a single operation.

In the fourth test case, we can't end up with a larger pile than we started with.

## 样例 #1

### 输入

```
11
6 4
9 4
4 2
18 27
27 4
27 2
27 10
1 1
3 1
5 1
746001 2984004```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
NO
NO```

# AI分析结果

### 题目内容中文重写
# 淘金热

## 题目描述
最初你有一堆包含 $n$ 个金块的金堆。在一次操作中，你可以进行以下操作：
- 选取任意一个金堆并将其分成两堆，使得其中一个新堆的金块数量恰好是另一个新堆的两倍。（所有金堆的金块数量都应为整数）

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829D/7d414b1e40fe9f84ac7152f64f7f831c73043b5b.png)一个可行的操作是选取一个大小为 $6$ 的金堆，将其分成大小为 $2$ 和 $4$ 的两堆，这是有效的，因为 $4$ 是 $2$ 的两倍。

你能否通过零次或多次操作得到一个恰好包含 $m$ 个金块的金堆？

## 说明/提示
第一个测试用例在题目描述中已给出图示。我们可以得到一个大小为 $4$ 的金堆。
在第二个测试用例中，我们可以进行以下操作：$\{\color{red}{9}\} \to \{\color{red}{6},3\} \to \{4,2,3\}$。每次操作前被拆分的金堆用红色标记。
在第三个测试用例中，我们无法进行任何操作。
在第四个测试用例中，我们最终得到的金堆大小不可能超过初始金堆大小。

## 样例 #1
### 输入
```
11
6 4
9 4
4 2
18 27
27 4
27 2
27 10
1 1
3 1
5 1
746001 2984004
```

### 输出
```
YES
YES
NO
NO
YES
YES
NO
YES
YES
NO
NO
```

### 算法分类
搜索

### 综合分析与结论
这些题解主要围绕能否通过特定操作从包含 $n$ 个金块的金堆得到包含 $m$ 个金块的金堆展开。思路主要分为搜索类（BFS、DFS）和数学分析类。
- **搜索类**：利用 BFS 或 DFS 模拟金堆的拆分过程，不断扩展状态，判断是否能达到目标状态 $m$。
- **数学分析类**：通过分析 $n$ 和 $m$ 的因子关系，判断是否可以通过去掉因子 $3$ 并适当添加因子 $2$ 使 $n$ 变为 $m$。

### 所选题解
- **作者：zhlzt (赞：11)，4星**
    - **关键亮点**：思路清晰，采用 BFS 模拟拆分过程，代码简洁易懂，复杂度分析明确。
- **作者：guanyf (赞：2)，4星**
    - **关键亮点**：DFS 代码实现简洁，使用三目运算符简化逻辑，还给出了拓展思路，将问题转化为数学等式进行分析。
- **作者：luqyou (赞：1)，4星**
    - **关键亮点**：从数学角度分析，通过统计 $n$ 和 $m$ 中 $2$ 和 $3$ 的因子数量来判断是否可行，逻辑严谨。

### 重点代码
#### zhlzt 的 BFS 代码
```cpp
bool bfs(int n,int m){
    queue<int>q;q.push(n);
    while(!q.empty()){
        int num=q.front();q.pop();
        if(num==m) return 1;
        if(num<m) continue;
        if(num%3==0) q.push(num/3),q.push(num/3*2);
    }
    return 0;
}
```
**核心实现思想**：使用队列存储待处理的金堆大小，不断从队列中取出元素，判断是否等于目标值 $m$，若小于 $m$ 则跳过，若为 $3$ 的倍数则将拆分后的两个金堆大小加入队列。

#### guanyf 的 DFS 代码
```cpp
bool dfs(int x) {
  return x == m ? 1 : (x % 3 || x < m ? 0 : dfs(x / 3) | dfs(x / 3 * 2));
}
```
**核心实现思想**：使用递归进行深度优先搜索，若当前值等于 $m$ 则返回 true，若不是 $3$ 的倍数或小于 $m$ 则返回 false，否则继续对拆分后的两个值进行递归搜索。

#### luqyou 的数学分析代码
```cpp
void solve(){
    int n,m,nsum2=0,nsum3=0,msum2=0,msum3=0;
    cin>>n>>m;
    if(n<m){
        cout<<"no"<<endl;
        return ;
    }
    if(n==m){
        cout<<"yes"<<endl;
        return ;
    }
    while(n%2==0){
        nsum2++;
        n/=2;
    } 
    while(n%3==0){
        nsum3++;
        n/=3;
    }
    while(m%2==0){
        msum2++;
        m/=2;
    }
    while(m%3==0){
        msum3++;
        m/=3;
    }
    if(n!=m){
        cout<<"no"<<endl;
        return ;
    }
    if(nsum3==0){
        cout<<"no"<<endl;
        return ;
    }
    if(nsum2>msum2){
        cout<<"no"<<endl;
        return ;
    }
    if(nsum3>=msum2-nsum2){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"no"<<endl;
    }
}
```
**核心实现思想**：统计 $n$ 和 $m$ 中 $2$ 和 $3$ 的因子数量，根据因子数量关系判断是否可以通过操作从 $n$ 得到 $m$。

### 最优关键思路或技巧
- **搜索类**：利用 BFS 或 DFS 模拟操作过程，通过队列或递归扩展状态，结合剪枝（如当前值小于目标值则跳过）提高效率。
- **数学分析类**：分析操作的数学本质，将问题转化为因子数量的比较，通过统计因子数量判断可行性。

### 拓展思路
同类型题或类似算法套路：
- 涉及状态转移和判断的问题，如倒水问题（通过不同容量的杯子倒水，判断能否得到特定容量的水），可使用 BFS 或 DFS 模拟操作过程。
- 与数论相关的问题，如判断一个数能否通过特定运算得到另一个数，可通过分析数的因子关系来解决。

### 推荐题目
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：考察搜索算法，通过搜索判断区域是否被包围。
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：经典的 BFS 问题，模拟马在棋盘上的移动。
- [P2392 kkksc03考前临时抱佛脚](https://www.luogu.com.cn/problem/P2392)：可使用搜索或动态规划解决，判断能否合理分配时间完成任务。

### 个人心得
部分题解提到朋友用推结论方法出错，提醒我们在解题时要谨慎推导结论，可先通过模拟或搜索等直观方法验证思路，确保正确性。同时，对于复杂问题，可从数学角度深入分析，挖掘问题的本质，找到更高效的解决方法。 

---
处理用时：46.95秒