# Set Construction

## 题目描述

给你一个 $n\times n$ 的矩阵 $b$。

你需要构造 $n$ 个集合，集合里出现的数只能是 $1\sim n$。


若 $b_{i,j}=1$，则说明集合 $i$ 是集合 $j$ 的子集。否则说明集合 $i$ 不是集合 $j$ 的子集。

数据保证有解，你需要构造出这 $n$ 个集合。

## 样例 #1

### 输入

```
2
4
0001
1001
0001
0000
3
011
001
000```

### 输出

```
3 1 2 3
2 1 3
2 2 4
4 1 2 3 4
1 1
2 1 2
3 1 2 3```

# 题解

## 作者：晴空一鹤 (赞：12)

## Solution

构造题一枚。

我们可以给每个集合分配一个不同的数字，容易发现，此时集合之间是互不包含的。

接下来处理给出的包含信息，若第 $i$ 个集合被第 $j$ 个集合包含，就把你给 $i$ 集合分配的数字加入到 $j$ 集合中，容易发现，此时能刚好满足这个关系，同时，与其他集合的关系也不会被破坏。

实现的话可以用 `vector`，另外多测记得清空。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
vector<int>q[105];
string s;
void inline slove(){
    cin>>n;
    for(int i=1;i<=n;i++)
    q[i].clear();
    for(int i=1;i<=n;i++)
    q[i].push_back(i);
    for(int i=1;i<=n;i++){
    cin>>s;
    for(int j=0;j<n;j++)
    if(s[j]=='1')
    q[j+1].push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
    cout<<q[i].size()<<" ";
    for(int j=0;j<q[i].size();j++)
    cout<<q[i][j]<<" ";
    cout<<endl;
    }
}
int main(){
    cin>>t;
    while(t--)slove();
}
```

---

## 作者：lutaoquan2012 (赞：3)

## 思路：
这是一道构造的题目。

我们首先把一个数字分配给每一个集合里去，如果一个集合 $i$ 被集合 $j$ 包含，就把集合 $i$ 里面最原始的那个数组放进 $j$ 集合里面去，不用把整个 $i$ 全部放进去，因为是 $i$ 的子集也肯定是 $j$ 的子集。

## 代码：
```cpp
//
// Created by 55062 on 2024/6/17.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, T;
char a[110][110];
set<ll> s[110];

int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) cin >> a[i][j];
        for (int i = 1; i <= n; i++) s[i].clear();
        for (int i = 1; i <= n; i++) s[i].insert(i);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (a[i][j] == '1') s[j].insert(i);
        for (int i = 1; i <= n; i++) {
            cout << s[i].size() << " ";
            for (auto it = s[i].begin(); it != s[i].end(); it++) cout << *it << " ";
            cout << endl;
        }
    }
    return 0;
}
```

---

## 作者：JW_Yesod (赞：1)

# CF1761C Solution

## 0x01 题意

现在有 $n$ 个集合，每个集合中的元素只能为 $1 \sim n$。

已知 $n \times n$ 的矩阵 $b$，矩阵中元素为 $1$ 或 $0$，若 $b_{i,j}=1$，则代表集合 $i$ 为集合 $j$ 的子集。

现在已知矩阵 $b$，需要你构造出这 $n$ 个集合。

## 0x02 思路

显然，这是一道**构造题**，那么我们可以先为每个集合赋一个**互不相同**的值（保证所有集合两两之间彼此独立）。

随后，扫一遍矩阵，当 $b_{i,j}=1$ 时，我们就在集合 $j$ 后加上集合 $i$ 的“初始值”（即一开始互不相同的值），此时 $i$ 一定为 $j$ 的子集。

## 0x03 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
ll t,n;
vector<ll>a[105];
void change(int A,int B){//在集合b后插入集合a的初始值 
	a[B].push_back(a[A].front());
}
int main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	cin>>t;
	while(t--){
		for(int i=1;i<=100;i++){//多测要清空 
			a[i].clear();
		}
		cin>>n;
		for(int i=1;i<=n;i++){//为每个集合赋上互不相同的值 
			a[i].push_back(i);
		}
		for(int i=1;i<=n;i++){
			string s;
			cin>>s;
			for(int j=0;j<s.size();j++){
				if(s[j]=='1'){
					change(i,j+1);
				}
			}
		}
		for(int i=1;i<=n;i++){
			cout<<a[i].size()<<" ";//要记得先输出集合内元素个数 
			for(int j=0;j<a[i].size();j++){
				cout<<a[i][j]<<" ";
			}
			cout<<'\n';
		} 
	}
	return 0;
}
```

## 0x04 注意
- 多测要记得清空。
- 需要先输出集合内元素个数。

---

## 作者：lwx20211103 (赞：1)

## 解法说明

这是一道构造题，答案不唯一。题意相信大家也看了。对于这种输入方式，我们可以使用 `std::string`定义一个字符串 $s$ 来存储，如果想用数字的话，可以采用这种方式：

```cpp
for (int i = 0;i < n;i++)
{
	scanf("%1d", &nums[i]);//仅供参考                   
}
```

我们可以开一个桶，如果碰到矩阵中有数字为 $1$ 的情况，就把当前的行的数字放入到当前的列的数字的桶里面，同时每个桶首先要放入自己本身。可以看图（样例一的第二个 test case）：
![](https://cdn.luogu.com.cn/upload/image_hosting/430dp6hb.png)
思路有了之后，代码就不难实现了。

## 完整代码

```cpp
#include <bits/stdc++.h> //I AK IOI.
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        string s;
        map<int, vector<int> > ans;//map代替二维vector。
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            ans[i].push_back(i);//放入自己
        }
        
        for (int i = 1; i <= n; i++)
        {
            cin >> s;
            for (int j = 0; j < n; j++)
            {
                if (s[j] == '1')
                {
                    ans[j + 1].push_back(i);//调了好几次，要从1开始
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            cout << ans[i].size() << " ";
            for (auto &&x : ans[i])
            {
                cout << x << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}

```


---

## 作者：Symbolize (赞：1)

# 思路
若 $i \subseteq j$ 则将 $i$ 加入 $j$ 的答案行列之中。

注：因为 $i \subseteq i$，所以 $i$ 的答案里面也会有 $i$ 本身。

然后输出答案即可。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e2+10;
using namespace std;
int t,n;
string a[N];
vector<vector<int> > v(N);
void getans()
{
	rep1(i,0,n-1) v[i].clear();//清空
	cin>>n;
	rep1(i,0,n-1)
	{
		cin>>a[i];
		v[i].push_back(i);//自身也得算上
		rep1(j,0,n-1) if(a[i][j]=='1') v[j].push_back(i);//j包含i
	}
	rep1(i,0,n-1)
	{
		cout<<v[i].size()<<' ';//集合元素个数
		rep1(j,0,v[i].size()-1) cout<<v[i][j]+1<<' ';//加1是因为我们从0开始的存储
		putchar('\n');//记得换行
	}
	return;
}
signed main()
{
	cin>>t;
	while(t--) getans();//t组数据
	return 0;//收场
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

对于第 $i$ 个集合，首先将其分别加入 $1,2,\dots,n$，使所有集合元素不同。如果对于一组 $(i,j)$，$i$ 需要是 $j$ 的子集，则我们只需要把 $i$ 中的元素加到 $j$ 里面去就行了。

你可以得到代码：

```cpp
il void solve(){
	cin>>n;
	for(re int i=1;i<=n;++i) ans[i].clear();
	for(re int i=1;i<=n;++i){
		cin>>a[i].s,a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(re int i=1;i<=n;++i){
		for(re int j=0;j<a[i].s.size();++j){
			if(a[i].s[j]=='1') ans[j+1].push_back(i);
		}
		ans[a[i].id].push_back(i);
	}
	for(re int i=1;i<=n;++i){
		cout<<ans[i].size()<<" ";
		for(re int j=0;j<ans[i].size();++j) cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
}
```
但很显然，这个排序是多余的。因为如果有 $i$ 是 $j$ 的子集且 $j$ 是 $k$ 的子集则 $i$ 必定是 $k$ 的子集。这个在输入的时候一定会给到。所以只边输入边将包含 $i$ 的集合添加元素 $i$ 就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

int n;
const int N=1e3+10;
vector<int> ans[N];

il void solve(){
	cin>>n;
	for(re int i=1;i<=n;++i) ans[i].clear();
	for(re int i=1;i<=n;++i){
		string s;cin>>s;
		for(re int j=0;j<s.size();++j)
			if(s[j]=='1') ans[j+1].push_back(i);
		ans[i].push_back(i);
	}
	for(re int i=1;i<=n;++i){
		cout<<ans[i].size()<<" ";
		for(re int j=0;j<ans[i].size();++j) cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
	return ;
}

signed main(){
	int t;cin>>t;while(t--)
	solve();
	return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 思路
这道题，我们只需要用一个动态数组存下每一条边，将第 $i$ 个集合的子集都放入 $v_i$ 中，然后我们要将每一个 $v_i$ 都初始化成 $i$ ，所以最后输出的时候只需要将 $v_i$ 的长度以及 $v_i$ 中存的数输出即可，这样一定符合题意，而且这道题不需要拓扑因为若 $b_{i,j}=1,b_{j,k}=1$ 那么 $b_{j,k}=1$ 那么只要他的输入正确，建边也一定没问题。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string a[110];
vector<int>v[10010];
int main(){
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=0;i<n;i++) v[i].clear();
		for(int i=0;i<n;i++) {
			cin>>a[i];
			v[i].push_back(i); //初始化
			for(int j=0;j<n;j++) {
				if(a[i][j]=='1') v[j].push_back(i); //建边
			}
		}
		for(int i=0;i<n;i++) {
			cout<<v[i].size()<<" ";
			for(int j=0;j<v[i].size();j++) cout<<v[i][j]+1<<" ";//记住一定要加一因为从0开始的
			puts("");
		}
	}
	return false;
}

```


---

## 作者：KingPowers (赞：0)

## 题意

给定一个 $n\times n$ 的 $01$ 矩阵 $b$，你需要构造出 $n$ 个集合 $A_1,A_2,\dots ,A_n$，满足：

- 所有集合内的元素都由 $1$ 到 $n$ 以内的整数构成。

- 所有集合都互不相同。

- 若 $b_{i,j}=1$，则说明 $A_i$ 是 $A_j$ 的子集，否则 $b_{i,j}=0$。

## 正文

考虑按照子集关系建一张图：当 $A_i$ 为 $A_j$ 的子集时，从 $i$ 向 $j$ 连一条有向边。

然后因为是按照子集关系连边，所以可以证明这张图一定是个有向无环图，那么我们就很容易想到拓扑排序。

然后呢？~~然后这题就做完了。~~

构造答案建议使用 set 或者 bitset 来构造，比较方便，这里我使用的是 set，具体见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fx first
#define fy second
#define mkp make_pair
#define umap unordered_map
using namespace std;
const int N=2e5+5;
const int inf=1e18;
int read(){
	int ans=0,flag=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') flag=-1;
	for(;isdigit(ch);ch=getchar()) ans=ans*10+(ch^48);
	return ans*flag;
}
struct edge{
	int nxt,to;
}e[N];
int T,n,cnt,head[N],ru[105];
void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void bfs(){  //拓扑排序 
	int idx=0;queue<int>q;
	for(int i=1;i<=n;i++)
		if(!ru[i]) q.push(i);
	vector<set<int>>ans;  //用set来统计答案，自动去重很方便 
	ans.resize(n+1);
	while(q.size()){
		int now=q.front();q.pop();
		ans[now].insert(++idx);
		for(int i=head[now];i;i=e[i].nxt){
			int to=e[i].to;
			for(auto j:ans[now]) ans[to].insert(j);  //连向的点对应的集合一定包含我们当前点的集合 
			ru[to]--;
			if(!ru[to]) q.push(to);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i].size());
		for(auto j:ans[i]) printf("%lld ",j);
		puts("");
	}
}
signed main(){
	T=read();
	while(T--){
		n=read(),cnt=0;
		memset(head,0,sizeof(head));
		memset(ru,0,sizeof(ru));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				char ch;cin>>ch;
				if(ch=='1') add(i,j),ru[j]++;  //按照子集关系连边 
			}
		bfs();
	}
	return 0;
}
```



---

## 作者：qzhwlzy (赞：0)

### 题目大意

[传送门](https://codeforces.com/problemset/problem/1761/C)

给出 $n\times n$ 的 01 矩阵 $b$，构造 $n$ 个集合 $A_1,A_2,\cdots,A_n\subseteq [1,n]$，使得 $\forall b_{i,j} = 1$，都有 $A_i\subsetneqq A_j$；$\forall b_{i,j} = 0$，都有 $A_i\nsubseteqq A_j$（请注意是**真子集**而非**子集**，翻译有误）。

### 思路

从简单的情况分析起，若所有 $b_{i,j}$ 均为 $0$，则只需要构造 $A_i = \{i\}$ 即可，此时集合间不存在子集关系。

如果有一项 $b_{i,j} = 1$，那么，只需要将 $A_j$ 中增加数 $i$，使得 $A_i = \{i\},A_j = \{i,j\}$，此时满足 $A_i\subsetneqq A_j$。

接下来分析此方法构造出的集合一定合法：假设 $X_i = \{x | b_{x,i} = 1\}$ 。那么对于任意 $i,j$ 满足 $b_{i,j} = 1$，一定有 $A_i = \{i\}\bigcup X_i , A_j = \{j\} \cup X_j$。

由于题中所给数据一定合法，有 $X_i\subseteq X_j$（因为若 $b_{x,i} = 1,b_{i,j} = 1$，根据子集的传递性，即 $A_x\subsetneqq A_i\subsetneqq A_j \Rightarrow A_x\subsetneqq A_j$，一定有 $b_{x,j} = 1$）；又 $i\in X_j$ 而 $j\notin X_i$（否则 $b_{i,j} = b_{j,i} = 1$，有 $A_i\subsetneqq A_j$ 且 $A_j\subsetneqq A_i$，矛盾），所以有 $A_i = \{i\}\bigcup X_i\subseteq X_j \subsetneqq \{j\} \cup X_j = A_j$。证毕。

至于代码，在读入时可以**直接**对于所有 $b_{i,j} = 1$ 的 $i,j$ 将 $i$ 加入集合 $A_j$，具体证明见上。

实现的话开数组二维数组 $a$，$a[i][j]$ 表示 $j$ 是否在 $A_i$ 中。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 105
using namespace std;
int T,n; int a[maxn][maxn],x;
void set(){for(int i=1;i<=n;i++){a[i][0]=1; for(int j=1;j<=n;j++) a[i][j]=(i==j);}}
int main(){
    scanf("%d",&T); while(T--){
        scanf("%d",&n); set(); // 多测,初始化
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){scanf("%1d",&x); if(x){a[j][i]=1; a[j][0]++;}}
        for(int i=1;i<=n;i++){printf("%d ",a[i][0]); for(int j=1;j<=n;j++) if(a[i][j]) printf("%d ",j); printf("\n");}
    } return 0; // 具体实现在上面思路部分
}

```

---

