# Composite Coloring

## 题目描述

A positive integer is called composite if it can be represented as a product of two positive integers, both greater than $ 1 $ . For example, the following numbers are composite: $ 6 $ , $ 4 $ , $ 120 $ , $ 27 $ . The following numbers aren't: $ 1 $ , $ 2 $ , $ 3 $ , $ 17 $ , $ 97 $ .

Alice is given a sequence of $ n $ composite numbers $ a_1,a_2,\ldots,a_n $ .

She wants to choose an integer $ m \le 11 $ and color each element one of $ m $ colors from $ 1 $ to $ m $ so that:

- for each color from $ 1 $ to $ m $ there is at least one element of this color;
- each element is colored and colored exactly one color;
- the greatest common divisor of any two elements that are colored the same color is greater than $ 1 $ , i.e. $ \gcd(a_i, a_j)>1 $ for each pair $ i, j $ if these elements are colored the same color.

Note that equal elements can be colored different colors — you just have to choose one of $ m $ colors for each of the indices from $ 1 $ to $ n $ .

Alice showed already that if all $ a_i \le 1000 $ then she can always solve the task by choosing some $ m \le 11 $ .

Help Alice to find the required coloring. Note that you don't have to minimize or maximize the number of colors, you just have to find the solution with some $ m $ from $ 1 $ to $ 11 $ .

## 说明/提示

In the first test case, $ \gcd(6,10)=2 $ , $ \gcd(6,15)=3 $ and $ \gcd(10,15)=5 $ . Therefore, it's valid to color all elements the same color. Note that there are other colorings which satisfy Alice's requirement in this test case.

In the second test case there is only one element of each color, so the coloring definitely satisfies Alice's requirement.

## 样例 #1

### 输入

```
3
3
6 10 15
2
4 9
23
437 519 865 808 909 391 194 291 237 395 323 365 511 497 781 737 871 559 731 697 779 841 961```

### 输出

```
1
1 1 1
2
2 1
11
4 7 8 10 7 3 10 7 7 8 3 1 1 5 5 9 2 2 3 3 4 11 6```

# 题解

## 作者：Rainy7 (赞：8)

- **题目大意**

  给定 $n$ 个数，要求将其分为不超过 $11$ 组，保证每组里面两两**不互质**。
  


------------


- **题解**

  打表可得，$\sqrt{1000}$ 中的质数不超过 $11$ 个，用数组 $p[i]$ 表示第 $i$ 个质数。
  
  **因为题目没有要求组数最大或最小**，所以对于 $a[i]$，如果它是 $p[j]$ 的倍数，那么他就为第 $j$ 组。
  
  每组确定后，再确定组数，因为题目要求**编号必须从 $1$ 开始，并且编号必须连续**，所以最后在处理一下中间有没有**空组**即可。
  


------------

- 代码

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int Maxn=1000+5;
int T,n,tot,a[Maxn],ans[Maxn];
int cnt,p[Maxn],num[Maxn];
bool f[Maxn],vis[Maxn];
int main()
{	scanf("%d",&T);
	int sq=sqrt(1000);
	for(int i=2;i<=sq;i++)
	{	if(f[i])continue;
		p[++cnt]=i;
		for(int j=i+i;j<=sq;j+=i)
			f[j]=1;
	}
//	for(int i=1;i<=cnt;i++)
//		printf("%d ",p[i]);
//	printf("\n");
	while(T--)
	{	memset(vis,0,sizeof(vis));
		memset(ans,0,sizeof(ans));
		memset(num,0,sizeof(num));
		tot=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=cnt;j++) //分组
				if(a[i]%p[j]==0){ans[i]=j;break;}
		for(int i=1;i<=n;i++) //判断空组
			vis[ans[i]]=1;
		for(int i=1;i<=cnt;i++) //统计&处理空组
			if(vis[i])num[i]=++tot;
		for(int i=1;i<=n;i++) 
			ans[i]=num[ans[i]];
		printf("%d\n",tot);
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```

--------------------

$$\text{by Rainy7}$$

---

## 作者：cute_overmind (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1332B)

### 题目大意
给定你 $n$ 个数，将这 $n$ 个数分成不超过 $11$ 组，要求保证每个组中的数两两不互质。

### 题目分析
因为题目中明确给出样例数据为 $1 \le n,a_i \le 1000$，而 $\sqrt{1000}$ 中质数只有 $11$ 个，所以我们只需按照它们是否含有 $1$ 至 $11$ 的质因数来对其进行分类即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int p[] = {1 , 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 33};
int cur[15] , a[N], b[N];
void solve()
{
	int cnt = 0 , n;
	memset(cur , 0 , sizeof(cur));
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= 11;j++){
			if(a[i] % p[j] == 0){
				if(cur[j] == 0) cur[j] = ++cnt;
				b[i] = cur[j];
				break;
			}
		}
	}
	cout << cnt << '\n';
	for(int i = 1;i <= n;i++) cout << b[i] << " ";
	cout << '\n';
}
int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：lijianACE (赞：2)

## Composite Coloring 题解
通过证明。

![](https://cdn.luogu.com.cn/upload/image_hosting/kxy100nw.png)

[ CF 传送门](https://codeforces.com/contest/1332/problem/B)   

[洛谷传送门](https://www.luogu.com.cn/problem/CF1332B)  

题目大意就是把每个数分到某个集合，使得集合内任意两个数不互质，并且集合个数小于等于十一。  

**注意，这里没要求集合个数要最小，只要个数小于等于十一就行了。**  

大家都知道，任何数都可以表示为几个质数相乘，所以如果能用质数来代表各个数的公因数，那就再方便不过了，先来枚举一下前十一个质数看看。      

$2,3,5,7\ldots 29,31$     

计算发现，$31$ 不仅是第十一个质数，并且是平方后不大于 $1000$ 且最接近 $1000$ 的质数。（$33=1089>1000$）  

所以，我们可以搞十一个桶，分别是十一个质数，假设 $a$ 序列第 $i$ 个数是 $a_i$，如果某个质数可以整除 $a_i$，那就把 $a_i$ 放入这个桶里，这样保证这个桶里得数的因数一定都有这个桶代表的质数，自然公因数就大于 $2$ 了。  

小疑问：  
1. $a_i$ 是质数怎么办?  
答：不会的，因为我们看一下题目。  
>
>  _**每个数有三个以上因子。**_ 
>

即每个数都是合数，这样第一个问题解决（所以以后做题要仔细看数据范围啊）。  

2. $a_i$ 的最小因数大于这几个桶怎么办？  
答：这个也容易解决，对于任意 $x$ 来说，假设它的因子为 $p$ 和 $q$，即 $x=p\cdot q$，且 $p\ge q$，则 $q\le\sqrt{x}$（如果 $q>\sqrt{x}$，而 $p\ge q$,则 $p\cdot q>x$,与 $x=p\cdot q$ 不符，判断质数用的优化也是这个方法）而 $\sqrt{1000}<33$，所以最多就到 $31$。  

3. 分出来得集合个数大于 $11$ 怎么办？  
答：和上个问题同理，十一个桶，至多用十一个，不可能出现十二个。  

输出是什么？第一行即为用过桶的个数，第二行即每个数在编号为几的桶里。（注意，是编号，不是桶代表的质数！）  

一次的时间复杂度大概是  $O(N)$，$T$ 次即  $O(T\times N)$，大概 $10^7$，但实际复杂度远小于这个数，所以能过。  
Code: 

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1145],prime[19]={0,2,3,5,7,11,13,17,19,23,29,31},usep[19],gs=0;
//定义一个usep，表示用的桶的编号
int main(){
	cin>>t;
	while(t--){
		gs=0;
		memset(usep,0,sizeof(usep));//记得清零
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=11;j++){
				if(a[i]%prime[j]==0){
					if(usep[j]==0){//如果还没用过
						gs++;
						usep[j]=gs;
					}
					a[i]=usep[j];//千万记得不是赋值它桶代表的质数
					break;
				}
			}
		}
		printf("%d\n",gs);
		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	return 0;
}
```
题解写的不是很好，望见谅！  

如果有误，敬请指导。  

QWQ  
2024.10.19 第一次打回，因为中英文间没加空格。  
2024.10.19 第二次打回，因为题解不符规范。  
2024.10.19 第三次打回，同上。  
2024.10.21 第四次打回！因为英文，数学式与中文标点见不小心多加了空格。

---

## 作者：⚡current⚡ (赞：2)

> Alice showed already that if all $a_i≤1000$​ then she can always solve the task by choosing some *m*≤11.

这句话看起来是一句保证，但思考一下为什么或许会有些帮助。

对所有小于1000的合数进行质因数分解，其中最小的一个质因数一定是小于33(不包括33)的质数，因为$33*33=1089>1000$，而小于33的质数恰好有11个，那么我们根据$a_i$的最小质因数来给$a_i$染色就可以了。

注意颜色编号从一开始哦，要记录一下。

前十一个质数:```const int c[15] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 33};```

$\text{CODE}\downarrow$

```c++
#include<stdio.h>

const int c[15] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 33};
int id[15], a[1005], b[1005], cnt, t, n;

int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 1; i <= 11; ++i)
			id[i] = 0;
		cnt = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a+i);
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= 11; ++j)
			{
				if(a[i]%c[j] == 0)
				{
					if(id[j] == 0) id[j] = ++cnt;
					b[i] = id[j];
					break;
				}
			}
		}
		printf("%d\n", cnt);
		for(int i = 1; i <= n; ++i) printf("%d ", b[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：2)

### Description

- 给定一个长度为 $n$ 的序列 $a$，满足序列 $a$ 中的元素都至少有三个因子（包括 $1$ 和自身）。
- 请用 $m$ 种颜色给 $a$ 染色，使得 $a$ 中每个元素都被染上颜色，并且每种颜色都被用到至少一次。
- 对于两个相同颜色的数字，要求他们的 $\gcd$ 大于 $1$，但是不要求 $\gcd$ 大于 $1$ 的数必须染相同颜色。
- 请构造一种可行的方案。**请注意，$m$ 是自己构造的而不是给出的，并且不必最小化 $m$**。
- 可以证明，对于给出的数据范围，一定存在一种 $m \leq 11$ 的方案，因此构造出的方案要求 $m \leq 11$。
- 多组数据，对于单组数据，$1 \leq n, a_i \leq 10^3$。且全部数据的 $n$ 之和不超过 $10^4$。

### Solution

为什么你们都用到了那个因子数不低于 $3$ 的性质啊.jpg。

注意到所有存在公因数的数都可以染上同一个颜色，所以可以考虑给因数染色。对 $a$ 的每个数都分解因数，如果它存在已经被染色的因数，就把该数也染成这个颜色，否则新开一个颜色，染给该数。最后将该数字的所有因数都染成该数的颜色即可。显然这是一种可以最小化 $m$ 的构造方法。因此给出的方案一定是符合 $m \leq 11$ 的要求的。

时间复杂度 $O(n \times a)$，好像和其他做法比菜了不少，但是**又 不 是 不 能 过**（雾

### Code

```cpp
const int maxn = 10005;
const int maxt = 1005;

int t, n;
int a[maxn], col[1005], ans[maxn];
std::vector<int> d[maxt];

int main() {
  freopen("1.in", "r", stdin);
  for (qr(t); t; --t) {
    qr(n);
    qra(a + 1, n);
    memset(col, 0, sizeof col);
    for (int i = maxt - 1; ~i; --i) d[i].clear();
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 2; j <= a[i]; ++j) if ((a[i] % j) == 0) {
        d[j].push_back(i);
      }
    }
    for (int i = 2; i < maxt; ++i) {
      int cc = 0;
      for (auto u : d[i]) if (ans[u] == 0) {
        cc = -1;
        break;
      }
      if (cc == -1) {
        ++cnt;
        for (auto u : d[i]) if (ans[u] == 0) {
          ans[u] = cnt;
        }
      }
    }
    qw(cnt, '\n');
    qwa(ans + 1, n, ' ', '\n');
    for (int i = 1; i <= n; ++i) ans[i] = 0;
  }
  return 0;
}
```



---

## 作者：George1123 (赞：1)

# 题解-Composite Coloring

## [博客中阅读](https://www.cnblogs.com/Wendigo/p/12611937.html#B)

> [Composite Coloring](https://codeforces.com/contest/1332/problem/B)

> $T$ 组测试数据，每次给定一个长度为 $n$ 的合数序列 $a_i$，需要将每个数染上颜色，使满足对于任意两个颜色相同的数不互质。求一种颜色数为 $m$ 的染色方案（$m$ 自选，不需最小，只需满足 $m\in[1,11]$）。

> 数据范围：$1\le T\le 10^3$，$1\le n\le 10^3$，$4\le a_i\le 10^3$，$1\le \sum n\le 10^4$。

**对于任意满足数据范围限制的序列绝对有解。**

对于任何合数 $a_i\le 1000$，必然有 $d$ 满足 $[d|i]\&[d<32]$。

$[1,32)$ 中正好有 $11$ 个质数，所以遍历每个质数然后把它们的倍数染同色即可。

**易错点：**

题目中有说对于 $1\sim m$ 中的每个颜色，必须有该颜色的数，所以需要对颜色离散化。

**代码：**

```cpp
//Data
const int N=1000;
int n,a[N+7],co[N+7];

//Prime
bitset<37> np;
vector<int> p;

//Main
int main(){
	for(re int i=2;i<=32;i++){
		if(!np[i]) p.pb(i);
		for(re int j:p)if(i*j>N) break;else np[i*j]=1;
	}
	re int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(re int i=1;i<=n;i++)
			scanf("%d",a+i);
		re int C=0;
		fill(co+1,co+n+1,0);
		for(re int j:p){
			re int ttt=0;
			for(re int i=1;i<=n;i++){
				if(!co[i]&&a[i]%j==0){ttt=1,co[i]=C+1;}
			}
			if(ttt) C++;
		}
		printf("%d\n",C);
		for(re int i=1;i<=n;i++)
			printf("%d%c",co[i],"\n "[i<n]);
	}
	return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：YuanZhizheng (赞：0)

题意：
给你一个合数序列，每个数字不大于1000，将序列中每个数字分组，使得每组里面的数字不互质。

题目已经提示了，最多11组。根号1000大约是30多，也就是前11个质数。我们可以知道，每个合数，都能拆解成多个质数的乘积。

前11个质数换着法子相乘是可以完全组成1000以内的数字的，所以我们按照他们是否含有某个质因数来对其进行分类即可。

AC代码如下（配合注释食用）：

```
#include<bits/stdc++.h>
using namespace std;
int a[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};//质数
vector<int>v[12];//用来分组
int num[2005];//记录每个位置数字对应的编号
int tot=1;
int duiyin[15];//记录每个质数对应的编号
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(duiyin,0,sizeof(duiyin));
        tot=1;
        int n;
        scanf("%d",&n);
        for(int i=0;i<=11;i++)
            v[i].clear();
        //上面全是初始化操作
        
        int df=0;//记录有多少种不同种类的质因数
        for(int i=0;i<n;i++)
        {
            int x;
            scanf("%d",&x);
            for(int j=0;j<11;j++)
            {
                if(x%a[j]==0)
                {
                    if(duiyin[j]==0)
                        duiyin[j]=tot++;//tot是编号用的
                    num[i]=duiyin[j];
                    v[j].push_back(x);
                    break;
                }
            }
        }
        for(int i=0;i<11;i++)
            if(v[i].size())df++;
        printf("%d\n",df);
        for(int i=0;i<n;i++)
        {
            printf("%d ",num[i]);
        }
        printf("\n");
        
        //下面这也是初始化
        for(int i=0;i<=n;i++)
            num[i]=0;
    }
    return 0;
}
```

---

## 作者：gyh20 (赞：0)

观察到 $m=11$ ，而不大于 $1000$ 的质数正好有 $11$ 个，按整除性分类即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[100002],p[12]={2,3,5,7,11,13,17,19,23,29,31},col[1002],mx,lst;
signed main(){
	t=read();
	while(t--){
		n=read();memset(col,0,sizeof(col));mx=0;
		lst=0;
		for(re int i=1;i<=n;++i)a[i]=read();
		for(re int i=0;i<11;++i){
			for(re int j=1;j<=n;++j){
				if((!col[j])&&(a[j]%p[i]==0)){
					if(mx!=i+1)++lst;
					col[j]=lst;
					mx=i+1;
				}
			}
		}
		mx=lst;
		printf("%d\n",mx);
		for(re int i=1;i<=n;++i)printf("%d ",col[i]);
		putchar('\n');
	}
}
```


---

## 作者：AutumnKite (赞：0)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

[题目传送门](https://codeforces.com/contest/1332/problem/B)

### 题意

有 $n$ 个大于 $1$ 的合数 $a_i$，你需要给每个数一个颜色 $c_i$，使得对于任意颜色相同的点对 $i,j\ (i\ne j)$，满足 $\gcd(a_i,a_j) > 1$。

你不需要最小化颜色数，但是你需要保证颜色数不超过 $11$，并且每种颜色都出现。

$1\le n\le 1000,4\le a_i\le 1000$。

### 题解

我这个憨批一直把 $\sqrt{1000}$ 当作 $300$ 左右在算...我也不知道我在想什么...

事实上，$\lfloor\sqrt{1000}\rfloor=31$，这意味着任意 $a_i$ 都含有一个不超过 $31$ 的质因子。

而 $31$ 以内的质数只有 $11$ 个，分别是 $2,3,5,7,11,13,17,19,23,29,31$。

直接求出每个数的最小质因子 $p_i$ 后，把 $p_i$ 相同的数颜色染成相同即可。

### 代码

```cpp
const int N = 1005;
const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int n, c[N];
std::vector<int> b[11];
void solve(){
	read(n);
	for (register int i = 0; i < 11; ++i) b[i].clear();
	for (register int i = 1; i <= n; ++i){
		int x;
		read(x);
		for (register int j = 0; j < 11; ++j)
			if (x % p[j] == 0){ b[j].push_back(i); break; }
	}
	int cnt = 0;
	for (register int i = 0; i < 11; ++i)
		if (b[i].size()){
			++cnt;
			for (int v : b[i]) c[v] = cnt;
		}
	print(cnt);
	for (register int i = 1; i <= n; ++i) print(c[i], ' ');
	putchar('\n');
}
```


---

