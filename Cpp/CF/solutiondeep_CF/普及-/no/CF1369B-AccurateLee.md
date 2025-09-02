# 题目信息

# AccurateLee

## 题目描述

Lee was cleaning his house for the party when he found a messy string under the carpets. Now he'd like to make it clean accurately and in a stylish way...

The string $ s $ he found is a binary string of length $ n $ (i. e. string consists only of 0-s and 1-s).

In one move he can choose two consecutive characters $ s_i $ and $ s_{i+1} $ , and if $ s_i $ is 1 and $ s_{i + 1} $ is 0, he can erase exactly one of them (he can choose which one to erase but he can't erase both characters simultaneously). The string shrinks after erasing.

Lee can make an arbitrary number of moves (possibly zero) and he'd like to make the string $ s $ as clean as possible. He thinks for two different strings $ x $ and $ y $ , the shorter string is cleaner, and if they are the same length, then the lexicographically smaller string is cleaner.

Now you should answer $ t $ test cases: for the $ i $ -th test case, print the cleanest possible string that Lee can get by doing some number of moves.

Small reminder: if we have two strings $ x $ and $ y $ of the same length then $ x $ is lexicographically smaller than $ y $ if there is a position $ i $ such that $ x_1 = y_1 $ , $ x_2 =       y_2 $ ,..., $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ .

## 说明/提示

In the first test case, Lee can't perform any moves.

In the second test case, Lee should erase $ s_2 $ .

In the third test case, Lee can make moves, for example, in the following order: 11001101 $ \rightarrow $ 1100101 $ \rightarrow $ 110101 $ \rightarrow $ 10101 $ \rightarrow $ 1101 $ \rightarrow $ 101 $ \rightarrow $ 01.

## 样例 #1

### 输入

```
5
10
0001111111
4
0101
8
11001101
10
1110000000
1
1```

### 输出

```
0001111111
001
01
0
1```

# AI分析结果

### 题目内容
AccurateLee

#### 题目描述
Lee在为派对打扫房子时，在地毯下发现了一个杂乱的字符串。现在他想用一种准确且时尚的方式将其清理干净。

他发现的字符串 $s$ 是一个长度为 $n$ 的二进制字符串（即字符串仅由0和1组成）。

在一次移动中，他可以选择两个连续的字符 $s_i$ 和 $s_{i + 1}$，如果 $s_i$ 是1且 $s_{i + 1}$ 是0，他可以准确地删除其中一个（他可以选择删除哪一个，但不能同时删除两个字符）。删除后字符串会收缩。

Lee可以进行任意次移动（可能为零次），并且他希望使字符串 $s$ 尽可能干净。他认为对于两个不同的字符串 $x$ 和 $y$，较短的字符串更干净，如果它们长度相同，那么字典序较小的字符串更干净。

现在你需要回答 $t$ 个测试用例：对于第 $i$ 个测试用例，打印Lee通过进行若干次移动可以得到的最干净的字符串。

小提示：如果我们有两个长度相同的字符串 $x$ 和 $y$，那么如果存在一个位置 $i$ 使得 $x_1 = y_1$，$x_2 = y_2$，...，$x_{i - 1} = y_{i - 1}$ 且 $x_i < y_i$，则 $x$ 的字典序小于 $y$。

#### 说明/提示
在第一个测试用例中，Lee无法执行任何移动。

在第二个测试用例中，Lee应该删除 $s_2$。

在第三个测试用例中，Lee可以按以下顺序进行移动：11001101 $\rightarrow$ 1100101 $\rightarrow$ 110101 $\rightarrow$ 10101 $\rightarrow$ 1101 $\rightarrow$ 101 $\rightarrow$ 01。

#### 样例 #1
**输入**
```
5
10
0001111111
4
0101
8
11001101
10
1110000000
1
1
```
**输出**
```
0001111111
001
01
0
1
```

### 算法分类
贪心

### 题解综合分析与结论
- **思路**：大多题解通过找规律，发现对于从1开始以0结束的子串都能化为`10`进而化为`0`，所以重点在于分离出字符串前后不可处理的`0`和`1`部分，再处理中间部分。
- **算法要点**：找出字符串前面连续的`0`和后面连续的`1`，对于中间部分，因为其开头为`1`结尾为`0`，根据规则能处理为`0`。最后将处理后的各部分组合输出。
- **解决难点**：核心难点在于总结出字符串处理的规律，即何种形式的子串能化简以及如何化简能保证字典序最小。部分题解采用模拟删除过程的方式，虽能解决问题，但相对复杂，不如直接利用规律简洁高效。

### 所选的题解
- **作者：namelessgugugu (5星)**
    - **关键亮点**：思路清晰，直接推导出字符串处理规律，代码简洁明了，通过寻找满足特定条件的`l`和`r`，直接对字符串进行处理输出，没有多余复杂操作。
    - **核心代码**：
```cpp
#include <cstdio>
#include <cstring>
const int N = 100005;
int t, n;
char str[N];
int main(void)
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%s", &n, str+1);
        int l = 1, r = n;
        while(str[l] == '0')
            ++l;
        while(str[r] == '1')
            --r;
        if(l > r) 
            printf("%s\n", str+1);
        else
        {
            for(int i = 1;i < l;++i)
                putchar(str[i]);
            putchar('0');
            for(int i = r+1;i <= n;++i)
                putchar(str[i]);
            putchar('\n');
        }
    }
    return 0;
}
```
    - **核心实现思想**：先读入测试用例数`T`，对于每个测试用例，读入字符串长度`n`和字符串`str`。通过循环找到字符串中第一个非`0`字符位置`l`和最后一个非`1`字符位置`r`。若`l > r`，说明字符串已最简，直接输出；否则，输出前面的`0`部分，再输出一个`0`（中间部分处理结果），最后输出后面的`1`部分。
- **作者：hzr6767 (4星)**
    - **关键亮点**：以通俗易懂的方式详细阐述了思路，通过模拟中间部分处理过程帮助理解，代码采用`string`类型，操作较为直观。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std; 
int main() {
    int t;
    cin >> t; 
    while (t --) {
        int len;
        string str, cnt = "";
        cin >> len >> str;
        int le = 0, rig = len - 1;
        while (str[le] == '0') {
            cnt += '0';
            le ++;
        }
        while (str[rig] == '1') {
            cnt += '1';
            rig --;
        }
        for (int i = le; i <= rig; i ++) {
            if (str[i] == '0') {
                cout << 0;
                break;
            }
        }
        cout << cnt << endl; 
    }
    return 0;
}
```
    - **核心实现思想**：读入测试用例数`t`，对每个测试用例，读入字符串长度`len`和字符串`str`。通过循环找到前面连续`0`的部分和后面连续`1`的部分存入`cnt`。再遍历中间部分，若有`0`则输出`0`，最后输出`cnt`。
- **作者：Berd__ (4星)**
    - **关键亮点**：简洁地阐述思路，代码风格简洁，利用`string`类型处理字符串，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define T kkk
using namespace std;
signed main(){
    int T,n;
    cin>>T;
    for(int i=1;i<=T;i++){
        string s,a="";
        cin>>n>>s;
        int l=0,r=n-1;
        while(s[l]=='0')
            l++,a+='0';
        while(s[r]=='1')
            r--,a+='1';
        for(int j=l;j<=r;j++)
            if(s[j]=='0'){
                cout<<'0';
                break;
            }
        cout<<a;
    }
    return 0;
}
```
    - **核心实现思想**：与hzr6767的思路类似，读入测试用例数`T`和每个测试用例的字符串长度`n`及字符串`s`。通过循环记录前面连续`0`和后面连续`1`存入`a`，遍历中间部分若有`0`输出`0`，最后输出`a`。

### 最优关键思路或技巧
通过找规律发现从1开始以0结束的子串可化为`0`，从而将字符串分为前面连续的`0`、中间可化为`0`的部分、后面连续的`1`这三部分处理，这种利用规律直接处理的方式避免了复杂的模拟删除操作，是解决本题的高效思路。

### 可拓展之处
同类型题常出现在字符串规律处理、贪心策略应用场景中。类似算法套路是先对给定操作和字符串特性进行分析，总结出化简规律，再根据规律对字符串进行分段处理，以达到题目要求。

### 洛谷相似题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：同样考察贪心策略，通过合并果子的操作求最小代价。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则找到最优策略，与本题找规律贪心选择类似。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：利用贪心思想对生产调度进行安排，优化生产时间。 

---
处理用时：73.09秒