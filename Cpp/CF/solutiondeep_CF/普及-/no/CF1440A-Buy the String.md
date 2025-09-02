# 题目信息

# Buy the String

## 题目描述

You are given four integers $ n $ , $ c_0 $ , $ c_1 $ and $ h $ and a binary string $ s $ of length $ n $ .

A binary string is a string consisting of characters $ 0 $ and $ 1 $ .

You can change any character of the string $ s $ (the string should be still binary after the change). You should pay $ h $ coins for each change.

After some changes (possibly zero) you want to buy the string. To buy the string you should buy all its characters. To buy the character $ 0 $ you should pay $ c_0 $ coins, to buy the character $ 1 $ you should pay $ c_1 $ coins.

Find the minimum number of coins needed to buy the string.

## 说明/提示

In the first test case, you can buy all characters and pay $ 3 $ coins, because both characters $ 0 $ and $ 1 $ costs $ 1 $ coin.

In the second test case, you can firstly change $ 2 $ -nd and $ 4 $ -th symbols of the string from $ 1 $ to $ 0 $ and pay $ 2 $ coins for that. Your string will be $ 00000 $ . After that, you can buy the string and pay $ 5 \cdot 10 = 50 $ coins for that. The total number of coins paid will be $ 2 + 50 = 52 $ .

## 样例 #1

### 输入

```
6
3 1 1 1
100
5 10 100 1
01010
5 10 1 1
11111
5 1 10 1
11111
12 2 1 10
101110110101
2 100 1 10
00```

### 输出

```
3
52
5
10
16
22```

# AI分析结果

### 题目内容
# 购买字符串

## 题目描述
给定四个整数 $n$、$c_0$、$c_1$ 和 $h$ 以及一个长度为 $n$ 的二进制字符串 $s$。

二进制字符串是由字符 $0$ 和 $1$ 组成的字符串。

你可以更改字符串 $s$ 中的任意字符（更改后字符串仍应为二进制字符串）。每次更改需支付 $h$ 枚硬币。

经过一些更改（可能为零次）后，你想要购买该字符串。要购买字符串，你需要购买其所有字符。购买字符 $0$ 需支付 $c_0$ 枚硬币，购买字符 $1$ 需支付 $c_1$ 枚硬币。

求购买该字符串所需的最少硬币数。

## 说明/提示
在第一个测试用例中，你可以购买所有字符并支付 $3$ 枚硬币，因为字符 $0$ 和 $1$ 都价值 $1$ 枚硬币。

在第二个测试用例中，你可以首先将字符串的第 $2$ 个和第 $4$ 个符号从 $1$ 更改为 $0$，并为此支付 $2$ 枚硬币。此时你的字符串将变为 $00000$。之后，你可以购买该字符串并为此支付 $5 \cdot 10 = 50$ 枚硬币。总共支付的硬币数将为 $2 + 50 = 52$ 枚。

## 样例 #1
### 输入
```
6
3 1 1 1
100
5 10 100 1
01010
5 10 1 1
11111
5 1 10 1
11111
12 2 1 10
101110110101
2 100 1 10
00
```
### 输出
```
3
52
5
10
16
22
```
### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略，通过比较将 $0$ 变成 $1$ 或 $1$ 变成 $0$ 后购买的花费与直接购买的花费，来决定每个字符的最优处理方式。不同题解在具体实现细节上有所差异，比如输入输出方式、代码结构等，但整体思路一致。

### 所选的题解
- **作者：zhenliu (5星)**
    - **关键亮点**：思路清晰简洁，代码直接在遍历字符串时，对每个字符比较直接购买和转换后购买的花费，取较小值累加到总花费中，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,c0,c1,h,n;
char c;
int main(){
    scanf("%d",&T);
    while(T--){
        int ans=0;
        scanf("%d %d %d %d",&n,&c0,&c1,&h);
        c=getchar();//把换行符读掉 
        for(int i=1;i<=n;i++){
            c=getchar();
            if(c=='0')ans+=min(c0,h+c1);//比较 
            else ans+=min(c1,h+c0);
        }
        printf("%d\n",ans);
    }
    return 0;
} 
```
核心实现思想：遍历字符串，对每个字符判断是直接购买花费少还是转换后购买花费少，将较小花费累加到总花费 `ans` 中。
- **作者：白鲟 (5星)**
    - **关键亮点**：同样采用简洁的贪心策略，代码风格优雅，通过数组 `c` 存储购买 $0$ 和 $1$ 的花费，利用位运算简化判断过程，代码简洁高效。
    - **核心代码**：
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1e3;
int T,n,c[2],h,ans;
char s[maxn+1];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        ans=0;
        scanf("%d%d%d%d%s",&n,&c[0],&c[1],&h,s+1);
        for(int i=1;i<=n;++i)
            ans+=min(c[s[i]-'0'],c[(s[i]-'0')^1]+h);
        printf("%d\n",ans);
    }
    return 0;
}
```
核心实现思想：通过数组 `c` 存储购买 $0$ 和 $1$ 的花费，遍历字符串，利用位运算 `^` 判断字符转换后的情况，取直接购买和转换后购买花费的较小值累加到总花费 `ans` 中。
- **作者：PragmaGCC (4星)**
    - **关键亮点**：以生活实例类比解题思路，易于理解，代码通过分类讨论，先判断整体转换的情况，再分别计算不同情况下的总花费，逻辑清晰。
    - **核心代码**：
```cpp
#include <cstdio>
int read() {
    register int n = 0;
    register char ch = getchar();
    bool f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + (ch ^ '0');
        ch = getchar();
    }
    return f? n : -n;
}
char str[1005];
void work() {
    int n = read(), c0 = read(), c1 = read(), k = read();
    scanf("%s", str + 1);
    int tot = 0;
    if (c0 + k < c1) {
        for (int i = 1; i <= n; i++)
            if (str[i] == '1')
                tot++;
        printf("%d\n", c0 * n + tot * k);
    } else if (c1 + k < c0) {
        for (int i = 1; i <= n; i++)
            if (str[i] == '0')
                tot++;
        printf("%d\n", c1 * n + tot * k);
    } else {
        int ans = 0;
        for (int i=1; i<=n; i++) {
            if (str[i] == '0') ans += c0;
            else ans += c1;
        }
        printf("%d\n", ans);
    }
}
int main(void) {
    int T = read();
    while (T--)
        work();
    return 0;
}
```
核心实现思想：先判断是否将所有 $1$ 转换为 $0$ 或所有 $0$ 转换为 $1$ 更划算，统计需要转换的字符个数，计算相应总花费；若转换不划算则直接按原价购买所有字符计算总花费。

### 最优关键思路或技巧
直接比较每个字符直接购买的花费和转换后购买的花费，取较小值累加，这是一种简单有效的贪心策略。在代码实现上，可以通过巧妙的数据结构（如数组存储花费）和位运算等方式简化代码。

### 可拓展之处
同类型题通常围绕不同物品有不同成本，且存在转换成本的情境，通过比较不同操作的成本，利用贪心策略求解最优解。类似算法套路是分析不同操作对整体成本的影响，找到局部最优决策，进而得到全局最优解。

### 洛谷相似题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无。 

---
处理用时：76.86秒