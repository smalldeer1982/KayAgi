# 题目信息

# Balanced Tunnel

## 题目描述

Consider a tunnel on a one-way road. During a particular day, $ n $ cars numbered from $ 1 $ to $ n $ entered and exited the tunnel exactly once. All the cars passed through the tunnel at constant speeds.

A traffic enforcement camera is mounted at the tunnel entrance. Another traffic enforcement camera is mounted at the tunnel exit. Perfectly balanced.

Thanks to the cameras, the order in which the cars entered and exited the tunnel is known. No two cars entered or exited at the same time.

Traffic regulations prohibit overtaking inside the tunnel. If car $ i $ overtakes any other car $ j $ inside the tunnel, car $ i $ must be fined. However, each car can be fined at most once.

Formally, let's say that car $ i $ definitely overtook car $ j $ if car $ i $ entered the tunnel later than car $ j $ and exited the tunnel earlier than car $ j $ . Then, car $ i $ must be fined if and only if it definitely overtook at least one other car.

Find the number of cars that must be fined.

## 说明/提示

The first example is depicted below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237B/7d2f6b4d3eea560d8fb835871b9aa0fd74a81766.png)

Car $ 2 $ definitely overtook car $ 5 $ , while car $ 4 $ definitely overtook cars $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ . Cars $ 2 $ and $ 4 $ must be fined.

In the second example car $ 5 $ was definitely overtaken by all other cars.

In the third example no car must be fined.

## 样例 #1

### 输入

```
5
3 5 2 1 4
4 3 2 5 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
5 2 3 6 7 1 4
2 3 6 7 1 4 5
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2
1 2
1 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 平衡隧道

##### 题目描述

考虑一条单向道路上的隧道。在某一天，编号从 $1$ 到 $n$ 的 $n$ 辆车依次进入并离开隧道，每辆车恰好进出一次。所有车辆以恒定速度通过隧道。

隧道入口处安装了一个交通监控摄像头，隧道出口处也安装了一个摄像头。完美平衡。

由于摄像头的存在，车辆进入和离开隧道的顺序是已知的。没有两辆车同时进入或离开隧道。

交通规则禁止在隧道内超车。如果车辆 $i$ 在隧道内超车了任何其他车辆 $j$，车辆 $i$ 必须被罚款。然而，每辆车最多只能被罚款一次。

正式地，如果车辆 $i$ 进入隧道的时间晚于车辆 $j$，并且离开隧道的时间早于车辆 $j$，那么我们说车辆 $i$ 肯定超车了车辆 $j$。那么，车辆 $i$ 必须被罚款当且仅当它肯定超车了至少一辆其他车辆。

请找出必须被罚款的车辆数量。

##### 说明/提示

第一个示例如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237B/7d2f6b4d3eea560d8fb835871b9aa0fd74a81766.png)

车辆 $2$ 肯定超车了车辆 $5$，而车辆 $4$ 肯定超车了车辆 $1$、$2$、$3$ 和 $5$。因此，车辆 $2$ 和 $4$ 必须被罚款。

在第二个示例中，车辆 $5$ 被所有其他车辆超车。

在第三个示例中，没有车辆需要被罚款。

##### 样例 #1

###### 输入

```
5
3 5 2 1 4
4 3 2 5 1
```

###### 输出

```
2
```

##### 样例 #2

###### 输入

```
7
5 2 3 6 7 1 4
2 3 6 7 1 4 5
```

###### 输出

```
6
```

##### 样例 #3

###### 输入

```
2
1 2
1 2
```

###### 输出

```
0
```

### 算法分类
排序

### 题解分析与结论

本题的核心在于判断车辆是否在隧道内超车。具体来说，如果车辆 $i$ 进入隧道的时间晚于车辆 $j$，并且离开隧道的时间早于车辆 $j$，则车辆 $i$ 必须被罚款。我们可以通过将车辆的进入和离开顺序进行映射，然后通过遍历来判断是否存在超车行为。

### 所选题解

#### 题解1：作者：HHYQ_07 (赞：5)

**星级：5星**

**关键亮点：**
- 通过倒序记录车辆的离开顺序，简化了问题的复杂度。
- 使用线性时间复杂度 $O(n)$ 解决了问题，优于其他 $O(n \log n)$ 的解法。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++)
{
    cin>>x;
    b[x]=i;
}
for(int i=1;i<=n;i++)
{
    cin>>x;
    a[n-i+1]=b[x];
}	
sum=a[1];
for(int i=2;i<=n;i++)
{
    if(sum<a[i])ans++;
    sum=min(sum,a[i]);
}
cout<<ans;
```

**实现思想：**
- 首先记录每辆车进入隧道的顺序。
- 然后倒序记录每辆车离开隧道的顺序。
- 遍历离开顺序，维护一个最小值，如果当前值大于最小值，则说明存在超车行为。

#### 题解2：作者：WsW_ (赞：4)

**星级：4星**

**关键亮点：**
- 通过队列模拟车辆的进出顺序，直观地判断超车行为。
- 使用标记数组记录已经离开隧道的车辆，避免重复计算。
- 代码逻辑清晰，易于实现。

**核心代码：**
```cpp
while(t[en[j]])j++;
if(ex[i]!=en[j]){
    sum++;
    t[ex[i]]=1;
}
else j++;
```

**实现思想：**
- 使用队列模拟车辆的进入顺序。
- 遍历离开顺序，如果离开的车辆不是队列头部的车辆，则说明存在超车行为。
- 使用标记数组记录已经离开隧道的车辆，避免重复计算。

#### 题解3：作者：kexinluo (赞：0)

**星级：4星**

**关键亮点：**
- 通过映射车辆的进入顺序，简化了问题的复杂度。
- 使用递推的方法计算最小值，优化了时间复杂度。
- 代码逻辑清晰，易于理解。

**核心代码：**
```cpp
f[n] = b[n];
for (int i=n-1; i>=1; i--)
{
    f[i] = min(f[i+1], b[i]);
}
int ans = 0;
for (int i=1; i<n; i++)
{
    if (b[i] > f[i+1]) ans ++;
}
```

**实现思想：**
- 首先映射车辆的进入顺序。
- 然后计算从当前位置到末尾的最小值。
- 遍历离开顺序，如果当前值大于最小值，则说明存在超车行为。

### 最优关键思路或技巧
- **倒序记录**：通过倒序记录车辆的离开顺序，可以简化问题的复杂度，使得问题可以在线性时间内解决。
- **最小值维护**：在遍历过程中维护一个最小值，可以快速判断是否存在超车行为。
- **队列模拟**：使用队列模拟车辆的进出顺序，可以直观地判断超车行为。

### 可拓展之处
- 类似的问题可以扩展到其他场景，如判断任务的执行顺序、事件的依赖关系等。
- 可以使用类似的方法解决其他排序相关的问题，如逆序对的计算、区间覆盖问题等。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3382 线段树 1](https://www.luogu.com.cn/problem/P3382)

### 个人心得
- **调试经历**：在实现过程中，需要注意边界条件的处理，如最小值初始化的位置和遍历的起始点。
- **踩坑教训**：在倒序记录时，容易忽略数组的索引问题，导致结果错误。
- **顿悟感想**：通过倒序记录和最小值维护，可以大大简化问题的复杂度，使得问题可以在线性时间内解决。

---
处理用时：45.39秒