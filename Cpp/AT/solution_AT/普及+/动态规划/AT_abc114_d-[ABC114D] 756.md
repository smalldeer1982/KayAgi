# [ABC114D] 756

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc114/tasks/abc114_d

整数 $ N $ が与えられます。$ N! $ $ (=\ 1\ \times\ 2\ \times\ ...\ \times\ N) $ の約数のうち、*七五数* は何個あるでしょうか？

ここで、七五数とは約数をちょうど $ 75 $ 個持つ正の整数です。

## 说明/提示

### 注記

正の整数 $ A $ が正の整数 $ B $ を割り切るとき、$ A $ を $ B $ の *約数* といいます。 例えば、$ 6 $ の約数は $ 1,2,3,6 $ の $ 4 $ 個です。

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ N $ は整数である。

### Sample Explanation 1

$ 9!\ =\ 1\ \times\ 2\ \times\ ...\ \times\ 9\ =\ 362880 $ の約数に七五数はありません。

### Sample Explanation 2

$ 10!\ =\ 3628800 $ の約数のうち、七五数であるのは $ 32400 $ の $ 1 $ 個です。

## 样例 #1

### 输入

```
9```

### 输出

```
0```

## 样例 #2

### 输入

```
10```

### 输出

```
1```

## 样例 #3

### 输入

```
100```

### 输出

```
543```

# 题解

## 作者：雨伞CKY (赞：9)

# 符号约定
1. 在数学中，我们用 $\prod$ 表示求积运算，例如，可以使用 $\prod \limits ^{n}_{k=1}a_{k}$ 表示 $a_{1}\cdot a_{2}\cdot a_{3}\dotsm a_{n}$。

2. 为行文方便，$S_{i}$ 表示质因数出现次数大于等于 $i$ 的质因数的个数。

# 题目分析
我们可以通过分解质因数和排列组合推理出一个数因数个数的求法。对于任何一个大于 $1$ 的自然数 $M$，如果 $M$ 不为质数，那么 $M$ 可以唯一分解成有限个质数 $P_{1},P_{2},P_{3},\dotsc ,P_{n}$ 的乘积：$M=\prod \limits ^{n}_{k=1}P^{a_{k}}_{k}$，这样的分解称为 $M$ 的标准分解式。

所以，$M$ 的任意一个因数都可以表示为 $\prod \limits ^{n}_{k=1}P^{b_{k}}_{k}(0\leq b_{1}\leq a_{1},0\leq b_{2}\leq a_{2},0\leq b_{3}\leq a_{3},\dotsc ,0\leq b_{n} \leq a_{n})$。所以，$M$ 有 $\prod \limits ^{n}_{k=1}(a_{k}+1)$ 个因数。

因此，**当且仅当一个数能用三个不同的质数 $p,q,r$ 表示为 $p^{74}$，$p^{14}\cdot q^{4}$，$p^{24}\cdot q^{2}$ 或 $p^{4}\cdot q^{4}\cdot r^{2}$ 表示时，这个数恰有 $75$ 个因数**。我们的程序可以先对 $N!$ 分解质因数，并记录分解后各个质因数的表示为幂的形式时的次数，再遍历查询质因数超过对应次数的质因数并计算。

对于计算，实际也是排列组合。
- 能表示为 $p^{74}$ 的数的个数，就是出现次数大于等于 $74$ 的质因数的个数，即 $S_{74}$。
- 能表示为 $p^{14}\cdot q^{4}$ 的数的个数，是出现次数大于等于 $14$ 的质因数的个数和可选的出现次数大于等于 $4$ 的质因数的个数之积。而出现次数大于等于 $14$ 的质因数也包括在出现次数大于等于 $4$ 的质因数内，所以需要舍去两个质因数相同的情况，即有 $S_{14}\cdot (S_{4}-1)$ 个数能表示为 $p^{14}\cdot q^{4}$。
- 同理，能表示为 $p^{24}\cdot q^{2}$ 的数有 $S_{24}\cdot (S_{2}-1)$ 个。
- 同理，去除重复的情况后，能表示为 $p^{4}\cdot q^{4} \cdot r^{2}$ 的数有 $\frac{S_{4}\cdot (S_{4}-1)\cdot (S_{2}-2)}{2}$ 个。

根据算数基本定理（唯一分解定理），上述的枚举不存在重复现象或遗漏现象。

# 代码
```cpp
#include <iostream>
using namespace std;

int N,A[110];
//A[i] 表示 i 作为质因数出现的次数

void decompose(int num){
    //对 num 分解质因数，并存储在数组 A 中
    for (int i = 2;;i++){
        while (num % i == 0){
            A[i]++;
            num /= i;
        }
        if (num == 1) return ;
    }
}

int S(int num){
    //遍历查询质因数出现次数大于等于 num 次的质因数的个数
    int cnt = 0;
    for (int i = 2;i <= N;i++){
        if (A[i] >= num) cnt++;
    }
    return cnt;
}

int main(){
    cin >> N;
    for (int i = 2;i <= N;i++) decompose(i);
    cout << S(74) + S(24) * (S(2) - 1) + S(14) * (S(4) - 1) + S(4) * (S(4) - 1) * (S(2) - 2) / 2;
}
```

[AC 记录：Submission #24388692 - AtCoder](https://atcoder.jp/contests/abc114/submissions/24388692)

---

## 作者：Liuhy2996 (赞：5)

### 思路
由于 $N\le100$，所以最多有 $25$ 个质因子，直接将 $N$ 因式分解即可。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int p[26]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97},n,a[26],cnt;
int main(){
	cin>>n;
	for(int i=1;i<26;++i){
		int k=n;
		while(k) k/=p[i],a[i]+=k;
	}
	if(a[1]>=74) cnt=1; //一个质因子的情况，该质因子只能是2 
	for(int i=1;i<26;++i)
		for(int j=1;j<26;++j) cnt+=(i!=j&&a[i]>=4&&a[j]>=14)+(i!=j&&a[i]>=2&&a[j]>=24); //两个质因子的情况
	for(int i=1;i<26;++i)
		for(int j=1;j<26;++j)
			for(int k=1;k<j;++k) cnt+=(i!=j&&i!=k&&a[i]>=2&&a[j]>=4&&a[k]>=4); //三个质因子的情况
	cout<<cnt;
	return 0;
}
```

---

## 作者：szh_AK_all (赞：3)

### 前置知识
对于一个正整数 $x$，若可以将它分解为 $x=\prod p_i^{a_i}$ 的形式，则 $x$ 的因子的数量为 $\prod (a_i+1)$。可以根据组合原理得出，对于 $x$ 的每个质因子 $p_i$，可以选择贡献 $p_i^0,p_i^1\dots p_i^{a_i}$ 这些值作为某个因子。

### 分析
现将 $1\sim n$ 这些数所包含的质因子记录下来，也就是间接地将 $n!$ 分解为 $\prod p_i^{a_i}$ 的形式。而我们同样要从中选出若干个质因子，使得 $\prod (b_i+1)=75$，其中 $b_i$ 代表选出的质因子 $p_i$ 的指数，显然，$b_i\le a_i$。

又因为 $75=5\times 15=5\times 3\times 5=25\times 3=1\times 75$，所以只需要分别考虑这 $4$ 中指数拆分方案的方案数即可，也就是要记录指数 $a_i\ge2,4,14,24,74$ 的 $p_i$ 的数量。

### 细节
计算方案数时要注意一些细节。例如，在计算 $5\times 3\times 5$ 的拆分方案数时，设 $t2,t4$ 分别表示指数 $a_i\ge 2,4$ 的 $p_i$ 的数量，则方案数应为 $C_{t_4}^2\times (t_2-1)$，因为从 $t_4$ 个可选的 $p_i$ 中选出 $2$ 个的方案数为 $C_{t_4}^2$，而在 $t_2$ 个可选的 $p_i$ 中选出 $1$ 个的方案数为 $t_2$，又因为符合 $a_i\ge 2$ 的 $p_i$ 的数量包含了符合 $a_i\ge4$ 的 $p_i$ 的数量，所以为了避免与选出的两个符合 $a_i\ge4$ 的 $p_i$ 重复，所以在计算方案数时，$t_2$ 应减去 $2$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int vis[105], pri[105], tot;
int k[105];

int c(int n) {
	return n * (n - 1) / 2;
}

signed main() {
	int n;
	cin >> n;
	for (int i = 2; i <= n; i++) {
		if (!vis[i])
			pri[++tot] = i;
		for (int j = 1; j <= tot && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0)
				break;
		}
	}
	//75=5*15=5*3*5=25*3=1*75
	for (int i = 2; i <= n; i++) {
		int x = i;
		for (int j = 2; j * j <= x; j++) {
			while (x % j == 0) {
				k[j]++;
				x /= j;
			}
		}
		if (x)
			k[x]++;
	}
	int t2 = 0, t4 = 0, t24 = 0, t14 = 0, t74 = 0;
	for (int i = 1; i <= tot; i++) {
		int x = pri[i];
		if (k[x] >= 2)
			t2++;
		if (k[x] >= 4)
			t4++;
		if (k[x] >= 24)
			t24++;
		if (k[x] >= 14)
			t14++;
		if (k[x] >= 74)
			t74++;
	}
	int ans = (t4 - 1) * t14 + c(t4) * (t2 - 2) + t24 * (t2 - 1) + t74;
	cout << ans;
}
```

---

## 作者：Nightingale_OI (赞：2)

### 大意

求有多少个 $ n ! $ 的因数 $ x $ ，使得 $ x $ 恰好有 $ 75 $ 个因数。

### 思路

由于 $ n \leq 100 $ ，所以 $ n ! $ 只有 $ 25 $ 个质因数。

如果一个数 $ x $ 有 $ 75 $ 个因数，那么 $ x $ 的质因数分解有以下情况：

1.  $ x = a^2 \times b^4 \times c^4 $ 。

2.  $ x = a^2 \times b^{24} $ 。

3.  $ x = a^4 \times b^{14} $ 。

4.  $ x = a^{74} $ 。

分解 $ n ! $ 并枚举一下情况即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int a[26];
int p[26]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int main(){
    cin>>n;
    m=25;
    f(i,1,n)f(j,1,m){
        s=i;
        while(s%p[j]==0){
            s/=p[j];
            ++a[j];
        }
    }
    f(i,1,m)f(j,1,m)f(k,j,m)l+=(i!=j && i!=k && j!=k && a[i]>=2 && a[j]>=4 && a[k]>=4);
    f(i,1,m)f(j,1,m)l+=(i!=j && a[i]>=2 && a[j]>=24)+(i!=j && a[i]>=4 && a[j]>=14);
    f(i,1,m)l+=(a[i]>=74);
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：PDAST (赞：2)

## 题意
就是求 $N$ 的阶乘的因数中有多少个有 $75$ 个因数的数。
## 思路
题意是简洁明了，模拟是不可能的了，一百的阶乘光高精度都得寄，所以数学应该一目了然了，但怎么个数学法呢？质因数分解就不用说了，剩下的呢？这时，你应该想起你~~幼儿园小班~~初中就学过的求因数个数的办法,按使用方法的话，应该叫指数加一相乘法，具体看[这里](https://www.zhihu.com/question/50757823)，求因数有 $75$ 个数的数就行了。
## Code
[AC 代码](https://www.luogu.com.cn/record/153770536)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1001],k,t[101],v[6];
int fact(int n){
	int s=1;
	for(int i=1;i<=n;i++){
		s*=i;
	}
	return s;
}
signed main(){
	int n,s=0;
	cin>>n;
	for(int i=2;i<=n;i++){
		int tmp=i;
		for(int j=2;j<=i;j++){
			while(tmp>1&&tmp%j==0){
				a[++k]=j;
				tmp/=j;
			}
		}
		if(tmp==i){
			a[++k]=i; 
		}
	}
	sort(a+1,a+k+1);
	for(int i=1;i<=k;i++){
		t[a[i]]++;
	}
	for(int i=1;i<=100;i++){
		if(t[i]>=74)v[5]++;
		if(t[i]>=24)v[4]++;
		if(t[i]>=14)v[3]++;
		if(t[i]>=4)v[2]++;
		if(t[i]>=2)v[1]++;
	} 
	s=v[5]+v[3]*(v[2]-1)+v[4]*(v[1]-1)+(fact(v[2])/fact(v[2]-2)/fact(2))*(v[1]-2);
	cout<<s;
	return 0;
}
```

---

## 作者：Anby_ (赞：1)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/AT_abc114_d)。
## 大意
找出 $n$ 的多少因数 $a$，使得 $a$ 的因数个数为 $75$。
## 思路
众所周知，一个数 $a$ 可以表示为多个素数的乘积，记作：
$$
a=\displaystyle\prod_{i=1}^{n} P_{i}^{k_i}
$$
其中，$P$ 是 $a$ 的质因数，$k$ 是该质因数的次数。  
所以，我只需让 $n!$ 几个质因数的积等于 $75$ 即可。

### 打表机
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int cnt,ot,a[100],endd=2,b3,b5,b15,b25,b75;
int main(){
	freopen("out.txt","w",stdout);
	cout<<"int a[110]={0";
	for(int i=1;i<=100;i++){
		int l=i;
		for(int j=2;j<=97;j++){
			while(!(l%j)){
				endd=max(endd,j),a[j]++,l/=j,cnt++;
				b3+=a[j]==2,b5+=a[j]==4,b15+=a[j]==14,b25+=a[j]==24,b75+=a[j]==74;
			}
		}
		cout<<","<<((b5*(b5-1))/2*(b3-2)+b25*(b3-1)+b15*(b5-1)+b75);
	}
	cout<<"};";
	return 0;
}

```
### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int n,a[110]={0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3,3,3,8,8,11,11,11,11,14,14,32,32,35,35,35,35,42,42,42,42,49,49,49,49,49,49,75,75,86,86,86,86,86,86,123,123,131,131,131,131,148,148,153,153,170,170,170,170,170,170,227,227,227,227,227,227,250,250,323,323,324,324,324,324,354,354,354,354,384,384,384,384,384,391,491,491,529,529,529,529,529,529,543};
int main(){
	cin>>n;
	cout<<a[n];
	return 0;
}

```

---

## 作者：Kyl_in_2024 (赞：1)

### 前言

学校比赛做对了的都是绿，黄的一题没做出来。

### 思路

~~死去的~~小奥知识突然开始攻击我。。。

假设 $x$ 刚好有 `75` 个因数。

```
75=3*5*5=3*25=5*15=75
```

那么 $x$ 可以拆成 $a^{3-1} \times b^{5-1} \times c^{5-1}$，$a^{3-1} \times b^{25-1}$，$a^{5-1} \times b^{15-1}$，$a^{75-1}$ 这四种方式，其中，$a$，$b$，$c$ 为**质数**。

如果单纯从 `1` 乘到 `n` 再求质因数的话肯定不可取，所以可以单个单个算。而且都是质因数，没有需要两个乘起来才能算的方式。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int cnt[105];
bool pd(int x){//质数判断 
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0) return 0;
	}
	return 1;
}
signed main(){
	int n,ans=0,ans2=0,ans4=0,ans14=0,ans24=0;//ansxx代表出现次数大于xx的质因数有多少 
	cin >> n;
	for(int i=2;i<=n;i++){
		for(int j=2;j<=i;j++){//把n!大卸八块！！ 
			int tmp=i;
			while(tmp%j==0){//这里的j不一定是质数，但是懒得判了
				tmp/=j;
				cnt[j]++;
			}
		}
	}
	for(int i=2;i<=n;i++){
		if(pd(i)){
			if(cnt[i]>=2) ans2++;
			if(cnt[i]>=4) ans4++;
			if(cnt[i]>=14) ans14++;
			if(cnt[i]>=24) ans24++;
			if(cnt[i]>=74) ans++;//注意纯74在这里统计了 
		}
	}
	ans+=(ans4*(ans4-1)/2*(ans2-2))+(ans14*(ans4-1))+(ans24*(ans2-1));//因为不能用两遍，所以后面要-1 
	cout<<ans;
	return 0;
} 
```

[AC 记录](https://atcoder.jp/contests/abc114/submissions/51916919)

---

## 作者：shuangmu (赞：1)

[题目链接](https://atcoder.jp/contests/abc114/tasks/abc114_d)

## 题意

给定一个数 $n$，求 $n!$ 的因数中，刚好有 $75$ 个因数的数的个数。

## 分析

首先有这样一个性质，对于一个数 $a$，我们将其分解质因数，即

$$a =  \prod_{i = 1}^{n} p_i^{k_i}$$

那么，$a$ 的因数个数就是

$$sum =  \prod_{i = 1}^{n} (k_i+1)$$

简单证明一下，对于第 $i$ 个质因数，可以选 $[0, k_i]$ 个，所以最终能组合出来的不同因数就是 $sum$ 个。

题干要求因数个数为 $75$ 的因数，首先考虑什么样的数有 $75$ 个因数——没错，我们将 $75$ 分解因数，发现

$75 = 5 \times 5 \times 3$，则 $a= p_1^4 p_2^4 p_3^2 $；

同理，

$75 = 5 \times 15$，$a= p_1^{4} p_2^{14} $

$75 = 25 \times 3$，$a= p_1^{24} p_2^2 $

$75 = 75 \times 1$，$a= p_1^{74}$

因为 $n!$ 的质因数包括了其所有因数的质因数，而每种质因数组合只能确定一个数，故我们可以直接考虑每种情况如何构造出 $a$。我们令 $s_i$ 表示，个数大于等于 $i$ 的质因数个数。因为多余的数没有用，所以这里我们直接考虑大于等于的数。

那么，对于第一种情况，对答案的贡献为 $C_{s_4}^2 \times(s_2-2)$；

同理，第二种的贡献 $s_{14}\times (s_{4}-1)$；

第三种的贡献 $s_{24}\times (s_2-1)$；

第四种的贡献 $s_{75}$。

最后看数据范围。$n$ 不太大，可以考虑对 $1$ 到 $n$ 的数分解质因数，那么 $n!$ 的质因数分解就是对 $[1, n]$ 的数的质因数的指数做前缀和。最后的答案就是将以上四种贡献加起来。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 305;
int n;
int a[105][105];
bool vis[105];
int pr[105], tot;
void init(){
	for(int i = 2; i<=100; i++){
		if(vis[i]) continue;
		vis[i] = 1, pr[++tot] = i;
		for(int j = i; j<=100; j+=i){
			vis[j] = 1;
		}
	}//数据范围很小很小所以简单筛一下质数就行。
	for(int i = 2; i<=100; i++){
		int tmp = i;
		for(int j = 1; j<=tot; j++){
			if(tmp%pr[j] == 0){
				while(tmp%pr[j] == 0){
					tmp/=pr[j];
					a[i][j]++;//对1~100内的数分解质因数。
				}
			}
		}
	}
}
int f[N];
int sum[N]; 
int ts[N];
int main(){
	scanf("%d", &n);
	init();
	for(int i = 1; i<=n; i++){
		for(int j = 1; j<=tot; j++){
			sum[j]+=a[i][j];//求n!因数分解后质因数的指数。
		}
	}
	int ans = 0;
	int L = 0, R = 0, Y = 0;
	sort(sum+1, sum+1+tot, greater<int>());
	for(int i = 1; i<=tot; i++){
		if(sum[i]>=24){
			ts[24]++;
		}
		if(sum[i]>=14){
			ts[14]++;
		}
		if(sum[i]>=74){
			ts[74]++;
		}
		if(sum[i]>=4){
			ts[4]++;
		}
		if(sum[i]>=2){
			ts[2]++;
		}
	} 
	if(ts[74]){
		ans+=ts[74];
	}
	if(ts[24]){
		ans+=ts[24]*(ts[2]-1);
	}
	if(ts[14]){
		ans+=(ts[14]*(ts[4]-1));
	}
	if(ts[4]){
		ans+=(ts[4]*(ts[4]-1)/2*(ts[2]-2));
	}

	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：wyc0607 (赞：0)

闲话：

对于这道题，我第一眼看到时，觉得是高精度，于是就开开心心地写了 20 分钟的高精度，结果 $1 \le N \le 100$，orz。

正解：

我突然想起小奥学过的因数个数定理：对于 $$x=a_{1}^{b_{1}} \times a_{2}^{b_{2}} \times a_{3}^{b_{3}} \times...\times a_{N}^{b_{N}}$$，$x$ 的因数个数为 $$(b_{1}+1) \times (b_{2}+1) \times (b_{3}+1) \times ... \times (b_{N}+1)$$，而又 $100!$ 的质因数最大不超过 $100$，于是就枚举 $N!$ 的每个质因数个数，再根据公式推导即可。

代码中的变量解释:

$pr_{i}$：100 以内第 $i$ 个质数。

$a_{i}$：$n!$ 中第 $pr_{i}$ 个质数的次方数。

$ans$：答案。

```cpp
#include<bits/stdc++.h>
#define int long long
#define IAKIOI ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
int pr[26]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};//100 以内的所有质数。
int n,ans=0,a[26]; 
main(){
	IAKIOI//卡常。 
	cin>>n;
	for(int i=1;i<=25;i++){//枚举每个质数的次方数。 
		int p=n;
		while(p){
			p/=pr[i]; 
			a[i]+=p;//如满足条件，次方数+=k。 
		} 
	}
	if(a[1]>73) ans++;//如果有 74 个 2 ，即有一个数为 2 的 75 次方，ans++。 
	for(int i=1;i<=25;i++) for(int j=1;j<=25;j++){
		if(i!=j&&a[i]>=4&&a[j]>=14) ans++;//如果一个数为 a 的 4 次方及以上，b 的 14 次方及以上，ans++（据公式）。 
		if(i!=j&&a[i]>=2&&a[j]>=24) ans++;//如果一个数为 a 的 2 次方及以上，b 的 24 次方及以上，ans++（据公式）。
	}
	for(int i=1;i<=25;i++) for(int j=1;j<=25;j++) for(int k=1;k<j;k++) if(i!=j&&j!=k&&i!=k&&a[i]>=2&&a[j]>=4&&a[k]>=4) ans++;//如果一个数为 a 的 2 次方及以上,b 的 4 次方及以上，c 的 4 次方及以上，ans++（据公式）。
	cout<<ans;//输出，完结撒花。 
}

---

## 作者：Breath_of_the_Wild (赞：0)

众所周知，一个正整数 $n$ 可以被唯一分解为 $p_1^{c_1}\times p_2^{c_2}\times \cdots \times p_k^{c_k}$，即
$$\tag{1}\prod_{i=1}^{k}p_i^{c_i}$$
其中 $p_i(i=1,2,\cdots k)$ 为质数。那么这个数的因数个数为 $(c_1+1)(c_2+1)\cdots (c_k+1)$，即
$$\tag{2}\prod_{i=1}^{k}(c_i+1)$$
那么回到题目，既然要求 $N$ 的因数中 $75$ 个因数的个数，不妨根据 $(2)$ 式来分讨每个质因数的指数。

因为 $75=75=3\times 5\times 5=5\times 15=3\times 25$，因此有 $75$ 个因数的数可表示为 $p_1^{74}$、$p_1^2\times p_2^4\times p_3^4$、$p_1^4\times p_2^{14}$ 或 $p_1^{2}\times p_2^{24}$。

由于 $N\le 100$，于是可以将 $N!$ 暴力地拆解其质因数，并统计每个质因数出现的次数。

最后算答案的时候注意一下不要算重。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=111;
int n,tot[N],a2,a4,a14,a24,a74;
bool Chk(int x){
	for(int i=2;i*i<=x;i++) if(x%i==0) return 0;
	if(x>1) return 1;
	return 0;
}
int main(){
	cin>>n;
	// 拆 N! 质因数 
	for(int i=2;i<=n;i++){
		for(int j=2;j<=i;j++){
			int cur=i;
			while(cur%j==0){     
				cur/=j;
				tot[j]++;
			}
		}
	}
	// 统计每种个数 
	for(int i=2;i<=n;i++){
		if(Chk(i)){
			if(tot[i]>=2) a2++;
			if(tot[i]>=4) a4++;
			if(tot[i]>=14) a14++;
			if(tot[i]>=24) a24++;
			if(tot[i]>=74) a74++;
		}
	}
	cout<<a74   +   (a4*(a4-1)/2*(a2-2))   +   a24*(a2-1)   +   a14*(a4-1);
	cout<<'\n';
	return 0;
}

---

## 作者：_Gabriel_ (赞：0)

### 思路

题意是求 $N!$ 的因数中有多少个七五数。

把 $75$ 分解一下，即 $75=3 \times 5^2$。

如果要让因数 $a$ 有 $75$ 个因数，则有如下几种情况：

1. $a=p_1^{\alpha_1}p_2^{\alpha_2}p_3^{\alpha_3}$，且 $(\alpha_1+1)(\alpha_2+1)(\alpha_3+1)=75$，因为 $75=3 \times 5^2$，所以 $\alpha_1,\alpha_2,\alpha_3$ 为 $2,4,4$。

2. $a=p_1^{\alpha_1}p_2^{\alpha_2}$，且$(\alpha_1+1)(\alpha_2+1)=75=3 \times25=5 \times15$，所以 $\alpha_1,\alpha_2$ 为 $2,24$ 或者 $4,14$。

3. $a=p_1^{\alpha_1}$，可知 $\alpha_1=74$。

把 $N!$ 分解之后每个因数枚举一下即可。

### 代码


```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
int a[N];
int n;

bool is_prime(int k) {
	if (k <= 1) {
		return 0;
	}
	for (int i = 2; i * i <= k; i++) {
		if (k % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
    	if (is_prime(i)) {
    		int tmp = 1, cnt = 0;
    		while (tmp * i <= n) {
    			tmp *= i;
    			cnt += n / tmp;
			}
			a[cnt]++;
		}
	}
	for (int i = 100; i >= 1; i--) a[i] += a[i + 1];
	cout << a[74] + a[4] * (a[4] - 1) / 2 * (a[2] - 2) + a[24] * (a[2] - 1) + a[14] * (a[4] - 1);
    return 0;
}
```

---

