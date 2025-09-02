# Factorial Divisibility

## 题目描述

### 题面翻译

给定两个正整数 $n$ 和 $x$ 和一个正整数序列 $a_1 \sim a_n$。

请问 $\sum_{i = 1}^n a_i!$ 是否能被 $x!$ 整除。如果能则输出一个字符串 $\texttt{Yes}$，不能则输出字符串 $\texttt{No}$。

## 样例 #1

### 输入

```
6 4
3 2 2 2 3 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
8 3
3 2 2 2 2 2 1 1```

### 输出

```
Yes```

## 样例 #3

### 输入

```
7 8
7 7 7 7 7 7 7```

### 输出

```
No```

## 样例 #4

### 输入

```
10 5
4 3 2 1 4 3 2 4 3 4```

### 输出

```
No```

## 样例 #5

### 输入

```
2 500000
499999 499999```

### 输出

```
No```

# 题解

## 作者：liangbowen (赞：17)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1753B)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16823055.html)

其实挺简单的，赛时多打了个等号，被人叉了。![](//啧.tk/ll)![](//啧.tk/ll)![](//啧.tk/ll)

## 思路

关键是 $n! \times (n + 1) = (n + 1)!$。

原因很显然：$(1 \times 2 \times \cdots \times n) \times (n + 1) = (n + 1)!$。

知道这个，这道题不就做完了吗。统计每一个数码的个数，每次能进位就进位（指 $(n + 1)$ 个 $n!$ 进出一个 $(n + 1)!$）。

要求成立，当且仅当 $1$ 至 $(x - 1)$ 都进没了，只有 $x$ 的桶里有数。

具体看代码吧，非常容易理解。

## 代码

```cpp
//赛时代码
#include <bits/stdc++.h>
using namespace std;
int cnt[500005];
int main()
{
	ios::sync_with_stdio(false);
	int n, x;
	cin >> n >> x;
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		cnt[a]++; //统计
	}
	for (int i = 1; i < x; i++) cnt[i + 1] += (cnt[i] / (i + 1)), cnt[i] %= (i + 1); //"进位"
	for (int i = 1; i < x; i++)
		if (cnt[i])
		{
			cout << "No";
			return 0;
		}
	if (cnt[x]) cout << "Yes";
	else cout << "No";
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Binary_Lee (赞：5)

## [题面传送门](https://www.luogu.com.cn/problem/CF1753B)

### 解决思路

先手算一下样例，可以发现，$i+1$ 个 $i!$ 相加等于 $(i+1)\times i!= (i+1)!$。所以考虑把可以合并的都合并。

因为 $a_i\le 500000$，所以只需用桶计数，从 $1$ 到 $500000$ 扫一遍，发现满足条件的就向后一位进位。 然后我们就得到了原数列最简形式。

考虑两个数 $x,y$，当 $x\ge y$ 时，$x!$ 显然可以被 $y!$ 整除，因为 $x!=y!\times(y+1)\times \dots \times x$。同理，对于另一个 $z\ge y$，$x!+z!$ 也一定可以被 $y!$ 整除。其实就是乘法分配律。反之，对于 $t<y$，则 $t!$ 不能被 $y!$ 整除，$x!+z!+t!$ 也就不能被 $y!$ 整除了。

所以我们得出，若最简序列中最小 $a_i$ 的若小于 $x$，则最后的和显然无法被 $x!$ 整除。


### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0) 
#define int long long
#define double long double
using namespace std;
int n,k,a,t[500005];
signed main(){
	IOS;TIE;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;
		t[a]++;
	}
	for(int i=1;i<=500000;i++){
		t[i+1]+=t[i]/(i+1);
		t[i]%=(i+1); 
	}
	for(int i=1;i<k;i++){
		if(t[i]){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：Day0 (赞：3)

### 题意描述:

给你一些数，求这些数字的阶乘之和是否为 $w!$ 的倍数。

### 思路:

先将这些数从小到大排序，筛掉大于 $w$ 的数字（这些数字阶乘之和肯定为 $w!$ 的倍数）。

我们知道一个结论：

$$
k! \cdot (k+1)=(k+1)!
$$

然后我们发现 $k+1$ 个 $k$ 可以变成一个 $k+1$，如果前面数字 $k$ 无法全部变成 $k+1$，则输出 `NO`，反之为 `YES`。

### code:

```cpp
/*
    Author : TLE_Automaton && hhdxgd && JRXGD && hwd-gd
    Right Output ! & Accepted !
*/

#include <bits/stdc++.h>
//#define int long long
using namespace std;

int T;
const int L = 5e5 + 5;
int t, n, k, x, y, z, ans, cnt, a[L], flag[L];

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
		f = (ch == '-' ? -1 : f), ch = getchar();
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
	return x * f;
}

int maxn = -1;

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) {
		flag[a[i]]++;
		maxn = max(maxn, a[i]);
		if (a[i] >= k)
			break;
	}
	for (int i = 1; i <= k; i++) {
		flag[i] += flag[i - 1] / i;
		if (flag[i - 1] % i) {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
}

```

---

## 作者：cjh20090318 (赞：3)

大家好，我是 CQ-C2024 蒟蒻 CJH。

难度：普及/提高-。

标签：数学。

## 题意

给定 $n$ 个数 $a_1,a_2,\dots,a_n$，求出 $\sum\limits_{i=1}^n{a_i!} \bmod x!$ 是否等于 $0$。

## 思路

根据阶乘的定义我们可知：
$$
(x+1) \times x!=(x+1)!
$$
所以思路就非常清晰了，我这里将 $i$ 阶乘出现的次数记为 $b_i$，然后统计 $b_1,b_2,\dots,b_x$。

接着枚举 $1 \sim x-1$ 进行合并同类项的操作，如果 $b_i \bmod (i+1) \ne 0$，那就肯定不符合整除的要求。

如果最终可以合并到底，就说明是符合要求的。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define P puts("WA")
using namespace std;
int a[500005];//这里用 a 数组来记录 i 阶乘出现的次数
int main(){
	int n,x;
	scanf("%d%d",&n,&x);
	for(int i=1,y;i<=n;i++)
		scanf("%d",&y),++a[y];
	for(int i=1;i<x;i++){
		if(a[i]%(i+1)) return puts("No"),0;//判断是否能整除。
		a[i+1]+=a[i]/(i+1);//向 (i+1)! 合并。
	}
//	printf("%d\n",a[x]);
	puts(a[x]?"Yes":"No");//如果结果为真（正数），即为正确。
	return 0;
}

```

*谢谢大家！*

---

## 作者：Shunpower (赞：2)

## 思路

注意这可能不是一种正解。

首先让我们考虑 $a_i!$ 之和的最大值，显然是 $n\times x!$，我们用它除以一个 $x!$，这时我们就得到了最终的商的最大值，是 $n$。

下面考虑哈希（类似的算法），我们随便选一个质数模数 $m$（当然要大于 $5\times 10^5$），然后我们算出来 $a_i!$ 之和模掉 $m$ 的答案，然后乘 $x!$ 在模 $m$ 意义下的逆元，再模掉 $m$。如果算出来的答案小于 $n$（实际上我用 $5\times 10^5$ 也过了），那么我们就判 `Yes`，否则就是 `No`。

理论上这种东西可以被赛时针对性 Hack 掉，不过我是赛后过的。理论上模数只要拿得够多就很难 Hack 了。假设取了 $k$ 个质数模数，复杂度就是 $O(nk\log A)$ 的，$A$ 是质数模数的值域。理论上取 $10$ 个左右刚刚好。

## 代码

$1$ 个模数，为 $20070737$。


```
//Author:Zealous_YH / Cream_H
//Su Chanzi & Xiao Bao
//Hey Left
//Just enjoy the loneliness
//Open a personal party always stay
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
//Quickly power: ll d=qpow(b,p>>1,k);
//Segment Tree: Memory Limit Excceed
//Segment Tree: Modify()->Pushdown()
//Don't do a problem for too long time.
using namespace std;
const int N=5e5+10;
const ll H1=20070737;
namespace Cream_H{
	int lowbit(int x){
		return x&-x;
	}
	template <typename T>
	inline void read(T &x){
	   T s=0,w=1;
	   char ch=getchar();
	   while(ch<'0'||ch>'9'){
	   		if(ch=='-'){
				w=-1;
	   		}
	        ch=getchar();
		}
	   while(ch>='0'&&ch<='9'){
	   		s=s*10+ch-'0';
			ch=getchar();
	   }
	   x=s*w;
	}
	template <typename T>
	inline void write(T x){
	    if(x<0){
	        putchar('-');
	        x=-x;
	    }
	    if(x>9){
	    	write(x/10);
		}
	    putchar(x%10+'0');
	}
}
using namespace Cream_H;
ll n,x;
ll frac[N];
ll k;
ll d;
ll qpow(ll b,ll p,ll k){
	if(!p){
		return 1;
	}
	ll d=qpow(b,p>>1,k);
	if(p&1){
		return d*d%k*b%k;
	}
	else{
		return d*d%k;
	}
}
void init(int x){
	frac[0]=1;
	fr1(i,1,x){
		frac[i]=frac[i-1]*(ll)i;
		frac[i]%=H1;
	}
}
int main(){
	cin>>n>>x;
	init(x);
	fr1(i,1,n){
		cin>>d;
		k+=frac[d];
		k%=H1;
	}
//	cout<<x<<endl;
//	cout<<k<<","<<qpow(x,H1-2,H1)<<","<<k*qpow(x,H1-2,H1)%H1<<endl;
	if(k*qpow(frac[x],H1-2,H1)%H1<=500000){
		cout<<"Yes"<<endl;
	}
	else{
		cout<<"No"<<endl;
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//YHX 2004.08.16
//Everything For Ji, Lin, Hao, Shun, Hang and You.
```

[AC 记录](https://www.luogu.com.cn/record/91473657)

---

## 作者：smallpeter (赞：1)

感觉翻译已经够简洁的了，可以直接去看题面。

# 题目思路

看到这题相信很多人第一想法都是暴力算出模数然后计算~~但这显然会寄~~，因为 $x!$ 这玩意显然是不能直接当模数计算的（因为会炸 `long long` ）。不难想到另一种~~妙妙~~思路。我们发现 $a!\times(a+1)=(a+1)!$，也就是说我们可以通过合并的方法来变成 $x!$ 的倍数（或说明不行）。思路就很简单了，我们从 $1!$ 开始合并，一直合并到 $x!$，如果在合并过程中出现了剩余，那就证明不是 $x!$ 的倍数。思路就这样了，上代码。

# 代码
```

#include<bits/stdc++.h>
using namespace std;
 
#define LL long long
 
const LL N=5e5+10;
 
LL n,x,a[N],f[N];
 
int main(){
	scanf("%lld%lld",&n,&x);
	for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(LL i=1;i<=n;i++){
		if(a[i]<x){//大于等于x的肯定是x!的倍数，所以只考虑小于x的
			f[a[i]]++;
		}
	}
	for(LL i=1;i<x;i++){
		if(f[i]==0) continue;
		if(f[i]%(i+1)==0){//刚好能合并完
			f[i+1]+=f[i]/(i+1);//合并
		}
		else{//合并后有剩余
			printf("No");
			return 0;
		}
	}
	printf("Yes");
}
```

---

## 作者：litachloveyou (赞：1)

首先我们来想一下阶乘的定义，也就是 $n!=n\times(n-1)\times (n-2)\times...\times1$。

如果一个阶乘 $a_i!$ 出现的次数 $k $ $\bmod $ $ (ai+1)=0$，也就说明阶乘   $(a_i+1)!$ 出现了 $k \div (a_i+1)$ 次。

举个例子，**当 $2!$ 出现了 $3$ 次的时候，就说明 $3!$ 出现了一次**。

想到这里，我们只需要判断 $[1,x-1]$ 里每个阶乘 $i!$ 出现的次数 $k$ 是否是 $i+1$ 的倍数就可以了，并且 $(i+1)!$ 的出现次数还需要加上 $ k\div (i+1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
	int n, x;
	scanf("%d%d", &n, &x);
	vector<int>a(x + 1);
	for (int i = 1, m; i <= n; i++)
	{
		scanf("%d", &m);
		a[m]++;
	}
	for (int i = 1; i < x; i++)
	{
		if (a[i] % (i + 1))
		{
			puts("No");
			return;
		}
		a[i + 1] += a[i] / (i + 1);
	}
	puts("Yes");
}
int main()
{
	int T = 1;
	//scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：_dijkstra_ (赞：0)

简单的题目，这应该算是贪心吧。

显然 $i! = 1 \times 2 \times \cdots \times i$，再乘个 $(i + 1)$ 就是 $(i + 1)!$ 了。

我们利用这一点，一直进位即可。

最后看，是不是只有 $x$ 对应的桶有数。

## 代码：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int box[500010];
int main(){
    int n, x;
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++){
        int a;
        scanf("%d", &a);
		box[a]++;
    }
    for (int i = 2; i <= x; i++){
    	box[i] += box[i - 1] / i;
		box[i - 1] %= i;
	}
    for (int i = 1; i < x; i++){
    	if (box[i]) puts("No"), exit(0);
    }
    if (box[x]){
    	puts("Yes");
	}else{
		puts("No");
	}
    return 0;
}
```

---

## 作者：cosf (赞：0)

# [CF1753B](https://codeforces.com/problemset/problem/1753/B) [Factorial Divisibility](https://www.luogu.com.cn/problem/CF1753B)

题目大意：

给定 $n$ 个数 $a_1, a_2, \dots, a_n$ 求 $a_1! + a_2! + \dots + a_n!$ 是否整除 $x!$。

---
思路
---

根据阶乘的定义，易得 $i!(i + 1) = (i + 1)!$。根据阶乘的性质，易得当 $i < j$ 时，$i!|j!$。

所以我们可以对 $a_i$ 进行处理。比如，如果有 $a_i$ 个数和 $a_i$ 相同（不包括 $a_i$)，则可以把它们全部换成一个数，即 $a_i+1$。（根据定义）

处理完所有的这种情况后，我们可以从 $1$ 扫描到 $x$，如果这个时候还存在一个 $a_i$ 和正在扫描的数相等，则输出 `No`，否则输出 `Yes`。（根据性质）

---
实现
---

我们可以构造一些桶 $b_i$，其中 $b_i$ 表示 $a$ 中有多少个等于 $i$。然后再根据上述内容进行“进位”。最后再扫描。

---
有注释的代码：
---

## AC Code

```cpp
#include <iostream>
using namespace std;

int n, x;
int a[500005];

int main()
{
	cin >> n >> x;
	int c;
	int mc = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> c;
		a[c]++; // 这里的 a 即上述的 b，这里直接忽略了上述的 a（因为没用）。
		mc = max(mc, c);
	}
	int i;
	for (i = 1; i <= mc || a[i]; i++) // 注意要合并到哪里，其实到 x 就够了。
	{
		a[i + 1] += a[i] / (i + 1); // (i + 1)i! = (i + 1)!
		a[i] %= (i + 1); // 剩下合不了的。也可以直接再这里判断No 和 Yes
	}
	for (int j = 1; j < x; j++) // 扫描
	{
		if (a[j])
		{
			cout << "No" << endl; // 不整除
			return 0;
		}
	}
	cout << "Yes" << endl; // 整除
	return 0;
}

```

---

## 作者：FutureSnow (赞：0)

考虑阶乘递推
	
   $$2 \times 1! = 2!$$
   
   $$3 \times 2! = 3!$$
   
   $$4 \times 3! = 4!$$
   
   $$\vdots$$
   
   $$(n + 1) \cdot n! = (n + 1)!$$
   
根据该递推式，我们可以统计每个数的阶乘出现的次数，如果一个数 $i$ 的阶乘出现了 $c_i$ 次且 $c_i \mid i + 1$，则将 $c_{i + 1}$ 增加 $\dfrac{c_i}{i+1}$ 且将 $c_i$ 清零。

最后如果不存在一个数 $i$ 满足 $i < x$ 且 $c_i > 0$ 则输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

```cpp
 
#include <bits/stdc++.h>
 
using namespace std;
int n;
int a[500050];
int cnt[500050];
int x;
int main (){
	cin >> n >> x;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		cnt[a[i]]++;
	}
	for(int i = 1; i <= x; i++){
		if(cnt[i] % (i + 1) == 0){
			cnt[i + 1] += cnt[i] / (i + 1);
			cnt[i] = 0;
		}
	}
	for(int i = 1; i < x; i++){
		if(cnt[i]){
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl;
	return 0;
}
```

---

## 作者：awask (赞：0)

## 闲话
比赛开始之后快一个小时才开始打 Div2，下午一直在和去年S组的回文较劲，结果改完最后一遍发现 4:30 多了，就打了个 A B C1 和 D，喜提 $2659$ 名的**好成绩**。
## 做法
观察数据范围，$1 \le a_i \le 5 \times10^5 $，显然暴力计算阶乘不可取，时间复杂度会爆炸。所以考虑用桶来做。

我们知道，如果 $n \le m$，那么 $ n! \mid m!$ ，原因显然。所以不用理会输入中所有的 $ a_i \ge x $ 的情况；又因为 $n!=n\times(n-1)!$，所以很容易想出一种思路：将所有 $a_i < x$ 凑成 $\ge x$ 的阶乘；一旦有某个 $ < x$ 的数 $a_i$ 有 $\ge 1$ 的剩余不能被加到 $(a_i +1)!$ 中，则一定无解。详情看代码。

## 代码
```cpp
#include<iostream>
using namespace std;
int n,a[500002],k,p,check;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>p;
		a[p]++;
	}
	for(int i=1;i<k;i++)
	{
		if(a[i]>i)
			a[i+1]+=a[i]/(i+1),a[i]%=(i+1);//本行是此题的关键
		if(a[i])
  		{
			check=1;
			break;
		}
	}
	if(check)cout<<"No";
	else cout<<"Yes";
	return 0;
}
```

---

