# 题目信息

# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3
```

### 输出

```
YES
1 0
2 3
4 1
```

## 样例 #2

### 输入

```
4 4 7
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# Vasya和三角形

## 题目描述
Vasya得到了三个整数$n$、$m$和$k$。他想找到三个整数点$(x_1, y_1)$、$(x_2, y_2)$、$(x_3, y_3)$，使得$0 \leq x_1, x_2, x_3 \leq n$，$0 \leq y_1, y_2, y_3 \leq m$，并且由这些点构成的三角形面积等于$\frac{nm}{k}$。

请帮助Vasya！找到这样的点（如果可能的话）。如果有多个解决方案，输出其中任何一个。

## 说明/提示
在第一个示例中，三角形的面积应该等于$\frac{nm}{k} = 4$。输出中提到的三角形如下图所示：
![图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)
在第二个示例中，不存在面积为$\frac{nm}{k} = \frac{16}{7}$的三角形。

## 样例 #1
### 输入
```
4 3 3
```
### 输出
```
YES
1 0
2 3
4 1
```

## 样例 #2
### 输入
```
4 4 7
```
### 输出
```
NO
```

### 综合分析与结论
所有题解的核心思路都是基于整点三角形面积性质，先判断是否有解，再构造满足面积要求的三角形。
1. **思路**：利用整点三角形面积的两倍是整数这一性质，判断$k$是否整除$2nm$，若不整除则无解。有解时，通过构造直角顶点在原点的直角三角形，设另外两点为$(a, 0)$和$(0, b)$，使$ab = \frac{2nm}{k}$来求解。
2. **算法要点**：根据$k$的奇偶性对其质因数进行枚举，将质因数分配到$n$和$m$中以得到合适的$a$和$b$。
3. **解决难点**：难点在于证明存在满足$ab = \frac{2nm}{k}$且$a \leq n$，$b \leq m$的整数对$(a, b)$。不同题解通过不同方式证明，如利用$k$的奇偶性分析质因数分配可行性等。

### 所选的题解
#### 作者：da32s1da (5星)
- **关键亮点**：思路清晰，先给出一个整点三角形面积可表示范围的结论并证明，再据此判断无解情况，通过巧妙的$x$、$y$取值构造出解，代码简洁明了。
- **重点代码**：
```cpp
#include<cstdio>
typedef long long LL;
LL n,m,k,X,Y;
LL gcd(LL u,LL v){return v?gcd(v,u%v):u;}
int main(){
    scanf("%I64d%I64d%I64d",&n,&m,&k);
    if(k/gcd(n*m,k)>2){//特判无解
        puts("NO");
        return 0;
    }
    puts("YES");
    printf("0 0\n");//原点
    X=(2*n)/gcd(2*n,k);
    if(X>n)X/=2,m*=2;//调整解
    k/=gcd(2*n,k);
    Y=m/k;
    printf("%I64d 0\n",X);
    printf("0 %I64d\n",Y);
}
```
**核心实现思想**：先通过`gcd`函数判断无解情况。有解时，先计算出初始的$X$，若$X$大于$n$则进行调整，同时调整$m$，最后计算出$Y$，输出三个顶点坐标。

#### 作者：chen_hx (4星)
- **关键亮点**：提出一种$O(1)$的构造方法，从不同角度思考问题，先根据$n$与$x$（$x = \frac{n \times m \times 2} k$）的大小关系确定底边，再通过等积变形和坐标调整得到满足条件的三角形。
- **重点代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch))f^=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return f?x:-x;
}

int n,m,k,s,x,y;
signed main(){
    n=read(),m=read(),k=read();
    s=n*m*2;
    if(s%k)return 0&puts("NO");
    else puts("YES");
    s/=k;
    puts("0 0");
    if(n>s){
        printf("%lld 0\n",s);
        printf("%lld 1\n",s);
        return 0;
    }
    else{
        printf("%lld 1\n",n);
        int tmp=ceil((1.00*s)/(1.00*n));
        y=tmp*n-s;
        printf("%lld %lld\n",y,tmp);
    }
}
```
**核心实现思想**：先读入数据，判断无解情况。有解时，根据$n$与$s$（$s=\frac{2nm}{k}$）的大小关系，分别确定不同的顶点坐标。

#### 作者：wjyyy (4星)
- **关键亮点**：详细证明了格点三角形面积是$\frac{1}{2}$的倍数以及存在满足条件整数对$(a, b)$的结论，逻辑严谨，代码通过优化枚举起点避免$TLE$。
- **重点代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
long long n,m,k;
long long gcd(long long a,long long b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%I64d%I64d%I64d",&n,&m,&k);
    long long tt=n>m?n:m;
    int flag=(n>=m);
    k=k;
    long long t=n>m?n:m;
    n=n*m;
    long long tmp=gcd(n,k);
    n/=tmp;
    k/=tmp;
    if(k>2)
    {
        puts("NO");
        return 0;
    }
    if(k==1)
        n*=2;
    long long up=sqrt(n)+1;
    for(int i=(n/tt)?(n/tt):1;i<=up;++i)
        if(n%i==0)
            if(n/i<=t)
            {
                n=n/i;
                m=i;
                break;
            }
    puts("YES");
    puts("0 0");
    if(flag)
    {
        printf("%I64d 0\n",n);
        printf("0 %I64d\n",m);
    }
    else
    {
        printf("%I64d 0\n",m);
        printf("0 %I64d\n",n);
    }
    return 0;
}
```
**核心实现思想**：先通过`gcd`函数化简$n$和$k$，判断无解情况。有解时，通过优化后的枚举找到满足条件的$n$和$m$作为三角形两条直角边长度，输出顶点坐标。

### 最优关键思路或技巧
1. **利用整点三角形面积性质**：整点三角形面积的两倍是整数，以此判断是否有解，缩小问题范围。
2. **构造直角三角形**：通过构造直角顶点在原点的直角三角形简化问题，将问题转化为寻找满足特定等式的整数对。
3. **根据$k$的性质处理质因数**：根据$k$的奇偶性对其质因数进行分配，从而找到符合条件的三角形边长。

### 可拓展之处
同类型题可关注涉及几何与数论结合的问题，特别是在给定区域内构造满足特定面积或边长关系的几何图形问题。类似算法套路为利用几何图形性质（如面积公式、边长关系等）结合数论知识（如整除、质因数分解等）进行求解。

### 推荐题目
1. [P1072  Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)：通过数论知识求解满足特定最大公约数和最小公倍数关系的数。
2. [P2152  [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：考察大整数的最大公约数计算，涉及数论和高精度运算。
3. [P1463  [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：结合数论中约数个数的性质求解反素数问题。 

---
处理用时：40.19秒