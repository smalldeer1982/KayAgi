# [CERC2015] Kernel Knights

## 题目描述

马上长矛比武是一种中世纪的比赛，参赛者骑在马上，用木制长矛高速冲刺，试图击中对方。共有 2n 名骑士参加了马上长矛比武比赛——来自两个伟大敌对家族的 n 名骑士。到达后，每位骑士向另一家族的一名骑士发起了挑战。

一个“核”被定义为骑士的某个子集 S，具有以下两个特性：

- S 中没有骑士被 S 中的其他骑士挑战。
- 不在 S 中的每个骑士都被 S 中的某个骑士挑战。

给定发出的挑战集，找到一个“核”。保证“核”总是存在。

## 说明/提示

Central Europe Regional Contest 2015 Problem K。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 
5 6 7 7 
1 3 2 3```

### 输出

```
1 2 4 8```

# 题解

## 作者：TsH_GD (赞：6)

### 此题的第一篇题解（也是我的第一篇题解）

[题链](https://www.luogu.com.cn/problem/P4355)

## 分析

没人攻击的骑士一定在 $\rm kernel$ 里，把没人攻击的加入队列，然后被他攻击的骑士一定在 $\rm kernel$ 外。

$\rm kernel$ 外的骑士的攻击无效，因为如果一个骑士如果只被外面的骑士攻击，他就是 $\rm kernel$ 里的。

于是 被 外面的骑士攻击 的骑士 的被攻击次数 `-1`，如果被攻击次数为 $0$ 了就加入队列。

某个导致我 `WA` 的地方：被攻击次数 `-1` 这个操作不能重复，所以要判断当前这个“外面的骑士”是不是已经处理过。


## code:

```cpp
#include<queue>
#include<cstring>
using namespace std;
const int maxn=2e5+100;
int n,a[maxn],d[maxn],k[maxn];
queue<int> q;

int main()
{
    while(~scanf("%d",&n))
    {
        while(!q.empty()) q.pop();
        memset(d,0,sizeof(d));
        memset(k,0,sizeof(k));
        for(int i=1; i<=2*n; i++)
        {
            scanf("%d",&a[i]);
            d[a[i]]++;
        }
        for(int i=1; i<=2*n; i++)
        {
            if(d[i]==0)q.push(i);
        }
        while(!q.empty())
        {
            int p=q.front();
            q.pop();
            k[p]=1;
            if( k[ a[p] ]==-1  )continue;//没有它而让我WA的地方
            k[a[p]]=-1;
            d[a[a[p]]]--;
            if(d[a[a[p]]]==0)q.push(a[a[p]]);
        }
        for(int i=1; i<=2*n; i++)
        {
            if(i<=n&&k[i]>=0)printf("%d ",i);
            else if(k[i]==1)printf("%d ",i);
        }
        printf("\n");
    }
    return 0;
}
```

qwq，一定要过啊

---

## 作者：floris (赞：2)

$update$：已经修改了错误内容。

这道题对于细节的考虑比较细致。

## 思路

首先，我们可以发现没被攻击的骑士一定是在这个集合中的，于是我们用一个队列维护这些骑士，那么他们攻击的骑士一定不在集合中，那么重点来了：

不在集合中的骑士的进攻是无效的！

所以：这些骑士进攻的骑士有些就可以进入这个集合了。

这就体现了队列维护的好处。

## develop

后面我们发现：单纯用 $vis$ 数组维护是否遍历过会导致一些骑士判断为无法进入集合，但实际上他们是可以的。

这个 $vis$ 数组可以维护两种情况，最后输出也要判断两种情况，只要一种成立就输出。


还是看正解吧。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 10005
int n,a[N],c[N],ans[N];
int vis[N];
queue<int> q;
int main(){
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=2*n;i++){
        cin>>a[i];
        c[a[i]]++;
    }
    for(int i=1;i<=2*n;i++){
        if(c[i]==0) q.push(i); //第一遍判断
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=1;
        if(vis[a[u]]==-1) continue; //判断是否已经操作过了
        vis[a[u]]=-1;
        c[a[a[u]]]--;
        if(c[a[a[u]]]==0) q.push(a[a[u]]); //被攻击为0就入队
    }
    for(int i=1;i<=2*n;i++){
        if(i<=n&&vis[i]>=0) cout<<i<<" ";
        else if(vis[i]==1) cout<<i<<" "; //两种情况判断
    }
    return 0;
}
```

这个题目好像不用多测不知道为什么其他题解写了多测。

---

## 作者：2021changqing52 (赞：2)

# 思路：
- 思路来自题解。
1. 没有被攻击的骑士一定在这个内核当中。
1. 在做完步骤 $1$ 之后，集合外的骑士如果没有被集合内的任何骑士攻击，就将其加入内核。
1. 由于步骤 $2$ 还要将其加入内核，所以用上一个**队列**维护比较方便（用数组模拟也行）。

注意已经处理过的骑士**不用再处理**（第一篇题解已经提醒过了，不注意会 WA）。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],d[N],k[N];
queue<int>q;
int main(){
    while(cin>>n){
        memset(d,0,sizeof(d));//重置
        memset(k,0,sizeof(k));
        for(int i=1;i<=2*n;i++){
            scanf("%d",&a[i]);
            d[a[i]]++;//次数加一
        }
        for(int i=1;i<=2*n;i++)if(!d[i])q.push(i);//没人攻击的人在内核中
        while(!q.empty()){
            int p=q.front();q.pop();k[p]=1;
            if(!~k[a[p]])continue;//处理过就不用再处理了
            k[a[p]]=-1;d[a[a[p]]]--;//外面的骑士可以看成攻击无效
            if(d[a[a[p]]]==0)q.push(a[a[p]]);//没人攻击的人在内核中
        }
        for(int i=1;i<=2*n;i++)
        if(i<=n&&k[i]>=0||i>n&&k[i]==1)printf("%d ",i);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：ShiZhaoxu_YY202305 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P4355)

**总思路**

根据题意可得：我们所求的核中的骑士之间不互相挑战。

深入分析可得——从始至终未被挑战的骑士一定在核中，被从未被挑战过的骑士所挑战的骑士一定不在核之中。

又一次深入分析可得——而只被核之外骑士所挑战的骑士也可以进入进核中，现在我们已经成功梳理出本题的基本思路了。

**代码元素**

我们需要以下元素：

1. 一个初始数据数组；

2. 一个处理数组记录骑士被挑战的次数（处理被核外骑士所挑战骑士的个数信息）；

3. 一个辅助队列（辅助求解判断数组）与一个判断数组（记录一定在核中的骑士）；

**代码实现**

各功能解释详见代码注释：

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=2e5+10;
int n,a[N],b[N],c[N];//a记录初始数据,b记录骑士被挑战的次数,c记录是否在核中 
queue<int> q;
int main(){
	while(cin>>n){
		while(!q.empty()) q.pop();
		memset(b,0,sizeof(b)); 
		memset(c,0,sizeof(c));
		for(int i=1;i<=2*n;i++){
			scanf("%d",&a[i]);
			b[a[i]]++;
		}
		for(int i=1;i<=2*n;i++) if(!b[i]) q.push(i);//不被其余骑士挑战的骑士一定在核中 
		while(!q.empty()){//只被核外骑士挑战的骑士也在核中 
			int num=q.front();
			q.pop();
			c[num]=1; 
			if(c[a[num]]==-1) continue;
			c[a[num]]=-1;//被核中挑战的骑士一定不在本核中 
			b[a[a[num]]]--;//被核中挑战的骑士所挑战的骑士可能在本核中,因此本次挑战无效 
			if(!b[a[a[num]]]) q.push(a[a[num]]);//如果被挑战次数小于等于0,代表受挑战均为核外的攻击,将其加入核
		}
		for(int i=1;i<=2*n;i++){
			if(i<=n && c[i]>=0) cout<<i<<" ";//未被核中骑士所挑战的骑士也在核中
			else if(c[i]==1) cout<<i<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P4355)

## 思路

题目中说：内核被定义为**骑士**的一些子集，具有以下两个属性

1.$S$ 中**没有**骑士受到 $S$ 中另一个骑士的挑战。

2.**每一个**不在 $S$ 中的骑士都会受到一些S中的骑士的挑战。

---
所以，所有集合内的骑士如果没有被挑战，则加入内核。集合外的骑士如果没有收到集合内的骑士的挑战，也要加入内核。（某个骑士若已处理则不用在处理）。
## Code
```cpp

#include<bits/stdc++.h>
#define int long long 
using namespace std;

int n,a[200005], mp1[200005], mp2[200005];
queue<int> qu;

signed main()
{
	
    while(cin >> n)
	{
    
        memset (mp1 , 0, sizeof(mp1));//清空 
        memset (mp2 , 0, sizeof(mp2));
        while(!qu.empty()) qu.pop();
        
        
        for(int i=1; i<=2*n; ++i)
		{
            cin >> a[i];
            mp1[a[i]]++;
        }
        
        for(int i=1; i<=2*n; ++i) if(mp1[i] == 0) qu.push(i); 
		
        while(!qu.empty())
		{
        	
            int t = qu.front();
            qu.pop();
            
            mp2[t]=1;
            if(mp2[a[t]] == -1) continue;
            
            mp2[a[t]] = -1, mp1[a[a[t]]]--;
            if(mp1[a[a[t]]] == 0) qu.push(a[a[t]]);
        }
        
        for(int i=1; i<=2*n; ++i)
		{
            if(i <= n && mp2[i] >= 0) cout << i << " ";
            else if(mp2[i] == 1) cout<< i << " ";
        }
        
        cout << "\n";//千万要加！！！ 
    }
    return 0;
}
```

---

## 作者：Lain_yc (赞：1)

## P4355 [CERC2015] Kernel Knights
### 原题链接：

[传送门](https://www.luogu.com.cn/problem/P4355)


---


### 题意：

寻找集合 $S$ ，使得：  
1. $S$ 中的骑士不能互相挑战。
2. 不在 $S$ 中的骑士都会被 $S$ 中的骑士挑战。


---


### 思路：

首先看一下挑战的具体规则：

> 在第 $i$ 个位置上的数 $k_i$ 代表着编号为 $i$ 的骑士挑战编号为 $k_i$ 的骑士。

观察第二条要求，不难发现，在 $S$ 外的骑士一定都被挑战了，由此我们可以知道，**只要一个骑士 $a$ 并没有被挑战过，那么他一定在集合 $S$ 中**。  
同时，因为集合内的骑士不能互相攻击，所以**被骑士 $a$ 挑战的那名骑士 $b$ 一定在集合 $S$ 的外面**。  
最后，队伍中可能出现一个非常招仇恨的骑士，他会被挑战很多次，这个时候我们**只用把他排出集合 $S$ 一次**就好了（~~要是祂被打一次赶祂一次岂不是给人家发配边疆了~~）。

这时候，可能有严谨的小伙伴要问了：
> 那集合外面的骑士的攻击怎么办呢？

事实上，集合外的攻击完全不用管，我们只需要看好集合内的骑士让他们不要打架就可以了，至于那些被流放到集合外的骑士就不属于我们的管理范围了~。

---

### 实现：

由于要进行踢出集合和加入集合两种操作，不难想到，我们可以开一个桶标记被攻击次数，并使用队列维护此集合：  
1. 先把没有被攻击过的骑士加入队列。
2. 进行完第一步后，把队列外没有被队列内骑士攻击的都加入队列。

然后就可以愉快的通过啦！（~~估计不会有人和我一样傻傻忘记输出空格全似了吧~~）。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],b[N],c[N];
queue<int>q;
int main(){
    while(cin>>n){
        memset(b,0,sizeof(b));//多测不清空 
        memset(c,0,sizeof(c));//亲人两行泪 
        int m=n*2;
        for(int i=1;i<=m;i++){
            cin>>a[i]; 
            b[a[i]]++;//开桶标记被攻击次数 
        }
        for(int i=1;i<=m;i++){
        	if(!b[i]){
        		q.push(i);//先处理没被打过的，一定在集合里 
        	}
        }
        while(!q.empty()){//处理操作 2 
            int p=q.front();
            q.pop();
            c[p]=1;
            if(c[a[p]])continue;//不要发配边疆，只踢出一次，方便又快捷 
            c[a[p]]=-1;b[a[a[p]]]--;//集合外面的骑士自己一边玩去 
            if(b[a[a[p]]]==0)q.push(a[a[p]]);//没人打的骑士也进来 
        }
        for(int i=1;i<=m;i++){
        	if(i<=n&&c[i]>=0||i>n&&c[i]==1)cout<<i<<" ";
        }
        //注意输出格式 qwq 
        cout<<'\n';
    }
    return 0;//华丽结束
}
```
~~说句闲话，研究骑士的最好方式是……~~

---

## 作者：zzy0618 (赞：1)

#### 题目

[题目链接](https://www.luogu.com.cn/problem/P4355)

#### 大体思路

1. 没有被攻击的骑士一定在这个集合当中。

2. 在做完步骤 $1$ 之后，集合外的骑士如果没有被集合内的其实攻击，就将其加入集合。

3. 由于步骤 $2$ 还要将其加入集合，所以用上一个队列维护比较方便。

前边已经有人用 ```queue``` 写过了，所以这次用数组模拟一下吧。

#### 完整代码

```cpp
#include<bits/stdc++.h>
#define ok 12345
#define no -1
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int a[200005], tong[200005];
int q[200005], ans[200005];
//tong:记录攻击次数，ans:记录答案，q:队列 
signed main() {
	register int n, i, N;
	register int l = 1, r = 0, f;
	n = read();
	N = 2 * n;//优化常数 
	for (i = 1; i <= N; i++)
		a[i] = read(), tong[a[i]] += 1;
	for (i = 1; i <= N; i++)
		if (tong[i] == 0)
			q[++r] = i;//step 1 
	while (l <= r) {
		f = q[l++];
		ans[f] = ok;
		if (ans[a[f]] == no)continue;//注意已经被攻击的骑士不在集合 
		ans[a[f]] = no;
		tong[a[a[f]]] -= 1;
		if (tong[a[a[f]]] == 0)q[++r] = a[a[f]];
	}//step 2,3
	for (i = 1; i <= N; i++) {
		if (i <= n && ans[i] >= 0)printf("%d ", i);
		else if (ans[i] == ok)printf("%d ", i);
	}
	return 0;
}
```


---

## 作者：wyc0607 (赞：0)

### 思路：
图论。

开一个队列记录核中骑士

记录每个骑士的被攻击次数（入度）。如果有未被攻击（入度为 0）的，直接入队。

接着，循环直到队列为空：

取出队头 $x$，弹出。将 $ih[x]$，即是否入队，更改为一。将其对手的 $ih$ 数组更改为 $-1$，即永远无法入核。将其敌人的敌人的被攻击次数减一。如果减完后该值为零，将其（敌人的敌人）入队。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],at[200005];
int ih[200005];
//a：读入数组，ih：是否在核中，at：被攻击的次数
main() {
	while(cin>>n) {
		/*初始化*/ 
		queue<int> q;
		memset(a,0,sizeof(a)),memset(at,0,sizeof(at)),memset(ih,0,sizeof(ih));
		/*读入*/ 
		for(int i=1; i<=2*n; i++) {
			cin>>a[i];
			at[a[i]]++;//被攻击次数++
		}
		for(int i=1;i<=2*n;i++) if(at[i]==0) q.push(i);//没被攻击，直接入队 
		while(!q.empty()){
			int x=q.front();
			q.pop();
			ih[x]=1;//入核 
			if(ih[a[x]]==-1) continue;//如果敌人已被本核骑士挑战，继续下一次循环 
			ih[a[x]]=-1,at[a[a[x]]]--;
			if(at[a[a[x]]]==0) q.push(a[a[x]]);
		}
		for(int i=1;i<=2*n;i++){
			if(i<=n&&ih[i]>=0) cout<<i<<' ';
			else if(ih[i]==1) cout<<i<<' ';
		}
		cout<<'\n';
	}
}
```

---

## 作者：ridewind2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4355)

## 分析
给出一些骑士，定义集合中的骑士没有受到挑战，但集合外的骑士都会受到集合中一些骑士的挑战，求集合中有哪些骑士。

## 思路

- 没有被攻击的骑士一定在这个集合当中。
- 然后，集合外的骑士如果没有被集合内的骑士攻击，就将其加入集合。
- 由于还要将其加入集合，所以用上一个队列维护比较方便。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],h[200010],s[200010];
queue<int>q;
int main(){
	int n;
	cin>>n;
    for(int i=1;i<=n*2;i++){
        cin>>a[i];
    	h[a[i]]++;
    }
    for(int i=1;i<=n*2;i++){
		if(h[i]==0)q.push(i);
	}
    while(q.size()>0){
	    int cur=q.front();
		q.pop();
		s[cur]=1;
	    if(s[a[cur]]==-1)continue;
	    s[a[cur]]=-1;
		h[a[a[cur]]]--;
        if(h[a[a[cur]]]==0)q.push(a[a[cur]]);
    }
    for(int i=1;i<=n*2;i++){
    	if(i<=n&&s[i]>=0||i>n&&s[i]==1)cout<<i<<" ";//输出集合 
	}
    return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4355)

题目大意：给出 $n$ 个红点和 $n$ 个蓝点，每个红点都向其中一个蓝点连一条边，每个蓝点也都向其中一个红点连一条边。现在要求出一个点集 $S$，满足：

- $\forall i,j\in S(i\neq j)$，$i$ 不向 $j$ 连边。

- $\forall i\notin S,\exist j\in S$ 使得 $j$ 向 $i$ 连边。

来看几个定理：

1. 如果一个点 $i$ 没有被连向，那么 $i$ 肯定属于 $S$，否则 $S$ 中找不到连向 $i$ 的点。

2. 设对于一个 $S$ 内的点 $i$，它向 $j$ 连一条边，则根据条件，$j$ 不在 $S$ 内。

3. 如果点 $i$ 只被 $S$ 外的点连向，则 $i$ 肯定属于 $S$，否则 $S$ 中找不到连向 $i$ 的点。

我们可以先按定理 $1$ 加入所有不被连向的点，然后利用定理 $2$ 排除被 $S$ 中的点连向的点。假设刚刚排除了 $i$ 点，它连向 $j$ 点，那么我们可以给 $j$ 的度数减一。如果 $j$ 的度数被减到 $0$，说明 $j$ 只被 $S$ 外的点连向，根据定理 $3$，把 $j$ 加入 $S$ 中。

最后可能会剩下一些节点，不知道应不应该放到 $S$ 中。所幸每个节点都只连出一条边，所以剩下的节点形成了几个环；又因为边是按照“红-蓝-红-蓝”的顺序连的，所以环都是偶环。所以我们只需要从每个环中选一种颜色的点加入 $S$ 即可。

代码贴上：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, to[200001], deg[200001], ok[200001];//ok[i]表示i是否在S内，为1表示是，为-1表示否，为0表示不确定
queue<int> q;
int main(){
	scanf("%d", &n);//1到n表示红点，n+1到2n表示蓝点
	for (int i = 1; i <= n * 2; i++){
		scanf("%d", &to[i]);
		deg[to[i]]++;//记录度数
	}
	for (int i = 1; i <= n * 2; i++)
		if (!deg[i]){ok[i] = 1; q.push(i);}//定理1
	while (!q.empty()){
		int u = q.front(); q.pop();
		if (ok[to[u]]) continue;//每个S外的点都只有一次贡献
		ok[to[u]] = -1; deg[to[to[u]]]--;//定理2
		if (!deg[to[to[u]]]){ok[to[to[u]]] = 1; q.push(to[to[u]]);}//定理3
	}
	for (int i = 1; i <= n; i++) if (ok[i] != -1) printf("%d ", i);//红色点：只要可能在S中就输出
	for (int i = n + 1; i <= n * 2; i++) if (ok[i] == 1) printf("%d ", i);//蓝色点：确认在S中才输出
	return 0;
}
```

---

## 作者：TheForgotten (赞：0)

# P4355 [CERC2015] Kernel Knights 题解
[题目传送门](luogu.com.cn/problem/P4355)
## 题目大意
给出一些骑士，定义集合 $S$ 中的骑士没有受到挑战，但集合外的骑士都会受到集合中一些骑士的挑战，求集合 $S$ 中有哪些骑士。

## 思路
没有被攻击的骑士一定在集合中，在做完步骤一之后，集合外的骑士如果没有被集合内的骑士攻击，就将其加入集合。又因为步骤二还有一些骑士需要进入集合，所以考虑用队列维护。

在开始时把骑士的受攻击次数初始化，如果受攻击次数等于 $0$ 就把这个骑士加入队列，注意多组数据每次都需要初始化，于是就可以开始写代码了，

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=2e5+100;
int n,a[maxn],d[maxn],k[maxn];
queue<int> q;
signed main(){
    while(~scanf("%d",&n)){
        while(!q.empty()) q.pop();
        memset(d,0,sizeof(d));
        memset(k,0,sizeof(k));
        for(int i=1;i<=2*n;i++){
            scanf("%d",&a[i]);
            d[a[i]]++;
        }
        for(int i=1;i<=2*n;i++){
			if(d[i]==0){
				q.push(i);
			}
		} 
        while(!q.empty()){
            int p=q.front();
            q.pop();
            k[p]=1;
            if(k[a[p]]==-1) continue;
            k[a[p]]=-1,d[a[a[p]]]--;
            if(d[a[a[p]]]==0) q.push(a[a[p]]);
        }
        for(int i=1;i<=2*n;i++){
            if(i<=n&&k[i]>=0)printf("%d ",i);
            else if(k[i]==1)printf("%d ",i);
        }
        printf("\n");
    }
    return 0;
}

```

---

## 作者：Genius_Star (赞：0)

### 思路：
因为原图是二分图，所以所有的环都是偶环。

因为每个点只有一个出度，所以所有的环都是简单环。

那么这个图可以想象成一个内向基环森林。

每次给度为 $0$ 的节点染色。

每遍历到一个点：

- 如果将要到达的点度为 $0$ 或者它的颜色为不可选（因为此点不可选所以不能随便染色），那么继续遍历。

然后把所有没有标记的环搞一遍就可以了。
### 完整代码：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 500010
using namespace std;
int n;
int to[maxn], h[maxn], cnt, deg[maxn], col[maxn];
void add(int u, int v){to[u] = v, deg[v] ++;}
 
void BFS(int u){
    col[u] = 2;
    while(true){
        if(col[to[u]])break;
        deg[to[u]] --;
        if(deg[to[u]] == 0 || col[u] == 2){
            col[to[u]] = col[u] ^ 1;
            u = to[u];
        }
        else break;
    }
}
 
void Col(int u){
    col[u] = 2;
    while(true){
        if(col[to[u]])break;
        col[to[u]] = col[u] ^ 1;
        u = to[u];
    }
}
 
int main(){
    scanf("%d", &n);
    int v;
    for(int i = 1; i <= n; i ++)
        scanf("%d", &v), add(i, v);
 
    for(int i = n + 1; i <= n * 2; i ++)
        scanf("%d", &v), add(i, v);
    n <<= 1;
    for(int i = 1; i <= n; i ++)
        if(!deg[i] && !col[i])BFS(i);
    for(int i = 1; i <= n; i ++)
        if(!col[i])Col(i);
    for(int i = 1; i <= n; i ++)
        if(col[i] == 2)printf("%d ", i);
    return 0;
}
```


---

