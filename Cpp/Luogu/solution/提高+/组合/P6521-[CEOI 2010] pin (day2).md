# [CEOI 2010] pin (day2)

## 题目描述

给定 $n$ 个长度为 $4$ 的字符串，你需要找出有多少对字符串满足**恰好** $D$ 个对应位置的字符不同。



## 说明/提示

#### 【样例解释】

#### 样例 1 解释

任意两个字符串都有多于一个位置不相同。

#### 样例 2 解释

共有三对字符串：`0000,a010` `a010,a0e2` `0000,0202`。

#### 【数据规模与约定】

- 对于 $15\%$ 的数据，保证 $n\le 2000$；
- 对于 $30\%$ 的数据，保证 $D=1$；
- 对于 $60\%$ 的数据，保证 $D\le 2$；
- 对于 $75\%$ 的数据，保证字符串中只包含小写字母 $a\sim f$ 以及数字。因此可以视为 $16$ 进制数；
- 对于 $100\%$ 的数据，保证 $2\le n\le 5\times 10^4$，$1\le D\le 4$，所有输入的字符串没有重复，串中的字符仅可能为 $a\sim z$ 或者数字字符。


#### 【说明】

**题目译自 [CEOI 2010](http://ceoi2010.ics.upjs.sk/Contest/Tasks) day 2 *[T2 pin](https://people.ksp.sk/~misof/ceoi2010/pin-eng.pdf)***。

翻译版权为题目提供者@[ShineEternal](https://www.luogu.com.cn/user/45475) 所有，未经许可禁止转载。



## 样例 #1

### 输入

```
4 1
0000
a010
0202
a0e2```

### 输出

```
0```

## 样例 #2

### 输入

```
4 2
0000
a010
0202
a0e2```

### 输出

```
3```

# 题解

## 作者：Cry_For_theMoon (赞：11)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/P6521)

&emsp;&emsp;今天机房T3出了这道题，纪念第一次机房模拟赛AK

&emsp;&emsp;这道题一下想到容斥的都是数学神仙吧。

&emsp;&emsp;一步步分析。当 15% 的暴力打完以后，我们发现其实 $D$ 只有四种，所以自然想到分类讨论 $D$。既然第一个给的是 $D=1$，自然是有他的道理的。

&emsp;&emsp;"有一个不同"的关系和"有三个相同"是一一对应的。考虑计算三个字符相同的密码的数，枚举这三个字符的位置，只有 $C_4^3=4$ 种。此时我们可以用一个三维数组去记录这三个字符出现的所有次数，最后枚举所有的三个字符的情况对应的次数 $k$，$C_{k}^2$ 就是贡献。但是我们可以用哈希的思想把给定的三个字符转成一个三十六进制数（机房考试没有十六进制的部分分，我也感觉没必要）：

```cpp
inline int hash3(char a,char b,char c){
	return hash1(a)*36*36+hash1(b)*36+hash1(c);
}
```

&emsp;&emsp;相应的我们写出了这样的代码：

```cpp
//3位相同
for(int i=1;i<=4;i++){
	for(int j=i+1;j<=4;j++){
		for(int k=j+1;k<=4;k++){
			clearmemory();
			for(int l=1;l<=n;l++){
				size[hash3(pins[l][i],pins[l][j],pins[l][k])]++;
			}
			for(int l=0;l<=LIM;l++){
				cnt[3] = cnt[3] + size[l] * (size[l]-1)/2; 
			}
		}
	}
} 
```

&emsp;&emsp;这个 clearmemory() 是memset。$i,j,k$ 代表计算的是哪三位相同的字符串关系数量。$l$ 则枚举的是对应的字符串，把每个字符串对应的这三位转成一个唯一的 36 进制数（上界用计算器可算出小于5e4），然后统计每个数出现的次数，从中选出两个数的对数就是这三位相同的字符串关系数量。

&emsp;&emsp;两位和一位的哈希函数同理，完整代码会在文末给出。

&emsp;&emsp;这个时候不是输出 $cnt(4-d)$ 就完事的。题目要求的是恰好 $4-D$ 位相同的关系。考虑两个密码0001，0002，如果 $D=2$，答案是0，然而它们两确实是有两位相同的，而且还不知一个，第一位&第二位，第一位&第三位，第二位&第三位这三种情况下这个三位相同的都会被加进两位相同的去算）。考试的时候我卡在这里卡了很久

&emsp;&emsp;题目中的一句话点醒了我:“任意两个字符串都有多于一个位置不相同”
，再想一下第一个是 $D=1$，当我们计算出 $cnt(3)$ 的时候，其实是没有多算的，因为没有什么字符串是四位全部相同的，最多也就三位相同，所以当 $D=1$ 的时候输出 $cnt(3)$ 即可。

&emsp;&emsp;顺着下去推 $D=2$（记作 $ans(2)$），显然每个 $ans(3)$（根据上文我们已经知道就是 $cnt(3)$) 会在两个字符相同计数时被算**三**次，这实际上是 $C_3^2 = 3$的缘故.所以 $ans(2) = cnt(2)-ans(3)*3$，这是容斥（补集）的思想

&emsp;&emsp;接下来是 $D=3$，每一个 $ans(2)$ 会算两次，$ans(3)$ 是3次，因为$C_2^1 = 2,C_3^1=3$ 的缘故。所以 $ans(1) = cnt(1)-ans(2)*2-ans(3)*3$

&emsp;&emsp;最后 $D=4$ 即没有相同字符关系的密码的数量，显然一共有 $\frac{n(n-1)}{2}$ 对关系，减去 $(ans(1)+ans(2)+ans(3))$ 即可。即 $ans(0) = C_n^2-ans(1)-ans(2)-ans(3)$

&emsp;&emsp;最后输出 $ans(4-D)$ 就是答案啦QwQ

```cpp
//CEOI,2010
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=6e4+10,LIM=5e4;
int n,d;
char pins[MAXN][10];
long long size[MAXN],cnt[10],ans[10];
inline void clearmemory(){
	memset(size,0,sizeof size);
}
inline int hash1(char a){
	if(a>='0'&&a<='9'){
		return a-'0';
	}else{
		return a-'a'+10;
	}
}
inline int hash2(char a,char b){
	return hash1(a)*36+hash1(b);
}
inline int hash3(char a,char b,char c){
	return hash1(a)*36*36+hash1(b)*36+hash1(c);
}
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++){
		scanf("%s",pins[i]+1);
	}
	//1位相同 
	for(int i=1;i<=4;i++){
		clearmemory();
		for(int j=1;j<=n;j++){
			size[hash1(pins[j][i])]++;
		}
		for(int j=0;j<=LIM;j++){
			cnt[1] = cnt[1] + size[j] * (size[j]-1)/2;
		}
	}
	//2位相同
	for(int i=1;i<=4;i++){
		for(int j=i+1;j<=4;j++){
			clearmemory();
			for(int k=1;k<=n;k++){
				size[hash2(pins[k][i],pins[k][j])]++;
			}
			for(int k=0;k<=LIM;k++){
				cnt[2] = cnt[2] + size[k] * (size[k]-1)/2;
			}
		}
	} 
	//3位相同
	for(int i=1;i<=4;i++){
		for(int j=i+1;j<=4;j++){
			for(int k=j+1;k<=4;k++){
				clearmemory();
				for(int l=1;l<=n;l++){
					size[hash3(pins[l][i],pins[l][j],pins[l][k])]++;
				}
				for(int l=0;l<=LIM;l++){
					cnt[3] = cnt[3] + size[l] * (size[l]-1)/2; 
				}
			}
		}
	} 
	ans[3] = cnt[3];
	ans[2] = cnt[2]-ans[3]*3;
	ans[1] = cnt[1]-ans[2]*2-ans[3]*3;
	ans[0] = (long long)n*(n-1)/2 - ans[1]-ans[2]-ans[3];
	printf("%lld",ans[4-d]); 
	return 0;
}

```


---

## 作者：一扶苏一 (赞：9)

## 【容斥】【P6521】 [CEOI2010 day2] pin

### Analysis

因为做这个题的时候，憨憨 @[**ShineEternal**](https://www.luogu.com.cn/user/45475) 翻译错了题面，把恰好**不同**译成了恰好**相同**，所以我按照相同做的，当然没有什么区别，把 $d$ 改成 $4 - d$ 即可。因此下面考虑恰好有 $d$ 个位置相同应该怎么做。

首先我们可以用 map 轻松维护出与当前字符串至少某几个位置相同的字符串个数（只需要把剩下的位置都统一改成某个无关字符即可）。

考虑容斥计算答案。设与当前字符串至少 $i$ 个位置相同的统计值为 $f_i$，恰好有 $i$ 个位置相同的实际值为 $g_i$。

因为没有重复的字符串，所以 $g_3 = f_3$。

考虑计算 $g_2$。任何一个有三个位置相同的字符串都被统计了 $C_{3}^2$ 次，因此 $g_2 = f_2 - G_{3}^2 g_3$。

类似的，可以得到 $g_i = f_i - \sum\limits_{j = i + 1}^3 C_j^i g_j$。递推出 $g_d$ 即可。

### Code

```cpp
#include <map>
#include <vector>
#include <string>
#include <iostream>

int n, d, dd;
long long C[5][5], g[5];
long long ans;
std::string s, t;
std::vector<int> sta[5];
std::map<std::string, int> mp;

void calc(const int x) {
  for (int i = 3; i >= dd; --i) {
    long long f = 0;
    for (auto u : sta[i]) {
      t = s;
      for (int o = 0; o < 4; ++o) if ((u & (1 << o)) == 0) {
        t[o] = '$';
      }
      f += mp[t];
    }
    for (int j = i + 1; j <= 3; ++j) {
      f -= C[j][i] * g[j];
    }
    g[i] = f;
  }
  ans += g[d];
}

void add() {
  for (int i = 0; i < 4; ++i) {
    for (auto u : sta[i]) {
      t = s;
      for (int o = 0; o < 4; ++o) if ((u & (1 << o)) == 0) {
        t[o] = '$';
      }
      ++mp[t];
    }
  }
}

inline int countbit(const int x) { return __builtin_popcount(x); }

int main() {
  std::cin >> n >> d;
  C[0][0] = 1;
  for (int i = 1; i <= 3; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
  dd = d = 4 - d;
  for (int i = 0, upc = 1 << 4; i < upc; ++i) {
    sta[countbit(i)].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> s;
    calc(i);
    add();
  }
  std::cout << ans << std::endl;
}
```



---

## 作者：yuzhechuan (赞：5)

来一个麻烦点的方法（指二项式反演）

---

### 题解：

一看到“恰好”就想到了二项式反演（大雾）

于是先套路地反向考虑问题，即恰好$D$个位置不同就是恰好$4-D$个位置相同

于是暴力钦定相同的位置，用通配符（例如问号）占据未被钦定的位置，然后用map数一数就好啦

得到钦定的答案后，再套路地用一次二项式反演就好了

（二项式反演不会可以百度，这题差不多是个裸题）

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int C[5][5]={
{1,0,0,0,0},
{1,1,0,0,0},
{1,2,1,0,0},
{1,3,3,1,0},
{1,4,6,4,1}
};
const int N=5e4+5;
string s[N];
int n,m,ans,f[5];
map<string,int> mp;

signed main(){
	read(n);read(m);m=4-m;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int S=0;S<16;S++){
		int cnt=0,cur=0;
		mp.clear();
		for(int i=0;i<4;i++) cnt+=S>>i&1;
		for(int i=1;i<=n;i++){
			string t=s[i];
			for(int j=0;j<4;j++) if(~S>>j&1) t[j]='?';
			f[cnt]+=mp[t];
			cur+=mp[t]++;
		}
	}
	for(int i=m,op=1;i<=4;i++,op=-op) ans+=op*C[i][m]*f[i]; //反演
	write(ans);
}
```

---

## 作者：Istruggle (赞：4)

看到题目中被加粗的“恰好”，便想到可以用二项式反演将“至少”转化为“恰好”。

我们先将 $D$ 改为 $4-D$，这样题目就转化为了求有多少对字符串的对应位置相同，接着令 $g_k$ 表示至少 $k$ 个位置相同的对数，令 $f_k$ 表示恰好有 $k$ 个位置对应的字符相同的对数。关于计算 $g_k$， 我们可以二进制枚举钦定哪些位上的字符相同，接着枚举所有字符串，求出对应位置上的哈希值，并将对应哈希值上的答案累加。

最后套上二项式反演的公式:

$$f_k = \sum_{i=k}^{n}\binom{i}{k}(-1)^{i-k}g_i$$

最终答案即为 $f_D$。

#### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5e4+5;
#define int long long
const int mod=1e9+7;
int n,k,g[N],ans,fac[11];
string s[N];
int c(int x,int y){return fac[x]/fac[y]/fac[x-y];}
signed main(){
	scanf("%lld%lld",&n,&k); fac[0]=1; k=4-k;
	for(int i = 1;i<=7;i++) fac[i]=fac[i-1]*i;
	for(int i = 1;i<=n;i++) cin>>s[i];
	for(int S = 0;S<16;S++){
		map<unsigned long long,int> mp;
		for(int i = 1;i<=n;i++){
			unsigned long long hash=0;
			for(int j = 0;j<4;j++){
				if(S&(1<<j))
		    	hash=hash+s[i][j];
		    	hash=hash*13331;
			}
			g[__builtin_popcount(S)]+=mp[hash];
			mp[hash]++;
		}
	}
	for(int i = k;i<=4;i++){
		int x;
		if((i-k)%2==1) x=-1;
		else x=1;
		ans+=c(i,k)*g[i]*x;
	}
	printf("%lld",ans);
}
```

---

## 作者：PCCP (赞：2)

## 前言

~~今天学校模你赛出了这题当 T2，一眼容斥但是没能想到好的首先方法，又不想写超长代码，于是摆烂了（~~

## 思路

这题一上手很容易能想到容斥，因为他的答案有包含关系，加上询问给定的 $ D $ 是很小的。因为题目保证没有相同的字符串，所以反向去算各位相同的答案会快很多，至于容斥怎么算，一张韦恩图就很明了了。

其中四个集合分别表示第几位相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/9nahoek7.png)

## 关于计算

赛时我大脑降级只想到了把各种情况都单独算一遍，这样十分甚至九分的复杂，所以我直接放弃了。后面看了一别人的代码才想到可以直接循环。由于输入的字符串两两不同，所以上图最中间的深红区域其实是没有的。那么三位相同的答案就不需要另行计算了。

为了便于统计答案，可以用三十六进制来哈希，可以计算得出这样的空间不会炸。每一次哈希得到的值是有上限的，计算出上限可以让代码快很多。

时间复杂度：$ O(4^3n) $。

以下是代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
using namespace std;
const int N=5e4+10;
int n,d;
long long cnt[N],res[N],ans[N];
struct node{
	int c[5];
}a[N];
string s;
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=0;j<4;j++){
			if('0'<=s[j]&&s[j]<='9'){
				a[i].c[j+1]=s[j]-'0';
			}
			else{
				a[i].c[j+1]=s[j]-'a';
				a[i].c[j+1]+=10;
			}
		}
	}
	for(int i=1;i<=4;i++){
		for(int x=1;x<=n;x++){
			cnt[a[x].c[i]]++;
		}
		for(int x=0;x<=36;x++){
			res[1]+=cnt[x]*(cnt[x]-1)/2;
			cnt[x]=0;
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=i+1;j<=4;j++){
			for(int x=1;x<=n;x++){
				cnt[a[x].c[i]*36+a[x].c[j]]++;
			}
			for(int x=0;x<=1296;x++){
				res[2]+=cnt[x]*(cnt[x]-1)/2;
				cnt[x]=0;
			}
		}
	}
	for(int i=1;i<=2;i++){
		for(int j=i+1;j<=3;j++){
			for(int k=j+1;k<=4;k++){
				for(int x=1;x<=n;x++){
					cnt[a[x].c[i]*1296+a[x].c[j]*36+a[x].c[k]]++;
				}
				for(int x=0;x<=46656;x++){
					res[3]+=cnt[x]*(cnt[x]-1)/2;
					cnt[x]=0;
				}
			}
		}
	}
	ans[3]=res[3];
	ans[2]=res[2]-ans[3]*3;
	ans[1]=res[1]-ans[2]*2-ans[3]*3;
	ans[0]=(long long)n*(n-1)/2-ans[1]-ans[2]-ans[3];
	printf("%lld",ans[4-d]);
}
```

---

## 作者：huangrenheluogu (赞：2)

随机跳了一题，就跳到了这一道。

这是我在准备离开机房的时候看的，在回家路上想到的，所以写一篇题解纪念一下。

**正难则反**，我们难以求出不同的，求相同的好了，我们可以进行这样子的转化：$D$ 位不同等价于 $4-D$ 位相同。~~我才不会告诉你是我在车上忘记题目才想到的。~~

我们发现可以利用进制（$75\%$ 的数据也在提示这一点），把一个字符串转成一个进制的数。

因为我需要一个留空的位，所以我选择了 $37$ 进制。

把 $1/2/3/4$ 位相同的存到桶里，接着我们就可以统计出相同位**大于等于** $x$ 的数量，我记作 $mor_x$。

为什么是大于等于 $x$ 呢？因为我们发现，相同位大于等于 $x$ 的数也符合要求，而且不仅符合一次，就是说，**会重复计算**大于 $x$ 位相同的字符串。

我们想一想，两个**恰有** $a$ 位相同的字符串在大于等于 $b(b<a)$ 位相同的统计中出现了几次？

考虑组合数，把 $a$ 位中选出 $b$ 位当作相同的，并统计进去，有 $C_a^b$ 种可能。

在程序中，我把恰有 $x$ 位相同的字符串对数记作 $jus_x$，就可以根据上面的分析写出这样的代码：

```cpp
jus[4] = mor[4];
jus[3] = mor[3] - jus[4] * 4;
jus[2] = mor[2] - jus[3] * 3 - jus[4] * 6;
jus[1] = mor[1] - jus[2] * 2 - jus[3] * 3 - jus[4] * 4;
jus[0] = n * (n - 1) / 2 - jus[1] - jus[2] - jus[3];
```

说一句，我没有计算 $mor_0$，原因是所有的都有大于等于 $0$ 位相同，所以直接用 $\dfrac{n \times (n-1)}{2}$ 代替就可以了。

~~`jus[4]` 是因为我没看题，略去。~~

**同时注意到 $1 \le D \le 4$，所以不要忘记 $jus_0$。**

我还有一个神奇的错误就是我开始写成 $36$ 进制了，所以导致 $75pts$。希望大家不要犯。

接下来放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e4 + 5, maxn = 1874160;
int n, a[N][5], mor[5], jus[5], tong[maxn + 5], base[5], D, tem;
string s;
inline int Str(char c){
	if('0' <= c && c <= '9') return c - '0' + 1;
	return c - 'a' + 11; 
}
inline int calc(int x){
	int res = 0;
	while(x){
		if(x % 37 != 0) res++;
		x /= 37;
	}
	return res;
}
signed main(){
//	freopen("1.in", "r", stdin);
	base[1] = 1;
	for(int i = 2; i <= 4; i++) base[i] = base[i - 1] * 37;
	scanf("%lld%lld", &n, &D);
	for(int i = 1; i <= n; i++){
		cin>>s;
		a[i][1] = Str(s[0]), a[i][2] = Str(s[1]), a[i][3] = Str(s[2]), a[i][4] = Str(s[3]);
	}
	for(int i = 1; i <= n; i++){
		for(int _1 = 0; _1 <= 1; _1++){
			for(int _2 = 0; _2 <= 1; _2++){
				for(int _3 = 0; _3 <= 1; _3++){
					for(int _4 = 0; _4 <= 1; _4++){
						tem = a[i][1] * base[1] * _1 + a[i][2] * _2 * base[2] + a[i][3] * _3 * base[3] + a[i][4] * _4 * base[4];
						tong[tem]++; 
					}
				}
			}
		}
	}
	for(int i = 1; i <= maxn; i++) mor[calc(i)] += tong[i] * (tong[i] - 1) / 2;
	jus[4] = mor[4];
	jus[3] = mor[3] - jus[4] * 4;
	jus[2] = mor[2] - jus[3] * 3 - jus[4] * 6;
	jus[1] = mor[1] - jus[2] * 2 - jus[3] * 3 - jus[4] * 4;
	jus[0] = n * (n - 1) / 2 - jus[1] - jus[2] - jus[3];
	printf("%lld", jus[4 - D]);
	return 0;
} 
```

~~我才不会告诉你 `freopen` 是我 RE 之后下的数据呢。~~

后记：

如何想到容斥呢？

~~看标签。~~

我们可以很容易求出 $mor_4,mor_3,mor_2,mor_1,mor_0$，然后我们发现 $jus_i$ 与 $mor_i$ 有一定的关系，就可以发现容斥可以做了。

~~反正我是看标签的。~~

---

## 作者：_ChongYun_ (赞：2)

题意就是给出一些长度为 $4$ 的字符串，求有多少对字符串**恰好**有 $p$ 个字符不相同。

我们会发现恰好有若干个字符不相同的字符串对数不是很好求，考虑将其问题转化。

我们设恰好有 $p$ 个字符不相同的字符串对的集合为 $S_1$，至少有 $p$ 个字符不相同的字符串对的集合为 $S_2$，至少有 $p+1$ 个字符不相同的字符串对的集合为 $S_3$。

很容易发现，$|S_1| = |S_2| - |S_3|$。~~虽然我光发现这个东西就用了十五分钟。因为萌新刚学容斥。~~

我们现在只需要求出至少有 $x$ 个字符不相同的字符串对数。发现求的结果变成了 $|\bigcup{s_i}|$，其中 $s_i$ 表示第 $i$ 种取出 $x$ 个字符位置组合不相同的字符串对的集合。

接着又发现，虽然我们很难求出不同的情况，但我们很容易在合理时间复杂度内求出取出字符相同的字符串对，这仅仅需要一个 `map`。

又因为字符数量为定值 $4$，所以应该将整个问题转化成求有多少对字符串恰好有 $4-p$ 个字符相同。

到这里，题目的思路就讲完了。因为代码实现不难，这里就不一一解释了。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,x;
int a[114514];
int qwq[114514],qaq[114514],cnt1=0,cnt2=0;
string str[114514];
void init(){
    map<string,int> mp;
    for(int k=1;k<16;k++){
        mp.clear();
		for(int i=1;i<=n;i++){
			string u;
			for(int j=0;j<4;j++){
				if((k>>j)&1) u+=str[i][j];
			}
			mp[u]++;
		}
		int cntt=0;
		for(auto i:mp) cntt+=i.second*(i.second-1);
		a[k]=cntt/2;
	}
	for(int k=1;k<16;k++){
		int cntt=0;
		for(int j=0;j<4;j++){
			if((k>>j)&1) cntt++;
		}
		if(cntt==x) qwq[++cnt1]=k;
	}
    for(int k=1;k<16;k++){
		int cntt=0;
		for(int j=0;j<4;j++){
			if((k>>j)&1) cntt++;
		}
		if(cntt==x+1) qaq[++cnt2]=k;
	}
    return ;
}
int get_union(int cnt,int S[]){
    int ans=0;
    for(int k=1;k<(1<<cnt);k++){
		int cntt=0,kk=0;
		for(int i=1;i<=cnt;i++){
			if((k>>(i-1))&1){
				kk|=S[i];
				cntt++;
			}
		}
		if(cntt&1) ans+=a[kk];
		else ans-=a[kk];
	}
	return ans;
}
signed main(){
	cin>>n>>p; x=4-p;
	for(int i=1;i<=n;i++) cin>>str[i]; init(); 
    cout<<(x?get_union(cnt1,qwq):n*(n-1)/2)-get_union(cnt2,qaq)<<endl;
	return 0;
}
```

---

## 作者：LinuF (赞：1)

~~今天模拟赛里面遇到这道题。但是因为很睿智的错误（一个字符敲错）让我爆零。~~

### 题目意思

题目意思很简单。

### 思路

看见那么小的字符串，还要求**恰好 $D$ 个对应位置不相同**，很容易会想到去用容斥解决。

首先我们可以把恰好 $x$ 个位置不同的匹配数做一个转换，转换为至少 $x$ 个位置不同的匹配数减去至少 $x+1$ 不同的匹配数，很套路的前缀转换思想。

现在的问题就转变成了要求至少 $x$ 个位置不同的匹配数量，怎么去求。很显然的容斥问题。举个很简单的例子我们要去求至少一个位置不同的匹配，我们分别统计这四个位置不同的的匹配情况，用容斥求并集即可。

但是会遇到一个问题就是难以去计算指定位置不同的匹配数，但是计算指定位置相同的办法很简单。那正难则反，我们把问题变成求恰好 $4-D$ 个位置相同的方案数。

那现在还有个问题，如何求指定位置相同的匹配数，我这里是采用一个 `map<string,int>` 来解决的，其实哈希也可以。

```cpp
for(int state=1;state<(1<<4);state++){
    map<string,int> s;
    for(int i=1;i<=n;i++){
        string cr;
        for(int j=0;j<4;j++){
            if((state>>j)&1){
                cr+=c[i][j];
            } 
        }
        s[cr]++;
    }
    int num=0;
    for(auto x : s){
        num+=x.second*(x.second-1);
    }
    num/=2;
    sum[state]=num;
}
```

我采用类似状压的方法处理指定位置相同的方案数求法。求出所有状态的方案数就更便于求并集了。

```cpp
for(int state=1;state<(1<<cnt);state++){
    int st=0,num=0;
    for(int i=1;i<=cnt;i++){
        if((state>>(i-1))&1) st|=q[i],num++; 
    }
    if(num%2){
        ans1+=sum[st];
    }
    else ans1-=sum[st];
}
```

这是求并集的代码。

全部代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename types>
inline void read(types &x){
    x = 0; char c = getchar(); int f = 1;
    while (!isdigit(c)){ if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= f; return;
}
inline void read(){}
template<typename types, typename... Args>
void read(types &x, Args&... args){
    read(x), read(args...);
    return;
}
template<typename types>
void write(types x){
    if (x < 0) putchar('-'), x = -x;
    types k = x / 10;
    if (k) write(k);
    putchar(x - k * 10 + '0');
    return;
}
const int N=2e5+5;
int n,x;
char c[N][5];
int sum[N],cnt=0,cnt2=0,q[N],p[N];
void solve(){
    read(n,x);
    x=4-x;//恰好x个相等的
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++){
            cin>>c[i][j];
        }
    }
    int ans1=0,ans2=0;
    for(int state=1;state<(1<<4);state++){
        map<string,int> s;
        for(int i=1;i<=n;i++){
            string cr;
            for(int j=0;j<4;j++){
                if((state>>j)&1){
                    cr+=c[i][j];
                } 
            }
            s[cr]++;
        }
        int num=0;
        for(auto x : s){
            num+=x.second*(x.second-1);
        }
        num/=2;
        sum[state]=num;
    }
    cnt=cnt2=0;
    for(int state=1;state<(1<<4);state++){
        int num=0;
        for(int i=0;i<4;i++){
            if((state>>i)&1){
                num++;
            }
        }
        if(num==x) q[++cnt]=state;
        if(num==x+1) p[++cnt2]=state;
    }
    //要求x的并集
    for(int state=1;state<(1<<cnt);state++){
        int st=0,num=0;
        for(int i=1;i<=cnt;i++){
            if((state>>(i-1))&1) st|=q[i],num++; 
        }
        if(num%2){
            ans1+=sum[st];
        }
        else ans1-=sum[st];
    }
    //求x+1的并集
    for(int state=1;state<(1<<cnt2);state++){
        int st=0,num=0;
        for(int i=1;i<=cnt2;i++){
            if((state>>(i-1))&1) st|=p[i],num++; 
        }
        if(num%2){
            ans2+=sum[st];
        }
        else ans2-=sum[st];
    }
    if(x==0){
        ans1=n*(n-1)/2;
    }
    write(ans1-ans2);puts("");//做差分   
}
signed main(){
#ifndef ONLINE_JUDGE
    solve();
    return 0;
}
```


------------
~~赛时我还拍了过了小样例，但是我把第 60 行的 $i$ 写成了 $n$。~~


---

## 作者：Herowin (赞：1)

二进制+容斥思想+哈希

题目完全等价转化于“有多少对字符串满足恰好 $4 - D$ 个对应位置的字符相同”可以继续转化成 “满足$4 - D$个对应位置的组数 $-$ 非恰好的组数”由此可以使用容斥的思想来解决此题。

$f(i)$表示恰好i个对应位置字符串相同的组数 ， $g(i)$表示i个对应位置相同的组数

便有 

$f(3) = g(3)$ 由于本题满足字符串不会相等

$f(2) = g(2)-\dbinom{3}{1}\times f(3)$

$f(1) = g(1)-\dbinom{3}{2}\times f(3) -\dbinom{2}{1}\times f(2)$

$f(0) = g(0)-f(1)-f(2)-f(3)$

接下来是我重点想说的，也就是实现。感觉其他几篇题解的实现过于复杂了些。
我们可以二进制来枚举所有情况(1表示选,0表示不选) ， 然后求出满足当前二进制的字符串的哈希值，最后用map求解出$g(i)$ 就可以了。
核心代码如下所示

```cpp
	rep (i , 1 , 16) t1[i] = t1[i >> 1] + (i & 1) ;
	rep (k , 0 , 15) {
		map <u64 , int> o ;
		LL cnt = 0 ;
		rep (i , 1 , n) {
			u64 id = 0 ;
			rep (j , 1 , 4) if (k & (1 << (j - 1))) id = id * 260 + ch[i][j] ;
			cnt += o[id] , ++o[id] ;
		}
		g[t1[k]] += cnt ;
	}
	
	f[3] = g[3] , f[2] = g[2] - f[3] * 3 ;
	f[1] = g[1] - f[2] * 2 - f[3] * 3 ;
	f[0] = g[0] - f[2] - f[3] - f[1] ;
```









---

## 作者：729hao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6521)

------------
## 思路
看数据范围，有这么一句话：
> 对于 $75\%$ 的数据，保证字符串中只包含小写字母 $a\sim f$ 以及数字。**因此可以视为 $16$ 进制数**；

并且：
> 对于 $100\%$ 的数据，保证 $2\le n\le 5\times 10^4$，$1\le D\le 4$，所有输入的字符串没有重复，串中的字符仅可能为 $a\sim z$ 或者数字字符。

于是我们就可以把输入看作 $36$ 进制数。并且字符串长度仅有 $4$，那么这个 $36$ 进制数转 $10$ 进制后最大为 $36^4-1=1,679,616$，只开一维是不大的。

有恰好 $D$ 个对应位置的字符不同，就是有恰好 $4-D$ 个对应位置的字符不同。显然统计相同的比统计不同的要简单得多。

因为长度只有 $4$，我们可以稍微暴力一点，**枚举哪些位置上的数相同**，一共只有 $15$ 种情况，然后看有多少字符串的这些位置相同。

于是我们可以用桶来存对应位置下，字符组成的个数。即 $bck_{i,j,k}$ 表示有 $i$ 个位置相同，第 $j$ 种情况下，组成的 $36$ 转 $10$ 进制的数为 $k$。
例如，当 $i=2,j=3,k=41$ 时，对应下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/qk619xj4.png)

这样做，空间是完全开得下的：
>$i=1$ 时最多只有 $4$ 种情况，大小为 $4\times 36=144$ 个 int 类变量；  
>$i=2$ 时最多只有 $6$ 种情况，大小为 $6\times 36^2=7776$ 个 int 类变量；  
>$i=3$ 时最多只有 $4$ 种情况，大小为 $4\times 36^3=186624$ 个 int 类变量；  
>$i=4$ 时最多只有 $1$ 种情况，大小为 $1\times 36^4=1679616$ 个 int 类变量。

一共只占了 $144+7776+186624+1679616=1874160$ 个 int 变量，约占空间 $7.15MB$。

处理完每一个字符串后，再扫一遍每一个字符串 $s$，枚举 $i,j$，找到字符串对应的 $k$，那么 $kck_{i,j,k}-1$ 就是与 $s$ 有**至少 $i$ 个**相同的。

最后，求出对于 $i(i\le4)$，**至少有 $i$ 个位置**相同的字符串对数，容斥求出**有且仅有 $i$ 个位置**相同的对数，结束。
## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e4;
const int F=36;
int n,d,fc[4][F],sc[6][F*F],thc[4][F*F*F],lc[F*F*F*F],ans[5],cnt;
//fc即bck[1]，sc即bck[2]，thc即bck[3]，lc即bck[4]
int tt(char c){
	if(c>='0'&&c<='9')return c-'0';
	return c-'a'+10;
}
struct info{
	string t;
	int f[4],s[6],th[4],l;
	void ul(){
		int cnt=0;
		for(int i=0;i<4;i++){
			f[i]=tt(t[i]);
			fc[i][f[i]]++; 
		}
		cnt=0;
		for(int i=0;i<4;i++){
			for(int j=i+1;j<4;j++){
				s[cnt]=tt(t[i])*36+tt(t[j]);
				sc[cnt][s[cnt]]++;
				cnt++;
			}
		}
		cnt=0;
		for(int i=0;i<4;i++){
			for(int j=i+1;j<4;j++){
				for(int k=j+1;k<4;k++){
					th[cnt]=tt(t[i])*36*36+tt(t[j])*36+tt(t[k]);
					thc[cnt][th[cnt]]++;
					cnt++;
				}
			}
		}
		l=tt(t[0])*36*36*36+tt(t[1])*36*36+tt(t[2])*36+tt(t[3]);
		lc[l]++;
	}
}a[N+5];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
//	freopen("P6521_1.in","r",stdin);
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].t;
//		printf("pass\n");
		a[i].ul();
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++){
			ans[1]+=fc[j][a[i].f[j]]-1;
		}
		for(int j=0;j<6;j++){
			ans[2]+=sc[j][a[i].s[j]]-1;
		}
		for(int j=0;j<4;j++){
			ans[3]+=thc[j][a[i].th[j]]-1;
		}
		ans[4]+=lc[a[i].l]-1;
//		printf("%lld:%lld %lld %lld %lld\n",i,ans[1],ans[2],ans[3],ans[4]);
	}
	ans[3]-=ans[4]*4;
	ans[2]-=ans[3]*3+ans[4]*6;
	ans[1]-=ans[2]*2+ans[3]*3+ans[4]*4;
	ans[0]=n*1ll*(n-1)-ans[1]-ans[2]-ans[3]-ans[4];
//	printf("%lld %lld %lld %lld\n",ans[1],ans[2],ans[3],ans[4]);
	cout<<ans[4-d]/2ll;
	return 0;
}
```

---

## 作者：Annihilation_y (赞：0)

挑战你谷最短正确代码。

### 思路
这题正着想不好做，可以反着想。分别找到有一位相同，两位相同，三位相同和四位相同的情况。最后的答案利用充斥原理求出即可。

按位枚举所有的字符串。因为每个字符串的长度一定为 $4$，所以直接枚举的话总个数也不多。

拿一个 $s$ 数组记录每一种情况的所有字符串，另有一个 $mp$ 记录出现次数。

### Code
~~~c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5;
#define int long long

map<string,int> mp[20];
int tot[20];
int n,d,ans[5]; 
string S,s[20][MAXN];

int CL(int x){
	if(x==1 || x==2 || x==4 || x==8) return 1;
	if(x==3 || x==5 || x==6 || x==9 || x==10 || x==12) return 2;
	if(x==7 || x==11 || x==13 || x==14) return 3;
	if(x==15) return 4;
}
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++) {
		cin>>S;
		string x;
		for(int j=1;j<=15;j++) {
			x="";
			if(j&8) x+=S[0];  
			if(j&4) x+=S[1]; 
			if(j&2) x+=S[2]; 
			if(j&1) x+=S[3];
			if(mp[j][x]==0) s[j][++tot[j]]=x;
			mp[j][x]++;
		}
	}
	for(int i=1;i<=15;i++) {
		int x=CL(i);
		for(int j=1;j<=tot[i];j++){
			ans[x]+=mp[i][s[i][j]]*(mp[i][s[i][j]]-1)/2;
		}
	}
	if(d==1) cout<<ans[3]-ans[4]*4;
	if(d==2) cout<<ans[2]-ans[3]*3+ans[4]*6;
	if(d==3) cout<<ans[1]-ans[2]*2+ans[3]*3-ans[4]*4;
	if(d==4) cout<<n*(n-1)/2-ans[1]+ans[2]-ans[3]+ans[4];
} 
~~~

---

## 作者：FBW2010 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P6521)

# 前言

一道简单的容斥，可本蒟蒻用了一个和许多题解不一样的思路过了，这里分享一下我的神奇思路。

# 思路

首先，直接求不同是很麻烦的，我们可以**正难则反**，转化成求有多少对有 $4-d$ 个位置恰好相同。同样的，我们还会发现如果固定哪些位置相同，可以直接用 **map** 求出数量。也就是说，我们能知道有多少对字符串的固定几个位置相同。

为了方便表示，我们直接把 $d$ 赋为 $4-d$。如果直接暴力枚举哪几个位置相同，分别求出答案累加，那肯定会有重复的。因为我们求出的不一定只有那几位相同，其他位也可能相同。这时，我们不难想到用**容斥**去掉多余情况，也就是去掉两种同时满足的，再加上三种同时满足的，之后以此类推。如果不理解的可以参考代码。

你以为这就完了？如果这样直接交上去，会直接获得 $30$ 分的好成绩。原因是这样算出来的是**至少**有 $d$ 个相同的个数。~~不愧是洛谷，数据这么水~~。此时我们可以直接将 $d$ 加一，再跑一遍，直接减去便能求出刚好 $d$ 个的了。

# 代码

代码实现略微有些麻烦。我是先一遍 DFS 预处理出每种选 $d$ 个的情况，放进 bitset 里，然后再来一遍 DFS 容斥。但这样复杂度是 $O(2^{C_4^d}n\log n)$ 的，会 T 两个点。但实际上只会有 $2^4$ 种不同的方案，这样会重复算很多，于是可以在第二次 DFS 时记忆化或提前与处理一下，复杂度就只有 $O(2^4n\log n)$ 了，可以通过此题。

~~不开 long long 见祖宗~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int n,d,cnt;
long long ans,f[105]/*记忆化数组*/;
string s[N];
bitset<5> t,vis[105]/*预处理方案的bitset*/;
void DFS(int x){ //预处理方案 
	if(x>4){
		if(t.count()==d)vis[++cnt]=t;
		return;
	}
	DFS(x+1);
	t[x]=1;
	DFS(x+1);
	t[x]=0;
}
void DFS2(int x,int k){ //容斥 
	if(x>cnt){
		if(!k)return;
		long long sum=0;
		if(f[t.to_ulong()]!=-1)sum=f[t.to_ulong()];
		else{ //计算数量 
			map<string,int> mp;
			for(int i=1;i<=n;i++){
				string p="";
				for(int j=1;j<=4;j++){
					if(t[j])p.push_back(s[i][j]);
				}
				sum+=mp[p];
				mp[p]++;
			}
			f[t.to_ulong()]=sum;
		}
		if(k%2)ans+=sum; //容斥，奇数加上，偶数减去 
		else ans-=sum;
		return;
	}
	DFS2(x+1,k);
	bitset<5> t2=t;
	t|=vis[x];
	DFS2(x+1,k+1);
	t=t2;
}
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=" "+s[i];
	}
	d=4-d;
	memset(f,-1,sizeof(f));
	DFS(1);
	DFS2(1,0);
	if(d==4){ //有4个就没必要再跑一遍了 
		cout<<ans;
		return 0;
	}
	long long k=ans;
	memset(f,-1,sizeof(f));
	ans=cnt=0;
	d++;
	DFS(1);
	DFS2(1,0);
	cout<<k-ans;
	return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6521)

说实话这题一眼容斥，是因为以前做一个让我印象很深刻的类似的题目 ([link](https://www.luogu.com.cn/problem/P5123))，然后还得益于之前做过的一个容斥 dp（好像？）

回归正题。首先我们先考虑变成求恰好 $4-D$ 个相同的，然后试试容斥。容斥一般是钦定两个东西，一个是至少，另一个是恰好。而且我们发现这里字符串长度极小，于是大胆状压。

设 $f_{i,S}$ 表示至少在集合 $S$ 中与 $i$ 相同的个数，$g_{i,S}$ 表示恰好在集合 $S$ 中与 $i$ 相同的个数。$f_{i,S}$ 是很容易计算的，我们用个桶即可，现在就是如何用 $f_{i,S}$ 求得 $g_{i,S}$。

与其他题解不同，我没有用计算组合数那套，而是去用这个 $f$ 和 $g$ 本身的内在联系去计算。

$$f_{i,S}=\sum_{S\subset T}g_{i,T}$$

其实这个式子是十分显然的。

我们着重观察，我们要求的是 $g_{i,S}$，已知 $f_{i,S}$，假如说我们已经知道了除 $g_{i,S}$ 的其他，我们就可以求出来了。重点是我们发现这可以倒着来枚举 $S$ 就行了！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
#define ll long long
int inline read()
{
    int num=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
    return num*f;
}
int n,D,f[N][16],g[N][16],cnt[16],vis[5];
ll sum[16],ans;
char a[N][5];
map<string,int>mp;
int main(){
    n=read();D=read();
    for(int i=0;i<8;i++)
    {
        cnt[i<<1]=cnt[i];
        cnt[i<<1|1]=cnt[i]+1;
    }
    for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
    for(int S=0;S<16;S++)
    {
    	int x=S;
        for(int j=4;j>=1;j--)
        	vis[j]=x%2,x/=2;
        mp.clear();
        for(int i=1;i<=n;i++)
        {
            string str="";
            for(int j=1;j<=4;j++)
                if(vis[j])str+=a[i][j];
            mp[str]++;
        }
        for(int i=1;i<=n;i++)
        {
            string str="";
            for(int j=1;j<=4;j++)
                if(vis[j])str+=a[i][j];
            g[i][S]=f[i][S]=mp[str]-1;
        }
    }
    for(int i=1;i<=n;i++)
    {
    	for(int S=15;S>=1;S--)
        {
        	for(int T=S&(S-1);T;T=S&(T-1))
        		g[i][T]-=g[i][S];
        	g[i][0]-=g[i][S];
        }
    }
    for(int i=1;i<=n;i++)
        for(int S=0;S<16;S++)
            sum[S]+=g[i][S];
    for(int S=0;S<16;S++)
        if(cnt[S]==4-D)ans+=sum[S];
    printf("%lld",ans/2);
    return 0;
}
```

时间复杂度 $O(N\times 3^w)$，其中 $w=4$ 为字符串的长度。

------------

### 题外话

那个 link 是 sky 选拔出到的原题，而且之前还讲过，然后我写挂了，于是无缘 sky。![](https://cdn.luogu.com.cn/upload/image_hosting/7wenf40l.png)

哦对了，写这道题也是因为 5.4 模拟赛放的 T1。

---

## 作者：banned_gutongxing (赞：0)

## 思路分析

恰好有 $D$ 个位置不同，可以考虑**广义容斥原理**。

用 $g(S)$ 代表至少 $S$ 位置集合中相同的对数。

用 $f(S)$ 代表恰好 $S$ 位置集合中相同的对数。

显然 
$$g(S)=\sum_{T\supseteq S}{f(T)}$$
根据广义容斥原理
$$f(S)=\sum_{T\supseteq S}{(-1)^{|S|-|T|}g(T)}$$


## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+10;
namespace math{
	int frac[MAXN];
	int qpow(int a,int b){
		if(b==0) return 1;
		if(b==1) return a;
		int k = qpow(a,b>>1);
		k*=k;
		if(b&1) k*=a;
		return k;
	}
	int C(int n,int m){
		if(n<m) return 0;
		return frac[n]/(frac[m]*frac[n-m]);
	}
	int get(int n,int m){
		return C(m+n-1,m);
	}
	int lowbit(int k){
		return k&(-k);
	}
	int bit(int k){
		int sum = 0;
		while(k){
			sum ++;
			k -= lowbit(k);
		}
		return sum;
	}
	int log2(int k){
		for(int i = 0;i<=64;i++){
			int p = 1;
			if(p<<i==k) return i;
		}
		return 0;
	}
}
using namespace math;
int n,D,g[0b11111],f[0b11111];
map<string,int> mp[0b11111];
string tmp;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	frac[0] = 1;
	for(int i = 1;i<=MAXN-1;i++){
		frac[i] = frac[i-1]*i;
	}
	cin >> n >> D;
	for(int i = 1;i<=n;i++){
		cin >> tmp;
		for(int j = 0;j<=(1<<4)-1;j++){
			int k = j;
			string str = "";
			while(k){
				str += tmp[math::log2(lowbit(k))];
				k -= lowbit(k);
			}
			mp[j][str]++;
		}
	}
	for(int i = 0;i<=(1<<4)-1;i++){
		for(auto j:mp[i]){
			g[i] += j.second*(j.second-1)/2;
		}
	}
	int u = 4-D;
	D = 4-D;D = (1<<(D-1));
	int ans = 0;
	for(int S = 0;S<=(1<<4)-1;S++){
		for(int T = 0;T<=(1<<4)-1;T++){
			if((T&S)==S){
				f[S] += qpow(-1,bit(T)-bit(S))*g[T];
			}
		}
	}
//	cout << 0b1010 << endl;
	for(int i = 0;i<=(1<<4)-1;i++){
		if(bit(i)==u){
			ans += f[i];
		}
	}
	cout << ans;
	return 0;
}
```

---

