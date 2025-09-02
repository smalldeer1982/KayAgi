# 题目信息

# Restore the Array

## 题目描述

Kristina 有一个包含 $ n $ 个**非负整数**的数组 $ a $。

她构造了一个长度为 $ n - 1 $ 的新数组 $ b $，使得 $ b_i = \max(a_i, a_{i + 1}) \text{ } (1 \le i \le n - 1) $。

例如，假设 Kristina 有一个长度为 $ 5 $ 的数组 $ a = [ 3, 0, 4, 0, 5 ] $，则她将以以下方式构造数组 $ b $：

1. $ b_1 = \max(a_1, a_2) = \max(3, 0) = 3; $
2. $ b_2 = \max(a_2, a_3) = \max(0, 4) = 4; $
3. $ b_3 = \max(a_3, a_4) = \max(4, 0) = 4; $
4. $ b_4 = \max(a_4, a_5) = \max(0, 5) = 5. $

所以，她得到了一个长度为 $ 4 $ 的数组 $ b = [ 3, 4, 4, 5 ] $。

现在，你只知道数组 $ b $。你需要找出**任意一个**可能的数组 $ a $。



对于第二组测试数据，我们可以从 $ a = [ 2, 2, 1, 1 ] $ 推出 $ b = [ 2, 2, 1 ] $：

* $ b_1 = \max(a_1, a_2) = \max(2, 2) = 2; $
* $ b_2 = \max(a_2, a_3) = \max(2, 1) = 2; $
* $ b_3 = \max(a_3, a_4) = \max(1, 1) = 1. $

对于第三组测试数据，数组 $ b $ 中的所有元素均为 $ 0 $，因为 $ b $ 中的每个元素均为 $ a $ 中两个相邻元素的最大值，所以数组 $ a $ 中的每个元素均为 $ 0 $。

对于第四组测试数据，我们可以从 $ a = [ 0, 0, 3, 4, 3, 3 ] $ 推出 $ b = [ 0, 3, 4, 3, 3 ] $：

* $ b_1 = \max(a_1, a_2) = \max(0, 0) = 0; $
* $ b_2 = \max(a_2, a_3) = \max(0, 3) = 3; $
* $ b_3 = \max(a_3, a_4) = \max(3, 4) = 4; $
* $ b_4 = \max(a_4, a_5) = \max(4, 3) = 4; $
* $ b_5 = \max(a_5, a_6) = \max(3, 3) = 3. $

## 样例 #1

### 输入

```
11
5
3 4 4 5
4
2 2 1
5
0 0 0 0
6
0 3 4 4 3
2
10
4
3 3 3
5
4 2 5 5
4
3 3 3
4
2 1 0
3
4 4
6
8 1 3 5 10```

### 输出

```
3 0 4 0 5
2 2 1 1
0 0 0 0 0
0 0 3 4 3 3
10 10
3 3 3 1
4 2 2 5 5
3 3 3 3
2 1 0 0
2 4 4
8 1 1 3 5 10```

# AI分析结果

### 题目内容
# 恢复数组

## 题目描述
Kristina 有一个包含 $n$ 个**非负整数**的数组 $a$。
她构造了一个长度为 $n - 1$ 的新数组 $b$，使得 $b_i = \max(a_i, a_{i + 1}) \text{ } (1 \le i \le n - 1)$。
例如，假设 Kristina 有一个长度为 $5$ 的数组 $a = [ 3, 0, 4, 0, 5 ]$，则她将以以下方式构造数组 $b$：
1. $b_1 = \max(a_1, a_2) = \max(3, 0) = 3; $
2. $b_2 = \max(a_2, a_3) = \max(0, 4) = 4; $
3. $b_3 = \max(a_3, a_4) = \max(4, 0) = 4; $
4. $b_4 = \max(a_4, a_5) = \max(0, 5) = 5. $
所以，她得到了一个长度为 $4$ 的数组 $b = [ 3, 4, 4, 5 ]$。
现在，你只知道数组 $b$。你需要找出**任意一个**可能的数组 $a$。

对于第二组测试数据，我们可以从 $a = [ 2, 2, 1, 1 ]$ 推出 $b = [ 2, 2, 1 ]$：
* $b_1 = \max(a_1, a_2) = \max(2, 2) = 2; $
* $b_2 = \max(a_2, a_3) = \max(2, 1) = 2; $
* $b_3 = \max(a_3, a_4) = \max(1, 1) = 1. $

对于第三组测试数据，数组 $b$ 中的所有元素均为 $0$，因为 $b$ 中的每个元素均为 $a$ 中两个相邻元素的最大值，所以数组 $a$ 中的每个元素均为 $0$。

对于第四组测试数据，我们可以从 $a = [ 0, 0, 3, 4, 3, 3 ]$ 推出 $b = [ 0, 3, 4, 3, 3 ]$：
* $b_1 = \max(a_1, a_2) = \max(0, 0) = 0; $
* $b_2 = \max(a_2, a_3) = \max(0, 3) = 3; $
* $b_3 = \max(a_3, a_4) = \max(3, 4) = 4; $
* $b_4 = \max(a_4, a_5) = \max(4, 3) = 4; $
* $b_5 = \max(a_5, a_6) = \max(3, 3) = 3. $

## 样例 #1
### 输入
```
11
5
3 4 4 5
4
2 2 1
5
0 0 0 0
6
0 3 4 4 3
2
10
4
3 3 3
5
4 2 5 5
4
3 3 3
4
2 1 0
3
4 4
6
8 1 3 5 10
```
### 输出
```
3 0 4 0 5
2 2 1 1
0 0 0 0 0
0 0 3 4 3 3
10 10
3 3 3 1
4 2 2 5 5
3 3 3 3
2 1 0 0
2 4 4
8 1 1 3 5 10
```
### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于 $b_i = \max(a_i, a_{i + 1})$ 这个条件来反向构造数组 $a$。大多数题解发现了 $a_i$ 与 $b_i$、$b_{i - 1}$ 的大小关系，即 $a_i \leq \min(b_i, b_{i - 1})$，并以此为依据进行数组 $a$ 的构造。不同之处主要在于边界处理和代码实现方式。

### 所选的题解
- **作者：MarsTraveller (5星)**
    - **关键亮点**：思路清晰，通过对条件的分析直接得出 $a_i = \min(b_i, b_{i - 1})$ 的构造方式，并通过对 $b$ 数组边界赋值巧妙处理了 $a$ 数组开头和结尾的情况，代码简洁明了。
    - **重点代码核心思想**：先读入数据，对 $b$ 数组边界赋值，然后通过遍历根据 $a_i = \min(b_i, b_{i - 1})$ 计算并输出 $a$ 数组。
    - **核心代码片段**：
```cpp
#include <iostream>
#define big long long
using namespace std;
big t,n,b[200005],a[200005];
int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(big i = 1;i < n;i++)//注意b数组长度。
        {
            cin >> b[i];
        }
        b[0] = b[1];
        b[n] = b[n-1];//为了防止a数组开头和结尾出错，即a数组开头结尾与b数组相等。
        for(big i = 1;i <= n;i++)
        {
            a[i] = min(b[i],b[i-1]);
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
```
- **作者：Coffee_zzz (4星)**
    - **关键亮点**：从后往前构造数组 $a$，根据 $b_{i - 1}$ 与 $b_i$ 的大小关系确定 $a_i$ 的值，思路独特，代码实现也较为简洁。
    - **重点代码核心思想**：读入数据后，先确定 $a_n = b_{n - 1}$，然后从后往前遍历，根据 $b_{i - 1}$ 与 $b_i$ 的大小关系确定 $a_i$ 的值，最后输出 $a$ 数组。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>

using namespace std;
namespace IO{
    //...
}
using IO::read;
const int N=2e5+5;
int a[N],b[N];
void solve(){
    int n;
    n=read();
    for(int i=1;i<n;i++) b[i]=read();
    a[n]=b[n-1];
    b[0]=1e9;
    for(int i=n-1;i>=1;i--){
        if(b[i-1]<b[i]) a[i]=b[i-1];
        else a[i]=b[i];
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    cout<<endl;
}
signed main(){
    int t;
    t=read();
    for(int temp=0;temp<t;temp++) solve();
    return 0;
}
```
- **作者：hycqwq (4星)**
    - **关键亮点**：通过图示清晰展示思路，根据 $a$ 数组元素对 $b$ 数组元素的影响，给出分情况的构造公式，代码实现借助 `vector` 较为直观。
    - **重点代码核心思想**：读入数据后，根据构造公式分别确定 $a$ 数组开头、中间和结尾元素的值，存储在 `vector` 中并输出。
    - **核心代码片段**：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if

int t, n, b[200005];
vector<int> a;

int main()
{
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cin >> n;
        for (int j = 1; j < n; j++)
            cin >> b[j];
        a.clear();
        a.push_back(b[1]);
        for (int j = 1; j < n - 1; j++)
            a.push_back(min(b[j], b[j + 1]));
        a.push_back(b[n - 1]);
        for (auto i : a)
            cout << i << " ";
        cout << endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
通过分析 $a_i$ 与 $b_i$、$b_{i - 1}$ 的关系，利用 $a_i \leq \min(b_i, b_{i - 1})$ 这一特性进行数组 $a$ 的构造。在处理边界情况时，可以采用对 $b$ 数组边界赋值（如 MarsTraveller 的方法）或者直接根据边界特性单独处理（如 hycqwq 的方法）。

### 拓展
同类型题通常围绕数组元素间的特定关系进行构造，类似算法套路是通过分析已知条件得出元素间的大小或等式关系，进而构造出满足要求的数组。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合构造，从给定数字中选取若干个数满足一定条件。
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：通过对迷宫规则的分析进行构造与搜索。
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：根据函数关系构造函数值，考察对条件的分析与构造能力。

### 个人心得
无。 

---
处理用时：63.81秒