# 题目信息

# [USACO12FEB] Overplanting S

## 题目描述

Farmer John has purchased a new machine that is capable of planting grass within any rectangular region of his farm that is "axially aligned" (i.e., with vertical and horizontal sides).  Unfortunately, the machine malfunctions one day and plants grass in not one, but N (1 <= N <= 1000) different rectangular regions, some of which may even overlap.

Given the rectangular regions planted with grass, please help FJ compute the total area in his farm that is now covered with grass.

在一个笛卡尔平面坐标系里（则 $X$ 轴向右是正方向，$Y$ 轴向上是正方向），有 $N\ (1 \le N \le 1000)$ 个矩形，第 $i$ 个矩形的左上角坐标是 $(x_1,y_1)$，右下角坐标是 $(x_2,y_2)$。问这 $N$ 个矩形所覆盖的面积是多少？

注意：被重复覆盖的区域的面积只算一次。

## 样例 #1

### 输入

```
2
0 5 4 1
2 4 6 2
```

### 输出

```
20```

# AI分析结果

• 综合分析与结论：这些题解主要围绕计算多个矩形覆盖面积这一问题，提出了扫描线、矩形切割、差分等多种解法。扫描线方法通过离散化和线段树维护区间覆盖信息，按竖边扫描累加面积；矩形切割是用新矩形切割已有矩形集合，避免重复覆盖；差分则是对覆盖区域进行差分处理后前缀和还原，统计被覆盖位置面积。各题解在思路清晰度、代码可读性和优化程度上有所差异。
- 作者Ofnoname的题解（5星）
  - 关键亮点：清晰阐述扫描线算法思路，结合离散化和线段树，代码实现完整且注释详细。
  - 个人心得：提到代码在开O2优化时会WA，需更大空间，但未明确原因。
  - 核心代码片段（线段树维护部分）：
```cpp
struct Segtree
{
	#define i0 (i << 1)
	#define i1 (i << 1 | 1)
	int L[MAX << 2], R[MAX << 2], v[MAX << 2], len[MAX << 2];
	void init(int i, int l, int r)
	{
		L[i] = l, R[i] = r, v[i] = len[i] = 0;
		if (l!= r) {
			int mid = l + r >> 1;
			init(i0, l, mid), init(i1, mid+1, r);
		}
	}
	void add(int i, int l, int r, int c)
	{
		if (r < L[i] || R[i] < l) return;
		if (l <= L[i] && R[i] <= r)
			v[i] += c;
		else add(i0, l, r, c), add(i1, l, r, c);
		if (v[i]) len[i] = qy[R[i]+1] - qy[L[i]];
		else len[i] = len[i0] + len[i1];
	}
} Seg;
```
核心思想：线段树节点保存区间覆盖次数v和区间长度len，init初始化线段树，add函数实现区间修改，根据覆盖次数更新len。
- 作者山蛙or山兔的题解（4星）
  - 关键亮点：思路清晰，通过竖线切割扫描，代码简洁易懂，对扫描过程的处理逻辑清晰。
  - 核心代码片段（扫描更新答案部分）：
```cpp
for (int i=1;i<2*n;i++)
{
	if (side[i-1]==side[i]) continue;
	int m=0;
	for (int j=0;j<n;j++)
	{
		if (x[j]<=side[i-1] && side[i]<=x2[j]) arr[m++]=j;
	}
	sort(arr,arr+m,cmp);
	long long h=y[arr[0]],d=y2[arr[0]],w=side[i]-side[i-1];
	for (int j=1;j<m;j++)
	{
		int temp=arr[j];
		if (y[temp]>d)
		{
			ans+=(h-y[temp])*w;
			h=y[temp];
		}
		else
		{
			ans+=(h-d)*w;
			h=y[temp];
		}
		if (y2[temp]<d) d=y2[temp];
	}
	ans+=(h-d)*w;
}
```
核心思想：遍历排序后的竖线，找出被两条竖线穿过的矩形，按顶边排序，维护顶边h和底边d，根据矩形位置关系更新答案。
- 作者Shik__Utau的题解（4星）
  - 关键亮点：详细介绍矩形切割思想，代码实现完整，对矩形切割过程描述清晰。
  - 核心代码片段（矩形切割部分）：
```cpp
void Cut(int p,ll x1,ll y1,ll x2,ll y2,int cmd){
	ll k1,k2;
	if(!cmd){//x轴切割
		k1=max(x1,a[p].x1);
		k2=min(x2,a[p].x2);
		if(a[p].x1<k1)Add(a[p].x1,a[p].y1,k1,a[p].y2);
		if(k2<a[p].x2)Add(k2,a[p].y1,a[p].x2,a[p].y2);
		Cut(p,k1,y1,k2,y2,1);
	}
	else{//y轴切割
		k1=max(y1,a[p].y1);
		k2=min(y2,a[p].y2);
		if(a[p].y1<k1)Add(x1,a[p].y1,x2,k1);
		if(k2<a[p].y2)Add(x1,k2,x2,a[p].y2);
	}
}
```
核心思想：用当前矩形(x1,y1,x2,y2)切割集合内矩形a[p]，先在x轴方向找交点k1,k2，生成新矩形，再递归到y轴方向切割。

最优关键思路或技巧：扫描线算法结合离散化和线段树能高效解决此类问题，离散化减少数据规模，线段树维护区间信息。矩形切割思想直观，通过不断切割避免重复覆盖。

可拓展之处：此类算法可用于计算多边形面积并、交等几何问题，以及一些涉及区域统计的场景。

推荐题目：
- P1496 [USACO08MAR] Land Acquisition G
- P1856 [USACO12FEB] Large Square G
- P2774 方格取数问题

---
处理用时：29.47秒