# Pinkie Pie Eats Patty-cakes

## 题目描述

Pinkie Pie has bought a bag of patty-cakes with different fillings! But it appeared that not all patty-cakes differ from one another with filling. In other words, the bag contains some patty-cakes with the same filling.

Pinkie Pie eats the patty-cakes one-by-one. She likes having fun so she decided not to simply eat the patty-cakes but to try not to eat the patty-cakes with the same filling way too often. To achieve this she wants the minimum distance between the eaten with the same filling to be the largest possible. Herein Pinkie Pie called the distance between two patty-cakes the number of eaten patty-cakes strictly between them.

Pinkie Pie can eat the patty-cakes in any order. She is impatient about eating all the patty-cakes up so she asks you to help her to count the greatest minimum distance between the eaten patty-cakes with the same filling amongst all possible orders of eating!

Pinkie Pie is going to buy more bags of patty-cakes so she asks you to solve this problem for several bags!

## 说明/提示

For the first bag Pinkie Pie can eat the patty-cakes in the following order (by fillings): $ 1 $ , $ 6 $ , $ 4 $ , $ 7 $ , $ 1 $ , $ 6 $ , $ 4 $ (in this way, the minimum distance is equal to $ 3 $ ).

For the second bag Pinkie Pie can eat the patty-cakes in the following order (by fillings): $ 1 $ , $ 4 $ , $ 6 $ , $ 7 $ , $ 4 $ , $ 1 $ , $ 6 $ , $ 4 $ (in this way, the minimum distance is equal to $ 2 $ ).

## 样例 #1

### 输入

```
4
7
1 7 1 6 4 4 6
8
1 1 4 6 4 6 4 7
3
3 3 3
6
2 5 2 3 1 4```

### 输出

```
3
2
0
4```

# 题解

## 作者：奇米 (赞：10)

# 题解 - $\mathrm{CF1393C}$

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF1393C)

## $\mathrm{Sol}$

一道贪心结论题

我们贪心构造把出现次数多的先填把整个序列个塞满，举个例子就是假设 $a$ 为序列中出现次数最多的数那么变化的序列应该长成 $a(...)a(...)a$ 的样子（我们不需要关心其他数在 $(...)$ 中是怎么填的）。

那么对于有多个出现次数最多的数，我们考虑把这些数合并成一块。举个例子假设 $a,b$ 为出现次数最多的数，那么原序列会变为: $[a,b] (..) [a,b] (..) [a,b]$。

所以假设有 $S$ 个数出现了 $MX$ 次，那么答案即为：$\frac{(n-MX\times S)}{MX-1}+(S-1)$。除 $(MX-1)$ 是由于有这么多个间隔放别的数，加了 $S-1$ 即出现次数最多拼成联通块的长度。

时间复杂度 $O(\sum n)$

## $\mathrm{Code}$

```
int main()
{
	io.read(Q);
	for (;Q--;)
	{
		io.read(n);
		int MX=0,S=0;
		For(i,1,n) 
		{
			io.read(a[i]);
			MX=max(MX,++b[a[i]]);
		}
		For(i,1,n) 
		{
			S+=(b[i]==MX);
			b[i]=0;
		}
		io.write((n-MX*S)/(MX-1)+S-1);
		puts("");
	}
}
```




---

## 作者：huayucaiji (赞：7)

此题的数学方法不再赘述，我们来关注一下冷门的二分答案（至少我没看到几个二分答案做的）。

确定做法二分答案，我们的重点就放在了 ```check``` 函数上。首先先讲讲我在考试的时候怎么想的（**这个是错误想法**）。

我们确定了一个答案 $x$，判断是否可行，我们一个一个放数字，从出现次数最多的开始放，每隔 $x$ 个位置就放一个，如果已经到头了，却还有剩余，就代表答案不存在，返回 $0$。**但这是错的**。我们举个例子，比如对于：

```plain
10
4 4 4 4 3 3 2 2 1 1
```

按照我们的做法，若 $x=2$，放完了 $4,3,2$ 后，是这样的一个序列：$4\ 3\ 2\ 4\ 3\ 2\ 4\ 0\ 0\ 4$。其中 $0$ 代表还未放置的数。明显，我们会认为它是不可行的。其实我们可以实现，比如这个序列：$4\ 3\ 2\ 4\ 1\ 2\ 4\ 1\ 3\ 4$。这个```check```直接暴毙。

我们来换一个贪心的思路。我们考虑到第 $i$ 个位置，若在 $[i-x-1,i]$ 内 $k$ 这个数还没有出现过，那么 $k$ 就成为了 $i$ 这个位置上的候选人。假设我们有 $d$ 个候选人 $k_1,k_2...k_d$。我们就肯定先选择剩下还需在序列中出现次数最多的那个数，填在 $i$ 这个位置上。因为填在这一位上，肯定比在 $i+q$ 的位置上优。如果在考虑某个位置时，没有可以选择的数，即 $d=0$ 时，肯定是无解的，返回 $0$。在计算时用一个堆维护即可。时间复杂度为 $O(n\log^2 n)$。可以卡过此题。

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,a[maxn],cnt[maxn];
int b[maxn];

bool check(int x) {
	fill(b+1,b+n+1,0);
	priority_queue<pair<int,int> > q;
	
	for(int i=1;i<=n;i++) {
		if(cnt[i])
			q.push(make_pair(cnt[i],i));
	}
	
	for(int i=1;i<=n;i++) {
		if(i>x+1) {
			if(cnt[b[i-x-1]])
				q.push(make_pair(cnt[b[i-x-1]],b[i-x-1]));//把重新“合法”的这个数加回堆中。
		}
		if(q.empty()) {
			return 0;//此时无解
		}
		
		pair<int,int> pr=q.top();
		q.pop();
		cnt[pr.second]--;//剩余出现次数减1
		b[i]=pr.second;
	}
	return 1;
}

void clear() {
	fill(cnt+1,cnt+n+1,0);
	for(int i=1;i<=n;i++) {
		cnt[a[i]]++;
	}
}

signed main() {
	int t=read();
	
	while(t--) {
		n=read();
		
		for(int i=1;i<=n;i++) {
			a[i]=read();
			cnt[a[i]]++;
		}
		
		int l=0,r=n-2;
		
		while(l+1<r) {
			int mid=(l+r)>>1;
			clear();//恢复cnt数组
			
			if(check(mid)) {
				l=mid;
			}
			else {
				r=mid;
			}
		}
		clear();//恢复cnt数组
		if(check(r)) {
			printf("%d\n",r);
		}
		else {
			printf("%d\n",l);
		}
		fill(cnt+1,cnt+n+1,0);
	}
	return 0;
}

```

---

## 作者：RyexAwl (赞：5)

考虑二分答案然后贪心 check。一种错误的贪心是按权值出现次数从大到小考虑往序列中放，每次第一个数放在最靠前的未被放置的位置。

在 @huayucaiji 的题解中提出了一组 hack 数据：

$$
[4,4,4,4,3,3,2,2,1,1]
$$

在 check 是否能够让任意两个相同的权值之间相隔的数的个数均 $\ge 2$，放完 $4,3,2$ 后：

$$
[4,3,2,4,3,2,4,0,0,4]
$$

我们找不到一种合法的放置方案，但是实际上是可以找到的：

$$
[4,3,2,4,1,2,4,1,3,4]
$$

这里给出该贪心算法为什么是假的一个理（感）性分析。我们这个贪心算法的放置是按权值顺序考虑依次考虑每种权值放置的位置，我们考虑一次操作对后续操作的影响，如果放完前 $k$ 个权值后长度为 $l$ 的后缀均被“占用”了，如果我们 check 的间距为 $len$，那么 $[l-len,l-1]$ 范围内的未被占用的位置只能放某种权值的最后一个数（因为如果放的不是最后一个数，后面还需要放，是找不到可以放的位置的）。

如果 check 的间距 $len>0$，那么任意时刻一定存在一段后缀内的空格子是不能放的，如果我们把这个空格子留到之后的状态，那么就可能会寄，同样是上面那个例子，在填完 $4,2$ 后考虑填 $3$，其中红色的空位置只能填某种权值最后一次出现的数：

$$
[4,0,2,4,0,2,4,\textcolor{red}{0},\textcolor{red}{0},4]
$$

如果我们把 $3$ 填到前两个 $0$ 中，那么留给 $1$ 的就只有两个标号的空位了，但是如果其中一个 $3$ 占用最后一个红色的 $0$，留给 $1$ 的情况就是合法的。

考虑换种角度思考，从序列的维度思考从左往右依次考虑序列中每个位置填几，如果当前考虑到第 $i$ 位，check 的间距为 $len$，那么只有在 $[i-len,i-1]$ 中未出现过的权值可以填在第 $i$ 位，感性理解我们一定是填当前（即还未填入序列中的）出现次数最大的权值。如果不存在能填的则无解。

具体实现时考虑使用 set 维护所有能填的数的出现次数即可，复杂度 $O(n\log ^2 n)$。

下面将使用调整法证明下面的结论的正确性：

**如果存在一组合法的放置方案，那么上述贪心算法一定能找到一种合法的方案。**

证明思路为对于任意一种方案，我们都可以在有限步内调整成贪心算法找到的合法方案，且每一步调整后方案仍然合法。

考虑贪心算法找到的方案和当前考虑方案的第一个不同点，即在考虑第 $i$ 位时贪心算法选择了填权值 $x$，当前方案填了权值 $v$，且在后续的序列中 $x$ 的出现次数不小于 $v$ 的出现次数（即在两种方案中，$\ge i$ 位置上 $x$ 的出现次数不小于 $v$ 的出现次数，因为前面都一样所以在 $\ge i$ 的位置上 $x$ 两种方案每种权值出现的次数均相同）。

如果 $x$ 出现了 $p$ 次，$v$ 出现了 $q$ 次，$p\ge q$，且出现位置分别为 $x_1,x_2,...,x_p$，$v_1,v_2,...,v_q$。

如果 $x_q>v_q$，那么直接将 $x_1,x_2,...,x_p$ 和 $v_1,v_2,...,v_q$ 整段交换（即 $x_i$ 和 $v_i$ 交换）。

如果 $x_q<v_q$，那么至少存在一个前缀 $k$ 满足其中 $x$ 的个数比 $v$ 的个数大，考虑段 $(v_1,v_2),(v_2,v_3),...,(v_{q-1},v_q)$，每次扩增一个段考虑，考虑最小的 $i$ 满足 $v_1\sim v_{i+1}-1$ 之间 $x$ 的个数大于 $i$，那么在段 $(v_i,v_{i+1})$ 中一定有至少两个 $x$（因为之前段 $x$ 出现次数 $\le v$，$v$ 新增一个 $x$ 至少新增 $2$ 个），考虑取前 $i$ 个 $x$ 和前 $i$ 个 $v$ 交换，交换后也一定是合法的。

并且显然这个过程可以在 $O(n)$ 步内结束。

---

## 作者：45dinо (赞：3)

一个恶心~~恶臭~~的数学题

发现最小值肯定属于那些出现次数最多的，统计出 q 个，最大值为 m 次。

答案明显为 $\frac {n-q\times w} {m-1}+q-1$ 。

为什么这么明显呢？$n-q\times w$ 就是剩下多少数，把这些数平分成 m-1 份，就是 $\frac {n-q\times w} {m-1}$。

要求的是两个一样的口味的间隔，所以就要再加 q-1。

---

## 作者：ENJOY_AK (赞：0)

## 思路：
  先循环找出出现次数最多的数字的次数 $maxx$ 以及有多少个出现次数最多的数字 $s$。我们找到这两个东西之后，先算出除了这些出现次数最多的数之外的数字，也就是 $n-maxx \times s$，然后再除以出现次数最多数中间的间隔，也就是 $maxx-1$，然后加上每个数之间会间隔的 $s-1$ 个数，$-1$ 是因为填的时候两个相同数中间的会多判一个，所以最后要减去即为答案。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t,n,x,maxx,s; 
int main(){
	cin>>t;
	while(t--){
		map<ll,ll>a;
		maxx=-INF,s=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			a[x]++;
			if(a[x]>maxx)maxx=a[x],s=1;
			else if(a[x]==maxx)s++;
		} 
		cout<<(n-maxx*s)/(maxx-1)+s-1<<endl;
	}
}

```

---

## 作者：ka_da_Duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1393C)

歪解：

看到题目中的**最小的最大**，很容易想到二分，并且发现其满足单调性。时间复杂度 $O(n\log n)$，可以通过。

正解：

数学题，我们想到循环着摆放相同的数字是最优的。将所有出现次数最多的数字合在一起，作为循环节，然后在每两个循环节之间插入出现次数非最多的数字，其实就是插空。

假设出现次数最多的数字有 $k$ 个，出现了 $cnt$ 次，那么答案就是 $\lfloor\dfrac{n - cnt\times k}{k - 1}\rfloor+cnt+1$。时间复杂度 $O(n)$，也是可以通过的。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e6 + 10;

int n, mx, cnt;
int c[maxn];

void solve() 
{
	cin >> n;
	for (int i = 0; i <= n; ++i) c[i] = mx = cnt = 0;;
	for (int i = 1, x; i <= n; ++i) cin >> x, c[x]++, mx = max(mx, c[x]);
	for (int i = 1; i <= n; ++i) cnt += (c[i] == mx);
	cout << cnt - 1 + (n - cnt * mx) / (mx - 1) << '\n';
}

signed main() 
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}
```

---

## 作者：Erotate (赞：0)

考虑二分。

显然对于只出现过一次的数不用理它。记出现次数大于 $1$ 的数 $i$ 的出现次数为 $t_i$，那么显然我们是可以预处理出来的。那么怎么看对于一个 $t$ 它是否符合要求呢，只需要满足：

$$(t_i - 1) \times (x + 1) + s < n$$

上面 $x$ 表示二分的值，$s$ 表示从哪个位置开始放，也就是只需要每隔 $x$ 个位置放一个数，看看是否都能在 $n$ 个位置之内放下就行了。

考虑一组数据：

```
5
1 2 2 1 2
```
如果在处理出 $t$ 之后直接按上面检查是否满足要求，就会发现 $x = 1$ 时程序判断是不满足要求的，但显然手推可以发现 $x = 1$ 是可以的。因此我们发现需要对 $t$ 进行从大到小排序，然后再进行检查。所以检查的式子最终变成了

$$(t_i - 1) \times (x + 1) + i < n$$

注意因为排过序了，所以原来的 $s$ 可以直接用 $i$ 来代替。


```cpp
int T, n, a[N], cnt[N], tot, t[N];
bool check(int x){
    for(int i = 1; i <= tot; ++i)
        if((t[i] - 1) * (x + 1) + i > n) return 0;
    return 1;
}
void solve(){
    tot = 0;
    n = read();
    for(int i = 1; i <= n; ++i) cnt[a[i] = read()]++;
    for(int i = 1; i <= n; ++i)
        if(cnt[i] > 1) t[++tot] = cnt[i];
    sort(t + 1, t + tot + 1, greater<int>()); 
    int l = 0, r = n, ans = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid)){
            l = mid + 1;
            ans = mid;
        }else r = mid - 1;
    }
    Write(ans);
    for(int i = 1; i <= n; ++i) cnt[i] = 0;
} 
```

---

## 作者：_anll_ (赞：0)

真的能有绿吗？
## 大体思路
我们令出现次数最多的数为 $x$。不难想到一种构造：$x\dots x\dots x$。正确性显然：若还有数 $a$ 出现次数等于 $x$，可以将 $a$ 跟在 $x$ 的后面，像 $x \ a\dots x\ a\dots x\ a$。若还有数 $b$ 出现次数小于 $x$，可以将其随机填进两个 $x$ 之间的间隔处。

于是问题转换为如何确定每个 $x$ 之间会间隔多少个数。令有 $s$ 个出现次数与 $x$ 相同的数，次数均为 $an$，那么这 $s$ 个数一定都是捆绑出现在一起，因此可以需要拼接处理的只有 $n-s\times an$。那么最大间隔就呼之欲出了，令刚刚算得的东西为 $awa$，则答案为 $\dfrac{awa}{an-1}+s-1$。

## 代码
部分变量名有差异。
```cpp
#include<iostream>
#include<map>
#define int long long
using namespace std;
int t,n;
map<int,int> mo;
void solve(){
	cin>>n;mo.clear();int an=0,s=0,x;
	for(int i=1;i<=n;i++){
		cin>>x;mo[x]++;
		if(an<mo[x]) an=mo[x],s=1;
		else if(an==mo[x]) s++;
	}
	int awa=n-an*s;
	cout<<awa/(an-1)+s-1<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：KSToki (赞：0)

最小值最大，我一下子想到了二分。主要思想是先用出现次数最多的把位置隔开，隔开后就可以保证距离。而此时最后的那一段是最特殊的，我们需要统计出现次数最多的数有几个，看最后剩的那些位置能不能放得下即可。

顺便说一下，比赛时我忘了特判，system test爆了啊啊啊。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,o,ract;
int rcnt[100001],cnt[100001],len;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
inline bool cmp(int x1,int x2)
{
	return x1>x2;
}
bool check(int k)
{
	int rest=n-(cnt[1]-1)*(k+1);
	if(rest<ract)
	    return 0;
	else
	    return 1;
}
int main()
{
	t=read();
	while(t--)
	{
		memset(rcnt,0,sizeof(rcnt));
		len=0;
		n=read();
		for(register int i=1;i<=n;++i)
		{
			o=read();
			++rcnt[o];
		}
		for(register int i=1;i<=n;++i)
			if(rcnt[i]!=0)
				cnt[++len]=rcnt[i];
		if(len==1)//注意特判，不然ract会减成0
		{
			printf("0\n");
			continue;
		}
		sort(cnt+1,cnt+len+1,cmp);
		for(ract=1;ract<=len;++ract)
			if(cnt[ract]!=cnt[1])
			    break;
		--ract;
		int l=0,r=n-2,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid))
			{
				ans=mid;
				l=mid+1;
			}
			else
			    r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Celtic (赞：0)

题意：给出$n$个数$a_i$，让相同的数之间隔的数尽量多，求相同的数之间隔的数的最小值最大时的值。

拿到这道题首先想到二分。

然而虽然标签里有，不过这题有更优的线性做法。

我们计算出这些数中出现次数最多的数出现的次数和出现次数最多的数的不同的数的个数（即代码中的$maxn$和$cnt$）。

将$n$减去$maxn\times cnt$，此时的$n$就是除了出现次数最多的数的数的个数。

对于出现次数最多的数，它们中间会有$maxn-1$个空。

每个空最少放的剩下的数的个数为$\lfloor \frac{n}{maxn-1} \rfloor$。

这里剩下的数由于出现次数较少，一定能均分到这$maxn-1$个空中。

然后再加上每个数之间会间隔的$cnt-1$个数，即为答案。

细节见代码

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 2001
#define re register
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=1e18; 
inline void read(re ll &ret)
{
    ret=0;re char c=getchar();re bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,t,a[N],maxn,num[N],cnt;
signed main()
{
	read(t);
	while(t--)
	{
		maxn=-inf;
		cnt=0;
		read(n);
		for(re int i=0;i<=100000;i++)
			num[i]=0;
		for(re int i=1;i<=n;i++)
		{
			read(a[i]);
			num[a[i]]++;
			if(num[a[i]]>maxn)
			{
				maxn=num[a[i]];
				cnt=1;
			}
			else if(num[a[i]]==maxn)
				cnt++;
		}
		n-=cnt*maxn;
		printf("%lld\n",cnt-1+n/(maxn-1));
	}
	
	exit(0);
}
```


---

