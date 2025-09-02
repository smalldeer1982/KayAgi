# 题目信息

# Vessels

## 题目描述

There is a system of $ n $ vessels arranged one above the other as shown in the figure below. Assume that the vessels are numbered from 1 to $ n $ , in the order from the highest to the lowest, the volume of the $ i $ -th vessel is $ a_{i} $ liters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371D/f198564e53bb2ea5c99e17b823930a432879118f.png)Initially, all the vessels are empty. In some vessels water is poured. All the water that overflows from the $ i $ -th vessel goes to the $ (i+1) $ -th one. The liquid that overflows from the $ n $ -th vessel spills on the floor.

Your task is to simulate pouring water into the vessels. To do this, you will need to handle two types of queries:

1. Add $ x_{i} $ liters of water to the $ p_{i} $ -th vessel;
2. Print the number of liters of water in the $ k_{i} $ -th vessel.

When you reply to the second request you can assume that all the water poured up to this point, has already overflown between the vessels.

## 样例 #1

### 输入

```
2
5 10
6
1 1 4
2 1
1 2 5
1 1 4
2 1
2 2
```

### 输出

```
4
5
8
```

## 样例 #2

### 输入

```
3
5 10 8
6
1 1 12
2 2
1 1 6
1 3 2
2 2
2 3
```

### 输出

```
7
10
5
```

# AI分析结果

### 题目翻译
有一个由 $n$ 个容器从上到下排列组成的系统，如下图所示。假设容器从 1 到 $n$ 编号，顺序是从最高到最低，第 $i$ 个容器的容量是 $a_{i}$ 升。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371D/f198564e53bb2ea5c99e17b823930a432879118f.png)

最初，所有容器都是空的。向某些容器中倒水，从第 $i$ 个容器溢出的所有水都会流入第 $(i + 1)$ 个容器。从第 $n$ 个容器溢出的水会流到地上。

你的任务是模拟向容器中倒水的过程。为此，你需要处理两种类型的查询：
1. 向第 $p_{i}$ 个容器中加入 $x_{i}$ 升水；
2. 输出第 $k_{i}$ 个容器中的水量。

当你回复第二个请求时，可以假设到此时为止倒入的所有水都已经在容器之间溢出完毕。

### 综合分析与结论
这些题解主要围绕如何高效模拟向容器倒水的过程展开，核心在于优化暴力模拟中处理水溢出时的时间复杂度。大部分题解采用并查集的方法，也有使用链表模拟和线段树的做法。

|题解作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|sto_5k_orz|用并查集跳过已装满的容器，每次一个容器装满就把上一个容器直接连到下一个|并查集路径压缩，每次操作时更新并查集连接关系|避免重复检查已装满的容器，降低时间复杂度|4星|
|b6e0_|用并查集，$x$ 的祖先是 $y$ 表示 $x$ 后第一个没有被倒满的节点是 $y + 1$，倒满后更新祖先关系|并查集查找和合并操作，在倒水过程中更新祖先|快速定位下一个未装满的容器|4星|
|SunnyYuan|定义权值并查集，权值保存集合还能存下多少水，装不下就合并集合|并查集合并和查找，根据权值判断是否合并|处理水溢出时集合的合并|3星|
|zt17|建立数组存储每个沙漏下面第一个非空的沙漏的位置，直接将水加到该位置|数组模拟链表，更新数组指向关系|减少水溢出时的搜索次数|3星|
|Lijunzhuo|用并查集维护沙漏中水溢出时漏到的最终位置，溢出时递归处理|并查集和递归调用，更新溢出位置|处理连续溢出的情况|3星|
|TheShuMo|用并查集使每个 $x$ 的父亲是它下面第一个没装满水的沙漏|并查集查找和路径压缩，倒水时更新父亲关系|快速找到下一个可倒水的沙漏|4星|
|scc36|纯模拟链表，用数组存储数值、“大哥”和“小弟”，满了就更新关系|数组模拟链表操作，更新链表连接|模拟链表操作避免使用指针|2星|
|OIer_ACMer|用并查集合并注满水的盘子，对 $k$ 操作就是对大于等于 $k$ 的盘子操作|并查集查找和合并，判断水溢出情况|处理盘子合并和水溢出|3星|
|MuYC|线段树支持区间覆盖、单点修改、区间查询、单点查询；链表存下一个未装满的水桶|线段树操作和链表更新，二分查找可注满的沙漏区间|维护水一直向下流的过程|3星|
|Kirisame_Marisa_|维护每个容器下方第一个没满的容器 $nxt_i$，溢出时递归更新|数组维护和递归调用，分析 $nxt$ 数组性质|优化暴力遍历容器的时间复杂度|3星|

### 所选题解
- **sto_5k_orz（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用并查集跳过已装满的容器，有效降低时间复杂度。
    - **核心代码**：
```cpp
int find(int x){return nxt[x] == x? x : nxt[x] = find(nxt[x]);}
void add(int x)
{
    int y = read();
    water[x] += y;
    while(x <= n && water[x] > a[x])
    {
        nxt[find(x - 1)] = find(x);
        int i = find(x) + 1;
        water[i] += water[x] - a[x];
        water[x] = a[x];
        x = i;
    }
}
```
核心思想是使用并查集的路径压缩优化，当一个容器装满时，将其前一个容器的并查集祖先指向该容器的下一个容器，从而跳过已装满的容器。

- **b6e0_（4星）**
    - **关键亮点**：详细分析了复杂度，通过并查集将时间复杂度优化到 $O(m + n)$，代码逻辑清晰。
    - **核心代码**：
```cpp
int get(int x)
{
    if(fa[x]!= x)
        return fa[x]=get(fa[x]);
    return x;
}
while(m--)
{
    o = read();
    x = read();
    if(o - 1)
        printf("%d\n",ans[x]);
    else
    {
        ans[x] += read();
        while(x <= n && ans[x] > a[x])
        {
            fa[get(x - 1)] = get(x);
            o = get(x) + 1;
            ans[o] += ans[x] - a[x];
            ans[x] = a[x];
            x = o;
        }
    }
}
```
核心思想是通过并查集的查找和合并操作，在倒水过程中不断更新祖先关系，快速定位下一个未装满的容器。

- **TheShuMo（4星）**
    - **关键亮点**：使用并查集维护每个沙漏下方第一个没装满水的沙漏，代码实现简洁。
    - **核心代码**：
```cpp
int find(int x){
    if(fa[x]!= x) return fa[x] = find(fa[x]);
    return x;
}
void adw(int x){
    int k = read();
    zl[x] += k;
    for(;x <= n && zl[x] > a[x];){
        fa[find(x - 1)] = find(x);
        int nxt = find(x) + 1;
        zl[nxt] += zl[x] - a[x];
        zl[x] = a[x];
        x = nxt;
    }
}
```
核心思想是利用并查集的查找和路径压缩，在倒水时快速找到下一个可倒水的沙漏，并更新并查集关系。

### 最优关键思路或技巧
使用并查集来跳过已装满的容器，避免重复检查，将时间复杂度从暴力模拟的 $O(n^2)$ 优化到 $O(m + n)$。

### 拓展思路
同类型题可以是涉及容器倒水、资源分配且有溢出情况的问题，类似算法套路是使用并查集、链表等数据结构优化暴力模拟的时间复杂度。

### 推荐题目
1. [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：并查集的经典应用，涉及集合合并和元素距离查询。
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：并查集的基础模板题，可用于巩固并查集的基本操作。
3. [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：简单的并查集应用，判断元素是否属于同一集合。

### 个人心得摘录与总结
- **OIer_ACMer**：尝试用链表做此题在外网 TLE 了 8 个点，得出链表不是万能的结论，提醒在选择算法和数据结构时要谨慎。
- **MuYC**：做此题时一开始没思考直接用线段树做，后来发现可以用链表做到复杂度 $O(n)$ 级别，强调做题要动脑子思考，避免一上来就用暴力方法。 

---
处理用时：50.18秒