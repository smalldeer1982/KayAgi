# Tweetuzki 爱军训

## 题目描述

Tweetuzki 仍然记得，初一军训的时候，有关他们班的教官的一些事儿。

Tweetuzki 所在的班级有 $n$ 名学生，座号从 $1$ 到 $n$。有一次，教官命令班上的 $n$ 名学生按照座号顺序从左到右排成一排站好军姿，其中 $1$ 号学生在最左边，$n$ 号学生在最右边。

由于同学们站了很久，怨声载道，仁慈的教官又不希望大家一起解散导致混乱的局面，于是想了一个办法：教官从最左边——也就是 $1$ 号学生身旁出发，走到 $n$ 号学生右边后，再折返回到 $1$ 号同学旁边。在教官在从 $1$ 号同学走到 $n$ 号同学这段路上，当走到某位同学身边时，他可以选择让这位同学出列，也可以等到折返的时候再使这名同学出列。

但是有一些同学在军训过程中表现极坏，因此教官希望他们晚一些出列休息。对于 $i$ 号同学，定义他的“坏值”为 $w_i$。教官希望在一次往返过程中，使得所有学生出列，且最大化 $\sum_{i = 1}^n r_i \times w_i$ 的值，其中 $r_i$ 表示 $i$ 号同学是第 $r_i$ 位出列的学生。机智的教官一下子就想出了这个方案，Tweetuzki 大为惊讶，于是他去请教教官如何做到。可是他的胆子很小而且“坏值”很大，教官可能不会告诉他，所以他就找到了你。

## 说明/提示

### 样例解释 1

在去的路上让 $3, 4, 5$ 号同学出列，回来时让 $2, 1$ 号同学出列。总的值为 $5 \times 7 + 4 \times 8 + 1 \times 1 + 2 \times 2 + 3 \times 5 = 87$，可以证明没有使得答案大于 $87$ 的方案。

### 数据范围

本题共设 $20$ 组测试点，每组测试数据 $5$ 分。

对于 $10\%$ 的数据，$n \le 8$。  
对于 $30\%$ 的数据，$n \le 20$。  
对于 $60\%$ 的数据，$n \le 1000$。  
对于 $100\%$ 的数据，$5 \le n \le 10^6$，$0 \le w_i \le 10^6$。  

## 样例 #1

### 输入

```
5
7 8 1 2 5```

### 输出

```
87
1 2 5 8 7```

## 样例 #2

### 输入

```
5
7 99 1 5 2```

### 输出

```
530
7 1 2 5 99```

## 样例 #3

### 输入

```
8
1 9 2 6 0 8 1 7```

### 输出

```
206
1 2 0 1 7 8 6 9```

# 题解

## 作者：Lysus (赞：5)

首先我们可以第一遍全部让学生出列

这样答案就会是$\sum^n_{i=1}w[i]*i$

( sum[ i ]为 1 到 i 的 w[ i ] 的前缀和)

当第i位同学第二批出列时，贡献就会变化 - (sum [ n ] - sum [ i ]) + (n - i) * w [ i ] 

(自己想想为什么)

然后就很简单了

贡献为正，第二批

贡献为负，第一批

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int N = 5000010;

int n, w[N], sum[N], ans, a_1[N], a_2[N];

signed main () {
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++ ) scanf("%lld", &w[i]), sum[i] = sum[i - 1] + w[i], ans += w[i] * i, a_1[i] = 1;
	for(int i = 1; i <= n; i ++ ) {
		if((n - i) * w[i] - (sum[n] - sum[i]) > 0) {
			ans += (n - i) * w[i] - (sum[n] - sum[i]);
			a_1[i] = 0; a_2[i] = 1;
		}
	}
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i ++ ) if(a_1[i]) printf("%lld ", w[i]);
	for(int i = n; i >= 1; i -- ) if(a_2[i]) printf("%lld ", w[i]);
	return 0;
}
```


---

## 作者：子谦。 (赞：4)

很明显，1e6的范围，要么nlgn要么O(n)

nlgn的话可能会想到借助一些数据结构，我并没有想到这种做法

对于这种题，O(n)的做法要么是线性递推，要么就应该是贪心了

考虑这道题我们怎么贪心

如果可以走无数个来回的话，那很明显我们可以从小到大依次取出，一定是最大的

可惜只能走一个来回

那么我们来看看只能走一个来回的话，有什么特性

对于第i个同学，要么是去的时候取出，要么是回来的时候取出，我们来考虑一下这有什么区别

当第i个同学为从去的时候取出变为回来的时候取出，多做的贡献就是排名差乘上他的权值

那么他会对那些同学造成影响呢？由于教官的路线是一个来回，我们不妨破环成链来考虑一下。

我们会发现第i个同学对应着两个位置——$i$和$2n-i+1$，设i为去的时候去的时候取，$2n-i+1$为回来取，那么如果我们将去的时候取换成回来取，会造成$[i+1,2n-i]$之间的点排名整体前移1，也就是说如果第i名同学滞后取出，会造成$-\sum_{k=i+1}^n w[k]$的贡献，这个很明显可以用前缀和或后缀和O(1)算出

那么很明显了，如果i同学滞后选择额外产生的贡献严格大于零（因为要求相同情况序号字典序最小）那么我们就可以最后再选择他。

那么我们就可以直接贪心求方案，用双指针记录目前还没有确认的出列顺序的左右端点

没明白就看代码吧

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#ifdef ONLINE_JUDGE
#define printf(o"\n") printf("I AK IOI\n")
#define printf(o) printf("I AK IOI")
#endif
#define ll long long
#define gc getchar
#define maxn 1000005
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}

int n,l,r;
ll ans,a[maxn],b[maxn],c[maxn];
int main(){
	n=read();l=1,r=n;
	for(int i=1;i<=n;++i){
		a[i]=read();
		b[i]=a[i]+b[i-1];    //前缀和
	}
	for(int i=1;i<=n;++i){
		ll jia=a[i]*(r-l);    //表示滞后取出产生的正贡献
		if(jia>b[n]-b[i]){  //大于负贡献也就是大于零
			c[r]=i;
			ans+=(ll)a[i]*r;
			--r;
		}
		else{    //否则正常取出
			c[l]=i;
			ans+=(ll)a[i]*l;
			++l;
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;++i)
		printf("%lld ",a[c[i]]);    //c数组记录的只是下标，可别直接输出c数组
	return 0;
}
```

抄题解的猜猜我代码能不能AC（滑稽

---

## 作者：一扶苏一 (赞：3)


## Solution

考虑答案的出列编号序列一定是单峰的，即如果把序列下标作为 $x$ 坐标， 出列选手的序号作为 $y$ 坐标，则函数图像一定如下

![qwq](https://cdn.luogu.com.cn/upload/pic/45808.png)

并且 $n$ 一定是峰。于是考虑倒着往前决定出队的顺序，考虑已经决定了 $i+1~\sim~n$的出队顺序，那么 $i$ 只可能放在这条函数图线的最左侧或者最右侧，我们比较他们的贡献。

考虑 $i$ 放在最左侧的情况，这相当于他后面出队所有人的 $r$ 值都加一，于是放在左侧的贡献 $s_l~=~\sum_{j~=i+1}^{n}~w_j~+~w_i$

同理，考虑放在右侧的贡献，即为他前面已经放的人的个数，即 $s_r~=~(n-i)~\times~w_i~+~w_i$

比较 $sl$ 和 $s_r$ 的大小即可。由于序号字典序尽可能小，当两者相等时优先放在左侧即可。

## Code

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define putchar(o)\
puts("I am a cheater!")
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 1000010;

int n;
ll ans, sum;
int MU[maxn], temp[maxn];
std::vector<int>pre,pos;

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) qr(MU[i]);
	for (rg int i = n; i; --i) {
		ll sl = sum + MU[i], sr = 1ll * MU[i] * (n - i) + MU[i];
		if (sl >= sr) {pre.push_back(i); ans += sl;}
		else {pos.push_back(i); ans += sr;}
		sum += MU[i];
	}
	qw(ans, '\n', true);
	int sz = pre.size();
	for (rg int i = sz - 1; ~i; --i) qw(MU[pre[i]], ' ', true);
	sz = pos.size();
	for (rg int i = 0; i < sz; ++i) qw(MU[pos[i]], ' ', true);
	putchar('\n');
}
```



---

## 作者：hwx12233 (赞：2)

首先看到这道题时我们发现：教官是走两遍的

那么选的人的下标的编号一定是先递增后递减的

那么可以看成将一个人安排在前面或后面

相当于已有$1,x,x,x,x,2 $

这样是已排好的那么3号位置的人只可以放在1后或2前才能符合题意

假如这样$1,3,x,x,x,2$

那么4也只能放在3后或2前

那么我们肯定选最优的

将这个人放在已经排好队列的前面的贡献是$a[i]*l+pre[n]-pre[i]$

$l$是现在左边放的位置

$pre$为前缀和 因为放了后面的排名就会+1

将这个人放在后面的贡献是$a[i]*r$

$r$是目前右边放的位置

取两者较大的放

前面以保证最优这一步最优所以这一步最优必定是全局最优

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f
#define INF 1e19
#define int ll
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x>y?y:x;}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int N=1e6+10;
int n,a[N],pre[N],anss,ans[N],l,r;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),pre[i]+=pre[i-1]+a[i];
	l=1,r=n;
	for(int i=1;i<=n;i++){
		int ll=a[i]*l+pre[n]-pre[i],rr=a[i]*r;
		if(ll<=rr)ans[r]=a[i],anss+=a[i]*r,r--;
		else ans[l]=a[i],anss+=a[i]*l,l++;
	}
	cout<<anss<<endl;
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
```


---

## 作者：Space_Gold_Trash (赞：2)

[题目连接](https://www.luogu.com.cn/problem/P5078)

[体验++](https://www.cnblogs.com/the-Blog-of-Mikasa/p/13207290.html)

### 我们首先从确定算法着手

$ n=1e6 $

根据常识,我们可以选择的有$O(nlogn) or O(n)$

同样根据常识$O(nlogn)的玩意儿有二分,线段树等等$

$O(n)$的玩意儿有dp,贪心

$dp$我觉得起码要开二维才行,否则弄不出来的

那么就只剩下贪心和二分线段树之类的

首先二分线段树之类我是实在想不出怎么做

贪心倒是可以做出来

### 思路

~~XBB结束~~

我们让他们第一次过去全部出队

回来的一趟再把他们拉回来再出队（雾

我们想想

比如一组数

1 2 3 4 5 6

把第**i**位拉出来放在最后

是不是只对$i+1->n$的排名有影响?

那么我们就更新...等等!这不就成$O(n^2)$了吗?

我们需要用聪明的方法来玄学优化这一个更新

明显,$i+1->n$排名均$--$

那么我们用结合律搞一下,不就是减去$\sum_{j=i+1}^n a(j)吗$

那么加一个前缀和优化一波

然后我们再用指针乱搞一下排名

就AC啦~

```
#include<bits/stdc++.h> 
#define N 1001001
#define int unsigned long long
using namespace std;
inline int read( ){
	int sum=0,ft=1;
	char ch=getchar( );
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar( );
	if(ch=='-'){
		ch=getchar( );
		ft=-1;
	}
	while(ch>='0'&&ch<='9'){
		sum=ch-'0'+(sum<<3)+(sum<<1);
		ch=getchar( );
	}
	return ft*sum;
}
inline void print(int k){
	if(!k)return;
	print(k/10);
	putchar(k%10+'0');
}
int sum[N],n,a[N],pre[N],nex[N],last,xu[N];
inline void work(int k){
	nex[last]=k;
	pre[nex[k]]=pre[k];
	nex[pre[k]]=nex[k];
	nex[k]=0;
	pre[k]=last;
	last=k;
}
signed main( ){
	n=read( );
	int i,j,ans=0,k;
	for(i=1;i<=n;i++){
		nex[i]=i+1;
		pre[i]=i-1;
		k=read( );
		sum[i]=k;
		a[i]=k;
		ans=ans+k*i;
	}
	last=n;
	nex[n]=0;
	for(i=n-1;i>=1;i--)sum[i]+=sum[i+1];
	for(i=n;i>=1;i--)
	if((n-i)*a[i]>sum[i+1]){
		ans+=(n-i)*a[i]-sum[i+1];
		work(i);
	}
	print(ans);
	putchar('\n');
	int ci=0,t;
	for(i=1;i<=n;i++)
	if(!pre[i]){
		t=i;
		break;
	}
	while(t){
		xu[++ci]=t;
		t=nex[t];
	}
	for(i=1;i<=n;i++){
		if(a[xu[i]])print(a[xu[i]]);
		else putchar('0');
		putchar(' ');
	}
}
```

---

## 作者：SSerxhs (赞：2)

考虑把i从第一次出队改变到第二次出队，则其贡献增加a[i]*(n-i)，其后(n-i)人贡献都减少，第j个人减少a[j]。

由于每次贡献增加都是单点增加，减少都是后缀减少，故统计后缀和s，若a[i]*(n-i)>s[i+1]则i应该第二次出队。

```cpp
// luogu-judger-enable-o2
#include <stdio.h>
#include <string.h>
const int N=1e6+2;
typedef long long ll;
int a[N];
ll s[N],ans;
bool ed[N];
int n,i,c;
inline void read(int &x)
{
    c=getchar();
    while ((c<48)||(c>57)) c=getchar();
    x=c^48;c=getchar();
    while ((c>=48)&&(c<=57))
    {
        x=x*10+(c^48);
        c=getchar();
    }
}
int main()
{
    read(n);
    for (i=1;i<=n;i++) read(a[i]);
    for (i=n;i;i--) s[i]=s[i+1]+a[i];
    for (i=1;i<=n;i++) ans+=(ll)a[i]*i;
    for (i=1;i<=n;i++) if ((ll)a[i]*(n-i)>s[i+1])
    {
        ans+=(ll)a[i]*(n-i)-s[i+1];
        ed[i]=1;
    }
    printf("%lld\n",ans);
    for (i=1;i<=n;i++) if (!ed[i]) printf("%d ",a[i]);
    for (i=n;i;i--) if (ed[i]) printf("%d ",a[i]);
}
```

---

## 作者：Sunrise_beforeglow (赞：1)

挺好的贪心。

为了方便，将 $1$ 到 $n$ 的巡视称作第一次巡视，$n$ 到 $1$ 的巡视称作第二次巡视。

首先我们可以让所有人都在第一次巡视中出列。

这样的答案既为 $\sum\limits_{i=1}^nw_i\cdot i$。

然后我们考虑如果 $i$ 变成第二次巡视中出列的会发生什么事。

第一个就是他会变成最后一个出列的，将答案会加上 $(n-i)w_i$。

第二个就是显然 $1$ 到 $i-1$ 的人顺序没变。而对于 $i+1$ 到 $n$ 的人而言，不管他是第一次巡视中出列还是第二次巡视中出列，**出列顺序一定介于 $i$ 在第一次巡视出列顺序到 $i$ 在第二次巡视出列顺序之间。** 所以会将答案减去 $\sum\limits_{j=i+1}^nw_j$，可以用前缀和优化。

综上，$i$ 变成第二次巡视中出列的会将答案加上 $(n-i)w_i-(sum_n-sum_i)$。（其中 $sum_i=\sum\limits_{j=1}^iw_j$。）

只要看它是不是大于 $0$ 即可。

代码环节（$x_i$ 表示 $i$ 是否在第二遍巡视中出列）：


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[1000005],x[1000005],sum[1000005],ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++)ans+=a[i]*i;
    for(int i=1;i<=n;i++)
    {
        if((n-i)*a[i]-(sum[n]-sum[i])>0)
        {
            ans+=(n-i)*a[i]-(sum[n]-sum[i]);
            x[i]=1;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)if(!x[i])cout<<a[i]<<' ';
    for(int i=n;i>=1;i--)if(x[i])cout<<a[i]<<' ';
    return 0;
}
```

---

## 作者：wyl123ly (赞：1)

## 引言

本文更注重推导过程，无法理解其他题解的可以来这里看看。

[博客食用](https://www.cnblogs.com/wyl123ly/p/18457120)

## 解法

考虑贪心。

用 $ans$ 表示最后的答案，在刚开始时假设全部都按 $1 \to n$ 的顺序出列，则 $ans = \sum^{n}_{i = 1} w_i \times i$。

对第 $k$ 个同学出列的价值变化考虑，有：
$$
ans = \sum^{k - 1}_{i = 1} w_i \times i + \sum^{n}_{k + 1} w_i \times (i - 1) + n \times w_k
$$
我们计算初始的 $ans$ 和变化后的 $ans$ 值的差值：
$$
delta = \sum^{n}_{i = 1} w_i \times i - \left( \sum^{k - 1}_{i = 1} w_i \times i + \sum^{n}_{k + 1} w_i \times (i - 1) + n \times w_k \right)
$$

$$
= \sum^{n}_{i = 1} w_i \times i - \sum^{k - 1}_{i = 1} w_i \times i - \sum^{n}_{k + 1} w_i \times (i - 1) - n \times w_k
$$

$$
= \sum^{n}_{i = k} w_i \times i - \sum^{n}_{i = k + 1} w_i \times i + \sum^{n}_{k + 1} w_i - n \times w_k
$$

$$
= (k - n) \times w_k - \sum^{n}_{k + 1} w_i
$$

我们设 $pre_m = \sum^{m}_{i = 1}w_i$

则：
$$
delta = (k - n) \times w_k - (pre_n - pre_k)
$$
 如果 $delta < 0$，则说明第 $k$ 位上同学在教官反着走的时候出列，比在教官正着走时出列更优，则使得第 $k$ 为上的人出列即可。

那么我们的核心代码就很好写了：

```cpp
for(int k = 1;k <= n;k++){
    if(pre[n] - pre[k] + (k - n) * w[k] < 0){
        ans += -(pre[n] - pre[k] + (k - n) * w[k]);
        id[k] = true;
	}
}
```

## 证明

我们推导的时候会发现，有没有可能选择一个 $k$ 位置上的人，反着走时被选择，会对其他人的选择贪心判断造成影响。

考虑在我们想要选择 $k$ 位置上的人时，前面已经有一个 $s$ 位置上的人被选了。（$k > s$）

则选择这两个后的 $ans$ 会变为：
$$
\sum^{s - 1}_{i = 1}w_i \times i + \sum^{k - 1}_{i = s + 1} w_i \times (i - 1) + \sum^{n}_{i = k + 1}w_i \times (i - 2) + w_s \times n + w_k \times (n - 1)
$$
那么 $delta$ 会变为：
$$
\sum^{n}_{i = 1} w_i \times i - \left(\sum^{s - 1}_{i = 1}w_i \times i + \sum^{k - 1}_{i = s + 1} w_i \times (i - 1) + \sum^{n}_{i = k + 1}w_i \times (i - 2) + w_s \times n + w_k \times (n - 1)\right)
$$

$$
= \sum^{n}_{i = s} w_i \times i - \sum^{k - 1}_{i = s + 1} w_i \times (i - 1) - \sum^{n}_{i = k + 1} w_i \times (i - 2) - w_s \times n - w_k \times(n - 1)
$$

$$
= \sum^{n}_{i = s} w_i \times i - \sum^{k - 1}_{i = s + 1} w_i \times i + \sum^{k - 1}_{i = s + 1}w_i - \sum^{n}_{i = k + 1} w_i \times i + \sum^{n}_{i = k + 1}2w_i - w_s \times n - w_k \times n + w_k
$$

$$
= \left( \sum^{n}_{i = k} w_i \times i + w_s \times s \right) + (pre_{k - 1} - pre_s) - \sum^{n}_{i = k + 1}w_i * i + 2 \times (pre_n - pre_k) - w_s \times n - w_k \times n + w_k
$$

$$
= w_k \times (k - n) + w_s \times (k - n) + (pre_n - pre_k) + (pre_n - pre_s) + w_k - (pre_{k - 1} - pre_k)
$$

$$
= \{ (k - n) \times w_k - (pre_n - pre_k) \} + \{ (s - n) \times w_s - (pre_n - pre_s) \}
$$

那么我们发现，最后的式子可以拆成 $s$ 单独选择和 $k$ 单独选择后加起来。

同理可得，无论多少个数选择都不会对彼此造成影响，也就是说这些选择彼此是独立的。

那么贪心即可，代码超短：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
const int MAXN = 1e6 + 7;
int n;
int w[MAXN];
bool id[MAXN];
int pre[MAXN];
int ans;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> w[i],pre[i] = pre[i - 1] + w[i];
    for(int i = 1;i <= n;i++) pre[i] = pre[i - 1] + w[i],ans += w[i] * i;
    for(int k = 1;k <= n;k++){
        if(pre[n] - pre[k] + (k - n) * w[k] < 0){
            ans += -(pre[n] - pre[k] + (k - n) * w[k]);
            id[k] = true;
        }
    }
    cout << ans << endl;
    for(int i = 1;i <= n;i++) if(!id[i]) cout << w[i] << " ";
    for(int i = n;i >= 1;i--) if(id[i]) cout << w[i] << " "; 
    return 0;
}
```

done.

---

## 作者：irris (赞：1)

## Preface

> 贪心 / 最优化 / 普及组。

为啥所有题解全在讲不直观的同一种做法？？？

为啥这题是蓝？？？

## Solution

考察第 $1$ 个人，在折返过程中，**他要么第 $1$ 个出列，要么第 $n$ 个出列**，所以假如我们确定了后 $n - 1$ 个人的最优答案是 $ans$，那么新的最优答案就是 $ans' = ans + \max(\displaystyle\sum_{i=1}^n w_i, w_1\times n)$，分别表示第 $1$ 在第 $n$ 个位置出列产生的贡献。

注意到假如无视第 $1$ 个人，第 $2$ 个也要么在最前面出列，要么在最后面出列，于是从 $n$ 到 $1$ 倒推上述过程，动态记录一个后缀和即可。

时空复杂度 $\mathcal O(n)$。

## Code

仅保留核心部分。

```cpp
int main() {
	int N = read<int>();
	for (int i = 1; i <= N; ++i) w[i] = read<int>();
	long long sum = 0, ans = 0;
	std::deque<int> Q;
	for (int i = N; i; --i) {
		if (1ll * w[i] * (N - i) > sum) {
			ans += 1ll * w[i] * (N - i + 1);
			Q.push_back(w[i]);
		} else ans += w[i] + sum, Q.push_front(w[i]);
		sum += w[i];
	}
	print<long long>(ans, '\n');
	for (int u : Q) print<int>(u, ' ');
	return 0;
}
```

---

## 作者：Liveddd (赞：1)

考虑贪心。我们依次考虑，将每个点放在左端或者右端。

而是对于每个点，我们考虑拆贡献。设放在前面的点 $[1,l]$ 的和为 $sum1$，放在后面的点 $[r,n]$ 的和为 $sum2$，所有点和为 $sum$，那么：

1.放在前面的点，对其后面的点贡献为 $sum-sum1$。

2.放在后面的点，对其后面的点贡献为 $sum2$。而他前面还有 $r-l+1$ 个点未计算贡献，而这部分贡献为 $a_i\times (r-l+1)$。

注意，我们直接统计贡献是会有重复的。但是这样贪心的话，我们能保证对于之后的决策都会是更优的。真正的的贡献直接统计就好了。

下面代码与上述变量的定义略有不同。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const int N=1e6+10;
template<class T>
inline void read(T &x)
{
    x=0;bool f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=-x;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x),read(x1...);
}

int n;
int a[N];
int l,r,ans[N];
ll sum1,sum2;
int main()
{
    read(n);
    for(int i=1;i<=n;i++)
        read(a[i]),sum1+=a[i];
    l=1,r=n;
    ll res=0;
    for(int i=1;i<=n;i++)
    {
        if(sum1>=1ll*a[i]*(r-l+1)+sum2)
            res+=1ll*a[i]*l,ans[l++]=a[i],sum1-=a[i];
        else res+=1ll*a[i]*r,ans[r--]=a[i],sum2+=a[i];
    }
    printf("%lld\n",res);
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：lcjqwq (赞：1)

唯一一道在比赛的时候没有 A 的题目.. 
### Solution

先求出如果第一次遍历直接让所有人出队的价值 $\sum\limits_{i=1}^{n} i \times w_i$

现在如果让一个人在折返的时候出队，那么它对答案产生的影响 $delta = w_i * (n-i) - \sum \limits_{j=i + 1}^{n}w_i$ 

就是 $i$ 之后的所有人往前移了一位，$i$ 跳到后面去了。

此时可以发现，每个点对答案的贡献是独立的。因为不可能出现 $i < j$ ，$i$ 跳过去后 ，$j > i$ （因为教练的路程是一个折返），所以对于 $i$ 来说，其他的点跳不跳过去都没有关系，他对答案产生的贡献都是上面的哪个式子。

所以就可以贪心的选取所有 $>0$ 的 $delta$ 累加。

输出方案就记录一下这个点有没有跳过去过就行了

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1001000;
int n; bool flag[N]; ll w[N], ans, sum[N]; 
int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%lld", &w[i]), ans += w[i] * i; 
  for(int i = n; i >= 1; i--) sum[i] = sum[i + 1] + w[i]; 
  for(int i = 1; i <= n; i++) {
    ll delta = w[i] * (n - i) - sum[i + 1];
    if(delta > 0) ans += delta, flag[i] = 1;  
  }
  printf("%lld\n", ans);
  for(int i = 1; i <= n; i++)
    if(!flag[i]) printf("%lld ", w[i]);
  for(int i = n; i >= 1; i--) 
    if(flag[i]) printf("%lld ", w[i]); 
  return 0; 
}
```


---

## 作者：LG_kemeng (赞：0)

显然，每个数取出的前后顺序所造成的贡献独立。因为它只会影响到它后面的数，且影响固定为 $-suf_{i+1} + w_i \times (n-i-1)$，其中 $suf$ 为后缀和。判断贡献正负即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T> inline void read(T &x){x=0;register int f=1;register char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}x*=f;}
template<typename T,typename ...Args> inline void read(T &x,Args &... y){read(x);read(y...);}
template<typename T> inline void print(T x){if(x>=10)print(x/10);putchar(x%10+'0');}
template<typename T,typename ... Args> inline void print(T &x,Args &... y){print(x);putchar(10);print(y...);putchar(10);}
int w[1000010],lst[2000010],ans,suf[1000010];
signed main(void)
{
	register int n;read(n);
	for(register int i=0;i^n;i=-~i) read(w[i]),ans+=w[i]*(-~i);
	for(register int i=n-1;i>=0;--i) suf[i]=suf[-~i]+w[i];
	for(register int i=0;i^n;i=-~i)ans=(-suf[-~i]+w[i]*(n-i-1)>0)?ans-suf[-~i]+w[i]*(n-i-1)+0*(int)(lst[(n<<1)-i]=-~i):ans+0*(int)(lst[-~i]=-~i);
	print(ans);putchar('\n');for(register int i=1;i^(-~(n<<1));i=-~i) lst[i]&&printf("%lld ",w[lst[i]-1]);
	return 0;
}
```

---

