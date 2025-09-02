# 题目信息

# Case of Fake Numbers

## 题目描述

Andrewid the Android is a galaxy-famous detective. He is now investigating a case of frauds who make fake copies of the famous Stolp's gears, puzzles that are as famous as the Rubik's cube once was.

Its most important components are a button and a line of $ n $ similar gears. Each gear has $ n $ teeth containing all numbers from $ 0 $ to $ n-1 $ in the counter-clockwise order. When you push a button, the first gear rotates clockwise, then the second gear rotates counter-clockwise, the the third gear rotates clockwise an so on.

Besides, each gear has exactly one active tooth. When a gear turns, a new active tooth is the one following after the current active tooth according to the direction of the rotation. For example, if $ n=5 $ , and the active tooth is the one containing number $ 0 $ , then clockwise rotation makes the tooth with number $ 1 $ active, or the counter-clockwise rotating makes the tooth number $ 4 $ active.

Andrewid remembers that the real puzzle has the following property: you can push the button multiple times in such a way that in the end the numbers on the active teeth of the gears from first to last form sequence $ 0,1,2,...,n-1 $ . Write a program that determines whether the given puzzle is real or fake.

## 说明/提示

In the first sample test when you push the button for the first time, the sequence of active teeth will be 2 2 1, when you push it for the second time, you get 0 1 2.

## 样例 #1

### 输入

```
3
1 0 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
4 2 1 4 3
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
4
0 2 3 1
```

### 输出

```
No
```

# AI分析结果

### 题目翻译
# 假数字事件

## 题目描述
安卓机器人安德鲁伊德是银河系著名的侦探。他目前正在调查一起欺诈案件，这些欺诈者制造著名的斯托尔普齿轮的假冒复制品。斯托尔普齿轮是一种谜题，曾经和魔方一样有名。

它最重要的组件是一个按钮和一排 $n$ 个相似的齿轮。每个齿轮有 $n$ 个齿，这些齿按逆时针顺序包含从 $0$ 到 $n - 1$ 的所有数字。当你按下按钮时，第一个齿轮顺时针旋转，然后第二个齿轮逆时针旋转，第三个齿轮又顺时针旋转，依此类推。

此外，每个齿轮都恰好有一个活动齿。当齿轮转动时，新的活动齿是根据旋转方向在当前活动齿之后的那个齿。例如，如果 $n = 5$，且活动齿是包含数字 $0$ 的那个齿，那么顺时针旋转会使数字 $1$ 所在的齿成为活动齿，而逆时针旋转会使数字 $4$ 所在的齿成为活动齿。

安德鲁伊德记得真正的谜题有以下特性：你可以多次按下按钮，最终使从第一个到最后一个齿轮的活动齿上的数字按顺序形成序列 $0, 1, 2, \cdots, n - 1$。编写一个程序来判断给定的谜题是真的还是假的。

## 说明/提示
在第一个样例测试中，当你第一次按下按钮时，活动齿的序列将是 2 2 1；当你第二次按下按钮时，你会得到 0 1 2。

## 样例 #1
### 输入
```
3
1 0 0
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
5
4 2 1 4 3
```
### 输出
```
Yes
```

## 样例 #3
### 输入
```
4
0 2 3 1
```
### 输出
```
No
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕模拟齿轮转动过程来判断是否能得到目标序列。大部分题解思路是通过第一个齿轮的转动步数来带动其他齿轮转动，同时注意奇偶齿轮转动方向不同。不同题解在实现方式上有所差异，有的采用直接计算，有的使用函数模拟转动，还有的进行暴力枚举。

### 所选题解
- **流绪（4星）**
    - **关键亮点**：思路清晰，通过定义转动函数 `turn` 模拟齿轮转动，代码结构良好，易于理解。
    - **核心代码**：
```cpp
bool turn(int i,int j,int s,int d)
{
    if(i%2==0)
        d*=-1;
    int p=(a[i]+s*d);
    if(p<0)
        p=n+p;
    else
        p%=n;
    if(p==j)
        return 1;
    return 0; 
}
```
核心实现思想：根据齿轮的奇偶性改变转动方向，计算转动后的齿的编号，判断是否等于目标值。
- **wang_freedom（4星）**
    - **关键亮点**：代码简洁，同样通过定义转动函数 `trn` 模拟齿轮转动，逻辑清晰。
    - **核心代码**：
```cpp
bool trn(int i,int j,int s,int d){
    if(i%2==0)
        d=-d;
    int p=a[i]+s*d;
    if(p<0)
        p+=n;
    else
        p%=n;
    if(p==j)
        return 1;
    return 0;
} 
```
核心实现思想：与流绪的题解类似，根据齿轮奇偶性改变方向，计算转动后的齿的编号并判断是否等于目标值。
- **andyli（4星）**
    - **关键亮点**：使用 Python 实现，通过预处理将所有 $a_i$ 变为 $(a_i - i) \bmod n$，简化判断条件，只需判断数组是否全为 $0$ 即可。
    - **核心代码**：
```python
n, *a = map(int, open(0).read().split())
for i in range(n):
    a[i] = (a[i] - i) % n
for _ in range(n):
    for i in range(n):
        if i % 2:
            a[i] += 1
        else:
            a[i] -= 1
        a[i] %= n
    if sum(a) == 0:
        exit(print('Yes'))
print('No')
```
核心实现思想：先对数组进行预处理，然后模拟每次按下按钮时齿轮的转动，判断数组元素和是否为 $0$。

### 最优关键思路或技巧
- 利用第一个齿轮的转动步数来带动其他齿轮转动，简化问题。
- 注意奇偶齿轮转动方向不同，通过取负来改变方向。
- 对数组进行预处理，将判断条件简化为判断数组是否全为 $0$。

### 可拓展之处
同类型题可能会改变齿轮的转动规则或目标序列，解题思路仍然是模拟转动过程，根据具体规则进行相应的计算和判断。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)：模拟乒乓球比赛过程。
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)：模拟多项式的输出过程。
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)：模拟字符串的展开规则。

### 个人心得
题解中未包含个人心得。

---
处理用时：30.28秒