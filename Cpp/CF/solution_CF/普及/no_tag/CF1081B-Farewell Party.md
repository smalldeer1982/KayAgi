# Farewell Party

## 题目描述

Chouti and his classmates are going to the university soon. To say goodbye to each other, the class has planned a big farewell party in which classmates, teachers and parents sang and danced.

Chouti remembered that $ n $ persons took part in that party. To make the party funnier, each person wore one hat among $ n $ kinds of weird hats numbered $ 1, 2, \ldots n $ . It is possible that several persons wore hats of the same kind. Some kinds of hats can remain unclaimed by anyone.

After the party, the $ i $ -th person said that there were $ a_i $ persons wearing a hat differing from his own.

It has been some days, so Chouti forgot all about others' hats, but he is curious about that. Let $ b_i $ be the number of hat type the $ i $ -th person was wearing, Chouti wants you to find any possible $ b_1, b_2, \ldots, b_n $ that doesn't contradict with any person's statement. Because some persons might have a poor memory, there could be no solution at all.

## 说明/提示

In the answer to the first example, all hats are the same, so every person will say that there were no persons wearing a hat different from kind $ 1 $ .

In the answer to the second example, the first and the second person wore the hat with type $ 1 $ and all other wore a hat of type $ 2 $ .

So the first two persons will say there were three persons with hats differing from their own. Similarly, three last persons will say there were two persons wearing a hat different from their own.

In the third example, it can be shown that no solution exists.

In the first and the second example, other possible configurations are possible.

## 样例 #1

### 输入

```
3
0 0 0
```

### 输出

```
Possible
1 1 1 ```

## 样例 #2

### 输入

```
5
3 3 2 2 2
```

### 输出

```
Possible
1 1 2 2 2 ```

## 样例 #3

### 输入

```
4
0 1 2 3
```

### 输出

```
Impossible
```

# 题解

## 作者：Laolizi (赞：11)

题意比较简单 , 做法也不难 。

对于 $x$ 个不同的帽子的种类，定有 $n$ $-$ $x$ 个人与其相同种类。

举个例子：

```
6

3 3 3 4 4 5

```

对于这个样例：

把 $x$ 值相同的人设为同样的种类即可。

但是

```
6

3 3 3 3 3 3

```

对于这个样例：

显然 $x$ 设为同样的种类并不对，这时应当设 $y$ 为 $a_i$ 去除具有相同 $x$ 值的人的个数。

再将这些人平均分给 $y$ 个不同的种类。

最后可以再给答案一个小小的优化。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,ans[100005];
int vis[100005],pot[100005],h,t;

struct node {
	int value,num;
} a[100005];

bool cmp(node b,node c){
	return b.value<c.value;
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i].value);
		a[i].value=n-a[i].value;
		vis[a[i].value]=1;
		a[i].num=i;
		ans[i]=a[i].value;
	}
	for(int i=1; i<=n; ++i) if(!vis[i]) pot[++t]=i;
	sort(a+1,a+n+1,cmp);
	int m=1; 
	while(m<=n){
		int cnt=0,now=m-1;
		while(a[m+cnt].value==a[m].value) ++cnt;
		if(cnt%a[m].value) puts("Impossible"),exit(0);
		for(int j=1; j<(cnt/a[m].value); ++j) {
			now+=a[m].value,++h;
			for(int k=1; k<=a[m].value; ++k) ans[a[now+k].num]=pot[h];
		}
		m+=cnt;
	}
	puts("Possible");
	int minn=0x3f3f3f;
	for(int i=1; i<=n; ++i) minn=min(ans[i],minn);
	for(int i=1; i<=n; ++i) printf("%d ",ans[i]-minn+1);
}
```

---

## 作者：lzyqwq (赞：3)

**[CF](https://codeforces.com/problemset/problem/1081/B) [洛谷](https://www.luogu.com.cn/problem/CF1081B)**

我们注意到，若 $a_i$ 个人的帽子和 $i$ 不同，则有 $n-a_i-1$ 个人的帽子和他相同（不算自己），这种颜色的帽子有 $n-a_i$ 个人戴，称帽子颜色相同的人为一组。

若两个人帽子的颜色相同，则帽子和他们不同的人数是一样的。

因此将所有人放进下标为 $n-a_i$ 的容器里，每次从下标为 $k$ 的容器里选 $k$ 个人出来作为一组，给他们同一种**独一无二颜色**，这样保证这些人以外的人的帽子颜色和他们都不同。

若选不出来则无解，因为我要满足有 $k$ 个人戴这种颜色的帽子，即不能把他们放到别的已经好的组里去（破坏了别的组的合法性），又不能让其他组的人过来（同理），也不能让 $k$ 不相同的人过来（破坏了 $k$ 不相同的人的合法性），还不能把他们放到 $k$ 不相同的人的组里去（同理）。就无法操作了。

然后就做完了，时间、空间复杂度均为 $\mathcal{O}(n)$。

**[代码](https://codeforces.com/problemset/problem/1081/B)**

---

## 作者：da32s1da (赞：1)

一个明显的思路：有$x$个人与ta颜色不同，说明有$n-x$个人与ta颜色相同。很自然想到把$x$相同的人颜色设为一样的。

但是这是错的。比如数据
```
4
2 2 2 2
```
两个人颜色是$1$，两个人颜色是$2$

对这种情况进行调整，设成不同的颜色即可。

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+50;
int n,Ans[N];
int vis[N],zn[N],h,t;
struct node{
	int col,id;
	bool operator <(const node &o)const{
		if(col!=o.col)return col<o.col;
		return id<o.id;
	}
}a[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].col);
		a[i].col=n-a[i].col;
        //有n-x个人与ta颜色一样
		vis[a[i].col]=1;
		a[i].id=i;
		Ans[i]=a[i].col;
	}
	for(int i=1;i<=n;i++)
	if(!vis[i])zn[++t]=i;//记录没用过的颜色
	sort(a+1,a+n+1);
	for(int i=1;i<=n;){
		int gs=0,now=i-1;
		while(a[i+gs].col==a[i].col)++gs;
        //有多少人x相同
		if(gs%a[i].col){//判无解
			puts("Impossible");
			return 0;
		}
		for(int j=1;j<(gs/a[i].col);j++){
			now+=a[i].col;++h;
			for(int k=1;k<=a[i].col;k++)
			Ans[a[now+k].id]=zn[h];
            //调整颜色
		}
		i+=gs;
	}
	puts("Possible");
	for(int i=1;i<=n;i++)printf("%d ",Ans[i]);
}
```

---

## 作者：Loser_Syx (赞：0)

发现 $a_i$ 个人与其颜色不同可以转化为 $n-a_i$ 个人与其颜色相同，故可以直接对每个 $n-a_i$ 统计有哪些人。

然后对每一种 $n-a_i$，将其分为若干组 $n-a_i$ 个 $a_i$，每组染个不同颜色即可。  
这样直接保证了 $n-a_i$ 个与其颜色相同，如果不能均分则是无解。

```cpp
signed main() {
	int n = read();
	vector<vector<int> > mp(n+1, vector<int>());
	for (int i = 0; i < n; ++i) {
		int x = read();
		mp[n - x].emplace_back(i);
	}
	vector<int> ans(n);
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (mp[i].size() % i) return puts("Impossible"), 0;
		while (mp[i].size()) {
			++cnt;
			for (int j = 1; j <= i; ++j) {
				ans[mp[i].back()] = cnt;
				mp[i].pop_back();
			}
		}
	}
	puts("Possible");
	for (auto i : ans) write(i, ' ');
	return 0;
} 
```

---

## 作者：Maysoul (赞：0)

## 简述思路：

题目中给出了 $a_{i}$ 代表有 $a_{i}$ 个人所戴的帽子与此人不同，也就是告诉了我们对于每个人有 $n-a_{i}$ 个人和自己是同一顶帽子（含自己）。

那么戴着同一顶帽子的人，和他们戴同一顶帽子的人数一定是一样的，所以我们可以开一个桶，把所有相同的 $n-a_{i}$ 处理下来。

现在我们按照值域将他们分为了 $n$ 组，对于每一组我们还需要继续分组，因为如果有人认为 $x$ 个人和自己戴着同一顶帽子，那么和这个人戴同一顶帽子的一共有 $x-1$ 个。

所以在每一组 $i$ 中，我们将 $i$ 个人分为一组，共有 $\frac{tot_{i}}{i} $ 组。如果不能分配，那么一定无解。而且其中每一组戴着同一顶帽子。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num=1,ans[MAXN],tot[MAXN];
vector<vector<int>> id;
//如果存在失配可能，当且仅当存在一个组人数不够 
int main()
{
	int n,a;
	cin>>n;
	id.resize(n+1);
	for (int i=1;i<=n;i++){
		cin>>a;
		int b=n-a;
		tot[b]++;
		id[b].push_back(i);
	}
	for (int i=1;i<=n;i++){
		if(tot[i]%i!=0){
			cout<<"Impossible"<<endl;
			return 0;
		}
		int k=i,cnt=0;
		for (int j:id[i]){
			ans[j]=num;
			cnt++;
			if(cnt==k){
				cnt=0;
				num++;
			}
		}
	}
	cout<<"Possible"<<endl;
	for (int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```


---

## 作者：Wander_E (赞：0)

这题本质上其实不过是模拟。

第 $i$ 个人有 $a_i$ 个人和他不同相当于有 $n-a_i$ 个人与其相同。

如果 $a_j=a_i$ 且与 $i$ 帽子颜色相同的人不超过 $n-a_i$ 那么就将第 $j$ 个人的帽子染成与第 $i$ 个人帽子相同的颜色。

如果每种帽子颜色所对应的人数之和 $>n$ 或者有某种颜色的帽子小于该颜色帽子的人数需求（换句话说，如果设与第 $i$ 个人同色的帽子数为 $cnt$，那么 $cnt\mid n-a_i$），那么就输出 $-1$。

这题细节较多，一定要考虑好逻辑再写，重点注意染色部分的处理。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
int a[N];
int sum = 0;
bool flag = 1;
map <int, int> mp, id;
int cur = 0;
int ans[N], cnt = 0;
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		if(!mp[n - a[i]]) 
			sum += (n - a[i]);
		mp[n - a[i]] = 1;
		if(a[i] != a[1]) flag = 0;
	}
	mp.clear();
	if(sum > n)
	{
		cout << "Impossible\n";
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		if(!mp[a[i]] || !id[a[i]])
		{
			id[a[i]] = ++cur;
			ans[++cnt] = id[a[i]];
			mp[a[i]] = (n - a[i] - 1);
		}
		else ans[++cnt] = id[a[i]], --mp[a[i]];
	}
	for(auto it: mp)
	{
		if(it.second)
		{
			cout << "Impossible\n";
			return 0;
		}
	}
	cout << "Possible\n";
	for(int i = 1; i <= cnt; i++)
		cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：DANIEL_x_ (赞：0)

## 思路
让 $b_i = n - a_i$ 代表第 $i$ 个人戴相同类型的帽子的人数。

实际上，戴相同类型帽子的人必须有相同的 $b$。假设具有相同  $b_i$ 的人数是 $t$，则正好有多种帽子有 $b_i$ 的佩戴者。因此，$t$ 一定是 $b_i$ 的倍数。反之，也是正确的。

## code
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int maxn = 100010;
int n,ans[maxn],cnt;
pair<int,int> a[maxn];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].fi,a[i].first=n-a[i].fi,a[i].se=i;
    sort(a+1,a+n+1);
    for(int l=1,r=0;l<=n;l=r+1){
        for(r=l;r<n&&a[r+1].fi==a[r].fi;++r);
        if((r-l+1)%a[l].fi){
            cout<<"Impossible"<<endl;
            return 0;
        }
        for(int i=l;i<=r;i+=a[l].fi){
            cnt++;
            for(int j=i;j<i+a[l].fi;++j)ans[a[j].se]=cnt;
        }
    }
    cout<<"Possible"<<endl;
    for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```


---

