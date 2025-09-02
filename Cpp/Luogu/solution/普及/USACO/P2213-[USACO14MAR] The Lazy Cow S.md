# [USACO14MAR] The Lazy Cow S

## 题目描述

It's a hot summer day, and Bessie the cow is feeling quite lazy.  She wants

to locate herself at a position in her field so that she can reach as much

delicious grass as possible within only a short distance.


The field Bessie inhabits is described by an N by N grid of square cells

(1 <= N <= 400).  The cell in row r and column c (1 <= r,c <= N) contains

G(r,c) units of grass (0 <= G(r,c) <= 1000).  From her initial square in

the grid, Bessie is only willing to take up to K steps (0 <= K <= 2\*N).

Each step she takes moves her to a cell that is directly north, south,

east, or west of her current location.


For example, suppose the grid is as follows, where (B) describes Bessie's

```cpp
50    5     25*   6     17    
14    3*    2*    7*    21    
99*   10*   1*(B) 2*    80*    
8     7*    5*    23*   11   
10    0     78*   1     9        
```

initial position (here, in row 3, column 3):

If K=2, then Bessie can only reach the locations marked with \*s.

Please help Bessie determine the maximum amount of grass she can reach, if

she chooses the best possible initial location in the grid.

奶牛贝茜非常懒惰，她希望在她的地盘内找到一点最佳位置居住，以便在有限的步数内可以吃到尽量多的青草。

她的地盘是一个 $N \times N(1\le N \le 400)$ 的矩阵，第 $r$ 行 $c$ 列包含 $G(r,c)$ 单位的青草 $(0 \le G(r,c) \le 1000)$。从她的居住点，她最多愿意走 $K$ 步 $(0 \le K \le 2 \times N)$，每一步她可以走到上与她相邻的某个格子。

## 说明/提示

OUTPUT DETAILS:


In the example above, Bessie can reach 342 total units of grass if she

locates herself in the middle of the grid.


Source: USACO 2014 March Contest, Silver


## 样例 #1

### 输入

```
5 2
50 5 25 6 17
14 3 2 7 21
99 10 1 2 80
8 7 5 23 11
10 0 78 1 9
```

### 输出

```
342```

# 题解

## 作者：yxy666 (赞：19)

这道题的做法是旋图。
是的，你没有听错。因为直接模拟各种细节实在是太负杂了。但我我们把脑袋旋转45度后再看，就看舒服多了。使 $( i , j )$ 的位置旋到 $( i+j-1 , n-i+j )$。 

详见图：![](https://cdn.luogu.com.cn/upload/image_hosting/f1ts0ruw.png)

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define maxn 2005
using namespace std;
int N,K,ans,mp[maxn][maxn],F[maxn][maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-')f=-f;ch=getchar();}
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	N=read(),K=read();
	for (int i=1;i<=N;i++)
	for (int j=1;j<=N;j++) mp[i+j-1][N-i+j]=read();
	for (int i=1;i<2*N;i++)
	for (int j=1;j<2*N;j++) F[i][j]=F[i-1][j]+F[i][j-1]-F[i-1][j-1]+mp[i][j];
	for (int i=1;i<=N;i++)
	for (int j=1;j<=N;j++){
		int now_x=i+j-1,now_y=N-i+j;
		int x_l=max(0,now_x-K-1),y_l=max(0,now_y-K-1),x_r=min(2*N-1,now_x+K),y_r=min(2*N-1,now_y+K);
		ans=max(ans,F[x_r][y_r]-F[x_l][y_r]-F[x_r][y_l]+F[x_l][y_l]);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Ajwallet (赞：8)

#前缀和+处理边界

可以利用前缀和的思想，省去一重循环，用h[i][j]表示第i行前j个数的前缀和。然后用u循环i-k行-i+k行，对这三行要求的值进行处理，再处理边界。

简单解释一下，一组数

:3 7  6  4  2

前缀和:3 10 16 20 22

假设我要7,6,4，那么我可以用h[4]（暂时先一维，待会扩展）-h[1]就可以得到了。

拓展到二维也是一样的道理，不过开头和结尾需要处理边界。

代码
```cpp
#include<cstdio>
#define r(i,a,b) for(int i=a;i<=b;i++)
#define N 402
using namespace std;
int ans,n,k,p[N][N],h[N][N],now,mid,maxn;
int max(int x,int y){return x>y?x:y;}
int main()
{
    scanf("%d %d",&n,&k);
    r(i,1,n)
     r(j,1,n)
      {scanf("%d",&p[i][j]);maxn=max(p[i][j],maxn);h[i][j]=h[i][j-1]+p[i][j];}
    if(!k) {printf("%d",maxn);return 0;}//特殊处理，当这头牛懒得连一步都不愿意走，输出最大值（站在原地吃草）。
    r(i,1,n)
     r(j,1,n)
     {
      now=0;
      r(u,i-k,i+k)
      {
          if (u<1) u=1;if(u>n) break;//处理边界，如果小于1直接变成1，大于n直接退出
        int uu=i-u>0?i-u:u-i;int uuu=j+k-uu>n?n:j+k-uu;int uuuu=j-k+uu<0?1:j-k+uu;//uu可以理解为abs(i-u)，就是i和u之间相距几行，uuu是奶牛站在第i行第j列的时候能走到第u行的最远的距离，同时处理边界，因为它不能走出这块地。uuuu则是第u行我能走到的最前面的那个，后面的判断是因为我有可能可以走完整一行，那uuuu的值就会是负数了，所以要变成1，而后面还会减一，也就是0了，不会造成越界
          now+=h[u][uuu]-h[u][uuuu-1];//累加
      }
      ans=max(ans,now);//保留最优解
     }
    printf("%d",ans);//输出
}
```

---

## 作者：一只野生蒟蒻 (赞：3)

dalao们旋转后n^2的算法以本蒟蒻的智商实在是理解不了，但这题的n非常非常非常小，所以我就用了一种不用旋转的n^3的算法，照样可以过，而且理解起来和码起来都容易很多~ 

仔细读一遍题就知道，奶牛能吃到的草其实就是一个菱形的面积，所以就定义一个s数组，s[i][j]表示第i行前j个数的和，然后再直接求出菱形的面积就行了。时间复杂度为n^3。

参考代码：
```
#include <bits/stdc++.h>
using namespace std;
int k,n,ans=-1,s[404][404];
int read()//快读 
{
	int f=1;
	char c;
	while ((c=getchar())<'0'||c>'9')
		if (c=='-') f=-1;
	int x=c-'0';
	while ((c=getchar())>='0'&&c<='9')
		x=x*10+c-'0';
	return x*f;
}
int sum(int x,int y)
{
	int t=0;
	for (int i=x-k;i<=x+k;i++)
		if (i>=1&&i<=n)//行边界 
		{
			int l,r;//处理菱形形状 
			if (i<=x)
			{
				l=y-(i-x+k);
				r=y+(i-x+k);
			}
			else
			{
				l=y-(x+k-i);
				r=y+(x+k-i);
			}
			if (l<1) l=1;
			if (r>n) r=n;//列边界 
			t+=s[i][r]-s[i][l-1];//累加面积 
			//printf("%d %d\n",l,r);
		}
	return t;
}
int main()
{
	n=read(); k=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			s[i][j]=s[i][j-1]+read();//处理前缀和 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			ans=max(ans,sum(i,j));//以每个点为中心求一遍菱形面积，记录下最大值 
	printf("%d",ans);//输出 
	return 0;
}
```
这种n^3的算法好想好写，也只用到了数组和循环，非常适合初学者练手~


~~顺便吐槽一下，这题数据这么小，以至于能用n^3的做，哪有
提高+/省选- 的难度，最多 普及/提高-。就算只能用n^2做，那也只有 普及+/提高 吧。~~

---

## 作者：nzcnnr (赞：1)

# 题目思路
本人使用了 $O{(n^3)}$ 算法，不喜勿喷。

因为变量 $k$ 已知，所以说关于一个点的所有可以到的点便在一个一这个点为中心的菱形中，当然，这个菱形可能会不全在正方形内，此时，我们便要求的就是菱形与正方形相交部分的数总和。

那应该怎么求相交部分呢？利用前缀和，不过这一次的前缀和有所特殊，并非标准二维前缀和，而是为该行的前缀和，类似多个一维前缀和，也就是说对于一个点的前缀和 $sum_{i,j}=sum_{i,j-1}+num_{i,j}$。

总共有 $n^2$ 个点，由于利用前缀和优化使得求菱形与正方形相交部分的数总和的次数为 $n$ 次，所以说，复杂度为 $O{(n^3)}$。

剩下的就是代码部分（注释均在代码内）。
# CODE
```c
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int map[405][405];
int dp[405][405];//前缀和数组
int n,k;
long long ans=-1;//答案初始化
void point(int x,int y,int k,int n){
	long long num=0;
	for(int i=max(1,x-k);i<=min(n,x+k);i++){//注意边界
		int kp=k-abs(x-i);
    	    //我们注意到，在x轴方向和y轴方向移动距离之和为k，符合菱形特性
		num+=dp[i][min(n,y+kp)]-dp[i][max(0,y-kp-1)];//注意边界
	}
	ans=max(num,ans);
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&map[i][j]);
			dp[i][j]=dp[i][j-1]+map[i][j];//单行前缀和计算
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			point(i,j,k,n);//枚举每一个点
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Expecto (赞：1)

啊啊啊啊啊啊不小心被卡了一个点

注意k=2n时直接输出sum啊

每个点线性转移上个点的值，扣掉两个斜行，加上两个斜行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[404][404],n,k;
int main(){
    scanf("%d%d",&n,&k);
    int sum=0;
    for (int i=1;i<=n;i++)
       for (int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            sum+=a[i][j];
       }
    if (k>=n*2) {
        cout<<sum;
        return 0;
    }
    int ans=0;
    for (int i=1;i<=n;i++){
        int tmp=0;
        for (int x=-k;x<=k;x++)
            for (int y=0;abs(x)+y<=k;y++)
            if (i+x>0 && i+x<=n && y+1<=n)
                tmp+=a[i+x][1+y];
        ans=max(tmp,ans);
        for (int j=2;j<=n;j++){
            int x,y;
            for (x=i-k,y=j-1; x<=i;x++,y--)
                if (x>0 && y>0 ) tmp-=a[x][y];
            for (x=i-k,y=j;  x<=i;x++,y++)
                if (x>0 && y<=n) tmp+=a[x][y];
            for (x=i+k,y=j-1; x>i;x--,y--)
                if (x<= n && y>0) tmp-=a[x][y];
            for (x=i+k,y=j;x>i;x--,y++)
                if (x<=n && y<=n) tmp+=a[x][y];  
            ans=max(tmp,ans);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Link_Space (赞：0)

题解大佬有 $N^2$ 做法，我太菜了没想到怎么旋转就打了暴力 $N^3$ ，由于数据范围只有400，实际可能更小，所以还是可以通过此题。

做法是先 $N^2$ 预处理前缀和数组之后 $N^3$ 暴力判断每一个点的最多吃到的草，然后取最大值即可，对于此题还需要考虑边界问题，如果超出了边界应该自动忽略。

以下是代码，由于是 $N^3$所以很短很清晰

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1e3 + 5;
int sum[N][N];
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            int a;
            scanf("%d", &a);
            sum[i][j] = sum[i][j - 1] + a;
        }
    }
    int maxn = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            int all = 0;
            for (int now = max(1, i - k); now <= min(i + k, n);now++)
            {
                if(now<=i)//记得考虑边界
                    all += sum[now][min(j + k - i + now, n)] - sum[now][max(j - k + i - now - 1, 0)];
                else
                    all += sum[now][min(j + k - now + i, n)] - sum[now][max(j - k + now - i - 1, 0)];
            }
            maxn = max(maxn, all);
        }
    }
    printf("%d\n", maxn);
}
```


---

## 作者：moosssi (赞：0)

这前缀和水题啊，直接 $O(n^3)$ 可过。

题意应该都清楚，大概可以看成一个正的三角形加一个倒着的三角形，我们设 $h[i][j]$ 表示第 $i$ 行前 $j$ 列的总和。

依次枚举选取的中心位置 $(i,j)$，再枚举第 $i-k$ 到 $i+k$ 行，利用前缀和计算每一行值，得到总和后，每次更新最大值即可，具体见代码。

注意，要仔细考虑边界问题，不然很容易出错。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,k,h[N][N],ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&h[i][j]);
			h[i][j]+=h[i][j-1];//预处理前缀和 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int sum=0,d=0;
			for(int l=i-k;l<=i;l++,d++){//枚举正着的三角形 
				if(l<1)continue;//超出上边界不计算 
				int r2=min(n,j+d);//枚举每一行左右位置，注意不要越界
				int r1=max(1,j-d);
				sum+=h[l][r2]-h[l][r1-1];
			}
			d-=2;
			for(int l=i+1;l<=min(i+k,n);l++,d--){//同理处理倒着的三角形 
				int r2=min(n,j+d);
				int r1=max(1,j-d);
				sum+=h[l][r2]-h[l][r1-1];			
			}
			ans=max(ans,sum);//每次记得更新最大值 
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

