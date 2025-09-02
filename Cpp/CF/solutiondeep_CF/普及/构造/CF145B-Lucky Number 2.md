# 题目信息

# Lucky Number 2

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya loves long lucky numbers very much. He is interested in the minimum lucky number $ d $ that meets some condition. Let $ cnt(x) $ be the number of occurrences of number $ x $ in number $ d $ as a substring. For example, if $ d=747747 $ , then $ cnt(4)=2 $ , $ cnt(7)=4 $ , $ cnt(47)=2 $ , $ cnt(74)=2 $ . Petya wants the following condition to fulfil simultaneously: $ cnt(4)=a_{1} $ , $ cnt(7)=a_{2} $ , $ cnt(47)=a_{3} $ , $ cnt(74)=a_{4} $ . Petya is not interested in the occurrences of other numbers. Help him cope with this task.

## 样例 #1

### 输入

```
2 2 1 1
```

### 输出

```
4774
```

## 样例 #2

### 输入

```
4 7 3 1
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 幸运数字 2

## 题目描述
Petya 非常喜欢幸运数字。众所周知，幸运数字是十进制表示中仅包含幸运数字 4 和 7 的正整数。例如，数字 47、744、4 是幸运数字，而 5、17、467 不是。

Petya 非常喜欢长的幸运数字。他对满足某些条件的最小幸运数字 $d$ 感兴趣。设 $cnt(x)$ 是数字 $x$ 在数字 $d$ 中作为子串出现的次数。例如，如果 $d = 747747$，那么 $cnt(4) = 2$，$cnt(7) = 4$，$cnt(47) = 2$，$cnt(74) = 2$。Petya 希望同时满足以下条件：$cnt(4) = a_{1}$，$cnt(7) = a_{2}$，$cnt(47) = a_{3}$，$cnt(74) = a_{4}$。Petya 不关心其他数字的出现情况。帮助他完成这个任务。

## 样例 #1
### 输入
```
2 2 1 1
```
### 输出
```
4774
```

## 样例 #2
### 输入
```
4 7 3 1
```
### 输出
```
-1
```

### 综合分析与结论
这些题解的核心思路都是先根据给定的 4、7、47、74 的个数判断是否有解，若有解则构造出满足条件的最小幸运数。不同题解在构造方法和判断无解的条件上有相似之处，但实现细节有所不同。
- **思路对比**：
    - pikabi 和 Sayori 的思路较为相似，都是先搭建 47 和 74 的骨架，再填充多余的 4 和 7。
    - wyc0607、lin_A_chu_K_fan 和 _zhaosihan_qwq_ 主要是先给出判断无解的条件，然后提到枚举求解，但未详细说明构造方法。
- **算法要点**：
    - 共同要点是判断 $|a_3 - a_4| > 1$ 时无解，以及 $a_1 < a_3$ 或 $a_2 < a_3$ 或 $a_1 < a_4$ 或 $a_2 < a_4$ 时无解。
    - pikabi 和 Sayori 还涉及到根据 47 和 74 的数量关系搭建骨架和填充数字的具体操作。
- **解决难点**：
    - 难点在于判断无解的条件和构造满足条件的最小幸运数。不同题解通过不同的方式处理这些难点，如 pikabi 使用 vector 存储数字，Sayori 直接用数组存储。

### 所选题解
- **pikabi（4星）**：
    - **关键亮点**：使用 vector 存储数字，思路清晰，通过搭建骨架和填充数字的方式构造幸运数，考虑了 47 和 74 数量相等时的特殊情况。
    - **核心代码**：
```cpp
if(nn >= mm) {
    int k = nn + mm;
    a[1].push_back(1), --n; 
    for(int i = 2; i <= k + 1; i++){
        if(i % 2 == 1){
            if(!mm ||!n) {
                goto there;
            }
            a[i].push_back(1), --mm, --n;
        }
        else{	
            if(!nn ||!m){
                goto there;
                return 0;
            }
            a[i].push_back(2), --nn, --m; 
        }
    }
    while(n--){
        a[1].push_back(1); 
    }
    int w = k + 1;
    if(!(k % 2)) w--;
    while(m--){
        a[w].push_back(2); 
    }
    // 输出结果
}
```
核心实现思想：先根据 47 和 74 的数量关系搭建骨架，再将多余的 4 放在最前面的 4 后，多余的 7 放在最后的 7 后。
- **Sayori（4星）**：
    - **关键亮点**：代码简洁，先构造以 4 为首项和以 7 为首项的 47 字符串，再判断是否满足条件，最后输出结果。
    - **核心代码**：
```cpp
if(a[1] < a[3] || a[2] < a[3] || a[1] < a[4] || a[2] < a[4] || abs(a[3] - a[4]) > 1){
    puts("-1"); return 0;
}
int x = a[1], y = a[2], z = a[3], w = a[4];
ans[cnt = 1] = 4; x--;
while(z > 0 || w > 0){
    ans[++cnt] = fl == 0? 7 : 4;
    if(fl == 0) z--, y--;
    else w--, x--;
    fl ^= 1;
}
if(x < 0 || y < 0 || z < 0 || w < 0){
    // 构造以 7 为首项的 74 字符串
}
// 输出结果
```
核心实现思想：先判断无解的条件，然后构造以 4 为首项的 47 字符串，若不满足条件则构造以 7 为首项的 74 字符串，最后输出满足条件的字符串。

### 最优关键思路或技巧
- 先判断无解的条件，如 $|a_3 - a_4| > 1$ 和 $a_1 < a_3$ 等，减少不必要的计算。
- 先搭建 47 和 74 的骨架，再填充多余的 4 和 7，保证构造出的幸运数最小。

### 可拓展之处
同类型题可能会改变幸运数字的范围，或者增加更多子串的出现次数要求。类似算法套路是先分析无解的条件，再根据条件构造满足要求的字符串。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串的处理和规则判断。
- [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)：需要根据给定的规则构造字符串。
- [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)：涉及字符串中字符的统计和判断。

### 个人心得
无。

---
处理用时：33.64秒