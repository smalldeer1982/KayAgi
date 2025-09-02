# 题目信息

# Numbers

## 题目描述

One day Anna got the following task at school: to arrange several numbers in a circle so that any two neighboring numbers differs exactly by 1. Anna was given several numbers and arranged them in a circle to fulfill the task. Then she wanted to check if she had arranged the numbers correctly, but at this point her younger sister Maria came and shuffled all numbers. Anna got sick with anger but what's done is done and the results of her work had been destroyed. But please tell Anna: could she have hypothetically completed the task using all those given numbers?

## 样例 #1

### 输入

```
4
1 2 3 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6
1 1 2 2 2 3
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
6
2 4 1 1 2 2
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 数字

## 题目描述
一天，安娜在学校接到了如下任务：将若干数字排成一个圆圈，使得任意两个相邻数字恰好相差1。安娜得到了若干数字，并将它们排成一个圆圈以完成任务。然后她想检查自己是否排列正确，但就在这时，她的妹妹玛丽亚过来把所有数字打乱了。安娜气得不轻，但木已成舟，她的劳动成果已被破坏。但请告诉安娜：她是否有可能在假设情况下使用所有给定数字完成任务？

## 样例 #1
### 输入
```
4
1 2 3 2
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
6
1 1 2 2 2 3
```
### 输出
```
YES
```

## 样例 #3
### 输入
```
6
2 4 1 1 2 2
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路大多是先对输入数字进行排序，判断相邻数字差值是否都不大于1，若存在差值大于1的情况则直接判定无法构成满足条件的环。接着通过离散化或桶排序等方式处理数据范围，再尝试从某个起始值开始，按照相邻数字差为1的规则，优先选择较大值（若存在），否则选择较小值，逐步构建环，过程中若无法继续构建或构建完成后剩余数字不为0，或者最终位置不符合闭环要求，则判定不能构成环。部分题解还提到了一些特殊情况，如n为奇数时直接判定无解，因为要形成闭环，+1和 -1的次数需相等，所以n必须为偶数。

### 所选的题解
 - **作者：封禁用户 (赞：2)  星级：4星**
    - **关键亮点**：思路清晰，先排除明显不可能的情况（排序后相邻数差≥2），再缩小数据范围方便用桶处理，通过贪心的转移规则模拟构建环的过程，最后检查桶内是否有剩余元素判断能否成环。
    - **重点代码**：
```cpp
sort(a + 1, a + n + 1);
for(int i = 2; i <= n; i++)
{
    if(a[i] - 1 > a[i - 1])
    {
        cout << "NO";
        return 0;
    }
}
for(int i = n; i >= 1; i--)
{
    a[i] -= a[1];
    b[a[i]]++;
}
while(1)
{
    b[cnt]--;
    if(b[cnt + 1])
    {
        cnt++;
    }
    else if(cnt == 1 &&!b[0])
    {
        break;
    }
    else if(b[cnt - 1])
    {
        cnt--;
    }
    else
    {
        cout << "NO";
        return 0;
    }
}
for(int i = 1; i <= 100000; i++)
{
    if(b[i])
    {
        cout << "NO";
        return 0;
    }
}
cout << "YES";
```
核心实现思想：先排序判断相邻数差，然后将数放入桶中，从0开始按贪心规则移动，若移动过程中无法继续则判定无解，最后检查桶内是否有剩余元素。
 - **作者：rui_er (赞：2)  星级：4星**
    - **关键亮点**：先利用n必须为偶数这一特性快速排除奇数情况，后续处理与其他题解类似，排序判断相邻数差，离散化处理数据，从最小值开始按规则构建环，利用闭环性质判断最后一个数是否为2以及桶内是否有剩余元素。
    - **重点代码**：
```cpp
if(n & 1) return puts("NO"), 0; 
rep(i, 1, n) scanf("%d", &a[i]), mi = min(mi, a[i]);
sort(a+1, a+1+n);
rep(i, 2, n) if(a[i] - a[i-1] > 1) return puts("NO"), 0; 
rep(i, 1, n) ++buc[a[i]-mi+1];
int u = 1; --buc[1];
loop {
    if(buc[u+1]) --buc[++u];
    else if(buc[u-1]) --buc[--u];
    else break;
}
if(u!= 2) return puts("NO"), 0; 
rep(i, 0, N-1) if(buc[i]) return puts("NO"), 0; 
return puts("YES"), 0;
```
核心实现思想：先判断n的奇偶性，然后排序检查相邻数差，将数放入桶中，从1开始按规则构建环，根据最后位置和桶内剩余情况判断能否成环。
 - **作者：Exber (赞：1)  星级：4星**
    - **关键亮点**：通过离散化处理数据，将环问题转化为链问题，从1出发构造相邻高度差为1的折线，通过对不同高度点数量的分析，逐步处理每个高度的点，判断能否完成遍历。
    - **重点代码**：
```cpp
sort(a+1,a+n+1);
int tot=0;
for(int i=1;i<=n;i++)
{
    if(a[i]!=a[i-1])
    {
        if(i!=1&&a[i]!=a[i-1]+1)
        {
            puts("NO");
            return 0;
        }
        tot++;
    }
    cnt[tot]++;
}
for(int i=1;i<=tot;i++)
{
    if(--cnt[i]<0)
    {
        puts("NO");
        return 0;
    }
}
for(int i=tot;i>=2;i--)
{
    if(cnt[i]<0)
    {
        puts("NO");
        return 0;
    }
    cnt[i-1]-=cnt[i]+1;
}
puts(cnt[1]==-1?"YES":"NO");
```
核心实现思想：排序判断相邻数差，离散化统计各数出现次数，先处理“上坡路”，再从高到低处理每个高度点，根据各高度点数量关系判断能否成环。

### 最优关键思路或技巧
1. **数据预处理**：排序后检查相邻数字差值，快速排除不可能的情况，同时对数据进行离散化处理，缩小数据范围，方便后续操作。
2. **贪心策略**：在构建环的过程中，优先选择较大值（若存在），否则选择较小值，尽可能地完成环的构建。
3. **利用闭环性质**：如n必须为偶数，以及构建环的最后一个数需满足特定条件（如离散化后为2），利用这些性质简化判断过程。

### 同类型题或类似算法套路拓展
同类型题通常围绕数字的特定排列规则展开，类似算法套路包括先对数据进行预处理（如排序、离散化），再依据给定规则通过贪心或模拟的方式尝试构建满足条件的排列，过程中利用问题的特殊性质（如奇偶性、边界条件）优化判断。

### 洛谷相似题目推荐
1. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察按特定规则生成排列组合，与本题构建特定数字排列有相似之处。
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和判断来满足特定条件，类似本题对数字排列条件的判断。
3. [P1092 虫食算](https://www.luogu.com.cn/problem/P1092)：需要根据题目规则对数字进行填充和判断，与本题构建数字环并判断是否符合规则思路类似。 

---
处理用时：72.36秒