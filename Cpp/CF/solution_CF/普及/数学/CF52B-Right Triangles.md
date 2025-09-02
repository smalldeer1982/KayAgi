# Right Triangles

## 题目描述

You are given a $ n×m $ field consisting only of periods ('.') and asterisks ('\*'). Your task is to count all right triangles with two sides parallel to the square sides, whose vertices are in the centers of '\*'-cells. A right triangle is a triangle in which one angle is a right angle (that is, a 90 degree angle).

## 样例 #1

### 输入

```
2 2
**
*.
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4
*..*
.**.
*.**
```

### 输出

```
9
```

# 题解

## 作者：Super_dark (赞：3)

### 题意
任意一个**三个顶点**都在星号上的三角形就是“Right Triangles”。
### 解题思路
在输入时统计每行每列有多少个星号,这里设第 $i$ 行有 $x_i$ 个星号，第 $j$ 列有 $y_j$ 个星号。最后从头搜索星号，因为三角形的边与矩形的边平行，所以一旦搜到星号就能计算出以它为顶点能构造出 $x_i-1$ 乘 $y_j-1$ 个三角形。即它横向有几个点能与它构成直角边和
它纵向有几个点能与它构成直角边之积（减一正是为了减掉自己）。
### 提示
最极端情况下 int 会爆，要用long long！
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans,x[1005],y[1005]; 
char mp[1005][1005];
signed main() {
    cin>>n>>m;
    for (long long i=1;i<=n;i++) 
    	for (long long j=1;j<=m;j++) {
        	cin>>mp[i][j]; 
            if (mp[i][j]=='*') {
            	x[i]++; 
                y[j]++; 
            }
        }
    for (long long i=1;i<=n;i++) 
    	for (long long j=1;j<=m;j++)
        	if (mp[i][j]=='*') 
            	ans+=(x[i]-1)*(y[j]-1);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Siyuan (赞：3)

## 本题思路：
通过分析易得：统计每行、每列各有几个`*`。最后判断每个字符，如果是`*`，那么对答案的贡献为$\ (x[i]-1)*(y[j]-1)$。

### 代码如下：
> **卡常 + 空间压缩**。。。

```
#include<cstdio>
using namespace std;

int n,m;
int x[1001],y[1001];
bool a[1001][1001];

int main()
{
	scanf("%d%d",&n,&m);
	while(getchar()!='\n');
	for(register int i=1;i<=n;getchar(),i++)
		for(register int j=1;j<=m;j++)
		{
			register char t=getchar();
			if(t=='*')  x[i]++,y[j]++,a[i][j]=1;
		}
	register long long ans=0;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
			if(a[i][j])  ans+=(x[i]-1)*(y[j]-1);
	printf("%I64d",ans);
	return 0;
}
```

---

## 作者：codeLJH114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF52B)

## 题目大意

输入一个 $n \times m$ 的矩阵，只包含星号和点号。

一个 $\text{Right Triangle}$ 就是**三个**顶点都在星号上，且直角边分别平行于矩形的场合宽的直角三角形。（不论方向）

## 数据范围

$1 \leq n \leq 1000$

$1 \leq m \leq 1000$

## 解题思路

先统计出来每一行，每一列中星号的个数。

接下来循环每一个坐标，只要矩形的该点为星号，就可以对答案产生影响。

用乘法原理就可以推出具体影响为 $ (x_i - 1) \times (y_j - 1)$ （$x_i$ 为第 $i$ 行星号的个数，$y_j$ 为第 $j$ 列星号的个数，$-1$ 是因为要去掉自己。）

## 坑点

- 直角三角形的三个定点必须都在星号上，我就是被坑了，以为只要是直角的那个顶点在星号上就可以了 $\cdots$

- 一个直角三角形不能只要一个点。

- 答案必须开 `long long`，因为如果 $n$ 和 $m$ 均为 $1000$，且矩阵全为星号时，每行每列都有 $1000$ 个星号，所以每个点对答案有 $(1000 - 1) \times (1000 - 1)$ 的影响，大约是 $10 ^ 6$ 量级，再乘上 $1000$，所以答案最大可以达到 $10 ^ 12$ 量级，`int` 必爆炸。（亲测，不开 `long long` 错 #$17$ 测试点）

## AC 代码

```cpp
#include <iostream>
#define maxn 1024
using namespace std;
int64_t n, m, ans, count_x[maxn], count_y[maxn]; // 不开 long long 见祖宗
char mp[maxn][maxn];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
    	for (int j = 1; j <= m; j++) {
        	cin >> mp[i][j]; 
            if (mp[i][j] == '*') {
            	count_x[i] += 1; 
                count_y[j] += 1; 
            }
        } // 统计每行每列的星号个数。
    for (int i = 1; i <= n; i++) 
    	for (int j = 1; j <= m; j++)
        	if (mp[i][j] == '*') 
            	ans += (count_x[i] - 1) * (count_y[j] - 1);
    // 统计每个点对答案的影响并累加。
    cout << ans;
    return 0;
}
```cpp

---

## 作者：Jiyuu_no_Tsubasa (赞：1)

这是一道比较有思维的题。

对于每一个 "*" 点，我们应该统计：

+ 它横向有几个点能与它构成直角边
+ 它纵向有几个点能与它构成直角边

然后再把这两个数据根据乘法原理相乘就能得到每个点的贡献。

我们可以使用一个数组来存储上面所提到的两个数据，并用 bool 数组记录 "*" 点。

然后这道题就做出来了：

```
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int x[N],y[N];
bool a[N][N];
int main(){
    int n; cin>>n;
    int m; cin>>m;
    char opt;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>opt;
            if(opt=='*')
                x[i]++,y[j]++,a[i][j]=1;
        }
    long long ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j])
                ans+=(x[i]-1)*(y[j]-1);//-1是减去自己
    cout<<ans;
    return 0;
}

```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF52B)

## 思路

循环输入时一边输入一边统计每行每列的星号数。之后再次循环遍历每个星号，利用乘法原理推出具体影响是 $(x_i-1)\times (y_j-1)$。累加后输出。

- 数据可能达到 $10^{12}$ 量级，所以别忘开 long long。

## 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1010;
ll n,m,x[N],y[N],ans;
char c[N][N];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>c[i][j];
            if(c[i][j]=='*'){
                x[i]++;
                y[j]++;
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(c[i][j]=='*')ans+=(x[i]-1)*(y[j]-1);
        }
    }
    cout<<ans<<endl;
    return 0;
}
~~~
[已 AC](https://www.luogu.com.cn/record/96866271)

---

## 作者：_lgh_ (赞：0)

### 思路：
本题首先要知道  $\text{Right Triangle}$ 的定义：三个顶点都是星号，且直角边分别平行于矩形的场合宽的直角三角形。

直接考虑每个点对答案的贡献。贡献就是该行除了本个点的个数 $\times$ 该列除了本个点的个数。

直接开两个 int 数组（分别统计行和列星号的个数）和一个统计是否星号的 bool 数组，输入的时候在该行和该列加一即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x[1010],y[1010];char c;bool a[1010][1010];
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(register int i=1; i<=n; i++)
	  for(register int j=1; j<=m; j++) 
	  	cin>>c,((c=='*')&&(x[i]++,y[j]++,a[i][j]=1));
	register long long num=0;
	for(int i=1; i<=n; i++)
	  for(int j=1; j<=m; j++)
	    if(a[i][j]) num+=(x[i]-1)*(y[j]-1);
	cout<<num<<'\n';
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

**update on 2022.04.26：**

修改了一处炸掉的格式。
### 一、题意

题目给我们一个 $n\times m$ 的字符矩阵，求**三个`*`为顶点且直角边水平或竖直**的三角形。

### 二、思路

首先想到的显然是暴力：

$\text{找到一个点->找到另一个点->判断是否符合条件}$

显然，不明确计算复杂度也知道肯定上天了。

那怎么办呢？

我们仔细观察这样一个图形：

```cpp
......
....*.
....*.
......
....*.
*..***
```

你可以数一下，其中有$3\times3=9$个三角形。

于是，我们会发现：

设 $col_i$ 表示第 $i$ 列 `*` 的个数， $row_i$ 表示第 $i$ 行 `*` 的个数。

则以第 $i$ 行，第 $j$ 列这个 `*` 为**顶点**的三角形有 $\left(col_i-1\right)\times\left(row_i-1\right)$ 个（请您思考为什么要减一）。

此时，标程呼之欲出了。

### 三、代码

由上面的式子直接写就可以了。

减一的原因是 **第 $i$ 行，第 $j$ 列这个字符本身也是\*** 。

```cpp
#include <stdio.h>
#include <string.h>
using namespace std;
int _x;char _c;
int read(){
	_x=0;_c=getchar();
	while(_c<'0'||_c>'9')_c=getchar();
	while(_c<='9'&&_c>='0'){
		_x=(_x<<1)+(_x<<3)+(_c^'0');
		_c=getchar();
	}
	return(_x);
}//加速读入
int n,m;
char c;char s[1005][1005];
int col[1005],row[1005];
int main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	long long ans=0;//注意 long long
	n=read();m=read();
	for(int i=1;i<=n;getchar(),i++)//getchar()似乎比cin.get(),scanf都要快，但是比fread慢
		for(int j=1;j<=m;j++){
			s[i][j]=c=getchar();
			if(c=='*')++row[i],++col[j];
		}//读入矩阵存入s,并算出row,col数组。
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='*')//这个if不能少
				ans+=(row[i]-1)*(col[j]-1);
	printf("%lld\n",ans);//输出
	return(0);
}

```

---

## 作者：songhongyi (赞：0)

题目意思：有一个字符矩阵，由`*`和`.`构成，求有多少个直角三角形满足三个顶点都是`*`且两个直角边都平行于矩阵的边框（即一个横，一个竖）  
这道题和[P6355](https://songhongyi.blog.luogu.org/solution-p6355)有点相像，其实核心思路是完全类似的，就是**枚举直角顶点，然后枚举该行该列的`*`个数，进行统计**  
代码如下
```cpp

// Problem: CF52B Right Triangles
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF52B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
using namespace std;
long long int cntx[ 1010 ], cnty[ 1010 ];
char map[ 1010 ][ 1010 ];
int main()
{
    int n, m;
    cin >> n >> m;
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < m; j++ )
        {
            cin >> map[ i ][ j ];
            if ( map[ i ][ j ] == '*' )
            {
                cntx[ i ]++;
                cnty[ j ]++;
            }
        }
    }
    long long int ans = 0;
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < m; j++ )
        {
            if ( map[ i ][ j ] == '*' )
            {
                ans += ( cntx[ i ] - 1 ) * ( cnty[ j ] - 1 );
            }
        }
    }
    cout << ans << endl;
}
```

---

## 作者：梦游的小雪球 (赞：0)

## 思路：
1. 搜直角端点,设它为c[i][j]。
1. 看这一列有几个可以与它连接的，设它为h[i]。
1. 再看这一排有几个可以与它连接的,设它为l[j]
1. 将每一个点连起来，即可形成h[i]* l[j]个三角形。
### 注意：
- 由于三角形可能会很多，所以用来累加的数要用long long。
## 按照思路来，代码就出来了：
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,s,h[1002],l[1002];//定义。
char c[1002][1002];//n*m的矩阵。
int main(){
	cin>>n>>m;//输入。
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>c[i][j];//输入矩阵。
			if(c[i][j]=='*'){
				h[i]++;
				l[j]++;
			}//统计这一行有几个“*”。
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(c[i][j]=='*')//搜直角端点
				s=s+(h[i]-1)*(l[j]-1);//注意要减去它本身这一个“*”。
		}
	cout<<s;//输出
	return 0;
} 
```
**望通过，谢谢QWQ**

---

## 作者：18lxxrz (赞：0)

### 思路

------------

输入时记录每列每行顶点数，然后两个for循环，一列一列数，其中的减一是指减去自己,模拟即可。


------------
话不多说，上代码

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[6666][6666];
int r[6666],c[6666],n,m;
long long ans;
int main ()
{
    scanf("%d%d",&n,&m);
    for(register int i=0;i<n;++i)
    {
        scanf("%s",s[i]);
        for(register int j=0;j<m;++j)
            if(s[i][j]=='*')
                r[i]++,c[j]++;
    }
    for(register int j=0;j<m;++j)
    {
        long long temp=0;
        for(register int i=0;i<n;++i)
            if(s[i][j]=='*')
                temp+=r[i]-1;
        ans+=temp*(c[j]-1);//减去自己
    }
    printf("%I64d\n",ans);//注意不是%lld

    return 0;
}
```


---

