# Kaavi and Magic Spell

## 题目描述

Kaavi, the mysterious fortune teller, deeply believes that one's fate is inevitable and unavoidable. Of course, she makes her living by predicting others' future. While doing divination, Kaavi believes that magic spells can provide great power for her to see the future.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336C/28f922a8d61b005da66667b890172094e2d89686.png)

Kaavi has a string $ T $ of length $ m $ and all the strings with the prefix $ T $ are magic spells. Kaavi also has a string $ S $ of length $ n $ and an empty string $ A $ .

During the divination, Kaavi needs to perform a sequence of operations. There are two different operations:

- Delete the first character of $ S $ and add it at the front of $ A $ .
- Delete the first character of $ S $ and add it at the back of $ A $ .

Kaavi can perform no more than $ n $ operations. To finish the divination, she wants to know the number of different operation sequences to make $ A $ a magic spell (i.e. with the prefix $ T $ ). As her assistant, can you help her? The answer might be huge, so Kaavi only needs to know the answer modulo $ 998\,244\,353 $ .

Two operation sequences are considered different if they are different in length or there exists an $ i $ that their $ i $ -th operation is different.

A substring is a contiguous sequence of characters within a string. A prefix of a string $ S $ is a substring of $ S $ that occurs at the beginning of $ S $ .

## 说明/提示

The first test:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336C/fc1e4ff58b9c787fb84f7835d5e964b3b486f03c.png)

The red ones are the magic spells. In the first operation, Kaavi can either add the first character "a" at the front or the back of $ A $ , although the results are the same, they are considered as different operations. So the answer is $ 6\times2=12 $ .

## 样例 #1

### 输入

```
abab
ba```

### 输出

```
12```

## 样例 #2

### 输入

```
defineintlonglong
signedmain```

### 输出

```
0```

## 样例 #3

### 输入

```
rotator
rotator```

### 输出

```
4```

## 样例 #4

### 输入

```
cacdcdbbbb
bdcaccdbbb```

### 输出

```
24```

# 题解

## 作者：Fairicle (赞：30)

这题其实和[合唱队](https://www.luogu.com.cn/problem/P3205)有点像。

这题主要的难点是状态的设计和转移，我们可以看作每次都是一个区间增加一个元素变成另外一个区间，于是想到区间 dp。

记串 $s,t$ 长度分别为 $slen,tlen$。设 $f_{i,j}$ 表示有多少种方案使得 $s_1$ 到 $s_{j-i+1}$ 能通过插入最前端和插入最后端构成 $t_i$ 到 $t_j$ 的字符组成。

那么状态初始化就是

$$f_{i,i}=2(t_i=s_1)$$

状态转移方程就是

$$f_{j,i+j-1}+=f_{j+1,i+j-1}(t_j=s_i)$$

$$f_{j,i+j-1}+=f_{j,i+j-2}(t_{i+j-1}=s_i)$$

然而当你这样计算并把 $f_{1,tlen}$ 作为最终答案的时候，发现有亿点点不对。因为这样只算了最终答案是 $t$ 的方案数，而答案叫我们求前缀是 $t$ 的方案数。

我们只需要修改一下定义：设 $f_{i,j}$ 表示有多少种方案使得 $s_1$ 到 $s_{j-i+1}$ 能通过插入最前端和插入最后端使得前 $min(tlen,j-i+1)$ 个字符构成 $t_i$ 到 $t_{min(tlen,j)}$ 的字符组成。

那么初始化就要加上一个东西：

$$f_{i,i}=2(i\in(tlen,slen])$$

状态转移方程就变为

$$f_{j,i+j-1}+=f_{j+1,i+j-1}(t_j=s_i||j>tlen)$$

$$f_{j,i+j-1}+=f_{j,i+j-2}(t_{i+j-1}=s_i||i+j-1>tlen)$$

答案就是 $\sum\limits_{i=tlen}^{slen}f_{1,i}$

代码很短，但是干货很多。

```cpp
#define ri register int
#define mod 998244353
#define N 3010
char s[N],t[N];
int slen,tlen;
ll f[N][N];
int main()
{
	scanf("%s%s",s+1,t+1);
	slen=strlen(s+1),tlen=strlen(t+1);
	for(ri i=1;i<=tlen;++i) if(t[i]==s[1]) f[i][i]=2;
	for(ri i=tlen+1;i<=slen;++i) f[i][i]=2;
	for(ri i=2;i<=slen;++i){
		for(ri j=1;i+j-1<=slen;++j){
			if(j>tlen||t[j]==s[i]) f[j][i+j-1]=(f[j][i+j-1]+f[j+1][i+j-1])%mod;
			if(i+j-1>tlen||t[i+j-1]==s[i]) f[j][i+j-1]=(f[j][i+j-1]+f[j][i+j-2])%mod;
		}
	}
	ll ans=0;
	for(ri i=tlen;i<=slen;++i) ans=(ans+f[1][i])%mod;
	cout<<ans;
    return 0;
}
```


---

## 作者：万弘 (赞：18)

洛谷的$L^AT_EX$可能挂，建议去[My blog](https://oierwanhong.cc/2020/04/16/CF1336C/)查看

## CF1336C

题意：给一个初始串$s$和目标串$t$，每次可以取出（并删除）$s$的第一个字符加入另一个串$A$的开头或末尾（初始为空），求$t$是$A$的前缀的方案数（任意一步操作不同即不同，$s$不必删完）

$|t|\le |s|\le 3000$

<!--more--> 

区间dp。令$f(l,r)$表示用$s$的前$r-l+1$个字符拼出$t_{l...r}$的方案数。（对于$i>|t|,t_i$可为任意字符）

边界：$t_i=s_1,f(i,i)=2$

转移：枚举长度$len$,和左端点$l$,则$r=l+len-1$。  

- 当$s_{len}=t_l,f(l,r)$可由$f(l+1,r)$转移而来
- 当$s_{len}=t_r,f(l,r)$可由$f(l,r-1)$转移而来

最后的答案就是$\sum _{i=|t|}^{|s|} f(1,i)$

注意取模。时间复杂度$\mathcal O(n^2)$.

```cpp
#include<bits/stdc++.h>
char s[3011],t[3011];
int f[3011][3011],yg=998244353;//yg txdy!!!
int main()
{
    scanf("%s%s",s+1,t+1);
    int n=strlen(s+1),m=strlen(t+1),res=0,i,j;
    for(i=1;i<=n;++i)f[i][i]=(i>m||s[1]==t[i])*2;
    for(int len=2;len<=n;++len)
        for(i=1;i+len-1<=n;++i)
        {
            j=i+len-1;
            if(i>m||s[len]==t[i])(f[i][j]+=f[i+1][j])%=yg;
            if(j>m||s[len]==t[j])(f[i][j]+=f[i][j-1])%=yg;
        }
    for(i=m;i<=n;++i)(res+=f[1][i])%=yg;
    printf("%d",res);
    return 0;
}
```

还有一份更短的代码，现在是size排序rk2：[link](https://codeforces.ml/contest/1336/submission/76952794)

---

## 作者：Mihari (赞：5)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1336C)

# 题解

考虑构想一下最终情况：在 $S$ 的前 $i$ 位已经以某种放入方式放进 $A$ 之后，$T$ 成为了 $A$ 的前缀，然后 $T$ 的 $i+1$ 到 $lenS$ 位直接放入 $A$ 的后面（显然 $i$ 有可能为 $lenS$），如果我们直接枚举这个 $i$，显然很难做，考虑往前退一步的情况，一共就两种情况：

1. $S$ 的第 $i$ 位直接放入 $A$ 的后面；
2. $S$ 的第 $i$ 位放到了 $A$ 的前面；

对于第一种情况，说明 $A$ 在 $S[i]$ 放入之前，其前缀就已经是 $T$ 了，即 $S[1...i-1]$ 构成了 $T$

对于情况二，说明$S[i]$ 还未放入时 $A$ 的前缀是 $T[2...lenT]$，即 $S[1...i-1]$ 构成了 $T[2...lenT]$

考虑再往前退一步？四种情况

1. 1. $S$ 的第 $i-1$ 位直接放入 $A$ 的后面；
   2. $S$ 的第 $i-1$ 位放到了 $A$ 的前面；
2. 1. $S$ 的第 $i-1$ 位直接放入 $A$ 的后面；
   2. $S$ 的第 $i-1$ 位放到了 $A$ 的前面；

对于 $1.1$，说明 $A$ 在 $S[i],S[i-1]$ 放入之前，其前缀已经是 $T$，即 $S[1...i-2]$ 构成了 $T$

对于 $1.2$，说明 $A$ 在 $S[i],S[i-1]$ 放入之前，其前缀是 $T[2...lenT]$，且 $T[1]=S[i-1]$，即 $S[1...i-2]$ 构成了 $T[2...lenT]$

对于 $1.3$，说明 $A$ 在 $S[i],S[i-1]$ 放入之前，其前缀是 $T[2...lenT]$，且 $T[1]=S[i]$，即 $S[1...i-2]$ 构成了 $T[2...lenT]$

对于 $1.4$，说明 $A$ 在 $S[i],S[i-1]$ 放入之前，其前缀是 $T[3...len]$，且 $T[2]=S[i-1],T[1]=S[i]$，即 $S[1...i-2]$ 构成了 $T[3...len]$

再往前面退...通过看上面的分析中“即...”部分，我们会发现，**总是 $S[1...x]$ 构成了 $T[l...r]$，然后考虑加入 $S[x+1]$ 会发生什么**

**这就是这道题的子状态，只需将其写作状态**，即定义状态 $f[l][r]$ 为 $S[1...r-l+1]$ 构成 $T[l...r]$ 的部分的方案数

对于这个状态，首先有初始化 $f[i][i]=2,S[1]=T[i]$，然后考虑转移：

1. 如果 $S[r-l+1]=T[r]$，则 $f[l][r]+=f[l][r-1]$；
2. 如果 $S[r-l+1]=T[l]$，则 $f[l][r]+=f[l+1][r]$；

但是直到这里，我们求的都是用 $S$ 构成 $T$ 的方案数，但是题目只要求 $T$ 成为 $A$ 的前缀，而我们的状态定义显然有 $i>lenT$ 的部分，对于这些部分，我们进行特殊定义：

> 当 $i>lenT$ 时，$T[i]$ 可以为任意字符。

这样这个方法就完整了，最后的答案显然为
$$
\sum_{i=lenT}^{lenS}f[1][i]
$$

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13394160.html
```



---

## 作者：suxxsfe (赞：4)

我太蒻了刚发出来就被指出一个小错，所以重新提交一遍  

[CF1336C Kaavi and Magic Spell](http://codeforces.com/contest/1336/problem/C)  
**区间dp**  

## 题意  

给一个长度为 $n$ 的字符串 $S$ 和一个长度为 $m$ 的字符串$T$ ，$1\le m\le n$，然后开始有一个空串 $A$，接下来可对 $S$ 串进行 $n4 次操作:  

- 把S的首个字符添加到A的开头然后删掉  

- 把S的首个字符添加到A的尾端然后删掉  

问在操作过程中使得 $A$ 的前 $m$ 个字符为 $T$（也就是前缀为 $T$）的情况共有多少？  
长度不同或者是操作序列中有某个地方不同可视为是不同情况。  

--------------  

我们先让 $T$ 的长度和 $S$ 相同，在多处来的那 $m+1,m+2,\cdots,n$ 那几位上，钦定它和 $S$ 中所有元素都“相等”，因为在这些位置上我们可以取任意值  
设计状态：$f(l,r)$ 表示的是满足 $\forall l\le i\le r,S_i=T_i$ 能构造出多少操作序列  

那么假设我们在删除 $S_i$ 并把它往 $A$ 里添加，此时 $A$ 中一定有了 $i-1$ 个元素  
考虑 $f(l,r),r-l+1=i$ 可以由什么状态转移而来  

- $S_i=T_l$，则可以把 $S_i$ 添加到这个 $[l+1,r]$ 区间的前面，构成 $[l,r]$，就是 $f(l,r)+=f(l+1,r)$  
- $S_i=T_r$，这和上面就一样了，$f(l,r)+=f(l,r+1)$  

-----------  

基本已经完成了，现在考虑初始状态和答案  
$f(i,i)=2[S_i=T_i]$，就是说一种方法是把 $S_1$ 从前面添加到 $A$ 的第一个元素，一种是从后面添加，虽然结果一样，但是题目要求这是两种不同方式  

长度不同算不同情况，这也说明了不一定要操作 $n$ 次，只要操作 $i,m\le i\le n$ 次就行了  
所以答案是 $\sum_{i=m}^{n}f(1,i)$  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
#define mod 998244353
char s[3006],t[3006];
int f[3006][3006];
int main(){
	std::scanf("%s",s+1);std::scanf("%s",t+1);
	int n=std::strlen(s+1),m=std::strlen(t+1);
	for(reg int i=1;i<=m;i++) f[i][i]=(s[1]==t[i])<<1;
	for(reg int i=m+1;i<=n;i++) f[i][i]=2;
	for(reg int i=2,len=2;i<=n;i++,len++){
		for(reg int l=1,r=len;r<=n;l++,r++){
			if(l>m||s[i]==t[l]) f[l][r]+=f[l+1][r],f[l][r]%=mod;
			if(r>m||s[i]==t[r]) f[l][r]+=f[l][r-1],f[l][r]%=mod;
		}
	}
	int ans=0;
	for(reg int i=m;i<=n;i++) ans=(ans+f[1][i])%mod;
	std::printf("%d",ans);
	return 0;
}
```

---

## 作者：pengyule (赞：2)

$t$ 末尾添加通配符，进行简单区间 dp。  
本题坑点：可以只操作 $\le n$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3005,mod=998244353;
inline void add(int &x,int y){(x+=y)>=mod&&(x-=mod);}
int n,m,f[N][N];
char s[N],t[N];
int main(){
	scanf("%s%s",s+1,t+1),n=strlen(s+1),m=strlen(t+1);
	for(int i=m+1;i<=n;i++)t[i]='#';
	for(int i=1;i<=n+1;i++)f[i][i-1]=1;
	for(int len=1;len<=n;len++)for(int l=1,r=len;r<=n;l++,r++){
		if(s[r-l+1]==t[r]||t[r]=='#')add(f[l][r],f[l][r-1]);
		if(s[r-l+1]==t[l]||t[l]=='#')add(f[l][r],f[l+1][r]);
	}
	int ans=0;
	for(int i=m;i<=n;i++)add(ans,f[1][i]);
	cout<<ans<<'\n';
}
```

---

## 作者：huayucaiji (赞：2)

首先这道题乍一看没有任何思路，本人想到的是“后缀自动机，后缀数组，后缀树”能不能做，答案是：我也不知道（因为我也不是对着三个算法和数据结构和熟悉，如果有人用这三种方法做出来了，私信我谢谢）。但是我可以告诉你，这道题可以用 DP 来解决。

### 定状态

我们定义 $f_{i,j}$ 为用 $s_1$ 到 $s_{j-i+1}$ 根据题目中的规则，填充 $t_i$ 到 $t_j$ 的方案数。

我们在定义 $S,T$ 的长度为 $n,m$。

### 转移方程

很明显，这是一个**区间DP**的定义方式，所以转移方程很好想，应该是这样的：

$$f_{i,j}=\max \begin{cases} f_{i+1,j}+f_{i,j-1}&(i>m|t_i=s_{j-i})\&(j>m|t_j=s_{j-i})\\f_{i+1,j}&i>m|t_i=s_{j-i}\\f_{i,j-1}&j>m|t_j=s_{j-i}\\0 \end{cases}$$

Q1：为什么 $i$ 会大于 $m$？
A1：因为我们拼出的字符串 $A$ 的长度不一定小于 $T$ 的长度，所以在拼完前 $m$ 个字符，后面可以随便拼，故 $i>m$ 时，可以随便拼字符。

### 边界

我们在上面说过：$i,j\geqslant m$ 是可以的，所以 $i$ 要循环到 $n$。但是注意区间DP的常见错误！先枚举长度，再枚举起点！

### 初始化

很明显我们要初始化 $f_{i,i}$。

$$f_{i,i}=\max \begin{cases}2&i>m|t_i=s_1\\0\end{cases}$$

和上面的转移方程很类似。原因不再赘述。

### 写代码

**注意我用的是 string，一定要注意下表从 $0$ 开始。所以可能会和上面的转移方程有一些不同之处（主要是边界）。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=3000+10,mod=998244353; 

int n,m,f[maxn][maxn];
string s,t;

signed main() {
	
	cin>>s>>t;
	n=s.size();
	m=t.size();
	
	for(int i=0;i<n;i++) {
		if(i>=m||t[i]==s[0]) {
			f[i][i]=2;
		}
	}
	for(int len=2;len<=n;len++) {
		for(int i=0;i<n;i++) {
			if(len+i-1>=n) {
				break;
			}
			int j=len+i-1;
			if(i>=m||t[i]==s[len-1]) {
				f[i][j]+=f[i+1][j];
			}
			if(j>=m||t[j]==s[len-1]) {
				f[i][j]+=f[i][j-1];
			}
			f[i][j]%=mod;
		}
	}
	
	int ans=0;
	for(int i=m-1;i<n;i++){
		ans+=f[0][i];
		ans%=mod;
	}
	
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2200}$
---
### 解题思路：

主要是这个前缀的要求不好处理，考虑将字符串 $T$ 补上若干个可以匹配任意字符的特殊字符，由于原来串中保证没有数字，可以设定为任意数字，例如一个纯数字字符串 $\text{1145141919810}$ 的循环。

然后具体考虑动态规划，$f_{i,j}$ 表示用 $S$ 中前 $j-i+1$ 个表示出字符串 $T$ 中位置 $i$ 到 $j$ 的方案数。

具体转移的时候考虑左右两个端点，若当前左端点恰好和 $S$ 中对应的位置相同，那么就可以进行转移，右端位置同理。

由于可以在任意位置停下来，最后的答案是 $\sum_{i=m}^nf_{1,i}$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MAXN=3005,MOD=998244353;
int n,m,f[MAXN][MAXN],ans;
char S[MAXN],T[MAXN],c,X[50]={'1','1','4','5','1','4','1','9','1','9','8','1','0'};
bool check(char a,char b){
	if(a>='0'&&a<='9')return 1;
	return a==b;
}
signed main(){
	for(c=getchar();c<='z'&&c>='a';c=getchar())S[++n]=c;
	for(;c>'z'||c<'a';c=getchar());
	for(;c<='z'&&c>='a';c=getchar())T[++m]=c;
	for(int i=m+1;i<=n;i++)T[i]=X[i%13];
	for(int i=1;i<=n;i++)if(check(T[i],S[1]))f[i][i]=2;
	
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			
			if(check(T[i],S[len]))f[i][j]=(f[i][j]+f[i+1][j])%MOD;
			if(check(T[j],S[len]))f[i][j]=(f[i][j]+f[i][j-1])%MOD;
		}
	}
	for(int i=m;i<=n;i++)ans=(ans+f[1][i])%MOD;
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：Silence_World (赞：0)

# 思路

题意比较简单，不多赘述，此题主要是需要想到用区间 dp。

## 为什么要用区间 dp

此题就类似于维护一个区间，往这个区间里塞东西让这个来求方案数，其实本质上还是维护一个区间的，有方案数，很显然是 dp（~~这个不用多说了吧~~），和区间有关，便想到了区间 dp。

## dp 方法

我们考虑一种风格情况，当一个数塞进来字符串构成了一个前缀，即无论哪个数塞进去，方案便是 $+1$，这种思路很好想，但我们考虑放在前面的情况，很明显的，在前面便是其想构成一个前缀，说明其在前缀字符之中，即要构成前缀，所以初始化就很简单了，当 $t_{i} = s_{1}$ 时，便有两种情况，参与构成前缀及不参与构成前缀和直接往后塞,有了这两种情况，便可以推出方程：

当 $j>tlen $  或  $  s_{i}=t_{j}$ 时：

### $dp_{j,i+j-1} = dp_{j,i+j-1}+dp_{j+1,i+j-1}$

当 $i+j-1>tlen$ 或 $s_{i}=t_{i+j-1}$ 时：

### $dp_{j,i+j-1}=dp_{j,i+j-1}+dp_{j,i+j-2}$

最后把所有方案加起来，结束！

还有就是别忘了取模！！！（~~为什么题目翻译没翻译啊喂~~）

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[3005][3005];
char a[10005];
char b[10005];
const int MOD=998244353;
main(){
	scanf("%s%s",a+1,b+1);
	for(int i=1;i<=strlen(b+1);i++){
		if(b[i]==a[1]){
			dp[i][i]=2;
		}
	}
	for(int i=strlen(b+1)+1;i<=strlen(a+1);i++){
		dp[i][i]=2;
	}
	for(int i=2;i<=strlen(a+1);i++){
		for(int j=1;j+i-1<=strlen(a+1);j++){
			int r=i+j-1;
			if(j>strlen(b+1) or a[i]==b[j]){
				dp[j][r]=(dp[j][r]+dp[j+1][r])%MOD;
			}
			if(r>strlen(b+1) or a[i]==b[r]){
				dp[j][r]=(dp[j][r]+dp[j][r-1])%MOD;
			}
		}
	}
	int sum=0;
	for(int i=strlen(b+1);i<=strlen(a+1);i++){
		sum+=dp[1][i];
		sum%=MOD;
	}
	cout<<sum%MOD;
	return 0;
} 
```


---

## 作者：Liuxizai (赞：0)

## Description

给定一个字符串 $S$ 和一个字符串 $T$，每次操作可以删掉 $S$ 的第一个字符，然后放到一个初始为空的字符串 $A$ 的首部或尾部，你可以进行任意次操作，求有多少种不同的方法使得 $T$ 是 $A$ 的前缀。

$|T|\le|S|\le3000$

## Solution

先考虑 $|S|=|T|$ 的情况。

设 $f_{i,j}$ 表示用 $S$ 的前 $j-i+1$ 位构造出 $T_{i\dots j}$ 的方案数。

不难得到转移方程：
$$
f_{i,j}=[S_{j-i+1}=T_i]f_{i+1,j}+[S_{j-i+1}=T_j]f_{i,j-1}
$$
初始化：
$$
f_{i,i}=[S_1=T_i]2
$$
区间 dp 即可。

如果 $|S|>|T|$，那么对于最后构造出来的 $A$，$(|T|,|A|]$ 这些位是什么我们并不关心，也就是说，我们实际上可以将 $T$ 的长度补至与 $S$ 等长，补充的这些位能够与任意字符匹配。

答案即为 $\sum_{i=|T|}^{|S|}f_{1,i}$。

## Code

```cpp
namespace Main{
    const int MOD = 998244353;
    const int L = 3005;
    int ls, lt, ans, f[L][L];
    char s[L], t[L];
    void Main(){
        scanf("%s%s", s + 1, t + 1);
        ls = strlen(s + 1), lt = strlen(t + 1);
        for(ri i = 1; i <= lt; i++) if(s[1] == t[i]) f[i][i] = 2;
        for(ri i = lt + 1; i <= ls; i++) f[i][i] = 2;
        for(ri len = 2; len <= ls; len++){
            for(ri i = 1; i + len - 1 <= ls; i++){
                ri j = i + len - 1;
                if(i > lt || s[len] == t[i]) f[i][j] += f[i+1][j];
                if(j > lt || s[len] == t[j]) f[i][j] += f[i][j-1];
                f[i][j] %= MOD;
            }
        }
        for(ri i = lt; i <= ls; i++) ans = (ans + f[1][i]) % MOD;
        write(ans);
        return;
    }
} // namespace
```

---

## 作者：xixiup (赞：0)

## 更新日志

2020.11.1 感谢 @syzf2222 提出状态转移方程的错误

## 题目大意

给一个串 $S$，串 $T$ 与空串 $A$，长度分别为 $n$ 和 $m$，你可以操作若干次，每一次操作你可以将 $S$ 的第一个字母删除并加入 $A$ 的前面或后面，求有多少种方法使得 $T$ 是 $A$ 的前缀。

## 思路分享

由于你可以往两边加入字母，所以我们可以考虑区间$DP$。

我们可以设 $dp_{i,j}$，$l=j-i+1$，$dp_{i,j}$ 表示将 $S_{1 \cdots l}$ 操作为 $A_{i \cdots j}$ 的方法数。

然后我们就可以得到式子：
$$
dp_{i,j}=dp_{i+1,j}*(i>m|s_{j-i+1}=t_i)+dp_{i,j-1}*(j>m|s_{j-i+1}=t_j)
$$
所以我们就可以 $\Theta(n^2)$ 求出 $dp$。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3010,Mod=998244353;
string s,t;
int n,m,dp[3010][3010];
int main(){
	cin>>s>>t;
	n=s.size();m=t.size();
	for(int i=1;i<=m;i++){//赋初始值
		if(s[0]==t[i-1]){
			dp[i][i]=2;
		}
	}
	for(int i=m+1;i<=n;i++){
		dp[i][i]=2;
	}
	for(int l=2;l<=n;l++){//求dp
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			if(j>m||s[l-1]==t[j-1]){
				dp[i][j]+=dp[i][j-1];
				dp[i][j]%=Mod;
			}
			if(i>m||s[l-1]==t[i-1]){
				dp[i][j]+=dp[i+1][j];
				dp[i][j]%=Mod;
			}
		}
	}
	int sum=0;
	for(int i=m;i<=n;i++){//统计答案
		sum+=dp[1][i];
		sum%=Mod;
	}
	printf("%d",sum);
	return 0;
}
```


---

