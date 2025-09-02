# Argus

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3644

[PDF](https://uva.onlinejudge.org/external/12/p1203.pdf)

# 题解

## 作者：666DHG (赞：4)

看到UVA的题解很少，那我这个蒟蒻来写一篇._.

我的思路是：
1. 读入
2. 将这条信息**重复地**放入优先队列，分别模拟**第一次**、**第二次**......的查询时间点
3. 输出前$k$条信息

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
 
struct Data
  {
    int num;
    int time;
    Data(int a=0,int b=0):num(a),time(b){};
    bool operator<( const Data &c) const //重载运算符
      {
        return time>c.time||(time==c.time&&num>c.num); //时间从小到大排序，相同的编号小的优先
      }
  };
 
priority_queue <Data> Q; //优先队列（简单来说就是自动排序）
 
string k;
int n,a,b;
 
int main()
  {
    while (1)
      {
        getline(cin,k);
        if (k[0]=='#') break;
        k.erase(0,9); //把"Register "删去
        sscanf(k.c_str(),"%d%d",&a,&b); //sscanf : 从字符串中读取数据
        for (int i=1;i<=3010;i++) //这里要特别注意!假如i的上限过大会MLE QwQ
          {
            Data put;
            put.num=a;
            put.time=b*i; //该查询点第i次的查询时间点
            Q.push(put);
          }
      }
    scanf("%d",&n);
    for (int i=1;i<=n;i++) //取出前k个小的并输出
      {
        printf("%d\n",Q.top().num);
        Q.pop();
      }
    return 0;
  }
```

---

## 作者：_•́へ•́╬_ (赞：4)

**~~似乎没有题解，我来搞一篇~~**
# 不就是一个优先队列吗？
```cpp
#include<bits/stdc++.h>//懒人专用头文件
#define rpt(n) for(register int ttxyc=0;ttxyc<n;ttxyc++)
using namespace std;
struct tle//QWQ QAQ Q_Q
{
	int num,now,time;
	bool operator < (const tle&a)const//重要！别漏后面的const了
	{
		return now>a.now||(now==a.now&&num>a.num);
	}
};
priority_queue<tle>pq;//定义优先队列
main()
{
    for(string s;cin>>s,s!="#";)//输入
	{
		tle t;
		scanf("%d%d",&t.num,&t.time);t.now=t.time;//输入
		pq.push(t);//存入系统
	}
	register int k;
	scanf("%d",&k);//输入k
	rpt(k)
	{
		tle t=pq.top();pq.pop();//取时间最小的
		printf("%d\n",t.num);//输出
		t.now+=t.time;//过一段时间
		pq.push(t);//重新入队列
	}
}/**/
```

---

## 作者：fedoralxy (赞：3)

这道题有一个更加新颖（chou xiang）的思路，我们很容易发现，每一次询问都是其中一条命令中 $\tt period$ 的倍数，那么为了可以不重不漏的枚举每一个查询的时间，可以采用对于所有 $\tt period$ 取公因数的方式，依次枚举公因数的倍数。

对于当前枚举的数，我们将排序后的数组按顺序遍历，直到第一个 $\tt period$ 满足其是该数的因数，输出 $\tt Q_{num}$ 即可。

实现如下：

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 1e6 + 10;
string opt;
ll n = 0, gcd_;
ll x, p, id;
class node {
	public :
		ll x, p, idx;
}a[N];
int main () {
	do {
		cin >> opt;
		if (opt == "#") {
			break;
		}
		cin >> x >> p;
		gcd_ = (n == 0) ? p : __gcd (gcd_, p);
		a[++ n].x = x, a[n].p = p, a[n].idx = n;
	} while (true);
	sort (a + 1, a + n + 1, [] (node a, node b) {
		if (a.x == b.x) {
			return a.idx < b.idx;
		}
		return a.x < b.x;
	});
	ll k, tmp = 0; 
	cin >> k;
	while (id < k) {
		tmp += gcd_;
		for (int i = 1; i <= n; ++ i) {
			if (tmp % a[i].p == 0) {
				cout << a[i].x << '\n';
				++ id;
			}
		}
	}
	return 0;
}
```

---

## 作者：maziming (赞：1)

## 题意：
有若干个指令，每个指令每 Period 秒输出一次，输出 $k$ 次。
## 思路：
我们可以将第一次输入的时间加入结构体，然后排个序，输出第一个，然后将最短的加上这个每一次要加的时间，再次排序。感觉解释得有点不清楚，如有不懂者去看代码解释。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n=1,k;
string a;
struct aa{
	long long a,b,c;
}s[10010];
long long cmp(aa a,aa b){
	if(a.c!=b.c)return a.c<b.c;
	return a.a<b.a;
}//排序
int main()
{
	cin>>a;
	while(a!="#")
	{
		cin>>s[n].a>>s[n].b;
		s[n].c=s[n].b;//将第一次加入结构体
		n++;
		cin>>a;
	}
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		sort(s+1,s+n,cmp);//排序
		cout<<s[1].a<<endl;
		s[1].c+=s[1].b;//将最短的加上每一次要加的时间
	}
	return 0;
}
```

---

## 作者：Ivan422 (赞：1)

题目大意：给出若干个查询，每次查询输出 $Q_{num}$，每个查询间隔 $Period$ 秒，请按照顺序输出前 $k$ 次查询的答案，当两次查询输出时间相同，先输出查询结果小的。

思路：我们会发现查询的时间是从小到大的，于是使用优先队列。首先定义一个结构体，再定义一个比较函数，直接定义一个 STL 里的大根堆，注意符号的方向。接着是若干个输出，直接用 `while(cin>>s)` 即可。每次像约瑟夫一样输出堆顶时间，并弹出。接着把下一次查询的时间加入堆，就可以实现查询了。

```cpp
//2022tysc0819
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
//using namespace __gnu_pbds;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e5+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,per,qes,k;
string s;
struct Argus{int perj,ti,val;};
bool operator<(Argus x,Argus y){
    if(x.ti!=y.ti)return x.ti>y.ti;
    return x.val>y.val;
}
priority_queue<Argus>q;
signed main(){
    while(cin>>s){
        if(s=="#")break;
        cin>>qes>>per;
        q.push(Argus{per,per,qes});
    }
    cin>>k;
    for(int i=1;i<=k;i++){
        cout<<q.top().val<<endl;
        q.push(Argus{q.top().perj,q.top().ti+q.top().perj,q.top().val});
        q.pop();
    }
    return 0;
}
//note:
```

---

## 作者：zhou_rui_tong (赞：0)

### 题目大意：
每个用户一个 id ，一个间隔时间 $t$，在 $t$ 秒， $2\times t$ 秒，$3\times t$，$i\times t$ 秒会接收到，问前 $k$ 次接收到的用户 id 是分别什么。

我们可以用优先队列来解决，按每个用户下一次接收到信息的时间排序。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string q;
ll n;
struct qq
{
	ll i,s,t;
	friend bool operator < (qq a,qq b)
	{
		if(a.s!=b.s)return a.s>b.s;
		else return a.i>b.i;
	}
}p;
priority_queue<qq> a;
int main()
{
	cin.tie(0);
	cout.tie(0);
	while(1)
	{
		cin>>q;
		if(q=="#")break;
		cin>>p.i>>p.t;
		p.s=p.t;
		a.push(p);
	}
	cin>>n;
	while(n--)
	{
		cout<<a.top().i<<"\n";
		a.push(qq{a.top().i,a.top().s+a.top().t,a.top().t});
		a.pop();
	}
	return 0;
}
```

---

## 作者：tsh_qwq (赞：0)

优先队列秒了，但结构体。  
众所周知，优先队列无法直接套用结构体，所以需要**运算符重载**，知道这一点就很简单了。

#### 思路
1. while 读入，检测到 `#` 退出。
2. 循环 $k$ 次从优先队列中取出信息，输出后加上间隔时间重新加入。
   
#### 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
struct no
{
    int id,p,ti;
}h;
bool operator < (const no &a,const no &b)//运算符重载
{
    if(a.ti!=b.ti)return a.ti>b.ti; 
    return a.id>b.id;
}
priority_queue<no>q; 
int main()
{
    while(1)
	{
		string s;
		int id,p;
		cin>>s;
		if(s=="#")break;
        cin>>id>>p;
        q.push({id,p,p});
    }
    cin>>k;
    while(k--)
	{
        h=q.top(); 
        q.pop();
        cout<<h.id<<"\n";//好习惯
        q.push({h.id,h.p,h.ti+h.p});
    }
    return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## UVA1203 Argus 题解

### 思路分析

本题的翻译有些难懂，我给出一个版本：

给你若干对整数 $(x, y)$，每隔 $y$ 输出一遍 $x$，有同时的则**先**输出 $x$ 较小的那个。共输出 $k$ 个。

考虑使用优先队列实现。

对于一个类 `node`，定义 $key, add, time$。

- $key$ 记录数值
- $add$ 记录每次增加时间
- $time$ 记录当前时间

重载运算符先考虑时间，相同时考虑数值。

实现如下：

```cpp
class node
{
  public:
    int key;
    int add;
    int time;
    friend bool operator<(const node &__x, const node &__y)
    {
        return __x.time > __y.time || (__x.time == __y.time && __x.key > __y.key);
    }
};
```

输入我们采用输入一行字符串的方式，之后对其拆分。

实现如下：

```cpp
for (;;)
{
    scanf("%[^\n]s", s);
    getchar();
    if (s[0] == '#')
    {
        break;
    }
    sprintf(s, "%s", s + 9);
    int x, y;
    x = 0;
    y = 0;
    for (;;)
    {
        if (s[0] == ' ')
        {
            break;
        }
        x *= 10;
        x += s[0] - '0';
        sprintf(s, "%s", s + 1);
    }
    sprintf(s, "%s", s + 1);
    for (;;)
    {
        if (s[0] == ' ' || s[0] == '\0')
        {
            break;
        }
        y *= 10;
        y += s[0] - '0';
        sprintf(s, "%s", s + 1);
    }
    node temp;
    temp.key = x;
    temp.add = y;
    temp.time = y;
    queue.push(temp);
}
```

#### Tips：

- `scanf("%[^\n]s", s);` 定义了终止符为 `\n`，后面的 `getchar();` 是为了去掉 `\n`，否则会死循环。
- `queue` 定义为 `std::priority_queue<node> queue;`
- `sprintf(s, "%s", s + 1);` 可以理解为将字符串整体向前移动一位，并舍弃多余部分。

### 代码实现

```cpp
#include <cstdio>
#include <queue>
#include <unordered_map>
constexpr int MaxN = 1e4 + 5;
class node
{
  public:
    int key;
    int add;
    int time;
    friend bool operator<(const node &__x, const node &__y)
    {
        return __x.time > __y.time || (__x.time == __y.time && __x.key > __y.key);
    }
};
int k;
char s[MaxN];
std::priority_queue<node> queue;
int main()
{
    for (;;)
    {
        scanf("%[^\n]s", s);
        getchar();
        if (s[0] == '#')
        {
            break;
        }
        sprintf(s, "%s", s + 9);
        int x, y;
        x = 0;
        y = 0;
        for (;;)
        {
            if (s[0] == ' ')
            {
                break;
            }
            x *= 10;
            x += s[0] - '0';
            sprintf(s, "%s", s + 1);
        }
        sprintf(s, "%s", s + 1);
        for (;;)
        {
            if (s[0] == ' ' || s[0] == '\0')
            {
                break;
            }
            y *= 10;
            y += s[0] - '0';
            sprintf(s, "%s", s + 1);
        }
        node temp;
        temp.key = x;
        temp.add = y;
        temp.time = y;
        queue.push(temp);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        node temp = queue.top();
        queue.pop();
        printf("%d\n", temp.key);
        temp.time += temp.add;
        queue.push(temp);
    }
    return 0;
}
```

---

## 作者：xiezihanAKIOI (赞：0)

题意：
=

给你多个命令，每个命令如 Register 2004 200 对应于编号为 2004 的事件，每隔 200 秒发生一次，然后在给你一个 $k$，要你输出前 $k$ 个发生事件的编号，如果几个事件同时发生,输出事件编号小的。

思路：
=

用优先队列维护即可，队列中按照时间小的优先，时间相同的比较他们的编号，弹出 $k$ 次，每次弹出时，将时间加上 period 后放回队列中，更新下一次的出队时间。但是如果枚举全部放进队列，空间会爆，所以出一个进一个，不能全部保留。

代码实现：
=
```pascal
#include <bits/stdc++.h>

using namespace std;

struct NODE {
	int n_id, n_out, n_time;
	bool operator < (NODE a) const {
		if (a.n_time == n_time) return a.n_id < n_id;
		return n_time > a.n_time;
	}
};

string s;
priority_queue <NODE> q;

int main () {
	while (cin >> s) {
		if (s == "#") break;
		int x, y;
		cin >> x >> y;
		q.push ((NODE) {x, y, y});
	}
	int n;
	cin >> n;
	while (n--) {
		NODE f = q.top ();
		q.pop ();
		cout << f.n_id << endl;
		q.push ((NODE) {f.n_id, f.n_out, f.n_out + f.n_time});
	}
	return 0;
}
```


---

## 作者：Erotate (赞：0)

**题意：** 注册若干条数据，以 “#” 结束，每个数据以一个特定的周期出现。现在问你前 $n$ 条信息是什么？

这里我们用优先队列来做（有不懂的看优先队列[这里](https://so.csdn.net/so/search?q=%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97&t=&u=&urw=)）。对于每一条数据，每经过一个周期就入队一次。然后因为优先队列可以对这些入队的数据进行排序，所以队列里的第一项就是答案（按时间从小到大排序）。记得要弹出首项。
代码如下：
```cpp
struct task{
    int id,prd,t;
    bool operator<(const task& x)const{return t==x.t?id>x.id:t>x.t;}//重载运算符，时间不同按时间排，时间相同按编号排。
};
string s;
priority_queue<task>q;//创建一个优先队列。
int id,prd,n;
int main(){
    while(cin>>s){//输入并且把每一个数据第一个周期入队
        if(s=="#") break;
        cin>>id>>prd;
        q.push((task{id,prd,prd}));
    }
    cin>>n;
    for(int i=1;i<=n;++i){//对于每一个查询，输出并弹出队列第一项，再把下一个周期入队。
        task tm=q.top();
        q.pop();
        cout<<tm.id<<endl;
        q.push((task){tm.id,tm.prd,tm.t+tm.prd});
    }
    return 0;
}
```


---

## 作者：lowAltitudeFlyer (赞：0)

## Description
你的任务是编写一个称为Argus的系统。该系统支持一个Register命令
~~~
Register Q_num Period
~~~
该命令注册了一个触发器，它每$Period$秒钟就会产生一次编号为$Q\_num$的事件。你的任务是模拟出前$k$个事件。如果多个事件同时发生，先处理$Q\_num$小的事件。命令条数$n$不超过$1000$。
## Solution
用优先队列（堆）维护每个触发器的下一个事件，每次按照优先级（时间早的事件先发生，如果多个事件同时发生，先处理$Q\_num$小的事件）取出优先级最高的事件，输出其$Q\_num$，重复$k$次。
## Tips
- 每个触发器产生的第一次事件在第$Period$秒，不在第$0$秒
- priority_queue是一个大根堆，重载小于号时需要注意

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Item {
	int t, p, num; //t：time p：period num：Q_num 
	//重载小于号 
	bool operator < (const Item x) const {
		return t == x.t ? num > x.num : t > x.t; //时间早的事件先发生，如果多个事件同时发生，先处理Q_num小的事件 
	}
};
char opt[15];
priority_queue<Item> h; //优先队列 
int k;
int main() {
	while(1) {
		scanf("%s", opt);
		if(opt[0] == '#') break;
		Item x;
		scanf("%d%d", &x.num, &x.p);
		x.t = x.p; //该触发器第一次事件的时间是第p秒，不是第0秒 
		h.push(x); //插入优先队列 
	}
	scanf("%d", &k);
	for(int i = 1; i <= k; i++) { //模拟前k个事件 
		Item x = h.top(); h.pop(); //取出下一个事件 
		printf("%d\n", x.num);
		x.t += x.p; //更新该触发器的“下一个事件”的时间 
		h.push(x); //重新插入优先队列 
	}
	return 0;
}
```


---

