# 「CZOI-R6」Border

## 题目描述

给定一个仅包含小写字母的字符串 $s$（下标从 $1$ 开始），你可以将 **不超过 $\boldsymbol{1}$ 个位置** 修改为任意小写字母，使得最大化其最长 border 长度。你只需输出这个最大化的长度即可。

字符串 $b$ 是字符串 $a$ 的 border，当且仅当 $\lvert b\rvert < \lvert a\rvert$，且 $b$ 既是 $a$ 的前缀又是 $a$ 的后缀。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask #1（$10\ \text{pts}$）：$|s|\le 20$。
- Subtask #2（$20\ \text{pts}$）：$s_i\in\{\texttt a,\texttt b\}$。
- Subtask #3（$30\ \text{pts}$）：$|s|\le 1000$。
- Subtask #4（$40\ \text{pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le |s|\le 10^6$，$s$ 仅包含小写字母。

## 样例 #1

### 输入

```
abaa```

### 输出

```
3```

## 样例 #2

### 输入

```
qwqqaq```

### 输出

```
3```

## 样例 #3

### 输入

```
iakioi```

### 输出

```
1```

## 样例 #4

### 输入

```
ababaaab
```

### 输出

```
6
```

## 样例 #5

### 输入

```
r```

### 输出

```
0
```

## 样例 #6

### 输入

```
onion
```

### 输出

```
2
```

# 题解

## 作者：_O_v_O_ (赞：2)

考虑枚举 border 长度。

注意到假如枚举到了 $x$，那么 $s_{1\sim x}$ 和 $s_{n-x+1\sim n}$ 只有 $\le 1$ 处不同。

那么问题就被转化成了给定一个字符串，每次给定两个子串，问是否只有 $\le 1$ 处不同。

设这两个子串提取出来分别是 $a,b$，那么对于每个 $i$，若 $a_{1\sim i}=b_{1\sim i}$，那么不同的位置在 $[i+1,n]$，否则，在 $[1,i]$。

因此考虑二分，再用哈希判断两个子串是否相等。

然后你发现修改的位置假如同时影响了两个 border 那么就不行了，这样我们就相当于把 border 分成了三个串（有两个分点），还是二分即可。

时间复杂度 $O(n\log n)$。

Bonus：$O(n)$？

---

## 作者：_ckx_ (赞：1)

## 题目大意

给定一个字符串 $s$，至多修改其中一个字符，使其最长 `border` 尽量长。

`border`: 既是前缀又是后缀的子串。

## 分析

一开始智了，想的是二分，但是机房~~内阁~~同学写了一发 WA 了，才发现并没有单调性。

#### 接下来是正解：

由于只能进行一次修改，所以前后缀修改后**最多就改变两个位置**（两个串有交时改中间）。

所以**如果前后缀有 $>2$ 个位置不同，就肯定不能成为 `border`**。

于是可以枚举 `border` 的长度（也就是答案），找到前后缀的**第一个**不同字符位置，修改后再判断是否相等（如果有两个位置不同，就判第一和第二个）。

只判第一个和第二个的原因就是上面的结论。

现在问题就是找到第一个不同位置和判相等了，这个直接**二分**~~（这下有单调性了）~~ 再加个**哈希**就行了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll read()
{
    ll ret = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-' ? -f : f), ch = getchar();
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return ret * f;
}

int n;
const int N = 1e6 + 10;
char s[N];
ull h[N] ,pw[N] ,base = 1331;

ull get(int l ,int r) //获取 l ~ r 的子串 hash 值 
{
	if (l > r) return 0;
	return h[r] - h[l - 1] * pw[r - l + 1];
}

int main()
{
	scanf("%s",s + 1); n = strlen(s + 1);
	
	pw[0] = 1;
	for (int i = 1;i <= n;i++) pw[i] = pw[i - 1] * base;
	for (int i = 1;i <= n;i++) h[i] = h[i - 1] * base + s[i] - 'a'; //hash
	
	int ans = 0;
	for (int i = 1;i < n;i++)
	{
		int j = n - i + 1;
		int l = 1 ,r = i ,now = 0;
		while (l <= r) //二分找到最后一个相同的位置 
		{
			int mid = l + r >> 1;
			if (get(1 ,mid) == get(j ,j + mid - 1)) now = mid ,l = mid + 1;
			else r = mid - 1;
		}
		if (now == i) //直接匹配上 
		{
			ans = i;
			continue;
		}
		now++; //第一个不同的位置 
		bool f = false;
		
		//修改前缀的不同字符（第一个不同位置） 
		ull hs = get(1 ,i) - (s[now] - 'a') * pw[i - now]; //hs:前缀扣掉 now位置 的 hash 值 
		for (int c = 0;c < 26;c++) //枚举 now位置 替换成啥 
		{
			ull a = hs + c * pw[i - now] ,b = get(j ,n);
			
			//可能对后缀也有影响 
			if (j <= now) b += c * pw[n - now] - (s[now] - 'a') * pw[n - now];
			
			if (a == b) { f = true; break; } //找到可行修改 
		}
		if (f) { ans = i; continue; }
		
		//同理，修改后缀中的不同字符（第二个不同的位置）
		now = j + now - 1;
		hs = get(j ,n) - (s[now] - 'a') * pw[n - now];
		for (int c = 0;c < 26;c++)
		{
			ull b = hs + c * pw[n - now] ,a = get(1 ,i);
			if (i >= now) a += c * pw[i - now] - (s[now] - 'a') * pw[i - now];
			if (a == b) { f = true; break; }
		}
		if (f) ans = i;
	}
	
	printf("%d\n",ans);
	
    return 0;
}
```

---

## 作者：Ivan422 (赞：1)

### 前言

看到出题人题解的 Bonus 有 $\mathcal O(n)$ 做法，这里分享一下我的 Z 函数解法。

*本题目做法类似 PKUSC2023 D1T1 解法。*

### 题目大意

这题就是给你一个字符串，允许你动态修改至多一个位置求出可能的最长 Border。

### 思路

我们注意到这个值仅有关于前缀后缀，可以考虑哈希预处理出字符串的哈希值，然后快速匹配。

但是我们题目给定了修改操作，那么我们就需要请出 Z 函数了。

> Z 函数 $\operatorname{Z}(i)$ 是指从 $i$ 开始的后缀与原字符串的最长公共前缀长度。

我们有这个东西有什么用呢？可以考虑用 Z 函数值来匹配。


为表示方便，下文令 $z$ 为 $\operatorname{Z}(i)$。

### 做法

首先我们倒序遍历，相当于枚举后缀。然后我们发现 $z=i$ 时显然是出现了不用修改的 Border。这个东西在 PKUSC2023 D1T1 中比较重要，但是由于不一定要修改，这种情况会在后面被包含。

否则只可能是 $z<i$。这时显然需要修改。我们发现 Border 可能是由两个不交区间相等产生，也可能是两区间存在交集。这时我们需要分类讨论。

### 前后缀不交的情况

这时我们发现 $z$ 其实就是最后一个合题点。我们考虑跳过不合法点判断剩余是否还有其他的错误点，要是剩下都对，就可以更新答案。

具体的，第 $z+1$ 个字符是不合法字符，此时存在于前缀中的 $z+2$ 到第 $i$ 个字符所构成的子串将是合法字符。同理我们还要比对从第 $n-i+z+2$ 到第 $n$ 个字符所构成的子串是否有不合法字符。直接比对这两个子串的哈希值即可。
  
### 前后缀交的情况

比较麻烦了，我们发现这时候中间公共部分肯定要保证没有问题，因为这样需要改 $2$ 个以上的点，不过要是在正中间的话就不是这里的问题了。之后还需要像上一个情况一样再比对一次才能保证可以更新。

### 代码

综上，我们处理了所有情况，就可以正确求出所有的值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define us unsigned 
const int N=2e6+10;
const us int P=19937;
string a;
int n,Z[N],noupdate,ans[N];
us int pw[N],hsh[N];
us int Hash(int l,int r){
	return hsh[r]-hsh[l-1]*pw[r-l+1];
}
void maxs(int &p,int v){
	p=v;
	return;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>a;
    n=a.size();
    a=" "+a;
    pw[0]=1;
    for(int i=1;i<=n;i++)
    	pw[i]=pw[i-1]*P;
    for(int i=1;i<=n;i++)
    	hsh[i]=hsh[i-1]*P+a[i];
    int l=1,r=0;
    Z[1]=n;
    for(int i=2;i<=n;i++){
        if(i>r)
            Z[i]=0;
        else{
            int k=i-l+1;
            Z[i]=min(Z[k],r-i+1);
        }
        while(i+Z[i]<=n&&a[Z[i]+1]==a[i+Z[i]])
            ++Z[i];
        if(i+Z[i]-1>r)
            l=i,
            r=i+Z[i]-1;
    }
    for(int i=1;i<n;i++){
    	int z=Z[n-i+1];
    	if(z==i)
    		noupdate=i;
    	else if(z<i){
    		if((i<<1)<=n+z){
    			if(Hash(z+2,i)==Hash(n-i+z+2,n)){
    				maxs(ans[z+1],i);
    				maxs(ans[n-i+z+1],i);
    			}
    		}else{
    			if(Hash(n-i+z+2,i)==Hash(((n-i)<<1)+z+2,n))
    			if(Hash(z+2,n-i+z)==Hash(n-i+z+2,((n-i)<<1)+z))
    				maxs(ans[n-i+z+1],i);
    		}
    	}
    	if(i<(n+1)/2)
    		ans[i+1]=ans[n-i]=noupdate;
    }
    int mx=0;
    for(int i=1;i<=n;i++)
    	mx=max(mx,ans[i]);
    cout<<mx;
    return 0;
}
```


#### 或许是双倍

在判断内加上需要修改是否是另一个字符串的对应字符可以通过 PKUSC2023 D1T1。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define us unsigned 
const int N=2e6+10;
const us int P=19937;
string a,b;
int n,Z[N],noupdate,ans[N];
us int pw[N],hsh[N];
us int Hash(int l,int r){
	return hsh[r]-hsh[l-1]*pw[r-l+1];
}
void maxs(int &p,int v){
	p=v;
	return;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>a>>b;
    n=a.size();
    a=" "+a,b=" "+b;
    pw[0]=1;
    for(int i=1;i<=n;i++)
    	pw[i]=pw[i-1]*P;
    for(int i=1;i<=n;i++)
    	hsh[i]=hsh[i-1]*P+a[i];
    int l=1,r=0;
    Z[1]=n;
    for(int i=2;i<=n;i++){
        if(i>r)
            Z[i]=0;
        else{
            int k=i-l+1;
            Z[i]=min(Z[k],r-i+1);
        }
        while(i+Z[i]<=n&&a[Z[i]+1]==a[i+Z[i]])
            ++Z[i];
        if(i+Z[i]-1>r)
            l=i,
            r=i+Z[i]-1;
    }
    for(int i=1;i<n;i++){
    	int z=Z[n-i+1];
    	if(z==i)
    		noupdate=i;
    	else if(z<i){
    		if((i<<1)<=n+z){
    			if(Hash(z+2,i)==Hash(n-i+z+2,n)){
    				if(b[z+1]==a[n-i+z+1])
    					maxs(ans[z+1],i);
    				if(a[z+1]==b[n-i+z+1])
    					maxs(ans[n-i+z+1],i);
    			}
    		}else{
    			if(Hash(n-i+z+2,i)==Hash(((n-i)<<1)+z+2,n))
    			if(Hash(z+2,n-i+z)==Hash(n-i+z+2,((n-i)<<1)+z)){
    				if(a[z+1]==b[n-i+z+1])
    				if(a[((n-i)<<1)+z+1]==b[n-i+z+1])	
    					maxs(ans[n-i+z+1],i);
    			}
    		}
    	}
    	if(i<(n+1)/2)
    		ans[i+1]=ans[n-i]=noupdate;
    }
    for(int i=1;i<=n;i++){
    	if(a[i]==b[i])
    		cout<<noupdate<<"\n";
    	else
    		cout<<ans[i]<<"\n";
    }
    return 0;
}
```

---

## 作者：rabbit_mygo (赞：0)

## 前置知识
扩展 kmp 或字符串哈希。  
## 思路分析
记 $(l,r)$ 为区间 $[l,r]$ 的字符，$zp_i$ 为字符串 $s$ 的以 $c_i$ 开始的后缀与原字符串 $s$ 的最长公共前缀长度，$zs_i$ 为字符串 $s$ 的以 $c_i$ 结尾的后缀与原字符串 $s$ 的最长公共后缀长度。  

从大到小枚举 border 长度。  

记枚举到长度 $i$。

如果不改变字符且该 border 合法，则有 $(1,i) = (n-i+1,n)$。  

否则改变了一个字符。  

根据长度分类讨论。  

当 $ i \gt \lfloor \frac{n}{2} \rfloor$ 时，border 对应的前缀与后缀是有交的，反之则无交。  

先考虑无交的情况，发现如果改变某个字符 $c_z$ 能使得该 border 合法，则有 $zp_i+zs_{n-i+1}+1=i$。  
形象地，就是从两个无交的 $(1,i),(n-i+1,n)$ 中断掉一个点 $c_z$，断点两边的 $(1,z-1),(n-i+1,z-1)$ 和 $(z+1,i),(z+1,n)$ 依然相等。  

再考虑有交的情况，对于 $c_z$ 是否处在区间的交集分讨。  

如果是处在无交部分，那仍然有 $zp_i+zs_{n-i+1}+1=i$ 的判断条件。  

否则由于有交，断点会导致出现一段匹配“空白”。   

举个例子，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bte47so7.png)  

有一个字符串 $s$，现在枚举长度 $i$ 到 $10$，橙色部分是前缀，红色部分是后缀，紫色划线部分是对饮匹配的前后缀。  
然后观察如果改变某个字符能使得橙色部分与红色部分匹配，会满足什么条件（不保证 $10$ 就是答案，只是举例）。  

不难发现其中的蓝色字符 $c_7 = b$ 是需要改变的字符，并且将其改成 $c$ 整个字符串就全是 $c$，肯定合法。

记 $p1 = zp_{n-i+1},p2 = zs_i$，即枚举到的橙色前缀和红色后缀的最长公共前缀长 $p1$ 和最长公共后缀长 $p2$，这里 $p1 = 2,p2 = 3$。  

可以发现，限制 $p1$ 的第一个字符应当是 $c_{n-i+p1}$，而限制 $p2$ 的第一个字符应当是 $c_{n-p2}$
，这里二者算出来都为 $b_7$。  

如果 $c_{n-i+p1} = c_{n-p2}$ 不成立，说明至少有两个字符限制了前缀与后缀的匹配，但是我们至多改变一个字符，那肯定不存在合法的需要改变字符了。  

否则的话，前缀与后缀匹配还需要一些条件。  

首先橙色前缀的 $b$ 会与红色后缀中的绿色字符相等，而红色后缀的 $b$ 会与橙色前缀的绿色字符相等。  

所谓绿色字符，其实就是匹配的下一位，所以有第一个条件 $c_{p1+1} = c_{n-p2}$。  

并且，粉色划线部分会对应相等，即有 $(p1+2,i-p2-1) = (n-i+p1+1,n-p2-1)$。  

这可以用字符串哈希 $O(1)$ 匹配。  

对于求 $zs_i,zp_i$，如果知道扩展 kmp 的话是可以 $O(n)$ 递推的 $zp_i$，求 $zs_i$ 的话可以翻转整个字符串，然后按求 $zp_i$ 的方式求，最后再翻转 $zs$ 数组即可。  

匹配两个区间的字符串是否相等可以用进制哈希。  

这样时间复杂度就是 $O(n)$ 的。  

如果不知道扩展 kmp 也可以对于每个位置二分。  

这样时间复杂度是 $O(n \log n)$ 的。  

## 代码
```cpp
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
static int stkk[100],topp;
inline void output(int x){
	if(!x)return(void)(putchar('0'));
	if(x<0)x = ~x+1,putchar('-');
	for(;x;stkk[++topp]=x%10^48,x/=10);
	for(;topp;putchar(stkk[topp--]));
}
inline int readx(){
	int x = 0,y = 1;char c = getchar();
	for(;c<48||c>58;c = getchar())if(c=='-')y = -1;
	for(;c>=48&&c<=58;c = getchar())x = (x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int N = 1e6+10,b1 = 131,b2 = 137,m1 = 1e9+7,m2 = 1e9+9;
char s[N];
int zp[N],zs[N],n,h1[N],h2[N],p1[N],p2[N];
inline void init(){
	scanf(" %s",s+1);
	n = std::strlen(s+1);
	p1[0] = p2[0] = 1;
	for(int i = 1;i <= n;i++){
		h1[i] = (1ll*h1[i-1]*b1%m1+s[i])%m1;
		h2[i] = (1ll*h2[i-1]*b2%m2+s[i])%m2;
		p1[i] = 1ll*p1[i-1]*b1%m1;
		p2[i] = 1ll*p2[i-1]*b2%m2;
	}
}
inline int hash1(int l,int r){return (0ll+(h1[r]-1ll*h1[l-1]*p1[r-l+1]%m1)%m1+m1)%m1;}
inline int hash2(int l,int r){return (0ll+(h2[r]-1ll*h2[l-1]*p2[r-l+1]%m2)%m2+m2)%m2;}
inline bool pi(int l,int r,int x,int y){return l>r?1:hash1(l,r)==hash1(x,y)&&hash2(l,r)==hash2(x,y);}
inline void getz(int* z){
	for(int i = 2,k = 1;i <= n;i++){
		if(z[i-k+1]<k+z[k]-i)z[i] = z[i-k+1];
		else{
			z[i] = k+z[k]-i;
			if(z[i]<0)z[i] = 0;
			while(i+z[i]-1<n&&s[i+z[i]]==s[z[i]+1])++z[i];
			k = i;
		}
	}
	z[1] = n;
}
inline void solve(){
	getz(zp);
	std::reverse(s+1,s+1+n);
	getz(zs);
	std::reverse(zs+1,zs+1+n);std::reverse(s+1,s+1+n);
	int ans = 0;
	for(int i = n-1;i > (n>>1);i--){
		if(zp[n-i+1]==i){ans = i;break;}
		int p1 = zp[n-i+1],p2 = zs[i];
		if(p1+p2+1==i){ans = i;break;}
		if(n-i+p1+1!=i-p2)continue;
		if(s[p1+1]==s[n-p2]&&pi(p1+2,i-p2-1,n-i+p1+2,n-p2-1)){ans = i;break;}
	}
	if(ans)output(ans),exit(0);
	for(int i = (n>>1);i;i--){
		if(zp[n-i+1]==i){ans = i;break;}
		else if(zp[n-i+1]+zs[i]+1==i){ans = i;break;}
	}
	output(ans),putchar(10);
}
int main(){
	init(),solve();
	return 0;
}
````

若有疏漏和错误，在此表示歉意并欢迎 dalao 指出。  

最后祝您：万事如意！（q'w'q）

---

## 作者：fengzhaoyu (赞：0)

## 前言
~~我是 hash 仙人，叫我场切了。~~
## 思路
分类讨论一下：
1. 最大 border 前后不相交，即小于等于 $\frac{n}{2}$。此时我们只需遍历一下答案的长度 $i$，看符合题意的最大值是多少。由于题中说只能改一个，那我们就判断一下前 $i$ 个和后 $i$ 个字符是否只有一个位置不同即可。
2. 最大 border 前后相交，即大于 $\frac{n}{2}$。那么前后的交集，如果我改了其中的值，是不是前后都有一个位置会改变且两位置下标差是 $n-i$（因为前后开头差都是 $n-i$）？设这两个位置在前面 $i$ 个元素的下标为 $l$，$l1$（后面的则为 $n-i+l$ 和 $n-i+l1$）。不妨设 $l1<l$，那么 $s_{l}=s_{n-i+l1}$（同一个点嘛）且 $s_{l1}=s_{n-i+l}$（你改只会变 $s_{l}$ 即 $s_{n-i+l1}$，所以剩下两个必须一样才行）。不理解看图。
![1](https://cdn.luogu.com.cn/upload/image_hosting/afaf5wy0.png)
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=5e6+25;
ull h[N],d=1331,qp[N];
int n;
ull get(int l,int r)
{
	if(l>r) return 0;
	return h[r]-h[l-1]*qp[r-l+1];
}
bool check(int l,int r,int y)//判断是否前后缀相同 
{
	if(l>r) return 1;
	return get(l,r)==get(n-y+l,n-y+r);
}
//bool check1(int x)
//{
//	return get(1,x)==get(n-x+1,n);
//}
int main()
{
	string s;
	cin>>s;
	n=s.size();
	s=" "+s;
	qp[0]=1;
	for(int i=1;i<=n;i++) 
	{
		qp[i]=qp[i-1]*d;
		h[i]=h[i-1]*d+ull(s[i]-'a'+1);
	}
	int ans=0;
	for(int i=1;i<n;i++)
	{
		if(get(1,i)==get(n-i+1,n))
		{
			ans=i;
			continue;
		}
		if(i<=(n)/2)
		{
			int l=1,r=i;
			while(l<r)//二分找不同的地方
			{
				int mid=(l+r)>>1;
				if(check(1,mid,i))
				{
					l=mid+1;
				}
				else r=mid;
			}
			if(check(1,l-1,i)&&check(l+1,i,i))//除了这个地方不同以外其他地方是否全相同
			{
				ans=i;
			}	
//			cout<<i<<" "<<l<<endl;
			continue;		
		}
		int l=1,r=i;
		while(l<r)
		{
			int mid=(l+r)>>1;
//			if(i==6)cout<<l<<" "<<r<<" "<<mid<<" "<<check(3,i)<<endl;
			if(check(1,mid,i))
			{
				l=mid+1;
			}
			else r=mid;
		}
		int k=0;
		int	l1=1,r1=l-1;
		if(get(1,l-1)!=get(n-i+1,n-i+l-1))
		{
			k++;
			while(l1<r1)
			{
				int mid=(l1+r1)>>1;
				if(check(1,mid,i))
				{
					l1=mid+1;
				}
				else r1=mid;
			}
		}
		if(get(l+1,i)!=get(n-i+l+1,n))
		{
			k++;
			l1=l+1,r1=n;
			while(l1<r1)
			{
				int mid=(l1+r1)>>1;
				if(check(l+1,mid,i))
				{
					l1=mid+1;
				}
				else r1=mid;
			}
		}
		if(l1>l) swap(l1,l);
		if((k==1&&l-l1==n-i&&(s[l1]==s[n-i+l])&&(s[l]==s[n-i+l1])))
		{
//		cout<<l1<<' '<<l<<" "<<i<<endl;
//				if(i==3) cout<<check(l+1,n,i);

//			cout<<i<<endl;
//			cout<<(get(1,l1-1)==get(n-i+1,n-i+l1-1))<<endl;
			if(check(1,l1-1,i)&&check(l1+1,l-1,i)&&check(l+1,i,i))//同i<=n/2，只是分成3段罢了。
			{
				ans=i;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：IntoTheDusk (赞：0)

:::info[题面]
给定一个仅包含小写字母的字符串 $s$（下标从 $1$ 开始），你可以将不超过 $1$ 个位置修改为任意小写字母，使得最大化其最长 $\rm{border}$ 长度。

$1 \le |s| \le 10^6,\rm{2.0s,512MiB}$。
:::

这是一篇采用后缀数组做法的题解。和官方的哈希加二分的做法相比，其算法本身难度高，常数较大，跑的很慢，但是在了解到其一些性质后优化到线性的思维难度非常低（因为事实上复杂度瓶颈就在于求 $\rm{SA}$ 以及 $O\left(n\right)-O\left(1\right)$ 的静态 $\rm{RMQ}$，前者可以用 $\rm{SA-IS}$，后者可以用四毛子,不过个人感觉没啥必要，代码难度和常数在同复杂度算法中都非常劣，本篇题解也不重点涉及这一块的优化）。

首先，先对 $s$ 求个 $\rm{SA}$ 并对 $\rm{height}$ 做一次 $\rm{ST}$ 表，这样的话我们可以 $O\left(1\right)$ 求 $\rm{LCP}$，进而也可以做到 $O\left(1\right)$ 比较子串。

然后回到原题，我们从小到大枚举 $i$ 考虑能否让 $\rm{border}$ 的长度达到 $n-i+1$，如果发现可以了就直接输出并退出，如果完全没有就输出 $0$。于是现在只需考虑怎么判定。令 $L=\rm{LCP}(1,i)$，我们发现 $s_{L+1} \ne s_{i+L}$。为了让 $\rm{border}$ 的长度不短于 $n-i+1$，我们必须改变这两个字符中的一个才有可能达到我们的目标。于是我们只需要考虑跳过这两个字符后这两个前缀能否一直匹配到字符串末尾。

但这个时候我们发现单次的改动有可能对后续产生影响，于是我们试着分类讨论。

- 如果 $n-i-L \le i-2$，类似下图，我们本质上是想要比较红色部分和绿色部分的是否相同，而此时我们怎么修改都是不会影响这一部分的。于是我们直接比较 $s_{L+2 \dots n-i+1}$ 与 $s_{i+L+1 \dots n}$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/dyw1ja3w.png)

- 如果 $n-i-L > i-2$，类似下图，我们还是只需要让红色和绿色的部分匹配，但我们发现我们的更改可能会对后续的匹配产生影响（因为红色部分覆盖了 $i+L$），但这个影响非常小，只有一个字符。于是我们进一步分类讨论。
  + 如果我们要把 $s_{L+1}$ 变为 $s_{i+L}$，那么我们需要保证在 $s_{i+L}$ 不变的情况下可以完成匹配。通过推导我们容易发现，我们需要保证 $s_{i+L}=s_{2i+L-1}$，此外还需判断 $s_{L+2 \dots n-i+1}$ 与 $s_{i+L+1 \dots n}$ 是否相同。
  + 如果我们要把 $s_{i+L}$ 变为 $s_{L+1}$，那我们其实就要保证 $s_{i+1}=s_{2i+L-1}$。此外，由于 $s_{i+L}$ 在一开始无法被匹配，我们的匹配还需要被拆为两段，一段是 $s_{L+2 \dots i+L-1}$ 与 $s_{i+L+1 \dots 2i+L-2}$，另一段则是 $s_{i+L+1 \dots n-i+1}$ 与 $s_{2i+L \dots n}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jxc6z1wb.png)

于是就做完了。由于我写的是倍增 $\rm{SA}$ 加上 $\rm{ST}$ 表，时间复杂度 $O\left(n \log n \right)$。想优化到线性的话可以用我在开头讲的方法。

:::success[一份 $O\left(n \log n \right)$ 的实现]
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int N=1e6+10;
string s;
int n,m,x[N],y[N],c[N];
int sa[N],height[N],rk[N];
int lg[N],f[N][22];
void rmq(){
	lg[0]=-1;
	for(int i=1;i<=n;i++){
		lg[i]=lg[i>>1]+1;f[i][0]=height[i];
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int l,int r){
	int k=lg[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
void getsa(){	
    for(int i=1;i<=n;i++){
    	x[i]=s[i];++c[x[i]];
    }
    for(int i=2;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k=k<<1){	
        int num=0;
        for(int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;i++){
            if(sa[i]>k)y[++num]=sa[i]-k;
        }
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[i]]++;
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--){
        	sa[c[x[y[i]]]--]=y[i];y[i]=0;
        }
        swap(x,y);
        num=1;x[sa[1]]=1;
        for(int i=2;i<=n;i++){	
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
            else x[sa[i]]=++num;
        }
        if(num==n)break;
        m=num;
    }
}
void getlcp(){	
    int k=0;
    for(int i=1;i<=n;i++) rk[sa[i]]=i;
    for(int i=1;i<=n;i++){	
        if(rk[i]==1)continue;
        if(k)k--;
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])k++;
        height[rk[i]]=k;
    }
    rmq();
}
int lcp(int i,int j){
    if(rk[i]>rk[j]) swap(i,j);
    int ret=0;
    if(i==j) ret=n-i+1;
    else ret=query(rk[i]+1,rk[j]);
    return ret;
}
bool check(int l1,int r1,int l2,int r2){
	if(r1-l1+1!=r2-l2+1){
		return false;
	}
	if(r1-l1+1==0) return true;
	if(1<=l1&&l1<=r1&&r1<=n){
		if(1<=l2&&l2<=r2&&r2<=n){
			int L=r1-l1+1;
			int L2=lcp(l1,l2);
			return L<=L2;
		}
		else return false;
	}
	else return false;
}
bool check(int l1,int r1,int l2){
	return check(l1,r1,l2,l2+(r1-l1));
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s;n=s.size();s=" "+s;m=122;
    getsa();getlcp();
    for(int i=2;i<=n;i++){
    	int L=lcp(1,i);
    	if(L==n-i+1){
    		cout<<n-i+1<<'\n';return 0;
		}
		if(n-i-L+2<=i){
			if(check(i+1+L,n,L+2)){
				cout<<n-i+1<<'\n';return 0;
			}
		}
		else{
			if(check(L+2,i+L-1,i+L+1)){
				int R=i+L-L-1;
				if(s[i+L+R]==s[i+L]||s[i+L+R]==s[L+1]){
					if(check(i+L+R+1,n,L+1+R+1)){
						cout<<n-i+1<<'\n';return 0;
					}
				}
			}
		}
	}
	cout<<"0\n";
    return 0;
}
```
:::

---

## 作者：SegmentTree_ (赞：0)

记 $s_i$ 为 $s$ 的第 $i$ 个字符，$s(l,r)$ 为 $s$ 的子串 $s_ls_{l+1}\cdots s_{r-1}s_{r}$，$pre(i)$ 为 $s(1,i)$，$suf(i)$ 为 $s(n-i+1,n)$。  
考虑枚举答案，判断这个答案是否合法。  
设当前枚举到 $l$，要判断的是 $pre(l)$ 和 $suf(l)$ 中不同的字母个数是不是小于等于 $1$。若 $pre(l)=suf(l)$，则 $l$ 是合法的，可以用哈希判断，下文中只考虑 $pre(l)$ 和 $suf(l)$ 恰好差一个的情况。  
有一个方法是用二分哈希找到第一个不同的位置，然后跳过那个位置，判断后面的部分是否相同。遗憾的是这是假的，跳过相当于修改，但如果 $[1,l]$ 和 $[n-l+1,n]$ 的交集非空，且修改的位置正好在上面，就会同时改变 $pre(l)$ 和 $suf(l)$，可能会炸掉，所以可以开一个线段树维护哈希，修改直接做就行。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define lid (id << 1)
#define rid (id << 1 | 1)
const int N = 1e6+5;
namespace tianyu{
	int n;
	string s;
	ull hsh[N], pw[N];
	ull hash(int l, int r){return hsh[r] - hsh[l - 1] * pw[r - l + 1];}
	int lcp(int x, int y){
		int l = 1, r = n - max(x, y) + 1, ans = 0;
		while (l <= r){
			int mid = l + r >> 1;
			if (hash(x, x + mid - 1) == hash(y, y + mid - 1)){
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		return ans;
	}
	struct node{
		int l, r;
		ull hsh;
	}tr[N << 2];
	void pushup(int id){
		tr[id].hsh = tr[lid].hsh * pw[tr[rid].r - tr[rid].l + 1] + tr[rid].hsh;
	}
	void build(int id, int l, int r){
		tr[id].l = l, tr[id].r = r;
		int mid = l + r >> 1;
		if (l == r){
			tr[id].hsh = s[l];
			return;
		}
		build(lid, l, mid);
		build(rid, mid + 1, r);
		pushup(id);
	}
	void modify(int id, int p, int x){
		if (tr[id].l == tr[id].r){
			tr[id].hsh = x;
			return;
		}
		int mid = tr[id].l + tr[id].r >> 1;
		if (p <= mid) modify(lid, p, x);
		else modify(rid, p, x);
		pushup(id);
	}
	ull query(int id, int l, int r){
		if (l <= tr[id].l && tr[id].r <= r) return tr[id].hsh;
		int mid = tr[id].l + tr[id].r >> 1;
		if (r <= mid) return query(lid, l, r);
		else if (l > mid) return query(rid, l, r);
		else return query(lid, l, mid) * pw[r - mid] + query(rid, mid + 1, r);
	}
	void awa(){
		cin >> s;
		n = s.size();
		s = ' ' + s;
		pw[0] = 1;
		for (int i = 1;i <= n;i++){
			hsh[i] = hsh[i - 1] * 131 + s[i];
			pw[i] = pw[i - 1] * 131;
		}
		build(1, 1, n);
		for (int i = n - 1;i >= 1;i--){
			int pos = lcp(1, n-i+1);
			if (pos >= i){
				cout << i;
				return;
			}
			int x = pos + 1, y = n - i + pos + 1;
			char a = s[x], b = s[y];
			modify(1, y, a);
			if (query(1, 1, i) == query(1, n - i + 1, n)){
				cout << i << '\n';
				return;
			}
			modify(1, x, b), modify(1, y, b);
			if (query(1, 1, i) == query(1, n - i + 1, n)){
				cout << i << '\n';
				return;
			}
			modify(1, x, a);
		}
	}
}
signed main(){
	int T = 1;
	while (T--) tianyu::awa();
	return 0;
}
```

---

