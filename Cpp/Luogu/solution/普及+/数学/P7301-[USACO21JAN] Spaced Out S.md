# [USACO21JAN] Spaced Out S

## 题目描述

Farmer John 想要拍摄一张他的奶牛吃草的照片挂在墙上。草地可以用一个 $N$ 行 $N$ 列正方形方格所组成的方阵表示（想象一个 $N \times N$ 的棋盘），其中 $2 \leq N \leq 1000$。在 Farmer John 最近拍摄的照片中，他的奶牛们太过集中于草地上的某个区域。这一次，他想要确保他的奶牛们分散在整个草地上。于是他坚持如下的规则：

 - 没有两头奶牛可以位于同一个方格。
 - 所有 $2 \times 2$ 的子矩阵（共有 $(N-1) \times (N-1)$ 个）必须包含恰好 2 头奶牛。

例如，这一放置方式是合法的：

```
CCC
...
CCC
```

而这一放置方式是不合法的，因为右下的 $2 \times 2$ 正方形区域仅包含 1 头奶牛：

```
C.C
.C.
C..
```

没有其他限制。你可以假设 Farmer John 有无限多的奶牛（根据以往的经验，这种假设似乎是正确的……）。

Farmer John 更希望某些方格中包含奶牛。具体地说，他相信如果方格 $(i, j)$ 中放有一头奶牛，照片的美丽度会增加 $a_{ij}$（$0 \leq a_{ij} \leq 1000$）单位。

求合法的奶牛放置方式的最大总美丽度。


## 说明/提示

在这个样例中，最大美丽度可以在如下放置方式时达到：

```
CC..
..CC
CC..
..CC
```

这种放置方式的美丽度为 $3 + 3 + 3 + 1 + 3 + 3 + 3 + 3 = 22$。

测试点性质：

 - 测试点 2-4 满足 $N \le 4$。
 - 测试点 5-10 满足 $N\le 10$。
 - 测试点 11-20 满足 $N \le 1000$。

供题：Hankai Zhang，Danny Mittal

## 样例 #1

### 输入

```
4
3 3 1 1
1 1 3 1
3 3 1 1
1 1 3 3```

### 输出

```
22```

# 题解

## 作者：K8He (赞：26)


[原题传送门](https://www.luogu.com.cn/problem/P7301)

~~神奇的5分算法：直接输出样例。~~
# 20分算法
直接把每个点是否有牛的状态DFS一遍同时判断是否合法，时间复杂度约为$O(2^{n^2})$（因为有判断合法的剪枝所以会比这个低）。而在前四个测试点中$N\le4$，用枚举算法在最坏情况下需要运行$65536$次，时间非常富裕，但是在之后的测试点中就会超时了。
# 50分算法
每四个方格内都有$C^2_4=6$种方法放置牛：
~~~
1   2   3   4   5   6
CC  C.  C.  .C  .C  ..
..  C.  .C  C.  .C  CC
~~~
DFS每四个方格内的六种情况同时判断是否合法，时间复杂度约为$O(6^{n^2})$（因为有判断合法的剪枝所以会比这个低）。
部分参考代码：
~~~
int a[1001][1001],ans,n;
char v[1001][1001];
string d[]={"cc00","c0c0","c00c","0cc0","0c0c","00cc"};
int dx[]={0,0,1,1};
int dy[]={0,1,0,1};
void dfs(int x,int y){
	int nextx=x,nexty=y+1;
	if(nexty==n) nextx++,nexty = 1;
	if(x>=n){
		int newscore=0;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) newscore+=v[i][j]=='c'?a[i][j]:0;
		ans=max(ans,newscore);//更新答案 
		return;	
	}
	for(int i=0;i<6;i++){
		int match=true;
		string old="";
		for(int j=0;j<4;j++) old+=v[x+dx[j]][y+dy[j]];
		for(int j=0;j<4;j++){
			int row=x+dx[j],col=y+dy[j];
			if(v[row][col]!=' '&&v[row][col]!=d[i][j]){//判断是否合法 
				match=false;
				break;
			}
		}
		if(match){
			for(int j=0;j<4;j++) v[x+dx[j]][y+dy[j]]=d[i][j];
			dfs(nextx,nexty);
			for(int j=0;j<4;j++) v[x+dx[j]][y+dy[j]]=old[j];
		}//回溯 
	}
}
~~~
上面这份代码是我的神仙老师 @[akic](https://www.luogu.com.cn/user/333773) 写的，大家可以去膜拜他
# 满分算法
先给大家看几种合法的$3\ast3$放置方法：
~~~
C.C  CC.  C.C  ..C
C.C  ..C  .C.  CC.
.C.  CC.  C.C  ..C
~~~
发现了吧，**每一行或每一列的奶牛排列方式一定是交替排列的，而且上一行或上一列的交替排列方式对这一行或这一列交替排列方式没有影响**，所以我们只需要先计算每一行的奇数列之和 和 偶数列之和 以及每一列的奇数行之和 和 偶数行之和（建议多读几遍，我当时都写晕了），再取每行的两种交替方式中的最大值，最后再取行上交替排列和列上交替排列的最大值就是答案了。

参考代码：
~~~cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,x[1010][2],y[1010][2],num,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&a),x[i][j%2]+=a,y[j][i%2]+=a;
	for(int i=1;i<=n;++i)
		num+=max(x[i][1],x[i][0]),ans+=max(y[i][1],y[i][0]);
	printf("%d",max(num,ans));
	return 0;
}//为什么大家的代码都这么长啊……
~~~
------------
### Update 1（2021/2/14）：改正了50分算法的时间复杂度

---

## 作者：Diaоsi (赞：3)

### Update1:修了一点小锅

------------

**分析性质+贪心**

纪念一下这场被我 AK 的银组月赛。

首先考虑一种情况，若某行中有两只奶牛连在一起时：

```
	**CC**
	******
	******
```
“ * ”为暂时不确定该位是否可以放置。

显然，为了满足题目提供的要求（ $2 \ast 2$ 的矩阵内必须**恰好**有两头奶牛），如果出现了这种放置方式，那么这两头牛的下面一定不能放置奶牛。

于是我们有了下面这种放置方式：

```
	**CC**
	**..**
	**CC**
```

也就是说，对于这两列，奶牛**交替放置**

那么对于旁边的两列呢？

显然这种情况是**不会**出现的，因为不符合题目的要求：


```
	**CCC*
	**..C*
	**CC**
```

只能这样放：
```
	**CC.*	**CCC*
	**..C*	**...*
	**CC.*	**CCC*
```

也就是说，若一行中出现了**两个以上的**连起来放置的奶牛，那么为了符合题目要求，所有**列**的奶牛放置都是**交替进行的**

同理，若一列中出现了**两个以上的**连起来放置的奶牛，那么为了符合题目要求，所有**行**的奶牛放置都是**交替进行的**

显然若没有一列或一行出现了连续放置的奶牛，那么所有的牛都应该交替放置。

此时我们得到了一个性质：**对于最优的放置方式，要么它的行放置方式是交替的，要么它的列放置方式是交替的**。

也就是说，每一行或每一列的放置方式最多只有两种。

对每行每列取 $\max$ 即可。

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=10010,INF=0x3f3f3f3f;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
int n,ans1,ans2,a[N][N];
int line_sum(int j,int type){
	int res[2]={0,0};
	for(int i=1;i<=n;i++)
		res[i&1]+=a[i][j];
	return res[type];
}
int row_sum(int i,int type){
	int res[2]={0,0};
	for(int j=1;j<=n;j++)
		res[j&1]+=a[i][j];
	return res[type];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int k=1;k<=n;k++){
		if(line_sum(k,0)>line_sum(k,1))
			ans1+=line_sum(k,0);
		else ans1+=line_sum(k,1);
	}
	for(int k=1;k<=n;k++){
		if(row_sum(k,0)>row_sum(k,1))
			ans2+=row_sum(k,0);
		else ans2+=row_sum(k,1);
	}
	printf("%d\n",Max(ans1,ans2));
	return 0;
}
```




---

## 作者：JiaY19 (赞：2)

比较简单的一道题。
## 思路
根据题意我们可以知道，在每个 $2 × 2$ 方格内有且仅有六种放法。

即（黄色为奶牛）：
![](https://cdn.luogu.com.cn/upload/image_hosting/imkka61t.png)

那么以 $3 × 3$ 的方格，我们再举一个例子（红色代表不能放）。

![](https://cdn.luogu.com.cn/upload/image_hosting/3dk1m2in.png)

第一行模拟的是开始选横的两个。则他们下面两个就不能放，在下面就必须放。至于旁边的，有两种情况，我都模拟了出来。

第二行模拟的是开始选竖的两个。情况与上面大同小异。

而两个相交错的情况，与上面也是一样。

那么，我们不妨把情况推广到 $n × n$ 的方格中。

可以轻松的看出，整张图最终的答案，要么是横着奇偶交错相加，要么是竖着奇偶交错相加，只需要在加的时候取最大值即可。

## Code

```
#include<bits/stdc++.h>
using namespace std;
int n , ans1 , ans2 , a[1010][1010] , h[1010][10] , s[1010][10];
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++) for(int j = 1;j <= n;j++) cin >> a[i][j];
	for(int i = 1;i <= n;i++) for(int j = 1;j <= n;j++) s[i][j % 2] += a[i][j];
	for(int i = 1;i <= n;i++) for(int j = 1;j <= n;j++) h[i][j % 2] += a[j][i];
	for(int i = 1;i <= n;i++) ans1 += max(s[i][0] , s[i][1]) , ans2 += max(h[i][0] , h[i][1]);
	cout << max(ans1 , ans2);
	return 0;
}

```


---

## 作者：BreakPlus (赞：1)

仅此题解，纪念我在考场上唯一 $\color{green} \texttt{AC}$ 的题目。

## $\text{Part}$ #$\text{1}$ 部分分算法

对于第一档部分分，可以直接枚举放置状态。

第二档目前还不会。

## $\text{Part}$ #$\text{2}$ $\color{green} \texttt{AC}$ 算法

显然，像是个 $\text{dp}$ ，但是直接做不好做，可能还要找规律。接下来我们画几组可行的放置方案。

![image.png](https://i.loli.net/2021/01/30/vTOtJyrG9epk2dL.png)

发现了什么？奇数行的放置方案和偶数行的放置方案都分别相同。也就是说，在前两行的某一个位置上放置了奶牛，那么接下来和它行数奇偶性相同的行数、相同的列数的位置被捆绑放置了。我们可以将捆绑起来的地方预处理。预处理为 $sum$ 数组（请自行理解下列代码）

```cpp
for(int j=1;j<=n;j++)
	for(int i=1;i<=n;i+=2) sum[j][1]+=a[i][j];
for(int j=1;j<=n;j++)
	for(int i=2;i<=n;i+=2) sum[j][2]+=a[i][j];
```

然后就是化简为一个 $2 \times n$ 的矩阵搞事情了。这也很简单了，我们可以推得转移方程：

$F_{i,0}=F_{i-1,3}$

$F_{i,1}=\max (F_{i-1,1},F_{i-1,2}) + sum_{i,1}$

$F_{i,2}=\max (F_{i-1,1},F_{i-1,2}) + sum_{i,2}$

$F_{i,3}=F_{i-1,0}$

其中，$F_{i,x}$ 表示这个 $2 \times n$ 的矩阵的第 $i$ 列在 $x$ 的放置情况下，前 $i$ 列能够获得的最大值。当 $x= \{ 0,1,2,3\}$ 时，分别代表第 $i$ 列两个位置均不放置、第一个位置放置、第二个位置放置、均放置的情况。

```cpp
dp[1][0]=0;
dp[1][1]=sum[1][1];
dp[1][2]=sum[1][2];
dp[1][3]=sum[1][1]+sum[1][2];
for(int i=2;i<=n;i++){
	dp[i][0]=dp[i-1][3];
	dp[i][1]=maxx(dp[i-1][1],dp[i-1][2])+sum[i][1];
	dp[i][2]=maxx(dp[i-1][1],dp[i-1][2])+sum[i][2];
	dp[i][3]=dp[i-1][0]+sum[i][1]+sum[i][2];
}
```

显然，上述方程式是正确的。但是这样做仅能获得六个测试点的分数。为什么？看我举一个“奇数行的放置方案和偶数行的放置方案都分别相同”的反例：

![image.png](https://i.loli.net/2021/01/30/mFStL7P5Zx4TVgH.png)

其实我们不必慌张，这个图旋转 $90$° 后依然符合要求。也就是说，需要考虑旋转。注意：旋转 $0$° 与旋转 $180$° 是一样的；旋转 $90$° 与 $270$° 同理。我们需要做两次  $\text{dp}$ 。

至此，我们就 $\color{green} \texttt{AC}$ 了这道题。

## $\text{Part}$ #$\text{3}$   参考 $\text{Code}$

较复杂，轻喷。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[1010][1010],b[1010][1010],dp[1010][5],sum[1010][3];
int maxx(int a,int b){
    return a>b?a:b;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i+=2) sum[j][1]+=a[i][j];
    for(int j=1;j<=n;j++)
        for(int i=2;i<=n;i+=2) sum[j][2]+=a[i][j];
    dp[1][0]=0;
    dp[1][1]=sum[1][1];
    dp[1][2]=sum[1][2];
    dp[1][3]=sum[1][1]+sum[1][2];
    for(int i=2;i<=n;i++){
        dp[i][0]=dp[i-1][3];
        dp[i][1]=maxx(dp[i-1][1],dp[i-1][2])+sum[i][1];
        dp[i][2]=maxx(dp[i-1][1],dp[i-1][2])+sum[i][2];
        dp[i][3]=dp[i-1][0]+sum[i][1]+sum[i][2];
    }
    int answer=maxx(maxx(dp[n][0],dp[n][1]),maxx(dp[n][2],dp[n][3]));
    memset(dp,0,sizeof(dp));
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[j][n-i+1]=a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=b[i][j];
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i+=2) sum[j][1]+=a[i][j];
    for(int j=1;j<=n;j++)
        for(int i=2;i<=n;i+=2) sum[j][2]+=a[i][j];
    dp[1][0]=0;
    dp[1][1]=sum[1][1];
    dp[1][2]=sum[1][2];
    dp[1][3]=sum[1][1]+sum[1][2];
    for(int i=2;i<=n;i++){
        dp[i][0]=dp[i-1][3];
        dp[i][1]=maxx(dp[i-1][1],dp[i-1][2])+sum[i][1];
        dp[i][2]=maxx(dp[i-1][1],dp[i-1][2])+sum[i][2];
        dp[i][3]=dp[i-1][0]+sum[i][1]+sum[i][2];
    }
    answer=maxx(answer,maxx(maxx(dp[n][0],dp[n][1]),maxx(dp[n][2],dp[n][3])));
    printf("%d\n",answer);
    return 0;
}
```

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经了解了题目意思

我们可以任意观察一个$2*2$的网格

一共有$4$种方法

CC  C. C. .C .C ..

..  C. .C C. .C CC

我们可以发现，无论怎么放置奶牛，两行或两列一定为一头奶牛和一块空地

所以如果这么填下去，一定会有一行或者一列出现隔一个跳一个的情况

所以，我们分情况讨论，最后求最大值即可

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))
		{
			f|=(c=='-');
			c=getchar();
		}
	while(isdigit(c))
		{
			x=(x<<1)+(x<<3)+(c^48);
			c=getchar();
		}
	return f?-x:x;
}
inline void write(int x){
	if(x<0)
		{
			putchar('-');
			x=-x;
		}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int n;
int a[1010][1010];
int st1[1010],st2[1010];
int ct1[1010],ct2[1010];
int ans1,ans2;
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			a[i][j]=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;j+=2)
			st1[i]+=a[j][i];
	for(register int i=1;i<=n;++i)
		for(register int j=0;j<=n;j+=2)
			st2[i]+=a[j][i];
	for(register int i=1;i<=n;++i)
		ans1+=max(st1[i],st2[i]);
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;j+=2)
			ct1[i]+=a[i][j];
	for(register int i=1;i<=n;++i)
		for(register int j=0;j<=n;j+=2)
			ct2[i]+=a[i][j];
	for(register int i=1;i<=n;++i)
		ans2+=max(ct1[i],ct2[i]);
	write(max(ans1,ans2));
	return 0;
}

```


---

## 作者：Skies (赞：0)

## 思路

这道题分析一下，可以发现：

**满足条件的放置方式，要么是行跳着放，要么列跳着放**

跳着放: $_C_C_C_C$

请读者自行分析（这是解题关键）

所以我们分成两种情况讨论

$1.$ 行跳着放   $2.$ 列跳着放

这里以 $1.$ 举例  

对于每一行，用 $sum(0)$ , $sum(1)$ 分别记录两种跳着放的方式

每行累加其中较大的

在用同样的方式操作 $2.$

输出其中较大的

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=1e3+10,M=2e5+10;
int a[N][N],n;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int sum[2];
		sum[0]=0,sum[1]=0;
		for(int j=1;j<=n;j++)
		{
			sum[j%2]+=a[i][j];
		}
		ans+=max(sum[1],sum[0]);
	}
	int aa=0;
	for(int i=1;i<=n;i++)
	{
		int sum[2];
		sum[0]=0,sum[1]=0;
		for(int j=1;j<=n;j++)
		{
			sum[j%2]+=a[j][i];
		}
		aa+=max(sum[1],sum[0]);
	}
	cout<<max(ans,aa);
}
```



---

