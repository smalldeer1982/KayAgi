# Land Lot

## 题目描述

Vasya has a beautiful garden where wonderful fruit trees grow and yield fantastic harvest every year. But lately thieves started to sneak into the garden at nights and steal the fruit too often. Vasya can’t spend the nights in the garden and guard the fruit because there’s no house in the garden! Vasya had been saving in for some time and finally he decided to build the house. The rest is simple: he should choose in which part of the garden to build the house. In the evening he sat at his table and drew the garden’s plan. On the plan the garden is represented as a rectangular checkered field $ n×m $ in size divided into squares whose side length is 1. In some squares Vasya marked the trees growing there (one shouldn’t plant the trees too close to each other that’s why one square contains no more than one tree). Vasya wants to find a rectangular land lot $ a×b $ squares in size to build a house on, at that the land lot border should go along the lines of the grid that separates the squares. All the trees that grow on the building lot will have to be chopped off. Vasya loves his garden very much, so help him choose the building land lot location so that the number of chopped trees would be as little as possible.

## 说明/提示

In the second example the upper left square is (1,1) and the lower right is (3,2).

## 样例 #1

### 输入

```
2 2
1 0
1 1
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 5
0 0 1 0 1
0 1 1 1 0
1 0 1 0 1
1 1 1 1 1
2 3
```

### 输出

```
2
```

# 题解

## 作者：亦枫 (赞：4)

## Solution

题目大意：给你一个 $ n \times m $ 大小的矩阵，每个点的数字只为 $ 0 $ 或 $ 1 $，让我们求出其中面积为 $ a \times b $ 并且 $ 1 $ 的个数最少的一个子矩阵中的 $ 1 $ 的个数。

看到这道题，我们使用**二维前缀和**预处理，在进行枚举右下角的端点，得到一个子矩阵中 $ 1 $ 的个数，再取最小值即可。

**但是**，我们要注意，这题的子矩阵，横着放和竖着放都可以，所以要考虑两种情况。

Code：

```cpp
#include<bits/stdc++.h>
#define rt return
#define f(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
int n,m,a,b,tmp,ans=0x7fffffff,tree[55][55],c[55][55];
int main() {
	scanf("%d %d",&n,&m);
	f(i,1,n)f(j,1,m)scanf("%d",&c[i][j]);
	f(i,1,n)f(j,1,m)tree[i][j]=c[i][j]+tree[i][j-1];//先处理出每行的前缀和 
	f(i,1,m)f(j,1,n)tree[j][i]=tree[j][i]+tree[j-1][i];//在每行依次相加得到二维前缀和 
	scanf("%d %d",&a,&b);
	f(i,a,n)f(j,b,m)tmp=tree[i][j]-tree[i-a][j]-tree[i][j-b]+tree[i-a][j-b],ans=min(ans,tmp);//a*b的情况，竖着放的矩阵 
	f(i,b,n)f(j,a,m)tmp=tree[i][j]-tree[i-b][j]-tree[i][j-a]+tree[i-b][j-a],ans=min(ans,tmp);//b*a的情况，横着放的矩阵 
	printf("%d",ans);
	rt 0;
}
```


---

## 作者：wssdl (赞：2)

# 题目大意

给你一个 $n\times m$ 的矩阵，矩阵里只有 $0$ 与 $1$ 两种数值，如果一个位置为 $1$ 表示这个地方有一棵树，否则就没有树，再给你两个数 $a$ 和 $b$ 表示另一个小矩阵的范围，让你求出把这个小矩阵放在大矩阵中，覆盖的地方最多有几棵树。

# 解题思路

数据范围： $1\le n,m\le 50$ 。

真不错，数据范围告诉我们可以直接暴力枚举，那我们就可以直接枚举小矩阵的左上角点，再判断是否能摆放得下，但是这么做会 **WA** 因为把小矩阵放入大矩阵其实有两种摆法，假设这是个 $3\times 4$ 的大矩阵，要把一个 $2\times 3$ 的小矩阵放入其中，如图。

摆法 $1$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/85daznbc.png)

摆法 $2$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/3t0gxo0v.png)

所以我们在这里分开判断即可。

# 时空复杂度

时间复杂度： $O(nmab)$ 。

空间复杂度： $O(nm)$ 。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int n, m;            //给定矩阵
int a, b;            //摆放矩阵
int minx = INT_MAX;  //最小值，即答案
int mp[N][N];        //存储矩阵
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> mp[i][j];
    }
  }
  cin >> a >> b;
  for (int i = 1; i <= n; i++) {  //枚举左上角点
    for (int j = 1; j <= m; j++) {
      if (i + a - 1 <= n && j + b - 1 <= m) {  //判断越界
        int sum = 0;                           //两种情况分开判断
        for (int x1 = i; x1 <= i + a - 1; x1++) {
          for (int y1 = j; y1 <= j + b - 1; y1++) {
            sum += mp[x1][y1];  //可以直接加值，统计1的数量
          }
        }
        minx = min(minx, sum);
      }
      if (i + b - 1 <= n && j + a - 1 <= m) {  //同上
        int sum = 0;
        for (int x1 = i; x1 <= i + b - 1; x1++) {
          for (int y1 = j; y1 <= j + a - 1; y1++) {
            sum += mp[x1][y1];
          }
        }
        minx = min(minx, sum);
      }
    }
  }
  cout << minx;
  return 0;
}
```


---

## 作者：Elgo87 (赞：1)

对于这道题，翻译没有说清楚输入的格式，蒟蒻~~推测~~申明应该是这样：
```
输入第一行是两个数 n,m， 代表矩阵的长和宽。
输入第二行~第 n+1 行，每行 m 个数，代表城市的地图。
    其中 0 代表没有树木，1 代表有树木。
输入第 n+2 行是两个数 a 和 b， 代表房屋的长和宽。

```
## 本题思路
咳咳，回到正题。

本题不难，主要是有个坑，可以横放或竖放。

房屋的摆放我们可以分为 $a \times b$ 和 $b \times a$ 两种情况，也就是像下图一样：
![](https://cdn.luogu.com.cn/upload/image_hosting/vxid5efy.png)

我们看题目中的数据范围，不大，$1 \le n,m \le 50$，所以我们可以枚举房屋在场地上摆放的每一种情况。

而本题只需要枚举所有情况，然后计算当前子矩阵中前缀和的最小值。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m,a,b,x;
    int map[55][55]={0},s[55][55]={0};
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		cin>>x;
    		//计算前缀和数组s 
    		s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+x;
		}
	}
	cin>>a>>b;
	
	int ans=INT_MAX;
	for(int k=0;k<2;k++)//枚举横或竖 
	{
		for(int i=a;i<=n;i++)
		{
			for(int j=b;j<=m;j++)
			{
				//前缀和公式 
				ans=min(ans,s[i][j]-s[i-a][b]-s[x][j-b]+s[i-a][j-b]);
			}
		}		
		swap(a,b); //由于长宽可以交换，所以将房屋“旋转90°” 
	}


	cout<<ans;
	return 0;
}
```






---

## 作者：LiuHao2019 (赞：1)

[[更好的阅读体验]](https://www.luogu.com.cn/blog/LiuHao2019/solution-cf48b)

**[题目大意]** 在n×m的矩形中放一个a×b或b×a的矩形，使得这个a×b或b×a的矩形覆盖的数的和最小

本题数据范围非常小

>1 <= n,m <= 50
>
>1 <= a,b <= 50

可以直接暴力枚举a×b或b×a的矩形的左上角，四重循环即可

---

那么这题出题人是良心出题人 **吗**？

你一定注意到我之前说的话

>a×b或b×a的矩形

我们一下子就意识到这题出题人是个凉心出题人:

**a和b在题目中没有说明哪个是长，哪个是宽！**

其他也没有什么坑点了，所以这题出题人还算比较良心

---

[[AC记录]](https://www.luogu.com.cn/record/49690582)

[AC代码]

```
#include<stdio.h>
int n,m,a,b;
int tree[55][55];//数组不用开太大
int c;
int minn = 2500;//最大值为 n的最大值 × m的最大值 = 50 × 50 = 2500
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= m;j ++) scanf("%d",&tree[i][j]);
	scanf("%d%d",&a,&b);
   	//以上为输入
   
	for(int i = 1;i <= n-a+1;i ++)//枚举左上角纵坐标
		for(int j = 1;j <= m-b+1;j ++){//枚举左上角横坐标
			c = 0;//每次清零
			for(int i2 = i;i2 <= i+a-1;i2 ++)
				for(int j2 = j;j2 <= j+b-1;j2 ++) c += tree[i2][j2];
        		//计算砍了多少树
			if(minn > c) minn = c;//检查哪个砍的树更少
		}
	//处理a×b的矩形
   
	int tmp = a;
	a = b;
	b = tmp;
	//交换a,b(可替换为swap(a,b),但是需要加上iostream库和std命名空间)

	for(int i = 1;i <= n-a+1;i ++)//枚举左上角纵坐标
		for(int j = 1;j <= m-b+1;j ++){//枚举左上角横坐标
			c = 0;//每次清零
			for(int i2 = i;i2 <= i+a-1;i2 ++)
				for(int j2 = j;j2 <= j+b-1;j2 ++) c += tree[i2][j2];
                	//计算砍了多少树
			if(minn > c) minn = c;//检查哪个砍的树更少
		}
	//处理b×a的矩形
   
	printf("%d\n",minn);
	//输出
}
```

>kkksc03提醒您
>
>算法千万条
>
>理解第一条
>
>直接抄题解
>
>棕名两行泪

---

## 作者：ueettttuj (赞：1)

[题目](https://www.luogu.org/problem/CF48B)

这题很水，还是道灰题 ~~(都没人做)~~ 。

首先对矩形求一遍二维前缀和，新矩形$rec[i][j]$就表示原矩形以$(1,1)$为左上角，$(i,j)$为右下角的树的数量。然后我们要求以点$(i,j)$为右下角的大小为$a \times b$ 的矩形中的树的数量。由容斥原理可知，

以点$(i,j)$为右下角的大小为$a \times b$ 的矩形中的树的数量为$rec[i][j]-rec[i-a][j]-rec[i][j-b]+rec[i-a][j-b]$

以点$(i,j)$为右下角的大小为$b \times a$ 的矩形中的树的数量为$rec[i][j]-rec[i-b][j]-rec[i][j-a]+rec[i-b][j-a]$

画张图感受一下

![](https://cdn.luogu.com.cn/upload/pic/71271.png)

其中以点$(4,5)$为右下角的大小为$2\times 3$ 的矩形中的树为(红色方框$-$绿色方框$-$深蓝色方框$+$淡蓝色方框)，也就是$rec[4][5]-rec[2][5]-rec[4][2]+rec[2][2]$

最后，贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long mapp[51][51];
long long rec[51][51];
long long n,m,a,b;
long long ans;
int main(){
	scanf("%lld %lld",&n,&m);
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=m;j++){
			scanf("%lld",&mapp[i][j]);
		}
	}
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=m;j++){
			rec[i][j]=mapp[i][j]+rec[i][j-1];
		} 
	}
	for(long long i=1;i<=m;i++){
		for(long long j=1;j<=n;j++){
			rec[j][i]=rec[j][i]+rec[j-1][i];      //求二维前缀和(我写的比较麻烦) 
		}                                       
	}
	scanf("%lld %lld",&a,&b);
	ans=1000000007;
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=m;j++){
			long long anss;
			if(i>=a && j>=b){
				anss=rec[i][j]-rec[i-a][j]-rec[i][j-b]+rec[i-a][j-b]; //a*b的矩阵 
				if(anss<ans) ans=anss;
			}
			if(i>=b && j>=a){
				anss=rec[i][j]-rec[i-b][j]-rec[i][j-a]+rec[i-b][j-a];//b*a的矩阵 
				if(anss<ans) ans=anss;
			}
		}
	} 
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：TLMPEX (赞：1)

这道题的数据很小，n和m均不超过50，所以暴力4层循环完全可以。

有一点要注意：就是没说a和b那个是长那个是宽，所以要交换一下。

下面上代码。
```c
#include<bits/stdc++.h>
using namespace std;
int a[101][101];
int main(){
	int n,m,x,y,i,j,k,p,s,z=2500;//把z置为最多（50×50）
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>a[i][j];
	cin>>x>>y;
	for(i=1;i<=n-x+1;i++)
		for(j=1;j<=m-y+1;j++){
			s=0;//注意每次要把s清0
			for(k=i;k<i+x;k++)
				for(p=j;p<j+y;p++)
					s+=a[k][p];
			z=min(z,s);//取砍树最小值
		}
	swap(x,y);//交换木屋的长和宽
	for(i=1;i<=n-x+1;i++)
		for(j=1;j<=m-y+1;j++){
			s=0;
			for(k=i;k<i+x;k++)
				for(p=j;p<j+y;p++)
					s+=a[k][p];
			z=min(z,s);
		}
	cout<<z;
}
```


---

## 作者：信守天下 (赞：0)

## [CF传送门](http://codeforces.com/contest/48/problem/B)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF48B)
## 思路
在整个地图中去枚举每一个 $a \times b$ 的矩阵房子不好枚举。

但是我们可以枚举每个矩阵右上角的坐标，就可以确认矩阵位置。

根据左上角的坐标，可以求出矩阵的横纵坐标范围。

然后直接在地图中遍历小矩阵，计算数量。

在所有的矩阵中记录数量最小的方案的数量。

需要注意的是，每个坐标可以有两个矩阵，一个横的一个竖的。

注意判定每个坐标对应的矩阵有没有越界。

## 复杂度分析
### 时间复杂度
读入地图 $O(nm)$ 。

枚举坐标 $O(nm)$ 。

遍历矩阵 $O(ab)$ 。

更新答案 $O(1)$ 。

总共 $O(nmab)$ 。

### 空间复杂度
存储地图 $O(nm)$ 。

## $code$
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 51;
int n, m, a, b, ans = 1e9;  //ans初始值要取一个比较大的数
bool mp[kMaxN][kMaxN];      //地图，由于只有0和1就用了布尔数组
int Chick(int x, int y) {
  int ans1 = 1e9, ans2 = 1e9;  //不同的两种矩阵数量
  if (x + b - 1 <= n && y + a - 1 <= m) {
    ans1 = 0;  //这个矩阵合法，答案清空准备记录
    for (int i = x; i <= x + b - 1; i++) {
      for (int j = y; j <= y + a - 1; j++) {
        ans1 += mp[i][j];
      }
    }
  }
  if (x + a - 1 <= n && y + b - 1 <= m) {
    ans2 = 0;
    for (int i = x; i <= x + a - 1; i++) {
      for (int j = y; j <= y + b - 1; j++) {
        ans2 += mp[i][j];
      }
    }
  }
  return min(ans1, ans2);
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> mp[i][j];  //读入地图
    }
  }
  cin >> a >> b;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans = min(ans, Chick(i, j));  //更新答案
    }
  }
  cout << ans;
  return 0;
}
~~~	

---

## 作者：Sham_Sleep (赞：0)

其实理解题意就不难知道，立马就想到了二维前缀和。


不过他是求最小值的，所以初始化要稍微改动一下。

然后这个题目最坑的地方来辽——他的矩形的长和宽可以交换。


也就是说，我要搜两边，第一遍让横轴充当长，纵轴充当宽。

第二次让横轴充当宽，纵轴充当长。

接下来，就没了。。。

如果有人没学过二维前缀和，就可以先康康本蒟蒻的代码。也可以上网找帖子（~~本蒟蒻因为太蒻就没有写~~）

~~蒟蒻味~~二维前缀和
```
#include <stdio.h>
#include <iostream>
using namespace std;


int r,c;
int m,n;
int t;
int mapp[3005][3005];


int main()
{
	scanf("%d%d" , &r , &c); //读入地图大小
	scanf("%d%d" , &m , &n); //读入要求的矩阵大小
	for(int i = 1; i <= r; ++i){
		for(int j = 1; j <= c; ++j){
			scanf("%d" , &t);
			mapp[i][j] = t - mapp[i - 1] [j - 1] + mapp[i - 1] [j] + mapp[i] [j - 1]; //二维前缀和的递推公式
		}
	}
	int ans = 0;
	for(int i = m; i <= r; ++i){
		for(int j = n; j <= c; ++j){
			ans = max(ans , mapp[i] [j] - mapp[i - m] [j] - mapp[i] [j - n] + mapp[i - m][j -n]);//根据题目改变是求最大值还是最小值 
		}
	}
	printf("%d" , ans);//输出答案
	return 0;
}
//本蒟蒻这个二维前缀和没有讲交换长宽的情况算进去，根据题意更改
```

~~AC~~代码
```
#include <stdio.h>
#include <iostream>
using namespace std;


int r,c;
int m,n;
int t;
int mapp[3005][3005];


int main()
{
	scanf("%d%d" , &r , &c);
	for(int i = 1; i <= r; ++i){
		for(int j = 1; j <= c; ++j){
			scanf("%d" , &t);
			mapp[i][j] = t - mapp[i - 1] [j - 1] + mapp[i - 1] [j] + mapp[i] [j - 1]; 
		}
	}
	scanf("%d%d" , &m , &n);
	int ans = 99999999;
	for(int i = m; i <= r; ++i){
		for(int j = n; j <= c; ++j){
			ans = min(ans , mapp[i] [j] - mapp[i - m] [j] - mapp[i] [j - n] + mapp[i - m][j -n]);
		}
	}
	for(int i = n; i <= r; ++i){
		for(int j = m; j <= c; ++j){
			ans = min(ans , mapp[i][j] - mapp[i - n][j] - mapp[i][j - m] + mapp[i - n][j - m]);
		}
	}
	printf("%d" , ans);
	return 0;
}
```
支持一下本蒟蒻吧QAQ



---

## 作者：hater (赞：0)

上一篇题解很用心

但是可能对前缀和不是了解

蒟蒻来补一篇题解

这道题目可以算是前缀和的板子

但是有一个坑点

a b 没说哪个是长 哪个是宽

所以我把a b swap 之后又跑了一遍

贴代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int Map[55][55],n,m,cnt[55][55],r,c,ans=0x7f7f7f7f;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    cin>>Map[i][j];
	cin>>r>>c;
        for(int i=1;i<=n;i++)
          for(int j=1;j<=m;j++)
            cnt[i][j]=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1]+Map[i][j];
        for(int i=r;i<=n;i++)
          for(int j=c;j<=m;j++)
            ans=min(ans,cnt[i][j]-cnt[i-r][j]-cnt[i][j-c]+cnt[i-r][j-c]);
        swap(r,c);
        for(int i=r;i<=n;i++)
          for(int j=c;j<=m;j++)
            ans=min(ans,cnt[i][j]-cnt[i-r][j]-cnt[i][j-c]+cnt[i-r][j-c]);
        cout<<ans<<endl;
	return 0;
} 
```

luogu缩进有problem    勉强看着吧

---

