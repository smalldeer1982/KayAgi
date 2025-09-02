# 题目信息

# Card Constructions

## 题目描述

A card pyramid of height $ 1 $ is constructed by resting two cards against each other. For $ h>1 $ , a card pyramid of height $ h $ is constructed by placing a card pyramid of height $ h-1 $ onto a base. A base consists of $ h $ pyramids of height $ 1 $ , and $ h-1 $ cards on top. For example, card pyramids of heights $ 1 $ , $ 2 $ , and $ 3 $ look as follows:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345B/c8f889835ab0788603a3c97f750b5560a2dca9f4.png)You start with $ n $ cards and build the tallest pyramid that you can. If there are some cards remaining, you build the tallest pyramid possible with the remaining cards. You repeat this process until it is impossible to build another pyramid. In the end, how many pyramids will you have constructed?

## 说明/提示

In the first test, you construct a pyramid of height $ 1 $ with $ 2 $ cards. There is $ 1 $ card remaining, which is not enough to build a pyramid.

In the second test, you build two pyramids, each of height $ 2 $ , with no cards remaining.

In the third test, you build one pyramid of height $ 3 $ , with no cards remaining.

In the fourth test, you build one pyramid of height $ 3 $ with $ 9 $ cards remaining. Then you build a pyramid of height $ 2 $ with $ 2 $ cards remaining. Then you build a final pyramid of height $ 1 $ with no cards remaining.

In the fifth test, one card is not enough to build any pyramids.

## 样例 #1

### 输入

```
5
3
14
15
24
1```

### 输出

```
1
2
1
3
0```

# AI分析结果

### 题目内容
# 纸牌搭建

## 题目描述
高度为1的纸牌金字塔由两张纸牌相互倚靠构成。对于$h>1$，高度为$h$的纸牌金字塔通过将高度为$h - 1$的纸牌金字塔放置在一个底座上构建而成。一个底座由$h$个高度为1的金字塔和$h - 1$张纸牌堆叠在顶部组成。例如，高度为1、2和3的纸牌金字塔如下所示：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345B/c8f889835ab0788603a3c97f750b5560a2dca9f4.png)
你一开始有$n$张纸牌，并构建出你所能搭建的最高金字塔。如果还有剩余纸牌，再用剩余纸牌构建出所能搭建的最高金字塔。重复这个过程，直到无法再构建金字塔为止。最终，你一共构建了多少个金字塔？

## 说明/提示
在第一个测试用例中，你用2张纸牌构建了一个高度为1的金字塔。还剩下1张纸牌，不足以构建一个金字塔。

在第二个测试用例中，你构建了两个高度为2的金字塔，没有剩余纸牌。

在第三个测试用例中，你构建了一个高度为3的金字塔，没有剩余纸牌。

在第四个测试用例中，你用9张纸牌构建了一个高度为3的金字塔，还剩下9张纸牌。然后用剩下的纸牌构建一个高度为2的金字塔，还剩下2张纸牌。最后用这2张纸牌构建一个高度为1的金字塔，没有剩余纸牌。

在第五个测试用例中，1张纸牌不足以构建任何金字塔。

## 样例 #1
### 输入
```
5
3
14
15
24
1```
### 输出
```
1
2
1
3
0```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先确定搭建不同高度金字塔所需纸牌数，再通过贪心策略，每次选取能搭建的最高金字塔，直到纸牌不足。
- **思路方面**：部分题解通过打表得到搭建高度为`h`的金字塔所需纸牌数，有些题解直接利用数学推导得出公式。之后，有的采用二分查找寻找当前能搭建的最高金字塔，有的直接根据公式计算高度。
- **算法要点**：关键在于准确得出搭建不同高度金字塔所需纸牌数，并高效地找出每次可搭建的最高金字塔。
- **解决难点**：难点在于发现搭建金字塔纸牌数的规律，以及如何优化查找每次可搭建最高金字塔的过程。

### 所选的题解
- **作者：bbbzzx (5星)**
  - **关键亮点**：直接利用数学推导得出高度为$n$的卡片堆用去$\frac{n(3n + 1)}{2}$张卡片的公式，无需二分或打表，代码简洁高效。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,h,s,k;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        s=0,k=n;
        while(k>1)
        {
            h=floor((sqrt(1+24*k)-1)/6);
            k-=(h*(3*h+1))/2;
            s++;
        }
        cout<<s<<endl;
    }
    return 0;
}
```
  - **核心思想**：通过公式直接计算每次能搭建的金字塔高度`h`，然后更新剩余纸牌数`k`，并统计搭建金字塔的数量`s`。
- **作者：Isshiki_Hugh (4星)**
  - **关键亮点**：思路清晰，先通过递推式打表得到搭建不同高度金字塔所需纸牌数，再利用二分查找每次能搭建的最高金字塔。
  - **核心代码**：
```cpp
int T,a[30000],ans,m;

inline ll find(ll x){
    int l = 1, r = 27000;
    while(l <= r){
        m = (l + r) / 2;
        if(a[m] == x) return m;
        else if(a[m] < x) l = m + 1;
        else r = m - 1;
    }
    if(a[m] == x) return m;
    else if(a[m] < x) return m;
    else return m = m-1;
}
int main(){
    cin >> T;
    ll x;
    a[1] = 2;
    rep(i,1,27000) a[i] = a[i-1] + 3 * i -1;

    while(T--){
        ans = 0;
        cin >> x;
        while(find(x) > 0){
            x -= a[m];
            ++ans;
        }
        cout << ans << "\n";
    }

    return 0;
}
```
  - **核心思想**：先打表填充数组`a`记录不同高度金字塔所需纸牌数，通过`find`函数二分查找当前纸牌数`x`能搭建的最高金字塔高度，更新纸牌数`x`并统计搭建数量`ans`。
- **作者：andyli (4星)**
  - **关键亮点**：借助OEIS A005449得出高度为$n$用去$\dfrac{n(3n + 1)}{2}$个卡片的公式，利用二分查找最大可能的卡片数，代码简洁明了。
  - **核心代码**：
```cpp
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        int cnt = 0;
        while (n > 1) {
            int l = 1, r = n;
            while (l < r) {
                int m = (l + r + 1) >> 1;
                if (LL(m) * (3LL * m + 1) / 2 <= n)
                    l = m;
                else
                    r = m - 1;
            }
            cnt++;
            n -= LL(l) * (3LL * l + 1) / 2;
        }
        writeln(cnt);
    }
    return 0;
}
```
  - **核心思想**：利用公式在循环中二分查找当前纸牌数`n`能搭建的最高金字塔高度，更新纸牌数`n`并统计搭建数量`cnt`。

### 最优思路或技巧
- **数学推导**：直接得出搭建高度为$n$的金字塔所需纸牌数公式$\frac{n(3n + 1)}{2}$，可避免打表，提高效率。
- **二分查找**：在已知所需纸牌数的情况下，通过二分查找能快速确定当前可搭建的最高金字塔高度，优化查找过程。

### 同类型题或类似算法套路
此类题目通常涉及找规律得出数学公式，再结合贪心策略解决问题。遇到类似构建物体并统计数量的题目，可先尝试找规律得出关键数据的计算公式，再根据题目要求选择合适的查找或遍历方法。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：同样是贪心策略，通过不断合并果子使总代价最小。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：需根据题目条件找出贪心策略，合理安排生产顺序。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对数据排序，依据贪心策略解决问题。 

---
处理用时：67.10秒