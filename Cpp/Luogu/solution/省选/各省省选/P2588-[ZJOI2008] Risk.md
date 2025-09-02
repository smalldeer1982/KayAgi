# [ZJOI2008] Risk

## 题目描述

经过连续若干年的推广，Risk这个游戏已经风靡全国，成为大众喜闻乐见的重要娱乐方式。Risk这个游戏可以理解为一种简易的策略游戏，游戏者的目的是占领所有的土地。由于游戏规则的规定，只要两个国家相邻，就认为两个国家有交战的可能性。我们现在希望知道在当前的局面下，哪些国家之间有交战的可能性。注意，我们认为只有当两个国家的国界线有公共边的时候才认为相邻，若两个国家的领土只有公共点，则认为两个国家不相邻。

每一个国家的边界由一系列线段组成，保证这个边界是一个简单多边形，即严格不自交。为了定位每个国家的位置，我们还给出每个国家最庞大的一支军队的位置，保证这个位置一定出现在某一个形内，而不是出现在某条边界上。


## 样例 #1

### 输入

```
4 12
3 2
11 8
12 17
1 19
0 0 10 0
10 0 20 0
20 0 20 10
20 10 20 20
20 20 10 20
10 20 0 20
0 20 0 10
0 10 0 0
10 0 10 10
0 10 10 10
20 10 10 10
10 20 10 10
```

### 输出

```
2 2 4
2 1 3
2 2 4
2 1 3
```

## 样例 #2

### 输入

```
4 16
170 13
24 88
152 49
110 130
60 60 140 60
140 60 140 140
140 140 60 140
60 140 60 60
0 0 200 0
200 0 200 200
200 200 0 200
0 200 0 0
40 40 160 40
160 40 160 160
160 160 40 160
40 160 40 40
20 20 180 20
180 20 180 180
180 180 20 180
20 180 20 20
```

### 输出

```
1 2
2 1 3
2 2 4
1 3
```

# 题解

## 作者：xtx1092515503 (赞：10)

# [Portal](https://www.luogu.com.cn/problem/P2588)

这里介绍的方法同[[IOI2007] flood 洪水](https://www.luogu.com.cn/problem/P4646)中[我的题解](https://www.luogu.com.cn/blog/Troverld/solution-p4646)的方法一致，大家也可以结合链接中的题解里的图像理解，~~顺便把那题刷了练手~~。

本题我的算法主要分两步：

1. 求出每个多边形的边界

2. 求出每个点归属于哪个多边形

下面将逐一讲解。

可以发现，我们如果将一个点连出的所有线段**按照幅角排序**后，相邻的两条线段必位于同一多边形上。于是，对于第 $i$ 条边 $(u,v)$，我们将其拆成两条边，即边 $2i:(u\rightarrow v)$ 与边 $2i+1:(v\rightarrow u)$，分别将其幅角和编号打成 ```pair``` 扔到 $u$ 和 $v$ 分别对应的一个 ```vector``` 中保存。

之后，我们遍历每个 ```vector```，将内部元素按照幅角排序。我们定义一条边 $i$ 的**右侧**为 $i$，**左侧**为 $i\operatorname{xor}1$。可以发现，$2i$ 的右侧等价于 $2i+1$ 的左侧，反之亦然——这恰是我们想要的。于是，我们遍历 ```vector``` 中每一对相邻的元素（**注意其首尾的元素实质上也是相邻的**），并合并前面元素的右侧和后面元素的左侧（即标记它们处于同一个多边形内）。

为了准确求出多边形的边界，我们令（前面元素的右侧）的**后继**是（后面元素的左侧），并令（后面元素的左侧）的**位置**是当前 ```vector``` 代表的位置。这样，所有多边形边缘节点就构成了一个**环状链表**，链表上依次**逆时针**（为什么一定是逆时针呢？因为我们是令右侧的后继是左侧，画出图来就会发现它就是按照逆时针排布的）储存了多边形顶点的位置。

放一下上述代码。

```cpp
const double pi=acos(-1);
int n,m,cnt,nex[8010],tot;
struct Vector{
	int x,y;
	Vector(int X=0,int Y=0){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const double &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const double &v){return Vector(u.x/v,u.y/v);}
	friend int operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}//cross times
	friend int operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}//point times
	double operator !()const{return atan2(y,x);}
	friend bool operator <(const Vector &u,const Vector &v){return !u<!v;}
	void read(){scanf("%d%d",&x,&y);}
	void print(){printf("(%d,%d)",x,y);}
}p[610],q[8010],pos[8010];
typedef Vector Point;
map<pair<int,int>,int>mp;
vector<pair<Vector,int> >v[8010];
void func(int x){
	sort(v[x].begin(),v[x].end());
	for(int i=0;i<v[x].size();i++){
		int U=v[x][i].second,V=v[x][(i+1)%v[x].size()].second^1;
		pos[V]=q[x],nex[U]=V;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)p[i].read(); 
	for(int i=0;i<m;i++){
		Vector U,V;
		U.read(),V.read();
		if(mp.find(make_pair(U.x,U.y))==mp.end())mp[make_pair(U.x,U.y)]=++cnt,q[cnt]=U;
		if(mp.find(make_pair(V.x,V.y))==mp.end())mp[make_pair(V.x,V.y)]=++cnt,q[cnt]=V;
		v[mp[make_pair(U.x,U.y)]].push_back(make_pair(V-U,i<<1));
		v[mp[make_pair(V.x,V.y)]].push_back(make_pair(U-V,i<<1|1));
	}
}
```

在求出上述的环状链表后，求出多边形的边界就变得很简单了——直接依次遍历一遍，并记录 $col_i$ 表示第 $i$ 个点归属于哪个多边形即可。

但是，假如你敲出上述代码后，会发现它不仅给出了所有多边形的**内边界**，还把**外边界**一起给出来了！（带进第一组样例，会发现它给出了四个小正方形和最外面的大正方形）

那咋办呢？还得特判内外吗？

没关系！我们之前特意强调了，多边形上的点是按照**逆时针**排布的。但是，这仅限于内边界！外边界上的点反而是依照**顺时针**排布的！

于是我们需要找到一个判断顺逆排布的算法。这很简单，求一下它的面积（此处不能取绝对值），然后看面积正负，正则为逆时针，负则为顺时针，这是因为向量叉积的定义如此。

此部分的代码：

```cpp
int col[8010];
typedef vector<Point> Points;
bool side[8010];//1:outer border 0:inner border
Points u[8010];
int main(){
 	for(int i=1;i<=cnt;i++)func(i);
 	for(int i=0;i<(m<<1);i++){
		if(col[i])continue;
		tot++;
		int x=i;
		do{col[x]=tot,u[tot].push_back(pos[x]),x=nex[x];}while(x!=i);
	}
	for(int i=1;i<=tot;i++){
		double all=0;
		for(int j=0;j<u[i].size();j++)all+=u[i][(j+1)%u[i].size()]&u[i][j];
		side[i]=all>0;
	}
}
```

那我们保留外边界有何用呢？这时我们看到第二组样例，就会发现它是一种套娃式的状况。我们需要外边界帮助我们求出每个多边形内部与哪些多边形相交。

（说法有点迷惑是不是？这里我们统一定义一下，**内边界**指的是多边形外部的边界（因为其内部是多边形），**外边界**指的是内部的边界（因为其外部是多边形）——写代码时就这么写的，再改就改不过来了）

那么我们怎么处理某个外边界到底对应着哪个内边界呢？

我们注意到，某个外边界一定被套在它所对应的内边界内部。但是它可能不止被套在一个内边界内部（考虑第二组样例，最里层的外边界外面套了三层内边界），而明显套着它的内边界们自身也是一层套一层的（禁 止 套 娃）。于是，我们只需要找出套的最里层的一个内边界，它直接套着此外边界。

于是我们现在需要一个程序来判断一个边界是否套在另一个边界内部。因为很明显本题中边界不可能相交，所以我们内部的那个边界仅需判断边界上的一个点是否套在内部即可。

这里有一种方法：射线法——

我们从待测点出发，沿 $x$ 轴正方向引一条射线（或者不管哪个方向都行，但是为了代码方便这里选 $x$ 轴正方向）。则我们可以看到，若该射线与奇数条线段相交，它在多边形内；偶数条，则在形外。

代码很好写，这里主要回答两个疑问：

1. 假如射线刚好与一条线段重合咋办？

画出图来，就会发现这条线段可以被忽略（更准确地说，相交两次等于没相交）

2. 假如射线刚好与一个角重合咋办？

这种情形比较烦人，我们需要判断两条直线都在同一侧还是在异侧。假如是同侧，直接忽略；假如是异侧，算相交一次。(但实际上我没有判断这种情况就过了）

此部分代码：

```cpp
int outer[8010];//only if it's an inner border, this stands for the exact outer border for i.
Points u[8010];
bool in(int id,Point ip){//check if a point is exactly in a figure, no matter it's a outer border or a inner
	bool ret=false;
	for(int i=0,j=1;i<u[id].size();i++,j++,j%=u[id].size()){
		Point I=u[id][i],J=u[id][j];
		if(!(((I.y>ip.y)^(J.y>ip.y))))continue;//have no intersection with this segment
		if(I.y>J.y)swap(I,J);//ensure the side of inequalitic symbol
		if((ip.x-I.x)*(J.y-I.y)==(J.x-I.x)*(ip.y-I.y))return false;
		if((ip.x-I.x)*(J.y-I.y)>(J.x-I.x)*(ip.y-I.y))continue;//calculate whether the intersection is on the right of the point or not
		ret^=1;
	}
	return ret;
}
int main(){
	for(int i=1;i<=tot;i++){
		if(side[i])continue;
		for(int j=1;j<=tot;j++){
			if(!side[j]||!in(j,u[i][0]))continue;
			if(!outer[i])outer[i]=j;
			else if(in(outer[i],u[j][0]))outer[i]=j;
		}
	}
}
```

下面就要判断一个点到底在哪个多边形内了。我们只需要判断一个点是否在一个内边界内，并且在所有对应着它的外边界外即可。

此部分代码：

```cpp
bool ok[8010];
int id[8010];
int main(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=tot;j++)if(side[j])ok[j]=true;
		for(int j=1;j<=tot;j++){
			if(side[j]&&!in(j,p[i]))ok[j]=false;
			if(outer[j]&&in(j,p[i]))ok[outer[j]]=false;
		}
		for(int j=1;j<=tot;j++)if(ok[j])id[j]=i;
	}
}
```

最终就是求答案部分了。求答案我们从**边**的角度来看，即，对于边 $i$，它所对应的两条边 $2i$ 和 $2i+1$，会分别处于两个不同的边界（分别编号为 $col_{2i}$ 和 $col_{2i+1}$）上，而这两个边界所对应的多边形被算作相邻。

此部分代码：

```cpp
vector<int>res[610];
#define corr(i) id[outer[i]?outer[i]:i]
int main(){
	for(int i=0;i<(m<<1);i++){
		int U=col[i],V=col[i^1];
		U=corr(U),V=corr(V);
		if(U&&V)res[U].push_back(V);
	}
	for(int i=1;i<=n;i++){
		sort(res[i].begin(),res[i].end()),res[i].resize(unique(res[i].begin(),res[i].end())-res[i].begin());
		printf("%d ",res[i].size());for(auto j:res[i])printf("%d ",j);puts("");
	}
}
```
最后只需要把上面给出的所有代码块缝合起来即可得到完整程序。

时间复杂度 $O(n^2)$，瓶颈在于求外边界对应的内边界和求点对应的多边形。假如有人想到更好的对应方法可以私信我，~~更好的方法是自己写一篇题解然后私信我让我观摩观摩~~

觉得写得好不妨点个赞罢。

---

