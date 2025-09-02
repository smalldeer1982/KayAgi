# 题目信息

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56```

### 输出

```
Yes
Yes
No
Yes
No```

# AI分析结果

### 题目翻译
#### Fishingprince玩数组

#### 题目描述
Fishingprince正在玩一个数组 $ [a_1,a_2,\dots,a_n] $ 。他还有一个神奇的数字 $ m $ 。

他可以对该数组进行以下两种操作：
- 选择 $ 1\le i\le n $ ，使得 $ a_i $ 能被 $ m $ 整除（即存在一个整数 $ t $ ，使得 $ m \cdot t = a_i $ ）。将 $ a_i $ 替换为 $ m $ 个 $ \frac{a_i}{m} $ 。其他元素的顺序不变。例如，当 $ m = 2 $ 且 $ a = [2,3] $ ，$ i = 1 $ 时，$ a $ 变为 $ [1,1,3] $ 。
- 选择 $ 1\le i\le n - m + 1 $ ，使得 $ a_i = a_{i + 1} = \dots = a_{i + m - 1} $ 。将这 $ m $ 个元素替换为一个 $ m \cdot a_i $ 。其他元素的顺序不变。例如，当 $ m = 2 $ 且 $ a = [3,2,2,3] $ ，$ i = 2 $ 时，$ a $ 变为 $ [3,4,3] $ 。

注意，数组的长度可能会在操作过程中发生变化。上述的 $ n $ 定义为当前数组的长度（可能与输入中的 $ n $ 不同）。

Fishingprince还有另一个数组 $ [b_1,b_2,\dots,b_k] $ 。请判断他是否可以使用任意数量（可能为零）的操作将数组 $ a $ 转换为数组 $ b $ 。

#### 说明/提示
在样例的第一个测试用例中，我们可以对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ 。

在样例的第二个测试用例中，我们可以：
- 对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ 。
- 对 $ i = 4 $ 执行第二个操作：$ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ 。
- 对 $ i = 3 $ 执行第一个操作：$ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ 。
- 对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ 。
- 对 $ i = 3 $ 执行第二个操作：$ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ 。
- 对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ 。

#### 样例 #1
##### 输入
```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56
```

##### 输出
```
Yes
Yes
No
Yes
No
```

### 综合分析与结论
这些题解的核心思路一致，均是利用两个操作互逆的特性，将数组 $a$ 和 $b$ 中的元素尽可能拆分，再判断拆分后的数组是否相同。由于直接拆分存储可能导致空间不足，所以都采用结构体记录拆分后数字及其出现次数的方式进行优化。

### 所选题解
- **作者：lenlen（5星）**
    - **关键亮点**：思路清晰，详细阐述了判断过程，代码使用双端队列存储拆分后的 $a$ 数组，在拆分 $b$ 数组时逐步比较，代码可读性高。
    - **核心代码**：
```cpp
deque <hl> q;
for(int i=1;i<=n;i++) 
{
    scanf("%d",&a[i]);s1+=a[i];
    int k=1;
    while(a[i]%m==0) a[i]/=m,k*=m;
    q.push_back((hl){a[i],k});
}
for(int i=1;i<=nn&&!flag;i++)
{
    int k=1;
    while(b[i]%m==0) b[i]/=m,k*=m;
    while(k)
    {
        if(q.empty())
        {
            flag=1;
            break;
        }
        tmp=q.front();q.pop_front();
        if(tmp.d!=b[i]) 
        {
            flag=1;
            break;
        }
        if(tmp.sum<=k) k-=tmp.sum;
        else
        {
            q.push_front((hl){tmp.d,tmp.sum-k});
            k=0;
        }
    }
}
```
    - **核心实现思想**：先将数组 $a$ 拆分后存入双端队列，再逐个拆分 $b$ 数组元素，与队列中的元素比较，若类型或数量不匹配则标记不可转换。

- **作者：Avocadooo（4星）**
    - **关键亮点**：对思路的推导过程解释详细，通过数学形式表示数组拆分，便于理解，使用结构体存储拆分后结果并进行合并操作。
    - **核心代码**：
```cpp
for(int i=1,x,y;i<=n;i++)
{
    scanf("%d",&x);
    sum+=x,y=1;
    while(x%m==0) x/=m,y*=m;
    if(!cnt || x!=a[cnt].rt) a[++cnt].rt=x,a[cnt].cnt=y;
    else if(x==a[cnt].rt) a[cnt].cnt+=y;
}
for(int i=1,x,y;i<=k;i++)
{
    scanf("%d",&x);
    sum-=x,y=1;
    while(x%m==0) x/=m,y*=m;
    if(!a2 || x!=b[a2].rt) b[++a2].rt=x,b[a2].cnt=y;
    else if(x==b[a2].rt) b[a2].cnt+=y;
}
```
    - **核心实现思想**：分别对数组 $a$ 和 $b$ 进行拆分，使用结构体存储拆分后数字及其出现次数，相邻相同数字的次数合并，最后比较两个结构体数组。

### 最优关键思路或技巧
- **思维方式**：利用操作互逆的特性，将问题转化为判断两个数组拆分后的结果是否相同。
- **数据结构**：使用结构体记录拆分后数字及其出现次数，避免直接存储拆分后的所有元素，节省空间。

### 可拓展之处
同类型题目可能会改变操作规则或增加限制条件，例如操作次数限制、操作顺序限制等。类似算法套路可用于处理具有可逆操作的状态转换问题，通过将状态转换为标准形式进行比较。

### 洛谷推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：涉及状态转换和可行性判断。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：需要对状态进行操作和转换以达到最优解。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：与状态转换和可行性判断相关。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：38.87秒