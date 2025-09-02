# ABCDEF - ABCDEF

## 题目描述

You are given a set S of integers between -30000 and 30000 (inclusive).

Find the total number of sextuples ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/60da4a6ec7452a0168508bec756f9c6a0109d346.png) that satisfy:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/5ae23b14079f628cec1090fc74b452939c2ffbe4.png)

### Input

The first line contains integer N (1

Elements of S are given in the next N lines, one integer per line. Given numbers will be distinct.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
2
2
3
```

### 输出

```
4```

## 样例 #3

### 输入

```
2
-1
1
```

### 输出

```
24```

## 样例 #4

### 输入

```
3
5
7
10
```

### 输出

```
10```

# 题解

## 作者：alex_liu (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/SP4580)


## 前置芝士：
meet in the middle 算法 （又叫 split and merge 算法）

顾名思义这种算法就是同时从两个点往中间搜索，直到碰头为止

而使等式两边未知数个数相等或尽量均匀分布是用 meet in the middle 算法解决等式问题的常见方法

## 思路：

首先转化一下题目中的式子：

$$a \times b+c=d \times (e+f)$$

由式子可知：$a$、$b$、$c$ 与 $d$、$e$、$f$ 是互不相干的

所以可以先算出 $a$ 、$b$、$c$，再算 $d$、$e$、$f$ 即可

也就是说，先搜索 $a \times b + c$ 的所有可能结果，然后搜索 $d \times ( e + f )$ 的所有可能结果，最后将两步的结果合起来即可得到答案
### 坑点：$d=0$

理解了思路，接下来就看代码啦

## CODE ：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}//快读优化 
int n,ans,c1,c2,a[105],a1[2000005],a2[2000005],cnt[2000005];
signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) {
    	for(int j=1;j<=n;j++){
    		for(int k=1;k<=n;k++){
    			c1++;
    			a1[c1]=a[i]*a[j]+a[k];//枚举 a b c 
			}
		}
	}
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
    		for(int k=1;k<=n;k++){
    			if(a[i]!=0){//注意特判 
    				c2++;
    				a2[c2]=a[i]*(a[j]+a[k]);//枚举 d e f 
				}
			}
		}
	}
    sort(a1+1,a1+c1+1),sort(a2+1,a2+c2+1);
    for(int i=1,j=1;i<=c2;i++){
        if(i!=1&&a2[i]==a2[i-1]){
			cnt[i]=cnt[i-1];
			continue;
		}
        while(a1[j]<=a2[i]&&j<=c1){
            if(a1[j]==a2[i])cnt[i]++;
            j++;
        }
    }
    for(int i=1;i<=c2;i++)ans+=cnt[i];
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：南宫家二少 (赞：3)


看到大佬都用的啥Meet in the middle（~~那是啥~~）

我太弱了，map又要超时，只能用Hash表了

枚举a,b,c将其值Hash

再枚举d,e,f，判断是否相等，再用加法原理算出答案就好了


记得Hash时要给原数加上一个很大的值，让它变成正数


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e2+10;
const int maxh=1e6+10;
const int mod1=1e6+7;
const ll mod2=9e8+1e7;//要加的数
int n;
int X[maxn];
ll ans;
ll cnt[maxh];
ll head[maxh],tot=0;
ll Nxt[maxh];
ll HSAH[maxh];
inline void finit()
{
	freopen("input.txt","w",stdin);
	freopen("output.txt","r",stdout);
}

template <typename T>inline void read(T &x)
{
	char ch=getchar();T f=1;x=0;
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	x*=f;
}

inline void readdata()
{
	read(n);
	for(int i=1;i<=n;i++)
	read(X[i]);
}

inline void insert(ll x)
{
	ll key=(x+901000000LL)%mod1;//取余Hash，最简单的Hash
	for(int i=head[key];i;i=Nxt[i])
	if(HSAH[i]==x)
	{
		cnt[i]++;//方案数++
		return;
	}
	//这里就像邻接链表一样（就是图论里的加边）
	Nxt[++tot]=head[key];
	head[key]=tot;
	HSAH[tot]=x;
	cnt[tot]++;
}

inline ll query(ll x)
{
	ll key=(x+901000000LL)%mod1;
	for(int i=head[key];i;i=Nxt[i])
	{
		if(HSAH[i]==x)
		return cnt[i];
	}
	return 0;
}

inline void work()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
			{
				ll temp=X[i]*X[j]+X[k];
				insert(temp);
			}
			
	for(int i=1;i<=n;i++)
	{
		if(!X[i])
		continue;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
			{
				ll temp=(X[j]+X[k])*X[i];
				ans+=query(temp);
			}
	}
	
	printf("%lld",ans);
}

int main()
{
//	finit();
	readdata();
	work();
	return 0;
} 
```


---

## 作者：zhengzhi726 (赞：3)

本题分析复杂度 有30分是暴力枚举
同时我们观察到存在一个减号 于是移项通分除化乘
发现化为了  + = + 的形式
那么左等于右分别枚举。
n^4的复杂度加巨大常数过不去
于是二分化为n^2 logn或者n^3过去即可

```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 110
using namespace std;
int s[maxn],cnt,num[5000000];
int erfen2(int x)
{
    int l = 1,r = cnt,res = 0;
    while(l <= r)
    {        int mid = (l+r)>>1;
        if(x >= num[mid]){l = mid+1;res = mid;}
        else r = mid - 1;    }
    return res;
}

int erfen1(int x)
{
    int l = 1,r = cnt,res = 0;
    while(l <= r)    {
        int mid = (l+r)>>1;
        if(x <= num[mid]){r = mid-1;res = mid;}
        else l = mid + 1;    }
    return res;
}

int main(){
    int n,ans = 0;
    cin>>n;
    for(int i = 1;i <= n;i++) cin>>s[i];
    cnt = 0;
    for(int a=1;a<=n;a++) 
    for(int b=1;b<=n;b++)
    for(int c=1;c<=n;c++)
        num[++cnt] = s[a]*s[b]+s[c];
    sort(num+1,num+cnt+1);
    for(int d=1;d<=n;d++) 
    for(int e=1;e<=n;e++)
    for(int f=1;f<=n;f++)
        if(s[d] != 0) 
        {
            int x = s[d]*(s[e]+s[f]);
            
            int r = erfen2(x),l = erfen1(x);
            if(r >= l && r != 0 && l != 0)
            ans+=1+r-l;
        }
    cout<<ans;
    return 0;
}
```

---

## 作者：风随逐影 (赞：2)

# 这么经典的hash题怎么能没有hash表题解呢？
暴力枚举O(N^6)，考虑将除号移过去，把等式分为左右两部分，时间复杂度将至O(N^3).hash表查询O(1),总时间复杂度(N^3)


------------
```
#include<bits/stdc++.h>
using namespace std;
#define go(i,a,b) for(int i=(a);i<=(b);++(i))
#define com(i,a,b) for(int i=(a);i>=(b);--(i))
#define mem(a,b) memset((a),(b),sizeof(a))
#define inf 0x3f3f3f3f
#define fin freopen("input.txt","r",stdin)
#define fout freopen("output.txt","w",stdout)
const int maxn=1e6+50,mod=1e6+7;
long long a[105];
int cnt=0,head[maxn],nxt[maxn],num[maxn],key[maxn]; 
  
void read(long long &x){
    int f=1;char s=getchar();x=0;
    while(!isdigit(s)){
        if(s=='-') f=-1;s=getchar();
    }
    while(isdigit(s)){
        x=(x<<3)+(x<<1)+s-'0';s=getchar();
    }
    x*=f;
}//读入优化
  
void insert(long long x){
    int h=(x%mod+mod)%mod;
    for(int i=head[h];i+1;i=nxt[i]) 
    if(key[i]==x){num[i]++;return;}
    nxt[cnt]=head[h],num[cnt]=1,key[cnt]=x,head[h]=cnt++;
}
long long get(long long x){
    int h=(x%mod+mod)%mod;
    for(int i=head[h];i+1;i=nxt[i]){
        if(key[i]==x) return num[i];
    }
    return 0;
}
   
int main()
{
    //fin;//fout;
    mem(head,-1);
    int n;scanf("%d",&n);
    go(i,1,n) read(a[i]);
    go(i,1,n)go(j,1,n) go(k,1,n){
        insert(a[i]*a[j]+a[k]);
    }
    long long ans=0;
    go(i,1,n)go(j,1,n) go(k,1,n){
        if(!a[k]) continue;//不能用除以0 
        ans+=get((a[i]+a[j])*a[k]);
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：1234567890sjx (赞：1)

原题的方程式是：
$$
\frac{a\times b+c}{d}-e=f
$$
那么首先把 $e$ 移到右边。
$$
\frac{a\times b+c}{d}=e+f
$$
然后把 $d$ 也移到右边。
$$
a\times b+c=d\times e+d\times f
$$
那么考虑先枚举计算出左边 $a\times b+c$ 的值，然后枚举右边 $d\times e+d\times f$ 的值，计算一下有多少个不同的 $(a,b,c)$ 满足 $a\times b+c=d\times e+d\times f$ 即可。

上面的统计三元组部分可以用一个 `map` 来维护。

时间复杂度是 $O(n^3\log n)$ 的。

---

## 作者：dingshengyang (赞：1)

+ 算法 $1$：暴力枚举，时间复杂度 $O(n^6)$，死死的 TLE。

考虑优化。

首先，把原式

$\dfrac{a\times b + c}{d}-e=f$

变成：

$\dfrac{a\times b+c}{d} = f+e$

再变化：

$a\times b+c=(f+e)\times d$

使用折半搜索的思想，先枚举等号左边的 $a,b,c$。得到结果 $ans_i$；

然后搜索等号右边的 $d,e,f$，得到结果 $ans'_i$；

当 $ans_i = ans'_i$，则累加 $ans_i$ 出现的次数。

但是这题直接开数组是不行的。

开 `map` ：一共要算 $n^3 \log_2 n^3=10^6\log_2 10^6$，不稳。

开 `unordered_map`。

```cpp
#include <bits/stdc++.h>
using namespace std;
unordered_map<int,int> mp;
int n,ans;
int a[105];
int main(){
	cin >> n;
	for(int i = 1;i <= n;i ++)cin >> a[i];
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++)
			for(int k = 1;k <= n;k ++)
				mp[a[i]*a[j]+a[k]] ++;
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++)
			for(int k = 1;k <= n;k ++)
				if(a[k] != 0)//注意 d 不能为 0
					ans += mp[(a[i]+a[j])*a[k]];
	cout << ans << endl;
	return 0;
}
```

---

## 作者：__ZXYAKIOI__ (赞：1)

# SP4580 ABCDEF - ABCDEF 题解

## 题意

给你一个集合 $S$，求：

$$
\frac {a \times b + c} {d} = e + f
$$

其中 $a,b,c,d,e,f \in S,|S| \le 100$。

## 做法

首先，看见这个烦人的分数，我们可以进行一下转换：

$$
a \times b + c = d (e + f)
$$

显然，分别枚举 $a,b,c,d,e,f$，时间复杂度 $O(n^6)$，最高能达到$O(10^{12})$，是不可取的。

我们换一种枚举方式，先枚举 $a,b,c$，**找出所有的可能答案（即等号左边的式子）**，然后枚举 $d,e,f$，**找出他们的可能答案（即等号右边的式子）**，判断是否相等即可。

具体来说，我们把等号左边的式子插入到 hash 表里，然后判断等号右边可能的答案在 hash 表里出现过没有即可。

注意，还需要特判分母 $d$ 不为 $0$。

这样我们就以 $O(2 \times n^3)$ 的时间复杂度解决了本题。

## 总结

其实，上述做法就是 **Meet in the middle** 的思想，是一种用以 **获取足够高效解决方案** 的灵巧的思想。**和分治思想非常类似**，它将问题**分割成两个部分**，然后**试着合并这两个子问题的结果**。**用一点额外的空间，解决两倍规模的原来可以解决的问题。**

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

map<int,int> mp;
int n;
int a[100 + 9];
int ans;

signed main(){
	cin >> n;
	for(int i=1;i<=n;++i) cin >> a[i];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)
				++mp[a[i]*a[j]+a[k]]; // 枚举 ab+c
	for(int i=1;i<=n;++i)
		if(a[i]) // 特判 d
			for(int j=1;j<=n;++j)
				for(int k=1;k<=n;++k)
					ans += mp[a[i]*(a[j]+a[k])]; // d(e+f)
	cout << ans << endl;
	return 0;
}
```

---

## 作者：xzyxzy (赞：1)

枚举6个会TLE

所以Meet in the middle 枚举3个

~~辣鸡~~用Map会TLE

还有注意d=0是不合法的

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1000100;
int n,s[N],w[N],v[N],B[N],cnt;
ll ans;
int find(int x)
{
	int l=1,r=cnt,res=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(B[mid]>=x) r=mid-1,res=mid;
		else l=mid+1;
	}
	return B[res]==x?v[res]:0;
}
void Get(int op)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
			{
				if(op==1) w[++cnt]=s[i]*s[j]+s[k];
				else if(s[k]!=0) ans+=find((s[i]+s[j])*s[k]);
			}
	if(op==1)
	{
		sort(w+1,w+cnt+1);
		int top=0;
		for(int i=1;i<=cnt;i++)
			if(w[i]==B[top]&&top) v[top]++;
			else B[++top]=w[i],v[top]=1;
		cnt=top;
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	Get(1);Get(2);
	printf("%lld\n",ans);
}
```
~~广告：MITM以及搜索有关（舞蹈链、退火啥的）[https://www.cnblogs.com/xzyxzy/]~~

---

## 作者：ivyjiao (赞：0)

一看 $n\leq 100$ 和 $360$ 毫秒的时限，想到 $O(n^3)$。

于是开始推式子：

$$\dfrac{a*b+c}{d}-e=f$$
$$\dfrac{a*b+c}{d}=f+e$$
$$a*b+c=(f+e)*d~$$
$$∴ab+c=de+df~(a,b,c,d,e,f\in S,d\neq 0)$$

然后 $O(n^3)$ 搜索即可。

建议用 `unordered_map`，普通 `map` 会 TLE。

注意 $d\neq 0$（$d=0$ 的话原式也就无意义了）。

```cpp
#include<iostream>
#include<unordered_map>
using namespace std;
int n,a[1001],b[5],ans;
unordered_map <int,int> mp;
void dfs1(int now){
    if(now==4){
        mp[a[b[1]]*a[b[2]]+a[b[3]]]++;
        return;
    }
    for(int i=1;i<=n;i++) b[now]=i,dfs1(now+1),b[now]=0;
}
void dfs2(int now){
    if(now==4){
        if(a[b[3]]) ans+=mp[a[b[1]]*a[b[3]]+a[b[2]]*a[b[3]]];
        return;
    }
    for(int i=1;i<=n;i++) b[now]=i,dfs2(now+1),b[now]=0;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    dfs1(1);
    dfs2(1);
    cout<<ans;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP4580)     
## 题意  
给你一个集合 $S$，求满足以下条件的六元祖 $(x_1,x_2,x_3,x_4,x_5,x_6)$ 的个数：    
- $x_1,x_2,x_3,x_4,x_5,x_6$ 可重复。    
- $\frac{S_{x_1}\times S_{x_2}+S_{x_3}}{S_{x_4}}-S_{x_5}=S_{x_6}$。       

## 解法
我们发现第二个条件的式子有些复杂，我们可以进行移项：    
$\frac{S_{x_1}\times S_{x_2}+S_{x_3}}{S_{x_4}}-S_{x_5}=S_{x_6}$ 先化掉左边减法：     
为 $\frac{S_{x_1}\times S_{x_2}+S_{x_3}}{S_{x_4}}=S_{x_5}+S_{x_6}$。      
我们再化左边除法：   
为 $S_{x_1}\times S_{x_2}+S_{x_3}=S_{x_4}\times(S_{x_5}+S_{x_6})$。     
我们可以发现左右正好都是三个元素，我们可以用 $O(n^3)$ 的复杂度预处理出一个桶。设 $mp$ 为这个桶，$mp_i$ 表示 $i=S_{x_1}\times S_{x_2}+S_{x_3}$ 时，有多少个三元组 $(x_1,x_2,x_3)$ 满足条件。     
之后，我们可以用 $O(n^3)$ 的复杂度对 $x_4,x_5,x_6$ 进行枚举，注意这里 $x_4$ 不能为 $0$。        
这里的 $mp$ 因为 $i$ 比较大，所以我们可以用 `unordered_map` 来实现。        
[CODE](https://www.luogu.com.cn/paste/agz4xrso)

---

