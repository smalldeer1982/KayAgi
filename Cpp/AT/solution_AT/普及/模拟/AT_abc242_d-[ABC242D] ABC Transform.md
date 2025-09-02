# [ABC242D] ABC Transform

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc242/tasks/abc242_d

`A`, `B`, `C` のみからなる文字列 $ S $ が与えられます。

$ S^{(0)}:=S $ とし、$ i=1,2,3,\ldots $ について $ S^{(i)} $ を $ S^{(i-1)} $ の各文字を `A` → `BC`, `B` → `CA`, `C` → `AB` と同時に置き換えたものと定義します。

以下の $ Q $ 個のクエリに答えてください。$ i $ 個目のクエリの内容は以下の通りです。

- $ S^{(t_i)} $ の先頭から $ k_i $ 文字目を出力せよ。

## 说明/提示

### 制約

- $ S $ は `A`, `B`, `C` のみからなる長さ $ 1 $ 以上 $ 10^5 $ 以下の文字列
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 0\ \leq\ t_i\ \leq\ 10^{18} $
- $ 1\ \leq\ k_i\ \leq\ \min(10^{18},\ S^{(t_i)} $ の長さ$ ) $
- $ Q,\ t_i,\ k_i $ は整数

### Sample Explanation 1

$ S^{(0)}= $`ABC`, $ S^{(1)}= $`BCCAAB` です。 よって各クエリへの答えは順に `A`, `B`, `C`, `B` となります。

## 样例 #1

### 输入

```
ABC
4
0 1
1 1
1 3
1 6```

### 输出

```
A
B
C
B```

## 样例 #2

### 输入

```
CBBAACCCCC
5
57530144230160008 659279164847814847
29622990657296329 861239705300265164
509705228051901259 994708708957785197
176678501072691541 655134104344481648
827291290937314275 407121144297426665```

### 输出

```
A
A
C
A
A```

# 题解

## 作者：Frank_G (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc242_d)

这道题是一个递归的好题。

# 逐步分析

## 部分一

### 理解题意

不难读懂这道题的题意，但如果纯靠题干所展示出的信息，代码将会非常复杂，因为将 $\text{A,B,C}$ 三个字符进行互相转化需要进行很多的判断，这样的话代码会写的很复杂且出现问题一改就是一大段。

### 解决

要想解决这个问题，关键就在于合理的利用余数，考虑到  $\text{A,B,C}$  是三个在   ASCII 码表中连续的字符，不妨利用它们**除以 $3$ 的余数**来解题，这一点在我的代码中多有体现。

**例如:**

```cpp
for(int i=0;i<s.size();i++)
{
	a[i+1]=s[i]-'A';
}
```

## 部分二

### 整体思路

当第一眼看到题目的时候，像我这种蒟蒻想到的是模拟，但是之后看了数据范围后发现模拟的时间复杂度和空间复杂度都会超过很多，于是我们考虑递归处理问题。

注意到 $\text{k}$ 值再大也不会超过 $10^{18}$，所以可以用二分的思路进行处理，这样的话单个的时间复杂度不会超过 $O(\log n)$，可以过。

## 部分三

### 代码实现

这一部分在代码中表现为：

```cpp
ll f(ll t,ll k){
	if(t==0) return a[k];
	if(k==1) return (a[1]+t%3)%3;
	return k&1 ? (f(t-1,(k+1)/2)+1)%3 : (f(t-1,(k+1)/2)+2)%3;
}
```

## 考虑特殊情况（递归边界）

### 当 $t=0$ 时

直接返回 $a_k$ 即可。

### 当 $k=1$ 时

因为 $t$ 可能达到 $10^{18}$，所以只单单靠 $t=0$ 这一个递归边界是很有可能 TLE 的。

又注意到 $k$ 不会超过 $10^{18}$，所以可以拿 $k$ 来做文章。

**具体操作就是特判 $k=1$ 的情况，以此来避免 $t$ 过大而导致  TLE。**

注意到，在余数下，用 $\text{BC}$ 代替 $\text{A}$，用 $\text{CA}$ 代替 $\text{B}$，用 $\text{AB}$ 代替 $\text{C}$，相当于用 $j+1$ 和 $j+2$ 代替 $j$。而我们这里只考虑 $k=1$ 的情况，所以每一次的 $t$ 都相当于让第一个字符加 $1$，所以代码里有：

```cpp
if(k==1) return (a[1]+t%3)%3;
```

## 考虑一般情况

可以发现第 $j$ 位经过一次变化可以变为第 $2\times j+1$ 位和第 $2\times j+2$ 位。相反地，第 $j$ 位由上一次变化的第 $\lfloor \frac{j-1}{2} \rfloor$ 位得到。

此时再考虑奇偶：显然，如果 $j$ 是奇数，那么前者就比后者大 $1$，否则就比后者大 $2$。

所以有：

```cpp
return k&1 ? (f(t-1,(k+1)/2)+1)%3 : (f(t-1,(k+1)/2)+2)%3;
```

最终的时间复杂度为：$O(∑\min(t_i,\log k_i))$。



# 献上代码

```cpp
#include <bits/stdc++.h> //万能头
#define ll long long
using namespace std;
int q;
ll t,k; //十年OI一场空，不开longlong见祖宗
int a[1000001]; //a[i]存储s的相关信息
string s;
ll f(ll t,ll k){
	if(t==0) return a[k];
	if(k==1) return (a[1]+t%3)%3;
	return k&1 ? (f(t-1,(k+1)/2)+1)%3 : (f(t-1,(k+1)/2)+2)%3;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	cin >> q;
	for(int i=0;i<s.size();i++){
		a[i+1]=s[i]-'A'; //将字符串s转化为整型数组a
	}
	while(q--){
		cin >> t >> k; //基本的输入
		cout << (char)(f(t,k)%3+'A') <<endl; //输出答案
	}
	return 0;
}
```

然后你就可以像我一样 AC 啦。

![AC](https://ts1.cn.mm.bing.net/th/id/R-C.6265136af2fb6d1696153c0628133f58?rik=9DH74ME1a7B2bQ&riu=http%3a%2f%2fa2.qpic.cn%2fpsb%3f%2fV12Nr9Jd3RiGAO%2f2Gpg2BrIG8eM09hEcxA8*n*6lSoWRGXlt4rCfh9Eo9c!%2fb%2fdLkAAAAAAAAA%26ek%3d1%26kp%3d1%26pt%3d0%26bo%3d9AGWAQAAAAADN3A!%26tl%3d1%26vuin%3d2080788523%26tm%3d1556971200%26sce%3d60-2-2%26rf%3dviewer_4&ehk=EeDV0jeq6Oo%2bl08RRaUSjf2Vr6u7pzniYE78gi%2fc46Q%3d&risl=&pid=ImgRaw&r=0)

**声明+提醒：一定要自己写一遍，否则你不知道你有哪里还没明白！！！**

---

## 作者：Harrylzh (赞：4)

可以这样思考一次操作：把原字符串每个字符“加一”和每个字符串“加二”交叉在一起。就是这样：

$\texttt{ABC}\rightarrow \texttt{B\ \ C\ \ A}$

$\texttt{ABC}\rightarrow \texttt{\ \ C\ \ A\ \ B}$

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \downarrow$

$\ \ \ \ \ \ \ \ \ \ \ \ \ \texttt{BCCAAB}$

所以，此时位置在奇数位的是“加一”得到的，偶数位的是“加二”得到的。所以，考虑用要求的位置逆推每一次是“加一”还是“加二”，再计算总和得到答案。

~~极简~~代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int q;
int main()
{
    cin>>s>>q;
    while(q--)
    {
        long long t,k,a,b;//a表示在原来的第几个字符，b表示是该字符生成的字符串的第几位
        cin>>t>>k;
        if(t>60) a=0,b=k-1;//如果每个字符生成的字符串长度超过了long long范围，则要求的一定是原来的第一个字符生成的
        else a=(k-1)/(1ll<<t),b=(k-1)%(1ll<<t);
        long long ch=(s[a]-'A'+t)%3;//先统一“加一”,ch计算结果，用0,1,2表示A,B,C
        for(long long i=b;i>0;i-=(i&-i)) ch=(ch+1)%3;//要“加二”的再加一
        cout<<(char)(ch+'A')<<endl;
    }
    return 0;
}
```

---

## 作者：Kylin_ZHH (赞：4)

# ABC242D题解
设 $f(t,k)$ 为“返回 $s^{(t)}$ 的第 $k$ 个字符的函数”。首先，

$f(t,k)$ 是 $S$ 的第 $k$ 个字符。
 
 接下来，我们考虑 $k=0$ 的情况。仔细观察，我们可以看到 $S^{(0)}$，$S^{(1)}$，$S^{(2)}$，$S^{(3)}$，$S^{(4)}$ 的第 0 个字符。
 
要么是

- A，B，C，A，B$\dots$

- B，C，A，B，C$\dots$

- C，A，B，C，A$\dots$

这明显是有规律的呀！

如果 $A$ 的后继字符定义为 $B$，$B$ 是 $C$，$C$ 是 $A$，则 $S^{(t)}$ 的
第 $0$ 个字符是 $S^{(0)}$

第一个字符的第 $t$ 个后继字符。因此，当 $k=0$ 时，$f(t,k)$ 是 $S_{0}$ 的第 $k$ 个后继者。

最后，让我们考虑一下 $f(t,k)$ 在 $0<t,k$ 时返回什么。


再仔细看看，我们可以轻松的得到

- 当 $k$ 为偶数时，$f(t,k)$ 是 $f(t-1,\frac{k}{2})$ 的第一个后继者;

- 当 $k$ 为奇数时，$f(t,k)$ 是 $f(t-1,\frac{k}{2})$ 的第二个后继者。

因此，对于 $0<t,k$，我们可以根据 $f(t-1,\lfloor\frac{k}{2}\rfloor)$ 的值递归得到 $f(t,k)$。

因此，$f(t,k)$ 是

- 如果 $t=0$，则为 $S$ 的第 $k$ 个字符。

- 如果 $k=0$，则为 $S_{0}$ 的第 $k$ 个后继者。

- 如果 $t=0$，则 $f(t-1,\frac{k}{2})$ 的后继者（$k$ 的余数乘以 $2$，加上 $1$）。

然后就可以看代码了：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int q;
    cin >> q;
    while (q--) {
        ll t, k;
        cin >> t >> k;
        k--;
 
        ll i = 0;
        if (t < 60) {
            i = k >> t;
            k -= i << t;
        }
        int r = t % 3;
        for (int j = 60 - 1; j >= 0; j--) {
            ll m = 1LL << j;
            if (k & m) {
                k ^= m;
                r += 1;
            }
        }
 
        char c = (r + s[i] - 'A') % 3 + 'A';
        cout << c << '\n';
    }
 
    return 0;
}
```



---

## 作者：wangzikang (赞：3)

一个较水的题。

考虑一下递归求值。

我们先来看看递归返回条件。

当 $t=0$ 时，显然这个东西就是原数组。

看完递归条件，再来想递归过程。

我们先把 $s$ 中所有的 A 变成 0，所有的 B 变成 1，所有的 C 变成 2，方便我们操作。

显然，$s_i$ 的第 $j$ 位可以控制 $s_i+1$ 的第 $2 \cdot j - 1$ 和第 $2 \cdot j$ 的值。

将它反过来呢？

那就是 $s_i$ 的第 $j$ 位依靠 $s_{i-1}$ 的第 $\lfloor\frac{j+1}{2}\rfloor$ 位生成。

显然，如果 $j$ 是奇数，那么 前者就比后者大一，否则就比后者大二。

由于只有 3 个字母，所以需要对 3 取模。

但 $t$ 很大，怎么办呢？

当 $k=1$ 时，显然每一次操作都是在取下一个数模三的值，所以这部分我们可以 $O(1)$ 做！

单次查询时间复杂度 $O(\min(t,\log k))$。

输出记得转 char。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s[100001];//0A
int sovle(int t,int k){
	if(k==1){
		return (s[1]+t%3)%3;
	}
	if(t==0)return s[k];
	int p=sovle(t-1,(k+1)>>1);
	if(k&1)return(p+1)%3;
	return(p+2)%3;
}
signed main(){ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	string a;
	cin>>a;
	const int LLL=a.length();
	for(int i=0;i!=LLL;++i){
		s[i+1]=a[i]-'A';
	}
	int q;
	cin>>q;
	while(q--){
		int t,k;
		cin>>t>>k;
		cout<<char(sovle(t,k)+'A')<<'\n';
	}
	return 0; 
} 
```


---

## 作者：Dreamerly (赞：3)

## 题目：[AT_abc242_d](https://www.luogu.com.cn/problem/AT_abc242_d)
## 题意：
给定字符串 $S$,其中只包含 `ABC` 三个字母。 $S_i$ 为 $S_{i-1}$ 经过以下变换而来：将 `A` 替换为 `BC`,将 `B` 替换为 `CA`,将 `C` 替换为 `AB`。

再给 $Q$ 次询问，每次给定一个 $t$ 和 $k$，输出 $S_t$ 的第 $k$ 个字符。
## 思路：
首先，看数据规模，发现从 $t$ 入手不好做，因此从 $k$ 入手。而从 $k$ 入手，又不得不找规律性。

其次，我们不妨模拟一组数据：$S_0=\texttt{ABC}$，$S_1=\texttt{BCCAAB}$，$S_2=\texttt{CAABABBCBCCA}$。观察和理解一下，不难得出**对于当前位置为 $i$ 的字符，经过一次替换后的两个字符的位置一定是 $2\times i-1$ 和 $2\times i$ 这两个位置**。反过来想，对于 $S_t$ 的第 $k$ 个字符，即是由 $S_{t-1}$ 的第 $\frac{k}{2}$ 或 $\frac{k+1}{2}$ 个字符得来，简化一下就是 $\frac{k+1}{2}$。若 $k$ 为奇数，则偏移了 $1$ 个字母；若 $k$ 为偶数，则偏移了 $2$ 个字母。那直接模拟思想即可。

然后，我们发现 $k$ 的规模依然很大。但对于 $S_t$ 的第一个字符，它始终是由 $S_0$ 为首 `ABC` 的循环，因此进一步优化，当 $k=1$ 时就可以 $O\left(1\right)$ 解决。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
}
char s[100010];
char dfs(int k,int t){
	if(!t) return s[k];//若t为0，则为原串 
	int tmp;
	if(k==1){//k为1时，有ABC的规律 
		tmp=(s[1]-'A'+t%3)%3;
		return 'A'+tmp;
	}
	char ch=dfs((k+1)>>1,t-1);
	if(k&1) tmp=(ch-'A'+1)%3;
	else    tmp=(ch-'A'+2)%3;
	return 'A'+tmp;
}
signed main(){
	scanf("%s",s+1);//地址偏移，从下标1存入 
	int Q=read();
	while(Q--){
		int t=read(),k=read();
		printf("%c\n",dfs(k,t)); 
	}
	return 0;
} 
```


---

## 作者：cjh20090318 (赞：3)

很巧妙的一道题。

## 题意

给定一个字符串 $S$，只包含字符 `A`，`B`，`C`。

每过一个时刻，字符会发生变化：`A`$\to$`BC`，`B`$\to$`CA`，`C`$\to$`AB`。

设 $0$ 时刻为 $S_0=S$。

进行 $Q$ 次询问，每次询问时刻 $t$ 时，字符串 $S_t$ 中第 $k$ 个字符。

## 分析

为了方便处理，我这里将所有下标减一。

经过观察可以得出，$t \ (t>0)$ 时刻的第 $k$ 个字符，一定是由 $t-1$ 时刻的第 $\left\lfloor\dfrac k 2\right\rfloor$ 个字符变化而来的。

如果 $k \bmod 2 = 0$ 则是变化后的第一个字符，否则是第二个。

此时就可以倒推出 $0$ 时刻对应的字符，再返回得到答案。

但是发现这样一个递归求解的复杂度是 $O(t)$ 的，无法接受。

$\log_2 k + 1$ 次操作后 $k=0$ 且不会再变，此时构成了一个 `ABC` 的循环节。

单次询问时间复杂度 $O(\min(t,\log_2 k))$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define MAXN 100005
using namespace std;
typedef long long LL;
char s[MAXN];
const char T[3][3]={"BC","CA","AB"};//打表每种字符对应的情况，避免大量的分类讨论。
char dfs(const LL&t,const LL&k){return k?(t?T[dfs(t-1,k>>1)-'A'][k&1]:s[k]):(s[0]-'A'+t%3)%3+'A';}//k=0 不再变化时，直接由循环节得出，否则如果 t=0 返回第 k 位字符，否则获取上个时刻的字符。
int main(){
	int q;
	scanf("%s %d",s,&q);
	for(LL t,k;q--;) scanf("%lld%lld",&t,&k),putchar(dfs(t,k-1)),putchar('\n');//因为下标减一，所以查询的时候也要减一。
	return 0;
}
```

---

## 作者：IGpig (赞：1)

## ABC242D
### Problem
给定一个字符串 $S$。

设 $S_0=S$，令 $S_i$ 是同时替换 $S_{i-1}$ 中字符的结果，替换规则如下：$A\rightarrow BC$，$B\rightarrow CA$，$C\rightarrow AB$。

查询如下：打印 $S_t$ 的第 $k$ 个字符。

### Solution
这个 $10^{18}$ 的数据范围，我们考虑分治。\
定义 $\operatorname{dfs}(t,k)$ 表示 $S_t$ 的第 $k$ 个字符。
那么很明显有：
$$t=0\Longrightarrow s_k$$
$$k=0\Longrightarrow\space (s_1+t \bmod{3})\bmod{3}$$
然后考虑转移，因为每一次替换第 $k$ 的位置会映射到 $k\times{2}$，$k\times{2}+1$。\
所以有:
$$\operatorname{dfs}(t,k)\Longrightarrow \operatorname{dfs}(t-1,(k+1)\div{2}+1+(k\bmod{2}))$$

### Code
~~~cpp
#include<bits/stdc++.h>
using LL=long long;
using namespace std;
LL q,t,k,n;
string s;
LL dfs(LL t,LL k){
	if(t==0) return s[k]-'A';
	if(k==1) return (s[1]-'A'+t%3)%3;
    return (dfs(t-1,(k+1)/2)+1+(k%2))%3;
}
int main(){
	cin>>s;
    n=s.size();
	cin>>q;
	while(q--){
		cin >> t >> k; 
		cout << char(dfs(t,k)%3+'A') <<endl; 
	}
	return 0;
}
~~~

---

## 作者：DragonForge (赞：1)

## AT_abc242_d [ABC242D] ABC Transform
注：本题解参考 [@maziming](https://www.luogu.com.cn/user/1271739) 的代码与思路，这里再做详细解释。

这是一道递推题，~~我的老师说还可以用分治做~~。由于 `A` `B` `C` 之间不好互相转换，我采用三者间 ASCLL 码相连的性质，用数字转换。注意，最后输出不能只输出一个数字！

根据变换规则，以 `A` 为例。变化一次变成 `BC`，再变变成 `CAAB`，接着是 `ABBCBCCA` ，`BCCACAABCAABABBC`……其实这样下去一点规律也没有，但是聪明的同学已经发现，变化后，第 $2i$ 和 $2i + 1$ 项是由原数组的第 $i$ 项变成的，而且分别是第 $i$ 项数值加一模 3 和加二模 3。此时这道题递推起来就轻松了。

放一下代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

using LL=long long;
LL q,t,k,l;
string s;

int main(){
	cin>>s;
	for(cin>>q;q--;){
		cin>>t>>k;
		k--;
		LL whr=0;
		if(t<60){
			whr=k>>t;
			k-=whr<<t;
		}
		l=t%3;
		for(int j=59;j>=0;j--){
			LL m=1ll<<j;
			if(k&m){
				k^=m,l+=1;
			}
		}
		char ans=(l+s[whr]-'A')%3+'A';
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：maziming (赞：1)

## 题意：
每一次操作可以这样理解：

假设一个字符串 `ABC`。

|原单词|奇数位|偶数位|
|:-:|:-:|:-|
| $A$ | $B$ | $C$ |
| $B$ | $C$ | $A$ |
| $C$ | $A$ | $B$ |

`ABC` 变成：`BCCAAB`

所以，此时位置在奇数位的是“加一”得到的，偶数位的是“加二”得到的。所以，考虑用要求的位置逆推每一次是“加一”还是“加二”，再计算总和得到答案。

代码自己理解哈。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll q,t,k,l;
string s;
int main()
{
	cin>>s>>q;
	while(q--)
	{
		cin>>t>>k;
		k--;
		ll i=0;
		if(t<60)i=k>>t,k-=i<<t;
		l=t%3;
		for(int j=59;j>=0;j--)
		{
			ll m=1LL<<j;//一定要用1LL，不然会错！！！
			if(k&m)k^=m,l+=1;
		}
		cout<<char((l+s[i]-'A')%3+'A')<<endl;
	}
	return 0;
}
```

---

## 作者：Kawaii_qiuw (赞：1)

### 解题思路

首先第 $0$ 层是给定的字符串，然后，第 $t$ 层可以看做是 $t$ 个 $t$ 层的完全二叉树，这样的话，最后一层的最大编号数为 $n \times 2^t$，最大达到了 $10^5 \times 2^{(10^{18})}$，一个巨大的数字。但是显然给定的k范围没有这么大，所以要从 $k$ 下手。

首先如果考虑朴素做法，从树底部往上一步一步走，是 $O(t)$ 解法，过不了，但是可以通过 $k$ 来剪枝，当 $t$ 比较大的时候，$k$ 每次找父亲的时候会变成 $(k+1)/2$，最多 $64$ 次左右变成 $1$，也就是第一个二叉树的最左边一列，容易发现最左边一列是有规律的，假如最左边字母是 ```A```，那么最左边一列是 ```ABCABCAB........```，此时 $O(1)$ 地给出结果即可。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define debug cout<<"!!!"<<endl;
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
const int N = 1e5+5;
char s[N]; int q,t,k;
 
char ask(int t,int k){
    if(t==0) return s[k]; //已经到第一层了
    if(k==1) return 'A'+(s[1]-'A'+t)%3; //到达最左边一列
    else return 'A'+(ask(t-1,(k+1)/2)-'A'+(!(k%2)+1))%3; //k为奇数，相对父亲+1，否则相对父亲+2，然后对3取余
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin>>(s+1)>>q;
    For(i,1,q){
        cin>>t>>k;
        cout<<ask(t,k)<<'\n';
    }
}
```

[AC记录。](https://www.luogu.com.cn/record/197105880)

完结撒花。

---

## 作者：TainityAnle (赞：1)

### 题目翻译

给您一个字符串，由 `A`，`B`，`C` 构成，每一次操作把 `A` 变成 `BC`，`B` 变成 `CA`,`C` 变成 `AB`。

$Q$ 次询问，每次有 $t_i$ 和 $k_i$，求经过 $t_i$ 次操作后的第 $k_i$ 个字符是什么（从 $1$ 开始）。

### 思路

首先，模拟肯定是过不了的，正难则反，我们就可以考虑从 $S^{(t_i)}$ 开始倒推。

对于 $S^{(t_i)}_i$，有两种情况，要么是当 $i$ 为偶数时从 $S^{(t_i-1)}_{i/2}$ 转移过来，要么是当 $i$ 为奇数时从 $S^{(t_i-1)}_{(i+1)/2}$ 转移过来。

这就很像一个 DP，但是是逆向的，这样就可以递归解决。当我们递归到 $t$ 为 $0$ 的时候，看我们的 $k$ 回到哪里就可以了。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s[100005];
int T,k,t;
int solve(int t,int k) {
	if(t==0) return s[k];
	int ans=0;
	if(k==1) {
		ans=(s[1]-'A'+t%3)%3;
		return 'A'+ans;
	}
	char tmp=solve(t-1,(k+1)/2);
	if(k%2) ans=(tmp-'A'+1)%3;
	else ans=(tmp-'A'+2)%3;
	return ans+'A';
}
signed main() {
	cin>>s+1;
	cin>>T;
	while(T--) {
		cin>>t>>k;
		cout<<(char)solve(t,k)<<endl;
	}
	return 0;
}
```

---

## 作者：tsh_qwq (赞：1)

### 大致题意：
有一个字符串，每次操作会将 A 改为 BC，B 改为 AC，C 改为 AB。  
然后我们就可以发现，**这怎么像个二叉树呢？**    
![](https://cdn.luogu.com.cn/upload/image_hosting/iqwld53g.png)   
现在我们要做的就是，根据输入的 $t_i$ 与 $k_i$ 求出其根节点，再逆着求一次。  
还有一个非常重要的点，就是因为数据范围是 $k_i \le  10 ^ {18} $，所以要加特判。

### 代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("3","Ofast","inline")
#define int long long
#define endl "\n"
using namespace std;
string s;
int q,a,b,x,y;
signed main()
{
	//log(1e18)=59.7947
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	cin>>q;
	for(int i=0;i<(int)s.length();i++)s[i]-='A';
	while(q--)
	{
		cin>>x>>y;
		if(x>60)
		{
			a=0;
			b=y-1;
		}
		else
		{
			a=(y-1)/(1ll<<x);
			b=(y-1)%(1ll<<x);
		}
		int c=(s[a]+x)%3;
		for(int i=b;i>0;i-=(i&-i))
		{
			c++;
			c%=3;
		}
		cout<<(char)(c+'A')<<endl;
	}
	return 0;
}
```

---

## 作者：VelvetChords (赞：1)

# AT_abc242_d [ABC242D] ABC Transform
## 0.前言
核心是如何高效地通过递归关系计算一个字符串 $s^{(t)}$ 中某个位置的字符，而不需要显式地构建整个字符串。

## 1.思路
字符串 $s^{(t)}$ 通过递归的方式构建，每个 $s^{(t)}$ 都由前一个字符串 $s^{(t-1)}$ 及其前后继字符构成。

假设，字符串的构建规则如下：

$s^{(0)}$ 是初始字符串。

对于 $t > 0$，$s^{(t)}$ 可以由 $s^{(t-1)}$ 变换得到。

这个变换的本质是字符的后继关系，也就是说，每个字符 $A, B, C$ 都有一个确定的后继字符。例如：

- $A$ 的后继是 $B$

- $B$ 的后继是 $C$

- $C$ 的后继是 $A$

由于字符的后继关系是周期性的（每三个字符形成一个周期：$A → B → C → A$），我们可以发现，字符的变化实际上是周期性的。对于某个位置 $k$ 的字符，我们只需要考虑其所处的周期层次，而不需要考虑整个字符串 $s^{(t)}$。

代码通过位操作来快速计算某个位置 k 在 $s^{(t)}$ 中对应的字符。

代码过于简单，不再给出。

---

## 作者：Gaochenxi103_QWQ (赞：0)

## 第一步

因为发现每个字符进过一次变化会变成两个其他的字符。\
而那两个字符又会各自分成另外两个字符。\
所以我们发现，这类似一个二叉树的每一层。

像这样。
```
    A
   / \
  B   C
 /\   /\
C  A A  B
```

而且我们发现对于变化。
```
 A->B = A+1
 A->C = A+2

 B->C = B+1
 B->A = (B+2)%3

 C->A = (C+1)%3
 C->B = (C+2)%3
```

假设 ABC 是一个循环，左子树就是 $+1$，右子树就是 $+2$。\
超出 ABC 之后就是进入下一个循环。

我们就可以将 $A$ 设为 $0$，$B$ 设为 $1$，$C$ 设为 $2$。


## 第二步

我们发现确定 $S^{t}$ 的第 $k$ 项的难点在于。\
**注：下文将 $S^{t}$ 的第 $k$ 项表述为目标。**

  1. 我们知道目标一定是从一个字符变换过来的，所以要想知道目标是多少，就需要找到起始的字符。

2. 怎么操作得到最后的值。

3. 我们发现变换次数 $t$ 的值很大，所以我们肯定不能直接模拟转换。

### 解决方案

1. 我们发现在变换之后，应该会出现最开始的字符个数个深度为t二叉树，也就是现在的字符串有 $n\times 2^t$ 个字符，所以我们可以一直循环去找是第几个二叉树。

```cpp
    int root=1;
    while(k>2^t)
    {
        k-=2^t;
        root++;
    }
```

2. 我们发现要求目标，那么就模拟一下二叉数（左 $+1$，右 $+2$）如果他大于 $2^{t'-1}$ 说明它是往左走，反之往右。

```
   还是这个树 t=2
     0
    / \
   1   2
  /\   /\
 2  0 0  1
 假设 k为3

 因为k>2^(2-1)，所以往右走并且 k-=2^(2-1) t-=1
     0
    / \
   -   2
  /\   /\
 -  - -  -

 因为k<=2^(1-1)，所以往左走并且 t-=1
     0
    / \
   -   2
  /\   /\
 -  - 0  -

 因为 t=0 所以结束输出 0(就是A)
```

代码演示如下。

```cpp
    int now=root;
    while(t>0)
    {
        if(k>2^(t-1))
        {
            k-=2^(2-1),t-=1;
            root+=2;
        }
        else
        {
            t-=1;
            root+=1;
        }
        root%=3;
    }    
```

3. 我们发现 $k$ 小于等于 $10^{18}$。而一个二叉树的深度为 $60$ 时，他最后一层的数比 $10^{18}$ 大。就是当 $t>59$ 时，这个查询的值一定是在第一个字符所变换的二叉树之中，当 $t<60$ 直接模拟（详细见 $2$）。


## 第三步

当 $t>59$ 时，说明目标在 $1$（就是第一个字母的变换）中。\
并且在 $t-60$ 的部分一定是往左走的，因为如果往右走一步，那么最后最小到的位置也是比 $10^{18}$ 大的，（$2^{60}+1>10^{18}$）。

所以代码出来如下。

```cpp
    int now=root;
    if(t>60)
    {
        now+=t-60;
        now%=3;
        t=60;
    }
    //下面的一样
    while(t>0)
    {
        if(k>2^(t-1))
        {
            k-=2^(2-1),t-=1;
            root+=2;
        }
        else
        {
            t-=1;
            root+=1;
        }
        root%=3;
    }    
```

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long T,t,k;
int main()
{
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    cin>>s>>T;
    while(T--)
    {
        cin>>t>>k;
        long long root=1;

        if(t<60)//找根
        {
            long long cnt=pow(2,t);
            while(k>cnt)
            {
                k-=cnt,root++;
            }
        }

        long long now= (long long)(s[root-1]-'A');
        
        if(t>60)
        {
            now+=t-60;
            now%=3;
            t=60;
        }

        while(t>0)
        {
            long long cnt=pow(2,t-1);
            if(k>cnt)
            {
                k-=cnt,t-=1;
                now+=2;
            }
            else
            {
                t-=1;
                now+=1;
            }
            now%=3;
            // cout<<cnt<<" "<<now<<"\n";
        }
        cout<<char('A'+now)<<"\n";
    }
}


```

---

## 作者：zyc418 (赞：0)

# D - ABC Transform
[题目](https://atcoder.jp/contests/abc242/tasks/abc242_d)

我们不难发现，它每次分裂出两个节点，这是啥，二叉树啊，请看图：
![](https://cdn.luogu.com.cn/upload/image_hosting/uq13mj8o.png)

所以我们只需用一个变量统计一下单复数，左根加 $1$ 右根加 $2$，即：
$$
sum = sum + \begin{cases}
1 & k \equiv 1 \pmod 2\\
2 & k \equiv 0 \pmod 2
\end{cases}
$$

注意，如果 $60 \le t$ 那么数肯定大于 $10^{18}$。
# D - Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
const ll N=1e6+5;
ll q;
string s;
char ans;
int main() {
    cin>>s>>q;
    while(q--) {
        ll k,t;
        cin>>t>>k;
        ll sum=0;
        while(1) {
            if(!t||k==1) break;
            if(k%2==1) sum++;
            else sum+=2;
            k=(k+1)/2;
            t--;
        }
        if(t) {
            ans=(s[0]-'A'+sum+t)%3+'A';
        }
        else {
            ans=(s[k-1]-'A'+sum)%3+'A';
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：cwxcplh (赞：0)

~~其实这道题还是挺简单的。~~

怎么说呢，看到这道题的后我瞬间就想到了分治和二叉树（主要是因为一个字母可以分成两个字母），于是我就写了个 dfs，但有个问题：题目给的数据范围是 $0\le t_i\le10^{18}$，而写二叉树则是一层一层往上跑，这不就成了 $O(10^{18})$ 了吗？

然后我就看到了这句话：$1\le k_i\le\operatorname{min}(10^{18},t_i)$。这说明一件事：我的层数不可能真的跑到 $10^{18}$ 那么多，在到了某个点后就必然是某个数列的第一个。那我只需要多加一个边界条件就行了。粗略算了一下，大约 $60$ 层的时候就已经超过 $10^{18}$ 了。

然后就可以开始安心的写代码了，首先定义一个 `dfs(x,y,f)` 表示第 $x$ 层的第 $y$ 个是什么，而 $f$ 表示以现在这个节点为根节点，我上一个要求的点是左子树的还是右子树的，为了方便，我在最初是用的 $-1$ 表示我要求的点（相当于没有左子树也没有右子树的点）。

AC 代码（代码中用了大量的三目运算符压行，看不懂三目运算符的同学请先看[这里](https://blog.csdn.net/qq_43003456/article/details/136985040?ops_request_misc=&request_id=&biz_id=102&utm_term=%E4%B8%89%E7%9B%AE%E8%BF%90%E7%AE%97%E7%AC%A6%E6%98%AF%E4%BB%80%E4%B9%88&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-136985040.nonecase&spm=1018.2226.3001.4187)）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q,t,k;
string c;
char dfs(int x,int y,int f)
{
    if(x==0)
    {
        return ((!f)?(c[y]=='A'?'B':(c[y]=='B'?'C':'A')):(c[y]=='A'?'C':(c[y]=='B'?'A':'B')));
    }
    if(y==1)
    {
        if(f==-1)
        {
            return (c[y]+x%3=='D'?'A':(c[y]+x%3=='E'?'B':c[y]+x%3));
        }
        return ((!f)?((c[y]+x%3=='D'?'A':(c[y]+x%3=='E'?'B':c[y]+x%3))=='A'?'B':((c[y]+x%3=='D'?'A':(c[y]+x%3=='E'?'B':c[y]+x%3))=='B'?'C':'A')):((c[y]+x%3=='D'?'A':(c[y]+x%3=='E'?'B':c[y]+x%3))=='A'?'C':((c[y]+x%3=='D'?'A':(c[y]+x%3=='E'?'B':c[y]+x%3))=='B'?'A':'B')));//比较抽象，可以慢慢看……
    }
    char tt=dfs(x-1,(y+1)/2,!(y&1));
    if(f==-1)
    {
        return tt;
    }
    return ((!f)?(tt=='A'?'B':(tt=='B'?'C':'A')):(tt=='A'?'C':(tt=='B'?'A':'B')));
}
signed main()
{
    cin>>c;
    c=' '+c;//把第零位变到第一位
    cin>>q;
    while(q--)
    {
        cin>>t>>k;
        if(t==0)//特判了一下
        {
            cout<<c[k]<<endl;
            continue;
        }
        cout<<dfs(t,k,-1)<<endl;//最初没有左右子树
    }
    return 0;
}
```

---

## 作者：zhou_rui_tong (赞：0)

### 题目大意：

变化 $t$ 次，每次用 $\texttt{BC}$ 代替 $\texttt{A}$ ，用 $\texttt{CA}$ 代替 $\texttt{B}$，用 $\texttt{AB}$ 代替 $\texttt{C}$ 。求第 $k$ 个字符。

不管时间，先上暴力代码，即生成字符串。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string x,z;
ll n,t;
struct qq
{
	ll i,a,k;
	char s;
}a[100005];
bool cmp(qq a,qq b)
{
	return a.a<b.a;
}
bool cmp1(qq a,qq b)
{
	return a.i<b.i;
}
int main()
{
	cin.tie(0);
	cout.tie(0);
	cin>>x>>n;
	for(int i=1;i<=n;i++)
	{
		a[i].i=i;
		cin>>a[i].a>>a[i].k;
	}
	sort(a+1,a+n+1,cmp);//排序是为了优化时间
	for(int i=1;i<=n;i++)
	{
		while(t<a[i].a)
		{
			z="";
			for(int j=0;j<x.size();j++)
			{
				if(x[j]=='A')z+="BC";
				if(x[j]=='B')z+="CA";
				if(x[j]=='C')z+="AB";
			}
			x=z;
			t++;
		}
		a[i].s=x[a[i].k-1];
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)cout<<a[i].s<<"\n";
	return 0;
}
```

可这样的代码必定超时。

这是，我们反过来想，不生成字符串，而是算出第 $t$ 次变化后第 $k$ 个字符是由原字符串的哪一位变化来的。

$t$ 次的第 $k$ 位就是 $t-1$ 次的第 $k/2$ 位；$\tt-1$ 次的第 $k/2$ 位就是 $t-2$ 次的第 $k/4$ 位......。

只要算出 $t-1$ 的第 $k/2$ 位，就可算出 $t$ 的第 $k$ 位。

算法如下：

```cpp
char f[5][3]={{'B','C'},{'C','A'},{'A','B'}};
//ABC每次变化第一为与第二位
char aa(ll a,ll k)
{
	char x=aa(a-1,(k+1)/2);
	x=f[x-65][1-k%2];
	return x;
}
```

但我们发现，$t$ 也是特变大。但 $k$ 每次除以二,变为一速度十分快，在发现 $\texttt{A}$ 变后第一位是 $\texttt{B}$ ， $\texttt{B}$ 变后第一位是 $\texttt{C}$ ， $\texttt{C}$ 变后第一位是 $\texttt{A}$ ......。
这很明显是周期问题，据此，改进算法如下：

```cpp
char f[5][3]={{'B','C'},{'C','A'},{'A','B'}};
char aa(ll a,ll k)
{
	if(a>0&&k!=1)
	{
		char x=aa(a-1,(k+1)/2);
		x=f[x-65][1-k%2];
		return x;
	}
	else if(k==1&&a!=0)
	{
		char z=x[k-1];
		z=(z+a-65)%3+65;
		return z;
	}
	else return x[k-1];//x为原字符串
}
```

现在，只需组合起来。

### 正确代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string x;
ll n,a,k; 
char f[5][3]={{'B','C'},{'C','A'},{'A','B'}};
char aa(ll a,ll k)
{
	if(a>0&&k!=1)
	{
		char x=aa(a-1,(k+1)/2);
		x=f[x-65][1-k%2];
		return x;
	}
	else if(k==1&&a!=0)
	{
		char z=x[k-1];
		z=(z+a-65)%3+65;
		return z;
	}
	else return x[k-1];
}
int main()
{
	cin.tie(0);
	cout.tie(0);
	cin>>x>>n;
	while(n--)
	{
		cin>>a>>k;
		cout<<aa(a,k)<<"\n";
	}
	return 0;
}

```

---

## 作者：Antiluna (赞：0)

貌似是题解区最复杂的做法。

显然可以 $O(t)$ 处理第 $k$ 个字符，但是会 TLE。

但是自己打几组数据观察就会发现当 $t$ 很大时前面的很多位其实符合 `A,B,C,A,B,C,A` 这样的规律，并且仅由第一位影响。于是可以拿一个比较小的数推，我这里对大于 $2^{30}$ 的 $t$ 进行优化。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q,t,k,n;
char s[100010];
int power(int a,int b)
{
	int res=1;
	for(int i=1;i<=b;i++)res*=a;
	return res;
}
signed main()
{
	scanf("%s",s);
	n=strlen(s); 
	scanf("%lld",bitand q);
	while(q--)
	{
		scanf("%lld %lld",bitand t,bitand k);
		int pj=1,tj=0,bj=0,cj=t;
		while(pj<k)pj*=2,tj++;
		if(t>tj&&tj>30)t=tj,bj=1;
		int jb=power(2,t);
		char c=s[signed(ceil(k*1.0/jb))-1];
		if(bj==1)c=s[0];
		while(1)
		{
			if(jb==1)break;
			int sb=k%jb;
			if(sb==0)sb=jb;
			jb/=2;
			//BC CA AB
			if(sb>jb)
			{
				if(c=='A')c='C';
				else if(c=='B')c='A';
				else c='B';
			}
			else
			{
				if(c=='A')c='B';
				else if(c=='B')c='C';
				else c='A';
			}
			k=sb;
		}
		if(bj==0)printf("%c\n",c);
		else
		{
			c+=(cj-t)%3;
			if(c>'C')c-=3;
			printf("%c\n",c);
		}
	}
	return 0;
}
```

---

## 作者：Never_care (赞：0)

### 思路
一道字符串递归的题目。

先想递归的边界如何判断。

1. $t=0$ 时，直接返回原字符串。
2. 介于 $t\ge10^8$，所以只判断 $t=0$ 的边界有可能超时。
3. $k=1$ 时，通过找规律可发现，$t$ 其实就是让字符串的第一个字母加 $1$。

现在判断非特殊情况。

很明显，假设要变化的字符为变量 $x$，当 $x$ 为奇数时即可变化成 $x\times2+1$，为偶数则为 $x\times2+2$。
不要忘了除以三求余。
```cpp
if(x%2==1){
  return f(t-1,(x+1)/2+1)%3;
}
else{
  return f(t-1,(k+1)/2+2)%3;
}
```
代码不贴了。

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

首先我们发现了，对于最终的答案是第 $k$ 位，然而，每次进行一个操作相当于位置会乘 $2$。所以我们可以直接暴力，到了一定地方进行特判即可。直接模拟，从 $k$ 位一直除 $2$，（这是必然的）。然后若 $k = 1$，以后肯定一直就是 $1$ 了。我们又发现，他其实是一个长度为 $3$ 的区间，直接将次数模 $3$。即可。

代码细节有一点多，详见代码。

[link](https://atcoder.jp/contests/abc242/submissions/49421907)。

---

## 作者：Genius_Star (赞：0)

### 思路：

把原序列的每一个字母当成成一个根，可以发现这是一棵 $t$ 层的二叉树。

题目意思是查询第 $t$ 层的第 $k$ 个节点，这样一棵二叉树第 $t$ 层有 $2^t$ 个节点。

显然如果 $t > 60$，节点数目是非常多的，算一下 $2^{60}$ 肯定大于 $10^8$，这样第 $k$ 个节点就一定是从初始序列的第一个字母开始变化的，当 $t$ 始终大于 $60$ 时，每次向下延申肯定选择最左边的节点，这样就会有循环节。

我们模拟一下初始字母对应的循环节，然后就 $s\bmod 3$ 就可以得到 $t = 60$ 的时候的字母，即作为递归求解时的根节点。

如果 $t \le 60$，所查询的节点它就可能不是从初始序列的第一个字母开始变化，应该是从初始序列第 $\lfloor \frac{k}{2^t} \rfloor$ 个开始变化。

这样我们确定出来根节点了。

然后递归模拟拓展的过程求答案就好了。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define ld long double
#define all(x) x.begin(), x.end()
#define mem(x, d) memset(x, d, sizeof(x))
#define eps 1e-6
using namespace std;
const int maxn = 2e6 + 9;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll n, m;
map <char, string> ma, mb;
char ans;

void dfs(int t, char x){
	if(t == 0){
		ans = x;return;
	}
	m %= (1ll << t);
	if(m < (1ll << (t - 1))){
		dfs(t - 1, mb[x][0]);
	}
	else dfs(t - 1, mb[x][1]);
}
void work()
{
	ma['A'] = "ABC";ma['B'] = "BCA";ma['C'] = "CAB";
	mb['A'] = "BC";mb['B'] = "CA";mb['C'] = "AB";
	string s;cin >> s;
	int q;cin >> q;
	while(q--){
		cin >> n >> m;
		--m;
		char x;
		if(n > 60){
			x = ma[s[0]][(n-60)%3];
		}
		else x = s[m/(1ll<<n)];
		n = min(n, 60ll);
		dfs(n, x);
		cout << ans << endl;
	}
}

int main()
{
	ios::sync_with_stdio(0);
//	int TT;cin>>TT;while(TT--)
	work();
	return 0;
}


```


---

## 作者：xiaoPanda (赞：0)

## 题意
给出 $S_0$，只包含 `ABC` 三个字母， $S_i$ 是由 $S_{i-1}$ 经过以下变换形成的：

+ 将字符 `A` 替换成 `BC`，将字符 `B` 替换成 `CA`，将字符 `C` 替换成 `AB`

多测，问 $S_t$ 的第 $k$ 个字符。
## 题解
注意到 $t$ 很大，但 $k$ 相对 $|S_t|$ 又很小，所以可以从 $k$ 入手。

容易发现 $S_i$ 的第 $j$ 个字符是由 $S_{i-1}$ 的第 $\lceil\frac k 2\rceil$ 个字符变成的，所以如果我们知道 $j$ 的奇偶和 $S_{i-1}$ 的第 $\lceil\frac k 2\rceil$ 个字符就可以求出 $S_i$ 的第 $j$ 个字符。

因此我们可以找到 $S_t$ 是由 $S_w$ 的第 $1$ 个字符变成的，并且从 $S_0$ 到 $S_w$ 的第 $1$ 个字符可以直接求出，即 `(ch[1]+w-'A')%3+'A'`。

计算 $S_w$ 时可以顺带着计算当前 $j$ 的奇偶，用数组存一下，然后从 $S_w$ 开始倒推即可：

+ 如果当前 $j$ 为奇数，`A->B B->C C->A`。
+ 如果当前 $j$ 为偶数，`A->C B->A C->B`。

当然还要处理亿点点细节，如果直到 $S_0$ 还没有将 $j$ 变成 $1$ ，那就不用算了，直接带入 $ch_j$。

---

