# Multicolored Cars

## 题目描述

定义$cnt_{x}(i)$表示到$i$时刻$x$出现过的个数。

现在给出$n$个数$a_{1},a_{2}……a_{n}$,$a_{i}$表示时刻$i$出现的数。$Alice$选择了一个数$m$，请帮助$Bob$选择一个数$k$，使得对任意时刻$i$，都有$cnt_{k}(i)>=cnt_{m}(i)$。若不存在这样的$k$请输出$-1$。

## 说明/提示

所有数不超过$10^6$

## 样例 #1

### 输入

```
4 1
2 1 4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2
2 2 4 5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 10
1 2 3
```

### 输出

```
4
```

# 题解

## 作者：墨舞灵纯 (赞：5)

习惯性地写了翻译就来写题解。

看到网上一堆线段树的题解，我觉得很奇怪，这题跟线段树似乎没任何关系。

显然我们记录当前时刻$m$的个数为$now$，如果某个$x$出现在$m$的后面，而且$cnt_{x}$<$now$，说明$x$不合法，那就没必要累加了，如果$x$在这之前都是合法的，我们就累加一次。

$\mathcal\textcolor{SpringGreen}{Code:}$

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000005;
int maxn,a[N],m,n,x,now; 
int main()
{
	scanf("%d%d",&n,&m);
	while(n--)
	{
		scanf("%d",&x);
		maxn=max(x,maxn);
		if(x==m) 
			++now;
		else
			if(a[x]>=now) 
				++a[x];
	}
	for(int i=1;i<=maxn;++i)
		if(a[i]>=now&&i!=m)
		{
			printf("%d",i);
			return 0;
		}
	printf("-1");
	return 0;
}

```

---

## 作者：ARIS2_0 (赞：2)

### 思路

我们有一个非常暴力的 `set` 做法。

我们开 $n+1$ 个 `set`，其中第 $i$ 个 `set` 存放出现了 $i$ 次的数字（不包括 $m$，下标从 $0$ 开始）。初始时将 $1$ 到 $10^6$ 中的所有数放入第 $0$ 个 `set` 中。同时，定义 $f_i$ 为第 $i$ 个数出现的次数。

接着，遍历数列 $a$：

- 如果 $a_i\not=m \land f_i\not=-1$，将 $a_i$ 从第 $f_i$ 个 `set` 中删除，加入到第 $f_i+1$ 个 `set` 中，更新 $f_i$；

- 如果 $a_i=m$，将第 $f_m$ 个 `set` 中所有 $x$ 的 $f_x$ 设为 $-1$，清空这个 `set`（显然这个 `set` 里的数不可能是答案了），更新 $f_m$。

- 否则 $a_i$ 不可能是答案，直接跳过即可。

最后，检查第 $f_m$ 个 `set` 到第 $n$ 个 `set` 中有没有数即可。

时间复杂度 $O(A\log A)$，其中 $A=10^6$。离散化后可以做到 $O(n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10,maxa=1e6+10;
set<int>s[maxn];
int f[maxa];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
    for(int i=1;i<=1e6;i++){
        if(i!=m)s[0].insert(i);
    }
    for(int i=1;i<=n;i++){
        int pos;cin>>pos;
        if(pos!=m){
            if(f[pos]==-1)continue;
            s[f[pos]].erase(pos);
            f[pos]++;
            s[f[pos]].insert(pos);
        }
        else{
            for(int res:s[f[m]])f[res]=-1;
            s[f[m]].clear();
            f[m]++;
        }
    }
    for(int i=f[m];i<=n;i++){
        if(s[i].size()){
            cout<<(*s[i].begin());
            return 0;
        }
    }
    cout<<-1;
	return 0;
}
```

---

## 作者：wuyixiang (赞：2)

很简单的一道题。

这道题暴力的复杂度是会超时的。但是在比较的过程中所有出现的数其实只变了 $n$ 次，所以说暴力其实很多都是在做重复运算的。那么有没有更好的方法呢？

考虑到只有数变的时候才会有影响，所以我们就用变的数和 $m$ 做比较。如果这个变的数加上一之后还是不大于 $m$ 出现的次数，就说明之前肯定不符合要求了，直接标记。

有没有漏网之鱼呢？这个很简单，当一个数已经不符合条件且一直没变动时，它最后的结果肯定也小于 $m$ 出现的次数。所以最后再判断一下 $10^6$ 个数即可。注意 $a_i$ 的大小可以到 $10^6$。

代码：

```cpp
#include <iostream>
using namespace std;
int cnt[1000005],a[1000005],m,n;
int main()
{
    cin >> n >> m;
    for(int i = 1,x;i <= n;i ++)
    {
        cin >> x;
        cnt[x] ++;
        if(cnt[x] <= cnt[m])a[x] = 1;
    }
    for(int i = 1;i <= 1e6;i ++)
        if(i != m && !a[i] && cnt[i] >= cnt[m])
        {
            cout << i;
            return 0;
        }
    cout << -1;
}
```

---

## 作者：gcx114514 (赞：1)

做这道题本来是想练习一下数据结构的，一看题解全是模拟，我提供一种**平衡树**做法。

## 解题思路：

观察题目可知要让我们找一个任意位置出现次数都大于等于 $m$ 的数，我们可以发现这种数一定在 $m$ 第一次出现前出现过。而对于数的筛选只会在 $m$ 出现时筛除。

那么我们可以将在 $m$ 第一次出现前出现过的数扔进一棵平衡树（本文使用 FHQ-Treap ）中并对其打标记，在树上我们记录其出现次数 $val(x)$ 以及对应在原序列中的值 $ans(x)$。

然后遍历输入序列，如果 $a_i$ 打过标记，那么我们就更改树中 $ans$ 为 $a_i$ 的点的 $val$ 将其加一。

当序列中数为 $m$ 时，按照 $val$ 将树分裂成 $val$ 小与 $m$ 出现次数 $cnt_i(m)$ 的和大于等于 $cnt_i(m)$ 的两棵树，将权值打的树保留，小的树删除。由于如果数此处以及不满足条件了，那么以后一定不会满足，那么就将删除的树上的点的 $ans$ 对应的标记清零，防止以后再次加入树。

最后如果树不为空，那么树中任意点的 $ans$ 都是一个合法答案，若树为空，那么无解。

## code :

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Max=4e5+10;
const int M=1e6+10;
int vis[M];
int a[Max],dis[M],zis[M];
struct FHQ{
	int root,pos;
	struct tree{
		int ch[2],val,p,ans;
		#define ch(x,i) tr[x].ch[i]
		#define val(x) tr[x].val
		#define ans(x) tr[x].ans
		#define p(x) tr[x].p
	}tr[Max];
	
	void split(int now,int v,int &x,int &y){
		if(!now){
			x=0;
			y=0;
			return;
		}
		if(val(now)<=v){
			x=now;
			split(ch(x,1),v,ch(x,1),y);
		}else{
			y=now;
			split(ch(y,0),v,x,ch(y,0));
		}
	}
	
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(p(x)<p(y)){
			ch(x,1)=merge(ch(x,1),y);
			return x;
		}else{
			ch(y,0)=merge(x,ch(y,0));
			return y;
		}
	}

	int buildnode(int x){
		int k=++pos;
		val(k)=vis[x];
		ans(k)=x;
		p(k)=rand();
		ch(k,0)=ch(k,1)=0;
		return k;
	}
	
	void insert(int x){
		int xx,yy;
		split(root,vis[x],xx,yy);
		root=merge(merge(xx,buildnode(x)),yy);
	}
	
	void dfs(int now){
		dis[ans(now)]--;
		if(ch(now,1))dfs(ch(now,1));
		if(ch(now,0))dfs(ch(now,0));
	}
	 
	
	void del(int v){
		int xx=0;
		split(root,v-1,xx,root);
		dfs(xx);               //将不满足条件的点的标记清空，以防再次加入 
	}
}tre;

//以上为平衡树模板 

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int z=n;
	int bol=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(!bol&&a[i]!=m){vis[a[i]]++;tre.insert(a[i]);dis[a[i]]++;}   //筛选出在 m 第一次出现前出现的，扔进平衡树 
		if(a[i]==m)z=i;
		if(!bol&&a[i]==m)bol=i;
	}
	for(int i=bol;i<=z;++i){
		vis[a[i]]++;
		if(a[i]!=m&&dis[a[i]]){		     //必须有标记才能进树 
			tre.insert(a[i]);dis[a[i]]++;
		}else{
			if(a[i]==m)tre.del(vis[m]);   //筛选不合适的 
		}
	}
	if(tre.root){              //最后输出树中任意一点即可 
		printf("%d\n",tre.ans(tre.root)); 
		return 0;
	}
	printf("-1\n"); 
	return 0;
}
```



---

## 作者：ZLCT (赞：0)

# CF818D Multicolored Cars
## 题目翻译
给定一个长度为 $n$ 的序列 $a$ 和一个颜色 $k$，定义 $sum_{i,j}$ 表示颜色 $i$ 在 $[1,j]$ 之间出现的次数。求一个颜色 $c$ 满足 $\forall i$ $sum_{c,i}\ge sum_{k,i}$。如果不存在则输出 $-1$。
## 标签 `data structures`？
这个题当然有神奇数据结构的写法，具体来说就是定义 $val_i$ 表示第 $i$ 种颜色出现次数。用线段树记录每种颜色出现的次数，每读入一个元素就更新一遍，当读到 $k$ 时就把线段树上小于 $val_k$ 的点标记（这里可以线段树二分），最后没有被标记的点就是可行的。\
（代码暂时不放了，这种做法唯一的好处就是锻炼码力）
## 正常的解法
其实线段树解法的大致思路是比较顺势而为的。\
我们首先暴力地考虑如果要满足题目条件，就是每进入一个元素更新一次，当读到 $k$ 时把小于 $val_k$ 的点标记。\
但是这样复杂度就是一个满满当当的 $O(n^2)$。\
于是下面就出现了两种流派：
1. 我们每次标记如果只把需要的标记，这样一共不就只需要标记 $n$ 次了吗？
2. 每次既然都只加入一个元素，我们为什么不把比较先欠着，下次它出现的时候再比较？

第一种流派于是就有人想出来线段树二分，但是仔细想想就发现其实本质上是平衡树啊：以 $val_i$ 作为比较值，每次读到 $k$，就把 $k$ 的左子树删去。\
这不是更麻烦了吗？确实如果你要写平衡树会更麻烦，但是众所周知在很多情况下 STL 就是我们~~懒人~~自己的平衡树。\
这个题完全可以拿 set 重载运算符，模拟平衡树加点删点的过程。
### 不熟悉 set？第二种流派来咯
因为只有加入一个元素才会对它产生影响，所以我们每次比较都可以欠着，直到下次加入该元素。需要注意的是最后有些元素还是欠着没比较，所以最后我们全部再比较一遍就行了。
### 题不在难，掌握为精；码不在多，能过就行。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[112345],cnt[1123456],sumk,maxcol;
bool vis[1123456];
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        maxcol=max(maxcol,a[i]);
        if(k==a[i])sumk++;
        else{
            if(cnt[a[i]]<sumk)vis[a[i]]=1;
            else cnt[a[i]]++;
        }
    }
    for(int i=1;i<=maxcol+1;++i){//防止n=0
        if(!vis[i]&&cnt[i]>=sumk&&k!=i){
            cout<<i<<'\n';
            return 0;
        }
    }
    cout<<-1<<'\n';
    return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF818D)

题目翻译很清楚，故不再重叙。

我们用 $cnt$ 记录 $m$ 的数量，维护一个桶 $num$，$num_i$ 表示第 $i$ 个数的个数。
	
边读入边处理，输入 $x$，若 $x=m$ 则加 $cnt$，否则如果 $num_x \ge cnt$，这个 $x$ 合法，$x$ 的个数加 $1$。

AC 代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1145141];
int num[1145141];
int cnt,k,maxn;
int main(){
	memset(num,0,sizeof(num));
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		maxn=max(maxn,a[i]);
		if(a[i]==m)cnt++;
		else if(num[a[i]]>=cnt)num[a[i]]++;
		//已经不符合的直接筛掉了
	}
	for(int i=1;i<=maxn;i++)
	{
		//如果连maxn 都不行就更不行了
		if(num[i]>=cnt&&i!=m)
		{
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：liaoz123 (赞：0)

模拟。

明显若一个数 $k$ 满足条件，则必须在任意时刻出现次数都不小于 $m$，那么我们可以在输入的时候边判断，只对当前出现次数大于 $m$ 出现次数的数计数，就相当于自动排除了不合法的答案。答案就是值域内任意一个出现次数不小于 $m$ 出现次数的数。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,cnt[N],num,fla;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		if(x==m)num++;
		else if(cnt[x]>=num)
		cnt[x]++;
	}
	for(int i=1;i<N;i++)
	if(cnt[i]>=num&&i!=m){
		cout<<i<<endl;fla=1;
		break;
	}
	if(!fla)cout<<"-1"<<endl;
	return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

定义 $cnt_x(i)$ 表示到 $i$ 时刻 $x$ 出现过的个数。

现在给出 $n$ 个数 $a_1,a_2,\cdots,a_n$，$a_i$ 表示时刻 $i$ 出现的数。Alice 选择了一个数 $m$，请帮助 Bob 选择一个数 $k$，使得对任意时刻 $i$，都有 $cnt_k(i)\ge cnt_m(i)$。若不存在这样的 $k$ 请输出 -1。

## 思路1

令 $count_x$ 表示 $x$ 实时出现次数。

根据输入做，如果输入的是 $m$，那么直接把 $count_m$ 加一。如果输入的是其它的数 $i$，先检查 $count_i\ge count_m$，如果成立，$count_i$ 加一，否则 `bool` 数组标记为不能取这个数。

注意最后输出答案时，要判断那个数 $i$ 最终是否 $count_i>count_m$，因为有时候这个数最后没有出现，因此没有被检查到。

## 代码1

根据思路，代码就很简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt[1000005];
bool b[1000005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=1e6;i++)b[i]=(i!=m);
	//注意初始化，不能与Alice选的数相同！
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x==m)cnt[m]++;
		else{
			if(cnt[x]>=cnt[m])cnt[x]++;
			else b[x]=0;
		}
	}
	for(int i=1;i<=1e6;i++){
		if(b[i]&&cnt[i]>=cnt[m]){//注意判断最后是否仍大于或等于
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```


## 思路2

和上一个思路较为类似，依然还是模拟。

令 $count_x$ 表示 $x$ 实时出现次数。一开始答案为除 $m$ 以外的任意 $x \in [1,10^6]$。

根据输入做，如果输入的是 $m$，那么 $count_m$ 加一。然后检查没有被去除的数中，对于 $count_i<count_m$，将它们删去。如果输入的是其它的数 $i$，那么直接把 $count_i$ 加一。

可以用一个 `multimap` 做 $count$ 到 $x$ 的一个映射。最后直接找未被删除的输出即可。

这里就不放代码了，请读者自行尝试一下。

---

## 作者：_HMZ_ (赞：0)

## 解题思路：

有个奇怪的做法。

一开始尝试正向想，给定选的数后有多少个会被淘汰，全部淘汰之后哪些是可行的。

想了一会不太行，发现值域比较小（其实值域比较大也能离散化），于是我们反向考虑，对于 $i$ ，是否可行。

如何判断可行呢？假设当前选定的是 $i$，如果在第 $j$ 个位置出现了 $i$，则离 $j$ 最近的，位置大于 $j$，且值是 $m$ 的就无效了。

因为这题要求任意位置 $cnt_i$ 都大于 $cnt_m$，所以每出现一次 $i$，就能抵消一次 $m$。

还有一个小优化，如果到最后 $cnt_i$ 还是小于 $cnt_m$，那么至少在 $n$ 这个位置是不满足条件的，于是直接跳过就好了。

## AC代码：

```cpp
#include<iostream>
#include<vector>
#include<set>
using namespace std;
int n,m,val[1000005],del[1000005],cnt;
vector<int> e[1000005];
set<int> beg;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>val[i];
		if(val[i]==m)
			beg.insert(i);//我们用set存下给定颜色的位置。
		else
			e[val[i]].push_back(i);//用一个vector存下所有值为i的位置。
	}
	for(int i=1;i<=1e6;i++)
	{
		if(i==m || e[i].size()<beg.size())	continue;//小优化
		cnt=0;
		for(int j=0;j<e[i].size();j++)
		{
			set<int>::iterator it=beg.lower_bound(e[i][j]);
			if(it!=beg.end())
				beg.erase(it),del[++cnt]=(*it);
		}
		if(beg.empty())//删除空了代表当前枚举的 i 可行。
		{
			cout<<i;
			return 0;
		}
		for(int j=1;j<=cnt;j++)//set复制有点慢，只能删除几个放进去几个。
			beg.insert(del[j]);
	}
	cout<<-1;
	return 0;
}
```




---

