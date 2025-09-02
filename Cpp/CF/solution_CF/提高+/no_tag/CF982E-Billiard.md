# Billiard

## 题目描述

Consider a [billiard table](https://en.wikipedia.org/wiki/Billiard_table) of rectangular size $ n \times m $ with four pockets. Let's introduce a coordinate system with the origin at the lower left corner (see the picture).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/5400ec264949b612eb9900ddf2189fccb1a2c217.png)There is one ball at the point $ (x, y) $ currently. Max comes to the table and strikes the ball. The ball starts moving along a line that is parallel to one of the axes or that makes a $ 45^{\circ} $ angle with them. We will assume that:

1. the angles between the directions of the ball before and after a collision with a side are equal,
2. the ball moves indefinitely long, it only stops when it falls into a pocket,
3. the ball can be considered as a point, it falls into a pocket if and only if its coordinates coincide with one of the pockets,
4. initially the ball is not in a pocket.

Note that the ball can move along some side, in this case the ball will just fall into the pocket at the end of the side.

Your task is to determine whether the ball will fall into a pocket eventually, and if yes, which of the four pockets it will be.

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/69be840146adfcf731c5725a9e0b894673e7da29.png)The second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/a92c4ee568a643301b20d63f7451b437aa813098.png)In the third sample the ball will never change its $ y $ coordinate, so the ball will never fall into a pocket.

## 样例 #1

### 输入

```
4 3 2 2 -1 1
```

### 输出

```
0 0```

## 样例 #2

### 输入

```
4 4 2 0 1 1
```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 10 10 1 -1 0
```

### 输出

```
-1```

# 题解

## 作者：是个汉子 (赞：7)

### Solution

将图经过~~小学就学了的~~反转转化成一条斜率为 $1$ 的直线，那么有解就是经过了 $a$ 个 $n$ 的同时经过了 $b$ 个 $m$ ，又因为起点 $S(x,y)$ 也经过这条直线，所以 $y$ 轴交点为 $(0,y-x)$ 。

然后就可得到：
$$
an+(y-x)=bm\Rightarrow an-bm=x-y\Rightarrow an+b(-m)=x-y
$$
用扩展欧几里得求解完，再 $\%$ 出个最小值即可。

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
int n,m,x,y,vx,vy;
int rex,rey;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

ll exgcd(ll a,ll b,ll &x1, ll &y1){
    if(!b){
        x1=1;
        y1=0;
        return a;
    }
    ll ans=exgcd(b,a%b,x1,y1);
    ll t=x1;
    x1=y1;
    y1=t-a/b*y1;
    return ans;
}

int main(){
    n=read();m=read();x=read();y=read();vx=read();vy=read();
    //判断平行情况
    if(vx==0){
        if(x==0||x==n){
            if(vy==1) printf("%d %d\n",x,m);
            else printf("%d %d\n",x,0);
        }
        else puts("-1");
        return 0;
    }
    if(vy==0){
        if(y==0||y==m){
            if(vx==1) printf("%d %d\n",n,y);
            else printf("%d %d\n",0,y);
        }
        else puts("-1");
        return 0;
    }
    if(vx==-1) rex=1,x=n-x;
    if(vy==-1) rey=1,y=m-y;
    //这里就是将速度反转过来了
    ll a,b,gcd;
    gcd=exgcd(n,m,a,b);
    if((x-y)%gcd){//判断无解
        puts("-1");return 0;
    }
    a*=(x-y)/gcd,b*=(x-y)/gcd;//解出来的真正的a,b
    int n1=n/gcd,m1=m/gcd;
    ll a1=(a%m1+m1-1)%m1+1,b1=-((x-y)-a1*n)/m,ansx=n,ansy=m;//最小解
    if(a1%2==0) ansx=n-ansx;//经过偶数个n,此时应该是0
    if(b1%2==0) ansy=m-ansy;//经过偶数个m,此时应该是0
    if(rex) ansx=n-ansx;//反转
    if(rey) ansy=m-ansy;//反转
    printf("%lld %lld\n",ansx,ansy);
    return 0;
}
```



---

## 作者：Leap_Frog (赞：6)

### Descripton.
台球桌上四角是洞，告诉你球桌大小，初始坐标，初始速度分量。  
求球能否落入某个洞。  

### Solution.
如果速度分量水平/垂直，直接特判。  
然后如果速度分量为 $-$ 直接翻转球桌。  
这样我们就把速度分量变成了 $\vec{v}=(1,1)$  

然后根据小学奥数，这个撞击很难处理。  
我们不妨把台球桌翻折出去，这样球运动轨迹就是直线。  
然后我们就需要解方程
$$
\begin{cases}
x+Z=A\times n\\
y+Z=B\times m\\
\end{cases}
$$
$$\therefore x-y=A\times n-B\times m$$
解出最小的 $A\ge0$ 和 $B\ge 0$就好了。  
然后判断翻折了多少次。  

如果是奇数，最后它是经过镜像翻折过的。  

### Coding.
```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
int n,m,x,y,u,v;
inline int gcd(int x,int y) {return y?gcd(y,x%y):x;}
inline void exgcd(ll a,ll b,ll &x,ll &y) {if(!b) x=1,y=0;else exgcd(b,a%b,y,x),y-=a/b*x;}
int main()
{
	read(n),read(m),read(x),read(y),read(u),read(v);
	if(u==0) return x==0||x==n?printf("%d %d\n",x,(v>0)*m):puts("-1"),0;
	if(v==0) return y==0||y==m?printf("%d %d\n",(u>0)*n,y):puts("-1"),0;
	if(u<0) u=1,x=n-x;else u=0;
	if(v<0) v=1,y=m-y;else v=0;
	if((x-y)%gcd(n,m)) return puts("-1");
	//printf("%d %d %d %d %d %d\n",n,m,x,y,u,v);
	ll A,B,g=gcd(n,m),aa=m/g;exgcd(n,-m,A,B),A*=(x-y)/g,B*=(x-y)/g;
	if(x-y!=A*n-B*m) A=-A,B=-B;
	ll ra=((A+aa-1)%aa+aa)%aa+1,rb=(ra*n-x+y)/m;u^=ra&1,v^=rb&1;
	//printf("%lld , %lld ; %lld , %lld\n",A,B,ra,rb);
	return printf("%d %d\n",u?n:0,v?m:0),0;
}
```

---

## 作者：lemon_qwq (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF982E)。

是可爱的萌萌思维题。

前置知识：[扩欧](https://www.luogu.com.cn/problem/P5656)。

台球的撞击很难处理，我们可以假设有无限个台球桌对齐平铺在这个地方。

如果台球碰到边缘则不会反弹，穿到另一个台球桌上。

如果能到达任意台球桌的角落，则有解。

那么怎么判断能否到达呢？

根据我们推出来的思路，可以得到这样一个二元一次方程：

$$x+u\times t=k\times n$$
$$y+v\times t=q\times m$$


我们尽量让 $t$ 相等，然后用扩欧解最小的正整数 $k,q$ 即可。

如果无解，则不可到达。

根据奇偶性来判断最后落在哪个角上。

偶数次可以理解这个球桌镜像翻折过，画一下正常的图和无限个台球桌的图对比一下可能会方便理解。

完结撒花！

---

## 作者：lfxxx (赞：0)

首先两维分离。

很经典的 trick，碰壁反转可以视为不反转，但是将空间以一侧为镜子折过去后再无限重复。

那么假设走的步数是 $x$，走到 $0$ 或者 $n$ 上的条件就是模 $2 \times n$ 意义下为某个值。

对于两维分别求解限制后再扩展中国剩余定理合并限制即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mul(int a,int b,int c){
	int res=0,sum=a;
	for(int i=0;i<63;i++){
		if((1ll<<i)&b) res=(res+sum)%c;
		sum=(sum+sum)%c; 
	}
	return res;
}
int exgcd(int a,int b,int &x,int &y){
    //ax+by=gcd(a,b)
	bool flag=false;
	if(a<b) swap(a,b),flag=true;
    if(b==0){
        x=1;
        y=0;
		if(flag==true) swap(x,y);
        return a;       
    }else{
        int k=a/b;
        int d=exgcd(b,a%b,y,x);
        y-=k*x;
		if(flag==true) swap(x,y);
        return d;
    }   
}
int solve(int a1,int b1,int a2,int b2){
    //X = b1 (mod a1) X = b2 (mod a2)
    b1%=a1,b2%=a2;
    int M=a1,ans=b1;
    int c=((b2-ans)%a2+a2)%a2;
    int x=0,y=0;
	int g=exgcd(M,a2,x,y);
    int p=a2/g;
    x=mul(x,c/g,p);
    ans+=x*M;
    M*=p;
    ans=(ans%M+M)%M;
    if(ans%a1!=b1||ans%a2!=b2) return 1e18;
    return ans;
}
int n,m;
int sx,sy;
int vx,vy;
const int inf = 1e18;
int ans[4]={inf,inf,inf,inf};
signed main(){
    cin>>n>>m>>sx>>sy>>vx>>vy;
    //(0,0)
    if(vx!=0||sx==0){
        if(vy!=0||sy==0){
            ans[0]=solve((vx!=0?2*n:1),(vx!=0?(vx==1?2*n-sx:sx):0),(vy!=0?2*m:1),(vy!=0?(vy==1?2*m-sy:sy):0));
        }
    }
    //(n,0)
    if(vx!=0||sx==n){
        if(vy!=0||sy==0){
            ans[1]=solve((vx!=0?2*n:1),(vx!=0?(vx==1?n-sx:sx+n):0),(vy!=0?2*m:1),(vy!=0?(vy==1?2*m-sy:sy):0));
        }
    }
    //(0,m)
    if(vx!=0||sx==0){
        if(vy!=0||sy==m){
            ans[2]=solve((vx!=0?2*n:1),(vx!=0?(vx==1?2*n-sx:sx):0),(vy!=0?2*m:1),(vy!=0?(vy==1?m-sy:sy+m):0));
        }
    }
    //(n,m)
    if(vx!=0||sx==n){
        if(vy!=0||sy==m){
            ans[3]=solve((vx!=0?2*n:1),(vx!=0?(vx==1?n-sx:sx+n):0),(vy!=0?2*m:1),(vy!=0?(vy==1?m-sy:sy+m):0));
        }
    }
    if(min(min(ans[0],ans[1]),min(ans[2],ans[3]))>=1e18){
        cout<<"-1\n";
        return 0;
    }else{
        //cout<<ans[0]<<' '<<ans[1]<<' '<<ans[2]<<' '<<ans[3]<<"\n";
        int Min=min(min(ans[0],ans[1]),min(ans[2],ans[3]));
        if(ans[0]==Min){
            cout<<0<<' '<<0<<"\n";
        }else if(ans[1]==Min){
            cout<<n<<' '<<0<<'\n';
        }else if(ans[2]==Min){
            cout<<0<<' '<<m<<'\n';
        }else cout<<n<<' '<<m<<'\n';
    }
    return 0;
}
```

---

