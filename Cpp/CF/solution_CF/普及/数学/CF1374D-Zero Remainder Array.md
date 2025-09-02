# Zero Remainder Array

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers.

Initially, you have an integer $ x = 0 $ . During one move, you can do one of the following two operations:

1. Choose exactly one $ i $ from $ 1 $ to $ n $ and increase $ a_i $ by $ x $ ( $ a_i := a_i + x $ ), then increase $ x $ by $ 1 $ ( $ x := x + 1 $ ).
2. Just increase $ x $ by $ 1 $ ( $ x := x + 1 $ ).

The first operation can be applied no more than once to each $ i $ from $ 1 $ to $ n $ .

Your task is to find the minimum number of moves required to obtain such an array that each its element is divisible by $ k $ (the value $ k $ is given).

You have to answer $ t $ independent test cases.

## 说明/提示

Consider the first test case of the example:

1. $ x=0 $ , $ a = [1, 2, 1, 3] $ . Just increase $ x $ ;
2. $ x=1 $ , $ a = [1, 2, 1, 3] $ . Add $ x $ to the second element and increase $ x $ ;
3. $ x=2 $ , $ a = [1, 3, 1, 3] $ . Add $ x $ to the third element and increase $ x $ ;
4. $ x=3 $ , $ a = [1, 3, 3, 3] $ . Add $ x $ to the fourth element and increase $ x $ ;
5. $ x=4 $ , $ a = [1, 3, 3, 6] $ . Just increase $ x $ ;
6. $ x=5 $ , $ a = [1, 3, 3, 6] $ . Add $ x $ to the first element and increase $ x $ ;
7. $ x=6 $ , $ a = [6, 3, 3, 6] $ . We obtained the required array.

 Note that you can't add $ x $ to the same element more than once.

## 样例 #1

### 输入

```
5
4 3
1 2 1 3
10 6
8 7 1 8 3 7 5 10 8 9
5 10
20 100 50 20 100500
10 25
24 24 24 24 24 24 24 24 24 24
8 8
1 2 3 4 5 6 7 8```

### 输出

```
6
18
0
227
8```

# 题解

## 作者：Blunt_Feeling (赞：6)

## CF1374D Zero Remainder Array 题解
这是一篇用了大量 STL 的题解。

首先请看这组样例：

**输入**
```
1
5 4
4 6 6 3 6
```
**输出**
```
11
```

~~我自己造的。~~

为了把每个 $a_i$ 都变成 $k$ 的倍数，我们就可以先把数列中的每一个数都对 $k$ 取模，根据余数来看还需要给这个数加上多少。于是这个数列就可以变成`0 2 2 3 2`，排序过后就是`0 2 2 2 3`，设这个数列为 $a$ 数组。

我们可以知道，$a_1$ 已经不需要再加；因为 $x$ 的值会变大，所以 $a_2$ 还需要加 $2$，$a_3$ 要加 $6$，$a_4$ 要加 $10$，$a_5$ 要加 $1$。$x$ 的值在每次操作时都会加 $1$，又因为题目最后说：
>Note that you can't add $x$ to the same element more than once.

也就是说每个数被加的次数不能超过一次。这也就意味着把 $x$ 一路加过来，当 $x$ 到达 $10$ 的时候才能把 $a_4$ 变成 $4$ 的倍数，而另外的数在这之前都能被加好。

于是这道题就能转化为：寻找 $a$ 数组中元素都相等的子段，求出它们各自需要把 $x$ 加到多少，并求出这些值的最大值。观察题面可以得知，**最终输出的答案就为 $x$ 的最大值加 $1$**。

这里用了集合`set`给 $a$ 数组去重，便于后期找到一段子段中每个元素的大小。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long //此题要开long long
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=200050;
int T,n,k,a[maxn];
set<int> st;
signed main()
{
    cin>>T;
    while(T--)
    {
    	cin>>n>>k;
    	st.clear(); //set初始化
	    For(i,1,n)
	        cin>>a[i],a[i]%=k,st.insert(a[i]); //先让a[i]对k取模，并压入集合
	    sort(a+1,a+n+1); //排序
	    int ans=0;
	    for(set<int>::iterator it=st.begin();it!=st.end();it++) //迭代器遍历set
	    {
	    	if(*it==0) continue; //值为0就不用再加
	    	int num=(upper_bound(a+1,a+n+1,*it)-lower_bound(a+1,a+n+1,*it));
	    	//用upper_bound-lower_bound求有组数列中值为*it的元素个数
	    	ans=max(ans,k-*it+(num-1)*k+1);
	    	/*
			* 由于要求的是像2,6,10一样的等差数列的末项，
			* 就要用到末项公式：末项=首项+(项数-1)×公差
			* 首项为(k-*it)，项数为num，公差为k
			* 于是ans=max(ans,k-*it+(num-1)*k+1) 注意+1不能忘！！ 
			*/ 
		}
	    cout<<ans<<endl;
	}
    return 0;
}
```
想看无注释的代码？[点这里](https://codeforces.ml/problemset/submission/1374/86017432)。

---

## 作者：45dino (赞：2)

不需要那么复杂的。

注意到有一句**加粗**的话：
>**注意：你只可以给同一个数加一次 $x$** 。

这样就很简单了！

对于 $a_i$ 只要 $a_i$ 不能被 $k$ 整除，就要加上 $b$ ，满足 $b$ $mod(k)=k-a$ $mod(k)$ 。

如果有 $m$ 个数模 $k$ 余 j，那么 $x$至少加到 $(m-1)\times k+j$ ，要进行 $(m-1)\times k+j+1$ 次操作。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int> num;
int t,a[200001];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		int n,k,ans=0,maxx=0;
		scanf("%lld%lld",&n,&k);
		num.clear();
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]%k==0)//如果能整除，是不需要加的	
				continue; 
			num[k-a[i]%k]++;
			if(num[k-a[i]%k]==maxx)
				ans=max(ans,k-a[i]%k);
			if(num[k-a[i]%k]>maxx)
			{
				maxx=num[k-a[i]%k];
				ans=k-a[i]%k;
			}
		}
		if(maxx==0&&ans==0)//特判
			puts("0");
		else
			cout<<(maxx-1)*k+ans+1<<endl;
	} 
	return 0;
}
```


---

## 作者：Sun_wtup (赞：1)

# Zero Remainder Array 题解
[题目传送](https://www.luogu.com.cn/problem/CF1374D)
## 题意
给出一个正整数 $k$，一个序列 $a$。有一个变量 $x$，最初是 $0$，定义一次操作为将 $x$ 加一以及将任意的一个 $a_i$ 加 $x$（当然也可以不加）。问最少操作几次能使 $k$ 整除每个 $a_i$。
## 分析与思路
对于输入的每个 $a_i$ 判断是否 $k$ 整除 $a_i$，如果是，不管。否则再判断：
  - 如果 $a_i$ 小于 $k$，将他离 $k$ 的距离记录，将这个距离的出现的次数加一，与当前操作的最大次数比大小，如果当前距离是第一次出现，那么比最大值和当前距离，如果不是就先加到 $k$（也就是加当前距离），然后后面几次出现的每个加 $k$ 就可以了，然后再和最大值比大小。
  - 如果 $a_i$ 大于 $k$，将他离最近大于自己的 $k$ 的倍数的距离记录，将这个距离的出现的次数加一，与当前操作的最大次数比大小，如果当前距离是第一次出现，那么比最大值和当前距离，如果不是就先加到 $k$（也就是加当前距离），然后后面几次出现的每个加 $k$ 就可以了，然后再和最大值比大小（其实和小于的情况差不多）。
## 实现
我们用 `map < int, int > mp;` 存距离的出现次数，最大操作次数为 `int maxn;`。然后根据上文就有
```cpp
if(a[j] % k != 0){
    if(a[j] < k){
        mp[k - a[j]]++;//将距离加一
        maxn = max(maxn,(mp[k - a[j]] - 1) * k + k - a[j]);
    }//k - a[j]是当前距离，(mp[k - a[j]] - 1) * k就是后面加的k
    else{
        mp[(a[j] / k + 1) * k - a[j]]++;//将距离加一，(a[j] / k + 1) * k是距离最近的的k的倍数
        maxn = max(maxn,(mp[(a[j] / k + 1) * k - a[j]] - 1) * k + (a[j] / k + 1) * k - a[j]);
    }//(a[j] / k + 1) * k - a[j]是当前距离，(mp[(a[j] / k + 1) * k - a[j]] - 1) * k是后面加的k
}
```
温馨提示：多测别忘归零。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
#define int long long 
int t,n,k,x;
int maxn = 0;
int a[200005];
map < int, int > mp;
inline void clear(){
    for(int i = 1; i <= n; i++){
        if(a[i] % k != 0){
            if(a[i] < k){
                mp[k - a[i]] = 0;
            }
            else{
                mp[(a[i] / k + 1) * k - a[i]] = 0;
            }
        }
    }
} 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    for(register int i = 1; i <= t; i++){
        cin >> n >> k;
        maxn = 0;
        for(register int j = 1; j <= n; j++){
            cin >> a[j];
            if(a[j] % k != 0){
                if(a[j] < k){
                    mp[k - a[j]]++;
                    maxn = max(maxn,(mp[k - a[j]] - 1) * k + k - a[j]);
                }
                else{
                    mp[(a[j] / k + 1) * k - a[j]]++;
                    maxn = max(maxn,(mp[(a[j] / k + 1) * k - a[j]] - 1) * k + (a[j] / k + 1) * k - a[j]);
                }
            }
        }
        clear();
        cout << ((!maxn) ? 0 : (maxn + 1)) << "\n";
    }
    return 0;
}
```
本蒟蒻水平有限，如有不周之处，请谅解。

---

## 作者：EC75 (赞：1)

### 代码

我把代码放在前面~~方便大家抄~~。

```python
import os
import sys
from io import BytesIO, IOBase
BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0
    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()
    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()
    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
from math import gcd, ceil
def pre(s):
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        j = pi[i - 1]
        while j and s[i] != s[j]:
            j = pi[j - 1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j
    return pi
def prod(a):
    ans = 1
    for each in a:
        ans = (ans * each)
    return ans
def lcm(a, b): return a * b // gcd(a, b)
def binary(x, length=16):
    y = bin(x)[2:]
    return y if len(y) >= length else "0" * (length - len(y)) + y
for _ in range(int(input()) if True else 1):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    vals = {}
    for i in a:
        vals[i%k] = 1 if i%k not in vals else vals[i%k] + 1
    ans=0
    for i in vals:
        if i==0:continue
        ans = max(ans, -i+vals[i]*k+1)
    print(ans)
```
~~好长啊~~

### 思路

首先，我们可以理解，在 $x$ 从 $0$ 到$k-1$ 的每个完整周期中，我们只能修复每个余数一次。请注意，当我们添加一些 $x$ 时，我们会修正余数 $k-x$（我们不需要修正已经可以被 $k$ 整除的元素）。设 $cnt_i$ 为条件 $k-a_i \mod k=i$ 适用的此类元素的数量（即，如果我们将值 $i \mod k$ 添加到这些元素中，我们可以修复的此类元素的数量）。我们可以使用一些对数数据结构（比如 C++ 中的 std::map）来计算。

那么，完整周期的数量是多少？它等于 $cnt$ 中最常见元素的量自减。所以，答案至少是这样的：$k×(\max(cnt)-1)$。最后一个循环可能是不完整的。那么再来的次数是多少？它等于所有 $cnt_i=\max(cnt)$ 中的最大可能 $i$。

所以如果 $key$ 是最大值，比如$cnt_{key}=\max(cnt)$，那么答案是 $k×(cnt_{key}-1)+key+1$。

时间复杂度：$O(n \log n)$。

---

## 作者：expecto__patronum (赞：0)

## 题目大意：
给定一个数组和一个数 $k$，初始 $x=0$，每一步可以有两种操作，将 $x$ 加到某一个数上并且 $x$ 自增，或者只是 $x$ 自增。尽量通过最少的操作次数，使得数组中每一个数都可以整除 $k$。

## 题解：
因为一步操作只能对一个数增加，所以相同的数字需要在下一次满足条件时增加。对于数组，先求出每一个数的目标数字，目标数组与原数组差的最大值加一就是最小操作步数。

## AC代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
bool cmp(long long a, long long b){
    return a < b;
}
int t, n;
long long k;
map<long long ,int>vis;
long long a[N], b[N];
int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i = 1; i <= n; ++i){
            cin>>a[i];
            a[i] %= k;
        }
        sort(a+1, a+n+1,cmp);
        for(int i = 1; i <= n; ++i){
            if(a[i]){
                vis[a[i]]++;
                b[i] = vis[a[i]] * k;
            }
        }
        vis.clear();
        for(int i = 1; i <= n; ++i){
            a[i] = b[i] - a[i];
        }
        sort(a+1, a+n+1,cmp);
        if(a[n]){
            cout<<a[n]+1<<endl;
        }
        else{
            cout<<"0\n";
        }
        for(int i = 1; i <= n; ++i){
            a[i] = 0, b[i] = 0;
        }
    }
}
```
[更好的阅读体验](https://blog.csdn.net/weixin_64257615/article/details/128950682)
空格好难！求过！

---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF1374D)

# 解法

先求出每个 $a[i]$ 加几最小能变成 $k$ 的倍数。

因为每个 $x$ 都只能加一次，所以重复的数量要多加一个 $k$。

直接统计即可。

# 代码（有注释）
```cpp
#include<bits/stdc++.h>
#define N 200010
#define int long long//开long long
using namespace std;
int _,n,k,a[N],p[N];
signed main(){
	cin>>_;
	while(true){
		if(!_) break;_--;
		cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i],a[i]=(-a[i]+k*(a[i]/k+1))%k;//a[i]改为增加数量。
		sort(a+1,a+n+1);//排序
		for(int i=1;i<=n;++i)
			if(a[i]==a[i-1]) p[i]=p[i-1];
			else p[i]=i;//同一个加数有几个。
		for(int i=1;i<=n;++i) if(a[i]!=0) a[i]+=(i-p[i])*k;
        //将a[i]更新为最终步数。
		int ans=*max_element(a+1,a+n+1);//求最大值，即为答案。
		if(ans) cout<<ans+1<<"\n";
		else cout<<"0\n"; //特判
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/125362407)

---

## 作者：B_1168 (赞：0)

首先推销一下数据点加强版本：[超强数据！](https://www.luogu.com.cn/problem/U120689)

萌新首打Div. C，E1居然没做出来……

很显然，对每组数据，为了便于处理，可以将给出的`a[i]`进行一些变形，存下`b[i]=(k-(a[i]%k))%k`，代表最小的数，使得`a[i]+b[i]%k==0`

考虑到每次操作只能对一个元素进行且必有`x+=1`操作，如果有多于一个数的`b[i]`值相等，显然需要多进行`k`次操作才能同时确保这些数均能被`k`整除。在此，可使用`map`或离散化记录每一个`b[i]`值出现的次数，相应计算。特别注意，`b[i]==0`时需要特判。

赛时代码：

```cpp
//Code as is from contest
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;

long long a[maxn],b[maxn],d[maxn],n,k,t,ans,fl;

//不开ll见祖宗----但是开太多也会因为TLE见祖宗

void solve(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	map<long long,long long>c;
	ans=0;fl=0;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=(k-(a[i]%k))%k;
		d[i]=b[i];
		if(b[i]!=0){
			fl=1;
		}
	}
	if(!fl){
		printf("0\n");
		return;
	}
	for(int i=1;i<=n;i++){
		if(b[i]){ //留意特判
			d[i]+=k*c[b[i]];
			c[b[i]]++;
		}
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,d[i]);
	}
	printf("%lld\n",ans+1);
}

int main(){
	scanf("%lld",&t);
	while(t--){
		solve();
	}
}
```

由于$T\leq2\times10^4$，每组数据都对两个二十万的`long long`数组进行`memset`的时间开销极端可怖，以致测试点#3跑到了1.73s，赛时评测更是跑到了1.98s，离超时仅有一步之遥……

意识到这尴尬的情况，我决定对赛时代码进行一些改造----

- 留意到我们根本没有用到过`a[i]`和`d[i]`，删除
- 为了适应不同的数据范围，改用`std::vector`
- 留意到数组和`map`并不需要`long long`的数据范围，改为仅答案和`k`使用`long long`
- 快读是必不可少的qwq

然后……就是改进版代码啦！

```cpp
//Luogu_Resubmission
#include<bits/stdc++.h>
#define maxn 2000005
using namespace std;

int n,t,fl;

long long ans,k;

map<int,int>c;

inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf; 
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++; 
}

inline int read(){
	int x=0,f=1;char ch=nc();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=nc();}
	while (isdigit(ch)){x=x*10+ch-48;ch=nc();}
	return x*f;
}

void solve(){
	vector<int>b;
	b.push_back(0);
	c.clear();
	ans=0;fl=0;
	n=read(),k=read();
	for(register int i=1;i<=n;i++){
	    b.push_back((k-(read()%k))%k);
		if(b[i]!=0){
			fl=1;
		}
	}
	if(!fl){
		printf("0\n");
		return;
	}
	for(register int i=1;i<=n;i++){
		if(b[i]){
			long long temp=(b[i]+k*c[b[i]]);
			ans=max(ans,temp);
			c[b[i]]++;
		}
	}
	printf("%lld\n",ans+1);
}

int main(){
//	freopen("CF1374D_2.in","r",stdin);
//	freopen("CF1374D_2.out","w",stdout);
	t=read();
	while(t--){
		solve();
	}
}
```
感谢管理大大审核，感谢阅读，欢迎去加强数据版挑战常数qwq

---

## 作者：PanH (赞：0)

## 题意
给你两个数 $n$ , $k$ ,和一个大小为 $n$ 的数组 $a$。另有一个一开始为 $0$ 的数 $x$ 。每一步 $x$ 会增加 $1$ （ $x=0$ 时算第一步）。对于每一步你可以使数组 $a$ 中的一个元素加上当前的 $x$ ，加过的元素不能重复加（或者跳过当前步）。最终使得 $a$ 中的每个元素都能被 $k$ 整除。

## 做法
对于本身就是 $k$ 的倍数的元素，自然不用去管。

对于模 $k$ 余 $p$ 的元素，我们要给它加 $s\cdot k-p$ ，$s$ 要往小的数取。而 $s$ 的最小取值与余数是 $p$ 的元素数量有关。考虑到范围比较大，直接上 map 就彳亍了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000005],k;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		map<long long,long long> p;
		cin>>n>>k;
		long long ans=0;//开long long
		for(int i=1;i<=n;i++)
		{
			long long x;cin>>x;
			x%=k;
			if(x==0)	continue;
			p[x]++;
			ans=max(ans,p[x]*k-x);
		}
		if(ans)cout<<ans+1<<endl;
		else	cout<<0<<endl;
	}
	return 0;
}
```


---

## 作者：Clouder (赞：0)

初始 $x = 0$，每次操作后 $+1$，两种操作：   

1. $a_i += x$   
2. 什么都不干   

操作1对每个数最多进行一次。  
求 $\forall a_i \equiv 0 \pmod{k}$  的最小步数。  
将所有数模 $k$ 处理，对于 $a_i$，$x = k - a_i$ 是唯一操作方法。  
进行操作与什么都不干等代价，则能使  $a_i += x$ 时一定会进行操作。  
由于 $x$ 单调递增，每次找到最小的 $x \leq a_i$，再进行计算转移，一定是最优的。  
可以用set来处理。    

```cpp
#include <cstdio>
#include <set>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
#define int long long
const int maxn = 2e5 + 100;
int T,n,k,a[maxn];
std::multiset<int> s;
signed main()
{
    read(T);
    while(T--)
    {
        s.clear();
        read(n),read(k);
        for(int i = 1;i<=n;++i) read(a[i]),a[i] = k - (a[i] % k);
        for(int i = 1;i<=n;++i) if(a[i] != k) s.insert(a[i]);
        int ans = 0,x = 0;
        while(!s.empty())
        {
            std::set<int>::iterator it = s.lower_bound(x);
            if(it == s.end())  ans += k - x,x = 0;//找不到则归零
            else ans += *it - x + 1,x = (*it) + 1,s.erase(it);
            x %= k;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

