# 题目信息

# 「LAOI-1」GCD

## 题目描述

一张图有 $n$ 个节点，编号为 $1,2,3,\dots,n$。其中 $i$ 号节点会向 $j$ 号节点连一条边权为 $|i-j|$ 的无向边，当且仅当 $\gcd(i,j)=i,\operatorname{lcm}(i,j)=j$ 时连边。现询问 $q$ 次，每次询问求 $x$ 到 $y$ 的最短路径。

## 说明/提示

注意时空限制，本题不捆绑。

对于 $40\%$ 的数据，$T,n,q\le100$;

对于 $100\%$ 的数据，$1\le T\le10^6$，$1\le n,q\le10^6$，$1\le x,y\le n$，$1\le \sum n,\sum q\le10^6$。

**请使用更快的 IO 方式**。

updata on 2024/8/8：

时限上调到 1000ms。/yun

## 样例 #1

### 输入

```
1
6 4
1 4
3 5
2 5
2 4```

### 输出

```
3
6
5
2```

# AI分析结果

### 综合分析与结论
这两道题解都基于对题目条件的分析，得出节点连边条件等价于两数存在倍数关系，进而推导得出最短路径的计算方式。
 - **思路**：都通过分析条件得出连边关系，且都证明了最短路径是将两点都跳到它们的最大公约数处，从而得出答案为 \(x + y - 2\gcd(x,y)\)。
 - **算法要点**：核心在于快速计算最大公约数，以及理解并应用路径计算的公式。
 - **解决难点**：主要难点在于证明将两点跳到最大公约数处是最优路径，两位作者分别从不同角度进行了证明。

### 题解分析
 - **作者：Coffins**
    - **星级**：4星
    - **关键亮点**：思路清晰，从条件出发通过分类讨论证明将 \(x\)，\(y\) 都跳到 \(\gcd(x,y)\) 处是最优路径，代码简洁明了，使用了快速输入输出。
    - **个人心得**：赛时 5min 切题，但首次提交被卡输入。说明输入方式对本题很关键。
    - **核心代码**：
```cpp
int gcd(int a,int b)
{
    while(b^=a^=b^=a%=b);
    return a;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        for(int i=1;i<=q;i++)
        {
            cin>>x>>y;
            cout<<x+y-2*gcd(x,y)<<'\n';
        }
    } 
    return 0;
}
```
核心实现思想：自定义快速求最大公约数函数 `gcd`，主函数中通过快速输入输出，循环处理每次询问，根据公式计算并输出结果。
 - **作者：sto_5k_orz**
    - **星级**：4星
    - **关键亮点**：通过与到更小公约数以及另一种可能路径的比较，证明答案的最优性，代码使用了自定义的快速输入输出函数。
    - **核心代码**：
```cpp
namespace SlowIO{
    I int read() {
        int x = 0, f = 1; char ch = gc();
        W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
        W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
        return x * f;
    }
    I void Read(int &x) {x = read();}
    I void Read(int &x, int &y) {Read(x), Read(y);}
    I void write(int x) {
        if(x < 0) pc('-'), x = -x;
        if(x > 9) write(x / 10);
        pc(x % 10 + '0');
    }
    I void writeln(int x) {write(x); pc('\n');}
} using namespace SlowIO;
signed main() {
    int t; Read(t);
    while(t--) {
        int n, q; Read(n, q); 
        while(q--) {
            int a, b; Read(a, b); int g = __gcd(a, b);
            writeln(a + b - 2 * g);
        }
    }
    return 0;
}
```
核心实现思想：自定义 `SlowIO` 命名空间实现快速输入输出，主函数中通过循环处理每次询问，调用库函数 `__gcd` 计算最大公约数，根据公式计算并输出结果。

### 最优关键思路或技巧
 - **思维方式**：深入分析题目中给出的条件，将复杂的图论问题转化为简单的数学关系（倍数关系），从而简化问题求解。
 - **代码实现技巧**：使用快速输入输出方式以满足题目时间限制，如 `ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);` 或者自定义快速输入输出函数。

### 可拓展之处
同类型题或类似算法套路：此类题目通常是将图论中的边权关系与数论知识相结合。常见套路是先分析图中节点连接条件背后的数学关系，再利用数论性质（如最大公约数、最小公倍数）来优化路径计算。

### 相似知识点洛谷题目
 - [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
 - [P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)
 - [P1890 [USACO03NOV] 公约数的和 SUM of GCDs](https://www.luogu.com.cn/problem/P1890)

---
处理用时：26.94秒