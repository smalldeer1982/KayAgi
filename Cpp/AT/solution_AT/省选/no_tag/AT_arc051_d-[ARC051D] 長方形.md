# [ARC051D] 長方形

## 题目描述

给定一个长度为 $W$ 的数列 $a_1, a_2, \ldots, a_W$ 和一个长度为 $H$ 的数列 $b_1, b_2, \ldots, b_H$。

现在，我们构造一个 $W \times H$ 的矩阵。矩阵中第 $i$ 列第 $j$ 行的格子的值为 $a_i + b_j$。

接下来有 $Q$ 个查询，每个查询要求如下：

- 给定两个参数 $A$ 和 $B$，请在左上角 $A$ 列以内和 $B$ 行以内的所有格子中选择一些格子，要求这些格子组成一个矩形，并求出这些格子的值之和的最大值。注意，至少需要选择一个格子。

## 样例 #1

### 输入

```
2 2
0 10
0 -1
4
1 1
1 2
2 1
2 2```

### 输出

```
0
0
10
19```

## 样例 #2

### 输入

```
3 3
1 10 100
1000 10000 100000
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3```

### 输出

```
1001
11002
111003
2011
22022
222033
3111
33222
333333```

## 样例 #3

### 输入

```
10 8
2 -4 0 0 -1 4 5 0 -3 0
2 0 0 -3 -5 -5 -4 -4
10
2 6
1 4
1 2
5 7
1 5
7 6
7 4
1 5
3 5
10 7```

### 输出

```
8
8
6
8
8
34
34
8
8
36```

# 题解

## 作者：skylee (赞：2)

# [ARC051D]長方形
## 题目大意：
给定$A_{1\sim n}$和$B_{1\sim m}(n,m\le2000,|A_i|,|B_i|\le10^5)$，矩阵$C_{i,j}=A_i+B_j$。$q(q\le2000)$次询问，求坐标不超过$(x,y)$的最大权值子矩阵的权值。

## 思路：
用$maxa[i][j]$表示$A_{1\sim i}$中长度为$j$的最大连续子段和，$maxb$同理。

对于询问$(x,y)$，答案即为$\max\{maxa[x][i]\times j+maxb[y][j]\times i\mid i\le x,j\le y\}$。

$\max$内变形后即为$j\times(maxa[x][i]+\frac{maxb[y][j]\times i}j)$。括号内的东西可以看作是关于$\frac{maxb[y][j]}j$的一次函数，使用李超树维护凸壳即可。

时间复杂度$\mathcal O(qn\log n)$。

## 源代码：
```cpp
#include<cmath>
#include<cstdio>
#include<cctype>
#include<climits>
#include<algorithm>
inline int getint() {
	register char ch;
	register bool neg=false;
	while(!isdigit(ch=getchar())) neg|=ch=='-';
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return neg?-x:x;
}
typedef long long int64;
const int N=2001,LIM=1e5,SIZE=(LIM<<1|1)<<2;
int a[N],b[N],maxa[N][N],maxb[N][N];
class SegmentTree {
	#define _left <<1
	#define _right <<1|1
	#define mid ((b+e)>>1)
	private:
		struct Node {
			int a,b,tim;
		};
		Node node[SIZE];
	public:
		void insert(const int &p,const int &b,const int &e,int i,int j,const int &t) {
			if(node[p].tim<t) {
				node[p].a=i;
				node[p].b=j;
				node[p].tim=t;
				return;
			}
			int64 lval1=1ll*node[p].a*b+node[p].b;
			int64 rval1=1ll*node[p].a*e+node[p].b;
			int64 lval2=1ll*i*b+j,rval2=1ll*i*e+j;
			if(lval1<lval2) {
				std::swap(lval1,lval2);
				std::swap(rval1,rval2);
				std::swap(node[p].a,i);
				std::swap(node[p].b,j);
			}
			if(rval1>=rval2||b==e) return;
			const double c=1.*(j-node[p].b)/(node[p].a-i);
			if(c<=mid) {
				insert(p _left,b,mid,node[p].a,node[p].b,t);
				node[p].a=i;
				node[p].b=j;
			} else {
				insert(p _right,mid+1,e,i,j,t);
			}
		}
		double query(const int &p,const int &b,const int &e,const double &x,const int &t) const {
			if(node[p].tim<t) return -1e15;
			double ret=node[p].a*x+node[p].b;
			if(b==e) return ret;
			if(x<=mid) ret=std::max(ret,query(p _left,b,mid,x,t));
			if(x>mid) ret=std::max(ret,query(p _right,mid+1,e,x,t));
			return ret;
		}
	#undef _left
	#undef _right
	#undef mid
};
SegmentTree t;
int main() {
	const int n=getint(),m=getint();
	for(register int i=1;i<=n;i++) {
		maxa[i][i]=a[i]=a[i-1]+getint();
		for(register int j=1;j<i;j++) {
			maxa[i][j]=std::max(maxa[i-1][j],a[i]-a[i-j]);
		}
	}
	for(register int i=1;i<=m;i++) {
		maxb[i][i]=b[i]=b[i-1]+getint();
		for(register int j=1;j<i;j++) {
			maxb[i][j]=std::max(maxb[i-1][j],b[i]-b[i-j]);
		}
	}
	const int q=getint();
	for(register int p=1;p<=q;p++) {
		const int x=getint(),y=getint();
		for(register int i=1;i<=x;i++) {
			t.insert(1,-LIM,LIM,i,maxa[x][i],p);
		}
		int64 ans=LLONG_MIN;
		for(register int i=1;i<=y;i++) {
			ans=std::max(ans,llround(t.query(1,-LIM,LIM,1.*maxb[y][i]/i,p)*i));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

