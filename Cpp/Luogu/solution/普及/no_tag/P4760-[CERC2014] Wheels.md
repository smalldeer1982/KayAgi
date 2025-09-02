# [CERC2014] Wheels

## 题目描述

一个非常重要和复杂的机器由$n$个轮子组成，编号为$1,2,…,n$。它们其实是齿轮，但是齿太小了，我们可以把它们近似看成成平面上的圆。

每一个齿轮都能围绕它的中心旋转。

两个齿轮不会重叠（因为它们内部没有共同的点），但它们可以互相接触。

如果两个齿轮相互接触，其中一个齿轮转动，另一个齿轮也随之转动，因为它们的齿被卡在一起。

一个力作用于齿轮1（并且力没有作用于其他齿轮），使它以每分钟转一圈的速度顺时针旋转。计算其他齿轮的运动速度。你可以假设机器没有卡住（运动在物理理论上是可以的）。

## 样例 #1

### 输入

```
1
5
0 0 6
6 8 4
-9 0 3
6 16 4
0 -11 4
```

### 输出

```
1 clockwise
3/2 counterclockwise
2 counterclockwise
3/2 clockwise
not moving```

# 题解

## 作者：_Goodnight (赞：2)

### 物理必修二，由线速度相等可推出下列式子
 $v_i=v_0*r_0/r_i$ 
 
#### 有了公式，思路就清晰了：对于每个轮子，我们都需要查看它是否带动与它相切的轮子是否已经被之前的轮子带动了，如果没有被带动，我们就把它带动起来，计算他的速度以及它的转动方向
 
 注意： ```clockwise```   顺时针

```	
counterclockwise 逆时针
```


一个顺时针的齿轮 ```i``` 所带动的齿轮 ```j``` 是逆时针转的 这里可以用 ```clock``` 记录， -1 为暂时还未搜索到，也就时目前还没转动，然后用取反进行转向，用结构体存储每一个齿轮，每次搜索找到相切的并且没更新的，计算这个齿轮的速度。

然后我们就可以用广度优先搜索去找他啦
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 2000000000
typedef unsigned long long ull;
struct circle {
	int x=0, y=0, r=0;
	int clock = -1;
	int up = 1, down = 1;
	//0 shunshizhen -1 chushihua 1 nishizhen
}a[1010];
int n;
queue<circle> q;
//summary:
// 判断2圆是否相切
bool IsCircleQIE(circle a, circle b) {
	int d = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
	if (d <= (a.r + b.r)*(a.r+b.r)) {
		return 1;
	}
	return 0;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
pair<int, int> fenshu(int up, int down) {
	int d=gcd(up, down);
	return { up / d,down / d };
}
void read() {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].x >> a[i].y >> a[i].r;
			a[i].clock = -1, a[i].up = a[i].down = 1;
		}
}
void out() {
	for (int i = 1; i <= n; i++) {
		if (a[i].clock != -1) {
			cout << a[i].up;
			if (a[i].down != 1) {
				cout << "/" << a[i].down;
			}
			cout << (a[i].clock==1 ? " counterclockwise" : " clockwise")<<endl;
			
		}
		else {
			cout << "not moving"<<endl;
		}
	}
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		read();
		a[1].clock = 0;
		q.push(a[1]);
		while (!q.empty()) {
			circle u = q.front(); q.pop();
			for (int i = 1; i <= n; i++) {
				if (a[i].clock == -1) {
					if (IsCircleQIE(u, a[i])) {
						a[i].clock = !u.clock;
						pair<int, int> t = fenshu(u.r * u.up, u.down * a[i].r);
						a[i].up = t.first, a[i].down = t.second;
						q.push(a[i]);
					}
				}
			}
		}
		out();
	}

}
```


---

## 作者：HRLYB (赞：2)

### 本题题面存在的问题：题目中的输出格式表述不明。

![](https://s2.ax1x.com/2019/06/17/VbJIJS.png)

题目说输出“ p/q clockwise 或 p/q counterclockwise ”，而没有说明什么情况下输出哪一个。按照题目的意思，以样例为例，应该是这样的：

	2号和3号轮贴着1号轮，输出countclockwise；4号轮贴着2号轮，输出clockwise；也就是说，第k层输出countclockwise则第k+1层输出clockwise
    
    希望管理员大大能够稍微修改一下题面，使题目更方便理解！

好的，接下来我们来看看题目。

~~毒瘤题啊！~~

为什么这么说呢？第一，它只有两个测试点；第二，只过了一个测试点，竟然是0分！


虽然说是黄题，但代码细节很多，而且模拟想来也不简单。

主要就是各个齿轮的运动状态的关系（齿轮半径与齿轮转速成反比），我们通过模拟可得，

```cpp
		lef[i]=lef[x]*p[x].r;
                righ[i]=righ[x]*p[i].r;
                num[i]=(num[x]==1?0:1);
                int g=gcd(lef[i],righ[i]);
                lef[i]/=g;
                righ[i]/=g;//lef表示分子，righ表示分母，num是一个标记数组，用于标记层数
                
              
```



#### 而且我们看到，由于有层与层之间的关系，所以大可像写spfa和BFS时一样，用queue实现层层递进的关系

还有，不知道为什么，用STL来写queue时挂了，怎么也调不出来，只好手写。

```cpp
#include<bits/stdc++.h>
#define maxn 1010
using namespace std;
struct point{
	int x,y,r;
}p[maxn];
int num[maxn],lef[maxn],righ[maxn];
int q[maxn],headd,taill;//手写队列基本操作
int T,n;
int gcd(int x,int y){return y?gcd(y,x%y):x;}//gcd（最大公约数），保证最后输出的结果互质
void operation(){
	int x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&p[i].x ,&p[i].y ,&p[i].r );
	}
	memset(lef,0,sizeof lef);//一定要记得初始化，不然上一次的结果可能会对下一次造成影响
	lef[1]=1;
	righ[1]=1;
	num[1]=1;
    	headd=0,taill=0;//没写这个T了好多次。。
	q[taill++]=1;
        while(headd!=taill){
            int x=q[headd++];
            for(int i=1;i<=n;i++){
                if(x!=i&&!lef[i]&&(long long)((p[i].x-p[x].x)*(p[i].x-p[x].x)+(p[i].y-p[x].y)*(p[i].y-p[x].y))==(long long)(p[i].r+p[x].r)*(p[i].r+p[x].r)){//平方可能是一个很大的数，所以要记得开long long
					lef[i]=lef[x]*p[x].r;
                    righ[i]=righ[x]*p[i].r;
                    num[i]=(num[x]==1?0:1);//num用来描述现在是第几轮被搜到的点，然后如上所述输出
                    int g=gcd(lef[i],righ[i]);
                    lef[i]/=g;//保证输出互质
                    righ[i]/=g;
                    q[taill++]=i;
                }
            }
        }
	printf("1 clockwise\n");
	for(int i=2;i<=n;i++){
		if(!lef[i])printf("not moving\n");//左边没有赋值，说明没有移动
		else{
            if(righ[i]==1){
            	printf("%d ",lef[i]);
            }else{
                printf("%d/",lef[i]);
                printf("%d ",righ[i]);
            }
            if(num[i])printf("clockwise\n");
            else printf("counterclockwise\n");//平淡无奇的输出
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T){
		operation(); 
		T--;
	}
	return 0;
} 
```




---

## 作者：内拉组里 (赞：0)

# Thoughts：

- 根据小学五年级就学过的圆与圆位置关系判断可知，

	满足以下条件的两个齿轮 $ (x1,y1,r1) $ 和 $ (x2,y2,r2) $ 啮合：

	$$  (x1 - x2)^2 + (y1 - y2)^2 = (r1 + r2)^2  $$ 

	暴力匹配即可。

- 根据小学三年级奥数就学过的齿轮问题可知，

	对于啮合的两个半径分别为 $ r_1 $ 和 $ r_2 $ 的齿轮，当前者以 $ v_1 $ 的速度转动时，

	将会带动后者以 $ v_2 = \cfrac{v_1 r_1}{r_2} $ 的速度反方向转动。

接下来把所有齿轮丢进去跑一遍类似拓扑序的 **dp**。

对于没有与任何齿轮啮合的齿轮，输出 `not moving` 即可。

# Analyses：

> 总时间复杂度 $ \Theta (T N^2) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Details：

> - 记录答案时记得约分，否则**可能**会乘爆。
> - 多测记得清空。

# Code：

```cpp
#include	<algorithm>
#include	<iostream>
#include	<cstring>
#include	<queue>
using namespace std;
constexpr int maxn = 1e3+4;

struct
{
	int x, y, r;
}
a[maxn];
int t, n;
struct
{
	int p, q, dir;
}
ans[maxn];
queue<int> q;
int vis[maxn];

signed main (void)
{
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i].x >> a[i].y >> a[i].r;
		q.push(1);
		ans[1] = {1, 1, 1};
		memset (vis, 0, sizeof vis);
		vis[1] = 1;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			auto [x1, y1, r1] = a[u];
			auto &[p, q, dir] = ans[u];
			int gcd = __gcd (p, q);
			p /= gcd;
			q /= gcd;
			for (int v = 1; v <= n; v++) if (!vis[v])
			{
				auto [x2, y2, r2] = a[v];
				if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) == (r1 + r2) * (r1 + r2))
				{
					::q.push(v);
					vis[v] = 1;
					ans[v] = {p * r1, q * r2, !dir};
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (!vis[i])
				cout << "not moving" << endl;
			else
			{
				auto [p, q, dir] = ans[i];
				if (q == 1)
					cout << p << ' ';
				else
					cout << p << '/' << q << ' ';
				if (dir)
					cout << "clockwise" << endl;
				else
					cout << "counterclockwise" << endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：tmpliyijiang (赞：0)

## 关于题目表述
`clockwise` 表示顺时针，`counterclockwise` 表示逆时针。
## 思路
注意到 $n$ 较小，并且齿轮之间是链式关系，所以可以把 $n$ 个齿轮看作一张 $n$ 个点的图，在相接触的圆之间连 $1$ 条边。将问题变形之后，就可以上 bfs 大法！

对于 bfs 算法中每一个从队列中取出的队首元素 $tmp$，遍历 $n$ 个点，若两圆外切，即半径之和等于两圆心的欧拉距离，且未被操作（由题目中机器没有卡住的假设），即可对这个点进行操作。

- 速度的操作

设第 $tmp$ 个点的分子为 $q_1$，分母为 $q_2$，将其分子修改为 $r_{tmp}\times q_1$，将分母修改为 $r_i \times q_2$，再对分数进行化简。

- 方向的操作

将第 $i$ 个点的方向修改为第 $tmp$ 个点的反方向，可以用位运算实现。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p{//点的结构体
	int x,y,r,n,m,cnt;
}a[10005];
inline int gcd(int a,int b){// p/q 为最简分数
	return ((!b)?a:gcd(b,a%b));
}
queue<int> q;
int t,n;
void solve(){
	scanf("%d",&n);
	for(register int i=0;i<n;i++){
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
		a[i].m=0,a[i].n=0,a[i].cnt=0;
	}
	a[0].n=1,a[0].m=1;//初始化
	q.push(0);
	while(!q.empty()){// bfs 大法
		int tmp=q.front();
		q.pop();
		for(register int i=0;i<n;i++){
			if((tmp!=i)&&(!a[i].n)&&((a[tmp].r+a[i].r)*(a[tmp].r+a[i].r)==(a[i].x-a[tmp].x)*(a[i].x-a[tmp].x)+(a[i].y-a[tmp].y)*(a[i].y-a[tmp].y))){
				a[i].n=a[tmp].r*a[tmp].n,a[i].m=a[tmp].m*a[i].r,a[i].cnt=(a[tmp].cnt+1)&1;
				int k=gcd(a[i].n,a[i].m);
				if(k-1)a[i].n/=k,a[i].m/=k;
				q.push(i);
			}
		}
	}
	for(register int i=0;i<n;i++){//输出
		if(!a[i].n)printf("not moving\n");
		else {
			if(a[i].m-1)printf("%d/%d",a[i].n,a[i].m);
			else printf("%d",a[i].n);
			if(!a[i].cnt)printf(" clockwise\n",a[i].n,a[i].m);
			else printf(" counterclockwise\n",a[i].n,a[i].m);
		}
	}
}
signed main(){
	scanf("%d",&t);
	for(register int i=0;i<t;i++)solve();
	return 0;
}

```

---

