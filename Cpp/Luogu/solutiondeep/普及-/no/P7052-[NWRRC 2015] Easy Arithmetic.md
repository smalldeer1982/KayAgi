# 题目信息

# [NWRRC 2015] Easy Arithmetic

## 题目描述



Eva is a third-grade elementary school student. She has just learned how to perform addition and subtraction of arbitrary-precision integers. Her homework is to evaluate some expressions. It is boring, so she decided to add a little trick to the homework. Eva wants to add some plus and minus signs to the expression to make its value as large as possible.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
10+20-30
```

### 输出

```
10+20-3+0
```

## 样例 #2

### 输入

```
-3-4-1
```

### 输出

```
-3-4-1
```

## 样例 #3

### 输入

```
+10
```

### 输出

```
+10
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
题目要求通过在表达式中添加加号或减号，使得表达式的值最大。所有题解都采用了贪心算法，核心思路是在减法操作后的数字中尽可能早地添加加号，以最大化表达式的值。具体来说，当遇到减法时，将减号后的数字尽可能早地分割为多个部分，并在分割点添加加号。这样可以减少减法的负面影响，增加加法的正面影响。

### 所选高星题解

#### 1. 作者：Wan__Ye__Chu (4星)
**关键亮点**：思路清晰，代码简洁，直接通过遍历字符串并在适当位置添加加号来实现贪心策略。
**个人心得**：作者通过举例说明贪心策略的正确性，帮助理解如何在减法操作中最大化表达式的值。
**核心代码**：
```cpp
for(int i=0;i<len;i++)
{
    if(a[i]=='+')
        sum=0;
    if(a[i]=='-')
    {
        sum=1;
        cout<<"-";
        continue;
    }
    if(sum==1 && a[i-1]!='-')
    {
        cout<<"+";
        if(a[i+1]!='-' && a[i+1]!='+' && a[i]=='0')
        {
            cout<<a[i];
            continue;
        }	
        sum=0;
    }
    cout<<a[i];
}
```

#### 2. 作者：mbzdf (4星)
**关键亮点**：详细分析了贪心策略的合理性，并特别处理了前导零的情况，确保代码的鲁棒性。
**个人心得**：作者强调了在处理前导零时需要注意的细节，确保不会因为前导零而影响表达式的值。
**核心代码**：
```cpp
for(int i=0;i<len;++i)
{
    if(a[i]=='+')
    {
        t=0;
    }
    if(a[i]=='-')
    {
        t=1;
        cout<<'-';
        continue;
    }
    if(t && a[i-1]!='-')
    {
        cout<<'+';
        if(a[i]=='0')
        {
            if(a[i+1]!='-' && a[i+1]!='+')
            {
                cout<<a[i];
                continue;
            }
        }
        t=0;
    }
    cout<<a[i];
}
```

#### 3. 作者：_Nancy_ (4星)
**关键亮点**：代码结构清晰，处理前导零的方式简洁有效，逻辑严谨。
**个人心得**：作者通过举例说明了如何处理前导零，确保表达式的值最大化。
**核心代码**：
```cpp
for(int i=0;i<lens;i++)
{
    if(s[i]=='-') 
    {
        cout<<s[i];
        i++;
        cout<<s[i];
        bool f=false;
        if(s[i+1]>='0'&&s[i+1]<='9') i++;
        else continue;
        while(s[i]>='0'&&s[i]<='9')
        {
            if(s[i]=='0')
            {
                if(!f) cout<<'+'<<s[i];
                else cout<<s[i];
            }
            else
            {
                if(!f) 
                {
                    cout<<'+'<<s[i];
                    f=true;
                }
                else cout<<s[i];
            }
            if(s[i+1]>='0'&&s[i+1]<='9') i++;
            else break;
        }
    }
    else cout<<s[i];
}
```

### 最优关键思路或技巧
1. **贪心策略**：在减法操作后的数字中尽可能早地添加加号，以最大化表达式的值。
2. **前导零处理**：在遇到前导零时，确保每个零都通过加号分隔，避免影响表达式的值。

### 可拓展之处
类似的问题可以通过贪心策略来解决，特别是在需要最大化或最小化某个值时。例如，在分配资源或优化路径时，贪心算法可以快速找到局部最优解，进而逼近全局最优解。

### 推荐题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：32.80秒