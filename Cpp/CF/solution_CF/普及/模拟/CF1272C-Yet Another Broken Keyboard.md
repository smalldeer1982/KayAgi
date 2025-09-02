# Yet Another Broken Keyboard

## 题目描述

$Norge$，找到了一个长度为$n$的字符串$s$（$s$仅由小写英文字母构成），他想把这个字符串的所有$\frac{n(n+1)}{2}$个连续非空子串都打出来

可是，他发现他的键盘坏了，只能打出26字母中的$k$个  
这$k$个字母分别为：$c_1,c_2,c_3,\dots ,c_k$

请求出用这个坏掉的键盘，最多能打出多少个字符串$s$的连续非空子串

## 说明/提示

$1\leq n \le 2\cdot 10^5$，$1\leq k \le 26$  
感谢 @_Wolverine 提供的翻译

## 样例 #1

### 输入

```
7 2
abacaba
a b
```

### 输出

```
12
```

## 样例 #2

### 输入

```
10 3
sadfaasdda
f a d
```

### 输出

```
21
```

## 样例 #3

### 输入

```
7 1
aaaaaaa
b
```

### 输出

```
0
```

# 题解

## 作者：Rainbow_qwq (赞：3)

[CF1272C Yet Another Broken Keyboard](https://www.luogu.com.cn/problem/CF1272C)

---

# 思路

来观察一下样例。

$asadfaasdda$，可用字母：$f,a,d$

我们用$\color{red}\text{红色}$标记不可用的字母。如下：

$a$ $\color{red}{s}$ $adfaa$ $\color{red}{s}$ $dda$

发现：整个字符串被不可用的字母分成了几段。

最终符合条件的子串的左右端点一定在一段黑色字母中。

假设一段黑色字母的长度为$len$，那就答案$+=\dfrac{len\times (len+1)}{2}$

如:对于$adfaa$，$len=5$，答案$+=\dfrac{5\times (5+1)}{2}$

那就$O(n)$解决了。

# 代码
放了一些注释。
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,m,res;
char s[200007];
bool can[33];//can[i]:第i个字母能不能用。
signed main()
{
	n=read(),m=read();
	cin>>s;
	For(i,1,m){
		char ch;
		cin>>ch;
		can[ch-'a'+1]=1;//标记掉
	}
	int len=0;
	For(i,0,n-1){
		if(can[s[i]-'a'+1])len++;//是可用的字母就len++
		else{//不是可用的字母
			res+=len*(len+1)/2;//添加到答案
			len=0;//清空掉
		}
	}res+=len*(len+1)/2;
	cout<<res; 
    return 0;
}
```
后记：虽然$1\leq n\leq 2*10^5$，我的一个同学居然暴力$O(n\log^2 n)$过掉了，~~所以数据很水~~

---

## 作者：LITFLYR (赞：1)

# CF1272C — 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF1272C)
### 题意
给你一个长度为 $n$ 的字符串 $s$，再给你 $k$ 个字母，问在这个字符串中，有多少个非空子串仅包含这 $k$ 种字母中的几种。
### 数据范围
$ 1 \le n \le 2\times10^5$，$ 1 \le k \le 26$。
### 基本思路
首先开一个 bool 类型的数组，将字符串 $s$ 中出现的所有在这 $k$ 种字母中的字母标成 true。然后利用循环找到连续的 $x$ 个 true，如果当前为 false，那就将前面连续的 $x$ 个 true 可以构成的非空子串个数加在 $ans$ 上，然后清空 $x$ 继续寻找连续的 true。

为了降低时间复杂度，我们不会用两层循环去计算每处连续 true 可以构成的子串个数，而是使用一个求和公式 $\frac{(n+1)\times n}{2}$。

至于为什么要使用求和公式，以连续三个 true 举例，我们可以构成一个，两个或三个字母构成的子串，共有 $3+2+1=6$ 个，现在可以理解了吧。

有一个特别需要注意的点，如果整个字符串最后一位是 true 的话，需要在出循环后再判一下连续 true 的记录变量是否清空了。如果没有，需要把这个部分的连续 true 最后计算进去。

最后，请大家看一下代码。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,u;
char s[200020];
char can;
bool flag[200020];
long long an,ans;
int main(){
    cin >> n >> u >> s;
    for (int i=0;i<u;i++){
    	cin >> can;
    	for (int j=0;s[j]!='\0';j++){
    		if (s[j]==can) flag[j]=true;//我选择的方法是将这 k 个分别输入，每次都走一遍整个字符串。
		}
	}
	for (int i=0;s[i]!='\0';i++){
		if (flag[i]==true){
			an++;//寻找连续 true。
		}
		else{
			ans=ans+((an+1)*an)/2; //如果连续 true 断了 就计算子串个数
			an=0;
		}
	}
	if (an!=0) ans=ans+((an+1)*an)/2;//判最终连续 true 是否清空。
	cout << ans;
	return 0;
}
```

---

## 作者：BYWYR (赞：1)

## $\texttt{Solution}$

先看一下样例1：

$$\mathbf{abacaba}$$

将打字机不可以打出来的字母删去后，可以得到：

$$\mathbf{aba\|aba}$$  

那么很显然，得到的子序列一共有：

$$ans_1=\frac{(3+1) \times 3}{2}+=\frac{(3+1) \times 3}{2}=12$$

再举个栗子（样例2）：

$$\mathbf{sadfaasdda}$$

将打字机不可以打出来的字母删去后，可以得到：

$$\mathbf{adfaa\|dda}$$

得到的子序列一共有：

$$ans_2=\frac{(5+1) \times 5}{2}+\frac{(3+1) \times 3}{2}=21$$

那么这道题就迎刃而解了。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k;
string s;
char ch[35];
int main(){
	cin>>n>>k;
	cin>>s;
	for(int i=1;i<=k;i++){
		cin>>ch[i];
	}
	ll last=0,ans=0;
   //last表示连续可以打出来几个字母
   //ans表示子序列的个数
	for(int i=0;i<n;i++){
		bool flag=false;
		for(int j=1;j<=k;j++){
			if(s[i]==ch[j]){
				flag=true;
				break;
			}
		}
		if(flag==false){
			ans+=(1+last)*last/2;
			last=0;
		}
		else last++;
	}
	ans+=(1+last)*last/2;
   //最后一个字母若可以打出来要加到子序列的个数里
	cout<<ans;
	return 0;
}
```


---

## 作者：rrrrr (赞：1)

被hk了两次，都失败了$（*_*）$

枚举每一个端点，二分求可以选的子串的最右值。   
状压，用线段树维护包含的值   
时间复杂度  $ O(nlog^2n)$
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[200005],ans=0;char c[200005];
struct abc
{
	int l,r,ans;
}s[200005*4];
void build(int rt,int l,int r)
{
	int mid=(l+r)>>1;
	if(l==r)
	{
		s[rt].ans=a[l];
		s[rt].l=l;
		s[rt].r=r;
		return ;
	}
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	s[rt].l=l;
	s[rt].r=r;
	s[rt].ans=s[rt*2].ans|s[rt*2+1].ans;
}
int query(int rt,int l,int r)
{
	if(r<s[rt].l||l>s[rt].r)
	return 0;
	if(l<=s[rt].l&&r>=s[rt].r)
	return s[rt].ans;
	int mid=(l+r)>>1;
	return query(rt*2,l,r)|query(rt*2+1,l,r);
}
signed main()
{
	cin>>n>>m;
	scanf("%s",c+1); 
	int len=strlen(c+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=1ll<<(c[i]-'a');
	}
	build(1,1,n);
	int cd=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",c+1);
		cd|=1ll<<(c[1]-'a');
	}
	for(int i=1;i<=n;i++)
	{
		if(cd>=a[i]&&((cd^a[i])==(cd-a[i])))
		{
		int l=i,r=n,an=l;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int ld=query(1,i,mid);
			if(cd>=ld&&cd^ld==cd-ld)
			l=mid+1,an=mid;
			else r=mid-1;
		}
		ans+=an-i+1;
}
	}
	cout<<ans; 
}
```

---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1272C)

[AC记录](https://codeforces.com/contest/1272/submission/280321617)
# 题意简述
给定字符串 $s$ 和 $k$ 个可以使用的字符（$c_1\ ,c_2\ ,c_3\ ,\dots\ ,c_k$）。  
求用可使用的字符能组成 $s$ 中的几个子串。
# 题解
遍历 $s$，记下每个由不可使用的字符分开的区间长度 $len$，然后用下面的求和公式算出区间内有几个子串。
$$
\dfrac{len \times (len+1)}{2}
$$
最后将求得的结果加起来输出即可。

#### 示例如下（样例 $2$）:  
$\ \ $输入：    
$\ \ \texttt{sadfaasdda}$  
$\ \ \texttt{f a d}$  
$\ \ $分段：$\texttt{adfaa}$||$\texttt{dda}$（$\texttt{s}$ 舍去）  
$\ \ $答案：$\dfrac{5 \times (5+1)}{2}+\dfrac{3 \times (3+1)}{2}=15+6=21$

**注意！！！ 不开`long long`见祖宗！！！**
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
int n,k;
string s;
char c[30];
long long ans=0;
int main(){
    cin>>n>>k>>s;
    for(int i=1;i<=k;i++) cin>>c[i];
    int cnt=0;
    for(int i=0;i<n;i++){
        bool flag=0;
        for(int j=1;j<=k;j++) if(s[i]==c[j]) flag=1;//若s[i]可使用，记录。
        if(flag) cnt++;//可使用，长度+1。
        else{
            ans+=1ll*cnt*(cnt+1)/2;//否则统计当前答案。
            cnt=0;
        }
    }
    ans+=1ll*cnt*(cnt+1)/2;//别忘了记下最后一次
    cout<<ans;
    return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

题意：给定一个字符串 $s$，以及一个字符集 $t$，求 $s$ 有多少个非空子串满足子串内所有字母都在字符集里。

观察样例，实际上 $s$ 就是由一段段满足条件的串组合起来的，中间由非法字符分割开，对于每个串单独计算这一段的贡献即可，即 $\frac{len(len+1)}{2}$。答案可能很大，而且 $len(len+1)$ 也有可能爆 `int`。复杂度 $\mathcal{O}(n)$。[代码](https://paste.ubuntu.com/p/2pkJCxFzKG/)。

---

## 作者：huta0 (赞：0)

简单题。

题目要求可以打出来的连续子串有多少，我们先考虑关于连续子串的做法。

既然是连续啦，那么我们不难想到，找极长合法子串，然后对答案就是每个弄出来的极长合法字串的长度有贡献，因为我们不难看出啦，这种合法子串的子串也是合法子串。

剩下的就是细节和爆 int 的问题啦，我偷懒用了 map 记录可以用的字母，多了一个 log。

```cpp
#include <iostream>
#include <vector>
#include <map>
#define ai_jiang signed main()
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define drep(a,b,c) for(int a=b;a>=c;a--)
#define all(a) a.begin(),a.end()
#define ll long long
#define int long long
using namespace std;
using poly=vector<ll>;
namespace ai {
    constexpr int N = 2e5+5;
    int n,m;
    ll ans;
    char s[N];
    map<char,int> use;
}
using namespace ai;
ai_jiang {
    cin.tie(0); cout.tie(0);
    scanf("%d %d %s",&n,&m,s+1);
    rep(i,1,m) { char ch; cin>>ch; use[ch]=1; }
    rep(i,1,n) {
        if(!use[s[i]]) continue;
        int r=i;
        for(r=i;r<=n;r++)
            if(!use[s[r]]) { r--; break; }
        r=min(r,n);    
        int l=r-i+1;    
        ans+=l*(l+1)/2;
        i=r;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：AmamiyaYuuko (赞：0)

这道题给出了一个字符串和一些字母，问我们在这个字符串的所有子串中有几个只由这些字母构成的。

首先我们知道，一个字符串的所有子串个数为 $\dfrac{n(n + 1)}{2}$，其中 $n$ 是字符串的长度。

对于这道题而言，只需要维护一个长度 $len$，表示当前位置往前 $len$ 个位置的没有损坏的子串长度。一旦当前位置的字符损坏了，就把答案加上 $\dfrac{len(len + 1)}{2}$。

那么做法就很明显了：在读入时用一个 `bool` 数组统计一下哪些字母能用，哪些不能用，在处理时如果当前字母能用，就把 $len$ 加 $1$。如果不能用，就更新答案，把 $len$ 置为 $0$。

循环结束后如果 $len$ 不为 $0$，还应该更新一次答案。 

由于 $n \le 2 \times 10 ^ 5$，最后的答案要开 `long long`。我就因为这个导致了一次 WA ...

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

std::string str;
long long n, k, ans, len;
char c[30];
bool b[30];

int main()
{
    std::cin >> n >> k >> str;
    for (int i = 1; i <= k; ++i)
        std::cin >> c[i], b[c[i] - 'a'] = true;
    for (int i = 0; i < n; ++i)
    {
        if (b[str[i] - 'a'])
            ++len;
        else
        {
            ans += (len * (len + 1)) / 2;
            len = 0;
        }
    }
    if (len)   ans += (len * (len + 1)) / 2;
    std::cout << ans << std::endl;
    return 0;
}
```

---

