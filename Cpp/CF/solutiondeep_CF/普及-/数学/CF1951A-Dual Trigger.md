# 题目信息

# Dual Trigger

## 题目描述

[Ngọt - LẦN CUỐI (đi bên em xót xa người ơi)](https://youtu.be/kSjj0LlsqnI)

ඞ



There are $ n $ lamps numbered $ 1 $ to $ n $ lined up in a row, initially turned off. You can perform the following operation any number of times (possibly zero):

- Choose two non-adjacent $ {}^\dagger $ lamps that are currently turned off, then turn them on.

Determine whether you can reach configuration $ s $ , where $ s_i = 1 $ means the $ i $ -th lamp is turned on, and $ s_i = 0 $ otherwise.

 $ {}^\dagger $ Only lamp $ i $ and $ i + 1 $ are adjacent for all $ 1 \le i < n $ . Note that lamp $ n $ and $ 1 $ are not adjacent when $ n \ne 2 $ .

## 说明/提示

In the first test case, the sequence of operation could have been as follows (note that initially $ s $ is all zero): $ \mathtt{0000000000} \to \mathtt{\color{red}{1}0000000\color{red}{1}0} \to \mathtt{1\color{red}{1}00000\color{red}{1}10} \to \mathtt{110\color{red}{1}0\color{red}{1}0110} $ .

In the third test case, we don't have to do any operation.

In the fourth test case, we cannot do any operation, but we need the first lamp to be on. Therefore, it is impossible to achieve the desired state.

## 样例 #1

### 输入

```
5
10
1101010110
10
1001001110
6
000000
1
1
12
111111111111```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容重写
# 双触发

## 题目描述

有 $n$ 个编号为 $1$ 到 $n$ 的灯排成一排，初始状态为关闭。你可以进行以下操作任意次（包括零次）：

- 选择两个不相邻的关闭的灯，将它们打开。

判断是否可以通过这些操作达到目标状态 $s$，其中 $s_i = 1$ 表示第 $i$ 个灯是打开的，$s_i = 0$ 表示关闭。

 $ {}^\dagger $ 对于所有 $1 \le i < n$，只有灯 $i$ 和 $i + 1$ 是相邻的。注意当 $n \ne 2$ 时，灯 $n$ 和 $1$ 不相邻。

## 说明/提示

在第一个测试用例中，操作序列可能如下（注意初始状态 $s$ 全为 0）：$ \mathtt{0000000000} \to \mathtt{\color{red}{1}0000000\color{red}{1}0} \to \mathtt{1\color{red}{1}00000\color{red}{1}10} \to \mathtt{110\color{red}{1}0\color{red}{1}0110} $ 。

在第三个测试用例中，不需要进行任何操作。

在第四个测试用例中，无法进行任何操作，但需要第一个灯是打开的。因此，无法达到目标状态。

## 样例 #1

### 输入

```
5
10
1101010110
10
1001001110
6
000000
1
1
12
111111111111```

### 输出

```
YES
NO
YES
NO
YES```

### 题解分析与结论

#### 综合分析
题目要求通过每次操作打开两个不相邻的关闭的灯，判断是否可以达到目标状态。所有题解都基于以下两个关键点：
1. **奇数个打开的灯无法实现**：因为每次操作只能打开偶数个灯，奇数个打开的灯无法通过偶数次操作实现。
2. **特殊情况**：当只有两个灯打开且它们相邻时，无法通过操作实现，因为操作要求选择不相邻的灯。

#### 最优思路与技巧
- **奇偶性判断**：首先判断目标状态中打开的灯的数量是否为偶数，如果不是，直接输出 `NO`。
- **相邻灯的特判**：如果打开的灯的数量为 2，且这两个灯相邻，则输出 `NO`，否则输出 `YES`。

#### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察模拟和条件判断。
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：考察递归和动态规划。
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：考察组合和回溯。

### 所选高分题解

#### 题解1：作者 baokun (5星)
**关键亮点**：
- 简洁明了地分析了奇偶性和特殊情况。
- 代码清晰，逻辑严谨。

**核心代码**：
```cpp
int num=0;
bool flag=0;
for(int i=0;i<n;i++){
    if(s[i]=='1')num++;
    if(s[i]=='1'&&s[i-1]=='1')flag=1;
}
if(num&1||(flag&&num==2)){
    cout<<"NO"<<endl;
    continue;
}cout<<"YES"<<endl;
```

#### 题解2：作者 Kindershiuo (4星)
**关键亮点**：
- 详细解释了奇偶性和特殊情况。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
if(ma['1'] == 2) {
    int t1 = s.find('1');
    int t2 = s.find('1', t1 + 1);
    if(t2 - t1 == 1)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
} else if(ma['1'] % 2 != 0)
    cout << "NO" << endl;
else {
    cout << "YES" << endl;
}
```

#### 题解3：作者 fengyuxuan (4星)
**关键亮点**：
- 简洁明了地分析了奇偶性和特殊情况。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
if(sum%2==1||(sum==2&&a[2]-a[1]==1))
    cout<<"No"<<endl;
else
    cout<<"Yes"<<endl;
```

### 总结
最优思路是通过奇偶性判断和相邻灯的特判来解决问题。代码实现简洁，逻辑清晰，适合初学者理解和应用。

---
处理用时：36.41秒