# [Violet] 蒲公英

## 题目背景

亲爱的哥哥：

你在那个城市里面过得好吗？

我在家里面最近很开心呢。昨天晚上奶奶给我讲了那个叫「绝望」的大坏蛋的故事的说！它把人们的房子和田地搞坏，还有好多小朋友也被它杀掉了。我觉得把那么可怕的怪物召唤出来的那个坏蛋也很坏呢。不过奶奶说他是很难受的时候才做出这样的事的……

最近村子里长出了一大片一大片的蒲公英。一刮风，这些蒲公英就能飘到好远的地方了呢。我觉得要是它们能飘到那个城市里面，让哥哥看看就好了呢！

哥哥你要快点回来哦！

爱你的妹妹 Violet

Azure 读完这封信之后微笑了一下。

“蒲公英吗……”


## 题目描述

在乡下的小路旁种着许多蒲公英，而我们的问题正是与这些蒲公英有关。

为了简化起见，我们把所有的蒲公英看成一个长度为 $n$ 的序列 $\{a_1,a_2..a_n\}$，其中 $a_i$ 为一个正整数，表示第 $i$ 棵蒲公英的种类编号。

而每次询问一个区间 $[l, r]$，你需要回答区间里出现次数最多的是哪种蒲公英，如果有若干种蒲公英出现次数相同，则输出种类编号最小的那个。

**注意，你的算法必须是在线的**。


## 说明/提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n,m \le 3000$。
- 对于 $100\%$ 的数据，保证 $1\le n \le 40000$，$1\le m \le 50000$，$1\le a_i \le 10^9$，$1 \leq l_0, r_0 \leq n$。


## 样例 #1

### 输入

```
6 3 
1 2 3 2 1 2 
1 5 
3 6 
1 5
```

### 输出

```
1 
2 
1
```

# 题解

## 作者：Gypsophila (赞：166)

upd 2018.09.16 发现自己的图没了，重新审核

[我的博客同题题解QAQAQQQ](https://www.cnblogs.com/acfunction/p/10051345.html)

神仙分块题。。

### Description

给出一个长度为 $n$ 序列 $a$ ，$m$ 次询问，每次询问区间 $[l,r]$ 里的众数（出现次数最多的数）。若有多个，输出最小的。

$a_i \leq 10^9, n \leq 40000, m \leq 50000$，强制在线。

### Solution 

$a_i \leq 10^9$ ，先离散化。然后

算法一：暴力 $n ^ 2$ ，预计得分 20 ； 实际得分 20 （开了 O2 直接变成 85 啥操作）

算法二：$n \leq 40000$ ， 看来需要搬出分块大法。 

预处理出两个数组：

$p[i][j]$：表示第 $i$ 个块 到第 $j$ 个块的（最小的）众数。

$s[i][j]$：类似于前缀和，在前 $i$ 个（包括 $i$ ）个块中 $j$ （离散化之后的值）出现了几次。

如何预处理 $p,s$

对于 $s$ ，直接每个块扫一遍，复杂度 $O(n \sqrt n)$

对于 $p$ ，双重循环枚举 $i,j$，开一个数组暴力统计每个数出现了多少次。复杂度 $O(\sqrt n \sqrt n \sqrt n)=O(n \sqrt n)$

预处理 $p,s$ 有啥用呢？对于一个询问 $[l,r]$ ，设 $l$ 在第 $posl$ 个块中，$r$ 在第 $posr$ 个块中。那么分两种情况：

第一种：$posr - posl <= 1$，直接暴力扫 $l,r$，复杂度 $O(\sqrt n)$

第二种：$posr - posl >= 2$，如下图：

![](https://cdn.luogu.com.cn/upload/pic/33249.png)

红线就是 $l$，蓝线就是 $r$，黑线是块与块的分割线。

答案 $\in$ $\{\text{黄线中的元素}\} \cup \{\text{绿线的众数}\}$

绿线的众数在之前已经预处理好了，对于黄线中的每一个元素在区间$[l,r]$中出现的次数就是 在黄线中出现的次数 + 在绿线中出现的次数。

对于在黄线中出现的次数，可以直接扫，复杂度 $O(\sqrt n)$

对于在绿线中出现的次数，可以根据之前处理的前缀和算出。

这样每个元素就可以在 $O(\sqrt n)$ 的时间内求出出现次数，然后就可以愉快的AC~~神仙分块黑题了~~了。 （细节很多，调了很久）


### Code 

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 40040;
const int K = 220;
int n, m, L, len, sum[K][N], vis[N];
int tmpnum[N], B[N], last, pre[N];
struct getin {
    int id, d, se;
}a[N];
struct node {
    int num, s;
}p[K][K];
inline bool cmp1(getin x, getin y) { return x.d < y.d; }
inline bool cmp2(getin x, getin y) { return x.id < y.id; }
inline int getB(int x) {
    int ret = x / L;
    if(x % L) ret++;
    return ret;
}
inline void prework() {
    for(int i = 1; i <= len; i++) {
        memset(B, 0, sizeof(B)); node tmp;
        tmp.num = tmp.s = 0;
        for(int j = i; j <= len; j++) {
            for(int k = (j - 1) * L + 1; k <= min(n, j * L); k++) {
                B[a[k].se]++;
                if(B[a[k].se] > tmp.s) {
                    tmp.num = a[k].se;
                    tmp.s = B[a[k].se];
                }
                else if(B[a[k].se] == tmp.s)
                    tmp.num = min(tmp.num, a[k].se), 
                    tmp.s = B[a[k].se];
            }
            p[i][j] = tmp;
        }
    }
    for(int i = 1; i <= len; i++) {
        for(int j = 1; j <= n; j++) sum[i][a[j].se] = sum[i - 1][a[j].se];
        for(int j = (i - 1) * L + 1; j <= min(n, i * L); j++) 
            sum[i][a[j].se]++;
    }
}
int main() {
    scanf("%d%d", &n, &m); L = sqrt(n);
    len = (n + L - 1) / L;
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i].d), a[i].id = i;
    sort(a + 1, a + n + 1, cmp1); a[0].d = -1;
    for(int i = 1; i <= n; i++) {
        a[i].se = a[i - 1].se;
        if(a[i - 1].d != a[i].d) 
            a[i].se++;
        pre[a[i].se] = a[i].d;
    }
    sort(a + 1, a + n + 1, cmp2);
    prework(); 
    for(int i = 1; i <= m; i++) {
        int l, r; scanf("%d%d", &l, &r);
        l = (l + last - 1) % n + 1;
        r = (r + last - 1) % n + 1;
        if(l > r) swap(l, r);
        int posl = getB(l), posr = getB(r);
         if(posr - posl <= 2) {
            int ans = 0;
            for(int j = l; j <= r; j++) tmpnum[a[j].se] = 0;
            for(int j = l; j <= r; j++) {
                tmpnum[a[j].se]++;
                if(tmpnum[a[j].se] > tmpnum[ans]) ans = a[j].se;
                else if(tmpnum[a[j].se] == tmpnum[ans]) ans = min(ans, a[j].se);
            }
            printf("%d\n", last = pre[ans]);
        } 
        else {
            int ans = p[posl + 1][posr - 1].num;
            tmpnum[ans] = 0, vis[ans] = 0;
            for(int j = l; j <= min(n, posl * L); j++) tmpnum[a[j].se] = 0, vis[a[j].se] = 0;
            for(int j = (posr - 1) * L + 1; j <= r; j++) tmpnum[a[j].se] = 0, vis[a[j].se] = 0;
            for(int j = l; j <= min(n, posl * L); j++) tmpnum[a[j].se]++;
            for(int j = (posr - 1) * L + 1; j <= r; j++) tmpnum[a[j].se]++;
            int MXnum, MX = 0;
            for(int j = l; j <= min(n, posl * L); j++)
                if(!vis[a[j].se]) {
                    vis[a[j].se] = 1;
                    int val = tmpnum[a[j].se] + sum[posr - 1][a[j].se] - sum[posl][a[j].se];
                    if(MX < val)
                        MX = val, 
                        MXnum = a[j].se;
                    else if(MX == val) MXnum = min(MXnum, a[j].se);
                }
            for(int j = (posr - 1) * L + 1; j <= r; j++)
                if(!vis[a[j].se]) {
                    vis[a[j].se] = 1;
                    int val = tmpnum[a[j].se] + sum[posr - 1][a[j].se] - sum[posl][a[j].se];
                    if(MX < val)
                        MX = val, 
                        MXnum = a[j].se;
                    else if(MX == val) MXnum = min(MXnum, a[j].se);
                }
            if(MX > tmpnum[ans] + p[posl + 1][posr - 1].s) ans = MXnum;
            else if(MX == tmpnum[ans] + p[posl + 1][posr - 1].s) ans = min(ans, MXnum);
            printf("%d\n", last = pre[ans]);
        } 
    }
    return 0;
}
```




---

## 作者：hkr04 (赞：91)

分块看似暴力，但其实确实是很优美。  
在这种**不满足区间可加性**的题目中，分块就发挥了它的作用。   

这道题的题意十分清晰，就是求区间众数。   
想不出正解？我们可以用暴力。  
对于每次询问开一个桶 $t$，从左至右扫一遍，找出众数。

直接开 $10^9$ 的数组来统计肯定是会爆空间的,但是我们可以注意到，最多只可能有 $40000$ 种不同的数值，所以只要**离散化**一下就可以暴力统计了。数组 $a$ 存储原本的数值的排名，**有序数组** $b$ 存储原本的数值。    
由于数据比较良心，加上快读不开 $O_{2}$ 可以得到 $45$ 分。  

其实我们离正解并不远：  
我们可以感性理解一下，如果我们把一个数列分成几段，那么如图所示，这个区间的众数一定会是橙色区域中的众数或者蓝色区域出现了的数。  
![](https://i.loli.net/2018/11/24/5bf912331b9c0.png)  
设橙色部分中任意出现过的数字为 $x$，众数为 $f$。  
若 $x$ 原本的数量加上了在蓝色部分的数量仍然没有 $f$ 原本的数量加上 $f$ 在蓝色部分的数量之和大，那么它是不可能成为众数的。  
没出现？视为原本在橙色部分的数量为 $0$ 即可。  
若在蓝色部分没出现且本来就不是众数，就更不可能打过众数了。  
所以我们只需要考虑蓝色部分出现过的数字并将它和橙色部分的众数作比较即可。  
因为蓝色部分长度和小于两格的长度，所以每次询问最多只需要查两格这么多，一下就省去了很多时间。  
理解了这一部分，你就已经会这道题的正解了，剩下的是有一些细节的代码实现。  

为了方便，我们需要预处理一个众数数组 $f$ 和前缀和数组 $s$，$f[i][j]$ 表示从第 $i$ 个块到第 $j$ 个块中的众数，$s[i][j]$ 表示在前 $i$ 块中 $b[j]$ 出现的次数。  

一些细节在代码中有注释：  
```
#include <cstdio>
#include <cmath>
#include <algorithm>
const int maxn=40000+10;
int a[maxn],b[maxn],s[200+10][maxn],f[200+10][200+10],t[maxn];
int block;//每块长度 

int read()
{
	int x=0,p=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if (ch=='-')
			p=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*p;
}
int get_block(int u)
{
	return (u-1)/block+1;
}
inline int min(int x,int y)
{
	return x<y?x:y;
}
int main()
{
	int n=read(),m=read();
	block=int(sqrt(n));//每一块的长度
	 
	for (int i=1;i<=n;i++)
		b[i]=a[i]=read();
	std::sort(b+1, b+1+n);
	int sum=std::unique(b+1, b+1+n)-b-1,cnt=(n-1)/block+1;//sum是不同的数值个数，cnt是总块数 
	for (int i=1;i<=n;i++)
		a[i]=std::lower_bound(b+1, b+1+sum, a[i])-b;//这一部分是离散化，a存储的是a_i在b中的位置 
	
	for (int i=1;i<=cnt;i++)//预处理出f和s 
	{
		for (int j=block*(i-1)+1;j<=min(block*i, n);j++)//小心处理边界问题 
			s[i][a[j]]++;
		for (int j=1;j<=sum;j++)
			s[i][j]+=s[i-1][j];
	}
	for (int i=1;i<=cnt;i++)
		for (int j=i;j<=cnt;j++)
		{
		    int MAX=f[i][j-1];
			for (int k=block*(j-1)+1;k<=min(block*j, n);k++)//不需要从头开始扫
			    if ((s[j][a[k]]-s[i-1][a[k]]>s[j][MAX]-s[i-1][MAX])||(s[j][a[k]]-s[i-1][a[k]]==s[j][MAX]-s[i-1][MAX]&&a[k]<MAX))
					MAX=a[k];
			f[i][j]=MAX;
		}
		
	int x=0;
	while(m--)
	{
		int l=(read()+x-1)%n+1,r=(read()+x-1)%n+1;
		if (l>r)
			std::swap(l, r);
		int bl=get_block(l),br=get_block(r),MAX=0;//bl是l所属块编号，br是r所属块的编号，MAX是众数在b中的下标 
		if (br-bl<=1)//如果区间长度小于等于两格，直接暴力 
		{
			for (int i=l;i<=r;i++)
				t[a[i]]++;
			for (int i=l;i<=r;i++)
			    if (t[a[i]]>t[MAX]||(t[a[i]]==t[MAX]&&a[i]<MAX))
			        MAX=a[i];
			for (int i=l;i<=r;i++)//将桶清空 
				t[a[i]]=0;
		}
		else
		{
			for (int i=l;i<=block*bl;i++)
				t[a[i]]++;
			for (int i=block*(br-1)+1;i<=r;i++)
				t[a[i]]++;
				
			MAX=f[bl+1][br-1];
			for (int i=l;i<=block*bl;i++)//考虑蓝色部分出现的数是否会成为众数 
			{
			    int pre=t[MAX]+s[br-1][MAX]-s[bl][MAX],now=t[a[i]]+s[br-1][a[i]]-s[bl][a[i]];
			    if (now>pre||(now==pre&&MAX>a[i]))
			        MAX=a[i];
			}
			for (int i=block*(br-1)+1;i<=r;i++)
			{
			    int pre=t[MAX]+s[br-1][MAX]-s[bl][MAX],now=t[a[i]]+s[br-1][a[i]]-s[bl][a[i]];
			    if (now>pre||(now==pre&&MAX>a[i]))
			        MAX=a[i];
			}
			for (int i=l;i<=block*bl;i++)//将桶清空 
			    t[a[i]]=0;
			for (int i=block*(br-1)+1;i<=r;i++)
			    t[a[i]]=0;
		}
		x=b[MAX];
		printf("%d\n",x);
	}
	return 0;
}
```

---

## 作者：Leianha (赞：48)

## 分块

提供几个必须要知道的注意事项。

首先暴力统计区间众数的时间复杂度为接近$O(n^2)$，时间复杂度不够优秀，所以我们 ~~遇事不决先分块~~考虑分段处理。数据范围比较大，所以我们离散化。所谓离散化就是将数据排好序后用ta的排名来代替ta本身（需要另开一个数组）。$nlog(n)$时间内就能完成。

```cpp
void yych()//离散化 
{
	len=sqrt(n);
	memset(L,0x3f,sizeof(L));
	for(int i=1;i<=n;++i)
	{
		pos[i]=(i-1)/len+1;
		L[pos[i]]=min(L[pos[i]],i);
		R[pos[i]]=max(R[pos[i]],i);
		a[i]=read();
		b[i]=a[i];	
	}
	sort(b+1,b+1+n);
	tot=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
}
```


然后我们考虑分块预处理。我们首先可以处理出每个数字在块中出现次数的前缀和。枚举每一个数是$O(n)$,枚举每一个块时间是$O(\sqrt n)$,所以总的时间就是$O(n \sqrt n)$。然后我们还可以处理出从第$l$个块到第$r$个块的区间众数。我们枚举$l$的复杂度是$O(\sqrt n)$,枚举$r$的复杂度是$O(\sqrt n)$,然后枚举块内每一个数的时间复杂度也是$O(\sqrt n)$,总共就是$O(n\sqrt n)$.

```cpp
void Treaker()//分块预处理 
{
	for(int i=1;i<=n;++i)
	for(int j=pos[i];j<=pos[n];++j)s[j][a[i]]++;
	
	for(int i=1;i<=pos[n];++i)
	{
		memset(tong,0,sizeof(tong));
		for(int j=i;j<=pos[n];++j)
		{
			p[i][j]=p[i][j-1];
			for(int k=L[j];k<=R[j];++k)
			{
				tong[a[k]]++;
				if((tong[a[k]]>tong[p[i][j]])||(tong[a[k]]==tong[p[i][j]]&&a[k]<p[i][j]))p[i][j]=a[k];
			}
		}
	}
	memset(tong,0,sizeof(tong));
}
```

其中非常重要的就是
```cpp
p[i][j]=p[i][j-1];
```
因为我们首先需要继承原先的区间众数，然后才能够比较更新。否则的话就会 听取WA声一片,我就是有很多次挂在这里的 TAT.

然后就是询问操作，我们根据分块直觉，就应该是残块暴力搞，整块骚操作。所以我们对于$pos_r- pos_l \le2$的情况直接暴力就OK了。
```cpp
if(pos[r]-pos[l]<=2)
	{
		int res=0;
		for(int i=l;i<=r;++i)
		{
			++tong[a[i]];
			if(tong[a[i]]>tong[res]||(tong[a[i]]==tong[res]&&a[i]<res))res=a[i];
		}
		for(int i=l;i<=r;++i)tong[a[i]]=0;
		return res;
	}
```


对于其他的情况，我们知道我们所求的答案，要么是整块里的众数，要么是残块里的数字。对于残块里的数字，以为我们之前已经处理过了整块的数字出现的前缀和，所以我们能统计出残块中的数字在询问区间里的出现次数。对于整块中的众数，我们也能在$O(\sqrt n)$复杂度内统计出 ta在残块中的出现次数。这样我们就能得到我们询问区间里众数。

```cpp
int res=0;
	for(int i=l;i<=R[pos[l]];++i)if(!tong[a[i]])tong[a[i]]+=s[pos[r]-1][a[i]]-s[pos[l]][a[i]];
	for(int i=L[pos[r]];i<=r;++i)if(!tong[a[i]])tong[a[i]]+=s[pos[r]-1][a[i]]-s[pos[l]][a[i]];
	for(int i=l;i<=R[pos[l]];++i)
	{
		++tong[a[i]];
		if(tong[a[i]]>tong[res]||(tong[a[i]]==tong[res]&&a[i]<res))res=a[i];
	}
	for(int i=L[pos[r]];i<=r;++i)
	{
		++tong[a[i]];
		if(tong[a[i]]>tong[res]||(tong[a[i]]==tong[res]&&a[i]<res))res=a[i];
	}
	int k=p[pos[l]+1][pos[r]-1];
	int lin=s[pos[r]-1][k]-s[pos[l]][k];
	for(int i=l;i<=R[pos[l]];++i)lin+=(a[i]==k);
	for(int i=L[pos[r]];i<=r;++i)lin+=(a[i]==k);
	if(lin>tong[res]||(lin==tong[res]&&k<res))res=k;
	
	for(int i=l;i<=R[pos[l]];++i)tong[a[i]]=0;
	for(int i=L[pos[r]];i<=r;++i)tong[a[i]]=0;
	return res;
```


还有一点就是我们在统计每个数字出现的次数的时候我们需要开一个桶数组，我们每次用完了之后不用全部清空，只用将我们使用过的清空一下就珂以啦。实测可以省掉很大的时间。

最后说一下注意事项：

1.注意离散化，否则直接RE到原地起飞。

2.注意p数组的转移，否则WA到怀疑人生。

3.注意分块的边界，否则TLE到直接原地爆炸。

另外听说开$n^{\frac {1} {3}}$个块会更快一些，哪位大神能给窝解释解释?QAQ

最后献上窝丑陋的代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int n,m,tot,len,l,r,ans;
const int N=40010,M=50010,K=510;
int a[N],b[N],pos[N],s[K][N],L[K],R[K],p[K][K],tong[N];
int read()
{
	char ch;int x=0,f=1;
	while(!isdigit(ch=getchar()))
	{(ch=='-')&&(f=-f);}
	while(isdigit(ch))
	{x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
int cnt=0;
void yych()//离散化 
{
	len=sqrt(n);
	memset(L,0x3f,sizeof(L));
	for(int i=1;i<=n;++i)
	{
		pos[i]=(i-1)/len+1;
		L[pos[i]]=min(L[pos[i]],i);
		R[pos[i]]=max(R[pos[i]],i);
		a[i]=read();
		b[i]=a[i];	
	}
	sort(b+1,b+1+n);
	tot=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
}
void Treaker()//分块预处理 
{
	for(int i=1;i<=n;++i)
	for(int j=pos[i];j<=pos[n];++j)s[j][a[i]]++;
	
	for(int i=1;i<=pos[n];++i)
	{
		memset(tong,0,sizeof(tong));
		for(int j=i;j<=pos[n];++j)
		{
			p[i][j]=p[i][j-1];
			for(int k=L[j];k<=R[j];++k)
			{
				tong[a[k]]++;
				if((tong[a[k]]>tong[p[i][j]])||(tong[a[k]]==tong[p[i][j]]&&a[k]<p[i][j]))p[i][j]=a[k];
			}
		}
	}
	memset(tong,0,sizeof(tong));
}
int ask(int l,int r)
{
	if(pos[r]-pos[l]<=2)
	{
		int res=0;
		for(int i=l;i<=r;++i)
		{
			++tong[a[i]];
			if(tong[a[i]]>tong[res]||(tong[a[i]]==tong[res]&&a[i]<res))res=a[i];
		}
		for(int i=l;i<=r;++i)tong[a[i]]=0;
		return res;
	}
	int res=0;
	for(int i=l;i<=R[pos[l]];++i)if(!tong[a[i]])tong[a[i]]+=s[pos[r]-1][a[i]]-s[pos[l]][a[i]];
	for(int i=L[pos[r]];i<=r;++i)if(!tong[a[i]])tong[a[i]]+=s[pos[r]-1][a[i]]-s[pos[l]][a[i]];
	for(int i=l;i<=R[pos[l]];++i)
	{
		++tong[a[i]];
		if(tong[a[i]]>tong[res]||(tong[a[i]]==tong[res]&&a[i]<res))res=a[i];
	}
	for(int i=L[pos[r]];i<=r;++i)
	{
		++tong[a[i]];
		if(tong[a[i]]>tong[res]||(tong[a[i]]==tong[res]&&a[i]<res))res=a[i];
	}
	int k=p[pos[l]+1][pos[r]-1];
	int lin=s[pos[r]-1][k]-s[pos[l]][k];
	for(int i=l;i<=R[pos[l]];++i)lin+=(a[i]==k);
	for(int i=L[pos[r]];i<=r;++i)lin+=(a[i]==k);
	if(lin>tong[res]||(lin==tong[res]&&k<res))res=k;
	
	for(int i=l;i<=R[pos[l]];++i)tong[a[i]]=0;
	for(int i=L[pos[r]];i<=r;++i)tong[a[i]]=0;
	return res;
}
int main()
{
	cin>>n>>m;
	yych();
	Treaker();
	for(int i=1;i<=m;++i)
	{
		l=read();r=read();
		l=(l+ans-1)%n+1;r=(r+ans-1)%n+1;
		if(l>r)swap(l,r);
		ans=b[ask(l,r)];
		printf("%d\n",ans);
	}
	return 0;
}
/*
6 3 
1 2 3 2 1 2 
1 5 
3 6 
1 5
*/
```



---

## 作者：ww3113306 (赞：33)

乍一看是一道恐怖的黑题，仔细一看发现并没有那么难；

大致思路是这样的，首先我们要充分发挥分块暴力大法好的精神

先暴力预处理出每个块内每种蒲公英的个数，

然后求出对每个块而言的前缀和，

于是这样我们就可以区间查询任意两个块之间每种蒲公英的数量了

然后我们预处理出任意两个块之间的众数

最后对于每组询问，我们先找到夹在它们中间的块，

如果这个两个块r-l<=1，那么我们暴力求众数

为什么？ 因为不这样的话，万一x,y在一个快，那么r可能会比l小，要特判

如果x,y隔得很近，同样有各种奇奇怪怪的情况要做特判，

那既然这么麻烦，我们不如直接暴力搞是吧。

如果两个块相差超过了1，那么我们先取出中间块的众数，作为我们的answer，然后对旁边两个块暴力处理众数（此处注意判断时要加上中间的蒲公英）。

最后我们就得到了答案，

但是注意到ai的范围很大，所以我们需要离散化。

并且由于数量相同时要优先编号小的，于是我们处理众数的时候要多加这个判断

基本就是这样了。。。

表示本蒟蒻第一次做黑题一A过了还是很开心的(*^▽^*)（虽然说第一次交没删调试结果too many or too few lines 了，但是去掉调试就过了，也可以算是一A嘛是吧）

下面代码：

不知道为什么下面题解说块分根号n过不去？

我感觉我的速度还可以啊

至少进了第一版嘛

另外：
我之前测试程序的时候，，，发现

 6 4 
 
 7 12 8 1 7 3
 
 2 5
 
 3 3 
 
 4 6 

3 5
 
 对于这组数据，楼上某份题解会输出

1

1

1

1
 
但是答案应该是

1

1

7

1

所以可以注意一下（当然如果是我错了，，，你可以私信我）

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 40100
#define ac 210
#define D printf("line in %d\n",__LINE__);
int block,n,m,answer,tot;
int s[AC];
struct abc{
    int num,w,x;
}b[AC];//原数列+离散化后数组
int sum[ac][AC];//每种数字块内前缀和
int ans[ac][ac];//任意两块之间的众数
int belong[AC];//所属块
int color[AC];

inline int read()
{
    int x=0;char c=getchar();
    while(c>'9' || c<'0') c=getchar();
    while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
    return x;
}

bool cmp1(abc a,abc b)
{
    return a.w < b.w;
}

bool cmp2(abc a,abc b)
{
    return a.num < b.num;
}

void search(int x,int y)
{
//	printf("%d %d\n",x,y);
    int l=x/block + 1,r=y/block - 1;//取出中间块
    if(r - l <= 1)//如果x,y相差很小,那么暴力统计
    {
        answer=0;
        for(R i=x;i<=y;i++)
            if((++color[b[i].x] > color[answer]) || (color[b[i].x] == color[answer] && b[i].x < answer)) answer=b[i].x;
        for(R i=x;i<=y;i++)
            --color[b[i].x];
        printf("%d\n",s[answer]);
        return ;
    }
    else//不然的话
    {
        int ll=l * block - 1,rr=(r+1) * block;
        answer=ans[l][r];
        for(R i=x;i<=ll;i++)
        {
            ++color[b[i].x];
            if(color[b[i].x] + sum[r][b[i].x] - sum[l-1][b[i].x] > color[answer] + sum[r][answer] - sum[l-1][answer]) answer=b[i].x;
            else if(color[b[i].x] + sum[r][b[i].x] - sum[l-1][b[i].x] == color[answer] + sum[r][answer] - sum[l-1][answer] && b[i].x < answer) answer=b[i].x;//编号小也要优先，因为一行写不下，为了美观，，，就用else吧，不然就用||了
        }
        for(R i=rr;i<=y;i++)
        {
            ++color[b[i].x];
            if(color[b[i].x] + sum[r][b[i].x] - sum[l-1][b[i].x] > color[answer] + sum[r][answer] - sum[l-1][answer]) answer=b[i].x;
            else if(color[b[i].x] + sum[r][b[i].x] - sum[l-1][b[i].x] == color[answer] + sum[r][answer] - sum[l-1][answer] && b[i].x < answer) answer=b[i].x;
        }
        for(R i=x;i<=ll;i++) --color[b[i].x];
        for(R i=rr;i<=y;i++) --color[b[i].x];
        printf("%d\n",s[answer]);
        return ;
    }
}

void pre()//读入
{
    n=read(),m=read();
    block=sqrt(n);
    for(R i=1;i<=n;i++) b[i].w=read(),b[i].num=i;
    sort(b+1,b+n+1,cmp1);
    for(R i=1;i<=n;i++)
    {
        if(b[i].w != b[i-1].w) 
        {
            s[++tot]=b[i].w;//存下对应新编号的对应真实编号 
            b[i].x=tot;
        }
        else b[i].x=b[i-1].x;//离散化
    }
    sort(b+1,b+n+1,cmp2);
}

void getsum()
{//注意0也被分在块0中
    for(R i=1;i<=n;i++)
    {
        belong[i]=i/block;
        sum[belong[i]][b[i].x]++;
    }
    for(R i=0;i<=belong[n];i++)
        for(R j=1;j<=tot;j++)
            sum[i][j]+=sum[i-1][j];
}

void getans()
{
    for(R i=0;i<=belong[n];i++)
    {
        int be=i * block,now=0;
        if(!be) be=1;//这里和作诗不同，因为这里的now要参与比较了，而不是单纯的统计，而now初始值为0，所以color[0]不能被修改
        for(R j=be;j<=n;j++)
        {
            if((++color[b[j].x] > color[now]) || (color[b[j].x] == color[now] && b[j].x < now)) now=b[j].x;//更新ans
            ans[i][belong[j]]=now;//存下新ans
        }
        for(R j=be;j<=n;j++) --color[b[j].x];//暴力撤销
    }
    /*for(R i=0;i<=belong[n];i++)
    {
        for(R j=i;j<=belong[n];j++)
            printf("%d ",ans[i][j]);
        printf("\n");
    }*/
}

void work()//预处理出前缀和和众数
{
    int a,b;
    for(R i=1;i<=m;i++)
    {
        a=(read() + s[answer] -1) % n + 1,b=(read() + s[answer] - 1) % n + 1;//获取询问
        if(a < b) search(a,b);
        else search(b,a);//因为经过了运算，所以大小顺序就可能改变了
    }	
}

int main()
{
//	freopen("in.in","r",stdin);
    pre();
    getsum();
    getans();
    work();
//	fclose(stdin);
    return 0;
}
```

---

## 作者：一叶知秋。 (赞：21)

来一篇在线莫队的题解？（为什么感觉好像分块啊qwq）

[想了解莫队的点我](https://www.luogu.org/blog/codesonic/Mosalgorithm)

[想了解在线莫队的点我](https://shoko.blog.luogu.org/moqueue)，~~顺便%%%诗乃，%%%lxl~~

这道题显然是道分块裸题，但由于（~~题解里有了~~）分块码量过大，我们选择使用在线莫队（虽然就是询问的时候码量少了，但也少了很多）

首先，按照诗乃神仙的做法，我们设下许多特征区间，其实在这里的处理与分块的做法相同，不再赘述。

我们直接看结论：

一个区间（设其为$L$~$R$）的众数只能是它中间夹的一~~堆~~些连续特征区间（设其为$l$~$r$）整个的众数 $or$ $L$~$l$的蒲公英的各种种类 $or$ $r$~$R$的蒲公英的各种种类

所以我们不仅要预处理每个特征区间出现的种类的个数，还要处理$i$~$j$的众数

然后在询问时将$l$,$r$（定义见上）分别移到$L$,$R$即可。

可是这是在线莫队，每次要清空$cnt$数组，怎么办呢？再跳回来即可，记得还要将众数的出现次数清空

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

#define maxn 55555
#define sqrtn 333

inline int read(){
	int r=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return r*f;
}

inline int max(int a,int b){
	return a>b?a:b;
}

inline void swap(int &a,int &b){
	int c=a;
	a=b;
	b=c;
}

struct L_R{
	int l,r;
	int cnt[maxn];
}lr[sqrtn];

int n,m,size,cnt,s_block,a[maxn],b[maxn],lsh[maxn],pos[maxn],cnt_block[maxn];

int ans,anss[sqrtn][sqrtn];//anss[i][j]为编号为i的特征区间到编号为j的特征区间的众数

bool used[maxn];//方便清0

inline int find(int x){
	int l=0,r=n+1;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(lsh[mid]<x)l=mid;
		else r=mid;
	}
	return r;
}

inline void add(int l,int r,int x,int k){
	if(!cnt_block[x])cnt_block[x]=lr[r].cnt[x]-lr[l-1].cnt[x],used[x]=1;
    //如果是第一次遇见，那就要加上l~r(定义见上)中x出现的次数
	else if(k<0&&used[x])cnt_block[x]-=lr[r].cnt[x]-lr[l-1].cnt[x],used[x]=0;
    //退回来时第一次看见，就要减去l~r(定义见上)中x出现的次数
	cnt_block[x]+=k;
	if(k<0)return;
	if(cnt_block[x]>cnt_block[ans])ans=x;//比较答案是否更优
	else if(cnt_block[x]==cnt_block[ans]&&x<ans)ans=x;
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)lsh[i]=a[i]=read();
	sort(lsh+1,lsh+1+n);
	for(int i=2;i<=n;i++)
		if(lsh[i-1]==lsh[i])lsh[i-1]=1e9+10;
	sort(lsh+1,lsh+1+n);
	for(int i=1;i<=n;i++){//离散化
		int wz=find(a[i]);
		b[wz]=a[i],a[i]=wz;
		cnt=max(cnt,a[i]);
	}
	s_block=size=sqrt(n);
	for(int i=1;i<=s_block;i++){//预处理，特征区间一般存个数存的都是前缀和
		lr[i].l=(i-1)*size+1,lr[i].r=i*size;
		for(int j=(i-1)*size+1;j<=i*size;j++)lr[i].cnt[a[j]]++,pos[j]=i;
		for(int j=1;j<=cnt;j++)lr[i].cnt[j]+=lr[i-1].cnt[j];
	}
	if(size*size<n){//还有一小块没处理
		lr[s_block+1].l=size*size+1,lr[s_block+1].r=n;
		for(int i=size*size+1;i<=n;i++)lr[s_block+1].cnt[a[i]]++,pos[i]=s_block+1;
		for(int i=1;i<=cnt;i++)lr[s_block+1].cnt[i]+=lr[s_block].cnt[i];
		s_block++;
	}
	for(int i=1;i<=s_block;i++){//算anss
		for(int j=i;j<=s_block;j++,anss[i][j]=anss[i][j-1]){
        //记得继承i~j-1的众数，否则倘若一个数未出现在这一个特征区间里，但i~j-1个特征区间里出现的特别多，那就没有考虑到
			for(int k=lr[j].l;k<=lr[j].r;k++){
				cnt_block[a[k]]++;
				if(cnt_block[a[k]]>cnt_block[anss[i][j]])anss[i][j]=a[k];
				else if(cnt_block[a[k]]==cnt_block[anss[i][j]]&&a[k]<anss[i][j])anss[i][j]=a[k];
			}
		}
		for(int j=1;j<=cnt;j++)cnt_block[j]=0;
	}
	for(int i=1;i<=m;i++){
		int L=(read()+b[ans]-1)%n+1,R=(read()+b[ans]-1)%n+1;
		if(L>R)swap(L,R);
		int LL=R+1,RR=R;
		int l=R+1,r=R,posl=1,posr=0;
		if(pos[L]+1<pos[R]){//中间夹了特征区间
			posl=pos[L]+1,posr=pos[R]-1;
			ans=anss[posl][posr];
			l=LL=lr[posl].l;
			r=RR=lr[posr].r;
			cnt_block[ans]=lr[posr].cnt[ans]-lr[posl-1].cnt[ans];
		}
        //莫队
		while(l>L)add(posl,posr,a[--l],1);
		while(r<R)add(posl,posr,a[++r],1);
		printf("%d\n",b[ans]);
        //记得扫回来
		while(l<LL)add(posl,posr,a[l++],-1);
		while(r>RR)add(posl,posr,a[r--],-1);
		if(pos[L]+1<pos[R])//记得减去中间夹的特征区间的众数个数
			cnt_block[anss[posl][posr]]-=lr[posr].cnt[anss[posl][posr]]-lr[posl-1].cnt[anss[posl][posr]];
	}
	return 0;
}
```


---

## 作者：mulberror (赞：20)

$$\href{http://blog.chhokmah.top/index.php/archives/37/}{\Large\texttt{My blog}}$$

---
# Description
求区间众数，如果有多个取最小的那一个
强制在线
# Data range 
$n\leq 40000$
# Solution
先离散化一下。  
用分块**边角暴力**的思想。  
首先把问题分成边角和整段讨论。  
我们设$cnt[l][r][x]$表示的第$l$段到第$r$段中$x$出现的次数。  
暴力求解是$tot^2\times n$，$tot$是块的个数。  
维护$f[i][j]$表示的是整段$i$到$j$的众数出现的次数，并且记录$d[i][j]$为该数为多少。  
以上所有操作的复杂度为$tot^2\times n$。
差不多完成了整段的任务了。   
那么考虑边角暴力。    
如果相邻在一起，那么就直接暴力求解。    
如果不是相邻，那么就修改在当前的整段答案上。    
什么意思
假如说你现在要查询的区间是$[l,r]$  
整段的区间是$[bl,br]$  
很明显我们已经求出了$[bl,br]$。
那么在边角暴力查询的时候我们就把答案累加在$[bl,br]$的答案上就可以了，之后不要忘记还原。  
注意一点，不要非常傻的累加答案后暴力，因为插入一个数只有这个数改变，换句话说就是只有这个数原来的答案会对答案产生影响，只需要判断这个数的改变量就可以了。  
以上的复杂度为$\frac{mn}{tot}$，设$n$和$m$是同阶的，那么可得当$tot$为$^3\sqrt{n}$运行最快。   
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x) {
    x = 0; T fl = 1; char ch = 0; 
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') fl = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x *= fl;
}
const int N = 40000 + 5;
int n, m, blo, dn, ans, tot, L, R, ANS1, ANS2;
int disc[N], a[N], b[N], cnt[45][45][N], pos[N], num[45][45], f[45][45];
int st(int x) { return x * blo - blo + 1; }
int ed(int x) { return x * blo; }
void read_disc() {
    read(n); read(m); 
    tot = (int) pow(n * 1.0, 1.0 / 3);
    if (tot) blo = n / tot; 
    if (n % blo != 0) tot ++; 
    for (int i = 1; i <= n; i ++) 
        read(a[i]), disc[i] = a[i], pos[i] = (i - 1) / blo + 1;
    sort(disc + 1, disc + 1 + n); dn = unique(disc + 1, disc + 1 + n) - disc - 1;
    for (int i = 1; i <= n; i ++) 
        b[i] = lower_bound(disc + 1, disc + 1 + dn, a[i]) - disc;
}
void pre() {
    for (int i = 1; i <= tot; i ++) 
        for (int j = i; j <= tot; j ++) {
            for (int k = st(i); k <= ed(j); k ++) cnt[i][j][b[k]] ++;
            for (int k = 1; k <= dn; k ++) 
                if (cnt[i][j][k] > f[i][j] || (cnt[i][j][k] == f[i][j] && num[i][j] > k))  
                    f[i][j] = cnt[i][j][k], num[i][j] = k; 
        }
}
void add(int x) {
    cnt[L][R][b[x]] ++;
    if (cnt[L][R][b[x]] > ANS1 || (cnt[L][R][b[x]] == ANS1 && b[x] < ANS2)) 
        ANS1 = cnt[L][R][b[x]], ANS2 = b[x];
}
int query(int ql, int qr) {
    int px = pos[ql], py = pos[qr];
    L = px + 1, R = py - 1; 
    if (L > R) L = R = 0;  
    ANS1 = f[L][R], ANS2 = num[L][R];
    if (px == py) {
        for (int i = ql; i <= qr; i ++) add(i);
        for (int i = ql; i <= qr; i ++) cnt[L][R][b[i]] --;
    } else {
        for (int i = ql; i <= ed(px); i ++) add(i);
        for (int i = st(py); i <= qr; i ++) add(i);
        for (int i = ql; i <= ed(px); i ++) cnt[L][R][b[i]] --;
        for (int i = st(py); i <= qr; i ++) cnt[L][R][b[i]] --;
    }
    return disc[ANS2];
}
int main() {
    read_disc(); pre();
    ans = 0; 
    for (int i = 1; i <= m; i ++) {
        int x, y, ql, qr; read(x); read(y);  
        ql = (x + ans - 1) % n + 1, qr = (y + ans - 1) % n + 1;
        if (ql > qr) swap(ql, qr); ans = query(ql, qr);
        printf("%d\n", ans); 
    }
    return 0;
}
```

---

## 作者：linakrbcs (赞：14)

## 阅读提示

本题解注重思维，较为详细地叙述了提出算法及优化时空复杂度的过程。

希望读者阅读时充分地开动脑筋，不要浅尝辄止或走马观花。

## 题意简述

给出 $n$ 个数的序列 $a _ 1 \sim a _ n$，有 $m$ 个询问，每次给出询问区间 $\left[ l , r \right]$，求 $a _ l \sim a _ r$ 的**众数**最小值。**（强制在线）**

## 算法分析

区间问题常用树状数组、线段树等数据结构维护，但它们难以应用于本题。

原因是：已知左、右两段区间的众数，一般不能直接推得整个区间的众数，即使额外维护一些信息也是如此（即众数**不具有“区间可加性”**）。

于是考虑分块处理。

具体地，将 $a _ 1 \sim a _ n$ 划分为 $t$ 块，块长为 $d$（首尾两块可能不同）。则每个 $\left[ l , r \right]$ 由若干**连续整块**，以及至多首尾两个**非整块**组成。

注意到，如果一个数不是连续整块的众数，则一定需要通过在非整块中出现来增加出现次数，才有可能成为 $a _ l \sim a _ r$ 的众数。

于是得到**引理：$a _ l \sim a _ r$ 的众数只可能是 $\left[ l , r \right]$ 对应连续整块的众数，或是在非整块中出现的数。**

### 方法一

由上述引理，可以自然得到以下算法：

首先将数列离散化，使值域在 $1 \sim n$ 内。

预处理 $Cnt _ {i , j} \left( w \right)$ 为数值 $w$ 在第 $i \sim j$ 块出现的次数，$Mode _ {i , j}$ 为第 $i \sim j$ 块的众数。

对每个左端点 $i$，依次从 $i$ 到 $t$ 扫描 $j$，在 $Cnt _ {i , j - 1}$ 的基础上加入第 $j$ 块元素的计数，即得 $Cnt _ {i , j}$。

在更新 $Cnt _ {i , j}$ 时进行比较，顺便可得到 $Mode _ {i , j}$。

这样，对询问区间 $\left[ l , r \right]$，设其对应连续整块为第 $i \sim j$ 块，则连续整块部分的众数为 $Mode _ {i , j}$。

对于非整块中出现的数，在 $Cnt _ {i , j}$ 的基础上，加入它们的计数。如果某个数值能够替换当前众数（指这个数值出现的次数比当前众数多，或者当出现次数相等时，数值比当前众数小），则将其替换为新的众数。

时间复杂度 $O \left( n \log n + n t ^ 2 + m d \right)$，空间复杂度 $O \left( n t ^ 2 \right)$。由

$$O \left( n t ^ 2 + m d \right) = O \left( \dfrac {n ^ 3} {d ^ 2} + m d \right) = O \left( \dfrac {n ^ 3} {d ^ 2} + m d + m d \right) \ge O \left( \sqrt [3] {n ^ 3 m ^ 2} \right) = O \left( n m ^ {\frac 2 3} \right) .$$

等号成立时 $\dfrac {n ^ 3} {d ^ 2} = m d$，即 $d = \dfrac n {\sqrt [3] m}$。

于是，取 $d = \dfrac n {\sqrt [3] m}$，$t = \sqrt [3] m$ 时，时间复杂度 $O \left( n \log n + n m ^ {\frac 2 3} \right)$，空间复杂度 $O \left( n m ^ {\frac 2 3} \right)$，在洛谷上已经可以 AC 了。

（代码链接在文末）

#### 小细节

- 处理每次询问时，不能用 `memset` 或 `memcpy` 对一个大小为 $O \left( n \right)$（离散化后的值域）的数组进行赋值，否则会破坏这部分 $O \left( m d \right)$ 的时间复杂度。  
  正确的做法是：直接在对应 $Cnt _ {i , j}$ 的基础上修改，统计结束后，重新扫描一遍涉及的元素，并减去其计数，即恢复原状态。
- 当 $l$ 和 $r$ 在同一块时，注意特判（基本上所有分块都要注意这一点）。

### 方法二

真正热爱算法竞赛的人，不应以 AC 为终极目的。

方法一的时空复杂度相对较高，虽然在洛谷能过，但在我弱校 OJ 上就够呛。~~说到底还是为了在我弱校 OJ 上 AC。~~

注意到方法一中将 $Cnt _ {i , j}$ 赋值为 $Cnt _ {i , j - 1}$ 的复杂度较高——单次 $O \left( n \right)$，考虑省去这个过程。

但这意味着，当 $i$ 不变，$j$ 增加时，$Cnt _ {i , j}$ 必须现用现改，无法保存了，只能保存 $Mode _ {i , j}$。

于是对于非整块中出现的数值，要另辟蹊径查询其在 $a _ l \sim a _ r$ 中出现的次数。

考虑对每个数值 $w$ 开一个**动态数组** $v _ w \left( k \right)$，记录其在 $a _ 1 \sim a _ n$ 中出现的所有位置。

这样，要查询数值 $w$ 在 $a _ l \sim a _ r$ 中出现的次数，在 $v _ i$ 中**二分查找**第一个**大于** $r$ 的位置和第一个**大于等于** $l$ 的位置，二者相减，即为答案。

剩下的操作就和方法一基本相同了。

时间复杂度 $O \left( n \log n + n t + m d \log n \right)$，空间复杂度 $O \left( n + t ^ 2 \right)$。由

$$O \left( n t + m d \log n \right) = O \left( \dfrac {n ^ 2} d + m d \log n \right) \ge O \left( \sqrt {n ^ 2 m \log n} \right) = O \left( n \sqrt {m \log n} \right) .$$

等号成立时 $\dfrac {n ^ 2} d = m d \log n$，即 $d = \dfrac n {\sqrt {m \log n}}$。

注意二分查找的 $\log$ 底数取 $2$ 较合适。于是，取 $d = \dfrac n {\sqrt {m \log _ 2 n}}$，$t = \sqrt {m \log _ 2 n}$ 时，时间复杂度 $O \left( n \log n + n \sqrt {m \log n} \right)$，空间复杂度 $O \left( n + m \log n \right)$。

#### 小细节

- 虽然理想块长为 $d = \dfrac n {\sqrt {m \log _ 2 n}}$，但不建议在程序中直接写 `n/sqrt(m*log2(n))`！  
  当 $n = 1$ 时，$\log _ 2 n = 0$，引发除数为 $0$。浮点数除数为 $0$ 不会直接报错，根据程序原理，结果可能正确，可能异常。  
  使用 `n/sqrt(m*log2(n+1))` 可以回避这个问题。

### 方法三

以上两种方法记载于蓝书《算法竞赛进阶指南》。有没有更好的做法呢？李煜东老师告诉我们：

> 虽然很多问题的时间复杂度是有下界的，但从某种程度上说，算法的设计、优化是永无止境的。

在这句话的指引下，我们希望把方法二时间复杂度中的 $\sqrt {\log n}$ 去掉，也就是省去二分查找。

于是考虑预处理 $S _ i \left( w \right)$ 表示 $w$ 在第 $i$ 块中出现的次数。

设 $\left[ l , r \right]$ 对应的连续整块为第 $i \sim j$ 块，$Cnt \left( w \right)$ 为数值 $w$ 在非整块中出现的次数，则 $w$ 在 $a _ l \sim a _ r$ 中出现的次数为

$$S _ j \left( w \right) - S _ {i - 1} \left( w \right) + Cnt \left( w \right).$$

运用这个值，在经方法二预处理得到的 $Mode _ {i , j}$ 基础上更新众数即可。

时间复杂度 $O \left( n \log n + n t + m d \right)$，空间复杂度 $O \left( n t \right)$。由

$$O \left( n t + m d \right) = O \left( \dfrac {n ^ 2} d + m d \right) \ge O \left( \sqrt {n ^ 2 m} \right) = O \left( n \sqrt m \right) .$$

等号成立时 $\dfrac {n ^ 2} d = m d$，即 $d = \dfrac n {\sqrt m}$。

于是，取 $d = \dfrac n {\sqrt m}$，$t = \sqrt m$ 时，时间复杂度 $O \left( n \log n + n \sqrt m \right)$，空间复杂度 $O \left( n \sqrt m \right)$。

### 方法四

方法三的时间复杂度优于方法二，但空间复杂度反而劣于方法二（对数变成了根号）。~~我弱校 OJ 上 AC 不了。~~

注意到 $S _ i \left( w \right)$ 占用空间太大，这使我们想要请回动态数组 $v _ w \left( k \right)$。但二分查找的问题又横在我们面前。

如果预处理每个 $a _ x$ 在 $v _ {a _ x} \left( k \right)$ 中出现的位置 $u _ x$，那么，当查询 $w$ 在 $a _ l \sim a _ r$ 中出现的次数时，如果 $a _ l = w$ **且** $a _ r = w$，则答案为 $u _ r - u _ l + 1$。

现在问题是：$a _ l = w$ 且 $a _ r = w$ 不一定满足。

但是，对每个 $\left[ l , r \right]$ 划分出的非整块至多只有首尾两个。对首块扫描到 $a _ x$，一定有 $\left[ x , r \right] \subseteq \left[ l , r \right]$ 且 $a _ l = w$（不是从前到后第一次出现的元素，其贡献可以直接忽略）；对尾块扫描到 $a _ x$，一定有 $\left[ l , x \right] \subseteq \left[ l , r \right]$ 且 $a _ r = w$（不是从后到前第一次出现的元素，其贡献可以直接忽略）。

即 $a _ l = w$ **或** $a _ r = w$ 一定满足。

这启示我们用**单调性**解决问题。

具体地，预处理时，在方法二的基础上，除了保留 $Mode _ {i , j}$，还保留连续整块众数的出现次数 $Cnt _ {i , j}$，其他数出现次数仍不保留。

对询问区间 $\left[ l , r \right]$，设对应的连续整块为第 $i \sim j$ 块，当前已处理部分的众数为 $mode$，其出现次数为 $cnt$。初始 $mode = Mode _ {i , j}$，$cnt = Cnt _ {i , j}$。

对于首块的所有元素 $a _ x$：

- 若 $v _ {a _ x} \left( u _ x + cnt - 1 \right) > r$ 或越界，则 $a _ x$ 的出现次数小于 $cnt$，不能更新 $mode$。
- 若 $v _ {a _ x} \left( u _ x + cnt - 1 \right) \le r$，但 $v _ {a _ x} \left( u _ x + cnt \right) > r$ 或越界，则 $a _ x$ 的出现次数等于 $cnt$，应将 $mode$ 与 $a _ x$ 取 $\min$。
- 若 $v _ {a _ x} \left( u _ x + cnt \right) \le r$，则 $a _ x$ 的出现次数大于当前的 $cnt$，应将 $a _ x$ 作为新的 $mode$，并更新 $cnt$。

对于尾块，同理可解决该问题。

时间复杂度分析与方法三相同，但空间复杂度 $O \left( n + t ^ 2 \right) = O \left( n + m \right)$。

实测该方法在时间上也更优，加了快读快写后竟然成了[最优解](https://www.luogu.com.cn/record/137919302)（在~~开了 O2 并~~用了 `vector` 的情况下）。

## 总结

对一道好题来说，AC 只是最低要求，更重要的是让题目拓展我们的思维，激发有深度的思考，让我们切切实实感受到这道题对我们的益处。

本文提到了几个细节，也是用自己的人生经验提醒大家“细节决定成败”。

~~另外，感谢我弱校 OJ 对于我写这篇题解的贡献。~~

## 参考

李煜东《算法竞赛进阶指南》0x44

## 代码

- [方法一](https://www.luogu.com.cn/paste/swkuixo7)
- [方法二](https://www.luogu.com.cn/paste/d6as4rqf)
- [方法三](https://www.luogu.com.cn/paste/9oju1crw)
- [方法四](https://www.luogu.com.cn/paste/pfm7hua0)


---

## 作者：dz_ice (赞：11)

前几天刚学习了分块，感觉这道题用分块求解的方式挺巧妙的

既然用的是分块，那么肯定是两端暴力求解，中间要快速地处理每个块

首先我们要得到一个结论，最后求出的这一个众数必定为中间块的众数或者是两端的任意一个数，那么我们用$nu[i][j]$来表示第$i$个块到第$j$个块的众数，我们可以用用$O(n\sqrt{n})$的时间复杂度，先枚举每个块，然后枚举后面的点来求出$nu[i][j]$,放一下这一段的代码

```
void pre(int x)
{
	memset(cnt,0,sizeof(cnt));
	int maxx=0,num1=0;
	for(int i=(x-1)*m+1;i<=n;i++)
	{
		cnt[a[i]]++;
		if(cnt[a[i]]>maxx||(cnt[a[i]]==maxx&&a[i]<num1))
			maxx=cnt[a[i]],num1=a[i];
		nu[x][pos[i]]=num1;
	}
}
```

接下来就是每一次的询问，先假定中间的块的众数为整个区间的众数，并求出在区间内的个数，再枚举两端的每一个点，求出在区间内的个数，如果比之前的多那么就更新

至于求一个数在区间内的个数，我们可以巧用$vector$,记录每个数字出现的位置，然后用upper_bound和lower_bound求出在区间内的个数

记得离散化！

```
#include<bits/stdc++.h>
using namespace std;
int n,a[100003],num[100003],id,pos[100003],l,r,su,cnt[100003],nu[3003][3003],res,m,b[100003],las,o;
vector<int>l1[100003];
map<int,int>mp;
int ask1(int ll,int rr,int x)
{
	return upper_bound(l1[x].begin(),l1[x].end(),rr)-lower_bound(l1[x].begin(),l1[x].end(),ll); //求出一个数在区间内的个数
}
void pre(int x) //预处理nu[i][j]
{
	memset(cnt,0,sizeof(cnt));
	int maxx=0,num1=0;
	for(int i=(x-1)*m+1;i<=n;i++)
	{
		cnt[a[i]]++;
		if(cnt[a[i]]>maxx||(cnt[a[i]]==maxx&&a[i]<num1))
			maxx=cnt[a[i]],num1=a[i]; 
		nu[x][pos[i]]=num1;
	}
}
int ask(int l1,int r1)
{
	int maxx=0,num1=0;
	if(pos[l1]+1<pos[r1])
		maxx=ask1(l1,r1,nu[pos[l1]+1][pos[r1]-1]),num1=nu[pos[l1]+1][pos[r1]-1]; //假定众数为中间的块的众数
	for(int i=l1;i<=min(r1,pos[l1]*m);i++) //枚举左端的块
	{
		res=ask1(l1,r1,a[i]);
		if(res>maxx||(res==maxx&&a[i]<num1))
			maxx=res,num1=a[i];
	}
	if(pos[l1]!=pos[r1]) //枚举右端的块
		for(int i=(pos[r1]-1)*m+1;i<=r1;i++)
		{
			res=ask1(l1,r1,a[i]);
			if(res>maxx||(res==maxx&&a[i]<num1))
				maxx=res,num1=a[i];
		}
	return num[num1];
}
int main()
{
	scanf("%d%d",&n,&o);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		if(!mp[b[i]])
			id++,mp[b[i]]=id,num[id]=b[i]; //离散化
	for(int i=1;i<=n;i++)
		a[i]=mp[a[i]],l1[a[i]].push_back(i); 
	for(int i=1;i<=id;i++)
		l1[i].push_back(n+1);
	m=pow(n,0.4);
	for(int i=1;i<=n;i++)
		pos[i]=(i-1)/m+1;
	su=pos[n];
	for(int i=1;i<=su;i++)
		pre(i);
	for(int i=1;i<=o;i++)
	{
		scanf("%d%d",&l,&r);
		l=(l+las-1)%n+1,r=(r+las-1)%n+1;
		if(l>r)
			swap(l,r);
		las=ask(l,r);
		cout<<las<<endl;
	}
	return 0;
}

```


---

## 作者：arfa (赞：11)

好久以前就要写的博客拖到运动会来写....(~~当时思路好像还是原创的,现在不是了~~)

先说明并没有 $A$ 这道题,但是 $A$ 了 [$loj$ 分块 $9$](https://loj.ac/problem/6285) (也是区间众数,我是按在线做的)。**如果有大佬知道为什么我没有 $A$ 蒲公英可以来 @ 我!**。

本篇适合于刚刚入手分块的蒟蒻(~~超详细~~)。

首先我们先把区间分块(~~废话~~)。考虑到一个区间的众数是要不是这个区间的**最大块的答案**,就是**旁边多出来的边角的数字**。因为任何数在**最大块中出现的次数** 肯定小于 **最大块的众数的出现次数**,而边角却可以让自己的出现次数增加来达到超越最大块的众数的效果。

![](https://i.loli.net/2018/11/21/5bf4ebe8e4cb3.png)

(如图,黄色部分的数字的出现次数可能超过最大块众数 $x$ 的出现次数,红色为最大块的边界)

所以我们就可以预处理出第 $i$ 块到第 $j$ 块的众数,且要知道最大块中的每个数字的出现次数。

首先要预处理每个块中数的出现次数。如果我们定义数组 $times[i,j,x]$ 代表 $i$ 块到 $j$ 块的出现次数的话,空间爆炸 $n \times \sqrt{n} \times \sqrt{n}$ --- $O(n^2)$。如果我们用 $times[i,x]$ 表示第 $i$ 块 $x$ 的出现次数的话,时间复杂度爆炸 --- 一次查询 $O(\sqrt{n} \times \sqrt{n})$ (因为我们还要一块一块的找出现次数,本来的时间复杂度就 $\sqrt{n}$)。然后我们就机制的把 $times[i,x]$ 定义为 $1$~$i$ 的 $x$ 的出现次数。那我们查询第 $i$ 块到第 $j$ 块的出现次数就是 $times[i,x]-times[j-1,x]$ 了。预处理复杂度 $O(n \sqrt{n})$。(离散化以后)

```pascal
j:=1;
for i:=1 to n do
begin
    inc(times[j,num[i]]);
    if i mod (block_num-1)=0 then // block_num 代表块的个数
    begin
        for k:=1 to tail do times[j+1,k]:=times[j,k]; // 全部数字都要继承
        inc(j); // 又过了一块
    end;
end;
```

接下来我们要快速构造数组 $ans[i,j]$ 代表第 $i$ 块到第 $j$ 块的答案。我们想,如果我们已经有了 $ans[i,j-1]$,我们如何求 $ans[i,j]$ ? 暴力跑一遍啊!反正中间只有 $\sqrt{n}$ 个数字! 为什么上一个答案可以拿来比较? 因为 $i,j$ 包括着 $i,j-1$,我们已知的众数只有 $ans[i-1,j]$,那么只有块 $j-1$ 到块 $j$ 这个地方又可能超过原有的众数,其实就是一个查询。 其中我们要两个循环 $i,j$ 所以时间复杂度变为 $\sqrt{n} \times \sqrt{n}$ --- $O(n)$,然后暴力扫,变为 $O(n \sqrt{n})$。

```pascal
for i:=1 to block_num do
    for j:=i to block_num do
    begin
        now:=ans[i,j-1]; // 上一次的答案
        for k:=(j-1)*node_num+1 to min(n,j*node_num) do // 这个块
        begin
            tmp1:=times[j,num[k]]-times[i-1,num[k]]; // 现有答案的出现次数
            tmp2:=times[j,now]-times[i-1,now]; // 可能的数的出现次数
            if (tmp1>tmp2)or((tmp1=tmp2)and(num[k]<now)) then now:=num[k]; // 更好就更新
        end;
        ans[i,j]:=now;
     end;
```

查询的思路讲得很清楚了,大家主要看注释。

讲一下定义:

- $Ready$ 输入 $+$ 离散化 $+$ 预处理
- $now$ 答案的离散化后的编号
- $recf$ 编号所对应的原有数组
- $Locate$ 这个位置在第几块 
- $real[1$~$2]$ 最大块的边界的块编号 (比如 $l=1$ 的时候 $real[1]=1$,$r=n$ 的时候 $real[2]=Locate(n)$)
- $bucket$ 这个数字在边角的出现次数
- $node_{num}$ 每个块的数字个数

```pascal

begin
    Ready; now:=0; recf[0]:=0; // 一开始 now=0
    for i:=1 to m do
    begin
        read(l,r);
        real[1]:=Locate(l); real[2]:=Locate(r); bucket[0]:=0;
        if real[2]-real[1]<=1 then // 可以暴力就暴力 复杂度是两个 sqrt(n)
        begin
            now:=0; 
            for k:=l to r do
            begin
                inc(bucket[num[k]]);
                if (bucket[num[k]]>bucket[now])or((bucket[num[k]]=bucket[now])and(now>num[k])) then now:=num[k];
            end;
            for k:=l to r do bucket[num[k]]:=0;
            writeln(recf[now]);
        end
        else
        begin // 只有左右需要暴力,还要清空,所以是四个 sqrt(n)
            now:=ans[real[1]+1,real[2]-1]; // 最大块的出现次数
            for k:=l to min(n,real[1]*node_num) do // 左边角暴力
            begin
                inc(bucket[num[k]]);
                tmp1:=bucket[num[k]]+times[real[2]-1,num[k]]-times[real[1],num[k]];
                tmp2:=bucket[now]+times[real[2]-1,now]-times[real[1],now];
                if (tmp1>tmp2)or((tmp1=tmp2)and(now>num[k])) then now:=num[k];
            end;
            for k:=(real[2]-1)*node_num+1 to r do // 右边角暴力
            begin
                inc(bucket[num[k]]);
                tmp1:=bucket[num[k]]+times[real[2]-1,num[k]]-times[real[1],num[k]];
                tmp2:=bucket[now]+times[real[2]-1,now]-times[real[1],now];
                if (tmp1>tmp2)or((tmp1=tmp2)and(now>num[k])) then now:=num[k];
            end;
            // 清空
            for k:=l to min(n,real[1]*node_num) do bucket[num[k]]:=0;
            for k:=(real[2]-1)*node_num+1 to r do bucket[num[k]]:=0;
            writeln(recf[now]);
        end;
    end;
end.
```

写了好久,希望给个赞再走 $QwQ$。

---

## 作者：Tari (赞：10)

[My Blog](https://www.cnblogs.com/Jackpei/p/11105253.html)

这道题算是好好写了。写了三种方法。

注:$pos[i]$表示$i$属于第$pos[i]$块。

###### upd：代码已经格式化
------------


第一种是统计所有可能的块组成的区间中（第i块到第j块）,每个数出现的次数，记做$f[i][j][k]$，和所有可能的块组成的区间的答案，记做$h[i][j]$。

然后每次先把整块的答案作为初始答案，然后对于散块中的每个值$vl$，暴力修改对应的$f[i][j][vl]$,更新答案。

当块长取$N^\frac{2}{3}$,时间复杂度$O(N^\frac{5}{3})$级。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define ull unsigned long long
#define ll long long
#define R register int
#define pause (for (R i = 1; i <= 10000000000; ++i))
#define OUT freopen("out.out", "w", stdout);
using namespace std;
namespace Fread
{
static char B[1 << 15], *S = B, *D = B;
#define getchar() (S == D && (D = (S = B) + fread(B, 1, 1 << 15, stdin), S == D) ? EOF : *S++)
inline int g()
{
  R ret = 0, fix = 1;
  register char ch;
  while (!isdigit(ch = getchar()))
    fix = ch == '-' ? -1 : fix;
  do
    ret = ret * 10 + (ch ^ 48);
  while (isdigit(ch = getchar()));
  return ret * fix;
}
inline bool isempty(const char &ch) { return ch <= 36 || ch >= 127; }
inline void gs(char *s)
{
  register char ch;
  while (isempty(ch = getchar()))
    ;
  do
    *s++ = ch;
  while (!isempty(ch = getchar()));
}
} // namespace Fread
using Fread::g;
using Fread::gs;
const int N = 40010, M = 37;
int n, m, tot, T, lst;
int f[M][M][N], h[M][M], vl[N], a[N], b[N], pos[N];
inline void PRE()
{
  R mx = 0, ans = 0;
  for (R i = 1; i <= n; ++i)
    pos[i] = (i - 1) / T + 1;
  for (R j = 1, L = pos[n]; j <= L; ++j, mx = 0, ans = 0)
    for (R t = j; t <= L; ++t)
    {
      memcpy(f[j][t], f[j][t - 1], sizeof(f[j][t - 1]));
      for (R i = (t - 1) * T + 1, LL = min(t * T, n); i <= LL; ++i)
        ++f[j][t][a[i]];
      for (R i = tot; i; --i)
        if (f[j][t][i] >= mx)
          mx = f[j][t][i], ans = i;
      h[j][t] = ans;
    }
}
signed main()
{
#ifdef JACK
  freopen("NOIPAK++.in", "r", stdin);
  OUT;
#endif
  n = g(), m = g(), T = n / pow(n, 1.0 / 3);
  for (R i = 1; i <= n; ++i)
    a[i] = g();
  memcpy(b, a, sizeof(a));
  sort(b + 1, b + n + 1);
  tot = unique(b + 1, b + n + 1) - b - 1;
  for (R i = 1; i <= n; ++i)
    a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
  memcpy(vl, b, sizeof(int) * (tot + 1));
  PRE();
  for (R i = 1, l, r; i <= m; ++i)
  {
    R mx = 0, ans = 0;
    l = (g() + lst - 1) % n + 1, r = (g() + lst - 1) % n + 1;
    l > r ? swap(l, r) : (void)0;
    R p = pos[l] + 1, q = pos[r] - 1;
    ans = h[p][q], mx = f[p][q][ans];
    if (pos[l] == pos[r])
    {
      for (R i = l; i <= r; ++i)
      {
        ++f[p][q][a[i]];
        if (f[p][q][a[i]] > mx || (f[p][q][a[i]] == mx && a[i] < ans))
          mx = f[p][q][a[i]], ans = a[i];
      }
      for (R i = l; i <= r; ++i)
        --f[p][q][a[i]];
    }
    else
    {
      ans = h[p][q], mx = f[p][q][ans];
      for (R i = l, L = pos[l] * T; i <= L; ++i)
      {
        ++f[p][q][a[i]];
        if (f[p][q][a[i]] > mx || (f[p][q][a[i]] == mx && a[i] < ans))
          mx = f[p][q][a[i]], ans = a[i];
      }
      for (R i = (pos[r] - 1) * T + 1; i <= r; ++i)
      {
        ++f[p][q][a[i]];
        if (f[p][q][a[i]] > mx || (f[p][q][a[i]] == mx && a[i] < ans))
          mx = f[p][q][a[i]], ans = a[i];
      }
      for (R i = l, L = pos[l] * T; i <= L; ++i)
        --f[p][q][a[i]];
      for (R i = (pos[r] - 1) * T + 1; i <= r; ++i)
        --f[p][q][a[i]];
    }
    printf("%d\n", lst = vl[ans]);
  }
}
    

```


------------
                                            
                                            
第二种是预处理出所有可能的块组成的区间中（第$i$块到第$j$块）的答案$f[i][j]$,并且拿一个$vector$存每个数$vl$出现的位置$s[vl][1...n]$。

答案初始化为整块的答案，然后对于散块中的每个数$vl$,在$s[vl]$中二分出$[l,r]$的最小和最大的位置的下标，相减就是$[l,r]$有多少个$vl$,然后更新答案。

当块长取$\sqrt{\frac{N}{logN}}$,时间复杂度$O(N\sqrt{NlogN})$。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define ull unsigned long long
#define ll long long
#define R register int
#define pause (for (R i = 1; i <= 10000000000; ++i))
#define OUT freopen("out.out", "w", stdout);
using namespace std;
namespace Fread
{
static char B[1 << 15], *S = B, *D = B;
#define getchar() (S == D && (D = (S = B) + fread(B, 1, 1 << 15, stdin), S == D) ? EOF : *S++)
inline int g()
{
  R ret = 0, fix = 1;
  register char ch;
  while (!isdigit(ch = getchar()))
    fix = ch == '-' ? -1 : fix;
  do
    ret = ret * 10 + (ch ^ 48);
  while (isdigit(ch = getchar()));
  return ret * fix;
}
inline bool isempty(const char &ch) { return ch <= 36 || ch >= 127; }
inline void gs(char *s)
{
  register char ch;
  while (isempty(ch = getchar()))
    ;
  do
    *s++ = ch;
  while (!isempty(ch = getchar()));
}
} // namespace Fread
using Fread::g;
using Fread::gs;
const int N = 40010;
int n, m, T, tot, lst;
vector<int> s[N];
#define pb push_back
int f[10010][10010], cnt[N], p[N], pos[N], a[N], b[N], vl[N];
inline void PRE(int p)
{
  R ans = 0, mx = 0;
  memset(cnt, 0, sizeof(cnt));
  for (R t = p, lim = pos[n]; t <= lim; ++t)
  {
    for (R i = (t - 1) * T + 1, lim = min(n, t * T); i <= lim; ++i)
    {
      if (++cnt[a[i]] > mx || (cnt[a[i]] == mx && a[i] < ans))
        mx = cnt[a[i]], ans = a[i];
    }
    f[p][t] = ans;
  }
}
inline int calc(int l, int r, int x) { return upper_bound(s[x].begin(), s[x].end(), r) - lower_bound(s[x].begin(), s[x].end(), l); }
inline int solve(int l, int r)
{
  R mx = 0, ret = 0;
  if (pos[l] == pos[r])
  {
    memset(cnt, 0, sizeof(cnt));
    for (R i = l; i <= r; ++i)
      if (++cnt[a[i]] > mx || (cnt[a[i]] == mx && a[i] < ret))
        ret = a[i], mx = cnt[a[i]];
  }
  else
  {
    ret = f[pos[l] + 1][pos[r] - 1], mx = calc(l, r, ret);
    for (R i = l, lim = pos[l] * T; i <= lim; ++i)
    {
      R t = calc(l, r, a[i]);
      if (t > mx || (t == mx && a[i] < ret))
        ret = a[i], mx = t;
    }
    for (R i = (pos[r] - 1) * T + 1; i <= r; ++i)
    {
      R t = calc(l, r, a[i]);
      if (t > mx || (t == mx && a[i] < ret))
        ret = a[i], mx = t;
    }
  }
  return ret;
}
signed main()
{
#ifdef JACK
  freopen("NOIPAK++.in", "r", stdin);
  OUT;
#endif
  n = g(), m = g(); //,T=n/sqrt(n*log2(n));
  T = qpow(n, 1.0 / 4);
  for (R i = 1; i <= n; ++i)
    a[i] = g();
  memcpy(b, a, sizeof(a));
  sort(b + 1, b + n + 1);
  tot = unique(b + 1, b + n + 1) - b - 1;
  memcpy(vl, b, sizeof(int) * (tot + 1));
  for (R i = 1; i <= n; ++i)
    a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b, s[a[i]].pb(i);
  for (R i = 1; i <= n; ++i)
    pos[i] = (i - 1) / T + 1;
  for (R i = 1; i <= pos[n]; ++i)
    PRE(i);
  for (R i = 1, l, r; i <= m; ++i)
  {
    l = (g() + lst - 1) % n + 1, r = (g() + lst - 1) % n + 1;
    l > r ? swap(l, r) : (void)0;
    printf("%d\n", lst = vl[solve(l, r)]);
  }
}


```


------------
 
  
第三种按理说是复杂度最优秀的，但是跑的不是很快$qwq$。

但是还是恳请大佬们帮我看看为什么这么慢$qwq$

同第二种，预处理出所有可能的块组成的区间中（第i块到第j块）的答案$f[i][j]$,并且拿一个$vector$存每个数$vl$出现的位置$s[vl][1...n]$。

然后预处理$a[i]$是整个数列中的第几个$a[i]$,出第$1$到第$i$块中最靠后的$vl$是第几个$vl$，记为$d[i][vl]$，预处理出第$n$块到第$i$块中最靠前的$vl$是第几个$vl$,记为$h[i][vl]$。

对于左边散块中的$vl$，查一下$d[pos[r]-1][vl]$,和右边散块中是否有更靠后的$vl$(可以事先用一个数组存起来)，然后可以求出这个区间有多少个$vl$(每一个$vl$是第几个$vl$已经知道了),更新答案。

当块长取$\sqrt{n}$时，时间复杂度为$O(N\sqrt{N})$级(不知道推没推错)。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define ull unsigned long long
#define ll long long
#define R register int
#define pause (for (R i = 1; i <= 10000000000; ++i))
#define OUT freopen("out.out", "w", stdout);
using namespace std;
namespace Fread
{
static char B[1 << 15], *S = B, *D = B;
#define getchar() (S == D && (D = (S = B) + fread(B, 1, 1 << 15, stdin), S == D) ? EOF : *S++)
inline int g()
{
  R ret = 0, fix = 1;
  register char ch;
  while (!isdigit(ch = getchar()))
    fix = ch == '-' ? -1 : fix;
  do
    ret = ret * 10 + (ch ^ 48);
  while (isdigit(ch = getchar()));
  return ret * fix;
}
inline bool isempty(const char &ch) { return ch <= 36 || ch >= 127; }
inline void gs(char *s)
{
  register char ch;
  while (isempty(ch = getchar()))
    ;
  do
    *s++ = ch;
  while (!isempty(ch = getchar()));
}
} // namespace Fread
using Fread::g;
using Fread::gs;
const int N = 40010, M = 1000;
int n, m, T, tot, lst;
vector<int> s[N];
#define pb push_back
int f[M][M], cnt[N], P[N], pos[N], a[N], b[N], vl[N], h[M][N], d[M][N], c[M][M];
inline void PRE(int p)
{
  R ans = 0, mx = 0;
  memset(cnt, 0, sizeof(cnt));
  for (R t = p, lim = pos[n]; t <= lim; ++t)
  {
    for (R i = (t - 1) * T + 1, lim = min(n, t * T); i <= lim; ++i)
    {
      if (++cnt[a[i]] > mx || (cnt[a[i]] == mx && a[i] < ans))
        mx = cnt[a[i]], ans = a[i];
    }
    f[p][t] = ans, c[p][t] = mx;
  }
}
inline int solve(int l, int r)
{
  R mx = 0, ret = 0, p = pos[l] + 1, q = pos[r] - 1;
  if (pos[l] == pos[r])
  {
    memset(cnt, 0, sizeof(cnt));
    for (R i = l; i <= r; ++i)
      if (++cnt[a[i]] > mx || (cnt[a[i]] == mx && a[i] < ret))
        ret = a[i], mx = cnt[a[i]];
  }
  else
  {
    ret = f[p][q], mx = c[p][q];
    memset(cnt, 0x3f, sizeof(cnt));
    for (R i = l, L = pos[l] * T; i <= L; ++i)
      if (cnt[a[i]] == 0x3f3f3f3f)
        cnt[a[i]] = P[i];
    for (R i = q * T + 1; i <= r; ++i)
    {
      R tmp = P[i] + 1 - min(cnt[a[i]], h[p][a[i]]);
      if (tmp > mx || (tmp == mx && a[i] < ret))
        ret = a[i], mx = tmp;
      cnt[a[i]] = P[i];
    }
    for (R i = l, L = pos[l] * T; i <= L; ++i)
    {
      R tmp = max((cnt[a[i]] == 0x3f3f3f3f ? 0 : cnt[a[i]]), d[q][a[i]]) - P[i] + 1;
      if (tmp > mx || (tmp == mx && a[i] < ret))
        ret = a[i], mx = tmp;
    }
  }
  return ret;
}
signed main()
{
#ifdef JACK
  freopen("NOIPAK++.in", "r", stdin);
  OUT;
#endif
  n = g(), m = g();
  T = pow(n, 1 / 2.3); //好像更小一点更快（也不是越小越快）
  for (R i = 1; i <= n; ++i)
    a[i] = g();
  memcpy(b, a, sizeof(a));
  sort(b + 1, b + n + 1);
  tot = unique(b + 1, b + n + 1) - b - 1;
  memcpy(vl, b, sizeof(int) * (tot + 1));
  for (R i = 1; i <= n; ++i)
    a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b, s[a[i]].pb(i);
  for (R i = 1; i <= n; ++i)
    pos[i] = (i - 1) / T + 1;
  for (R i = 1; i <= n; ++i)
    P[i] = ++cnt[a[i]];
  memset(cnt, 0, sizeof(cnt));
  memset(h[pos[n] + 1], 0x3f, sizeof(h[pos[n] + 1]));
  for (R t = pos[n]; t; --t)
  {
    memcpy(h[t], h[t + 1], sizeof(h[t + 1]));
    for (R i = min(n, t * T); i > (t - 1) * T; --i)
      h[t][a[i]] = P[i];
  }
  for (R t = 1; t <= pos[n]; ++t)
  {
    memcpy(d[t], d[t - 1], sizeof(d[t - 1]));
    for (R i = (t - 1) * T + 1, L = t * T; i <= L; ++i)
      d[t][a[i]] = P[i];
  }
  for (R i = 1; i <= pos[n]; ++i)
    PRE(i);
  for (R i = 1, l, r; i <= m; ++i)
  {
    l = (g() + lst - 1) % n + 1, r = (g() + lst - 1) % n + 1;
    l > r ? swap(l, r) : (void)0;
    printf("%d\n", lst = vl[solve(l, r)]);
  }
}
```

2019.06.28

---

## 作者：laduiw (赞：9)

# 分块

算是比较简单的一道黑题，思路依然是分块，但是稍有差别
1. 把序列a分成t块，每段len=n/t
1. 对于询问[l,r]，设l处于tl块，r处于tr块，把[l,r]分为三段，左边不足的+中间整的+右边多的
1. 显然对于[l,r]中的众数只有两种可能 在中间整块中或是两边零散的数

	到这里都是一样的，但是其他题解貌似保存了所有以块边界为端点的数出现的次数，这样复杂度变为nt^2，这里提供另一种思路。
    
## Solution
    1. 我们只记录f[i][j]，表示i块到j块的众数（离散之后的值），假设你已经知道怎么nt求出
    2.对于整区间，算出这个众数以及他出现的次数,可以用下面的方法二分这个众数在这整段区间出现次数。
    3.对于零散的两边的数，暴力枚举每一个，但怎么知道它在[l,r]之间出现的次数呢？
    可以对每个离散后的数值建一个vector，记录它每次出现的位置，因为是一位一位加，每个vector内一定是单调递增的，然后假设你想知道k这个数在[l,r]出现的次数，就在k这个vector二分第一个>=l的数，最后一个<=r的数，这两个下标相减+1，就是出现次数。
    举个例子，a={2,3,3,2,4,2,1,1,2,4},你想求2在[3,10]出现次数，2的vector={1,4,6,9}，二分出第一个>=3的下标，得到2,最后一个<=10的下标，得到4,这样出现次数=4-2+1=3
    现在唯一问题就是怎么求f[i][j]
    可以枚举每一个块i，以这个块左端点为起点，向后延伸，记录sum[k]数组表k这种数出现次数，假设向右延伸到j,sum[c[j]]++,(c[j]是j离散后的值)，然后用maxx表示出现最多的数出现次数，ans记录出现最多的数，每次用sum[j]跟新maxx,ans跟着变，最后f[i][id[j]]=ans（这一步仔细体会一下，f[i][id[j]]会被赋值多次但最后一定是最优的）
    最后考虑复杂度求f数组nt，每次询问 len*log(n)所以总复杂度nt+n/t*log(n),所以t=sqrt(n*log(n))最优.
   ```
#include<bits/stdc++.h>
using namespace std;
const int maxn=40010,maxt=1000;
vector <int> ed[maxn];
int a[maxn],b[maxn],c[maxn],sum[maxn],f[maxt][maxt],id[maxn],p,len,t;
//c是离散后的数组，id是i这个点所在编号 ,t是块数,len是每块长度 
int n,m,l[maxt],r[maxt];
void prework(int x)//求f[i][j],当前在x这个块 
{
	int maxx=0,ans=0;
	memset(sum,0,sizeof(sum));//每次都要清空 
	for (int i=(x-1)*len+1;i<=n;i++)//从这个块左端点一位一位向后移动 
	{
		sum[c[i]]++;
		if (maxx<sum[c[i]] ||(maxx==sum[c[i]] && b[c[i]]<b[ans]))//如果编号小也可以 
		{
			ans=c[i];
			maxx=sum[c[i]];
		}
		f[x][id[i]]=ans;
	}
}

int chal(int x,int g,int h)//二分最左边下标 
{
	int ll=0,rr=ed[x].size()-1;
	while (rr>ll)
	{
		int mid=(ll+rr)>>1;
		if (ed[x][mid]>=g) rr=mid;
			else ll=mid+1;
	}
	return rr;
}

int chair(int x,int g,int h)//二分最右边下标 
{
	int ll=0,rr=ed[x].size()-1;
	while (rr>ll)
	{
		int mid=(ll+rr+1)>>1;//细节，不加1会死循环,如果l=4,r=5,mid=4,ed[x][mid]<=h,l=4就死循环了 
		if (ed[x][mid]<=h) ll=mid;
			else rr=mid-1;
	}
	return ll;
}

int askl(int al,int ar)
{
	int tl=id[al],tr=id[ar];
	if (tl+1>=tr-1) {//如果这段太小，也就是没有中间整段 
		int maxx=0,ans=0;
		for (int i=al;i<=ar;i++)
			{
				int pl=chal(c[i],al,ar),pr=chair(c[i],al,ar);
				if (maxx<pr-pl+1 || (maxx==pr-pl+1 && b[c[i]]<b[ans]))
				{
					ans=c[i];
					maxx=pr-pl+1;
				} 
			}
		return b[ans];
	}
	int ans=f[tl+1][tr-1];//中间整块的众数 
	int maxx=chair(ans,l[tl+1],r[tr-1])-chal(ans,l[tl+1],r[tr-1])+1;//ans的出现次数 
	for (int i=al;i<=r[tl];i++)//处理左边零散块 
	{
		int pl=chal(c[i],al,ar),pr=chair(c[i],al,ar);
		if (maxx<pr-pl+1 || (maxx==pr-pl+1 && b[c[i]]<b[ans]))
		{
			ans=c[i];
			maxx=pr-pl+1;
		} 
	}
	for (int i=l[tr];i<=ar;i++)//处理右边零散块 
	{
		int pl=chal(c[i],al,ar),pr=chair(c[i],al,ar);
		if (maxx<pr-pl+1 || (maxx==pr-pl+1 && b[c[i]]<b[ans]))
		{
			ans=c[i];
			maxx=pr-pl+1;
		} 
	}
	return b[ans];
}


int main()
{
	memset(a,0,sizeof(a));
	memset(f,0,sizeof(f));
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
	t=sqrt(n*log(n));
	len=n/t; 
	for (int i=1;i<=t;i++)
	{
		if (i*len>n) break;//块太大就不要 
		l[i]=(i-1)*len+1;
		r[i]=i*len;
	}
	if (r[t]<n) {
		t++;l[t]=r[t-1]+1;r[t]=n;//最后一段独立成块 
	}
	for (int i=1;i<=t;i++)
		for (int j=l[i];j<=r[i];j++)
			id[j]=i;
	sort(b+1,b+n+1);
	int q=unique(b+1,b+n+1)-(b+1);
	for (int i=1;i<=n;i++)
		c[i]=lower_bound(b+1,b+q+1,a[i])-b;//离散化，这里使用排序后第一次出现位置做离散值 
	for (int i=1;i<=n;i++)
		ed[c[i]].push_back(i);//每种数加下标 
	for (int i=1;i<=t;i++)
		prework(i);
	for (int i=1;i<=m;i++)
	{
		int l0,r0;
		scanf("%d %d",&l0,&r0);
		l0=(l0+p-1)%n+1;r0=(r0+p-1)%n+1;//强制在线 
		if (l0>r0) swap(l0,r0);
		p=askl(l0,r0);
		printf("%d\n",p);
	}
	return 0;
}
```
//细节还是蛮多的，祝诸君好运

---

## 作者：杨铠远 (赞：5)

# 恩 怎么说呢 暴力o2过了
感谢洛谷！
本蒟蒻离散化了一下，然后就A了（莫名其妙）
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
inline int read()//快读 正常操作（不写会T一个点哦） 
{
	int res=0;
	char ch;
	while(isspace(ch=getchar()));
	do res=res*10+ch-'0';
	while(isdigit(ch=getchar()));
	return res;
}
int n,m,l,r,x;
long long belong[40005];//记一下他原本的标号 
int b[40005];//离散化后将数放进b数组 
int tong[40005];//浅显易懂 
//int a[40005];
struct pp{
	int w,r;
}a[40005];
bool cmp(pp x,pp y)//手写cmp 
{
	return x.w<y.w;
}
int main()
{
	n=read();
	m=read();
	//cin>>n>>m;
	for(int i=1;i<=n;i++)
	a[i].w=read(),a[i].r=i;
	//cin>>a[i].w,a[i].r=i;
	sort(a+1,a+1+n,cmp);
	int now=1;
	int last=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i].w==last){//注意！题目要求输出最小的 
			belong[now]=a[i].w;
			a[i].w=now;
			b[a[i].r]=now;
		}
		else {
			now++;
			belong[now]=a[i].w;
			last=a[i].w;
			a[i].w=now;
			b[a[i].r]=now;
		}
	}
//	for(int i=1;i<=n;i++)
//	cout<<b[i]<<' ';
	while(m--)
	{
		//cin>>l>>r;
		l=read();
		r=read();
		l=(l+x-1)%n+1;
		r=(r+x-1)%n+1;
		if(l>r)
		{
			int t=r;
			r=l;
			l=t;
		}
		memset(tong,0,sizeof(tong));
		int maxx=0;
		int ans;
		for(int i=l;i<=r;i++)
		{
			tong[b[i]]++;//桶乃日常操作 
			if(tong[b[i]]>maxx){
				maxx=tong[b[i]];
				ans=belong[b[i]];
			}
			if(tong[b[i]]==maxx)
			{
				if(belong[b[i]]<ans)
				ans=belong[b[i]];
			}
		}
		x=ans;
		printf("%d\n",ans);
	//	cout<<ans<<endl;
	}
	return 0;//赢了！ 
}
```
。。。第一次交黑题题解。慌得一批


---

## 作者：pipiispig (赞：2)

#
本篇题解的分块思路并不需要二分



首先把区间分块， 预处理出每个块内每个数出现的次数， 以及区间众数，然后把所有连续的块的众数求出来，预处理是 O(NT^2),这里的T是把区间分成的块数，同时查询的时候，可以再进行一次朴素的扫描， 把块两边余处的地方经行处理即可复杂度为O(MN/T);

所以综上复杂度为O(NT^2 + MN/T), 通过一定的计算可的， 最有复杂度应该在NT^2 = MN/T时取得， 我们假设N和M是同数量级的， 即NT^2 = N^2/T, 可得当T =（N ^(1/ 3))时可以有最有的复杂度O(N^(5/3))!

同时我们在时间复杂度最优的情况下空间为O(NT^2), 即O(N^(5/3))， 可以通过本题！

同时推荐徐明宽神仙的论文《非常规大小分块算法初探》 QwQ

ps:那么问题来了，如果不算一下分块大小会怎么样？然而我们这样写挂了，不但炸了空间，导致要开一个数量级1e9的数组，要不就会RE + 各种TLE,所以不能只要分块题都随手开根号啊！可以自己算一下， 简单的话均值不等式就可以解决大部分的分块大小问题了!

```c
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 40005;
inline int read() {
    int x = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c<='9'){x = x * 10 + c - 48; c = getchar();}
    return x;
}
int sum[50][50][N], f[50][50], Cnt[50][50];
int K, n, m, bl[N], blo, a[N], b[N];
inline int query(int l, int r) {
    int ans = 0, cnt = 0x3f3f3f3f;
    if(l > r) swap(l, r); 
    int L = bl[l], R = bl[r];
    if(L == R) {
        L = R = 0;
        for(int i = l; i <= r; i ++) {
            sum[L][R][a[i]] ++;
            if(sum[L][R][a[i]] > ans || sum[L][R][a[i]] == ans && a[i] < cnt)
                cnt = a[i], ans = sum[L][R][a[i]]; 
        }
        for(int i = l; i <= r; i ++)
            sum[L][R][a[i]] --;
        return b[cnt];
    }
    else L = L + 1, R = R - 1;  
    ans = f[L][R], cnt = Cnt[L][R];
    for(int i = l; i <= min((L - 1) * blo, r); i ++) {
        sum[L][R][a[i]] ++;
        if(sum[L][R][a[i]] > ans || (sum[L][R][a[i]] == ans && a[i] < cnt)) {
            cnt = a[i], ans = sum[L][R][a[i]]; 
        }
    }  
    for(int i = R * blo + 1; i <= r; i ++) {
        sum[L][R][a[i]] ++;
        if(sum[L][R][a[i]] > ans || sum[L][R][a[i]] == ans && a[i] < cnt) {
            cnt = a[i], ans = sum[L][R][a[i]]; 
            }   
    }
    for(int i = R * blo + 1; i <= r; i ++)
            sum[L][R][a[i]] --;
    for(int i = l; i <= min((L - 1) * blo, r); i ++)
        sum[L][R][a[i]] --;
    return b[cnt];
}
int main() {
//  freopen("tjj.in", "r" ,stdin); 
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read(), b[i] = a[i];
    sort(b + 1, b + n + 1);
    K = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; i ++)
        a[i] = lower_bound(b + 1, b + K + 1, a[i]) - b;
    blo = pow(n * 1.0, 1.0/ 3);
    if(blo!=0) blo = n/blo;
    else blo = 1;
    for(int i = 1; i <= n; i ++)
        bl[i] = (i - 1) / blo  + 1; 
    for(int i = 1; i <= bl[n]; i ++) {
        for(int j = i; j <= bl[n]; j ++) {
            for(int k = (i - 1) * blo + 1; k <= min(blo * j, n); k ++)
                sum[i][j][a[k]] ++;
            for(int k = 1; k <=  K; k ++)
                if(sum[i][j][k] > f[i][j])
                    f[i][j] = sum[i][j][k], Cnt[i][j] = k;  
        }
    }
    int ans = 0;
    for(int i = 1; i <= m; i ++) {
        int x = read(), y = read();
        ans = query((x + ans - 1) % n + 1, (y + ans - 1) % n + 1);
        printf("%d\n", ans);
    }
}
```

---

## 作者：dfydada⚡⚡⚡ (赞：2)

在乡下的小路旁种着许多蒲公英，而我们的问题正是与这些蒲公英有关。

为了简化起见，我们把所有的蒲公英看成一个长度为 n 的序列a1,a2,…,an,其中ai为一个正整数，表示第 i 棵蒲公英的种类编号。

而每次询问一个区间 [l,r] ，你需要回答区间里出现次数最多的是哪种蒲公英，如果有若干种蒲公英出现次数相同，则输出种类编号最小的那个。

输入格式
第一行两个整数n，m，表示有 n 株蒲公英，m 次询问。

接下来一行 n 个空格隔开的整数ai,表示蒲公英的种类。

再接下来 m 行每行两个整数l0,r0，我们令上次询问的结果为 x（如果这是第一次询问，则 x=0）。

令l=(l0+x-1) mod n+1,r=(r0+x-1) mod n+1,如果l>r,则交换l，r。

最终的询问区间为[l,r]。

输出格式
输出 m 行。

每行一个整数，表示每次询问的结果。

数据范围
1≤n≤40000,
1≤m≤50000,
1≤ai≤109


----------

### 算法1
##### (分块+二分) O(n（√mlogn）)

预处理出所有以"段边界"为端点的区间[L,R]中每个数出现的次数,以及区间众数.这样的区间共有O(T²)个,并且保存每个数出现的次数需要长度为O(N)的数组(记为cntL,R).

对于每个询问中的[l,L)与(R,r]可以通过朴素扫描,在数组cntL,R的基础上累加次数,从而更新答案.回答询问后再进行一次朴素扫描,从cntL,R中减少次数,把数组复原.

这个算法的时间为O(NT²+MN/T),空间为O(NT²).不妨设N,M为相同数量级,通过方程NT²=MN/T,可解得T≈sqrt(sqrt(N)),此时整个算法的复杂度在O(pow(N,5/3))级别.


#### C++ 代码
```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)//O2优化
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1e5+10;
ll n,m,anst;
ll a[N],b[N],f[N],tot;
ll d[1000][1000];
ll ct[N];
vector<ll> g[N];
void asd()
{
    anst=max(1,(int)(n/sqrt(m*log2(n))));
    for(int i=1;i<=n;i++)
    {
    	b[i]=(i-1)/anst+1;
	}
}
ll bll(ll l,ll r,ll val)
{
    ll t=upper_bound(g[val].begin(),g[val].end(),r)-lower_bound(g[val].begin(),g[val].end(),l);
    return t;
}
void qwe(int x)//预处理从块x到其他块的众数
{
    memset(ct,0,sizeof(ct));
    int ansy=-1,ans=0;
    for(int i=(x-1)*anst+1;i<=n;i++)
    {
        ct[a[i]]++;
        if(ct[a[i]]>ansy||(ct[a[i]]==ansy&&a[i]<ans))
        {
            ans=a[i];
            ansy=ct[a[i]];
        }
        d[x][b[i]]=ans;
    }
}
ll dsa(ll l,ll r)
{
    ll ans=d[b[l]+1][b[r]-1];
    ll ansy=bll(l,r,ans);
    ll ant=0;
    ll minn=min(r,b[l]*anst);
    for(int i=l;i<=minn;i++)
    {
        ant=bll(l,r,a[i]);
        if(ant>ansy||(ant==ansy&&f[ans]>f[a[i]]))
        {
            ansy=ant;
            ans=a[i];
        }
    }
    if(b[l]!=b[r])
    {
        for(int i=(b[r]-1)*anst+1;i<=r;i++)
        {
            ant=bll(l,r,a[i]);
            if(ant>ansy||(ant==ansy&&ans>a[i]))
            {
                ansy=ant;
                ans=a[i];
            }
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        f[i]=a[i];
    }
    asd();
    sort(f+1,f+n+1);
    int N=unique(f+1,f+n+1)-f-1;
    for(int i=1;i<=n;i++)
    {
        a[i]=lower_bound(f+1,f+N+1,a[i])-f;
        g[a[i]].push_back(i);
    }
    int ans=0;
    for(int i=1;i<=b[n];i++)
    {
    	qwe(i);
	}
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l=(l+ans-1)%n+1;
        r=(r+ans-1)%n+1;
        if(l>r)
        {
        	swap(l,r);
		}
        ans=f[dsa(l,r)];
        printf("%d\n",ans);
    }
    return 0;
}

```


----------

### 算法2
##### (分块+后缀和) O(n（√n）)

在预处理时,只保存所有以"段边界"为端点的区间[L,R]的众数.另外,对每个数值建立一个STLvertor,按顺序保存该数值在序列a中每次出现的位置.

对于每个询问,扫描[l,L)与(R,r]中的每个数x,在对应的vertor里二分查找即可得到x在[l,r]中出现的次数,从而更新答案.

例如序列a={1,4,2,3,2,4,3,2,1,4},数值1出现的位置为{1,9},数值2出现的位置为{3,5,8},数值3出现的位置为{4,7},数值4出现的位置俄日{2,6,10}.假设l=2,r=8,若要求是数值2在序列a的区间[l,r]中出现多少次,则应该在{3,5,8}中二分
查找第一个≥l的数,得到3(下标为0);二分查找最后一个≤r的数,得到8(下标为2).把两个下标相减再加1,得到答案:3次.

这个算法的时间为O(NT+MN/T*logN),空间为O(T²).应取T=sqrt(NlogN),此时整个算法的复杂度在O(Nsqrt(NlogN))级别.


这些都是从书上看到的，我只是搬运工

---

## 作者：dblark (赞：2)

犹豫了很久还是决定来写一篇Pascal题解。

经典的分块入门题。

简单介绍一下分块：

把数据分成一些块，然后预处理。

维护或查询数据时，中间连续的几个块一起操作，边角暴力。

小于两个块的话就直接暴力了。

一般每个块的大小为$\sqrt{n}$。

当题目强制在线的话用分块，离线就可以用莫队了。

先看题目，$1\le a_i\le 10^9$。肯定要离散化。

然后就是预处理。这是分块里面很重要的一步。这个想出来以后做题就不难了。

求区间众数需要每个数出现的数量。考虑用前缀和对每一个块维护。

我们还需要维护连续的几个块的众数。

查询的时候直接枚举边角的数就好了（边角暴力）。

详细还是见代码吧：

```
{P4168}
var
  a,d,p,sum,temp:array[1..40000]of longint;//a是原始数组（后来被离散化了），p是离散化前原始的数值，d和temp用来离散化（具体看主程序），sum是查询过程中统计数量的
  s:array[0..200,1..40000]of longint;//预处理的前缀和
  m:array[1..200,1..200]of longint;//区间众数
  n,q,i,x,l,r,num,size,last:longint;
function min(x,y:longint):longint;//不解释
begin
  if x<y then
    exit(x)
  else
    exit(y);
end;
procedure swap(var x,y:longint);//不解释
var
  t:longint;
begin
  t:=x;
  x:=y;
  y:=t;
end;
procedure quicksort(l,r:longint);//不解释
var
  i,j,m,t:longint;
begin
  i:=l;
  j:=r;
  m:=a[(l+r) div 2];
  repeat
    while a[i]<m do
      inc(i);
    while a[j]>m do
      dec(j);
    if i<=j then
    begin
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
      t:=d[i];
      d[i]:=d[j];
      d[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then
    quicksort(l,j);
  if i<r then
    quicksort(i,r);
end;
procedure init;                //初始化
var
  i,j,k:longint;
begin
  for i:=1 to num do
  begin
    for j:=1 to x do
      s[i,j]:=s[i-1,j];
    for j:=(i-1)*size+1 to min(n,i*size) do//计算前缀和
      inc(s[i,a[j]]);
    for j:=1 to i do           //计算从第j个块到第i个块的区间众数
    begin
      m[j,i]:=1;
      for k:=2 to x do         //暴力枚举
        if s[i,k]-s[j-1,k]>s[i,m[j,i]]-s[j-1,m[j,i]] then
          m[j,i]:=k;
    end;
  end;
end;
function query(l,r:longint):longint;//查询
var
  i,tl,tr:longint;
begin
  tl:=(l-1) div size+1;        //l所在的块
  tr:=(r-1) div size+1;        //r所在的块
  if tr-tl<=1 then             //小于2个块直接暴力
  begin
    for i:=l to r do
      sum[a[i]]:=0;
    for i:=l to r do           //把所有数的数量都统计出来
      inc(sum[a[i]]);
    query:=a[l];
    for i:=l+1 to r do         //暴力枚举
      if (sum[a[i]]>sum[query]) or (sum[a[i]]=sum[query]) and (a[i]<query) then
        query:=a[i];
  end
  else
  begin
    sum[m[tl+1,tr-1]]:=s[tr-1,m[tl+1,tr-1]]-s[tl,m[tl+1,tr-1]];//先把区间众数的数量统计好
    for i:=l to min(n,tl*size) do//统计每个边角的数在块内的数量
      sum[a[i]]:=s[tr-1,a[i]]-s[tl,a[i]];
    for i:=(tr-1)*size+1 to r do
      sum[a[i]]:=s[tr-1,a[i]]-s[tl,a[i]];
    for i:=l to min(n,tl*size) do//统计边角的数量
      inc(sum[a[i]]);
    for i:=(tr-1)*size+1 to r do
      inc(sum[a[i]]);
    query:=m[tl+1,tr-1];
    for i:=l to min(n,tl*size) do//暴力枚举
      if (sum[a[i]]>sum[query]) or (sum[a[i]]=sum[query]) and (a[i]<query) then
        query:=a[i];
    for i:=(tr-1)*size+1 to r do
      if (sum[a[i]]>sum[query]) or (sum[a[i]]=sum[query]) and (a[i]<query) then
        query:=a[i];
  end;
  query:=p[query];             //注意离散化过，要把答案转回去
end;
begin
  read(n,q);
  size:=trunc(sqrt(n));        //块的大小
  num:=(n-1) div size+1;       //一共有几块
  for i:=1 to n do
  begin
    read(a[i]);                //读入
    d[i]:=i;                   //把序号记下来，方便离散化
  end;
  quicksort(1,n);              //排序
  x:=a[1];                     //写的极丑的离散化
  a[1]:=1;
  p[1]:=x;
  for i:=2 to n do
    if a[i]=x then
      a[i]:=a[i-1]
    else
    begin
      x:=a[i];
      a[i]:=a[i-1]+1;
      p[a[i]]:=x;
    end;
  x:=a[n];
  temp:=a;
  for i:=1 to n do
    a[d[i]]:=temp[i];
  init;
  last:=0;
  for i:=1 to q do             //查询部分
  begin
    read(l,r);
    l:=(l+last-1) mod n+1;     //强制在线
    r:=(r+last-1) mod n+1;
    if l>r then
      swap(l,r);
    last:=query(l,r);
    writeln(last);
  end;
end.
```

---

## 作者：小塘空明 (赞：2)

将数组按照(n^(1/3))进行分块，预处理出从块i到块j中每个数出现的个数，最大的出现次数和对应的数。

对于每个询问l，r，答案只可能来自于块[L,R]中的众数，或其余范围内的数。因为不是块[L,R]中的众数，或其余范围内的数的数，很明显没有块[L,R]中的众数优。

对于每个询问l，r，先通过朴素扫描，在[L,R]的基础上累计次数并更新答案，回答询问后再朴素扫描复原数组。

时间复杂度O(n^(5/3))

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
const int u=40010;
int c[40][40][u],f[40][40],d[40][40],a[u],b[u],fa[u],fb[u],st[40],ed[40];
int n,m,t,l,tot,i,j,k,x,y,ans,L,R,cnt,num;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline void prework(){
	t=(int)pow(n*1.0,1.0/3.0);
	if(t) l=n/t;
	for(i=1;i<=t;i++) st[i]=(i-1)*l+1,ed[i]=i*l;
	if(ed[t]<n) st[t+1]=ed[t]+1,ed[++t]=n;
	memcpy(fa,a,sizeof(a));
	sort(fa+1,fa+1+n);
	for(i=1;i<=n;i++) if(i==1||fa[i]!=fa[i-1]) fb[++tot]=fa[i];
	for(i=1;i<=n;i++) b[i]=lower_bound(fb+1,fb+1+tot,a[i])-fb;
	for(i=1;i<=t;i++){
		for(j=i;j<=t;j++){
			for(k=st[i];k<=ed[j];k++) c[i][j][b[k]]++;
			for(k=1;k<=tot;k++){
				if(f[i][j]<c[i][j][k]||f[i][j]==c[i][j][k]&&d[i][j]>k){
					f[i][j]=c[i][j][k];d[i][j]=k;
				}
			}
		}
	}
}
inline void update(int i){
	c[L][R][b[i]]++;
	if(c[L][R][b[i]]>cnt||c[L][R][b[i]]==cnt&&b[i]<num) cnt=c[L][R][b[i]],num=b[i];
}
inline int solve(int x,int y){
	int i,l,r;
	if(x>y) swap(x,y);
	for(i=1;i<=t;i++) if(x<=ed[i]){l=i;break;}
	for(i=t;i>=1;i--) if(y>=st[i]){r=i;break;}
	if(l+1<=r-1){L=l+1;R=r-1;}
	else L=R=0;
	cnt=f[L][R],num=d[L][R];
	if(l==r){
		for(i=x;i<=y;i++) update(i);
		for(i=x;i<=y;i++) c[L][R][b[i]]--;
	}
	else{
		for(i=x;i<=ed[l];i++) update(i);
		for(i=st[r];i<=y;i++) update(i);
		for(i=x;i<=ed[l];i++) c[L][R][b[i]]--;
		for(i=st[r];i<=y;i++) c[L][R][b[i]]--;
	}
	return fb[num];
}
int main(){
	n=read();m=read();
	for(i=1;i<=n;i++) a[i]=read();
	prework();
	for(i=1;i<=m;i++){
		x=read();y=read();
		ans=solve((x+ans-1)%n+1,(y+ans-1)%n+1);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：psk011102 (赞：2)

这是一道明显的分块题。

先将颜色离散化~~（毕竟颜色数字有1e9）~~再分成$\sqrt{n}$个块，记录每个块的众数，可以把每次询问拆成k个整块与不完整块的众数。于是每次最多需要比较$2\sqrt{n}+1$个元素。

有几个小的注意事项：

1.这是强制在线的！！！

2.块不一定是标准的$\sqrt{n}$块！！！~~（我不会告诉你这样我还拿了85分的）~~建议块数记一个变量


代码如下，缩进较丑见谅~~（我是不会说我因为缩进有些地方写错了没发现然后wa了几次的）~~

```
#include <bits/stdc++.h>
#define F(i, l, r) for(int i = (l), _end_ = (int)(r); i <= _end_; ++i)
#define f(i, r, l) for(int i = (r), _end_ = (int)(l); i >= _end_; --i)
#define Set(a, v) memset(a, v, sizeof(a))
using namespace std;

bool chkmin(int &a, int b) {return b < a ? a = b, 1 : 0;}
bool chkmax(int &a, int b) {return b > a ? a = b, 1 : 0;}

inline long long  read() {
 long long x = 0, fh = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar() ) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar() ) x = (x<<1) + (x<<3) + (ch ^ '0');
    return x * fh;
}
int sum[230][230];
int mp[50005],mp2[50005];
int h[50005],t[50005];
int n,m;
int cnt;
int k;
int ksum;
int from[50005];
int num[50005];
int col[230][50005];
int main () {
#ifndef ONLINE_JUDGE
    freopen("fk.in","r",stdin);
    freopen("fk.out","w",stdout);
#endif
    n=read();
    m=read();
    F(i,1,n){
       mp[i]=mp2[i]=read();
    }
    cnt=n;
    sort(mp2+1,mp2+cnt+1);
    cnt=unique(mp2+1,mp2+cnt+1)-mp2-1;
    F(i,1,n)mp[i]=lower_bound(mp2+1,mp2+cnt+1,mp[i])-mp2;
    k=sqrt(n);
    F(i,1,n){
       if(i%k==1)h[++ksum]=i;
       if(i%k==0||i==n)t[ksum]=i;
       from[i]=ksum;
    }
    F(i,1,ksum){
       F(j,i,ksum){
         sum[i][j]=sum[i][j-1];
         F(l,h[j],t[j]){
            ++num[mp[l]];
            if((num[mp[l]]>num[sum[i][j]])||(num[mp[l]]==num[sum[i][j]]&&mp[l]<sum[i][j]))sum[i][j]=mp[l];

         }
       }
       F(j,1,n)col[i][j]=col[i-1][j];
       F(j,h[i],t[i])++col[i][mp[j]];
       Set(num,0);
    }
    int lstans=0;
    F(i,1,m){
       int l=read(),r=read();
       l=(l+lstans-1)%n+1,r=(r+lstans-1)%n+1;
       if(l>r)swap(l,r);
       lstans=0;
       if(from[l]+1>=from[r]){
           F(i,l,r){
              ++num[mp[i]];
              if(num[mp[i]]>num[lstans]||(num[mp[i]]==num[lstans]&&mp[i]<lstans))lstans=mp[i];
           }
           F(i,l,r)num[mp[i]]--;
       }
       else{
           lstans=sum[from[l]+1][from[r]-1];
           F(i,l,t[from[l]]){
              ++num[mp[i]];
              int lans=num[mp[i]]+col[from[r]-1][mp[i]]-col[from[l]][mp[i]],rans=num[lstans]+col[from[r]-1][lstans]-col[from[l]][lstans];
               if(lans>rans||(lans==rans&&mp[i]<lstans))lstans=mp[i];
           }
           F(i,h[from[r]],r){
              ++num[mp[i]];
              int lans=num[mp[i]]+col[from[r]-1][mp[i]]-col[from[l]][mp[i]],rans=num[lstans]+col[from[r]-1][lstans]-col[from[l]][lstans];
               if(lans>rans||(lans==rans&&mp[i]<lstans))lstans=mp[i];
           }
           F(i,l,t[from[l]])--num[mp[i]];
           F(i,h[from[r]],r)--num[mp[i]];
       }
       lstans=mp2[lstans];
       printf("%d\n",lstans);
    }
    return 0;
}
```

---

## 作者：Edward_Elric (赞：1)

UPD ON：2019/7/17 发现写了个假算法
## 思路
同[hzwer分块9题](http://hzwer.com/8053.html)。

我们知道，众数一定在整块和散块之间。分块的思想：**大段维护，小段朴素**于是这个思路便很好想了

大段：预处理整块之间的众数$f[i][j]$来表示，
$O(n\sqrt{n})$ 预处理。

小段：二分暴力查询

但这样的复杂度是$O(n\sqrt{n} logn)$的，所以我们考虑如何去掉这个$logn$

------------

于是考虑两个数组：

$c[i][x]$表示前$i$块(包含$i$)$x$的总数

$s[i][j][x]$表示第$i$块前$j$个数(包含$j$)$x$的总数

这两个数组都是可以在$O(n\sqrt[2]{n})$内处理的。至于查询操作不再赘述。类似于前缀和的$O(1)$

当然还少不了离散化

## 代码
不加优化，需要开O2才能跑过

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn=50000+100,md=200+100;
int f[md][md];
int L[md],R[md],pos[maxn];
int a[maxn],cnt[maxn];
int val[maxn];
map<int,int>ma;
vector<int>v[maxn];
int n,m,id=0,x=0;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<='0'||ch>='9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
} 
void cal(int p){
    memset(cnt,0,sizeof(cnt));
    int ans=0;
    for(int i=L[p];i<=n;i++){
        cnt[a[i]]++;
        int q=pos[i];
        if(cnt[a[i]]>cnt[ans]||(cnt[a[i]]==cnt[ans]&&val[a[i]]<val[ans]))
        ans=a[i];
        f[p][q]=ans; 
    }
}
void pre(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(!ma[a[i]]){
            ma[a[i]]=++id;
            val[id]=a[i];
        }
        a[i]=ma[a[i]];
        v[a[i]].push_back(i);
    }
    int blo=sqrt(n);
    for(int i=1;i<=blo;i++)
    L[i]=(i-1)*blo+1,R[i]=i*blo;
    if(R[blo]<n)blo++,L[blo]=R[blo-1]+1,R[blo]=n;
    for(int i=1;i<=blo;i++)
      for(int j=L[i];j<=R[i];j++)
      pos[j]=i;
    for(int i=1;i<=blo;i++)cal(i);
}
int query(int x,int l,int r){
    return upper_bound(v[x].begin(),v[x].end(),r)-lower_bound(v[x].begin(),v[x].end(),l);
}
int query(int l,int r){
    int p=pos[l],q=pos[r];
    int ans=0,mt=0;
    if(p==q){
        for(int i=l;i<=r;i++){
            int t=query(a[i],l,r);
            if(t>mt||(t==mt&&val[a[i]]<val[ans]))
            ans=a[i],mt=t;
        }
    } 
    else{
        ans=f[p+1][q-1];
        mt=query(ans,l,r);
        for(int i=l;i<=R[p];i++){
            int t=query(a[i],l,r);
            if(t>mt||(t==mt&&val[a[i]]<val[ans]))
            ans=a[i],mt=t;
        }
        for(int i=L[q];i<=r;i++){
            int t=query(a[i],l,r);
            if(t>mt||(t==mt&&val[a[i]]<val[ans]))
            ans=a[i],mt=t;
        }
    }
    return val[ans];
}
void work(){
    for(int i=1;i<=m;i++){
      	int l=(read()+x-1)%n+1,r=(read()+x-1)%n+1;
      	if(l>r)swap(l,r);
        x=query(l,r);
        printf("%d\n",x);
    }
}
int main(){
    pre();
    work();
    return 0;
} 
```
------------
优化，写的并不是很优美。常数也很大，谅解。。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5,md=320+5;
int f[md][md],c[md][maxn],s[md][md][md];
int L[md],R[md],pos[maxn];
int a[maxn],cnt[maxn];
int val[maxn];
int vis[md][maxn];
map<int,int>mp;
int n,m,id=0,x=0;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
} 
void cal(int p){
    memset(cnt,0,sizeof(cnt));
    int ans=0;
    for(int i=L[p];i<=n;i++){
        cnt[a[i]]++;
        int q=pos[i];
        if(cnt[a[i]]>cnt[ans]||(cnt[a[i]]==cnt[ans]&&val[a[i]]<val[ans]))
        ans=a[i];
        f[p][q]=ans; 
    }//预处理f 
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=id;i++)
    c[p][i]=c[p-1][i]; 
    for(int i=L[p];i<=R[p];i++)
    c[p][a[i]]++;//预处理c
    int tot=0;
	for(int j=1,i=L[p];i<=R[p];i++,j++){
		if(!vis[p][a[i]])vis[p][a[i]]=++tot; 
		cnt[vis[p][a[i]]]++;
		for(int k=1;k<=tot;k++)
		s[p][j][k]=cnt[k];
	}//二次离散处理s 
} 
void pre(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(!mp[a[i]]){
            mp[a[i]]=++id;
            val[id]=a[i];
        }
        a[i]=mp[a[i]];
    }
    int blo=sqrt(n);
    for(int i=1;i<=blo;i++)
    L[i]=(i-1)*blo+1,R[i]=i*blo;
    if(R[blo]<n)blo++,L[blo]=R[blo-1]+1,R[blo]=n;
    for(int i=1;i<=blo;i++)
      for(int j=L[i];j<=R[i];j++)
      pos[j]=i;
    for(int i=1;i<=blo;i++)cal(i);
}
int query(int l,int r){
    int p=pos[l],q=pos[r];
    int ans=0,mt=0;
    if(p==q){
        for(int i=l;i<=r;i++){
            int t=s[p][r-L[p]+1][vis[p][a[i]]]-s[p][l-L[p]][vis[p][a[i]]];
            if(t>mt||(t==mt&&val[a[i]]<val[ans]))
            ans=a[i],mt=t;
        }
    } 
    else{
        ans=f[p+1][q-1];
        mt=c[q-1][ans]-c[p][ans];
        for(int i=l;i<=R[p];i++){
            int t=c[q-1][a[i]]-c[p-1][a[i]]-s[p][l-L[p]][vis[p][a[i]]]+s[q][r-L[q]+1][vis[q][a[i]]];
            if(t>mt||(t==mt&&val[a[i]]<val[ans]))
            ans=a[i],mt=t;
        }
        for(int i=L[q];i<=r;i++){
            int t=c[q-1][a[i]]-c[p-1][a[i]]-s[p][l-L[p]][vis[p][a[i]]]+s[q][r-L[q]+1][vis[q][a[i]]];;
            if(t>mt||(t==mt&&val[a[i]]<val[ans]))
            ans=a[i],mt=t;
        }
    }
    return val[ans];
}
void work(){
    for(int i=1;i<=m;i++){;
      	int l=(read()+x-1)%n+1,r=(read()+x-1)%n+1;
      	if(l>r)swap(l,r);
      	x=query(l,r);
        printf("%d\n",x);
    }
}
int main(){
    pre();
    work();
    return 0;
} 
```



---

## 作者：GoldenPotato137 (赞：1)

[戳我来获得更的阅读体验w](https://www.cnblogs.com/GoldenPotato/p/10351638.html)

---
# Solution
题目要求求出区间众数，强制在线。

区间众数是一个比较尴尬的问题，我们无法用区间数据结构来处理这个问题，因为我们没法很好的合并区间众数的答案。

既然区间数据结构解决不了这个问题，我们可以考虑一下使用基于分块的算法，例如莫队。
这题用莫队非常好处理，不幸的是，这题要求强制在线。
因此我们考虑使用分块算法。

分块算法的核心在于把一整个块的信息压缩起来以便快速处理。
我们要查询一段区间的众数，我们可以考虑这样搞：**对于这个区间内连续的块，我们先快速地查询这个连续的块中的众数，然后我们暴力处理这个区间剩余的左右两个零散的点，开一个桶暴力维护这些零散的点每个颜色出现的次数，每新加入一个点，就与整个区间的答案比较一下，如果更优就替换答案。**

为了实现上面那个思路，我们必须要实现两点：**快速求出一段连续块的每个颜色出现的次数，快速求出一段连续块的众数。**
对于第一个问题，解决方法很简单，我们暴力做**前缀和**即可，复杂度$O(n*\sqrt n)$
```cpp
for(int i=1;i<=cnt_block;i++)
	{
		for(int j=1;j<=to;j++)
			pre[i][j]=pre[i-1][j];
		for(int j=(i-1)*size;j<i*size;j++)
			pre[i][a[j]]++;
	}
```
对于第二个问题，我们可以考虑把每段连续块的答案预处理出来。
具体做法是：我们枚举每个块，然后我们暴力往后扫描，每扫到一个块的结尾就记录答案。
```cpp
cnt[0]=-0x3f3f3f3f;
	for(int i=1;i<=cnt_block;i++)
	{
		int t_ans=0;
		for(int j=(i-1)*size;j<=n;j++)
		{
			cnt[a[j]]++;
			if(cnt[a[j]]>cnt[t_ans] or (cnt[a[j]]==cnt[t_ans] and a[j]<t_ans)) 
				t_ans=a[j];
			if((j+1)%size==0)
				f[i][j/size+1]=t_ans;
		}
		memset(cnt,0,sizeof cnt);
		cnt[0]=-0x3f3f3f3f;
	}
```


就酱，这题就被我们搞定啦~

复杂度$O(n\sqrt n)$

---
# Code
**本题实现上有较多细节要处理，请小心**
```cpp
//Luogu P4168 [Violet]蒲公英
//Feb,4th,2019
//分块套路题
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
long long read()
{
	long long x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=40000+1000;
const int M=200+10;
int n,m,a[N],b[N],t_n,mmap[N];//离散值->原值
int f[M][M],pre[M][N];//f[i][j]:块i到j的众数，pre[i][j]：到i块为止，颜色j的出现次数前缀和
int cnt[N];//零时记录每个元素出现次数
int main()
{
	//freopen("testdata.in","r",stdin);
	//freopen("4168.out","w",stdout);
	
	t_n=n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=a[i];
	
	sort(b+1,b+1+n);
	int to=0,last=0;
	for(int i=1;i<=n;i++)
		if(b[i]!=last)
			last=b[i],b[++to]=b[i];
	for(int i=1;i<=n;i++)
	{
		int t=lower_bound(b+1,b+1+to,a[i])-b;
		mmap[t]=a[i],a[i]=t;
	}
	int size=int(sqrt(n)),cnt_block=n/size+1;
	n=cnt_block*size-1;
	for(int i=1;i<=cnt_block;i++)
	{
		for(int j=1;j<=to;j++)
			pre[i][j]=pre[i-1][j];
		for(int j=(i-1)*size;j<i*size;j++)
			pre[i][a[j]]++;
	}
	cnt[0]=-0x3f3f3f3f;
	for(int i=1;i<=cnt_block;i++)
	{
		int t_ans=0;
		for(int j=(i-1)*size;j<=n;j++)
		{
			cnt[a[j]]++;
			if(cnt[a[j]]>cnt[t_ans] or (cnt[a[j]]==cnt[t_ans] and a[j]<t_ans)) 
				t_ans=a[j];
			if((j+1)%size==0)
				f[i][j/size+1]=t_ans;
		}
		memset(cnt,0,sizeof cnt);
		cnt[0]=-0x3f3f3f3f;
	}
	
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int l=read(),r=read();
		l=(l+ans-1)%t_n+1,r=(r+ans-1)%t_n+1;
		if(l>r) swap(l,r);
		
		int bl=l/size+1,br=r/size+1;
		ans=0;
		if(bl+1<=br-1)
			ans=f[bl+1][br-1];
		for(int j=l;j<bl*size and j<=r;j++)
		{
			cnt[a[j]]++;
			int tmp1=cnt[a[j]],tmp2=cnt[ans];
			if(bl+1<=br-1)
				tmp1+=pre[br-1][a[j]]-pre[bl][a[j]],
				tmp2+=pre[br-1][ans]-pre[bl][ans];
			if(tmp1>tmp2 or (tmp1==tmp2 and a[j]<ans)) 
				ans=a[j];
		}
		if(bl!=br)
			for(int j=(br-1)*size;j<=r;j++)
			{
				cnt[a[j]]++;
				int tmp1=cnt[a[j]],tmp2=cnt[ans];
				if(bl+1<=br-1)
					tmp1+=pre[br-1][a[j]]-pre[bl][a[j]],
					tmp2+=pre[br-1][ans]-pre[bl][ans];
				if(tmp1>tmp2 or (tmp1==tmp2 and a[j]<ans)) 
					ans=a[j];
			}
			
		for(int j=l;j<bl*size and j<=r;j++)
			cnt[a[j]]--;
		if(bl!=br)
			for(int j=(br-1)*size;j<=r;j++)
				cnt[a[j]]--;
		cnt[0]=-0x3f3f3f3f;
		
		ans=mmap[ans];
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Wow_Goodjob (赞：1)

###### ~~Violet 逗我吗？？~~

## 啊,分块大法好

#### 暴力出奇迹~~(poi~~

让我们来看看题目

啊，有好多数$a$($a\le10^{9}$),让我们求出每次求$l-r$,之间的众数，强制在线呦！！

学过分块的***dalao***们应该都一眼秒掉了这道题吧(实在是太裸了)

那我们就来考虑一下怎么分块

首先我们的第一个思路就是分块之后预处理出第$i-j$块之间的众数

然后对于每一个询问中$l-r$的整块,直接读取,再便利非整块上的元素,用他们更新答案便是我们所要求的答案了

为什么这么做呢？？因为有一个比较显然的结论

#### 敲黑板

对于每一个询问,如果某个数(即本题中某种蒲公英),他没有出现在零碎的块中,他一定不是答案

##### 证明

我们假设存在$a_{i}$不存在与零碎的块中,且不是$l-r$之间的众数,那么他对于每一次询问的个数即是$l-r$整块内的个数,但因为他不是$l-r$之间的众数,所以一定没有$l-r$之间的众数优,所以可能更新答案的数一定存在于零碎的块中出现过的数里面,因为他们的数量相对于$l-r$之间他们相应的数量是可以增加的,所以他们有可能更新答案

##### 证毕

#### 敲黑板结束

所以我们的问题就转化到了如何预处理出块与块之间的众数了

**直接开一个数组存??**听上去是一个好主意

我们考虑开一个数组**mode[l][r][k]**表示第$l-r$之间$k$出现了几次

但是我们看看$a_{i}\le10^{9}$,只开一个**mode[k]**就炸空间了,更别说还要开两维了,但是我们又看看n(即最多可能出现的蒲公英的种数)$n\le40000$,顿时计上心头**离散化是个好东西**于是我们考虑


**mode[l][r][k]**表示第$l-r$块中离散化之后标号为k的数有几个

**mode[l][r][0]**表示$l-r$块之间众数的数量

**mode_id[l][r]**表示$l-r$块之间众数的标号

### 离散化

因为本人太懒了,~~其实是太菜了~~离散化一般用**map**写,虽然有点慢,但是效果还是不错的

**CODE**

其中$a_{i}$表示***i***位置上的蒲公英的种类,$b_{i}$表示离散化后编号为***i***的元素原来的值
```cpp
map<int,int>Mymap;
void Discretization_Method(){
    for(map<int,int>::iteratorit=Mymap.begin();it!=Mymap.end();it++)
        it->second=++Rin;//返回Mymap的迭代器并把它的第二维的值赋值为它离散化之后的的编号
    for(int i=1;i<=n;++i)
        b[Mymap[a[i]]]=a[i],a[i]=Mymap[a[i]];
}//离散化大法好
```

四八四灰常地简单

然后我们就解决了数据范围过大的问题,现在正式来考虑如何分块解决这道题目,先考虑块长的问题,因为我们**mode[l][r][k]**是一个三维数组,所以即使我们控制了k的大小,空间还是不可一忽略的,诸位看官可以试试**sqrt(n)**分块直接MLE到飞起,所以我们不得不考虑一种船星~~蛤西~~分块方法,$n^{\frac{2}{3}}$了解一下??经过一番乱搞我们发现以这个为块长的分块即使到了$n==40000$的情况下,也只有不到**40**块的分块！！！

**congratulations！！！**

恭喜大佬找到了正确的打开姿势  但还是有一个不怎么起眼的小细节,就是分块$L_{i},R_{i}$数组的处理,因为我们这里块长为$n^{\frac{2}{3}}$次方,所以块的处理就一定要重开一个数来记录一共有几块

我们把所有的区间就这么分成了这么几个区间,下面考虑预处理

**CODE**

其中$L_{i}$与$R_{i}$分别表示第***i***块的左右端点,$Len$为总块数

```cpp
void Find_Mode(){
    for(int i=1;i<=Len;++i)//枚举前一块
        for(int j=i;j<=Len;++j)//枚举后一块
            for(int k=L[i];k<=R[j];++k){//枚举第i到j块之间的每一个数
                ++mode[i][j][a[k]];
                if(mode[i][j][a[k]]>mode[i][j][0]||(mode[i][j][a[k]]==mode[i][j][0]&&a[k]<mode_id[i][j]))
                    mode[i][j][0]=mode[i][j][a[k]],mode_id[i][j]=a[k];//满足数量大于当前众数,或数量等于,编号小于就更新预处理数组
            }
}//处理出区间众数
```
如此我们便找到了区间的众数,根据分块的思想,我们对于每一个询问,先假设整块的众数就是答案,在用零碎的块上的数去试图更新答案就可以了

**CODE**

其中**temporary[]**值得是存储零碎的块中相应的个数有几个

```cpp
int Find_Ans(int l,int r){
    int ans=0,mode_num=-1;
    if(belong[l]==belong[r]){//左右端点之间没有整块就暴力查询
        for(int i=l;i<=r;++i){
            ++temporary[a[i]];
            if(temporary[a[i]]>mode_num||(temporary[a[i]]==mode_num&&a[i]<ans))
                ans=a[i],mode_num=temporary[a[i]];
        }
        for(int i=l;i<=r;++i)
            temporary[a[i]]=0;//对于每一次询问记得清0这个临时数组
        return ans;
    }
    ans=mode_id[belong[l]+1][belong[r]-1],mode_num=mode[belong[l]+1][belong[r]-1][0];//先钦定整块的答案就是答案
    for(int i=l;i<L[belong[l]+1];++i){
        ++temporary[a[i]];
        if(temporary[a[i]]+mode[belong[l]+1][belong[r]-1][a[i]]>mode_num||(temporary[a[i]]+mode[belong[l]+1][belong[r]-1][a[i]]==mode_num&&a[i]<ans))
            ans=a[i],mode_num=temporary[a[i]]+mode[belong[l]+1][belong[r]-1][a[i]];
    }
    for(int i=R[belong[r]-1]+1;i<=r;++i){
        ++temporary[a[i]];
        if(temporary[a[i]]+mode[belong[l]+1][belong[r]-1][a[i]]>mode_num||(temporary[a[i]]+mode[belong[l]+1][belong[r]-1][a[i]]==mode_num&&a[i]<ans))
            ans=a[i],mode_num=temporary[a[i]]+mode[belong[l]+1][belong[r]-1][a[i]];
    }//试图用零块上的数更新答案
    for(int i=l;i<L[belong[l]+1];++i)
        temporary[a[i]]=0;
    for(int i=R[belong[r]-1]+1;i<=r;++i)
        temporary[a[i]]=0;//记得将标记删除
    return ans;
}//分块！！！
```

至于整段的代码这里就不给出了(其实就是懒

---

## 作者：zyzzyzzyzzyz (赞：1)


------

## 分块

### 一.题意及思路

首先，发现题目是要求静态区间众数

**暴力**的想法:

​	先离散化,对于每个询问区间$[l,r]$ ,开一个桶,然后暴扫,复杂度$O(n\times m)$,TLE

那么可以考虑用线段树等

但是显然众数不满足区间可加性

所以考虑分块算法

虽然复杂度更劣，但代码简单

-----

### 二.分块正解

将整个区间分为$T$个块,每块长 $len$

那么询问$[l,r]$ 必然包括三个部分

即两端的零散区间和中间整段区间

那么众数的来源也就对应的只有三种情况

~~废话,不然呢!~~

到这里,我们的复杂度仍然是假的

因为每次都要将整个询问区间扫一遍

**那么此时分块的优势就体现出来了**

将询问区间分成三块后,分别处理:

​	1.左边零散区间:暴力扫,复杂度$O(len)$

​	2.右边零散区间:同上

​	**3.中间整块区间**:

​		我们可以预处理出一个数组$color[L][R][N]$做到每次询问时$O(1)$

​		**其中$L,R​$是表示左右端点块(即当前区间$[l,r]=[L*len+1,R*len]​$)**

​		$N$表示哪种颜色

​		那么$color[L][R][K]=color[L][R-1][K]+\sum_{i=(R-1)*len+1}^{R*len}[a[i]==K]$

​		所以预处理的复杂度是$O(N*T^2)$ 

那么总共的复杂度就是$O(N*T*T+M*N/T)$ 

可以发现当$T=N^\frac{1}{3}$ 时最优

### 三.代码

```cpp
#include<bits/stdc++.h>
#define il inline 
#define RG  register int
#define ll long long
#define gc getchar
using namespace std;
il int rd()
{
    int x=0,flag=1;
    char ch=0;
    while((ch>'9'||ch<'0')&&ch!='-')ch=gc();
    if(ch=='-')flag=-1,ch=gc();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=gc();
    return x*flag;
}
const int MAXT=40,MAXN=40010;
int color[MAXT][MAXT][MAXN];
int modenum[MAXT][MAXT],mdtimes[MAXT][MAXT];
int n,m,T,len;
int a[MAXN],b[MAXN];
int l,r,ans,ans2;
int main ()
{
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
    n=rd();m=rd();
    T=floor(pow(n,0.3333333));
    len=n/T;
    for(RG i=1;i<=n;i++)
        b[i]=a[i]=rd();
    sort(b+1,b+n+1);
    unique(b+1,b+n+1);
    for(RG i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    for(RG i=1;i<=T;i++)
        for(RG j=i;j<=T;j++){
            for(RG k=1;k<=n;k++)
                color[i][j][k]+=color[i][j-1][k];
            for(RG k=(j-1)*len+1;k<=j*len;k++)
                color[i][j][a[k]]++;
            for(RG k=1;k<=n;k++)
                if(mdtimes[i][j]<color[i][j][k])modenum[i][j]=k,mdtimes[i][j]=color[i][j][k];
        }
    for(RG i=1;i<=m;i++){
        l=rd(),r=rd();
        l=(l+b[ans2]-1)%n+1,r=(r+b[ans2]-1)%n+1;
        if(l>r)swap(l,r);
        int L=l/len+1,R=(r-1)/len;
        ans2=modenum[L+1][R];//?
        if(L<=R)
        {
            for(RG j=l;j<=L*len;j++)
                color[L+1][R][a[j]]++;
            for(RG j=R*len+1;j<=r;j++)
                color[L+1][R][a[j]]++;
            for(RG j=l;j<=L*len;j++)
                if(color[L+1][R][a[j]]>color[L+1][R][ans2]||(color[L+1][R][a[j]]==color[L+1][R][ans2]&&ans2>a[j]))ans2=a[j];
            for(RG j=R*len+1;j<=r;j++)
                if(color[L+1][R][a[j]]>color[L+1][R][ans2]||(color[L+1][R][a[j]]==color[L+1][R][ans2]&&ans2>a[j]))ans2=a[j];
            for(RG j=l;j<=L*len;j++)
                color[L+1][R][a[j]]--;
            for(RG j=R*len+1;j<=r;j++)
                color[L+1][R][a[j]]--;
            printf("%d\n",b[ans2]);
        }
        else
        {
            for(RG j=l;j<=r;j++)
                color[L+1][R][a[j]]++;
            for(RG j=l;j<=r;j++)
                if(color[L+1][R][a[j]]>color[L+1][R][ans2]||(color[L+1][R][a[j]]==color[L+1][R][ans2]&&ans2>a[j]))ans2=a[j];
            for(RG j=l;j<=r;j++)
                color[L+1][R][a[j]]--;
            printf("%d\n",b[ans2]);
        }
    }
    return 0;
}


```

---

## 作者：Isonan (赞：1)

原题传送门[>Here<](https://www.luogu.org/problemnew/show/P4168)

（强制在线坑死人啊。。）

一句话题意：在线静态区间众数。

同机房奆佬分了3块就水过了此题，然而我不是很~~**想打**~~会这种~~**暴力**~~高深的算法。（死也不用分块系列）

我本来以为可以像[总统选举](https://www.luogu.org/problemnew/show/P3765)一样用线段树维护区间众数，可惜一个区间众数并没有可以用来合并的性质，如果要通过两个区间合并得到大区间中的众数，答案有可能是其中一个区间中第二大的数，要维护第二大的数又要记录第三大。。

没有办法，最后还是~~**屈服在分块的淫威之下**~~打了分块。

用分块打就很简单了：

预处理出每个块中每种花个数，然后对于块求前缀和，并算出每个块中的众数。

每次查询时加上两边的部分，一边加一边更新众数。

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>

int block,pos[100001],sum[1001][100001],num[100001],orig[100001],n,m,ans,lim,a[1001][1001];
int start[1001],count[100001],l,r;
int main(){
	scanf("%d%d",&n,&m);
	block=(int)sqrt(n);
	for(int i=1;i<=n;i++)scanf("%d",num+i),orig[i]=num[i];
	std::sort(orig+1,orig+n+1);
	lim=std::unique(orig+1,orig+n+1)-orig-1;
	for(int i=1;i<=n;i++){
		++sum[pos[i]=(i-1)/block+1][num[i]=std::lower_bound(orig+1,orig+lim+1,num[i])-orig];
		if(pos[i]!=pos[i-1])start[pos[i]]=i;
	}
	for(int i=1;i<=pos[n];i++)
		for(int j=1;j<=lim;j++)
			sum[i][j]+=sum[i-1][j];
	for(int i=1;i<=pos[n];i++){
		for(int j=start[i];j<=n;j++){
			if(pos[j]!=pos[j-1])a[i][pos[j]]=a[i][pos[j]-1];
			if(++count[num[j]]>count[a[i][pos[j]]]||(count[num[j]]==count[a[i][pos[j]]]&&num[j]<a[i][pos[j]]))
				a[i][pos[j]]=num[j];
		}
		for(int j=start[i];j<=n;j++){
			--count[num[j]];
		}
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		l=(l+ans-1)%n+1;
		r=(r+ans-1)%n+1;
		if(l>r)l^=r^=l^=r;
		ans=0;
		if(pos[r]-pos[l]<=2){
			for(int j=l;j<=r;j++){
				if(++count[num[j]]>count[ans]||(count[num[j]]==count[ans]&&num[j]<ans))
					ans=num[j];
			}
			for(int j=l;j<=r;j++){
				--count[num[j]];
			}
		}
		else{
			ans=a[pos[l]+1][pos[r]-1];
			for(int j=l;pos[j]==pos[l];j++)
				if(++count[num[j]]+sum[pos[r]-1][num[j]]-sum[pos[l]][num[j]]>count[ans]+sum[pos[r]-1][ans]-sum[pos[l]][ans]||
					(count[num[j]]+sum[pos[r]-1][num[j]]-sum[pos[l]][num[j]]==count[ans]+sum[pos[r]-1][ans]-sum[pos[l]][ans]&&
					num[j]<ans))
				ans=num[j];
			for(int j=start[pos[r]];j<=r;j++)
				if(++count[num[j]]+sum[pos[r]-1][num[j]]-sum[pos[l]][num[j]]>count[ans]+sum[pos[r]-1][ans]-sum[pos[l]][ans]||
					(count[num[j]]+sum[pos[r]-1][num[j]]-sum[pos[l]][num[j]]==count[ans]+sum[pos[r]-1][ans]-sum[pos[l]][ans]&&
					num[j]<ans))
				ans=num[j];
			for(int j=l;pos[j]==pos[l];j++)--count[num[j]];
			for(int j=start[pos[r]];j<=r;j++)--count[num[j]];
		}
		ans=orig[ans];
		printf("%d\n",ans);
	}
}
```

---

## 作者：PandZz (赞：0)

# 题目大意

求区间众数，且解法被强制在线：

```
再接下来m 行每行两个整数 l0,r0 我们令上次询问的结果为 x（如果这是第一次询问，则x=0）。

令 l=(l0+x−1)%n+1,r=(r0+x−1)%n+1,如果l>r，则交换l,r 。

最终的询问区间为[l,r]。
```

可怕吧

# 解法

类似此种不满足区间可加性的，我们常采用**暴力**的分块来解决

1. 将原数据离散化，并建立映射
2. 分块
3. 预处理出两个数组：
	* $mode[i][j]$,表示第$i$块到第$j$块的众数
    * $sum[i][j]$,表示从第$0$块到第$i$块,$j$的个数
    
## 预处理方法

比较简单，直接贴代码：

```cpp
//calc:sum 
	for (i=1;i+SQRTN-1<=n;i+=SQRTN){
		lim=i+SQRTN-1,++pos;
		if (i!=1){
			for (j=1;j<=cnt;++j) sum[pos][j]=sum[pos-1][j];
		}
		for (j=i;j<=lim;++j) ++sum[pos][a[j]],P[j]=pos;
	}
	if (i+SQRTN-1<n){
		++pos;
		for (;i<=n;++i) ++sum[pos][a[i]],P[i]=pos;
	}
//calc:mode 
	tot=pos;
	for (i=1;i<=tot;++i){
		for (j=i;j<=tot;++j){
			lim=j*SQRTN>n?n:j*SQRTN,ls=0,pos=0x7f7f7f7f;
			for (k=(i-1)*SQRTN+1;k<=lim;++k){
 				if ((sum[j][a[k]]-sum[i-1][a[k]]>ls)||(sum[j][a[k]]-sum[i-1][a[k]]==ls&&a[k]<pos))
					ls=sum[j][a[k]]-sum[i-1][a[k]],pos=a[k]; 
			}
			mode[i][j]=pos;
		}
	}    
```

## 求解

1. 若$l,r$位于相邻或同一块，暴力求解
2. 若$l,r$之间包含整块，直接使用$mode[l][r]$求出中间的众数，那么众数就只能在两个地方产生：
	* 中间的众数
    * 两边"残余"的段中的数，此情况暴力即可

---

## 作者：Great_Influence (赞：0)

和[这个](https://www.luogu.org/problemnew/show/P5048)一样。

这个方法常数和内存都比较小，要好一些。

具体来说，先求出块内答案，然后暴力处理边角料。

对于边角料中的答案，如果一个数字向前/向后第$ans$次出现位置仍然在区间内，则可以将答案+1。

这样只需要用$vector$记录所有点的出现位置集合即可。

时间复杂度$O[(n+q)\sqrt n]$，空间复杂度$O(n)$。

```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define pb push_back
#define mp make_pair
typedef unsigned long long uint64;
typedef unsigned int uint32;
using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<24;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

inline void file()
{
#ifndef ONLINE_JUDGE
	FILE*WA=freopen("water.in","r",stdin);
	FILE*TER=freopen("water.out","w",stdout);
#endif
}

const int MAXN=4e4+7;

static int n,m,a[MAXN],b[MAXN],tt,ps[MAXN],sz[MAXN];

vector<int>show[MAXN];

inline void init()
{
	read(n),read(m);
	Rep(i,1,n)read(a[i]),b[i]=a[i];
	sort(b+1,b+n+1),tt=unique(b+1,b+n+1)-b-1;
	Rep(i,1,n)
	{
		a[i]=lower_bound(b+1,b+tt+1,a[i])-b;
		show[a[i]].pb(i);
		ps[i]=show[a[i]].size();
	}
	Rep(i,1,tt)sz[i]=show[i].size();
}

const int BLK=211;

static int blk,ans[BLK][BLK],shown[BLK][BLK];

static int nt,cnt[MAXN];

static int bel[MAXN],lp[BLK],rp[BLK];

inline void Chkmin(int&a,int b){a>b?a=b:0;}

inline void fixans(int l,int r,int w)
{
	if(ans[l][r]<cnt[w])ans[l][r]=cnt[w],shown[l][r]=w;
	else if(ans[l][r]==cnt[w])Chkmin(shown[l][r],w);
}

inline void solve()
{
	blk=sqrt(n)+1;
	Rep(i,1,n)
	{
		bel[i]=(i-1)/blk+1;
		if(!lp[bel[i]])lp[bel[i]]=i;
		rp[bel[i]]=i;
	}
	nt=bel[n];
	Rep(z,1,nt)
	{
		ans[z][z]=0;
		Rep(i,1,tt)cnt[i]=0;
		Rep(i,lp[z],rp[z])++cnt[a[i]],fixans(z,z,a[i]);
		Rep(i,z+1,nt)
		{
			ans[z][i]=ans[z][i-1],shown[z][i]=shown[z][i-1];
			Rep(j,lp[i],rp[i])++cnt[a[j]],fixans(z,i,a[j]);
		}
	}
	static int l,r,mx,lasans=0;
	Rep(_,1,m)
	{
		read(l),read(r);
		l=(l+lasans-1)%n+1,r=(r+lasans-1)%n+1;
		if(l>r)swap(l,r);
		mx=0;
		if(r-l<=2*blk)
		{
			Repe(i,r,l)
			{
				if(sz[a[i]]>=ps[i]+mx&&show[a[i]][ps[i]+mx-1]<=r)++mx,lasans=a[i];
				else if(sz[a[i]]>=ps[i]+mx-1&&show[a[i]][ps[i]+mx-2]<=r)
					Chkmin(lasans,a[i]);
			}
			lasans=b[lasans];
			write(lasans);
			continue;
		}
		int x=l==lp[bel[l]]?bel[l]:bel[l]+1,y=r==rp[bel[r]]?bel[r]:bel[r]-1;
		mx=ans[x][y];
		lasans=shown[x][y];
		Repe(i,lp[x]-1,l)
		{
			if(sz[a[i]]>=ps[i]+mx&&show[a[i]][ps[i]+mx-1]<=r)++mx,lasans=a[i];
			else if(sz[a[i]]>=ps[i]+mx-1&&show[a[i]][ps[i]+mx-2]<=r)
				Chkmin(lasans,a[i]);
		}
		Rep(i,rp[y]+1,r)
		{
			if(ps[i]>=mx+1&&show[a[i]][ps[i]-mx-1]>=l)++mx,lasans=a[i];
			else if(ps[i]>=mx&&show[a[i]][ps[i]-mx]>=l)Chkmin(lasans,a[i]);
		}
		lasans=b[lasans];
		write(lasans);
	}
	flush();
}

int main()
{
    init();
    solve();
    return 0;
}
```

---

## 作者：zhenglier (赞：0)

```cpp
//解决本题的重要性质： 
//对于两个区间a,b,其中已知a区间的众数k 
//则众数一定为k或是b区间的任意一个数  
#include<bits/stdc++.h>
#define re register int 
using namespace std;
const int N=40010,M=410;
int n,q,m,blen,bsum;
int a[N],b[N];//b为离散数组 
int bl[M][M];//bl[i][j]表示第i个块中的第j个数，bl[i][0]表示第i个块的长度 
int bk[N];//bk[i]表示第i个数（在原数列中）在第bk[i]个块中 
int f[M][M];//f[i][j]表示第i块到第j块之间的众数 
int g[N][M];//g[i][j]表示i在前j个块中出现的次数 
void init(){//初始化 
	for(int i=1,j=1;i<=n;++j){
		int k;
		for(k=1;k<=blen&&i<=n;++i,++k){
			bk[i]=j;
			bl[j][k]=a[i];
		}k--;
		bl[j][0]=k;
		bsum=j;
	}//处理块 
	for(int i=1;i<=bsum;++i){
		for(int j=1;j<=m;++j){
			g[j][i]=g[j][i-1];
		}
		for(int j=1;j<=bl[i][0];++j){
			g[bl[i][j]][i]++;
		}
	}//预处理g数组 
	for(int i=1;i<=bsum;++i){
		for(int j=i;j<=bsum;++j){
			int num=f[i][j-1];int mx=g[num][j]-g[num][i-1];
			for(int k=1;k<=bl[j][0];++k){
				int now=g[bl[j][k]][j]-g[bl[j][k]][i-1];
				if(now>mx||(now==mx&&bl[j][k]<num))num=bl[j][k],mx=now;
			}
			f[i][j]=f[j][i]=num;
		}
	}//预处理f数组 
}
void read(){//读入 
	cin>>n>>q;blen=sqrt(n);
	for(int i=1;i<=n;++i)scanf("%d",a+i),b[i]=a[i];
}
void lsh(){//lisanhua==lsh,离散化 
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
//	for(int i=1;i<=n;++i)cout<<i<<":"<<a[i]<<' ';puts("");
}
void work(){
	int last=0;
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		l=(l+last-1)%n+1;
		r=(r+last-1)%n+1;
		if(l>r)swap(l,r);
		static int bj[M],cnt,v[N];cnt=0;//bj记录边角的数据,cnt为边角数据的数量
		int L,R,num,mx; 
		if(bk[l]==bk[r]){//在同一块内暴力求众数 
			for(int i=l;i<=r;++i)bj[++cnt]=a[i],v[a[i]]++;
			mx=0;
			for(int i=l;i<=r;++i){
				if(v[a[i]]>mx||(v[a[i]]==mx&&a[i]<num))num=a[i],mx=v[a[i]];
			}
			printf("%d\n",last=b[num]);
		}else{//在不同块时，将中间当成一大块和边角比较
		      //根据性质，众数只有可能是中间这一块的众数或是边角上的数
			  //所以暴力枚举再判断就行了 
			re i;
			for(i=l;bk[i]==bk[i-1];++i){
				bj[++cnt]=a[i];v[a[i]]++;
			}L=bk[i]; 
			for(i=r;bk[i]==bk[i+1];--i){
				bj[++cnt]=a[i];v[a[i]]++;
			}R=bk[i];
		    num=f[L][R],mx=v[num]+g[num][R]-g[num][L-1];
		    for(i=1;i<=cnt;++i){
		    	int now=v[bj[i]]+g[bj[i]][R]-g[bj[i]][L-1];
		    	if(now>mx||(now==mx&&bj[i]<num))num=bj[i],mx=now;
			}
//			printf("%d\n",num);
			printf("%d\n",last=b[num]);
		}
//		for(int i=1;i<=cnt;++i)cout<<bj[i]<<' ';puts("");
		for(re i=1;i<=cnt;++i)--v[bj[i]];//v数组要这样清空，复杂度O(cnt)，不能用memset，那样是O(n)
	}
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	read();
	lsh();
	init();
	work(); 
}
```

---

## 作者：bztMinamoto (赞：0)

先厚颜无耻的打个广告->[这里](https://www.cnblogs.com/bztMinamoto/p/9607299.html)

md调了一个晚上最后发现竟然是空间开小了……明明算出来够的……

讲真其实我以前不太瞧得起分块，觉得这种基于暴力的数据结构一点美感都没有。然而今天做了这道分块的题才发现分块的暴力之美（如果我空间没有开小就更美了）

我们先将整个数组分块，设块的大小为$T$

我们先预处理出所有以块边界为端点的区间的答案，即$ans[L][R]$代表着第$L$块到第$R$块的序列所代表的答案。这个可以$O(n*n/T)$预处理

然后我们先将所有的数给离散化，然后对每一个值都开一个vector，记录这个值在数组中出现的每一个位置。比如数组的下标为1,3,5的位置都是3，那么3的vector记录的就是{1,3,5}

这个有什么用呢？我们设查询的区间为$[l,r]$，然后在这个vector里先二分查找第一个大于等于$l$的数的位置，再二分查找第一个大于$r$的数的位置，那么两个位置一减就是这个数在这个区间中的出现次数。比如查询区间$[2,4]$，我们先找到第一个大于等于2的数3，在vector中下标为2，再找第一个大于4的数为5，下标为3，那么3-2=1就是3这个数字在这个区间中的出现次数

那么，我们设$[L,R]$为查询区间之间的整块，因为我们第一步已经预处理出了所有块与块之间的答案，那么这一段之间的众数也就可以知道。那么，只有区间$[l,L-1]$和$[R+1,r]$之间的数字有可能更新答案。那么我们就去枚举这两个区间中的所有数字，然后用上面说的方法去查询它在整个查询区间内的出现次数，然后更新答案即可

复杂度为$O(n*n/T+n*T*logn)$，设块的大小为$n/sqrt{nlogn}$ ，那么时间复杂度就是$O(nsqrt{nlogn})$

其实还有一种更快的方法是先预处理出块与块之间的答案和各个数的出现次数，然后查询只要在散块里暴力增加并更新答案，之后暴力复原即可（然而我懒并不想打）。楼下已经写了，我就不多提了（主要是打完才发现楼下那个好想跑的比我快，因为少了个二分的复杂度）

然后基本注意点都写在注解里了
```
//minamoto
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#define inf 0x3f3f3f3f
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=40005,M=1005;
int ans[M][M],a[N],b[N],cnt[N],rt[N],vis[N];
vector<int> pos[N];
int n,m,q,lastans=0,s,l,r;
inline int query_cnt(int x){
	//查询数的出现次数，注意l和r要开全局变量 
    return upper_bound(pos[x].begin(),pos[x].end(),r)-lower_bound(pos[x].begin(),pos[x].end(),l);
}
void init(){
	//暴力枚举块与块之间的答案 
    for(int i=1;i<=rt[n];++i){
        memset(cnt,0,sizeof(cnt));
        int bg=s*(i-1)+1,res=a[bg];
        for(int j=bg;j<=n;++j){
            ++cnt[a[j]];
            if(cnt[a[j]]>cnt[res]||(cnt[a[j]]==cnt[res]&&a[j]<res)) res=a[j];
            ans[i][rt[j]]=res;
        }
    }
}
int query(int l,int r){
	//查询，小块暴力，大块直接找答案 
    if(rt[r]-rt[l]<=1){
    	int id=0,res=0;
        for(int i=l;i<=r;++i)
        if(!vis[a[i]]){
            int t=query_cnt(a[i]);
            if(t>res||(t==res&&a[i]<id)) res=t,id=a[i];
            vis[a[i]]=1;
        }
        for(int i=l;i<=r;++i) vis[a[i]]=0;
        return b[id];
    }
    int L=rt[l]+1,R=rt[r]-1;
    int LL=(L-1)*s+1,RR=R*s;
    int id=ans[L][R],res=query_cnt(id);vis[id]=1;
    for(int i=l;i<LL;++i)
    if(!vis[a[i]]){
        int t=query_cnt(a[i]);
        if(t>res||(t==res&&a[i]<id)) res=t,id=a[i];
        vis[a[i]]=1;
    }
    for(int i=RR+1;i<=r;++i)
    if(!vis[a[i]]){
        int t=query_cnt(a[i]);
        if(t>res||(t==res&&a[i]<id)) res=t,id=a[i];
        vis[a[i]]=1;
    }
    for(int i=l;i<LL;++i) vis[a[i]]=0;
    for(int i=RR+1;i<=r;++i) vis[a[i]]=0;
    vis[ans[L][R]]=0;
    return b[id];
}
int main(){
    n=read(),q=read(),s=sqrt(n/(double)(log2(n))+1);
    //我怕s会变成0所以sqrt里加了个1（可能并不需要） 
    for(int i=1;i<=n;++i) a[i]=b[i]=read(),rt[i]=(i-1)/s+1;//分块 
    sort(b+1,b+1+n),m=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+1+m,a[i])-b,pos[a[i]].push_back(i);
    //以上是离散 
    init();
    while(q--){
        l=read(),r=read();
        l=(l+lastans-1)%n+1,r=(r+lastans-1)%n+1;
        if(l>r) swap(l,r);
        print(lastans=query(l,r));
    }
    Ot();
    return 0;
}
```

---

