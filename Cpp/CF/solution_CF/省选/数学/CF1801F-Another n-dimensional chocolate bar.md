# Another n-dimensional chocolate bar

## 题目描述

Mom bought the boy Vasya a $ n $ -dimensional chocolate bar, which is a $ n $ -dimensional cube with the length of each side equal to $ 1 $ . The chocolate is planned to be divided into slices. According to the $ i $ th dimension, it can be divided by hyperplanes into $ a_i $ equal parts. Thus, the chocolate is divided in total into $ a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n $ slices, each slice has a length of $ i $ -th dimension equal to $ \frac{1}{a_i} $ , respectively, the volume of each slice is $ \frac{1}{a_1 a_2 \cdots a_n} $ .Vasya and his friends want to cut a chocolate bar to get at least $ k $ pieces, while Vasya wants to maximize the volume of the smallest of them. It is possible to cut the chocolate bar only at the junction of the lobules, and each incision must pass through the entire chocolate bar along some hyperplane involved in the formation of lobules. Only after making all the cuts, Vasya disassembles the chocolate into pieces.

More formally, Vasya wants to choose the numbers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le a_i $ ) — the number of parts into which Vasya will cut the chocolate bar along each dimension. The condition $ b_1 \cdot b_2 \cdot \ldots \cdot b_n \ge k $ must be met to get at least $ k $ pieces after all cuts. It can be noted that with optimal cutting with such parameters, the minimum piece will contain $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor $ slices, and its volume will be equal to $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} $ .

Vasya wants to get the maximum possible value of the volume of the minimum piece multiplied by $ k $ , that is, he wants to maximize the number of $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} \cdot k $ . Help him with this.

## 说明/提示

In the first example, a one – dimensional chocolate bar can be divided as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/f5840bc9b6fba83080f4985e511bff8530afd934.png)

Then the answer will be $ \frac{2}{5} \cdot 2 = 0.8 $

In the second example, the chocolate bar can be cut as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/627b4397ae726c6c50e5194d712fdc53a32a0b7f.png)

Then the answer will be $ \frac{2}{5} \cdot \frac{3}{10} \cdot 6 = 0.72 $

In the third example, the chocolate bar can be cut as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/40196c672f43b7ab300ba0a5b9511f838e6ac4ad.png) Then the answer will be $ \frac{2}{4} \cdot \frac{1}{4} \cdot 7 = 0.875 $

## 样例 #1

### 输入

```
1 2
5```

### 输出

```
0.8```

## 样例 #2

### 输入

```
2 6
5 10```

### 输出

```
0.72```

## 样例 #3

### 输入

```
2 7
4 4```

### 输出

```
0.875```

## 样例 #4

### 输入

```
2 3
4 5```

### 输出

```
0.75```

## 样例 #5

### 输入

```
4 444
57 179 239 2```

### 输出

```
0.97557326850704739751```

## 样例 #6

### 输入

```
2 5
2 2```

### 输出

```
0```

# 题解

## 作者：mod998244353 (赞：13)

看到积式，我们自然能想到用 dp 来解决此类问题。

设 $f_{i,j}$ 表示前 $b_{1,2,\cdots,i}$ 的值已经确定，后面的数的限制为 $\prod\limits_{p=i+1}^n b_p\geq j$ 的前提下， $\prod\limits_{p=1}^i\lfloor\dfrac{a_p}{b_p}\rfloor \times \dfrac{1}{a_p}$ 的最大值。

自然可以通过枚举 $b_i$ 的值来转移：

令 $b_i=x$ ，则有转移： $f_{i,\lceil\frac{j}{x}\rceil}\leftarrow f_{i-1,j}\times\lfloor\dfrac{a_p}{x}\rfloor \times \dfrac{1}{a_p}$

初始状态为： $f_{0,k}=1$，答案为： $f_{n,1}\times k$。

直接转移是 $O(nk)$ 的，考虑优化。

可以发现，第二维的值是由 $k$ 不断除以整数后向上取整得到的。

向上取整有一个性质：
 
$\lceil\dfrac{k}{a}\rceil=\lfloor\dfrac{k-1}{a}\rfloor+1$

而且这个式子可以嵌套：

$\lceil\dfrac{\lceil\frac{k}{a}\rceil}{b}\rceil=\lfloor\dfrac{\lfloor\frac{k-1}{a}\rfloor+1-1}{b}\rfloor+1=\lfloor\dfrac{\lfloor\frac{k-1}{a}\rfloor}{b}\rfloor+1=\lfloor\dfrac{k-1}{ab}\rfloor+1$

这样我们就可以把向上取整转化为向下取整了，用类似杜教筛的转移方式就可以得到 $O(nk^{0.75})$ 的做法。

警钟长鸣：递归写法有可能被卡常，我考场上就被卡了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105,N=7005;
int n,k,a[MAXN],v[N],m,id[10000001];
bool vis[MAXN][N];
double f[MAXN][N];
int main() {
    scanf("%d%d",&n,&k);
    for(int i=1; i<=n; ++i)
        scanf("%d",&a[i]);
    if(k==1) {//记得特判k=1
        double ans=1.0;
        printf("%.20lf\n",ans);
        return 0;
    }
    for(int l=1,r; l<k; l=r+1) {
        r=(k-1)/((k-1)/l);
        v[++m]=(k-1)/l;
        id[v[m]]=m;
    }
    v[++m]=0,id[0]=m;//不要忘记还有1
    f[0][1]=1;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            if(f[i-1][j]) {
                for(int l=1,r; l<=v[j]; l=r+1) {
                    r=v[j]/(v[j]/l);
                    f[i][id[v[j]/r]]=max(f[i][id[v[j]/r]],(a[i]/l)/(double)a[i]*f[i-1][j]);
                }
                f[i][m]=max(f[i][m],(a[i]/(v[j]+1))/(double)a[i]*f[i-1][j]);
			}
    printf("%.15lf\n",f[n][m]*k);
    return 0;
}
```

---

## 作者：RedLycoris (赞：7)

考虑到最多只会有一个 $b_i \ge \sqrt{k}$。

+ 没有任何一个 $b_i \geq \sqrt{k}$。

那么我们可以考虑类似 meet-in-the-middle 的做法。

令 $f_{i,j}$ 表示考虑了前 $i$ 个数，此时乘积为 $j$，$\lfloor\frac{a_1}{b_1}\rfloor\lfloor\frac{a_2}{b_2}\rfloor\dots\lfloor\frac{a_i}{b_i}\rfloor\frac{1}{a_1a_2\dots a_i}$ 的最大值，$g_{i,j}$ 的定义类似，不过是从 $n$ 开始倒着的。dp 的时候枚举 $i$，枚举 $j$，再枚举满足 $j\times k \le$ 第二维大小的所有 $k$ 即可。

则我们这种情况下的最好答案就是枚举一个中间断点 $i$，和 $i$ 左边的部分的乘积 $j$，$f_{i,j}\times g_{i+1,\lceil\frac{k}{j}\rceil}$ 的最小值了。

此时我们需要证明，在所有选择的 $b_i$ 都 $\le \sqrt{k}$ 的情况下，$f$ 和 $g$ 的第二维都只要开到 $k^{\frac{3}{4}}$ 即可。

不妨设一个 $x$，初始为 $b_i$ 最大的位置，令 $p$ 为 $x$ 左边所有 $b_i$ 的乘积，$q$ 为 $x$ 右边所有 $b_i$ 的乘积。

我们贪心的考虑，如果 $b_x^2\times p <q$，就让 $x+1$；如果 $b_x^2\times q < p$，就让 $x-1$。在移动 $x$ 的同时维护 $p$ 和 $q$ 的值。

此时第二维就需要开到一个 $\min(p,q)\times b_x$ 的大小。因为 $p \times q \times b_x$ 是 $O(k)$ 级别的，所以 $\min(p,q)\le \sqrt{\frac{k}{b_x}}$，故第二维只需要开到 $\sqrt{\frac{k}{b_x}}\times b_x=\sqrt{k\times b_x}$ 即可。因为 $b_x\le \sqrt{k}$，所以 $\sqrt{\frac{k}{b_x}}\times b_x \le k^{\frac{3}{4}}$，得证。

综上，该部分复杂度为 $O(n\times k^{\frac{3}{4}}\times\log(k^{\frac{3}{4}}))$。

+ 存在恰好一个 $b_i \geq \sqrt{k}$。

那么我们可以直接枚举这个 $i$，发现 $i$ 左侧和右侧 $b_j$ 的乘积均 $\le \sqrt{k}$。令 $h_j$ 表示现暂时不选 $b_i$，其他所有位置都选之后乘积为 $j$ 时的最大值。这个可以利用 $f_{i-1}$ 和 $g_{i+1}$ 快速处理。

然后我们枚举除了 $b_i$ 的所有 $b_j$ 的乘积 $t$，推出 $b_i$ 的值最小是多少，计算出 $\lfloor\frac{a_i}{b_i}\rfloor\frac{1}{a_i}$ 即第 $i$ 个数的贡献，乘上 $h_t$ 即可。

该部分复杂度为 $O(n\sqrt{k})$。

综上，总复杂度为 $O(n\times k^{\frac{3}{4}}\times\log(k^{\frac{3}{4}}))$，可以~~不知道为什么但只跑了1.5s~~通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int B=177830;
const int B2=6600;
int n,w,a[103];
double f[103][B+3],g[103][B+3],ans;
vector<int>v;
double h[B2+3];
int main(){
	cin>>n>>w;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	f[0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=B;j++)
			for(int k=1;k<=B/j;k++)
				f[i][j*k]=max(f[i][j*k],f[i-1][j]*(1.0*(a[i]/k)/a[i]));
		for(int j=B;j>0;j--)
			f[i][j]=max(f[i][j],f[i][j+1]); 
	}
	g[n+1][1]=1;
	for(int i=n;i;i--){
		for(int j=1;j<=B;j++)
			for(int k=1;j*k<=B;k++)
				g[i][j*k]=max(g[i][j*k],g[i+1][j]*(1.0*(a[i]/k))/a[i]);
		for(int j=B;j>0;j--)
			g[i][j]=max(g[i][j],g[i][j+1]); 
	}
	for(int i=0;i<=n;++i)for(int j=1;j<=B;++j) 
	    if((w+j-1)/j<=B)ans=max(ans,f[i][j]*g[i+1][(w+j-1)/j]);
	for(int i=1;i<=n;++i){
		if(1){
			for(int j=1;j<=B2;++j)h[j]=0;
			for(int j=1;j<=B2;++j)
				for(int k=1;k*j<=B2;++k)
					h[j*k]=max(h[j*k],f[i-1][j]*g[i+1][k]);
			for(int j=B2;j;--j)h[j]=max(h[j],h[j+1]);
			for(int j=1;j<=B2;++j){
				int ee=(w+j-1)/j;ee=max(ee,1);
				if(ee>a[i])continue;
				int e2=a[i]/ee;
				ans=max(ans,1.0*e2/(1.0*a[i])*h[j]);
			}
		}
	}
	cout<<fixed<<setprecision(15)<<ans*w<<'\n';
}
```

---

## 作者：WrongAnswer_90 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17949702)

[CF1801F Another n-dimensional chocolate bar](https://www.luogu.com.cn/problem/CF1801F)

高妙的数论分块优化 DP。

第一步设计状态就有很大问题，如果直接设 $f_{i,j}$ 表示前 $i$ 个数成绩为 $j$ 那就死了。这完全没有利用到整除的性质。正确做法是设 $f_{i,j}$ 表示前 $i$ 个数把 $k$ “削”成了 $j$（要求 $\prod_{k=i+1}^nb_k\geq j$）。转移：

$$
f_{i,\lceil\frac j {b_i}\rceil}\leftarrow f_{i,j}\times \lfloor\frac{a_i}{b_i}\rfloor\times\frac 1 {a_i}
$$

利用向上取整的性质

$$
f_{i,\lfloor\frac {j-1} {b_i}\rfloor+1}\leftarrow f_{i,j}\times \lfloor\frac{a_i}{b_i}\rfloor\times\frac 1 {a_i}
$$


注意到 $j$ 如果被“削”两次：

$\lfloor\frac{\lfloor\frac {j-1} x\rfloor+1-1}{y}\rfloor+1=\lfloor\frac j {xy}\rfloor+1$

所以无论 $k$ 被怎么削，状态只会在 $S=\{\lfloor\frac k i\rfloor|i\in [1,k]\}$ 的 $\mathcal O(\sqrt k)$ 个数中，所以状态数变成了 $\mathcal O(n\sqrt k)$。

第二个问题，一眼想到把 $a$ 整除分块变成 $\mathcal O(\sqrt a)$ 个有价值的 $b$，看上去非常的有道理，但乘上状态数当场爆炸。正确的做法是对于状态进行数论分块，对于 $\lfloor\frac j x\rfloor$ 相同的 $x$ 的区间，只需要取最优的左端点进行转移。这样复杂度可以由类似杜教筛的分析方式得出，为 $\mathcal O(k^{0.75})$。

代码很好写，但是小心炸精度。

```cpp
	int n,m,cnt,v[7010],a[110];
	double f[110][7010];
	short pos[10000010];
	inline void mian()
	{
		read(n,m);
		for(int i=1;i<=n;++i)read(a[i]);
		for(int l=1,r;l<m;l=r+1)v[++cnt]=(m-1)/l,r=(m-1)/((m-1)/l);
		v[++cnt]=0,reverse(v+1,v+1+cnt);
		for(int i=1;i<=cnt;++i)pos[v[i]]=i;
		f[0][cnt]=1;
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=cnt;++j)
			{
				if(!f[i-1][j])continue;
				for(int l=1,r;l<=v[j];l=r+1)
				{
					r=v[j]/(v[j]/l);
					Mmax(f[i][pos[v[j]/l]],f[i-1][j]*(a[i]/l)/a[i]);
				}
				Mmax(f[i][1],f[i-1][j]*(a[i]/(v[j]+1))/a[i]);
			}
		}
		printf("%.10lf",f[n][1]*m);
	}
```

---

