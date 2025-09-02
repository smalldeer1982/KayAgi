# Download More RAM

## 题目描述

有一家商店有 $n$ 种不同的软件，可以增加你的内存。第 $i$ 个内存增加软件需要 $a_i$ GB 的内存来运行（这是暂时的。一旦程序运行完毕，您就可以恢复内存），并**永久**提供额外的 $b_i$ GB 内存。**每个软件只能使用一次**。您的电脑当前有 $k$ GB 内存。请注意，如果需要使用比当前更多 GB 的内存，则不能使用内存增加软件。

因为内存是世界上最重要的东西，你想知道，能运行的软件全部运行完后，可以达到的最大内存量是多少？

## 样例 #1

### 输入

```
4
3 10
20 30 10
9 100 10
5 1
1 1 5 1 1
1 1 1 1 1
5 1
2 2 2 2 2
100 100 100 100 100
5 8
128 64 32 16 8
128 64 32 16 8```

### 输出

```
29
6
1
256```

# 题解

## 作者：ttq012 (赞：2)

贪心。

我们按照运行需要的内存数量来从小到大排序，然后暴力模拟，如果运行程序需要的内存大于当前的内存，那么代表当前和剩下的内存增加软件都不可以使用了，直接跳出循环，否则就加入可以增加的内存数量即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node {
    int x, y;
    bool operator < (const node &_1) {
        return x < _1.x;
    }
} a[1000010];

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n;
        long long m;
        scanf ("%d%lld", &n, &m);
        for (int i = 1; i <= n; i ++) {
            scanf ("%d", &a[i].x);
        }
        for (int i = 1; i <= n; i ++) {
            scanf ("%d", &a[i].y);
        }
        sort (a + 1, a + n + 1);
        for (int i = 1; i <= n; i ++) {
            if (a[i].x <= m) {
                m += a[i].y;
            } else {
                break;
            }
        }
        printf ("%lld\n", m);
    }
    return 0;
}
```


---

## 作者：fls233666 (赞：1)

我们注意到 $a_i,b_i$ 都是大于 $0$ 的数，所以我们为了换取更多的内存，目标就变成了**尽可能运行更多的软件。**

因为每次运行一个软件，内存就会增加。而内存增加，我们又可以运行更多的软件。我们不妨把每个软件按照 $a_i$ 从**小到大排序**。先运行需要的内存少的软件，随着内存增加，再运行需要的内存更大的软件，直到不能运行新的软件为止。

总结一下，对于每组数据，程序处理分为四步：

1. 读入 $n,k,a_i,b_i$；
2. 把软件按 $a_i$ 从小到大排序；
3. 从 $a_i$ 小的软件开始运行，直到不能运行新的软件或者全部软件都运行过一次；
4. 输出最后的内存大小。

于是这题就做完了。下面是 Python 3 代码：

```python
test = (int)(input())

for ti in range (1,test+1,1):
    
    n,k=[ int(i) for i in input().split() ]
    a = [ int(i) for i in input().split() ]
    b = [ int(i) for i in input().split() ]
	#读入数据
    
    for i in range (0,n,1):
        for j in range (i,n,1):
            if a[i]>a[j]:
                tmp = a[i]
                a[i] = a[j]
                a[j] = tmp
                tmp = b[i]
                b[i] = b[j]
                b[j] = tmp
	#暴力排序

    for i in range (0,n,1):
        if k>=a[i]:
            k+=b[i]
        else:
            break
	#运行软件

    print(k) #输出答案
```



---

## 作者：清烛 (赞：0)

## Description
$n$ 个程序，第 $i$ 个程序运行时需要占用 $a_i$ GB 内存（要求当前内存不低于 $a_i$），运行完之后会使得本机增加 $b_i$ GB 内存。

已知一开始有 $k$ GB 内存，问最后最多能达到多少 GB 内存。

## Solution
按照 $a_i$ 从小到大排序即可，每次选能跑的需要最小内存的程序。

是一个比较简单的贪心。
## Implementation
```cpp
using pii = pair<int, int>;
pii a[105];

int main() {
    int T; read(T);
    while (T--) {
        int n, k; read(n, k);
        FOR(i, 1, n) read(a[i].first);
        FOR(i, 1, n) read(a[i].second);
        sort(a + 1, a + n + 1);
        FOR(i, 1, n) {
            if (a[i].first > k) break;
            k += a[i].second;
        }
        print(k);
    }
    return output(), 0;
}
```

---

## 作者：BaCO3 (赞：0)

## 题目大意
你的电脑现在有 $k$ GB 的内存，有 $n$ 个可以增加内存的软件（只能用一次），第 $i$ 个使用时占用 $a_i$ GB 的内存（临时的），结束时你会增加 $b_i$ GB 的内存。求你的电脑可拥有的最大内存。

## 分析
直接贪心就可以了。

因为使用过的内存会归还，所以我们只需要将软件按 $a_i$ 从小往大排个序，遍历直至现在拥有的内存小于目前软件运行需要的内存时，你拥有的内存就是最大值了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,k;
struct RAM{
	int u,v;
}a[105];

bool cmp(RAM a,RAM b){
	return a.u<b.u;
}

int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i].u;
		for(int i=1;i<=n;i++) cin>>a[i].v;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(a[i].u>k) break;
			k+=a[i].v;
		}
		cout<<k<<endl;
	}
    
    return 0;
}

```


---

## 作者：Violet___Evergarden (赞：0)

# CF1629A
## 题意
你最开始有 $k$ 的内存，你有 $n$ 个软件，第 $i$ 个软件运行需要 $a_i$ 的内存，运行之后可以获得 $b_i$ 的内存。运行软件仅仅是需要内存但不花费内存。
## 解法
**贪心**。因为我们要尽量多的运行软件，所以对于每个软件，我们都要保证把能运行的先运行完，再来看这个能不能运行。那么就可以把它们按 $a_i$ 从下到大、$a_i$ 相同是按 $b_i$ 从大到小的顺序排序，然后按顺序判断内否运行即可。
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct P
{
  int a,b;
}p[101];
int t;
int n,k;
bool cmp(P i,P j)
{
  return i.a==j.a?i.b>j.b:i.a<j.a;
}
int main()
{
cin>>t;
while(t--)
{
  cin>>n>>k;
  for(int i=1;i<=n;i++)
  {
    cin>>p[i].a;
  }
  for(int i=1;i<=n;i++)
  {
    cin>>p[i].b;
  }
  int now=k;
  sort(p+1,p+n+1,cmp);
  for(int i=1;i<=n;i++)
  {
    if(now>=p[i].a)now+=p[i].b;
  }
  cout<<now<<"\n";
}
return 0;
}
```

---

## 作者：Crab_time (赞：0)

题目大意略

这个题主要方法就是用结构体存储 $a$ 和 $b$ ，按 $a$ 从小到大排序，然后用循环将 ${a}_i$ 依次与 $k$ 比较，若 $k \ge {a}_i  $ 则增加 $ {b}_i $ ，若 $k < {a}_i$ 则退出循环。

小提示：这里如果自己写 ```cmp``` 函数时，如果用 ```sort``` 则等于时不能返回 ```true``` 否则会卡RE 建议如果要等于时返回 ```true``` 用 ```stable_sort``` 。

完整代码如下：
```cpp
//A. Download More RAM

#include<iostream>
#include<algorithm>
using namespace std;

struct ram
{
    int a,b;
}r[101];

bool cmp(ram a,ram b)
{
    if(a.a <= b.a)
    {
        return true;
    }
    return false;
}

int main()
{
    long t,n,k,i,j;
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        for(i = 0;i<n;i++)
        {
            cin >> r[i].a;
        }
        for(i = 0;i<n;i++)
        {
            cin >> r[i].b;
        }
        stable_sort(r,r+n,cmp);
        j=k;
        for(i = 0;i<n;i++)
        {
            if(r[i].a <= j)
            {
                j += r[i].b;
            }
            else{
                break;
            }
        }
        cout << j << endl;
    }
    return 0;
}
```
第一篇题解，求过审

---

## 作者：zhicheng (赞：0)

### 分析

题目要求所有软件运行完之后的内存最大值，因此我们考虑贪心，让耗内存最小的软件先运行，这样可以保证能运行的所有软件都运行过，于是运行完之后的内存就可以保证最大。

### 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct s{
	int a,b;
}x[110];
bool cmp(s x,s y){
	return x.a<y.a;
}
int main(){
	int n,m,p,now;
	scanf("%d",&n);
	while(n--){
		now=0;
		memset(x,0,sizeof(x));
		scanf("%d%d",&m,&p);
		for(int i=0;i<=m-1;i++){
			scanf("%d",&x[i].a);
		}
		for(int i=0;i<=m-1;i++){
			scanf("%d",&x[i].b);  //结构体存数组a、b
		}
		sort(x,x+m,cmp);
		while(p>=x[now].a&&now<m){
			p+=x[now++].b;  //从内存最小的开始运行，保证答案最大
		}
		printf("%d\n",p);
	}
}
```
~~大水题~~

---

## 作者：Unnamed114514 (赞：0)

### 题意
你有 $k$ 个内存，现在有 $n$ 个任务，完成每个任务需要 $a$ 个内存，完成后会把这 $a$ 个内存回收，并且给你 $b$ 个内存，求最后可以获得的最多内存的数量。
### 思路
因为浪费会回收，所以先取那个后取那个不重要，那么我们先取需求量少的即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int res=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    	ch=getchar();
    while(ch>='0'&&ch<='9'){
    	res=(res<<1)+(res<<3)+(ch^'0');
    	ch=getchar();
    }
    return res;
}
int T,n,k;
struct node{
    int a,b;
    inline bool operator <(const node &t) const{
    	if(a==t.a)
    		return b>t.b;
    	return a<t.a;
    }
}f[105];
int main(){
    T=read();
    while(T--){
    	n=read(),k=read();
    	for(int i=1;i<=n;++i)
    		f[i].a=read();
    	for(int i=1;i<=n;++i)
    		f[i].b=read();
    	stable_sort(f+1,f+n+1);
    	for(int i=1;i<=n;++i){
    		if(k<f[i].a)
    			break;
    		k+=f[i].b;
    	}
    	printf("%d\n",k);
    }
    return 0;
}
```

---

## 作者：CmsMartin (赞：0)

### 题意简述

[题目传送门](https://codeforces.com/contest/1629/problem/A)

现在又一些软件，第 $i$ 个软件运行的时候会占用 $a_i GB$ 的内存（程序停止运行后会停止占用内存），运行结束后会使你的电脑额外增加 $b_iGB$ 的内存，你的电脑原来有 $kGB$ 内存，请问在运行完这些软件后内存最多为多少（每个软件只能运行一次）

### 思路

~~非常水的一道题~~

很显然使用结构体将 $a_i$ 和 $b_i$ 捆绑起来，并以 $a_i$ 为关键词排序，能运行时就直接运行软件，如果运行不了就结束。

正确性显然。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<class T>
inline char read(T &ret) {
	ret = 0;
	char c = getchar();
	short f = 1;
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c <= '9' && c >= '0') {
		ret = (ret << 3) + (ret << 1) + c - 48;
		c = getchar();
	}
	ret *= f;
	return c;
}

int T;
int N , K;
int A[110] , B[110];
multiset<pair<int , int> > SoftWare;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--) {
		memset(A , 0 , sizeof A);
		memset(B , 0 , sizeof B);
		SoftWare.clear();
		cin >> N >> K;
		for(int i = 1; i <= N; i++) {
			cin >> A[i];
		}
		for(int j = 1; j <= N; j++) {
			cin >> B[j];
		}
		for(int i = 1; i <= N; i++) {
			SoftWare.insert(make_pair(A[i] , B[i]));
		}
		for(multiset<pair<int , int> >::iterator it = SoftWare.begin(); it != SoftWare.end(); it++) {
			if(it -> first <= K) {
				K += it -> second;
			}
			else break;
		}
		cout << K << endl;
	}
	return 0;
}
```

---

## 作者：shiranui (赞：0)

~~这道题我居然看了好久才看懂……~~

## 题目大意
给定 $n$ 个能增加空间的神奇软件，每个软件将占用 $a[i]$ 的空间，并为你带来 $b[i]$ 的空间。最开始你有 $k$ 的空间，问你最多能有多少空间。

## 思路
为了让最后的空间最大，我们肯定要从最优的开始取。

我们把这些软件排个序。

具体规则：占用空间小的优先，占用空间相同时附赠空间多的优先（据说这条可以不用？）。

代码见下：

```cpp
struct node
{
	int a, b;
} s[1100];
bool cmp(node x, node y)
{
	if (x.a != y.a) return x.a < y.a;
	return x.b > y.b;
}
```

取用软件：

```cpp
int cnt = k, p = 1;//cnt:目前所有的内存大小 p:取用第几个软件
while (s[p].a <= cnt && p <= n)
	cnt = cnt + s[p++].b;
```

注意：一定要写 ```p <= n``` ！

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n, k;
struct node
{
	int a, b;
} s[1100];
bool cmp(node x, node y)
{
	if (x.a != y.a) return x.a < y.a;
	return x.b > y.b;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		for (int i = 1; i <= n; i++) cin >> s[i].a;
		for (int i = 1; i <= n; i++) cin >> s[i].b;
		sort (s + 1, s + 1 + n, cmp);
		int cnt = k, p = 1;
		while (s[p].a <= cnt && p <= n)
			cnt = cnt + s[p++].b;
		cout << cnt << endl;
	}
	return 0;
} 
```

## 结语

~~确实是道水题，我居然在16分钟是才A了……~~

注意一些小细节。

祝过题愉快。

---

