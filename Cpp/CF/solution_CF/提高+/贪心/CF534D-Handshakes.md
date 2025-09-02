# Handshakes

## 题目描述

On February, 30th $ n $ students came in the Center for Training Olympiad Programmers (CTOP) of the Berland State University. They came one by one, one after another. Each of them went in, and before sitting down at his desk, greeted with those who were present in the room by shaking hands. Each of the students who came in stayed in CTOP until the end of the day and never left.

At any time any three students could join together and start participating in a team contest, which lasted until the end of the day. The team did not distract from the contest for a minute, so when another student came in and greeted those who were present, he did not shake hands with the members of the contest writing team. Each team consisted of exactly three students, and each student could not become a member of more than one team. Different teams could start writing contest at different times.

Given how many present people shook the hands of each student, get a possible order in which the students could have come to CTOP. If such an order does not exist, then print that this is impossible.

Please note that some students could work independently until the end of the day, without participating in a team contest.

## 说明/提示

In the first sample from the statement the order of events could be as follows:

- student 4 comes in ( $ a_{4}=0 $ ), he has no one to greet;
- student 5 comes in ( $ a_{5}=1 $ ), he shakes hands with student 4;
- student 1 comes in ( $ a_{1}=2 $ ), he shakes hands with two students (students 4, 5);
- student 3 comes in ( $ a_{3}=3 $ ), he shakes hands with three students (students 4, 5, 1);
- students 4, 5, 3 form a team and start writing a contest;
- student 2 comes in ( $ a_{2}=1 $ ), he shakes hands with one student (number 1).

In the second sample from the statement the order of events could be as follows:

- student 7 comes in ( $ a_{7}=0 $ ), he has nobody to greet;
- student 5 comes in ( $ a_{5}=1 $ ), he shakes hands with student 7;
- student 2 comes in ( $ a_{2}=2 $ ), he shakes hands with two students (students 7, 5);
- students 7, 5, 2 form a team and start writing a contest;
- student 1 comes in( $ a_{1}=0 $ ), he has no one to greet (everyone is busy with the contest);
- student 6 comes in ( $ a_{6}=1 $ ), he shakes hands with student 1;
- student 8 comes in ( $ a_{8}=2 $ ), he shakes hands with two students (students 1, 6);
- student 3 comes in ( $ a_{3}=3 $ ), he shakes hands with three students (students 1, 6, 8);
- student 4 comes in ( $ a_{4}=4 $ ), he shakes hands with four students (students 1, 6, 8, 3);
- students 8, 3, 4 form a team and start writing a contest;
- student 9 comes in ( $ a_{9}=2 $ ), he shakes hands with two students (students 1, 6).

In the third sample from the statement the order of events is restored unambiguously:

- student 1 comes in ( $ a_{1}=0 $ ), he has no one to greet;
- student 3 comes in (or student 4) ( $ a_{3}=a_{4}=1 $ ), he shakes hands with student 1;
- student 2 comes in ( $ a_{2}=2 $ ), he shakes hands with two students (students 1, 3 (or 4));
- the remaining student 4 (or student 3), must shake one student's hand ( $ a_{3}=a_{4}=1 $ ) but it is impossible as there are only two scenarios: either a team formed and he doesn't greet anyone, or he greets all the three present people who work individually.

## 样例 #1

### 输入

```
5
2 1 3 0 1
```

### 输出

```
Possible
4 5 1 3 2 ```

## 样例 #2

### 输入

```
9
0 2 3 4 1 1 0 2 2
```

### 输出

```
Possible
7 5 2 1 6 8 3 4 9```

## 样例 #3

### 输入

```
4
0 2 1 1
```

### 输出

```
Impossible
```

# 题解

## 作者：边缘白鸟 (赞：5)

我来完善一下其他题解的想法。

题意：一群学生会去参加比赛，然后三人一组，每个人会和场馆中还未组队的 $a[i]$ 个人进行握手，可以自己一个人一组，求给出一个可行排列。

我们来看一下样例二，可以很容易的模拟出一个过程：

$$
0\ \ \ \ 2\ \ \ \ 3\ \ \ \ 4\ \ \ \ 1\ \ \ \ 1\ \ \ \ 0\ \ \ \ 2\ \ \ \ 2
$$

然后你肯定让 $0$ 的先进去，然后因为要让后面数字大的人进去，所以前面的不要组队，先是能进去肯定先进去。

然后等到进不去了，就开始三人组队。

那么假设你这一次进去了 $x$ 人，即一个 $1,2,\dots,x$ 的序列，那么组完队就是 $x-3$ 人。

那么接下来从 $x+1-3$ 的序号开始进人。

所以限制只有，当前要进去的这个人的数字，是否小于等于当前场馆内未组队人数，为了让后面的人进去，场馆中一定要有一些未组队的人来当基石。

在这样的情况达到最后组队的人数字是 $0,1,2$ 时，就成功了。

比如第二个样例，如果加上一个 $5$ ，就完蛋了，因为这样模拟最后的序列是：

$$
0\ \ \ \ 1\ \ \ \ 2\ \ \ \ 2
$$

然后你从 $0$ 开始拿，最后就留了一个 $2$ 拿不了了。

那么由上面的过程，可以想到用一个桶来维护人，代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 1;

int n, a[N], cur = 0, tot, ans[N];

vector <int> cnt[N];

int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++) {
		scanf ("%d", &a[i]);
		cnt[a[i]].push_back (i); // 桶，为了构造答案方便所以用 vector  
	}
	while (tot < n) {
		if (cnt[cur].size () > 0) { // 能继续让人进来就先让人进 
			ans[++ tot] = cnt[cur].back (); // 就是构造答案  
			cnt[cur ++].pop_back (); // 用完就扔掉不然要出事  
		}
		else { // 如果不存在可以继续进的了  
			if (cur < 3) // 取完以后结果这一批队伍都不到三个 
				return puts ("Impossible"), 0;
			cur -= 3; // 先让里面的人组成一只队伍，cur 就是当前等待人数（进去了但是没组队） 
		}
	}
	puts ("Possible");
	for (int i = 1; i <= tot; i ++)
		printf ("%d ", ans[i]);
}
```

---

## 作者：nothing__ (赞：1)

思路：显然直接模拟，如果小于当前未组队人数小于三，并且可以之前找到没有使用过的位置使用，否则无解；如果当前大于等于三，就往下模拟到第一个没有使用过的。

具体实现：先排序，然后离散化，每次二分查找，查找完以后记忆化当前值哪些节点不可用。

代码稍丑，勉强看，记忆化可以自己加，要特判一下没有查找过的情况。

代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x=0, w=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') w=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+(ch-'0'); ch=getchar();}
	return x*w;
}
const int N=2e5+10;
int n, ans[N];
bool v[N];
int c[N], p[N], w[N];
bool cmp(int x, int y) {return c[x]<c[y];}
map<int, int> le;
int main() {
	n=read();
	for(int i=1;i<=n;i++) c[i]=read(), p[i]=i;
	sort(p+1, p+1+n, cmp);
	for(int i=1;i<=n;i++) w[i]=c[p[i]];
	if(w[1]!=0) {puts("Impossible"); return 0;}
	int now=1; ans[1]=p[1]; v[1]=1;
	for(int i=2;i<=n;i++,now++) {
		if(now<3) {
			int id=lower_bound(w+1, w+1+n, now)-w;
			if(le[w[id]]==-1||w[id]!=now) {puts("Impossible"); return 0;}
			if(w[id]==now&&!v[id]) {
				ans[i]=p[id];
				v[id]=true;
				if(w[id+1]==now&&id!=n) le[w[id]]=id+1;
				else le[w[id]]=-1;
			}
			else {
				bool pd=0;
				if(le[w[id]]==0&&w[id]==now) le[w[id]]=id;
				for(int j=le[w[id]];j<=n;j++) {
					if(w[j]!=now) break;
					if(!v[j]) {
						ans[i]=p[j];
						v[j]=true; pd=1; 
						if(w[j+1]==now&&j!=n) le[w[id]]=j+1;
						else le[w[id]]=-1;
						break;
					}
				}
				if(!pd) {puts("Impossible"); return 0;}
			}
		}
		else {
			int id=lower_bound(w+1, w+1+n, now)-w;
			if(le[w[id]]!=-1&&w[id]==now) {
				if(le[w[id]]==0) le[w[id]]=id;
				if(w[id]==now&&!v[id]) {
					ans[i]=p[id];
					v[id]=true; 
					if(w[id+1]==now&&id!=n) le[w[id]]=id+1;
					else le[w[id]]=-1;
					continue;
				}
				else if(w[id]==now) {
					bool pd=0;
					for(int j=le[w[id]];j<=n;j++) {
						if(w[j]!=now) break;
						if(!v[j]) {
							ans[i]=p[j];
							v[j]=true; pd=1; 
							if(w[j+1]==now&&j!=n) le[w[id]]=j+1;
							else le[w[id]]=-1;
							break;
						}
					}
					if(pd) continue;
				}
			}
			now-=3;
			bool pd=0;
			while(now>=0) {
				id=lower_bound(w+1, w+1+n, now)-w;
				if(le[w[id]]==-1||w[id]!=now) {
					if(now>=3) {now-=3; continue;}
					else break;
				}
				if(le[w[id]]==0) le[w[id]]=id;
				if(w[id]==now&&!v[id]) {
					ans[i]=p[id]; 
					v[id]=true; pd=1; 
					if(w[id+1]==now&&id!=n) le[w[id]]=id+1;
					else le[w[id]]=-1;
					break;
				}
				else if(w[id]==now) {
					bool f=0;
					for(int j=le[w[id]];j<=n;j++) {
						if(w[j]!=now) break;
						if(!v[j]) {
							ans[i]=p[j];
							v[j]=true; f=1; 
							if(w[j+1]==now&&j!=n) le[w[id]]=j+1;
							else le[w[id]]=-1;
							break;
						}
					}
					if(f) {pd=1; break;}
				}
				if(now<3) break; else now-=3;
			}
			if(!pd) {puts("Impossible"); return 0;}
		}
	}
	puts("Possible");
	for(int i=1;i<=n;i++) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：yangmuguang (赞：0)

### 题意
本来有一个数列 $a$，满足 $\forall a_i\ge 0,a_1=0$，且 $a_i= a_{i-1}+1-3k$，其中 $k$ 为自定的非负整数。

现在这个数列被打乱了，问原数列是什么，输出原数列的每一项在新数列中的位置。
### 解法
从 $0$ 开始摆放，每次从大到小枚举可以放什么数，如果能放就放，没有能放的就判负。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
#define no {cout<<"Impossible";return 0;}
ll n,ans[200005];
deque<ll>v[200005];
int main()
{
	faster;
	cin>>n;
	for (ll i=1;i<=n;i++)
	{
		ll a;
		cin>>a;
		v[a].pb(i);
	}
	ll x=0;
	if (!v[x].size())no
	else
	{
		ans[1]=v[x].back();
		v[x].pop_back();
	}
	for (ll i=2;i<=n;i++)
	{
		bool flag=1;
		ll a=x+1;
		while (a>=0)
		{
			if (v[a].size())
			{
				ans[i]=v[a].back();
				v[a].pop_back();
				flag=0;
				x=a;
				break;
			}
			a-=3;
		}
		if (flag) no;
	}
	cout<<"Possible\n";
	for (ll i=1;i<=n;i++)cout<<ans[i]<<" ";
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 翻译：

原翻译中已经给出数学模型了，但是想要用那么抽象的东西分析问题难度好像反而上升了不少，这里给出原本的题意：

在农夫约翰的农场上，有 $n$ 头奶牛，现在这些奶牛正在举办一场 CTOP 比赛，每头奶牛在入座前需要和其他单独写代码的奶牛打招呼，在任意时候，每三个奶牛可以组成一队（也可不组）,这样就不用打招呼了。组队操作不可撤销。

已知每一只奶牛想要打招呼的次数，求一种可行的入场方案使得所有的奶牛都能满足这个特定的打招呼次数。

---
### 解题思路：

考虑贪心，做法不难，但想完整地证明还是有一点难度的。

在分析问题前，可以先将所有的人按照打招呼的需求数量从小到大排序，显然这种仅仅改变编号的变换不会造成任何影响，而且可以方便分析。

然后发现每一个人在加入后就失去了特征，所以只需要维护当前未组队的有多少人，每一次组队直接将这个值减少 $3$ 就行了。
再考虑加入操作，当未组队的人确定的时候，每一次可能的加入人的打招呼次数是唯一且确定的。、

这样问题就简单多了，每一次只需要考虑是加入一个人或者减少 $3$ 个人让其组队就行了。

不过直接这样做还是不太好处理（直接做复杂度 $O(2^n)$），考虑再次发掘其性质。

注意到如果在可以将一个人加入时，不加入而将三个人组队可以直接不考虑，也就是说在当前能加入时一直加入，当无法加入时让其中一些人组队。

这样做的证明思路是当削减人数可行时，证明不削减而优先让要求打招呼多的人进入一定可行，然后再反过来证明先让打招呼多的人进入，最后削减人数可行时先削减人数可能不可行。也不是很难。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
using namespace std;
int n,a[200005],t[200005],now,flag=1,cnt[200005],pri[200005];
vector <int> ans[200005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),t[a[i]]++;
	for(int i=1;i<=n;i++){
		while(t[now]==0&&now>=3)now-=3;
		if(t[now]==0&&now<3)flag=0;
		t[now]--;
		ans[now].push_back(i);
		cnt[now]++;
		now++;
	}
	if(flag==0)printf("Impossible\n");
	else{
		printf("Possible\n");
		for(int i=1;i<=n;i++)
		pri[ans[a[i]][--cnt[a[i]]]]=i;
		for(int i=1;i<=n;i++)
		printf("%d ",pri[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Silence_World (赞：0)

# 题意

题目还是比较容易理解的，就是给你一堆人，这些人要互相打招呼，三个人可以组一队，求每个人打招呼的次数，数学模型题中已给，简单易懂，在此不过多赘述。

# 思路

贪心，我们肯定是优先让打招呼多的进去，然后判断组队，三人一组，很显然的，我们只需要判断新来的人或自己是否组队就行了，主要就是判断新加入的人，然后不停减少人数，最后构造出解，算是很简单的一道蓝了。

but，我又被 UKE 卡了好久呜呜呜，真的已经调自闭了 QAQ，最后发现数组开小了（崩溃）。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
priority_queue<int,vector<int>,greater<int> >q;
int a[10000005];
int dp[1000005];
int t1[1000005];
main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&t1[i]);
		a[t1[i]]++;
	}
	int r=0;
	bool fl=1;
	vector<int>b[200005];
	int c[1000005];
	for(int i=1;i<=n;i++){
		while(!a[r] and r>=3)r-=3;
		if(!a[r] and r<3)fl=0;
		a[r]--;
		b[r].push_back(i);
		c[r]++;
		r++;
	}
	int sum[1000005];
	if(!fl){
		printf("Impossible");
		return 0;
	}
	else{
		printf("Possible\n");
		for(int i=1;i<=n;i++){
			c[t1[i]]--;
			sum[b[t1[i]][c[t1[i]]]]=i;
		}
		for(int i=1;i<=n;i++)printf("%.lld ",sum[i]);
		printf("\n");
	}
	return 0;
} 
```


---

## 作者：durex_com (赞：0)

题意：
选手进场会与没有组队的人握手，每三个未组队的人可以组团队，也可以
不组，现在给你每个人要求握手次数，输出一组可行解，否则输出“Impossible”。
尽量多让人进。
不行就组队再让人进。

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector> 
using namespace std;
int n;
int cou=0;
int ans[200001];
int a[200001];
vector<int> tong[200001];
int cnt=0,tot=0;;
int vis[200001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);tong[a[i]].push_back(i);
	}
	while(tot<n)
	{
		int bl=0;
		if (tong[cnt].size()>0)
		{
			bl=1;
			tot++;
			ans[tot]=tong[cnt].back();
			tong[cnt].pop_back();
			cnt++;
		}
		if (bl==0)
		{
			if (cnt<3) 
			{
				printf("Impossible");
				return 0;
			}
			cnt-=3;
		}
	}
	printf("Possible\n");
	for(int i=1;i<=n;i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

