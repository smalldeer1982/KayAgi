# Corrupted Array

## 题目描述

给定一个正整数$n$和长度为$n+2$的数组$b$，数组$b$是依据如下算法构造的：

- 随机生成一个含有 $n$ 个元素的原始数组$a$；
- 把数组 $a$ 赋值给数组 $b$，即 $b_i=a_i(1\le i\le n)$；
- 数组 $b$ 的第 $n+1$ 个元素为数组 $a$ 的元素和，即 $b_{n+1}=\sum_{i=1}^na_i$；
- 数组 $b$ 的第 $n+2$ 个元素是个随机整数 $x(1\le x\le10^9)$；
- 打乱 $b$ 数组。

例如，数组 $b=[2,3,7,12,2]$，那么它能够通过如下方式构建：

- $a=[2,2,3]$，且$x=12$；
- $a=[3,2,7]$，且$x=2$。

给定一个$b$数组，请你求出它对应的$a$数组。

## 样例 #1

### 输入

```
4
3
2 3 7 12 2
4
9 1 7 1 6 5
5
18 2 2 3 2 9 2
3
2 6 9 2 1```

### 输出

```
2 3 7 
-1
2 2 2 3 9 
1 2 6```

# 题解

## 作者：Dragonbell_exp (赞：5)

### 思路：
因为数组 $a$ 的元素全是大于 $1$ 的正数，所以数组 $a$ 的元素和一定大于 $a$ 中的任何元素，我们把这个元素和称为 $v$。

如果没有 $x$，$v$ 一定是数组 $b$ 中最大的。但是因为有了 $x$，$v$ 就有可能是最大的，也有可能是次大的了。

因此，我们可以逐个判断 $v$ 是最大的还是次大的。如果 $v$ 是次大的，小于 $v$ 的所有数就是数组 $a$ 的全部元素；如果 $v$ 是最大的，那么还需要在剩下的里面找出 $x$。
### 实现：
为数组 $b$ 排序，先将前 $n$ 个数相加并与第 $n+1$ 个数做判断，如果等于则证明 $v$ 是次大的。

否则让和多加上第 $n+1$ 个数，逐个枚举这 $n+1$ 个数，如果找到了一个数在减去这个数后和恰好等于 $b$ 中的第 $n+2$ 个数，则证明这个数就是 $x$，输出这 $n+1$ 个数并在遇到 $x$ 之后跳过即可。
### 代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t;
int n;
long long num;
int a[1000000];
bool can;
int main(){
	t=read();
	while(t--){
		n=read();
		num=0;
		can=0;
		for(int i=1;i<=n+2;i++){
			a[i]=read();
		}
		sort(a+1,a+n+3);
		for(int i=1;i<=n;i++){
			num+=a[i];
		}
		if(num==a[n+1]){
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";
			}
			cout<<endl;
			can=1;
			continue;
		}
		num+=a[n+1];
		for(int i=1;i<=n+1;i++){
			if(num-a[i]==a[n+2]){
				for(int j=1;j<=n+1;j++){
					if(j==i){
						continue;
					}
					cout<<a[j]<<" ";
				}
				cout<<endl;
				can=1;
				break;
			}
		}
		if(can==0){
			cout<<-1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：wheneveright (赞：4)

## 题意

一句话题意：对于每一组数据，给出一个 $n$ 和长度为 $n+2$ 的序列 $b$。请求出一个长度为 $n$ 的序列 $a$ 使得 $a$ 是 $b$ 的子序列，并且 $\sum_{i=1}^n a_i$ 是 $b$ 中除去 $a$ 的元素后剩下的两个元素之一。

## 分析

看到这个题目一定可以立刻想出一个 $\operatorname{O}(n^3)$ 的做法，首先用 $n^2$ 的复杂度枚举两个存在于 $b$ 不存在于 $a$ 的数，然后 $\operatorname{O}(n)$ 胡一个判断就好了，怎么高的复杂度不能承受，于是我们又能想到将判断部分优化成 $\operatorname{O}(1)$ 定义 $sum = \sum_{i = 1}^{n + 2} b_i$ 然后就可以用 $sum - b_i - b_j$ 来表示剩下的元素之和，其中 $b_i,b_j$ 表示当前美剧的两个数，然后就能将时间复杂度降到 $\operatorname{O}(n^2)$。

然而 $\operatorname{O}(n^2)$ 也不是这道题的最优解法，然后我们思考能不能将枚举部分的复杂度优化成 $\operatorname{O}(n)$ 或者 $\operatorname{O}(n\times \log_2n)$， 思考只枚举一个数字，令当前枚举的这个数字为 $b_i$，需要寻找的另一个不在 $b$ 序列中的数字为 $b_j$，则除了 $b_i$ 之外的 $b$ 序列元素之和为 $sum - b_i$，我们设 $sum - b_i = sum_i$。

因为：

$$\sum_{k = 1}^n a_k = b_i, \sum_{k = 1}^n a_k + b_j + b_i = \sum_{l = 1}^{n+2} b_l = sum$$

移项带入得到:

$$b_i = \sum_{k = 1} ^ n a_k = sum - b_i - b_j$$

再移项一下得出 $b_j = sum - b_i\times 2$，二分查找这样的 $b_j$ 是否存在就好了，要注意的一点是 $j \not = i$ 如果等于的话看一下是否有多个 $k$ 满足 $b_k = b_i$ （但是它的数据好像没有那么刁钻，不用看多个数相同）。

时间复杂度为 $\operatorname{O}(n\times \log_2 n)$。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;

struct reader {
    template <typename Type>
    reader & operator >> (Type & ret) {
        int f = 1; ret = 0; char ch = getchar ();
        for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -f;
        for (; isdigit (ch); ch = getchar ()) ret = (ret << 1) + (ret << 3) + (ch - '0');
        ret *= f; return *this;
    }
}fin; // 快速读入

int T, N;
long long A[maxn]; // b 数列我直接开成 A 因为打的时候比较习惯
int L, R, mid, res;
long long sum; // sum 记得开 long long
bool check;

int main () {
	fin >> T;
	while (T--) {
		fin >> N; sum = 0; N += 2; // N 直接 +2 比较好操作，不然打的烦
		for (register int i = 1; i <= N; i++) fin >> A[i], sum += A[i];
		sort (A + 1, A + 1 + N); check = false; // 先排序，这样可以支持二分
		for (register int i = N; i >= 1; i--) {
			L = 1; R = N; res = -1; // 二分找出是否存在这样的 b[j]
			while (L <= R) {
				mid = L + R >> 1;
				sum - A[mid] >= A[i] * 2 ? L = mid + 1, res = mid : R = mid - 1;
			} // 判断 res 是否满足条件
			if (res != -1 && sum - A[res] == A[i] * 2 && res != i) {
				for (register int j = 1; j <= N; j++)
				if (j != i && j != res) printf ("%d ", A[j]);
				check = true; break; // 将 check 标为 true
			}
		}
		if (not check) {printf ("-1");} putchar (10);
	}
	return 0;
}
```

---

## 作者：rui_er (赞：2)

有一个长度为 $n$ 的数组 $a$，按照如下方式构造数组 $b$：

$$
b_i=\begin{cases}
a_i & 1\le i\le n \\
\sum\limits_{i=1}^na_i & i=n+1 \\
x & i=n+2
\end{cases}
$$

其中 $x$ 是一个 $1\sim 10^9$ 的随机数。现在给出打乱的数组 $b$，构造出一个符合条件的数组 $a$。

---

做法：

显然，打乱前的 $b_{n+1}$ 位置一定是最大的或第二大的（取决于 $x$ 与 $b_{n+1}$ 的大小关系），因此将 $b$ 排序并求出前缀和 $s$。

如果 $b_{n+1}=s_n$，就意味着 $x\gt b_{n+1}$，此时 $a$ 数组即为 $b_1,b_2,\cdots,b_n$。

否则如果 $\exists i\in\left[1,n+1\right],b_{n+2}=s_{n+1}-b_i$，就意味着 $x=b_i$，此时 $a$ 数组为 $b_1,\cdots,b_{i-1},b_{i+1},\cdots,b_{n+1}$。

否则无解，输出 $-1$。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 ll T; for(scanf("%lld", &T);T;T--)
#define mulT1 ll T, rnds; for(scanf("%lld", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const ll N = 2e5+5;

ll n, k, b[N], s[N];

int main() {
	mulT0 {
		scanf("%lld", &n); k = n + 2;
		rep(i, 1, k) scanf("%lld", &b[i]);
		sort(b+1, b+1+k);
		rep(i, 1, k) s[i] = s[i-1] + b[i];
		if(b[n+1] == s[n]) rep(i, 1, n) printf("%lld ", b[i]);
		else {
			int ok = 0;
			rep(i, 1, n+1) if(b[n+2] == s[n+1] - b[i]) {ok = i; break;}
			if(ok) {rep(i, 1, n+1) if(i != ok) printf("%lld ", b[i]);}
			else printf("-1");
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：haokee (赞：0)

枚举 $x$，那么剩下的所有数当中最大的那个就一定是 $a_i\sim a_n$ 的和，因为 $1\le b_i\le 10^9$，$a$ 同理。判断一下剩下的那个数是否合法就行了。

```cpp
#include <iostream>
#include <set>

using namespace std;
using LL = long long;

const LL kMaxN = 2e5 + 5;

LL a[kMaxN], t, n, sum, ans1, ans2;
multiset<LL> s;

int main() {
  for (cin >> t; t; t--) {
    cin >> n;
    sum = 0, ans1 = -1;
    s.clear();
    for (LL i = 1; i <= n + 2; i++) {
      cin >> a[i];
      s.insert(a[i]);
      sum += a[i];
    }
    for (LL i = 1; i <= n + 2; i++) {
      s.erase(s.find(a[i]));
      if (*s.rbegin() == sum - a[i] - *s.rbegin()) {
        ans1 = a[i];
        ans2 = *s.rbegin();
        break;
      }
      s.insert(a[i]);
    }
    if (!~ans1) {
      cout << "-1\n";
      continue;
    }
    for (LL i = 1; i <= n + 2; i++) {
      if (a[i] == ans1) {
        ans1 = 0;
      } else if (a[i] == ans2) {
        ans2 = 0;
      } else {
        cout << a[i] << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## CF1512D Corrupted Array 题解
### 分析
将 $b$ 数组从小到大排序，可知 $a$ 数组的和只可能出现在 $b_{n+1}$ 和 $b_{n+2}$ 中间，枚举 $x$ 统计和再分别判断即可。若 $b_{n+1}$ 为和，则 $x$ 一定为 $b_{n+2}$（因为 $a$ 数组中没有负数），直接用前 $n$ 个的和跟 $b_{n+1}$ 判等。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, b[200005];
signed main()
{
    for(cin>>t;t;t--)
    {
        cin>>n;
        for(int i=1;i<=n+2;i++)
        {
            cin>>b[i];
        }
        sort(b+1,b+1+(n+2));
        int cnt=0;
        for(int i=1;i<=n+1;i++)
        {
            cnt+=b[i];
        }
        if(cnt-b[n+1]==b[n+1])
        {
            for(int i=1;i<=n;i++)
            {
                cout<<b[i]<<" ";
            }
            cout<<"\n";
            continue;
        }
        int id=0;
        for(int i=1;i<=n+1;i++)
        {
            if(cnt-b[i]==b[n+2])
            {
                id=i;
                break;
            }   
        }
        if(id==0)
        {
            cout<<-1<<"\n";
            continue;
        }
        for(int i=1;i<n+2;i++)
        {
            if(i!=id)
            {
                cout<<b[i]<<" ";
            }
        }
        cout<<"\n";
    }
}

```

---

## 作者：fedoralxy (赞：0)

## 题目大意

给定一个长度为 $n$ 的数组 $a$ 并按照如下方式构造数组 $b$。
 
- 当 $1 \leq i \leq n$ 时 $b_i = a_i$

- 当 $i = n + 1$ 时 $b_i = \sum_{i = 1}^{n} a_i$ 

- 当 $i = n + 2$ 时 $b_i = x$

要注意的是 $x$ 是一个在 $1 \sim 10^9$ 的随机数，即：
$\exists\  x \ s.t. \ x \in [1,10^9] $。

现在给出打乱的数组 $b$ 构造出一个符合条件的数组 $a$。

## 分析与实现

- 分析

因为 $1 \leq a_i$，所以 $\sum_{i = 1}^n a_i$ 大于任意的 $a_i$。

我们令 $v = \sum_{i = 1}^n a_i$。

除去 $x$ 之后 $v$ 必然是数组 $b$ 中最大的。

所以很显然，在正常情况下 $v$ 是数组 $b$ 中最大或次大的。

逐个判断 $v$ 是最大的还是次大的。若 $v$ 是次大的，小于 $v$ 的数就是数组 $a$ 中的任意元素，反之 $v$ 是最大的，那么就要在剩下的数中找出 $x$。

- 实现

将数组 $b$ 排序。

将 $n$ 个数相加并与第 $n+1$ 个数比较，如果等于则 $v$ 是次大的。

否则让 $v$ 加上第 $n + 1$ 个数，逐个枚举这 $n+1$ 个数，如果找到了一个数在减去这个数后和恰好等于 $b$ 中的第 $n + 2$ 个数则恭喜你找到了 $x$ 并输出这 $n + 1$ 个数并在发现 $x$ 之后跳过即可。

## 参考代码

```cpp
/*
   * @file    :Corrupted Array.cpp
   * @author  :fedoralxy
   * @userid  :491542
   * @version :V1.0.0
   * @date    :2023-08-13
   */
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
ll q;
ll n;
ll a[N];
int main()
{
	cin>>q;
	while(q--)
	{
		ll sum=0;
		cin>>n;
		for(int i=1;i<=n+2;i++)
        cin>>a[i];
		sort(a+1,a+n+3);
		for(int i=1;i<=n;i++)
        sum+=a[i];
		if(sum==a[n+1])
		{
			for(int i=1;i<=n;i++)
				std::cout<<a[i]<<" ";
			std::cout<<endl;
			continue;
		}
		sum+=a[n+1];
		bool f=1;
		for(int i=1;i<=n+1;i++)
			if(sum-a[i]==a[n+2])
			{
				for(int j=1;j<=n+1;j++)
				{
					if(j==i)
            		continue;
					cout<<a[j]<<" ";
				}
				cout<<endl;
				f=0;
				break;
			}
		if(f==1)
        cout<<-1<<endl;
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1512D)

------------
# 思路：
先升序排序 $b$，显然有两种情况可以找到序列 $a$。

1. 项之和等于第 $n+1$ 项，也就是要扔掉第 $n+2$ 项；
2. $1$ 项之和减某一项等于第 $n+2$ 项，也就是要扔掉那某一项。

关于第二种情况，用 $rtmp$ 记录（前 $n+1$ 项之和减第 $n+2$ 项）的值。显然要删的那个项的值就是 $rtmp$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
const int N=2e5+7;
int b[N];
typedef long long ll;
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n+2;i++) cin>>b[i];
	sort(b+1,b+n+2+1);
	ll sum=0;
	for(int i=1;i<=n;i++) sum+=b[i];//前n项之和
	ll ltmp=b[n+1]-sum;
	ll rtmp=b[n+1]+sum-b[n+2];
	if(ltmp==0){//即满足第一种情况
		for(int i=1;i<=n;i++)cout<<b[i]<<' ';
		cout<<'\n';return;
	}
	ll index=-1;//保存要删掉的那个项的下标
	for(int i=1;i<=n+1;i++){
		if(b[i]==rtmp){
			index=i;break;
		}
	}
	if(index==-1){//即第二种情况也不满足，gg
		cout<<-1<<'\n';return;
	}
	for(int i=1;i<=n+1;i++){
		if(i==index) continue;
		cout<<b[i]<<' ';
	}
	cout<<'\n';return;
}
int main(){
//用函数可以快速跳出多重循环，而不用goto。
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Zhangikun (赞：0)

## 思路：
### 首先：
因为 $b$ 在被打乱前 $b_{n+1}$ 是 $b_1+b_2+......+b_{n-1}+b_n$ 所以打乱前的 $b_n+1$ 肯定在数组 $b$ 较靠后的地方，所以得先排序。
### 其次：
排完序后，用 $sum$ 数组维护前缀和（其实不用，还可以更简单，便于理解我就写前缀和了），枚举打乱前 $b_{n+2}$ 的那个随机数是打乱后的 $b_i$，那么就有两种情况：
1. 如果 $i\le n-1$，那么 $a$ 数组的和就是 $sum_{n+1}-b_i$，按理来说，和是 $b_{n+2}$，如果 $sum_{n+1}-b_i=b_{n+2}$ 就说明成立。
2. 如果 $i=n+2$，那么 $a$ 数组的和就是 $sum_n$，按理来说，和是 $b_{n+1}$，如果 $sum_n=b_{n+1}$ 就说明成立。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int cxk=2e5+10;
int sum[cxk],a[cxk];
void help()
{
  int n;
  cin>>n;
  n+=2;
  fill(a+1,a+n+1,0);
  fill(sum+1,sum+n+1,0);
  for(int i=1;i<=n;i++)
  {
    cin>>a[i];
    f[a[i]]=1;
  }
  sort(a+1,a+n+1);
  for(int i=1;i<=n;i++)
  {
    sum[i]=sum[i-1]+a[i];
  }
  for(int i=1;i<n;i++)
  {
    if(sum[n-1]-a[i]==a[n])
    {
      f[a[i]]=0;
      for(int j=1;j<n;j++)
      {
        if(j==i)continue;
        cout<<a[j]<<" ";
      }
      cout<<"\n";
      return;
    }
  }
  if(sum[n-2]==a[n-1])
  {
    for(int i=1;i<=n-2;i++)
    {
      cout<<a[i]<<" ";
    }
    cout<<"\n";
    return;
  }
  cout<<"-1\n";
  return;
}
int32_t main()
{
  int t;
  cin>>t;
  while(t--)
  {
    help();
  }
  return 0;
}
```


---

## 作者：_GW_ (赞：0)

看到题，马上就想到先将 $b$  序列排序，再枚举 $x$，然后判断。

具体怎么做呢？有 $n+2$ 个数字，先把他们给排序了，那么，要么是 $a$ 序列的和是这 $n+2$ 个数中最大的，要么是 $a$ 序列的和是第二大的，随机数 $x$ 是最大的。

如果 $a$ 序列的和是第二大的，那么 $a$ 序列就是 $b_1$ 到 $b_n$，直接输出即可。

另一种呢，则复杂一些。观察到只有 $x$ 是不变的，那么枚举 $x$，在输出即可。

如果一直没有输出，那就是无解，输出 $-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114514*2;
long long  a[N],b[N],num,data,n,m,T,sum;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        mp.clear();
        sum=0;
        for(int i=1;i<=n+2;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+3+n);//排序，方便计算。
        for(int i=1;i<=n;i++) sum+=a[i];
        if(sum==a[n+1])//a序列的和是第二大的。
        {
            for(int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
            flag=1;//记录。
        }
        bool flag=0;
        sum+=a[n+1];
        for(int i=1;i<=n+1;i++)//枚举x。
        {
            if(sum-a[i]==a[n+2])
            {
                for(int j=1;j<=n+1;j++) if(i!=j) cout<<a[j]<<" ";
                cout<<endl;
                flag=1;
                break;
            }
        }
        if(!flag) cout<<-1<<endl;//无解。
    }
    return 0;
}
```


---

## 作者：StayAlone (赞：0)

### 题意
现有一个长度为 $n$ 的 $a$ 数组，按照如下顺序进行操作后，得到一个 $b$ 数组，给定 $t$ 个 $b$ 数组，请输出其对应的 $a$ 数组的一个情况，若没有，输出 $-1$。

- $a_{n+1} = \sum\limits_{i=1}^{n} a_i$;
- $a_{n+2}$ 为一个随机整数 $x$;
- 打乱 $a$ 数组。

### 思路

仔细分析这道题，不难想到，如果合法，**排序后的数组**只有两种情况：
  
- $b_{n+1}$ 是和，$b_{n+2}$ 是随机数;
- $b_{n+2}$ 是和，$b_1\sim b_{n+1}$ 中的某一个是随机数。

当然，在答案存在时，有可能会有和与答案相等但在 $b_{n+1}$ 之前。

因此，我们换一种更加严谨的说法，两种情况分别是：
- 等于 $b_{n+1}$ 的是和，$b_{n+2}$ 是随机数；
- 等于 $b_{n+2}$ 的是和，$b_1 \sim b_{n+1}$ 中的某一个是随机数。

在其他情况下，**一定**会出现**有值大于和**的情况，因此不用考虑。  

接下来的实现比较轻松。

定义 $s1$ 表示 $\sum\limits_{i=1}^{n} b_i$；
$s2$ 表示 $\sum\limits_{i=1}^{n+1} b_i$，即 $s1+b_{n+1}$。  
先考虑第一种情况：  
$s1 = b_{n+1}$ 直接输出 $b_1,b_2,\cdots,b_n$。  

否则考虑第二种情况：  

定义函数 $f(k)$，将返回 $b_1\sim b_{n+1}$ 中 $k$ 的下标，若不存在，返回 $-1$。  

由于 $b_{n+2}$ 为和，因此 $s2 - b_{n+2}$ 的值即为随机数的值。  

如果这个值存在，则输出 $b_1\sim b_{n+1}$ 中，除了随机数以外的数。即使这个差值是负数，**因为它不存在**于数组中，因此同样会返回 $-1$ 而不输出。  

如果返回了 $-1$，则输出 $-1$。  

注意几个要开 $\texttt{long long}$ 的地方：  
$s1$， $s2$，$k$。
这个 $k$ 是指前面传入函数的值。  
~~为什么要开也很好算吧。~~

[AC code记录](https://www.luogu.com.cn/record/50588440)

解释一下，代码里面的 $a$ 数组 $\Leftrightarrow$ 上述中的 $b$ 数组。

```cpp
#include <bits/stdc++.h>
#define ll long long // 偷懒行为
using namespace std;
int t, n, a[200010];
int f(ll aim) // 返回 aim 的下标，不存在则返回 -1
{
	for (int i = 1; i <= n+1; ++i)
		if (a[i] == aim) return i;
	return -1;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n+2; ++i) scanf("%d", a+i);
		sort(a+1, a+3+n); // 一定要排序
		ll s1 = 0, s2 = 0;
		for (int i = 1; i <= n; ++i) s1 += a[i];
		if (s1 == a[n+1])
		{
			for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
			puts(""); continue; 
		}
		s2 = s1 + a[n+1];
		int x = f(s2 - a[n+2]);
		if (!~x) // 等价于 x == -1
		{
			puts("-1"); continue;
		}
		for (int i = 1; i <= n+1; ++i)
			if (x^i) printf("%d ", a[i]); //等价于 x ！= i
		puts("");
	}
	return 0;
}
```

写代码的时候一定要养成该开 $\texttt{long long}$ 的一定算好，不用开的就不开的习惯。


给一个**高级**的 hack 数据：  
```
1
55
70000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 80000000 95032704 95032704   
这是CF的第14个测试数据。
```

这个数据的 95032704 看起来很~~没用~~奇怪，其实是运用了计算机存储的知识，如果我的 $f$ 函数中的 $k$ 不开 $\texttt{long long}$，会被卡掉，卡掉的原因是 $s2 - b_{n+2}$ 会被函数找到。实际上是没有的，大家可以算算。

这个样例是怎么得到的嘛。。。 

![](https://cdn.luogu.com.cn/upload/image_hosting/wygxpf53.png)  

大家都知道，CF 里面虽然会给数据，然而省略号很烦。当时对于这个样例，我是这样处理的：

观察发现，每个数后面的 $0$ 很多，那我就判断一下，当输入为 $t$ 为 $1$，$n$ 为 $55$ 时，输出数组内数的值除以 $100000$。

然后有一点推理：得到了两个 $950$，但是能找到省略号之前的 $95032704$，因此把这两个 $950$ 改成 $95032704$，其它数乘 $100000$ 就得到了完整的测试数据。

---

## 作者：lingfunny (赞：0)

## Solution
设：$S=\sum_{i=1}^na_i$。


最简单的思路就是找出$S$ 和$x$ 是哪两个，是一个$\mathcal{O(n^3)}$的算法。

但稍微想一下就可以发现，因为$a_i$是正数，所以$S$ 必然大于其他的$a_i$，这样$S$ 就必然是$b$ 数组中第一大或者第二大的元素（可能小于$x$）。

这样就能想到一个$\mathcal{O(n)}$的算法（目前应该是题解区最快的吧）：

1. 求出数组$b$的最大值和次大值$mx1$与$mx2(mx1\ge mx2)$（当然也要记录它们的下标$idx$）；
2. 求出$b$ 数组的和$sum'$；
3. 暴力分两类，$S=mx1$或$S=mx2$。然后$\mathcal{O(n)}$枚举所有$b_i(i\not=idx)$，判断其为$x$ 时，$sum'-x$是否等于$2S$。

等等...$2S$？

可以发现，$\sum_{i=1}^{n+2}b_i=2Sm+x$，这时可以想到另一个$\mathcal{O(nlogn)}$的算法：

$\mathcal{O(n)}$枚举所有的$b_i$，当其为$x$ 时，判断$\frac{sum'-x}{2}$是否在$b$ 数组里。至于如何判断，只需要开个map存就好了。

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**枚举**的思路：

- 先记录每个数出现的次数 $mp_{b_i}$，记录所有数值和 $sum$。

- 接下来遍历序列，如果 $mp_{sum-2\times b_i}$ 存在，我们便可以构造出序列中额外的随机数，即为 $sum-2\times b_i$，需要特判随机数与总和相同。并做记录。

- 如果没有产生可构造情况（如上），无解。

- 接下来，我们只要保证输出时不把那个记录好的随机数和总和输出即可，剩余全部输出。

- 时间复杂度 $O(n)$。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define int long long//祖宗！
using namespace std;
const int N=2e5+5;
int t,n,b[N],sum,book1,book2;
bool flag1,flag2;
map<int,int>mp;//记录每个数出现次数
signed main()
{
	cin>>t;
	while(t--)
	{
		flag1=false;
		flag2=false;
		mp.clear();
		book1=-1;
		book2=-1;
		sum=0;//全部初始化
		cin>>n;
		for(int i=1;i<=n+2;i++)
		{
			cin>>b[i];
			sum+=b[i];
			mp[b[i]]++;//记录，统计
		}
		for(int i=1;i<=n+2;i++)
		{
			if(mp[(sum-2*b[i])])//可以构造
			{
				if(sum==3*b[i])//特判总和与额外随机数相同
				{
					if(mp[sum-2*b[i]]>=2)
					{
						book1=b[i];//记录其他数总和的数book1
						book2=sum-2*b[i];//记录额外的随机数book2
					}
				}
				else//无特判
				{
					book1=b[i];
					book2=sum-2*b[i];//同上记录
				}
			}
		}
		if(book1==-1&&book2==-1)//未产生可构造情况
		{
			cout<<"-1\n";//无解
			continue;
		}
		for(int i=1;i<=n+2;i++)
		{
			if(b[i]==book1)//与book1相等
			{
				if(flag1)//如果已经跳过了一个book1
				{//即出现两个与book1相等的数
					if(flag2||b[i]!=book2)
					{//并且此数不是book2或已经跳过了一个book2
						cout<<b[i]<<" ";
						continue;
					}
				}
				else//跳过book1
				{
					flag1=true;
					continue;
				}
			}
			if(b[i]==book2)//与book2相等
			{
				if(!flag2)//如果没跳过
				{
					flag2=true;//跳过
					continue;
				}
				else
				{
					cout<<b[i]<<" ";//可以输出
					continue;
				}
			}
			cout<<b[i]<<" ";//否则直接输出
		}
		cout<<"\n";
	}
	return 0;
}
~~~

---

