# 题目信息

# Three Threadlets

## 题目描述

Once upon a time, bartender Decim found three threadlets and a pair of scissors.

In one operation, Decim chooses any threadlet and cuts it into two threadlets, whose lengths are positive integers and their sum is equal to the length of the threadlet being cut.

For example, he can cut a threadlet of length $ 5 $ into threadlets of lengths $ 2 $ and $ 3 $ , but he cannot cut it into threadlets of lengths $ 2.5 $ and $ 2.5 $ , or lengths $ 0 $ and $ 5 $ , or lengths $ 3 $ and $ 4 $ .

Decim can perform at most three operations. He is allowed to cut the threadlets obtained from previous cuts. Will he be able to make all the threadlets of equal length?

## 说明/提示

Let's consider some testcases of the first test.

In the first testcase, you can apply following operations:

 $ 1, 3, 2 \to 1, 2, 1, 2 \to 1, 1, 1, 1, 2 \to 1, 1, 1, 1, 1, 1 $ .

In the second testcase, you can do nothing, the threadlets are already of equal length.

In the third testcase, it isn't possible to make threadlets of equal length.

## 样例 #1

### 输入

```
15
1 3 2
5 5 5
6 36 12
7 8 7
6 3 3
4 4 12
12 6 8
1000000000 1000000000 1000000000
3 7 1
9 9 1
9 3 6
2 8 2
5 3 10
8 4 8
2 8 4```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
NO
NO
YES
YES
NO
YES
NO```

# AI分析结果

### 中文重写题目内容
# 三条线绳

## 题目描述
从前，酒保德西姆（Decim）发现了三条线绳和一把剪刀。

在一次操作中，德西姆选择任意一条线绳并将其剪成两条线绳，这两条线绳的长度为正整数，且它们的长度之和等于被剪线绳的长度。

例如，他可以将一条长度为 5 的线绳剪成长度为 2 和 3 的线绳，但不能剪成长度为 2.5 和 2.5 的线绳，也不能剪成长度为 0 和 5 的线绳，或者长度为 3 和 4 的线绳。

德西姆最多可以进行三次操作。他被允许对之前操作得到的线绳进行裁剪。他是否能够使所有线绳的长度相等？

## 说明/提示
让我们考虑第一个测试的一些测试用例。

在第一个测试用例中，你可以进行以下操作：
1, 3, 2 → 1, 2, 1, 2 → 1, 1, 1, 1, 2 → 1, 1, 1, 1, 1, 1 。

在第二个测试用例中，你什么都不用做，线绳的长度已经相等。

在第三个测试用例中，不可能使线绳的长度相等。

## 样例 #1

### 输入
```
15
1 3 2
5 5 5
6 36 12
7 8 7
6 3 3
4 4 12
12 6 8
1000000000 1000000000 1000000000
3 7 1
9 9 1
9 3 6
2 8 2
5 3 10
8 4 8
2 8 4
```

### 输出
```
YES
YES
NO
NO
YES
YES
NO
YES
NO
NO
YES
YES
NO
YES
NO
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分析三个数之间的关系，判断是否能在三次操作内让所有数相等。大部分题解是通过分类讨论满足条件的数的组合形式，如 `(a,a,a)`、`(a,a,2a)` 等；部分题解通过计算总和的因数以及判断数是否为因数的倍数来确定是否可行；还有题解通过模拟切割操作来判断。

各题解的算法要点和难点对比如下：
- **分类讨论类**：思路清晰，直接列举满足条件的数的组合，难点在于不遗漏情况。
- **因数判断类**：通过数学计算判断可行性，难点在于理解因数与切割操作的关系。
- **模拟操作类**：直观模拟切割过程，难点在于正确处理每次切割后的数组排序和状态更新。

### 所选题解
- **作者：wanghaoran00 (4星)**
    - **关键亮点**：思路清晰，代码简洁，直接列举所有满足条件的情况进行判断。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long T,a[10];
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%lld",&a[1],&a[2],&a[3]);
        sort(a+1,a+4);
        if((a[1]==a[2]&&a[2]==a[3])||(a[2]==a[3]&&a[2]==a[1]*2)||(a[1]==a[2]&&a[3]==a[1]*2)||(a[1]==a[2]&&a[3]==a[1]*3)||(a[1]==a[2]&&a[3]==a[1]*4)||(a[2]==a[1]*2&&a[3]==a[1]*3)){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
```
- **作者：include13_fAKe (4星)**
    - **关键亮点**：思路详细，对每种情况的讨论清晰，代码逻辑明确。
```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int a,b,c;
    cin>>a>>b>>c;
    if(a>b) swap(a,b);
    if(b>c) swap(b,c);
    if(a>b) swap(a,b);
    if(a==b&&b==c){
        puts("YES");
        return;
    }
    if(a==b&&(a*2==c||a*3==c||a*4==c)){
        puts("YES");
        return;
    }
    if(b==c&&a*2==b){
        puts("YES");
        return;
    }
    if(a*2==b&&a*3==c){
        puts("YES");
        return;
    }
    puts("NO");
    return;
}
int main(){
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```
- **作者：1234567890sjx (4星)**
    - **关键亮点**：将判断逻辑封装在函数中，代码结构清晰，时间复杂度低。
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

bool check(int *a) {
    if (a[0] == a[1] && a[1] == a[2]) return true;
    if (a[0] == a[1] && a[1] * 2 == a[2]) return true;
    if (a[0] == a[1] && a[1] * 3 == a[2]) return true;
    if (a[0] == a[1] && a[1] * 4 == a[2]) return true;
    if (a[0] * 2 == a[1] && a[0] * 2 == a[2]) return true;
    if (a[0] * 2 == a[1] && a[0] * 3 == a[2]) return true;
    return false;
}

void slv(int tc = 0) {
    if (tc) {
        cerr << "Test Case " << tc << '\n';
    }
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    sort(a, a + 3);
    cout << (check(a) ? "Yes" : "No") << '\n';
}

signed main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        slv(i + 1);
    }
    return 0;
}
```

### 最优关键思路或技巧
- 先对三个数进行排序，方便后续比较和分类讨论。
- 直接列举出满足条件的数的组合形式，通过简单的判断语句进行筛选。

### 拓展思路
同类型题可能会改变操作次数或数字个数，解题思路仍然是分析数字之间的关系，判断是否能通过有限次操作达到目标状态。类似算法套路包括分析数字的因数、倍数关系，以及模拟操作过程等。

### 推荐洛谷题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)

### 个人心得摘录与总结
- **作者：include13_fAKe**：“谨以此篇题解纪念我 CF 绿名”，表达了对解题和自身成长的纪念意义。 

---
处理用时：44.18秒