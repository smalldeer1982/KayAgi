# 题目信息

# [ARC111A] Simple Math 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc111/tasks/arc111_a

正整数 $ N,\ M $ が与えられます。$ \lfloor\ \frac{10^N}{M}\ \rfloor $ を $ M $ で割った余りを求めてください。

  $ \lfloor\ x\ \rfloor $ について $ \lfloor\ x\ \rfloor $ は、 $ x $ を超えない最大の整数を表します。例としては次のようになります。 - $ \lfloor\ 2.5\ \rfloor\ =\ 2 $
- $ \lfloor\ 3\ \rfloor\ =\ 3 $
- $ \lfloor\ 9.9999999\ \rfloor\ =\ 9 $
- $ \lfloor\ \frac{100}{3}\ \rfloor\ =\ \lfloor\ 33.33...\ \rfloor\ =\ 33 $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ M\ \leq\ 10000 $

### Sample Explanation 1

$ \lfloor\ \frac{10^1}{2}\ \rfloor\ =\ 5 $ なので、$ 5 $ を $ 2 $ で割った余りの $ 1 $ を出力します。

## 样例 #1

### 输入

```
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
2 7```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000000000000000 9997```

### 输出

```
9015```

# AI分析结果



### 中文题目重写  
**题目名称**：[ARC111A] Simple Math 2  
**题目描述**  
给定正整数 $N$ 和 $M$，求 $\lfloor \frac{10^N}{M} \rfloor \bmod M$ 的值。  
$\lfloor x \rfloor$ 表示不超过 $x$ 的最大整数。  
**输入格式**：两个整数 $N, M$  
**输出格式**：计算结果  
**样例说明**：  
样例1：输入 1 2，输出 1（计算 $\lfloor 10/2 \rfloor=5$，5 mod 2=1）  
**数据范围**：$1 \leq N \leq 10^{18},\ 1 \leq M \leq 10^4$  

---

### 算法分类  
数学（模运算性质 + 快速幂）  

---

### 题解分析与结论  
所有题解均基于以下核心数学推导：  
$$\lfloor \frac{10^N}{M} \rfloor \bmod M = \lfloor \frac{10^N \bmod M^2}{M} \rfloor \bmod M$$  
**关键思路**：  
1. 将原式转化为对 $M^2$ 取模，避免计算超大数的 $10^N$  
2. 使用快速幂计算 $10^N \bmod M^2$  
3. 计算结果除以 $M$ 的整数部分即为答案  

**解决难点**：  
- 发现 $10^N \bmod M^2$ 的等价性需要数学直觉  
- 处理 $N$ 超大时的高效计算  

---

### 高星题解推荐  
#### 1. Pink_Cut_Tree（⭐⭐⭐⭐⭐）  
**亮点**：  
- 完整推导数学等价式，给出清晰证明  
- 代码简洁高效，无冗余逻辑  
```cpp
#include<iostream>
#define ll long long
ll ksm(ll x,ll y,ll p){
    ll ans=1%p;
    while(y){
        if(y&1) ans=ans*x%p;
        x=x*x%p; y>>=1;
    }
    return ans;
}
int main(){
    ll n,m; std::cin>>n>>m;
    std::cout<<ksm(10,n,m*m)/m;
}
```

#### 2. PineappleSummer（⭐⭐⭐⭐）  
**亮点**：  
- 同时给出 Python 单行实现，突显算法本质  
- 数学公式排版清晰  
```python
n, m = map(int, input().split())
print(pow(10, n, m * m) // m)
```

#### 3. ZXXS（⭐⭐⭐⭐）  
**亮点**：  
- 代码规范，使用标准快速幂模板  
- 强调 long long 类型必要性  
```cpp
int qpow(int x,int p){
    int s=1;
    while(p){
        if(p&1) s=s*x%(m*m);
        x=x*x%(m*m); p>>=1;
    }
    return s;
}
```

---

### 关键技巧总结  
1. **模平方转换**：将大数取模问题转化为模 $M^2$，利用 $\frac{a \bmod kM}{M} \equiv \lfloor \frac{a}{M} \rfloor \bmod M$  
2. **快速幂优化**：计算 $10^N \bmod M^2$ 时时间复杂度为 $O(\log N)$  
3. **边界处理**：当 $M=1$ 时特判避免除以零  

---

### 同类题目推荐  
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)  
2. [P2613 【模板】扩展欧几里得](https://www.luogu.com.cn/problem/P2613)（模逆元应用）  
3. [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)（欧拉函数与数论分块）  

---

### 题解心得摘录  
- **调试教训**：多题解强调必须使用 `long long` 避免溢出（如 ZXXS 题解）  
- **数学直觉**：推导时可将 $10^N$ 视为 $kM^2 + r$ 形式（ruanwentao666 题解）  
- **模板复用**：快速幂模板需支持自定义模数（Pink_Cut_Tree 题解）

---
处理用时：50.04秒