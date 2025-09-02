# XOR Pairs

## 题目背景

CT 每天只知道在伦敦哼哼蓝调，在校领导面前溜达，懒惰而浪荡的生活使他非常的潦倒，于是，他决定痛改前非学习数学……


## 题目描述

CT 在做数学题。

CT 手里一个长度为 $n$ 的序列 $a$，现在给定 CT $q$ 次操作，对于每次操作：
- 把 $a_x$ 改成 $y$ 。
- 求修改后数组中合法二元组的个数。

**注：** 对于一对满足 $a_i\oplus a_j > \max\{a_i,a_j\}$ 的 $(a_i,a_j)(i<j)$ 二元组，我们称其为合法二元组。其中 $\oplus $ 表示按位异或，$\max\{x,y\}$ 表示 $x,y$ 中的较大值。



## 说明/提示

#### 【数据范围】

对于全部数据，保证 $1\le n \le 10^6$，$1\le q\le 10^5$，$1\le a_i\le 10^6$，$1\le x \le n$，$1\le y \le 10^6$。

|$\text{Subtask}$|$n\leq$|$q\leq$|分值| 特殊性质 |
|:-:|:-:|:-:|:-:|:-:|
|$0$|$10^2$|$10^2$|$13$|无|
|$1$|$10^6$|$10^5$|$87$|无|

## 样例 #1

### 输入

```
6 4
1 1 4 5 1 4
1 2
4 3
5 2
6 5```

### 输出

```
9
10
10
9```

# 题解

## 作者：Miracle_InDream (赞：15)

可能没人能想到我这只蒟蒻会来写这题题解吧。

赛时打了个暴力（因为太菜了），只拿了 13pts。赛后求助机构老师，老师给出了代码，我自己边打边研究了下，有些没写注释的地方我自己看懂了。感谢老师的指导！

因为数据量比较大，$O(n^2)$ 的时间复杂度肯定会超。

那我们该怎么办呢？

想让 $x \oplus y > \max(x,y)$（注：$\oplus$ 代表异或），那么 $x$ 的最高位 $1$ 一定对应 $y$ 位置的 $0$ ，所以统计最高位的 $1$ 和每个位置的 $0$，再使用排列组合实现。（注：这篇题解所有最高位的 $1$ 和每一位的 $0$ 都是二进制下的！别搞错了！！！！！）

所以，每输入一个数，我们都需要求这个数最高位的 $1$ 和每一位的 $0$。

这一部分的代码如下：

```cpp
void find1(int x,int v)
{
	int a=1;
	int n=-1;
	while(x)//如果 x>0，那就判断 x 的最后一位是不是 1
	{
		if((x&1)==1)//如果是，n 就变成 a
		{
			n=a;
		}
		a++;
		x>>=1;
		//a 增加 1，x>>=1 的效果与 x/=2 差不多，部分童鞋可以检查下这部分是不是脑子混掉然后直接写上 x/=10 捏~
	}
	b1[n]+=v;//b1[n] 要加上 v。
}//查找最高位的 1。
void find0(int x,int v)
{
	int a=1;
	while(x)//如果 x>0，那就判断 x 的最后一位是不是 0 
	{
		if((x&1)==0)//如果是，b0[a] 就要加上 v。
		{
			b0[a]+=v;
		}
		a++;
		x>>=1;
	}
}//查找每一位的 0。
//这段虽然和上面那个查找最高位的 1 差不多，但是功能上还是有差异的。这个是查找每一位的 0 的。
```

下面的主函数实现方式也很简单，我们可以边输入边统计最高位的 $1$ 和每一位的 $0$，然后每次询问（更改）都要清空数组里与原数字相应的位置，再统计新数字最高位的 $1$ 和每一位的 $0$（~~有点儿啰嗦，其实写到这里我自己满脑子也都是最高位的 $1$ 和每一位的 $0$ 了 hhh~~）。

上代码（除了老师的注释，我自己也加了很多注释，有很多关于自己对代码的解读，如果有问题，可以帮我纠正捏~）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
long long b1[105],b0[105],a[N],n,q;
long long ans;
void find1(int x,int v)
{
	int a=1;
	int n=-1;
	while(x)//如果 x>0，那就判断 x 的最后一位是不是 1
	{
		if((x&1)==1)//如果是，n 就变成 a
		{
			n=a;
		}
		a++;
		x>>=1;
		//a 增加 1，x>>=1 的效果与 x/=2 差不多，部分童鞋可以检查下这部分是不是脑子混掉然后直接写上 x/=10 捏~
	}
	b1[n]+=v;//b1[n] 要加上 v。
}//查找最高位的 1。
void find0(int x,int v)
{
	int a=1;
	while(x)//如果 x>0，那就判断 x 的最后一位是不是 0 
	{
		if((x&1)==0)//如果是，b0[a] 就要加上 v。
		{
			b0[a]+=v;
		}
		a++;
		x>>=1;
	}
}//查找每一位的 0。
//这段虽然和上面那个查找最高位的 1 差不多，但是功能上还是有差异的。这个是查找每一位的 0 的。
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		find1(a[i],1);
		find0(a[i],1);
		//这里可以边输入边找最高位的 1 和每一位的 0。
	}
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		find1(a[x],-1);
		find0(a[x],-1);
		find1(y,1);
		find0(y,1);
		a[x]=y;
		//因为 a[x] 被更改了，所以这里需要清掉 b1 和 b0 两个数组原本因为 a[x] 造成的改变，并重新统计 y 的最高位的 1 和每一位的 0，存进 b1 和 b0。
		ans=0;
		for(int i=1;i<=32;i++)
		{
			ans+=b1[i]*b0[i];//求修改后数组中合法二元组的个数。
		}
		cout<<ans<<endl;//输出！
	}
	return 0;//华丽结束~~~
}
```

求管理大大通过捏~

---

## 作者：Drifty (赞：7)

### Preface

啊？

### Solution

对于 $ \forall (a,b)$，若其是靓点二元组的充要条件为：

- $b$ 的二进制位数小于 $a$。
- $b$ 的最高位对应的 $a$ 这一位为 $0$（二进制）。

**为什么？**

第一条是为了保证顺序（即 $i<j$）。

第二条则是真正的关键。由于 $b$ 的最高位必定为 $1$，若 $b$ 的最高位对应的 $a$ 这一位为 $1$，则那一位异或后的结果必定为 $0$，而 $a$ 那一位原来为 $1$，因此导致 $a\ \mathrm{xor}\ b$ 必定小于 $a$，又由第一条知 $a>b$，$\therefore a\ \mathrm{xor}\ b<\max\{a,b\}$，违背题意。

**如何实现？**

我们可以开设两个桶 $t,p$，对于每一个 $a_i$，把它的二进制分离出来，枚举每一位。如果对于从右到左的第 $i$ 位为 $0$，则 $t_i+1\to  t_i$；如果对于从右到左的第 $i$ 位为 $1$，则 $p_i+1\to  p_i$。

这样，从 $1$ 枚举到 $\log_2{\max\{a_i\}}+1$，把 $ans$ 不断加上 $t_i\times p_i$ 即是答案。

时间复杂度 $O(n\times\log_2{\max\{a_i\}})$，空间复杂度 $O(n+\log_2{\max\{a_i\}})$。

### AC-Code

以下是 [Pentatonic_Vi0lin](/user/761743) 给出的实现。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
    int x=0, f=1; char c = getchar();
    while (c<'0' || c>'9') {if (c == '-') f = -1; c = getchar();}
    while (c>='0' && c<='9') x = (x << 3) + (x << 1) + (c ^ 48), c=getchar();
    return x * f;
}
constexpr int N = 3e6 + 5, add = 1, del = -1;
long long a[N], b[305], c[305], n, ans, Q, x, y;
inline void change(long long num, int op) {
	int k = 1;
	for (; num; k ++, num >>= 1) 
		if (!(num & 1)) b[k] += op;
	c[k-1] += op;
}
signed main() {
	int n = read(), Q = read(); 
	for (int i=1; i<=n; i++)
		a[i] = read(), change(a[i], add);
	while (Q--) {
		x = read(), y = read();
		change(a[x], del), change(y, add);
		a[x] = y, ans = 0;
		for(int i=1; i<=32; i++) ans += b[i] * c[i];
		printf("%d\n", ans); 
	}
	return 0;
}
```

---

## 作者：_Supernova (赞：3)

###  一、思路分析。

本题关键在于如何求出数对个数。

对于数 $a$ 和 $b$，如何判定合法？

不妨设 $a \leq b$。

容易发现当 $a$ 的最高位在 $b$ 的位置为 $0$，则可以满足条件。

证明：若那一位为 $1$，则异或起来那一位为 $0$，发现小于 $b$，不满足条件。

如何实现呢？

我们考虑维护两个桶 $t$ 和 $p$，分别维护有多少个数在当前位为 $0$，有多少个数的最高位在这一位。

统计答案时，枚举位数 $i$，则这一位对答案的贡献即为 $t_i \times p_i$。

每次询问修改两个桶即可。

###  二、代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef unsigned long long ull;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <pii, int> piii;
typedef long double ld;
const int N = 1e6 + 6, V = 30;
ll n, q, t[V], p[V], a[N], x, y;
void change(ll num, ll add) {
	ll pos = 1;
	while (num) {
		if (!(num & 1)) {
			t[pos] += add;
		}
		++pos;
		num >>= 1;
	}
	p[pos - 1] += add;
	return ;
}
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (ll i = 1; i <= n; ++i) {
		cin >> a[i];
		change(a[i], 1);
	}
	while (q--) {
		cin >> x >> y;
		change(a[x], -1);
		change(y, 1);
		a[x] = y;
		ll ans = 0;
		for (ll i = 1; i < V; ++i) {
			ans += (p[i] * t[i]);
		}
		cout << ans << '\n';
	}
	return 0;
}
```

感谢！

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
暴力是不可能暴力的，$O(nq)$ 的时间复杂度绝对过不了，想了想也没想到有什么数据结构能优化。那么既然有异或，我们就可以直接考虑二进制了。
## 2. 题目做法
考虑什么情况下两个数进行异或之后比这两个数的较大值还大，我们也可以想成更大的那个数要异或上什么样的数才能使自己变得更大。因为异或运算法则是每位上若相同则为 $0$，若不同才为 $1$，更小的那个数最高位一定为 $1$，若更小数最高位对应更大数的这个位上是 $1$，那么这个位异或后便为 $0$，后面不管怎么样，异或出的数一定不会大于更大数。  
如果我们反过来想，更小数的最高位如果对应更大位的这个位上是 $0$，那么异或出的数一定大于更大数。  
统计的话只需要开一个桶记录这个位上是 $0$ 的数有多少个，要快速修改的话只需要统计这个位上是最高位的数有多少个，这样预处理复杂度为 $O(n)$，每次询问时间复杂度为 $O(1)$，完全可以通过此题。  
最后注意答案会较大，注意变量类型。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x; 
}
bitset<20>t;
int n,m;
int a[N],x,y;
int num[N],zero[20],s[20];
long long sum;
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		t=a[i];
		for(int j=19;j>=0;j--)
		{
			if(t[j])
			{
				num[i]=j;
				s[j]++;
				break;
			}
		}
		for(int j=0;j<num[i];j++)
			!t[j]?zero[j]++:1;
	}
	for(int i=1;i<=n;i++)
		sum+=zero[num[i]];
	while(m--)
	{
		x=read(),y=read();
		sum-=zero[num[x]];
		t=a[x];
		for(int i=0;i<num[x];i++)
			!t[i]?zero[i]--,sum-=s[i]:1;
		s[num[x]]--;
		t=a[x]=y;
		for(int i=19;i>=0;i--)
		{
			if(t[i])
			{
				num[x]=i;
				break;
			}
		}
		s[num[x]]++;
		for(int i=0;i<num[x];i++)
			!t[i]?zero[i]++,sum+=s[i]:1;
		sum+=zero[num[x]];
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：锦依卫小生 (赞：1)

# P11016  
## 题意简述  
对一个数组进行 $q$ 次操作，每次操作后查询异或结果大于最大值的对数。  
## 基本思路  
采用字典树维护。先不考虑更新操作，对初始数组如何计算结果，每次操作在上一次基础上补充计算即可。    
对二进制位分析，对每个数字 $x$ 考虑小于它的数 $y$，求和后就是初始结果。考虑满足条件的情形。对 $x$ 和 $y$ 的二进制位进行分析，发现 $y$ 总是形如若干连 $0$ 后出现 $1$，该 $1$ 位对应的 $x$ 必须是 $0$ 且在 $x$ 的做高位 $1$ 后。而后 $y$ 的位可任取。    
字典树维护策略：插入时统计每个节点下共有几个数字（计数器数组 $cnt$ 累加即可）。统计答案沿着 $0$ 边遍历，若当前已过 $x$ 最高 $1$ 位，且 $x$ 在这一位上是 $0$ ，累加 $1$ 边下节点的数字个数；无 $0$ 边退出即可。  
继续分析更新操作。此时必须考虑大于当前修改数字的元素对答案的影响。每次更新先减去小于和大于两种情况，在字典树中执行删除操作，再插入新数，加上新数的小于和大于的两种情况即可。    
经过对小于情况的分析，不难发现大于 $x$ 的 $y$ 必须在 $x$ 的最高 $1$ 位上为 $0$，并且在这位之前有至少一位为 $1$。
令 $x$ 的最高 $1$ 位对应边上面的结点为 $u$，答案为 $cnt_{root} - cnt_{u} -delta$。$delta$为不满足在 $x$ 的最高 $1$ 位上为 $0$ 条件的情况。发现对特定 $x$，这种情况出现的位置在字典树中出现的层数是一定的，不妨在插入时对层数维护由 $1$ 边派生的数字个数（注意排除掉 $x$ 本身即形如连 $0$ 后接着 $1$ 的情况）。  
字典树操作执行插入的逆操作即可。    
详见代码
## 代码    
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e6+5;
int ch[MAX*22][2];
int cnt[MAX*22];
int n,q,a[MAX],tot=1,sum[22];//sum 数组维护的就是前文中的 delta。
long long ans;
void insert(int x){
	int u=1;
	cnt[u]++;
	bool flag=0;
	for(int i=20;i>=0;--i){
		int c=(x&(1<<i))?1:0;
		if(!ch[u][c]){
			ch[u][c]=++tot;
		}
		u=ch[u][c];
		cnt[u]++;
		if(c==1){
			if(flag)//排除连 0 接 1 情况 
				sum[i]+=1; 
			flag=1;
		}
	}
}
int find1(int x){//小于
	bool flag=0;
	int u=1;
	int res=0;
	for(int i=20;i>=0;--i){
		if(x&(1<<i)){
			flag=1;
		}
		if(!flag){
			if(cnt[ch[u][0]])//注意加 cnt，删除节点后该点形式上还留在树中 
				u=ch[u][0];
			else
				return 0;
		}
		else{
			if(!(x&(1<<i))){
				res+=cnt[ch[u][1]];
			}
			if(cnt[ch[u][0]]){
				u=ch[u][0];
			}
			else
				return res;//无 0 边退出即可，同本函数上一个 return 
		}
	}
	return res;
}
int find2(int x){//大于
	if(x==0)
		return 0;
	int dep1,u=1;
	for(int i=20;i>=0;--i){
		if(x&(1<<i)){
			dep1=i;
			break;
		}	
		u=ch[u][0];
	}
	return cnt[1]-cnt[u]-sum[dep1];
}
void dele(int x){
	int u=1;
	cnt[1]--;
	bool flag=0;
	for(int i=20;i>=0;--i){
		int c=(x&(1<<i))?1:0;
		u=ch[u][c];
		cnt[u]--;
		if(c==1){
			if(flag)
				sum[i]--;
			flag=1;
		}
	}
}
int read(){
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-'){
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = x*10+c-'0';
		c = getchar();
	}
	return x*f;
}

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		a[i]=read();
		insert(a[i]);
	}
	for(int i=1;i<=n;++i){
		ans+=find1(a[i]); 
	}
	for(int i=1;i<=q;++i){
		int x=read(),y=read();
		ans-=find1(a[x]);
		ans-=find2(a[x]);
		dele(a[x]);
		a[x]=y;
		insert(a[x]);
		ans+=find1(a[x]);
		ans+=find2(a[x]); 
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Union_Find (赞：1)

虽然很丢人，但还是要讲一下我赛时的神奇做法。

一开始很正常的推性质。这种题暴力很好出，但是正解肯定是要用到某些性质的。想到了一个 $O(n \log(A_i)+Tn \log(A_i))$ 的做法，就是先考虑一开始序列的值，每次修改减去 $x$ 的就贡献，加上新贡献。

其实 $a_i$ 的顺序无所谓，我们可以改一下合法二元组定义即可。如果 $a_i\oplus a_j > a_j(a_i < a_j)$，则 $(i,j)$ 合法。这两种定义其实是等价的，所以我们可以考虑当 $a_x$ 作为 $a_i$ 和 $a_j$ 是产生的贡献。

我们发现，当 $a_j > a_i$ 时，只要 $a_i$ 的最高位对应到 $a_j$ 上是 $0$，就合法。所以我们就可以知道当 $a_x$ 作为 $a_i$ 时，只要记录比它大的且符合上述条件的 $a_j$ 数量即可。而 $a_x$ 作为 $a_j$ 时同理。我们只需要知道比它小的且符合条件的 $a_i$ 数量。

按照上面的写发写，你可以得到一份 $O(n \log(A_i)+Tn \log(A_i))$ 的代码。考虑优化。

求比某个数大的数的数量，这不就是权值线段树吗？因为每一位单独计算，且每一个数字只会被计算，所以可以开 $20$ 个线段树。

赛时写线段树 T 飞了，所以改成了树状数组，最后极限卡过。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll int
#define il inline
#define N 1000000
il ll rd(){
	ll s = 0;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar());
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s;
}
ll n = rd(), T = rd(), a[N + 1], x, y, tr[N + 1][21], t[N + 1], sum[N + 1][21];
long long ans;
ll lowbit(ll x){return x & (-x);}
void add(ll x, ll k, ll d){
	for (int i = x; i <= 1e6; i += lowbit(i)) tr[i][k] += d;
}
ll ask(ll x, ll k){
	ll ans = 0;
	for (int i = x; i >= 1; i -= lowbit(i)) ans += tr[i][k];
	return ans;
}
void ads(ll x, ll k, ll d){
	for (int i = x; i <= 1e6; i += lowbit(i)) sum[i][k] += d;
}
ll ass(ll x, ll k){
	ll ans = 0;
	for (int i = x; i >= 1; i -= lowbit(i)) ans += sum[i][k];
	return ans;
}
void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);
}
int main(){
	for (int i = 1; i <= n; i++){
		a[i] = rd();
		for (int j = 0; j <= 20; j++){
			if ((a[i] >> j) & 1) t[i] = j;
			else ads(a[i], j, 1);
		}
		add(a[i], t[i], 1);
	}
	for (int i = 1; i <= n; i++) for (int j = 0; j <= 20; j++) if (!((a[i] >> j) & 1))
		ans += ask(a[i] - 1, j);
	for (;T--;){
		x = rd(), y = rd();
		//删 
		for (int j = 0; j <= 20; j++) if (!((a[x] >> j) & 1))
			ans -= ask(a[x] - 1, j);
		ans -= ass(1e6, t[x]) - ass(a[x], t[x]);
		add(a[x], t[x], -1);
		for (int j = 0; j <= 20; j++) if (!((a[x] >> j) & 1))
			ads(a[x], j, -1);
//		cout << ans << "\n";
		a[x] = y;
		//加 
		for (int j = 0; j <= 20; j++) if ((a[x] >> j) & 1) t[x] = j;
		for (int j = 0; j <= 20; j++) if (!((a[x] >> j) & 1))
			ans += ask(a[x] - 1, j);
		ans += ass(1e6, t[x]) - ass(a[x], t[x]);
		add(a[x], t[x], 1);
		for (int j = 0; j <= 20; j++) if (!((a[x] >> j) & 1))
			ads(a[x], j, 1);
		printf ("%lld", ans), putchar('\n');
	}
	return 0;
}
```

## 彩蛋

赛后啃了官方题解跑的飞快，而我还在 $992$ 毫秒卡常。算了一下，最劣情况下大约 $2 \times 10^8$ 的，只能说出题人数据太强了。

这是我的 [AC 记录](https://www.luogu.com.cn/record/175513084) 和 [线段树 T 飞](https://www.luogu.com.cn/record/175510974)。我甚至之后发这份代码再交了几次，没有一次 AC 了，都是 $1.02$ 秒左右。

---

## 作者：可爱的小棉羊 (赞：1)

好的如你所见，这个二元组关系看起来很抽抽象，也是非常的奇怪。

好的我们思考：假如说 $x<y$ 他们时候满足关系那么他们满足什么条件呢？

我们思考 $x$ 和 $y$ 的最高位，要是 $y$ 的最高位和 $x$ 的那位上的 $1$ 异或成 $0$ 显然一定 $\max(x,y)>x \oplus y$。

然后条件就显然了小值的最高位的大值的这一位为 $0$。

开桶就可以了，~~加入树状数组后可以支持区间查询（？）~~。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005],n,q;
int A[25],B[25];
void add(int k,int val){
	int x=20;
	for(;x>=0;x--){
		if(k&(1<<x))break;
	}
	A[x]+=val;
	for(int j=x-1;j>=0;j--){
		if(!(k&(1<<j)))B[j]+=val;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		add(a[i],1);
	}
//	int ans=0;
//	for(int i=0;i<=20;i++){
//		ans+=1ll*A[i]*B[i];
//	}
//	cout<<ans<<"\n";
	while(q--){
		int x,y;
		cin>>x>>y;
		long long ans=0;
		add(a[x],-1);
		add(y,1);
		a[x]=y;
		for(int i=0;i<=20;i++){
			ans+=1ll*A[i]*B[i];
		}
		cout<<ans<<"\n";
	}
	
	return 0;
}
```

---

## 作者：wzhm54nr (赞：0)

# 一些约定
以下，称一个数的第 $i$ 位为二进制下，从低位往高位。最低位是第 $0$ 位。
# 观察
为了方便研究，令在 $a\oplus b > \max\{a,b\}$ 中，$a>b$。

于是，问题就转化为了：一个数异或另一个数，何时大于本身。异或不能产生进位，所以我们只考虑答案对于 $a$ 发生变化的最高的位。如果 $b$ 有 $i$ 位，我们显然只需要考虑 $a$ 的第 $i$ 位。为什么？请看异或值表。

||0|1|
|:-:|:-:|:-:|
|0|0|1|
|1|1|0|

> 任何值异或 $0$ 都等于它本身；  
> 任何值异或 $1$ 都等于对它本身取反。

所以，定义两个数组 $x$ 和 $y$，$x_i$ 表示有多少个数第 $i$ 位为 $0$，$y_i$ 表示有多少个数有 $i$ 位。修改时，清除原数产生的贡献，加入新数产生的贡献。显然，所求为 $\sum x_i\times y_i$。

有一个细节：这些结论均基于 $a>b$，所以 $a$ 应该只对满足 $i<\text{a 的位数}$ 的 $x_i$ 产生贡献，使得当 $b>a$ 时 $b$ 无法“享受”此贡献，也就不会对答案进行错误的累加。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,M=32;
int n,q,a[N],x[M],y[M];
void modify(int t,int add){
	int cnt=0;
	while(t){
		if(!(t&1))  x[cnt]+=add;
		++cnt;t>>=1;
	}
	y[cnt-1]+=add;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		modify(a[i],1);
	}
	while(q--){
		int u,v;scanf("%d%d",&u,&v);
		modify(a[u],-1);modify(v,1);
		a[u]=v;
		long long ans=0;
		for(int i=0;i<M;i++)  ans+=1ll*x[i]*y[i];
		printf("%lld\n",ans);
	}
}
```

---

## 作者：_zuoqingyuan (赞：0)

赛时猜出了主要结论，但仍然不会做，简直菜到家了。

# 思路分析

我们思考合法二元组 $(a_i,a_j)$ 的性质，为了方便，不妨假设 $a_i < a_j$。

首先思考，如何比较两个二进制数的大小？正确的做法是先比较最高位高低，如果最高位相同，则从最高位到最低位逐位比较，直到出现某一位两个数不一样。这种思想会为我们带来启发。

假如将 $a_j$ 异或上 $a_i$ 后为 $x$。根据贪心的思想，如果想比较 $x,a_j$ 的大小，我们**只需要关注不同的最高一位**，如果这一位是从 $1$ 变 $0$，其之后不管如何变化，始终满足 $x<a_j$，相反，如果是从 $0$ 变为 $1$，则一定满足 $x>a_j$。

如果 $(a_i,a_j)$ 是合法二元组，则一定是上面所述的第二种变化。因为 $a_i$ 在二进制下某一位为 $0$ 不会发生变化，且要关注不同的最高一位，所以我们重点研究 $a_i$ 的最高位。假设这一位是 $h$ 位。

- 如果 $a_j$ 的 $h$ 位为 $1$：则变化后 $a_j$ 的 $h$ 位从 $1$ 变 $0$。

- 如果 $a_j$ 的 $h$ 位为 $0$：则变化后 $a_j$ 的 $h$ 位从 $0$ 变 $1$。

**结论**：如果 $(a_i,a_j)$ 满足 $a_i$ 的最高位在 $a_j$ 中为 $0$，则 $(a_i,a_j)$ 是合法二元组。

理论部分讲解完毕，那么如何做这个题呢？

首先，限制 $i<j$ 而不限制 $a_i<a_j$ 的合法二元组个数同限制 $a_i<a_j$ 而不限制 $i<j$ 的合法二元组个数一样。

假设有 $t_i$ 个数最高位为 $i$ 位，有 $p_i$ 个数第 $i$ 位 $0$ 且最高位大于第 $i$ 位。显然，这 $t_i$ 个数和 $p_i$ 个数没有重复，且 $p_i$ 个数都比 $t_i$ 个数大，根据结论。$t_i,p_i$ 个数中任意选出两个都满足其实合法二元组，则他对答案的贡献为 $t_i\times p_i$。

预处理出 $t_i$ 和 $p_i$，每次修改把桶修改一下，计算答案时直接统计 $\sum t_i\times p_i$ 即可。时间复杂度 $O(n\log n)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N=1e6+10;
int n,q,a[N],x,y;
ll t[21],p[21];
void add(int x,int s){
    int hbt=0;
    for(int i=0;i<=21;i++){
        if(!(x>>i)){
            hbt=i;break;
        }
    }
    t[hbt-1]+=1ll*s;
    for(int i=0;i<hbt;i++){
        if(!((x>>i)&1)){
            p[i]+=1ll*s;
        }
    }
    return;
}
ll ask(){
    ll cnt=0;
    for(int i=0;i<=21;i++){
        cnt+=1ll*t[i]*p[i];
    }
    return cnt;
}
int main(){
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        add(a[i],1);
    }
    while(q--){
        scanf("%d %d",&x,&y);
        add(a[x],-1),add(y,1),a[x]=y;
        printf("%lld\n",ask());
    }
}
```

如有错误，请指出。

---

## 作者：2012_Zhang_ (赞：0)

## 思路解析
众所周知异或是一种关于二进制的运算。\
异或使得一数的任意二进制数位增大的条件是：
 1. 该数位上的数是 0。
 2. 与它进行异或的数位上是 1。

进一步分析，经过异或使得一数增大的方法是，另一数的最高位对应该数相应的数位上的数是 0。\
用桶计算各个数对应位置的 0 的个数的总数，再遍历计算各个数可增大的方案数，累加后是初始值。\
对于每次询问，只需将删除的数的每个是 0 的数位对答案的贡献去掉，在计算新的数的贡献并加上，通过桶的优化后，总时间效率为 $O(n\log a_i+q \log a_i)$。\
这样的复杂度完全够用了，接下来是代码。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,x,y,s[1000005],f[1000005],sum;
long long s2[1000005],f2[1000005],flag[1000005][20];//桶优化
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>x;
        int j=1;
        while(x>0){
            if(x%2==0)f[i]=j,flag[i][j]=1,s2[j]++;
            x/=2;
            j++;
    	}//初始化
        s[j-1]++;
        f2[i]=j-1;
    }
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=f[i];j++){
    		if(flag[i][j]==1) sum+=s[j];//计算初始值
		}
	}
    for(int i=1;i<=q;i++){
        cin>>x>>y;
        for(int j=1;j<=f[x];j++){
        	if(flag[x][j]==1)
                sum-=s[j],flag[x][j]=0,s2[j]--;
		}
		sum-=s2[f2[x]];//删除当前数的贡献
		s[f2[x]]--;
		f[x]=0,f2[x]=0;
		int j=1;
        while(y>0){
            if(y%2==0)f[x]=j,flag[x][j]=1,s2[j]++;
            y/=2;
            j++;
    	}
        s[j-1]++;
        f2[x]=j-1;
		for(int j=1;j<=f[x];j++){
			if(flag[x][j]==1) sum+=s[j];
		}
		sum+=s2[f2[x]];//加上新增数的贡献
        cout<<sum<<endl;
    }
    return 0;
}

---

## 作者：Nazq (赞：0)

我考场上的想法 Trie。

判断合法二元组 $(a, b), a \gt b$：
1. $a$ 最高位的 $1$，$b$ 为 $0$。（不然异或会变小）
2. 存在位置 $pos$，使得大于 $pos$ 的位置，$b$ 全为 $0$；在 $pos$ 这位，$a$ 为 $0$，$b$ 为 $1$；$pos$ 以下的位就不管了。

查询以 $c$ 为二元组较大值的数量。
先找到 $c$ 最高位的 $1$，然后往 $0$ 走（$1$）。
接下来如果 $c$ 存在某位是 $0$，就累加 $1$ 这棵树的数量。
一直往 $0$ 走（$2$）。

查询以 $c$ 为二元组较小值的数量。
如果 $c$ 这 $i$ 位为 $1$，累加 $pos = i$ 的答案，即当前枚举的 $a$ 的前缀 $k$ 的数量，由于枚举的 $k$ 存在 $1$，所以这要求 $k \gt val$。

初始时，$ans$ 为所有数的较大（较小）查询之和。
每次修改，只需要修改这个数的两种查询。

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
struct Trie {
    int son[2], sum;
    int& operator [] (const int& i) { return son[i]; }
} t[N << 1];
int n, q, a[N], cnt;
ll ans;
void Insert(const int& val, const int& k) {
    int cur = 0;
    for(int i = 19, c; ~i; --i) {
        c = val >> i & 1;
        if(!t[cur][c])t[cur][c] = ++cnt;
        cur = t[cur][c];
        t[cur].sum += k;
    }
}
ll query_max(const int& val) {
    int i = 19, cur = 0, ans = 0, c = val >> i & 1;
    // 找最高位的 1
    while(~i && !c) {
        if(!t[cur][c])return 0;
        cur = t[cur][c];
        --i;
        if(~i)c = val >> i & 1;
    }
    //较小数在 val 最高位的 1 是 0，先把 0 走了
    if(~i) {
        if(!t[cur][0])return 0;
        cur = t[cur][0], --i;
    }
    for(; ~i; --i) {
        c = val >> i & 1;
        // pos = i 的情况
        if(!c && t[cur][1])ans += t[t[cur][1]].sum;
        if(!t[cur][0])return ans;
        cur = t[cur][0];
    }
    return ans;
}
ll query_min(int cnt, int cur, int val, int k) {
    if(!~cnt)return 0;
    //走到最高位的 1，累加答案
    if(val >> cnt & 1)return k > val ? t[t[cur][0]].sum : 0;
    else {
        ll res = 0;
        if(t[cur][0])res += query_min(cnt - 1, t[cur][0], val, k);
        if(t[cur][1])res += query_min(cnt - 1, t[cur][1], val, k | 1 << cnt);
        return res;
    }
}
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        Insert(a[i], 1);
    }
    for(int i = 1; i <= n; ++i)
        ans += query_max(a[i]);
    while(q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if(a[x] != y) {
            ans -= query_max(a[x]) + query_min(19, 0, a[x], 0);
            Insert(a[x], -1);
            ans += query_max(y) + query_min(19, 0, y, 0);
            Insert(y, 1);
            a[x] = y;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

```

---

## 作者：iyka (赞：0)

题面十分清晰，所以关于题目大意在此就不再赘述。

题目中给出的合法二元组中是要两数异或的结果严格大于两数中最大的一数（不会异或的请到 [这里](http://oi-wiki.com/math/bit/#%E4%B8%8E%E6%88%96%E5%BC%82%E6%88%96) 来看看），所以我们就有以下结论：如果 $(x,y)(x<y)$ 是一个合法二元组，设 $x$ 的最高位的位数为 $u$，则有 $y$ 的第 $u$ 位为零。

证明也非常简单，如果 $y$ 的第 $u$ 位不为零，在异或的过程中 $y$ 的第 $u$ 位将会变成零，得到的数就一定会比 $y$ 小，就无法得到一个合法二元组。

程序实现也十分简单，这里我们用两个桶来存储，$on$ 和 $tp$，$on$ 存储在这个数位上有几个数是零，$tp$ 存储在这个数位上有几个数是最高位，又因为 $\log_2{10^6}\approx 19$，所以最后的答案就是 $\sum_{k=0}^{20} on[k]\times tp[k]$。

不开 long long 见祖宗！！！

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10,M=20;
int n,q,a[N],on[M],tp[M],ans;
void putin(int u)
{
	bool f=0; 
	for(int i=M;i>=0;--i)
	{
		if(u&(1<<i) && !f)
			on[i]++, f=1;
		else if(!(u&(1<<i)) && f)
			tp[i]++;
	}
}
void kick(int u)
{
	bool f=0; 
	for(int i=M;i>=0;--i)
	{
		if(u&(1<<i) && !f)
			on[i]--, f=1;
		else if(!(u&(1<<i)) && f)
			tp[i]--;
	}
}
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>a[i], putin(a[i]);
	for(int i=1,x,y;i<=q;++i,ans=0)
	{
		cin>>x>>y;
		kick(a[x]);
		putin(y), a[x]=y;
		for(int j=0;j<=M;++j)
			ans+=on[j]*tp[j];
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：DFM_O (赞：0)

## [P11016 题目](https://www.luogu.com.cn/problem/P11016)

### 解题思路
首先我们容易得知若想使得 $a_i\oplus a_j>\max(a_i,a_j)$，则将两数写成二进制后其中必须要有一位满足两个数中一个为 $0$，一个为 $1$，且在这一位之前不存在任意一位两个数均为 $1$。

总结后就是：$a\oplus b>\max(a,b)(a\le b)$ 当且仅当 $a$ 写成二进制后，最高位的这一位在 $b$ 中为 $0$。

由于有修改操作，所以需先计算出操作之前有多少个合法二元组，并在每次操作进行修改。

用两个桶实现即可。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000001],zg[1000001],s[31],s1[31];
signed main()
{
	ios::sync_with_stdio(false);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		int t=a[i],j=30;
		while(j>=0)
		{
			bool w=t&(1<<j);
			if(w==1)
			{
				s[j]++,zg[i]=j;
				break;
			}
			j--;
		}
		j=0;
		while(t)
		{
			if(t%2==0)
				s1[j]++;
			t/=2,j++;
		}
	}
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		int t=a[i],j=30,pd=0;
		while(j>=0)
		{
			bool w=t&(1<<j);
			if(w==0)
			{
				if(pd==1)
					ss+=s[j];
			}
			else
			{
				if(pd==0)
					ss+=s1[j];
				pd=1;
			}
			j--;
		}
	}
	ss/=2;
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		int t=a[x],j=30,pd=0;
		while(j>=0)
		{
			bool w=t&(1<<j);
			if(w==0)
			{
				if(pd==1)
					ss-=s[j];
			}
			else
			{
				if(pd==0)
					ss-=s1[j];
				pd=1;
			}
			j--;
		}
		j=0;
		while(t)
		{
			if(t%2==0)
				s1[j]--;
			t/=2,j++;
		}
		a[x]=y,s[zg[x]]--;
		t=a[x],j=30;
		while(j>=0)
		{
			bool w=t&(1<<j);
			if(w==1)
			{
				s[j]++,zg[x]=j;
				break;
			}
			j--;
		}
		j=0;
		while(t)
		{
			if(t%2==0)
				s1[j]++;
			t/=2,j++;
		}
		t=a[x],j=30,pd=0;
		while(j>=0)
		{
			bool w=t&(1<<j);
			if(w==0)
			{
				if(pd==1)
					ss+=s[j];
			}
			else
			{
				if(pd==0)
					ss+=s1[j];
				pd=1;
			}
			j--;
		}
		cout<<ss<<"\n";
	}
	return 0;
}
```

---

