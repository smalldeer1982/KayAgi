# Hard Process

## 题目描述

给你一个数组，其中有n个元素。每个元素不是0就是1。
现在可以进行k次操作，每次操作可以改变数组中的一个元素（只能改成0或1）。
请你求出操作后最长连续1的序列的长度，并输出操作后的序列。

## 样例 #1

### 输入

```
7 1
1 0 0 1 1 0 1
```

### 输出

```
4
1 0 0 1 1 1 1
```

## 样例 #2

### 输入

```
10 2
1 0 0 1 0 1 0 1 0 1
```

### 输出

```
5
1 0 0 1 1 1 1 1 0 1
```

# 题解

## 作者：引领天下 (赞：17)

看到C++的都是二分的尺取法表示不服

这题朴素想法：枚举l，r，暴力求[l,r]中0的个数是否小于k，复杂度$O(n^{3})$

我们想想有没有什么优化的办法

很明显，对于一个含0的区间，我们让区间中的0都填满是最优的

于是维护一段区间，保证区间中的0的个数≤k就可以

于是就可以对于0的个数≤k时右移右端点，增添新的位置，扩大区间；

当[l,r]中0的个数＞k时我们没有必要再回到l从头开始，可以只右移l，到[l,r]中0的个数≤k时为止（其实最后肯定=k，自己想想为什么！）

于是复杂度降到了线性的$O(n)$，或成此题最优解？

并不长的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005],k,n,ans,cnt,ml,mr;
int main(){
    scanf ("%d%d",&n,&k);
    for (int i=1;i<=n;i++)scanf ("%d",&a[i]);
    for (int l=1,r=1;r<=n;r++){//持续右移右端点
        cnt+=!a[r];
        if (cnt>k){
            cnt-=!a[l];
            l++;
        }//长了就右移左端点
        if (r-l+1>ans)ans=r-l+1,ml=l,mr=r;
    }
    for (;ml<=mr;ml++)a[ml]=1;
    printf ("%d\n",ans);
    for (int i=1;i<=n;i++)printf ("%d ",a[i]);
}
```

---

## 作者：Zxsoul (赞：2)

这题我的做法还是蛮暴力的，只要为了练码力来的

这里说一下思路：

用结构体记录每个 $0$ 

1. 自己位置：$pt$ 
2. 左边最近零的位置：$id$
3. 右边最近零的位置：$rid$
4. 自己是否已经变成 $1$: $flag$
5. 距左右最近零的区间内 $1$ 的个数：$l,r$

当我们进行更改操作时，找出左右$1$的个数总和最大的 $0$,这必然是最优的结果（很显然），当我们把当前位置上的 $0$ 变成 $1$时，更需要更改他的左右位置的零的左右的1的数量(很绕),暴力就好啦
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 1e7+10;
const int B = 1e4+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

struct node{int l,r,id,rid,flag,pt;}a[B];
int n,k,b[B],cnt;

main()
{
	int x;
	n=read();k=read();
	b[0]=inf;
	int js=0,p=0,top=1;
	for (int i=1;i<=n;i++)
	{
		b[i]=read();
//		if (p==0 && b[i]==0) {top=i;p=1;}
		if (b[i]==1) js++;
		else if (b[i]==0) 
		{
			a[cnt+1].id=cnt;
			a[++cnt].l=js;
			a[cnt].pt=i;
//			a[cnt].id=top;
//			top=i;
			js=0;		
		}
	}
	int s=cnt;
	p=0,top=n,js=0;
	for (int i=n;i>=1;i--)
	{
//		if (p==0 && b[i]==0) {top=i;p=1;}
		if (b[i]==1) js++;
		if (b[i]==0)
		{
			if (!(s-1)) {a[s].r=js;break;} 
			a[s-1].rid=s;
			a[s--].r=js;
//			a[s--].rid=top;
//			top=i;
			js=0;
		}
	}
	
		for (int j=1;j<=k;j++)
		{
			int id,cmp=0,s=cnt;
			for (int i=cnt;i>=1;i--)
			{
				if (cmp<(a[i].l+a[i].r)) 
				{
					cmp=a[i].r+a[i].l;
					id=i;
				}
			}
			int ID=a[id].id;
			int rr=a[id].rid;
			a[ID].r+=(a[id].r+1);
			a[ID].rid=a[id].rid;
			a[rr].l+=(a[id].l+1);
			a[rr].id=a[id].id;
			a[id].flag=1;
		}
	for (int i=1;i<=cnt;i++) if(a[i].flag==1) b[a[i].pt]=1;
	int ans=0;
	js=0;
	for (int i=1;i<=n;i++)
	{
		if (b[i]==1) js++;
		if (b[i]==0) 
		{
			ans=max(ans,js);
			js=0;
		}
	}
	ans=max(js,ans);
	printf("%lld\n",ans);
	for (int i=1;i<=n;i++) printf("%lld ",b[i]);
}
```

---

## 作者：惟有泪千行 (赞：2)

~~我队列必须有排面~~

#### 题目描述：

给你一个01序列，有k次机会可以将0变成1，求最后可以得到的最长的连续1序列的长度并输出。

#### 思路一：暴力枚举

复杂度O(n^3),每次暴力求[l,r]中0的个数是否小于k，显然复杂度不对，并不能通过此题

#### 思路二：维护队列

每次维护队列里的0的个数，总长度，从左往右扫一遍，如果是0就将0的个数++，如果队列里的0的个数小于等于总次数，就可以与最大值比较了（注意是小于等于，我在这里被卡了一次QAQ），如果大于次数，就开始踢掉队首的元素，直到队列里的0的个数等于总次数，具体实现就看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,cnt,a,n,m,maxn=0,ls;
int b[300010];
queue<int>q;
inline int read()//快读 
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
	{
		b[i]=read();
		q.push(b[i]);//入队 
		if(b[i]==0)++ans;//累加0的个数 
		++cnt;
		while(ans>m)//如果0的数量大于m，就弹出队首 
		{
			if(!q.front())--ans;
			q.pop();
			--cnt;
		}
		if(ans<=m&&cnt>maxn)//记录最大的长度和起始位置 
		{
			maxn=cnt;
			ls=i-maxn+1;
		}
	}
	printf("%d\n",maxn);// 
	for(register int i=1;i<=n;++i)//输出序列 
	{
		if(i>=ls&&i<=ls+maxn-1)//改后序列 
		{
			printf("1 ");
		}
		else printf("%d ",b[i]);
	}
	return 0;
}
```
复杂度O(n)，完全可过


---

## 作者：Lucifer_Bartholomew (赞：2)

# ~~二分答案~~
对于一段序列里面，若0的个数小于k，则说明右边界可以向右拓展，所以只需要枚举左边界就行了
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,k,pos,a[300010],in[300010];
bool check(int len)
{
    for(int i=1;i<n-len+2;++i)
        if(a[i+len-1]-a[i-1]>=len-k)
		{
            pos=i;
            return 1;
        }
    return 0;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
	{
    	scanf("%d",&in[i]);
    	a[i]+=a[i-1]+in[i];
    }
    for(int i=n+1;i<300010;++i)
		a[i]=a[i-1];
    if(n==k)
	{
    	printf("%d\n",n);
    	for(int i=1;i<=n;++i)
			printf("1 ");
    	return 0;
    }
    int ans=-1,l=k,r=n;
    while(l<=r)
	{
        int mid=l+((r-l)>>1);
        if(check(mid))
		{
        	ans=mid;
        	l=mid+1;
        }
		else r=mid-1;
    }
    printf("%d\n",ans);
    int p=1;//输出注意一下
    for(;p<pos;++p)
		printf("%d ",in[p]);
    for(;p<=min(n,pos+ans-1);++p)
		printf("1 ");
    for(;p<=n;++p)
		printf("%d ",in[p]);
	puts("");
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：暗ざ之殇 (赞：1)

## 洛咕网课 (逃

这是洛咕网课上的一道题目，听完讲师的思路之后就过来切了。

### 题解
如果直接枚举左右端点，再统计区间内 $0$ 的数量是否 $<=k?O(n^3)$

考虑对于区间 $[l,r]$ 和区间 $[l,r+1]$，$0$ 的数量差仅取决于 $a[r+1]$，所以枚举右端点时 $0$ 的数量可以直接转移。$o(n^2)$。

因为实际上我们在贪心地选取一个最长的 $0$ 的个数不多于 $k$ 的区间，所以当右端点取得的 $0$ 的个数大于 $k$ 的位置时就可以不用继续向右枚举了，而我们右移左端点时也可以用之前统计的 $0$ 的数量直接转移，从区间 $[l,r]$ 转移到区间 $[l+1,r]$ 仅取决于 $a[l]$。

这样我们就得到了一个“不停把右端点向右移，$0$ 数量 $>k$ 时就右移左端点直到 $0$ 数量 $<=k$” 的方法，时间复杂度 $O(n)$。

这种做法有一堆名字，“$Two-Pointers$”“尺取法”“滑动窗口”$......$

$Code:$

```
#include<iostream>
#include<cstdio>
using namespace std;
const int N=3e5+5;
int n,m,l,r,L,R,sum,ans;
int a[N];
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(m==0)                   //注意特判m=0的情况,此时的问题转化为求最长连续子序列 
	{
		int now=0;             //记录目前的连续子序列的长度 
		for(int i=1;i<=n;i++)
		{
			if(a[i]) now++;    
			else now=0;
			ans=max(ans,now);  //连续子序列断了,now要清空 
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		return 0;
	}
	l=r=1;sum=a[1]==0;         //sum表示[l,r]内有多少个0 
	while(l<=r&&r<=n)
	{
		if(sum<=m)             //如果[l,r]内0的个数小于sum,那么我们更新一下答案,并继续将右端点右移 
		{
			if(r-l+1>ans)
			{
				L=l;R=r;       //记录将哪个答案区间进行修改 
				ans=r-l+1;
			}
			r++;
			sum+=a[r]==0;      //维护新区间的信息 
		}
		else                   //否则右移左端点 
		{
			sum-=a[l]==0;      //维护新区间的信息 
			l++;
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	{
		if(L<=i&&i<=R) printf("1 ");  //将更改后的区间0变为1 
		else printf("%d ",a[i]);  //其余的按原来的输出即可 
	}
	return 0;
}
```

$Another$ $Solution:$

由上面的贪心思路可知，对于每一个区间左端点 $l$，我们只关心区间内 $0$ 的个数 $<=k$ 的最靠右的右端点 $r$，而由于 $r$ 越靠右，区间内 $0$ 的个数不会减少，所以最优的 $r$ 肯定只有 $1$ 个，我们可以通过预处理来求：

$S[i]:$ 表示前 $i$ 个数中有多少个 $0$(包含$i$)，那么对于区间 $[l,r]$ 内的 $0$ 的个数，我们可以利用前缀和思想通过 $S[r]-S[l-1]$ 来 $O(1)$ 算出。

那么如何 $O(1)$ 地求出最优的 $r$ 呢？

我们再设 $r[i]$ 记录在一些前缀和为 $i$ 的数中最大的那个数是多少，注意前缀和是记录的 $0$ 的个数。

**这样的话，对于一个 $l$，它的最优右端点一定是 $r[S[l-1]+k]$。**

解释一下：$S[l-1]$ 是 $l-1$ 前面有多少个 $0$，$k$ 是最优情况下区间 $[l,r]$ 内 $0$ 的数量，相加就是 $r$ 前面有多少个 $0$，及 $r$ 的前缀和我们就可以确定出来了，再通过上面的数组就可以求得这个最优的 $r$。

注意一个细节：当整个序列的 $0$ 的数量 $<k$ 时，我们是找不到 $r[S[l-1]+k]$ 的，所以如果 $r[i]==0$ 我们将其赋值为 $r[i]=n$，表示区间的右端点最大是 $n$。

时间复杂度 $O(n)$。

$Code:$
```
#include<iostream>
#include<cstdio>
using namespace std;
const int N=3e5+5;
int n,m,L,R,ans;    //[L,R]是最优的修改区间 
int a[N],S[N],r[N]; //S[i]表示i前面有多少个0,r[i]记录在一些前缀和为i的数中最大的那个数是多少 
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		if(!a[i]) S[i]=S[i-1]+1;   //算前缀和 
		else S[i]=S[i-1];
		r[S[i]]=max(r[S[i]],i);    //更新一下r数组 
	}
	for(int i=1;i<=n;i++)
	    if(!r[i]) r[i]=n;          //将r[i]=0的部分赋值为r[i]=n 
	for(int i=1;i<=n;i++)          //枚举左端点 
	{
		if(r[S[i-1]+m]-i+1>ans)    //贪心地找出了右端点r[S[i-1]+m] 
		{
			L=i;R=r[S[i-1]+m];     //如果更优就更新答案 
			ans=r[S[i-1]+m]-i+1;
		}
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)          
    {
    	if(L<=i&&i<=R) printf("1 ");  //注意将修改区间全部输出1 
    	else printf("%d ",a[i]);   //其余的按原来的输出即可 
	}
	return 0;
}
```


---

## 作者：Derpy (赞：1)

# 一个~~简单的~~二分加滑动窗口

先简单说一下思路吧，二分枚举窗口的宽度x然后在整个数列中从左往右扫描每一个长度为x的连续数列，一直找到最长的满足情况的数列为止

每次扫描时间复杂度为n，logn次扫描，总的算下来也就是n(logn)

详细说一下关于滑动窗口实现的原理吧，就是在一个长度为n的数组中找找长度为x的满足条件的连续序列，我们先把前x个扫描一遍，把里面出现过的1的数量记录下来，0的数量也记录下来，然后开始往后更新每次更新可以看作是去掉头位置上的那个数,然后加上结尾后的那个数，一直扫描到最后，中途如果有满足条件的直接return 1就好了（这有一道原理类似的可以看看[P1638 逛画展](https://www.luogu.org/problemnew/show/P1638)）

代码附上
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[300005];
int n,k;
int l,mid,r,ans;
int head,tail;//head和tail记录所需数列的首尾 
int mark[2];//mark[0]表示0在队列中出现的次数，mark[1]同理 
bool check(int x)
{
    memset(mark,0,sizeof(0));
    for(int i=1;i<=x;i++)
    {
        mark[a[i]]++;
    }
    if(mark[0]<=k)//如果一开始就满足的话直接退出 
    {
        head=1;tail=x;//那当然就是从第一个开始到第x个了 
        return 1;
    }
    for(int i=x+1;i<=n;i++)//i表示的是序列的尾巴的位置 
    {
        mark[a[i-x]]--;//去掉开头的那个数 
        mark[a[i]]++;//加上结尾的那个数 
        if(mark[0]<=k) 
        {
            head=i-x+1;tail=i;//尾巴是i,头就是i-x+1 
            return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    l=0;r=n;//长度至少 为0(全是0还不准改)，最多为n(全是1) 
    while(l<=r)//标准的二分板子 
    {
        mid=(r+l)>>1;
        if(check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
    }
    printf("%d\n",ans);//输出长度 
    for(int i=1;i<=n;i++)
    {
        if(i>=head&&i<=tail)//如果在队列中的话那肯定已经被我们改成1了 
        {
            printf("1 ");
        }
        else
        {
            printf("%d ",a[i]);//不在队列中的话就保持原状 
        }
    }
    return 0;
}
```

---

## 作者：shame_djj (赞：1)

姑且算是一遍 AC，写篇题解纪念一下

原题链接[CF660C 【Hard Process】](https://www.luogu.org/problem/CF660C)

滑动窗口，时间复杂度 O（n），也就是所谓的双指针

我就奇了怪了，为什么总是有人不知道为什么就给时间复杂度多了一个 log

是因为在他们的潜意识中，滑动窗口的长度必须是固定的，左端点和右端点必须同时移动，

但其实并不如此

滑动窗口是不一定非得左右端点同时移动的

我们每次在滑动的时候，只滑动一个端点就好了

代码也不是很长

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 3e5 + 10;

inline int read () {
	char c = getchar(); int x = 0, f = 1;
	for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
	for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f;
}

int n, k, ans, ansl, ansr;
int a[maxn];

void djj_lxy () {
	n = read(), k = read();
	for (register int i = 1; i <= n; i ++)
		a[i] = read();
	int l = 1, r = 0, s = 0;
	for (; r <= n; ) {
		if (r < l) s += a[++ r];
		if (r - l + 1 <= s + k && r - l + 1 > ans)
			ans = r - l + 1, ansl = l, ansr = r;
		if (r - l + 1 <= s + k)
			s += a[++ r];
		else
			s -= a[l ++];
	}
	printf ("%d\n", ans);
	for (register int i = ansl; i <= ansr; i ++)
		a[i] = 1;
	for (register int i = 1; i <= n; i ++)
		printf ("%d ", a[i]);
}

int main () {
	djj_lxy ();
}
```

有一道类似的题[CF701C 【They Are Everywhere】](https://www.luogu.org/problem/CF701C)

和本题基本上是一个思路了

滑窗可做

~~或者你实在是想写二分我也不拦着，也没法儿拦~~

最后祝大家 CSP-S rp++

也希望自己能更努力一些，加油

---

## 作者：wangyibo201026 (赞：0)

## 暴力

考虑暴力，枚举序列中所有连续子序列的 $l$ 和 $r$，最好的方法也需要 $O(N^2)$ 的时间（前缀和维护），所以考虑优化。

## 双指针

我们发现，题目简意就是找一个最长的含有 $k$ 个 $0$ 子序列的长度，并全部改成 $1$，那么就有点像双指针了。

这道题目在优化的关键是：当已选子序列后面还有 $1$ 时，可以继续延伸下去，就没必要再枚举了。那么在双指针上怎么实现呢？

我们可以再添加一个循环，循环往后找 $1$。那么这样会不会影响复杂度呢？
我们可以这么想，你循环找的 $1$ 越多，那么下一次找的 $r$ 就会越大，循环次数就会越少，因此不影响时间复杂度。

最后注意一些循环变量的问题就可以了。

## 代码

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, k, a[300005], tot, ans = -1e9, zi, zj;

void Solve(){
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  for(int i = 1, j = 1; i <= n; i++){    //双指针
    for(; j <= n && tot < k; j++){
      if(!a[j]){    //0 的个数
        tot++;
      }
    }
    for(; j <= n; j++){
      if(!a[j]){     //往后延伸
        break;
      }
    }
    if(j - i > ans && tot <= k){    //如果合法
      ans = j - i;      //统计答案
      zi = i;
      zj = j - 1;
    }
    if(!a[i]){     //注意，i 最后还多加了一次
      tot--;
    }
  }
  cout << ans << endl;
  for(int i = 1; i <= zi - 1; i++){
    cout << a[i] << " ";
  }
  for(int i = zi; i <= zj; i++){
    cout << 1 << " ";
  }
  for(int i = zj + 1; i <= n; i++){    //颓废的输出
    cout << a[i] << " ";
  }
}

int main(){
  Solve();
  return 0;
}
```

---

## 作者：Swerve (赞：0)

## 方法：直接记录 $0$ 的位置再枚举
可能比用两个指针移来移去的方法更好理解也更容易实现。
### 题意简述
给定一个由 $0$ 和 $1$ 构成的序列，将其中有限个 $0$ 变成 $1$，使得出现连续的 $1$ 的个数最多。
### 题目分析

（虽然被我写起来这么长还有各种字母，但其实真的很好理解 $qwq$）
- 首先，这 $k$ 次操作要尽可能用完。
- 接下来，可以发现，我们选择操作的这些 $0$，在位置上一定是连续的。换句话说，假设**只**给序列中的 $m$ 个 $0$ 按顺序标号为 $a_1,a_2,\ldots,a_m$，那么要修改的是其中 $a_i,a_{i+1},\ldots,a_{i+k-1}$ 这 $k$ 个 $0$。因为这样，这些被修改的 $0$ 才能 “专心地” 让一段 $1$ 的序列更长。
- 于是，我们可以枚举 $i$，计算修改 $a_i,a_{i+1},\ldots,a_{i+k-1}$ 这 $k$ 个 $0$ 时，形成的连续为 $1$ 的序列长度。
- 那怎样计算呢？在这一段区间中所有的 $0$ 已经被全部替换成 $1$，所以我们只需找到**区间两端**的 $0$ ，也就是 $a_{i-1}$ 和 $a_{i+k}$。
- 如果我们在读入时就**预处理**出每个 $0$ 出现的**位置** $pos_i$，那么这个连续为 $1$ 的序列长度就是其两端的 $0$ 的位置相减再 $-1$，表示成 $pos_{i+k}-pos_{i-1}-1$。于是，我们枚举 $i$ 去找到上式的最大值就可以啦！
- 最后，如果连续的 $1$ 出现在序列的头尾，两端不是 $0$ 了，怎么处理？方法也很简单：处理边界值，使 $pos_0=0$, $pos_{m+1}=n+1$。这相当于给序列在头尾都添加了一个 $0$。

### 代码实现
代码的实现难度并不大，然而第一次交上去之后我第 $30$ 个点 WA 掉了......
我的循环是这样写的：（$cnt$ 用作下标维护 $pos$ 数组，因为 $pos_0$ 和 $pos_{m+1}$ 都要修改，所以这里的 $cnt=m+1$。）

```cpp
	for(int i=1;i+k<=cnt;i++)
		if(pos[i+k]-pos[i-1]-1>ans) 
		ans=pos[i+k]-pos[i-1]-1,r=pos[i+k],l=pos[i-1];
```

ta 在应该输出 $1$ 的点上输出了 $0$，也就是说 $ans$ 的值好像并没有被更新。为什么？

于是我发现，在 $k\le cnt$，也就是全部 $0$ 的数量少于 $k$ 的时候，不会进入更新 $ans$ 值的循环。因为我们默认了 " $k$ 次操作要用完" ，但此时这句话是不成立的。**不过只要我们加入特判，在这种情况下把序列里的所有 $0$ 改成 $1$ 就可以啦。** 

AC 代码如下，里面也有一些比较详细的注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
int n,k,a[N],pos[N],ans=0,cnt=0,l,r;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(!a[i]) pos[++cnt]=i;//pos数组记录0出现的位置
	}
	pos[0]=0;//这一句删去也可,当做有一个0出现在0号位置 
	pos[++cnt]=n+1;//当做有一个0出现在n+1的位置
	for(int i=1;i+k<=cnt;i++)//枚举k+1个0头尾位置相差最大的情况，并用l,r记录区间的范围 
		if(pos[i+k]-pos[i-1]-1>ans) 
        	ans=pos[i+k]-pos[i-1]-1,r=pos[i+k],l=pos[i-1];
	if(cnt<=k) l=0,r=n+1,ans=n;//0的个数比可改的次数还少的情况，因为此时修改次数不等于k了所以要特判下 
	for(int i=l+1;i<r;i++) if(!a[i]) a[i]=1;//修改区间，区间两端的0不可以算进去的 
	printf("%d\n",ans);
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```
时间复杂度是很明显的 $O(n)$。

若加读优的话，最慢的点也才跑 $62ms$。虽然还不是最快的，但也很好了吧 $qwq$

 作为自己的第一篇题解，我觉得写的还是挺用心的（逃
 ### 感谢观看！

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF660C)

看到dalao们都用什么尺取法、滑动窗口，像我这种蒟蒻表示看不懂（虽然很厉害）。于是，就有了这篇二分题解。

思路：二分区间长度，维护一个前缀和，判断每一个为当前长度的区间是否可以用至少 $k$ 次操作修改出，如果可以，就记录修改位置和区间长度。然后继续进行二分。

方法：

- $1.$ 输入序列；

- $2.$ 二分寻找区间长度；

- $3.$ 判断是否可行；

- $4.$ 根据上一步结果更新答案并修改范围，同时记录修改起点；

- $5.$ 继续二分。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long//个人习惯 
using namespace std;
LL ans,n,k,a[300005],sum[300005];//ans是答案，n、k如题意，a数组是原序列，sum数组是一个前缀和 
LL l=1,r,mid,p;//l、r和mid分别是二分的左右区间和当前枚举的长度，p是能修改出的为当前长度的第一个区间的起点 
int check(LL x)//check函数是用来判断的 
{
    for(int i=1;i<=n-x+1;i++)//因为长度是x，所以起点枚举到n-x+1就行了 
    {
        if(x-(sum[i+x-1]-sum[i-1])<=k)//如果当前区间内需修改成1的数的个数不大于k 
		{
			p=i;//记录起点 
            return 1;//可行 
        }    	
	}
    return 0;//不可行 
}
int main()
{
	cin>>n>>k;//输入 
	r=n;//右区间为序列长度（应该比较好理解吧） 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];//计算前缀和 
	}
	while(l<=r)//二分板子 
	{
		LL mid=(l+r)/2; 
		if(check(mid))//如果可行 
		{
			ans=mid;//更新答案 
			l=mid+1;//缩小上界 
		}
		else//如果不可行 
		{
			r=mid-1;//扩大上界 
		}
	}	
	cout<<ans<<endl;//输出答案  
	for(int i=p;i<=p+ans-1;i++)
	{
		a[i]=1;//修改这个区间 
	}	
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<" ";//输出修改后的序列 
	}
	return 0;//结束程序 
}
```

---

## 作者：DPair (赞：0)

提供一种奇奇怪怪的队列优化 $DP$ （~~递推？~~）的解法。复杂度还是比较优秀的，主要是好懂。

## 【思路】

### 【求解】
首先设计状态：

$$
dp[i][j] 
$$

表示到第 $i$ 个数变了 $j$ 个 $0$ 的 **以第i个数结尾** 的最长连续 $1$ 串长度。

方程很显然：

$$
dp[i][j]=dp[i-1][j-1]+1,dp[i][0]=0(a[i]=0)
$$
$$
dp[i][j]=dp[i-1][j]+1(a[i]=1)
$$

最后取 $max\{dp[i][k]\}$ 即可。

这是 $O(n^2)$ 的，考虑优化。

首先 $dp[i]$ 这一维显然可以滚掉不要。

然后发现 $dp$ 数组的变化要么是 **不变然后加1** ，要么是 **整体移动一位，然后加1，然后只对一个数清零** 。

因此想到用队列优化。

维护一个队列，队首是 $dp[k]$ ，队尾是 $dp[0]$ 。

对于整体加 $1$ 的操作，外置一个变量 $base$ ，保存总共加过几次 $1$ 即可。

对于移动一位的操作，直接删掉队首即可，这是因为没有 $dp[k+1]$ 这一项，所以移动后元素个数是 $-1$ 的，而且这样一来 $dp[k-1]$ 就会刚好变成 $dp[k]$ ，其他元素同理。

然后由于新加进来的 $dp[0] = 0$ ，而队列里的每一个数其实都不是其真实值，而是 **真实值 - base（定义见上文）**，因此我们把 $-base$ 入队就完成了 $dp[0]=0$ 操作。

至此完成了 $O(n)$ 求出解的算法，下面考虑输出。

### 【输出】
最后输出这个变化后的序列其实也不难。

现在我们已经知道了末尾最长可以有几个连续的 $1$ ，设这个答案为 $ans$ 。

我们自然也知道这个答案是在 $i=$ 多少的时候取出来的，假设是在 $i=pos$ 时取出来的。

那么只要使得满足 $i\in[pos-ans+1,pos]$ 的所有 $a[i]$ 为 $1$ 即可，因为 $ans$ 已经可以确定是一组解，那么把这 $ans$ 个数全部变为 $1$ 一定满足题意，即一定为一组解。

剩下的数照常输出即可。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, ans, pos, base;
int a[300005];
queue <int> q;
int main(){
    scanf("%d%d", &n, &k);
    while(k --) q.push(0);
    q.push(0);
    for (register int i = 1;i <= n;i ++){
        int x;
        scanf("%d", &x);
        a[i] = x;
        base ++;
        if(!x){
            q.pop();q.push(-base);
        }
        if(ans < q.front() + base){
            ans = q.front() + base;
            pos = i;
        }
    }
    printf("%d\n", ans);
    for (register int i = 1;i <= n;i ++){
        if(i >= pos - ans + 1 && i <= pos) printf("1 ");
        else printf("%d ", a[i]);
    }
    putchar(10);
}
```

---

