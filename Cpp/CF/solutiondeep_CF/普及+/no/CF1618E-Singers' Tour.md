# 题目信息

# Singers' Tour

## 题目描述

$ n $ towns are arranged in a circle sequentially. The towns are numbered from $ 1 $ to $ n $ in clockwise order. In the $ i $ -th town, there lives a singer with a repertoire of $ a_i $ minutes for each $ i \in [1, n] $ .

Each singer visited all $ n $ towns in clockwise order, starting with the town he lives in, and gave exactly one concert in each town. In addition, in each town, the $ i $ -th singer got inspired and came up with a song that lasts $ a_i $ minutes. The song was added to his repertoire so that he could perform it in the rest of the cities.

Hence, for the $ i $ -th singer, the concert in the $ i $ -th town will last $ a_i $ minutes, in the $ (i + 1) $ -th town the concert will last $ 2 \cdot a_i $ minutes, ..., in the $ ((i + k) \bmod n + 1) $ -th town the duration of the concert will be $ (k + 2) \cdot a_i $ , ..., in the town $ ((i + n - 2) \bmod n + 1) $ — $ n \cdot a_i $ minutes.

You are given an array of $ b $ integer numbers, where $ b_i $ is the total duration of concerts in the $ i $ -th town. Reconstruct any correct sequence of positive integers $ a $ or say that it is impossible.

## 说明/提示

Let's consider the $ 1 $ -st test case of the example:

1. the $ 1 $ -st singer in the $ 1 $ -st city will give a concert for $ 3 $ minutes, in the $ 2 $ -nd — for $ 6 $ minutes, in the $ 3 $ -rd — for $ 9 $ minutes;
2. the $ 2 $ -nd singer in the $ 1 $ -st city will give a concert for $ 3 $ minutes, in the $ 2 $ -nd — for $ 1 $ minute, in the $ 3 $ -rd - for $ 2 $ minutes;
3. the $ 3 $ -rd singer in the $ 1 $ -st city will give a concert for $ 6 $ minutes, in the $ 2 $ -nd — for $ 9 $ minutes, in the $ 3 $ -rd — for $ 3 $ minutes.

## 样例 #1

### 输入

```
4
3
12 16 14
1
1
3
1 2 3
6
81 75 75 93 93 87```

### 输出

```
YES
3 1 3 
YES
1 
NO
YES
5 5 4 1 4 5```

# AI分析结果

### 题目中文重写
# 歌手巡演

## 题目描述
有 $n$ 个城镇按顺时针顺序依次排列成一个圆圈。城镇从 $1$ 到 $n$ 按顺时针方向编号。对于每个 $i \in [1, n]$，第 $i$ 个城镇有一位歌手，其曲目时长为 $a_i$ 分钟。

每位歌手都按顺时针顺序访问了所有 $n$ 个城镇，从他所在的城镇开始，并在每个城镇恰好举办一场音乐会。此外，在每个城镇，第 $i$ 位歌手都获得了灵感，创作了一首时长为 $a_i$ 分钟的歌曲。这首歌曲被添加到他的曲目中，以便他可以在其余的城市中演唱。

因此，对于第 $i$ 位歌手，在第 $i$ 个城镇的音乐会将持续 $a_i$ 分钟，在第 $(i + 1)$ 个城镇的音乐会将持续 $2 \cdot a_i$ 分钟，……，在第 $((i + k) \bmod n + 1)$ 个城镇的音乐会时长将为 $(k + 2) \cdot a_i$ 分钟，……，在第 $((i + n - 2) \bmod n + 1)$ 个城镇的音乐会时长为 $n \cdot a_i$ 分钟。

给定一个包含 $b$ 个整数的数组，其中 $b_i$ 是第 $i$ 个城镇的音乐会总时长。重构任何正确的正整数序列 $a$，或者说明这是不可能的。

## 说明/提示
让我们考虑示例中的第一个测试用例：
1. 第一位歌手在第一个城市的音乐会时长为 $3$ 分钟，在第二个城市为 $6$ 分钟，在第三个城市为 $9$ 分钟；
2. 第二位歌手在第一个城市的音乐会时长为 $3$ 分钟，在第二个城市为 $1$ 分钟，在第三个城市为 $2$ 分钟；
3. 第三位歌手在第一个城市的音乐会时长为 $6$ 分钟，在第二个城市为 $9$ 分钟，在第三个城市为 $3$ 分钟。

## 样例 #1
### 输入
```
4
3
12 16 14
1
1
3
1 2 3
6
81 75 75 93 93 87
```

### 输出
```
YES
3 1 3 
YES
1 
NO
YES
5 5 4 1 4 5
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过对题目所给条件列出线性方程组，然后通过方程的变形和运算来求解出 $a$ 数组。具体做法是先将所有方程相加求出 $\sum a_i$ 的表达式，再通过相邻方程相减得到关于单个 $a_i$ 的表达式。在求解过程中，需要注意判断计算结果是否为正整数，若不满足则说明无法构造出符合要求的 $a$ 数组。

### 所选题解
- **Bbaka（4星）**
  - **关键亮点**：思路清晰，详细地展示了从列方程到求解的每一步推导过程，代码实现简洁明了，易于理解。

### 重点代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long n;
long long a[50009],b[50009];
int main () {
    cin>>t;
    while (t--) {
        cin>>n;
        long long sum=0;
        for (int i = 1; i <= n;++i) {
            cin>>b[i];
            sum+=b[i];
        }
        if (sum%(((1 + n) * n / 2))!=0) {
            cout<<"NO"<<endl;
            continue;
        }
        sum/=((1+n)*n/2);
        long long S=0;
        bool check=true;
        for (int i=2;i<=n;++i) {
            if ((b[i-1]-b[i]+sum)%n!=0||(b[i-1]-b[i]+sum)<=0)
                check=false;
            a[i]=(b[i-1]-b[i]+sum)/n;
        }
        if ((b[n]-b[1]+sum)%n!=0||(b[n]-b[1]+sum)<=0)
            check=false;
        a[1]=(b[n]-b[1]+sum)/n;
        if (check==false) {
            cout<<"NO"<<endl;
            continue;
        }
        cout<<"YES"<<endl;
        for (int i=1;i<=n;++i)
            cout<<a[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```
**核心实现思想**：先读取输入的 $t$ 组数据，对于每组数据，读取 $n$ 和 $b$ 数组，并计算 $b$ 数组的总和。通过判断总和是否能被 $\frac{n(n + 1)}{2}$ 整除来确定是否有解。若有解，则根据相邻方程相减得到的表达式计算 $a$ 数组的每个元素，同时判断计算结果是否为正整数。最后根据判断结果输出 `YES` 或 `NO` 以及 $a$ 数组。

### 最优关键思路或技巧
- 通过对线性方程组进行相加和相减的操作，巧妙地消去多余的未知数，从而得到 $\sum a_i$ 和单个 $a_i$ 的表达式。
- 在计算过程中，通过判断除法是否整除以及结果是否为正整数来确定是否有解，避免了复杂的计算和判断。

### 可拓展之处
同类型题目可能会改变方程组的形式或增加一些额外的条件，但解题的核心思路仍然是通过对方程组进行变形和运算来求解未知数。类似的算法套路可以应用于其他需要求解线性方程组的问题中。

### 推荐洛谷题目
- P1082 [NOIP2012 提高组] 同余方程
- P1516 青蛙的约会
- P3811 【模板】乘法逆元

---
处理用时：39.60秒