# [ARC120B] Uniformly Distributed

## 题目描述

给定一个大小为 $H \times W$ 的网格图，每个格子可以被染成红色（R）、蓝色（B）或为空（.）。记空格数量为 $k$，将所有空格依次染成红色或蓝色，总共有 $2^k$ 种染色方案。

现在要求在从 $(1,1)$ 出发，向下或向右移动一格到达 $(H,W)$ 的过程中，所有经过的格子（包括起点和终点）中被染成红色的格子数目相等。求有多少种方案满足条件。答案对 $998244353$ 取模。

## 说明/提示

$1 \leq H,W \leq 500$

## 样例 #1

### 输入

```
2 2
B.
.R```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
R.R
BBR
...```

### 输出

```
0```

## 样例 #3

### 输入

```
2 2
BB
BB```

### 输出

```
1```

# 题解

## 作者：zhangjiahe__ (赞：1)

# 题面简述：

$H$ 行 $W$ 列的网格图，每个点有可能是红、蓝、白色。将白色格涂成红或蓝，使得从左上角 $(1, 1)$ 到右下角的每一条路径红色数相等，且蓝色数也相等，只能向右向下移动。

# 思路：

不难发现一个重要结论：

**题目条件要想满足，要保证每个以 $(1, 1)$ 为左上角与任意一个方格为右下角围成的矩形满足条件。**

## 证明：

假设有一个矩形不满足条件，则可以在不满足条件的矩形内取不合法的路径，后面的路线完全重合，构造出不满足的情况。出现矛盾，结论得证。

接下来，看这个条件又有什么用处。如表格所示，根据结论，二行一列一定填和一行二列一样的红色，往下扩展，即可发现二行二列必须填和一行三列一样的红色。三行二列同理必填蓝色。


|||||
|:-:|:-:|:-:|:-:|
|B|R|R|B|
|.|.|B|.|
|R|.|B|B|
|B|B|B|B|

如图，可确定的位置加粗

|||||
|:-:|:-:|:-:|:-:|
|.| **_R_** |.|.|
|R|.|.|**_B_**|
|.|.|B|.|
|.|**_B_**|.|.|

可以发现，**从左下到右上的斜线填的颜色一样**。若有矛盾，答案为 $0$；若有颜色，即可确定整条线的颜色；若都没有颜色，任填相同颜色，答案乘 $2$。具体实现代码有注释。

# 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
char R = 'R', B = 'B';
long long n, m, ans=1; //注意相乘初始值设为1
char rb[505][505]; //存储颜色数
int main()
{
	cin >> n >> m;
	memset(rb, '?', sizeof(rb)); //似乎没用?
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> rb[i][j];
	int mx = max(n, m), mn = min(n, m);
	for(int i = 2; i <= n+m; i++) //斜线中行数加列数是定值
	{
        char color = '?';
		for(int j = 1; j <= min(1ll*i-1, n); j++)
        {
            int x = j, y = i-j;
            if(y > m) continue;
            if(rb[x][y] == R || rb[x][y] == B)
            {
                if(color != '?' && color != rb[x][y]) //矛盾
                {
                    cout << 0;
                    return 0;
                }
                color = rb[x][y];
            }
        }
        if(color == '?') //任填
        {
            ans *= 2;
            ans %= 998244353;
        }
	}
    cout << ans;
    return 0;
} 
```

---

## 作者：DengDuck (赞：1)

感觉不擅长结论题，可以场切的同学好强啊。

这题我们发现结论是，情况合法当且仅当所有的格子 $(i+1,j)$ 和 $(i,j+1)$ 相等。

必要性：如果格子 $(i+1,j)\not =(i,j+1)$，那么 $(i,j)\to (i+1,j+1)$ 的路径的红色格子数是不同的，这与题设矛盾。

充分性：对于满足 $(i+1,j)=(i,j+1)$ 的局面，可以发现对于一种 $x+y$，所有的格子 $(x,y)$ 相等，而每次移动其实是从 $x+y$ 的格子移动到了 $x+y+1$ 的格子，因此所有移动方案的路径的经过的颜色都是一样的，因此此时局面合法。

所有我们证明了之后就很简单了，对于每一种 $x+y$ 统计所有的格子 $(x,y)$：
- 如果只有一种颜色，那么合法，剩下格子填这种颜色，答案不变。
- 如果有两种颜色，那么题目无解，答案变成 $0$。
- 如果没有颜色，那么填什么颜色都可以，答案翻倍。

直接做，时间复杂度为 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=505;
//const LL M;
const LL mod=998244353;
//const LF eps;
//const LL P;
LL n,m,ans=1;
char c[N][N];
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",c[i]+1);
	}
	for(int i=2;i<=n+m;i++)
	{
		LL flg1=0,flg2=0;
		for(int j=max(1ll,i-m);j<=n&&j<i;j++)
		{
			if(c[j][i-j]=='R')flg1=1;
			if(c[j][i-j]=='B')flg2=1;
		}
		if(flg1&&flg2)ans=0;
		if(!flg1&&!flg2)ans=2*ans%mod;
	}
	printf("%lld",ans);
	return 0;
}
//RP++
```

---

## 作者：DrDuck (赞：0)

人类智慧题。

在合法方案中，对于每条路线，所有经过的格子（包括起点和终点）中被染成红色的格子数目相等，我们便会去思考这个合法方案所生成的地图是否具有一定的对称性。

我们首先考虑 $H = 2$，$W = 2$ 的情况。

```cpp
BB BR RB RR BR ......
BB RB BR RR RR ......
```
以上都是合法的（没有列举完）。

反之，类似于：

```cpp
BR RR ......
BB BB ......
```
这类都是不合法的（没有列举完）。

不难发现合法情况总是斜对角线（从右上到左下）同色的时候。那么当 $H > 2$，$W > 2$ 时还成立吗？是否对于任意的 $H$ 和 $W$，都有每条从右上到左下的斜线（这里的斜线必须满足对于斜线上的每一个点 $(x,y)$，都有 $x + y$ 为一定值，即类似于解析几何中直线的斜率必须是 $1$，为了下文方便，这里定义这种斜线为**优美的线**）的颜色都必须相同呢？下面利用反证法进行严谨证明。

![](https://cdn.luogu.com.cn/upload/image_hosting/qbgge9q8.png?x-oss-process=image/resize,m_lfit,h_3500,w_2250)

我们假设上图中点 $C$ 与点 $D$ 的颜色不同。假设起始点 $S$，终点 $E$，必然有两条路线，其中一条为 $S \to A \to C \to B \to E$，另一条为 $S \to A \to D \to B \to E$，其中第一条路径中 $S \to A$ 经过的点与第二条路径中相同，第一条路径中 $B \to E$ 经过的点与第二条路径中相同。又由于点 $C$ 与点 $D$ 颜色不同，第一条路径与第二条路径中经过的颜色为 $R$ 的点的个数必然不同，这样的路径必定不是合法路径。

下面开始讲如何统计答案。对于每一条优美的线而言：
* 如果它既出现了 $R$ 又出现了 $B$，那么一定无法构造合法答案，输出 $0$ 即可。
* 如果它出现了 $R$ 和 $B$ 其中一种，这条线上所有的点的颜色已经确定，不做任何操作。
* 如果它全是问号，那么置 $ans \gets ans \times 2$。注意 $ans$ 初值为 $1$。
# CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5e+2 + 2;
const int mod = 998244353;
int n, m, ans = 1;
char a[maxn][maxn];
signed main()
{
    //freopen("color.in", "r", stdin);
    //freopen("color.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int k = 2; k <= m + n; k++)
    {
        char c = '.';
        for (int i = max(1ll, k - m); i <= min(k - 1, n); i++)
        {
            int j = k - i;
            if (c == '.')
            {
                if (a[i][j] != '?')
                {
                    c = a[i][j];
                }
            }
            else if (c != a[i][j] && a[i][j] != '?')
            {
                cout << 0;
                return 0;
            }
        }
        (ans *= (c == '.' ? 2 : 1)) %= mod;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{43}$ 篇题解。

# $\mathbf{0x01}$ 承

求有多少种方案，使从起点到终点所有经过的格子（包括起点和终点）中被染成红色的格子数目相等。

# $\mathbf{0x02}$ 转

无论你在哪个点上，由于只能向下或向右，同时为了保证经过的红色格子数目相同，因此这个点的右边和下边必须是同种颜色。

我们可以进一步推广到在这个矩阵中，连接某个点右边的点和下边的点，其所在直线（即任意一条斜对角线）上的所有点颜色一定相同。

证明如下：

已知 $(i+1,j)$ 和 $(i,j+1)(i\in[1,H],j\in[1,W],i,j\in\mathbb{Z})$ 颜色相同，因此 $(i,j)$ 和 $(i+1,j+1)$ 颜色也相同，$(i,j)$ 和 $(i+k,j+k)(k\in[\max\{1-i,1-j,0\},n-\max\{i,j\}])$ 颜色也相同。

知道了这个，我们就可以循环枚举每一条斜对角线上的字符：
- 如果又有 `R` 又有 `B`，那么显然不符合要求，答案为 $0$；
- 如果只有其中的一个，矩阵符合要求当且仅当这一条斜对角线上的 `.` 也为这个字符。
- 如果全是 `.`，那么可以在这一条斜对角线上填入 `R` 或 `B`，答案 $\times2$。

其它的看注释。

# $\mathbf{0x03}$ 合

代码的变量名和原题有些不一样，按照个人习惯进行了一些调整。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll n,m,ans=1;
char mp[502][502];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>mp[i]+1;
	}
	for(int i=2;i<=n+m;i++){
		bool f1=0,f2=0;//f1记录是否有R，f2记录是否有B
		for(int x=1;x<=i;x++){
			int y=i-x;
			if(x>n||y>m||(x<=0||y<=0)){
				continue;//边界判断
			}
			if(mp[x][y]=='R')f1=1;
			if(mp[x][y]=='B')f2=1;
		}
		if(f1&&f2)ans=0;
		else if(f1==0&&f2==0)ans*=2,ans%=mod;//取模
	}
	cout<<ans;
}

```

---

## 作者：Hog_Dawa_IOI (赞：0)

### 题目描述
给定一个大小为 $n \times m$ 的网格图，每个格子可以被染成红色（R）、蓝色（B）或为空（.）。记空格数量为 $k$，将所有空格依次染成红色或蓝色，总共有 $2^k$ 种染色方案。    
现在要求在从 $(1,1)$ 出发，向下或向右移动一格到达 $(n,m)$ 的过程中，所有经过的格子（包括起点和终点）中被染成红色的格子数目相等。求有多少种方案满足条件。       
答案对 $998244353$ 取模。       
数据范围：$2 \le n,m \le 500$。

### 画图分析
这是根据样例一画的图。      
![](https://cdn.luogu.com.cn/upload/image_hosting/ircyvgzu.png)     
可以看到，这里仅有的两条路径中，有且仅有一个方格不同，而它们处于**从右上角到左下角的斜线**的位置。那么我们可以猜想，如果要达成所有路线经过的红色格子数量相同，那么是不是在从右上角到左下角的斜线上的所有格子都要相同？   
下面再根据样例二和样例三手玩一把。    
![](https://cdn.luogu.com.cn/upload/image_hosting/31qku8yw.png)    

可以看到：

- 左上角的图中（样例二），当我们来到第一行第二列的格子时，要么向下，要么向右，但此时两个格子的颜色不相同，所以无法达成所有经过的格子中被染成红色的格子数目相等的任务。     
- 右上角的图中（样例三），从右上角到左下角的斜线中，颜色都是一样的，所以方法只有一种。    

那么我们也许可以总结出如下规律：      
**当且仅当从右上角到左下角的斜线中的所有格子颜色相同时，当前情况合法。**    
这里的“右上角到左下角的斜线”指的是横坐标和纵坐标之和相同的所有格子连起来的一条线（见下图中的黑线）。      
如果仍然有疑惑的话可以看下面这张图，它把所有情况都总结在了一起。   
![](https://cdn.luogu.com.cn/upload/image_hosting/7i6jngw2.png)     
这幅图中从左上往右下数，第一条斜线已被填满；第二条斜线只能填满蓝色；第三条斜线只能填满红色；第四条斜线只能填满蓝色。但第五条斜线由于没有任何格子被填上颜色，所以既可以填红色也可以填蓝色，方案数也要乘 $2$。
当然了如果某一条斜线上本来就有不同的颜色，那么没有涂色方案使其合法，方案数就是 $0$。      
如果需要这个规律的证明，可以移步 [DengDuck 的题解](https://www.luogu.com.cn/blog/DengDuck/solution-at-arc120-b)，那里写得相当详细。     
所以我们的操作就很清晰了，对于每一条斜线，统计所有的格子：

- 如果没有任何一个格子被涂上颜色，那么这条线上的格子既可以涂红色也可以涂蓝色，答案乘 $2$；
- 如果总共只有一种颜色出现，那么为了统一颜色，这条线上的格子的颜色都确定了，方案数不变；
- 如果两种颜色都出现了，那么不存在合法的涂色方案，答案瞬间变成 $0$，不管别的斜线怎么样。 

### 参考代码
记得在统计答案的时候取模。
```cpp
#include<stdio.h>
int n,m;long long ans=1;char s[505][505];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i1=n,i2=m;i1>=1;i1--)
    {
        bool red=0,blue=0;int last1=0,last2=0;
        for(int j1=i1,j2=i2;j1<=n&&j2>=1;j1++,j2--)
        {
            red|=(s[j1][j2]=='R'),blue|=(s[j1][j2]=='B');
            if(last1!=0&&last2!=0&&(s[j1][j2]=='R'||s[j1][j2]=='B')&&s[j1][j2]!=s[last1][last2])
            {printf("0");return 0;}
            if(s[j1][j2]!='.') last1=j1,last2=j2;
        }
        if(!(red||blue)) ans=ans*2%998244353;
    }
    for(int i1=1,i2=m-1;i2>=1;i2--)
    {
        bool red=0,blue=0;int last1=0,last2=0;
        for(int j1=i1,j2=i2;j1<=n&&j2>=1;j1++,j2--)
        {
            red|=(s[j1][j2]=='R'),blue|=(s[j1][j2]=='B');
            if(last1!=0&&last2!=0&&(s[j1][j2]=='R'||s[j1][j2]=='B')&&s[j1][j2]!=s[last1][last2])
            {printf("0");return 0;}
            if(s[j1][j2]!='.') last1=j1,last2=j2;
        }
        if(!(red||blue)) ans=ans*2%998244353;
    }
    printf("%lld",ans);
}
```

---

## 作者：wzt2012 (赞：0)


首先可以观察出必要条件，也就是对于所有 $(i,j)$ 要求 $(i+1,j)$ 和 $(i,j+1)$ 的颜色相等，这样才能保证无论用什么方法走到 $(i+1,j+1)$ 经过红色格子的数量都是一样的。

这也是充分条件，因为任意时候路径经过红色格子数都是全相等的。

所以对于每一个 $i+j$ 统计颜色分布，如果全是 `.` 答案 $\times 2$，如果既有 $\text B$ 又有 $\text W$ 答案为 $0$，否则答案不变。


---

参考代码：

```
#include<bits/stdc++.h>
using namespace std;
const int M = 505, mod = 998244353;
int read(){
	int x = 0, f = 1;
	char c;
	while((c = getchar()) < '0' || c > '9'){
		if(c == '-') f = -1;
	}
	while(c >= '0' && c <= '9'){
		x = (x << 3) + (x << 1) + (c ^ 48); 
		c = getchar();
	}
	return x * f;
}
int n, m, ans = 1;
char s[M][M];
signed main(){
	n = read();
	m = read();
	for(int i = 1; i <= n; i ++){
		scanf("%s", s[i] + 1);
	}
	for(int i = 2; i <= n + m; i ++){
		int c1 = 0;
		int c2 = 0;
		for(int j = 1; j <= n; j ++){
			if(i - j <= 0 || i - j > m) continue;
			if(s[j][i - j] == 'R') c1 ++;
			if(s[j][i - j] == 'B') c2 ++;
		}
		if(c1 && c2) ans = 0;
		if(!c1 && !c2) ans = 2 * ans % mod;
	}
	printf("%d\n", ans);
	return 0;
}

---

## 作者：TLEWA (赞：0)

## 思路介绍

我们可以将这个矩阵分解为一个个右上到左下的对角线所组成的集合，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/4si5er8o.png)

由于操作只有向右和向下，所以每一次操作都会将位置变到下一个编号的对角线上。要想所有方案中，经过的 `R` 点数量都一致的话，必须保证每条对角线的点类型一致，不一致的情况下则没有合法方案。我们可以改变的是 `.` 点，所以只有在一条对角线上均为 `.` 点时，我们才可以任选对角线的点类型。设这种对角线的数量为 $x$，则方案数为 $2^x$。总时间复杂度 $O(HW)$，可以通过此题。

记得取模。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w;
string s[505];
bool a,b;
long long ans=1;
int main() {
	cin >> h >> w;
	for(int i=0;i!=h;++i) cin >> s[i];
	for(int i=0;i<h+w-1;++i) {
		a=0,b=0;
		for(int j=0;j<min(i+1,h+w-1);++j) {
			if(j<h&&(i-j)<=w) {
				if(s[j][i-j]=='B') a=1;
				else if(s[j][i-j]=='R') b=1;
			}
		}
		if(a==1&&b==1) ans=0;
		else if(a==1||b==1) ans=ans;
		else ans=(ans*2)%998244353;
//		cout << a << ' ' << b << endl;
	}
	cout << ans << endl;
	return 0;
}

```



---

## 作者：qzhwlzy (赞：0)

## 题目大意

给定一个 $H\times W$ 的矩阵，每个格子是红色（`R`）或蓝色（`B`）或无色
（`.`）。现在要将所有无色的格子涂成蓝色或红色其中一种，问满足以下条件的方案数：从左上角 $(1,1)$ 到右下角 $(H,W)$ 的所有路径经过的红色格子数相等。

## 思路

在所有从 $(1,1)$ 到 $(H,W)$ 的路径中，一条右上 - 左下的对角线 $\{(x,y)|x+y = k\}$ 只会经过其中一个一次。首先显然一定会经过，其次若经过对角线上一点，剩余点要么在其上方要么在其左方，所以这条对角线上的点只会经过一个。

所以对于所有的 $H+W-1$ 条对角线，要么全红，要么全蓝，扫一遍统计一下即可。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 505
#define ll long long
#define mod 998244353
using namespace std;
int h,w,a[maxn]; char c[maxn][maxn]; ll ans=1LL;
int main(){
    scanf("%d%d",&h,&w); for(int i=1;i<=h;i++) for(int j=1;j<=w;j++)
        {scanf("%1c",&c[i][j]); if(c[i][j]=='\n') scanf("%1c",&c[i][j]);}
    for(int i=1;i<=w+h-1;i++){
        bool flr=0,flb=0; for(int j=1,k=i;k>=1;j++,k--) if(j<=h&&k<=w)
            {flr|=(c[j][k]=='R'); flb|=(c[j][k]=='B');}
        if(flr&&flb) ans*=0; else if(!flr&&!flb) ans=ans*2%mod;
    } printf("%lld",ans);
    return 0;
}

```

---

