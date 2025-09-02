# Number of Triplets

## 题目描述

You are given $ n $ points on a plane. All points are different.

Find the number of different groups of three points $ (A,B,C) $ such that point $ B $ is the middle of segment $ AC $ .

The groups of three points are considered unordered, that is, if point $ B $ is the middle of segment $ AC $ , then groups $ (A,B,C) $ and $ (C,B,A) $ are considered the same.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
0 0
-1 0
0 1
```

### 输出

```
0
```

# 题解

## 作者：abc1234shi (赞：1)

# 题目要求
题目说得很清楚，给你一堆点，这些点的坐标都不一样。然后让你找出有多少组三个点 $(A,B,C)$，使得 $B$ 是 $A$ 和 $C$ 的中点。换句话说，就是 $A$、$B$、$C$ 三个点在一条直线上，$B$ 正好在 $A$ 和 $C$ 的中间。而且题目还说了，$(A, B, C)$ 和 $(C, B, A)$ 算同一个，也就是说顺序不重要。
# 怎么想这个问题
**第一步，中点的定义**

首先，得知道啥叫中点。

假设 $A$ 的坐标是 $(x1, y1)$，$C$ 的坐标是 $(x2, y2)$，那么 $B$ 的坐标就是 $((x1 + x2) ÷ 2, (y1 + y2) ÷ 2)$。这个公式很重要，后面会用到。

**第二步，暴力解法**

最直接的想法是，把所有点两两配对，看看它们的中点是不是也在这些点里。如果在，就说明找到了一个符合条件的三元组。不过，这种方法效率太低了。因为点的数量可能有 $3000$ 个，两两配对的话，计算量会非常大，肯定超时。

**第三步，聪明点的方法**

既然暴力解法不行，那得想个更聪明的办法。我们可以用一个“哈希表”（你可以把它想象成一个超级快的查找工具）。先把所有点的坐标都存到这个哈希表里，这样我们就能快速判断某个点是否存在。

接下来，我们再遍历每对点 $A$ 和 $C$，计算它们的中点 $B$ 的坐标。如果这个中点 $B$ 的坐标在哈希表里，说明这个中点 $B$ 是存在的，那么我们就找到了一个符合条件的三元组。最后，把所有找到的三元组数量加起来，就是答案。

**第四步，注意细节**

坐标是整数，但中点的坐标可能是小数。为了避免这个问题，我们可以在计算中点坐标时，把两个坐标都乘以 $2$，这样就保证了中点的坐标也是整数。

因为三元组是无序的，所以我们在计算的时候，要避免重复计算。比如，$(A, B, C)$ 和 $(C, B, A)$ 是同一个，我们只需要计算一次。
# 总结
这道题的关键在于：

- 理解中点的定义：$B$ 的坐标是 $A$ 和 $C$ 坐标的平均值。
- 用哈希表快速查找：这样可以大大提高效率。
- 注意细节：避免重复计算，确保中点坐标是整数。

其实，这道题就是一个典型的“用数据结构优化暴力解法”的问题。只要你想到了用哈希表，问题就变得简单多了。

---

## 作者：zh1221_qwq (赞：1)

感觉其他题解的做法都比较迷，单论这题的数据范围我的方法其实感觉更优。

我们考虑 $O(n^2)$，注意到点的值域只有 $1\times 10^3$，可以记一个二维数组 $b$ 存每个点出没出现过。然后枚举题中的 $a$，$b$，判断 $a$，$b$ 中点是否存在即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[2005][2005],x[3005],y[3005],ans; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		b[x[i]+1000][y[i]+1000]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if((x[i]+x[j])%2==0&&(y[i]+y[j])%2==0&&b[(x[i]+x[j])/2+1000][(y[i]+y[j])/2+1000]==1)ans++;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Starmoon_dhw (赞：0)

# Solution
前置芝士：初中数学中的坐标系和中点公式。

  题目要求我们找 $(a,b,c)$ 满足点 $B$ 是线段 $AC$ 的中点，既然是要重点，那我们可以直接联想到中点公式。具体的，对于 $2$ 个点分别记为 $(a1,b1)$，$(a2,b2)$ 他们的中点就是 $((a1+a2)\div 2,(b1+b2) \div 2 )$。
  
  知道了这个定理后，我们只需要暴力枚举即可，还有一个细节要注意，如果 $a1+a2$ 或 $b1+b2$ 是个奇数，那么就不存在可行的中点了，毕竟输入的都是整数。

---

## 作者：_5t0_0r2_ (赞：0)

# 分析：

使用一种用 vector 的做法，用 $n$ 个可变数组，每加入一个点 $P(x,y)$，将其 $y$ 值加入第 $x$ 个数组中，每次查询中点，先判断中点是否存在小数，如果没有就算出中点的坐标（假设坐标为 $(x_0,y_0)$），再查询第 $x_0$ 个数组中是否存在 $y_0$ 即可判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 30009;
struct point{
	int x,y;
} p[N];
vector<int> point_y[N];
int n,ans;
point mid_point(point p1,point p2){
	return (point){(p1.x + p2.x) >> 1,(p1.y + p2.y) >> 1};
}
bool check(point p1,point p2){
	if((p1.x + p2.x) & 1 || (p1.y + p2.y) & 1)
		return false;
	point mid = mid_point(p1,p2);
	for(int i = 0;i < (int)point_y[mid.x].size();i++)
		if(point_y[mid.x][i] == mid.y)
			return true;
	return false;
}
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d", &p[i].x, &p[i].y);
		point_y[p[i].x].push_back(p[i].y);
	}
	for(int i = 1;i < n;i++)
		for(int j = i + 1;j <= n;j++)
			if(check(p[i],p[j]))
				ans++;
	printf("%d", ans);
}
```


---

## 作者：TheSky233 (赞：0)

## Description

给你 $n$ 个不同的点，求满足点 $B$ 是线段 $AC$ 的中点的三元组 $(A,B,C)$ 个数

其中三元组是无序的，即 $(A,B,C)$ 和 $(C,B,A)$ 被认为是同一个三元组。

数据范围：$3\le n\le3000$，点的坐标都在 $[-1000,1000]$ 内。

## Solution

前置知识：中点公式、`std::set` 及 `std::pair` 的运用。

我们知道，如果有两个点 $A(x_1,y_1),C(x_2,y_2)$，那么线段 $AC$ 的中点 $B$ 的坐标为 $(\dfrac{x_1+x_2}{2},\dfrac{y_1+y_2}{2})$。于是我们只要枚举线段的两个端点，判断这条线段的中点是否在给定点集内即可。

- 一个小优化：因为点集里点的坐标都是整数，所以如果这条线段的中点坐标带有小数就跳过。

注意三元组是无序的，我们只要保证枚举时第二个点的编号大于第一个点即可。

时间复杂度：$O(n^2 \log n)$，对于本题来说可以通过。

## Code

```cpp
#include <set>
#include <utility>
#include <cstdio>

const int N=3000+5;

int n,ans;
std::set<std::pair<int, int> > st;
std::pair<int, int> point[N];

std::pair<int, int> midPoint(std::pair<int, int> a, std::pair<int, int> b){
	return std::make_pair((a.first+b.first)/2,(a.second+b.second)/2);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		point[i]=std::make_pair(x,y);
		st.insert(std::make_pair(x,y));
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			std::pair<int, int> a=point[i],b=point[j];
			if((a.first+b.first)&1 || (a.second+b.second)&1) continue;
			if(st.count(midPoint(a,b))) ans++;
		}
	}
	printf("%d\n",ans);
}
```

---

## 作者：wang_freedom (赞：0)

### 思路：
一个想法：确定了 $A$ 点和 $C$ 点就能得到 $B$ 点。

之后直接枚举 $A$ 点和 $C$ 点，在 `set` 寻找 $B$ 点。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,x,y,ans;
set<pii>st;
vector<pii>v;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	rep(i,1,n){
		cin>>x>>y;
		v.push_back({x,y});
		st.insert({x,y});
	}
	rep(i,0,n-2)
		rep(j,i+1,n-1){
			if((v[i].fi+v[j].fi)&1||(v[i].se+v[j].se)&1)
				continue;
			if(st.find({(v[i].fi+v[j].fi)/2,(v[i].se+v[j].se)/2})!=st.end())
				ans++; 
		}
	cout<<ans;
	return 0;
}
```

---

