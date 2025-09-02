# 【MX-X6-T1】 Subtask Dependency

## 题目背景

原题链接：<https://oier.team/problems/X6B>。

## 题目描述

现在有一道 OI 题。这道题有 $n$ 个子任务，编号从 $1$ 到 $n$。编号为 $i$ 的子任务依赖 $d_i$ 个子任务，这些子任务的编号分别为 $a_{i,1},a_{i,2},\dots,a_{i,d_i}$。保证对于所有 $1\leq i\leq n,1\leq j\leq d_i$，有 $a_{i,j}<i$，即**一个子任务只会依赖编号小于自己的子任务**。注意一个子任务可能不依赖任何子任务。

一个选手的程序可以描述为一个长度为 $n$ 的 $0/1$ 序列 $p_1,p_2,\dots,p_n$，分别表示该程序能否通过第 $i$ 个子任务。

评测一个程序时，评测机会按照编号从小到大依次考虑每一个子任务。当考虑到第 $i$ 个子任务时：

- 如果该子任务依赖的子任务中存在一个子任务的状态为错误，则该子任务的状态为错误；
- 否则，评测机测试该子任务。如果选手的程序能通过该子任务，则该子任务状态为正确；否则状态为错误。

一个程序的得分是评测后状态为正确的子任务个数。

现在有 $m$ 个选手提交程序，你需要分别计算它们的得分。

## 说明/提示

**【样例解释 #1】**

- 选手 1 的程序可以通过所有子任务，因此所有 $3$ 个子任务的结果均为正确；
- 选手 2 的程序不能通过子任务 2，因此子任务 2 会被判定为错误；由于子任务 3 依赖子任务 2，因此即使选手 2 的程序可以通过子任务 3，子任务 3 也会被判定为错误。该选手的程序的评测结果只有子任务 1 正确。
- 选手 3 的程序不能通过任何子任务，因此所有子任务结果均为错误。

**【数据范围】**

对于所有数据，满足 $1\leq n,m\leq 100$，$0\leq d_i<i$，$1\leq a_{i,j}<i$，$0\leq p_{i,j}\leq 1$，不存在 $i$ 和 $j_1\neq j_2$ 使得 $a_{i,j_1}=a_{i,j_2}$。

共 $10$ 组数据，具体限制如下：

- 对于第 $1,2$ 组数据，满足 $n=1$；
- 对于第 $3,4,5$ 组数据，满足对所有 $i$，有 $d_i\leq 1$；
- 对于其他数据，不满足任何附加限制。

## 样例 #1

### 输入

```
3
0
1 1
1 2
3
1 1 1
1 0 1
0 0 0
```

### 输出

```
3
1
0```

## 样例 #2

### 输入

```
10
0
1 1
1 2
3 1 2 3
4 1 4 2 3
0
5 6 4 5 2 1
0
1 4
1 9
10
1 0 0 1 1 0 1 0 0 0
1 0 1 0 1 0 1 0 1 0
1 0 1 1 1 1 1 1 0 1
1 1 0 1 1 0 1 1 0 1
1 1 0 1 0 0 0 1 1 1
1 1 0 1 0 1 0 1 1 1
1 0 0 1 0 1 1 1 0 1
1 1 0 1 1 1 0 0 1 1
1 1 1 0 0 0 0 0 1 1
1 0 0 0 1 1 1 0 1 1```

### 输出

```
1
1
3
3
3
4
3
3
3
2```

# 题解

## 作者：lovely_lbh (赞：6)

## 题意

首先这是一道题，总共有 $n$ 个子任务，其中有一些子任务依赖于其他的子任务。

判断一个程序能否通过一个子任务的条件如下：

1. 如果该子任务依赖的子任务中存在一个子任务的状态为错误，则该子任务的状态为错误；

2. 否则，评测机测试该子任务。如果选手的程序能通过该子任务，则该子任务状态为正确；否则状态为错误。

随后会给你 $m$ 个选手程序，以及这些程序所对应的子任务的通过情况，你需要计算这些程序的得分。

## 分析

首先可以看出这是一道较为简单的模拟题，其中可能有一点点图论建模的相关知识，我们需要根据题意进行模拟。

首先将每一个子任务的依赖关系存储进一个数组。随后对于每一个给出的程序，枚举其子任务的通过情况，并计算得分即可，特别需要注意的一点是**会出现某个子任务通过，但其所依赖的子任务不通过**的情况，这时我们不应该计算该子任务的得分。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int s[114][514],d[114];
bool o[114];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>d[i];
		for(int j=1;j<=d[i];j++)cin>>s[i][j];
	}
	int m;
	cin>>m;
	while(m--)
	{
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>o[i];
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=d[i];j++)
			{
				if(!o[s[i][j]])o[i]=0;
			}
		}
		for(int i=1;i<=n;i++)if(o[i])ans++;
		cout<<ans<<endl;
	}
}
```

---

## 作者：shy_lihui (赞：4)

### 思路分析
简单模拟，我是把每个子任务的依赖子任务用了 set 存起来。遇到一个不正确的子任务就标记成假，遇到正确的看之前有没有假，有则是假，反之为真。

对于一个 oier 的得分情况可以用一个数组标记，$vis_i=0$ 代表当前第 $i$ 子任务没有判定是否得分，$1$ 表示判定过并且正确，为 $-1$ 就是不通过。

具体细节代码里说。

### 附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
set<int>s[105];//第 i 个子任务依赖。 
bool a[105][105]; 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int len;//第 i 个子任务依赖数量。 
		cin>>len;
		while(len--)
		{
			int x;
			cin>>x;//第 i 个子任务依赖第 x 个子任务。 
			s[i].insert(x);
		}
	}
	cin>>m;//这里就不多说了。 
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;i++)//枚举每个 oier 。 
	{
		int vis[105]={0}; //得分情况。 
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==0)//如果不通过。 
			{
				vis[j]=-1;//标记。 
			}
			if(a[i][j]==1)//这时判断依赖的子任务是否通过。 
			{
				bool flag=1;
				for(int x:s[j])//遍历 j 的依赖。 
				{
				//上面 x:s[j] 有的人可能编译不过去，因为这是 c++14 及以上特有的功能。 
				//dev-c++默认c++11，可以在网上搜教程调成 c++14 。 
					if(vis[x]==-1)//如果依赖的子任务没过。 
					{
						flag=0;//喜提不通过。 
						break;
					}
				}
				if(flag)//若依赖子任务全部通过。 
				{
					vis[j]=1;//通过。 
				}
				else
				{
					vis[j]=-1; 
				}
			}
		}
		int sum=0;
		for(int x=1;x<=m;x++)//通过了几个子任务。 
		{
			if(vis[x]==1)
			{
				sum++;
			}
		}
		cout<<sum<<'\n';
	}
	return 0;
}
```

---

## 作者：hjm777 (赞：2)

### Subtask Dependency

直接模拟，代码量不大。

请注意：**一个子任务是对的不仅要通过它依赖的子任务，还要通过它依赖的子任务的子任务，以及它依赖的子任务的子任务的子任务等等，所以要记得实时更新是否通过每个子任务为是否通过了它依赖的子任务以及它本身**。

```cpp
// Author : hejinming2012
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define dbg(x) cout << #x " = " << (x) << endl
#define quickio ios::sync_with_stdio(false);
#define quickin cin.tie(0);
#define quickout cout.tie(0);

using namespace std;
inline int read() {
    int now = 0, nev = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') nev = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { now = (now << 1) + (now << 3) + (c & 15); c = getchar(); }
    return now * nev;
}
void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int a[105][105], p[105];
signed main() {
    quickio
    quickin
    quickout
	int n = read();
    for(int i = 1; i <= n; i++) {
        a[i][0] = read();
        for(int j = 1; j <= a[i][0]; j++)
            a[i][j] = read();
    }
    int m = read();
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++)
            p[j] = read();
        int ans = 0;
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= a[j][0]; k++)
                p[j] &= p[a[j][k]];
            ans += p[j];
        }
        write(ans), putchar(10);
    }
    return 0;
}
```

---

## 作者：jinfanhao (赞：2)

这道题就是模拟，没什么难度。\
但是可能大家都忽略了一个点，需要它说明的点过了还要自己也过，我比赛时就是错这里。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=101;
int n,m,op[N][N],f[N],ok[N];
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; ++i){
		scanf("%d",&f[i]);
		for(int j=1; j<=f[i]; ++j)scanf("%d",&op[i][j]);
	}
	scanf("%d",&m);
	while(m--){
		memset(ok,0,sizeof(ok));
		int sum=0;
		for(int i=1; i<=n; ++i){
			int s;
			scanf("%d",&s);
			if(!s)ok[i]=-1;
			else{
				bool t=true;
				for(int j=1; j<=f[i]; ++j){
					if(ok[op[i][j]]==-1)t=false;
				}
				if(t)++sum;
				else ok[i]=-1;
			}
		}
		printf("%d\n",sum);
	}
	return 0;
} 
```

---

## 作者：BGM114514 (赞：1)

这题难度不高，模拟即可。

---

考虑用一个数组 $b_{1\sim n}$ 来表示各个子任务的状态，在输入时更新即可。（因为输入会把之前的数据给覆盖掉，所以不用担心）

**那怎么更新呢？** 

* 首先要存储子任务的依赖关系。考虑到数据范围并不大，可以使用数组，但是本人还是推荐使用 vector。什么是 vector 呢？你可以暂时的理解为一个大小随着数据个数变大而变大的“动态”数组。输入一个需要依赖的子任务，把该子任务 push_back 进 vector 里。

* 接着就是更新了。每输入一个 $b_i$，把 vector[i] 遍历一遍，将当前 $b_i$ 与 vector[i] 中的所有元素相与，最后如果 $b_i$ 为真就把答案累加。

**具体细节请看代码。**

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> v[105];//vector
bool b[105];//数组（子任务状态）
signed main(){
	ios::sync_with_stdio(false);//关闭同步流（相当于 scanf、printf）
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++){
		int k;
		cin>>k;
		while(k--){
			int p;
			cin>>p;
			v[i].push_back(p);//向 vector 尾部插入 p
		}
	}
	cin>>m;
	while(m--){//多组数据
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>b[i];
			for(auto it:v[i]){//遍历（C++11才能用）
				b[i]&=b[it];//相与
			}
			ans+=b[i];//累加
		}
		cout<<ans<<endl;//撒花！
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/180798570)

---

## 作者：AFO_Lzx (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P11155)

### $\texttt{Description}$

给定一个评测机和 $m$ 个选手的程序，让你分别计算出这 $m$ 个选手的得分并输出。

### $\texttt{Solution}$

这题就是一个模拟题，我们只需要按照下列步骤对于程序进行评测：

- 对于当前的子任务，我们需要检查其依赖的子任务的状态，如果存在依赖的子任务状态为错误，则将当前这个子任务的状态设为错误，并继续评测下一个子任务。
- 如果当前子任务的所有依赖的子任务状态都为正确，或当前子任务没有依赖的子任务，则根据选手的程序决定是否通过该子任务来设置其状态。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e2 + 5;
int n, m, a[N][N], b[N], p[N][N];
int res[N];

signed main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		
		for (int j = 1; j <= b[i]; j++) {
			int x; cin >> x;
			a[i][x] = 1;
		}
	}
	
	cin >> m;
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> p[i][j];
		}
	}
	
	for (int i = 1; i <= m; i++) {
		int cnt = 0;
		
		for (int j = 1; j <= n; j++) {
			res[j] = 1;
			
			for (int k = 1; k <= j - 1; k++) {
				if (a[j][k] == 1 && res[k] == 0) {
					res[j] = 0;
					break;
				}	
			}
			
			if (res[j] && p[i][j]) cnt++;
			else res[j] = 0;
		}
		
		cout << cnt << "\n";
	}
	return 0;
}
```

完结。

---

## 作者：Ak_hjc_using (赞：0)

考虑模拟。

### 思路

这道题我们可以用一个标记数组判断否这个子任务的评测状态，如果评测结果错误的，就将这个子任务的状态标记为 $-1$，否则就标记为 $0$，然后我们在判断一个子任务是否错误时，我们可以遍历所有与它有关系的子任务，如果有错误就标记为错误，否则就标记为 $0$。

最后用变量记录下来就可以了。

### 注意点

一定要将数组清空。

### 代码：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3 + 1;
int n, a[N][N], d[N], vis[N];
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1;i <= n;i ++)
	{
		cin >> d[i];
		for (int j = 1;j <= d[i];j ++)
		{
			cin >> a[i][j];
		}
	}
	int m;
	cin >> m;
	while (m --)
	{
		memset(vis, 0, sizeof vis); // 清空数组。
		int ans = 0;
		for (int i=1;i<=n;i++)
		{
			bool cnt;
			cin >> cnt;
			if (cnt == 0)
			{
				vis[i] = -1; // 如果错误，标记为-1。
			}
			else
			{
				bool flag = true;
				for (int j = 1;j <= d[i];j ++)
				{
					if (vis[a[i][j]] == -1)
					{
						flag = false;	// 判断是否成功
					}
				}
				if (flag == true)		
				{
					ans ++;	// 如果成功，计数器++
				}
				else
				{
					vis[i ]= -1; // 否则标记为-1。
				}
			} 
		}
		cout << ans << '\n'; // 输出答案。
	}
	return 0;
}

```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11155)

### 思路

数据不大，直接模拟即可。

但是要注意在标记时，如果它依赖的子任务错了而它本身是对的，也要标记为错。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105][105],d[105],p[105][105],m,b,t;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>d[i];
        for(int j=1;j<=d[i];j++)
        {
            cin>>a[i][j];
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        t=0;//多测不清空，爆零两行泪
        for(int j=1;j<=n;j++)
        {
            cin>>p[i][j];
            b=1;
            for(int k=1;k<=d[j];k++)
            {
                if(p[i][a[j][k]]==0)  
                {
                	b=0;//如果有依赖的子任务错了，那就不行
                	break;//退出
                }
            }
            if(p[i][j]==1&&b==1)  t++;//可以
            else  p[i][j]=0;//不行，标记为0，表示不能过
        }
        cout<<t<<endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11155)

又是一道模拟题。

我们定义 $a_{i,j}$ 表示第 $i$ 个子任务依赖于第 $j$ 个子任务，$x_i$ 表示对于某一个询问，该选手能否通过第 $i$ 个子任务。

对于每一个子任务，我们先对查找所有的 $x_{a_{i,j}}$，如果均为通过，我们再判断该子任务是否通过，否则直接判错，最后统计即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=101;
int n,m,a[N][N],d[N],ans;
bool x[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		for(int j=1;j<=d[i];j++) cin>>a[i][j];
	}
	cin>>m;
	while(m--){
		memset(x,true,sizeof(x));
		for(int i=1,t;i<=n;i++){
			cin>>t;
			for(int j=1;j<=d[i];j++){
				if(!x[a[i][j]]){
					x[i]=false;
					break;
				}
			}
			if(x[i]) x[i]=t;
		}
		ans=0;
		for(int i=1;i<=n;i++) if(x[i]) ans++;
		cout<<ans<<endl;
	}
}
```

---

## 作者：fanjiayu666 (赞：0)

### 题意简述
给定 $n$ 个子任务，并告诉你每个子任务依赖了哪些子任务，然后告诉你每个选手子任务通过情况，请你统计每位选手的得分。

### 思路
首先，这道题一看就现要用很多 STL，很容易想到要用到 ``vector`` 储存，然后使用数组储存每位选手的通过情况，并且用 ``map`` 或数组来记录总通过情况。

所以我们现在可以有个大概思路，先来看输入：
```cpp
cin>>n;
for(int i=1;i<=n;i++){
    int d;
    cin>>d;
    while(d--){
        int tmp;
        cin>>tmp;
        a[i].push_back(tmp);//往vector里面加入子任务依赖
    }
}
```
接下来，我们就要处理每位选手的分数：
```cpp
cin>>m;
for(int i=1;i<=m;i++){
    mp.clear();
    memset(b,0,sizeof(b));
    int s=0;
    for(int j=1;j<=n;j++){
        cin>>b[j];
        mp[j]=b[j];//先记录通过情况。
    }
    for(int j=1;j<=n;j++){
        if(b[j]==1){
            for(int k=0;k<a[j].size();k++){
                if(mp[a[j][k]]==0){mp[j]=0;goto d;}//查找依赖子任务中有没有未通过的，如果有，则将这个子任务的通过状态设为未通过。
            }
            s++;
            d:;
        }
    }
    cout<<s<<endl;//输出当前选手的总分。
}
```
上面的代码中的 ``goto x;`` 语句的作用是：跳到 ``x`` 这个位置继续执行代码。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int>a[1000];
map<int,int>mp;
int b[1000];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int d;
        cin>>d;
        while(d--){
            int tmp;
            cin>>tmp;
            a[i].push_back(tmp);
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        mp.clear();
        memset(b,0,sizeof(b));
        int s=0;
        for(int j=1;j<=n;j++){
            cin>>b[j];
            mp[j]=b[j];
        }
        for(int j=1;j<=n;j++){
            if(b[j]==1){
                for(int k=0;k<a[j].size();k++){
                    if(mp[a[j][k]]==0){mp[j]=0;goto d;}
                }
                s++;
                d:;
            }
        }
        cout<<s<<endl;
    }
}
```
（注释见上）

完结撒花❀！！！

---

## 作者：王逸辰 (赞：0)

# P11155 【MX-X6-T1】Subtask Dependency 题解
## 思路
按题意模拟。

注意：

即使能通过当前子任务，也要判断一下他所依赖的子任务是否通过。

若能，则当前子任务用另一个数组标记当前子任务状态为通过，反之亦然（当然，若当前子任务不依赖任何子任务，直接判断即可）。



具体细节见代码注释。
## Code
赛时代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[200][200],p[200][200],ans,d[200][200];
inline bool bcj(int x,int y){
	for(int i=1; i<=a[y][0]; i++)
		if(!d[x][a[y][i]])//判断
			return false;
	return true;
}
int main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>a[i][0];
		for(int j=1; j<=a[i][0]; j++)
			cin>>a[i][j];
	}
	cin>>m;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			cin>>p[i][j];
	for(int i=1; i<=m; i++){//m和n的顺序别弄反了
		ans=0;
		for(int j=1; j<=n; j++){
			if(p[i][j]){
				if(a[j][0]==0||bcj(i,j)){
					ans++;
					d[i][j]=1;//用于标记的数组
				}
			}
		}
		cout<<ans<<'\n';//换行
	}
	return 0;
}
```

---

