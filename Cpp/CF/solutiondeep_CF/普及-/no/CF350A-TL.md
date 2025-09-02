# 题目信息

# TL

## 题目描述

Valera wanted to prepare a Codesecrof round. He's already got one problem and he wants to set a time limit (TL) on it.

Valera has written $ n $ correct solutions. For each correct solution, he knows its running time (in seconds). Valera has also wrote $ m $ wrong solutions and for each wrong solution he knows its running time (in seconds).

Let's suppose that Valera will set $ v $ seconds TL in the problem. Then we can say that a solution passes the system testing if its running time is at most $ v $ seconds. We can also say that a solution passes the system testing with some "extra" time if for its running time, $ a $ seconds, an inequality $ 2a<=v $ holds.

As a result, Valera decided to set $ v $ seconds TL, that the following conditions are met:

1. $ v $ is a positive integer;
2. all correct solutions pass the system testing;
3. at least one correct solution passes the system testing with some "extra" time;
4. all wrong solutions do not pass the system testing;
5. value $ v $ is minimum among all TLs, for which points $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ hold.

Help Valera and find the most suitable TL or else state that such TL doesn't exist.

## 样例 #1

### 输入

```
3 6
4 5 2
8 9 6 10 7 11
```

### 输出

```
5```

## 样例 #2

### 输入

```
3 1
3 4 5
6
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
#### TL
#### 题目描述
瓦莱拉想准备一场Codesecrof竞赛。他已经有了一道题目，并且想为这道题设置一个时间限制（TL）。

瓦莱拉已经编写了$n$个正确的解法。对于每个正确解法，他都知道其运行时间（以秒为单位）。瓦莱拉还编写了$m$个错误的解法，并且对于每个错误解法，他也知道其运行时间（以秒为单位）。

假设瓦莱拉在题目中设置$v$秒的时间限制。那么我们可以说，如果一个解法的运行时间最多为$v$秒，它就能通过系统测试。我们还可以说，如果对于一个解法的运行时间$a$秒，不等式$2a \leq v$成立，那么这个解法就能通过系统测试并获得一些“额外”时间。

结果，瓦莱拉决定设置$v$秒的时间限制，使得满足以下条件：
1. $v$是一个正整数；
2. 所有正确解法都能通过系统测试；
3. 至少有一个正确解法能通过系统测试并获得一些“额外”时间；
4. 所有错误解法都不能通过系统测试；
5. 在满足上述1、2、3、4点的所有时间限制中，$v$是最小的。

帮助瓦莱拉找到最合适的时间限制，否则说明这样的时间限制不存在。
#### 样例 #1
**输入**
```
3 6
4 5 2
8 9 6 10 7 11
```
**输出**
```
5
```
#### 样例 #2
**输入**
```
3 1
3 4 5
6
```
**输出**
```
-1
```
### 算法分类
数学
### 综合分析与结论
所有题解的核心思路都是通过分析题目所给的条件，找出时间限制$v$的取值范围来确定最终结果。主要通过分别找出正确解法的最大、最小运行时间，以及错误解法的最小运行时间，来判断是否存在满足条件的$v$，若存在则求出其最小值。不同题解在具体实现细节和代码风格上有所差异。
### 所选的题解
- **作者：封禁用户 (5星)**
    - **关键亮点**：思路清晰，详细阐述了判断无解情况和求解最小值的逻辑，代码注释详尽，对变量初始化、边界条件判断处理得当。
    - **重点代码**：
```cpp
int a[101],b[101];  
int main()
{
    int n,m;  
    int acmin=100000000,acmax=-100000000,tlemin=100000000;  
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(acmin>a[i])  
        {
            acmin=a[i];
        }
        if(acmax<a[i])  
        {
            acmax=a[i];
        }
    }
    for(int i=1;i<=m;i++)
    {
        cin>>b[i];
        if(tlemin>b[i])  
        {
            tlemin=b[i];
        }
    }
    if(acmax>=tlemin)  
    {
        cout<<"-1";
    }
    else
    {
        if(2*acmin>=tlemin)  
        {
            cout<<"-1";
        }
        else
        {
            cout<<max(acmin*2,acmax);  
        }
    }
    return 0;  
}
```
    - **核心思想**：先读入数据，在循环中分别找出正确解法的最小、最大运行时间`acmin`、`acmax`和错误解法的最小运行时间`tlemin`。然后根据条件判断是否无解，若有解则输出`acmin*2`和`acmax`中的较大值。
- **作者：orange166 (4星)**
    - **关键亮点**：简洁明了，指出甚至无需开数组，直接在输入时求最大最小值，代码简洁高效，同时给出了扫一遍求最小值的思路。
    - **重点代码**：
```cpp
int a,b,maxn=-1,minn=q,minn2=q,tmp,s; 
int main(){
    scanf("%d%d",&a,&b);
    for(register int i=1; i<=a; i++){ 
        scanf("%d",&tmp);
        minn=min(tmp,minn);
        maxn=max(tmp,maxn);
    }
    for(register int i=1; i<=b; i++){
        scanf("%d",&tmp);
        minn2=min(tmp,minn2); 
    }
    if(minn2<=maxn || minn2<=minn*2){ 
        printf("-1");
        return 0;
    }
    s=max(minn*2, maxn);  
    printf("%d",s);
    return 0;
}
```
    - **核心思想**：在输入正确解法和错误解法的运行时间时，同步更新正确解法的最小、最大运行时间`minn`、`maxn`以及错误解法的最小运行时间`minn2`。之后根据条件判断是否无解，有解则输出`minn*2`和`maxn`中的较大值。
- **作者：Colead (4星)**
    - **关键亮点**：清晰总结出时间限制$v$的三个限定范围，通过判断范围是否有交集来确定是否有解，逻辑清晰。
    - **重点代码**：
```cpp
long long n,m,maxn=0,minn=99999999,mina=99999999;
long long a[1005],b[1005]={};
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>maxn)maxn=a[i];
        if(a[i]<mina)mina=a[i];
    }
    for(int i=1;i<=m;i++)
    {
        cin>>b[i];
        if(b[i]<minn)minn=b[i];
    }
    if(mina*2>=minn||maxn>=minn)
    {
        cout<<"-1"<<endl;
        return 0;
    }
    else
    {
        cout<<max(maxn,mina*2)<<endl;
    }
    return 0;
}
```
    - **核心思想**：输入数据过程中确定正确解法的最大、最小运行时间`maxn`、`mina`和错误解法的最小运行时间`minn`。依据$v$的限定范围判断是否有解，有解则输出`maxn`和`mina*2`中的较大值。
### 最优关键思路或技巧
通过分析题目条件，总结出时间限制$v$的上下限范围，利用正解的最大、最小运行时间和错解的最小运行时间来判断是否有解以及求解。在实现上，部分题解避免使用数组，直接在输入时同步更新最值，简化代码并提高效率。
### 拓展思路
此类题目属于根据条件确定取值范围并求最值的问题。类似套路可应用于其他需要根据多种限制条件确定某个参数取值的场景，例如资源分配、任务调度等问题中，通过分析各条件对参数的约束，找出符合所有条件的最优解。
### 洛谷相似题目推荐
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及到根据给定规则对序列进行操作并寻找特定状态，与本题根据条件确定最值思路类似。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过分析操作条件对结果的影响，求解最终状态，与本题分析条件确定取值有相似之处。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同购买方案的条件，计算满足需求的最小花费，同样是根据条件求最值的类型。
### 个人心得摘录与总结
- **作者：happybob**：强调注意`for`循环中条件是`<`不是`<=`，否则会WA，表明边界条件处理在编程中的重要性。 

---
处理用时：70.38秒