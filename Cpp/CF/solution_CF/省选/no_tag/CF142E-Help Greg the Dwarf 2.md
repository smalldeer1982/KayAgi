# Help Greg the Dwarf 2

## 题目描述

Greg the Dwarf has been really busy recently with excavations by the Neverland Mountain. However for the well-known reasons (as you probably remember he is a very unusual dwarf and he cannot stand sunlight) Greg can only excavate at night. And in the morning he should be in his crypt before the first sun ray strikes. That's why he wants to find the shortest route from the excavation point to his crypt. Greg has recollected how the Codeforces participants successfully solved the problem of transporting his coffin to a crypt. So, in some miraculous way Greg appeared in your bedroom and asks you to help him in a highly persuasive manner. As usual, you didn't feel like turning him down.

After some thought, you formalized the task as follows: as the Neverland mountain has a regular shape and ends with a rather sharp peak, it can be represented as a cone whose base radius equals $ r $ and whose height equals $ h $ . The graveyard where Greg is busy excavating and his crypt can be represented by two points on the cone's surface. All you've got to do is find the distance between points on the cone's surface.

The task is complicated by the fact that the mountain's base on the ground level and even everything below the mountain has been dug through by gnome (one may wonder whether they've been looking for the same stuff as Greg...). So, one can consider the shortest way to pass not only along the side surface, but also along the cone's base (and in a specific case both points can lie on the cone's base — see the first sample test)

Greg will be satisfied with the problem solution represented as the length of the shortest path between two points — he can find his way pretty well on his own. He gave you two hours to solve the problem and the time is ticking!

## 样例 #1

### 输入

```
2 2
1.0 0.0 0.0
-1.0 0.0 0.0
```

### 输出

```
2.000000000```

## 样例 #2

### 输入

```
2 2
1.0 0.0 0.0
1.0 0.0 1.0
```

### 输出

```
2.414213562```

## 样例 #3

### 输入

```
2 2
1.0 0.0 1.0
-1.0 0.0 1.0
```

### 输出

```
2.534324263```

## 样例 #4

### 输入

```
2 2
1.0 0.0 0.0
0.0 1.0 1.0
```

### 输出

```
3.254470198```

# 题解

## 作者：_outcast_ (赞：1)

题意非常简单，就是求圆锥上两点（设为 $A$ 和 $B$ ）的最小表面距离。
### 分析
来考虑一下两个点的位置情况：

- 两个点都在底面

这种情况很显然直接计算欧几里得距离就行了。

- 一个点在侧面，一个点在底面

这种情况下，暂时还没有想到什么简单的几何计算方法，但是我们可以考虑暴力枚举底面圆上的点，取最小值。

- 两个点在侧面

可能很多人都会觉得，侧面上两点的最小表面距离就是把侧面展开成扇形后再求两点的欧几里得距离。但是事实上，这样并不总是最优的，最短距离是可能经过底面的，例如下面一组数据：
>顶点坐标（0，0,100）；底面半径100；两点坐标分别为（99，0，1），（-99，0，1）；如果是在侧面上的话算出来是 $198\sqrt2\times\sin\frac{\sqrt2}{4}\pi\approx250.898$，如果按经过底面来算的话是 $200+2\sqrt2\approx202.828$

（事实上当两个点距离底面较近时，最短距离大概率是经过底面的，而不是在侧面。）

计算经过底面的路径时可以在底面圆上枚举两个点，再计算底面两点的距离加上侧面的距离，如下图红线，取最小值：

![](https://cdn.luogu.com.cn/upload/image_hosting/i1rxhgxr.png)

综上我们就理论做出了这道题了，代码细节很多，还有一些小技巧，来看看具体实现

### 代码实现
接下来我会详细说明两个最重要的函数的代码实现

- 计算圆锥底面两点的距离：

用空间两点距离公式（z 其实可以省去）
```cpp
int d(point a1,point a2){
    return sqrt((a1.x-a2.x)*(a1.x-a2.x)+(a1.y-a2.y)*(a1.y-a2.y)+(a1.z-a2.z)*(a1.z-a2.z));
}
```
- 计算圆锥侧面两点的距离：

我们需要分别连接顶点和 $A$，顶点和 $B$，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mcys3hvk.png)

我们可以把这部分红色的取出来，展开这部分的侧面，现在我们把其中一边放在x轴，$A$ 的坐标为 $(l_{AV},0)$，$B$ 的坐标为 $(l_{BV}\cos\angle_{AVB} , l_{BV}\sin\angle_{AVB})$ 如图；
![](https://cdn.luogu.com.cn/upload/image_hosting/lcdqhfdo.png)

发现 $\angle_{AVB}=$ 弧$FG\div VG$，$VG$ 是圆锥母线的长度，可以利用勾股定理 $VG^2=h^2+r^2$ 求出，弧$FG$ 的长度怎么求？

回到上面的立体图形可以发现，我们可以利用底面圆求出弧$FG$。这需要我们求出 $\angle_{FOG}$，可以利用 $A$，$B$ 的 x , y 坐标再利用反正切函数（atan）求出。

```cpp
int solve(point a1,point a2){
    int res;
    if(abs(a1.z)<eps&&abs(a2.z)<eps) return d(a1,a2);
    
    int l1=d(a1,vertex),l2=d(a2,vertex);
    int A=atan2(a2.y,a2.x)-atan2(a1.y,a1.x);
    
    while(A<-eps) A+=2*pi;
    while(A>2*pi-eps) A-=2*pi;//这里是将∠FOG化到0~90度
    if(A>pi) A=2*pi-A;
    
    int B=(A*r)/sqrt(r*r+h*h);//求∠AVB
    int u1=0,v1=l1,u2=l2*sin(B),v2=l2*cos(B);
    res=sqrt((u1-u2)*(u1-u2)+(v1-v2)*(v1-v2));
    B=2*pi-B;//这里还需要考虑∠AVB的补角
    u1=0,v1=l1,u2=l2*sin(B),v2=l2*cos(B);
    res=min(res,sqrt((u1-u2)*(u1-u2)+(v1-v2)*(v1-v2)));
    return res;
}
```
有了上述两个关键函数我们就能愉快的切掉这道题了。


- 小tips

我们枚举的时候不用以精度为步长来枚举，因为这样会枚举很多次，直接TLE，可以先大步的跳，再根据大步长得到一个粗略答案，调整区间，进行精度二分。

完整代码（详见注释）
```cpp
#include<bits/stdc++.h>
#define int double
using namespace std;
const int eps=1e-7,pi=acos(-1.0);
int ans,r,h,la,ra,mxa,mya,lb,rb,mxb,myb,lv,rv,step=pi/20;
struct point{int x,y,z;}vertex,a,b;
int d(point a1,point a2){ //空间两点距离 
    return sqrt((a1.x-a2.x)*(a1.x-a2.x)+(a1.y-a2.y)*(a1.y-a2.y)+(a1.z-a2.z)*(a1.z-a2.z));
}
int solve(point a1,point a2){ //计算圆锥侧面展开图上两点距离，以及两点都在底面的距离 
    int res;
    if(abs(a1.z)<eps&&abs(a2.z)<eps) return d(a1,a2);
    
    int l1=d(a1,vertex),l2=d(a2,vertex);
    int A=atan2(a2.y,a2.x)-atan2(a1.y,a1.x);
    
    while(A<-eps) A+=2*pi;
    while(A>2*pi-eps) A-=2*pi;//这里是将∠FOG化到0~90度
    if(A>pi) A=2*pi-A;
    
    int B=(A*r)/sqrt(r*r+h*h);//求∠AVB
    int u1=0,v1=l1,u2=l2*sin(B),v2=l2*cos(B);
    res=sqrt((u1-u2)*(u1-u2)+(v1-v2)*(v1-v2));
    B=2*pi-B;//这里还需要考虑∠AVB的补角
    u1=0,v1=l1,u2=l2*sin(B),v2=l2*cos(B);
    res=min(res,sqrt((u1-u2)*(u1-u2)+(v1-v2)*(v1-v2)));
    return res;
}

int get_line_basement(int A,int B){ //计算两个点都在侧面，经过底面的情况 
    point aa=(point){r*cos(A),r*sin(A),0};
	point bb=(point){r*cos(B),r*sin(B),0};
	return solve(a,aa)+solve(b,bb)+d(aa,bb);
}

int get_min_line(int A){//这是枚举两个点时为了保证精度额外提出来的一维枚举 
    int B,vl,ch,ret=1919810;
    for(B=0;B<2*pi;B+=step){
    	vl=get_line_basement(A,B);
    	if(ret>vl){
    		ret=vl;
    		ch=B;
    	}
    }
    lb=max(0.0,ch-step);
    rb=min(2*pi,ch+step);
    while(lb<rb){
    	mxb=0.5*(lb+rb);
    	myb=mxb+eps;
    	if(get_line_basement(A,mxb)>get_line_basement(A,myb)) lb=mxb+eps;
        else rb=mxb-eps;
    }
    vl=get_line_basement(A,0.5*(lb+rb));
    if(ret>vl) ret=vl;
    return ret;
}
signed main(){
    scanf("%lf%lf",&r,&h);
    scanf("%lf%lf%lf",&a.x,&a.y,&a.z);
    scanf("%lf%lf%lf",&b.x,&b.y,&b.z);
    ans=1919810;
    vertex=(point){0,0,h};
    if(abs(a.z)<eps&&abs(b.z)<eps) return printf("%0.9f",d(a,b)),0;//两点都在底面 
	if(abs(b.z)<eps){
    	swap(a.x,b.x);
    	swap(a.y,b.y);
    	swap(a.z,b.z);
    }
    if(abs(a.z)<eps&&abs(b.z)>eps){//一个在底面，一个在侧面 
    	int B,vl,ch,mi=1919810;
        for(B=0;B<2*pi;B+=step){//暴力枚举两个圆上的点 
    	    point t=(point){r*cos(B),r*sin(B),0}; 
			vl=solve(a,t)+solve(b,t);
    		if(mi>vl){
    			mi=vl;
    			ch=B;
    		}
    		if(ans>vl) ans=vl;
    	}
    	la=max(0.,ch-step);
    	ra=min(2*pi,ch+step);
    	while(la<ra){
    		mxa=0.5*(la+ra);
    		mya=mxa+eps;
    		point t1=(point){r*cos(mxa),r*sin(mxa),0};
    		point t2=(point){r*cos(mya),r*sin(mya),0};
    		lv=solve(a,t1)+solve(b,t1);
        	rv=solve(a,t2)+solve(b,t2);
    		if(lv>rv) la=mxa+eps;
    		else ra=mxa-eps;	
    	}
    	point tool=(point){r*cos(0.5*(la+ra)),r*sin(0.5*(la+ra)),0};
    	vl=solve(a,tool)+solve(b,tool);
    	if(ans>vl) ans=vl;
    	return printf("%0.9f",ans),0;
	}
	if(abs(a.z)>eps&&abs(b.z)>eps){//两点都在侧面 
		ans=min(ans,solve(a,b));//侧面展开路径 
		int B,vl,ch,mi=1919810;
    	for(B=0;B<2*pi;B+=step){
    		vl=get_min_line(B);//暴力枚举圆上的两点 
    		if(mi>vl){
            	mi=vl;
            	ch=B;
        	}
        	if(ans>vl) ans=vl;
    	}
    	la=max(0.0,ch-step);
    	ra=min(2*pi,ch+step);
    	while(la<ra){
        	mxa=0.5*(la+ra);
        	mya=mxa+eps;
    		if(get_min_line(mxa)>get_min_line(mya)) la=mxa+eps;
    		else ra=mxa-eps;
    	}
    	vl=get_min_line(0.5*(la+ra));
    	if(ans>vl) ans=vl;
    	printf("%.9f\n",ans);
	}
}
```




---

