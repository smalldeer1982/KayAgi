# Cellular Network

## 题目描述

在直线上给出n个城市的位置(x坐标)和在同一直线上的m个蜂窝塔的位置(x坐标)。所有的塔都以同样的方式工作——它们为所有城市提供蜂窝网络，这些城市位于离塔不超过r的距离处才能被蜂窝网络覆盖。

你的任务是找出使得每个城市都能被蜂窝网络覆盖的最小r值，即每个城市在距离r的范围内至少有一个蜂窝塔。

如果r=0，则塔仅为其所在的位置提供蜂窝网络。一个塔可以为任意数量的城市提供蜂窝网络，但是所有这些城市都必须在距离塔不超过r的距离上。

## 说明/提示

1<=n,m<=10^5

-10^9<=a[i]<=10^9

-10^9<=b[j]<=10^9

## 样例 #1

### 输入

```
3 2
-2 2 4
-3 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 3
1 5 10 14 17
4 11 15
```

### 输出

```
3
```

# 题解

## 作者：shucai (赞：10)

## [题目传送门](https://www.luogu.com.cn/problem/CF702C)

### 题意

一条直线上有 $n$ 个城市和 $m$ 个塔，塔可以为它左右距离 $r$ 以下的城市提供流量，问最小 $r$ 值是多少？

### 思路

本题考查算法：贪心 & 二分。

对于一个城市，为它提供流量的肯定是离它最近的塔。求出每个城市离为它提供流量的塔的距离，它们的最大值就是我们要求的答案。

### **code**

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <queue>
#define int long long
using namespace std;
int a[100005], b[100005];
int n, m;
signed main() {
    int ans = -1e9;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= m; i++)
        cin >> b[i];

    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + m);

    for (int i = 1; i <= n; i++) {
        int k;
        /*while(b[k]<a[i]&&k<=m)
        k++;*/
        k = lower_bound(b + 1, b + 1 + m, a[i]) - b;
        //这个函数可以从它第一个参数到第二个参数间找到第一个比第三个参数大的数
        //并返回他的下标

        if (k > m) {
        //特判，如果没有比这个城市的坐标大的话，就是最后一个
            ans = max(ans, abs(b[m] - a[i]));
        } else if (k == 1) {
        //同上（没有比他小的）
            ans = max(ans, abs(b[1] - a[i]));
        } else {
            ans = max(ans, min(abs(b[k] - a[i]), abs(b[k - 1] - a[i])));
        }
    }

    cout << ans;
    return 0;
}
```



---

## 作者：苏联小渣 (赞：4)

二分套二分，但我调了大半天。

---

题目要求 $r$ 的最小值，而 $r$ 的范围可能很大，一一枚举肯定不行，考虑二分 $r$。

为什么可以二分呢？感性理解一下，这个决策显然是有单调性的。假设一个 $r_0$，那么 $r_0+k(k>0)$ 的覆盖范围肯定比 $r_0$ 更广。所以随着 $r_0$ 的增加，覆盖的范围也会不断增大。

二分的 $l$ 应该是 $0$，$r$ 要设多大呢？注意到 $a_i,b_i \in [-10^9,10^9]$，能够覆盖全部的最大值 $r_{\max}$ 就是 $2 \times 10^9$。二分模板如下：

```c++
int l=0, r=2e9;
while (l <= r){
	int mid = l + r >> 1;
	if (check(mid)) s = mid, r = mid - 1;
	else l = mid + 1;
}
```

那么 `check` 函数怎么写呢？每一次 `check` 要求出当前有多少个点可以被网络覆盖。对于每一个 $a_i$，离它最近的网络要么是 $b$ 中第一个大于等于它的，要么是 $b$ 中第一个小于等于它的。第一个大于等于的可以再一次二分查找得到，可以发现，第一个小于等于的位置就是第一个大于等于的位置 $-1$（如果第一个大于等于的就是它本身那么 $-1$ 也不影响）。所以只要用两者判断一下，如果存在一个和 $a_i$ 相差不超过 $\text{mid}$，那么这里就被网络覆盖了。如果可以覆盖的点为 $n$ 个，就返回 `true`。

最后用外面的二分可以最小化 $r$。

时间复杂度 $O(n \log(2 \times 10^9)\log n)\approx O(31n \log n)$。

细节有点多，还要开 `long long`。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, s, a[100010], b[100010];
int check(int x){
	int cnt = 0;
	for (int i=1; i<=n; i++){
		//左边不超过x，右边不超过x
		int pos1 = lower_bound(b+1, b+m+1, a[i]) - b; 
		int pos2 = pos1 - 1;
		if (pos1 > m) pos1 = m, pos2 = m;
		if (abs(a[i] - b[pos1]) <= x || abs(a[i] - b[pos2]) <= x) cnt ++;
	}
	return cnt == n;
}
signed main(){
	scanf ("%lld%lld", &n, &m);
	for (int i=1; i<=n; i++){
		scanf ("%lld", &a[i]);
	}
	sort (a+1, a+n+1);
	for (int i=1; i<=m; i++){
		scanf ("%lld", &b[i]);
	}
	sort (b+1, b+m+1);
	b[0] = 1e18;
	int l=0, r=2e9;
	while (l <= r){
		int mid = l + r >> 1;
		if (check(mid)) s = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf ("%lld\n", s);
	return 0;
}

```

---

## 作者：Trinitrotoluene (赞：4)

## 题意简述：

给出一个数轴上 $n$ 个点的坐标 $a_1$,$a_2$,$\cdots$,$a_n$ 以及 $m$ 个点的坐标 $b_1$,$b_2$,$\cdots$,$b_m$，若对于任意的 $a_i$，存在 $b_j$，使得$\operatorname{abs}$($a_i$-$b_j$) $\leq$ $ans$，求 $ans$ 的最小值。

## 题目分析

根据上述简述可知：对于任意一个点 $a_i$，若从 $m$ 个点中选出的那个点不是它左边或右边的第一个点，那么就不符合 $ans$ 最小这一条件了。

因此，我们就可以用贪心来做：求出 $a_i$ 到左边以及右边第一个点的距离的最小值 $l_i$，那么 $ans$=$\max${$l_1$,$l_2$,$\cdots$,$l_n$}。

~~由于语文表达能力有限~~，下面借助样例来进行解释。

### 样例1:

```
3 2
-2 2 4
-3 0
```

则 $l_1$=$\min${1,2}=1，$l_2$=$\min${2,+$\infty$}=2，$l_3$=$\min${4,+$\infty$}=4。

所以 $ans$=$\max${$l_1$,$l_2$,$l_3$}=4。

### 样例2：

```
5 3
1 5 10 14 17
4 11 15
```
则 $l_1$=$\min${+$\infty$,3}=3，$l_2$=$\min${1,6}=1，$l_3$=$\min${6,1}=1，$l_4$=$\min${3,1}=1，$l_5$=$\min${2,+$\infty$}=2。

所以 $ans$=$\max${$l_1$,$l_2$,$l_3$,$l_4$,$l_5$}=3。

不过，有几点需要注意：

#### 一、可能存在左边或右边没有点的情况，因此需要特判，或者令其等于-$\infty$或+$\infty$。

#### 二、可能输入的点不是按从小到大的顺序排的，因此需要排序，不过本题不用。

最后，就可以得到一份代码了。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int a[N],b[N],n,m,p,s;
inline int r(){
	int o=0,f=1;char c=getchar();
	while(c<48||c>57)	f=c^45?1:-1,c=getchar();
	while(c<58&&c>47)	o=(o<<1)+(o<<3)+(c^48),c=getchar();
	return o*f;
}
int main(){
	n=r();m=r();
	for(int i=0;i<n;++i)	a[i]=r();sort(a,a+n);
	for(int i=0;i<m;++i)	b[i]=r();sort(b,b+m);
	for(int i=0;i<n;++i){
		while(b[p]<a[i]&&p<m)	++p;
		if(p==m&&b[p]<a[i])	s=max(s,a[i]-b[p-1]);
		else if(!p)	s=max(s,b[p]-a[i]);	
		else s=max(s,min(a[i]-b[p-1],b[p]-a[i]));
	}
	printf("%d",s);
	return 0;
}
```

---

## 作者：When (赞：4)

#### 算法

贪心+二分~~不知道为什么是蓝题~~

#### 思路

显然，我们将城市与塔都按照$x$坐标排序以后，对于每一个城市，覆盖它的必然是$x$坐标与它最相近的两座塔之一，那么我们就可以二分来用城市找塔，在相邻两塔与它的距离中取$min$，再取所有城市的$max$就是答案了

**tips：** 有的城市可能在所有塔的左边或者是右边，这时它只有一种选择，需要特判一下

#### 代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
int t[maxn],c[maxn],n,m,minn;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++ i) scanf("%d", c + i);
    for(int i = 1; i <= m; ++ i) scanf("%d", t + i);
    sort(c + 1, c + 1 + n); sort(t + 1, t + 1 + m);
    for(int i = 1; i <= n; ++ i){
        int pos = lower_bound(t + 1, t + 1 + m, c[i]) - t;
        if(pos > m) minn = max(minn, abs(t[pos - 1] - c[i]));
        else if(pos - 1 <= 0) minn = max(minn, abs(t[pos] - c[i]));
        else minn = max(minn, min( abs(t[pos] - c[i]), abs(t[pos - 1] - c[i]) ));
    } printf("%d\n", minn);
    return 0;
}
```



---

## 作者：欧鹰 (赞：2)

（日常聊天），闲着无聊，来CF刷刷题，毕竟CF~~穿越这么好玩~~.



------------

题意，一个x轴，有n个终点与m个起点，找到最大的路程。

------------


然后，我们考虑做法，这其实是一道水题（与他的颜色一样水）。

其实只要先从左到右遍历，如果当前终点没有下一个终点更优，我们就到下一个终点。

因为下一个起点一定在当前起点的右边，而下一个终点也在当前终点的右边，

如果当前终点没有下一个终点到当前起点更优，那么自然下一个起点到下一个终点更优。

就是下面这代码：
```cpp
	for(int i=1;i<=cnt;i++)
	{
		if(abs(a[i]-b[j])>abs(a[i]-b[j+1])&&j<cntt)
		{
			while(abs(a[i]-b[j])>abs(a[i]-b[j+1])&&j<cntt) j++;
			
			ans=max(ans,abs(a[i]-b[j]));
		} 
		
		else ans=max(ans,abs(a[i]-b[j]));
	}
```


据本人蒟蒻分析，复杂度应该是O(N+M);

#### 还有不要忘了去重。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int x[500500],y[500500],n,m,ans,cnt,cntt,a[500500],b[500500];

signed main()//主程序 
{
	cin>>n>>m;
	
	for(int i=1;i<=n;i++) cin>>x[i];
	
	for(int j=1;j<=m;j++) cin>>y[j];
	
	sort(x+1,x+1+n);
	
	sort(y+1,y+1+m);
	
	for(int i=1;i<=n;i++)
	{
		if(x[i]==x[i+1]&&i!=n) continue;
		
		a[++cnt]=x[i];
	}
	
	for(int i=1;i<=m;i++)
	{
		if(y[i]==y[i+1]&&i!=m) continue;
		
		b[++cntt]=y[i];
	}
	
//	for(int i=1;i<=cnt;i++) cout<<a[i]<<" ";
//	cout<<endl;
//	for(int j=1;j<=cntt;j++) cout<<b[j]<<" ";
	
	int j=1;
	
	for(int i=1;i<=cnt;i++)
	{
		if(abs(a[i]-b[j])>abs(a[i]-b[j+1])&&j<cntt)
		{
			while(abs(a[i]-b[j])>abs(a[i]-b[j+1])&&j<cntt) j++;
			
			ans=max(ans,abs(a[i]-b[j]));
		} 
		
		else ans=max(ans,abs(a[i]-b[j]));
	}
	
	cout<<ans;
	
	return 0;
	
}
```


---

## 作者：lzjsy (赞：2)

## 二分答案？不存在的，

首先我比较赞同楼下dalao的说法，~~这题确实比较水~~。。。

看到dalao们都是用二分答案来解决这道题的，但其实可以用二分查找来做，具体思路和二分答案的查询操作类似。

因为我们必须保证每个城市都能够接受到信号，故只需要对每座城市（即 a ) 找到最近的蜂窝网络（ 即 b ) 

直接对b数组排一次序，每次二分查找最接近它的两个蜂窝网络，取一个最小值，最小值中的最大值就是答案了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1000010;
inline int read()
{
	int z=0,x=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') x=-1; c=getchar(); }
	while(c>='0'&&c<='9') z=z*10+c-'0',c=getchar();
	return z*x;
}
inline int abs(int a)
{
	return a<0?-a:a;
}
int n,m;
int ans=0;
int a[N],b[N];
int main()
{
	n=read(),m=read();
	for(register int q1=1;q1<=n;q1++) a[q1]=read();
	for(register int q1=1;q1<=m;q1++) b[q1]=read();
	sort(b+1,b+m+1);
	int le=1,ri=m,mid;
	for(register int q1=1;q1<=n;q1++)
	{
		int le=1,ri=m,mid;
		while(le<ri)
		{
			mid=(le+ri)>>1;
			if(a[q1]>b[mid]) le=mid+1;
			else ri=mid;
		}
		if(le!=1)
			ans=max(ans,min(abs(b[le-1]-a[q1]),abs(b[le]-a[q1])));
		else
			ans=max(ans,abs(b[le]-a[q1]));
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：莫奈的崖径 (赞：2)

qwq感觉这道题近似二分的模板题，一开始看到是蓝题被吓到了...


------------


### **思路**

题目要求找一个尽可能小的r覆盖所有城市，可以想到用二分答案。

先让r尽可能地大（初始化操作），然后二分对l+r进行二分。

如果当前的r能够覆盖所有城市，说明我们还能把r取小一点；如果当前的r不能覆盖所有城市，r就要往大取。最后返回r。


------------


### **坑点**(dalao请无视)

1.因为城市和蜂窝塔的坐标可以取负数，所以在输入的时候要找出坐标中的max和min值，为了**r尽可能大**，所以初始化r=maxn-min(0,minn)，当然看到有dalao把r初始化一个边界条件常数值也是可以的。

2.有一个测试点的数据很大，我一开始T掉。l，r，mid值开成long long就可以了。

3.要注意二分答案的边界条件和循环条件，可以手动模拟一下，不同的题目二分的写法有着细微但是举足轻重的区别，如果写错很可能就是没有输出......（就像我一样调了半天）


------------
### **AC代码**
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,m,x[N],net[N],maxn=-1,minn=0x7ffffff;
bool check(long long R)
{
    int pos=1;
    for(int i=1;i<=m;i++)
    {
    while((x[pos]>=(net[i]-R))&&(x[pos]<=(net[i]+R))&&pos<=n) pos++;
    if(pos==n+1) return true;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
    scanf("%d",&x[i]);  
    maxn=max(maxn,x[i]);
    minn=min(minn,x[i]);
    }   
    for(int i=1;i<=m;i++)
    {
    scanf("%d",&net[i]);    
    maxn=max(maxn,net[i]);
    minn=min(minn,net[i]);
    }
    long long l=0,r=maxn-min(0,minn);
    while(l<=r)
    {
        long long mid=(l+r)>>1;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    printf("%lld\n",l);
    return 0;
}
```


---

## 作者：BennyHu (赞：2)

#### 这个题其实可以不用二分。。

贪心的，每个城市被离它最近的塔覆盖 则r的值为每个城和离它最近的塔中的最大值。

直接向左向右暴力会超时，所以会想到，
如果一个城市的左边也是城市,那么位于它左边的最近的塔也就是位于它左边城市的左边的最近的塔。

先按坐标排序，城市和塔分别作标记。 然后进行预处理，处理出每个城市左边和右边分别最近的塔。

举个栗子，向左预处理
```
for(int i=n;i>0;--i)
    if(a[i].p==0&&fil[i]==-1)
        fil[i]=L_find(i);
```

核心的，找塔的函数
```
int L_find(int x)
{
if(a[x-1].p==0) return fil[x-1]=fil[x]=L_find(x-1);
else return x-1;
}
```

fil是左边最近塔的标号，fir是右边的，a数组是结构体，.x是坐标，.p是标记，0是城，1是塔。 左右没有塔的时候特判一下，然后输出，这题就完了。

附完整代码。
```
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
struct node
{
    int x,p;
}a[200005];
int fil[200005],fir[200005];
int n,m,ans;
bool cmp(node a,node b)
{
    return a.x<b.x;
}
int L_find(int x)
{
    if(a[x-1].p==0) return fil[x-1]=fil[x]=L_find(x-1);
    else return x-1;
}
int R_find(int x)
{
    if(a[x+1].p==0) return fir[x+1]=fir[x]=R_find(x+1);
    return x+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(fil,-1,sizeof(fil));
    memset(fir,-1,sizeof(fir));
    for(int i=1;i<=n;++i)
    {
        a[i].p=0;
        scanf("%d",&a[i].x);
    }
    for(int i=1;i<=m;++i)
    {
        a[n+i].p=1;
        scanf("%d",&a[n+i].x);
    }
    n+=m;
    sort(a+1,a+n+1,cmp);
    a[0].p=1;
    a[n+1].p=1;
    for(int i=n;i>0;--i)
        if(a[i].p==0&&fil[i]==-1)
            fil[i]=L_find(i);
    for(int i=1;i<=n;++i) if(a[i].p==0)
    {
        if(fir[i]==-1) fir[i]=R_find(i);
        ans=max(ans,min(fil[i]==0?2000000000:a[i].x-a[fil[i]].x,fir[i]==n+1?2000000000:a[fir[i]].x-a[i].x));
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：linaonao (赞：1)

## 思路 

我对差分不是很熟练，所以......我选择不用差分。



仔细读题面，可以发现，这道题要求的 $r$ 值肯定大于等于每一个城市与最近的蜂窝塔的距离，即：



~~~cpp
r=max(r,min(dis(tower[l-1],city[i]),dis(tower[l],city[i])));
~~~



注意点：

- $tower$数组要先升序排序好。
- 用二分求出离城市最近右边的蜂窝塔$l$和左边的$l-1$时，若$l=1$，即左边没有蜂窝塔时，只用计算右边的。

贴上代码：

## 代码

~~~cpp
#include<bits/stdc++.h>
template<typename T>inline void read(T &x){
	T f=0;x=0;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f|=ch=='-';
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    x=f?-x:x;
}
template<typename T>inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
using namespace std;
inline int dis(int a,int b){
	return abs(a-b);
}
int n,m,ans;
int city[100005],tower[100005];
int main(){
	read(n),read(m);
	for(int i=1;i<=n;++i) read(city[i]);
	for(int i=1;i<=m;++i) read(tower[i]);
	sort(tower+1,tower+m+1);
	for(int i=1;i<=n;++i){
		int l=1,r=m,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(city[i]>tower[mid]) l=mid+1;
			else r=mid;
		}
		if(l==1) ans=max(ans,dis(tower[l],city[i]));
		else ans=max(ans,min(dis(tower[l-1],city[i]),dis(tower[l],city[i])));
	}
	write(ans);
	return 0;
}

~~~



---

## 作者：oneman233 (赞：1)

这题其实挺水，不知道怎么评成了蓝题。

基本想法是二分通信塔的半径，对每一个ai判断一下左右离他最近的bi，如果左右的距离都大于r，那么显然返回false

对于找左右最近的bi可以二分，免去操作差分数组。每一次check操作的时间复杂度为O(nlogm)，总的时间复杂度O(nlogmlog最大距离)。

有几个坑点，二分时候可能会出现ai在最大的bi右侧的情况，比如样例二，这时应当把bm+1设置在非常远的位置，我使用的是0x3f3f3f3f3f3f3f3f，当我使用0x3f3f3f3f时会WA

同理，b0也应当设置在-0x3f3f3f3f3f3f3f3f的位置，第三个测试点数据如下：

1 1

1000000000

-1000000000

答案应当是2000000000，同时也说明二分答案的上限也就是2e9了。

代码如下：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100005;
const int inf=0x3f3f3f3f3f3f3f3f;

int n,m;
int a[maxn],b[maxn];

bool chk(int r)
{
    for(int i=1;i<=n;++i){
        int pos=lower_bound(b+1,b+1+m,a[i])-b;
        if(a[i]-b[pos-1]>r&&b[pos]-a[i]>r)
            return false;
    }
    return true;
}

void half(int l,int r)
{
    while(l<=r){
        int m=(l+r)/2;
        if(chk(m))
            r=m-1;
        else
            l=m+1;
    }
    printf("%lld",l);
}

signed main()
{
    scanf("%lld %lld",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%lld",&a[i]);
    for(int j=1;j<=m;++j)
        scanf("%lld",&b[j]);
    b[0]=-inf;b[m+1]=inf;
    half(0,2000000000);
    return 0;
}

```


---

## 作者：_byta (赞：1)

提供一种两只 $log$ 的做法。

我们可以看出答案满足单调性，所以可以二分。

在判断时我们首先要找到距离这个城市最近的蜂窝塔，在判断他们两个的距离是否大于二分的值。找最近的蜂窝塔我们可以排序之后用 lower_bound 求。所以复杂度又带了一只 $log$。

似乎可以预处理优化到一只 $log$。

不过既然过了就不纠结了，想要优化的可以自行尝试。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N], d[N];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
bool check(int x)
{
    int flag = 0;
    for (int i = 1; i <= n; i++)
    {
        t = lower_bound(b + 1, b + m + 1, a[i]) - b;
        if(t == 1)
        {
            if(abs(b[t] - a[i]) > x) { flag = 1; break; }
        }
        else if(t > m) 
        {
            if(abs(a[i] - b[m]) > x) { flag = 1; break; }
        }
        else 
        {
            int mn = min(abs(b[t - 1] - a[i]), abs(b[t] - a[i]));
            if(mn > x) { flag = 1; break; }
        }
    }
    if(!flag) return 1;
    else return 0;
}
signed main()
{
	n = read(); m = read();
	for (int i = 1; i <= n; i++) a[i] = read(); 
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) b[i] = read();
	sort(b + 1, b + m + 1);
	l = 0, r = 1e18;
	while (l <= r)
	{
	    int mid = (l + r) >> 1;
	    if(check(mid)) ans = mid, r = mid - 1;
	    else l = mid + 1;
	}
	cout << ans << endl;
    return 0;
} 
```

难度似乎评高了，顶多黄题吧。

---

## 作者：ImposterAnYu (赞：0)

# 题意
给定 $n$ 个城市在数轴上的位置和 $m$ 个蜂窝塔在数轴上的位置，第 $i$ 个城市的位置为 $a_i$，第 $j$ 个蜂窝塔的位置为 $b_j$。求最小的 $r$，使得 $\forall\ 1 \leq i \leq n$，都至少有一个 $j(1 \leq j \leq m)$，使得 $i$ 和 $j$ 满足 $\vert a_i - b_j \vert \leq r$。
# 解析
首先，因为为一个城市供网的蜂窝塔一定是离这个城市最近的蜂窝塔，所以我们很容易就可以想到贪心：对于每个 $i$，我们都可以找到使得 $\vert a_i - b_j \vert$ 最小的 $j$（记为 $x_i$），也就是找到离城市 $i$ 最近的蜂窝塔 $x_i$，这样一来，最后的答案 $r$ 就是 $\max\limits_{1 \leq i \leq n}{\vert a_i - b_{x_i} \vert}$ 了。（为什么要取最大值呢？因为要保证每个城市都能在 $r$ 的距离内找到一个蜂窝塔为其供网。）

问题是：我们如何找到离城市 $i$ 最近的蜂窝塔 $x_i$ 呢？每次都暴力扫一遍吗？不可能的，因为 $n$ 和 $m$ 都很大，直接暴力扫绝对会超时。这里提供 $2$ 种方法：
## 1. 用 lower_bound（二分查找）。
`STL` 里面有个好东西，名字叫做 `lower_bound`，一般我们这样调用它：
```
int p = lower_bound(a + x,a + y + 1,z) - a;
```
~~看着好奇怪啊。~~

调用这一行代码后，$p$ 的值就会变为数组 $a$ 中 $\left[x,y\right]$ 这个区间内第一个 $\ge z$ 的元素的下标。如果这段区间内没有 $ \geq z$ 的元素，则 $p = y + 1$。

`lower_bound` 的工作原理是二分查找，所以它的时间复杂度和二分查找一样，都是 $O(\log(y - x + 1))$ 的。当然，和二分查找一样，使用 `lower_bound` 有个前提条件，就是数组 $a$ 单调不降或单调上升。

所以，我们可以用它，来快速地找到符合条件的 $x_i$。
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 1145141919810114514
using namespace std;
int1 n,m,i,j,a[100005],b[100005],s,x;
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	n = read(),m = read();
	for(i = 1; i <= n; i++){
		a[i] = read();
	}
	for(i = 1; i <= m; i++){
		b[i] = read();
	}
	sort(b + 1,b + m + 1);//保证使用 lower_bound 时数组 b 单调不降或单调上升。 
	a[n + 1] = b[m + 1] = p,a[0] = b[0] = -p;//设个边界，防止溢出。
	for(i = 1; i <= n; i++){
		x = lower_bound(b + 1,b + m + 1,a[i]) - b;//找到第一个坐标不小于 a[i] 的 b[j]。 
		s = max(s,min(b[x] - a[i],a[i] - b[x - 1]));//根据 lower_bound 的特性，可以得出 b[j - 1] 的坐标一定比 a[i] 小。 
	}
	print(s);
  	return 0;
}
```
时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。[AC记录。](https://www.luogu.com.cn/record/78719686)
## 2. 优化了亿下的暴力。
假如我们将 $a,b$ 都按升序排序，我们就可以得出一个结论：当 $i < j$ 时，$x_i \leq x_j$。因为排序后，$a_i \leq a_j$，$b_i \leq b_j$，所以 $x_j$ 相较于 $x_i$，只能更大，不能更小。

这样一来，我们就不需要每次暴力都重新扫一遍了,而是可以从上一次的答案稍加修改就得到了！
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 1145141919810114514
using namespace std;
int1 n,m,i,j,a[100005],b[100005],s,x;
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	n = read(),m = read();
	for(i = 1; i <= n; i++){
		a[i] = read();
	}
	for(i = 1; i <= m; i++){
		b[i] = read();
	}
	sort(a + 1,a + n + 1); 
	sort(b + 1,b + m + 1);
	a[n + 1] = b[m + 1] = p,a[0] = b[0] = -p;//设个边界，防止溢出。 
	for(i = 1; i <= n; i++){
		while(b[x] < a[i]){//如果 b[x] < a[i]，x 就一直加 1，直到 b[x] 刚好 >= a[i] 为止（和 lower_bound 的结果一样）。 
			x++;
		}
		s = max(s,min(b[x] - a[i],a[i] - b[x - 1]));//统计答案。 
	}
	print(s);
  	return 0;
}
```
时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$，但是代码量稍微多两行。[AC记录。](https://www.luogu.com.cn/record/78725567)

#### 2024.7.19补充（来自@[Lily_White](https://www.luogu.com.cn/user/87696)）：其实这个方法就是排序后双指针（

---

## 作者：cyrxdzj (赞：0)

### 一、前置芝士

`lower_bound` 函数，用于求出数组中第一个大于给定数据的位置。

参数：

1. 数组第一个元素的指针。

2. 数组最后一个元素再往右边的指针。

3. 给定数据。

返回：数组所求位置的指针。可以将返回值直接减去数组，得出一个数字，代表位置。

使用示例：`int position=lower_bound(tower+1,tower+1+m,city[i])-tower;`

特殊情况：如果数组中没有数据大于给定数据，则返回参数 $2$ 的值。

### 二、思路

本题可以使用贪心与二分算法。

首先，将所有城市和蜂窝塔的位置从小到大排序。

然后，对于每个城市，用 STL 的 `lower_bound` 函数辅助，寻找离这个城市最近的蜂窝塔，并得出距离。

最后，将这些距离取最大值，即为答案。

### 三、完整代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
int city[100005],tower[100005];
int ans=0;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&city[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&tower[i]);
	}
	sort(city+1,city+1+n);//排序。
	sort(tower+1,tower+1+m);
	for(int i=1;i<=n;i++)
	{
		int position=lower_bound(tower+1,tower+1+m,city[i])-tower;//寻找第一个在城市右边的蜂窝塔。
		if(position>m)//如果这个城市在所有蜂窝塔的右边：
		{
			ans=max(ans,abs(city[i]-tower[position-1]));//取城市左边的蜂窝塔。
		}
		else if(position<=1)//如果这个城市在所有蜂窝塔的左边：
		{
			ans=max(ans,abs(city[i]-tower[position]));//取城市右边的蜂窝塔。
		}
		else
		{
			ans=max(ans,min(abs(city[i]-tower[position]),abs(city[i]-tower[position-1])));//在城市两边的蜂窝塔中取最近的。
		}
	}
	printf("%d\n",ans);
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

对于每个城市，计算出它跟网络塔的最近距离，再对这一堆数据取最大值即可。

### 2 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int max_t=200000;
const int max_num=2000000000;//设置一个极大值2乘10的9次方
int n,m;
struct C{//城市结构体
	int x;//坐标
	bool k;//类型
		//0 城市  1 网络塔
}a[max_t+2];
bool cmp(C a,C b){return a.x<b.x;}//升序排一遍
int min_d=2000000000;
int ans=0;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].x);
		a[i].k=false;
	}
	for(int i=1;i<=m;++i){
		scanf("%d",&a[i+n].x);
		a[i+n].k=true;
	}
	sort(a+1,a+n+m+1,cmp);
	for(int i=1;i<=n+m;++i){
		if(!a[i].k){//这是一个城市
			int d1=max_num,d2=max_num;
			for(int j=i;j>=1;--j){
				if(a[j].k){//蜂窝塔
					d1=a[i].x-a[j].x;
					break;
				}
			}
			for(int j=i;j<=n+m;++j){
				if(a[j].k){//蜂窝塔
					d2=a[j].x-a[i].x;
					break;
				}
			}
			ans=max(ans,min(d1,d2));
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

By **dengziyue**

---

## 作者：pengyule (赞：0)

大家好，这是我做的第二道 CF 题，写的第一篇 CF 题解，如果没看的太懂轻多多包涵！

## 算法：二分答案+差分
做这道题的思路是，首先我们用二分答案来寻找最小的 $r$，然后应该有一个 check 的函数。怎么 check 呢？我们想，枚举每一个信号点，判断他能够覆盖到的地方，最后看一看是不是所有的城市都被覆盖到了，就好了，我们就返回真，否则返回假。

那么怎么把能够覆盖的地方标记一下呢？我们肯定不可能去逐一判断城市是不是在该信号点的覆盖范围内。然后我们想到差分，直接把能够覆盖到的地方全部加一就好了。（如果你还不会差分，请看题解最下面的网址中我的博客，里面有讲简单的差分操作和原理。）但是我们能这么做吗——这个信号点的坐标是 $x$，我们把数轴上 $x-dis$ ~ $x+dis$ 全部标记下来（其中 $dis$ 是二分到的 $r$）。这样的空间复杂度一定是 $10^9$ 级别的，不能通过。

然后我们想，那我们可以把 $a$ 数组中的可以被覆盖到的城市标记啊。好，那我们就想从 $1$ 到 $n$ 枚举城市，看一看这个城市是不是大于等于 $x-dis$ 且小于等于 $x+dis$。可是，这样复杂度又高起来了，不能行。所以我们又想到二分，二分到 $a$ 数组中第一个大于等于 $x-dis$ 的数，以及最后一个小于等于 $x+dis$ 的数，也即是这个可以覆盖到的城市区间的左端点与右端点。然后我们把这一段差分加上 $1$ 就好了。

当然，还有一些细节，如根本没有城市满足要求，或者左端点在右端点的右边等等不合实际的情况，一一筛去，具体操作见代码及注释。
## 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;//记得开long long要不会TLE或者RE
const ll MaxD=1e9*2+5;//最大r大约不能超过这个数
int n,m;
ll a[100010],b[100010];//如题
ll p[100010];//差分数组
bool check(ll dis){
    memset(p,0,sizeof(p));//每一次都要归零，因为这是新一次在判断每个城市是否满足
    ll x,y;
    ll L,R,mid,u,v;
    for(int i=1;i<=m;i++){
        x=b[i]-dis,y=b[i]+dis;
        L=0,R=n+1;
        while(L<R-1){//寻找左端点
            mid=(L+R)/2;
            if(a[mid]<x) L=mid;
            else R=mid;
        }
        if(R==n+1) continue;//R根本没变说明没有一个城市在左端点范围内，如果不太清楚可以看一下题解最下方的图一
        u=R;
        L=0,R=n+1;
        while(L<R-1){//寻找右端点
            mid=(L+R)/2;
            if(a[mid]>y) R=mid;
            else L=mid;
        }
        if(L==0) continue;//L根本没变说明没有一个城市在有端点范围内，如果不太清楚可以看一下题解最下方的图二
        v=L;
        if(u>v) continue;//左端点比右端点还大
        p[u]++,p[v+1]--;//区间加法（差分）
    }
    for(int i=1;i<=n;i++){
        p[i]+=p[i-1];//前缀和差分实现
        if(p[i]==0) return false;//城市没被覆盖
    }
    return true;
}
void Finddis(){//二分r
    ll L=-1,R=MaxD,mid;
    while(L<R-1){
        mid=(L+R)/2;
        if(check(mid)) R=mid;
        else L=mid;
    }
    cout<<R<<endl;
}
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
    Finddis();
    return 0;
}
```
## 复杂度分析
1. 第一层：二分 $r$，复杂度 $\log (2\times 10^9+5)$
2. 第二层：枚举信号点，复杂度 $m$
3. 第三层：二分寻找覆盖区间左右端点，复杂度 $\log n$

总复杂度：$O(m\cdot\log n\cdot \log (2\times 10^9+5))$，不应超过 $10^8$ 次运算。
## 附件
- **图片**
![image.png](https://i.loli.net/2020/05/29/FoSpN5ZseKDmT4O.png)（图一）
![image.png](https://i.loli.net/2020/05/29/ZsR2gL8c97oHVFm.png)（图二）

- **学习网址**

[差分算法（大家可以只看下半部分）](https://www.luogu.com.cn/blog/hellosandy/wei-yun-suan-yu-ci-fen-suan-fa)

谢谢大家，希望这篇题解对你有帮助！

---

