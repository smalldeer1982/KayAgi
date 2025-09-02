# [ABC217E] Sorting Queries

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc217/tasks/abc217_e

空の列 $ A $ があります。クエリが $ Q $ 個与えられるので、与えられた順番に処理してください。  
 クエリは次の $ 3 $ 種類のいずれかです。

- `1 x` : $ A $ の最後尾に $ x $ を追加する。
- `2` : $ A $ の最初の要素を出力する。その後、その要素を削除する。このクエリが与えられるとき、$ A $ は空でないことが保証される。
- `3` : $ A $ を昇順にソートする。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ x\ \leq\ 10^9 $
- クエリ `2` が与えられるとき、$ A $ は空でない。
- 入力は全て整数である。

### Sample Explanation 1

入力例 $ 1 $ において、 $ i $ 番目のクエリを処理した後の $ A $ の状態を $ i $ 行目に示すと以下のようになります。 - $ (4) $ - $ (4,\ 3) $ - $ (4,\ 3,\ 2) $ - $ (4,\ 3,\ 2,\ 1) $ - $ (1,\ 2,\ 3,\ 4) $ - $ (2,\ 3,\ 4) $ - $ (2,\ 3,\ 4,\ 0) $ - $ (3,\ 4,\ 0) $

### Sample Explanation 2

入力例 $ 2 $ において、 $ i $ 番目のクエリを処理した後の $ A $ の状態を $ i $ 行目に示すと以下のようになります。 - $ (5) $ - $ (5,\ 5) $ - $ (5,\ 5,\ 3) $ - $ (5,\ 3) $ - $ (3,\ 5) $ - $ (5) $ - $ (5,\ 6) $ - $ (5,\ 6) $ - $ (6) $

## 样例 #1

### 输入

```
8
1 4
1 3
1 2
1 1
3
2
1 0
2```

### 输出

```
1
2```

## 样例 #2

### 输入

```
9
1 5
1 5
1 3
2
3
2
1 6
3
2```

### 输出

```
5
3
5```

# 题解

## 作者：_zzzzzzy_ (赞：1)

# 思路
这里发一个不是官方题解的思路。

用一个双端队列进行存储，在排序操作时将双端队列里面的数全部加入到优先队列里面，如果是查询第一个的话优先选双端队列里面的数，如果队列是空的那就选优先队列里的第一个。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
deque<int>deq;
priority_queue<int,vector<int>,greater<int>>qp;
signed main(){
	int Q;
	cin>>Q;
	while(Q--){
		int op=0;
		cin>>op;
		if(op==1){
			int x;
			cin>>x;
			deq.push_back(x);
		}
		else if(op==2){
			if(qp.size()){
				cout<<qp.top()<<"\n";
				qp.pop();
			}
			else{
				cout<<deq.front()<<"\n";
				deq.pop_front();
			}
		}
		else{
			while(deq.size()){
				qp.push(deq.front());
				deq.pop_front();
			}
		}
	}
	return 0;
}
```

---

## 作者：DerrickLo (赞：1)

这道题我们只需要创建一个优先队列和一个普通队列即可。

对于 $1$ 操作，只需要将 $x$ 放入普通队列中即可。

对于 $3$ 操作，只需要将普通队列中的所有数都放入优先队列中即可，优先队列可以自动排序。

而对于 $2$ 操作，若优先队列不为空，则输出优先队列开头的元素，反之则输出普通队列开头的元素。因为如果优先队列不为空，则必然执行过 $3$ 操作，此时原题中的队列开头的元素必为优先队列开头的元素，而普通队列中的元素都被插入在优先队列元素的后面了。

## 具体见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int Q,x,opt;
priority_queue<int,vector<int>,greator<int> > qu;//越小越优先的优先队列
queue<int> q;//普通队列
int main(){
	cin>>Q;
	while(Q--){
		cin>>opt;
		if(opt==1){//1操作
			cin>>x;
			q.push(x);
		}
		else if(opt==2){//2操作
			if(qu.size()){
				cout<<qu.top()<<endl;
				qu.pop();
			}
			else{
				cout<<q.front()<<endl;
				q.pop();
			}
		}
		else{//3操作
			while(q.size()){
				qu.push(q.front());//将普通队列中的数转移到优先队列中
				q.pop();
			}
		}
	}
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

提供另一个更加巧妙的解法，来自官方题解。

首先对于插入操作，插入的同时插入一个优先级，这个优先级加上一个极大值表示标记是否被排序过，所以实际插入的优先级为询问编号加上极大值，维护询问间的先后顺序，则实际顺序为较晚的询问大于较早的询问大于没有标记的询问，第二关键字为插入的值。

对于排序操作，不断将序列末尾的标记清除改为权值即可，显然这么做先后顺序不会受影响。

对于询问操作，输出队头对应的权值即可。

这些操作显然都可以用 multiset 实现，时间复杂度 $ \mathcal{O}(q\log{q}) $，喜提最劣解，可以通过。具体实现见代码。

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e9;
multiset<pair<int, int>> s;
signed main() 
{
  int q;
  cin>>q;
  for(int i=1;i<=q;i++)
  {
    int t;
    cin>>t;
    if (t==1) 
    {
      int x;
      cin>>x;
      s.insert(make_pair(i+N,x));
    } 
    else if(t==2) 
    {
      cout<<s.begin()->second<<"\n";
      s.erase(s.begin());
    } 
    else 
      while(s.size()&&s.rbegin()->first>=N) 
      {
        int val=s.rbegin()->second;
        s.erase(--s.end());
        s.insert(make_pair(val, val));
      }
  }
}
```


---

