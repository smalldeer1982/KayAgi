# プログラミングコンテストチャレンジブック

## 题目描述

你有 $N$ 个木棒，第 $i$ 个木棒的长度为 $a_{i}$ 。从这 $N$ 根木棒中选取6根，组成两个三角形(要求每个三角形中是三根木棒**顺次首尾相连**)，你需要求出能组成的两个三角形的周长和的最大值。

## 说明/提示

- 对于 $20\%$ 的数据， $1 \le N \le 10$ 

- 对于 $100\%$ 的数据， $1 \le N \le 10^{5}$ ， $1 \le a_{i} \le 10^{15}$ 

感谢@常暗踏阴 提供的翻译

# 题解

## 作者：Rachel_in (赞：16)


看到此题没有题解，那我就来写一下。

这是一道贪心题，我们把每根木棍按长度由小到大排序。

我们先确定两个三角形的最大边是什么，倘若排序后$a[i] \ge a[i-1]+a[i-2]$,那么$a[i]$是不可能变成最大边的。我们把可以作为最大边的边的标号从小到大依次选出，成为$b$数组{$b_1,b_2,b_3........b_m$}（注意$b$数组记录的是该边在$a$数组的下标）。

### 有一个贪心的结论就是:其中选$b_m$这个标号的边为最大边是最优的。

先不管证明，来说一下得知这个结论后该怎么处理这个问题：

我们选两个最大边的标号，分别为:$b[m]$ , $ b[i]$.

当$b[m]-b[i] \ge 3$时：他们没有冲突，更新答案为：

$$a[b[m]]+a[b[m]-1]+a[b[m]-2]+a[b[i]]+a[b[i]-1]+a[b[i]-2]$$

当$b[m]-b[i] \lt 3$时：他们有冲突，也就是我们只需特判一下末六位能否满足，若满足，更新答案为：
$$a[b[m]]+a[b[m]-1]+a[b[m]-2]+a[b[m]-3]+a[b[m]-4]+a[b[m]-5]$$

### 证明:

1. 对于一组$b[i],b[j](i \lt j)$，他们没有冲突（也就是差大于等于3），此时取$b[i],b[m]$肯定最优，因为$b[i],b[m]$肯定也不冲突

2. 对于一组$b[i],b[j](i \lt j)$,他们有冲突，但$b[j],b[m]$没有冲突，那么取$b[j],b[m]$肯定最优

3. 对于一组$b[i],b[j](i \lt j)$,他们有冲突，但$b[i],b[m]$没有冲突，那么取$b[i],b[m]$肯定最优

4. 对于一组$b[i],b[j](i \lt j)$,他们有冲突，且它们两个与$b[m]$都有冲突，那么取$b[i],b[m]$或$b[j],b[m]$对答案都没有影响。

得证。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int a[N],n,ans,b[N],m;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=3;i<=n;i++)	
		if(a[i]<a[i-1]+a[i-2]) b[++m]=i;//找出可成为最大边的木棍 
	int ans=0,maxx=0;
	for(int i=1;i<=m;i++)	
		if(b[m]-b[i]>=3) maxx=i;//记录不与b[m]冲突的最大木棍标号 
	if(maxx!=0)
		ans=a[b[m]]+a[b[m]-1]+a[b[m]-2]+a[b[maxx]]+a[b[maxx]-1]+a[b[maxx]-2];//双方没有冲突，记录答案 
	if(b[m]>=6){//判断有冲突的情况 
		int t1=a[b[m]-5],t2=a[b[m]-4],t3=a[b[m]-3],t4=a[b[m]-2],t5=a[b[m]-1],t6=a[b[m]];
		int tt=t1+t2+t3+t4+t5+t6;
		if(t1+t2>t3&&t4+t5>t6) ans=tt;//以下为满足条件的情况 
		if(t1+t2>t4&&t3+t5>t6) ans=tt;
		if(t1+t2>t5&&t3+t4>t6) ans=tt;
		if(t1+t2>t6&&t3+t4>t5) ans=tt;
		if(t1+t3>t4&&t2+t5>t6) ans=tt;
		if(t1+t3>t5&&t2+t4>t6) ans=tt;
		if(t1+t3>t6&&t2+t4>t5) ans=tt;
		if(t1+t4>t5&&t2+t3>t6) ans=tt;
		if(t1+t4>t6&&t2+t3>t5) ans=tt;
		if(t1+t5>t6&&t2+t3>t4) ans=tt;
	}
	printf("%lld\n",ans);
	return 0;
}
```
### UPD:修改部分$LaTeX$

---

## 作者：Sankano (赞：6)

## 序言
感觉题解里的那个大佬讲的对于初学者来说有点难理解，所以我也来写一下帮助大家理解。

如果用常规做法做一定会超时（双重循环），而且题目中很明确，$N$ 的范围在一万以内，如果用原来的做法，就可能突破一亿次操作，所以时间复杂度，不通过，选择的一定是贪心（看破题目的套路）。

而还有一个注意点，就是输入的每个数 $a <= 10^{15}$ ，如果是这样，输入一个数就足以爆 int，所以类型上来说，选择 long long。
# 正文
做这道题需要了解三角形知识。

公理：任意两边之和大于第三边，转换了就是两个较短边之和大于长边。
$$a+b>c,c<a+b$$
则等价于代码中的：
$$a[i]<a[i-1]+a[i-2]$$

这就是我们判断一个三角形是否合格的最简依据。两个三角形同理，只是要考虑冲突问题。

而要使他们的周长和最大，首先对他给的长度进行排序，然后利用公理对输入的长度进行判断筛选，最后利用等会儿要推导出的贪心策略解决问题，就可以了。

定义一个 $a$ 数组来记录长度（long long）， $f$ 数组来找最优解下标。先进行排序。

然后从第二个数开始开始，利用公理找最优解。用 $tr1$ 记录 $f[p]$ 的值。
细节问题就不说了。
```c
for(int i=2;i<n;i++)
	if(a[i]<a[i-1]+a[i-2]) f[++p]=i;
tr1=f[p];
```
------------
## 记录 f[p] 的值的原因

其实是这样的， $f[p]$ 是我们最后找到的符合公理（比前两个数之和小）的值，并且是值最大的最优解，利用这一点可以确定第一个三角形的周长最大值。

用前面大佬的方案也可以证明。

第一个三角形最大值求解可以这样：
$$Triangle_1=a_{tr1}+a_{tr1-1}+a_{tr1-2}$$
```c
//代码中的实现
ans=a[tr1]+a[tr1-1]+a[tr1-2] //本身加上前两个的值
```
------------
然后就是查找第二个三角形的下标。

在与 $tr1$ 不冲突的情况下查找 $tr2$ 的最大值。
```c
for(int i=0;i<p;i++)
   if(tr1-f[i]>=3) //如果他们公用边了，则视为冲突
      tr2=f[i];
```
------------
## 判断语句是 $tr1-f[i]>=3$ 的原因

因为我 $f[i]$ 里存的是 $a$ 数组中的最优解的下标，而如果我 $tr1$ 中的下标和传上来的下标的差大于 $3$ ，那么一定产生了冲突。

**Example**

假设 $a$ 数组中有： 1 2 3 4 5 6 7 8 9。

根据我上面的推理 $tr1$ 中下标的值一定是 $8$ （从 $0$ 数起），而查找中如果出现 $tr2= 7$ ，那么他们就是这样：
```c 
三角形1：7 8 9  三角形2：6 7 8
```
很明显重复了。但是一旦我加了判断，就会是这样：
```c
三角形1：7 8 9  三角形2：4 5 6
```
------------
解决了以上的主要问题，然后就是收尾工作了，两个特判。

如果发现找到了 $tr2$ 并且与 $tr1$ 不冲突，那么程序结束了，一个公式解决。
$$ans=a[tr1]+a[tr1-1]+a[tr1-2]+a[tr2]+a[tr2-1]+a[tr2-2]$$
```c
if(tr2!=-1) //我设定tr2初始值为-1，一旦还是-1，说明没找到
	ans=a[tr1]+a[tr1-1]+a[tr1-2]+a[tr2]+a[tr2-1]+a[tr2-2];
```
如果没找到，还有一种情况，就是如果 $tr1$ 往前还有 $6$ 个数，继续垂死挣扎一下。
```c
long long t1=a[tr1-5],t2=a[tr1-4],t3=a[tr1-3],t4=a[tr1-2],t5=a[tr1-1],t6=a[tr1];
long long tmp=t1+t2+t3+t4+t5+t6;
if(t1+t2>t3&&t4+t5>t6) ans=tmp;
else if(t1+t2>t4&&t3+t5>t6) ans=tmp;
else if(t1+t2>t5&&t3+t4>t6) ans=tmp;
else if(t1+t2>t6&&t3+t4>t5) ans=tmp;
else if(t1+t3>t4&&t2+t5>t6) ans=tmp;
else if(t1+t3>t5&&t2+t4>t6) ans=tmp;
else if(t1+t3>t6&&t2+t4>t5) ans=tmp;
else if(t1+t4>t5&&t2+t3>t6) ans=tmp;
else if(t1+t4>t6&&t2+t3>t5) ans=tmp;
else if(t1+t5>t6&&t2+t3>t4) ans=tmp;
```
这段特判的意义就是，只要你这六个数当中有一种组合还符合三角形定理，仍然是最优解。

如果 $tr1<5$ 的话，就直接~~好自为之~~输出 $0$ 吧。

这样问题就迎刃而解了
#  _AC code_
```c
// 我也是看了楼上的思路才明白的，框架和他的有点像，但并没有抄袭。
// 其实都是正解
#include<bits/stdc++.h>
#define myint long long
using namespace std;
int f[100010],p=-1; int tr1=-1,tr2=-1;
int main()
{
	std::ios::sync_with_stdio(false); //加速cin和cout的
	int n; cin>>n;
	myint a[n]; myint ans=0;
	for(int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	for(int i=0;i<n;i++) if(a[i]<a[i-1]+a[i-2]&&i>=2) f[++p]=i;
	tr1=f[p];
	for(int i=0;i<p;i++) if(tr1-f[i]>=3) tr2=f[i];
	//cout<<tr1<<" "<<tr2<<endl; 
	if(tr2!=-1) ans=a[tr1]+a[tr1-1]+a[tr1-2]+a[tr2]+a[tr2-1]+a[tr2-2];
	if(tr1>=5)
	{
		myint t1=a[tr1-5],t2=a[tr1-4],t3=a[tr1-3],t4=a[tr1-2],t5=a[tr1-1],t6=a[tr1];
		myint tmp=t1+t2+t3+t4+t5+t6;
		if(t1+t2>t3&&t4+t5>t6) ans=tmp;
		else if(t1+t2>t4&&t3+t5>t6) ans=tmp;
		else if(t1+t2>t5&&t3+t4>t6) ans=tmp;
		else if(t1+t2>t6&&t3+t4>t5) ans=tmp;
		else if(t1+t3>t4&&t2+t5>t6) ans=tmp;
		else if(t1+t3>t5&&t2+t4>t6) ans=tmp;
		else if(t1+t3>t6&&t2+t4>t5) ans=tmp;
		else if(t1+t4>t5&&t2+t3>t6) ans=tmp;
		else if(t1+t4>t6&&t2+t3>t5) ans=tmp;
		else if(t1+t5>t6&&t2+t3>t4) ans=tmp;
	}
	cout<<ans<<endl;
	return 0;
}
```
有不理解的评论区或者私信我。

### 改进日志
2021.8.23 将 $Latex$ 的排版改进

---

## 作者：huhexuan (赞：3)

这是一道贪心题。

很明显暴力会超时，那就考虑贪心思路。

首先根据三角形任意两边之和大于第三边得出结论:

 $$a[i]<a[i-1]+a[i-2]$$ 

这里的 $a[i]$ 是一个三角形的最长边，之所以是 $a[i]<a[i-1]+a[i-2]$ ，是因为在排完序之后，对于 $a[i]$ 来说 $a[i-1]$ 和 $a[i-2]$ 是最大的长度小于 $a[i]$ 的两条边，如果 $a[i]\ge a[i-1]+a[i-2]$，那么 $a[i]$ 很明显不合法，因为肯定没有另外的两条边 $a[j]$ 和 $a[k]$ 满足 $a[j]<a[i]$,$a[k]<a[i]$, 且 $a[i]<a[j]+a[k]$。
 
所以第一步就是先排一遍序，之后将每一个合法的 $a[i]$ 的下标存在$xia$数组中，取出 $a[xia[len]]$ 作为第一个三角形的最长边，那么第一个三角形的周长也就是：
$$anssum1=a[xia[len]]+a[xia[len]-1]+a[xia[len]-2]$$

### $xia$ 数组中存下标的原因：

是因为在找第二个三角形最长边时可能会引起重复使用，记录下标会更好的解决这个问题，详见下文。

### 第二个三角形的周长求法：

首先找第二个三角形的最长边，但为了避免重复使用，所以要加一个特判：$xia[len]-xia[i]>2$。

为什么要加这样一个特判呢？

因为 $xia[len],xia[len]-1,xia[len]-2$   都被第一个三角形用过了，第二个三角形只能从 $xia[len]-3$ 开始使用，所以要加一个特判。

那第二个三角形的最长边长就是最大的满足 $xia[len]-xia[i]>2$ 的 $a[xia[i]]$。

将这个最长边长的下标设为   $ansxia2$，那周长就是：

 $$anssum2=a[ansxia2]+a[ansxia2-1]+a[ansxia2-2]$$

### 答案的求法：

如果找到了 $ansxia2$，那么 $anssum1+anssum2$ 就是一个合法答案，但不一定是最优解。

为什么不是最优解？

因为 $xia[len]$ 的前面 6 个（包括它自己），如果有两组满足之前的 $a[i]<a[i-1]+a[i-2]$，也就是能组成两个三角形，那么 $a[xia[len]]+a[xia[len]-1]+a[xia[len]-2]+a[xia[len]-3]+a[xia[len]-4]+a[xia[len]-5]$ 才是最优解。

那么如果没有这样的合法的两组，答案就是 $anssum1+anssum2$。

如果既没有合法的两组，也没有找到 $ansxia2$,那就直接输出 $0$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,a[100005],xia[100005]; 
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	int len=0;
	for(int i=3;i<=n;i++) if(a[i]<a[i-2]+a[i-1]) xia[++len]=i;
	int ansxia1=xia[len];
	int ansxia2=0;
	for(int i=1;i<len;i++) if(xia[len]-xia[i]>=3) ansxia2=xia[i];
	int anssum=0;
	bool flag=0;
	if(ansxia1>=6)
	{
		int t1=a[ansxia1-5],t2=a[ansxia1-4],t3=a[ansxia1-3],t4=a[ansxia1-2],t5=a[ansxia1-1],t6=a[ansxia1];
		int tmp=t1+t2+t3+t4+t5+t6;
		flag=0;
		if(t1+t2>t3&&t4+t5>t6) anssum=tmp,flag=1;
		if(t1+t2>t4&&t3+t5>t6) anssum=tmp,flag=1;
		if(t1+t2>t5&&t3+t4>t6) anssum=tmp,flag=1;
		if(t1+t2>t6&&t3+t4>t5) anssum=tmp,flag=1;
		if(t1+t3>t4&&t2+t5>t6) anssum=tmp,flag=1;
		if(t1+t3>t5&&t2+t4>t6) anssum=tmp,flag=1;
		if(t1+t3>t6&&t2+t4>t5) anssum=tmp,flag=1;
		if(t1+t4>t5&&t2+t3>t6) anssum=tmp,flag=1;
		if(t1+t4>t6&&t2+t3>t5) anssum=tmp,flag=1;
		if(t1+t5>t6&&t2+t3>t4) anssum=tmp,flag=1;
	}	
	if(!flag) if(ansxia2) anssum=a[ansxia1]+a[ansxia1-1]+a[ansxia1-2]+a[ansxia2]+a[ansxia2-1]+a[ansxia2-2];
	cout<<anssum<<"\n";
    return 0;
}
```

---

## 作者：dOvOb (赞：2)

首先我们在排序后的 $a$ 数组中考虑这个问题。

对于一个从 $a$ 数组中选出的三角形，若它的三条边分别为 $(a_i,a_j,a_k)$，其中 $i<j<k$，那么我们定义它覆盖的区间 $f((a_i,a_j,a_k))=[i,k]\cap \mathbb{N}$，显然 $\forall x,f(x)\ge 3$。

那么，有这样一个结论：如果我们最终选出的两个三角形为 $x,y$，那么 $|f(x)\cup f(y)|=6$。

> 证明：
>
> 我们分两种情况讨论。
>
> ---
>
> 第一种情况，当两个三角形覆盖的区间不交时，原结论等价于 $|f(x)|+|f(y)|=6 $。又因为 $|f(x)\ge 3|,|f(y)\ge 3|$，所以只需证明 $|f(x)|=|f(y)|=3$。
>
> 设 $x=(a_i,a_j,a_k)$，其中 $i<j<k$。若 $|f(x)|\gt 3$，则意味着 $k-i+1\gt 3$，即 $k-i\gt 2$。这时我们可以构造三角形 $x'=(a_{k-2},a_{k-1},a_k)$。容易发现有
>
> $$
> i<k-2,j\le k-1
> $$
>
> 因为 $a$ 是排序后的，所以
>
> $$
> a_i\le a_{k-2},a_j\le a_{k-1}
> $$
>
> 所以若 $x$ 满足 $a_i+a_j>a_k$，则 $x'$ 同样满足 $a_{k-2}+a_{k-1}>a_{k}$，同样可以构成三角形，而且构成的三角形和 $y$ 的边没有重合（读者自证不难），同样合法。而且 $C_{x'}\ge C_{x}$，所以 $x'$ 不劣于 $x$。因此 $x$ 不会出现在答案里。所以 $|f(x)|=3$。同理可证， $|f(y)=3|$。结论证毕。
>
> ---
>
> 第二种情况，当两个三角形覆盖的区间有交时。
>
> 设 $x=(a_i,a_j,a_k),y=(a_m,a_n,a_p)$，其中 $i<j<k,m<n<p,k>p>i,\set{i,j,k}\cap \set{m,n,p}=\empty $。
>
> 设 $S=(f(x) \cup f(y))\setminus (x\cup y)$，若 $|f(x)\cup f(y)|>6$，则 $|S|>0$。我们对 $|S\cap [p,k]|$ 分类讨论。
>
> 若 $|S\cap [p,k]|=0$，我们可以将 $x$ 中短于 $a_p$ 的边和 $y$ 中短于 $a_p$ 的边按大小顺序分别改为 $a_{p-1},a_{p-2},a_{p-3},\dots$，即，将 $\set{a_i,a_j,a_k,a_m,a_n,a_p}$ 中在 $a$ 中的位置小于 $p$ 的最大的边改成 $a_{p-1}$，次大的改为 $a_{p-2}$，以此类推。仿照第一种情况的证明，我们容易说明这样是不劣的。这样之后， $f(x)\cup f(y)=\set{k-5,k-4,k-3,k-2,k-1,k}$。故 $|f(x)\cup f(y)|=6$。
>
> 若 $|S\cap [p,k]|=1$，我们将 $j$ 改成 $k-1$，仿照第一种情况，容易说明这样是不劣的。这时就变成 $|S\cap [p,k]|=0$ 的情况了。
>
> 若 $|S\cap [p,k]|\ge 2$，则我们可以将 $i,j$ 分别改成 $k-2,k-1$。仿照第一种情况容易说明这样不劣。这样之后 $x$ 和 $y$ 覆盖的区间就不交了，转化为第一种情况。
>
> 结论证毕。
>
> ---

于是，我们只需要分别处理这两种情况即可。对于第一种情况，我们可以用一次 dp 解决。对于第二种情况，我们枚举 $x$ 和 $y$ 覆盖区间的并集，然后枚举划分方案更新答案即可。

时间复杂度 $O(n\log n+n+C(6,3)\times n)$。

代码：

```cpp
// https://atcoder.jp/contests/utpc2011/tasks/utpc2011_7
#include<bits/stdc++.h>
using namespace std;
using i64=long long;
constexpr int mxn{100005};
int N;
i64 a[mxn],dp[mxn];
bool canmake(array<i64,3>a)
{
	return a[0]+a[1]>a[2];
}
bool check(array<i64,6>x)
{
	for(unsigned i=0;i<(1<<6);++i)
	{
		if(popcount(i)==3)
		{
			array<i64,3>a,b;
			int ia=0,ib=0;
			for(int j=0;j<6;++j)
				if(i&(1<<j))
					a[ia++]=x[j];
				else
					b[ib++]=x[j];
			sort(a.begin(),a.end());
			sort(b.begin(),b.end());
			if(canmake(a)&&canmake(b))
				return true;
		}
	}
	return false;
}
int main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cin>>N;
	for(int i=0;i<N;++i)
		cin>>a[i];
	sort(a,a+N);
	fill_n(dp,N,-1e18);
	if(canmake({a[0],a[1],a[2]}))
		dp[2]=a[0]+a[1]+a[2];
	i64 ans=0;
	for(int i=3;i<N;++i)
	{
		if(canmake({a[i-2],a[i-1],a[i]}))
		{
			dp[i]=max(dp[i],a[i-2]+a[i-1]+a[i]);
			ans=max(ans,dp[i-3]+a[i-2]+a[i-1]+a[i]);
		}
		dp[i]=max(dp[i],dp[i-1]);
	}
	for(int i=6;i<=N;++i)
	{
		array<i64,6>x;
		copy_n(a+i-6,6,x.begin());
		if(check(x))
			ans=max(ans,accumulate(a+i-6,a+i,0ll));
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Rannio (赞：2)

**题目大意**：从 $n$ 根木棒里选出六根拼成两个合法的三角形，使这两个三角形的周长和最大。
  
考虑贪心，证明在后面。  
  
首先我们要知道一个三角形基本定理：**较短两边长度之和大于最长边**。  
那我们就根据这个定理先去寻找最大三角形的最长边。  
先排序，然后循环枚举，对于每个 $a_i$，可以寻找到的最大的其余两边为 $a_{i-1}$ 与 $a_{i-2}$，如果该组不合法，那么其余组也不合法，否则我们就保存当前的 $i$，把最大的两组加起来输出即可。

但是这题还有个比较坑的地方，两组合法三角形的边可能产生冲突，解决方法也很简单：从最大三角形的最长边往下找六条边，只要里面还有一种组合合法那就是最优解，否则无解。

**证明**：  
设可以选的最大边为为 $s_m$，那么对于一组可选边 $s_i$，$s_j$，会有以下几种情况：
- $s_i$ 与 $s_j$ 不冲突，那么 $s_i$ 与 $s_m$ 肯定也不冲突，所以选 $s_i$ 和 $s_m$。
- $s_i$ 与 $s_j$ 冲突，但 $s_j$ 与 $s_m$ 不冲突，那么选 $s_j$ 与 $s_m$ 最优。
- $s_i$ 与 $s_j$ 冲突，但 $s_i$ 与 $s_m$ 不冲突，那么选 $s_i$ 与 $s_m$ 最优。
- $s_i$ 与 $s_j$ 冲突，并且它们与 $s_m$ 都有冲突，那么选哪组都对答案无影响。  
  
证毕。
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,s,d[100005],f[100005];
ll ans,sum,cnt,maxn;
int main() {
	scanf("%lld",&a);
	for(int i=1;i<=a;i++){
		scanf("%lld",&d[i]);
	} 
	sort(d+1,d+a+1);
	for(int i=3;i<=a;i++){
		if(d[i]<d[i-1]+d[i-2]){
			f[++cnt]=i;
		}
	}
	for(int i=1;i<=cnt;i++){
		if(f[cnt]-f[i]>=3){
			maxn=i;
		}
	}
	if(maxn!=0){
		ans=d[f[cnt]]+d[f[cnt]-1]+d[f[cnt]-2]+d[f[maxn]]+d[f[maxn]-1]+d[f[maxn]-2];
	}
	if(f[cnt]>=6){
		ll num1=d[f[cnt]-5],num2=d[f[cnt]-4],num3=d[f[cnt]-3],num4=d[f[cnt]-2],num5=d[f[cnt]-1],num6=d[f[cnt]];
		sum=num1+num2+num3+num4+num5+num6;
		if(num1+num2>num3&&num4+num5>num6){
			ans=sum;
		}
		if(num1+num2>num4&&num3+num5>num6){
			ans=sum;
		}
		if(num1+num2>num5&&num3+num4>num6){
			ans=sum;
		}
		if(num1+num2>num6&&num3+num4>num5){
			ans=sum;
		}
		if(num1+num3>num4&&num2+num5>num6){
			ans=sum;
		}
		if(num1+num3>num5&&num2+num4>num6){
			ans=sum;
		}
		if(num1+num3>num6&&num2+num4>num5){
			ans=sum;
		}
		if(num1+num4>num5&&num2+num3>num6){
			ans=sum;
		}
		if(num1+num4>num6&&num2+num3>num5){
			ans=sum;
		}
		if(num1+num5>num6&&num2+num3>num4){
			ans=sum;
		}
	} 
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

首先将所有边的长度从大到小排序，并找出所有合法并且靠近的三元组 $(x,y,z)$ 满足 $x>y>z$ 组成一个三条边为 $x$，$y$，$z$ 的三角形。很显然合法的三角形必然满足 $y+z>x$。

定义一个满足上述条件的三元组的权值系数 $S(x,y,z)$ 为 $x+y+z$，那么求出所有的权值系数之后，权值系数最大的三元组 $(x,y,z)$ 组成的三角形是必须要选择的。

第一个三角形选择完毕之后，就需要选择第二个三角形了。

显然第二个三角形应该选择上面得到的所有的三元组中权值系数 $S$ 最大并且和第一个三角形没有任何的交集（互不影响），这样才能使答案最大。

特殊情况：如果边的长度最大的 $6$ 条边可以恰好组成两个不同的三角形且不重不漏那么这样更优秀。

时间复杂度是 $O(n\log n)$ 的，瓶颈在于排序。

---

## 作者：Wsy_flying_forever (赞：1)

# 题意描述
    n支木棍，选6根组成两个三角形。求两个三角形最大周长和。
# 解题思路
我们将原问题分为若干子问题进行求解
##     1.排序
      看到这题以后，我们可能毫无头绪，但仔细想一下，求最大周长和，选取的边肯定是越大越好。
##     2.选取最大边
      选三角形最大边，前提是与它最接近的两条边之和必须比它大，才有可能组成三角形。而在此条件下求得的最大边max，可以证明必为ans中的一条边。
###    证明
   设选取的边是为 $b[i]$ 、 $b[j]$ （i>=j）   
   a.$i-j \geq 3$   
   取 $b[m]$、$b[j]$ 显然更优  
   b.$i-j < 3$ && $(m-j \geq 3 || m-i \geq 3)$
   取 $b[m]$、$b[i] || b[j]$ 显然更优  
   c.$i-j<3$ && $m-i<3$ && $m-j<3$  
   取 $b[m]$、$b[i]$  或 $b[m]$、$b[j]$ 使选边的可能性增大，显然更优
####       **证毕**
##     3.简单的贪心
   分两种情况  
   A.取 $b[i]$ 的最大值使其不与 $b[m]$ 冲突，求该种情况下的三角形边数之和  
   B.设最大边max在a数组编号id，在 $a[id]$、$a[id+1]$.....$a[id+5]$ 以任意方式排列能构成两个三角形时，取该种情况下的三角形边数之和
其中B的优先级大于A
## 4.输出答案即可


---

## 作者：Zskioaert1106 (赞：0)

前言：冥思苦想得出一个零分代码后，迫不得已看了题解（我不会告诉你最后原因是没开 long long 的），然后发现大家的做法好像都差不多？这里简单总结一下这题思路，然后说说我踩的坑。

题目传送门：[AT_utpc2011_7 プログラミングコンテストチャレンジブック](https://www.luogu.com.cn/problem/AT_utpc2011_7)

### 做题思路

首先这题是贪心无疑（我总记得做过一道类似的题，但就是想不起来了），我们知道**三角形两边之和大于第三边**，所以我们就可以定义一个 $f$ 数组，用以存储所有的可能情况：

```cpp
for(int i=1;i<=n;i++)cin>>a[i];
sort(a+1,a+1+n);
for(int i=3;i<=n;i++){
  if(a[i]<a[i-2]+a[i-1])f[top++]=i;
}
```

（$top$ 代表满足情况的三角形数——或者是三角形的某一条边数）

这样先~~拍一遍婿~~排一遍序，就可以保证越往后的结果更优，因为我们要求的是能组成的两个三角形的周长和的**最大值**。所以我们的第一个三角形就是：

```cpp
ansone=f[top];
```

之后这一步：

```cpp
for(int i=1;i<top;i++){
  if(f[top]-f[i]>2)
    anstwo=f[i];
}
```

这一步的意思（好像楼上有一位的题解里讲过了）就是：$f_{top}$，$f_{top-1}$，$f_{top-2}$ 都在第一个三角形中用过了，所以第二个三角形的答案只能是第二个往后的合法边。

但是此时这两个三角形的结果并不是全部的正确答案，因为事实上，如果 $ans_{one}\geqslant6$，那从 $f_{top-6}$ 到 $f_{top-3}$ 的三条边才是最优的第二个三角形。

然后就到了~~最麻烦~~的部分了，即这两个三角形六条边满足题目的所有情况。

```cpp
long long t1=a[f[top]-5],t2=a[f[top]-4],t3=a[f[top]-3],
t4=a[f[top]-2],t5=a[f[top]-1],t6=a[f[top]];
if(t1+t2>t3&&t4+t5>t6)
or(t1+t2>t4&&t3+t5>t6)
or(t1+t2>t5&&t3+t4>t6)
or(t1+t2>t6&&t3+t4>t5)
or(t1+t3>t4&&t2+t5>t6)
or(t1+t3>t5&&t2+t4>t6)
or(t1+t3>t6&&t2+t4>t5)
or(t1+t4>t5&&t2+t3>t6)
or(t1+t4>t6&&t2+t3>t5)
or(t1+t5>t6&&t2+t3>t4)
  ans=t1+t2+t3+t4+t5+t6;
```

同时这里还要加一个判断即 $ans_{one}\geqslant6$，如果不满足很显然上面的第二个三角形不成立。如果不成立，原来的 $ans_{two}$ 才是答案：

```cpp
if(!ans&&anstwo)
  ans=a[ansone]+a[ansone-1]+a[ansone-2]+a[anstwo]+a[anstwo-1]+a[anstwo-2];
```

此时我们的程序还有一个功能，就是找不到任何正确的三角形时，会输出 `0`。

### ~~代码编写~~踩坑

以下是我亲自踩过的坑：

- 首先，不要只看出如何求两个三角形就提交

- 其次，判断好两种方法分别是什么时候用：第一种是 $ans_{one}\geqslant6$ 且六条边能组成合法的三角形，第二种是 `!ans&&anstwo`

- 最后，**不开 long long 见祖宗！！！**

当然 AT 的题都要换行，不过我相信你应该知道。

#### 完整代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,top=0,a[100005],f[100005],ans=0,ansone,anstwo=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=3;i<=n;i++){
        if(a[i]<a[i-2]+a[i-1])f[top++]=i;
    }
    ansone=f[top];
    for(int i=1;i<top;i++){
        if(f[top]-f[i]>=3)anstwo=f[i];
    }
    if(ansone>=6){
		long long t1=a[f[top]-5],t2=a[f[top]-4],t3=a[f[top]-3],t4=a[f[top]-2],t5=a[f[top]-1],t6=a[f[top]];
		if(t1+t2>t3&&t4+t5>t6||t1+t2>t4&&t3+t5>t6||t1+t2>t5&&t3+t4>t6||t1+t2>t6&&t3+t4>t5||t1+t3>t4&&t2+t5>t6||t1+t3>t5&&t2+t4>t6||t1+t3>t6&&t2+t4>t5||t1+t4>t5&&t2+t3>t6||t1+t4>t6&&t2+t3>t5||t1+t5>t6&&t2+t3>t4)ans=t1+t2+t3+t4+t5+t6;;
	}
	if(!ans&&anstwo)ans=a[ansone]+a[ansone-1]+a[ansone-2]+a[anstwo]+a[anstwo-1]+a[anstwo-2];
	cout<<ans<<'\n';
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/171881451)

感谢（鞠躬）

---

## 作者：huangrenheluogu (赞：0)

这道题没有样例，我把官方样例放在最前面：

AtCoder 的题目在 [这里](https://atcoder.jp/contests/utpc2011/tasks/utpc2011_7)。

```
in:
6
1
1
1
1
1
1
out:
6
```

**然后，如果 `ans` 后面没有 `\n`，请加上。**

~~这个数据强度，我服了。~~

## 从错解出发

看到这一道题目，我第一眼想到的就是找到两个最大的三角形。

首先，先将数组升序排序。

感觉是一种惯性的思维方式，选了 $a,b,c,d,e,f,a\le b\le c\le d\le f$，让人很容易感觉是 $a,b,c$ 一组，$d,e,f$ 一组。

可能各位神犇不是这么想的，但我这个蒟蒻确实这么想过。

但是考虑 `2 3 5 5 6 7` 这六个数，可以 $(2,6,7),(3,5,5)$ 组合（当然不止这一种方式），并没有按照上面的思路，所以这一种做法是错误的。

## 从让我们错误的样例爬起

发现如果要按照上满的情况，$a+b\le c$ 但是仍然可行，可以感性地理解要取地尽量接近。

而且如果更小的数可行，换成更大的数依然满足“两边之和大于第三边”的条件。

所以我们记录一个 $\{b\}$ 存储 $a_i,a_{i-1},a_{i-2}$ 符合三角形三边的条件的 $i$。

我们分两种情况讨论：

- 两个数集互不相交

直接相加。

- 两个数集相交

去除最近的 $6$ 个数，判断。

我看了一下题解，发现判断过程都是手写，但是感觉用循环更加方便。

但是对于每一个 $i$，去枚举 $j$，会超时。

发现 $\{b\}$ 数组里的元素单调，所以可以从 $i-1$ 开始枚举，知道枚举完毕或者满足 $b_j\le b_i-3$，这里应用了贪心。

可以写出代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, a[N], b[N], cnt, ans, c[7], d[7], e[7], cnt1, cnt2;
inline bool check(){
	sort(e + 1, e + 4);
	sort(d + 1, d + 4);
	return e[1] + e[2] > e[3] && d[1] + d[2] > d[3];
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 3; i <= n; i++){
		if(a[i] < a[i - 1] + a[i - 2]) b[++cnt] = i;
	}
	for(int i = 1; i <= cnt; i++){
		for(int j = i - 1; j >= 1; j--){
			if(b[j] > b[i] - 3) continue ;
			ans = max(ans, a[b[i]] + a[b[i] - 1] + a[b[i] - 2] + a[b[j]] + a[b[j] - 1] + a[b[j] - 2]);
			break;
		}
		if(b[i] >= 6){
			for(int j = 1; j <= 6; j++) c[j] = a[b[i] - j + 1];
			for(int k = 1; k <= 6; k++){
				for(int kk = 1; kk <= 6; kk++){
					if(k == kk) continue ;
						for(int kkk = 1; kkk <= 6; kkk++){
						if(k == kkk || kk == kkk) continue ;
						cnt1 = cnt2 = 0;
						for(int j = 1; j <= 6; j++){
							if(j == k || j == kk || j == kkk) d[++cnt1] = c[j];
							else e[++cnt2] = c[j];
						}
						if(check()) ans = max(ans, c[1] + c[2] + c[3] + c[4] + c[5] + c[6]);
					}
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

这一份代码虽然时间复杂度比较大，但是感觉思路更加清晰，而且不会 TLE，所以可能比大部分题解会更加好想。

主要还是我太弱了，如果有大神会只用 $b_{cnt}$ 的证明，欢迎在评论区薄纱我。

---

