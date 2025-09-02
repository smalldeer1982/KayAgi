# Captain Marmot

## 题目描述

Captain Marmot wants to prepare a huge and important battle against his enemy, Captain Snake. For this battle he has $ n $ regiments, each consisting of $ 4 $ moles.

Initially, each mole $ i $ ( $ 1<=i<=4n $ ) is placed at some position $ (x_{i},y_{i}) $ in the Cartesian plane. Captain Marmot wants to move some moles to make the regiments compact, if it's possible.

Each mole $ i $ has a home placed at the position $ (a_{i},b_{i}) $ . Moving this mole one time means rotating his position point $ (x_{i},y_{i}) $ $ 90 $ degrees counter-clockwise around it's home point $ (a_{i},b_{i}) $ .

A regiment is compact only if the position points of the $ 4 $ moles form a square with non-zero area.

Help Captain Marmot to find out for each regiment the minimal number of moves required to make that regiment compact, if it's possible.

## 说明/提示

In the first regiment we can move once the second or the third mole.

We can't make the second regiment compact.

In the third regiment, from the last $ 3 $ moles we can move once one and twice another one.

In the fourth regiment, we can move twice the first mole and once the third mole.

## 样例 #1

### 输入

```
4
1 1 0 0
-1 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-2 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-1 1 0 0
-1 1 0 0
-1 1 0 0
2 2 0 1
-1 0 0 -2
3 0 0 -2
-1 1 -2 0
```

### 输出

```
1
-1
3
3
```

# 题解

## 作者：QQH08 (赞：3)


~~话说这暴力题真恶心~~

首先看到n只有 $100$，只有 $4$ 个点，直接考虑暴力。

为了不在循环中写太长，直接预处理出每个老鼠旋转 $i$ 次 $90^ \circ $ 后的坐标。（注意每次转 $90^\circ$ 后，跟原点的横纵坐标差要互换）

然后枚举每只老鼠转几次，判断 $4$ 个点是否能构成正方形，跟答案取 $\min$。

判断正方形的条件：

1. $4$ 条边长度一样。（用欧几里得距离算即可）
2. 斜边长度的平方等于两倍边长的平方。
3. 任意一条边不为 $0$ 。

最后放上我~~自认为挺短~~的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=105;
int n;
ll x[N*4],y[N*4],p[10];
ll pf(ll x){return x*x;}
ll calc(int a,int b){
	return pf(x[a]-x[b])+pf(y[a]-y[b]);
}
int main(){
	scanf("%d",&n);
	for(int T=1;T<=n;T++){
		for(int i=0;i<4;i++){
			ll a,b,c,d;
			scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
			a-=c,b-=d;
			x[i*4]=a,y[i*4]=b;
			for(int j=1;j<4;j++)
				x[i*4+j]=-y[i*4+j-1],y[i*4+j]=x[i*4+j-1];
			for(int j=0;j<4;j++)x[i*4+j]+=c,y[i*4+j]+=d;
		}
		int ans=1e9;
		for(int i=0;i<4;i++)
			for(int j=4;j<8;j++)
				for(int k=8;k<12;k++)
					for(int l=12;l<16;l++){
						p[0]=calc(i,j),p[1]=calc(i,k),p[2]=calc(i,l),p[3]=calc(j,k),p[4]=calc(j,l),p[5]=calc(k,l);
						sort(p,p+6);
						if(p[0]==p[1]&&p[1]==p[2]&&p[2]==p[3]&&p[4]==p[5]&&p[0]*2==p[4]&&p[0]!=0)ans=min(ans,i+j+k+l-24);
					}
		if(ans==1e9)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Rain_G (赞：0)

我服了天才题目。

### 题目大意
给你四个点，可以分别绕一个点旋转，判断能否形成一个正方形，并输出要转几次。

### 正解
看数据范围可以想到先暴力求出每个点再枚举是否为正方形。暴力预处理点还算简单，重点在于怎么判断正方形。一开始想着边相等再判断直角，结果发现要 longlong 啊，精度直接飞了。

应该判断边相等再勾股定理，注意距离不要开根号，直接平方判断就行了，还有边不能为 $0$ 卡了我好久。感觉通过率被我刷下来了。

### 代码

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<math.h>
#include<algorithm>
#define int long long
using namespace std;
const int N = 2e3 + 20;
const int INF = 0x7f;
struct node{int x, y;};
int f( node a, node b) {return ( a.x - b.x) * ( a.x - b.x) +  ( a.y - b.y) * ( a.y - b.y);}
node q[N];
int a, b, c, d;
int T, sum[10], ans = INF;
void init(int qwq)
{
	q[qwq].x = a, q[qwq].y = b,q[qwq + 1].x = - q[qwq].y,q[qwq + 1].y = q[qwq].x,q[qwq + 2].x = - q[qwq + 1].y,q[qwq + 2].y = q[qwq + 1].x,q[qwq + 3].x = - q[qwq + 2].y,q[qwq + 3].y = q[qwq + 2].x;
	q[qwq + 0].x += c,q[qwq + 0].y += d,q[qwq + 1].x += c,q[qwq + 1].y += d,q[qwq + 2].x += c,q[qwq + 2].y += d,q[qwq + 3].x += c,q[qwq + 3].y += d;
}
bool check()
{
	if(sum[0] == sum[1] && sum[1] == sum[2] && sum[2] == sum[3] && sum[4] == sum[5] && sum[0] * 2 == sum[4] && sum[0] != 0)
		return 1;
	return 0;
}
signed main() {
	scanf("%lld", &T);
	while(T--)
	{
		for( int i = 0; i < 4; i++) {
			
			scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
			int qwq = i * 4;
			a -= c, b -= d;
			q[qwq].x = a, q[qwq].y = b;
			init(qwq);
		}
//		for( int i = 0 ; i< 4; i++)
//		{
//			for(int j = 0; j < 4; j++)
//			{
//				cout << q[i * 4 + j].x <<  " " << q[i * 4+j].y <<endl;
//			}
//		}
		ans = INF;
		for( int i = 0; i <= 3; i++)
			for( int j = 4; j <= 7; j++)
				for( int k = 8; k <= 11; k++)
					for( int l = 12; l <= 15; l++) 
					{
						sum[0] = f( q[i], q[j]);
						sum[1] = f( q[i], q[k]);
						sum[2] = f( q[i], q[l]);
						sum[3] = f( q[j], q[k]);
						sum[4] = f( q[j], q[l]);
						sum[5] = f( q[k], q[l]);
						sort( sum, sum + 6);
						if(check())
							ans = min( ans, i + j + k + l - 24);
					}
		if(ans == INF)
			ans = -1;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：鹤箩芠 (赞：0)

~~序：为什么要写这道题呢 ， 还不是因为写查错题了~~

思维真的固化了啊 ， 一道简单题 ， 却想了十几分钟 ，~~主要是我以为有什么好玩的性质~~ ， 事实上并没有 

我们考虑到 ，每个坐标只会有四个状态 ， 暴力枚举即可 ， 注意有的地方需要开$long long$

贴个代码 ? 

```cpp
struct node {ll x , y ;} dis[5][5] , h[5] ;

node roate (node x , int k) {
	node t ;
	t = x  ;
	t.x = h[k].x + h[k].y - x.y , t.y = h[k].y - h[k].x + x.x ;
	return t ;
}  
ll P[7] ;

bool cmpt (int a , int b) {
	return a < b ;
}

ll dist (node a , node b) {
	return (ll) ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)) ; 
}
bool check (int x , int typx , int y , int typy) {
	if (dis[x][typx].x == dis[y][typy].x && dis[x][typx].y == dis[y][typy].y) return false ;
    return true ; 
}
int main () {
	cin >> n ;
	while (n --) {	
		for (int i = 1 ; i <= 4 ; i ++) {
			int a , b ;
			cin >> a >> b >> h[i].x >> h[i].y ;
			dis[i][0].x = a , dis[i][0].y = b ;
		}
		for (int i = 1 ; i <= 4 ; i ++) {
			for (int j = 1 ; j <= 3 ; j ++) {
			    dis[i][j] = roate (dis[i][j - 1] , i) ; 
			}
		}
		int ans = 16 ;
		for (int A = 0 ; A <= 3 ; A ++) {
			for (int B = 0 ; B <= 3 ; B ++) {
				for (int C = 0 ; C <= 3 ; C ++) {
					for (int D = 0 ; D <= 3 ; D ++) {
						memset (P + 1 , 0 , sizeof P) ;
						if (!check (1 , A , 2 , B)) continue ;
						if (!check (1 , A , 3 , C)) continue ;
						if (!check (1 , A , 4 , D)) continue ;
						if (!check (2 , B , 3 , C)) continue ;
						if (!check (2 , B , 4 , D)) continue ;
						if (!check (3 , C , 4 , D)) continue ;
						P[1] = dist (dis[1][A] , dis[2][B]) ; 
						P[2] = dist (dis[1][A] , dis[3][C]) ;
						P[3] = dist (dis[1][A] , dis[1][D]) ;
						P[4] = dist (dis[2][B] , dis[3][C]) ;
						P[5] = dist (dis[2][B] , dis[4][D]) ;
						P[6] = dist (dis[3][C] , dis[4][D]) ;
						sort (P + 1 , P +  7) ;
						if (P[1] == P[2] && P[3] == P[2] && P[3] == P[4] && P[4] == P[1] && P[1] && P[5] == P[6]) ans = min (ans , A + B + C + D) ;
					// 这里做了好多无效判断 ， 大佬们不要嘲笑 ， 因为莫名其妙wa 了 不少次 /kk
					}
				}
			}
		}
		if (ans == 16) cout << -1 << endl ;
		else cout << ans << endl ;
	}
	return 0 ;
}
```



---

