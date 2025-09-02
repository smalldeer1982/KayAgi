# Unforgivable Curse (hard version)

## 题目描述

This is a complex version of the problem. This version has no additional restrictions on the number $ k $ .

The chief wizard of the Wizengamot once caught the evil wizard Drahyrt, but the evil wizard has returned and wants revenge on the chief wizard. So he stole spell $ s $ from his student Harry.

The spell — is a $ n $ -length string of lowercase Latin letters.

Drahyrt wants to replace spell with an unforgivable curse — string $ t $ .

Dragirt, using ancient magic, can swap letters at a distance $ k $ or $ k+1 $ in spell as many times as he wants. In other words, Drahyrt can change letters in positions $ i $ and $ j $ in spell $ s $ if $ |i-j|=k $ or $ |i-j|=k+1 $ .

For example, if $ k = 3, s =  $ "talant" and $ t =  $ "atltna", Drahyrt can act as follows:

- swap the letters at positions $ 1 $ and $ 4 $ to get spell "aaltnt".
- swap the letters at positions $ 2 $ and $ 6 $ to get spell "atltna".

You are given spells $ s $ and $ t $ . Can Drahyrt change spell $ s $ to $ t $ ?

## 说明/提示

The first case is explained in the condition.

In the second case, we can swap adjacent letters, so we can sort the string using bubble sorting, for example.

In the third case, we can show that from the string $ s $ we cannot get the string $ t $ by swapping letters at a distance of $ 6 $ or $ 7 $ .

In the fourth case, for example, the following sequence of transformations is appropriate:

- "accio" $ \rightarrow $ "aocic" $ \rightarrow $ "cocia" $ \rightarrow $ "iocca" $ \rightarrow $ "aocci" $ \rightarrow $ "aicco" $ \rightarrow $ "cicao"

In the fifth case, we can show that it is impossible to get the string $ s $ from the string $ t $ .

In the sixth example, it is enough to swap the two outermost letters.

## 样例 #1

### 输入

```
7
6 3
talant
atltna
7 1
abacaba
aaaabbc
12 6
abracadabraa
avadakedavra
5 3
accio
cicao
5 4
lumos
molus
4 3
uwjt
twju
4 3
kvpx
vxpk```

### 输出

```
YES
YES
NO
YES
NO
YES
NO```

# 题解

## 作者：lfxxx (赞：8)

发现一个神奇的事实：显然不限制交换次数可以实现交换任意字符。

因此可以直接判断字符集是否相等。

在考虑哪些地方可以交换。

根据题意可知可以交换的区间为 $[1,n - k]$ 以及 $[k + 1,n]$。

不能交换的区间是静态的，所以判断是否相等即可。

代码实现很简单，就不给出了。

---

## 作者：Larryyu (赞：4)

简单版和困难版的唯一区别在于 $k$ 的数据范围，简单版中，保证 $k=3$。

给定 $n$，$k$，及两个长度为 $n$ 的字符串 $a$，$b$。

问能否在通过若干次操作后使 $a$ 改为 $b$。

在一次操作中，你可以交换 $a_i,a_j(i<j)$ 当且仅当 $\left\vert i-j\right\vert=k\space or\space k+1$。

共 $T$ 组数据。

## _Solution_
我们以 $k=3$ 来找规律。

首先当 $n\leq3$ 时，任何字母都无法操作，所以 $a$ 和 $b$ 要完全相同才可行。

$n=4$ 时 $a_2,a_3$（以一为字符串开始下标）是无法移动的，而 $a_1,a_4$ 可以交换。

$n=5$ 时 $a_3$ 无法移动，换言之其他字母也无法到 $a_3$。其他的位置可以任意交换：
- $a_1\rightarrow a_2$：先到 $a_4$ 再到 $a_2$。
- $a_1\rightarrow a_3\space or\space a_4$：一步到达，其他位置同理。

$n=6$ 时，任意字母可以到达任意位置。

如果 $a_i\rightarrow a_{i+j}$，向右移 $4$ 步再往左移 $3$ 步，重复 $j$ 次即可，如果越界，适量减少重复次数，调整右移左移步数及顺序，显然可以到达任意位置（$a_5$ 到 $a_6$ 的顺序为 $a_5\rightarrow a_2\rightarrow a_6$）。$a_{i-j}$ 同理。

总结规律，只要 $a_i$ 可以进行操作（$i-k\geq 1$ 并且 $i+k\leq n$），它就可以移到任意字母，任意字母也可以移到这个位置上。

只需判断那些不能移动的位置上更改前和更改后是否相同。

记得保证该字母在 $a$ 中出现过，记录每种字母修改前后的数量是否一致即可。

简单版和困难版皆可通过。

## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int t;
int vis1[30],vis2[30];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read(),k=read();
	string a,b;
	cin>>a>>b;
	memset(vis1,0,sizeof(vis1));
	memset(vis2,0,sizeof(vis2));
	for(int i=0;i<n;i++){
		vis1[a[i]-'a'+1]++;
		vis2[b[i]-'a'+1]++;
	}
	for(int i=1;i<=26;i++) {
		if(vis1[i]!=vis2[i]){//数量不同无法实现
			cout<<"NO"<<endl;
			return ;
		}
	}
	for(int i=0;i<n;i++){
	    if(i+k>=n&&i-k<0){//无法操作
	        if(a[i]!=b[i]){
	            cout<<"NO"<<endl;
	            return ;
	        }
	    }
	}
	cout<<"YES"<<endl;
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}

```

---

## 作者：_GW_ (赞：2)

## 思路
首先，我们先用一个桶统计每个字母出现的次数，然后判断一下两个字符串中每个字母的数量是不是完全相等，这是容易想到的。

然后，我们想从任意一个点出发，看看他能到那些点。

设此时在 $i$ 这个位置，然后跳一步可以到的点是 $i+k$ 和 $i+k+1$ 和 $i-k$ 和 $i-k-1$ 这几个点。

画个图即可发现，我们先向前跳 $k+1$ 格，再向后跳 $k$ 格，正好向前移动了一格！向后移动也是同理。

那么，就可以在不越界的情况下随便变换了，此时只要判断每个点跳的时候是否会越界即可！

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114514*2;
int a[N],T,b[N],num,n,m,k;
string s,s1,s2,ss;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>k>>s>>ss;
        memset(a,0,sizeof a);memset(b,0,sizeof b);
        bool flag=1;
        for(int i=0;i<n;i++) a[s[i]]++,b[ss[i]]++;
        for(int i=0;i<26;i++)
        {
            if(a['a'+i]!=b['a'+i])
            {
                flag=0;
                cout<<"NO"<<endl;
                break;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(i+k>=n&&i-k<0&&s[i]!=ss[i]&&flag==1)
            {
                flag=0;
                cout<<"NO"<<endl;
            }
        }
        if(flag) cout<<"YES"<<endl;
    }
    return 0;
}
```
## ~~双倍经验~~

[CF1800E1](https://www.luogu.com.cn/problem/CF1800E1)

---

## 作者：rainygame (赞：1)

全题解区最简洁的代码来了！

首先可以发现，不限交换次数就可以交换任意字符。

那么显然，我们可以交换的字符就是 $[1,n-k]$ 和 $[k+1,n]$ 的字符。

所以，我们只需要判断 $[1,n-k]$ 和 $[k+1,n]$ 的**字符集是否相同**以及 $[n-k+1,k]$ 是否**完全相同**即可。

这时候就可以请出我们的 `std::sort` 了！只需 `sort` 一下，即可判断字符集是否相同。因为如果 $[n-k+1,k]$ **完全相同**，那么它们不会影响到字符集的判断，可以直接判断 $[1,n]$。

而判断 $[n-k+1,k]$ **完全相同**则可以使用 `x.substr(n-k,(k<<1)-n)`。

注意：因为 $n,k$ 几乎没有限制，所以一定要添加各种和 $0$ 取 $\max$ 的代码。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define gc() getchar()
#define pc(x) putchar(x);
#define sp pc(' ');
#define el pc('\n');
#define Yes printf("YES");
#define No printf("NO");
#define err assert(0);
//const int MAXN(1e5+1);
//const ll MOD(1e9+7);

ll re(){
	ll x(0), f(1);
	char ch;
	while ((ch = gc()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = gc()) > 47);
	return x * f;
}

void uwr(ll x){
	ll tmp(x/10);
	if (tmp) uwr(tmp);
	pc(x-(tmp<<1)-(tmp<<3)^48);
}

void wr(ll x){
	if (x < 0){
		pc('-');
		x = -x;
	}
	uwr(x);
}

int n, k;
string a, b;

void solve(){
	n = re();
	k = re();
	cin >> a >> b;
	
	if (a.substr(max(n-k, 0), max((k<<1)-n, 0)) != b.substr(max(n-k, 0), max((k<<1)-n, 0))){
		No;
		return;
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	cout << (a == b ? "YES" : "NO");
}

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	int t(1);
	t = re();
	while (t--){
		solve();
		el
	}

	return 0;
}

```


---

## 作者：Neilchenyinuo (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1800E2)

## Solution

1. 统计字符串中字母出现的次数并判断两个字符串中每个字母个数是否相等，如果不相等，那么就无法成功。

2. 然后枚举起点 $i$，那么 $i$ 这个点改一次可到 $i+k$， $i+k+1$， $i-k$ 和 $i-k-1$ 这几个点。

3. 我们可以先到第 $i+k+1$ 的位置，然后往回 $k$ 个，那不就到了第 $i+1$ 个位置吗？向后也是同理。

4. 最后，只用判断是否越界即可。
## Code
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int cnta[N],t,cntb[N],num,n,m,k;
string a,b;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k>>a>>b;
        memset(cnta,0,sizeof cnta);
		memset(cntb,0,sizeof cntb);
        bool flag=1;
        for(int i=0;i<n;i++)
			cnta[a[i]]++,cntb[b[i]]++;
        for(int i=0;i<26;i++)
        {
            if(cnta[i+'a']!=cntb[i+'a'])
            {
                flag=0;
                cout<<"NO\n";
                break;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(i+k>=n&&i-k<0&&a[i]!=b[i]&&flag==1)
            {
                flag=0;
                cout<<"NO\n";
                break;
            }
        }
        if(flag==1)
			cout<<"YES\n";
    }
    return 0;
}
```
### 莫抄袭，没了 AC 记录，空悲切！

#### ~~双倍经验~~

[CF1800E1](https://www.luogu.com.cn/problem/CF1800E1)

---

## 作者：Llx2022 (赞：0)

#  _**Solution**_ 


这是一道找**规律**的好题。我们发现在满足 $|i-j|=k$ 或 $|i-j|=k+1$ 的情况下，可以任意交换两个位置 $i$ 和 $j$。因此，我们只需要关注区间 $[1,n-k]$ 和区间 $[k+1,n]$。我们可以通过将区间 $[1,n-k]$ 中的元素移动到区间 $[k+1,n]$，或将区间 $[k+1,n]$ 中的元素移动到区间 $[1,n-k]$，从而达到目标状态。因此，我们需要判断**区间 $(n-k,k+1)$ 是否相等**，以及**两个字符数组的元素个数是否相等**。如果都满足相等，则输出 YES；否则，输出 NO。


- 图是模拟一下字符 $A$ 的移动过程


![无标题.png](https://img1.imgtp.com/2023/06/06/xaWmfHcu.png)

#  _**Code**_ 



```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2e5+9;
int T,n,k;
char s1[N],s2[N];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        memset(s1,'0',sizeof(s1));
        memset(s2,'0',sizeof(s2));
        scanf("%s%s",s1+1,s2+1);
        for(int i=n-k+1;i<k+1;i++){
            if(s1[i]!=s2[i]){
                puts("NO");
                goto next;
            }
        }
        sort(s1+1,s1+n+1);
        sort(s2+1,s2+n+1);
        if(strcmp(s1,s2)!=0){
            puts("NO");
            goto next;
        }
        puts("YES");
        next:;
    }
    return 0;
}
```


---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/CF1800E1)

## Solution

一道好玩的脑筋急转弯题。

首先，由题意可得，有无限次交换，就可以把 $s_1$ 中可以交换的部分认为是“可以被任意组合”的，所以我们只需要考虑不可交换的范围，可以将字符串 $s_1$ 分为两部分：可以被交换的，也就是交换不会越界的，和不可以被交换的。

那么可以算出不可交换的范围为 $[n - k + 1, k]$，此处的下标从 $1$ 开始。

注意，如果 $k > n$ 可以直接判断 $s_1$ 和 $s_2$ 是否相等，否则在计算 $n - k + 1$ 时会越界。

在这之前，我们要判断 $s_1$ 和 $s_2$ 的各个字符数量是否相等，也就是它们的字符集是否相等。

## Code

```cpp
// 2023/5/31 Accept__

#include <iostream>
#include <cstring>

typedef long long ll;

using namespace std;

const int kMaxN = 2e5 + 7;

int t, n, k, l, r, a[kMaxN], b[kMaxN];
bool p;
string s1, s2;

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        cin >> n >> k >> s1 >> s2, s1 = " " + s1, s2 = " " + s2, l = 1, r = n;
        for (int i = 1; i <= n; i++) {
            a[s1[i]]++, b[s2[i]]++;
        }
        for (int i = 'A'; i <= 'z' && !p; i++) {
            (a[i] != b[i]) && (p = 1);
        }
        l = n - k + 1, r = k;
        if (k <= n) {
            for (int i = l; i <= r; i++) {
                (s1[i] != s2[i]) && (p = 1);
            }            
        } else {
            s1 == s2 ? (p = 0) : (p = 1);
        }
        puts(p ? "NO" : "YES"), l = r = p = 0, memset(a, 0, sizeof a), memset(b, 0, sizeof b);
    }
    
	return 0;
}
```


---

## 作者：yyz1005 (赞：0)

建议先阅读：[本题目的简化题目的题解](https://www.luogu.com.cn/blog/yyz666-lg-blog/solution-cf1800e1)

在本体的简化版中，我们推出了只要对于 $s$ 中，任意一个 满足 $i-k < 0$ 且 $n \le i+k$ 的 $i$，$s[i]$ 是不可以与其他项交换的。

当 $n \le k$ 时， 我们注意到一个关于 $i$ 的隐藏条件 $i \le n$。显然可得任意一个 $i$ 都是满足 $i-k < 0$ 且 $n \le i+k$ 的。也就是说，$n \le k$ 时 $s$ 可以变换为 $t$ 当且仅当 $s=t$。

当 $2 \times k \le n$ 时，若 $i$ 同时满足 $i-k < 0$ 且 $n \le i+k$。则 $(i+k)-(i-k) \geqslant n$，即有 $2k \geqslant n$。矛盾。所以 $2 \times k \le n$ 时 $s$ 恒能变换为 $t$。

当 $k+1 < n < 2 \times k -1$ 时，解 $i-k < 0$ 且 $n \le i+k$ 得 $n-k \le i < k$。枚举满足条件的 $i$ 是否满足 $s[i] = t[i]$ 即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
string s1,s2;
string s11,s22;
int main(){
	ll T;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		cin >> s1 >> s2;
		s11 = s1;
		s22 = s2;
		sort(s11.begin(),s11.end());
		sort(s22.begin(),s22.end());
		if(s11!=s22) puts("NO");
		else {
			if(n>=k*2) puts("YES");
			else if(n<=k){
				if(s1==s2) puts("YES");
				else puts("NO");
			} else {
				for(ll i = n-k+1-1; i <= k-1; i++){
					if(s1[i]!=s2[i]){
						puts("NO");
						break;
					}
					if(i==k-1) puts("YES");
				}
			}
		}
	}
	return 0;
}

```


---

