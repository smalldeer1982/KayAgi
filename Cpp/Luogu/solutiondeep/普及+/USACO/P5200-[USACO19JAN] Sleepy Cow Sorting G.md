# 题目信息

# [USACO19JAN] Sleepy Cow Sorting G

## 题目背景

USACO 19年一月月赛金组第二题

## 题目描述

Farmer John正在尝试将他的 $N$ 头奶牛（$1\le N\le 10^5$），方便起见编号为 $1\ldots N$，在她们前往牧草地吃早餐之前排好顺序。

当前，这些奶牛以 $p_1,p_2,p_3,\ldots,p_N$ 的顺序排成一行，Farmer John站在奶牛 $p_1$ 前面。他想要重新排列这些奶牛，使得她们的顺序变为 $1,2,3,\ldots,N$，奶牛 $1$ 在 Farmer John 旁边。

今天奶牛们有些困倦，所以任何时刻都只有直接面向 Farmer John 的奶牛会注意听 Farmer John 的指令。每一次他可以命令这头奶牛沿着队伍向后移动 $k$ 步，$k$ 可以是 $1$ 到 $N−1$ 之间的任意数。她经过的 $k$ 头奶牛会向前移动，腾出空间使得她能够插入到队伍中这些奶牛之后的位置。

例如，假设 $N=4$，奶牛们开始时是这样的顺序：

```plain
 FJ: 4 3 2 1
```

唯一注意 FJ 指令的奶牛是奶牛 $4$。当他命令她向队伍后移动 $2$ 步之后，队伍的顺序会变成：

```plain
 FJ: 3 2 4 1 
```

现在唯一注意 FJ 指令的奶牛是奶牛 $3$，所以第二次他可以给奶牛 $3$ 下命令，如此进行直到奶牛们排好了顺序。

Farmer John 急欲完成排序，这样他就可以回到他的农舍里享用他自己的早餐了。请帮助他求出一个操作序列，使得能够用最少的操作次数将奶牛们排好顺序。

## 样例 #1

### 输入

```
4
1 2 4 3```

### 输出

```
3
2 2 3```

# AI分析结果

### 综合分析与结论
这些题解的核心思路基本一致，都是将序列划分为待排序和已排序两部分，找出从后往前的最长上升后缀作为已排序部分，其余为待排序部分，待排序部分元素的数量即为最小移动次数。对于每头牛移动的距离，是未排序牛的数量减 1 加上已排序牛中小于队头牛的数量。为了高效计算小于某个数的元素数量，多数题解采用树状数组，其单点修改和区间查询复杂度为 $O(log n)$，使整体复杂度降为 $O(n log n)$。部分题解还提到用平衡树（如 pbds）来解决，但相对树状数组更复杂。

### 所选题解
- **作者：HRLYB（5星）**
    - **关键亮点**：思路清晰，详细阐述了分段维护思想，将复杂问题分解为已解决和未解决两部分，方便思考和代码实现。代码注释完善，可读性高。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define maxn 100010
using namespace std;
int n,a[maxn],tree[maxn],ans[maxn];
int lowbit(int x){return x&(-x);}
void add(int x,int k){
    for(int i=x;i<=n;i+=lowbit(i))tree[i]+=k;
}
int query(int x){
    int ret=0;
    for(int i=x;i;i-=lowbit(i))ret+=tree[i];
    return ret;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    int k=0,sum=n;
    while(a[n-k]>a[n-k-1]){
        add(a[n-k],1);
        sum--;
        k++;
    }
    add(a[n-k],1),sum--;
    for(int i=1;i<=sum;i++){
        add(a[i],1);
        ans[i]=sum-i+query(a[i]-1);
    }
    printf("%d\n",sum);
    for(int i=1;i<=sum;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}
```
    - **核心思想**：先找出最长上升后缀，用树状数组标记已排序元素。对于待排序元素，计算其移动距离，即未排序序列长度减 1 加上该元素在已排序序列中前面元素的数量。

- **作者：SymphonyOfEuler（4星）**
    - **关键亮点**：对树状数组进行了简要介绍，方便读者理解。思路阐述清晰，代码注释详细。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int n;
int c[MAXN], a[MAXN];
inline int lowbit(int x) { return x & -x; }
void update(int x) {
    while (x <= n) {
        c[x]++;
        x += lowbit(x);
    }
}
int sum(int x) {
    int res = 0;
    while (x > 0) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    int k = n - 1;
    while (k > 0 && a[k] < a[k + 1]) {
        k--;
    }
    printf("%d\n", k);
    for (int i = k + 1; i <= n; ++i) {
        update(a[i]);
    }
    for (int i = 1; i <= k; ++i) {
        printf("%d ", k - i + sum(a[i]));
        update(a[i]);
    }
    printf("\n");
    return 0;
}
```
    - **核心思想**：先找到末尾非逆序元素的长度，确定最小移动次数。用树状数组标记已排序元素，对于待排序元素，计算其移动距离并输出。

- **作者：CYJian（4星）**
    - **关键亮点**：思路简洁明了，强调维护最长上升后缀，代码短小精悍。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define reg register
#define ge getchar()
#define Re read()
#define FI "sleepy.in"
#define FO "sleepy.out"
#define MAXN 100000
inline int read() {
    reg int x = 0, ch;
    while(!isdigit(ch = ge)) ;
    while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = ge;
    return x;
}
int a[MAXN + 1];
int T[MAXN + 1];
inline void Add(reg int p) { while(p <= MAXN) T[p]++, p += p & -p; }
inline int Ask(reg int p) { reg int x = 0; while(p) x += T[p], p ^= p & -p; return x; }
int main() {
    reg int n = Re;
    for(reg int i = 1; i <= n; i++) a[i] = Re;
    reg int la = n + 1;
    for(reg int i = n; i >= 1; i--) {
        if(a[i] > la) {
            printf("%d\n", i);
            for(reg int j = 1; j <= i; j++) {
                printf("%d%c", i - j + Ask(a[j]), " \n"[j == i]);
                Add(a[j]);
            }
            break;
        }
        la = a[i], Add(a[i]);
    }
}
```
    - **核心思想**：从后往前找最长上升后缀，确定最小移动次数。对于待排序元素，计算其移动距离，即当前位置到后缀前端的距离加上后缀中小于该元素的数量。

### 最优关键思路或技巧
- **分段维护思想**：将序列分为待排序和已排序两部分，简化问题。
- **树状数组**：用于高效计算前缀和和单点修改，降低时间复杂度。

### 可拓展之处
同类型题如涉及序列排序且有操作次数限制或求最优操作方案的题目，可采用类似的分段思想和数据结构优化。例如一些序列插入排序问题，可通过树状数组维护元素的位置信息。

### 推荐题目
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组单点修改、区间查询模板题。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可使用树状数组统计逆序对数量。
- [P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)：与本题分段思想有一定关联，可用于练习序列处理。

### 个人心得摘录与总结
- **作者：lxxwxxxxx**：刚开始从前往后枚举分界点导致错误，后来发现应从后往前枚举，保证元素从后往前递减，强调了思考方向的重要性。
- **作者：ValiZpg**：觉得用平衡树（替罪羊树）实现较复杂，于是用 pbds 凑合，体现了在实现算法时可根据实际情况选择合适的数据结构。 

---
处理用时：45.16秒