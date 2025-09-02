# Maria Breaks the Self-isolation

## 题目描述

由于本场题面违反互联网相关法律，不予展示原题面。

## 样例 #1

### 输入

```
4
5
1 1 2 2 1
6
2 3 4 5 6 7
6
1 5 4 5 1 9
5
1 2 3 5 6```

### 输出

```
6
1
6
4```

# 题解

## 作者：_ouhsnaijgnat_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1358B)

## 思路

这道题只要 $a_{i}$ 能进去，那么 $a_{1\backsim i}$ 都能进去。

我们也很容易发现，只要 $a_{i}\leq i$，那么第 $i$ 个人是可以进去的。

再根据刚才发现的规律，先排序，再枚举 $1\backsim n$，找出一个可以进去的人，输出编号 $+1$ 即可，因为还包括我。

话不多说，直接上代码。

```cpp
#include<iostream>
using namespace std;
int a[100003],ans;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+1+n);
		ans=1;//如果我邀请的朋友一个没来，要输出1，所以初始化为1。 
		for(int i=1;i<=n;i++)//枚举1~n。 
			if(a[i]<=i){
				ans=i+1;//ans更新 
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：juicyyou (赞：2)

# CF1358B Maria Breaks the Self-isolation
## 解法：
首先我们知道，如果有一个人进不去，那所有 $a_i$ 比他大的人都进不去。

其次，我们还知道，如果一个人能进去，那所有 $a_i$ 比他小的人也都能进去。( 让那个人和他一起进去 )

那么，我们只需要找到 $a_i$ 最大的能进去的人，然后让所有 $a_i$ 比他小的人和他一起进去就行了。

那怎么找呢？

我们可以从大到小的考虑每一个人，我们知道知道，如果让 $a_i$ 进去了，那么他至少会看见 $i$ 个人，所以，我们只需要找到最大的 $i$ 使得 $a_i \le i$ 然后输出 $i + 1$ 就行了。

下面是Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll n, ans;
ll a[maxn];
int main(){
	ll t;
	qread(t);
	while(t--){
		qread(n);
		for(int i = 1;i <= n;i++){
			qread(a[i]);
		}
		sort(a + 1, a + n + 1);
		ans = 1;
		int now = 1;
		for(int i = 1;i <= n;i++){
			if(a[i] <= i){
				ans = i + 1;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```
上述算法的单次复杂度为 $O(n \log n)$，算上多组数据后，复杂度为 $O(\sum n \log n)$，可以通过此题。

---

## 作者：Together_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1358B)

## 题目大意:

你准备邀请 $n$ 个人去参加聚会，每个人有个 $a_i$，若你要求此人 $t_i$ 时刻来，则在 $t_i$ 时刻前来的人数要 $\geq a_i$。（**包括你自己**）

## 思路：

若第 $i$ 个人去了，那么前 $i$ 个人都是可以去的。

**算法**：枚举，遍历一遍 $1\sim n$，依此判断，$i$ 能否去。

**答案**：若 $i$ 能去，则结果为 $i+1$（选最大的 $i$），$+1$ 是因为你也是一个人。

**注意**：要排序！



---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1358B)

### [思路]

这道题稍微思考一下就会发现，当第 $i$ 个人进入时，前面的人都可以进入，
所以要进行排序，而只有当 $a_i \leq i$ 时，第 $i$ 个人才能进入，判断然后逐个统计，所以输出的就是 $ans + 1$，因为自己也是人。我们只用跟着题目进行模拟即可。

### [代码]

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main()
{
	int g;
	cin>>g;
	while(g--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int ans=1;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
		if(a[i]<=i)ans=i+1;
		cout<<ans<<endl;
	}
	
	return 0;
}

```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1358B)

### **[题意解析]**
题目大意是，对于一个 $a_i$，我们发现：
+ 如果 $a_i$ 能进去，那比 $a_i$ 小的所有数都能进去。
+ 如果 $a_i$ 不能进去，那比 $a_i$ 大的所有数都不能进去。

### **[思路分析]**
知道了题目的意思，我们就照着题目说的做就好了。我们可以从小到大在 $a_i$ 找一次，找到 $a_i$ 中最大的那个能进去的人就可以了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100010],ans; 
int main()
{
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1; i<=n; i++)cin>>a[i];
		sort(a+1,a+1+n);
		/*把a数组排序*/
		ans=0; 
		for(int i=1; i<=n; i++)/*从小到大*/
			if(a[i]<=i)ans=max(i+1,ans);/*找到能进去中，最大的*/ 
		if(ans==0)cout<<"1\n";/*注意，坑点，如果一个都进不去，要输出1！！！*/
		else cout<<ans<<"\n";
		/*输出答案*/
	}
	return 0;
}
```


---

## 作者：iterator_it (赞：0)

我们可以发现，对于 $1$ 到 $n$ 之间的任何一个数字 $i$，如果第 $i$ 个人可以进入，那么从 $1$ 到 $i$ 的人都可以进入。

所以，我们只需要枚举 $1$ 到 $n$，如果第 $i$ 个人可以进入，那么我们的结果就为 $i+1$，因为自己也是人，所以有了这个 $+1$。

那么，我们如何判断第 $i$ 个人能否进入呢？其实我们只需要判断 $a_i$ 是否 $\leq i$ 即可，因为我们是按照顺序遍历，所以就算第 $i$ 个人可以进入，也要遍历到 $n$，不可以中途`break`。

核心代码：
```cpp
sort(a+1,a+1+n);
int ans=0;
for(int i=1;i<=n;i++)
	if(a[i]<=i)
    	ans=i;
cout<<ans+1;//注意这里是ans+1，因为我们要把自己算进去
```

---

## 作者：_lmz_ (赞：0)

我们可以发现，如果第 $i$ 个人可以进入，那么前 $i$ 个人都是可以进入的。

然后，我们可以发现，只有当 $a_i \leq i$ 的时候，第 $i$ 个人才可以进入。

所以说，我们只需要维护一下这个序列，求出最大值，就可以快乐的 AC 啦。

核心代码：
```cpp
/*输入*/
ll ans=1;
for(int i=1;i<=n;i++)
    if(a[i]<=i)
        ans=i+1;
/*输出*/
```

---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1358B)

好奇这比赛题面是啥会违反互联网相关法律（

cf 登不上看不了/kk

**结论**：首先对于 $a$ 数组从小到大排个序，

然后找到最大的 $i$ 满足 $a_i\le i$ 并输出 $i+1$ 即可。

**简略证明**：对于一个人 $i$，有两种情况：

- 如果他进去了，那么对于所有的满足 $a_j<a_i$ 的 $j$ 都可以进去；

- 如果他没进去，那么那么对于所有的满足 $a_j>a_i$ 的 $j$ 都不能进去；

所以我们只要找到 $a_i$ 最大且能进去的人即可。

由题易知能进去的人 $i$ 必须满足 $a_i\le i$，

所以题目就被转化成：求出最大的 $i$，使$a_i\le i$。

由于没有体面所以补充下数据范围：

$1\le n\le 10^5,1\le a_i\le 2\times 10^5$

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);//排序 
		int ans=1;//注意至少会有一个人进去，所以ans初始化为1 
		for(int i=1;i<=n;i++){
			if(a[i]<=i){
				ans=i+1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：LeavingZzz (赞：0)

# Solution For CF1258B  
（~~从whk里面溜出来比赛qaq~~）  
介绍一个线性的做法（效率上和 $O(n)$ 差不多）  

大部分人都用的是 `sort` 通过此题，但是这会让复杂度带上一个 $log$，然后你就会注意到有一个条件：$1\le a_i\le 2\times10^5$。  

值域这么小，暗示桶排序嘛  

所以我们用桶，$book[i]$ 表示需要等到 $i$ 个人的时候才能来的人的个数。  

然后就直接枚举每一个 $i$ 来统计。  
因为不一定每次枚举到一个 $i$ 的时候等候值为 $i$ 的人一定可以来，所以我们开一个变量记录我们已经存下来的人数。  

如果对于当前的 $i$ 满足 $\boxed{\color{green}i\le\texttt{已经来了的人}+\texttt{当前累计的人数}+book[i]-1}$，那么就说明之前累计的所有人和等候值为 $i$ 的这些人都可以来了，更新答案，并且把累计器清零。  

如果不满足这个条件，说明这 $book[i]$ 个人要等到有更多的人才可以来，就把这 $book[i]$ 个人加入累计器,继续枚举。  

细节详见代码啦qaq  
$\large\mathsf{Code:}$  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=200007;
typedef long long LL;
int book[maxn];
int N;
int T;
inline int R()
{
    char c;
    int re;
    while((c=getchar())>'9'||c<'0');
    re=c-48;
    while((c=getchar())>='0'&&c<='9')
    re=re*10+c-48;
    return re;
}
int main()
{
    T=R();
    while(T--)
    {
        memset(book,0,sizeof(book));
        N=R();
        LL cur=1,x,lim=0,tmp=0,val;
        //lim为需要等候人数最多的那一类人等候的人，注意初始化！
        //cur是已经来了的人，tmp是累计器
        for(register int i=1;i<=N;i++)
            x=R(),book[x]++,lim=max(lim,x);
        for(register int i=1;i<=lim;i++)
        {
            if(book[i])
            {
                val=cur+book[i]+tmp-1;
                if(val>=i)//如果能来
                {
                    cur+=tmp+book[i];//更新当前已经来的人数
                    tmp=0;//累计器清零
                }
                else tmp+=book[i];//暂时来不了，存起来
            }
        }
        printf("%lld\n",cur);
    }
    return 0;
}
```
~~萌新上分，越上越昏~~  
$\huge\mathcal{The\text{ }End}$  
谢谢管理大大审核 ^_^

---

