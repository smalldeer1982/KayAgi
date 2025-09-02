# 题目信息

# Array Stabilization (GCD version)

## 题目描述

You are given an array of positive integers $ a = [a_0, a_1, \dots, a_{n - 1}] $ ( $ n \ge 2 $ ).

In one step, the array $ a $ is replaced with another array of length $ n $ , in which each element is the [greatest common divisor (GCD)](http://tiny.cc/tuy9uz) of two neighboring elements (the element itself and its right neighbor; consider that the right neighbor of the $ (n - 1) $ -th element is the $ 0 $ -th element).

Formally speaking, a new array $ b = [b_0, b_1, \dots, b_{n - 1}] $ is being built from array $ a = [a_0, a_1, \dots, a_{n - 1}] $ such that $ b_i $ $ = \gcd(a_i, a_{(i + 1) \mod n}) $ , where $ \gcd(x, y) $ is the greatest common divisor of $ x $ and $ y $ , and $ x \mod y $ is the remainder of $ x $ dividing by $ y $ . In one step the array $ b $ is built and then the array $ a $ is replaced with $ b $ (that is, the assignment $ a $ := $ b $ is taking place).

For example, if $ a = [16, 24, 10, 5] $ then $ b = [\gcd(16, 24) $ , $ \gcd(24, 10) $ , $ \gcd(10, 5) $ , $ \gcd(5, 16)] $ $ = [8, 2, 5, 1] $ . Thus, after one step the array $ a = [16, 24, 10, 5] $ will be equal to $ [8, 2, 5, 1] $ .

For a given array $ a $ , find the minimum number of steps after which all values $ a_i $ become equal (that is, $ a_0 = a_1 = \dots = a_{n - 1} $ ). If the original array $ a $ consists of identical elements then consider the number of steps is equal to $ 0 $ .

## 样例 #1

### 输入

```
5
4
16 24 10 5
4
42 42 42 42
3
4 6 4
5
1 2 3 4 5
6
9 9 27 9 9 63```

### 输出

```
3
0
2
1
1```

# AI分析结果

### 题目翻译
# 数组稳定化（最大公约数版本）

## 题目描述
给定一个正整数数组 $a = [a_0, a_1, \dots, a_{n - 1}]$（$n \ge 2$）。

在一步操作中，数组 $a$ 会被另一个长度为 $n$ 的数组替换，新数组中的每个元素是原数组中相邻两个元素的[最大公约数（GCD）](http://tiny.cc/tuy9uz)（即元素本身与其右侧相邻元素的最大公约数；认为第 $(n - 1)$ 个元素的右侧相邻元素是第 $0$ 个元素）。

形式上，从数组 $a = [a_0, a_1, \dots, a_{n - 1}]$ 构建一个新数组 $b = [b_0, b_1, \dots, b_{n - 1}]$，使得 $b_i = \gcd(a_i, a_{(i + 1) \mod n})$，其中 $\gcd(x, y)$ 是 $x$ 和 $y$ 的最大公约数，$x \mod y$ 是 $x$ 除以 $y$ 的余数。在一步操作中，先构建数组 $b$，然后将数组 $a$ 替换为 $b$（即执行赋值操作 $a := b$）。

例如，如果 $a = [16, 24, 10, 5]$，那么 $b = [\gcd(16, 24), \gcd(24, 10), \gcd(10, 5), \gcd(5, 16)] = [8, 2, 5, 1]$。因此，经过一步操作后，数组 $a = [16, 24, 10, 5]$ 将变为 $[8, 2, 5, 1]$。

对于给定的数组 $a$，求经过最少多少步操作后，数组 $a$ 中的所有值 $a_i$ 都相等（即 $a_0 = a_1 = \dots = a_{n - 1}$）。如果原始数组 $a$ 中的所有元素都相同，则认为操作步数为 $0$。

## 样例 #1
### 输入
```
5
4
16 24 10 5
4
42 42 42 42
3
4 6 4
5
1 2 3 4 5
6
9 9 27 9 9 63
```

### 输出
```
3
0
2
1
1
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是先发现操作次数的单调性，利用二分查找最小的操作次数，使得数组中所有元素相等。在处理环的问题上，普遍采用断环成链的方法，将数组复制一份接在原数组后面。对于区间 $\gcd$ 的计算，大部分题解使用 ST 表来优化查询，也有部分题解使用线段树或 zkw 线段树。

不同题解的主要区别在于实现细节和使用的数据结构。部分题解先将所有数除以数组的 $\gcd$，将问题转化为求最长的 $\gcd$ 不为 $1$ 的连续子串；部分题解则直接二分答案并检查是否满足条件。

### 所选题解
- **作者：Him_shu (赞：13)  4星**
    - **关键亮点**：思路清晰，详细解释了每个步骤的原理，包括最后的相等值为所有初始项的 $\gcd$，用双倍链解决环问题，用 ST 表快速计算区间 $\gcd$，并使用二分答案进行求解。代码实现规范，注释详细。
- **作者：MatrixCascade (赞：12)  4星**
    - **关键亮点**：先将所有数除以 $\gcd(a_1,a_2,\dots,a_n)$，将问题转化为求最长的 $\gcd$ 不为 $1$ 的连续子串，使用线段树 + 双指针维护，思路简洁，代码实现高效。
- **作者：HoshizoraZ (赞：10)  4星**
    - **关键亮点**：详细证明了 $\gcd(a,b,c)=\gcd(\gcd(a,b),c)$ 这个结论，然后通过断环成链、二分查找和 ST 表优化，逐步解决问题，思路严谨，代码可读性高。

### 重点代码
#### Him_shu 的代码核心片段
```cpp
// ST表初始化
void in(){
  for(int i=1;i<=n*2;i++){
    st[i][0]=a[i];
  }
  for(int j=1;(1<<j)<=n*2;j++){
    for(int i=1;i+(1<<j)-1<=n*2;i++){
      st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
  }
}
// ST表查询
int out(int a,int b){
  int k=log(b-a+1)/log(2.0);
  return __gcd(st[a][k],st[b-(1<<k)+1][k]);
}
// 检查答案是否可行
bool isok(int x){
  for(int i=1;i<=n;i++){
    if(out(i,i+x)!=zh){
      return 0;
    }
  }
  return 1;
}
```
**核心实现思想**：`in` 函数用于初始化 ST 表，`out` 函数用于查询区间 $\gcd$，`isok` 函数用于检查在操作 $x$ 次后，数组中所有元素是否相等。

#### MatrixCascade 的代码核心片段
```cpp
// 线段树建树
void build(int p,int l,int r) {
    if(l==r) {
        ans[p]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    pushup(p);
}
// 线段树查询
int qry(int p,int l,int r,int nl,int nr) {
    if(l>=nl&&nr>=r) return ans[p];
    int mid=(l+r)>>1;
    int nw=0;
    if(nl<=mid) nw=__gcd(nw,qry(ls(p),l,mid,nl,nr));
    if(nr>mid) nw=__gcd(nw,qry(rs(p),mid+1,r,nl,nr));
    return nw;
}
```
**核心实现思想**：`build` 函数用于构建线段树，`qry` 函数用于查询线段树中指定区间的 $\gcd$。

#### HoshizoraZ 的代码核心片段
```cpp
// ST表查询
int query(int i, int j) {
    int k = log2(j - i + 1);
    return gcd(st[i][k], st[j - (1 << k) + 1][k]);
}
```
**核心实现思想**：`query` 函数用于查询 ST 表中指定区间的 $\gcd$。

### 关键思路或技巧
- **断环成链**：将环形数组复制一份接在原数组后面，将环的问题转化为链的问题，方便处理。
- **ST 表优化**：利用 ST 表可以在 $O(1)$ 时间内查询区间 $\gcd$，提高算法效率。
- **二分答案**：由于操作次数具有单调性，使用二分查找可以快速找到最小的操作次数。

### 拓展思路
同类型题或类似算法套路：
- 涉及环形数组的问题，通常可以采用断环成链的方法。
- 对于区间查询问题，如果满足结合律和幂等性，可以使用 ST 表进行优化。
- 当问题具有单调性时，可以考虑使用二分查找来求解。

### 推荐题目
- [P2880 [USACO07JAN]Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)：区间最值查询问题，可使用 ST 表解决。
- [P3865 [模板]ST 表](https://www.luogu.com.cn/problem/P3865)：ST 表的模板题，帮助掌握 ST 表的使用。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分答案的经典题目，可加深对二分思想的理解。

### 个人心得摘录与总结
- **lgx57**：提到数组要开 2 倍空间，避免因数组开小而出现问题，提醒在处理环形数组时要注意空间的使用。
- **lateworker**：强调用 `memset` 清空数组会超时，要控制清空长度，在多组数据的情况下，要注意清空数组的方式，避免不必要的时间开销。

---
处理用时：63.36秒