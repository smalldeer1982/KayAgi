# [LMXOI Round 1] Size

## 题目背景

在漆黑的夜晚，魔女带走了 LMX，HQZ 为了拯救 LMX。要完成魔女给出的任务。

## 题目描述

魔女给出一个长度为 $n$ 的序列 $d$，魔女想要求得：

$$\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}{((d_i\oplus d_j)+(d_i \otimes d_j))}$$

其中定义 $\oplus$ 代表二进制下两数相加的和数位上 $1$ 的个数， $\otimes$ 代表二进制下较大减较小的差数位上 $1$ 的个数。

## 说明/提示

**样例解释 #1**

如下表所示，因此答案为 $1 + 2 + 2 + 2 = 7$。
| $i$ | $j$ | $ans$ |
| :-----: | :-----: | :-------: |
| $1$ | $1$ | $1$ |
| $1$ | $2$ | $2$ |
| $2$ | $1$ | $2$ |
| $2$ | $2$ | $2$ |


对于 $100 \%$ 的数据，保证 $1 \le n\le 2\times 10^6,\sum\limits d_i\le5\times10^7$。 
| 子任务编号 |     $n$     |          特殊性质          | 分值 |
| :--------: | :------------------: | :-------------------------: | :--: |
| Subtask #1 |     $\le 2\times10^6 $     |   $d_i =1$       |  $10$  |
| Subtask #2 |     $\le 5000$     |      无      |  $20$  |
| Subtask #3 | $\le 2\times 10^6$ | $d_i$ 是 $2$ 的次幂 |  $30$  |
| Subtask #4 | $\le 2\times 10^6$ |      无      |  $40$  |

## 样例 #1

### 输入

```
2
1 3 ```

### 输出

```
7```

## 样例 #2

### 输入

```
10
114514 19 19 810 1477 44151 15260 369 2010 222```

### 输出

```
1396```

# 题解

## 作者：__Chx__ (赞：16)

## 题意
给出一个长度为 $n$ 的序列 $d$，求：

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}{((d_i\oplus d_j)+(d_i \otimes d_j))}$$

其中定义 $\oplus$ 代表二进制下两数相加所得到的 $1$ 的个数， $\otimes$ 代表二进制下较大的减较小的所得到的 $1$ 的个数。


我们发现当确定了 $\sum\limits d_i$ 后，种类数的量级也会被确定下来：当我们的序列形如 $0,1,2,3,4,5 \dots x$ 时，$d_i$ 的种类是最多的，但发现这个 $x$ 并不会很大，设 $s=\sum\limits d_i$，那么这个 $x$ 最多在 $\sqrt {s}$ 的量级，所以直接统计每种 $d_i$ 的数量暴力计算即可。

我们用 $V$ 表示值域上界，那么时间复杂度是 $O(s \log V)$ 的，预处理 $\operatorname{popcount}$ 可以做到 $O(s)$，题解给出的是 $O(s \log V)$ 的解法。

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e7+5;
template<typename T>inline void read(T &x){
    x=0;int f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x*=f;
}
int n,cnt[N],d,a[N],len;
long long ans;
inline int calc(int x){
    int res=0;
    while(x) ++res,x-=x&-x;
    return res;
}
int main(){
    read(n);
    while(n--){
        read(d);
        if(cnt[d]++==0) a[++len]=d;
    }
    for(int i=1;i<=len;++i)
        for(int j=1;j<=len;++j)
            ans+=1ll*cnt[a[i]]*cnt[a[j]]*(calc(a[i]+a[j])+calc(abs(a[i]-a[j])));
    printf("%lld",ans);
    return 0;
}

```

```


---

## 作者：int08 (赞：5)

## 前言
Never gonna give you up.

感觉被诈骗了。

# Solution

### 你好像意识到了什么
观察一下，题目让你求的东西有什么特点：

求两数二进制下和以及差数位上 $1$ 的个数。

这个玩意一眼就不太好求，因为即便在二进制下，加减也是有进或者退位的，这种位数统计题最常见的做法之分位统计就不太行得通了。

当你还在琢磨有没有什么办法消除位之间的影响的时候，你顺带看了一眼排行榜，有人 $3$ 分钟就做出来了。

然后你很机敏地看了一眼在比赛说明界面的 std 代码运行时间。

$2\times10^6$ 就 $63$ 毫秒？这连 $O(n\log d)$ 都做不到啊！

说明：**这是一道诈骗题。**

这使你充满了决心。

### 何为诈骗

既然知道是诈骗题了，那你肯定就需要留意题目中的每一个细节。

发现有一个条件我们全程没有用到：$\Sigma d_i \le 5 \times 10^7$。

照理来说它要表示数据范围，为什么要限定数据的和呢？这又不是多测……

你又想起了 std 的用时，只能说明，并不是每一个 $d_i$ 都用来计算了。

说明有些 $d_i$ 重复了。

那么本质不同的 $d_i$ 有多少？

即便最贪心地，从 $1$ 往上选择，也就 $\sqrt{\Sigma d_i}$ 级别的数就卡满了。

“你也许也意识到了这件事，$\oplus$ 和 $\otimes$ 是掩盖正解的虚像，$\Sigma d_i$ 正指引着我们的命运。”

直接桶排记录数字的出现次数，然后只需统计每个出现过的数字的贡献即可。

统计部分是简单的。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,i,j,d,tong[50000010],num[114514],cont[114514],cnt,ans;
int bitnum(int q)
{
	int ans=0;
	for(int i=1;i<=q;i=(i<<1)) if(q&i) ans++;
	return ans;
}
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>d;
		tong[d]++;
	}
	for(i=0;i<=50000000;i++)
	{
		if(tong[i])
		{
			cnt++;
			num[cnt]=i,cont[cnt]=tong[i];
		}
	}
	for(i=1;i<=cnt;i++)
	{
		for(j=1;j<=cnt;j++)
		{
			ans+=(cont[i]*cont[j]*(bitnum(num[i]+num[j])+bitnum(abs(num[i]-num[j]))));
		}
	}
	cout<<ans;
	return 0;
}
```

## 后记

我其实不太喜欢这道题，感觉做法与题面无关，正解都在数据范围上。

# The End.

---

## 作者：strcmp (赞：5)

题意已经很简洁了。希望你不会像我一样眼瞎看了几分钟没看到 $\sum d_i$ 的限制。

------------

注意到因为 $\sum d_i \le 5 \times 10^7$，不妨考虑不相同的数的个数。

最坏情况下 $d = \{ 0,\,1,\,2,\,3,\,\dots,\,w\}$，此时不重复的数最多的情况下和最小，不重复的数个数是 $w + 1$，总和为 $\frac{w(w + 1)}{2}$。

令 $\mathcal S \leftarrow \sum d_i$，$k$ 为最小的 $\frac{k(k + 1)}{2} \ge \mathcal S$，则必然 $k$ 不小于 $d$ 中不同的数的个数 $p$。

解上述不等式得 $p \le k + 1 < \frac{\sqrt{8\mathcal S + 1} + 1}{2} < \frac{4 \sqrt{\mathcal S} + 1}{2} < 2\sqrt{S}+ 1$。

所以 $d$ 中不同数的数量是 $\Theta(\sqrt {\sum d_i})$ 级别的，由于 $\sum d_i \le 5 \times 10^7$ 所以 $d$ 中不同数的数量 $p$ 最大不会超过 $14144$，直接暴力 $p^2$ 计算。

使用了一个 $\Theta(1)$ 的 `popcnt` 函数，时间复杂度 $\Theta(\sum d_i)$，带一个大概 $4$ 倍的常数，但实际情况下完全跑不满。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 2e4 + 10;
int p = 0, n, a[maxn], c[maxn * 2500];
inline int popcnt(int n) {
	n -= (n >> 1) & 0x55555555;
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = ((n >> 4) + n) & 0x0F0F0F0F, n += n >> 8, n += n >> 16;
	return n & 0x0000003F;
}
inline int Abs(int x) { return x < 0 ? -x : x; }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int w; scanf("%d", &w);
		if (!c[w]) a[++p] = w, ++c[w];
		else ++c[w];
	}
	ll ans = 0;
	for (int i = 1; i <= p; i++) ans += (ll)c[a[i]] * c[a[i]] * popcnt(a[i] << 1);
	for (int i = 1; i <= p; i++) {
		for (int j = 1; j < i; j++) {
			ans += (ll)c[a[i]] * c[a[j]] * (popcnt(a[i] + a[j]) + popcnt(Abs(a[i] - a[j]))) << 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Genius_Star (赞：4)

### 思路：

因为 $\sum\limits_{i=1}^n d_i \le 5 \times 10^7$，使得 $d$ 不重复最坏情况是 $d=[1 + 2 + 3 + \cdots +w]$ 的，则当前情况下 $\sum\limits_{i=1}^n d_i = \frac{w \times (w+1)}{2}$。

因为 $\frac{w \times (w+1)}{2} \le 5 \times 10^7$，可得 $w$ 最大为 $\frac{\sqrt{4 \times 10^8+1}-1}{2}$，约等于 $10^4$。

然后对于相同的数，暴力计算即可。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=5e7+10,M=10100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
bitset<64> A,B;
ll n,x,cnt,ans;
ll a[N],b[M];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x=read();
		a[x]++;
	}
	for(int i=0;i<N;i++)
	  if(a[i])
	    b[++cnt]=i;
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			A=b[i]+b[j],B=abs(b[i]-b[j]);
			ans+=(A.count()+B.count())*a[b[i]]*a[b[j]];
		}
	}
	write(ans);
	return 0;
}
```


---

## 作者：_zuoqingyuan (赞：4)

# 题意简述：
给出一个长度为 $n$ 的序列 $d$，求得：

$$\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}{((d_i\oplus d_j)+(d_i \otimes d_j))}$$

其中定义 $\oplus$ 代表二进制下两数相加的和数位上 $1$ 的个数， $\otimes$ 代表二进制下较大减较小的差数位上 $1$ 的个数。

对于所有数据，$n\le 2\times 10^6,\sum{d_i}\le 5\times 10^7$。
# 核心思路：
定义 $\operatorname{num}(x)$ 为 $x$ 二进制下 $1$ 的个数，显然 $(d_i\oplus d_j)=\operatorname{num}(d_i+d_j),(d_i \otimes d_j)=\operatorname{num}(\operatorname{abs}(d_i-d_j))$，其中 $\operatorname{abs}(x)$ 表示 $x$ 的绝对值。
## Sub1
特殊性质：所有的 $d_i=1$。
化简式子：
$$\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}{((1\oplus 1)+(1 \otimes 1))}=\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}{(\operatorname{num}(2)+\operatorname{num}(0))}$$
$$\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}{(\operatorname{num}(2)+\operatorname{num}(0))}=\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}1=n\times n$$

输出 $n \times n$，即可。
```cpp
void sub1(){
    cout<<(long long)n*n<<endl;
    return;
}
```
## Sub2
数据特点：$n\le 5\times 10^3$。
暴力，枚举每一个 $d_i,d_j$，计算其贡献，累加在 ans 中，输出答案
```cpp
int ABS(int x){
    return x<0?-x:x;
}
int num(int x){
    int cnt=0;
    while(x){
        if(x&1)cnt++;
        x>>=1;
    }
    return cnt;
}
void sub2(){
    ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ans+=num(d[i]+d[j])+num(ABS(d[i]-d[j]));
        }
    }
    cout<<ans<<endl;
    return;
}
```
## Sub3
特殊性质：$d_i$ 均为 $2$ 的非负整数次幂。

开始动脑子，因为 $\sum{d_i}\le 5\times 10^7$，而 $d_i$ 均为 $2$ 的非负次幂。说明 $d_i$ 顶多只有不到三十种取值。我们考虑每种取值为答案带来的贡献。

1. 如果 $d_i=2^k,d_j=2^{k'}$ 且 $k\ne k'$。那么 $\operatorname{num}(d_i+d_j)$ 的值必然为 $2$。因为 $d_i,d_j$ 在二进制下只有一个 $1$，且 $1$ 的位置不相同。

2. 如果 $d_i=2^k,d_j=2^{k'}$ 且 $k=k'$。那么 $\operatorname{num}(d_i+d_j)$ 的值必然为 $1$。因为 $d_i,d_j$ 在二进制下只有一个 $1$，且 $1$ 的位置相同。相加进位后原来的两个 $1$ 会进位成一个新的 $1$。

3. 如果 $d_i=2^k,d_j=2^{k'}$ 且 $k=k'$。那么 $\operatorname{num}(\operatorname{abs}(d_i-d_j))$ 的值必然为 $0$。两个相等的数差为 $0$，二进制下 $1$ 的个数自然为 $0$

3. 如果 $d_i=2^k,d_j=2^{k'}$ 且 $k\ne k'$。那么 $\operatorname{num}(\operatorname{abs}(d_i-d_j))$ 的值必然为 $\operatorname{abs}(k-k')$。可以自己举几个例子尝试一下。

用一个数组 $mk_i$ 表示数组 $d$ 中，$2^i$ 出现的次数，$len$ 表示 $d$ 数组中出现的 $2$ 的最高次幂。则最终答案为：
$$\sum\limits_{i=0}^{len}mk_i\times(2\times n-mk_i)+\sum\limits_{i=0}^{len}\sum\limits_{j=0}^{len}mk_i\times mk_j\times (i-j)$$

前面这一堆是上述 $1,2$ 两种情况对答案的贡献，表示有 $mk_i$ 个 $2^i$，每个 $2^i$ 和其他 $mk_i$ 个数的和在二进制下有一个 $1$，与 $n-mk_i$ 个数的和有 $2$ 个 $1$，化简后就是上式。

后面一堆则是 $4$ 这种情况的贡献。就不多赘述了。
```cpp
void sub3(){
	long long res=0,len=0;
	for(int i=1;i<=n;i++)mk[(int)log2(d[i])]++,len=max((long long)log2(d[i]),len);
	for(int i=0;i<=len;i++)res+=1ll*mk[i]*(2*n-mk[i]);
    for(int i=0;i<=len;i++){
        for(int j=0;j<=len;j++){
            res+=1ll*(mk[i]*mk[j]*ABS(i-j));
        }
    }
	printf("%lld\n",res);
	return;
}
```
## Sub4
令 $s=\sum d_i$，因为 $\sum d_i\le 5\times 10^7$，所以哪怕是最坏情况，$d_i$ 不同数的个数也不过在 $\sqrt{s}$ 左右，储存不同种类的数出现的数组 $mk$，暴力统计即可。
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N=5e7+10;
int n,mk[N],x;
vector<int>v;
long long ans=0;
int ABS(int x){
    return x<0?-x:x;
}
int num(int x){
    int cnt=0;
    while(x){
        if(x&1)cnt++;
        x>>=1;
    }
    return cnt;
}
int main(){
    scanf("%d",&n);
    v.push_back(0);
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        if(!mk[x])v.push_back(x);
        mk[x]++;
    }
    for(int i=1;i<v.size();i++){
        for(int j=1;j<v.size();j++){
            ans+=(long long)mk[v[i]]*mk[v[j]]*(num(v[i]+v[j])+num(ABS(v[i]-v[j])));
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
枚举不同种类数的两层循环复杂度 $O(s)$，内部计算 $(\log V)$，其中 $V$ 是值域大小。


---

## 作者：2huk (赞：2)

高质量诈骗题。

观察数据范围 $n \le 2 \times 10^6$，$\sum d_i \le 5 \times 10^7$，可以相同的数字很多。

我们先统计原来 $d$ 中每个元素出现的次数，然后将 $d$ 去重。若令 $len$ 表示去重后的 $d$ 的大小，$p_i$ 表示 $i$ 出现的次数，那么答案为：

$$
\sum_{i = 1}^{len}\sum_{j = 1}^{len} p_ip_j((i \oplus j) + (i \otimes j))
$$

上面的 $\oplus$ 和 $\otimes$ 就是题目中的运算。

上面的 $len$ 其实趋近于 $\sqrt{\sum d_i}$，所以总复杂度约为 $\Theta\left(\sum d_i\right)$。

```cpp
for (int i = 1; i <= n; ++ i ) p[a[i]] ++ ;
sort(a + 1, a + n + 1);
int len = unique(a + 1, a + n + 1) - a - 1;
for (int i = 1; i <= len; ++ i )
	for (int j = 1; j <= len; ++ j )
		res += (pop(a[i] + a[j]) + pop(abs(a[i] - a[j]))) * p[a[i]] * p[a[j]];
cout << res;
```

---

## 作者：zzy0618 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P10114)

### 大体思路

一开始看到 $\sum d_i \le5\times10^7$ 时不知道是什么，于是考虑 Subtask #3。因为他是 $2$ 的次幂，所以相同的数应该很多，所以用一个 ```map``` 存一下。对于不同的两个数 $a,b$，只需要计算 $(a\oplus b+a\otimes b)\times sum_a\times sum_b$。其中 $sum_x$ 表示 $x$ 的个数。

提交之后竟然全部过了。再次观察这个性质，假设我们希望 $b$ 数组中不同的数尽量的多，肯定要像 $1,2,3,4...$ 这样安排然而到 $\sqrt{\sum b_i}$ 左右级别的时候，就已经达到 $\sum b_i$。这里的求和公式相信不用多说。所以在这样的情况下，先去重，再批量计算，时间复杂度为 $O(\sqrt{\sum b_i}\times \sqrt{\sum b_i} \times \log_2(\sqrt{\sum b_i}))$，也就是 $O(\sum b_i \log_2 \sum b_i)$，当然这跑不满。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
map<int,int> mp;
map<int,int>::iterator it,ti;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;++i)	
		cin>>x,++mp[x];
	for(it=mp.begin();it!=mp.end();++it){
		for(ti=mp.begin();ti!=mp.end();++ti){
			int c=it->first,d=ti->first;
			int s=c+d,t=max(c,d)-min(c,d);
			ans+=(__builtin_popcountll(s)+__builtin_popcountll(t))*it->second*ti->second;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：harmis_yz (赞：1)

## 分析

考虑暴力。

注意到 $\sum d_i \le 5\times 10^7$，在最坏情况下（即 $d_i=1,2,3,\dots$）不同的 $d_i$ 是 $\sqrt{n}$ 的。然后就是暴力，将 $d$ 去重之后统计出 $cnt_i$，表示 $i$ 这个数在去重之前的数量。枚举 $i,j$，求出和与差的二进制中 $1$ 的数量和，计为 $c$。则 $d_i'$ 这个数和 $d_j'$ 和与差的二进制 $1$ 的数量和为：$c \times cnt_{d_{i}'} \times cnt_{d_{j}'}$。

复杂度 $O(\sum d_i \log V)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=5e7+10,M=5e6+10;
int n,a[M];
int b[M],idx;
int Cnt[N];

il void solve(){
	n=read();
	for(re int i=1;i<=n;++i) a[i]=read(),b[++idx]=a[i],++Cnt[a[i]];
	sort(b+1,b+n+1),idx=unique(b+1,b+n+1)-(b+1);
	long long ans=0;
	for(re int i=1;i<=idx;++i){
		for(re int j=1;j<=idx;++j){
			int he=b[i]+b[j],cha=b[i]-b[j];
			int cnt=0;
			while(he) cnt+=he&1,he/=2;
			while(cha) cnt+=cha&1,cha/=2;
			ans+=cnt*(Cnt[b[i]]*Cnt[b[j]]);
		}
		
	}
	cout<<ans;
   	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：sbno333 (赞：1)

显然这道题看上去不可做，但注意到神奇的数据范围，因此种类数最多只有 $\sqrt{\sum d_i}$ 次。

证明：

贪心可以得到为了使种类数尽量多，$d_i$ 尽量小，则有 $d_i=i$。

则求最大 $n$ 使得 $\sum\limits_{i=1}^{n}i\le5\times10^7$。

所以 $n^2+n\le10^8$。

所以 $n\le10^4$。

那么我们将相同的存起来，接着凭借洛谷神机跑暴力，在乘上方案数，也就是出现次数的积，我这里卡了一下常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct st{
	int s,t;	
}sd[2000009];
int inn;
int a[2000009]={-1};
short ff[50000009];
int kkk(int sb){
	if(sb<0){
		sb=-sb;
	}
	if(sb<=50000000){
		if(ff[sb]){
		return ff[sb];
	}
	}
	
	int ccf;
	ccf=sb;
	int ans;
	ans=0;
	while(sb){
		ans++;
		sb-=sb&(-sb);
	}
	if(ccf<=50000000){
		ff[ccf]=ans;
	}
	return ans;
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1]){
			sd[inn].t++;
			continue;
		}
		sd[++inn].s=a[i];
		sd[inn].t=1;
	}
	int ans;
	ans=0;
	for(int i=1;i<=inn;i++){
		for(int j=1;j<=i;j++){
			ans+=sd[i].t*sd[j].t*(kkk(sd[i].s+sd[j].s)+kkk(sd[i].s-sd[j].s));
		}
	}
	ans*=2;
	for(int j=1;j<=inn;j++){//去掉重复的
			ans-=kkk(2*sd[j].s)*sd[j].t*sd[j].t;
		}
	cout<<ans;
	return 0;
}
```

~~如果变量名有歧义，仅为本人习惯编写的变量名，如果有不同变量名挨在一起，仅为巧合，请勿当真。~~

本题有意思的点在于 $1145141919810$，巧合的是题号是 $10114$。

---

## 作者：Clay_L (赞：1)

### 题意简述

给定 $n$ 个数，问把这 $n$ 个数分别两两相加或相减取绝对值（两个数的下标可以一样）化成二进制后 `'1'` 的个数。

### 算法分析

一种有技巧的暴力。

先把那 $n$ 个数拿桶存每个数出现的次数，把所有出现过的数去重后存入一个数组（设其长度为 $\text{cnt}$），再以 $O(\text{cnt}^2)$ 的时间复杂度去暴力扫一遍。再用组合数学和一些方法得出化成二进制后 `'1'` 的个数（这里我用的是以 $\text{lowbit}$ 为基础的 $\text{popcount}$）即可得出答案。

时间复杂度怎么计算呢？好吧其实我不知道。但是以数据范围中的 $\sum d_i\le5\times10^7$ 即可得出当 $n$ 取一个比较大的值时，$d_i$ 肯定有较多重复。所以就可以得出用此方法此题可过。

下方代码有注释，若有不懂可以在下方评论。

### 放个代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(NuM) (NuM&-NuM)//lowbit一个数二进制中最低的一个'1'的位置
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=10*x+ch-'0',ch=getchar();
	return x*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n=read(),a[2000010],b[2000010],mp[50000010],cnt,ans;
bool rec[50000010];
inline int popcount(int x){//不断求最低位再减掉得出'1'的个数
	int sum=0;
	while(x)sum++,x-=lowbit(x);
	return sum;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	for(int i=1;i<=n;i++){
		a[i]=read(),mp[a[i]]++;//桶
		if(!rec[a[i]])rec[a[i]]=1,b[++cnt]=a[i];//去重操作
	}
	for(int i=1;i<=cnt;i++){//暴力操作
		for(int j=1;j<=cnt;j++){
			ans+=popcount(b[i]+b[j])*mp[b[i]]*mp[b[j]];
			ans+=popcount(abs(b[i]-b[j]))*mp[b[i]]*mp[b[j]];
            /*组合数学:个数*个数=组合后的组数*/
		}
	}
	write(ans);
	return 0;
}
```

呵呵完结撒花。

---

## 作者：This_Rrhar (赞：1)

注意到 $\sum d_i\le5\times10^7$。

考虑对 $d$ 序列进行去重，记录下每个数值及其出现次数，再两两计算其贡献。

因为当 $d$ 序列两两不同时至多有 $\sqrt{5\times10^7}$ 个数，故时间复杂度为 $O(n\log n+\sum d_i)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _r return*this
#define _o &operator
namespace IO
{
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		char gc(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		input _o>>(char&num){do num=gc();while(num==' '||num=='\n'||num=='\r'||num=='\t');_r;}
		template<typename T>input _o>>(T&x)
		{
			char c=gc();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=gc();
			while(isdigit(c))x=(x*10)+(c^48),c=gc();
			x*=f;_r;
		}
		input(){}
	}in;
	long long read(){long long x;return in>>x,x;}
	struct output
	{
		void pt(char num){*pp++=num;if(pp-pb==_S)fl();}
		output _o<<(char num){pt(num);_r;}
		template<typename T>output _o<<(T x)
		{
			if(!x){pt(48);_r;}
			if(x<0)pt('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)pt(s[t--]+48);
			_r;
		}
		output _o<<(const char*s2){int num=0;while(s2[num])pt(s2[num++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
}
using IO::in;
using IO::out;
using IO::read;
using ll=long long;

#define N 2000001

ll n,m;

ll a[N];

pair<ll,ll>b[N];

ll ans;

int main()
{
	in>>n;
	for(int i=1;i<=n;i++)in>>a[i];
	sort(a+1,a+1+n),b[++m]={a[1],1};
	for(int i=2,j=1;i<=n;i++)
		if(a[i]==a[j])b[m].second++;
		else b[++m]={a[i],1},j=i;
	for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)
		ans+=(__builtin_popcountll(b[i].first+b[j].first)+__builtin_popcountll(abs(b[i].first-b[j].first)))*b[i].second*b[j].second;
	out<<ans;
}
```

---

## 作者：ForwardStar (赞：1)

注意到 $\sum d_i\leq5\times10^7$，而公差为 $1$ 的等差数列的增长趋势是平方的，所以数值不同 $d_i$ 最多大约只有 $\sqrt{\sum d_i}$ 个，统计出后直接暴力做即可。  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 55, K = 30, INF = 1e9, MOD = 1e9 + 7;
int n;
long long ans;
int a[N], b[N], cnt[N];
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	int idx = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] != a[i - 1]) idx++;
		b[idx] = a[i];
		cnt[idx]++;
	}
	for (int i = 1; i <= idx; i++) {
		for (int j = 1; j <= idx; j++) {
			long long tot = 0;
			int nk = b[i] + b[j];
			int mk = b[i] - b[j];
			if (mk < 0) mk *= -1;
			while (nk) {
				tot += nk & 1;
				nk >>= 1;
			}
			while (mk) {
				tot += mk & 1;
				mk >>= 1;
			}
			ans += tot * cnt[i] * cnt[j];
		}
	}
	printf("%lld\n", ans);
	return 0;
}

```


---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10114)

赛时靠评测机返回得出，除了 Subtask 3 外，两数最大和 $\le2\times10^4$，直接 $\mathcal{O}((2\times10^4)^2=4\times10^8)$，再判断 Subtask 3 就过了。

还是来讲正解。注意到 $\sum\limits d_i$ 的值很小，平均下来每个测试点中 $d_i$ 的平均值为 $\dfrac{5\times10^7}{2\times10^6}=25$，且 $d_i$ 的值很容易重复。

于是我们将原序列 $d$ 去重，这样 $\mathcal{O}(n^2)$ 就可行了。计算的话直接用 $d_i$ 在原序列出现次数乘上 $d_j$ 在原序列出现次数再乘上答案就行了。

最后注意不要见祖宗了。代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
#define itn int
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
inline string jia(string a1,string b1){int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=max(lena,lenb),t=0;for(int i=0;i<lenc;i++){c[i]=a[i]+b[i]+t;if(c[i]>=10){t=1,c[i]%=10;}else{t=0;}}if(t==1){lenc++;c[lenc-1]=1;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline string jian(string a1,string b1){if(a1.size()<b1.size()||a1.size()==b1.size()&&a1<b1){pc('-'),swap(a1,b1);}int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=lena;for(int i=0;i<lenc;i++){if(a[i]<b[i]){a[i+1]--,a[i]+=10;}c[i]=a[i]-b[i];}while(lenc>=1&&c[lenc-1]==0){lenc--;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline int qpow(int a,int b,int p){int ans=1;while(b){if(b&1){ans=(ans*a)%p;}b>>=1;a=(a*a)%p;}return ans;}
inline int qp(int a,int b){int ans=1;while(b){if(b&1){ans*=a;}b>>=1;a*=a;}return ans;}
int a[2000010];
int b[50000010],c[2000010];
signed main()
{
	int n;
	rd(n);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		rd(a[i]);
		if(!b[a[i]])
		{
			c[++cnt]=a[i];
		}
		b[a[i]]++;
	}
	int ans=0;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=1;j<=cnt;j++)
		{
			ans+=(__builtin_popcount(c[i]+c[j])+__builtin_popcount(abs(c[i]-c[j])))*b[c[i]]*b[c[j]];
		}
	}
	wtl(ans);
	return 0;
}
```

---

## 作者：Z3k7223 (赞：0)

update 2024/03/02 洛谷专栏区更新导致 $\LaTeX$ 炸了，修了一下并添加了时间复杂度部分，麻烦管理员通过。

[题目链接](https://www.luogu.com.cn/problem/P10114)

## 题意

给定长度为 $n$ 的序列 $a$，求

$$\sum_{i=1}^n \sum_{j=1}^n f(a_i+a_j)+f(\left\vert a_i-a_j\right\vert)$$

其中 $f(x)$ 为 $x$ 在二进制下 $1$ 的个数。

## 做法

第一眼：$n\le 2\times 10^6$，直接想 $O(n \log n)$ 或者 $O(n)$ 做法。

然而在尝试 114514 秒后：什么玩意？

再看一眼，又发现了一个东西：$\sum\limits d_i\le5\times10^7$！

那么显然这个序列的最大值不超过 $5\times10^7$，序列里不同元素的个数不超过 $\sqrt{2 \times n}$。

简单证明第二点：

假设序列中的元素互不相同，当序列和最小时即为 $1$，$2$，$3$，$\cdots$，$n$。

设序列和为 $S$ ，这时 $S=\frac{n(n+1)}{2}$。

解得 $n$ 约为 $\sqrt{2 \times S}$，当 $S=5 \times 10^7$ 时，序列中不同数字的个数取 $10^4$。

到这里做法就很显然了，只需要枚举所有不相同的 $x$ 和 $y$，记它们在序列中出现的次数为 $cnt_x$ 和 $cnt_y$，根据乘法原理，它们对答案的贡献为 $cnt_x \times cnt_y \times f(x+y)+f(\left\vert x-y\right\vert)$。

## code:

在实现时，我使用了 STL 里的排序和去重函数以及内建的 `__builtin_popcount` 函数。另外，由于 $f(i+j)+f(\left\vert i-j\right\vert)=f(j+i)+f(\left\vert j-i\right\vert)$ ，所以我们可以减少一半的计算量，当 $i \ne j$ 时计算两次贡献即可。

时间复杂度 $O(n^2)$，其中 $n$ 取 $10^4$，可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e6 + 10, M = 5e7 + 10;
int n;
int a[N], cnt[M];

inline ll f(int x, int y) {
	ll ret = __builtin_popcount(x + y) + __builtin_popcount((abs(x - y)));
	ret *= (ll)cnt[x] * cnt[y];
	return x == y ? ret : ret << 1LL;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		++cnt[a[i]];
	}
	sort(a + 1, a + 1 + n);
	int tot = unique(a + 1, a + 1 + n) - a - 1;
	ll ans = 0;
	for (int i = 1; i <= tot; i++) {
		for (int j = 1; j <= i; j++) {
			ans += (ll)f(a[i], a[j]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：_GeorgeAAAADHD_ (赞：0)

## 题目大意

给定 $n$ 个不同的数，你需要求出任意两个数（顺序不同算两对，可以自己和自己算一对）的和与差的绝对值在二进制下数字 $1$ 的个数总和。

## 分析

我们注意到 $\sum d_i \le 5\times10^7$，因此不同的数字最多有 $\sqrt{d_i}$ 个，所以可以计算相同的数字个数之后再计算。

时间复杂度 $O(d_i\times \log_2 d_i)$，但是这个东西跑不满，因此可以过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int> mp;
int n,d[2000005],t[32],s[100005],cnt=0;
bool f=0;
inline int read(){
	int x=0;
	char c=getchar();
	while(c<48||c>57)c=getchar();
	while(c>=48&&c<=57)x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
inline void write(long long x){
	if(x>9)write(x/10);
	putchar(x%10+48);
}
inline int pc(int x){
	int a=0;
	while(x){
		if(x&1)a++;
		x>>=1;
	}
	return a;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;i++){d[i]=read();mp[d[i]]++;if(mp[d[i]]==1)s[++cnt]=d[i];}
	long long ans=0;
	for(register int i=1;i<=cnt;i++){
		for(register int j=1;j<=cnt;j++){
			ans+=1ll*(pc(s[i]+s[j])+pc(abs(s[i]-s[j])))*mp[s[i]]*mp[s[j]];
		}
	}
	write(ans);
	return 0;
}

---

## 作者：ZHONGZIJIE0608 (赞：0)

**题意简述**

给定一个长度为 $n$ 的序列 $d$，求：
$$\sum\limits_{i=1}^{ n}\sum\limits_{j=1}^{n}{((d_i\oplus d_j)+(d_i \otimes d_j))}$$

其中定义 $\oplus$ 代表二进制下两数相加的和数位上 $1$ 的个数，$\otimes$ 代表二进制下较大减较小的差数位上 $1$ 的个数。

**算法分析**

由题可知 $1 \le n\le 2\times 10^6,\sum\limits d_i\le5\times10^7$。

因为 $\sum_{i=1}^{10^{4}}i = 50005000 \gt 5 \times 10^{7}$，所以显然有最多 $10^{4}$ 个不同的 $d_{i}$。

开个桶记录不同 $d_{i}$ 的个数，枚举值域中存在的数直接计算即可。

时间复杂度为 $O(d^{2})$，其中 $d$ 表示 不同 $d_{i}$ 的个数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10,M=5e7+10;
int d[N],n,ans=0;
inline int pop(int x){int s=0;while(x){s+=(x&1);x>>=1;}return s;}
inline int Abs(int x){return x<0?-x:x;}
unordered_map<int,int>t;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;for(int i=1;i<=n;++i)cin>>d[i],++t[d[i]];
	for(auto i:t){
		for(auto j:t){
			ans+=i.second*j.second*(pop(i.first+j.first)+pop(Abs(i.first-j.first)));
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：sangshang (赞：0)

# Description

给一个长度 $n$ 序列 $a$，求出：

$$\sum_{i=1}^{n}\sum_{j=1}^{n}f(a_i+a_j)+f(abs(a_i-a_j))$$

$f(b)$ 是指 $b$ 在二进制下 $1$ 的个数。

# Solution

第一眼看上去，$n\le 2\times 10^{6}$，好像是要线性算法，使用暴力计算时间复杂度 $O(n^2)$ 加上特殊性质只能拿 $30\textmd{pts}$。

发现题目中有一句话 $\sum a_i\le 5\times 10^{7}$。可以想，考虑 $a$ 是元素不重复的情况下和尽可能小的整数序列，即 $a$ 是正整数序列，$\sum_{i=1}^{n}a_i=\frac{n\times(n-1)}{2}$。而 $\sum a_i\le 5\times 10^{7}$ 使得序列 $a$ 在 $n$ 比较大地情况下一定会有大量重复元素。具体地，去重后 $a$ 的元素个数 $\le \sqrt{5\times 10^{7}\times 2}$，$O(n^2)$ 算法可以解决。

对于元素 $x$ 有 $|x|$ 个，元素 $y$ 有 $|y|$ 个，它两能组成 $|x|\times|y|\times 2$ 个匹配，而元素 $x$ 本身能组成 $|x|^2$ 个匹配。

于是就有了优雅又暴力的代码。

# Code

```cpp
#include <bits/stdc++.h>
#define maxn 2000005

using namespace std;
int a[maxn];
int Map[50000005];
#define lowbit(a) (a&(-a))

namespace IO {
	const int LEN = (1 << 21);
	char buf[LEN], *front = buf, *back = buf;
#define GetChar() ((front==back)&&(back=(front=buf)+fread(buf,1,LEN,stdin),front==back)?EOF:(front++)[0])
	inline int read() {
		int res = 0;
		bool flag = false;
		char ch = GetChar();
		while (ch < '0' || ch > '9') {
			if (ch == '-') {
				flag = true;
			}
			ch = GetChar();
		}
		while (ch >= '0' && ch <= '9') {
			res = res * 10 + ch - '0';
			ch = GetChar();
		}
		return flag ? -res : res;
	}
}
using namespace IO;

inline int check(int a) {
	int res = 0;
	while (a) {
		a ^= lowbit(a);
		++res;
	}
	return res;
}

int main() {
	int n;
	n = read();
	//scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		//scanf("%d", &a[i]);
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) {
		++Map[a[i]];
	}
	int cnt = unique(a + 1, a + n + 1) - a - 1;
	long long sum = 0;
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j < i; ++j) {
			sum += (check(a[i] + a[j]) + check(abs(a[i] - a[j]))) * (long long)Map[a[i]] * Map[a[j]] * 2;
		}
		sum += (check(a[i] + a[i]) + check(abs(a[i] - a[i]))) * Map[a[i]] * (long long)Map[a[i]];
	}
	printf("%lld\n", sum);
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

# Solution
 
这道题只想出了 $O(n^2)$ 的做法，赛场上还没卡过去，又经过一些优化后终于过了。

## Subtask #1,#2

暴力，按题意模拟，就不说了，双重循环跑一遍就行。

## Subtask #3

因为告诉了序列和不超过 $5\times10^7$，还都是非负整数，所以最大数也不会超过 $5\times10^7$。估算一下就会发现最多到 $2^{35}$，那么就会产生许多重复的数。

于是，我们就记录每个数出现次数，并把多次出现的删掉只剩 $1$ 个。计算时，每一对只需要乘上两个数个数。

另外，不难看出，$(i,j)$ 与 $(j,i)$ 的结果是相同的，乘二即可。

## Subtask #4

与上述相同，虽然范围更大，但卡卡常就能过去。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[2000005];
__int128 ans;
map <long long,int> m;
inline long long lowbit(long long x)
{
	return x&(-x);
}
inline long long read()
{
	long long x=0,f=1;
	char ch=0;
	while(ch<'0'||ch>'9')
	{ 
    	if(ch=='-') 
			f=-1;
    	ch=getchar();
  	}
  	while(ch>='0'&&ch<='9')
  		x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
  	return x*f;
}
inline void write(__int128 x)
{
	if(x>=10)
		write(x/10);
	putchar(x%10+'0');
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(m[a[i]])
		{
			n--;
			i--;
			m[a[i+1]]++;
			continue;
		}
		m[a[i]]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			long long x=a[i]+a[j],cnt=0;
			while(x)
				x-=lowbit(x),cnt+=1+(i!=j);
			x=abs(a[i]-a[j]);
			while(x)
				x-=lowbit(x),cnt+=1+(i!=j);
			ans+=cnt*m[a[i]]*m[a[j]];
		}
	write(ans);
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

有趣的暴力，很像 [P8572](https://www.luogu.com.cn/problem/P8572)。

我们可以将 $d_i$ 统计数量后计算答案。具体来说，设 $cnt_i$ 为 $i$ 出现的次数，则两个数 $i,j$ 对答案的贡献为：$cnt_i\times cnt_j\times ((i\oplus j)+(i\otimes j))$，暴力计算即可。

关于为何暴力可过，此处给出证明：

首先，上述序列的时间复杂度为 $O((size^2\log\max d_i)$，其中 $size$ 指 $d$ 中不同元素的数量（有 $\log\max d_i$ 是因为要处理 $\operatorname{lowbit}$）。

其次，在此复杂度下，$d$ 的最坏情况为 $1,2,3,\cdots a$，此时复杂度为 $O(a^2\log a)$，$\sum d_i=a\times(a-1)\div2\approx a^2$，我们注意到题面中 $\sum d_i\le 5\times 10^7$，所以上述暴力法最多被卡到 $O(\sum d_i\times(\log\sqrt{\sum d_i}))$。由于你谷评测机过于强大，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=5e7+5;
int n,d,ans;
int cnt[N];
vector<int> v;

int lowbit(int x){
	return x&-x;
}

int popcount(int x){
	int ans=0;
	while(x){
		x-=lowbit(x);
		ans++;
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d;
		if(cnt[d]==0) v.push_back(d);
		cnt[d]++;
	}
	int l=v.size();
	for(int i=0;i<l;i++){
		for(int j=0;j<l;j++){
			ans+=cnt[v[i]]*cnt[v[j]]*(popcount(v[i]+v[j])+popcount(abs(v[i]-v[j])));
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

## 思路

~~暴力碾标算~~！

我们要好好利用 $\sum\limits d_i\le5\times10^7$ 的性质啊，于是就可以发现最多只有 $10000$ 个不同的数。

于是我们记录每一个数字的思路，然后排序去重，最后正常暴力即可。

注意要把循环控制在 $10000^2\div2$，不可以真的傻傻 $10000^2$。


---

```C++
/*
CB Ntsc
*/

#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define err cerr<<"Error"
#define rd read()
// #define nl putc('\n')
#define ot write
#define nl putchar('\n')
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int INF = 1e13;
const int N = 2e6+5;
const int M = 1e6+5;
const int S=1e6+5;
const int maxlog = 10;

int n,ans;
int d[N];
map<int,int> cnt;

inline int popc(int a){
  int res=0;
  while(a){
    if(a&1){
      res++;
    }
    a>>=1;
  }
  return res;
}


signed main(){
  n=rd;
  for(int i=1;i<=n;i++){
    d[i]=rd;
    cnt[d[i]]++;
  }
  sort(d+1,d+n+1);
  n=unique(d+1,d+n+1)-d-1;
  for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
      int a=d[i],b=d[j];
      if(a<b)swap(a,b);
      ans+=cnt[a]*cnt[b]*2*(popc(a+b)+popc(a-b));
    }
  }
  for(int i=1;i<=n;i++){
    int a=d[i];
    ans+=cnt[a]*cnt[a]*(popc(a+a)+popc(a-a));
  }
  write(ans);
}
```




---

## 作者：xz001 (赞：0)

首先我们发现序列中的元素个数是根号级别的，因为总共的和 $\sum d_i$ 不超过 $5\times 10^7$，所以若每个元素都不同，那 $n$ 个元素和至少为 $\sum_{i=1}^{n}i=\frac{n(n+1)}{2}$，大约 $\sqrt {\sum d_i}$ 个元素和就超过 $\sum d_i$ 了，所以我们统计每个元素的个数，然后将序列去重，暴力枚举即可。

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define int long long

// typedef
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

// const
const int N = 1e6 + 10, M = 2e6 + 10;
const int INF = 2e9, P = 998244353;
const double eps = 1e-6;



// debug
const bool DeBug = true;
int db_cnt;
il void db() { if (DeBug) puts("--------------"); return; }
il void db(auto a) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << '\n'; return; }
il void db(auto a, auto b) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << '\n'; return; }
il void db(auto a, auto b, auto c) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << '\n'; return; }
il void db(auto a, auto b, auto c, auto d) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << '\n'; return; }
il void db(auto a, auto b, auto c, auto d, auto e) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << ", " << e << '\n'; return; }
il void db(auto *a, auto len) { if (DeBug) { ++ db_cnt; cout << "-- | t" << db_cnt << " : {"; if (!len) cout << "empty";else { cout << a[1]; for (int i = 2; i <= len; ++ i ) cout << ", " << a[i]; } cout << "}\n"; } return; }
il void db(pair<auto, auto> a) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : <" << a.first << ", " << a.second << ">\n"; return; }

// common functions
il int Max(co int a, co int b) { return a > b ? a : b; }
il int Min(co int a, co int b) { return a < b ? a : b; }
il int read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { (c == '-') ? f = false : 0; c = getchar(); }while (c > 47 && c < 58) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(re auto x) { (x < 0) ? putchar('-'), x = -x : 0; (x > 9) ? write(x / 10) : void(); putchar(x % 10 + 48); return; }
il void wel(co auto x) { write(x), putchar('\n'); return; }
il void wel(co auto x, co int y) { write(x), putchar(' '), write(y), putchar('\n'); return; }
il void wel(co auto x, co int y, co int z) { write(x), putchar(' '), write(y), putchar(' '), write(z), putchar('\n'); return; }
il void wsp(co auto x) { write(x), putchar(' '); return; }

int n, a[M], ans, b[M];

bool f = true, is = true;

int cnt[50000001];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i), f &= a[i] == 1, is &= __builtin_popcount(a[i]) == 1;
    if (f) {
    	printf("%lld\n", n * n);
    	return 0;
	}
	for (int i = 1; i <= n; ++ i) b[i] = a[i], ++ cnt[a[i]];
    sort(b + 1, b + n + 1);
    n = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++ i) {
	   	for (int j = 1; j <= n; ++ j) {	    	
		   	ans += (__builtin_popcount(b[i] + b[j]) + __builtin_popcount(abs(b[i] - b[j]))) * cnt[b[i]] * cnt[b[j]];
		}		}
	printf("%lld\n", ans);
	return 0;
}


```

---

## 作者：EricWan (赞：0)

笑死，瞪着大眼 5 分钟才看见 $\sum d_i\le5\times10^7$。

本题考虑根号分治，小于 $10000$ 的数最多有 $10000$ 种，大于 $10000$ 的数最多有 $5000$ 个，枚举 $10000$ 以内的数两两之间对答案产生的贡献，$10000$ 以内的数与 $10000$ 以外的数间对答案的贡献（这个贡献需要乘 $2$，这个贡献需要乘 $2$，这个贡献需要乘 $2$，重要的事情说三遍，我因为这个调了 5 分钟），$10000$ 以外的数两两之间对答案产生的贡献，加和即可。

废话不多说，直接看代码：

```cpp
// Problem: T412755 [LMXOI Round 1] Size
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T412755?contestId=152140
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))
#define lowbit(x) ((x)&-(x))
#define abs(x) (((x)<(0))?(-(x)):(x))
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
int quikpower(int a, int b)
{
//	if (b < 0)
//	{
//		return quikpower(a, b + mod - 1);
//	}
	int c = 1;
	while (b)
	{
		if (b & 1)
		{
			c *= a;
//			c %= mod;
		}
		a *= a;
//		a %= mod;
		b >>= 1;
	}
	return c;
}
int countbit(int x)
{
	// cout << x << "\n";
	int ans = 0;
	while (x)
	{
		ans += (x & 1);
		x >>= 1;
	}
	return ans;
}
int n, x, box[10005], ans;
map<int,int> st;
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		if (x <= 10000)
		{
			box[x]++;
		}
		else
		{
			st[x]++;
		}
	}
	for (int i = 1; i <= 1000; i++)
	{
		for (pair<int,int> j : st)
		{
			ans += countbit(i + j.first) * box[i] * j.second + countbit(abs(i - j.first)) * box[i] * j.second;
		}
	}
	ans *= 2;
	for (int i = 0; i <= 10000; i++)
	{
		for (int j = 0; j <= 10000; j++)
		{
			ans += countbit(i + j) * box[i] * box[j] + countbit(abs(i - j)) * box[i] * box[j];
		}
	}
	for (pair<int,int> i : st)
	{
		for (pair<int,int> j : st)
		{
			ans += countbit(i.first + j.first) * i.second * j.second + countbit(abs(i.first - j.first)) * i.second * j.second;
		}
	}
	cout << ans;
	return 0;
}
```

提交之后，你会发现全 T 了，我也不知道为啥，但是将分治边界改为 $1000$ 就跑地飞快，可能数据不随机？

---

## 作者：Gaode_Sean (赞：0)

注意到 $\sum d_i \leq 5 \times 10^7$，可以得出不同的数至多有大约 $\sqrt{5 \times 10^7}$ 个。

于是考虑用 map 求出每个数出现的次数，设值不同的数有 $m$ 个，则可以 $\mathcal{O}(m^2)$ 计算答案。

记得预处理 $1 \sim 7\times 10^7$（上界不确定) 中每个数二进制下 $1$ 的个数，递推即可。

卡常之后惊险 $950$ ms。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,M=7e7+5;
typedef long long ll;
int n;
int d[N],f[M];
ll ans;
map<int,int> mp;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&d[i]),mp[d[i]]++;
	sort(d+1,d+1+n);
	int m=unique(d+1,d+1+n)-d-1;
	for(int i=1;i<M;i++) f[i]=f[i>>1]+(i&1);
	for(int i=1;i<m;i++)
	{
		for(int j=i+1;j<=m;j++) ans+=2ll*mp[d[i]]*1ll*mp[d[j]]*1ll*(f[d[i]+d[j]]+f[max(d[i],d[j])-min(d[i],d[j])]);
	}
	for(int i=1;i<=m;i++) ans+=1ll*mp[d[i]]*1ll*mp[d[i]]*1ll*f[2*d[i]];
	printf("%lld",ans);
	return 0;
}
```

---

