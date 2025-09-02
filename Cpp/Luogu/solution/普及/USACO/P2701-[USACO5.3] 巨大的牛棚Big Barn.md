# [USACO5.3] 巨大的牛棚Big Barn

## 题目背景

（USACO 5.3.4）


## 题目描述

FJ 有一个大小为 $n\times n$ 的农场（$1\le n\le 1000$），他想要在他的农场上建造一座正方形大牛棚。他的农场中有 $t$ 棵果树（$1\le t\le10000$），但他为了不破坏果树，就想找一个空旷无树的地方修建牛棚。你的任务是计算并输出，在他的农场中，不需要砍树却能够修建的最大正方形牛棚的边长。当然，牛棚的边必须和水平轴和垂直轴平行。

考虑下面的农场，`.` 表示没有树的方格，`#` 表示有树的方格。
```plain
0 1 2 3 4 5 6 7 8
1 . . . . . . . .
2 . # . . . # . .
3 . . . . . . . .
4 . . . . . . . .
5 . . . . . . . .
6 . . # . . . . .
7 . . . . . . . .
8 . . . . . . . .
```
最大的牛棚是边长为 $5$ 的，可以建造在农场右下角的两个位置其中一个。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 5.3


## 样例 #1

### 输入

```
8 3
2 2
2 6
6 3```

### 输出

```
5```

# 题解

## 作者：旗木五五开 (赞：33)

## 首先本蒟蒻膜一遍楼下所有dalao（QWQ）

------------


#### 这题动态规划，状转方程：（~~似乎不是很难~~）  
f[i][j]=min(min(f[i][j-1],f[i-1][j]),f[i-1][j-1])+1;

#### 说明：
f（i, j）表示以（i, j）为右下角的最大正方形的边长。

只有a[i][j]不是树时，（i, j）才能作为正方形的右下角；~~树砍掉不就不用这么麻烦了么。。。~~

对于一个值为x的f[i][j]，它表示包括（i，j）向上和向左的x个点的正方形中所有a（i, j）都是树；对于未确定的f(i, j)，可以由f（i-1, j），f(i, j-1)，f(i-1, j-1)的值得知

------------
#### 举个 （~~栗 子~~） 例子：
假设1表示空地，0表示树:

a数组如下
```cpp
0 1 1 0 1
1 1 1 1 0
0 1 1 1 0
1 1 1 1 0
0 1 1 0 1
```
则f数组为
```cpp
0 1 1 0 1
1 1 2 1 0
0 1 2 2 0
1 1 2 3 0
0 1 2 0 1
```
#### （~~有点乱，别介意~~）

#### 由此推出可怕的动态转移方程： f[i][j]=min(min(f[i][j-1],f[i-1][j]),f[i-1][j-1])+1;


------------

### 下面就可以上~~一只~~AC代码啦：


```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>	//憋问我为啥写这么多头文件
using namespace std;
int n,m;
int a[1005][1005],f[1005][1005];
int main() {
	scanf("%d%d",&n,&m);
	memset(a,1,sizeof(a));
	int x,y;
	for(int i=1; i<=m; i++) {
		scanf("%d%d",&x,&y);
		a[x][y]=0;
	}			//输入
			
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(a[i][j])		//如果有树就返回（话说建在树上有啥不好。。。 ）
				f[i][j]=min(min(f[i][j-1],f[i-1][j]),f[i-1][j-1])+1;	//动态转移方程
	int ans=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			ans=max(ans,f[i][j]);	//ans记录最大值
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Jayun (赞：29)

## 思路：

这道题很水，但很适合dp初学者做！（~~瞎扯一下~~）

先写动态转移方程，待会解释

### $f_{i,j}=min\{f_{i-1,j},f_{i,j-1},f_{i-1,j-1}\}+1$

### $(a_{i,j}!=\#)$

#### 解释：

$f_{i,j}$表示以矩阵$i\times j$为右下的正方形边长

用**jio**指头想想就能知道，$f_{i,j}$是由左、上、左上方向来的

用$min$的原因是，如果用$max$,三个方向的正方形可能会碰到树,以及其它情况（蒟蒻表达不出来，看栗子~）.

拿样例解释：
```pascal
 . . . . . . . .

 . # . . . # . .

 . . . . . . . .

 . . . . . . . .

 . . . . . . . .

 . . # . . . . .

 . . . . . . . .

 . . . . . . . .
```
用$max$:

```pascal
 1 1 1 1 1 1 1 1

 2 0 2 3 4 0 2 3

 3 4 5 6 7 8 9 10

 4 5 6 7 8 9 10 11

 5 6 7 8 9 10 11 12

 6 7 0 9 10 11 12 13

 8 9 10 11 12 13 14 15

 9 10 11 12 13 14 15 16
```
实际：

```pascal
 1 1 1 1 1 1 1 1

 1 0 1 2 2 0 1 2

 1 1 1 2 3 1 1 2

```
 （前几行，我累了。。。）
 
 对比一下，用$max$根本不可能
 
 ## 代码
 
 ### 创建美好洛谷，切勿Ctrl+C
 
 c++党这里↓
 
 ```cpp
 #inculde<bits/stdc++.h>

using namespace std;

int n,t;
int f[1010][1010];
int ans;

int main() {
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=1;      //边界条件哦
    while(t--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        f[x][y]=0;           //树的位置打零
    }
    for(int i=1;i<=n;i++)     
    {
        for(int j=1;j<=n;j++) //i和j千万不要从2开始哦
        {
            if(f[i][j]==0)continue;
            f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;          //转移方程哦
            ans=max(ans,f[i][j]);  //更新目标
        }
    }
    printf("%d",ans);      //输出yeah
    return 0;              //。。。yeah
}


 ```
 
---

p党在这里哦~
```pascal
var
    f:array[0..1010,0..1010]of longint;//注意是从0开始
    x,y,i,j,n,t,ans:longint;
function min(a,b:longint):longint;
begin
    if a>b then exit(b)
    else exit(a); 
end;
function mx(a,b:longint):longint;
begin
    if a<b then exit(b)
    else exit(a); 
end;
begin
    readln(n,t);
    for i:=1 to n do
        for j:=1 to n do
            f[i,j]:=1;  //边界条件
    for i:=1 to t do
    begin
        readln(x,y);
        f[x,y]:=0;   //树的位置打零
    end;
    for i:=1 to n do
        for j:=1 to n do
        begin
            if f[i,j]=0 then continue;
            f[i,j]:=min(min(f[i-1,j],f[i,j-1]),f[i-1,j-1])+1;   //转移方程
            ans:=max(ans,f[i,j]);  //更新目标
        end;
    writeln(ans);  //yeah~
end.
```
希望你喜欢（暗示点赞

---

## 作者：顾z (赞：15)

**广告** [安利blog](https://www.luogu.org/blog/RPdreamer/#)

**题目大意**

给定一个01棋盘,求其中全为1的最大正方形边长。
//暂且这么理解,有树的位置我们视为0.

**分析:**

发现题解没有用悬线法的 所以介绍一下
~~说实话我快写吐了~~

以下内容部分参考[@Clove_unique](https://blog.csdn.net/Clove_unique/article/details/50512624)

**悬线法**

    用途:
       解决给定矩阵中满足条件的最大子矩阵
    做法:
       用一条线(横竖貌似都行)左右移动直到不满足约束条件或者到达边界
    定义几个东西:
        left[i][j]:代表从(i,j)能到达的最左位置
        right[i][j]:代表从(i,j)能到达的最右位置
        up[i][j]:代表从(i,j)向上扩展最长长度.
    这里给出递推公式：
        left[i][j]=max(left[i][j],left[i-1][j]
        right[i][j]=min(right[i][j],right[i-1][j]

至于为什么递推公式中考虑上一层的情况？

是因为up数组的定义,up数组代表向上扩展最长长度, 所以需要考虑上一层的情况.而我们要考虑上一层的情况的话,需要考虑左右边界问题,因此递推公式中分别取max与min即可。

然后我们去利用dp方程去求解即可.

------------------代码--------------------

```cpp
#include<bits/stdc++.h>
#define IL inline
#define RI register int
#define N 1008
IL void read(int &x){
	int f=1;x=0;char s=getchar();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
	while(s<='9'&&s>='0'){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int res[N][N],n,m,ans;
int left[N][N],right[N][N],up[N][N];
int main()
{
	read(n),read(m);
	for(RI i=1;i<=n;i++)
		for(RI j=1;j<=n;j++)
		{
			left[i][j]=right[i][j]=j;
			up[i][j]=1;
		}//千万不要忘记初始化！！
	for(RI i=1,x,y;i<=m;i++)
	{
		read(x),read(y);
		res[x][y]=1;
	}
	for(RI i=1;i<=n;i++)
		for(RI j=2;j<=n;j++)
			if(res[i][j]==0&&res[i][j-1]==0)
				left[i][j]=left[i][j-1];//预处理左边界
	for(RI i=1;i<=n;i++)
		for(RI j=n-1;j>0;j--)
			if(res[i][j]==0&&res[i][j+1]==0)
				right[i][j]=right[i][j+1];//预处理右边界
	for(RI i=1;i<=n;i++)
		for(RI j=1;j<=n;j++)
		{
			if(i>1&&res[i][j]==0&&res[i-1][j]==0)
			{
				left[i][j]=std::max(left[i][j],left[i-1][j]);
				right[i][j]=std::min(right[i][j],right[i-1][j]);
				up[i][j]=up[i-1][j]+1;
			}
			int a=right[i][j]-left[i][j]+1;
			int b=std::min(a,up[i][j]);
			ans=std::max(ans,b);
		}
	printf("%d",ans);
	
}
```

悬线法题目:[P1169 棋盘制作](https://www.luogu.org/problemnew/show/P1169)   [p4147 玉蟾宫](https://www.luogu.org/problemnew/show/P4147)   [p2701 巨大的牛棚](https://www.luogu.org/problemnew/show/P2701)   [p1387 最大正方形](https://www.luogu.org/problemnew/show/P1387)

---

## 作者：LGwyy (赞：7)



~~本蒟蒻做到这题一下就想到了二分（不慌），
已提交居然对了，一看题解里没有这种高（la）级（ji）二分，毅然决然地就写题解~~

（上面纯属废话）

下面进入正题，本题的思路就是一个二维前缀数组，然后二分正方形的边长。

当然二维前缀数组中判断用中间有没有树（只要自己画画图就能理解了，在此就不再详讲）：
  
         a[i+xx-1] [j+xx-1]-a[i+xx-1][j-1]-a[i-1][j+xx-1]+a[i-1][j-1]=0
         
##### 下面才是重点——代码：


------------

```pascal
var
  x,y,n,m,i,j,t,w,res,mid:longint;
  a:array[0..1001,0..1001]of longint;
function check(xx:longint):boolean;//判断
var
  i,j:longint;
begin
   
  for i:=1 to n-xx+1 do
    for j:=1 to n-xx+1 do
      if (a[i+xx-1,j+xx-1]-a[i+xx-1,j-1]-a[i-1,j+xx-1]+a[i-1,j-1]=0) then//就是上面的那个
      begin
        exit(true);
      end;
  exit(false);
end;
begin
  readln(n,m);
  for i:=1 to m do
    begin
      readln(x,y);
      a[x,y]:=1;
    end;

  for i:=1 to n do
    for j:=1 to n do
      begin
        a[i,j]:=a[i-1,j]+a[i,j];
      end;
  for i:=1 to n do
    for j:=1 to n do
      a[i,j]:=a[i,j]+a[i,j-1];//二维前缀
 t:=1;w:=n;res:=0;
 while t<=w do
   begin
     mid:=(t+w) shr 1 ;
     if check(mid) then begin res:=mid;t:=mid+1;end
       else w:=mid-1;
   end;//二分边长长度
 writeln(res);//输出
end.
```
------------
###### 给P党点福利啊！！！~~虽然本人要转C++了~~
 _最后支持洛谷，多写题解_    (*^▽^*)


---

## 作者：Drifterming (赞：5)

/\*一开始没认真读题，做成长方形，其实是正方形。读了题之后感觉和以前做的一道P1387 最大正方形很像，因为觉得该题是长方形，所以没在意，但是。。。。题目中说是正方形，那就和 P1387 最大正方形 一样了。。

转移方程：dp[i][j]=min(dp[i-1][j-1],min(dp[i][j-1],dp[i-1][j])

为什么是min不是max，画图可以知道，如果取max，那么可能会有树出现。

\*/




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,t,x,y,ans;
int map[1005][1005],dp[1005][1005];
inline int read(int &num)
{
    num=0;char c=getchar();
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar()){num=num*10+c-'0';}
}
int main()
{
    read(n),read(t);
    for(int i=1;i<=t;i++)
    {
        read(x),read(y);
        map[x][y]=1;    //标记当前位置为数 
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(!map[i][j])        //当前位置不是树 
            {
                dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
                ans=max(ans,dp[i][j]);        //取最大的边长 
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：huiwang17 (赞：2)

# 前缀和 + 二分
## 一开始没看到数据范围T了我好亏啊


```cpp

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define ll long long
const int MAXN = 1017;
const int INF = 10000000;
int a[MAXN][MAXN];
int sum[MAXN][MAXN];

int search(int l, int r, int x, int y){ //二分！
    int ans = 0;
    while(l <= r){
        int k = (l + r) >> 1;
        if(sum[x][y] - sum[x-k][y] - sum[x][y-k] + sum[x-k][y-k] == k * k)
            ans = k, l = k + 1;
        else r = k - 1;
    }
    return ans;
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            a[i][j] = 1;
    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        a[x][y] = 0;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            sum[i][j] = sum[i-1][j] + sum[i][j-1] + a[i][j] - sum[i-1][j-1];
    int ans = 0;
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++){
            int k = search(ans, n, x, y);
            ans = max(ans, k);
        }
    cout << ans << endl;
}

```


---

## 作者：wlzhouzhuan (赞：2)

个人认为这道题还是用悬线法比较好。

$Solution:$

先定义三个数组：

$up[i][j]$ 表示$(i,j)$在垂直方向最长延伸的长度

$l[i][j]$ 表示$(i,j)$能延伸到的最左的点为$(i,l[i][j])$

$r[i][j]$ 表示$(i,j)$能延伸到的最右的点为$(i,r[i][j])$

知道了这三个数组的含义后，我们开始考虑转移。

对于每一个$(i,j)$，它都可以由$(i-1,j)$转移而来，当且仅当：
$i>1$，且$a[i][j],a[i-1][j]$都没有树，

所以得到状态转移方程：

$up[i][j]=up[i-1][j]+1,l[i][j]=max(l[i][j],l[i-1][j],r[i][j]=min(r[i][j],r[i-1][j])$

每次的答案$tmp$即为$min(r[i][j]-l[i][j]+1,up[i][j])$（$r[i][j]-l[i][j]+1$表示横向最长，$up[i][j]$表示纵向最长，两者取小）

最终的答案$ans=max(tmp)$，注意一下$up[i][j],l[i][j],r[i][j]$的初始条件

这道题差不多就做完了。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define req(i, l, r) for (int i = l; i >= r; i--)

const int N = 1005;
int l[N][N], r[N][N], up[N][N];
int a[N][N], n, m, ans;

void read(int &x) {
    x = 0; int f = 1;
    char op = getchar();
    while (!isdigit(op)) {
        if (op == '-') f = -1;
        op = getchar();
    }
    while (isdigit(op)) {
        x = 10 * x + op - '0';
        op = getchar();
    }
    x *= f;
}

void pre() {
	rep(i, 1, n) rep(j, 2, n) {
		if (a[i][j] && a[i][j - 1])
			l[i][j] = l[i][j - 1];
	}
	rep(i, 1, n) req(j, n - 1, 1) {
		if (a[i][j] && a[i][j + 1])
			r[i][j] = r[i][j + 1];
	}
}

void work() {
	rep(i, 1, n) rep(j, 1, n) {
		if (i > 1 && a[i][j] && a[i - 1][j]) {
			up[i][j] = up[i - 1][j] + 1;
			l[i][j] = max(l[i][j], l[i - 1][j]);
			r[i][j] = min(r[i][j], r[i - 1][j]);
		}
		int a = r[i][j] - l[i][j] + 1;
		int b = min(a, up[i][j]);
		ans = max(ans, b);
	}
}

int main() {
	read(n), read(m);
	rep(i, 1, n) rep(j, 1, n) {
		a[i][j] = up[i][j] = 1;
		l[i][j] = r[i][j] = j;
	}
	while (m--) {
		int x, y; read(x), read(y);
		a[x][y] = 0;
	}
	pre(); work();
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：EarthGiao (赞：2)

## 【思路】
然后就可以用来DP了   
跑得飞快就是不太好想    
如果是第一次做这种题的话   
可能很吃力    

### 【DP思路】
f(i,j)表示以(i,j)为右下角的最大子矩阵的大小   
然后这个点的最大子矩阵的大小   
等于左边上边和左上边   
以这三个点为右下角的最大子矩阵的大小里面最小的那个+1    
但是要注意一下     
如果这个点是一棵树   
那就不能作为右下角的    
（真不明白为什么不能以一棵树作为右下角    
MC党的我，最喜欢把家建在树上和地下了QWQ）     
$$f[i][j] = min(min(f[i - 1][j - 1],f[i - 1][j]),f[i][j - 1]) + 1$$    
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
const int Max = 1010;
int f[Max][Max];
int a[Max][Max];
signed main()
{
	int n,m;
	cin >> n >> m;
	for(register int i = 0;i <= n;++ i)
		for(register int j = 0;j <= n;++ j)
			a[i][j] = 1;
	int x,y;
	int M = 0;
	for(register int i = 1;i <= m;++ i)
		cin >> x >> y,a[x][y] = 0;
	for(register int i = 1;i <= n;++ i)
		for(register int j = 1;j <= n;++ j)
			if(a[i][j] != 0)
			f[i][j] = min(min(f[i - 1][j - 1],f[i - 1][j]),f[i][j - 1]) + 1,M = max(M,f[i][j]);
	cout << M << endl;
	return 0;
}
```

---

## 作者：dl__hh6 (赞：2)

这个题目本蒟蒻来说还是挺难想到的，但是
想到P1387 最大正方形时发现他两很像；就
突然~~灵感大发~~！！

但是，这个题目有一点比较难想到，就是动
态转移方程**不能用max，要用min**,因为max的
话就会遇到大树，
动态转移一方程：

**f[i,j]:=min(f[i-1,j-1],min(f[i-
1,j],f[j-1,i]));**

```pascal


uses math; //math库有很多好东东；；

var

 i,j,n,z,ans,x,y:longint;

 a,f:array[0..1000,0..10000]of  longint;

begin

  readln(n,z);

    for i:=1 to n do begin

     for j:=1 to n do

     a[i,j]:=1;

end;//先创造出一个以n为边的矩形

    for i:=1 to z do begin

     readln(x,y);

     a[x,y]:=0;//将大树的位置附成0，便于后面判断

end;

     for i:=1 to n do begin

      for j:=1 to n do begin

     if a[i,j]=1  then begin  //当这个点
不是大树时；

     f[i,j]:=min(f[i-1,j-1],min(f[i-1,j],f[i,j-1]))+1; //动态转移方程

a  ns:=max(ans,f[i,j]); //和当前的最长
边比较；；

end;

end;

end;

writeln(ans);//输出，完工

end.

```
清楚AC代码：
```pascal
uses math;
var
  i,j,n,z,ans,x,y:longint;  
  a,f:array[0..1000,0..10000]of longint;
begin
  readln(n,z);
   for i:=1 to n do begin
    for j:=1 to n do
   a[i,j]:=1;
 end;
  for i:=1 to z do begin
   readln(x,y)
   a[x,y]:=0;
end;
  for i:=1 to n do begin
   for j:=1 to n do begin
    if a[i,j]=1  then begin
    f[i,j]:=min(f[i-1,j-1],min(f[i-1,j],f[i,j-1]))+1;
    ans:=max(ans,f[i,j]);
  end; 
  end;
  end;
writeln(ans);
end.

```
~~做题愉快！！！~~

~~注：如还不懂请私信我！~~


---

## 作者：Mr_Wolfram (赞：1)

###悬线法

本题也可以使用悬线法求最大子矩阵，首先 O(n^2) 预处理，对于矩阵上的每一个点，我们可以：


1.从它向上引一条悬线，遇到边界或障碍点停止，h[i][j] 数组记录从点 (i,j) 向上的悬线长度。


2.向左延伸，遇到边界或障碍点停止，l[i][j] 数组记录从点 (i,j) 向左最大能延伸的长度。


3.向右延伸，遇到边界或障碍点停止，r[i][j] 数组记录从点 (i,j) 向右最大能延伸的长度。

但是这样是不够的， 因为，L[i][j] 和 L[i][j] 的值都各自取决于 L[i-1][j] 和 R[i-1][j]。（因为为保证成为一个矩形，L[i][j] 不能超过 L[i-1][j]，R同理）


所以枚举点对 l 和 r 进行更新，对 L[i-1][j] 与 l[i][j] 取 max，r 同理。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
const int MAXN=1005;
int init(){
    int rv=0,fh=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') fh=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        rv=(rv<<1)+(rv<<3)+c-'0';
        c=getchar();
    }
    return fh*rv;
}
int n,t,l[MAXN][MAXN],r[MAXN][MAXN],L[MAXN][MAXN],R[MAXN][MAXN],H[MAXN][MAXN],ans;
bool ff[MAXN][MAXN];
int main(){
    freopen("in.txt","r",stdin);
    n=init();t=init();
    for(int i=1;i<=t;i++){
        int x=init(),y=init();
        ff[x][y]=1;
    }
    for(int i=1;i<=n;i++){
        l[i][1]=0;
        for(int j=2;j<=n;j++){
            if(ff[i][j]){
                l[i][j]=j;
            }else l[i][j]=l[i][j-1];
        }
        r[i][n]=n+1;
        for(int j=n-1;j>=1;j--){
            if(ff[i][j]){
                r[i][j]=j;
            }else r[i][j]=r[i][j+1];
        }
    }
    for(int j=1;j<=n;j++){
        H[1][j]=1;L[1][j]=l[1][j];R[1][j]=r[1][j];
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ff[i-1][j]){
                H[i][j]=1;
                L[i][j]=l[i][j],R[i][j]=r[i][j];
            }else{
                H[i][j]=H[i-1][j]+1;
                L[i][j]=max(L[i-1][j],l[i][j]);
                R[i][j]=min(R[i-1][j],r[i][j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int len=min(H[i][j],R[i][j]-L[i][j]-1);
            //if(len==6) printf("%d %d\n",i,j);
            ans=max(ans,len);
        }
    }
    cout<<ans;
    fclose(stdin);
    return 0;
}
```

---

## 作者：reek (赞：1)

本人比较弱，所以写了O（n^2 log n）的做法。

大概思路是从上往下枚举正方形最下面的一行，更新每一格上面有多少格空的格，用ST表预处理区间最小值。

然后用两种做法。一种是二分答案，判断时枚举左下顶点，O（1）查询是否能够构成当前大小的正方形。

另一种是用两个指针。在当前矩形的长>=宽时右指针往右挪，否则左指针往右挪，同时更新ans。

但因为预处理ST表需要O（n log n），所以总时间复杂度为O（n^2 log n）

二分法版代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m,x,y,l,r,mid,kl,ans;
int b[1001][13];
bool a[1001][1001];
int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&x,&y);
        a[x][y]=1;
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++)
        if (a[i][j]) b[j][0]=0; else b[j][0]++;
        for (int k=1;(1<<k)<=n;k++)
        for (int j=1;j+(1<<k)-1<=n;j++)
        b[j][k]=min(b[j][k-1],b[j+(1<<(k-1))][k-1]);
        l=0; r=n+1;
        while (l+1<r) {
            mid=(l+r)>>1;
            kl=log2(mid);
            for (int j=1;j+mid-1<=n;j++)
            if (min(b[j][kl],b[j+mid-(1<<kl)][kl])>=mid) {
                l=mid; break;
            }
            if (l<mid) r=mid; else ans=max(ans,l);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
双指针法版代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m,x,y,l,r,mid,kl,ans,xiao;
int b[1001][13];
bool a[1001][1001];
int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&x,&y);
        a[x][y]=1;
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++)
        if (a[i][j]) b[j][0]=0; else b[j][0]++;
        for (int k=1;(1<<k)<=n;k++)
        for (int j=1;j+(1<<k)-1<=n;j++)
        b[j][k]=min(b[j][k-1],b[j+(1<<(k-1))][k-1]);
        l=0; r=1; xiao=b[1][0];
        while (r<=n) {
            while (l+1<r&&r-l>xiao) {
                l++; kl=log2(r-l);
                xiao=min(b[l+1][kl],b[r-(1<<kl)+1][kl]);
            }
            ans=max(ans,r-l);
            r++;
            xiao=min(xiao,b[r][0]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：yz0414 (赞：0)

这题做法就是先预处理a数组为1，读入的a[x,y]=0,再跑一遍dp如果a[i,j]=1就做，求出f[i,j]中最大的，输出。

动态转移方程：f[i,j]:=min(f[i-1,j-1],min(f[i-1,j],f[i,j-1]))+1;

代码：

```pascal
var i,j,n,z,ans,x,y:longint;
    a,f:array[0..1000,0..10000]of longint;
function max(x,y:longint):longint;
begin if x>y then exit(x);exit(y); end;
function min(x,y:longint):longint;
begin if x<y then exit(x);exit(y); end;
begin
   readln(n,z);
   for i:=1 to n do
     for j:=1 to n do
       a[i,j]:=1;
   for i:=1 to z do
     begin
        readln(x,y);
        a[x,y]:=0;
     end;
   for i:=1 to n do
     for j:=1 to n do
       if a[i,j]=1  then
        begin
           f[i,j]:=min(f[i-1,j-1],min(f[i-1,j],f[i,j-1]))+1;
           ans:=max(ans,f[i,j]);
        end;
   writeln(ans);
end.
```


---

## 作者：梅心 (赞：0)

# 这道题...
### 是一道美国信息竞赛题
### 说实话是一道很简单的dp题
```

```
# 重点：
### dp有三步：
#### 1.定义边界或者叫初始化 
#### 2.定义状态
#### 3 状态转移方程
### 最后一步是最复杂的
```

```
## 本题状态转移方程：
```
dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;

##### 完整代码：
```
```
#include<bits/stdc++.h>//万能脑袋 
using namespace std;
int dp[1005][1005], n, t, x[10005], y[10005], maxi; 
int main()
{
	cin >> n >> t;//输入 
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			dp[i][j] = 1;//初始化 
		}
	}
	for(int i = 1; i <= t; i++)
	{
		cin >> x[i] >> y[i];//输入 
		dp[x[i]][y[i]] = 0;//将有数的格子置为0,表示有数的格子
	}
	for(int i = 2; i <= n; i++)//上面有大佬说从1开始，但我从2开始也过了 
	{
		for(int j = 2; j <= n; j++)
		{
			if(dp[i][j] == 1)//如果这里没有树 
			{
				dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;//边长加1 
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
		 	maxi = max(maxi, dp[i][j]);//求最大边长 
		}
	}
	cout << maxi;//输出 
	return 0;//完美结束 
}
```
##### 感谢apple365

---

## 作者：hater (赞：0)

前缀和

这道题实际上是本蒟蒻的学校模拟赛的题F   ~~出题老师请用点心~~

然后写了个暴力   ~~之前做过的最大正方形都做过的呢（尴尬）~~

实际上暴力是需要加一个小优化

不然是会超时的

## 算法以及优化

两重循环枚举牛棚的左上坐标

一重循环枚举长度

两重循环判断有没有树

O（n^5) ~~（1 <= N <= 1000）~~ 显然会超时QAQ

那么来优化吧

稍微有一点经验的OIER也知道

最后两重循环实际上可以用前缀和

sum [  i  ]   [  j  ] 表示（1，1）~（i，j）有多少棵树

求 (x1,y1)~(x2,y2) 有多少棵树 (x2>x1, y2>y1)

易得 用容斥原理 

sum[  x2   ] [ y2 ] - sum[ x1-1 ] [ y1 ]-sum[ x1 ][ y1-1 ] +sum [ x1-1 ] [ y1-1 ]

那么代码就出来啦 

就是枚举长度不要出界

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,ans,a[1005][1005],sum[1005][1005];
int main() {
    int x,y;
    cin>>n>>T;
    for(int i=1;i<=T;i++) 
    {
         cin>>x>>y;
         a[x][y]=1; 
    }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
       sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
       {
           int l;
           for(l=1;i+l-1<=n&&j+l-1<=n;l++)
           if(sum[i+l-1][j+l-1]-sum[i-1][j+l-1]-sum[i+l-1][j-1]+sum[i-1][j-1]!=0) break;
           ans=max(ans,l-1);//因为当lbreak时是放不下的，所以要-1
       }
    cout<<ans<<endl;
    return 0;
} 
```
~~想AC没那么容易————says  O（n^3) （1 <= N <= 1000）~~

嗯 这个是会超时的

实践证明

但是我们只需要再改几个字就够了

l可以从ans开始循环 （1~ans） 可以不用枚举

有点像最优解剪枝

跑出来最慢的只有27ms dp肯定更快

但是对于暴力来说已经足够了

实际上可以更快

枚举长度还可以用二分

读入数据大用快读

但是蒟蒻没心情弄了（题E还没打好就来打题解）

各种更快优化等你来拿


---

## 作者：da32s1da (赞：0)

与[P1387 最大正方形](https://www.luogu.org/problemnew/show/P1387)相似，修改细节即可。

$f[i][j]$表示以$(i,j)$为右下角能围成的最大正方形，转移显然

令$b[i][j]$表示$(i,j)$向左的第一个$0$，$c[i][j]$表示$(i,j)$向上的第一个$0$，那么

$f[i][j]=\min\{f[i-1][j-1]+1,j-b[i][j],i-c[i][j]\}$

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1005;
int n,m,x,y,ans;
int a[N][N],b[N][N],c[N][N],f[N][N],pre;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    scanf("%d%d",&x,&y),a[x][y]=-1;
    for(int i=1;i<=n;i++){
        pre=0;
        for(int j=1;j<=n;j++)
        if(~a[i][j])b[i][j]=pre;//向左的第一个0
        else pre=j;
    }
    for(int j=1;j<=n;j++){
        pre=0;
        for(int i=1;i<=n;i++)
        if(~a[i][j])c[i][j]=pre;//向上的第一个0
        else pre=i;
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(~a[i][j]){
        f[i][j]=min({f[i-1][j-1]+1,j-b[i][j],i-c[i][j]});//转移
        ans=max(ans,f[i][j]);//取最大值
    }
    printf("%d\n",ans);
}
```

---

## 作者：Chicago_01 (赞：0)

## 题面

农夫约翰想要在他的正方形农场上建造一座正方形大牛棚。

他讨厌在他的农场中砍树，想找一个能够让他在空旷无树的地方修建牛棚的地方。

我们假定，他的农场划分成 N x N 的方格。输入数据中包括有树的方格的列表。你的任务是计算并输出，在他的农场中，不需要砍树却能够修建的最大正方形牛棚。

牛棚的边必须和水平轴或者垂直轴平行。

## 题意

给你一个图，要求找出图中符合规则的最大正方形。

题意同：[ P1387 最大正方形](https://www.luogu.org/problemnew/show/P1387)

## 题解

这是一道非常经典的矩阵（二维）动态规划，还有一道相似的题目：[ P1508 Likecloud-吃、吃、吃](https://www.luogu.org/problemnew/show/P1508)
(学会一道题，然后三倍经验😀)

遇到矩阵（二维）动态规划的题目，常规的思路就是手动构造->找状态转移方程。

非常规的思路就是："这题我做个类似的，这个状态转移方程我知道!"

---

* 首先画一个图，这是一个原始的图。

| 0 | 1 | 1 | 0 | 1 |
| - | - | - | - | - |
| 1 | 1 | 1 | 1 | 0 |
| 0 | 1 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 |
| 0 | 1 | 1 | 0 | 1 |

* 然后构造出每一个点的最大正方形边长。

| 0 | 1 | 1 | 0 | 1 |
| - | - | - | - | - |
| 1 | 1 | 2 | 1 | 0 |
| 0 | 1 | 2 | 2 | 0 |
| 1 | 1 | 2 | 3 | 0 |
| 0 | 1 | 2 | 0 | 1 |

* 由下图和上图可推出状态转移方程 ： $ dp[i][j] = min(dp[i][j-1],dp[i-1][j],dp[i-1][j-1])+1 $

* 最后只需要找出整个图中最大的点就行了。

## 代码
动态规划的题目的代码都非常的简单。
```
#include<bits/stdc++.h>
using namespace std;

int n,m,mapp[1010][1010];
int dp[1010][1010];

int main(int argc, char const *argv[])
{
    cin >> n >> m;
    memset(mapp,1,sizeof(mapp));
    for(int i = 1;i <= m;++i)
    {
        int x,y;
        cin >> x >> y;
        mapp[x][y] = 0;
    }

    int maxx = -1;

    for(int i = 1;i <= n;++i)
    {
        for(int j = 1;j <= n;++j)
        {
            if(mapp[i][j])
            {
                dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
            }
            maxx = max(maxx,dp[i][j]);
        }
    }

    cout << maxx;

    return 0;
}

```

---

## 作者：Celebrate (赞：0)

这题不用看都知道是DP，时间O(n^2)，DP肯定是找关于这一个点周围的三个点

凭借感觉退出公式：f[i][j]=max(f[i-1][j-1]+1,max(f[i][j-1],f[i-1][j]))

但是这种做法完全忽略了破坏正方形的因素

所以，只能用min来做，因为如果旁边有树肯定会使这个点为1

正确的公式：f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1;

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool a[1100][1100];
int f[1100][1100];//记录 
int t,maxx;
inline int in()//方便很多的输入 
{
	scanf("%d",&t);
	return t;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	memset(a,true,sizeof(a));
	for(i=1;i<=m;i++) a[in()][in()]=false;
	for(i=1;i<=n;i++)//枚举一次 
	{
		for(j=1;j<=n;j++)
		{
			if(a[i][j]==true)//如果没有 
			{
				f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1;//记录下来 
				maxx=max(maxx,f[i][j]);//求最大值，最大值不一定是最后一个 
			}
		}
	}
	printf("%d\n",maxx);//输出 
	return 0;
}
```

注：f[i][j]表示已点(i,j)为结束点的最大值

---

## 作者：Dr_殇 (赞：0)

#这题就是最大子矩阵的思路。


#穷举每一个点，例如map[i][j]（map这里我是用来存树的），如果这个点不是树，那么这个点的正方形的边长就是它左上，左边，上面的最小值+1，所以可得动态转移方程：s[i][j]=min(min(s[i][j-1],s[i-1][j]),s[i-1][j-1])+1。


##注：这里min里的三个变量可以随意交换，没有任何顺序。


##代码如下：





```cpp
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
int n,m,ans,s[1005][1005],map[1005][1005];//定义动规数组和状态数组
int main(){
    scanf ("%d %d",&n,&m);
    for (int i=1;i<=m;i++){
        int a,b;
        scanf ("%d %d",&a,&b);
        map[a][b]=1;
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (!map[i][j]){
                s[i][j]=min(min(s[i][j-1],s[i-1][j]),s[i-1][j-1])+1;//动态转移方程
                ans=max(ans,s[i][j]);//求最大值
            }
        }
    }
    printf ("%d\n",ans);//最后输出
    while (1);//反抄袭
    return 0;
}
```
完成！

#这题我一开始用最大子矩阵做，做了好久就是不对，突然发现，这不就是类似简单的模拟上，左和左上最小值+1吗，才作对，希望大家不要有我一开始这个错误的想法。


#珍爱生命，拒绝抄袭！


---

## 作者：doby (赞：0)

dp很好写，暴力更简单……

状态转移方程：f[i][j]=min(f[i-1][j],f[i][j-1],f[i-1][j-1])+1

```cpp
#include<iostream>
using namespace std;
int a[1005][1005]={{0}},f[1005][1005]={{0}},n,t,x,y,maxb=1;
int minn(int a,int b)
{
    if(a<b){return a;}
    else{return b;}
}
int minnn(int a,int b,int c)
{
    return minn(minn(a,b),c);
}
int main()
{
    cin>>n>>t;
    for(int i=1;i<=t;i++){cin>>x>>y;a[x][y]=1;}
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[i][j]){continue;}//如果上面有东西就跳过
            f[i][j]=minnn(f[i-1][j],f[i][j-1],f[i-1][j-1])+1;//状态转移
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(f[i][j]>maxb){maxb=f[i][j];}//找最大的
        }
    }
    cout<<maxb;
}
```

---

## 作者：Radium_ (赞：0)

我就给个思路，两种解法：

1. DP，用f[i,j]表示以当前格子为右→下角能构成的最大的正方形大小，方程f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;楼上题解已有，此处不再赘述；

2. 二维数组前缀和，可能会超时，可以参见 洛谷P2733 ,跟这道题的区别就是没有区别 ，核心代码如下，如有不理解可参见博客：


    

```cpp
    for(int i=1;i<=N;i++){//二维数组前缀和
        for(int j=1;j<=N;j++) sum[i][j]=sum[i][j-1]+int(a[i][j]-'0');
        for(int j=1;j<=N;j++) sum[i][j]+=sum[i-1][j];
    }
    for(int k=2;k<=N;k++)//对边长进行枚举
        for(int i=1;i+k-1<=N;i++)
            for(int j=1;j+k-1<=N;j++)
                if(cal(i,j,i+k-1,j+k-1)==k*k)
                    ans=k;
```
以下是两道运用前缀和的题目
[洛谷 P1736 创意吃鱼法](http://www.cnblogs.com/radiumlrb/p/5808527.html)

[洛谷 P1387 最大正方形 ](http://www.cnblogs.com/radiumlrb/p/5808285.html)


---

## 作者：eternal (赞：0)

状态 o F[i][j] 表示以(i,j)为左上角最大正方形的边长


初始条件 o 如果(i,N)没有障碍 F[i][N]=1 否则 F[i][N]=0 o 如果(N,i)没有障碍 F[N][i]=1 否则 F[N][i]=0


状态转移方程 o F[i][j]=min(F[i+1][j],F[i][j+1],F[i+1][j+1])+1;








```cpp
#include <bits/stdc++.h>
#define MAXN 1001
using namespace std;
int M[MAXN][MAXN],N,ans;
void init()
{
    int T,x,y,i;
    cin >> N >> T;
    for (i=1;i<=T;i++)
    {
        cin >> x >> y;
        M[x][y]=-1;
    }
}
inline int min(int a,int b,int c)
{
    if (a<=b && a<=c) return a;
    if (b<=a && b<=c) return b;
    return c;
}
void dynamic()
{
    int i,j;
    for (i=1;i<=N;i++)
    {
        if (M[N][i]==0)    M[N][i]=1;
        else            M[N][i]=0;
        if (M[i][N]==0)    M[i][N]=1;
        else            M[i][N]=0;
    }
    for (i=N-1;i>=1;i--)
        for (j=N-1;j>=1;j--)
            if (M[i][j]==-1)
                M[i][j]=0;
            else
            {
                M[i][j]=min(M[i+1][j],M[i][j+1],M[i+1][j+1])+1;
                if (M[i][j]>ans)
                    ans=M[i][j];
            }
}
void print()
{
    cout << ans << endl;
}
int main()
{
    int i,j;
    init();
    dynamic();
    print();
    return 0;
}
```

---

