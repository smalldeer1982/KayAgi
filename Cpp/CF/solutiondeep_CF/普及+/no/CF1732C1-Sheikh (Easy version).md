# 题目信息

# Sheikh (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ q = 1 $ .

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

The cost of a subsegment of the array $ [l, r] $ , $ 1 \leq l \leq r \leq n $ , is the value $ f(l, r) = \operatorname{sum}(l, r) - \operatorname{xor}(l, r) $ , where $ \operatorname{sum}(l, r) = a_l + a_{l+1} + \ldots + a_r $ , and $ \operatorname{xor}(l, r) = a_l \oplus a_{l+1} \oplus \ldots \oplus a_r $ ( $ \oplus $ stands for [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

You will have $ q = 1 $ query. Each query is given by a pair of numbers $ L_i $ , $ R_i $ , where $ 1 \leq L_i \leq R_i \leq n $ . You need to find the subsegment $ [l, r] $ , $ L_i \leq l \leq r \leq R_i $ , with maximum value $ f(l, r) $ . If there are several answers, then among them you need to find a subsegment with the minimum length, that is, the minimum value of $ r - l + 1 $ .

## 说明/提示

In the first test case, $ f(1, 1) = 0 - 0 = 0 $ .

In the second test case, $ f(1, 1) = 5 - 5 = 0 $ , $ f(2, 2) = 10 - 10 = 0 $ . Note that $ f(1, 2) = (10 + 5) - (10 \oplus 5) = 0 $ , but we need to find a subsegment with the minimum length among the maximum values of $ f(l, r) $ . So, only segments $ [1, 1] $ and $ [2, 2] $ are the correct answers.

In the fourth test case, $ f(2, 3) = (12 + 8) - (12 \oplus 8) = 16 $ .

There are two correct answers in the fifth test case, since $ f(2, 3) = f(3, 4) $ and their lengths are equal.

## 样例 #1

### 输入

```
6
1 1
0
1 1
2 1
5 10
1 2
3 1
0 2 4
1 3
4 1
0 12 8 3
1 4
5 1
21 32 32 32 10
1 5
7 1
0 1 0 1 0 1 0
1 7```

### 输出

```
1 1
1 1
1 1
2 3
2 3
2 4```

# AI分析结果

### 题目内容（中文重写）
# Sheikh（简单版本）

## 题目描述
这是该问题的简单版本。唯一的区别在于在这个版本中 $q = 1$。

给定一个整数数组 $a_1, a_2, \ldots, a_n$。

数组子段 $[l, r]$（$1 \leq l \leq r \leq n$）的代价是 $f(l, r) = \operatorname{sum}(l, r) - \operatorname{xor}(l, r)$，其中 $\operatorname{sum}(l, r) = a_l + a_{l + 1} + \ldots + a_r$，$\operatorname{xor}(l, r) = a_l \oplus a_{l + 1} \oplus \ldots \oplus a_r$（$\oplus$ 表示[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)）。

你将有 $q = 1$ 次询问。每次询问由一对数字 $L_i$，$R_i$ 给出，其中 $1 \leq L_i \leq R_i \leq n$。你需要找到子段 $[l, r]$（$L_i \leq l \leq r \leq R_i$），使得 $f(l, r)$ 的值最大。如果有多个答案，那么在这些答案中你需要找到长度最小的子段，即 $r - l + 1$ 的最小值。

## 说明/提示
在第一个测试用例中，$f(1, 1) = 0 - 0 = 0$。

在第二个测试用例中，$f(1, 1) = 5 - 5 = 0$，$f(2, 2) = 10 - 10 = 0$。注意，$f(1, 2) = (10 + 5) - (10 \oplus 5) = 0$，但我们需要在 $f(l, r)$ 的最大值中找到长度最小的子段。所以，只有子段 $[1, 1]$ 和 $[2, 2]$ 是正确答案。

在第四个测试用例中，$f(2, 3) = (12 + 8) - (12 \oplus 8) = 16$。

在第五个测试用例中有两个正确答案，因为 $f(2, 3) = f(3, 4)$ 且它们的长度相等。

## 样例 #1
### 输入
```
6
1 1
0
1 1
2 1
5 10
1 2
3 1
0 2 4
1 3
4 1
0 12 8 3
1 4
5 1
21 32 32 32 10
1 5
7 1
0 1 0 1 0 1 0
1 7
```
### 输出
```
1 1
1 1
1 1
2 3
2 3
2 4
```

### 算法分类
二分

### 综合分析与结论
这些题解主要围绕如何高效地找到满足条件的子段 $[l, r]$ 展开。核心思路是利用 $f(l, r)$ 的单调性，通过预处理前缀和与前缀异或来快速计算 $f(l, r)$ 的值，再结合二分查找来缩小搜索范围，从而在满足 $f(l, r)$ 最大的前提下，找到长度最小的子段。

不同题解的差异主要体现在代码实现细节和对特殊情况（如数组中存在 $0$）的处理方式上。部分题解还提供了更复杂情况下（如 $q=n$）的思路和优化方法。

### 所选题解
- **作者：c202201（5星）**
  - **关键亮点**：思路清晰，详细分析了 $f$ 值的单调性，并给出了简单版本和困难版本的不同解法。代码实现规范，对边界条件和特殊情况处理得当。
  - **个人心得**：无
- **作者：MoyunAllgorithm（4星）**
  - **关键亮点**：对 $f(l, r)$ 的单调性证明详细，二分查找的思路和实现过程清晰，还指出了考场代码的错误，有助于理解和避免常见问题。
  - **个人心得**：考场代码存在一处错误，二分时候选的答案区间写错，将 `Func(lb,mid)` 改为 `Func(i,mid)` 即可通过本题。
- **作者：kernel_panic（4星）**
  - **关键亮点**：思路简洁明了，直接指出最大价值必然是整个区间的价值，通过枚举左端点和二分右端点来最小化区间长度，代码实现简洁高效。
  - **个人心得**：无

### 重点代码
#### 作者：c202201
```cpp
il int calc(int l,int r) {return sum[r]-sum[l-1]-(xr[r]^xr[l-1]);}
il void work(){
    scanf("%lld%*lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",a+i),sum[i]=sum[i-1]+a[i],xr[i]=(xr[i-1]^a[i]);
    scanf("%*lld%*lld"),ans=calc(1,n),ansl=l=1,ansr=r=n;
    int mn=inf;
    for (int i=l;i<=r;++i){
        int ll=i,rr=r,pos=r;
        while(ll<=rr){
            int mid=(ll+rr)>>1;
            if(calc(i,mid)<ans) ll=mid+1;
            else rr=mid-1,pos=mid;
        }
        if(calc(i,pos)<ans) ++pos;
        if(pos==r+1) continue;
        if(mn>pos-i+1) mn=pos-i+1,ansl=i,ansr=pos;
    }
    printf("%lld %lld\n",ansl,ansr);
}
```
**核心实现思想**：先预处理前缀和 `sum` 和前缀异或 `xr`，然后枚举左端点 $i$，对于每个左端点，通过二分查找找到满足 $f(i, r)$ 最大且长度最小的右端点 $r$。

#### 作者：MoyunAllgorithm
```cpp
long long Func(int l,int r)
{
    return psum[r]-psum[l-1]-(pxor[r]^pxor[l-1]);
}
signed main()
{
    T=Read();
    while(T--)
    {
        N=Read(),Q=Read();
        for(int i=1;i<=N;i++) a[i]=Read();
        for(int i=1;i<=N;i++)
        {
            psum[i]=psum[i-1]+a[i];
            pxor[i]=pxor[i-1]^a[i];
        }
        int l=Read(),r=Read();
        long long goal=Func(l,r);
        int ansl=l,ansr=r;
        for(int i=l;i<=r;i++)
        {
            int lb=i,rb=r;
            int pos=0;
            while(lb<=rb)
            {
                int mid=(lb+rb)/2;
                if(Func(i,mid)!=goal) lb=mid+1;
                else 
                {
                    rb=mid-1;
                    pos=mid;
                }
            }
            if(pos==0) continue;
            if(ansr-ansl+1>pos-i+1) ansr=pos,ansl=i;
        }
        printf("%lld %lld\n",ansl,ansr);
    }
    return 0;
}
```
**核心实现思想**：同样先预处理前缀和 `psum` 和前缀异或 `pxor`，计算出目标值 `goal`，然后枚举左端点 $i$，二分查找满足 $f(i, r)$ 等于 `goal` 且长度最小的右端点 $r$。

#### 作者：kernel_panic
```cpp
bool check(int l, int r, i64 ans) { return (ss[r] - ss[l - 1]) - (sx[r] ^ sx[l - 1]) == ans; }
int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> q;
        for (int i = 1; i <= n; i++) std::cin >> a[i];
        for (int i = 1; i <= n; i++) ss[i] = ss[i - 1] + a[i], sx[i] = sx[i - 1] ^ a[i];
        std::cin >> L >> R;
        i64 ans = (ss[R] - ss[L - 1]) - (sx[R] ^ sx[L - 1]);
        int cl = L, cr = R;
        for (int i = L; i <= R; i++) {
            int l = i, r = R, res = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (check(i, mid, ans)) r = mid - 1, res = mid;
                else l = mid + 1;
            }
            if (res == 0) continue;
            if (cr - cl + 1 > res - i + 1) cl = i, cr = res;
        }
        std::cout << cl << " " << cr << "\n";
    }
    return 0;
}
```
**核心实现思想**：预处理前缀和 `ss` 和前缀异或 `sx`，计算出整个区间的价值 `ans`，枚举左端点 $i$，二分查找满足价值等于 `ans` 且长度最小的右端点 $r$。

### 关键思路或技巧
- **单调性分析**：通过数学推导证明 $f(l, r)$ 具有单调性，即当左端点固定时，右端点向右移动，$f(l, r)$ 单调不减；当右端点固定时，左端点向左移动，$f(l, r)$ 单调不减。利用这一性质可以使用二分查找来优化搜索过程。
- **前缀和与前缀异或**：预处理前缀和与前缀异或数组，能够在 $O(1)$ 时间内计算出任意子段的和与异或和，从而快速计算 $f(l, r)$ 的值。

### 可拓展之处
同类型题目可能会改变询问次数、数组元素范围或增加其他限制条件。类似的算法套路可以应用于其他涉及区间和、区间异或以及单调性的问题，如区间最大/最小和、区间最大/最小异或等。在处理这些问题时，同样可以考虑使用前缀和、前缀异或以及二分查找等方法来优化算法复杂度。

### 推荐洛谷题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察区间最大和问题，与本题中计算区间和有相似之处。
2. [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及区间最值问题，可通过单调队列等方法解决，与本题的区间处理思路有一定关联。
3. [P3817 小A的糖果](https://www.luogu.com.cn/problem/P3817)：需要对区间进行操作和计算，可运用前缀和等技巧来优化算法。

---
处理用时：78.54秒