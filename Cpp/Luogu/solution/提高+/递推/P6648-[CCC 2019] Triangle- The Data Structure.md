# [CCC 2019] Triangle: The Data Structure

## 题目背景

在 Shuchong 的平行宇宙里，计算机学中的最重要的数据结构就是三角形。   
注：因为原数据包太大，故这题缩减了一些数据，具体缩减的数据点如下：

- Subtask 1：1 ~ 10
- Subtask 2：1 ~ 10

所以此题拥有的测试点为：

- Subtask 1：11 ~ 26
- Subtask 2：11 ~ 24

若想测试本题没有的测试点请到 [此处](https://www.luogu.com.cn/problem/U120704) 测试。

## 题目描述

大小为 $m$ 的一个三角形由 $m$ 行组成，第 $i$ 行包含 $i$ 个元素。   
并且，这些行必须排为等边三角形的形状。  
比如说，以下是一个 $m=4$ 的三角形。   
![](https://cdn.luogu.com.cn/upload/image_hosting/fdut4hrs.png)    
每个三角形还包含子三角形。   
比如说上面这个三角形，包含：
- $10$ 个大小为 $1$ 的三角形。
- $6$ 个大小为 $2$ 的三角形。
- $3$ 个大小为 $3$ 的三角形。

注意，每个三角形都是自身的子三角形。   
现在给定一个大小为 $n$ 的三角形，求对于每个大小为 $k$ 的子三角形，子三角形内几个数的最大值的和。

## 说明/提示

#### 数据规模与约定

- Subtask 1（25 pts）：$n \le 1000$。
- Subtask 2（75 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k \le n \le 3000$，$0 \le $ 三角形内每个数 $\le 10^9$。

#### 说明

**翻译自 [CCC 2019](https://cemc.math.uwaterloo.ca/contests/computing/2019/index.html) Senior T5 [Triangle: The Data Structure](https://cemc.math.uwaterloo.ca/contests/computing/2019/stage%201/seniorEF.pdf)。**   
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

## 样例 #1

### 输入

```
4 2
3
1 2
4 2 1
6 1 4 2```

### 输出

```
23```

# 题解

## 作者：有趣的问题 (赞：29)

提供一种不用倒三角形也不用单调队列的做法。

### 题意

给定一个等边三角形的数字阵，求所有边长为给定值的子三角形的最大值之和。

### 思路

看到这题，很容易想到用一个类似 ST 表的东西来做。对于每个点，我们维护以该点为三角形上顶点的子三角形的最大值。参考 ST 表的做法，我们只用维护边长为 $2$ 的次方的子三角形，然后用某种方法拼出查询所需要的三角形就可以了。

怎么拼呢？设查询的三角形边长为 $h$，也就是题目中输入的 $k$，那么显然我们需要用边长为 $2^{\log_2 k}$ 的三角形来拼它。首先需要下图中的三个：

![](https://cdn.luogu.com.cn/upload/image_hosting/pzpawrpz.png)

然后我们发现一个严重的问题：中间可能会有一个小三角形没有被覆盖到！

于是我们可以在底部正中间再放一个同样大小的三角形：

![](https://cdn.luogu.com.cn/upload/image_hosting/qljylfrr.png)

可是问题并没有完全解决，图中灰色的两块仍然没有被覆盖到啊……

于是我们发扬人类智慧：放一个不行，就放三个！

就有了下面这个：

![](https://cdn.luogu.com.cn/upload/image_hosting/lgr8ec2x.png)

容易证明，这样一定可以把中间的部分覆盖完（考虑红色三角形边长恰好是大三角形边长一半的情况）。

### 实现细节

想到这些，我兴致勃勃的写完交了一发：MLE。然后发现被毒瘤出题人卡空间了。注意到这题的询问子三角形大小是固定的，因此我们的 ST 表可以滚动起来，保留 $\log_2 k$ 的值就可以了。另外位运算什么的细节也比较多，比较考验仔细程度。

### 丑陋的代码

```c++
#include <bits/stdc++.h>
using namespace std;
int n,h,val[3005][3005],st[3005][3005][2],lg[3005],k;
long long ans;
int query(int x,int y){
	int l=x+h-1,r=y+h-1; 
	int u=k&1;
	int ans=max(st[x][y][u],max(st[l-(1<<k)+1][y][u],st[l-(1<<k)+1][r-(1<<k)+1][u]));
	if(k<=1)return ans;
	int cha=(h-(1<<k))>>1;
	ans=max(max(ans,st[l-(1<<k)+1][y+cha][u]),max(st[x+cha][y][u],st[x+cha][y+cha][u]));
	return ans; 
}
signed main(){
    freopen("star.in","r",stdin);
    freopen("star.out","w",stdout);
	cin>>n>>h;
	k=log2(h);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			scanf("%d",&val[i][j]);
			st[i][j][0]=val[i][j];
		}
	}
	for(int t=1;t<=k;t++){
		int u=t&1,v=u^1;
		for(int i=1;i+(1<<t)-1<=n;i++){
			for(int j=1;j<=i;j++){
				st[i][j][u]=max(max(st[i][j][v],st[i+(1<<t-1)][j][v]),st[i+(1<<t-1)][j+(1<<t-1)][v]);
				if(t>1){
					st[i][j][u]=max(max(st[i][j][u],st[i+(1<<t-1)][j+(1<<t-2)][v]),max(st[i+(1<<t-2)][j][v],st[i+(1<<t-2)][j+(1<<t-2)][v]));
				}
			}
		}
	}
	for(int i=1;i<=n-h+1;i++){
		for(int j=1;j<=i;j++){
			ans+=query(i,j);
		}
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：xiaolilsq (赞：13)

[题目链接](https://www.luogu.com.cn/problem/P6648)

## 题目分析

首先发现题目中要求的是一个三角形区域的最大值，第一时间想到的就是线段树和 ST 表，线段树不好维护三角形区域的最大值，考虑使用 ST 表（倍增）来求。

使用 ST 表最主要要考虑的问题就是如何转移，由于转移时可能需要用到倒着的三角形，不妨设 $dp(c,i,j,rv)$ 表示以 $(i,j)$ 作为顶部，大小为 $c$ ，是否倒着 $rv$ 的子三角形区域中的最大值是什么，每次我们都希望可以均分，所以考虑如何用大小为 $cc=\lceil\frac{c}{2}\rceil$ 的三角形区域最大值求出当且区域最大值。

转移如下：

$$
dp(c,i,j,0)=\max(dp(cc,i,j,0),dp(cc,i+c-cc,j,0),dp(cc,i+c-cc,j+c-cc,0),dp(cc,i+c-1,j+cc-1,1))
$$

$$
dp(c,i,j,1)=\max(dp(cc,i,j,1),dp(cc,i-c+cc,j,1),dp(cc,i-c+cc,j-c+cc,1),dp(cc,i-c+1,j-cc+1,0))
$$

怎么得到的呢？正着的三角形转移如下图（原谅我画的丑），其中当前三角形最大值是由三个红色边围成的三角形和一个黑色边围成的三角形取最大值。

![](https://cdn.luogu.com.cn/upload/image_hosting/qah2p47f.png)

如此我们便得到了 $\mathcal O(n^2\log_2k)$ 的算法。

## 具体如何实现

先将 $k,\lceil\frac{k}{2}\rceil,\dots$ 这些数记录下来，存到 $s$ 数组内，然后把 $c$ 的定义改为大小为 $s_c$ 的三角形即可。

建议使用递推而不是记搜，递推快些。

## 如何卡空间

发现这样直接做过不了，空间没法卡过，考虑使用滚动数组滚掉 $c$ 这一维，但是还是过不了，发现存储的是一个三角形区域，但是空间却开了一个矩形区域，可以再次压缩空间，不妨设 $sm_i=\sum_{j=1}^i j$ ，把原本的 $i,j$ 存储到 $i\times sm_{i-1}+j$ 即可将空间再次压缩。

## 参考代码

如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
const int maxn=3005;
int cnt,s[15],dp[2][maxn*maxn/2][2],sm[maxn];
int main(){
	int n,k;
	read(n),read(k);
	int ck=k;
	while(ck>1){
		s[cnt++]=ck;
		ck=(ck+(ck&1))>>1;
	}
	for(int i=2;i<=n;++i)sm[i]=sm[i-1]+i-1;
	for(int i=1,a;i<=n;++i)
		for(int j=1;j<=i;++j)
			read(a),dp[cnt&1][sm[i]+j][0]=dp[cnt&1][sm[i]+j][1]=a;
	for(int c=cnt-1;~c;--c){
		int o=c&1,_o=!o,sk=s[c],nt=(s[c]+(s[c]&1))>>1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=i;++j){
				for(int rv=0;rv<2;++rv){
					int re=0;
					if(!rv&&i+sk-1>n)continue;
					if(rv&&i-sk+1<1)continue;
					if(!rv){
						re=max(re,dp[_o][sm[i]+j][false]);
						re=max(re,dp[_o][sm[i+sk-nt]+j][false]);
						re=max(re,dp[_o][sm[i+sk-nt]+j+sk-nt][false]);
						re=max(re,dp[_o][sm[i+sk-1]+j+nt-1][true]);
					}
					else{
						re=max(re,dp[_o][sm[i]+j][true]);
						re=max(re,dp[_o][sm[i-sk+nt]+j][true]);
						re=max(re,dp[_o][sm[i-sk+nt]+j-sk+nt][true]);
						re=max(re,dp[_o][sm[i-sk+1]+j-nt+1][false]);
					}
					dp[o][sm[i]+j][rv]=re;
				}
			}
		}
	}
	long long ans=0;
	for(int i=1;i<=n-k+1;++i){
		for(int j=1;j<=i;++j){
			ans+=dp[0][sm[i]+j][false];
		}
	}
	write(ans),pc('\n');
	return 0;
}
```

---

## 作者：frostedstar (赞：10)

这里是[题目链接](https://www.luogu.com.cn/problem/P6648)。

萌新的第一篇题解，这道题做了好久，期间某一次提交超时了0.08s，这可太难受了。

![](https://cdn.luogu.com.cn/upload/image_hosting/2rs373va.png?x-oss-process=image/resize,m_lfit,h_170,w_225)![](https://cdn.luogu.com.cn/upload/image_hosting/ywcoir76.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

## 题目分析
题目需要求任意大小为 $k$ 的三角形里的数的最大值，这其实可以看作是一种RMQ问题，又由于数据是静态的，所以~~很容易~~可以想到用ST表来求。然而萌新不太会处理倒三角形的问题，所以我是全用正三角形进行转移的：

```c
st[k][i][j] = max(st[k - 1][i][j], *max_element(st[k - 1][i + ju] + j, st[k - 1][i + ju] + j + ju + 1));
```

 $st_{k,i,j}$ 代表以第 $i$ 行第 $j$ 列为上顶点的大小为 $2^k$（这个 $k$ 不是题目里的 $k$，只是一个普通的变量）的三角形的最大值，而 max_element 函数是一个求地址 $[a,b)$ 之间的最大值的函数，函数会返回最大值的地址，该函数的时间复杂度近似为 $O(b-a)$。

比如说以第一行第一列为上顶点，大小为4的三角形的最大值，就等于这4个红色的大小为2的三角形的最大值的最大值（可能有点绕）。


![](https://cdn.luogu.com.cn/upload/image_hosting/onb9eo6k.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以，这是一个空间复杂度为 $O(n^2\log_2n)$，时间复杂度近似为 $O(n^2k\log_2n)$ 的算法。然而它在空间和时间上都会爆炸！！！

因此，我们需要优化。
## 优化

首先观察转移方程，可以发现 $st_{k,i,j}$ 的值只由 $st_{k-1}$ 决定，如果对背包问题比较熟悉的话就可以想到用滚动数组，这样空间复杂度就会降到 $O(n^2)$，空间问题解决了。

至于时间问题，其实我们可以发现每次转移时都会调用一次 max_element 函数，而调用一次这个函数最长需要花费我们 $O(k)$ 的时间，这导致了我们的转移方程很慢。

然而其实调用 max_element 函数的本质是为了求区间的最大值，而这个区间不但是定长的（只与 $st_{k,i,j}$ 的 $k$ 有关），而且是向右不断滑动的。滑动区间求最值问题，用单调队列优化可以把 $O(k)$ 优化成 $O(1)$，这样总体时间复杂度就降到了 $O(n^2\log_2k)$。

## 代码
但是不知道是不是我用了STL容器 deque 来模拟单调队列的缘故（听说STL容器很慢），不开O2优化的话，第2组测试数据全TLE，然而开了O2优化的话，最慢的一组数据只需要567ms。代码如下：

```c
#include<bits/stdc++.h>
using namespace std;
int a[3002][3002] = { 0 }, st[3002][3002] = { 0 };
int main() {
	int n, K, maxk, ma, ju;
	long long ans = 0;
	deque<int>dui;//用双端队列模拟单调队列
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			scanf("%d", *(a + i) + j); st[i][j] = a[i][j];
		}
	}
	maxk = log2(K);
	for (int k = 1; k <= maxk; ++k) {
		ma = n - (1 << k) + 1; ju = 1 << k - 1;
		for (int i = 1; i <= ma; ++i) {
			for (int j = 1; j <= ju; ++j) {//初始化队列
				while (!dui.empty() && st[i + ju][dui.back()] < st[i + ju][j])dui.pop_back();
				dui.push_back(j);
			}
			for (int j = 1; j <= i; ++j) {
				while (!dui.empty() && st[i + ju][dui.back()] < st[i + ju][j + ju])dui.pop_back();
				while (!dui.empty() && dui.front() < j)dui.pop_front();
				dui.push_back(j + ju);
				st[i][j] = max(st[i][j], st[i + ju][dui.front()]);
			}
			dui.clear();//清空队列
		}
	}
	ma = n - K + 1;
	if (K == 1 << maxk) {
		for (int i = 1; i <= ma; ++i) {
			for (int j = 1; j <= i; ++j) {
				ans += st[i][j];
			}
		}
	}
	else {
		ju = 1 << maxk;
		for (int i = 1; i <= ma; ++i) {
			for (int j = 1; j <= K - ju; ++j) {
				while (!dui.empty() && st[i + K - ju][dui.back()] < st[i + K - ju][j])dui.pop_back();
				dui.push_back(j);
			}
			for (int j = 1; j <= i; ++j) {
				while (!dui.empty() && st[i + K - ju][dui.back()] < st[i + K - ju][j + K - ju])dui.pop_back();
				while (!dui.empty() && dui.front() < j)dui.pop_front();
				dui.push_back(j + K - ju);
				ans += max(st[i][j], st[i + K - ju][dui.front()]);
			}
			dui.clear();
		}
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：CYZZ (赞：9)

# [P6648](https://www.luogu.com.cn/problem/P6648)

简单易懂的 dp 的做法。
## 思路
首先想到把每个目标子三角形的最大值分别求出，然后统计和。

要在一个二维平面上维护最大值，直接用线段树这样的简单数据结构不好处理（其实我也只会这些了）。所以考虑 dp，也就是用小三角形的信息推出大三角形的信息。

对于一个边长为 $k$ 的三角形，我们要用小三角形把它覆盖。发现边长为 $\frac{k}{2}$ 的三角形比较好，可以先这样覆盖：

![](https://cdn.luogu.com.cn/upload/image_hosting/9uq1gnju.png)

但是你会发现中间有个倒着的三角形没被覆盖，于是你再用三个三角形覆盖它：

![](https://cdn.luogu.com.cn/upload/image_hosting/xpeqn1t6.png)

这样，我们就可以用六个小三角形盖住大三角形。发现这个过程类似倍增算法，可以在 $\mathcal{O(\log n)}$ 次转移内求出。

然后我们的状态就确定好了，$dp_{i,j,k}$ 表示以 $(i,j)$ 为顶点的边长为 $2^k$ 的三角形中的最大值。由于每次倍增只需要用到上次的信息，所以第三维可以滚掉。（转移方程有点长，大家可以自己手推一遍）

求答案的过程和上述过程类似，用边长为 $2^{\lfloor \log_2k\rfloor}$ 的三角形凑出：

![](https://cdn.luogu.com.cn/upload/image_hosting/v4halffl.png)

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,dp[3005][3005][2],len=1,now;
long long ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            scanf("%d",&dp[i][j][0]);
        }
    }
    while(len*2<m)
    {
        len*=2;
        for(int i=1;i+len-1<=n;i++)
        {
            for(int j=1;j<=i;j++)
            {
                dp[i][j][now^1]=max({//C++11神秘语法
                    dp[i][j][now],//六个点的坐标
                    dp[i+len/2][j][now],
                    dp[i+len/2][j+len/2][now],
                    dp[i+len/4][j][now],
                    dp[i+len/4][j+len/4][now],
                    dp[i+len/2][j+len/4][now]
                });
            }
        }
        now^=1;//滚动
    }
    for(int i=1;i+m-1<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            ans+=max({//同上
                dp[i][j][now],
                dp[i+m-len][j][now],
                dp[i+m-len][j+m-len][now],
                dp[i+(m-len)/2][j][now],
                dp[i+(m-len)/2][j+(m-len)/2][now],
                dp[i+m-len][j+(m-len)/2][now]
            });
        }
    }
    printf("%lld",ans);
}
```
究极压行版：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,dp[3005][3005][2],len=1,now;
long long ans;
int getans(int i,int j,int k){return max({dp[i][j][now],dp[i+k][j][now],dp[i+k][j+k][now],dp[i+k/2][j][now],dp[i+k/2][j+k/2][now],dp[i+k][j+k/2][now]});};
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            scanf("%d",&dp[i][j][0]);
    while(len*2<m)
    {
        for(int i=1;i+len-1<=n;i++)
            for(int j=1;j<=i;j++)
                dp[i][j][now^1]=getans(i,j,len);
        now^=1,len<<=1;
    }
    for(int i=1;i+m-1<=n;i++)
        for(int j=1;j<=i;j++)
            ans+=getans(i,j,m-len);
    printf("%lld",ans);
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：Danno0v0 (赞：8)

用正三角加倒三角递推的做法第一篇题解已经讲得很清楚了，这里发一个只用正三角做法。~~其实是因为不会推第一种的式子~~

~~焯和第二篇做法一样啊算了当补充吧~~

用 ```ST[i][j][p]``` 表示以 $(i,j)$ 作为三角形定点边长为 $2^p$ 的三角形中的最大值。

然后易得转移方程
$$
ST[i][j][p]=\max(ST[i][j][p-1],\max_{d=j}^{j+2^{p-1}}(ST[i+2^{p-1}][d][p-1]))
$$

实际上转移方程就是这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/8mmi8ank.png?x-oss-process=image)

建议手推一遍转移方程中的各项加深理解。~~实际上是因为推死我了不能让别人白嫖~~

然后 $p$ 倍增到小于 $k$ ，原理大概和倍增 LCA 防止跳过头一样。

查询的方程也可以很快搞出来：（假设 $p$ 是最大的满足 $2^p<k$ 的）

$$
Ans[i][j]=\max(ST[i][j][p],\max_{d=j}^{j+k-2^p}(ST[i+k-2^p][d][p]))
$$

~~依然建议手推一下~~

然后发现空间是 $O(n^2logn)$ 的，有点危险，滚动数组滚掉后面的 $logn$ 就好了。

时间是 $O(n^3)$ 的直接 T 飞（这上界是否过松）。

观察发现这一坨
$$
\max_{d=j}^{j+2^{p-1}}(ST[i+2^{p-1}][d][p-1])
$$
直接平添一个 $n$ ，考虑怎么加速。

再观察实际上我们求的是一个连续区间内的最大值，然后再观察我们发现对于第 $i$ 行的点后面的 $i+2^{p-1}$ 是相同的，所有的 $d$ 是第 $i+2^{p-1}$ 行的长度为 $2^{p-1}$ 的所有区间，要求这些区间的最大值，直接滑动窗口单调队列即可，可以消掉一个 $n$ ，查询时同理可以这样优化，时间复杂度为 $O(n^2)$ 。

code：
```cpp
//一道蓝题能调一上午rnmtq
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long ans;
int ST[3001][3001];
int que[1000001],l,r;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			cin>>ST[i][j];
	int p=2;
	for(;p<k;p*=2)
	{
		for(int x=1;x<=n-p+1;x++)
		{
			l=1,r=0;
			for(int i=1;i<=(p>>1);i++)
			{
				while(l<=r&&ST[x+(p>>1)][i]>=ST[x+(p>>1)][que[r]]) r--;
				que[++r]=i;
			}
			for(int y=1;y<=x;y++)
			{
				while(l<=r&&que[l]<y) l++;
				while(l<=r&&ST[x+(p>>1)][y+(p>>1)]>=ST[x+(p>>1)][que[r]]) r--;
				que[++r]=y+(p>>1);	
				ST[x][y]=max(ST[x][y],ST[x+(p>>1)][que[l]]); 
			}
		}
	}
	p>>=1;
	for(int x=1;x<=n-k+1;x++)
	{
		l=1,r=0;
		for(int i=1;i<=k-p;i++)
		{
			while(l<=r&&ST[x+k-p][i]>=ST[x+k-p][que[r]]) r--;
			que[++r]=i;
		}
		for(int y=1;y<=x;y++)
		{	
			while(l<=r&&que[l]<y) l++;
			while(l<=r&&ST[x+k-p][y+k-p]>=ST[x+k-p][que[r]]) r--;
			que[++r]=y+k-p;	
			ans+=max(ST[x][y],ST[x+k-p][que[l]]); 
		}
	}
	cout<<ans;				
} 
/*
6 4
3
2 1
4 5 7
2 4 3 6
9 8 4 7 2
1 5 3 7 9 5
*/
```

---

## 作者：OIerror (赞：3)

[传送门](https://www.luogu.com.cn/problem/P6648)

# 思路


------------
~~一开始以为是用单调队列，后来直接听取 WA 声一片……~~

## 预处理
这就是一个类似二维 RMQ 问题，只不过是在三角形上的。

和矩阵类似，我们设 $f_{x,y,t}$ 表示左上角为 $(x,y)$，边长为 $2^t$ 的三角形中的最大值。发现一个边长为 $2^t$ 的大三角形可以用六个边长为 $2^{t-1}$ 的小三角形覆盖。

如下图：

![图爆了 QWQ](https://cdn.luogu.com.cn/upload/image_hosting/4lw9hyzj.png)

可得转移方~~橙~~程：
		
$$f_{x,y,t}=\max(f_{x,y,t-1},f_{x+2^{t-2},y,t-1},f_{x+2^{t-1},y,t-1},f_{x+2^{t-1},y+2^{t-2},t-1},f_{x+2^{t-2},y+2^{t-2},t-1},f_{x+2^{t-1},y+2^{t-1},t-1})$$
代码：
```cpp
int p=log2(k);
for(int t=1; t<=p; t++)
{
	for(int i=1; i+(1<<t)-1<=n; i++)
	{
		for(int j=1; j<=i; j++)
		{
			f[i][j][t]=f[i][j][t-1];
			f[i][j][t]=max(f[i][j][t],f[i+(1<<(t-1))][j][t-1]);
			f[i][j][t]=max(f[i][j][t],f[i+(1<<(t-1))][j+(1<<(t-1))][t-1]);
			if(t>=2)
			{
				f[i][j][t]=max(f[i][j][t],f[i+(1<<(t-2))][j][t-1]);
				f[i][j][t]=max(f[i][j][t],f[i+(1<<(t-1))][j+(1<<(t-2))][t-1]);
				f[i][j][t]=max(f[i][j][t],f[i+(1<<(t-2))][j+(1<<(t-2))][t-1]);
			}
		}
	}
}
``````
## 询问
要询问每个边长为 $k$ 的三角形的最大值，我们可以枚举每个三角形的左上角，对每个左上角为 $(i,j)$ 的三角形进行查询。
```cpp
long long ans=0;//不开longlong见祖宗
for(int i=1;i<=n-k+1;i++)
{
	for(int j=1;j<=i;j++)
	{
		ans+=query(i,j);
	}
}
``````
所以现在的重点就是如何写这个 $\operatorname{query}$ 函数。

参照预处理的思路，我们令 $p=\log{k}$，容易发现边长为 $k$ 的三角形可以用六个边长为 $p$ 的三角形覆盖。

代码：
```cpp
int query(int x,int y)
{
	int p=log2(k);
	int ans;
	int l=x+k-1,r=y+k-1;
	ans=f[x][y][p];
	ans=max(ans,f[l-(1<<p)+1][y][p]);
	ans=max(ans,f[l-(1<<p)+1][r-(1<<p)+1][p]);
	if(k>=2)
	{
		int t=(k-(1<<p))/2;
		ans=max(ans,f[l-(1<<p)+1][y+t][p]);
		ans=max(ans,f[x+t][y][p]);
		ans=max(ans,f[x+t][y+t][p]);
	}
	return ans;
}
``````
# 细节
交上去，MLE，0 分(QWQ。

于是，我参照大佬的思路，把矩阵数组压缩成了三角形的一维数组。MLE，25 分。

两小时后，我发现 $f_{x,y,t}$ 只和 $f_{x,y,t-1}$ 有关。又两小时后，我终于把 ST 表滚动了起来（我真是个辣鸡……

终极代码（空间最优解！）：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int f[5000001];
int n,k;
int p;
int get(int i,int j)
{
	return i*(i+1)/2+j;
}
int query(int x,int y)
{
	int ans;
	int l=x+k-1,r=y+k-1;
	ans=f[get(x,y)];
	ans=max(ans,f[get(l-(1<<p)+1,y)]);
	ans=max(ans,f[get(l-(1<<p)+1,r-(1<<p)+1)]);
	if(k>=2)
	{
		int t=(k-(1<<p))/2;
		ans=max(ans,f[get(l-(1<<p)+1,y+t)]);
		ans=max(ans,f[get(x+t,y)]);
		ans=max(ans,f[get(x+t,y+t)]);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	p=log2(k);
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=i; j++)
		{
			scanf("%d",&f[get(i,j)]);
		}
	}
	for(int t=1; t<=p; t++)
	{
		for(int i=1; i+(1<<t)-1<=n; i++)
		{
			for(int j=1; j<=i; j++)
			{
				int cnt=get(i,j);
				int cur;
				cur=f[cnt];
				cur=max(cur,f[get(i+(1<<(t-1)),j)]);
				cur=max(cur,f[get(i+(1<<(t-1)),j+(1<<(t-1)))]);
				if(t>=2)
				{
					cur=max(cur,f[get(i+(1<<(t-2)),j)]);
					cur=max(cur,f[get(i+(1<<(t-1)),j+(1<<(t-2)))]);
					cur=max(cur,f[get(i+(1<<(t-2)),j+(1<<(t-2)))]);
				}
				f[cnt]=cur;
			}
		}
	}
	long long ans=0;
	for(int i=1;i<=n-k+1;i++)
	{
		for(int j=1;j<=i;j++)
		{
			ans+=query(i,j);
		}
	}
	printf("%lld",ans);
	return 0;
}
``````

---

## 作者：Lotus_Land (赞：3)


非常毒瘤的一题。

其实就是一个 ST 表，只不过这个 ST 表是二维的。用 $st[a][b][c]$ 表示以 $(a,b)$ 为顶点，边长为 $c$ 的三角形中的元素最大值。

重点是这个 ST 表怎么更新，怎么查询？

要查询的话，就要把边长为 $k$ 的三角形用若干个边长为 2 的整数次幂的三角形给覆盖住。以下的图是一种覆盖方式。（以边长为 14 的三角形为例，用边长为 8 的三角形覆盖住。）

为什么蓝色的三角形需要三个？因为这样覆盖一定能将大三角形完全覆盖住。如果只有一个蓝色三角形的话，就可能留下空隙。


![](https://cdn.luogu.com.cn/upload/image_hosting/dtb7r53h.png)


更新 ST 表的思路也差不多。把边长为 $2^i$ 的三角形用若干个边长为 $2^{i-1}$ 的整数次幂的三角形给覆盖住。

（以上说的的三角形都是顶角朝上的等边三角形，所以才需要这么多三角形。）

另外因为 $st[][][i]$ 的数值只与 $st[][i-1]$ 有关，所以要用滚动数组优化，不然会 MLE 得很惨。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,maxn,a[3005][3004],st[3005][3005][2];
long long ans;
int query(int x,int y) {
	int l=x+m-1,r=y+m-1;
	int k=maxn,len=(1<<k);
	int res=max({st[x][y][k&1],
	             st[l-len+1][y][k&1],
	             st[x+(m-len)/2][y][k&1],
	             st[l-len+1][r-len+1][k&1],
	             st[l-len+1][y+(m-len)/2][k&1],
	             st[x+(m-len)/2][y+(m-len)/2][k&1]
	            });
	return res;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=i; j++) {
			scanf("%d",&a[i][j]);
			st[i][j][0]=a[i][j];
		}
	}
	maxn=12;
	while((1<<maxn)>m)maxn--;
	for(int i=1; i<=maxn; i++) {
		for(int j=1; j+(1<<i)-1<=n; j++) {
			for(int k=1; k<=j; k++) {
				st[j][k][i&1]=max({st[j][k][i&1^1],
				                   st[j+(1<<(i-1))][k][i&1^1],
				                   st[j+(1<<(i-1))][k+(1<<(i-1))][i&1^1],
				                  });
				if(i>1){
					st[j][k][i&1]=max({st[j][k][i&1],
								   st[j+(1<<(i-1))][k+(1<<(i-2))][i&1^1],
				                   st[j+(1<<(i-2))][k][i&1^1],
				                   st[j+(1<<(i-2))][k+(1<<(i-2))][i&1^1]
				                  });
				}
			}
		}
	}
	for(int i=1; i<=n-m+1; i++) {
		for(int j=1; j<=i; j++) {
			ans+=query(i,j);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ThisIsLu (赞：3)

[题目](https://www.luogu.com.cn/problem/P6648)

提供一个奇怪但简单的做法。

首先，这题很明显枚举所有大小为 $k$ 的三角形，算出每个三角形的最大值加起来。

很明显，这速度太慢，于是就有了倍增方法。

你可以用六个三角形拼，或者正三角形和反三角形，但也可以用正方形和三角形。

设  $f(x,y,j,0/1)$ 表示以 $(x,y)$ 为左下顶点的大小为 $j$ 三角形/正方形。
![配图1](https://cdn.luogu.com.cn/upload/image_hosting/1q6q6hbx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
如图，有：

$$
\begin{aligned}
f(x,y,j,0)&=\max(f(x,y,\left\lceil\frac{j}{2}\right\rceil,         1),f(x,y+\left\lfloor\frac{j}{2}\right\rfloor,\left\lceil\frac{j}{2}\right\rceil,0),f(x-\left\lfloor\frac{j}{2}\right\rfloor,y,\left\lceil\frac{j}{2}\right\rceil,0))\\
f(x,y,j,1)&=\max(f(x,y,\left\lceil\frac{j}{2}\right\rceil,1),f(x,y+\left\lfloor\frac{j}{2}\right\rfloor,\left\lceil\frac{j}{2}\right\rceil,1),f(x-\left\lfloor\frac{j}{2}\right\rfloor,y,\left\lceil\frac{j}{2}\right\rceil,1),f(x-\left\lfloor\frac{j}{2}\right\rfloor,y+\left\lfloor\frac{j}{2}\right\rfloor,\left\lceil\frac{j}{2}\right\rceil,1))
\end{aligned}
$$

由于我们只需计算大小为 $k$ 的三角形，所以也只需计算 $k$，$\left\lceil \dfrac{k}{2} \right\rceil$，$\left\lceil \dfrac{\left\lceil \dfrac{k}{2} \right\rceil}{2} \right\rceil$……，$1$，把这些倒序存进数组 $s$ 计算。

因此可以改变一下状转：

$$
\begin{aligned}
f(x,y,j,0)&=\max(f(x,y,j-1,1),f(x,y+s_j-s_{j-1},j-1,0),f(x-s_j+s_{j-1},y,j-1,0))\\
f(x,y,j,1)&=\max(f(x,y,j-1,1),f(x,y+s_j-s_{j-1},j-1,1),f(x-s_j+s_{j-1},y,j-1,1),f(x-s_j+s_{j-1},y+s_j-s_{j-1},j-1,1))
\end{aligned}
$$

时间没问题了，但可惜出题人不止于此，想让你省点空间：

第一：惯用套路，由于只有一个三角形，不需要用二维存，改成一维的，写个函数 $go(x,y)=\dfrac{(x-1)x}{2}+y$，把刚才方程中 $(x,y)$改成 $go(x,y)$。

第二：滚动数组，枚举 $x$ 时从大到小，$y$从小到大。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int f[4501501][2];
int go(int x,int y){
	return (x-1)*x/2+y;
}
stack<int> s;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			scanf("%d",f[go(i,j)]);
			f[go(i,j)][1]=f[go(i,j)][0];
		}
	}
	while(k>1){
		s.push(k);
		k=(k+1)/2;
	}
	while(!s.empty()){
		int j=s.top();
		s.pop();
		int last=(j+1)/2;
		for(int x=n;x>=1;x--){
			for(int y=1;y<=x;y++){
				if(y+j-1<=x&&x-j+1>=1){
					f[go(x,y)][0]=max(max(f[go(x,y)][1],f[go(x,y+j-last)][0]),f[go(x-j+last,y)][0]);
				}
				else f[go(x,y)][0]=-1;
				if(y+j-1<=x-j+1){
					f[go(x,y)][1]=max(max(f[go(x,y)][1],f[go(x,y+j-last)][1]),max(f[go(x-j+last,y)][1],f[go(x-j+last,y+j-last)][1]));
				}
				else f[go(x,y)][1]=-1;
			}
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(f[go(i,j)][0]==-1) continue;
			ans+=f[go(i,j)][0];
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：yeshubo_qwq (赞：3)

图丑勿喷。

膜拜 a_grain 带领我搞懂此题。

考虑对于边长为 $x$ 的正着的三角形，如何转移到边长为 $2x$ 的正着的三角形。

以 $x=4$ 为例：

为了取到三个顶点，我们首先取三个正的着三角形（绿色）。

易发现，此时中间还剩下一个倒着的三角形，直接取一个倒着的三角形（红色），便可以覆盖剩余部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/2enmcale.png)

我们再来考虑倒着的三角形。

以刚刚的红色三角形为例：

先取三个倒的着三角形（绿色），再取一个正着的三角形（蓝色）即可。

（其实反着的三角形和正着的三角形是类似的）。

![](https://cdn.luogu.com.cn/upload/image_hosting/4kjndhgp.png)

边长为 $2x-1$ 的三角形的转移也是类似的。

因此，用倍增维护 $st_{x,i,j,0/1}$ （表示边长为 $x$，顶点为 $i,j$，$0/1$ 表示正着/倒着的三角形中几个数的最大值）即可。

代码咕了。

---

## 作者：rainygame (赞：0)

这里给一个简单且自然的做法。

看到静态范围最值，考虑倍增。设 $f_{i,j,k}$ 表示以 $(i,j)$ 为左上角边长为 $2^k$ 的等边三角形的最大值。考虑转移。

![](https://cdn.luogu.com.cn/upload/image_hosting/7rvda871.png)

观察上图可以发现如果设 $g_{i,j,k}$ 表示以 $(i,j)$ 为左上角边长为 $2^k$ 的菱形的最大值，那么转移方程为：

$$
f_{i,j,k} = \max\{f_{i,j,k-1},f_{i+2^{k-1},j+2^{k-1},k-1},g_{i+2^{k-1},j,k-1}\}
$$

可以发现在二维数组中 $g$ 实际在维护一个正方形，所以它的转移方程为：

$$
g_{i,j,k} = \max\{g_{i,j,k-1},g_{i+2^{k-1},j,k-1}, g_{i,j+2^{k-1},k-1},g_{i+2^{k-1},j+2^{k-1},k-1}\}
$$

对于查询，思路和一维 ST 是相同的——用两个很大的等边三角形合并答案。但是会发现中间可能还有一块菱形区域，直接用 $g$ 填上即可。（类似转移，只是可能会有重合部分）

这样就接近做完了，但是空限限制了只能使用约 $3$ 个 $n\times n$ 的数组。注意到 $m$ 是固定的，所以查询使用的等边三角形和菱形的边长分别是唯一的。使用滚动数组优化可以做到 $5$ 个 $n\times n$ 数组（因为菱形的长度可能比等边三角形小，所以需要 $n\times n$ 的空间），差一点点了！

观察转移方程，注意到 $f$ 和 $g$ 的转移方程都只使用了 $k-1$ 中**未被更新**的状态，所以根本不需要滚动数组，直接把 $k$ 那一维去掉即可，类似 01 背包。这样就完成了卡空间。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 3001

int n, m, lim, lim2;
int f[MAXN][MAXN], g[MAXN][MAXN], h[MAXN][MAXN];

int query2(int x, int y){
	int rx(x+m-(1<<lim)-1), ry(y+m-(1<<lim)-1);
	return max({h[x][y], h[rx-(1<<lim2)+1][y], h[x][ry-(1<<lim2)+1], h[rx-(1<<lim2)+1][ry-(1<<lim2)+1]});
}

int query(int x, int y){
	int rx(x+m-1), ry(y+m-1); if (m == (1<<lim)) return g[x][y];
	return max({g[x][y], g[rx-(1<<lim)+1][ry-(1<<lim)+1], query2(x+(1<<lim), y)});
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m; lim = __lg(m); lim2 = __lg(m-(1<<lim));
	for (int i(1); i<=n; ++i) for (int j(1); j<=i; ++j) cin >> f[i][j], g[i][j] = f[i][j];
	if (!lim2) memcpy(h, f, sizeof(f));
	for (int k(1); k<=lim; ++k){
		for (int i(1); i+(1<<k)-1<=n; ++i) for (int j(1); j+(1<<k)-1<=n && j<=i; ++j){
			f[i][j] = max({f[i][j], f[i+(1<<(k-1))][j], f[i][j+(1<<(k-1))], f[i+(1<<(k-1))][j+(1<<(k-1))]});
			g[i][j] = max({g[i][j], f[i+(1<<(k-1))][j], g[i+(1<<(k-1))][j+(1<<(k-1))]});
		}
		if (k == lim2) memcpy(h, f, sizeof(f));
	}
	long long ans(0); for (int i(1); i+m-1<=n; ++i) for (int j(1); j<=i; ++j) ans += query(i, j); cout << ans;

	return 0;
}
```

---

## 作者：ZDQ2011 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P6648)
### 问题描述
- 有一个大小为 $n$ 的等边三角形，第 $i$ 行包含 $i$ 个数字。对于这个等边三角形，求对于每个大小为 $k$ 的子三角形内数字最大值的和。
- 数据范围：$1 \leq k < n \leq 3 \times 10 ^ 3$。
--------
### 解题思路
- 我们需要对每个边长为 $k$ 的子三角形快速求出其最大值。
- 明显的 $DP$ 的方法。根据数据范围 $3000$，推测 $DP$ 的状态可能是二维或者三维。
- 状态定义：$dp[i][j][p]$ 表示以 $(i, j)$ 为顶点，边长为 $p$ 的三角形的数字中的最大值。时间复杂度 $O(n ^ 3)$，空间复杂度 $n ^ 3$。
- 优化：数据范围 $3000$ 会TLE，考虑用倍增的方法优化。倍增枚举 $p$，此时的状态定义变为 $dp[i][j][p]$ 表示以 $(i, j)$ 为顶点，边长为 $2 ^ p$ 的等边三角形的数字中的最大值。此时的时间和空间复杂度均为 $n ^ 2 log(n)$。
- 转移方程：枚举到当前 $(i, j, p)$，状态转移就是把三角形分成上下两半，上面一个边长为 $2 ^ {p - 1}$ 的三角形，下面 $2 ^ {p - 1} + 1$ 个边长为 $2 ^ {p - 1}$ 的三角形，从中求出最大值。
- 状态转移可以用滑动窗口优化，时间复杂度均摊为 $O(1)$。
- 统计答案：要求的边长为 $k$，我们找一个最大的满足 $2 ^ p \leq k$ 的 $p$，然后将整个边长为 $k$ 的三角形分成上面一个边长为 $k$，下面若干个边长为 $k$，那么统计答案和状态转移也是类似的。

---

