# 题目信息

# Counting Sticks

## 题目描述

When new students come to the Specialized Educational and Scientific Centre (SESC) they need to start many things from the beginning. Sometimes the teachers say (not always unfairly) that we cannot even count. So our teachers decided to teach us arithmetics from the start. And what is the best way to teach students add and subtract? — That's right, using counting sticks! An here's our new task:

An expression of counting sticks is an expression of type:

\[ $ A $ sticks\]\[sign +\]\[ $ B $ sticks\]\[sign =\]\[ $ C $ sticks\] $ (1<=A,B,C) $ . Sign + consists of two crossed sticks: one vertical and one horizontal. Sign = consists of two horizontal sticks. The expression is arithmetically correct if $ A+B=C $ .

We've got an expression that looks like $ A+B=C $ given by counting sticks. Our task is to shift at most one stick (or we can shift nothing) so that the expression became arithmetically correct. Note that we cannot remove the sticks from the expression, also we cannot shift the sticks from the signs + and =.

We really aren't fabulous at arithmetics. Can you help us?

## 说明/提示

In the first sample we can shift stick from the third group of sticks to the first one.

In the second sample we cannot shift vertical stick from + sign to the second group of sticks. So we cannot make a - sign.

There is no answer in the third sample because we cannot remove sticks from the expression.

In the forth sample the initial expression is already arithmetically correct and that is why we don't have to shift sticks.

## 样例 #1

### 输入

```
||+|=|||||
```

### 输出

```
|||+|=||||
```

## 样例 #2

### 输入

```
|||||+||=||
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
|+|=||||||
```

### 输出

```
Impossible
```

## 样例 #4

### 输入

```
||||+||=||||||
```

### 输出

```
||||+||=||||||
```

# AI分析结果

### 题目内容
# 数火柴棍

## 题目描述
当新学生来到专业教育与科学中心（SESC）时，他们需要从许多事情的开头做起。有时老师们会说（并不总是不公平）我们甚至不会数数。所以我们的老师决定从头开始教我们算术。教学生加减法的最佳方法是什么呢？没错，就是使用火柴棍！这就是我们的新任务：

一个用火柴棍表示的表达式是如下类型的表达式：

\[ $A$ 根火柴棍\]\[符号 +\]\[ $B$ 根火柴棍\]\[符号 =\]\[ $C$ 根火柴棍\]  $(1\leq A,B,C)$。符号 + 由两根交叉的火柴棍组成：一根垂直和一根水平。符号 = 由两根水平火柴棍组成。如果 $A + B = C$，则该表达式在算术上是正确的。

我们得到了一个用火柴棍表示的看起来像 $A + B = C$ 的表达式。我们的任务是最多移动一根火柴棍（或者我们也可以不移动），使该表达式在算术上正确。请注意，我们不能从表达式中移除火柴棍，也不能移动符号 + 和 = 上的火柴棍。

我们在算术方面真的不怎么样。你能帮助我们吗？

## 说明/提示
在第一个示例中，我们可以将第三组火柴棍中的一根火柴棍移动到第一组。

在第二个示例中，我们不能将 + 号中的垂直火柴棍移动到第二组火柴棍中。所以我们不能形成 - 号。

在第三个示例中没有答案，因为我们不能从表达式中移除火柴棍。

在第四个示例中，初始表达式在算术上已经是正确的，所以我们不必移动火柴棍。

## 样例 #1
### 输入
```
||+|=|||||
```
### 输出
```
|||+|=||||
```

## 样例 #2
### 输入
```
|||||+||=||
```
### 输出
```
Impossible
```

## 样例 #3
### 输入
```
|+|=||||||
```
### 输出
```
Impossible
```

## 样例 #4
### 输入
```
||||+||=||||||
```
### 输出
```
||||+||=||||||
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解的核心思路都是先读取等式中三个部分（两个加数与和）的火柴棍数量，然后通过分类讨论判断是否能通过移动一根火柴棍使等式成立。主要的难点在于如何准确读取各部分火柴棍数量，以及当需要移动火柴棍时，如何处理一些特殊情况，如某个加数为1时的移动规则。各题解在实现方式上略有不同，有的通过标志变量判断当前读取的火柴棍属于哪一部分，有的通过查找符号位置来确定各部分长度。代码实现上，部分题解注重代码简洁性，部分则更强调逻辑的清晰展示。

### 所选的题解
- **作者：清小秋ovo（5星）**
    - **关键亮点**：思路清晰，先判断等式本身是否成立，再考虑两种移动火柴棍的情况，且对特殊情况（某个加数为1）处理得当，代码结构清晰，可读性强。
    - **重点代码 - 核心实现思想**：通过遍历输入字符串统计两个加数和和的火柴棍数量，根据不同条件判断并输出结果。
```cpp
//输出函数
void print(int a,int b, int c){
    for(int i=0;i<a;i++)cout<<"|";
    cout<<"+";
    for(int i=0;i<b;i++)cout<<"|";
    cout<<"=";
    for(int i=0;i<c;i++)cout<<"|";
}
int main()
{
   string a;
   cin>>a;
   int n=0,m=0,k=0,plus=0,s=0;
   for(int i=0;i<a.length();i++){
       if(a[i]=='+')plus++;
       if(a[i]=='=')s++;
       if(a[i]=='|'&&plus==0&&s==0)n++;
       if(a[i]=='|'&&plus==1&&s==0)m++;
       if(a[i]=='|'&&plus==1&&s==1)k++;
   }
   if(n+m==k) cout<<a<<endl,exit(0);
   if(n+m+2==k){
           cout<<"|";
           print(n,m,k-1);
           return 0;
   }
   if(n+m==k+2){
       if(n>1){
           print(n-1,m,k+1);
           return 0;
       }if(m>1){
           print(n,m-1,k+1);
           return 0;
       }
   }
   cout<<"Impossible"<<endl; 
}
```
- **作者：Ryan_Yu（4星）**
    - **关键亮点**：通过定义布尔型标志变量来判断火柴棍所属部分，逻辑较为清晰，对不同情况的判断和处理完整。
    - **重点代码 - 核心实现思想**：利用标志变量在遍历字符串时统计各部分火柴棍数量，根据等式成立条件进行相应输出。
```cpp
int main() 
{
    cin>>a;
	al=a.size();
    for(i=0;i<al;i++)
    {
        if(a[i]=='|')
        {
            if(flag1==false)
                n1++;
            if(flag2==false)
                n2++;
            if(flag3==false)
                n3++;
        }
        else if(a[i]=='+')
            {
                flag1=true;
                flag2=false;
            }
        else if(a[i]=='=')
            {
                flag2=true;
                flag3=false;
            }
    }
    if(n1+n2==n3)
    {
        for(i=1;i<=n1;i++)
            cout<<"|";
        cout<<"+";
        for(i=1;i<=n2;i++)
            cout<<"|";
        cout<<"=";
        for(i=1;i<=n3;i++)
            cout<<"|";
        cout<<endl;
    }
    else if(n1+n2-1==n3+1)
    {
        if(n1>n2)
            n1--;
        else
            n2--;
        for(i=1;i<=n1;i++)
            cout<<"|";
        cout<<"+";
        for(i=1;i<=n2;i++)
            cout<<"|";
        cout<<"=";
        for(i=1;i<=n3+1;i++)
            cout<<"|";
        cout<<endl;
    }
    else if(n1+n2+1==n3-1)
    {
        for(i=1;i<=n1+1;i++)
            cout<<"|";
        cout<<"+";
        for(i=1;i<=n2;i++)
            cout<<"|";
        cout<<"=";
        for(i=1;i<=n3-1;i++)
            cout<<"|";
        cout<<endl;
    }
    else
        cout<<"Impossible"<<endl;
	return 0;
}
```
- **作者：__LiChangChao__（4星）**
    - **关键亮点**：先将火柴棍式子转化为数学式子，通过分类讨论三种等式成立的情况，并对特殊情况进行特判，思路简洁明了。
    - **重点代码 - 核心实现思想**：遍历输入字符串统计各部分火柴棍数量，依据不同等式成立条件进行计算和输出。
```cpp
int main() {
	cin>>s;
	for(int i=0; i<s.length(); i++) {
		if(s[i]=='+'||s[i]=='=') {
			cnt++;
			continue;
		}
		sum[cnt]++;
	}
	if(sum[1]+sum[2]==sum[3])return cout<<s,0;
	else {
		if(sum[1]+sum[2]==sum[3]+2) {
			if(sum[1]>1)sum[1]-=1;
			else if(sum[2]>1)sum[2]-=1;
			sum[3]+=1;
		} else if(sum[1]+sum[2]+2==sum[3]) {
			sum[1]+=1;
			sum[3]-=1;
		} else {
			printf("Impossible");
			return 0;
		}
	}
	for(int i=1; i<=sum[1]; i++)printf("|");
	printf("+");
	for(int i=1; i<=sum[2]; i++)printf("|");
	printf("=");
	for(int i=1; i<=sum[3]; i++)printf("|");
}
```

### 最优关键思路或技巧
1. **利用标志变量或符号位置确定各部分火柴棍数量**：这是准确读取输入数据的有效方法，如Ryan_Yu通过标志变量，__LiChangChao__通过符号位置来统计各部分火柴棍数量。
2. **全面的分类讨论**：清晰地列举出等式成立的各种情况，包括等式本身成立，以及左右两边差值为2时的两种移动情况，并对特殊情况（如某个加数为1）进行细致处理。

### 拓展
同类型题通常围绕火柴棍等式、图形变换等场景，通过移动特定数量的火柴棍使等式成立或图形满足某种条件。类似算法套路是先明确规则，然后对各种可能的移动情况进行枚举和判断。

### 相似知识点洛谷题目
1. [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)：通过模拟计算级数和，考察基本的模拟能力。
2. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同购买方案模拟计算最优解，与本题分类讨论思想类似。
3. [P5718 三角形分类](https://www.luogu.com.cn/problem/P5718)：通过模拟三角形边长关系进行分类判断，锻炼分类讨论与模拟实现能力。 

---
处理用时：81.36秒