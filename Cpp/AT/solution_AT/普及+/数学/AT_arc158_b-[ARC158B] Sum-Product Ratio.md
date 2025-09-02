# [ARC158B] Sum-Product Ratio

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc158/tasks/arc158_b

$ 0 $ でない整数 $ x_1,\ \ldots,\ x_N $ が与えられます．$ i,j,k $ を $ 1\leq\ i\ <\ j\ <\ k\leq\ N $ を満たす整数とするとき，$ \dfrac{x_i+x_j+x_k}{x_ix_jx_k} $ としてありうる最小値と最大値を求めてください．

## 说明/提示

### 制約

- $ 3\leq\ N\leq\ 2\times\ 10^5 $
- $ -10^6\leq\ x_i\ \leq\ 10^6 $
- $ x_i\neq\ 0 $
 
### Sample Explanation 1

$ \dfrac{x_i+x_j+x_k}{x_ix_jx_k} $ としてありうる値は次の $ 4 $ 通りです． - $ (i,j,k)\ =\ (1,2,3) $：$ \dfrac{(-2)\ +\ (-4)\ +\ 4}{(-2)\cdot\ (-4)\cdot\ 4}\ =\ -\dfrac{1}{16} $． - $ (i,j,k)\ =\ (1,2,4) $：$ \dfrac{(-2)\ +\ (-4)\ +\ 5}{(-2)\cdot\ (-4)\cdot\ 5}\ =\ -\dfrac{1}{40} $． - $ (i,j,k)\ =\ (1,3,4) $：$ \dfrac{(-2)\ +\ 4\ +\ 5}{(-2)\cdot\ 4\cdot\ 5}\ =\ -\dfrac{7}{40} $． - $ (i,j,k)\ =\ (2,3,4) $：$ \dfrac{(-4)\ +\ 4\ +\ 5}{(-4)\cdot\ 4\cdot\ 5}\ =\ -\dfrac{1}{16} $． これらの最小値は $ -\dfrac{7}{40} $，最大値は $ -\dfrac{1}{40} $ です．

## 样例 #1

### 输入

```
4
-2 -4 4 5```

### 输出

```
-0.175000000000000
-0.025000000000000```

## 样例 #2

### 输入

```
4
1 1 1 1```

### 输出

```
3.000000000000000
3.000000000000000```

## 样例 #3

### 输入

```
5
1 2 3 4 5```

### 输出

```
0.200000000000000
1.000000000000000```

# 题解

## 作者：_•́へ•́╬_ (赞：5)

## 思路

我们充分发扬人类智慧：

先把所有数排个序。

根据数学直觉，我们取到的值肯定比较“极”，要么极大极小，要么极靠近零。

所以我们只取酱紫的 12 个数来计算答案。

这样速度快得飞起，在 $n=200000$ 时都可以在 25ms 内艹过。

（其实可以分讨，但是容易少情况，赛时挨罚了）

## code

```cpp
#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	bool t=0;char c=nc();for(;c<'0'||'9'<c;t|=c=='-',c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());if(t)x=-x;
}
int n,x[200009];double minn(1e12),maxn(-1e12);vector<int>a;
inline void upd(const double&x){minn=min(minn,x);maxn=max(maxn,x);}
inline void upd(const int&i,const int&j,const int&k)
	{upd((double)(i+j+k)/i/j/k);}
main()
{
	read(n);for(int i=0;i<n;read(x[i++]));sort(x,x+n);
	int i=lower_bound(x,x+n,0)-x;
	if(i<=6)for(int j=0;j<i;a.emplace_back(x[j++]));
	else a.emplace_back(x[0]),a.emplace_back(x[1]),a.emplace_back(x[2]),
		a.emplace_back(x[i-3]),a.emplace_back(x[i-2]),a.emplace_back(x[i-1]);
	if(n-i<=6)for(int j=i;j<n;a.emplace_back(x[j++]));
	else a.emplace_back(x[i]),a.emplace_back(x[i+1]),a.emplace_back(x[i+2]),
		a.emplace_back(x[n-3]),a.emplace_back(x[n-2]),a.emplace_back(x[n-1]);
	for(int i=0;i<a.size();++i)for(int j=i+1;j<a.size();++j)
		for(int k=j+1;k<a.size();++k)upd(a[i],a[j],a[k]);
	printf("%.16lf\n%.16lf",minn,maxn);
}
```



---

## 作者：sanaka87 (赞：4)

发现没人和我一个做法，来水个题解。

对式子变形：

$$\frac 1{x_ix_j}+\frac 1{x_ix_k}+\frac 1{x_kx_j}=(\frac 1{x_j}+\frac 1{x_i})(\frac 1{x_j}+\frac 1{x_k})-(\frac{1}{x_j})^2$$

枚举中间的 $j$，然后分别维护前后缀的最大最小值，四个两两相乘取 $\max/\min$ 即可。时间复杂度 $O(n)$。

（写完还以为我是标算）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define gc getchar
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=gc();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=gc();}
	while (isdigit(ch)){x=x*10ll+ch-'0';ch=gc();}
	return x*f;
}
int n,m;
ll a[1010101];
double pmi[1010101],pma[1010101],smi[1010101],sma[1010101];
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	smi[n+1]=pmi[0]=1e10;
	sma[n+1]=pma[0]=-1e10;
	for (int i=1;i<=n;i++){
		pmi[i]=fmin(pmi[i-1],1./a[i]);
		pma[i]=fmax(pma[i-1],1./a[i]);
	}
	for (int i=n;i;i--){
		smi[i]=fmin(smi[i+1],1./a[i]);
		sma[i]=fmax(sma[i+1],1./a[i]);
	}
	double MI=1e10,MA=-1e10;
	for (int i=2;i<n;i++){
		double A=(smi[i+1]+1./a[i])*(pmi[i-1]+1./a[i]);
		double B=(sma[i+1]+1./a[i])*(pmi[i-1]+1./a[i]);
		double C=(smi[i+1]+1./a[i])*(pma[i-1]+1./a[i]);
		double D=(sma[i+1]+1./a[i])*(pma[i-1]+1./a[i]);
		MI=fmin(MI,fmin(fmin(A,B),fmin(C,D))-1./(a[i]*a[i]));
		MA=fmax(MA,fmax(fmax(A,B),fmax(C,D))-1./(a[i]*a[i]));
	}
	printf("%.14lf\n%.14lf\n",MI,MA);
	return 0;
}


```


---

## 作者：iiiiiyang (赞：3)

[这篇博客摘要好有意思](https://www.cnblogs.com/LittleTwoawa/p/17211385.html)

[题目链接](https://www.luogu.com.cn/problem/AT_arc158_b)

先化一下：
$$
\mathcal F(x_i,x_j,x_k) = \frac{x_i + x_j + x_k}{x_i x_j x_k} = \frac{1}{x_i x_j} + \frac{1}{x_i x_k} + \frac{1}{x_j x_k}
$$

记 $t = \frac{1}{x}$，$\mathcal G$ 是关于 $t$ 的函数，为 $\mathcal G(t_i,t_j,t_k) = t_i t_j + t_i t_k + t_j t_k$，有：
$$
\mathcal G(t_i,t_j,t_k) = \mathcal F(x_i,x_j,x_k) = (t_i + t_j) t_k + t_i t_j
$$

容易得到当固定 $t_i$ 和 $t_j$ 的时候，$\mathcal g$ 是关于 $t_k$ 的一次函数。所以如果想要得到答案，$t_k$ 的取值必然是所有数去掉 $t_i$ 和 $t_j$ 后取最大值和最小值。

类似的我们就可以得到 $t_i$ 和 $t_j$ 也一定要取极值。综上我们将 $x$ 按照 $\frac{1}{x}$ 的大小排序，取三个最大值和三个最小值，设他们从大到小依次分别为 $a_1,a_2,a_3$ 和 $b_1,b_2,b_3$，最后的答案一定在 $\mathcal F(a_1,a_2,a_3)$，$\mathcal F(a_1,a_2,b_3)$，$\mathcal F(a_1,b_2,b_3)$，$\mathcal F(b_1,b_2,b_3)$ 中。复杂度瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
namespace LgxTpre
{
	static const int MAX=200010;
	static const int INF=4557430888798830399;
	static const double inf=2147483647.0;
	static const int mod=998244353;
	
	int n,x;
	double num[MAX];
	double maxx,minx;
	
	inline double func(double a,double b,double c) {return (a+b+c)/(a*b*c);}
	inline void cmin(double &a,double b) {a=a<b?a:b;}
	inline void cmax(double &a,double b) {a=a>b?a:b;}
	
	inline void lmy_forever()
	{
		cin>>n;
		for(int i=1;i<=n;++i) cin>>num[i];
		sort(num+1,num+1+n,[](double x,double y)
		{
			return 1/x<1/y;
		});
		minx=inf,maxx=-inf;
		cmin(minx,func(num[1],num[2],num[3])),cmin(minx,func(num[1],num[2],num[n])),
		cmin(minx,func(num[1],num[n-1],num[n])),cmin(minx,func(num[n-2],num[n-1],num[n]));
		cmax(maxx,func(num[1],num[2],num[3])),cmax(maxx,func(num[1],num[2],num[n])),
		cmax(maxx,func(num[1],num[n-1],num[n])),cmax(maxx,func(num[n-2],num[n-1],num[n]));
		cout<<fixed<<setprecision(15)<<minx<<endl;
		cout<<fixed<<setprecision(15)<<maxx<<endl;
		return;
	}
}
 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	LgxTpre::lmy_forever();
	return (0-0);
}
```

---

## 作者：Leasier (赞：0)

**缩小范围**：考虑现在已知 $x_i, x_j$，我们希望知道怎样的 $x_k$ 可以成为一个较优的解。

考虑将原式改写为 $\frac{\frac{1}{x_i} + \frac{1}{x_j}}{x_k} + \frac{1}{x_i x_j}$，则随着 $\frac{1}{x_i} + \frac{1}{x_j}$ 的变化，$x_k$ 可能会取到正 / 负数中绝对值最小 / 大且还可以选的值。

将该结论推而广之，我们会发现：

- $x_i, x_j, x_k$ 只会在正 / 负数中绝对值最小 / 大的 $3$ 个值中产生（因为你最多可能三个数全正 / 负）。

于是我们把这 $\leq 12$ 个值抓出来求 $\min/\max$ 即可。时间复杂度为 $O(n)$。~~不过我偷懒写了个 $O(n \log n)$ 的排序（~~

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int x[200007], pos[17];

inline double calc(int i, int j, int k){
	return 1.0 * (i + j + k) / i / j / k;
}

int main(){
	int n, m = 0, up1, up2, k = 0;
	double ans1 = 1e9, ans2 = -1e9;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> x[i];
	}
	sort(x + 1, x + n + 1);
	while (m < n && x[m + 1] < 0) m++;
	up1 = min(m, 3);
	for (int i = 1; i <= up1; i++){
		pos[++k] = i;
		pos[++k] = m - i + 1;
	}
	up2 = min(n - m, 3);
	for (int i = 1; i <= up2; i++){
		pos[++k] = i + m;
		pos[++k] = n - i + 1;
	}
	for (int i = 1; i <= k; i++){
		for (int j = i + 1; j <= k; j++){
			if (pos[i] != pos[j]){
				for (int y = j + 1; y <= k; y++){
					if (pos[i] != pos[y] && pos[j] != pos[y]){
						double val = calc(x[pos[i]], x[pos[j]], x[pos[y]]);
						if (ans1 > val) ans1 = val;
						if (ans2 < val) ans2 = val;
					}
				}
			}
		}
	}
	printf("%.15lf\n", ans1);
	printf("%.15lf", ans2);
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

我们发现，答案的大小只与以下两个因素有关：

- 答案的正负性
- 答案的绝对值

因此我们得出结论：$x_i,x_j,x_k$ 只会取到负数的前三大、负数的前三小、正数的前三大、正数的前三小。于是直接排完序找到这些数之后暴力枚举就行。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
double x[200005];
vector<double> a;
bool cmp(double a,double b){
	return a>b;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf",&x[i]);
	double mx=-1e15,mn=1e15;
	sort(x+1,x+n+1);
	int id=0;
	for(int i=1;i<n;i++)
		if(x[i]*x[i+1]<0){
			id=i;
			break;
		}
	if(!id){
		a.push_back(x[1]);
		a.push_back(x[2]);
		a.push_back(x[3]);
		if(n>3) a.push_back(x[n]);
		if(n-1>3) a.push_back(x[n-1]);
		if(n-2>3) a.push_back(x[n-2]);
	}
	else{
		a.push_back(x[1]);
		a.push_back(x[2]);
		a.push_back(x[3]);
		if(id>3) a.push_back(x[id]);
		if(id-1>3) a.push_back(x[id-1]);
		if(id-2>3) a.push_back(x[id-2]);
		if(id+1<=n&&id+1>3) a.push_back(x[id+1]);
		if(id+2<=n&&id+2>3) a.push_back(x[id+2]);
		if(id+3<=n&&id+3>3) a.push_back(x[id+3]);
		if(id+3<n) a.push_back(x[n]);
		if(id+3<n-1) a.push_back(x[n-1]);
		if(id+3<n-2) a.push_back(x[n-2]);
	}
	int lst=a.size()-1;
	for(int i=0;i<=lst;i++)
		for(int j=0;j<=lst;j++)
			for(int k=0;k<=lst;k++){
				if(i==j||j==k||i==k) continue;
				mx=max((a[i]+a[j]+a[k])/(a[i]*a[j]*a[k]),mx);
				mn=min((a[i]+a[j]+a[k])/(a[i]*a[j]*a[k]),mn);
			}
	printf("%.15lf\n%.15lf",mn,mx);
	return 0;
}
```


---

## 作者：FastingRabble (赞：0)

题目题面和题意都十分简单。

首先，不难想到，求最大和最小值，那么大概率是取极值。

所以，尝试取出
- 负数中最小的三个，最大的三个。
- 正数中最小的三个，最大的三个。

这时枚举的数据量已经很小了。再暴力枚举即可。

参考代码：(~~赛时丑陋的代码~~)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define open(x) freopen(x ".in", "r", stdin);freopen(x ".out", "w", stdout);
#define db double
inline int read(){int f=1;int x=0;char c=getchar();while(c<'0'||c>'9'){if(c=='-'){f=-f;}c=getchar();}while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}return x*f;}
inline void wr(int x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

int T;
int n;
db a[1000050];
db f[1000050];
db z[1000050];

inline void ok(){
	cin >> n; 
	int cnt1 = 0;
	int cnt2 = 0;
	for(int i = 1 ; i <= n ;++i){
		cin >> a[i];
		if(a[i] < 0) f[++cnt1] = a[i];
		else z[++cnt2] = a[i];
	} 
	db ans = -1e9 - 7;
	db minans = 1e9 + 7;  
	sort(f + 1 , f + cnt1 + 1);           
	sort(z + 1 , z + cnt2 + 1 , greater<int>());
	if(cnt1 >= 3)ans = max({ans, (f[1] + f[2] + f[3]) / (f[1] * f[2] * f[3]) , (f[cnt1] + f[cnt1 - 1] + f[cnt1 - 2]) / (f[cnt1] * f[cnt1 - 1] * f[cnt1 -2])});
	if(cnt2 >= 1 && cnt1 >= 2) ans = max({ans , (z[1] + f[1] + f[2]) / (z[1] * f[1] * f[2]) , (z[1] + f[cnt1] + f[cnt1 - 1]) / (z[1] * f[cnt1] * f[cnt1-1]) , (z[cnt2] + f[1] + f[2]) / (z[cnt2] * f[1] * f[2]) , (z[cnt2] + f[cnt1] + f[cnt1 - 1]) / (z[cnt2] * f[cnt1] * f[cnt1-1])});
	if(cnt2 >= 2 && cnt1 >= 1) ans = max({ans , (z[cnt2] + z[cnt2 - 1] + f[1]) / (z[cnt2] * z[cnt2 - 1] * f[1]) , (z[cnt2] + z[cnt2 - 1] + f[cnt1]) / (z[cnt2] * z[cnt2 - 1] * f[cnt1]) , (z[1] + z[2] + f[1]) / (z[1] * z[2] * f[1]) , (z[1] + z[2] + f[cnt1]) / (z[1] * z[2] * f[cnt1])}); 
	if(cnt2 >= 3) ans = max({ans , (z[cnt2] + z[cnt2 - 1] + z[cnt2 - 2]) / (z[cnt2 - 1] * z[cnt2] * z[cnt2 - 2]) , (z[1] + z[2] + z[3]) / (z[1] * z[2] * z[3])});
	
	if(cnt2 >= 3)minans = min({minans, (z[1] + z[2] + z[3]) / (z[1] * z[2] * z[3]) , (z[cnt2] + z[cnt2 - 1] + z[cnt2 -2]) / (z[cnt2] * z[cnt2 - 1] * z[cnt2 -2]) });
	if(cnt1 >= 1 && cnt2 >= 2) minans = min({minans , (f[1] + z[1] + z[2]) / (f[1] * z[1] * z[2]) , (f[cnt1] + z[1] + z[2]) / (f[cnt1] * z[1] * z[2]) , (f[1] + z[cnt2] + z[cnt2 - 1]) / (f[1] * z[cnt2] * z[cnt2 - 1]) , (f[cnt1] + z[cnt2] + z[cnt2 - 1]) / (f[cnt1] * z[cnt2] * z[cnt2 - 1])});
	if(cnt1 >= 2 && cnt2) minans = min({minans , (f[1] + f[2] + z[1]) / (f[1] * f[2] * z[1]) , (f[1] + f[2] + z[cnt2]) / (f[1] * f[2] * z[cnt2]) , (f[cnt1] + f[cnt1 - 1] + z[1]) / (f[cnt1] * f[cnt1 - 1] * z[1]) , (f[cnt1] + f[cnt1 - 1] + z[cnt2]) / (f[cnt1] * f[cnt1 - 1] * z[cnt2])}); 
	if(cnt1 >= 3) minans = min({minans , (f[1] + f[2] + f[3]) / (f[1] * f[2] * f[3]) , (f[cnt1] + f[cnt1 - 1] + f[cnt1 - 2]) / (f[cnt1] * f[cnt1 - 1] * f[cnt1 - 2])});
	if(cnt1 && cnt2) minans = min({minans , (z[1] + f[1] + z[cnt2]) / (z[1] * f[1] * z[cnt2])});
	if(cnt1 >= 2 && cnt2) minans = min(minans , (f[1] + f[cnt1] + z[1]) / (f[1] * f[cnt1] * z[1]));
	cout << fixed << setprecision(12) << minans << "\n";
	cout << fixed << setprecision(12) << ans << "\n";
	return;
}

signed main(){
	//open("1");
	ios::sync_with_stdio(false);
	cin.tie(0);
	ok();
	return 0;
}
```


---

