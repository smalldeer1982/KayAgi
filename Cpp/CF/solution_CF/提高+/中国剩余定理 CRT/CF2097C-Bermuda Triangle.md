# Bermuda Triangle

## 题目描述

百慕大三角——大西洋中一片神秘区域，据传言船只和飞机都会在此凭空消失。有人归咎于磁力异常，有人则认为是通往异世界的传送门，但真相仍笼罩在谜团之中。

在一个晴朗的日子里，814 次常规客运航班正从迈阿密飞往拿骚。在飞机进入一片诡异闪烁的迷雾区域前，一切都看似正常。无线电通讯中断，仪表疯狂旋转，窗外闪烁着非自然的光芒。

为简化问题，我们假设百慕大三角和飞机都位于平面上，且三角形的顶点坐标为 $(0, 0)$、$(0, n)$ 和 $(n, 0)$。飞机初始位于严格处于百慕大三角内部的点 $(x, y)$，并以速度向量 $(v_x, v_y)$ 移动。由于所有仪器都已失灵，机组人员无法控制飞机。

当飞机到达三角形任意一个顶点时，即可成功逃离。但如果飞机在任意时刻（可能是非整数时间）碰到三角形的边界（不包括顶点），其速度向量会立即根据该边进行镜面反射$^\dagger$，随后飞机将继续沿新方向移动。

请判断飞机是否能逃离百慕大三角（即到达某个顶点）。如果可能，还需计算在逃离前会碰到边界的次数（每次触碰边界都计入次数，即使是在同一点；经过顶点不计入次数）。

$^\dagger$ 反射遵循物理定律：入射角等于反射角。

## 说明/提示

第一个测试用例的示意图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097C/5dcc41152cc7283979e514f25388f82aa27ff3b9.png)

第二个测试用例中，除速度外初始数据与第一个测试用例相同，且飞机初始运动方向相同，因此答案相同。

第三个测试用例的答案为 $-1$，因为飞机将始终沿着绿色标记的线段移动。示意图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097C/dea0fd33e36a4eb6795ed5c962c688b9827de243.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
6 2 2 5 2
6 2 2 20 8
4 1 2 1 1
4 1 1 1 2
4 1 1 2 1
6 2 3 2 3```

### 输出

```
2
2
-1
-1
-1
5```

# 题解

## 作者：chenzhaoxu2027 (赞：8)

## 简述题意

- 有一个等腰直角三角形的台球桌，三个顶点分别是 $(0,0),(0,n),(n,0)$，一个球位于坐标为 $(x,y)$ 的位置，现在沿方向向量为 $(v_x,v_y)$ 的方向将这个球击打出去，每一秒运动 $\sqrt{v_x^2+v_y^2}$ 的长度。这个球桌没有摩擦力，但是碰到边就会反弹，球到达这个三角形的顶点时就会进袋，求这个球碰撞几次之后才会进袋，或者输出无解。

## 分析

这个问题说球可以反弹，十分的难以计算。我们不妨考虑球匀速直线运动，但是球桌通过轴对称布满平面。我们惊人的发现去找球的运动轨迹与密铺三角形的顶点的交点的效果和原问题是等价的。

首先考虑判断无解。这一步我们将时间的秒数化为整数方便计算，那么我们只需要将 $v_x$ 和 $v_y$ 除以 $\gcd(v_x,v_y)$ 就可以了。

然后我们假设进袋时间是 $M$，那么就有以下的两个同余方程：

$$x + Mv_x \equiv 0 \pmod n$$

$$y + Mv_y \equiv 0 \pmod n$$

分别解这两个方程可以使用 exgcd。如果这两个方程的任何一个无解，那么这个问题就无解。

但是这两个方程解出来的 $M$ 可能不一样，不妨假设分别解得特解 $M_x$ 和 $M_y$，那么我们就需要看是否可能找到另外两个解让 $M_x=M_y$。

根据二元一次方程通解公式，我们可以得到：

$$M_x+k\times \frac{n}{\gcd(n,v_x)}=M_y+p\times \frac{n}{\gcd(n,v_y)}$$

其中 $k,p$ 是整数。解这一个方程我们可以使用 exgcd 解出 $k,p$，这个方程无解那么这个问题就无解。然后我们在倒退就可以算出真正的 $M$。

好，有了 $M$ 我们就能计算出球直线运动后的终点坐标 $(t_x,t_y)$。原问题中反弹了几次的问题就等价于现在的：“球运动的这个线段中与密铺的三角形的线段相交了几次？”

我们分 4 类考虑：竖直的、水平的、左下往右上斜的和左上往右下斜的。前两类只需要使用终点的对应坐标除以 $n$ 再减一就可以了。（因为起点在最左下的三角形内，减一是为了减去终点碰到的那根线）而后两类就复杂一些，我们暂时不考虑减去终点碰到的那根线这回事。

左上往右下斜的线上的点的坐标满足 $x+y$ 是一个定值，但是我们发现这个密铺三角形的图案里面不是所有 $n$ 的倍数都可以作为 $x+y$ 的定值使得左上往右下斜的线出现的。这个数必须是 $n$ 的奇数倍数。这也不难，我们直接将终点的横纵坐标加起来再加一个 $n$，这个时候条件就变成了 $n$ 的偶数倍数，所以线的个数就是 $\lfloor \frac{t_x+t_y+n}{2n} \rfloor$。

另一种斜向的线同理。需要注意的是，另一种斜向的线上的点满足差值是定值，如果直接套用上面的式子会错，得加一个绝对值。

最后的问题：处理终点的额外计算的线的个数。这里我想到了一种偷懒的办法，还是以左上往右下斜的线为例，如果终点位于这根线上，那么一定有：$t_x+t_y+n=2qn$，其中 $q$ 是整数；否则就有：$t_x+t_y+n=(2q+1)n$，其中 $q$ 是整数。我们要让第一种情况答案减一，第二种情况答案不变，我们发现，只要不加那个 $n$ 就能达到我们的目的。另一种情况也是一样的。

然后就做完了，值得注意的是这种方式的中间步骤可能爆 long long，得用 int128。听着很复杂实际上写着比较简单。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
int gcd(int a,int b){
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}
void exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	int x_=x,y_=y;
	x=y_;
	y=x_-(a/b)*y_;
}
int read(){}//快读快写省略，目的是配套int128
void write(int x){}
signed main(){
	int t=read();
	while(t--){
		int n=read(),x=read(),y=read(),vx=read(),vy=read();
		int g=gcd(vx,vy);
		vx/=g;
		vy/=g;
		if(x%gcd(vx,n)!=0||y%gcd(vy,n)!=0){
			cout<<-1<<"\n";
			continue;
		}
		int gx=gcd(vx,n),gy=gcd(vy,n);
		int mx,kx,my,ky;
		exgcd(vx/gx,n/gx,mx,kx);
		exgcd(vy/gy,n/gy,my,ky);
		mx*=x/gx;
		my*=y/gy;
		mx=-mx;
		my=-my;//注意正负性啊
		if(max(my-mx,mx-my)%gcd(n/gx,n/gy)!=0){
			cout<<-1<<"\n";
			continue;
		}
		int G=gcd(n/gx,n/gy);
		int k,l;
		exgcd(n/gx/G,n/gy/G,k,l);
		l=-l;
		k*=(my-mx)/G;
		int M=mx+n/gx*k;
		M=(M%n+n)%n;//M可能不在范围内，由于保证了vx与vy互质，那么周期一定是n
		int X=M*vx+x,Y=M*vy+y;
		int bx=X/n-1,by=Y/n-1,bs=(X+Y)/(2*n),bt=(max(Y-X,X-Y))/(2*n);//CF上面int128不让用abs，只能这么写qwq
		write(bx+by+bs+bt);
		cout<<"\n";
	}
	return 0;
} 
```

---

## 作者：OtterZ (赞：2)

# 题意
给定一个等腰直角三角形，从一个点开始朝一个方向走，碰到边反弹，碰到点结束，问反弹了多少次。
# 题解

我们充分发扬人类智慧。

对三角形不断地做对称，铺展成一个无限大的网格，题目转化成在如图的网格上到第一个黑色粗边交点之间碰了几个边。

![](https://cdn.luogu.com.cn/upload/image_hosting/jvyxnbd9.png)

首先算出顶点位置，我们先得到 $T$，使得：

$$
n | x + vxT \\
n | y + vyT
$$

在 $\gcd(vx,vy) = 1$ 的情况下 $T$ 为整数，$\gcd(vx,vy) \neq 1$ 是两个同时做除法进行转化，然后用CRT得到 $T$，CRT处理过程中判无解则原问题无解。

接下来看图说话，对于结尾点 $(nx,ny)$，得到经过图上横边 $\frac{nx}{n} - 1$ 条，竖边 $\frac{ny}{n} - 1$ 条，左上到右下斜边 $[\frac{nx + ny}{2n}]$ 条，左下到右下斜边 $[\frac{|nx - ny|}{2n}]$ 条，于是此题就做完了。

没错，就是这么简单。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,y,vx,vy,fx,fy,tx,ty,px,py;
int exgcd(int a,int b,int &x,int &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	int t = exgcd(b,a % b,y,x);
	y = y - 1ll * a / b * x;
//	printf(" %d %d %d %d\n",a,b,x,y);
	return t;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d %d %d",&n,&x,&y,&vx,&vy);
		int p = exgcd(vx,vy,fx,fy);
		vx /= p;
		vy /= p;
		tx = exgcd(vx,n,fx,px);
		//printf("%d %d %d %d %d\n",vx,n,fx,px,tx);
		fx %= (n / tx);
		if(fx < 0)
			fx += n / tx;
		if((n - x) % tx != 0){
			puts("-1");
			continue;
		}
		else
			fx = 1ll * fx * (n - x) / tx % (n / tx);
		px = n / tx;
		//printf("%d\n",fx);
		ty = exgcd(vy,n,fy,py);
		fy %= (n / ty);
		if(fy < 0)
			fy += n / ty;
		if((n - y) % ty != 0){
			puts("-1");
			continue;
		}
		else
			fy = 1ll * fy * (n - y) / ty % (n / ty);
		py = n / ty;
		//printf("%d\n",py);
		if(fx == fy){
			int T = fx;
			long long nx = 1ll * T * vx + x,ny = 1ll * T * vy + y;
			//printf("%d %d %d %d\n",nx / n - 1,ny / n - 1,((nx + ny) / n >> 1),(abs(nx - ny) / n >> 1));
			printf("%lld\n",nx / n + ny / n - 2 + ((nx + ny) / n >> 1) + (abs(nx - ny) / n >> 1));
			continue;
		}
  	//printf(" %d %d %d %d\n",fx,fy,px,py);
		int o = exgcd(px,py,tx,ty);
		//printf("%d %d %d %d %d\n",px,py,tx,ty,o);
		if((fy - fx) % o != 0){
			puts("-1");
			continue;
		}
		else{
			tx *= ((fy - fx) /o);
			ty *= ((fy - fx) /o);
		}
		//printf("%d %d\n",tx,-ty);
		int lx = (px) / o,ly = (py) / o;
		tx = tx % abs(ly);
		if(tx < 0){
			tx = tx + abs(ly);
		}
		int T = fx + tx * px;
		long long nx = 1ll * T * vx + x,ny = 1ll * T * vy + y;
		//printf("%d %d %d %d\n",nx / n - 1,ny / n - 1,((nx + ny) / n >> 1),(abs(nx - ny) / n + 1 >> 1));
		printf("%lld\n",nx / n + ny / n - 2 + ((nx + ny) / n >> 1) + (abs(nx - ny) / n >> 1));
	}
}
```

---

