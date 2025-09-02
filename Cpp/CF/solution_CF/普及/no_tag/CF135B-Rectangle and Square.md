# Rectangle and Square

## 题目描述

给定 $8$ 个点，判断它们是否能组成一个正方形和一个矩形。矩形可以是正方形，且长方形和正方形面积均非零。不强制要求图形和坐标轴平行。

## 样例 #1

### 输入

```
0 0
10 11
10 0
0 11
1 1
2 2
2 1
1 2
```

### 输出

```
YES
5 6 7 8
1 2 3 4
```

## 样例 #2

### 输入

```
0 0
1 1
2 2
3 3
4 4
5 5
6 6
7 7
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
0 0
4 4
4 0
0 4
1 2
2 3
3 2
2 1
```

### 输出

```
YES
1 2 3 4
5 6 7 8
```

# 题解

## 作者：封禁用户 (赞：4)

## CF135B Rectangle and Square 题解
### 解题思路
这道题涉及的算法有**数学**、**枚举**和**全排列**。

刚看到这道题时，发现在坐标系中只有 $8$ 个点，便想要尝试枚举 $x$ 坐标相等和 $y$ 坐标相等的点来确定长方形和正方形。但是，题目告诉我，我太天真了。题目中有：“不强制要求图形和坐标轴平行。”就像这样：

![1](https://cdn.luogu.com.cn/upload/image_hosting/1tealny5.png?x-oss-process=image/resize,m_lfit,h_170,w_225) ![2](https://cdn.luogu.com.cn/upload/image_hosting/mv18dork.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以，我们只能换一种方法做了。

在小学数学中，我们学过正方体的四条边都相等，而长方体对边相等，于是，我们可以通过勾股定理推出这条边的长短，再对边长进行比较。

![3](https://cdn.luogu.com.cn/upload/image_hosting/yin53tfl.png?x-oss-process=image/resize,m_lfit,h_170,w_225) ![4](https://cdn.luogu.com.cn/upload/image_hosting/90jvhs0f.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但是，如果遇到一个菱形，那么这个判断方法就失效了。

![5](https://cdn.luogu.com.cn/upload/image_hosting/8hobcmut.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以，我们要增加一个条件，就是这个图形中至少有一个角是直角。这个也可以用勾股定理实现，就不再赘述了。

最后，我们枚举所有点构成图形的可能情况，按照以上方法判断就可以 $\texttt{AC}$ 了。
#### 附上推出边长短的公式：
$\text{边长} = \sqrt{(x_1-x_2)^{2}+(y_1-y_2)^{2}}$
#### 最后注明这道题的几个坑点：

- 边长不一定是整数，所以开 $\texttt{int}$ 或 $\texttt{long long}$ 不可行。
- 有时这道题会出现精度问题，直接用双等号判断会失误。
- 要特判三点共线和四点共线的情况，有些样例会骗过勾股定理。

### 参考代码
```cpp
#include<bits\stdc++.h>
using namespace std;
int x[10] , y[10] , tmpx[5] , tmpy[5];
bool square[10];
double s[10];
bool line()
{
	sort(tmpx + 1 , tmpx + 5);
	sort(tmpy + 1 , tmpy + 5);
	if(tmpx[1] == tmpx[2] && tmpx[2] == tmpx[3])
	{
		return 1;
	}
	if(tmpx[2] == tmpx[3] && tmpx[3] == tmpx[4])
	{
		return 1;
	}
	if(tmpy[1] == tmpy[2] && tmpy[2] == tmpy[3])
	{
		return 1;
	}
	if(tmpy[2] == tmpy[3] && tmpy[3] == tmpy[4])
	{
		return 1;
	}
	return 0;
}
bool check()
{
	for(int i = 1 ; i <= 8 ; i++)
	{
		if(square[i])
		{
			continue;
		}
		for(int j = i + 1 ; j <= 8 ; j++)
		{
			if(square[j])
			{
				continue;
			}
			for(int k = j + 1 ; k <= 8 ; k++)
			{
				if(square[k])
				{
					continue;
				}
				for(int l = k + 1 ; l <= 8 ; l++)
				{
					if(square[l])
					{
						continue;
					}
					tmpx[1] = x[i];
					tmpx[2] = x[j];
					tmpx[3] = x[k];
					tmpx[4] = x[l];
					tmpy[1] = y[i];
					tmpy[2] = y[j];
					tmpy[3] = y[k];
					tmpy[4] = y[l];
					if(line())
					{
						continue;
					}
					s[1] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
					s[2] = sqrt((x[j] - x[k]) * (x[j] - x[k]) + (y[j] - y[k]) * (y[j] - y[k]));
					s[3] = sqrt((x[k] - x[l]) * (x[k] - x[l]) + (y[k] - y[l]) * (y[k] - y[l]));
					s[4] = sqrt((x[l] - x[i]) * (x[l] - x[i]) + (y[l] - y[i]) * (y[l] - y[i]));
					s[5] = sqrt((x[i] - x[k]) * (x[i] - x[k]) + (y[i] - y[k]) * (y[i] - y[k]));
					s[6] = sqrt((x[l] - x[j]) * (x[l] - x[j]) + (y[l] - y[j]) * (y[l] - y[j]));
					sort(s + 1 , s + 7);
					if(s[1] == s[2] && s[3] == s[4] && abs(s[1] * s[2] + s[3] * s[4] - s[6] * s[7]) < 0.001)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void print()
{
	cout << "YES\n";
	for(int i = 1 ; i <= 8 ; i++)
	{
		if(square[i])
		{
			cout << i << ' ';
		}
	}
	cout << endl;
	for(int i = 1 ; i <= 8 ; i++)
	{
		if(!square[i])
		{
			cout << i << ' ';
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	for(int i = 1 ; i <= 8 ; i++)
	{
		cin >> x[i] >> y[i];
	}
	for(int i = 1 ; i <= 8 ; i++)
	{
		for(int j = i + 1 ; j <= 8 ; j++)
		{
			for(int k = j + 1 ; k <= 8 ; k++)
			{
				for(int l = k + 1 ; l <= 8 ; l++)
				{
					s[1] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
					s[2] = sqrt((x[j] - x[k]) * (x[j] - x[k]) + (y[j] - y[k]) * (y[j] - y[k]));
					s[3] = sqrt((x[k] - x[l]) * (x[k] - x[l]) + (y[k] - y[l]) * (y[k] - y[l]));
					s[4] = sqrt((x[l] - x[i]) * (x[l] - x[i]) + (y[l] - y[i]) * (y[l] - y[i]));
					s[5] = sqrt((x[i] - x[k]) * (x[i] - x[k]) + (y[i] - y[k]) * (y[i] - y[k]));
					s[6] = sqrt((x[l] - x[j]) * (x[l] - x[j]) + (y[l] - y[j]) * (y[l] - y[j]));
					sort(s + 1 , s + 7);
					if(s[1] == s[2] && s[2] == s[3] && s[3] == s[4] && abs(s[1] * s[2] + s[3] * s[4] - s[6] * s[7]) < 0.001)
					{
						square[i] = 1;
						square[j] = 1;
						square[k] = 1;
						square[l] = 1;
						if(check())
						{
							print();
							return 0;
						}
						square[i] = 0;
						square[j] = 0;
						square[k] = 0;
						square[l] = 0;
					}
				}
			}
		}
	}
	cout << "NO";
	return 8;
}
```

---

## 作者：zym20249_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF135B)
## 题意
给定 $8$ 个点，判断它们是否能组成一个正方形和一个矩形，矩形可以是正方形，且长方形和正方形面积均不能为零。不要求图形的边和坐标轴平行。\
输出结果如果可以就输出可以，下一行为构成正方行的编号，再下行是构成矩形的编号。不可以就输出不可以。
## 思路
我们只需要判断他的四条边的两条边平行而且长度一致就可以了。\
但题目中有说过不一定与坐标轴平行，所以我们会发现菱形也被算在了内部，我们需要让他判断是否其中一个角为直角，利用勾股定理就可以了。

这里不能用整形，因为有时会出现小数。\
容易出现精度问题，不能直接用双等于。\
要注意多点一线，勾股定理可能会失效。

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF135B)

## 思路

点一共只有 $8$ 个，可以 $8!$ 枚举所有点的排列方式，前 $4$ 个为正方形，后 $4$ 个为长方形，用初中数学三垂直模型判断即可。

但这样有可能将平行四边形或菱形误判，于是需要用勾股定理判断角是否为直角。

## 代码

```cpp// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 2e5 + 5;
const LL kP = 998244353, B = 233;

LL T = 1, n = 8, a[kMaxN], b[kMaxN], f[kMaxN], ans;

void pr(bool pr) { cout << (pr ? "YES" : "NO") << '\n'; }
LL D(int i, int j) { return (a[i] - a[j]) * (a[i] - a[j]) + (b[i] - b[j]) * (b[i] - b[j]); }

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (; T; T--, ans = 0) {
    for (int i = 1; i <= n; i++) {
      cin >> a[i] >> b[i], f[i] = i;
    }
    do {
      LL x[5] = {0, abs(a[f[2]] - a[f[1]]), abs(b[f[2]] - b[f[3]]), abs(a[f[4]] - a[f[3]]), abs(b[f[1]] - b[f[4]])}, y[5] = {0, abs(b[f[1]] - b[f[2]]), abs(a[f[2]] - a[f[3]]), abs(b[f[4]] - b[f[3]]), abs(a[f[1]] - a[f[4]])};
      if (x[1] == x[2] && x[2] == x[3] && x[3] == x[4] && y[1] == y[2] && y[2] == y[3] && y[3] == y[4] && D(f[1], f[2]) + D(f[2], f[3]) == D(f[1], f[3])) {
        LL x_[5] = {0, abs(a[f[6]] - a[f[5]]), abs(b[f[6]] - b[f[7]]), abs(a[f[8]] - a[f[7]]), abs(b[f[5]] - b[f[8]])}, y_[5] = {0, abs(b[f[5]] - b[f[6]]), abs(a[f[6]] - a[f[7]]), abs(b[f[8]] - b[f[7]]), abs(a[f[5]] - a[f[8]])};
        if (x_[1] == x_[3] && x_[2] == x_[4] && y_[1] == y_[3] && y_[4] == y_[2] && D(f[5], f[6]) + D(f[6], f[7]) == D(f[5], f[7])) {
          return pr(1), cout << f[1] << ' ' << f[2] << ' ' << f[3] << ' ' << f[4] << "\n" << f[5] << ' ' << f[6] << ' ' << f[7] << ' ' << f[8] << '\n', 0;
        }
      }
    } while (next_permutation(f + 1, f + n + 1));
  }
  pr(0);
  return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF135B Rectangle and Square
## 题目翻译
给定平面上 $8$ 个点，问是否能组成 $1$ 个正方形和 $1$ 个矩形。若可以则构造一组方案。
## 一道考察是否会写代码的好题
这道题首先需要解决的就是如何去枚举这 $8$ 个点。\
如若暴力枚举 $8$ 个点，虽然复杂度可行，但是代码会十分不雅。\
于是我们尝试曲线救国。\
我们只需要把所有情况列举出来（选哪 $4$ 个为正方形，哪 $4$ 个为矩形，摆放顺序是什么），因此我们利用将点的编号全排列，把前 $4$ 个和后 $4$ 个分别为矩形，顺序也按逆时针依次排列。\
那么接下来就是如何判断矩形和正方形了。\
首先我们明确一点，我们只需要得到两个矩形并且至少一个矩形的四条边都相等即可。\
而我们既然已经确定了摆放顺序，四条边相等就轻而易举了。\
关键是如何判断矩形。\
有人用对角线相等来判断，但是需要特判一条线的情况，我认为十分不优雅，于是我来介绍一种优雅的方法。\
根据两点间距离公式我们可以求出两两之间边的长度，那矩形与其它形状的区别就在于矩形四个角都是直角。\
那进一步直角有什么性质呢？\
众所周知平面直角坐标系的横轴纵轴夹角就是直角，在线性代数的角度只有此时两条边的叉乘恰好等于两条边的长度之积。\
那么我们只需要判断是否四个角都为直角（三个角也行），就可以判断一个图形是否是矩形。\
在这里由于我们已经确定了摆放顺序，所以这一步十分容易。
## code
```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
const double eps=1e-11;
struct point{
    double x,y;
}a[8];
int id[8],numz,numj,flag;
bool same(double c1,double c2){
    return abs(c1-c2)<eps;
}
double getlen(point A,point B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
double getsum(point A,point B,point mid){
    A.x-=mid.x;A.y-=mid.y;B.x-=mid.x;B.y-=mid.y;
    return abs((A.x*B.y)-(A.y*B.x));
}
void make(int d){
    double e[4];
    for(int i=0;i<4;++i){
        int u=i,v=(i+1)%4;
        e[i]=getlen(a[id[u+d]],a[id[v+d]]);
    }
    if(same(e[0],e[1])&&same(e[1],e[2])&&same(e[2],e[3]))numz++;
    int straight=0;
    for(int i=0;i<4;++i){
        int u=(i+3)%4,v=(i+1)%4;
        double s=getsum(a[id[u+d]],a[id[v+d]],a[id[i+d]]);
        if(same(s,e[u]*e[i]))straight++;
    }
    if(straight==4)numj++;
    return;
}
bool check(){
    numz=numj=flag=0;
    make(0);
    if(numz==1)flag=1;
    make(4);
    if(numz>=1&&numj>=2)return 1;
    return 0;
}
signed main(){
    for(int i=0;i<8;++i){
        cin>>a[i].x>>a[i].y;
        id[i]=i;
    }
    for(int i=1;i<=40320;++i){
        if(check()){
            cout<<"YES\n";
            if(!flag)for(int i=0;i<4;++i)swap(id[i],id[i+4]);
            cout<<id[0]+1<<' '<<id[1]+1<<' '<<id[2]+1<<' '<<id[3]+1<<'\n';
            cout<<id[4]+1<<' '<<id[5]+1<<' '<<id[6]+1<<' '<<id[7]+1<<'\n';
            return 0;
        }
        next_permutation(id,id+8);
    }
    cout<<"NO\n";
    return 0;
}
```

---

## 作者：Leaves_xw (赞：0)

题目难度：黄。涉及的算法：数学，搜索，全排列枚举。

**思路：**

首先我们要把 $8$ 个坐标全排列枚举一遍。

那么如何判断是正方形或一个矩形呢？

**正方形判断方法：**

根据平面直角坐标系上，给出两个点的坐标，既可以根据公式 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 求出线段的长度，如果每一条线段都相等，则就是一个正方形。

**矩形判断方法：**

跟正方形的差不多，只需要判断其中的一个角是直角且对边长度相等即可。

---

## 作者：lukzia (赞：0)

### 题解

数据范围不大，暴力枚举每个点即可 

时间复杂度$O(1)$ ~~常数有点大233~~

***对于矩形的判定：***

~~复习初中内容（~~


我们有这么一个几何图形：

![](https://cdn.luogu.com.cn/upload/image_hosting/pk7knx5u.png)

要证明它是一个矩形，先要证明它是平行四边形，所以它的对边要相等。

![](https://cdn.luogu.com.cn/upload/image_hosting/bvahko4t.png)

对于一个平行四边形，我们只需要证明它的其中一个角是直角便可证明他是矩形。

~~我比较菜，不会什么叉积。~~

我们只需使用 *勾股逆定理* 便可

> 如果三角形两条边的平方和等于第三边的平方，那么这个三角形就是直角三角形。最长边所对的角为直角

![](https://cdn.luogu.com.cn/upload/image_hosting/lbk1am0p.png)

$$a^2 + b^2 = c^2$$

而

$$a = (y_k - y_i)^2 + (x_k-x_i)^2$$

$$b = (y_i - y_k)^2 + (x_j-x_i)^2$$

$$c = (y_k - y_j)^2 + (x_k-x_j)^2$$

对于 ***正方形*** ，我们只需证明它是 ***临边相等*** 即可。

### 代码

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define n 8
#define ix star[i].x
#define jx star[j].x
#define kx star[k].x
#define lx star[l].x
#define iy star[i].y
#define jy star[j].y
#define ky star[k].y
#define ly star[l].y
#define fors(a,c) for(register int a=1;a<=c;a++)

//对边是否相等
#define cube1 (iy - jy) ==  (ly - ky) and  (lx - ix) ==  (kx - jx)

//临边是否相等
#define cube2 pow((iy-jy),2) + pow((jx-ix),2) == pow((ly - iy),2) + pow((lx-ix),2)

//四个点连成一条线是不合法的欧
#define other  ky != jy and  jx !=  ix

//是否有直角
#define zhijiao  pow((iy-jy),2) +  pow((jx-ix),2) +  pow((ly - iy),2) +  pow((lx-ix),2) ==  pow((lx-jx),2) +  pow((ly-jy),2)
using namespace std;
 
struct S
{
	int x, y;
} star[10];
 
bool done, vis[10];
 
vector<int> v, v1;
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	fors(i, n)
	cin >> ix >> iy;

	fors(i, n) //找正方形
	{
		fors(j, n)
		{
			fors(k, n)
			{
				fors(l, n)
				{
					if (i == j or j == k or k == l or i == k or i == l or j == l) continue;  //判重
					if (cube1 and cube2 and other and zhijiao)
					{
			            vis[i] = vis[j] = vis[k] = vis[l] = true; //标记点已被使用
			            v.push_back(i), v.push_back(j), v.push_back(k), v.push_back(l);
			            sort(v.begin(), v.end());  //暴力排序233
			            done = 1;
			            break;
					}

				}
				if (done)
					break;
			}
			if (done)
				break;
		}
		if (done)
			break;
	}
	if (!done) {cout << "NO" << endl; return 0;}
	done = 0;
	fors(i, n) //找矩形
	{
		if (vis[i])  //如果当前点被使用了，跳过
			continue;
		fors(j, n)
		{
			if (vis[j])
				continue;  //如果当前点被使用了，跳过
			fors(k, n)
			{
				if (vis[k])
					continue;  //如果当前点被使用了，跳过
				fors(l, n)
				{
					if (vis[l])  //如果当前点被使用了，跳过
						continue;
					if (i == j or j == k or k == l or i == k or i == l or j == 	 l) continue; //判重
					if (cube1 and other and zhijiao)
					{
						v1.push_back(i), v1.push_back(j), v1.push_back(k), v1.push_back(l);
						sort(v1.begin(), v1.end());  //暴力排序233
						done = 1;
						break;
					}
				}
				if (done)
					break;
			}
			if (done)
				break;
		}
		if (done)
			break;
	}
	if (!done) {cout << "NO" << endl; return 0;}
 
	cout << "YES" << endl;  //输出答案
	for (int q = 0; q < 4; q++)
		cout << v[q] << " ";
	cout << endl;
	for (int q = 0; q < 4; q++)
		cout << v1[q] << " ";

	return 0;
}
```



---

## 作者：D愚者 (赞：0)

### 思路：

按字典序枚举8的全排列，再判断正方形和矩形即可。

正方形判定可以用四边相等，对角线相等。

矩形判定可以用两组对边分别相等，对角线相等。


---

