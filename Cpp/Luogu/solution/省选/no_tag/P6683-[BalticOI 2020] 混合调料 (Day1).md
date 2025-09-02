# [BalticOI 2020] 混合调料 (Day1)

## 题目描述

著名餐厅 *Salt, Pepper & Garlic* 的主厨 Serge 准备好成为一名米其林一星厨师。他已被告知，今晚一位秘密评审员将光临他的餐厅。

虽然他并没有得知这位评审员的姓名，但他已经得知了这位评审员将要点的菜和他的口味偏好。具体来说，这位评审员希望在菜肴中加入非常精确比例的盐，胡椒粉和大蒜粉。

Serge 在厨房的一个架子上放了若干盐，胡椒粉和大蒜粉的混合调料瓶。对于每种调料瓶，Serge 都知道该调料瓶中混合的盐，胡椒粉和大蒜粉的量（单位为千克），他可以通过将任意多瓶调料混合起来（当然也可以单独使用一瓶调料），得到所需比例的调料。

事实上菜肴里放的调料量并不多，因此可以认为调料的量是足够的。但是，评审员要求的盐，胡椒粉和大蒜粉的量之比中的数字可能非常大。

现在 Serge 想要求出，是否能够利用已有的调料瓶配制出满足评审员要求比例的调料？如果能够配制，最少需用多少个瓶子？

此外，Serge 可能会拿到新的调料瓶，或者将架子上已有的调料瓶给其他厨师，这意味着架子上的瓶子种类会不断发生改变，Serge 希望在每次架子上的调料瓶发生变化后，再解决上面的问题。

举个例子，假如评审员要求的盐，胡椒粉和大蒜粉的量的比例为 $1:1:1$，架子上有以下几种调料瓶：

| 调料瓶编号 |  盐  | 胡椒粉 | 大蒜粉 |
| :--------: | :--: | :----: | :----: |
|     1      |  10  |   20   |   30   |
|     2      | 300  |  200   |  100   |
|     3      |  12  |   15   |   27   |

则只需将瓶子 $1$ 中的全部调料，和瓶子 $2$ 中的 $60$ 千克调料（其中包括盐 $30$ 千克，胡椒粉 $20$ 千克，大蒜粉 $10$ 千克）混合即可满足要求。一旦取走瓶子 $2$，则无法满足评审员的要求。

## 说明/提示

所有数据均满足：$1 \leq N \leq 10^5$，$S_f,P_f,G_f \geq 0$，$0 \lt S_f+P_f+G_f \leq 10^6$，$S_i,P_i,G_i \geq 0$，$0 \lt S_i+P_i+G_i \leq 10^6$。

- 子任务 1（13 分）：$N \leq 50$，$0 \lt S_i+P_i+G_i \leq 10^2$；
- 子任务 2（17 分）：$N \leq 500$，$0 \lt S_i+P_i+G_i \leq 10^3$；
- 子任务 3（30 分）：$N \leq 5000$，$0 \lt S_i+P_i+G_i \leq 10^4$；
- 子任务 4（40 分）：无特殊限制。

## 样例 #1

### 输入

```
1 2 3
6
A 5 6 7
A 3 10 17
R 1
A 15 18 21
A 5 10 15
R 3
```

### 输出

```
0
2
0
2
1
1
```

# 题解

## 作者：7KByte (赞：1)

几何 + DS神题。

开始看非常没有思路，但是根据样例我们可以猜到答案一定很小，事实上答案 $\le 3$。

我们不妨先考虑二维的情况，如果我们只有两种调料如何处理。

我们用二元组 $(P,Q)$ 描述一个瓶子，不难发现我们只关心这个比值 $\frac{P}{Q}$ 。而最终我们需要调出的也只需要一个比值。

那么这个比值可以看成数轴上的一个点，显然两个瓶子对应两个点 $A,B$，我们可以调出线段 $AB$ 上对应的任意比值。感性理解一下，如果只用一个瓶子，就是线段端点，再加入另一个瓶子能使得比例偏移。

那么对于三元组 $(X,Y,Z)$ ，我们也只关心比值 $(\dfrac{X}{X+Y+Z},\dfrac{Y}{X+Y+Z})$，现在我们一个瓶子看成平面直角坐标系中的一个点。

那么对于两个瓶子，显然只能调出对应两点线段上的比值。

现在加入第三个瓶子，也就是在这条线段取一个点，再与第三个点连线。不难发现这条连线是动态的，且扫过的面积恰好是以三个点为顶点三角形。

归纳一下，对于 $N$ 个点，可以取到的比值就是 $N$ 点对应凸包里面的比值。

因此答案 $\le 3$。

如果有瓶子与初始点重合，那么答案为 $1$。

如果有两个瓶子的连线经过初始点，那么答案为 $2$。

如果初始点在凸包中，那么答案为 $3$ 。

否则答案为 $0$。

但是朴素维护凸包和连线，和朴素的 $\mathcal{O}(N^4)$ ，没有什么区别。

由于我们只关心瓶子与初始点的位置，所以我们以初始点为端点进行极角排序。

那么经过初始点的连线，意味着存在两个角相差为 $\pi$。

如果初始点在凸包中，意味着大小相邻的两个角相差 $\le \pi$。

我们直接用平衡树维护角度即可，注意精度问题。时间复杂度 $\mathcal{O}(N\log N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int a[N], b[N], c[N], idx, n, s0, s1, s2;
typedef long double db;
db st, ed;
const db pi = acos(-1.0), eps = 1e-15;
struct cmp{bool operator ()(const db &x, const db &y)const{return x + eps < y;}};
multiset<db, cmp>s;
db calc(db x, db y){
	db cur = atan2(x, y);
	if(cur < 0)cur += pi + pi;
	return cur;
}
inline db rev(db ang){
	if(ang > pi)return ang - pi;
	return ang + pi;
}
void ins(int i){
	int sum = a[i] + b[i] + c[i];
	db x = (db)a[i] / sum, y = (db)b[i] / sum;
	if(fabs(x - st) <= eps && fabs(y - ed) <= eps)s0++;
	else {
		db ang = calc(x - st, y - ed);
		if(s.find(ang) == s.end() && s.find(rev(ang)) != s.end())s1++;
		s.insert(ang); 
	}
}
void del(int i){
	int sum = a[i] + b[i] + c[i];
	db x = (db)a[i] / sum, y = (db)b[i] / sum;
	if(fabs(x - st) <= eps && fabs(y - ed) <= eps)s0--;
	else {
		db ang = calc(x - st, y - ed);
		s.erase(s.find(ang));
		if(s.find(ang) == s.end() && s.find(rev(ang)) != s.end())s1--; 
	}
}
int main(){
	scanf("%d%d%d", &a[0], &b[0], &c[0]);
	st = (db)a[0] / (a[0] + b[0] + c[0]), ed = (db)b[0] / (a[0] + b[0] + c[0]);
	scanf("%d", &n);
	char op[2];int x;
	rep(i, 1, n){
		scanf("%s", op);
		if('A' == *op)++idx, scanf("%d%d%d", &a[idx], &b[idx], &c[idx]), ins(idx);
		else scanf("%d", &x), del(x);
		if(s0)puts("1");else if(s1)puts("2");else if(s.size() < 3)puts("0");
		else if((*s.rbegin() - *s.begin()) < pi)puts("0");
		else if((*s.lower_bound(pi) - *(--s.upper_bound(pi))) > pi)puts("0");
		else puts("3");
	}
	return 0;
}
```



---

