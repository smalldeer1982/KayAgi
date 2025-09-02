# Bus of Characters

## 题目描述

在一辆公交车中有 $n$ 排座位，每一排有两个座位。第 $i$ 排的两个座位的宽度均为 $w_i$ 。所有的 $w_i$ 互不相同。

初始时，公交车是空的。接下来会依次停靠 $2n$ 个站，每一站将上来一名乘客。乘客分为两类：
- 内向者：此类乘客总是会选择两个座位都是空的那一排就坐，如果有多排都是空的，他将会选择 $w_i$ 最小的那一排中任意一个空座坐下。
- 外向者：此类乘客总是会选择已有一人就坐（当然是内向者）的那一排，如果有多排都满足条件，他会选择 $w_i$ 最大的那一排的空座坐下。

现在给定每一排的宽度 $w_i$ 以及乘客上车的顺序。请确定每一个乘客将会选择哪一排坐下。

## 说明/提示

在第一个样例中：

第1名乘客（内向者）选择了第2排（由于它的宽度最小）。

第2名乘客（内向者）选择了第1排（由于它是唯一的没有人坐的那排）。

第3名乘客（外向者）选择了第1排（由于它正好是有一个人落座，并且宽度最大）。

第4名乘客（外向者）选择了第2排（由于它是唯一的有空座的那排）。

## 样例 #1

### 输入

```
2
3 1
0011
```

### 输出

```
2 1 1 2 
```

## 样例 #2

### 输入

```
6
10 8 9 11 13 5
010010011101
```

### 输出

```
6 6 2 3 3 1 4 4 1 2 5 5 
```

# 题解

## 作者：zzx114514 (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/CF982B)
## 题目大意
在一辆公交车中有 $n$ 排座位，每一排有两个座位。第 $i$ 排的两个座位的宽度均为 $w_i$。所有的 $w_i$ 互不相同。  
初始时，公交车是空的。接下来会依次停靠 $2n$ 个站，每一站将上来一名乘客。乘客分为两类：  
内向者：此类乘客总是会选择两个座位都是空的那一排就坐，如果有多排都是空的，他将会选择 $w_i$ 最小的那一排中任意一个空座坐下。  
外向者：此类乘客总是会选择已有一人就坐（当然是内向者）的那一排，如果有多排都满足条件，他会选择 $w_i$ 最大的那一排的空座坐下。  
现在给定每一排的宽度 $w_i$ 以及乘客上车的顺序。请确定每一个乘客将会选择哪一排坐下。
## 解题思路
本题考察堆的数据结构。堆是一种能快速找出最值的数据结构，具体[可看这里](https://baike.baidu.com/item/%E5%A0%86/20606834)。  
我们开两个堆，一个大根堆，一个小根堆，分别存储外向者的首选座位和内向者的首选座位，堆顶就是最优选择。  
初始由于所有座位都空着，所有座位都分给内向者，每次坐座位，将堆顶人数加 $1$，如果堆顶还剩一个座位，就将其分给外向者，如果没座位就弹出。  
我个人习惯使用 `STL` 库中的优先队列来实现堆，具体思路请看代码。
## 解题代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,w;
string s;
struct Sit
{
	int w,s;//定义座位结构体，w表示宽度，s表示编号 
};
struct cmpin
{
	bool operator()(Sit a,Sit b) const
	{
		return a.w>b.w;//重载括号运算符，实现小根堆，注意要反过来，小根堆要用大于号 
	}
};
struct cmpout
{
	bool operator()(Sit a,Sit b) const 
	{
		return a.w<b.w;//同上，实现大根堆 
	}
};
priority_queue<Sit,vector<Sit>,cmpin> in;//内向者 
priority_queue<Sit,vector<Sit>,cmpout> out;//外向者 
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>w;
		in.push(Sit{w,i});//将座位都分给内向者 
	}
	cin>>s;
	for (int i=0;i<s.size();i++)
	{
		if (s[i]=='0')//如果上来的是内向者 
		{
			cout<<in.top().s<<' ';//输出堆顶编号 
			out.push(in.top());//由于堆顶坐了一个人，另一个座位必是外向者坐，将其分给外向者 
			in.pop();//由于堆顶坐了一个人，另一个座位必不是内向者坐，将堆顶弹出 
		}
		else//如果上来的是外向者 
		{
			cout<<out.top().s<<' ';//同上
			out.pop();
		}
	}
	return 0;//华丽的结尾 
}

```


---

## 作者：yeshubo_qwq (赞：5)

STL大法好！

这题我们用两个堆（即 priority_queue 优先队列），用一个小根堆存内向的人可以坐的位置的宽度，再用一个大根堆存外向的人可以坐的位置的宽度。

用堆的好处：1.最大（最小）的元素在堆顶，方便此题迅速找到乘客的座位；2.每次 pop 操作删除的元素正好是堆顶坐过的乘客座位。

然后，模拟一遍乘客上车的过程就可以了。

代码实现：不想写结构体加重载运算符 ~~（话说其他题解都是结构体）。~~ 但是，不把座位的宽度和序号用结构体存一起也是可以的。因为题目保证宽度不相同，所以，我们只需要一个 map 存宽度对用的序号就行了。

附上带注释的详细代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,x;
char s[400005];//注意乘客人数是n*2，所以数组要开两倍大小。 
priority_queue<int,vector<int>,greater<int> > q;//内向乘客（小根堆） 
priority_queue<int> p;//外向乘客（priority_queue默认大根堆） 
map<int,int> a;//存宽度对应的序号 
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&x),a[x]=i,q.push(x);//初始没坐过全是内向乘客的位置 
	scanf("%s",s+1);
	for(i=1;i<=n*2;i++){
		if(s[i]=='0')x=q.top(),q.pop(),p.push(x);//内向乘客坐上去以后变成供外向乘客坐的位置 
		else x=p.top(),p.pop();//外向乘客上去后座位满了，不用二次进堆 
		printf("%d ",a[x]);
	}
	return 0;
}
```


---

## 作者：xyta (赞：2)

谢谢管理员大大给过
那我们就来研究研究吧。

 先看题目 
 
[题目传送门](https://www.luogu.com.cn/problem/CF982B)

 我们今天就来学习一下 STL 里的优先队列。

不会优先队列的朋友们可以参考这个链接 

[优先队列讲解](https://xyt.blog.luogu.org/stl-you-xian-dui-lie)

# AC 优先队列代码
我们的思路就是定义两个优先队列，一个存储内向（从小到大），一个存储外向（从大到小）。一开始将数据输入内向队列，接着每上车一个，就将内向队列顶部删除插入到外向中，接着外向遍历之后删除即可。具体看代码 ：
```cpp
#include<iostream>
#include<string>
#include<queue>//队列头文件 
using namespace std;
struct node{//结构体 
	int ans;
	int w;
};
struct cmp1{//从大到小 
	bool operator ()(node a,node b)
	{
		return a.w>b.w;
	}
};
struct cmp2{//从小到大 
	bool operator ()(node a,node b)
	{
		return a.w<b.w;
	}
};
priority_queue <node,vector<node>,cmp1> q1;//内向 
priority_queue <node,vector<node>,cmp2> q2;//外向 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		q1.push(node{i,x});//存储进入内向优先队列 
	}
	string a;//01字符串 
	cin>>a;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='0')//如果内向 
		{
			if(!q1.empty())//其实这题不用，好习惯。 
			{
				cout<<q1.top().ans<<" ";//输出顶部id 
				q2.push(q1.top());//插入外向优先队列中 
				q1.pop();//删除 
			}
		}
		else
		{
			if(!q2.empty())//同上 
			{
				cout<<q2.top().ans<<" ";//输出顶部 
				q2.pop();//删除 
			}
		}
	}
	return 0;
}//就这么简单完毕！ 
```
写的不好，望大佬勿喷！

---

## 作者：wwwop (赞：2)

首先要用结构体存起来。
```
#include <bits/stdc++.h>
using namespace std;
struct B
{
	int w,id;//宽度和编号
}a[200010];
```
然后要开两个优先队列，分别存储适合内向的和适合外向的。
```
//写好排序规则
struct cmp1
{
	bool operator () (B a,B b)
	{
		return a.w>b.w;
	}
};
struct cmp2
{
	bool operator () (B a,B b)
	{
		return a.w<b.w;
	}
};
priority_queue <B,vector<B>,cmp1> q1;//内向的按Wi从小到大
priority_queue <B,vector<B>,cmp2> q2;//外向的按Wi从大到小
```
之后根据输入处理并输出答案。
```
int main()
{
	string s;
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		a[i].id=i;
		cin>>a[i].w;
		q1.push(a[i]);
	}
	cin>>s;
	int m=2*n;
	for(i=0;i<m;i++)
	{
		if(s[i]=='0')
		{
			//如果是内向的，输出堆顶、删除堆顶，并装进适合外向的堆里
         		B t=q1.top();
			q1.pop();
			q2.push(t);
			cout<<t.id<<" ";
		}
		else
		{
			//如果是外向的，输出堆顶、删除堆顶
        	 	B t=q2.top();
			q2.pop();
			cout<<t.id<<" ";
		}
	}
	return 0;
}
```
谢谢大家，本片题解到此结束。

---

## 作者：爬行者小郑 (赞：2)

## STL:priority_queue做法

我们可以利用两个优先队列，模拟一下内向人可以坐哪些排，以及外向人可以做哪些排。

在落座的过程中，我们要注意内向人做过的排数还可以给外向人坐。

code：
```cpp
#include <iostream>//基本输入输出 
#include <queue>//一会要用到优先队列 
using namespace std;
const int MAXN=200005;
int vis[MAXN];//记录当前这一排坐的人数 
struct Node
{
	int id,w;//分别是排的编号和宽度 
};
struct cmpmi//按照w从小到大 
{
	bool operator()(Node a,Node b)
	{
		return a.w>b.w;
	}
};
struct cmpma//按照w从大到小 
{
	bool operator()(Node a,Node b)
	{
		return a.w<b.w;
	}
};
priority_queue<Node,vector<Node>,cmpmi>q;//内向的 
priority_queue<Node,vector<Node>,cmpma>q2;//外向的 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		Node tmp;
		tmp.id=i;tmp.w=x;
		q.push(tmp);//先放入这排座位的信息 
		q2.push(tmp);
	}
	string op;
	cin>>op;
	for(int i=0;i<op.size();i++)//依次入座 
	{
		Node tmp;
		if(op[i]=='0')//内向的 
		{
			while(!q.empty())
			{
				tmp=q.top();//取出宽度最小的 
				if(vis[tmp.id]==0)//如果没人 
				{
					cout<<tmp.id<<" ";//可以取 
					vis[tmp.id]++;//做进去一个人 
					q.pop(); 
					q2.push(tmp);//把这排座位放到外向的队列里面 
					break;//退出 
				}
				else q.pop();//有人pop掉再找下一个 
			}
		}
		else//外向同理 
		{
			while(!q2.empty())
			{
				tmp=q2.top();
				if(vis[tmp.id]==1)
				{
					cout<<tmp.id<<" ";
					vis[tmp.id]++;
					q2.pop();//这里已经坐满了，不用管这排了 
					break;
				}
				else q2.pop();
			}
		}
		//cout<<"in"<<endl;
	}
	return 0;//养成好习惯 
}
```
谢谢大家，优先队列在竞赛中使用十分广泛


---

## 作者：Reanap (赞：2)

#       一道优秀的“栈”

内向的每次要选一个没人的最窄的座位，而外向的要选一个有人的最宽的座位。我们可以建立一个栈，将内向者入栈，遇到外向者则从栈顶取走一个（因为外向者要求座位尽可能宽）

手写数据结构：
      
      

------------

      #include <cstdio>
      #include <algorithm>
      using namespace std;
      const int MAXN = 1e5 + 5;
      int stack[MAXN * 2];
      char str[MAXN * 5];
      struct node {
          int num,s;
      } a[MAXN * 5]; //结构体，记录宽度即顺序（方便排序后使用）
      bool cmp(node x,node y) {
          return x.num < y.num;
      }
      int main() {
          int n;
          scanf("%d",&n);
          for (int i = 1; i <= n; ++i) scanf("%d",&a[i].num,a[i].s = i); //缩进（懒）
          stable_sort(a + 1 , a + 1 + n , cmp);
          //stable_sort相当于归并排序，在数字大小相同不会改变原来顺序
          //sort并不稳定（然而sort也能过）
          //内向者选最窄的，排序后只需要选没选过的第一个
          int p = 1,t = 0;//t表示栈顶，p表示内向者选到哪了
          scanf("%s",str);
          for (int i = 0; i <= 2 * n - 1; ++i) {
              if(str[i] == '1') {
                  printf("%d ",stack[t]);
                  t --; //出栈并输出
              } else if(str[i] == '0') {
                  printf("%d ",a[p].s);
                  stack[++t] = a[p].s;
                  p++; //入栈
              }
          }
          return 0; // 结束主函数
      }

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF982B)
#### 这道题用优先队列模拟要比用结构体并使用重载运算符要简单得多。
### 思路如下
这道题的每一排座位都有三种状态：没人做，有一个内向的人坐，或坐满了。

所以首先用一个 map 将与宽度对应的编号存起来，然后用两个优先队列将每一排座位的第一和第二种状态存起来，第三种状态则不用管它。因为内向的人喜欢坐编号小的位置，所以第一个优先队列需要从小往大排，而外向的人喜欢坐编号大的位置，所以第二个优先队列需要从大往小排。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
string s;
priority_queue<int,vector<int>,greater<int> >q;
priority_queue<int,vector<int> >p;//两个优先队列
map<int,int>mp;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		x;
		cin>>x;
		mp[x]=i;
		q.push(x);//进入没人坐的状态
	}
	cin>>s;
	for(int i=0;i<2*n;i++){
		if(s[i]=='0'){
			x=q.top();
			q.pop();
			p.push(x);//进入坐了一个内向的人的状态
		}
		else{
			x=p.top();
			p.pop();//坐满了人，不必再管
		}
		printf("%d ",mp[x]);将宽度对应编号输出
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF982B)

搞两个优先队列，一个大根堆，一个小根堆。注意默认是大根堆，加 greater 是小根堆，别搞错。

大根堆记录外向者的最优选择，小根堆记录内向者的最优选择。

先用 pair 把所有行全部加进小根堆里面。

每来一个内向者就弹出小根堆顶的元素插入大根堆里面，每来一个外向者就弹出大根堆顶的元素。

最后输出弹出的元素。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
priority_queue<pii > p1;//记录外向者
priority_queue<pii, vector<pii>, greater<pii > > p0;//记录内向者
int n, w; pii a;
int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> w;
		pii p; p.first = w, p.second = i;
		p0.push(p);//插入数据
	}
	for (int i = 1; i <= n * 2; i++){
		char c; cin >> c;
		if (c == '0'){
			a = p0.top();
			p1.push(a); p0.pop();
		}
		else{a = p1.top(); p1.pop();}
		cout << a.second << " ";//在线处理
	}
	return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF982B Bus of Characters](https://www.luogu.com.cn/problem/CF982B) 题解

我看到题解区里主要都是用堆来解的，作为一个没学过堆（~~其实是忘了~~）的蒟蒻，我今天就来写一篇栈的题解。

## 思路
由于内向者总会选择一个 $w_i$ 最小的空排，所以我们可以对 $w$ 数组从小到大排序，每次取出最小的空排，输出该排的编号并入栈。

外向者每次会选 $w_i$ 最大的有内向者坐的排，而内向者坐的排已经入栈了，根据栈先进后出的原理，栈顶一定是当前外向者的选择，输出栈顶编号后弹出即可。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

struct node
{
    int w, id;
}a[200005];

stack <int> s;

bool cmp(node x, node y)
{
    if (x.w == y.w)
        return x.id < y.id;
    else
        return x.w < y.w;
}

int main()
{
    int n, t = 1;
    char ch;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].w;
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= 2 * n; i++)
    {
        cin >> ch;
        if (ch == '0')
        {
            cout << a[t].id << " ";
            s.push(a[t].id);
            t++;
        }
        else if (ch == '1')
        {
            cout << s.top() << " ";
            s.pop();
        }
    }
    return 0;
}
```

---

## 作者：haokee (赞：0)

## 思路

既然每次都是坐在最值上面，那么我们就可以定义两个优先队列，分别存上内向者和外向者的座位信息，需要的时候就可以 `top` 出来最大或最小的座位。

由于堆顶的值 `top` 出来实际上是座位的宽度，因此通过所有的 $w_i$ 都不相同的特性，我们可以使用 `map` 或者 `unordered_map` 来存储位置编号。

**优先队列介绍：**[Oi - Wiki](https://oi-wiki.org/lang/csl/container-adapter/#%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97)，[Cppreference](https://en.cppreference.com/w/cpp/container/priority_queue)，本质上就是一个堆。

## 代码

```cpp
#include <iostream>
#include <queue>  // 优先队列
#include <unordered_map>  // 哈希表

using namespace std;

int n, v;
char c;
priority_queue<int, vector<int>, greater<int>> q1;  // 小根堆，存储内向者
priority_queue<int, vector<int>, less<int>> q2;  // 小根堆，存储内向者
unordered_map<int, int> f;  // 哈希表

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> v;
    f[v] = i, q1.push(v);  // 存储进小根堆以及哈希表
  }
  for (int i = 1; i <= n << 1; ++i) {
    cin >> c;
    if (c == '0') {  // 内向者
      cout << f[q1.top()] << ' ';  // 输出堆鼎的编号
      q2.push(q1.top()), q1.pop();  // 这个位置只能坐外向者了
    } else {  // 外向者
      cout << f[q2.top()] << ' ';  
      q2.pop();  // 这个位置满了
    }
  }
  return 0;
}
```

## 思路 2

我们可以想，内向者既然选了一个最小的位置，那么最后一个内向者必然坐着有人当中最大的位置，然后外向者正好需要选择有人当中最大的位置，那不就是单调栈吗？

**单调栈介绍：**[Oi - Wiki]([单调栈 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/ds/monotonous-stack/))，本质上就是满足一定顺序的栈。

## 代码

```cpp
#include <iostream>
#include <algorithm>  // sort
#include <stack>  // 栈
#include <unordered_map>  // 哈希表

using namespace std;

const int kMaxN = 2e5 + 1;

int a[kMaxN], n, p;
char c;
stack<int> s;
unordered_map<int, int> f;

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i], f[a[i]] = i;  // 读入并存进哈希表
  }
  sort(a + 1, a + n + 1);  // 按座位宽度排序
  for (int i = 1; i <= n << 1; ++i) {
    cin >> c;
    if (c == '0') {
      cout << f[a[++p]] << ' ';  // 选择下一个座位
      s.push(a[p]);  // 这个座位坐了内向者
    } else {
      cout << f[s.top()] << ' ';  // 输出栈顶元素
      s.pop();  // 出栈
    }
  }
  return 0;
}
```

---

