# Hash?

## 题目背景

**zhoutb2333**学习了哈希算法，他于是去统计给定一些字符串，其中有多少个本质不同的字符串。


但是**zhoutb2333**突发奇想，如果哈希采用的$base$每次随机，那么结果会变成什么样呢？

**辣鸡出题人又出锅了！subtask3的数据有问题，现在统一将模数改为65537**

题目来源：[zhoutb2333](https://www.luogu.org/space/show?uid=31564)

## 题目描述

他通过某种办法，获得了一个函数:$int \ Rand(int  \ x)$，它会等概率地返回一个$[0,x)$中的整数。

他写下了这样的代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int x=10,maxn=35,maxlen=16010;
ll HASH[maxn];
const ll p=65537;
char str[maxlen];
ll Hash(){
    int base=Rand(x);
    ll ret=0;
    for(int i=1;str[i];i++)
        ret=(ret*base+str[i]-'a'+1)%p;
    return ret;
}
int main(){
    int ans=0,n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",str+1),HASH[i]=Hash();
    sort(HASH+1,HASH+n+1);
    HASH[0]=-1;
    for(int i=1;i<=n;i++)
        ans+=(HASH[i]!=HASH[i-1]);
    printf("%d\n",ans);
    return 0;
}
```
**zhoutb2333**想问你，给定一些字符串和参数$x$，答案$ans$的期望是多少呢？

$65537= 2^{16}+1$**是质数**

**参数$x$在这个程序中是确定的$10$，但是每次输入会给定。**

## 说明/提示

本题由$3$个$subtask$组成，设$M$为这$N$个字符串中，每个字符串长度的最大值。

对于$subtask \ 1$：$1 \le N \le 8 , M \le 10,x \le 4$，分值为$20$，时间限制为$1s$。

对于$subtask \ 2$：$1 \le N \le 30 , M \le 500,x \le 500$，分值为$50$，时间限制为$1s$。

对于$subtask \ 3$：$1 \le N \le 5 , M \le 16000,x \le 16000$，分值为$30$，时间限制为$4.5s$。

**样例#1解释：**

参数$x=2$，那么可能的哈希$base$为$0,1$。

如果哈希第一个`aa`采用的$base$和第二个`aa`的$base$相同，那么答案为$1$。

如果两个$base$不相同，那么答案为$2$。

分析发现这两种情况发生的概率相同，都是$\frac{1}{2}$，那么答案$ans$的期望为$1 * \frac{1}{2} + 2 * \frac{1}{2}=\frac{3}{2}$。使得$2x \equiv 3 \ (mod \ 65537)$的最小正整数$x$为$32770$。

**样例#2解释：**

求得答案为$\frac{53}{9}$。使得$9x \equiv 53 \ (mod \ 65537)$的最小正整数$x$为$58261$。

**注意：本题允许手动开$O2$优化以避免被卡常数，方法如下：**
``` cpp
%:pragma GCC optimize(2)
/*程序*/
```

## 样例 #1

### 输入

```
2 2
aa
aa```

### 输出

```
32770
```

## 样例 #2

### 输入

```
3 6
i
dont
know
what
to
say```

### 输出

```
58261
```

# 题解

## 作者：zhoutb2333 (赞：9)

**算法1：**

考虑将所有字符串的所有哈希值计算出来。那么枚举每一种情况并统计即可。复杂度$O(NMx+x^N)$。

可以通过$subtask \ 1$，预期得分$20$分。

**算法2：**

仍然考虑将所有哈希值计算出来，但是统计答案时改为计算每个结果对$ans$的贡献。

等于$\sum ^{p-1}_{i=0}P(i$出现$)*1+P(i$不出现$)*0$

即$\sum ^{p-1}_{i=0}( 1- \prod ^{N}_{j=1} \frac{x-cnt[S_j][i]}{x})$，其中$S_j$表示第$j$个字符串，$x$表示$rand()$参数，$cnt[S_j][i]$表示$S_j$的哈希值中$i$出现的次数。复杂度$O(NMx) $。

可以通过$subtask \ 2$，预期得分$70$分。

**算法3：**

单独考虑一个字符串，下标从$1$开始。

设当前的$base=b$，$f[n]$表示$S$哈希到第$n$位的值。则有转移$f[n]=b*f[n-1]+S[n]$。那么我们会发现$f[\left| S \right|]$是一个关于$b$的多项式函数，设为$G(b)$。容易知道$G(b)=\sum ^{\left| S \right|}_{i=1} S[i]*b^{n-i}$

那么我们求的是$G(0),G(1) \dots G(x-1)$。可以用多项式多点求值做，复杂度$O(NSlog^2S),S=2^{\lceil log \ max(M,x) \rceil}$。

可以通过$subtask \ 3$，预期得分$100$分。

嗯..这是$p=998244353$的做法，下调成了$40961$是我出锅了。

如果是现在的$p=65537$还有一种很快的算法，就是将长度$M$强行设为$65536$后用一遍$DFT$带入求值。

因为$\frac{(p-1)}{M}=1$，所以做完$DFT$后数组里第$i$位是$G(g^i)$，然后$g^i$遍历$1$~$p-1$，所以最后再加上$G(0)$即可...比多点求值快不知道哪去了

---

## 作者：WorldMachine (赞：1)

好题。

设 $h_i(x)$ 表示第 $i$ 个串取 $\text{base}=x$ 时的哈希值。则：
$$
h_i(x)=\sum_{j=1}^{\text{len}}s_{i,j}x^{\text{len}-j}
$$
这是一个关于 $x$ 的多项式。求出所有 $h$ 的点值有两种方式，最暴力的是直接多点求值硬上。注意到 $p=2^{16}+1$，将长度直接设为 $2^{16}$ 跑 NTT，做完后数组中第 $j$ 位为 $[x^{g^j\bmod p}]h_{i}(x)$，刚好取遍 $2\sim p-1$，$[x^0]h_i$ 和 $[x^1]h_i$ 可以暴力求。

求出所有 $h$ 之后，问题转化为：有一个 $n\times x$ 的矩阵，你可以从每行当中选一个，问所有选法的颜色数之和。考虑对每个颜色单独计算贡献，正难则反计算有多少种选法中不包含该颜色。设第 $i$ 行的颜色 $j$ 个数为 $\text{cnt}_{i,j}$，则答案为：
$$
\sum\limits_{i=0}^{p-1}\left(x^n-\prod\limits_{j=1}^n(x-\text{cnt}_{j,i})\right)
$$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 35, P = 1 << 16 | 5, nn = 1 << 16, p = 65537, g = 3;
int num, X, tax[P], gen[P], h[N][P], tmp[P], ans, cnt[N][P];
char str[P];
int qpow(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = (ll)c * a % p;
		a = (ll)a * a % p, b >>= 1;
	}
	return c;
}
void init() {
	for (int i = 1; i < nn; i++) tax[i] = tax[i >> 1] >> 1 | (i & 1) << 15;
	gen[0] = 1;
	for (int i = 1; i <= nn; i++) gen[i] = (ll)gen[i - 1] * g % p;
}
void NTT(int a[]) {
	int w, x, y;
	for (int i = 1; i < nn; i++) if (i < tax[i]) swap(a[i], a[tax[i]]);
	for (int k = 1, l = nn >> 1; k < nn; k <<= 1, l >>= 1) {
		for (int i = 0; i < nn; i += k << 1) {
			for (int j = 0; j < k; j++) {
				w = gen[l * j];
				x = a[i + j], y = (ll)a[i + j + k] * w % p;
				a[i + j] = (x + y) % p, a[i + j + k] = (x - y + p) % p;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> X >> num;
	init();
	for (int i = 1, len; i <= num; i++) {
		cin >> str, len = strlen(str);
		for (int j = 0; j < len; j++) h[i][j] = str[len - j - 1] - 'a' + 1;
		NTT(h[i]);
		memset(tmp, 0, sizeof(tmp));
		for (int j = 1; j < nn; j++) tmp[gen[j]] = h[i][j];
		for (int j = 1; j < nn; j++) h[i][j] = tmp[j];
		h[i][0] = str[len - 1] - 'a' + 1;
		h[i][1] = 0;
		for (int j = 0; j < len; j++) h[i][1] = (h[i][1] + str[j] - 'a' + 1) % p;
		for (int j = 0; j < X; j++) cnt[i][h[i][j]]++;
//		for (int j = 0; j < X; j++) cerr << h[i][j] << ' ';
//		cerr << '\n';
	}
	for (int i = 0, mul; i < p; i++) {
		mul = 1;
		for (int j = 1; j <= num; j++) mul = (ll)mul * (X - cnt[j][i]) % p;
//		cerr << i << ' ' << mul << '\n';
		ans = (ans + qpow(X, num) - mul + p) % p;
	}
	cout << (ll)ans * qpow(qpow(X, num), p - 2) % p;
}
```

好饿。

---

## 作者：ZhongYuLin (赞：0)

现在是 $2024$ 年，评测机速度大幅提升。

假设我们可以以某种手段计算出每个字符串的所有哈希值，并将它们存入桶中。记 $f_{i,j}$ 表示第 $i$ 个字符串有 $f_{i,j}$ 个为 $j$ 的哈希值。注意到期望的线性性，答案即为：

$$\sum_{j=0}^{P-1}\frac{x^n-\prod_{i=1}^n(x-f_{i,j})}{x^n}$$

暴力统计可以获得 $70$ 分，使用多项式多点求值可以通过。但是注意到数据范围较小、模数较小的特点，我们可以循环展开并多次乘法后才进行一次取模，可以通过这道题。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=7e4+3,P=65537;
template<class T1,class T2>void add(T1 &x,T2 y){if((x+=y)>=P)x-=P;}
template<class T1,class T2>void dlt(T1 &x,T2 y){if((x-=y)<0)x+=P;}
int K,n;
int h[31][N];
string s;
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>K>>n;
    for(int i=1;i<=n;++i){
        cin>>s;int len=s.size();
        for(int k=0;k<K;++k){
            ll w=0;
            int j=0;
            for(;j+14<len;j+=15){
                w=(w*k+s[j]-96);
                w=(w*k+s[j+1]-96);
                w=(w*k+s[j+2]-96)%P;
                w=(w*k+s[j+3]-96);
                w=(w*k+s[j+4]-96);
                w=(w*k+s[j+5]-96)%P;
                w=(w*k+s[j+6]-96);
                w=(w*k+s[j+7]-96);
                w=(w*k+s[j+8]-96)%P;
                w=(w*k+s[j+9]-96);
                w=(w*k+s[j+10]-96);
                w=(w*k+s[j+11]-96)%P;
                w=(w*k+s[j+12]-96);
                w=(w*k+s[j+13]-96);
                w=(w*k+s[j+14]-96)%P;
            }
            for(;j<len;++j)w=(w*k+s[j]-96)%P;
            ++h[i][w];
        }
    }
    auto fp=[&](ll a,ll b=P-2){ll ans=1;for(;b;b>>=1,a=a*a%P)if(b&1)ans=ans*a%P;return ans;};
    int ans=0,inv=fp(fp(K,n));
    for(int i=0;i<P;++i){
        int res=1;
        for(int j=1;j<=n;++j)
            res=1ll*res*(K-h[j][i])%P;
        ans=((ans+1-1ll*res*inv)%P+P)%P;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

