# 题目信息

# Ralph And His Magic Field

## 题目描述

Ralph has a magic field which is divided into $ n×m $ blocks. That is to say, there are $ n $ rows and $ m $ columns on the field. Ralph can put an integer in each block. However, the magic field doesn't always work properly. It works only if the product of integers in each row and each column equals to $ k $ , where $ k $ is either 1 or -1.

Now Ralph wants you to figure out the number of ways to put numbers in each block in such a way that the magic field works properly. Two ways are considered different if and only if there exists at least one block where the numbers in the first way and in the second way are different. You are asked to output the answer modulo $ 1000000007=10^{9}+7 $ .

Note that there is no range of the numbers to put in the blocks, but we can prove that the answer is not infinity.

## 说明/提示

In the first example the only way is to put -1 into the only block.

In the second example the only way is to put 1 into every block.

## 样例 #1

### 输入

```
1 1 -1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 3 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 3 -1
```

### 输出

```
16
```

# AI分析结果

### 题目内容
# Ralph And His Magic Field

## 题目描述
Ralph有一块魔法田地，被划分为$n×m$个区块。也就是说，这块田地上有$n$行和$m$列。Ralph可以在每个区块中放入一个整数。然而，这块魔法田地并非总是能正常运作。只有当每行和每列中整数的乘积都等于$k$（$k$的值为$1$或$-1$）时，它才能正常工作。

现在Ralph希望你找出，以何种方式在每个区块中放置数字，才能使魔法田地正常运作。当且仅当至少存在一个区块，其中两种放置方式的数字不同时，这两种方式才被视为不同。你需要输出答案对$1000000007 = 10^{9}+7$取模的结果。

注意，放置在区块中的数字没有范围限制，但我们可以证明答案不是无穷大。

## 说明/提示
在第一个示例中，唯一的方法是在唯一的区块中放入 -1。

在第二个示例中，唯一的方法是在每个区块中放入1。

## 样例 #1
### 输入
```
1 1 -1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
1 3 1
```
### 输出
```
1
```

## 样例 #3
### 输入
```
3 3 -1
```
### 输出
```
16
```

### 算法分类
数学

### 综合分析与结论
所有题解思路基本一致，均基于以下要点：因为$k$取值为$1$或$-1$，所以矩阵中的数只能是$1$或$-1$。前$n - 1$行和$m - 1$列的数可任意填，通过最后一行和最后一列的数来调整，使每行每列乘积为$k$ ，根据乘法原理，方案数为$2^{(n - 1)(m - 1)}$。同时都考虑到当$|n - m|$为奇数且$k = -1$时无解。由于指数较大，都使用快速幂来计算结果。各题解主要差异在于代码实现细节、输入输出方式及对无解情况的判断表述略有不同。

### 所选的题解
- **作者：liuyi0905 (5星)**
    - **关键亮点**：思路清晰，先阐述整体思路，通过举例说明，再分析无解情况，最后给出简洁且注释详细的代码。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,k;
int power(int a,int b){//快速幂模版
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;//如果指数为奇数，答案就与相乘
        a=a*a%mod,b>>=1;//将b不断除以二，a不断相乘
    }
    return ans;
}
signed main(){
    cin>>n>>m>>k;
    if(abs(n-m)%2&&!~k)puts("0");//特判无解的情况
    else cout<<power(power(2,n-1),m-1);//输出答案
    return 0;
}
```
    - **核心实现思想**：定义快速幂函数`power`计算幂次，在`main`函数中输入`n`、`m`、`k`，先判断无解情况，有解时通过两次调用快速幂函数计算$2^{(n - 1)(m - 1)}$ 。

- **作者：Stars_visitor_tyw (4星)**
    - **关键亮点**：思路阐述清晰，详细说明有解和无解的原理，还给出判断$n$和$m$一奇一偶的技巧，并提供详细代码。
    - **重点代码**：
```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
#define int long long
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mod=1e9+7;
int qpow(int a,int b)//快速幂模板
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
signed main()
{
    int n,m,k;
    n=read();
    m=read();
    k=read();
    if(abs(n-m)%2==1&&k==-1)
    {
        cout<<0;
    }
    else 
    {
        cout<<qpow(qpow(2,n-1),m-1);
    }
    return 0;
}
```
    - **核心实现思想**：自定义`read`函数输入数据，`qpow`函数实现快速幂运算，在`main`函数中输入`n`、`m`、`k` ，判断无解情况后，通过两次调用`qpow`函数计算方案数。

- **作者：Epoch_L (4星)**
    - **关键亮点**：先分析数据范围得出关键结论，再阐述有解和无解情况，代码注释清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x)
{
    char ch=getchar();
    int r=0,w=1;
    while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
    while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
    x=r*w;
}
const int mod=1e9+7;
int get(int a,int b)//快速幂
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
main()
{
    int n,m,k;
    read(n);
    read(m);
    read(k);
    if(abs(n-m)%2==1&&k==-1)cout<<0;//无解
    else cout<<get(get(2,n-1),m-1);
    return 0;
}
```
    - **核心实现思想**：通过自定义`read`函数输入数据，`get`函数实现快速幂，在`main`函数中输入`n`、`m`、`k` ，判断无解情况后，两次调用`get`函数计算$2^{(n - 1)(m - 1)}$ 得出方案数。

### 最优关键思路或技巧
- **数学分析**：通过分析$k$的取值以及行列乘积的要求，得出矩阵中元素只能是$1$或$-1$，并且前$n - 1$行和$m - 1$列可自由填充的结论，利用乘法原理计算方案数。
- **快速幂优化**：由于指数$(n - 1)(m - 1)$可能很大，使用快速幂算法优化计算幂次的过程，避免计算过程中数据溢出。

### 拓展
同类型题目通常围绕矩阵元素的特定约束条件，计算满足条件的方案数。类似算法套路是先通过对约束条件的数学分析，找出可自由变化的部分和受限制部分，再利用乘法原理等计算方案数，过程中可能会用到快速幂等优化计算。

### 洛谷推荐题目
- [P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)：专门考察快速幂算法的应用。
- [P1577 切绳子](https://www.luogu.com.cn/problem/P1577)：结合数学分析和二分查找解决实际问题，与本题类似在于需要对问题进行数学建模。
- [P2149 [SDOI2009]Elaxia的路线](https://www.luogu.com.cn/problem/P2149)：涉及图论和数学分析，通过分析图中路径的约束条件，利用数学原理计算方案数，和本题思路类似在于对条件的分析与利用。 

---
处理用时：63.10秒