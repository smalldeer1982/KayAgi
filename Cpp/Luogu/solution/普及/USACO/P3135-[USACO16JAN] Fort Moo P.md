# [USACO16JAN] Fort Moo P

## 题目描述

Bessie 正在和她的朋友 Elsie 一起建造一个堡垒。像任何好的堡垒一样，这个堡垒需要一个坚固的框架。Bessie 想要建造一个一米宽的矩形轮廓框架，然后在这个框架上建造堡垒。

Bessie 已经选择了一个建造堡垒的地点——一块 $N$ 米乘 $M$ 米的土地（$1 \leq N, M \leq 200$）。不幸的是，这块地有一些沼泽区域，不能用来支撑框架。请帮助 Bessie 确定她可以用堡垒覆盖的最大面积（由框架支撑的矩形的面积），使得框架不会坐落在任何沼泽区域上。

## 说明/提示

在示例中，最优框架的位置由下面的 `f` 表示：

```
.ffff.
.fX.fX
Xf.Xf.
.ffff.
..X...
```

## 样例 #1

### 输入

```
5 6
......
..X..X
X..X..
......
..X...```

### 输出

```
16```

# 题解

## 作者：潜翎 (赞：16)

200引导我们思考O(n^3)。

O(n^3)的矩阵中的dp最经典的不就是最大子矩阵了么？

让我们回忆一下最大子矩阵是怎么搞的。

```cpp
两层循环枚举起始行和终止行，预处理每一列前缀和。
一层循环做dp：
如果仅选择当前列不比选择原结果优，暂时加入原结果。
如果仅选择当前列更优，舍弃原结果，选择当前列。
实时更新ans。
```
然后我们发现这玩意儿和最大子矩阵差不多。
```cpp
两层循环枚举起始行和中止行，预处理列的连通性。
一层循环做dp:
如果这两行中间的某一列是连通的，说明它有成为一堵纵向墙的资格。
如果随着列的枚举，这两行的连通性被破坏(之间建不成横向墙)，那么前面的纵向墙就作废。
如果一堵纵向墙前面还有另一堵未被作废的纵向墙，那么可用来更新答案。
```
我知道看起来云里雾里的，所以放代码吧。
```cpp
for(int i=1;i<=m;i++)
	{
		int x=0;
		for(int j=0;j<=n;j++)
		 if(str[j][i]=='X'||!str[j][i]) x++;
		 else a[j][i]=x;
	}
```
这一段是预处理纵向连通性的。如果一数列中数字一样且非0就连通，0是沼泽。

用样例打出来的a数组是这样的：
```cpp
111111
110110
012012
212212
210212
```
对照一下代码应该很好理解吧。
```cpp
for(int i=1;i<n;i++)
    for(int j=i+1;j<=n;j++)
        for(int k=1;k<=m;k++)
```
枚举起始行中止行。扫过每一列。
```cpp
if(str[i][k]!='.'||str[j][k]!='.') l=0;
```
l是较靠左的纵向墙。

如果地图中枚举出的这两行中有一片沼泽地的话，这片沼泽地的左侧的墙全都不能为这两行接下来的答案做出贡献了。所以左墙设为空。
```cpp
if(a[i][k]==a[j][k]&&a[i][k])
{
        if(!l) l=k;
	else r=k,len=max(r-l+1,len);
}
```
如果满足a[i][k]==a[j][k]则纵向连通，但要排除a[i][k]==a[j][k]=0的情况（这样就是两片沼泽）。

这说明这儿有资格建纵向墙。

如果没有左侧的墙就赶紧把它设为左侧的墙。

我们是从左向右枚举的，我们自然希望较靠右的墙越靠右越好，所以如果左侧墙存在，我们可以直接把这列设为右侧墙，并且答案可更新。

最后乘一乘输出就好了。

完整代码奉上：
```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 210
using namespace std;
int n,m,a[N][N],f[N],ans;
char str[N][N];
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	 scanf("%s",str[i]+1);
	for(int i=1;i<=m;i++)
	{
		int x=0;
		for(int j=0;j<=n;j++)
		 if(str[j][i]=='X'||!str[j][i]) x++;
		 else a[j][i]=x;
	}
	for(int i=1;i<n;i++)
	 for(int j=i+1;j<=n;j++)
	 {
	 	int len=0,l=0,r=0;
	 	memset(f,0,sizeof(f));
	 	for(int k=1;k<=m;k++)
	 	{
	 		if(str[i][k]!='.'||str[j][k]!='.') l=0;
	 		if(a[i][k]==a[j][k]&&a[i][k])
	 		{
	 			if(!l) l=k;
	 			else r=k,len=max(r-l+1,len);
			}
		}
		ans=max(ans,(j-i+1)*len);
	 }
	 printf("%d",ans);
	 return 0;
}
```


------------
后记：

这是我第一次不看题解（好吧，以前看过，不过我没记住题解内容，也算独立完成吧）写蓝题dp，我一直不擅长dp，居然把这个写出来了，有点自豪。

我做题之前瞄了一眼题解数量，5篇，心想自己是不是也能写题解试试。

然后看了一眼范围，n m<=200，心里忽然飘过一句话“200引导我们思考O(n^3)。”感觉是哪个题解里见过，觉着挺乐呵。

做完题，习惯性打开题解。

第一句话。

“200引导我们思考O(n^3)。”

我忽然就真想动动手写题解了。

---

## 作者：kczno1 (赞：10)

200引导我们思考O(n^3)。

就是先枚举矩形的两个列。

现在矩形的一个边长已经定了，就是要让另一个最大化。

从上到下枚举所有能联通的行，

dp一下他能联通的最上面的行。

就是如果他跟他上面那个行联通，就转移那个行的dp值，

否则dp值就是自己。

判断两个点是否联通只要预先dp出每个点能联通的最左点，最上点即可。

```cpp
#include<bits/stdc++.h>

const int N=205;
int n,m,i,j,k,left[N][N],up[N][N];
char ch[N][N];

void chmax(int &x,int y)
{
    if(x<y)x=y;
}

int main()
{freopen("1.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;++i)scanf("%s",ch[i]+1);
    for(i=1;i<=n;++i)
    for(j=1;j<=m;++j)
    if(ch[i][j]=='.') { left[i][j]=(j==1)?1:left[i][j-1];up[i][j]=(i==1)?1:up[i-1][j]; }
    else {left[i][j]=j+1;up[i][j]=i+1;}
    
    int ans=0;
    for(i=1;i<=n;++i)
    for(j=i;j<=n;++j)
    {
        int mxlen=0,last=0;
      for(k=1;k<=m;++k) 
      if(up[j][k]<=i)
      {
            if(left[i][k]<=last&&left[j][k]<=last) chmax(mxlen,k-last+1);
            else last=k;
      }
        chmax(ans,(j-i+1)*mxlen);
    }
    
    printf("%d\n",ans);
}
```


---

## 作者：xkcdjerry (赞：6)

这道题很多人是拿 DP 做的，但是由于数据不是很强可以用 $O(n^4)$ 的玄学暴力卡过去：

首先考虑最简单的 $O(n^5)$ 做法： $O(n^2)$ 枚举左上角，$O(n)$ 枚举长， $O(n)$ 枚举宽，$O(n)$ 验证，共计 $O(n^5)$。  
由于验证只是求四条边是否全是 `.` ，即**四条边是否 `.` 的个数等于长度**，可以使用前缀和优化做到 $O(n^4)$ 。

但是如果代码这么写就会获得 78 分的好成绩，考虑优化：  

可以令 $x$,$y$ 逆序循环，$i,j$ 正序循环，那么显然每一层循环每跑一次可能画出矩形的最大值就会更小，因此：
* 如果 $y$ 循环内找到了可行解可以直接跳出，因为后面一定找不到更大的了。
* 在任何一层循环里如果能够取到的最大值 $ \leqslant mx$ 也可以跳出，原因同上。

加上优化之后的代码可以取得 93 分，而且还有一个大的优化点：

观察代码可以发现 `col[x][j]-col[i-1][j]==x-i+1` 与 $y$ 无关。可以提取到 $x$ 循环中。减少求值和提前剪裁掉不符合的答案。  

这个优化后代码终于[获得了 100 分](https://www.luogu.com.cn/record/56726575)，不开 O2 时时间为 77ms，开了之后为 [54ms](https://www.luogu.com.cn/record/56729186)，是当前（2021 年 8 月 25 日）的最优解。

完整代码如下：  
```c++
#include <cstdio>
#define N 210
int n,m;
int a[N][N];
int row[N][N],col[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    {
        char c;
        scanf(" %c",&c);
        a[i][j]=c=='.';
        row[i][j]=row[i][j-1]+a[i][j];
        col[i][j]=col[i-1][j]+a[i][j];
    }
    int mx=-1;
    for(int i=1;i<=n;i++)
    {
        if((n-i+1)*m<=mx) break;
        for(int j=1;j<=m;j++)
        {
            if((n-i+1)*(m-j+1)<=mx) break;
            for(int x=n;x>=i;x--)
            {
                if((x-i+1)*(m-j+1)<=mx) break;
                if(col[x][j]-col[i-1][j]!=x-i+1) continue;//左
                for(int y=m;y>=j;y--)
                {
                    if((x-i+1)*(y-j+1)<=mx) break;
                    if(row[i][y]-row[i][j-1]==y-j+1&& //上
                            row[x][y]-row[x][j-1]==y-j+1&& //下
                            col[x][y]-col[i-1][y]==x-i+1) //右
                    {
                        mx=(x-i+1)*(y-j+1);
                        break;
                    }
                }
            }
        }
    }
    printf("%d",mx);
    return 0;
}
```

---

## 作者：违规用户名71524 (赞：3)

这个题我好像用暴力把其他人的dp都干爆了？？
现在速度排第一。。。。
先处理出每个点向上（up数组），向左（l数组）能延伸到的最远的点，然后枚举矩形的两条纵向的边，这样只要保证矩形上下两条边联通就好了，用处理的l数组判断即可。中间随便把一些不可能更优的状态剪掉，轻松ac。
φ(゜▽゜*)♪
```cpp
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<bitset>
#include<vector>
#include<math.h>
#include<stack>
#include<map>
#include<queue>
#define eps 1e-9
using namespace std;
int n,m;
char mp[205][205];
int up[205][205],l[205][205];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",mp[i]+1);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(i==1)up[i][j]=1;
            else
            {
                if(mp[i-1][j]=='X')
                {
                    up[i][j]=i;
                }
                else
                {
                    up[i][j]=up[i-1][j];
                }
            }
            if(j==1)l[i][j]=1;
            else
            {
                if(mp[i][j-1]=='X')
                {
                    l[i][j]=j;
                }
                else
                {
                    l[i][j]=l[i][j-1];
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=j;mp[i][k]!='X'&&k<=m;k++)
            {
                if((k-j+1)*(i-max(up[i][j],up[i][k])+1)<=ans)continue;
                for(int p=max(up[i][j],up[i][k]);p<=i;p++)
                {
                    if(l[p][k]<=j)
                    {
                        //cout<<i<<' '<<j<<' '<<k<<' '<<p<<' '<<(i-p+1)*(k-j+1)<<endl;
                        ans=max(ans,(i-p+1)*(k-j+1));
                    }
                }
            }
        }
    }
    printf("%d",ans);
}
```


---

## 作者：L01001101 (赞：2)

[$\color{3498DB}\text{P3135 [USACO16JAN] Fort Moo P}$](https://www.luogu.com.cn/problem/P3135)

看到题目，首先可以想到 $O(n^2m^2)$ 的枚举：

枚举矩阵的两条横边所处的行，两条竖边所在的列，然后再通过分别对行和对列的前缀和判断矩阵是否满足条件即可。

但我们发现 $n,m \leq 300$ 的数据范围会超时。

考虑减少一层对于列的枚举。

通过枚举两个行确定矩阵的高，接着将列扫一遍确定最大且满足条件的线段，此线段即作为矩阵的边。

然后更新答案即可。

时间复杂度 $O(n^2m)$。

```cpp
#include<cstdio>
#include<cstring>
const int N=210;
int n,m;
int ans;
char a[N][N];
int s[N][N];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')ch=='-'?f=0:0,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		scanf("%s",a[i]+1);
	for(int j=1;j<=m;++j)for(int i=1;i<=n;++i)
		s[i][j]=s[i-1][j]+(a[i][j]=='X');
	for(int i=1,l,r,_l,_r;i<=n;++i)for(int j=i;j<=n;++j){
		l=r=_l=_r=0;//l,r 为最优线段左右端点，_l,_r 为当前线段的左右端点。
		for(int k=1;k<=m;++k){
			if(a[i][k]=='X'||a[j][k]=='X'){_l=_r=0;continue;}
			if(s[j][k]-s[i-1][k]==0)!_l?_l=k:0,_r=k;
			r-l<_r-_l?l=_l,r=_r:0;
		}
		r-l<_r-_l?l=_l,r=_r:0,l?ans=max(ans,(r-l+1)*(j-i+1)):0;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Celebrate (赞：2)

宣传一下[我的博客](https://blog.csdn.net/zsyzClb/article/details/84831140)

看到这一题，就感觉是用O(n^3)的做法

因为这一题要找一个矩形框架，我们知道要找框架需要固定两条边，然后从中间开始找

所以先枚举两列，然后枚举行，如果可行就更新最大值

代码（我的代码可能和其他题解有些不一样）

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std ;
inline int read() { //快读 
	int x = 0 , f = 0 ; char s = getchar() ;
	while ( !isdigit(s) ) s = getchar() ;
	while (  isdigit(s) ) x = (x<<1) + (x<<3) + s - 48 , s = getchar() ;
	return !f ? x : -x ;
}
const int N = 210 ;
int n , m ;
int sum[N][N] ; //第i行的前缀和 
char st[N] ;
int query( int i , int x , int y ) { return sum[i][y] - sum[i][x-1] ; } //查询第i行从x到y的和 
int maxx = 0 ;
int main() {
	n = read() , m = read() ;
	for ( int i = 1 ; i <= n ; i ++ ) {
		scanf ( "%s" , st+1 ) ;
		for ( int j = 1 ; j <= m ; j ++ ) //前缀和 
			sum[i][j] = sum[i][j-1] + ( st[j] == '.' ? 0 : 1 ) ;
	}
	for ( int l = 1 ; l <= m ; l ++ ) //枚举两列 
		for ( int r = l ; r <= m ; r ++ ) {
			int last = 1 ; //last表示上一个全部为非沼泽地区的行 
			while ( last < n && query(last,l,r) != 0 ) last ++ ; //找第一个 
			if( query(last,l,r) != 0 ) continue ; // 如果没有就离开 
			for ( int i = last ; i <= n ; i ++ ) { //枚举行 
				if( query(i,l,l) != 0 || query(i,r,r) != 0 ) { //如果这两个点又沼泽（说明这个框架不能到达这里） 
					last = i + 1 ; // 找下一个满足条件的行 
					while ( last < n && query(last,l,r) != 0 ) last ++ ;
					if( query(last,l,r) != 0 ) break ;//如果没有满足条件的行 
				}
				else {
					if ( query(i,l,r) == 0 ) //如果能够形成框架 
						maxx = max( maxx , (r-l+1) * (i-last+1) ) ; //更新最大值 
				}
			}
		}
	printf( "%d\n" , maxx ) ;
	return 0 ; 
}

```

---

## 作者：qinsishi (赞：2)

首先这道题我们要明确是一个 DP 题，而且注意这是一个**二维**的。

一般我们做二维 DP，的**常规思路**是：

1. 使用**两维循环**确定两行。

2. 在确定范围里面，每一列当做一个元素，进行**一维 DP**。

在这之中会有一些优化：

1. 对于内层循环，可以进行前缀和优化。

那么现在再来审视此题，就感觉非常容易了。

我们进行二维循环确定两行，在这里面找到全是空地的连续格子，当做一个备选项，加入**备选数组**，当备选数组里面有多个项，选择一个和当前的元素进行匹配。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 205;
int a[N][N];
int sum[N][N]; // sum[i][j] 表示第 i 列，前 j 个数的和 
int hang1[N]; // hang1前缀和 
int hang2[N]; // hang2前缀和 
int xuan[N]; // 当前行区间内的可选性 
int n, m;
int tot, st;
int ans; // 最终的答案 

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; i++) {
		string s;
		cin >> s;
		s = " " + s;
		for (int j=1; j<=m; j++) {
			if (s[j] == 'X') {
				a[i][j] = 1;
			}
			sum[j][i] = sum[j][i-1] + a[i][j];
		}
	}
	// 枚举 i,j 行之后，进行一维的DP 
	for (int i=1; i<=n; i++) {
		for (int j=i; j<=n; j++) {
			memset(hang1, 0, sizeof hang1);
			memset(hang2, 0, sizeof hang2);
			memset(xuan, 0, sizeof xuan);
			tot = 0; // 前面有几个可能的边界 
			st = 1; // 前面失效的去掉 
			for (int k=1; k<=m; k++) { // 枚举列 
				hang1[k] += hang1[k-1] + a[i][k];
				hang2[k] += hang2[k-1] + a[j][k];
				if (sum[k][j]-sum[k][i-1] == 0) {
					if (tot == 0) { 
						xuan[++tot] = k; 
					} else { // 里面之前已经有数了，可以更新答案 
						xuan[++tot] = k;
						for (int h=st; h<tot; h++) {
							// 满足之间没有沼泽，更新答案 
							if (hang1[xuan[tot]]-hang1[xuan[h]] == 0 && hang2[xuan[tot]]-hang2[xuan[h]] == 0) {  
								ans = max(ans, (j-i+1)*(xuan[tot]-xuan[h]+1));
								break; 
							} else st++; // 可选点后移 
						}	
					}
				} 
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：crz_qwq (赞：1)

你说的对，但是 $O(n^2m^2)$ 的暴力加上 O2 可以过掉这道题。

首先求矩阵的二维前缀和，然后枚举城堡的四个角，用二维前缀合判断是否合法即可。

具体的，我们设这个矩阵的四个角，设这四个角的坐标分别是 $(x1,y1),(x1,y2),(x2,y1),(x2,y2)$，并且 $x1 \le x2,y1\le y2$。

则当 $(x1,y1)$ 到 $(x1,y2)$ 没有 `X` 并且 $(x1,y1)$ 到 $(x2,y1)$ 没有 `X` 并且 $(x1,y2)$ 到 $(x2,y2)$ 没有 `X` 并且 $(x2,y1)$ 到 $(x2,y2)$ 没有 `X` 时，这个矩阵是合法的，答案与其面积去较大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
int sum[N][N];
char a[N][N];
inline int qry(int X1,int Y1,int X2,int Y2){return sum[X2][Y2]-sum[X1-1][Y2]-sum[X2][Y1-1]+sum[X1-1][Y1-1];}
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(a[i][j]=='X');
        }
    int ans=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            for(int x=1;x<=i;++x)
                for(int y=1;y<=j;++y)
                {
                    int t1=qry(i,y,i,j),t2=qry(x,y,x,j),t3=qry(x,j,i,j),t4=qry(x,y,i,y);
                    if(t1+t2+t3+t4==0)
                        ans=max(ans,(i-x+1)*(j-y+1));
                }
    cout<<ans;
}
```

---

## 作者：ZeroF (赞：1)

我提供一种奇特的解法。

## 思路

### 暴力

枚举左上角坐标 $(x_1,y_1)$ 和右上角坐标 $(x_2,y_2)$ ，然后用二维前缀和判断一下有没有沼泽地，最后算一下面积，取最大值 就是答案。

时间复杂度 $O(n^4)$ ，很明显会超时。

暴力代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[1145][1145];
int query(int x1,int y1,int x2,int y2){
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char s;
			cin>>s;
			sum[i][j]=-sum[i-1][j-1]+sum[i-1][j]+sum[i][j-1]+(s=='X');
		}
	}
	int ans=0;
	for(int x1=1;x1<=n;x1++){
		for(int y1=1;y1<=m;y1++){
			for(int x2=x1;x2<=n;x2++){
				for(int y2=y1;y2<=m;y2++){
					if(x1==x2&&y1==y2||query(x1,y1,x2,y1)||query(x1,y1,x1,y2)||query(x2,y1,x2,y2)||query(x1,y2,x2,y2))continue;
					ans=max(ans,(x2-x1+1)*(y2-y1+1));
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

### 优化

我们可以枚举一个矩形的两列竖边 $l_1$ 和 $l_2$ ，然后枚举所有在 $[l_1,l_2]$ 间没有沼泽的横边，处理出来放到一个数组 $q$ 里，如图

我们已经保证横边没有沼泽了，我们还需要找出两条横边，且两条横边夹着的两条竖边间没有沼泽，这样就能求出矩形的面积，然后取最大值。

问题是我们要找出两条横边并且是复杂度是 $O(n)$ 的，怎么找？

定义两个指针 $p_1$ 和 $p_2$ ，遍历一下数组 $q$ ，令当前下标为 $i$ ，让 $p_2$ 等于 $i$ ，如果 $p_1$ 到 $p_2$ 间有沼泽，令 $p_1$ 等于 $p_2$ ，否则不变，计算此时的面积，取最大值。

关于这样做正确性证明：如果能走到 $[p_1,p_2-1]$ 这里，那么 $[p_1,p_2-1]$ 之间肯定是没有沼泽的，如果在 $[p_1,p_2]$ 间发现了沼泽，那么沼泽肯定是在 $[p_{2}-1,p_2]$ 之间的，也就是说区间想以 $p_2$ 结尾，开头肯定只能从 $p_2$ 开始。

时间复杂度 $O(n^3)$ 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[1145][1145],q[1145];
int query(int x1,int y1,int x2,int y2){
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char s;
			cin>>s;
			sum[i][j]=-sum[i-1][j-1]+sum[i-1][j]+sum[i][j-1]+(s=='X');
		}
	}
	int ans=0;
	for(int l1=1;l1<=m;l1++){
		for(int l2=l1;l2<=m;l2++){
			int st,ed,p=0;
			for(int l3=1;l3<=n;l3++){
				if(!query(l3,l1,l3,l2))q[++p]=l3; //预处理合法的横边
			}
			if(p==0)continue;
			st=ed=q[1];
			ans=max(ans,(ed-st+1)*(l2-l1+1));
			for(int i=1;i<=p;i++){
				ed=q[i];
				if(query(st,l1,ed,l1)||query(st,l2,ed,l2)){
					st=ed; //如果[p1,p2]有沼泽，那么p1=p2
					ans=max(ans,(ed-st+1)*(l2-l1+1));
				}
				else ans=max(ans,(ed-st+1)*(l2-l1+1)); //否则可以走过来，不变
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

比较奇怪的一道题。只要会爆搜就行。可以说是暴力碾标算吧。

## 题目大意

给定一个字符矩形 $\mathrm{g}$，其中 $\texttt{.}$ 代表平地，$\texttt{X}$ 代表沼泽。在矩形 $\mathrm{g}$ 中找到一个面积最大的矩形，使得矩形的四条边所在的字符都不是 $\texttt{X}$。

## 题目分析

抱着试一试的心态，我们可以写一个搜索。

首先我们可以遍历矩形的左上角，再遍历矩形的右下角，判断四条边是否合法并统计答案。判断四条边是否合法可以用前缀和做到 $\mathrm{O(1)}$ 的复杂度，总复杂度 $\mathrm{O(n ^ 4)}$。

当然这样的算法一定会超时。考虑进行剪枝。

 - 首先，如果当前答案是 $\mathrm{s}$，当前枚举的矩形长是 $\mathrm{x}$。那么矩形宽一定要严格大于 $\mathrm{\dfrac{s}{x}}$。这样可以减少第二层循环量。
 
 - 其次，如果当前矩形长已经覆盖了沼泽，后面枚举一定也会。应该直接剪掉。
 

于是就可以愉快的过题了。

## 代码示例

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define dop(i, a, b) for (int i = (a); i > (b); i -- )

using namespace std;

using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;

const int N = 210;
int n, m, ans, g[N][N];
char ch[N];
int col[N][N], row[N][N];

void solve(int x, int y) {
	for (int tx = x; tx <= n; tx ++ ) {
		if (col[tx][y] - col[x - 1][y]) break;
		for (int ty = max(y, (int)ceil(ans / (tx - x + 1) + y - 1)); ty <= m; ty ++ ) {
			if (row[x][ty] - row[x][y - 1]) break;
			if (row[tx][ty] - row[tx][y - 1]) break;
			if (col[tx][ty] - col[x - 1][ty]) continue;
			ans = max(ans, (tx - x + 1) * (ty - y + 1));
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) {
		scanf("%s", ch + 1);
		rep(j, 1, m) g[i][j] = (ch[j] == 'X');
	}
	rep(i, 1, n) rep(j, 1, m)
		row[i][j] = row[i][j - 1] + g[i][j],
		col[i][j] = col[i - 1][j] + g[i][j];
	rep(i, 1, n) rep(j, 1, m) {
		if (g[i][j]) continue;
		solve(i, j);
	}
	printf("%d\n", ans);
	return 0;
}
```

### 说在最后

真的没有想到暴力可以碾压标算。

纪念一下通过各种~~卑鄙~~巧妙的方法卡到的最优解。希望可以加强数据。

---

## 作者：_Blue_ (赞：1)

#### 题目
[P3135 [USACO16JAN]Fort Moo P](https://www.luogu.com.cn/problem/P3135)   
>观前提示：**贪心的暴力可过此题**，且速度或比正解更快，但正解思想更加优秀。  
  
#### 前置内容  
[更好的阅读体验](https://www.luogu.com.cn/blog/bluecyw/solution-p3135)    

本题是 [最大子段和](https://www.luogu.com.cn/problem/P1115) 的一个**扩展**。  
#### 思路  
**先看数据范围。**  
$$1\le n,m\le200 $$  
可以想到 ${O(N^{3})}$ 的时间复杂度可以通过此题。  
>注：贪心的暴力可以通过此题的原因是**较难造出能让贪心跑满的数据**，而正解却是跑满了 ${O(N^{3})}$ 。 
  
联想到**最大子段和**的做法：  
>从第一个数开始选择，每加入一个数都记录最大值，若当前数和小于零，则将数和清零。   

通过这样的做法，我们避免了枚举左端和枚举右端的 ${O(N^{2})}$ 的低效做法，我们需要思考的是，这样**为何更优**？   

我们这里不从 DP 的角度来分析。   

考虑这样一个有穷数列：  
```cpp
i= 1 2 3 4 5  6
   2 3 1 5 2 -20
```
假如我们使用**暴力的解法**：   
- 从第一个数开始，遇上 ${-20}$ 时数和为零，该子段和对于后面的字段和无用，清零。  
- 从第二个数开始，遇上 ${-20}$ 时数和为零，该子段和对于后面的字段和无用，清零。  
- ……   

可以发现，从第 ${1}$ 个数加到第 ${5}$ 数的过程中，数和都不为零。  
这样一来，以 ${2—5}$ 中的任何数作为起点都**无法对答案产生贡献**。  
那么我们将这一段操作删去，便优化了时间复杂度。   

---
回到本题  

考虑这样一个情况：  
我们确定了**子矩形的上边和下边**（没有具体确定长度）。  
>注，红色表示平地，黄色表示沼泽。  
  
  
![](https://cdn.luogu.com.cn/upload/image_hosting/1totypsy.png)
- 通过查询**上下点的地图情况**，判断是否能作为矩形的上下边的一部分。  
- 通过判断**每个点向上延伸的最大距离**，判断是否能作为矩形的左边框或右边框。    

例如上图，我们确定了上边和下边，发现第一列和第三，四列可以构成一个矩形。  
>那么还有无第三列作为从左边向右寻找的必要呢？  
>**没有必要**，因为第一列转移到第三列的过程中**没有发生阻断**，所以以第一列为左端点必然比第三列优。  

于是优秀的解法产生了。~~虽然跑不过贪心~~  

#### 解法  
>两层循环枚举起始行和中止行，预处理列的连通性。
>一层循环做dp:

>如果这两行中间的某一列是连通的，说明它有成为一堵纵向墙的资格。

>如果随着列的枚举，这两行的连通性被破坏(之间建不成横向墙)，那么前面的纵向墙就作废。

>如果一堵纵向墙前面还有另一堵未被作废的纵向墙，那么可用来更新答案。  
>--[潜翎](https://www.luogu.com.cn/user/101526)    
  
  
#### Code  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[205][205];
int d[205][205];
int ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		char s[205];scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='.')
				d[i][j]=d[i-1][j]+1; //记录向上延伸的平地数量 
			else 
				a[i][j]=1;//标记该点为沼泽 
		}
	}
	for(int i=1;i<n;i++)//枚举上边 
	
		for(int j=i+1;j<=n;j++){//枚举下边 
		
			int res=0;//记录但前选择了的列数（连续的） 
			int h=j-i+1;//表示当前矩阵的高 
			
			for(int k=1;k<=m;k++){//从左到右枚举每一列
			
				if(a[i][k]||a[j][k]) {
					/*
					此时上下至少有一点为沼泽，连通性被破坏
					那么无论我们当前是否找到左边框，res都要清零
					*/
					res=0; 
					continue;
				}
				
				/*
				不连通的情况已经continue，处理到这里的都连通的情况 
				那么无论如何选择的列数都会加一
				*/ 
				res++;
				if(res==1){//之前没有找到左边框，尝试当前列 
					if(d[j][k]>=h)  
						continue;//上下连通，可以作为边框
					else 
						res=0;//没有左边框，无法开始选择 
				}
				else{//已经找到了左边框，寻找右边框 
					if(d[j][k]>=h)
						//找到一个可能的右边框（不一定最优
						ans=max(ans,res*h); 
					else
						continue;
				}
			}
		}
		
	printf("%d\n",ans); 
} 
```

---

## 作者：大菜鸡fks (赞：1)

这题主要就是枚举。 固定左右两边，O（n）枚举中间部分

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=205;
int n,m,b[N][N];
char a[N][N];
inline void init(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
	}
	for (int j=1;j<=m;j++){
		for (int i=1;i<=n;i++){
			if (a[i][j]=='X') b[i][j]=b[i-1][j]+1;
				else b[i][j]=b[i-1][j];
		}
	}
}
int ans;
inline void solve(){
	for (int i=1;i<=n;i++){
		for (int j=i;j<=n;j++){
			int x=0,y=0;
			for (int k=1;k<=m;k++){
				if (b[j][k]-b[i-1][k]==0){
					x=max(x,k);
					y=x;
					while (x<m&&a[i][x+1]=='.'&&a[j][x+1]=='.'){
						x++;
						if (b[j][x]-b[i-1][x]==0) y=x;
					}
					ans=max(ans,(j-i+1)*(y-k+1));
				}
			}
		}
	}
	printf("%d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P3135)

题目大意：

现给定一个 $n$ 行 $m$ 列的字符矩阵 $c$。请输出能围出的最大竖直摆放的矩形面积，使得矩形的边上没有 $\texttt{X}$。

思路：

使用前缀和优化暴力的算法可以通过本题，时间复杂度为 $\Theta(n^2m^2)$。在本题解中，我们将讨论 $\Theta(n^2m)$ 的解法。

我们先枚举矩阵的左上角和右下角的横坐标，不妨设左上角的横坐标为 $i$，右上角的横坐标为 $j$。我们预处理出 $r_{i,j}$ 表示第 $i$ 行前 $j$ 列有多少个 $\texttt{X}$，$c_{i,j}$ 表示第 $j$ 列前 $i$ 行有多少个 $\texttt{X}$。特别的，$r_{i,0}=c_{0,i}=0$。显然 $k$ 对于 $\forall m\in[i,j]\cap\mathbb{N}$ 都有 $c_{m,k}$ 不是 $\texttt{X}$ 等价于 $c_{j,k}=c_{i-1,k}$。所以，我们可以通过枚举一遍 $k$ 来处理出一个长度为 $a$ 数组 $p$，其中的元素严格从小到大排列且所构成的集合为上述所有 $k$ 所构成的集合。然后，我们用双指针的方法来在线处理出对于每一个纵坐标 $k$ 的最大 $l$ 使得以 $(i,k)$ 为左上角、$(j,l)$ 为右下角的矩形的边框上没有 $\texttt{X}$。具体详见代码。然后，我们将所有 $(j-i+1)(l-k+1)$ 的最大值算出来输出即可。

上代码：

```cpp
#include <iostream>
using namespace std;

char mp[201][201];
int pre_row[201][201], pre_column[201][201], column[201];

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);// cin、cout 优化
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> mp[i][j];
        }
    }
    // 预处理前缀和
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            pre_row[i][j] = pre_row[i][j - 1];
            if (mp[i][j] == 'X'){
                pre_row[i][j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            pre_column[i][j] = pre_column[i - 1][j];
            if (mp[i][j] == 'X'){
                pre_column[i][j]++;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++){
        for (int k = i; k <= n; k++){
            // 预处理出所有满足条件的纵坐标
            int sz_column = 0;
            for (int j = 1; j <= m; j++){
                if (pre_column[k][j] == pre_column[i - 1][j]){
                    column[++sz_column] = j;
                }
            }
            int lft = 1, rght = 1;
            while (lft <= sz_column){
                if (mp[i][column[lft]] == 'X' || mp[k][column[lft]] == 'X'){// 如果满足条件的纵坐标已经找完
                    break;
                }
                rght = lft;
                while (rght < sz_column && pre_row[i][column[rght + 1]] == pre_row[i][column[lft] - 1] && pre_row[k][column[rght + 1]] == pre_row[k][column[lft] - 1]){// 判断横向的边框上没有 X
                    rght++;
                }
                ans = max(ans, (k - i + 1) * (column[rght] - column[lft] + 1));
                lft = rght + 1;
                while (lft < sz_column && mp[i][column[lft]] == 'X'){// 继续寻找新的起点
                    lft++;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Nephren_Sakura (赞：0)

首先，我们可以考虑暴力枚举出来矩阵的最左方在那一列和最右方在哪一列。

然后考虑枚举行，设当前行为 $i$。

显然可以预处理前缀和求出每一行的每一段区间有多少个沼泽地。

然后，因为我们要求面积最大，所以我们维护一个 $last$ 表示满足条件的不超过 $i$ 的与 $i$ 距离最远的行。（这句话可能有点绕，请好好理解）

设最左列为 $l$，最右列为 $r$。

分情况讨论：

1. 若 $c_{i,l}$ 为沼泽地或 $c_{i,r}$ 为沼泽地，显然在 $i$ 上方的所有 $last$ 都不满足条件，先将 $last=i+1$，然后继续往下找直到找到一个满足条件的 $last$。

2. 若第 $i$ 行的 $l$ 列到 $r$ 列之间都没有沼泽地，更新答案。

3. 否则不做任何操作。

下面给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,sum[205][205],maxi=0;
char c[205][205];
bool check(int h,int l,int r){
	return sum[h][r]-sum[h][l-1]==0;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>c[i][j];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			sum[i][j]=sum[i][j-1]+(c[i][j]=='X');
	for(int l=1; l<=m; l++){
		for(int r=l; r<=m; r++){
			int last=1,mx=0;
			for(int i=1; i<=n; i++){
				if(c[i][l]=='X'||c[i][r]=='X'){
					last=i+1;
					continue;
				}
				while(check(last,l,r)==false)
					last++;
				if(check(i,l,r)==true)
					mx=max(mx,i-last+1);
			}
			maxi=max(maxi,(r-l+1)*mx);
		}
	}
	cout<<maxi;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

## 题目简述:
- 给出 $n$ , $m$ 及$n*m$的字符阵
- 在 ```.``` 上用围栏围长方形
- 求最大长方形面积

## 题目分析：
~~200引导我们思考$O(n^3)$~~

这题显然是dp题，然而用 $O(n^3)$ 解的dp题中最经典的就是[最大矩阵和](https://www.luogu.com.cn/problem/P1719)啦

我们复习一下最大矩阵和的做法就好了

- 枚举顶行和末行
- 预处理前缀和 $d_n$
- 计算 $f_n$ 即可



但是这样的方法显然不适合我们这道题，但是我们可以借鉴里面的思路

以下是我个人的思路：

- 为了节省空间，我们可以使用 $a_{i,j}$ 表示 第 $i$ 行 $j$ 列的字符是不是 ```.```

- 为了节省空间，把 $d_n$ 也改写成 $d_k$ 表示当前枚举的 $i,j$ 所对应的列 $k$ 是否一列都是 ```.```

- 定义 $l$ 表示当前枚举到 $k$ 时最往左并可行的一列，相对应的还要一个 $flag$ 表示有没有这样的 $l$

## 完整代码献上

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
const int MAXN=205;
int n,m;
bool a[MAXN][MAXN];//节省空间，a[i][j]表示i行j列是否‘.’
char kkk;
int ans=0;
bool d[MAXN];//d[k]记录第i行到第j行是否都为‘.’
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++){
    		cin>>kkk;
    		a[i][j]=(kkk=='.');
    	}
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++)
    		d[j]=true;//清零
    	for(int j=i;j<=n;j++){
    		int l=0;//当前左端
    		bool flag=false;//记录是否使用中
    		for(int k=1;k<=m;k++)
    			d[k]=(a[j][k]&&d[k]);
    		//更新d[k]
    		for(int k=1;k<=m;k++){
    			if(a[i][k]&&a[j][k]){
    				if(d[k]){
    					if(flag)
    						ans=max(ans,(k-l+1)*(j-i+1));
    					else{
    						flag=true;
    						l=k;
    					}
    				}
    			}
    			else
    				flag=false;
    		}
    	}
    }
    cout<<ans;
}
```

祝：早日AC []~(￣▽￣)~*


---

## 作者：MuYC (赞：0)

#### 前言

~~我又双叒叕来水沝淼㵘题解了~~

这道题的思路大概是指针 + 暴力枚举 以及悬针法优化。

（不是很懂为什么会出现动态规划的标签）

#### 具体做法：

相信一道叫玉蟾宫的题目大家都做过。

那道题的一个最重要的技巧就是悬针法（这个不会的可以到玉蟾宫的题解那里学）。

这道题的数据范围很显然的来看 O($n^4$) 是过不了的.....

思考如何优化至 O($n ^ 3$)。

不难发现我们肯定要预处理每一个点向上以及向右最远能扩展的地方(可以 $n^2$ 或者 $n^3$ 预处理，影响不大)。

然后我们枚举两行，就假定为 $i$ 行以及 $j$ 行，不妨钦定 $i < j$

然后枚举第 $j$ 行 的所有列 $k$ ， 如果第 $j$ 行的第 $k$ 列那一个点，最远能到达的最上面的点的横坐标小于等于 $i$ , 那么就说第 $k$ 列是备选点，放入队列。


接下来就好办了，这些备选点中(肯定是按照列号递增的)，有些点是可以构成一个框架的，但是有一些是无法连接的，这个在前面说到的悬针法可以预处理出来。

我们借助一个指针，枚举当前可选点最远能扩展到的可选点，不难发现这个指针是只增不减的，同时下一次枚举的起点就是现在指针的位置了（这个应该也很容易想到，因为枚举当前起点和当前指针的中间的点是没有意义的），那么总的时间复杂度就是 O($n ^ 3$) 的了。

一个小细节就是当扩展不了的时候就强制从指针的下一个位置开始枚举，还有就是注意移动指针的时候要取上下两个点的 min ，因为是要形成一个矩形框架，不能一边长一边短，因此要取 min。

### Code

(本人较菜，上面可能不是很清楚，看看代码吧)


```cpp
#include <bits/stdc++.h>
using namespace std;
int H[505][505],R[505][505],vis[505];
char mp[505][505];
int n,m;
int main()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n; i ++)
        cin >> mp[i] + 1;
    memset(H,0x3f,sizeof(H));//一开始一定要初始化
    memset(R,0,sizeof(R));
    //我选择的是n^3预处理
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= m ; j ++)
        {
            if(mp[i][j] == 'X') continue;
            for(int k = i ; k >= 1 ; k --)
            {
                if(mp[k][j] == 'X') break;
                H[i][j] = k;//悬针法求向上面能够到达的最远点
            }
            for(int k = j ; k <= m ; k ++)
            {
                if(mp[i][k] == 'X') break;
                R[i][j] = k;//悬针法求向右能够到达的最远点
            }
        }
    }
    int Ans = -1;
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = i + 1; j <= n ; j ++)
        {
            int tail = 0;
            for(int k = 1 ; k <= m ; k ++)
            if(H[j][k] <= i) tail ++ , vis[tail] = k;//可选点入队
            int Now = 0;//Now表示指针
            while(Now <= tail)
            {
                int x = Now;
                while(min(R[i][vis[x]],R[j][vis[x]]) >= vis[Now + 1] && Now < tail) Now ++;
                //注意取min，然后判断向右能扩展的最远点是否大于等于指针指到的可选点即可，最后取到的就是最远能够扩展到的可选点
                if(x == Now) {Now ++ ;continue;}//扩展不动了强行移动
                Ans = max(Ans, (vis[Now] - vis[x] + 1) * (j - i + 1));//底乘高得到面积，最终答案取Max
            }
        }
    }
    cout << Ans;
    return 0;
}
```

---

## 作者：Saber_Master (赞：0)

[[USACO16JAN]Fort Moo P](https://www.luogu.com.cn/problem/P3135)

这题的思路挺好的，来发篇题解。

这题$n,m\leq200$,所以复杂度不难往三次方上面靠.

对于一个$n*m$的矩阵来讲，我们有一个套路性的技巧：$n^2$枚举行，想办法用$O(m)$复杂度处理列，然后就可以做到三次方复杂度枚举子矩阵.用到这思路的还有[这题](https://www.luogu.com.cn/problem/P3941)

然后就有如下算法：

1. $O(n^2)$枚举两行，将两行之间的若干行矩阵压缩成一行.

2. 扫描每一列，若两行间该列上下联通，则$dp$统计面积.

统计面积很简单，直接记录一下就好，我们需要思考的是如何$O(1)$判联通.

这里用了一种类似于[悬线法](https://www.luogu.com.cn/problem/P4147)预处理的思路：$O(n*m)$扫描出每个点最上方的不为$X$所在行的编号$up_x$，即$up_x$要么是$1$要么上面是障碍.这样我们只需判断$up_{j,k}$是否小于等于$up_{i,k}$即可判断$i,j$两行在第$k$列处是否联通

具体详见代码

复杂度$O(n^2m+n*m)$

```cpp
const ll N=2e2+2;

ll n, m;

char mp[N][N];
ll up[N][N];
int res;
int main(){
	read(n); read(m);
	for (R ll i=1; i<=n; i++) scanf("%s", mp[i]+1);
	for (R ll i=1; i<=n; i++)
		for (R ll j=1; j<=m; j++){
			if (mp[i][j]=='X') continue;
			if (up[i-1][j]) up[i][j]=up[i-1][j];
			else up[i][j]=i;
		}
	for (R ll i=1; i<=n; i++)
		for (R ll j=i+1; j<=n; j++)
			for (R ll k=1, last=0; k<=m; k++){
				if (mp[i][k]=='X' || mp[j][k]=='X') last=0;
				else {
					if (up[j][k]<=i){
						if (last) chkmax(res, (k-last+1)*(j-i+1));
						else last=k;
					}
				}
			}
	writeln(res);
}
```


---

## 作者：Vin_1999 (赞：0)

暴力的话是o(n^5)的，预处理一下变n^4，但是只能过60分。

蒟蒻我加了个散列表，变成了76分。然后就一直在想动规解法。

后来看了某大神的思路，发现只用枚举上下或左右边界就行了，也就是定长或定宽，然后来一遍扫描，就变成了o(n^3)。

原来代码其实是o(n^4)的，但是有这个强力剪枝，所以ac了。

貌似预处理的好可以直接n^3，又想了一下，其实自己预处理冗余了。

但是就算自己优化了代码也还是n^4，orz。（可是最慢的点也只跑了58ms）

所以这跟动规有毛线关系了？期待神牛的动规解法。






  

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<cstring>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int maxn=210;
static bool G[maxn][maxn];
static int dp[maxn][maxn][2],n,m,ans;//0 xiang you 1 xiang xia
//然而这数组和动规没有毛线关系 
inline void init()
{
    scanf("%d%d",&n,&m);
    char x;
    rep(i,1,n) rep(j,1,m)
    {
        x=getchar();
        while(x!='.'&&x!='X') x=getchar();
        if(x=='.') G[i][j]=1;
  } 
  rep(i,1,n) for(int j=m;j;j--) if(G[i][j]){dp[i][j][0]=dp[i][j+1][0]+1;}
    rep(j,1,m) for(int i=n;i;i--) if(G[i][j]) dp[i][j][1]=dp[i+1][j][1]+1;
}
int main()
{
    freopen("e:/in.txt","r",stdin);
    init();
    rep(i1,1,n) 
    {
    rep(j1,1,m)
        {
          for(int i2=i1+dp[i1][j1][1]-1;i2>=i1;i2--)
          {
              int a=i2-i1+1,lim=min(dp[i1][j1][0],dp[i2][j1][0]);
              for(int j2=j1+lim-1;j2>=j1;j2--) 
              if(dp[i1][j2][1]>=a)
              {
                  ans=max(ans,a*(j2-j1+1));
                  break;
                }
          }
        }
  } 
  /*rep(i,1,n) 
  {
      rep(j,1,m) printf("%d",G[i][j]);
      printf("\n");
    }*/
    printf("%d",ans);
    return 0;
}//copyright-fjlyyz ljy
```

---

