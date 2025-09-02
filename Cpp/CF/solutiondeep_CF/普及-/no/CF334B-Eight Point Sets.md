# 题目信息

# Eight Point Sets

## 题目描述

Gerald is very particular to eight point sets. He thinks that any decent eight point set must consist of all pairwise intersections of three distinct integer vertical straight lines and three distinct integer horizontal straight lines, except for the average of these nine points. In other words, there must be three integers $ x_{1},x_{2},x_{3} $ and three more integers $ y_{1},y_{2},y_{3} $ , such that $ x_{1}&lt;x_{2}&lt;x_{3} $ , $ y_{1}&lt;y_{2}&lt;y_{3} $ and the eight point set consists of all points $ (x_{i},y_{j}) $ ( $ 1<=i,j<=3 $ ), except for point $ (x_{2},y_{2}) $ .

You have a set of eight points. Find out if Gerald can use this set?

## 样例 #1

### 输入

```
0 0
0 1
0 2
1 0
1 2
2 0
2 1
2 2
```

### 输出

```
respectable
```

## 样例 #2

### 输入

```
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
```

### 输出

```
ugly
```

## 样例 #3

### 输入

```
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
```

### 输出

```
ugly
```

# AI分析结果

### 题目内容
# 八点集

## 题目描述
杰拉尔德对八点集非常挑剔。他认为，任何像样的八点集都必须由三条不同的整数垂直直线和三条不同的整数水平直线的所有两两交点组成，但不包括这九个点的“中间点”。换句话说，必须存在三个整数 \(x_1\)、\(x_2\)、\(x_3\) 以及另外三个整数 \(y_1\)、\(y_2\)、\(y_3\)，使得 \(x_1 < x_2 < x_3\)，\(y_1 < y_2 < y_3\)，并且八点集由所有点 \((x_i, y_j)\)（\(1 \leq i, j \leq 3\)）组成，但不包括点 \((x_2, y_2)\)。

你有一个八点集。判断杰拉尔德是否可以使用这个集合？

## 样例 #1
### 输入
```
0 0
0 1
0 2
1 0
1 2
2 0
2 1
2 2
```
### 输出
```
respectable
```

## 样例 #2
### 输入
```
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
```
### 输出
```
ugly
```

## 样例 #3
### 输入
```
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
```
### 输出
```
ugly
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕判断给定的8个点是否能构成符合特定要求的八点集。思路主要分为以下几类：
1. **排序后判断坐标关系**：通过对8个点按横纵坐标排序，利用排序后点的位置关系，直接判断是否满足八点集的坐标分布规律，如某些点的横、纵坐标应分别相等。
2. **统计横纵坐标种类**：先统计不同横坐标和纵坐标的个数是否恰好为3个，再结合其他条件判断。如判断点是否重复，以及点的横纵坐标是否符合在“九宫格”去掉中间点的分布（即横或纵坐标为最大或最小值）。

各题解的难点主要在于准确梳理出八点集的坐标特征，并转化为代码中的判断条件。不同题解在实现细节上有所差异，例如判断点是否重复、利用数据结构辅助判断等方面。

### 所选的题解
- **作者：dthythxth_Huge_Brain (5星)**
    - **关键亮点**：思路清晰，先重载运算符对8个点排序，然后直接通过判断点之间的坐标关系来确定是否为合法八点集，代码简洁明了。
    - **重点代码**：
```cpp
bool operator<(st u,st v){
    if(u.x<v.x)return true;
    else if((u.x==v.x)&&(u.y<v.y))return true;
    return false;
}
void solve(){
	for(int i=1;i<=8;i++)for(int j=1;j<=8;j++)if((i!=j)&&(a[i].x==a[j].x)&&(a[i].y==a[j].y)){
		puts("ugly");
		exit(0);
	}
	if((a[3].y!=a[5].y)||(a[8].y!=a[3].y)||(a[2].y!=a[7].y)||(a[2].y!=a[7].y)||(a[1].x!=a[2].x)||(a[2].x!=a[3].x)||(a[4].x!=a[5].x)||(a[4].x!=a[5].x)||(a[6].x!=a[8].x)||(a[7].x!=a[8].x)||(a[1].y!=a[4].y)||(a[1].y!=a[6].y))puts("ugly");
	else puts("respectable");
}
```
    - **核心实现思想**：重载小于运算符对结构体数组`a`进行排序，先判断是否有重复点，再通过一系列具体的坐标关系判断是否为合法八点集。

- **作者：Alex_Wei (5星)**
    - **关键亮点**：同样先排序，然后通过清晰的坐标关系判断条件，同时强调了先计算不同横坐标和纵坐标个数是否为3的重要性，逻辑完整。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
}c[8];
bool cmp(node a,node b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
//从上到下，从左到右
int x,y,a[1000002],b[1000002];
int main()
{
	for(int i=0;i<8;i++)
		cin>>c[i].x>>c[i].y;
	for(int i=0;i<8;i++)
		x+=!a[c[i].x],a[c[i].x]++,y+=!b[c[i].y],b[c[i].y]++;//求出不同的纵，横坐标个数
	sort(c,c+8,cmp);//排序（相当于依次编号） 
	if(x==3&&y==3&&c[0].x==c[1].x&&c[1].x==c[2].x&&c[3].x==c[4].x&&c[5].x==c[6].x&&c[6].x==c[7].x&&
	c[0].y==c[3].y&&c[3].y==c[5].y&&c[1].y==c[6].y&&c[2].y==c[4].y&&c[4].y==c[7].y)cout<<"respectable";
	else cout<<"ugly";
	return 0;
}
```
    - **核心实现思想**：定义结构体`node`存储点坐标，通过`cmp`函数排序，利用数组`a`和`b`统计不同横、纵坐标个数，最后根据横纵坐标个数及排序后点的坐标关系判断。

- **作者：conti123 (4星)**
    - **关键亮点**：详细分析了八点集合法的条件，包括无重复点、由特定直线交点组成、横纵坐标不同值个数为3等，代码实现基于这些条件逐步判断。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int maxx=-1,minx=1e7,maxy=-1,miny=1e7,x[10],y[10];
set<int>countx,county;
set<pair<int,int>>countxy;//set能自动去重 
signed main()
{
	for(int i=1;i<=8;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		maxx=max(maxx,x[i]),maxy=max(maxy,y[i]);
		minx=min(minx,x[i]),miny=min(miny,y[i]);
		countx.insert(x[i]),county.insert(y[i]);
		countxy.insert(make_pair(x[i],y[i]));
	}
	if(countx.size()!=3||county.size()!=3||countxy.size()!=8)
	{
		puts("ugly");
		return 0;
	}
	for(int i=1;i<=8;i++)
		if(x[i]!=minx&&x[i]!=maxx&&y[i]!=miny&&y[i]!=maxy)
		{
			puts("ugly");
			return 0;
		}
	puts("respectable");
}
```
    - **核心实现思想**：利用`set`自动去重特性，统计不同横、纵坐标个数及点对个数，通过判断横纵坐标是否为最大或最小值来确定是否为合法八点集。

### 最优关键思路或技巧
1. **排序与坐标关系判断**：对八点集进行排序后，利用排序后点的相对位置确定横纵坐标的相等关系，这是直接且有效的判断方式。
2. **利用数据结构辅助判断**：如使用`set`来统计不同横、纵坐标个数以及去重判断点是否重复，简化了代码实现。

### 拓展思路
同类型题目通常围绕几何图形的点集判断，类似算法套路包括先明确图形点集的数学特征，转化为代码中的条件判断，可能涉及排序、统计、坐标关系分析等操作。

### 推荐题目
1. **P1090 [NOIP2004 提高组] 合并果子**：涉及贪心策略，通过模拟合并过程求解最优值，与本题一样需要分析题目条件并转化为代码逻辑。
2. **P1249 最大乘积**：同样是模拟类型题目，通过枚举和计算不同组合的乘积，与本题类似在于对给定条件的模拟实现。
3. **P1163 银行贷款**：需要根据给定规则模拟还款过程，锻炼对实际问题条件的分析与代码实现能力，和本题判断八点集的逻辑分析有相似之处。 

---
处理用时：83.93秒