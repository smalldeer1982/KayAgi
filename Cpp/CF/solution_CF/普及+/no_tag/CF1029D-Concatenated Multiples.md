# Concatenated Multiples

## 题目描述

You are given an array $ a $ , consisting of $ n $ positive integers.

Let's call a concatenation of numbers $ x $ and $ y $ the number that is obtained by writing down numbers $ x $ and $ y $ one right after another without changing the order. For example, a concatenation of numbers $ 12 $ and $ 3456 $ is a number $ 123456 $ .

Count the number of ordered pairs of positions $ (i,j) $ ( $ i≠j $ ) in array $ a $ such that the concatenation of $ a_{i} $ and $ a_{j} $ is divisible by $ k $ .

## 说明/提示

In the first example pairs $ (1,2) $ , $ (1,3) $ , $ (2,3) $ , $ (3,1) $ , $ (3,4) $ , $ (4,2) $ , $ (4,3) $ suffice. They produce numbers $ 451 $ , $ 4510 $ , $ 110 $ , $ 1045 $ , $ 1012 $ , $ 121 $ , $ 1210 $ , respectively, each of them is divisible by $ 11 $ .

In the second example all $ n(n-1) $ pairs suffice.

In the third example no pair is sufficient.

## 样例 #1

### 输入

```
6 11
45 1 10 12 11 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 2
2 78 4 10
```

### 输出

```
12
```

## 样例 #3

### 输入

```
5 2
3 7 19 3 3
```

### 输出

```
0
```

# 题解

## 作者：BLUESKY007 (赞：4)

$qwq$昨天晚上$Div.3$过了这道题...早上交了$1A$...看在$CF$上$hack$的情况并不乐观而且也没人来交这题的份上...我决定发一篇题解帮$(zhuang)$助$(yi)$大$(bo)$家$(x)$  
题目大意:给出$n$个数$a_1,a_2,\dots,a_n$和$k$,求对于任意的两个数$a_i,a_j(i\neq j)$,使得两数连接起来组成的新数(如$12$与$3456$连接组成$123456$)是$k$的倍数的选定方式共有多少种.  
很显然检验所有的组合并不现实,一共有$n\times (n-1)$个新数组成方法(~~n方乱搞绝对T飞~~),所以显然需要用一些特$(qi)$殊$(ji)$方$(yin)$法$(qiao)$来搞定这道题.  
利用这是一道数论题的性质,显然涉及到整除可以从余数的角度考虑~~(这还用想吗)~~,考虑到题目上拼接的操作对余数的影响,我们可以对所有的$a_1,a_2,\dots,a_n$进行预处理,只需要找到合适的$i,j(i\neq j)$使得$a_i\times (\lfloor log_{10}a_j\rfloor+1)+a_j=0(mod\ k)$即可.  
所以只需找出能与$a_i$组成$k$的倍数的$a_j$个数并累加即可,个数由预处理得到.  
预处理在本题中显得尤为重要,对于每一个数$a_i$都可以前接$a_j$,由于连接操作对前数的余数影响取决于后数的位数,故我们需要判断$a_i$的位数下对应能与$a_i$余数加和成为$k$的倍数的数的个数,所以预处理的内容就是后接$m(m\in [1,10])$位数后各余数对应数字的个数~~(表达能力掉线...感性理解一下)~~  
梳理一下思路:先对所有的$a_1,a_2,\dots,a_n$,处理每个数后接$m(m\in [1,10])$位数后的余数情况(在此选用$map$存储...毕竟余数值域是$[0,10^9-1]$...处理对应$map$中后接$m$位时的余数作为下标的值$+1$即可统计个数),同时考虑到这样做有可能把$a_i$后接$a_i$的情况记入答案,所以在累加后特判一下$a_i$后接$a_i$的情况是否合法,合法时将$ans--$去重.  
下面放代码$\downarrow \downarrow \downarrow$...如果实在理解不了的话...我也没什么办法惹~~(逃)~~
```cpp
#include<cstdio>//CF1029D
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<map> 

using namespace std;

map<int,int>mp[11];

const int N=2e5+5;

const long long shi[11]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000};

int ws(int u){
	return (int)log10(u)+1;
}

int n,k,a[N],mo[N];

long long ans;

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mo[i]=a[i]%k;
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++){
			mp[j][(int)(((shi[j]%k)*mo[i])%k)]++;
		}
	}
	for(int i=1;i<=n;i++){
		int w=ws(a[i]);
		ans+=mp[w][(k-mo[i])%k];
		if((int)((((shi[w]%k)*mo[i])%k)+mo[i])%k==0){
			ans--;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
小小卡了一下常数刚好跑过$qwq$...生死速度就差$35ms$~~(逃)~~

$update1:(20180828)$  
由于本题毒瘤卡常卡的厉害...上面代码还是有可能会T~~(都怪CF评测机...脸黑就是过不了(逃))~~...所以再放一个卡了常数的代码...亲测$1887ms$跑过...应该算是比较保险了...
```cpp
#include<cstdio>//CF1029D
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<map> 

using namespace std;

map<int,int>mp[11];

const int N=2e5+5;

int ws(int u){
	return (int)log10(u)+1;
}

int n,k,a[N],mo[11][N];

long long ans;

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mo[0][i]=a[i]%k;
		for(int j=1;j<=10;j++){
			mo[j][i]=(int)(((long long)mo[j-1][i]*10)%k);
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++){
			if(mo[j][i]){
				mp[j][mo[j][i]]++;
			}
			else{
				mp[j][0]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		int w=ws(a[i]);
		if(mo[0][i]){
			ans+=mp[w][k-mo[0][i]];
		}
		else{
			ans+=mp[w][0];
		}
		if((mo[w][i]+mo[0][i])%k==0){
			ans--;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：fighter (赞：3)

# 【题解】CF1029D Concatenated Multiples

[原题传送门](<https://www.luogu.org/problemnew/show/CF1029D>)

## Solution

我们发现，题目中要求的"把a接到b前面"实际上等于$a*10^{log_{10}b}+b$。于是我们自然想到预处理出$a_i*10^x \mod k$，显然$x$不会超过10。然后对于每个$a_i$，查询有多少数接到自己前面可以被$k$整除。

预处理和枚举$a_i$的$O(n)$复杂度是不可避免的，那么我们就考虑如何加快询问速度。

最容易想到的是，我们对于每个$x$，把$a_i^{x}\mod k$插入到一个``map​``中。这样最多开10个``map``，并且每次查询只需$log_2n$的时间，理论上可以通过此题。

然而到这一步的时候，我就看见同机房巨佬的$map$被卡到了自闭，最后用了``unordered_map``才勉强卡过（话说``unordered_map``是不是需要c++11啊，哪位大佬科普一下）。然后才想起来$map$有巨大的常数，于是我们想进一步优化。

我们发现，这里的$map$实际上大材小用了，我们只需要简单的插入和查询，并不需要容器有序，于是我们可以自然的想到用~~unordered_map~~哈希表进行优化。虽然哈希表时间复杂度比较玄学，但再怎么样也不会比一只$log$再加大常数的``map``慢。而且哈希表复杂度几乎可以看做常数级别。

所以我们就可以愉快地水掉一道紫题啦！！

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 200005
#define P 10007
using namespace std;

ll n, k;
ll a[MAX], p[20], lg[MAX];
struct hash_map {
    int head[MAX], Next[MAX], cnt;
    ll val[MAX], tot[MAX];
    
    hash_map(){
        cnt = 0;
        memset(head, 0, sizeof(head));
        memset(Next, 0, sizeof(Next));
        memset(val, 0, sizeof(val));
        memset(tot, 0, sizeof(tot));
    }
    
    void insert(ll x) {
        ll k = x%P;
        for(int i = head[k]; i; i = Next[i]) {
            if(val[i] == x) {
                tot[i]++;
                return;
            }
        }
        cnt++;
        Next[cnt] = head[k];
        head[k] = cnt;
        val[cnt] = x;
        tot[cnt] = 1;
    }

    ll find(ll x) {
        ll k = x%P;
        for(int i = head[k]; i; i = Next[i]) {
            if(val[i] == x) {
                return tot[i];
            }
        }
        return 0;
    }
}mp[15];

int main() {
    cin >> n >> k;
    p[0] = 1;
    for(int i = 1; i <= 10; i++) {
        p[i] = p[i-1]*10%k;
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        ll tmp = a[i];
        while(tmp) {
            lg[i]++;
            tmp /= 10;
        }
    }
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= n; j++){
            mp[i].insert(a[j]%k*p[i]%k);
        }
    }
    
    ll t, ans = 0;
    for(int i = 1; i <= n; i++){
        t = ((k-a[i])%k+k)%k;
        ans += mp[lg[i]].find(t);
        if((a[i]%k*p[lg[i]]%k+a[i]%k)%k == 0){
            ans--;
        }
    }
    cout << ans << endl;

    return 0;
}
```



---

## 作者：Forsaken2020 (赞：1)

花式预处理然后合理的暴力，亲测代码跑的飞快，成功跑出洛谷最快，嗯....写的时候先被爆了int，然后再被爆了ll，最后用ull才过的，可以说是非常的智障了。

![被日哭了,jpg](https://cdn.luogu.com.cn/upload/pic/31767.png)

```cpp
//author Eterna
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<cmath>
#include<climits>
#include<deque>
#include<functional>
#include<complex>
#include<numeric>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define INF 0x7fffffff
#define Pi acos(-1.0)
#define maxn 200000
#define eps 1e-15
#define MOD 1000000007
#define ABS(x) ((x)>=0?(x):(-(x)))
#define pb(x) push_back(x)
#define lowbit(x) (x&-x)
#define mid (L+R)/2
#define Lson (index*2)
#define Rson (index*2+1)
#define root arr[0].child[1]
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline int read_int() {
	char c;
	int ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}
inline ll read_ll() {
	char c;
	ll ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}
inline bool Get_Line(string& s) {
	s.clear();
	char ch;
	while ((ch = getchar()) && ch != '\n'&&ch != '\r') {
		if (ch == EOF)return false;
		s.push_back(ch);
	}
	return true;
}
inline int Count_Len(int x) {
	int ret = 0;
	while (x) {
		ret++;
		x /= 10;
	}
	return ret;
}
const int Up = 1e9;
int arr[maxn + 5], len[maxn + 5], n, length, max_len;
ll ans;
ull now, p;
map<int, int> mp[11];
int main(void)
{
	//ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	n = read_int(), p = read_ll();
	for (int i = 1; i <= n; i++) {
		arr[i] = read_int();
		len[i] = Count_Len(arr[i]);
		max_len = max(max_len, len[i]);
		mp[len[i]][arr[i] % p]++;
	}
	for (int i = 1; i <= n; i++) {
		now = arr[i]; length = len[i];
		while (length - len[i] < max_len) {
			now *= 10; length++;
			ll a = now%p;
			ll b = p - a; b %= p;
			if (mp[length - len[i]].find(b) != mp[length - len[i]].end()) {
				ans += mp[length - len[i]][b];
				if (len[i] == length - len[i] && arr[i] % p == b)ans--;
			}
		}
	}
	cout << ans << endl;
	//system("pause");
	return 0;
}
```

---

