# Codeforces Subsequences

## 题目描述

Karl likes Codeforces and subsequences. He wants to find a string of lowercase English letters that contains at least $ k $ subsequences codeforces. Out of all possible strings, Karl wants to find a shortest one.

Formally, a codeforces subsequence of a string $ s $ is a subset of ten characters of $ s $ that read codeforces from left to right. For example, codeforces contains codeforces a single time, while codeforcesisawesome contains codeforces four times:  codeforcesisawesome,  codeforcesisawesome,  codeforcesisawesome,  codeforcesisawesome.

Help Karl find any shortest string that contains at least $ k $ codeforces subsequences.

## 样例 #1

### 输入

```
1```

### 输出

```
codeforces```

## 样例 #2

### 输入

```
3```

### 输出

```
codeforcesss```

# 题解

## 作者：Skyjoy (赞：7)

分析一下这道题，可以发现这道题计算一个字符串中的 "codeforces" 的个数的方法其实很简单：把无关的字符给排掉，然后给每一种连续出现的字符计数，最后把每一种连续的字符的个数乘起来就是答案了。

那我们要如何保证字符总数最小呢？小学数学老师告诉我们：**和一定差小积大，积一定差小和小**。所以我们只需要把每一个字符的个数尽量平均分，这样字符总数就是最小的了！

简单吧！看代码（只有20行）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll k,cnt[10],tot;
char ch[10]={'c','o','d','e','f','o','r','c','e','s'};
ll calc(){
	ll res=1;
	for(int i=0;i<10;i++)res*=cnt[i];
	return res;
}
int main(){
	scanf("%lld",&k);
	while(1){
		cnt[tot++]++;
		tot%=10;
		if(calc()>=k)break;
	}
	for(int i=0;i<10;i++)for(int j=1;j<=cnt[i];j++)printf("%c",ch[i]);
	return 0;
}
```

---

## 作者：KXY_Moon (赞：2)

## 题意

需要求一个字符串 $S$ 且 `codeforces` 这个字符子串出现在 $S$ 中 $u$ 次($u>=k$)，使得 $S$ 的长度最短。

## 解法

枚举 `codeforces` 中出现的几个字符，再判断是否按照原顺序排列即可。

同时，为了使 $S$ 的长度最短，每个字符出现的次数尽量平均。

## 代码：


```cpp
// 不可抄袭！
# include<iostream>
# include<cstdio>
const int N=10;
#define int long long
using namespace std;
int n,t,k[N],op(1);
char H[N]={'c','o','d','e','f','o','r','c','e','s'};
bool thisper(){ op=1;
	for(int i=0;i<N;++i) op*=k[i];
	return (op>=n);}
main(){ scanf("%d",&n);
	while(true){
		++k[++t],t%=N;
		if(!thisper());
		else break;
	}for(int i=0;i<N;i++)
	  for(int j=1;j<=k[i];j++)
		printf("%d",H[i]);   
	return 0;
}
```
End.

---

## 作者：wjh2011 (赞：2)

这道题要求字符串 $S$ 最短，所以只能有 `codeforces` 所包含的字母，且要按所有字母在 `codeforces` 中出现的顺序出现。

因为和不变，差小积大；积不变，差小和小。所以每个字母出现的次数要尽量平均。

注意不开 `long long` 见祖宗。

十分简单的代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x, cnt[10];
char c[10] = {'c', 'o', 'd', 'e', 'f', 'o', 'r', 'c', 'e', 's'};
bool check() {
    int mul = 1;
    for (int i = 0; i < 10; i++) mul *= cnt[i];
    return mul >= n;
}
signed main() {
    cin >> n;
    while (1) {
        cnt[x++]++;
        x %= 10;
        if (check()) break;
    }
    for (int i = 0; i < 10; i++)
        for (int j = 1; j <= cnt[i]; j++)
            cout << c[i];
    return 0;
}
```

---

## 作者：CSP_Sept (赞：2)

#### 题意简述

给定 $k(1\le k\le 10^{16})$，请构造一个**最短的**字符串，使这个字符串为 `codeforces` 的字串个数**至少**为 $k$。

#### 思路

考虑贪心。

构造一个由 $a_0$ 个 `c`，$a_1$ 个 `o`，$a_2$ 个 `d`，$\cdots\ $，$a_9$ 个 `s` 连结的字符串，它为 `codeforces` 的字串个数为 $\prod\limits_{i=0}^9a_i$。考虑让 $a_0\sim a_9$ 尽可能接近。

#### 代码 $\And$ 讲解

```cpp
#include <cstdio>

using namespace std;
typedef unsigned long long ull;//开 ull
ull k;
char s[10]={'c','o','d','e','f','o','r','c','e','s'};
int a[10]={0};//统计 a_0 ~ a_9
inline ull Num(){//求当时为 "codeforces" 的字串个数
    ull Ans=1;
    for(int i=0;i<10;i++)
        Ans*=a[i];
    return Ans;
}
void Work(){
    scanf("%lld",&k);
    int Cnt=0;
    while(1){
        a[Cnt]++;
        Cnt++;
        Cnt%=10;//若 Cnt=10 则返回更新为 1
        if(Num()>=k) break;//满足题意则跳出
    }
    for(int i=0;i<10;i++)
        for(int j=0;j<a[i];j++)
            printf("%c",s[i]);//顺序 print
    return;
}
int main(){
    Work();
    return 0;
}
```

---

## 作者：Sora1336 (赞：2)

这题目怕不是有毒，，，样例万恶之源...

直接导致有人在谷群内询问如何在 1s 内输出 $10^{16}$ 个字符。

------------

好了说题解。

首先读题，不难发现是**最少** $k$ 个子串。我们开一个数组，存储 `codeforces` 每一个字母要输出几个。

显然的，每个字母的数量应该尽可能接近对方，这样就可以使子串的数量尽可能多，现在可以简单地通过增加的方法得到最优分布，比如输出 `cccdddeeefffooorrreeesss` 之类的字符串。

具体实现请查看代码。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll k,cnt=1,a[15];
    string s="codeforces";
    cin>>k;
    for(int i=0;i<10;i++)a[i]=1;
    while(cnt<k) {
        for(int i=0;i<10;i++){
            if(cnt<k){
                cnt/=a[i],
                cnt*=a[i]+1,
                a[i]++;			//对每个字符进行处理
            }else break;
        }
    }
    for(int i=0;i<10;i++)
        for(int j=1;j<=a[i];j++)
        	cout<<s[i];
    return 0;
}
```


---

## 作者：Implicit (赞：1)

构造

简单组合知识可得，`codeforces` 各位置字母分别出现 $a_0, a_1,\cdots, a_9$ 次（顺次连接）时，子串个数为 $\prod a_i$，然后字符串长度就是 $\sum a_i$ 呗 .

于是我们的任务就是：

- 已知 $\prod a_i\ge k$
- 最小化 $\sum a_i$ .

我们有 算术-几何 均值不等式：
> 对于序列 $\{a\}$，我们有
> $$\sqrt[^n]{\prod a}\le \dfrac1n\displaystyle\sum a$$
> 当且仅当 $a$ 所有元素都相等时等号成立 .

以下均有 $n=9$ .

简单变形，可得

$$\sum a\ge n\sqrt[^n]{\prod a}\ge n\sqrt[^n]{k}$$

于是有 $\displaystyle\sum a$ 的一个下界 $n\sqrt[^n]k$ .

下界当且仅当 $a_1=a_2=\cdots=a_n$ 时取到（也就是上面那个均值不等式条件）

我们要最小化 $\displaystyle\sum a_i$，只需要令 $a_1=a_2=\cdots=a_n$ 即可，那么 $a$ 的所有元素的值都是 $\sqrt[^n]k$ .

由于某些不可抗力，我们的 $a_i$ 必须是整数，咋办呐？

我们尽量达到这个条件吧，平均分 $a_1,a_2,\cdots, a_n$ 即可 .

Code:

```cpp
typedef long long ll;
ll ans[10],n;
const char ch[]="codeforces";
// 0 1 2 3 4 5 6 7 8 9
// c o d e f o r c e s
int main()
{
	scanf("%lld",&n); int idx=0;
	while (true)
	{
		++ans[idx]; ++idx; idx%=10;
		if (1ll*ans[0]*ans[1]*ans[2]*ans[3]*ans[4]*ans[5]*ans[6]*ans[7]*ans[8]*ans[9]>=n) break;
	}
	for (int i=0;i<10;i++)
		while (ans[i]--) putchar(ch[i]);
	return 0;
}
```

暴力跳最多跳 $\sqrt[9]k$ 次，绰绰有余啊 .

---

## 作者：songtaoran (赞：0)

## 题目简述
给定数字 $k$，求最短的**至少**有 $k$ 个`codeforces`**子序列**的字符串。  
## 做法
### 求一个字符串有几个`codeforces`子序列
去掉多余的字符（即除了 `c`，`o`，`d`，`e`，`f`，`o`，`r`，`c`，`e`，`s`以外的字符），看每个字符有多少个连续的个数，相乘起来就是了。  
例子：`ccoooddeeefiurforctuycess`有多少个 `codeforces`子序列？  
1. 去掉多余字母,字符串变成 `ccoooddeeefforccess`;
2. 各个字符连续个数：$2$，$3$，$2$，$3$，$2$，$1$，$1$，$2$，$1$，$2$;
3. 乘起来：$2 \times 3 \times 2 \times 3 \times 2 \times 1 \times 1 \times 2 \times 1 \times 2 = 288$。
### 如何求出最短字符串使得其至少有 $k$ 个`codeforces`
题目就相当于选 $10$ 个数字，使得ta们的乘积 $\geq k$。  
那如何使其最短呢？  
我们知道，要使其最短，首先不能有多余的字母。即只能有`c`，`o`，`d`，`e`，`f`，`o`，`r`，`c`，`e`，`s`这些字母。  
~~我们小学二年级就学过（突然毕导~~我们小学时期就学过和同近积大，那么我们让这 $10$ 个数平均就行啦。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
char c[20] = {'c', 'o', 'd', 'e', 'f', 'o', 'r', 'c', 'e', 's'};
ll k, cnt = 0, ans[20];
ll calc(){ // 注意类型要是 long long 
	 ll p = 1; // 乘积 
	 for(ll i = 0; i < 10; i++) p *= ans[i];
	 return p;
}
int main(){
	cin >> k;
	while(1){
		ans[cnt++]++;
		if(cnt == 10) cnt = 0;
		if(calc() >= k) // 如果已经有至少 k 个 'codeforces' 
			break; // 就退出循环 
	}
	for(ll i = 0; i < 10; i++)
		for(ll j = 1; j <= ans[i]; j++) putchar(c[i]);
	return 0;
}
// author: songtaoran
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1368B)

设 `codeforces` 中各字符的出现次数分别为 $a_0,a_1,a_2 \dots a_9$。

那么，这个字符串为 `codeforces` 的子串个数为 $\prod\limits_{i=0}^9 a_i$。

现在的问题就变成了：在 $\prod\limits_{i=0}^9 a_i \ge k$ 的情况下，构造 $a$ 使得 $\sum\limits_{i=0}^9 a_i$ 尽量小。

众所周知，在多个数乘积一定时，它们的差越小，和就越小。

所以，给 $a_0$ 到 $a_9$ 轮流加 $1$，这样可以保证它们的差不超过 $1$。只要它们的乘积大于 $k$ 就输出字符串并结束。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long k, a[10], cnt;
string cf = "codeforces";
long long mul(){long long ans = 1; for (int i = 0; i < 10; i++) ans *= a[i]; return ans;}//求乘积
int main(){
	scanf("%lld", &k);
	while (true){
		a[cnt % 10]++; cnt++;//轮流加一
		if (mul() >= k) break;
	}
	for (int i = 0; i < 10; i++)
		for (int j = 1; j <= a[i]; j++) printf("%c", cf[i]);//按每个字符的数量输出
    return 0;
}
```

---

## 作者：coritom (赞：0)

## 分析
这题其实很简单，用一个 $a$ 数组计录每一个字母需要几个。如果每个字母的个数更相近，计算量就越少。
\
那怎样算有多少个串呢？只需要把每个字母的个数相乘就可以了，因为每一个字母可以跟其它所有串组合，自然要把它们乘起来。
＼
### 代码如下

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int k;
int a[15] = {0};
int ans, cnt = 0, num;
char s[13] = {'c', 'o', 'd', 'e', 'f', 'o', 'r', 'c', 'e', 's'};
void solve(){
	while(1){
		a[cnt++]++;
		cnt %= 10;
		num = 1;
		for(int i = 0; i <= 9; i++){
			num *= a[i];
		}
		if(num >= k) break;
	} 
}
void input(){
	scanf("%lld", &k);
}
void print(){
	for(int i = 0; i <= 9; i++){
		for(int j = 1; j <= a[i]; j++) printf("%c", s[i]);
	} 
}
signed main(){
	input();
	solve();
	print();
	return 0;
}

```


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

这是一道构造题。

`codeforces` 字母分别出现 $a_0$ 至 $a_9$ 次时，子串个数为 $\prod a_i$，字符串长度为 $\sum a_i$。我们已知 $\prod a_i\ge k$，使 $\sum a_i$ 最大。

对于数组 $a$，$\sqrt[n]{\prod a}\le\dfrac{1}{n}\sum a_i$。在 $a$ 数组的所有元素都相等时才等号成立。也就是 $\sum a_i\ge n\sqrt[n]{\prod a}\ge n\sqrt[n]{k}$。则 $\sum a$ 的下界为 $n\sqrt[n]{k}$。因为 $\sum a_i$ 要最小，只要让 $a$ 数组的所有元素为 $\sqrt[n]{k}$。因为 $a_i$ 必须是整数，只要把 $a$ 数组平分就可以了。

时间复杂度 $O(\sqrt[9]{k})$，可以说非常低。

参考代码：

```cpp
#include <iostream>
using namespace std;

long long ans[10];
const char ch[] = "codeforces";

int main()
{
    long long n;
    cin >> n;
    int idx = 0;
	while (true)
	{
		ans[idx]++;
		idx++;
		idx %= 10;
		if (1ll * ans[0] * ans[1] * ans[2] * ans[3] * ans[4] * ans[5] * ans[6] * ans[7] * ans[8] * ans[9] >= n) break;
	}
	for (int i = 0; i < 10; i++) while (ans[i]--) cout << ch[i];
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析： 

因为要求长度最小，所以我们每个字符就应该发挥最大的价值，不会有没有作用的字符。   

设有 $x_1$ 个 $c$ ，$x_2$ 个 $o$ ，$x_3$ 个 $d$ ，$x_4$ 个 $e$ ，$x_5$ 个 $f$ ，$x_6$ 个 $o$ ，$x_7$ 个 $r$ ，$x_8$ 个 $c$ ，$x_9$ 个 $e$ ，$x_{10}$ 个 $s$ 。(均为连续)   

则子序列的种数为 $\prod_{i=1}^{10} a_i$    

为了使得 $\sum_{i=1}^{10} a_i$ 的值最小，种数又最大，我们就要使得 $a_i$ 的值都相对平均。     

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll k;

char c[15]={'c','o','d','e','f','o','r','c','e','s'};
ll res[15]={0,1,1,1,1,1,1,1,1,1,1};

ll sol(){
	ll tot=1;
	for(int i=1;i<=10;++i){
		tot*=res[i];
	}
	return tot;
}

int main()  
{
	k=read();
	int cnt=0;
	while(1){
		if(sol()>=k) break;
		cnt%=10;
		res[++cnt]++;
	}
	for(int i=0;i<10;++i){
		for(int j=1;j<=res[i+1];++j){
			printf("%c",c[i]);
		}
	}
	return 0;
}

```

---

## 作者：xiaolilsq (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1368B)

## 题意简述

求出长度最小的字符串使得`codeforces`作为**子序列**出现在此字符串中至少 $k$ 次。

## 题目分析

不妨先求出这个字符串的长度，显然这个长度有单调性，即若 $a<b$ ，那么长度为 $a$ 的字符串中出现子序列`codeforces`的最多次数一定小于长度为 $b$ 的字符串中出现子序列的最多次数。

考虑二分答案，那么接下来的问题就是求长度为 $n$ 的字符串中出现子序列`codeforces`的最多次数。

贪心地想，显然我们发现`c...co...od...de...ef...f...`的情况下肯定是最优的，不妨设字符`c`出现的次数为 $a_1$ ，字符`o`出现次数为 $a_2$ ，以此类推，那么答案就是 $\prod_{i=1}^{10}a_i$ ，问题变成：构造一个长度为 $10$ 的序列 $a$ ，满足 $\sum_{i=1}^{10}a_i=n$ 的情况下使得 $\prod_{i=1}^{10}a_i$ 最大，**尽量平均分**最优。

至此我们找到了求长度为 $n$ 的字符串中出现子序列`codeforces`的最多次数的方法，那么如何构造呢？其实在二分答案的时候我们已经找到了方法：**尽量平均分**。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
char s[10]={'c','o','d','e','f','o','r','c','e','s'};
int tmp[10];
void divide(int n){
	int s=n/10;
	for(int i=0;i<10;++i)
		tmp[i]=s;
	s=n%10;
	for(int i=0;i<s;++i)
		++tmp[i];
}
int main(){
	long long k;read(k);
	int l=10,r=400;
	while(l<r){
		int mid=(l+r)>>1;
		divide(mid);long long s=1;
		for(int i=0;i<10;++i)s*=tmp[i];
		if(s<k)l=mid+1;else r=mid;
	}
	divide(l);
	for(int i=0;i<10;++i)
		while(tmp[i]--)
			pc(s[i]);
	pc('\n');
	return 0;
}
```

---

## 作者：Loxilante (赞：0)

贪心水题~

---

看到样例后:不是吧怎么这么简单

看到数据范围后:???

---

题意是求有至少n个"codeforces子串"的字符串的最小长度。有点像周长相等的矩形中正方形面积最大，我们让每个字母的个数量尽量均匀，这样就可以让子串个数最多：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll w[15];
const string str = "codeforces";
inline ll mult(void) // 现在有多少个codeforces子串
{
	ll ans = 1;
	for(int i = 0; i < 10; i++) ans *= w[i];
	return ans;
}
signed main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll n, pos = 0;
    cin>>n;
	for(int i = 0; i < 10; i++) w[i] = 1; // 不能用memset~
	while(mult() < n) // 子串个数大于n后跳出
	{
		w[pos++]++; // 表示对应str中字母的个数增加
		if (pos == 10) pos = 0; // 一轮结束 回到第一个字母c
	}
	for(int i = 0; i < 10; i++)
        for(int j = 0; j < w[i]; j++) // 输出w[i]次字符
            cout<<str[i];
	cout<<endl;
	return 0;
}
```



---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1368B)

### $\texttt{Description}$

给定一个正整数 $k \ (1 \le k \le 10^{16})$ （所以一定要开 `long long`），求一个字符串，满足其中至少有 $k$ 个子序列是 `codeforces` 的字符串 $S$。

### $\texttt{Solution}$

这题我们只需要用贪心的思想来做就行。我开始甚至还想枚举，但是看到数据范围后就直接换思路了。

我们可以将所有字母尽量平均分，这样子序列就会更多。

理由如下：

假设有两个整数 $a$ 和 $b$ 且 $a = \max(a,b)$，则有如下规律：

如果 $a+b$ 不变，就会 $a-b$ 越小，那么 $a \times b$ 就越大。

如果 $a \times b$ 不变，就会 $a-b$ 越小，那么$a+b$ 就越小。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 10;
const string ss = "codeforces";
int n, sum[N], tot;

bool check() {
	int res = 1;
	for (int i = 1; i <= 10; i++) res *= sum[i - 1];
	// res就是含有 codeforces 的子序列个数
	return res >= n;
}

inline int read() { // 快读
	int x = 0, f = 1;
	char ch;
	
	while (isdigit(ch) == 0) {ch = getchar(), f = (ch == '-' ? -1 : 1);}
	while (isdigit(ch) == 1) {x = x * 10 + (ch ^ 48), ch = getchar();}
	return x * f;
}

signed main() {
	n = read();
	
	while (true) { // 死循环一直到满足条件
		sum[tot]++;
		tot++;
		tot %= N; // 就是 tot 对 10 取模
		if (check() == 1) break;
	}
	
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= sum[i - 1]; j++) {
			cout << ss[i - 1];
		}
	}
	
	return 0;
}
```

完结。

---

