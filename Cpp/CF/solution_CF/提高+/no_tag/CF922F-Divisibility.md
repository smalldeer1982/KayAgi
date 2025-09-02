# Divisibility

## 题目描述

Imp is really pleased that you helped him. But it you solve the last problem, his gladness would raise even more.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/80a786f701ecc7d26672fb3b926d9dbbafc0495c.png) Let's define ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/473e0c7367d2c6c65b609424fc67aa6d9df96dba.png) for some set of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png) as the number of pairs $ a $ , $ b $ in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png), such that:- $ a $ is strictly less than $ b $ ;
- $ a $ divides $ b $ without a remainder.

You are to find such a set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png), which is a subset of $ {1,2,...,n} $ (the set that contains all positive integers not greater than $ n $ ), that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/8b010c35295a2181d8d3d9dae7832a9cb8742631.png).

## 说明/提示

In the second sample, the valid pairs in the output set are $ (1,2) $ , $ (1,4) $ , $ (1,5) $ , $ (1,6) $ , $ (2,4) $ , $ (2,6) $ . Thus, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/4055df47b045359cddfa03da919a728d3502ec96.png).

In the third example, the valid pairs in the output set are $ (2,4) $ , $ (4,8) $ , $ (2,8) $ . Thus, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/8e639a6dd37ec9bd64a5d37b32a72070668e9569.png).

## 样例 #1

### 输入

```
3 3
```

### 输出

```
No
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
Yes
5
1 2 4 5 6 ```

## 样例 #3

### 输入

```
8 3
```

### 输出

```
Yes
4
2 4 5 8
```

# 题解

## 作者：fade_away (赞：2)

## Solution
我们令$e(x)$表示$x$的真约数个数。

令$m$表示让$S=\sum_{i=1}^me(x)\geq k$最小的$m$。

现在我们考虑用$1..m$其中删掉若干个数构造答案。

我们发现如果删掉$1..\lfloor \frac{m}{2} \rfloor$的数，会对后面数的贡献产生影响，但是如果删掉$\lfloor \frac{m}{2} \rfloor+1..m$的数$x$，则只会让答案减少$e(x)$，因此我们只删除后面的数。

现在问题变成，你可以减去若干个$e(x)$，使得$S-\sum e(x)=k$。这个我们直接贪心从大到小能减则减即可。

Then，考虑它为什么正确，显然有性质：$S-k\leq e(m)$，且$e(m)$的阶为$O(m^{\frac{1.066}{\ln\ln m}})$~~（为什么？我咋知道）~~，而$\lfloor \frac{m}{2} \rfloor..m$的质数约为$O(\frac{m}{2\ln m})$，因此在$m$大于$150$的时候必然有解（因为只用质数就能满足条件，不知道为啥官题是120，我打表打出的是150)

再之，$e(x)=3$的个数有$O(\frac{m}{\ln m}*\frac{m}{\ln m})$个，而$m\leq 150$时，$e(m)$最多为$15$，大致估算一下或者打表就可以知道，$2\leq m\leq 150$时有解。

因此只要能够找到一个$m$满足$S\geq k$，必有方案。

时间复杂度$O(n\lg n )$

## Code
```cpp
signed main()
{
	int n=read(),k=read(),sum=0,id=0,num=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j*j<=i;j++) a[i].fi+=(i%j==0)*(1+(j*j!=i));
	for (int i=1;i<=n;i++) 
	{
		a[i].fi--,a[i].se=i,sum+=a[i].fi;
		if (sum>=k) { id=num=i; break; }
	}
	sort(a+id/2+1,a+id+1);
	for (int i=id;i>=id/2+1;i--)
		if (sum-a[i].fi>=k) sum-=a[i].fi,flag[a[i].se]=1,num--;
	if (sum^k) { puts("No"); return 0; }
	puts("Yes");
	printf("%d\n",num);
	for (int i=1;i<=id;i++)
		if (!flag[i]) printf("%d ",i);
	return 0;
}

```


---

## 作者：Mirasycle (赞：1)

直观感受这题不太好做，因为每个数都有双重影响，一个是作为约数，一个是作为倍数。遇到这种很难下手的问题，我们尝试对于难处理部分进行猜测，减小问题规模和复杂度。

设 $d_i$ 表示 $i$ 的约数个数（不包含本身）。

显然如果 $\sum\limits_{i=1}^nd_i<k$，那么就无解。否则找到最小的 $q$ 满足 $\sum\limits_{i=1}^qd_i\ge k$。

> 猜测一：最后的答案可以由 $[1,q]$ 之间的数字组成。

我们算出贡献差，也就是 $\Delta=\sum\limits_{i=1}^q d_i-k$。于是我们只需要先选上 $1-q$，再删除若干个数使得删除的代价为 $\Delta$。下面要解决的问题是双重身份带来的贡献难统计。

> 猜测二：被删除的数字范围是在 $[\lfloor\dfrac{q}{2}\rfloor+1,q]$。这样子可以使得数字的身份唯一，即只作为倍数，而不作为约数。

于是我们只需要减去若干个 $d_i$ 凑出 $\Delta$ 即可。

由于约数个数 $d$ 的范围很小，打表一下也可以发现小约数个数的数很多，所以一些很小的差距也容易凑出。

> 猜测三：我们将上述可删范围内的约数个数按照从大到小排序之后，扫描，能减就尽可能减去，最后如果凑不出就是无解，如果可以凑出就是有解。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=3e5+10;
void chkmax(int &x,int y){ x=x>y?x:y; }
void chkmin(int &x,int y){ x=x<y?x:y; }
int n,k,d[maxn]; ll sum[maxn];
pair<int,int> a[maxn]; vector<int> vec;
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=i*2;j<=n;j+=i) d[j]++;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+d[i];
	if(k>sum[n]){ cout<<"No"; return 0; } int q=0,tot=0;
	for(int i=1;i<=n;i++)
		if(sum[i]>=k){ q=i; break; }
	int rest=sum[q]-k;
	for(int i=1;i<(q+2)/2;i++) vec.pb(i);
	for(int i=(q+2)/2;i<=q;i++) a[++tot]=mp(d[i],i);
	sort(a+1,a+1+tot); reverse(a+1,a+1+tot);
	for(int i=1;i<=tot;i++){
		if(a[i].fi<=rest) rest-=a[i].fi;
		else vec.pb(a[i].se);
	}
	if(rest>0){ cout<<"No"; return 0; }
	cout<<"Yes"<<endl; sort(vec.begin(),vec.end());
	cout<<vec.size()<<endl;
	for(auto v:vec) cout<<v<<" "; 
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：1)

### 思路：

如果所有数都被选了的话那么，每个数的贡献就是它的约数个数。所以，对于约数个数可以求一个前缀和找到第一个 $\ge K$ 的位置就停下。

那么，现在相当于只要用这些数就可以组成 $K$ 组了。

（默认从这个位置是 $n$ 了）现在考虑怎么组合如果删掉一个数就要考虑他的倍数和约数的贡献的影响。

这样做会很麻烦，那么我们可以不可以抛开其中一个？

当然可以，约数是一定存在的，但是倍数不一定，所以考虑一下没有倍数的数
那就是 $n/2$ 到 $n$。

把这些数拿出来，按照约数个数排序。如果这个数被删掉，就一定会减少他约数个数的贡献。那么，从大到小排序之后，能删就删掉，这样就构造出了一组解。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define RG register
#define MAX 300003
int n,K;
ll d[MAX];
pair<int,int> c[MAX];
int tot;
bool vis[MAX];
int main()
{
	cin>>n>>K;
	for(int i=1;i<=n;++i)
		for(int j=i<<1;j<=n;j+=i)++d[j];
	for(int i=1;i<=n;++i)d[i]+=d[i-1];
	if(K>d[n]){puts("No");return 0;}
	for(int i=1;i<=n;++i)
		if(d[i]>K){n=i;break;}
	for(int i=n;i*2>n;--i)c[++tot]=make_pair(d[i]-d[i-1],i);
	sort(&c[1],&c[tot+1]);
	int ss=d[n]-K;
	for(int i=tot;i;--i)if(ss>=c[i].first)ss-=c[i].first,vis[c[i].second]=true;
	tot=0;
	for(int i=1;i<=n;++i)if(!vis[i])++tot;
	puts("Yes");
	printf("%d\n",tot);
	for(int i=1;i<=n;++i)
		if(!vis[i])printf("%d ",i);puts("");
	return 0;
}


```



---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

首先考虑一种最基本的无解情况，由于加上任意的一个数之后结果不减，如果将全部的 $n$ 加上，得到的结果任然比需要的少，则一定无解。

分析取满的情况，发现对于一个数，其能够产生的贡献为这个数的真约数个数 $f(i)$，由于每一个数的贡献都不是很大，直觉上感觉对于任意的 $k\le \sum f(i)$ 都是有解的。

很容易发现对于上述的猜想有推论：将 $n$ 直接缩小到满足 $k\le \sum f(i)$ 的最小 $n'$ 仍然是有解的。

---

然后就发现这个问题在 $n$ 较大的时候会非常容易有解，将可供删除的位置变成原来的一半，使得删除的数之间相互不影响，也就是考虑 $(\lfloor\dfrac{n}{2}\rfloor+1,n]$ 范围内的质数的个数和 $f(n)$ 的大小，前者根据素数定理大致为 $\dfrac{n}{2\ln n}$，而后者明显很小，渐进为 [$O(n^{\frac{1.066}{\ln\ln n}})$](https://blog.csdn.net/VFleaKing/article/details/88809335)。在这种情况下，由于质数的贡献全都为 $1$ 一定是有解的。

而对于较小的情况，由于 $f(n)$ 本身也不是很大，所以其实也很容易得到一组可行的结果。

如果实在不放心，可以直接打个表做一下，一种可行的打表思路是取出 $f(i)$ 不太大的 $i$ 直接计算是否可能覆盖全部 $f(n)$ 的变动情况。


---

