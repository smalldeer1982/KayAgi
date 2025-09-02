# 题目信息

# [USACO22JAN] Searching for Soulmates S

## 题目描述

Farmer John 的每头奶牛都想找到她们的灵魂伴侣——另一头具有相似特点的奶牛，与她们最大程度地相容。每头奶牛的性格由一个整数 $p_i$（$1 \leq p_i \leq 10^{18}$）描述。两头性格相同的奶牛就是灵魂伴侣。奶牛可以通过「改变操作」，对她的性格乘以 $2$，除以 $2$（当 $p_i$ 是偶数时），或者加上 $1$。

Farmer John 最初以任意方式配对了他的奶牛。他很好奇为使每对奶牛成为灵魂伴侣需要进行多少次改变操作。对于每对奶牛，求配对中的第一头奶牛所必须进行的最小改变操作次数，从而可以与第二头奶牛成为灵魂伴侣。

## 说明/提示

【样例解释】

对于第一个子测试用例，一个最优的操作序列为 $31 \implies 32 \implies 16 \implies 8 \implies 9 \implies 10 \implies 11 \implies 12 \implies 13$。

对于第二个子测试用例，一个最优的操作序列为 $12 \implies 6 \implies 7 \implies 8$.

【数据范围】

- 测试点 1-4 满足 $p_i \le 10^5$。
- 测试点 5-12 没有额外限制。



## 样例 #1

### 输入

```
6
31 13
12 8
25 6
10 24
1 1
997 120```

### 输出

```
8
3
8
3
0
20```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何通过乘 2、除 2（偶数时）、加 1 操作，将一个数转换为另一个数的最小操作次数展开。多数题解先分析操作的特性，如乘除操作不会交替出现，而是存在分界点，且通常是先除后乘。然后通过分情况讨论、递归函数、枚举二进制前缀等方法来计算最小操作次数。各题解在实现细节和思路切入点上有所不同，但核心思想相似。

### 所选题解
- **作者：MY（一名蒟蒻）**（4星）
    - **关键亮点**：思路清晰，先从 SPFA 爆搜的问题分析入手，逐步推导出操作的特性和算法实现，代码注释详细。
    - **个人心得**：赛时因数据范围大爆搜失败，赛后补题发现网上题解有些地方不清晰，于是自己写题解。原代码被 hack，是因为实现细节没处理好，将 `while` 循环改为 `do...while` 循环解决问题。
- **作者：YCSluogu**（4星）
    - **关键亮点**：提供新奇思路，通过枚举目标数的二进制前缀作为中转值，将问题转化为弱化情况，代码实现简洁。
- **作者：jimmy2021**（4星）
    - **关键亮点**：逻辑严谨，通过分情况讨论明确操作分界点前后的操作，递归函数计算乘加操作的最小次数，代码结构清晰。
    - **个人心得**：原代码被 hack，是因为特殊情况没处理好，将 `while` 循环改为 `do...while` 循环解决问题。

### 重点代码
#### MY（一名蒟蒻）
```cpp
ll dfs(ll x, ll y)
{
    if(x > y) return 1e18;
    if(x << 1 > y) return y - x;
    return y & 1? dfs(x, y - 1) + 1 : dfs(x, y >> 1) + 1;
}

inline ll solve()
{
    if(a == b) return 0;
    ll ans = 1e12, cnt = 0;
    do
    {
        ll res = dfs(a, b);
        ans = min(ans, res + cnt);
        if(a & 1) a++;
        else a >>= 1;
        cnt++;
    } while(a > 1);
    return ans;
}
```
**核心思想**：`dfs` 函数计算仅通过乘 1 和加 3 操作将 `x` 变成 `y` 的代价，`solve` 函数枚举前半部分操作的结束点，取最小操作次数。

#### YCSluogu
```cpp
long long len(long long num) {
    for (long long i = 63; i >= 0; i--) {
        if ((num >> i) & 1) {
            return i + 1;
        }
    }
    return 0;
}

long long get(long long num, long long i, long long len) {
    return num >> (len - i);
}

void solve() {
    long long a, b, c, cnt = 0, ans = INT_MAX;
    cin >> a >> b;
    if (a == b) {
        cout << 0 << endl;
        return;
    }
    c = len(b);
    long long save = a;
    for (long long i = 1; i <= c; i++, ans = min(ans, cnt), a = save) {
        cnt = 0;
        long long nowb = get(b, i, c);
        while (a != nowb) {
            if (a > nowb) {
                if (a & 1) a++;
                else a /= 2;
                cnt++;
            } else {
                cnt += nowb - a;
                a = nowb;
            }
        }
        for (long long j = i + 1; j <= c; j++) {
            nowb = get(b, j, c);
            a <<= 1;
            cnt++;
            if (nowb != a) a++, cnt++;
        }
    }
    cout << ans << endl;
}
```
**核心思想**：`len` 函数计算数的二进制长度，`get` 函数获取数的二进制前缀。`solve` 函数枚举 `b` 的二进制前缀作为中转值，计算 `a` 变为中转值的操作次数，再将中转值变为 `b`。

#### jimmy2021
```cpp
LL f(LL a, LL b){
    if(a > b) return 1e18;
    if(a * 2 > b) return b - a;
    if(b % 2 == 1) return f(a, b - 1) + 1;
    if(b % 2 == 0 && a <= b / 2) return f(a, b / 2) + 1;
}
LL solve(LL a, LL b){
    LL cnt1 = 0;  //光由除操作和加操作的最小操作次数
    if(a == b) return 0;
    LL ret = 1e18;
    do{
        //可以随时设当前为分界点
        LL cnt2 = f(a, b);
        ret = min(ret, cnt1 + cnt2);
        
        if(a % 2 == 1) a++;
        else a /= 2;
        cnt1++;
    }while(a > 1);
    return ret;
}
```
**核心思想**：`f` 函数递归计算仅通过乘和加操作将 `a` 变成 `b` 的最小次数，`solve` 函数枚举前半部分操作的结束点，取最小操作次数。

### 最优关键思路或技巧
- **操作特性分析**：通过分析发现乘除操作不会交替出现，而是存在分界点，通常先除后乘，减少不必要的搜索。
- **递归函数计算代价**：使用递归函数计算仅通过乘和加操作将一个数变成另一个数的代价，简化问题。
- **枚举二进制前缀**：枚举目标数的二进制前缀作为中转值，将问题转化为更简单的情况。

### 可拓展之处
同类型题可能涉及更多的操作类型或不同的数据范围，类似算法套路可以是先分析操作的特性，找出最优的操作顺序，再通过分情况讨论、递归、枚举等方法计算最小操作次数。

### 推荐题目
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：涉及搜索和状态转移，与本题的操作和状态变化有相似之处。
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：需要分析状态的转移和最优路径，与本题的思路类似。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合和递归计算，锻炼分情况讨论和递归的能力。

---
处理用时：44.86秒