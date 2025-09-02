# 题目信息

# Divided Prime

## 题目描述

给定一个数字$A$，这个$A$由$a_1,a_2,\cdots,a_N$相乘得到。

给定一个数字$B$，这个$B$由$b_1,b_2,\cdots,b_M$相乘得到。

如果$\frac{A}{B}$是一个质数，请输出`YES`，否则输出`NO`。



## 说明/提示

$1 \le N \le 100000$

$0 \le M \le N$

$1 \le a_i,b_i \le 10^{12}$

$1 \le T \le 10$

$\sum N \le 100000$

## 样例 #1

### 输入

```
2
3 2
5 7 7
5 7
4 2
5 7 7 7
5 7```

### 输出

```
YES
NO```

# AI分析结果

• 综合分析与结论：
    - 这些题解的核心思路均基于题目条件 “数字在 \(b_i\) 中出现次数不多于 \(a_i\) 中出现次数”，对 \(A\) 和 \(B\) 进行约分处理，判断约分后剩余结果是否为质数。
    - 算法要点包括：排除数字 \(1\) 的干扰，处理数据规模大不能直接相乘的问题，判断剩余数字是否为质数。
    - 解决难点在于找到高效的约分方法和质数判断方式，避免超时和数据溢出。

    - 多数题解通过排序数组后对比找到剩余数字，部分题解使用 map、multiset 等数据结构记录因子出现次数，还有题解利用异或运算巧妙约分。质数判断多采用朴素的根号 \(n\) 试除法，少数使用 Miller - Rabbin 算法。

    - 整体来看，各题解思路清晰，但在代码可读性、优化程度上存在差异。

• 所选的题解：
  - **作者：Iowa_BattleShip (5星)**
    - **关键亮点**：利用异或运算进行约分，代码简洁高效，思路独特新颖，无需复杂数据结构和排序操作。
    - **个人心得**：“因为每个因子都很大，所以我们不可能直接乘起来再除，而题目保证对于一个数字，其在 \(b_i\) 中出现的次数不多于在 \(a_i\) 中出现的次数，所以我们很容易想到要把 \(a\) 中的数用 \(b\) 里的约分掉，而众所周知，\(a\land a = 0\)，于是我们就可以考虑利用异或来约分”。
    - **重点代码**：
```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
ll re()//快读
{
    ll x = 0;
    char c = getchar();
    bool p = 0;
    for(; c < '0' || c > '9'; c = getchar())
        p = (c == '-' || p)? 1 : 0;
    for(; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + (c - '0');
    return p? -x : x;
}
bool judge(ll x)//判断是否是质数
{
    int i;
    if(!x || x == 1)//特判0和1
        return false;
    for(i = 2; 1LL * i * i <= x; i++)//朴素根号n试除法判断
        if(!(x % i))
            return false;
    return true;
}
int main()
{
    int i, n, m, t, s;
    ll x, y;
    t = re();
    while(t--)
    {
        x = y = s = 0;
        n = re();
        m = re();
        for(i = 1; i <= n + m; i++)
        {
            y = re();
            if(y!= 1)
            {
                i > n? s-- : s++;
                x ^= y;
            }
        }
        if(s == 1 && judge(x))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```
    - **核心实现思想**：通过快读函数读取数据，在读取 \(a\) 和 \(b\) 的所有数字过程中，利用异或运算将相同数字抵消，同时统计 \(a\) 比 \(b\) 多的非 \(1\) 数字个数，最后判断剩余数字是否为质数。

  - **作者：FlierKing (4星)**
    - **关键亮点**：逻辑清晰，先对数组排序，然后通过双指针法删除 \(a\) 中与 \(b\) 相同的数字，再判断剩余数字是否为质数，代码实现简洁明了。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAXN 100005
using namespace std;
    int T, n, m, cnt;
    ll a[MAXN], b[MAXN];
    bool u[MAXN];
ll inline read()
{
    ll x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    return x;
}
int check(int x)
{
    for (int i = 2, to = sqrt(x); i <= to; i++)
        if (x % i == 0) return 2;
    return 1;
}
bool cmp(int x, int y)
{
    return x > y;
}
int main()
{
    T = read();
    while (T--)
    {
        memset(u, 0, sizeof(u));
        n = read(), m = read();
        for (int i = 1; i <= n; i++)
            a[i] = read();
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= m; i++)
            b[i] = read();
        sort(b + 1, b + m + 1, cmp);
        for (int i = 1, j = 1; i <= m; i++)
        {
            while (b[i] < a[j]) j++;
            u[j] = true; j++;
        }
        cnt = 0;
        for (int i = 1; i <= n; i++)
            if (!u[i])
            {
                if (a[i] == 1) continue;
                cnt += check(a[i]);
                if (cnt > 1) break;
            }
        puts(cnt == 1? "YES" : "NO");
    }
    return 0;
}
```
    - **核心实现思想**：快读函数读取数据，对 \(a\) 和 \(b\) 数组降序排序，通过双指针遍历，标记 \(a\) 中与 \(b\) 相同的数字，最后统计剩余未标记且不为 \(1\) 的数字的质数个数，判断结果。

  - **作者：hawa130 (4星)**
    - **关键亮点**：使用 STL 中的 map 记录因子出现次数，代码简洁，逻辑清晰，对 map 的操作熟练，很好地解决了约分和判断剩余结果的问题。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 3;
int T, n, m;
template<typename Tp> void read(Tp &x) {
    char c = getchar();
    x = 0;
    while (!isdigit(c)) c = getchar();
    do {
        x = (x * 10) + (c ^ 48);
        c = getchar();
    } while (isdigit(c));
}
bool isprime(long long x) {
    long long tmp = sqrt(x);
    for (long long i = 2; i <= tmp; i++)
        if (!(x % i)) return false;
    return true;
}
int main() {
    read(T);
    while (T--) {
        map<long long, int> cnt;
        read(n), read(m);
        for (int i = 1; i <= n; i++) {
            long long num;
            read(num);
            if (num == 1) continue;
            cnt[num]++;
        }
        for (int i = 1; i <= m; i++) {
            long long num;
            read(num);
            if (num == 1) continue;
            if(!(--cnt[num]))
                cnt.erase(num);
        }
        if (cnt.size()!= 1) printf("NO\n");
        else {
            long long num = cnt.begin()->first;
            int sum = cnt.begin()->second;
            if (sum!= 1) printf("NO\n");
            else if (isprime(num)) printf("YES\n");
            else printf("NO\n");
        }
    }
}
```
    - **核心实现思想**：快读函数读取数据，利用 map 记录 \(a\) 中各因子出现次数，读取 \(b\) 时相应减少次数，通过判断 map 中剩余元素个数和出现次数，结合质数判断函数得出结果。

• 最优关键思路或技巧：
    - **异或运算约分**：如 Iowa_BattleShip 的题解，利用异或运算 \(a\land a = 0\) 的特性，将相同数字抵消，简洁高效地实现约分，避免复杂的数据结构和排序操作。
    - **数据结构应用**：hawa130 使用 map 记录因子出现次数，方便进行约分和结果判断，充分利用了 STL 数据结构的优势，代码简洁明了。
    - **双指针法优化**：FlierKing 通过对数组排序后使用双指针法，快速删除 \(a\) 中与 \(b\) 相同的数字，提高了算法效率。

• 可拓展思路：
    - 同类型题可拓展到更多涉及大数因子运算及判断结果性质的题目，类似算法套路包括利用数据结构记录因子信息、巧妙运用位运算简化操作、根据题目条件分析可能结果并针对性处理。

• 相似知识点洛谷题目：
    - [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)：结合质数判断和回文数判断，需优化算法避免超时。
    - [P3912 素数个数](https://www.luogu.com.cn/problem/P3912)：考察质数判断及在一定范围内统计质数个数，可使用筛法优化。
    - [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：在构造幻方过程中结合质数判断，增加题目综合性。

• 个人心得摘录与总结：
    - **Iowa_BattleShip**：强调不能直接相乘除，基于题目条件想到用异或约分，体现从条件出发寻找解题思路的重要性。
    - **Limerick**：提到排序在解题中的重要性，以及在质数判断算法选择上的思考，如 Miller - Rabbin 算法可用于大数字质数判断。
    - **Trinity**：指出面对大数据要优化，在小细节上要做好特判，避免因细节问题导致错误。 

---
处理用时：98.88秒