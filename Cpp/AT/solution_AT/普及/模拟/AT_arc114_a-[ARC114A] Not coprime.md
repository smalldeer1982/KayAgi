# [ARC114A] Not coprime

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc114/tasks/arc114_a

$ N $ 個の $ 2 $ 以上 $ 50 $ 以下の整数 $ X_1,\ X_2,\ \cdots,\ X_N $ が与えられます．全ての $ i\ =\ 1,\ 2,\ \cdots,\ N $ について次の条件を満たす正の整数 $ Y $ のうち，最小のものを求めてください．

- $ X_i $ と $ Y $ は互いに素でない

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 49 $
- $ 2\ \leq\ X_i\ \leq\ 50 $
- $ X_i\ \neq\ X_j\ (i\ \neq\ j) $
- 入力は全て整数

### Sample Explanation 1

$ 4 $ と互いに素でないためには偶数である必要があり，$ 3 $ と互いに素でないためには $ 3 $ の倍数である必要があります．

## 样例 #1

### 输入

```
2
4 3```

### 输出

```
6```

## 样例 #2

### 输入

```
1
47```

### 输出

```
47```

## 样例 #3

### 输入

```
7
3 4 6 7 8 9 10```

### 输出

```
42```

# 题解

## 作者：zcr0202 (赞：1)

## 题目大意

给定 $N$ 个数 $ X_1,\ X_2,\ \cdots,\ X_N $​ ，求一个最小的数 $Y$ ，使每个数 $X_i$​ 都与 $Y$ 不互质。

## 解题思路

众所周知，$50$ 以内的质数总共只有 $15$ 个，这个数字非常好，因为 $2^{15}$ 刚好不会时间超限，所以我们枚举这 $15$ 个质数的状态，是选还是不选，直接暴力即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1001;
int n;
int a[N];
int bz[N];
int su[50]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int s[N], d;
int minn = LONG_LONG_MAX;    //初始化要开大一点
void ss(int t, int k) {
    if(t == k + 1) {
        int s = 1;
        for(int i = 1; i <= 16; i++) {
            if(bz[i]) s *= su[i];
        }
        bool p = 1;
        for(int i = 1; i <= n; i++) {    //判断是否合法
            if(__gcd(s, a[i]) == 1) {
                p = 0;
                break;
            }
        }
        if(p) {
            minn = min(minn, s);
        }
        return ;
    }
    else {
        for(int i = 0; i <= 1; i++) {    //枚举
            bz[t] = i;
            ss(t + 1, k);
            bz[t] = 0;
        }
    }
}
signed main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {    //输入
        cin >> a[i];
    }
    ss(1, 15);
    cout << minn;
    return 0;
}
```

---

## 作者：Dream_poetry (赞：1)

## 翻译：
给定 $N$ 个数：$x_1$，$x_2$，$x_3$，$\dots$，$x_N$。

请求出一个数 $y$，使得序列 $x$ 中的每个元素的任一**质因子**是 $y$ 的因子。

## 思路：
先看数据范围：$2 \le x_i \le 50$。嗯，很水！

所以直接暴力，看每个质数选与不选，看看是否与所有元素不互质。如果是，更新最小值。

最后输出即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int ljlbj_fengyuwuzu[114514]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int f[500];
int a[500005];
int minn=0x3f3f3f3f;

void Dragon_Clan(int fu__men){
	int tep=0,ans=1;
	if (fu__men==16){ // 当所有的质数状态决定好后 
		for (int i=1;i<=55;i++) // 计算总乘积 
			if (f[i]==1)
				ans*=i;
		for (int i=1;i<=n;i++) // 直接算最大公因数（真好用） 
			if (__gcd(a[i],ans)>1) // 如果不互质 
				tep++; // 增加 
		if (tep==n){  // 都不互质 
			minn=min(minn,ans); // 更新 
		}
		return; // 跳出循环 
	}
	f[fu__men]=1;
	Dragon_Clan(fu__men+1);
	f[fu__men]=0;
	Dragon_Clan(fu__men+1);
}
signed main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	Dragon_Clan(1);
	cout<<minn;
	return 0;
}
```


---

## 作者：Frictional (赞：1)

我们看到数据范围，很明显可以打暴力。为 $50$ 以内的质数只有 $15$ 个，我们枚举每个质数是否选中。之后判断序列中的数是否不与质数的乘积互质，然后满足条件的取最小值就可以了。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define r rd()
#define frz(a,b,c) for(int a=b;a<=c;a++)
#define frj(a,b,c) for(int a=b;a>=c;a--)
#define wh(a,b) while(a<=b)
#define wh1 while(1)
#define gc getchar()
#define pc putchar
#define pcs putchar(' ')
#define pcen putchar('\n')
using namespace std;
int rd(){
	int x=0,f=1;
	char ch=gc;
	while(ch<48||ch>57){if(ch=='-') f=-1;ch=gc;}
	while(ch>=48&&ch<=57) x=x*10+ch-48,ch=gc;
	return x*f;
}
void wr(int x){
	if(x<0) x=-x;
	if(x>9) wr(x/10);
	pc(x%10+48);
} 
int n,x[55];
map<int,int>f[55];
int primes[17]={0,2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
int ans=1e18;
bool use[16];
void dfs(int i){
	if(i==16){
		int sum=1;
		int summ=0;
		for(int i=1;i<=15;++i){
			if(use[i]==true) sum*=primes[i];
		}
		for(int i=1;i<=n;++i){
			if(__gcd(sum,x[i])>1) summ++;
		}
		if(summ==n) ans=min(ans,sum);
		return;
	}
	use[i]=1;
	dfs(i+1);
	use[i]=0;
	dfs(i+1);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i];
    dfs(1);
    cout<<ans;
	return 0;
}
/*
3336443107998
166822155399tj90
*/
```


---

## 作者：zsh_haha (赞：0)

### 题目大意

给定 $n$ 个数，再找一个数，使找的数与这 $n$ 个数中的每个数的最大公因数不等于 $1$。

### 思路讲解

一道考验数学知识的好题。

对于一个正整数 $m$，可以得到：

$$m=p_1p_2p_3\cdots p_k$$

其中 $k$ 为正整数，$p_i$ 为质数，也是 $m$ 的质因子。

若想使两个数的最大公因数不等于 $1$，那么这两个数必须至少有一个相同的质因子。

所以我们想找的数的所有质因子必须**包含**这 $n$ 个数中每个数的所有质因子。

所以我们可以选若干个质数相乘使这些质数**包含**这 $n$ 个数中每个数的所有质因子，相乘得到的结果就是我们要找的这个数。

由于这里的 $a_i$ 范围很小，最大为 $50$，所以我们可以先列举出 $50$ 以内的所有质数，再用深搜暴力枚举得出答案。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long pri[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
long long n,a[50];
long long ans=1e18;//注意不能设1e9了 
void dfs(long long pro,int now){
	for(int i=1;i<=n;i++){
		if(__gcd(a[i],pro)==1){
			goto t1;
		}
	}
	ans=min(ans,pro);
	t1:;
	if(now==16){
		return;
	}
	dfs(pro*pri[now],now+1);
	dfs(pro,now+1);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	dfs(1,1);
	cout<<ans;
    return 0;
}
```

---

## 作者：watcher_YBH (赞：0)

# 题目大意：
求出一个最小的 $ans$，使 $ans$ 不与任何一个 $x_i$ 互质。
# 思路：
看到这道题，我们首先会想到：把每个 $x_i$ 的最小质因数乘起来就可以了。但是，这样是不对的，比如这三个数：$22,33,55$。如果按照以上方法来做，得出的答案为 $30$，但正确答案为 $11$，所以我们采用搜索。

由于我太懒了，所以我运用了一个技巧：状态压缩。因为小于 $50$ 的质数只有 $16$ 个，而 $ans$ 就是这当中几个数的乘积。这 $16$ 质数可以分为“乘”或“不乘”，分别用 $1$ 和 $0$ 来表示，所以这 $16$ 个情况就可以压缩成一个 $16$ 位的二进制数。所以，$1 \sim 2^{16}-1$ 就可以表示所有的方案。

所有方案的最小值就是 $ans$。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX = 1e5+5;
int n,ans = 1e18;
int a[MAX],pri[17] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};// 小于50的质数 
void js(int x){
	int k = 1,ans1 = 1;
	while(x){// 解压 
		if(x&1) ans1 *= pri[k];// 当前这位是1就乘 
		if(ans1>ans) return;// 超过当前最小值就不继续了 
		x>>=1,k++;// 下一位 
	}
	for(int i = 1; i<=n; i++)// 判断是否与所有数互质 
		if(__gcd(ans1,a[i])<2) return;// '<2' 比 '==1' 少一个字符，所以我写 '<2' (:P)
	if(ans1)ans = min(ans,ans1);// 记录最小值 
}
signed main(){
	cin>>n;
	for(int i = 1; i<=n; i++) cin>>a[i];
	for(int i = 1; i<=(1<<16)-1; i++) js(i);// 每一种状态压缩后情况 
	cout<<ans;
	return 0;
}

```


---

## 作者：liangbob (赞：0)

## $\mathtt{Pre\ Explanation}$

本人第一次使用新风格写题解，希望大家多多包涵~

## $\mathtt{Solution}$

我们先来证明一个结论：

- 答案必然是 $p_1 \times p_2 \times p_3 \times \cdots p_n$，其中 $p$ 为 $1$ 到 $50$ 内全体质数集合的一个子集。

下面我们分步来论述一下：

- 首先，由于答案是满足每个数都至少有一个质因子是其质因数，我们暂时忽略“质数”这一条件，也就是每个数都有一个因子是其因数，这个很显然，就是最大公因数大于 $1$。而再加上“质数”这个条件，也就是有一个质数公因数。

- 而又由于我们希望这个数尽量的小，因此需要包含尽可能少的因数。而如果答案不是质数的乘积，那必然有一个质数重复乘了几次（即在答案分解质因数后有一个质因数的指数不为 $1$）。

- 不妨设这个数为 $r$，如果之前 $r$ 本身就不是给定的数中某个数的质因数，那么乘上之后答案如果满足题意还是满足题意，不满足还是不满足，多此一举。而如果是，那在乘上之前答案本身在这个数上就已经达成了目标（有一个质数公因数），再乘上也是多此一举，综上，答案必为质数的乘积。

- 其次由于 $X_{i} \le 50$，而一个数的因数不能超过这个数本身，如果答案中的 $p_i$ 超过 $50$，那么它必然不是任何一个 $X_i$ 的因数，相当于这个 $p_i$ 就没用，因此 $p_i \le 50$。

由于 $1$ 到 $50$ 内全体质数集合的元素个数较小，因此我们可以发挥我们的数学常识将其所有元素默写出来，然后使用二进制枚举状态的方法，枚举每个质数的选和不选，那么把所有选的质数乘起来就是 $p_1 \times p_2 \times p_3 \times \cdots p_n$，接着判断一下是否跟所有的 $X$ 都有一个共同的质因数（由于答案为质数相乘，那么相当于判断最大公因数是否大于 $1$）就可以了。

时间复杂度 $O(N2^M)$，其中 $M$ 为 $1$ 到 $50$ 内全体质数集合的元素个数。

## $\mathtt{Critical\ Code}$

```cpp
for(int S = 1;S < (1 << 15);S++) //状态
{
    int u = 1;
    for(int i = 1;i <= 15;i++)
    {
        if(S & (1 << (i - 1))) u *= p[i]; //计算答案
    }
    int cnt = 0;
    for(int i = 1;i <= n;i++)
    {
        if(__gcd(a[i], u) > 1) cnt++; //判断有无共同的质因数
    }
    if(cnt == n) ans = min(ans, u); //更新最小值
} 
```

---

## 作者：Berd__ (赞：0)

### 题目大意

给定 $N$ 个数 $X_1,X_2,\cdots,X_N$，求一个最小的数 $Y$，使每个数都至少有一个质因子为 $Y$ 的因数。

- $ 1\ \leq\ N\ \leq\ 49 $
- $ 2\ \leq\ X_i\ \leq\ 50 $
- $ X_i\ \neq\ X_j\ (i\ \neq\ j) $
- 输入都为整数

可以发现 $X_i<50$，暴力枚举即可。

因为数据范围较小，所以判断队列中的数不与质数的乘积互质，满足条件就和之前的答案比较大小，保存较小的即可。

对了，顺便放一下求 $50$ 以内质数的代码：
```
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int N = 50;//上限
    cout << 2 <<",";
    for (int i = 3; i < N; ++i) {
        bool flag = true;
        for (int j = 2; j < i; ++j) {
            if (!(i % j)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << i <<",";
        }
    }
    return 0;
}
```
### AC CODE：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll prime[30]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
map<ll,bool>ma;//标记
ll a[10000],ans=10000000000000;
void dfs(ll rp)
{
    ll temp=1;//保存乘积
    ll cnt=0;
    if(rp==16)
    {
        for(ll i=1;i<=60;i++)
        {
            if(ma[i])
            {
                temp=temp*i;
            }
        }
        for(ll i=1;i<=n;i++)
        {
            if(__gcd(temp,a[i])>1)
                cnt++;//判断互质
        }
        if(cnt==n)
            ans=min(ans,temp);
        return;
    }
    ma[prime[rp]]=0;
    dfs(rp+1);
    ma[prime[rp]]=1;
    dfs(rp+1);
}
int main()
{
    cin>>n;
    for(ll i=1;i<=n;i++)
        cin>>a[i];
    dfs(1);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：hubin1 (赞：0)

# Not coprime

## 题意
给定 $N$ 个数 $X_1,\ X_2,\ \cdots,\ X_N$，求一个最小的数，使每个数都至少有一个**质因子**为 $Y$ 的因数。

## 数据范围
- $1\ \leq\ N\ \leq\ 49$
- $2\ \leq\ X_i\ \leq\ 50$
- $X_i\ \neq\ X_j\ (i\ \neq\ j)$
- 输入全部为整数

## 一种不太对的解法

### 思路
把所有数的最小质因数相乘。

### Code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1e4;
int prime[30]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int a[MAX];
map<int,bool>ma;
signed main()
{
    int ans=1;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        for(int j=1;j<=15;j++)
        {
            if(a[i]%prime[j]==0)
            {
                ma[prime[j]]=1;
                break;
            }
        }
    }
    for(int i=1;i<=50;i++)
    {
        if(ma[i]==1)
            ans=ans*i;
    }
    cout<<ans<<endl;
    return 0;
}
```

### 问题
```
3  
45 5 2
```
这组数据会暴露一些问题，上边的代码会运行出 $30$，但实际应该是 $10$。问题就在于，这个方法选的是**最小的**质数，而有时选择一个不那么小的质数，会让答案更小。

## 可以通过的解法

### 思路
由于数据范围不大，可以直接暴力。判断 $50$ 以内的质数是否可以被这个数整除，如果可以，就标记下来。判断得到的这个数是否和**全部**的数互质。满足条件就和之前的答案比较大小，保存较小的。

### Code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1e4;
int prime[30]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};//50以内的质数
map<int,bool>ma;//用来标记
int a[MAX];
int n,ans=1e18;//ans初始一定要大
void dfs(int rp)
{
    int temp=1;//保存乘积
    int cnt=0;//保存个数
    if(rp==16)//跳出
    {
        for(int i=1;i<=60;i++)
        {
            if(ma[i])
            {
                temp=temp*i;
            }
        }
        for(int i=1;i<=n;i++)
        {
            if(__gcd(temp,a[i])>1)
                cnt++;//判断是不是互质
        }
        if(cnt==n)
            ans=min(ans,temp);//更新数据
        return;
    }
    ma[prime[rp]]=0;
    dfs(rp+1);
    ma[prime[rp]]=1;
    dfs(rp+1);
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    dfs(1);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：fkjhzhkjv (赞：0)

题目大意：输入 $n$ 个长方体，输出能分别装下这 $n$ 个长方体的盒子的最小体积。

大概思路：按每个长方体的长宽高的大小顺序排序，将排序后的数据从大到小命名为长、宽、高，分别求出所有长方体的长、宽、高的最大值，求他们的乘积。

证明：因为长方体的长宽高按任意顺序交换不改变长方体大小，题目也默许对其进行翻转，所以思路成立。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n, a, b, c, x = 0x7f, x2, x3 = -1, max1 = -1, max2 = -1, max3 = -1;
   cin >> n;
   for(int i = 1;i <= n;++i){
       cin >> a >> b >> c;
       x = min(min(a, b), c);//求最小
       x3 = max(max(a, b), c);//求最大
       x2 = a + b + c - x - x3;//剩下的值
       max1 = max(max1, x);//目前最大值
       max2 = max(max2, x2);
       max3 = max(max3, x3);
   }
   cout << max1 * max2 * max3 << endl;//求解
   return 0;
}
```
不知道为什么题解界面未显示，重交一遍，请管理见谅

---

## 作者：ljlawa (赞：0)

~~机房大佬提出打一场比赛，所以见到了这道题。~~

首先我们看到题一定会认为这是道数学方面的题。（事实确实如此。）

题目的大意就是输出一个最小的数，满足他与其他任何数的 $\gcd$ 都 $\gt1$。

于是想到了一种贪心思路，就是枚举 $50$ 以内的质数，然后将可以满足当前所有的数的个数最多的取出作为答案的一部分。并将已经满足条件的数取出。再如此往复直到所有的数都被满足。

因为数据范围很小，所以这种算法是可行的。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100;

int n, a[N];
int pri[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
int cnt[20];
bool vis[N];
long long ans = 1;

int gcd (int a, int b)
{
	return b == 0 ? a : gcd (b, a % b);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	while (1)
	{
		bool flag = 0;
		for (int i = 1; i <= 15; i ++) cnt[i] = 0;
		for (int i = 1; i <= n; i ++)
		{
			if (vis[i]) continue;
			for (int j = 1; j <= 15; j ++)
			{
				if (a[i] % pri[j] == 0)
				{
					cnt[j] ++;
					flag = 1;
				}
			}
		}
		if (!flag) break;
		int maxx = 0, id;
		for (int i = 1; i <= 15; i ++)
			if (cnt[i] > maxx) id = i, maxx = cnt[i];
		ans = ans * pri[id] / gcd(ans, pri[id]);
		for (int i = 1; i <= n; i ++) if (a[i] % pri[id] == 0) vis[i] = 1;
	}
	cout << ans;
	return 0;
}
```

但是我们发现有一些问题。

例如：

```
2
14 21
```
会输出 $7$，而不是 $6$。

~~(他过了at的脚造数据。)~~

因此我们做出一些改动。我们不止枚举质数了。

我们将 $pri$ 数组改变一下。

然后就没有问题了

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100;

int n, a[N];
int pri[50] = {0, 2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 17, 19, 21, 22, 23, 26, 29, 30, 31, 33, 34, 35, 37, 38, 39, 41, 42, 43, 46, 47};
int cnt[50];
bool vis[N];
long long ans = 1;

int gcd (int a, int b)
{
	return b == 0 ? a : gcd (b, a % b);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	while (1)
	{
		bool flag = 0;
		for (int i = 1; i <= 30; i ++) cnt[i] = 0;
		for (int i = 1; i <= n; i ++)
		{
			if (vis[i]) continue;
			for (int j = 1; j <= 30; j ++)
			{
				if (gcd(a[i], pri[j]) > 1)
				{
					cnt[j] ++;
					flag = 1;
				}
			}
		}
		if (!flag) break;
		int maxx = 0, id;
		for (int i = 1; i <= 30; i ++)
			if (cnt[i] > maxx) id = i, maxx = cnt[i];
		ans = ans * pri[id] / gcd(ans, pri[id]);
		for (int i = 1; i <= n; i ++) if (gcd(a[i], pri[id]) > 1) vis[i] = 1;
	}
	cout << ans;
	return 0;
}
```


---

