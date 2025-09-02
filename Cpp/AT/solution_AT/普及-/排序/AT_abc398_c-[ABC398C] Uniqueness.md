# [ABC398C] Uniqueness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc398/tasks/abc398_c

有 $N$ 个人，编号为 $1$ 至 $N$。第 $i$ 个人持有数值 $A_i$。

请找出满足以下条件的个体中持有数值最大的那个人的编号：
- 在除自己之外的 $N-1$ 人中，不存在持有相同数值的人。

如果不存在满足条件的人，请报告这一情况。


## 说明/提示

### 约束条件

- $1 \leq N \leq 3 \times 10^5$
- $1 \leq A_i \leq 10^9$
- 输入均为整数

### 样例解释 1

满足条件的人为编号 $4,7,8,9$ 的 $4$ 人。他们持有的数值分别为 $7,4,5,8$，其中最大数值的持有者是编号 $9$，因此答案为 $9$。

### 样例解释 2

当不存在满足条件的人时，输出 `-1`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
2 9 9 7 9 2 4 5 8```

### 输出

```
9```

## 样例 #2

### 输入

```
4
1000000000 1000000000 998244353 998244353```

### 输出

```
-1```

# 题解

## 作者：oVo_yangxy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc398_c)

小小枚举，拿下！
## 题目描述
给你 $N$ 个数，求出这些数中最大数的编号，并且这个数在所有数当中只有一个。如果不存在这个数就输出负一。
## 思路
输入，把输入的数存在字符串里，并记录每个数的编号。

把结构体从大到小的按数的大小排序，这里每个数的编号是会跟着原数变化的。

从前往后的找，如果这个数的左右相邻的两个数都与它不相等，说明这个数满足条件，输出该数编号，结束程序。

在这里，如果没有数满足条件，程序是不会中途停下来的，所以在最后输出一个负一就好了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node{
	int a,id;
}s[300005];
bool cmp(node a,node b){return a.a>b.a;}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].a;
		s[i].id=i;
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(s[i].a!=s[i-1].a && s[i].a!=s[i+1].a){
			cout<<s[i].id;
			return 0;
		}
	}
	cout<<"-1";
    return 0;
}
```
~~（给蒟蒻点个赞吧）~~

---

## 作者：Ray_yi (赞：2)

### 思路：

看到题目首先想到暴力，用一个桶来标记，但是数据范围太大，开不了这么大的数组，所以直接开数组标记这个方法行不通。

于是，我们就可以想到，把原数组的每个数的下标记住，再从大到小排序，遍历整个数组，找到没有重复数字的，也就是前后两个数都不等于当前数的第一个数，在输出下标即可。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node{
	int x,id;
}a[300005];
bool cmp(node a,node b){
	return a.x>b.x;
}//从大到小排序
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x,a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].x!=a[i-1].x&&a[i].x!=a[i+1].x){//判断有没有重复的数
			cout<<a[i].id;
			return 0;
		}
	}
	cout<<"-1";
	return 0;
}
```

---

## 作者：_qumingnan_ (赞：2)

[题目跳楼机](https://www.luogu.com.cn/problem/AT_abc398_c)

# 正文开始：

## 阅读理解：

有 $n$ 个人，编号为 $1\sim n$，每个人身上有一个数 $A_i$，求值最大且没有任何人与他数值相同的人的编号。

## 思路

看到题目，我们立马就能想到用一个桶来统计数出现的情况，于是我们就只需要在统计完后再遍历一次，就可以求出值最大的人的编号。

### 代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[300005],ans=-1,s;
map<int,int>mp;//桶。因为 Ai<=1e9，数组大小不够，所以用map 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],mp[a[i]]++;//统计每个数出现的情况 
	for(int i=1;i<=n;i++)//遍历 
		if(mp[a[i]]==1)//只出现一次 
			if(a[i]>s)ans=i,s=a[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：YBJ1006 (赞：1)

排序一下，从大到小试即可。

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 3e5 + 10;

struct node
{
    int val, id;
}a[N];

bool cmp(node x, node y)
{
    return x.val > y.val;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
    {
        if (a[i].val != a[i + 1].val && a[i].val != a[i - 1].val)
        {
            cout << a[i].id;
            return 0;
        }
    }
    cout << -1;
    return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 题意

给定一个序列 $A$，其中含有 $N$ 个数字。我们需要找到只出现过一次的数字中最大的数字的编号。

## 分析

我们要完成这几个操作：

1. 记录每个数出现的次数
  
2. 找到只出现一次的数字
  
3. 求出数值最大的满足条件的数的编号
  

对于每个要完成的操作，我们依次分析：

1. 由于这道题的数据不大，$1\le N\le 3\times10^5$，所以我们可以考虑到使用桶进行计数。而 $1\le A_i\le 10^9$，所以开数组是不行的，就可以想到使用 map，代码实现即为 `map<int,int> a`，只需要在输入的同时加入这个数即可。
  
2. 在数列中枚举每个数，对于数 $B_i$，检查 $A_{B_i}$。
  
3. 若 $A_{B_i}=1$，与当前最大数字比较，更新数字编号。
  

这样，每个需要操作的步骤都完成了，就可以开始写代码了。

## 代码
[AC记录](https://atcoder.jp/contests/abc398/submissions/64057523)
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> a;
int b[300005],ans=-1,cnt;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		a[b[i]]++; //桶中加入数 
	}
	for(int i=1;i<=n;i++){
		if(a[b[i]]==1){ //若只出现一次 
			if(b[i]>cnt)
				ans=i,cnt=b[i]; //更新 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：SunburstFan (赞：1)

## C - Uniqueness

### 题目大意

给定 $N$ 个人，每人有一个整数 $A_i$，若某人的数在所有人中不重复，则该人满足条件。找出满足条件的人的最大数，并输出此人的编号；若无满足条件者，则输出 $-1$。

### 解题思路

统计每个整数出现的次数，然后在所有只出现一次的整数中寻找最大值，并输出对应的下标；若没有出现次数为 $1$ 的整数，则输出 $-1$。

**代码**：

```cpp
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int n;
    cin>>n;

    vector<int> a(n+1);
    for(int i=1;i<=n;i++)
        cin>>a[i];
    
    map<int,int> mp;
    for(int i=1;i<=n;i++)
        mp[a[i]]++;
    
    int maxn=-1,ans=-1;
    for(int i=1;i<=n;i++){
        if(mp[a[i]]==1&&maxn<a[i]){
            maxn=a[i];
            ans=i;
        }
    }
    cout<<ans;
    
    return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：1)

# AT_abc398_c [ABC398C] Uniqueness 题解

----------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc398_c)。


~~刚开始看错题了还挂了一发。~~

---------------

## 题意

求出现次数为 $1$ 的所有数最大的那个数的位置。

---------------

## 思路

你拿个 `map` 统计每个数出现次数（这里也可以离散化后用桶）。

然后扫一遍所有数打擂台求最大即可。

复杂度 $O(n\log n)$。

---------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
int in()
{
	int k=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=3e5+10;
int a[N];
map<int,int>mp;
int main()
{
	int n=in();
	for(int i=1;i<=n;i++)a[i]=in(),mp[a[i]]++;
	int ans=-1;
	for(int i=n;i>=1;i--)
		if(mp[a[i]]==1)
			if(ans==-1||a[i]>a[ans])ans=i;
	out(ans);
	return 0;
}
```

---------------

若有误或不清，欢迎评论或私信。

---

## 作者：abc1856896 (赞：1)

简单题，建议评橙。

# Solution

暴力 $O(n^2)$ 会超时，直接上桶优化即可。但 $A_i$ 范围大，因此我们使用 map 维护即可。

注意最后输出的 $A_i$ 最大值。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n,a[N];
unordered_map<int,int>cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],cnt[a[i]]++;
	int mx=-1;
	for(int i=1;i<=n;i++) if(cnt[a[i]]==1&&(mx==-1||a[i]>a[mx]))mx=i;
	if(mx==-1)cout<<"-1";
	else cout<<mx;
	return 0;
}
```

---

## 作者：JCT_addyi (赞：1)

## 题意：
给你 $n$ 个数，编号为 $1$ 到 $n$ 的数，找到没有和它相同的一些数，如果没有就输出 $-1$，否则找到它们当中值最大的数，输出这个数的下标。

## 思路：
我们用桶记录每个数的个数，然后找出个数为一的数，再在当中比较数的大小，然后拿个变量存下表。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300005],ans,cnt;
map<int,int> b; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]++;//桶
	}
	for(int i=n;i>=1;i--){
		if(b[a[i]]==1){
			if(a[i]>ans){//比较
				ans=a[i];
				cnt=i;//存下标
			}
		}
	}
	if(cnt==0) cout<<"-1";//输出-1
	else cout<<cnt;//否则输出下标
	return 0;
}

```

谢谢大家！

---

## 作者：boluo2014 (赞：1)

这次 atcoder 的 C 题不知道为什么那么的水。 

### 思路

首先，题目要看懂：在 $n$ 个数中，找到最大的只出现一次的数。

那如果我们之间遍历每一个 $a_i$，再去数数，就很容易开心地 TLE。但是我们发现每一个 $a_i$ 的数量永远是不变的，所以预处理出每个数的数量即可。

但是 $a_i \le 10^9$，怎么办？普通数组肯定炸裂，其实可以使用 map，我发现 at 经常有用 map 的题。

### 做法

先用 map 预处理出每一个数出现的次数。

再遍历每一个 $a_i$，如果它只出现一次就比一比是不是更大，并记录编号，记录标记。

最后如果没有标记过输出不可行，否则输出编号即可。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int a[maxn];
map<int,int>mp;
int main(){
	int n;
	cin>>n;
	int i,mx=0,id=-1;
	bool t=false;
	for(i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	for(i=1;i<=n;i++){
		if(mp[a[i]]==1){
			t=true;
			if(a[i]>mx){
				id=i;
				mx=a[i];
			}
		}
	}
	if(t)cout<<id<<endl;
	else cout<<-1<<endl;
	return 0;
}
```
代码不像你的那样形容俊美、英俊帅气，所以凑活吧。

如果你觉得我是个傻子，就点赞吧。

---

## 作者：CCY20130127 (赞：1)

## 题目大意：
[题目传送门](https://www.luogu.com.cn/problem/AT_abc398_c)

求满足除自己以外的 $n-1$ 人中不存在与自己拥有相同数量的人这一条件的人中拥有最多数量的人的编号。

## 题目思路：
这道题不用什么算法，只需要一个数组记录每个元素出现的次数，用一个变量存**满足这一条件的人中拥有最多数量的人**，在用一个变量存答案。

## 注意事项：
数组要开大一点！别漏了 $-1$。

## 代码展示：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int n,a[3*N],maxn=INT_MIN,ans;
map<int,int> f;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(f[a[i]]==1){
			if(a[i]>maxn){
				maxn=a[i];
				ans=i;
			}
		}
	}
	if(ans!=0) cout<<ans;
	else cout<<-1;
	return 0;
}
```

---

## 作者：DoubleQLzn (赞：0)

> 考察知识点：map，模拟

我们考虑使用一个 map 来存储下所有数字的出现次数。

随后将出现次数 $1$ 的数本身与下标放入表 $v$。

接着将 $v$ 排序，输出下标即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> f;
int a[300005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,x;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		f[a[i]]++;
	}
	vector<pair<int,int>> b;
	for (int i = n;i >= 1;i--)
	{
		if (f[a[i]] == 1)
		{
			b.push_back({a[i],i});
		}
	}
	sort(b.begin(),b.end());
	if (b.size()) cout << b[b.size() - 1].second;
	else cout << -1;
	return 0;
}
```

---

## 作者：kuaiCreator (赞：0)

## 题目大意
编号为 $1-n$ 的人手里都有一个数，找到数是唯一且最大的那个人的编号。
## 解题思路
映射一下数出现的个数，然后遍历找到唯一的数，再遍历人找到人的编号。
## 代码实现
```C++
#include<bits/stdc++.h>
using namespace std;
map<int, int> mp;
int n, a[300005], ans;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]]++;
	}
	for (auto it : mp) {
		if (it.second == 1)
			ans = max(ans, it.first);
	}
	for (int i = 1; i <= n; i++)
		if (a[i] == ans) {
			cout << i;
			return 0;
		}

	cout << -1;
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定 $N$ 个编号为 $1\sim N$ 的点，第 $i$ 个点有权值 $A_i$，求出权值最大且唯一的点的编号。

## 解题思路

首先满足权值唯一的点，可通过桶+哈希或者用 `unordered_map` 求解。然后再扫一遍 $A_i$，求出每个 $A_i$ 对应的桶里的值，并找到值为 $1$ 且 $A_i$ 最大的位置，答案即为 $i$，初始时答案设为 $-1$ 即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,a[300001],ans,p=-1;
unordered_map<ll,ll> bz;

int main()
{
    n=read();
    for(R int i=1; i<=n; ++i)
    a[i]=read(), ++bz[a[i]];

    for(R int i=1; i<=n; ++i)
    {
        if(bz[a[i]]==1 && ans<a[i])
        ans=a[i], p=i;
    }

    write(p);
    return 0;
}
```

---

## 作者：rqliushuangyu (赞：0)

### 题目大意
找一个数值最大且只出现过一次的下标。

### 思路
排序（当然要记录上原来的下表），从大向小找，找到为单独出现的值，输出并结束运行。

### 代码
[代码传送门](https://atcoder.jp/contests/abc398/submissions/64055927)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct peo{
	int idx,val;
};
bool cmp(peo a,peo b){
	return a.val<b.val;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	peo a[n+1];
	for(int i=1;i<=n;i++){//输入
		cin>>a[i].val;a[i].idx=i;
	}
	sort(a+1,a+1+n,cmp);//排序，以值的大小排
	for(int i=n;i>=1;i--){
		if(i==1 || a[i].val!=a[i-1].val){
			if(i==n || a[i].val!=a[i+1].val){//第一个单独出现的，输出并结束。
				cout<<a[i].idx;
				return 0;
			}
		}
	}
	cout<<-1;
	return 0;
}

```

---

## 作者：liusimo0727 (赞：0)

可以使用结构体排序。

在输入时，可以将输入的数，成为结构体中的一个数，循环变量作为另一个数，把标准设置为输入的那个数。

最后逆序遍历，如果两侧没有和它一样的数，就输出编号。

上代码！


```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=3*1e5+1;
struct node{
	int id,r;
}a[N];
bool cmp(node s,node q){
	if (s.r<q.r) return 1;
	else return 0;
}//标准
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].r;
		a[i].id=i;//赋值编号
	}
	sort(a+1,a+1+n,cmp);
	for(int i=n;i>=1;i--){
		if (a[i].r!=a[i-1].r&&a[i].r!=a[i+1].r){
			cout<<a[i].id;
			return 0;//记得结束
		}
	}
	cout<<-1;//最后就是不存在
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
按照对应 $A_i$ 排序完后若 $A_i$ 不等于 $A_{i-1}$ 和 $A_{i+1}$ 就输出 $i$。
### 代码
```cpp
struct node{int sum,z;}a[maxn];
bool cmp(node x,node y){return (x.sum!=y.sum)?x.sum<y.sum:x.z<y.z;}
int n;
signed main()
{
	fastread;
	cin>>n;
	for(int i=1;i<=n;i++) {cin>>a[i].sum;a[i].z=i;}
	sort(a+1,a+n+1,cmp);
	for(int i=n;i>=1;i--)
	{
		if(i==n&&a[i].sum!=a[i-1].sum)  return cout<<a[i].z,0;
		else if(i==1&&a[i].sum!=a[i+1].sum)  return cout<<a[i].z,0;
		else if(i!=1&&i!=n&&a[i].sum!=a[i+1].sum&&a[i-1].sum!=a[i].sum) return cout<<a[i].z,0;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 思路
用一个哈希表记录每个数出现的次数，寻找只出现一次的最大值并且返回它的位置。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int s(int n, vector<int>& a) {
    unordered_map<int, int> cnt;
    for (int i=0;i<n;i++) cnt[a[i]]++;//统计出现的次数 
    int m = -1, d = -1;
    for (int i = 0; i < n; ++i) 
        if (cnt[a[i]] == 1 && a[i] > m) m = a[i],d = i + 1;//更新只出现一次的最大值并且记录坐标 
    return d;
}
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << s(n, a) << endl;
    return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

首先，循环输入 $n$ 个数。使用 `unordered_map` 记录每个整数出现的次数。循环，每一次将 $f_x$ 增加 $1$。

然后使用 `vector`，统计那些只出现一次的数。这个代码比较好写：

```cpp
vector <int> u;
for (auto& p : f) 
    if (p.second == 1) u.push_back (p.first);
```

那么什么情况下是无解的呢？就是当我的 $u$ 里面没有数字的时候，就是无解的，所以输出 $-1$。

```cpp
if (u.empty ()) {
    cout << -1 << endl;
    return 0;
}
```

否则进行循环，在满足条件的人中，找出拥有最大整数的那个人。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define please return
#define AC 0
#define int unsigned long long
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)
signed main () {
    int n;
    cin >> n;
    vector <int> a (n);
    rep(i, 0, n - 1) cin >> a[i];
    unordered_map <int, int> f;
    for (int x : a) f[x] ++;
    
    vector<int> u;
    for (auto& p : f) 
        if (p.second == 1) u.push_back (p.first);
    if (u.empty ()) {
        cout << -1 << endl;
        return 0;
    }
    int m = *max_element (u.begin (), u.end ());
    rep(i, 0, n - 1) {
        if (a[i] == m) {
            cout << i + 1 << endl;
            break;
        }
    }
    
	please AC;
}
```

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1E5XWYKE3n?t=143)

[参考代码](https://atcoder.jp/contests/abc398/submissions/64033168)

---

