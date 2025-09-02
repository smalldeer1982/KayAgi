# 题目信息

# [NEERC 2017] Box

## 题目描述



Bella is working in a factory that produces boxes. All boxes are in a shape of rectangular parallelepipeds. A net of the corresponding parallelepiped is cut out of a flat rectangular piece of cardboard of size $w$ *h . This net is a polygon with sides parallel to the sides of the rectangle of the cardboard. The net is bent along several lines and is connected along the edges of the resulting parallelepiped to form a box. The net is bent only along the edges of the resulting box.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15284/1.png)

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15284/2.png)

The first example

The third example

Bella is a software developer and her task is to check whether it is possible to make a box of size $a \times b \times c$ out of a cardboard of size $w \times h$ . Bella did write a program and boxes are being produced. Can you do the same?



## 说明/提示

Time limit: 3 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
1 2 3
6 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 2 3
5 5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1 1 1
10 2
```

### 输出

```
Yes
```

# AI分析结果

### 算法分类
枚举

### 综合分析与结论
该题的核心在于枚举长方体展开图的所有可能情况，并判断这些展开图是否能够放入给定的矩形纸片中。题解们主要通过枚举长方体的长、宽、高的排列组合，并结合展开图的不同类型进行判断。虽然题解们的思路相似，但在展开图的分类和判断条件上有所不同。

### 所选高星题解

#### 题解1：作者：Harry27182 (5星)
**关键亮点：**
- 详细列出了五种展开图的长宽计算公式，并通过枚举排列组合进行判断。
- 代码结构清晰，逻辑严谨，易于理解。

**核心代码：**
```cpp
bool pd(int u,int v,int w)//枚举每种展开图 
{
	if(3*u+v+w<=ww&&w+v<=hh)return true;//如果满足这种情况，就返回真 
	if(2*w+v+u<=ww&&u+v+w<=hh)return true;//同上 
	if((2*u+2*v<=ww&&2*u+w<=hh)||(2*u+2*v<=hh&&2*u+w<=ww))return true;//同上
	if((2*u+2*v<=ww&&2*v+w<=hh)||(2*u+2*v<=hh&&2*v+w<=ww))return true;//同上
	if((2*u+2*v<=ww&&u+v+w<=hh)||(2*u+2*v<=hh&&u+v+w<=ww))return true;//同上
	return false;//否则返回假 
}
```

#### 题解2：作者：Iam1789 (5星)
**关键亮点：**
- 通过排序减少枚举次数，优化了判断条件。
- 代码简洁，逻辑清晰，易于实现。

**核心代码：**
```cpp
if((a+b<=w&&3*c+b+a<=h)||(a+c<=w&&3*b+c+a<=h)||(b+c<=w&&3*a+b+c<=h))    
	cout<<"Yes";
else if((a*2+b*2<=h&&c+a*2<=w)||(a*2+c*2<=h&&b+a*2<=w))
	cout<<"Yes";
else if(a+b+c<=w&&2*a+b+c<=h)
	cout<<"Yes";
else
	cout<<"No";
```

#### 题解3：作者：Avocadooo (4星)
**关键亮点：**
- 将展开图分为三种类型，分别进行判断，思路清晰。
- 使用全排列函数简化了枚举过程。

**核心代码：**
```cpp
bool test()
{
	for(int i=1;i<=6;i++)
	{
		for(int i=1;i<=2;i++)
		{ 
			if(2*a[1]+2*a[2]<=x&&2*a[2]+a[3]<=y) return true;//情况1
			if(3*a[3]+a[1]+a[2]<=x&&a[1]+a[2]<=y) return true;//情况2
			if(2*a[1]+a[2]+a[3]<=x&&a[1]+a[2]+a[3]<=y) return true;//情况3
			swap(x,y);//旋转纸张 
		}
		next_permutation(a+1,a+4);
	}
	return false;
}
```

### 最优关键思路或技巧
1. **枚举排列组合**：通过枚举长方体的长、宽、高的排列组合，确保所有可能的展开图都被考虑。
2. **展开图分类**：将展开图分为几种类型，分别计算其长宽，简化判断条件。
3. **优化枚举**：通过排序和提前判断，减少不必要的枚举次数，提高效率。

### 可拓展之处
该题的思路可以拓展到其他几何图形的展开图问题，如正方体、棱柱等。类似的枚举和分类思想也可以应用于其他需要穷举所有可能情况的题目。

### 推荐相似题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

### 个人心得摘录
- **Harry27182**：通过画图发现展开图的长宽只有五种情况，大大简化了问题。
- **Iam1789**：排序后减少了枚举次数，提高了代码效率。
- **Avocadooo**：使用全排列函数简化了枚举过程，代码更加简洁。

---
处理用时：27.82秒