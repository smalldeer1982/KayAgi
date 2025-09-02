# [ABC298C] Cards Query Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_c

$ 1 $ から $ N $ までの番号がついた $ N $ 個の空の箱と、何も書かれていない無数のカードがあります。  
 $ Q $ 個のクエリが与えられるので、順番に処理してください。クエリは次の $ 3 $ 種類のいずれかです。

- `1 i j` $ \colon $ カードを $ 1 $ 枚選んで数 $ i $ を書き込み、そのカードを箱 $ j $ に入れる
- `2 i` $ \colon $ 箱 $ i $ に入っているカードに書かれた数を**昇順で**すべて答える
- `3 i` $ \colon $ 数 $ i $ が書かれたカードが入っている箱の番号を**昇順で**すべて答える
 
ただし、以下の点に注意してください。

- $ 2 $ 番目の形式のクエリにおいては、箱 $ i $ の中に同じ数が書かれたカードが複数枚あるときは、入っている枚数と同じ回数だけその数を出力する
- $ 3 $ 番目の形式のクエリにおいては、数 $ i $ が書かれたカードが同じ箱に複数枚入っている場合でも、その箱の番号は $ 1 $ 度だけ出力する

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1 $ 番目の形式のクエリについて、
  - $ 1\ \leq\ i\ \leq\ 2\ \times\ 10^5 $
  - $ 1\ \leq\ j\ \leq\ N $
- $ 2 $ 番目の形式のクエリについて、
  - $ 1\ \leq\ i\ \leq\ N $
  - このクエリが与えられる時点で箱 $ i $ にカードが入っている
- $ 3 $ 番目の形式のクエリについて、
  - $ 1\ \leq\ i\ \leq\ 2\ \times\ 10^5 $
  - このクエリが与えられる時点で数 $ i $ が書かれたカードが入っている箱が存在する
- 出力するべき数は合計で $ 2\ \times\ 10^5 $ 個以下
- 入力はすべて整数
 
### Sample Explanation 1

クエリを順に処理していきます。 - カードに $ 1 $ を書き込み、箱 $ 1 $ に入れます。 - カードに $ 2 $ を書き込み、箱 $ 4 $ に入れます。 - カードに $ 1 $ を書き込み、箱 $ 4 $ に入れます。 - 箱 $ 4 $ に入っているカードに書かれた数は $ 1,\ 2 $ です。 - $ 1,\ 2 $ の順に出力してください。 - カードに $ 1 $ を書き込み、箱 $ 4 $ に入れます。 - 箱 $ 4 $ に入っているカードに書かれた数は $ 1,\ 1,\ 2 $ です。 - $ 1 $ を $ 2 $ 度出力することに注意してください。 - 数 $ 1 $ が書かれたカードが入っている箱は箱 $ 1,\ 4 $ です。 - 箱 $ 4 $ には数 $ 1 $ が書かれたカードが $ 2 $ 枚入っていますが、$ 4 $ は $ 1 $ 回しか出力しないことに注意してください。 - 数 $ 2 $ が書かれたカードが入っている箱は箱 $ 4 $ です。

## 样例 #1

### 输入

```
5
8
1 1 1
1 2 4
1 1 4
2 4
1 1 4
2 4
3 1
3 2```

### 输出

```
1 2
1 1 2
1 4
4```

## 样例 #2

### 输入

```
1
5
1 1 1
1 2 1
1 200000 1
2 1
3 200000```

### 输出

```
1 2 200000
1```

# 题解

## 作者：_Ad_Astra_ (赞：2)

观察题面，有两种操作：将每个箱子中的球按升序**不去重**输出，以及将每种球所在的箱子编号升序**去重**输出。不难想到，前者可以使用 `multiset`，后者则可以使用 `set`。由于总操作数 $\le 2 \times 10^5$，因此总大小也不超过 $2 \times 10^5$。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
multiset<int>s1[200010];
set<int>s2[200010];
map<int,int>mp[200010];
signed main()
{
	cin>>n>>q;
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x,id;
			cin>>x>>id;
			s1[id].insert(x);
			s2[x].insert(id);
		}
		else if(op==2)
		{
			int id;
			cin>>id;
			for(auto i:s1[id])cout<<i<<" ";
			cout<<endl;
		}
		else
		{
			int x;
			cin>>x;
			for(auto i:s2[x])cout<<i<<" ";
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

对于询问，需要排序，所以使用 `set/multiset`。

对于第一种询问：查询箱子里面有哪些球，不去重，所以用 `multiset`，此处定义为 $s$。

对于第二种询问：查询求在哪些箱子里面，要去重，所以用 `set`，此处定义为 $S$。

对于操作 `1 i j` 直接进行 `S[i].insert(j),s[j].insert(i)` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
set<int> S[maxn];
multiset<int> s[maxn];
int n,q;
int main(){
	scanf("%d%d",&n,&q);
	while(q--){
		int op,i,j;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&i,&j);
			S[i].insert(j);
			s[j].insert(i);
		} else if(op==2){
			scanf("%d",&i);
			for(auto it=s[i].begin();it!=s[i].end();++it)
				printf("%d ",(*it));
			puts("");
		} else{
			scanf("%d",&i);
			for(auto it=S[i].begin();it!=S[i].end();++it)
				printf("%d ",(*it));
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：zajasi (赞：1)

## 题意
现在有 $3$ 个操作。

* `1 x y`：将 $x$ 号球放入 $y$ 中。
* `2 x`：询问第 $i$ 个箱子里所有的球的编号。升序。
* `3 x`：询问第 $i$ 号球所在的所有箱子。升序。

注意：对于操作 $3$ 需去重。而对于操作 $2$ 则不要。
## 解题思路
维护很多个 multiset 记录每个箱子里球的信息。

维护很多个 set 记录每个球在箱子里的信息。

对于操作 $1$，更新 multiset 和 set.

对于操作 $2$，输出 multiset。

对于操作 $3$，输出 set。

详见代码
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
int t;
int op;
int x,y;
multiset<int> s[200020];
set<int> ss[200020];
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    cin>>t;
    while(t--){
        cin>>op;
        if(op==1){
            cin>>x>>y;
            s[y].insert(x);//箱子里的球
            ss[x].insert(y);//球所在的箱子
        }
        else if(op==2){
            cin>>x;
            for(auto&i:s[x]){//输出 x 箱子中的球
                cout<<i<<" ";
            }
            cout<<"\n";
        }
        else{
            cin>>x;
            for(auto&i:ss[x]){//输出 x 号球所在的箱子
                cout<<i<<" ";
            }cout<<"\n";
        }
    }
    return 0;
}

```

---

## 作者：liangbob (赞：0)

### AT_abc298_c 题解

#### 思路分析

看到题解区里的各位大佬都直接上 set 和 multiset，我这里说一个用两组 set 和一组 map 的算法。

首先，题目要求记录哪些盒子装了某个数并要求升序去重输出。这个简单，用一组 set 记录每个数装在的盒子，然后每装一次，设把 $x$ 装进 $y$，那么就将 $y$ 往第 $x$ 个 set 里面装，然后每次询问直接输出即可。

其次，对于另外一种询问，要求求出盒子里面装了哪些数并要求升序排序。我们可以参照上述的思路，把数存进一组 set 里面。但是，set 会自动去重，所以还要再开一组 map，记录每个盒子里面的每个数的出现次数。在操作放入时，设把 $x$ 装进 $y$，那么就将 $x$ 往第 $y$ 个 set 里面装，同时让第 $y$ 个 map 中 $x$ 项的值加一。在询问输出时，先遍历所有数，然后对于每个数，重复输出相应次数次就可以了。

依照上述步骤实现即可。

#### 关键代码

```cpp
set <int> a[N]; //用于记录哪些盒子装了某个数的 set
set <int> b[N]; //用于记录盒子里面装了哪些数的 set
map <int, int> ca[N];//用于记录每个盒子里面的每个数的出现次数的 map

int main()
{
	int n, q;
	cin >> n >> q;
	while(q--)
	{
		int op;
		cin >> op;
		if(op == 1) //插入操作
		{
			int x, y;
			cin >> x >> y;
			a[y].insert(x); //记录盒子里面装了哪些数：将 x 往第 y 个 set 里面装
			ca[y][x]++; //记录次数
			b[x].insert(y); //记录哪些盒子装了某个数：将 y 往第 x 个 set 里面装
		}
		if(op == 2) 
		{
			int g;
			cin >> g; 
			for(auto i = a[g].begin();i != a[g].end();i++) //先遍历所有数
			{
				int p = *i; //根据迭代器获取值
				for(int j = 1;j <= ca[g][p];j++) //对于每个数，重复输出相应次数次
				{
					cout << p << " ";
				}
			}
			cout << endl;
		}
		if(op == 3) //哪些盒子装了某个数
		{
			int g;
			cin >> g; 
			for(auto i = b[g].begin();i != b[g].end();i++) //直接遍历输出
			{
				int p = *i; //根据迭代器获取值
				cout << p << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
```



---

## 作者：Jerry_heng (赞：0)

（一）

由于要从小到大输出，所以用两个二维优先队列 $ans1$ 和 $ans2$ 对应操作 $2$ 和 $3$。

注意：操作三要去重！这里用 map 解决。

（二）

AC 代码（略卡常）。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
priority_queue<int,vector<int>,greater<int> >ans1[200001],ans2[200001],t;
map<int,bool>mp[200001];
int m,n;
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int op,x,y;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&x,&y);
			ans1[y].push(x);
			if(!mp[x][y])ans2[x].push(y),mp[x][y]=1;
		}
		if(op==2){
			scanf("%d",&x);
			t=ans1[x];
			while(!t.empty()){
				printf("%d ",t.top());
				t.pop();
			}
			printf("\n");
		}
		if(op==3){
			scanf("%d",&x);
			t=ans2[x];
			while(!t.empty()){
				printf("%d ",t.top());
				t.pop();
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：DHeasy (赞：0)

一道很好的复习数据结构的题。

对于第 $1$ 个问答（既第 $2$ 种操作），我用一个小根堆（优先队列，$\text{priority\_queue}$）来储存第 $i$ 个盒子的卡牌。

对于第 $2$ 个问答（既第 $3$ 种操作），我用一个 $\text{set}$ 来储存编号为 $i$ 个卡牌在哪些盒子里。  
由于 $\text{set}$ 会自动去重，也会自动排序，所以直接存和输出了。

#### 怎么存呢？

先看一下我开的变量：

```cpp
set<int>q2[200010];
priority_queue<int,vector<int>,greater<int> >q1[200010],k;
```

其中 $q_1[i]$ 表示第 $i$ 个盒子里的卡牌（小根堆，升序排序），$q_2[i]$ 表示编号为 $i$ 个卡牌在的盒子的编号（也是升序排序），$k$ 是输出用做过渡的。

设要将编号为 $a$ 的卡牌放在编号为 $b$ 的盒子里，则：

```cpp
q1[b].push(a);
q2[a].insert(b);
```

看不懂的结合定义再理解一遍。

会存了，询问就直接输出了。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
set<int>q2[200010];
priority_queue<int,vector<int>,greater<int> >q1[200010],k;
int main(){
	scanf("%d%d",&n,&q);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int a,b;
			scanf("%d%d",&a,&b);
			q1[b].push(a);
			q2[a].insert(b);
		}
		else if(op==2){
			int a;
			scanf("%d",&a);
			while(!q1[a].empty()){
				k.push(q1[a].top());
				printf("%d ",q1[a].top());
				q1[a].pop();
			}
			putchar('\n');
			while(!k.empty()){
				q1[a].push(k.top());
				k.pop();
			}
		}
		else{
			int a;
			scanf("%d",&a);
			for(set<int>::iterator it=q2[a].begin();it!=q2[a].end();it++) printf("%d ",*it);
			putchar('\n');
		}
	}
	return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[ABC298C Cards Query Problem](https://www.luogu.com.cn/problem/AT_abc298_c)。

有趣的题目，看到了各种奇妙的做法。

## 思路

作为 ABC 的 C 题，这道题是一个简单的模拟，考验选手对 STL 的使用能力。

在 STL 中，我们有两种数据结构：set（不可重有序集合）和 multiset（可重有序集合）。

我们可以声明 $n$ 个 set，记录装有 $1\sim n$ 的盒子。

再声明 $n$ 个 multiset，记录第 $1\sim n$ 的盒子装有的卡片。

由于 set 和 multiset 内定的特定属性，可以自动去重或排序，当询问时，直接按序述处即可。

当加入一张卡片的时候，我们令卡片的编号为 $c
_i$，令箱子的编号为 $b_i$，就将卡片的编号 $c_i$ 加入第 $b_i$ 个 multiset，将箱子的编号 $b_i$ 加入第 $c_i$ 个 set 中即可。

查询时，按需输出 set 或 multiset 中的内容即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q;
set<int> q2[200005];
multiset<int> q1[200005];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int a, b;
      cin >> a >> b;
      q1[b].insert(a);
      q2[a].insert(b);
    } else if (op == 2) {
      int a;
      cin >> a;
      for (auto c : q1[a]) cout << c << ' ';
      cout << '\n';
    } else {
      int a;
      cin >> a;
      for (auto c : q2[a]) cout << c << " ";
      cout << '\n';
    }
  }
  return 0;
}
```
我的 [AC 记录](https://www.luogu.com.cn/record/108252618)。

---

## 作者：atomic_int (赞：0)

## 题意：
有 $n$ 个盒子，$q$ 次如下操作：
- `1 i j` 把编号为 $j$ 的球放入第 $i$ 个盒子
- `2 i` 升序输出第 $i$ 个盒子所有球的编号
- `3 i` 升序输出包含 $i$ 号球的盒子编号

## 分析：
对于 $1$ 操作，用 `multiset` 保存即可，保证升序且可以重复，便于 $2$ 操作输出。对于 $3$ 操作，我们只需要使用 `set` 在进行 $1$ 操作时统计 $i$ 号球所在的盒子编号，且自动去重。

## 代码：
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<multiset<int>> a(n + 1);
    vector<set<int>> s(2e5 + 10);

    while (q--) {
        int op, x, y;
        cin >> op >> x;

        if (op == 1) {
            cin >> y;
            a[y].insert(x);
            s[x].insert(y);
        } else if (op == 2) {
            for (auto i : a[x]) {
                cout << i << ' ';
            }
            cout << '\n';
        } else {
            for (auto i : s[x]) {
                cout << i << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}

```

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定 $n$ 个盒子，你需要满足一下三种操作：

$1\ i\ j$，把数字 $i$ 扔到盒子 $j$ 里面；

$2\ i$，查询盒子 $i$ 里面的数字，按升序输出；

$3\ i$，查询数字 $i$ 出现在的盒子编号，按升序输出。（**若多个同一数字出现在一个盒子，那么这个盒子编号只输出一次**。）

### 题目分析：

我们对颜色和盒子分别开个 `vector`，然后操作 $1$ 时，我们只需要分别往颜色和盒子的 `vector` 内丢就好。对于操作 $2$，我们只需要对此盒子内的数字进行排序；对于操作 $3$，我们只需要先排序，然后去重，操作类似离散化，然后输出就行。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
#define pd(x) push_back(x)
#define all(x) x.begin(),x.end()
//===
//缺省源
//IO::WL是输出加换行
//===
vector<int> col[N],a[N];
int n,m;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	while(m--){
		int opt;cin>>opt;
		if(opt==1){
			int x,y;cin>>x>>y;
			col[x].pd(y);
			a[y].pd(x);
		}else if(opt==2){
			int x;cin>>x;
			sort(all(a[x]));
			for(auto y:a[x])IO::WS(y);
			putchar('\n');
		}else{
			int x;cin>>x;
			sort(all(col[x]));
			auto p=unique(all(col[x]));
			col[x].erase(p,col[x].end());
			for(int i=0;i<col[x].size();i++)IO::WS(col[x][i]);
			putchar('\n');
		}
	}return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc298_c)       
比较好的 set 练手题。        
题面中，对于第二和第三操作，都是升序输出，我们可以想到用 set 来维护。          
第二个操作不能去重，我们使用 multiset，第三个直接用 set。         
设 $s1$ 为 multiset，$s2$ 为 set，则有：$s1_{i}$ 为第 $i$ 个盒子下所有数字的升序排列；$s2_i$ 为数字 $i$ 在哪些盒子里出现过，升序排列。            
对于第一个操作，我们插入两次就可以了。       
[CODE](https://www.luogu.com.cn/paste/7g6t23uw)

---

