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

### 题目中文重写
# Vasya和三角形

## 题目描述
Vasya有三个整数 $ n $、$ m $ 和 $ k $。他想找到三个整数点 $ (x_1, y_1) $、$ (x_2, y_2) $、$ (x_3, y_3) $，使得 $ 0 \le x_1, x_2, x_3 \le n $，$ 0 \le y_1, y_2, y_3 \le m $，并且由这些点构成的三角形的面积等于 $ \frac{nm}{k} $。

帮助Vasya！找到这样的点（如果可能的话）。如果有多个解，打印其中任意一个。

## 说明/提示
在第一个样例中，三角形的面积应该等于 $ \frac{nm}{k} = 4 $。输出中提到的三角形如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)
在第二个样例中，不存在面积为 $ \frac{nm}{k} = \frac{16}{7} $ 的三角形。

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
这些题解的核心思路都是先判断是否存在满足条件的三角形，即判断 $k$ 是否能整除 $2nm$，若不能则无解。若有解，都尝试构造一个直角顶点在 $(0, 0)$ 的直角三角形，通过确定另外两个顶点 $(a, 0)$ 和 $(0, b)$ 使得三角形面积为 $\frac{ab}{2}=\frac{nm}{k}$，即 $ab = \frac{2nm}{k}$。

各题解的算法要点和难点对比：
|作者|算法要点|难点|
| ---- | ---- | ---- |
|da32s1da|利用结论判断可表示的面积范围，通过 $gcd$ 计算 $x$ 和 $y$，若 $x$ 大于 $n$ 则进行调整|理解面积表示范围的结论和 $x$、$y$ 的计算调整过程|
|chen_hx|根据 $n$ 和 $x$ 的大小关系构造三角形，若高为小数则用等积变形调整|等积变形调整高为整数的理解和实现|
|DJRzjl|根据 $k$ 的奇偶性枚举质因数，将质因数分配到 $n$ 和 $m$ 上|质因数分配的证明和实现|
|unputdownable|根据 $k$ 的奇偶性构造三角形，若面积需乘 $2$ 则调整顶点|面积乘 $2$ 时顶点调整的推理|
|wjyyy|证明格点三角形面积是 $\frac{1}{2}$ 的倍数，枚举约数确定 $a$ 和 $b$，并进行上下界优化|面积是 $\frac{1}{2}$ 倍数的证明和约数枚举的上下界优化|
|我打|根据 $k$ 的奇偶性枚举质因数，将质因数分配到 $n$ 和 $m$ 上，处理 $2$ 的情况|质因数分配和 $2$ 的处理的证明和实现|
|IMIDAZOLE|枚举 $k$ 的质因数，将质因数整除到 $n$ 或 $m$ 中，处理 $2$ 的情况|质因数整除和 $2$ 的处理的理解|

### 所选题解
- **da32s1da（5星）**
    - 关键亮点：思路清晰，利用面积表示范围的结论快速判断和计算，代码简洁。
    - 核心代码：
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
核心实现思想：先判断是否无解，若有解则通过 $gcd$ 计算 $X$ 和 $Y$，若 $X$ 大于 $n$ 则进行调整，最后输出三个顶点坐标。

- **chen_hx（4星）**
    - 关键亮点：提出 $O(1)$ 的构造方法，通过等积变形解决高为小数的问题。
    - 核心代码：
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
核心实现思想：先判断是否无解，若有解则根据 $n$ 和 $s$ 的大小关系构造三角形，若高为小数则通过等积变形调整顶点坐标。

### 最优关键思路或技巧
- 利用整点三角形面积的两倍一定是整数这一性质，快速判断无解情况。
- 构造直角顶点在 $(0, 0)$ 的直角三角形简化问题。
- 运用 $gcd$ 进行质因数分配和计算，避免枚举质因数的复杂过程。

### 可拓展之处
同类型题可能会改变三角形的限制条件，如要求三角形为等边三角形、等腰三角形等，或者改变平面的限制条件，如在三维空间中构造三角形。类似算法套路可以是先根据几何性质判断是否有解，再通过构造特殊图形来求解。

### 推荐题目
- [P1328 生活大爆炸版石头剪刀布](https://www.luogu.com.cn/problem/P1328)：涉及数学计算和逻辑判断。
- [P1002 [NOIP2002 普及组] 过河卒](https://www.luogu.com.cn/problem/P1002)：需要运用数学方法和动态规划思想。
- [P1047 [NOIP2005 普及组] 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察数学思维和数组操作。

### 个人心得
- **wjyyy**：一开始感觉上下互质可能会出问题，但发现和质数无关，和约分有关。枚举约数时从 $1$ 开始容易 $TLE$，需要进行上下界优化。
总结：做题时不要被表面现象误导，要深入分析问题本质，同时注意算法的复杂度，进行必要的优化。 

---
处理用时：45.09秒