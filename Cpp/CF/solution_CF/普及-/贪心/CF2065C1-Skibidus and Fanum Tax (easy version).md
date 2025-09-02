# Skibidus and Fanum Tax (easy version)

## 题目描述

这是这道题的简单版本，在该版本中，$m = 1$。

Skibidus 有两个数组 $a$ 和 $b$，分别包含 $n$ 和 $m$ 个元素。对于 $1$ 到 $n$ 的每个整数 $i$，他**最多**可以执行一次以下操作：

- 选择一个整数 $j$（$1 \leq j \leq m$），将 $a_i$ 赋值为 $b_j - a_i$。注意，经过此操作后，$a_i$ 可能变为非正数。

Skibidus 需要你的帮助，判断是否可以通过若干次上述操作，使得数组 $a$ 为非递减序列。

$^{\text{∗}}$ 若 $a_1 \leq a_2 \leq \dots \leq a_n$，则数组 $a$ 为非递减序列。

## 说明/提示

- 在第一个测试用例中，$[5]$ 已经是非递减序列。
- 在第二个测试用例中，可以证明无法使其非递减。
- 在第三个测试用例中，我们可以将 $a_3$ 更新为 $b_1 - a_3 = 6 - 2 = 4$，此时数组变为 $[1, 4, 4, 5]$，是非递减序列。
- 在最后一个测试用例中，我们可以对每个位置执行操作，数组变为 $[-1, 0, 1]$，是非递减序列。

## 样例 #1

### 输入

```
5
1 1
5
9
3 1
1 4 3
3
4 1
1 4 2 5
6
4 1
5 4 10 5
4
3 1
9 8 7
8```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：canwen (赞：3)

简单题，建议橙。

提供一种逆序遍历的做法。

我们从后往前看，假如 $a_i\le a_{i+1}(1\le i\le n)$，如果 $a_i \gets b_1-a_i$ 能使 $a_i$ 更大且 $i=n$（最后一个元素）或者 $b_1-a_i\le a_{i+1}$（仍能满足单调非递减的条件），那么贪心将 $a_i \gets b_1-a_i$；假如 $a_i > a_{i+1}$，如果 $a_i \gets b_1-a_i$ 能使得 $a_i \le a_{i+1}$，那么更改，否则因为不满足单调非递减的条件，一定无解。

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define pb push_back
#define mk make_pair
#define fst first
#define snd second
#define pc putchar('\n')
#define nowtime (double)clock()/CLOCKS_PER_SEC
int in(){int k=0,kk=1;char a=getchar();while(!isdigit(a)){if(a=='-') kk=-1;a=getchar();}while(isdigit(a))k=(k<<3)+(k<<1)+a-'0',a=getchar();return k*kk;}
void out(int a){if(a<0) putchar('-'),a=-a;if(a>9) out(a/10);putchar('0'+a%10);}
const int N = 2e5 + 5, M = 2;
int a[N],b[M];
signed main(){
	int t;
	t=in();
	while(t--){
		int n = in(), m = in(), flag = 1;
		_rep(i,1,n) a[i] = in();
		_rep(i,1,m) b[i] = in();
		_rrep(i,n,1){
			if(i!=n&&a[i]>a[i+1]){
				if(b[1]-a[i]<=a[i+1] )a[i] = b[1]-a[i];
				else {flag = 0; break;} 
			}else if(b[1]-a[i]>a[i]&&(i==n||b[1]-a[i]<=a[i+1])) a[i] = b[1]-a[i];
		}
		if(flag) printf("Yes\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：xingshuyan000 (赞：3)

# 题目大意

给你一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$，对于每一个整数 $i$（其中 $i \in [1,n]$），你可以执行下面的操作最多一次：

- 选择一个整数 $j$（其中 $j \in [1,m]$），让 $a_i \leftarrow b_j-a_i$。注意，执行操作后，$a_i$ 可能会变成非正数。

你需要判断，执行完操作后，数组 $a$ 能否变为单调不减的数组，如果可以，输出 `YES`，否则输出 `NO`。数组 $a$ 是单调不减的数组，当且仅当数组 $a$ 满足 $a_1 \le a_2 \le a_3 \le \cdots \le a_n$。

在这道题中，数据范围满足：$1 \le n \le 2 \times 10^5,\textbf{m=1}$，$1 \le a_i, b_i \le 10^9$。

# 题目分析

注意到，在这一题中，$m=1$ 是一个非常重要的信息，这就说明，$b$ 数组里面只有一个元素，所以 $j$ 只能等于 $1$。接下来，就是判断经过一系列操作后，$a$ 数组能否变为单调不减的。因为前一个元素要不大于后一个元素，所以，我们就要保证前一个元素在小于等于后一个元素的同时，大小尽可能小。这个时候，我们就先判断 $a_i$ 和 $\min(a_{i+1},b_1-a_{i+1})$ 的关系，如果 $a_i \le \min(a_{i+1},b_1-a_{i+1})$，那么就让 $a_{i+1} \leftarrow \min(a_{i+1},b_1-a_{i+1})$；否则，就判断 $\max(a_{i+1},b_1-a_{i+1})$ 和 $a_i$ 的关系，如果 $a_i \le \max(a_{i+1},b_1-a_{i+1})$，那么就让 $a_{i+1} \leftarrow \max(a_{i+1},b_1-a_{i+1})$；如果还是不满足，那直接输出 `NO` 即可。数组 $a$ 如果遍历到最后，还都没有输出 `NO`，那就说明这个 $a$ 数组可以变成单调不减的，输出 `YES`。

这样下来，题目就分析完了，难度不算很大，反正肯定比那个 Hard 版本简单很多，毕竟 $b$ 数组只有一个元素。

# MY CODE

我的代码跟我前面讲的思路稍微差了一点点，就是写几个判断的顺序不同，其他都没啥区别。我的代码应该比较好理解，所以就不加注释了。

```cpp
//C1
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 50;
long long a[N], b[N];
void solve()
{
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	for(int i = 1; i <= m; i ++) cin >> b[i];
	a[1] = min(a[1], b[1] - a[1]);
	for(int i = 1; i <= n - 1; i ++)
	{
		if(a[i] > max(b[1] - a[i + 1], a[i + 1]))
		{
			cout << "NO" << endl;
			return;
		}
		else if(a[i] <= min(a[i + 1], b[1] - a[i + 1]))
			a[i + 1] = min(a[i + 1], b[1] - a[i + 1]);
		else a[i + 1] = max(a[i + 1], b[1] - a[i + 1]);
	}
	cout << "YES" << endl;
	return;
}
int main()
{
	int t;
	cin >> t;
	while(t --) solve();
	return 0;
}
```
完结撒花~

---

## 作者：Pyrf_uqcat (赞：1)

考虑一个贪心策略。为了成为非递减序列，需要让前面的数尽量小。

所以对于每个数，我们要在**保证非递减的前提**下进行对数的操作，让当前数尽量小。


```cpp
#include <bits/stdc++.h>
#define int long long

#define N 200005

using namespace std;

int n,m,a[N],b[N];

signed main()
{
	int t;cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i];
		bool flag=1;
		a[1]=min(a[1],b[1]-a[1]);
		for(int i=2;i<=n;i++)
		{
			int c=b[1]-a[i];
			if(c>=a[i-1]&&c<a[i]) a[i]=c;
			if(a[i]<a[i-1]&&c>=a[i-1]) a[i]=c;
			if(a[i-1]>a[i]) flag=0;
		}
		cout<<(flag?"YES":"NO")<<endl;
	}
    return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

赛时 C 写挂调了一个世纪没调出来，导致时间严重不够。

然后赛后 13min 调出来了（

---

题面要求我们通过若干次操作使得序列单调递增，我们只需要在合法的前提下使靠前的元素尽可能小就行了。

如果最后无法合法就是无解。

注意到对于相同的 $a_i$，$b_j$ 越大结果越大。

那么我们就可以将 $b$ 排序后二分修改最优解了。

时间复杂度 $O(n \log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005];
void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    for(int i=1;i<=m;i++)
    cin>>b[i];
    sort(b+1,b+1+m);
    a[1]=min(a[1],b[1]-a[1]);
    //cout<<a[1]<<' ';
    for(int i=2;i<=n;i++)//,cout<<a[i-1]<<' ')
    {
        int l=1,r=m+1;
        while(l<r){
            int mid=(l+r)/2;
            if(b[mid]-a[i]<a[i-1])l=mid+1;
            else r=mid;
        }
        //cout<<r<<'!';
        if(r!=m+1&&(b[r]-a[i]<=a[i]||a[i]<a[i-1]))
        a[i]=b[r]-a[i];
    }
    for(int i=1;i<n;i++)
    if(a[i]>a[i+1]){
        puts("NO");
        return;
    }
//    for(int i=1;i<=n;i++)
//    cout<<a[i]<<' '; 
    puts("YES");
    return;
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

糖题写挂，人比题糖。

---

## 作者：FXLIR (赞：0)

### 思路

可以发现，若想形成非递减序列，则每个元素应尽量小。

因为每个 $i$ 只能被选择一次，所以最后 $a_i$ 的值要么是 $a_i$，要么是 $b-a_i$。

那么，在保证 $a_i \ge a_{i-1}$ 的情况下，对每一个元素依次进行操作，将其修改为尽可能小的值即可。具体地，若 $b-a_i \ge a_{i-1}$，则将 $a_i$ 赋值为 $b-a_i$，否则不进行变化。

然后，考虑如何判断 $a$ 不可能变成非递减序列的情况。不难发现，若存在一个 $a_i$，使得 $\max(a_i,b-a_i) < a_{i-1}$，则 $a$ 不可能变成非递减序列——因为按照前面的策略，此时 $a_{i-1}$ 应是条件允许情况下的最小值。

按照这个思路实现即可。
### AC code
```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5,INF=1e9;
int t,n,m,a[N],b;
bool solve(){
	a[1]=min(a[1],b-a[1]);
	for(int i=2;i<=n;i++){
		if(a[i-1]>max(a[i],b-a[i])){
			return 0;
		}
		a[i]=(b-a[i]>=a[i-1]?b-a[i]:a[i]);
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		cin>>b;
		cout<<(solve()?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Wind_love (赞：0)

## 思路
对于该题，我们很容易想到一个贪心思路。  
即对于每一个 $a_i$，在保证其大于等于 $a_{i-1}$ 的同时尽量最小化其值。   
则对于每一个 $a_i$，我们有两种可能的情况。第一种，保持其值不变；第二种，通过题中所说操作改变其值。    
我们重点看到第二种情况，我们可以通过二分查找的方式，让 $b_j-a_i$ 在大于等于 $a_{i-1}$ 的情况下最小。   
最后，对于两种情况，若都能满足大于等于 $a_{i-1}$，则取最小值；否则取能满足的值。   
得到结果后遍历数组判定是否非严格递增即可。  
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,m,a[200005],b[200005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++)cin>>b[i];
		sort(b+1,b+m+1);
		int f=1;
		a[0]=-1e18;
		for(int i=1;i<=n;i++){
			int temp=lower_bound(b+1,b+m+1,a[i]+a[i-1])-b;
			if(temp<=m){
				if(a[i]>=a[i-1])a[i]=min(a[i],b[temp]-a[i]);
				else a[i]=b[temp]-a[i];
			}
		}
		for(int i=1;i<n;i++){
			if(a[i]>a[i+1]||a[i-1]>a[i]){
				f=0;
				break;
			}
		}
		if(f)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

---

## 作者：EternalLabyrinth (赞：0)

加强题目，考虑 C2 做法。

### 题意：
$T$ 组数据，给定序列 $a$，给定序列 $b$。对于 $a$ 序列的每个 $a_i$，都可以至多选择一个 $j$，让 $a_i$ 变为 $b_j-a_i$。

请问经过操作后是否能让序列单调不降。

### 解法：

先把 $b$ 序列从小到大排序。

首先对于第一个位置的处理：肯定是让 $a_i$ 变为 $\min\{a_i,b_1-a_i\}$。其次我们注意到往前的位置应该在满足条件的情况下尽可能小。这一点可以类比最长不下降子序列。

于是对于每个位置 $i(i\geq 2)$。应二分找到最小的 $j$ 使得 $b_j-a_i\geq a_{i-1}$，当然如果 $a_i$ 本身大于等于 $a_{i-1}$ 的话，它是最优的也是有可能的，需要特判。

无解情况就是找不到这个 $j$ 且 $a_i$ 本身又小于 $a_{i-1}$ 了。注意如果找到了别忘了每次把 $a_i$ 赋为 $\min\{a_i,b_j-a_i\}$。然后我们就做完了。

---

## 作者：ztd___ (赞：0)

简单题。~~但是我秒了 A，C1，D，E 结果 B 死活过不去并且不会 C2 是怎么回事。~~

观察到每一个 $a_i$ 最多也只能变一次，所以在最终的序列里，$a_i$ 必然是不变或 $b_1 - a_i$。

然后贪心地考虑。我们为了让最终的序列非递减，必然会让前面的数字尽可能小，这样后面的数字才会有更大的使用空间。

那么就显然了。我们用一个数组 $c$ 来记录答案序列，然后对于每一个第 $i$ 个位置，我们先尝试将 $c_i$ 设为 $\min(a_i, b_1 - a_i)$，如果他比前面一个小，我们就需要把他换成 $\max(a_i, b_1 - a_i)$。如果还是比前面小，就说明无法将原序列排序。如果到最后也没有出现这种情况，就说明可以将原序列排序。

为了方便，我们可以将 $c_0$ 设为一个极小值，这样我们就不用特判 $i = 1$ 了。

AC Code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 55;
int n, m, a[N], b[N], c[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1;i <= n;i++) {
			cin >> a[i];
		}
		for (int i = 1;i <= m;i++) {
			cin >> b[i];
		}
		c[0] = -1e18;
		int flg = 0;
		for (int i = 1;i <= n;i++) {
			c[i] = min(a[i], b[1] - a[i]);
			if (c[i] < c[i - 1]) c[i] = max(a[i], b[1] - a[i]);
			if (c[i] < c[i - 1]) { flg = 1; break; }
		}
		if (flg) cout << "NO\n";
		else cout << "YES\n";
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# CF2065C1 题解

## 思路

简单版，$b$ 数组只有一个值，那么对于 $a$ 的每个位置，取值只有两种，要么 $a_i$，要么 $b_1 - a_i$，要让构造的数组单调不降，那么尽可能让前面的小。

从 $1$ 到 $n$ 扫一遍，如果 $\min(a_i,b_1-a_i) \ge a_{i-1}$，则 $a_i \leftarrow \min(a_i,b_1-a_i)$，否则，如果 $\max(a_i,b_1-a_i)<a_{i-1}$，则无解，否则，$a_i \leftarrow \max(a_i,b_1-a_i)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=200005;
const int inf=2e9;

int T,n,m;
int a[N],b[N];

int main() {
    read(T);
    while (T--) {
        read(n),read(m);
        _rep(i,1,n) read(a[i]);
        _rep(i,1,m) read(b[i]);
        bool ok=true;
        int las=-inf;
        _rep(i,1,n) {
            int mn=min(a[i],b[1]-a[i]);
            int mx=max(a[i],b[1]-a[i]);
            if (mn>=las) las=mn;
            else if (mx<las) {
                ok=false;
                break;
            } else las=mx;
        }
        if (!ok) puts("NO");
        else puts("YES");
    }
    return 0;
}
```

---

## 作者：StormWhip (赞：0)

考虑贪心：对于数组中得每一个元素 $a_i$，要在保证其不小于 $a_{i-1}$ 的前提下最小化其的值。  
因此比较操作前和操作后这个元素的值：
- 若操作前后的值都满足要求，则选取较小的一个。
- 若操作前后的值有且仅有一个满足要求，则选取满足要求的那一个。
- 若都不满足要求，则说明无法使其按非递减顺序排序。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,Inf=-1e12;
int T,n,m,a[N],b[N];
signed main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		bool f=1;
		cin>>n>>m;
		a[0]=Inf;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i];
		for(int i=1;i<=n;i++)
		{
			int t=b[1]-a[i];
			if(t>=a[i-1]&&a[i]>=a[i-1]) a[i]=min(a[i],t);
			if(t<a[i-1]&&a[i]>=a[i-1]) continue;
			if(t>=a[i-1]&&a[i]<a[i-1]) a[i]=t;
			if(t<a[i-1]&&a[i]<a[i-1]) {cout<<"NO\n";f=0;break;}
		}
		if(f) cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### Analysis
记 $prev$ 为上一个值。

对于每一个 $i$，$1 \leq i \leq n$：
- 如果 $\min(a_i, b - a_i) \geq prev$，则 $prev \gets \min(a_i, b - a_i)$。
- 否则，如果 $\max(a_i, b - a_i) \geq prev$，则 $prev \gets \max(a_i, b - a_i)$。
- 否则，无解，输出 `NO`。
### Code
```cpp
#include <bits/stdc++.h>
const int N = 2e5 + 5;
int a[N], b;
int main() {
    int T;
    std::cin >> T;
    while (T --) {
        int n, m;
        std::cin >> n >> m;
        for (int i = 1; i <= n; i ++) std::cin >> a[i];
        std::cin >> b;
        bool f = 0; int prev = INT_MIN;
        for (int i = 1; i <= n; i ++) {
            if(std::min(a[i], b - a[i]) >= prev){
                prev = std::min(a[i], b - a[i]);
            }else if(std::max(a[i], b - a[i]) >= prev){
                prev = std::max(a[i], b - a[i]); 
            }else{ 
                std::cout << "NO" << std::endl;
                f = 1; break;
            }
        }
        if(!f) std::cout << "YES" << std::endl;
    }
}
```

---

