# Guard Duty (easy)

## 题目描述

The Rebel fleet is afraid that the Empire might want to strike back again. Princess Heidi needs to know if it is possible to assign $ R $ Rebel spaceships to guard $ B $ bases so that every base has exactly one guardian and each spaceship has exactly one assigned base (in other words, the assignment is a perfect matching). Since she knows how reckless her pilots are, she wants to be sure that any two (straight) paths – from a base to its assigned spaceship – do not intersect in the galaxy plane (that is, in 2D), and so there is no risk of collision.

## 说明/提示

For the first example, one possible way is to connect the Rebels and bases in order.

For the second example, there is no perfect matching between Rebels and bases.

## 样例 #1

### 输入

```
3 3
0 0
2 0
3 1
-2 1
0 3
2 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 1
1 0
2 2
3 1
```

### 输出

```
No
```

# 题解

## 作者：Pursuing_OIer (赞：7)

### Meaning
在二维平面内，有位置不同且不存在三点共线的 $R$ 个红点和 $B$ 个黑点，判断是否能用一些互不相交的线段连接每一个点，使得每条线段的两端都分别是黑点和白点。  

### Solution 

当 $R\ne{B}$ 时，显然无法实现红点与黑点的两两组合，故题干所述的情况一定不存在。  
当 $R=B$ 时，我们考虑一种连线的方式（事先给所有红点带上 $1$ 的权值，给所有黑点带上 $-1$ 的权值）：先找到纵坐标最小的一列点，以其中任意一个点作为坐标原点重新构建平面直角坐标系。接下来，以这个坐标原点为顶点，向 $y$ 轴正方向做一条射线。然后，将射线上除端点外所有点的权值累加起来，并将该射线绕着端点顺时针旋转，直到该射线过平面中其他的点。重复此操作并累加权值，直到累加值与端点的权值之和为 $0$。  
由于射线最后扫过的点可以为累加值做出与端点相反的贡献，使得累加值为端点权值的相反数，故最后扫过的点一定与端点异色。而由于保证任意三点不共线，可以在这个点与端点之间连一条符合题意的线段。而且，由于顶点权值与累加值之和为 $0$，所以这条线段上方、下方的红点与黑点的个数均分别相等。将线段上方、下方的两部分取出，重复上述的操作，直到某一部分只剩下一个红点和一个黑点。由于在这几个部分独立且均满足 $R=B$，所以这一组操作可以完成，且没有任何两条线段相交。  
综上所述，当 $R=B$ 时，题干所述的情况一定存在。  
  
下面，我们利用样例 $1$ 来演示一下上述过程。  

![](https://cdn.luogu.com.cn/upload/image_hosting/ip3gz7dh.png)  

如图，我们找到点 $D$ 并进行扫描。  

1. 射线 $DE$，累加值 $-1$，端点权值 $-1$，扫描继续。  
2. 射线 $DF$，累加值 $-2$，端点权值 $-1$，扫描继续。  
3. 射线 $DC$，累加值 $-1$，端点权值 $-1$，扫描继续。  
4. 射线 $DB$，累加值 $0$，端点权值 $-1$，扫描继续。  
5. 射线 $DA$，累加值 $1$，端点权值 $-1$，扫描结束。  

因此，我们连接 $DA$。  

![](https://cdn.luogu.com.cn/upload/image_hosting/g4i9ztls.png)

由于没有下半部分，只考虑上半部分。找到新的坐标原点为点 $E$。经过扫描，连接 $EB$。  

![](https://cdn.luogu.com.cn/upload/image_hosting/9wipj2fp.png)  

此时只剩下红点 $C$ 和黑点 $F$，故存在题干所述的情况。    

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int b,r,x,y;
	scanf("%d%d",&r,&b);
	for(int i=1;i<=r;++i){
		scanf("%d%d",&x,&y);
	}
	for(int i=1;i<=b;++i){
		scanf("%d%d",&x,&y);
	}
	if(b==r)
	printf("Yes");
	else
	printf("NO");
}
```

---

## 作者：npqenqpve (赞：4)

### 题意：
在二维平面中给出 $R$ 个点和 $B$ 个点，要将 $R_i$ 与 $B_j$ 连一条线段，问是否存在方案使得线段两两不相交。

### 思路：
如果 $R \neq B$ 时，显然不存在方案，因为必然两个线段是共端点的；

如果 $R=B$，此时是否一定存在是一个值得思考的问题，不妨从小问题开始考虑，共四个点， $A$ 、 $B$ 两点与 $C$ 、 $D$ 两点两两相连，如果线段 $AC$ 与线段 $BD$ 相交，那么可以改变主意，连接 $AD$，$BC$，必然不相交，以此类推， $R=B$ 时必然存在方案。

---

## 作者：cff_0102 (赞：2)

显然当 $R\ne B$ 时不能成功一一配对（个数都不一样怎么配对？）。

接下来需要证明：当 $R=B$ 时，所有连线的线段长度之和最小的配对方案必然不会产生交点。

假设现在采用的是所有连线线段长度之和最小的一种方案，但是 $R_1B_1$ 和 $R_2B_2$ 这两条线段产生了交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/h8drsbuh.png)

设交点为 $O$，并连接 $R_1B_2,R_2B_1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ru3pii9m.png)

因为先前假设的是 $R_1B_1,R_2B_2$ 这种方案是线段长度之和最小的，所以理应 $R_1B_1+R_2B_2\le R_1B_2+R_2B_1$。但是因为 $R_2,B_1,O$ 组成一个三角形（题目保证不存在三点共线，那么 $R_2,B_1,B_2$ 不可能共线，所以 $R_2,B_1,O$ 一定能组成三角形），而三角形两边之和大于第三边，所以 $R_2O+OB_1>R_2B_1$，同理 $R_1O+OB_2>R_1B_2$，可以得出 $R_1B_2+R_2B_1<R_1B_1+R_2B_2$，这与之前“$R_1B_1,R_2B_2$ 这种方案是线段长度之和最小的”的假设矛盾。

因此，不存在“所有连线线段长度之和最小的一种方案能够让两条线段连线产生交点”的情况，就可以推出“所有连线线段长度之和最小的一种方案一定不会让两条线段连线产生交点”，那么当 $R=B$ 时就一定有解。

综上所述，只需要判断 $R$ 是否等于 $B$，就能知道是否有解了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int r,b;cin>>r>>b;
	if(r==b)cout<<"Yes";
	else cout<<"NO";
}
```

---

## 作者：GOD_hj (赞：2)

## 题意
在一个二维平面内，有 $R$ 个黑点，$B$ 个白点。要将黑点和白点之间连一条线段，问是否存在方案使得线段两两不相交。

## 思路
进行分类讨论。

当 $B \neq R$ 时，此时肯定有两个线段共端点的。

如图，白点 $2$ 会和黑点 $2$ 和 $3$ 分别连线，出现共端点。

![](https://cdn.luogu.com.cn/upload/image_hosting/u53pvnys.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当 $B = R$ 时，肯定有一种情况符合题意。

我们可知：线段长度之和最小的分配不会有任何交叉点。

我们可以用反证法证明：

因为没有三点共线和两点重合的情况，所以假设存在相交的线段 $AB$，$CD$，其中 $A$ 和 $C$ 是飞船，$B$，$D$ 是基地。

如果我们改变赋值到 $AD$ 和 $BC$，由于三角形不等式(两边之和大于第三边，两边之差小于第三边)，段长之和将减少，且其段长之和小于最小值，矛盾。

因此，只要黑点和白点的数量相同，就一定能保证所有的线段都不相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/y7ozqm2t.png)


---

## 作者：xxxr_2024 (赞：2)

# CF958E1 Guard Duty (easy) 题解
## 题意
给你两类点（飞船、基地），要求在两类点中间连线，线段必须一端是飞船一端是基地，给你这些点的坐标，问能不能构造出符合条件的线段不相交。

## 分析
结论题，分类讨论。

如果 $R$ 不等于 $B$ 显然会有至少两条线段拥有共同的端点，不符合条件，直接输出 `No`。

接下来讨论当 $R$ 等于 $B$ 时的情况。假设存在点 $A,B$ 是飞船，点 $C,D$ 是基地，线段 $AC,BD$ 相交。那么显然，一定会存在 $AD,BC$ 不相交。所以推广后，当 $R=B$ 时，直接输出 `Yes`。

## 代码（可有可无）
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    signed work()
    {
        int r,b;
        cin>>r>>b;
        cout<<(r==b?"Yes":"No")<<endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF958E1)

## 思路

一道水题。

当 $R\neq B$ 的时候，可以想象飞船和基地对应时一定会有至少一个飞船或基地连至少两个基地或飞船，如图。（图中字母代表基地，数字代表飞船。）此图中基地 $D$ 要和 $4$ 号、$5$ 号飞船分别连线，出现交点。
 
![](https://cdn.luogu.com.cn/upload/image_hosting/ybr8s9ot.png)

当 $R=B$ 的时候，一定能保证每个飞船和每个基地一一对应，不会出现相交的点，如图。（图中字母代表基地，数字代表飞船。）图中飞船基地间连线没有出现交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/z7a0qk3y.png)

代码只需判断 $R$ 是否等于 $B$，如果等于则输出 ``Yes``，不等于则输出 ``No`` 即可。

---

