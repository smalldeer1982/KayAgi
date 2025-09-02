# Shifting String

## 题目描述

Polycarp found the string $ s $ and the permutation $ p $ . Their lengths turned out to be the same and equal to $ n $ .

A permutation of $ n $ elements — is an array of length $ n $ , in which every integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 2, 3] $ and $ [4, 3, 5, 1, 2] $ are permutations, but $ [1, 2, 4] $ , $ [4, 3, 2, 1, 2] $ and $ [0, 1, 2] $ are not.

In one operation he can multiply $ s $ by $ p $ , so he replaces $ s $ with string $ new $ , in which for any $ i $ from $ 1 $ to $ n $ it is true that $ new_i = s_{p_i} $ . For example, with $ s=wmbe $ and $ p = [3, 1, 4, 2] $ , after operation the string will turn to $ s=s_3 s_1 s_4 s_2=bwem $ .

Polycarp wondered after how many operations the string would become equal to its initial value for the first time. Since it may take too long, he asks for your help in this matter.

It can be proved that the required number of operations always exists. It can be very large, so use a 64-bit integer type.

## 说明/提示

In the first sample operation doesn't change the string, so it will become the same as it was after $ 1 $ operations.

In the second sample the string will change as follows:

- $ s $ = babaa
- $ s $ = abaab
- $ s $ = baaba
- $ s $ = abbaa
- $ s $ = baaab
- $ s $ = ababa

## 样例 #1

### 输入

```
3
5
ababa
3 4 5 2 1
5
ababa
2 1 4 5 3
10
codeforces
8 6 1 7 5 2 9 3 10 4```

### 输出

```
1
6
12```

# 题解

## 作者：liujy_ (赞：7)

 ### 修改于2023年10月17日，补了一个严格线性做法。    
 首先看到题目中，马上想到把 $i$ 向 $p_i$ 连边，由于 $p$ 是一个排列，所以每个点的出度与入度一定为一，最后的图一定是一堆环。  
 于是问题就转化为给定许多个环，每个点上的字符在每次操作中会往前跳一步，问最少的操作次数可以是每个点上和最初在这个点上的字符相同。  
 然后我马上就想到直接统计所有的环长，最后的答案就是所有环长的最小公倍数。然后我就兴奋的把代码打下来然后发现过不了样例。仔细一看发现每个环不一定一定要回到最初的位置每个位置的字母才可以。  
 那么接下来问题就是如何统计每个环要最少跳多少步。一看数据范围 $n \leq 200$，所以我们可以直接暴力跳，跳到相同为止。最后在记录最小公倍数就可以啦！  
 下面是代码。  
 ```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
int t,n,m,now,mn,a[205],l[205];char ch[205],c[205];bool vis[205];
bool check(int x){
	for(int i=a[x];i!=x;i=a[i])
		if(c[i]!=ch[i])return 0;
	if(c[x]!=ch[x])return 0;
	return 1;
}//判断当前的环是否和最开始相同 
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(vis,0,sizeof(vis));memset(l,0,sizeof(l));
		scanf("%lld",&n);
		scanf("%s",ch+1);
		memcpy(c,ch,sizeof(c));
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(vis[i])continue ;
			++cnt;
			for(int j=i;!vis[j];j=a[j])vis[j]=1;//标记这个环 
			l[cnt]=1;
			char t=c[i];c[i]=c[a[i]];
			for(int j=a[i];j!=i;j=a[j]){
				c[j]=c[a[j]];
				if(a[j]==i)c[j]=t;
			}//需要先跳一次，否则进不去下面的循环 
			while(!check(i)){
				t=c[i];c[i]=c[a[i]];
				for(int j=a[i];j!=i;j=a[j]){
					c[j]=c[a[j]];
					if(a[j]==i)c[j]=t;
				}
				l[cnt]++;
			}//暴力往前跳 
		}
		int ans=l[1];
		for(int i=2;i<=cnt;i++){
			int d=__gcd(ans,l[i]);
			ans=ans*l[i]/d;
		}//统计lcm 
		printf("%lld\n",ans);
	}
    return 0;
}
```

初写这篇题解的时候比较菜，过了一道题就很兴奋想交题解，最近在准备给学弟学妹做杂题选讲看到了这道题就想了一下不暴力判断的话要怎么做，其实也不是很难。   
我们考虑一个环每跳一步的本质是什么。不要把这个过程看成一个环在转，而是把一个环看成一个普通的字符串，那么实质上每跳一步就相当于把第一个字符放到了最后，那么最少要跳的步数相当于找这个字符串的最小循环同构。   
一个简单的想法是枚举我们跳了几步，考虑如何快速判断这样的新字符串是否与原串相等。   
我们假设已经跳了 $x$ 步，那么相当于前 $x$ 个字符被删去然后接到了字符串的最后，也就是说如果此时的串等于原串，那么前 $x$ 个字符一定是原串的一个公共前后缀，同理此时从 $x+1$ 到字符串的最后这个后缀肯定也是一个公共前后缀。判断一个前缀或者后缀是否是一个公共前后缀只要跑一遍 KMP 即可。  
贴个代码。  
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
int t,n,m,now,mn,cnt,a[205],l[205],nxt[205];
char ch[205],c[205];bool vis[205],use1[205],use2[205];
signed main(){
	scanf("%lld",&t);
	for(int T=1;T<=t;T++){
		memset(vis,0,sizeof(vis));memset(l,0,sizeof(l));
		scanf("%lld",&n);scanf("%s",ch+1);cnt=0;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++){
			if(vis[i])continue ;
			++cnt;int len=0;nxt[1]=0;
			for(int j=i;!vis[j];j=a[j])vis[j]=1,c[++len]=ch[j];
		    for(int i=2,j=0;i<=len;i++){use1[i]=use2[i]=0;
		        while(j&&c[i]!=c[j+1])j=nxt[j];
		        if(c[i]==c[j+1])j++;nxt[i]=j;
		    }
		    l[cnt]=len;int p=nxt[len];
		    while(p)use1[p]=1,use2[len-p+1]=1,p=nxt[p];
		    for(int i=2;i<=len;i++)
		    	if(use2[i]&&use1[i-1]){l[cnt]=i-1;break;}
		}
		int ans=l[1];
		for(int i=2;i<=cnt;i++){
			int d=__gcd(ans,l[i]);
			ans=ans*l[i]/d;
		}
		printf("%lld\n",ans);
	}
    return 0;
}
```


---

## 作者：3a51_ (赞：5)

赛时过了这题，写篇题解纪念下。

---

首先，假设序列为 $2\;4\;5\;1\;3(n=5)$，对于第一个字符（假设为 $\text{a}$）：

- 第一次重排后，由于 $p_1=2$，所以 $\text{a}$ 到达了第二个位置；
- 第二次重排后，由于 $p_2=4$，所以 $\text{a}$ 到达了第四个位置；
- 第三次重排后，由于 $p_4=1$，所以 $\text{a}$ 回到了第一个位置。

不难发现，$\text{a}$ 经过的所有位置组成了一个环，所以，每 $3$ 次重排，$\text{a}$ 就回到了原点。

这样来说，就有了最初版的解题思路：

> 寻找所有环，统计长度的 $\operatorname{lcm}$

但是分析样例的第一组数据，发现：

有可能出现环内存在循环的情况，此时应该取最短循环节的长度。

所以，正确思路是：

> 寻找所有环的最短循环节，统计长度的 $\operatorname{lcm}$

最后注意记得开`long long`。

---

## 作者：中缀自动机 (赞：1)

题意：输入一个长度为 $n$ 的字符串和排列顺序，每一次操作都让字符串根据排列的顺序改变位置，问最少执行多少次操作后字符串重新回到开始的样子。

------------
分析：求排列中的环的长度，对这些长度求最小公倍数，但是如果环中的字符有重复子串，需要用最小重复子串的长度来计算，如 $abababab$，作为一个环，它的长度为 $8$，但其实经过两次操作，它就回到初始排列了。


------------
这样来说，就有了最初版的解题思路：

>寻找所有环，统计长度的 $\operatorname{lcm}$

但是分析样例的第一组数据，发现：

>有可能出现环内存在循环的情况，此时应该取最短循环节的长度。

所以，正确做法是：
>寻找所有环的最短循环节，统计长度的 $\operatorname{lcm}$

------------
证明：

假设 $k\nmid$ ，则 $n=qk+rn=qk+r$ $(0<r<k)$。那么有 $s=s\circ f^n=s \circ f^{qk}\circ f^r=s\circ f^r$ 。但这与 $k$ 是最小的满足要求的数相矛盾。所以必有 $k\mid n$，证毕。

------------


注：要开 long long


------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long gcd(long long x,long long y){
	if(y==0) return x;
	else return gcd(y,x%y);
}
char sca[300];
long long use[300],p[300];
int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,n;
	cin>>t;
	while(t--){
		memset(use,0,sizeof(use));
		long long cnt=0,ans=1;
		cin>>n;
		cin>>sca+1;
		for(int i=1;i<=n;i++) cin>>p[i];
		for(int i=1;i<=n;i++){
			if(use[i]) continue;
			use[i]=1;
			long long x=i;
			vector<char> vec;
			vec.push_back(sca[x]);
			while(use[p[x]]==0){
				x=p[x];
				use[x]=1;
				vec.push_back(sca[x]);
			}
			for(int z=1;z<=vec.size();z++){
				if(vec.size()%z==0){
					bool flag=1;
					for(int j=z;j<vec.size();j++){
						if(vec[j]!=vec[j-z]){
							flag=0;
							break;
						}
					}
					if(flag){
						ans=ans*z/gcd(ans,z);
						break;
					}
				}
			}
		}
		cout<<ans<<"\n";
	}
    return 0;
}
```


---

## 作者：Xu_brezza (赞：1)

继续水题解.jpg
在此膜拜 KH & slb 两位大佬 orz！
## 题意：
给你一个长度为 $n$ 的字符串，和一个 $1$ 到 $n$ 的排列，定义 shift 操作为将该字符串按照该排列排列，问最少多少次能得到初始的字符串。

## 分析：
这是一个映射对吧，那么对于每个位置上的 $i$，我们将它向 $p[i]$(对应排列的位置)连一条有向边，那么最后我们肯定会得到很多个环（不理解可以手玩一下），那么这个环上的每一个点就是一个对应原字符串的字符，一次 shift 操作就相当于把这个环转了一下，那就相当于转了 $k$ 次后，我们的环和原来的环长得一样（假设有相对位置），那么这一个环最少要 $k$ 次，我们只需要求出所有的环，求出每个环的 $k$，然后求最小公倍数，就是答案！在求 $k$ 的时候可以破环成链来解决，然后暴力就好啦。
[代码在这~~~](https://www.luogu.com.cn/paste/rftbos17)

---

## 作者：fast_photon (赞：1)

**0. 前言**  
Upd 2022.6.8. 22:25，修改了最大公因数和最小公倍数的 $\LaTeX$；删除了本该在 E 题的叙述（不开 LL 见祖宗）；修改了补充证明的叙述。  
Upd 2022.6.9. 14:32，更正了一处写成 $n-i$ 的 $n/i$    
Upd 2022.6.11 9:24，增加了注释  
Upd 2022.6.11 9:45，添加了关于“为何求 lcm”的叙述
[这题](https://www.luogu.com.cn/problem/CF1690F)赛时大概花了一分多钟想正解，二十分钟实现。  
好了我们进入正题。  

**1. 分析**  
首先，因为我~~思维比较敏锐~~见过此类题目，所以一眼就看出了大题做法。不过分析还是要分析的，不然你们也不用看题解了，直接随便找个正确代码交上去完了。  
这题首先先从数据入手。乍一看最多换 $n$ 次就能换回来，因为一个数只有 $n$ 个地方可以去。然而...这题放在F，真的会这么简单？  
首先，换回来肯定是经过了一轮循环。然而，对于一个数 $a_i$，不是所有地方都可能被换到，换句话说，很可能存在很多个 $a_j$，在交换途中 $a_j$ 永远不等于 $a_i$。这么说不太直观，我们来举个例子：  
$$s=[a,b,c,d]$$  
$$p=[3,4,1,2]$$  
进行无论多少次交换，第 $2$ 和第 $4$ 个位置上都不会有 `a` 和 `c` 出现，因为在 $p$ 中第 $1$ 和第 $3$ 个位置构成了一个**循环**。  
那有人（比如我）可能就会想，统计循环个数，求个 lcm 不就完事了？  
等等...那他给 $s$ 干什么？  
我们再看题面。  
> the string would become equal to its initial value for the first time.  

也就是说只要同一位置上字母和原来一样就行。继续举例子：  
$$s=[a,b,a,b]$$  
$$p=[2,3,4,1]$$  
唯一的一个环长度是 $4$，但是答案应该是 $2$。问题出在交换 $2$ 次之后第一个 `a` 和第二个 `a` 互换了位置，而在字符串上不会体现效果。于是，我们要对每个环随意拆开并求最短重复子串的长度，就比如 `abab` 的最短重复子串是 `ab`。  
最短重复子串的定义是，对于 $s=[c_1,c_2,...,c_n]$ 和 $i|n$，满足对于任意的 $1\le j\le n-i$（这里是为了避免越界，否则应该对所有 $1\le j\le n$）满足 $s_j=s_{j+i}$。这就相当于，操作 $i$ 次后这 $n/i$ 个子串被轮换了位置，但是都是相同的，所以就会回来。  
那么我们怎么找这个子串呢？我们注意到 $n$ 只有 $200$，所以可以暴力查找，具体就是枚举每个可能的长度（枚举 $i^2\le n,\;i|n$，那么 $i,\;n\div i$ 就是两个可能的长度），用 $substr$ 或类似的方式提取一个子串，然后重复 $n\div len$ （$len$ 是子串长度）次，和原串比较即可。  
还是那个 `abab` 的例子。当我判断 $1$ 的时候提取了 `a` 重复后变成 `aaaa`，和原串不同。
判断 $2$ 时提取了 `ab`，重复后变成 `abab`，和原串相同。可以证明没有更小的答案。  
最后对于所有循环的最短重复子串长度求一个最小公倍数，就结束啦~  
至于为啥，最小公倍数是所有周期的倍数，那么轮换这么多次一定会回到原来的，都说了“最小”就一定是符合答案的最小的。  
最小公倍数我顺便提一句，$\text{lcm}(a,b)=a/\gcd(a,b)*b$。如果先乘后除可能越界（即使是ll）所以我喜欢这种写法。$\gcd$ 直接用 C++ 提供的 __gcd 函数就可以。

这里来补充证明一下为什么可以随意拆开。对于任意的字符串，有长度为 $i$ 的最短重复子串长，排布成一个环，再拆开，任意一对本来之前距离是 $i$ 整数倍的相同字符之后的距离一定也是 $i$ 整数倍，因为其中间的字符个数永远模 $i$ 余 $i-1$，符合前面的定义。  

所以找环的时候对于所有没有记录过的点开始，不断地跳到 $p_i$，向字符串内（初始有 $s_i$） $s_{p_i}$，然后再记录 $p_i$，直到跳回 $i$ 为止。

**2. 代码**  
说了这么多，放个代码就溜了
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
#define maxn 205

using namespace std;

int a[maxn], vis[maxn];

inline string repeat(string x, int y) { //因为懒写一个函数，计算把 x 重复 y 次后得到的字符串
	string res = "";
	for(int i = 0; i < y; i++) res += x;
	return res;
}

int minr(string s) { //这个是计算最短重复字串长度用的
	int len = s.size();
	int ans = 0x3f3f3f3f;
	for(int i = 1; i * i <= len; i++) {//使用i*i可以避免TLE，对于所有 len 的因数i1，i1和n/i1一定有一个小于等于根号len
		if(s.size() % i != 0) continue; 
		if(repeat(s.substr(0, i), len / i) == s) {
			ans = min(ans, i);
		}
		if(repeat(s.substr(0, len / i), i) == s) {
			ans = min(ans, len / i);
		}
	}
	return ans;
}

string s;

string srch(int i) {//search，一步一步跳，拼接字符串的函数
	string res = "";
	res += s[i];
	vis[i] = true;
	for(int j = a[i]; j != i; j = a[j]) {
		res += s[j];
		vis[j] = true;
	}
	return res;
}

int solve2(int a, int b) {//其实就是求lcm
	return a / __gcd(a, b) * b;
}

void solve() {//多测
	int ans = 1;
	int n;
	scanf("%lld %lld", &n);
	cin >> s;
	s = " " + s;
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		vis[i] = 0;
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			ans = solve2(ans, minr(srch(i)));
		}
	}
	printf("%lld\n", ans);
}

signed main() {
	int t;
	scanf("%lld", &t);
	while(t--) {
		solve();
	}
}
```

---

## 作者：zhouyuhang (赞：0)

严格线性做法。该做法可能有蓝。

显然可以将一个置换拆成许多不相交的轮换。因此只需求解 $p=(2,3,4,…,n,1)$ 时的问题。以下所有内容均为求解该问题的方法。

令
$$
\quad
f=\begin{pmatrix} 1 & 2 & … & n-1 & n\\ 2 & 3 & … & n & 1\end{pmatrix}
\quad
$$
则 $k$ 次操作的结果为 $s\circ f^k$。现在考虑 $s\circ f^k=s$ 意味着什么。注意到，$s\circ f^k$ 实际上是将 $s$ 左移了 $k$ 位，即 $s\circ f^k={\rm merge}(s[k+1…n],s[1…k])$。有因为 $s\circ f^k = s$，所以就有 
$$
{\rm merge}(s[1…n-k],s[n-k+1…n])=s={\rm merge}(s[k+1…n],s[1…k])
$$

观察上式，可以发现我们只需要枚举 $k$。如果 $k$ 满足 
1. $s[1…n-k]=s[k+1…n]$。
2. $s[1…k]=s[n-k+1…n]$。

那么 $k$ 就满足 $s\circ f^k=s$。这两个条件的判断可以使用子串哈希，也可以使用 KMP。稍微描述一下 KMP 的做法：在处理出 $s$ 的前缀函数 $\pi$ 之后，考虑从字符串末尾不断沿着 $\pi_i$ 回跳，直到开头，并给沿途中遍历到的每个位置打上标记。显然，被标记过的位置就是所有满足 $s[1…k]=s[n-k+1…n]$ 的 $k$。那我们只需要在枚举时查看 $k$ 和 $n-k$ 是否都被标记过即可。复杂度 $O(n)$。

做完了？

实际上并没有。问题在于一开始将置换拆成许多轮换后，正常想法是取所有轮换的答案的 $\rm lcm$。在 $s$ 是一个排列时，这样做没啥毛病。但是为什么 $s$ 变成一个字符串之后这个方法还是对的捏？实际上，这是因为一个小结论的成立。

Lemma I：对于任意  $s\circ f^k=s,s\circ f^{ik}=s$。 

Proof：废话。

Lemma II：$s\circ f^n=s$。

Proof：废话。

Lemma III：对于最小的 $k>0$ 满足 $s\circ f^k=s$，有 $k\mid n$。

Proof：反证。假设 $k\nmid n$，则 $n=qk+r$（$0<r<k$）。那么有 $s=s\circ f^n=s \circ f^{qk}\circ f^r=s\circ f^r$。但这与 $k$ 是最小的满足要求的数相矛盾。所以必有 $k\mid n$，证毕。

由 Lemma III 可以看出，任何一种可行解必是最小解的倍数，所以直接对所有轮换的最小解取 $\rm lcm$ 就是正确的做法。

似乎跟群论有一些微妙的关系。奈何作者的数学水平有限，只能摆了。

其实如果注意到 Lemma III 暴力也可以做到 $O(n\sqrt n)$。当然，直接 $O(n^2)$ 也可以过，但是并不优美。

---

## 作者：让风忽悠你 (赞：0)

## 题意

给出一个长度为 $n$ 的字符串，并给出一个长度为 $n$ 的排列 $p$，你可以做若干次操作，定义每次操作为 将 $i$ 位置的字符换为这次操作前位置为 $p_i$ 的字符，要求最少需要多少次操作能够使字符串为原来的字符串。

## 做法

首先最容易想到的就是找到每一个环，然后取每个环的大小的最小公倍数，但是会发现连样例都过不了。

注意题目中要求的只是让字符串与原字符串相同，那么我们就可以将该环中字符串的循环节视作其大小，然后对所有取出来的大小取最小公倍数。考虑到数据范围偏小，这里直接用暴力找的循环节。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define N 205
#define int long long // 要开ll

using namespace std;

int T,n,ans;
int to[N];
bool vis[N];
char s[N];

int get(int x){
	string st="";
	int k=x,size=1;
	bool fl;
	
	while(to[k]!=x){
		st+=s[k];
		vis[k]=1;
		k=to[k];
		++size;
	}
	
	vis[k]=1;
	st+=s[k];
	
	int len=st.size();
	
	for(int i=1;i<=len;i++){
		if(len%i) continue;
		fl=0;
		
		for(int j=0;j<len;j++)
			if(st[j]!=st[j%i])
				fl=1;
				
		if(!fl) return i;
	} // 找循环节
}

int gcd(int a,int b){
	if(!b) return a;
	return gcd(b,a%b); 
}

signed main(){
	scanf("%lld",&T);
	
	while(T--){
		ans=1;
		memset(vis,0,sizeof(vis));
		scanf("%lld",&n);
		scanf(" %s",s+1);
		
		for(int i=1;i<=n;i++)
			scanf("%d",&to[i]);
		
		for(int i=1;i<=n;i++){
			if(vis[i]) continue;
			int num=get(i);
			
			ans=ans*num/gcd(ans,num); // 取最小公倍数
		}
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
```


---

