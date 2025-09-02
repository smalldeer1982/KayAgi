# [ABC047B] すぬけ君の塗り絵 2 イージー

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc047/tasks/abc047_b

$ xy $ 平面上に、左下の座標が $ (0,\ 0) $、右上の座標が $ (W,\ H) $ で、各辺が $ x $ 軸か $ y $ 軸に平行な長方形があります。最初、長方形の内部は白く塗られています。

すぬけ君はこの長方形の中に $ N $ 個の点を打ちました。$ i $ 個目 ($ 1\ ≦\ i\ ≦\ N $) 点の座標は $ (x_i,\ y_i) $ でした。

また、すぬけ君は長さ $ N $ の数列 $ a $ を決めて、各 $ 1\ ≦\ i\ ≦\ N $ に対し、

- $ a_i\ =\ 1 $ のときは長方形の $ x\ <\ x_i $ をみたす領域
- $ a_i\ =\ 2 $ のときは長方形の $ x\ >\ x_i $ をみたす領域
- $ a_i\ =\ 3 $ のときは長方形の $ y\ <\ y_i $ をみたす領域
- $ a_i\ =\ 4 $ のときは長方形の $ y\ >\ y_i $ をみたす領域

を黒く塗りました。

塗りつぶしが終わったあとの長方形内での白い部分の面積を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ W,\ H\ ≦\ 100 $
- $ 1\ ≦\ N\ ≦\ 100 $
- $ 0\ ≦\ x_i\ ≦\ W $ ($ 1\ ≦\ i\ ≦\ N $)
- $ 0\ ≦\ y_i\ ≦\ H $ ($ 1\ ≦\ i\ ≦\ N $)
- $ W $, $ H $ (21:32 追記), $ x_i $, $ y_i $ は整数である
- $ a_i $ ($ 1\ ≦\ i\ ≦\ N $) は $ 1,\ 2,\ 3,\ 4 $ のいずれかである

### Sample Explanation 1

すぬけ君が塗りつぶしを始める前の長方形は以下の図のようになっています。 !\[e19e673abcd0882783f635cce9d2f94d.png\](https://atcoder.jp/img/abc047/e19e673abcd0882783f635cce9d2f94d.png) $ (x_1,\ y_1)\ =\ (2,\ 1) $、$ a_1\ =\ 1 $ なので、まずすぬけ君は $ x $ 座標が $ 2 $ より小さい領域を塗りつぶし、長方形は以下のようになります。 !\[f25cd04bbac23c4e5426d70511a9762f.png\](https://atcoder.jp/img/abc047/f25cd04bbac23c4e5426d70511a9762f.png) $ (x_2,\ y_2)\ =\ (3,\ 3) $、$ a_2\ =\ 4 $ なので、次にすぬけ君は $ y $ 座標が $ 3 $ より大きい領域を塗りつぶし、長方形は最終的に以下のようになります。 !\[46b0c06fd9eee4f148e1f441f7abca53.png\](https://atcoder.jp/img/abc047/46b0c06fd9eee4f148e1f441f7abca53.png) この最終的な状態における白い部分の面積は $ 9 $ なので、出力は $ 9 $ となります。

### Sample Explanation 2

塗りつぶした結果、白い部分が残らないこともありえます。

## 样例 #1

### 输入

```
5 4 2
2 1 1
3 3 4```

### 输出

```
9```

## 样例 #2

### 输入

```
5 4 3
2 1 1
3 3 4
1 4 2```

### 输出

```
0```

## 样例 #3

### 输入

```
10 10 5
1 6 1
4 1 3
6 9 4
9 4 2
3 1 3```

### 输出

```
64```

# 题解

## 作者：lgvc (赞：5)

## 方法1：

暴力枚举，时间复杂度 $O(NHW)$，可以通过。

## 方法2：

考虑对该暴力算法进行优化。

考虑如下两次操作：

```
3 4 1
5 5 1
```

第一次操作是对所有的 $x<3$ 进行涂色，第二次操作是对所有的 $x<5$ 进行涂色。

可以发现第一操作已经被第二次操作覆盖了，换句话说就是第一次操作做了也是白做。

于是我们就忽略掉第一次操作。

操作 $2,3,4$ 同理。

故对于每一种操作，我们至多可以保留一组有用的操作。

最后对剩下的 $4$ 组操作进行数学计算答案即可，时间复杂度 $O(N)$。

代码：

```cpp
#include <bits/stdc++.h>
int a1,a2,a3,a4,W,H,N;
signed main(void) {
	scanf("%d %d %d",&W,&H,&N);
	a2=W;
	a4=H;
	for(int i=1;i<=N;i++) {
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		if(c==1) {
			a1=std::max(a1,a);
		} else if(c==2) {
			a2=std::min(a2,a);			
		} else if(c==3) {
			a3=std::max(a3,b);
		} else if(c==4) {
			a4=std::min(a4,b);
		}
	}	
	if(a1>a2||a3>a4) printf("0");else printf("%d",(a2-a1)*(a4-a3));
    return 0;
}
```


---

## 作者：FreedomKing (赞：2)

# 暴力+优化=奇迹
[注：blog 食用更佳](https://www.luogu.com.cn/blog/531806/AT2145)

------------
### 题目大意
有一个左上角为 $(0,0)$，右下角为 $(W,H)$ 的矩阵，初始时全部为白色。

给出 $N$ 个操作，每个操作给定一个点 $(x_i,y_i)$ 和一个数 $a_i$，代表：

- $a_i=1$ 时：将 $x<x_i$ 的区域全部涂黑
- $a_i=2$ 时：将 $x>x_i$ 的区域全部涂黑
- $a_i=3$ 时：将 $y>y_i$ 的区域全部涂黑
- $a_i=4$ 时：将 $y>y_i$ 的区域全部涂黑

问当所有操作均结束后剩下的白色区域的面积
### 思路
首先可以发现的是，打暴力 $O(NHW)$ 的时间复杂度是可以过的。但这并不能令我们满足，所以经过思考后发现有的操作是会被覆盖的，利用这一个特点进行取最大值或最小值再涂色便可以优化到最优了。

------------
[AT2145 [ABC047B] すぬけ君の塗り絵 2 イージー / Snuke's Coloring 2](https://www.luogu.com.cn/problem/AT2145)
### AC Code:
```cpp
#include<bits/stdc++.h>//不用万能头也可以，但个人觉得万能头方便
using namespace std;
int n,w,h,l,r,u,d,x,y,a;
int main(){
	scanf("%d%d%d",&w,&h,&n);//输入优化
	l=0,r=w,u=h,d=0;//初始化
	for(register int i=1;i<=n;i++){
		scanf("%d%d%d",&x,&y,&a);
		if(a==1) l=max(l,x);
		if(a==2) r=min(r,x);
		if(a==3) d=max(d,y);
		if(a==4) u=min(u,y);
		//去最大值或最小值
	}
	if(l>=r||d>=u) putchar('0');//使用putchar较快
	else printf("%d",(r-l)*(u-d));//输出优化
	return 0;//好习惯
}
```
~~蒟蒻的第 9 篇题解，但还是求过 QwQ~~

---

## 作者：LYqwq (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT2145)

# 题目大意

有一个左上角为 $(0,0)$，右下角为 $(W,H)$ 的矩阵，初始时全部为白色。

给出 $N$ 个操作，每个操作给定一个点 $(x_i,y_i)$ 和一个参数 $a_i$，代表：

- $a_i=1$：将 $x<x_i$ 的区域全部涂黑。
- $a_i=2$：将 $x>x_i$ 的区域全部涂黑。
- $a_i=3$：将 $y<y_i$ 的区域全部涂黑。
- $a_i=4$：将 $y>y_i$ 的区域全部涂黑。

问操作后还剩下的白色区域的面积。

# 思路

可尝试暴力，直接按照题意模拟，最后统计面积，时间复杂度 $\mathcal{O}(WHN)$，可过。

但还有更优雅的方法。我们发现，每次操作的区域都是一个矩形，而且是一行一行和一列一列地操作。考虑维护白色区域的左上角 $(x_1,y_1)$ 和右下角 $(x_2,y_2)$ 坐标，对于每次操作：

- $a_i=1$：$x_1 \gets \max\{x_1,x\}$，这个操作覆盖的是坐标点上面的所有行，故取 $\max$。
- $a_i=2$：$x_2 \gets \min\{x_2,x\}$，覆盖坐标点下面的所有行，故取 $\min$。
- $a_i=3$：$y_1 \gets \max\{y_1,y\}$，覆盖坐标点左边的所有列，故取 $\max$。
- $a_i=4$：$y_2 \gets \min\{y_2,y\}$，覆盖坐标点右边的所有列，故取 $\min$。

最后，若左上角坐标还在右下角坐标的后面，那么就没有白色区域，输出 $0$。

否则，输出坐标差之积，即为白色区域面积。

# 代码

```cpp
#include <iostream>
using namespace std;
int w,h,n,x,y,a;
int x1,x2,y1,y2;

int main(){
	cin >> w >> h >> n;
	x2=w,y2=h; // x2 和 y2 不能忘了初始化
	while(n--){
		cin >> x >> y >> a;
		switch(a){
			case 1: x1=max(x1,x); break; // 1 操作涂的是第一行到当前行 -1，取最大值
			case 2: x2=min(x2,x); break; // 2 操作涂的是当前行 +1 到最后一行，取最小值
			case 3: y1=max(y1,y); break; // 3 操作涂的是第一列到当前列 -1，取最大值
			case 4: y2=min(y2,y); break; // 4 操作涂的是当前列 +1 到最后一列，取最小值
			default: break;
		}
	}
	// 全部操作执行完成后，白色区域的矩阵左上角坐标为 (x1,y1)，右下角坐标为 (x2,y2)
	if(x1>x2 || y1>y2){
		puts("0"); // 只要左上角在右下角的右下方，那么就没有白色区域
	}else{
		// 坐标差相乘即为白色区域面积
		cout << (x2-x1)*(y2-y1) << endl;
	}
	return 0;
}
```



---

## 作者：phigy (赞：1)

暴力 $O(NHW)$ 是可以过的 。

但是效率低下。

发现对于 $a_i=a_j=1$ 如果 $x_i < x_j$ 。

那么相当于只有 $x_j$ ，因为 $i$ 号限定被完全覆盖了 。

其他三种同理。

也就是说对于四种我们只需记录最大或最小的。

最后只用四次遍历，复杂度 $O(N+HW)$ 。

最后的遍历其实并没有必要。

设 $i$ 号操作中最大或最小的为 $c_i$ 。

若 $c_1>c_2$ 或 $c_3>c_4$ 那么答案为 0 。

否则答案为 $(c_1-c_2)(c_3-c_4)$ 。

时间复杂度 $O(N)$ 。

```cpp
#include <bits/stdc++.h>

using namespace std;

int w,h,n;
int a[110],x[110],y[110];
int c[5];
int main()
{
    int i,j,k;
    cin>>w>>h>>n;
    c[1]=0;
    c[2]=w;
    c[3]=0;
    c[4]=h;
	for(i=1;i<=n;i++)
	{
        cin>>x[i]>>y[i]>>a[i];
        if(a[i]==1)
        {
            c[1]=max(x[i],c[1]);
        }
        if(a[i]==2)
        {
            c[2]=min(x[i],c[2]);
        }
        if(a[i]==3)
        {
            c[3]=max(y[i],c[3]);
        }
        if(a[i]==4)
        {
            c[4]=min(y[i],c[4]);
        }
    }
    if(c[1]>c[2]||c[3]>c[4])cout<<0;
    else
    {
        cout<<(c[2]-c[1])*(c[4]-c[3]);
    }
    return 0;
}
```


---

## 作者：LongDouble (赞：1)

#### **思路**

暴力出奇迹！

我们只要暴力枚举每一个区域，再枚举每一个操作是否能把该区域涂黑就行了。

由于 $1\leq W,H,N\leq 100$，所以 $O(WHN)$ 的时间复杂度是可以过的。

另外注意，可能是题面的锅，当结果等于 $0$ 时，样例输出是空的。

但是实际上当结果等于 $0$ 时，还是要输出 $0$。

#### **代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
int w, h, n, a[110], x[110], y[110], ans;

int main()
{
	scanf("%d%d%d", &w, &h, &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d", &x[i], &y[i], &a[i]);
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			bool ok = 1;
			for (int k = 1; k <= n; k++)
			{
				if (a[k] == 1 && i < x[k])
				{
					ok = 0;
					break;
				}
				if (a[k] == 2 && i >= x[k])
				{
					ok = 0;
					break;
				}
				if (a[k] == 3 && j < y[k])
				{
					ok = 0;
					break;
				}
				if (a[k] == 4 && j >= y[k])
				{
					ok = 0;
					break;
				}
			}
			if (ok) ans++;
		}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：3a51_ (赞：0)

### 题目大意

一个 $w \times h$ 的矩形，给定 $n$ 个操作，每次给定参数 $a_i$ 、点     $x_i,y_i$ ，操作规则如下：

$1.a_i=1$ 时， $x<x_i$ 的区域将被涂黑；

$2.a_i=2$ 时， $x>x_i$ 的区域将被涂黑；

$3.a_i=3$ 时， $y<y_i$ 的区域将被涂黑；

$4.a_i=4$ 时， $y>y_i$ 的区域将被涂黑。

求没被涂黑的面积。

### 算法1

暴力枚举长方形并标记，最后统计一遍没被标记的点即可。

时间复杂度 $O(WHN)$ ，可以通过本题。

### 算法2

仔细思考一下，发现对于两次操作 $i,j$ ，如果 $a_i=a_j=1$ 且 $x_j<x_i$ ，则 $j$ 操作需要覆盖的面积已经被 $i$ 操作覆盖了，所以 $j$ 操作的时间完全可以省下来。

对于 $a_i=a_j$ 的其他三种情况也同理，所以我们就可以直接记录最大值和最小值即可。

#### 划重点！

因为去掉的是四周，所以最终的部分一定是一个在中间的长方形。

当 $a_i=1$ 时，覆盖的是 $x_i$ 左边，所以 $x_i$ 越大，覆盖的越多。也就是说，我们对于 $a_i=1$ 的情况，只需要取 $\max(x_i)$ 即可，这就是最终剩余长方形的左边界。

当 $a_i=2$ 时，覆盖的是 $x_i$ 右边，所以 $x_i$ 越小，覆盖的越多。也就是说，我们对于 $a_i=2$ 的情况，只需要取 $\min(x_i)$ 即可，这就是最终剩余长方形的右边界。

当 $a_i=3$ 时，覆盖的是 $y_i$ 上边，所以 $y_i$ 越大，覆盖的越多。也就是说，我们对于 $a_i=3$ 的情况，只需要取 $\max(y_i)$ 即可，这就是最终剩余长方形的上边界。

当 $a_i=4$ 时，覆盖的是 $y_i$ 下边，所以 $y_i$ 越小，覆盖的越多。也就是说，我们对于 $a_i=4$ 的情况，只需要取 $\min(y_i)$ 即可，这就是最终剩余长方形的下边界。

综上所述，最终长方形的长为 $\min(x_i)(a_i=2)-\max(x_i)(a_i=1)$ ,宽为     $\min(y_i)(a_i=4)-\max(y_i)(a_i=3)$ 。将两数相乘即为最终剩余长方形的面积。

#### 温馨提示

长和宽可能存在负数，要特判变为 $0$ ，因为题面的某些问题，样例输出为$0$时不显示。

**注意：$x_{min},y_{min}$ 必须初始化为 $w,h$ ，否则会 $WA$**。

最终时间复杂度 $O(n)$ 。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h,n,a,x,y,xmax,xmin,ymax,ymin;
int main()
{
    cin>>w>>h>>n;
    xmin=w,ymin=h;
	for(int i=1;i<=n;i++)
	{
        cin>>x>>y>>a;
        if(a==1)
            xmax=max(xmax,x);
        if(a==2)
            xmin=min(xmin,x);
        if(a==3)
            ymax=max(ymax,y);
        if(a==4)
            ymin=min(ymin,y);
    }
    if(xmax>xmin || ymax>ymin)
		cout<<0;
    else
        cout<<(ymin-ymax)*(xmin-xmax);
    return 0;
}
```

---

## 作者：szhqwq (赞：0)

[AT2145](https://www.luogu.com.cn/problem/AT2145)

## 分析

这道题我们可以直接暴力再优化，因为数据范围是完全小于等于 $100$ 的，所以暴力是完全可以过的，那么我们考虑以下几种情况：

1. $op=1$，当前区域在后边输入之中被覆盖时，前面所记录的被涂黑的区域就没有了意义，因此，在每次输入时应取 $\max$，即为 $a=\max(a,x)$；

2. $op=2$，同上，唯一需注意的是这里写的是 $x>x_i$，那么 $x_i$ 越小涂黑区域就越大，即为 $b=\min(b,x)$；

这里还有第三,第四种情况，都与一、二种情况一一对应。

最后特判一下，如果 $b \ge a$ 或 $d \ge c$ 则没有白色区域，输出 $0$。

AC code

```cpp
#include <bits/stdc++.h>
#define int long long
#define AC return 0
#define il inline
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,r,l) for(int i=r;i>=l;i--)
using namespace std;

const int N=100010;

int a=0,b=0,c,d;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,l,r;
	cin>>l>>r>>n;
	b=l,d=r;
	rep(i,1,n) {
		int x,y,op;
		cin>>x>>y>>op;
		if(op==1) a=max(a,x);
		else if(op==2) b=min(b,x);
		else if(op==3) c=max(c,y);
		else if(op==4) d=min(d,y);
	}
	if(a>=b || c>=d) puts("0");
	else cout<<(b-a)*(d-c)<<endl;
	AC;
}
```

---

