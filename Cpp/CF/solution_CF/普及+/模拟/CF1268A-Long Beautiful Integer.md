# Long Beautiful Integer

## 题目描述

给定一个由 $a_1, a_2, \ldots, a_n$ 从左到右构成的整数 $x$ 和一个正整数 $k$。

若由 $b_1, b_2, \ldots, b_m$ 从左到右构成的整数满足 $\forall i \in [1,m-k], b_i=b_{i+k}$，则称其为美丽数。

请求出最小的由 $b_1, b_2, \ldots, b_m$ 从左到右构成的美丽数 $y$，满足 $y \geq x$。

## 说明/提示

$2 \leq n \leq 2 \times 10^5$，$1 \leq k \leq n$。

## 样例 #1

### 输入

```
3 2
353
```

### 输出

```
3
353
```

## 样例 #2

### 输入

```
4 2
1234
```

### 输出

```
4
1313
```

# 题解

## 作者：ZLCT (赞：1)

# CF1268A Long Beautiful Integer
## 题目翻译
给定长度为 $n$ 的数 $m$，和一个正整数 $k$。求循环节为 $k$ 的最小整数 $l$ 使 $l\ge m$。
### 明显的构造思路
我们既然要使构造的数尽可能和 $m$ 接近，那么我们最佳答案肯定是 $m$。\
于是就启示我们尽可能地让 $l$ 从高位到低位与 $m$ 相等。\
简单理解一下，如果有一位我们可以构造 $b_i$ 而我们构造 $b_i+1$，那么答案肯定不是最小的（起码有这一位为 $b_i$ 比它小）。\
于是我们就可以提出 $m$ 的前 $k$ 位，并判断它构成的数是否满足条件，如果不满足就把第 $k$ 位 $+1$ 就是答案。\
证明 $1$：如果把第 $k$ 位 $+1$，那么答案起码比原数多 $10^{n-k}$，即使原数后面全是 $9$，最多也只有 $10^{n-k}-1$，于是肯定满足构造的数大于原数。\
证明 $2$：因为我们构造的数肯定由长度为 $k/k+1$，所以把最后一位 $+1$ 一定是最小的大于 $m$ 的数字。\
于是这种构造方法一定是答案。\
tips：注意进位。
### code by me
```cpp
#include<bits/stdc++.h>
using namespace std;
string y;
int a[212345];
int n,k;
bool flag;
void add(){
    y[y.size()-1]++;
    for(int i=(int)y.size()-1;i>=0;--i){
        if(y[i]>'9'){
            if(i!=0){
                y[i]='0';
                y[i-1]++;
            }else{
                flag=1;
                int len=(int)y.size();
                y="1";
                for(int j=1;j<=len;++j)y+='0';
                return;
            }
        }else{
            return;
        }
    }
}
void print(){
    const int leng=(int)y.size();
    cout<<n+flag<<'\n';
    for(int i=0;i<n+flag;++i){
        cout<<y[i%leng];
    }
}
bool check(){
    for(int i=0;i<n;++i){
        if(a[i]>(y[i%k]-'0'))return false;
        else if(a[i]<(y[i%k]-'0'))return true;
    }
    return true;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    char ch;
    for(int i=0;i<n;++i){
        cin>>ch;
        a[i]=ch-'0';
        if(i<k)y+=ch;
    }
    if(check()){
        print();
    }else{
        add();
        print();
    }
}
```
### a beautiful code by `StarSilk`
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,k,i,flag;
	cin>>n>>k>>s;
	flag=0;
	for(i=0;i<n;i++)
	{
		if(s[i]!=s[i%k])
		{
			if(s[i]>s[i%k])flag=1;
			break;
		}
	}
	if(flag)
	{
		for(i=k-1;s[i]=='9';i--)s[i]='0';
		s[i]++;
	}
	cout<<n<<'\n';
	for(i=0;i<n;i++)cout<<s[i%k];
	cout<<'\n';
	return 0;
}
```

---

## 作者：囧仙 (赞：1)

## 题目大意

已知有$n$位的数$A$，和常数$k$。现在需要求出最小的数$B$，使得对于任何可能的$i$，有$B_i=B_{i+k}$，且$A\le B$。

## 题解

很显然，$B$的这个限制条件就是把一个长度为$k$的数字重复了若干遍。

$$B=\overline{\tt{abcdabcdabc\cdots}} _ {(10)}$$

显然，$B$的位数和$A$相同。因为如果$B$的位数小于$A$，那么$B$不可能大于$A$；我们可以构造符合条件的数字$\overline{\tt{99999\cdots}} _ {(10)}$，来保证长度为$n$位的数字符合条件。

我们要让$B$最小，最贪心的做法就是直接取$A$的前$k$位。

举个例子：

$$A=\overline{1919810}_{(10)},k=3\Rightarrow B=\overline{1911911}_{(10)}$$

但此时，我们发现$B<A$。不过我们可以使$B_k$加上$1$（同时向前进位），然后更新答案。这样可以保证在前$k$位，$B>A$，此时$B$取得最小值。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
const int MAXN=2e5+3;
int n,m; bool flg; char A[MAXN],B[MAXN];
int main(){
    scanf("%d%d%s",&n,&m,A);
    up(0,n/m,i) memcpy(B+i*m,A,min(m,n-i*m));
    up(0,n-1,i) if(A[i]!=B[i]){flg=A[i]>B[i];break;}
    if(flg){
        ++A[m-1]; dn(m-1,1,i) if(A[i]=='9'+1) A[i]='0',++A[i-1];
        up(0,n/m,i) memcpy(B+i*m,A,min(m,n-i*m));
    }
    printf("%d\n%s\n",n,B);
    return 0;
}
```

---

## 作者：liuyz11 (赞：1)

# 题解 CF1268A 【Long Beautiful Integer】

该场比赛所有题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12177652.html)

题目大意：给你一个数字x，以及正整数k，求一个大于等于x的最小数字y并满足 yi = yi + k (1 <= i <= n - k) 。n为x的长度，n小于等于500.

这一题hack数据还真多，197组……

首先可以发现，数字y的长度一定是等于x的长度的，因为全为9的数字一定满足条件。

对于 yi = yi + k 这个式子，我们发现，对于所有位置i对k取模结果相同的，该位上的数字也一定是相同的。

那我们只要枚举最后前k位数字即可，为了让数字尽量小，我们让y的每一位和x一样大，然后判断此时y和x的大小。

若y大于等于x，那么y就是答案。若y小于x，只需要在第k位加上1即可。

注意：需要进位！！！

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 200005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int num[MAXN], ans[MAXN];
char st[MAXN];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s", st);
	int maxx = 0;
	rep(i, 1, n){
		num[i] = st[i - 1] - '0';
		maxx = max(maxx, num[i]);
	}
	int minx = INF, miny = INF;
	rep(i, 1, m){
		ans[i] = num[i];
		for(int j = i ; j <= n; j += m){
			if(ans[i] < num[j]) minx = min(minx, j);
			if(ans[i] > num[j]) miny = min(miny, j);
		}
	}
	if(miny > minx){
		ans[m] = num[m] + 1;
		for(int x = m; x > 0 && ans[x] == 10; x--){
			ans[x] = 0;
			ans[x - 1]++;
		}
	}
	printf("%d\n", n);
	rep(i, 1, n) printf("%d", ans[(i - 1) % m + 1]);
	puts("");
    return 0;
}

```

---

## 作者：宋睿天 (赞：1)

#### 这道题是要找循环k个数后最小的数，也就是说要把前k位循环m次后生成一个数，如果这个数小于原数，就把前k位的数+1，再生成就一定大于原数，输出即可
###
#### 至于处理的时候我把原数前k个数存在1个字符串中,再利用string相加并比较即可



```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
string b,a,c;
int n,k,l;
bool ok;
void plues(){    //plues是把一个数+1
	int t=k-1;
	while(1){
		if(b[t]<='8'&&b[t]>='0') {
			b[t]+=1;
			return;
		}
		else {
			b[t]='0';
			t--;
		}
	}
}
int main(){
    scanf("%d%d",&n,&k);
    printf("%d\n",n);
    cin>>a;
    l=n%k; 
    for(int i=0;i<k;i++) b+=a[i];
	for(int i=1;i<=n/k;i++) c+=b;
	for(int i=0;i<l;i++) c+=b[i];
	if(c>=a) cout<<c;
	else {
		plues();
		for(int i=1;i<=n/k;i++) cout<<b;
		for(int i=0;i<l;i++) cout<<b[i];
		return 0;
	}
}
```


---

## 作者：寒鸽儿 (赞：1)

保留前 $k$ 位按照规则生成一个数。  
判断它是否原数。  
然后如果$\geqslant$则输出。  
然后考虑小于的情况。  
只要将前$k$位 $+1$ 然后按规则生成。注意进位。  
```cpp
#include <cstdio>

using namespace std;

int getdi() {
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    return ch - '0';
}

const int N = 234567;
int v[N], yl[N];

void build(int f, int k, int t) {
    for(int i = f; i <= t; ++i) {
        v[i] = v[i - k];
    }
}

bool greater(int n) {
    for(int i = 1; i <= n; ++i) {
        if(v[i] > yl[i]) return true;
        if(v[i] < yl[i]) return false;
    }
    return true;
}

void output(int n) {
    printf("%d\n", n);
    for(int i = 1; i <= n; ++i) putchar('0' + v[i]);
    printf("\n");
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; ++i) {
        yl[i] = getdi();
    }
    for(int i = 1; i <= k; ++i) {
        v[i] = yl[i];
    }
    build(k + 1, k, n);
    if(greater(n)) {
        output(n);
    } else {
        ++v[k];
        for(int i = k; i; --i) {
            if(v[i] > 9) {
                v[i] %= 10; ++v[i-1];
            }else {
                break;
            }
        }
        if(v[0] == 1) {
            ++k; n += 2; v[1] = 1;
            for(int i = 2; i <= k; ++i) v[i] = 0;
        }
        build(k + 1, k, n);
        output(n);
    }
    return 0;
}
```

---

