# 题目信息

# Bus Video System

## 题目描述

The busses in Berland are equipped with a video surveillance system. The system records information about changes in the number of passengers in a bus after stops.

If $ x $ is the number of passengers in a bus just before the current bus stop and $ y $ is the number of passengers in the bus just after current bus stop, the system records the number $ y-x $ . So the system records show how number of passengers changed.

The test run was made for single bus and $ n $ bus stops. Thus, the system recorded the sequence of integers $ a_1, a_2, \dots, a_n $ (exactly one number for each bus stop), where $ a_i $ is the record for the bus stop $ i $ . The bus stops are numbered from $ 1 $ to $ n $ in chronological order.

Determine the number of possible ways how many people could be in the bus before the first bus stop, if the bus has a capacity equals to $ w $ (that is, at any time in the bus there should be from $ 0 $ to $ w $ passengers inclusive).

## 说明/提示

In the first example initially in the bus could be $ 0 $ , $ 1 $ or $ 2 $ passengers.

In the second example initially in the bus could be $ 1 $ , $ 2 $ , $ 3 $ or $ 4 $ passengers.

In the third example initially in the bus could be $ 0 $ or $ 1 $ passenger.

## 样例 #1

### 输入

```
3 5
2 1 -3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 4
-1 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4 10
2 4 1 2
```

### 输出

```
2
```

# AI分析结果

### 题目内容重写

**题目描述：**

Berland的公交车配备了视频监控系统。该系统记录了公交车在每站停车后乘客数量的变化。

如果在当前公交站之前公交车上有$x$名乘客，而在当前公交站之后公交车上有$y$名乘客，那么系统会记录下$y - x$的值。因此，系统记录的是乘客数量的变化。

在一次测试中，一辆公交车经过了$n$个公交站。因此，系统记录了一个整数序列$a_1, a_2, \dots, a_n$（每个公交站对应一个数字），其中$a_i$是第$i$个公交站的记录。公交站按时间顺序从$1$到$n$编号。

确定在第一个公交站之前，公交车上有多少种可能的乘客数量，假设公交车的容量为$w$（即任何时候公交车上的乘客数量都应该在$0$到$w$之间，包括$0$和$w$）。

**说明/提示：**

在第一个例子中，公交车最初可能有$0$、$1$或$2$名乘客。

在第二个例子中，公交车最初可能有$1$、$2$、$3$或$4$名乘客。

在第三个例子中，公交车最初可能有$0$或$1$名乘客。

**样例 #1：**

### 输入

```
3 5
2 1 -3
```

### 输出

```
3
```

**样例 #2：**

### 输入

```
2 4
-1 1
```

### 输出

```
4
```

**样例 #3：**

### 输入

```
4 10
2 4 1 2
```

### 输出

```
2
```

### 算法分类
模拟

### 题解分析与结论

这道题的核心在于通过模拟公交车的乘客数量变化，确定初始乘客数量的可能范围。所有题解都采用了类似的方法：通过遍历记录的变化，计算乘客数量的最大值和最小值，然后根据这些值来确定初始乘客数量的可能范围。

### 所选高分题解

#### 题解1：作者：「已注销」 (5星)

**关键亮点：**
- 简洁明了地通过遍历记录的变化，计算乘客数量的最大值和最小值。
- 使用`max(0LL, w - mx + mn + 1)`来计算可能的初始乘客数量，避免了复杂的逻辑判断。

**核心代码：**
```cpp
for(int i=1;i<=n;++i){
    cin>>a;
    s+=a;
    mx=max(mx,s);
    mn=min(mn,s);
}
cout<<max(0LL,w-mx+mn+1);
```

#### 题解2：作者：wuyixiang (4星)

**关键亮点：**
- 详细解释了如何通过最大值和最小值来确定初始乘客数量的范围。
- 代码中使用了`max(w - maxx + minn + 1,0LL)`，确保了结果的正确性。

**核心代码：**
```cpp
for(int i = 1;i <= n;i ++)
{
    cin >> a;
    num += a;
    maxx = max(maxx,num),minn = min(minn,num);
}
cout << max(w - maxx + minn + 1,0LL);
```

#### 题解3：作者：Fkxxx (4星)

**关键亮点：**
- 通过图示直观地解释了如何确定初始乘客数量的范围。
- 使用了`max((int)0 , w - maxx + minx + 1)`，确保了结果的正确性。

**核心代码：**
```cpp
for( int i = 1 ; i <= n ; i ++ ){
    int u ;
    cin >> u ;
    num += u ;
    maxx = max( maxx , num ) ;
    minx = min( minx , num ) ;
}
cout << max( (int)0 , w - maxx + minx + 1 ) ;
```

### 最优关键思路

通过遍历记录的变化，计算乘客数量的最大值和最小值，然后根据这些值来确定初始乘客数量的可能范围。最终的结果通过`max(0, w - max + min + 1)`来计算，确保结果的正确性。

### 可拓展之处

类似的问题可以通过模拟和计算极值来解决，例如在资源分配、时间调度等领域。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：29.38秒