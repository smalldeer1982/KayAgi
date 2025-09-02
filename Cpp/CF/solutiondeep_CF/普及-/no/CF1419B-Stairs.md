# 题目信息

# Stairs

## 题目描述

Jett is tired after destroying the town and she wants to have a rest. She likes high places, that's why for having a rest she wants to get high and she decided to craft staircases.

Staircase is a squared figure that consists of square cells. Each staircase consists of an arbitrary number of stairs. If a staircase has $ n $ stairs, then it is made of $ n $ columns, the first column is $ 1 $ cell high, the second column is $ 2 $ cells high, $ \ldots $ , the $ n $ -th column if $ n $ cells high. The lowest cells of all stairs must be in the same row.

A staircase with $ n $ stairs is called nice, if it may be covered by $ n $ disjoint squares made of cells. All squares should fully consist of cells of a staircase.

 This is how a nice covered staircase with $ 7 $ stairs looks like: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)Find out the maximal number of different nice staircases, that can be built, using no more than $ x $ cells, in total. No cell can be used more than once.

## 说明/提示

In the first test case, it is possible to build only one staircase, that consists of $ 1 $ stair. It's nice. That's why the answer is $ 1 $ .

In the second test case, it is possible to build two different nice staircases: one consists of $ 1 $ stair, and another consists of $ 3 $ stairs. This will cost $ 7 $ cells. In this case, there is one cell left, but it is not possible to use it for building any nice staircases, that have not been built yet. That's why the answer is $ 2 $ .

In the third test case, it is possible to build only one of two nice staircases: with $ 1 $ stair or with $ 3 $ stairs. In the first case, there will be $ 5 $ cells left, that may be used only to build a staircase with $ 2 $ stairs. This staircase is not nice, and Jett only builds nice staircases. That's why in this case the answer is $ 1 $ . If Jett builds a staircase with $ 3 $ stairs, then there are no more cells left, so the answer is $ 1 $ again.

## 样例 #1

### 输入

```
4
1
8
6
1000000000000000000```

### 输出

```
1
2
1
30```

# AI分析结果

### 题目重写
# Stairs

## 题目描述
杰特在摧毁城镇后感到疲惫，她想要休息一下。她喜欢高处，所以为了休息，她想爬到高处，于是决定搭建楼梯。

楼梯是一个由正方形单元格组成的方形图形。每个楼梯由任意数量的台阶组成。如果一个楼梯有 $n$ 个台阶，那么它由 $n$ 列组成，第一列高 $1$ 个单元格，第二列高 $2$ 个单元格，……，第 $n$ 列高 $n$ 个单元格。所有台阶的最低单元格必须在同一行。

如果一个有 $n$ 个台阶的楼梯可以被 $n$ 个不相交的由单元格组成的正方形覆盖，那么这个楼梯就被称为“好楼梯”。所有正方形都应该完全由楼梯的单元格组成。

这是一个有 $7$ 个台阶的“好楼梯”被覆盖的样子：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)
找出总共使用不超过 $x$ 个单元格可以建造的不同“好楼梯”的最大数量。任何单元格都不能被使用超过一次。

## 说明/提示
在第一个测试用例中，只能建造一个由 $1$ 个台阶组成的楼梯。它是“好楼梯”。这就是为什么答案是 $1$。

在第二个测试用例中，可以建造两个不同的“好楼梯”：一个由 $1$ 个台阶组成，另一个由 $3$ 个台阶组成。这将花费 $7$ 个单元格。在这种情况下，还剩下一个单元格，但它不能用于建造任何尚未建造的“好楼梯”。这就是为什么答案是 $2$。

在第三个测试用例中，只能建造两个“好楼梯”中的一个：由 $1$ 个台阶组成的或由 $3$ 个台阶组成的。在第一种情况下，会剩下 $5$ 个单元格，这些单元格只能用于建造一个由 $2$ 个台阶组成的楼梯。这个楼梯不是“好楼梯”，而杰特只建造“好楼梯”。这就是为什么在这种情况下答案是 $1$。如果杰特建造一个由 $3$ 个台阶组成的楼梯，那么就没有剩余的单元格了，所以答案仍然是 $1$。

## 样例 #1
### 输入
```
4
1
8
6
1000000000000000000
```
### 输出
```
1
2
1
30
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路均是先证明只有级数为 $2^n - 1$ 的阶梯才是“好阶梯”，再基于此结论，利用贪心思想，每次选择级数尽可能小的阶梯，以求出使用不超过 $x$ 个单元格时能建造的不同“好楼梯”的最大数量。各题解的主要区别在于证明过程和代码实现细节。证明过程中，有的从正方形覆盖特点出发，有的通过分治思想分析，有的借助枚举归纳；代码实现上，在计算阶梯所需单元格数量、循环条件设置以及变量初始化等方面存在差异。

### 所选的题解
- **作者：Chinese_zjc_（5星）**
  - **关键亮点**：思路清晰，先提出假设，再从正方形占用阶梯最左方块这一特性出发，严谨证明只有级数为 $2^n - 1$ 的阶梯是“好阶梯”。代码简洁明了，利用位运算和简单循环实现贪心算法，复杂度为 $O(\log_2n)$。
  - **重点代码**：
```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define PI 3.14159265358979323
#define INF 0x3fffffffffffffff
using namespace std;
int T, n, ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--)
    {
        cin >> n;
        ans = 0;
        for (int i = 1; n >= ((1ll << i) - 1) * (1ll << i) / 2; ++i)
        {
            ++ans;
            n -= ((1ll << i) - 1) * (1ll << i) / 2;
        }
        cout << ans << endl;
    }
    return 0;
}
```
  - **核心实现思想**：通过循环，每次判断当前 $n$ 是否足够建造级数为 $2^i - 1$ 的“好阶梯”，若够则建造（更新 $ans$ 和 $n$），直到 $n$ 不足，最终输出 $ans$。

- **作者：511_Juruo_wyk（4星）**
  - **关键亮点**：从题目所给样图出发，直观地利用分治思想发现只有当 $n = 2^k - 1$（$k$ 为正整数）时阶梯为“好阶梯”的规律。代码中使用位运算符提高计算效率，同时对 `endl` 和 `cin/cout` 进行优化，提高程序运行速度。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define endl '\n'//让endl的时间复杂度变低 
using namespace std;
int t;
long long num;//注意开long long 
long long power;
long long sum(long long n){return n*(n+1)/2;}//高斯求和公式 
int main(){
    std::ios::sync_with_stdio(false);//让cin和cout速度变快，但是不能使用scanf和printf 
    cin>>t;
    while(t--){
        cin>>num;
        power=1;//初始化 
        while(num>0){
            power++;
            num=num-sum((1<<power)-1);//位运算符时间复杂度比pow(2,power)要低很多 
        }
        cout<<power-1<<endl;//注意power是从1开始的，所以输出时要减1 
    }
    return 0;//养成好习惯 
}
```
  - **核心实现思想**：利用 `while` 循环，每次增加 `power`，计算并减去级数为 $2^{power} - 1$ 的“好阶梯”所需单元格数，直到 `num` 不足，输出 `power - 1`。

- **作者：Mine_King（4星）**
  - **关键亮点**：通过观察题目样图，从“好楼梯”的形成过程出发，先证明 $2^n - 1$ 阶的楼梯是好楼梯，再从正方形覆盖条件出发，反证只有 $2^n - 1$ 阶的楼梯是好楼梯。证明过程详细，易于理解。代码实现简洁，逻辑清晰。
  - **重点代码**：
```cpp
#include<cstdio>
#define int long long
using namespace std;
int T,n,ans;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        ans=0;
        scanf("%lld",&n);
        int k=2;
        while(true)
        {
            int x=k-1;
            int res=(1+x)*x/2;
            if(n>=res) n-=res;
            else break;
            ans++;
            k*=2;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
  - **核心实现思想**：利用 `while` 循环，每次计算并判断当前 $n$ 是否能建造级数为 $k - 1$ 的“好阶梯”，若能则建造并更新相关变量，直到 $n$ 不足，输出 `ans`。

### 最优关键思路或技巧
- **证明思路**：从正方形覆盖阶梯的特点出发，如每个正方形必须占用阶梯每层最左的方块，以此为基础证明只有 $2^n - 1$ 级的阶梯是“好阶梯”，逻辑严谨且易于理解。
- **代码实现**：利用位运算计算 $2$ 的幂次方，相比使用 `pow` 函数，时间复杂度更低，提高了程序运行效率。同时，采用贪心策略，优先选择级数小的“好阶梯”，符合题目要求且实现简单高效。

### 拓展思路
同类型题通常围绕图形的组合、覆盖问题，通过寻找特定规律，利用贪心、数学推导等方法解决。类似算法套路是先观察样例或小数据，尝试找出规律，再进行严谨证明，最后根据规律和题目要求选择合适算法（如贪心、动态规划等）实现。

### 洛谷相似题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过分析数据间的关系，利用贪心策略解决问题，与本题寻找规律后使用贪心算法类似。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：同样是基于一定的逻辑分析，采用贪心思想优化排队顺序，以达到最优解，和本题思路有相似之处。
- [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：通过对区间分配问题的分析，运用贪心策略解决，与本题在分析问题和选择算法上有共通点。 

---
处理用时：73.01秒