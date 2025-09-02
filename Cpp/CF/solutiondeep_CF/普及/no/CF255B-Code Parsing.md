# 题目信息

# Code Parsing

## 题目描述

Little Vitaly loves different algorithms. Today he has invented a new algorithm just for you. Vitaly's algorithm works with string $ s $ , consisting of characters "x" and "y", and uses two following operations at runtime:

1. Find two consecutive characters in the string, such that the first of them equals "y", and the second one equals "x" and swap them. If there are several suitable pairs of characters, we choose the pair of characters that is located closer to the beginning of the string.
2. Find in the string two consecutive characters, such that the first of them equals "x" and the second one equals "y". Remove these characters from the string. If there are several suitable pairs of characters, we choose the pair of characters that is located closer to the beginning of the string.

The input for the new algorithm is string $ s $ , and the algorithm works as follows:

1. If you can apply at least one of the described operations to the string, go to step 2 of the algorithm. Otherwise, stop executing the algorithm and print the current string.
2. If you can apply operation 1, then apply it. Otherwise, apply operation 2. After you apply the operation, go to step 1 of the algorithm.

Now Vitaly wonders, what is going to be printed as the result of the algorithm's work, if the input receives string $ s $ .

## 说明/提示

In the first test the algorithm will end after the first step of the algorithm, as it is impossible to apply any operation. Thus, the string won't change.

In the second test the transformation will be like this:

1. string "yxyxy" transforms into string "xyyxy";
2. string "xyyxy" transforms into string "xyxyy";
3. string "xyxyy" transforms into string "xxyyy";
4. string "xxyyy" transforms into string "xyy";
5. string "xyy" transforms into string "y".

As a result, we've got string "y".

In the third test case only one transformation will take place: string "xxxxxy" transforms into string "xxxx". Thus, the answer will be string "xxxx".

## 样例 #1

### 输入

```
x
```

### 输出

```
x
```

## 样例 #2

### 输入

```
yxyxy
```

### 输出

```
y
```

## 样例 #3

### 输入

```
xxxxxy
```

### 输出

```
xxxx
```

# AI分析结果



# 中文题目重写

## 题目描述

小Vitaly喜欢各种算法。今天他发明了一个新算法。该算法处理由字符"x"和"y"组成的字符串$s$，运行时使用两种操作：

1. 找到相邻的"yx"字符对，交换为"xy"，优先处理最左边的匹配对
2. 找到相邻的"xy"字符对直接删除，优先处理最左边的匹配对

算法流程：
1. 只要可以进行操作1或2就继续执行
2. 优先执行操作1，若不能则执行操作2
3. 重复上述步骤直到无法操作

给定初始字符串$s$，求最终输出的字符串。

## 输入输出样例
样例1输入x输出x；样例2输入yxyxy输出y；样例3输入xxxxxy输出xxxx

# 算法分类
数学

# 题解综合分析

各题解核心思路：通过观察操作规律，发现最终结果只与字符数量差有关，无需模拟操作过程。所有成对x和y都会被消除，剩余字符由数量差决定。

**关键结论**：  
`result = 数量较多的字符重复 |x_count - y_count| 次`

# 精选题解

## 1. 作者：liupan2010（⭐⭐⭐⭐⭐）
**亮点**：  
- 代码极简（仅7行），利用STL的count函数  
- 直接数学推导，时间复杂度O(n)  
**核心代码**：
```cpp
int x=count(str.begin(),str.end(),'x'), y=...;
for(i=1;i<=abs(x-y);i++) printf("%c",(x>y)?'x':'y');
```

## 2. 作者：WA_sir（⭐⭐⭐⭐）
**亮点**：  
- 输入时即时统计，减少空间占用  
- 三目运算符与循环条件优化  
**核心代码**：
```cpp
while(cin>>z)z-'y'?x++:y++; //边读边统计
z=x>y?'x':'y'; //确定输出字符
while(x--)cout<<z; //循环输出
```

## 3. 作者：yzm0325（⭐⭐⭐⭐）
**亮点**：  
- Python实现仅7行，展示跨语言解法  
- 利用字符串乘法特性简化输出  
**核心代码**：
```python
print('x'*(x-y) if x>y else 'y'*(y-x)) # 利用字符串乘法
```

# 关键思路总结
**核心技巧**：  
通过数学分析将问题转化为字符统计问题，避免复杂模拟。该问题的本质是每次操作等价于消除一对x和y，最终剩余字符由数量差决定。

**同类拓展**：  
类似"括号消除"问题中，可以通过统计左右括号数量差判断是否合法。例如：P1739 表达式括号匹配。

# 推荐练习题
1. CF266B（队列模拟）  
2. P1106 删数问题（贪心选择）  
3. P1321 单词覆盖（字符串处理）

---
处理用时：50.04秒