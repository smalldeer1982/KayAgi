# 题目信息

# Yaroslav and Sequence

## 题目描述

现有 $2n-1$ 个整数，每次操作可以使其中的 $n$ 个数 $\times (-1)$。



现在请问进行任意次操作后，这些整数的最大和是多少？



---

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le100,1\le|x|\le1000$

## 样例 #1

### 输入

```
2
50 50 50
```

### 输出

```
150
```

## 样例 #2

### 输入

```
2
-1 -100 -1
```

### 输出

```
100
```

# AI分析结果

### 题目内容
# Yaroslav和序列

## 题目描述
现有 $2n - 1$ 个整数，每次操作可以使其中的 $n$ 个数乘以 $(-1)$ 。

现在请问进行任意次操作后，这些整数的最大和是多少？

## 说明/提示
对于 $100\%$ 的数据，$1 \leq n \leq 100$，$1 \leq |x| \leq 1000$

## 样例 #1
### 输入
```
2
50 50 50
```
### 输出
```
150
```

## 样例 #2
### 输入
```
2
-1 -100 -1
```
### 输出
```
100
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路均为贪心策略结合分类讨论。要点在于分析不同情况下（$n$ 的奇偶性以及负数个数的奇偶性）如何通过操作使最终和最大。难点在于证明各种情况下能否将所有负数变为正数，以及理解在不能全部变正时如何保证剩下的负数绝对值最小。

大部分题解思路清晰，通过分类讨论得出：当 $n$ 为奇数时，无论负数个数奇偶，都能将所有负数变为正数；当 $n$ 为偶数时，若负数个数为偶数也能将所有负数变为正数，若负数个数为奇数则会剩下一个负数，此时应使这个负数绝对值最小。代码实现上，基本都是在输入时统计所有数的绝对值和、负数个数以及最小绝对值，然后根据上述分类讨论得出结果。

### 所选的题解
- **作者：fuxuantong123 (4星)**
    - **关键亮点**：思路阐述清晰，先提出贪心方向，再对各种情况详细分析，逻辑连贯。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[110];
int main(){
    int n;
    int mi=2147483647;
    int cnt=0;
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<2*n;i++){
        scanf("%d",&a[i]);
        int x=abs(a[i]);
        mi=min(mi,x);
        ans+=x;
        if(a[i]<0){
            cnt++;
        }
    }
    if(cnt%2==0){
        printf("%d",ans);
        return 0;
    }
    if(n%2!=0){
        printf("%d",ans);
        return 0;
    }
    printf("%d",ans-mi*2);
    return 0;
}
```
    - **核心思想**：输入时统计所有数绝对值之和 `ans`、负数个数 `cnt` 以及最小绝对值 `mi`，根据 `cnt` 和 `n` 的奇偶性输出结果。
- **作者：maomao233 (4星)**
    - **关键亮点**：通过具体例子辅助理解分类讨论情况，使思路更易读懂。
    - **个人心得**：遇到此类题目，草稿纸是万能的。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define wtl(x) wt(x),putchar('\n')
#define kg putchar(' ')
#define hh putchar('\n')
signed main()
{
    int n;
    rd(n);
    int ans=0,mn=1010,cnt=0;
    for(int i=1;i<=2*n-1;i++)
    {
        int x;
        rd(x);
        ans+=abs(x);
        mn=min(mn,abs(x));
        cnt+=(x<=-1);
    }
    if((n&1)||(!(n&1)&&!(cnt&1)))
    {
        wtl(ans);
    }
    else
    {
        wtl(ans-mn-mn);
    }
    return 0;
}
```
    - **核心思想**：与上一题解类似，统计相关数据后，根据 `n` 和负数个数 `cnt` 的奇偶性输出结果。
- **作者：Spir1t (4星)**
    - **关键亮点**：先阐述关键观察点，从原理层面说明结果的推导依据，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' or ch < '0') {
        if (ch == '-')f = -1;
        ch = getchar();
    }
    while (ch >= '0' and ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int Ma=INT_MAX;
const int Mi=INT_MIN;
int n;
int a[205];
signed main() {
    n=read();
    int ans=0;  // 所有数的绝对值之和
    int num=0;    // 负数的个数
    int mi=Ma;  // 最小绝对值
    for (int i = 0; i < 2*n - 1; ++i) {
        a[i]=read();
        ans += abs(a[i]);
        if (a[i] < 0) {
            num++;
        }
        mi = min(mi, abs(a[i]));
    }
    if (n % 2  or (n % 2 == 0 and num % 2 == 0)) {
        printf("%d qwq\n",ans);
    } else {
        printf("%d\n",ans-mi*2);
    }
    return 0;
}
```
    - **核心思想**：输入时统计所有数绝对值和 `ans`、负数个数 `num` 和最小绝对值 `mi`，按 `n` 和 `num` 的奇偶性输出结果。

### 最优关键思路或技巧
通过分析操作特性，利用贪心思想，根据 $n$ 和负数个数的奇偶性分类讨论，确定如何操作使和最大。在实现上，通过在输入时统计关键数据（绝对值和、负数个数、最小绝对值）简化后续计算。

### 拓展思路
此类题目属于贪心策略结合奇偶性分析的类型。相似套路是对操作规则进行深入分析，找出不同条件下的最优策略。例如在一些涉及对序列元素进行特定操作以获取最值的题目中，可通过分析操作对元素正负性、大小关系的影响，结合奇偶性等特性，利用贪心策略求解。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P1094 [NOIP2007 普及组] 纪念品分组](https://www.luogu.com.cn/problem/P1094)

---
处理用时：62.13秒