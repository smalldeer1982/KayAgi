# [Algo Beat Contest 001 C] Creating a Queue

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|    $\text{C - Creating a Queue}$    | $400$ |    [joe_zxq](https://www.luogu.com.cn/user/623577)    | [fanchuanyu](https://www.luogu.com.cn/user/706256) & [joe_zxq](https://www.luogu.com.cn/user/623577) | [joe_zxq](https://www.luogu.com.cn/user/623577) |    [remmymilkyway](https://www.luogu.com.cn/user/551981)     | [Link](https://www.luogu.com.cn/article/7r5l2cag) by [joe_zxq](https://www.luogu.com.cn/user/623577) |

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A$。

现在你需要用 $1\sim M$ 之间的正整数替换所有序列 $A$ 中的 $0$，使得对于其中的任何一段长度大于等于 $2$ 的子数组，不能存在唯一众数。

> 子数组：在一个数组中，选择一些连续的元素组成的新数组。
>
> 唯一众数：众数指的是一个数字序列中出现次数最多的元素。如果一个数字序列众数只有一个，我们称这个序列有唯一众数。

求有多少种不同方案，答案对 $1145141923$ 取模。两种方案称为不同，当且仅当替换后的序列至少有一位上的数不同。

## 说明/提示

#### 样例解释 #1

有 $2$ 个满足条件的序列，分别为 $\{1,2\}$ 和 $\{1,3\}$。

#### 样例解释 #2

序列已经完全固定，本身就是一种合法的序列，于是答案为 $1$。

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le N \le 10^6$，$1 \le M \le 10^9$，$0 \le A_i \le M$。

## 样例 #1

### 输入

```
2 3
1 0```

### 输出

```
2```

## 样例 #2

### 输入

```
4 1046
114 514 191 981```

### 输出

```
1```

# 题解

## 作者：Besheep (赞：4)

我们计序列 $A$ 中 $0$ 的个数为 $cnt$。

保证子数组不能存在唯一众数，不就是序列中的元素互不相等？

惊人的注意力。所以注意到有以下两种情况是无法构造成合法序列的：
- 序列 $A$ 中任意一项的个数**大于 $1$**。
- $m<cnt$，此时序列 $A$ 中至少有两项相同的数，不满足上一条。

不难发现，小于等于 $m$ 且未在序列 $A$ 中出现数字的个数为 $m-n+cnt$，我们要在剩余的 $cnt$ 个位置里去摆放这些数，于是问题便转化为求：
$$\large A^{cnt}_{m-n+cnt}$$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e6+10,mod=1145141923;
ll n,m,a[N],cnt,ans=1;
map<ll,bool>mp;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
		if(a[i]==0){
			cnt++;
			continue;
		}
		if(mp[a[i]]){
			cout<<0;
			return 0;
		}
		mp[a[i]]=1;
	}
    m-=n-cnt;
    for(int i=0;i<cnt;i++) ans=ans*(m-i)%mod;
    cout<<ans;
	return 0;
}
```

---

## 作者：fish_love_cat (赞：3)

首先容易发现，当子数组长度为 $2$ 时，该子数组内若出现相同值显然是错误的。

子数组长度为 $3$ 时同理。

那子数组为 $4$ 时的相同呢？这时进行讨论显然要在目前已知的位置都不能违反上述两条的前提下才有意义，我们只能假设子数组是这样的：$[x,0,0,x]$。

依题意得中间两位必须填相同值，然而此时却又违反了上述两条的结论。所以得到当子数组长度为 $4$ 时，该子数组内若出现相同值仍旧是错误的。

推广开来可得，一个序列合法当且仅当整个序列中不存在相同值。

那么这题极其好做，注意几个 corner case，比如 $M<N$。

代码不放了。

---

## 作者：yedalong (赞：2)

## Solution
这里有一个结论：一个符合要求的序列内是不会有相同的数的。  
这里简单证明一下。相邻的两个数是不可能相同的，长度为 $3$ 的序列内也是不可能有两个相同的数的。但是长度为 $4$ 的序列内呢？我们发现不管相等的数怎么分布，总是会违背以上的两个理论，因此长度为 $4$ 的序列内也不能有相同的数。长度大于 $4$ 的序列也能通过此方法推出，出现两个相等的数的这种情况是不可能出现的。  
讲到这里代码就很好写了，首先特判出现两个相同的数的情况，因为不合法，因此答案为 $0$。假设序列里不为 $0$ 的数个数为 $x$，那么对于第 $i$ 个 $0$，有 $M-x-(i-1)$ 种可能，因为前面 $i-1$ 个 $0$ 我们已经确定了它的值，那么就不能与它们相等。根据组合数学，可以得知最后的答案就为 $\prod\limits_{i=1}^x(M-x-i+1)\mod 1145141923$。  
## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1145141923;
map<int,int> cnt;
int n,m,a[1000005],ans=1;
signed main(){
    cin>>n>>m;
    for(int i = 1;i<=n;i++){
        cin>>a[i],cnt[a[i]]++;
        if(cnt[a[i]]>1&&a[i]!=0){
            cout<<0;
            return 0;
        }
    }
    sort(a+1,a+1+n);
    n=unique(a+1,a+1+n)-a-1;
    for(int i = 0;i<cnt[0];i++){
        ans=ans*(m-(n-1)-i)%mod;
    }
    cout<<ans;
}
```

---

## 作者：StormWhip (赞：2)

### 思路
首先给出结论：如果满足“其中的任何一段长度大于等于 $2$ 的子数组，不能存在唯一众数”，则该数组中的数必定**两两不同**。   
证明：假设 $a[i]$ 和 $a[j]$ 是满足 $a[i]=a[j]$ 中，$j-i+1$ 最小的（即 $i$ 和 $j$ 最接近的），若从 $a[i]$ 到 $a[j]$ 这一段子数组中众数不是唯一的，则一定存在至少一组 $i<p<q<j$，使得 $a[p]=a[q]$，这与假设矛盾，结论得证。  

### 代码
得出结论后代码就很简单了。  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,Mod=1145141923;
int n,m,p,ans=1;
unordered_map <int,int> t;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x==0) {p++;continue;}
		if(t[x]) {cout<<"0\n";return 0;}
		t[x]++;m--;
	}
	for(int i=m-p+1;i<=m;i++) ans=ans*i%Mod;
	cout<<ans<<"\n";
	return 0;	
}
```

---

## 作者：getchar_unlocked (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11681)

### 思路

先由小推，若序列 $A$ 长度为 $2$，那么这 $2$ 个数必定不同。再想若 $A$ 的长度为 $3$，那么这 $3$ 个数必定不相同。若 $A$ 长度为 $4$，可以将其划分为 $4$ 个不同的数或者 $2$ 组各 $2$ 个数，但显然这不可以，因为 $A$ 的子序列的众数会只出现 $1$ 个。所以得出了该序列的一个性质：序列中每个数互不相同。

于是先判断无解的情况：序列中有重复的数。

得到了这个性质，接着统计出 $A_i\ne0$ 的个数，记为 $X$。然后推导答案，第 $1$ 次可选 $M-X$ 个，第 $2$ 次可选 $M-X-1$ 个，第 $3$ 次可选 $M-X-2$ 个，第 $k$ 次可选 $M-X-k+1$ 个。最终将每一次可选个数想乘，所以 $\prod\limits_{i=X}^{N-1}(M-i)$ 为最终答案。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e6+10,MOD=1145141923;
int a[N];
unordered_map<int,bool>mp;
signed main(){
	int n=read(),m=read();
	if(n>m)
		return printf("0\n"),0;
	for(int i=1;i<=n;++i)
		a[i]=read();
	int cnt=0;
	for(int i=1;i<=n;++i){
		if(mp[a[i]]&&a[i])
			return printf("0\n"),0;
		mp[a[i]]=true;
		if(a[i])
			++cnt;
	}
	int ans=1;
	for(int i=cnt;i<n;++i)
		ans=ans*(m-i)%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

这能黄？

对于任何子数组都不存在唯一众数，即数组中元素互不相同，否则一定可以找到一组距离最近的相同元素，以这两个数为首尾的子数组一定不符合要求（因为这个子数组中除首尾元素外没有相同的元素，所以存在唯一众数）。

如果原数组中已经存在相同元素则答案为 $0$。

我们处理出原数组中 $0$ 的个数 $z$。若其大于 $m$，则我们填的数中必有相同的数，答案为 $0$；否则因为原数组中已经填了 $n-z$ 个数，答案为在 $m-(n-z)$ 个数中选择 $z$ 个数并按顺序填入的方案数，即 $A_{m-n+z}^z$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int mod=1145141923;
map<int,bool> mp;

int main(){
    int n,m;cin>>n>>m;
    int zr=0;
    for(int i=1; i<=n; i++){
    	int a;cin>>a;
		if(!a) zr++;
		else{
			if(mp[a]){
				cout<<0;
				return 0;
			}
			mp[a]=true;
		}
	}
	if(zr>m){
		cout<<0;
		return 0;
	}
    long long ans=1;
    for(int i=m-n+zr; i>=m-n+1; i--) ans=ans*i%mod;
    cout<<ans;
	return 0;
}
```

---

## 作者：M1__ (赞：1)

# 题解：P11681 [Algo Beat Contest 001 C] Creating a Queue
[题目传送门](https://www.luogu.com.cn/problem/P11681)
## 题目思路
### 形式化题意
- 用 $1\sim M$ 之间的正整数替换所有序列 $A$ 中的 $0$。
- 构造出的序列不能有重复的元素。
  - 证明：对于一个长度为 $2$ 的序列，如果这个序列满足上述要求，那么这个序列的众数个数应当等于序列长度。因此，这个序列没有重复的元素。
  - 当序列长度为 $3$ 时，如果有两个元素相同，显然这就是一个不符合题意的最短的子串。
  - 当序列长度为 $4$ 时同理。也就是说对于一个序列，如果有一个元素（不包括 $0$）的出现次数大度等于 $2$，那么不符合题意的子串会随着元素出现次数的增多而增多。
   - 证毕，推广开来，对于一个合法序列，这个序列中所有的非 $0$ 元素一定不会重复出现。显然这个时候方案数为 $0$。

对应地，当一个序列满足形式化题意中所说的要求时，方案数如下：
  - 首先要统计非 $0$ 元素的个数，令个数为 $n$。因为不允许有重复的元素，所以原本的方案数 $M$ 自然要减去 $n$。
  - 对于第 $i$ 个 $0$，因为前面的 $i-1$ 个 $0$ 早就用完了 $i-1$ 个方案数，因此方案数还要减去 $i-1$。
  - 因此，对于 $m$ 个 $0$，$n$ 个非 $0$ 元素，答案为：
    $$\prod _{i=1}^{m} (M-n-(i-1))\bmod 1145141923=\prod _{i=1}^{m} (M-n-i+1)\bmod 1145141923$$
## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1145141923;
const ll MAXN=1e6+10;
map<ll,ll>cnt;
ll n,m,a[MAXN],ans=1,sum=0,sum1=0;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
		cnt[a[i]]++;
        if(cnt[a[i]]>1&&a[i]!=0){
            cout<<0;
            return 0;
        }
    }
	for(int i=1;i<=n;i++){
		if(a[i]!=0) sum++;
		else sum1++;
	}    
    for(int i=1;i<=sum1;i++){
	    ans=ans*(m-sum-(i-1))%MOD;
	}
	cout<<ans;
}
```

---

## 作者：belif__kibo (赞：1)

#### 于2025/2/5进行修正，望审核大大通过~~~


---



# _一道带点思维量的数学题_ 

题意梗概：给定一个长为 $n$ 的序列，序列中的数均为不大于 $m$ 的正整数，已知的数均给出，未知的数用 $0$ 表示，现要求将序列填充完整，问多少个方案满足**序列中不存在长度不为 $1$ 且存在唯一众数的连续子段**，答案对一个很臭的数取模。


乍一看这个限制很吓人，实则非常简单，可以将其翻译为**序列中不存在相同的数**，证明如下：

 1、对于任意长为二的连续子段，容易知道“不存在唯一众数”与“不存在相同数字”等效。

 2、对于任意长为三的连续子段，此处不妨设三个数从左到右分别为 $i,j,k$ 。已知 $i$ 与 $j$ 不同，倘若 $i$ 与 $k$ 相同，便存在唯一众数，不合法，因而 $i$ 与 $k$  应不同。即“不存在唯一众数”与“不存在相同数字”仍然等效。  
 举例：对于 $[1,2,0]$ 的填充， $[1,2,1]$显然不合法，而 $[1,2,3]$是合法的。

 3、使用**数学归纳法**容易证明，若一个方案满足限制，则这个方案所得序列中不存在相同的数。

---
然后这题基本就做完了，只需要再注意一些细节即可：

1、数据中 $m$ 可能会小于 $n$ ，出现这种情况时显然不可能有解，方案数为 $0$ ；

2、使用 ```map```
 或 ```set``` 记录数是否已经出现，当序列中已经存在重复的数时，方案数为 $0$ ；

3、记序列中 $0$ 的个数为 $a$ ，值域内没有出现过的数有 $b$ 个，容易知道方案数即**排列数**为 $\frac{b!}{(b-a)!}$ ,然而考虑到数据范围大到 $1\times10^9$ ，因此直接算阶乘并不现实。  

考虑到 $b$ 可能很大而 $a$ 往往较小，因此采用下述方法：

考虑先从 $b$ 个数中取走 $1$ 个数作为第一个数，此时取走的数有 $b$ 种可能；随后再从 $b-1$ 个数中取走 $1$ 个数作为第二个数，此时取走的数有 $b-1$ 种可能。反复取数，直到取完第 $a$ 个数并结束。

此时，根据**乘法原理**，方案数应当为取走的每个数的可能种类数的积，遂有下述做法。

---


代码很短，码风很丑QwQ


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1145141923;
int n,m,a,b,ans=1;
unordered_map<int,int> f;
signed main()
{
	cin>>n>>m;
	if(m<n) return cout<<0,0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(!x) a++;
		else if(f[x]) return cout<<0,0;
		else f[x]=1;
	}
	b=m-f.size();
	while(a)
	{
		ans=ans*b%mod;
		a--;b--;
	}
	cout<<ans;
}
```

---

## 作者：Left_i_Forever (赞：1)

$\Large{\text{Solution}}$

一个奇妙的性质：要满足要求，则数组中的数两两不同。

稍微感性一点的理解，如果有两个数相同，以这两个数为端点的区间有两种情况：

1. 中间还有其他的数有两个（有多个就已经不满足了）。
2. 中间没有重复的数（那么这个区间不满足）。

可以发现 1 的情况和这个区间是一样的，那么我们递归下去中间肯定会有没有重复的数的时候，所以数组中不能有数相同。

那么答案就是 $\Pi_{i=m-n+cnt0}^{m-n+1} i$，$cnt0$ 为我们需要填的空的个数。

$\Large{\text{Code}}$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1145141923;
int a[1000010];
map <int, int> mp;

signed main()
{
	int n, m, cnt = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i], cnt += a[i] == 0;
		if (mp.count (a[i])) return cout << 0 << endl, 0;
		if (a[i]) mp[a[i]] = true;
	}
	int ans = 1, x = m - mp.size ();
	for (int i = 1; i <= cnt; i++)
		ans = (ans * (x--)) % mod;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_Tea (赞：1)

注意到，“对于其中的任何一段长度大于等于 2 的子数组，不能存在唯一众数”，可以推出原序列**没有任何元素相等**  
稍感性的**证明**：  
假设如果存在至少两个元素相等，一定能找到一组 $l$ 和 $r$ 同时满足：
- $ a_{l} = a_{r} = x $
- $ \forall i,j \in (l,r)[ i \neq j ] , a_{i} \neq a_{j} $

则区间 $ [l,r] $ 存在唯一众数 $ x $ ，与题意矛盾，所以合法的序列一定满足**没有任何元素相等**


------------
在保证原序列无重复元素的情况下，我们记录序列 $ A $ 中 $ 0 $ （即替换数）的个数为 $ cnt $ ，则已有元素已经占了 $ 1 \thicksim M$ 中的 $ N - cnt $ 个，在剩下的 $ M - (N - cnt) $ 个元素中选择 $ cnt $ 个，用排列数 $ A $ 计算即可  
时间复杂度 $ O(N) $
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rint register int
#define F(i, x, y) for (rint i = (x); i <= (y); i++)
#define int long long
const int N = 1e6+10 ,mod = 1145141923;
int n,m,cnt;
int a[N];
map<int,bool> M;

int A(int n,int m) // A(n,m) = n! / (m-1)!
{
	int ans = 1;
	while(m)
	{
		ans = (ans*n) % mod;
		n--,m--;
	}
	return ans;
}

signed main()
{
	cin>>n>>m;
	if(m<n) // m个里选n个，m < n 一定不满足 
	{
		puts("0");
		return 0;
	}
	F(i,1,n)
	{
		cin>>a[i];
		if(a[i]==0)  // cnt 表示 替换数 个数 
		{
			cnt++;
			continue;
		}
		if(M[a[i]]) // 原序列有重复元素  ，一定不满足 
		{
			puts("0");
			return 0;
		}
		M[a[i]] = true;
	}
	cout<<A(m-(n-cnt),cnt);
	return 0;
}

```

---

## 作者：nightwatch.ryan (赞：1)

### Analysis
有一个显然的结论：一个对于其中的任何一段长度大于等于 $2$ 的子数组，不存在唯一众数的序列，**当且仅当该序列没有数字重复**。

我们来简单证明一下：我们有一个序列 $A$。设 $A_i = A_j$，$i < j$，且 $A_{i + 1}, A_{i + 2}, \dots, A_{j - 1}$ 不存在重复数字。显然，$A_i$ 和 $A_j$ 的出现次数为 $2$，而其他元素的出现次数为 $1$，不难看出该子数组存在唯一众数。由此，得证。

接下来，我们来讲解实现方法。

用一个 `set` 存储所有非 $0$ 的数字，设其为 $p$，记其大小为 $sz$；用一个变量 `zero` 存储 $0$ 的个数，设其为 $zero$。

如果 $sz$ 不等于 $N - zero$，则说明存在重复数字，输出 $0$。

如果 $M < zero$，则说明 $0$ 的个数大于 $m$，在 $0$ 的位置上填数字肯定会出现重复，输出 $0$。

如果 $A$ 中不存在 $0$，则 $p$ 的大小是否等于 $n$，如果等于 $n$，则输出 $1$，否则输出 $0$。

因为 $0 \leq A_i \leq 10^9$，所以 $A$ 中非 $0$ 数字的取值范围都是 $[1, M]$。故 $0$ 的位置上可以填的数字个数为 $M - sz$。那么，如果 $M - sz$ 小于 $zero$，则输出 $0$。否则，输出 $A_{M - sz}^{zero}$ 即为答案。这里的 $A$ 指的是排列数。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

#define P(i, a, b) for(int i = a; i <= b; i++)
#define Q(i, a, b) for(int i = a; i >= b; i--)
const int maxn = 1000005;
const int inf = 0x3f3f3f3f;
const int mod = 1145141923;

mt19937 rnd(chrono::duration_cast<chrono::nanoseconds>
           (chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

int n, m, a[maxn], zero;

signed main(){

    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    P(i, 1, n) cin >> a[i];
    P(i, 1, n) zero += a[i] == 0;
    set<int> p;
    P(i, 1, n) if(a[i] != 0) p.insert(a[i]);
    if(p.size() != n - zero) return cout << 0 << endl, 0;
    if(m < zero) return cout << 0 << endl, 0;
    if(zero == 0){
        if(p.size() == n) return cout << 1 << endl, 0;
        else return cout << 0 << endl, 0;
    }else{
        if(m - p.size() < zero){
            cout << 0 << endl;
        }else{
            int x = m - p.size(), result = 1;
            for(int i = 0; i < zero; i ++) (result *= (x - i)) %= mod;
            cout << result << endl;
        }
    }

}
```

---

## 作者：joe_zxq (赞：1)

这题放在 C 确实有点难了。

---

我们发现这个对序列的要求比较复杂，可以考虑如何转化成简单的形式。

用我们惊人的观察力，可以发现一个特别重要的性质：一个序列满足条件，当且仅当序列中没有重复的数。

证明：反证法，假设存在重复的数，设相隔最近的两个相同的数的下标分别为 $i$ 和 $j$，其中 $i<j$。那么，子数组 $A_{i},A_{i+1},\dots,A_{j}$ 中 $A_i$ 和 $A_j$ 显然是唯一众数。

那么，这道题就很简单了。设已经有 $a$ 个数被用过了，还有 $b$ 个位置没有用过，那么答案即为 $\prod\limits_{i=a}^{a+b-1}(M-i) \bmod 1145141923$，即每次乘上还没有用过的数的数量。

需要特判 $N>M$ 和序列中本身就有重复的数的情况。

时间复杂度：$O(N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6, MOD = 1145141923;
int N, M;
bool A[MAXN + 5];
unordered_map<int, bool> mp;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> M;
	if (M < N) {
		cout << "0\n";
		return 0;
	}
	int cnt = 0;
	for (int i = 1, u; i <= N; i++) {
		cin >> u;
		A[i] = (u >= 1);
		if (A[i]) {
			if (mp[u]) {
				cout << "0\n";
				return 0;
			}
			mp[u] = 1;
			cnt++;
		}
	}
	ll ans = 1;
	for (int i = 1; i <= N; i++) {
		if (!A[i]) {
			(ans *= M - cnt) %= MOD;
			cnt++;
		}
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

这是一道不错的思维题和数学题。

本题题面要求**每个**子数组**不能**有“唯一众数”的描述似乎很吓人，再加上 $N \le 10^6$ 的数据范围，相信不少人第一感觉是复杂的动态规划或是差分约束。然而这只是 C 题呢！于是我们想到，“每个子数组众数不唯一”是否只是一个幌子，靠我们思维来破解？

让我们用归纳法来分析：对于数组中任意一个 $a_i$，根据要求，$a_{i-1} \ne a_i ⇒ a_{i-2} \ne a_{i-1} \ne a_{i}⇒ ...$，由此我们发现一个重要性质：当且仅当数组中任意两数互不相同时（每个数只出现一次），才能满足约束。

到这里，本题不就变成经典的（小奥或高中课本中的）排列组合问题了吗！有解时，答案就是 $A_{m-cnt1}^{cnt2}$。（$cnt1$ 表示已确定数的个数，$cnt2$ 表示待确定数个数）。注意特判无解或全确定情况。

[代码](https://www.luogu.com.cn/paste/g3zuavqg)

---

## 作者：__qkj__ (赞：0)

## 解题思路
从小到大推导。

- 当子数组长度 $n=2$ 时，两个数字必须不同。
- 当 $n=3$ 时，三个数字也不能相同。
- 当 $n=4$ 时，可以发现要么只有两种数字，要么四个都不同。当只有两种数字时，如果选 $n=3$ 的子数组，就必有两个会相同，不符合题意。所以四个都不同。
- 以此类推，由于 $n-1$ 长度的子数组两两不同，所以 $n$ 长度的子数组只能两两不同。

当原数列有重复，无解，输出 $0$。

否则，设原数列共有 $k$ 个 $0$，第一个 $0$ 有 $m-(n-k)$ 种替换方法，第二个 $0$ 有 $m-(n-k)-1$ 种替换方法……于是，答案就是 $\prod\limits^{k}_{i=1}[m-(n-k)-i]\bmod 1145141923$。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1145141923;
map<int,int>s;
int a[1000010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,sum=0,ans=1;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(!a[i])sum++;
		else if((++s[a[i]])==2)
		{
			cout<<0;
			return 0;
		}
	}
	m-=(n-sum);
	for(int i=1;i<=sum;i++)
		(ans*=m-i+1)%=mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：ztd___ (赞：0)

### 大家好啊，我是怒调本题 1h+ 的看错题意选手。
只要没有看错题，这个题就不会很难。

容易发现的是，如果最终的序列里面有重复数字，这个序列就是不合法的。

证明：  
假设重复的数字为 $a$，那么答案序列一定有一个连续子序列是这样的（其中两个 $a$ 中间没有重复数字）：
$$\lbrace a, \dots, a \rbrace$$

>如果两个 $a$ 中间有重复数字，比如：
>$$\lbrace a, \dots, b, \dots, b, \dots, a \rbrace$$
>
>那么中间的 $\lbrace b, \dots, b \rbrace$ 必然还是上面的连续子序列类型。

然后因为两个 $a$ 中间没有重复数字，所以 $a$ 必然是这一段的唯一众数。不合法。

证毕。

接着非常好做。搞一个 `set` 去一下重，设 $s$ 为去重后的大小，$cnt$ 为空位的个数。

**以下内容默认 $cnt \ne 0$**，因为如果没有空位的话显然后面都不用算了，特判即可。把下文的所有 $s - 1$ 当成 $s$ 算也行。

如果发现 $s - 1 \ne n - cnt$，那么说明已经存在重复，输出 $0$。减一是因为 $0$（即空位）要单独考虑。

容易发现剩下还可以填的数字总数就是 $m - (s - 1)$，如果这么多的数字还不够填剩下的空位，显然也无解。即如果 $m - (s - 1) < cnt$，输出 $0$。

然后就是简单的计数。枚举每一个空位。设枚举到了第 $i$ 个空位，那么已经用掉的数字个数就是 $i - 1$，还能用的个数就是 $m - (s - 1) - (i - 1)$，累乘即可。注意取模。

代码过于简单，不贴了，赛时代码糖分超标。[赛后 AC 记录。](https://www.luogu.com.cn/record/201488246)  
但是在此为大家警钟长鸣：如果你觉得自己的做法很对，但是在 IOI 赛制下一直 WA，或者在 OI 赛制下一直过不了大样例，那么一定要检查自己是否看错了题。

---

## 作者：DashZhanghanxu (赞：0)

# 解析
分析题意，要求不能有唯一众数，所以我们可以知道数组中不可以有重复元素，否则就一定会有一个子数组中众数只有一个，不符合要求。而这道题本质上就是求出将可分配数字分配给可替换数字。

输入数据，求出数据中可替换数字的个数，并求出在数组中有多少元素，从而得出可分配数字的个数，再通过数字排列组合公式计算求出答案：
$$
{A}^{sum0}_{all}= \frac{all!}{(all - sum0)!}
$$

最后需要特判当原始序列就不符合要求，即存在唯一众数时，此时所有数字数量减去可分配数字不等于数组中的非零不相等元素数量，输出零，无解。
# CODE

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1145141923;
unordered_set<int>nums;
ll p(int all,int sum0){
    ll num=1;
    for(int i=all-sum0+1;i<=all;i++){
        num=(num*i)%mod;
    }
    return num;
}
int main(){
    int n,m;
    cin>>n>>m;
    int sum0=0;
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        if(a==0){
            sum0++;
        }else if(a<=m){
            nums.insert(a);
        }
    }
    int all=nums.size();
    if(all!=n-sum0)cout<<0; 
    else cout<<p(m-all,sum0)%mod<<"\n";
    return 0;
}
```

---

## 作者：ridewind2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11681?contestId=206100)

## 分析

题目要求使得对于其中的任何一段长度大于等于 $2$ 的子数组，不能存在唯一众数。仔细思考可以发现，这就是要让整个序列里的元素互不相同。

## 思路

一道非常典型的[排列组合](https://baike.so.com/doc/2732818-2884569.html)题，假设 $0$ 的数量为 $k$，$1$ 到 $m$ 中没有出现过的数的数量为 $t$，$t$ 就等于 $m - (n - k)$，那么答案就是 $A_{k}^{t}$。

易错点：原始序列可能出现有数字出现多次，所以我们可以用一个 set 来去重，再判断 set 里元素的数量与 $n - k$ 是否相等：
+ 如果相等，就继续往下计算，让答案 $ans$ 从 $t - k + 1$ 乘到 $t$，$ans$ 别忘了开 long long 和对 $1145141923$ 取模，直接输出 $ans$ 即可。
+ 否则，直接输出 $0$。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1145141923;
set<int>s;
int main(){
	int n,m,k=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(!x)k++;
		else s.insert(x);
	}
	if(s.size()!=n-k){//特判 
		cout<<0;
		return 0;
	}
	int t=m-(n-k);
	long long ans=1;
	for(int i=t-k+1;i<=t;i++){//计算答案 
		ans=ans*i%p;
	}
	cout<<ans;//输出答案 
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

应该是这场比赛除了 G 之外最有思维难度的题。

首先考虑长度为 $2$ 的数组。由于它不能有唯一众数，所以两个数不同。

接下来考虑长度为 $3$ 的数组。由于满足前面的条件，那么 $a_1\neq a_2$，$a_2\neq a_3$，若 $a_1=a_3$ 则有唯一众数为 $a_1$，不符合条件。所以 $a_1$ 到 $a_3$ 互不相同。

如果写下去，你就会发现如下规律：

考虑长度为 $k$ 的数组，由于满足前面的条件，那么 $a_1$ 到 $a_{k-1}$ 互不相同，$a_2$ 到 $a_k$ 互不相同，若 $a_1=a_k$ 则有唯一众数为 $a_1$，不符合条件。所以 $a_1$ 到 $a_k$ 互不相同。

然后你就会发现题目只是在问使得所有的数不相同的填法数量。

太智慧了。

时间复杂度 $O(n)$。
```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10, mod = 1145141923;
int n, m, a[N], cnt, res;
void run()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		if (a[i])
			continue;
		i--, n--, cnt++;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i < n; i++)
	{
		if (a[i] == a[i + 1])
		{
			puts("0");
			return;
		}
	}
	m -= n;
	res = 1;
	for (int i = 1; i <= cnt; i++)
	{
		res = 1ll * res * (m - i + 1) % mod;
	}
	printf("%d\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```
**但是你先别急**！我把这个问题丢给了 DeepSeek R1，他在长达 $823$ 秒的思考后说出了这句话：
> 该方法确保替换后的数组满足相邻元素不同且所有元素互不相同的条件，从而保证任何子数组都没有唯一众数。

结果你猜怎么着？他给的代码甚至无法通过样例！于是我再次强调所有元素互不相同，在 $77$ 秒的思考后才输出了这段能通过的代码：
```c++
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

const int MOD = 1145141923;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    unordered_set<int> unique_vals;
    bool valid = true;
    for (int i = 0; i < N; ++i) {
        if (A[i] != 0) {
            if (unique_vals.count(A[i])) {
                valid = false;
                break;
            }
            unique_vals.insert(A[i]);
        }
    }

    if (!valid) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < N - 1; ++i) {
        if (A[i] != 0 && A[i + 1] != 0 && A[i] == A[i + 1]) {
            valid = false;
            break;
        }
    }

    if (!valid) {
        cout << 0 << endl;
        return 0;
    }

    int c = unique_vals.size();
    vector<int> zeros;
    for (int i = 0; i < N; ++i) {
        if (A[i] == 0) {
            zeros.push_back(i);
        }
    }

    long long result = 1;
    unordered_set<int> used;

    for (int pos : zeros) {
        unordered_set<int> adj;
        if (pos > 0 && A[pos - 1] != 0) adj.insert(A[pos - 1]);
        if (pos < N - 1 && A[pos + 1] != 0) adj.insert(A[pos + 1]);

        int available = M - c - adj.size();
        available -= used.size();

        if (available <= 0) {
            cout << 0 << endl;
            return 0;
        }

        result = result * available % MOD;
        c += 1;
    }

    cout << result << endl;
    return 0;
}
```
于是我得出一个恐怖的结论：在 DeepSeek R1 眼里，[F 比 C 简单](https://www.luogu.com.cn/article/i5s0wa95)。

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
结论：一个数列中不可有两个相同数。

证明：

找两个相同的数。

如果中间还有相同的，用中间的，直到中间的都不相同。

如果没有，那么这个子序列不合法。

接下来，先用 set 判重，再利用小学生都会的组合数算一下就行。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a,all,ans,b;
set<long long> s;//不开龙龙见祖宗
int main(){
	cin>>n>>m;
	all=n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a==0){
			continue;
		}
		all--;
		auto kkk=s.insert(a);
		if(kkk.second==0){
			cout<<0;
			return 0;
		}//判重
	}
	if(!all){
		cout<<0;
		return 0;
	}//没有0
	b=m-s.size();
	ans=1;
	while(all){
		ans*=b;
		ans%=1145141923;
		all--,b--;
	}//煎蛋的组合数
	cout<<ans;
}
```

---

## 作者：Your_Name (赞：0)

## 题解

先说结论：**构造出的序列一定没有重复元素。**

考虑证明：

我们先设该序列有重复元素，且距离最近的一对下标为 $(i,j)$。

那么在 $i$ 到 $j$ 中就没有相同元素，那么众数必定唯一。

矛盾，得证。

有了这个就好做了，直接看我们能改的数还有多少，然后每填一个，可用的数减少一个。全部乘起来就行。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, mod = 1145141923;
long long cnt, n, m, a[N], ans;
map<int, bool> ma;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        if(x == 0){
            cnt ++;
            continue;
        }//可以改的位置
        if(ma.count(x)){
            cout << 0;
            return 0;
        }//本身就有重复
        ma[x] = 1;
    }
    m -= n - cnt;//少了这么多可用的数。
    ans = 1;
    for(int i = 0; i < cnt; i ++){
        ans = ans * (m - i) % mod;
    }//每次少一个
    cout << ans;
    return 0;
}
```
 _完结撒花。_

---

