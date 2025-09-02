# [CERC2017] Kitchen Knobs

## 题目描述

你正一家大型的快餐餐厅的巨型灶台上烹饪。这个灶台上有n个炉子排成一排，并按序标为1-n号。每个炉子都会被它的控制手柄所控制。这些手柄可不一般：每个手柄上面都有1-7的号码围成一圈。灶台的火力就是从它的控制手柄顶端开始顺时针读取数字而得到的。

【图片】：样例数据1输入的初始手柄位置如图所示。

每一步你都可转动一个或多个相邻手柄——向任意方向转动任意几下。但是，同一步转动的手柄只能向同一方向转动同样的次数。

找到最少的步数来吧所有的炉子都设定到可能的最大火力。

## 样例 #1

### 输入

```
6
9689331
1758824
3546327
5682494
9128291
9443696
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
5941186
3871463
8156346
9925977
8836125
9999999
5987743
```

### 输出

```
2
```

# 题解

## 作者：弦巻こころ (赞：6)

一道比较巧妙的思维题.

转化后题意:给你一个数组,每次可以将$a[i],i\in[l,r]$变成$(a[i]+v)\%7,i\in[l,r],v\in[1,6]$.求使得整个数组变为$0$的最小操作次数.

这个题一看就非常差分,所以我们先差分一下.发现操作变成了,对于差分数组$c[i]$你可以将$c[i]+v,(c[j]-v+7)\%7,i<j$或者只将$c[i]+v$.

就相当于我们将所有$c[i]$分组,使得同一组的$sum\%7=0$(这样同一组就可以用$sz-1$此组全部弄成$0$)并且组数尽可能多.

乍一看好像没啥特别的,但是我们发现$0$是不用操作的,$16,25,34$,两两配对分组是很优秀的.而且配对过后,我们就只剩下3种数了.

我们此时将剩下的数设一个四维$f[i][j][k]$
表示,选了$i$个第一种数,$j$个第二种数,$k$个第三种数,我们发现当$i* v[1]+j* v[2]+k* v[3]=0$时,我们此时组数就可以加一,因为我们此时必然可以通过$i,j,k$的一些组合凑出一组新的$sum$为$0$,转移就是你枚举一个数添加就行了.但$n^3$的空间太大了开不下,我们可以滚动数组或者~~short~~解决问题.

注意你转化的时候,如果那个数字全部相同,那它是没有意义的(咋转都没区别),一定要记得特判这种情况!!!(考场上感觉很难想到这种情况)

转化就是你枚举一下顺时针转几次得到最大值,那个次数就是题目中的$a_i$了

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
const int N=514;
int n,nw,as,mx[N],a[N][8],p[10],c[10],ct[10];
short f[N][N][N];
void MX(short &a,short b){a=a>b?a:b;}
int main(){
	scanf("%d",&n);
	rep(i,1,n){scanf("%d",&a[i][0]);
		if(a[i][0]%1111111==0){i--;n--;continue;}//一定要判,巨坑
		rep(j,1,6){
			a[i][j]=(a[i][j-1]%1000000)*10+a[i][j-1]/1000000;
			if(a[i][mx[i]]<a[i][j])mx[i]=j;
		}
	}//转化mx[i]相当于a[i]
   rep(i,1,n)ct[(mx[i]-mx[i-1]+7)%7]++;
	p[1]=abs(ct[1]-ct[6]);c[1]=ct[1]>ct[6]?1:6;
	p[2]=abs(ct[2]-ct[5]);c[2]=ct[2]>ct[5]?2:5;
	p[3]=abs(ct[3]-ct[4]);c[3]=ct[3]>ct[4]?3:4;//将16,25,34先行配对,0不用管
	as+=max(ct[1],ct[6])+max(ct[2],ct[5])+max(ct[3],ct[4]);
	rep(i,0,p[1])rep(j,0,p[2])rep(k,0,p[3]){
		f[i][j][k]+=(i*c[1]+j*c[2]+k*c[3])%7==0;//这样就可以形成一个新的分组
		MX(f[i+1][j][k],f[i][j][k]);
		MX(f[i][j+1][k],f[i][j][k]);
		MX(f[i][j][k+1],f[i][j][k]);//依次枚举数添加
	}
   printf("%d",as+1-f[p[1]][p[2]][p[3]]);
}
	
```



---

## 作者：初春饰利 (赞：4)

简明题意如下：
    
    有n个转盘，每个转盘上都有着7个数字（1~9），现在每次可以选定一个区间[L,R],将区间内的转盘顺时针同事转动若干次，使每个转盘在最后的时候本身所表示的数字最大（数字表示形式：转盘上小三角所指向的数字为七位数的最高位，然后顺时针依次顺位），问最少要选多少个区间才能满足结果。
    
首先，我们可以通过题面所给的数据，想到可以将此题从一个转盘转化为对一个数列进行操作。不难发现：每个转盘所到达最终状态的旋转次数，要么是确定的，要么怎么转都可以（所有数一致）。所以我们可以将题目转化为：
- 每个转盘应转动的次数为ai。
- 每次可以选择一个区间，加上一个相同的数，使得最终ai%7=0
- 求出最少的选定区间次数

将问题转化于此之后，你可能会想到 玩具积木 这道题，然而这两者是有很大的区别的，在这里不过多提出。

现在，我们可以将a进行差分操作，将区间+操作也进行差分，则问题又能转化为：
- 每次选取两个数，一个加上k，一个减去k
- 用最少的操作次数让所有数mod7等于0

到这步后，显然我们可以设一个b(i)=a(i)-a(i-1)。将区间操作化为点的操作。把bi分成尽量多的组，使每一组的和等于0，原题的答案也就等于n-组数。

无视0，那么一定是16配对，25配对，34配对。这样处理以后最多还有三种数字A,B,C。问题就又变为：将这些数分成最多的组数，使得每组的和为0。

最后就用dp算出答案即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<ctime>
#define MAXN 200005
#define ll long long
#define maxn 15
#define maxs 1000005
#define inf 1e9
#define eps 1e-9
using namespace std;
inline char gc() {
	static char now[1<<16],*S,*T;
	if (T==S) {
		T=(S=now)+fread(now,1,1<<16,stdin);
		if (T==S) return EOF;
	}
	return *S++;
}
inline ll readlong() {
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x*=10;
		x+=ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x*=10;
		x+=ch-'0';
		ch=getchar();
	}
	return x*f;
}
void putint(long long t) {
	int ans[40]= {0};
	for(; t; t/=10)ans[++ans[0]]=t%10;
	for(; ans[0]; ans[0]--)putchar('0'+ans[ans[0]]);
	putchar('\n');
}
const int N=505;
int n;
int a[N];
int A,B,C;
int cnt[7];
int x,y,z;
int ans,m;
int e[N][4];
int f[N][N][N];
int t;
int query(){
	char s[10];
	scanf("%s",s);
	string Ans="";
	for(int i=0;i<7;i++){
		Ans.push_back(s[i]);
	}
	int mask=1,sum=0;
	for(int i=1;i<7;i++){
		string now="";
		for(int j=0;j<7;j++){
			now.push_back(s[(i+j)%7]);
		}
		if(now==Ans){
			mask|=1<<i;
			sum+=i;
		}
		else if(now>Ans){
			mask=1<<i;
			sum=i;
			Ans=now;
		}
	}
	if(mask!=(mask&(-mask))){
		return -1;
	}
	return sum;
}
int main(){
	int T=read();
	while(T--){
		int x=query();
		if(x<0){
			continue;
		}
		a[++n]=x;
	}
	if(!n){
		printf("0\n");
		return 0;
	}
	for(int i=n+1;i;i--){
		a[i]-=a[i-1];
	}
	for(int i=1;i<=n+1;i++){
		a[i]=((a[i]%7+7)%7);
	}
	for(int i=1;i<=n+1;i++){
		cnt[a[i]]++;
	}
//	for(int i=1;i<=7;i++){
//		cout<<cnt[i]<<endl;
//	}
	while(cnt[1]&&cnt[6]){
		cnt[1]--;
		cnt[6]--;
		ans++;
	}
	A=cnt[1]?cnt[1]:cnt[6];
	x=cnt[1]?1:6;
	while(cnt[2]&&cnt[5]){
		cnt[2]--;
		cnt[5]--;
		ans++;
	}
	B=cnt[2]?cnt[2]:cnt[5];
	y=cnt[2]?2:5;
	while(cnt[3]&&cnt[4]){
		cnt[3]--;
		cnt[4]--;
		ans++;
	}
//	cout<<ans<<endl;
	C=cnt[3]?cnt[3]:cnt[4];
	z=cnt[3]?3:4;
	for(int i=0;i<=7;i++){
		for(int j=0;j<=7;j++){
			for(int k=0;k<=7;k++){
				if(i+j+k&&(i*x+j*y+k*z)%7==0){
					e[m][0]=i;
					e[m][1]=j;
					e[m][2]=k;
					e[m++][3]=i+j+k-1;
				}
			}
		}
	}
	for(int i=0;i<=A;i++){
		for(int j=0;j<=B;j++){
			for(int k=0;k<=C;k++){
				if(i+j+k){
					int tmp=inf;
					for(int x=0;x<m;x++){
						if(i>=e[x][0]&&j>=e[x][1]&&k>=e[x][2]){
							tmp=min(tmp,f[i-e[x][0]][j-e[x][1]][k-e[x][2]]+e[x][3]);
						}
					}
					f[i][j][k]=tmp;
				}
			}
		}
	}
	printf("%d\n",ans+f[A][B][C]);

	return 0;
}

```

---

## 作者：exCat (赞：2)

## 简要题意   

有 $n$ 个手柄，手柄上有 $7$ 个数字围成一圈，**手柄的大小为顶端开始顺时针读取数字**，每次选择一个区间，将区间内的手柄向同一方向转动相同的次数。**求最少的步数使所有的炉子都设定到可能的最大火力** 。

## 主要算法   

dp，差分。

## 主要思路   

题目转化 $1$：反向考虑，预处理出每个手柄的最大值的位置，记录每个位置的转动次数，每次操作就是区间加，只要最后每个位置的值模 $p$ 等于 $0$ 即可（相当于从目标通过转动转回初始状态。   

题目转化 $2$：只有区间加，可以通过查分，将区间加转化为两个单点修改。只要差分数组都为 $0$，原数组就满足条件。  

题目转化 $3$：仍然不好做，发现对于一些和为 $7$ 的倍数的数，我们只需要这些数的总数 $−1$ 次“修改两个数”即可处理它们。所以最终答案为（$k$ 为和为 $7$ 的倍数的数集的个数）。

$$
\sum_{i=1}^{k}cnt_{i}-1=n-k
$$

dp 方程：$dp_{a_0,a_1,a_2,a_3,a_4,a_5,a_6}$ 表示 $a_0$ 个 $0$，$a_1$ 个 $1$，$a_2$ 个 $2$ 可以分成最多多少个部分。显然 $O(n^6)$ 已经炸了。   

dp 优化：$0$ 明显不用考虑，同时将尽可能多的 $1$ 和 $6$，$2$ 和 $5$，$3$ 和 $4$ 分在一起。这样将其中一个用完，就只剩 $3$ 个数了，$O(n^3)$ 显然可以。       

dp 转移：考虑加一个元素不增加部份数 ，所以将 $dp_{a_1,a_2,a_3}$ 向 $dp_{a_1+1,a_2,a_3}$，$dp_{a_1,a_2+1,a_3}$，$dp_{a_1,a_2,a_3+1}$ 转移。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=510;
#define int long long
int n,ans,wz[10],col[10],b[N],cnt[10],mx[N];
short f[N][N][N];
signed main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0),cout.tie(0); 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		bool flag=1;
		cin>>wz[0];
		if(wz[0]%1111111==0)
		{
			i--,n--;
			continue;
		}
		for(int j=1;j<=6;j++)
		{
			wz[j]=(wz[j-1]%1000000)*10+wz[j-1]/1000000;
			if(wz[j]>wz[mx[i]])mx[i]=j;
		}
	}
	for(int i=1;i<=n;i++)cnt[(mx[i]-mx[i-1]+7)%7]++;
//	for(int i=1;i<=6;i++)cout<<cnt[i]<<' '; 
	ans+=max(cnt[1],cnt[6])+max(cnt[2],cnt[5])+max(cnt[3],cnt[4]);
	col[1]=cnt[1]>cnt[6]?1:6;col[2]=cnt[2]>cnt[5]?2:5;col[3]=cnt[3]>cnt[4]?3:4;
	cnt[3]=abs(cnt[3]-cnt[4]);cnt[1]=abs(cnt[1]-cnt[6]);cnt[2]=abs(cnt[2]-cnt[5]);
	for(int a1=0;a1<=cnt[1];a1++)
		for(int a2=0;a2<=cnt[2];a2++)
			for(int a3=0;a3<=cnt[3];a3++)
			{
				f[a1][a2][a3]+=(a3*col[3]+a2*col[2]+a1*col[1])%7==0;
				f[a1+1][a2][a3]=max(f[a1+1][a2][a3],f[a1][a2][a3]);
				f[a1][a2+1][a3]=max(f[a1][a2+1][a3],f[a1][a2][a3]);
				f[a1][a2][a3+1]=max(f[a1][a2][a3+1],f[a1][a2][a3]);				
			}

	printf("%lld\n",ans+1-f[cnt[1]][cnt[2]][cnt[3]]);
	return 0;
}
```

## 注意事项
如果所有数相同则没有最优位置，直接不管就行了。

---

## 作者：JoshAlMan (赞：2)

考虑 $7$ 是个质数，因此要么一个轮盘数字全一样就是怎么转就行，即没有限制，要么就是有唯一的旋转位置。把怎么转都行的剔除掉。

考虑把这个环的东西弄成模意义的数值问题，设位置状态是 $i$，意义即顺时针转 $i$ 次的状态，在 $\bmod 7$ 意义下。那么问题就变成了一个序列，最初全为 $0$，有一个目标状态 $a$ 数组，每次可以连续选一段 $+k$，问最少操作多少次变成目标状态。

考虑是操作是互逆的，可以将初始和目标反转，又考虑这个连续的一段操作，可以用差分变成两个点的操作，设 $b$ 为 $a$ 的差分数组，那么问题转化为：

* 一个操作可以选择一个 $l < r$ 和 $k$， 使得 $b[l]$ 加 $k$，$b[r]$ 减 $k$。

问变成全 $0$ 最少操作次数。

这个东西还是不太好做，考虑转化。发现一个关键性质就是每次操作不改变 $b$ 的和。考虑一组最优解，把每次选择的 $l, r$ 之间连边，那么对于每一个大小为 $cnt$ 的连通图而言，需要满足他们的 $b$ 的和模意义是 $0$，并且至少操作 $cnt - 1$ 次，如果我们能构造出一种 $cnt - 1$ 次数的答案。因此就可以说明一定存在一组最优解是分成若干组，并且使用的是我们的这种构造方式，那么我们只需要求这种方式的最优值就好了。那么问题就等价于：

* 把序列分成若干组，每组的 $b$ 和为 $0$。设有 $k$ 组，每组大小是 $cnt_i$，答案即 $\sum_{i=1}^k (cnt_i - 1) = n - k$。

------

构造的证明：

考虑把这些点从左到右排序，依次是 $p_1, p_2, p_3,..., p_{cnt}$。

考虑第 $i$ 次操作，前 $i - 1$ 个都变成 $0$ 了，现在让 $b_{p_i}$ 变成 $0$。

让 $l = p_i, r = p_{i+1}, k = 7 - b_{p_i}$ 就好了。

因为和是 $0$，因此前 $cnt - 1$ 变成 $0$ 了，最后一个也是 $0$。

------

因此我们需要最大化分的组数。

直接求是一个非常大的背包不太可做。

我们先考虑把 $a + b = 7$ 这样大小可以为 $2$ 的组给安排了。

那么最终 $1, 6$ 、$2, 5$，$3, 4$，三种组，分配后剩下每组最多只有一种，因此剩下的数字种类最多 $3$ 个。

用这三个（设为 $x, y, z$）用的数量做一个三位背包就好了，考虑物品 $i\times x +j\times y+  k \times z$，必须满足 $i, j, k < 7, \gcd(i,j,k) = 1$（还有单独七个特判），否则可以继续分成两半，更优，可以打表发现物品个数最多是 $41$ 个。

设剩下的数字种类每个数分别 $A_1, A_2, A_3$。

那么时间复杂度是 $O(\prod A \times 41)$。

用均值不等式发现这个东西最大是 $2e8$ 左右，可以苟过。



---

## 作者：ax_by_c (赞：0)

下文计算都在模 $7$ 意义下。

首先 $7$ 是个质数，所以循环节长度只可能是 $1$ 或 $7$，也就是说一个炉子要么只有一种最优方案，要么全部都是最优方案。

将全部都是最优方案的炉子删掉，问题相当于给定数组 $a$，每次操作可以给一个区间加上一个数，求使 $a$ 中元素全部变为零所需的最小操作次数。

考虑差分，令 $a'_i=a_i-a_{i-1}$，那么原操作相当于 $a'_l\leftarrow a'_l+x,a'_{r+1}\leftarrow a'_{r+1}-x$。

问题相当于从 $a'$ 找出尽可能多的互不相交的组，且每组数的和为零。因为如果有 $m$ 个数的和为零就可以用 $m-1$ 次操作使它们都变为零，所以答案就是 $n$ 减去组数。

显然可以先提出 $\{0\},\{1,6\},\{2,5\},\{3,4\}$，提完后至多只会剩下三种不同的数。

考虑 dp，设 $f_{i,j,k}$ 表示三种数各有 $i,j,k$ 个时可能的最大组数。

考虑将这些数排列，所有组排在最前面，那么组数就等于前缀和为零的位置个数。于是只需在平凡转移时和为零处加一即可。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int N=505;
const int V=7;
int n,m,a[N],cnt[V],a_[3],xx,f[N][N][N];
void chk(int &x,int y){
	x=(x>y)?(x):(y);
}
void main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		bool fd=0;
		for(auto it:s)if(it!=s[0])fd=1;
		if(!fd)continue;
		a[++m]=0;
		string mx=s;
		for(int j=1;j<=6;j++){
			string tmp="";
			for(int k=1;k<=6;k++)tmp+=s[k];
			tmp+=s[0];
			s=tmp;
			if(s>mx){
				mx=s;
				a[m]=j;
			}
		}
	}
	n=m;
	for(int i=n;i>=1;i--)a[i]-=a[i-1],cnt[(a[i]%7+7)%7]++;
	int ans=cnt[0];
	cnt[0]=0;
	for(int i=1,j=6,k;i<=j;i++,j--){
		k=min(cnt[i],cnt[j]);
		cnt[i]-=k,cnt[j]-=k,ans+=k;
	}
	for(int i=0;i<7;i++)if(cnt[i])a_[xx++]=i;
	for(int i=0;i<=cnt[a_[0]];i++)
	for(int j=0;j<=cnt[a_[1]];j++)
	for(int k=0;k<=cnt[a_[2]];k++){
		int s=a_[0]*i+a_[1]*j+a_[2]*k;
		chk(f[i+1][j][k],f[i][j][k]+bool((s+a_[0])%7==0));
		chk(f[i][j+1][k],f[i][j][k]+bool((s+a_[1])%7==0));
		chk(f[i][j][k+1],f[i][j][k]+bool((s+a_[2])%7==0));
	}
	ans+=f[cnt[a_[0]]][cnt[a_[1]]][cnt[a_[2]]];
	printf("%d\n",n-ans);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [Kitchen Knobs](https://www.luogu.com.cn/problem/P4749)

首先，一个 trivial 的想法是，因为每个旋钮如果上面的数字并非全部相同则其必有唯一最优位置，故直接扔掉那些全部相同的旋钮，对于剩余的求出其最优位置。明显此位置是一 $0\sim6$ 的数。

因为是区间同时旋转，所以转成数之后就是区间加同一个数。

一个经典套路是差分。这样就变成了每次同时修改序列中的两个数，一个加 $x$，另一个减 $x$。当然，还可以只修改一个位置到任意值。

然后我们发现，对于一些和为 7 的倍数的数，我们只需要这些数的总数 $-1$ 次“修改两个数”即可处理它们。

然后我们又发现，首先那些本身就是 0 的数可以直接扔掉，再怎么搞都不会修改到它们；这样的话，每次合并所能省下的次数最多只是 $50\%$，因此我们一定会合并那些 $50\%$ 的方案，即合并 $(1,6),(2,5),(3,4)$。

这样合并完后，我们发现最多只剩下 3 种不同的数，因此一个 $n^3$ 的 DP 就可以构思出来了。

然后我们还需要知道所有的和为 7 的组合。并且，这些组合必须是极小组合。于是我们直接 $7^3$ 枚举三个数的次数，再 $7^3$ 枚举其子集验证其是否是极小组合即可。

最后别忘记算 $(7,0,0),(0,7,0),(0,0,7)$ 这三种组合！！！因为没有考虑到这个我挂了很久。

这样一通算下来，极小组合数可以被视作很小的常数。于是直接 $n^3$ 的 DP 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,cmp,res,cnt;
int a[N],f[N][N][N],g[N][4],tot[8],lim[4],num[4];
string s,t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
		t=s;
        bool as=true;
        for(int j=1;j<7;j++) if(s[j]!=s[0]){as=false;break;}
        if(as){
			i--;
			n--;
			continue;
		}
        for(int j=0;j<7;j++){
			rotate(s.begin(),s.begin()+1,s.end());
			t=max(t,s);
		}
        for(int j=0;j<7;j++){
            if(s==t){
				a[i]=j;
				break;
			}
            rotate(s.begin(),s.begin()+1,s.end());
        }
    }
    n++;
    for(int i=n;i>=2;i--) a[i]=(a[i]-a[i-1]+7)%7;
    for(int i=1;i<=n;i++) tot[a[i]]++;
    for(int i=1,x;i<=3;i++){
		x=min(tot[i],tot[7-i]);
		tot[i]-=x;
		tot[7-i]-=x;
		n-=x;
	}
    n-=tot[0];
    for(int i=1;i<7;i++){
		if(tot[i]){
			lim[cmp]=tot[i];
			num[cmp]=i;
			cmp++;
		}
	}
    for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			for(int k=0;k<7;k++){
				if((i*num[0]+j*num[1]+k*num[2])%7) continue;
				if(!i&&!j&&!k) continue;
				bool ok=true;
				for(int I=0;I<=i;I++){
					for(int J=0;J<=j;J++){
						for(int K=0;K<=k;K++){
							if((I*num[0]+J*num[1]+K*num[2])%7) continue;
							if((!I&&!J&&!K)||(i==I&&j==J&&k==K)) continue;
							ok=false;break;
						}
					}
				}
				if(ok){
					g[cnt][0]=i;
					g[cnt][1]=j;
					g[cnt][2]=k;
					cnt++;
				}
			}
		}
	}
    g[cnt][0]=7;g[cnt][1]=0;g[cnt][2]=0;cnt++;
    g[cnt][0]=0;g[cnt][1]=7;g[cnt][2]=0;cnt++;
    g[cnt][0]=0;g[cnt][1]=0;g[cnt][2]=7;cnt++;
    for(int i=0;i<=lim[0];i++){
		for(int j=0;j<=lim[1];j++){
			for(int k=0;k<=lim[2];k++){
				for(int l=0;l<cnt;l++){
					if(i<g[l][0]||j<g[l][1]||k<g[l][2]) continue;
					f[i][j][k]=max(f[i][j][k],f[i-g[l][0]][j-g[l][1]][k-g[l][2]]+1);
				}
				res=max(res,f[i][j][k]);
			}
		}
	}
    cout<<n-res;
    return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/P4749)

一道挺有意思的思维题。

首先有一个 obvious 的结论，那就是 $7$ 是质数，故对于每个炉子，要么转到哪里都符合条件，要么存在唯一的最大值。对于转到哪儿都符合条件的炉子我们 duck 不必考虑它，故我们只用考虑存在唯一最大值的炉子即可，我们记 $a_i$ 表示第 $i$ 个炉子需顺时针旋转多少次才能到达火力最大的位置，那么对一个区间 $[l,r]$ 进行逆时针旋转 $c$ 格的操作就等价于令 $[l,r]$ 中的 $a_i$ 在模 $7$ 意义下全部加 $c$，我们要求最少多少次操作才能将其全变为 $0$。

这里涉及区间加，因此套路地考虑**差分**，记差分序列为 $b$，那么一个区间 $+c$ 即可转化为两个单点加。乍一看还是不太好做，不过注意如果我们考虑在每次选择的两个点 $x,y$ 中连一条边，那么最终会得到一张 $cnt$ 条边的图，其中 $cnt$ 为操作次数。显然每次单点加操作并不改变 $b$ 数组的和，而对于图中的每个连通块，该连通块中的点最终的 $b_i$ 之和为 $0$，故一开始他们 $b_i$ 的和也是 $0$，因此我们可以将题目转化为，将所有 $b_i$ 划分为尽可能多的组，满足每组的和模 $7$ 余 $0$，答案就是 $n-$划分次数。

这个划分次数怎么求呢？我们首先求出 $cnt_v$ 表示有多少个 $b_i=v$，首先 $0$ 肯定是单独成一组的，产生 $cnt_0$ 的贡献，接下来我们肯定希望划分出大小为 $2$ 的组，而大小为 $2$ 的组肯定只能由 $(1,6),(2,5),(3,4)$ 配对得到，这样两两配对又能产生一些贡献，配完对后就只剩下三种数 $x,y,z$ 了，此时可以直接 $dp_{i,j,k}$ 表示还剩 $i$ 个 $x$，$j$ 个 $y$，$k$ 个 $z$ 最多可以划分为多少组，转移 $\mathcal O(1)$，总复杂度 $\dfrac{n^3}{27}$，跑得飞快（

```cpp
const int MAXN=501;
int n,m,a[MAXN+5],cnt[7],ans=0,dp[MAXN+5][MAXN+5][MAXN+5];
pair<int,int> clr(int x,int y){
	return (cnt[x]>cnt[y])?(ans+=cnt[y],mp(x,cnt[x]-cnt[y])):(ans+=cnt[x],mp(y,cnt[y]-cnt[x]));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		string s;cin>>s;bool flg=0;
		for(int j=0;j<7;j++) if(s[j]!=s[0]) flg=1;
		if(!flg) continue;
		vector<pair<string,int> > vec;
		for(int j=0;j<7;j++){
			string str;
			for(int k=j,stp=0;stp<7;stp++,k=(k+1)%7) str=str+s[k];
			vec.pb(mp(str,j));
		} sort(vec.begin(),vec.end());
		reverse(vec.begin(),vec.end());
		a[++m]=vec[0].se;
	}
	for(int i=m;i;i--) a[i]=(a[i]-a[i-1]+7)%7,cnt[a[i]]++;
	ans=cnt[0];
	pair<int,int> p1=clr(1,6);
	pair<int,int> p2=clr(2,5);
	pair<int,int> p3=clr(3,4);//printf("%d\n",ans);
//	printf("%d %d %d\n",p1.fi,p2.fi,p3.fi);
//	printf("%d %d %d\n",p1.se,p2.se,p3.se);
	for(int i=0;i<=p1.se;i++) for(int j=0;j<=p2.se;j++) for(int k=0;k<=p3.se;k++){
		chkmax(dp[i+1][j][k],dp[i][j][k]+!(((i+1)*p1.fi+j*p2.fi+k*p3.fi)%7));
		chkmax(dp[i][j+1][k],dp[i][j][k]+!((i*p1.fi+(j+1)*p2.fi+k*p3.fi)%7));
		chkmax(dp[i][j][k+1],dp[i][j][k]+!((i*p1.fi+j*p2.fi+(k+1)*p3.fi)%7));
	} printf("%d\n",m-(ans+dp[p1.se][p2.se][p3.se]));
	return 0;
}
```



---

