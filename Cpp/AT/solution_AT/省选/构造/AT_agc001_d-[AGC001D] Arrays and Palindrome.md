# [AGC001D] Arrays and Palindrome

## 题目描述

高桥くん的母亲在高桥生日的时候送了他 $a, b$ 两个数列。因为 $a, b$ 满足了如下的所有性质， 所以他非常高兴：

* $a$ 数列的数字总和是 $N$；
* $b$ 数列的数字总和是 $N$；
* $a, b$ 中包含的数都是正整数； 
* 满足以下两个条件的数列， 所有元素必定是相同的。
  * 最开始的 $a_1$ 个元素, 接下来的 $a_2$ 个元素，更后面的 $a_3$ 个，等等，都是回文；
  * 最开始的 $b_1$ 个元素, 接下来的 $b_2$ 个元素，更后面的 $b_3$ 个，等等，都是回文。

但是有一天，高桥把把数列 $a$ 和 $b$ 都弄丢了， 幸运的是，他知道数列 $a$ 是另一个长度为 $M$ 的序列 $A$ 的排列。

为了让他再一次高兴起来， 他妈妈决定给他另一对数列使其满足如上性质。

## 说明/提示

- $1≤N≤10^5$；
- $1≤M≤100$；
- $1≤A_i≤10^5$。

数据保证 $A_i$ 的和是 $N$。

## 样例 #1

### 输入

```
3 2
2 1```

### 输出

```
1 2
1
3```

## 样例 #2

### 输入

```
6 1
6```

### 输出

```
6
3
1 2 3```

## 样例 #3

### 输入

```
55 10
1 2 3 4 5 6 7 8 9 10```

### 输出

```
Impossible```

# 题解

## 作者：feecle6418 (赞：18)

这种“使所有元素相同”题目的一般套路是第一个段伸出一个接口，中间的段接受一个接口再伸出下一个接口，最后一个段接受最终的接口，这样就满足条件。

这道题中我们可以这样设计接口：

![](https://cdn.luogu.com.cn/upload/image_hosting/dmxtkre0.png)

（图中绿圈表示接口，黑线表示 $A$ 确定的必须相等的元素，蓝线表示构造的 $B$ 确定的必须相等的元素。①为中间段，②为开始段，③为结束段）

由上图发现，只有长度为 $2k$ 的段才能放在中间。因此长度为奇数的段至多只能有两个，一个在最开始，一个在最后。具体排列及 $B$ 数组直接根据上图构造即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],cnt[2],ans[1005];
int main() {
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>a[i],cnt[a[i]&1]++;
	if(m==1){
		if(a[1]==1)cout<<"1\n1\n1\n";
		else cout<<a[1]<<endl<<2<<endl<<1<<' '<<a[1]-1<<endl;
		return 0;
	}
	if(cnt[1]>2)return puts("Impossible"),0;
	sort(a+1,a+m+1,[](int i,int j){return i%2>j%2;});
	cout<<a[1]<<' ';
	for(int i=3;i<=m;i++)cout<<a[i]<<' ';
	cout<<a[2]<<endl,ans[++ans[0]]=a[1]+1;
	for(int i=3;i<=m;i++)ans[++ans[0]]=a[i];
	if(a[2]>1)ans[++ans[0]]=a[2]-1;
	cout<<ans[0]<<endl;
	for(int i=1;i<=ans[0];i++)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：CYJian (赞：6)

## AGC001D

一道构造题。。

首先很容易发现，如果我们把回文的对应相等的关系当成连边，我们就相当于希望这个东西连成一个联通块。首先不难发现，我们每次连的边数是 $\sum_{i=1}^{M} \left\lfloor \frac{a_i}{2} \right \rfloor$ 的。如果给出的 $a_i$ 中存在三个及以上的奇数，那么就一定不可能了。因为每有两个奇数，连出来的边数就会减少 $1$。连成一个联通块至少要是一棵树才行。

那么怎么构造呢？

我们先从特殊的情况考虑：$M=1$ 的时候，我们发现，只需要令 $a_1=N$ ，$b_1=1$，$b_2=N-1$ 就行了。 

然后我们考虑这样构造：首先将所有奇数分别放在开头结尾，然后这样构成 $a$ 数列；

再让开头 $+1$，结尾 $-1$，就能构造出来合法的序列了。

不难发现，这样构造，会让中间的边正好错开，前后两个的边也是错开的，边数恰为 $n-1$，正好构成一棵树。

代码很简单，就不贴了。

---

## 作者：foreverlasting (赞：6)

[题面](https://www.luogu.org/problemnew/show/AT1982)

构造题。

首先把$a$数组转成回文串的形式很简单，这里就不讲了。具体是如何构造$b$，我猜了一个结论：$b$的首是$a$的末$+1$，$b$的末是$a$的首$-1$，中间把构造好的$a$塞进去就好了。至于证明，看[这篇博客](https://www.cnblogs.com/wendavid/p/8982266.html)。

code:
```
//2018.9.20 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
const int N=1e5+10;
namespace MAIN{
    int n,m;
    int a[N],b[N],bx;
    inline void MAIN(){
        n=read(),m=read();
        for(res i=1;i<=m;i++)a[i]=read();
        if(m==1)b[++bx]=1,b[++bx]=n-1;
        else {
            res cnt=0;
            for(res i=1;i<=m;i++)cnt+=a[i]&1;
            if(cnt>2){puts("Impossible");return;}
            for(res i=2;i<m;i++)
                if(a[i]&1){
                    if(a[1]&1)_swap(a[i],a[m]);
                    else _swap(a[1],a[i]);
                }
            b[++bx]=a[m]+1;
            for(res i=m-1;i>1;i--)b[++bx]=a[i];
            b[++bx]=a[1]-1;
        }
        for(res i=1;i<=m;i++)printf("%d ",a[i]);
        puts("");
        if(!b[bx])bx--;
        printf("%d\n",bx);
        for(res i=bx;i>=1;i--)printf("%d ",b[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Ebola (赞：5)

楼下没有证明，我来简单说一下推导过程

建立一个图论模型。对于钦定相等的两个点，给它们连一条边，然后一个联通块内的所有点都要相等

那对于一个长度为n的回文串，其实就是钦定了i与n-i+1要相等，相当于在图中连了n/2条边（下取整）

为了让n个点连通，我们需要至少n-1条边。对于一个由若干段回文构成的序列，它至多连出(n-odd)/2条边，其中odd表示大小为奇数的段数

可以看出，若一开始给定的数列中，奇数大于2个，必然无解

那么对于一个有解的数列，把奇数放在首尾得到序列1，第一个数减一、最后一个数加一得到序列2

这样，每一段都是错开的，每一条边都必然连接两个原本不连通的块

因为题目要求不能输出0，所以需要再特判一下

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=110;
int a[N],n,m;
int oddnum[2];

int main()
{
    int odd=0,tot=0;
    scanf("%d%d",&n,&m);
    oddnum[0]=1;oddnum[1]=m;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",a+i);
        if(~a[i]&1) continue;
        oddnum[odd++]=i;
        if(odd>2) return puts("Impossible"),0;
    }
    swap(a[1],a[oddnum[0]]);
    swap(a[m],a[oddnum[1]]);
    if(m==1&&a[1]==1) return puts("1\n1\n1"),0;
    for(int i=1;i<=m;i++) printf("%d ",a[i]);
    if(m==1) return printf("\n2\n%d 1\n",a[1]-1),0;
    printf("\n%d\n%d ",a[m]>1?m:m-1,a[1]+1);
    for(int i=2;i<m;i++) printf("%d ",a[i]);
    if(a[m]>1) printf("%d\n",a[m]-1);
    return 0;
}
```



---

## 作者：tzc_wk (赞：4)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Atcoder 题面传送门](https://atcoder.jp/contests/agc001/tasks/agc001_d)

[洛谷题面传送门](https://www.luogu.com.cn/problem/AT1982)

又是道思维题，又是道把我搞自闭的题。

首先考虑对于固定的 $a_1,a_2,\dots,a_n;b_1,b_2,\dots,b_m$ 怎样判定是否合法，我们对于回文串对应的点之间连边，表示它们必须相等，这样可以形成一张图，如果该图连通那么证明这两个数组合法，反之不合法，正确性显然。

注意到对于每个 $a_i$ 会连出 $\lfloor\dfrac{a_i}{2}\rfloor$ 条边，换句话说，如果 $a_i$ 是偶数那么全部 $\dfrac{a_i}{2}$ 条边都能连，如果 $a_i$ 是奇数那么会出现一个孤立点，综上 $a$ 部分连出的边的个数为 $\dfrac{n-a\ \text{数组中奇数的个数}}{2}$，而 $b$ 数组不论你怎么排最多只能连出 $\lfloor\dfrac{n}{2}\rfloor$ 条边，故如果 $a$ 数组中奇数个数 $\geq 3$，那么最多也只能连出 $\dfrac{n-3}{2}+\dfrac{n-1}{2}=n-2<n-1$ 条边，无解。

接下来考虑怎样构造出符合要求的解，先从特殊的情况开始，如果 $m=1$，那么分两种情况：$n=1$ 那么显然 $m=1,b_1=1$ 就符合要求。如果 $n>1$，那么考虑一个“错位”的思想，分两组，一组长度为 $1$，另一组长度为 $n-1$，这样连就能解决问题了，因为这样会导致 $1$ 与 $n$ 相连，$n$ 与 $2$ 相连，$2$ 又与 $n-1$ 相连……$i$ 与 $n-i+1$ 和 $n-i$ 相连，最终 $1\sim n$ 就一定会被连成一条链了。

接下来考虑更一般的情况，考虑先重排 $a$ 数组，如果 $a$ 数组有奇数，就将奇数放在 $a$ 数组的两边（有一个就放在开头，有两个就一个放开头一个放结尾）。其次考虑这样构造 $b$ 数组，$b_1=a_1+1,b_i=a_i(i\in [2,n]),b_n=a_n-1$。这样做就对了。

为什么？其实也是用了“错位”的思想，借鉴 $n=2$ 的经验，构造 $b_1=a_1+1$ 显然可以使前 $a_1$ 个数连成一片，同时也能将第一块（$[1,a_1]$）与第二块（$[a_1+1,a_1+a_2]$）串在一起，以此类推就能将全部 $n$ 个数串在一起。还有一个问题，那就是为什么一定要把奇数放到开头或结尾，因为假设 $\exist i,a_i=b_i\equiv 1\pmod{2}$，那么 $a_i$ 与 $b_i$ 在字符串上对应的位置一定是一个两个长度为 $a_i$ 区间，并且左、右端点各相差 $1$，不妨设其为 $[l,r]$ 与 $[l+1,r+1]$，考虑对棋盘进行黑白染色，$l,l+2,l+4,\dots,l+2k,\dots$ 染黑色，$l+1,l+3,l+5,\dots,l+2k+1,\dots$ 染白色，由 $a_i\equiv 1\pmod{2}$ 可知 $l$ 与 $r$ 染色相同，故我们显然只在颜色相同的点之间连边，故黑格与白格间没有边，图也就不连通了。

所以怎么说呢？这种人类智慧思维题，我根本想不出来/kk，wtcl/wq

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
int n,m,p1,p2,cnt[2],a[105];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&a[i]),cnt[a[i]&1]++;
	if(cnt[1]>=3){puts("Impossible");return 0;}
	if(m==1){
		if(a[1]==1) printf("1\n1\n1\n");
		else printf("%d\n2\n1 %d\n",a[1],a[1]-1);
		return 0;
	} sort(a+1,a+m+1,[](int x,int y){return (x&1)>(y&1);});
	printf("%d ",a[1]);for(int i=3;i<=m;i++) printf("%d ",a[i]);printf("%d\n",a[2]);
	vector<int> ans;ans.pb(a[1]+1);for(int i=3;i<=m;i++) ans.pb(a[i]);if(a[2]!=1) ans.pb(a[2]-1);
	printf("%d\n",ans.size());ffe(it,ans) printf("%d ",*it);printf("\n");
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：3)

a. **[[AGC001D] Arrays and Palindrome](https://www.luogu.com.cn/problem/AT_agc001_d)（5）**

> - 对两个数列 $(a_1,a_2,\dots,a_n),(b_1,b_2,\dots,b_m)$ 称为**相配的**当且仅当：
>  - - $a,b$ 两个数列所有元素总和相等（记为 $s$）。
>    - 对任意满足「条件」的长度为 $s$ 的序列 $c$ 总有全部元素相等。
>    - 条件：$c$ 满足前 $a_1$ 个元素回文，接下来 $a_2$ 个元素回文，…，接下来 $a_n$ 个元素回文。且前 $b_1$ 个元素回文，接下来 $b_2$ 个元素回文，…，接下来 $b_m$ 个元素回文。
>  - 给定一个打乱的 $a$，你可以任意排列 $a$，并且任意给出一组相配的 $a,b$。或者说明无解。
>  - $a_i,s\leq 10^5,n\leq 100$。

首先一个长度为 $n$ 的回文可以提供 $[\dfrac n2]$ 条相等信息。我们需要判断全部数相等至少需要 $n-1$ 条相等信息，所以说**最多只有两个奇数**。

观察一种结构，比如当 $n$ 为偶数时，$c[1,n],c[2,n+1]$ 都是回文的情况下， 观察下图可以得到 $c[1,n+1]$ 全部相等：

![](https://cdn.luogu.com.cn/upload/image_hosting/wrjv5lg1.png)

两个接口点可以把所有这种结构都串起来，比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/dn8d9d9i.png)

我们根据这个得到启发：先把所有奇数放两边，我们对每个偶数 $a_i$，搞一个恰好比 $a_i$ 后一格的回文这样子就可以让中部全部相等了。

对于两边的奇数处理是简单的，留给读者。

[submission](https://atcoder.jp/contests/agc001/submissions/41602816)


---

## 作者：ImmortalWatcher (赞：3)

- 经典套路：先考虑如何判定

已知 $a,b$，考虑如何判定合法。

我们根据回文关系连边，两个字符之间有一条边表示它们相等，合法当且仅当所有点联通，这样可以做到 $O(n)$ 判断。

可以发现要使得所有点联通，那么至少要有 $n-1$ 条边，而 $a,b$ 中的一个奇数的连边数是 $\lfloor\dfrac{x}{2}\rfloor$，就会比偶数少连一条边，所以可以得到，一组合法的解 $a,b$ 中奇数个数一定不超过 $2$。

容易发现一种合法的方式是 $a,b$ 错位排列，最后一位可以特殊判断。

同时发现，如果错位排列，奇数放在中间会导致有一条边没有连上（手玩）。

所以我们得到一种构造方法，让奇数放在两边，然后中间按顺序错位排列即可。

 $m=1$ 时需要特判。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[100010],t,b[100010];
int main()
{
	freopen("a.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&a[i]);
		if (a[i]&1) b[++t]=i; 
	}
	if (m==1)
	{
	    if (a[1]==1)printf("%d\n1\n1",a[1],a[1]-1);
	    else printf("%d\n2\n1 %d",a[1],a[1]-1);
	    return 0;
  	}
	if (t>2)
	{
		puts("Impossible");
		return 0;
	}
	if (t>=1) swap(a[1],a[b[1]]);
	if (t>=2) swap(a[m],a[b[2]]);
	for (int i=1;i<=m;i++)
		printf("%d ",a[i]);
	puts("");
	t=0;
	int s1=a[1],s2=a[1]+1;
	b[++t]=a[1]+1;
	for (int i=2;i<m;i++)
	{
		s1+=a[i];
		b[++t]=s1+1-s2;
		s2+=b[t];
		if (!b[t]) t--;
	}
	b[++t]=a[m]-1;
	if (b[t]==0) t--;
	printf("%d\n",t);
	for (int i=1;i<=t;i++)
		printf("%d ",b[i]);
	return 0;
}
```


---

## 作者：eastcloud (赞：2)

[安利一下我的 AGC 补题笔记](https://www.cnblogs.com/eastcloud/p/17421820.html)

把样例画出来试一试，发现在人工判断的过程中，我们相当于给图中具有等价关系的两点连边。即一个回文串中相等的点连边，然后构造出的解必须满足点构成的图联通。

由此我们可以考虑无解的情况，即图不连通，此时分为两种情况，要么边不够 $n-1$ 条，要么图较为特殊。但本题中如果只判断 $a$ 或 $b$ 单个数组所构成的回文串，边数也不超过 $\frac{n}{2}$，而出现奇回文块的情况更是会减少边数，因此我们可以得到如果 $a$ 中奇回文块的个数多于 2，那么一定无解。

那其他情况呢？继续手推样例，发现无解的情况大多出现在我们使某两个回文块回文中心相同，于是我们可以考虑错排，$b$ 中第一个连通块为 $a$ 中第一个连通块大小加 1，最后一个为 $a$ 中最后一块减 1，其他不变，可以发现这种构造方法是正确的。

为了保证少出现奇连通块，我们还需要把 $a$ 中奇连通块放到头尾，即可正确构造。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define N 1000005
using namespace std;
int a[N];
int main(){
	int n,m,tot=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++){cin>>a[i];if(a[i]%2)tot++;}
	if(tot>2){cout<<"Impossible";return 0;}tot=0;
	for(int i=1;i<=m;i++){
		if(a[i]%2 && tot==0) {swap(a[1],a[i]);tot++;}
		else if(a[i]%2)swap(a[m],a[i]);
	}
	for(int i=1;i<=m;i++) cout<<a[i]<<' ';
	cout<<endl;
	if(m==1 && a[1]==1){cout<<1<<endl<<1;return 0;}
	if(m==1){cout<<2<<endl<<a[1]-1<<' '<<1;return 0;}
	if(a[m]-1!=0)cout<<m<<endl;
	else cout<<m-1<<endl;
	for(int i=1;i<=m;i++){
		if(i==m){
			if(a[i]-1==0) continue;
			cout<<a[i]-1<<' ';
		}
		else if(i==1) cout<<a[i]+1<<' ';
		else cout<<a[i]<<' ';
	}
}
```


---

## 作者：Purslane (赞：1)

# Solution

我不会构造题，呜呜呜呜呜。

考虑把 $n$ 个数抽象为 $n$ 个点，每个回文信息可以在对称的位置上连边，最后要求图联通。

$n$ 个点的图联通至少要 $n-1$ 条边。

一个长度为 $l$ 的回文串，可以贡献 $\lfloor \dfrac{l}{2} \rfloor$ 条边。

因此，$A \cup B$ 中最多有 $2$ 个奇数。

可以构造了。很容易想到这种结构：

![](https://s21.ax1x.com/2024/06/07/pkt3JW4.png)

方便起见，使得所有交错的地方长度为 $1$。

分析发现，两头的线段长度奇偶性好像无所谓，但是中间的必须都是偶数。

那么把已知的 $a$ 中元素的技术奇数放到两头即可。

特判 $m=1$ 的情况。

```cpp
#include<bits/stdc++.h> 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=150;
int cnt,n,m,a[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) cin>>a[i],cnt+=(a[i]&1);
	if(m==1) {
		if(a[1]==1) cout<<a[1]<<'\n'<<1<<'\n'<<a[1];
		else cout<<a[1]<<'\n'<<2<<'\n'<<1<<' '<<a[1]-1;
		return 0;
	}
	if(cnt>2) return cout<<"Impossible",0;
	sort(a+1,a+m+1,[](int A,int B) {
		return (A&1)<(B&1);	
	});
	if(a[m-1]&1) swap(a[1],a[m-1]);
	cnt=m;
	ffor(i,1,m) cout<<a[i]<<' ';
	cout<<'\n';
	if(a[1]==1) cnt--; 
	cout<<cnt<<'\n';
	if(a[1]-1) cout<<a[1]-1<<' ';
	ffor(i,2,m-1) cout<<a[i]<<' ';
	cout<<a[m]+1;
	return 0;
}
```

---

## 作者：win114514 (赞：1)

一道比较神秘的构造题。

### 思路

考虑如何通过回文串的性质将所有字符连接起来。

容易发现本题需要使用通过回文串类似连边的方式将所有字符变为一整个连通块。

考虑三种情况。

1. 偶数连偶数

	前面的偶数将最后一个字符与后面的偶数前 $len-1$ 个字符组成一个回文串。
   
2. 偶数连奇数

	前面的偶数将最后一个字符与后面的奇数的所有字符组成一个回文串，至于奇数在前的情况是一样的。
    
3. 奇数连奇数

	用连偶数的方式即可。
    
讨论这三种情况后，容易发现一个序列中有且仅能有不超过 $2$ 个奇数。

并且需要把他们放在一头一尾。

接着就比较好构造了。

### Code

[AC 记录](https://atcoder.jp/contests/agc001/submissions/44652839)。

---

## 作者：huangkx (赞：0)

**总结**：先抓满足限制的必要条件，从必要条件入手来构造，如果一定能构造出来，这个必要条件就也是充分条件（或者也可能在构造的过程中探索到充分条件（？）），于是可以判无解。另外也要多找性质。勤画图。把情况处理（包括想）全。关键是通过必要条件、性质来限制自己构造的方向。

神仙构造题，思路自然流畅。（个人认为；但是自己看了很多题解才懂。）

一定要自己画图，勤画图。另外有些时候画图也需要一定技巧，要尽量画得易于思考、尽可能画出各种情况（尽量富于多样性）。

首先读懂题意，发现没什么直接的思路。

注意到要求任何满足 $a,b$ 限制的字符串所有字符都相同，那么就是说要求 $a,b$ 的回文关系（没有其他促使所有字符相同的因素，仅仅靠回文关系）使得所有字符相同。

那么我们转化题意，变成按照回文关系在相同的字符之间连无向边，要求整个图连通。

还是没什么直接的思路，于是探索图的形态。

- 一个长度为 $x$ 的奇回文串会连 $\frac { x - 1 } 2$ 条边，不会给回文中心连边。
- 一个长度为 $x$ 的偶回文串会连 $\frac x 2$ 条边。

我们要使 $n$ 个点连通，就至少需要 $n - 1$ 条边。而所有回文串的长度之和为 $2n$，全是偶回文的话会连 $n$ 条边，每有一个变成奇回文就会少 $\frac 1 2$ 条边。于是所有回文段（$a$ 中的和 $b$ 中的）中，奇回文段的个数不能超过 $2$。超过 $2$ 就判无解。

仅仅知道这一条信息还是难以构造（个人认为）。但是我们注意到 $a$ 中回文段不相交，$b$ 中回文段也不相交，那么一个点的度数最多是 $2$，即 $a$ 中的回文段给它一条边，$b$ 中的回文段也给它一条边；而对于奇回文段的回文中心，它们的度数是 $1$，因为要连通至少要给它一条边（偶回文），而奇回文不会给它边。

现在先思考有两段奇回文时的图的结构。

知道了这样的度数关系，我们发现两段奇回文的图一定是一条链，且链的开头和结尾分别是两个奇回文串的回文中心。

那考虑怎么把图串起来。看到回文的连边想到错位，我们尝试画一下：

- 偶回文段 $[x,y]$ 和偶回文段 $[x+1,y+1]$ 可以形成一段链，端头分别是 $x$ 和 $y + 1$（只看这一部分的话它们的度数都是 $1$，也就是说它们只被 $a$ 中的回文段或 $b$ 中的回文段覆盖，还可以被覆盖一次）。
- 奇回文段 $[x,y]$ 和偶回文段 $[x,y+1]$ 可以形成一段链，端头分别是这个奇回文段的中心和 $y + 1$，但奇回文段的中心不能再被覆盖了，$y+1$ 还能再被覆盖。
- 奇回文段 $[x,y]$ 和偶回文段 $[x+1,y]$ 可以形成一段链，端头分别是这个奇回文段的中心和 $x$，但奇回文段的中心不能再被覆盖了，$x$ 还能再被覆盖。（与第二种 **有点** 对称）

我们在这样的过程中受到启发，把还能再被覆盖的点（一些端点；不是端点的显然度数已经满了，也就是已经被覆盖两次了）作为“插头”。那么第一种构造可以放在中间来连接，第二种构造可以放在开头，第三种构造可以放在结尾，它们通过插头互相连接（插头接插头）。

现在有了基础的想法，画一画特殊情况，再想一下扩展：

- $a$ 只有两段时，直接第二种接第三种是否可行？可行。
- $a$ 只有一段时怎么办？
  - 如果 $n=1$，就直接让 $b$ 中唯一的一个元素为 $1$。
  - 否则让 $b$ 中的两个元素依次是 $1, n-1$（相当于上面的第三种结构，$a$ 中奇数配 $b$ 中偶数或 $a$ 中偶数配 $b$ 中奇数）。
- $a$ 中奇数不足 $2$ 个怎么办？在 $b$ 中构造奇数。

考虑这样拼接是否满足题目中 $a$ 中元素加起来等于 $n$ 且 $b$ 中元素加起来也等于 $n$ 的限制。

我们直接按照这种拼接构造，发现这就相当于把 $A$ 的两个奇数丢到一头一尾得到 $a$，而 $b$ 是 $a$ 复制一遍后把开头元素 $+1$，结尾元素 $-1$（减成 $0$ 就不要了，这个要特判，容易画图验证这样也能形成上面的第三种结构）。这样很巧妙，有两个好处：

- $b$ 首尾和 $a$ 首尾的奇偶性不同，而 $a,b$ 非首尾的元素都是偶数，就保证 $a$ 和 $b$ 总共的奇数个数不超过 $2$。
- 恰好把每个部分都正确地错位了。

我们注意到这样做可以满足 $a$ 只有两段和 $a$ 中奇数不足 $2$ 个的特殊情况，但满足不了 $a$ 只有一段的特殊情况。于是 $a$ 只有一段的特判即可。

发现这样就做完了，$a$ 中奇数个数 $\leq 2$ 原本是有合法构造的必要条件，但现在我们也说明了它是充分条件。

流程没想清楚的话可以看代码实现。

画的图（此题）：蚊香（在网上发现的比喻）。

这里的这种构造是我从这里学的：[题解 AT1982 【Arrays and Palindrome】 - 洛谷专栏](https://www.luogu.com.cn/article/za1z1e16)。%%%

```cpp
#include <bits/stdc++.h>
#define gc getchar
#define pc putchar
using namespace std;

namespace FastIO{
	int rd()
	{
		int x = 0, f = 1; char c = gc();
		while(c < '0' || c > '9') { if(c == '-') f = (- 1); c = gc(); }
		while(c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
		return (x * f);
	}
	void wt(int x)
	{
		if(x < 0) { x = (- x); pc('-'); }
		if(x > 9) wt(x / 10);
		pc(x % 10 + '0');
	}
}
using namespace FastIO;

const int M = 100;
int a[M + 1], na[M + 1];
vector < int > b;

void Solve()
{
	int n = rd(), m = rd();
//	vector < int > a(m + 1), na(m + 1);
	int cnt = 0;
	vector < int > od(2);
	for(int i = 1; i <= m; ++ i){
		a[i] = rd();
		if(cnt <= 1) if(a[i] & 1) od[cnt] = a[i]; // 要写 if(cnt <= 1) // 这就不能把 cnt ++ 写在里面了 // 是 od[cnt]，不是 od[cnt + 1]
		cnt += (a[i] & 1); //
	}
	if(cnt > 2){ // 是 > 2，不是 >= 2
//		puts("Impossible"); // ?
		printf("Impossible"); // ?
		return ;
	}
	int tot = 0;
	if(od[0]) na[++ tot] = od[0];
	for(int i = 1; i <= m; ++ i) if((a[i] & 1) ^ 1) na[++ tot] = a[i]; // m, not n
	if(od[1]) na[++ tot] = od[1];
	for(int i = 1; i <= m; ++ i) a[i] = na[i];
//	vector < int > b;
	if(m == 1){
		b.emplace_back(1);
		if(a[1] - 1 > 0) b.emplace_back(a[1] - 1); // 也要特判（特判就是这里的 if）
	}else{
		b.emplace_back(a[1] + 1);
		for(int i = 2; i <= m - 1; ++ i) b.emplace_back(a[i]); // m - 1, not m
		if(a[m] - 1 > 0) b.emplace_back(a[m] - 1); // 要特判（特判就是这里的 if）
	}
	for(int i = 1; i <= m; ++ i) { wt(a[i]); pc(' '); }
	pc('\n'); wt(((int)b.size())); pc('\n');
	for(int x : b) { wt(x); pc(' '); }
//	pc('\n'); // ?
}

int main()
{
	Solve();
	return 0;
}
// 看了大量题解才懂，感谢大佬们
// 不知道是不是 https://www.luogu.com.cn/discuss/758556
```

---

## 作者：hgckythgcfhk (赞：0)

考虑刻画这个问题的结构，先假设 $a$ 和 $b$ 是固定的，这个事情不太好直接描述，所以放段程序，我们按这段程序对题目中所谓的所有序列 $c$ 赋值，由于每个值是什么并不重要，所以先按 $a$ 构造一个代表元 $d$。

```cpp
int cnt=0,pos=0;
for(int i=1;i<=n;++i){
	for(int j=1;j<=(a[i]+1>>1);++j)d[++pos]=++cnt;
	int _=pos;for(int j=(a[i]+1>>1);j;--j)d[++pos]=d[_--];
}
```

这个我没运行过，可能细节上有问题，但大体意思表达清楚了，大概就是“回文着”标号。

同理按 $e$ 构造一个代表元 $d$，则对于所有的 $(i,j)$，若满足 $d_i=d_j$ 或者 $e_i=e_j$，则一定有 $c_i=c_j$，于是把所有的位置 $k$ 满足 $d_k=c_i$ 或 $e_k=c_i$ 换成 $c_i$，而且这个东西可以连锁反应，这说的不是很严谨，但大体意思我应该是表达清楚了。

考虑到这个连锁反应，发现这个相当于是维护一个并查集，把所有的相等的点的所在集合合并，如果所有序列都所有位置相等，那一定满足最后合并出来只有一个集合。

所以现在能直接维护吗？我感觉好像能写，但我不会写，所以考虑利用回文的性质。

先考虑怎么连接两段，每个点能连出两条边，特别的，对于奇数长的回文区间的中点只能连一条，这种点相当于叶子，对连通性没有任何的贡献，而且，把这个叶子缩掉会继续出现叶子，不断缩下去，发现对于每个 $b_i$ 的控制范围内不能有超过两个奇数段中点，如果恰有两个，那么该段是一个以这两个点为端点的链，这两个点不会对其他段连边，所以容易发现，$a$ 中不能有超过两个奇数。

考虑对 $a$ 中的奇数进行讨论，对于恰有两个的情况，这两个一定在两端，因为在前面的过程中发现奇数段中点只能作为端点，同样，如果恰有一个也得在端点，只不过在哪一端都可以。

现在，如果我们有一种方法能连接奇数段和偶数段，两个偶数段，偶数段和奇数段，或者两个奇数段那这个题就做完了，考虑第一段剩下一个，最后一段多选一个，然后中间整体往前移动一个位置，这样可以处理上述所有情况，现在证明：

以奇数段和偶数段为例，其他情况差不多。

> 奇数段一定在第一段，所以对于奇数段：$1,2,3,\dots,x,x-1,x-2\dots 3,2$，有 $1\to 2,2\to 3 \dots,x-1\to x$，显然成立。
> 
> 同时对于下一段，由于前面都换成了 $1$，后面编号可以映射到更小的，有：$1,2,3,\dots,x,x,x-1,\dots,3$，则 $1\to 3,3\to 5\dots,2\to 4,4\to 6\dots$，发现隔一个有边，则 $x\to x-1$ 有边，$x$ 和 $x-1$ 奇偶性不同，所以整段连通，此时后面的 $2$ 换成了 $1$。

可以发现，上面我们其实证了一个单点可以连一个偶数段并剩下一个，也证了一个单点可以连一个奇数段，同时如果右边有一个一样的单点可以继续链接，否则连不了，于是我们可以得出上述所有情况都是对的。

现在的做法很明确了：
1. 数 $a$ 有多少个奇数，超过两个判定无解。

2. 把 $a$ 的奇数放在两边。

3. 构造 $b$ 使得：

$$b_i= \begin{cases}
  a_i-1 & i = 1 \\
  a_i & 2\le i <n \\
  a_i+1 & i=n
\end{cases}$$

可以发现，奇数不够用的情况用偶数代替也是对的。

特别的，要对 $n=1$ 的情况单独谈论。

这里只放核心程序，忽略了宏定义以防止由于火车头导致无法过审，但不影响阅读。

```cpp
unsigned n,m,a[N];vint b,c[2];
void init(){cin>>m>>n;sca(a);
	for(int i=1;i<=n;++i)c[a[i]&1]+=a[i];
	if(c[1].SZ>2)cout<<"Impossible",exit(0);
	int j=0;
	for(cit&i:c[1])a[++j]=i;
	for(cit&i:c[0])a[++j]=i;
}
void solve(){init();
	if(n==1){if(m==1){cout<<"1\n1\n1";return;}
	else cout<<a[1]<<"\n2\n1 "<<a[1]-1;return;}
	cout<<a[1]<<' ';for(int i=3;i<=n;++i)cout<<a[i]<<' ';cout<<a[2]<<'\n';
	b+=a[1]+1;for(int i=3;i<=n;++i)b+=a[i];if(a[2]>1)b+=a[2]-1;
	cout<<b.SZ<<'\n';for(cit&i:b)cout<<i<<' ';
}signed main(){open;int t=1;//cin>>t;
	while(t--)solve();
}
```

---

## 作者：Guizy (赞：0)

题意：给你 $N,M$ 和一个长度为 $M$ 数列 $A$，表示 $a$ 的排列。求 $a,b$ 满足以下条件：

- $a,b$ 的数字总和是 $N$。

- $a,b$ 中的数字都为正整数。

- 所有满足以下两条的序列所有元素都是相同的：

  - 最开始的 $a_1$ 个元素, 接下来的 $a_2$ 个元素，更后面的 $a_3$ 个，等等，都是回文；

  - 最开始的 $b_1$ 个元素, 接下来的 $b_2$ 个元素，更后面的 $b_3$ 个，等等，都是回文。

其实就是让你构造 $a,b$，把每组回文里正数和倒数的第 $i$ 个两两连边，使其构成一个连通块。

首先考虑什么情况下无解。

$n$ 个点要构成连通块，必须要有至少 $n-1$ 条边（并且这 $n-1$ 条边不能有环，下文称这种边为有效边，反之为无效边），对于每一个 $A_i$，如果为奇数，那么就有一个点是无效边，被浪费。所以，有效的边数就是 $\lfloor\frac{n-\sum A_i\bmod 2}{2}\rfloor$。因为 $b$ 数组不论如何构造最多只能连出 $\lfloor\frac{n}{2}\rfloor$ 条，两个数相加即 $\lfloor\frac{2n-\sum A_i\bmod 2}{2}\rfloor$，即：当 $A_i$ 中出现 $2$ 个以上奇数时，无解。其余情况可以通过构造 $b$ 使得连出的有效边最多来保证有解。

在考虑怎么构造能使其是连通块。

我们可以通过错开一个的方式构造（如下图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/oq8y8f1t.png)

即：$b_1=a_1+1$，$b_M=a_M-1$，其他不变。为了使 $b$ 中的无效边尽可能少，我们把 $A$ 中的奇数分别放在第一位和第 $M$ 位。

这样你就可以愉快 AC 了！时间复杂度 $O(m\log m)$，当然可以把 sort 换成把奇数移动到头和尾的代码，就可以做到 $O(m)$。

```cp
#include<bits/stdc++.h>
using namespace std;

int n,m,a[100001],cnt,ans[100001];

bool cmp(int x,int y){
	return x%2>y%2;
}

int main(){
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
		if(a[i]&1) cnt++;
	}
	
	if(cnt>2)
		return printf("Impossible"),0;
	
	sort(a+1,a+m+1,cmp); cnt=0;
	//偷懒sort，但是这里的a[2]是a[M]，其余（原来的a[2]~a[M-1]）都后移一位。
	
	if(m==1){
		if(n==1) return printf("1\n1\n1"),0;
		else 
			return printf("%d\n2\n%d %d",a[1],a[1]-1,1),0;
	}
	
	printf("%d ",a[1]);	
	for(int i=3;i<=m;i++) printf("%d ",a[i]);
	printf("%d\n",a[2]);
	
	a[1]++,a[2]--;
	printf("%d\n",m-(a[2]==0));
	printf("%d ",a[1]);
	for(int i=3;i<=m;i++){
		printf("%d ",a[i]);
	}
	if(a[2]) printf("%d",a[2]);
	puts("");
		
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

我们考虑对被限制相同的字符连边，那么合法的构造即为使得建出的图为联通图。

首先考虑 $m = 1$ 时如何处理，发现对于所有 $i \in \left[0, \left\lceil\frac{n}{2}\right\rceil\right)$，若我们可以使得连通块 $\left\{i + 1, n - i\right\}$ 与连通块  $\left\{i + 2, n - i - 1\right\}$ 联通，那么我们即可构造出有解方案，进而我们考虑连边 $\left(1, n - 1\right)$，并依次为回文串边界继续建边 $\left(2, n - 2\right)$，进而可以得到形如下图的构造，可以发现其一定有解。

![](https://cdn.luogu.com.cn/upload/image_hosting/s32zmhdy.png)

通过上述分析我们可以得到，对于一个长度为 $n$ 的回文串，我们在其端点处添加 $n - 1$ 的限制即可使得其元素均相同。下面我们考虑如何扩展到 $m = 2$ 的情况，一个直观的想法是我们令 $b$ 序列为 $\left\{a_1 - 1, 2, a_2 - 1\right\}$。发现这样构造其实是通过一个长度为 $2$ 的小回文串使得其相同的。但是这样难于扩展到 $m$ 更大的情况，我们考虑另一种构造。

首先我们取 $b_1 = a_1 - 1$，接下来我们不妨删去字符串的前 $a_i - 1$ 个字符，因此我们只需要使得剩余的字符均相同那么即可得到一组合法的构造，那么我们现在的 $a$ 序列实际上为 $\left\{1, a_2\right\}$ 发现其与上述 $m = 1$ 情况时的 $b$ 序列相似，因此我们取 $b_2 = a_2 + 1$ 即可构造出一组合法方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/uryjix98.png)

考虑扩展到 $m > 2$ 的情况。我们继续使用上述删除前缀的思想，那么问题转化为了 $a = \left\{1, x\right\}$ 的情况，另外我们还要求 $\sum b = x$。

我们考虑有解的必要条件，即至少存在 $n - 1$ 条边，否则一定无解。

已知 $a$ 数组已经贡献了 $\left\lfloor\frac{x}{2}\right\rfloor$ 条边，而可以发现 $b$ 至多贡献 $\left\lfloor\frac{x}{2}\right\rfloor$ 条边，因此若 $x$ 为奇数，那么我们至多有 $x - 2$ 条边，因此我们在这里只考虑 $x$ 为偶数的情况，后文会证明其他情况一定无解。现在我们已经限制了 $x$ 为偶数，不难发现若 $a = \left\{1, x\right\}, b = \left\{x, 1\right\}$ 那么一定合法。因此若 $a$ 中不存在超过两个奇数，我们将这些奇数放到 $a_1$ 或 $a_n$ 的位置上，剩余部分按上述方法处理即可。

进而我们得到了一组合法的构造方式，对于 $i in \left[2, n - 1\right]$，令 $b_i = a_i$，并且 $b_1 = a_1 - 1, b_2 + a_2 + 1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2zf3hfg.png)

发现我们仅剩下了 $a$ 多与两个奇数的情况未考虑，我们可以发现若 $a$ 中存在多于两个奇数，那么我们一定无法得到 $n - 1$ 条边，进而一定无解。

复杂度为 $\mathcal{O}(n)$。

---

