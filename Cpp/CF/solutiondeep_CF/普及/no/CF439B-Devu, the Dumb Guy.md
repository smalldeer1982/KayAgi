# 题目信息

# Devu, the Dumb Guy

## 题目描述

Devu is a dumb guy, his learning curve is very slow. You are supposed to teach him $ n $ subjects, the $ i^{th} $ subject has $ c_{i} $ chapters. When you teach him, you are supposed to teach all the chapters of a subject continuously.

Let us say that his initial per chapter learning power of a subject is $ x $ hours. In other words he can learn a chapter of a particular subject in $ x $ hours.

Well Devu is not complete dumb, there is a good thing about him too. If you teach him a subject, then time required to teach any chapter of the next subject will require exactly 1 hour less than previously required (see the examples to understand it more clearly). Note that his per chapter learning power can not be less than 1 hour.

You can teach him the $ n $ subjects in any possible order. Find out minimum amount of time (in hours) Devu will take to understand all the subjects and you will be free to do some enjoying task rather than teaching a dumb guy.

Please be careful that answer might not fit in 32 bit data type.

## 说明/提示

Look at the first example. Consider the order of subjects: $ 1 $ , $ 2 $ . When you teach Devu the first subject, it will take him $ 3 $ hours per chapter, so it will take $ 12 $ hours to teach first subject. After teaching first subject, his per chapter learning time will be $ 2 $ hours. Now teaching him second subject will take $ 2×1=2 $ hours. Hence you will need to spend $ 12+2=14 $ hours.

Consider the order of subjects: $ 2 $ , $ 1 $ . When you teach Devu the second subject, then it will take him $ 3 $ hours per chapter, so it will take $ 3×1=3 $ hours to teach the second subject. After teaching the second subject, his per chapter learning time will be $ 2 $ hours. Now teaching him the first subject will take $ 2×4=8 $ hours. Hence you will need to spend $ 11 $ hours.

So overall, minimum of both the cases is $ 11 $ hours.

Look at the third example. The order in this example doesn't matter. When you teach Devu the first subject, it will take him $ 3 $ hours per chapter. When you teach Devu the second subject, it will take him $ 2 $ hours per chapter. When you teach Devu the third subject, it will take him $ 1 $ hours per chapter. In total it takes $ 6 $ hours.

## 样例 #1

### 输入

```
2 3
4 1
```

### 输出

```
11
```

## 样例 #2

### 输入

```
4 2
5 1 2 1
```

### 输出

```
10
```

## 样例 #3

### 输入

```
3 3
1 1 1
```

### 输出

```
6
```

# AI分析结果



# 中文题目重写

# Devu, the Dumb Guy

## 题目描述

Devu 的学习曲线非常缓慢。你需要教他 $n$ 个科目，第 $i$ 个科目有 $c_i$ 个章节。教学时必须连续完成一个科目的所有章节。

假设他初始每个章节的学习能力为 $x$ 小时，即每个章节需要花费 $x$ 小时。每完成一个科目的教学，后续科目的每个章节所需时间将减少 1 小时（但不能低于 1 小时）。你可以以任意顺序教学这些科目，求完成所有教学的最小总时间。

## 输入格式

输入包含：
- 第一行两个整数 $n$ 和 $x$
- 第二行 $n$ 个整数表示 $c_i$

## 输出格式

输出最小总时间（可能超过 32 位整数范围）

## 样例

样例 1 输入：
2 3
4 1
输出：11

样例解释：按科目顺序 [2,1] 教学时总时间最小（3×1 + 2×4 = 11）

## 数据范围
$1 \leq n \leq 10^5$, $1 \leq c_i \leq 10^5$

---

**算法分类**：贪心

---

## 题解综合分析

所有题解均采用贪心策略，核心思路是将科目按章节数从小到大排序，优先教学章节少的科目。这样可以让后续章节数多的科目以更低的单章时间学习，从而最小化总时间。

### 关键思路
1. **排序策略**：将 $c_i$ 从小到大排序，使后续大章节数的科目享受更多的时间衰减
2. **时间衰减处理**：每完成一个科目，x 减 1（但保持 ≥1）
3. **数据类型**：必须使用 64 位整型（long long）避免溢出

---

## 精选题解（评分≥4星）

### 题解1 - sanjingshou14（5星）
**亮点**：
- 明确指出贪心策略的数学依据（大数乘小数）
- 代码简洁高效，正确处理 x 的最小值
- 强调数据类型选用 unsigned long long 的必要性

```cpp
#include<bits/stdc++.h>
using namespace std;
long long c[100010];
int main(){
    long long n,x;
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>c[i];
    sort(c+1,c+n+1);
    unsigned long long s=0;
    for(int i=1;i<=n;i++){
        s += c[i]*x;
        if(x>1) x--;  // 自动处理下限
    }
    cout<<s;
    return 0; 
}
```

### 题解2 - 封禁用户（4星）
**亮点**：
- 尝试桶排序优化（虽实际提升有限）
- 代码包含完整优化思路
- 强调循环中维护 x ≥1 的重要性

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[100005], tong[100005], n;
long long cnt, x;
int main(){
    cin >> n >> x;
    // 桶排序实现
    for(int i=0; i<n; i++){
        cin >> c[i];
        tong[c[i]]++;
    }
    // 重构排序数组
    int ctmp = 0;
    for(int i=0; i<=100000; i++)
        while(tong[i]--) c[ctmp++] = i;
    // 计算总时间
    for(int i=0; i<n; i++){
        cnt += c[i]*x;
        if(x>1) x--;
    }
    cout << cnt;
}
```

### 题解3 - Genshin_ZFYX（4星）
**亮点**：
- 用三目运算符精简代码
- 代码风格清晰易读
- 包含调试注释（"我爱火星"彩蛋）

```cpp
#include<bits/stdc++.h>
#define int long long
signed main(){
    int n,x,sum=0;
    cin>>n>>x;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a.begin()+1,a.end());
    for(int i=1;i<=n;i++){
        sum += a[i]*x;
        x = (x==1) ? x : x-1; // 简洁处理衰减
    }
    cout<<sum;
}
```

---

## 关键技巧总结

1. **贪心排序原则**：优先处理对后续影响更大的元素（此处章节数小的科目先处理）
2. **衰减边界处理**：使用 `if(x>1)` 或 `max(1,x-1)` 维护时间下限
3. **数据类型选择**：总和可能达到 $10^5 \times 10^5 \times 10^5 = 10^{15}$，必须使用 64 位整型

---

## 拓展练习

1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（同类贪心排序）
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列优化）
3. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)（复杂贪心策略）

---

## 题解心得摘录

- **sanjingshou14**："必须使用 unsigned long long 才过，用 long long 就 WA" → 注意数据范围的特殊情况
- **封禁用户**：尝试桶排序优化但发现实际提升有限 → 算法选择需考虑实际数据特征
- **Genshin_ZFYX**：使用三目运算符精简代码 → 代码简洁性与可读性的平衡

---
处理用时：63.03秒