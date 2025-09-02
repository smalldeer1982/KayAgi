# Matching Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ . The beauty of the arrays $ a $ and $ b $ is the number of indices $ i $ such that $ a_i > b_i $ .

You are also given an integer $ x $ . Determine whether it is possible to rearrange the elements of $ b $ such that the beauty of the arrays becomes $ x $ . If it is possible, output one valid rearrangement of $ b $ .

## 说明/提示

In test cases 1 and 2, the beauty of the arrays has to be $ 0 $ since $ a_1 = 1 \le 2 = b_1 $ .

In test cases 3, 4, 5 and 6, the only possible beauty of the arrays is $ x = 1 $ and $ x = 2 $ . In particular, if $ b $ is rearranged to $ [2, 4, 1] $ , then $ a_3 = 3 > 1 = b_3 $ , so the beauty of the arrays is $ 1 $ . If $ b $ is kept in the same order as given the input, then $ a_2 = 4 > b_2 = 1 $ and $ a_3 = 3 > 2 = b_3 $ , so the beauty of the arrays is $ 2 $ .

## 样例 #1

### 输入

```
7
1 0
1
2
1 1
1
2
3 0
2 4 3
4 1 2
3 1
2 4 3
4 1 2
3 2
2 4 3
4 1 2
3 3
2 4 3
4 1 2
5 2
6 4 5 6 2
9 7 9 1 1```

### 输出

```
YES
2
NO
NO
YES
2 4 1
YES
4 1 2
NO
YES
1 9 9 7 1```

# 题解

## 作者：wxzzzz (赞：12)

### 思路

先考虑一个简化版的问题：$x=0$。

显然，思路是排序 $a_i,b_i$，直接判断是否所有 $a_i$ 都小于等于 $b_i$。

现在把问题扩展到 $x\ge 0$。

最优策略一定是这样：让最小的 $x$ 个 $b_i$ 匹配最大的 $x$ 个 $a_i$，这样就可以使后面满足 $a_i\le b_i$ 的操作有更多的选择余地。

对于最小的 $x$ 个 $a_i$ 和最大的 $x$ 个 $b_i$，仿照 $x=0$ 的做法，排序，判断是否任意 $a_i>b_i$。

对于剩下的数，直接用 $x=0$ 的做法。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, b[200005], ans[200005];
struct data {
    int id, val;
} a[200005];
bool cmp1(data x, data y) {
    return x.val > y.val;
}
bool cmp2(data x, data y) {
    return x.val < y.val;
}
bool solve() {
    sort(a + 1, a + n + 1, cmp1);
    sort(b + 1, b + n + 1);
    sort(a + 1, a + m + 1, cmp2);

    for (int i = 1; i <= m; i++) {
        if (a[i].val <= b[i])
            return 0;

        ans[a[i].id] = b[i];
    }

    sort(a + m + 1, a + n + 1, cmp2);

    for (int i = m + 1; i <= n; i++) {
        if (a[i].val > b[i])
            return 0;

        ans[a[i].id] = b[i];
    }

    return 1;
}
int main() {
    cin >> t;

    while (t--) {
        cin >> n >> m;

        for (int i = 1; i <= n; i++)
            a[i].id = i, cin >> a[i].val;

        for (int i = 1; i <= n; i++)
            cin >> b[i];

        if (!solve()) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";

        for (int i = 1; i <= n; i++)
            cout << ans[i] << ' ';

        cout << '\n';
    }

    return 0;
}
```

---

## 作者：Zhuluoan (赞：1)

## 题目简述

给定两个长度为 $n$ 的数列 $a,b$，再给定一个数 $x$，请你判断是否存在一种重排 $b$ 数列的方式，使得满足 $a_i>b_i$ 的 $i$ 恰好有 $x$ 个。

$n\leq 2\times 10^5$。

## 题目分析

遇到这种可行性问题，首先考虑做出最优解，以此来判断是否无解。

接下来，可以思考最优解如何构造，我们利用贪心思想，将 $a$ 数组中的前 $x$ 大的数与 $b$ 数组中的前 $x$ 小的数匹配在一起，判断能否满足这 $x$ 对数都是 $a_i>b_i$ 的。这样做的目的是尽量消耗 $a$ 数组中大的数，保存 $b$ 数组中较大的数，争取接下来 $n-x$ 个数满足 $a_i\leq b_i$。然后，我们判断剩余的数能否满足条件。如果上述两部分数都能满足条件，那便是可行，否则由于最优解都不可行，那一定是无解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,b[N],x,ans[N];
struct Num
{
	int num,id;
}a[N];
bool cmp1(Num i,Num j)
{
	return i.num>j.num;
}
bool cmp2(Num i,Num j)
{
	return i.num<j.num;
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>T;
    while(T--)
	{
	    int f=0;
		cin>>n>>x;
	    for(int i=1;i<=n;i++)
	    {
		    cin>>a[i].num;
		    a[i].id=i;
	    }
	    for(int i=1;i<=n;i++)
	    {
		    cin>>b[i];
	    }
	    sort(a+1,a+1+n,cmp1);
	    sort(b+1,b+1+n);
	    sort(a+1,a+1+x,cmp2);
	    for(int i=1;i<=x;i++)
	    {
		    if(a[i].num>b[i])
		    {
			    ans[a[i].id]=b[i];
		    }
		    else f=1;
	    }
	    sort(a+x+1,a+1+n,cmp2);
	    for(int i=x+1;i<=n;i++)
	    {
		    if(a[i].num<=b[i])
		    {
			    ans[a[i].id]=b[i];
		    }
		    else f=1;
	    }
	    if(f==1)
	    {
	    	cout<<"No\n";
		}
		else
		{
			cout<<"Yes\n";
	        for(int i=1;i<=n;i++)
	        {
		        cout<<ans[i]<<" ";
	        }
	        cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：bigclever (赞：1)

## 思路：
因为只有 $x$ 个 $a_i \gt b_i$，剩下的都要满足 $a_i \le b_i$。所以我们考虑贪心，让 $a$ 的前 $x$ 大与 $b$ 的前 $x$ 小进行**逐位**配对，然后让 $a$ 的前 $n-x$ 小与 $b$ 的前 $n-x$ 大进行**逐位**配对。易知这种方法必然是最优的，如果这种方案都满足不了，那么肯定无解。否则按此规则重排即可。 

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> a[200005];
int b[200005],ans[200005];
int main(){
	int t; scanf("%d",&t);
	while(t--){
		int n,x;
		scanf("%d %d",&n,&x);
		for(int i=1;i<=n;i++)scanf("%d",&a[i].first),a[i].second=i;
		for(int i=1;i<=n;i++)scanf("%d",b+i);
		sort(a+1,a+n+1),sort(b+1,b+n+1);
		int id1=n-x+1,id2=1;
		bool ok=true;
		for(int i=1;i<=x;i++){//枚举a的前x大与b的前x小
			if(a[id1].first<=b[id2]){ok=false;break;}
            //a的第id1个数配对b的第id2个数
			ans[a[id1].second]=b[id2],id1++,id2++;
		}	
		id1=1;//a重新从1开始
		for(int i=1;i<=n-x;i++){//枚举a的前n-x小与b的前n-x大
			if(a[id1].first>b[id2]){ok=false;break;}
			ans[a[id1].second]=b[id2],id1++,id2++;
		}
		if(ok){
			puts("yes");
			for(int i=1;i<=n;i++)printf("%d ",ans[i]);
			puts("");
		}else puts("no");
	}
	return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意
给定两个长为 $n$ 的数列 $a,b$，再给定一个数 $x$，判断是否有一种排列 $b$ 的方式，使得满足 $a_i>b_i$ 的 $i$ 恰好有 $x$ 个。
# 思路
我们需要满足 $a_i>b_i$ 的 $i$ 的个数刚好为 $x$，也就意味着除了这 $a_i>b_i$ 以外的部分需要保证 $a_i\le b_i$。

所以我们应为 $a$ 最大的 $x$ 个元素分配尽量小的 $b$ 的元素，这样才能尽可能保证这 $x$ 个外的 $a,b$ 剩余元素可以保证 $a_i\le b_i$。

有了以上思路，这道题基本上就很好过了。

只需要先将 $a,b$ 排序，然后将 $a$ 最大的 $x$ 个和 $b$ 最小的 $x$ 个分配。然后再将 $a,b$ 剩下的元素分配，看是否符合**使得满足 $a_i>b_i$ 的 $i$ 恰好有 $x$ 个**的条件。
# 实现
```cpp
#include<iostream>
#include<algorithm>
#define N 200005
using namespace std;
struct tmc{int n,i;}a[N],b[N];
bool cmp(tmc aa,tmc bb){return aa.n>bb.n;}
int t,n,m,k,c[N];
int main(){
	scanf("%d",&t);
	while(t--){
		int kd=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i].n),a[i].i=i;
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i].n);
			b[i].i=i;
			if(a[i].n>b[i].n)kd++;
		}if(kd==m){
			printf("YES\n");
			for(int i=1;i<=n;i++)printf("%d ",b[i].n);
			printf("\n");
			continue;
		}sort(a+1,a+n+1,cmp);
		sort(b+1,b+n+1,cmp);
		k=0;
		for(int i=1;i<=n;i++)if(a[i].n<=b[k+1].n)k++;
		if(m<(n-k)){
			printf("NO\n");
			continue;
		}k=0;
		for(int i=1;i<=n;i++)if(b[i].n<a[k+1].n)k++;
		if(m>k){
			printf("NO\n");
			continue;
		}for(int i=1;i<=m;i++)c[a[i].i]=b[n-m+i].n;
		for(int i=m+1;i<=n;i++)c[a[i].i]=b[i-m].n;
		printf("YES\n");
		for(int i=1;i<=n;i++)printf("%d ",c[i]);
		printf("\n"); 
	}
} 
```

---

## 作者：guozhe6241 (赞：1)

# 题目传送门

[CF1896C](https://www.luogu.com.cn/problem/CF1896C)

# 思路

根据这题的题意，先拿一个结构体将题中的 $a$ 数组存起来，里面存两个变量 $val,id$ 分别表示值和下标，然后创建一个 $b$ 数组和 $ans$ 数组。

然后把这两个数组排序，$a$ 数组按照值从小到大排序，$b$ 数组也按照值从小到大排序，再用一个 $flag$ 存储是否合法，初始化为 $false$。

接着我们取出 $b$ 数组第 $1 \thicksim x$ 个数判断一下是否大于等于 $a_{n-x+i}$，如果大于，把 $flag$ 赋值为 $1$，然后直接 $break$。

接着我们取出 $b$ 数组第 $x+1 \thicksim n$ 个数判断一下是否小于 $a_{i-x}$，如果小于，把 $flag$ 赋值为 $1$，然后直接 $break$。

如果 $flag$ 是 $true$，直接输出 $No$。

如果 $flag$ 是 $false$，先输出 $Yes$，再将 $b_i$ 赋值给 $ans_{a_n-m+i.id}$，然后下半部分也是同理的。

接下来讲一下证明。

因为我们要使 $a_i \gt b_i$ 的对数刚好有 $x$ 个，所以我们要将 $a$ 数组前 $x$ 大与 $b$ 数组前 $x$ 小放一起才可以符合题意。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int val,id;
}a[200005];
int t,n,m;
int b[200005],ans[200005];
bool cmp(node x,node y){
	return x.val<y.val;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i].val;
			a[i].id=i;
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		sort(a+1,a+n+1,cmp);
		sort(b+1,b+n+1);
		int flag=0;
		for(int i=1;i<=m;i++){
			if(b[i]>=a[n-m+i].val){
				flag=1;
				break;
			}
		}
		for(int i=m+1;i<=n;i++){
			if(b[i]<a[i-m].val){
				flag=1;
				break;
			}
		}
		if(flag){
			cout<<"No"<<endl;
		}else{
			cout<<"Yes"<<endl;
			for(int i=1;i<=m;i++){
				ans[a[n-m+i].id]=b[i];
			}
			for(int i=m+1;i<=n;i++){
				ans[a[i-m].id]=b[i];
			}
			for(int i=1;i<=n;i++){
				cout<<ans[i]<<" ";
			}
			cout<<endl;
		}
	}
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/140556087)

---

## 作者：Register_int (赞：1)

先对 $a,b$ 排序。由于我们需要满足：

- 前 $x$ 个 $b_i$ 尽量小、$a_i$ 尽量大，以满足 $\forall i\le m,a_i>b_i$。
- 后 $n-x$ 个 $b_i$ 尽量大、$a_i$ 尽量小，以满足 $\forall i>m,a_i\le b_i$。

那么有一个显然的贪心策略：按从小到大的顺序将 $a$ 的前 $x$ 大与 $b$ 的前 $x$ 小放一块。易证任何调整都是不优的，那么如果这种方案也无法满足，即可判定无解。时间复杂度 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct node { int x, id; } a[MAXN]; int b[MAXN], ans[MAXN];

int t, n, m; bool f;

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d%d", &n, &m), f = 0;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i].x), a[i].id = i;
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]); sort(b + 1, b + n + 1);
		sort(a + 1, a + n + 1, [](const node &p, const node &q) { return p.x < q.x; });
		for (int i = 1; i <= m; i++) if (b[i] >= a[n - m + i].x) { f = 1; break; }
		for (int i = m + 1; i <= n; i++) if (b[i] < a[i - m].x) { f = 1; break; }
		if (f) puts("NO");
		else {
			puts("Yes");
			for (int i = 1; i <= m; i++) ans[a[n - m + i].id] = b[i];
			for (int i = m + 1; i <= n; i++) ans[a[i - m].id] = b[i];
			for (int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
		}
	}
}
```

---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1896C)。

给出两个长度均为 $n$ 的数列 $\{a_n\},\{b_n\}$，和一个整数 $x$，你需要找出数列 $ \{b_n\}$ 的一种排列方式，使得 $a_i>b_i$ 恰好有 $x$ 个。

$n\le 2\times 10^5$，$0\le x \le n$，$a_i,b_i \le 2\times n$。

### 题目类型

数学，构造，排序。

### 解题思路

可以先对两个数列进行从小到大排序，将前 $x$ 大的 $a_i$ 和前 $x$ 小的 $b_i$ 匹配，剩下的按照顺序匹配即可，之后遍历一遍，如果 $a_i>b_i$ 不是 $x$ 个，就输出 NO。

因为要将数列 $\{b_n\}$ 输出，需要用到复位操作，可以借助结构体完成。

### code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, n, ans, a, x, arr[300100];
struct lint
{
	ll a, b, id;
} num[500100];
bool cmp(lint q, lint w)
{
	return q.a < w.a;
}
bool cmp1(lint q, lint w) // 复位用的排序规则
{
	return q.id < w.id;
}
void solve()
{
	cin >> n >> x;
	for (int i = 0; i < n; i++)
	{
		cin >> num[i].a;
		num[i].id = i; // 记录位置，复位用到
	}
	for (int i = 0; i < n; i++)
		cin >> arr[i]; // 单独存b数列
	sort(arr, arr + n);
	sort(num, num + n, cmp);
	ans = 1;
	int j = n - x;
	for (int i = 0; i < x; i++, j++)
	{
		num[j].b = arr[i]; // 按位匹配
		if (num[j].a <= arr[i])
		{
			ans = 0;
			break;
		}
	}
	if (ans == 0)
		cout << "NO\n";
	else
	{
		for (int i = x; i < n; j++, i++)
			num[j % n].b = arr[i];	// 继续匹配
		for (int i = 0; i < n; i++) // 检查
			if (num[i].a > num[i].b)
				x--;
		if (x != 0)
		{
			cout << "NO\n";
			return;
		}
		sort(num, num + n, cmp1);
		cout << "YES\n";
		for (int i = 0; i < n; i++)
			cout << num[i].b << " ";
		cout << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：AKPC (赞：0)

VP 赛签到题，显然需要贪心策略：

先给 $a$ 和 $b$ 数组从小到大排序，然后选择 $b$ 数组前 $x$ 小匹配 $a$ 数组前 $x$ 大，即 $b_1,b_2,\dots,b_x$ 以及 $a_{n-x+1},a_{n-x+2},\dots,a_n$，其中对于任意整数 $i\in[1,x]$，让 $b_i$ 匹配 $a_{n-x+i}$，易证这样是最优的。对于任意整数 $i\in[1,x]$，如果 $b_i\geq a_{n-x+i}$，则说明再怎么排序也没用了。

$a,b$ 剩下的元素按照类似的匹配方式和判断无解方式处理即可，最后在 $a$ 中存储排序前每个元素对应位置方便最后输出 $b$ 数组。

[code](/paste/rll5riq0)。

---

## 作者：Eazin_star (赞：0)

### 思路
贪心思想，按从小到大的顺序将 $a$ 的前 $x$ 大与 $b$ 的前 $x$ 小放一块，易得一定最优。如果最优都无解，那么一定无解。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

struct JZ { //结构体
	int v, id; //方便后续输出，存一些编号
}a[200005];
int t;
int b[200005], ans[200005];
bool cmp(JZ u, JZ w) {
	return u.v < w.v;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		int n, x;
		scanf("%d %d", &n, &x);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i].v), a[i].id = i;
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
		sort(a+1, a+n+1, cmp);
		sort(b+1, b+n+1);
		bool f = 1; //判断最优是否符合
		for (int i = x+1; i <= n; i++) {
			if (b[i] < a[i-x].v) {
				f = 0;
				break;
			}
		}
		for (int i = 1; i <= x; i++) {
			if (b[i] >= a[n-x+i].v) {
				f = 0;
				break;
			}
		}
		if (!f) printf("NO\n"); //不符合
		else {
			printf("YES\n"); //符合的话就输出
			for (int i = 1; i <= x; i++) ans[a[n-x+i].id] = b[i];
			for (int i = x+1; i <= n; i++) ans[a[i-x].id] = b[i];
			for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
			putchar('\n');
		}
		
	}	
	return 0;
}
```


---

## 作者：Jorisy (赞：0)

我们考虑对 $a$ 升序排序，此时 $a_i$ 的排名就是 $i$。

我们首先考虑 $a,b$ 是 $1\sim n$ 的排列的情况。当 $x=0$ 时，容易想到 $b=\{1,2,\cdots,n\}$；当 $x=1$ 时，我们考虑给 $b$ 向左“滚动”一格，也就是 $b=\{2,3,\cdots,n,1\}$。以此类推，当 $x=p$ 时，$b=\{p+1,p+2,\cdots,n,1,2,\cdots,p\}$。

非排列的情况同理，只要对 $b$ 排序，然后对应填入，最后验证一下即可。如果验证错误，那么就是无解。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

pair<int,int>a[200005],c[200005];
int n,k,b[200005];

void sol()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].first;
		a[i].second=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int t=1;
	for(int i=n-k+1;i<=n;i++) c[i]={a[i].second,b[t++]},swap(a[i].first,a[i].second);
	for(int i=1;i<=n-k;i++) c[i]={a[i].second,b[t++]},swap(a[i].first,a[i].second);
	sort(a+1,a+n+1);
	sort(c+1,c+n+1);
	int s=0;
	for(int i=1;i<=n;i++) s+=a[i].second>c[i].second;
	//cout<<"D ";for(int i=1;i<=n;i++) cout<<c[i].second<<' ';
	if(s!=k)
	{
		puts("NO");
		return;
	}
	puts("YES");
	for(int i=1;i<=n;i++) cout<<c[i].second<<' ';
	puts(""); 
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol(); 
 	return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析

给定两个数组 $a$ 和 $b$，求重排列 $b$ 数组使得只存在 $x$ 个 $i$ 满足 $a_i \gt b_i$。

我们考虑一种贪心的策略，因为要有 $x$ 个 $a_i \ge b_i$，所以我们把前 $x$ 大的 $a_i$ 全部拿出来，依次和前 $x$ 小的 $b_i$ 对应。剩下的从大到小依次对应即可，注意如果其中有任意一组不符合条件就不可能构造，因为我们的构造已经是最贪心的，这样还不行就不可能行了。

注意 $a$ 数组排序后要按照原来顺序输出，赛时因为这个吃了俩罚时。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;

int b[N],ans[N];

struct node{
	int val;
	int id;
}a[N];

inline void fake_main(){
	int n,x; cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i].val; a[i].id=i;
	}
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1,[](node x,node y){
		return x.val<y.val;
	}); sort(b+1,b+n+1);
	for(int i=n;i>=n-x+1;i--){//前 x 项都要保证 a>b，如果有任意一个 b>=a 就不符合条件，注意是较大的匹配较大的，较小的匹配较小的。
		ans[a[i].id]=b[i-n+x];
		if(b[i-n+x]>=a[i].val){
			cout<<"NO\n"; return;
		}
	}
	for(int i=n-x;i>=1;i--){//剩下的都要让 b>=a，如果不满足也是直接输出 NO
		ans[a[i].id]=b[i+x];
		if(b[i+x]<a[i].val){
			cout<<"NO\n"; return;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" "; cout<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}
```

---

