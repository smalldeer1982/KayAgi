# 题目信息

# 転倒数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

数列 $ a $ をバブルソートした時、スワップが何回発生するかを出力しなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1

### 输入

```
5

3 1 5 4 2```

### 输出

```
5```

## 样例 #2

### 输入

```
6

1 2 3 4 5 6```

### 输出

```
0```

## 样例 #3

### 输入

```
7

7 6 5 4 3 2 1```

### 输出

```
21```

## 样例 #4

### 输入

```
20

19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
114```

# AI分析结果

### 题目翻译
# 逆序数

## 题目描述
[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

请输出对数列 $ a $ 进行冒泡排序时，发生交换的次数。

## 说明/提示
### 制约
- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1
### 输入
```
5
3 1 5 4 2
```
### 输出
```
5
```

## 样例 #2
### 输入
```
6
1 2 3 4 5 6
```
### 输出
```
0
```

## 样例 #3
### 输入
```
7
7 6 5 4 3 2 1
```
### 输出
```
21
```

## 样例 #4
### 输入
```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12
```
### 输出
```
114
```

### 综合分析与结论
本题的核心是求数列的逆序对个数，因为冒泡排序的交换次数就等于逆序对的数量。各位大神的题解主要采用了冒泡排序模拟、归并排序、树状数组这几种方法。

- **冒泡排序模拟**：通过两层循环遍历数组，比较并交换逆序对，统计交换次数。时间复杂度为 $O(n^2)$，在数据量较大时会超时。
- **归并排序**：在归并的过程中统计逆序对。将数组不断二分，分别对左右子数组排序，合并时统计跨越左右子数组的逆序对。时间复杂度为 $O(n\log n)$。
- **树状数组**：利用树状数组维护前缀和，统计每个数前面比它大的数的个数。对于较大的数据范围，需要进行离散化处理。时间复杂度为 $O(n\log n)$。

### 所选的题解
- **作者：Diamiko (赞：15，4星)**
  - **关键亮点**：思路清晰，详细解释了逆序对的概念和树状数组求逆序对的方法，还提到了离散化技巧。
  - **个人心得**：指出不开 `long long` 可能会出错，提醒读者注意数据范围。
- **作者：冽酒灬忄 (赞：7，4星)**
  - **关键亮点**：使用归并排序求逆序对，代码简洁明了。
- **作者：fjy666 (赞：0，4星)**
  - **关键亮点**：详细阐述了归并排序求逆序对的思路，保证了不重不漏，复杂度分析清晰。

### 重点代码
#### 树状数组求逆序对（Diamiko）
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
struct Number
{
    int order;//序号
    int value;//值
}a[100005];
int lsh[100005];//离散化后的数组
int c[100005];
int n;
int lowbit(int x)
{
    return x&-x;
}
void update(int x,int k)
{
    for(int i=x;i<=n;i+=lowbit(i))
    {
        c[i]+=k;
    }
}
int getSum(int x)
{
    int res=0;
    for(int i=x;i>0;i-=lowbit(i))
    {
        res+=c[i];
    }
    return res;
}
bool cmp(Number x,Number y)
{
    return x.value<y.value;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].value;
        a[i].order=i;//记录原序
    }
    sort(a+1,a+n+1,cmp);//快排
    for(int i=1;i<=n;i++)
    {
        lsh[a[i].order]=i;//离散化的过程
    }
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        update(lsh[i],1);
        ans+=i-getSum(lsh[i]);//减去小于的数即为大于的数即为逆序数
    }
    cout<<ans<<endl;
    return 0;
}
```
**核心思想**：先对数组进行离散化处理，将每个数映射到一个较小的范围内。然后使用树状数组维护前缀和，每次读入一个数，更新树状数组，并统计前面比它小的数的个数，进而得到逆序对的数量。

#### 归并排序求逆序对（冽酒灬忄）
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
long long n,ans=0,rank[100001],a[100001];
void guibing(long long l,long long r){
    if(l==r)
        return ;
    long long mid=(l+r)/2;
    guibing(l,mid);
    guibing(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r){
        if(a[i]<=a[j])
            rank[k++]=a[i++];
        else{
            ans=ans+mid-i+1;
            rank[k++]=a[j++];
        }
    }
    while(i<=mid){
        rank[k++]=a[i++];
    }
    while(j<=r){
        rank[k++]=a[j++];
    }
    for(int p=l;p<=r;p++)
        a[p]=rank[p];
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    guibing(1,n);
    cout<<ans<<endl;
    return 0;
}
```
**核心思想**：将数组不断二分，分别对左右子数组进行归并排序。在合并的过程中，如果右子数组的元素小于左子数组的元素，说明存在逆序对，逆序对的数量为左子数组剩余元素的个数。

#### 归并排序求逆序对（fjy666）
```cpp
#include <cstdio>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
using namespace std;
const int kN = 1005000;
int a[kN],b[kN];
ll cnt;
void mergeSort(int L,int R){
    if(L == R)return;
    int mid = L+R>>1;
    mergeSort(L,mid);
    mergeSort(mid+1,R);
    int pL = L,pR = mid + 1;
    _rep(i,L,R){
        if(pL <= mid && (pR > R || a[pR] >= a[pL]))b[i] = a[pL++];
        else b[i] = a[pR++],cnt += mid - pL + 1;
    }
    _rep(i,L,R)a[i] = b[i]; 
}
int main(){
    int n;
    while(~scanf("%d",&n)){
        _rep(i,1,n)
            scanf("%d",a+i);
        cnt = 0;
        mergeSort(1,n);
        printf("%lld\n",cnt);
    }
    return 0;
}
```
**核心思想**：同样是利用归并排序的思想，在合并左右子数组时，统计跨越左右子数组的逆序对数量，保证每个逆序对只被统计一次且不会遗漏。

### 最优关键思路或技巧
- **数据结构**：树状数组可以高效地维护前缀和，在求逆序对问题中发挥重要作用。对于数据范围较大的情况，离散化可以避免数组越界和空间浪费。
- **算法优化**：归并排序的时间复杂度为 $O(n\log n)$，比冒泡排序的 $O(n^2)$ 更优，适合处理大规模数据。

### 拓展思路
同类型题或类似算法套路：
- 求二维平面上点的逆序对问题，可以先对 $x$ 坐标排序，再用树状数组或归并排序处理 $y$ 坐标。
- 求数组中满足特定条件的逆序对，如 $a[i] > k * a[j]$ 且 $i < j$ 的逆序对，可以在归并排序或树状数组的基础上进行修改。

### 推荐洛谷题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [P2513 [HAOI2009]逆序对数列](https://www.luogu.com.cn/problem/P2513)
- [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637)

### 个人心得总结
- 多位作者提到冒泡排序模拟会超时，应使用归并排序或树状数组等更优算法。
- 注意数据范围，使用 `long long` 避免溢出。
- 对于数据范围较大的情况，需要进行离散化处理。

---
处理用时：57.40秒