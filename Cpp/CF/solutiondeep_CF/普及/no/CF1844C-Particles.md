# 题目信息

# Particles

## 题目描述

You have discovered $ n $ mysterious particles on a line with integer charges of $ c_1,\dots,c_n $ . You have a device that allows you to perform the following operation:

- Choose a particle and remove it from the line. The remaining particles will shift to fill in the gap that is created. If there were particles with charges $ x $ and $ y $ directly to the left and right of the removed particle, they combine into a single particle of charge $ x+y $ .

For example, if the line of particles had charges of $ [-3,1,4,-1,5,-9] $ , performing the operation on the $ 4 $ th particle will transform the line into $ [-3,1,9,-9] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1844C/e6e0f8b89386e2413f8854df6b39484bae0098bc.png)If we then use the device on the $ 1 $ st particle in this new line, the line will turn into $ [1,9,-9] $ .

You will perform operations until there is only one particle left. What is the maximum charge of this remaining particle that you can obtain?

## 说明/提示

In the first test case, the best strategy is to use the device on the $ 4 $ th particle, then on the $ 1 $ st particle (as described in the statement), and finally use the device on the new $ 3 $ rd particle followed by the $ 1 $ st particle.

In the second test case, the best strategy is to use the device on the $ 4 $ th particle to transform the line into $ [998244353,998244353,1996488706] $ , then on the $ 2 $ nd particle to transform the line into $ [2994733059] $ . Be wary of integer overflow.

In the third test case, there is only one particle, so no operations can be performed.

## 样例 #1

### 输入

```
3
6
-3 1 4 -1 5 -9
5
998244353 998244353 998244353 998244353 998244353
1
-2718```

### 输出

```
9
2994733059
-2718```

# AI分析结果

### 题目内容重写

#### 题目描述

你在一行上发现了 $n$ 个带有整数电荷 $c_1,\dots,c_n$ 的神秘粒子。你有一个设备，可以执行以下操作：

- 选择一个粒子并将其从行中移除。剩下的粒子会移动以填补产生的空隙。如果被移除的粒子左右两侧分别有电荷为 $x$ 和 $y$ 的粒子，它们会合并成一个电荷为 $x+y$ 的粒子。

例如，如果粒子行的电荷为 $[-3,1,4,-1,5,-9]$，对第 $4$ 个粒子执行操作后，行将变为 $[-3,1,9,-9]$。如果我们在新行中对第 $1$ 个粒子使用设备，行将变为 $[1,9,-9]$。

你将执行操作直到只剩下一个粒子。你能得到的最终粒子的最大电荷是多少？

#### 说明/提示

在第一个测试用例中，最佳策略是对第 $4$ 个粒子使用设备，然后对第 $1$ 个粒子使用设备（如题目描述中所述），最后对新行的第 $3$ 个粒子使用设备，再对第 $1$ 个粒子使用设备。

在第二个测试用例中，最佳策略是对第 $4$ 个粒子使用设备，将行变为 $[998244353,998244353,1996488706]$，然后对第 $2$ 个粒子使用设备，将行变为 $[2994733059]$。注意整数溢出。

在第三个测试用例中，只有一个粒子，因此无法执行任何操作。

#### 样例 #1

##### 输入

```
3
6
-3 1 4 -1 5 -9
5
998244353 998244353 998244353 998244353 998244353
1
-2718
```

##### 输出

```
9
2994733059
-2718
```

### 算法分类
贪心

### 题解分析与结论

#### 核心思路
所有题解都基于一个关键观察：每次操作后，粒子的下标奇偶性保持不变。因此，奇数下标和偶数下标的粒子无法合并。最终答案只能是奇数下标或偶数下标粒子的最大可能和。

#### 解决难点
1. **奇偶性分析**：理解并利用操作后粒子下标奇偶性不变的性质。
2. **负数处理**：如何处理负数粒子，特别是当所有粒子都为负数时，必须保留一个粒子。
3. **优化策略**：通过贪心策略，只累加正数粒子，避免不必要的合并操作。

#### 最优关键思路
- **奇偶性分离**：将奇数下标和偶数下标的粒子分开处理，分别计算它们的最大可能和。
- **负数处理**：如果所有粒子都为负数，则直接取最大值作为最终结果。
- **贪心策略**：只累加正数粒子，忽略负数粒子，因为它们可以通过合并操作消除。

### 精选题解

#### 题解1：zct_sky (5星)
**关键亮点**：
- 清晰解释了奇偶性不变的性质。
- 提供了详细的负数处理策略。
- 代码简洁且高效。

**核心代码**：
```cpp
ll sum1=0,sum2=0;
for(int i=1;i<=n;i++)
    if(i&1)sum1+=max(a[i],0ll);
    else sum2+=max(a[i],0ll);
printf("%lld\n",max(sum1,sum2));
```

#### 题解2：无钩七不改名 (4星)
**关键亮点**：
- 通过动态更新奇偶下标的最大值，优化了计算过程。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
if(c[i]<=0)continue;
if(i&1){
    c[i]=max(c[i],c[i]+js);
    js=max(js,c[i]);
}
else{
    c[i]=max(c[i],c[i]+os);
    os=max(os,c[i]);
}
maxn=max(maxn,c[i]);
```

#### 题解3：Halberd_Cease (4星)
**关键亮点**：
- 详细解释了合并操作的奇偶性影响。
- 提供了构造方案以达到上界的方法。

**核心代码**：
```cpp
if(sum1==0&&sum2==0){
    cout<<max(mx1,mx2)<<endl;
}
else{
    cout<<max(sum1,sum2)<<endl;
}
```

### 拓展思路
- **类似题目**：可以考虑处理其他需要奇偶性分离的问题，如某些动态规划问题。
- **优化技巧**：在处理类似问题时，可以通过预处理或动态更新来优化计算过程。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：29.91秒