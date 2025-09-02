# 题目信息

# Omkar and the Meaning of Life

## 题目描述

It turns out that the meaning of life is a permutation $ p_1, p_2, \ldots, p_n $ of the integers $ 1, 2, \ldots, n $ ( $ 2 \leq n \leq 100 $ ). Omkar, having created all life, knows this permutation, and will allow you to figure it out using some queries.

A query consists of an array $ a_1, a_2, \ldots, a_n $ of integers between $ 1 $ and $ n $ . $ a $ is not required to be a permutation. Omkar will first compute the pairwise sum of $ a $ and $ p $ , meaning that he will compute an array $ s $ where $ s_j = p_j + a_j $ for all $ j = 1, 2, \ldots, n $ . Then, he will find the smallest index $ k $ such that $ s_k $ occurs more than once in $ s $ , and answer with $ k $ . If there is no such index $ k $ , then he will answer with $ 0 $ .

You can perform at most $ 2n $ queries. Figure out the meaning of life $ p $ .

## 说明/提示

In the sample, the hidden permutation $ p $ is $ [3, 2, 1, 5, 4] $ . Three queries were made.

The first query is $ a = [4, 4, 2, 3, 2] $ . This yields $ s = [3 + 4, 2 + 4, 1 + 2, 5 + 3, 4 + 2] = [7, 6, 3, 8, 6] $ . $ 6 $ is the only number that appears more than once, and it appears first at index $ 2 $ , making the answer to the query $ 2 $ .

The second query is $ a = [3, 5, 1, 5, 5] $ . This yields $ s = [3 + 3, 2 + 5, 1 + 1, 5 + 5, 4 + 5] = [6, 7, 2, 10, 9] $ . There are no numbers that appear more than once here, so the answer to the query is $ 0 $ .

The third query is $ a = [5, 2, 4, 3, 1] $ . This yields $ s = [3 + 5, 2 + 2, 1 + 4, 5 + 3, 4 + 1] = [8, 4, 5, 8, 5] $ . $ 5 $ and $ 8 $ both occur more than once here. $ 5 $ first appears at index $ 3 $ , while $ 8 $ first appears at index $ 1 $ , and $ 1 < 3 $ , making the answer to the query $ 1 $ .

Note that the sample is only meant to provide an example of how the interaction works; it is not guaranteed that the above queries represent a correct strategy with which to determine the answer.

## 样例 #1

### 输入

```
5

2

0

1```

### 输出

```
? 4 4 2 3 2

? 3 5 1 5 5

? 5 2 4 3 1

! 3 2 1 5 4```

# AI分析结果

### 题目内容翻译
#### Omkar 与生命的意义

#### 题目描述
事实证明，生命的意义是整数 $1, 2, \ldots, n$ 的一个排列 $p_1, p_2, \ldots, p_n$（$2 \leq n \leq 100$）。创造了所有生命的 Omkar 知道这个排列，并允许你通过一些查询来找出它。

一个查询由一个整数数组 $a_1, a_2, \ldots, a_n$ 组成，数组中的整数在 $1$ 到 $n$ 之间。$a$ 不需要是一个排列。Omkar 首先会计算 $a$ 和 $p$ 的逐元素和，即他会计算一个数组 $s$，其中对于所有 $j = 1, 2, \ldots, n$，$s_j = p_j + a_j$。然后，他会找到最小的索引 $k$，使得 $s_k$ 在 $s$ 中出现不止一次，并返回 $k$。如果不存在这样的索引 $k$，则返回 $0$。

你最多可以进行 $2n$ 次查询。请找出生命的意义 $p$。

#### 说明/提示
在样例中，隐藏的排列 $p$ 是 $[3, 2, 1, 5, 4]$。进行了三次查询。

第一次查询是 $a = [4, 4, 2, 3, 2]$。这会得到 $s = [3 + 4, 2 + 4, 1 + 2, 5 + 3, 4 + 2] = [7, 6, 3, 8, 6]$。$6$ 是唯一出现不止一次的数字，它第一次出现在索引 $2$ 处，因此该查询的答案是 $2$。

第二次查询是 $a = [3, 5, 1, 5, 5]$。这会得到 $s = [3 + 3, 2 + 5, 1 + 1, 5 + 5, 4 + 5] = [6, 7, 2, 10, 9]$。这里没有出现不止一次的数字，所以该查询的答案是 $0$。

第三次查询是 $a = [5, 2, 4, 3, 1]$。这会得到 $s = [3 + 5, 2 + 2, 1 + 4, 5 + 3, 4 + 1] = [8, 4, 5, 8, 5]$。$5$ 和 $8$ 都在这里出现不止一次。$5$ 第一次出现在索引 $3$ 处，而 $8$ 第一次出现在索引 $1$ 处，且 $1 < 3$，因此该查询的答案是 $1$。

请注意，样例仅用于说明交互的工作方式；不能保证上述查询代表了确定答案的正确策略。

#### 样例 #1
##### 输入
```
5
2
0
1
```
##### 输出
```
? 4 4 2 3 2
? 3 5 1 5 5
? 5 2 4 3 1
! 3 2 1 5 4
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕如何在最多 $2n$ 次查询内找出隐藏的排列 $p$ 展开。大部分题解的思路是先通过一定次数的查询确定某个位置的值，再利用这个已确定的值去确定其他位置的值。不同题解在具体的查询策略和确定值的方式上有所不同。

### 所选题解
- **vectorwyx（4星）**
  - **关键亮点**：思路清晰，先确定 $a_n$ 的值，再利用已确定的 $a_n$ 依次确定其他位置的值，代码实现简洁明了。
  - **核心实现思想**：先通过 $n$ 次查询，利用值域排除法确定 $a_n$ 的值。然后再用 $n$ 次查询，令其他位置为 $a_n$，通过改变 $b_n$ 的值来确定其他位置的值。
  - **核心代码**：
```cpp
int a[105],b[105],n;

int query(){
    putchar('?'),putchar(' ');out(b,1,n);
    cout.flush();
    return read();
}

int main(){
    cin>>n;
    fo(i,1,n-1) b[i]=1;
    fo(i,1,n){
        b[n]=n+1-i;
        int x=query();
        if(x){
            a[n]=i;
            break;
        }
    }if(!a[n]) a[n]=n;
    fo(i,1,n-1) b[i]=a[n];
    fo(i,1,n) if(i!=a[n]){
        b[n]=i;
        int x=query();
        a[x]=i;
    }
    putchar('!'),putchar(' ');out(a,1,n);
    return 0;
}
```
- **tttianyu（4星）**
  - **关键亮点**：提出了 $n + 1$ 次询问的做法，通过巧妙的查询策略确定每一位的大小关系，代码实现较为巧妙。
  - **核心实现思想**：通过从后往前枚举，分别查询一个都是 $2$ 的数组把某一位改成 $1$ 和一个都是 $1$ 的数组把某一位改成 $2$ 的情况，确定每一位的大小关系，最后通过类似链表的做法确定每一个数字。
  - **核心代码**：
```cpp
int n,lst[110],nxt[110],ans[110];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        lst[i]=nxt[i]=-1;
    int tmp;
    for(int i=n;i;i--)
    {
        int x;
        if(lst[i]==-1)
        {
            printf("? ");
            for(int j=1;j<i;j++)
                printf("2 ");
            printf("1 ");
            for(int j=i+1;j<=n;j++)
                printf("2 ");
            puts("");
            fflush(stdout);
            scanf("%d",&x);
            if(x!=0)
                lst[i]=x,nxt[x]=i;
            else
                lst[i]=0,tmp=i;
        }
        if(nxt[i]==-1)
        {
            printf("? ");
            for(int j=1;j<i;j++)
                printf("1 ");
            printf("2 ");
            for(int j=i+1;j<=n;j++)
                printf("1 ");
            puts("");
            fflush(stdout);
            scanf("%d",&x);
            if(x!=0)
                nxt[i]=x,lst[x]=i;
            else
                nxt[i]=n+1;
        }
    }
    printf("! ");
    int cnt=1;
    while(cnt<=n)
    {
        ans[tmp]=cnt;
        ++cnt;tmp=nxt[tmp];	
    }
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    fflush(stdout);
    return 0;
}
```
- **loser_seele（4星）**
  - **关键亮点**：提供了严格 $n$ 次询问的做法，通过巧妙的查询策略和推理，每次确定一个数，最终确定整个排列。
  - **核心实现思想**：先不断询问 $1,1,1,\cdots,k(k = 2,3,\cdots)$，直到回答为 $0$ 为止，确定 $p_n$ 的值，再反推出比它大的所有数。然后对于已经确定的位置，每次询问将这些位置设置为 $n$，将 $p_n$ 位置的询问设置为 $1$，遍历所有 $k=(2,3,\cdots,p_n)$，将没确定的位置填上 $k$，逐次从大到小确定剩下所有的数。
  - **核心代码**：
```cpp
int n,a[200020],b[200020];
int tot;
void query() 
{
    tot++;
    cout<<"? ";
    for (int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    cout<<endl;
}
void answer() 
{
    cout<<"! ";
    for (int i=1;i<=n;i++)
        cout<<b[i]<<' ';
    cout<<endl;
}
int read() 
{
    int x;
    cin>>x;
    return x;
}
int main() 
{
    n=read();
    for (int i=1;i<=n;i++)
        a[i]=1;
    for (int i=1;i<=n;i++) 
    {
        a[n]++;
        int tmp=0;
        if(i!=n) 
        {
            query();
            tmp=read();
        } 
        else
            tmp=0;
        if(!tmp) 
        {
            b[n]=n-i+1;
            for (int j=1;j<=n-1;j++)
                if(b[j])
                    b[j]+=b[n];
            break;
        } 
        else
            b[tmp]=i;
    }
    a[n]=1;
    for (int i=1;i<=b[n]-1;i++)
    {
        for (int j=1;j<n;j++)
            if(b[j])
                a[j]=n; 
            else
                a[j]=i+1;
        query();
        b[read()]=b[n]-i;
    }
    answer();
    return 0;
}
```

### 最优关键思路或技巧
- 大部分题解都采用了先确定一个位置的值，再利用这个已确定的值去确定其他位置的值的思路，这种分步骤解决问题的方法可以降低问题的复杂度。
- 一些题解通过巧妙的查询策略，如改变查询数组中某一位的值，利用交互库返回的信息来确定排列中的元素，体现了对问题的深入理解和巧妙运用。

### 可拓展之处
同类型的交互题通常需要根据交互库的反馈信息，设计合理的查询策略来逐步确定问题的答案。在解决这类问题时，可以尝试先确定一些关键信息，再利用这些信息去推导其他信息。类似的算法套路包括利用值域排除、通过改变查询数组的某些元素来获取有用信息等。

### 推荐洛谷题目
1. P1115 最大子段和（考察对问题的分析和构造能力）
2. P1047 校门外的树（简单的模拟和构造问题）
3. P1098 字符串的展开（需要根据规则构造输出的字符串）

### 个人心得摘录与总结
- **pitiless0514**：提到考试之前发题解可以增加 rp，属于个人调侃，无实际解题心得。
- 大部分题解没有包含个人调试经历、踩坑教训等内容。 

---
处理用时：99.25秒