# Cubes

## 题目描述

One day Petya got a set of wooden cubes as a present from his mom. Petya immediately built a whole city from these cubes.

The base of the city is an $ n×n $ square, divided into unit squares. The square's sides are parallel to the coordinate axes, the square's opposite corners have coordinates $ (0,0) $ and $ (n,n) $ . On each of the unit squares Petya built a tower of wooden cubes. The side of a wooden cube also has a unit length.

After that Petya went an infinitely large distance away from his masterpiece and looked at it in the direction of vector $ v=(v_{x},v_{y},0) $ . Petya wonders, how many distinct cubes are visible from this position. Help him, find this number.

Each cube includes the border. We think that a cube is visible if there is a ray emanating from some point $ p $ , belonging to the cube, in the direction of vector $ -v $ , that doesn't contain any points, belonging to other cubes.

## 样例 #1

### 输入

```
5 -1 2
5 0 0 0 1
0 0 0 0 2
0 0 0 1 2
0 0 0 0 2
2 2 2 2 3
```

### 输出

```
20```

## 样例 #2

### 输入

```
5 1 -2
5 0 0 0 1
0 0 0 0 2
0 0 0 1 2
0 0 0 0 2
2 2 2 2 3
```

### 输出

```
15```

# 题解

## 作者：jucason_xu (赞：1)

首先我们通过翻转坐标系强制要求光的方向是正方向。翻转坐标系就翻转矩阵的对应维度就可以了。

然后我们发现，如果不考虑遮挡关系，只考虑平面，对于每个位置的方块而言，能照到它的光是一段区间。就是能照到 $(i-1,j)$ 和能找到 $(i,j-1)$ 的光。

我们考虑把光映射到光所在直线在 $y$ 轴上的投影。那么经过点 $(x,y)$ 的光就映射到 $y-\dfrac{v_yx}{v_x}$，我们就映射到了 $y$ 轴的一个区间 $[l_{x,y},r_{x,y}]$，只要这个区间里有光，当前位置就能被照到。

同时我们容易发现，每个方块所对应的区间是等长的。不过这不重要。

我们把所有的光区间端点离散化下来。然后对于 $(x,y)$ 的位置来说，只要在当前高度 $[l_{x,y},r_{x,y}]$ 上任意的点有光就可以。而对于高度而言有没有光显然是存在单调性的。

同时遮挡关系也是存在单调性的。__处在当前点右边或者上方的点一定遮挡不了当前的点。__ 那么我们考虑从左下角一行一行扫，开一棵线段树记录，对于每个光区间，有多少高度已经完全没有光了。

这样，我们每次在线段树上查询区间最小值（只要有即可），找到当前的位置有多少方块被挡住了，用 $a_{i,j}$ 减得到没挡住的。然后区间修改，自己区间上的所有数对 $a_{i,j}$ 取 $\max$（这些光都被遮挡了）。

所以，我们只要实现线段树区间取 $\max$，查询区间最小值，这是容易的。

同时注意，这题卡精度，我的方法是实现了一个 `struct`，然后重载了小于号，这样的好处是依旧可以使用 `sort` 和 `lower_bound` 而不掉精度。离散化的时候要 `unique`，否则线段树区间会出问题，这个功能我不知道要重载什么，但是可以直接自己手写。

复杂度 $O(n^2\log n)$

```cpp
const ld eps=1e-6;
int n,a[1005][1005],vx,vy,m; 
int l[1005][1005],r[1005][1005];
struct mydouble{
	ld x;
	bool operator ==(const mydouble b)const{
		return fabs(x-b.x)<=eps;
	}
	bool operator <(const mydouble b)const{
		return b.x>x&&!(fabs(b.x-x)<=eps);
	}
};
mydouble L[1005][1005],R[1005][1005],x[2000005],y[2000005];
struct node{
	int l,r,m,tg;
}sg[8000005];
inline void init(int i,int l,int r){
	sg[i].l=l,sg[i].r=r,sg[i].m=0,sg[i].tg=0;
	if(l==r)return;
	init(i<<1,l,(l+r)>>1);
	init(i<<1|1,((l+r)>>1)+1,r);
}
inline void push(int i){
	if(!sg[i].tg)return;
	sg[i].m=max(sg[i].m,sg[i].tg);
	if(sg[i].l!=sg[i].r){
		sg[i<<1].tg=max(sg[i<<1].tg,sg[i].tg);
		sg[i<<1|1].tg=max(sg[i<<1|1].tg,sg[i].tg);
	}sg[i].tg=0;
}
inline void modify(int i,int l,int r,int x){
	push(i);
	if(sg[i].l>r||sg[i].r<l)return;
	if(sg[i].l>=l&&sg[i].r<=r){
		sg[i].tg=max(sg[i].tg,x);
		return push(i);
	}modify(i<<1,l,r,x);
	modify(i<<1|1,l,r,x);
	sg[i].m=min(sg[i<<1].m,sg[i<<1|1].m);
}
inline int qry(int i,int l,int r){
	push(i);
	if(sg[i].l>r||sg[i].r<l)return 1e9;
	if(sg[i].l>=l&&sg[i].r<=r)return sg[i].m;
	int res=min(qry(i<<1,l,r),qry(i<<1|1,l,r));
	sg[i].m=min(sg[i<<1].m,sg[i<<1|1].m);
	return res;
}
inline void chdir(){
	if(vx<0){
		rep(j,1,n)rep(i,1,n/2)swap(a[i][j],a[n-i+1][j]);
		vx=-vx;
	}
	if(vy<0){
		rep(i,1,n)rep(j,1,n/2)swap(a[i][j],a[i][n-j+1]);
		vy=-vy;
	}
}
inline ld calc(int x,int y){
	return y-1.0*x*vy/vx;
}
inline void calclr(){
	rp(i,n)rp(j,n){
		if(vx!=0){
			L[i][j].x=calc(i,j-1);
			R[i][j].x=calc(i-1,j);
			x[++m]=L[i][j];
			x[++m]=R[i][j];
		}else{
			L[i][j].x=i-1,R[i][j].x=i;
			x[++m].x=i-1,x[++m].x=i;
		}
	}
	sort(x+1,x+1+m);
	int cnt=1;y[cnt]=x[1];
	rep(i,2,m)if(!(x[i-1]==x[i]))y[++cnt]=x[i];
	m=cnt;
	rep(i,2,m)x[i]=y[i];
	rp(i,n)rp(j,n){
		l[i][j]=lower_bound(x+1,x+1+m,L[i][j])-x;
		r[i][j]=lower_bound(x+1,x+1+m,R[i][j])-x-1;
	}init(1,1,m);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>vx>>vy;
	rp(i,n)rp(j,n)cin>>a[i][j];
	chdir();
	calclr();
	ll ans=0;
	rp(i,n)rp(j,n)if(a[i][j]){
		ans+=max(0,a[i][j]-qry(1,l[i][j],r[i][j]));
		modify(1,l[i][j],r[i][j],a[i][j]);
	}cout<<ans<<endl;
	return 0;
}
//Crayan_r
```


---

