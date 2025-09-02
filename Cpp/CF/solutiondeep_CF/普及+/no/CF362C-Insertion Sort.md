# 题目信息

# Insertion Sort

## 题目背景

Petya is a beginner programmer. He has already mastered the basics of the C++ language and moved on to learning algorithms. The first algorithm he encountered was insertion sort. Petya has already written the code that implements this algorithm and sorts the given integer zero-indexed array $ a $ of size $ n $ in the non-decreasing order.

```cpp
for (int i = 1; i < n; i = i + 1)
{
    int j = i; 
    while (j > 0 && a[j] < a[j - 1])
    {
        swap(a[j], a[j - 1]); // swap elements a[j] and a[j - 1]
        j = j - 1;
    }
}
```

Petya uses this algorithm only for sorting of arrays that are permutations of numbers from $ 0 $ to $ n-1 $ . He has already chosen the permutation he wants to sort but he first decided to swap some two of its elements. Petya wants to choose these elements in such a way that the number of times the sorting executes function swap, was minimum. Help Petya find out the number of ways in which he can make the swap and fulfill this requirement.

It is guaranteed that it's always possible to swap two elements of the input permutation in such a way that the number of swap function calls decreases.

## 题目描述

Petya is a beginner programmer. He has already mastered the basics of the C++ language and moved on to learning algorithms. The first algorithm he encountered was insertion sort. Petya has already written the code that implements this algorithm and sorts the given integer zero-indexed array $ a $ of size $ n $ in the non-decreasing order.

`for (int i = 1; i < n; i = i + 1)<br></br>{<br></br>   int j = i; <br></br>   while (j > 0 && a[j] < a[j - 1])<br></br>   {<br></br>      swap(a[j], a[j - 1]); // swap elements a[j] and a[j - 1]<br></br>      j = j - 1;<br></br>   }<br></br>}<br></br>`Petya uses this algorithm only for sorting of arrays that are permutations of numbers from $ 0 $ to $ n-1 $ . He has already chosen the permutation he wants to sort but he first decided to swap some two of its elements. Petya wants to choose these elements in such a way that the number of times the sorting executes function swap, was minimum. Help Petya find out the number of ways in which he can make the swap and fulfill this requirement.

It is guaranteed that it's always possible to swap two elements of the input permutation in such a way that the number of swap function calls decreases.

## 说明/提示

In the first sample the appropriate pairs are $ (0,3) $ and $ (0,4) $ .

In the second sample the appropriate pairs are $ (0,4) $ , $ (1,4) $ , $ (2,4) $ and $ (3,4) $ .

## 样例 #1

### 输入

```
5
4 0 3 1 2
```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
5
1 2 3 4 0
```

### 输出

```
3 4
```

# AI分析结果

### 题目内容
# 插入排序

## 题目背景
Petya是一位初学者程序员。他已经掌握了C++语言的基础知识，并开始学习算法。他遇到的第一个算法是插入排序。Petya已经编写了实现该算法的代码，用于对给定的长度为n的整数零索引数组a按非递减顺序进行排序。
```cpp
for (int i = 1; i < n; i = i + 1)
{
    int j = i; 
    while (j > 0 && a[j] < a[j - 1])
    {
        swap(a[j], a[j - 1]); // 交换元素a[j]和a[j - 1]
        j = j - 1;
    }
}
```
Petya仅使用此算法对由0到n - 1的数字组成的排列数组进行排序。他已经选择了要排序的排列，但首先决定交换其中两个元素。Petya希望以这样一种方式选择这些元素，使得排序过程中执行swap函数的次数最少。帮助Petya找出满足此要求的交换方式的数量。
保证始终可以通过交换输入排列中的两个元素，使得swap函数的调用次数减少。

## 题目描述
Petya是一位初学者程序员。他已经掌握了C++语言的基础知识，并开始学习算法。他遇到的第一个算法是插入排序。Petya已经编写了实现该算法的代码，用于对给定的长度为n的整数零索引数组a按非递减顺序进行排序。
```cpp
for (int i = 1; i < n; i = i + 1)
{
    int j = i; 
    while (j > 0 && a[j] < a[j - 1])
    {
        swap(a[j], a[j - 1]); // 交换元素a[j]和a[j - 1]
        j = j - 1;
    }
}
```
Petya仅使用此算法对由0到n - 1的数字组成的排列数组进行排序。他已经选择了要排序的排列，但首先决定交换其中两个元素。Petya希望以这样一种方式选择这些元素，使得排序过程中执行swap函数的次数最少。帮助Petya找出满足此要求的交换方式的数量。
保证始终可以通过交换输入排列中的两个元素，使得swap函数的调用次数减少。

## 说明/提示
在第一个样例中，合适的数对是(0, 3)和(0, 4)。
在第二个样例中，合适的数对是(0, 4)、(1, 4)、(2, 4)和(3, 4)。

## 样例 #1
### 输入
```
5
4 0 3 1 2
```
### 输出
```
3 2
```

## 样例 #2
### 输入
```
5
1 2 3 4 0
```
### 输出
```
3 4
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是基于冒泡排序交换次数等于逆序对个数这一性质，通过枚举交换的两个元素，计算交换后逆序对的变化来求解。主要差异在于计算逆序对变化量的方式以及预处理数组的定义和使用。
1. **思路**：多数题解先计算原序列逆序对总数，再通过预处理数组来快速计算交换两个元素后逆序对的变化量，从而找到最小逆序对数量及方案数。
2. **算法要点**：
    - 计算原序列逆序对，可使用归并排序或暴力枚举。
    - 定义并预处理数组，如`f[i][j]`表示第`i`位之前有多少个数大于`a[j]`等，通过前缀和思想递推得到。
    - 枚举交换的两个元素，根据预处理数组计算交换后的逆序对数量。
3. **解决难点**：关键在于如何`O(1)`计算交换两个元素后逆序对的变化量，通过巧妙定义和预处理数组来实现。

### 所选的题解
- **作者：lenlen (5星)**
    - **关键亮点**：思路清晰，先明确问题核心是计算交换元素后逆序对的变化，通过定义`f[i][j]`和`g[i][j]`数组，利用前缀和思想递推预处理，能`O(1)`计算交换后的逆序对数量，时间复杂度`O(n^2)`。代码实现完整，包含归并求逆序对的函数。
    - **重点代码 - 核心实现思想**：通过`cdq`函数归并求逆序对总数`sum`，利用两层循环递推预处理`f`和`g`数组，再通过两层循环枚举交换的两个元素，根据公式计算交换后的逆序对数量并更新答案。
```cpp
void cdq(int l,int r) //cdq求逆序对，也就是归并求逆序对
{
    if(l==r) return ;
    int mid=l+r>>1;
    cdq(l,mid),cdq(mid+1,r);
    int i,j,num=l-1;
    for(i=mid+1,j=l;i<=r;i++)
    {
        while(b[j]<b[i]&&j<=mid) c[++num]=b[j++];
        sum+=mid-j+1;
        c[++num]=b[i];
    }
    while(j<=mid) c[++num]=b[j++];
    for(int i=l;i<=r;i++) b[i]=c[i];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),++a[i],b[i]=a[i];
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++) f[j][i]=f[j-1][i]+(a[i]<a[j]),g[j][i]=g[j-1][i]+(a[i]>a[j]);//预处理
    cdq(1,n);
    ans=sum,cnt=1;
    for(int l=1;l<=n;l++)
    for(int r=l+1;r<=n;r++)
    {
        if(ans>sum+(f[r][l]-f[l][l])-(g[r][l]-g[l][l])-(f[r][r]-f[l][r])+(g[r][r]-g[l][r])) 
        {
            ans=sum+(f[r][l]-f[l][l])-(g[r][l]-g[l][l])-(f[r][r]-f[l][r])+(g[r][r]-g[l][r]);
            cnt=1;
        }
        else if(ans==sum+(f[r][l]-f[l][l])-(g[r][l]-g[l][l])-(f[r][r]-f[l][r])+(g[r][r]-g[l][r])) ++cnt;
    }
    printf("%d %d\n",ans,cnt);
}
```
 - **作者：李34 (4星)**
    - **关键亮点**：同样基于逆序对的思路，通过递推记录`L`和`M`数组，利用前缀和思想计算交换后的逆序对变化量，代码简洁明了，直接暴力计算逆序对和预处理数组，时间复杂度`O(n^2)`。
    - **重点代码 - 核心实现思想**：通过两层循环递推预处理`L`和`M`数组，同时计算原序列逆序对总数`ori`，再通过两层循环枚举交换元素，根据公式计算交换后的逆序对数量并更新答案。
```cpp
signed main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%d",&A[i]);++A[i];
		for (int j=1;j<=n;++j){
			L[i][j]=L[i-1][j]+(A[i]<j);
			M[i][j]=M[i-1][j]+(A[i]>j);
		}//递推求两个数组。
		ori+=M[i][A[i]];
		//计算逆序对。
	}
	int ans=ori,ansk=0;
	for (int i=1;i<=n;++i){
		for (int j=i+1;j<=n;++j){
			int p=ori-M[i-1][A[i]]-M[j-1][A[j]]-L[j-1][A[i]]+L[i][A[i]]
			         +M[i-1][A[j]]+M[j-1][A[i]]+L[j-1][A[j]]-L[i][A[j]];
			//计算：减掉原来的，加上现在的。
			if (ans>p) ans=p,ansk=1;
			else if (ans==p) ++ansk;
		}
	}
	printf("%d %d",ans,ansk);
	return 0;
}
```
 - **作者：Lagerent (4星)**
    - **关键亮点**：清晰阐述交换元素后对逆序对影响的四个方面，通过前缀和预处理`f`和`g`数组来`O(1)`计算影响，代码结构清晰，注释详细。
    - **重点代码 - 核心实现思想**：通过两层循环预处理`f`和`g`数组，同时计算原序列逆序对总数`s`，再通过两层循环枚举交换元素，根据公式计算交换后的逆序对数量并更新答案。
```cpp
int main() {
	n = rd(); 
	rep(i, 1, n) a[i] = rd();
	rep(i, 1, n) {
		rep(j, 1, n) {
			if(i < j && a[i] > a[j]) ++ s;
			f[j][i] = f[j - 1][i] + (a[j] < a[i]);
			g[j][i] = g[j - 1][i] + (a[j] > a[i]);
		}
	}
	int res = s, cnt = 0;
	rep(l, 1, n - 1) {
		rep(r, l + 1, n) {
			int t = s + (g[r][l] - g[l][l]) - (f[r][l] - f[l][l]) + (f[r][r] - f[l][r]) - (g[r][r] - g[l][r]);
			if(t < res) {
				res = t;
				cnt = 1;
			}
			else if(t == res) ++ cnt;
		}
	}
	printf("%d %d\n", res, cnt);
	return 0;
}
```

### 最优关键思路或技巧
1. **利用逆序对性质**：将冒泡排序交换次数问题转化为逆序对问题，这是解题的关键。
2. **前缀和预处理数组**：通过定义和预处理如`f[i][j]`、`g[i][j]`等数组，利用前缀和思想快速计算交换元素后逆序对的变化量，优化了枚举交换元素时的计算过程。

### 拓展
同类型题常围绕排序算法的交换次数与逆序对的关系展开，类似算法套路是先明确原问题与逆序对的联系，再通过预处理数组或数据结构优化计算交换元素后逆序对的变化。

### 洛谷题目推荐
1. **P1908 逆序对**：基础的逆序对计算问题，可巩固逆序对的计算方法。
2. **P3369 【模板】普通平衡树**：在维护数据结构的过程中涉及到逆序对相关的操作，能提升对逆序对应用的理解。
3. **P5634 【CSGRound2】开拓者的卓识**：结合了逆序对与其他算法思想，有一定难度，可加深对逆序对在复杂场景下应用的掌握。 

---
处理用时：89.79秒