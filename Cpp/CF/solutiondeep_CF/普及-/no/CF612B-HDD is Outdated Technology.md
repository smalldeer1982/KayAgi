# 题目信息

# HDD is Outdated Technology

## 题目描述

HDD hard drives group data by sectors. All files are split to fragments and each of them are written in some sector of hard drive. Note the fragments can be written in sectors in arbitrary order.

One of the problems of HDD hard drives is the following: the magnetic head should move from one sector to another to read some file.

Find the time need to read file split to $ n $ fragments. The $ i $ -th sector contains the $ f_{i} $ -th fragment of the file ( $ 1\le f_{i}\le n $ ). Note different sectors contains the different fragments. At the start the magnetic head is in the position that contains the first fragment. The file are reading in the following manner: at first the first fragment is read, then the magnetic head moves to the sector that contains the second fragment, then the second fragment is read and so on until the $ n $ -th fragment is read. The fragments are read in the order from the first to the $ n $ -th.

It takes $ |a-b| $ time units to move the magnetic head from the sector $ a $ to the sector $ b $ . Reading a fragment takes no time.

## 说明/提示

In the second example the head moves in the following way:

- 1->2 means movement from the sector 1 to the sector 5, i.e. it takes 4 time units
- 2->3 means movement from the sector 5 to the sector 2, i.e. it takes 3 time units
- 3->4 means movement from the sector 2 to the sector 4, i.e. it takes 2 time units
- 4->5 means movement from the sector 4 to the sector 3, i.e. it takes 1 time units

So the answer to the second example is $ 4+3+2+1=10 $ .

## 样例 #1

### 输入

```
3
3 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 3 5 4 2
```

### 输出

```
10
```

# AI分析结果

### 题目中文重写
# HDD 是过时的技术

## 题目描述
HDD 硬盘按扇区对数据进行分组。所有文件都被分割成碎片，每个碎片都被写入硬盘的某个扇区。注意，这些碎片可以以任意顺序写入扇区。

HDD 硬盘的问题之一如下：磁头需要从一个扇区移动到另一个扇区才能读取某个文件。

找出读取被分割成 $n$ 个碎片的文件所需的时间。第 $i$ 个扇区包含文件的第 $f_{i}$ 个碎片（$1\leq f_{i}\leq n$）。注意，不同的扇区包含不同的碎片。开始时，磁头位于包含第一个碎片的位置。文件的读取方式如下：首先读取第一个碎片，然后磁头移动到包含第二个碎片的扇区，接着读取第二个碎片，依此类推，直到读取完第 $n$ 个碎片。碎片按从第一个到第 $n$ 个的顺序读取。

磁头从扇区 $a$ 移动到扇区 $b$ 需要 $|a - b|$ 个时间单位。读取一个碎片不需要时间。

## 说明/提示
在第二个示例中，磁头的移动方式如下：
- 1 -> 2 表示从扇区 1 移动到扇区 5，即需要 4 个时间单位
- 2 -> 3 表示从扇区 5 移动到扇区 2，即需要 3 个时间单位
- 3 -> 4 表示从扇区 2 移动到扇区 4，即需要 2 个时间单位
- 4 -> 5 表示从扇区 4 移动到扇区 3，即需要 1 个时间单位

所以第二个示例的答案是 $4 + 3 + 2 + 1 = 10$。

## 样例 #1
### 输入
```
3
3 1 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
5
1 3 5 4 2
```
### 输出
```
10
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟磁头从一个碎片所在扇区移动到下一个碎片所在扇区的过程，通过计算相邻碎片所在扇区位置的差值的绝对值并累加来得到总时间。主要的算法要点是用数组记录每个碎片所在的扇区位置，然后遍历数组计算相邻位置的距离和。解决的难点在于理解输入数据的含义（第 $i$ 个扇区包含第 $f_{i}$ 个碎片）以及注意结果可能超出 `int` 范围，需要使用 `long long` 类型。

### 所选题解
- **zhanghzqwq（4星）**
    - **关键亮点**：思路清晰，代码简洁，明确指出答案需要开 `long long`，时间复杂度为 $O(n)$。
    - **个人心得**：提到“十年OI一场空，不开longlong见祖宗”，强调了使用 `long long` 的重要性。
- **翼德天尊（4星）**
    - **关键亮点**：对题目进行了详细分析，包括输入数据的处理和答案范围的计算，使用了快读优化输入。
    - **个人心得**：通过计算最坏情况下的答案范围，得出需要使用 `long long` 的结论。
- **封禁用户（4星）**
    - **关键亮点**：不仅给出了常规模拟的解法，还通过分析样例推导出数学公式，给出了更简洁的解法。
    - **个人心得**：通过观察样例发现规律，推导出等差数列求和公式来解决问题。

### 重点代码
#### zhanghzqwq 的代码
```cpp
#include<cmath>
#include<iostream>
using namespace std;
int a[200005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[x]=i; // 记录 x 的位置
    }
    long long ans=0; // 一定要开 long long
    for(int i=2;i<=n;i++){ // 从 2 开始循环
        ans+=abs(a[i]-a[i-1]);
    }
    cout<<ans<<endl; // 输出
    return 0; // 华丽的结束
}
```
**核心实现思想**：用数组 `a` 记录每个碎片所在的扇区位置，然后遍历数组，计算相邻碎片所在扇区位置的差值的绝对值并累加到 `ans` 中。

#### 翼德天尊的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,s[N];
long long ans;
inline int read(){ // 快读
    int w=0,f=1;
    char c=getchar();
    while (c>'9'||c<'0'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        w=(w<<3)+(w<<1)+(c^48);
        c=getchar();
    }
    return w*f;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)
        s[read()]=i;
    for (int i=2;i<=n;i++)
        ans+=abs(s[i]-s[i-1]);
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：使用快读优化输入，用数组 `s` 记录每个碎片所在的扇区位置，然后遍历数组，计算相邻碎片所在扇区位置的差值的绝对值并累加到 `ans` 中。

#### 封禁用户的代码
```cpp
// 模拟解法
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
ll a[200001];
int main()
{
    ios::sync_with_stdio(0);
    ll n,ans=0;
    ll zhi;
    cin>>n;
    for(ll i=1;i<=n;i++)
    {
        cin>>zhi;
        a[zhi]=i;
    }
    for(ll i=1;i<n;i++)
    {
        ans+=abs(a[i+1]-a[i]);
    }
    cout<<ans;
    return 0;
}

// 数学公式解法
#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    cout<<(n*(n-1))/2;
    return 0;
}
```
**核心实现思想**：模拟解法与其他题解类似，用数组记录位置并计算相邻位置的距离和；数学公式解法通过观察样例发现规律，推导出等差数列求和公式 $\frac{n(n - 1)}{2}$ 来直接计算结果。

### 最优关键思路或技巧
- 使用数组记录每个碎片所在的扇区位置，方便后续计算相邻碎片的距离。
- 注意结果可能超出 `int` 范围，使用 `long long` 类型来避免溢出。
- 可以通过观察样例和问题的特点，尝试推导出数学公式来简化计算。

### 可拓展之处
同类型题可能会改变移动规则或增加其他条件，例如每个碎片的读取时间不为 0，或者磁头的移动有额外的限制等。类似的算法套路包括模拟实际操作过程，通过数组记录关键信息，然后根据规则进行计算。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：模拟种树和砍树的过程。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：模拟铺地毯的过程，计算某个点最终被哪块地毯覆盖。
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)：模拟字符串的展开规则，对输入的字符串进行处理。

### 个人心得总结
- 很多题解都强调了使用 `long long` 的重要性，在处理可能出现大数的问题时，要注意数据类型的选择，避免溢出。
- 可以通过观察样例和问题的特点，尝试寻找规律，推导出数学公式来简化计算，提高解题效率。

---
处理用时：47.61秒