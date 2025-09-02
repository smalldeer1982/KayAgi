# Lucky Tickets

## 题目描述

### 题目内容
在海象岛，公共交通车票的特点是两个整数：一个是线路号，另一个是票号。线路号由 $a$ 表示，票号由 $b$ 表示，然后车票编号由有序的一对数字 $(a,b)$ 表示。

海象认为，如果 $a\times b= \operatorname{rev}(a)\times\operatorname{rev}(b)$，那么一张票是幸运的。

一般地，函数 $\operatorname{rev}(x)$ 定义为将 $x$ 翻转并去掉先导 $0$。

例如：

$$\operatorname{rev}(12343)=34321$$
$$\operatorname{rev}(12000)=21$$

公共交通管理委员会希望发售 $x$ 条线路的车票，每个线路都包含 $y$ 张票，以便至少发售 $w$ 张幸运票。并且委员会会使发售的票的总数 $(x\times y)$ 最少。而且，公共交通管理委员会一次只能发售不超过 $x_{max}$ 条线路的车票，每条线路只能发售不超过 $y_{max}$ 张车票。

## 样例 #1

### 输入

```
2 2 1
```

### 输出

```
1 1```

## 样例 #2

### 输入

```
132 10 35
```

### 输出

```
7 5```

## 样例 #3

### 输入

```
5 18 1000
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
48 132 235
```

### 输出

```
22 111```

# 题解

## 作者：genshy (赞：3)



### 题意描述：


设 $rev(i)$ 表示把 $i$ 的每一位翻转之后所得到的数。

如果 $a\times b = rev(a) \times rev(b) $ , 则称数对 $(a,b)$ 是合法的。

$f(n,m)$ 表示：$i\leq n,j\leq m$, 且数对 $(i,j)$ 是合法的数对的个数。 

现在给你三个数 $x_{max},y_{max},w$， 让你求一组 $(x,y)$ 满足：$f(n,m)\geq w$ 且 $x\leq x_{max},y\leq y_{max}$ ，$x\times y$ 最小,无解则输出 $-1$。

数据范围： $x_{max},y_{max}\leq 10^5, w\leq 10^7$ 。

### solution：

$\ map$ + 双指针。

首先我们考虑一个问题就是怎么求出 $f(n,m)$ 。

我们把 $a\times b = rev(a)\times rev(b)$ 变形为：${a\over rev(a)} = {rev(b)\over b}$。

然后可以先开个 $map$ 存一下 $a\over rev(a)$ 出现的次数， 然后在枚举一下 $b$ ，那么 $b$ 对 $f(n,m)$ 的贡献就是 $rev(b)\over b$ 出现的次数。

在能求出来 $f(n,m)$ 之后，我们这道题就很好做了。

我们可以先扫一遍求出 $f(x_{max},y_{max})$ ,无解的情况就是 $f(x_{max},y_{max}) > w$

至于有解的情况，我们维护两个指针 $l,r$ 表示 当 $x=l$  时，符合条件的 $y$ 最小为 $r$ 。

同时维护一个 变量 $cnt$， 表示当前 $f(l,r)$ 的值。

不难发现，随着 $l$ 的递增， $r$ 一定是单调递减的。

所以我们可以拿双指针维护一下，同时再开两个 $map$ 用来统计 $a\over rev(a)$ 和 $rev(b)\over b$ 出现的次数。

当 $l,r$ 指针移动的时候, 用 $map$ 就可以直接维护出移动之后 $cnt$ 的值 (类似于莫队的指针移动)。

复杂度： $O(nlogn)$

**code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
int maxx,maxy,w,l,r,ans,ansl,ansr,cnt,sum;
map<double,int> t1,t2;
inline int read()
{
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
    return s * w;
}
int rev(int x)
{
    int res = 0;
    while(x)
    {
        res = res * 10 + x % 10;
        x /= 10;
    }
    return res;
}
int main()
{
    maxx = read(); maxy = read(); w = read(); ans = 1e10;
    for(int i = 1; i <= maxx; i++) t1[1.0*i/rev(i)]++;
    for(int i = 1; i <= maxy; i++) sum += t1[1.0*rev(i)/i];//求f(maxx,maxy)
    if(sum < w) printf("%d\n",-1);//无解的情况
    else
    {
        l = maxx, r = 0;
        while(l && r <= maxy)
        {
            while(cnt < w && r <= maxy)
            {
            	r++;
                t2[1.0*rev(r)/r]++;
                cnt += t1[1.0*rev(r)/r];//r指针对cnt的贡献
            }
            if(cnt >= w && r*l < ans)
            {
                ans = r*l;
                ansl = l; ansr = r;
            }
            cnt -= t2[1.0*l/rev(l)];//l向左移对cnt的贡献
            t1[1.0*l/rev(l)]--;
            l--;
        } 
		printf("%d %d\n",ansl,ansr);
    }
   
    return 0;
}
```





   







---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

二分位置加数据结构。

不妨先固定一个位置 $x$，可以发现如果一个位置 $y_1$ 可行，那么对于任意的 $y_2>y_1$ 也一定可行，所以可以枚举 $x$，然后二分 $y$ 的位置。

处理这个问题的关键就变成了如何快速计算出每一个 $y$ 的位置的贡献，也就是在 $[1,y]$ 上有哪一些是可以和 $[1,x]$ 上的数产生贡献。如果有一种方法能够在很短的时间内找出对于一个数 $x$ 满足 $\text{rev}(x)\text{rev}(y)=xy$ 的所有的 $y$ 的位置，就可以用树状数组或者线段树做一个单点修改，区间查询，这一步维护的复杂度 $O(\log n)$，是很优秀的。

那么就只要找到这种方法就行了，直接枚举复杂度直接爆炸，重新回到原来的式子中：$\text{rev}(x)\text{rev}(y)=xy$，变一下形，得到 $\dfrac{\text{rev}(x)}{x}=\dfrac{y}{\text{rev}(y)}$，这样每一个数字就对应了唯一一个函数值，不妨将其称为“特征值”，对于 $y$ 就直接将所有的“特征值”相同的放到一起，更新 $x$ 直接取出来就行了。

相对双指针巨大慢，代码提交时是全谷最劣解。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
#include<map>
using namespace std;
#define int long long
const int MAXN=1000005;
int mx,my,w,f[MAXN],cnt,num[MAXN],l,r,ans,mid,resx,resy,res;
map <double,int> m;
vector <int> p[MAXN];
int lowbit(int x){return x&(-x);}
void add(int x){
	for(int i=x;i+lowbit(i)<=MAXN;i+=lowbit(i))
	f[i]++;
}
int query(int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))ans+=f[i];
	return ans;
}
int rev(int x){
	int cnt=0;
	while(x){
		num[++cnt]=x%10;
		x/=10;
	}
	for(int i=1;i<=cnt;i++)
	x=x*10+num[i];
	return x;
}
signed main(){
	scanf("%I64d%I64d%I64d",&mx,&my,&w);
	for(int i=1;i<=my;i++){
		int REV=rev(i);
		if(m[(double)i/REV]==0){
			m[(double)i/REV]=++cnt;
			p[cnt].push_back(i);
		}
		else{
			p[m[(double)i/REV]].push_back(i);
		}
	}
	res=9223372036854775807;
	for(int i=1;i<=mx;i++){
		int REV=rev(i);
		double u=(double)REV/i;
		if(m[u]==0)continue;
		int now=m[u];
		for(int j=0;j<p[now].size();j++)
		add(p[now][j]);
		l=1;r=my;ans=-1;
		while(l<=r){
			mid=l+r>>1;
			if(query(mid)<w)l=mid+1;
			else r=mid-1,ans=mid;
		}
		if(ans==-1)continue;
		if(i*ans<res){
			res=i*ans;
			resx=i;resy=ans;
		}
	}
	if(res==9223372036854775807){
		printf("-1\n");
		return 0;
	}
	printf("%I64d %I64d\n",resx,resy);
	return 0;
}
```



---

