# Necklace Assembly

## 题目描述

The store sells $ n $ beads. The color of each bead is described by a lowercase letter of the English alphabet ("a"–"z"). You want to buy some beads to assemble a necklace from them.

A necklace is a set of beads connected in a circle.

For example, if the store sells beads "a", "b", "c", "a", "c", "c", then you can assemble the following necklaces (these are not all possible options):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/d2ddac43ecb91517adf034c4a5c0862106e5b4e4.png)And the following necklaces cannot be assembled from beads sold in the store:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/509baa50603d3d471878b58a508e7ec9dac1674b.png)The first necklace cannot be assembled because it has three beads "a" (of the two available). The second necklace cannot be assembled because it contains a bead "d", which is not sold in the store.We call a necklace $ k $ -beautiful if, when it is turned clockwise by $ k $ beads, the necklace remains unchanged. For example, here is a sequence of three turns of a necklace.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/2f3c78fa3723939cbe420518274f88aa30a08005.png) As you can see, this necklace is, for example, $ 3 $ -beautiful, $ 6 $ -beautiful, $ 9 $ -beautiful, and so on, but it is not $ 1 $ -beautiful or $ 2 $ -beautiful.In particular, a necklace of length $ 1 $ is $ k $ -beautiful for any integer $ k $ . A necklace that consists of beads of the same color is also beautiful for any $ k $ .

You are given the integers $ n $ and $ k $ , and also the string $ s $ containing $ n $ lowercase letters of the English alphabet — each letter defines a bead in the store. You can buy any subset of beads and connect them in any order. Find the maximum length of a $ k $ -beautiful necklace you can assemble.

## 说明/提示

The first test case is explained in the statement.

In the second test case, a $ 6 $ -beautiful necklace can be assembled from all the letters.

In the third test case, a $ 1000 $ -beautiful necklace can be assembled, for example, from beads "abzyo".

## 样例 #1

### 输入

```
6
6 3
abcbac
3 6
aaa
7 1000
abczgyo
5 4
ababa
20 10
aaebdbabdbbddaadaadc
20 5
ecbedececacbcbccbdec```

### 输出

```
6
3
5
4
15
10```

# 题解

## 作者：Tx_Lcy (赞：9)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16821650.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1367E)

## 思路

提供一种比现有的两篇题解都简单的方法。

我们枚举答案，发现最终的答案数组一定是由多个完全相同的块组成的，并且块长必定是 $k$ 的因数。

然后我们考虑枚举答案 $i$，那么此时的块长必然是 $\gcd(i,k)$，那么可以得到块的数量为 $\dfrac{i}{\gcd(i,k)}$，每个字母在每个块中的数量也可以简单地计算出来，为 $\sum \dfrac{a_i}{\frac{i}{\gcd(i,k)}}$，最后比较这个值与块长 $\gcd(i,k)$ 的大小即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=2e3+10;
int a[30];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while (t--){
        memset(a,0,sizeof a);
        int n,k;string s;cin>>n>>k>>s;
        s=" "+s;int ans=0;
        for (int i=1;i<=n;++i) ++a[s[i]-'a'];
        for (int i=1;i<=n;++i){
            int len=i/__gcd(i,k),sum=0;
            for (int j=0;j<26;++j) sum+=a[j]/len;
            if (sum>=__gcd(i,k)) ans=max(ans,i);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```


---

## 作者：F_Mu (赞：5)

**题意**

给定一个字符串$s$，长度为$n$，一根项链为一个环，定义一根项链为$k-beautiful$，则该项链顺时针转$k$下后与原项链相等，给出$k$，请构造一根最长的$k-beautiful$项链，项链由$s$中的一些字符组成，长度为$1$的项链和组成字符全部相等的项链满足任意$k$

**分析**

首先最小的答案是最大的字符个数，然后考虑项链中字符不全相等的情况，一根项链转$k$下不变，则$k$的某个因子可能也满足，不妨设为$j$，则$j-beautiful$的项链也满足$k-beautiful$，我们枚举因子$j$，然后找到可以构造出的最长项链，设项链为字符串$t$，注意到$j-beautiful$的项链有$t[1]=t[j+1],\cdots ,t[j-1]=t[2*j-1]$，注意到这个等式可以继续下去，那么我们要考虑项链的节数，每节有$j$个字符，那么要找到可以满足的最大节数，最长的$j-beautiful$项链即为：最大节数乘以$j$，这个最大节数具有二分性质，二分即可

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
 
#include <bits/stdc++.h>
 
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 5e6 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
int num[26];
 
bool check(int each, int jie) {
    rep(i, 0, 25) {
        each -= num[i] / jie;
        if (each <= 0)
            return true;
    }
    return false;
}
 
void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int ans = 1;
    rep(i, 0, 25)num[i] = 0;
    rep(i, 0, s.size() - 1)++num[s[i] - 'a'], ans = max(ans, num[s[i] - 'a']);
    vector<int> v;
    for (int i = 2; i <= k; ++i) {
        if (k % i == 0)
            v.push_back(i);
    }
    for (auto &each:v) {
        int l = 1, r = n / each;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(each, mid))
                ans = max(ans, mid * each), l = mid + 1;
            else
                r = mid - 1;
        }
    }
    cout << ans << '\n';
}
 
signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```



---

## 作者：_edge_ (赞：3)

提供一种暴力的想法，复杂度是 $O(n^2 \log n)$，如果要更加优秀请看别题解。

首先，先把这个环的长度枚举一下，我们会发现如果转一转要相等的，那么对于 $i$ 以及 $(i+k) \bmod n$ 要相等。

我们对于这样两个相等的点连一条边，连出来就是个连通块。

每一个连通块内的点都要相等，然后问题就转化为给定两个序列，第二个序列要匹配第一个序列的点，匹配一下就减去他的权值，不能减成 $0$，然后问是否能合法匹配。

这个问题应该可以贪心，直接拿第二个和第一个序列的目前最大值减一减即可，如果可以减的话，第二个序列往后移动即可，证明我不会(

利用双指针做到 $O(n^2 \log n)$。

```cpp
/*
0 1 2 3 4 5 
b a c b a c

a[(i+k)%T]=a[i]
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF=2e3+5;
int t,cnt[35],n,k,fa_set[INF],aa[INF],cnt1[INF],tmp[35];
string s1;
int find_set(int x) {return x==fa_set[x]?x:fa_set[x]=find_set(fa_set[x]);}
void mer(int x,int y) {
	x=find_set(x);y=find_set(y);
	fa_set[x]=y;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while (t--) {
		cin>>n>>k>>s1;s1=" "+s1;
		for (int i=0;i<26;i++) cnt[i]=0;
		for (int i=1;i<=n;i++) {
			cnt[s1[i]-'a']++;
//			cout<<s1[i]-'a'<<" kel\n";
		}
		sort(cnt,cnt+26);
		int ans=0;
		for (int l=1;l<=n;l++) {
			for (int j=0;j<l;j++) fa_set[j]=j,cnt1[j]=0;
			for (int j=0;j<l;j++) {
				mer(j,(j+k)%l);
//				cout<<j<<" "<<(j+k)%l<<" ove?\n";
			}
			for (int j=0;j<l;j++)
				cnt1[find_set(j)]++;
			aa[0]=0;
			for (int j=0;j<l;j++) {
				if (!cnt1[j]) continue;
				aa[++aa[0]]=cnt1[j];
//				cout<<cnt1[j]<<" ?\n";
			}
			memcpy(tmp,cnt,sizeof cnt);
			sort(aa+1,aa+1+aa[0]);int r=25,fl=0;
			for (int i=aa[0];i;i--) {
//				cout<<aa[i]<<" "<<r<<" "<<cnt[r]<<" "<<aa[i]<<" ?\n";
				while (r>-1 && cnt[r]<aa[i]) r--;
				if (r<0) {fl=1;break;}
				if (r>-1 && cnt[r]>=aa[i]) cnt[r]-=aa[i];
				else r--;
			}
			memcpy(cnt,tmp,sizeof cnt);
			if (!fl) ans=max(ans,l);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

当然还有更加优秀的做法。

观察题目中的环，会发现这件事情和 $\gcd$ 稍微有点关系。

我们来尝试去思考，写出这些式子，$1 \bmod n$ 和 $(1+k) \bmod n$ 和 $(1+2\times k) \bmod n$ …… 以此类推。

对于两个点，$x,y$ 如果他们在同一个连通块内则 $x+a \times k \equiv y \pmod n$

然后移项，并且化简得到了 $a\times k + b \times n=y-x$。

类似的，这里我们解一个二元一次方程即可，根据裴蜀定理，这个成立仅当 $(y-x)$ 能被 $\gcd(k,n)$ 整除。

于是我们就可以比较快速的计算这些连通块的个数了。

设 $g=\gcd(k,n)$，那么如果两个点 $x,y$ 相差 $g$，则他们在同一个连通块内。

因此，连通块大小即为 $\dfrac{n}{g}$，因为每一个连通块类似于对称一样的。

每个连通块大小知道了，就可以利用每个字符去除掉他，计算出能贡献的连通块个数。

然后就能快速判断了。

总时间复杂度是 $O(n \log n)$。

---

## 作者：FireFy (赞：2)

~~题外话：自从洛谷的RMJ似了以后我的咕值就没涨过，写篇题解张张咕。~~

是[这篇题解](https://www.luogu.com.cn/article/rreaqyw6)的pro版本。

好像感觉很水的样子...

先看样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/2f3c78fa3723939cbe420518274f88aa30a08005.png)

这其中 $k$ 是 $3$，$n$ 是 $6$。

题面给的有点复杂，让我给它简化一下：

给你 $n$ 个字母，要求你把用一些字母组成首尾相连的若干段，使每个段**完全相等**，其中要求每段的长度必须为 $k$ 的因数。

读者可以暂停一下然后理解一下我这段话的意思。

然后就是思路。

我们对答案进行枚举，求出分段的数量及每段的长度，然后看每个字母可以在每个段中均匀分布几个，加到 $sum$ 当中，最后如果 $sum$ 大于每段长度，说明以 $i$ 作为总长度可行，记录答案。 

说一下该怎么求段数与段长。

每段长度：如果我们的目前枚举到的答案是 $i$，那么因为要满足每段的长度为 $k$ 的因数，所以直接对其求 $\gcd$ 即可。

分段数量：我们已经有了每段的长度，所以只需要将总长度 $i$ 除以每段的长度即可。

放上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
char c[2024];
int book[30];
int gcd(int n,int m)
{
	if(n%m==0) return m;
	else return gcd(m,n%m);
}
int main()
{
	int T,i,j,n,m,k,ans=0;
	cin>>T;
	while(T--)
	{
		ans=0;
		for(i=1;i<=30;i++) book[i]=0;
		cin>>n>>k;
		for(i=1;i<=n;i++)
		{
			cin>>c[i];
			book[c[i]-'a'+1]++;
		}
		for(i=1;i<=n;i++)
		{
			int len=gcd(max(i,k),min(i,k)),num=i/len,sum=0;
			for(j=1;j<=26;j++) sum+=book[j]/num;
			if(sum>=len) ans=i; 
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：yr409892525 (赞：1)

## CF1367E Necklace Assembly
发现答案是由多个相同元素的块组成，不妨枚举答案，设答案为 $i$，一共有 $\gcd(i,k)$ 个块，每一个块的大小都是 $i \div \gcd(i,k)$，只需要枚举 $26$ 个字母，累加每一个字母对答案的贡献，判断是否合法，可以从大到小枚举，第一个合法答案就是最大的答案。                   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,inf=1e18;
int a[N];
int gcd(int x,int y){
	return ((y==0)?x:gcd(y,x%y));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		string s;
		cin>>s;
		for(int i=0;i<26;i++) a[i]=0;
		for(int i=0;i<n;i++){
			a[s[i]-'a']++; 
		} 
		for(int i=n;i>=1;i--){
			int x=gcd(i,m);
			int sum=0;
			for(int j=0;j<26;j++){
				sum+=a[j]*x/i;
			}
			if(sum>=x){
				cout<<i<<"\n";
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：AlexandreLea (赞：1)

## 题目大意

给定一个字符串 $S$，满足 $|S|=n$，要求从字符串中选取 $h$ 个字符组成新字符串 $S'$，满足字符串循环左移 $k$ 位后得到的字符串等于 $S'$。求最大的 $h$。

## 题目思路

不难得出先求各个字符的个数并从大到小排序并（贪心地）取字符。

我们发现可以通过填充 $q$ 个重复的长为 $l$ 的串（满足 $l\backslash k$）来得到我们的字符串。令 $w=l$，不断地从 $w$ 中减去 $e=\lfloor x/q\rfloor$，其中 $x$ 代表某个字符的出现次数，这个式子代表 $x$ 个字符中的 $eq$ 个字符可以用于填充长为 $l$ 的字串直到结尾。这里我们要枚举 $l$ 并用除法实现 $q$。

需要注意的是循环范围。代码如下。

```cpp
// Codeforces 1367E - Necklace Assembly
#include <bits/stdc++.h>
using namespace std;
int n, k, m, cebt[30];
void solve()
{
    string s;
    cin >> n >> k >> s;
    int es = s.length();
    for (int i = 0; i < es; ++i)
        cebt[s[i] - 'a']++;
    sort(cebt, cebt + 26, greater<int>()), m = 0;
    while (cebt[m])
        ++m;
    int ans = 0;
    for (int i = k; i >= 1; --i)
    {
        if (k % i != 0)
            continue;
        for (int j = n / i; j >= (n >= k ? k / i : 1); --j)
        {
            int qe = i;
            for (int e = 0; e < m; ++e)
                qe -= cebt[e] / j;
            if (qe <= 0)
                ans = max(ans, i * j);
        }
    }
    cout << ans << endl;
    memset(cebt, 0, sizeof(cebt));
}
int main()
{
    int _;
    cin >> _;
    while (_--)
        solve();
    return 0;
}
```

代码用 vscode 自带的格式化工具格过。

## 后话

学了这样多年 OI，又怎样呢？于个人能力并未提升，于升学也无帮助。

只得回去当算法爱好者了。

> 工匠精神并不以成功为旨归，却足以为成功铺就通天大道。
>
> ——摘自语文书十年级上册

---

