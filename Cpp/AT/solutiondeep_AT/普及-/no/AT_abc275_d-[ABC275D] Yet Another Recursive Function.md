# 题目信息

# [ABC275D] Yet Another Recursive Function

## 题目描述

定义函数 $f(x)$ 有如下定义

- $ f(0)\ =\ 1 $
- 对于任意正整数 $k$ 有 $f(k)\ = f(\lfloor\frac{k}{2}\rfloor)\ +\ f(\lfloor\frac{k}{3}\rfloor) $

$ \lfloor A\rfloor $ 代表小于等于 $A$ 的最大整数。

求 $f(x)$。

## 说明/提示

- $ 0\ \le\ N\ \le\ 10^{18} $

### 样例一解释

$ f(2)\ =\ f(\lfloor\frac{2}{2}\rfloor)\ +\ f(\lfloor\frac{2}{3}\rfloor)\ =\ f(1)\ +\ f(0)\ =(f(\lfloor\frac{1}{2}\rfloor)\ +\ f(\lfloor\frac{1}{3}\rfloor))\ +\ f(0)\ =(f(0)+f(0))\ +\ f(0)=\ 3 $。

## 样例 #1

### 输入

```
2```

### 输出

```
3```

## 样例 #2

### 输入

```
0```

### 输出

```
1```

## 样例 #3

### 输入

```
100```

### 输出

```
55```

# AI分析结果

【题目内容】
# [ABC275D] Yet Another Recursive Function

## 题目描述

定义函数 $f(x)$ 有如下定义

- $ f(0)\ =\ 1 $
- 对于任意正整数 $k$ 有 $f(k)\ = f(\lfloor\frac{k}{2}\rfloor)\ +\ f(\lfloor\frac{k}{3}\rfloor) $

$ \lfloor A\rfloor $ 代表小于等于 $A$ 的最大整数。

求 $f(x)$。

## 说明/提示

- $ 0\ \le\ N\ \le\ 10^{18} $

### 样例一解释

$ f(2)\ =\ f(\lfloor\frac{2}{2}\rfloor)\ +\ f(\lfloor\frac{2}{3}\rfloor)\ =\ f(1)\ +\ f(0)\ =(f(\lfloor\frac{1}{2}\rfloor)\ +\ f(\lfloor\frac{1}{3}\rfloor))\ +\ f(0)\ =(f(0)+f(0))\ +\ f(0)=\ 3 $。

## 样例 #1

### 输入

```
2```

### 输出

```
3```

## 样例 #2

### 输入

```
0```

### 输出

```
1```

## 样例 #3

### 输入

```
100```

### 输出

```
55```

【算法分类】
递归、记忆化搜索

【题解分析与结论】
本题的核心在于通过递归计算函数 $f(x)$，但由于 $x$ 的范围高达 $10^{18}$，直接递归会导致超时。因此，记忆化搜索是解决该问题的关键。通过使用 `std::map` 或 `unordered_map` 来存储已经计算过的 $f(x)$ 值，可以避免重复计算，从而将时间复杂度降低到 $O(\log^2 n)$。

【评分较高的题解】

1. **作者：_Haoomff_ (赞：4)**
   - **星级：5星**
   - **关键亮点：**
     - 使用 `std::map` 进行记忆化，代码简洁明了。
     - 时间复杂度分析清晰，明确指出使用记忆化后的复杂度为 $O(\log^2 n)$。
   - **核心代码：**
     ```cpp
     map<ll,ll> a;
     inline ll f(ll n){
         if(n==0)return a[0]=1;
         if(a[n])return a[n];
         return a[n]=f(n/2)+f(n/3);
     }
     ```

2. **作者：FFTotoro (赞：3)**
   - **星级：4星**
   - **关键亮点：**
     - 使用 `std::map` 存储 $f(i)$ 的值，代码结构清晰。
     - 时间复杂度分析准确，适合处理大范围数据。
   - **核心代码：**
     ```cpp
     map<int,int> m;
     int f(int n){
         if(m[n])return m[n];
         if(!n)return m[0]=1;
         return m[n]=f(n>>1ll)+f(n/3);
     }
     ```

3. **作者：FReQuenter (赞：2)**
   - **星级：4星**
   - **关键亮点：**
     - 使用 `std::map` 进行记忆化，代码简洁且易于理解。
     - 时间复杂度分析合理，适合处理大范围数据。
   - **核心代码：**
     ```cpp
     std::map<int,int> mp;
     int f(int x){
       if(!x) return 1;
       if(mp[x]) return mp[x];
       int ans=f(x/2)+f(x/3);
       mp[x]=ans;
       return ans;
     }
     ```

【最优关键思路或技巧】
- **记忆化搜索**：通过 `std::map` 或 `unordered_map` 存储已经计算过的 $f(x)$ 值，避免重复计算，显著降低时间复杂度。
- **时间复杂度优化**：通过记忆化，将时间复杂度从指数级降低到 $O(\log^2 n)$，适合处理大范围数据。

【可拓展之处】
- 类似的问题可以通过记忆化搜索来优化递归计算，例如斐波那契数列、组合数计算等。
- 可以进一步探讨使用 `unordered_map` 代替 `std::map` 来优化查找效率。

【推荐题目】
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1464 Function](https://www.luogu.com.cn/problem/P1464)

---
处理用时：27.59秒