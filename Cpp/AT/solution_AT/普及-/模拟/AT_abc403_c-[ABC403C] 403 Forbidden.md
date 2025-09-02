# [ABC403C] 403 Forbidden

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc403/tasks/abc403_c

WAtCoder 有 $N$ 个用户，编号从 $1$ 到 $N$。还有 $M$ 个比赛页面，编号从 $1$ 到 $M$。初始时，所有用户都没有任何比赛页面的访问权限。

现在需要依次处理 $Q$ 个查询。查询共有三种类型，格式如下：

- `1 X Y`：授予用户 $X$ 访问比赛页面 $Y$ 的权限。
- `2 X`：授予用户 $X$ 访问所有比赛页面的权限。
- `3 X Y`：查询用户 $X$ 是否可以访问比赛页面 $Y$。

注意：在查询过程中，可能会多次授予某个用户已经拥有的权限。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq X \leq N$
- $1 \leq Y \leq M$
- 输入中的所有值均为整数

### 样例解释 #1

- 第一个查询授予用户 $1$ 访问比赛页面 $2$ 的权限。
- 第二个查询时，用户 $1$ 只能访问比赛页面 $2$，因此查询页面 $1$ 时输出 `No`。
- 第三个查询时，用户 $1$ 可以访问比赛页面 $2$，因此输出 `Yes`。
- 第四个查询授予用户 $2$ 访问所有比赛页面的权限。
- 第五个查询时，用户 $2$ 可以访问所有页面（$1,2,3$），因此查询页面 $3$ 时输出 `Yes`。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2 3 5
1 1 2
3 1 1
3 1 2
2 2
3 2 3```

### 输出

```
No
Yes
Yes```

## 样例 #2

### 输入

```
5 5 10
2 2
3 4 4
1 1 1
1 4 1
1 4 2
1 4 4
1 2 4
3 3 2
3 5 4
3 2 1```

### 输出

```
No
No
No
Yes```

# 题解

## 作者：include13_fAKe (赞：3)

吐槽：为什么不添加撤销查看权的操作，这个题是否太简单了。

STL 运用之 map。map 套 map。

每一次当 $\texttt 1$ 操作时，令 $map_{x,y}=1$。$\texttt 2$ 操作时，开一个数组 $a$，令 $a_x=1$。

查询时查 $map_{x,y}$ 是否已经有了值或 $a_x$ 已经有了值，分别代表人 $x$ 能够看 $y$ 问题、人 $x$ 能够看所有问题。

笑点解析：笔者赛时 B 调了很久才过的。B 调试困难时果断先切了 C。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2*114514;
map<int,map<int,int> > maze;
bool maze1[N];
int n,m,q;
signed main(){
	cin>>n>>m>>q;
	while(q--){
		int op;
		cin>>op;
		switch(op){
			case 1:{
				int x,y;
				cin>>x>>y;
				maze[x][y]=1;
				break;
			}
			case 2:{
				int x;
				cin>>x;
				maze1[x]=1;
				break;
			}
			default:{
				int x,y;
				cin>>x>>y;
				if(maze[x][y]||maze1[x])	cout<<"Yes"<<endl;
				else	cout<<"No"<<endl;
				break;
			}
		}
	}
	cout<<endl;
	return 0;
}//ABC403C 
```

---

## 作者：chu_yh (赞：1)

水题。本题解用一个浅显易懂的 `set`。

### 思路

开个布尔型的二维数组 $a_{i,j}$，表示 $i$ 用户能否访问 $j$ 页面。

如此，操作二就需要把所有网站遍历一遍，时间不够优秀，考虑 STL 容器，很多人用 `map`，这里讲 `set`。

### `set`讲解

在 C++17 中，`std::set` 作为标准模板库（STL）中的关联容器，提供了自动排序、**唯一元素**存储（可用作去重）的功能。插入、删除、查找均为 $O(\log n)$。

#### 包含头文件与声明

```cpp
#include <set>
std::set<int> s; 
```

#### 插入元素

插入值为 $x$ 的元素：`s.insert(x);`

#### 删除元素
删除值为 $x$ 的元素：`s.erase(x)`。

#### 查找遍历

- 查找值为 $x$ 的元素：`s.count(x)`。
  - 若该元素存在，返回 $1$。
  - 若该元素不存在，返回 $0$。
- 查找值为 $x$ 的元素的位置：`auto a= s1.find(x);`。
  - 若该元素存在，返回迭代器。
  - 若该元素不存在，返回 `s.end()`。

#### 遍历

若不加 `&`,`num` 就只是形式变量，不影响原本 `s1` 中的值。

```cpp
for(auto& num : s1){}
```

### 解题过程

为每一个用户开一个 `set`，再开个一维的布尔型数组 $vis_i$ 表示用户 $i$ 能否查看所有网站。
- 若是操作一，向该用户的 `set` 中插入网站号即可；
- 若是操作二，更改该用户的 $vis$ 即可；
- 若是操作三，若该用户 $vis$ 为真或该用户 `set` 容器中能查询到该网站，输出 `Yes`，否则输出 `No`。

注意：**老老实实用三个变量依次读入**，否则读入顺序可能会混乱，然后 WA 掉，~~比如我就因这个问题吃了五个法师~~。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+2;
int n,m,Q,t,x,y;
bool vis[N];
set<int> a[N];
inline int read(){
	register int X=0; register char C=getchar();
	while(C<'0'||'9'<C) C=getchar();
	while('0'<=C&&C<='9'){X=(X<<3)+(X<<1)+(C^48);C=getchar();}
	return X;
}

int main(){
	n=read(),m=read(),Q=read();
	while(Q--){
		t=read(),x=read();
		if(t!=2) y=read();
		if(t==1) a[x].insert(y);//插入
		else if(t==2) vis[x]=true;
		else{//count(a)查询集内是否有a
			if(vis[x]||a[x].count(y)) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}
```

---

## 作者：__assassin_ (赞：0)

[原题链接](https://atcoder.jp/contests/abc403/tasks/abc403_c)

## 思路：
首先定义一个 `map<pair<int,int>,int>` 的变量 $mp$，$mp_{x,0}$ 的值表示学生 $x$ 是否可以打开所有网站，$mp_{x,y}$ 的值表示学生 $x$ 是否打开网站 $y$。对于操作一，将 $mp_{x,y}$ 设为 $1$；对于操作二，将 $mp_{x,0}$ 设为 $1$；对于操作三，如果 $mp_{x,0}$ 或 $mp_{x,y}$ 等于 $1$，则输出 `Yes`，反之输出 `No`。注意换行。

## AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q;
int op,x,y;
map<pair<int,int>,int> mp;//定义map变量，用mp[{x,0}]和mp[{x,y}]的值判断学生x是否可以打开网站y
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>q;
	while(q--){//q次操作
		cin>>op;
		if(op==1){//对于操作一
			cin>>x>>y;
			mp[{x,y}]=1;//表示学生x可以打开网站y
		}
		if(op==2){//对于操作二
			cin>>x;
			mp[{x,0}]=1;//表示学生x可以打开所有网站
		}
		if(op==3){//对于操作三
			cin>>x>>y;
			if(mp[{x,0}]==1||mp[{x,y}]==1) cout<<"Yes";//学生x可以打开网站y
			else cout<<"No";//学生x无法打开网站y
			cout<<"\n";
		}
	}
	return 0;
}



```

---

## 作者：floris (赞：0)

## 思路

可以使用一个 `set` 数组（即很多个 $set$ 容器）维护，对于每一次询问，就在对应的 $set$ 数组里查询，如问 $x$ 是否可以查看 $y$ 页权限，只需要查询 `set[x]` 中是否有 `y` 就行了。

剩下就只有按题意写代码就可以了。

## AC code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,m,q;
bool vis[N];  // 记录用户是否拥有所有页面的权限
set<int> s[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		int opt,x,y;
		cin>>opt>>x;
		if(opt==1){
			cin>>y;
			s[x].insert(y);
		}
		else if(opt==2) vis[x]=1;
		else{
			cin>>y;
			if(vis[x]==1){
				cout<<"Yes"<<'\n';
				continue;
			}
			if(s[x].count(y)) cout<<"Yes"<<'\n';
			else cout<<"No"<<'\n';
		}
	}
	return 0; 
} 
```

---

## 作者：zyn0309 (赞：0)

# [ABC403C] 403 Forbidden
[题目传送门](https://atcoder.jp/contests/abc403/tasks/abc403_c)

## 思路
对每一个用户开一个 map，设用户 $x$ 对应的 map 为 $mp_x$。在开一个 bool 类型的数组 $b$。对于操作一，将 $mp_{x,y}$ 赋值为 true。操作二，将 $b_x$ 赋值为 true。操作三，如果 $mp_{x,y}$ 或 $b_x$ 等于 true，说明 $x$ 可以查看 $y$，否则不能查看。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+10;
int n,m,q;
map<int,bool>mp[N];
bool b[N];
signed main(){
	cin>>n>>m>>q;
	int opt,x,y;
	while(q--){
	  cin>>opt;
	  if(opt==1){
	  	cin>>x>>y;
	  	mp[x][y]=1;
	  }
	  if(opt==2){
	  	cin>>x;
	  	b[x]=1;
	  }
	  if(opt==3){
	  	cin>>x>>y;
	  	if(mp[x][y]||b[x])cout<<"Yes\n";
	  	else cout<<"No\n";
	  }
	}
	return 0;
}
```

---

## 作者：ccxXF (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/AT_abc403_c)
## 题目分析
希望审核员大大给过。

这道题一眼就是一道模拟题，分别判断第一个数字是 $1$，$2$，$3$ 的情况，可以用一个 ```vector``` 来记录。
- 当第一个数字为 $1$ 时，用 ```vector``` 进行标记，但是普通的 ```vector``` 查找的时间复杂度为 $O(n)$，所以要用到 ```vector<unordered_set<int>>```，```unordered_set``` 是基于哈希表的集合，提供 $O(1)$ 平均时间复杂度的查找、插入和删除操作。
- 当第一个数字为 $2$ 时，可以再另外这一个数组标记，判断时仅需加上这个数组即可。
- 当第一个数字为 $3$ 时，判断两个标记数组里是否含有 ```y```，有就输出 Yes，反之 No，即 ```all[X] || sp[X].count(Y) ? "Yes\n" : "No\n"```，其中 ```sp``` 为 ```vector<unordered_set<int>>``` 类型，```all``` 为数组类型。
## 题目代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int all[2000001];
vector<unordered_set<int>> sp(2000001);
int main() {
	int N, M, Q;
	cin >> N >> M >> Q;
	while (Q--) {
		int t, X, Y;
		cin >> t;
		if (t == 1) {
			cin >> X >> Y;
			if (!all[X]) sp[X].insert(Y);
		} else if (t == 2) {
			cin >> X;
			all[X] = true;
			sp[X].clear();
		} else if (t == 3) {
			cin >> X >> Y;
			cout << (all[X] || sp[X].count(Y) ? "Yes\n" : "No\n");
		}
	}
	return 0;
}

```

---

## 作者：CCY20130127 (赞：0)

## 题目大意：
[403 Forbidden](https://www.luogu.com.cn/problem/AT_abc403_c)

上方为题目传送门，目前还没有翻译，请谅解。

## 题目思路：
这道题需要用两个数组标记数据。**特定权限管理**：每个用户可能有多个特定的竞赛页面权限，可以用哈希集合来存储这些页面编号。**全局权限管理**：某些用户可能被授予所有页面的权限，可以用一个布尔数组来标记这些用户。

对于类型 $1$ 的查询，如果用户还没有全局权限，则将其特定页面权限添加到对应的集合中。

对于类型 $2$ 的查询，标记该用户拥有全局权限，并清空其特定权限集合，因为全局权限覆盖特定权限。

对于类型 $3$ 的查询，检查用户是否有全局权限，或者是否有特定的页面权限。

## 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
int N, M, Q;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> N >> M >> Q;
	vector<unordered_set<int>> a(N + 1);
	vector<bool> f(N + 1, false);
	while (Q--) {
		int type, X, Y;
		cin >> type;
		if (type == 1) {
			cin >> X >> Y;
			if (!f[X]) {
				a[X].insert(Y);
			}
		} else if (type == 2) {
			cin >> X;
			f[X] = true;
			a[X].clear();
		} else if (type == 3) {
			cin >> X >> Y;
			if (f[X] || a[X].count(Y)) {
				cout << "Yes\n";
			} else {
				cout << "No\n";
			}
		}
	}
	return 0;
}
```

---

