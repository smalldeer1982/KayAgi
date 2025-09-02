# [ARC141A] Periodic Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc141/tasks/arc141_a

正整数 $ n $ に対し、$ n $ を十進法表記した文字列を $ \mathrm{str}(n) $ で表します。

正整数 $ n $ について、ある正整数 $ m $ が存在して $ \mathrm{str}(n) $ が $ \mathrm{str}(m) $ を $ 2 $ 個以上連結したものになっているとき、 $ n $ は「周期的な数」であるといいます。たとえば $ 11,\ 1212,\ 123123123 $ は「周期的な数」です。

$ 11 $ 以上の正整数 $ N $ が与えられます。 $ N $ 以下の「周期的な数」の最大値を求めてください。 $ N $ 以下の「周期的な数」は $ 1 $ つ以上存在することが示せます。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^4 $
- $ 11\ \leq\ N\ <\ 10^{18} $
- 入力される値はすべて整数

### Sample Explanation 1

$ 1 $ 個目のテストケースについて、 $ 1412 $ 以下の「周期的な数」にはたとえば $ 11,\ 222,\ 1212,\ 1313 $ などが考えられますが、このうち最大のものは $ 1313 $ です。

## 样例 #1

### 输入

```
3
1412
23
498650499498649123```

### 输出

```
1313
22
498650498650498650```

# 题解

## 作者：cjh20090318 (赞：6)

一个不怎么需要动脑筋的做法，看了一圈题解区没有一篇题解提到，虽然效率不高但是还是来记录一下。

## 题意

给定一个正整数 $N \ge 11$，求不超过 $N$ 最大拥有循环节的数。

## 分析

因为答案有单调性，所以这种求不超过最大的问题可以二分答案转化为判定性问题。

外层循环枚举循环次数，内部二分重复的数即可。

单次时间复杂度 $O(\log_{10}n\log_2{n})$，效率比较低。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
LL n;
int w(const LL&x){return int(log10((long double)x))+1;}//求正整数位数。
LL p1[20];
LL f(const int x,int t){
	LL ret=0;
	int q=w(x);
	if(q*t>18) return n+1;//位数太多直接返回 n+1。
	while(t--) ret=ret*p1[q]+x;
	return ret;
}
void solve(){
	scanf("%lld",&n);
	LL ans=0;
	for(int i=2,mi=w(n);i<=mi;i++){
		int l=1,r=p1[mi/i+1];
		for(int mid;l<r;) f(mid=(l+r+1)>>1,i)>n?r=mid-1:l=mid;//二分找到最后一个小于等于 n 的数。
		LL k=f(l,i);
		k<=n&&(ans=max(ans,k));//取最大值。
	}
	printf("%lld\n",ans);
}
int main(){
	p1[0]=1;
	for(int i=1;i<=18;i++) p1[i]=p1[i-1]*10;
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：2)

**这道题是不大于 $n$ 的最小整数，而不是小于 $n$！！！**

下文中 $n$ 表示 $|s|$。

对于所有的 $k$ 满足 $k\mid n$，对前 $k$ 个数位进行生成，记前 $k$ 位构成数 $x$，整个数是 $x2$。首先，将 $x$ 复制 $\dfrac{n}{k}$ 次得到 $xx$，当 $xx\le x2$ 时更新答案，否则当 $x$ 不为 $10^k$ 时，用 $x-1$ 复制 $\dfrac{n}{k}$ 次得到的值更新。

答案最初设为 $\sum^{n-1}_{i=1}(9\times10^i)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Dino{
inline int r(){
  int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}return x*f;
}
int t;
int get(int n,int le,int c){
	int x=pow(10,le),a=0;for(int i=1;i<=c;++i)a=a*x+n;return a;
}
inline void bigdino(){
  string s;cin>>s;int n=s.size(),x=0,Ans,xx,x2=0;Ans=get(9,1,n-1);
  for(int i=0;i<n;++i)x2=x2*10+s[i]-'0';
  for(int i=1,j=1;i<=n/2;++i,j*=10){
    x=x*10+s[i-1]-'0';if(n%i==0){
    xx=get(x,i,n/i);if(xx<=x2)Ans=max(Ans,xx);else if(x!=j){
      xx=get(x-1,i,n/i);Ans=max(Ans,xx);
      }
    }
  }cout<<Ans<<'\n';
}
inline void _(){
	t=r();while(t--)bigdino();
}
}
signed main(){Dino::_();}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

# 题解：AT\_arc141\_a \[ARC141A] Periodic Number

考试时竟然没做出来！！！（失败了）

## 解法

看到题目，由于 $n \le 10^{18}$，所以我们考虑枚举循环节的位数 $i$，设 $len$ 为 $n$ 的长度，在 $len \bmod i = 0$ 的情况下，将 $n$ 分成 $\frac{len}{i}$ 组，那么，我们只需要计算出所有组可以达到的最大值即可，再注意一下答案的初值：$len - 1$ 个 $9$ 永远都可以。这里可以暴力算，但也可以用更巧妙的方法，设 $q = 0...010...010...01$，其中 $i - 1$ 个 $0$ 后面跟上一个 $1$ 作为一个循环节（$0...01$）（就是循环节长度为 $i$ 时的数的因数），这样答案就很显然是 $\lfloor \frac{n}{q} \rfloor \times q$ 了（具体看代码吧！）。

## 代码

```
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

#define int long long

void init(vector<int>& a) {
    a[0] = 1;
    for (int i = 1; i <= 18; i++)
        a[i] = a[i - 1] * 10;
}
int solve(int x, const vector<int>& pow10) {
    int len = to_string(x).size(), res;
    res = pow10[len - 1] - 1;
    for (int i = 1; i < len; i++) 
        if (len % i == 0) {
            int t = len / i, q = 0;
            for (int j = 0; j < t; j++)
                q += pow10[j * i];
//构造循环节长度为i的基数
            res = max(res, x / q * q);
//求出n是它的多少倍，在乘回来
        }
    return res;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
    vector<int> pow10(20);
    init(pow10);
// 预处理10^x，方便未来计算
	int T, x;
	cin >> T;
	while (T--) {
		cin >> x;
		cout << solve(x, pow10) << '\n';
	}
	return 0;
}

```

---

## 作者：chinazhanghaoxun (赞：1)

## 思路
假设 $N$ 的位数为 $K$，由于这道题的 $N\le 10^{18}$，所以想到可以枚举 $K$ 的所有因数表示这个循环节的位数 $X$。那么我们只要复制这个前缀 $\frac{K}{X}$ 遍即可。注意还有一种情况就是 $K-1$ 个 $9$ 的数也是永远满足条件的一个数字。

还有一个技巧就是对于这种需要分裂位数的可以预处理一个 $ten$ 数组，$ten_i\gets 10^i$。用法见代码。
## 代码+注释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	vector<long long> ten(19);
	ten[0]=1;
	for(int i=0;i<17;i++) //预处理10的次方数组 
		ten[i+1]=ten[i]*10;
	
	int T;
	cin>>T;	
	
	for(int i=0;i<T;i++){
		long long N;
		cin>>N;
		int Len=to_string(N).size(); //数字位数 
		long long ans=ten[Len-1]-1; //全为9的情况 
		
		for(int j=1;j<Len;j++){
			if(Len%j==0){ //是长度的因数 
				long long q=0;
				for(int k=0;k<Len/j;k++){
					q+=ten[k*j]; //计算出最大的循环的因数 
				}
				long long p=N/q*q;
				ans=max(ans,p); //取最大数 
			}
		}
		
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Star_Rail (赞：1)

根据题目我们可以知道，有周期性的数至少循环两次。并且我们可以知道这种数一定是若干个 $10$ 的幂次方的和的倍数。

例如：$12341234 = 10001\times1234$
我们可以令 $k$ 为输入的数 $n$ 的长度，所以求不大于 $n$ 的最大的好数的长度是 $k$ 或 $k-1$。

### 接下来分两种情况：

第一种情况：长度等于 $k$：我们可以令 $d$ 为 $10$ 的幂次方的和那个数，然后我们就可以的到这样一个式子：
$$d = \sum\limits_{i=0}^{\frac{k}{l}-1}{{10^{i\times l}}}$$
   然后 $\lfloor \frac{n}{d}\rfloor$ 就是每个周期的数字，再乘上 $d$ 就是小于 $n$ 的周期数,再求最大值就是答案了；

第二种情况：长度等于 $k-1$：在这种情况下，$k-1$ 个 $9$ 就是情况二的答案；

之后把情况一与情况二求最大值就可以了。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T,x;
int d;
int maxx;
int temp;
int mi[25];

int t(int s){
	int k=0;
	while(s){
		k++;
		s/=10;
	}
	return k;
}

main(){
	ios::sync_with_stdio(false);
	cin>>T;
	mi[0] = 1;
	for (int i=1;i<=18;i++) mi[i] = mi[i-1]*10;
	while (T--){
		cin>>x;
		int k = t(x);
		int ans = mi[k-1]-1;
		maxx = -1;
		for(int l=1;l<k;l++){
			if (k%l!=0) continue;
			d = 1;
			for (int i=1;i<k/l;i++) d+=mi[i*l];
			int f = (x/d)*d;
			if (x/d < mi[l-1]) continue;
			ans=max(ans,f);
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc141_a)
# 题意
给出一个 $1 \le x < 10^{18}$，求最大的有循环节并且小于等于 $x$ 的数是多少。
# 思路
首先，设 $x$ 的位数为 $k$，那么可得，答案的位数**只会**是 $k$ 或 $k-1$，那么分类讨论。
- 若答案位数为 $k-1$，很明显，直接输出 $k-1$ 个 $9$。这种情况适用于 $k \bmod 2 = 1$ 或 $k = 10 ^ { N }$，并且 $N$ 为正整数。
- 答案位数为 $k$，可以枚举出所有循环节。设循环节的位数为 $i$，那么当 $k \bmod i = 0$，将这个循环节复制 $\frac{k}{i}$ 份，然后用变量存储所有答案的最大值，输出即可。

蒟蒻码风过丑，就不放了，求关~

---

## 作者：Novelist_ (赞：0)

设 $k$ 是 $x$ 的位数，容易证明，最大好数的位数仅可能是 $k-1$ 或 $k$。那么我们就分类讨论。

第一种情况：很明显，直接输出 $k-1$ 个 $9$。这种答案仅适合 $k$ 为奇数或数像 $1000$ 这样的。

第二种情况：由于数据不大，所以我们可以直接枚举出循环节。首先我们设 $i$ 是枚举出来循环节的位数，当 $i$ 是 $x$ 的因数时，我们枚举出循环节 $n$，并将 $n$ 复制 $\frac{k}{i}$ 份，然后与 $ans$ 作比较，若比 $ans$ 大则更新答案。

题目有点简单，代码就不放了。

---

## 作者：XYQ_102 (赞：0)

## 题意
输出不大于 $N$ 的最大周期数
## 思路
考虑枚举所有与 $N$ 的位数相同的合适周期数，即对 $N$ 考虑可能满足条件的最大周期数。

同时，优先考虑前缀构成周期数，再考虑特殊数输出 $999\cdots999$。
## Code
```cpp
inline void solve()
{
  string s; cin >> s;
  int n = (int)s.size();
  int x = stoll(s);
  int ans = 0;
  for (int i = 1; i < n; i ++)
    if (n % i == 0)
    {
      int l = n / i;
      int now = stoll(s.substr(0, i));
      int now1 = now - 1; // 如果当前前缀周期单位数不满足要求，就考虑少1的周期数
      string pre = to_string(now); // 比如114514这个数可以114114
      string pre1 = to_string(now1); // 但是114110这个数只考虑113113
      string x1, x2; // 凑成完整与N位数相同的数
      for (int j = 0; j < l; j ++)
      {
        x1 += pre;
        x2 += pre1;
      }
      int y1 = stoll(x1); // 凑位结束后进行转换
      int y2 = stoll(x2); // 当然位数相同比较字典序也是一样的
      if (y1 <= x)
        ans = max(ans, y1);
      if (y2 <= x)
        ans = max(ans, y2);
    }
  int Max = stoll(string(n - 1, '9')); // 考虑奇位可以出现的 999...99
  cout << max(Max, ans) << '\n'; // 形如1111110这样的数都是 999...99
}
```

---

## 作者：Down_syndrome (赞：0)

## 一句话题意
找到最大的不大于 $n$ 的有循环节的数。其中 $x\le10^{18}$。
## 思路
首先分类讨论。令 $k\gets\log_2(n)+1$，即 $k$ 为 $n$ 的位数，$num(i,j)$ 表示 $n$ 从左到右第 $i$ 位到第 $j$ 位组合成的数，$times(i,j)$ 表示 $i$ 循环 $j$ 次的数，则有：
- 如果存在位数为 $k$ 的有循环节的数，因为 $k$ 最多只有 $18$，所以可以枚举 $k$ 的因数，设为 $i$。如果循环节为 $num(1,i)$ 合法，则最大为 $times(num(1,i),k/i)$。否则为 $times(num(1,i)-1,k/i)$。如：
- 如果不存在位数为 $k$ 的有循环节的数（例如 $1009$），答案自然为 $times(9,k-1)$。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,k,s,ans,num[20][20];
ll cnt(ll x){
	return n%(ll)(pow(10,x))/(ll)(pow(10,x-1));
}
ll times(ll x,ll tim){
	ll p=(ll)(pow(10,(ll)(log10(x))+1)),s=0;
	for(int i=1;i<=tim;i++) s=s*p+x;
	return s;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		k=(ll)(log10(n)+1);
		memset(num,0,sizeof(num));
		for(int i=1;i<=k;i++) for(int j=i;j<=k;j++) num[i][j]=num[i][j-1]*10+cnt(k-j+1);
		ans=0;
		for(int i=1;i<k;i++){
			if(k%i) continue;
			if(times(num[1][i],k/i)<=n) s=times(num[1][i],k/i);
			else s=times(num[1][i]-1,k/i);
			ans=max(ans,s);
		}
		printf("%lld\n",max(ans,times(9,k-1)));
	}
	return 0;
}
```


---

