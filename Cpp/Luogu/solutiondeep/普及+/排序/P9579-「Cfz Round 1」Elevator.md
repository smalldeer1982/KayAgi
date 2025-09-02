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
这些题解主要围绕如何构造满足条件的最短序列展开，核心在于处理 \(a_i > b_i\) 的情况。多数题解采用贪心策略，少数使用动态规划。主要思路包括将 \(a_i, b_i\) 看作区间，找出最大值 \(mx\) 构造基础上升序列满足 \(a_i < b_i\) 的情况，再通过不同方式处理 \(a_i > b_i\) 的区间，如合并相交区间、按特定规则排序后插入等。

### 所选的题解
1. **作者：Komomo（5星）**
    - **关键亮点**：思路清晰，详细分析了插入下降区间的代价及优化方法，先去掉下降区间中互相包含者，合并相交区间，再按 \(b_i\) 从小到大排序取前缀最小值，代码简洁明了，逻辑严谨。
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
    for (int i = 2; i <= tmp; i ++)
        if (!(r[L].r <= p[i].r && p[i].l <= r[L].l)) { 
            if (r[L].l >= p[i].r && p[i].r >= r[L].r) r[L].l = p[i].l; 
            else r[++ L] = p[i]; 
        }
    int del = 0, sum = 0; 
    r[L + 1].r = up; 
    for (int i = 1; i <= L; i ++) { 
        sum += 2 * (r[i].l - r[i].r);
        del = min((lo - r[i + 1].r) + sum, del);
    }
    cout << ans + del << endl;
    return 0;
}
```
    - **核心实现思想**：首先读取数据，将 \(a > b\) 的区间记录下来。若不存在这样的区间，直接输出 \(a, b\) 中的最大值。否则，对这些区间按右端点排序，处理包含和相交情况，合并区间。接着计算将区间插入到上升序列前的代价前缀和以及新答案与原答案的差值，最终输出最优答案。

2. **作者：佬头（4星）**
    - **关键亮点**：先构造上升序列解决 \(a_i < b_i\) 的情况，再对 \(a_i > b_i\) 的情况按 \(a\) 降序排列，分析三种插入方式的代价，通过比较不同插入方式的代价来更新总代价，思路易懂，代码实现较为简洁。
    - **核心代码**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500005;
int n, cnt, maxx, minn, ans;
pair <int, int> s[N];
int read(){
    int x = 0;
    char a = getchar();
    while(a < '0' || '9' < a) a = getchar();
    while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
    return x;
}
void write(int x){
    if(x > 9) write(x / 10);
    putchar(x % 10 | 48);
}
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
    - **核心实现思想**：读取数据并筛选出 \(a > b\) 的情况，记录 \(a, b\) 中的最大值 \(maxx\)。对 \(a > b\) 的区间按 \(a\) 降序排序，遍历这些区间，计算不同插入方式下的代价并更新总代价，最终输出最大值与总代价之和。

3. **作者：qzhwlzy（4星）**
    - **关键亮点**：分析出 \(p\) 中元素最大值为 \(a, b\) 中的最大值 \(mx\)，先构造到 \(mx\) 的上升序列满足 \(a_i \leq b_i\) 的区间。对于 \(a_i > b_i\) 的区间，提出合并相交区间和按区间右端点从小到大的后缀从 \(mx\) 走下来的性质，通过枚举后缀来求解，思路合理，代码有较好的可读性。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 500005
#define int long long
using namespace std;
int n,mmax,l,r,cnt=0,ccnt=0,ans=0,res; struct node{int l,r;}a[maxn],b[maxn];
bool cmpl(node aa,node bb){return aa.l<bb.l;} bool cmpr(node aa,node bb){return aa.r<bb.r;}
signed main(){
    scanf("%lld",&n); for(int i=1;i<=n;i++){
        scanf("%lld%lld",&l,&r); mmax=max(mmax,max(l,r));
        if(l>r) b[++ccnt]=(node){r,l};
    } if(ccnt==0){printf("%lld",mmax); return 0;}
    sort(b+1,b+1+ccnt,cmpl); int pos;
    for(int i=1;i<=ccnt;i=pos+1){
        pos=i; while(pos<ccnt&&b[pos+1].l<=b[i].r) pos++,b[i].r=max(b[i].r,b[pos].r);
        a[++cnt]=(node){b[i].r,b[i].l};
    } sort(a+1,a+1+cnt,cmpr);
    ans=res=2*mmax-a[1].r; a[cnt+1].r=mmax; for(int i=1;i<=cnt;i++){
        res=res-(a[i+1].r-a[i].r)+(a[i].l-a[i].r)*2;
        ans=min(ans,res);
    } printf("%lld",ans);
    return 0;
}
```
    - **核心实现思想**：读入数据，记录 \(a > b\) 的区间。若不存在则直接输出 \(mx\)。对这些区间按左端点排序，合并相交区间，再按右端点排序。初始化答案和中间变量，通过枚举后缀计算并更新最优答案。

### 最优关键思路或技巧
1. **区间合并**：对于 \(a_i > b_i\) 的区间，合并相交区间能避免重复计算，减少不必要的步数，是优化答案的关键。
2. **排序策略**：按区间的右端点（或结合左端点）排序，有助于按顺序处理区间，找到最优的插入方式，降低问题复杂度。

### 可拓展思路
此类题目属于序列构造与优化问题，相似套路是将条件转化为区间问题，利用排序、合并等操作简化问题，通过贪心或动态规划求解。类似题目通常围绕如何在满足一系列限制条件下，构造最优序列或路径。

### 相似知识点题目推荐
1. **P1080 [NOIP2012 提高组] 国王游戏**：通过排序和贪心策略解决分配问题，与本题排序后贪心选择的思路类似。
2. **P1106 删数问题**：运用贪心思想，在数字序列中删除数字以得到最小数，和本题构造最优序列思路相关。
3. **P1937 [USACO10MAR]Barn Allocation G**：涉及区间分配和排序，与本题处理区间的方式有相似之处。 

---
处理用时：66.37秒