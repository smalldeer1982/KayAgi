# [GESP202403 五级] B-smooth 数

## 题目描述

小杨同学想寻找一种名为 $ B $-smooth 数的正整数。 

如果一个正整数的最大质因子不超过 $ B $，则该正整数为 $ B $-smooth 数。小杨同学想知道，对于给定的 $ n $ 和 $ B $，有多少个不超过 $ n $ 的 $ B $-smooth 数。

## 说明/提示

### 数据规模与约定

| 子任务 | 得分 | $n \leq $ | $B$ |
| :-: | :-: | :-: | :-: |
| $1$ | $30$ | $10^3$ | $1 \leq B \leq 10^3$ |
| $2$ | $30$ | $10^6$ | $\sqrt n \leq B \leq 10^6$ |
| $3$ | $40$ | $10^6$ | $1 \leq B \leq 10^6$ | 

对全部的测试数据，保证 $1 \leq n, B \leq 10^6$。

## 样例 #1

### 输入

```
10 3```

### 输出

```
7```

# 题解

## 作者：Little_x_starTYJ (赞：37)

### 解题思路
这道题目的数据范围有点大，暴力算法的时间复杂度是 $O(n^2)$ 的，明显超时，于是我们可以先预处理出 $1\sim n$ 的所有数的最大质因子。但是暴力找到最大质因子也是很慢的，所以我们可以先筛出每个数的最大质因子，最后统计一下即可。

为什么可以用筛法呢？因为例如数字 $6$，他的质因子有 $2$ 和 $3$，于是它在 $i =2$ 时被处理了一次。当 $i = 3$ 时，由于他是 $3$ 的倍数，所以它又被处理了一次，最后我们算出它的最大质因子为 $3$。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000010];
int ans;
int main() {
	int n, b;
	cin >> n >> b;
	a[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!a[i]) {
			for (int j = i; j <= n; j += i)
				a[j] = i;
		}
	}
	for (int i = 1; i <= n; i++) { 
		if (a[i] <= b)
			ans++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：dlzlj_2010 (赞：8)

注意到 $1\le n,B\le10^6$，**直接枚举最大质因子是不可能的了**，考虑与埃氏筛类似的思想**预处理**每个数的最大质因子。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int mp[N];//最大质因子
int n,b,ans=0;
void work(int n){
	mp[1]=1;
	for(int i=2;i<=n;i++){
		if(!mp[i]){//如果是质数
			mp[i]=i;//其最大质因子为其本身
			for(int j=2;i*j<=n;j++){//将所有i的倍数枚举
				mp[i*j]=i;
			}
		}
	}
}
signed main(){
	cin>>n>>b;
	work(n);
	for(int i=1;i<=n;i++){
		if(mp[i]<=b)ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：spfa_ (赞：8)

[B3969 [GESP202403 五级] B-smooth 数](https://www.luogu.com.cn/problem/B3969)

总所周知，质因数分解是 $O(\sqrt n)$ 的，枚举每个 $i$ 并判断的复杂度是 $O(n\sqrt n)$ 的，而 $n\le10^6$，故是可以过的。

具体的，我们只需枚举每个数 $i$。对于 $i$，从 $2$ 开始枚举每个质因子，若 $i$ 能整除，则将 $i$ 一直除这个质因子，注意判断最后的 $i>1$ 的情况，此时 $i$ 也为质因子。

代码：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
inline ll rdll() { ll x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

int get(int x) {
	int mx = 0;
	for (int i = 2; i*i <= x; ++i) while (x%i == 0) mx = max(mx, i), x /= i;
	return x > 1 ? max(mx, x) : mx;
}

int main() {
	int n, b, ans = 0; cin >> n >> b;
	for (int i = 1; i <= n; ++i) if (get(i) <= b) ++ans;
	cout << ans;
	return 0;
}
```

---

## 作者：xyx404 (赞：6)

## 思路：
定义一个数组存这个数最大的质因数。

如何存，枚举每一个小于 $n$ 的**质数**，再枚举它的倍数，但是在枚举倍数时要注意如果第二个数字大于了第一个数字且第二个数字是质数那么先跳过，且第一个数字乘第二个数字要是大于 $n$ 那么退出这一层循环写进判断条件里，代码如下。
```cpp
for(long long i=2;i<=n;i++){
		if(zs(i))//注意 i 要是质数
		for(long long j=1;j*i<=n;j++){//枚举 i 的倍数
			if(j>i&&zs(j))continue;// 如果 j 大于 i 且 j 是质数 那么说明 i*j 这个数的最大质因数不是 i 直接跳过后面再赋值
			bj[j*i]=i;
			//cout<<i*j<<"\n";// 测试
		}
		else continue;//i 不是质数跳过
	}
```

标记好了后，定义一个存的变量变量赋值为一，因为虽然一没有质因数但是还是要加上，然后枚举从二到 $n$ 中有多少个的最大质因数是小于等于 $B$ 的就可以了，为什么从二开始枚举因为一已经在定义时加上了，代码如下。
```cpp
long long ans=1;
for(long long i=2;i<=n;i++){
		if(bj[i]<=b)ans++/*,cout<<i<<"\n";*/;
	}
```
然后输出就可以了。

## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,b,ans=1;// 定义移到主函数外了
long long bj[1000099];
bool zs(long long x){// 判断质数
	if(x==1)return 0;
    if(x==2||x==3)return 1;
    if(x%6!=1&&x%6!=5)return 0;
    for(int i=5;i*i<=x;i+=6)if(x%i==0||x%(i+2)==0)return 0;
    return 1;
}
int main(){
	cin>>n>>b;// 输入
	for(long long i=2;i<=n;i++){
		if(zs(i))
		for(long long j=1;j*i<=n;j++){
			if(j>i&&zs(j))continue;
			bj[j*i]=i;
			//cout<<i*j<<"\n";
		}
		else continue;
	}
	for(long long i=2;i<=n;i++){
		if(bj[i]<=b)ans++/*,cout<<i<<"\n";*/; 
		//if(bj[i]==0)cout<<i<<"\n";// 测试
	}
	cout<<ans;// 输出
	return 0;
}

```

---

## 作者：GavinWu_qwq (赞：4)

### 题意简述

给定正整数 $n,B$，请你求出在不超过 $n$ 的正整数中，有多少个最大质因子不超过 $B$ 的数。

### 解题思路

#### 子任务 1 —— 暴力枚举

暴力枚举的思路很好想。对于所有不超过 $n$ 的正整数，直接分解质因数，找出其最大质因子，然后做判断即可。

时间复杂度 $O(n^2)$，预期得分 $30$ 分。

#### 正解

既然正向思考不行，那么我们就逆向思考。

根据题意，若一个正整数存在一个大于 $B$ 质因子 $x$，那么这个数就是不符合条件的；反过来，对于所有大于 $B$ 的质数 $x$，它的倍数都是不符合条件的。

于是我们就可以找出所有大于 $B$ 且不超过 $n$ 的质数，并找出它们所有的倍数，剩下的没有被找出的数就是满足条件的数。

时间复杂度 $O(n \sqrt{n})$，在 $n \le 10^6$ 的数据范围下可以通过。

### 完整代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;
bool flag1[1000010], flag2[1000010];
bool isPrime(int x){
    if (x == 1) return false;
    if (x == 2) return true;
    for (int i = 2;i * i <= x;i++)
        if (x % i == 0)
            return false;
    return true;
}
int main(){
    memset(flag2, true, sizeof(flag2));
    int n, b;
    cin >> n >> b;
    for (int i = b + 1;i <= n;i++)
        flag1[i] = isPrime(i);
    for (int i = b + 1;i <= n;i++)
        if (flag1[i] == true)
            for (int j = 1;i * j <= n;j++)
                flag2[i * j] = false;
    int cnt = 0;
    for (int i = 1;i <= n;i++)
        if (flag2[i] == true)
            cnt++;
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：zhc20170619 (赞：1)

### 题意

 求 $[1,n]$ 中最大质因子不超过 $B$ 的数的数量

### 思路和步骤

1. 线性筛预处理 $[2,n]$ 中的每个数的最小质因子，若这个数本身是素数，则它的最大最小质因子都是自身。
2. 遍历 $[2,n]$ 中的每个数 $i$ ，如果 $i$ 是素数，则它的最大质因子就是自身，判断是否小于等于 $B$ 。若 $i$ 是合数，则通过删去它的最小质因子的过程找出它的最大质因子，判断是否小于等于 $B$。
3. 这个问题中把 $1$ 的最大质因子也看做了 $1$ (特殊情况) ，因此答案初始化为 $1$ 。

### Code

```c++
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
#define PII pair<int,int> 
using namespace std;
const int N=1e6+10;
int n,b,p[N],cnt;
int v[N];
void primes(int n){
	for(int i=2;i<=n;i++){
		if(!v[i]){
			p[++cnt]=i;
			v[i]=i;
		}
		for(int j=1;p[j]<=n/i;j++){
			v[i*p[j]]=p[j];
			if(i%p[j]==0) break;
		}
	}
}
int main()
{
	cin>>n>>b;
	primes(n);
	int ans=1;
	for(int i=2;i<=n;i++){
		if(v[i]==i){
			if(i<=b) ans++;
		}
		else{
			int t=i,res=0;
			while(t!=1) res=max(res,v[t]),t/=v[t];
			if(res<=b) ans++;
		}
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：Ryzen_9_7950X (赞：1)

省流：欧♂拉♂筛♂连♂着♂埃♂氏♂筛♂

# 思路
我们可以用欧拉筛进行素数的查找，\
然后用类似于埃氏筛的做法，\
将答案数组的这个素数的倍数位置设置为该素数，\
最后将答案数组区间内的值与 $B$ 进行比较，\
输出答案即可。
# 示例
就拿样例来说吧：
```
10 3
```
首先初始化之后，三个数组分别为为：\
\
素数数组：\
$\begin{bmatrix} 2 & 3 & 5 & 7 \end{bmatrix}$\
\
素数查找数组：\
$\begin{bmatrix} 0 & 1 & 1 & 0 & 1 & 0 & 1 & 0 & 0 & 0 \end{bmatrix}$\
\
答案数组：\
$\begin{bmatrix} 1 & 2 & 3 & 2 & 5 & 3 & 7 & 2 & 3 & 5 \end{bmatrix}$\
\
容易看出， $5$、$7$、$10$ 的最大质因子均超过了样例中的上限值 $3$ ，除这些数以外的数共有 $7$ 个，所以答案为 $7$。
# 代码
我们可以用上述的思路，得到以下的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int ss[1000005],answer[1000005],init[1000005];
void INIT()
{
    int array = 1;
    answer[1] = init[1] = 1;
    for(int i = 2;i <= 1000000;i++)
    {
        if(!init[i])
        {
            ss[array] = i;
            array++;
        }
        for(int j = 1;j <= array && ss[j] * i <= 1000000;j++)
        {
            init[ss[j] * i] = 1;
            if(i % ss[j] == 0) break;
        }
    }
    for(int i = 1;i <= 1000000;i++)
    {
        for(int j = 1;i * ss[j] <= 1000000 && j <= array;j++)
        {
            answer[i * ss[j]] = max(ss[j],answer[i * ss[j]]);
        }
    }
}
int main()
{
    INIT();
    int a,b;
    cin >> a >> b;
    int ans = 0;
    for(int i = 1;i <= a;i++)
    {
        ans += (answer[i] <= b);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：zxy1919810 (赞：1)

## B3969 [GESP202403 五级] B-smooth 数题解
[题目传送门](https://www.luogu.com.cn/problem/B3969)。

因为需要求出所有 $1$ 到 $n$ 之间的 $B$-smooth 数，所以我们可以使用 for 循环枚举 $1$ 到 $n$ 里的所有正整数。

那么，如何确定一个数 $i$ 是不是 $B$-smooth 数呢？

1. 枚举从 $1$ 到 $i$ 的所有数，找到 $i$ 最大的质因数，与 $B$ 比较。
1. 枚举从 $1$ 到 $ \sqrt{i} $ 的所有数，找到 $i$ 最大的质因数，与 $B$ 比较。

很显然，第一种方法时间复杂度为 $O(n^2)$ 会超时。

所以我们可以采取第二种方法。

```cpp
int k=i;                  //使用k代替i让循环正常进行
for(int j=2;j*j<=k;j++)   //枚举1到i
	if(k%j==0){       //如果 可以整除
		while(k%j==0) k/=j;	 //就把所有质因子除掉
		MAX=max(MAX,j); //打擂台求出最大值
	}
MAX=max(MAX,k); //若i的质因子有大于根号i的，那么必定只有一个，并且就是最后的k，所以打擂台求最大值
```
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,b,ans=0;
	cin>>n>>b;
	for(int i=1;i<=n;i++){
		int MAX=0,k=i;
		for(int j=2;j*j<=k;j++)
			if(k%j==0){
				while(k%j==0) k/=j;	
				MAX=max(MAX,j);
			}
		MAX=max(MAX,k);
		if(MAX<=b) ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hard_learn (赞：1)

# 简要题意
题目要求计算给定范围内不超过给定最大质因子的正整数数量。
# 思路
- 首先，需要实现一个函数来判断一个数是否为质数。
- 然后，使用一个循环从  $2$ 开始逐个检查每个数，找出不超过 $B$ 的最大质因子。
- 对于每个检查的数，如果它的最大质因子不超过  $B$，则计数器加 $1$。
- 最后返回计数器的值即可。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int ans[1000006];
bool flag[1000006];
int f(int n,int B){
    memset(flag,0,sizeof(flag));
	memset(ans,0,sizeof(ans));
    for(int p=2;p<=n;p++){
        if(flag[p]==0){
            for(int i=p;i<=n;i+=p){
                flag[i]=1;
                ans[i]=p;
            }
        }
    }
    int cnt=1;
    for(int i=2;i<=n;i++){
        if(ans[i]<=B){
            cnt++;
        }
    }
    return cnt;
}
int main(){
    int n,B;
    cin>>n>>B;
    cout<<f(n,B)<<endl;
    return 0;
}

```

---

## 作者：nightwatch.ryan (赞：1)

### 思路
预处理出 $2 \sim n$ 所有数的最大质因子，然后统计小于 $B$ 的即可。
### 代码
```cpp
#include<iostream>
#define ll long long
#define N 1000005
ll n,b,ans,p[N];
int main(){
	std::cin>>n>>b;
	for(ll i=2;i<=n;i++)
		if(!p[i]){
			p[i]=i;
			for(ll j=2;i*j<=n;j++)
			p[i*j]=i;
		}
	for(int i=1;i<=n;i++)
	if(p[i]<=b)ans++;
	std::cout<<ans;
} 
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/B3969)
# 思路
我们只要求出每个数的最大质因数，再一个个判断是否满足要求即可。

如何找到每个数的最大质因数呢？其实，我们可以在埃氏筛法的基础上进行改进，从而达到算出最大质因数的目的。

让我们先来了解一下埃氏筛法，知道的人可以跳过。埃氏筛法，是一种筛选质数的方法。首先定义一个 `bool` 型数组（初始全部赋值为 $1$，再后面我们用 $flag$ 进行代替），如果 $flag_i$（$2\le i\le n$，$i$ 初始值为 $2$） 为 `true`，而由于 $i$ 的倍数肯定包含质因数 $i$，所以就要依次将下标为 $i$ 的倍数的位置的值都改成 `false`，最后将 $i$ 的值加上 $1$。通过进行如上操作后，$flag$ 数组中值为 `true` 的位置的下标即为质数。具体的代码如下：
```cpp
for(int i=2;i<=n;++i) if(flag[i]) for(int j=i;j<=n;j+=i) flag[j]=false;
```
那么，如何进行改进呢？其实，我们可以不把下标为 $i$ 的倍数的位置的值改成 `false`，而是改成 $i$，而 $i$ 也就是它们**当前**的最大质因数，如果后面 $i$ 加了若干个 $1$ 之后还是它们之中任意个的质因数，则会更改其最大质因数为现在的 $i$。需要注意的一点是，由于埃氏筛的筛法变了，它的判断条件也将改变，并且由于 $flag$ 所存储的类型改变成了 `int` 类型，所以也要将 $flag$ 改成 `int` 类型。
# code
```cpp
#include<iostream>
using namespace std;
int n,b,Max[1000005]/*存储最大质因数*/,ans;
int main() {
	cin>>n>>b;
	Max[1]=1;
	for(int i=2;i<=n;++i) if(!Max[i]) for(int j=i;j<=n;j+=i) Max[j]=i;//找到最大质因数
	for(int i=1;i<=n;++i) if(Max[i]<=b) ++ans;//判断是否满足要求
	cout<<ans;
	return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/B3969)
## 解题思路
### $30$ 分解法
直接暴力即可。

代码不放。
### $100$ 分解法
我们先选出所有质数，再求出所有 $n$ 以内的 $B$-smooth 数。

让 $i$ 从 $2$ 到 $n$ 遍历，如果 $i$ 是质数，则让 $j$ 从 $i$ 到 $n$ 遍历，每次 $j\gets j+i$。

那什么时候可以存下当前方案呢？

当 $j\le i^2$ 时，显然可以。当 $j> i^2$ 时，如果 $\dfrac{j}{i}$ 不是质数，也是可以使 $a_j \gets i$ 的。

这样，就可以使 $a_i$ 是 $i$ 的最大质因子了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000010];
bool ss(int n)
{
	if(n<2)return 0;
	for(int i=2;i<=sqrt(n);i++)
		if(n%i==0)return 0;
	return 1;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,s=0;
	cin>>n>>m;
	for(int i=2;i<=n;i++)
		if(ss(i))
			for(int j=i;j<=n;j+=i)
				if(j<=i*i||!ss(j/i))a[j]=i;
	for(int i=1;i<=n;i++)s+=(a[i]<=m);
	cout<<s;
	return 0;
}
```

但是，怎么 TLE 了呢？

原来，我的质数判断太慢了。

于是，我写了个时间复杂度为 $O(\dfrac{\sqrt{n}}{2})$ 的质数判断函数：
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000010];
bool ss(int n)
{
	if(n<2)return 0;
	if(n==2)return 1;
	if(n%2==0)return 0;
	for(int i=3;i<=sqrt(n);i+=2)
		if(n%i==0)return 0;
	return 1;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,s=0;
	cin>>n>>m;
	for(int i=2;i<=n;i++)
		if(ss(i))
			for(int j=i;j<=n;j+=i)
				if(j<=i*i||!ss(j/i))a[j]=i;
	for(int i=1;i<=n;i++)s+=(a[i]<=m);
	cout<<s;
	return 0;
}
```

---

## 作者：Kle1N (赞：0)

看到别人都写的线筛做法，我比较菜，就介绍一种比较暴力的做法吧。

看到 $n$ 才不到 $10^6$，于是果断枚举。依次枚举 $1\sim n$ 的每个数，每次检查其最大质因子是否小于等于 $B$，统计结果即可。那最大质因子怎么求呢？我们可以对这个数质因数分解，除到 $1$ 前的那一个数或是循环后剩的数就是这个数的最大质因子了。除此之外还要注意 $1$ 也是 B-smooth 数，统计答案时要加上。这个做法看起来没问题，实则时间复杂度高达 $\Theta(n\sqrt{n})$，对于 $10^6$ 的数据而言显然会超时。

考虑优化。这里我加了两个优化，一是注意到 $n\le B$ 答案显然就是 $n$；二是添加了一个记忆化数组 ans 记录一个数的最大质因子，这么做的原因是因为可以发现求解过程中一个数的最大质因子可能会被计算多次，浪费时间，而用数组记下答案就可以有效避免这个问题。

具体见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,b,cnt,ans[1000001];
int f(int x){
	int t=x;
	for(int i=2;i*i<=x;i++){
		if(ans[t]!=0) return ans[t];
		if(t%i==0){
			while(t%i==0){
				if(ans[t]!=0) return ans[t];
				if(t/i==1) return ans[t]=i;
				t/=i;
			}
		}
	}
	if(t!=1) return ans[t]=t;
}
int main(){
	scanf("%d%d",&n,&b);
	if(n<=b){
		printf("%d",n);
		return 0;
	}
	for(int i=2;i<=n;i++){
		if(f(i)<=b) cnt++;
	}
	printf("%d",cnt+1);
	return 0;
}
```

---

