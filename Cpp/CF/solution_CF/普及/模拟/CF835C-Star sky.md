# Star sky

## 题目描述

在空中设置笛卡尔坐标系。有 $n$ 个星星，第 $i$ 个星星有坐标 $(x_i,y_i)$ 和最大亮度 $c$ ，每个星星有个初始亮度 $s_i(0\leq s_i\leq c)$   
随着时间推移，星星的亮度也在变化。第0时刻亮度为 $s_i$ 。若 $t$ 时刻亮度为 $x$ ，则 $t+1$ 时刻为 $x+1,x+1\leq c$ 否则为0  
你想观察天空 $q$ 次，第 $i$ 你会在 $t_i$ 时刻观察一个和坐标轴平行的矩阵范围，矩阵左下角为 $(x_{1i},y_{1i})$ ，右上角为 $(x_{2i},y_{2i})$ 。对于每一次观察，你都想知道范围内星星亮度总和  
若星星在边界上也算作内部

## 样例 #1

### 输入

```
2 3 3
1 1 1
3 2 0
2 1 1 2 2
0 2 1 4 5
5 1 1 5 5
```

### 输出

```
3
0
3
```

## 样例 #2

### 输入

```
3 4 5
1 1 2
2 3 0
3 3 1
0 1 1 100 100
1 2 2 4 4
2 2 1 4 7
1 50 50 51 51
```

### 输出

```
3
3
5
0
```

# 题解

## 作者：Akoasm_X (赞：6)

比较简单直接的做法

观察到最大亮度 C 小于等于10，并且发现 所有的星星 亮度周期就是 C+1。x，y的范围比较小，再加上一维 C 。对于时间T，答案对应T % （C + 1），然后就是代码实现了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 105;
int n,m,c;
int sum[11][maxn][maxn];

inline int read() 
{
    int x = 0 , f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
}

int main()
{
	n = read();m = read();c = read();
	for(int i=1;i<=n;i++)
	{
		int x = read(),y = read(),s = read();
		for(int j=0;j<=c;j++) sum[j][x][y] += (s + j) % (c + 1);
	}
	for(int k=0;k<=c;k++)
		for(int i=1;i<=100;i++)
			for(int j=1;j<=100;j++)
				sum[k][i][j] += sum[k][i-1][j] + sum[k][i][j-1] - sum[k][i-1][j-1];
	for(int i=1;i<=m;i++)
	{
		int t = read(),x1 = read(),y1 = read(),x2 = read(),y2 = read();
		t %= (c+1);
		printf("%d\n",sum[t][x2][y2] - sum[t][x1-1][y2] - sum[t][x2][y1-1] + sum[t][x1-1][y1-1]);
	}
	return 0;
}
```


---

## 作者：Muruski (赞：4)

跟楼上那位大佬思路基本一样~~可是不是非常详细...~~

我就写一下我的看法...

**这是我们校内模拟ACM弄得一道题...**

题意：

天上有很多星星，每个星星有他自己的坐标和初始亮度

每个星星的亮度在一秒内会加一，如果大于最大亮度C就会变为0

观察星星，给出视野范围（矩形）的左下角和右上角，以及观察的时间

问视野中星星亮度总和是多少。

楼上那位大佬说第一眼二维树状数组，我第一眼线段树，（因为我不知道什么是二维树状数组）~~对没错我是蒟蒻欸嘿嘿~~

思路：

1. 很显然他这个星星亮度是变化的，所以我们需要一个change来记录星星的亮度状态

1. 再根据一手题意利用二维前缀和求这个视野（该矩形区间）的和，并且由于数组是不用更新的，所以直接预处理前缀和

1. 用sum [ i ] [ j ] [ k ]  表示左下角 ( 0 , 0 ) 到右上角 ( i , j ) 统计亮度为k的星星的个数

1. 再通过一个容斥原理得出一个类似于状态转移方程的式子：

```cpp
sum[i][j][k] = sum[i-1][j][k] +sum[i][j-1][k] -sum[i-1][j-1][k];
```
5. 在询问的时候我们就遍历所问区间中从1~c的所有亮度的总和，对其求和即为答案 

也没有多详细...

上代码叭，代码里也有一些解释

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN=105;
int n,m,c;
int sum[MAXN][MAXN][15];
void init(){
    for(int i=1;i<=100;i++){
        for(int j=1;j<=100;j++){
            for(int k=0;k<=c;k++){//数据不大三重for欸嘿嘿...
                sum[i][j][k]+=sum[i-1][j][k]+sum[i][j-1][k]-sum[i-1][j-1][k];//k是星星的亮度...
            }
        }
    }
}//预处理...
int main(){
    while(cin>>n>>m>>c){//while里面如果用scanf我不知道加不加那个“~”，所以直接用cin，速度不会太慢，反正数据也不大欸嘿嘿...
        memset(sum,0,sizeof(sum));
        for(int i=0;i<n;i++){
            int x,y,z;
            cin>>x>>y>>z;
            sum[x][y][z]++;
        }
        init();
        for(int i=0;i<m;i++){
            int change,x1,x2,y1,y2;
            int ans=0;
            cin>>change>>x1>>y1>>x2>>y2;
            for(int k = 0;k<=c;k++){
                //注意边界...
                //遍历所有亮度的总和...
                int num=sum[x2][y2][k]-sum[x1-1][y2][k]-sum[x2][y1-1][k]+sum[x1-1][y1-1][k];
                ans+=((k+change)%(c+1))*num;//求个和，就是答案啦...
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}

```
参考了一位大佬的博客，不过我是真的找不到了，有知道的话私信我，我加上链接，抱歉抱歉。

顺便求管理大大通过

---

## 作者：KXY_Moon (赞：1)

#### 前缀和好题

[前缀和-My.](https://www.luogu.com.cn/article/s4yfk459)

[前缀和-oi wiki.](https://oi-wiki.org/basic/prefix-sum/)
## 解法

设 $F_{i,j,k}$ 为在第 $k$ 时刻且当矩阵右上角为 $(x_i,y_j)$ 时的星星亮度之和。

再构造 $P_{A_{i,j,k}}$ 为坐标系中点 $A(x_i,y_j)$ 在第 $k$ 时刻的亮度。

根据二维前缀和：

$$sum_{i,j}=sum_{i,j-1}+sum_{i-1,j}-sum_{i-1,j-1}+A_{i,j}$$

那么有：

$$F_{i,j,k}=F_{i,j-1,k}+F_{i-1,j,k}-F_{i-1,j-1,k}+P_{A_{i,j,k}}$$

$$time=t\bmod(c+1)$$

$$Answer_i=F_{x_{1i},y_{1i},time}-F_{x_{2i-1},y_{1i},time}-F_{x_{1i},y_{2i-1},time}+F_{x_{2i-1},y_{2i-1},time}$$

## 代码


```cpp

//Star sky

#include<bits/stdc++.h>
using namespace std;
#define kint long long
const int N=115,u=1e2+1,m=15,d(0);
kint n,q,c,F[N][N][m],P[N][N][m];
kint xtwo,ytwo,xone,yone,t;
void skyopen(){
	//freopen("Star sky.in","r",stdin);
	//freopen("Star sky.out","w",stdout);
	return;
}
int main()
{   skyopen(); cin>>n>>q>>c;
	for(kint i=1,x,y,o;i<=n;i++){
		cin>>x>>y>>o;
		F[x][y][d]+=o%(c+1);
		for(kint j=1;j<=c;j++)
			F[x][y][j]+=(o+j)%(c+1);
	}for(kint k=d;k<=c;k++)
		for(kint i=1;i<=u;i++)
			for(kint j=1;j<=u;j++)
				F[i][j][k]+=F[i-1][j][k]
				+F[i][j-1][k]-F[i-1][j-1][k];
	while(q--){ cin>>t>>xtwo>>ytwo>>xone>>yone;t%(c+1);
		kint Answer=F[xone][yone][t]-F[xtwo-1][yone][t]
		-F[xone][ytwo-1][t]+F[xtwo-1][ytwo-1][t];
		cout<<Answer<<endl;
	} return 0;
}
```
End.

---

## 作者：Angelina188 (赞：0)

除了星星亮度会随时间变化外，纯二维前缀和模板。那么就思考如何处理星星的亮度变化。
####   思路
若全部一起解决，肯定算不清。但当看到 $c \le 10$ 时，就能想到直接统计每颗星星在不同矩形内的亮度。\
因此，设 `s[i][j][k]` 表示表示坐标 $(0,0)$ 到 $(i,j)$ 亮度为 $k$ 的星星数。这样，就能在求答案时直接对不同亮度的星星求和即可。
#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,c,s[105][105][15];
int main(){
	cin>>n>>q>>c;
	for(int i=1;i<=n;i++){
		int x,y,p;
		cin>>x>>y>>p;
		s[x][y][p]++;
	}
	for(int i=1;i<=100;i++){
		for(int j=1;j<=100;j++){
			for(int k=0;k<=c;k++){
				s[i][j][k]+=s[i-1][j][k]+s[i][j-1][k]-s[i-1][j-1][k];
			}
		}
	}
	while(q--){
		int t,a1,b1,a2,b2;
		cin>>t>>a1>>b1>>a2>>b2;
		int ans=0;//多测清零
		for(int i=0;i<=c;i++){
			int num=s[a2][b2][i]-s[a1-1][b2][i]-s[a2][b1-1][i]+s[a1-1][b1-1][i];//二维前缀和
			ans+=num*((i+t)%(c+1));
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：__cheems__ (赞：0)

## 思路

考虑前缀和。定义 $a_{i,j,k}$ 为在第 $k$ 个时刻，左下角为 $(1,1)$ ，右上角为 $(i,j)$ 的矩阵中星星亮度总和。再定义 $b_{i,j,k}$ 为坐标 $i,j$ 在第 $k$ 个时刻的亮度。不难得出 $a_{i,j,k}=a_{(i-1),j,k} + a_{i,(j-1),k} - a_{(i-1),(j-1),k}+b_{i,j,k}$。

然后发现星星亮度 $c+1$ 个时刻为一次周期。所以对于观察时刻 $t$ 与时刻 $t\bmod(c+1)$ 所看到的星星亮度一致。通过前缀和数组求出答案即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q, c;
int a[108][108][11];
int sum[108][108][11];
bool b[108][108];
signed main()
{
	cin >> n >> q >> c;
	for (int i = 1, x, y, z; i <= n; i++)
	{
		cin >> x >> y >> z;
		a[x][y][0] += z % (c + 1); 
		for (int j = 1; j <= c; j++)
		{
			a[x][y][j] += (z + j) % (c + 1);
		}
	}
	for (int k = 0; k <= c; k++)
	{
		for (int i = 1; i <= 101; i++)
		{
			for (int j = 1; j <= 101; j++)
			{
				a[i][j][k] += a[i - 1][j][k] + a[i][j - 1][k] - a[i - 1][j - 1][k];
			}
		}
	}
	while (q--)
	{
		int px, py, qx, qy, t;
		cin >> t >> px >> py >> qx >> qy;
		t %= (c + 1);
		cout << a[qx][qy][t] - a[px - 1][qy][t] - a[qx][py - 1][t] + a[px - 1][py - 1][t] << "\n";
	}
    return 0;
}
```

---

## 作者：cqbzhr (赞：0)

根据题意，不难发现，如果这些星星的亮度不会发生变化，那么这个题就是一个模板题，但是，现在的问题就是去解决星星亮度的变化的问题。

很明显，星星亮度的变化不能放在一起解决，所以我们可以直接统计每一种星星在不同矩形中的亮度。

设 $sum[i][j][k]$ 表示从 $(0,0)$ 到 $(i,j)$ 的矩形中，亮度为 $k$ 的星星的数量。所以，最后的答案只用针对不同亮度的星星进行求和。

注意：因为每颗星星最大的亮度为 $c$，所以最终每颗星星的亮度为 $(k+t)\bmod(c+1)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,c,sum[15][105][105];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q>>c;
	for(int i=1;i<=n;i++){
		int x,y,s;
		cin>>x>>y>>s;
		sum[0][x][y]+=s;
		for(int j=1;j<=c;j++){
			sum[j][x][y]+=(s+j)%(c+1);
		}
	}
	for(int k=0;k<=c;k++){
		for(int i=1;i<=100;i++){
			for(int j=1;j<=100;j++){
				sum[k][i][j]+=sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1];
			}
		}
	}
	while(q--){
		int t,x,y,x2,y2;
		cin>>t>>x>>y>>x2>>y2;
		cout<<sum[t%(c+1)][x2][y2]-sum[t%(c+1)][x-1][y2]-sum[t%(c+1)][x2][y-1]+sum[t%(c+1)][x-1][y-1]<<"\n";
	}
	return 0;
}
```

---

## 作者：黑影洞人 (赞：0)

题意：在一个 $100\times 100$ 的平面上有一些点，给出这些点的亮度初始值和最大值限制，问随机的一个时间内，一定区域内的亮度值之和。

观察发现，最大值限制小于等于 $10$，说明可以直接用数组存起来。

直接对每个时间做一个二维前缀和即可。

```cpp
#include<cstdio>
#include<algorithm>
#define N 105
using namespace std;
int n,q,c;
int dp[15][N][N];
signed main(){
	scanf("%d%d%d",&n,&q,&c);
	for(int i=1;i<=n;i++){
		int x,y,s;
		scanf("%d%d%d",&x,&y,&s);
		dp[0][x][y]+=s;//这些点可以叠加，要注意 
		for(int j=1;j<=c;j++)dp[j][x][y]+=(s+j)%(c+1);
	}
	for(int k=0;k<=c;k++){
		for(int i=1;i<=100;i++){
			for(int j=1;j<=100;j++)dp[k][i][j]+=dp[k][i-1][j]+dp[k][i][j-1]-dp[k][i-1][j-1];
		}
	}
	while(q--){
		int t,x,y,xx,yy;
		scanf("%d%d%d%d%d",&t,&x,&y,&xx,&yy);
		printf("%d\n",dp[t%(c+1)][xx][yy]-dp[t%(c+1)][x-1][yy]-dp[t%(c+1)][xx][y-1]+dp[t%(c+1)][x-1][y-1]);
	}
	return 0;
}



```


---

## 作者：MuelsyseU (赞：0)

一开始看到题目时想到前缀和，发现这个模数是固定的就考虑了统计矩形中的星星总亮度和数量，把时间造成的亮度增加与原先的亮度分别取模后计算。

但是这个思路的问题在于，最后输出时并没有同样取模，这也意味着模数的性质在这里显然不能使用。然而可以发现，这里的模数 $c$ 只有 $10$ 种取值，实际上非常小，而这个输入的 $t$ 同样在取模 $c$ 后不会影响答案，也只有 $10$ 种取值。

所以就可以导出一种正确的做法：对于取模后每个 $t$ 预处理一遍这时的二维前缀和，这样规避掉上述的问题从而可以得到正确答案。

注意一个位置实质上可能有多个星星，有些实现会受到这个条件的影响而不能正确处理前缀和。

```
#include <bits/stdc++.h>
using namespace std;

int n, m, mod, x, y, z, x2, y2;
long long s[202][202][12];
int main() {
    scanf("%d%d%d", &n, &m, &mod), ++mod;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        for (int j = 0; j < mod; j++) s[x][y][j] += (z + j) % mod;
    }
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= 200; ++j)
            for (int k = 0; k < mod; ++k)
                s[i][j][k] += s[i - 1][j][k] + s[i][j - 1][k] - s[i - 1][j - 1][k];
    while (m--)
        scanf("%d%d%d%d%d", &z, &x, &y, &x2, &y2), z %= mod,
            printf("%lld\n", s[x2][y2][z] - s[x - 1][y2][z] - s[x2][y - 1][z] + s[x - 1][y - 1][z]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

#### 思路

看着就很像用前缀和吧。

首先，看到数据范围， $ c $ 很小。

于是定义 $ f[i][j][k] $ 为前 $ j \times k $ 个星星的亮度为 $ i $ 时的个数

则 $ f[i][j][k] \gets  f[i][j][k] + f[i][j - 1][k] + f[i][j][k - 1] - f[i][j - 1][k - 1] $

#### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 1e5 + 5;
int n , q , c , x[Maxn] , y[Maxn] , p[Maxn];
int f[15][105][105] , T , A , B , C , D , Ans , Sum;
int main() {
	cin >> n >> q >> c;
	for(int i = 1 ; i <= n ; i ++) {
		cin >> x[i] >> y[i] >> p[i];
		f[p[i]][x[i]][y[i]]++;
	}
	for(int i = 0 ; i <= c ; i ++) {
		for(int j = 1 ; j <= 100 ; j ++) {
			for(int k = 1 ; k <= 100 ; k ++) {
				f[i][j][k] += f[i][j - 1][k] + f[i][j][k - 1] - f[i][j - 1][k - 1];
			}
		}
	}
	while(q--) {
		cin >> T >> A >> B >> C >> D;
		Ans = 0;
		for(int i = 0 ; i <= c ; i ++) {
			Ans += (i + T) % (c + 1) * (f[i][C][D] - f[i][C][B - 1] - f[i][A - 1][D] + f[i][A - 1][B - 1]);
		}
		cout << Ans << endl;
	}
	return 0;
}

---

## 作者：wanghaoyu1008 (赞：0)

此题当然不算难题，但对于最近热衷于数据结构的（快被弄疯掉的）我来说并不显然（我第一眼看以为是二维树状数组）。

我们关注到c=10。话说星星一眨眼，人间数十寒暑，那c其实可以出到3e8的。其实再大点也不要紧，因为noip2017的教官就管了海量的人。言归正转，我们看看这道题怎么做。

大致可以猜出府再度应该是$O(n^2*c+q*c)$的。题目中第$t$秒星星亮度为$(s_i+t)mod(c+1)$，可以用一维存！（受P2427启发）然后就变成裸的前缀和。

附代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int s[102][102][11];

int main()
{
	int n,q,c,i,j,k,x,y,_x,_y,t;
	scanf("%d%d%d",&n,&q,&c);
	for(i=1;i<=n;i++){
		scanf("%d%d%d",&x,&y,&t);
		++s[x][y][t];
        //最后一维表示初始亮度
	}
	for(k=0;k<=c;k++){
		for(i=1;i<=100;i++)
			for(j=1;j<=100;j++)
				s[i][j][k]+=s[i][j-1][k];
		for(i=1;i<=100;i++)
			for(j=1;j<=100;j++)
				s[i][j][k]+=s[i-1][j][k];
	}
	for(i=1;i<=q;i++){
		scanf("%d%d%d%d%d",&t,&x,&y,&_x,&_y);
		int ans=0;
		for(k=0;k<=c;k++)
			ans+=(k+t)%(c+1)*(s[_x][_y][k]-s[_x][y-1][k]-s[x-1][_y][k]+s[x-1][y-1][k]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

