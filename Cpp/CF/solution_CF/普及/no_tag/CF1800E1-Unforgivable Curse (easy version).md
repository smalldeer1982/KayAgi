# Unforgivable Curse (easy version)

## 题目描述

This is an easy version of the problem. In this version, $ k $ is always $ 3 $ .

The chief wizard of the Wizengamot once caught the evil wizard Drahyrt, but the evil wizard has returned and wants revenge on the chief wizard. So he stole spell $ s $ from his student Harry.

The spell — is a $ n $ -length string of lowercase Latin letters.

Drahyrt wants to replace spell with an unforgivable curse — string $ t $ .

Drahyrt, using ancient magic, can swap letters at a distance $ k $ or $ k+1 $ in spell as many times as he wants. In this version of the problem, you can swap letters at a distance of $ 3 $ or $ 4 $ . In other words, Drahyrt can change letters in positions $ i $ and $ j $ in spell $ s $ if $ |i-j|=3 $ or $ |i-j|=4 $ .

For example, if $ s =  $ "talant" and $ t =  $ "atltna", Drahyrt can act as follows:

- swap the letters at positions $ 1 $ and $ 4 $ to get spell "aaltnt".
- swap the letters at positions $ 2 $ and $ 6 $ to get spell "atltna".

You are given spells $ s $ and $ t $ . Can Drahyrt change spell $ s $ to $ t $ ?

## 说明/提示

The first example is explained in the condition.

In the second example we can proceed as follows:

- Swap the letters at positions $ 2 $ and $ 5 $ (distance $ 3 $ ), then we get the spell "aaacbba".
- Swap the letters at positions $ 4 $ and $ 7 $ (distance $ 3 $ ), then you get the spell "aaaabbc".

In the third example, we can show that it is impossible to get the string $ t $ from the string $ s $ by swapping the letters at a distance of $ 3 $ or $ 4 $ .

In the fourth example, for example, the following sequence of transformations is appropriate:

- "accio" $ \rightarrow $ "aocic" $ \rightarrow $ "cocia" $ \rightarrow $ "iocca" $ \rightarrow $ "aocci" $ \rightarrow $ "aicco" $ \rightarrow $ "cicao"

In the fifth example, you can show that it is impossible to get the string $ s $ from the string $ t $ .

In the sixth example, it is enough to swap the two outermost letters.

## 样例 #1

### 输入

```
7
6 3
talant
atltna
7 3
abacaba
aaaabbc
12 3
abracadabraa
avadakedavra
5 3
accio
cicao
5 3
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

## 作者：yyz1005 (赞：9)

## 题目翻译

给定 $2$ 个长度为 $n$ 的字符串 $s1$，$s2$。你可以将 $s1$ 中的任意一个字符（设为 $s1_i$）与 $s1_{i+k}$，$s1_{i+k+1}$，$s1_{i-k}$，$s1_{i-k-1}$ 交换，请问是否能使得 $s$ 变为 $t$。特别的，$k$ 将永远为 $3$。

## 思路

注意到将 $s_i$ 向右移动 $k+1$ 位 在向左移动 $k$ 位等价于向右移动 $1$ 位。

所以当 $s1[i] \neq s2[i]$ 时，只要第 $i$ 位可以交换，必然可以使得 $s1[i]=s2[i]$。（从样例可以看出来）。

而 $s1[i]$ 不能交换当且仅当 $i-k < 0$ 且 $n \le i+k$。（第一个是向左交换 $k$，向右交换 $k+1$，第二个则向右交换 $k$，向左交换 $k+1$）

另外，可以通过这个条件发现 $6 \le n$ 时是 $s1$ 一定可以变换为 $s2$。

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
		sort(s22.begin(),s22.end());//显然，当两个字符串的长度或字符不完全相同时一定是错误的
		if(s11!=s22) puts("NO");
		else {
			for(ll i = 0; i < n; i++){
				if(i-k<0&&i+k>=n&&s1[i]!=s2[i]){
					puts("NO");
					break;
				}
				if(i==n-1) puts("YES");
			}
		}
	}
	return 0;
}
```

---

## 作者：_GW_ (赞：2)

## 思路
我们直接考虑困难版。

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

[CF1800E2](https://www.luogu.com.cn/problem/CF1800E2)

---

## 作者：Larryyu (赞：2)

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

## 作者：REAL_曼巴 (赞：1)

此题是简单版，但我会介绍加强版和简单版的所有解法。

首先是简单版，他的 $k$ 的是定值所以我们可以找一下规律。我们可以发现，只要移动的位置在字符串范围内，每个字符可以移动到任意位置。

所以这道题分成了两步，第一步是先把字符串的每一个位置的字符都统计出个数，如果两个字符串每个是字符串的字母数量都不行同那一定不合法。

第二步我们是判断位置不匹配的位置，他要移动的距离是否在字符串的范围内。我们可以通过不等式的方式来判断。就像这样。

```
bool check_pos(int x){
    return ((x+k<n)||(x-k>=0));
}
```

之后就是代码了。两个版本都可通过。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1001;
int s[maxn][maxn];
map<char,int>mp1;
map<char,int>mp2;
int n,k;
bool check_pos(int x){
    return ((x+k<n)||(x-k>=0));
}
signed main(){
    int t;
    cin>>t;
    while(t--){
        mp1.clear();
        mp2.clear();
        bool f=0;
        cin>>n>>k;
        string s1,s2;
        cin>>s1>>s2;
        for(int i=0;s1[i];++i)mp1[s1[i]]++;
        for(int i=0;s2[i];++i)mp2[s2[i]]++;
        for(char i='a';i<='z';++i){
            if(mp1[i]!=mp2[i]){
                cout<<"NO"<<endl;
                f=1;
                break;
            }
        }
        if(f)continue;
        f=0;
        for(int i=0;s1[i];++i){
            if(s1[i]!=s2[i]){
                //cout<<i<<endl;
                if(!check_pos(i)){
                    cout<<"NO"<<endl;
                    f=1;
                    break;
                }
            }
        }
        if(!f)cout<<"YES"<<endl;
    }
    return 0;
}
```


---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1800E1) & [CF 传送门](//codeforces.com/problemset/problem/1800/E1)
# 思路
我们做以下步骤即可将 $a_i$ 和 $a_{i-1}$ 交换：
1. 交换 $a_i$ 和 $a_{i+k}$。
1. 交换 $a_{i+k}$ 和 $a_{i-1}$。
1. 交换 $a_i$ 和 $a_{i+k}$。

我们可以交换相邻两个数，这说明只要 $i$ 和 $j$ 都是能交换的，那 $i$ 位置上的字符一定能到达 $j$！而 $i$ 位置能交换的标准就是 $i<k$ 且 $i>=n-k$。另外，我们还要判断一下两个字符串是否拥有同一堆字符。
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
using namespace std;
int t, n, k, sa[150], sb[150], x;
string a, b;
bool f () {
	cin >> n >> k >> a >> b;
	//从这里开始判重……这是一种记录字母数量方法，还有一种用排序判重的方法可以看 yyz1005 的题解
	memset (sa, 0, sizeof sa); //多组数据要清空！
	memset (sb, 0, sizeof sb);
	for (int i = 0; i < n; ++ i)
		++ sa[a[i]]; //记录 a 的字母
	for (int i = 0; i < n; ++ i)
		++ sb[b[i]]; //记录 b 的字母
	for (char i = 'a'; i <= 'z'; ++ i)
		if (sa[i] != sb[i]) //数量不相同
			return 0;
	//到这里结束判重……
	for (int i = 0; i < n; ++ i)
		if (a[i] != b[i] && i < k && i >= n - k) //判断字符是否相同和能不能交换
			return 0;
	return 1;
}
int main () {
	cin >> t;
	while (t --)
		cout << (f () ? "YES\n" : "NO\n");
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1800E1)

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
[CF1800E2](https://www.luogu.com.cn/problem/CF1800E1)

---

## 作者：Llx2022 (赞：0)

#  _**Solution**_ 

### **直接使用大范围的 $k$**

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

**注意，这里提供给的做法是** $1 \leq k \leq 2 \times 10 ^ 5$ **的做法，也就是更难的版本。**

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

