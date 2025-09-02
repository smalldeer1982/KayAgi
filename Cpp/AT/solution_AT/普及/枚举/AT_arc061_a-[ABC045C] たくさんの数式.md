# [ABC045C] たくさんの数式

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc045/tasks/arc061_a

`1` 以上 `9` 以下の数字のみからなる文字列 $ S $ が与えられます。 この文字列の中で、あなたはこれら文字と文字の間のうち、いくつかの場所に `+` を入れることができます。 一つも入れなくてもかまいません。 ただし、`+` が連続してはいけません。

このようにして出来る全ての文字列を数式とみなし、和を計算することができます。

ありうる全ての数式の値を計算し、その合計を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ &#124;S&#124;\ \leq\ 10 $
- $ S $ に含まれる文字は全て `1` 〜 `9` の数字

### Sample Explanation 1

考えられる数式としては、 `125`、`1+25`、`12+5`、`1+2+5` の $ 4 $ 通りがあります。それぞれの数式を計算すると、 - $ 125 $ - $ 1+25=26 $ - $ 12+5=17 $ - $ 1+2+5=8 $ となり、これらの総和は $ 125+26+17+8=176 $ となります。

## 样例 #1

### 输入

```
125```

### 输出

```
176```

## 样例 #2

### 输入

```
9999999999```

### 输出

```
12656242944```

# 题解

## 作者：Krimson (赞：11)

有一个$O(n^2)$的dp做法,后面还会提供一种$O(n)$的做法  
$f[i]$表示到了第i位的所有情况的和  
$num[i]$表示到了第i位有多少种不同的组合  
$sum[i][j]$表示从数字i到数字j为一组的值(比如123456,$sum[1][4]$就等于1234)  
所以不难得到这样一个柿子  
$$
f[i]=\sum\limits_{j=1}^{i}f[j-1]+sum[j][i]*num[j-1]
$$  
相当于去固定右端点i,去枚举左端点j的位置  
然后最终答案就是$f[n]$了    
下面是代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
string s;
int a[11];
ll f[11];
ll num[11];
ll sum[11][11];
int n;
int main(){
    num[0]=1;
    cin>>s;
    n=s.length();
    for(ri i=1;i<=n;++i){
        a[i]=s[i-1]-'0';
    }
    for(ri i=1;i<=n;++i){
        for(ri j=i;j<=n;++j){
            sum[i][j]=sum[i][j-1]*10+a[j];
        }
    }
    for(ri i=1;i<=n;++i){
        for(ri j=1;j<=i;++j){
            f[i]+=f[j-1]+sum[j][i]*num[j-1];
            num[i]+=num[j-1];
        }
    }
    print(f[n]);
    return 0;
}
```


------------
但是这道题目的柿子很简单,以至于给人一种可以$O(nlogn)$过去的感觉   
发现$num[i]$就是相当于每一个空位上放或不放$+$的方案数,也就是$2^{i-1}$    
其中$num[0]=1$  
为了方便此处定义$2^{-1}=1$  
这个时候再来看刚才推出来的柿子,$\sum\limits_{j=1}^{i}f[j-1]$是可以通过前缀和$O(1)$得到的,瓶颈在另半边上  
$\sum\limits_{j=1}^{i}2^{j-2}sum[j][i]$,如果单考虑第i个数字的贡献而不去看别的数字,用$g[i]$表示此时第i位上的贡献  
$g[i]=a[i]\sum\limits_{j=1}^{i}2^{j-2}=a[i]2^{i-1}$  
$g[i-1]=10*a[i-1]2^{i-2}$  
以此类推就可以了  
所以$\sum\limits_{j=1}^{i}2^{j-2}sum[j][i]=\sum\limits_{j=1}^{i}10^{i-j}a[j]2^{j-1}$,可以发现后面的$a[j]2^{j-2}$与i没有关系,可以提前预处理出来  
于是此处用到$F[i]=\sum\limits_{j=1}^{i}a[j]2^{j-1}$  
可以发现$F[i]=2F[i-1]+a[i]$,$O(n)$得到  
所以$\sum\limits_{j=1}^{i}2^{j-2}sum[j][i]=\sum\limits_{j=1}^{i}10^{i-j}F[j]$,前面那一陀用$G[i]$表示  
同样可以推得$G[i]=G[i-1]*10+a[i]*2^{i-1}$,和$F[i]$没有关系了  
而且整理发现,上面这个过程的总复杂度**是$O(n)$的**!  
  

------------

接下来重新梳理一下上面的过程  
$f[i]=\sum\limits^{i-1}_{j=1}f[j]+G[i]=sum[i-1]+G[i]$  
$G[i]=G[i-1]*10+a[i]*2^{i-1}$  
只需要这两个简单的柿子就可以做到$O(n)$    
下面是代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
string s;
const int MAXM=11;
int a[MAXM];
ll f[MAXM];
ll sum[MAXM];
ll g[MAXM];
int n;
ll powt[MAXM];
int main(){
    num[0]=1;
    cin>>s;
    n=s.length();
    for(ri i=1;i<=n;++i){
        a[i]=s[i-1]-'0';
        sum[i]=sum[i-1]+a[i];
    }
    powt[0]=1;//2的k次方
    for(ri i=1;i<=n;++i){
        powt[i]=powt[i-1]<<1;
        g[i]=g[i-1]*10+a[i]*powt[i-1];         
        f[i]=sum[i-1]+g[i];
        sum[i]=sum[i-1]+f[i];
    }
    print(f[n]);
    return 0;
}
```


---

## 作者：Anaxagoras (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT2067)

### 0x00 所需知识

1. 深度优先搜索

1. 暴力枚举（其实也可以说没有）

### 0x01 思路

看到这题及其数据范围，我马上就想到了深度优先搜索。

搜索过程其实就是在每一位上枚举：

1. 这里有一个加号

1. 这里没有加号

这两种可能，所以在搜索过程种分类讨论就可以了。

### 0x02 AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
int a[11];
string st; 
inline void init()
{
	for(int i=0;i<n;i++)
	{
		a[i+1]=st[i]-'0';
	}
}
inline void dfs(int k,int sum,int num)//sum 是表示当前的和，num 是表示当前的数
{
	if(k==n+1)//枚举完成
	{
		ans+=num+sum;//加上答案及当前数
		return ;
	}
	num=num*10+a[k];
	dfs(k+1,sum+num,0);//这里有加号的情况
	dfs(k+1,sum,num);//这里没加号的情况
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>st;
	n=st.size();
	init();//初始化
	dfs(1,0,0);
	cout<<(ans>>1)<<'\n';//答案要除以 2
	return 0;
}
```

求求点赞，谢谢！

---

## 作者：cheating_dictator (赞：2)

有一定难度，但无奈数据太小(s<10)

导致爆搜都能A，这题爆搜的话难度最多黄题


------------

~~看起来像~~正解：推导每一位数字在各位出现次数，然后加起来

**举例1：$125$，这时总共有两个空**

要满足1在百位，必须满足‘1’后面两个空不能填加号，第三个空必须填加号

因此两个空都确定了

所以1在百位出现一次（$125$）

要满足1在十位，必须满足‘1’后面一个空不能添加号，后面第二个空必须填加号

两个空也确定了

1在十位出现一次（$12+5$）

要满足1在个位，必须满足‘1’后面一个空必须填加号

但还有一个空格没确定（1+2？5），于是1在个位出现$2^1$次（$1+25 和1+2+5$）

要满足2在十位，必须满足‘2’后面一个空不能添加号，第二个空必须填加号($1?25$)

但还有一个空格没确定，于是2在十位出现$2^1$次($125和1+25$)

... ...

------------
### **初步得到某数字在某位出现的个数为 2^（总空格数-已确定空格数)**

**举例2：$9999999999$**

列出各数字出现次数表

|  | 十亿位 | 亿位 | 千万位 | 百万位 | 十万位 | 万位 | 千位 | 百位 | 十位 | 个位 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| （从左往右）第1个9 | $2^0$ | $2^0$ | $2^1$ | $2^2$ | $2^3$ | $2^4$ | $2^5$ | $2^6$ | $2^7$ | $2^8$ |
| 第2个9  | 0 | $2^1$ | $2^1$ | $2^2$ | $2^3$ | $2^4$ | $2^5$ | $2^6$ | $2^7$ | $2^8$ |
| 第3个9  | 0 | 0 | $2^2$ | $2^2$ | $2^3$ | $2^4$ | $2^5$ | $2^6$ | $2^7$ | $2^8$ |
| 第4个9  | 0 | 0 | 0 | $2^3$ | $2^3$ | $2^4$ |  $2^5$| $2^6$ | $2^7$ | $2^8$ |
| 第5个9  | 0 | 0 | 0 | 0 | $2^4$ |  $2^4$| $2^5$ | $2^6$ | $2^7$| $2^8$ |
| 第6个9  | 0 | 0 | 0 | 0 | 0 | $2^5$ | $2^5$ | $2^6$ | $2^7$ | $2^8$ |
| 第7个9  | 0 |  0| 0 | 0 | 0 | 0 | $2^6$ | $2^6$ | $2^7$ | $2^8$ |
|  第8个9 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | $2^7$ | $2^7$ | $2^8$ |
| 第9个9  | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | $2^8$ | $2^8$ |
| 第10个9  | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | $2^9$ |

整理得出算式：$(2^9×1+2^8×19+2^7×180+2^6×1700+2^5×16000+2^4×150000+2^3×1400000+2^2×13000000+2^1×120000000+2^0×1100000000)×9=12656242944$

做法已经显而易见了

 _在观察中思考_ 

**Code：**
```cpp
#include<string>
#include<iostream>
#include<cmath>
using namespace std;
long long bit(int l,int r,int po){//计算2^l*10^po+2^(l+1)*10^(po-1)...+2^r
	if(l>r)
	return 0;
	long long cnt=0;
	for(int i=l;i<=r;i++)
	cnt+=(1<<i)*pow(10,po+l-i);
	return cnt;
}
int main(){
	string a;
	cin>>a;
	long long ans=0;
	for(int i=0;i<a.size();i++){
		ans+=((int)a[i]-'0')*((1<<i)*pow(10,a.size()-i-1)+bit(i,a.size()-2,a.size()-i-2));//各位数乘位值和
	}
	cout<<ans;
  return 0;//完美结束
}  
```


---

## 作者：dz_ice (赞：2)

说实话这个题不是蓝题吧......

看到$1≤∣S∣≤10$，自然想到可以暴力枚举加号的位置

程序也很好写，先数位分离，再dfs数字的每一位，分两种情况，可以将这一位与上一位合并，也可以添加一个加号

代码难度不大，下面是只有十几行的ac代码

```
#include<iostream>
#include<cstdio>
using namespace std;
long long n,sum,a[13]; //记得开long long
long long dfs(long long x,long long sum,long long sum1)
{
	if(x==1)
		return 2*sum+sum1+a[x]+sum1*10+a[x];
	return dfs(x-1,sum,sum1*10+a[x])+dfs(x-1,sum+sum1,a[x]); //分两种情况dfs
}
int main()
{
	cin>>n;
	while(n!=0)
		sum++,a[sum]=n%10,n/=10;
	cout<<dfs(sum,0,0)/2;
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
给定一个仅包含数字 $1\sim 9$ 的字符串 $S$，你可以在任意相邻两个字符的中间添加一个加号，使其变成一个加式。定义一个加式的权值为其所有加数的和。求所有可得到的加式的权值和。

**数据范围：$1\leqslant |S|\leqslant 10$。**
## Solution
由于此题的数据范围很小，因此我们可以直接枚举所有可能的加式。具体地，我们枚举每对相邻两个字符中间是否放上加号，然后计算这个加式的权值。这里可以通过 dfs 实现，由于可能的加式最多不超过 $2^9=512$ 种，因此可以很轻松地跑过去。
## Code
```cpp
namespace Solution {
	int n, vis[17];
	string s;
	ll ans;
	
	iv dfs(int x) {
		if(x >= n) {
			ll num = 0;
			F(int, i, 1, n) {
				num = num * 10 + s[i] - '0';
				if(vis[i] || i == n) ans += num, num = 0;
			}
			return;
		}
		vis[x] = 1, dfs(x + 1);
		vis[x] = 0, dfs(x + 1);
	}
	
	iv Main() {
		cin >> s, n = s.size(), s = " " + s;
		dfs(1), write(ans);
		return;
	}
}
```

---

## 作者：_Qer (赞：1)

一个比较水的DFS吧

深搜出所有的可能排列方案，计算出答案加起来就可以了，要说哪里难可能就是计算算式结果麻烦点吧

$2^n$的算法是稳过的。假设可以插10个+号（题目限制了字符串长），每个空有插或不插两种选择，那么总共就有$2^10=1024$种方法，每次计算也只用$O(strlen(s))$扫一遍，还是很快的，亲测总共12ms就过了

有个细节可能需要注意一下：$n$个数字间只有$n-1$个空，dfs和计算时不要循环多了

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
//以下数组下标统一0开始
char s[20];
long long ans, n;//n存下字符串长，方便使用
bool pls[20];//第i个为true表示在数字i和i+1间有加号
long long calc() {//计算结果
	//main函数提前处理了字符（s[i]-='0'）
    long long t = 0, sum = 0;
    for (int i = 0; i < n - 1; ++i) {//注意边界是<n-1
        t = t * 10 + s[i];//先加当前位
        if (pls[i]) {//如果有+
            sum += t;
            t = 0;//记得清0
        }
    }
    t = t * 10 + s[n - 1];//不要忘记最后一位数
    return t + sum;//结果也要加上
}
void dfs(int k) {
    if (k == n - 1) {
        ans += calc();
        return;
    }
    pls[k] = false;//不加+
    dfs(k + 1);
    pls[k] = true;
    dfs(k + 1);
}
int main() {
    cin >> s;
    n = strlen(s);
    for (int i = 0; i < n; ++i) {
        s[i] -= '0';
    }
    dfs(0);//是从0开始
    cout << ans << endl;
    return 0;
}
```

---

## 作者：SilverLi (赞：0)

[たくさんの数式 の 传送门](https://www.luogu.com.cn/problem/AT_arc061_a)

题目说要在 $S$ 中加 `+` 号，所以可以枚举放`+` 号的方案。

方案的记录可以用一个 `string` 先把 $S$ 复制过来，再在对应位置添加 `+` 号。

然后每次计算该方案的结果，全部加起来就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 15
int res,a[N];
string str;
int sum(string s) {
	int sum=0,t=0,tot=s.size();
	for(int i=0;i<tot;++i) {
		if(s[i]=='+')	sum+=t,t=0;
		else	t=t*10+s[i]-'0';
	}
	if(t)	sum+=t;
	return sum;
}
int main() {
	cin>>str;
	int l=str.size()-1;
	while(true) {
		for(int i=0;i<l;++i)	a[i+1]+=a[i]/2,a[i]%=2;
		if(a[l]!=0)	break;
		string s;
		for(int i=0;i<l;++i) {
			s+=str[i];
			if(a[i]!=0)	s+='+';
		}
		s+=str[l],++a[0];
		res+=sum(s);
	}
	cout<<res;
	return 0;
}

```

---

## 作者：xuhanxi_dada117 (赞：0)

# [ABC045C] たくさんの数式 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc061_a)

## 题目大意

给出一个数串，求在串中任意添加加号能得到的数和。

## Solution

一看这题 $|S| \leq 10$ 肯定是搜索了。

搜索方法也很简单：枚举每个空加不加就行了，枚举玩在计算加起来。

注意在串变数的过程中一定看好数组下标！

## 代码

~~（听说以前是蓝题？？？）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;int a[60];bool Plus[60];string s;
void Get(){
	long long tmp=0;
	for(int i=1;i<=s.size();++i){
		tmp=tmp*10+a[i];
		if(Plus[i]) ans+=tmp,tmp=0;
	}
	ans+=tmp;
}
void dfs(int x){
	if(x>=s.size()){
		Get();
		return;
	}
	Plus[x]=false;
	dfs(x+1);
	Plus[x]=true;
	dfs(x+1);
}
int main(){
	cin>>s;
	for(int i=0;i<s.size();++i) a[i+1]=s[i]-'0';
	dfs(1);cout<<ans;
	return 0;
}
```
[Accept](https://www.luogu.com.cn/record/100362498)

## 后记

今天我本来在打 ```Atcode286``` ，结果做到一半 ```Atcoder``` 卡住了，于是就来刷题了...

---

## 作者：chufuzhe (赞：0)

这道题数据范围较小，暴力枚举就可以通过。

可以深搜枚举 $+$，具体就是枚举相邻两个数之间是否有 $+$，因为每个位置都有有和没有两种选择，所以时间复杂度就是 $O(2^|S|)$。而 $|S|$ $\leq$ $10$，显然可以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[15];
long long ans; //注意要用long long
void dfs(int dep, long long sum, long long s) { //深搜
	if(dep > n) { //枚举结束
		sum += s; //不要忘记加上最后一个数
		ans += sum; //累加结果
		return ;
	}
	s = s * 10 + a[dep]; //加上现在这一位
	dfs(dep + 1, sum + s, 0); //第dep和dep+1位中间有+
	dfs(dep + 1, sum, s); //第dep和dep+1位中间没有+
	return ;
}
int main()
{
	ios::sync_with_stdio(false);
	string st; //输入
	cin >> st;
	n = st.size();
	for(int i = 0; i < st.size(); i++)
		a[i + 1] = st[i] - '0';
	dfs(1, 0, 0);
	cout << ans / 2 << endl; //注意答案要除以二
	return 0;
}

```


---

## 作者：Ezio__Auditore (赞：0)

## Solution AT2067 たくさんの数式 / Many Formulas
[[ARC061A] たくさんの数式 / Many Formulas](https://www.luogu.com.cn/problem/AT2067)

##### $Date:\ Nov.\ 18th\ 2020$

---
##### 简要题意：
  给你一个长度为 $n$ ( $n\le 10$ ) 的数字串 $S$， 允许你在这个数子串中间加任意数量的 ' $+$ '，使其成为一个算式， 求出所有合法算式结果之和。

---
##### 简单的解法
  首先 $n\le 10$ 显然可以枚举每一位有无加号爆搜，这里就不给出代码了

##### 继续思考  
  介绍一个 $O(n)$ 的算法。
  
  
  但是秉承着~~抢最优解~~发掘优秀做法的初心。
  
  找找规律看看, 考虑每一位相对位置不变，所以**答案一定是每一位乘上一个系数**。
  
  设这个数字每一位分别是 $...\ d\ c\ b\ a$。
  
   开始爆搜 $+$ 找手动找规律：

  $ n = 1 \to Ans = a \times 1 $
  
  $ n = 2 \to Ans = b \times 11 + a \times 2 $
  
  $ n = 3 \to Ans = c \times 112 + b \times 22 + a \times 4$
  
  $ n = 4 \to Ans = d \times 1124 + c \times 224 + b \times 44 + a \times 8 $
  
  记录系数为 $f_{i, j}$ 表示 $n=i$ 时第 $j$ 位的系数，
  初始化 $f_{1, 1} = 1$，
  
  不难发现:
  $$
  f_{i, 1} = f_{i-1, 1}\times10 + 2^{i-2}\ (i\ge2)
  $$
  且有:
  $$
  f_{i_j}=f_{i-1, j - 1} \times 2\ (j\ge2)
  $$
  所以可得：
  $$
  Ans=\sum\limits_{i=1}^n{a_i\times f_{n, i}}
  $$
  整理得：
  $$
  Ans = \sum\limits_{i = 1}^{n}{a_i \times 2^{i - 1} \times ((\sum\limits_{j = 1}^{n - i}{10^{n - i - j} \times 2^{j - 1}) + 10^{n - i}})}
  $$

  
  ---
  
  **$O(n)$ 预处理系数 $(\sum\limits_{j = 1}^{n - i}{10^{n - i - j} \times 2^{j - 1}})+10^{n - i}$ 可以做到 $O(n)$ 求解。**
  
  预处理只需要让 $base_i$ 表示 $n=i+1$ 时的第一个系数。
  
  初始化 $base_0 = 1$ :
  $$
  base_i = base_{i - 1}\times 10 + 2^{i - 1}
  $$
  然后系数 $f_{n,i}$ 可通过 $base_{n-i}\times2^{i - 1}$。
  
  这样你就得到了一个优秀的 $O(n)$ 做法，但是 $n$ 实在太小了，显现不出优势。
  
---
### Code:
```cpp
#include <bits/stdc++.h>
// AT2067
typedef long long ll;
const int kMaxN = 1e1 + 5;
char s[kMaxN];
int base[kMaxN]; // 预处理系数
int pw[kMaxN]; // 预处理2次方
int main() {
  std::cin >> (s + 1);
  int n = strlen(s + 1);
  base[0] = pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw[i] = pw[i - 1] << 1;
    base[i] = (base[i - 1] << 3) + (base[i - 1] << 1)+ pw[i - 1]; // base * 10 + 2^(i-1)
  }
  ll ans = 0; // 答案统计需要long long
  for (int i = 1; i <= n; i++)
    ans += 1ll * (s[i] - '0') * (pw[i - 1]) * base[n - i];
  printf("%lld", ans);
  return 0;
}
```
---

  对于学有余力的同学可以来尝试一下这道题的超级加强版。
  
  [[Problem Statement]](https://www.luogu.com.cn/problem/U141427) < 100ms / 1MB > 享受极限卡常的快感！
  
  还有我写的对应题解 [在这里](https://www.luogu.com.cn/blog/Ezio--Auditore/solution-u141427)。虽然有那么**亿点点毒瘤**，但是做起来还是挺有意思和帮助滴。
  
---
**UPD:已重新排版。**

---

## 作者：Ancers (赞：0)

### AT2067 たくさんの数式 / Many Formulas
[题目传送门](https://www.luogu.org/problem/AT2067)  
### 题意
有一个仅由字符1到9构成的字符串S(1≤∣S∣≤10)，让你在中间添加+，使其变成一个加式。求所有方案的和值（详见样例解释）。
输入125,输出176.

有4种：

    125
    1+25=26
    12+5=17
    1+2+5=8

### 题解  
（驳回无脑暴搜）  
 看到题目直接想到的就是  
 对于字符串中的每一段数字分别计算贡献再求和  
每一段数字的贡献就是 数值*安排加号的方案数（该数值两边的加号已经安排好了）  
对于一个长为tot的序列 中间可以插入加号的的空为（tot-1）个  
那么对于一段长为len的数字 它安排加号方案数的计算方法如下：  
情况一：该段数字并没有处在边界上（没有拿第一位数字或者最后一位数字）  
        1.该段数字使得其内部无法填入加号，坑位减少（len-1）个；  
        2.该段数字两边无法填入加号，坑位减少2个；  
        3.合计减少坑位（len+1）个。  
        剩余坑位为（tot-1-len-1）=（tot-len-2）个  
情况二：该段数字处在边界上  
        1.内部无法填入加号，坑位减少（len-1）个；  
        2.该段数字的一边无法填入加号（另一边是边界，本来就没得坑位），坑位减少1个；  
        3.合计减少坑位（len）个。  
        剩余坑位为（tot-1-len）=（tot-len-1）个。  
那么知道坑位个数就可以算出方案数了吧  
对于每个坑可以填也可以不填，所以方案数就是2^（坑数）。  
最后累加就行了。  
还有一个关键点就是如何枚举每一段数字，这里我的方法是先枚举长度，再枚举起点。  
（时间比别的代码好像快那么几毫秒，纯粹是赢在算法上？）
### 代码
 ```cpp
#include <cstdio>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int a[20],q[20];
int tot;
ll ans;

signed main(){
	ll b=read();
	while (b){
		q[++tot]=b%10;
		b/=10;
	}
	for (int i(1);i<=tot;++i) a[i]=q[tot-i+1];//可能这一步还有更优处理。
	for (int l(1);l<=tot;++l)
		for (int i(1);i+l-1<=tot;++i){
			ll num=0;
			for (int j(i);j<=i+l-1;++j) num*=10,num+=a[j];
			//printf("%lld ",num);
			if (i==1||i+l-1==tot){//靠在边界上
				for (int i(1);i<=tot-l-1;++i) num*=2;
				ans+=num;
			}
			else {//没靠在边界上
				for (int i(1);i<=tot-l-2;++i) num*=2;
				ans+=num;
			}
		}
	printf("%lld",ans);
	return 0; 
}

```

---

## 作者：Xx_queue (赞：0)

我的方法:
## 找规律
(ps:考试的时候旁边的人都是用DFS写的)

对于一个由$n(n<=10)$个字符构成的字符串$abc...$,它的各种排列的方式都是固定的,所以一定有一个固定的规律能够算出答案,所以就来探究这个规律;

比如说$abc$,
可以拆成:
$a*100+b*10+c$、$a*10+b+c$、$a+b*10+c$、$a+b+c$

总和为
$(a*100+b*10+c)+(a*10+b+c)+(a+b*10+c)+(a+b+c)$

合并一下:$Sum=(a*112+b*22+c*4)$

这说明对于任何一个$n=3$的字符串,其答案为:
$Sum=(a*112+b*22+c*4)$

同理可以算出$n=4$时答案为$Sum=(a*1124+b*224+c*44+d*8)$

公式证明可以用组合数的方式尝试证明,这里不再赘述;

代码如下:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
string s;
LL ans,len;
LL count(LL a,LL i)
{
	LL s=0;
	LL cnt=i;
	i=pow(2,i);
	s+=i;
	for(int j=1;j<=len-cnt-1;j++)
	{
		s=s*10+i;
		i*=2;
	}
	return a*s;
}
int main()
{
	cin>>s;
	len=s.length();
	for(LL i=0;i<s.length();i++)
	{
		ans+=count(s[i]-'0',i);
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：520Enterprise (赞：0)

提供一个O(n^2)的做法（可以优化到O(nlogn)）。

一共有n-1位。

对于第1位上的数（从前往后），有2^(n-1)次被选为个位。

对于第2位上的数，有2^(n-2)次被选为个位，2^(n-2)被选为十位。

对于第3位上的数，有2^(n-2)次被选为百位，2^(n-3)被选为十位，2^(n-3)被选为个位。

……以此类推

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=1000;
long long shuzi[maxn],mi2[20]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096},ans; 
long long mi10[20]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000};
int main()
{
	char a[maxn];
	cin>>a;
	int len=strlen(a);
	for(int i=0;i<len;i++)
		shuzi[i+1]=a[i]-'0';
	ans=shuzi[len]*mi2[len-1];
	for(int i=len-1;i>=1;i--)
	{
		 for(int j=len-2;j>=i-1;j--)
		{
			int ai=shuzi[i];
			int mi2lenj=mi2[len-j];
			int mi10j2=mi10[j-2];
			ans+=shuzi[i]*mi2[j]*mi10[len-j-2];
		}
		ans+=shuzi[i]*mi2[i-1]*mi10[len-i];
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：wsk_1202 (赞：0)

因为字符串长度小于等于10，故直接爆搜即可。

对于每一个可以放加号的地方，考虑放或不放。当枚举到最后一个可以放的地方，就可以计算和了。

代码
```cpp
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
long long ans,a[100],f=1,tmp,l;
int vis[100];
string s;
void calc()
{
	long long tmp=0;
	for(int i=1;i<=l;i++)
	{
		tmp=tmp*10+a[i];
		if(vis[i])ans+=tmp,tmp=0;//如果某个地方放了加号，从中间断开，继续计算
	}
	ans+=tmp;//要加上剩余的部分
}
void dfs(int pos)
{
	if(pos==l)//如果到了最后一个位置，计算，返回
	{
		calc();
		return;
	}
	vis[pos]=1;dfs(pos+1);//放加号
	vis[pos]=0;dfs(pos+1);//不放加号
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);//cin,cout系列玄学加速
	cin>>s;l=s.length();
	for(int i=0;i<l;i++)a[i+1]=s[i]-48;//把字符串转化成数字，方便计算
	dfs(1);//爆搜
	printf("%lld\n",ans);
	return 0;
}
```

---

