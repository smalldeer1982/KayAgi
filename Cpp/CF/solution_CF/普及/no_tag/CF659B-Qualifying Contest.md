# Qualifying Contest

## 题目描述

有 $n$ 个人，$m$ 个区。你需要从每个区域中选出成绩最好的两个人去参加比赛，输出这两个人的名字。如果第三个人的成绩和第二个人的成绩相同，则输出 ?，保证结果不确定。

## 样例 #1

### 输入

```
5 2
Ivanov 1 763
Andreev 2 800
Petrov 1 595
Sidorov 1 790
Semenov 2 503
```

### 输出

```
Sidorov Ivanov
Andreev Semenov
```

## 样例 #2

### 输入

```
5 2
Ivanov 1 800
Andreev 2 763
Petrov 1 800
Sidorov 1 800
Semenov 2 503
```

### 输出

```
?
Andreev Semenov
```

# 题解

## 作者：Chicken_Rrog (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF659B)

看了一圈，没有用优先队列做的啊，我这里写一种用优先队列的做法吧。

## 大致题意

给出 $n$ 个人分别 $m$ 个组，求每个组的最大值和次大值。

特别的，当第二大和第三大相等时，输出问号。
## 思路

首先在输入时，我们可以把每个人的名字和分数放到对应区域的优先队列里，再遍历 $m$ 个区域，把每个区域第一大，第二大，第三大的值弹出，如果第二大的值和第三大的值相等，就输出问号，否则就输出前两名的名字。

直接看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ps,num;
string s;
int main(){
    scanf("%d%d",&n,&m);
    priority_queue<pair<int,string> > q[m+1];//pair类型自动按照first排序，所以分数放在第一位。
    for(int i=1;i<=n;++i){
        cin>>s;scanf("%d%d",&ps,&num);
        q[ps].push(make_pair(num,s));
    }
    for(int i=1;i<=m;i++){//枚举每一个区域。
        string s1=q[i].top().second;//求前三名的分数。
        q[i].pop();
        string s2=q[i].top().second;int score2=q[i].top().first;
        q[i].pop();
        if(q[i].size()){
        string s3=q[i].top().second;int score3=q[i].top().first;
        if(score2==score3) printf("?\n");
        else cout<<s1<<" "<<s2<<endl;
        }else{
            cout<<s1<<" "<<s2<<endl;
        }
    }
    return 0;
}
```


---

## 作者：ztytql (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF659B)
## Description
给定 $m$ $(1≤m≤10^4)$ 组区域共 $n$ $(2≤n≤10^5)$ 位选手，每个选手有姓名以及得分，求每个区域中得分最高的两位选手的名称。

特别地，当这组的第二大的数和第三大的数相等时，输出一个问号。
## Solution
很明显，这道题如果直接用数组存储的话肯定会炸内存，所以我们考虑使用 ```vector``` 容器进行存储。

首先定义一个结构体 ```person``` ，其中存储的是每位选手的姓名以及分数。
然后我们可以定义一个类似于二维数组的 ```vector``` 容器 ```vector<person> p[10010]``` ，这样就解决了内存的问题。然后再考虑排序。一个最容易想到的办法是将 $m$ 个区域每个区域都 ```sort``` 一遍，直接将各个区域选手的得分排名直接排了出来。

最后，输出每个区域的第一个选手以及第二个选手的姓名输出就可以了。需要特别注意的是，不仅要判断第二名选手与第三名选手的得分是否相同，还要判断这个区域的选手个数是否多于两个：如果选手个数在两名及以下，则访问 ```vector``` 容器时将会出现越界情况，需要特判一下。

看一下代码可能会理解的更清楚吧。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct person // 定义结构体
{
	string name;
	int score;
};

vector <person> p[10010]; // 定义 vector 容器

int n, m;

bool cmp(person x, person y) // 自定义排序函数
{
	return x.score > y.score;
}

signed main()
{
	cin >> n >> m;
	
	for (int i = 1 ; i <= n ; i ++)
	{
		string a;
		int x, y;
		cin >> a >> x >> y;
		p[x].push_back((person){a, y}); // 将数据存储到 vector 容器中
	}
	
	for (int i = 1 ; i <= m ; i ++) // 将 m 个区域的选手各自排序
		sort(p[i].begin(), p[i].end(), cmp);
	
	for (int i = 1 ; i <= m ; i ++)
	{
		if (p[i].size > 2 && p[i][1].score == p[i][2].score) // 这里需要特判一下元素个数，防止越界
			puts("?");
		else
			cout << p[i][0].name << " " << p[i][1].name << endl; // 输出
	}
	
	return 0;
}
```

---

## 作者：_lgh_ (赞：1)

### 思路：
提供一种比较慢但是能过的做法。题目很好理解，直接模拟即可。使用 vector 存储，然后对每一个区域进行排序，排序后分类讨论：

1. 如果刚好这个区域只有两个人，输出即可。
2. 如果这个区域里第二高的人的分数和第三高的人的分数不一样，也可以直接输出。
3. 如果这个区域里第二高的人的分数和第三高的人的分数一样，输出问号。

时间复杂度 $O(nm \log n)$ 。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,string> >q[10010];
  bool cmp(pair<int,string> a,pair<int,string> b) {
    	return a.first>b.first;
  } 
int main() {
	int n,m,w,score;string s;
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>s>>w>>score,q[w].push_back({score,s}/*也可以写成 make_pair(score,s)*/);
	for(int i=1; i<=m; i++) sort(q[i].begin(),q[i].end(),cmp);
	for(int i=1; i<=m; i++) {
		if(q[i].size()<=2) cout<<q[i][0].second<<' '<<q[i][1].second<<'\n'; 
		else {
			if(q[i][1].first==q[i][2].first) puts("?");
			else cout<<q[i][0].second<<' '<<q[i][1].second<<'\n';
		}
	} 
	return 0;	
}
```

---

## 作者：yangzd (赞：1)

# 题目大意：

有 $n$ 个人，$m$ 个区。给出 $n$ 个人的姓名（保证不相同），属于的区域，所得分数。从每个区域中选出成绩最好的两个人去参加比赛，输出这两个人的名字。如果第三个人的成绩和第二个人的成绩相同，则输出 ```?```，保证结果不确定。

# 分析：

刚开始想用个什么 STL 容器把这三个属性存进去，然后根据区域的不同对每个区域的选手的分数进行排序，最后看选手确定，输出答案。

可是没有想到应该用什么 STL 容器。

然后想到了用结构体。

结构体里面有选手的三个信息，然后对结构体进行排序。

交上去发现错了，后来发现是自己在写判断条件的时候出错了。对于判断条件与思路一定要条理清晰才不容易出错。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

struct p
{
    string s;
    long long num;
    long long scro;
}a[200005];

bool cmp(p X,p Y)
{
    if(X.num==Y.num)
        return X.scro>Y.scro;
        
    return X.num<Y.num;
}

signed main()
{
	ios::sync_with_stdio(0);
	
    long long n,m,t1,t2;
    
    string s1;
    
    cin >> n >> m;

    for(long long i=0; i<n; i++)
        cin >> a[i].s >> a[i].num >> a[i].scro;

    sort(a,a+n,cmp);

    for(long long j=1; j<=m;)
    {
        for(long long i=0; i<n; i++)
        {
            if(a[i].num==j)
            {
                if(a[i+1].num==j)
                {
                    if((a[i+2].num==j&&a[i+1].scro!=a[i+2].scro) || (a[i+2].num!=j))
                       cout << a[i].s << " " << a[i+1].s << endl;
                       
                    else
                       cout << "?" << endl;
                }
                
                else
                    cout << "?" << endl;
                    
                j++;
            }
        }
    }

    return 0;
}

```

---

## 作者：Underage_potato (赞：0)

[**传送门**](https://www.luogu.com.cn/problem/CF659B)

这道题可以用优先队列的做法。

## 题意

有 $n$ 个人，分 $m$ 个组，求每个组的最大值次大值。且当第三大的值与第二大的值相等时输出问号。

## 思路

可以用 STL 里的优先队列维护，共有 $m$ 个优先队列，当遍历到每个优先队列的时候将最大值和次大值取出，在将第三大的取出并与次大值相对比，然后输出即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<pair<int,string> > q[10100];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x,y;
		string s;
		cin>>s>>x>>y;
		q[x].push(make_pair(y,s));
	}
	for(int i=1;i<=m;i++){
		int a,b,c;
		string aa,bb;
		a=q[i].top().first,aa=q[i].top().second;
		q[i].pop();
		b=q[i].top().first,bb=q[i].top().second;
		q[i].pop();
		if(q[i].size()){
			c=q[i].top().first;
			if(b==c){
				cout<<"?"<<endl;
			}
			else{
				cout<<aa<<" "<<bb<<endl;
			}
		}
		else{
			cout<<aa<<" "<<bb<<endl;
		}
	}
	return 0;
}
/* by Underage_potato*/

```


---

## 作者：Keroshi (赞：0)

# 题目分析  
题目要求每个队选出最好的两个人去参赛， 也就是要排序。  
可以维护 $m$ 个优先队列来求出分数最高的两人。   
# 代码   
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e4+5;
// 维护m个优先队列
priority_queue<pair<int,string>> a[N];
int n,m;
string s;
int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> s;
        cin >> x >> y;
        a[x].push(make_pair(y, s));
    }
    for(int i=1;i<=m;i++){
        // 取出前三项
        int n1=a[i].top().first;
        string s1=a[i].top().second;
        a[i].pop();
        int n2=a[i].top().first;
        string s2=a[i].top().second;
        a[i].pop();
        if(a[i].size()){ 
            int n3=a[i].top().first;
            if(n3==n2) cout << "?" << endl;
            else cout << s1 << " " << s2 << endl;
        }
        else{
            cout << s1 << " " << s2 << endl;
        }
    }
    return 0;
}

```

---

## 作者：Jeremiahy (赞：0)

# 分析

可以建立一个结构体，然后开一个二维数组，读入后进行排序，再进行判断并输出，但是这样会导致 ```MLE```，所以我们考虑替换成 ```vector``` 和 ```pair```。

具体步骤如下：

1. 定义 ```vector``` 数组和比较函数（按分数从大到小）。

1. 读入并存储。

1. 对每个区进行排序。

1. 遍历每个区，如果第二名和第三名分数一样输出 ```?```，否则输出前两名的名字。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<string, int> > v[10005];//存储每个区内每个人的姓名和分数
int n, m, qu, sc;//qu为读入时所用，sc同上
string st;//同上
bool cmp(pair<string, int> a, pair<string, int> b) {
    return a.second > b.second;//按分数大小排序
}
signed main() {
	cin >> n >> m;
	for (register int i = 1; i <= n; i++) 
		cin >> st >> qu >> sc, v[qu].push_back({st, sc});//读入并存储
	for (register int i = 1; i <= m; i++)  {
		sort(v[i].begin(), v[i].end(), cmp);//排序
		if (v[i].size() > 2 && v[i][1].second == v[i][2].second)//如果出现上述情况
			puts("?");
		else	
			cout << v[i][0].first << ' ' << v[i][1].first << '\n'; 		
	}
	return 0;	
}
```


---

## 作者：dingshengyang (赞：0)

来提供目前并没有人写的 $O(n)$ 线性算法。

然而……

> 常数决定一切。

---

废话少说，我们开始。

首先，一把元素的名字、区块、得分读入，我们就把它丢进一个桶里。这个桶以区块编号为下标。用 `vector[]` 存储。

然后，显然，我们需要找出每一个区块的第一和第二。但是什么情况下需要输出问号呢？

首先，我们设当前块的第一、第二、第三名的得分分别为 $s1,s2$ 和 $s3$。

显然，$s1\ge s2\ge s3$。

现在，我们发现，当且仅当 $s2=s3$ 时，无法抉择。

为什么呢？显然，如果 $s2\not=s3$ 时也无法抉择，那么 $s1\ge s2>s3$，取 $s1$ 和 $s2$ 即可。

然后，如何求出 $s1,s2,s3$ 呢？

排序？

大可不必。

首先用擂台法求出 $s1$，及其对应的名字 $n1$。

然后再用擂台法求出 $s2$，但是替换的条件是当前名字不等于 $n1$。

然后顺便求出 $n2$。

然后再用擂台法求出 $s3$，但是替换的条件是当前名字不等于 $n1$ 且不等于 $n2$。

最后看看 $s2$ 是否等于 $s3$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
class slove_CF659B{
	private:
	static const int M = 10005;
	int n,m;
	class person{
		public:
		string name;
		int score;
		person(string _name=" ",int _score=0):name(_name),score(_score){}
	};
	vector<person>* block[M];
	public:
	slove_CF659B(){
		scanf("%d%d",&n,&m);
		for(int i = 1;i <= m;i ++)block[i] = new vector<person>(),block[i]->clear();
		for(int i = 1;i <= n;i ++)
		{
			string name;
			int belong,score;
			cin >> name;scanf("%d%d",&belong,&score);
			block[belong]->push_back(person(name,score));
		}
		for(int i = 1;i <= m;i ++){
			string best,second;
			int maxs = -0x3f3f3f3f,ok = 1;
			for(auto j:*block[i]){
				if(j.score > maxs){
					best = j.name;maxs = j.score;
				}
			}
			maxs = -0x3f3f3f3f;
			for(auto j:*block[i]){
				if(j.score > maxs && j.name != best){
					second = j.name;maxs = j.score;
				}
			}
			for(auto j:*block[i]){
				if(j.score == maxs && j.name != best && j.name != second){
					ok = 0;break;
				}
			}
			if(ok){
				cout << best << " " << second << endl;
			}else{
				cout << '?' << endl;
			}
		}
	}
};
int main() {
	slove_CF659B slover;
	return 0;
}
 
```


---

## 作者：liuyongle (赞：0)

分别考虑每个地区的参与者。

对于每个区域而言，只需要按照其得分的升序对所有参与者进行sort排序。当且仅当第二参与者和第三参与者的分数均相等时，区域答案才不一致，否则答案是该序列里的第一与第二名。

时间复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define endl "\n"

using namespace std;

struct node {
    string name;
    int score;
};

const int maxn=2*(1e5)+5;

node a[maxn];

vector<node> v[maxn];

int cmp(node x,node y) {
    return x.score > y.score;
}

int main() {
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i=0;i<maxn;i++)
        v[i].clear();
    string name;
    int pos,score;
    for(int i=0;i<n;i++) {
        cin>>name>>pos>>score;
        a[i].name=name;
        a[i].score=score;
        v[pos].push_back(a[i]);
    }
    for(int i=1;i<=m;i++) {
        sort(v[i].begin(),v[i].end(),cmp);
        if(v[i].size()>2 && v[i][1].score==v[i][2].score)
            cout<<"?"<<endl;
        else
            cout<<v[i][0].name<<" "<<v[i][1].name<<endl;
    }
    return 0;
}
```

---

