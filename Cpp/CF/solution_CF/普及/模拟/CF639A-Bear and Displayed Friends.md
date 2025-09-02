# Bear and Displayed Friends

## 题目描述

# 题目表述
Limak有n个朋友，他与第i个朋友的友谊值是ti，题目保证不会出现两个朋友的友谊值相同。

有一天，Limak上网和朋友聊天，此时只有Limak在线，接下来，会有一些朋友陆续上线。

系统会显示在线的朋友，但如果超过k个，系统只会显示ti最大的k个。

你的任务是处理两种查讯:

“1 id”表示id号的朋友上线，保证他以前没有在线；

“2 id”检测系统会不会显示id号的朋友，在单独一行中输出“YES”或“NO”。

## 样例 #1

### 输入

```
4 2 8
300 950 500 200
1 3
2 4
2 3
1 1
1 2
2 1
2 2
2 3
```

### 输出

```
NO
YES
NO
YES
YES
```

## 样例 #2

### 输入

```
6 3 9
50 20 51 17 99 24
1 3
1 4
1 5
1 2
2 4
2 2
1 1
2 4
2 3
```

### 输出

```
NO
YES
NO
YES
```

# 题解

## 作者：kdy20100729 (赞：7)

#### 题目传送门： [CF639A](https://www.luogu.com.cn/problem/CF639A)

### 题意：  
一个队列，每次可以放一个数进去，或者问某数是不是这个队列前 $k$ 大。

### 思路：  
这道题用 STL 库中的 set 模拟过程即可。  
$Q:$ 为什么要用 ```set```？  
$A:$  因为题目会询问某数是不是这个队列前 $k$ 大。并且 ```set``` 有 ```find()``` 函数，可以按元素查找，返回元素地址，而且时间复杂度为 $O(\log n)$。所以我们可以用 ```find()``` 来查找它。

### 代码如下：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
set<int> s;
set<int>::iterator it;
int t,n,k,x,y,friendship[150005];
signed main()
{
    cin >> n >> k >> t;
    for(int i=1; i<=n; i++)
        cin >> friendship[i];
    while(t--)
    {
        cin >> x >> y;
        if (x==1)
            s.insert(friendship[y]);
        else
        {
            if (s.find(friendship[y])!=s.end())
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        if (s.size()>k)
            s.erase(s.begin());
    }
    return 0;
}
```

---

## 作者：max0810 (赞：3)

题目是我一年前翻译的，我承认当时不会markdown，所以再次为大家说一下题目大意:

有一个队列，每次可以放一个数进去，或者询问某数是不是这个对列前$k$大。


------------

这道题每次保留前$k$大，肯定会想到优先队列或者栈，想要让他们的长度$\le k$，那么放数就有两种情况：

- 如果还没有$k$个数，直接放进去就行。
- 已经$k$个了，如果放的数小于队列最小的数，就不放，反之就替换。

考虑到放的数一定没有重复的，而且set自带查找功能，所以我直接选择了set。 ~~（大佬们别听本蒟蒻的）~~
```cpp
#include <iostream>
#include <set>
using namespace std;
set<int> s;                                //set默认从小到大
int a[150005];
int main()
{
    int n,k,q;
    cin >> n >> k >> q;
    for(int i = 1;i <= n;i++)cin >> a[i];   //输入不用我多说吧
    while(q--)
    {
        int t,id;
        cin >> t >> id;
        if(t==1)
        {
            if(s.size()<k)s.insert(a[id]);    //直接放进去
            else                               //判断
                if(a[id]>*s.begin())    //*s.begin()指s的开头，就是第k大的数
                {s.erase(*s.begin());s.insert(a[id]);}  //这些函数待会讲
        }
        else
            cout << (s.count(a[id])?"YES\n":"NO\n");
    }
    return 0;
}
 ```
 下面，为大家扩展一些set的函数
 ```
begin();            //返回指向第一个元素的迭代器
end();              //返回指向迭代器的最末尾处（即最后一个元素的下一个位置）
clear();            //清除所有元素
count(a);           //返回a这个值元素的个数（因为set有去重，所以只有可能返回1或0）
empty();            //如果集合为空，返回true
erase(a)            //删除集合中a这个元素
insert(a)           //在集合中插入元素a
lower_bound(a)      //返回指向大于（或等于）a的第一个元素的迭代器
upper_bound(a)      //返回大于a第一个元素的迭代器

```
注意，若it是迭代器，则*it就是他指向的元素的值

示例
```cpp
#include <iostream>
#include <set>
using namespace std;
set<int> s;
int main()
{
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        int x;
        cin >> x;
        s.insert(x);
    }
    set<int>::iterator it;//迭代器
    for(it = s.begin();it!=s.end();it++)
        cout << *it << ' ';
    cout << endl << s.count(2) << endl;
    s.erase(1);
    cout << s.size() << endl;
    cout << *s.lower_bound(3) << endl;
    cout << *s.upper_bound(3) << endl;
    return 0;
}

```
输入
```
5
1 5 3 7 2
```
输出
```
1 2 3 5 7 
1
4
3
5
```

---

## 作者：ZZQF5677 (赞：2)

### 解题思路
每次输入都要 $\operatorname{sort}$ 太麻烦，但使用 `set<long long> st` 既可以自动排序还可以给出数组长度，哈哈。

先将 Limak 的 $n$ 个朋友的亲密值插入数组 $a$。

每次循环时：
> + 如果 $type$ 是 $1$：
>> 那就直接用 $\operatorname{insert}$ 插入 $a_{id}$。

> + 否则：
>> 先看看 $st$ 数组的长度是否超过了 $k$，如果超过了就删掉队头即可，因为 `set` 数组是有序的。然后再查找 Limak 的第 $id$ 个朋友（$a_{id}$）是否在 $st$ 队列里，输出 `YES` 或 `NO` 即可。

### 代码
```cpp

#include <bits/stdc++.h>
using namespace std;
long long n, k, q, a[150005];
set<long long> st;
int main() {
  cin >> n >> k >> q;
  for (long long i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (long long i = 1; i <= q; i++) {
    long long op, id;
    cin >> op >> id;
    if (op == 1) {
      st.insert(a[id]);
    } else {
      if (st.size() > k) {  //数组的长度是否超过了 k。
        st.erase(st.begin());
      }

      auto it = st.lower_bound(a[id]);  //查找。
      if (*it == a[id]) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }
  return 0;
}
```

---

## 作者：_Execution_ (赞：1)

## 思路

由于要询问是否为前 $k$ 大，所以可以利用 `set` 中的 `find()` 函数按照元素查找，并返回地址。 

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x,y,f[150005];
set<int> lis;
int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++) cin>>f[i];
    for(;t;t--){
        cin>>x>>y;
        if(x==1) lis.insert(f[y]);
        else if(lis.find(f[y])!=lis.end()) cout<<"YES"<<endl; else cout<<"NO"<<endl;
        if(lis.size()>k) lis.erase(lis.begin());
    }
}
```


---

## 作者：cannotdp (赞：1)

题解里大部分都是使用 set 的题解，我提供一篇使用优先队列的。

### 思路

开一个 pair 的优先队列，第一维存友谊值，第二维存 id，不停地将当前人入队，当当前显示人数超过 $k$ 时，把当前上线的人和之前上线友谊值最小的人进行一个比较。

### 代码实现

```
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int N=1e5+5e4+5;
int n,k,q;
int id[N];
bool f[N];
priority_queue<pair<int,int> >Q;//第一维存友谊，第二维存id
signed main(){
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        id[i]=x;//id为i的人的友谊值为x
    }
    while(q--){
        int K,L;
        scanf("%d%d",&K,&L);//L为id
        if(K==1){	
            if(Q.size()>=k){//如果当前显示的人数超过了k
                if(id[L]>(-Q.top().first)){
                    f[Q.top().second]=0,Q.pop();//如果当前上线的人比之前上线的人的友谊的最小值要大，就把之前的最小值弹出，不显示
                    Q.push(make_pair(-id[L],L));//将友谊和编号存进小根堆
                    f[L]=1;//标记是否显示
                }
            }
            else{
                Q.push(make_pair(-id[L],L));
                f[L]=1;
            }
        }
        else{
            if(f[L]) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
```


---

## 作者：wgyhm (赞：1)

# 【水题解记录】CF639A Bear and Displayed Friends

## 题目大意

给定长度为 $n$ 的序列。另有一个空的队列，每次加入其中一个数或者查询这个数是不是其中的前 $k$ 大。

## 题解

查询前 $k$ 大，首先考虑优先队列，再其次考虑平衡树之类的东西。

* 如果队列中没有到 $k$ 个数，直接扔进去。
* 如果队列中已经有 $k$ 个数，跟第 $k$ 个数进行比较。所以我们要维护一个小根堆。

## Code

```cpp
#include<bits/stdc++.h>
#define rg register
#define ll long long 
#define maxn 200005
#define put() putchar('\n')
using namespace std;
inline void read(int &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
int n,k,T;
int a[maxn],tot,t[maxn];
struct node{
	int id,w;
	node(int x=0,int y=0){
		id=x;w=y;
	}
	bool operator <(const node &x) const{
	    return w>x.w;
	}
}; 
priority_queue<node>q;
signed main(){
    rg int i,x,y;
    read(n);read(k);read(T);
    for (i=1;i<=n;i++) read(a[i]);
	while (T--){
		read(x);read(y);
		if (x==1) {
			if (++tot<=k) q.push(node(y,a[y])),t[y]=1;
			else {
				if (a[y]>q.top().w) t[q.top().id]=0,q.pop(),t[y]=1,q.push(node(y,a[y])); 
			}
		}
		else puts(t[y]?"YES":"NO");
	} 
    return 0;
}
```





---

## 作者：ZolaWatle (赞：1)

#### 题目大意

对于一个集合 $S$，其中每一个元素有一个权值 $t_i$。接下来有 $q$ 次操作：

- 将元素 $i$ 加入集合 $S'$ 中。保证此前 $i\notin S'$。
- 询问，对于一个元素 $i$，若 $i\in S'$ 且 $t_i$ 在 $S'$ 中的所有 $t_i$ 的排名在前 $k$ 位，输出 "YES"；否则输出 "NO"。

#### 解题思路

首先我们不考虑排名。由于保证了新上线的朋友此前不在线，我们可以开一个数组 $on_i = 0/1$，表示这位朋友是否上线。判断时，我们可以先检查 $on_i$ 的情况。如果现在需要判断的朋友是 $x$ 号，若 $on_x = 0$，可以直接输出 "NO"。

对于排名，我们考虑使用一个优先队列。建立一个二元组 $\text{<first, second>}$，第一维表示 $t_i$，第二位表示 $i$。对于操作一，我们将 $\text{<}t_i, i\text{>}$ 加入队列。由于 $\text{pq}$ 默认的是大根堆，我们就保证了队头的前 $k$ 个朋友一定是 $t_i$ 值前 $k$ 大的。特别地，如果进行询问时队列的大小不超过 $k$，此时我们只需要判断当前询问对象的 $on$ 值即可。

如果不是这样，我们让队头的前 $k$ 个二元组弹出并暂存。接下来判断这 $k$ 个二元组中是否有一个 $\text{second}$ 值为当前询问的对象，如果有，输出 "YES"；否者输出 "NO" 就可以了。

时间复杂度为 $\text{O}(qk)$，大约是 $1e6$ 的级别。因为 $k$ 实际上不会超过 $6$，可以理解为一个 $\text{O}(q)$ 的算法，在本题是能够轻松通过的。

本题还有一个理论上更为优秀的平衡树算法，但常数远比此算法大，读者可以自行了解。

#### 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register int
#define rl register ll
#define rep(i,a,b) for(re i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(re i=(a),i##end=(b);i>=i##end;--i)
#define mem(x,val) memset(x,val,sizeof(x))
#define cpy(a1,a2) memcpy(a1,a2,sizeof(a2))
using namespace std;

const int N=1.5e6+10;
int n,K,Q,tot,flg,t[N],on[N];
pair <int,int> tmp[10];
priority_queue < pair <int,int> > q;

inline int rint()
{
    re x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}

signed main()
{
    n=rint(),K=rint(),Q=rint();
    rep(i,1,n) t[i]=rint();

    while(Q--)
    {
        re typ=rint(),x=rint();
        if(typ==1)
        {
            q.push(make_pair(t[x],x));
            on[x]=1;
        }
        else
        {
            if(!on[x])
            {
                puts("NO");
                continue;
            }
            if(q.size()<=K)
            {
                puts("YES");
                continue;
            }
            tot=0,flg=0;
            rep(i,1,K)
            {
                if(q.top().second==x)
                {
                    puts("YES");
                    flg=1;
                    break;
                }
                tmp[++tot]=q.top();
                q.pop();
            }
            rep(i,1,tot) q.push(tmp[i]);
            if(!flg) puts("NO");
        }
    }

    return 0;
}
```

感谢阅读！

---

## 作者：jasonshen_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF639A)
### 题意
维护一个队列，每次可以加入一个数到队尾，问这个数是不是比这个队列前面的一项大。
### 思路
![](https://oi-wiki.org//lang/csl/images/container1.png)
可以使用关联式容器 `set`，`set` 有自动排序和给出数组长度的功能，很好用。

具体用法：[OI-WIKI](https://oi-wiki.org//lang/csl/associative-container/)。

这里讲一下本题涉及到的 `set` 知识点。
- 插入操作：`insert(x)` 当容器中没有等价元素的时候，将元素 `x` 插入到 `set` 中。

例子：
```cpp

    set<std::string> myset; 
    string str = "jasonshen_";
    myset.insert(str);
```
- 访问队列首个元素：`队列名.begin()`。

- 删除操作

1. `erase(x)` 删除值为 x 的 **所有**元素，返回删除元素的个数。

1. `erase(pos)` 删除迭代器为 `pos` 的元素，要求迭代器**必须合法**。
    
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> s;
int id[150001];
int main() {
	int n,k,q;
	cin>>n>>k>>q;
	for(int i=1; i<=n; ++i) {
		cin>>id[i];
	}
	for(int i=1; i<=q; ++i) {
		int x,d;
		cin>>x>>d;
		if(x==1) {
			s.insert(id[d]);
			if(s.size()>k) s.erase(s.begin());
		} else {
			if(!s.count(id[d])) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}
}
```

---

## 作者：glx123 (赞：0)

# 题目分析
这道题可以描述为：有一个空队列，有两种操作，放入一个数，或查询这个数是否是这个队列里前 $k$ 大的数（前提是此数在队列中）

首先想到优先队列，可以定义一个从从小到大的优先队列，每次加入，如果长度达到 $k$ 则比较队列中最小的和新加入的，留下大的。
# 代码
```
#include <bits/stdc++.h>
using namespace std;
priority_queue< pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >qu;//从小到大的优先队列，写得有些冗长了。 
int n,k,q;
int f[150005];//每个人的亲密度，即比较对象。 
bool x[150005];//判断每个人是否在队列中。 
int main() {
	
	scanf("%d %d %d",&n,&k,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i]);//读入亲密度。 
	}
	while(q--){
		int a,b;
		scanf("%d %d",&a,&b);
		if(a==1){//加入的情况： 
			if(qu.size()>=k){//如果队列里已人数已满—— 
				if(f[b]>qu.top().first){//则比较队列中最小者与加入者，如果加入者更大。 
					x[qu.top().second]=0;
					qu.pop();//删去队列中较小者 
					qu.push(make_pair(f[b],b)),x[b]=1;//加入 。 
				}
			}else{//人数未满，继续加入 。 
				qu.push(make_pair(f[b],b)),x[b]=1;
			}
		}else{//查询是否是前k个，输出。 
			if(x[b]){
				printf("YES\n");
			}else{
				printf("NO\n");
			}
		}
	}
	return 0;
}
```
完成！

---

## 作者：_Jonny_404 (赞：0)

一开始想到的思路：用 map，定义一个 `map` 类型的 $m$，用数组 $a$ 储存每个朋友的友谊值，每次当 $type$ 等于 $1$ 时，将键值为 $a_{id}$ 对应的映射为 $id$，若 $m$ 的大小大于 $k$，则弹出第一个元素（`map` 按从小到大排序），查找时判断键值为 $a_id$ 的是否在 $m$ 中。但我们很快发现这种方法不可行，一旦有两个朋友的友谊值相同，可能会出现判断错误的 $id$。

那么我们重新想办法，于是想到了另一种办法，同样是用 `map`，但键值变为一个 `pair`，第二个值变为 `bool` 类型，因为 `pair` 可以自动按第一个元素排序，所以我们将 `pair` 的 `first` 记录 $a_{id}$，`second` 记录 $id$，而 `bool` 类型则记录是否有这样一位朋友上线。查找时，判断是否存在有一个键值为 `first` 是 $a_id$ 而 `second` 是 $id$ 的在 $m$ 当中。

代码：

```cpp
#include <iostream>
#include <map>
using namespace std;

int n, k, q;
int a[157300];
map<pair<int, int>, int> m;

int main() {
  cin >> n >> k >> q;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    a[i] = x;  // id为i的人的友谊值
  }
  while (q--) {
    int type, id;
    cin >> type >> id;
    if (type == 1) {
      m[make_pair(a[id], id)] = 1;
      if (m.size() > k)
        m.erase(m.begin());  // 去除友谊值最小的那个
    } else {
      if (m.count(make_pair(a[id], id)))
        cout << "YES" << endl;
      else
        cout << "NO" << endl;
    }
  }
  return 0;
}
```

---

## 作者：Chang_Pei (赞：0)

### 题目

[Link](https://www.luogu.com.cn/problem/CF639A)

### 思路&题意

一个队列，每次可以放一个数进去，或者问某数是不是这个队列前 $k$ 大。

用 STL 中的 set 模拟这个过程。

不会 set 的同学看这里： [Link](https://www.luogu.com.cn/blog/chenzhangpei/set-di-yong-fa)。

$Q$ ： 为什么要用 set 呀？

$A$ ： 因为题目会询问某数是不是这个队列前 k 大。并且 set 有 find() 函数，可以按元素查找，返回元素地址，而且时间复杂度为 $ O(log n) $。所以我们可以用 find() 来查找它。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=150005;
int n,k,q,x,y,t[maxn];
set<int> s; //set
set<int>::iterator it; //迭代器
int 
int main(){
    cin>>n>>k>>q;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    while(q--){
        cin>>x>>y;
        if(x==1){ //插入元素
	        s.insert(t[y]);
        }else{
            if(s.find(t[y])!=s.end()){ //如果t[y]不是t[n]
                cout<<"YES"<<endl;
            }else{ 
                cout<<"NO"<<endl;
            }
        }
        if(s.size()>k){ 
            s.erase(s.begin());
        }
    }	
    return 0;
}
```


---

