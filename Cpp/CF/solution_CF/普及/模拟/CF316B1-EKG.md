# EKG

## 题目描述

一家医院的挂号处，排起了一条长度为 $n$ 的队，这 $n$ 个人依次编号为 $1\sim n$

一个人只会记得他前面的人的编号，而其中的某些人，已经忘记了前面人的编号。

给出 $n$ 和 $pos$ ，请求出编号为 $pos$ 的人在队伍中所有可能站的位置。

## 说明/提示

$0 \le a_i \le n$  
$1 \le n,pos \le 1000$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
6 1
2 0 4 0 6 0
```

### 输出

```
2
4
6
```

## 样例 #2

### 输入

```
6 2
2 3 0 5 6 0
```

### 输出

```
2
5
```

## 样例 #3

### 输入

```
4 1
0 0 0 0
```

### 输出

```
1
2
3
4
```

## 样例 #4

### 输入

```
6 2
0 0 1 0 4 5
```

### 输出

```
1
3
4
6
```

# 题解

## 作者：Priori_Incantatem (赞：4)

双倍经验：  
[CF316B1 EKG](https://www.luogu.com.cn/problem/CF316B1)  
[CF316B2 EKG](https://www.luogu.com.cn/problem/CF316B2)

仔细观察题目，我们发现给出的队列信息形成了若干条链。而最终的完整队列是由这些小的链组成的，且队内顺序不能交换

想要找出所有 $pos$ 可能站的位置，我们就需要找出站在他前面所有可能的链的组合（前面人的个数）

首先，我们肯定能想到暴力枚举，时间复杂度 $O(2^n)$，显然不行  
仔细撕烤发现，我们只需要知道 $1\sim n$ 中，那些值能被若干条链长总和凑出来，并不需要知道怎么凑出来的  
也许你已经发现，这跟01背包的用途非常像

我们只需要将每一个链长（除了 $pos$ 所在的链）当成一个物品，跑一边01背包就可以了，时间复杂度 $O(n^2)$

最后别忘了，我们是要求 $pos$ 前面的人数，所以需要求出 $pos$ 所在的小链中排第几个，我们设这个值为 $val$。对于每一个能被其他若干条链长凑出的值 $x$，我们输出 $x+val$

**AC代码**

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=1000+20,inf=0x3f3f3f3f;
int nxt[Maxn],a[Maxn];
bool f[Maxn],vis[Maxn];
int n,m,val,pos;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),pos=read();
	
	for(int i=1;i<=n;++i)
	{
		int x=read();
		if(x)nxt[x]=i,vis[i]=1;
	}
	for(int i=1;i<=n;++i)
	{
		if(vis[i])continue;
		int cnt=0,x=i;
		while(x)
		{
			++cnt;
			if(x==pos){val=cnt;goto GG;}
			x=nxt[x];
		}
		a[++m]=cnt;
		
		GG:;
	}
	f[0]=1;
	for(int i=1;i<=m;++i)
	{
		for(int j=n;j>=a[i];--j)
		if(f[j-a[i]])f[j]=1;
	}
	for(int i=0;i<=n;++i)
	if(f[i])printf("%d\n",i+val);
	
	return 0;
}
```

---

## 作者：chl090410 (赞：1)

## CF316B1 题解

### 题目大意

$n$ 个编号为 $1\sim n$ 的人排队，给出排在一些人前面的人，问编号为 $pos$ 的人所有可能的位置。

#### 数据范围

$1\le n,pos\le 1000$，$0\le a_i\le n$

### 分析

由题目中的信息可将这 $n$ 个人划分为 $k$ 个小队，而总队伍就由这 $k$ 个小队任意排列而成。

我们先用 $f$ 数组记录每个人后面的人，没有则记为 $0$。

若 $a_i=0$，则说明第 $i$ 个人不记得前面是谁了，那么在他所处的小队中，因为他前面没有人，所以他就是该队伍中的第一个人。

我们以每个 $a_i=0$ 的位置 $i$，利用 $f$ 数组向后遍历所有小队直至队尾，求出每个小队的长度，然后将编号为 $pos$ 的人所在小队以外的小队的长度储存在数组 $t$ 中，再求出编号为 $pos$ 的人在他所在小队中的位置。

我们可以选取若干个小队排在编号为 $pos$ 的人所在小队的前面，当然，也可以不选。我们将每个小队（编号为 $pos$ 的人所在小队除外）的长度看作一个物品，然后可以使用[ 01 背包](https://oi-wiki.org/dp/knapsack/)求出编号为 $pos$ 的人所在小队的前面的人数的所有可能性。

最后输出每个可能人数 $+$ 编号为 $pos$ 的人在他所在小队中的位置。

总时间复杂度为 $O(n^2)$，能通过。

### 下面附上完整代码

```
#include <bits/stdc++.h>
using namespace std;
int ly[1005],a[1005],f[1005],t[1005],kl[1005],s=1,k,n,ff,m=1,u;
int main(){
	cin>>n>>u;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=0){
			f[a[i]]=i;
		}
	}
	for(int i=1;i<=n;i++){
		int p=i;
		if(a[p]==0){
			while(f[p]!=0){
				if(p==u){
					s=m;
					ff=1;
				}
				m++;
				p=f[p];
			}
			if(p==u){
				s=m;
				ff=1;
			}
			if(ff!=1){
				t[++k]=m;
			}
			m=1;ff=0;
		}
	}
	ly[0]=1;
	for(int i=1;i<=k;i++){
		for(int j=n;j>=0;j--){
			if(ly[j]==1){
				ly[j+t[i]]=1;
			}
		}
	}
	for(int i=0;i<=n;i++){
		if(ly[i]==1){
			cout<<s+i<<endl;
		}
	}
	return 0;
}




---

## 作者：2huk (赞：1)

> 一家医院的挂号处，排起了一条长度为 $n$ 的队，这 $n$ 个人依次编号为 $1\sim n$。
>
> 一个人只会记得他前面的人的编号，而其中的某些人，已经忘记了前面人的编号。
>
> 给出 $n$ 和 $pos$ ，请求出编号为 $pos$ 的人在队伍中所有可能站的位置。
>
> $n \le 10^3$。

套路建图。将 $a_i \to i$ 连边，表示 $a_i$ 在 $i$ 前面。那么显然图中有多条链。

我们要做的就是把这些链连起来，求 $pos$ 有几种在链中的位置。

首先可以 $\mathcal O(2^n)$ 枚举连在 $pos$ 之前的链，然后计算位置。但是是不优的，考虑优化。

首先求出 $pos$ 在它那条链的位置，记为 $k$。然后需要选择一些剩下的链放在这条链之前。若令剩下的链的长度组成的序列为 $\{a_i\}_{1 \le i \le len}$，那么问题就变成了：

> $a$ 中元素相加的和有多少种。

可以直接类似背包的 DP。设 $f_{i, j}$ 表示用前 $i$ 个长度，能否拼成长度 $j$。转移有：
$$
f_{i, j} = f_{i - 1, j} \operatorname{or}f_{i - 1, j - a_i}
$$
其中 $\operatorname{or}$ 是或运算。

然后找到所有满足 $f_{len, i}$ 为真的 $i$，那么 $i + k$ 即为答案。

代码实现细节较多。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

// to[i] 表示 i 的上一个人，lst[i] 表示 i 的下一个人
int n, a[N], to[N], lst[N];
vector<int> v;
bool st[N];
int k, x;
bool f[N][N];		// 用前 i 个物品能否凑出 j

int main() {
	cin >> n >> x;
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		if (a[i]) to[i] = a[i], lst[a[i]] = i, st[a[i]] = true;
	}
	
	int X = x;
	k = 1;
	while (to[x]) {
		++ k;
		st[x] = true;
		x = to[x];
	}
	st[x] = true;
	x = X;
	while (lst[x]) {
		st[x] = true;
		x = lst[x];
	}
	st[x] = true;
	
	for (int i = 1; i <= n; ++ i ) {
		if (!st[i]) {
			int k = 1, x = i;
			while (to[x]) {
				++ k;
				x = to[x];
			}
			v.push_back(k);
		}
	}
	
	int len = v.size();
	for (int i = 0; i <= len; ++ i ) f[i][0] = true;
	for (int i = 1; i <= len; ++ i ) {
		int w = v[i - 1];
		for (int j = 1; j <= n; ++ j ) {
			f[i][j] = f[i - 1][j];
			if (j >= w)
				f[i][j] |= f[i - 1][j - w];
		}
	}
	
	for (int i = 0; i <= n; ++ i )
		if (f[len][i])
			cout << i + k << '\n';
	
	return 0;
}
```



---

## 作者：RiceFruit (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF316B2)

## 题目大意

给你正整数 $n$ 和 $pos$，和 $n$ 个非负整数 $a_i$，表示第 $i$ 个人前面的人，若 $a_i$ 为 $0$ 表示他不确定前面是谁。让你求出第 $pos$ 个人可能排在哪里。

## 题目思路

我们可以将一堆连续的一起的人看做一条链。而链与链之间的顺序可以任意。而对于一条链，它若排在一条链的前面，则会让那条链往后移；如果它排在一条链的后面，则不会有影响。应该都看出来了吧，就是裸的 `01` 背包。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
inline int read();
int n,pos,wz;
int pre[N];
int blo[N],blct;
bool b[N];
bool f[N];
signed main(){
	n=read(),pos=read();
	for(int i=1;i<=n;i++){
		pre[i]=read();
		b[pre[i]]=1;
	}
	for(int i=1;i<=n;i++){
		if(!b[i]){
			int cnt=1,now=i;
			bool as=(i==pos);
			while(pre[now]){
				now=pre[now];
				cnt++;
				if(now==pos)as=1;
			}
			blo[++blct]=cnt;
			if(as==1){
				int ct=1,nw=i;
				if(nw!=pos)
					while(pre[nw]){
						nw=pre[nw];
						ct++;
						if(nw==pos){
							break;
						}
					}
				wz=cnt-ct+1;
				blct--;
			}
		} 
	}
	f[0]=1;
	for(int i=1;i<=blct;i++){
		for(int j=n;j>=blo[i];j--){
			f[j]|=f[j-blo[i]];
		}
	}
	for(int i=0;i<=n;i++)
		if(f[i])
			printf("%d\n",i+wz);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

---

## 作者：3ksc03_is_sb (赞：1)

# 前言
**经验 double!**  
[CF316B1 EKG](https://www.luogu.com.cn/problem/CF316B1)  
[CF316B2 EKG](https://www.luogu.com.cn/problem/CF316B2)  
# 正文
## 题目大意
给出 $n$ 和 $pos$，再给出每个人前面的人的编号，问第 $pos$ 个人站哪里。  
## 思路
我们发现，这些人排的队伍似乎是一条条链，我们首先可以想到暴力枚举，但时间复杂度为 $O(2^n)$，肯定 TLE。
我们又发现，题目只需要第 $pos$ 个人所站的编号。这意味着我们并不需要爆搜，我们只需要求出在所有的链中，$pos$ 的位置能被哪些链凑出来。聪明人肯定发现了，这就是 **01 背包**！这样，我们就只需要把链长看成价值，把所有链（除了第 $pos$ 个人所在的链）跑一次 01 背包就能轻松过了。时间复杂度 $O(n^2)$。
## 代码实现
有了思路还不够，我们想想代码怎么写。首先，我们发现题目中的某些 $a_i$ 的值是 0。我们可以在代码中把他视为链的第一个节点，每个节点的值是他的编号。我们还要建一个 $vis$ 数组，如果这个数不是 0，就把 $vis_i$ 设为 1，以后遍历时遇到就 continue，可以减少很多不必要的搜索。接着，我们一个个链搜下去，如果遇到了 $pos$ 所在的链，就把 $pos$ 站的位置存入变量中，否则就把链的长度存入数组中。  
附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1145/*14*/;
bool dp[N],vis[N],flag;
int l[N],si[N],n,pos,num,tot,x,cnt;
signed main(){
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin>>n>>pos;
    for(int i=1;i<=n;++i){
        cin>>x;
        if(x){
            l[x]=i;
            vis[i]=1;
        }
    }
    for(int i=1;i<=n;++i){
        if(vis[i]) continue;
        flag=0;//用来判断是不是pos所在链
        cnt=0;//链长度
        x=i;//编号
        while(x){
            ++cnt;
            if(x==pos){
                num=cnt;
                flag=1;
                break;
            }//如果是，就退出
            x=l[x];//继续遍历
        }
        if(!flag) si[++tot]=cnt;//如果不是pos所在链，就把长度存数组
    }
    dp[0]=1;
    for(int i=1;i<=tot;++i){
        for(int j=n;j>=si[i];--j){
            if(dp[j-si[i]]) dp[j]=1;
        }
    }//01背包，如果可行就设为1
    for(int i=0;i<=n;++i){
        if(dp[i]) cout<<(i+num)<<"\n";
    }//注意，我们要求pos的位置，所以要把上面的num加上
    return /*191981*/0;//玄学
}
```

---

## 作者：bloodstalk (赞：0)

## Description
题目给的很清楚了。

## Solution

你会发现这个操作最终会把这个序列切分成若干条链，那么很显然，最终的答案就是选取若干个链，再把答案所在的那条链接到后头，所有可能的结果就是答案。

暴力枚举是 $O(2^n)$ 的，考虑怎么优化。

我们发现，我们只是关心答案的位置，并不关心它前面是由哪几条链组成的。而答案的位置是由链的长度拼接而来的，你会发现这其实是一个  01 背包问题，每个链的价值就是它的长度，跑一遍 01 背包后，看看这个长度是否能够被凑出来，再加上答案在其所在的链的位置即可。

可以看出来，我们跑 01 背包的时候，是要把答案所在的链剔除出去的。

这样，复杂度就是 $\mathcal O(n^2)$，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 1e3 + 5;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n,m,x,pos,cnt,wz;
bool flag;
int f[N],next[N],a[N];
bool head[N];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

signed main()
{
	n = read() , pos = read();
	memset(head , 1  , sizeof head);//head[i]表示判断i是不是一条链的起点
	for(re int i=1;i<=n;i++)
	{
		x = read();
		if(!x) continue;
		next[x] = i , head[i] = 0;//i有前缀，它就不可能是起点了
	}
	for(re int i=1;i<=n;i++)
	{
		if(!head[i]) continue;//从链头开始计数，所以不是链头的continue掉
		int p = i; cnt = 0 , flag = 1;
		while(p)
		{
			++cnt;
			if(p == pos) { wz = cnt; flag = 0; break; }//剔除答案所在的链
			p = next[p];
		}
		if(flag) a[++m] = cnt;
	}
	f[0] = 1;
	for(re int i=1;i<=m;i++)
		for(re int j=n;j>=a[i];j--)
			f[j] += f[j-a[i]];//跑一下
	for(re int i=0;i<=n;i++) if(f[i]) cout << i + wz << "\n";
	return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
题目大意是有 $n$ 个人，给出每个人的前面的人（可能为 $0$，即不记得），求第 $pos$ 个人站在哪里。

不难发现，这些人组成了一条又一条的链。暴力枚举是 $O(2^n)$ 的，因为存在有人不记得的情况，所以明显不可以过。但不难发现，我们只需要求出一个人的位置即可。所以这一题就变为了一个背包问题，因为不存在多个前驱，所以只需要把除了第 $pos$ 个人所在的链跑一遍，链长作为价值，对，就是 01 背包。时间复杂度为 $O(n^2)$，是十分充裕的。

因为存在为 $0$ 的情况，我们可以将它设为链的开头，值就是编号。再用一个记忆化数组来剪枝。如果找到了一个存在 $pos$ 的链，就存入，否则存链的长度到数组 $c$ 里。接下来是 01 背包，如果 $dp_{j-c_i}=1$，就把 $dp_j$ 设为 $1$。然后从头到尾遍历一遍，注意要加上开头的位置。

[AC 记录](https://codeforces.com/problemset/submission/316/297218316)

---

