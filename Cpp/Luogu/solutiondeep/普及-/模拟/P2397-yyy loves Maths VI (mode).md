# 题目信息

# yyy loves Maths VI (mode)

## 题目背景

自从上次 redbag 用加法好好的刁难过了 yyy 同学以后，yyy 十分愤怒。  
他还击给了 redbag 一题，但是这题他惊讶的发现自己居然也不会，所以只好找你


## 题目描述

一共有 $n$ 个正整数 $a_i$，他让 redbag 找众数。他还特意表示，这个众数出现次数超过了一半。  


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 2\times 10^6$，$a_i \in [1,2^{31})$。

有人想水过,但我告诉你这空间是不够的。

//kkksc03偷偷地说：你随便输出一个数字吧，都有1/2的几率。不过这可是乐多赛，值得不值得你看着办。所以最好想一想正解。


## 样例 #1

### 输入

```
5
2 3 3 3 3```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
本题要求在空间限制下找出出现次数超过一半的众数。多数题解采用摩尔投票法，利用众数出现次数超过一半的特性，通过抵消不同数对来确定众数。部分题解从二进制位统计、随机化、骗分等角度出发，但从思路清晰度、代码可读性和优化程度综合看，多数题解质量有待提升。

### 所选的题解
- **作者：PauGasol (赞：137)  星级：4星**
    - **关键亮点**：思路清晰，以形象的“小房子”比喻解释摩尔投票法，代码简洁明了。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
int n,m;
int house,cnt;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m);
        if(house==m)cnt++;
        if(cnt==0){
            house=m;cnt++;
        }
        if(house!=m){
            cnt--;
        }
    }
    printf("%d",house);
    return 0;
}
```
    - **核心思想**：用house记录当前可能的众数，cnt记录其出现次数。读入数字，若与house相同则cnt加1，若cnt为0则更新house为当前数字并设cnt为1，若与house不同则cnt减1，最后house即为众数。
- **作者：鸩羽 (赞：30)  星级：4星**
    - **关键亮点**：详细阐述摩尔投票法思想，通过打架情景类比帮助理解，代码注释详尽。
    - **个人心得**：初看无思路，先给出会炸空间的排序做法得40分，后通过看题解学习到摩尔投票法。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int n,ls;
    int ans,js=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&ls);
        if(js==0) ans=ls;
        if(ans==ls) js++;
        if(ans!=ls) js--;
    } 
    printf("%d",ans);
    return 0;
}
```
    - **核心思想**：用ans记录当前可能众数，js为计数器。读入数字，若js为0则更新ans为当前数；若与ans相同则js加1，不同则js减1，最终ans即为众数。
- **作者：leaves_ (赞：12)  星级：4星**
    - **关键亮点**：清晰介绍摩尔投票法原理，通过举例说明算法正确性，代码简洁易懂。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
int n;
int l;
int main()
{
    scanf("%d",&n);
    int cnt=0;
    int mina;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&l);
        if(cnt==0)
        {
            mina=l;
            cnt=1;    
        }
        else cnt+=(l==mina)?1:-1;
    }
    printf("%d",mina);
    return 0;
}
```
    - **核心思想**：cnt为计数器，mina记录当前可能众数。读入数字，若cnt为0则更新mina并设cnt为1，若与mina相同则cnt加1，不同则cnt减1，最后mina即为众数。

### 最优关键思路或技巧
摩尔投票法是解决本题的关键技巧，利用众数出现次数超过一半的条件，通过抵消不同数对，最终剩下的数即为众数。这种基于数据特性的抵消思想，避免了排序或大规模数组统计带来的空间问题。

### 可拓展之处
类似题目可拓展到求出现次数超过1/3、1/4等情况，原理类似摩尔投票法，但需记录多个候选数及对应次数。例如求出现次数超过1/3的数，需记录两个候选数及对应次数，每次读入数字，若与候选数相同则对应次数加1，若次数为0则更新候选数，不同则所有候选数次数减1。

### 推荐洛谷题目
- [P1138 第k小整数](https://www.luogu.com.cn/problem/P1138)：可利用类似思想在不排序情况下找第k小整数。
- [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)：虽非直接找众数，但可锻炼对数据特性利用及算法优化能力。
- [P1980 计数问题](https://www.luogu.com.cn/problem/P1980)：通过统计数字出现次数，可类比本题众数统计思路。 

---
处理用时：70.38秒