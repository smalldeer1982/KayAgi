# Songs Compression

## 题目描述

Ivan has $ n $ songs on his phone. The size of the $ i $ -th song is $ a_i $ bytes. Ivan also has a flash drive which can hold at most $ m $ bytes in total. Initially, his flash drive is empty.

Ivan wants to copy all $ n $ songs to the flash drive. He can compress the songs. If he compresses the $ i $ -th song, the size of the $ i $ -th song reduces from $ a_i $ to $ b_i $ bytes ( $ b_i < a_i $ ).

Ivan can compress any subset of the songs (possibly empty) and copy all the songs to his flash drive if the sum of their sizes is at most $ m $ . He can compress any subset of the songs (not necessarily contiguous).

Ivan wants to find the minimum number of songs he needs to compress in such a way that all his songs fit on the drive (i.e. the sum of their sizes is less than or equal to $ m $ ).

If it is impossible to copy all the songs (even if Ivan compresses all the songs), print "-1". Otherwise print the minimum number of songs Ivan needs to compress.

## 说明/提示

In the first example Ivan can compress the first and the third songs so after these moves the sum of sizes will be equal to $ 8 + 7 + 1 + 5 = 21 \le 21 $ . Also Ivan can compress the first and the second songs, then the sum of sizes will be equal $ 8 + 4 + 3 + 5 = 20 \le 21 $ . Note that compressing any single song is not sufficient to copy all the songs on the flash drive (for example, after compressing the second song the sum of sizes will be equal to $ 10 + 4 + 3 + 5 = 22 > 21 $ ).

In the second example even if Ivan compresses all the songs the sum of sizes will be equal $ 8 + 4 + 1 + 4 = 17 > 16 $ .

## 样例 #1

### 输入

```
4 21
10 8
7 4
3 1
5 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 16
10 8
7 4
3 1
5 4
```

### 输出

```
-1
```

# 题解

## 作者：Pethly_Cat (赞：5)

看看题解这么少，那就来发一篇吧。

首先，先贴上这道题的翻译（来自@enor2017）：

$Ivan$在手机里有$n$个歌曲，第$i$个歌曲的大小是 $a[i]$ 。他还有个 $U$ 盘，容量是 $m$ 。一开始盘是空的。

$Ivan$想要把 $n$ 首歌全部拷贝到盘里。好消息是，他可以把音乐压缩。第$i$首歌经过压缩，容量会由 $a[i]$ 变为 $b[i]$ (保证 $a[i] < b[i]$ )。

$Ivan$可以压缩任意个歌曲（当然可以不压缩任何歌曲），然后将歌曲存到$U$盘里。（并且不要求压缩的歌曲是相邻的）

$Ivan$想要知道他最少需要压缩多少个歌，才能全部装到盘里（也就是要求总容量$\leqslant m$）

如果不可能做到，就输出$-1$，否则输出最少他需要压缩多少歌。

##### 输入格式
第一行两个整数$n,m\left( 1\leqslant n\leqslant 10^5,1\leqslant m\leqslant 10^9 \right) $，分别代表歌曲的总数和$U$盘的容量。

接下来$n$行每行两个整数$a_i,b_i\left( 1\leqslant b_i<a_i\leqslant 10^9 \right) $，分别代表第$i$首歌原来的大小和压缩后的大小。
##### 输出格式
如果把所有歌都压缩了也不能全部装到盘里，输出$-1$，
否则输出最少需要压缩多少歌。

看了一遍题目之后，我们不难看出，这是一个**贪心**题。

既然没有办法全部装进盘里，又要求压缩的个尽可能的小，所以，我们压缩 $a[i]$ 和 $b[i]$的差尽可能的大的，就可以尽可能少的压缩歌曲的次数。

分析完了思路，我们就可以愉快地打出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum1,sum2;
struct node
{
	int x,y;
}a[100001];
bool cmp(node a,node b)
{
	return a.x-a.y>b.x-b.y;//贪心
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		sum1+=a[i].y;//统计所有的歌曲都压缩了的题积
		sum2+=a[i].x;//统计所有歌曲的体积和
	}
	if(sum1>m){//判断是否将所有的歌曲压缩也无法全部装进U盘
		cout<<-1;
		return 0;
	}
	sort(a+1,a+n+1,cmp);//结构体排序，需要写一个函数来告诉系统怎么排序
	for(int i=1;i<=n;i++){
		if(sum2<=m){
			cout<<i-1;
			return 0;
		}
		sum2-=a[i].x-a[i].y;//压缩歌曲并更新当前体积
	}
	cout<<n;
	return 0;
}
```

于是我们就鱼块地 $WA$ 了

再提醒大家一句：万年 $OI$ 一场空，不开 $long$ $long$ 见祖宗。

$AC$ 的代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,sum1,sum2;
struct node
{
	long long x,y;
}a[100001];
bool cmp(node a,node b)
{
	return a.x-a.y>b.x-b.y;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		sum1+=a[i].y;
		sum2+=a[i].x;
	}
	if(sum1>m){
		cout<<-1;
		return 0;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(sum2<=m){
			cout<<i-1;
			return 0;
		}
		sum2-=a[i].x-a[i].y;
	}
	cout<<n;
	return 0;
}
```

#### 只求二事：

#### 赞和过

---

## 作者：Nygglatho (赞：2)

一道简单的贪心题。

将 $a_i$ 变为 $b_i$ 的次数如果要最少，显然需要每一次减少的数量要最多，即 $a_i - b_i$ 要尽量大。

可以用反证法。设答案为 $k$，假设并没有将 $a_i - b_i$ 前 $k$ 大的这些变成 $b_i$，而是将后面变成了 $b_i$，那么我们将其中的不是前 $k$ 大的去掉，换成 $a_i - b_i$ 是前 $k$ 大的，那么显然，改变后结果小于等于原来并没有将 $a_i - b_i$ 前 $k$ 大的这些变成 $b_i$ 的结果。

```c
#include <bits/stdc++.h>
 
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define ul unsigned long long
 
using namespace std;
 
struct g {
	ll x, y;
}t[114514];
 
bool cmp(g a, g b) {
	return (a.x - a.y) > (b.x - b.y);
}
 
ll p;
 
int main() {
	int n, m;
	IOS
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> t[i].x >> t[i].y;
		p += t[i].x;
	}
	if (p <= m) {
		cout << 0; return 0;
	}
	sort(t + 1, t + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		p -= t[i].x - t[i].y;
		if (p <= m) {cout << i; return 0;}
	}
	cout << -1;
}
```

---

## 作者：EightSixSun (赞：2)

分情况，先特判不可能全部装下和不需要压缩以及全部压缩(也不一定，可能有压缩前和压缩后占用空间相等的，这也是个小细节，这里所说的全部压缩是指粗略的全部压缩)之后恰好能装下的情况 

如果不属于以上三种情况，那就按压缩前和压缩后的占用空间的差值排序，然后贪心（优先选择差值最大的进行压缩）就行了

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define For(i,l,r) for(int i=l;i<=r;++i)
#define MAXN 100001
using namespace std;
long long as,bs;
int n,m,song[MAXN];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    int tx,ty,tn;
    scanf("%d %d",&n,&m);
    tn=n;
    For(i,1,n)
    {
        scanf("%d %d",&tx,&ty);
        if(tx==ty)
            --tn;
        song[i]=tx-ty;
        as+=tx;
        bs+=ty;
    }
    if(as<=m)//无需压缩
    {
        cout<<"0";
        return 0;
    }
    if(bs>m)//不可能全装下
    {
        cout<<"-1";
        return 0;
    }
    if(bs==m)//全压缩恰好全装下
    {
        cout<<tn;
        return 0;
    }
    sort(song+1,song+n+1,cmp);
    bs=0;//使用bs记录答案
    For(i,1,n)
    {
        bs++;
        as-=song[i];
        if(as<=m)
         break;
    }
    cout<<bs;
    return 0;
}
```

---

## 作者：FQR_ (赞：0)

## 思路

贪心。

考虑到，如果把 $a_i$ 换成 $b_i$，总重量会减少 $a_i-b_i$。

每次操作找到最大的 $a_i-b_i$，把 $a_i$ 替换成 $b_i$。

所以，我们可以将这些物品按 $a_i-b_i$ 递减的顺序来排序。

排序后，按照从 $1$ 到 $n$ 的顺序替换，直到总重量不超过 $m$ 为止。

程序末尾还要判断一下，当 $a_i$ 全部替换成 $b_i$ 时，是否能装下。

---

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{int a,b;} a[100010];
bool cmp(node a,node b)
{
	return a.a-a.b>b.a-b.b;
}
int n,m;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	int sum=0;//sum记录总质量
	for(int i=1;i<=n;i++)
		cin>>a[i].a>>a[i].b,sum+=a[i].a;
		
	if(sum<=m)//特判：此时总重量小于等于m，不需要替换，答案为0
	{
		cout<<0;return 0;
	}
	
	sort(a+1,a+1+n,cmp);//按照b[i]-a[i]递减的顺序排序
	for(int i=1;i<=n;i++)
	{
		sum-=a[i].a-a[i].b;//将a[i]替换成b[i]，总质量减少a[i]-b[i]
		if(sum<=m)//如果总重量小于等于m，说明背包已经能装下。此时替换了i次，直接输出i即可
		{
			cout<<i;return 0;
		}
	}
	cout<<"-1";//所有的数字都换了，仍无法装下，输出-1
	return 0;
}
```

---

## 作者：LKY928261 (赞：0)

## 题目分析

大致题意：有 $n$ 首歌和一个容量为 $m$ 的存储器，每首歌的初始内存为 $a_i$，压缩后内存为 $b_i$，求要想容纳所有歌曲所要压缩的最小歌曲数。若不可能全部存储则输出 `-1` 。

~~（我居然在没有翻译的情况下自己看懂了耶）~~

根据题意可知，如果所有的歌曲压缩后的内存之和仍然大于存储器的容量，那么就直接输出 `-1` 。

如果有可以存储的方案，那么优先压缩压缩时节约空间最多的歌曲即可。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,k,t,x,y,a[100005],i,j;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=0;i<n;i++){cin>>x>>y;a[i]=x-y;k+=x;t+=y;}
	//k表示最大的内存和，t表示最小内存和
	//为节约空间，只开了一个数组
	if(t>m){cout<<"-1\n";return 0;}
	//判断能否全部容纳
	sort(a,a+n);
	for(i=n-1;i>=0&&k>m;i--)k-=a[i];
	//按节约的空间从大到小依次压缩
	cout<<n-i-1<<"\n";
}
```

---

## 作者：Apro1066 (赞：0)

题目大意：有$n$首歌曲，给定压缩前和压缩后的大小，以及U盘的空间$m$。现在求最少压缩几首歌能把所有歌放入U盘，如果放不进去输出$-1$。

贪心，先写2个特判以便节省时间。

1.如果压缩后的全部歌曲$s2$大于$m$，则说明肯定放不进去，输出$-1$结束即可；

2.如果未压缩的全部歌曲$s1$小于等于$m$，则说明一定能全部放进去，输出$0$即可。

如果不符合上述情况，则把每个歌曲$i$**未压缩和压缩后的大小差**从大往小排序，因为我们要选尽可能少费空间（差值大的）的让最优解最优。然后**贪心**，差值大的优先放入U盘。

```cpp
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef struct//歌曲结构体 
{
	long long int a,b,dc;//a和b分别是对于歌曲i来说，压缩前的空间和压缩后的空间，dc是它们的差值 
}lxydl;
lxydl song[100001];
long long int n,m,s1,s2,s,cnt;//注意要开long long 
inline int cmp(lxydl a,lxydl b)//按歌曲压缩空间差值从大往小排序 
{
	return a.dc>b.dc;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register long long int i;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>song[i].a>>song[i].b;
		song[i].dc=song[i].a-song[i].b;//计算歌曲的空间差 
		s1=s1+song[i].a;//计算未压缩的歌曲空间总和 
		s2=s2+song[i].b;//计算压缩的歌曲空间总和
	}
	if(s2>m)//如果压缩后的歌曲还比m大 
	{
		cout<<-1<<endl;
		return 0;
	}
	if(s1<=m)//如果未压缩的歌曲比m小 
	{
		cout<<0<<endl;//肯定都能放进去，不用压缩 
		return 0;
	}
	sort(song+1,song+n+1,cmp);//排序 
	long long int space(s1-m);//计算空间差 
	for(i=1;i<=n;i++)
	{
		if(s>=space)//如果空间不够了 
		{
			break;
		}
		else
		{
			s=s+song[i].dc;
			cnt++;
		}
	}
	cout<<cnt<<endl;
	return 0;
}
```


---

## 作者：haohaoh4 (赞：0)

因为每一首歌至少要占用压缩后大小的空间，所以只要让压缩前-压缩后的大小最大即可。另外要判断如果全部都压缩了也不能满足，就输出-1。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct song_size{
	int before,after;
};
bool cmp(song_size a,song_size b)
{
	return a.before-a.after>b.before-b.after;
}
int song,mem;
song_size songs[100001];
int main()
{
	long long used_mem=0;
	cin>>song>>mem;
	for(int i=0;i<song;i++)
		cin>>songs[i].before>>songs[i].after,used_mem+=songs[i].before;
	sort(songs,songs+song,cmp);
	int i=0;
	while(used_mem>mem)//使用内存大于内存总量
	{
		if(i>=song){
			cout<<"-1\n";return 0;
		}
		used_mem-=songs[i].before-songs[i].after;
		i++;
	}
	cout<<i<<"\n";
	return 0;
}
```

---

