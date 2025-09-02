# 题目信息

# Connect the Points

## 题目描述

You are given three points on a plane. You should choose some segments on the plane that are parallel to coordinate axes, so that all three points become connected. The total length of the chosen segments should be the minimal possible.

Two points $ a $ and $ b $ are considered connected if there is a sequence of points $ p_0 = a, p_1, \ldots, p_k = b $ such that points $ p_i $ and $ p_{i+1} $ lie on the same segment.

## 说明/提示

The points and the segments from the example are shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666C/076acbc26156c4b983e140e9e71fa403c1c87ecb.png)

## 样例 #1

### 输入

```
1 1
3 5
8 6```

### 输出

```
3
1 1 1 5
1 5 8 5
8 5 8 6```

# AI分析结果

### 题目翻译
# 连接点

## 题目描述
在平面上给定三个点。你应该在平面上选择一些平行于坐标轴的线段，使得这三个点都连通。所选线段的总长度应尽可能小。

如果存在一个点序列 $p_0 = a, p_1, \ldots, p_k = b$，使得点 $p_i$ 和 $p_{i + 1}$ 位于同一条线段上，则认为两个点 $a$ 和 $b$ 是连通的。

## 说明/提示
示例中的点和线段如下所示。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666C/076acbc26156c4b983e140e9e71fa403c1c87ecb.png)

## 样例 #1
### 输入
```
1 1
3 5
8 6
```
### 输出
```
3
1 1 1 5
1 5 8 5
8 5 8 6
```

### 算法分类
构造

### 综合分析与结论
- **思路对比**：三位作者都先对三个点按横坐标排序，在此基础上进行线段构造。BorisDimitri 找到第二大的纵坐标 $y_{mid}$，从 $(x_{min},y_{mid})$ 向 $(x_{max},y_{mid})$ 连边，再将各点竖直连到 $y_{mid}$；Cuiyi_SAI 确定两条线段 $(x_1,y_1,x_2,y_1)$ 和 $(x_3,y_3,x_2,y_3)$ 后，在合适位置连第三条线；eb0ycn 找到 $y$ 坐标中位数确定“主干道”，再将各点连到“主干道”。
- **算法要点**：均利用排序确定点的顺序，通过寻找合适的纵坐标来构造平行于坐标轴的线段，使三个点连通且总长度最小。
- **解决难点**：核心在于证明最小总长度为 $x_{max} - x_{min} + y_{max} - y_{min}$，并构造出达到该长度的线段方案。

### 题解列表
- **BorisDimitri（5星）**
  - **关键亮点**：思路清晰，先证明最小长度，再给出具体构造方法，代码可读性高。
- **Cuiyi_SAI（4星）**
  - **关键亮点**：抛弃复杂的曼哈顿距离思路，直接构造三条线段，逻辑简洁。
- **eb0ycn（3星）**
  - **关键亮点**：手写冒泡排序，适合理解排序原理，但代码整体简洁性和可读性稍逊。

### 重点代码
#### BorisDimitri 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

pair<int,int> p[10];
vector<int> px,py;

int main()
{
	int n = 3;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i].x>>p[i].y;
		px.push_back(p[i].x), py.push_back(p[i].y);
	}
	
	sort(p+1,p+1+n);
	sort(px.begin(),px.end());
	sort(py.begin(),py.end());
	
	vector<vector<int>> ans;
	ans.push_back({px[0],py[1],px[2],py[1]});
	for(int i=1;i<=3;i++)
	{
		if(p[i].y != py[1]) ans.push_back({p[i].x,p[i].y,p[i].x,py[1]});
	}
	
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++)
	{
		for(int j=0;j<ans[i].size();j++)
			printf("%d ",ans[i][j]);
		cout<<endl;
	}
	
	return 0;
}
```
**核心实现思想**：先读取三个点的坐标，将点按横坐标排序，同时记录横、纵坐标并排序。找到第二大的纵坐标，构造一条平行于 $x$ 轴的线段，再将不在该纵坐标上的点竖直连到该线段。

#### Cuiyi_SAI 的代码
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
struct node
{
	int x,y;
} a[4];
bool cmp(node s,node t)
{
	return s.x<t.x;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=3;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+3,cmp);
	if(a[1].y>a[3].y) swap(a[1],a[3]);
	cout<<3<<'\n';
	cout<<a[1].x<<' '<<a[1].y<<' '<<a[2].x<<' '<<a[1].y<<'\n';
	cout<<a[2].x<<' '<<a[3].y<<' '<<a[3].x<<' '<<a[3].y<<'\n';
	cout<<a[2].x<<' '<<max({a[1].y,a[2].y,a[3].y})<<' '<<a[2].x<<' '<<min({a[1].y,a[2].y,a[3].y});
	return 0;
} 
```
**核心实现思想**：定义结构体存储点的坐标，按横坐标排序。根据排序后的点构造三条线段，直接输出线段端点坐标。

### 最优关键思路或技巧
- 先对三个点按横坐标排序，便于后续构造线段。
- 找到合适的纵坐标（如第二大的纵坐标、中位数等）作为基准，构造平行于坐标轴的线段，使三个点连通且总长度最小。

### 拓展思路
同类型题目可能会增加点的数量或改变连通条件，解题思路仍可从排序和构造线段入手，根据具体条件调整构造方法。

### 洛谷题目推荐
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得
Cuiyi_SAI 提到第一眼想用曼哈顿距离求解，但发现比较麻烦，于是抛弃该思路重新思考，最终找到更简单的构造方法。这提示我们在解题时如果发现当前思路复杂，可及时转换思路。 

---
处理用时：41.83秒