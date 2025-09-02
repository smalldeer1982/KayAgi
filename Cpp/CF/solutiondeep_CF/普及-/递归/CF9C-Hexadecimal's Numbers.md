# 题目信息

# Hexadecimal's Numbers

## 题目描述

One beautiful July morning a terrible thing happened in Mainframe: a mean virus Megabyte somehow got access to the memory of his not less mean sister Hexadecimal. He loaded there a huge amount of $ n $ different natural numbers from 1 to $ n $ to obtain total control over her energy.

But his plan failed. The reason for this was very simple: Hexadecimal didn't perceive any information, apart from numbers written in binary format. This means that if a number in a decimal representation contained characters apart from 0 and 1, it was not stored in the memory. Now Megabyte wants to know, how many numbers were loaded successfully.

## 说明/提示

For $ n $ = 10 the answer includes numbers 1 and 10.

## 样例 #1

### 输入

```
10
```

### 输出

```
2```

# AI分析结果

### 题目中文重写
# 十六进制的数字

## 题目描述
在一个美好的七月早晨，主机世界发生了一件可怕的事情：邪恶的病毒梅加比特不知怎么地获取了他同样邪恶的妹妹十六进制的内存访问权限。他在那里加载了大量从 1 到 $n$ 的不同自然数，试图完全控制她的能量。

但他的计划失败了。原因很简单：十六进制只能处理以二进制格式书写的数字。这意味着，如果一个十进制表示的数字中包含除 0 和 1 之外的字符，它就不会被存储在内存中。现在梅加比特想知道，成功加载了多少个数字。

## 说明/提示
当 $n = 10$ 时，答案包括数字 1 和 10。

## 样例 #1
### 输入
```
10
```
### 输出
```
2
```

### 综合分析与结论
这些题解的核心目标都是找出 1 到 $n$ 中各数位只包含 0 和 1 的数的个数，主要思路和方法可归纳如下：
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|char32_t|递归生成二进制型数；打表法|递归函数生成 $n*10$ 或 $n*10 + 1$ 形式的数；提前存储 $10^9$ 内二进制型数|避免生成超出范围的数|4星|
|test_check|深度优先搜索（DFS）|从 1 开始递归搜索，每次递归生成 $cur*10$ 和 $cur*10 + 1$ 的数|确定递归边界|4星|
|damage|枚举、DFS、公式计算|枚举每个数并判断；DFS 排除无用决策；根据数字位信息和 2 的幂计算答案|优化枚举复杂度；处理 DFS 爆栈问题|3星|
|BBD186587|十重循环暴力判断|循环生成所有可能的数并判断是否在区间内|减少不必要的计算|2星|
|HiroshiRealm|队列存储|用队列存储满足条件的数，队头用于生成新数和判断|队列的使用和边界判断|3星|
|lixiao189|递归构造和公式计算|递归生成答案；找出最大二进制型数并用 2 的幂更新答案|找出最大二进制型数和理解公式原理|3星|
|Loser_King|DFS 和 BFS|DFS 递归生成数；BFS 用优先队列存储和扩展数|处理 BFS 队列元素类型和边界|3星|
|北雪2009|递归|思路同 DFS，但未给出代码|无|1星|
|shenzuxin|九重循环枚举|循环生成所有可能的数并统计|减少循环次数|2星|
|LevenKoko|DFS|从 0 开始 DFS，排除特殊情况|处理特殊情况|3星|
|Andysun06|打表法|存储 $10^9$ 内二进制型数并查找|处理特殊测试点|3星|

### 所选题解
- **char32_t（4星）**
    - 关键亮点：思路清晰，提供递归和打表两种方法，代码简洁易懂。
    - 核心代码：
```cpp
// 递归方法
int binary(int m) {
    if(m > n) return 0;
    else count++;
    binary(m * 10);
    binary(m * 10 + 1);
}
```
    - 核心实现思想：递归生成 $n*10$ 或 $n*10 + 1$ 形式的数，若数不超过 $n$ 则计数器加 1。
- **test_check（4星）**
    - 关键亮点：详细解释 DFS 思路，代码规范。
    - 核心代码：
```cpp
void dfs(int cur) {
    if(cur > n) return;
    else ++ans;
    dfs(cur * 10 + 1);
    dfs(cur * 10);
}
```
    - 核心实现思想：从 1 开始 DFS，每次递归生成 $cur*10$ 和 $cur*10 + 1$ 的数，若数不超过 $n$ 则计数器加 1。

### 最优关键思路或技巧
- 利用递归或 DFS 生成符合条件的数，避免枚举所有数，降低时间复杂度。
- 打表法适用于数据范围固定的情况，可直接查找答案，提高效率。

### 可拓展之处
同类型题可涉及不同进制、不同数位限制的数字统计问题，类似算法套路有 BFS、递归、打表等。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：考察递归和组合枚举。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：考察 BFS 或 DFS 的应用。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：考察回溯算法，与递归思路相关。

### 个人心得摘录与总结
- **HiroshiRealm**：受测试点超时困扰，决定采用队列方法，借鉴超级素数做法，用队列存储满足条件的数。
- **Andysun06**：指出第 15 个测试点有坑，采用打表法并对特殊情况进行处理。 

---
处理用时：38.68秒