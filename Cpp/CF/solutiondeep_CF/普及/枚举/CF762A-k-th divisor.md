# 题目信息

# k-th divisor

## 题目描述

你被给了两个整数$n$ 和$k$ 。找到$n$ 的第$k$ 小因子，或者告知其不存在。

任意一个可以除$n$ 而没有余数的自然数都是$n$ 的因子。

## 说明/提示

在第一个样例中，数字$4$ 有三个因子：$1$ ，$2$ 和$4$ 。第二小的为$2$ 。

在第二个样例中，数字$5$ 仅有两个因子$1$ 和$5$ 。第三个因子是不存在的，因此答案是-1。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
12 5
```

### 输出

```
6
```

# AI分析结果

### 题解综合分析与结论
这些题解的核心思路都是利用因数成对出现的特性，通过枚举 $1$ 到 $\sqrt{n}$ 的数来找出 $n$ 的所有因数，进而找到第 $k$ 小的因数。各题解的主要区别在于因数的存储方式、排序处理以及对完全平方数的特判方式。

#### 思路对比
- **暴力存储排序**：伟大的王夫子、crh1272336175、Kevin_Zhen 等题解先将因数存储起来，再进行排序，最后输出第 $k$ 个因数。
- **直接查找**：Khassar、infinities、leoair 等题解在枚举过程中直接判断是否找到第 $k$ 个因数，避免了排序操作。
- **双端队列排序**：文·和使用双端队列，通过特定的插入方式实现因数的排序。
- **利用 STL 集合**：Jelly_Goat 使用 `set` 自动完成去重和排序。

#### 算法要点
- **因数成对特性**：若 $i$ 是 $n$ 的因数，则 $\frac{n}{i}$ 也是 $n$ 的因数，因此只需枚举 $1$ 到 $\sqrt{n}$。
- **完全平方数特判**：当 $n$ 是完全平方数时，$\sqrt{n}$ 只算一个因数，需要特殊处理。

#### 难点解决
- **存储与排序**：不同题解采用不同的数据结构和方法来存储和排序因数，如数组、向量、双端队列、集合等。
- **边界判断**：判断第 $k$ 个因数是否存在，若不存在则输出 -1。

### 所选题解
- **伟大的王夫子（5星）**
    - **关键亮点**：思路清晰，代码简洁，对特殊情况（如 $n = 1$）有明确的特判，注释详细。
    - **个人心得**：提到了被数据点 $1 \,\,\,2$ 坑的经历，强调了特判和使用 `long long` 的重要性。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long k, p[10000010], cnt;
int main() {
    cin >> n >> k;
    p[1] = 1;
    cnt = 1;
    if (n!= 1) p[2] = n, cnt = 2;
    for (register long long i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            p[++cnt] = i;
            if (i!= n / i) p[++cnt] = n / i;
        }
    }
    sort(p + 1, p + cnt + 1);
    if (k <= cnt) cout << p[k];
    else puts("-1");
} 
```
- **Kevin_Zhen（4星）**
    - **关键亮点**：思路明确，代码规范，对算法复杂度有清晰的分析，使用 `vector` 存储因数，方便排序和访问。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, k;
vector <ll> ans;
int main() {
    scanf("%lld%lld", &n, &k);
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i) continue;
        ans.push_back(i);
        if (i * i!= n) ans.push_back(n / i);
    }
    if (ans.size() < k) { printf("-1"); return 0; }
    sort(ans.begin(), ans.end());
    printf("%lld", ans[k - 1]);
    return 0;
}
```
- **αnonymous（4星）**
    - **关键亮点**：对因数个数进行了分析和特判，避免了不必要的存储和排序，直接根据 $k$ 的位置计算第 $k$ 个因数。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
unsigned long long n,k,pri[30000010],pn,all,i;
int main(){
    scanf("%lld%lld",&n,&k);
    if(k>2*sqrt(n))
        cout<<"-1"<<endl;
    else{
        for(i=1;i*i<=n;++i)
            if(n%i==0)
                pri[++pn]=i;
        all=pn*2;
        if(pri[pn]*pri[pn]==n)
            all--;
        if(k<=pn)
            cout<<pri[k]<<endl;
        else if(k>all)
            cout<<"-1"<<endl;
        else
            cout<<n/pri[all-k+1]<<endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
- **因数成对枚举**：利用因数成对出现的特性，将枚举范围从 $1$ 到 $n$ 缩小到 $1$ 到 $\sqrt{n}$，降低时间复杂度。
- **完全平方数特判**：在处理因数时，对 $n$ 是完全平方数的情况进行特判，避免重复计算。
- **合理选择数据结构**：根据具体需求选择合适的数据结构，如数组、向量、双端队列、集合等，以简化代码和提高效率。

### 拓展思路
同类型题可以是求一个数的所有因数之和、求一个数的因数个数等，解题思路类似，都可以利用因数成对出现的特性进行优化。

### 洛谷相似题目推荐
- P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题
- P1072 [NOIP2009 提高组] Hankson 的趣味题
- P2261 [CQOI2007] 余数求和

---
处理用时：31.38秒