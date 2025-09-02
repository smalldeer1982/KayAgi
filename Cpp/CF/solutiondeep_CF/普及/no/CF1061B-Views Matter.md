# 题目信息

# Views Matter

## 题目描述

You came to the exhibition and one exhibit has drawn your attention. It consists of $ n $ stacks of blocks, where the $ i $ -th stack consists of $ a_i $ blocks resting on the surface.

The height of the exhibit is equal to $ m $ . Consequently, the number of blocks in each stack is less than or equal to $ m $ .

There is a camera on the ceiling that sees the top view of the blocks and a camera on the right wall that sees the side view of the blocks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061B/f0bac26a304f5339f8800747dc3cc95aa0eba485.png)Find the maximum number of blocks you can remove such that the views for both the cameras would not change.

Note, that while originally all blocks are stacked on the floor, it is not required for them to stay connected to the floor after some blocks are removed. There is no gravity in the whole exhibition, so no block would fall down, even if the block underneath is removed. It is not allowed to move blocks by hand either.

## 说明/提示

The following pictures illustrate the first example and its possible solution.

Blue cells indicate removed blocks. There are $ 10 $ blue cells, so the answer is $ 10 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061B/5c39371a94179ca28ceb7e2172bc3ac014dca01f.png)

## 样例 #1

### 输入

```
5 6
3 3 3 3 3
```

### 输出

```
10```

## 样例 #2

### 输入

```
3 5
1 2 4
```

### 输出

```
3```

## 样例 #3

### 输入

```
5 5
2 3 1 4 4
```

### 输出

```
9```

## 样例 #4

### 输入

```
1 1000
548
```

### 输出

```
0```

## 样例 #5

### 输入

```
3 3
3 1 1
```

### 输出

```
1```

# AI分析结果

### 题目内容重写
#### 题目描述
你来到一个展览会，其中一个展品引起了你的注意。它由 $n$ 堆方块组成，第 $i$ 堆由 $a_i$ 个方块堆叠而成。展品的高度为 $m$，因此每堆方块的数目不超过 $m$。

天花板上的摄像头可以看到方块的俯视图，右侧墙上的摄像头可以看到方块的侧视图。你需要找到在不改变这两个视图的情况下，最多可以移除多少个方块。

注意，虽然最初所有方块都堆叠在地面上，但在移除一些方块后，方块不需要保持与地面的连接。整个展览中没有重力，因此即使下方的方块被移除，上方的方块也不会掉落。不允许手动移动方块。

#### 说明/提示
以下图片展示了第一个样例及其可能的解决方案。

蓝色方块表示被移除的方块。共有 $10$ 个蓝色方块，因此答案为 $10$。

#### 样例 #1
##### 输入
```
5 6
3 3 3 3 3
```
##### 输出
```
10
```

#### 样例 #2
##### 输入
```
3 5
1 2 4
```
##### 输出
```
3
```

#### 样例 #3
##### 输入
```
5 5
2 3 1 4 4
```
##### 输出
```
9
```

#### 样例 #4
##### 输入
```
1 1000
548
```
##### 输出
```
0
```

#### 样例 #5
##### 输入
```
3 3
3 1 1
```
##### 输出
```
1
```

### 算法分类
贪心

### 题解分析与结论
本题的核心在于通过贪心策略，最大化移除方块的数量，同时保持俯视图和侧视图不变。各题解的思路主要集中在如何通过排序和贪心策略来计算需要保留的方块数量，从而得到可以移除的最大方块数。

### 精选题解
#### 题解1：作者：きりと (4星)
##### 关键亮点
- 通过排序和贪心策略，计算每列需要保留的方块数量。
- 使用指针 `cnt` 来维护当前需要保留的方块数量，确保每行至少有一个方块。
- 代码实现清晰，逻辑严谨。

##### 核心代码
```cpp
sort(a+1,a+n+1,cmp);
int ans=0,cnt=a[1];
forr(i,1,n-1)
{
    if(cnt>a[i+1])
    {
        ans+=a[i+1]+a[i]-cnt;
        cnt=a[i+1];
    }
    else
    {
        ans+=a[i]-1;
        cnt=max(cnt-1,1LL);
    }
}
cout<<ans+a[n]-cnt<<endl;
```

#### 题解2：作者：封禁用户 (4星)
##### 关键亮点
- 通过贪心策略，优先保留右上角的方块，确保每行和每列至少有一个方块。
- 使用排序和贪心策略，计算需要保留的方块数量。
- 代码简洁，逻辑清晰。

##### 核心代码
```cpp
sort(a , a + n);
for(int i = 0 ; i < n ; i++)
{
    if(a[i] > h)
    {
        h++;
    }
}
need = a[n - 1] + n - h;
cout << cnt - need;
```

#### 题解3：作者：一扶苏一 (4星)
##### 关键亮点
- 通过排序和贪心策略，优先选择未被选择的组进行填充，节省方块数量。
- 使用扫描和贪心策略，计算需要保留的方块数量。
- 代码实现详细，逻辑严谨。

##### 核心代码
```cpp
std::sort(MU + 1, MU + 1 + n);
int pre = 0;
for (rg int i = n; i; --i) {
    ++pre;
    pre -= MU[i] - MU[i - 1];
    ans -= MU[i] - MU[i - 1];
    pre = std::max(0, pre);
}
qw(ans - pre, '\n', true);
```

### 最优关键思路
- **排序**：将方块数量从大到小排序，便于后续贪心策略的实施。
- **贪心策略**：通过维护一个指针或计数器，确保每行和每列至少有一个方块被保留，从而最大化移除的方块数量。
- **细节处理**：在处理最后一列时，需要单独处理，确保所有方块都被正确计算。

### 可拓展之处
- 类似的问题可以通过贪心策略和排序来解决，例如在保持某些视图不变的情况下，最大化或最小化某些操作的数量。
- 可以扩展到三维空间中的类似问题，通过保持多个视图不变，计算最大移除量。

### 推荐题目
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得
- **调试经历**：在处理最后一列时，容易出现边界条件错误，需要特别注意。
- **踩坑教训**：贪心策略的选择和实现细节对结果影响很大，需要仔细验证。
- **顿悟感想**：通过排序和贪心策略，可以简化复杂问题的处理逻辑，提高解题效率。

---
处理用时：38.04秒