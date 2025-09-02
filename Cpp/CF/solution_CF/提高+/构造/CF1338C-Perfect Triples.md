# Perfect Triples

## 题目描述

Consider the infinite sequence $ s $ of positive integers, created by repeating the following steps:

1. Find the lexicographically smallest triple of positive integers $ (a, b, c) $ such that 
  - $ a \oplus b \oplus c = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
  - $ a $ , $ b $ , $ c $ are not in $ s $ .
  
   Here triple of integers $ (a_1, b_1, c_1) $ is considered to be lexicographically smaller than triple $ (a_2, b_2, c_2) $ if sequence $ [a_1, b_1, c_1] $ is lexicographically smaller than sequence $ [a_2, b_2, c_2] $ .
2. Append $ a $ , $ b $ , $ c $ to $ s $ in this order.
3. Go back to the first step.

You have integer $ n $ . Find the $ n $ -th element of $ s $ .

You have to answer $ t $ independent test cases.

A sequence $ a $ is lexicographically smaller than a sequence $ b $ if in the first position where $ a $ and $ b $ differ, the sequence $ a $ has a smaller element than the corresponding element in $ b $ .

## 说明/提示

The first elements of $ s $ are $ 1, 2, 3, 4, 8, 12, 5, 10, 15, \dots  $

## 样例 #1

### 输入

```
9
1
2
3
4
5
6
7
8
9```

### 输出

```
1
2
3
4
8
12
5
10
15```

# 题解

## 作者：ix35 (赞：9)

红名了，纪念一下。

这题一开始看不出任何东西，于是写了下面这个程序打了个表：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int cnt,vis[MAXN];
int main () {
	for (int i=1;i<=10000;i++) {
		if (vis[i]) {continue;}
		for (int j=i+1;j<=10000;j++) {
			int flg=0;
			if (vis[j]) {continue;}
			for (int k=j+1;k<=10000;k++) {
				if (vis[k]) {continue;}
				if (i^j^k) {continue;}
				printf("%d:   %d %d %d\n",++cnt,i,j,k);
				vis[i]=vis[j]=vis[k]=1;
				flg=1;
				break;
			}
			if (flg) {break;}
		}
	}
	return 0;
}
```

表大概长这样（局部：

![](https://cdn.luogu.com.cn/upload/image_hosting/m4i3mdwz.png)

然后可以总结出如下规律:

1. $a$ 的取值把序列分成了若干块，每一块内的 $a$ 都是从 $2^k$ 到 $2^{k+1}-1$ 的连续整数。

2. 同一块内，$b$ 的取值可以递归构造。每次将大块分成四小块，分别取第 $1,3,4,2$ 小的值。

3. 同一块内，$c$ 的取值可以递归构造。每次将大块分成四小块，分别取第 $1,4,2,3$ 小的值。

于是我们先搞出 $n$ 在哪一块，如果是 $a$ 可以直接返回，如果是 $b,c$ 就递归构造即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll calc2 (ll x,ll y) {
	if (x==1) {return 1;}
	else {
		ll t=x/4;
		if (y<=t) {return calc2(t,y);}
		else if (y<=2*t) {return calc2(t,y-t)+2*t;}
		else if (y<=3*t) {return calc2(t,y-2*t)+3*t;}
		else {return calc2(t,y-3*t)+t;}
	}
}
ll calc3 (ll x,ll y) {
	if (x==1) {return 1;}
	else {
		ll t=x/4;
		if (y<=t) {return calc3(t,y);}
		else if (y<=2*t) {return calc3(t,y-t)+3*t;}
		else if (y<=3*t) {return calc3(t,y-2*t)+t;}
		else {return calc3(t,y-3*t)+2*t;}
	}
}
ll t,n;
ll calc (ll n) {
	ll tmp=n%3;
	n=(n+2)/3;
	ll pos=0,cnt=0;
	while (pos+(1ll<<cnt)<n) {
		pos+=(1ll<<cnt);
		cnt+=2;
	}
	ll res=3*pos;
	if (tmp==1) {
		return res+(n-pos);
	} else if (tmp==2) {
		return res+(1ll<<cnt)+calc2(1ll<<cnt,n-pos);
	} else {
		return res+(1ll<<(cnt+1))+calc3(1ll<<cnt,n-pos);
	}
}
int main () {
	scanf("%lld",&t);
	for (int ii=1;ii<=t;ii++) {
		scanf("%lld",&n);
		printf("%lld\n",calc(n));
	}
	return 0;
}
```










---

## 作者：feecle6418 (赞：6)

#### Update：修改了笔误

我的代码非常短。

最开始没看出什么规律，于是我花了 30 分钟写出了 前 42 个数。

前 15 个没啥规律，唯一引人注目的就是它覆盖了 1 至 15 的所有数：

$$1,2,3,4,8,12,5,10,15,6,11,13,7,9,14,\cdots$$

继续写（鬼知道我怎么那么有耐心）：

$$16,32,48,17,34,51,18,35,49,19,33,50$$

$$20,40,60,21,42,63,22,43,61,23,41,62$$

$$24,44,52,\cdots$$

你应该可以容易地发现：$3$ 个 $3$ 个分组，第一个数总是从 $2^{2k}$ 开始顺序排列，到 $2^{2k+1}-1$，这些三元组刚好覆盖完 $2^{2k}\sim2^{2k+2}-1$ 的所有数。

可是后面两个数没啥规律，，，考虑写出二进制表示。显然第一个数异或第二个数等于第三个数，只需求第二个即可。

第二个数显然是大于等于 $2^{2k+1}$ 的，考虑写出其相对于 $2^{2k+1}$ 的增量。

写出来是这样的：

$$00000$$

$$00010$$

$$00011$$

$$00001$$

$$01000$$

$$01010$$

$$01011$$

$$01001$$

$$01100$$

看出来了吗？从最后两位开始，每两位都从 $00\to 10\to 11\to 01$ 递变！于是写出代码就很容易了。

代码如下。一些 $+1-1$ 的细节需要自己斟酌一下。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
ll n,f[]={0,1,2,3,4,8,12,5,10,15,6,11,13,7,9,14},ff[]={0,2,3,1};
int main() {
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		ll tmp=n;
		if(n<=15){
			printf("%lld\n",f[n]);
			continue;
		}
		ll now=0;
		while(tmp)tmp/=4,now++;
		tmp=(n+2)/3;
		ll from=(1ll<<(2*(now-1)))+(n-(1ll<<(2*(now-1))))/3;
		if(n%3==1)printf("%lld\n",from);
		else {
			ll sx=(n-(1ll<<(2*(now-1))))/3;
			ll tmp=(1ll<<(2*now-1));
			ll ii=1;
			while(sx)tmp+=ii*ff[sx%4],sx/=4,ii*=4;
			if(n%3==2)printf("%lld\n",tmp);
			else printf("%lld\n",from^tmp);
		}
	}
}
```

---

## 作者：wwwwwza (赞：2)

找规律题，先打表：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
int n;
bool vis[N];
signed main(){
	cin >>n;
	for(int i=1;i<=n;i++){
		cout <<"Case "<<i<<": ";
		int a=1;
		while(vis[a])a++;
		vis[a]=1;
		int b=a;
		while(vis[b]||vis[a^b])b++;
		vis[b]=vis[a^b]=1;
		int c=a^b;
		cout <<a<<" "<<b<<" "<<c<<endl;
	}
	return 0;
}
```
[表格](https://www.luogu.com.cn/paste/6qs3fgct)

我们先看 $a$ 的规律：$1,4,5,6,7,16,17,18,\cdots$   
发现好像少了点什么，只剩：$2^{2n}$ 到 $2^{2n+1}-1$ 的数了 $(n\in\mathbb{N})$。  
按这个规律我们就可以求出 $a$。   
```cpp
int rec(int x){
	int ans=1,pos=1;
	while(pos+ans<=x){//枚举每一个块的长度 
		pos+=ans;
		ans*=4;
	}
	return ans+(x-pos);
}
```

接着看 $b$ 的规律，按 $a$ 的规律。  
可以看出这是一个可递归构造的数列：将这一大块分为四小块，这四个小块的首位的大小顺序分别为：$1,3,4,2$。   
```cpp
int dfs(int st,int r){//每一个大块的第一个数的位置，大块的长度 
	if(r==0)return 0;
	if(st<=r){//按顺序递推 
		return 0*r+dfs(st-0*r,r/4);
	}else if(st<=2*r){
		return 2*r+dfs(st-1*r,r/4);
	}else if(st<=3*r){
		return 3*r+dfs(st-2*r,r/4);
	}else{
		return 1*r+dfs(st-3*r,r/4);
	}
}
```


$c$ 就好办了，题目说：$a\otimes b\otimes c=0$，所以 $a\otimes b=c$。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
struct node{
	int a,b,c;
};
int dfs(int st,int r){//每一个大块的第一个数的位置，大块的长度 
	if(r==0)return 0;
	if(st<=r){//按顺序递推 
		return 0*r+dfs(st-0*r,r/4);
	}else if(st<=2*r){
		return 2*r+dfs(st-1*r,r/4);
	}else if(st<=3*r){
		return 3*r+dfs(st-2*r,r/4);
	}else{
		return 1*r+dfs(st-3*r,r/4);
	}
}
node rec(int x){//计算答案 
	node end;
	int ans=1,pos=1;
	while(pos+ans<=x){//枚举每一个块的长度 
		pos+=ans;
		ans*=4;
	}
	end.a=ans+(x-pos);//为了方便我就放一起了 
	end.b=dfs(x-pos+1,ans/4)+ans*2;//每一个大块从0开始枚举比较方便 
	end.c=end.a^end.b;
	return end;
}
signed main(){
	cin >>t;
	while(t--){
		cin >>n;
		node p=rec((n-1)/3+1);//题目中三个为一组 
		if(n%3==1)cout <<p.a<<endl;
		else if(n%3==2)cout <<p.b<<endl;
		else cout <<p.c<<endl;
	}
	return 0;
}

```

---

## 作者：Lynkcat (赞：2)

乱搞做法，同样是找规律。

举个例子：

```
0000000000000000000000000011011
0000000000000000000000000101101
0000000000000000000000000110110

0000000000000000000000000011100
0000000000000000000000000100100
0000000000000000000000000111000

0000000000000000000000000011101
0000000000000000000000000100110
0000000000000000000000000111011

0000000000000000000000000011110
0000000000000000000000000100111
0000000000000000000000000111001
```

这些事我打表出来的四组合法的数，不难发现两位两位分块能发现

```
10
11
01
```

```
01
10
11
```

```
11
01
10
```

也就是说我们只要找到这三个数中任意一个的规律，其他两个自然也就迎刃而解。

于是我打出了所有第一个数的表：

```
0000000000000000000000000000001
0000000000000000000000000000100
0000000000000000000000000000101
0000000000000000000000000000110
0000000000000000000000000000111
0000000000000000000000000010000
0000000000000000000000000010001
0000000000000000000000000010010
0000000000000000000000000010011
0000000000000000000000000010100
0000000000000000000000000010101
0000000000000000000000000010110
0000000000000000000000000010111
0000000000000000000000000011000
0000000000000000000000000011001
0000000000000000000000000011010
0000000000000000000000000011011
0000000000000000000000000011100
0000000000000000000000000011101
0000000000000000000000000011110
```

不难发现，是 $2^0+2^2+2^4……$ 依次迭代下去，可以轻松计算所有的 $a$ 。

然后这道题就解决了。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 1000000007
#define Endl endl
#define int ll
//#define N
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int T,n,v,sum,ans,now;
signed main()
{
	T=read();
	while (T--)
	{
		n=read();
		int u=(n-1)%3+1;sum=0;
		if (u==1)
		{
			n=(n-1)/3;
			for (int i=0;i<=63;i+=2)
			{
				if ((1ll<<i)+sum>n) 
				{
					now=i;
					break;
				}
				sum+=(1ll<<i);
			}
			writeln((1ll<<now)+n-sum);
		} else
		if (u==2)
		{
			n=(n-1)/3;
			for (int i=0;i<=63;i+=2)
			{
				if ((1ll<<i)+sum>n) 
				{
					now=i;
					break;
				}
				sum+=(1ll<<i);
			}
			v=(1ll<<now)+n-sum;ans=v;
			for (int i=0;i<=63;i+=2)
			{
				int p=((v>>i)&1),p1=(v>>(i+1))&1;
				if (p&&p1) ans^=(1ll<<(i+1));
				if (p&&!p1) ans^=(1ll<<i),ans^=(1ll<<(i+1));
				if (!p&&p1) ans^=(1ll<<i);
			}
			writeln(ans);
		} else
		{
			n=(n-1)/3;
			for (int i=0;i<=63;i+=2)
			{
				if ((1ll<<i)+sum>n) 
				{
					now=i;
					break;
				}
				sum+=(1ll<<i);
			}
			v=(1ll<<now)+n-sum;ans=v;
			for (int i=0;i<=63;i+=2)
			{
				int p=((v>>i)&1),p1=(v>>(i+1))&1;
				if (p&&p1) ans^=(1ll<<i);
				if (p&&!p1) ans^=(1ll<<(i+1));
				if (!p&&p1) ans^=(1ll<<i),ans^=(1ll<<(i+1));
			}
			writeln(ans);
		}
	}
			
}
/*

*/

```

---

## 作者：gyh20 (赞：2)

最开始单纯的以为是 $x,2x,3x$ 的形式，WA了。

直接规律不好找，打个表最简单暴力。

[前 $100$ 组](https://www.luogu.com.cn/paste/1sjvzrr5)（太长了，不放在题解页面）

[打表代码](https://www.luogu.com.cn/paste/ze3tjape)（题解篇幅有限，难度不高，也放在剪贴板）

可以发现，第一个数都是 $2^k\sim 2^{k+1}-1,k\equiv 0\pmod 2$。

观察一下第二个数

先按第一个数的大小分组，看每一组内的关系：

假设第一个数在 $2^k\sim 2^{k+1}-1$ 之间，那么第二个数在$2^{k+1}\sim 2^{k+1}+2^{k}-1$ 范围内，令 $x$ 为 $2^k$，假设分成四部分 $a,b,c,d$，其中每部分占四分之一，那么最后的组合是 $a,c,d,b$，对于 $a,b,c,d$ 再分成四个块分别处理节课。

第三个数其实就是第一个数异或第二个数。

所以，我们对于每一个 $n$ ，只需要找到它在哪一排即可。

时间复杂度：$O(T\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
} 
int n,t,l,r;
inline int work(re int x,re int y){
	if(y==0)return x;
	re int p=y/4;
	if(x<p)return work(x,y/4);
	else if(x<2*p)return work(x-p,y/4)+y/2;
	else if(x<3*p)return work(x-2*p,y/4)+3*y/4;
	else return work(x-3*p,y/4)+y/4;
}
signed main(){
	t=read();
	while(t--){
		re int m=read();
		n=(m-1)/3+1;
		re int b=1,siz=0;
		while(siz<n)siz+=b,b*=4;siz-=b/4;
		re int xx=n-siz-1;n=b/4+n-siz-1;
		re int ans=work(n-b/4,b/4)+b/2;
		if(m%3==1){
			printf("%lld\n",n);
			continue;
		}
		else if(m%3==2){
			printf("%lld\n",ans);
			continue;
		}
		else printf("%lld\n",ans^n);
	}
}
```
（这次怎么全都是规律题啊）


---

## 作者：VenusM1nT (赞：1)

结论。

不是一道难题，但是是一道烦题（可能是因为我太 naive）  
初看没什么想法，先打个表，以三个为一组，看看能不能找到规律。  
打表程序如下。
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
using namespace std;
int n;
bool fg[MAXN];
int main()
{
	freopen("1.txt","w",stdout);
	for(reg int i=1;i<=1000;i++)
	{
		if(fg[i]) continue;
		for(reg int j=i+1;j<=1000;j++)
		{
			if(fg[j]) continue;
			reg int k=i^j;
			if(fg[k]) continue;
			fg[i]=fg[j]=fg[k]=1;
			printf("%d %d %d\n",i,j,k);
			break;
		}
	}
	return 0;
}
```
打出一个这样的表：
```cpp
1 2 3
4 8 12
5 10 15
6 11 13
7 9 14
16 32 48
17 34 51
18 35 49
19 33 50
20 40 60
21 42 63
22 43 61
23 41 62
24 44 52
25 46 55
26 47 53
27 45 54
28 36 56
29 38 59
30 39 57
31 37 58
64 128 192
...
```
一眼看上去没什么规律，但可以发现：  
1. 以每 $2^{2k}$ 组数为一个大组，发现每个组内的数正好取满 $[2^{2(k-1)},2^{2k})$ .  
2. 第一排数在各自的大组内递增。

虽然没什么大作用，但我们至少知道了第一排数，也就是 $n\equiv1\pmod3$ 这组的规律，可以倍增推出。

然后我们再来看第二排，想到这是一个异或的题，于是大力拆成二进制。程序如下：
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
using namespace std;
int n,t[15];
bool fg[MAXN];
void Bit(reg int x)
{
	memset(t,0,sizeof(t));
	reg int i=1;
	while(x)
	{
		t[i]=x%2;
		x/=2;
		i++;
	}
	for(reg int i=11;i>=1;i--) printf("%d",t[i]);
	printf(" ");
}
int main()
{
	freopen("2.txt","w",stdout);
	reg int tot=0;
	for(reg int i=1;i<=1000;i++)
	{
		if(fg[i]) continue;
		for(reg int j=i+1;j<=1000;j++)
		{
			if(fg[j]) continue;
			reg int k=i^j;
			if(fg[k]) continue;
			tot++;
			fg[i]=fg[j]=fg[k]=1;
			Bit(i); Bit(j); Bit(k);
			puts("");
			break;
		}
	}
	return 0;
}
```

打出一张这样的表（我自己分了一下类）：

```cpp
00000000001 00000000010 00000000011 

00000000100 00000001000 00000001100 
00000000101 00000001010 00000001111 
00000000110 00000001011 00000001101 
00000000111 00000001001 00000001110 

00000010000 00000100000 00000110000 
00000010001 00000100010 00000110011 
00000010010 00000100011 00000110001 
00000010011 00000100001 00000110010 

00000010100 00000101000 00000111100 
00000010101 00000101010 00000111111 
00000010110 00000101011 00000111101 
00000010111 00000101001 00000111110 

00000011000 00000101100 00000110100 
00000011001 00000101110 00000110111 
00000011010 00000101111 00000110101 
00000011011 00000101101 00000110110 

00000011100 00000100100 00000111000 
00000011101 00000100110 00000111011 
00000011110 00000100111 00000111001 
00000011111 00000100101 00000111010 

00001000000 00010000000 00011000000 
...
```

忽略第一行，观察第二列，发现末尾两个数字是

$$00 \to 10 \to 11 \to 01$$

这样一个循环，再观察倒数第三第四两个数字，发现它们也符合上面这个循环，而且这个循环正好在 $2^{2k}$ 这样一个大小的组内循环，且每种情况正好占据它的 $\frac{1}{4}$，至此我们的解法就出来了。对于 $n\equiv 2 \pmod 3$ 的情况，我们先取到它的最大组，然后分四种情况大力分别讨论就可以解决了。

虽然说着很简单，但其实还是调了挺久的……边界条件太恶心了……

至于 $n\equiv 0\pmod 3$ 的情况，我们记上面求出的两个东西分别为 $A$ 和 $B$，那么 $n\equiv 0\pmod 3$ 时的答案就是 $A \oplus B$，因为只有这样才能使得异或和为 0。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,_[65],A,B,C;
void Calc(reg int l,reg int r,reg int x)
{
	B<<=2;
	if(r-l+1==4)
	{
		if(x%4==1) B+=0;
		if(x%4==2) B+=2;
		if(x%4==3) B+=3;
		if(x%4==0) B+=1;
		return;
	}
	reg int len=r-l+1;
	if(l<=x && x<l+len/4)
	{
		B+=0;
		Calc(l,l+len/4-1,x);
	}
	if(l+len/4<=x && x<l+len/2)
	{
		B+=2;
		Calc(l+len/4,l+len/2-1,x);
	}
	if(l+len/2<=x && x<l+len/4*3)
	{
		B+=3;
		Calc(l+len/2,l+len/4*3-1,x);
	}
	if(l+len/4*3<=x && x<l+len)
	{
		B+=1;
		Calc(l+len/4*3,l+len-1,x);
	}
}
inl void Find(reg int x,reg int maxn)
{
	reg int sum=0;
	for(reg int i=1;i<=maxn;i++)
	{
		sum+=_[i];
		if(sum>=x)
		{
			Calc(max(1ll,sum-_[i]+1),sum,x);
			break;
		}
	}
}
signed main()
{
	//freopen("1.txt","r",stdin);
	int Time;
	scanf("%lld",&Time);
	_[0]=1;
	for(reg int i=1;i<=60;i++) _[i]=_[i-1]<<2ll;
	while(Time--)
	{
		A=B=C=0;
		scanf("%lld",&n);
		if(n<=3)
		{
			printf("%lld\n",n);
			continue;
		}
		reg int unt=n/3;
		if(!(n%3)) unt--;
		reg int sum=0;
		for(reg int i=1;i<=60;i++)
		{
			sum+=_[i];
			if(sum>=unt)
			{
				reg int pos=unt-(sum-_[i]);
				A=pos+(sum-_[i]+1)*3;
				break;
			}
		}
		if(n%3==1)
		{
			printf("%lld\n",A);
			continue;
		}
		B=2;
		Find(unt,60);
		if(n%3==2)
		{
			printf("%lld\n",B);
			continue;
		}
		C=A^B;
		if(!(n%3)) printf("%lld\n",C);
	}
	return 0;
}
```

---

## 作者：DepletedPrism (赞：1)

#### 解题思路

首先可以注意到, 题目给定的数列存在一定规律, 于是打表.

数列 $S$ 每次增加一个三元组, 将得到的数列进行如下的处理:

```plain
1 2 3

4 8 12
5 10 15
6 11 13
7 9 14

16 32 48
17 34 51
18 35 49
19 33 50
20 40 60
21 42 63
22 43 61
23 41 62
24 44 52
25 46 55
26 47 53
27 45 54
28 36 56
29 38 59
30 39 57
31 37 58

64 128 192
...
```

我们将每三个数称作一组, 依照换行的位置分成数块. 三个数分别称作 $a,\ b,\ c$, 那么首先可以发现

1. 每一块内第一组中的 $a$ 是 $2$ 的偶数次幂, $b$ 是 $a$ 的两倍.

2. 每一块中元素个数是 $2$ 的偶数次幂, 即 $2^0,\ 2^2,\ 2^4, \ldots$

3. 每一块内, 除去第一组以外, $a$ 的值较上一组增加 $1$.

此时可以快速确定 $a$ 的值 --- 只需判定 $n$ 在哪一块内, 然后计算即可.

考虑到 $a \oplus b = c$, 只需得到 $b$ 的值即可计算 $c$.

因此现在的问题在于计算 $b$ 的值. 将 $b$ 的值单独以二进制的形式列出, 可以得到

*这里空白太小, 写不下:* <https://www.luogu.com.cn/paste/47ldzmpt>.

从低位到高位, 每两位进行考虑. 对于小数据, 后两位形同

```plain
00 10 11 01
```

并以此循环. 观察更高位, 也是依照这样的顺序, 只是重复的次数增加, 且重复的次数也是 $2$ 的幂.

那么, 从低位开始依次考虑即可得到 $b$.

#### 代码实现

赛时找到了规律, 只是没有调出来 = =

大概是将 $n$ 拆分成 $n = 3x+ y$ 的形式, 然后再依照以上的规律逐位考虑吧 (

以及利用 `bitset` 调试的技巧.

```cpp
// E2
// DeP
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL n;

int main() {
#ifndef ONLINE_JUDGE
    freopen("E.in", "r", stdin);
#endif
    int Ti;
    scanf("%d", &Ti);
    while (Ti--) {
        scanf("%lld", &n);
        LL x = n / 3, y = n % 3;
        if (!y) --x, y = 3;
        if (!x) { printf("%lld\n", y); continue; }
        LL a = 0, b = 0;
        int d = 0;
        while (a <= x) a += 1LL << d, d += 2;
        LL idx = x - (a - (1LL << (d-2)));
        a = (1LL << (d - 2)) + (x - (a - (1LL << (d-2))));
        if (y == 1) printf("%lld\n", a);
        else {
            b = 1LL << (d - 1);
            for (int i = 0; i < d - 2; i += 2) {
                LL m = 1LL << (i + 2);
                LL res = idx % m;
                if (res < (1LL << i))
                    b |= 0LL << i;
                else if (res < (1LL << (i+1)))
                    b |= 2LL << i;
                else if (res < (1LL << i) + (1LL << (i+1)))
                    b |= 3LL << i;
                else
                    b |= 1LL << i;
            }
            printf("%lld\n", (y == 2)? b: (a ^ b));
        }
    }
    return 0;
}
```


---

## 作者：lyhqwq (赞：0)

# Solution

难绷题。

考虑每三个数为一组打表找规律，可发现 $a \in [2^k,2^{k+1}-1] (k \equiv 0 \pmod 2)$。如果把一个组内分成四个小组，则每个小组内的第二个数形如 $a,c,d,b$ 分布。

考虑 $O(\log n)$ 算出第一个数，$O(\log_4 n)$ 递归算出第二个数，异或算出第三个数，具体细节见代码。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int _;
LL n;
LL work(LL l,LL r,LL L,LL R,LL x){
    if(l==r) return L;
    LL len=(r-l+1)/4;
    LL mid=(l+r)/2,mid1=l+len-1,mid2=r-len+1,_mid=(L+R)/2,_mid1=L+len-1,_mid2=R-len+1;
    //printf("%lld %lld %lld %lld %lld\n",l,mid1,mid,mid2,r);
    if(x<=mid1) work(l,mid1,L,_mid1,x);
    else if(x<=mid) work(mid1+1,mid,_mid+1,_mid2-1,x);
    else if(x<=mid2-1) work(mid+1,mid2-1,_mid2,R,x);
    else  work(mid2,r,_mid1+1,_mid,x);
}
int main(){
    scanf("%d",&_);
    while(_--){
        scanf("%lld",&n);
        LL p=(n-1)/3+1,r=n%3,k=0,sum=0;
        for(k=0;k<=60;k+=2){
            if(sum+(1ll<<k)>=p) break;
            else sum+=(1ll<<k);
        }
        p=p-sum;
        LL a=(1ll<<k)+p-1,b=work(1,(1ll<<k),(1ll<<k+1),(1ll<<k+1)+(1ll<<k)-1,p);
        if(r==0) printf("%lld\n",a^b);
        if(r==1) printf("%lld\n",a);
        if(r==2) printf("%lld\n",b);
    }
    return 0;
}

```

---

## 作者：Libra_ (赞：0)

## 题目 [CF1338C](https://codeforces.com/problemset/problem/1338/C)
现在有一个空序列 $S$，每次找到字典序最小的三元组 $(a,b,c)$ 满足 $a\oplus b\oplus c=0$ 且 $a,b,c \notin S$。把 $a,b,c$ 按顺序加入 $S$ 的末尾。询问第 $n$ 项是什么。


## 分析
因为感觉有规律，所以打了个表，把数字转换成二进制形式是这样的：

```cpp
0000000001 
0000000010 
0000000011 
  
0000000100 
0000001000 
0000001100 

0000000101 
0000001010 
0000001111 

0000000110 
0000001011 
0000001101 
......

```

整理一下，变成这样：

```cpp
0000000001  //a
0000000010  //b
0000000011  //c

0000000100 0000000101 0000000110 0000000111  //a
0000001000 0000001010 0000001011 0000001001  //b
0000001100 0000001111 0000001101 0000001110  //c

0000010000 0000010001 0000010010 0000010011 0000010100 0000010101 0000010110 0000010111 0000011000 0000011001 0000011010 0000011011 0000011100 0000011101 0000011110 0000011111  //a
0000100000 0000100010 0000100011 0000100001 0000101000 0000101010 0000101011 0000101001 0000101100 0000101110 0000101111 0000101101 0000100100 0000100110 0000100111 0000100101  //b
0000110000 0000110011 0000110001 0000110010 0000111100 0000111111 0000111101 0000111110 0000110100 0000110111 0000110101 0000110110 0000111000 0000111011 0000111001 0000111010  //c

0001000000 0001000001 0001000010 0001000011 0001000100 0001000101 0001000110 0001000111 0001001000 0001001001 0001001010 0001001011 0001001100 0001001101 0001001110 0001001111 0001010000 0001010001 0001010010 0001010011 0001010100 0001010101 0001010110 0001010111 0001011000 0001011001 0001011010 0001011011 0001011100 0001011101 0001011110 0001011111 0001100000 0001100001 0001100010 0001100011 0001100100 0001100101 0001100110 0001100111 0001101000 0001101001 0001101010 0001101011 0001101100 0001101101 0001101110 0001101111 0001110000 0001110001 0001110010 0001110011 0001110100 0001110101 0001110110 0001110111 0001111000 0001111001 0001111010 0001111011 0001111100 0001111101 0001111110 0001111111  //a
0010000000 0010000010 0010000011 0010000001 0010001000 0010001010 0010001011 0010001001 0010001100 0010001110 0010001111 0010001101 0010000100 0010000110 0010000111 0010000101 0010100000 0010100010 0010100011 0010100001 0010101000 0010101010 0010101011 0010101001 0010101100 0010101110 0010101111 0010101101 0010100100 0010100110 0010100111 0010100101 0010110000 0010110010 0010110011 0010110001 0010111000 0010111010 0010111011 0010111001 0010111100 0010111110 0010111111 0010111101 0010110100 0010110110 0010110111 0010110101 0010010000 0010010010 0010010011 0010010001 0010011000 0010011010 0010011011 0010011001 0010011100 0010011110 0010011111 0010011101 0010010100 0010010110 0010010111 0010010101  //b
0011000000 0011000011 0011000001 0011000010 0011001100 0011001111 0011001101 0011001110 0011000100 0011000111 0011000101 0011000110 0011001000 0011001011 0011001001 0011001010 0011110000 0011110011 0011110001 0011110010 0011111100 0011111111 0011111101 0011111110 0011110100 0011110111 0011110101 0011110110 0011111000 0011111011 0011111001 0011111010 0011010000 0011010011 0011010001 0011010010 0011011100 0011011111 0011011101 0011011110 0011010100 0011010111 0011010101 0011010110 0011011000 0011011011 0011011001 0011011010 0011100000 0011100011 0011100001 0011100010 0011101100 0011101111 0011101101 0011101110 0011100100 0011100111 0011100101 0011100110 0011101000 0011101011 0011101001 0011101010  //c
......
  
```

发现对于 $a,b,c$ 各组，开头前两位是不变的，分别对应 `01 10 11`。对于它们的位置，第一组在 $4^1$ 位，第二组在 $4^2$ 位，第三组在 $4^3$ 位......每组的数字个数（$a,b,c$ 组分开来算）分别是 $4^0$，$4^1$，$ 4^2$......

所以可以根据 $n$ 先确定好在哪一组，然后再确定是该组内的第几个。

继续观察发现每组以 $4$ 为周期呈现规律。

具体的，以 $b$ 的第三组为例：

```cpp
0000100000 0000100010 0000100011 0000100001 
0000101000 0000101010 0000101011 0000101001 
0000101100 0000101110 0000101111 0000101101 
0000100100 0000100110 0000100111 0000100101 
  
```
上面是 $b$ 的第三组。观察发现二进制下的第五六位（从一开始数）（即 $4^3$ 位）均为 $10$。

末尾四位是这样的：
```cpp
0000 0010 0011 0001
1000 1010 1011 1001
1100 1110 1111 1101
......
```
使二进制下的 `00 10 11 01` 分别代表四进制下的 `0 1 2 3`。则是这样的：

```cpp
00 01 02 03
10 11 12 13
20 21 22 23
......
```

这样就变成了四进制运算。

对于 $a$ 组和 $c$ 组同理。

更具体一点可以看代码。

## 代码
[我的代码](https://www.luogu.com.cn/paste/46rbrmg6)

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
没什么好说的，就是打表找规律……

[表在这里](https://www.luogu.com.cn/paste/kamel742)

不难发现，三元组中第一个数的最后两位按照 $00\to 01\to 10\to 11$ 的顺序变化，其他位也一样，同样，第二个数和第三个数中每两位分别按照 $00\to 10\to 11\to 01$ 和 $00 \to 11\to 01\to 10$ 的顺序变化，且与第一个数对应变化。那么只要我们第一个数确定了，第二个和第三个数也就确定了，因此，我们的问题变为了如何快速确定第一个数。

观察发现，当 $n=4^k$ 且 $k\in \mathbb Z$ 时，三元组第一个数为 $n$。并且可以看出，在第一个数为 $4^k\sim 2^{2\times k}-1$ 的连续若干个三元组中，第一个数是连续的，即分别为 $4^k,\dots,2^{2\times k}-1$。由此，我们可以找到第一个小于等于 $n$ 的 $x$ 使得 $x=4^k$ 且 $k\in\mathbb Z$，那么 $n$ 所在三元组的第一个数即为 $\displaystyle 2^k+\frac{n-2^k}{3}$。

综上，本题步骤为：
- 找到第 $n$ 个数所在三元组的第一个数；
- 令第一个数为 $m$，我们将 $m$ 转化为二进制，并将其位数补为偶数；
- 根据 $m$ 从最高位开始，每两位为一组，计算出对应的第 $2$、$3$ 个数的这两位；
- 将第 $2$、$3$ 个数转化位十进制下整数；
- 判断 $M=n\bmod 3$ 并输出，若 $M=1$，输出第一个数，若 $m=2$，输出第二个数，否则输出第三个数。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <string.h>
#define int long long
#define N 100
int n,m;char a[N],b[N],c[N];
inline int GetStr(int x,char *s){
    int ce=0;while(x){
        s[++ce]='0'+(x&1);
        x>>=1;
    }return ce&1?ce+1:ce;
}
inline void GetNum(int &x,char *s,int len){
    x=0;for(register int i=len;i>=1;--i)
        x=(x<<1ll)+(s[i]-'0');
}
inline void work(){
    scanf("%lld",&n);int lin;
    for(register int i=60ll;i>=0ll;--i)
        if((n>>i)&1ll){
            m=i&1ll?i-1ll:i;
            lin=m;break;
        }
    int sub=(1ll<<m),res=(n-sub)/3ll;
    m=sub+res;int _1=m,_2,_3;
    for(register int i=1;i<=80;++i)
        a[i]='0';int ce=GetStr(m,a);
    for(register int i=ce;i>=1;i-=2){
        if(a[i]=='0'&&a[i-1]=='0'){
            b[i]='0',b[i-1]='0';
            c[i]='0',c[i-1]='0';
        }else if(a[i]=='0'&&a[i-1]=='1'){
            b[i]='1',b[i-1]='0';
            c[i]='1',c[i-1]='1';
        }else if(a[i]=='1'&&a[i-1]=='0'){
            b[i]='1',b[i-1]='1';
            c[i]='0',c[i-1]='1';
        }else if(a[i]=='1'&&a[i-1]=='1'){
            b[i]='0',b[i-1]='1';
            c[i]='1',c[i-1]='0';
        }
    }GetNum(_2,b,ce),GetNum(_3,c,ce);
    if(n%3==0) printf("%lld\n",_3);
    else if(n%3==1) printf("%lld\n",_1);
    else printf("%lld\n",_2);
}
signed main(){
    int T;scanf("%lld",&T);
    while(T--) work();
    system("pause");
}
```

---

