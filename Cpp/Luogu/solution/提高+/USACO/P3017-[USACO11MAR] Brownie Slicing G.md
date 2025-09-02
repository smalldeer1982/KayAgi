# [USACO11MAR] Brownie Slicing G

## 题目描述

Bessie 烤了一个长方形的布朗尼，可以看作是一个 $R \times C$ 的网格（$1 \le R \le 500$；$1 \le C \le 500$），由小方块组成。在第 $i$ 行，第 $j$ 列的方块中有 $N_{ij}$（$0 \le N_{ij} \le 4,000$）颗巧克力豆。

Bessie 想把布朗尼分成 $A \times B$ 块（$1 \le A \le R$；$1 \le B \le C$）：每头牛一块。布朗尼的切割方式是先进行 $A-1$ 次水平切割（总是在整数坐标上），将布朗尼分成 $A$ 条带。然后每条带独立地进行 $B-1$ 次垂直切割，也是在整数边界上。其他 $A \times B - 1$ 头牛各自选择一块布朗尼，剩下最后一块给 Bessie。由于它们很贪心，它们会把巧克力豆最少的一块留给 Bessie。

假设 Bessie 以最优方式切割布朗尼，求 Bessie 能获得的最多巧克力豆数。

例如，考虑一个 5 行 4 列的布朗尼，巧克力豆分布如下：
```
1 2 2 1
3 1 1 1
2 0 1 3
1 1 1 1
1 1 1 1
```

Bessie 必须将布朗尼分成 4 条水平带，每条带有两块。Bessie 可以这样切割布朗尼：

```
1 2 | 2 1
---------
3 | 1 1 1
---------
2 0 1 | 3
---------
1 1 | 1 1
1 1 | 1 1
```

因此，当其他贪心的牛选择它们的布朗尼块时，Bessie 仍然可以得到 3 颗巧克力豆。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 4 4 2 
1 2 2 1 
3 1 1 1 
2 0 1 3 
1 1 1 1 
1 1 1 1 
```

### 输出

```
3 
```

# 题解

## 作者：xMinh (赞：36)

# 这道二分还真是不同于流俗啊

因为看错题，白白想了一个多小时。。。

好像没有c++的题解？

只要看懂题目的话其实还好

先二分最大化最小值

对于每一行，就像最基本的二分那样做，纵向切割

如果这一行不满足条件，就加上下一行继续判断

用now来保存上一个切点，用矩阵前缀和优化就行了

如果最后横向切割的次数大于等于a，就代表可以

PS:最后一行（列）也是要切一刀的

因为如果最后不能切的话就说明最后一段不满足条件

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int r,c,a,b,map[501][501],s[501][501],ans;
bool check(int x)
{
    int now=0,num=0;
    for (int i=1;i<=r;i++)
    {
        int dis=0,sum=0;
        for (int j=1;j<=c;j++)
            if (dis+(s[i][j]-s[i][j-1])-(s[now][j]-s[now][j-1])<x)
                dis+=(s[i][j]-s[i][j-1])-(s[now][j]-s[now][j-1]);
            else
            {
                sum++;
                dis=0;
            }
        if (sum>=b)
        {
            now=i;num++;
        }
    }
    if (num<a) return 0;
    return 1; 
}
int main()
{
    cin>>r>>c>>a>>b;
    for (int i=1;i<=r;i++)
        for (int j=1;j<=c;j++)
            cin>>map[i][j];
    for (int i=1;i<=r;i++)
        for (int j=1;j<=c;j++)
            s[i][j]=s[i-1][j]+s[i][j-1]+map[i][j]-s[i-1][j-1];
    int h=0,t=s[r][c];
    while (h<=t)
    {
        int mid=(h+t)/2;
        if (check(mid))
        {
            h=mid+1;
            ans=mid;
        }
        else t=mid-1;
    }
    cout<<ans;
}
```

---

## 作者：DennyQi (赞：16)

题目描述非常坑啊。并没有说竖的切必须是一条直线啊，只不过每条分成B块而已……害我苦想30min……

知道了题意就很简单了。题目要求最大化最小值，因此可以二分答案。然后贪心的让每一块尽量满足且超出的尽量小即可。具体一点，对于某一条，如果已经能够在满足$mid$的情况下分为$B$块，就不再考虑。如果不能满足，则应当把下一行合并上来让它满足，再不行就再合并一行……最后判断横向能否切A条即可。如果不能就意味着答案太大了……

还是非常水的，我那么菜竟然一遍就过了。另外在代码实现上，不必统计矩阵之和，只需要每一列维护一下前缀和就好了。

```cpp
/*By DennyQi 2018*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 510;
const int INF = 1061109567;
inline int Max(const int a, const int b){ return (a > b) ? a : b; }
inline int Min(const int a, const int b){ return (a < b) ? a : b; }
inline int read(){
    int x = 0; int w = 1; register char c = getchar();
    for(; c ^ '-' && (c < '0' || c > '9'); c = getchar());
    if(c == '-') w = -1, c = getchar();
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x<<3) + (x<<1) + c - '0'; return x * w;
}
int R,C,A,B,l(INF),r,mid,ans;
int a[MAXN][MAXN],s[MAXN][MAXN];
inline bool judge(int x){
	int lst = 0,cnt,sum,tot=0;
	for(int i = 1; i <= R; ++i){
		cnt = 0;
		sum = 0;
		for(int j = 1; j <= C; ++j){
			sum += s[i][j] - s[lst][j];
			if(sum >= x){
				++cnt;
				sum = 0;
			}
		}
		if(cnt >= B){
			lst = i;
			++tot;
		}
	}
	return tot >= A;
}
int main(){
//	freopen(".in", "r", stdin);
	R = read(), C = read(), A = read(), B = read();
	for(int i = 1; i <= R; ++i){
		for(int j = 1; j <= C; ++j){
			a[i][j] = read();
			s[i][j] = s[i-1][j] + a[i][j];
			r += a[i][j];
			l = Min(l, a[i][j]);
		}
	}
	while(l<=r){
		mid=(l+r)>>1;
		if(judge(mid)) ans=mid, l=mid+1;
		else r=mid-1;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Yummy_ (赞：9)


 二分答案，然后用贪心思想来检查这个答案。注意题目中输入的a和b是分成几块而不是切几刀的意思。详解见代码。
 
------------
FROM:
https://www.cnblogs.com/Patrick-X/p/6183169.html

------------华丽的分割线-----------------------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[501][501];
int r,c,a,b;
bool check(int num) { //二分产生的答案 
	int i=1,j=1,tot2=0;//i，j表示当前横着切的蛋糕上下界，tot2表示横着分成了几块
	while (j<=r) { //然后贪心求出这块横着的蛋糕在满足num的要求的情况下，最多分成几块
		int s=1,sum=0,tot=0;//指针s，指向当前这刀切哪的位置，tot表示竖着切了几刀
		while (s<=c) {
			for (int k=i; k<=j; k++)
				sum+=x[k][s];
			if (sum>=num) { //满足num，竖着切下一块
				sum=0;
				tot++;
			}
			s++;//指针后移
		}
		if (tot>=b) {
			i=j+1;    //满足竖着切b刀的条件，横着切一刀，下块蛋糕的边界调整
			tot2++;
		}
		j++;//无论满不满足，蛋糕的边界下移
	}
	if (tot2>=a) return true;//满足横着切a刀的条件，返回true
	else return false;
}

int main() {
	int left=-1,right=0;
	cin>>r>>c>>a>>b;
	for (int i=1; i<=r; i++){
		for (int j=1; j<=c; j++) {
			cin>>x[i][j];
			right+=x[i][j]; //求出前缀和 
		}
	} 
	int mid,st=0,ans=0;
	while (left<=right) { //注意二分的边界问题
		mid=(left+right)/2;
		if (check(mid)) {
			ans=mid;    //记录做到的最优方案
			left=mid+1;
		} else right=mid-1;
	}
	cout<<ans<<endl;
	return 0;//功德圆满
}
```


---

## 作者：deleted (赞：7)

题意：有一个$r\times c$的矩阵，每一个点有一个点权$N_{i,j}$，要求将这个矩阵先水平切成$a$块子矩阵，再将每一个子矩阵竖直切成$b$块小子矩阵，不同子矩阵切割方式相互独立。要求：所有点的点权之和最小的一块小子矩阵的点权之和，并最大化这个总和。

最大化最小点权之和，显然考虑二分答案。考虑二分一个值$x$，如何判断$x$是否能作为答案，也就是判断$x$是否能作为所有点的点权之和最小的一块小子矩阵的点权之和。等价于其他的所有小子矩阵的点权总和都要大于等于$x$。

如何判断？记$x$为当前待检验的答案，$tiao$为当前切的条数（水平方向），$kuai$为当前切的块数（竖直方向），$now$为水平方向的上一次切割位置，$last$为竖直方向的上一次切割位置。枚举水平方向上的切割点$i$和竖直方向上的切割点$j$，如果在$(i-now)$～$(j-last)$之间的点权之和大于等于$x$，那么符合要求，可以在这里切割，并更新各项信息。当$kuai\geq b$时就可以在$i$处切一条，$tiao++$。最后只需判断$tiao\geq a$是否成立即等价于$x$是否能成为答案。

可以用二维前缀和预处理出每个二维矩阵的点权之和。

$code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define il inline
#define dou double
#define un unsigned
il int read()
{
	char c=getchar();int x=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
#define INF 114514114
#define clr(x) memset(x,0,sizeof(x))
#define N 500+10
int r,c,a,b,le,ri,mid;
int x[N][N],sum[N][N];
il bool check(int x)
{
	int tiao=0,now=0;
	for(re int i=1;i<=r;i++)
	{
		int kuai=0,last=0;
		for(re int j=1;j<=c;j++)
		{
			if(sum[i][j]-sum[i][last]-sum[now][j]+sum[now][last]>=x)
			{
				kuai++;
				last=j;
			}
		}
		if(kuai>=b)
		{
			now=i;
			tiao++;
		}
	}
	return tiao>=a?true:false;
}
int main()
{
	r=read();c=read();a=read();b=read();
	for(re int i=1;i<=r;i++)
	{
		for(re int j=1;j<=c;j++)
			x[i][j]=read();
	}
	for(re int i=1;i<=r;i++)
	{
		for(re int j=1;j<=c;j++)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+x[i][j];
	}
	le=1;ri=sum[r][c];
	while(le+1<ri)
	{
		mid=(le+ri)>>1;
		if(check(mid))le=mid;
		else ri=mid;
	}
	cout<<le<<endl;
	return 0;
}
```

---

## 作者：Fr0sTy (赞：4)

### 题意简述
------------

给定一个 $r \times c$ 矩阵，先水平切成 $a$ 块，然后每块竖着切成 $b$ 块，让每块的的值 $a_{ij}$ 的最大值最小。

但这里有个坑点注意一下：**并不是**每一刀都是**水平**或**垂直**的。

### 解题思路
------------

比较容易可以想到**二分答案**。

所谓**二分答案**，就是用二分的方法，在可能的答案区间里找出问题的方法。

当然，纯粹的二分答案肯定会 TLE，因为对每块的枚举时间复杂度就有平方级别。

所以这里可以采用二维数组前缀和来优化，每次判断时间复杂度可以到 $Θ(1)$。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int pre[1005][1005],maps[1005][1005];
int lef,rig,n,m,a,b,ans;
int pre_sol(int i,int j) {
	int tmp=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+maps[i][j];
	return tmp;
}
int pre_spl(int i,int j,int mem_i,int mem_j) {
	int tmp=pre[i][j]-pre[i][mem_j]-pre[mem_i][j]+pre[mem_i][mem_j];
	return tmp;
}
bool check(int t) {
	int sum=0,num=0,mem_i=0,mem_j=0;
	for(int i=1;i<=n;i++) {
		mem_j=0; num=0;
		for(int j=1;j<=m;j++) {
			if(pre_spl(i,j,mem_i,mem_j)>=t) {
				num++; mem_j=j;
			}
		}
		if(num>=b) {
			sum++; mem_i=i;
		}
	}
	if(sum>=a) return true;
	else return false;
}
int main() {
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&maps[i][j]);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) pre[i][j]=pre_sol(i,j);
	rig=pre[n][m]/(a*b);
	while(lef<=rig) {
		int mid=(lef+rig)/2;
		if(check(mid)) {ans=mid; lef=mid+1;}
		else rig=mid-1;
	}
	printf("%d",ans);
	return 0;
}
//code by TheCedar
```


---

## 作者：Erotate (赞：4)

[P3017 Brownie Slicing G](https://www.luogu.com.cn/problem/P3017)
---

首先，看看“由于贪心，他们只会留给 Bessie 巧克力碎屑**最少**的那块。求出 Bessie **最优情况**下会获得多少巧克力碎屑”这句话，是不是相当于求最小值最大。所以，这题可以使用二分答案。

------------
**初始化：**

可以看到，这是一个二维的网格，而我们要把它分成若干块，所以我们可以先用一个二维的前缀和记录住每一块的巧克力数量，以便查询。

然后，因为要切成 $A\times B$ 块，所以，对于 Bessie 来说，最多可以得到 $\dfrac{s[n][m]}{A\times B}$ 的巧克力碎屑,那就是 $r$ 的范围。显然 $l$ 初始化为 0。

接下来模板二分即可。

**check 函数：**

因为只用切 $A-1$ 刀变成 $A$ 条，而 $A$ 有可能小于 $n$，所以我们需要引用变量 $now$ 来记录上一刀切在哪一条上。同理，$B$ 有可能小于 $m$，所以我们需要引用变量 $lst$ 来记录上一刀切在哪一块上。

如何计算出当前切的这一块的巧克力碎屑总数呢？因为我们有 $s$ 数组记录二维前缀和，那我们只需要用下面这条公式即可：$s[i][j]-s[i][lst]-s[now][j]+s[now][lst]$。

接下来如果当前块的碎屑数大于等于二分的答案，切好的块数加一。循环结束后，再判断是否切够 $B$ 块，即一条，如果切够了，切好的条数加一。最后返回是否切够 $A$ 条即可。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,l,r,ans,s[505][505];
bool check(int x){
	int tmp=0,now=0;//tmp表示切了几条
	for(int i=1;i<=n;++i){//枚举条
		int k=0;//k表示切了几块
		for(int j=1,lst=0;j<=m;++j)//枚举块
			if(s[i][j]-s[i][lst]-s[now][j]+s[now][lst]>=x){//是否能切成一块
				k++;
				lst=j;
			}
		if(k>=b){//是否能切成一条
			tmp++;
			now=i;
		}
	}
	return tmp>=a;
}
int main(){
	cin>>n>>m>>a>>b;
	for(int i=1;i<=n;++i)
		for(int j=1,x;j<=m;++j){
			cin>>x;
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+x;//计算前缀和
		}
	r=s[n][m]/(a*b);//二分答案
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：bifanwen (赞：4)

changelog：把时间复杂度部分前面加了空格，后面的符号改成了中文符号。

[博客园同步](https://www.cnblogs.com/bifanwen/p/15077435.html)

[CSDN同步](https://blog.csdn.net/bifanwen/article/details/119222282)

[原题链接](https://www.luogu.com.cn/problem/P3017)

这题做法还算比较明显，$500$ 的数据范围也暗示了做法。

考虑直接二分所求答案，在 $\mathcal{O}(n^2)$ 的时间内进行验证。如何验证 $x$ 的合法性？

可以逐行操作。比如先考虑把第一行分成 $\geq x$ 的 $b$ 块。如果不可以，那么就加上第二行再分，一直叠加直到可以分出这样的 $b$ 块为止，假设叠加到了第 $p$ 行，那么 $[1,p]$ 就作为横向切的第一刀（即切在 $p$ 行处），然后再对 $p+1$ 行进行同样的操作。最后判断能否切到 $a$ 刀即可。这个过程做 $n$ 次。

如何验证能否把若干行分成 $\geq x$ 的 $b$ 块？要求线性做法，你有可能会想到再次二分？那 $2$ 个 $\text{log}$ 当然也可以。但不如考虑直接 $1 - n$ 枚举列的切法，维护二维前缀和，扫到当前和 $\geq x$ 那么就清空和，扫到最后一列看有没有 $b$ 块。这个过程也要做 $n$ 次。

其实说白了，就是先操作列切，合法了再操作行切，行列枚举法。加上二分，复杂度没炸，这题就轻松过了。

时间复杂度： $\mathcal{O}(n^2 \log \sum a_{i,j})$。

注意：二分不知道怎么写 `l<r` 和 `r=mid` 的写法炸了，只能换了一种。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e2+1;

inline int read(){char ch=getchar(); int f=1; while(ch<'0' || ch>'9') {if(ch=='-') f=-f; ch=getchar();}
	int x=0; while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar(); return x*f;}

inline void write(int x) {
	if(x<0) {putchar('-');write(-x);return;}
	if(x<10) {putchar(char(x%10+'0'));return;}
	write(x/10);putchar(char(x%10+'0'));
}

int r,c,a,b,s[N][N];

inline int Sum(int a,int b,int c,int d) {return s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1];}

inline bool check(int x) {
	int ans=0,st=1;
	for(int i=1;i<=r;i++) {
		int p=0,q=1;
		for(int j=1;j<=c;j++)
			if(Sum(st,q,i,j)>=x) p++,q=j+1;
		if(p>=b) st=i+1,ans++;	
	} return ans>=a;
}

int main() {
	r=read(),c=read(),a=read(),b=read();
	for(int i=1;i<=r;i++)
	for(int j=1;j<=c;j++)
		s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+read();
	int l=1,r=4000*500*500;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	} printf("%d\n",l-1);
	return 0;
}


```

---

## 作者：Engulf (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P3017)

[更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-p3017)

## 题意

给定一个 $r \times c$ 矩阵，先水平切 $a$ 块，然后**每块**竖着切 $b$ 块，让每块的权值**最大值最小**。

## 分析

看到**最大值最小**这类题目，可以二分求解。

我们枚举可能的最小值 $x$，那么只要有一块矩阵的权值 $\ge x$，且能切成 $a\times b$ 块就可行。

我们标记上一次切块的行 $last_{row}$ 和列 $last_{col}$，然后枚举分割点 $j$，如果该块权值和 $\ge x$，列切的块数增加 $1$ 并更新 $last_{col}\leftarrow j+1$。

同样，如果切完块数 $\ge b$，行切的块数增加 $1$ 并更新 $last_{row}\leftarrow i+1$。

最后判断一下水平能否切成 $a$ 块即可。

在求矩阵权值和时，可以用二维前缀和优化。

## 代码实现


```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f^=!(ch^45),ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
inline void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(int x){write(x);puts("");}

int r,c,a,b;
int n[505][505];

inline int sum(int a,int b,int c,int d){
	return n[c][d]-n[a-1][d]-n[c][b-1]+n[a-1][b-1];
}

bool check(int x){
	int row=0,last_row=1;
	for(int i=1;i<=r;i++){
		int col=0;
		int last_col=1;
		for(int j=1;j<=c;j++){
			if(sum(last_row,last_col,i,j)>=x){
				col++;last_col=j+1;
			}
		}
		if(col>=b){
			row++;last_row=i+1;
		}
	}
	return row>=a;
}

int main(){
	r=read();c=read();a=read();b=read();
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			n[i][j]=n[i-1][j]+n[i][j-1]+read()-n[i-1][j-1];
		}
	}
	int l=0,r=1e9,ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	writeln(ans);
	#ifndef ONLINE_JUDGE
	system("pause");
	#endif
	return 0;
}
```

---

## 作者：Register (赞：3)

### 题目描述
给你一个$n$行$m$列的矩阵，每个点有一个权值

首先水平切成$a$条

接着每一条切成$b$块

问：如何切，使得最小的一块的权值最大，只需要输出这个权值
### 解题思路
看到“让最小最大”或“让最大最小”很容易联想到二分

我们先考虑一下如何二分：

很简单，不断切块

- 记录目前一共切了几条，这一条里又切了几块

- 记录上一条切到了哪里，这一条刚刚切的一块又切在哪

能够切块的条件：

> 这一块的和达到了目标值

能够切条的条件：

> 这一行能够切足$b$块

目标值成功的条件：

> 能够切足$a$条

**算法$1:$**

判断是否切块达到目标值的时候暴力枚举

- 显然超时

**算法$2:$**

使用二维前缀和判断切块，每次判断时间复杂度为$\Theta(1)$

- 可以通过本道题

### 代码

```cpp
#include <cstdio>
int n,m,a,b,l,r,ans,sum[501][501];
int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
bool check(int x){
	int t=0,now=0;
	for(register int i=1,k;i<=n;i++)
	{
		k=0;
		for(register int j=1,last=0;j<=m;j++)
			if(sum[i][j]-sum[i][last]-sum[now][j]+sum[now][last]>=x) {k++;last=j;}
		if(k>=b) {t++;now=i;}
	}
	return t>=a;
}
int main(){
	n=read();m=read();a=read();b=read();
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++) sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+read();
    r=sum[n][m]/(a*b);
    while(l<=r)
    {
    	int mid=(l+r)>>1;
    	if(check(mid)) {ans=mid;l=mid+1;}
    	else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

## 题目简述

- 有一块 $r\times c$ 的蛋糕，$i$ 行 $j$ 列上有 $a_{ij}$ 的巧克力碎屑。
- 将其先沿水平方向切 $a-1$ 刀，得到的 $a$ 部分**每部分都**沿竖直方向切 $b-1$ 刀。
- 在 $a\times b$ 块切好的蛋糕中，巧克力碎屑的一块最少的一块最多有多少块巧克力碎屑？

## 解题思路

本题采用二分。

设 $x$ 为等待检验的答案，$last$ 为上一次横向切的位置，$line$ 表示一共横向切了多少块。

显然，当 $line>a$ 时，$x$ 是可行的，反之亦然。

后使用两次贪心，每次发现可行的行就直接切，并更新 $last,line$。

对于如何判断是否可以直接切，只需看是否能把 $last+1$ 到 $i$ 行的蛋糕分成 $b$ 块，每块的巧克力碎屑均不小于 $x$，这显然也是一次贪心。

## 参考代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=505;
int t[MAXN][MAXN];
int s[MAXN][MAXN];
int r,c,a,b;
int p,q,mid;
bool check(int x){
	int last=0,line=0;
	for(int i=1;i<=r;i++){
		int sum=0,ups=0;
		for(int j=1;j<=c;j++)
			if(s[i][j]-s[last][j]-s[i][ups]+s[last][ups]>=x)
				sum++,ups=j;
		if(sum>=b)
			line++,last=i;
	}
	return line>=a;
}
int main(){
	cin>>r>>c>>a>>b;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++){
			cin>>t[i][j];
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+t[i][j];
		}
	p=0,q=1e9;
	while(q>p){
		mid=(p+q+1)/2;
		if(check(mid)) p=mid;
		else q=mid-1;
	}
	cout<<p;
	return 0;
}
```


---

## 作者：luckydrawbox (赞：2)

## 题意

有一块可以被看作一个 $R \times C$ 大小的方格的蛋糕，第 $i$ 行第 $j$ 列的方格上有 $N_{i,j}$ 块巧克力碎屑。

首先要水平方向切 $A-1$ 刀，把蛋糕分成 $A$ 条；接着，对于每一条，竖直切 $B-1$ 刀，分成 $B$ 块（注意，每一条蛋糕分割成 $B$ 小块的方式**不必相同**，每一刀都只能切沿**整数坐标**切）。

求问，巧克力碎屑最少的那块蛋糕最多有多少块巧克力碎屑。

## 分析

设答案为 $ans$，显然如果 $ans'<ans$，因为 $ans$ 最大，所以 $ans'$ 可以满足要求；如果 $ans'>ans$，就无法切出来。也就是说答案满足**单调性**，所以我们可以**二分**。

### 来一个不一样的二分

这里给出一个与其他题解不一样的二分。

提前做一下处理：因为计算中需要多次用到许多块的巧克力碎屑数，所以我们用**二维前缀和**存储每一块的和。

##### 处理

```cpp
for(int i=1;i<=r;i++)
	for(int j=1;j<=c;j++)
	{
		cin>>s[i][j];
		s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	}
```

##### 查询

```cpp
#define S(a,b,c,d) s[c][d]+s[a-1][b-1]-s[c][b-1]-s[a-1][d]
```

先二分巧克力碎屑最少的那块蛋糕有 $x$ 块巧克力碎屑，边界最少为 $0$，最多为 $\text{S}(1,1,R,C)$。

```cpp
int L=0,R=S(1,1,r,c);
while(L<R)
{
	int mid=(L+R+1)>>1;
	if(check(mid))//check(mid)代表当巧克力碎屑最少的那块蛋糕有mid块巧克力碎屑时是否可以切成
		L=mid;
	else
		R=mid-1;
}
cout<<L;
```

接下来我们写 $\text{check}(x)$ 函数。

先确定每一条的第一行 $r1$ 和最后一行 $r2$，循环 $A$ 次，每次令 $r2=r1$，令 $r2$ 不断增加，直到 $\text{S}(r1,1,r2,C)≥B\times x$，也就是这一条的和有可能分成每份不小于 $x$ 的 $B$ 份。

接着再令 $r2$ 不断增加，用 $\text{check2}(x,r1,r2)$ 函数表示当巧克力碎屑最少的那块蛋糕有 $x$ 块巧克力碎屑时，要把第一行为 $r1$，最后一行为 $r2$ 的一条分成符合要求的 $B$ 块是否可行，直到 $\text{check2}(x,r1,r2)=1$ 时，$r2$ 停止自增。这时我们找出了这一条满足要求时最小需要的行数。

在整个过程中，若 $r2>R$，也就是无法满足要求，则返回假，否则最后返回真。

```cpp
bool check(int x)
{
	int r1,r2=0;
	for(int i=1;i<=a;i++)
	{
		r1=r2+1;//第一行会等于上一条最后一行+1
		r2=r1;
		if(r2>r)
			return 0;
		while(S(r1,1,r2,c)<x*b)
		{
			r2++;
			if(r2>r)
				return 0;
		}
		while(!check2(x,r1,r2))
		{
			r2++;
			if(r2>r)
				return 0;
		}
	}
	return 1;
}
```


最后我们来写 $\text{check2}(x,r1,r2)$ 函数。

先确定这一条的第一列 $c1$ 和最后一列 $c2$，循环 $B$ 次，每次令 $c2=c1$，令 $c2$ 不断增加，直到 $\text{S}(r1,c1,r2,c2)≥x$，这时就算切了一刀，这一块已符合要求。

在整个过程中，若 $c2>R$，也就是无法满足要求，则返回假，否则最后返回真。

```cpp
bool check2(int x,int r1,int r2)
{
	int c1,c2=0;
	for(int i=1;i<=b;i++)
	{
		c1=c2+1;//第一列会等于上一块最后一列+1
		c2=c1;
		if(c1>c)
			return 0;
		while(S(r1,c1,r2,c2)<x)
		{
			c2++;
			if(c2>c)
				return 0;
		}
	}
	return 1;
}
```

总体复杂度最坏情况下为 $Θ(RC\log \text{S}(1,1,R,C))$。

## 代码

```cpp
#include<bits/stdc++.h>
#define S(a,b,c,d) s[c][d]+s[a-1][b-1]-s[c][b-1]-s[a-1][d]
using namespace std;
const int N=5010;
int r,c,a,b,s[N][N];
bool check2(int x,int r1,int r2)
{
	int c1,c2=0;
	for(int i=1;i<=b;i++)
	{
		c1=c2+1;
		c2=c1;
		if(c1>c)
			return 0;
		while(S(r1,c1,r2,c2)<x)
		{
			c2++;
			if(c2>c)
				return 0;
		}
	}
	return 1;
}
bool check(int x)
{
	int r1,r2=0;
	for(int i=1;i<=a;i++)
	{
		r1=r2+1;
		r2=r1;
		if(r2>r)
			return 0;
		while(S(r1,1,r2,c)<x*b)
		{
			r2++;
			if(r2>r)
				return 0;
		}
		while(!check2(x,r1,r2))
		{
			r2++;
			if(r2>r)
				return 0;
		}
	}
	return 1;
}
int main()
{
    cin>>r>>c>>a>>b;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			cin>>s[i][j];
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	int L=0,R=S(1,1,r,c);
	while(L<R)
	{
		int mid=(L+R+1)>>1;
		if(check(mid))
			L=mid;
		else
			R=mid-1;
	}
	cout<<L;
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

题目分析：

题目就是要求分割后最小的一块矩形上的值最大，想到二分答案。

然后问题转换成是否能使得每一块在保留 $num$ 块巧克力碎屑的情况下切出 $a\times b$ 块蛋糕。

具体的，对于每一行需要切出 $b$ 块，那么记录下上一次切在哪一个点，然后向右枚举，一旦超过所需要的 $num$ 块巧乐力碎屑就立即切下，可以证明这是最优的，最终如果能切出多于 $b$ 块那就是可行的。

然后对于列，需要切出 $a$ 列蛋糕，类似的，记录下上一次切的位置，然后向下枚举，一旦可以切，即保证这样切可以使得横行能切出 $b$ 块，就立即切。

------------
这道题的贪心和其他贪心不一样的地方就是一个贪心的嵌套，也就是在一个贪心里用另一个贪心判断可行性，不过对于这道题，嵌套的两个贪心思路一样，所以也不算太难想。

------------
代码：
```cpp
#include<cstdio>
using namespace std;
int sum[505][505],aaa[505][505],n,m,a,b,l,r;
bool check(int num){
	int x=0,tot2=0;
	for(int i=1;i<=n;i++){
		int y=0,tot=0;
		for(int j=1;j<=m;j++)
		if(sum[i][j]-sum[x][j]-sum[i][y]+sum[x][y]>=num)
		tot++,y=j;
		if(tot>=b)x=i,tot2++;
	}
	if(tot2>=a)return 1;
	return 0;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		scanf("%d",&aaa[i][j]);
		sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+aaa[i][j];
	}
	l=1;r=sum[n][m];
	while(l+1<r){
		int mid=l+r>>1;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%d",l);
	return 0;
}
```

---

## 作者：CGDGAD (赞：1)

## 题解 P3017 [USACO11MAR] Brownie Slicing G

----

### Part 1 题目大意

有一块可以被看作一个 $R \times C$ 大小的方格的蛋糕，第 $i$ 行第 $j$ 列的方格上有 $N_{i,j}$ 块巧克力碎屑。首先要水平方向切 $A-1$ 刀，把蛋糕分成 $A$ 条；接着，对于每一条，竖直切 $B - 1$ 刀，分成 $B$ 块（注意，每一条蛋糕分割成 $B$ 小块的方式不必相同）。求问，巧克力碎屑最少的那块蛋糕最多有多少块巧克力碎屑。

----

### Part 2 题目分析

这道题求的是**最少的最多**，而二分答案通常可以解决此类问题，由此想到二分答案的做法。

二分答案的一个重要特点：

>  问题可以被看作求使某个命题 $P(x)$ 成立（或不成立）的最大（或最小）的 $x$。

这道题显然满足这个特点，但是这个 $P(x)$ 是什么呢？可以转化一下，即，**如果每一小块上的巧克力碎屑都至少为 $x$，是否能够将这块大蛋糕分成 $A$ 行 $B$ 列**。

接下来，我们来看一下是否满足**单调性**，当然对于此题显然是满足的。

----

最后一个问题，就是如何高效判断对于一个 $x$，$P(x)$ 是否成立。

由于「将每一条分成 $B$ 小块」这一部分的分割比较随意，于是很容易想到一种朴素做法：

对于每一行，检查是否能被切成每块巧克力碎屑数都至少为 $x$ 的 $B$ 小块，如果不行，则加入下一行，继续检查，直到可行为止，算作切好了一条。当所有行都被检查完，如果还不够切成 $A$ 条，则这个 $x$ 不可行。

这个做法有一个缺陷：当连续很多行都无法切成一条的时候，每新加入一行检查就需要重新算一遍之前几行，效率很低，于是自然地想到了二维前缀和优化。二维前缀和可以把时间复杂度降到 $O(R \times C)$ 以内。

----

### Part 3 代码实现

```cpp
#include <cstdio>
#define max(a, b) ( (a) > (b) ? (a) : (b) )
#define min(a, b) ( (a) < (b) ? (a) : (b) )
int r, c, a, b;
int pre[501][501];
inline int read() {
	int t = 0; bool neg = 0; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') neg = 1; ch = getchar(); }
	do { t = t * 10 + ch - '0'; ch = getchar(); } while (ch >= '0' && ch <= '9');
	if (neg) t = -t;
	return t;
}
int getSum(int x1, int y1, int x2, int y2) {
	return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
}
bool check(int x) {
	int currA = 0, startR = 1;
	for (int i = 1; i <= r; ++i) {
		int currB = 0, startC = 1;
		for (int j = 1; j <= c; ++j) {
			if (getSum(startR, startC, i, j) >= x) {
				++currB;
				startC = j + 1;
			}
		}
		if (currB >= b) {
			startR = i + 1;
			++currA;
		}
	}
	return currA >= a;
}
int main() {
	r = read(), c = read(), a = read(), b = read();
	int lower = 1e8, upper = 0;
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j) {
			int n = read();
			pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + n;
			upper += n;
			lower = min(lower, n);
		}
	int ans = 0;
	while (lower <= upper) { // 注意二分答案写法，这里我是按照《深基》上的写法写的。
		int mid = (lower + upper) >> 1;
		if (check(mid))
			ans = mid, lower = mid + 1;
		else
			upper = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
```





---

## 作者：傅思维666 (赞：1)


## 题解：

看到最小值最大，果断二分。重点是如何判断当前二分的合不合法。

抓住二分的本质：二分的是答案，答案是什么？最小值最大。如何判断合不合法？就看能不能割出这个值，能割出来，说明不够大。割不出来，说明太大了，需要减小。

最后就维护一个矩阵前缀和来优化枚举即可。

代码：

```cpp
#include<cstdio>
using namespace std;
int n,m,a,b,map[510][510],s[510][510],ans;
bool check(int x)
{
    int now=0,num=0;
    for(int i=1;i<=n;i++)
    {
        int dis=0,sum=0;
        for(int j=1;j<=m;j++)
            if(dis+(s[i][j]-s[i][j-1])-(s[now][j]-s[now][j-1])<x)
                dis+=(s[i][j]-s[i][j-1])-(s[now][j]-s[now][j-1]);
            else
            {
                sum++;
                dis=0;
            }
        if(sum>=b)
            now=i,num++;
    }
    if(num<a) 
		return 0;
    return 1; 
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&a,&b);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&map[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            s[i][j]=s[i-1][j]+s[i][j-1]+map[i][j]-s[i-1][j-1];
    int l=0,r=s[n][m];
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
        {
            l=mid+1;
            ans=mid;
        }
        else 
			r=mid-1;
    }
    printf("%d",ans);
	return 0;
}
```



---

