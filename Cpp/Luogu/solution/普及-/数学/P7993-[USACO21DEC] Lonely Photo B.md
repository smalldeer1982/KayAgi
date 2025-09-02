# [USACO21DEC] Lonely Photo B

## 题目描述

Farmer John 最近购入了 $N$ 头新的奶牛（$3 \le N \le 5 \times 10^5$），每头奶牛的品种是更赛牛（Guernsey）或荷斯坦牛（Holstein）之一。 

奶牛目前排成一排，Farmer John 想要为每个连续不少于三头奶牛的序列拍摄一张照片。 然而，他不想拍摄这样的照片，其中只有一头牛的品种是更赛牛，或者只有一头牛的品种是荷斯坦牛——他认为这头奇特的牛会感到孤立和不自然。 在为每个连续不少于三头奶牛的序列拍摄了一张照片后，他把所有「孤独的」照片，即其中只有一头更赛牛或荷斯坦奶牛的照片，都扔掉了。

给定奶牛的排列方式，请帮助 Farmer John 求出他会扔掉多少张孤独的照片。如果两张照片以不同的奶牛开始或结束，则认为它们是不同的。


## 说明/提示

【样例解释】

这个例子中的每一个长为 3 的子串均恰好包含一头更赛牛或荷斯坦牛——所以这些子串表示孤独的照片，并会被 Farmer John 扔掉。所有更长的子串（GHGH、HGHG 和 GHGHG）都可以被接受。

【数据范围】

- 测试点 2-4 满足 $N \le 50$。
- 测试点 5-10 满足 $N \le 5000$。
- 测试点 11 没有额外限制。

注意这个测试点的答案可能无法用标准的 32 位整数型存储，你可能需要使用更大的整数类型（例如，C++ 中 64 位的 "long long int" 类型）。

## 样例 #1

### 输入

```
5
GHGHG```

### 输出

```
3```

# 题解

## 作者：ynxynx (赞：17)

方法1:

时间复杂度$O(n^2)$

每次对于一个点枚举两端的牛的个数再乘起来

期望得分:90(当然我同学改数据前卡过AC)

方法2:

时间复杂度$O(n)$

example:

$|GGG|HHHHH|GGG|H|$

将连续的牛合成一个块

如果一个块只有一个牛,我们就把他两边综合一下:
```
ans=ans+a[i+1]*a[i-1]+a[i+1]-1;
```

如果有至少两个,我们只看他右边的牛:
```
ans=ans+a[i+1]+a[i]-2;
```
期望得分:100

```上代码
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗
using namespace std;
int a[10000001],n,ans,cnt;
char ch[10000001];
signed main(){
	scanf("%lld %s",&n,ch);
	a[++cnt]++;
	for (int i=1;i<n;i++){//分成几块
		if (ch[i]==ch[i-1]) {
			a[cnt]++;
		}
		else a[++cnt]++;
	}
	for (int i=1;i<cnt;i++){//递推公式
		if (a[i]==1) ans=ans+a[i-1]*a[i+1]+a[i+1]-1;
		else ans=ans+a[i]+a[i+1]-2;
	}
	printf("%lld",ans);//完美结束
}
```

---

## 作者：徐晨轩✅ (赞：16)

~~这题窝想了 2h 才出正解~~

大致思路是这样的：扫描每一头牛，计算出这头牛是“孤独的”的照片有多少张，加到 `ans` 里头去。最后输出 `ans`。有人担心这种方法会重复计算，实际上是不会的。因为每张照片都只会有唯一的一只牛是“孤独的”，也就是说这张照片只会被这只“孤独的”牛计算一遍。

那么重点来了，怎么算呢？？

我们可以再计算前先处理四个数组：`LG[],RG[],LH[],RH[]`。这四个数组的第 $i$ 位分别表示：第 $i$ 头牛左边有几头**连续的**更赛牛，第 $i$ 头牛右边有几头**连续的**更赛牛，第 $i$ 头牛左边有几头**连续的**荷斯坦牛，第 $i$ 头牛右边有几头**连续的**荷斯坦牛。在计算答案时，对于每头牛（假设这头牛是更赛牛，荷斯坦牛类似），考虑以下两种情况：

1. 这头牛是在照片里的最左边或最右边。这种情况可以加上 `LH[i]?LH[i-1]:0+RH[i]?RH[i+1]:0`（`-1` 或 `+1` 是为了避免 `len==2` 的情况），画图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/giot2lbx.png)

2. 这头牛实在照片里的中间。这种情况可以加上 `LH[i]*RH[i]`，画图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2vefcxrn.png)

将这两个加起来就行了。

AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=500001;
int n,l=1,r=1,ans,LG[N],RG[N],LH[N],RH[N];
string s;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> s;s=" "+s;
	for(int i=2;i<=n;i++)
		LG[i]=s[i-1]=='G'?LG[i-1]+1:0;
	for(int i=n-1;i>=1;i--)
		RG[i]=s[i+1]=='G'?RG[i+1]+1:0;
	for(int i=2;i<=n;i++)
		LH[i]=s[i-1]=='H'?LH[i-1]+1:0;
	for(int i=n-1;i>=1;i--)
		RH[i]=s[i+1]=='H'?RH[i+1]+1:0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='H')
		{
			if(LG[i])ans+=LG[i-1];
			if(RG[i])ans+=RG[i+1];
			ans+=LG[i]*RG[i];
		}
		else
		{
			if(LH[i])ans+=LH[i-1];
			if(RH[i])ans+=RH[i+1];
			ans+=LH[i]*RH[i];
		}
//		cout << ans << endl;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：5)

首先时最简单的做法，两层循环逐一判断，时间复杂度为 $O(n^2)$。但是现在无法通过最后一个数据点，需要优化程序。

对于一个从 $i$ 开始的情况，首先用一次二分找到最远的点符合只出现 `H` 或 `G` 的情况，设为 $l$。然后再用一次二分找到最远的点符合该区间内只有一个 `H` 或一个 `G` 的情况，设为 $r$。那么由题目的意思可知，$[i,n]$ 的区间对答案的贡献为 $r - (l + 1) + 1 = r - l$。注意题目的限制，连续的区间，长度不小于 $3$，因此一些特殊的地方要进行特判。这样，时间复杂度就降到了 $O(n \log n)$，可以通过本题。

接下来给一下代码：（思路有点奇怪嘿嘿）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 5e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,a[MAX],b[MAX];
ll ans;
char str[MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	scanf ("%s",str + 1);
	for (int i = 1;i <= n;++i)
	{
		if (str[i] == 'G') a[i] = a[i - 1] + 1,b[i] = b[i - 1];
		else a[i] = a[i - 1],b[i] = b[i - 1] + 1;
	}//前缀和维护一段区间里 G 或 H 的个数
	for (int i = 1;i <= n;++i)
	{
		int l = i + 2,r = n,st,end;
		if (l > r) break;
		while (l <= r)//第一次二分找到 l，st = l + 1
		{
			int mid = (l + r) >> 1;
			if (a[mid] - a[i - 1] == mid - i + 1 || b[mid] - b[i - 1] == mid - i + 1) l = mid + 1;
			else r = mid - 1;
		}
		--l;
		if (l < i + 2) st = i + 2;//特殊情况
		else st = l + 1;
		l = st,r = n;
		while (l <= r)//第二次二分找到 end = r
		{
			int mid = (l + r) >> 1;
			if (a[mid] - a[i - 1] == 1 || b[mid] - b[i - 1] == 1) l = mid + 1;
			else r = mid - 1;
		}
		--l;
		end = l;
		ans += end - st + 1;//累计贡献
	}	
	printf ("%lld\n",ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：rzh123 (赞：4)

# P7993 题解  

题目链接：[P7993 \[USACO21DEC\] Lonely Photo B](https://www.luogu.com.cn/problem/P7993)  

## 90 分做法：前缀和  

很容易想到前缀和，用两个数组分别存储 `G` 和 `H` 的前缀和，时间复杂度 $O(n^2)$，能过前十个点。  

**爸特，$3 \le N \le 5 \times 10^5$，刚才的做法显然爆了。**  

## 100 分做法：数学  

（以 `G` 为例，`H` 同理）  

有哪些照片中只有一个 `G`？  

分类讨论：  

### 1.`G` 开头或结尾  

如果一个 `G` 与后一个 `G` 之间有 $x (x \ge 2)$ 个 `H`，就有 $x-1$ 张照片会被扔掉，长度分别为 $3 \sim (x+1)$。  
与前一个之间同理。  

### 2.中间有 `G`  

如果一个 `G` 前后各有大于一个 `H`，这张照片就会被扔掉。  
如果一个 `G` 之前有 $a$ 个 `H`，之后有 $b$ 个 `H` $(a,b \ge 1)$，根据数学里的乘法原理，会有 $a \times b$ 种情况。  

分析完了。  

程序可以先预处理出每一头牛与前一个、后一个同类之间的距离，再代入以上公式计算。  

时间复杂度 $O(n)$。  

AC 代码：  

```cpp
#include <cstdio>
#define N 500007
typedef long long unsigned llu;
int n;
char t[N];
llu c;
llu a[N],b[N];
int g,h; 
int main(){
	scanf("%d%s",&n,t+1);
	g=h=0;
	for(int i=1;i<=n;++i){
		if(t[i]=='G'){
			a[i]=b[g]=i-g-1;
			g=i;
		}
		else{
			a[i]=b[h]=i-h-1;
			h=i;
		}
	}
	b[g]=n+1-g-1,
	b[h]=n+1-h-1;
	for(int i=1;i<=n;++i){
		if(a[i]>=2){
			c+=a[i]-1;
		}
		if(b[i]>=2){
			c+=b[i]-1;
		}
		if(a[i]>=1&&b[i]>=1){
			c+=a[i]*b[i];
		}
	}
	printf("%llu\n",c);
	return 0;
}
```  

[AC 记录](https://www.luogu.com.cn/record/65653122)

---

## 作者：cwfxlh (赞：4)

# P7993
### 题意：  
这道题就是说，有多少个长度大于 3 的区间内， G 或 H 只有一个。  
____
### 算法一：  
首先很容易想到的是，从 1 到 n 遍历区间起点，里面再套一层循环，遍历终点，但明显超时。并且这个办法也很难再优化了，即使使用二分查找可行的终点，依旧会超时，所以应该换一条路。  
____
### 算法二：  
一张孤独的照片里，一定有一种奶牛是孤独的，也就是说，与这头奶牛同种的奶牛都不在照片中。进一步，我们可以根据两个种类建立两个双向链表，记录一下，一个奶牛前后的两只同种奶牛到底在哪里，拍照的时候，只需要确定，这只奶牛在照片里，但是它前后两只奶牛都不在这里面。  
____
### 例子：  
GHGHG  
那么当 3 号奶牛是孤独的，可行的拍照范围就在 2 到 4 之间了，就只有一种。枚举每一个奶牛是孤独的情况有多少种就可以了，而且不会出现重复的情况，乘法原理加起来就可以了。
____
###  AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,G,H;
long long ans;
string s;
long long nxt[600003],fnxt[600003],lastG=-1,lastH=-1;
int main()
{
	cin>>n>>s;
	for(int i=0;i<s.length();i++)
	{
		nxt[i]=s.length();//nxt 下一只同种奶牛
		fnxt[i]=-1;//fnxt 上一只同种奶牛
		if(s[i]=='G')
		{
			if(lastG!=-1)
			{
				nxt[lastG]=i;
				fnxt[i]=lastG;
			}
			lastG=i;
		}
		else
		{
			if(lastH!=-1)
			{
				nxt[lastH]=i;
				fnxt[i]=lastH;
			}
			lastH=i;
		}
	}
	for(int i=0;i<s.length();i++)
	{
		if(nxt[i]-i>2)
		{
			ans+=nxt[i]-i-2;//实际情况需要多打几种特殊情况的判定
		}
		if(i-fnxt[i]>2)
		{
			ans+=i-fnxt[i]-2;
		}
		if(nxt[i]-1-(fnxt[i]+1)>=2)
		{
			ans+=(nxt[i]-1-i)*(i-(fnxt[i]+1));
		}
	}
	cout<<ans;
	return 0;
}
```
### 结尾：  
祝大家在 USACO 中取得好成绩！！！

---

## 作者：Leonid (赞：2)

[原题](https://www.luogu.com.cn/problem/P7993)

数据范围是 $n\in[3,5\times 10^5]$ 的，暴力 $\Theta(n^2)$ 过不了。

考虑 $\Theta(n)$ 的递推。

把连续相同的牛合并，然后分类讨论。

**1. 一个块中只有一头牛**

把左右两个块里的牛结合，根据乘法原理算出孤独的照片数量，并舍去不到三头牛的照片。

$$ans=ans+pre_{i+1}\times pre_{i-1}+pre_{i+1}-1$$

**2. 一个块中有两头以上牛**

只考虑右边的块的牛，根据加法原理算出孤独的照片数量，并舍去不到三头牛的照片。

$$ans=ans+pre_{i+1}+pre_i-2$$

注意 long long。

```cpp
#include<cstdio>

using namespace std;

#define M 500005

long long n,pre[M],cnt;
char s[M];
long long ans;

int main(){
	scanf("%lld %s",&n,s);
	pre[1]=cnt=1;
	for(int i=1;i<n;++i)
		if(s[i]==s[i-1]) ++pre[cnt];
		else ++pre[++cnt];
	for(int i=1;i<cnt;++i)
		if(pre[i]==1) ans+=pre[i-1]*pre[i+1]+pre[i+1]-1;
		else ans+=pre[i]+pre[i+1]-2;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：andychen_2012 (赞：2)

## 一、解题思路

我们可以知道要扔掉的照片的字符串长度至少为3。

那么我们可以先看看长度为3的字符串可能有哪些。

GGG HHH GHG HGH GGH HHG HGG GHH

那么我们可以分情况讨论，上面的八种字符串其实可以分为两种情况：全都是同一种字符，有两种不同的字符。

#### 1、全都是同一种字符

设这种字符为 $x$，另一种字符为 $y$。

我们可以找到这一段字符串后第一个 $y$ 的位置 $pos0$，如果存在的话，我们再找到最近的且在 $pos0$ 后面的 $y$，设这个位置为 $pos1$，则答案加上 $pos1-pos0$。

为什么呢？

我们可以举个例子：

GGGGHGGH

那么对于最开始的GGG来说，答案应该是 $8-5=3$。

也就是说要被扔掉的照片应该是：

GGGGH GGGGHG GGGGHGG

大家自行理解一下。

#### 2、有两种不同的字符

设出现了一次的字符为 $x$，出现了两次的字符为 $y$。

设这一段字符串结尾的位置为 $pos0$。

我们可以找到这一段字符串后第一个 $x$ 的位置，设为 $pos1$。

那么答案加上 $pos1-pos0$。

我们再举一个例子：

GHGGGGHG

那么对于最开始的GHG来说，答案应该是 $7-3=4$。

也就是说要被扔掉的照片应该是：

GHG GHGG GHGGG GHGGGG

### 总结

我们可以先做一个预处理，把每一个字符的后面的第一个与它相同的字符和与它不同的字符的位置分别用两个数组 $nxt$ 与 $pos$ 记录下来。

然后载进行一次对整个字符串的便利，对每一个长度为三的字符段进行答案计算，把对于每一个字符段来说的答案累加在一起就是最终的答案了。

## 二、解题代码

```cpp
#include<cstdio>
int n;
char s[500005];
int pos[500005],nxt[500005];
int g[500005],h[500005];
typedef long long ll;
int main(){
	scanf("%d%s",&n,s);
	//预处理与当前字符不同的字符的位置，要从后往前搜，因为是存后面第一个与它不同的字符的位置 
	int x=n;
	pos[n]=n;
	char lst=s[n-1];
	for(int i=n-1;i>=0;--i){
		if(s[i]!=lst){
			pos[i]=x;
			lst=s[i];
			x=i;
		}
		else{
			pos[i]=pos[i+1];
			x=i;
		}
	}
	//用两个数组将两种字符分别存储下来，以便找出每一个字符的下一个与之相同的字符的位置 
	int cnt1=0,cnt2=0;
	for(int i=0;i<n;++i){
		if(s[i]=='G')
			g[++cnt1]=i;
		else
			h[++cnt2]=i;
	}
	for(int i=1;i<cnt1;++i)
		nxt[g[i]]=g[i+1];
	nxt[g[cnt1]]=n;  //注意要将最后的下一个字符指向n，因为此时是没有下一个字符的 
	for(int i=1;i<cnt2;++i)
		nxt[h[i]]=h[i+1];
	nxt[h[cnt2]]=n;
//	for(int i=0;i<n;++i)
//		printf("%d ",pos[i]);
	ll ans=0;
	for(int i=0;i<n-2;++i){
		if(s[i]!=s[i+1]&&s[i]!=s[i+2]){
			ans+=nxt[i]-i-2;
		}
		else if(s[i+1]!=s[i]&&s[i+1]!=s[i+2]){
			ans+=nxt[i+1]-i-2;
		}
		else if(s[i+2]!=s[i]&&s[i+1]!=s[i+2]){
			ans+=nxt[i+2]-i-2;
		}
		else{
			int y=pos[i+2];
			if(y==n) continue;
			int z=nxt[y];
			ans+=z-y;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：lsj2009 (赞：2)

[更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/solution-p7993)
## 题目大意
在仅包含字符 H 和 G 的字符串 $s$ 中，有多少个子串：

- 包含一个 H，包含至少两个 G；
- 包含一个 G，包含至少两个 H。

满足要求。

## 思路
第一反应是枚举字符串左端点 $l$，右端点 $r$，然后统计在 $[l,r]$，范围内 G 和 H 分别出现的次数。时间复杂度 $Θ(n^3)$，前缀和优化后 $Θ(n^2)$，面对 $n \le 5 \cdot 10^5$ 的数据范围望而生畏。

既然打暴力行不通，那么只能考虑数学解法：

仔细观察满足条件的子串要求，发现了什么？****有一个字符只出现一次****！

根据这个条件，我们可以设计出合理的算法：****枚举满足要求的子串中心点 $s_i$**** （即只出现一次的那个字符的位置）。如果它可以像左拓展至 $l$（即 $s_{l-1}=s_i$），可以像右拓展至 $r$（即 $s_{r+1}=s_i$），那 ****端点在 $[l,r]$ 之间且经过 $i$ 的子串（长度 $len \ge 3$）均满足要求！****

最坏情况时间复杂度 $Θ(n^2)$，预处理每个 $i$ 的 $l$ 和 $r$ 后 $Θ(n)$，完美通过此题。

更多细节在代码中展示。
## AC CODE：
```cpp
#include<bits/stdc++.h>
#define int long long //注意这个测试点的答案可能无法用标准的 32 位整数型存储
using namespace std;
const int N=5e5+5;
int pre[N],nxt[N],n,ans;
signed main() {
	string s;
	cin>>n>>s;
	int preH=-1,preG=-1; //左端点初值默认-1
	for(int i=0;i<s.size();i++) { //预处理l
		if(s[i]=='H') pre[i]=preH,preH=i;
		if(s[i]=='G') pre[i]=preG,preG=i;
	}
	int nxtH=n,nxtG=n; //右端点初值默认n
	for(int i=s.size()-1;i>=0;i--) { //预处理r
		if(s[i]=='H') nxt[i]=nxtH,nxtH=i;
		if(s[i]=='G') nxt[i]=nxtG,nxtG=i;
	} 
	for(int i=0;i<s.size();i++) {
		ans+=(i-pre[i])*(nxt[i]-i)-1;
		/*根据乘法原理，端点在[l,r]之间且经过i的子串个数为左可拓展长度*右可拓展长度*/
		if(nxt[i]!=i+1) --ans; //处理长度小于3的子串
		if(pre[i]!=i-1) --ans;
	} 
	printf("%lld",ans);
	return 1;
}

```
完美撒花！

---

## 作者：Eason_AC (赞：2)

[Advertisement](https://www.cnblogs.com/Eason-AC/p/15718313.html)

## Content
有一个长度为 $n$ 的字符串 $s$，仅包含两种字符：`G` 和 `H`。定义字符串 $s'$ 是孤独的，当其仅当 $s'$ 中恰好只有一个 `G` 或 `H` 且 $|s'|\geqslant 3$。例如，字符串 `GHGGG`、`GHHHH` 是孤独的，而字符串 `GH`、`GHGHG` 不是。现在，请你求出 $s$ 的所有孤独的子串的个数。

**数据范围：$n\leqslant 5\times 10^5$。**
## Solution
我们很容易想到一个 $\mathcal O(n^2)$ 的做法，即暴力模拟每个子串并判断其是否是孤独的。但是有没有更优的方法？确实有。我们可以先预处理出当前字符前面、后面有多少个连续的与当前字符不同的字符，设在 $i$ 位置上的字符前面连续的与当前字符不同的字符有 $\textit{bef}_i$ 个，后面连续的与当前字符不同的字符有 $\textit{aft}_i$ 个。那么，我们就可以对于每个位置直接算其对答案的贡献就好了。具体地，对于当前位置 $i$：

- 如果 $\textit{bef}_i>0$ 且 $\textit{aft}_i>0$，那么当前位置对答案的贡献加上 $\textit{bef}_i\cdot\textit{aft}_i$。
- 如果 $\textit{bef}_i>1$，那么那么当前位置对答案的贡献加上 $\textit{bef}_i-1$。
- 如果 $\textit{aft}_i>1$，那么那么当前位置对答案的贡献加上 $\textit{aft}_i-1$。

综上，当前位置 $i$ 对答案的贡献是 $\textit{bef}_i\cdot\textit{aft}_i+\max(0,\textit{bef}_i-1)+\max(0,\textit{aft}_i-1)$。

由此，我们将算法优化到了 $\mathcal{O}(n)$，就可以通过这道题目了。
## Code
赛时代码。
```cpp
namespace Solution {
	const int N = 5e5 + 7;
	int n, cntg, cnth, g[N], h[N], numg[N], numh[N], bef[N], aft[N];
	char a[N];
	
	iv Sub1_work() {
		ll ans = 0;
		F(int, i, 1, n) {
			if(i <= n - 2 && ((a[i] == 'G' && a[i + 1] == 'H' && a[i + 2] == 'H') || (a[i] == 'H' && a[i + 1] == 'G' && a[i + 2] == 'G'))) {
				int cur = i + 2;
				for(; cur < n && a[cur + 1] == a[i + 2]; cur++);
				ans += (cur - (i + 2) + 1);
			}
			if(i > 1 && i < n && ((a[i] == 'G' && a[i - 1] == 'H' && a[i + 1] == 'H') || (a[i] == 'H' && a[i - 1] == 'G' && a[i + 1] == 'G'))) {
				int curl = i - 1, curr = i + 1;
				for(; curl > 1 && a[curl - 1] == a[i - 1]; curl--);
				for(; curr < n && a[curr + 1] == a[i + 1]; curr++);
				ans += 1ll * ((i - 1) - curl + 1) * (curr - (i + 1) + 1);
			}
			if(i >= 3 && ((a[i] == 'G' && a[i - 1] == 'H' && a[i - 2] == 'H') || (a[i] == 'H' && a[i - 1] == 'G' && a[i - 2] == 'G'))) {
				int cur = i - 2;
				for(; cur > 1 && a[cur - 1] == a[i - 2]; cur--);
				ans += ((i - 2) - cur + 1);
			}
		}
		write(ans);
	}
	iv Sub2_work() {
		F(int, i, 1, n) if(a[i] == 'G') g[++cntg] = i, numg[i] = cntg;
		F(int, i, 1, n) if(a[i] == 'H') h[++cnth] = i, numh[i] = cnth;
		int cnt = 0;
		F(int, i, 1, n) {
			if(a[i] == 'G') cnt++;
			else {
				bef[i] = cnt;
				if(numh[i] != 1) aft[h[numh[i] - 1]] = cnt;
				cnt = 0;
			}
		}
		aft[h[cnth]] = cnt, cnt = 0;
		F(int, i, 1, n) {
			if(a[i] == 'H') cnt++;
			else {
				bef[i] = cnt;
				if(numg[i] != 1) aft[g[numg[i] - 1]] = cnt;
				cnt = 0;
			}
		}
		aft[g[cntg]] = cnt;
		ll ans = 0;
		F(int, i, 1, n) {
			ans += 1ll * bef[i] * aft[i];
			if(bef[i] >= 2) ans += bef[i] - 1;
			if(aft[i] >= 2) ans += aft[i] - 1;
		}
		write(ans);
	}
	
	iv Main() {
		read(n), scanf("%s", a + 1);
		if(n <= 5000) Sub1_work();
		else Sub2_work();
		return;
	}
}
```

---

## 作者：xxasmcd (赞：2)

解题过程如下。

1. 用两个结构体来维护，对于每一个结构体都设两个量来分辨两种奶牛,last 来分别记录上一个两种奶牛出现的位置,nxt 来分别记录下一个两种奶牛出现的位置。

1. 对于每一头奶牛，把他左边的奶牛位置和他右边的奶牛位置通过两个结构体确定，然后和当前这头奶牛的位置做差相乘即可，但要注意需要减去不足三头奶牛的情况。

1. 这道题的坑点会爆 int，需要用 long long。


1. 代码附有注释可参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[500005],sum[500005];//需要设long long，会爆int
char c[500005];
struct node
{
	long long g,h;
}last[500005],nxt[500005];
long long ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
    {
		cin>>c[i];
	}
		last[1].g=last[1].h=0;//设立初始值
		for(int i=2;i<=n;i++)//用来记录上一头两种奶牛的位置
		{
			if(c[i-1]=='G')
            {
				last[i].g=i-1;
				last[i].h=last[i-1].h;
			}
			else
			{
				last[i].h=i-1;
				last[i].g=last[i-1].g;
			}
		}
		nxt[n].g=nxt[n].h=n+1;
		for(int i=n-1;i>=1;i--)//用来记录下一头两种奶牛的位置
		{
			if(c[i+1]=='G')
            {
				nxt[i].g=i+1;
				nxt[i].h=nxt[i+1].h;
			}
			else
			{
				nxt[i].h=i+1;
				nxt[i].g=nxt[i+1].g;
			}
		}
		for(int i=1;i<=n;i++)
		{
			long long num=0;
			if(c[i]=='G')
			{
				num=(nxt[i].g-i)*(i-last[i].g);//做差乘积
				if(num>3)//去掉不足三头奶牛的情况
				{
					ans+=num-3;
				}
			}
            else
            {
				num=(nxt[i].h-i)*(i-last[i].h);//做差乘积
				if(num>3)
				{
					ans+=num-3;//去掉不足三头奶牛的情况
				}
			}
		}
		cout<<ans;
	return 0;
}
```



---

## 作者：Ginger_he (赞：1)

# 题目描述
给定一个长度为 $n$ 的字符串 $s$，求 $s$ 中有多少个长度至少为 $3$ 且只含有一个字符 'H' 或 'G' 的字串
# 题解
因为计算 'H' 和 'G' 的方法是一样的，所以下面只讨论有一个 'H' 的情况。  
假设某个 'H' 前面有 $x$ 个连续的 'G'，后面有 $y$ 个连续的 'G'。  
### $x$ 和 $y$ 均为 $0$
不存在含有这个 'H' 的字串。  
### $x$ 和 $y$ 中有且仅有一个为 $0$
不妨假设 $y$ 为 $0$，则我们可以从这个 'H' 前面选 $2,3,…,x$ 个 'G' 构成符合条件的字串。因此，对于这种情况，共有 $(x+y-1)$ 个包含这个 'H' 的字串。  
### $x$ 和 $y$ 均不为 $0$
情况a. 从左边和右边各选一个 'G'，共有 $(x\times y)$ 个符合条件的字串。  
情况b. 只从一边选，回到上面那种分类，共有 $(x+y-2)$ 个符合条件的字串。  
综上，对于这种情况，共有 $(x\times y+x+y-2)$ 个包含这个 'H' 的字符串。  
### 实现
把每个 'H' 的位置记录下来，然后计算出每个 'H' 前面和后面的 'G' 的个数，再用上面的计算方法即可。  
**再次说明，'G' 和 'H' 的计算方法是一样的。**
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+5;
int n;
char s[maxn];
ll calc(char c)
{
    vector<int> v;
    for(int i=1;i<=n;i++)
    {
        if(s[i]==c)
            v.push_back(i);
    }
    ll x,y,res=0,m=v.size()-1;
    for(ll i=0;i<=m;i++)
    {
        if(!m) x=v[i]-1,y=n-v[i];//s中只有一个c 
        else if(!i) x=v[i]-1,y=v[i+1]-v[i]-1;//第一个c 
        else if(i==m) x=v[i]-v[i-1]-1,y=n-v[i];//最后一个c 
        else x=v[i]-v[i-1]-1,y=v[i+1]-v[i]-1;//其他c 
        if(!x&&!y) continue;
        else if(!x||!y) res+=x+y-1;
        else res+=x*y+x+y-2;
        //分情况计算 
    }
    return res;
}
int main()
{
    scanf("%d\n%s",&n,s+1);
    printf("%lld\n",calc('H')+calc('G'));
    return 0;
}
```

---

