# Social Network (hard version)

## 题目描述

The only difference between easy and hard versions are constraints on $ n $ and $ k $ .

You are messaging in one of the popular social networks via your smartphone. Your smartphone can show at most $ k $ most recent conversations with your friends. Initially, the screen is empty (i.e. the number of displayed conversations equals $ 0 $ ).

Each conversation is between you and some of your friends. There is at most one conversation with any of your friends. So each conversation is uniquely defined by your friend.

You (suddenly!) have the ability to see the future. You know that during the day you will receive $ n $ messages, the $ i $ -th message will be received from the friend with ID $ id_i $ ( $ 1 \le id_i \le 10^9 $ ).

If you receive a message from $ id_i $ in the conversation which is currently displayed on the smartphone then nothing happens: the conversations of the screen do not change and do not change their order, you read the message and continue waiting for new messages.

Otherwise (i.e. if there is no conversation with $ id_i $ on the screen):

- Firstly, if the number of conversations displayed on the screen is $ k $ , the last conversation (which has the position $ k $ ) is removed from the screen.
- Now the number of conversations on the screen is guaranteed to be less than $ k $ and the conversation with the friend $ id_i $ is not displayed on the screen.
- The conversation with the friend $ id_i $ appears on the first (the topmost) position on the screen and all the other displayed conversations are shifted one position down.

Your task is to find the list of conversations (in the order they are displayed on the screen) after processing all $ n $ messages.

## 说明/提示

In the first example the list of conversations will change in the following way (in order from the first to last message):

- $ [] $ ;
- $ [1] $ ;
- $ [2, 1] $ ;
- $ [3, 2] $ ;
- $ [3, 2] $ ;
- $ [1, 3] $ ;
- $ [1, 3] $ ;
- $ [2, 1] $ .

In the second example the list of conversations will change in the following way:

- $ [] $ ;
- $ [2] $ ;
- $ [3, 2] $ ;
- $ [3, 2] $ ;
- $ [1, 3, 2] $ ;
- and then the list will not change till the end.

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

## 作者：jiangXxin (赞：3)

$B1$的加强版，其实也没难多少
	
现在有n条信息，但是你的手机只能显示m条信息，每次弹过来一条信息，它将被放在第一位，如果当前手机显示的信息大于m，那么最后一个就会被弹出，同时，每一次弹过来的信息，如果手机里面已经有这个人发的信息，那么就可以不作出改变。

思路：使用一个单调队列，每一次弹来的信息，放入队头，如果已经出现过，那么就$continue$,（这里考虑到$a_i$比较大，那么就可以使用一个map）当队列的长度大于m，则把最后一个信息弹出。

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

## 作者：Meatherm (赞：2)

同样可以用 `std::deque` 来实现。

在 B1 中，求数组元素数量使用了 `q.size()`，这个函数的复杂度为 $O(k)$ ，而插入、删除复杂度均为 $O(1)$，所以总复杂度为 $O(nk)$。

考虑手动记录双端队列的元素个数。这样求当前双端队列的元素个数复杂度降为 $O(1)$，总复杂度降为 $O(n)$。

而我们需要离散化，离散化需要排序，所以程序复杂度应该为 $O(n\log n)$。

```cpp
# include <bits/stdc++.h>
# define rr register
using namespace std;
const int N=200010;
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
	int asa=0;
	for(rr int i=1;i<=n;++i){
		if(!use[std::lower_bound(b+1,b+1+n,a[i])-b]){
			q.push_front(a[i]),use[std::lower_bound(b+1,b+1+n,a[i])-b]=true;
			++asa;			
		}
		if(asa>k){
			use[std::lower_bound(b+1,b+1+n,q.back())-b]=false,q.pop_back();
			--asa;
		}	
	}
	int tmp=asa;
	cout<<tmp<<endl;
	for(rr int i=1;i<=tmp;++i)
		cout<<q.front()<<" ",q.pop_front();
	return 0;
}
```

---

## 作者：dz_ice (赞：2)

 _### stl大法好！_ 

先讲一讲题意，就是一开始有一个队列，每输入一个元素，如果这个队列有这个元素，那么就什么都没有发生；如果没有就在队首加入这个元素，如果序列长度大于了$k$，那么队尾的元素就出队。最后输出这个队列

我们只需要用队列和一个判重数组来实现这些操作，不过看到数据范围$1≤id_i≤10^9$，我们还得将$id$进行离散化，使用stl中的map即可

上代码

```
#include<bits/stdc++.h>
using namespace std;
int n,k,sum,b[200003],a[200003],t,p;
queue<int>q;
map<int,int>mp; //离散化处理
int main()
{
	cin>>n>>k;
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		if(mp[a[i]]==0)
			p++,mp[a[i]]=p; 
		if(b[mp[a[i]]]==0)
		{
			q.push(a[i]);
			if(q.size()>k) //队列的长度要小于等于k 
			{
				b[mp[q.front()]]=0; //出队时要更改判重数组 
				q.pop();
			}
		}
		b[mp[a[i]]]=1;
	}
	sum=q.size();
	cout<<sum<<endl;
	while(!q.empty())
	{
		t++,b[t]=q.front();
		q.pop();
	}
	for(int i=sum; i>=1; i--)
		cout<<b[i]<<" ";
	return 0;
}
```


---

## 作者：Trimsteanima (赞：1)

# $\mathtt{CF 1234B2}$

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

## 作者：Katsura_Hinagiku (赞：1)

看看这题，不就是一个栈吗，用数组模拟栈即可。

用一个桶记录当前显示的信息中是否有$id[i]$发来的，因为$id[i]$的范围是$[1,10^9]$,所以需要离散化，因为我太懒，所以直接用map完成离散化操作。

最后直接从栈顶开始向下输出即可

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>mp;
int n,k;
int stck[200005],top=0;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	{
		int ccc;
		scanf("%d",&ccc);
		if(mp[ccc])continue;
		mp[ccc]=1;
		stck[++top]=ccc;
		if(top>k)
		{
			mp[stck[top-k]]=0;
		}
	}
	printf("%d\n",min(top,k));
	for(int i=top;i>=max(top-k+1,1);--i)
	{
		printf("%d ",stck[i]);
	}
	return 0;
}
```

---

## 作者：AzureMist (赞：0)

这题可以用 set 和 queue 配合着作。因为 set 可以使用 count，如果 count 的结果为 $0$ 说明当前这位好友的消息还没有在屏幕上显示，但是 set 是会自动排序的，为了避免让一些无辜的好友的消息被挤出去，我们需要用 queue 来维护它的顺序。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
set<int> p;
queue<int> c;
int main()
{
	cin>>n>>k;
	for(int i=0;i<=n-1;i++)
	{
		int a;
		cin>>a;
		if(!p.count(a))//count的结果为0，表示id为a的好友的消息还未出现在屏幕上
		{
			if(c.size()==k)//屏幕上放不下了
			{
				p.erase(c.front());//把此时的队首从set中删掉
				c.pop();//同步删除
			}
			c.push(a);//然后再把新消息放进去
			p.insert(a);//同步插入新消息
		}
	}
	vector<int> ans;
	while(c.size()>0)
	{
		ans.push_back(c.front());
		c.pop();//保存还在屏幕上的
	}
	cout<<ans.size()<<endl;
	for(int i=ans.size()-1;i>=0;i--) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
用 `deque` 来维护序列，然后，用一个 `map` 来看是否添加过了。

具体分为一下步骤：

> 若当前已经有了，那么直接 `continue`。

> 若长度 $= k$ 了，就弹出队尾，然后把标记删掉。

> 然后插入队头,然后再标记一下就可以了。
 
## AC CODE:
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <deque>
#include <map>
using namespace std;
int n , k;
int a[200010];
deque <int> q;//维护序列
map <int , int> ma;//在聊天框里是否出现过
int main(){
	scanf ("%d%d" , &n , &k);
	for (int i = 1; i <= n; ++ i)
		scanf ("%d" , &a[i]);
	for (int i = 1; i <= n; ++ i) {
		if (ma[a[i]]) continue;//已经出现过了，那么就跳过
		if (q.size () == k) ma[q.back()] = false , q.pop_back();//弹出，然后去掉标记
		if (!ma[a[i]])q.push_front (a[i]) , ma[a[i]] = true;//插入，标记
	}
	cout << q.size() << endl;//输出长度
	for (int i = 0; i < q.size(); ++ i)
		cout << q[i] << ' ';//输出聊天窗里的数
	return 0;//完结散花
}
```
码字不易，求赞！

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
{   q.empty(); 
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

## 作者：serverkiller (赞：0)

# CF1234B 【Social Network】

---

讲道理这个HARD出现的原因是easy真的太easy了

还是先讲题意:
>n条信息，每个人的信息只能同时出现一个（如果你已经有了，就不会收到他的信息），如果>k个就删掉最早一条，输出剩余信息数，并按发信息的先后输出

开始我们考虑可以使用set来处理超出的情况 但是这样无法知道应该删掉的是哪个人,于是使用队列来记录 最后统计答案就可以了 注意需要逆序

```
#include <bits/stdc++.h>
using namespace std;

int n,k;
int tot = 0,ans[200005];
map <int,int> mp;
set <int> s;
struct node
{
	int w,id;
};
queue <node> q;

int main()
{
	scanf("%d%d",&n,&k);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d",&x);
		if (!s.count(x))
		{
			mp[x] = i;
			node t;
			t.id = i;
			t.w = x;
			q.push(t);
		}
		s.insert(x);
		if (s.size() > k)
		{
			while (!q.empty())
			{
				node u = q.front();
				q.pop();
				if (mp[u.w] == u.id)
				{
					s.erase(u.w);
					mp[u.w] = 0;
					break;
				}
			}
		}
	}
	int l = s.size();
	printf("%d\n",l);
	while (!q.empty())
	{
		node u = q.front();
		q.pop();
		if (mp[u.w] == u.id) ans[++tot] = u.w;
	}
	for (int i = tot; i >= 1; i--) printf("%d ",ans[i]);
	//system("pause");
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

维护一个长度最多为 $k$ 的序列，每次加入一个数 $x$，如果 $x$ 在序列中，则不进行任何操作。否则将 $x$ 插入序列头部，序列长度超过 $k$ 时舍弃超出的部分。求所有操作结束后序列的长度和内容。

**解题思路**

这是一道正宗的**模拟**题，用 $\texttt{STL}$ 里的  $\texttt{deque}$ 和 $\texttt{map}$ 来维护。

先将第一个聊天记录存入 $\texttt{deque}$ 中，并标记一下。

再遍历一下，如果这个元素没有标记过，则插进双端队列的队首。

如果插入后双端队列的长度大于了 $k$，那么将队尾的元素弹出，并取消标记。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N];
deque<int> dq;
map<int, int> mp;
int main() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dq.push_front(a[1]);
	mp[a[1]] = 1;
	for(int i = 2; i <= n; i++) {
		if(!mp[a[i]]) {
			dq.push_front(a[i]);
			if(dq.size() > k) {
				mp[dq.back()] = 0;
				dq.pop_back();
			}
			mp[a[i]] = 1;
		}
	}
	cout << dq.size() << "\n";
	while(!dq.empty()) {
		cout << dq.front() << " ";
		dq.pop_front();
	}
	return 0;
}
```

---

