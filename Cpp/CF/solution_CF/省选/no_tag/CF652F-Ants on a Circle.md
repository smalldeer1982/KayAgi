# Ants on a Circle

## 题目描述

 $ n $ ants are on a circle of length $ m $ . An ant travels one unit of distance per one unit of time. Initially, the ant number $ i $ is located at the position $ s_{i} $ and is facing in the direction $ d_{i} $ (which is either L or R). Positions are numbered in counterclockwise order starting from some point. Positions of the all ants are distinct.

All the ants move simultaneously, and whenever two ants touch, they will both switch their directions. Note that it is possible for an ant to move in some direction for a half of a unit of time and in opposite direction for another half of a unit of time.

Print the positions of the ants after $ t $ time units.

## 样例 #1

### 输入

```
2 4 8
1 R
3 L
```

### 输出

```
1 3
```

## 样例 #2

### 输入

```
4 8 6
6 R
5 L
1 R
8 L
```

### 输出

```
7 4 2 7
```

## 样例 #3

### 输入

```
4 8 2
1 R
5 L
6 L
8 R
```

### 输出

```
3 3 4 2
```

# 题解

## 作者：hxhhxh (赞：10)

## 大意

长度为 $ m $ 的圆环上有 $ n $ 只蚂蚁，每一只蚂蚁会向某个特定方向以每秒一个单位的速度爬，当蚂蚁碰到一只迎面走来的蚂蚁时两只蚂蚁都会掉头，求最后所有蚂蚁的位置（要考虑编号）。

## 思路

首先不考虑编号，两只蚂蚁就想是穿过了对方一样，所以可以将所有蚂蚁最终位置很简单地算出来。

因为碰到就掉头，不影响相对位置，所以只要确定一只蚂蚁的编号就可以确定答案了。

考虑将蚂蚁排序，找第一只蚂蚁最后的编号。有这样几种情况会影响：

- 第一只蚂蚁穿过基准线，影响为 $ \pm \, (n - 1) $；
- 有一只蚂蚁穿过第一只蚂蚁，影响为 $ \pm 1 $；
- 有一只蚂蚁穿过基准线（不是第一只蚂蚁），影响为 $ \pm 1 $。

按照第一只蚂蚁的编号推算最后的编号就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t,ans[300005],eid;
char ch;
struct ant{
	int x,d,id;
}a[300005],e[300005];
bool cmp(ant a,ant b){
	return a.x<b.x;
}
signed main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++){
		scanf("%lld %c",&a[i].x,&ch);
		a[i].id=i;
		if(ch=='L'){
			a[i].d=e[i].d=-1;
			eid=((eid-(t+m-a[i].x)/m)%n+n)%n;
			e[i].x=((a[i].x-t)%m+m-1)%m+1;
		}
		else{
			a[i].d=e[i].d=1;
			eid=(eid+(t+a[i].x-1)/m)%n;
			e[i].x=((a[i].x+t)%m+m-1)%m+1;
		}
	}
	sort(a+1,a+n+1,cmp);
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++) ans[a[i].id]=e[(i+eid-1)%n+1].x;
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：猪脑子 (赞：10)

首先我们考虑直线上的情况，不难发现蚂蚁与蚂蚁的相对顺序不会发生改变。这时我们如果将蚂蚁按照$s_i$排序，然后从左到右重新编号，那么无论蚂蚁的位置怎么变化，蚂蚁的编号顺序都会是$1\dots n$。

如果我们不考虑蚂蚁的编号，只考虑蚂蚁的位置，那么两只蚂蚁相遇后掉头就完全可以看做是两只蚂蚁无视对方而继续向前走。那么对于一只原本在$s_i$位置的蚂蚁，$t$时间后它会走到$s_i+t$或$s_i-t$的位置。因此对于直线上的情况，我们只需要将每只蚂蚁的结束位置求出来，进行排序，这样按照重新编号的顺序就可以依次确定每个编号对应蚂蚁的结束位置。

那么我们再考虑环的情况，此时如果我们按照$s_i$从小到大重新编号为$1\dots n$，那么无论蚂蚁怎么走，蚂蚁位置的相对顺序依然不会改变。我们可以像刚刚那样求出蚂蚁们能够到达的位置，但是这样还无法确定答案：我们并不能像刚刚那样确定每个编号对应的是哪个位置，因为在环上有$n$种编号与位置的对应方案。

我们重新回顾一下链的情况。我们这里还是认为蚂蚁不进行掉头，而是直接穿过跟它相遇的蚂蚁。如果一只向左走的蚂蚁穿过了一只向右走蚂蚁，不难发现，它的编号会减少1（这里是按照初始位置排序得到的编号，下同），对于向右走的蚂蚁也是一样的，只不过变成了增加。同样地，我们把它放到环上，向左走（题目中的顺时针）的蚂蚁如果穿过了向右走的蚂蚁，那么编号同样会减少1（如果本来编号是1那么编号会变成$n$），向右也是同理。

首先我们还是求出这$n$只蚂蚁的结束位置的集合，此时我们考虑最开始编号为1的蚂蚁，如果我们求出它结束时的编号（假设是$pos$）与对应位置，那么我们就可以按照逆时针的方向依次确定编号为$pos,pos+1,\dots,n-1,n,1,2,\dots,pos-1$的蚂蚁的最终位置。初始编号为1的蚂蚁的结束位置很好求，只需要算$s_1+t$（或$s_1-t$）模$m$的值就可以了，而它的编号我们也可以通过算穿过其它蚂蚁的次数来计算（在环上有可能会穿过同一个蚂蚁多次，只需要做个除法就可以了）。

最后，实现的过程中一定要想好细节，防止在各种奇奇怪怪的情况下（比如结束位置相等时）出错。

具体细节看一下我的代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int s[300010];
char op[300010];
int id[300010];
int n,m;
long long t;
bool cmp1(int a,int b)
{
	int pa,pb;//计算两个蚂蚁的结束位置
	if(op[a]=='L')
		pa=((s[a]-t)%m+m)%m;
	else pa=(s[a]+t)%m;
	if(op[b]=='L')
		pb=((s[b]-t)%m+m)%m;
	else pb=(s[b]+t)%m;
	if(pa!=pb)return pa<pb;
	return op[a]=='L';
	//如果相等的话我选择的是让向左走的排在前面
	//至于为啥加这个判断，是为了防止结束位置相等时计算答案出现偏移
}
int id2[300010];
bool cmp2(int a,int b)
{
	//比较初始位置
	if(s[a]!=s[b])
		return s[a]<s[b];
	return op[a]=='L';
}
int ans[300010];
int main()
{
	//为了方便，代码中蚂蚁与位置都是从0开始
	cin>>n>>m>>t;
	for(int i=0;i<n;i++)
	{
		cin>>s[i]>>op[i];
		s[i]--;id[i]=id2[i]=i;
	}
	//按照结束位置与初始位置排序
	//按照初始位置排序相当于重新编号
	sort(id,id+n,cmp1);
	sort(id2,id2+n,cmp2);
	int pos=0;//算对应位置
	if(op[0]=='L')
	{
		long long x=s[0]-t;
		for(int i=0;i<n;i++)
			if(op[i]=='R')
			{
				long long y=s[i]+t;
				if(s[i]>s[0])y-=m;
				if(y<x)continue;
				pos=(pos+(y-x)/m+1)%n;
			}
		pos=(n-pos)%n;
	}
	else{
		long long x=s[0]+t;
		for(int i=0;i<n;i++)
			if(op[i]=='L')
			{
				long long y=s[i]-t;
				if(s[i]<s[0])y+=m;
				if(y>x)continue;
				pos=(pos+(x-y)/m+1)%n;
			}
	}
	int p=0;
	for(int i=0;i<n;i++)
		if(id2[i]==0)p=i;
	p=(p+pos)%n;
	int q=0;
	for(int i=0;i<n;i++)
		if(id[i]==0)q=i;
	for(int i=0;i<n;i++)
	{
		int j=id[(q+i)%n];
		int x=(q+i)%n,y;
		if(op[j]=='L')
			y=((s[j]-t)%m+m)%m;
		else y=(s[j]+t)%m;
		int z=id2[(p+i)%n];
		ans[z]=y+1;
	}
	for(int i=0;i<n;i++)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：灰鹤在此 (赞：2)

简单版：[AT2369 [AGC013C] Ants on a Circle](https://www.luogu.com.cn/problem/AT2369)

题意：给你 $n$ 只不同位置的蚂蚁、长度为 $m$ 的一个环和总时间 $t$，每只蚂蚁每秒走 $1$ 长度。然后给你每只蚂蚁的位置和方向（顺时针或逆时针），让你求 $t$ 秒之后每一只蚂蚁的位置（顺序同输入顺序）。

解题思路：假如我们站在很高很高的山上看这群蚂蚁在绕着这个环转，那么我们会很惊奇的发现，两只蚂蚁碰到之后，他们居然穿过了对方！而且，因为是一个环，每一只蚂蚁只要碰到对方就掉头，那么，排在一只蚂蚁顺时针方向的蚂蚁永远不会到这只蚂蚁的逆时针（指相对位置），排在一只蚂蚁逆时针方向的蚂蚁永远不会到这只蚂蚁的顺时针。于是我们得到，他们的相对位置是永不变的。

于是我们先将每一只蚂蚁的初始位置排序，得出他们的相对位置顺序，然后，我们只需要紧盯着一只蚂蚁，我取了排完序后距离最小的第一只蚂蚁，然后求出它的精确位置，于是我们就可以得到所有蚂蚁的位置了。

由于是在环上，我们之前取的第一只蚂蚁走过 $t$ 秒后并不一定就还是最靠前的（相对于环上的位置 $1$），我们记 $1$ 为蚂蚁运动时一个固定的“路标”，如果有蚂蚁顺时针经过了 $1$，那么 $1$ 号蚂蚁前面就多了一只蚂蚁（在以 $1$ 位置为起点 $0\degree\sim360\degree$ 时）。如果有蚂蚁逆时针经过了 $1$，那么 $1$ 号蚂蚁前面就少了一只蚂蚁。因为我们是拿 $1$ 作为参考系的，所以 $1$ 号蚂蚁经过 $1$ 也要处理。由此，我们就可以计算出 $1$ 号蚂蚁前面有多少只蚂蚁了，然后我们从 $1$ 号蚂蚁依次把排序完后的所有蚂蚁最终的位置传给每一只蚂蚁就行了。

我们能这么做的原因是：你可以想象一只带着光源的蚂蚁，然后他从 $x$ 位置出发，如果他碰到了一只蚂蚁，那么他就把光源传给了他碰到的那一只蚂蚁，然后那一只蚂蚁又碰到了另一只蚂蚁，那么那一只蚂蚁就把光源传给了另一只蚂蚁……由此看来，我们根本无需在蚂蚁爬行时那么在意他们的编号。

这里再给出一些优化建议：我们可以将环的长度从 $1\sim m$ 改为 $0\sim m-1$。这样可以在处理第一只蚂蚁的最终相对位置时更加简单。排序前一定要把蚂蚁输入时顺序的编号记下来，否则最终输出的就不是题目所要的蚂蚁的位置了。然后我在做这题时被卡精度了 QWQ，所以我用了 $\text{\_\_int128}$ 和 $\text{long double}$

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
void read(T&s){
	s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
}
template <typename T>
inline void write(T x){
	if(x==0){
		putchar('0');
	}else{
		static int sta[45],top=0;
		while(x){
			sta[++top]=x%10;
			x/=10;
		}
		while(top){
			putchar(sta[top--]+'0');
		}
	}
}
const int MaxN=3e5+5;
__int128 n,l,t,first_ant_place,ans[MaxN],h[MaxN];
struct hh{
	__int128 place,ends,id;
	bool friend operator < (hh x,hh y){	
		return x.ends<y.ends;
	}
}a[MaxN];
bool cmp(hh x,hh y){
	return x.place<y.place;
}
int main(){
	read(n),read(l),read(t);
	char opt;
	for(__int128 i=1;i<=n;i++){
		a[i].id=i;
		read(a[i].place);
		a[i].place--;
		opt=getchar();
		while(opt!='L'&&opt!='R'){
			opt=getchar();
		}
		if(opt=='R'){
			a[i].ends=a[i].place+t;
		}else{
			a[i].ends=a[i].place-t;
		}
	}
	sort(a+1,a+n+1,cmp);
	for(__int128 i=1;i<=n;i++){
		h[a[i].id]=i;
		first_ant_place=((first_ant_place+(__int128)floor((long double)a[i].ends/l))%n+n)%n;
		a[i].ends=(a[i].ends%l+l)%l;
	}
	sort(a+1,a+n+1);
	for(__int128 i=1;i<=n;i++){
		ans[i]=a[(first_ant_place+i-1)%n+1].ends+1;
	}
	for(__int128 i=1;i<=n;i++){
		write(ans[h[i]]);
		putchar(' ');
	}
	puts("");
	return 0;
}
```

---

## 作者：Purslane (赞：1)

## Solution

看到蚂蚁题，第一反应是上帝视角。两只蚂蚁撞在一起，实际上对于宏观来看，相当于两只蚂蚁互相穿过对方。

所以我们可以很容易知道最后哪些位置有蚂蚁。

如果是简化版在一根木棒上，那么最前面的蚂蚁还是最前面的蚂蚁，相对顺序不变。可是这道题，如何知道最终那只蚂蚁是原来的第一只呢?

我们可以跟踪第一只蚂蚁。当它和另一只蚂蚁相撞的时候，我们不掉头，而是继续跟踪相撞的那只蚂蚁。换句话说，我们跟踪的蚂蚁只往一个方向从白走到黑。

但这时候，我们跟踪的蚂蚁已经变成另外一只了。。。。。。如果第一只蚂蚁向右爬，那么每撞一次，它的编号增加 $1$。如果它向左爬，那么每撞一次，它的编号减少 $1$。我们只需要计算每只蚂蚁和我们跟踪的蚂蚁相撞多少次。

其他的蚂蚁在宏观上也不需要区分掉头的顺序，因为到底谁撞得无所谓，只需看装了多少次。

还有一个小问题，最后两只蚂蚁停一块，怎么办?由于蚂蚁的坐标不重复，那么这两只蚂蚁必定一左一右。我们不妨钦定向左的蚂蚁比向右的蚂蚁更靠前。这种情况下，两只蚂蚁最后停一块也应该算相撞。

题解仅供参考，强烈建议自己把思路理顺了再写代码，别像我搞了 $2$ h 才发现自己的思路好像有 bug。

代码 :

```cpp
#include<bits/stdc++.h>
#define int __int128
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,m,t,ans[MAXN];
namespace IO {
	int read(void) {
		int s=0,f=0; char ch=getchar();
		while(!(ch>='0'&&ch<='9')) f=(ch=='-'),ch=getchar();
		while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
		return f?-s:s;
	}
	char gread(char L,char R) {
		char ch=getchar();
		while(ch<L||ch>R) ch=getchar();
		return ch;	
	}
	void write(int x) {
		if(x<0) putchar('-'),x=-x;
		if(x>=10) write(x/10);
		return putchar(x%10+'0'),void();
	}
	int mul(char ch) {return (ch=='L')?-1:1;}
	int modm(int pos) {
		pos%=m,pos+=m,pos%=m; if(!pos) pos=m;
		return pos;	
	}
};
using namespace IO;
struct Ants {int pos,id;char ch;}v1[MAXN],v2[MAXN];
signed main() {
	n=read(),m=read(),t=read();
	ffor(i,1,n) v1[i].pos=read(),v1[i].id=i,v1[i].ch=gread('A','Z');
	sort(v1+1,v1+n+1,[](Ants A,Ants B) {
		if(A.pos!=B.pos) return A.pos<B.pos;	
		return A.ch<B.ch;
	});
	ffor(i,1,n) v2[i]={modm(v1[i].pos+mul(v1[i].ch)*t),v1[i].id,v1[i].ch};
	sort(v2+1,v2+n+1,[](Ants A,Ants B) {
		if(A.pos!=B.pos) return A.pos<B.pos;	
		return A.ch<B.ch;
	});
	int pos=1,res=0;
	ffor(i,1,n) {
		if(i!=1) {
			if(v1[i].ch!=v1[1].ch) {
				int dis=2*t,cnt=0;
				if(v1[i].ch=='L') {
					int len=modm(v1[i].pos-v1[1].pos);
					if(dis>=len) pos+=1+(dis-len)/m;
				}
				else {
					int len=modm(v1[1].pos-v1[i].pos);
					if(dis>=len) pos-=1+(dis-len)/m;
				}
			}
		}
		pos%=n,pos+=n,pos%=n;
	}
	pos%=n,pos+=n,pos%=n;
	if(pos==0) pos=n;
	ffor(i,1,n) if(v2[i].id==v1[1].id) res=i;
	res-=pos-1,res%=n,res+=n,res%=n;
	ffor(i,1,n) {
		int id=res+i-1;
		id%=n,id+=n,id%=n;if(id==0) id=n;
		ans[v1[i].id]=v2[id].pos;
	}
	ffor(i,1,n) write(ans[i]),putchar(' ');
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

首先在一条直线上考虑这个问题。不难发现所有最终位置是容易确定的。但各蚂蚁的最终位置却不好求。

注意到重要的性质：蚂蚁的相对位置不改变。于是易得。

但在圆环上，只能保证蚂蚁的相对位置与开始循环同构。故不能用上述方法做。

不妨这样思考：每只蚂蚁携带一个电子屏，开始时第 
$i$
 只显示 
$i$。相遇时交换电子屏上的数字。设结束时第 
$i$
 只显示 
$a_
i$，则 
$a_
i$ 的答案即为 
$i$
 的位置。

构造几组样例，不难得出以下性质：若蚂蚁 
$i$
 初始向右，则每相遇一次，
$a_
i$
 在模 
$n$
 意义下加 
$1$。可以感性理解一下。

于是此题解决。

---

