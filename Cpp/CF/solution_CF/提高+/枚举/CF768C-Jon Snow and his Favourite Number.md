# Jon Snow and his Favourite Number

## 题目描述

题意:

你有一串长度为n的序列a,重复k次操作,问操作后的序列的极值值.
操作:
将序列从小到大排序,从1标号,对序号为奇数的数^(xor)x.

## 说明/提示

n,k:[1,1e5]
x,a[i]:[1,1e3]

注意:

None.

感谢@尘染梦 提供的翻译

## 样例 #1

### 输入

```
5 1 2
9 7 11 15 5
```

### 输出

```
13 7```

## 样例 #2

### 输入

```
2 100000 569
605 986
```

### 输出

```
986 605```

# 题解

## 作者：迟暮天复明 (赞：2)

[题面](https://codeforces.com/contest/768/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16292669.html)

Description:

有一个长度为 $n(1\leq n\leq10^5)$ 的数组 $a(0\leq a_i\leq 1000)$，你要进行 $k(0\leq k\leq10^5)$ 次操作：

+ 将数组排序；
+ 将数组中**下标为奇数**的数字异或 $x(0\leq x\leq1000)$。

问操作完毕后数组中最大值和最小值。

-----
重在乱搞。

随便手造了几组小数据，发现都在若干步之后进入了循环。所以我们大胆猜测：对于所有数据，一定会进入循环。

~~不知道怎么证明，但是因为通过了，所以这个猜测是正确的。~~

后面就全是暴力了。暴力做每一步，做完以后哈希，每次判断是否与之前某一位的哈希值相等即可。如果相等了，说明陷入了循环。算一下循环节就知道 $k$ 对应循环中的哪一位。

似乎不用哈希也能过？但是用了的话匹配会快很多，也省空间。

注意 $k=0$ 的数据。

[代码](https://paste.ubuntu.com/p/Q5MNBc6Vsd/)

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF768C)

玩 duel 玩的这题，然后觉得很简单，于是来水一下估值。

> 所以为什么蓝题？

发现值域很小，显然是在值域上突破。

这也意味着很多个数相同，所以我们开个桶记录一下每个数出现的次数，并且相当于同时给数组排好了序，于是直接按题意对着值域模拟即可。

注意应该枚举到 $1023$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
#define ll long long
int inline read() {
	int num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n, k, x, f[1024], g[1024]; 
void solve() {
	int cnt = 0;
	for(int i = 0; i < 1024; ++i) {
		if(!f[i]) continue; 
		if(cnt & 1) g[i ^ x] += f[i] >> 1, g[i] += f[i] + 1 >> 1;
		else g[i ^ x] += f[i] + 1 >> 1, g[i] += f[i] >> 1; 
		cnt += f[i];
	}
	for(int i = 0; i < 1024; ++i) f[i] = g[i], g[i] = 0;
}
int main() {
	n = read(), k = read(), x = read();
	for(int i = 1; i <= n; ++i) ++f[read()];
	for(int i = 1; i <= k; ++i) solve();
	int R = 0, L = 1023; 
	for(int i = 0; i < 1024; ++i) {
		if(f[i]) L = min(L, i), R = max(R, i);
	}
	printf("%d %d\n", R, L);
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：0)

打个表发现有循环节，然后我就 naive 地觉得循环节大小一定是 $2$ 导致爆了 OJ。

发现循环节的长度不会超过 $200$。于是就可以暴力 $200$ 次找出循环节来然后做。这样的复杂度是 $O(200\cdot n)$ 的。

关于循环节，个人的理解仅限于 `xor` 运算有自反性，所以显然循环节应该是偶数长度的。

…不会编了。就当是一个乱搞吧= =

话说我确实没怎么写过乱搞，业务生疏.jpg

```cpp

int cnt ;
int p, q ;
int n, k, m ;
 
int rec[M][N] ;
int base[N] ;
int buc[N] ;
int cycle ;
 
bool cmp(int *a, int *b){
    for (int i = 1 ; i <= n ; ++ i)
        if (a[i] != b[i]) return 0 ;
    return 1 ;
}
int cmp_rec(int *a){
    for (int i = 0 ; i < cnt ; ++ i)
        if (cmp(rec[i], a)) return i ;
    return -1 ;
}
int main(){
    cin >> n >> k >> m ;
    for (int i = 1 ; i <= n ; ++ i)
        base[i] = qr() ; p = -1, q = P ;
    sort(base + 1, base + n + 1) ;
    memcpy(rec[0], base, sizeof(base)) ;
    if (!k){
        for (int i = 1 ; i <= n ; ++ i)
            chkmax(p, base[i]), chkmin(q, base[i]) ;
        cout << p << " " << q << '\n' ;
        return 0 ;
    }
    while (k){
        -- k ; ++ cnt ; //debug(cnt) ;
        for (int i = 1 ; i <= n ; ++ i)
            rec[cnt][i] = rec[cnt - 1][i] ^ (i & 1) * m ;
        sort(rec[cnt] + 1, rec[cnt] + n + 1) ; //debug(rec[cnt], 1, n) ;
        if ((cycle = cnt - cmp_rec(rec[cnt])) <= cnt) break ;
    }
    if (k)
        k %= cycle, cnt -= cycle - k ;
    for (int i = 1 ; i <= n ; ++ i){
        chkmax(p, rec[cnt][i]) ;
        chkmin(q, rec[cnt][i]) ;
    }
    cout << p << " " << q << '\n' ;
}
 
```

---

## 作者：Hades18 (赞：0)

首先先安利一发[翻译](https://www.luogu.org/discuss/show/33646).

本题有两种解法,先介绍第一种暴力.

-----------------------

我们观察数据范围,发现值域非常小,然后我们就可以开一个桶,暴力走k次操作,时间复杂度为O(值域*k).

由于仅为奇数号位的数要xor,所以我们要考虑一下这个桶里有多少个数被xor了,有多少个数还留在桶里.

具体见代码：
```
#include<cstdio>
inline int read(){
	int x=0,f=0;
	register char ch=getchar();
	for(;ch<48||ch>57;ch=getchar())f|=ch=='-';
	for(;ch>47&&ch<58;ch=getchar())
	x=(x<<1)+(x<<3)+(ch^48);
	return f?~x+1:x;
}
using namespace std;
int m[1024],tmp[1024];
int main()
{
	int n=read(),k=read(),x=read();
	for(int i=0;i<n;++i)++m[read()];
	for(int i=0;i<k;++i)
	{
		int now=1;//奇偶操作.
		for(int i=0;i<1024;++i)
		{
			tmp[i]+=(m[i]+(now^1))>>1;
			tmp[(i^x)]+=(m[i]+now)>>1;
			now=(now+m[i])&1;
		}
		for(int i=0;i<1024;++i)
			m[i]=tmp[i],tmp[i]=0;
	}
	for(int i=1023;;--i)
	if(m[i])
	{
		printf("%d ",i);
		break;
	}
	for(int i=0;;++i)
	if(m[i])
	{
		printf("%d\n",i);
		break;
	}
	return 0;
}
```

---------

看k这么大,想必不是暴力跑,那应该是有循环节了,所以第二种方法是求循环节.

~~(虽然我觉得这题的循环节可能会很长,然后T掉...)~~

大概在50次操作前就会出现循环节,不过要是觉得不稳,可以开vector.

上代码([搬运](https://www.cnblogs.com/barrier/p/6425870.html))：
```
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define N 100005
using namespace std;
typedef long long ll;
int inf=1000000;
int n,k,x,a[N],l[50][N];
int check(int x){
    for(int i=0;i<x;++i){
        bool f=1;
        for(int j=0;j<n;++j){
            if(l[i][j]!=l[x][j]){
                f=0;break;
            }
        }if(f)return i;
    }
    return -1;
}
int main(void){
    cin>>n>>k>>x;
    for(int i=0;i<n;++i){
        cin>>a[i];
        l[0][i]=a[i];
    }
    int pre,time=1;
    for(;time<=k;time++){
        sort(a,a+n);
        for(int j=0;j<n;++j){
            if(j%2==0)a[j]^=x;
            l[time][j]=a[j];
        }
        pre=check(time);
        if(pre!=-1)break;
    }
    if(k>time){
        int len=time-pre;
        int finally=(k-time)%len;
        time=pre+finally;
    }else time=k;
    int minn=inf,maxn=-inf;
    for(int i=0;i<n;++i){
        minn=min(minn,l[time][i]);
        maxn=max(maxn,l[time][i]);
    }
    cout<<maxn<<" "<<minn;
}
```

---

