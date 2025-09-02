# Boneca Ambalabu

## 题目描述

Boneca Ambalabu 给你一个包含 $n$ 个整数的序列 $a_1,a_2,\ldots,a_n$。

在所有 $1 \leq k \leq n$ 中，输出 $(a_k \oplus a_1) + (a_k \oplus a_2) + \ldots + (a_k \oplus a_n)$ 的最大值。注意 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 说明/提示

在第一个测试用例中，我们能得到的最大值是 $(18 \oplus 18) + (18 \oplus 18) + (18 \oplus 18) = 0$。

在第二个测试用例中，我们选择 $k=5$ 得到 $(16 \oplus 1) + (16 \oplus 2) + (16 \oplus 4) + (16 \oplus 8) + (16 \oplus 16) = 79$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
18 18 18
5
1 2 4 8 16
5
8 13 4 5 15
6
625 676 729 784 841 900
1
1```

### 输出

```
0
79
37
1555
0```

# 题解

## 作者：FishPressedCoins (赞：2)

我采用“分别求得每一个数与数组所有数异或的总和进行比较”来求得最终答案。当然，如果将所有数遍历一遍肯定会超时，所以我们可以换一种方式求得异或和。

首先 $int$ 类型转换为二进制有 $32$ 位，我统计这个数组中每一个数的每个二进制位出现一的次数，根据异或原则，两个数互相异或，二进制位同为一或者同为零的情况下，这个二进制位异或后为零，相反情况为一。

那么我就可以利用之前我统计好的数组，直接算出这个二进制位当前的贡献是多少，只需要 $30$ 次二进制位遍历就可以算出这个数异或数组后的异或和。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int T, N;
//a[i][0]表示第i个数的第1个二进制位是否为1，是为1，否为0
long long a[200005][35];
//统计所有二进制位，1的数量
int sum[35];
int main()
{
	cin >> T;
	while (T--) {
		cin >> N;
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= N; i++) {
			memset(a[i], 0, sizeof(a[i]));
			//这里我图方便用a[i][33]直接存储数组的数据
			cin >> a[i][33];
			for (int j = 30; j >= 0; j--) {
				if (((1 << j) & a[i][33]) != 0) {
					sum[j]++, a[i][j]++;
				}
			}
		}
		long long ans = 0, S = 0;
		//遍历所有可能的答案
		for (int i = 1; i <= N; i++, S = 0) {
			for (int j = 0; j < 31; j++) {
				//如果这个二进制位为1，那么数组中数据的所有这个二进制位，只要是1就没有贡献
				if (((1 << j) & a[i][33]) != 0) {
					//所以统计二进制位为零的数量
					S += ((1ll << j) * (N - sum[j]));
				}
				else {
					//相反就是有贡献，直接加上
					S += ((1ll << j) * sum[j]);
				}
			}
			ans = max(ans, S);
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：2)

考虑拆位。

对于每个二进制位 $x$，我们记录有多少 $a_i$ 满足 $a_i$ 在二进制下的第 $x$ 为 $0$ 或 $1$。然后枚举 $k$，计算每一个二进制为为 $0$ 或 $1$ 时对答案产生的贡献即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int k[N], er[32][2];
 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> k[i];
			for (int j = 0; j <= 30; j++) {
				bool e = k[i] & (1 << j);
				er[j][e]++;
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int tmp = 0;
			for (int j = 0; j <= 30; j++) {
				bool e = k[i] & (1 << j);
				tmp += er[j][1 - e] * (1 << j);
			}
			ans = max(ans, tmp);
		}
		cout << ans << "\n";
		memset(er, 0, sizeof(er));
	}
}

```

---

## 作者：Killer_Steven (赞：1)

# 题目大意  
给出一个长度为 $n$ 的数组，设 $a_k$ 为数组中的某个元素，求出 $a_k$ 异或数组中所有元素的和的最大值。   
**注意**：多组测试数据，记得清空数组。  

# 解题思路  
首先，正常人（排除某些神犇）肯定会去想暴力，一一枚举，这里就不细说了，直接给代码。  
```cpp
#include<bits/stdc++.h>
#define db double
#define ll long long
#define str string
using namespace std;
const ll MAXN = 2e5+5;
ll t, n, a[MAXN], ans, cnt;
int main()
{
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (ll i = 1; i <= n; ++i) cin >> a[i];
		for (ll i = 1; i <= n; ++i)
		{
			for (ll j = 1; j <= n; ++j)
				cnt += (a[i] ^ a[j]);
			ans = max (ans, cnt), cnt = 0;
		}
		cout << ans << endl, ans = 0;
	}
	return 0;
}
```
显然会超时。  

那我们该怎么办呢？让我们先回顾一下**异或**的本质。异或就是将两个数的二进制位逐位比较，如果相同就为 $0$，不同则为 $1$ 然后将得到的结果组成一个新的数字。  

很显然，只有一个二进制位与 $a_k$ 对应的二进制位**不同**时，这个二进制位才回做出**贡献**，使得当前结果增加。  

按照这个思路，我们可以将所有数转化为二进制后，将每一个二进制位上 $0$ 和 $1$ 各**出现次数**统计起来，以后使用时就不需要在一个数一个数的计算。  
这些功能的实现都非常简单，直接上代码。  
# code  
```cpp
#include<bits/stdc++.h>
#define db double
#define ll long long
#define str string
using namespace std;
const ll MAXN = 2e5+5;
ll t, n, a[MAXN], ans, cnt, tot[100][5], maxn = 31;
//转化为二进制
inline str gbt (ll x) {
	str s = "";
	while (x) {
		s = to_string (x % 2) + s;
		x /= 2;
	}
	//为了方便确定当前位是第几位，所有字符串同意将长度设为31
	while (s.size() < maxn) s = '0' + s;
	return s;
}
//统计每个数位上0和1出现的次数
inline void tj (str s) {
	for (ll i = 0; i < s.size(); i++) {
		if (s[i] == '0') tot[s.size() - i][0]++;
		else tot[s.size() - i][1]++;
	}
}
int main() {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t--) {
		memset (tot, 0, sizeof tot);
		cin >> n;
		for (ll i = 1; i <= n; ++i) cin >> a[i], /*统计0、1数量*/tj (gbt (a[i]) );
		for (ll i = 1; i <= n; ++i) {
			str s = gbt (a[i]); //将当前所选数字转化为二进制
			while (s.size() < maxn) s = '0' + s; //补齐高位
			for (ll i = 0; i < s.size(); i++)
				if (s[i] == '0')           //如果当前位是0，那么只有1才回做出贡献
					cnt += (/*有多少个1就能增加多少贡献*/tot[s.size() - i][1] * /*二进制转十进制，不多说*/pow (2, maxn - i - 1) );
				else                        //若为1，则0做出贡献
					cnt += (tot[s.size() - i][0] * pow (2, maxn - i - 1) );
			ans = max (ans, cnt), cnt = 0;     //求最大值
		}
		cout << ans << endl, ans = 0;
	}
	return 0;
}
```

---

## 作者：Ag2WO4 (赞：1)

可以先将异或拆成相加再减去二倍的重叠部分，发现相加部分是 $na_k+s$（$s$ 为数列总和），重叠部分可以统计 $a_i$ 每一位的数量，然后逐个逐位比对相减，答案为 $s+\max(na_k-2\sum_{j=0}^{29}2^ja_{kj}s_j)$，其中 $a_{kj}$ 代表 $a_k$ 的二进制第 $j$ 位是否为一。提前统计好和数列在第 $j$ 位上的统计和 $s_j$ 以及所有数的总和 $s$ 就可以实现 $O(n)$ 的复杂度（虽然拿 Python 交的话不用集合优化会被卡掉数据完全一致的临界点，用又差点被卡数据两两不同的临界点，好在 $1952\text{ms}$ 极限通关）。

#### Python 代码
```python
for _ in range(int(input())):
    n=int(input());a=[0]*30;b=list(map(int,input().split()))
    for i in b:
        for j in range(30):
            if(1<<j)&i:a[j]+=2
    print(sum(b)+max(n*i-sum(a[j]*(i&(1<<j))for j in range(30))for i in set(b)))
```
#### C/C++ 代码
```c
#include<stdio.h>
long long n,a[30],b[200000],t,i,j,s,m,k;
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        for(j=0;j<30;++j)a[j]=0;
        m=-1<<30;
        m<<=30;
        s=0;
        scanf("%lld",&n);
        for(i=0;i<n;++i)
        {
            scanf("%lld",&b[i]);
            s+=b[i];
            for(j=0;j<30;++j)if(1<<j&b[i])a[j]+=2;
        }
        for(i=0;i<n;++i)
        {
            k=n*b[i];
            for(j=0;j<30;++j)k-=a[j]*(1<<j&b[i]);
            m=k>m?k:m;
        }
        printf("%lld\n",s+m);
    }
}

---

## 作者：IGpig (赞：0)

## CF2094E

### Solution

看到异或，可以很明显想到二进制。先枚举答案 $x$，对于 $x$ 的每一个二进制位，只有与它异或的另一个数的那一位与其相反才有用。

所以我们可以把每一位的 $1$ 的数量加起来，然后枚举答案时可以直接计算。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
LL t;
LL n, ans, a[200005], f[31], g[35] = {1};
int main() {
	for (int i = 1; i <= 31; i++) g[i] = g[i - 1] * 2;
	cin >> t;
	while (t--) {
		memset(f, 0, sizeof(f));
		cin >> n;
		ans = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			LL p = a[i], cnt = 0;
			for (LL j = 30; j >= 0; j--) {
				if (p >= g[j]) {
					p -= g[j];
					f[j]++;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			LL sum = 0;
			for (int j = 0; j <= 30; j++) {
				sum += g[j] * ((a[i] & (1 << j)) ? (n - f[j]) : f[j]);
			}
			// cout<<a[i]<<' '<<sum<<endl;
			ans = max(ans, sum);
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：kent2017 (赞：0)

对于二进制从小往大数的第 $i$ 位而言，若数组  $a$ 中有  $x$ 个第  $i$ 位为 $1$ 的数，那么选一个第 $i$ 位为 $0$ 的数作为 $a_k$ ，第 $i$ 位会产生 $2^{i-1}\times x$ 的贡献，反之则为 $2^{i-1}\times (n-x)$。

于是，我们统计二进制下每一位的数量，并计算贡献，最后就能在 $O(n \log(\max(a_i)))$ 的时间复杂度下求出对于每个 $a_i$ 作为 $a_k$ 时的结果了。

```
#include<bits/stdc++.h>
using namespace std;
long long a[200001],cnt[31];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	long long t;cin>>t;++t;
	for(;--t;){
		long long n,ans=-1;cin>>n;
		for(long long i=0;i<31;++i){//多测记得清空 
			cnt[i]=0;
		}
		for(long long i=1;i<=n;++i){
			cin>>a[i];
			for(long long j=0;j<=30;++j){//统计1数量 
				if(a[i]&(1<<j)){
					++cnt[j];
				}
			}
		}
		for(long long i=1;i<=n;++i){
			long long cnti=0;
			for(long long j=0;j<=30;++j){
				if(a[i]&(1<<j)){//这一位是1,所有这一位为0的数产生贡献 
					cnti+=(n-cnt[j])*(1<<j);
				}else{
					cnti+=(cnt[j])*(1<<j);//这一位是0,所有这一位为1的数产生贡献 
				}
			}
			if(cnti>ans){//更新答案 
				ans=cnti;
			}
		}
		cout<<ans<<endl;
	} 
	return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
请你求出 $(a_k\oplus a_1)+(a_k\oplus a_2)+(a_k\oplus a_3)+\cdots+(a_k\oplus a_n)$（$1\le k\le n$）的最大值。
## 题目解法
我们发现两个数的异或值跟各个二进制位有关系，由于分别计算两两之间的异或值复杂度大，所以可以先把各个二进制位出现的数量统计出来，然后计算即可，复杂度为 $O(n\log a_i)$。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 2e5 + 10, kMaxM = 30;

int a[kMaxN], cnt[kMaxM], t, n, ans;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; memset(cnt, 0, sizeof(cnt)), ans = 0) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      for (int j = 0, x = a[i]; j < 30; j++, x /= 2) {  // 统计二进制位数量
        cnt[j] += x % 2;
      }
    }
    for (int i = 1; i <= n; i++) {
      int sum = 0;
      for (int j = 0, x = a[i]; j < 30; j++, x /= 2) {  // 计算异或值
        (x % 2) ? (sum += (n - cnt[j]) * (1 << j)) : (sum += cnt[j] * (1 << j));
        // 如果该位位为 1 就加上 0 的数量，反之加上 1 的数量
        // 注意：每个数量求出来后还要乘上位权
      }
      ans = max(ans, sum);
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个整数数组 $a$，求其中之一 $a_k$ 异或其它所有整数之和的最大值。

### 思路：

显然整数个数比较多不好下手，从二进制位上考虑。

由于 $a_k$ 的每一位必然是 $0$ 或者 $1$，所以我们可以对于每一位，预处理当前这一位的 $a_k$ 如果是 $0$ 或者 $1$ 的话，能对最终结果造成多少贡献。预处理这一步一共是 $O(nD)$，$D$ 表示二进制位数。

接下来可以直接暴力扫一遍所有的 $a$，对于每一位提取它的贡献并且加和，最后找出最大值。所以还是 $O(nD)$ 的。

### 程序如下：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2e5+5,D=35;
int T,n,a[N];
long long con[D][2],power[D];
int main(){
	scanf("%d",&T);
	power[0]=1;
	for(int i=1;i<=30;i++)power[i]=power[i-1]*2;
	while(T--){
		long long ans=0;
		scanf("%d",&n);
		memset(con,0,sizeof(con));
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			int tmp=a[i];
			for(int j=1;j<=30;j++){
				con[j][!(tmp%2)]+=power[j-1];
				tmp/=2;
			}
		}
		for(int i=1;i<=n;i++){
			int tmp=a[i];
			long long nowans=0;
			for(int j=1;j<=30;j++){
				nowans+=con[j][tmp%2];
				tmp/=2;
			}
			if(nowans>ans)ans=nowans;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


### THE END

![](https://cdn.luogu.com.cn/upload/image_hosting/xnjqrk08.png)

---

## 作者：jinhangdong (赞：0)

首先将这些数转化成二进制，然后遍历每一个数，枚举每一个二进制位，先看自己这一位是几，如果是 $1$，那么看有几个 $0$，如果是 $0$，那么看有几个 $1$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,Max,ans,a[N],sum[35][2];
signed main()
{
	cin>>t;
	while(t--)
	{
		Max=0;
		memset(sum,0,sizeof(sum));
		cin>>n;
		for(int i=1;i<=n;++i)
		{
			cin>>a[i];
			int x=a[i],cnt=0;
			for(int j=0;j<32;++j)//转二进制
			{
				sum[cnt++][x%2]++;//统计这一位几个0，几个1
				x/=2;
			}
		}
		for(int i=1;i<=n;++i)
		{
			ans=0;
			for(int j=0;j<32;++j)
			{
				if((1<<j)&a[i]) ans+=sum[j][0]*(1<<j);
				else ans+=sum[j][1]*(1<<j);
			}
			Max=max(Max,ans);
		}
		cout<<Max<<"\n";
	}
	return 0;
}
```

---

