# 题目信息

# Digits Permutations

## 题目描述

Andrey's favourite number is $ n $ . Andrey's friends gave him two identical numbers $ n $ as a New Year present. He hung them on a wall and watched them adoringly.

Then Andrey got bored from looking at the same number and he started to swap digits first in one, then in the other number, then again in the first number and so on (arbitrary number of changes could be made in each number). At some point it turned out that if we sum the resulting numbers, then the number of zeroes with which the sum will end would be maximum among the possible variants of digit permutations in those numbers.

Given number $ n $ , can you find the two digit permutations that have this property?

## 样例 #1

### 输入

```
198
```

### 输出

```
981
819
```

## 样例 #2

### 输入

```
500
```

### 输出

```
500
500
```

# AI分析结果

### 题目内容
# 数字排列

## 题目描述
安德烈最喜欢的数字是 $n$ 。他的朋友们送给他两个相同的数字 $n$ 作为新年礼物。他把它们挂在墙上，满心欢喜地看着。

后来，安德烈看腻了同样的数字，于是他开始先对其中一个数字交换数位，接着对另一个数字交换数位，然后又对第一个数字交换数位，如此反复（每个数字都可以进行任意次数的交换）。在某个时刻，发现如果将得到的两个数字相加，那么在这些数字所有可能的数位排列组合中，这个和的末尾零的个数将达到最多。

给定数字 $n$ ，你能找出具有此属性的两个数位排列吗？

## 样例 #1
### 输入
```
198
```
### 输出
```
981
819
```
## 样例 #2
### 输入
```
500
```
### 输出
```
500
500
```

### 算法分类
构造

### 综合分析与结论
三道题解思路大致相同，均基于对数字相加末尾产生零的规律分析来构造满足条件的数字排列。核心思路是先确定相加为10的一对数字，再确定相加为9的多对数字，最后处理末尾的0。主要难点在于如何选择相加为10的数字，使得对后续相加为9的数字组合影响最小，从而保证末尾零的个数最多。ZLCT的题解通过函数封装和枚举优化，代码结构清晰，逻辑严谨；Light_Pursuer和Allanljx的题解思路类似，代码实现上采用双端队列存储答案，但在代码可读性和逻辑封装上稍逊一筹。

### 所选的题解
 - **ZLCT题解** ：★★★★
    - **关键亮点**：通过`get`函数计算不同枚举情况下末尾零的个数，逻辑清晰，代码优雅，对细节处理得当，如对特殊情况`ans == 0`的处理。
```cpp
#include<bits/stdc++.h>
using namespace std;
string n,p1,p2;
int num[10],num2[10],num3[10],ans,ansid,now0,f0;
int get(int x){
    int res=0;
    for(int i=0;i<=9;++i){
        num2[i]=num3[i]=num[i];
    }
    num2[x]--;num3[10-x]--;
    if(num2[x]<0||num3[10-x]<0)return 0;
    res=1;
    for(int i=0;i<=9;++i){
        res+=min(num2[i],num3[9-i]);
        int d=min(num2[i],num3[9-i]);
        for(int j=1;j<=d;++j){
            num2[i]--;num3[9-i]--;
        }
    }
    now0=min(num2[0],num3[0]);
    return res+now0;
}
void make(int x){
    for(int i=0;i<=9;++i){
        num2[i]=num[i];
    }
    num[x]--;num2[10-x]--;
    for(int i=1;i<=f0;++i){
        p1+='0';p2+='0';num[0]--;num2[0]--;
    }
    p1+=char(x+'0');p2+=char(10-x+'0');
    for(int i=0;i<=9;++i){
        while(num[i]&&num2[9-i]){
            p1+=char(i+'0');p2+=char(9-i+'0');
            num[i]--;num2[9-i]--;
        }
    }
    for(int i=0;i<=9;++i){
        while(num[i]){
            p1+=char(i+'0');num[i]--;
        }
    }
    for(int i=0;i<=9;++i){
        while(num2[i]){
            p2+=char(i+'0');num2[i]--;
        }
    }
}
signed main(){
    cin>>n;
    for(char c:n){
        num[c-'0']++;
    }
    for(int i=1;i<=5;++i){
        int g=get(i);
        if(g>ans){
            ansid=i;
            ans=g;
            f0=now0;
        }
    }
    if(ans==0){
        sort(n.begin(),n.end(),greater<char>());
        cout<<n<<'\n'<<n<<'\n';
        return 0;
    }
    make(ansid);
    reverse(p1.begin(),p1.end());
    reverse(p2.begin(),p2.end());
    cout<<p1<<'\n'<<p2<<'\n';
    return 0;
}
```
核心代码实现思想：`get`函数用于计算以数字`x`和`10 - x`作为末尾相加为10的数时，能产生的末尾零的个数。`make`函数根据`get`函数得到的最优结果，构造出两个满足条件的数字排列。主函数通过枚举确定最优的末尾相加为10的数字，然后调用`make`函数生成结果并输出。

### 最优关键思路或技巧
通过分析数字相加末尾产生零的规律，采用先确定末尾相加为10的数字，再确定相加为9的数字，最后处理末尾0的构造方法。同时，通过函数封装和合理枚举，优化代码结构和逻辑，提高可读性和可维护性。

### 可拓展思路
此类题目属于数字构造类问题，类似套路是深入分析数字运算规律，根据题目要求构造满足条件的数字组合。常见的拓展方向有改变数字运算规则（如乘法、除法），或者改变条件限制（如要求和的末尾为特定数字组合等）。

### 洛谷相似题目推荐
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464)

---
处理用时：57.82秒