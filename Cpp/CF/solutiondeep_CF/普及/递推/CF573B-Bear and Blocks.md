# 题目信息

# Bear and Blocks

## 题目描述

Limak is a little bear who loves to play. Today he is playing by destroying block towers. He built $ n $ towers in a row. The $ i $ -th tower is made of $ h_{i} $ identical blocks. For clarification see picture for the first sample.

Limak will repeat the following operation till everything is destroyed.

Block is called internal if it has all four neighbors, i.e. it has each side (top, left, down and right) adjacent to other block or to the floor. Otherwise, block is boundary. In one operation Limak destroys all boundary blocks. His paws are very fast and he destroys all those blocks at the same time.

Limak is ready to start. You task is to count how many operations will it take him to destroy all towers.

## 说明/提示

The picture below shows all three operations for the first sample test. Each time boundary blocks are marked with red color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png) After first operation there are four blocks left and only one remains after second operation. This last block is destroyed in third operation.

## 样例 #1

### 输入

```
6
2 1 4 6 2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
3 3 3 1 3 3 3
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
## 熊与方块

### 题目描述
小熊利马克喜欢玩耍。今天他在玩摧毁方块塔的游戏。他在一排建了 $n$ 座塔，第 $i$ 座塔由 $h_{i}$ 个相同的方块组成。为了便于理解，请参考第一个样例的图片。

利马克会重复以下操作，直到所有东西都被摧毁。

如果一个方块的四个面（上、左、下、右）都与其他方块或地面相邻，那么这个方块被称为内部方块。否则，这个方块就是边界方块。在一次操作中，利马克会同时摧毁所有边界方块。

利马克已经准备好开始了。你的任务是计算他需要多少次操作才能摧毁所有的塔。

### 说明/提示
下图展示了第一个样例测试的所有三次操作。每次操作中，边界方块都用红色标记。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png)

第一次操作后还剩下四个方块，第二次操作后只剩下一个方块。这个最后的方块在第三次操作中被摧毁。

### 样例 #1
#### 输入
```
6
2 1 4 6 2 2
```
#### 输出
```
3
```

### 样例 #2
#### 输入
```
7
3 3 3 1 3 3 3
```
#### 输出
```
2
```

### 题解综合分析与结论
这些题解主要围绕计算摧毁所有方块塔所需的最少操作次数展开，核心在于分析每列方块消失的时间。不同题解采用了多种思路和算法，下面是详细对比：
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|梦游的小雪球|用 $V$ 数组存每列最快消失时间，考虑从左、右、顶三个方向炸的情况，取最小值，最终结果是 $V$ 数组最大值|动态规划，三次循环分别处理从左、右和顶端开始的情况|确定每列最快消失时间的计算方式|4星|
|南橙未熟k|模拟从左和从右扫描数组，取 $a[i]$ 与 $a[i + 1]+1$ 或 $a[i - 1]+1$ 中的小值，最终结果是 $a$ 数组最大值|模拟，两次循环处理左右情况|确定每次操作后方块数的变化规律|4星|
|Karry5307|分析一次、两次操作对第 $i$ 列方块高度的影响，用数学归纳法得出 $k$ 次操作后的公式，通过线段树求 $h_j - j$ 的前缀最小值和 $h_j + j$ 的后缀最小值|线段树，数学归纳法|推导 $k$ 次操作后高度的公式，以及使用线段树求最值|3星|
|Farkas_W|将方块按列考虑，用 $l$、$r$ 数组分别表示因左边、右边无方块而消失的时间，最终每列消失时间是 $\min(l_i, r_i)$ 的最大值|动态规划，两次循环分别处理左右情况|确定每列消失时间的计算方式|4星|
|Plozia|考虑 $a_i$ 降为 0 的次数，用动态规划，状态转移方程为 $f_i = \max{(f_{i - 1} + 1, a_i, f_{i + 1} + 1)}$，做两遍 dp 解决|动态规划，两次 dp 处理左右数据|确定状态转移方程和处理左右数据的方法|3星|
|Alarm5854|先暴力模拟，分析改变柱子高度的三种方式，用动态规划，状态转移方程为 $f_i=\min(f_{i - 1}+1, h_i, f_{i + 1}+1)$，最终结果是 $f$ 数组最大值|动态规划，先模拟后优化|从暴力模拟过渡到动态规划的优化|3星|
|DennyQi|根据题目性质得到操作公式，迭代推出 $k$ 次操作后的公式，用 ST 表维护 $h_i + i$ 的最小值，最终结果是所有 $k_{min}$ 的最大值|ST 表，公式迭代|推导 $k$ 次操作后的公式和使用 ST 表维护最值|3星|
|frankchenfu|设每个“塔”高度为 $h_i$，第一次操作后高度为 $\min(h_i - 1, h_{i - 1}, h_{i + 1})$，用线段树维护 $\min_{j = 0}^{i}\{h_{i - j}+j\}$ 和 $\min_{j = 0}^{i}\{h_{i + j}+j\}$，最终结果是所有最小时间的最大值|线段树，递推公式|推导递推公式和使用线段树维护区间最值|3星|
|轻绘|二分金字塔大小，判断图中是否存在该金字塔，最终结果是（底边块数 + 1）/ 2|二分答案，模拟判断|确定二分的对象和判断金字塔是否存在的方法|3星|
|ykuouzf|确定最后删去的方块在最下面一行，用动态规划，转移方程考虑左、右和向上延伸三种情况取 $\min$，最终结果是 $f$ 数组最大值加 1|动态规划，考虑三种转移情况|确定答案分布和转移方程|3星|

### 所选题解
- **梦游的小雪球（4星）**
    - 关键亮点：思路清晰，代码简洁，通过简单的动态规划解决问题。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,h[100002],v[100002];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    v[1]=1;
    for(int i=2;i<n;i++)
        v[i]=min(v[i-1]+1,h[i]);
    v[n]=1;
    for(int i=n-1;i>=0;i--)
        v[i]=min(v[i],v[i+1]+1);
    for(int i=1;i<=n;i++)
        s=max(s,v[i]);
    printf("%d\n",s);
    return 0;
}
```
    - 核心实现思想：先初始化 $v[1]$ 和 $v[n]$，然后从左到右遍历，计算从左边和顶端开始的最快消失时间，再从右到左遍历，更新从右边开始的最快消失时间，最后取 $v$ 数组的最大值作为结果。

- **南橙未熟k（4星）**
    - 关键亮点：通过简单的模拟和取最小值的方式解决问题，代码易懂。
    - 核心代码：
```pascal
var     i,j,n,m,k,t,x:longint;
        a:array[0..1000000]of longint;
function min(x,y:longint):longint;
begin
        if x>y then exit(y);
        exit(x);
end;
function max(x,y:longint):longint;
begin
        if x>y then exit(x);
        exit(y);
end;
begin
        readln(n);
        for i:=1 to n do
                read(a[i]);
        for i:=1 to n do
                a[i]:=min(a[i],a[i-1]+1);
        for i:=n downto 1 do
                a[i]:=min(a[i],a[i+1]+1);
        for i:=1 to n do
                x:=max(x,a[i]);
        writeln(x);
end.
```
    - 核心实现思想：先读入数组 $a$，然后从左到右遍历，取 $a[i]$ 与 $a[i - 1]+1$ 中的小值，再从右到左遍历，取 $a[i]$ 与 $a[i + 1]+1$ 中的小值，最后取 $a$ 数组的最大值作为结果。

- **Farkas_W（4星）**
    - 关键亮点：将方块按列考虑，思路直观，代码简洁高效。
    - 核心代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define re register int
#define int long long
#define il inline
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5;
int n,ans,l[N],r[N];
signed main()
{
  n=read();
  for(re i=1;i<=n;i++)l[i]=r[i]=read();
  for(re i=1;i<=n;i++)l[i]=min(l[i],l[i-1]+1);
  for(re i=n;i>=1;i--)r[i]=min(r[i],r[i+1]+1);
  for(re i=1;i<=n;i++){ans=max(ans,min(r[i],l[i]));}
  print(ans);
  return 0;
}
```
    - 核心实现思想：先将 $l$ 和 $r$ 数组初始化为每列的高度，然后从左到右遍历，计算 $l$ 数组，再从右到左遍历，计算 $r$ 数组，最后取 $\min(l_i, r_i)$ 的最大值作为结果。

### 最优关键思路或技巧
- **动态规划思想**：多数题解采用动态规划，通过状态转移方程计算每列方块消失的时间，避免了暴力模拟的高复杂度。
- **多方向考虑**：考虑从左、右、顶三个方向炸方块的情况，取最小值确定每列最快消失时间。
- **虚拟柱子**：部分题解在左右两边加上高度为 0 的虚拟柱子，方便处理边界情况。

### 可拓展之处
同类型题可能会改变方块的排列方式或操作规则，但核心思路依然是分析每个元素的状态变化和消失时间。类似算法套路包括动态规划、二分答案、线段树等，可用于解决各种涉及状态转移和最值计算的问题。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划思想。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：也是动态规划问题，与本题的状态转移思路有相似之处。
- [P2258 子矩阵](https://www.luogu.com.cn/problem/P2258)：涉及矩阵的操作和最值计算，可使用动态规划或二分答案等方法解决。

### 个人心得摘录与总结
- **Karry5307**：“这神仙题差点把我给卡死。” 总结：遇到难题时会有较大挑战，但通过深入分析和思考可以找到解决方法。
- **Farkas_W**：“表示完全看不懂其他 $dalao$ 的线段树， $st$ 表和曼哈顿最小生成树做法，于是自己写一发题解帮助其他像我一样的蒟蒻。” 总结：当看不懂复杂解法时，可以尝试自己思考，找到适合自己的简单解法，同时也可以帮助其他有类似困惑的人。
- **ykuouzf**：“学校里模拟赛考了这题，虽说最后成绩不怎么样，不过抢到了这题的首A（$20min$）~~勉强没有爆零~~” 总结：在考试中即使整体成绩不理想，也可以通过快速解决某道题获得成就感，同时也说明平时的练习和思考对考试有帮助。 

---
处理用时：84.71秒