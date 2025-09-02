# 题目信息

# 「Cfz Round 1」Elevator

## 题目背景

电梯是一个可以让人充分思考的空间。

## 题目描述

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $p$ 是满足条件的，设 $p$ 的长度为 $m$，当且仅当：

- $p_1=1$；  
- 对于所有的 $1\le i<m$，都有 $|p_i-p_{i+1}|=1$；  
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1 \le i < j \le m$ 且 $p_i=a_k$，$p_j=b_k$。

你需要输出所有满足条件的序列 $p$ 中，$p$ 的长度的最小值。

## 说明/提示

#### 【样例解释 #1】

序列 $p$ 的长度的最小值为 $7$，此时的序列 $p$ 为 $\{1,2,3,2,3,4,5\}$。

#### 【数据范围】

对于所有数据，$1 \le n \le 5\times10^5$，$1 \le a_i,b_i \le 10^9$，保证 $a_i \neq b_i$。

**本题采用捆绑测试。**

|子任务编号|分值|$n \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1$|$9$|$1$|无|
|$2$|$9$|$5\times10^5$|保证 $a_i < b_i$|
|$3$|$21$|$5\times10^5$|数据随机生成|
|$4$|$27$|$2000$|无|
|$5$|$34$|$5\times10^5$|无|

## 样例 #1

### 输入

```
2
3 2
2 5```

### 输出

```
7```

## 样例 #2

### 输入

```
4
4 7
10 8
9 11
4 2```

### 输出

```
18```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何构建满足条件的序列 $p$ 并求出其最小长度展开。多数题解将 $(a_i, b_i)$ 看作区间，区分上升区间（$a_i < b_i$）和下降区间（$a_i > b_i$），先处理上升区间，重点解决下降区间的插入问题。不同题解在处理下降区间时采用了不同策略，如排序、合并区间、动态规划等。

### 所选题解
- **作者：Komomo（5星）**
    - **关键亮点**：思路清晰，详细分析了下降区间的插入代价和优化方法，通过排序、去重、合并相交区间等操作简化问题，代码实现简洁易懂。
    - **核心代码**：
```cpp
int n, L, ans, up, lo = 2e9;
struct Node { int l, r; } p[maxn], r[maxn];
bool cmp(Node a, Node b) { return a.r < b.r || a.r == b.r && a.l > b.l; }
signed main() {
    n = read(); 
    for (int i = 1; i <= n; i ++) {
        int l = read(), r = read(); up = max({up, l, r});
        if (l > r) lo = min(lo, r), p[++ L] = Node {l, r};
    }
    if (lo == 2e9) return cout << up, 0;
    ans = up + (up - lo), sort(p + 1, p + L + 1, cmp);
    int tmp = L; r[L = 1] = p[1]; 
    for (int i = 2; i <= tmp; i ++) {
        if (!(r[L].r <= p[i].r && p[i].l <= r[L].l)) {
            if (r[L].l >= p[i].r && p[i].r >= r[L].r) r[L].l = p[i].l;
            else r[++ L] = p[i];
        }
    }
    int del = 0, sum = 0; r[L + 1].r = up;
    for (int i = 1; i <= L; i ++) { 
        sum += 2 * (r[i].l - r[i].r);
        del = min((lo - r[i + 1].r) + sum, del);
    }
    cout << ans + del << endl;
    return 0;
}
```
    - **核心实现思想**：先找出所有下降区间，按右端点排序，去除包含区间和合并相交区间，然后枚举每个前缀，计算插入下降区间的代价，取最小值更新答案。

- **作者：佬头（4星）**
    - **关键亮点**：思路直观，通过构造上升序列，再将下降区间插入其中，详细分析了下降区间插入的三种情况，代码实现简洁。
    - **核心代码**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500005;
int n, cnt, maxx, minn, ans;
pair <int, int> s[N];
int read(){...}
void write(int x){...}
int main(){
    n = read();
    for(int i = 1; i <= n; ++ i){
        s[++ cnt].first = read(), s[cnt].second = read();
        if(s[cnt].first > maxx) maxx = s[cnt].first;
        if(s[cnt].second > maxx) maxx = s[cnt].second;
        if(s[cnt].first < s[cnt].second) cnt --;
    }
    minn = maxx;
    sort(s + 1, s + 1 + cnt);
    for(int i = cnt; i >= 1; -- i)
        if(s[i].first!= s[i - 1].first && minn > s[i].second){
            ans += (min(minn, s[i].first) - s[i].second) << 1;
            minn = s[i].second;
            if(ans > maxx - minn) ans = maxx - minn;
        }
    write(maxx + ans);
    return 0;
}
```
    - **核心实现思想**：先构造上升序列，解决 $a_k < b_k$ 的情况，再将 $a_k > b_k$ 的区间按 $a$ 降序排列，选择 $b$ 最小的情况插入，计算插入代价，取最小值更新答案。

- **作者：One_JuRuo（4星）**
    - **关键亮点**：思路清晰，先分析出两种满足 $a_i > b_i$ 的方式，通过排序和枚举，考虑区间重叠情况进行优化，代码实现简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long a,b;}spe[500005];
inline bool cmp(node a,node b){return (a.b!=b.b)?a.b<b.b:a.a<b.a;}
long long n,a1,b1,cnt,maxn,ans,sum,lasa;
int main()
{
    scanf("%lld",&n);
    for(long long i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a1,&b1);
        if(a1>b1) spe[++cnt].a=a1,spe[cnt].b=b1;
        maxn=max(maxn,max(a1,b1));
    }
    ans=0x3f3f3f3f3f3f3f3f;
    sort(spe+1,spe+cnt+1,cmp);
    for(long long i=1;i<=cnt;++i)
    {
        ans=min(ans,sum+maxn-spe[i].b);
        sum+=2*(max(0ll,spe[i].a-max(lasa,spe[i].b))),lasa=max(lasa,spe[i].a);
    }
    printf("%lld",min(sum,ans)+maxn);
    return 0;
}
```
    - **核心实现思想**：先找出所有 $a_i > b_i$ 的区间，按 $b$ 排序，枚举 $i$，$i$ 以前的用先降后升的方式，$i$ 以后的用到最大值再降的方式，考虑区间重叠情况更新答案。

### 最优关键思路或技巧
- **区间处理**：将 $(a_i, b_i)$ 看作区间，区分上升区间和下降区间，先处理上升区间，重点解决下降区间的插入问题。
- **排序与合并**：对下降区间按右端点或左端点排序，去除包含区间和合并相交区间，简化问题。
- **枚举与贪心**：枚举下降区间的前缀或后缀，通过贪心策略选择最优插入方式。

### 可拓展之处
同类型题或类似算法套路：区间覆盖问题、区间合并问题、动态规划优化问题等。可以通过排序、贪心、动态规划等方法解决。

### 推荐题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得
- **One_JuRuo**：最初的代码 WA 是因为没有考虑到区间重叠的情况，如 $1,5$ 和 $3,7$ 两组都选择先降后升的方式时，增加的答案应该是 $2\times(7 - 1)$ 而非 $2\times(5 - 1) + 2\times(7 - 3)$。通过记录前面所有的 $a_i$ 的最大值 $lasa$，处理区间重叠问题，最终 AC。总结：在处理区间问题时，要仔细考虑区间之间的关系，避免遗漏特殊情况。 

---
处理用时：47.85秒