# Plane Tiling

## 题目描述

你有五个整数$n,dx_1,dy_1,dx_2,dy_2$。你必须选择$n$个**互不相同**的整数对$(x_i, y_i)$。对于所有可能的整数对$(x, y)$，存在**恰好**一个整数的三元组，$(a, b, i)$符合以下条件：

$$\begin{cases} x \, = \, x_i + a \cdot dx_1 + b \cdot dx_2 \\ y \, = \, y_i + a \cdot dy_1 + b \cdot dy_2 \end{cases}$$

## 样例 #1

### 输入

```
4
2 0
0 2```

### 输出

```
YES
0 0
0 1
1 0
1 1```

## 样例 #2

### 输入

```
5
2 6
1 5```

### 输出

```
NO```

## 样例 #3

### 输入

```
2
3 4
1 2```

### 输出

```
YES
0 0
0 1```

# 题解

## 作者：skyskyCCC (赞：2)

## 前言。
本题的第一篇题解！

用到了数论几何，构造与计算几何。较为复杂的一道题。

第一次修改于 $2023$ 年 $11$ 月 $27$ 日：补充代码。

题意简述：  
给定一个 $n$ 和两个向量 $\vec{v_1}=\left(dx_1,dy_1\right)$ 和 $\vec{v_2}=\left(dx_2,dy_2\right)$ 然后在平面内找出 $n$ 个不相同的点。使平面上任意一个点 $\left(x,y\right)$ 恰好有一个 $\left(x_i,y_i\right)$ 满足 $\left(x,y\right)=\left(x_i,y_i\right)+\vec{v_1}+\vec{v_2}$ 的要求。如果存着输出 ```YES``` 并输出点的坐标，否则输出 ```NO``` 结束程序。
## 分析。
参考官方题解，虽然很难理解。

- 方法 $1$ 来自综合理解。

考虑有一个无限的 $2$ 维平面，并用平行于向量 $\vec{v_1}$ 和 $\vec{v_2}$ 的线绘制一个网格，我们令它为基准平行四边形。

如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/f2u9zasr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

明显这是一个平面的平铺的一坨平行四边形，其中一个平行四边形的角，即我们作为基准点的那个平行四边形的顶点，分别位于 $\left(0,0\right),\left(dx_1,dy_1\right),\left( dx_1+dx_2,dy_1+dy_2\right),\left(dx_2,dy_2\right)$ 这个可以通过向量的加法法则求出。同理，所有的平行四边形都是相同的形状，可以通过向量 $\left(a\times dx_1+b\times dx_2,a\times dy_1+b\times dy_2\right)$ 平移其中一个来表示。其中 $a$ 和 $b$ 是所有可能的整数对。

此时我们发现根据皮克定理 $S=n+\frac{s}{2}-1$ 容易发现这些点的数量就是平行四边形的面积，这样是否存在解就可以直接判断了。所以平面几何就可以做了。问题再于，这样做会导致在计算过程中遇见不等情况，会造成精度缺失。考虑另外想一个方法，我们发现每个平行四边形内部和边上的**整点**都可以由相邻平行四边形**相同位置**的点到达，即平移，且这些点相互不可达，所以只要将基准平行四边形内部和边上的整点作为要找到的点。但是注意到这些点只包括左边和下边，不包括上边和右边，因为上边和右边的点可以由左边和下边的点通过平移到达，那我们就不用找了因为直接自己找到自己了。如果这些点的个数等于 $n$ 个，则有解，否则无解。

这样我们就将这个数论题转化为几何题了，代码复杂度为 $O\left(n\right)$ 足以通过本题。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
const double eps=1e-9;

//定义一个点。
struct node{
	double x,y;
	node(double x=0,double y=0):x(x),y(y){}
};

//判断符号的函数。
int sig(double x){
	if(fabs(x)<eps){
        return 0;
    }//负数判断，注意浮点。
	else if(x>0){
        return 1;
    }//正数判断。
	else return -1;//特判0的情况。
}

//浮点数的比较函数。
int exch(double x,double y){
	if(fabs(x-y)<eps){
        return 0;
    }
	else if(x>y){
        return 1;
    }//这个的思想就是绝对值。
	else return -1;
}

//定义一个向量。
typedef node vvector;
//向量的加法。 
vvector operator+(vvector a,vvector b){
	return vvector(a.x+b.x,a.y+b.y);
}
//向量的减
vvector operator-(vvector a,vvector b){
	return vvector(a.x-b.x,a.y-b.y);
}
//向量的数乘。
vvector operator*(vvector a,double p){
	return vvector(a.x*p,a.y*p);
}
vvector operator/(vvector a,double p){
	return vvector(a.x/p,a.y/p);
}
//两个点判等。
bool operator==(const node &a,const node &b){
	if(exch(a.x,b.x)==0&&exch(a.y,b.y)==0){
        return true;
    }
	else return false;
}
//点积。
double dianji(vvector a,vvector b){
	return a.x*b.x+a.y*b.y;
}
//叉积。
double chaji(vvector a,vvector b){
	return a.x*b.y-a.y*b.x;
}
double Mo(vvector a){
	return sqrt(dianji(a,a));
}

//判断直线和线段是否相交
bool cheak(node P,vvector v,node a,node b){
	double fi=chaji(v,a-P);
    double se=chaji(v,b-P);
	if(!sig(fi)||!sig(se)){
		if(!sig(fi)&&!sig(se)){
			return false;
		}
		else return true;
	}
	else return sig(fi)*sig(se)<0;
}

//计算两直线的交点(P+tv,Q+tw)。
//注意在在调用前要保证两直线相交，否则不存在交点。
node point_two(node point,vvector tv,node point_other,vvector tw){
	vvector tot=point-point_other;
	double cut=chaji(tw,tot)/chaji(tv,tw);
	return point+tv*cut;
}

int n,dx1,dy1,dx2,dy2;
vector<pair<int,int> > ans;
node p1,p2,p3,p4,p5;
vvector v,v1,v2;
node sum1,sum2;
int ksum_1,ksum_2,du1,du2;

int main(){
	cin>>n>>dx1>>dy1>>dx2>>dy2;
	if(dx1<0){dx1*=-1;dy1*=-1;}
	if(dx2<0){dx2*=-1;dy2*=-1;}
    //处理负数的情况。
	if((dx1==0&&dy1==0)||(dx2==0&&dy2==0)||(dx1==dx2&&dy1==dy2)){
		cout<<"NO\n";
        //cout<<"yep!\n";
		return 0;
	}//判断无解情况。
    p1=node(dx1,dy1);
    p2=node(dx2,dy2);
    p3=node(0,0);
    p4=node(dx1+dx2,dy1+dy2);
    v=vvector(0,1);
    v1=vvector(dx1,dy1);
    v2=vvector(dx2,dy2);
	int flag=1;
	for(int i=0;i<=dx1+dx2-1;i++){
		if(i==dx1+dx2){
            continue;
        }
		p5=node(i,0);
		if(cheak(p5,v,p1,p4)){
			sum1=point_two(p5,v,p1,v2);
			ksum_1=0;
		}
		else{
			sum1=point_two(p5,v,p3,v1);
			ksum_1=1;
            //注意不要打错变量名，比如我这里之前打成了ksum_1调了10分钟。
		}
		if(cheak(p5,v,p2,p4)){
			sum2=point_two(p5,v,p2,v1);
			ksum_2=0;
		}
		else{
			sum2=point_two(p5,v,p3,v2);
			ksum_2=1;
		}
		if(exch(sum1.y,sum2.y)>0){
			swap(sum1,sum2);
			swap(ksum_1,ksum_2);
        }
        //进入复杂区，注意细节。
		if(ksum_1==1){
			if(sig(sum1.y-round(sum1.y))==0){
				du1=round(sum1.y);
			}
			else{
				if(sig(sum1.y)<0){
					du1=(int)sum1.y;
				}
				else{
					du1=(int)sum1.y+1;
				}
			}
		}
		else{
			if(sig(sum1.y-round(sum1.y))==0){
				du1=round(sum1.y)+1;
			}
			else{
				if(sig(sum1.y)<0){
					du1=(int)sum1.y;
				}
				else{
					du1=(int)sum1.y+1;
				}
			}
		}
		if(ksum_2==1){
			if(sig(sum2.y-round(sum2.y))==0){
				du2=round(sum2.y);
			}
			else{
				if(sig(sum2.y)<0){
					du2=(int)sum2.y-1;
				}
				else{
					du2=(int)sum2.y;
				}
			}
		}
		else{
			if(sig(sum2.y-round(sum2.y))==0){
				du2=round(sum2.y)-1;
			}
			else{
				if(sig(sum2.y)<0){
					du2=(int)sum2.y-1;
				}
				else{
					du2=(int)sum2.y;
				}
			}
		}
        //cout<<du1<<" "<<du2<<"\n";
		for(int j=du1;j<=du2;j++){
			ans.push_back(make_pair(i,j));
			if((int)(ans.size())>n){
				flag=0;
				break;
			}
		}
		if(!flag){
            break;
        }
	}
	if((int)(ans.size())!=n){
		cout<<"NO\n";
	}
	else{
		cout<<"YES\n";
		for(auto count:ans){
            cout<<count.first<<" "<<count.second<<"\n";
		}
	}
	return 0;
}
```
考虑到这道题应该也有用数学方法做的，所以补充一些数学证明。
- 方法 $2$ 来自官方题解。

首先，我们计算 $d$ 的绝对值：

$d=\left| \det\left(\left(dx_1,dy_1\right),\left(dx_2,dy_2\right)\right)\right|=\left|dx_1\times dy_2-dx_2\times dy_1\right|$

其中 $\det(X)$ 表示行列式 $X$ 的标量。

所以如果 $n\neq d$ 则无解，特别的，如果 $d=0$ 没有所需的 $n$ 对整数。现在我们让 $n=d$ 并且 $d_x=\gcd\left(dx_1,dx_2\right)$ 和 $d_y=\gcd\left(dy_1,dy_2\right)$。我们用 $d_x$ 除以 $dx_1$ 和 $dx_2$ 然后用 $d_y$ 除以 $dy_1$ 和 $dy_2$。

定义 $m=n\div(d_x \times d_y)$ 并且规定 $n=d$ 故它能被 $d_x\times d_y$ 整除。因此，我们首先需要找到 $m$ 点 $\left(x_i,y_i\right)$ 使得所有值 $\left(x_i+a \times dx_1+b \times dx_2,y_i+a \times dy_1+b\times dy_2\right)$ 都不同。显然这对于求解来说已经足够了，因为我们仍然有 $m$ 等于新矩阵行列式的绝对值。

显然可以选择点 $\left(0,0\right),\left(0,1\right), \ldots,\left(0,m-1\right)$ 即 $x_i=i$ 且 $y_i=0$。

如何证明这样的选择是正确的呢？

假设对于某些非零对 $\left(a,b\right)$ 和某些 $j$ 中，我们有其中一个点为 $x_i=x_j+a\times dx_1+b\times dx_2$ 和 $y_i=y_j+a\times dy_1+b\times dy_2$。考虑到当 $y_i=y_j=0$ 时，我们有 $a \times dy_1+b\times dy_2=0$ 。因为我们已将其除以 $d_y$ 所以 $dy_1$ 和 $dy_2$ 是素数，所以对于某个整数 $k$ 有 $a = k \times dy_2$ 且 $b = -k\times dy_1$。如果我们用它来计算 $x$ 等式，容易得到：

$x_i - x_j=k \times dy_2 \times dx_1 - k \times dy_1 \times dx_2$ 即 $x_i - x_j=k \times (dx_1 \times dy_2 - dx_2 \times dy1)=\pm k \times m$。

因为 $-m < x_i-x_j < m$ 所以这个方程对于整数的非零的 $k$ 没有解。因此这组点是正确的。

显然，我们需要将当前答案坐标乘以 $d_x$ 和 $d_y$ 然后，对于这些点中的每一个 $0 \leq r_x < d_x$ 和每一个 $0 \leq r_y < d_y$ 都是一个新答案。因此，每个 $0 \leq i < m$ 且 $0 \leq r_x < d_x$ 且 $0 \leq r_y < d_y$ 的答案都是 $\left(i\times d_x+r_x,r_y\right)$。

或者说，我们回到开头的那个图。观察它们与一侧顶点的距离，显然可以表示成 $a\times dx_1+b\times dx_2$ 或是 $a\times dy_1+b\times dy_2$ 并且是依次变化的。如果我们考虑将每种距离都取到**恰好**一次，就恰好拼成了一个平行四边形，也就找出了解。所以根据裴蜀定理，只要将初始的一个点增加至 $\gcd\left(dx_1,dx_2\right)$ 或者 $\gcd\left(dy_1,dy_2\right)$ 个点即可。

也就是说任意一个边长为上面这两个终点的矩形中的点都可为解。代码现在有了。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,dx1,dy1,dx2,dy2;
int main(){
    cin>>n>>dx1>>dy1>>dx2>>dy2;
	long long d=1ll*dx1*dy2-1ll*dx2*dy1,l=__gcd(dx1,dx2);
	if(d<0){
		d=-d;
	}
	if(l<0){
		l=-l;
	}
	if(n!=d){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	for (int i=1;i<=l;i++){
		for (int j=1;j<=d/l;j++){
			cout<<i<<" "<<j<<"\n";
		}
	}
	return 0;
}
```
## 后记。
很有意思也很烧脑的题。如果不相信写错了一个变量，调个半小时都是家常便饭。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：紊莫 (赞：1)

标签：数学

首先考虑 $a \times dx_1 + b \times dx_2 = x$ 固定的情况。

那么可以得到所有可行的 $a, b$，记 $G = \gcd (dx_1, dx_2)$：

$$\left\{\begin{matrix}
a = a_0 + t\dfrac{dx_2}{G} 
 \\
b = b_0 - t\dfrac{dx_1}{G}
\end{matrix}\right.$$

带入到另一个式子里可以得到：

$$(a_0 + t\dfrac{dx_2}{G})dy_1 + (b_0 - t\dfrac{dx_1}{G})dy_2$$

那么发现 $t$ 的系数是 $C = \dfrac{\left | dx_2dy_1-dx_1dy_2 \right | }{G}$，也就是我们得到了 $x$ 固定的时候 $y$ 的步长。

那么 $x$ 的步长是显然的，为 $G$。

那么要不重不漏，也就是要恰好有 $CG$ 个数字填补空缺。

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 200005, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, dx1, dx2, dy1, dy2;
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> dx1 >> dy1 >> dx2 >> dy2;
    int G = gcd(dx1, dx2);
    if (!G) cout << "NO", exit(0);
    int C = abs(dx2 * dy1 - dx1 * dy2) / G;
    if (G * C != n) cout << "NO", exit(0);
    cout << "YES\n";
    F(i, 0, G - 1) F(j, 0, C - 1) cout << i << ' ' << j << '\n';
    return 0;
}

```

---

