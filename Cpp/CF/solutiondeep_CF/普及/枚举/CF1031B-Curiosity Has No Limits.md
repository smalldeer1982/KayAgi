# 题目信息

# Curiosity Has No Limits

## 题目描述

When Masha came to math classes today, she saw two integer sequences of length $ n - 1 $ on the blackboard. Let's denote the elements of the first sequence as $ a_i $ ( $ 0 \le a_i \le 3 $ ), and the elements of the second sequence as $ b_i $ ( $ 0 \le b_i \le 3 $ ).

Masha became interested if or not there is an integer sequence of length $ n $ , which elements we will denote as $ t_i $ ( $ 0 \le t_i \le 3 $ ), so that for every $ i $ ( $ 1 \le i \le n - 1 $ ) the following is true:

- $ a_i = t_i | t_{i + 1} $ (where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR)) and
- $ b_i = t_i \& t_{i + 1} $ (where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND)).

The question appeared to be too difficult for Masha, so now she asked you to check whether such a sequence $ t_i $ of length $ n $ exists. If it exists, find such a sequence. If there are multiple such sequences, find any of them.

## 说明/提示

In the first example it's easy to see that the sequence from output satisfies the given conditions:

- $ t_1 | t_2 = (01_2) | (11_2) = (11_2) = 3 = a_1 $ and $ t_1 \& t_2 = (01_2) \& (11_2) = (01_2) = 1 = b_1 $ ;
- $ t_2 | t_3 = (11_2) | (10_2) = (11_2) = 3 = a_2 $ and $ t_2 \& t_3 = (11_2) \& (10_2) = (10_2) = 2 = b_2 $ ;
- $ t_3 | t_4 = (10_2) | (00_2) = (10_2) = 2 = a_3 $ and $ t_3 \& t_4 = (10_2) \& (00_2) = (00_2) = 0 = b_3 $ .

In the second example there is no such sequence.

## 样例 #1

### 输入

```
4
3 3 2
1 2 0
```

### 输出

```
YES
1 3 2 0 ```

## 样例 #2

### 输入

```
3
1 3
3 2
```

### 输出

```
NO```

# AI分析结果

### 题目翻译
# 好奇心无止境

## 题目描述
今天玛莎来上数学课的时候，她看到黑板上有两个长度为 $ n - 1 $ 的整数序列。我们将第一个序列的元素记为 $ a_i $（$ 0 \le a_i \le 3 $），第二个序列的元素记为 $ b_i $（$ 0 \le b_i \le 3 $）。

玛莎想知道是否存在一个长度为 $ n $ 的整数序列，我们将其元素记为 $ t_i $（$ 0 \le t_i \le 3 $），使得对于每个 $ i $（$ 1 \le i \le n - 1 $）都满足以下条件：
- $ a_i = t_i | t_{i + 1} $（其中 $ | $ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)）；
- $ b_i = t_i \& t_{i + 1} $（其中 $ \& $ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)）。

这个问题对玛莎来说太难了，所以现在她请你检查是否存在这样一个长度为 $ n $ 的序列 $ t_i $。如果存在，找出这样一个序列。如果有多个这样的序列，找出其中任意一个。

## 说明/提示
在第一个样例中，很容易看出输出的序列满足给定条件：
- $ t_1 | t_2 = (01_2) | (11_2) = (11_2) = 3 = a_1 $ 且 $ t_1 \& t_2 = (01_2) \& (11_2) = (01_2) = 1 = b_1 $；
- $ t_2 | t_3 = (11_2) | (10_2) = (11_2) = 3 = a_2 $ 且 $ t_2 \& t_3 = (11_2) \& (10_2) = (10_2) = 2 = b_2 $；
- $ t_3 | t_4 = (10_2) | (00_2) = (10_2) = 2 = a_3 $ 且 $ t_3 \& t_4 = (10_2) \& (00_2) = (00_2) = 0 = b_3 $。

在第二个样例中，不存在这样的序列。

## 样例 #1
### 输入
```
4
3 3 2
1 2 0
```
### 输出
```
YES
1 3 2 0
```

## 样例 #2
### 输入
```
3
1 3
3 2
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路都是通过枚举 $t$ 数组的第一个元素（或最后一个元素），然后根据按位与和按位或的条件递推计算出 $t$ 数组的其余元素。具体实现上略有不同，部分题解利用了 $a \& b + a | b = a + b$ 这个规律来简化计算。

### 所选题解
- **作者：DarkShadow (赞：4)，5星**
    - **关键亮点**：思路清晰，代码简洁，对枚举和递推的过程解释详细，时间复杂度分析明确。
    - **核心代码**：
```cpp
bool check(int a){
    way[1]=a;
    bool flag;
    for(int i=2;i<=n;i++){
        flag=0;
        for(int j=0;j<=3;j++)
            if((way[i-1]|j)==A[i-1]&&(way[i-1]&j)==B[i-1]){
                flag=1,way[i]=j;
                break;
            }
        if(!flag)  return 0;
    }
    printf("YES\n");
    for(int i=1;i<=n;i++)
        printf("%d ",way[i]);
    return 1;
}
```
    - **核心实现思想**：函数 `check` 用于检查以 `a` 作为 $t_1$ 时是否能构造出满足条件的 $t$ 数组。通过两层循环，外层循环遍历 $t$ 数组的每个元素，内层循环枚举当前元素的可能取值，若满足按位与和按位或的条件则记录该值，若无法找到合适的值则返回 `false`。

- **作者：Karry5307 (赞：2)，4星**
    - **关键亮点**：利用了 $a_i+b_i=t_{i}+t_{i+1}$ 这个规律，减少了内层枚举的过程，代码简洁。
    - **核心代码**：
```cpp
for(register int i=0;i<=3;i++)
{
    t[1]=i,flg=1;
    for(register int j=2;j<=n;j++)
    {
        t[j]=x[j]+y[j]-t[j-1];
        flg&=(((t[j]|t[j-1])==x[j])&&((t[j]&t[j-1])==y[j]));
    }
    if(flg)
    {
        puts("YES");
        for(register int j=1;j<=n;j++)
        {
            printf("%d ",t[j]);
        }
        return 0;	
    }
}
```
    - **核心实现思想**：通过枚举 $t_1$ 的值，利用 $a_i+b_i=t_{i}+t_{i+1}$ 递推计算出 $t$ 数组的其余元素，同时检查是否满足按位与和按位或的条件，若满足则输出结果。

- **作者：StudyingFather (赞：0)，4星**
    - **关键亮点**：同样利用了 $a \& b + a | b = a + b$ 的规律，代码简洁，逻辑清晰。
    - **核心代码**：
```cpp
for(int i=0;i<=3;i++)
{
    bool flag=true;
    t[0]=i;
    for(int j=1;j<n;j++)
    {
        t[j]=a[j]+b[j]-t[j-1];
        if((t[j-1]|t[j])!=a[j]||(t[j-1]&t[j])!=b[j])
        {
            flag=false;
            break;
        }
    }
    if(flag)
    {
        puts("YES");
        for(int i=0;i<n;i++)
            printf("%d ",t[i]);
        return 0;
    }
}
```
    - **核心实现思想**：枚举 $t_1$ 的值，根据规律递推计算 $t$ 数组的其余元素，若出现不满足条件的情况则标记为 `false`，若最终 `flag` 为 `true` 则输出结果。

### 最优关键思路或技巧
- 利用 $a \& b + a | b = a + b$ 这个规律，减少了枚举的复杂度，将时间复杂度控制在 $O(N)$。
- 由于 $t$ 数组的每个元素只有 $0,1,2,3$ 四种情况，所以可以通过枚举 $t_1$ 的值来简化问题。

### 拓展思路
同类型题目可能会改变数据范围或运算规则，例如将按位与和按位或运算换成其他位运算，或者增大数据范围，此时可能需要使用更高效的算法或数据结构。类似的算法套路是通过枚举部分元素的值，然后根据给定的条件递推计算出其他元素的值。

### 洛谷推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来解决问题。
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察组合枚举的实现。
3. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)：涉及到全排列的枚举。

### 个人心得摘录与总结
- **作者：5G信号塔报装**：在代码实现过程中容易出现逻辑运算符优先级错误和变量书写错误，同时要注意题目要求，当有多个答案时只需输出一个。总结来说，在编码时要仔细检查逻辑和变量，认真阅读题目要求。 

---
处理用时：42.77秒