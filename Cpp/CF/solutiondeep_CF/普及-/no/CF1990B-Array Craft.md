# 题目信息

# Array Craft

## 题目描述

For an array $ b $ of size $ m $ , we define:

- the maximum prefix position of $ b $ is the smallest index $ i $ that satisfies $ b_1+\ldots+b_i=\max_{j=1}^{m}(b_1+\ldots+b_j) $ ;
- the maximum suffix position of $ b $ is the largest index $ i $ that satisfies $ b_i+\ldots+b_m=\max_{j=1}^{m}(b_j+\ldots+b_m) $ .

You are given three integers $ n $ , $ x $ , and $ y $ ( $ x > y $ ). Construct an array $ a $ of size $ n $ satisfying:

- $ a_i $ is either $ 1 $ or $ -1 $ for all $ 1 \le i \le n $ ;
- the maximum prefix position of $ a $ is $ x $ ;
- the maximum suffix position of $ a $ is $ y $ .

If there are multiple arrays that meet the conditions, print any. It can be proven that such an array always exists under the given conditions.

## 说明/提示

In the second test case,

- $ i=x=4 $ is the smallest index that satisfies $ a_1+\ldots +a_i=\max_{j=1}^{n}(a_1+\ldots+a_j)=2 $ ;
- $ i=y=3 $ is the greatest index that satisfies $ a_i+\ldots +a_n=\max_{j=1}^{n}(a_j+\ldots+a_n)=2 $ .

Thus, the array $ a=[1,-1,1,1] $ is considered correct.

## 样例 #1

### 输入

```
3
2 2 1
4 4 3
6 5 1```

### 输出

```
1 1
1 -1 1 1
1 1 -1 1 1 -1```

# AI分析结果

### 题目翻译
# 数组构造

## 题目描述
对于一个长度为 $m$ 的数组 $b$，我们定义：
- $b$ 的最大前缀位置是满足 $b_1+\ldots+b_i=\max_{j=1}^{m}(b_1+\ldots+b_j)$ 的最小索引 $i$；
- $b$ 的最大后缀位置是满足 $b_i+\ldots+b_m=\max_{j=1}^{m}(b_j+\ldots+b_m)$ 的最大索引 $i$。

给定三个整数 $n$，$x$ 和 $y$（$x > y$）。构造一个长度为 $n$ 的数组 $a$，满足：
- 对于所有 $1 \le i \le n$，$a_i$ 为 $1$ 或 $-1$；
- $a$ 的最大前缀位置是 $x$；
- $a$ 的最大后缀位置是 $y$。

如果有多个数组满足条件，输出任意一个。可以证明，在给定条件下，这样的数组总是存在的。

## 说明/提示
在第二个测试用例中：
- $i = x = 4$ 是满足 $a_1+\ldots +a_i=\max_{j=1}^{n}(a_1+\ldots+a_j)=2$ 的最小索引；
- $i = y = 3$ 是满足 $a_i+\ldots +a_n=\max_{j=1}^{n}(a_j+\ldots+a_n)=2$ 的最大索引。

因此，数组 $a = [1, -1, 1, 1]$ 被认为是正确的。

## 样例 #1
### 输入
```
3
2 2 1
4 4 3
6 5 1
```
### 输出
```
1 1
1 -1 1 1
1 1 -1 1 1 -1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于构造的方法来解决问题。关键在于利用条件 $x > y$，先确定 $y$ 到 $x$ 之间的元素为 $1$，因为这样能使前缀和与后缀和在这个区间达到较大值。对于 $1$ 到 $y - 1$ 以及 $x + 1$ 到 $n$ 的部分，为了保证最大前缀位置是 $x$，最大后缀位置是 $y$，采用 $1$ 和 $-1$ 交替填充的方式，让这两部分的和的绝对值尽可能小。

各题解的区别主要在于代码实现的细节，如输出方式、变量的使用等，但整体的构造思路是一致的。

### 所选题解
- **作者：Linge_Zzzz (赞：5)，4星**
  - **关键亮点**：思路清晰，先阐述了错误的尝试（全填 $-1$），然后分析原因并给出正确的构造方法，最后对正确性进行了一定的解释，代码可读性较好。
  - **个人心得**：一开始把 $1$ 到 $y - 1$ 以及 $x + 1$ 到 $n$ 全填了 $-1$，吃了一发罚时，通过具体例子分析出问题所在，从而找到新的构造方向。

### 重点代码
```cpp
#include <iostream>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int a[N];
void solve(){
    int n,x,y;
    cin>>n>>x>>y;
    fill(a,a+1+n,0);
    for(int i=x+1;i<=n;i++)a[i]=-1;
    for(int i=1;i<y;i++)a[i]=-1;
    for(int i=1;i<=n;i++){
        if(a[i]==-1)cout<<-1<<' ';
        else cout<<1<<' ';
    }
    cout<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
    return 0;
}
```
**核心实现思想**：先将数组初始化为 $0$，然后把 $x + 1$ 到 $n$ 以及 $1$ 到 $y - 1$ 的元素标记为 $-1$，最后遍历数组，标记为 $-1$ 的输出 $-1$，其余输出 $1$。

### 可拓展之处
同类型的题目可能会改变数组元素的取值范围，或者改变最大前缀位置和最大后缀位置的定义，例如改为最大前缀和的绝对值最大的位置等。类似的算法套路是根据给定的条件，先确定一部分元素的值，再通过合理的构造方式确定其余元素的值，以满足题目要求。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)

---
处理用时：30.82秒