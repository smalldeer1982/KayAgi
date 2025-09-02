# Vasya the Architect

## 题目描述

Once Vasya played bricks. All the bricks in the set had regular cubical shape. Vasya vas a talented architect, however the tower he built kept falling apart.

Let us consider the building process. Vasya takes a brick and puts it on top of the already built tower so that the sides of the brick are parallel to the sides of the bricks he has already used. Let's introduce a Cartesian coordinate system on the horizontal plane, where Vasya puts the first brick. Then the projection of brick number $ i $ on the plane is a square with sides parallel to the axes of coordinates with opposite corners in points $ (x_{i,1},y_{i,1}) $ and $ (x_{i,2},y_{i,2}) $ . The bricks are cast from homogeneous plastic and the weight of a brick $ a×a×a $ is $ a^{3} $ grams.

It is guaranteed that Vasya puts any brick except the first one on the previous one, that is the area of intersection of the upper side of the previous brick and the lower side of the next brick is always positive.

We (Vasya included) live in a normal world where the laws of physical statics work. And that is why, perhaps, if we put yet another brick, the tower will collapse under its own weight. Vasya puts the cubes consecutively one on top of the other until at least one cube loses the balance and falls down. If it happens, Vasya gets upset and stops the construction. Print the number of bricks in the maximal stable tower, that is the maximal number $ m $ satisfying the condition that all the towers consisting of bricks 1, 2, ..., $ k $ for every integer $ k $ from 1 to $ m $ remain stable.

## 样例 #1

### 输入

```
2
0 0 3 3
1 0 4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
0 0 3 3
2 0 5 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
0 0 3 3
1 0 4 3
2 0 5 3
```

### 输出

```
3
```

# 题解

## 作者：封禁用户 (赞：3)

## 题解：CF38D Vasya the Architect

**物理公式题**。

### 解题思路

**暴力枚举**放第 $i$ 块方块时塔会不会倒。

如果放第 $i$ 块时这个塔的第 $1$ 到 $i$ 层，$2$ 到 $i$ 层 $\cdots\ i - 1$ 到 $i$ 层的质心都在支点上，则此时塔是稳定的。否则塔是不稳定的，输出 $i - 1$。如果整个塔直到所有方块放完还没有倒塌，输出 $n$。我们可以直接套用物理公式求解答案，复杂度 $O(n^3)$。

### 物理知识补充

一个物体是稳定的，当且仅当在它的任何点上，施加在该点上的力矩和为零。即，该物体的质心投影位于该物体所在的支点投影的内部或边界时，它才是稳定的。

若现在在检查放置第 $k$ 个方块，每个立方体的左上角为 $(x_{i , 1} , y_{i , 1})$，右下角的坐标为 $(x_{i , 2} , y_{i , 2})$，则这部分的质心投影坐标为，$(x_c , y_c)$，有：

$$x_c = \frac{\sum_{i}^{k}(|x_{i,1}-x_{i,2}|^3\times\frac{x_{i,1}+x_{i,2}}{2})}{\sum_{i}^{k}|x_{i,1}-x_{i,2}|^3},y_c=\frac{\sum_{i}^{k}(|y_{i,1}-y_{i,2}|^3\times\frac{y_{i,1}+y_{i,2}}{2})}{\sum_{i}^{k}|y_{i,1}-y_{i,2}|^3}$$

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , a[105] , b[105] , c[105] , xa , ya , xb , yb , w;
double u , v;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> xa >> ya >> xb >> yb;
		a[i] = xa + xb;
		b[i] = ya + yb;
		c[i] = abs(xb - xa);
		for(int j = 1 ; j <= i ; j++)
		{
			u = v = w = 0;
			for(int k = j + 1 ; k <= i ; k++)
			{
				int m = c[k] * c[k] * c[k];
				u += a[k] * m;
				v += b[k] * m;
				w += m;
			}
			u = u / w;
			v = v / w;
			if(max(fabs(u - a[j]) , fabs(v - b[j])) > c[j])
			{
				cout << i - 1;
				return 0;
			}
		}
	}
	cout << n;
	return 0;
}
```

[record](https://codeforces.com/contest/38/submission/284274177)。

---

## 作者：FFTotoro (赞：2)

## 前言

CF 远古物理题，没给出任何的提示，对于一些物理不好的同学不是很公平。而且官网上只有俄语题解。

## 解法

本题需要一些前置物理知识。

一个物体是稳定的，当且仅当在它的任何点上，施加在该点上的力矩和为零。即，该物体的质心投影位于该物体所在的支点投影的内部或边界时，它才是稳定的。

考虑原问题，每次添加一个立方体时，都要考虑它会不会使整个系统的稳定的状态被打破：只用判断整个“塔”中的所有“后缀”是否稳定即可。具体地，我们只要求出这个后缀的质心即可解决问题。

按照题目描述，设整个“后缀”的质心投影的坐标为 $(x_c,y_c)$，每一个立方体的投影的左上角、右下角的坐标为 $(x_{i,1},y_{i,1}),(x_{i,2},y_{i,2})$，我们有：

设 $x_i=\dfrac{x_{i,1}+x_{i,2}}{2},y_i=\dfrac{y_{i,1}+y_{i,2}}{2},$

$m_i=|x_{i,1}-x_{i,2}|^3=|y_{i,1}-y_{i,2}|^3,$

有 $x_c=\dfrac{\sum\limits_im_ix_i}{\sum\limits_im_i},y_c=\dfrac{\sum\limits_im_iy_i}{\sum\limits_im_i}$。

直接套用上面的公式循环求解即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<int> a(n),b(n),c(n);
  for(int i=0;i<n;i++){
    int x1,y_,x2,y2; cin>>x1>>y_>>x2>>y2;
    // 这里不用 y1 的原因是会与 cmath 库里面的 y1 函数发生命名冲突，导致 CE
    a[i]=x1+x2,b[i]=y_+y2,c[i]=abs(x2-x1); // c[i] 的立方即为 m[i]
    for(int j=0;j<i;j++){
      double u=0,v=0; int w=0;
      for(int k=j+1;k<=i;k++){
        int m=c[k]*c[k]*c[k];
        u+=a[k]*m,v+=b[k]*m,w+=m; // 套公式
      }
      u=u/w,v=v/w; // 套公式，两个和相除
      if(max(fabs(u-a[j]),fabs(v-b[j]))>c[j]+1e-8){
        cout<<i<<endl; return 0;
      } // 判断质心的投影是否在规定区域内，加上 1e-8 是为了避免精度误差
    }
  }
  cout<<n<<endl; // 能垒完所有的立方体
  return 0;
}
```

---

