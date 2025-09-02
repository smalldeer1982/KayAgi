# 『XYGOI round1』一些数

## 题目背景

MX 在研究排列所具有的性质。这一天，她拿出了 $n$ 张卡片排成一排，想要在上面填数以写成一个 $1\sim n$ 的排列。  

Piggy 趁 MX 不注意，偷偷在一些卡片上写了数。

## 题目描述

MX 很快发现了这一切。不过她并不生气，而是考虑一个有趣的问题：如果我在上面填一些数，让它依然构成一个排列，且它的最长上升子序列长度为 $n-1$，MX 有多少种填数方法呢？    

Piggy 比较良心。他没有在不同的位置上填相同的数。

## 说明/提示

#### 样例解释
用 $-1$ 代表此位置数字还未确定。  
样例 $1$：第一组给定的排列为 $-1,2,-1,8,-1,5,6,-1,-1,-1$。容易发现，只有 $1,2,3,8,4,5,6,7,9,10$ 的最长上升子序列长度为 $10-1=9$。第二组给定的排列为 $-1,-1$，$2,1$ 为唯一满足要求的序列。

**本题采用捆绑测试。**


| Subtask | $\sum n$ | $\sum q$ |  分值 |
|:-:|:-:|:-:|:-:|
|0|$\le 10$|$\le 10$|10|
|1|$\le 15$|$\le 10$|20|
|2|$\le 5\times 10^3$|$\le 5\times 10^3$|30|
|3|$\le 5\times 10^5$|$\le 5\times 10^5$|40| 

保证 $ 0\le q\le n$，$1\le n\le  5\times 10^5$，$1\le T\le 10^5$，$1 \le x,y \le n$。

## 样例 #1

### 输入

```
2
10 4
2 2 4 8 6 5 7 6
2 0```

### 输出

```
1
1```

## 样例 #2

### 输入

```
2
40 21
1 1 2 2 6 6 7 7 8 8 9 9 10 10 11 11 15 15 16 16 23 23 24 24 25 25 26 26 30 30 34 35 35 36 36 37 37 38 38 39 40 40
40 15
3 3 4 4 14 14 15 15 17 17 19 19 24 23 25 24 27 26 30 29 31 30 33 32 35 34 39 38 40 39```

### 输出

```
4
4
```

# 题解

## 作者：Piggy343288 (赞：12)

首先我们考察 LIS 长度为 $n-1$ 的数列的性质。可以发现，这必定是 $1,2,3,\cdots,n$ 中拎出一个不听话的元素甩到其他地方去，剩下的元素依次补齐所构成的。这意味着，最多只有一个元素满足 $a_i-i\ge2$，更具体的，不考虑只对邻项交换的排列（即形如 $1,2,3,\cdots,i,i-1,\cdots,n$），每个满足要求的排列都有且仅有一个元素满足 $a_i-i\ge 2$。  

接下来对所有钦定了值的元素进行考察。这意味着下文中我们已经默认了 $a_i\not=-1$。  

- 所有 $a_i=i$。那么我们只能对下标的空隙部分做操作。也就是假设相邻的两个下标分别为 $i,j$，那么这一段对答案的贡献是 $(j-i-2)^2$。不难写出如下的代码：  
```
int cur = 0;
for(int i = 1; i <= n; i++){
	if(!~a[i]) cur++;
	else if(cur){
		ans += pow(cur - 1, 2);
		cur = 0;
	}
}
if(cur) ans += pow(cur - 1, 2);
```
- 存在 $|a_i-i|\ge 2$。因为这样的 $i$ 只能有一个，所以如果找到多个这样的下标直接 `cout<<0<<"\n"` 走人。即使仅有一个这样的 $i$，合法的也最多只能有一个排列。因此判断一下是否合法即可。不难写出下面的代码：
```
int p = -1;
for(int i = 1; i <= n; i++){
	if(!~a[i]) continue;
	if(abs(a[i] - i) >= 2){
		if(~p) return false;
		else p = i;
	}
}
if(~p){
	//found one abs(a[i] - i) >= 2
	if(a[p] > p){
		int l = p, r = a[p];
		for(int i = 1; i <= n; i++){
			if(!~a[i]) continue;
			if((i < l || i > r) && a[i] != i) return false;
			if((i > l && i <= r) && a[i] != i - 1) return false;
		}			
	}else{
		// just a reversion of a[p] > p...
		int l = a[p], r = p;
		for(int i = 1; i <= n; i++){
			if(!~a[i]) continue;
			if((i < l || i > r) && a[i] != i) return false;
			if((i >= l && i < r) && a[i] != i + 1) return false;
		}
	}
}
```
- 存在 $a_i=i+1,a_{i+1}=i$。这种比较好判断，而且也最多只能存在一个这样的 $i$。  
```
int cnt = 0;
for(int i = 1; i <= n; i++){
	if(a[i] != i && ~a[i]){
		if(a[i] == i + 1 && a[i + 1] == i) i++, cnt++;
		else return false;				
	}
}
if(!cnt) return false;
```
> 在写代码的时候，我把上述两个情况合并在一起了。因为它和下面的情况相差较大，但这两个本质是一个情况，即指定了开头所提到的“不听话的元素”。  

- 存在一段 $a_i=i+1$ 或一段 $a_i=i-1$。注意判断仅能存在一个这样的段！因此我们不难写出下面的代码，其中 $flag$ 标志了目前在什么阶段（进入段前，段中，第一段后）。  
```
int flag = 0;
p = 0;
for(int i = 1; i <= n; i++){
	if(!~a[i]) continue;
	if(a[i] == i){
		if(flag == 1) flag = 2;// signal if i is out of the offset area.
	}else{
		// a[i] != i
		r = i;
		if(flag == 0){
			//no offset currently
			p = a[i] - i;
			l = i, flag = 1;// into the offset area;
		}else{
			if(flag == 1){
				if(a[i] - i != p) return false;
			}else{
				assert(flag == 2); return false;// out of the offset area and found another section,
				// which is impossible to generate any valid solution in this occasion.
			}
		}
	}
}
return true;
```
```
int lcnt = 0, rcnt = 0;
for(int i = l - 1; i && !~a[i]; i--) lcnt++;
for(int i = r + 1; i <= n && !~a[i]; i++) rcnt++;
ans = 1ll * lcnt * rcnt;
ans += (~p ? rcnt : lcnt);
```  
把几段代码融合一下，就得到了此题的代码。完整代码不给！

---

## 作者：bloodstalk (赞：3)

## Description
在长度为 $n$ 的排列里给定一些数，问把剩下的数填上，最后排列的 LIS 为 $n-1$ 的方案数。

## Solution
大力分讨。

我们发现一个长度为 $n$ 的排列的最长上升子序列是 $n-1$ 的话，就相当于是把 $1\sim n$ 中的一个数取出来插到另两个数之间，这样除去它最长上升子序列就是 $n-1$ 了，那我们要做的就是找出这样的一个元素，判断它的情况，并看看是否有多种这样的元素，是的话就是无解的。

接下来我们观察一下钦定的元素值具有的性质，然后进行分类讨论。

- 所有给出的 $a_i$，满足 $a_i = i$

这其实就等价于把这个区间分成了若干块，你不能把一个块的一个元素插入到另一个块里面，这样就会导致某些给出的 $a_i$ 是不能等于 $i$ 的，因为被挤掉了，所以贡献就只会在每个块之内产生。

设两个相邻的 $a_i = i$ 的元素之间有 $x$ 个空，那么每个数都可以插到除去它自己的 $x-1$ 个空里面，贡献就是 $x(x-1)$，但是这样会算重，因为相邻两个数之间的交换本质上是一种，但是会被算两遍，$x$ 个数中有 $x-1$ 对相邻的数，那么把它减去即可，最后答案就是 $(x-1)^2$。

- 仅存在一个 $a_i = i$，满足 $|a_i-i| \ge 2$，其余的要么 $a_i = i$，要么为空。

这相当于就是给了我们那个被取出来的数，既然给出来了，那就说明其余 $n-1$ 个位置是不能变的了，应当满足一个 $1\sim n$ 除去 $a_i$ 这个数的升序关系，我们让它和给出的序列对应一下，如果对应成功，存在唯一解，否则不存在。

- 仅存在一个 $a_i = i+1$ 且 $a_{i+1} = i$，其余的要么 $a_i = i$，要么为空。

这个本质上和上面这种情况是一种情况，把它单独拎出来的原因是，和第一种情况相似的，相邻的情况其实两种方案本质上是一种方案，而如果采用第二种方法的判断方式就会出错，所以单独考虑。最后的判断和第二种是一样的。

- 仅存在一段连续的区间，满足 $a_i =i+1$ 或 $a_i = i-1$，其余的要么 $a_i = i$，要么为空。

这个条件说明这一段连续的区间是被影响的一段区间，也就是被那个元素挤出了原来的位置，我们找到这个区间的左右端点 $l_0,r_0$，然后分别向左右延申找到第一个 $a_i = i$ 的位置 $l_1,r_1$，设这两段区间内的元素个数分别为 $l,r$（不包括 $l_0,l_1,r_0,r_1$）。与第一种情况同理的，方案只会从左边 $l$ 个数中选一个插到右边 $r+1$ 个空中，方案数是 $l(r+1)$，或是从右边 $r$ 个数中选一个插到左边 $l+1$ 个空中，方案数是 $(l+1)r$。不能再从 $l$ 左边或 $r$ 右边选的原因同第一种情况的原因。

画个图模拟一下可以得出，如果这段是 $a_i = i-1$，是右边的插到左边，方案数是 $(l+1)r$；如果是 $a_i=i+1$，是左边的插到右边，方案数是 $l(r+1)$。

然后这个分讨题就做完了。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 5e5 + 5;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int T,n,q,x,y;
ll ans;
int a[N],pos;
int kind,l,r,dif;
bool flag;

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il void Calc1()
{
	int now = 0;
	for(re int i=1;i<=n;i++)
	{
		if(!a[i]) now++;
		else if(now)
		{
			ans += pow(now-1,2);
			now = 0;
		}
	}
	if(now) ans += pow(now-1,2);
}

il void Calc4()
{
	int lcnt = 0 , rcnt = 0;
	for(re int i=l-1;i && !a[i];i--) lcnt++;
	for(re int i=r+1;i<=n && !a[i];i++) rcnt++;
	ans = 1ll * lcnt * rcnt;
	if(dif == 1) ans += rcnt; else ans += lcnt;	
}

il bool check1()
{
	flag = 1 , pos = 0;
	for(re int i=1;i<=n;i++)
	{
		if(!a[i]) continue;
		if(abs(a[i]-i) >= 2)
		{
			if(!pos) pos = i;
			else return false;
		}	
	}
	if(pos)
	{
		int val = a[pos];
		if(val > pos)
		{
			int l = pos , r = val;
			for(re int i=1;i<=n;i++)
			{
				if(!a[i]) continue;
				if((i < l || i > r) && a[i] != i) return false;
				if((i > l && i <= r) && a[i] != i-1) return false;
			}
		}
		else
		{
			int l = val , r = pos;
			for(re int i=1;i<=n;i++)
			{
				if(!a[i]) continue;
				if((i < l || i > r) && a[i] != i) return false;
				if((i >= l && i < r) && a[i] != i+1) return false;
			}
		}
		return true;
	}
	else
	{
		for(re int i=1;i<=n;i++)
		{
			if(a[i] != i && a[i])
			{
				if(a[i] == i+1 && a[i+1] == i && !pos) pos = i , i++;
				else return 0;
			}
		}
		if(!pos) return false; 
	}
	return true;
}

il bool check3()
{
	kind = l = r = dif = 0;
	for(re int i=1;i<=n;i++)
	{
		if(!a[i]) continue;
		if(a[i] == i)
		{
			if(kind == 1) kind = 2;
		}
		else
		{
			r = i;
			if(!kind)
			{
				kind = 1 , l = i;
				dif = a[i] - i;
			}
			else
			{
				if(kind == 1)
				{
					if(a[i] - i != dif) return 0;
				}
				else return false;
			}
		}
	}
	Calc4();
	return true;
}

signed main()
{
	T = read();
	while(T--)
	{	
		n = read() , q = read();
		for(re int i=1;i<=n;i++) a[i] = 0;
		ans = 0 , flag = 1;
		while(q--)
		{
			x = read() , y = read();
			a[x] = y;
			if(x != y) flag = 0;
		}
		if(flag) { Calc1(); cout << ans << "\n"; continue ; }
		if(check1()) ans = 1;
		else check3();
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：_edge_ (赞：3)

开到这题的时候，我的内心是拒绝写这个题的。

因为情况有点多，当然，情况多不代表它一定非常困难，其实还是挺简单的。

考虑这么一件事情，最长上升子序列个数为 $n$ 的时候，排列一定为 $1,2,3,4,5,6,7,\cdots ,n$。

然后我们只需要在这上面进行修改即可，通过各种手玩发现只需要将一个数挪到另外一个位置即可。

证明也非常简单，因为挪动了之后这个排列一定不能组成 $n$ 个最长上升子序列，然后 $n-1$ 的最长上升子序列即为踢出那个元素。

于是我们只需要，判断一个数是否能挪动到另外位置。

值得一提的是，交换相邻两个数会重复计算，即前面那个挪到后面，后面那个挪到前面。

现在，我们已经能够写出一个暴力的东西了，枚举那个挪动的元素，挪动到哪里，然后判这种方案是否合法，具体的，可以稍微手玩一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/b5fqsffn.png)

$O(n^3)$ 是可以做到的，但是这东西居然过掉了 $n \le 5000$。

一看这东西就很能优化的样子。

容易发现如果我们枚举了那个要挪动的元素，那么那么上图绿色合法的一段是单调的，后缀也是单调的，蓝色那个特判一下就可以了。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
int n,q,num[INF];
void solve() {
    cin>>n>>q;
    for (int i=1;i<=n;i++) num[i]=-1;
    for (int i=1;i<=q;i++) {
        int x=0,y=0;cin>>x>>y;
        num[x]=y;
    }
    int ans=0;
    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) {
            if (num[j]==-1 || num[j]==i) {
                int fl=0;
                for (int k=1;k<i;k++)
                    if (num[k]==-1 || num[k]==k) ;
                    else fl=1;
                for (int k=i;k<j;k++)
                    if (num[k]==-1 || num[k]==k+1) ;
                    else fl=1;
                for (int k=j+1;k<=n;k++)
                    if (num[k]==-1 || num[k]==k) ;
                    else fl=1;
                if (!fl) ans++;
            }
        }
    }

    for (int i=1;i<=n;i++) {
        for (int j=1;j<i-1;j++) {
            if (num[j]==-1 || num[j]==i) {
                int fl=0;
                for (int k=1;k<j;k++)
                    if (num[k]==-1 || num[k]==k) ;
                    else fl=1;
                for (int k=j+1;k<=i;k++)
                    if (num[k]==-1 || num[k]==k-1) ;
                    else fl=1;
                for (int k=i+1;k<=n;k++)
                    if (num[k]==-1 || num[k]==k) ;
                    else fl=1;
                if (!fl) ans++;
            }
        }
    }
    cout<<ans<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    int t=0;cin>>t;
    while (t--) solve();
    return 0;
}
```

上面那个是 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
int n,q,num[INF],f[INF],f1[INF],sum2[INF],sum4[INF],sumw[INF],p[INF];
void solve() {
    cin>>n>>q;
    for (int i=1;i<=n;i++) num[i]=p[i]=-1;
    for (int i=1;i<=q;i++) {
        int x=0,y=0;cin>>x>>y;
        num[x]=y;p[y]=x;
    }
    if (n==1) {cout<<"0\n";return ;}
    f[0]=1;
    for (int i=1;i<=n;i++) {
    	if (num[i]==-1 || num[i]==i) f[i]=f[i-1];
    	else f[i]=0;
	}
	f1[n+1]=1; 
	for (int i=n;i;i--) {
		if (num[i]==-1 || num[i]==i) f1[i]=f1[i+1];
		else f1[i]=0;
	}
	for (int i=1;i<=n;i++) sum2[i]=sum2[i-1]+!(num[i]==-1 || num[i]==i+1);
	for (int i=1;i<=n;i++) sumw[i]=sumw[i-1]+(num[i]==-1);
	for (int i=1;i<=n;i++) sum4[i]=sum4[i-1]+!(num[i]==-1 || num[i]==i-1);
    int res=0;
    for (int i=1;i<=n;i++) {
    	if (!f[i-1]) continue;
    	int l=i+1,r=n,ans=-1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (sum2[Mid-1]-sum2[i-1]==0) l=(ans=Mid)+1;
			else r=Mid-1;
		}
		if (ans==-1) continue;
    	l=i+1,r=n;
		int ans2=-1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (f1[Mid+1]) r=(ans2=Mid)-1;
			else l=Mid+1;
		}
		if (ans2==-1) continue;
        res+=max(0ll,sumw[ans]-sumw[ans2-1])+(p[i]>=ans2 && p[i]<=ans);
    }

    for (int i=1;i<=n;i++) {
        if (!f1[i+1]) continue;
    	
//    	if (p[i]!=-1 && p[i]<i-1) res+=solve5(i,p[i]);
        int l=1,r=i-2,ans=-1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (sum4[i]-sum4[Mid]==0) r=(ans=Mid)-1;
			else l=Mid+1;
		}
		if (ans==-1) continue;
		l=1,r=i-2;
		int ans2=-1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (f[Mid-1]) l=(ans2=Mid)+1;
			else r=Mid-1;
		}
		if (ans2==-1) continue;
//		for (int j=ans;j<=ans2;j++) {
//            if (num[j]==-1 || num[j]==i) res++;
//        }
		res+=max(0ll,sumw[ans2]-sumw[ans-1])+(p[i]>=ans && p[i]<=ans2);
    }
    
    cout<<res<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    int t=0;cin>>t;
    while (t--) solve();
    return 0;
}
```

值得一提的是，二分加上上面那个注释掉的，居然过掉了本题（

---

## 作者：wind_seeker (赞：1)

~~分讨有点小多。~~

首先可以确定的一点是，如果最长上升子序列长度为 $n-1$ 那么就证明一定只有一个数是排在了比原先靠前的位置，其余的数往后顺延，或者是一个数排在了比原先靠后的位置，其余的数往前顺延。

#### 1.编号与位置一样
如果说填的数全部与编号一样，那么答案应该为将 $x$ 排序之后，$\sum (x_i-x_{i-1}-2)^2$，这个贡献的含义是在一段未填区间内一个数错位的方案数，具体证明如下：

- 设未填区间长度为 $len$。先取出一个数错位，则对于该数有 $len-1$ 个位置可以填，方案数为 $(len-1)\times len$。而后考虑到相邻两个数交换的情况会在计算两次，所以减去一个 $len-1$ 的贡献。

- 最后证明错位只能在一段连续的未填区间内。假设有一个数错位，越过该区间左端点。若区间左端点为 $p$，该数为 $q$，则必有一个数 $r$ 小于 $p$ 填至 $p$ 右端，则 $q,p,r$ 三数单调下降，至多只有一个数出现在最长上升子序列上，故不符合题目要求。

#### 2.编号与数发生错位

考虑之前所说两种错位方法，则可以确定的是错位的必然是一个连续的区间，所以我们找到最大可能的连续区间。

- 定义 $minl$ 为已填数中最小错位位置，$maxr$ 为已填数中最大错位位置，$numl$ 为 $minl$ 左侧与其相连未填连续区间长度，$numr$ 为 $maxr$ 右侧与其相连未填连续区间的长度。

而后判断其是否合法，为以下情况：

1. $a_{minl}$ 的值位于 $[maxr,maxr+numr]$ 之间，证明有一个数往前错位，需满足 $a_i=i-1(minl+1\le i\le maxr)$，答案为 $1$。
2. $a_{maxr}$ 的值位于 $[minl-numl,minl]$ 之间，证明有一个数往后错位，需满足 $a_i=i-1(minl\le i\le maxr-1)$，答案为 $1$。
3. 满足 $a_i=i+1(minl\le i\le maxr)$，则在左侧未填区间内有数错位至右侧未填区间，方案数为左侧未填数，乘以右侧位置 $(numl+1)\times numr$。
4. 满足 $a_i=i-1(minl\le i\le maxr)$，同理得 $numl\times(numr+1)$。

**最后注意判断 $minl=maxr$。**


### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+1e3;

int T,n,m,a[N],ans;

void solve(){
	cin>>n>>m;ans=0;
	for(int i=0;i<=n+1;i++) a[i]=0;
	bool fl=true;int minl=n+1,maxr=0,numl=0,numr=0;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;a[x]=y;fl&=(x==y);//cout<<x<<" "<<a[x]<<endl;
		if(x!=y) minl=min(minl,x),maxr=max(maxr,x);
		//cout<<x<<" "<<a[4]<<endl;
	}
	if(fl){//如果原本就按顺序填好了
		int lst=0,ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]==i){
				int len=i-lst-1;
				if(len) ans+=(len-1)*(len-1);
				lst=i;
			}
		}
		int len=n-lst;
		if(len) ans+=(len-1)*(len-1);
		cout<<ans<<'\n';
		return;
	}
	//有一个特殊性质是，被改变的一定是连续段
	for(int i=minl-1;i>=1;i--) {if(a[i]) break;else numl++;}
	for(int i=maxr+1;i<=n;i++) {if(a[i]) break;else numr++;}
	//printf("minl:%lld a:%lld\n",minl,a[minl]);
	//printf("minl:%lld numl:%lld maxr:%lld numr:%lld\n",minl,numl,maxr,numr);
	if(a[minl]==minl+1){
		for(int i=minl;i<maxr;i++){
			if(a[i]&&a[i]!=i+1){cout<<0<<'\n';return;}
		}
		if(a[maxr]==maxr+1) cout<<(numl+1)*numr<<'\n';
		else if(a[maxr]<=minl&&a[maxr]>=minl-numl) cout<<1<<'\n';
		else cout<<0<<'\n';
	}
	else if(a[maxr]==maxr-1){
		for(int i=minl+1;i<=maxr;i++){
			if(a[i]&&a[i]!=i-1){cout<<0<<'\n';return;}
		}
		if(a[minl]==minl-1) cout<<numl*(numr+1)<<'\n';
		else if(a[minl]>=maxr&&a[minl]<=maxr+numr) cout<<1<<'\n';
		else cout<<0<<'\n';
	}
	else if(minl==maxr){
		if(a[maxr]<maxr&&a[maxr]<=minl&&a[maxr]>=minl-numl) cout<<1<<'\n';
		else if(a[minl]>minl&&a[minl]>=maxr&&a[minl]<=maxr+numr) cout<<1<<'\n';
		else cout<<0<<'\n';
	} 
	else cout<<0<<'\n';
}

signed main(){
	//首先可以确定的一点是，如果最长上升子序列长度为n-1
	//那么就证明一定只有一个数是排在了比原先靠前的位置，其余的数往后顺延
	//或者是一个数排在了比原先靠后的位置，其余的数往前
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;while(T--) solve();
}
/*
1
100 2
2 2 5 5
*/
```

---

## 作者：樱雪喵 (赞：0)

排版奇怪的原因是这是之前写 ppt 怕自己忘词写的注释。  

## Description

钦定一些位置的值，问有多少长度为 $n$ 的排列满足条件，且最长上升子序列长度为 $n-1$。  

$\sum n \le 10^5,\sum q \le 10^5$。  

## Solution

我们考察最长上升子序列长度为 $n-1$ 的排列有什么性质，它其实就是忽略其中一个位置，其余位置的数按递增顺序排列得到的序列。那也可以理解为，把一个 $1\sim n$ 完全有序的排列挑一个数拎出来，再把它随便挑一个位置插回去。  

显然原排列所有的 $i$ 都等于 $a_i$，考虑经过上述操作后，拎出来的这个数后来到的位置 $|a_i-i|\ge 1$，中途经过的这一段数都平移了一位，$|a_i-i|=1$。其余位置在上述操作前后的值不变，即 $|a_i-i|=0$。  
也就是说，除去这个数只移动一位的情况，排列合法的必要条件为有且仅有一个位置 $|a_i-i|\ge 2$。而这就启发我们按已经钦定的这些位置 $|x_i-y_i|$ 的值对答案分类讨论。  

- 所有 $x_i=y_i$。每个 $x_i$ 把序列分成若干段，每段的贡献为 $(x_i-x_{i-1}-2)^2$。
>因为钦定了一些位置的值没有动，就是说取出再插回去的操作是不能跨段进行的。只能从这一段内取出一个数，再插回同一段内。    
>这段有 $len$ 个数，删去后还有 $len-1$ 个位置，一共有 $len(len-1)$ 种方案。这东西看起来很对，但你发现它是会重复的。  
>比如 $a=1,2,3,4,5$，当把 $3$ 拎出来放到 $4$ 后面，和把 $4$ 拎出来放到 $3$ 前面实际上是一样的。考虑问题的本质是什么，交换相邻位的操作被前后算了两次，一共有 $len-1$ 对相邻位被多算了一次，答案是 $len(len-1)-(len-1)=(len-1)^2$。
- 存在 $|x_i-y_i|\ge 2$。合法排列最多只有一个，可以 $O(n)$ 判断。
>既然已经有一个 $x_i-y_i\ge 2$ 了，可以确定它一定就是被拎出来的那一个。那整个排列就是可以唯一确定的。我们 $O(n) $ 判断一下这个排列和钦定位置的值匹不匹配就好了，匹配答案是 $1$，不匹配就是 $0$。
- 存在 $x_i=i+1,x_{i+1}=i$。同上。
>排列的相邻两项被交换，之前已经说过会存在重复计数的问题，故我们就钦定这种情况都是从前面取数插到后面。其余和上面 $x_i-y_i\ge 2$ 的情况是一样的。
- 存在连续的一段 $x_i=y_i-1$ 或 $x_i=y_i+1$。答案分别为 $(y_{st}-y_{st-1}-1)(y_{ed+1}-y_{ed})$ 和 $(y_{st}-y_{st-1})(y_{ed+1}-y_{ed}-1)$。
>存在连续的一段 $x_i-y_i=1$ 或 $-1$，也就是说操作的数跨越了这一段。  
>当 $x_i=y_i-1$ 时，就是这部分整体前移了一位，即移动的数是从 $x_i$ 前面的空隙里移到 $y_i$ 后面的空隙里。
>至此我们就分类讨论了所有情况，时间复杂度 $O(n)$，实现得好一点也可以是 $O(q)$。

---

