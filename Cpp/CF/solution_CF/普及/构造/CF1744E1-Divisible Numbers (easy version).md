# Divisible Numbers (easy version)

## 题目描述

This is an easy version of the problem. The only difference between an easy and a hard version is the constraints on $ a $ , $ b $ , $ c $ and $ d $ .

You are given $ 4 $ positive integers $ a $ , $ b $ , $ c $ , $ d $ with $ a < c $ and $ b < d $ . Find any pair of numbers $ x $ and $ y $ that satisfies the following conditions:

- $ a < x \leq c $ , $ b < y \leq d $ ,
- $ x \cdot y $ is divisible by $ a \cdot b $ .

Note that required $ x $ and $ y $ may not exist.

## 样例 #1

### 输入

```
5
1 1 2 2
3 4 5 7
8 9 15 18
12 21 14 24
36 60 48 66```

### 输出

```
2 2
4 6
12 12
-1 -1
-1 -1```

# 题解

## 作者：Allanljx (赞：8)

## 思路
E1：

枚举 $x$，那么 $y$ 必须是 $a\times b\div\gcd(a\times b,x)$ 的倍数，然后可以利用除法的向下取整算出 $y$ 在不超过 $d$ 的情况下最大是多少，然后再判 $y$ 是否大于 $b$。

E2：

E1 复杂度的瓶颈是有许多无用的 $x$，因此考虑一些 $x$ 的性质。$x$ 一定是 $a$ 的一个因数与 $b$ 的一个因数的积的倍数，所以分别枚举 $a$ 和 $c$ 的某个因数，设为 $p,q$。所以 $x$ 就是最小的大于 $a$ 的并且是 $p\times q$ 的倍数的数；$y$ 是最小的大于 $c$ 的并且是 $(a\times b)\div(p\times q)$ 的倍数的数。

## 代码
E1:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],b[200005];
int t,y;
signed main()
{
    cin>>t;
    while(t--)
	{
		int a,b,c,d;
        cin>>a>>b>>c>>d;
        int f=0;
        int x=a*b;
        for(int i=a+1;i<=c;i++)
		{
            int y=x/__gcd(x,i);
            y=d/y*y;
            if(y>b)
			{
				cout<<i<<' '<<y<<endl;
                f=1;
                break;
            } 
        }
        if(!f) cout<<"-1 -1\n";
    }
}
```
E2:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,c,d;
int a1[200005];
int a2[200005];
int tmp1,tmp2;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c>>d;
		tmp1=tmp2=0;
		for(int i=1;i*i<=a;i++)
		{
			if(a%i!=0) continue;
			a1[++tmp1]=i;
			if(i*i!=a) a1[++tmp1]=a/i;
		}
		for(int i=1;i*i<=b;i++)
		{
			if(b%i!=0) continue;
			a2[++tmp2]=i;
			if(i*i!=b) a2[++tmp2]=b/i;
		}
		int f=0;
		for(int i=1;i<=tmp1;i++)
		{
			if(f) break;
			for(int j=1;j<=tmp2;j++)
			{
				int x=a1[i]*a2[j];
				int y=a*b/x;
				if((a+x)/x*x<=c&&(b+y)/y*y<=d)
				{
					cout<<(a+x)/x*x<<' '<<(b+y)/y*y<<endl;
					f=1;
				}
				if(f) break;
			}
		}
		if(!f) cout<<"-1 -1\n"; 
	}
}
```

---

## 作者：srds_cbddl (赞：7)

notice：本题解重点在于讲解如何使用查找算法通过此题，而非重点讲解数学内容。

## 坑点

- $10 ^ 5 \times {10 ^ 5} > 10 ^ 9$，要开 ```long long```；

- 题目使用 ```Special Judge```，所以样例没过的话自己测一下，大概是第 4 行有 2 种答案；

- 其实不用完全按照数学的思路去做这道题，不过必须推式子，暴力过不了。

## 暴力

**大体思路**

双重循环，使用 ```flag``` 标记是否找到，找到后直接输出，跳出循环即可。

$10 ^ {5} \times {10 ^ {5}} \times {10} = 10 ^ {11}$，略微 TLE。

**核心代码**

```cpp
bool flag = false;
for (int i = a + 1; i <= c; i ++) { // notice: long long
    if (flag) break;
    for (int j = b + 1; j <= d; j ++) {
        if (i * j % (a * b) == 0) {
            cout << i << ' ' << j << '\n';
            flag = true;
            break;
        }
    }
}
if (!flag) cout << "-1 -1\n";
```

实测 TLE on #9。

## 二分

**大体思路**

二分的简单优化在于只使用一个循环遍历每个 $x$，然后再二分 $y$，最后输出即可。

这里实际上需要简单推式子：

对于每个 $x$，$\because ab \mid xy \quad \therefore \frac {ab} {\gcd {x, ab}} \mid y$。看出这一点后，在 $10 ^ 5$ 范围内用二分查找有无符合 $b < y \le d$ 的数即可。

这个环节也可以通过其他查找方法解决，这里不再一一赘述。

**核心代码**

```cpp
for (int i = a + 1; i <= c; i ++) {
    int w = a * b / __gcd(a * b, i);
    int l = 1, r = 1e5, mid;
        while (l <= r) {
            mid = (l + r) / 2;
            if (b < mid * w && d >= mid * w) {
                flag = true;
                break;
            }
            else if (mid * w <= b) l = mid + 1;
            else r = mid - 1;
        }
        if (flag) {
            cout << i << ' ' << mid * w << '\n';
            break;
        }
    }
if (!flag) cout << "-1 -1\n";
```

实测 AC。

---

## 作者：GenesisCrystal (赞：6)

暴力。

## Solution

枚举 $i \in (a, c]$，算出 $o = \operatorname {lcm}(a \times b, i) \div i$，如果 $\lfloor \dfrac{d}{o} \rfloor  > \lfloor \dfrac{b}{o} \rfloor$，那么此时 $x = i,y = \lceil \dfrac{b+1}{o}\rceil \times o$。若果都不满足 $\lfloor \dfrac{d}{o} \rfloor  > \lfloor \dfrac{b}{o} \rfloor$，那么就无解。

## Code
短小精悍。
```cpp
#include <iostream>

using namespace std;
using ll = long long;

ll t, a, b, c, d;

ll gcd(ll x, ll y) {
  return y ? gcd(y, x % y) : x;
}

ll lcm(ll x, ll y) {
  return x * y / gcd(x, y);
}

int main() {
  for (cin >> t; t; t--) {
    cin >> a >> b >> c >> d;
    pair<ll, ll> ans = {-1, -1};
    for (ll i = a + 1; i <= c; i++) {
      ll o = lcm(a * b, i) / i;
      if (d / o > b / o) {
        ans = {i, (b + o) / o * o};
      }
    }
    cout << ans.first << ' ' << ans.second << '\n';
  }
  return 0;
}
```

---

## 作者：LHQing (赞：4)

### 题目分析：

思考一下，我们假使确定了 $x$，那么 $y$ 应该满足什么样的条件。

我们记 $p=ab$。

$\because p\mid xy$，记 $p=r\times s$，$x=r\times t$，并且 $\gcd(s,t)=1$。

$\therefore s\mid ty$，$\therefore s|y$。

$\therefore y$ 满足是 $s$ 的倍数，$y$ 最小的时候是 $s$，而当 $s$ 取最小的时候，$r$ 取最大，即 $\gcd(p,x)$。

因此我们每次统计出 $s$，令 $l=\left\lfloor\frac{b}{s}\right\rfloor+1$，$r=\left\lfloor\frac{d}{s}\right\rfloor$，这么操作类似于求 $\frac{y}{s}$ 的上界和下界。判断 $l$ 是否不大于 $r$。若是，说明有解，且其中一个解可以是 $l\times s$。否则，当前情况无解。然后不断枚举 $x$，若所有的 $x$ 都没有 $y$ 与之相对应，那么全局下无解。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd(x) push_back(x)
#define all(x) x.begin(),x.end()
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=1e5+10;
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
int T;
ll a,b,c,d;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>T;
	while(T--){
		cin>>a>>b>>c>>d;
		ll p=a*b;bool flag=false;
		for(ll i=a+1;i<=c;i++){
			ll g=gcd(i,p),k=p/g;
			ll l=b/k+1;
			ll r=d/k;
			if(l<=r){
				flag=true;
				printf("%lld %lld\n",i,l*k);
				break;
			}
		}if(!flag)puts("-1 -1");
	}return 0;
}
/*
1
12 21 14 24
*/
```



---

## 作者：_FastFT2013 (赞：4)

## Solution:

首先我们第一个想到的做法肯定是暴力做法:

枚举两个值 $i$ 和 $j$，$a<i\le c,b<j\le d$。

直到找到一个满足条件 $(ab \mid ij)$ 的 $i,j$ 输出即可。

但是这样的时间复杂度为 $O(n^2)$，无法通过。

第二种想法:

因为每一个 $i$ 都会对应一些（可能没有）满足条件的 $j$。

于是我们只用去枚举 $i$,找出满足条件的 $j$ 就好了。

对于满足 $a<i\le c$ 的 $i$，$\gcd(i,ab)$ 是 $i$ 和 $ab$ 共有的 **最大** 因子，则 $j$ 只要满足有因子 $\frac{ab} {\gcd(i,ab)}$ 就可以满足 $(ab \mid ij)$ 这个条件了。

我们现在设 $t=\frac{ab} {\gcd(i,ab)}$，则满足条件 $(ab \mid ij)$ 的 $j$ 一定是 $t$ 的倍数。

我们现在就是要找到一个正整数 $m$，使得 $b<mt\le d$ 就行了。$m$ 的最小值可以用不等式的性质进行求解，最终解得:

若 $b \nmid t$，则 $m$ 的最小值为 $\lceil \frac{b}{t} \rceil$，

若 $b \mid t$，则 $m$ 的最小值为 $\lceil \frac{b}{t} \rceil + 1$。

**注意：用以上方法进行求解 $m$ 可能不会满足 $mt\le d$ 这个条件，所以解出来后还需进行判断，如果不满足   $mt\le d$ 这个条件，就说明当此个 $i$ 没有对应满足所有条件的的 $j$。**

时间复杂度 $O(n \log n)$。
## Code:

```cpp
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#define ll long long
using namespace std;
const int N=105;
ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}
void solve(){
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	ll z=a*b;
	for(ll x=a+1;x<=c;x++){
		ll t;
		t=z/gcd(z,x);
		ll m=(b+t-1)/t;//作用相当于向上取整
		if(b%t==0){
		    m++;
		}
		if(t*m>b&&t*m<=d){
			cout<<x<<" "<<t*m<<"\n";
			return;
		}
	}
	cout<<"-1 -1\n";//若所有的i都没有对应解，那就是无解
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Fire_Kylin (赞：3)

## 题目翻译

给你四个数 $a,b,c,d$ 你需要找出一组 $x,y$ 使得 $ a<x≤c , b<y≤d$  并且 $x⋅y$  能被 $a⋅b$ 整除，如果没有输出 $-1 -1$ , 题目中所谓的 E1 和 E2，是这个题的两种版本。

## 我的做题过程
第一眼看到题的我：黄题？？？好简单啊！暴力谁不会

于是乎有了下面的代码：

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d;
int main(){
	register int i,j;
	scanf("%d",&n);//输入 
	while(n--){// n 组数据 
		scanf("%d%d%d%d",&a,&b,&c,&d);//输入 
		bool flag=0;
		for(i=a+1;i<=c;i++){//双层循环枚举 x 和 y 
			for(j=b+1;j<=d;j++) {
				if(i*j%(a*b)==0) { 
            		printf("%d %d\n",i,j);
            		flag=1;//如果符合条件就输出并退出 
            		break;
        		}
    		}
    		if (flag) break;//退出 
		}
		if(!flag) printf("%d %d\n",-1,-1); //如果没有找到答案，输出 -1 -1 
	}
return 0;
} 
```

然而，TLE 在了第9个点

So ,我剥掉了一层循环

于是乎又有了
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d;
int main(){
	register int i,j,k;
    cin>>t; //一样的输入 
    while(t--) {
        cin>>a>>b>>c>>d;
        bool flag=1;
        for(i=a+1;i<=c;i++) {//一层循环枚举 x 
            int y=a*b/__gcd (a*b,i);//算出 y 
            y=d/y*y;
            if (y>b) {
                cout<<i<<' '<<y<<endl;
                flag=0;//符合条件则输出 
                break;
            }
        }
        if(flag) cout<<-1<<" "<<-1<<endl;//不符合输出 -1 
    }
return 0;//没写 scanf （我懒）
}
```

然而 ~~（又然而了）~~，```int``` 爆了

不开  ```long long```  见祖宗
......

于是乎
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,c,d;
signed main(){
	register int i,j,k;
    cin>>t; //一样的输入 
    while(t--) {
        cin>>a>>b>>c>>d;
        bool flag=1;
        for(i=a+1;i<=c;i++) {//一层循环枚举 x 
            int y=a*b/__gcd (a*b,i);//算出 y 
            y=d/y*y;
            if (y>b) {
                cout<<i<<' '<<y<<endl;
                flag=0;//符合条件则输出 
                break;
            }
        }
        if(flag) cout<<-1<<" "<<-1<<endl;//不符合输出 -1 
    }
return 0;
}
```
AC

## 番外

这题其实是蛮简单的，~~（我居然写了好几遍）~~。另外，这道题还有二分等做法，其他题解也有写不同方法的，还是多多学习吧。

附时间复杂度计算：我使用的是较为粗略的计算方法，根据题目的数据范围计算循环次数，例如：

之所以我的第一份代码会超时，是因为 $a,b,c,d$ 的规模超过了 5000 ，$n$ 方的算法显然是不行的，而剥掉一层循环后，则一定在 $n$ 以内（上述复杂度仅是一组数据的，所以应该都乘以 $t$ ),二分会更快，一般是 $log  n$ , 你可以理解成根号 $n$。

所以，一道题目应该在充分考虑数据规模后，选取适用的算法来解决。

---

## 作者：guanyf (赞：3)

### 题意
- 给定 $a,b,c,d$，求是否存在 $x,y(a < x \le c,b < y \le d)$ 使得 $ab \mid xy$。

- $1 \le a,b,c,d \le 10^5$

### 分析、思路
我们可以考虑枚举 $x$。我们充分发扬人类智慧，题目中的式子可以转化成 $ab \mid x \bmod ab \times y$。根据数学直觉，实际上最小满足条件的 $ x \bmod ab \times y$ 就是 $\operatorname{lcm}(x \bmod ab ,ab)$。当知道了这个值，$y = \frac{\operatorname{lcm}(x \bmod ab ,ab)}{x}$。但可能 $y \le b$，因此 $y = (\frac{b}{y}+1) \times y$。当 $y \le d$ 时，$x,y$ 合法。

虽然这种做法对于这道题来说跑得飞快，却依然过不了 [CF1744E2](https://www.luogu.com.cn/problem/CF1744E2)。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int T, a, b, c, d;
void solve() {
  for (int i = a + 1; i <= c; i++) {
    int x = i % (a * b), y = __gcd(x, a * b);
    int res = a * b / y, t = (b / res + 1) * res;
    if (t <= d) {
      cout << i << ' ' << t << '\n';
      return;
    }
  }
  cout << "-1 -1\n";
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    cin >> a >> b >> c >> d;
    solve();
  }
  return 0;
}
```


---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1744E1)

## 题意

给定 $a,b,c,d$，找出一组 $x,y$ 使得 $a<x \le c,b<y \le d$ 并且 $x \cdot y$ 能被 $a \cdot b$ 整除，若没有输出 -1 -1。

## 思路

暴力，枚举 $x$，则 $y$ 为 $a \times b \div \gcd (a \times b,x)$ 的倍数。
用向下取整求出 $y$ 在 $y \le d$ 时的最大值。
若 $y>b$，即 $(x,y)$ 为一组答案。如果没找到输出 -1 -1。

注意 long long。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,d,x,y,fl;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a>>b>>c>>d;
        fl=0;
        for(x=a+1;x<=c;x++){
            y=a*b/__gcd(a*b,x);
            y=d/y*y;
            if(y>b){
                cout<<x<<" "<<y<<"\n";
                fl=1;
                break;
            }
        }
        if(!fl) cout<<"-1 -1\n";
    }
    return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

本题解与 E2 区分开来，不涉及 E2 知识点，~~因为模拟赛只开出来 E1。~~

------------

考虑暴力的枚举 $x$，事实上我们需要再求一个 $k$ 使得 $xy|k\times ab,b<k\times ab\div x\le d$，但如果直接暴力枚举所有的 $k$，会 [TLE on #25](https://codeforces.com/contest/1744/submission/267818754)。

考虑继续优化。若枚举的不是 $ab$ 的倍数，而是 $ab$ 和 $x$ 的公倍数，记其为 $t$，此时一定 $x|kt$，大量减少不存在 $y$ 的情况。

code：

```cpp
signed main(){
    std::cin>>t;
    while(t--){
        bool flag=false;
        std::cin>>a>>b>>c>>d;
        for(int x=a+1;x<=c;x++){//枚举x
            int t=lcm(a*b,x);//同上文
            for(int i=1;i*t/x<=d;i++)//枚举t的倍数，并且保证y小于等于d
                if(i*t/x>b){//合法情况
                    std::cout<<x<<" "<<i*t/x<<"\n";//输出x和y
                    flag=true;//标记已求出答案
                    break;
                }
            if(flag)
                break;
        }
        if(not flag)
            puts("-1 -1");//若未求出答案输出-1 -1
    }
    return 0;//撒花！
}
```

本题有 SPJ，与样例输出不同是正常情况，可以自己手玩一下。

---

