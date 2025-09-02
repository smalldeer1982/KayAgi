# 题目信息

# Count the Number of Pairs

## 题目描述

Kristina has a string $ s $ of length $ n $ , consisting only of lowercase and uppercase Latin letters. For each pair of lowercase letter and its matching uppercase letter, Kristina can get $ 1 $ burl. However, pairs of characters cannot overlap, so each character can only be in one pair.

For example, if she has the string $ s $ = "aAaaBACacbE", she can get a burl for the following character pairs:

- $ s_1 $ = "a" and $ s_2 $ = "A"
- $ s_4 $ = "a" and $ s_6 $ = "A"
- $ s_5 $ = "B" and $ s_{10} $ = "b"
- $ s_7 $ = "C" and $ s_9 $ = "c"

Kristina wants to get more burles for her string, so she is going to perform no more than $ k $ operations on it. In one operation, she can:

- either select the lowercase character $ s_i $ ( $ 1 \le i \le n $ ) and make it uppercase.
- or select uppercase character $ s_i $ ( $ 1 \le i \le n $ ) and make it lowercase.

For example, when $ k $ = 2 and $ s $ = "aAaaBACacbE" it can perform one operation: choose $ s_3 $ = "a" and make it uppercase. Then she will get another pair of $ s_3 $ = "A" and $ s_8 $ = "a"

Find maximum number of burles Kristina can get for her string.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is not possible to get any pair by performing any number of operations.

## 样例 #1

### 输入

```
5
11 2
aAaaBACacbE
2 2
ab
4 1
aaBB
6 0
abBAcC
5 3
cbccb```

### 输出

```
5
0
1
3
2```

# AI分析结果

### 题目内容
# 统计配对数量

## 题目描述
克里斯蒂娜有一个长度为 $n$ 的字符串 $s$，仅由小写和大写拉丁字母组成。对于每一对小写字母及其对应的大写字母，克里斯蒂娜可以获得1布尔（货币单位）。然而，字符对不能重叠，所以每个字符只能在一对中。

例如，如果她有字符串 $s$ = "aAaaBACacbE"，她可以为以下字符对获得布尔：
- $s_1$ = "a" 和 $s_2$ = "A"
- $s_4$ = "a" 和 $s_6$ = "A"
- $s_5$ = "B" 和 $s_{10}$ = "b"
- $s_7$ = "C" 和 $s_9$ = "c"

克里斯蒂娜想为她的字符串获得更多布尔，所以她打算对其执行不超过 $k$ 次操作。在一次操作中，她可以：
- 要么选择小写字符 $s_i$（$1 \leq i \leq n$）并将其变为大写。
- 要么选择大写字符 $s_i$（$1 \leq i \leq n$）并将其变为小写。

例如，当 $k$ = 2 且 $s$ = "aAaaBACacbE" 时，她可以执行一次操作：选择 $s_3$ = "a" 并将其变为大写。然后她将得到另一对 $s_3$ = "A" 和 $s_8$ = "a"。

找出克里斯蒂娜通过她的字符串最多能获得多少布尔。

## 说明/提示
第一个测试用例在问题陈述中已解释。

在第二个测试用例中，无论执行多少次操作都无法得到任何配对。

## 样例 #1
### 输入
```
5
11 2
aAaaBACacbE
2 2
ab
4 1
aaBB
6 0
abBAcC
5 3
cbccb
```
### 输出
```
5
0
1
3
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为一致，均先统计字符串中每个字母大小写的出现次数，计算无需操作就能配对的对数，然后贪心考虑通过不超过 $k$ 次操作，将剩余的大小写字母进行转换以形成更多配对。主要差异在于实现细节和代码风格，如使用的数据结构（数组、map 等）以及计算操作后可新增配对数的具体写法。

### 所选的题解
- **作者：zajasi (赞：4) - 5星**
    - **关键亮点**：思路清晰简洁，代码实现直接明了。先利用数组统计大小写字母个数，然后先将能配对的直接配对，接着通过贪心策略，尽可能利用操作次数去配对剩余字母，逻辑连贯，易于理解。
    - **重点代码**：
```cpp
for(int i=0;i<n;i++){
    if(a[i]>='A'&&a[i]<='Z'){
        c[a[i]-'A'+1]++;
    }
    else{
        d[a[i]-'a'+1]++;
    }//统计大小写个数
}
int z=0;
for(int i=1;i<=26;i++){
    int x=min(c[i],d[i]);
    z+=x;
    c[i]-=x;
    d[i]-=x;
    //先把能配的配了
    if(k>=(c[i]+d[i])/2){
        z+=(c[i]+d[i])/2;
        k-=(c[i]+d[i])/2;
    }
    else{
        z+=k;
        k=0;
    }//贪心，能配多少配多少
}
```
- **作者：Larryyu (赞：1) - 4星**
    - **关键亮点**：对思路的阐述详细，先明确为使分值最大需让大小写数量之差尽量小，通过公式计算出每种字母操作后能增加的对数，整体逻辑推导清晰。
    - **重点代码**：
```cpp
for(int i=1;i<=26;i++){
    ans+=min(a[i],b[i]);//操作前就有的分值
    ans+=min(abs(a[i]-b[i])/2,k);//操作后增加的分值
    k-=min(abs(a[i]-b[i])/2,k);//减去该字母耗费的操作数
}
```
- **作者：ダ月 (赞：0) - 4星**
    - **关键亮点**：分析过程清晰，先记录未操作前能有的配对数 $a$，再计算假使任意次操作让整个序列达到最多配对数的最少操作数 $b$，最后答案为 $a + \min\{b, k\}$，计算过程简洁明了。
    - **重点代码**：
```cpp
for(int i='a';i<='z';i++)
    sum+=abs(tot[i]-tot[i-'a'+'A'])/2,
    k+=min(tot[i],tot[i-'a'+'A']);
printf("%d\n",k+min(sum,m));
```

### 最优关键思路或技巧
1. **数据统计**：利用数组或 map 统计每个字母大小写的出现次数，为后续配对计算做准备。
2. **贪心策略**：优先配对无需操作的字符对，然后对于剩余字符，通过改变大小写尽可能形成新的配对，每次操作都选择能增加配对数最多的方式，充分利用操作次数 $k$。

### 可拓展之处
同类型题通常围绕字符串中字符的配对、变换操作及最值求解。类似算法套路是先统计相关元素数量，再依据题目规则贪心或按特定逻辑处理剩余元素。例如给定字符串和有限次替换操作，求满足特定子串数量最大化等。

### 洛谷相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过合理排序解决问题，与本题贪心思路类似。
2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：同样需运用贪心思想对任务进行排序调度，优化生产时间。
3. [P1948 概率充电器](https://www.luogu.com.cn/problem/P1948)：结合贪心与概率计算，在树形结构上进行分析，对贪心思维有进一步拓展。 

---
处理用时：44.98秒