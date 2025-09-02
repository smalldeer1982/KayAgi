# Anton and Fairy Tale

## 题目描述

Anton likes to listen to fairy tales, especially when Danik, Anton's best friend, tells them. Right now Danik tells Anton a fairy tale:

"Once upon a time, there lived an emperor. He was very rich and had much grain. One day he ordered to build a huge barn to put there all his grain. Best builders were building that barn for three days and three nights. But they overlooked and there remained a little hole in the barn, from which every day sparrows came through. Here flew a sparrow, took a grain and flew away..."

More formally, the following takes place in the fairy tale. At the beginning of the first day the barn with the capacity of $ n $ grains was full. Then, every day (starting with the first day) the following happens:

- $ m $ grains are brought to the barn. If $ m $ grains doesn't fit to the barn, the barn becomes full and the grains that doesn't fit are brought back (in this problem we can assume that the grains that doesn't fit to the barn are not taken into account).
- Sparrows come and eat grain. In the $ i $ -th day $ i $ sparrows come, that is on the first day one sparrow come, on the second day two sparrows come and so on. Every sparrow eats one grain. If the barn is empty, a sparrow eats nothing.

Anton is tired of listening how Danik describes every sparrow that eats grain from the barn. Anton doesn't know when the fairy tale ends, so he asked you to determine, by the end of which day the barn will become empty for the first time. Help Anton and write a program that will determine the number of that day!

## 说明/提示

In the first sample the capacity of the barn is five grains and two grains are brought every day. The following happens:

- At the beginning of the first day grain is brought to the barn. It's full, so nothing happens.
- At the end of the first day one sparrow comes and eats one grain, so $ 5-1=4 $ grains remain.
- At the beginning of the second day two grains are brought. The barn becomes full and one grain doesn't fit to it.
- At the end of the second day two sparrows come. $ 5-2=3 $ grains remain.
- At the beginning of the third day two grains are brought. The barn becomes full again.
- At the end of the third day three sparrows come and eat grain. $ 5-3=2 $ grains remain.
- At the beginning of the fourth day grain is brought again. $ 2+2=4 $ grains remain.
- At the end of the fourth day four sparrows come and eat grain. $ 4-4=0 $ grains remain. The barn is empty.

So the answer is $ 4 $ , because by the end of the fourth day the barn becomes empty.

## 样例 #1

### 输入

```
5 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 1
```

### 输出

```
5
```

# 题解

## 作者：npqenqpve (赞：3)

### 题意：

给定 $n$ 和 $m$，第 $i$ 天 $n \gets \max(n,n+m)-i$，求哪天起 $n \leq 0$

### 思路：

如果 $n\leq m$，那等价于 $n\gets n-i$，直到第 $n$ 天 $n-i=0$   ；

否则可以发现前 $m$ 天减去的都会被下一天补回到 $n$，那么在第 $m+1$ 天 $n$ 下一天只能被补成 $n-1$，所以第 $m+i$ 天 $n$ 减少了 $i$，第 $m$ 天往后 $i$ 天总共减少了 $\frac{(i+1)\times i}2$，因为第 $m+1$ 天开始时 $n$ 为 $n-m$，所以求解 $n-m\leq\frac{(i+1)\times i}2$ 的最小 $i$ 即可，二分或者暴力枚举都行，我写的二分。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long //No long long see your ancestor!!!
#define int unsigned long long //Have long long see your ancestor!!!
#define ld long double //No long double see your ancestor!!!
using namespace std;
signed main()
{
    int n,m;cin>>n>>m;
    int ans=m;
    if(n<=m)
    {
        cout<<n<<"\n";
    }
    else 
    {
        int l=1,r=1e10;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            // cout<<l<<" "<<r<<" "<<mid<<"\n";
            if(mid*(mid+1)>=2*(n-m))
            {
                r=mid-1;
            }
            else 
            {
                l=mid+1;
            }
        }
        cout<<ans+l<<"\n";
    }
    // system("pause");
}
```


---

## 作者：dingshengyang (赞：2)

一开始，我们在第 $i$ 天都会被吃掉 $i$ 谷粒。

然后再第 $i+1$ 天又会被补满……当然前提是 $i \le m$。

那么，第 $m$ 天被补满后，$m$ 就渐渐跟不上了，于是，$n$ 渐渐变成 $n-1$，然后是 $n-1-2$……

那么，我们用 $f(n)$ 来计算这之后需要多少天。

```cpp
int f(long long d){
	long long tot = 1;
	while(d>0){
		d -= tot++;
	}
	return --tot;
}
```

然后就输出 $m+f(n-m)$！

然后……WA 了。

原因：如果 $n < m$，那么在 $n$ 天，库存就被 $n$ 只鸟干死了，那么就等不到 $m$ 的支援！

code：
```cpp
#include <bits/stdc++.h>
#define R register
#define inl inline
#define fastios ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define Debug(file) freopen(file".in","r",stdin);freopen(file".out","w",stdout);
using namespace std;
long long n,m;
int f(long long d){
	long long tot = 1;
	while(d>0){
		d -= tot++;
	}
	return --tot;
}
int main() {
	cin >> n >> m;
	if(n >= m)cout << (m+f(n-m)) << endl;
	else cout << n << endl;
	return 0;
}
```

UPD：既然有重复解法，那么我就来个倍增吧！管理员，可以吗？

倍增思想是指，假设我要查 $563$，那么，我先查 $1$，比它大，然后就查 $2$，一直查 $2^k(2^k \le n)$，然后一直到 $1024$，过头了，回过来，$512$。

那么我们就取 $512$ 的一半，取 $512\times\dfrac{3}{2}=768$，然后是 $512\times\dfrac{5}{4}=640$,还过头了，就取 $512\times\dfrac{9}{8}=576$，只差一点了！

取 $512\times\dfrac{17}{16}=544$，小过头了。注：刚才增量为 $32$，这次我们取 $16$，$544+16=560$……

下面不一一码中文了，直接上 LaTeX。

$560-8=552,552+4=556,556-2=554,554-1=553$，答案 GET 到了。


这份代码仅限于读者学习倍增，如果当 $i\times(i+1)=d$ 没有整数解，还需要打个表。

```cpp
#include <bits/stdc++.h>
#define R register
#define inl inline
#define fastios ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define Debug(file) freopen(file".in","r",stdin);freopen(file".out","w",stdout);
using namespace std;
unsigned long long n,m;
int f(unsigned long long d){
	int tot = 0,add_sub = 1;
	while(tot*(tot+1)/2 != d){
		if(tot*(tot+1)/2 < d){
			tot += add_sub;
			add_sub <<= 1;
			continue;
		}
		if(tot*(tot+1)/2 > d){
			add_sub >>= 2;
			tot -= add_sub;
		}
	}
	return tot;
}
int main() {
	cin >> n >> m;
	if(n >= m)cout << (m+f(n-m)) << endl;
	else cout << n << endl;
	return 0;
}
```










---

## 作者：lichenfan (赞：1)

### 大模拟
这是一道比较考验思维的大模拟，我们可以分为两种情况来讨论。
第一种，如果 $n \leq m$，那么前 $n-1$ 天都是满的，到了第 $n$ 天一次性取完，所以答案就是 $n$。第二种，如果 $n>m$，那么前 $m-1$ 天也都是满的，到第 $m$ 天结束时只剩 $n-m$ 粒谷子了，然后后面每天多拿走 $1$ 粒谷子，用等差数列算一下即可了。最后记得开 longlong。 
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long       //全部开longlong，不然会炸 
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
    return x*f;
}
int n,m,ans;
signed main(){
    n=read(),m=read();
    if(n<=m){                    //第一种情况 
    	cout<<n;               
    	return 0;
	}                   
    n=(n-m)*2,ans=sqrt(n);       //第二种情况等差数列一个一个枚举 
    while(ans*(ans+1)>=n) ans--;
    cout<<ans+m+1;
}

```



---

## 作者：微分几何 (赞：0)

#  $n<=m : $

首先，如果 $n<=m$ ，答案就是 $n $。

#  $n>m : $
如果 $n>m $，我们可以发现，在第 $m $ 天结束后，谷有 $n-m $粒。

第 $m+1 $ 天比第 $m $ 天多吃 $1 $ 粒，第 $m+2 $ 天比第 $m+1 $ 天多吃 $2 $ 粒，以此类推，这不就是等差数列吗。

我们把 $n=n-m $ ，即剩下的数量，再去求一个 $x $ 使得， $(1+x)*x/2>=n $ ，枚举一下 $x $ 就可以，答案是 $m+x $ 天。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m;
	cin>>n>>m;
	if(n<=m)
	{
		cout<<n<<endl;
	}
	else
	{
		n-=m;
		n*=2;
		long long x;
		for(x=sqrt(n);;x--)
		{
			if(x*x+x<n)
			{
				break;
			}
		}
		cout<<m+x+1<<endl;
	}
    return 0;
}
```


---

