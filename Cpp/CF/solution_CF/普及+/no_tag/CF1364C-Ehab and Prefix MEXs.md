# Ehab and Prefix MEXs

## 题目描述

给出一个长度为 $n$ 的序列 $A$，你需要找到一个长度为 $n$ 的序列 $B$，满足 $A_i=mex(\{B_1,B_2,\dots,B_i\})$。

其中 $mex$ 函数的结果是最小的未出现在集合中的非负整数。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
0 1 2```

## 样例 #2

### 输入

```
4
0 0 0 2```

### 输出

```
1 3 4 0```

## 样例 #3

### 输入

```
3
1 1 3```

### 输出

```
0 2 1```

# 题解

## 作者：H6_6Q (赞：5)

### 题目翻译：
刚开始给你一个空的数组 $b\ (b_i \le 10^6)$ , 每次可以将任意一个数填入该数组中 , 但是必须保证第 $i$ 次放完后该数组的 $\text{mex}$ 为 $a_i \ (a_i\le 10^5)$。请你求出放数字的顺序。若没有合法的顺序就输出 `-1` 。

数据保证 $a$ 数组单调上升。

一个数组的 $mex$ 即在这个数组中最小的没有出现过的自然数。

### 思路：

CF 的传统构造题 , 其实很好想。

显然，如果 $a_i>=i$ 那显然是没有合法的顺序的，因为如果要使第 $i$ 次的 $\text{mex}=a_i$ , 就至少要放 $a_i$ 个数 , 而因为 $a_i>=i$  , 能放数的位置就会小于 $a_i$ , 故一定不合法。

那么我们可以将 $b_i$ 分成两种：

1. 放置对 $a_i$ 有影响的数字。
1. 放置对 $a_i$ **暂时**没有影响的数字。

因为有影响的数字定下来了就无法改变，那么我们可以记录一个指针 $now$ ，指向暂时没有影响的 $a_i$ 中 $i$ 最小的元素。

显然，所填的数一定也是单调递增的，所以还可以在记录一个标记 $num$ 表示现在已经填到了数字几。

这样的话我们每读到一个 $a_i$ ，就要判断 $num$ 是否已经到达了 $a_i-1$ ，如果没有就需要将从 $num \sim a_i-1$ 中的数全部填上。

因为越 $i$ 越小，留的余地就越大，所以每当需要填数时，就把他填在 $now$ 所指向的位置，并将这个 $b_i$ 纳入对 $a_i$ 有影响的那一类中。

但是需要注意的点是，当 $a_i$ 这个数首次出现时，$b_i$ 一定是对 $a_i$ 有影响的，因为第 $i$ 次填数导致了 $a_i$ 的变化。

而那些直到最后也没有对 $a_i$ 造成影响的 $b_i$ ，我们可以把他们全部设为 $10^6$ ，因为 $a_i \le 10^5$ 而 $b_i \le 10^6$，所以填 $10^6$。一定不会对 $a_i$ 造成影响。

### Code：
```

#include<bits/stdc++.h>
 
using namespace std;
 
int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
 
const int N=1e5+5;
int n,a[N],b[N],have,num,now=1;
 
int main()
{
	memset(b,-1,sizeof(b));
	// 将 b 数组全部设为暂时无影响 
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i)
	{
		if(a[i]>i)
		// 若 a_i > i 则一定无解 
		{
			printf("-1\n");
			return 0;
		}
		for(;num<=a[i]-1;++num)
		// 将 num ~ a_i-1 里的数全部填上 
		{
			if(b[i]==-1)
			// 如果 a_i 首次出现，则 b_i 一定有影响 
				b[i]=num;
			else
			{
				while(b[now]!=-1)
				// 找到暂时没有影响中 i 最小的位置 
					now++;
				// 将这个位置填上； 
				b[now]=num;
			}
		}
		num=a[i];
	}
	for(int i=1;i<=n;++i)
		if(b[i]==-1) printf("%d ",1000000); // 最后也没有影响的直接输出10^6 
		else printf("%d ",b[i]);
	return 0;
} 
```


---

## 作者：EDqwq (赞：3)

### 思路：

首先，我们来观察一下 $ \operatorname{mex} $ 的性质。

如果一个位置他的 $ \operatorname{mex} $ 为一个数，那么这个位置前面必定出现了 0 - （$ \operatorname{mex} $ - 1) 里的所有数。

一个 $ \operatorname{mex} $ 数列，一定是单调不减的。

所以，我们可以判无解了。

如果一个位置比之前某个位置小，那显然不行，或者如果某个位置 $i$ ，它小于 $a_i$ 那也显然无解。

接下来是构造。

我们需要在一个位置前面填满所有的比这个位置小的数。我们可以把前面一部分的位置拿来填，剩下的乱填即可，但是数字不能影响到答案，可以取一个很大的值，例如 114514 。

***

### 代码：

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n;
int a[1000010];
int b[1000010];
int maxx;
int now,num;

signed main(){
	mem(b,-1);
	cin>>n;
	for(int i = 1;i <= n;i ++)a[i] = read();
	for(int i = 1;i <= n;i ++){
		if(a[i] > i){
			puts("-1");
			return 0;
		}
		if(a[i] < a[i - 1]){
			puts("-1");
			return 0;
		}
	}
	now = 1;
	for(int i = 1;i <= n;i ++){
		for(int j = num;j <= a[i] - 1;j ++){
			if(b[i] == -1)b[i] = j;
			else {
				while(b[now] != -1)now ++;
				b[now] = j;
			}
			num = j;
		}
		num = a[i];
	}
	for(int i = 1;i <= n;i ++)b[i] == -1 ? cout<<"114514 " : cout<<b[i]<<" ";
	return 0;
}
```

---

## 作者：b6e0_ (赞：3)

[CF题面传送门](https://codeforces.com/contest/1364/problem/C) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1364C) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1364C)

本题不可能输出$-1$。因为题目中保证了$a_i\le i$且$a_{i-1}\le a_i$。因为每一个$a_i$都能保证前面的排列包含$0$~$a_i-1$，且不可能出现前面没出现的最小数大，后面出现的最小数小的情况。

分析性质。
1. 对于每一个$i$（$1\le i\le n$），$b_1$~$b_i$中都不能有$a_i$。
2. 对于每一个$i$（$2\le i\le n$），如果$a_i\not=a_{i-1}$，那么$b_i$一定为$a_{i-1}$。

题目中保证了$a$数组一定是非严格单调递增的，我们可以使$b$数组尽量严格单调递增，这样就好用尺取法快速判断当前填的数在后面的$a_i$中有没有。

但是，因为第二条性质，实际中$b$数组可能不是严格单调递增的。但其他的数一定是严格单调递增的，所以用尺取法判断重复就行了。赛时代码，写的很丑：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010];
int main()
{
	int n,i,j=1,num;//num为当前填的数字
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	b[1]=0;
	while(j<=n&&b[1]>a[j])//开始前做一遍
		j++;
	while(b[1]==a[j])
	{
		if(b[1]==a[j])
			b[1]++;
		while(j<=n&&b[1]>a[j])
			j++;
	}
	num=b[1]+1;
	for(i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1])//性质2
			b[i]=a[i-1];
		else
		{
			b[i]=num;
			while(j<=n&&b[i]>a[j])
				j++;
			while(b[i]==a[j])
			{
				if(b[i]==a[j])
					b[i]++;
				while(j<=n&&b[i]>a[j])
					j++;
			}
			num=b[i]+1;//更新num
		}
	}
	for(i=1;i<=n;i++)
		cout<<b[i]<<' ';
	return 0;
}
```
时间复杂度为$O(n)$。

---

## 作者：AlicX (赞：1)

## Solution 

看了一下题解，好像都写的比较复杂。

首先这道题没有无解的情况，因为只有出现逆序对或者 $a_i >i $ 才会无解，然而题目保证了 $a_i \leq a_{i+1}$ 且 $a_i \leq i$，所以都有解。

不妨用一个 `set` 存可填的数，而 $b_i$ 一定是填最小的。那什么数可填呢？假设当前在 $i$，$a_{i+1} \sim a_n$ 这些数和以前填的数不可填，其它数可填。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h> 
#define ll long long  
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=1e5+10; 
int n; 
int mp[N]; 
int a[N],b[N]; 
signed main(){ 
	n=read(); set<int> s; 
	for(int i=1;i<=n;i++) a[i]=read(),mp[a[i]]++; 
	for(int i=0;i<=n+1;i++) if(!mp[i]) s.insert(i); 
	for(int i=1;i<=n;i++){ 
		b[i]=*s.begin(); s.erase(s.begin()); mp[a[i]]--; 
		if(!mp[a[i]]) s.insert(a[i]);  
	} for(int i=1;i<=n;i++) printf("%d ",b[i]); puts(""); return 0; 
} 
```

---

## 作者：huayucaiji (赞：1)

~~这个题比 A 简单~~

这个题有一个很重要的条件

>**It’s guaranteed that $a_i\leq a_{i+1}$ for $1\leq i<n$**

所以我们可以进行这样的处理，先找出所有的没出现的数字。如果 $a_i=a_{i-1}$。那么我们为了尽量让题目有解，一定要尽量把更大的数放进答案数组 $b$ 里。如果 $a_i\neq a_{i-1}$。我们就要把 $a_{i-1}$ 放到 $b_i$ 上，因为这个数字不再是最小未出现过的数了。其实这个题还是非常简单的。

什么时候无解呢？我们现在极限的来操作一下 $b$ 数组

|i=|1|	2|	3|	4|	5|	6|	…	|i|
|---|---|---|---|---|---|---|---|---|
|b=	|0|	1|	2|	3|	4|	5|	…	|i-1|
|a=|1|	2|	3|	4|	5|	6|	…	|i|
我们发现 $a_i$ 的最大值为 $i$，所以如果输入时 $a_i>i$，输出 $-1$ 即可。
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

const int maxn=1e6+10;

int n,a[maxn],b[maxn],maxx[maxn];
bool ex[maxn];
vector<int> v;//存放未出现的数字

signed main() {
	n=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
		ex[a[i]]=1;
		if(a[i]!=0&&a[i]>i) {//注意 a_i!=0
			cout<<-1<<endl;
			return 0;
		}
	}
	for(int i=0;i<=1e6;i++) {
		if(!ex[i]){
			v.push_back(i);
		}
	}
	int index=0;//记录当前放到哪个数
	
	for(int i=1;i<=n;i++) {
		if(i==1||a[i]==a[i-1]) {
			b[i]=v[index++];
		}
		else {
			b[i]=a[i-1];
		}
		
		printf("%lld ",b[i]);
	}
	return 0;
}
```

---

## 作者：songtaoran (赞：0)

简单题。  
由于是 MEX，所以不可能的情况当且仅当 $a_{i + 1} \leq a_i$。  
如果 $a_i \ne a_{i - 1}$，因为这个数字从没有突然变到有了，所以 $ans_i = a_{i - 1}$。  
如果 $a_i = a_{i - 1}$，则取一个没有在 $a_i$ 中出现过的数即可。  
为什么呢？因为如果这个时候取一个 $a_i$ 中出现过的数，那么有两种可能：
+ 选重了。这对答案显然不好。
+ 没选重。即这个数字会在接下来的 $a_i$ 中出现，但是到了那个时候由于 $a_i$ 已经被选了，所以 MEX 就不是 $a_i$ 了，不合法。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, a[200010];
ll b[200010];
bool f[200010];
ll can[1000010], len = 0;
int main(){
	memset(b, -1, sizeof b);
	cin >> n;
	for(ll i = 1; i <= n; i++) scanf("%lld", &a[i]), f[a[i]] = 1;
	for(ll i = 0; i <= 1000000; i++)
		if(!f[i]) can[++len] = i;
	for(ll i = 1; i < n; i++)
		if(a[i + 1] < a[i])
			return puts("-1"), 0;
	for(ll i = 2; i <= n; i++)
		if(a[i] != a[i - 1]) b[i] = a[i - 1];
	ll now = 1;
	for(ll i = 1; i <= n; i++)
		if(b[i] == -1){
			b[i] = can[now]; now++;
		}
	for(ll i = 1; i <= n; i++)
		printf("%lld ", b[i]);
	return 0;
}
```
[提交记录 - $292435727$](https://codeforces.com/problemset/submission/1364/292435727)

---

## 作者：Isshiki_Hugh (赞：0)

我们观察&打表发现，对于$a[p]$，在$b[i]$中可能出现的第一个位置是$b[p+1]$。

由于$a[i]$具有不下降的性质，所以我们找到每一串相等的$a[x]$的最后一个，将它赋值给$b[x+1]$，然后再从小到大把其他数填充到没写过的地方就行了

题设已经保证了答案存在，所以大胆填吧！



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

int n,p,a[111111];
bool flag[111111];

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> n;
    rep(i,1,n){
        cin >> a[i];
        flag[a[i]] = true;
    }
    if(a[1] == 1) flag[0] = true;
    a[0] = 0;
    rep(i,1,n){
        if(a[i] == a[i-1]){
            while(p <= n+1 && flag[p]) ++p;
            flag[p] = true;
            cout << p << " ";
        } else cout << a[i-1] << " ";
    }

    return 0;
}
```

---

