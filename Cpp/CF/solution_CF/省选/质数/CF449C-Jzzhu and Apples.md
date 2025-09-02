# Jzzhu and Apples

## 题目描述

Jzzhu has picked $ n $ apples from his big apple tree. All the apples are numbered from $ 1 $ to $ n $ . Now he wants to sell them to an apple store.

Jzzhu will pack his apples into groups and then sell them. Each group must contain two apples, and the greatest common divisor of numbers of the apples in each group must be greater than 1. Of course, each apple can be part of at most one group.

Jzzhu wonders how to get the maximum possible number of groups. Can you help him?

## 样例 #1

### 输入

```
6
```

### 输出

```
2
6 3
2 4
```

## 样例 #2

### 输入

```
9
```

### 输出

```
3
9 3
2 4
6 8
```

## 样例 #3

### 输入

```
2
```

### 输出

```
0
```

# 题解

## 作者：pufanyi (赞：6)

[官方题解](https://codeforces.com/blog/entry/13112)说得很简单。就是枚举从大到小质因数$x$（如果$2x\ge n$显然就不用管了），找出所有之前没有匹配过得$x$的倍数，如果是偶数个就两两匹配，否则把$2x$除去即可。

那为什么这样是对的呢？

我们来看最后枚举到$x=2$的情况。如果有偶数个，那正好可以两两匹配，显然最优。如果是奇数个，那我们发现所有**可能被匹配的数**（即所有枚举到的数）有奇数个，即我们至少需要扔掉一个。现在我们只扔掉了一个（因为之前除去的$2x$都在此时被匹配了），所以这种情况是最优的。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, prime[maxn >> 1], p[maxn], cnt;

inline void oula(int n)
{
    cnt = 0;
    for(int i = 2; i <= n; ++i)
    {
        if(!p[i])
            prime[++cnt] = i;
        for(int j = 1; j <= cnt && prime[j] * i <= n; ++j)
        {
            p[prime[j] * i] = 1;
            if(!(i % prime[j]))
                break;
        }
    }
}

int aa[maxn], cntt, hv[maxn];
int ans[maxn][2], anss;

int main()
{
    scanf("%d", &n);
    oula(n >> 1);
    for(int i = cnt; i; --i)
    {
        cntt = 0;
        for(int j = prime[i]; j <= n; j += prime[i])
            if(!hv[j])
                aa[++cntt] = j;
        if(cntt & 1)
        {
            swap(aa[cntt], aa[2]);
            cntt--;
        }
        for(int j = 1; j <= cntt; j += 2)
        {
            hv[aa[j]] = hv[aa[j + 1]] = 1;
            ans[++anss][0] = aa[j];
            ans[anss][1] = aa[j + 1];
        }
    }
    printf("%d\n", anss);
    for(int i = 1; i <= anss; ++i)
        printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}
```

---

## 作者：Day_Dreamer_H (赞：3)

# CF449C 题解
## 题目大意
将 $[1,n]$ 分组使得每一组的最大公约数大于 $1$，输出最多组数和方案。
## 思路
如果要分成尽可能多组的话，两两分组肯定是最省的，而且我们要尽可能的不浪费每一个数。

那对于一些大质数的倍数，它的质因数拆分方式较少，为了用上肯定要优先分配。

那我们不如从大到小枚举质数 $x$，$[1,n]$ 中所有 $x$ 的倍数个数如果是偶数，那最好不过，直接两两分组结束。如果是奇数的话，我们应该留下 $2x$，为什么？

这里可以提供一个很不严谨的解释，因为 $2x$ 的质因数已经只剩下 $2$ 和 $x$ 了，但是 $2$ 的倍数最多，也最有可能可以重新匹配。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool vis[100005],used[100005];
int prime[10005],pos;
int counter;
pair<int,int>result[100005];
stack<int>s;
int main(){
	cin>>n;
	for(int i = 2;i<=100001;i++){
		if(vis[i])continue;
		prime[pos++] = i;
		for(int j = i+i;j<=100001;j+=i){
			vis[j] = true;
		}
	}
	for(int i = pos-1;i>=0;i--){
		if(prime[i]*2>n)continue;
		for(int j = prime[i]*2;j<=n;j+=prime[i]){
			if(used[j])continue;
			s.push(j);
			used[j] = true;
		}
		s.push(prime[i]);
		while(s.size()>1){
			int x = s.top();
			s.pop();
			result[++counter] = make_pair(x,s.top());
			s.pop();
		}
	}
	cout<<counter<<endl;
	for(int i = 1;i<=counter;i++){
		cout<<result[i].first<<" "<<result[i].second<<endl;
	}
}
```

---

## 作者：Jμdge (赞：3)


## 题意简述
```

给出正整数n,你要把1-n之间的正整数分成尽可能多组,
使得每一组两个数的最大公约数大于1;
输出能分成最多组的个数,
并按任意顺序输出每组的两个数.
```
（无耻安利博客：[Judge's Class](https://www.cnblogs.com/Judge/p/9859989.html)）



很妙的一道题。


首先我们考虑去处理每个质数的倍数，那么这个质数一定是小于等于 n/2 的，不然它在 n 的范围内是不会有倍数的。

那么我们先把 $1~n/2$ 范围内的所有质数筛出来。

# 枚举质数
然后我们要怎么用质数去处理答案呢？

首先我们从大到小枚举这些质数，然后去枚举它的倍数。

然鹅这样复杂度不会炸么？不会。 $O(\sigma_{i=2}^{n/2}n/i)$ 的复杂度吧，而且还远达不到。

信仰一下应该是过得了的，实际上确实也过了。



# 处理倍数
然后我们再考虑如果这些倍数该怎么处理。

我们首先看这些倍数有没有被使用过，没有的话就入栈。


# 最优性解释
那么为什么能用就入栈的解法最优呢？

其实很简单，因为当前枚举那个数可以被当前的质数整除，那么该数与当前枚举质数的倍数去匹配肯定不会产生更劣的结果。

## 特殊情况
那么如果有数字剩下来呢？

如果说当前枚举质数的未使用过的倍数有奇数个，那么我们可以将第 2 个倍数与最后一个换一下，然后弹出栈，标记为未使用。

为什么这样做能达到最优？

## 感性理解
考虑第二个倍数一定是 2 的倍数，那么把他弹出的话就可以和 2 的倍数去匹配，而且我们每次遇到奇数个的情况都是弹 2 的倍数，那么这些多余的数就可以凑一块儿了。


```
 1 //by Judge
 2 #include<vector>
 3 #include<cstdio>
 4 #include<iostream>
 5 #define P make_pair
 6 using namespace std;
 7 const int M=1e5+11;
 8 char sr[1<<21],z[20];int C=-1,Z;
 9 inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
10 inline void print(int x,char chr='\n'){
11     if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
12     while(z[++Z]=x%10+48,x/=10);
13     while(sr[++C]=z[Z],--Z);sr[++C]=chr;
14 } int n,cnt,ans,top,prim[M],is[M],vis[M],num[M];
15 pair<int,int> tmp[M];
16 inline void prep(){
17     for(int i=2;i<=n>>1;++i){
18         if(!is[i]) prim[++cnt]=i;
19         for(int j=1;j<=cnt&&i*prim[j]<=n/2;++j){
20             is[i*prim[j]]|=1;
21             if(i%prim[j]==0) break;
22         }
23     }
24 }
25 int main(){
26     scanf("%d",&n),prep();
27     for(int i=cnt;i;--i){ top=0;
28         for(int j=prim[i];j<=n;j+=prim[i])
29             if(!vis[j]) num[++top]=j,vis[j]|=1;
30         if(top&1) swap(num[2],num[top]),vis[num[top]]=0,--top;
31         for(int j=1;j<=top;j+=2) tmp[++ans]=P(num[j],num[j+1]);
32     } print(ans);
33     for(int i=1;i<=ans;++i)
34         print(tmp[i].first,' '),
35         print(tmp[i].second);
36     return Ot(),0;
37 }
```

---

## 作者：Fuko_Ibuki (赞：2)

这题是我在CF中见过最经典的题之一.要想分成最多组,必然要最优化每个约数的使用.那么可以先想到筛法求质数.求出质数以后再想一个问题,对于一个非常大的质数来说和它有除1以外的公约数的只剩下了它的倍数.那么如果把这个质数的两倍和另外某一个偶数放在一起,这个质数就浪费了.所以说应该把比较大的质数和它的倍数放在一起.
那么可以从n/2开始分组(大于n/2的质数当然没有n以内的其他倍数),从大往小,如果找到一个质数a,那么就把没有用过的a的倍数全部放到一个vector里,两两配对.
你可能还有问题.如果vector里的数的个数是奇数个怎么办呢?可以发现a的两倍一定有一个质因数2,那么我们把a的两倍单独拎出来,最后到2的时候一并配对.思路都在这里,接下来是代码.
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int boss=1e5;
int n,ans,p[boss+10],t,prime[boss+10],vis[boss+10];
vector<int> v;pii tmp[boss+10];//由于先要输出分组的总个数,每一组只能用一个pair保存一下了.

void doing_prime()//筛法求质数,prime数组里是从2-n/2的质数
{
int i,j;
for (i=2;i<=n/2;i++) if (!p[i])
for (prime[++t]=i,j=2*i;j<=n;j+=i) p[j]=1;
}

int main()
{
int i,j;
scanf("%d",&n),doing_prime();
for (i=t;i>0;--i) //从n/2开始向下寻找质数
  {
  v.clear();//清空vector
  for (j=prime[i];j<=n;j+=prime[i]) 
    {
    if (!vis[j]) v.push_back(j);//没有用过的倍数全部放入vector
    vis[j]=1;//标记已用
    }
  int l=v.size();//v数组里元素的个数
  if (l&1) --l,swap(v[1],v[l]),vis[v[l]]=0;//如果个数是奇数,把第二个和最后一个换一下(注意第一个元素是v[0],第二个才是v[1])
  for (j=0;j<l;j+=2) tmp[++ans]={v[j],v[j+1]};//直接两两配对
  }
printf("%d\n",ans);//输出总数
for (i=1;i<=ans;i++) printf("%d %d\n",tmp[i].first,tmp[i].second);
}
```

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF449C)

首先一个质数和它的倍数肯定应该放在一起，要不然这个质数就没地方放了。

那就处理出 $p_i \le \dfrac{n}{2}$ 的质数，然后枚举它的倍数并两两配对，但是这样可能会剩下一个落单的。为了保证这个落单的数能继续进行匹配，那就把 $2p_i$ 这个数单独拿出来即可，这样它肯定能进到 $2$ 的倍数里匹配。

那么从大到小枚举所有质数即可，最后如果有单出来的显然无法进行配对，因为当前所有能配对的数都已经配对了。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
int n,cnt,p[100005],ans1[100005],ans2[100005],sum;
bool vis[200005];
vector<int> a,b;
void pre(int n)
{
	for(ri i=2;i<=n;i++)
	{
		if(!vis[i])
			p[++cnt]=i;
		for(ri j=1;j<=cnt&&i*p[j]<=n;j++)
		{	
			vis[i*p[j]]=1;
			if(i%p[j]==0)
				break;
		}
	}
}
int main()
{
	n=read();
	pre(n);
	memset(vis,0,sizeof(vis));
	for(ri i=cnt;i>=1;i--)
	{
		a.clear();
		if(2*p[i]>n)
			continue;
		for(ri j=p[i];j<=n;j+=p[i])
			if(!vis[j])
				a.push_back(j),vis[j]=1;
		int now=a.size();
		if(now%2)
			vis[2*p[i]]=0,swap(a[1],a[now-1]),now--;
		for(ri i=0;i<now;i+=2)
			sum++,ans1[sum]=a[i],ans2[sum]=a[i+1];			
	}
	cout<<sum<<"\n";
	for(ri i=1;i<=sum;i++)
		cout<<ans1[i]<<" "<<ans2[i]<<"\n";
	back 0;	
}
```

---

## 作者：Z1qqurat (赞：0)

很阿妹胫骨的思维题。

看到之后有一个很简单的策略：从小到大枚举所有质数 $p$ 作为两个数的 $\gcd$，然后将还未用过的 $p$ 的质数两两配对，如果有剩下的就留到下一轮。

但是这个很不对啊，因为你容易发现，假如当前可用的 $p$ 的个数是奇数，那么我们会抛弃掉一个数，留给下一轮，但是如果这个数没选好可能会导致方案不优，于是我们要使抛弃掉的这个数尽可能地在后期还能被用上。于是我们发现从大到小枚举 $p$ 就有点劣了，从大到小枚举的话，每次抛弃掉的数很可能为一个更小的质数 $q$ 的倍数，更优。接下来怎么选出抛弃掉的数呢？我们肯定尽量选小的，$2p$，因为 $2$ 是最小，也就是最后枚举到的质数。所以如果除了一些 $2p > n$ 的质数 $p$ 以及 $1$，最多就会只有一个数没有被匹配（因为最后所有 $2$ 的倍数可能有奇数个那也没法儿救了），达到上界。

代码好写，时间复杂度 $O(n \log \log n)$（线性筛的复杂度？）。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define mr make_pair
#define fi first
#define se second
using namespace std;
const int N = 1e5 + 5;
int n, cnt, p[N];
bool isp[N], vis[N];
vector <int> v;
vector <pii> ans;

void sieve() {
    isp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if(!isp[i]) p[++cnt] = i;
        for (int j = 1; j <= cnt && 1ll * i * p[j] <= n; ++j) {
            isp[i * p[j]] = 1;
            if(!(i % p[j])) continue;
        }
    }
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n; sieve();
    for (int i = cnt; i; --i) {
        int d = p[i]; v.clear();
        for (int j = d; j <= n; j += d) {
            if(!vis[j]) v.emplace_back(j);
        }
        if(v.size() < 2) continue;
        if(v.size() & 1) {
            reverse(v.begin(), v.end());
            v.pop_back(), v.pop_back(), v.emplace_back(d);
        }
        for (int j = 0; j < v.size(); j += 2) {
            int x = v[j], y = v[j + 1];
            vis[x] = vis[y] = 1, ans.emplace_back(x, y);
        }
    }
    cout << ans.size() << "\n";
    for (pii i : ans) cout << i.fi << ' ' << i.se << "\n";
    return 0;
}

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出正整数 $n$，你要把 $1-n$ 之间的正整数分成尽可能多组，使得每一组两个数的最大公约数大于1；输出能分成最多组的个数，并按任意顺序输出每组的两个数。  
## $\text{Solution}$
朴素做法可以想到枚举 $\gcd$ 把所有的倍数尽可能的配对。  
考虑为什么这样随便选会不优。  
就是当某次配对落单的最后也没有配对，但是如果选择其他某个元素落单，后面却可以配对。    
所以我们应该尽可能的选取后面容易配对的。  
那么我们每次就令 $2\times g$ 配对，最后在 $g=2$ 的时候全都配对就行了。  
这样如果还有落单的，说明这些待定的是奇数个，那么肯定就会有落单的，不可能更优了。
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e5+100;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
int q[N],st,ed;
bool vis[N],jd[N];
int x[N],y[N],tot;
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=2;i<=n;i++){
    if(jd[i]) continue;
    for(int j=i+i;j<=n;j+=i) jd[j]=1;
  }
  for(int i=n;i>=2;i--){
    if(jd[i]) continue;
    st=1;ed=0;
    for(int j=i;j<=n;j+=i){
      if(!vis[j]) q[++ed]=j;
    }
    if(ed&1) swap(q[2],q[ed]);
    while(st<ed){
      ++tot;x[tot]=q[st];vis[q[st++]]=1;
      y[tot]=q[st];vis[q[st++]]=1;
    }
  }
  printf("%d\n",tot);
  for(int i=1;i<=tot;i++) printf("%d %d\n",x[i],y[i]);
  return 0;
}
/*
3 3
tsy
*/

```


---

## 作者：ModestCoder_ (赞：0)

先把质数弄出来

从大到小枚举质数x，统计出所有x的倍数

如果个数是偶数就直接匹配

若是奇数把$2x$扔掉，剩下的匹配


那么2的倍数肯定只能减减漏了，剩下2的倍数个数仍然是奇数的话最终也只是扔掉一个数

所以这种方案是最优的

那可不可能存在一个数都不扔掉的方案？不可能

因为这种方案最坏情况是扔掉一个数，那孤掌难鸣，肯定不可能组成一对啊

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
struct data{
	int x, y;
}ans[maxn];
int n, flag[maxn], tot, prime[maxn], sum, a[maxn];

int main(){
	scanf("%d", &n);
	for (int i = 2; i <= (n >> 1); ++i){
		if (!flag[i]) prime[++tot] = i;
		for (int j = 1; j <= tot && i * prime[j] <= (n >> 1); ++j){
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	memset(flag, 0, sizeof(flag));
	for (int i = tot; i; --i){
		int cnt = 0;
		for (int j = prime[i]; j <= n; j += prime[i])
			if (!flag[j]) a[++cnt] = j;
		if (cnt & 1) swap(a[2], a[cnt]);
		for (int j = 1; j + 1 <= cnt; j += 2){
			flag[a[j]] = flag[a[j + 1]] = 1;
			ans[++sum] = (data){a[j], a[j + 1]};
		}
	}
	printf("%d\n", sum);
	for (int i = 1; i <= sum; ++i) printf("%d %d\n", ans[i].x, ans[i].y);
	return 0;
} 
```


---

