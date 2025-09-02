# 题目信息

# Read Time

## 题目描述

Mad scientist Mike does not use slow hard disks. His modification of a hard drive has not one, but $ n $ different heads that can read data in parallel.

When viewed from the side, Mike's hard drive is an endless array of tracks. The tracks of the array are numbered from left to right with integers, starting with 1. In the initial state the $ i $ -th reading head is above the track number $ h_{i} $ . For each of the reading heads, the hard drive's firmware can move the head exactly one track to the right or to the left, or leave it on the current track. During the operation each head's movement does not affect the movement of the other heads: the heads can change their relative order; there can be multiple reading heads above any of the tracks. A track is considered read if at least one head has visited this track. In particular, all of the tracks numbered $ h_{1} $ , $ h_{2} $ , $ ... $ , $ h_{n} $ have been read at the beginning of the operation.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343C/477411d635199d18d36c6b93ba130f0f6f88e682.png)Mike needs to read the data on $ m $ distinct tracks with numbers $ p_{1} $ , $ p_{2} $ , $ ... $ , $ p_{m} $ . Determine the minimum time the hard drive firmware needs to move the heads and read all the given tracks. Note that an arbitrary number of other tracks can also be read.

## 说明/提示

The first test coincides with the figure. In this case the given tracks can be read in 2 seconds in the following way:

1. during the first second move the 1-st head to the left and let it stay there;
2. move the second head to the left twice;
3. move the third head to the right twice (note that the 6-th track has already been read at the beginning).

One cannot read the tracks in 1 second as the 3-rd head is at distance 2 from the 8-th track.

## 样例 #1

### 输入

```
3 4
2 5 6
1 3 6 8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
1 2 3
1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1 2
165
142 200
```

### 输出

```
81
```

# AI分析结果

### 题目内容
# 读取时间

## 题目描述
疯狂科学家迈克不使用慢速硬盘。他对硬盘的改造使其拥有的不是一个，而是 $n$ 个不同的磁头，这些磁头可以并行读取数据。

从侧面看，迈克的硬盘是一个无限的轨道数组。数组中的轨道从左到右用整数编号，从1开始。在初始状态下，第 $i$ 个读取磁头位于轨道编号 $h_{i}$ 上。对于每个读取磁头，硬盘的固件可以将磁头精确地向左或向右移动一个轨道，或者让它停留在当前轨道上。在操作过程中，每个磁头的移动不会影响其他磁头的移动：磁头可以改变它们的相对顺序；任何一个轨道上都可以有多个读取磁头。如果至少有一个磁头访问过某个轨道，那么该轨道就被认为是已读取的。特别地，在操作开始时，编号为 $h_{1}$，$h_{2}$，$ \cdots $，$h_{n}$ 的所有轨道都已被读取。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343C/477411d635199d18d36c6b93ba130f0f6f88e682.png)迈克需要读取编号为 $p_{1}$，$p_{2}$，$ \cdots $，$p_{m}$ 的 $m$ 个不同轨道上的数据。确定硬盘固件移动磁头并读取所有给定轨道所需的最短时间。注意，也可以读取任意数量的其他轨道。

## 说明/提示
第一个测试用例与图相符。在这种情况下，给定的轨道可以在2秒内按以下方式读取：
1. 在第一秒内，将第一个磁头向左移动并保持在那里；
2. 将第二个磁头向左移动两次；
3. 将第三个磁头向右移动两次（注意，第6个轨道在开始时已经被读取）。

由于第三个磁头与第8个轨道的距离为2，所以不可能在1秒内读取这些轨道。

## 样例 #1
### 输入
```
3 4
2 5 6
1 3 6 8
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3 3
1 2 3
1 2 3
```
### 输出
```
0
```

## 样例 #3
### 输入
```
1 2
165
142 200
```
### 输出
```
81
```

### 算法分类
二分

### 综合分析与结论
这几道题解思路较为一致，均利用答案的单调性进行二分答案求解。关键在于如何在二分的 `check` 函数中判断给定时间是否能满足读取所有轨道的要求。各题解都考虑到最优情况下磁头扫过区域不重叠这一重要结论，从左到右处理每个轨道，贪心选择由最左侧指针处理最左侧未读轨道。不同之处在于处理指针移动情况时的细节和代码实现方式。

### 所选的题解
 - **作者：离散小波变换° (5星)**
    - **关键亮点**：思路清晰，详细分析指针移动的各种情况，对二分答案及 `check` 函数的实现逻辑阐述清楚，代码注释详细。
    - **核心代码片段**：
```cpp
bool chk(i64 x){
    int p=1; up(1,n,i){
        if(P[p]<=H[i]){
            if(H[i]-P[p]>x) return false;
            i64 d=H[i]-P[p];
            while(p<=m&&(P[p]-H[i]<=x-2*d||2*(P[p]-H[i])+d<=x)) ++p;
        } else {
            while(p<=m&&P[p]-H[i]<=x) ++p;
        }
        if(p>m) return true;
    }
    return false;
}
```
    - **核心实现思想**：在 `chk` 函数中，从左到右遍历指针，针对当前指针与未读轨道最左侧点的位置关系，分情况讨论指针移动方式，判断能否在时间 `x` 内覆盖所有轨道。
 - **作者：Guess00 (4星)**
    - **关键亮点**：代码简洁，利用快读快输优化输入输出，`check` 函数通过枚举每个探头，基于上一次可到达轨道来判断当前时间是否能覆盖所有轨道，时间复杂度分析准确。
    - **核心代码片段**：
```cpp
inline bool check(int t)     //本题重点:判断 
{
	int l,r,ans;
	l=r=1;
    for (i=1;i<=n;i++)
    {
        ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
        while (r<=m && ans<=t)  //枚举 
            r++,ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
        l=r;
        if (r>m)   //已经覆盖了所有轨道 
            return true;  //t满足要求 
    }
    return false;
}
```
    - **核心实现思想**：`check` 函数中，从第一个探头开始，计算当前探头在时间 `t` 内从最左到最右能覆盖的轨道范围，不断更新范围并判断是否能覆盖所有 `m` 个轨道。
 - **作者：Graph_Theory (4星)**
    - **关键亮点**：同样采用二分答案结合贪心判断，对 `check` 函数中指针移动覆盖轨道的原理阐述清晰，通过公式计算每个头在对应时间下最多可扫描轨道，逻辑明确。
    - **核心代码片段**：
```cpp
bool check(int x)
{
	int l=1,r=1,ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
		while(r<=m && ans<=x)		
		{
			r++;
			ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
		}
		l=r;
		if(r>m) return true;
	}
	return false;
}
```
    - **核心实现思想**：与 `Guess00` 的 `check` 函数类似，通过循环枚举每个探头，利用公式计算在时间 `x` 内可覆盖的轨道范围，判断是否能覆盖所有轨道。

### 最优关键思路或技巧
利用二分答案的方法，结合最优情况下磁头扫过区域不重叠的特性，贪心选择最左侧指针处理最左侧未读轨道，通过分类讨论指针与未读轨道的位置关系，高效判断给定时间是否能满足要求。

### 可拓展之处
此类题目属于在一维空间中多个移动点覆盖特定点集的问题，类似套路可应用于其他具有单调性且可通过二分搜索解决的覆盖、最值问题。例如，在一维坐标轴上多个机器人移动到特定目标点的最短时间问题等。

### 推荐洛谷题目
 - [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分答案解决跳跃距离相关问题，与本题二分思路类似。
 - [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：同样采用二分答案，判断在给定条件下能否满足需求。
 - [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：利用二分答案结合贪心策略解决道路上设置路标数量的问题。

### 个人心得
无。 

---
处理用时：66.92秒