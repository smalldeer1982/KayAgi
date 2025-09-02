# 题目信息

# System Testing

## 题目描述

Vasya likes taking part in Codeforces contests. When a round is over, Vasya follows all submissions in the system testing tab.

There are $ n $ solutions, the $ i $ -th of them should be tested on $ a_i $ tests, testing one solution on one test takes $ 1 $ second. The solutions are judged in the order from $ 1 $ to $ n $ . There are $ k $ testing processes which test solutions simultaneously. Each of them can test at most one solution at a time.

At any time moment $ t $ when some testing process is not judging any solution, it takes the first solution from the queue and tests it on each test in increasing order of the test ids. Let this solution have id $ i $ , then it is being tested on the first test from time moment $ t $ till time moment $ t + 1 $ , then on the second test till time moment $ t + 2 $ and so on. This solution is fully tested at time moment $ t + a_i $ , and after that the testing process immediately starts testing another solution.

Consider some time moment, let there be exactly $ m $ fully tested solutions by this moment. There is a caption "System testing: $ d $ %" on the page with solutions, where $ d $ is calculated as

 $ $$$d = round\left(100\cdot\frac{m}{n}\right), $ $ </p><p>where  $ round(x) = \\lfloor{x + 0.5}\\rfloor $  is a function which maps every real to the nearest integer.</p><p>Vasya calls a submission <span class="tex-font-style-it">interesting</span> if there is a time moment (possibly, non-integer) when the solution is being tested on some test  $ q $ , and the caption says "System testing:  $ q$$$%". Find the number of interesting solutions.

Please note that in case when multiple processes attempt to take the first submission from the queue at the same moment (for instance, at the initial moment), the order they take the solutions does not matter.

## 说明/提示

Consider the first example. At time moment $ 0 $ both solutions start testing. At time moment $ 49 $ the first solution is fully tested, so at time moment $ 49.5 $ the second solution is being tested on the test $ 50 $ , and the caption says "System testing: $ 50 $ %" (because there is one fully tested solution out of two). So, the second solution is interesting.

Consider the second example. At time moment $ 0 $ the first and the second solutions start testing. At time moment $ 32 $ the first solution is fully tested, the third solution starts testing, the caption says "System testing: $ 25 $ %". At time moment $ 32 + 24.5 = 56.5 $ the third solutions is being tested on test $ 25 $ , the caption is still the same, thus this solution is interesting. After that the third solution is fully tested at time moment $ 32 + 33 = 65 $ , the fourth solution is fully tested at time moment $ 65 + 1 = 66 $ . The captions becomes "System testing: $ 75 $ %", and at time moment $ 74.5 $ the second solution is being tested on test $ 75 $ . So, this solution is also interesting. Overall, there are two interesting solutions.

## 样例 #1

### 输入

```
2 2
49 100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
32 100 33 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
14 5
48 19 6 9 50 20 3 42 38 43 36 21 44 6
```

### 输出

```
5
```

# AI分析结果

### 题目内容翻译

# 系统测试

## 题目描述

Vasya喜欢参加Codeforces比赛。当一轮比赛结束时，Vasya会关注系统测试标签中的所有提交。

有$n$个解决方案，第$i$个解决方案需要在$a_i$个测试上进行测试，每个测试需要$1$秒。解决方案按从$1$到$n$的顺序进行测试。有$k$个测试进程可以同时测试解决方案。每个进程一次最多只能测试一个解决方案。

在任何时刻$t$，当某个测试进程没有在测试任何解决方案时，它会从队列中取出第一个解决方案，并按测试ID的递增顺序进行测试。假设这个解决方案的ID为$i$，那么它将在时间$t$到$t+1$之间测试第一个测试，然后在$t+1$到$t+2$之间测试第二个测试，依此类推。这个解决方案将在时间$t+a_i$完全测试完毕，之后测试进程会立即开始测试另一个解决方案。

考虑某个时间点，假设此时已经有$m$个解决方案完全测试完毕。页面上会显示“系统测试：$d$%”，其中$d$的计算公式为：

$$d = round\left(100\cdot\frac{m}{n}\right),$$

其中$round(x) = \lfloor{x + 0.5}\rfloor$是将实数映射到最接近整数的函数。

Vasya称一个提交为“有趣的”，如果存在一个时间点（可能是非整数），当该解决方案正在测试某个测试$q$时，页面上显示“系统测试：$q$%”。请找出有多少个“有趣的”解决方案。

请注意，当多个进程同时尝试从队列中取出第一个提交时（例如，在初始时刻），它们取出的顺序无关紧要。

## 说明/提示

考虑第一个示例。在时间$0$，两个解决方案开始测试。在时间$49$，第一个解决方案完全测试完毕，因此在时间$49.5$，第二个解决方案正在测试第$50$个测试，页面上显示“系统测试：$50$%”（因为两个解决方案中有一个已经完全测试完毕）。因此，第二个解决方案是有趣的。

考虑第二个示例。在时间$0$，第一个和第二个解决方案开始测试。在时间$32$，第一个解决方案完全测试完毕，第三个解决方案开始测试，页面上显示“系统测试：$25$%”。在时间$32 + 24.5 = 56.5$，第三个解决方案正在测试第$25$个测试，页面上的显示仍然是“系统测试：$25$%”，因此这个解决方案是有趣的。之后，第三个解决方案在时间$32 + 33 = 65$完全测试完毕，第四个解决方案在时间$65 + 1 = 66$完全测试完毕。页面上显示“系统测试：$75$%”，在时间$74.5$，第二个解决方案正在测试第$75$个测试。因此，这个解决方案也是有趣的。总共有两个有趣的解决方案。

## 样例 #1

### 输入

```
2 2
49 100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
32 100 33 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
14 5
48 19 6 9 50 20 3 42 38 43 36 21 44 6
```

### 输出

```
5
```

### 算法分类
模拟

### 题解分析与结论

本题的核心是通过模拟系统测试的过程，找出“有趣的”解决方案。题解的关键在于如何高效地模拟每个测试进程的状态，并在每个时间点检查是否满足“有趣的”条件。

#### 题解1：__LiChangChao__
- **星级**：4星
- **关键亮点**：
  - 通过枚举每一秒来模拟测试过程，计算当前正在测试的解决方案是否满足“有趣的”条件。
  - 使用数组记录每个解决方案的开始时间和完成状态，确保模拟过程的准确性。
  - 时间复杂度为$O(n^2a_i)$，虽然较高，但在题目给定的数据范围内可以通过。

- **核心代码**：
```cpp
for(int i=1; i<=maxt; i++) {
    int nw=0,m=min(ed,n);
    int d=floor((finish*100.0/n)+0.5);
    for(int j=1; j<=m; j++){
        if(!ok[j]){
            if(i-start[j]==d&&!tj[j]){
                ans++;
                tj[j]=1;
            } 
        } 
        if(i-start[j]==a[j]){
            ok[j]=1,nw++;
        }
    }
    finish+=nw,ed+=nw;
    for(int j=1; j<=min(ed,n); j++){
        if(!start[j]&&j>k)start[j]=i;
    }
}
```

### 最优关键思路或技巧
- **模拟过程**：通过枚举每一秒来模拟测试进程的状态，确保每个解决方案的测试过程被准确记录。
- **状态记录**：使用数组记录每个解决方案的开始时间和完成状态，便于在模拟过程中进行状态检查和更新。

### 可拓展之处
- **并行处理**：可以进一步优化模拟过程，减少时间复杂度，例如通过并行处理多个测试进程的状态。
- **数据结构优化**：使用更高效的数据结构（如优先队列）来管理测试进程的状态，进一步提高模拟效率。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：37.19秒