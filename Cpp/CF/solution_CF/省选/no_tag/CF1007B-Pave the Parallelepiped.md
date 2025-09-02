# Pave the Parallelepiped

## 题目描述

给定一个长方体，其三条边长为正整数 $A$、$B$ 和 $C$。

请你求出有多少组不同的整数三元组 $(a, b, c)$，满足 $1 \leq a \leq b \leq c$，并且长方体 $A \times B \times C$ 可以被若干个 $a \times b \times c$ 的长方体完全铺满。注意，所有小长方体的朝向必须一致。

例如，$1 \times 5 \times 6$ 的长方体可以被 $1 \times 3 \times 5$ 的长方体分割，但不能被 $1 \times 2 \times 3$ 的长方体分割。

## 说明/提示

在第一个测试用例中，长方体 $(1, 1, 1)$ 只能被 $(1, 1, 1)$ 的长方体分割。

在第二个测试用例中，长方体 $(1, 6, 1)$ 可以被 $(1, 1, 1)$、$(1, 1, 2)$、$(1, 1, 3)$ 和 $(1, 1, 6)$ 的长方体分割。

在第三个测试用例中，长方体 $(2, 2, 2)$ 可以被 $(1, 1, 1)$、$(1, 1, 2)$、$(1, 2, 2)$ 和 $(2, 2, 2)$ 的长方体分割。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 1 1
1 6 1
2 2 2
100 100 100
```

### 输出

```
1
4
4
165
```

# 题解

## 作者：duyi (赞：6)

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/14454975.html)


# CF1007B Pave the Parallelepiped

## 题目大意

[题目链接](https://codeforces.com/contest/235/problem/C)

$T$ 组询问。每次给出三个正整数 $A, B, C$，代表一个长宽高分别为 $A, B, C$ 的长方体 $X$。请你求出有多少组正整数 $(a, b, c)$ 满足 $1\leq a\leq b\leq c$，且长宽高分别为 $a, b, c$ 的长方体 $Y$ 能被密铺在 $X$ 中。

密铺的定义是，可以以任意方向摆放 $Y$（$6$ 面里任意一面向下），但是用到的所有 $Y$ 的摆放方向必须一样，按这种方式，用 $Y$ 把 $X$ 填满。

数据范围：$1\leq T\leq 10^5$，$1\leq A,B,C\leq 10^5$。

## 本题题解

问题相当于，给定三个整数 $A, B, C$，求满足 $a|A, b|B, c|C$ 的**无序**三元组 $\{a, b, c\}$ 的数量。换句话说，$\{1, 2, 3\}$ 和 $\{1, 3, 2\}$ 被认为是同一个三元组。

先求出 $A, B, C$ 的所有约数。

考虑一个简化的问题：假设每个约数，都在 $A, B, C$ 里都出现过（也就是 $A = B = C$）。设有 $n$ 个不同的约数，问题相当于从 $n$ 个数里，选择 $k = 3$ 个数，**可以重复**，能得到的无序 $k$ 元组数量。记这个问题的答案为 $f(n, k)$。

这是一个经典问题。设每个数被选中的次数分别为 $x_1, x_2,\dots, x_n$，则 $x_1+x_2+\dots+x_n = k$，$\forall i:x_i\geq 0$。那么原问题相当于【$n$ 个非负整数，和为 $k$ 的方案数】。也就是把 $k$ 个球，分为 $n$ 份，每份可以为空的方案数。先强行给每份添加一个球，于是就是把 $k + n$ 个球，分为 $n$ 份，每份不可以为空的方案数。由插板法可得：$f(n, k) ={k + n - 1\choose n - 1} = {k + n - 1\choose k}$。

但是事实上并非每个约数都在 $A, B, C$ 里都出现过，上述做法里，我们可能会多统计一些答案。对于一道计数题，在这种情况下，往往有两种思路：(1) 容斥原理，即减去不合法的方案；(2) 不重不漏，也就是通过巧妙的枚举方式，使得每种方案恰好被算一次。在本题里，使用容斥原理比较麻烦，需要大量的讨论。故我们考虑不重不漏地计数。

对每个约数，给他一个 $3$ 位二进制码：

- 二进制码的第 $1$ 位为 $1$，表示它是 $A$ 的约数。
- 二进制码的第 $2$ 位为 $1$，表示它是 $B$ 的约数。
- 二进制码的第 $3$ 位为 $1$，表示它是 $C$ 的约数。

例如：$101$ 表示该数是 $A$ 和 $C$ 的约数，但不是 $B$ 的约数。

按照二进制码（共有 $7$ 种），将数划分为 $7$ 类。设每一类分别有 $\mathrm{cnt}_1, \mathrm{cnt}_2,\dots, \mathrm{cnt}_7$ 个数。

枚举无序三元组中，三个数分别属于哪一类，分别记为 $t_1, t_2, t_3$。为了避免重复计数，我们规定：$t_1\leq t_2\leq t_3$。显然必须满足，至少存在一种对应关系 $p$（是一个 $1, 2, 3$ 的排列），使得 $t_{p_1}, t_{p_2}, t_{p_3}$ 的第 $1, 2, 3$ 位分别为 $1$（也就是三元组 $p_1, p_2, p_3$ 位置上分别是 $A, B, C$ 的约数）。

求三个数分别属于 $t_1, t_2, t_3$ 的三元组数量。考虑 $t_1, t_2, t_3$ 中每种类别有几个。设类别 $i$ 有 $u_i = \sum_{j = 1}^{3} [t_j = i]$ 个，则方案数是 $f(\mathrm{cnt}_i, u_i)$。将每种类别的方案数相乘，就是符合 $t_1, t_2, t_3$ 的三元组数量。 累加到答案里即可。

形式化地说：
$$
\mathrm{ans} = \sum_{t_1, t_2, t_3}\prod_{i = 1}^{7}f(\mathrm{cnt}_i, \sum_{j = 1}^{3}[t_j = i])
$$
最后，发现我们其实不需要求出 $A, B, C$ 的所有约数具体是什么，而只需要求出 $\mathrm{cnt}_1, \mathrm{cnt}_2,\dots, \mathrm{cnt}_7$。预处理出每个数的约数数量 $d(x)$（可以线性筛）。每组询问时，用 $\gcd$ 计算出 $\mathrm{cnt}$ 数组，例如：$5 = (101)_2$，则 $\mathrm{cnt}_5 = d(\gcd(A, C)) - d(\gcd(A, B, C))$。

设 $n = \max\{A, B, C\}$。时间复杂度 $\mathcal{O}(n + q\log n)$。此外，因为要枚举 $t_1, t_2, t_3$ 并计算方案，每组询问有常数大约 $7^3\cdot 7$，但是因为强制了 $t_1\leq t_2\leq t_3$，所以实际更小。

## 参考代码

实际提交时建议使用读入、输出优化，详见本博客公告。

```cpp
// problem: CF1007B
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5;

int p[MAXN + 5], cnt_p;
bool v[MAXN + 5];
int d[MAXN + 5], num[MAXN + 5];
void sieve() {
	d[1] = 1;
	for (int i = 2; i <= MAXN; ++i) {
		if(!v[i]) {
			p[++cnt_p] = i;
			num[i] = 1;
			d[i] = 2;
		}
		for (int j = 1; j <= cnt_p && i * p[j] <= MAXN; ++j) {
			v[i * p[j]] = 1;
			if (i % p[j] == 0) {
				num[i * p[j]] = num[i] + 1;
				d[i * p[j]] = d[i] / (num[i] + 1) * (num[i] + 2);
				break;
			}
			num[i * p[j]] = 1;
			d[i * p[j]] = d[i] * 2;
		}
	}
}

int q, a, b, c;
int cnt[8], used[8];

int t[5];
bool check() {
	static int p[5];
	for (int i = 1; i <= 3; ++i) {
		p[i] = i;
	}
	do {
		if ((t[p[1]] & 1) && (t[p[2]] & 2) && (t[p[3]] & 4)) {
			return true;
		}
	} while (next_permutation(p + 1, p + 3 + 1));
	return false;
}

int gcd(int x, int y) {
	return (!y) ? x : gcd(y, x % y);
}
ll comb(int n, int k) {
	ll res = 1;
	for (int i = n; i >= n - k + 1; --i) {
		res *= i;
	}
	for (int i = k; i >= 1; --i) {
		res /= i;
	}
	return res;
}

int main() {
	sieve();
	
	cin >> q;
	while (q--) {
		cin >> a >> b >> c;
		
		int gab = gcd(a, b);
		int gac = gcd(a, c);
		int gbc = gcd(b, c);
		int gabc = gcd(gab, c);
		
		cnt[1] = d[a] - d[gab] - d[gac] + d[gabc];
		cnt[2] = d[b] - d[gab] - d[gbc] + d[gabc];
		cnt[4] = d[c] - d[gac] - d[gbc] + d[gabc];
		cnt[3] = d[gab] - d[gabc];
		cnt[5] = d[gac] - d[gabc];
		cnt[6] = d[gbc] - d[gabc];
		cnt[7] = d[gabc];
		
		ll ans = 0;
		for (t[1] = 1; t[1] <= 7; ++t[1]) {
			for (t[2] = t[1]; t[2] <= 7; ++t[2]) {
				for (t[3] = t[2]; t[3] <= 7; ++t[3]) {
					if (check()) {
						memset(used, 0, sizeof(used));
						used[t[1]]++;
						used[t[2]]++;
						used[t[3]]++;
						ll cur = 1;
						for (int i = 1; i <= 7; ++i) {
							cur *= comb(cnt[i] + used[i] - 1, used[i]);
						}
						ans += cur;
					}
				}
			}
		}
		
		cout << ans << endl;
	}
	return 0;
}
```





---

## 作者：liuyifan (赞：5)

(部分内容转载自CF官方题解)

![1](http://codeforces.com/predownloaded/b9/49/b949c7c458128ec2bb49ca65f0d73f54a7fbb82f.png)

![2](http://codeforces.com/predownloaded/64/c2/64c2b8c0a1c3dc988296b65a801a0190718ab3fd.png)

![3](http://codeforces.com/predownloaded/27/a6/27a624834e20fb191e1f59e5f2c34212a09fee9c.png)
本人渣code:
```cpp
#include<bits/stdc++.h>
#define reg register
#define ll long long
#define td (__gcd(__gcd(a,c),b))
using namespace std;
ll t,a,b,c,ab,bc,ac,f[100005]={1,1},num[100005],prime[100005],tot;
bool isprime[100005];
int main()
{
    for(reg int i=2;i<=100000;i++)
	{
        if(!isprime[i])
		{
            prime[++tot]=i;//质数 
            f[i]=2;
            num[i]=1;
        }
        for(reg int j=1;j<=tot&&i*prime[j]<=100000;j++)
		{
            isprime[i*prime[j]]=1;
            if(!(i%prime[j]))
			{
                num[i*prime[j]]=num[i]+1;
                f[i*prime[j]]=f[i]/(num[i]+1ll)*(num[i*prime[j]]+1ll);//预处理f数组
                break;
            }
            f[i*prime[j]]=f[i]*f[prime[j]];
            num[i*prime[j]]=1;
        }
    }//预处理 
    scanf("%lld",&t);//多组数据 
    while(t--)
	{
        scanf("%lld%lld%lld",&a,&b,&c);
        ab=__gcd(a,b);
		bc=__gcd(b,c);
		ac=__gcd(a,c);
		//__gcd:gcc内置gcd 
        ll ans1=f[a]*f[b]*f[c],ans2=(f[ab]*f[ab]-f[ab])/2ll*f[c],ans3=f[a]*(f[bc]*f[bc]-f[bc])/2ll,ans4=f[b]*(f[ac]*f[ac]-f[ac])/2ll,ans5=(f[td]*f[td]-f[td])+f[td]*(f[td]-1ll)*(f[td]-2ll)/6ll*4ll,ans6=(f[ab]-f[td])*f[td]*(f[td]-1ll)/2ll,ans7=(f[bc]-f[td])*f[td]*(f[td]-1ll)/2ll,ans8=(f[ac]-f[td])*f[td]*(f[td]-1ll)/2ll,ans9=(f[ab]-f[td])*(f[bc]-f[td])*(f[ac]-f[td]);
        //上述的几种情况 
        printf("%lld\n",ans1-ans2-ans3-ans4+ans5+ans6+ans7+ans8-ans9);//输出
    }
    return 0;
}
```

---

## 作者：takanashi_mifuru (赞：4)

~~本来有一篇现成的题解但是我觉得他是假的就删掉了，然后刚才他变成真的了，我还得重新写。~~

两秒 $2\times 10^9$，不是问题，只要自信，怎么过题都可以！

首先这个题我们先预处理一下三个数的连边状态，这个总共只有 $(2^3)^3$ 种，我们把所有可行状态全部记录，同时记录每一种状态需要哪两种状态才能满足完美匹配条件，这个用 Hall 定理是好做的。

然后我们把所有因数处理下来，去重之后排序。

然后我们倒序枚举 $x$，对于一个 $x$，假设他的状态是 $S$，那么我们预处理出来了哪些状态可以和他配在一起满足条件，这个是很好求的。

同时倒序枚举动态计数一下两个状态匹配在一起的方案数也是很好做的。

至此，我们用时间复杂度为 $O(T\sqrt n)$ 的算法解决了这个题，外面还有一个 $2^6$ 的常数。

而且很多时候跑不满 $2^6$。

实测有点小卡常，加个火车头可以直接过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int D[1<<3][1<<3];
int F[1<<3];
struct node{
   int x,y;
};
vector<node> Need[1<<3];
int fac[10005];
int tot;
void calc(int x){
   for(int i=1;i*i<=x;i++){
      if(x%i==0){
         fac[++tot]=i;
         if(i*i<x)fac[++tot]=x/i;
      }
   }
   return;
}
bool check(int a[]){//hall
   bool vis[5];
   for(int S=0;S<8;S++){
      for(int i=0;i<3;i++) vis[i]=false;
      int cnt=0;
      for(int i=0;i<3;i++){
         if((S>>i)&1){
            cnt++;
            for(int j=0;j<3;j++){
               if((a[i]>>j)&1){
                  vis[j]=true;
               }
            }
         }
      }
      for(int i=0;i<3;i++){
         cnt-=vis[i];
      }
      if(cnt>0){
         return false;
      }
   }
   return true;
}
signed main(){
   for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
         for(int k=j;k<8;k++){
            int a[3];
            a[0]=i,a[1]=j,a[2]=k;
            if(check(a)){
               Need[i].push_back(node{j,k});
            }
         }
      }
   }
   scanf("%d",&T);
   while(T--){
      tot=0;
      int a[3];
      for(int i=0;i<3;i++)scanf("%d",&a[i]);
      for(int i=0;i<3;i++)calc(a[i]);
      sort(fac+1,fac+1+tot);
      int pos=0;
      for(int i=1;i<=tot;i++){
         if(fac[i]!=fac[i-1]){
            fac[++pos]=fac[i];
         }
      }
      for(int i=0;i<8;i++){
         F[i]=0;
      }
      for(int i=0;i<8;i++){
         for(int j=0;j<8;j++){
            D[i][j]=0;
         }
      }
      int ans=0;
      for(int i=pos;i>=1;i--){
         int val=fac[i];
         int S=0;
         for(int j=0;j<3;j++){
            S=S<<1|(a[j]%val==0);
         }
         F[S]++;
         for(int R=S;R<8;R++){
            D[S][R]+=F[R];
         }
         for(int R=0;R<S;R++){
            D[R][S]+=F[R];
         }
         for(int j=0;j<Need[S].size();j++){
            int y=Need[S][j].x;
            int z=Need[S][j].y;
            ans+=D[y][z];
         }
      }
      printf("%d\n",ans);
   }
   return 0;
}
```

---

## 作者：攀岩高手 (赞：4)

题意可以转化为从 $A,B,C$ 的因子中各选一个数组成的本质不同的无序三元组有多少个。

我刚开始想简单了，以为把 $A,B,C$ 排个序然后再枚举前两个就可以了~~（毕竟 B 题）~~。实际上这样做明显是错的，因为较大的数不一定包含较小的数的所有因子。那么我们就需要讨论了。

手玩一下可以知道，$10^5$ 以内的数最多有约 100 个因数，所以枚举是不行的。我们考虑把这些因数分类（以 $A=9,B=6,C=8$ 为例）：

![](http://www.lengyanze.com:88/usr/uploads/2020/02/3482438881.png)

可以看出上图的 7 个区域中，两个不同区域的元素是无关的，所以我们只关心每个区域中的元素个数 $f(i)$，$i$ 为上图所示的括号中的区域编号。这可以先线性筛出约数个数再容斥求出。考虑在 $A,B,C$ 三个圆中分别选出一个区域，这样就可以覆盖所有本质不同的状态了。每种选择要讨论一下三种情况：
- 选出的三个区域都相同（即区域`7`）。此时贡献为 $\frac{f(7)[f(7)+1][f(7)+2]}{6}$。
- 选出的三个区域有两个相同（设为区域 $x$），剩下的一个与前两个不同（设为区域 $y$）。此时的贡献为 $\frac{f(x)[f(x)+1]}{2}\cdot f(y)$。
- 选出的三个区域都不同（设分别是 $x,y,z$）。此时贡献为 $f(x)f(y)f(z)$。

把表打出来可以发现一共有 51 种选出三个区域的方法，因此复杂度为 $O(51t)$。下面是代码，上面部分说的不够清楚的地方加了注释：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=110000;
const int C[51][3]={{1, 2, 4}, {1, 2, 5}, {1, 2, 6},
                    {1, 2, 7}, {1, 3, 4}, {1, 3, 5},
                    {1, 3, 6}, {1, 3, 7}, {1, 4, 6},
                    {1, 4, 7}, {1, 5, 6}, {1, 5, 7},
                    {1, 6, 6}, {1, 6, 7}, {1, 7, 7},
                    {2, 3, 4}, {2, 3, 5}, {2, 3, 6},
                    {2, 3, 7}, {2, 4, 5}, {2, 4, 7},
                    {2, 5, 5}, {2, 5, 6}, {2, 5, 7},
                    {2, 6, 7}, {2, 7, 7}, {3, 3, 4},
                    {3, 3, 5}, {3, 3, 6}, {3, 3, 7},
                    {3, 4, 5}, {3, 4, 6}, {3, 4, 7},
                    {3, 5, 5}, {3, 5, 6}, {3, 5, 7},
                    {3, 6, 6}, {3, 6, 7}, {3, 7, 7},
                    {4, 5, 6}, {4, 5, 7}, {4, 6, 7},
                    {4, 7, 7}, {5, 5, 6}, {5, 5, 7},
                    {5, 6, 6}, {5, 6, 7}, {5, 7, 7},
                    {6, 6, 7}, {6, 7, 7}, {7, 7, 7}};
// 以上是 51 种选三个区域的方法

bool mark[MAXN];
int pri[MAXN], d[MAXN], num[MAXN];
void sieve(int lim)
{
    int cnt=0; d[1]=1;
    for (int i=2; i<=lim; i++)
    {
        if (!mark[i])
            pri[cnt++]=i, d[i]=2, num[i]=1;
        for (int j=0; j<cnt&&i*pri[j]<=lim; j++)
        {
            mark[i*pri[j]]=1;
            if (i%pri[j]==0)
            {
                num[i*pri[j]]=num[i]+1;
                d[i*pri[j]]=d[i]/(num[i]+1)*(num[i*pri[j]]+1);
                break;
            }
            d[i*pri[j]]=d[i]*d[pri[j]];
            num[i*pri[j]]=1;
        }
    }
}

int f[10];

int main()
{
//	freopen("B.in", "r", stdin);
//	freopen("B.out", "w", stdout);
	int t;
	scanf("%d", &t);
	sieve(1E5); // 线性筛约数个数
	while (t--)
	{
		int a[3];
		scanf("%d%d%d", &a[0], &a[1], &a[2]);
		
		for (int s=1; s<=7; s++)
		{
			int g=0;
			for (int i=0; i<3; i++)
				if (s&1<<i) g=__gcd(g, a[i]);
			f[s]=d[g];
			// 注意为了方便，图中的区域编号与二进制码一一对应
			// 两个数的因数的交就是它们 gcd 的因数
		}
		
		f[3]-=f[7], f[5]-=f[7], f[6]-=f[7];
		f[1]-=f[3]+f[5]+f[7];
		f[2]-=f[3]+f[6]+f[7];
		f[4]-=f[5]+f[6]+f[7];
		// 容斥，把重复算的东西去掉
		
		int ans=0;
		for (int i=0; i<51; i++)
		{
			int x=C[i][0], y=C[i][1], z=C[i][2];
			if (x==y&&x==z) ans+=f[x]*(f[x]+1)*(f[x]+2)/6;
			else if (x==y) ans+=f[x]*(f[x]+1)/2*f[z];
			else if (x==z) ans+=f[x]*(f[x]+1)/2*f[y];
			else if (y==z) ans+=f[y]*(f[y]+1)/2*f[x];
			else ans+=f[x]*f[y]*f[z];
			// 分别讨论了三种情况，其中第二种还要考虑是哪两个区域相同
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：2)

感觉这个做法比题解区几乎所有做法都简单啊！

为了方便，把题目给定的三元组记为 $(a_1,a_2,a_3)$。设 $D(i)$ 表示 $a_i$ 的所有因数构成的集合。

先单走一个 Burnside，这样的好处是不用考虑大小关系。那么我们只需要 $(x_1,x_2,x_3)$ 三元组满足：

- 存在一个长为 $3$ 的排列 $p\in \text{perm}(3)$，使得 $x_i\in D(p_i)$，$\forall 1\le i\le 3$。
- 可能会带有的限制：$x_1=x_2$ 或者 $x_2=x_3$ 或者 $x_3=x_1$，或者 $x_1=x_2=x_3$。

第二个限制太弱智了，只考虑第一个限制：设 $S(i)=\{j\mid x_i\in D(j)\}$，考虑二分图匹配。$L_i$ 向 $S(i)$ 中所有 $j\in S(i)$ 的 $R_j$ 连边，容易发现满足限制当且仅当存在完美匹配。

那么我们 $7^3$ 次枚举所有可能的 $(S(1),S(2),S(3))$，就能通过 Hall 定理（或者暴力匹配）得出所有满足限制的三元组。实际上可以发现只有 $k=247$ 组。

而对于所有可能的 $S(i)$，在给定 $a_1,a_2,a_3$ 的情况下，对应的 $x_i$ 的个数都是容易通过容斥 $O(1)$ 计算的（只需求出一些 $a_i$ 的 $\gcd$ 以及每个数的因数个数）。于是对应的 $(x_1,x_2,x_3)$ 的个数也容易计算。

那么对于每次询问，我们 $O(k)$ 枚举所有可能的 $(S(1),S(2),S(3))$ 三元组，以及 Burnside 中的 $6$ 种情况，加上对应的 $(x_1,x_2,x_3)$ 的个数，最后除以 $6$ 即可。复杂度 $O(w+T(k+\log w))$。

顺带一提，上面的 $(S(1),S(2),S(3))$ 是有序的，如果当成无序的话本质不同的只有 $51$ 组，而本质相同的对应的 $(x_1,x_2,x_3)$ 个数也是相同的，所以可以合并起来算，这样可以做到 $k=51$。 

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 1e5 + 5;

int tot;
int pr[N], vs[N], d[N], c[N];

struct S {
	
	int x, y, z;

	S () { }
	S (int _x, int _y, int _z) : x(_x), y(_y), z(_z) { }

};

vector<S> p;

void init(int lim) {
	d[1] = 1;
	F (i, 2, lim) {
		if (!vs[i]) {
			pr[++tot] = i, d[i] = 2, c[i] = 1;
		}
		F (j, 1, lim) {
			if (i * pr[j] > lim) {
				break;
			}
			vs[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				c[i * pr[j]] = c[i] + 1;
				d[i * pr[j]] = d[i] / (c[i] + 1) * (c[i] + 2); 
				break;
			}
			c[i * pr[j]] = 1;
			d[i * pr[j]] = d[i] * 2; 
		}
	}
	F (x, 1, 7) {
		F (y, 1, 7) {
			F (z, 1, 7) {
				int fl = 1, t[3] = { x, y, z };
				F (s, 1, 7) {
					int L = 0, R = 0;
					F (i, 0, 2) {
						if ((s >> i) & 1) {
							L++;
							R |= t[i];
						}
					}
					if (__builtin_popcount(R) < L) {
						fl = 0;
						break;
					}
				}
				if (fl) {
					p.eb(S(x, y, z));
				}
			}
		}
	}
}

void solve() {
	int a, b, c;
	cin >> a >> b >> c;
	int ab = __gcd(a, b);
	int bc = __gcd(b, c);
	int ca = __gcd(c, a);
	int abc = __gcd(ab, bc);
	ll f[8] = {
		0, 
		d[a] - d[ab] - d[ca] + d[abc],
		d[b] - d[bc] - d[ab] + d[abc],
		d[ab] - d[abc],
		d[c] - d[ca] - d[bc] + d[abc],
		d[ca] - d[abc],
		d[bc] - d[abc],
		d[abc]
	};
	ll res = 0;
	for (S i : p) {
		int x = i.x, y = i.y, z = i.z;
		res += f[x] * f[y] * f[z];
		if (x == y) {
			res += f[x] * f[z];
		}
		if (y == z) {
			res += f[x] * f[y];
		}
		if (z == x) {
			res += f[x] * f[y];
		}
		if (x == y && y == z) {
			res += 2 * f[x];
		}
	}
	cout << res / 6 << '\n';
}

bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	cin >> T, init(1e5);
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[CF1007B](https://www.luogu.com.cn/problem/CF1007B)

### 思路

显然题目要求计数 $u\mid A,v\mid B,w\mid C$。$O(n\sqrt n)$ 预处理出每个数的所有因数，记为集合 $p_i$。

容斥，记集合 $a,b,c,ab,ac,bc,all$ 为 $p_A,p_B,p_C,p_A\cap p_B,p_A\cap p_A,p_B\cap p_C,p_A\cap p_B\cap p_C$。可以用 bitset 维护交集。

首先加上 $|a||b||c|$。

- $u\in a,v\in bc,w\in bc,v\neq w$。$u,v$ 可以交换，最开始多算 $1$ 次，减去。

- $u\in abc,v\in abc,u\neq v,w\in bc\setminus all$。最开始算 $4$ 次，第一步减 $4$ 次，加上 $1$ 次。

- $u\in ab,v\in bc,w\in ac$。最开始算两次，减去 $1$ 次。

- $u,v,w\in all,u=v\neq w$。最开始算 $3$ 次，第一步减 $3$ 次，加上 $1$ 次。

- $u,v,w\in all$，$u,v,w$ 互不相等。最开始算 $6$ 次，第一步减 $3\times 3$ 次，加上 $4$ 次。

观察到 $2^3\times 3^3\times 5\times 7\times 11=83160$，所以 $|p_i|\le 128$。如果把分解因数写成先分解质因数再 dfs 求因数，复杂度 $O(n)$，常数约为 $400$。

### code

```
long long  a,b,c,ans;
vector<int> p[maxn];
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
int id[maxn],tim;
bitset<385> fa,fb,fc;
void work(){
	a=read();b=read();c=read();ans=0;
	fa.reset(),fb.reset(),fc.reset();
	for(int i:p[a])id[i]=0;
	for(int i:p[b])id[i]=0;
	for(int i:p[c])id[i]=0;
	tim=0;
	for(int i:p[a])if(!id[i])id[i]=++tim;
	for(int i:p[b])if(!id[i])id[i]=++tim;
	for(int i:p[c])if(!id[i])id[i]=++tim;
	for(int i:p[a])fa[id[i]]=1;
	for(int i:p[b])fb[id[i]]=1;
	for(int i:p[c])fc[id[i]]=1;
	long long ab=(fa&fb).count(),ac=(fa&fc).count(),bc=(fb&fc).count(),all=(fa&fb&fc).count();
	a=p[a].size(),b=p[b].size(),c=p[c].size();
	// cout<<a*b*c<<" "<<a*bc*(bc-1)/2<<" "<<b*ac*(ac-1)/2<<" "<<c*ab*(ab-1)/2<<" "<<all*(all-1)<<" "<<all*(all-1)*(all-2)/6<<"\n";
	ans=a*b*c-a*bc*(bc-1)/2-b*ac*(ac-1)/2-c*ab*(ab-1)/2+all*(all-1)+4*all*(all-1)*(all-2)/6;
	ans+=all*(all-1)/2*(ab-all)+all*(all-1)/2*(ac-all)+all*(all-1)/2*(bc-all);
	ans-=(ab-all)*(bc-all)*(ac-all);
	printf("%lld\n",ans);
}
int pre[maxn],cnt;
bool vis[maxn];
int f[maxn];
void s(int n){
	for(int i=2;i<=maxn-10;i++){
		if(!vis[i])pre[++cnt]=i,f[i]=i;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;f[i*pre[j]]=pre[j];
			if(i%pre[j]==0)break;
		}
	}
}
vector<pii> val;
void dfs(int dep,int mul,int idx){
	if(dep==val.size()){
		p[idx].push_back(mul);
		return ;
	}
	for(int i=0,s=1;i<=val[dep].se;i++){
		dfs(dep+1,mul*s,idx);
		s*=val[dep].fi;
	}
}
int T;
signed main(){
	T=read();s(maxn-10);
	for(int i=1;i<=maxn-10;i++){
		int x=i;val.clear();
		while(x>1){
			int lst=f[x],num=0;
			while(f[x]==lst){
				++num;
				x/=f[x];
			}
			val.push_back({lst,num});
		}
		dfs(0,1,i);
	}
	while(T--)work();
}
```

---

