# Social Network (easy version)

## 题目描述

你知道了将来N次给你发送的消息，而聊天软件一次性只能显示与K(1≤K≤200)个人的聊天记录。

当收到一条消息时，如果与这个人的聊天记录显示在聊天软件中，就什么都不做（注意，不需要把当前聊天记录置顶）；否则，如果当前已经显示了K个聊天记录，则删除最后一个聊天记录；添加与这个人的聊天记录在列表顶端，同时其他聊天记录下移一个位置。

询问在这N条消息发送之后，你的聊天软件最终会显示与哪几个人的聊天记录。

## 样例 #1

### 输入

```
7 2
1 2 3 2 1 3 2
```

### 输出

```
2
2 1 
```

## 样例 #2

### 输入

```
10 4
2 3 3 1 1 2 1 2 3 3
```

### 输出

```
3
1 3 2 
```

# 题解

## 作者：Blunt_Feeling (赞：7)

# CF1234B1 Social Network 简易版 题解
~~STL大法好~~

本题用一个普通的队列queue便可以轻易实现

对输入的每个编号进行访问和判断：

我们首先判断输入的编号有没有在队列里，如果没有在队列里，就将该编号入队；再判断队列里有没有超过K个聊天记录，若超过了，就删除队尾元素。

访问完后，先输出队列的长度，再借助一个可变数组vector，从队首到队尾输出所有元素

在这里需要用到一些关于队列的函数，在这里科普一下~
```
que.size()//返回队列长度
que.front()//返回队首元素
que.push(x)//将x插入到队尾
que.pop()//删除队首元素
que.empty()//返回一个布尔值，判断队列是否为空
```

最后附上C++的AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans[250];
queue<int> que;
vector<int> vec;
bool check(int id)//查找队列中有没有id这个编号
{
	bool flag=false;
	int len=que.size();
	for(int i=0;i<len;i++)
	{
		if(que.front()==id)
			flag=true;
		que.push(que.front());
		que.pop();
	}
	return flag;
}
int main()
{
	cin>>n>>k;
	while(n--)
	{
		int id;
		cin>>id;//读入一个编号
		if(!check(id))//id不在队列里
		{
			que.push(id);
			if(que.size()>k)//判断队列元素的个数有没有超过K个
				que.pop();
		}
	}
   	//输出当前屏幕上显示的聊天记录个数
	cout<<que.size()<<endl;
   	//由于队列不能遍历，所以将队列所有元素都存入vector
	while(!que.empty())
	{
		vec.push_back(que.front());
		que.pop();
	}
   	//用迭代器逆序访问vector并输出
	for(vector<int>::iterator it=vec.end()-1;it!=vec.begin()-1;it--)
		cout<<*it<<' ';
	return 0;
}
```
大家有兴趣的话还可以做一下此题的升级版CF1234B2，也不难的

本蒟蒻的第一篇题解

求过 o(￣▽￣)ｄ

---

## 作者：jiangXxin (赞：3)

简述一下题意,现在有n条信息，但是你的手机只能显示m条信息，每次弹过来一条信息，它将被放在第一位，如果当前手机显示的信息大于m，那么最后一个就会被弹出，同时，每一次弹过来的信息，如果手机里面已经有这个人发的信息，那么就可以不作出改变。

思路：使用一个单调队列，每一次弹来的信息，放入队头，如果已经出现过，那么就$continue$,当队列的长度大于m，则把最后一个信息弹出。

**code:**
```cpp
    /**
    *    author:  a2954898606
    *    created: 2019/10/01 22:54:49
    **/
    #include<bits/stdc++.h>
    #define REP(A,B,I) for(int I=(A);I<=(B);I++)
    #define PER(A,B,I) for(int I=(A);I>=(B);I--)
    #define max(X,Y) ((X)<(Y)?(Y):(X))
    #define min(Y,X) ((X)<(Y)?(X):(Y))
    #define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
    #define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
    #define LL long long
    using namespace std;
    deque<int> que;
    map<int,bool> mp;
    int n,k,m;
    int main(){
        //read(1)
        //write(1)
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
     
        cin>>n>>k;
        REP(1,n,i){
            int x;
            cin>>x;
            if(mp[x]==true)continue;
            mp[x]=true;
            que.push_front(x);
            if(que.size()>=k+1){
                m=que.back();
                mp[m]=false;
                que.pop_back();
            }
        }
        cout<<que.size()<<endl;
        while(!que.empty()){
            int x=que.front();
            que.pop_front();
            cout<<x<<" ";
        }
        return 0;
    }
```


---

## 作者：Trimsteanima (赞：0)

# $\mathtt{CF 1234B1}$

## $\mathcal{Description}$

有一个队列，长度最大为 $k$，开始时队列里没有元素，有 $n$ 个元素要加入队列，第 $i$ 个元素的值为 $id_i$ $(1 \leq id_i \leq 10 ^ 9)$。如果当前队列长度为 $k$，则清除队列第 $k$ 个位置的数，如果队列长度小于 $k$ 并且 $id_i$ 没在队列中出现过，则 $id_i$ 将出现在队列头部，其他的数向后移动一个位置，要求输出最后的队列。

$B1: 1 \leq n, k \leq 200$

$B2: 1 \leq n, k \leq 2e5$

## $\mathcal{Solution}$

用$queue$维护一个队列，按题目意思进行模拟，或者用数组模拟皆可。

## $\mathcal{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
queue<int> q;
map<int, bool> mp;
int n, k, x, a[200010];
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (!mp[x]) {
            mp[x] = 1;
            q.push(x);
        }
        if (q.size() > k) {
            mp[q.front()] = 0;
            q.pop();
        }
    }
    int sz = q.size();
    printf("%d\n", sz);
    for (int i = 1; i <= sz; i++)  {
        a[i] = q.front();
        q.pop();
    }
    for (int i = sz; i >= 1; i--)
        printf("%d%c", a[i], " \n"[i == 1]);
    return 0;
}
```



---

## 作者：littleseven (赞：0)

### 题目解析：

[博客地址](http://littleseven.top/)

这道题我们涉及到如何维护这个列表的问题，那么我们先看这个列表的一些性质：

- 唯一：列表中的所有元素只能出现一次，列表中没有重复的元素。
- 顺序：列表中的所有元素按照都按照出现的顺序排序，并且每次修改要删掉最后一个并且后推。

根据这道题所模拟的过程，我们很自然的就会想到队列。但是由于这道题既有队头入队，又有队尾出队，那么我们选择双端队列（deque）。

但是另外的一个问题，如何保证这个列表中的唯一性（不重复性）。这怎么实现？？？————集合啊。

按照集合的不重复性来维护这个不重复的列表刚刚好。（set里找不到就是没有出现过呗）

那么我们就用$deque$和$set$混合就好了。

```cpp
#include <bits/stdc++.h>

using namespace std;

char *p1, *p2, buf[100000];

#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1 ++ ) 

int rd() {
	int x = 0, f = 1;
	char c = nc();
	while (c < 48) {
		if (c == '-') {
			f = -1;
		}
		c = nc();
	}
	while (c > 47) {
		x = (((x << 2) + x) << 1) + (c ^ 48);
		c = nc();
	}
	return x * f;
}

const int N = 2e5 + 10;

int n, k;

bool vis[N];

int main() {
	n = rd(), k = rd();
	deque <int> q;
	set <int> s;
	for (int i = 1; i <= n; i ++ ) {
		int x = rd();
		if (s.find(x) == s.end()) {
			q.push_front(x);
			s.insert(x);
			if (q.size() > k) {
				int now = q.back();
				s.erase(now);
				q.pop_back();
			}
		}
	}
	printf("%d\n", q.size());
	while (! q.empty()) {
		printf("%d ", q.front());
		q.pop_front();
	}
	return 0;
}
```

---

## 作者：Meatherm (赞：0)

用 `std::deque` 模拟即可。

首先将所有数据离散化，开一个 `bool` 数组  `use` 记录这个 ID 的朋友发的消息是否存在于屏幕上。

对于第 $i$ 条消息：

- 如果 $id_i$ 在已经存在，那么就跳过这此操作。
- 否则在双端队列（`deque`） 的队首加入这个 $id_i$。
- 如果双端队列的元素个数 $>k$，将队尾元素弹出。

在 $n$ 次操作之后依次输出队列元素即可。

```cpp
# include <bits/stdc++.h>
# define rr register
using namespace std;
const int N=210;
int a[N],b[N];
int n,k;
int m;
bool use[N];
std::deque <int> q;
int main(void){
	cin>>n>>k;
	for(rr int i=1;i<=n;++i)
		cin>>a[i],b[i]=a[i];
	std::sort(b+1,b+1+n);
	m=std::unique(b+1,b+1+n)-(b+1);	
	for(rr int i=1;i<=n;++i){
		if(!use[std::lower_bound(b+1,b+1+n,a[i])-b])
			q.push_front(a[i]),use[std::lower_bound(b+1,b+1+n,a[i])-b]=true;
		if(q.size()>k){
			use[std::lower_bound(b+1,b+1+n,q.back())-b]=false,q.pop_back();
		}	
	}
	int tmp=q.size();
	cout<<tmp<<endl;
	for(rr int i=1;i<=tmp;++i)
		cout<<q.front()<<" ",q.pop_front();
	return 0;
}
```

---

## 作者：CLer (赞：0)

模拟题，规则跟QQ，WX差不多，屏幕只能容纳ｋ个消息，不同的是新消息的会话窗口已经出现在屏幕里，不会置顶，只有屏幕外的会话窗口发出新消息，才会置顶并且把最下面的消息顶出去。
```cpp
#include <cstdio>
#include <set>
#include <queue>

using namespace std;

const int maxn = 2e5+10;
int ans[maxn];
int main () {
	int n, k, num, cnt = 0;
	queue<int> q, tmp;
	set<int> se;
	set<int>::iterator it;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num);
		if (q.size() < k && se.count(num) == 0) {
			q.push(num);
			se.insert(num);
		} else {
			if (se.count(num) == 0) {
				q.push(num);
				se.insert(num);
				se.erase(se.find(q.front()));
				q.pop();
			}
		}
	}
	while (!q.empty()) {
		ans[++cnt] = q.front();
		q.pop();
	}
	printf("%d\n", cnt);
	for (int i = cnt; i ; i--) {
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意：现在有n条信息，你的屏幕上只能显示m种，每次来信息时屏幕变动规则如下：如果这个信息已经在屏幕上，那么不变，反之则吧最晚放进来的信息提出，在把这类放进去，求最后的信息排列。

思路：就是用queue维护一个队列。


```
#include<bits/stdc++.h>
using namespace std;
queue <int> q;
map <int ,int > my_hash;
int n,m,a[200010],cnt=1;
 
int main()
{	q.empty(); 
	cin>>n>>m;
	while(n--)
	{
		int x;
		cin>>x;
		if(!my_hash[x])
		{
			q.push(x);
			my_hash[x]=1;
		}
		if(q.size()>m)
		{
			int y=q.front();
			q.pop();
			my_hash[y]=0;
		}
	}
	cout<<q.size()<<endl;
	while(!q.empty())
	{
		a[++cnt]=q.front();
		q.pop();
	}
	for(int i=cnt;i>1;--i)
		cout<<a[i]<<' ';
	return 0;
}
```


---

## 作者：B_Qu1e7 (赞：0)

模拟（$B1B2$通吃版）

由题意我们得到，这个通讯软件的主体结构应该是一个$First\ In\ First\ Out$，这份代码中使用的是$Queue$。（正常的通讯软件应该是接收到一个人的信息的时候把当前对话置顶，不过那样更有难度。）

可以开一个队列，存储在队列中的位置，同时开一个$map$判断当前$ID$是不是已经在队列中了。最后倒序输出队列即可。
```
#include<map>
#include<queue>
#include<cctype>
#include<cstdio>
#define rint register int
using namespace std;
map<int,bool>t;
queue<int>q;
int N,K,a,ans[200005];
template<class T>inline void read(T &m)
{
	m=0;
	register char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
signed main()
{
	read(N),read(K);
	for(rint i=1; i<=N; ++i)
	{
		read(a);
		if(t[a])continue;//已经在队列中
		else
		{
			q.push(a);
			t[a]=1;
			//塞入，打标记
			if(q.size()>K)//超过应有长度
			{
				t[q.front()]=0;
				q.pop();
				//因为每次只塞入一个，所以删除一个即可，同时打上标记
			}
		}
	}
	//倒序输出
	while(!q.empty())
	{
		ans[++ans[0]]=q.front();
		q.pop();
	}
	printf("%d\n",ans[0]);
	while(ans[0])
	{
		printf("%d ",ans[ans[0]]);
		--ans[0];
	}
}
```

---

