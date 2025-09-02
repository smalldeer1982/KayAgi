# Building Bridge

## 题目描述

Two villages are separated by a river that flows from the north to the south. The villagers want to build a bridge across the river to make it easier to move across the villages.

The river banks can be assumed to be vertical straight lines $ x=a $ and $ x=b $ ( $ 0&lt;a&lt;b $ ).

The west village lies in a steppe at point $ O=(0,0) $ . There are $ n $ pathways leading from the village to the river, they end at points $ A_{i}=(a,y_{i}) $ . The villagers there are plain and simple, so their pathways are straight segments as well.

The east village has reserved and cunning people. Their village is in the forest on the east bank of the river, but its exact position is not clear. There are $ m $ twisted paths leading from this village to the river and ending at points $ B_{i}=(b,y'_{i}) $ . The lengths of all these paths are known, the length of the path that leads from the eastern village to point $ B_{i} $ , equals $ l_{i} $ .

The villagers want to choose exactly one point on the left bank of river $ A_{i} $ , exactly one point on the right bank $ B_{j} $ and connect them by a straight-line bridge so as to make the total distance between the villages (the sum of $ |OA_{i}|+|A_{i}B_{j}|+l_{j} $ , where $ |XY| $ is the Euclidean distance between points $ X $ and $ Y $ ) were minimum. The Euclidean distance between points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF250D/db1ba0d5909a3b47109b2e5f65fe13400ae1bd9a.png).

Help them and find the required pair of points.

## 样例 #1

### 输入

```
3 2 3 5
-2 -1 4
-1 2
7 3
```

### 输出

```
2 2```

# 题解

## 作者：mountain_climber (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF250D)

思路：

题目要求 $\min_{i=1}^{n}\min_{j=1}^{m}(|OA_i|+|A_iB_j|+l_j)$，数据范围为 $1\leq n,m\leq10^{5}$，容易想到把 $O(nm)$ 优化为 $O(n\log{m})$ 或 $O(m\log{n})$，问题也就变成了考虑枚举 $A$ 还是枚举 $B$，我们发现如果枚举 $B$ 的话，式子中的 $l_j$ 就一同被确定了，比较好考虑，所以我们选择枚举 $B$。

所以问题就变成了如何在可以接受的时间复杂度内对于一个 $B_j$ 找到能够使得 $|OA_i|+|A_iB_j|+l_j$ 最小的 $A_i$。然后容易发现 $f(x)=|OA_x|+|A_xB_j|+l_j$ 是一个单峰函数，直接用三分求其低谷（最小值）就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int inf=0x3f3f3f3f;
int n,m,a,b,yy2[N],l[N];
struct node1{
    int idx,yyy;
}yy1[N];
bool cmp(node1 n1,node1 n2){
    return n1.yyy<n2.yyy;
}
struct node{
    double x,y;
};
double dis(node n1,node n2){
    return sqrt((n1.x-n2.x)*(n1.x-n2.x)+(n1.y-n2.y)*(n1.y-n2.y));
}
double f(node n1,node n2,int ll){
    return dis({0,0},n1)+dis(n1,n2)+ll;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&a,&b);
    for(int i=1;i<=n;i++) scanf("%d",&yy1[i].yyy);
    for(int i=1;i<=n;i++) yy1[i].idx=i;
    sort(yy1+1,yy1+1+n,cmp);
    for(int i=1;i<=m;i++) scanf("%d",&yy2[i]);
    for(int i=1;i<=m;i++) scanf("%d",&l[i]);
    double minn=inf;
    int ansid1,ansid2;
    for(int i=1;i<=m;i++){
        double xx=b,yy=yy2[i];
        int tl=1,tr=n;
        while(tr-tl>2){
            int mid1=tl+(tr-tl)/3;
            int mid2=tr-(tr-tl)/3;
            node nn;
            nn.x=b,nn.y=yy2[i];
            node nn1={double(a),double(yy1[mid1].yyy)},nn2={double(a),double(yy1[mid2].yyy)};
            if(f(nn1,nn,l[i])<f(nn2,nn,l[i]))
                tr=mid2;
            else
                tl=mid1;
        }
        //printf("%d : %d %d \n",i,tr,tl);
        for(int j=tl;j<=tr;j++){
            node nn;
            nn.x=double(b),nn.y=double(yy2[i]);
            node nn1={double(a),double(yy1[j].yyy)};
            if(f(nn1,nn,l[i])<minn){
                minn=f(nn1,nn,l[i]);
                ansid1=yy1[j].idx;
                ansid2=i;
            }
        }
    }
    //printf("%d %d:%lf\n",ansid1,ansid2,minn);
    printf("%d %d\n",ansid1,ansid2);
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/162751323)

---

## 作者：Kazdale (赞：0)

做法：平面几何+二分

- ## 分析

	题面让我们求 $|OA_i|+|A_iB_j|+l_j$ 的最小值，考虑枚举两个点中的一个找出最优的另一个点的位置，因为 $l$ 的大小是无序的，难以找到最优的 $B$，所以枚举 $B$ 找最优的 $A$。
    
    所以现在我们要做的就是找到一个 $A$ 使得 $|OA|+|AB|$ 最小。
    
    我们设 $OB$ 交 $x=a$ 于点 $G$，那么有以下命题：
    
    当 $y_A > y_G$ 时，$|y_A-y_G|$ 越大，$|OA|+|AB|$ 越大。
    
    当 $y_A \leq y_G$ 时，$|y_A-y_G|$ 越大，$|OA|+|AB|$ 越大。
    
    如何证明？当 $y_A > y_G$ 时，有 $\triangle OAG$ 和 $\triangle BAG$，当 $y_A-y_G$ 增大时，边 $AG$也会增大，因为 $\angle OGA$ 和 $\angle BGA$ 不变，所以根据余弦定理，$|OA|$ 和 $|AB|$ 也会变大，所以对于 $y_A > y_G$ 的命题是正确的。
    
    同理可证，对于 $y_A \leq y_G$ 的命题也是正确的。
    
    根据此命题，我们分别找到大于 $y_G$ 的最小 $y_A$ 和小于等于 $y_G$ 的最大 $y_A$ 然后对两者的 $|OA|+|AB|$ 取 $\min$ 即可，我们可以先求出 $OB$ 的解析式进而求出点 $G$ 的坐标，然后二分求出大于 $y_G$ 的最小 $y_A$，那么若我们将 $y_A$ 序列升序排序，那么 $y_{A-1}$ 即为小于等于 $y_G$ 的最大 $y_A$。
    
    最后我们对每个 $B$ 所求出的 $|OA|+|AB|+l$ 值取 $\min$ 即可。
    
    时间复杂度 $\mathcal{O(m \log n + n \log n)}$，可以通过此题。
    
- ## 代码

```
#include <iostream>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
constexpr int MAXN(1000007);
long double l[MAXN];
int x[MAXN], y[MAXN];
int n, m, a, b, ans1, ans2;
long double minn(1000000000);
inline void read(int &temp) { cin >> temp; }
inline long double dis(int u, int v) {
	long double dx = (long double)x[u], dy = (long double)a;
	long double dis1 = sqrt(dx * dx + dy * dy);
	dx = (long double)(y[v] - x[u]), dy = (long double)(b - a);
	long double dis2 = sqrt(dx * dx + dy * dy);
	return dis1 + dis2;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m), read(a), read(b);
	for (int i(1); i <= n; ++i)  read(x[i]);
	for (int i(1); i <= m; ++i)  read(y[i]);
	for (int i(1); i <= m; ++i)  cin >> l[i];
	for (int i(1), col(0); i <= m; ++i) {
		int num = upper_bound(x + 1, x + n + 1, a * y[i] / b) - x;
		long double res(0);
		if (num <= 1)  res = dis(num, i), col = 1;
		if (num > n)  res = dis(num - 1, i), col = 2;
		if (num > 1 && num <= n && dis(num, i) <= dis(num - 1, i))  res = dis(num, i), col = 1;
		if (num > 1 && num <= n && dis(num - 1, i) <= dis(num, i))  res = dis(num - 1, i), col = 2;
		l[i] += res;
		if (l[i] < minn) {
			ans2 = i;
			if (col == 1)  ans1 = num;
			if (col == 2)  ans1 = num - 1;
			minn = l[i];
		}
	}
	cout << ans1 << " " << ans2 << endl;
	return 0;
}
```

---

