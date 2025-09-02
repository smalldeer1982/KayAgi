# Dishonest Sellers

## 题目描述

Igor found out discounts in a shop and decided to buy $ n $ items. Discounts at the store will last for a week and Igor knows about each item that its price now is $ a_{i} $ , and after a week of discounts its price will be $ b_{i} $ .

Not all of sellers are honest, so now some products could be more expensive than after a week of discounts.

Igor decided that buy at least $ k $ of items now, but wait with the rest of the week in order to save money as much as possible. Your task is to determine the minimum money that Igor can spend to buy all $ n $ items.

## 说明/提示

In the first example Igor should buy item 3 paying 6. But items 1 and 2 he should buy after a week. He will pay 3 and 1 for them. So in total he will pay $ 6+3+1=10 $ .

In the second example Igor should buy right now items 1, 2, 4 and 5, paying for them 3, 4, 10 and 3, respectively. Item 3 he should buy after a week of discounts, he will pay 5 for it. In total he will spend $ 3+4+10+3+5=25 $ .

## 样例 #1

### 输入

```
3 1
5 4 6
3 1 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 3
3 4 7 10 3
4 5 5 12 5
```

### 输出

```
25
```

# 题解

## 作者：锦瑟，华年 (赞：1)

论**sort**的方便性。

恩，这题似乎很简单，**只需要先把所有原价加起来，再减一下差值就可以了**。

换一种思路，就是先把差值尽量小的数（原价-折后价）的原价的钱数先加进来，如果有比k大的差值为负数的数的话，把这些的原价全都加起来，白捡的便宜白不捡吗。最后再把剩下的折后价加起来，这样这题就写好了。
 
恩，反正很简单，详细看代码吧。

	#include<stdio.h>
	#include<algorithm>
	using namespace std;
	int a[200005],b[200005],f[200005];
	int main(){
	   int n,k,i,ans=0;
 	   scanf("%d%d",&n,&k);
 	   for(i=1;i<=n;i++){
  	      scanf("%d",&a[i]);
       	  ans+=a[i];//把所有的原价加起来
   	    }
    	for(i=1;i<=n;i++){
        	scanf("%d",&b[i]);
        	f[i]=b[i]-a[i];//算差值
    	}
    	sort(f+1,f+1+n);//sort排序
    	i=1;
    	while(i<=n-k&&f[i]<0){//注意，要特判f[i]<0，白捡的便宜白不捡（多减一点）
        	ans+=f[i++];//减一下差值
    	}
    	printf("%d",ans);
    	return 0;
	}
    
既然这题是关于sort的排序贪心，我就再说一下stable_sort，它是稳定排序，稳定排序就是排完序后，同等的数顺序不变。而stable_sort内部是归并排序，是稳定排序的一种。详见：[传送门](https://www.luogu.com.cn/problem/T121524)，这是我自己出的。
    
好了，剩下的自己感受吧，拜拜~~，（^_^）。

---

## 作者：Leap_Frog (赞：1)

# CF779C Dishonest Sellers（题解）

### PS.
此题又是一道CF题库的恶评经典好题。  
在题解中，假设第一周的价格为$\texttt{a[]}$，第二周的价格为$\texttt{b[]}$。  
第一周与第二周之间的差值为$\texttt{c[]}$

### 题目分析
首先，这道题中不管前后都得买$\texttt{n}$个商品。  
那我们可以假设刚开始都买第一周的，然后又$\texttt{n-k}$个物品可以买成第二周的。  
那么我们理所当然想到取处理第一周与第二周的差值。  
那么答案为第一天所有物品之和加上一些物品的差值和。  
又因为第一天所有物品之和是一个定值。  
那么可以想到一个贪心，按照物品的差值排序，尽量取最差值为负数的或前$\texttt{k}$个最小的。  

所以代码出世了。

### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct good
{
	int fir,sec;
	inline bool operator<(good a) const {return sec-fir>a.sec-a.fir;}
}a[200005];
int n,k,i,ans=0;
int main()
{
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) scanf("%d",&a[i].fir);
	for(i=1;i<=n;i++) scanf("%d",&a[i].sec);
	sort(a+1,a+n+1);
	for(i=1;i<=k||a[i].sec-a[i].fir>0;i++) ans+=a[i].fir;
	for(;i<=n;i++) ans+=a[i].sec;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF779C)

方法：贪心。

**思路**

显然，如果有一件商品这周比上周更便宜，那一定要这周买~~不然就亏了~~否则就下周再买。但这个人~~不知道为什么~~至少要买 $k$ 件。所以可以按先买赚到的钱从大到小排序，以便减少为了满足至少买 $k$ 件的损失。

**上代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return f?x:-x;
}
struct node{
	int a,b;
}s[200005];
//这周与下周
int n,k,ans;
bool cmp(const node &x,const node &y){
	return x.a-x.b<y.a-y.b;
}
//按这周买赚的钱排序
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		s[i].a=read();
	for(int i=1;i<=n;i++)
		s[i].b=read();
	sort(s+1,s+n+1,cmp);
	int i;
	for(i=1;i<=k||s[i].a<s[i].b;i++)
		ans+=s[i].a;
	for(;i<=n;i++)
		ans+=s[i].b;
	printf("%d\n",ans);
	return 0;
}
```

完结撒花✿✿ヽ(°▽°)ノ✿。

---

## 作者：JustinXiaoJunyang (赞：0)

前排芝士：

Q ：如何在结构体内自定义排序方式？

A ：代码如下，如果是要单独一个 `cmp` 函数的，代码如下：

```cpp
bool cmp(/*结构体名*/ a, /结构体名*/ b)
{
	return /*一个 bool 值*/;
}
```

想简化在这题代码这么写:

```cpp
bool operator < (good x) const{return two - one > x.two - x.one;}
```
下面的代码很实用。

思路分析：

把问题特殊化：

先都买第一周的，然后 $n-k$ 个物品买成第二周。

把差值排序，选 $k$ 个最小的即可！

参考代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct good
{
	int one,two;
	bool operator < (good x) const{return two - one > x.two - x.one;}
}a[200005];

int main()
{
    int n, k;
    int sum = 0;
    cin >> n >> k;
    int i;
    for (i = 1; i <= n; i++) cin >> a[i].one;
    for (i = 1; i <= n; i++) cin >> a[i].two;
    sort(a + 1, a + n + 1);
    for (i = 1; i <= k || a[i].two - a[i].one > 0; i++) sum += a[i].one;
    for (; i <= n; i++) sum += a[i].two;
    cout << sum << endl;
    return 0;
}
```

---

## 作者：ytcccf (赞：0)

### 题意简述

共有 $n$ 个商品，给出第一周和第二周的价格，在第一周至少要买 $k$ 个商品，求购买所有商品的最小花费。

### 题目分析

题目难度：普及-

$AC code$ 时间复杂度：$\Theta(nlogn)$

### 解题思路 

想要花费少，那么就尽可能在价格低的时候那一周购买，但是，第一周至少要购买 $k$ 个物品，所以，第一周要尽可能地购买那些在第二周涨价的物品，其次去选择那些降价比较少的物品。因此，我们也可以轻易地得出结论：只有第二周降价了的物品才会选择在第二周买。

根据我们前面的分析，很显然，这是一道标准的贪心题目。

- 首先，在输入两周商品的价格时，同时求出两周价格的变化量。
- 然后，因为使用贪心的方法，所以我们按照价格差排一下序。
- 最后，在排完序之后，选择前 $k$ 个以及其他第二周涨价的商品第一周购买，其余第二周进行购买。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int a,b,d; //分别代表第一周、第二周以及价格差 
}x[200010];
bool cmp(node x,node y) //懒得重载运算符 
{
	return x.d<y.d;
}
int main()
{
	ios::sync_with_stdio(false); //cin、cout优化 
	int n,k,ans=0,i,j;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>x[i].a;
	}
	for(i=1;i<=n;i++)
	{
		cin>>x[i].b;
		x[i].d=x[i].a-x[i].b; //求出价格差 
	}
	sort(x+1,x+n+1,cmp);
	for(i=1;i<=k||x[i].d<0;i++) //选择前k个以及其他第二周涨价的商品第一周购买 
	{
		ans+=x[i].a;
	}
	for(j=i;j<=n;j++) //其余第二周进行购买
	{
		ans+=x[j].b;
	}
	cout<<ans<<endl; //输出答案 
	return 0; //完结撒花！ 
}
```

---

## 作者：Ag2WO4 (赞：0)

**这是一篇 Python 题解！**
## 思路
由于本题是求第一周至少买 $k$ 件商品，所以我们假设最开始全在第二周买，然后找第二周价格减第一周价格的最小值（相当于涨价最少）。如果买完 $k$ 件涨价已经到正值了就见好就收，如果没到就继续买第一周的商品，直到开始涨价为止。

由于挨个判定肯定麻烦，我们可以转化一下以上方法：将涨价量排序，如果跌价商品数比 $k$ 多就把所有跌价的商品全买下来，反之就只买到第 $k$ 件。这相当于，对于排序过的差价的列表，如果负数项比 $k$ 多就求负数项之和，反之取列表前 $k$ 项和，最后加上第二周商品总价即可。
## AC代码
```python
a,b=list(map(int,input().split()));a,c,d=list(map(int,input().split())),list(map(int,input().split())),[]
for i in range(len(a)):
    a[i]-=c[i]
for i in range(len(a)-1,-1,-1):
    if a[i]<0:
        d.append(a[i])
if len(d)<b:
    print(sum(c)+sum(sorted(a)[:b]))
else:
    print(sum(c+d))
```

---

## 作者：StarryWander (赞：0)

# 本题采用贪心

## 题目大意：
给出 $n$ 个物品和物品第一周和第二周的价格，**全部需要购买**，第一周**至少**购买 $k$ 个物品，第二周购买剩下的 $n-k$ 个物品，问最小的花费是多少。

## 想法:
想要花费尽可能少，那么就需要在尽可能价格低的那一周购买，但是，题目限定：**第一周至少购买 $k$ 个物品**，这时，我们就需要在**第一周尽可能购买那些在第二周涨价的物品**。如果没有涨价的物品怎么办？**此时就需要选择降价少的物品了**。

所以，我们可以得出结论：**只有第二周降价了的物品才会选择在第二周买**。

## 解题步骤：

1.根据价格的涨幅，很容易想到，先计算两周的**价格差**（第二周减第一周），也就是 涨价/降价 了多少。

2.从选择物品的角度，我们会想到：可以用价格差来做一次排序（**将价格差从小到大排序**。

3.在排完序的前 $n-k$ 个物品中（因为**第一周至少选 $k$个物品** ）选择第二周降价的物品。

建议：可以在**输入的时候直接累加第一周所有物品的价格**，到了第二周，若要选择，再加上它相应的差价即可。

## code：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pf(x) cout<<x<<endl;
using namespace std;
inline int read(){//快读。
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
struct node{
	int s,e,d; 
};
node v[200005];
bool cmp(node a,node b){//差价从小到大排序
	return a.d<b.d;
}
int main(){
	int n=read(),k=read(),sum=0;
	for(int i=1;i<=n;i++){
		v[i].s=read();
		sum+=v[i].s;
	}
	for(int i=1;i<=n;i++){
		v[i].e=read();
		v[i].d=v[i].e-v[i].s;//计算相应差价
	}
	sort(v+1,v+n+1,cmp);//排序
	for(int i=1;i<=n-k;i++){//最多选n-k个降价的物品。
		if(v[i].d<=0) sum+=v[i].d;//挑选第二周降价的物品。
	}
	printf("%d",sum);
	return 0;
}

```


---

## 作者：royal_111 (赞：0)

# 就是一个贪心+排序题
 
 _直接进入正题_ 
 
 1.首先排序对数据排序：
 
 如果物品涨价 差值大的排前面， 相反降价 差值小排前面，因为我们会先买涨价多的，其实买降价低的（如果满足k以内的话），下面就是cmp的写法。
 
 ```cpp
bool cmp(txt x, txt y)
{
    if(x.a <= x.b && y.a <= y.b) return x.b - x.a > y.b - y.a;
    if(x.a >= x.b && y.a >= y.b) return x.a - x.b < y.a - y.b;
    return x.a <= x.b && y.a >= y.b;
}
```


2.直接按好的顺序依次选择， 必须满足改价格前至少先买k个（至少），如果涨价的物品多于k个，就把涨价前的物品都按原价格买了；
如果涨价的物品没有k （低于k个）个，但是我们至少要在变价前买k个，剩下的就依次选紧接着的物品直到k个（都是变价前买），然后剩下的物品都是变价后买即可。（排序原理不再解释qWq）。

```cpp
ll ans = 0;
for(int i = 0; i < n; i ++ )
{
   if(k > 0) ans += g[i].a, k -- ;//直接取k个
   else 
   {
        if(g[i].a < g[i].b) ans += g[i].a;//法线海油涨价的直接取涨价前的价格
        else ans += g[i].b;
    }
}
```


------------
**接下来就是紧张刺激的代码时刻**


------------
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, k;

struct txt
{
    int a, b;
}g[N];

bool cmp(txt x, txt y)
{
    if(x.a <= x.b && y.a <= y.b) return x.b - x.a > y.b - y.a;
    if(x.a >= x.b && y.a >= y.b) return x.a - x.b < y.a - y.b;
    return x.a <= x.b && y.a >= y.b;
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i < n; i ++ ) cin >> g[i].a;
    for(int i = 0; i < n; i ++ ) cin >> g[i].b;
    sort(g, g + n, cmp);
    
    //for(int i = 0; i < n; i ++ ) cout << g[i].a << " " << g[i].b << endl;
    ll ans = 0;
    for(int i = 0; i < n; i ++ )
    {
        if(k > 0) ans += g[i].a, k -- ;
        else 
        {
            if(g[i].a < g[i].b) ans += g[i].a;
            else ans += g[i].b;
        }
    }
    printf("%lld", ans);//用不到 long long
    return 0;
}

```
# 完美结束！

---

## 作者：tryrtj (赞：0)

再次重复我的镇楼语

我tryrt就是死，手写cmp，o(n^2)冒泡排序，也不会用一个结构体，于是呢，TLE了

```
#include<iostream>
#include<algorithm>
using namespace std;
int a[200005],b[200005],c[200005];
int n,k;
void asd(){
    bool g=false;
    for(int i=0;i<n-1;i++){
        if(c[i]>c[i+1]){
            int t=c[i];
            c[i]=c[i+1];
            c[i+1]=t;
            t=a[i];
            a[i]=a[i+1];
            a[i+1]=t;
            t=b[i];
            b[i]=b[i+1];
            b[i+1]=t;
            g=true;
        }
    }
    if(g==true)asd();
    return;
}
int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
        c[i]=a[i]-b[i];
    }
    asd();
    int zong=0;
    for(int i=0;i<n;i++){
        if(c[i]<0)zong++;
    }
    int zong1=0;
    if(zong>=k){
        for(int i=0;i<zong;i++){
            zong1+=a[i];
        }
        for(int i=zong;i<n;i++){
            zong1+=b[i];
        }
    }
    if(zong<k){
        for(int i=0;i<k;i++){
            zong1+=a[i];
        }
        for(int i=k;i<n;i++){
            zong1+=b[i];
        }
    }
    cout<<zong1<<endl;
    return 0;
}
```

再一看数据范围200000，心想冒泡要凉，我立的不用结构体的flag怎么能倒？于是突然想到，既然总是现在要买大于等于k个物品，那为何不全部初始为现在买？

定义c数组存储现在与一星期后的差

然后呢，就是一个while循环，只要保证剩余的大于等于k并且加上可以省钱，就能求出最小值

完整代码，附注释

```
#include<iostream>
#include<algorithm>//sort所用
using namespace std;
int a[200005],b[200005],c[200005];
int n,k;
int main(){
	cin>>n>>k;
	long long zong1=0;
	for(int i=0;i<n;i++){
		cin>>a[i];
		zong1+=a[i];//初始化全部现在买
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
		c[i]=b[i]-a[i];//求差值
	}
	sort(c,c+n);//排序求最优
	int j=0;
	while(j<n-k&&c[j]<0){//必须为现在买的留够k个且省钱
		zong1+=c[j];//变为买一星期以后，节省钱
		j++;//继续判断下一个
	}
	cout<<zong1;//输出结果
	return 0;
}
```

---

