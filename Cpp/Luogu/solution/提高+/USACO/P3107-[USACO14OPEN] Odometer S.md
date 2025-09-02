# [USACO14OPEN] Odometer S

## 题目描述

农夫约翰的奶牛们正在进行一次公路旅行！他们的车上的里程表显示一个整数的里程值，旅行开始时为 $X$（$100 \leq X \leq 10^{18}$）英里，结束时为 $Y$（$X \leq Y \leq 10^{18}$）英里。每当里程表显示一个“有趣”的数字时（包括旅行的开始和结束），奶牛们就会哞叫。如果一个数字在去掉前导零后，其至少一半的数字是相同的，那么这个数字就是“有趣”的。例如，数字 3223 和 110 是有趣的，而数字 97791 和 123 则不是。

帮助农夫约翰计算在旅行中奶牛们会哞叫多少次。

## 说明/提示

旅行开始时里程表为 110，结束时为 133。

当里程表显示 110、111、112、113、114、115、116、117、118、119、121、122、131 和 133 时，奶牛们会哞叫。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
110 133 
```

### 输出

```
14 
```

# 题解

## 作者：whiteqwq (赞：9)

[P3107 [USACO14OPEN]Odometer S](https://www.luogu.com.cn/problem/P3107)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1714880)
## 题意
题意：给定区间$[l,r]$，求区间至少一半的数位相同的数数量。

数据范围：$1\leqslant l\leqslant r\leqslant 10^{18}$。

数位dp的普通题，但是有些细节需要注意。

## 分析
这里，我会把我所有的思考过程记录下来：

观察题面，发现这道题很显然是数位dp。

我们发现处理区间至少一半的数位相同的数的数量不好做，那么就把它拆成处理每个数字$k$出现超过一半的数的数量。

我们可以先写出$\text{calc}$函数的板子（即拆解数位）：
```
int calc(int x,int k){
	memset(f,-1,sizeof(f));
	for(len=0;x;x/=10)
		num[++len]=x%10;
	return dfs1(...);
}
```
这里$\text{calc(x,k)}$指拆解$x$的数位为$num$数组，并求小于等于$x$，且数字$k$不少于一半的数的个数的函数。

然后开始写记忆化搜索的$\text{dfs}$函数，考虑有哪些值可以影响答案：

- 首先是$len,k,flg1$，这三个数分别代表当前处理的数的长度，求解的数字$k$和卡位的标志。（卡位的标志$flg1$在当前选择的数与前面的数完全相同时为$1$，否则为$0$。卡位的标志影响答案的原因：如果$flg1=1$，则当前数位只能取到$num[len]$，因此答案会有差别）
- 为了处理答案（数字$k$必须超过一半），我们要记录两个参数$cnt1,cnt2$，分别指$k$出现的次数与非$k$的数字出现的次数。
- 发现前导零也会对答案造成影响（因为位数可能不一，这样会导致前导零。而前导零中的$0$是不能算到$cnt1$与$cnt2$中的），因此我们也要记录前导零的标志$flg2$。

这样，$\text{dfs}$函数的的参数就出来了：```int dfs1(int len,int k,int cnt1,int cnt2,int flg1,int flg2)```

然后是记忆化搜索的套路：用数组$f[len][cnt1][cnt2][flg1][flg2]$表示处理长度为$len$，当前钦定的数出现次数出现$cnt1$次，非当前钦定的数出现$cnt2$次，卡位标志为$flg1$，前导零标志为$flg2$的答案。

考虑转移也很简单：枚举数位$i$，然后对所有可以放得下（$flg1=0$或$i\leqslant num[len]$）的方案进行转移，注意在$cnt1$与$cnt2$进行转移的时候需要判断前导零，即：```res+=dfs1(len-1,k,cnt1+(i!=0||flg2==0)*(i==k),cnt2+(i!=0||flg2==0)*(i!=k),i==num[len]&&flg1,i==0&&flg2);```

这样，$\text{dfs}$函数也出来了：
```
int dfs(int len,int k,int cnt1,int cnt2,int flg1,int flg2){
	if(len==0)
		return cnt1>=cnt2;
	if(f[len][cnt1][cnt2][flg1][flg2]!=-1)
		return f[len][cnt1][cnt2][flg1][flg2];
	int res=0;
	for(int i=0;i<=9;i++)
		if(i<=num[len]||flg1==0)
			res+=dfs1(len-1,k,cnt1+(i!=0||flg2==0)*(i==k),cnt2+(i!=0||flg2==0)*(i!=k),i==num[len]&&flg1,i==0&&flg2);
	return f[len][cnt1][cnt2][flg1][flg2]=res;
}
```
虽然这样能过样例，但是交上去后会收获WA的好成绩。

这个程序有两点错误：

1. 没开$long\ long$
2. 求解发生错误。

第二点是为什么呢？我们举一个例子：$112212$，这个数可以在$k=1$时产生贡献，也会在$k=2$时产生贡献，即一个长度为偶数的数有可能会出现两个数出现次数同时不少于一半。

此时我们可以使用容斥，将总数减去这些特殊的数，在这里为了方便思考，我把这种特殊的数的求解用了另一个函数$\text{calc2}$，当然也用了另一个记忆化搜索函数$\text{dfs2}$。

$\text{calc2}$的代码很容易写出，这里就不单独提供了（后面有完整代码），我们讲一下$\text{dfs2}$的写法：
首先带入的参数有些变化：
1. 增加了一个$k2$，代表另一个求解的数。
2. 将$cnt2$的意义改成$k2$的出现次数。

记忆化很容易写出，然后就是转移了：

由于这个数只由两个数字组成，我们不需要循环，只需要把循环展开就好了，即写两个$if$，再把计算贡献的$copy$下来就$ok$了。（不过这里要记得考虑一下$cnt2$的转移）

```
long long dfs2(long long len,long long k1,long long k2,long long cnt1,long long cnt2,long long flg1,long long flg2){
	if(len==0)
		return cnt1==cnt2;
	if(f[len][cnt1][cnt2][flg1][flg2]!=-1)
		return f[len][cnt1][cnt2][flg1][flg2];
	long long res=0;
	if(k1<=num[len]||flg1==0)
		res+=dfs2(len-1,k1,k2,cnt1+(k1!=0||flg2==0),cnt2,k1==num[len]&&flg1,k1==0&&flg2);
	if(k2<=num[len]||flg1==0)
		res+=dfs2(len-1,k1,k2,cnt1,cnt2+(k2!=0||flg2==0),k2==num[len]&&flg1,k2==0&&flg2);
	return f[len][cnt1][cnt2][flg1][flg2]=res;
}
```

但是交上去后发现并没有这么简单，还是WA。

为什么呢？这里我想了很久，发现前导零没有考虑：因为位数不一定，因此要考虑前导零的转移（记得不要和$k1$与$k2$的转移重复计算贡献）：

```
	if(k1!=0&&k2!=0&&flg2==1)
		res+=dfs2(len-1,k1,k2,cnt1,cnt2,num[len]==0&&flg1,flg2);
```

## 代码
注意，这里数位dp采用更简单的记忆化搜索形式。
```
#include<stdio.h>
#include<string.h>
const int maxl=25;
long long i,j,k,m,n,len,ans;
long long num[maxl],f[maxl][maxl][maxl][2][2];
long long dfs1(long long len,long long k,long long cnt1,long long cnt2,long long flg1,long long flg2){
	if(len==0)
		return cnt1>=cnt2;
	if(f[len][cnt1][cnt2][flg1][flg2]!=-1)
		return f[len][cnt1][cnt2][flg1][flg2];
	long long res=0;
	for(long long i=0;i<=9;i++)
		if(i<=num[len]||flg1==0)
			res+=dfs1(len-1,k,cnt1+(i!=0||flg2==0)*(i==k),cnt2+(i!=0||flg2==0)*(i!=k),i==num[len]&&flg1,i==0&&flg2);
	return f[len][cnt1][cnt2][flg1][flg2]=res;
}
long long calc1(long long x,long long k){
	memset(f,-1,sizeof(f));
	for(len=0;x;x/=10)
		num[++len]=x%10;
	return dfs1(len,k,0,0,1,1);
}
long long dfs2(long long len,long long k1,long long k2,long long cnt1,long long cnt2,long long flg1,long long flg2){
	if(len==0)
		return cnt1==cnt2;
	if(f[len][cnt1][cnt2][flg1][flg2]!=-1)
		return f[len][cnt1][cnt2][flg1][flg2];
	long long res=0;
	if(k1<=num[len]||flg1==0)
		res+=dfs2(len-1,k1,k2,cnt1+(k1!=0||flg2==0),cnt2,k1==num[len]&&flg1,k1==0&&flg2);
	if(k2<=num[len]||flg1==0)
		res+=dfs2(len-1,k1,k2,cnt1,cnt2+(k2!=0||flg2==0),k2==num[len]&&flg1,k2==0&&flg2);
	if(k1!=0&&k2!=0&&flg2==1)
		res+=dfs2(len-1,k1,k2,cnt1,cnt2,num[len]==0&&flg1,flg2);
	return f[len][cnt1][cnt2][flg1][flg2]=res;
}
long long calc2(long long x,long long k1,long long k2){
	memset(f,-1,sizeof(f));
	for(len=0;x;x/=10)
		num[++len]=x%10;
	return dfs2(len,k1,k2,0,0,1,1);
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=0;i<=9;i++)
		ans+=calc1(m,i)-calc1(n-1,i);
	for(i=0;i<=9;i++)
		for(j=i+1;j<=9;j++)
			ans-=calc2(m,i,j)-calc2(n-1,i,j);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：flora715 (赞：6)

### 题意概括 》
求区间内有趣的数的个数。

该数满足：至少一半的数字时相同的。 


### 方法分析 》
**【多状态的数位DP】**
```cpp
f[i][limit][k][front_zero]
```
#### 表示 已经dp到第i位(从高到低)，

#### 是否触及上界的limit(bool值)，

#### 现在判断的数出现次数为k(正负数判断：每位取该数k--，取别的数k++)，


#### 前导零状态(记录为l，表示当前位置之前全部都是前导零)时，

#### 该位前方的状态已经计算完成，此时的方案数。

每次枚举当前需要判断相同的那个数字，进行数位DP。

注意：形如1122,3344等数计算了两遍，应该把它们枚举出来，再减掉。

具体实现时还有一些细节...

### 代码实现 》

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
using namespace std;
typedef long long ll;
typedef long unsigned int llu;

void reads(int &x){ //读入优化（正负整数）
	int f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=f; //正负号
}

ll f[21][2][51][2];
string le,ri; 

ll DP(string str,int len,int num1,int num2){ //两个数字num1，num2
	ll anss=0; //去除重复计算的时候num2为具体的数字，否则为-1 ↑↑↑
	memset(f,0,sizeof(f)); f[0][0][20][1]=1; //防止数组下标为负，初始化k为20（k会减小）
	for(int i=0;i<len;i++) //从高位到低位，最高位为第0位【遵守字符串的输入方式】
		for(int limit=0;limit<=1;limit++)
			for(int k=0;k<50;k++) //出现次数的加减情况
				for(int front_zero=0;front_zero<=1;front_zero++){
					ll cnt=f[i][limit][k][front_zero]; //用于储存上一次的状态
					for(int now=0;now<=9;now++){
						if(num2!=-1&&(now!=0||front_zero==0)&&now!=num2&&now!=num1) continue;
						//↑↑↑防止 在判断只有两个数字出现的情况中 出现了除前导零之外的其他数字
						if(limit==0&&now>str[i]-'0') continue;
						int nk=k,n0=front_zero;
						n0=n0&(now==0); //如果前导全是0，n0(即front_zero)就是1
						if(n0==0){ //前导不全是0
							if(num2==-1){ //传入函数的只有一个数字
								if(num1==now) nk--; //只用判断该位数字的次数加减情况
								else nk++; //是其他数字，k++
							}else if(num2!=-1){ //传入两个数字，以aaaabbbb形式出现
								if(num1==now) nk--; //num1为加
								else if(num2==now) nk++; //num2为减
							}
						} //注意初始方案数只有f[0][0][20][1]=1，所有状态只能从那里转化过来
						f[i+1][limit|(now<str[i]-'0')][nk][n0]+=cnt; //新状态要加上此次转移的方案数
					}
				}
	if(num2==-1){
		for(int limt=0;limt<2;limt++) //j<=20说明此时判断的数字出现的次数>=一半
			for(int j=0;j<=20;j++) anss+=f[len][limt][j][0];
	}else { for(int limt=0;limt<2;limt++) anss+=f[len][limt][20][0]; }
	return anss; //只有k加减后值为20时，才会使两个数字均恰好出现一半次数
}

ll solve(string str){
	ll anss=0;
	int len=str.length();
	for(int i=0;i<=9;i++) anss+=DP(str,len,i,-1);
	for(int i=0;i<=9;i++) //删除重复计算的aaabbb型
		for(int j=i+1;j<=9;j++) //注意j从i+1开始
			anss-=DP(str,len,i,j); //函数中传入两个数字
	return anss;
}

int main(){
	cin>>le>>ri; //直接把区间边界当做字符串输入进来
	for(int i=le.length()-1;i>=0;i--) //把区间下界转化为求解上界
		if(le[i]=='0') le[i]='9'; //即：把le变为le-1
		else{ le[i]--; break; }
	cout<<solve(ri)-solve(le)<<endl;
	return 0;
}
```

---

## 作者：IamZZ (赞：4)

### 题目大意

Farmer John 的奶牛们在进行一次汽车旅行，汽车上有一个里程表。

奶牛们的旅行从 $X$ 开始，到 $Y$ 结束，即里程表会显示从 $X$ 到 $Y$ 的所有数字。

当奶牛们看见了一个有趣的数字时，她们会发出愉快的叫声~~homo~~。

一个有趣的数满足：若这个数字有 $p$ 位，则至少有 $\lceil\frac{p}{2}\rceil$ 位的数字是相同的。

$100\leq X\leq Y\leq10^{18}$。

### 解题思路

位数，位数，看到答案与位数有关，就很容易想到数位 DP 吧？

数位 DP 无疑可以优秀地解决这道题目，~~但是呢，我每次打数位 DP 都总是打成计数~~。

没有关系，那我们就用数位 DP 的思想，直接计算方案。

1. 差分

$X,Y$ 都很大，直接从中间处理十分麻烦，按照正常的计数思路，肯定考虑计算前缀和 $S$。

最后的答案就可以用 $S_Y-S_{X-1}$ 计算。

如何计算前缀和 $S_v$？

我们设 $v$ 有 $p$ 位数，$c_k$ 为当前已确定的位数中值为 $k$ 的数量，$t_i$ 为 $v$ 第 $i$ 位上的数字。

2. 计数（位数不足）

首先，由于答案最后不考虑前缀 0 的个数，所以我们需要事先搞定位数不足 $p$ 的数中有几个有趣的数。

枚举位数 $i(1\leq i<p)$，不能有前缀 0，枚举的第一位 $j(1\leq j\leq 9)$，此时 $c_j+1$，再枚举数量 $\geq\lceil\frac{i}{2}\rceil$ 的那个数是 $k$，在后面 $i-1$ 位中出现了 $l$ 次。

如果 $l+c_k\geq\lceil\frac{i}{2}\rceil$，说明可行，我们计算方案数，在 $i-1$ 位里面取 $l$ 个位置附上 $k$ 这个数，剩下 $i-1-l$ 个数取不同于 $k$，有 $9^{i-1-l}$ 种取法。

综上，方案数加上 $C_{i-1}^l\times 9^{i-1-l}$。

细心的你，一定发现了问题吧？是的，如果 $i$ 是偶数，而刚好有两种颜色各有 $\frac{i}{2}$ 个，满足这样的有趣的数会被重复算一次。

因此，我们需要减掉这部分重复的数量，第一位有 9 种方案，从 $i-1$ 位中选取 $\frac{i}{2}-1$ 个位置有 $C_{i-1}^{\frac{i}{2}-1}$ 种方案，另一个数不能与第一个重复，也有 9 种。

方案数减去 $C_{i-1}^{\frac{i}{2}-1}\times 81$。位数不足的方案数就此解决。

3. 计数（位数相同）

现在，让我们去处理剩余的那一部分的方案数。

从高到低枚举当前处理的位数 $i$，枚举第 $i$ 位的数字 $j(0\leq j\leq t_i-1)$，注意，如果 $i=p$，$j$ 不能取 0。

$k,l$ 跟上面的定义是一样的，计数方法跟上面也是一样的，当然，前面已经确定为最高位的数也要算在 $c$ 中。

然后，我们又可以发现，如果 $p$ 是偶数，啊，又要算重了。

我们考虑还是枚举第 $i$ 位的值 $j$，现在我们判断已经确定的位上的数的种类，同时要保证没有一个数的个数 $>\frac{p}{2}$。

如果数的种类数是 1 而这个数是 $k$，在剩下的 $i-1$ 位中选取 $\frac{p}{2}-c_k$ 位，另一种数不等于 $k$，共有 $C_{i-1}^{\frac{p}{2}-c_k}\times 9$ 种方案数。

不然，若数的种类是 2，其中有一个数是 $k$，任意一个都可以，还是一样，但是另一种的取值已经固定了，所以只有 $C_{i-1}^{\frac{p}{2}-c_k}$ 种方案数。

把这两种情况都减去，哦对，还要判断 $v$ 是不是一个有趣的数。

到这里，$v$ 之内的所有的有趣的数都已经处理出来了。

完结撒花(●'◡'●)~

### 代码实现

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
ll x,y,m,t[101],p,c[11],fc[101],C[101][101];
ll calc(ll v)
{
	ll i,j,k,l,x=v,w=0,z;
	p=0;
	while(x)
	{
		++p;
		t[p]=x%10;
		x=x/10;
	}
	for(i=0;i<=9;++i)
	  c[i]=0;
	for(i=p;i>=2;--i)//算位数不足的 
	{
		for(j=1;j<=9;++j)
		{
			++c[j];
			for(k=0;k<=9;++k)
			{
				for(l=0;l<i-1;++l)
				{
					if(l+c[k]>=i>>1)
					  w=w+C[i-2][l]*fc[i-2-l];
				}
			}
			--c[j];
		}
		if(i-1&1)
		  continue;
		w=w-81*C[i-2][(i-1>>1)-1];//减！ 
	}
	for(i=p;i>=1;--i)//求位数相同的方案数 
	{
		z=0;
		if(i==p)
		  z=1;
		for(j=z;j<=t[i]-1;++j)//算！ 
		{
			++c[j];
			for(k=0;k<=9;++k)
			{
				for(l=0;l<i;++l)
				{
					if(l+c[k]>=(p+1)>>1)
					  w=w+C[i-1][l]*fc[i-1-l];
				}
			}
			--c[j];
		}
		if(!(p&1))
		{
			for(j=z;j<=t[i]-1;++j)//减掉重复的 
			{
				++c[j];
				x=0;
				for(k=0;k<=9;++k)
				{
					if(c[k])
					  ++x;
				}
				if(x==1)
				{
					for(k=0;k<=9;++k)
					{
						if(c[k]&&c[k]<=p/2)
						{
							w=w-9*C[i-1][p/2-c[k]];
							break;
						}
					}
				}
				else if(x==2)
				{
					for(k=0;k<=9;++k)
					{
						if(c[k]&&c[k]<=p/2)
						{
							w=w-C[i-1][p/2-c[k]];
							break;
						}
					}
				}
				--c[j]; 
			}
		}
		++c[t[i]];
	}
	for(i=0;i<=9;++i)//判断v是不是呢？ 
	{
		if(c[i]>=(p+1)>>1)
		{
			++w;
			break;
		}
	}
	return w;
}
void init()//预处理9的次方，组合数，注意组合数不要太大 
{
	ll i,j;
	C[0][0]=1;
	for(i=1;i<=20;++i)
	{
		C[i][0]=1;
		for(j=1;j<=i;++j)
		  C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	fc[0]=1;
	for(i=1;i<=18;++i)
	  fc[i]=fc[i-1]*9;
	return ;
}
int main()
{
	init();
	scanf("%lld%lld",&x,&y);
	m=calc(y)-calc(x-1);
	printf("%lld",m);
	return 0;
}
```



---

## 作者：mlvx (赞：3)

可爱数位 dp 题捏。

---

显然的，问题可以转化为下面两个问题。

1. $[l,r]$ 中有多少个数满足数码 $k$ 的数量大于等于其他数码的数量。

2. $[l,r]$ 中有多少个数满足数码 $k_1$ 的数量等于数码 $k_2$ 的数量且该数中只含数码 $k_1,k_2$。

---

对于第一个问题，我们只需要记录 $cnt_1$ 与 $cnt_2$，分别表示数码 $k$ 的数量与其他数码的数量。

```cpp
//lm 表示该位是否有限制，f 表示是否没有前导零
ll dfs1(int x,int cnt1,int cnt2,int k,int lm,int f){
	if(!x)return cnt1&&cnt1>=cnt2;//需要满足数码 $k$ 的数量大于等于其他数码的数量，并且这个数码还必须出现过
	if(!lm&&f&&~dp[x][cnt1][cnt2])return dp[x][cnt1][cnt2];//记忆化
	int maxc=lm?num[x]:9;ll ret=0;
	for(int i=0;i<=maxc;i++)ret+=dfs1(x-1,cnt1+(i==k&&(f||i)),cnt2+(i!=k&&(f||i)),k,lm&&i==maxc,f||i);
    //lm&&i==maxc 表示是否有限制，即本身有限制且本位已经取到最大了
    //f||i 表示没有前缀零，即本身就没有前缀零或者本身有前缀零但当前的数字非零
	return !lm&&f&&(dp[x][cnt1][cnt2]=ret),ret;//如果没有限制且没有前导零，就记下答案
}
```

---

为什么只记录第一个问题不行呢？

易举出反例：$1122$。

在我们的代码中，该数在 $k=1$ 时会被统计一次，在 $k=2$ 时会被再次统计。

所以我们要将这种数的重复贡献减掉，这也就是我们的第二个问题。

这类数的特征是只由两个数码组成并且两个数码出现次数相等。

记录 $cnt_1$ 与 $cnt_2$，分别表示数码 $k_1$ 的数量和数码 $k_2$ 的数量。

```cpp
//lm 与 f 的意义同上
ll dfs2(int x,int cnt1,int cnt2,int k1,int k2,int lm,int f){
	if(!x)return cnt1&&cnt1==cnt2;//需要满足二者数量相等，且出现过
	if(!lm&&f&&~dp[x][cnt1][cnt2])return dp[x][cnt1][cnt2];//记忆化
	int maxc=lm?num[x]:9;ll ret=0;//下面把循环展开了，不展开也是可以的
 	if(k1<=maxc)ret+=dfs2(x-1,cnt1+(f||k1),cnt2,k1,k2,lm&&k1==maxc,f||k1);//该位取 k1 的贡献
 	if(k2<=maxc)ret+=dfs2(x-1,cnt1,cnt2+(f||k2),k1,k2,lm&&k2==maxc,f||k2);//该位取 k2 的贡献
 	if(k1&&k2&&!f)ret+=dfs2(x-1,cnt1,cnt2,k1,k2,0,f);//该位有前导零，取 0，需要 k1!=0 且 k2!=0 的原因是防止与上面产生重复贡献
	return !lm&&f&&(dp[x][cnt1][cnt2]=ret),ret;//如果没有限制且没有前导零，就记下答案
}
```

---

贴一下完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll l,r,len,num[20],dp[20][20][20];
//lm 表示该位是否有限制，f 表示是否没有前导零
ll dfs1(int x,int cnt1,int cnt2,int k,int lm,int f){
	if(!x)return cnt1&&cnt1>=cnt2;//需要满足数码 $k$ 的数量大于等于其他数码的数量，并且出现过
	if(!lm&&f&&~dp[x][cnt1][cnt2])return dp[x][cnt1][cnt2];//记忆化
	int maxc=lm?num[x]:9;ll ret=0;
	for(int i=0;i<=maxc;i++)ret+=dfs1(x-1,cnt1+(i==k&&(f||i)),cnt2+(i!=k&&(f||i)),k,lm&&i==maxc,f||i);
    //lm&&i==maxc 表示是否有限制，即本身有限制且本位已经取到最大了
    //f||i 表示没有前缀零，即本身就没有前缀零或者本身有前缀零但当前的数字非零
	return !lm&&f&&(dp[x][cnt1][cnt2]=ret),ret;//如果没有限制且没有前导零，就记下答案
}
//lm 与 f 的意义同上
ll dfs2(int x,int cnt1,int cnt2,int k1,int k2,int lm,int f){
	if(!x)return cnt1&&cnt1==cnt2;//需要满足二者数量相等且出现过
	if(!lm&&f&&~dp[x][cnt1][cnt2])return dp[x][cnt1][cnt2];//记忆化
	int maxc=lm?num[x]:9;ll ret=0;//下面把循环展开了，不展开也是可以的
 	if(k1<=maxc)ret+=dfs2(x-1,cnt1+(f||k1),cnt2,k1,k2,lm&&k1==maxc,f||k1);//该位取 k1 的贡献
 	if(k2<=maxc)ret+=dfs2(x-1,cnt1,cnt2+(f||k2),k1,k2,lm&&k2==maxc,f||k2);//该位取 k2 的贡献
 	if(k1&&k2&&!f)ret+=dfs2(x-1,cnt1,cnt2,k1,k2,0,f);//该位有前导零，计算取 0 的贡献，需要 k1!=0 且 k2!=0 的原因是防止与上面产生重复贡献
	return !lm&&f&&(dp[x][cnt1][cnt2]=ret),ret;//如果没有限制且没有前导零，就记下答案
}void calc(ll x){for(len=0;x;x/=10)num[++len]=x%10;}//数位拆分
ll solve1(ll x,int k){return calc(x),dfs1(len,0,0,k,1,0);}//第一个问题 [1,x] 的答案
ll solve2(ll x,int k1,int k2){return calc(x),dfs2(len,0,0,k1,k2,1,0);}//第二个问题 [1,x] 的答案
ll solve(ll x,ll ret=0){
	for(int i=0;i<=9;i++)memset(dp,-1,sizeof dp),ret+=solve1(x,i);//枚举数码，计算各个数码的贡献
	for(int i=0;i<=9;i++)for(int j=i+1;j<=9;j++)memset(dp,-1,sizeof dp),ret-=solve2(x,i,j);//枚举两个数码，去掉重复贡献
	return ret;
}int main(){return cin>>l>>r,cout<<solve(r)-solve(l-1),0;}
```

---

感谢 @[TLE_AK](https://www.luogu.com.cn/user/788951) 指出了代码中的细节错误，在数码没有出现的时候不能统计进答案，~~但是因为是前缀和相减所以就消掉了，没有影响~~。

---

## 作者：lihe_qwq (赞：2)

首先，这是一道数位 dp 题，其次，这是一篇数位 dp 的题解，所以，不会数位 dp 的童鞋请移步这里[板子](https://www.luogu.com.cn/problem/P2602)。

这题与板子唯一的不同在于，板子是统计每一种数字的出现次数，而这题是统计有多少个数，其一半及以上的数位上的数字是相同的。

考虑在板子记录 $sum1$ 表示已填的钦定数字数量的基础上多记录一维 $sum2$ 表示已填的非钦定数字的数量，则填满时若 $sum1\geq sum2$ 则该数字是合法的。

同时我们发现像 $2233$ 这类数字会在钦定数字 $2$ 与 $3$ 时会被重复计算贡献，所以我们还需要减掉一次重复计算的贡献，这里我用的是只填前导零与钦定的两位数字，再跑一次 dp 的办法来解决。

细节很多这里不再赘述了，代码实现如下。

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
#define int long long
const int N=2e6+10;
int a,b,f[20][20][20][2][2],g[20][20][20][2][2],num[N],ans;
int dfs(int len,int sum1,int sum2,bool f1,bool zero,int d)
{
    if(len==0)
        return f[len][sum1][sum2][f1][zero]=(!zero&&sum1>=sum2);//只填前导零不能返回1
    if(f[len][sum1][sum2][f1][zero]!=-1)   return f[len][sum1][sum2][f1][zero];
    int res=0;
    for(int i=0;i<=9;i++)
    {
        if(!f1&&i>num[len]) break;
        if(zero&&i==0)
            res+=dfs(len-1,sum1,sum2,f1||(i<num[len]),zero&&(i==0),d);//前导零即不记录在sum1中也不记录在sum2中
        else
            res+=dfs(len-1,sum1+(i==d),sum2+(i!=d),f1||(i<num[len]),zero&&(i==0),d);
    }
    return f[len][sum1][sum2][f1][zero]=res;
}


int lp[5];
int Dfs(int len,int sum1,int sum2,bool f1,bool zero,int d)
{
    if(len==0)
        return g[len][sum1][sum2][f1][zero]=(!zero&&sum1==sum2);
    if(g[len][sum1][sum2][f1][zero]!=-1)   return g[len][sum1][sum2][f1][zero];
    int res=0;
    int l=(zero?0:1);//若钦定填的两个数中已经有了0那么就需要特判，否则会算重
    if(d==0)    l=1;
    for(int i=l;i<=2;i++)
    {
        if(!f1&&lp[i]>num[len]) break;
        if(zero&&lp[i]==0)
            res+=Dfs(len-1,sum1,sum2,f1||(lp[i]<num[len]),zero&&(lp[i]==0),d);
        else
            res+=Dfs(len-1,sum1+(lp[i]==d),sum2+(lp[i]!=d),f1||(lp[i]<num[len]),zero&&(lp[i]==0),d);
    }
    return g[len][sum1][sum2][f1][zero]=res;
}
int solve(int x,int id)
{
    int len=0;
    while(x)
    {
        num[++len]=x%10;
        x/=10;
    }
    memset(f,-1,sizeof(f));
    int res=0;//res记录对i而言，填另一个大于i的数字算重的数量
    for(int i=id+1;i<=9;i++)
    {
        lp[1]=id,lp[2]=i;
        memset(g,-1,sizeof(g));
        res+=Dfs(len,0,0,0,1,id);
    }
    return dfs(len,0,0,0,1,id)-res;
}
signed main()
{
    scanf("%lld%lld",&a,&b);
    for(int i=0;i<=9;i++)
        ans+=solve(b,i)-solve(a-1,i);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：haochengw920 (赞：2)

提供一下复杂度 $O(n^2)$ 的记搜解法。

思路是容斥，每个数字大于等于一半的方案数 减去 只由两个数字组成并且长度为偶数的方案数。

直接数位 dp 的话第二部分空间是 $O(n^3)$ 的，记录两个数字的出现次数。

这道题其实可以加强到 $3000$，这样的话就寄了。

有一个 trick：记一个数字，出现第一个 $+1$，出现第二个 $-1$ ，最后等于 $0$ 就行。

这样一看第一部分也可以这么写，于是一个 dfs 就行了。

写法上，记搜比递推更容易理解，~~理论上~~ 转移数量也更少，没有任何卡常跑到了最优解第 5 。

具体见代码： 

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;

const int MAXN = 25;

int L, R;
int dp[MAXN][MAXN << 1][2][2];

int a[MAXN];
inline int dfs(int len, int cnt, int num1, int num2, bool ld, bool lim) {
	if (!len) return (cnt == MAXN);
	if (~dp[len][cnt][ld][lim]) return dp[len][cnt][ld][lim];
	int mx = lim ? a[len] : 9, t, res = 0;
	for (int i = 0; i <= mx; ++ i) {
		if (num2 != -1 && (!ld || i != 0) && i != num1 && i != num2)
			continue;
		if (i == 0 && ld) res += dfs(len - 1, cnt, num1, num2, ld, lim && (i == mx));
		else res += dfs(len - 1, cnt - 2 * (i == num1) + 1, num1, num2, 0, lim && (i == mx));
	}
	return (dp[len][cnt][ld][lim] = res); 
}
inline int Solve(int x) {
	int len = 0, ans = 0;
	while (x) a[++ len] = x % 10, x /= 10;
	for (int i = 0; i <= 9; ++ i) {
		memset(dp, -1, sizeof(dp));
		for (int j = 0; j <= len; ++ j)
			ans += dfs(len, MAXN + j, i, -1, 1, 1);
	}
	for (int i = 0; i < 9; ++ i)
		for (int j = i + 1; j <= 9; ++ j) {
			memset(dp, -1, sizeof(dp));
			ans -= dfs(len, MAXN, i, j, 1, 1);
		}
	return ans;
}

signed main()
{
	scanf ("%lld%lld", &L, &R);
	printf ("%lld\n", Solve(R) - Solve(L - 1));
	return 0;
}
```

---

## 作者：Jr_Zlw (赞：2)

## 数位 dp

考虑比较难以记录某个状态下的最大值，可以直接枚举一个数  $d$  计算强制它为最大值的方案和。

设  $c$  为  $d$  在某个长度为  $n$  的数中的出现次数，要求满足  $c\geq \lceil\frac{n}{2}\rceil$。

设  $c'$  为  $d$  以外数码的出现次数，即需要满足  $c-c'\geq 0$。

所以设  $dp_{i,j}$  表示前  $i$  个数位，$c-c'=j$  的方案数，再按照数位 dp 的套路记录上下界啥的就可以转移了。

但是很遗憾，算重了。

需要容斥掉那些存在两个数码都恰好占一半的情况。

同样是枚举这两个数，然后发现这一次合法的数中只包含这两个字符，所以可以记录  $g_{i,j}$  表示考虑到前  $i$  位，其中一个数码填了  $j$  次的方案数，同样套路转移即可。

代码：

```
#include<cstdio>
#include<cstring>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
typedef long long ll;
const int M=20;
int a[20],n;ll L,R;
ll dp[20][50][10][2],g[20][20][2][2];
inline ll G(int d1,int d2)
{
	int d[2]={d1,d2};
	memset(g,0,sizeof(g));
	rep(0,1,i)
	{
		g[1][i][i][0]=1;
		if(d[i]<=a[1])g[1][i][i][1]=1;
	}
	rep(1,n-1,i)
	{
		rep(0,i,j)
		{
			rep(0,1,k)
			{
				rep(0,1,c)
				{
					int nj=j+c;
					g[i+1][nj][c][0]+=g[i][j][k][0];
					if(d[c]<=a[i+1])
					{
						if(d[c]==a[i+1]){g[i+1][nj][c][1]+=g[i][j][k][1];}
						else{g[i+1][nj][c][1]+=g[i][j][k][0];}
					}
				}
			}
		}
	}
	ll ans=0;
	if(!(n&1))
	{
		rep(0,1,i)if(d[i]&&d[i]<=a[n])
		{
			ans+=g[n][n>>1][i][d[i]==a[n]];
		}
	}
	for(int i=2;i<n;i+=2)
	{
		rep(0,1,j)if(d[j])
		{
			ans+=g[i][i>>1][j][0];
		}
	}
	return ans;
}
inline ll DP(int d)
{
	memset(dp,0,sizeof(dp));
	rep(0,9,i)
	{
		dp[1][(i==d?1:-1)+M][i][0]=1;
		if(i<=a[1])dp[1][(i==d?1:-1)+M][i][1]=1;
	}
	rep(1,n-1,i)
	{
		rep(-i,i,j)
		{
			rep(0,9,k)
			{
				rep(0,9,c)
				{
					int nj=j+(c==d?1:-1);
					dp[i+1][nj+M][c][0]+=dp[i][j+M][k][0];
					if(c<=a[i+1])
					{
						if(c==a[i+1])dp[i+1][nj+M][c][1]+=dp[i][j+M][k][1];
						else dp[i+1][nj+M][c][1]+=dp[i][j+M][k][0];
					}
				}
			}
		}
	}
	ll ans=0;rep(0,n,j)
	{
		rep(1,a[n]-1,c)ans+=dp[n][j+M][c][0];
		ans+=dp[n][j+M][a[n]][1];
	}
	rep(1,n-1,i)rep(0,i,j)rep(1,9,c)ans+=dp[i][j+M][c][0];
	return ans;
}
inline ll S(ll x)
{
	n=0;while(x)a[++n]=x%10,x/=10;ll ans=0;
	rep(0,9,i)ans+=DP(i);rep(0,9,i)rep(i+1,9,j)ans-=G(i,j);
	return ans;
}
int main()
{
	scanf("%lld%lld",&L,&R);
	printf("%lld\n",S(R)-S(L-1));
}
```

---

## 作者：Leianha (赞：2)

## 记忆化搜索

[博客阅读](https://www.cnblogs.com/wljss/p/12500405.html)

既然需要出现的次数 $\geq$ 长度的一半，我们不妨就枚举这个数，按照记搜的套路，我们记录一下这个数的出现次数以及是否没了前导零即可。

记录次数的时候如果往后添的数是枚举的数，则 $++cnt$ ,否则 $--cnt$ ,易证符合条件当且仅当 $pos=0$ 时 $cnt$ $\geq$ $0$.

我们发现对于 $10$ , $1122$ ，$2323$ 这类数会被计算 $2$ 次，我们再用类似的方法减去即可。

注意数组下标不能是负数。

详细可以看代码。

```cpp
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
int num1, num2, tot;
LL l, r;
int w[233];
LL f[20][40][40][2][2];
LL dfs(int pos, int cnt1, int cnt2, int pre, int g)
{
	if (!pos)return pre && (num2 == -1 ? cnt1 >= 19 : (cnt1 >= 19 && cnt2 >= 19));
	if (f[pos][cnt1][cnt2][pre][g] != -1)return f[pos][cnt1][cnt2][pre][g];
	int lim = g ? w[pos] : 9 , t1, t2; LL res = 0;
	for (int i = 0; i <= lim; ++i)
		t1 = cnt1 + (pre || i > 0) * (i == num1 ? 1 : -1),
		t2 = num2 == -1 ? 0 : cnt2 + (pre || i > 0) * (i == num2 ? 1 : -1),
		res += dfs(pos - 1, t1, t2 , pre || (i > 0), g && i == lim);
	return f[pos][cnt1][cnt2][pre][g] = res;
}
LL solve(LL x)
{
	tot = 0;
	while (x)w[++tot] = x % 10, x /= 10;
	LL res = 0;
	for (int i = 0; i <= 9; ++i)
		memset(f, -1, sizeof(f)), num1 = i, num2 = -1, res += dfs(tot, 19, 0, 0, 1);
	for (int i = 0; i <= 9; ++i)
		for (int j = i + 1; j <= 9; ++j)
			memset(f, -1, sizeof(f)), num1 = i, num2 = j, res -= dfs(tot, 19, 19, 0, 1);
	return res;
}
signed main()
{
	cin >> l >> r;
	cout << solve(r) - solve(l - 1);
	return 0;
}
```


---

## 作者：wmrqwq (赞：2)

# 题目链接

[P3107 [USACO14OPEN] Odometer S](https://www.luogu.com.cn/problem/P3107)

# 解题思路

数位 dp 模板。

令某个数的**特殊数字**为**在一个数字中至少出现过一半的数位的数字**。

首先我们可以依次拆分数位来枚举当某个数位为**特殊数字**时来进行数位 dp，状态为 $dp_{last,len,num,sum,\_1,\_0}$ 来代表还剩余 $last$ 个数位需要处理，当前**去除先导零**时的当前数字的位数为 $len$，当前的**特殊数字**为 $num$，当前出现的特殊数字的次数为 $sum$，$\_1$ 表示当前的位数是否取满，$\_0$  表示当前数字是否当前取的数字不全为零。

但是这样是不对的，为什么呢？你会发现，可能会有 $114414$ 这样类型的数字，这种数字会分别在以 $1$ 为特殊数字时被计算一次，以 $4$ 为特殊数字时计算一次，你会发现，这个数字对答案的贡献**被重复计算了**。

然后我们可以发现，一个数字会被重复计算当且仅当：

- 这个数字有两种不同的数位。

- 这个数字出现过的两种数位的出现次数相等。

这个部分也是数位 dp 板子。

状态为 $dp_{last,len,num1,num2,sum1,sum2,\_1,\_0}$ 来代表还剩余 $last$ 个数位需要处理，当前**去除先导零**时的当前数字的位数为 $len$，当前的**特殊数字** $1$ 为 $num1$，当前的**特殊数字** $2$ 为 $num2$，当前出现的特殊数字 $1$ 次数为 $sum$，当前出现的特殊数字 $2$ 次数为 $sum2$，$\_1$ 表示当前的位数是否取满，$\_0$  表示当前数字是否当前取的数字不全为零。

与前面的答案简单容斥一下即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll t;
ll l,r;
ll a[20],k;
ll dp[20][20][15][20][2][2];
int dp2[20][20][10][10][10][10][2][2];
__int128 ans;
ll dfs(ll last,ll len,ll num,ll sum,ll _1,ll _0)
{
	if(last==0)
		return sum*2>=len && sum && len && _0;
	if(dp[last][len][num][sum][_1][_0]>=0)
		return dp[last][len][num][sum][_1][_0];
	ll maxn=_1?a[last]:9,ans=0;
	forl(i,0,maxn)
		ans+=dfs(last-1,len+(_0||(i!=0)),num,sum+(i==num && (_0 || (i!=0))),_1&&(i==maxn),_0||(i!=0));
	dp[last][len][num][sum][_1][_0]=ans;
	return ans;
}
ll dfs2(ll last,ll len,ll num,ll num2,ll sum,ll sum2,ll _1,ll _0)
{
	Min(sum,9ll),Min(sum2,9ll);
	if(last==0)
		return sum+sum2==len && sum && len && _0 && sum2 && sum==sum2;
	if(dp2[last][len][num][num2][sum][sum2][_1][_0]>=0)
		return dp2[last][len][num][num2][sum][sum2][_1][_0];
	ll maxn=_1?a[last]:9,ans=0;
	forl(i,0,maxn)
		ans+=dfs2(last-1,len+(_0||(i!=0)),num,num2,sum+(i==num && (_0 || (i!=0))),sum2+(i==num2 && (_0 || (i!=0))),_1&&(i==maxn),_0||(i!=0));
	dp2[last][len][num][num2][sum][sum2][_1][_0]=ans;
	return ans;
}
ll sol(ll x,ll y)
{
	k=0;
	while(x)
		a[++k]=x%10,x/=10;

	return dfs(k,0,y,0,1,0);
}
ll sol2(ll x,ll y,ll z)
{
	k=0;
	while(x)
		a[++k]=x%10,x/=10;
	return dfs2(k,0,y,z,0,0,1,0);
}
void solve()
{
	forl(i,0,19)
		forl(j,0,19)
			forl(ii,0,14)
				forl(jj,0,19)
					forl(iii,0,1)
						forl(jjj,0,1)
							dp[i][j][ii][jj][iii][jjj]=-1;
	forl(i,0,19)
		forl(j,0,19)
			forl(ii,0,9)
				forl(jj,0,9)
					forl(iii,0,9)
						forl(jjj,0,9)
							forl(iiii,0,1)
								forl(jjjj,0,1)
									dp2[i][j][ii][jj][iii][jjj][iiii][jjjj]=-1;
	cin>>l>>r;
	forl(i,0,9)
		ans+=sol(r,i);
	forl(i,0,19)
		forl(j,0,19)
			forl(ii,0,14)
				forl(jj,0,19)
					forl(iii,0,1)
						forl(jjj,0,1)
							dp[i][j][ii][jj][iii][jjj]=-1;
	forl(i,0,9)
		ans-=sol(l-1,i);
	forl(i,0,9)
		forl(j,i+1,9)
			ans-=sol2(r,i,j);
	forl(i,0,19)
		forl(j,0,19)
			forl(ii,0,9)
				forl(jj,0,9)
					forl(iii,0,9)
						forl(jjj,0,9)
							forl(iiii,0,1)
								forl(jjjj,0,1)
									dp2[i][j][ii][jj][iii][jjj][iiii][jjjj]=-1;
	forl(i,0,9)
		forl(j,i+1,9)
			ans+=sol2(l-1,i,j);
	ll an=ans;
	cout<<an<<endl;
}
int main()
{
	IOS;
	t=1;
// 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：Erica_N_Contina (赞：1)

我的博客

本文知识点参考于：[oi-beats/数位 dp](https://ntsc-yrx.github.io/oi-beats/site/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E6%95%B0%E4%BD%8DDP/)，[个人博客](https://ntsc.flowus.cn/)。

知识点摘录

数位 DP 是一种处理数字相关问题的动态规划方法。它通常用于解决以下类型的问题：

1. 计算在给定范围内，满足某些特定数位条件的数字个数。

2. 求解某个数位问题的具体方案数。

3. 找出满足特定数位性质的数字。

数位 DP 的核心思想是将数字的每一位分开考虑，使用记忆化搜索（通常是递归的形式）来避免重复计算，从而提高效率。

本题是比较复杂的数位 dp，那么第一个难点就是任何定义状态。

题目要求我们求出至少一半的数字是相同的数字的个数，为了方便记录是那个数字，我们就像枚举那个超过一半的数字的值。

这里注意我们可能会重复计算类似 `aabb` 的数字，后面我们要减去。

那么先定义框架。

`dfs(len,val,cntVal,cntOth,zero,lim)` 表示从高到低考虑到第 $len$ 位，枚举的超过一半的数字为 $val$，个数为 $cntVal$，其他的数字的个数为 $cntOth$（不含前导 $0$），当前位是否可以填 $0$，当前位是否 $lim$。

这里提供一个记忆化搜索的数位 dp 模板，适合记忆，方便扩展。

```C++
int dfs(int x,...,bool zero,bool lim){

    //当前填第x位（从高到低），前面是否全是前导0，当前位之前是否全部顶格
    if(f[x][...][zero][lim]!=-1)return f[x][...][zero][lim];
    
    if(!x)return f[x][...][zero][lim]=...;
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9; 
    for(int i=l;i<=r;i++){
        res+=dfs(x-1,...,0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs(x-1,...,1,0);
    }

    f[x][...][zero][lim]=res;
    return res;
}

```


当写出状态后，我们的转移其实并没有多困难。

我们只需要在所有可用数字中枚举当前位可以填什么，然后对状态值进行一些改变就可以递归下去了。

统计答案：我们在 $len=0$ 时统计答案就行了！

```C++

int dfs(int x,int num,int cnt,int cntOth,bool zero,bool lim){
    if(f[x][cnt][cntOth][zero][lim]!=-1)return f[x][cnt][cntOth][zero][lim];
    
    if(!x)return f[x][cnt][cntOth][zero][lim]=(cnt&&cnt>=cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        res+=dfs(x-1,num,cnt+(i==num),cntOth+(i!=num),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs(x-1,num,cnt,cntOth,1,0);
    }

    f[x][cnt][cntOth][zero][lim]=res;
    return res;
}

```


计算 `aabb` 个数的时候，我们先枚举 $a,b$ 然后计算。有个很 naive 的想法是我们直接组合数计算不就行了？但是注意文明不能超过某一个上限，所以还是到数位 dp。

```C++
int dfs2(int x,int num1,int num2,int cnt,int cntOth,bool zero,bool lim){
    if(g[x][cnt][cntOth][zero][lim]!=-1)return g[x][cnt][cntOth][zero][lim];
    // if(num1==1&&num2==2)cdbg(x,num1,num2,cnt,cntOth,zero,lim);
    
    if(!x)return g[x][cnt][cntOth][zero][lim]=(cnt&&cnt==cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        if(i!=num1&&i!=num2)continue;
        res+=dfs2(x-1,num1,num2,cnt+(i==num1),cntOth+(i==num2),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs2(x-1,num1,num2,cnt,cntOth,1,0);
    }

    g[x][cnt][cntOth][zero][lim]=res;
    return res;
}
```


下面是完整代码：

```C++
/*
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+getId then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'

*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first
#define mp make_pair

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read() {
	int xx = 0, ff = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		xx = xx * 10 + (ch - '0'), ch = getchar();
	return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg) {
		cerr << s;
		if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() {
	cerr << endl;
}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
	for (auto v: a) cerr << v << ' ';
	err(x...);
}
template<typename T, typename... A>
void err(T a, A... x) {
	cerr << a << ' ';
	err(x...);
}
#else
#define dbg(...)
#endif



const int N = 50 + 10;
const int INF = 2e9;
const int M = 1e3 + 10;
const int MOD = 1e9 + 7;

int f[33][33][33][2][2];
int g[33][33][33][2][2];
int digit[N];

int dfs(int x,int num,int cnt,int cntOth,bool zero,bool lim){
    if(f[x][cnt][cntOth][zero][lim]!=-1)return f[x][cnt][cntOth][zero][lim];
    
    if(!x)return f[x][cnt][cntOth][zero][lim]=(cnt&&cnt>=cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        res+=dfs(x-1,num,cnt+(i==num),cntOth+(i!=num),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs(x-1,num,cnt,cntOth,1,0);
    }

    f[x][cnt][cntOth][zero][lim]=res;
    return res;
}


int dfs2(int x,int num1,int num2,int cnt,int cntOth,bool zero,bool lim){
    if(g[x][cnt][cntOth][zero][lim]!=-1)return g[x][cnt][cntOth][zero][lim];
    // if(num1==1&&num2==2)cdbg(x,num1,num2,cnt,cntOth,zero,lim);
    
    if(!x)return g[x][cnt][cntOth][zero][lim]=(cnt&&cnt==cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        if(i!=num1&&i!=num2)continue;
        res+=dfs2(x-1,num1,num2,cnt+(i==num1),cntOth+(i==num2),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs2(x-1,num1,num2,cnt,cntOth,1,0);
    }

    g[x][cnt][cntOth][zero][lim]=res;
    return res;
}

int calc(int x){
    // cdbg(x);
    int a=0,b=0;

    int len=0;
    while(x){
        digit[++len]=x%10;
        x/=10;
    }

    for(int i=0;i<=9;i++){
        memset(f,-1,sizeof f);   
        a+=dfs(len,i,0,0,1,1);
    }

    for(int i=0;i<=9;i++){
        for(int j=i+1;j<=9;j++){
            memset(g,-1,sizeof g);
            b+=dfs2(len,i,j,0,0,1,1);
        }
    }

    // cdbg(a,b);

    return a-b;
}

void solve(){
    int l=rd,r=rd;

    cout<<calc(r)-calc(l-1)<<endl;
}


signed main() {
    // freopen("kujou.in","r",stdin);
    // freopen("kujou.out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }

    return 0;
}

```

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

本题，很明显是一道数位动态规划，所以，我们首先从前缀和求答案来思考这道题，毕竟用前缀和可以利用数位动态规划的记忆化搜索来省去很多时间。

我们定义一个数 $k$，使得**它组成的数**满足题目~~严苛~~的条件，接着，我们求 $1$ 到 $x$ 有多少个数满足 $k$ 出现的次数多于一半，因此我们将第一个深度优先搜索函数中的变量分别定义为填到了第 $x$ 位，$k$ 这个数出现了 $t$ 次，当前是否达到最大值，也就是当前数位的最大值，毕竟枚举是有范围的。之后，我们枚举每次 $x$ 该填哪一个数字，枚举即可。

不过，当我们遇到 $1122$ 这种数字时，我们在枚举 $1$ 和 $2$ 时都算到了他们，那么我们还需要再设一个深度优先搜索函数，表示我们目前在第 $x$ 位，其中这一位要么是 $k1$，要么是 $k2$，其中 $k1$ 出现了 $t1$ 次，$k2$ 有 $t2$ 次，之后我们在计算答案 $ans$ 变量时直接通过是填 $k1$ 还是 $k2$ 即可。

最后，还要注意一点，这道题会**不能有前导 $0$ 出现**，所以，我们要在两个搜索开始前就枚举第一个数，毕竟第一个数只有从 $1$ 到 $9$。

# 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[51][51][10], d[51], tot;
int dfs1(int x, int k, int t, bool top, int vd)
{
    if (x > tot)
    {
        return t >= (vd + 1) / 2;
    }
    // assert(x <= 20);
    if (~dp[x][t][top])
    {
        return dp[x][t][top];
    }
    int ret = 0, mx = top ? d[x] : 9;
    for (int i = 0; i <= mx; i++)
    {
        ret += dfs1(x + 1, k, (i == k) + t, top && i == mx, vd);
    }
    // cout << "ret=" << ret << endl;
    return dp[x][t][top] = ret;
}
int g[51][51][51][10];
int dfs2(int x, int k1, int k2, int t1, int t2, bool top)
{
    if (x > tot)
    {
        return t1 == t2;
    }
    if (~g[x][t1][t2][top])
    {
        return g[x][t1][t2][top];
    }
    int ans = 0;
    if (!top)
    {
        ans += dfs2(x + 1, k1, k2, t1 + 1, t2, false);
        ans += dfs2(x + 1, k1, k2, t1, t2 + 1, false);
        // cout << "ans2=" << ans << endl;
        return g[x][t1][t2][top] = ans;
    }
    else
    {
        // cout << g[x][t1][t2][top] << endl << endl << endl;
        if (d[x] < k1)
        {
            return g[x][t1][t2][top] = 0;
        }
        if (k1 <= d[x] && d[x] < k2)
        {
            return g[x][t1][t2][top] = dfs2(x + 1, k1, k2, t1 + 1, t2, k1 == d[x]);
        }
        if (k2 <= d[x])
        {
            ans += dfs2(x + 1, k1, k2, t1 + 1, t2, k1 == d[x]);
            ans += dfs2(x + 1, k1, k2, t1, t2 + 1, k2 == d[x]);
            // cout << "ans3=" << ans << endl;
            return g[x][t1][t2][top] = ans;
        }
    }
}

int calc(int x)
{
    if (x == 1e18)
    {
        return calc(x - 1) + 1;
    }
    int t = x;
    tot = 0;
    while (t)
    {
        d[++tot] = t % 10;
        t /= 10;
    }
    reverse(d + 1, d + 1 + tot);
    int ans = 0;
    for (int i = 1; i <= tot; i++)
    {
        for (int k = 0; k <= 9; k++)
        {
            for (int j = 1; j <= 9; j++)
            {
                if (i == 1 && j > d[1])
                {
                    break;
                }
                memset(dp, -1, sizeof dp);
                int tmp = dfs1(i + 1, k, j == k, i == 1 && j == d[1], tot - i + 1);
                ans += tmp;
                // cout << "ans4=" << ans << endl;
            }
        }
    }
    for (int i = 1; i <= tot; i++)
    {
        if ((tot - i + 1) % 2)
        {
            continue;
        }
        for (int k1 = 0; k1 <= 9; k1++)
        {
            for (int k2 = k1 + 1; k2 <= 9; k2++)
            {
                if (i != 1)
                {
                    memset(g, -1, sizeof g);
                    if (k1)
                    {
                        ans -= dfs2(i + 1, k1, k2, 1, 0, false);
                    }
                    memset(g, -1, sizeof g);
                    if (k2)
                    {
                        ans -= dfs2(i + 1, k1, k2, 0, 1, false);
                    }
                    // cout << "ansgg=" << ans << endl;
                    continue;
                }
                if (d[1] < k1)
                {
                    break;
                }
                if (k1 <= d[1] && d[1] < k2)
                {
                    memset(g, -1, sizeof g);
                    if (k1)
                    {
                        ans -= dfs2(i + 1, k1, k2, 1, 0, d[1] == k1);
                    }
                }
                if (k2 <= d[1])
                {
                    memset(g, -1, sizeof g);
                    if (k1)
                    {
                        ans -= dfs2(i + 1, k1, k2, 1, 0, d[1] == k1);
                    }
                    memset(g, -1, sizeof g);
                    if (k2)
                    {
                        ans -= dfs2(i + 1, k1, k2, 0, 1, d[1] == k2);
                    }
                }
            }
        }
    }
    return ans;
}
signed main()
{
    int l, r;
    cin >> l >> r;
    cout << calc(r) - calc(l - 1) << endl;
    return 0;
}
```

---

## 作者：yuyudong (赞：0)

因为题目是问一个范围内的数是否满足某个条件，所以我们会想到数位 dp

对于本题，我有个不同于其他题解的思路，不用那么多状态（但其实还是有 4 个），我们可以分类讨论一下

首先我们把一个数，比如  114514  ，分成
1 - 9 ，10 - 99 ，100 - 999 ， 1000 -9999 ， 10000 - 99999，  100000 - 114514，然后就可以分类讨论了

`我们用四个维度，具体可以参考代码，现在考虑到（从高位到低位）第  $i$  个数， $a$ 表示目前的众数（出现最多的数），  $c$ 表示 $a$ 出现了多少次， $limit$ 表示现在的数是否达到上界

和我一开始想不清楚为什么要有    $limit$   的存在的童鞋可以去看这个文章       [点这里]（https://www.acwing.com/blog/content/34709/）

我知道你现在还是很懵，但你先别急

#### 初始化

初始化是单独求出第 $1$ 位（最高位）的答案
， 循环  $ i $  从  $1$  （最高位不能为 $0$ ） 到 $maxn$ （第一位最大的数），循环 $j$ （代表枚举众数） 从  $0$  到  $9$ （每个数，因为下面转移要用到）
`


#### 一般情况

我们先考虑一般的情况（除去 1122 这种只有两个数并且这两个数都是众数的情况）

我们枚举众数 $a$ ，从 $0$ 到 $9$ ，枚举出现的次数  $c$  ，从 $0$ 到  $n$ ，枚举  $limit$  ，要么 $0$ ，要么 $1$ ，再枚举当前的 第 $i$ 位，可以选择的数  $y$  （前面如果都选满了，即  `limit==1`  ， $y$ 就只能选到这个数的当前位置的数了（$maxy$），否则就可以选 $0$ 到    $9$

那么状态转移方程就是

`
 dp[i][a][c+（a==y）[ limit && y==maxy ]+=dp[i][a][c][limit]
`


这里如果枚举到的数和 $a$ 相等，那么 $c$ 就可以加 $1$ 
，如果前面的数都顶满了 （`limit==1`） ，并且当前位也顶满了 （`y==max_y`），那么这个状态就顶满了


最后把所有数加起来就行了

#### 特殊情况

好了，这样求我们会把 $ 1122 $ 的贡献算两次，重复了，所以我们还要一个函数把一个数字的贡献减去

没错我们还是枚举， $i$ 从 $0$ 到  $9$ ， $j$ 从 $i+1$ 到 $9$ ，
减去两个数字分别为为 $i$ 和 $j$ 的贡献

这个函数跟上面的函数差不多，但是我们可选择的数只有 $i$ 和 $j$ 了，所以可以去掉第二维（众数那一维），  $c$  只用枚举到   $\frac{n}{2}$   就行了，然后统计的时候统计和就行了，**注意，如果当前数的数位是奇数的话不可能用到这个函数，直接返回 0 就好了**

代码里还有一个小细节，我注释上了

#### 代码



---





 

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[21][11][21][2];
ll p10[21];
ll L,R;
ll calc3(int n,int a,int b,ll x)
{
	if(n%2) return 0;
	int f[21][21][2]={0}; 
	int maxn=x/p10[n-1];
	if(a>0&&a<=maxn) f[1][(a==a)][a==maxn]+=1;
	if(b>0&&b<=maxn) f[1][(b==a)][b==maxn]+=1;
	for(int i=1;i<=n-1;i++)
	{
		maxn=x/p10[n-1-i]%10;
		for(int c=0;c<=n/2;c++)
		{
			for(int p=0;p<=1;p++)
			{
				if(f[i][c][p])
				{
					int max_y= p ? maxn : 9;
					if(a<=max_y) f[i+1][c+(a==a)][p && a==max_y]+=f[i][c][p];
					if(b<=max_y) f[i+1][c+(b==a)][p && b==max_y]+=f[i][c][p];
				}
			}
		}
	}
	ll res=0;
	for(int p=0;p<=1;p++)
	{
		res+=f[n][n/2][p];
	}
	return res;
}
ll calc2(int n,ll x)
{
	memset(dp,0,sizeof(dp));
	int maxn=x/p10[n-1];
	for(int a=1;a<=maxn;a++)
	{
		for(int b=0;b<=9;b++)
		{
			dp[1][b][a==b][a==maxn]+=1;
		}
	 }
	for(int i=1;i<=n-1;i++)
	{
		maxn=x/p10[n-1-i]%10;
		for(int a=0;a<=9;a++)
		{
			for(int c=0;c<=n;c++)
			{
				for(int p=0;p<=1;p++)
				{
					if(dp[i][a][c][p])
					{
						int max_y= p? maxn : 9 ;
						for(int y=0;y<=max_y;y++)
						{
							dp[i+1][a][c+(a==y)][p && (y==max_y)]+=dp[i][a][c][p];
						}
					}
				}
			}
		}
	}
	long long res=0;
	for(int a=0;a<=9;a++)
	{
		for(int c=(n+1)/2;c<=n;c++)
		{
			for(int p=0;p<=1;p++)
			{
				res+=dp[n][a][c][p];
			}
		}
	}
	return res;
}
ll calc1(int n,ll x)
{
	long long res=calc2(n,x);
	for(int a=0;a<=9;a++)
	{
		for(int b=a+1;b<=9;b++)
		{
			res-=calc3(n,a,b,x);
		}
	}
	return res;
}
ll calc(ll x)
{
	ll res=0;
	for(int i=1;i<=18;i++)
	{
		if(x>=p10[i]) res+=calc1(i,p10[i]-1);
		else if(x>=p10[i-1]) res+=calc1(i,x);
		else break;
	 } 
	if(x==1e18) res++;//这里非常重要，不然会wa一个点
	//因为1e18会漏掉 1e18 - 1e18 这个情况，然而i枚举不到19，所以不会执行else if语句 
	return res;
}
int main()
{
	cin>>L>>R;
	p10[0]=1;
	for(int i=1;i<=18;i++) p10[i]=p10[i-1]*10; 
	cout<<calc(R)-calc(L-1);
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 题目大意：
求 $l$ 到 $r$ 中至少有一半数位上的数字相同的数字的个数。
### 分析：
考虑枚举那个相同的数字记为 $k$，然后用数位 dp 计算 $k$ 出现了超过一半的方案数，全部相加。

但是此时并不是最后的答案，考虑一种情况：一个数中有两个超过一半的数字，那么此数字就会被重复计算两遍，所以最后还要减去这些重复计算的，只需用数位 dp 计算同时有两个超过一半的数字的方案数即可。
### 代码如下：
```cpp
#include<bits/stdc++.h>
#define N 20
#define ll long long
using namespace std; 
ll n,m;
int cnt,s[N];
ll dp[N][N][N],ans;
ll dfs1(int x,int need,int cnt1,int cnt2,bool lim,bool fz){
	//cnt1 表示为need的个数 cnt2  表示不为need的个数
	if (x==0)	return cnt1>=cnt2; 
	if (!lim and !fz and dp[x][cnt1][cnt2]!=-1) return dp[x][cnt1][cnt2];
	int maxn=lim?s[x]:9;
	ll ret=0;
	for (int i=0;i<=maxn;i++){
		ret+=dfs1(x-1,need,cnt1+((i!=0 or !fz)&(i==need)),cnt2+((i!=0 or !fz)&(i!=need)),lim&(i==maxn),fz&(i==0));
	}
	if (!lim and !fz) return dp[x][cnt1][cnt2]=ret;
	return ret;
}
ll solve1(ll x,int i){
	memset(dp,-1,sizeof dp); 
	cnt=0;
	while(x!=0){
		s[++cnt]=x%10;
		x/=10;
	}
	return dfs1(cnt,i,0,0,1,1);
}
ll dfs2(int x,int k1,int k2,int cnt1,int cnt2,bool lim,bool fz){
	if (x==0)	return cnt1==cnt2;
	if (!lim and !fz and dp[x][cnt1][cnt2]!=-1) return dp[x][cnt1][cnt2];
	int maxn=lim?s[x]:9;
	ll ret=0;
	if(k1<=maxn)ret+=dfs2(x-1,k1,k2,cnt1+(k1!=0 or !fz),cnt2,lim&(k1==maxn),fz&(k1==0));
	if(k2<=maxn)ret+=dfs2(x-1,k1,k2,cnt1,cnt2+(k2!=0 or !fz),lim&(k2==maxn),fz&(k2==0));
	if(k1!=0 and k2!=0 and fz) ret+=dfs2(x-1,k1,k2,cnt1,cnt2,lim&(0==maxn),fz);//考虑前导零 
	if (!lim and !fz) return dp[x][cnt1][cnt2]=ret;
	return ret;
}
ll solve2(ll x,int k,int k1){
	memset(dp,-1,sizeof dp); 
	cnt=0;
	while(x!=0){
		s[++cnt]=x%10;
		x/=10;
	}
	return dfs2(cnt,k,k1,0,0,1,1);
}
int main(){
	cin>>n>>m;
	for(int i=0;i<=9;i++){
		ans+=solve1(m,i)-solve1(n-1,i);//求解超过一半的方案数 
	}
	for(int i=0;i<=9;i++){
		for(int j=i+1;j<=9;j++){
			ans-=solve2(m,i,j)-solve2(n-1,i,j);//减去重复贡献的有两个超过一半的数字的方案数 
		}
	}
	cout<<ans;
 	return 0;
} 
```

---

