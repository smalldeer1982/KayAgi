# Coins

## 题目描述

设 $N$ 是一个正的奇数。

有 $N$ 枚硬币，每枚硬币上标有编号 $1, 2, \ldots, N$。对于每个 $i$ ($1 \leq i \leq N$)，掷硬币 $i$ 时，正面朝上的概率是 $p _ i$，反面朝上的概率是 $1 - p _ i$。

太郎君把这 $N$ 枚硬币全部投掷了一次。请计算正面朝上的硬币数多于反面朝上的硬币数的概率。

## 样例 #1

### 输入

```
3
0.30 0.60 0.80```

### 输出

```
0.612```

## 样例 #2

### 输入

```
1
0.50```

### 输出

```
0.5```

## 样例 #3

### 输入

```
5
0.42 0.01 0.42 0.99 0.42```

### 输出

```
0.3821815872```

# 题解

## 作者：Haphyxlos (赞：23)

# AT4530 【Coins】
[题目传送门](https://www.luogu.com.cn/problem/AT4530)

这题很简单，设$dp[i][j]$表示前$i$个元素有$j$个向上的概率。只需要枚举当 前硬币是向上还是向下即可，与背包类似。

转移方程为：
$f[i][j]=f[i−1][j−1] \times p_i + f[i−1][j] \times (1−p_i) $

计算完毕后，枚举有多少枚硬币向上就做完了。

本题ACcode如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=3005;
const int maxm=1e6+5;
int n;
double a[maxn],f[maxn][maxn],ans;
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%lf",&a[i]); 
	}
	f[0][0]=1;
	for(int i=1;i<=n;++i){
		f[i][0]=f[i-1][0]*(1-a[i]);
		for(int j=1;j<=i;++j){
			f[i][j]=f[i-1][j-1]*a[i]+f[i-1][j]*(1-a[i]);
		}
	}
	for(int i=0;i<=n;++i){
		if(i>n-i){
			ans+=f[n][i];
		}
	}
	printf("%.10f",ans);
	return 0;
}
```
本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：CrTsIr400 (赞：9)

最优渐进复杂度做法，$O(n\log^2 n)$。

## [AT_dp_i Coins](https://www.luogu.com.cn/problem/AT_dp_i)

题意：

给你 $n$ 个硬币（$n$ 为奇数），每个硬币有 $p_i$ 的概率是正面，$(1-p_i)$ 的概率是反面。

求最后正面比反面**多**的概率，$n\le 2999$。

正解思路：

考虑一个很暴力的做法，设 $f[i]$ 为当前时间点 $t$ 有 $i$ 个硬币是正面的概率，则原址更新（倒着来），$f[i]=f[i-1]p_t+f[i](1-p_t)$。 

这个思路很简单。是 $O(n^2)$ 时间复杂度的，$O(n)$ 空间复杂度的，足以通过此题。（代码就不贴了，很短也很简单）

---

但是考虑还能不能更快。

这相当于 $n$ 个一次二项式（形如 $p_tx+(1-p_t)$）相乘，求乘积，最后算答案。

这里讲一下分治 FFT。

假设我要求出区间 $[l,r]$ 的所有多项式乘积，那么我把区间 $[l,mid]$ 和区间 $[mid+1,r]$ 的多项式乘积乘起来，即为答案。

考虑时间复杂度。因为每个坐标上只有一个一次二项式，所以这段区间的乘积多项式次数是 $O(r-l)$ 级别的。

每次我需要一个 $O((r-l)\log_2 (r-l))$ 的 FFT 运算来把两个多项式乘起来。

所以根据主定理，$T(n)=2T(\lfloor\dfrac{n}{2}\rfloor)+n\log n=O(n\log^2 n)$。

所以这题就真正做完了。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(auto i(a),_ei(b);i<=_ei;++i)
#define gch(w) for(;w(CH);CH=getchar())
using I=int;using V=void;using namespace std;
using DB=long double;
I n;const I N=3000;
using poly=vector<DB>;
poly a[N];
#define cs const
cs I NMax=8192;
struct fus{
	DB x,y;fus(cs DB _x=0,cs DB _y=0){x=_x;y=_y;}
	fus operator +(cs fus&a)cs&{return fus(x+a.x,y+a.y);}
	fus operator -(cs fus&a)cs&{return fus(x-a.x,y-a.y);}
	fus operator *(cs fus&a)cs&{return fus(x*a.x-y*a.y,x*a.y+y*a.x);}}
aa[NMax],bb[NMax];
I tr[NMax];
const DB PI=acos(-1);
V FFT(fus*a,I n,I op){
	fo(i,0,n-1)if(i<tr[i])swap(a[i],a[tr[i]]);//蝴蝶变换
	for(I len=2,hf=1;len<=n;len<<=1,hf<<=1){
		fus w(cos(2*PI/len),sin(2*PI/len)*op);
		for(fus*i=a;i<a+n;i+=len){
			for(fus bas(1,0),*j=i,*k=i+hf;k<i+len;++j,++k,bas=bas*w){
				fus num=*k*bas;
				*k=*j-num;
				*j=*j+num;}}}
	if(op==-1)fo(i,0,n-1)a[i].x/=n;}
poly convolution(poly a,poly b){
	poly c;c.resize(a.size()+b.size()-1);
	I n(1);for(;n<c.size();n<<=1);
	fo(i,1,n-1)tr[i]=tr[i>>1]>>1|(i&1?n>>1:0);
	fo(i,0,(I)a.size()-1)aa[i]=fus(a[i],0);
	fo(i,0,(I)b.size()-1)bb[i]=fus(b[i],0);
	FFT(aa,n,1);FFT(bb,n,1);
	fo(i,0,n)aa[i]=aa[i]*bb[i];
	FFT(aa,n,-1);
	fo(i,0,(I)c.size()-1)c[i]=aa[i].x;
	fo(i,0,n-1)aa[i]=bb[i]=fus(0,0);
	return c;
}
poly fzfft(I l,I r){
	if(l==r)return a[l];
	I mid=l+r>>1;
	return convolution(fzfft(l,mid),fzfft(mid+1,r));}
I main(){scanf("%d",&n);
	fo(i,1,n){a[i].resize(2);
		scanf("%Lf",&a[i][1]);
		a[i][0]=1-a[i][1];}
	poly ans=fzfft(1,n);DB anss(0);
	for(I i=(n+1)/2;i<ans.size();++i)anss+=ans[i];
	printf("%.11Lf\n",anss);
	return 0;
}
```

---

## 作者：MattL (赞：6)

[洛谷题目链接](https://www.luogu.com.cn/problem/AT4530)和[原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/4530)

---
**分析：**

一道很容易练手的~~简单~~动规题。

---
**动规：**

一级动规：通俗易懂

数组： $f[i][o]$ 表示前 $i$ 个硬币有 $o$ 个正面朝上的概率。

转移方程：枚举是不是正面即可
$$f[i][o]=f[i-1][o-1]\times a[i]+f[i-1][o]\times  (1-a[i])$$

注意事项 ~~我卡了一会儿的~~：要初始化 $f[0][0]=1$ ，$f[i][0]=f[i-1][0]\times (1-a[i])$

---
二级动规：压维

**压维原因：** 凡是看见等号左边是 $[i]$ 的，右边全是 $[i-1]$ 的，就可以压维。

数组： $f[o]$ 表示循环到现在这个时刻有 $o$ 个正面朝上的硬币的概率。

转移方程：~~是不是短小精湛呢？~~
$$f[o]=f[o-1]\times a[i]+f[o]\times (1-a[i])$$

注意事项~~我卡了很久的~~：要逆推、 $f[0]=f[0]\times (1-a[i])$ 要放在第二重循环后。

---
~~码风奇怪，敬请谅解~~

请把 $o$ 看成 $j$ 

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double a[3333],f[3333],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int o=i;o>=1;o--)
			f[o]=f[o]*(1-a[i])+f[o-1]*a[i];
		f[0]=f[0]*(1-a[i]);
	}
	for(int i=n/2+1;i<=n;i++)
		ans+=f[i];
	printf("%.10f\n",ans);
	return 0;
}
```


---

## 作者：Lates (赞：5)

设 $f[i][j]$ 表示 $1$ 到 $i$ 中，有 $j$ 个正面朝上的概率。

那么当第 $i$ 个

- 正面朝上：$f[i][j]=p[i]\times f[i-1][j-1]$

- 反面朝上：$f[i][j]=(1-p[i])\times f[i-1][j]$

所以就是这两种情况加起来。

$f[i][j]=p[i]\times f[i-1][j-1]+(1-p[i])\times f[i-1][j]$。

最终要求 正面朝上比反面朝上多。假设正面朝上的有 $i$ 个，那么反面的有 $n-i$ 个。那么答案应该为 $\sum\limits_{i>n-i}f[n][i]$。






---

## 作者：云浅知处 (赞：1)

用 $F(i,j)$ 表示「前 $i$ 枚硬币恰有 $j$ 枚正面朝上」的概率，那么最终的答案就是

$$
\sum_{i=\lceil n/2\rceil}^nF(n,i)
$$

转移时考虑枚举最后一枚硬币是正面朝上还是反面朝上，我们得到了转移方程：

$$
F(i,j)=p_i\cdot F(i-1,j-1)+(1-p_i)\cdot F(i-1,j)
$$

于是就得到了一个 $O(n^2)$ 的算法。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<iomanip>

#define int long long
const int MN=3005;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int n;
double dp[MN][MN],p[MN],mul[MN];

signed main(void){

    cin>>n;
    mul[0]=1.000000;
    for(int i=1;i<=n;i++)cin>>p[i],mul[i]=mul[i-1]*(1-p[i]);
    dp[0][0]=1.000000,dp[0][1]=0.000000;
    for(int i=1;i<=n;i++){
        dp[i][0]=mul[i];
        for(int j=1;j<=i;j++)dp[i][j]=p[i]*dp[i-1][j-1]+(1-p[i])*dp[i-1][j];
    }
    double ans=0.00000;
    for(int i=(int)(n/2);i>=0;i--)ans+=dp[n][n-i];
    cout<<fixed<<setprecision(10)<<ans<<endl;

    return 0;
}
```

---

## 作者：Phartial (赞：1)

由于直接计算正面数比反面数多的概率较为复杂，考虑简化状态。设 $f_{i,j}$ 表示前 $i$ 个硬币扔出 $j$ 个正面的概率，分类讨论如下：

- 若第 $i$ 个硬币抛出的是正面，则总共抛出 $j$ 个正面的概率是 $f_{i-1,j-1}$。

- 若第 $i$ 个硬币抛出的是反面，则总共抛出 $j$ 个正面的概率是 $f_{i-1,j}$。

综合以上条件即可推出转移方程为：

$$ f_{i,j}=f_{i-1,j-1}\times p_i+f_{i-1,j}\times(1-p_i) $$

最后枚举正面数量统计答案即可。

```cpp
#include <iomanip>
#include <iostream>

using namespace std;

const int kN = 3000;

int n;
double p[kN], f[kN][kN], s;

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  f[1][0] = 1 - p[1], f[1][1] = p[1];  // 边界初始化
  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      f[i][j] = (j ? f[i - 1][j - 1] * p[i] : 0) + f[i - 1][j] * (1 - p[i]);  // 转移方程，记得判边界
      if (i == n && j > i - j) {
        s += f[i][j];  // 统计答案
      }
    }
  }
  cout << fixed << setprecision(10) << (n == 1 ? p[1] : s);  // 特判n=1的情况
  return 0;
}
```


---

## 作者：SIXIANG32 (赞：0)

一道 dp 题。  
闲话少说，切入正题——  

---
“正面朝上的硬币比反面朝上的多”这个约束条件不好维护，我们来个简单的，$f_{i, j}$ 表示前 $i$ 个硬币中有 $j$ 个正面朝上（也就是说 $i - j$ 个反面朝上）的概率。这样就比较方便转移了。  

方程还是比较容易推出来的，分讨嘛，如果第 $i$ 个是正面概率有 $f_{i - 1, j - 1} \times p_i$，如果是反面有概率 $f_{i - 1, j}\times (1 - p_i)$

边界条件 $f_{0, 0} = 1$（没有硬币没有正面朝上的硬币概率必然为百分百啦），$f_{i, 0} = f_{i - 1, 0} \times(1 - p_i)$，计算前 $i$ 个全朝下的概率。

最后注意保留 $10$ 位小数保证精度！

代码：  

```cpp
#include <iostream>
#include <iomanip>
#define MAXN 2999
#define fs fixed << setprecision(10)
#define QWQ cout << "QWQ" << endl;
using namespace std;
double P[MAXN + 10], f[MAXN + 10][MAXN + 10];
int main() {
	f[0][0] = 1;
	double qAq = 0;
	int n; cin >> n;
	for(int p = 1; p <= n; p++) cin >> P[p];
	for(int p = 1; p <= n; p++) {
		f[p][0] = f[p - 1][0] * (1 - P[p]);
		for(int i = 1; i <= p; i++)
			f[p][i] = f[p - 1][i - 1] * P[p] + f[p - 1][i] * (1 - P[p]);
	}
	for(int p = 1; p <= n; p++)
		if(n - p < p)
			qAq += f[n][p];
	cout << fs << qAq << endl;
}
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4530) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_i)

>有$n(n\bmod2=1)$枚硬币，若扔第$i$枚，则有$a_i$的概率正面朝上，有$1-a_i$的概率反面朝上。求扔完所有硬币后，正面朝上的硬币比反面朝上的硬币多的概率。

>$n\in[1,2999]$。

设$dp_{i,j}$表示扔完前$i$个硬币后，正面朝上的硬币恰好有$j$个的概率。边界是$dp_{0,0}=1$，所有不合法状态DP值为$0$，目标是$\sum\limits_{i=\left\lceil\frac n2\right\rceil}^ndp_{n,i}$，状态转移方程是$dp_{i,j}=(1-a_i)dp_{i-1,j}+a_idp_{i-1,j-1}$（枚举该硬币是正面还是反面朝上）。时间复杂度$\mathrm O\!\left(n^2\right)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2999;
int n;
double a[N+1];
double dp[N+1][N+1];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[0][0]=1;//边界 
	for(int i=1;i<=n;i++)for(int j=0;j<=i;j++){//转移 
		dp[i][j]=(1-a[i])*dp[i-1][j];
		if(j)dp[i][j]+=a[i]*dp[i-1][j-1];
	}
	double ans=0;
	for(int i=n/2+1;i<=n;i++)ans+=dp[n][i];//目标 
	printf("%.100lf",ans);
	return 0;
}
```

---

