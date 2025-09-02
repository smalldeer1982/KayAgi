# XXXXX

## 题目描述

给出一个长度为 $n$ 的序列 $A$ 以及一个常数 $x$，你需要选择一个**连续**的子序列满足其求和后不为 $x$ 的倍数。  

求这个子序列的最长长度。

## 样例 #1

### 输入

```
3
3 3
1 2 3
3 4
1 2 3
2 2
0 6```

### 输出

```
2
3
-1```

# 题解

## 作者：一扶苏一 (赞：5)

## 【贪心】【CF1364A】XXXXX

~~把 subarray 看成 subsequence 的悲剧~~。

### Analysis

首先如果序列和不能被 $x$ 整除，那么选上整个序列即可。下面考虑和被 $x$ 整除的情况。

有一个结论是，如果存在解，答案选出来的 subarray 至少存在一个为 $1$ 或者 $n$ 的端点。也即 subarray 要么是原序列的一个前缀，要么是一个后缀。

简单证明如下：
用反证法，设最优答案序列为 $[l, r]$，且 $l \neq 1, r \neq n$。设序列前缀和为 $s$。显然 $s_r - s_{l - 1}$ 不能被 $x$ 整除。分情况讨论：

1. 若 $s_{l - 1}$ 不能被 $x$ 整除，则 $s_n - s_{l  - 1}$ 一定不能被 $x$ 整除，则选择 $[l, n]$ 是合法的，答案更优。
2. 若 $s_{l - 1}$ 被 $x$ 整除，则 $s_r$ 不能被 $x$ 整除，选择 $[1, r]$ 合法，答案更优。

证毕。

因此找一个最短的不能被 $x$ 整除的前缀和后缀，取 min 即可。如果找不到这样的前/后缀，显然无解。

### Code

```cpp
namespace Fusu {

int T;
int n, x;
int a[100005], b[100005];

void Main() {
  for (qr(T); T; --T) {
    qr(n); qr(x);
    qra(a + 1, n);
    for (int i = 1; i <= n; ++i) {
      b[i] = b[i - 1] + a[i];
    }
    if ((b[n] % x) != 0) {
      qw(n, '\n');
    } else {
      int ans = n + 1;
      for (int i = 1; i <= n; ++i) if ((b[i] % x) != 0) {
        ans = std::min({ans, i, n - i});
      }
      qw(n - ans, '\n');
    }
  }
}

} // namespace Fusu
```



---

## 作者：b6e0_ (赞：3)

[CF题面传送门](https://codeforces.com/contest/1364/problem/A) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1364A) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1364A)

A题就出现数组了？

如果整个数组的和就不能被$x$整除，那么直接输出$n$。如果数组里所有的数都能被$x$整除，那么输出$-1$，因为怎么取都能被$x$整除。如果和能被$x$整除，那么要删去一个不能被$x$整除的数。但是subarray要连续，所以数组两端都找。左端找到最近的一个不能被$x$整除的数，右端找到最近的一个不能被$x$整除的数，两者将删去的数的个数比$\min$。赛时代码，写的很丑：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010];
int main()
{
	int t,n,x,i,sum,a1,a2;
	bool f;
	cin>>t;
	while(t--)
	{
		cin>>n>>x;
		sum=0;//和
		f=true;//标记是否全部都能被x整除
		for(i=0;i<n;i++)
		{
			cin>>a[i];
			sum+=a[i];
			if(a[i]%x)
				f=false;
		}
		if(f)
			cout<<"-1\n";
		else
			if(sum%x)
				cout<<n<<endl;
			else
			{
				for(i=0;i<n;i++)//左边找
					if(a[i]%x)
						break;
				a1=i+1;
				for(i=n-1;i>=0;i--)//右边找
					if(a[i]%x)
						break;
				a2=n-i;
				cout<<n-min(a2,a1)<<endl;//比min
			}
	}
	return 0;
}
```
时间复杂度为$O(tn)$。

---

## 作者：Isshiki_Hugh (赞：3)

根据性质，得到的数组必然可以通过原数组删去一个前缀一个后缀得到。

我们先把所有数加起来，看`sum`是否可以被整除，如果不能，直接输出，如果可以，我们找第一个不能被整除的前缀或者后缀。

- 如果`sum`能被整除，而`x`不能被整除，那么`sum-x`也不能被整除。

至于实现，我们得到能被整除的`sum`以后，从头和尾开始分别找一个最短的不能被整除的缀，看看哪一个更短，然后直接输出就完事了。

证明如下：

设存在$p | sum$，$p\not |  k$，且$p > 1$

那么$p|(sum+p)$

$sum - k = sum+p-k   \mod p$

$$
\because p\not |  k
$$
$$
\therefore p-k \not |  k
$$

$$
\therefore (sum+p-k)\not |  k
$$

$$
\therefore (sum-k) \not | k
$$

讲道理我不太会证(有错误请大力攻击我(确信。




```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>//rand()
#define rep(i,a,b) for(register int i = (a);i <= (b);++i)
#define per(i,a,b) for(register int i = (a);i >= (b);--i)
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

int _,n,p,a[111111],head,tail;
bool flag;

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> _;
    while(_--){
        flag = true;
        cin >> n >> p;
        rep(i,1,n) cin >> a[i];
        //下面两行其实没必要，等效于直接判断sum是否被整除
        rep(i,1,n) if(a[i] % p != 0) flag = false;
        if(flag) cout << "-1\n";
        else {
            head = tail = 0;
            int sum = 0;
            rep(i,1,n) sum += a[i];
            if(sum % p == 0){
            	//寻找不能被整除的前缀&后缀，用head和tail记录长度
                rep(i,1,n){
                    if(a[i] % p == 0) ++head;
                    else break;
                }
                per(i,n,1){
                    if(a[i] % p == 0) ++tail;
                    else break;
                }
                cout << n - std::min(head,tail) - 1 << "\n";
            } else cout << n << "\n";
        }
    }
    return 0;
}   
```

---

## 作者：huayucaiji (赞：0)

~~这个题是 1h 50min 才做出来的~~

首先我们先来关注一句话：

>**An array $a$ is a subarray of an array $b$ if a can be obtained from $b$ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.**

注意 **subarray**。所以是一段连续的子序列啊啊啊啊啊。

所以我们现在的思路就很明确了。

1.如果 $\forall i<n,x|a_i$,答案肯定为 $−1$  
2.如果$x\nmid \sum_{i=1}^n a_i$，我们直接输出 $n$ 即可。
3.问题现在集中在如果不属于前两种情况，即 $x\nmid \sum_{i=1}^n a_i$，且不是所有的 $a_i$ 都是 $x$ 的倍数。这种情况我们可以从前往后扫一遍，直到出现不是 $x$ 的倍数的数就可以停下来，从后往前进行相同的操作，最后比较一下哪种更优即可。

为什么？

我们知道对于两个 $x$ 的倍数 $a,b$。我们设 $a=p\cdot x,b=q\cdot x$。$a-b=(p-q)\cdot x$，也是 $x$ 的倍数，所以我们要找到一个不能被 $x$ 整除的数才可以。**我们最后要在“从前往后”和“从后往前”得出的答案中选一个**。我们无需两边都减去，所以是取最值。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
 
const int maxn=1e5+10;
 
int n,a[maxn],cnt[maxn],x;
 
signed main() {
	int t;
	t=read();
	while(t--) {
		fill(cnt,cnt+n+1,0);
		n=read();x=read();
		int sum=0;
		
		for(int i=1;i<=n;i++) {
			a[i]=read();
			cnt[a[i]%x]++;
			sum+=a[i]%x;
		}
		if(cnt[0]==n) {
			cout<<-1<<endl;
			continue;
		}
		else if(sum%x!=0) {
			cout<<n<<endl;
			continue;
		}
		
		int left=1,right=n;
		
		for(;left<=n;left++) {
			if(a[left]%x!=0) break;
		}
		for(;right>=1;right--) {
			if(a[right]%x!=0) {
				break;
			}
		}
		cout<<max(n-left,right-1)<<endl; 
	}
	return 0;
}
```

---

