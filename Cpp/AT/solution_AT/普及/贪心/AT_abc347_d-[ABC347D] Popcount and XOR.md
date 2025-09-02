# [ABC347D] Popcount and XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_d

非負整数 $ a,b,C $ が与えられます。 次の $ 5 $ つの条件をすべて満たす非負整数の組 $ (X,Y) $ が存在するか判定し、存在するならひとつ出力してください。

- $ 0\leq\ X\lt2\ ^\ {60} $
- $ 0\leq\ Y\lt2\ ^\ {60} $
- $ \operatorname{popcount}(X)=a $
- $ \operatorname{popcount}(Y)=b $
- $ X\oplus\ Y=C $

ただし、$ \oplus $ はビットごとの排他的論理和を表します。

条件を満たす $ (X,Y) $ が複数存在する場合、どれを出力しても構いません。

popcount とは？非負整数 $ x $ について $ x $ の popcount とは、$ x $ を $ 2 $ 進法で表記したときの $ 1 $ の個数です。 より厳密には、非負整数 $ x $ について $ \displaystyle\ x=\sum\ _\ {i=0}\ ^\ \infty\ b\ _\ i2\ ^\ i\ (b\ _\ i\in\lbrace0,1\rbrace) $ が成り立っているとき $ \displaystyle\operatorname{popcount}(x)=\sum\ _\ {i=0}\ ^\ \infty\ b\ _\ i $ です。

例えば、$ 13 $ を $ 2 $ 進法で表記すると `1101` なので、 $ \operatorname{popcount}(13)=3 $ となります。 ビットごとの排他的論理和とは？非負整数 $ x,y $ について $ x,y $ のビットごとの排他的論理和 $ x\oplus\ y $ は以下のように定義されます。

- $ x\oplus\ y $ を $ 2 $ 進法で表記したときの $ 2\ ^\ k\ (k\geq0) $ の位は、$ x,y $ を $ 2 $ 進法で表記したときの $ 2\ ^\ k\ (k\geq0) $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $ 、そうでなければ $ 0 $ となる。

例えば、$ 9,3 $ を $ 2 $ 進法で表記するとそれぞれ `1001`, `0011` なので、$ 9\oplus3=10 $ となります（$ 10 $ を $ 2 $ 進法で表記すると `1010` です）。

## 说明/提示

### 制約

- $ 0\leq\ a\leq60 $
- $ 0\leq\ b\leq60 $
- $ 0\leq\ C\lt2\ ^\ {60} $
- 入力はすべて整数

### Sample Explanation 1

$ (X,Y)=(28,27) $ は条件を満たします。 $ X,Y $ を $ 2 $ 進法で表記するとそれぞれ `11100` と `11011` になります。 - $ X $ を $ 2 $ 進法で表記すると `11100` になるので、$ \operatorname{popcount}(X)=3 $ です。 - $ Y $ を $ 2 $ 進法で表記すると `11011` になるので、$ \operatorname{popcount}(Y)=4 $ です。 - $ X\oplus\ Y $ を $ 2 $ 進法で表記すると `00111` となり、$ X\oplus\ Y=7 $ です。 条件を満たす非負整数の組が複数存在する場合どれを出力しても構わないため、例えば `42 45` と出力しても正解になります。

### Sample Explanation 2

条件を満たす非負整数の組は存在しません。

### Sample Explanation 3

出力すべき値が $ 32\operatorname{bit} $ 整数に収まらない場合があります。

## 样例 #1

### 输入

```
3 4 7```

### 输出

```
28 27```

## 样例 #2

### 输入

```
34 56 998244353```

### 输出

```
-1```

## 样例 #3

### 输入

```
39 47 530423800524412070```

### 输出

```
540431255696862041 10008854347644927```

# 题解

## 作者：wangbinfeng (赞：4)

[![](https://img.shields.io/badge/题目-AT__abc347__d_[ABC347D]_Popcount_and_XOR-green)
![](https://img.shields.io/badge/难度-暂无评定（普及/提高−）-yellow)
![](https://img.shields.io/badge/考点-二进制-blue)
![](https://img.shields.io/badge/题型-传统题（SPJ）-red)](https://www.luogu.com.cn/problem/AT_abc347_d)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009) 

-----------
题意：已知 $X$ 和 $Y$ 在二进制下的 $1$ 的个数分别为 $a,b$，求满足 $X\oplus Y=C$ 的任意 $X,Y$。

可以发现，对于 $X$ 和 $Y$ 的二进制每一位，若均为 $0$ 或 $1$ 则 $C$ 的该位一定为 $0$，若一个为 $0$，另一个为 $1$ 则 $C$ 该位一定是 $1$。

可以想到，用 $\operatorname{popcount}(c)$ 个 $1$ 分摊（不一定平均）给 $A$ 和 $B$，再把多余的 $1$ 给 $A$ 和 $B$ 两两抵消掉即可。

下面作为易错点讲一下如何判断无解：
1. $a+b<\operatorname{popcount}(c)$：$X,Y$ 在二进制下没有足够的 $1$ 来凑出 $C$，显然无解。
2. $\operatorname{popcount}(c)-a-b \equiv 1\left(\bmod 2\right)$：在二进制下多余的 $1$ 两两抵消时，一个 $1$ 无法抵消，显然无解。
3. $\frac{a+b-\operatorname{popcount}(c)}{2}>(60-\operatorname{popcount}(c))$：在二进制下的 $1$ 过多，使 $A,B$ 为了满足条件超过了 $60$ 位，故无解。
4. $\left|a-b\right|>\operatorname{popcount}(c)$：在二进制下一边 $1$ 过多，一边 $1$ 过少，无法完全抵消，故无解。

可以发现，其他条件全部有解。

------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int popcnt(long long x){
	int ret=0;
	for(;x;x&=x-1)ret++;
	return ret;
}
long long a,b,c;
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>a>>b>>c;
	if(a+b<popcnt(c)||(a+b-popcnt(c))%2){printf("-1");return 0;}
	if((a+b-popcnt(c))/2>(60-popcnt(c))){printf("-1");return 0;}
	if((a-b>popcnt(c)||b-a>popcnt(c))){printf("-1");return 0;}
	bitset<60>d(c);//转成二进制 
	bitset<60>e,f;
	e.reset(),f.reset();
	for(int i=0;i<60;i++)cerr<<d[i];
	cerr<<endl;
	for(int i=0;i<60;i++){//抵消掉多余的 1
		if(a+b==popcnt(c))break;
		if(d[i]==false)e[i]=f[i]=true,a--,b--;
	}
	for(int i=0;i<60;i++){//将剩下的 1 分摊给 X,Y
		if(d[i]&&a-->0)
			e[i]=true;
		else{if(d[i]&&b-->0)
			f[i]=true;}
	}
	for(int i=0;i<60;i++)cerr<<e[i];
	cerr<<endl;
	for(int i=0;i<60;i++)cerr<<f[i];
	cerr<<endl;				//所有 cerr 仅在本地测试使用。正式提交应当删除（这里保留仅仅为了帮助读者测试）
	cout<<e.to_ullong()<<' '<<f.to_ullong();//用 bitset 自带的二进制转十进制函数输出结果
}
```

---

## 作者：zengziqvan (赞：4)

# 题目大意

给定 $a,b,C$。

构造两个不超过 $2^{60}$ 的数 $A,B$，使：

- $A \oplus B=C$

- $A$ 的二进制表示上有 $a$ 位是 $1$。

- $B$ 的二进制表示上有 $b$ 位是 $1$。

# 题目分析

本题比较考虑思维含量。

考虑异或运算的性质：不同才为 $1$。

因此，我们直接扫描 $C$ 在二进制上的每一位。对于第 $k$ 位：

- 如果这一位是 $1$，则可以让 $A$ 和 $B$ 的其中一个变为 $1$，另一个变为 $0$。

- 如果这一位是 $0$，则表示 $A$ 与 $B$ 这一位必须相同。

为了满足题目条件，我们要利用 $C$ 中的 $1$，使 $a$ 与 $b$ 趋近相等。

这样 $A,B$ 剩下未分配的 $1$ 都可以通过 $C$ 剩下的 $0$ 来补充。

综上我们采取以下一种策略：

- 若第 $k$ 位是 $1$，考虑 $A$ 与 $B$ 剩余未分配的 $1$ 哪个多，借此决定当前的 $1$ 应该分配给谁。

- $1$ 分配完毕后如果 $a$ 与 $b$ 不相等则无解。

- 如果剩余的 $0$ 不足以补充完 $a$ 也无解。

- 否则将构造的各位逐位相加即可。

时间复杂度 $\operatorname{O} (\log C)$。

```c++
//禁止抄袭！！！
#include <bits/stdc++.h>
using namespace std;
int a,b,in[70],tot,cnt1,A[70],B[70],tot1,tot2,c;
main() {
	cin>>a>>b>>c;
	ROF(i,60,0) in[++tot]=((c>>i)&1);
	reverse(in+1,in+tot+1); 
	FOR(i,1,tot) {
		if(in[i]) {
			if(a<=b) {
				B[i]=1;
				b--;
			} else {
				A[i]=1;
				a--;
			}
		} 
	}
	if(a!=b) {
		puts("-1");
		return 0;
	}
	FOR(i,1,tot) {
		if(a&&!in[i]) {
			A[i]=1;
			B[i]=1;
			a--;
			b--;
		} 
	}
	if(a) {
   	  puts("-1");
		return 0;
	}
	FOR(i,1,tot) res1+=(ll)(A[i]<<(i-1));
	FOR(i,1,tot) res2+=(ll)(B[i]<<(i-1));
	cout<<res1<<" "<<res2<<"\n";
	return 0;
}
```

---

## 作者：StormWhip (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc347_d)


## 题目大意
给你非负整数 $a$，$b$ 和 $C$。请判断是否有一对非负整数 $(X, Y)$ 满足以下五个条件。如果存在，请输出一组。

- $0 \le X \le 2^{60}$
- $0 \le Y \le 2^{60}$
- $\operatorname{popcount}(X) = a$
- $\operatorname{popcount}(Y) = b$
- $X \oplus Y = C$

这里，$\oplus$ 表示按位 XOR。

如果多对 $(X, Y)$ 满足条件，则可以输出其中任意一对。

其中 $\operatorname {popcount}$ 表示该数在二进制中 $1$ 的个数，
例如，$13$ 的二进制表示为 $1101$，则 $\operatorname{popcount}(13)=3$。

对于非负整数 $x,y$，$x \oplus y$ 的定义如下。

- 如果 $x$ 和 $y$ 的二进制表示中 $2^k$ 的位置 $\\ (k\geq0)$ 中正好有一个是 $1$，则 $x \oplus y$  是 $1$，否则是 $0$。

例如，$9$ 和 $3$ 的二进制表示分别为 $1001$ 和 $0011$，因此 $9 \oplus 3 = 10$ （二进制表示为 $1010$）。

## 思路
&emsp;&emsp;将 $C$ 分解为二进制，若其第 $i$ 位为 $1$，则将 $x$ 和 $y$ 二进制的第 $i$ 位分别填充为 $1$ 和 $0$（考虑当前 $x$ 和 $y$ 还需要填充多少个 $1$ ，更多的优先）。填充后若 $x$ 和 $y$ 还需填充的 $1$ 的数量不为 $0$，则将 $x$ 和 $y$ 二进制中都为 $0$ 的一位填充为 $1$，直至填充完毕。

## 代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=65;
unsigned long long x[N],y[N],t[N],c;
int a,b,now_2=60;
unsigned long long Pows(unsigned long long base,int p)
{
	if(p==1) return base;
	if(p==0) return 1;
	unsigned long long cnt=Pows(base,p/2),ans=cnt*cnt;
	if(p%2==1) ans=ans*base;
	return ans;
}//快速幂  
void Print()
{
	unsigned long long ansx=0,ansy=0;
	for(int j=0;j<60;j++)
		ansx+=x[j]*Pows(2,j);
	for(int j=0;j<60;j++)
		ansy+=y[j]*Pows(2,j);
	cout<<ansx<<" "<<ansy<<"\n";
	exit(0);
}//将x数组和y数组中储存的二进制转换为十进制并输出  
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b>>c;
	//将c转换为二进制，存储在t数组中  
	while(c!=0)
	{		
		if(c>=Pows(2,now_2))
		{
			t[now_2]=1;
			c-=Pows(2,now_2);					
		}
		now_2--;
	}
	//若c在二进制中的第i位为1，那么x和y在二进制中的第i位必将一个是1、一个是0，按照此时x和y二进制中还需"1"的数量进行填充 
	for(int i=0;i<60;i++)
		if(t[i])
		{
			if(a>b) x[i]=1,y[i]=0,a--;
			else x[i]=0,y[i]=1,b--;
		}
	if(a==0&&b==0) Print();//如果x和y二进制中1的数量已经足够，则直接输出  
	for(int i=0;i<60;i++)
		if(x[i]==0&&y[i]==0)//如果x和y二进制中的第i位都是0，则都将其填充为1，在不影响xor的结果的前提下填充完剩余的"1" 
		{
			a--;
			b--;
			x[i]=1;
			y[i]=1;
			if(a==0&&b==0) Print();//填充完了则直接输出  
		}
	cout<<"-1\n";//填充不完则输出-1  
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：2)

好题啊好题。首先如果抛去 $\operatorname{popcount}$ 这个条件不看的话，方案很好构造，让 $x = c, y = 0$ 即可。

加上 $\operatorname{popcount}$ 这个条件之后，考虑对 $x, y$ 进行相应的调整，使其满足条件。

有两种调整方案，使得 $x \oplus y$ 的值不改变。

- 将 $x$ 的某一位从 $1$ 变成 $0$，$y$ 的某一位从 $0$ 变成 $1$。异或值从原本的 $1 \oplus 0 = 1$ 变为 $0 \oplus 1 = 1$。

- 将 $x$ 的某一位从 $0$ 变成 $1$，$y$ 的某一位从 $0$ 变成 $1$。异或值从原本的 $0 \oplus 0 = 0$ 变为 $1 \oplus 1 = 0$。

假设对于第一种操作执行了 $k$ 次，第二种调整执行了 $b - k$ 次，这样可以满足 $y$ 中有恰好 $b$ 个 $1$。为了保证 $x$ 中有 $a$ 个 $1$，还有另外的约束条件。

不妨让 $c$ 中含有 $s$ 个 $1$，$60 - s$ 个 $0$。那么有：

$$s - k + b - k = a$$

移项可以得到关于 $k$ 的表达式：

$$k = \dfrac{s + b - a}{2}$$

判断 $s$ 与 $k$ 的大小以及 $b - k$ 与 $60 - s$ 的大小来判断能否调整。如果能够调整，就从低位到高位贪心调整即可。

最后需要判断调整后是否是正确的。代码就不贴了，大家应该都会。

---

## 作者：ykzzldz (赞：1)

这题说实话想法不难，可能代码难度稍微高一些，主要涉及进制转换。

在 $c_i$ 为 $1$ 时（这里 $c_i$ 指的是数字 $c$ 转为二进制后第 $i$ 位上的值），将二进制中 $1$ 较多的那一位赋成 $1$，另一个赋成 $0$。$c_i$ 为 $0$ 时，则打上标记，在最后的时候在判断 $1$ 是否足够，不够的话就赋成 $1$，否则赋为 $0$。最后，要注意一个细节，$x,y<2^{60}$，所以当你求出答案时一定要判断答案是否超过上界。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100],b[100],c[100],x,t,k,d,jsq;
void num(int x){
	while(x){
		if(x&1)c[++t]=1;
		else c[++t]=0;
		x>>=1;
	}
}
signed main(){
	cin>>k>>d>>x;
	num(x);//这里先将c转为二进制
	for(int i=t;i>=1;i--){
		if(k==0&&d==0){
			if(c[i]==1){
				cout<<-1;
				return 0;
			}
			else{
				a[i]=b[i]=0;
			}
		}
		else if(c[i]==0){
			jsq++;
			a[i]=b[i]=2;
		}
		else if(k>=d){
			a[i]=1;
			b[i]=0;
			k--;
		}
		else{
			a[i]=0;
			b[i]=1;
			d--;
		}
	}
	if(k!=d){
		cout<<-1;
		return 0;
	}
	for(int i=t;i>=1;i--){
		if(a[i]==2){
			if(d>0){
				a[i]=b[i]=1;
				d--;
			}
			else{
				a[i]=b[i]=0;
			}
		}
	}
	if(d!=0){
		for(int i=t+1;i<=t+d;i++){
			a[i]=1;
			b[i]=1;
		}
		t=t+d;
	}
	if(t>60){
		cout<<-1;
		return 0;
	}
	int ans1=0,ans2=0,w=1;
	for(int i=1;i<=t;i++){//将二进制转化为十进制
		ans1+=w*a[i];
		ans2+=w*b[i];
		w*=2;
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：Vocaloid世末歌者 (赞：1)

纯脑掺题目。

最开始的思路很飞舞我就不写了。

首先先是 `-1` 的情况（$c$ 是 $C$ 的 $popcount$）：

- $a+b+c\equiv 1\pmod 2$
- $a+b+c\gt 120$
- $a\gt b+c,b\gt c+a,c\gt a+b$.

第一个很容易想到。

第二个是因为题中 $X,Y$ 的上限限制。

第三个是因为很明显搞不了。

后面的构造：

为方便，让 $n_{i,j}$ 代表满足 $X$ 和 $Y$ 的二进制表示的第 $k$ 位分别是 $i$ 和 $j$ 的 $k$ 的个数。

设 $S_0$ 是由 $n_{0,0}$ 个 $(0,0)$ 和 $n_{1,1}$ 个 $(1,1)$ 组成的序列，$S_1$ 是由 $n_{0,1}$ 个 $(0,1)$ 和 $n_{1,0}$ 个 $(1,0)$ 组成的序列。（$(i,j)$ 表示 $X$ 这位选 $i$，$Y$ 这位选 $j$）

对于二进制下 $C$ 的每一位，设 $p$ 为这位的数字。（位**从后向前**进行递减）

首先，删掉 $S_p$ 的最后一个二元组，代表它被使用过了。

设 $(x,y)$ 为刚刚删掉的元素，并将 $X$ 和 $Y$ 的这位分别设为 $x$ 和 $y$。

然后，我们根据以上定义以及题目，发现：

- $popcount(X)=a\iff n_{1,0}+n_{1,1}=a$
- $popcount(Y)=b\iff n_{0,1}+n_{1,1}=b$
- $X\oplus Y=C\implies n_{1,0}+n_{0,1}=popcount(C)$

又因为 $\sum n_{i,j}=60$（总方案数就是整体），于是我们可以推出：

$$
n_{0,0}=60-\frac{a+b+c}{2}
$$

$$
n_{0,1}=\frac{-a+b+c}{2}
$$

$$
n_{1,0}=\frac{a-b+c}{2}
$$

$$
n_{1,1}=\frac{a+b-c}{2}
$$

没了。

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 __int128
#define lowbit(x) ((x)&(-(x)))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
void read(i128 &x)
{
	i128 f=1;
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
void writing(i128 x)
{
	if(x>=10)writing(x/10);
	putchar(x%10+'0');
}
void write(i128 x)
{
	if(x<0)
	{
		cout<<'-';
		x=-x;
	}
	writing(x);
}
LL a,b,C,c;
LL popcount(LL x)
{
	LL sum=0;
	while(x)
	{
		if(x&1)sum++;
		x/=2;
	}
	return sum;
}
int main()
{
	cin>>a>>b>>C;
	c=popcount(C);
	if((a+b+c)%2!=0||a+b+c>120||a>b+c||b>c+a||c>a+b)
	{
		cout<<-1<<endl;
		return 0;
	}
	LL n00=60-(a+b+c)/2;
	LL n01=(-a+b+c)/2;
	LL n10=(a-b+c)/2;
	LL n11=(a+b-c)/2;
	LL bx,by,nb;
	bx=by=0;
	nb=60;
	while(nb--)
	{
		bx*=2;
		by*=2;
		if(1&(C>>nb))
		{
			if(n10)
			{
				bx++;
				n10--;
			}
			else
			{
				by++;
				n01--;
			}
		}
		else
		{
			if(n00)
			{
				n00--;
			}
			else
			{
				bx++;
				by++;
				n11--;
			}
		}
	}
	cout<<bx<<' '<<by<<endl;
	return 0;
}
```

---

## 作者：ilibilib (赞：0)

# [ABC347D] Popcount and XOR

## 题目大意（机翻）：

给定非负整数 $a,b,C$。判断是否存在一对非负整数 $(X,Y)$ 满足以下五个条件，并输出一组满足条件的 $ (X,Y)$：

- $ 0\leq\ X\lt2^{60} $
- $ 0\leq\ Y\lt2^{60} $
- $ \operatorname{popcount}(X)=a $
- $ \operatorname{popcount}(Y)=b $
- $ X\oplus\ Y=C $

## 分析：

先将 $C$ 转化为二进制，那么对于每一位：

如果这一位是 $1$，那么 $X$ 和 $Y$ 二进制的这一位肯定是一个 $1$ 一个 $0$。

如果这一位是 $0$，那么 $X$ 和 $Y$ 二进制的这一位是两个 $1$ 或者 两个 $0$。

因为 $X$ 和 $Y$ 二进制中 $1$ 的总数肯定是可以确定的，即 $a+b$，再减去 $C$ 二进制中 $1$ 的个数，最后除以二，就可以得到有几位 $X$ 和 $Y$ 二进制都是 $1$。

最后把这些 $0$ 和 $1$ 分配到 $X$ 和 $Y$ 中即可。

以防万一，最后加个特判判断一下答案符不符合题目要求。

## code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000010
using namespace std;
signed main()
{
	int a,b,c,aa,bb;
	cin>>a>>b>>c;
	aa=a,bb=b;
	bitset<100>f=c;
	int x,y;x=f.count();
	y=a+b-x;
	if(y<0||y&1){cout<<-1;return 0;}
	y/=2;a-=y,b-=y;
	if(a<0||b<0){cout<<-1;return 0;}
	int r1=0,r2=0;
	for(int i=0;i<60;++i)
	{
		if(f[i]==0&&y>0) --y,r1+=(1ll<<i),r2+=(1ll<<i);
		if(f[i]==1)
		{
			if(a>0) --a,r1+=(1ll<<i);
			else if(b>0) --b,r2+=(1ll<<i);
		}
	}
	if(a||b){cout<<-1;return 0;}
	if(__builtin_popcountll(r1)!=aa||__builtin_popcountll(r2)!=bb||(r1^r2)!=c||r1>=(1ll<<60)||r2>=(1ll<<60)){cout<<-1;return 0;};
	cout<<r1<<' '<<r2<<'\n';
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 1.题目大意
有两个数 $x,y$，已知他们的二进制分别有 $a,b$ 个 $1$。又已知他们异或的结果为 $z$。求 $x,y$（满足条件就行）。
# 2.解题思路
设 $z$ 的二进制有 $t$ 个 $1$。

接着枚举 $i$，表示这 $t$ 个 $1$，第一个数分担 $i$ 个一，则第二个数分担 $t-i$ 个一。

容易发现，$a+b \ge t$。为什么会大于呢？因为两个数相同位置上有 $1$，异或就变成 $0$ 了。所以 $a-i = b-(t-i)$，就是合法的情况。 

我们不妨设 $z$ 的最低位 $i$ 个 $1$ 出自第一个数，后面 $t-i$ 个 $1$ 出自第二个数。

接着，找 $z$ 的二进制第 $i$ 位是 $0$ 的最低 $t-i$ 位，把 $x,y$ 的第 $i$ 位都变成 $1$。最后求十进制即可。
# 3.注意事项
就是**不开 long long 见祖宗！**
# 4.代码展示
```
//作者场切代码
#include<bits/stdc++.h>
using namespace std;
int a,b,t,d[70],e[70],f[70],k;//d,e表示x,y的二进制
long long c;
long long get(int a[]){//该函数是把二进制转成十进制的
    long long ans=0,t=1;
    for(int w=1;w<=60;w++,t*=2)ans+=a[w]*t;
    return ans;
}
int main(){
    scanf("%d%d%lld",&a,&b,&c);
    while(c)f[++k]=c%2,t+=c%2,c/=2;
    for(int w=0;w<=t;w++){
        int x=t-w;
        if(a-w!=b-x)continue;//满足条件的情况
        memset(d,0,sizeof(d)),memset(e,0,sizeof(e));//保险点嘛，说不定有两种情况呢。
        int o=1,p=0,cd=0,ce=0;//cd表示x 1的个数，ce表示y 1的个数，o是统计c二进制为1的位数的，p好像没啥用，删了吧
        for(int y=1;y<=k;y++)
            if(f[y])
                if(o<=w)o++,d[y]=1,cd++;//出自第一个数
                else o++,e[y]=1,ce++;//出自第二个数
        for(int y=1;y<=60;y++){
            if(ce==b&&cd==a)break;//满足条件就break
            if(!f[y]&&!d[y]&&!e[y])d[y]=e[y]=1,cd++,ce++;//两个都是1，异或才是0
        }
        if(cd==a&&ce==b){printf("%lld %lld",get(d),get(e));return 0;}
    }
    printf("-1");
    return 0;
}
```

---

## 作者：fuxiheng (赞：0)

### 题意
给你 $a$ 和 $b$ 和 $C$ 三个数，找出是否有两个数 $A$ 和 $B$ 满足条件 $A$ 的二进制中有 $a$ 个 $1$，$B$ 的二进制中有 $b$ 个 $1$，它们的异或和为 $C$。
### 分析
按数位考虑，先把 $C$ 的二进制每一位求出来，因为是异或，所以我们发现，为 $1$ 的位置可以为 $A$ 和 $B$ 其中一个提供一位 $1$，为 $0$ 的位置可以为两个都提供一个 $1$ 或者都不提供。所以我们先把 $1$ 分配好，剩余的不够的用 $0$ 补齐即可。具体实现看代码吧
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 105;
	int bi[MAXN];
	int main(){
		int a, b;
		long long c;
		scanf("%d%d%lld", &a, &b, &c);
		int now = 0, cnt = 0;
		while(c){
			bi[now] = c & 1;
			c >>= 1;
			if(bi[now]) cnt++;
			now++;
		}
		now--;
		if(cnt < abs(a - b) || cnt > a + b || (a + b - cnt) & 1){
			printf("-1");
			return 0;
		}
		int need_a = (a - b + cnt) / 2, need_b = (b - a + cnt) / 2;
		int now_need = a - need_a;
		bool flag = 1;
		long long A = 0, B = 0;
		for(int i = now;~i;i--){
			if(bi[i]){
				if(flag){
					if(need_a) {
						A |= (1ll << i);
						need_a--;
					}
					else{
						B |= (1ll << i);
						need_b--;
					}
					flag = 0;
				}
				else{
					if(need_b){
						B |= (1ll << i);
						need_b--;
					}
					else{
						A |= (1ll << i);
						need_a--;
					}
				}
			}
			else{
				if(now_need){
					A |= (1ll << i);
					B |= (1ll << i);
					now_need--; 
				}
			}
		}
		for(int i = now + 1;now_need && i < 60;i++){
			A |= (1ll << i);
			B |= (1ll << i);
			now_need--;
		}
		if(now_need || A > (1ll << 60) || B > (1ll << 60)) printf("-1");
		else printf("%lld %lld", A, B);
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

数学题。

根据 $C$ 的值，可以得出 $x$ 和 $y$ 有 $s1+s$ 个相同的数位和 $s2$ 个不同的数位。

$s1$ 是 $C$ 的二进制中 $0$ 的数量，$s2$ 是 $C$ 的二进制中 $1$ 的数量。

$x$ 和 $y$ 可以通过在开头放 $s$ 个 $1$ 的方式既不改变异或大小，又能凑到 $a$ 和 $b$。

然后按 $1$ 的个数列出方程,设 $x$ 的相同数位中有 $x'$ 个 $0$，不同数位中有 $y'$ 个 $0$。

$$
s1+s-x'+s2-y'=a
$$
$$
s1+s-x'+y'=b
$$
解这个不定方程即可。

注意要判断 $x$ 和 $y$ 是否 $<2^{60}$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,pos[20010],n,s1,s2,s,X[20010],Y[20010],cc;
signed main(){
	cin>>a>>b>>c;
	cc=c;
	while(c>0){
		pos[++n]=c&1;
		c>>=1;
		s1+=pos[n]==0,s2+=pos[n]==1;
	}
	if((s2+b-a)%2==1){
		cout<<-1;
		return 0;
	}
	int y=(s2+b-a)/2,x;
	int p=2*s1+s2-b-a;
	if(abs(p)%2==1){
		cout<<-1;
		return 0;
	}
	if(p>0)s=0,x=p/2;
	else x=0,s=(-p)/2;
	if(n+s>60){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(pos[i]==0){
			if(x)X[i]=0,x--;
			else X[i]=1;
			Y[i]=X[i];
		}
		else{
			if(y)X[i]=0,y--;
			else X[i]=1;
			Y[i]=X[i]^1;
		}
	}
	for(int i=1;i<=s;i++)n++,X[n]=Y[n]=1;
	int sx=0,sy=0;
	p=1;
	for(int i=1;i<=n;i++){
		sx+=X[i]*p,sy+=Y[i]*p;
		p*=2;
	}
	int ssx=sx,ssy=sy;
	while(ssx>0){
		a-=ssx&1;
		ssx>>=1;
	}
	while(ssy>0){
		b-=ssy&1;
		ssy>>=1;
	}
	if(n<=60&&a==0&&b==0&&(sx^sy)==cc)cout<<sx<<" "<<sy<<endl;
	else cout<<-1;
	return 0;
}
```

---

## 作者：aeaf (赞：0)

# 翻译
题目给出 $a$，$b$，$c$。求 $X$，$Y$ 使得二进制下 $X$ 中 $1$ 的个数等于 $a$，同理 $Y$ 也是一样，并且 $X$ 异或 $Y$ 等于 $c$。
## 思路
由于异或的特殊性质，我们不难想到，只需要去分配 $1$ 的个数，如果剩下偶数个 $1$，我们也可以两两配对，从而对结果没有任何影响。所以就变成了我们对 $a$,$b$ 中多出的 $1$ 去维护，当 $c$ 二进制下第 $i$ 位为 $1$ 时去加上 $2^i$，同时对 $a$ 或 $b$ 进行减减的操作，代表我们已经放下。最后别忘了统一加上剩下的 $1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int  long long
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int a,b,c;
	cin >> a >> b >> c;
	int res1=0,res2=0;
	for(int i=0;i<=60;i++){
		if((c>>i&1)==true){
			if(a<=b){
				b--;
				res2+=(1LL<<i);// 不然会爆！ 
			}else{
				a--;
				res1+=(1LL<<i);
			}
		}
	}
	if(a<0||b<0||a!=b){
		cout <<-1;
		return 0;
	}
	for(int i=0;i<=60;i++){
		if(a<=0||b<=0)break;
		if((c>>i&1)==false){
			a--;
			b--;
			res1+=(1LL<<i);
			res2+=(1LL<<i);
		}
	}
	//一定要注意最后还有没有落下数字没填，不然最后一个样例会WA 
	if(a||b){
		cout <<-1;
		return 0;
	}
	cout <<res1<<" "<<res2;
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 题意

找出 $x$ 和 $y$，使得 $x$ 在二进制下有 $a$ 个 $1$，$y$ 在二进制下有 $b$ 个 $1$，且 $x \oplus\ y = c$。若有解，输出一个解，否则输出 `-1`。

## 思路

很简单，先把 $c$ 转换成二进制，发现，某一位是 $1$ 时，可以把两个数中的某一个数的这一位赋值为 $1$。具体是哪一位呢？简单来说就是看谁更适合。如果这一位是 $0$，那要么两个数这一位都是 $1$，要么都是 $0$。

先把所有的为 $1$ 的位置用贪心处理好，再看剩下的为 $0$ 的位置，判断是否满足要求。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define debug(x) cout<<#x<<':'<<x<<endl
using namespace std;
const int N=70;
int A,B,C,a,b,c[N],top;
int s1[N],s2[N];
int ans1,ans2,num0;
signed main(){
	cin>>A>>B>>C;
	while(C){
		c[++top]=C%2;
		C/=2;
	}
	for(int i=1;i<=60;i++){
		if(c[i]==1){
			if(a<A&&b==B) {
				s1[i]=1;
				a++;
			}
			else if(a==A&&b<B) {
				s2[i]=1;
				b++;
			}
			else{
				if(A-a>B-b) {
					s1[i]=1;
					a++;
				}
				else {
					s2[i]=1;
					b++;
				}
			}
		}
		else num0++;
	}
	if(A-a==B-b&&A>=a&&A-a<=num0){
		int pw=1,x=A-a;
		for(int i=1;i<=60;i++){
			if(c[i]==0) {
				if(x){
					s1[i]=s2[i]=1;
					x--;
				}
			}
			ans1+=pw*s1[i];
			ans2+=pw*s2[i];
			pw*=2;
		}
		cout<<ans1<<' '<<ans2;
		return 0;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

设 $\operatorname{popcount}(C)$ 等于 $k$。

则表示这 $k$ 个位中，$A,B$ 只能有一个为一，其他的位 $A,B$ 相等。

容斥求一下 $\frac{a+b-k}{2}$ 是 $A,B$ 都为 $1$ 的位数个数。

按位枚举一下即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=998244353;
const int inf=0x3f3f3f3f;
int a,b,c,x,y;
signed main(){
	cin >>a>>b>>c;
	int t=c,res=0;
	while(t){
		res+=(t&1);
		t>>=1;
	}
	if((a+b-res)&1){
		cout <<-1;
		return 0;
	}
	int k=(a+b-res)/2,p=a-k,q=b-k;
	for(int i=0;i<60;i++){
		if(c&1){
			if(p)x+=(1ll<<i),p--;
			else if(q)y+=(1ll<<i),q--;
		}else{
			if(k){
				x+=(1ll<<i);
				y+=(1ll<<i);
				k--;
			}
		}
		c>>=1;
	}
	if(k||p||q)cout <<-1;
	else cout <<x<<" "<<y;
	return 0;
}
```

---

## 作者：haokee (赞：0)

## 题目大意

给定 $a,b$ 和 $C$，现在要你找到两个正整数 $x$ 和 $y$，使得 $x$ 的对应二进制数当中 $1$ 的个数为 $a$，$y$ 的对应二进制当中 $1$ 的个数为 $b$，以及 $x\oplus y=C$。

## 解法

首先，我们知道 $x\oplus 0=x$ 和 $x\oplus x=0$，然后考虑构造方案。不如先令 $x=C,y=0$，那么很显然 $x\oplus y=C$。接下来考虑如何满足条件一二，我们可以将 $x$ 的一些位置上面的 $1$ 移动到 $y$ 上面，这样子 $x\oplus y$ 仍等于 $C$。但是有可能位数不够用，这时候我们就需要找到一些 $x$ 和 $y$ 都等于 $0$ 的位置，然后把这个位置上面的数都改成 $1$，这样子 $x\oplus y$ 也是等于 $C$ 的。

为了让他们尽量匹配，在把 $x$ 的 $1$ 移到 $y$ 身上的时候，我们需要尽量的匀称，简单来说就是让 $a-\text{popcount(x)}$ 尽量接近 $b-\text{popcount}(y)$。

具体操作请看代码。

## 代码

```cpp
#include <iostream>
#include <bitset>

using namespace std;
using LL = unsigned long long;

const LL kMaxN = 2e5 + 5;

LL a, b, c;
bitset<60> x, y;

int main() {
  cin >> a >> b >> c;
  x = c;                                      // 先令 x = c
  LL cnt = 0, res = (x.count() + b - a) / 2;  // 计算需要移多少个
  for (LL i = 0; cnt < res && i < 60; i++) {  // 移动 res 次
    if (x[i]) {                               // 如果可以移
      x[i] = 0, y[i] = 1;                     // 移过去
      cnt++;                                  // 计数器累加
    }
  }
  cnt = 0, res = a - x.count();               // 清空并计算要填多少个 1
  for (LL i = 0; cnt < res && i < 60; i++) {  // 填 1
    if (!x[i] && !y[i]) {                     // 找空的地方填
      x[i] = y[i] = 1;                        // 填上去
      cnt++;                                  // 计数器累加
    }
  }
  if (x.count() != a || y.count() != b || (x.to_ullong() ^ y.to_ullong()) != c) {
    cout << "-1\n";
  } else {
    cout << x.to_ullong() << ' ' << y.to_ullong() << '\n';
  }
  return 0;
}
```

---

## 作者：lateworker (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc347_d)；[Atcoder](https://atcoder.jp/contests/abc347/tasks/abc347_d)。

题意简洁明了。做法嘛，直接贪心就结束了。

## 分析

考虑到最终的结果 $X$ 与 $Y$ 的异或和为定值 $C$，我们不难发现：

- 如果 $C_i=1$，那么只能将 $X_i$ 或 $Y_i$ 单独设为 $1$。（记为情况一）
- 反之 $C_i=0$，那么必须将 $X_i$ 或 $Y_i$ 同时设为 $0$ 或 $1$。（记为情况二）
- $C_i,X_i,Y_i$ 分别表示 $C,X,Y$ 二进制下，从高位起，第 $i$ 位的值，只能是 $0/1$。

可以发现，情况一中，我们对 $X_i/Y_i$ 的修改是强制性的，因此考虑优先处理。

情况二中，决策时要求 $X_i=Y_i$。为了更好地“凑”出答案，我们希望出现 $a-cntX=b-cntY$。因此处理情况一时应该按照 $a-cntX$ 和 $b-cntY$ 的大小进行贪心。

## 实现

**记得开 unsigned long long。**

**左移的时候要用 `1ull<<i` 而不是 `1<<i`。**

```cpp
#include <iostream>
using namespace std;
#define C_ const
#define int unsigned long long
C_ int N = 60;
int a, b, c;
signed main() {
	cin>>a>>b>>c;
	int x, y, cntx, cnty;
	x = y = cntx = cnty = 0;
	for(int i=0;i<N;++i) if(c>>i&1ull) {
		if(cntx <= a && cnty <= b) {
			if(a-cntx > b-cnty) x|=(1ull<<i), ++cntx;
			else y|=(1ull<<i), ++cnty;
		}
		else return !(cout<<"-1\n");
	}
	if(a-cntx!=b-cnty) return !(cout<<"-1\n");
	for(int i=0;i<N&&cntx<a&&cnty<b;++i) if(!(c>>i&1ull)) {
		x|=(1ull<<i), y|=(1ull<<i);
		++cntx, ++cnty;
	}
	// 这个判断是必须的，不然就会在最后一个点上 WA。
	if(cntx!=a||cnty!=b) cout<<"-1\n";  
	else cout<<x<<" "<<y<<"\n";
	return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc347_d)
## 思路
对于异或操作，我们会发现：  
*  当 $C$ 的二进制中某一位为 $1$ 时，$x$ 与 $y$ 这两个数的其中一个数的这一位必然为 $1$。
* 当这一位为 $0$ 时，$x$ 与 $y$ 的这一位要么都是 $0$ 要么都是 $1$。
## 做法
先命 $c$ 为 $C$ 中 $1$ 的数量。  
假设 $x$ 与 $y$ 的位置中有 $i$ 个位置都为 $1$。  
则 $(a - i) + (b - i) = c$，  
解得 $2i = a + b - c$。  
这样我们就得出了有多少个 $C$ 中为 $0$ 的位置在 $x$ 与 $y$ 中为 $1$。  
然后就是判断是否合法了，只要符合以下任意一点就不合法：
* $a + b + c > 120$ 总位数和也只有 $120$。
* $a + b + c \equiv 1 \pmod2$ 不符合我们上文推的式子。
* $a + b < c$ 或者 $b + c < a$ 或者 $c + a < b$ 根据上文的式子也能想出来一点?
最后只要一个一个填数就行了，具体看代码。
## AC Code
```cpp
#include<bits/stdc++.h>
#define sz(x) x.size()
#define szo(a) sizeof(a)
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef int I;
I x,y,t,a[70],len;//x中1的个数，y中1的个数，c中1的个数 
LL c;
I main(){
	scanf("%d%d%lld",&x,&y,&c);
	LL tmp = c;
	while(tmp){
		a[++len] = tmp % 2;
		if(a[len]) t++;
		tmp >>= 1; 
	}
	//假设有i个位置同样是1。(x - i) + (y - i) = t
	I z = (x + y - t) / 2;
	if(((x + y + t) % 2)||x + y < t||y + t < x||t + x < y||(x + y + t) > 120){
		printf("-1\n");
		return 0;
	}
	LL ans1 = 0,ans2 = 0,f = 1;
	x -= z,y -= z;
	for(I i = 1;i <= 61;i++){//填数字 
		if(a[i]){
			if(!x)
				y--,ans2 += f;
			else
				x--,ans1 += f;
		}else
			if(z)
				z--,ans1 += f,ans2 += f;	
		f *= 2;
	}
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}
```

---

## 作者：CEFqwq (赞：0)

复杂的分类讨论题~~但是我吃的罚时比 C 少~~。

首先我们把 `C` 转二进制并求出 $1$ 的个数，记为 $pc$。

然后有三种情况是 `-1`：

1. $pc > a + b$（$1$ 的数量不够，没法凑成 $C$）。

2. $\max\{a, b\} - \min \{a,b\} > pc$（$1$ 太多了，没法凑成 $C$）。

3. $(a+b) \bmod 2 \not= pc \bmod 2$。

$1$ 和 $2$ 都很好理解，$3$ 为什么无解？别急，看完下面的讲解，你自然就懂了。

### $C$ 数是怎样异或的

首先，我们假设 $a+b = pc$，这样很简单，把 $C$ 二进制 $1$ 的个数 $pc$ 拆成 $a+b$，前 $a$ 个 $1$ 对应 $X$ 中的 $1$，后 $b$ 个 $1$ 对应 $Y$ 中的 $1$，这样就没事了。

但是事实是，$C$ 数很可能不这么和谐，这会导致大多数情况下，$a+b > pc$，这个时候我们就要用到异或的性质了。

我们知道，$a \oplus a = 0$。特殊的，有 $2^k \oplus 2^k = 0$，也就是说，$X$ 的第 $k$ 位和 $Y$ 的第 $k$ 位如果同时为 $1$，$C$ 的第 $k$ 位为 $0$。

所以我们看看 $C$ 的哪些位为 $0$，把 $X$ 和 $Y$ 的对应位都设为 $1$ 就好了，既然一次性要用掉两位，$a+b$ 和 $pc$ 奇偶性当然得相同。于是就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a, b, c;
int bc[64], ba[64], bb[64], l, cnt;
void bin(long long x){//转二进制
	while (x){
		bc[++l] = x & 1;
		if (x & 1)
			++cnt;
		x >>= 1;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> a >> b >> c;
	bin(c);
	if (cnt > a + b){//三种无解情况
		cout << "-1";
		return 0;
	}
	if (max(a, b) - min(a, b) > cnt){
		cout << "-1";
		return 0;
	}
	if (((a + b) & 1) != (cnt & 1)){
		cout << "-1";
		return 0;
	}
	int csa = a - b, csb = 0, sm = 0;
	while (csa + csb < cnt)
		csa++, csb++;
	for (int i = 1; i <= 60; i++){//构造，先找 1
		if (bc[i]){
			if (csa)
				ba[i] = 1, csa--, sm++;
			else if (csb)
				bb[i] = 1, csb--, sm++;
		}
	}
	for (int i = 1; i <= 60; i++)//再找 0
		if (!bc[i])
			if (sm + 2 <= a + b){
				ba[i] = bb[i] = 1;
				sm += 2;
			}
	if (sm < a + b){
		cout << "-1";
		return 0;
	}
	long long aa = 0, bbb = 0;//输出
	for (int i = 1; i <= 60; i++)
		aa += ba[i] * (1ll << (i - 1));
	for (int i = 1; i <= 60; i++)
		bbb += bb[i] * (1ll << (i - 1));
	cout << aa << " " << bbb;
}
```

---

## 作者：NightStriker (赞：0)

考虑异或性质。

当 $C$ 的任意位为 $1$ 时，说明 $X$ 和 $Y$ 中有一个 $1$，一个 $0$。贪心，使得 $X$ 和 $Y$ 保持相等。

当 $C$ 的任意位为 $0$ 时，说明 $X$ 和 $Y$ 都为 $0$ 或 $1$，有 $1$ 则放，无 $1$ 跳过。最后检查 $a$ 和 $b$ 是否都为 $0$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,x,y;
signed main(){
	cin>>a>>b>>c;
	for(int i = 0; i<60; i++){
		if(c>>i&1){//当前位为 1
			if(a>=b) a--,x|=(1ll<<i);
			else b--,y|=(1ll<<i);
		}
	}
	for(int i = 0; i<60; i++){
		if(!(c>>i&1)){//当前位为 0
			if(a>0&&b>0) x|=(1ll<<i),y|=(1ll<<i),a--,b--;
		}
	}
	if(a==0&&b==0) cout<<x<<' '<<y<<endl;
	else cout<<-1<<endl;
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc347_d

## 题意简述

给出三个数 $a,b,c$ 请找出两个数 $x,y$ 使得其二进制位中 `1` 的个数分别为 $a,b$，且 $x \operatorname{xor} y=c$。

## 解题思路

首先让我们考虑什么时候无解。

稍加证明，我们就会发现，只要满足一下几个条件之一就必定无解：

- $(a+b+\operatorname{popcount}(c))\bmod 2=1$。

- $a+b+\operatorname{popcount}(c)>120$。

- $a>b+\operatorname{popcount}(c)$ 或 $b>\operatorname{popcount}(c)+a$ 或 $\operatorname{popcount}(c)>a+b$。

我们可以感性证明一下，对于第一条，$c$ 中是 $0$ 的必定要消耗偶数个（$0$ 或 $2$ 个）`1`，所以 $a+b$ 和 $\operatorname{popcount}(c)$ 的奇偶性必定相同。

对于第二条，由于 $c$ 中为 $1$ 的位置上只能放 $1$ 个，所以这条主要是为了防止 $a+b$ 过大导致 $60$ 位放不下。

对于第三条，我们可以想见，如果要放置 $a$（或 $b$）中的一个 `1`，那么要么 $c$ 的这一位上为 `1`，要么 $b$（或 $a$）的这一位为 `1`。

现在考虑如何求解。

尝试贪心，伪代码如下。

- 遍历 $c$ 的每一位。
	- 如果这一位是 `1`：  
      - 如果 $a>b$，把 $x$ 的这一位设为 `1`。
      - 否则，把 $y$ 的这一位设为 `1`。
   - 否则  
      - 如果 $a>b$，把 $x$ 的这一位设为 `1`。
      - 否则，把 $y$ 的这一位设为 `1`。
      - 如果 $a>b$，把 $x$ 的这一位设为 `1`。
      - 否则，把 $y$ 的这一位设为 `1`。

这样，只要我们保证了有解，通过这个方法就可以使得 $x \operatorname{xor} y=c$。

[code](https://atcoder.jp/contests/abc347/submissions/51967528)

---

## 作者：xiaofu15191 (赞：0)

从题目中异或的定义入手。每一位相同为 `0`，不相同为 `1`。

于是我们首先将 $C$ 进行二进制拆分。

令数字 $k$ 在二进制中的第 $i$ 位为 $k_i$，如果 $C_i$ 为 `1`，那么 $X_i=1,Y_i=0$ 或 $X_i=0,Y_i=1$。

考虑如何分配 `1`。显然，当 $C$ 中的 `1` 被分配完，$X$ 与 $Y$ 剩余的每一位都相同。

在分配 $C$ 中的 `1` 时，我们令当前 $X$ 中的 `1` 个数为 $sum_x$，$Y$ 中 `1` 个数为 $sum_y$。

很容易想到分配策略：如果当前 $a-sum_x>b-sum_y$，即当前 $X$ 比 $Y$ **更需要** `1`，就将 $X$ 的当前位设为 `1`，反之亦然。

分配完 $C$ 中的 `1` 之后，$a-sum_x=b-sum_y$，将剩余的 `1` 分配完即可，最后根据题意用 $\operatorname{popcount}$ 检查正确性即可。

---

## 作者：liangjindong0504 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc347_d)

[AT 题目传送门](https://atcoder.jp/contests/abc347/tasks/abc347_d)

显然，本场比赛 D 比 C 简单。（这还不是因为我太弱了）
### 题目大意
让你构造两个数 $X,Y$，它们都小于 $2^{60}$ 且它们用二进制表示分别有 $a,b$ 个 $1$，同时它们的异或为 $C$。给出 $a,b,C$，任意构造一组 $X,Y$，无解输出 $-1$。
### 思路分析
先不考虑别的，我们就考虑一下 $C$ 是怎么得来的。

为了方便，我们考虑先将 $C$ 变为二进制数。

首先，根据异或的定义，相同得 $0$，不同得 $1$，可知：

- 如果 $C$ 的一位是 $0$，则 $X,Y$ 这一位必须同时为 $1$ 或 $0$。
- 如果 $C$ 的一位是 $1$，则 $X,Y$ 这一位必须有且仅有一个为 $1$。不难发现，这种情况下 $X,Y$ 二进制表示中为 $1$ 的个数是确定的，为 $popcount(C)$。

这样，第一种情况下 $X,Y$ 的 $1$ 确定了，即每一个都为 $\frac{a+b-cnt}{2}$，$cnt$ 表示 $popcount(C)$。于是，从前往后遍历，如果 $C$ 的第 $i$ 位为 $0$ 且个数还没有超出，则 $a,b$ 都加上 $2^{i-1}$。
```cpp
for(int i=1;i<=60;i++){
	if(!f[i]&&opt<(a+b-cnt)/2){
		opt++,opq++;
		long long u=pow(2,i-1);
		ansa+=u;
		ansb+=u;
	}
}
```
第二种情况也就呼之欲出了，再遍历一次，如果 $C$ 的第 $i$ 位为 $1$，则可以先满足 $X$ 中 $1$ 的个数，再满足 $Y$ 的。
```cpp
for(int i=1;i<=60;i++){
	if(opt==a&&opq==b) break;
	if(f[i]==1){
		long long u=pow(2,i-1);
		if(opt<a) opt++,ansa+=u;
		else if(opq<b) opq++,ansb+=u;
	}
}
```
当然，最后不要忘记判断无解。
```cpp
if(opt!=a||opq!=b||(ansa^ansb)!=c) cout<<"-1";
else cout<<ansa<<" "<<ansb<<endl;
```
好了，核心部分已经给出，剩下的部分应该不用多说了吧。（~~逃~~）

当然，还有两点忠告：

**不开 long long 见祖宗！**

**pow 要先转成 long long 类型的！**（虽然我也不知道为什么）

---

## 作者：Kyl_in_2024 (赞：0)

### 思路

学过一点点位运算的都知道，`1^1=0`，所以如果你不能保证 $a+b=popcount(C)$，那么你可以选择 $C$ 的一个为 `0` 的数位，让 $X$ 和 $Y$ 的那一位同为 `1`。可知，结果还是不变的。

当然，并不是都有解的，这里有很多坑要踩：

如果 $a+b \lt popcount(C)$，肯定无论如何都无法满足条件；如果 $a+b- popcount(C)$ 是奇数，又会多出一个 `1`；但是如果 $a \lt b-popcount(C)$ 呢？当满足了 $C$ 的条件，$a,b$ 无论如何都不会相等，将 $a,b$ 调换后也是如此，都不能有解。

虽然看起来么啥错，[但是还是错了！](https://atcoder.jp/contests/abc347/submissions/51932938)

### 大坑

题目明确地说了：

- $0 \le X \lt 2^{60}$
- $0 \le Y \lt 2^{60}$

所以如果 $60 \lt (a+b-popcount(C))/2+popcount(C)$，这里的 $(a+b-popcount(C))/2$ 代表的是需要消除的多余的 $a,b$ 个数，那么最终答案会超出上限，所以也没有解。

### 最终代码

```
#include<bits/stdc++.h>
using namespace std;
signed main(){
	long long a,b,c;
	cin >> a >> b >> c;
	long long tmp=c,count=0;
	while(tmp){
		if(tmp&1) count++;//计算popcount(C)
		tmp>>=1;
	}
	if(a+b<count||(a+b-count)%2==1||a<b-count||b<a-count){//是否无解
		cout<<-1;
		return 0;
	}
	tmp=c;
	long long i=(a+b-count)/2,aa=a-i,bb=b-i;
	if(count+i>60){//特判
		cout<<-1;
		return 0;
	}
	long long ans1=0,ans2=0;
	for(long long j=0;j<64;j++){//答案！
		if(tmp&(1ll<<j)){
			if(aa){
				ans1|=(1ll<<j);
				aa--;
			}else if(bb){
				ans2|=(1ll<<j);
				bb--; 
			}
		}else{
			if(i){
				ans1|=(1ll<<j);
				ans2|=(1ll<<j);
				i--;
			}
		}
	}
	cout<<ans1<<" "<<ans2;
    return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc347/submissions/51865433)

---

