# Box

## 题目描述

排列 $ p $ 是一个 $ p=[p_1, p_2, \dots, p_n] $ 的广泛数列,包括 $ n $ 个各不相同（唯一）的从1到n的正整数。比如，这些数列是排列：$ [3, 4, 1, 2] $ , $ [1] $ , $ [1, 2] $。这些不是排列：$ [0] $ , $ [1, 2, 1] $ , $ [2, 3] $ , $ [0, 1, 2] $ 。

重要的钥匙在一个需要你打开的锁上的盒子里。你需要输入密码来打开它。密码是一个长度为 $n$ 的序列。

你不知道这个排列，你只知道这个排列前缀的最大值。定义如下：

- $ q_1=p_1 $ ,
- $ q_2=\max(p_1, p_2) $ ,
- $ q_3=\max(p_1, p_2,p_3) $ ,
- ...
- $ q_n=\max(p_1, p_2,\dots,p_n) $ .

你想要把所有可能的排列都构造出来（即任何这样的排列，使得计算出的 $q$ 与给出的数组相同）。

## 说明/提示

样例的第一组数据中， $ [1,3,4,5,2] $ 是唯一一组可能的答案:

- $ q_{1} = p_{1} = 1 $ ;
- $ q_{2} = \max(p_{1}, p_{2}) = 3 $ ;
- $ q_{3} = \max(p_{1}, p_{2}, p_{3}) = 4 $ ;
- $ q_{4} = \max(p_{1}, p_{2}, p_{3}, p_{4}) = 5 $ ;
- $ q_{5} = \max(p_{1}, p_{2}, p_{3}, p_{4}, p_{5}) = 5 $ .

可以证明样例的第二组数据没有答案。

翻译来自 @[carreye](https://www.luogu.com.cn/user/188360)

## 样例 #1

### 输入

```
4
5
1 3 4 5 5
4
1 1 3 4
2
2 2
1
1
```

### 输出

```
1 3 4 5 2 
-1
2 1 
1 
```

# 题解

## 作者：__UrFnr__ (赞：2)

**题目大意**：给定一个数组 $q$，其中 $q_i$ 表示前 $n$ 个元素的最大值，我们需要根据这个数组 $q$ 来构造数组 $p$。

**题目思路**：我们知道 STL 有个好东西叫优先队列，可以自动实现升序或降序排序。利用这个特点，我们可以使用一个大根堆（从大到小排序）。我们遍历 $1\sim n$，发现入队时有数 $<q_i$，则将 $1\sim n$ 入队，如果队列为空，则是无解情况，输出 `-1`，反之，我们可以将堆顶加入答案数组，将堆顶弹出，最后输出答案数组，即可完成。

根据思路模拟即可。

---

## 作者：naroto2022 (赞：2)

# CF1227B题解
### 题意
给一个数组 $q$，其中：
- $q_1=p_1$。
- $q_2=\max(p_1,p_2)$。
- $q_3=\max(p_1,p_2,p_3)$。
- $\cdots$
- $q_n=\max(p_1,p_2,p_3,\cdots p_n)$

求符合要求的 $p$ 数组。
### 思路
有以下两点：

1. 无解的情况：$q[i]<i$，为啥呢？答：那是因为 $q$ 数组的第 $i$ 个是为 $p$ 的前 $i$ 个数中最大的。又因为 $p$ 为 $1\sim n$ 中不重复的数字组成的数组。所以要是 $q[i]<i$，就是无解。
2. 求解操作呢，我借鉴了 SunArrebol 这位大佬，但是他没有解释，首先先讲解法：
```cpp
bool ok=0;//记录是否有符合题意的p数组 
		for(int i=1; i<=n; i++) p[i]=i;
		for(int i=1; i<=n; i++){
			scanf("%d",&q[i]);
			if(q[i]<i) ok=1;//标记为无解。
			else swap(p[i],p[q[i]]);//交换 
		}
```
那为啥是上面那样呢？首先一开始已经赋值 $p$ 为 $1,2,3,\cdots n$，此时录入 $q$，无解就不说了，我们要理解的是交换这一步，为啥是这样交换呢？分析如下：

我们都知道，$q$ 数组的第 $i$ 个是为 $p$ 的前 $i$ 个数中最大的，那么输入一个 $q[i]$ 分为以下两种情况：

 $\begin{cases} q[i]=p[i]=\max(p[1],p[2],p[3],\cdots p[i])\\p[i]\neq\max(p[1],p[2],p[3],\cdots p[i]),q[i]=q[i-1] \end{cases}$

对于第一种情况，$p[i]$ 是没有被交换过的，所以 $q[i]=p[i]=i$，所以交换了等于没交换。

对于第二种情况，因为 $q[i]=q[i-1]$，所以就说明前面 $p[q[i]]$ 已经交换过原来的小的了，在 $p[q[i]]<p[i]<q[i]$，所以也不影响 $q$ 数组最大值，操作合理。
### 总结
1. 在做操作的时候记得赋初值。
2. 记得特判无解的情况。
3. 别忘了换行！
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath> 
using namespace std;
int p[100005],q[100005],T,n;
int main(){
	scanf("%d",&T);
	while(T--){//有T组数据 
		scanf("%d",&n);
		bool ok=0;//记录是否有符合题意的p数组 
		for(int i=1; i<=n; i++) p[i]=i;//赋初值 
		for(int i=1; i<=n; i++){
			scanf("%d",&q[i]);
			if(q[i]<i) ok=1;//标记为无解。 
			//为啥无解呢？
			//那是因为：q数组的第i个是为p的前i个数中最大的。
			//又因为p为1~n中不重复的数字组成的数组。 
			//所以要是q[i]<i，就是无解。 
			else swap(p[i],p[q[i]]);//交换 
		}
		if(ok==1) printf("-1");//无解 
		else for(int i=1; i<=n; i++) printf("%d ",p[i]);
		printf("\n");//记得换行 
	} 
	return 0;
}
```


---

## 作者：Miracle_1024 (赞：2)

## 题目大意

输入 $q_1$ 到 $q_n$，构造满足要求的序列使得 $q_1=p_1,q_2=\max(p_1,p_2),q_3=\max(p_1,p_2,p_3),\cdots,q_n=\max(p_1,p_2,\cdots,p_{n-1},p_n)$。
## 解题思路
逐个输入 $x$，只需要输入一次就把当前的下标和 $i$ 下标比较并交换一下就可以了，最后如果没有特殊情况输出 `-1` 即可。
## 代码：很好理解
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005]={0},b[1000005]={0},t;
signed main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		memset(a,0,sizeof(a));
		memset(a,0,sizeof(b));
		int s=0;
		for(int i=1;i<=n;i++)a[i]=i;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			if(x<i)s=1;
			else swap(a[i],a[x]);
		}
		if(s==1)cout<<-1<<endl;
		else{for(int i=1;i<=n;i++)cout<<a[i]<<" ";}
		cout<<endl;
	} 
}

```

---

## 作者：ZJPex (赞：0)

### CF1227 [B. Box](https://codeforces.com/problemset/problem/1227/B)

#### 题目大意

给定一个数组 $q$，其中 $q[i]$ 表示排列中前 $n$ 个元素的最大值。你的任务是使用这个数组 $q$ 推导出排列 $p$。

#### 思路

首先，我们需要排除无效的情况，即当 $q[i] < i$ 或 $q[i] > q[i + 1]$ 时。后一种情况应该很容易理解，而前一种情况是因为排列的性质：像 1 这样的数字不可能出现在第一位之后，因此对于任何 $i$，它只能出现在前 $i$ 个位置中。排除无效情况后，我们迭代找出 $q[i] \neq q[i - 1]$ 的实例。在这些点上，$p[i]$ 应该等于当前的 $q[i]$。这点应该不需要太多解释就能清晰理解。我们会标记这些数字，之后再填补未标记的位置。

#### 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
#define int long long
#define PI acos(-1.0)
#define l1 cout << -1 << endl
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define endl "\n"
using namespace std;
using PII = pair<int,int>;
const int MAXN=1e5 + 9;
int t,p[MAXN];
int q[MAXN],used[MAXN];

void additional()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t;
}

void solve()
{
    int n;
    cin >> n;
    memset(p,0,sizeof(p));
    memset(used,0,sizeof(used));
    for(int i = 1;i <= n;i ++)
    {
        cin >> q[i];
    }
    q[n + 1] = MAXN;
    for(int i = 1;i <= n;i ++)
    {
        if(q[i] < i || q[i] > q[i + 1])
        {
            cout << -1 << '\n';
            return;
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        if(q[i] != q[i - 1])
        {
            p[i] = q[i];
            used[q[i]] = 1;
        }
    }
    int j = 1;
    for(int i = 1;i <= n;i ++)
    {
        if(!p[i])
        {
            while(used[j])
            {
                j ++;
            }
            p[i] = j;
            used[j] = 1;
            j ++;
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        cout << p[i] << " \n"[i == n];
    }
}

signed main()
{
    t = 1;
    additional();
    while(t --)
    {
        solve();
    }
}

---

## 作者：enyyyyyyy (赞：0)

 数据结构：
    优先队列。优先队列可以实现 `sort` 的功能。

  思路：
   遍历 $1$ 至 $n$，发现压入的数小于 $a_i$，那么把 $1,2,3\dots {n-1},n$ 压入优先队列，如果队列为空，那么输出 `-1`，将优先队列的顶端压入答案中。
    
 代码：
 
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll a[1000005],b[1000005],n,t;
int main(){
    t=read();
    while(t--){
		priority_queue<ll> q;
    	n=read();
        for(ll i=1;i<=n;i++) a[i]=read();
        ll f=0;
        for(ll i=1;i<=n;i++){
            while(f<a[i]) q.push(++f);
            if(q.empty()){
				printf("-1\n");
				break;
			}
            b[i]=q.top(); 
			q.pop();
        }
        for(ll i=1;i<=n;i++) print(b[i]),printf(" ");
        printf("\n");
	}
	return 0;
}
```


---

## 作者：shipeiqian (赞：0)

# 题意

使用 $1 \sim n$ 之间的每个数，构造一个序列，使得第 $1 \sim i$ 个位置上的最大值与给定序列的第 $i$ 项相符。

# 思路

使用优先队列，优先队列可以使更小的一项在前面，让后面的几项有更大的选择空间。然后遍历每一个位置，只要发现比给定序列的第 $i$ 项小，就将它入队，$visit[i]$ 打上标记，表示已经拿过。若发现没到最后一项，却无法再入队了，就说明没有比这一项更小的，无法使最大值相符了，不可行，直接输出 $-1$，结束；反之加入 $ans$ 数组，最后再输出。

# AC CODE

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int maxn=500005;
int n,a[maxn],ans[maxn];
bool vi[maxn];
void solve(){
	priority_queue<int> q;//优先队列
	cin >>n;
	for(int i=1;i<=n;i++)vi[i]=false;//每个位置设为没去过，也可以用memset
	for(int i=1;i<=n;i++)cin >>a[i];
	for(int i=1;i<=n;i++){
		for(int j=a[i-1]+1;j<=a[i];j++){//只要比当前位置小就入队
			if(!vi[j])q.push(j);
		}
		if(q.empty()){//无法入队说明不可行
			cout <<"-1\n";
			return ;
		}
		ans[i]=q.top();//加入答案数组
		vi[ans[i]]=true;//标记
		q.pop();//弹出队首
	}
	for(int i=1;i<=n;i++)cout <<ans[i] <<" ";//输出答案
	cout <<endl;
}
int main(){
	int t;
	cin >>t;
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# $\text{CF1227B - Box}$ 题解

## 题目大意

给定一个长度为 $n$ 的数组 $a$，构造出 $1\sim n$ 的一个排列 $p$ 使得 $\max_{i=1}^m \{p_i\}=a_m$，无解输出 $-1$。

数据范围保证 $n\le 10^5$。

## 思路分析

自己做的时候一发秒了，看了一圈题解似乎没有一样的做法，来一发自己的奇怪做法

从前往后扫一遍 $a_i$，将当前还没有加入 $p$ 中的数设为 $\mathbf S$。

- 若 $i=1$ 或 $a_i\neq a_{i-1}$，说明 $p_i=a_i$，在 $\mathbf S$ 中取出 $a_i$ 加入 $p$ 中即可
- 若 $a_i=a_{i-1}$，则 $p_i<a_i$，注意到 $a_i$ 单调递增，所以每次取出的 $p_i$ 对后面没有影响，直接选择 $\mathbf S$ 中最小的数作为 $p_i$即可

在以上取数的过程中，若找不到合法的 $p_i$，则报告无解信息。

发现对 $\mathbf S$ 的操作可以用一个 `set` 维护，所以整体的时间复杂度是 $\Theta(n\log n)$ 的。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1;
int a[MAXN];
inline void solve() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	set <int> s;
	vector <int> res; 
	for(int i=1;i<=n;++i) s.insert(i);
	for(int i=1;i<=n;++i) {
		if(a[i]==a[i-1]) {
			int v=*s.begin(); //取出S中最小的数 
			if(v>a[i]) return (void)(puts("-1"));
			//如果已经大于a[i]就无解 
			res.push_back(v);
			s.erase(s.begin()); //删除该数 
		} else {
			auto t=s.lower_bound(a[i]);
			if(t==s.end()||*t!=a[i]) return (void)(puts("-1"));
			//如果找不到a[i]则无解 
			s.erase(t);res.push_back(a[i]);
		}
	}
	for(int v:res) printf("%d ",v);
	return (void)(puts(""));
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一个长度为 $n$ 的排列 $q_{1...n}$，定义 $p_i=\max_{j\le i} q_j$，现在给出 $p_{1...n}(p_i\ge p_{i-1})$，请你构造一个合法的 $q$ 或者报告无解.  
$n\le 10^5$
## $\text{Solution}$
显然，最大值改变的位置必然就是最大值.  
剩下的位置从前往后贪心的先填小的即可.  
如果和最大值条件矛盾则无解.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
int vis[N];
int ans[N],mx[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    int now=0;
    n=read();
    fill(vis,vis+1+n,0);
    fill(ans,ans+1+n,0);
    for(int i=1;i<=n;i++){
      mx[i]=read();
      if(mx[i]>now){
	now=mx[i];ans[i]=mx[i];vis[mx[i]]=1;
	//printf("i=%d mx=%d\n",i,mx[i]);
      }
    }
    int pl=1,flag=0;
    for(int i=1;i<=n;i++){
      if(ans[i]) continue;
      while(vis[pl]) ++pl;
      //printf("i=%d pl=%d\n",i,pl);
      ans[i]=pl;vis[pl]=1;
      if(ans[i]>mx[i]){
	flag=1;printf("-1\n");break;
      }
    }
    if(!flag){
      for(int i=1;i<=n;i++) printf("%d ",ans[i]);
      putchar('\n');
    }    
  }
  return 0;
}
/*

*/

```


---

