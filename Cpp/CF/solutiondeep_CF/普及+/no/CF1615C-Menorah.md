# 题目信息

# Menorah

## 题目描述

There are $ n $ candles on a Hanukkah menorah, and some of its candles are initially lit. We can describe which candles are lit with a binary string $ s $ , where the $ i $ -th candle is lit if and only if $ s_i=1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1615C/23095c0b536d5c6c64ebf4ef5c8e358f51d36118.png)Initially, the candle lights are described by a string $ a $ . In an operation, you select a candle that is currently lit. By doing so, the candle you selected will remain lit, and every other candle will change (if it was lit, it will become unlit and if it was unlit, it will become lit).

You would like to make the candles look the same as string $ b $ . Your task is to determine if it is possible, and if it is, find the minimum number of operations required.

## 说明/提示

In the first test case, the two strings are already equal, so we don't have to perform any operations.

In the second test case, we can perform a single operation selecting the second candle to transform $ 01 $ into $ 11 $ .

In the third test case, it's impossible to perform any operations because there are no lit candles to select.

In the fourth test case, we can perform the following operations to transform $ a $ into $ b $ :

1. Select the $ 7 $ -th candle: $ 100010{\color{red}1}11\to 011101{\color{red} 1}00 $ .
2. Select the $ 2 $ -nd candle: $ 0{\color{red} 1}1101100\to 1{\color{red} 1}0010011 $ .
3. Select the $ 1 $ -st candle: $ {\color{red}1}10010011\to {\color{red}1}01101100 $ .

In the fifth test case, we can perform the following operations to transform $ a $ into $ b $ :

1. Select the $ 6 $ -th candle: $ 00101{\color{red}1}011\to 11010{\color{red}1}100 $
2. Select the $ 2 $ -nd candle: $ 1{\color{red}1}0101100\to 0{\color{red}1}1010011 $
3. Select the $ 8 $ -th candle: $ 0110100{\color{red}1}1\to 1001011{\color{red}1}0 $
4. Select the $ 7 $ -th candle: $ 100101{\color{red}1}10\to 011010{\color{red}1}01 $

## 样例 #1

### 输入

```
5
5
11010
11010
2
01
11
3
000
101
9
100010111
101101100
9
001011011
011010101```

### 输出

```
0
1
-1
3
4```

# AI分析结果

### 题目翻译
### 烛台

#### 题目描述
光明节的烛台上有 $n$ 根蜡烛，其中一些蜡烛最初是点燃的。我们可以用一个二进制字符串 $s$ 来描述哪些蜡烛是点燃的，当且仅当 $s_i = 1$ 时，第 $i$ 根蜡烛是点燃的。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1615C/23095c0b536d5c6c64ebf4ef5c8e358f51d36118.png)
最初，蜡烛的点亮情况用字符串 $a$ 表示。在一次操作中，你选择一根当前点亮的蜡烛。这样做后，你选择的蜡烛将保持点亮状态，而其他每根蜡烛都会改变状态（如果它是点亮的，它将熄灭；如果它是熄灭的，它将点亮）。

你希望使蜡烛的状态看起来与字符串 $b$ 相同。你的任务是确定是否可能，如果可能，找出所需的最少操作次数。

#### 说明/提示
在第一个测试用例中，两个字符串已经相等，所以我们不需要执行任何操作。

在第二个测试用例中，我们可以执行一次操作，选择第二根蜡烛，将 $01$ 转换为 $11$。

在第三个测试用例中，由于没有点亮的蜡烛可供选择，所以不可能执行任何操作。

在第四个测试用例中，我们可以执行以下操作将 $a$ 转换为 $b$：
1. 选择第 $7$ 根蜡烛：$100010{\color{red}1}11 \to 011101{\color{red} 1}00$。
2. 选择第 $2$ 根蜡烛：$0{\color{red} 1}1101100 \to 1{\color{red} 1}0010011$。
3. 选择第 $1$ 根蜡烛：${\color{red}1}10010011 \to {\color{red}1}01101100$。

在第五个测试用例中，我们可以执行以下操作将 $a$ 转换为 $b$：
1. 选择第 $6$ 根蜡烛：$00101{\color{red}1}011 \to 11010{\color{red}1}100$。
2. 选择第 $2$ 根蜡烛：$1{\color{red}1}0101100 \to 0{\color{red}1}1010011$。
3. 选择第 $8$ 根蜡烛：$0110100{\color{red}1}1 \to 1001011{\color{red}1}0$。
4. 选择第 $7$ 根蜡烛：$100101{\color{red}1}10 \to 011010{\color{red}1}01$。

#### 样例 #1
##### 输入
```
5
5
11010
11010
2
01
11
3
000
101
9
100010111
101101100
9
001011011
011010101
```
##### 输出
```
0
1
-1
3
4
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先挖掘操作的性质，即同一位置操作两次相当于没操作，不同位置各操作一次相当于交换两个位置的数。然后根据操作次数的奇偶性进行分类讨论：
 - **偶数次操作**：当两个字符串中 `0` 和 `1` 的数量分别相等时，可以通过若干次交换操作使两个字符串相等，操作次数为两个字符串中不同位置的数量。
 - **奇数次操作**：先选择一个两个字符串都为 `1` 的位置进行一次操作，若操作后两个字符串中 `0` 和 `1` 的数量分别相等，则可以继续通过交换操作使两个字符串相等，操作次数为原来两个字符串中相同位置的数量。

各题解的区别主要在于代码实现的细节和变量的命名，但整体思路是一致的。

### 所选题解
- **作者：LCat90 (赞：13)，4星**
    - **关键亮点**：思路清晰，代码简洁，直接通过统计 `0` 和 `1` 的数量以及不同位置的数量来判断是否可以转换，并计算最小操作次数。
- **作者：小薛小薛 (赞：4)，4星**
    - **关键亮点**：对偶数次操作和奇数次操作的情况分析详细，代码逻辑清晰，易于理解。
- **作者：Eazin_star (赞：2)，4星**
    - **关键亮点**：明确总结出两个重要性质，代码实现简洁明了，通过判断两种情况取最小值得到结果。

### 重点代码
#### LCat90 的代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int Maxn = 1e5 + 5;
int t, n;
char a[Maxn], b[Maxn];
int main() {
    scanf("%d", &t);
    while(t--) {
        int s = 0, s1 = 0, s2 = 0;
        scanf("%d", &n);
        scanf("%s %s", a + 1, b + 1);
        for(int i = 1;i <= n; ++i) {
            s += a[i] != b[i];
            if(a[i] == '1') s1 ++;
            if(b[i] == '1') s2 ++; 
        }
        int ans = 0x3f3f3f3f;
        if(s1 == s2) ans = s;
        if(n - s1 == s2 - 1) ans = min(ans, n - s);
        printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    }
    return 0;
}
```
**核心实现思想**：先统计两个字符串中不同位置的数量 `s`，以及两个字符串中 `1` 的数量 `s1` 和 `s2`。如果 `s1` 等于 `s2`，则可以通过偶数次操作使两个字符串相等，操作次数为 `s`；如果 `n - s1` 等于 `s2 - 1`，则可以通过奇数次操作使两个字符串相等，操作次数为 `n - s`。最后取两种情况的最小值作为答案，如果都不满足则输出 `-1`。

#### 小薛小薛的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{   
    int n,oa=0,ob=0,dif=0;
    cin >> n;
    string a, b;
    cin >> a >> b;
    for (int i = 0; i < n; i++)
    {
        oa += a[i] - '0', ob += b[i] - '0', dif += a[i] != b[i];
    }
    int A = 1e9;
    if (oa == ob)A = dif;
    if ((n - oa) == ob - 1)A = min(A, n - dif);
    cout << (A == 1e9 ? -1 : A )<<endl;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
```
**核心实现思想**：统计两个字符串中 `1` 的数量 `oa` 和 `ob`，以及不同位置的数量 `dif`。如果 `oa` 等于 `ob`，则可以通过偶数次操作使两个字符串相等，操作次数为 `dif`；如果 `n - oa` 等于 `ob - 1`，则可以通过奇数次操作使两个字符串相等，操作次数为 `n - dif`。最后取两种情况的最小值作为答案，如果都不满足则输出 `-1`。

#### Eazin_star 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;
string a, b;
int main() {
    scanf("%d", &t);
    while (t--) {
        int cnt = 0, cnta = 0, cntb = 0, ans = 0x3f3f3f3f;
        scanf("%d", &n);
        cin >> a >> b;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) cnt++;
            if (a[i] == '1') cnta++;
            if (b[i] == '1') cntb++;
        }
        if (cnta == cntb) ans = cnt;
        if (n-cnta == cntb-1) ans = min(ans, n-cnt);
        if (ans == 0x3f3f3f3f) printf("-1\n");
        else printf("%d\n", ans);
    }	
    return 0;
} 
```
**核心实现思想**：统计两个字符串中不同位置的数量 `cnt`，以及两个字符串中 `1` 的数量 `cnta` 和 `cntb`。如果 `cnta` 等于 `cntb`，则可以通过偶数次操作使两个字符串相等，操作次数为 `cnt`；如果 `n - cnta` 等于 `cntb - 1`，则可以通过奇数次操作使两个字符串相等，操作次数为 `n - cnt`。最后取两种情况的最小值作为答案，如果都不满足则输出 `-1`。

### 关键思路或技巧
- **操作性质的挖掘**：发现同一位置操作两次相当于没操作，不同位置各操作一次相当于交换两个位置的数，这是解决本题的关键。
- **分类讨论**：根据操作次数的奇偶性进行分类讨论，分别判断是否可以通过操作使两个字符串相等，并计算最小操作次数。

### 拓展思路
同类型题或类似算法套路：这类题目通常需要先挖掘操作的性质，然后根据性质进行分类讨论。常见的有位运算操作、状态转换等类型的题目，例如通过位运算改变数字的状态，或者通过一系列操作将一个序列转换为另一个序列等。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：需要根据操作的规则和条件进行分类讨论，判断某个点是否被地毯覆盖。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：通过模拟操作，统计剩余树的数量，需要考虑操作的影响和边界条件。
- [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)：需要对输入的数字进行统计和分类，根据统计结果进行输出。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：71.99秒