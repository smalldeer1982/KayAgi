# 题目信息

# Lock

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-china-open/tasks/code_festival_china_a



## 说明/提示

### Problem

Alice has a box locked with $ n $ digits dial lock. Each dial of the lock can be set to a digit from $ 0 $ to $ 9 $. Unfortunately, she forgot the passcode (of $ n $ digits). Now she will try all possible combinations of digits to unlock the key.

She can do one of the following procedure each time.

- Choose $ 1 $ dial and add $ 1 $ to that digit. (If the digit chosen was $ 9 $, it will be $ 0 $).
- Choose $ 1 $ dial and subtract $ 1 $ from that digit. (If the digit chosen was $ 0 $, it will be $ 9 $).

Curiously, she wants to try all combinations even if she found the correct passcode during the trials. But it is a hard work to try all the $ 10^n $ combinations. Help her by showing the way how to make the procedure less as possible.

Initially, the combination of digits of the lock is set to $ 00..0 $.

Calculate $ m $, the minimum number of procedures to try all combinations of digits, and show the $ m+1 $ combinations of digits after each procedures, including the initial combination $ 00..0 $. If there are more than one possible answer, you may choose any one of them.

Checking if the current combination of digits matches the passcode doesn't count as a procedure.

### Sample Explanation 1

Don't forget to output the minimum number of procedures $ 9 $ on the first line. On the following lines, note that you have to output $ m+1 $ lines including the initial combination $ 0 $.

## 样例 #1

### 输入

```
1```

### 输出

```
9

0

1

2

3

4

5

6

7

8

9```

## 样例 #2

### 输入

```
2```

### 输出

```
99

00

01

02

03

04

05

06

07

08

09

19

18

17

16

15

14

13

12

11

10

20

21

22

23

24

25

26

27

28

29

39

38

37

36

35

34

33

32

31

30

40

41

42

43

44

45

46

47

48

49

59

58

57

56

55

54

53

52

51

50

60

61

62

63

64

65

66

67

68

69

79

78

77

76

75

74

73

72

71

70

80

81

82

83

84

85

86

87

88

89

99

98

97

96

95

94

93

92

91

90```

# AI分析结果



### 题目翻译
#### 题目描述
Alice 有一个由 $n$ 个数字转轮组成的密码锁，每个转轮可以设置为 $0$ 到 $9$ 的数字。她忘记了密码，现在需要尝试所有可能的组合来解锁。每次操作只能选择一个转轮并对其加 $1$ 或减 $1$（循环变化，如 $9+1=0$，$0-1=9$）。要求找到操作次数最少的方式遍历所有 $10^n$ 种组合，并输出操作次数及每一步的状态。

#### 输入输出样例
**样例 1**  
输入：  
`1`  
输出：  
```
9
0
1
2
3
4
5
6
7
8
9
```

**样例 2**  
输入：  
`2`  
输出：  
```
99
00
01
...
99
98
...
90
```

---

### 算法分类
**深度优先搜索（DFS）**

---

### 题解分析与总结
#### 核心思路
1. **数学规律**：总操作次数为 $10^n - 1$，因为初始状态（全 0）不计入操作，但需要输出所有状态。
2. **DFS 生成路径**：递归处理每一位，根据当前位的值决定处理方向：
   - 若当前位为 $0$，则递增到 $9$，递归处理下一位。
   - 若当前位非 $0$（如 $9$），则递减到 $0$，递归处理下一位。
3. **相邻状态约束**：每次仅改变一位，确保路径最短。

#### 解决难点
- **递归方向控制**：通过当前位的值动态决定递增或递减，确保生成所有组合。
- **避免重复状态**：DFS 的递归顺序保证每个状态仅访问一次。

---

### 优质题解推荐
#### 1. Dream__Sky 的题解（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 代码简洁，递归逻辑清晰，通过逐位处理实现状态生成。
- 使用字符串直接操作状态，避免数组索引错误。

**核心代码**：
```cpp
void dfs(int dep) {
    if (dep == n) {
        cout << s << endl;
        return;
    }
    if (s[dep] == '0') { // 递增处理
        while (s[dep] < '9') {
            dfs(dep + 1);
            s[dep]++;
        }
        dfs(dep + 1);
    } else { // 递减处理
        while (s[dep] > '0') {
            dfs(dep + 1);
            s[dep]--;
        }
        dfs(dep + 1);
    }
}
```

#### 2. A_grasser 的题解（⭐⭐⭐⭐）
**关键亮点**：  
- 明确分情况处理递增和递减，逻辑易于理解。
- 显式处理边界条件，避免漏掉最后一个状态。

**核心代码**：
```cpp
void dfs(int x) {
    if (x == n) {
        cout << s << endl;
        return;
    }
    if (s[x] == '0') { // 递增
        for (int i = 0; i <= 9; i++) {
            s[x] = '0' + i;
            dfs(x + 1);
        }
    } else { // 递减
        for (int i = 9; i >= 0; i--) {
            s[x] = '0' + i;
            dfs(x + 1);
        }
    }
}
```

---

### 关键技巧总结
- **递归方向动态调整**：根据当前位的值选择递增或递减，确保路径最短。
- **字符串操作**：直接修改字符串中的字符表示状态变化，简化代码。
- **数学规律应用**：总操作次数为 $10^n - 1$，无需模拟即可快速计算。

---

### 拓展与举一反三
1. **同类问题**：类似格雷码生成、欧拉路径问题，均需遍历所有状态且相邻状态仅差一位。
2. **推荐题目**：
   - **P1706 全排列问题**：练习基础 DFS 生成排列。
   - **P1433 吃奶酪**：状态压缩与路径搜索。
   - **P1219 八皇后**：经典 DFS 回溯问题。

---

### 个人心得摘录
- **封禁用户**：初始尝试用奇偶性控制方向失败后，参考递归方向控制思路，最终实现正确逻辑。
- **调试经验**：递归边界处理需特别注意，如确保最后一个状态（如 $9$）被正确处理。

---
处理用时：69.70秒