# 题目信息

# Life Without Zeros

## 题目描述

Can you imagine our life if we removed all zeros from it? For sure we will have many problems.

In this problem we will have a simple example if we removed all zeros from our life, it's the addition operation. Let's assume you are given this equation $ a+b=c $ , where $ a $ and $ b $ are positive integers, and $ c $ is the sum of $ a $ and $ b $ . Now let's remove all zeros from this equation. Will the equation remain correct after removing all zeros?

For example if the equation is $ 101+102=203 $ , if we removed all zeros it will be $ 11+12=23 $ which is still a correct equation.

But if the equation is $ 105+106=211 $ , if we removed all zeros it will be $ 15+16=211 $ which is not a correct equation.

## 样例 #1

### 输入

```
101
102
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
105
106
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 没有零的生活

## 题目描述
你能想象如果我们从生活中移除所有的零，生活会变成什么样吗？可以肯定的是，我们会遇到很多问题。

在这个问题中，我们将看到一个简单的例子——如果从生活中移除所有的零，加法运算会受到什么影响。假设给定一个等式 $a + b = c$，其中 $a$ 和 $b$ 是正整数，$c$ 是 $a$ 与 $b$ 的和。现在，让我们从这个等式中移除所有的零。移除所有零后，等式是否仍然成立？

例如，如果等式是 $101 + 102 = 203$，移除所有零后变为 $11 + 12 = 23$，这仍然是一个正确的等式。

但如果等式是 $105 + 106 = 211$，移除所有零后变为 $15 + 16 = 211$，这就不是一个正确的等式了。

## 样例 #1
### 输入
```
101
102
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
105
106
```
### 输出
```
NO
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是先实现去除整数中零的功能，再判断去除零后的等式是否仍然成立。不同题解在实现去除零的方法上有所差异，包括使用栈、直接取余处理、`stringstream` 转换、数组存储等方式。

### 所选题解
- **Scherzo（4星）**
    - **关键亮点**：思路清晰，详细介绍了栈的使用方法，通过栈存储非零数字，再组合成新数字，代码可读性高。
    - **核心实现思想**：定义 `removeZero` 函数，利用栈存储非零数字，最后将栈中元素组合成新数字。
    - **核心代码**：
```cpp
stack<int>s;
int removeZero(int num)
{
    while (num>=1)
    {
        if (num%10!=0)
        {
            s.push(num%10);
        }
        num/=10;
    }
    int ans=0;
    while (!s.empty())
    {
        ans=ans*10+s.top();
        s.pop();
    }
    return ans;
}
```
- **时律（4星）**
    - **关键亮点**：采用 `stringstream` 实现数字与字符串的转换，思路新颖，代码简洁。
    - **核心实现思想**：使用 `stringstream` 将数字转换为字符串，删除字符串中的零，再将字符串转换回数字。
    - **核心代码**：
```cpp
int num(int u)
{
    stringstream ss;string a,b;int ans;
    ss.clear();
    ss<<u;ss>>a;
    for(int i=0;i<a.size();i++)
        if(a[i]!='0')
            b+=a[i];
    ss.clear();
    ss<<b;ss>>ans;
    return ans;
}
```
- **2x6_81（4星）**
    - **关键亮点**：利用数组存储 10 的幂次方，通过取余和乘法操作实现去除零的功能，代码简洁明了。
    - **核心实现思想**：通过取余判断每一位是否为零，不为零则乘以对应的 10 的幂次方累加到结果中。
    - **核心代码**：
```cpp
const int pow10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int a,b,c,aa,bb,cc,la,lb,lc;
while(a>0)if(a%10!=0)aa+=(a%10)*pow10[la++],a/=10;else a/=10;
while(b>0)if(b%10!=0)bb+=(b%10)*pow10[lb++],b/=10;else b/=10;
while(c>0)if(c%10!=0)cc+=(c%10)*pow10[lc++],c/=10;else c/=10;
```

### 最优关键思路或技巧
- 可以使用栈来存储非零数字，最后组合成新数字，如 Scherzo 的题解。
- 利用 `stringstream` 实现数字与字符串的转换，方便删除零，如时律的题解。
- 借助数组存储 10 的幂次方，通过取余和乘法操作实现去除零的功能，如 2x6_81 的题解。

### 可拓展之处
同类型题可能会涉及更多复杂的数字处理，如去除特定数字、对数字进行特定变换等。类似算法套路可用于处理字符串中的特定字符，或对数组元素进行特定筛选和组合。

### 推荐洛谷题目
- P1001 A+B Problem
- P1047 校门外的树
- P1055 ISBN 号码

### 个人心得摘录与总结
- **FCB_Yiyang2006✈**：提交 3 次才过，提醒要注意开 `long long` 以及对结果倒序处理等细节。总结：在处理数字时，要考虑数据范围和数字顺序等细节，避免出错。
- **Cesare**：认为题目简单，是恶意评分使其成为“黑题”。总结：题目难度判断可能因个人水平和题目评分存在差异，应注重题目本身的逻辑和实现。 

---
处理用时：35.95秒