# [USACO12FEB] Cow IDs S

## 题目描述

Being a secret computer geek, Farmer John labels all of his cows with binary numbers. However, he is a bit superstitious, and only labels cows with binary numbers that have exactly K "1" bits $(1 \le K \le 10)$. The leading bit of each label is always a "1" bit, of course. FJ assigns labels in increasing numeric order, starting from the smallest possible valid label -- a K-bit number consisting of all "1" bits. Unfortunately, he loses track of his labeling and needs your help: please determine the Nth label he should assign $(1 \le N \le 10^7)$.

FJ 给他的奶牛用二进制进行编号，每个编号恰好包含 $K$ 个 $1$（$1 \le K \le 10$），且必须是 $1$ 开头。FJ 按升序编号，第一个编号是由 $K$ 个 $1$ 组成。

请问第 $N$（$1 \le N \le 10^7$）个编号是什么。

## 样例 #1

### 输入

```
7 3 
```

### 输出

```
10110 
```

# 题解

## 作者：楚泫 (赞：36)

## 写了个暴力然后绿了！！！QAQ

~~暴风哭泣呜呜呜~~

---
首先，

每次找下一个更大的序列，找到第一个前面是0的1，（最高位1的前面也是0）

然后把这个0与1的位置互换，再让这个零后面的1全部在最后。

(这样说可能有点抽象，，我们来看下样例！！

111

1011

1101

1110

10011

10101

10110

应该很好懂叭！比如1110到10011的时候，就是把最高位一和前面的0互换位置，再将后面最后几位全部改为0。

直接记录二进制每位并不方便，但可以考虑来记录每个1的所在位置。

如果当前1的位置+1不等于下一位1的位置，就说明前面是空的。那么我们互换这两个。

至于如何把前面的1弄到最前面，我们只需要在遍历的时候在前面让1的位置等于数组下标即可。如果找到了可互换的就break掉。

最高复杂度O(n*k)，

---
## 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,rec[15];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++) rec[i]=i;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(rec[j]+1!=rec[j+1]) {++rec[j];break;}
			else rec[j]=j;
		}
	}
	for(int i=rec[k];i;i--)
	{
		if(rec[k]==i) { cout<<"1";--k; }
		else cout<<"0";
	}
}
```

---

## 作者：Ofnoname (赞：11)

#### 本来是为了练习位运算才找到此题的，但我发现这跟位运算关系并不大，不过练一练组合数学也并非不好。

这样一道题，一看就知道要找规律，容易发现本题向后递推的第一个规律，就是`0的个数是按顺序排列的`，比如说3个0的所有情况遍历完后，才会找4个0的情况。

答案是10110，所以需要直接去掉没有0和一个0的情况，然后从两个0的情况开始递推，那么如何使用组合数呢？这里用样例“7 3”来分析。我们把每个1后面的0的个数看做这个1”盘子“的苹果数。（因为1的个数是固定的）

1. `K=3, cnt=0`代表0个相同苹果放入3个不同盘子中，有1种方案。我们把`N-=1`，把`cnt++`;

2. `K=3, cnt=1`代表1个相同苹果放入3个不同盘子中，有3种方案。我们把`N-=3`，把`cnt++`;

3.  `K=3， cnt=2`代表2个相同苹果放入3个不同盘子中，有6种方案。但是`N=6`，已经不够减了，退出。

   如何计算方案综述，我在~~忘了哪一节~~课上，找到规律`f(K,cnt)=C(K+cnt-1,cnt-1)`，我也不知道这叫什么数，有兴趣的同学可以自行推导。

此时`K=3,N=3,cnt=2`代表我们需要把2个相同苹果放入3个不同盘子中，降序排列的第3种方案。

我们枚举排列：(这里的降序只从前往后比较)

```
2 0 0
1 1 0
1 0 1
0 2 0
0 1 1
0 0 2
```

第三个是`1 0 1`，代表第1个1和第3个1后面各有一个0，输出10110，`return 0;`

那么如何枚举排列呢？经过一节化学课的摸索，我找到规律：

**1.若最后一位(第K位)不为0，则把最靠后的一个数-1，它的下一个数变为1，如"4 2 2 0 0"→"4 2 1 1 0"**

**2.否则进行如下变换(太难说了，参见样例和代码)，如"2 0 1"→"1 2 0"，"4 2 2 0 3"→"4 2 1 4 0"**

我们可以使用`cnt`记录当前最后非0位的位置，节省时间空间。

至此，本题已经完美解决，代码如下：

```cpp
//时间比较紧，常数较大，代码不美观见谅。
#include <bits/stdc++.h>
using namespace std;

int N,K,cnt,ans[11],acnt;

int C(int n,int m)
//组合数计算
{
    int ans=1,div=2;
    for (register int i=n-m+1; i<=n; i++)
    {
        ans*=i;
        if (!(ans%div)&&div<=m) {ans/=div;div++;}
    }
    return ans;
}

int main()
{
    scanf("%d%d",&N,&K);
    while (N>C(K+cnt-1,K-1))
        N-=C(K+cnt-1,K-1),cnt++;
    //执行第一步操作
    ans[1]=cnt; cnt=1;
    while (--N)
    {
        if (cnt>=K)
        {
            for (int i=K-1;i>=1; i--)
                if (ans[i]>0)
                {
                    cnt=i+1;
                    ans[i]--;
                    ans[i+1]=1+ans[K];
                    if (i!=K-1) ans[K]=0;
                    //递推情况1
                    break;
                }
        }
        else ans[cnt]--, ans[++cnt]++;
        //递推情况2
    }
    for (int i=1; i<=K; i++)
    {//玄学输出
        putchar('1');
        while (ans[i]--) putchar('0');
    }
    return 0;
}
```





---

## 作者：The_KOG (赞：9)

[更好阅读体验戳这里](https://www.cnblogs.com/nlKOG/p/11104817.html)

[[USACO12FEB]牛的IDCow IDs](<https://www.luogu.org/problemnew/show/P3048>)

## Description

作为一个神秘的电脑高手，Farmer John 用二进制数字标识他的奶牛。然而，他有点迷信，标识奶牛用的二进制数
字，必须只含有K位"1"(1 <= K <= 10)。 当然，每个标识数字的首位必须为"1"。FJ按递增的顺序，安排标识数字
，开始是最小可行的标识数字（由"1"组成的一个K位数）。不幸的是，他没有记录下标识数字。请帮他计算，第N
个标识数字(1 <= N <= 10^7)。

## Input

第1行：空格隔开的两个整数，N和K。 

## Output

如题，第N个标识数字

## Sample Input

```
7 3	
```

## Sample Output

```
10110
```

## Solution

在len长区间中取k个数为1,第一位为1,方案数为C(len-1,k-1)

设$f(i,j)=\sum\limits_{x=1}^{i}C(x,j)$

对于题目中的n和k,求出i,使得$f(i,k-1)\le n<f(i+1,k-1) $

则有字符串的长度len=i+1

这样我们就得到了第一个'1'的位置了

此时令:$n=n-f(i,k-1)\ ,\ k=k-1$

接着以相同方式求出剩下的'1'的位置

## Code

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int f=1,re=0;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())re=re*10+ch-'0';
	return f*re;
}
int C(int n,int m){
	if(!m)return 1;
	int re=1;
	for(int i=n;i>=n-m+1;i--)re*=i;
	for(int i=1;i<=m;i++)re/=i;
	return re;
}
int n,k;
signed main(){
//	freopen("cowids.in","r",stdin);
//	freopen("cowids.out","w",stdout);
	n=read(),k=read();
	int len,tot,lst,tmp;
	len=k-1,tot=0,tmp=C(len,k-1);
	while(tot+tmp<n){
		tot+=tmp;
		tmp=C(++len,k-1);
	}
	lst=len,n-=tot;
	putchar('1');
	for(k--;k;k--){
		len=k-1,tot=0,tmp=C(len,k-1);
		while(tot+tmp<n){
			tot+=tmp;
			tmp=C(++len,k-1);
		}
		for(int i=1;i<=lst-len-1;i++)putchar('0');
		lst=len,n-=tot;
		putchar('1');
	}
	for(int i=1;i<=len;i++)putchar('0');
	return 0;
}
/*
7 3

*/
~~~

---

## 作者：a1399433645 (赞：9)

一个只有0和1的数字串，只有1对数字串大小有影响，0没有影响，大小取决于1的位置和数量。

因为题目中要求出第n个编号是什么，并且这道题有一个限制：第一位必须是0，那么我们先将这个串用足够大小保存，足够大的话我们可以添加前导0，到最后从第一个非0位输出即可，也就是说我们要找到一个m,使得C(m,k) >= n，可以二分求m。

当k=1直接特判掉。

从大到小确定每一位。

如果做到第i位，之前已经填了j个1，那么这一位填0的方案数就是C(i-1,k-j)，即还剩i-1位可以填k-j个1的方案数。

如果这个数小于n，那么这一位填1，并且n要减去这个数，否则这一位填0。

不过这个组合数会非常大，还会爆long long,需要分类讨论进行二分求m.一定要注意这点，第一次提交就在这里wa的QwQ

时间复杂度O(sqrt(n)k)

代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn = 10000010;
long long n , k , m;
long long num[maxn] , cnt;
long long mid , l , r;
long long zuhe(int x , int y)
{
    long long k = 1;
    for(int i = x;i > x - y;i --)
    {
        k *= i;
    }
    for(int i = y;i > 1;i --)
    {
        k /= i;
    }
    return k;
}
int main(){
    scanf("%lld%lld" , &n , &k);
    if(k == 1)
    {
        for(int i = n;i > 0;i --)
        {
            if(i == n)
            {
                printf("1");
            }
            else printf("0");
        }
        return 0; 
    }
    else {
//分类讨论二分求m
        if(k == 10)
        {
            l = 1;
            r = 600;
            while(l <= r)
            {
                mid = (l + r) / 2;
                if(zuhe(mid , k) >= n)
                {
                    m = mid;
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
        }
        else {
            if(k >= 7)
            {
                l = 1;
                r = 1000;
                while(l <= r)
                {
                    mid = (l + r) / 2;
                    if(zuhe(mid , k) >= n)
                    {
                        m = mid;
                        r = mid - 1;
                    }
                    else {
                        l = mid + 1;
                    }
                }
            }
            else {
                l = 1;
                r = 7000;
                while(l <= r)
                {
                    mid = (l + r) / 2;
                    if(zuhe(mid , k) >= n)
                    {
                        m = mid;
                        r = mid - 1;
                    }
                    else {
                        l = mid + 1;
                    }
                }
            }
        }
        for(int i = m;i > 0;i --)
        {
            long long t = zuhe(i - 1 , k);
            if(t < n)
            {
                num[i] = 1;
                n -= t;
                k --;
                if(!cnt)
                {
                    cnt = i;
                }
            }
            if(!k || !n)
            {
                break;
            }
        }
        for(long long i = cnt;i > 0;i --)
        {
            printf("%d" , num[i]);
        }
    }
    return 0;
}

```

---

## 作者：巨型方块 (赞：5)

太菜了没有想到组合数

我们也医用数位dp去做；

f[i][j] 表示在前i位我们放j个1的情况有几种

f[i][j]=f[i-1][j]+f[i-1][j];

然后我们直接大力的从字符串的高位开始枚举

如果这个位子不放我们后来所有的方法都不够了那就放

细节的话看代码把；

然后一个很主要的东西

假如输入

10000000 1

我们需要开1e7的数组不可能

假如
10000000 2

我们要开的数组1e5都不到

所以特判1

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=12,M=1e5+5;
Ll a[M],f[M][N];
Ll n,m,ok,v;
int main()
{
    scanf("%lld%lld",&m,&n);
    if(n==1){
        cout<<1;
        for(int i=1;i<m;i++)printf("0");
        return 0;
    }
    for(Ll i=0;i<=1e5;i++)f[i][0]=1;
    for(Ll i=1;i<=1e5;i++)if(!v)
        for(Ll j=1;j<=n;j++){
            f[i][j]=f[i-1][j]+f[i-1][j-1];
            if(j==n&&f[i][j]>=m){v=i;break;}
        }
    for(Ll i=v;i;i--){
        if(f[i-1][n]<m)
            a[i]=1,m-=f[i-1][n],n--;
        if(a[i])ok=1;
        if(ok)cout<<a[i];
    }
}
```

---

## 作者：Doraven (赞：0)

对于这种题目，个人比较喜欢用递归解决。

首先，先求出m位符合要求的数有几个，显然就是C(m,k)个。可以直接用组合数递推把表打出来，代码如下，复杂度$O(k\sqrt{n})$
```
for(int i=0;i<=4995;i++) cnm[i][0]=1;
for(int i=1;i<=10;i++)
	    for(int j=i;j<=4995;j++)
		{
		    cnm[j][i]=cnm[j-1][i-1]+cnm[j-1][i];
		    if(cnm[j][i]>=n) {key[i]=j;break;}
		}
```
将原问题记为$(k,n)$,
接下来考虑如何缩小子问题。对于一组$(know,nnow)$,
想办法将其降为$(know-1,x)$的形式，即放下一个1在$m$位.对于一个$m$位数,有$cnm[m][know]$种放数方法。即对这个$m$，要求$cnm[m-1][know]<nnow<=cnm[m][know]$
自然二分，然后记$ans[m]=1$即可（注意考虑$nnow==cnm[m][know]$的请况）。
递归过程：
```
void dfs(int know,int nnow)
{
	if(know==1) {ans[nnow]=1;return;}
	int l=1,r=key[know];
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(cnm[mid][know]<=nnow) l=mid;else r=mid-1;
	}
	if(cnm[l][know]==nnow)
	{
		for(int i=l;i>=l-know+1;i--) ans[i]=1;
		return;
	}
	else
	{
	    ans[l+1]=1;
	    dfs(know-1,nnow-cnm[l][know]);
	    return;
	}
}
```

最后，逆序输出$ans[i]$即可，注意前导0.
完整代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
bool ans[10000100];
int n,k,key[15];
int cnm[5000][15];
void dfs(int know,int nnow)
{
	if(know==1) {ans[nnow]=1;return;}
	int l=1,r=key[know];
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(cnm[mid][know]<=nnow) l=mid;else r=mid-1;
	}
	if(cnm[l][know]==nnow)
	{
		for(int i=l;i>=l-know+1;i--) ans[i]=1;
		return;
	}
	else
	{
	    ans[l+1]=1;
	    dfs(know-1,nnow-cnm[l][know]);
	    return;
	}
}
int main()
{
	cin>>n>>k;
	for(int i=0;i<=4995;i++) cnm[i][0]=1;
	for(int i=1;i<=10;i++)
	    for(int j=i;j<=4995;j++)
		{
		    cnm[j][i]=cnm[j-1][i-1]+cnm[j-1][i];
		    if(cnm[j][i]>=n) {key[i]=j;break;}
		}
	dfs(k,n);
	bool flag=0;
	for(int i=10000010;i>=1;i--)
	{
		if(flag==0&&ans[i]==1) flag=1;
		if(flag) cout<<ans[i];
	}
}
```

---

