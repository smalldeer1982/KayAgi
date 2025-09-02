# 题目信息

# Perfect Number

## 题目描述

We consider a positive integer perfect, if and only if the sum of its digits is exactly $ 10 $ . Given a positive integer $ k $ , your task is to find the $ k $ -th smallest perfect positive integer.

## 说明/提示

The first perfect integer is $ 19 $ and the second one is $ 28 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
19
```

## 样例 #2

### 输入

```
2
```

### 输出

```
28
```

# AI分析结果

【题目内容（中文重写）】
# 完美数

## 题目描述
当且仅当一个正整数的各位数字之和恰好为 10 时，我们称这个正整数为完美数。给定一个正整数 $k$，你的任务是找出第 $k$ 小的完美正整数。

## 说明/提示
第一个完美整数是 19，第二个是 28。

## 样例 #1
### 输入
```
1
```
### 输出
```
19
```

## 样例 #2
### 输入
```
2
```
### 输出
```
28
```

【算法分类】
枚举

【综合分析与结论】
这些题解主要围绕找出第 $k$ 小的各位数字之和为 10 的正整数展开。大部分题解采用暴力枚举的方法，从 1 开始逐个检查数字，计算其各位数字之和，若和为 10 则计数器加 1，直到计数器等于 $k$ 时输出该数字。部分题解还提到了用组合数学的方法，通过推导组合式和分段累计求和来解决，但实现相对复杂。

暴力枚举的优点是思路简单、代码实现容易，缺点是当 $k$ 较大时效率较低；组合数学的方法效率更高，但需要较强的数学基础和编程能力。

【所选的题解】
- 作者：DeepSkyBlue__ (赞：3)，4星。关键亮点：思路清晰，代码简洁易懂，通过定义一个计算各位数字之和的函数，然后使用循环枚举数字，当计数器达到 $k$ 时输出结果。
- 作者：L2_sheep (赞：2)，4星。关键亮点：提出了组合数学的方法，当数据范围扩大时能更高效地解决问题，通过推导组合式和分段累计求和来确定结果。
- 作者：char32_t (赞：1)，4星。关键亮点：模拟题的常规做法，通过定义判断函数，然后在循环中进行判断和计数，当达到第 $k$ 个完美数时输出。

【重点代码】
- **DeepSkyBlue__的代码**：
```cpp
int cnt(int x)//计算各位数字之和的函数
{
    int s=0;
    while(x>0)
    {
        s+=x%10;
        x/=10;
    }
    return s;
}
int main()
{
    int n;
    cin>>n;
    int sum=0;//计数器
    for(int i=1;;i++)//循环找数
    {
        if(cnt(i)==10)sum++;//如果各位数字之和为10那么计数器+1
        if(sum==n)//如果是第n个数了
        {
            cout<<i<<endl;//输出这个数
            return 0;//找到了，退出循环
        }
    }
    return 0;
}
```
核心实现思想：定义 `cnt` 函数计算数字各位之和，在 `main` 函数中从 1 开始枚举数字，判断各位之和是否为 10，若是则计数器加 1，当计数器等于 $n$ 时输出该数字。

- **L2_sheep的代码**：
```cpp
#include <stdio.h>
#define N 81
#define M 11

long long c[N][M] = {1};

int main() 
{
    int i, j, l, s;
    long long k, t = 0;

    scanf("%lld", &k);

    for(i = 1; i < N; i++){
        c[i][0] = 1;
        for(j = 1; j < M; j++) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }

    for(i = 2, j = 11; j < N; i++, j++){
        if(c[j][10] - i >= k) break;
        t = c[j][10] - i;
    }
    l = i - 1, s = 10;
    for(i = 1; ; i++){
        if(t + c[s - i - 1 + l][s - i] >= k) break;
        else t += c[s - i - 1 + l][s - i];
    }
    printf("%d", i);
    l--, s -= i;
    while(l > 0){
        if(s == 0) printf("0");
        else{
            for(i = 0; ; i++){
                if(t + c[s - i - 1 + l][s - i] >= k) break;
                else t += c[s - i - 1 + l][s - i];
            }
            printf("%d", i);
            s -= i;
        }
        l--;
    }
    printf("%d", s); 
    return 0;
}
```
核心实现思想：先使用杨辉三角生成组合数，然后通过推导的组合式计算范围，从高位开始分段累计求和，确定每一位的数字。

- **char32_t的代码**：
```cpp
int judge(int a) {//判断a是否为Perfect Number
    int i=0, count=0;
    while(a>0) {
        count+=a%10;
        a/=10;
    }
    return count==10?1:0;//珂怕的三目运算符
}
int main() {
    int count=0, n;
    scanf("%d", &n);//读入数据
    for(int i=9; i<=12000000; i++) {
        if(judge(i)) count++;//每当找到一个Perfect Number时，计数器加1
        if(count==n) {//到达范围边界时
            printf("%d", i);//输出
            break;//退出
        }
    }
    return 0;//结束程序
}
```
核心实现思想：定义 `judge` 函数判断数字是否为完美数，在 `main` 函数中从 9 开始枚举数字，当找到第 $n$ 个完美数时输出。

【可拓展之处】
同类型题可能会改变数字和的要求，或者要求找出满足其他数位条件的第 $k$ 小的数，类似算法套路可以是枚举、组合数学等。

【推荐题目】
1. P1008 三连击
2. P1036 选数
3. P1217 [USACO1.5]回文质数 Prime Palindromes

【个人心得】
- LucasXu80：提到PY代码会TLE，在这种PY明显会超时的题目中，PY不是明智选择，但如果 $k$ 足够小，PY可以方便使用。总结：不同语言在不同数据规模下的效率不同，需要根据实际情况选择合适的语言。

---
处理用时：44.09秒