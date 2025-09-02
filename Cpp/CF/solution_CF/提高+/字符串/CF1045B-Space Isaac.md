# Space Isaac

## 题目描述

似乎所有人都认为火星人是绿色的，但事实上他们是金属粉色且肥胖的。Ajs 有两个装有互不相同的非负整数的袋子。这两个袋子是不相交的，并且袋中数字的并集为 $ \{0,1,\ldots,M-1\} $，其中 $ M $ 是某个正整数。Ajs 从第一个袋子中取出一个数，从第二个袋子中取出另一个数，然后将它们的和对 $ M $ 取模。

请问有哪些模 $ M $ 的余数是 Ajs 无法通过这种方式得到的？


## 说明/提示

在第一个样例中，第一个袋子和第二个袋子分别包含 $ \{3,4\} $ 和 $ \{0,1,2\} $。Ajs 可以得到除余数 $ 2 $ 外的所有模 $ 5 $ 余数：$ 4 + 1 \equiv 0 $，$ 4 + 2 \equiv 1 $，$ 3 + 0 \equiv 3 $，$ 3 + 1 \equiv 4 $（模 $ 5 $）。可以验证不存在从两个袋子中选数使得和为 $ 2 $ 模 $ 5 $ 的情况。

在第二个样例中，第一个袋子包含 $ \{5,25,125,625\} $，而第二个袋子包含所有其他不超过 $ 9 $ 位十进制数的非负整数。每个模 $ 1\,000\,000\,000 $ 的余数都可以通过从两个袋子中各选一个数相加得到。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2 5
3 4
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
4 1000000000
5 25 125 625
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 4
1 3
```

### 输出

```
2
0 2
```

# 题解

## 作者：shadowice1984 (赞：6)

emmm……

字符串hash好题
__________________

首先我们先来想一个十分正常的暴力

我们把第二个数字的集合(就是那个最多有1e9个元素的集合)看成一个长度为$m$的01串,如果数字$i$出现在了第二个集合当中那这一位就是1否则就是0

接下来我们将整个集合加上$p$之后的得到的集合其实就是将这个01串循环右移$p$位之后的串

那么我们可以枚举第一个集合(就是那个最多有2e5个元素的集合)中的所有元素,然后让这个01串循环右移一下，最后把这些01串or起来得到一个新的01串,如果这个01串的第x位是0的话我们就无法表示出x这个数字了(因为刚才的暴力事实上是在枚举所有可能的相加情况)

接下来让我们想办法把这个$O(nm)$的暴力变成一个$O(n^2)$的暴力

我们把第二个数字的集合取一下补集(也就是把01串01翻转一下),接下来我们依然枚举一下第一个集合中所有的元素，然后让这个01串循环右移一下,最后把这些01串and一下之后的得到一个新的01串，如果这个01串的第x位是1的话我们就无法表示出x这个数字了(刚才的做法为什么是对的呢？根据德摩根律,一堆数or起来等于一堆数的补集and起来再取补)

那么我们看一下第二个数字的集合01翻转之后什么，显然这就是第一个数字的集合了

而刚才枚举第一个数字集合中的元素然后让这个01串循环右移的行为，其实是枚举了$O(n^2)$个数字相互相加然后对m取模的行为,而我们发现刚才的算法中我们的得到的新的01串中有一位是1当且仅当这个这一位在我们的$n$个01串当中都是1,换句话说，我们$O(n^2)$的枚举这些数字两两相加然后对$m$取模,如果一个数字在这个过程中出现了$n$次那么它不可以被成功表示(因为如果它出现了$n$次就说明它在$n$个01串中都是1)

那么我们现在得到了一个优秀的$O(n^2)$暴力,它有什么用呢？

首先我们会得到一个没什么用的结论是每个数字最多出现$n$次

十分显然，因为在模m剩余系下$a+x$和$a+y$肯定是不一样的(如果x,y小于m并且他俩不一样)

所以如果我们最后得到了一个数字$V$它出现了$n$次,假设有n对二元组$(i,j)$使得$a_{i}+a_{j} \equiv V (\mod m)$的话你会发现这些二元组的$i$值互不相同并且$j$值互不相同

那这又有什么用呢？

接下来的事情就比较玄学了

我们把这些二元组按照$a_{i}$值从小到大排个序

那么我们发现这些二元组的$a_{j}$一定是从大到小的一段和从大到小的一段拼到一起的

为什么呢？

因为我们发现一个十分重要的事实是$a_{i},a_{j} \leq m-1$

所以尽管我们的限制条件是$a_{i}+a_{j} \equiv V (\mod m)$,但是这两个数字的和最多有$V$和$V+m$两种取值

因此我们发现肯定是这个序列前一段$a_{j}$和它对应的$a_{i}$加起来是$V$的

然后后半段$a_{j}$加上它对应的$a_{i}$加起来就变成了$V+m$

我们的$a_{i}$是从小到大排序的，因此我们第一段j和第二段j都是从大到小排好序的并且第二段的最小值应该比第一段的最大值大(觉得不对的话可以自己画个图手玩一下)

换句话说我们的$a_{j}$应该是从大到小排好序的序列一个**轮换**，那么这样的轮换只有$O(n)$种我们可以挨个枚举一下进行验证(对了这样我们顺便证明了不能被表示的数最多$n$个)

那怎么验证呢？

我们现在相当于问你两个数组加起来是否是同一个数字

这个问题不是很好解决啊……

不过如果让我们牺牲一下正确率的话我们还是能办到的

那就是字符串$hash$

如果我们知道一个数组$A$的hash值和数组$B$的hash值的话，那么我们是可以计算出数组$A$和数组$B$按位相加的数组的$hash$值的，直接把A的hash值和B的hash值相加就可以了，同理我们无脑的把hash值相减就可以得到两个数组按位相减的hash值了

好了问题来了我们现在枚举了一个$a_{j}$从大到小排序的轮换，并且根据我们刚才的推倒过程来讲，前一半从大到小的$a_{j}$加上对应的$a_{i}$的结果应该是$V$，后一半从大到小的$a_{j}$加上对应的$a_{i}$的结果应该是$V+m$

问题来了处理$V+m$的时候我们的base明显是要炸掉的，此时我们将两个数组按位相加的得到的hash值没一点意义

怎么办呢？

转化一下

$$a_{i}+a_{j}=V+m$$

$$a_{i}-(m-a_{j})=V$$

好了现在我们的base就不会炸掉了，所以我们分别维护轮换的前半部分(这部分的字符串依然是$a_{j}$)和后半部分(这个时候的字符串中的值就变成了$m-a_{j}$)了

然后我们生成两个串按位相加后模m的hash值的时候就将前半部分的hash值相加，后半部分的hash值相减最后两个拼一起就可以生成我们想要的字符串了

好了最后一个问题，我们总算是得到了两个字符串按位相加的字符串的$hash$值了，怎么判断它是否是一个合法的串呢？

换句话说我们希望知道这个串是否是一个全部是一个数值比如说"xxxxxx"构成的串，并且如果它满足条件的话我们希望可以把$x$反解出来

怎么做呢？

假设这个字符串的hash值是$T$

那么这个字符串直接在最高位补x和将整个字符串右移一位后在末尾加x所得的应该是同一个字符串

所以我们可以列出这样的一个方程

$$baseT+x=T+base^{n}x$$

稍稍做一下变换就可以解出$x$了

$$x=\frac{(base-1)T}{base^{n}-1}$$

问题来了

就算我们的字符串是一个非法的字符串我们照样可以根据上面的式子解出一个$x$来……，但是我们知道此时的$x$一定是非法的,该怎么判断解的合法性呢？

~~双哈希一下比较一下解出来的两个x是不是一样就行了~~

嗯，解决方案就是如此的粗暴,不放心这个解法的正确性可以上三哈希

然后这题就做完了

所以我们的算法流程就是枚举轮换,按位相加，最后通过双哈希解出两个x来看一下是不是一样的，是一样的就是我们要的一个解

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;const int N=2*1e5+10;typedef long long ll;
inline ll po(ll a,ll p,ll mod){ll r=1;for(;p;p>>=1,a=a*a%mod)if(p&1)r=r*a%mod;return r;}
const ll mod1=1e9+7;const ll mod2=1e9+9;const ll bas=1e9+3;int n;int m;
ll a[N];ll b[N];ll pa1;ll pa2;ll sa1;ll sa2;ll pb1;ll pb2;ll sb1;ll sb2;
ll mi1[N];ll mi2[N];ll imi1[N];ll imi2[N];ll ans[N];int tp;ll inv1;ll inv2;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);sort(a+1,a+n+1);
    for(int i=1,j=n;i<=n;i++,j--)b[j]=a[i];
    mi1[0]=1;for(int i=1;i<=n;i++)(mi1[i]=mi1[i-1]*bas)%=mod1;
    mi2[0]=1;for(int i=1;i<=n;i++)(mi2[i]=mi2[i-1]*bas)%=mod2;
    //imi1[0]=1;for(int i=1;i<=n;i++)(imi1[i]=imi1[i-1]*750000005)%=mod1;
    //imi2[0]=1;for(int i=1;i<=n;i++)(imi2[i]=imi2[i-1]*166666668)%=mod2;
    for(int i=n;i>=1;i--)
        pa1=(pa1*bas+a[i])%mod1,pa2=(pa2*bas+a[i])%mod2,pb1=(pb1*bas+b[i])%mod1,pb2=(pb2*bas+b[i])%mod2;
    inv1=po(po(bas,n,mod1)+mod1-1,mod1-2,mod1);inv2=po(po(bas,n,mod2)+mod2-1,mod2-2,mod2);	
    for(int i=n;i>=0;i--)
    {
        ll t1=((pa1+pb1)+(sa1+mod1-sb1))%mod1;ll x1=(bas-1)*t1%mod1*inv1%mod1;
        ll t2=((pa2+pb2)+(sa2+mod2-sb2))%mod2;ll x2=(bas-1)*t2%mod2*inv2%mod2;
        if(x1==x2&&x1<m)ans[++tp]=x1;
        pa1=(pa1+mod1-a[i]*mi1[i-1]%mod1)%mod1;pa2=(pa2+mod2-a[i]*mi2[i-1]%mod2)%mod2;
        sa1=(sa1+a[i]*mi1[i-1])%mod1;sa2=(sa2+a[i]*mi2[i-1])%mod2;
        pb1=(pb1+mod1-a[i])*750000005%mod1;pb2=(pb2+mod2-a[i])*166666668%mod2;
        sb1=(sb1*750000005+mi1[n-1]*(m-a[i]))%mod1;sb2=(sb2*166666668+mi2[n-1]*(m-a[i]))%mod2;
    }printf("%d\n",tp);
    //for(int i=1;i<=tp;i++)ans[i]%=m;
    sort(ans+1,ans+tp+1);
    for(int i=1;i<=tp;i++)printf("%lld ",ans[i]);return 0;
}

```







---

## 作者：姬小路秋子 (赞：6)

写一篇略简洁的题解吧。

我们接下来都考虑不能被表示出来的数。

首先，这种数一定是(a[1]+a[i])%m ，因为如果(a[1]+a[i])%m表示不出这个数，那么说明这个数-a[1]肯定不在a里，那就一定能被表示出来。

然后你发现对于1...i，a[1]+a[i],a[2]+a[i-1]...都必须相等（等于a[1]+a[i]），因为不相等的话那就跟a[1]+a[i]那段的证法相同喽。

然后还得满足a[1]+a[i]+m==所有的a[i+1]+a[n],a[i+2]+a[n-1]...原理同上。

然后就是那段经典操作b[i]=a[i+1]-a[i]了（高明啊）

这种题现场过的都是神仙（对我来说

代码：

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
int n,ans;
ull m,pre[300001],nxt[300001],fac[300001],a[300001],b[300001],c[300001],p=569;
ull pd1(int l,int r){
	return pre[r]-pre[l-1]*fac[r-l+1];
}
ull pd2(int l,int r){
	return nxt[l]-nxt[r+1]*fac[r-l+1];
}
int ok(int l,int r){
	return pd1(l,r)==pd2(l,r);
}
int main(){
	int i,flag;
	scanf("%d%I64d",&n,&m);
	for(i=1;i<=n;i++)scanf("%I64d",&a[i]);
	for(i=1;i<n;i++)b[i]=a[i+1]-a[i];
	fac[0]=1;
	for(i=1;i<=n;i++)fac[i]=fac[i-1]*p;
	for(i=1;i<n;i++)pre[i]=pre[i-1]*p+b[i];
	for(i=n-1;i;i--)nxt[i]=nxt[i+1]*p+b[i];
	for(i=1;i<=n;i++){
		flag=1;
		if(i>1)flag&=ok(1,i-1);
		if(i<n){
			flag&=a[1]+a[i]+m==a[i+1]+a[n];
			if(i!=n-1)flag&=ok(i+1,n-1);
		}
		if(flag){
			c[++ans]=(a[1]+a[i])%m;
		}
	}
	sort(c+1,c+ans+1);
	printf("%d\n",ans);
	for(i=1;i<=ans;i++)printf("%I64d ",c[i]);
}
```

---

## 作者：迟暮天复明 (赞：3)

考虑到如果一个数 $k$ 无法被表示出来，那么对于每一个 $a_i$，一定存在一个 $a_j$ 使得 $(a_i+a_j)\bmod m=k$。

但是由于 $a_i+a_j<2m$，所以说 $a_i+a_j$ 的可能取值只有 $k$ 和 $m+k$。

同时，考虑和 $a_1,a_n$ 进行匹配的位置，不放设为 $a_l,a_r$，那么显然有 $l+1=r$，且对于所有 $1\le i\le l$ 有 $a_i+a_{l+1-i}=k$，对于所有 $r\le i\le n$ 有 $a_i+a_{r+n-i}=k+m$。

那么套路的我们就可以知道 $1\sim l$ 范围内和 $r\sim n$ 范围内的差分数组都是回文的，用哈希判断是否回文即可。

---

## 作者：pufanyi (赞：3)

感觉如果[$\color{black}\sf{s}\color{red}\sf{xd666}$](https://www.luogu.org/space/show?uid=84156)来做这题肯定能一眼秒，然而他正忙着切其他题。

首先我们发现如果要让$a + b \equiv x \pmod m$，如果已知$a, x$，那$b$一定是唯一的。也就是说，假设给定集合是$A$，与之对应的集合为$B$，如果有$a\in A$但找不到$b\in A$使得$a + b \equiv x\pmod m$。那么$x\in A + B$（定义$A + B = \{a + b : a\in A, b\in B\}$）。反过来讲，如果$x\notin A + B$，那么一定能把$A$中所有元素配对（可能两个数相同），也即$x\notin A + B \iff A = x - A$（定义$x - A= \{x - a : a\in A\}$）。

然后我们如果把小于$m$的整数看成一个环，如果有两个数$a, b$使$a + b \equiv x \pmod m$，$a$顺时针时针移动，$b$肯定逆时针移动（即运动方向相反，且移动的长度应该是相等的（$(a + k)\mod m + (b - k)\mod m \equiv a + b \pmod m$嘛）。

于是我们画两个圆，都表示集合$\{a_i\}$（假设$a_i$已经排好序），我们要把第一个圆的点与第二个圆的点匹配。

假设$a_i$与$a_j$匹配。我们把$i$移动至$i+1$，那么根据上面推出的单调性，$j$必须移至$j-1$（因为$a_i\sim a_{i+1}$之间没有数了，所以$j$也只能移动一格），又因为移动距离必须相等，即$a_{i+1} - a_i = a_j - a_{j-1}$。

所以我们令$b_i = a_{i} - a_{i-1}$（$b_1 = (a_1 - a_n)\mod m$），设串$s_1 = b_nb_{n-1}b_{n-2}\cdots b_1, s_2 = b_1b_2b_3\cdots b_n$，我们要找的是$s_1$与$s_2$成环后相等，并找到一对匹配的数，他们加起来模$m$即为一组解。我们令$s_3 = s_2 + s_2$，找到$s_3$中所有等于$s_1$的子串，就得到了所有解，这个问题用[KMP](https://pks-loving.blog.luogu.org/zi-fu-chuan-xue-xi-bi-ji-qian-xi-kmp-xuan-xue-di-dan-mu-shi-chuan-pi-post)或是[Z](https://blog.csdn.net/ZJZNKU/article/details/65447695)都能解决。

还是贴一下代码吧：

```cpp
#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 200005;

LL aa[maxn]; // 读入的a
LL bb[maxn]; // 即上面说的b
vector<LL> gou;
int in[maxn << 2];
LL Z[maxn << 2];
set<LL> ans;

int main()
{
	int n;
	LL m;
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%lld", &aa[i]);
	bb[1] = ((aa[1] - aa[n]) + m) % m;
	for(int i = 2; i <= n; ++i)
		bb[i] = ((aa[i] - aa[i-1]) % m + m) % m;
	for(int i = n; i; --i) // 这里用的是Z算法，所以合并成了一个串
	{
		gou.push_back(bb[i]);
		in[gou.size() - 1] = i;
	}
	gou.push_back(-1LL);
	for(int i = 1; i <= n; ++i)
	{
		gou.push_back(bb[i]);
		in[gou.size() - 1] = i;
	}
	for(int i = 1; i <= n; ++i)
	{
		gou.push_back(bb[i]);
		in[gou.size() - 1] = i;
	}
	Z[0] = gou.size();
	for(int i = 1, j = 1, k; i < (int) gou.size(); i = k) // Z算法
	{
		j = max(j, i);
		while(gou[j] == gou[j - i])
			++j;
		Z[i] = j - i;
		k = i + 1;
		while(k + Z[k - i] < j)
		{
			Z[k] = Z[k - i];
			++k;
		}
	}
	for(int i = 1; i < (int) gou.size(); ++i)
		if(Z[i] >= n) // 大力记录答案
			ans.insert((aa[in[i] - 1 ? in[i] - 1 : n] + aa[n]) % m);
	printf("%d\n", (int) ans.size());
	for(auto it = ans.begin(); it != ans.end(); ++it)
		printf("%lld ", *it);
	return 0;
}
```



---

