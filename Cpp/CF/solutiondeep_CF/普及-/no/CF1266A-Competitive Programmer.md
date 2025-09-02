# 题目信息

# Competitive Programmer

## 题目描述

Bob is a competitive programmer. He wants to become red, and for that he needs a strict training regime. He went to the annual meeting of grandmasters and asked $ n $ of them how much effort they needed to reach red.

"Oh, I just spent $ x_i $ hours solving problems", said the $ i $ -th of them.

Bob wants to train his math skills, so for each answer he wrote down the number of minutes ( $ 60 \cdot x_i $ ), thanked the grandmasters and went home. Bob could write numbers with leading zeroes — for example, if some grandmaster answered that he had spent $ 2 $ hours, Bob could write $ 000120 $ instead of $ 120 $ .

Alice wanted to tease Bob and so she took the numbers Bob wrote down, and for each of them she did one of the following independently:

- rearranged its digits, or
- wrote a random number.

This way, Alice generated $ n $ numbers, denoted $ y_1 $ , ..., $ y_n $ .

For each of the numbers, help Bob determine whether $ y_i $ can be a permutation of a number divisible by $ 60 $ (possibly with leading zeroes).

## 说明/提示

In the first example, there is one rearrangement that yields a number divisible by $ 60 $ , and that is $ 360 $ .

In the second example, there are two solutions. One is $ 060 $ and the second is $ 600 $ .

In the third example, there are $ 6 $ possible rearrangments: $ 025 $ , $ 052 $ , $ 205 $ , $ 250 $ , $ 502 $ , $ 520 $ . None of these numbers is divisible by $ 60 $ .

In the fourth example, there are $ 3 $ rearrangements: $ 228 $ , $ 282 $ , $ 822 $ .

In the fifth example, none of the $ 24 $ rearrangements result in a number divisible by $ 60 $ .

In the sixth example, note that $ 000\dots0 $ is a valid solution.

## 样例 #1

### 输入

```
6
603
006
205
228
1053
0000000000000000000000000000000000000000000000
```

### 输出

```
red
red
cyan
cyan
cyan
red
```

# AI分析结果

### 题目内容
# 竞技程序员

## 题目描述
鲍勃是一名竞技程序员。他想成为红名选手，为此他需要严格的训练计划。他参加了特级大师的年度会议，并询问了 $n$ 位大师他们为达到红名付出了多少努力。

“哦，我只花了 $x_i$ 小时来解题。”第 $i$ 位大师说道。

鲍勃想训练他的数学技能，所以对于每个答案，他都写下了对应的分钟数（$60 \cdot x_i$），向大师们表示感谢后就回家了。鲍勃可能会写下带前导零的数字 —— 例如，如果某位大师回答他花了 $2$ 小时，鲍勃可能会写 $000120$ 而不是 $120$。

爱丽丝想逗逗鲍勃，所以她拿走了鲍勃写下的数字，并且针对每个数字，她独立地进行了以下操作之一：
 - 重新排列其数字，或者
 - 写一个随机数。

通过这种方式，爱丽丝生成了 $n$ 个数字，记为 $y_1$，...，$y_n$。

对于每个数字，请帮助鲍勃确定 $y_i$ 是否可以是一个能被 $60$ 整除的数的排列（可能带有前导零）。

## 说明/提示
在第一个示例中，有一种重新排列能得到一个能被 $60$ 整除的数，即 $360$。

在第二个示例中，有两个解决方案。一个是 $060$，另一个是 $600$。

在第三个示例中，有 $6$ 种可能的重新排列：$025$，$052$，$205$，$250$，$502$，$520$。这些数字中没有一个能被 $60$ 整除。

在第四个示例中，有 $3$ 种重新排列：$228$，$282$，$822$。

在第五个示例中，$24$ 种重新排列中没有一个能得到能被 $60$ 整除的数。

在第六个示例中，请注意 $000\dots0$ 是一个有效的解决方案。

## 样例 #1
### 输入
```
6
603
006
205
228
1053
0000000000000000000000000000000000000000000000
```
### 输出
```
red
red
cyan
cyan
cyan
red
```

### 算法分类
数学

### 综合分析与结论
所有题解思路核心均为对数字进行因数分解判断。由于 $60 = 2^2×3×5$，可转化为判断能否被 $2$、$3$、$10$ 整除，或能否被 $3$ 和 $20$ 整除。各题解主要围绕如何判断这些整除条件展开，差异在于具体实现方式及细节处理。整体来看，题解质量差距不大，多数题解思路清晰，代码实现直接，但在优化程度和代码可读性上提升空间较小。

### 所选的题解
- **作者：1qaz234Q (5星)**
    - **关键亮点**：思路简洁清晰，直接利用 $60 = 3×20$ 的关系，通过判断数字和能否被 $3$ 整除、是否有 $0$ 以及除末尾 $0$ 外是否还有偶数来确定结果，代码实现简洁明了。
    - **重点代码核心实现思想**：遍历输入字符串，统计数字和、偶数个数并判断是否有 $0$，根据判断条件输出结果。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string a;
        bool flag = 0;
        int sum = 0; // 数字和
        int cnt = 0; // 偶数个数
        cin >> a;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] == '0') // 如果它为数字0
            {
                flag = 1;
            }
            sum += int(a[i] - '0');
            if (int(a[i] - '0') % 2 == 0) // 如果它为偶数
            {
                cnt++;
            }
        }
        cnt--;                               // 去掉末尾的0
        if (flag && sum % 3 == 0 && cnt > 0) // 如果它含数字0并且数字和能被3整除并且除末尾的0外还有另一个偶数
        {
            cout << "red" << endl;
        }
        else
        {
            cout << "cyan" << endl;
        }
    }
}
```
- **作者：可爱的甜甜猫 (4星)**
    - **关键亮点**：将判断过程封装成函数，使代码结构更清晰，逻辑更易读。同样基于判断能否被 $3$ 整除、是否有 $0$ 以及除 $0$ 外是否还有偶数来解题。
    - **重点代码核心实现思想**：定义函数 `f` 进行判断，遍历字符串统计数字和，标记是否有 $0$ 和除 $0$ 外的偶数，根据判断条件返回结果。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool f(string s){//使用函数判断，简单明了
    int sum=0;//用于统计各个数位上数字的和
    bool a=0,b=0;
   //a用于判断是否有0，b用于判断除此之外还有没有偶数
    for(int i=0;i<s.size();i++){
        int x=s[i]-'0';//x表示这个数位上的数
        sum+=x;//统计数位上数字之和
        if(x==0&&a==0){
            a=1;
            //如果在此之前没有0则将a的值改为1
        }else if(x%2==0){
            b=1;
            //除此之外有偶数，让b为1
        }
    }
    if(sum%3==0&&a==1&&b==1)return 1;
 //同时满足有0，除掉一个0还有偶数，各个数位的数之和能被三整除则返回1
    return 0;
 //否则返回0
}
int main(){
    int n;
    cin>>n;//我们需要判断n个数
    for(int i=1;i<=n;i++){
        string s;//使用字符串进行判断
        cin>>s;
        if(f(s)==1){
            cout<<"red"<<endl;
        }else{
            cout<<"cyan"<<endl;
        }
    }
    return 0;
}
```
- **作者：xvl_ (4星)**
    - **关键亮点**：对判断条件的分析较为详细，变量命名清晰，明确指出判断能否被 $2$、$3$、$10$ 整除的条件，同时注意到原数只出现一个 $0$ 时不能被 $10$ 和 $2$ 同时整除的特殊情况。
    - **重点代码核心实现思想**：遍历输入字符串，统计数位和、$0$ 的个数以及除 $0$ 以外的偶数个数，根据能否被 $2$、$3$、$10$ 整除的条件输出结果。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n;
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; // 不要用 int，否则会出错
        int sum = 0, cnt1 = 0, cnt2 = 0; // sum 是数位和，cnt1 是 0 的个数，cnt2 是除了 0 以外的偶数的个数
        bool flag1 = 0, flag2 = 0, flag3 = 0; // flag1 判断能否被 3 整除，flag2 判断能否被 10 整除，flag3 判断能够被 2 整除
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            int num = s[i] - '0';
            sum += num;
            if (num == 0) cnt1++;
            else if (num % 2 == 0) cnt2++;
        }
        if (sum % 3 == 0) flag1 = 1;
        if (cnt1) flag2 = 1;
        if (cnt2 or cnt1 > 1) flag3 = 1; // 如果有两个 0 也可以
        if (flag1 and flag2 and flag3) cout << "red\n";
        else cout << "cyan\n";
    }
    return 0;
}
```

### 最优关键思路或技巧
将 $60$ 进行因数分解，转化为判断能否被较小因数整除的问题，利用数字特性简化判断过程，如能被 $3$ 整除的数其各位数字之和能被 $3$ 整除，能被 $10$ 整除的数需含有 $0$ 等。同时，注意处理 $0$ 在被 $2$ 和 $10$ 整除判断中的特殊情况。

### 可拓展之处
同类型题通常围绕数论中的整除性质展开，类似算法套路是对目标数进行因数分解，根据因数的整除特性来设计判断逻辑。例如判断一个数能否通过数位重排被其他数整除，或者给定一些数，判断其组合能否满足特定的整除关系等。

### 相似知识点洛谷题目
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：通过对给定数进行质因数分解求解，考察数论基础和因数分解的实现。
- [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：需要利用数的排列组合以及特定的数学规律来构造幻方，涉及到数字特性和数学逻辑。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合斐波那契数列的性质和数论中求最大公约数的方法解题，对数论知识和数列性质的综合运用有一定要求。 

---
处理用时：98.09秒