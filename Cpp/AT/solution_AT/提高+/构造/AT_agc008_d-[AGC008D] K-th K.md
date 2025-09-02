# [AGC008D] K-th K

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_d

長さ $ N $ の数列 $ x $ が与えられます。 次の条件をすべて満たす数列 $ a $ が存在するか判定し、存在するならば $ a $ を $ 1 $ つ構成してください。

- $ a $ は長さ $ N^2 $ であり、整数 $ 1 $, $ 2 $, $ ... $, $ N $ をそれぞれちょうど $ N $ 個ずつ含む。
- 各 $ 1\ <\ =\ i\ <\ =\ N $ について、$ a $ に含まれる整数 $ i $ のうち左から $ i $ 番目に位置するものは、$ a $ 全体では左から $ x_i $ 番目に位置する。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 500 $
- $ 1\ <\ =\ x_i\ <\ =\ N^2 $
- $ x_i $ はすべて相異なる。

### Sample Explanation 1

たとえば、$ a $ に含まれる整数 $ 2 $ のうち左から $ 2 $ 番目に位置するものは、$ a $ 全体では左から $ 5 $ 番目に位置しています。 整数 $ 1 $, $ 3 $ についても同様に条件が成り立っています。

## 样例 #1

### 输入

```
3
1 5 9```

### 输出

```
Yes
1 1 1 2 2 2 3 3 3```

## 样例 #2

### 输入

```
2
4 1```

### 输出

```
No```

# 题解

## 作者：CYJian (赞：6)

## AGC 008 D

这题还算挺简单的

考虑 $p_i$ 为数字 $i$ 第 $i$ 次出现的位置，发现给出的这个限制条件还包含了： $1$~$p_i-1$ 中有 $i-1$ 个 $i$，$p_i + 1$~$n$ 有 $n-i$ 个 $i$。

不难发现，一个可行的构造方法是：每次贪心选一个 $p_i$ 最小的 $i$，然后在最前面 $i-1$ 个空位填上 $i$ ，如果发现这个时候第 $i-1$ 个数的位置大于 $i$，那么肯定不合法。

然后类比一下，我们再每次贪心选择一个 $p_i$ 最大的 $i$，然后在最后面 $n-i$ 个空位填上 $i$，如果填上去的最后一个数的位置小于 $p_i$，那么就不合法。

如果不存在不合法的情况，那么就构造出来一组可行解了。这时候输出这个解就好了。

${\rm Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T>
inline void chkmin(T&a, T b) { a = a < b ? a : b; }

const int MAXN = 300000;

int p[MAXN];
int vis[MAXN];
int ans[MAXN];
int cnt[MAXN];
int pos[MAXN];

int main() {
	int n = ri;
	for(int i = 1; i <= n; i++) {
		int x = p[i] = ri;
		if(vis[x]) {
			puts("No");
			return 0;
		}
		cnt[x] = i;
		vis[x] = 1;
		ans[x] = i;
		pos[x] = i;
	}
	int N = n * n;
	for(int i = 1; i <= N; i++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= N; i++)
		if(cnt[i] > i) { puts("No"); return 0; }
	int p = 1;
	for(int i = 1; i <= N; i++) {
		if(ans[i]) {
			int c = ans[i] - 1;
			while(c--) {
				while(ans[p]) ++p;
				if(p > i) {
					puts("No");
					return 0;
				} ans[p] = ans[i];
			}
		}
	} p = N;
	for(int i = N; i >= 1; i--) {
		if(pos[i]) {
			int c = n - pos[i];
			while(c--) {
				while(ans[p]) --p;
				if(p < i) {
					puts("No");
					return 0;
				} ans[p] = ans[i];
			}
		}
	}
	puts("Yes");
	for(int i = 1; i <= N; i++) printf("%d ", ans[i]);
	return puts(""), 0;
}
```

---

## 作者：EternalHeart1314 (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/AT_agc008_d)

# 题意

有一个整数 $n$ 和 一个长度为 $n$ 的序列 $X$。

要构造出一个序列 $a$，长度为 $n^2$，使得 $a_{X_i}=i$，$[1,X_i-1]$ 这个区间里有 $i-1$ 个 $i$，$[X_i+1,n^2]$ 这个区间里有 $n-i$ 个 $i$。

# 思路

一个简单的贪心。

首先令 $a_{X_i}=i$。

然后按 $X_i$ **从小到大**的顺序遍历，进行填数，具体地：

对于当前 $X_i$，将 $a$ 中前 $X_i-1$ 个可以填数的位置填上 $i$。如果填数的位置有一个或多个大于 $X_i$ 的，为无解情况。

接着按 $X_i$ **从大到小**的顺序遍历，进行填数，具体地：

对于当前 $X_i$，将 $a$ 中后 $n-X_i$ 个可以填数的位置填上 $i$。如果填数的位置有一个或多个小于 $X_i$ 的，为无解情况。

上述“可以填数的位置”可以理解为“没填过数的位置”。

代码中的 $i$ 和上述的 $i$ 不同。

时间复杂度 $O(n^2)$。

# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N(2.5e5 + 7);
int n, m, a[N], b[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	m = n * n;
	for(int i = 1, x; i <= n; ++ i) {
		cin >> x;
		a[x] = i, b[x] = 1;
	}
	for(int i = 1, j = 1, k; i <= m; ++ i) {
		if(a[i]) {
			k = a[i] - 1;
			while(k --) {
				while(a[j]) {
					if(a[j] == a[i]) {
						return cout << "No\n", 0;
					}
					++ j;
				}
				a[j ++] = a[i];
			}
		}
	}										//顺着填 
	for(int i = m, j = m, k; i >= 1; -- i) {
		if(b[i]) {
			k = n - a[i];
			while(k --) {
				while(a[j]) {
					if(a[j] == a[i]) {
						return cout << "No\n", 0;
					}
					-- j;
				}
				a[j --] = a[i];
			}
		}
	}										//逆着填 
	cout << "Yes\n";
	for(int i = 1; i <= m; ++ i) {
		cout << a[i] << ' ';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：yaotianhao (赞：4)

这道题主要是贪心，想到贪心思想，就比较~~简单~~。（还有很多细节

贪心策略是：对于每一个输入的 $x_i$，都直接填入，之后就把 $x_i$ 位置前的 $i-1$ 个 $i$ 按照 $x_i$ 的从小到大顺序进行填充，如果没有位置填充时，就是无解。除了 $x_i$ 前的 $i$，$x_i$ 后的 $n-i$ 个 $i$ 也要按照 $x_i$ 从大到小的顺序进行填充，如果没有位置填充，也是无解。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,a[N*N],s[N*N],sum,p,b[N*N];
struct node{
    int x,t;
}c[N];
bool cmp(node l,node r){
    return l.x<r.x;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i].x;
        c[i].t=i,a[c[i].x]=i;
    }
    for(int i=1;i<=n*n;i++){//预处理剩下的位置
        if(a[i-1]!=0) s[i]=s[i-1];
        else s[i]=s[i-1]+1;
    }
    sort(c+1,c+n+1,cmp);//可能x[i]会不按照顺序来，所以要排序
    for(int i=1;i<=n;i++){
        sum+=(c[i].t-1);
        if(s[c[i].x]<=sum){//如果剩下的位置不够，就无解
            cout<<"No";
            return 0;
        }
        int ans=0;
        while(ans<(c[i].t-1)){
            ++p;
            if(a[p]!=0){
                continue;
            }
            a[p]=c[i].t,ans++;
        }
    }
    sum=0,p=n*n+1;
    memset(s,0,sizeof(s));
    for(int i=n*n;i>=1;i--){//反着的剩下的位置
        if(a[i+1]!=0) s[i]=s[i+1];
        else s[i]=s[i+1]+1;
    }
    for(int i=n;i>=1;i--){
        sum+=(n-c[i].t);
        if(s[c[i].x]<=sum){//无解
            cout<<"No";
            return 0;
        }
        int ans=0;
        while(ans<(n-c[i].t)){
            --p;
            if(a[p]!=0){
                continue;
            }
            a[p]=c[i].t,ans++;
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n*n;i++){
        cout<<a[i]<<" ";
    }
}
```

---

## 作者：spire001 (赞：3)

## AT_agc008_d
### 题目大意
让你构造一个序列，使其满足 $a_{x_i}=i$ 并且 $i$ 在 $a_i,i\in[1,x_i]$ 中出现了 $i$ 次。
### 解题思路

题目明着让你构造，显然不太可能是动态规划。

那么考虑贪心。先去反向思考一下，第一个样例是有解的，哪些失败的操作可能导致其不满足题意呢？

样例输入：
```
3
1 5 9
```

一个正确的答案：
```
1 1 1 2 2 2 3 3 3
```

你发现，如果你把 $3$ 放的太前，或者把 $1$ 放的太后，都会让构造出来的序列不合法。

进一步的，你发现如果 $x_i$ 大的你先放或者 $x_i$ 小的你后放，这影响答案正确性的概率更大。你需要避免这种情况。

于是，你需要对 $x_i$ 排序，$x_i$ 大的你后放，$x_i$ 小的你先放。最后判断合法性并输出。

### 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int N = 502;
int n, x[N], m, a[N * N], cnt = 1, tong[N * N], ln;

struct node{
  node(int _nums = 0, int _times = 0, int _pos = 0) : nums(_nums), times(_times), pos(_pos) {}

  int nums, times, pos;
}; 
node bef[N * N];

bool check() // 判断最终答案合法性
{
  for (int i = 1; i <= n; i++)
  {
    int t = 0;
    for (int j = 1; j != x[i]; j++)
      if (a[j] == i) 
        t++;
    
    if (t != i - 1) return false;
  }

  return true;
}

int main()
{
  cin >> n; m = n * n; 

  for (int i = 1; i <= n; i++) 
  {
    cin >> x[i];
    a[x[i]] = i; // 这个位置已经可以判断了。
    bef[i] = node(i, i - 1, x[i]); // 在 1 ~ x[i] - 1 插入 i - 1 个 i
    tong[i] = n - i; // 还剩下 n - i 个
  }

  sort(bef + 1, bef + n + 1, [&](const node A, const node B){
    return A.pos > B.pos;
  }); // 排序

  for (int i = n; i >= 1; i--)
  {
    for (int j = 1; j <= bef[i].times; j++)
    {
      while (a[cnt]) cnt++; // 已经放过了就不放了
      a[cnt] = bef[i].nums;
    }
  }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= tong[bef[i].nums]; j++)
    {
      while (m && a[m]) m--; // 为了鲁棒性判断下 m > 0
      a[m] = bef[i].nums;
    }
  }
  
  if (check()) // 合法，输出结果
  {
    cout << "Yes\n";
    for (int i = 1; i <= n * n; i++) cout << a[i] << ' ';
    cout << endl;
  }
  else cout << "No" << endl; // 不合法

  // system("pause");
  return 0;
}
```
马蜂丑，请见谅。

---

## 作者：君のNOIP。 (赞：3)

#### ~~很明显の贪心。~~

------------

### 数据范围：

- $1\le N \le 500$

- $1\le x_i \le N^2 $

~~根据这个数据，一般是 $O(N^2) $ 爆踩过去了。~~

------------

### 基本思路：

- 开个 $pos_i$ 数组表示第 $i$ 位上の数。

- 很明显，若存在符合条件の序列， $ pos_{x_i} = i $

- 于是我们先~~随便~~出组样例模拟下：
```
3
7 5 3
```
- 手推一下答案只能是：

```
Yes
3 3 3 2 2 2 1 1 1
```
- 当输入结束，我们能得到の是：

```
pos 1 2 3 4 5 6 7 8 9
    . . 3 . 2 . 1 . .

```
- 先考虑填每个数左边の数，我们发现只要按照 $x_i$ 从小到大の顺序填，使指针从 $l=1$，向右移，一定最优，变为：

```
pos 1 2 3 4 5 6 7 8 9
    3 3 3 2 2 . 1 . .
```
- 同理，考虑填每个数右边の数，按照 $x_i$ 从大到小の顺序从右边往左填，使指针从 $r=N \times N $，向左移，一定最优，变为：

```
pos 1 2 3 4 5 6 7 8 9
    3 3 3 2 2 2 1 1 1
```
- 然后输出即可。

- 在填数过程中，若指针越过当前在填の数の位置，直接输出 No 



------------
### ~~十分简洁明了~~の代码如下：


------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define G() Cr=getchar()
int Xr;char Cr;
inline int  rd(){
	Xr=0;G();
	while(Cr<'0'||Cr>'9')G();
	while(Cr>='0'&&Cr<='9')Xr=(Xr<<1)+(Xr<<3)+Cr-'0',G();
	return Xr;
}

int n;
int pos[250005];
struct node{
	int num,p;
}e[5005];

bool comp(node x,node y){
	return x.p<y.p;
}
int main(){
	n=rd();
	for(int i=1;i<=n;i++)
		e[i].num=i,e[i].p=rd(),pos[e[i].p]=i;
		
	sort(e+1,e+1+n,comp);	
		
	int l=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<e[i].num;j++){
			while(pos[l])l++;
			if(l>=e[i].p){
				puts("No");
				return 0;
			}
			pos[l++]=e[i].num;
		}	
	}
	
	int r=n*n;
	for(int i=n;i>=1;i--){
		for(int j=n;j>e[i].num;j--){
			while(pos[r])r--;
			if(r<=e[i].p){
				puts("No");
				return 0;
			}
			pos[r--]=e[i].num;
		}
	}
	
	puts("Yes");
	for(int i=1;i<=n*n;i++)printf("%d ",pos[i]);
	puts("");
}
```


------------
### 完结撒花~~~

---

## 作者：听取MLE声一片 (赞：3)

细节构造题。

我们先写一个函数，是从目前的位置往后填一个数，注意之前填过的。

```
void put(int x){
	cnt++;
	while(b[cnt]!=0)
		cnt++;
	b[cnt]=x;
}
```

然后一定要先把要求的数和位置先填上。

我们称一个数放在给定位置之前的叫前部分，给定位置之后的叫后部分。

之后我们考虑，对于每个数，我们要把前部分的数从目前位置往后填，然后判断是否合法。填完前面再到后面填就行了。

我们发现一个问题，给出的数不是递增的，所以直接按照顺序填是不行的。我们考虑把出现位置靠前的数排在前面，这样能最大程度上保证位置不会浪费。

注意前部分和后部分的数都是要按照上面排序后从小到大，不要搞反，否则会在判断无解的地方挂掉。

Code:

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=510;
const int M=3e5+10;
int n,a[N],b[M],c[N],cnt;
void put(int x){
	cnt++;
	while(b[cnt]!=0)
		cnt++;
	b[cnt]=x;
}
int cmp(int x,int y){
	return a[x]<a[y];
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[a[i]]=i;
		c[i]=i;
	}
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++){
		int k=c[i];
		for(int j=1;j<k;j++)
			put(k);
		if(cnt>a[k]){
			puts("No");
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		int k=c[i];
		for(int j=n-k;j>=1;j--){
			put(k);
			if(cnt<a[k]){
				puts("No");
				return 0;
			}	
		}
	}
	puts("Yes");
	for(int i=1;i<=n*n;i++)
		printf("%d ",b[i]);
	return 0;
}

```

---

## 作者：Krimson (赞：2)

看了一下题解,发现我还是太naive,没有想到这么巧妙的贪心,而是想到了一个比较奇怪的做法  

对于每一个数$i$,不难发现在$a_i$前面必须出现过$i-1$次的$i$,等价于有$a_i-(i-1)$次我是可以放其它的数字的(称其为自由步数)，而且非常显然的一点是假设当前在第$pos$位上,那肯定是选择当前自由步数最少的那一个数字填在第$pos$位上最优。  
更近一步,当在$pos$位上时,设$lft_i$为还要出现$i$的次数,那么有
$$
free_i=(a_i-pos+1)-lft_i
$$  
而当前要比较的是$free_i$的大小  
可以发现$free_i$之间的大小只与$a_i-lft_i$有关,于是可以转而用一个小顶堆来维护这个东西。

假设前面的操作都合法,$pos=a_i$,那么说明到这个位置之后可以填$n-i$个$i$来占位置，当堆空了之后就可以使用这些元素了。如果堆空了且还没有足够的元素来填埋剩下的空位，则说明无解  
这个地方的实现比较简单，本人用了一个栈来维护  

剩下来的就是一些细节上的问题了，具体实现还是看代码比较容易理解  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar(' ');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
int n;
const int MAXN=5e5;
int a[MAXN],b[MAXN];
bool vis[MAXN];
struct node
{
    int id,dis;
    bool operator<(const node &x)const {return dis<x.dis;}
    bool operator>(const node &x)const {return dis>x.dis;}
};
priority_queue<node,vector<node>,greater<node> >q;
int sta[MAXN],top,lft[MAXN];
int main(){
    n=read();
    for(ri i=1;i<=n;++i) a[i]=read(),b[a[i]]=i;
    for(ri i=2;i<=n;++i) lft[i]=i-1,q.push((node){i,a[i]-lft[i]});
    // for(ri i=1;i<=n-1;++i) sta[++top]=1;
    for(ri i=1;i<=n*n;++i){
        if(b[i]){
            if(lft[b[i]]){
                puts("No");
                return 0;
            }
            for(ri j=1;j<=n-b[i];++j) sta[++top]=b[i];
            continue;
        }
        if(q.empty()){
            if(!top){
                puts("No");
                return 0;
            }
            b[i]=sta[top--];
        }
        else{
            node now=q.top();q.pop();
            if(now.dis<=0){
                puts("No");
                return 0;
            }
            if(--lft[now.id]){
                now.dis++;
                q.push(now);
            }
            b[i]=now.id;
        }
    }
    puts("Yes");
    for(ri i=1;i<=n*n;++i) print(b[i]);
    return 0;
}
```


---

## 作者：Ebola (赞：1)

# 【AGC008D】Kth - K

做这题呢，胆子要大

一件很显然的事情就是：$X_i$这个位置要放$i$，$X_i$左边要放$i-1$个$i$，$X_i$右边要放$n-i$个$i$。（废话）

我们先来考虑对于每个$i$，在$X_i$左边放$i-1$个$i$。若对于某个$i$，$X_i$左边还没放满$i-1$个$i$，那我们就称此时i处于“需求态”。如果我们按从左到右的顺序考虑$a$的所有未钦定的位置，那考虑到一个位置时，可能会有很多个$i$处于“需求态”，但我们只能减缓一个i的需求。那我们肯定要解决需求更迫切的那个$i$。显然需求最迫切的$i$就是$X_i$最小的$i$。于是我们可以将所有待填入数字按$X_i$排序，然后按排好的顺序来填数

一样的思路，我们再反向操作一遍。此时的“需求态”定义为$X_i$的右边还没放慢$n-i$个$i$

然后我们进行一遍检验，若对于所有的$i$，第$i$个$i$都出现在位置$X_i$，说明满足条件

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0;char c=Get();
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x;
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
}

using namespace IO;
const int N=510;
int a[N*N],X[N],n;
int c[N],cnt[N];
int pos[N][N],num[N];

bool cmp(const int &x,const int &y){return X[x]<X[y];}

bool check()
{
    for(int i=1;i<=n*n;i++)
        pos[a[i]][++num[a[i]]]=i;
    for(int i=1;i<=n;i++)
        if(pos[i][i]!=X[i]) return 0;
    return 1;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) X[i]=read();
    for(int i=1;i<=n;i++) c[i]=i,a[X[i]]=i;
    sort(c+1,c+1+n,cmp);
    for(int i=1;i<=n;i++) cnt[i]=i-1;
    for(int i=1;i<=n*n;i++)
    {
        if(a[i]) continue;
        for(int j=1;j<=n;j++)
            if(cnt[c[j]]){a[i]=c[j];cnt[c[j]]--;break;}
    }
    for(int i=1;i<=n;i++) cnt[i]=n-i;
    for(int i=n*n;i>=1;i--)
    {
        if(a[i]) continue;
        for(int j=n;j>=1;j--)
            if(cnt[c[j]]){a[i]=c[j];cnt[c[j]]--;break;}
    }
    if(check())
    {
        prints("Yes");
        for(int i=1;i<=n*n;i++)
            print(a[i]),putc(' ');
    }
    else prints("No");
    flush();
    return 0;
}
```



---

## 作者：nxd_oxm (赞：0)

注意到 $X_i$ 越小的数显然就要先填。

设在合法条件下有 $X_i<X_j$ 且存在两个位置 $p,q$ 使得 $q \neq i,p<q,a_q=i,a_p=j$，那么显然可以交换 $a_p,a_q$，因为 $p<q<X_i<X_j$。

所以我们就可以将 $X_i$ 排序后按顺序填，如果该位置被占用就填要求的数，并在这里判断是否是第 $i$ 个。要注意可能前面全部满足条件后最后面会有空位，就倒着再用剩下的数填一下即可。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(long long i=j;i<=n;i++)
#define F(i,n,j) for(int i=n;i>=j;i--)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define pb push_back
#define XQZ
using namespace std;
namespace fsd{
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin),p1==p2)?EOF:*p1++)
	const int MAXSIZE=1<<20;
	char buf[MAXSIZE],*p1,*p2;
	inline int read(){
		int ak=0,ioi=1;char c=gc();
		while(!isdigit(c)){if(c=='-')ioi=-1;c=gc();}
		while(isdigit(c))ak=ak*10+(c^48),c=gc();
		return ak*ioi;
	}
	inline string reads(){
		string o="";
		char p=gc();
		while(p>'z'||p<'a'){p=gc();}
		while(p<='z'&&p>='a'){o+=p;p=gc();}
		return o;
	}
	inline char readc(){
		char p=gc();
		while(!((p<='z'&&p>='a')||(p<='Z'&&p>='A'))){p=gc();}
		return p;
	}
}
using namespace fsd;
const int N=510*510;
int n;
pair<int,int> a[N];
int hs[N],b[N];
int c[N];
stack<int> s;
void gs(){
	n=read();
	f(i,1,n)a[i]={read(),i},c[i]=i;
	sort(a+1,a+1+n);
	f(i,1,n){
		if(hs[a[i].first]){printf("No\n");return;}
		hs[a[i].first]=a[i].second;
	}
	int j=1;
	f(i,1,n*n){
//		cout<<j<<" "<<i<<" "<<a[j].second<<' '<<c[a[j].second]<<endl;
//		f(j,1,n*n)cout<<b[j]<<" ";cout<<endl;
		if(hs[i]&&c[hs[i]]>1){
			printf("No\n");return;
		}
		while(j<=n&&c[a[j].second]==1){j++;}
		if(hs[i]){
			b[i]=hs[i];
			f(j,1,n-hs[i])s.push(hs[i]);
			continue;
		}else if(j>n){
			if(s.empty()){printf("No\n");return;}
			b[i]=s.top();
			s.pop();
		}else{
			b[i]=a[j].second;
			c[a[j].second]--;
		}
	}
	cout<<"Yes\n";
	f(i,1,n*n){
		cout<<b[i]<<" ";
	}
	cout<<endl;
}
signed main(){
#ifndef XQZ
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
#ifdef NXD
	int t=0;cin>>t;while(t--)
#endif
		gs();
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

感觉难度虚高了，应该绿差不多。

先把对应 $x_i$ 的数填了，之后拆成两部分做。

第一部分是把每个 $i$ 前面的 $i-1$ 个 $i$ 位置确定。发现这一部分填法很多。

第二部分是把数列剩下的空位用剩下的数填上。在这一部分里我们在位置 $i$ 里填数 $a$ 的前提是 $i>x_a$。显然这一部分比较好做，我们可以贪心地把 $x_a$ 更小的数填到更前面，如果此时仍然不满足要求即可判定无解。

现在我们的第一部分要为第二部分服务。在第一部分的填法中选择一种尽量满足第二部分的要求。

思考第二部分需要什么，对于越小的空位 $i$，它不满足要求的可能性越大，所以我们应尽量地让空位往后靠。那么我们填数的时候可以从第一位开始往后面填。这时为了满足第一部分的条件，可以让 $x_a$ 小即可以填的位置少的数先填。

做完了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef double db;
//typedef long long ll;
typedef pair<int,int> pii;
const int N=500,mod=20101009;
const db eps=1e-9;

int n,ps[N+5],p[N+5],a[N*N+5],g[N+5],pg=1;

Il bool cmp(int x,int y){return ps[x]<ps[y];} 

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(Ri i=1;i<=n;i++)cin>>ps[i],p[i]=i,a[ps[i]]=i;
	sort(p+1,p+n+1,cmp);
	for(Ri i=1,pt=1;i<=n;i++){
		int c=1;
		for(;(c^p[i])&&pt<=ps[p[i]];pt++){
			if(a[pt])continue;
			a[pt]=p[i];
			if((++c)==p[i])break;
		}
		if(c^p[i]){cout<<"No";return 0;}
	}
	for(Ri i=1;i<=ps[p[n]];i++)g[a[i]]++;
	for(Ri i=1;i<=n;i++)g[i]=n-g[i];
	for(Ri i=1;i<=n*n;i++){
		if(a[i])continue;
		while(pg&&!g[p[pg]])pg++;
		if(!pg||i<=ps[p[pg]]){cout<<"No";return 0;}
		a[i]=p[pg];g[p[pg]]--;
	}
	cout<<"Yes\n";
	for(Ri i=1;i<=n*n;i++)cout<<a[i]<<' ';
	return 0;
}
```

~~只要我不说就没有人知道我交了几发。~~

---

## 作者：Jsxts_ (赞：0)

这道题在 AGC 里还算简单的，不过我一点小错就调了一个下午。。。

一开始考虑直接在确定位置的左右填数，很容易发现 hack 数据：
```
3
1 4 9
```

于是我们再考虑一个贪心的构造方法：把当前 $X_i$ 最小的数的前 $i-1$ 个往最左边放，第二小的同理，而后 $n-i$ 个数则按照 $X_i$ 从大到小的顺序往最右边放。容易发现最左边的最靠左是优于其他数靠左的，靠右的同理，所以此方法可行。

具体就是排序之后从小往大、从大往小分别扫一遍，分别填出左边、右边的数，不符合题意（即填数的时候超过了 $X_i$）输出 No 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;

inline int read() {
	int s = 0;char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s;
}
int b[250010],cnt[510];
pair<int,int> a[510];
int main() {
	n = read();
	for (int i = 1;i <= n;i ++ ) a[i].first = read(),a[i].second = i;
	sort(a+1,a+n+1);
	int t = 1;
	for (int i = 1;i <= n;i ++ ) {
		b[a[i].first] = a[i].second;
		int tt = t;
		for (int j = 1;j <= a[i].second-1;j ++ ) {
			while (b[tt]) tt ++;
			if (tt > a[i].first) puts("No"), exit(0);
			b[tt] = a[i].second;
		}
		t = tt;
	}
	t = n*n;
	for (int i = n;i;i -- ) {
		b[a[i].first] = a[i].second;
		int tt = t;
		for (int j = 1;j <= n-a[i].second;j ++ ) {
			while (b[tt]) tt --;
			if (tt < a[i].first) puts("No"), exit(0);
			b[tt] = a[i].second;
		}
		t = tt;
	}
	puts("Yes");
	for (int i = 1;i <= n*n;i ++ ) printf("%d ",b[i]);
	return 0;
}
```

代码虽短，还是有一定思维难度的。

---

## 作者：Freopen (赞：0)

按$x_i$排序，从左到右贪心每次放还没放满$i-1$个中最小的$x_i$的$i$，如果刚好到$x_i$的时候不能把第$i$个放上去就非法，如果上两类中没有可以放的就放$x_i$以及被填了的数字，如果还是没有可以放的就非法，没有必要扫两遍。

$\rm AC \ Code$
```cpp
#include<bits/stdc++.h>
#define maxn 505
using namespace std;

int n,x[maxn],c[maxn],a[maxn*maxn];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	bool ER = 0;
	for(int i=1;i<=n*n;i++){
		for(int j=1;j<=n;j++) if(x[j] == i){
			c[j] ++;
			if(c[j] != j){
				ER = 1;
			}
			a[i] = j;
			break;
		}
		if(!a[i]){
			int p=0 , lc = n*n+2;
			for(int j=1;j<=n;j++) if(c[j] < j-1){
				if(x[j] < lc){
					lc = x[j];
					p = j;
				}
			}
			if(p){
				a[i] = p ,
				c[p] ++;
			}
		}
		if(!a[i]){
			for(int j=1;j<=n;j++) if(c[j] < n && x[j] < i){
				a[i] = j;
				c[j]++;
				break;
			}
		}
		if(!a[i]){
			ER = 1;
		}
	}
	if(ER){
		puts("No");
	}
	else{
		puts("Yes");
		for(int i=1;i<=n*n;i++) printf("%d%c",a[i]," \n"[i==n*n]);
	}
}
```


---

