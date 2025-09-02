# 题目信息

# Petya and Countryside

## 题目描述

Little Petya often travels to his grandmother in the countryside. The grandmother has a large garden, which can be represented as a rectangle $ 1×n $ in size, when viewed from above. This rectangle is divided into $ n $ equal square sections. The garden is very unusual as each of the square sections possesses its own fixed height and due to the newest irrigation system we can create artificial rain above each section.

Creating artificial rain is an expensive operation. That's why we limit ourselves to creating the artificial rain only above one section. At that, the water from each watered section will flow into its neighbouring sections if their height does not exceed the height of the section. That is, for example, the garden can be represented by a $ 1×5 $ rectangle, where the section heights are equal to 4, 2, 3, 3, 2. Then if we create an artificial rain over any of the sections with the height of 3, the water will flow over all the sections, except the ones with the height of 4. See the illustration of this example at the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF66B/9a7bf3e55f07a79a8c55bac4c2b87a72e9e3e5af.png)As Petya is keen on programming, he decided to find such a section that if we create artificial rain above it, the number of watered sections will be maximal. Help him.

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 1 2 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
8
1 2 1 1 1 3 3 4
```

### 输出

```
6
```

# AI分析结果

### 题目翻译
# 彼佳与乡村

## 题目描述
小彼佳经常去乡下看望他的祖母。祖母有一个大花园，从上方看，这个花园可以表示为一个 $1×n$ 的矩形。这个矩形被分成 $n$ 个相等的正方形区域。这个花园非常特别，因为每个正方形区域都有自己固定的高度，而且由于有最新的灌溉系统，我们可以在每个区域上方进行人工降雨。

进行人工降雨是一项昂贵的操作。因此，我们只限制在一个区域上方进行人工降雨。当在某一区域进行人工降雨时，如果相邻区域的高度不超过该区域的高度，水就会流向相邻区域。例如，花园可以用一个 $1×5$ 的矩形表示，其中各区域的高度分别为 4、2、3、3、2。那么，如果我们在任何一个高度为 3 的区域上方进行人工降雨，水将流向除高度为 4 的区域之外的所有区域。请参考下图中的示例说明：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF66B/9a7bf3e55f07a79a8c55bac4c2b87a72e9e3e5af.png)由于彼佳热衷于编程，他决定找到这样一个区域，如果在该区域上方进行人工降雨，被水浇灌的区域数量将达到最大。请帮助他。

## 样例 #1

### 输入
```
1
2
```

### 输出
```
1
```

## 样例 #2

### 输入
```
5
1 2 1 2 1
```

### 输出
```
3
```

## 样例 #3

### 输入
```
8
1 2 1 1 1 3 3 4
```

### 输出
```
6
```

### 算法分类
枚举

### 综合分析与结论
这些题解主要围绕枚举每个位置作为降雨点，然后向两边扩展计算能浇灌的区域数量，最后找出最大值。大部分题解采用了 $O(n^2)$ 的枚举方法，也有部分题解使用动态规划将时间复杂度优化到 $O(n)$。

### 所选的题解
- StudyingFather（5星）：思路清晰，代码简洁易懂，直接枚举每个位置，向两边扩展计算答案，是很标准的枚举解法。
- peppaking8（4星）：不仅给出了 $O(n^2)$ 的枚举思路，还提出了用动态规划优化到 $O(n)$ 的方法，并给出了优化后的代码，对不同复杂度的解法有全面的分析。
- chufuzhe（4星）：先预处理每个位置往左和往右最多能流的区域数，再打擂台找出最大值，思路独特，代码实现也比较清晰。

### 重点代码
#### StudyingFather 的代码
```cpp
for(int i=1;i<=n;i++)
{
    int l=i,r=i,ln=a[i],rn=a[i];
    while(l>1&&a[l-1]<=ln)
        ln=a[--l];
    while(r<n&&a[r+1]<=rn)
        rn=a[++r];
    ans=max(ans,r-l+1);
}
```
核心思想：枚举每个位置作为降雨点，向左右两边扩展，直到不能扩展为止，记录能浇灌的区域数量，取最大值。

#### peppaking8 的代码
```cpp
f[1]=0;
for(int i=2;i<=n;i++){
    if(a[i]>=a[i-1]) f[i]=f[i-1]+1;
    else f[i]=0;
}
g[n]=0;
for(int i=n-1;i>=1;i--){
    if(a[i]>=a[i+1]) g[i]=g[i+1]+1;
    else g[i]=0;
}
for(int i=1;i<=n;i++) ans=max(ans,f[i]+g[i]);
```
核心思想：使用动态规划，先计算每个位置左边和右边能浇灌的最远节点与其的距离，最后统计答案。

#### chufuzhe 的代码
```cpp
l[1]=0;
for(register int i=2;i<=n;i++)
    if(a[i-1]<=a[i])
        l[i]=l[i-1]+1;
r[n]=0;
for(register int i=n-1;i>=1;i--)
    if(a[i+1]<=a[i])
        r[i]=r[i+1]+1;
for(register int i=1;i<=n;i++)
    s=max(s,l[i]+r[i]+1);
```
核心思想：预处理每个位置往左和往右最多能流的区域数，最后打擂台找出最大值。

### 关键思路或技巧
- 枚举每个位置作为降雨点，向两边扩展计算能浇灌的区域数量。
- 可以使用动态规划，用空间换时间，将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
- 预处理每个位置往左和往右最多能流的区域数，减少重复计算。

### 拓展思路
同类型题可以是类似的一维或二维的水流扩展问题，或者是在某个位置进行操作，向周围扩展的问题。类似算法套路可以是枚举、动态规划等。

### 推荐题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1059 [NOIP2006 普及组] 明明的随机数
- P1067 [NOIP2009 普及组] 多项式输出

### 个人心得
- monstersqwq：第一眼以为是什么奇怪的模板题，后来又发现是能往两边流，感慨题目比较奇特。
- Mikemao666：调侃题目净整物理难题，实际关键在于求出每一个点的左、右两边不大于它自身的元素总数。
- 血色黄昏：提到小花说过 $n^2$ 的暴力基本上啥都能维护，说明对于数据范围较小的题目可以考虑暴力枚举。

---
处理用时：37.93秒