# 题目信息

# Bear and Prime 100

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

Bear Limak thinks of some hidden number — an integer from interval $ [2,100] $ . Your task is to say if the hidden number is prime or composite.

Integer $ x>1 $ is called prime if it has exactly two distinct divisors, $ 1 $ and $ x $ . If integer $ x>1 $ is not prime, it's called composite.

You can ask up to $ 20 $ queries about divisors of the hidden number. In each query you should print an integer from interval $ [2,100] $ . The system will answer "yes" if your integer is a divisor of the hidden number. Otherwise, the answer will be "no".

For example, if the hidden number is $ 14 $ then the system will answer "yes" only if you print $ 2 $ , $ 7 $ or $ 14 $ .

When you are done asking queries, print "prime" or "composite" and terminate your program.

You will get the Wrong Answer verdict if you ask more than $ 20 $ queries, or if you print an integer not from the range $ [2,100] $ . Also, you will get the Wrong Answer verdict if the printed answer isn't correct.

You will get the Idleness Limit Exceeded verdict if you don't print anything (but you should) or if you forget about flushing the output (more info below).

## 说明/提示

The hidden number in the first query is $ 30 $ . In a table below you can see a better form of the provided example of the communication process.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/b5d048578748c4adde3d49c36a749660a61701b4.png)

The hidden number is divisible by both $ 2 $ and $ 5 $ . Thus, it must be composite. Note that it isn't necessary to know the exact value of the hidden number. In this test, the hidden number is $ 30 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/f54f8d5adb5e9403a147185e0d841ee7fbfd7d7b.png)

 $ 59 $ is a divisor of the hidden number. In the interval $ [2,100] $ there is only one number with this divisor. The hidden number must be $ 59 $ , which is prime. Note that the answer is known even after the second query and you could print it then and terminate. Though, it isn't forbidden to ask unnecessary queries (unless you exceed the limit of $ 20 $ queries).

## 样例 #1

### 输入

```
yes
no
yes
```

### 输出

```
2
80
5
composite
```

## 样例 #2

### 输入

```
no
yes
no
no
no
```

### 输出

```
58
59
78
78
2
prime
```

# AI分析结果



# Bear and Prime 100

## 题目描述

这是一个交互题。在输出部分你将看到关于刷新输出的信息。

熊Limak想了一个隐藏的数字——一个区间$[2,100]$内的整数。你的任务是判断这个隐藏的数字是质数还是合数。

整数$x>1$被称为质数，如果它恰好有两个不同的除数：$1$和$x$。如果整数$x>1$不是质数，则称为合数。

你可以最多提出20次关于隐藏数字的除数的查询。每次查询应输出区间$[2,100]$内的一个整数。系统将回答"yes"表示你的整数是隐藏数的除数，否则回答"no"。

例如，如果隐藏数是$14$，则只有当你输出$2$、$7$或$14$时，系统会回答"yes"。

当你完成查询后，输出"prime"或"composite"并终止程序。

---

## 题解分析与结论

### 核心思路
1. **质数与平方数覆盖**：所有100以内的合数要么能被两个不同的小于等于50的质数整除，要么是某个质数的平方（如4,9,25,49）。需遍历这些质数及其平方。
2. **提前终止**：在每次质数查询得到"yes"后，立即检查其平方是否整除隐藏数。若两次回答为"yes"则直接判定合数，减少查询次数。
3. **查询优化**：总查询次数控制在19次以内，满足题目要求的20次限制。

### 最优题解（评分≥4星）

#### 题解1（作者：lukelin，★★★★★）
**关键亮点**：  
- 分阶段处理质数及其平方，动态生成查询项。
- 代码结构清晰，逻辑紧凑，提前终止机制高效。

**代码核心**：
```cpp
const int p_num = 15;
int prime[20] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

for (int i = 0; i < p_num; ++i) {
    cout << prime[i] << endl;
    cin >> s;
    if (s[0] == 'y') {
        if ((prime[i] * prime[i]) <= 100) {
            cout << prime[i] * prime[i] << endl;
            cin >> s;
            if (s[0] == 'y') return 0; // 立即终止
        }
        if (++cnt >= 2) return 0; // 二次确认即终止
    }
}
```

#### 题解2（作者：PC_DOS，★★★★☆）
**关键亮点**：  
- 预先生成包含质数和平方数的查询列表，代码简洁易实现。
- 通过固定数组覆盖所有可能情况，逻辑直观。

**代码核心**：
```cpp
int arrAsk[19] = {2,3,4,5,9,7,11,13,17,19,23,25,29,31,37,41,43,47,49};
for (int i = 0; i <= 18; ++i) {
    cout << arrAsk[i] << endl;
    if (response == "yes" && ++cnt >= 2) {
        cout << "composite";
        break;
    }
}
```

#### 题解3（作者：N_z_，★★★★☆）
**关键亮点**：  
- 结合质数查询与平方数验证，代码精简。
- 采用复合条件判断，逻辑效率高。

**代码核心**：
```cpp
for (int x : {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47}) {
    if (query(x) == "yes") {
        if (x*x <= 100 && query(x*x) == "yes") cnt++;
        if (++cnt >= 2) return "composite";
    }
}
```

---

## 关键技巧总结
1. **质数筛选范围**：仅需检查≤50的质数，因100的因数分解中至少有一个因数≤50。
2. **平方数特判**：针对形如$p^2$的合数需额外查询，避免漏判。
3. **交互优化**：通过条件提前终止（如两次"yes"响应）减少查询次数。

---

## 类似题目推荐
1. [洛谷P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)  
   **考察点**：质数筛法的基础应用。
2. [洛谷P1217 [USACO1.5]回文质数](https://www.luogu.com.cn/problem/P1217)  
   **考察点**：质数判断与特殊数生成结合。
3. [洛谷P1304 哥德巴赫猜想](https://www.luogu.com.cn/problem/P1304)  
   **考察点**：质数分解与组合判断。

---
处理用时：156.43秒