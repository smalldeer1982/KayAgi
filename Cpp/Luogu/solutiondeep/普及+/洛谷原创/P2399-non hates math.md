# 题目信息

# non hates math

## 题目背景

non习惯将分数化成小数，但在数学中要以分数形式写，不能化成小数

因此non找到了会编程的你，帮助他将小数化回分数


## 题目描述

给出一个小数，将它化成假分数的形式


小数的类型有2种：（不考虑无限不循环小数）

普通小数

循环小数（会给出循环节）

（循环节用( )表示）


## 说明/提示

输入小数的数据范围

0至1000


对于50%的数据保证没有循环节

对于20%的数据需要读入优化


## 样例 #1

### 输入

```
1.32```

### 输出

```
33/25```

## 样例 #2

### 输入

```
1.(3)```

### 输出

```
4/3```

## 样例 #3

### 输入

```
1.0```

### 输出

```
1/1```

# AI分析结果

### 综合分析与结论
这些题解思路总体一致，均根据小数类型（有限小数、纯循环小数、混循环小数）分类讨论，利用数学原理将小数化为分数后约分。
1. **思路**：先分离整数与小数部分，依据小数类型，按特定数学公式计算分子分母。有限小数分母为10的幂次方；纯循环小数分母由循环节位数个9组成；混循环小数分母由循环节位数个9和不循环部分位数个0组成，分子通过小数部分运算得出。最后整数部分乘分母加分子得到最终分子，再约分。
2. **算法要点**：字符串读入小数，遍历字符串判断小数类型、提取整数与小数部分、循环节等信息，按公式计算分子分母并约分。
3. **解决难点**：正确判断小数类型并按对应公式准确计算分子分母。处理混循环小数时，需正确分离不循环与循环部分并运算。

### 题解评分
1. **作者：Soledad_S（4星）**：思路清晰，先无视整数部分分析三种小数情况，定义明确，代码简洁，利用自带`__gcd`函数简化实现，但NOIp不能用。
2. **作者：LZY151114（4星）**：详细分析每种小数情况，思路清晰，代码逻辑强，使用`fgets`读入，`sscanf`提取数据，`gcd`函数约分，代码量适中。
3. **作者：111l（3星）**：介绍原理清晰，代码实现按小数类型处理，使用`scanf`读入，自定义`add_0`、`gcd`函数，但代码稍显冗长，部分逻辑可优化。

### 最优关键思路与技巧
 - **思路**：按小数类型分类讨论，利用数学原理构建分子分母。
 - **技巧**：使用字符串处理输入，方便判断循环节等信息。通过`gcd`函数约分保证结果最简。如LZY151114题解中，利用`sscanf`从字符串提取数据，简洁高效；Soledad_S题解定义清晰，代码结构紧凑。

### 拓展思路
此类题属于数学模拟范畴，类似题目常涉及分数小数互化、进制转换等。解题套路为依据数学原理分类讨论，通过字符串处理输入数据，按规则计算并化简。

### 相似知识点洛谷题目
1. **P1075 [NOIP2012 普及组] 质因数分解**：考察数论知识，需对整数进行分解，与本题处理小数类似，要按规则分类计算。
2. **P1072 [NOIP2009 普及组]  Hankson 的趣味题**：涉及数论中最大公约数与最小公倍数，需按条件分类讨论计算，和本题分类处理小数思路相似。
3. **P1028 [NOIP2001 普及组] 数的计算**：通过对数字按规则进行计算，与本题按小数类型规则计算分子分母类似，锻炼分类处理问题能力。

### 所选高质量题解
1. **作者：Soledad_S（4星）**
    - **关键亮点**：思路清晰，简洁明了地分析三种小数情况，代码实现简短高效。
    - **核心代码**：
```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int a,b,c,blen,clen,l,r,tot;
char s[1005];
int main(){
    int x;
    scanf("%s",&s);
    for(int i=0;i<strlen(s);i++)
        if(!isdigit(s[i])){
            x=i+1;
            break;
        }
        else a=(a<<1)+(a<<3)+s[i]-'0';
    for(int i=x;i<strlen(s);i++)
        if(isdigit(s[i]))tot=(tot<<1)+(tot<<3)+s[i]-'0';
    int bj=0;
    for(int i=x;i<strlen(s);i++)
        if(s[i]=='('){
            bj=1;
            x=i+1;
            break;
        }
        else b=(b<<1)+(b<<3)+s[i]-'0',blen++;
    if(bj)for(int i=x;i<strlen(s);i++)
            if(isdigit(s[i]))c=(c<<1)+(c<<3)+s[i]-'0',clen++;
    if(!c){
        r=pow(10,blen);
        l=b;
        x=__gcd(l,r);
        l/=x;
        r/=x;
        printf("%d/%d\n",a*r+l,r);
    }
    else if(!b){
        r=0;
        for(int i=1;i<=clen;i++)r=(r<<1)+(r<<3)+9;
        l=c;
        x=__gcd(l,r);
        l/=x;
        r/=x;
        printf("%d/%d\n",a*r+l,r);
    }
    else {
        for(int i=1;i<=clen;i++)r=(r<<1)+(r<<3)+9;
        for(int i=1;i<=blen;i++)r=(r<<1)+(r<<3);
        l=tot-b;
        x=__gcd(l,r);
        l/=x;
        r/=x;
        printf("%d/%d\n",a*r+l,r);
    }
    return 0;
}
```
    - **核心实现思想**：先读入字符串，找到整数与小数分界点计算整数部分`a`和整个小数部分`tot`。判断是否有循环节，有则计算循环节`c`及长度`clen`、非循环节`b`及长度`blen`。根据三种小数情况分别计算分子`l`和分母`r`，用`__gcd`函数约分后输出。
2. **作者：LZY151114（4星）**
    - **关键亮点**：详细分析每种小数转化情况，代码逻辑清晰，使用`fgets`和`sscanf`函数处理输入简洁高效。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register
#define il inline
using namespace std;
il ll gcd(ll a,ll b){return (b==0)?a:gcd(b,a%b);}
ll a,lena,fm,fz,dfz,lend,lenfz;
char s[1005];
bool flag=false;
int main(void){
    fgets(s,1005,stdin);
    for(re int i=0;s[i]!='.';++i)lena=i;
    if(s[lena+2]=='('){
        sscanf(s,"%lld.(%lld)",&a,&fz);
        for(re int i=lena+2;s[i+1]!=')';++i)fm=fm*10+9;
        int x=gcd(fz,fm);fz/=x,fm/=x;
        fz+=a*fm;
        printf("%lld/%lld\n",fz,fm);
    }
    else{
        for(re int i=lena;i<strlen(s);++i)if(s[i]=='(')flag=true,lend=strlen(s)-i-2,lenfz=i-lena-2;
        if(flag){
            sscanf(s,"%lld.%lld(%lld)",&a,&fz,&dfz);
            ll y=fz;
            for(re int i=1;i<=lend;++i)fm=fm*10+9,fz*=10;
            for(re int i=1;i<=lenfz;++i)fm*=10;
            fz+=dfz,fz-=y;y=gcd(fz,fm);fz/=y,fm/=y;
            fz+=a*fm;
            printf("%lld/%lld\n",fz,fm);
        }
        else{
            sscanf(s,"%lld.%lld",&a,&fz);
            fm=1;
            for(re int i=lena+2;i<strlen(s);++i)fm*=10;
            ll x=gcd(fz,fm);fz/=x,fm/=x;
            fz+=a*fm;
            printf("%lld/%lld\n",fz,fm);
        }
    }
    return 0;
}
```
    - **核心实现思想**：用`fgets`读入字符串，通过遍历找到整数部分长度。判断小数类型，纯循环小数用`sscanf`提取整数和循环节，计算分母并约分，加上整数部分处理；非纯循环小数和有限小数同样用`sscanf`提取数据，按规则计算分母、分子并约分输出。 

---
处理用时：111.39秒