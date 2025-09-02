# String Reversal

## 题目描述

You are given a string $ s $ . You have to reverse it — that is, the first letter should become equal to the last letter before the reversal, the second letter should become equal to the second-to-last letter before the reversal — and so on. For example, if your goal is to reverse the string "abddea", you should get the string "aeddba". To accomplish your goal, you can swap the neighboring elements of the string.

Your task is to calculate the minimum number of swaps you have to perform to reverse the given string.

## 说明/提示

In the first example, you have to swap the third and the fourth elements, so the string becomes "aazaa". Then you have to swap the second and the third elements, so the string becomes "azaaa". So, it is possible to reverse the string in two swaps.

Since the string in the second example is a palindrome, you don't have to do anything to reverse it.

## 样例 #1

### 输入

```
5
aaaza```

### 输出

```
2```

## 样例 #2

### 输入

```
6
cbaabc```

### 输出

```
0```

## 样例 #3

### 输入

```
9
icpcsguru```

### 输出

```
30```

# 题解

## 作者：Froranzen (赞：10)

## CF1430E



------------

### 前言


如果序列 $B$ 正好是序列 $A$ 的翻转序列，那么这道题直接倒序赋值，求逆序对即可，详细可以参考其他题解。笔者在这里讨论一下如果 $B$ 序列是被无序打乱后的 $A$ 序列该如何求最小移动数。

------------

### 思路

设数组 $p$，$p_i$ 表示序列 $B$ 中的第 $i$ 个字符经过移动后，最终在序列 $A$ 中的位置。

显然，如果序列 $B$ 中没有重复的字符，那么我们直接将 $B_i$ 的 $p_i$ 赋值为该字符在 $A$ 中的位置即可。

问题是如果 $B$ 中有多个相同的字符，该如何处理呢？

这种问题有一个性质：

设 $i < j$，且 $B_i = B_j$，那么 $p_i < p_j$。

证明：

若交换 $p_i$, $p_j$ 的值：
1. 首先会增加一对逆序对，因为 $i<j$，且之前 $p_i < p_j$。
2. 交换后，因为之前 $p_i < p_j$，所以交换后原本以 $j$ 结尾的逆序对数不会减少，因为比 $p_j$ 大的数也比 $p_i$ 大；
3. 因为 $i < j$ ，所以交换后原本以 $p_j$ 开头的逆序对数不会减少，因为在 $j$ 后比 $p_j$ 小的数也在 $i$ 后；
4. 因为原本 $p_j > p_i$ ，所以交换后原本以 $i$ 开头的逆序对数不会减少，因为在 $i$ 后比 $p_i$ 小的数也比 $p_j$ 小；
5. 因为 $j > i$，所以交换后原本以 $p_i$ 结尾的逆序对数不会减少，因为在 $i$ 前比 $p_i$ 大的数也在 $j$ 前。

综上，如果交换 $p_i$，$p_j$，逆序对数至少会 + 1，答案会更劣。

根据上文的性质这道题就很容易写了。用一个 vector 存下 $A$ 中每种字符出现的位置。然后 $B$ 中的第 $i$ 个字符 $k$ 所对应的 $p$ 就是 $A$ 中第 $i$ 个 $k$ 所对应的位置。最后树状数组求逆序对即可。


------------


### 代码 

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i, f, t) for(register int i(f); i <= t; ++i)
#define per(i, f, t) for(register int i(t); i >= f; --i)
typedef long long ll;

int n;
char s[200003];
char t[200003];
int val[200003];
int now[27];
vector<int>vis[27];
int tr[200003];

inline int lowbit (int a) {return a & -a;}

void update (int a) {
    while(a <= n) {
        ++tr[a];
        a += lowbit(a);
    }
}

int query (int a) {
    int res = 0;
    while(a) {
        res += tr[a];
        a -= lowbit(a);
    }
    return res;
}

int main () {
    scanf("%d %s", &n, s);
    rep(i, 0, n-1) {
        t[i] = s[n-1-i];
    }
    rep(i, 0, n-1) {
        vis[s[i] - 'a'].push_back(i);
    }
    rep(i, 0, n-1) {
        int u = vis[t[i]-'a'][now[t[i]-'a']++];
        val[i+1] = u+1;
    }
    long long ans = 0;
    rep(i, 1, n) {
        ans += 1ll*(query(n) - query(val[i]));
        update(val[i]);
    }
    printf("%lld\n", ans);
}   
```


------------


感谢您能阅读本篇博客~


---

## 作者：Jairon314 (赞：7)

$ \text{Solution} $

$ \text{\small 前置芝士——树状数组} $

____________

学习过用树状数组求逆序对的人应该都会做这题吧？但是不管是求逆序对的题解还是这题的题解，对于一些问题都没有严格的证明，所以我想来记录一下，顺便巩固自己的知识。

首先我们来看以下的一个问题：

> 求证：一个数列，每次能交换相邻的两个元素，代价为1，使这个数列达到升序的最小代价是逆序对的数量


这个怎么证明呢？我们可以想到，如果一个数列不是升序（不减）的，那么这个数列中一定存在一组相邻的数对 $ {(a_i,a_{i+1})} $ ，满足 $ a_i>a_{i+1} $，那么我们花费 $ 1 $ 的代价，把这个数对交换。那么可以发现，交换完成后该数对的逆序对数量 $-1.$ 此时如果数列还不是升序（不减）的话，仍然能找到符合要求的数对进行交换。当某一次交换完成的时候，如果数列成为不递减数列了，那么它也就没有逆序对了。每次花费一个代价，都能够减少数列中的一个逆序对，则最后花费的代价就是原数列的逆序对数量。

于是，因为一个数列越接近升序（不减），它的逆序对越少，因而得证。

> $ \text{Question} $：已知一个数列，比如说 $ {[1,3,2,5,4]} $ ，我想要通过一种方式把该数列变成 $ [1,2,4,3,5] $ ，能不能用逆序对的知识求交换的最小次数呢？

这个问题的答案显然是可行的。我们可以把后面的数列的每一个元素都赋一个值，满足后面的这个数列中元素所赋的值是严格升序的。再新建立一个数列，即第一个数列根据后面这个数列的对应关系形成的数列。于是问题就转化成了将这个数列变成升序的过程，即前面咱们证明的问题。

$ \text{\color{red} e.g. [1,2,4,3,5] 变成 [1,2,3,4,5]，即满足对应关系：} $

$ {\color{red} 1 \to 1,2 \to 2,4 \to 3,3 \to 4,5 \to 5 } $

$ \text{\color{red} 根据该对应关系，我们可以把第一个数列转化成为 [1,4,2,5,3] } $

$ \text{\color{red} 于是该问题就转化成为使 [1,4,2,5,3] 不减的最小步骤，即它的逆序对数量} $

> $ \text{Question} $：如果上面的问题变成 $ [a,e,c,d,b] \to [c,e,a,b,d] $，我们还能用逆序对解决吗？

答案是：“当然可以！”

首先我们都知道所有的字母都有 ``ascii`` 码，把字母转化成数字就跟上面一样了。其实如果就算不是字母，是毫无规律可言的符号，通过上面建立对应关系，依然可以这么解。

其他的就根据树状数组求逆序对的板子就行了，接下来就是代码时间喽？

____________

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

#define int long long

/***************快读***************/

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

#define gc getchar

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

/***************快读***************/

#define maxn 2000010

int n;
// std::string s1,s2;
char s1[maxn],s2[maxn];

struct Arr{
	int val;
	int pos;
}arr[maxn],brr[maxn];

int change[maxn];

bool my_cmp(Arr a,Arr b){
	if(a.val==b.val){return a.pos<b.pos;}
	return a.val<b.val;
}

class Tree_Array{
	#define lowbit(k) ((k)&(-k))

	private:

	public:
		int tree[maxn];

		void add(int x,int k){
			for(;x<=n;x+=lowbit(x)){
				tree[x]+=k;
			}
			return;
		}

		int sum(int x){
			int res=0;
			for(;x;x-=lowbit(x)){
				res+=tree[x];
			}
			return res;
		}
}ta;

signed main(){
	read(n);
	std::cin>>s1;
	for(int i=n;i>=1;i--){
		s2[i-1]=s1[n-i];
	}
	for(int i=0;i<n;i++){
		arr[i+1].val=s1[i]-'a'+1;
		arr[i+1].pos=i+1;
	}
	for(int i=0;i<n;i++){
		brr[i+1].val=s2[i]-'a'+1;
		brr[i+1].pos=i+1;
	}
	std::sort(arr+1,arr+n+1,my_cmp);
	std::sort(brr+1,brr+n+1,my_cmp);
	for(int i=1;i<=n;i++){
		change[arr[i].pos]=brr[i].pos;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ta.add(change[i],1);
		ans=(ans+(i-ta.sum(change[i])));
	}
	outn(ans);
	return 0;
}
```


---

## 作者：绝顶我为峰 (赞：4)

~~难得切一个 E。~~

~~不过这个确实比较水。/youl~~

题目大意：将一个字符串翻转，每次可以交换相邻两个字符，求最少交换次数。

看到**交换相邻字符**这种操作，自然想到逆序对，显然逆序对的数量就是交换次数。

那么有一个很 naive 的想法就是给每个字符一个目标位置，生成一个目标序列，然后统计一遍这个序列的逆序对就好了。

难点在于这个字符串里是有相同字符的，这样我们直接将 $i$ 的目标位设置成 $n-i+1$ 显然不是最优解（参见样例）

显然，我们的目标就是要生成一个 $1\sim n$ 的排列 $a$，使得 $\forall1\leq i\leq n,stringvalue_i=stringvalue_{a_i}$，且 $a$ 的逆序对数量最少。（**这里认为原串下标是 $1\sim n$**）

那么自然我们想到对于相同字符，把他们的 $a_i$ 倒序赋值就是最优解。

这个结论比较显然，因为序列 $a$ 越接近升序，他的逆序对就越少。

所以我们统计一下每种字母出现位置，同种字母倒序构造目标序列就好了。

置于实现方法，数组 哈希 $vector$ $queue$ $set$ 什么的全都可以。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define int long long
string s;
int n,ans,a[200001],b[200001];
vector<int> v[31];
void qqsort(int l,int r)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    qqsort(l,mid);
    qqsort(mid+1,r);
    int i=l,j=mid+1,cnt=l-1;
    while(i<=mid&&j<=r)
        if(a[i]<=a[j])
            b[++cnt]=a[i++];
        else
        {
            ans+=mid-i+1;
            b[++cnt]=a[j++];
        }
    while(i<=mid)
        b[++cnt]=a[i++];
    while(j<=r)
        b[++cnt]=a[j++];
    for(register int i=l;i<=r;++i)
        a[i]=b[i];
}
signed main()
{
    scanf("%lld",&n);
    cin>>s;
    s=" "+s;
    for(register int i=1;i<=n;++i)
        v[s[i]-'a'].push_back(i);
    for(register int i=0;i<26;++i)
        for(register int j=0;j<(int)v[i].size();++j)
            a[v[i][j]]=v[i][v[i].size()-j-1];//倒序赋值
    for(register int i=1;i<=n;++i)
        a[i]=n-a[i]+1;//因为前面赋值的是没有经过倒序的位置，所以这里统一倒序
    //for(register int i=1;i<=n;++i)
        //cout<<a[i]<<endl;
    qqsort(1,n);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：JK_LOVER (赞：3)

# 分析
我们可以模拟一下样例 $aaaza$ 经过翻转之后变为了 $azaaa$ 。那么我们考虑哪些字母要交换位置，对于一个 $A_i \not= B_i$ 的位置，那么这个位置是必须要变动的。而对于相同字母，如果 $A_i = A_j (i<j)$ 而且 $B_{l}=B_{r}(l < r)$ ，那么把 $i$ 移动到 $l$ ， $j$ 移动到 $r$ 这个一定是最优的。那么现在我们就是要求对于每个字母到底要移动多少步。[更差的阅读体验。](https://www.luogu.com.cn/blog/xzc/solution-cf1430e)

- $aaaza$ 变为了 $azaaa$ 那么我们把对应位置写出来，应该为 $1,3,4,2,5$ ，那么通过观察我们其实就是要求这个序列的逆序对。满足 $val_i > val_j,i < j$ 找个树状数组就过了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL read() {
	LL x=0,f=0;char ch = getchar();
	while(!isdigit(ch)) {if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 2e6 + 100,M = 2e6;
LL A[N],B[N],n,ans,t[N],num[30];
char ch[N],s[N];
vector<LL> pos[30];
void add(LL a,LL b) {for(LL i=a;i<=M;i+=i&-i) t[i] += b;}
LL ask(LL a) {LL tot = 0;for(LL i=a;i;i-=i&-i) tot += t[i];return tot;}
int main() {
	scanf("%lld%s",&n,ch + 1);
	for(LL i = 1;i <= n;i++) s[i] = ch[n - i + 1];
	for(LL i = 1;i <= n;i++) pos[s[i]-'a'].push_back(i);
	for(LL i = 1;i <= n;i++) {
		LL c = ch[i] - 'a';
		A[i] = pos[c][num[c]];
		num[c]++;
	}
	for(LL i = 1;i <= n;i++) B[A[i]] = i;
	for(LL i = 1;i <= n;i++) {
		// cout << B[i] << " ";
		ans += ask(B[i]);
		add(1,1);add(B[i],-1);
	}
	// cout << endl;
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Flowery (赞：2)

# 简单描述：

显然，我们肯定不会对两个相同字符做交换。

因此可以根据每类字符的起点和对应的⽬的地，算出每个字符最终要转移到哪⾥。

如果两个字符的起始相对位置与⽬的相对位置前后顺序发⽣改变，就说明他们两个⼀定有⼀次交换。

因此问题变成求逆序对个数。

# e.g.

小样例 3 ：

	9  
	icpcsguru

对于原顺序：

	icpcsguru
	123456789

翻转后：

	urugscpci
	789652341

对于数列：789652341的逆序对个数，即为答案

所以，现在问题变成了：

1. 求出翻转后的序列顺序

2. 求出序列的逆序对个数

第一个问题的解决方法，可以用一个二位数组记录每个字母的出现顺序，倒过来之后直接赋值即可，效率O(2n)

第二个问题，求逆序对个数，可以直接用树状数组解决（树状数组大家应该都会写吧），就直接倒着枚n，值域树状数组记录就好啦！

# Code

```cpp
#define Flowery
#define maxn 400000
#define ll long long
#define rg register int     
#define lowbit(x) ((x)&-(x))                 
#include<bits/stdc++.h>
using namespace std;
int n,a[27][maxn],b[maxn],cnt[27],c[maxn];
ll ans;
char s[maxn],t[maxn];
void add(int x,int y)
{
	for(;x<=n;x+=lowbit(x))c[x]+=y;
}
int ask(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))ret+=c[x];
	return ret;
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)t[n-i+1]=s[i];
	if(strcmp(s+1,t+1)==0){printf("0");return 0;}
	for(int i=1;i<=n;i++)
	{
		a[t[i]-'a'+1][++cnt[t[i]-'a'+1]]=i;
	}
	for(int i=1;i<=26;i++)cnt[i]=0;
	for(int i=1;i<=n;i++)
	{
		b[i]=a[s[i]-'a'+1][++cnt[s[i]-'a'+1]];
	}
	for(int i=n;i>=1;i--)
	{
		add(b[i],1);
		ans+=ask(b[i]-1);
	}
	printf("%lld",ans);
	return 0;
}
```

[my blog](https://www.luogu.com.cn/blog/flowery/)

---

## 作者：do_while_true (赞：0)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13799080.html)

# E. String Reversal

### Translate

给定长度为 $n$ 的字符串，每次可以交换两个相邻位置的字符，求这个字符串到它原串反转后的串的最小交换次数。

$n\leq 2\cdot 10^5$

### Solution

最小交换次数，交换相邻的...想到逆序对。

有能力的读者就可以停下来了，仔细想想发现这是个非常常见的套路。

把原串反转后的串的第一个字符到最后一个字符依次给予一个递增的权值，然后再传递给原串相应的位置那个权值，发现就是[这道题](https://www.luogu.com.cn/problem/P1774)。

那原串的反串的各个位的权值可以 $1$ 到 $n$，这个已经确定了，怎么传递给原串对应字符呢？相同的字符传递给谁更优呢？

因为求的是逆序对个数，所以原串相同字符的权值也递增会使答案更小。

这样就比较简单了，处理一下每个字符的权值然后逆序对即可。

### Code

采用树状数组求解。

```cpp
#define ll long long

const int N = 1e6 + 10;

int n, a[N], cnt[N], go[N];
char ch1[N], ch2[N];
ll tree[N << 1], ans;

inline int lowbit(int x) { return x & (-x); }
ll sum(int x) { ll rsum = 0; for(; x; x -= lowbit(x)) rsum += tree[x]; return rsum; }
void modify(int x, ll k) { for(; x <= n; x += lowbit(x)) tree[x] += k; }

std::vector<int>vec[27];
signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		char now;
		std:: cin >> now;
		ch1[i] = now; ch2[n - i + 1] = now;
	}
	for(int i = 1; i <= n; ++i) {
		vec[ch2[i] - 'a'].push_back(i);
		++go[ch2[i] - 'a'];
	}
	for(int i = 1; i <= n; ++i) {
		int now = ch1[i] - 'a';
		a[i] = vec[now][cnt[now]++];
	}
	for(int i = 1; i <= n; ++i) {
		modify(a[i], 1ll);
		ans += i - sum(a[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

