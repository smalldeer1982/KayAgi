# Circus

## 题目描述

**题意：** 有$n$组数（保证$n$是偶数），每组数中有两个数，第$i$组数中的数为$c_i$和$a_i$，其中$c_i,a_i$都为$0$或$1$

您需要将$n$组数分成两部分，满足：

- 每部分$\frac{n}{2}$组数。

- 第一部分中$c_i$的和=第二部分中$a_i$的和。

**数据范围：** $2\le n\le 5000$

## 样例 #1

### 输入

```
4
0011
0101
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
000000
111111
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
0011
1100
```

### 输出

```
4 3
```

## 样例 #4

### 输入

```
8
00100101
01111100
```

### 输出

```
1 2 3 6
```

# 题解

## 作者：cloud_9 (赞：5)

## Description:

给你2个长度为n的01串
从中选出$n/2$个,使得选出的数中第一排1的个数等于未选出数中第二排1的个数
输出一种方案即可,没有输出-1

## Hint:

$n \le 5000$

## Solution:

这题比赛的时候傻逼了

后面发现其实就是暴力枚举解方程

$AuBao$想出一个O(n)做法力碾标算,这里放出来%一%:

设$a_i$为**所选**第一排是1的数

$b_i$表示其**对应**第二排的数

设$sum$表示第二排1的个数

有:
$$\sum a_i = sum- \sum b_i$$

移过去用d数组代替

$$\sum d_i = sum$$

现在考虑d的取值,显然有0,1,2三种

且
$$cnt0*0+cnt1*1+cnt2*2=sum$$
$$cnt0+cnt1+cnt2=n/2$$

即
$$cnt1*1+cnt2*2=sum$$
$$cnt0+cnt1+cnt2=n/2$$

O(n)枚举即可

另附被爆踩的官方$n^2$的做法:

![](https://img2018.cnblogs.com/blog/1502480/201904/1502480-20190402083109217-1042554808.png)

```cpp
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define ls p<<1 
#define rs p<<1|1
using namespace std;
typedef long long ll;
const int mxn=1e5+5;
int n,m,cnt,hd[mxn];

inline int read() {
    char c=getchar(); int x=0,f=1;
    while(c>'9'||c<'0') {if(c=='-') f=-1;c=getchar();}
    while(c<='9'&&c>='0') {x=(x<<3)+(x<<1)+(c&15);c=getchar();}
    return x*f;
}
inline void chkmax(int &x,int y) {if(x<y) x=y;}
inline void chkmin(int &x,int y) {if(x>y) x=y;}

struct ed {
    int to,nxt;
}t[mxn<<1];

inline void add(int u,int v) {
    t[++cnt]=(ed) {v,hd[u]}; hd[u]=cnt;
}

char p[5005],q[5005];
int sum,cnt0,cnt1,cnt2;
vector<int > g0,g1,g2;

int main()
{
    n=read(); scanf("%s %s",p+1,q+1);
    for(int i=1;i<=n;++i) {
        if(p[i]=='0'&&q[i]=='0') ++cnt0,g0.push_back(i);
        if(p[i]=='0'&&q[i]=='1') ++cnt1,g1.push_back(i),++sum;
        if(p[i]=='1'&&q[i]=='0') ++cnt1,g1.push_back(i);
        if(p[i]=='1'&&q[i]=='1') ++cnt2,g2.push_back(i),++sum;
    }
    int c1,c0;
    for(int i=0;i<=cnt2;++i) {
        c1=sum-i*2; c0=n/2-i-c1;
        if(c1<0||c0<0) continue ;
        if(c1<=cnt1&&c0<=cnt0) {
            for(int j=0;j<c0;++j) 
                printf("%d ",g0[j]);
            for(int j=0;j<c1;++j)
                printf("%d ",g1[j]);
            for(int j=0;j<i;++j)
                printf("%d ",g2[j]);
            exit(0);	
        } 
    }
    puts("-1");
    return 0;
}
```



---

## 作者：蒟蒻本人 (赞：3)

#### 这是一个纯手动模拟
由于蒟蒻不会构造法就打了这个东西。

众所周知，这个数只有四种可能（０，０），（０，１），（１，０），（１，１）；

那么我们先来计算前一半的x的和再计算一波后一半y的和，用sumx和sumy来存一下。

然后我们进行分类讨论。

我们来手动交换他们的位置。

如果我要增加sumx的值或者减少sumy的值（达到的效果是一样的）
那我可以进行这几种操作；

１．将右边的（１，０）和我左边的（０，０）交换；

２．将右边的（０，１）和我左边的（０，０）交换；

３．将右边的（１，１）和我左边的任意非（１，１）的点交换。
对于减少sumx和增加sumy的值操作类似。

我使用了８个指针来表示左边和右边（０，０），（０，１），（１，０），（１，１）的位置，如果过了n/2，那就是左边（或者右边）已经没有那一类数了。
贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define r(x) x=read()
int read(){
	int w=0,f=1;char ch;
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {w=(w<<3)+(w<<1)+ch-'0';ch=getchar();}
	return w*f;
}
int n,ans[5001],sumx,sumy;
char nm[5001],mn[5001];
struct node{int x,y;} s[5001];
int a[5001],b[5001],c[5001],d[5001],aa=0,bb=0,cc=0,dd=0;
int main()
{
	r(n);
	scanf("%s",nm);scanf("%s",mn);
	for(int i=0;i<n;i++) s[i+1].x=nm[i]-'0';
	for(int i=0;i<n;i++) s[i+1].y=mn[i]-'0';
	for(int i=1;i<=n;i++) ans[i]=i;
	int mid=n>>1;
	for(int i=1;i<=mid;i++) sumx+=s[i].x,sumy+=s[n-i+1].y;
	if(sumx==sumy)
	{
		for(int i=1;i<=mid;i++) printf("%d ",i);
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(!s[i].x&&!s[i].y) {a[++aa]=i;continue;}
		if(s[i].x)
		{
			if(s[i].y) d[++dd]=i;
			else b[++bb]=i;
			continue;
		}
		c[++cc]=i;
	}
	if(sumx>sumy)
	{
		int sa=1,sb=1,sc=1,sd=1,ssa=aa,ssb=bb,ssc=cc,ssd=dd;
		while(sumx>sumy)
		{
			if(sumx==sumy+1)
			{
				if(a[ssa]>mid)
				{
					if(c[sc]<=mid&&c[sc]>0) {swap(ans[a[ssa]],ans[c[sc]]);break;}
					if(b[sb]<=mid&&b[sb]>0) {swap(ans[a[ssa]],ans[b[sb]]);break;}
				}
				if(c[ssc]>mid&&d[sd]<=mid&&d[sd]>0) {swap(ans[c[ssc]],ans[d[sd]]);break;}
				if(d[sd]<=mid&&b[ssb]>mid&&d[sd]>0) {swap(ans[d[sd]],ans[b[ssb]]);break;}
			}
			if(a[ssa]>mid)
			{
				if(d[sd]<=mid&&d[sd]>0)
				{
					swap(ans[d[sd]],ans[a[ssa]]);
					sd++,ssa--;
					sumx--,sumy++;
					continue;
				}
				if(b[sb]<=mid&&b[sb]>0)
				{
					swap(ans[b[sb]],ans[a[ssa]]);
					sb++,ssa--;
					sumx--;
					continue;
				}
				if(c[sc]<=mid&&c[sc]>0)
				{
					swap(ans[c[sc]],ans[a[ssa]]);
					sc++,ssa--;
					sumy++;
					continue;
				}
			}
			if(d[sd]<=mid&&d[sd]>0)
			{
				if(b[ssb]>mid)
				{
					swap(ans[d[sd]],ans[b[ssb]]);
					sd++;ssb--;
					sumy++;
					continue;
				}
				if(c[ssc]>mid)
				{
					swap(ans[d[sd]],ans[c[ssc]]);
					sd++,ssc--;
					sumx--;
					continue;
				}
			}
			{puts("-1");return 0;}
		}
		if(sumx<sumy) {puts("-1");return 0;}
		for(int i=1;i<=mid;i++) printf("%d ",ans[i]);
	}
	if(sumx<sumy)
	{
		int sa=1,sb=1,sc=1,sd=1,ssa=aa,ssb=bb,ssc=cc,ssd=dd;
		while(sumx<sumy)
		{
			if(sumx+1==sumy)
			{
				if(a[sa]<=mid&&a[sa]>0)
				{
					if(c[ssc]>mid) {swap(ans[a[sa]],ans[c[ssc]]);break;}
					if(b[ssb]>mid) {swap(ans[a[sa]],ans[b[ssb]]);break;}
				}
				if(d[ssd]>mid&&b[sb]<=mid&&b[sb]>0){swap(ans[d[ssd]],ans[b[sb]]);break;}
				if(d[ssd]>mid&&c[sc]<=mid&&c[sc]>0){swap(ans[d[ssd]],ans[c[sc]]);break;}
			}
			if(a[sa]<=mid&&a[sa]>0)
			{
				if(d[ssd]>mid)
				{
					swap(ans[d[ssd]],ans[a[sa]]);
					ssd--,sa++;
					sumx++,sumy--;
					continue;
				}
				if(b[ssb]>mid)
				{
					swap(ans[b[ssb]],ans[a[sa]]);
					ssb--,sa++;
					sumx++;
					continue;
				}
				if(c[ssc]>mid)
				{
					swap(ans[c[ssc]],ans[a[sa]]);
					ssc--,sa++;
					sumy--;
					continue;
				}
			}
			if(d[ssd]>mid)
			{
				if(b[sb]<=mid&&b[sb]>0)
				{
					swap(ans[d[ssd]],ans[b[sb]]);
					ssd--;sb--;
					sumy--;
					continue;
				}
				if(c[sc]<=mid&&c[sc]>0)
				{
					swap(ans[d[ssd]],ans[c[sc]]);
					ssd--,sc++;
					sumx++;
					continue;
				}
			}
			{puts("-1");return 0;}
		}
		if(sumy<sumx) {puts("-1");return 0;}
		for(int i=1;i<=mid;i++) printf("%d ",ans[i]);
	}
}
```
###### 

---

## 作者：冥诺在线发呆 (赞：2)

考试时爆零太桑心了，过来水一篇题解QAQ

敲好想的构造法！！

## 思路：

首先统计各类二元组个数，将（1，0）和（0，1）分别放至两个数组，计算两组之差

若（1，1）个数小于两组之差（补齐不了），先将少的那个加上（1，1）个数，两组用（0，0）补满，再用少的那组的（0，0）替换多的那一组的有贡献的二元组（如：（1，0）原在第一组，贡献1，替换到第二组贡献0，（0，0）加到第一组贡献0，一次操作后两组数差距减少1），若少的那组的（0，0）不够，则无解。

若（1，1）个数足够，补齐少的那一组，剩余均分，若（1，1）组均分不了（多1），则用少的那组的（0，0）替换多的那组的非（1，1）的有贡献二元组（同上），若（0，0）不够，则无解

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}//日常快读
const int N=5e3+5;
int n,shu[N],a[N]/*（0，0）*/,b[N]/*（1，0）*/,c[N]/*（0，1）*/,d[N]/*1，1*/,len[2][4]/*两组的二元组统计*/;
int main(){
	n=read();int mid=n>>1;
	for(int i=1;i<=n;i++){
		char s=getchar();
		while(s<'0'||s>'1')s=getchar();
		shu[i]=s-'0';
	}
	for(int i=1;i<=n;i++){
	    char s=getchar();
		while(s<'0'||s>'1')s=getchar();
		int y=s-'0';//读入
	    if(!shu[i]&&!y)a[++a[0]]=i;
		if(shu[i]&&!y)b[++b[0]]=i;
		if(!shu[i]&&y)c[++c[0]]=i;
		if(shu[i]&&y)d[++d[0]]=i;//统计各类二元组个数
	}
	if(((c[0]>mid||b[0]>mid)&&(n&1)==0)||((n&1)&&(b[0]>mid+1||c[0]>n-mid))){
		puts("-1");
		return 0;
	}//特判，若（1，0）或（0，1）二元组过半，定无解
    len[0][1]=b[0],len[1][2]=c[0];//两组的（1，0），（0，1）个数统计
    bool bj=len[0][1]<len[1][2];//bj为大的那一组
	int k=len[bj][bj+1]-len[bj^1][(bj^1)+1];//计算两组之差
	if(d[0]<k){//若（1，1）个数小于两组之差
    	len[bj^1][3]=d[0];//先将少的那个加上（1，1）个数
		len[bj][0]=(bj==0?mid:n-mid)-len[bj][bj+1];
		len[bj^1][0]=a[0]-len[bj][0];//用（0，0）将两组补满
		if(len[bj^1][0]>=k-d[0]&&len[bj][bj+1]>=k-d[0]){
			len[bj^1][0]-=(k-d[0]);
			len[bj^1][bj+1]+=k-d[0];
			len[bj][0]+=k-d[0];
			len[bj][bj+1]-=(k-d[0]);
		}//若少的那组的（0，0）够，用少的那组的（0，0）替换多的那一组的有贡献的二元组
		else{puts("-1");return 0;}
	}
	else {//若（1，1）个数足够
		len[bj^1][3]=k;//补齐少的那一组
		len[0][3]+=(d[0]-k)/2;
		len[1][3]=d[0]-len[0][3];
		len[0][0]=mid-len[0][1]-len[0][3];
		len[1][0]=a[0]-len[0][0];//剩余均分
		if((d[0]-k)&1){//若（1，1）组均分不了（多1）
			if(len[0][0]&&len[1][2]){
				len[0][0]--;
				len[0][2]++;
				len[1][0]++;
				len[1][2]--;
			}//用少的那组的（0，0）替换多的那组的非（1，1）的有贡献二元组
			else{
				puts("-1");
				return 0;
			}
		}
	}
	for(int i=1;i<=len[0][0];i++)
		printf("%d ",a[i]);
	for(int i=1;i<=len[0][1];i++)
		printf("%d ",b[i]);
	for(int i=1;i<=len[0][2];i++)
		printf("%d ",c[i]);
	for(int i=1;i<=len[0][3];i++)
		printf("%d ",d[i]);//输出
	return 0;
}
```


---

## 作者：skydogli (赞：0)

来一个超级亲民~~蒟蒻~~的$O(n)$做法

$\quad$首先这题只有$(0,0),(0,1),(1,0),(1,1)$四种情况，我们只需要使左半部分的$(1,0),(1,1)$的个数等于右半部分的$(0,1)(1,1)$个数就好了。另一个很显然的性质：一个数最多被交换$1$次，一次交换$2$个数，所以总共最多交换$\frac{n}{2}$次。所以我们可以直接记录左边和右边4种情况的数量，每次交换就行了，如果交换$\frac{n}{2}$次还不行，就输出$-1$。

$\quad$另外还有个小细节：交换时可能出现交换一次后，左右价值之差改变了$2$（例如左边$(0,0)$换右边$(1,1)$),当$2$边只相差$1$时可能会锅，所以我们每次尽量只改变$1$，改不了再改变$2$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MN 5005
int n,s[2][2],q[2][2][2],num[2][2][MN];
char x[MN],y[MN];
//q：左右部分各个情况的个数
//num：记录各个情况的位置
//s：记录整体部分各个情况的个数
bool chk1(){
	return q[0][1][0]+q[0][1][1]<q[1][0][1]+q[1][1][1];
}
bool chk2(){
	return q[0][1][0]+q[0][1][1]>q[1][0][1]+q[1][1][1];
}
//判断左边比右边多/少
void change(int x1,int y1,int x2,int y2){
	q[0][x1][y1]--;q[1][x1][y1]++;
	q[0][x2][y2]++;q[1][x2][y2]--;
}//左右互换
int main(){
	int Be=clock();
	scanf("%d",&n);
	scanf("%s",x+1);
	scanf("%s",y+1);
	for(int i=1;i<=n;++i){
		x[i]-='0';y[i]-='0';
		s[x[i]][y[i]]++;
		q[i>(n>>1)][x[i]][y[i]]++;
		num[x[i]][y[i]][s[x[i]][y[i]]]=i;
	}
	int CNT=0;
	memset(s,0,sizeof(s));
	while(chk1()||chk2()){
		CNT++;
		if(CNT>(n>>1)+1) break;
        //交换次数超过n的一半
		if(chk1()){
			bool t=0;//t判断本次是否交换过
			if(q[1][1][1]){
				if(q[0][0][1]){
					t=1;
					change(0,1,1,1);
				}
				else if(q[0][1][0]){
					t=1;
					change(1,0,1,1);
				}
			}
			if(!t&&q[0][0][0]){
				if(q[1][1][0]){
					t=1;
					change(0,0,1,0);
				}
				else if(q[1][0][1]){
					t=1;
					change(0,0,0,1);
				}
                //以上是交换改变为1的
				else if(q[1][1][1]){
					t=1;
					change(0,0,1,1);
				}//这个是变化为2的
			}
			if(!t){puts("-1");return 0;}
		}
		if(chk2()){
			bool t=0;
			if(q[0][1][1]){
				if(q[1][1][0]){
					t=1;
					change(1,1,1,0);
				}
				else if(q[1][0][1]){
					t=1;
					change(1,1,0,1);
				}
			}
			if(!t&&q[1][0][0]){
				if(q[0][0][1]){
					t=1;
					change(0,1,0,0);
				}
				else if(q[0][1][0]){
					t=1;change(1,0,0,0);
				}
				else if(q[0][1][1]){
					t=1;
					change(1,1,0,0);
				}
			}//同上
			if(!t){puts("-1");return 0;}
		}
	}
	if(chk1()||chk2()){puts("-1");return 0;}
	for(int j=0;j<2;++j)
		for(int k=0;k<2;++k)
			for(int l=0;l<q[0][j][k];++l){
				printf("%d ",num[j][k][++s[j][k]]);
			}//输出
	return 0;
} 

```

---

## 作者：EndSaH (赞：0)

# Solution

提供一种纯构造解法。

本质上共有 4 种不同的数对：全是 0，只有上面是 1，只有下面是 1，全是 1，分别标号为 0, 1, 2, 3。

于是考虑先让两组 1 的个数相等，再不断删添让两组大小相等。

首先，让两组 1 的个数相等：

> 0 号不管。考虑将 1 号全部丢到第一组，2 号全部丢到第二组，这样两组便有了各自 1 的个数，且与 1 号 2 号数量相等。此时两种情况：
>
> 1. 两组个数之差超过了 3 号的个数。于是将所有的 3 号丢到少的那组，再从多的那组里面抽此时两组大小之差个数的放到少的那组。
> 2. 没有超过。于是将两组大小之差个数的 3 号扔到少的那组，然后将 3 号均匀分配到两组之中即可。若无法均匀分配（即剩下的 3 号为奇数个），就考虑将剩下的那一个放至第一组，然后抽出第一组中的一个 1 号放至第二组，这样就能保证均衡；若第一组没有，抽第二组放至第一组。都没有无解。

其次，让两组总大小相等：

> 若继承上面的第一种情况：此时只有 0 号可用，若两组大小之差超过当前 0 号个数，无解。否则首先放入 0 号使两组大小相等，然后均匀放入即可。由于 $n$ 为偶数，均匀放入绝对可行。
> 
> 继承上面第二种情况：可以发现如果如此分配两组大小最多只会相差 1，如果相差 1 则放一个 0 号到少的那组，相等不放；剩余的均匀放入即可。

因为是一个纯构造算法，实现的不垃圾就可以做到 ${\mathcal O(n)}$。

# Code

写的实在很shi...将就着看看吧233

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

#define debug(...) fprintf(stderr, __VA_ARGS__)

using std::cin;
using std::cout;
using std::endl;

const int maxN = 5e3 + 2;

int n;
int cnt[2], tw, on[2], zr;
std::string c, a;
bool vis[maxN];
std::vector<int> two, one[2], zro;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("????.in", "r", stdin);
    freopen("????.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> c >> a;
    for (int i = 0; i < n; ++i)
    {
        if ((c[i] & 1) and (a[i] & 1))
            two.push_back(i);
        else if (c[i] & 1)
            one[0].push_back(i);
        else if (a[i] & 1)
            one[1].push_back(i);
        else
            zro.push_back(i);
    }
    tw = two.size(), on[0] = one[0].size(), on[1] = one[1].size(), zr = zro.size();
    if ( (tw & 1) and !on[0] and !on[1] )
    {
        cout << "-1";
        return 0;
    }
    int flag = on[0] > on[1];
    if (on[flag] + tw <= on[flag ^ 1])
    {
        one[flag].insert(one[flag].end(), two.begin(), two.end());
        int tmp = on[flag ^ 1] - on[flag] - tw;
        tw = 0, two.clear();
        one[flag].insert(one[flag].end(), one[flag ^ 1].end() - tmp, one[flag ^ 1].end());
        if (tmp)
            one[flag ^ 1].erase(one[flag ^ 1].end() - tmp, one[flag ^ 1].end());
        flag = one[0].size() < one[1].size();
        tmp = one[flag].size() - one[flag ^ 1].size();
        if (tmp > (int)zro.size())
        {
            cout << "-1";
            return 0;
        }
        else
        {
            one[flag ^ 1].insert(one[flag ^ 1].end(), zro.end() - tmp, zro.end());
            if (tmp)
                zro.erase(zro.end() - tmp, zro.end());
            tmp = zro.size() >> 1;
            one[flag].insert(one[flag].end(), zro.begin(), zro.begin() + tmp);
            one[flag ^ 1].insert(one[flag ^ 1].end(), zro.begin() + tmp, zro.end());
            for (auto i : one[0])
                cout << i + 1 << ' ';
            return 0;
        }
    }
    else
    {

        int tmp = on[flag ^ 1] - on[flag];
        one[flag].insert(one[flag].end(), two.end() - tmp, two.end());
        tw -= tmp;
        if (tmp)
            two.erase(two.begin() + tw, two.end());
        if ((tw + zr) & 1)
            throw 0;
        if (tw & 1)
        {
            one[flag].push_back(one[flag ^ 1].back());
            one[flag ^ 1].pop_back(), one[flag ^ 1].push_back(two.back()), one[flag ^ 1].push_back(zro.back());
            zro.pop_back(), two.pop_back();
        }
        one[0].insert(one[0].end(), two.begin(), two.begin() + (tw >> 1));
        one[1].insert(one[1].end(), two.begin() + (tw >> 1), two.end());
        one[0].insert(one[0].end(), zro.begin(), zro.begin() + (zr >> 1));
        one[1].insert(one[1].end(), zro.begin() + (zr >> 1), zro.end());
        for (int i : one[0])
            cout << i + 1 << ' ';
    }
    /*
       for (auto i : one[0])
       cout << i << ' ';
       cout << endl;
       for (auto j : one[1])
       cout << j << ' ';
       cout << endl;*/
}
```

---

## 作者：Zechariah (赞：0)

本人写的巨烂。。。不喜勿喷  
我们可以列出方程（代码中有）  
一个方程两个变量，我们只需要枚举一个变量就行了，得到这两个变量的解压后就试着去构造，构造出来就是可行解，否则继续枚举
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e5 + 5, mod = 998244353, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
char s[N], t[N];
int lx[5], dui[2][5], p[5][N], n;
/*
1. 0 0
2. 1 1
3. 0 1
4. 1 0
*/
//设第一堆人中，1类型x1个，2类型x2个，3类型x3个，4类型x4个
//由题列出方程
//①x1+x2+x3+x4=n/2
//②2x2+x3+x4=c2+c3
//②-①
//x2-x1=c2+c3-n/2
inl void judge(rg int x1, rg int x2)
{
    memset(dui, 0, sizeof(dui));
    rg int c3 = lx[3], c4 = lx[4];
    if (x2 < 0 || x2>lx[2])return;
    dui[0][1] = x1, dui[0][2] = x2;
    dui[0][0] = x1 + x2;
    dui[1][1] = lx[1] - x1, dui[1][2] = lx[2] - x2;
    dui[1][0] = lx[1] - x1 + lx[2] - x2;
    while (c3&&dui[1][3] + dui[1][2] < dui[0][4] + dui[0][2])--c3, ++dui[1][3], ++dui[1][0];
    while (c4&&dui[1][3] + dui[1][2] > dui[0][4] + dui[0][2])--c4, ++dui[0][4], ++dui[0][0];
    if (dui[1][3] + dui[1][2] != dui[0][4] + dui[0][2])return;
    if (dui[1][0] > n / 2 || dui[0][0] > n / 2)return;
    if (c3 < c4)dui[1][3] += c3, dui[0][4] += c3, dui[1][4] += c3, dui[0][0] += c3, dui[1][0] += c3, c4 -= c3, c3 = 0;
    else dui[1][3] += c4, dui[0][4] += c4, dui[1][4] += c4, dui[0][0] += c4, dui[1][0] += c4, c3 -= c4, c4 = 0;
    if (dui[0][0] < n / 2)dui[0][3] += c3, dui[0][0] += c3;
    if (dui[1][0] < n / 2)dui[1][4] += c4, dui[1][0] += c4;
    if (dui[0][0] + dui[1][0] != n || dui[0][0] != dui[1][0] || dui[0][2] + dui[0][4] != dui[1][2] + dui[1][3])return;
    for (rg int i = 1; i <= 4; ++i)
    {
        for (rg int j = 1; j <= dui[0][i]; ++j)
            fast_IO::write(p[i][j]), putchar(' ');
    }
    exit(0);
}
int main(void)
{
    n = fast_IO::read();
    scanf("%s%s", s + 1, t + 1);
    for (rg int i = 1; i <= n; ++i)
    {
        if (s[i] == t[i]) { if (s[i] == '0')++lx[1], p[1][++*p[1]] = i; else ++lx[2], p[2][++*p[2]] = i; }
        else { if (s[i] == '0')++lx[3], p[3][++*p[3]] = i; else ++lx[4], p[4][++*p[4]] = i; }
    }
    for (rg int x1 = 0; x1 <= lx[1]; ++x1)
        judge(x1, lx[2] + lx[3] - n / 2 + x1);
    puts("-1");
    return 0;
}

```


---

## 作者：Aicx_ (赞：0)

## 题意:
给你长度为$n$一个二元组序列$x,y$ , 求是否可以经过任意次交换二元组后 , 满足$\sum_{i=1}^{\frac{n}{2}}$ $x_i$   $=$ $\sum_{i=\frac{n}{2}+1}^{n}$ $y_i$ . 若可以则输出交换后序列 , 若不行则输出$-1$ . 保证$n$为偶数 .

## 题解:
令$sum$ $=$ $\sum_{i=1}^{n}$ $y_i$ , 若序列满足题目要求 , 那么有 :
$$\sum_{i=1}^{\frac{n}{2}}x_i = sum - \sum_{i=1}^{\frac{n}{2}}y_i$$
移项得:
$$\sum_{i=1}^{\frac{n}{2}}x_i +  \sum_{i=1}^{\frac{n}{2}}y_i = sum$$
考虑$x_i$ $+$ $y_i$的取值,显然只有$0$ , $1$ , $2$三种可能,设 $1$ , $.$ $.$ $.$ ,$\frac{n}{2}$这样的$i$
的个数分别为$cnt0$ , $cnt1$ , $cnt2$ .
那么有:
$$ 0 × cnt0 + 1 × cnt1 + 2 × cnt2 = sum $$
$$cnt0 + cnt1 + cnt2 = \frac{n}{2}$$
这是一个三元一次方程 , 由于都是整数 , 所以枚举其中一个 , 就可以确
定其它两个 , 只要满足构造的序列满足这两个方程即可 , 复杂度 $O(n)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e6+5;
#define Is(c) ('0'<=c && c<='9')
#define re register
inline void read(int &x){
	x=0;char c=getchar();
	while(!Is(c)) c=getchar();
	while(Is(c)) x=(x<<3)+(x<<1)+c-48,c=getchar();
}
namespace cx{
	int n;
	int sum,sum0,sum1,sum2,cnt0,cnt1;
	int num[N][3];
	int main(){
		read(n);
		int x,y;
		for(re int i=1;i<=n;i++){
			read(x),read(y);sum+=y;
			if(x+y==0) num[++sum0][0]=i;
			if(x+y==1) num[++sum1][1]=i;
			if(x+y==2) num[++sum2][2]=i;
		}
		n>>=1;
		for(re int cnt2=0;cnt2<=sum2;cnt2++){
			cnt1=sum-(cnt2<<1);
			cnt0=n-cnt1-cnt2;
			if(cnt1>sum1 || cnt0>sum0 || cnt1<0 || cnt0<0 || cnt2>sum2 || cnt2<0 || cnt0>n || cnt1>n || cnt2>n) continue;
			for(re int i=1;i<=cnt0;i++) printf("%d ",num[i][0]);
			for(re int i=1;i<=cnt1;i++) printf("%d ",num[i][1]);
			for(re int i=1;i<=cnt2;i++) printf("%d ",num[i][2]);
			for(re int i=cnt0+1;i<=sum0;i++) printf("%d ",num[i][0]);
			for(re int i=cnt1+1;i<=sum1;i++) printf("%d ",num[i][1]);
			for(re int i=cnt2+1;i<=sum2;i++) printf("%d ",num[i][2]);
			return 0;
		}
		puts("-1");
		return 0;
	}
}
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	return cx::main();
}
```


---

