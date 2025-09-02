# Camels

## 题目描述

Bob likes to draw camels: with a single hump, two humps, three humps, etc. He draws a camel by connecting points on a coordinate plane. Now he's drawing camels with $ t $ humps, representing them as polylines in the plane. Each polyline consists of $ n $ vertices with coordinates $ (x_{1},y_{1}) $ , $ (x_{2},y_{2}) $ , ..., $ (x_{n},y_{n}) $ . The first vertex has a coordinate $ x_{1}=1 $ , the second — $ x_{2}=2 $ , etc. Coordinates $ y_{i} $ might be any, but should satisfy the following conditions:

- there should be $ t $ humps precisely, i.e. such indexes $ j $ ( $ 2<=j<=n-1 $ ), so that $ y_{j-1}&lt;y_{j}&gt;y_{j+1} $ ,
- there should be precisely $ t-1 $ such indexes $ j $ ( $ 2<=j<=n-1 $ ), so that $ y_{j-1}&gt;y_{j}&lt;y_{j+1} $ ,
- no segment of a polyline should be parallel to the $ Ox $ -axis,
- all $ y_{i} $ are integers between 1 and 4.

For a series of his drawings of camels with $ t $ humps Bob wants to buy a notebook, but he doesn't know how many pages he will need. Output the amount of different polylines that can be drawn to represent camels with $ t $ humps for a given number $ n $ .

## 说明/提示

In the first sample test sequences of $ y $ -coordinates for six camels are: 123421, 123431, 123432, 124321, 134321 и 234321 (each digit corresponds to one value of $ y_{i} $ ).

## 样例 #1

### 输入

```
6 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
0
```

# 题解

## 作者：叶枫 (赞：5)

$DP$

但可以优化到三维

### 题意：
给你一个数$N$，从$1$到$N$形成$t$个波峰和$t-1$个波谷,总共有多少种情况。

### 思路：
将问题分解为求$2\times t-1$个转折点，设$dp[x][y][t]$为当最后一点落在$(x,y)$上时，出现$t$个转折点的总数。那么对于当前点有两种情况，他的前一个点到当前点要么高度比他大，要么比他小。

若当前点$(x,y)$之前出现了$t$个转折点，若$t$为偶数，也就是说只要前一个点落点在当前点的下方，当前状态要想保持任然只出现偶数$t$个转折点的情况，则
$$dp[x][y][t]=\sum (dp[x-1][h][t])(1\le h<y)$$

同时只要前一个点落在当前点的上方，都可以达到

$$dp[x][y][t+1]=\sum (dp[x][h][t])(y<h\le 4)$$
当$t$为奇数时,同样的，

$$dp[x][y][t]=\sum (dp[x-1][h][t])(y<h\le 4);$$

$$dp[x][y][t+1]=\sum (dp[x-1][h][t])(1\le h<y)$$

当然，对于最开始的转折点一定是上升的。

```cpp
int dp[25][5][25];
signed main(){
	for(int i=1;i<=3;i++) dp[1][i][0]=1;
	for(int x=2;x<22;x++)
	for(int y=1;y<=4;y++)
	for(int t=0;t<21;t++)
	for(int h=1;h<=4;h++){
		if(x==2){
            if(y>h){
            if(t%2) dp[2][y][t+1]+=dp[1][h][t];
            else dp[2][y][t]+=dp[1][h][t];
        	}
        }
        else{
            if(t%2){
            if(h>y) dp[x][y][t]+=dp[x-1][h][t];
            else if(h<y) dp[x][y][t+1]+=dp[x-1][h][t];
            }
            else{
            if(h<y) dp[x][y][t]+=dp[x-1][h][t];
            else if(h>y) dp[x][y][t+1]+=dp[x-1][h][t];
            }
        }
	}
	int n=read(),t=read();
	if(t*2+1>n||n>6*t+1) return puts("0"),0;
	int ans=0;
	for(int i=1;i<=4;i++)
	ans+=dp[n][i][2*t-1];
	printf("%d",ans); 
	return 0;
}
```

---

## 作者：ZJMZJM (赞：5)

~~看到n，t那么小，立刻想到了打表~~

~~然而并无卵用~~

题目意思是：求方案数

于是我们想到了DP
 
//f[i][j][k][r] 第i个数为j时在第k个驼峰上处于 r=1上升,r=0下降 状态的方案数

code
```
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>//头文件
#define For(k,i,j) for(int k=i;k<=j;k++)//简写for
#pragma GCC optimize(4)//O4
#define MAXN 20
#define MAXT 10
#define MAXK 4
#define MAXR 2//四个变量
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}//快读
int f[MAXN+2][MAXK+2][MAXT+2][MAXR+2];//数组，f[i][j][k][r]
int main()
{	
	int n=read(),t=read(),ans;
    f[2][2][1][1]=1;
    f[2][3][1][1]=2;
    f[2][4][1][1]=3;//初始化
    For(i,3,n)
       For(j,1,4)
            For(k,1,t) 
			{
                for(int r=4;r>j;r--)
                    f[i][j][k][0]+=f[i-1][r][k][0]+f[i-1][r][k][1];
                For(r,1,j-1)
                    f[i][j][k][1]+=f[i-1][r][k][1]+f[i-1][r][k-1][0];
            }//状态转移
    For(i,1,MAXK)
        ans+=f[n][i][t][0];//方案数相加
    printf("%d\n",ans);
    return 0;
}
```
四层for循环，然而n，t实在太小，也可以过。

PS：题目数据范围翻译有误：应为 3≤n≤20, 1≤t≤10

---

## 作者：Fading (赞：5)

考虑**暴力AC**。

设$f[i][j][k][a1][a2]$
为第
$i$位，$a[i]=j,a[i-1]=k$，已经满足$a1$个要求$1$，$a2$个要求$2$。

然后暴力转移就好了，复杂度$O(nt^2)$

$if\ (i<j$&&$j>k)\ \ f[l+1][j][k][a1+1][a2]+=f[l][i][j][a1][a2];$

$if\ (i>j$&&$j<k)\ \ f[l+1][j][k][a1][a2+1]+=f[l][i][j][a1][a2];$

$if\ (i!=j$&&$j!=k)\ \ f[l+1][j][k][a1][a2]+=f[l][i][j][a1][a2];$

orz楼下$O(nt)$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,t,f[25][5][5][25][25];
int main(){
	cin>>n>>t;
	if (n<=2){
		cout<<"0";
		return 0;
	}
	for (int i=1;i<=4;i++){
		for (int j=1;j<=4;j++){
			if (i!=j) f[2][i][j][0][0]=1;
		}
	}
	for (int l=2;l<=n;l++){
		for (int a1=0;a1<=t;a1++){
			for (int a2=0;a2<=t-1;a2++){
				for (int i=1;i<=4;i++){
					for (int j=1;j<=4;j++){
						for (int k=1;k<=4;k++){
							if (i<j&&j>k) f[l+1][j][k][a1+1][a2]+=f[l][i][j][a1][a2];
							else if (i>j&&j<k) f[l+1][j][k][a1][a2+1]+=f[l][i][j][a1][a2];
							else if (i!=j&&j!=k) f[l+1][j][k][a1][a2]+=f[l][i][j][a1][a2];
						}
					}
				}
			}
		}
	}
	ll ans=0;
	for (int i=1;i<=4;i++){
		for (int j=1;j<=4;j++){
			if (i!=j) ans+=f[n][i][j][t][t-1];
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：starrylasky (赞：4)

[~~**博客查看体验更佳**~~](https://www.cnblogs.com/hhhsky001/articles/16269046.html)

# 题面描述

[link](https://www.luogu.com.cn/problem/CF14E)

# Solution ： dp

考虑定义 $f_{i,j,k,p,q}$ ：到第 $i$ 个，有 $j$ 个 $a_{i-1}>a_i<a_{i+1}$ ， $k$ 个 $a_{i-1}<a_i>a_{i+1}$ 当前位置取 $p$ ， $q:a_{i-1}<a_i:0,a_{i-1}>a_i:1$ 。

## 转移：

$f_{i,j,k,p,0}=\sum_1^{p-1} f_{i-1,j,k,q,0}+f_{i-1,j-1,k,q,1}$

$f_{i,j,k,p,1}=\sum_{p+1}^4 f_{i-1,j,k,q,1}+f_{i-1,j,k-1,q,0}$

## code

```cpp
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define re register
#define int long long
#define fep(i,l,r) for(re int i=l;i<=r;++i)
#define For(i,u) for(re int i=head[u];i;i=e[i].nxt)
#define feb(i,r,l) for(re int i=r;i>=l;--i)
using namespace std;

const int N = 21,M = 11;
int f[N][M][M][5][2],n,t;
//到第i个有j个a[i-1]>a[i]<a[i+1] k个a[i-1]<a[i]>a[i+1]当前位置取 p a[i-1]<a[i]:0,a[i-1]>a[i]:1 

inline int read() { int s=0,w=1; char ch=getchar(); while(!(ch<='9'&&ch>='0')) {if(ch=='-') w=-1; ch=getchar();} while(ch<='9'&&ch>='0') {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();} return s*w; }
inline void write(int x) { if(x>=10) write(x/10); putchar(x%10+'0'); }
inline void print(int x,char ch) { if(x<0) putchar('-'),x=~(x-1); write(x);  putchar(ch);}
inline void swap(int &x,int &y) {x^=y,y^=x,x^=y;}

signed main()
{
	n=read(),t=read();
	if(n<=2) puts("0"),exit(0);
	fep(i,1,4) f[2][0][0][i][0]=i-1,f[2][0][0][i][1]=4-i;
	//fep(i,1,4) cout<<f[2][0][0][i][0]<<" "<<f[2][0][0][i][1]<<endl;
	fep(i,3,n)
	{
		fep(j,0,t-1)//a[i-1]>a[i]<a[i+1]
		{
			fep(k,0,t)//a[i-1]<a[i]>a[i+1]
			{
				fep(p,1,4)
				{
					//a[i-1]<a[i]:0,a[i-1]>a[i]:1 
					fep(q,1,p-1) f[i][j][k][p][0]+=f[i-1][j][k][q][0]+f[i-1][j-1][k][q][1];//a[i-2]>a[i-1]<a[i]
					fep(q,p+1,4) f[i][j][k][p][1]+=f[i-1][j][k][q][1]+f[i-1][j][k-1][q][0];//a[i-2]<a[i-1]>a[i]
				//	cout<<i<<" "<<j<<" "<<k<<" "<<p<<" "<<f[i][j][k][p][0]<<" "<<f[i][j][k][p][1]<<endl;
				}
			}
		}
	}
	int ans=0;
	fep(p,1,4) ans+=f[n][t-1][t][p][0]+f[n][t-1][t][p][1];
	print(ans,'\n');
	return 0;
}
```

---

## 作者：TainityAnle (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF14E)

既然题目用 hump，那我们就称 $a_{i-1}<a_i>a_{i+1}$ 的为峰,反之为谷。

这道题是一道紫，但我认为这个紫仅是针对那些优化，其实它用五维 DP 没有问题，~~对于五维 DP，是个绿就不错。~~

设数组（状态）$dp_{pos,up,down,pre,num}$，$pos$ 表示当前遍历到了哪个数，可以看做下标，$up$ 表示峰的数量，$down$ 表示谷的数量，$pre$ 表示上一个数放了几，$num$ 表示当前的数放了几。

这种五维 DP 的做法，洛谷题解写的很好，但我要写一个不一样的 DP，这道题，我要用搜索来做，但是，虽然说是使用了搜索，但是其思想是完完全全的 DP，而 DP 数组也是保留了的，它用来记忆化，如果不记忆化，妥妥的超时。

DP 数组的建模和上面的建模是一样的，其实这个建模就是这道题的重点。

关于做法，干讲不好说，重点思路其实就是上面的建模，做法我都写到代码注释上了。

空间非常极限，要“节约”一点。

还有一点：开 long long！！！

代码（重点看注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[21][15][15][5][5],res,n,t;
long long dfs(long long pos,long long up,long long down,long long pre,long long num) {
	if(down<0||up<0) return 0;
	if(dp[pos][up][down][pre][num]!=-1) return dp[pos][up][down][pre][num];//记忆化操作，此处为返回已求出的值
	if(pos<=2) {//这个特判必须要加，我一开始就是这里死的
		if(up==0&&down==0) return dp[pos][up][down][pre][num]=1;
		else return dp[pos][up][down][pre][num]=0;
	}
	long long ans=0;
	for(int i=1; i<=4; i++) {//开始给当前位置填数
		if(i==pre) continue;//题目规定，相邻位置不能相等
		//共有三种情况，这里是峰、这里是谷或啥也不是
		if(i>pre&&pre<num) 		ans+=dfs(pos-1,up,down-1,i,pre);//当有可能成为谷时，上一状态是位置-1，谷数-1，其他不变
		else if(i<pre&&pre>num) ans+=dfs(pos-1,up-1,down,i,pre);//当有可能成为峰时，上一状态是位置-1，峰数-1，其他不变
		else			   		ans+=dfs(pos-1,up,down,i,pre);//其余情况，啥也不是，上一状态位置-1，其他不变
	}
	return dp[pos][up][down][pre][num]=ans;//记忆化操作，此处为对未知的位置赋值
}
int main() {
	memset(dp,-1,sizeof dp);
	cin>>n>>t;
	for(int i=1; i<=4; i++)//枚举pre和num
		for(int j=1; j<=4; j++)
			if(i!=j) //题目规定，相邻位置不能相等
				res+=dfs(n,t,t-1,i,j);
	cout<<res;
	return 0;
}
```


---

## 作者：Composite_Function (赞：2)

# 思路

一眼看上去，就是道很裸的 $\texttt{DP}$。观察下数据，发现范围小的可怜，连降维都不需要了。~~真不愧为紫题~~

1. **状态**：$num[i][a][b][x][y]$ 表示到第 $i$ 位，$a[i] = a$，$a[i - 1] = b$，并且有 $x$ 个峰顶，$y$ 个谷底。
2. **动态转移方程**：$\forall i, j, k, tmp$，均有

$\left\{
\begin{array}{rcl}
num[tmp + 1][j][k][x][y + 1] \leftarrow&num[tmp + 1][j][k][x][y + 1] + ans[tmp][i][j][x][y]&(i > j, j < k)\\
num[tmp + 1][j][k][x + 1][y] \leftarrow&num[tmp + 1][j][k][x + 1][y] + num[tmp][i][j][x][y]&(i < j, j > k)\\
num[tmp + 1][j][k][x][y] \leftarrow&num[tmp + 1][j][k][x][y] + num[tmp][i][j][x][y]&(other, i \not = j \not = k)\\
\end{array}
\right.$
3. **初始值**：$\forall a, b \in [1, 4] ~~ num[2][a][b][0][0]$（注意这里翻译有误，$n \in [3, 20]$）。

------------

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define N 25
#define M 10
long long n,t,num[N][M][M][N][N],ans;
int main(){
	cin>>n>>t;
	if(n<=2){cout<<"0"; return 0;} // 习惯性的写一句，虽然题目保证不会有
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			if(i!=j) num[2][i][j][0][0]=1;
	for(int l=2;l<=n;l++)
		for(int num1=0;num1<=t;num1++)
			for(int num2=0;num2<=t-1;num2++)
				for(int i=1;i<=4;i++)
					for(int j=1;j<=4;j++)
						for(int k=1;k<=4;k++)
							if(i<j&&j>k) num[l+1][j][k][num1+1][num2]+=num[l][i][j][num1][num2];
							else if(i>j&&j<k) num[l+1][j][k][num1][num2+1]+=num[l][i][j][num1][num2];
							else if(i!=j&&j!=k) num[l+1][j][k][num1][num2]+=num[l][i][j][num1][num2]; // 动态转移方程
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			if(i!=j) ans+=num[n][i][j][t][t-1]; // 注意最后要求和（为了这个我调了半天）
	cout<<ans<<endl; return 0;
}
```

---

## 作者：Jerrlee✅ (赞：2)

**首先声明一下，这是一篇不正经的题解。**
## 题意
一行有 $n$ 个空位，每个空位可以填 $[1,4]$ 的整数，相邻两个数不相同，要求：

1. 有 $t$ 个位置满足 $a_{i-1}<a_i>a_{i+1}$ 且 ($1<i<n$)；
2. 有 $t-1$ 个位置满足 $a_{i-1}>a_i<a_{i+1}$。

范围：$1 \leq n \leq 20$，$1 \leq t \leq 10$。
## 思路
看到数据范围小，首先想到爆搜，但分支太多，还是会 T：<https://codeforces.com/contest/14/submission/149478428>

但既然有了暴力程序，数据范围这么小，我们可以想到什么？

**对啊，打表啊！**

对爆搜程序（假设大家都会，不进行讲解）进行修改，记得多测清空即可：
```cpp
#include<cstdio>
#include<cstring>
int n,t,ans,a[50];
void dfs(int x,int y,int z){
	if(y>t||z>=t) return;
	if(x==n+1){
		if(y==t&&z==t-1) ans++;
		return;
	}
	for(int i=1;i<=4;i++){
		if(a[x-1]!=i){
			a[x]=i;
			if(x<3) dfs(x+1,y,z);
			else{
				if(a[x-2]<a[x-1]&&a[x-1]>i) dfs(x+1,y+1,z);
				else if(a[x-2]>a[x-1]&&a[x-1]<i) dfs(x+1,y,z+1);
				else dfs(x+1,y,z);
			}
		}
	}
}
int main(){
    for(int i=1;i<=20;i++){
        for(int j=1;j<=10;j++){
	        n=i,t=j,ans=0;
	        memset(a,0,sizeof a);
	        dfs(1,0,0);
	        printf("if(n==%d&&t==%d) cout<<%d<<endl;\n",n,t,ans);
        }
    }
}
```
输出出来的就是表啦！

代码太长了，放剪贴板里了：<https://www.luogu.com.cn/paste/rt4w43t4>

[AC 记录（洛谷）](https://www.luogu.com.cn/record/71286874)

[AC 记录（CF）](https://codeforces.com/contest/14/submission/149478154)

---

## 作者：zilingheimei (赞：1)

首先，我们先看题目

[CF14E Camels](https://www.luogu.com.cn/problem/CF14E)

#### 这题我们可以用五维dp来过。


------------


### 思路

1. 我们一眼可以发现，这题暴搜是过不了的，时间复杂度 $O(n)$ 。那么我们可以怎样呢，很显然，暴搜过不了那就 $dp$  ~~逝世~~ 试试。

2. 那么怎么 $dp$ 呢，我们第一个应该想到可以多维表示，比如      $dp(i,j,k,l,x,y)$ 表示。

#### 填到第 $i$ 个数，第 $i-2$ 个数为 $j$ ，第 $i-1$ 个数为 $k$ ，第 $i$ 个数为 $l$ 。

#### 完成 $x$ 个条件 $1$ ， $y$ 个条件 $2$ 时	是否可以。

#### 很容易发现，当 $j<k$ 并且 $k>l$ 时，可以满足$dp(i,j,k,l,x,y)+dp(i-1,j,k,x,y-1)$ 。

#### 并且,当 $j>k$ 并且 $k<l$ ，可以满足 $dp(i,k,l,x,y)+dp(i-1,j,k,x-1,y)$ 。

#### 而要是都不满足，那么就是先前的 $dp(i,k,l,x,y)+dp(i-1,k,l,x,y)$ 。

3. 很显然，我们的 $dp$ 数组并不需要 $j,k,l$ 全部表示，只需要 $i-1$ 与$i$即可，那么 $dp(i,k,l,x,y)$ 便可以转化为 $dp(i,k,l,x,y)$ 。

4. 所以状态转移方程便可以表示为 $dp(i,k,l,x,y)=dp(i,k,l,x,y)+dp(i-1,j,k,x-1,y)+dp(i-1,j,k,x,y-1)$ ，而后两项则分别安装题目要求。
```
for(int i=3;i<=n;i++){
	for(int j=1;j<=4;j++){
		for(int k=1;k<=4;k++){
			for(int l=1;l<=4;l++){
				for(int x=0;x<=t;x++){
					for(int y=0;y<=t;y++){
						if(k==j||k==l)continue;//不满足跳过，但是注意只是j=k与k=l时不满足，可以参考题意理解
						if(j<k&&k>l){//条件1
							if(x>=1){
								f[i][k][l][x][y]+=f[i-1][j][k][x-1][y];
							}
						}
						else if(j>k&&k<l){//条件2
							if(y>=1){
								f[i][k][l][x][y]+=f[i-1][j][k][x][y-1];
							}
						}
						else {//普通情况
							f[i][k][l][x][y]+=f[i-1][j][k][x][y];
						}
					}
				}
			}
		}
	}
}
```


5. 然后我们附上初值 $dp(2,i,j,0,0)=1$ ，表示填$2$个，都不一定满足条件的情况是满足的。
```cpp
for(int i=1;i<=4;i++){
	for(int j=1;j<=4;j++){
		if(i==j)continue;//不满足时跳过
		f[2][i][j][0][0]=1;//初始化		
	}
}
```


6. 最后，我们搜 $k$ 与 $l$ ，也就是 $dp(n,k,l,t,t-1)$ ，加起来即可得到答案。
```cpp
int ans=0;
for(int i=1;i<=4;i++){
	for(int j=1;j<=4;j++){
		ans+=f[n][i][j][t][t-1];//计数
	} 
}
```


------------


### 思路题解中已讲，完整代码就不放了蛤。



---

## 作者：Tenderfoot (赞：1)

我们令 $Dp_{i,j,k,Opt}$ 表示第 $i$ 位，并且有 $j$ 个位置满足条件 $1$，待填的数是 $k$，上升下降趋势是 $Opt(Opt\in\{0,1\})$。

不难得到方程

$$
\begin{aligned}
\left\{\begin{matrix}
Dp_{i,j,k,0}=\sum\limits_{i=3}^{n} Dp_{i-1,j,l,0}+Dp_{i-1,j,l,1}(l<k)\\ 
Dp_{i,j,k,1}=\sum\limits_{i=3}^{n} Dp_{i-1,j,l,1}+Dp_{i-1,j-1,l,0}(l>k)
\end{matrix}\right.
\end{aligned}
$$

代码

```cpp
#include<bits/stdc++.h>

#define Mod 1000000009
#define int long long
#define MAXN 1000010
#define Enter puts("")
#define Space putchar(' ')
#define Test_Begin Enter , puts("Test--------------")
#define Test_End Enter , puts("--------------------")

using namespace std;

constexpr int INF = 2147483647;

static inline int Read()
{
	int Ans = 0;
	char Ch = getchar(), Las = ' ';
	while (!isdigit(Ch))
	{
		if (Ch == '-')
			Las = '-';
		Ch = getchar();
	}
	while (isdigit(Ch))
	{
		Ans = Ans * 10 + Ch - '0';
		Ch = getchar();
	}
	if (Las == '-')
		Ans = -Ans;
	return Ans;
}

static inline void Write(int x)
{
	if (x < 0)
	{
		x = -x;
		putchar('-');
	}
	if (x >= 10)
		Write(x / 10);
	putchar(x % 10 + '0');
}

int Dp[30][30][30][30];
int Ans;

signed main()
{
    int n = Read() , m = Read();
    Dp[2][0][4][0] = 3;
    Dp[2][0][3][0] = 2;
    Dp[2][0][2][0] = 1;
    for(register int i = 3; i <= n; i++)
        for(register int j = 0; j <= m; j++)
            for(register int k = 1; k <= 4; k++)
                for(register int l = 1; l <= 4; l++)
                {
                    if(l < k)
                        Dp[i][j][k][0] += Dp[i - 1][j][l][0] + 
                                          Dp[i - 1][j][l][1];
                    if(l > k)
                        Dp[i][j][k][1] += Dp[i - 1][j][l][1] + 
                                       (j > 0 ? Dp[i - 1][j - 1][l][0] : 0);
                    
                }
    for(register int i = 1; i <= 4; i++)
        Ans += Dp[n][m][i][1];
    Write(Ans) , Enter;
    return 0;
}
```


---

## 作者：hexagon (赞：1)

下文中，我们称 $a_{i-1}<a_i>a_{i+1}$ 的 $i$ 为山峰，$a_{i-1}>a_i<a_{i+1}$ 的 $i$ 为山谷。

那么显然，两个连续的山峰间必定存在一个山谷。

所以我们只需要保证再又 $t$ 个山峰的前提下，首尾都是山峰，就可以满足题目中的条件。

我们考虑 $dp$ 设 $dp[i][j][k][l]$ 表示考虑前 $i$ 个位置，第$i$个位置填 $j$ ，第 $i-1$ 个位置填 $k$ ，出现了 $l$ 个山峰的方案数。

答案为
$$
\sum_{i=1}^{4}{\sum_{j=1}^{4,j\neq i}{dp[n][i][j][t]}}
$$
 我们考虑转移，对于状态 $dp[i][j][k][l]$ ,如果在 $i+1$ 放入的数是 $x$ ,那么我们只用考虑 $i$ 是否会成为山峰：
$$
dp[i+1][x][j][l] \leftarrow dp[i][j][k][l] (j>k,j>x) 
$$
$$
dp[i+1][x][j][l+1] \leftarrow dp[i][j][k][l] (otherwise)
$$
注意首位都是山峰这个限制。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;i--)
#define mem(a,b) memset(a,b,sizeof(a))
#define ll long long
using namespace std;
int n,t; 
ll dp[25][5][5][15];
inline int read(){
	int f=1,x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return f*x;
}
int main(){
	n=read(),t=read();
	rep(i,1,4) rep(j,1,4) dp[2][i][j][0]=1;
	rep(i,3,n) rep(j,1,4) rep(k,1,4) rep(l,1,4) if(l!=k&&l!=j) rep(w,0,t){
		if(w==0&&l<k&&l<j) continue;
		if(w==t&&l<k&&l<j) continue;
		dp[i][k][l][(k<l&&l>j)+w]+=dp[i-1][l][j][w];
	}
	ll ans=0;
	rep(i,1,4) rep(j,1,4) ans+=dp[n][i][j][t];
	printf("%lld",ans);
	return 0;
}


```



---

## 作者：dead_X (赞：1)

## 思路
看到 $n\leq20,m\leq10$，有以下几种可能：meet-in-the-middle，剪枝，网络流，dp。

然而我最近写了 eJOI 的一个 dp 题，就把这个题秒切了=_=

你会发现这个 $a_{i-1}<a_{i}>a_{i+1}$ 和 $a_{i-1}>a_{i}<a_{i+1}$ 只和前两个数有关，结合 $4$ 的神奇值域，我们可以考虑**前两个位置**和**已经有前两种要求的个数**来 dp。

我们设 $dp_{t,i,j,x,y}$ 为**枚举到第 $t$ 个数，最后两个是 $i,j$，两种要求已经满足 $x,y$ 个**的情况数，然后转移十分简单。枚举三个数 $i,j,k$，要求 $i\neq j$ 且 $j\neq k$。

如果 $i>j$ 且 $j<k$，所有的 $dp_{t,i,j,x,y}$ 都能转移到 $dp_{t+1,j,k,x,y+1}$。

如果 $i<j$ 且 $j>k$，所有的 $dp_{t,i,j,x,y}$ 都能转移到 $dp_{t+1,j,k,x+1,y}$。

对于剩下的情况，所有的 $dp_{t,i,j,x,y}$ 都能转移到 $dp_{t+1,j,k,x,y}$。

时间复杂度~~懒得算~~是 $O(4^2nt^2)$，反正能过。

记得开 ``long long`` ，虽然我不知道 ``int`` 会不会挂。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
long long ans[23][13][13][4][4],Ans;
signed main()
{
    int n=read(),t=read();
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(i!=j) ans[2][0][0][i][j]=1;
	for(int q=3; q<=n; q++) for(int i=0; i<4; i++) for(int j=0; j<4; j++) for(int k=0; k<4; k++)
	if(i<j&&j>k) for(int l=1; l<=t; l++) for(int m=0; m<t; m++) ans[q][l][m][j][k]+=ans[q-1][l-1][m][i][j]; 
	else if(i>j&&j<k) for(int l=0; l<=t; l++) for(int m=1; m<t; m++) ans[q][l][m][j][k]+=ans[q-1][l][m-1][i][j]; 
	else if(i!=j&&j!=k) for(int l=0; l<=t; l++) for(int m=0; m<t; m++) ans[q][l][m][j][k]+=ans[q-1][l][m][i][j]; 		
	for(int i=0; i<4; i++) for(int j=0; j<4; j++) Ans+=ans[n][t][t-1][i][j];
	printf("%lld\n",Ans);
    return 0;
}

```

---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF14E)，巨水 $\tt^\ast1900$，简单 $\tt DP$。

$n$ 这么小，意味着我们怎么胡乱设状态（空间）都行。

考虑状态里应该有：

+ 当前推到第 $i$ 位
+ 出现了 $x$ 次波峰
+ 出现了 $y$ 次波谷
+ 上一个位置的数 $a^\prime=a_{i-1}$
+ 这一个位置的数 $b^\prime=a_i$。

总共是五维 $dp_{i,a,b,x,y}$。

---

初始化：$\forall a,b\in[1,4]\operatorname{and}i\ne j,dp_{0,a,b,x,y}=1$。

转移：枚举 $i,a,b,c,x,y$，然后

+ 如果 $\{a,b,c\}$ 是一个波峰，此时 $dp_{i,b,c,x,y}$ 加上 $dp_{i-1,a,b,x-1,y}$。
+ 如果 $\{a,b,c\}$ 是一个波谷，此时 $dp_{i,b,c,x,y}$ 加上 $dp_{i-1,a,b,x,y-1}$。
+ 否则 $dp_{i,b,c,x,y}$ 加上 $dp_{i-1,a,b,x,y}$。

答案是 $\displaystyle\sum_{a,b\in[1,4]}dp_{n,a,b,t,t-1}$。

---

## 作者：MCRS_lizi (赞：0)

[CF14E题目传送门](https://www.luogu.com.cn/problem/CF14E)
# 题目大意
输入 $n$ , $t$ ，求出所有满足：

1. 对于所有 $i$ $(1<i<n)$ 有 $t$ 个位置满足 $a_{i-1}<a_{i}>a_{i+1}$ 。

2. 对于所有 $i$ $(1<i<n)$ 有 $t-1$ 个位置满足 $a_{i-1}>a_{i}<a_{i+1}$ 。

3. 对于所有 $i$ $(1<=i<=n)$ ，满足 $1<=a_{i}<=4$ 。 

的序列 $a$ 的情况数量。

其中 $3<=n<=20$ ， $1<=t<=10$ 。
# 题目分析
这道题目数据范围比较小，最最暴力的方法就是搜索，时间复杂度为 $O(4^n)$ ，似乎差了一些。

那么接下来考虑dp解决，首先我们需要考虑怎么开dp数组的问题。

经过我的深思熟虑，既然数据范围这么小，那我们完全可以开一个五维数组。

则 $dp [i][j][flag][k][l]$ 为推到第 $i$ 位，这时填入数据为 $j$ ，有 $k$ 个位置满足条件1， $l$ 个位置满足条件2， $flag=1$ 表示这个位置数据比上个位置大， $flag=0$ 表示比上个位置小的情况数。

开好了数据，就可以推状态转移方程了。

若 $k>0$ ，就有 $dp[i][j][0][k][l]+=dp[i-1][f][1][k-1][l]$ 。 $(j<f<=4)$

若 $l>0$ ，就有 $dp[i][j][1][k][l]+=dp[i-1][f][0][k][l-1]$ 。 $(1<=f<j)$

$dp[i][j][1][k][l]+=dp[i-1][f][1][k][l]$ 。 $(1<=f<j)$

$dp[i][j][0][k][l]+=dp[i-1][f][0][k][l]$ 。 $(j<f<=4)$

状态转移方程有了，接下来给个初始值，dp还不是轻轻松松？

时间复杂度约为 $O(nt^2)$ 。
#  _**Code**_ 
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,dp[21][6][2][15][15];
signed main()
{
	cin>>n>>t;
	if(n<3)
	{
		cout<<0;
		return 0;
	}
	dp[2][1][0][0][0]=3;
	dp[2][2][0][0][0]=2;
	dp[2][3][0][0][0]=1;
	dp[2][2][1][0][0]=1;
	dp[2][3][1][0][0]=2;
	dp[2][4][1][0][0]=3;//给初始值
	for(int i=3;i<=n;i++)
	{
		for(int j=1;j<=4;j++)
		{
			for(int k=0;k<=t;k++)
			{
				for(int l=0;l<t;l++)
				{//状态转移
					if(l)
					{
						for(int f=1;f<j;f++)
						{
							dp[i][j][1][k][l]+=dp[i-1][f][0][k][l-1];
						}
					}
					if(k)
					{
						for(int f=j+1;f<=4;f++)
						{
							dp[i][j][0][k][l]+=dp[i-1][f][1][k-1][l];
						}
					}
					for(int f=1;f<j;f++)
					{
						dp[i][j][1][k][l]+=dp[i-1][f][1][k][l];
					}
					for(int f=j+1;f<=4;f++)
					{
						dp[i][j][0][k][l]+=dp[i-1][f][0][k][l];
					}
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=4;i++)
	{
		ans+=dp[n][i][0][t][t-1]+dp[n][i][1][t][t-1];//统计答案
	}
	cout<<ans;
 	return 0;
}//码完收工

```



---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1900}$
---
### 解题思路：

考虑动态规划。

设 $f_{i,j,k,x,y}$ 表示考虑到第 $i$ 个位置，第 $i-2$ 的位置上的数字是 $j$，第 $i-1$ 的位置上的数字是 $k$，已经满足了 $x$ 个条件一，$y$ 个条件二的方案数。

然后转移时枚举新的位置上的数，然后根据这个数的情况确定 $x$ 和 $y$ 即可。

---
具体地，设 $l$ 为 $i-2$ 位的数字，$j$ 为 $i-1$ 位的数字 $k$ 为 $i$ 位的数字，$x$ 为已经满足条件一的数量，$y$ 为已经满足条件二的数量，其中首先要保证 $j\neq k$ 且 $k\neq   l$：

1. 当满足 $j<k$ 且 $k>l$ 的时候，能够额外满足一个条件一，有：$f_{i,k,l,x,y}=\sum f_{i-1,j,k,x-1,y}$。

2. 当满足 $j>k$ 且 $k<l$ 的时候，能够额外满足一个条件二，有：$f_{i,k,l,x,y}=\sum f_{i-1,j,k,x,y-1}$。

3. 以上条件都不能满足时：$f_{i,k,l,x,y}=\sum f_{i-1,j,k,x,y}$。

统计答案的时候枚举最后两位即可。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long n,t,f[30][6][6][15][15],ans;
int main(){
	scanf("%I64d%I64d",&n,&t);
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
	if(i!=j)f[2][i][j][0][0]=1;
	
	for(int i=3;i<=n;i++)
	for(int x=0;x<=t;x++)
	for(int y=0;y<t;y++)
	for(int j=1;j<=4;j++)
	for(int k=1;k<=4;k++)
	for(int l=1;l<=4;l++)
	if(k!=j&&k!=l){
		if(j<k&&k>l){
			if(x>=1)f[i][k][l][x][y]+=f[i-1][j][k][x-1][y];
		}
		else{
			if(j>k&&k<l){
				if(y>=1)f[i][k][l][x][y]+=f[i-1][j][k][x][y-1];
			}
			else f[i][k][l][x][y]+=f[i-1][j][k][x][y];
		}
	}
	
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
	ans+=f[n][i][j][t][t-1];
	
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

这题目，真的有紫题的难度么 。。。。

考虑暴力搜索，大概是枚举前面一个点是什么数，前前一个是什么数，计算他们两个的贡献，也就是他们两个大于还是小于。

然后，，，这个东西我不确定能不能过，~~可以试试看~~。

不过么，想到这里，直接上一个记忆化，完事。

就是当前第几位，然后前一个是 $<$ 或者 $>$，多少个数满足条件 $1$，多少个数满足条件 $2$，前一个数是啥，然后第一个要大力枚举，计算贡献注意一下即可。

总时间复杂度 $O(n \times t^2 \times 32)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
int n,t,ans,f[23][15][15][15][15];
// 第几个，前一个是 > < 1/2 ，多少位置满足 1 多少满足 2，前一个是啥
// n*t^2*32
// 20*100*32
// 64000
int DFS(int a,int b,int c,int d,int e) {
        if (a>n) {
                if (c==t && d==t-1) return 1;
                else return 0;
        }
        if (b!=-1 && f[a][b][c][d][e]!=-1) return f[a][b][c][d][e];
        int res=0;
        for (int i=1; i<=4; i++) {
                if (i==e) continue; // 相邻的不能重复！
                res+=DFS(a+1,e<i ? 2 : 1,c+(b==2 && e>i),d+(b==1 && e<i),i);
        }
        if (b!=-1) f[a][b][c][d][e]=res;
        return res;
}
signed main()
{
        memset(f,255,sizeof f);
        scanf("%lld %lld",&n,&t);
        for (int i=1; i<=4; i++)
                ans+=DFS(2,-1,0,0,i);
        cout<<ans<<"\n";
        return 0;
}

```
谢谢！

---

