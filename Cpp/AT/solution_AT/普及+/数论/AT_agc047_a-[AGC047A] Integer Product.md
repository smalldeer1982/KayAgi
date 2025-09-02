# [AGC047A] Integer Product

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc047/tasks/agc047_a

$ N $ 個の実数 $ A_1,\ A_2,\ \ldots,\ A_N $ が与えられます。添字のペア $ (i,\ j) $ ($ i\ <\ j $) であって、積 $ A_i\ \cdot\ A_j $ が整数であるようなものの個数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200\,000 $
- $ 0\ <\ A_i\ <\ 10^4 $
- $ A_i $ は小数部の桁数が $ 9 $ 以下であるような数として与えられる。

### Sample Explanation 1

積が整数であるようなペアは以下の $ 3 $ 個です。 - $ 7.5\ \cdot\ 2.4\ =\ 18 $ - $ 7.5\ \cdot\ 16\ =\ 120 $ - $ 17\ \cdot\ 16\ =\ 272 $

## 样例 #1

### 输入

```
5
7.5
2.4
17.000000001
17
16.000000000```

### 输出

```
3```

## 样例 #2

### 输入

```
11
0.9
1
1
1.25
2.30000
5
70
0.000000001
9999.999999999
0.999999999
1.000000001```

### 输出

```
8```

# 题解

## 作者：Hisaishi_Kanade (赞：8)

思路和标程类似，但是没用 `map`。

首先 $n^2$ 暴力显然~~不过我不敢保证你会不会被卡掉精度~~

看到数据范围果断想低于 $n^2$ 的做法。

小数点后不超过 $9$ 位，这能给我们什么启示？

将每个 $A_i$ 乘上 $10^9$，记为 $B_i$。容易发现若 $A_i\times A_j$ 为整数，$10^{18}\mid B_i\times B_j$。

而小学数学告诉我们，若一个数有 $m$ 个因子 $2$，$n$ 个因子 $5$，它末尾零的个数为 $\min(m,n)$。

标程使用 `map`，但是实际上这个数字并不大，直接用桶记录。

```cpp
#include <map>
#include <stdio.h>
long long f[50][50];
int n,i,j,p,q,cnt1,cnt2;
long long mid,res;
long double x;
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	{
		cnt1=cnt2=0;
		scanf("%Lf",&x);
		mid=(long long)(x*1000000000+0.5);
		while(mid%2==0)
		{
			++cnt1;
			mid/=2;
		}
		while(mid%5==0)
		{
			++cnt2;
			mid/=5;
		}
		++f[cnt1][cnt2];
	}
	for(i=18;i<=90;++i)
	{
		for(j=18;j<=90;++j)
		{
			for(p=0;p<45&&p<=i;++p)
			{
				for(q=0;q<45&&q<=j;++q)
				{
					if(i-p>44||j-q>44)
						continue;
					if(i!=2*p||j!=2*q)
						res+=f[p][q]*f[i-p][j-q];
					else
						res+=f[p][q]*(f[p][q]-1);
				}
			}
		}
	}
	printf("%lld",res>>1);
	return 0;
}
```
- - -

写挂时参考了[网上题解](https://www.codeleading.com/article/14394608618/)和[官方题解](https://atcoder.jp/contests/agc047/editorial/36)。

表示膜拜。

---

## 作者：suzhikz (赞：4)

套路数学题。

首先小数非常糖，肯定直接把他变成整数，直接乘上 $10^9$ ，注意这里要手写快读，不然你的精度将会掉光光。

然后想要把小数变成整数就是要乘 $10$，所以我们把每个数分解质因数，看 $2$ 和 $5$ 的因数，如果两个数的 $2$ 的因数个数和和 $5$ 的因数个数和的最小值大于等于 $18$，我们就能把这玩意变回整数。

开个桶记一下即可，好写又好调。

记得手写快读，否则精度掉光光。

记得手写快读，否则精度掉光光。

记得手写快读，否则精度掉光光。

---

## 作者：hermione_wqx (赞：2)

- 先将小数转成整数，再算这个整数有几个因数 $2$ 和因数 $5$，用 $flag$ 标记好这个小数有多少个因数 $2$ 和因数 $5$，负数也是一样的。

 - 本题数据只有 $10^4$，可以过。（**注意要开 long long**）


# 代码：

```cpp

# include<bits/stdc++.h>
using namespace std;
const int N = 10e5+5; 
long long n;
string s[N];
long long num_5[N],num_2[N];
pair<int,int> find(string s){
	long long len=s.size();
	long long id=0;
	bool flag=true;
	for (long long i=0;i<len;++i)
	{
		if (s[i]=='.')
		{
			flag=false;
			id=i;
			break;
		}
	}
	if (flag!=0) 
	    if (flag) return make_pair(0,s.size() - 1);
	for (long long i = len - 1;i >= 0;i--){
		if (s[i]!='0') return make_pair(id,i);
		if (s[i]=='.') return make_pair(0,i-1);
	}
}
long long get_num(string s,long long ky){
	long long num=0;
	for (long long i=0;i<=ky;++i){
		if (s[i]!='.') num=num*10+(s[i]-'0');
	}
	return num;
}
long long a[2*50+5][2*50+5];
int main(){
	cin>>n;
	long long zheng=0;
	for (long long i=1;i<=n;++i)
	{
		cin>>s[i];
		pair<int,int> find_i=find(s[i]); 
		if (find_i.first==0) zheng++;
		long long ky=find_i.second-find_i.first;
		if (find_i.first == 0)ky=0;
		long long num = get_num(s[i],find_i.second);
		num_2[i]-=ky;num_5[i]-=ky;
		while (num%5==0) num/=5,num_5[i]++;
		while (num%2==0) num/=2,num_2[i]++;
		a[num_5[i]+50][num_2[i]+50]++;
	}
	long long sum(0);
	long long ans(0);
	for (long long i=0;i<=2*50;++i)
	{
		for (long long j=0;j<=2*50;j++)
		{
			for (long long k=2*50-i;k<=2*50;k++)
			{
				for (long long l=2*50-j;l<=2*50;l++){
					
					if(i==k&&j==l)
					{
						sum+=a[i][j]*(a[i][j]-1)/2;
						continue;
					}
					sum+=a[i][j]*a[k][l];
					ans+=a[i][j]*a[k][l];
				}
			}
		}
	}
	std::cout<<sum-ans/2<<endl;
}

谢谢审核的管理员，您辛苦了！

---

## 作者：Hacker_Cracker (赞：1)

## [AGC047A] Integer Product 题解
### Solution
首先两个 $9$ 位的实数相乘，肯定会出现精度误差。

像[这道题](https://www.luogu.com.cn/problem/P8972)一样，由于题目保证小数位最多为 $9$，我们考虑将所有的小数 $a_i$ 乘上 $10^9$，记此时的序列为 $b_i$。此时判断两数相乘是否为整的方法就是判断其乘积是不是 $10^{18}$ 的倍数。

如何判断？首先对每个 $b_i$ 进行质因数分解。记其质因数 $2$ 的个数为 $x$，质因数 $5$ 的个数为 $y$。此时它是 $10$ 的 $\min(x,y)$ 倍。

同理，两数的乘积，我们只需要计算出 $\min(x_1+x_2,y_1+y_2)$ 就可以得出它是 $10$ 的多少倍了。

解决过程：
- 首先对每个输入的 $a_i$ 处理变成 $b_i$。然后对 $b_i$ 质因数分解，开个 map 存储 $x_i$ 和 $y_i$。
- 然后两层循环枚举每一对 $(x,y)$。记 $(x_i,y_i)$ 的个数为 $z_i$，记 $(x_j,y_j)$ 的个数为 $z_j$。
- 判断 $x_i+x_j \ge 18$ 且 $y_i+y_j \ge 18$。如果符合条件，分两种情况讨论：
- 第一种，若 $x_i \le x_j$ 且 $y_i<y_j$，那么对答案的贡献为 $z_i \times z_j$。
- 第二种，若 $x_i=x_j$ 且 $y_i=y_j$，此时相当的在若干相同的数中任选 $2$ 个，对答案的贡献为 $\displaystyle{C_{z_i}^{2}}=\cfrac{z_i(z_i-1)}{2}$。

然后我们发现我们愉快地 [TLE](https://atcoder.jp/contests/agc047/submissions/62473072) 了。

原因是我们对 $b_i$ 做了太多的对答案没有贡献的分解。事实上，我们只需要找到质因子 $2$ 和 $5$ 的个数，其他的就不用分解了。

可能有人会问，为什么对 map 的两层循环不会 T？这是因为数对 $(x,y)$ 的个数不会超过 $\log_2^{10^{13}} \times \log_{5}^{10^{13}}$ 个。

最后：记得开 long long。要不然 AtCoder 的评测机会给你一个鲜艳的 [WA](https://atcoder.jp/contests/agc047/submissions/62473119)。
### [Accepted Code](https://atcoder.jp/contests/agc047/submissions/62473766)
```cpp
#include<iostream>
#include<map>
#include<cmath>
#define ll long long
using namespace std;
typedef pair<ll,ll> pii;
const int N=2e5+10;
const ll P=1e9;
ll a,res;
double x;
int n;
map<pii,ll>m;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf",&x);
		a=round(x*P);
		ll d=2,cnt2=0,cnt5=0;
		while(a%2==0){
			cnt2++;
			a>>=1;
		}
		while(a%5==0){
			cnt5++;
			a/=5;
		}
		m[make_pair(cnt2,cnt5)]++;
	} 
	for(auto i:m){
		for(auto j:m){
			if(i.first.first+j.first.first>=18&&i.first.second+j.first.second>=18){//10^18是a*b的约数 
				if(i<j) res+=i.second*j.second;
				else if(i==j) res+=i.second*(j.second-1)/2;
				//如果 i>j，那么就重复计算了 
			}
		}
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc047_a)。


## 思路

考虑将所有 $a_i$ 乘上 $10^9$，那么条件就转换成了 $a_ia_j\equiv 0\pmod {10^{18}}$，考虑求出最小的 $x$ 使得 $a_ix\equiv 0\pmod {10^{18}}$，那么 $a_ia_j\equiv 0\pmod {10^{18}}$ 当且仅当 $x\mid a_j$，显然有 $x=\frac{10^{18}}{\gcd(10^{18},a_i)}$，由于 $10$ 只有 $2,5$ 两个质因子，也就是我们只需处理这两个质因子即可，接下来随便计数即可。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n;
const int Maxn=2e5+7;
const int N=1e9;
const ll NN=1ll*N*N;
const double eps=1e-11;

ll num,a[Maxn];
int G[100][100];
ll ans;

ll kgcd(ll x,ll y){
	return !y?x:kgcd(y,x%y);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		double x;
		scanf("%lf",&x);
		ll num=llround(x*1e9);
		a[i]=num;
		ll kp=NN/kgcd(NN,a[i]);
		ll k2=0,k5=0;
		while(a[i]%2==0) k2++,a[i]/=2;
		while(a[i]%5==0) k5++,a[i]/=5;
		
		int res=0;
		for(int ir=0;ir<=k2;ir++)
			for(int jr=0;jr<=k5;jr++)
				res+=G[ir][jr];
		ans+=res;
		k2=0,k5=0;
		while(kp%2==0) k2++,kp/=2;
		while(kp%5==0) k5++,kp/=5;
		
		G[k2][k5]++;
	}
	printf("%lld",ans);
	
	
	return 0;
}

```

---

## 作者：xukehg (赞：0)

简单题。

把一个小数变成整数的方法就是不断乘十，因此我们可以先把小数转整数，然后在计算得到的整数含有几个因数 $2$ 和因数 $5$，记录这个小数有多少个因数 $2$ 和因数 $5$（负数理解为欠了多少个因数）。于是两个数乘积为整数相当于两个数因数 $2$ 和 $5$ 的总数大于大于等于 $0$，由于小数只有 $10^4$，因此一个数拥有的因数 $2$ 的个数实际很少。

代码：
```cpp
#include <bits/stdc++.h>
#define  int long long
using namespace std;
const int N = 2e5 + 5,M = 50;

int n;
string s[N];
int num_5[N],num_2[N];
pair<int,int> find(string s){
	int len = s.size();
	int id = 0;
	bool flag = true;
	for (int i = 0;i < len;i++){
		if (s[i] == '.'){
			flag = false;
			id = i;
			break;
		}
	}
	if (flag) return make_pair(0,s.size() - 1);
	for (int i = len - 1;i >= 0;i--){
		if (s[i] != '0') return make_pair(id,i);
		if (s[i] == '.') return make_pair(0,i - 1);
	}
}
int get_num(string s,int last){
	int num = 0;
	for (int i = 0;i <= last;i++){
		if (s[i] != '.') num = num * 10 + (s[i] - '0');
	}
	return num;
}
int a[2 * M + 5][2 * M + 5];
signed main(){
	cin >> n;
	int zheng = 0;
	for (int i = 1;i <= n;i++){
		cin >> s[i];
		pair<int,int> find_i = find(s[i]); 
		if (find_i.first == 0) zheng++;
		int last = find_i.second - find_i.first;
		if (find_i.first == 0) last = 0;
		int num = get_num(s[i],find_i.second);
		num_2[i] -= last;num_5[i] -= last;
		while (num % 5 == 0) num /= 5,num_5[i]++;
		while (num % 2 == 0) num /= 2,num_2[i]++;
		a[num_5[i] + M][num_2[i] + M]++;
	}
	int sum = 0;
	int ans = 0;
	for (int i = 0;i <= 2 * M;i++){
		for (int j = 0;j <= 2 * M;j++){
			for (int k = 2 * M - i;k <= 2 * M;k++){
				for (int l = 2 * M - j;l <= 2 * M;l++){
					if (i == k && j == l){
						sum += a[i][j] * (a[i][j] - 1) / 2;
						continue;
					}
					sum += a[i][j] * a[k][l];
					ans += a[i][j] * a[k][l];
				}
			}
		}
	}
	cout << sum - ans / 2 << endl;
}

---

## 作者：AsiraeM (赞：0)

发现当一个小数点后有 $a$ 位的数 $A$ 与一个小数点后有 $b$ 位的数 $B$ 相乘得到 $C$ 时，  
设 $i$ 和 $j$ 分别为 $A$ 和 $B$ 的因式分解中 $2$ 的次数，$k$ 和 $l$ 分别为 $A$ 和 $B$ 的因式分解中 $5$ 的次数，  
则 $C$ 小数点后的位数为 $\max(0,a+b-\min(i+j,k+l))$。  

也就是说，假设一个小数点后有 $a$ 位的数 $A$ 与一个小数点后有 $b$ 位的数 $B$ 相乘得到一个整数，  
且 $i$ 和 $j$ 分别为 $A$ 和 $B$ 的因式分解中 $2$ 的次数，$k$ 和 $l$ 分别为 $A$ 和 $B$ 的因式分解中 $5$ 的次数，  
则 $j-b\geq a-i$，$l-b\geq a-k$。  

因为 $A_i<10^{4}$，小数点后面最多不超过 $9$ 位，所以可以把每个数转成 `long long` 来存。  
分别求出每个 $A_{i}$ 的因式分解中 $2$ 和 $5$ 的次数减去小数点后面的位数（记为 $K_{i}$ 和 $L_{i}$），  
这样每个数可以看作平面直角坐标系中的一个点，给对应的位置打上标记。  

查询就是对于每个 $i$，对左下角为 $(-K_{i},-L_{i})$，右上角为 $(\infty,\infty)$ 的区域进行区间求和。用二维前缀和即可。  
可以把横纵坐标都加上一个值，避免出现下标为负的情况。当然也可以用指针。  
注意在 $A_{i}$ 为整数（也就是 $K_{i}$ 和 $L_{i}$ 都大于等于 $0$）时，会统计到自己，记得去掉。  

时间和空间复杂度都为 $O(n+\log^{2}{W})$，其中 $W$ 为 $A_{i}$ 转成 `long long` 后的最大值。  

代码：  
```cpp
//Talk is cheap.Show me the code.
#include<bits/stdc++.h>
namespace xcy{
const int MAXN=200005;
typedef long long ll;
int t[MAXN],f[MAXN],p[10]{1},s[205][205],i,j,ncnt;
ll n,k,l,ans;

inline ll fread(ll &X){X=ncnt=0;char C=getchar();while(isdigit(C))++ncnt,X=(X<<1)+(X<<3)+(C^48),C=getchar();return C;}
inline void fout(ll X){if(X<0)putchar('-'),X=-X;if(!X){putchar('0'),putchar(' ');return;}char C[25]{};ll Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}

int mian()
{
	for(i=1;i<10;++i)p[i]=p[i-1]*10;
	fread(n);
	for(i=1;i<=n;++i)
	{
		if(fread(l)=='.')
		{
			fread(k);
			t[i]=f[i]=-ncnt;//减去小数点后的位数
			l=l*p[-t[i]]+k;//转成long long
		}
		while(!(l&1))++t[i],l>>=1;//统计因式分解中2和5的个数
		while(!(l%5))++f[i],l/=5;
		++s[t[i]+80][f[i]+35];//打标记
	}
	for(i=144;i;--i)//二维前缀和
		for(j=60;j;--j)
			s[i][j]+=s[i][j+1]+s[i+1][j]-s[i+1][j+1];
	for(i=1;i<=n;++i)ans+=s[80-t[i]][35-f[i]]-(t[i]>=0&&f[i]>=0)/*避免统计到(i,i)这样的数对*/;
	fout(ans>>1);//去重
	return 0;
}}
int main(){return xcy::mian();}
```


---

