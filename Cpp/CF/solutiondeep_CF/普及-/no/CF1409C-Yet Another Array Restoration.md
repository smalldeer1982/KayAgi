# 题目信息

# Yet Another Array Restoration

## 题目描述

We have a secret array. You don't know this array and you have to restore it. However, you know some facts about this array:

- The array consists of $ n $ distinct positive (greater than $ 0 $ ) integers.
- The array contains two elements $ x $ and $ y $ (these elements are known for you) such that $ x < y $ .
- If you sort the array in increasing order (such that $ a_1 < a_2 < \ldots < a_n $ ), differences between all adjacent (consecutive) elements are equal (i.e. $ a_2 - a_1 = a_3 - a_2 = \ldots = a_n - a_{n-1}) $ .

It can be proven that such an array always exists under the constraints given below.

Among all possible arrays that satisfy the given conditions, we ask you to restore one which has the minimum possible maximum element. In other words, you have to minimize $ \max(a_1, a_2, \dots, a_n) $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2 1 49
5 20 50
6 20 50
5 3 8
9 13 22```

### 输出

```
1 49 
20 40 30 50 10
26 32 20 38 44 50 
8 23 18 13 3 
1 10 13 4 19 22 25 16 7```

# AI分析结果

### 题目内容
#### 又一个数组恢复问题
1. **题目描述**：我们有一个秘密数组，你不知道这个数组，而你必须恢复它。不过，你知道关于这个数组的一些信息：
    - 该数组由\(n\)个不同的正整数（大于\(0\)）组成。
    - 数组包含两个元素\(x\)和\(y\)（这两个元素你是知道的），且\(x < y\)。
    - 如果你将数组按升序排序（使得\(a_1 < a_2 < \ldots < a_n\)），所有相邻（连续）元素之间的差值相等（即\(a_2 - a_1 = a_3 - a_2 = \ldots = a_n - a_{n - 1}\)）。
    可以证明，在下面给出的限制条件下，这样的数组总是存在的。
    在所有满足给定条件的可能数组中，我们要求你恢复出一个最大元素尽可能小的数组。换句话说，你必须最小化\(\max(a_1, a_2, \dots, a_n)\)。
    你必须回答\(t\)个独立的测试用例。
2. **样例 #1**
    - **输入**：
```
5
2 1 49
5 20 50
6 20 50
5 3 8
9 13 22
```
    - **输出**：
```
1 49 
20 40 30 50 10
26 32 20 38 44 50 
8 23 18 13 3 
1 10 13 4 19 22 25 16 7
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是基于等差数列的性质，利用\(x\)和\(y\)的差值确定可能的公差，进而构造出满足条件且最大元素最小的数组。
1. **思路方面**：多数题解通过枚举\(x\)与\(y\)差值的因数作为公差，再根据数列项数\(n\)和正整数的限制条件来构造数列。部分题解还考虑了贪心策略，优先向较小值方向扩展数列以保证最大值最小。
2. **算法要点**：确定公差的可能值，保证数列包含\(x\)和\(y\)，满足正整数和项数\(n\)的条件，同时使数列的最大值最小。
3. **解决难点**：主要难点在于如何在满足所有条件的情况下找到最小的最大元素。不同题解通过不同方式判断公差是否合法以及如何扩展数列来解决这一问题，例如通过对公差的枚举范围限制、对数列项数的计算和判断等。

### 所选的题解
- **作者：EternalHeart1314 (赞：4)  星级：4星**
    - **关键亮点**：思路清晰简洁，通过寻找满足\(s\bmod ans = 0\)且\(s\div ans + 1 \leq n\)（\(s\)为\(x\)和\(y\)的差）的最大\(ans\)作为公差，然后根据公差构造数列，代码实现逻辑流畅。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int t, n, x, y, s, ans;

int main() {
    cin >> t;
    while(t --) {
        cin >> n >> x >> y;
        s = abs(x - y);
        for(int i(1); i <= s; ++ i) {
            if(!(s % i) && s / i + 1 <= n) {
                ans = i;
                break;
            }
        }
        for(int i(min(x, y)), ed(max(x, y)); i <= ed; i += ans) {
            cout << i << ' ';
            -- n;
        }
        s = min(x, y);
        while(n --) {
            if((s -= ans) <= 0) {
                ++ n;
                break;
            }
            cout << s << ' ';
        }
        s = max(x, y);
        while(n -- > 0) {
            cout << (s += ans) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```
    - **核心实现思想**：先求出\(x\)与\(y\)的差值\(s\)，枚举\(s\)的因数作为可能的公差，找到满足条件的公差\(ans\)。先输出\(x\)到\(y\)之间符合公差的数，再从\(x\)和\(y\)分别向两侧扩展输出，直到输出够\(n\)个数。
- **作者：Carotrl (赞：4)  星级：4星**
    - **关键亮点**：从大到小枚举\(x\)到\(y\)的元素个数，从而确定差值（公差），并按此公差依次输出数列元素，若元素个数不足\(n\)，则从\(x\)向下、从\(y\)向上继续输出，逻辑明确。
    - **重点代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string> 
using namespace std;
int t,n,x,y;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&x,&y);
        int a=y-x;
        for(int i=n;i>=1;i--){
            if(a%(i-1)==0){
                int p=a/(i-1),j;
                for(j=1;j<=n;j++){
                    if(x+(j-1)*p>y)break;
                    printf("%d ",x+(j-1)*p);
                } 
                j--;
                j=n-j;
                for(int k=x-p;k>0&&j;k-=p)printf("%d ",k),j--;
                for(int k=y+p;j;k+=p)printf("%d ",k),j--;
                break;
            }
        }
        printf("\n");
    }
}
```
    - **核心实现思想**：计算\(x\)与\(y\)的差值\(a\)，从大到小枚举\(x\)到\(y\)间元素个数\(i\)，若\(a\)能被\(i - 1\)整除，则确定公差\(p\)。先输出\(x\)开始符合公差的数，再从\(x\)向下、\(y\)向上按公差输出，直到输出够\(n\)个数。
- **作者：huyangmu (赞：4)  星级：4星**
    - **关键亮点**：由于数据范围小，直接枚举首项和公差，通过公式计算最后一项并与当前答案比较，同时通过函数判断首项和公差是否满足要求，思路直接且容易理解。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,x,y;
bool check (int i,int j){
    double tmp = (x - i) * 1.0 / j;
    if (floor(tmp)!= tmp || (int)(tmp) > n - 1 || (int)(tmp) < 0){
        return 0;
    }
    tmp = (y - i) * 1.0 / j;
    if (floor(tmp)!= tmp || (int)(tmp) > n - 1 || (int)(tmp) < 0){
        return 0;
    }
    return 1;
}
signed main (){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> T;
    while (T --){
        cin >> n >> x >> y;
        int maxn = 0x3f3f3f3f, sum = 0, sum2 = 0;
        for (int i = 1; i <= 51; ++i){
            for (int j = 1; j <= 51; ++j){
                if (check(i,j) && maxn > i + (n - 1) * j){
                    maxn = i + (n - 1) * j;
                    sum = i;
                    sum2 = j; 
                }
            }
        }
        for (int i = sum; i <= maxn; i +=sum2) cout << i << ' ';
        cout << '\n'; 
    }
    return 0;
}
```
    - **核心实现思想**：定义`check`函数判断首项\(i\)和公差\(j\)是否合法，即\(x\)、\(y\)到首项的项数是否为整数且在合理范围。枚举所有可能的首项和公差，找到使最后一项最小的组合，然后输出该等差数列。

### 最优关键思路或技巧
1. **利用等差数列性质**：通过分析\(x\)和\(y\)在等差数列中的关系，确定公差一定是\(y - x\)的因数，从而缩小公差的枚举范围，这是解决问题的关键数学性质应用。
2. **贪心策略**：在构造数列时，优先向较小值方向扩展数列，这样能保证在满足条件的情况下使数列的最大值最小，这是优化结果的重要贪心思路。

### 可拓展之处
同类型题通常围绕数列的特定性质和限制条件构造数列，类似算法套路是先根据已知条件确定数列的关键参数（如公差、首项等）的可能范围，再通过枚举、贪心等策略找到满足要求的数列。例如给定数列的部分项和一些其他条件（如和的限制、项数限制等），构造出符合条件的数列。

### 洛谷相似题目推荐
1. **P1088 [NOIP2004 普及组] 火星人**：通过模拟和贪心策略解决排列相关问题，与本题在利用特定规则构造序列上思路相似。
2. **P1149 火柴棒等式**：通过枚举和判断条件来构造满足等式的组合，和本题枚举公差并判断条件构造数列类似。
3. **P1308 [NOIP2011 普及组] 统计单词数**：在字符串处理中结合特定条件进行枚举判断，与本题在一定范围内枚举并筛选符合条件的解思路相近。 

---
处理用时：86.01秒