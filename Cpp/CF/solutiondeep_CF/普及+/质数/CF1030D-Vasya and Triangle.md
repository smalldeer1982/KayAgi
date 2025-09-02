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



### 题目翻译
# Vasya 和三角形

## 题目描述

Vasya 有三个整数 $n$、$m$ 和 $k$。他希望找到三个整点 $(x_1, y_1)$、$(x_2, y_2)$ 和 $(x_3, y_3)$，使得这些点满足 $0 \le x_1, x_2, x_3 \le n$，$0 \le y_1, y_2, y_3 \le m$，且由这些点组成的三角形的面积等于 $\frac{nm}{k}$。

帮助 Vasya 找到这样的点（如果可能）。若存在多个解，输出任意一个。

## 说明/提示

第一个样例中三角形面积应为 $\frac{nm}{k} = 4$。输出中的三角形如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)

第二个样例中没有面积为 $\frac{16}{7}$ 的三角形。

---

### 题解分析与结论

#### 通用结论
1. **面积合法性**：由皮克定理，整点三角形面积的两倍必为整数。因此若 $2nm \not\equiv 0 \pmod{k}$，直接输出无解。
2. **构造方法**：通过构造直角点在 $(0,0)$ 的直角三角形，设另两点为 $(a,0)$ 和 $(0,b)$，满足 $ab = \frac{2nm}{k}$。核心在于将 $k$ 的质因数分解到 $a$ 和 $b$ 的取值范围内。

---

### 高分题解推荐

#### 题解1：作者 da32s1da（4星）
**关键思路**：  
- 利用最大公约数分解因子，设 $x = \frac{2n}{\gcd(2n,k)}$，若 $x > n$ 则调整 $x$ 和 $y$ 的比例。
- 时间复杂度 $O(\log n)$，仅需一次 GCD 计算。

**代码核心**：
```cpp
#include<cstdio>
typedef long long LL;
LL n,m,k,X,Y;
LL gcd(LL u,LL v){return v?gcd(v,u%v):u;}

int main(){
    scanf("%I64d%I64d%I64d",&n,&m,&k);
    if(2*n*m % k != 0) { puts("NO"); return 0; }
    puts("YES");
    LL g = gcd(2*n, k);
    X = (2*n) / g;
    k /= g;
    Y = m / k;
    if(X > n) { X /= 2; Y *= 2; }
    printf("0 0\n%lld 0\n0 %lld\n", X, Y);
}
```

---

#### 题解2：作者 DJRzjl（4星）
**关键思路**：  
- 分 $k$ 为奇偶讨论：偶数时直接分解 $\frac{k}{2}$ 的因子，奇数时分配因子后调整乘2。
- 代码通过质因数分解实现因子分配。

**代码核心**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;

pair<int,int> solve(int x,int n,int m){
    // 质因数分解并分配因子到n和m
    int T=sqrt(x);
    for(int i=2;i<=T;i++)
        while(x%i==0){
            if(n%i==0) n/=i;
            else m/=i;
            x/=i;
        }
    if(x>1) (n%x==0) ? n/=x : m/=x;
    return {n,m};
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(2ll*n*m%k) return puts("NO")&0;
    puts("YES");
    pair<int,int> res;
    if(k%2==0) res = solve(k/2,n,m);
    else {
        res = solve(k,n,m);
        (res.first*2 <= n) ? res.first*=2 : res.second*=2;
    }
    printf("0 0\n0 %d\n%d 0\n", res.second, res.first);
}
```

---

#### 题解3：作者 我打（4星）
**关键思路**：  
- 直接分解 $k$ 的质因数，优先分配到 $n$ 或 $m$ 中，最后处理乘2的调整。

**代码核心**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;

int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(2ll*n*m%k) return puts("NO")&0;
    puts("YES");
    int a=n, b=m;
    if(k%2==0) k/=2;
    else {
        for(int i=2;i<=k;i++)
            while(k%i==0){
                if(a%i==0) a/=i;
                else b/=i;
                k/=i;
            }
        (a*2<=n) ? a*=2 : b*=2;
    }
    printf("0 0\n%d 0\n0 %d\n",a,b);
}
```

---

### 关键技巧总结
1. **数论分解**：利用 GCD 或质因数分解将 $k$ 的因子合理分配到 $n$ 和 $m$ 中。
2. **奇偶调整**：根据 $k$ 的奇偶性选择不同的乘2策略，确保解在范围内。
3. **极值构造**：固定直角点在原点简化计算，利用直角三角形面积公式快速验证。

---

### 类似题目推荐
1. [CF1183H](https://codeforces.com/problemset/problem/1183/H) - 数论构造
2. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516) - 扩展欧几里得
3. [P1447 能量采集](https://www.luogu.com.cn/problem/P1447) - 格点数与面积关系

---
处理用时：66.82秒