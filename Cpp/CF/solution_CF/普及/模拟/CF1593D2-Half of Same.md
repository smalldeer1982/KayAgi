# Half of Same

## 题目描述

给定一个包含 $n$（$n$ 是偶数）个整数的数列 $a_1,a_2,\ldots,a_n$。

考虑一个可能的**正整数** $k$，在每次操作中，你可以选定一个 $i$，并将 $a_i$ 减少 $k$。

你可以执行任意多次（也可能是零次）操作，使这个数列中**至少一半的数**相等。

请找出最大的符合条件的 $k$，如果 $k$ 可以是任意的大小，输出 $-1$。

## 说明/提示

- $1 \le t \le 10$；
- $4 \le n \le 40$；
- $-10^6 \le a_i \le 10^6$。

保证 $\sum\limits{n} \le 100$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
4
6
48 13 22 -15 16 35
8
-1 0 1 -1 0 1 -1 0
4
100 -1000 -1000 -1000
4
1 1 1 1```

### 输出

```
13
2
-1
-1```

# 题解

## 作者：Jairon314 (赞：7)

### CF1593D1

----------

> 给定一个长度为 $ n $ 的数组 $ a $ ， 找到一个最大的 $ k $ ，使得存在一个定值 $ val $ ，使得所有的 $ a_i-val $ 都被 $ k $ 整除或者 $ a_i=val $ 。如果这个 $ k $ 可以任意大，输出 $ -1 . $

首先考虑 $ k $ 任意大的情况。容易发现数组中的所有数字为定值是 $ k $ 能否任意大的充要条件。

根据同余的知识，我们可以发现，这个定值 $ val $ 肯定可以为最小值，那我们就把最值当作最小值来看。根据题意，可以发现，答案即为所有 $ a_i-val $ 的 $ gcd $（由题意可以直接得）。注意，这里所谓的所有 $ a_i $，不包括 $ a_i=val $ 的情况，所以注意特判。

该弱化版其实就是签到吧，看能不能读懂题。

### CF1593D2

----------

> 此题与上一题的区别在于，上一个题必须保证所有的 $ a_i-val $ 被 $ k $ 整除，而这个题只需要保证至少 $ \frac{n}{2} $ 个即可。

考虑与上一个题相同的做法，形成转化。

注意到该题可以考虑为从 $ n $ 个数字中选择 $ \frac{n}{2} $ 个数字使得 $ k $ 最大。

还是先考虑 $ k $ 任意大。容易发现是否存在大于等于 $ \frac{n}{2} $ 个相同的数字是 $ k $ 能否任意大的充要条件。

然后进行转化，因为选择 $ n $ 个数字的答案是不考虑 $ a_i=val $ 的情况中所有 $ a_i-val $ 的 $ gcd $ ，所以此题同理。由上一题的结论可得，定值 $ val $ 为选出来的数字中的最小值，所以我们可以枚举这个最小值，然后在比这个最小值大的数字中找到 $ \frac{n}{2} $ 个数字，使得这些数字与 $ val $ 的差的 $ gcd $ 最大。[就是这个题的结论。](https://www.luogu.com.cn/problem/P1414)

### 代码

----------

$ D1 $ 过于简单，代码就不放了哈，想要的找我私聊。

```cpp
// D2

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
 
#define int long long
 
/***** Fast_IO *****/
 
using std::cin;
using std::cout;
using vii = std::vector<int> ;
using pii = std::pair<int,int> ;
 
namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;
 
	inline char gc (){
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<21),stdin),p1==p2)?EOF:*p1++;
	}
 
	#define gc getchar
	#define pc putchar
	#define ONLINE_JUDGE OJ
 
	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}
 
	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}
 
	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
 
	void _FILE(){
		#ifndef ONLINE_JUDGE
			freopen("text.in","r",stdin);
			freopen("text.out","w",stdout);
		#endif
	}
 
	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
}using namespace IO;
 
/***** Fast_IO *****/
 
#define maxn 2000010
#define SIZE 5010
 
int T;
int a[maxn];
int c[maxn];
int n;
 
::unordered_map<int,int> buc;
 
signed main(){
	_FILE();
	read(T);
	while(T--){
		n=read(_);
		memset(a,0,sizeof a);
		buc.clear();
		int CNT=0,ans=0;
		FOR(i,1,n){ read(a[i]); CNT=::max(CNT,++buc[a[i]]); }
		if(CNT>=n/2){ puts("-1"); continue; }
		::sort(a+1,a+n+1);
		FOR(i,1,n/2+1){
			int res=0,rul=0;
			memset(c,0,sizeof c);
			FOR(j,i+1,n){
				int x=a[j]-a[i];
				if(x==0){ ++rul; continue; }
				res=::max(res,x);
				int lim=sqrt(x);
				for(int k=1;k<=lim;k++){
					if(x%k==0){
						++c[k];
						if(x!=k*k){
							++c[x/k];
						}
					}
				}
			}
			int delta=res;
			FOR(i,1,n/2-1-rul){
				while(c[delta]<i){ --delta; }
			}
			ans=::max(ans,delta);
		}
		outn(ans);
	}
	return 0;
}
```


---

## 作者：Blunt_Feeling (赞：6)

## CF1593D2 Half of Same 题解

假设最后到达相同值的那些数组成的原数列为 $a$，考虑枚举这个数列在排序后的第一个元素和第二个元素 $a_1,a_2$，由此得到差 $dif\leftarrow a_2-a_1$，可以证明答案 $k$ 为 $dif$ 的一个因数。于是继续枚举 $dif$ 的所有因数，再枚举 $a_3\sim a_{last}$，判断当前的 $k$ 是否可行，对 $k$ 求最大值。具体判断方法为检查 $a_i-a_1$ 能够被 $k$ 整除的数量是否大于等于 $n/2$。

处理的时候要注意先把每个数出现的次数先预处理出来，统计的时候直接加这个值就行了。

判断是否无解，只需判断初始序列是否已经满足条件。因为如果已经满足条件，有 $\forall k\in \text{N}$ 都满足要求，即不存在一个最大的 $k$。

时间复杂度 $O(n^3 \sqrt{a_i})$。

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int maxn=44;
int T,n,a[maxn],ans=1;
int tong[2000500];
bool checkno()
{
	For(i,1,n)
		if(tong[a[i]+1000000]>=n/2)
			return true;
	return false;
}
bool check(int k,int fi,int se)
{
	int cnt=tong[a[fi]+1000000]+tong[a[se]+1000000];
	int i;
	for(i=se+1;i<=n;i++)
		if(a[i]!=a[i-1])
			break;
	for(;i<=n;i++)
		if((a[i]-a[fi])%k==0)
			cnt++;
	return cnt>=n/2;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		For(i,1,n) cin>>a[i];
		sort(a+1,a+n+1);
		For(i,1,n) tong[a[i]+1000000]++;
		if(checkno()) { ans=-1; goto oops; }
		For(i,1,n/2+1) //枚举最小的数
		{
			if(i>1&&a[i]==a[i-1]) continue;
			For(j,i+1,n) //枚举第二个数
			{
				if(a[j]==a[j-1]) continue;
				int dif=a[j]-a[i],sqrtdif=sqrt(a[j]-a[i]);
				For(k,1,sqrtdif) //枚举答案
				{
					if(dif%k==0)
					{
						if(check(k,i,j))
							ans=max(ans,k);
						if(k*k!=dif)
						{
							if(check(dif/k,i,j))
								ans=max(ans,dif/k);
						}
					}
				}
			}
		}
		oops:;
		cout<<ans<<endl;
		For(i,1,n) tong[a[i]+1000000]=0;
		ans=0;
	}
	return 0;
}
```


---

## 作者：dd_d (赞：6)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15474322.html)  
### Sol  
首先转化一下题意，即要求有超过一半的数在模 $k$ 意义下相等。  
考虑若 $x=y \pmod k$，则 $(x-y) \bmod k=0$。  
在序列中随机两个数，记这两个数的差值为 $val$，那么 $val$ 满足要求的概率即为 $\frac{1}{4}$，不满足的概率即为 $\frac{3}{4}$。  
那么随机 $k$ 次，出错的概率就是 $(\frac{3}{4})^k$，当 $k$ 足够大时，出错的概率极小。  
枚举 $val$ 的因数判断是否满足要求即可。  
再考虑 $-1$ 的情况。  
即原数列中有超过一半的数相同。  
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e3+10,X=1e6+10;
int a[N],n;
bool check(int x)
{
	map<int,int> Map;
	for (int i=1;i<=n;i++)
	{
		Map[(a[i]+X*x)%x]++;
		if (Map[(a[i]+X*x)%x]>=n/2) return 1;
	}
	return 0;
}
signed main()
{
	srand(time(0));
	int T=read();
	while (T--)
	{
		n=read();
		for (int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+n+1);
		int cnt=1,flag=0;
		for (int i=2;i<=n;i++)
			if (a[i]==a[i-1])
			{
				cnt++;
				if (cnt>=n/2)
				{
					flag=1;
					break;
				}
			}
			else cnt=1;
		if (flag)
		{
			puts("-1");
			continue;
		}
		int ans=1;
		for (int k=1;k<=1000;k++)
		{
			int x=rand()%n+1,y=rand()%n+1,now=abs(a[x]-a[y]);
			for (int i=1;i*i<=now;i++)
				if (now%i==0)
				{
					if (check(i)) ans=max(ans,i);
					if (i*i!=now) if (check(now/i)) ans=max(ans,now/i);
				}
		}
		writeln(ans);
	}
}




```

---

## 作者：haokee (赞：0)

因为答案肯定在 $[0,2\times 10^6]$ 这个区间里面，因此我们可以考虑枚举所有可能的答案并逐一校验。检验时，我们可以枚举 $i$ 让其他 $j\ne i$ 的 $a_j$ 都改变成 $a_i$。时间复杂度为 $\mathcal O(kn^2)$，但是由于 $k$ 达到了 $2\times 10^6$，因此会超时。

考虑优化校验复杂度。能够发现，当 $a_j>a_i$ 的时候，只需要除可能解的余数一样就行了。因此，我们可以新建一个表用来存余数对应的数量，找到一个数量大于等于 $n/2$ 的余数。时间复杂度为 $\mathcal O(kn)$，仍然超时。

这次，我们不再寻找解了，而是枚举 $a_i$ 找到最优解。对于所有 $a_j>a_i$ 的 $a_j$，都可以通过一个数 $x$ 满足 $(a_j-a_i)\bmod x=0$ 减到 $a_i$，也就是说可能的 $x$ 必须是 $a_j-a_i$ 的因数。因此，我们先求出所有的因数，存进 map 里面，再找到一个最大的因数 $x$ 满足 $x$ 的数量大于等于 $n/2$ 就行了。时间复杂度 $\mathcal O(n^2\sum\limits_{i=1}^{n}\sqrt{a_i})$。

```cpp
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

const int kMaxN = 45;

int a[kMaxN], t, n, ans;
vector<int> v;
unordered_map<int, int> f;

unordered_set<int> calc(int x) {
  unordered_set<int> s;
  for (int i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      s.insert(i);
      s.insert(x / i);
    }
  }
  return s;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n;
    ans = -1e9;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    // 枚举要变成的
    for (int i = 1; i <= n; i++) {
      // 清空
      int times = 0;
      f.clear();
      v.clear();
      // 枚举其他的数
      for (int j = 1; j <= n; j++) {
        if (a[j] == a[i]) {          // 如果大小一样
          times++;                   // 记录数量
        } else if (a[j] > a[i]) {    // 大于 a[i]
          v.push_back(a[j] - a[i]);  // 加入 vector
        }
      }
      // 如果一样的已经超过了 n/2 就有无数种解
      if (times >= n / 2) {
        ans = 1e9;
        continue;
      }
      // 求因数并记录
      for (int i : v) {
        for (int j : calc(i)) {
          f[j]++;
        }
      }
      // 找最大的答案
      for (auto j : f) {
        if (j.second >= n / 2 - times) {
          ans = max(ans, j.first);
        }
      }
    }
    cout << (ans == 1e9 ? -1 : ans) << '\n';
  }
  return 0;
}
```

---

