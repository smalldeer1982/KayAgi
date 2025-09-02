# queue

## 题目背景

你说的对，但是舞萌 DX 是一款后面忘了。

## 题目描述

**补充说明：这里的排队和传统的排队有出入。正在游玩的人为队列的前两位，所以正在游玩视为正在排队。**

机厅里有一台游戏机，每次可供最多两人同时游玩。但是来玩的人显然不止两个！这个时候他们就需要排队了，而你需要写一个程序维护这个队列，并在他人游玩结束后通知接下来上场的人。在整个过程中，有以下几种事件可能发生：

- `start`：一局游戏开始。若这不是第一局游戏，则上一局的参与者**在这一局游戏开始前一瞬间**按照原本的顺序回到队尾。此时你应该按在队列中的顺序输出这一局上场的人的名字（正常来讲是队列前两位或者唯一一个人），若有两个则以空格分割。若这一局无人上场，则输出 `Error` 并忽略这条事件。

- `arrive x`：$x$ 到达机厅并且将自己加入队尾，此时 $x$ 不应该在排队，否则输出 `Error` 并忽略这条事件。若该事件成功执行则输出 `OK`。

- `leave x`：$x$ 离开机厅并离开队列。此时 $x$ 应该在排队但不应该在游玩，否则输出 `Error` 并忽略这条事件。若该事件成功执行则输出 `OK`。

你需要维护队列信息，并输出上述事件中要求的输出。

## 说明/提示

**【样例说明】**

样例 $1$ 中发生了如下的事件：

- 第一次 `start` 时队列并没有任何人，输出 `Error`。
- `A` 随即加入队列。
- 第二次 `start` 时仅有 `A` 一个人，所以输出 `A`。
- `B, C, D` 随即依次加入队列。
- 第三次 `start` 时 `B, C` 上场。
- `C` 试图离开，但是他在游玩。所以输出 `Error`。
- `D` 成功离开。
- 第四次 `start` 时 `A, B` 上场。
- `A` 试图加入队列，但是他已经在队列中。输出 `Error`。
- `D` 重新加入队列。
- `E` 试图离开，但是他根本不在排队，输出 `Error`。
- 第五次 `start` 时 `C, D` 上场。

样例 $2$ 中，`A, B, C` 依次入队，操作合法，输出三个 `OK`。

**【数据范围】**

对于 $20\%$ 的数据，保证 $n=1$。

对于 $40\%$ 的数据，保证 $n\le 2000$。

对于另外 $20\%$ 的数据，保证没有 `leave` 操作。

对于另外 $20\%$ 的数据，人名只有可能是单个大写字母。

对于 $100\%$ 的数据，保证 $1 \le n\le 10^5$，人名仅含有大小写字母且长度不超过 $10$。

**本题输入输出量较大，请注意使用合理的输入输出方式。**

## 样例 #1

### 输入

```
14
start
arrive A
start
arrive B
arrive C
arrive D
start
leave C
leave D
start
arrive A
arrive D
leave E
start```

### 输出

```
Error
OK
A
OK
OK
OK
B C
Error
OK
A B
Error
OK
Error
C D```

## 样例 #2

### 输入

```
3
arrive A
arrive B
arrive C```

### 输出

```
OK
OK
OK```

# 题解

## 作者：Register_int (赞：21)

为啥要放模拟啊 ![](//图.tk/k)

来理清思路我们要维护什么：

- 当前排队的人（按顺序）。
- 现在正在游玩的人。
- 每个人是否在排队/游玩。

先来考虑维护当前排队的人。我们需要一个支持 $O(\log n)$ 进行从尾部插入，并从任意位置删除元素的结构。这里我因为对 `list` 不熟悉而选择了 `set`：定义每个人的编号为当前队尾的人的编号 $+1$，为空时则是 $1$，即可保证人是有序的。

接下来定义两个 `string->int\bool` 的 `map`：`inq`（$\text{InQueue}$） 和 `ing`（$\text{InGame}$），分别表示每个人在队内的编号，以及是否在游玩。再用一个 `string` 数组 $t$ 以及一个 $num$ 来维护正在游玩的人与人数。我们就成功维护了所有需要的信息。定义大致如下：

```cpp
struct node {
	string s; int id;
	bool operator < (const node &rhs) const { return id < rhs.id; }
}; set<node> q;

map<string, int> inq;
map<string, bool> ing;
```

分别来看三种操作：

#### arrive

如果目标处于对内或者正在游戏中，那么返回 `0` 表示 `Error`。否则按前文插入即可。

```cpp
inline
bool try_insert(string s) {
	if (inq[s] || ing[s]) return 0;
	int x = q.empty() ? 0 : prev(q.end())->id;
	return q.insert({ s, inq[s] = x + 1 }), 1;
}
```

这里 `prev(q.end())->id` 的意思是查找 `set` 末尾这个人的编号。

#### leave

只需判断离开的人是否在队内。我们记录了每个人的编号，就能很方便的删除这个人。

```cpp
inline
bool try_erase(string s) {
	if (!inq[s]) return 0;
	return q.erase({ s, inq[s] }), inq[s] = 0, 1;
}
```

#### start

分三步进行操作：

1. 将正在游玩的人清空，并且插入到当前队伍末端（使用 `try_insert` 完成）。
2. 确定游玩人数，如果队伍为空返回 `Error`。
3. 移除队伍前端需要游玩的人并储存到 `t` 数组中，更改正在游戏的状态（使用 `try_erase` 完成）并输出。

实现比较简单。

```cpp
string t[2]; int num;

inline 
void try_start() {
	for (int i = 0; i < num; i++) ing[t[i]] = 0, try_insert(t[i]);
	num = min<int>(2, q.size());
	if (!num) return puts("Error"), void();
	for (int i = 0; i < num; i++) {
		try_erase(t[i] = q.begin()->s), ing[t[i]] = 1;
		cout << t[i] << " ";
	}
	puts("");
}
```

前两种操作根据返回值输出 `OK` 或 `Error` 即可。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

struct node {
	string s; int id;
	bool operator < (const node &rhs) const { return id < rhs.id; }
}; set<node> q;

map<string, int> inq;
map<string, bool> ing;

inline
bool try_insert(string s) {
	if (inq[s] || ing[s]) return 0;
	int x = q.empty() ? 0 : prev(q.end())->id;
	return q.insert({ s, inq[s] = x + 1 }), 1;
}

inline
bool try_erase(string s) {
	if (!inq[s]) return 0;
	return q.erase({ s, inq[s] }), inq[s] = 0, 1;
}

string t[2]; int num;

inline 
void try_start() {
	for (int i = 0; i < num; i++) ing[t[i]] = 0, try_insert(t[i]);
	num = min<int>(2, q.size());
	if (!num) return puts("Error"), void();
	for (int i = 0; i < num; i++) {
		try_erase(t[i] = q.begin()->s), ing[t[i]] = 1;
		cout << t[i] << " ";
	}
	puts("");
}

int n; string opt, s;

int main() {
	for (scanf("%d", &n); n--;) {
		cin >> opt;
		if (opt[0] == 'a') cin >> s, puts(try_insert(s) ? "OK" : "Error");
		if (opt[0] == 'l') cin >> s, puts(try_erase(s) ? "OK" : "Error");
		if (opt[0] == 's') try_start();
	}
}
```

码量在 $1\text{KB}$ 左右，算是一道小清新模拟题。

---

## 作者：CleverRaccoon (赞：14)

## 前言

看没有使用 `list` 的题解，所以我发一篇使用 `list` 的题解。

我的代码没有使用数组，使用了很多 STL 中的容器（我觉得使用 STL 真的很方便）。

下面来具体讲一下我的思路。

## 思路

先说我的存储思路：

- 先用一个 `list` 来表示队列（为什么不用 `queue` 呢？因为需要删除元素时，`queue` 不方便，可以 $\mathcal{O}(1)$ 删除元素的容器是链表 `list`）。

```cpp
list<string> q;
```

- 用一个 `unordered_set` 来记录正在排队的人，方便之后处理“某个人是否在队列中”这个问题（为什么不用 `set` 呢？因为我们不需要排序，使用无序的 `unordered_set` 可以提升时间复杂度，具体地讲，`set` 删除元素时间复杂度 $\mathcal{O}(\log n)$，而 `unordered_set` 删除元素的时间复杂度是 $\mathcal{O}(1)$，后者明显比前者快一些）。

```cpp
unordered_set<string> us;
```

- 用两个字符串表示正在游玩的两个人（即使两个人正在游玩，使用 `list` 模拟的队列中的前两个元素依然是他们，他们玩完以后才会把他们放到队尾）。

```cpp
string a="",b="";
```

- 用一个 `unordered_map` 来记录每个人在链表中对应的地址（这也是精髓），这样可以 $\mathcal{O}(1)$ 地查询到每个人在链表中对应的位置了，方便了链表的删除操作。这里 `list<string>::iterator>` 是一个迭代器，可以记录每个人在链表中对应的地址。

```cpp
unordered_map<string,list<string>::iterator> um;
```

本题分为三种操作，我们分别来看。

### 第一种操作：`start`

首先我们判断队列是否为空，如果为空直接输出 `Error`，不继续进行后面的操作。

```cpp
if(q.empty()){
	puts("Error");
	continue;
}
```

接着，新一局游戏的开始代表着正在玩的人需要到队尾重新排队，等待下一次游玩。但有可能有两个人在玩，也有可能没有人在玩，这里就需要特殊判断一下了。思路是先把两个（也有可能是一个）人加入队尾，然后再把队头的两个（或一个）人从队头（游戏机座位上）弹出。这里要重新记录一下当前这个人在链表中对应的地址。

```cpp
if(a!=""){
	q.push_back(a),q.pop_front();
	um[a]=--q.end();
}
if(b!=""){
	q.push_back(b),q.pop_front();
	um[b]=--q.end();
}
```

然后，获取新一局的玩家。先获取第一个人，然后判断是否还有第二个人，没有第二个人那么将记录第二个人名字的字符串设为空。

```cpp
a=q.front();
q.pop_front();
if(!q.empty()){
	b=q.front();
}else{
	b="";
}
```

因为要根据队列是否为空这个条件来判断有没有第二个玩游戏的人，因此我们要把第一个人从队列里先弹出，然后再加到队首。这里要重新记录一下当前这个人在链表中对应的地址。

```cpp
q.push_front(a);
um[a]=q.begin();
```

最后输出即可。

```cpp
cout<<a;
if(b!="")cout<<" "<<b;
cout<<endl;
```

### 第二种操作：`arrive`

首先输入到达的人的名字。

```cpp
string k;
cin>>k;
```

接下来，通过 `unordered_set`，找到里面是否已经有这个人了。如果已经有了，那么输出 `Error`。

```cpp
if(us.find(k)!=us.end()){
	puts("Error");
	continue;
}
```

将这个人加到队尾并加入 `unordered_set` 当中。注意，要重新记录这个人在链表中对应的地址。这里 `q.end()` 是获取 `list` 最后一个元素后面一个位置的地址，但不是最后一个元素的，因此要 `--q.end()`。为什么不是 `-1` 呢？因为只重载了 `--` 这个运算符。接着，输出 `OK` 即可。

```cpp
q.push_back(k);
um[k]=--q.end();
us.insert(k);
puts("OK");
```

### 第三种操作：`leave`

这个操作就体现了使用 `list` 的好处。

首先输入要离开的人的名字。

```cpp
string k;
cin>>k;
```

接着，如果要离开的人正在玩游戏机或者找不到这个人，输出 `Error`。

```cpp
if(k==a||k==b||us.find(k)==us.end()){
	puts("Error");
	continue;
}
```

最后，从 `list` 和 `unordered_set` 之中删除掉这个人，然后输出 `OK` 即可。注意我们之前记录了每个人在链表中对应的地址，所以直接拿过来用就好了。无论是查找地址还是删除，都是 $\mathcal{O}(1)$ 的。

```cpp
q.erase(um[k]);
us.erase(us.find(k));
puts("OK");
```

## 代码

最后放上完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
list<string> q;
string a="",b="";
unordered_set<string> us;
unordered_map<string,list<string>::iterator> um;
int main(){
	int n;
	cin>>n;
	while(n--){
		string s;
		cin>>s;
		if(s=="start"){	// 新一局开始。
			if(q.empty()){	// 当前没有人排队。
				puts("Error");
				continue;
			}
			if(a!=""){
				q.push_back(a),q.pop_front();	// 加到队尾，并删除队首元素。
				um[a]=--q.end();	// 记录这个人在链表中对应的地址。
			}
			if(b!=""){
				q.push_back(b),q.pop_front();	// 同上。
				um[b]=--q.end();	// 同上。
			}
			a=q.front();
			q.pop_front();
			if(!q.empty()){	// 有可能一开始排队人数只有一个人（弹出去以后链表中就没有元素了），没法两个人一起玩。
				b=q.front();
			}else{
				b="";	// 如果只有一个人能玩，那么将记录第二个人名字的字符串设为空。
			}
			q.push_front(a);	// 将正在玩游戏的人添加到队首（之前为了要根据队列是否为空这个条件来判断有没有第二个玩游戏的人，因此将第一个人从队列里先弹出，然后再加到队首）。
			um[a]=q.begin();	// 记录地址。
			cout<<a;	// 输出。
			if(b!="")cout<<" "<<b;
			cout<<endl;
		}else if(s=="arrive"){	// 第二种操作。
			string k;
			cin>>k;	// 先输入。
			if(us.find(k)!=us.end()){	// 如果以前有这个元素，那么输出“Error”。
				puts("Error");
				continue;
			}
			q.push_back(k);	// 入队。
			um[k]=--q.end();	// 记录地址。
			us.insert(k);	// 加入集合。
			puts("OK");
		}else if(s=="leave"){	// 第三种操作。
			string k;
			cin>>k;
			if(k==a||k==b||us.find(k)==us.end()){	// 如果正在游玩或者这个人根本就没在排队，那么输出“Error”。
				puts("Error");
				continue;
			}
			q.erase(um[k]);	// 删除掉这个人。
			us.erase(us.find(k)); 	// 同上。
			puts("OK");
		}
	}
	return 0;
}
```

这里是 [AC 记录](https://www.luogu.com.cn/record/120699575)。

谢谢大家！


---

## 作者：icypenguin (赞：10)

## 题目分析

我们需要一个队列来模拟这个操作，还需要用一个 map 标记它是第几次出现。

如果原来是 $1$ $2$ $3$ $4$，后面 $3$ 离开了队列，然后 $3$ 又加入了队列，那么应该执行的是 $1$ $2$ $4$ $3$，而不是 $1$ $2$ $3$ $4$ $3$。

所以我们需要使用 map 来判断这个数字是否是最新一次出现，只有最新一次出现的可以参与游戏。

对于操作 ```start```，直接遍历整个队列，如果这个序号是最后一次出现，那他就成功开始游戏，把它输出即可。如果已经有 $2$ 个符合条件的序号，则停止遍历。

对于操作 ```arrive x```，我们用 map 判断 $x$ 是否在队列中，如果 ```in[x] != 0```，这种情况我们设置 ```in[x] = ++c[x]```，操作成功，输出 ```OK```，```c[x]``` 表示这次是第几次出现。否则输出 ```Error```。

对于操作 ```leave x```，我们用 map 判断 $x$ 是否在队列中，如果 ```in[x] != 0``` 并且它不是正在玩游戏，则我们设置 ```in[x] = 0```，操作成功，输出 ```OK```。否则输出 ```Error```。

时间复杂度是 $O(n \log n)$ 的。

## 代码实现

```cpp
#include <iostream>
#include <queue>
#include <map>
#define ll long long
using namespace std;
struct node{
    string s;
    ll times;
};
queue<node> q;
map<string, ll> in, t;
string lst[1000005];
ll n, tot = 0, ti[1000005];
int main(){
    cin >> n;
    t.clear();
    in.clear();
    while (n--){
        string s;
        cin >> s;
        if (s == "start"){
            for (ll i = 1; i <= tot; i++){
                q.push(node{lst[i], ti[i]});
            }
            tot = 0;
            bool flg = false;
            ll cnt = 0;
            while (!q.empty()){
                node x = q.front();
                if (in[x.s] == x.times && cnt <= 1){
                    lst[++tot] = x.s;
                    ti[tot] = x.times;
                    cnt++;
                    cout << x.s << " ";
                    if (cnt == 2){
                        q.pop();
                        break;
                    }
                    flg = true;
                }
                q.pop();
            }
            if (flg){
                cout << endl;
            }else{
                cout << "Error" << endl;
            }
        }else if (s == "arrive"){
            string x;
            cin >> x;
            if (in[x] != 0){
                cout << "Error" << endl;
            }else{
                cout << "OK" << endl;
                if (t[x] == 0){
                    in[x] = 1;
                    t[x] = 1;
                }else{
                    t[x]++;
                    in[x] = t[x];
                }
                q.push(node{x, t[x]});
            }
        }else{
            string x;
            cin >> x;
            bool flg = false;
            for (ll i = 1; i <= tot; i++){
                if (lst[i] == x){
                    flg = true;
                    break;
                }
            }
            if (in[x] != 0 && !flg){
                in[x] = 0;
                cout << "OK" << endl;
            }else{
                cout << "Error" << endl;
            }
        }
    }
    return 0;
}
```






---

## 作者：ManGo_Mouse (赞：7)

### 题目分析

从题目的描述来看，这明显是一道模拟题。

首先想清楚，题目需要我们维护什么：

+ 当前排队的人。
+ 当前正在玩舞萌 DX 的人。
+ 每个人的排队/玩舞萌 DX 情况。

第一点很容易就可以想到使用队列，这里我选择使用 `deque<string>` 双端队列，首尾插入时间复杂度 $O(1)$，之所以不用 `queue`，原因后面会讲。

第二点也不难，可以用两个 `string` 记录正在玩舞萌 DX 的玩家名 `player1` 和 `player2`。

第三点更加简单，使用一个 `map<string,bool>` 记录，`true` 表示正在排队/玩舞萌 DX，`flase` 反之。

```cpp
deque<string> d;
map<string,bool> iiq;
string op,x,player1,player2; // op 和 x 分别表示操作和操作参数
```

接下来依次写出各操作代码：

#### start

分步进行：

+ 将上一局的玩家放回队尾。
+ 将当前队首的两名玩家弹出队列并将它们记录为玩家。
+ 输出新玩家。

第一点使用 `push_back()` 方法，将上局玩家放回队尾，再检测队伍内是否有人，因为上一局可能只有一个玩家，所以需要 `if` 检测一下非空。

第二点则是使用 `pop_front()` 和 `d.front()` 方法出队和获取队首，同样的，队伍里可能只有一个玩家，也需要 `if` 检测一下非空，**记录玩家的变量一定要初始化为空！**否则你会收获五彩斑斓的世界。

```cpp
if(op[0] == 's'){
    if(player1 != "")d.push_back(player1);
    if(player2 != "")d.push_back(player2);
    if(!d.size())printf("Error\n");
	else {
        player1 = player2 = "";
        if(d.size()){
            player1 = d.front();
            d.pop_front();
        }
        if(d.size()){
            player2 = d.front();
            d.pop_front();
        }
        printf("%s %s\n",player1.c_str(),player2.c_str());
    }
}
```

#### arrive

我们可检测 `iiq[x]` 是否为 `flase`，然后放入队尾并将 `iiq[x]` 设为 `true`，输出 `OK`，否则输出 `Error`。

```cpp
else if(op[0] == 'a'){
    cin>>x;
    if(!iiq[x]){
        iiq[x] = 1;
        d.push_back(x);
        printf("OK\n");
    }
    else printf("Error\n");
}
```

#### leave

与 `arrive` 相反，我们需要检测 `iiq[x]` 是否为 `true`，同时还要确保 `x` 不等于 `player1` or `player2`。

如果满足条件，将 `iiq[x]` 设为 `flase` 并使用 `d.erase()` 与 `find()` 方法找到 `x` 的位置和删除，现在你明白为什么用 `deque` 了吧，因为 `deque` 支持迭代器，有查找元素位置的方法，当然你也可以自己写一个 `queue` 的删除函数，效率一样，都是 $O(n)$。

```cpp
else {
    cin>>x;
    if(iiq[x] && player1 != x && player2 != x){
        iiq[x] = 0;
        d.erase(find(d.begin(),d.end(),x));
        printf("OK\n");
    }
    else printf("Error\n");
}
```

你有没有好奇，为什么我不直接使用 `find()` 查找，而是要再写一个 `map` 呢？

因为……之前酱紫 $\text {T L E}$ 了……`find()` $O(n)$ 的效率太慢，但是我们只要知道 `x` 存不存在，所以用 `map` 维护，$O(1)$。

### 完整 AC 代码

```cpp
// 代码仅供参考。
// 学习抄题解，名字两行泪。
#include<bits/stdc++.h>
using namespace std;
deque<string> d;
map<string,bool> iiq;
string op,x,player1,player2;
int n;
int main(){
    cin>>n;
    while(n --){
        cin>>op;
        if(op[0] == 's'){
            if(player1 != "")d.push_back(player1);
            if(player2 != "")d.push_back(player2);
            if(!d.size())printf("Error\n");
            else {
                player1 = player2 = "";
                if(d.size()){
                    player1 = d.front();
                    d.pop_front();
                }
                if(d.size()){
                    player2 = d.front();
                    d.pop_front();
                }
                printf("%s %s\n",player1.c_str(),player2.c_str());
            }
        }
        else if(op[0] == 'a'){
            cin>>x;
            if(!iiq[x]){
                iiq[x] = 1;
                d.push_back(x);
                printf("OK\n");
            }
            else printf("Error\n");
        }
        else {
            cin>>x;
            if(iiq[x] && player1 != x && player2 != x){
                iiq[x] = 0;
                d.erase(find(d.begin(),d.end(),x));
                printf("OK\n");
            }
            else printf("Error\n");
        }
    }
    return 0;
}
```

这题总体难度不大，只要细节处理好，基本没什么问题，本题解如有瑕疵，还望大佬指教。

---

## 作者：stripe_python (赞：5)

 _Updated 2023/8/14：因为没介绍平板电视没过审，提交后发现题解通道关了，不过代码是能过 Hack 的。_ 
 
 _Updated 2023/8/22：修改代码。_

### Step1：代码结构分析
看到题是典型的数据结构模拟，让我们支持 `start`、`push`、`pop` 三种操作，均摊 $O(\log{n})$ 及以下。 

这种模拟题本蒟蒻的习惯是面向对象写，先设计一种类，如下所示：
```cpp
class Manager {
public:
    pair<string, string> start();
    bool push(const string& s);
    bool pop(const string& s);
};
```
+ `start` 函数返回两个上场人员的名字，可以返回空字符串；
+ `push` 函数将人员加入队列，返回是否成功；
+ `pop` 函数将人员移出队列，返回是否成功；

于是我们的代码雏形如下：
```cpp
#include <bits/stdc++.h>
#define endl '\n'
// endl定义为换行符防止刷新缓冲，卡常小技巧 
using namespace std;

class Manager {
public:
    pair<string, string> start();
    bool push(const string& s);
    bool pop(const string& s);
};

int n;
string c, opt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    Manager man;
    // 这一块就是纯调API了，不解释
    while (n--) {
        cin >> opt;
        if (opt == "start") {
            auto h = man.start();
            if (h.first.empty()) {
                cout << "Error" << endl;
            } else if (h.second.empty()) { 
                cout << h.first << endl;
            } else {
                cout << h.first << ' ' << h.second << endl;
            }
        } else if (opt == "arrive") {
            cin >> c;
            bool ok = man.push(c);
            if (ok) cout << "OK" << endl;
            else cout << "Error" << endl;
        } else if (opt == "leave") {
            cin >> c;
            bool ok = man.pop(c);
            if (ok) cout << "OK" << endl;
            else cout << "Error" << endl;
        }
    }
    return 0;
}
```
### Step2：数据结构分析
考虑用二元组 $(x, user)$ 记录一个人，$x$ 记录入队时间，$user$ 记录人名。    

定义结构体如下：
```cpp
struct node {
    int x;
    string user;
        
    node(int _x, string _u) : x(_x), user(_u) {}
        
    bool operator< (const node& other) const {
        return x < other.x;   // 这里按入队时间排序
    }
};
```

现在所有要支持的操作摆出来了：     
1. $O(\log{n})$ 根据 $user$ 查找；
2. $O(\log{n})$ 添加元素；
3. $O(\log{n})$ 删除。


现在来具体分析一下各个操作：   
1. `push`：获取队列中的最后一个 $x$，并将 $(x + 1, user)$ 放入队列；
2. `pop`：根据哈希表获取 $s$ 的 $x$，删除 $(x, s)$；
3. `start`：设 $x, y$ 表示当前在玩的玩家，先将 $x, y$ 入队，接下来取出队列的前两项，pop出来返回即可。

考虑使用哈希表记录每个 $user$ 的 $x$，又要记录排队顺序，还要 $O(\log{n})$ 查找，首先想到`set`。        

~~然而本蒟蒻太弱了，比赛时调两个小时的`set`调不出来QwQ~~     

由上，支持对数的增删改查——平衡树！

### Step3：平衡树实现
注意到，本题元素不重复——     
平板电视大法好！
```cpp
#include <bits/extc++.h>
using namespace __gnu_pbds;
#define treetype tree<node, null_type, less<node>, rb_tree_tag, tree_order_statistics_node_update>

```

简单介绍一下：         
+ `null_type`：无映射；       
+ `rb_tree_tag`：红黑树；
+ `tree_order_statistics_node_update`：用这个才支持查询排名。

再介绍一下 `tree` 的常用操作：    
+ `erase`：从树中移出给定的 `node`；
+ `insert`：插入给定的 `node`；
+ `find_by_order`：根据排名找 `node`，注意返回的是指针；
+ `order_by_key`：根据 `node` 获取排名。

`tree` 的常数略大，但本题来说可以接受 $O(n\log{n})$ 的复杂度。

详细介绍见 [OI Wiki](https://oi-wiki.org/lang/pb-ds/tree/)。

### Step4：AC Code
思路讲过了，代码就不放太多注释了，自认为码风还是可读性较高的。

只放 `Manager` 的代码。
```cpp
using namespace __gnu_pbds;   // 平板电视大法好！ 

class Manager {
private:
    struct node {
        int x;
        string user;
        
        node(int _x, string _u) : x(_x), user(_u) {}
        
        bool operator< (const node& other) const {
            return x < other.x;    // 这里按入队时间排序
        }
    };
    string x, y;
#define treetype tree<node, null_type, less<node>, rb_tree_tag, tree_order_statistics_node_update>
    treetype tr;    // 平衡树 
    map<string, int> st;   // 记录入队时间 
    
    void show() {   // 调试用的 
        for (int i = 0; i < tr.size(); i++) {
            cout << tr.find_by_order(i)->user << " ";
        }
        cout << endl;
    }
    
    bool find(const string& s) {
        return st.count(s);
    }
    
    bool _pop(const string& s) {   
        if (tr.empty() || s.empty()) return false;
        if (!find(s)) return false;
        tr.erase(node(st[s], s));    // 删除(st[s], s) 
        st.erase(st.find(s));    // 哈希表一并要删除 
        return true;
    }
    
    bool _push(const string& s) {
        if (find(s)) return false;
        if (s.empty()) return false;
        //show();
        // 计算当前入队时间 
        int w = tr.empty() ? 0 : (tr.find_by_order(tr.size() - 1)->x) + 1;
        tr.insert(node(w, s));   // 插入(w, s) 
        st[s] = w;   // 设置哈希表 
        return true;
    }
    
public:
    pair<string, string> start() {
        _push(x), _push(y);
        //show();
        if (tr.empty()) return {"", ""};
        else if (tr.size() == 1) x = tr.find_by_order(0)->user, _pop(x);
        else x = tr.find_by_order(0)->user, y = tr.find_by_order(1)->user, _pop(x), _pop(y);
        return {x, y};
    }
    
    bool push(const string& s) {
        if (x == s || y == s) return false;
        return _push(s);
    }
    
    bool pop(const string& s) {
        if (x == s || y == s) return false;
        return _pop(s);
    }
};
```



---

## 作者：Flanksy (赞：4)

### 模拟

2023/8/16：感谢 [xing_yu](https://www.luogu.com.cn/user/384822) 和 [hhyz100413](https://www.luogu.com.cn/user/876418) 告知代码被 hack，现已修复。

------------

看一眼题目，鉴定为维护序列，分析一下操作。

- 将被标记的元素移动到队尾并取消标记，标记并输出当前序列第一个或前两个元素，要求序列不空。
- 在队尾加入元素，要求元素不能已经在序列中。
- 删除任意元素，要求元素在序列中且没有被标记。

可以发现一个关键性质：**序列元素不重**。

由于元素不重，链表可以做到 $O(1)$ 查找，记录每个元素的位置即可。同时链表自身 $O(1)$ 插入删除的特性也很优秀。

不想手写链表的话，`list` 是一个很好的选择。

使用 `unordered_map` 记录每个元素是否存在和每个元素在 `list` 中对应的迭代器，注意将元素从队首扔到队尾的时候需要更新。

**被 hack 实际是因为读错题目。认为队列的前两位始终保持游玩状态是错误的，只有最近一次 start 时的队首才处于游玩状态，因此需要记录当前正在游玩者的个数用于判断，即被标记的元素个数。**

先前代码中已经使用变量记录当前游玩人数，只在原有基础上做了轻微的改动。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_map<string,list<string>::iterator> ex;
unordered_map<string,bool> on;
list<string> q;
int last_sum;//从 start 函数内的静态变量改为全局变量 
void arrive(){
    static string x;
    cin>>x;
    if(on[x]) return cout<<"Error"<<'\n',void();
    on[x]=1,q.push_back(x);
    ex[x]=prev(q.end());
    cout<<"OK"<<'\n';
}
void start(){
    static bool started;
    if(q.empty()) return cout<<"Error"<<'\n',void();
    if(started) for(int i=1;i<=last_sum;i++){
        q.push_back(q.front());
        ex[q.front()]=prev(q.end());
        q.pop_front();
    }
    started=1;
    if(q.size()==1u) last_sum=1,cout<<q.front()<<'\n';
    else last_sum=2,cout<<q.front()<<' '<<*next(q.begin())<<'\n';
}
bool isplaying(string x){//新添加的函数 
	auto it=q.begin();
	for(int i=1;i<=last_sum;i++){
		if(it==q.end()) break;
		if(*it++==x) return 1;
	}
	return 0;
}
void leave(){
    static string x;
    cin>>x;
    if(!on[x]||isplaying(x)) return cout<<"Error"<<'\n',void();
    on[x]=0,q.erase(ex[x]);
    cout<<"OK"<<'\n';
}
int T;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        static string x;
        cin>>x;
        switch(x[0]){
	        case 'a':arrive();break;
	        case 's':start();break;
			case 'l':leave();break;
		}
    }
    return 0;
}
```

---

## 作者：_HyperV_ (赞：3)

一眼模拟。

需要维护的东西可以根据操作求得：

- start：正在玩游戏的 $1$ 或 $2$ 个人；
- arrive：当前在排队但没玩游戏的队列、每个人是否在排队、游玩；
- leave：每个人是否在排队、游玩。

---

## 如何维护

**正在玩游戏的人**：

我们使用 $p_1$、$p_2$ 两变量存储，优先保证 $p_1$ 有值，当 $p_1$ 为空时上一轮无人游玩，$p_2$ 为空时上一轮仅有一人游玩。

> tips：由于优先保证 $p_1$ 有值，故 $p_2$ 为空时 $p_1$ 非空。

---

**当前在排队但没玩游戏的队列**：

用数组模拟队列并惰性删除即可。

> tips：将正在玩游戏的人放到队首，并在玩完游戏后将其放到队尾，只用维护一个“队列”即可。

---

**每个人是否在排队、游玩**：

用 `map` 映射名字到队列中的位置即可（tips：为什么不映射 `bool`，在这个[讨论帖](https://www.luogu.com.cn/discuss/658858)里说的已经很明白了）。

要定义的东西如下：

```cpp
const int Maxn = 1e6 + 7;
int Q, l = 1, r = 1, len;
string q[Maxn], p1, p2;
map <string, int> m;
```

## 操作中的细节

**start**

只要队列里有人，游戏就能进行。因为根据题意描述，若只有 A 在游戏且无人排队、A 可在结束游戏后成为队首并加入下一轮游戏，故**队列无人**时输出 `Error`。

否则，将上一轮游玩的人放回队尾，并取出这一轮游玩的人（$\geq 1$，想一想，为什么），将其名字输出。

具体实现如下：

```cpp
if(opt == "start") {
	p1 = p2 = "";
	while(l < r && len) {
	    while(l < r && m[q[l]] != l) ++l;
	    if(l < r)
	    	m[q[l]] = r, q[r++] = q[l], ++l;
	    --len;
	}

	while(l < r && m[q[l]] != l)
		++l;
	if(l == r) {
		puts("Error");
		continue;
	}
	p1 = q[l]; 
    cout << p1;
	++len;
	   
	int pos = l + 1;
    while(pos < r && m[q[pos]] != pos) 
		++pos;
    if(pos < r) 
		p2 = q[pos], cout << ' ' << p2, ++len;
    puts("");
}
```

**arrive**

没什么好说的，看代码：

```cpp
if(opt == "arrive") {
	cin >> t;
	if(m[t]) 
		puts("Error");
	else 
		q[r++] = t, m[t] = r - 1, puts("OK"); 
}
```

**leave**

若 `x` 在队列里且 `x` 不为玩家，`x` 可以离队；否则不能。

```cpp
if (opt == "leave") {
	cin >> t;
	if(m[t] && t != p1 && t != p2) 
		m[t] = 0, puts("OK");
	else 
		puts("Error");
}
```

> **Warning**
>
> 考场并没有卡暴力 $O(n)$ 删除的做法，但考试结束后同机房的 @幻想繁星 就申请加了 hack 数据（[试图卡掉时的讨论帖](https://www.luogu.com.cn/discuss/658652)、[hack 数据](https://www.luogu.com.cn/discuss/658935)）

_Talk is cheap, show you the code._

```cpp
#include <bits/stdc++.h>

using namespace std;
const int Maxn = 1e6 + 7;

int Q, l = 1, r = 1, len;
string q[Maxn], p1, p2;
map <string, int> m;

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> Q;
	string opt, t;
	while(Q--) {
		cin >> opt;
		if(opt == "start") {
			p1 = p2 = "";
            while(l < r && len) {
                while(l < r && m[q[l]] != l) ++l;
                if(l < r)
                	m[q[l]] = r, q[r++] = q[l], ++l;
                --len;
            }

            while(l < r && m[q[l]] != l)
				++l;
            if(l == r) {
				puts("Error");
				continue;
			}
			p1 = q[l]; 
            cout << p1;
			++len;
            
			int pos = l + 1;
            while(pos < r && m[q[pos]] != pos) 
				++pos;
            if(pos < r) 
				p2 = q[pos], cout << ' ' << p2, ++len;
            puts("");
		}
		else if(opt == "arrive") {
			cin >> t;
			if(m[t]) 
				puts("Error");
			else 
				q[r++] = t, m[t] = r - 1, puts("OK"); 
		}
		else {
			cin >> t;
			if(p1 == t || p2 == t || !m[t]) 
				puts("Error");
			else 
				m[t] = 0, puts("OK");
		}
	}
	
	return 0;
}
```

---

## 作者：Code_Fish_GoodBye (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9518)

## 思路
一道稍稍有点复杂的模拟好题。

本题的关键性就在于需要实现的 ```leave``` 函数必须支持任意位置的删除，任意元素的查询，这对于 ```queue``` 或是 ```deque``` 是十分不利的。

故本题使用另外一种 STL： ```list``` 实现。

但是，```list``` 的查询其实也是比较耗费时间的，那么我们可以使用 $Map$ 来映射出每一个人的标号即可。

创建一个没有任何元素的空 ```list``` 容器：```std::list<T> values;```

下附 ```list``` 常用代码：

| 方法 | 作用 |
| :----------: | :----------: |
| ```begin()``` | 返回指向容器中第一个元素的双向迭代器。 |
| ```end()``` | 返回指向容器中最后一个元素所在位置的下一个位置的双向迭代器。 |
|```rbegin()```  | 返回指向最后一个元素的反向双向迭代器。 |
| ```rend()``` | 返回指向第一个元素所在位置前一个位置的反向双向迭代器。|
| ```size()``` | 返回当前容器实际包含的元素个数。 |
|```front()```|	返回第一个元素的引用。|
|```back()```|	返回最后一个元素的引用。|
| ```push_front()``` | 在容器头部插入一个元素。 |
| ```pop_front()``` | 删除容器头部的一个元素。 |
| ```push_back()``` | 在容器尾部插入一个元素。 |
| ```insert()```  | 在容器中的指定位置插入元素。 |
| ```erase()``` | 删除容器中一个或某区域内的元素。 |
| ```remove(val)```	|删除容器中所有等于 val 的元素。	 |
| ```remove_if()``` | 删除容器中满足条件的元素。 |
| ```count()``` | 查询容器中某值的出现次数。 |

最后依照题意模拟即可。


---

## 作者：eoinlee (赞：3)

## 题外话

~~不愧是基础赛，CSP-J 多年 T3 大模拟的传统也是学得很到位~~

## 题内话

本题解使用结构体模拟队列的方式处理本题。

## 细节

吐槽一下题面，很多细节没有说清楚（这算是造数据的人让错解代码爆大零的关键策略吧），**所以第一次看题的时候建议先看样例和样例说明**。先来看一看题目的三种操作中的细节。

### start 操作

> 1.   一局游戏开始。
> 2.   若这不是第一局游戏，则上一局的参与者按照原本的顺序回到队尾。
> 3.   此时你应该按在队列中的顺序输出这一局上场的人的名字（正常来讲是队列前两位或者唯一一个人），若有两个则以空格分割。
> 4.   若这一局无人上场，则输出 `Error` 并忽略这条事件。

1.   废话。
2.   也就是说，输入一个 `start` 既标志着当前这一局的开始，也标志着上一局的一到两个玩家**按照原本的顺序**回到队尾。什么是**原本的顺序**？就是上一局的这两个玩家在开始上一局时从队首进入游玩状态的顺序。
3.   假如队列里只有一个人，那么就只能让一个人开始玩。假如队列里有两个人或更多，那么就让队首的两个人按顺序进入游戏并输出。
4.   **「无人上场」**的本质是没有人排队。这也就意味着之前没有人进行过游戏，因为如果进行过游戏，就一定有人在这次 `start` 后被赶回队尾。

``` cpp
// occupied 是一个队列，存储当前在游玩状态的玩家
// q 也是一个队列，存储当前在等待状态的玩家
// status 是一个字符串映射为整数的无序 map，用于存储每个名称的玩家所处的状态
    // 0 表示已离开或未出现，这也是无序 map 中元素的默认值
    // 1 表示等待中
    // 2 表示游玩中
// 下面你会见到的 clean_up() 函数，是用于淘汰掉位于队首但已经离开机厅的玩家

// 函数名是 New York Back Raise!!!
string game_start() {
    // 先把前一局的玩家赶走并放回队尾
    while (occupied.size()) {
        string s = occupied.front();
        occupied.pop();
        status[s] = 1; // 标记为等待中
        q.push(s);
    }
    
    // 这里判断队内是否存在剩余玩家
    q.clean_up(); // 把队首已经标记为离开的玩家弹出队列，该函数的代码将在后面给出
    if (q.empty()) // 如果操作之后队里没有人，说明操作不合法
        return "Error";
    
    // 这里判断队内是否存在第一个玩家
    string player1 = q.front();
    q.pop();
    status[player1] = 2; // 标记为游玩中
    occupied.push(player1); // 把该玩家放进游玩区
    q.clean_up();
    if (q.empty()) // 如果队里就剩下这一个人，则只输出这一个人
        return player1;
    
    // 这里判断队内是否存在第二个玩家
    string player2 = q.front();
    q.pop();
    status[player2] = 2;
    occupied.push(player2);
    return player1 + " " + player2; // 有两个玩家可以玩，所以加一个空格输出
}
```

### arrive 操作

> 1.   $x$ 到达机厅并且将自己加入队尾，
> 2.   此时 $x$ 不应该在排队，否则输出 `Error` 并忽略这条事件。若该事件成功执行则输出 `OK`。

1.   将 $x$ 加入队尾。
2.   题目的补充信息说明了：游玩状态和等待状态都属于在排队。而一个人最多只会有三种状态：离开或未出现、游玩中、等待中。所以这句话实际是在说，$x$ 只能处于「离开或未出现」这一种状态时，操作才合法。

``` cpp
string arrival(string s) {
    if (status[s] != 0) // 如果不满足状态条件，则操作不合法
        return "Error";
    q.push(s); // 排到队尾
    status[s] = 1; // 标记为等待中
    return "OK"; // 操作合法
}
```

### leave 操作

>   1.   $x$ 离开机厅并离开队列。
>   2.   此时 $x$ 应该在排队但不应该在游玩，否则输出 `Error` 并忽略这条事件。若该事件成功执行则输出 `OK`。

1.   将 $x$ 标记为离开状态。（这样做是因为一般队列不支持在内部弹出元素，STL 双端队列的效率又很低。）
2.   当且仅当 $x$ 处于等待状态时，操作合法。

``` cpp
string leaving(string s) {
    if (status[s] != 1) // 如果不满足状态条件，则操作不合法
        return "Error";
    status[s] = 0; // 标记为已离开
    return "OK";
}
```

## 代码

想清楚了上面几点细节，代码其实还是比较好写的。这里我为了减少代码量（?）和增加可读性，选择把 `clean_up()` 函数作为队列的一个内置函数，所以队列用结构体（STL queue 其实也可以，就是 `clean_up()` 写在外面罢了）进行实现。代码如下。

``` cpp
#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

int n;
string s, t;

unordered_map<string, int> status;
// 0 = left
// 1 = queued
// 2 = playing

struct Queue {
    private:
        string name[N]; int head = 0, tail = -1;
    public:
        int size() { return tail - head + 1; }
        string front() { return name[head]; }
        string back() { return name[tail]; }
        bool empty() { return head > tail; }
        void push(string s) { name[++tail] = s; }
        void pop() { head++; }
        void clean_up() {
            // 只要队首已经标记为离开，就直接将其出队
            while (status[front()] == 0 && !empty())
                pop();
        }
} q, occupied;

string game_start() {
    while (occupied.size()) {
        string s = occupied.front(); occupied.pop();
        status[s] = 1; q.push(s);
    }
    q.clean_up();
    if (q.empty()) return "Error";
    string player1 = q.front(); q.pop();
    status[player1] = 2; occupied.push(player1);
    q.clean_up();
    if (q.empty()) return player1;
    string player2 = q.front(); q.pop();
    status[player2] = 2; occupied.push(player2);
    return player1 + " " + player2;
}

string arrival(string s) {
    if (status[s] != 0) return "Error";
    q.push(s);
    status[s] = 1;
    return "OK";
}

string leaving(string s) {
    if (status[s] != 1) return "Error";
    status[s] = 0;
    return "OK";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    while (n--) {
        cin >> s;
        if (s == "start") {
            cout << game_start() << endl;
        } else if (s == "arrive") {
            cin >> t;
            cout << arrival(t) << endl;
        } else if (s == "leave") {
            cin >> t;
            cout << leaving(t) << endl;
        }
    }
    return 0;
}
```

那么恭喜这份代码获得了 $40$ 分。

问题出在哪里呢？有这样一种情况。

假如 $x$ 在排队过程中被 `leave` 了，我们将其标记为「已离开」，但并没有直接将其出队。这就会导致一个问题：如果这个标记为已经离开的队列元素 $x$ 还没有移动到队首、还没有被及时清理掉的时候，同一个 $x$ 就重新回到机厅、排到了队尾，这个时候根据我们的程序，$x$ 的状态会被设为「等待中」，那么现在即使前面这个曾被标记为「已离开」的元素 $x$ 到了队首，也不会被 `clean_up()` 函数给删除掉。

`clean_up()` 检查的是当前队首名字为 $x$ 的元素的状态，而由于 $x$ 的重新进队，这个状态已经被设为了「等待中」。由此想到，**对于同一个名字的人（当然这道题里面也就是同一个人）而言，只有最新一次操作更新之后的位置才能认为是这个人的在队列中的有效位置。**

以上面的 $40$ 分代码为基础，想把这个想法实现的方法很多。这里我就使用了一个新的无序 `map`，名为 `latest`，它存储的是**每一个名字下的这个人**最后一次进队的位置，用一个不断递增的标记 `idx` 来记录。同时，将队列中的元素改成一个 `pair<string, int>` 的字符串—整数对，这个整数值就是用于存储**当前这个元素**进队时的位置。如果在执行队首清理的时候，队首元素的位置值，与队首元素的名字下最新的位置值不符，就说明这个人在中途离队之后重新进了队，因此队首保存的这个位置也就无效了，直接弹出即可。

AC 代码：

``` cpp
#include "bits/stdc++.h"
using namespace std;
using PSI = pair<string, int>;

const int N = 1e5 + 10;

int n, idx;
string s, t;

unordered_map<string, int> status;
// 0 = left
// 1 = queued
// 2 = playing
unordered_map<string, int> latest;

struct Queue {
    PSI name[N]; // 队列元素变成了字符串—整数对
    int head = 0, tail = -1;
    int size() { return tail - head + 1; }
    PSI front() { return name[head]; }
    PSI back() { return name[tail]; }
    bool empty() { return head > tail; }
    void push(string s) { name[++tail] = {s, latest[s]}; }
    void pop() { head++; }
    void clean_up() {
        // 只要「已经离队」和「位置无效」这两个条件其中一个满足，就清理掉
        while ((status[front().first] == 0 ||
                front().second != latest[front().first])
               && !empty())
            pop();
    }
} q, occupied;

string game_start() {
    while (occupied.size()) {
        string s = occupied.front().first; occupied.pop();
        status[s] = 1; q.push(s);
    }
    q.clean_up();
    if (q.empty()) return "Error";
    string player1 = q.front().first; q.pop();
    status[player1] = 2; occupied.push(player1);
    q.clean_up();
    if (q.empty()) return player1;
    string player2 = q.front().first; q.pop();
    status[player2] = 2; occupied.push(player2);
    return player1 + " " + player2;
}

string arrival(string s) {
    if (status[s] != 0) return "Error";
    latest[s] = ++idx; // 记录当前名字的最新位置值
    q.push(s);
    status[s] = 1;
    return "OK";
}

string leaving(string s) {
    if (status[s] != 1) return "Error";
    status[s] = 0;
    return "OK";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    while (n--) {
        cin >> s;
        if (s == "start") {
            cout << game_start() << endl;
        } else if (s == "arrive") {
            cin >> t;
            cout << arrival(t) << endl;
        } else if (s == "leave") {
            cin >> t;
            cout << leaving(t) << endl;
        }
    }
    return 0;
}
```

Upd: \[2023/8/12 21:16\] 更正一处笔误，略微优化了一下表达。


---

## 作者：Crazyouth (赞：3)

**分析**

硬核大模拟。一眼丁真，一个方便随时删数，插入数，查找数的 STL 就是 set。另外针对 set 排序的问题，我们给每个入队的人打上时间戳，然后重载结构体的小于号，就搞定了！模拟的细节详见代码。

P.S. 这题只是码量大而已，有耐心就能 AC。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
struct per
{
	string name;
	int t;
	bool operator<(const per &a)const//重载小于号
	{
		return t<a.t;
	}
};
set<per> st,pl;//st为队列，pl为当前在玩的人
map<string,int> mp,play;//mp为每个人的时间戳（方便在查找的时候知道当前人的时间戳），play[s]为1时s在玩
int nowtime=1;//当前时间
inline void solve()
{
	string opt;
	cin>>opt;
	if(opt=="start")//开始游戏
	{
		play.clear();//赶走当前在玩的人
		while(!pl.empty())//玩的人重新排队
		{
			per p=*(pl.begin());
			p.t=nowtime;
			nowtime++;//时间加
			pl.erase(pl.begin());
			mp[p.name]=p.t;//时间戳
			st.insert(p);//入队
		}
		if(st.empty())//队列为空，无人上场
		{
			cout<<"Error"<<endl;
			return;
		}
		int sz=st.size();//队列长度
		auto now=st.begin();
		cout<<(*now).name<<' ';//上场
		per tp;
		tp.name=(*now).name;
		tp.t=nowtime;
		mp[tp.name]=nowtime;//时间戳
		st.erase(st.begin());//从队列中删去
		pl.insert(tp);//开玩！
		play[tp.name]=1;//在玩
		if(sz>1)//多于一个人在队列
		{
			nowtime++;//其余同上
			now=st.begin();
			cout<<(*now).name<<' ';
			tp.name=(*now).name;
			tp.t=nowtime;
			st.erase(st.begin());
			pl.insert(tp);
			mp[tp.name]=nowtime;
			play[tp.name]=1;
		}
		cout<<endl;
	}
	else if(opt=="arrive")
	{
		string x;
		cin>>x;
		per tp;
		tp.name=x;
		tp.t=nowtime;
		if(mp[x]||play[tp.name])//这人已经在队列或者在玩了
		{
			cout<<"Error"<<endl;
			return;
		}
		cout<<"OK"<<endl;
		mp[tp.name]=nowtime;//时间戳
		st.insert(tp);//入队
	}
	else
	{
		string x;
		cin>>x;
		per tp;
		tp.name=x;
		if(!mp[tp.name]||play[tp.name])//不在队列或在玩
		{
			cout<<"Error"<<endl;
			return;
		}
		cout<<"OK"<<endl;
		tp.t=mp[tp.name];//得到该人的时间戳
		st.erase(tp);//出队
		mp[tp.name]=0;//清零
		play[tp.name]=0;//清零
	}
}
int main()
{
	ios::sync_with_stdio(0);//较快的读入方式
	cin.tie(0);
	cout.tie(0);
	int q;
	cin>>q;
	while(q--)
	{
		solve();
		nowtime++;//时间戳加一
	}
	return 0;
} 

---

## 作者：Fire_flame (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9518)

发现大家的思路和我不太一样捏。

## $\mathtt{Solution}$

考虑队列维护，为避免卡常我先给每一个出现在询问里面的字符串一个编号，默认当前操作字符串编号为 $x$。

----
`leave` 操作是比较难想的，大部分人写了神奇的 STL，~~但是我太菜了不会。~~

定义一个 $leave_i$ 为编号为 $i$ 的字符串出队多少次。同理，为解决 `arrive` 操作，定义 $num_i$ 为编号为 $i$ 的队伍入队多少次。

如果当前队里没有 $x$，即 $leave_x=num_x$，返回 `error`。

如果玩游戏的字符串里有 $x$，也返回 `error`。

否则，可以出队并且 $leave_x=leave_x+1$。

---

有了上面的定义，`arrive` 操作也迎刃而解。

如果当前队里，且玩游戏的字符串里面不包含 $x$，可以入队，$num_x=num_x+1$。

否则返回 `error`。

---

接下来是 `start` 操作。

首先把上一局玩游戏的人加进队列里面，记得 $num$ 要加一。

接下来，每次取出队首 $top$，直到队列为空：

- 如果 $leave_{top}\neq 0$，$leave_{top}=leave_{top}-1,num_{top}=num_{top}-1$，将队首弹出。

- 否则，记录一下第一或者第二个游玩者是 $top$，弹出队首以后结束循环。

上面的操作写两遍即可找出当前游戏的游玩者。

如果没有记录游玩者，返回 `error`。

时间复杂度 $O(n\log n)$，因为我用了 `map` 来给字符串编号。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 5e5 + 5;
int t, cnt, last1, last2, leave[MAXN], num[MAXN];
queue<int>q;
map<string, int>mp;
string s[MAXN];
char opt[MAXN];
int main(){
	t = read();
	while(t --){
		scanf("%s", opt + 1);
		if(opt[1] == 's'){
			if(last1)q.push(last1), num[last1] ++;//先把上一局游玩的人加回去
			if(last2)q.push(last2), num[last2] ++;
			if(q.empty())puts("Error");//发现队列为空
			else{
				int fst = 0, sec = 0;
				while(!q.empty()){
					if(leave[q.front()])leave[q.front()] --, num[q.front()] --, q.pop();
					else{
						fst = q.front();
						num[q.front()] --;
						q.pop();
						break;
					}
				}
				while(!q.empty()){
					if(leave[q.front()])leave[q.front()] --, num[q.front()] --, q.pop();
					else{
						sec = q.front();
						num[q.front()] --;
						q.pop();
						break;
					}
				}
				if(!fst)puts("Error");//一个参赛者都没有记录下来
				else{
					if(fst && !sec)cout << s[fst] << endl;
					else cout << s[fst] << " " << s[sec] << endl;
					last1 = fst, last2 = sec;
				}
			}
		}
		else if(opt[1] == 'a'){
			string tmp;
			cin >> tmp;
			if(!mp[tmp])mp[tmp] = ++ cnt, s[cnt] = tmp;//给每一个字符串编号
			if((num[mp[tmp]] - leave[mp[tmp]]) || last1 == mp[tmp] || last2 == mp[tmp])puts("Error");
			else num[mp[tmp]] ++, q.push(mp[tmp]), puts("OK");
		}
		else{
			string tmp;
			cin >> tmp;
			if(!mp[tmp])mp[tmp] = ++ cnt, s[cnt] = tmp;
			if((num[mp[tmp]] - leave[mp[tmp]]) && last1 != mp[tmp] && last2 != mp[tmp])leave[mp[tmp]] ++, puts("OK");
			else puts("Error");
		}
	}
	return 0;
}

```


---

## 作者：信息向阳花木 (赞：2)

模拟队列题。用一个队列来维护正在排队的人，用两个 `map` 来维护一个人是否在排队和是否在玩游戏。由于数据比较水，遇到离开的人，直接暴力遍历队列，用后面的数覆盖前面的就行。这题唯一的坑点就是遇到 `start` 时，应先让上局的玩家归队，再判断队列是否为空。玩家是可以连续玩游戏的，否则只有 $70$ 分。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 500010;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int n, last_cnt;
string last1, last2;
bool flag = 0;
int head = 1, tail = 0;
string q[N];
map<string, bool> in_que, in_game;

int main()
{
	in(n);
	while (n --)
	{
		string op, name;
		cin >> op;
//		while (!q.empty() && !in_que[q.front()]) q.pop();
		
		if(op[0] == 's')
		{
			if(flag)
			{
				in_game[last1] = 0;
				q[++ tail] = last1;
				in_que[last1] = 1;
				
				if(last_cnt == 2)
				{
					in_game[last2] = 0;
					q[++ tail] = last2;
					in_que[last2] = 1;
				}
			}
			if(tail < head) { puts("Error"); continue; }
			
			flag = 1; last_cnt = 1; last1 = q[head ++ ];
			cout << last1;
			in_game[last1] = 1;
			in_que[last1] = 0;
			
			if(head<= tail)
			{
				last2 = q[head ++ ];
				cout << ' ' << last2;
				in_game[last2] = 1;
				in_que[last2] = 0;
				last_cnt ++;
			}
			puts("");
		}
		else if(op[0] == 'a')
		{
			cin >> name;
			if(in_que[name] || in_game[name]) puts("Error");
			else
			{
				puts("OK");
				q[ ++ tail] = name;
				in_que[name] = 1;
			}
		}
		else if(op[0] == 'l')
		{
			cin >> name;
			if(!in_que[name]) puts("Error"); 
			else
			{
				puts("OK");
				in_que[name] = 0;
				for(int i = head; i <= tail; i ++ )
				{
					if(q[i] == name)
					{
						for (int j = i + 1; j <= tail; j ++ ) q[j - 1] = q[j];
						tail --;
						break;
					}
				}
			}
		}
	}
	return 0;
}
 ```

---

## 作者：jr_linys (赞：2)

唉，我一道黄题整那么久......

[题目链接](https://www.luogu.com.cn/problem/P9518)

## 提示

为方便，本题解使用以下奇怪的东西。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef queue<pair<string,uint>> qu;
typedef unordered_map<string,uint> ma;
#define fi first
#define se second
```

## Main

假如我们有这样的一个数据结构，可以维护一个队列，可以实现以下功能：

| 函数 | 功能 |
| :----------: | :----------: |
| `time(x,s)` | 若 $s$ 在在队列中，返回加入的时间，否则返回 $0$ |
| `get(x)` | 获取队列第一个元素，队列为空时返回空字符串 |
| `add(x,s)` | 在队列末尾加入 $s$ |
| `del(x,s)` | 删除 $s$ |
（以上的 $x$ 表示操作的队列编号）

然后维护两个队列，第一个是游玩队列，第二个是等待队列，那么我们把主函数搓出来就轻轻松松。
```cpp
嘿，这里先不放，这个不难吧。
```

## 操作函数

那么这些函数怎么实现呢？

这个时候就有帅比说了：啊？`set`乱搞不就过了吗？

那如果我们~~太傻没想到~~追求效率，可以使用队列和哈希表假删，达到 $O(n)$ 的时间复杂度（链表加哈希表真删能 $O(n)$）。

假删就是删除时并不是真删，而是打上一个删除的标记，等到一个元素被调用时再判断它还在不在。

对于**此题**，大致作法是：
- **加入**队列的元素记录其被**加入的时间**，将**哈希表中元素对应的时间**同步。
- **删除**时把**哈希表中元素对应的时间**设为 $0$。
- **取出**元素时判断被**加入的时间**与**希表中元素对应的时间**是否相同。

**时间**就是操作的编号。

一种理解方式就是看看你的**状态的版本**是不是**最新**的。

推荐使用`queue`和`unordered_map`实现（这东西把它当无序存储的`map`就行，用法差不多）。

使用`[]`重载运算符的实现。

[记录](https://www.luogu.com.cn/record/120604614)
```cpp
//为方便的奇怪定义
typedef queue<pair<string,uint>> qu;
typedef unordered_map<string,uint> ma;
#define fi first
#define se second
uint t,n;//t为时间
qu q[2];//队列
ma mp[2];//哈希表

uint time(uint x,string &s){
	return mp[x-1][s];
}

string _get(qu &q,ma &mp){
	while(!q.empty()){
		pair<string,uint> x=q.front();
		q.pop();
		if(mp[x.fi]==x.se) return x.fi;
	}
	return "";
}
string get(uint x){return _get(q[x-1],mp[x-1]);}

void add(uint x,string &s){
	q[x-1].push({s,t}),mp[x-1][s]=t;
}

void del(uint x,string &s){
	mp[x-1][s]=0;
}
```
调用函数的实现，并且删除 $s$ 时会把哈希表中元素对应的时间直接删掉而不是设为 $0$，常数更小。

[记录](https://www.luogu.com.cn/record/120587017)
```cpp
uint _time(ma &mp,string &s){
	ma::iterator p=mp.find(s);
	if(p==mp.end()) return 0;
	return (*p).se;
}
uint time(uint x,string &s){return _time(mp[x-1],s);}

string _get(qu &q,ma &mp){
	while(!q.empty()){
		pair<string,uint> x=q.front();
		q.pop();
		if(_time(mp,x.fi)==x.se) return x.fi;
	}
	return "";
}
string get(uint x){return _get(q[x-1],mp[x-1]);}

void _add(qu &q,ma &mp,string &s){
	q.push({s,t});
	ma::iterator p=mp.find(s);
	if(p==mp.end()) mp.insert({s,t});
	else (*p).se=t;
}
void add(uint x,string &s){_add(q[x-1],mp[x-1],s);}

void _del(ma &mp,string &s){
	ma::iterator p=mp.find(s);
	mp.erase(p);
}
void del(uint x,string &s){_del(mp[x-1],s);}
```

主函数
```cpp
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(t=1;t<=n;++t){
		string opt,name;cin>>opt;
		if(opt=="start"){
			while(1){
				name=get(1);
				if(name!="") del(1,name),add(2,name);
				else break;
			}
			name=get(2);
			if(name=="") cout<<"Error\n";
			else{
				cout<<name;
				add(1,name),del(2,name),name=get(2);
				if(name!="") cout<<' '<<name,add(1,name),del(2,name);
				cout<<"\n";
			}
		}else{
			cin>>name;
			if(opt=="arrive"){
				if(!time(1,name)&&!time(2,name)) add(2,name),cout<<"OK\n";
				else cout<<"Error\n";
			}else{
				if(!time(1,name)&&time(2,name)) del(2,name),cout<<"OK\n";
				else cout<<"Error\n";
			}
		}
	}
}
```
不放完整代码啦，要的话就把它们拼起来吧。

额，维护两个队列确实比较冗余，但是比较直观。

点个赞再走呗。

---

## 作者：qinsishi (赞：2)

本题是一个大模拟，只是**细节**有点多。

题目意思很明确，只需要维护一个队列，将队列里面的元素**添加、删除、移动位置**。

需要维护的数据有如下：

- `queue<pair<string, int> > que` 维护排队顺序，但和题意不同的是，此时的 que 不包括正在玩游戏的人。维护的 first 为人名，second 为有效编号，这个在下面也会提到。

- `set<string> peo` 表示队列里的人。

- `map<string, int> cnt` 表示人 first 他已经进队多少次，有效编号为 second，因为是懒标记，可能一个人同时在队列里出现多次。

- `string play1, play2` 表示正在玩的两个人，"-" 代表无人。

- `int p1, p2` 表示正在玩的两个人的编号。

那么接下来我们实现 `start()` 函数，首先更新正在玩游戏的两个人，将他们都插入队列中，接下来分类讨论：

- 队列长度为 $0$，那么是错误的。

- 队列长度为 $1$，那么只有一个人在玩游戏。

- 队列长度大于等于 $2$，那么拿出队头的人。

```cpp
bool start() { // 开始游戏 1 成功 0 错误
	if (play1 != "-") {
		que.push({play1, p1});
		play1 = "-";
	}
	if (play2 != "-") {
		que.push({play2, p2});
		play2 = "-";
	}
	if (que.size() == 0) {
		return 0;
	} else if (que.size() == 1) {
		updata(); // 这个函数很重要，我们接下来再说
		play1 = que.front().first;
		p1 = que.front().second;
		que.pop();
		cout << play1 << endl;
	} else {
		updata();
		play1 = que.front().first;
		p1 = que.front().second;
		que.pop();
		updata();
		play2 = que.front().first;
		p2 = que.front().second;
		que.pop();
		cout << play1 << " " << play2 << endl;
	}
	return 1;
}
```

达到 `arrive()` 函数非常简单，我们只需要将进来的人判断是否可行，就插入进队列里，并且标记此人已经存在，**更新此人的入队次数**。

```cpp
bool arrive(string x) { // 到达
	if (peo.count(x) == 1) return 0;
	peo.insert(x);
	que.push({x, ++cnt[x]});
	return 1;
}
```

离开 `leave()` 函数，只需要判断当前的人存在，且不等于正在玩游戏的两个人，那么就可以将这个人**懒标记**。注意是不是直接删，这样更方便。

```cpp
bool leave(string x) { // 离开
	if (play1 == x || play2 == x || peo.count(x) == 0) {
		return 0;
	}
	peo.erase(x); // 懒惰标记
	return 1;
}
```

接下来实现 `updata()` 函数，就是将队头应该已经离队的人删掉，**并在每次开始游戏时调用它**。

```cpp
void updata() { // 将队头已经出去的删掉
	while (que.size() && (peo.count(que.front().first) == 0 || cnt[que.front().first] != que.front().second)) {
		que.pop();
	}
}
```

接下来是完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
string play1 = "-"; int p1 = 0; // 正在玩的人1
string play2 = "-"; int p2 = 0; // 同上
queue<pair<string, int> > que; // 排队队列
set<string> peo; // 队列里面有什么人（包括正在玩）
map<string , int> cnt; // 非常重要，有效编号节点

void updata() { // 将队头已经出去的删掉
	while (que.size() && (peo.count(que.front().first) == 0 || cnt[que.front().first] != que.front().second)) {
		que.pop();
	}
}

bool start() { // 开始游戏 1 成功 0 错误
	if (play1 != "-") {
		que.push({play1, p1});
		play1 = "-";
	}
	if (play2 != "-") {
		que.push({play2, p2});
		play2 = "-";
	}
	if (que.size() == 0) {
		return 0;
	} else if (que.size() == 1) {
		updata();
		play1 = que.front().first;
		p1 = que.front().second;
		que.pop();
		cout << play1 << endl;
	} else {
		updata();
		play1 = que.front().first;
		p1 = que.front().second;
		que.pop();
		updata();
		play2 = que.front().first;
		p2 = que.front().second;
		que.pop();
		cout << play1 << " " << play2 << endl;
	}
	return 1;
}

bool arrive(string x) { // 到达
	if (peo.count(x) == 1) return 0;
	peo.insert(x);
	que.push({x, ++cnt[x]});
	return 1;
}

bool leave(string x) { // 离开
	if (play1 == x || play2 == x || peo.count(x) == 0) {
		return 0;
	}
	peo.erase(x); // 懒惰标记
	return 1;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	while (n--) {
		string op;
		cin >> op;
		if (op[0] == 's') {
			if (!start()) {
				cout << "Error" << endl;
			}
		} else if (op[0] == 'a') {
			string x;
			cin >> x;
			if (arrive(x)) {
				cout << "OK" << endl;
			} else {
				cout << "Error" << endl;
			}
		} else if (op[0] == 'l') {
			string x;
			cin >> x;
			if (leave(x)) {
				cout << "OK" << endl;
			} else {
				cout << "Error" << endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：1)

注：本篇题解赛时 90 分 TLE，赛后玄学地竟然[过了](https://www.luogu.com.cn/record/120562171)，因此本代码只为一种思路，不保证抄题解后提交能够 AC。

这里提供一种用 STL 中的 `list` 的写法。`list` 是 STL 中的一种容器，通常用于实现**双向链表**等结构的操作，一般来说，它支持以下功能：

1. 首尾插入元素；

2. 删除元素；

3. 查看元素；

由此我们可以来实现本题的功能。

- 对于操作 `start`，我们记录两个东西，一个是判断这是否是第一局游戏的，另一个是记录上一局游戏有几个人参加，随后我们根据记录的两个东西用 `list` 进行判断即可；

- 对于操作 `arrive` ，即然要随时判断链表中是否存在该元素，我们可以联想到集合 `set`，于是我们只需要在维护 `list` 的同时额外维护一个 `set`，每次判断 `s.count(x)` 即可；

- 对于操作 `leave`，我们只需判断 $x$ 是否同时满足在 `list` 里、在队列长度大于等于三时不在第一个或第二个即可。

于是这道模拟题就可以愉快地解决了。需要注意的一点是本题需要快速的读入方式，这里我用的 `getline`，它支持读入一整行字符串，随后再利用 STL 中的 `substr` 和 `replace` 操作实现将两个字符串分离。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
list<string> l;	//list
set<string> a;
int person;	//表示上一次游戏有几个人（1 or 2）
string t;
int main(){
	cin>>n;
	cin.ignore();
	for(int i=1;i<=n;i++){
		string s,t;
		getline(cin,s);	//分离操作
		if(s.find(" ")!=string::npos){
			t=s.substr(s.find(" ")+1,s.size()-s.find(" "));
			s.replace(s.find(" "),s.size()-s.find(" "),"");
		}
		if(s=="start"){
			if(l.size()==0){
				printf("Error\n");
				continue;
			}
			if(person){
				if(person==1){	//分类讨论，移到表尾操作
					string tmp=l.front();
					l.pop_front();
					l.push_back(tmp);
				}else if(person==2){
					string tmp=l.front();
					l.pop_front();
					l.push_back(tmp);
					tmp=l.front();
					l.pop_front();
					l.push_back(tmp);
				}
			}
			if(l.size()>=2){	//分类讨论输出
				list<string>::iterator it=l.begin();
				cout<<(*it)<<' ';
				it++;
				cout<<(*it)<<'\n';
				person=2;
			}else if(l.size()==1){
				cout<<l.front()<<'\n';
				person=1;
			}
		}else if(s=="arrive"){
			if(a.count(t)){	//判断是否处于 set 中
				printf("Error\n");
			}else{
				a.insert(t);
				l.push_back(t);
				printf("OK\n");
			}
		}else if(s=="leave"){
			list<string>::iterator it=l.begin();
			it++;
			if(a.count(t)&&t!=l.front()&&t!=(*it)){	//判断是否满足 leave 的条件
				list<string>::iterator pos=find(l.begin(),l.end(),t);
				l.erase(pos);
				a.erase(t);
				printf("OK\n");
			}else{
				printf("Error\n");
			}
		}
		//cout<<s<<' '<<t<<'\n';
	}
	return 0;
}
```


---

## 作者：fish_love_cat (赞：1)

第一次在月赛时看到大模拟，新鲜。

---

**需要的东西：**

用一个 `queue` 模拟队列，再用一个 `map` 做桶，记录每个人的状态（是否排队？是否游玩？）。然后再开两台机子（`string`），记录正在游玩的人的名字。

有了这些记录用的东西，接着就可以开始模拟了。

```cpp
string aj="",bj="";//机子
struct qq{//状态
    bool pd,yw;
};
int n;
queue<string> q;//队列
map<string,qq> mapp;//桶
map<string,int> shabiTLEsima;//后文会提到的优化计数器
```

---

`arrive` **部分：**

先读入字符串 $x$，即待会要加入进来的人。然后再扫一遍这个人的状态，如果在排队或者在游玩，那么输出 `Error` 并忽视。如果都不在，那就把这个人的排队属性打上勾（设为真），并加入队列。

这样人员的插入（也是最简单的部分）就搞定了。

```cpp
            if(s=="arrive"){
                if(mapp[x].pd||mapp[x].yw) puts("Error");//属性
                else{
                    mapp[x].pd=true,q.push(x);
                    puts("OK");//操作
                }
            }
```

---

`leave` **部分：**

照例先读那个要离开的人的人名。扫一遍状态，如果在玩或者不在排队里（即不在舞厅），那么输出 `Error` 并忽视，否则就要把这个人给踢出队伍。但是如果把队列颠倒一遍稳稳地超时，所以需要有一些优化，而这个优化我把他放到 `start` 里了。虽然单论这部分代码不比上面的加入难，但这个优化理应也算一部分（虽然在码不在此），所以我把他排到了第二难的位置。

这样离开的做法也搞定了。

```cpp
            if(s=="leave"){
                if(!mapp[x].pd||mapp[x].yw) puts("Error");//属性
                else{
                    mapp[x].pd=false,puts("OK");//操作
                    shabiTLEsima[x]++;//优化
                }
            }
```

---

`start` **部分：**

最难的来了。

首先执行把正在游玩的人放结尾的操作。我们把有人的机子上面的人修改状态，然后置空机子，把人压入队列即可。

接着进行一个化的优。我们用先前搞的优化 `map` 记录下一个人离开了几次，由于并没踢出队列，所以当我们发现队首这个人他先前离开过，这个只是一个残影，直接打飞即可。同时计数器记得减一。可以证明这比删除一次就扫一遍序列更优。

**小贴士：在两个人要上跳舞机时，上第一个人时要判断队首，上第二个人时也要判断一次队首！**

然后，再判断一下队列是否为空，为空输出 `Error`，否则就输出上跳舞机的几位。把这几位状态一改，跳舞机相关信息一改，队列弹出即可。

```cpp
        if(s=="start"){
            if(aj!="") mapp[aj].pd=true,mapp[aj].yw=false,q.push(aj),aj="";
            if(bj!="") mapp[bj].pd=true,mapp[bj].yw=false,q.push(bj),bj="";//跳舞机数据
            while(!q.empty()&&shabiTLEsima[q.front()]>0) shabiTLEsima[q.front()]--,q.pop();//优化
            if(q.empty()) puts("Error");//Error
            else{
                if(q.size()==1){
                    cout<<q.front()<<'\n',mapp[q.front()].pd=false,mapp[q.front()].yw=true,aj=q.front(),q.pop();//修改
                }else{
                    cout<<q.front()<<' ',mapp[q.front()].pd=false,mapp[q.front()].yw=true,aj=q.front(),q.pop();//修改
                    while(!q.empty()&&shabiTLEsima[q.front()]>0) shabiTLEsima[q.front()]--,q.pop();//二次优化
                    cout<<q.front()<<'\n',mapp[q.front()].pd=false,mapp[q.front()].yw=true,bj=q.front(),q.pop();//二次修改
                }
            }
        }
```

---

**总代码：**

赛时代码马蜂极丑，见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
//分代码里有注释，总的就不写了（
string aj="",bj="";
struct qq{
    bool pd,yw;
};
int n;
queue<string> q;
map<string,qq> mapp;
map<string,int> shabiTLEsima;
int main(){
    scanf("%d",&n);
    while(n--){
        string s;
        cin>>s;
        if(s=="start"){
            if(aj!="") mapp[aj].pd=true,mapp[aj].yw=false,q.push(aj),aj="";
            if(bj!="") mapp[bj].pd=true,mapp[bj].yw=false,q.push(bj),bj="";
            while(!q.empty()&&shabiTLEsima[q.front()]>0) shabiTLEsima[q.front()]--,q.pop();
            if(q.empty()) puts("Error");
            else{
                if(q.size()==1){
                    cout<<q.front()<<'\n',mapp[q.front()].pd=false,mapp[q.front()].yw=true,aj=q.front(),q.pop();
                }else{
                    cout<<q.front()<<' ',mapp[q.front()].pd=false,mapp[q.front()].yw=true,aj=q.front(),q.pop();
                    while(!q.empty()&&shabiTLEsima[q.front()]>0) shabiTLEsima[q.front()]--,q.pop();
                    cout<<q.front()<<'\n',mapp[q.front()].pd=false,mapp[q.front()].yw=true,bj=q.front(),q.pop();
                }
            }
        }else{
            string x;
            cin>>x;
            if(s=="arrive"){
                if(mapp[x].pd||mapp[x].yw) puts("Error");
                else{
                    mapp[x].pd=true,q.push(x);
                    puts("OK");
                }
            }else if(s=="leave"){
                if(!mapp[x].pd||mapp[x].yw) puts("Error");
                else{
                    mapp[x].pd=false,puts("OK");
                    shabiTLEsima[x]++;
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

大模拟啊，没什么好说的，按题意模拟即可。

这里说个坑点：

如果单纯记录一个人在不在队列里是错误的。如果他退队后进队，应该排在队尾，但是如果只是打个标记则不会判断到这一点。

给个 hack 数据：

```
6
arrive a
arrive b
arrive c
leave a
arrive a
start

out:
OK
OK
OK
OK
OK
b c
```
如果输出 ```a b``` 则很有可能是上述问题。

解决方案很简单，同时记录这个人最新一次是什么时候进的队，然后给队列加个时间维度。

给代码，写得很丑，仅仅用来拍吧。

```cpp
#include <bits/stdc++.h>
#define int long long
#define db double
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
const int N=1e5+10,INF=1e14;

int T;
string op,nm,ls="",rs="";//正在游戏的第1/2个人，如果没有为空
map<string,bool>mp;
map<string,int>lst;
struct Node{
	int t;
	string s;
};//记录时间维度
queue<Node>q;

inline void stt(int tm){
	if(ls!=""){
		q.push({tm,ls});
		mp[ls]=1;
		lst[ls]=tm;
	}//玩家一归队
	if(rs!=""){
		q.push({tm,rs});
		mp[rs]=1;
		lst[rs]=tm;
	}//玩家二归队
	ls=rs="";//清空
	while(1){
		if(q.empty())break;
		if(mp[q.front().s]&&q.front().t==lst[q.front().s])break;
		q.pop();
	}//把队列中的兀余元素弹出，也就是不处于真正的队列里的元素
	if(q.empty()){
		cout<<"Error\n";
		return;
	}//清除后没人了就不能开始
	ls=q.front().s;//记录第一个玩家
	q.pop();
	cout<<ls;
	mp[ls]=0;//可以视作出队，带一个地方待机
	while(1){
		if(q.empty())break;
		if(mp[q.front().s]&&q.front().t==lst[q.front().s])break;
		q.pop();
	}
	if(!q.empty()){
		rs=q.front().s;
		q.pop();
	}
	if(rs!=""){
		cout<<' '<<rs;
		mp[rs]=0;
	}//第二个玩家同理
	cout<<'\n';
	return;
}

inline void arr(string s,int id){
	if(mp[s])cout<<"Error\n";
	else if(ls!=""&&s==ls)cout<<"Error\n";
	else if(rs!=""&&s==rs)cout<<"Error\n";//如果已经在队里或者在游戏
	else{
		mp[s]=1;
		lst[s]=id;
		q.push({id,s});//更新
		cout<<"OK\n";
	}
	return;
}

inline void lev(string s){
	if(!mp[s])cout<<"Error\n";
	else if(ls!=""&&ls==s)cout<<"Error\n";
	else if(rs!=""&&rs==s)cout<<"Error\n";
	else{
		mp[s]=0;
		cout<<"OK\n";
	}
	return;
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	for(int i=1;i<=T;i++){
		cin>>op;
		if(op[0]=='s')stt(i);
		else if(op[0]=='a'){
			cin>>nm;
			arr(nm,i);
		}else if(op[0]=='l'){
			cin>>nm;
			lev(nm);
		}
	}
	return 0;
}
```

---

## 作者：joyslog (赞：1)

给一种比较短小且清真的写法。

对于人名，我们不妨通过 `unordered_map<string, int>` 将其处理为编号。接下来，结合本题的“排队”背景，我们就可以直接使用 `queue<int>` 来进行模拟了。

对于正在游戏的人，我们用两个变量 `t1` 和 `t2` 把它们的编号直接存起来。

1. `start` 操作：把 `t1` 和 `t2` 塞到队尾，再把队首的前两个元素拿出来，赋给 `t1` 和 `t2`，最后输出。如果一个也拿不出来，则操作不合法。

2. `arrive` 操作：用 `unordered_map` 判一下是否已经在队列中，不在就塞到队尾，否则操作不合法。

3. `leave` 操作：用 `unorder_map` 找到这个人的编号（如果找不到，则操作不合法），把这个编号记为无效。然后考虑这会对 `start` 操作产生影响，所以我们在 `start` 操作中拿队首元素时把无效编号忽略即可。

这样写理论上时间复杂度接近线性。但是由于 `cin`、`unordered_map`、`string` 的大常数，实际时间没那么优秀。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 1e5 + 10;
string s, t, names[MAX_N];
int n, t1, t2, cnt;
queue<int> q;
unordered_map<string, int> mp;

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> s;
		if(s == "start") {
			if(t1 > 0)	q.push(t1), t1 = 0;
			if(t2 > 0)	q.push(t2), t2 = 0;
			while(!q.empty() && names[q.front()] == "-")	q.pop(); 
			if(!q.empty())	t1 = q.front(), q.pop();
			while(!q.empty() && names[q.front()] == "-")	q.pop();
			if(!q.empty())	t2 = q.front(), q.pop();
			if(t1 && !t2)	cout << names[t1] << endl;
			else if(t1 && t2)	cout << names[t1] << " " << names[t2] << endl;
			else	cout << "Error" << endl;
		}
		else if(s == "arrive") {
			cin >> t;
			if(mp[t] > 0)	cout << "Error" << endl;
			else {
				names[++cnt] = t;
				q.push(cnt);
				mp[t] = cnt;
				cout << "OK" << endl;
			}
		}	
		else {
			cin >> t;
			int res = mp[t];
			if(res > 0 && res != t1 && res != t2) {
				names[res] = "-";
				mp[t] = 0;
				cout << "OK" << endl;
			}
			else	cout << "Error" << endl;
		}
	}
	return 0;
}
```




---

## 作者：Binary_Lee (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/P9518)

### 解决思路

其实用链表也可以维护这样一个队列（当时感觉删人会方便点所以写了链表）。

一个比较常用的技巧是使用 `stl::map`，可以方便地将字符串作为下标，写起来会简单很多。

然后看懂题意模拟即可，代码里有非常详细的注释。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int n;
string op,s;
string tail="0";   //队尾 
map<string,bool> pl,pd;   //分别代表一个人是否正在玩，是否正在排队 
map<string,string> fro,nxt;   //分别代表链表的前驱与后继 
vector<string> lst;   //存放上一次玩的人 

void add(string s){   //在链表的最末尾加上一个人 
	pd[s]=1;   //将此人设为正在排队 
	nxt[tail]=s,fro[s]=tail,tail=s;   //处理前驱后继，并将队尾设为当前人 
}

void del(string s){   //删人 
	pd[s]=0;   //将此人设为不在排队
	if(s==tail) tail=fro[s];   //如果此人是队尾，直接用改队尾的方法删 
	else{   //否则就是常规的链表删点 
		nxt[fro[s]]=nxt[s];   
		fro[nxt[s]]=fro[s];
	}
}

signed main(){
	IOS;TIE;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>op;
		if(op[0]=='a'){    //加人操作 
			cin>>s;
			if(pd[s]) cout<<"Error"<<'\n';    //如果此人已在队中，Error 
			else add(s),cout<<"OK"<<'\n';
		}
		else if(op[0]=='l'){    //删人操作 
			cin>>s;
			if(!pd[s]||pl[s]) cout<<"Error"<<'\n';    //如果此人不在队中或正在玩，Error 
			else del(s),cout<<"OK"<<'\n';
		}
		else if(op[0]=='s'){   //游玩操作 
			if(lst.size()){
				for(auto i:lst){    //把上一次玩的删掉，并且加入队尾 
					pl[i]=0;
					del(i),add(i);
				}
				lst.clear();
			}
			string _1=" ",_2=" ";   
			if(tail!="0"){    //尝试取第一个人 
				_1=nxt["0"];
				if(tail!=_1) _2=nxt[_1];   //尝试取第二个人 
			}
			if(_1==" ") cout<<"Error"<<'\n';    //没人 
			else if(_2==" ") cout<<_1<<'\n',lst.pb(_1),pl[_1]=1;   //有一个人 
			else cout<<_1<<' '<<_2<<'\n',lst.pb(_1),lst.pb(_2),pl[_1]=pl[_2]=1;   //有两个人
		}
	}
	return 0;
}


```



---

## 作者：AndyPomeloMars (赞：1)

## P9518 queue

### 题目大意

* 给定一个整数 $n$，进行 $n$ 种操作，分别为 `start`、`arrive` 和 `leave`，请你在对应的操作输出对应的结果。

* 对于 $100\%$ 的数据，保证 $1 \le n\le 10^5$，人名仅含有大小写字母且长度不超过 $10$。

### 题目分析

我们可以使用 `deque` 来模拟这个排队队列，用 `map` 来记录每个人的状态（$0$ 表示不在队中，$1$ 表示在排队，$2$ 表示在玩游戏）。

#### 第一类操作：start

先将轮数加一，然后判断队列是否为空，如果为空则输出 `Error`；接下来将上一轮玩过的人从队首移到队尾，并输出这一轮要玩的人的名字（使用变量 `P` 来记录当前游玩的人数）。

```cpp
if (expr == "start"){
    ++T;
    if (Q.empty()){
        cout << "Error" << endl;
        continue;
    }
    for (int i = 1; i <= P; ++i) Qm[Q[0]] = 1, Q.push_back(Q[0]), Q.pop_front();
    P = 0, cout << Q[0] << ' ', Qm[Q[0]] = 2, ++P;
    if (Q.size() > 1)  cout << Q[1] << ' ', Qm[Q[1]] = 2, ++P;
    cout << endl;
}
```

#### 第二类操作：arrive

判断名字是否已经在队列中或在玩游戏，如果是则输出 `Error`；否则输出 `OK` 并将它放入队尾，将人物状态标记成 $1$（正在排队）。

```cpp
else if (expr == "arrive"){
    cin >> name;
    if (Qm[name]) cout << "Error" << endl;
    else cout << "OK" << endl, Q.push_back(name), Qm[name] = 1;
}
```

#### 第三类操作：leave

判断名字是否不在队列中或在玩游戏，如果是则输出 `Error`；否则输出 `OK` 并将遍历 `deque` 并使用 `erase` 函数删除它，将人物状态标记成 $0$（不在队中）。

```cpp
else if (expr == "leave"){
    cin >> name;
    if (!Qm[name] || Qm[name] == 2) cout << "Error" << endl;
    else{
        cout << "OK" << endl, Qm[name] = 0;
        for (auto it = Q.begin(); it != Q.end(); ++it){
            if (*it == name){
                Q.erase(it);
                break;
            }
        }
    }
}
```

### 题目代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int N, T, P, cnt;
deque<string> Q;
map<string, int> Qm;

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> N;
    while (N--){
        ++cnt;
        string expr, name;
        cin >> expr;
        if (expr == "start"){
            ++T;
            if (Q.empty()){
                cout << "Error" << endl;
                continue;
            }
            for (int i = 1; i <= P; ++i) Qm[Q[0]] = 1, Q.push_back(Q[0]), Q.pop_front();
            P = 0, cout << Q[0] << ' ', Qm[Q[0]] = 2, ++P;
            if (Q.size() > 1)  cout << Q[1] << ' ', Qm[Q[1]] = 2, ++P;
            cout << endl;
        }
        else if (expr == "arrive"){
            cin >> name;
            if (Qm[name]) cout << "Error" << endl;
            else cout << "OK" << endl, Q.push_back(name), Qm[name] = 1;
        }
        else if (expr == "leave"){
            cin >> name;
            if (!Qm[name] || Qm[name] == 2) cout << "Error" << endl;
            else{
                cout << "OK" << endl, Qm[name] = 0;
                for (auto it = Q.begin(); it != Q.end(); ++it){
                    if (*it == name){
                        Q.erase(it);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
```


---

## 作者：渡鸦2007 (赞：1)

本题是惯常所说的“大模拟”，要点有如下几个：
1. 将字符串转为数字：我们使用 `map<string,int>` 可以方便地实现。
2. 维护队列：只需使用 `queue<int>`，无需手写。
3. 对是否在队伍内的维护（用于处理离队操作）：一个 `bool` 数组即可。
4. 对离队入队的处理（重点）。我们无需，也不应该在每次离开操作时遍历队列，而应该记录离开次数 $outcnt_i$，在处理开始游戏操作时，检查当前编号为 $i$ 的人对应的 $outcnt_i$ 是否为 $0$，如不是，则该人已离队。——这是因为我们在离队时没有弹出此前进队时的信息，所以有 $outcnt_i$ 个信息是无效的。

以下给出代码，时间复杂度近似 $O(m)$。
```cpp
map<string,int>m;char op[30];
int cnt=0;
queue<int>q;bool in[100100];string mir[100100];
//mir是编号到字符串的映射
queue<int>tmp;bool in_t[100100];//上一轮游戏者的临时存储
int outcnt[100100];
string nme;
int main()
{
	int n;n=read();
	while (n--)
	{
		scanf("\n%s",op+1);//operation,操作种类
		if (op[1]=='s')
		{
			int out=0;//out表示本轮合法出队人数
			while (tmp.size())//tmp是上一轮游戏的人，将其依次置于队尾
			{
				int t;t=tmp.front();tmp.pop();q.push(t);in[t]=1;in_t[t]=0;
			}
			while (q.size())//本轮出队操作
			{
				int p=q.front();q.pop();
				
				if (outcnt[p])//如此前讲述，该人已离队
				{
					--outcnt[p];
				}
				else if (!in[p]) ;
				else//该人合法
				{
					cout<<mir[p]<<" ";++out;in[p]=0;
					tmp.push(p);in_t[p]=1;
					if (out==2) break;//已有两人
				}
			}
			if (out) puts("");
			else puts("Error");
		} 
		else if (op[1]=='a')
		{
			cin>>nme;
			if (m.find(nme)==m.end())//即此前未出现此名字
			{
				m[nme]=++cnt;//给予编号
				mir[cnt]=nme;//记录映射
			}
			int id=m[nme];
			if (in[id] || in_t[id]) puts("Error");//在排队，或在游戏
			else 
			{
				in[id]=1;q.push(id);puts("OK");
			}
		}
		else if (op[1]=='l')
		{
			cin>>nme;
			if (m.find(nme)==m.end())
			{
				m[nme]=++cnt;
				mir[cnt]=nme;
			}
			int id=m[nme];
			if (!in[id]) puts("Error");//不在排队
			else 
			{
				in[id]=0;puts("OK");++outcnt[id];
			}
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```


---

## 作者：Peter2020 (赞：0)

## 题目简介
这道题，是一道队列模拟题。

题面已经告诉我们，要用一个队列模拟排队的状态。

再看题目中需要很多的查询操作，而队列的查询操作需要 $\mathcal{O(n)}$ 的时间复杂度。

为了优化时间复杂度，我们可以使用一个 `set` 来记录当前队列中的元素，这样我们可以在 $\mathcal{O(\log n)}$ 的时间内判断一个元素是否在队列中。

这里队列使用的是双向队列 `deque`，因为 `queue` 不具备迭代器的功能，使用 `queue` 可以帮助我们更好地实现 `leave` 的代码。

看前面的大佬已经提供了很多的方案，我这里就写一个只用一个 `set` 的代码。

## start
在处理 $\texttt{start}$ 时，我们可以将游玩的人暂时地放在一个数组中，待下次开始游玩时再将数组中的内容加入队列。

我们可以每次判断一下队列中元素的数量：
- 若队列为空，就输出 $\texttt{Error}$；
- 若队列有一个元素，就将它存进游玩的数组中；
- 若队列有两个以上的元素，就将队列的前两个元素加入数组。
##### 具体的看代码：
```cpp
if(s=="start"){//start 
		for(int i=0;i<flag;i++){//将游玩的人重新加入队列 
			q.push_back(p[i]);
			inq.insert(p[i]);
		}
		if(q.empty()){//队列为空 
			cout<<"Error"<<endl;
			flag = 0;
		}else{
			if(q.size() >= 2){//队列人数>=2 
				string p1=q.front();
				q.pop_front();
				string p2=q.front();//pop出两个元素 
				q.pop_front();
				cout<<p1<<" "<<p2<<endl;
				inq.erase(p1);
				inq.erase(p2);//set中抹去游玩的人 
				flag = 2;
				p[0]=p1,p[1]=p2;//加入暂时的数组 
			}else{//队列人数为1，与>=2的操作差不多 
				string p1=q.front();
				cout<<p1<<endl;
				inq.erase(p1);
				q.pop_front();
				flag = 1;//游玩人数，用于遍历暂时的数组 
				p[0] = p1;
			}
		}
}
```
## arrive
这里首先我们需要判断一下这个人是否在队列中，或是正在游玩，如果不是就加入队列。思路已经很清晰了，那就看代码吧：
```cpp
else if(s=="arrive"){//arrive 
		string name;
		cin >> name;
		if(inq.count(name)||judge(name)){//不在set中且不在游玩数组中 
			cout<<"Error"<<endl;
		}else{
			q.push_back(name);
			inq.insert(name);
			cout<<"OK"<<endl;
		}
}
```
## leave
$\texttt{leave}$ 就是删除队列中的某一元素，遍历队列即可。
```cpp
else if(s=="leave"){//leave
		string name;
		cin >> name;
		if(!inq.count(name)){//不在集合中 
			cout<<"Error"<<endl;
		}else{
			for(auto it=q.begin();it<q.end();it++){//遍历队列 
				if(*it==name){//找到并删除元素 
					q.erase(it);
					break;
				}
			}
			inq.erase(name);
			//set一定要同步队列，否则会出错！！！ 
			cout<<"OK"<<endl;
		}
}
```
## 完整代码
```cpp
#include <iostream>
#include <string>
#include <queue>
#include <set>
using namespace std;
int n, flag=0;//flag记录游玩的人数 
deque<string> q;//deque:双向队列
//queue不具备遍历功能，用deque更加方便 
set<string> inq;//记录一个人是否在队列中 
string p[2];//暂时存储游玩的人 
bool judge(string s){//判断一个人是否在游玩 
		for(int i=0;i<flag;i++){
			if(p[i]==s) return 1;
		}
		return 0;
}
int main(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
		cin >> n;
		while(n--){
			string s;
			cin >> s;
			if(s=="start"){//start 
				for(int i=0;i<flag;i++){//将游玩的人重新加入队列 
					q.push_back(p[i]);
					inq.insert(p[i]);
				}
				if(q.empty()){//队列为空 
					cout<<"Error"<<endl;
					flag = 0;
				}else{
					if(q.size() >= 2){//队列人数>=2 
						string p1=q.front();
						q.pop_front();
						string p2=q.front();//pop出两个元素 
						q.pop_front();
						cout<<p1<<" "<<p2<<endl;
						inq.erase(p1);
						inq.erase(p2);//set中抹去游玩的人 
						flag = 2;
						p[0]=p1,p[1]=p2;//加入暂时的数组 
					}else{//队列人数为1，与>=2的操作差不多 
						string p1=q.front();
						cout<<p1<<endl;
						inq.erase(p1);
						q.pop_front();
						flag = 1;//游玩人数，用于遍历暂时的数组 
						p[0] = p1;
					}
				}
			}else if(s=="arrive"){//arrive 
				string name;
				cin >> name;
				if(inq.count(name)||judge(name)){//不在set中且不在游玩数组中 
					cout<<"Error"<<endl;
				}else{
					q.push_back(name);
					inq.insert(name);
					cout<<"OK"<<endl;
				}
			}else if(s=="leave"){//leave
				string name;
				cin >> name;
				if(!inq.count(name)){//不在集合中 
					cout<<"Error"<<endl;
				}else{
					for(auto it=q.begin();it<q.end();it++){//遍历队列 
						if(*it==name){//找到并删除元素 
							q.erase(it);
							break;
						}
					}
					inq.erase(name);
					//set一定要同步队列，否则会出错！！！ 
					cout<<"OK"<<endl;
				}
			}
		}
		return 0;
}
```
**模拟题细节很多，需要慢慢调试，小心谨慎。**

---

## 作者：赛克尔だよ (赞：0)

这是一道模拟题，我们很容易看出。

大部分人都维护的是队列，这里我使用了一个链表进行维护。

就像这样：

```cpp
struct node{
	string name;//人名
	int Next,Before,isok,isplay;
	//Next是Ta后面那个人的编号，Before是Ta前面那个人的编号，isok是Ta是否在队列中，isplay是Ta是否在玩
}a[1000005];
```

当我们进行 arrive 操作时，我们会遇到一个问题：怎么查询这个人是否在队列中。

一开始我想到了 Trie 树，理论上可行，但是有点儿大材小用。后来又想到了 map。

所以我们定义一个 map，每个名字映射到它在这个 struct 数组中的编号即可，当然没有这个名字就是 0。

接下来就可以上代码了。

```
#include<bits/stdc++.h>
using namespace std;
map<string,int>q;
string name,s;
struct node{
	string name;
	int Next,Before,isok,isplay;
}a[1000005];
int n,head,ed,k,sp,gamer;
void start(){
	if(sp==0){
		cout<<"Error"<<endl;
		return;
	}
	else{
		if(sp>1){
			if(gamer==0);
			else{
			if(gamer>1){
				a[ed].Next=head;
				a[head].Before=ed;
				a[a[head].Next].isplay=a[head].isplay=0;
				ed=a[head].Next;
				head=a[a[head].Next].Next;
			}
			else{
				a[ed].Next=head;
				a[head].isplay=0;
				a[head].Before=ed;
				ed=head;
				head=a[head].Next;
			}
		}
			cout<<a[head].name<<" "<<a[a[head].Next].name<<endl;
			a[a[head].Next].isplay=a[head].isplay=1;
			gamer=2;
		}
		else{
			cout<<a[head].name<<endl;
			a[head].isplay=1;
			gamer=1;
		}
	}
}
void arrive(){
	string ss;
	cin>>ss;
	if(a[q[ss]].isok==1)cout<<"Error"<<endl;
	else{
		if(q[ss]==0){
			a[++k].name=ss;
			a[ed].Next=k;
			a[k].isok=1;
			a[k].Before=ed;
			q[ss]=k;
			ed=k;
			if(head==0)head=ed;
			sp++;
		}
		else{
			a[ed].Next=q[ss];
			a[q[ss]].isok=1;
			a[q[ss]].Before=ed;
			ed=q[ss];
			if(head==0)head=ed;
			sp++;
		}
		cout<<"OK"<<endl;
	}
}
void leave(){
	string ss;
	cin>>ss;
	if(a[q[ss]].isplay==1)cout<<"Error"<<endl;
	else{
		if(q[ss]==0)cout<<"Error"<<endl;
		else{
		if(a[q[ss]].isok==0)cout<<"Error"<<endl;
			else{
				cout<<"OK"<<endl;
				if(q[ss]!=ed&&q[ss]!=head){
					a[q[ss]].isok=0;
					a[a[q[ss]].Before].Next=a[q[ss]].Next;
					a[a[q[ss]].Next].Before=a[q[ss]].Before;
					sp--;
				}
				if(q[ss]==head&&q[ss]==ed){
					sp--;
					a[q[ss]].isok=0;
					head=ed=0;
				}
				else{
				if(q[ss]==ed){
					a[q[ss]].isok=0;
					a[a[q[ss]].Before].Next=0;
					sp--;
					ed=a[q[ss]].Before;
				}
				if(q[ss]==head){
						a[q[ss]].isok=0;
						a[a[q[ss]].Next].Before=0;
						sp--;
						head=a[q[ss]].Next;
					}
				}
			}
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s=="start")start();
		if(s=="arrive")arrive();
		if(s=="leave")leave();
	/*	for(int i=head;i!=ed;i=a[i].Next){
			cout<<a[i].name<<' ';
		}*/
		//cout<<a[ed].name<<endl;
	}
}
```

---

## 作者：COsm0s (赞：0)

## $\mathcal{Solution}$

很 STL 的一道题。

作为一道数据结构，我们需要观察维护的是什么，再考虑我们用什么维护。

1. 排队的人及其顺序。

2. 当前所有出现的人是否在排队的队列里。

3. 游玩的人及其顺序。

这就是我们需要维护的东西。

再来看我们可以用什么维护。

1. 对于第一点，我们明显需要一个近似队列，但是要能从任意位置删除的结构。

	作者使用了 `set` 和 `map` 结合的方法，更加普遍的用法是 `set` 结构体后重载运算符。
    
    这一段复杂度为 $\Theta(\log n)$。

2. 对于第二点，由于每个人只有在和不在即 $0,1$ 两种状态，所以直接用 `map` 维护即可。

3. 对于第三点，因为游玩的人最多只有 $2$ 个，所以直接暴力 `vector` 维护。

在实际代码中，我们可以分段，将 `arrive`，`leave`，`start` 操作分开写，这样在 `start` 函数中对于插入删除的操作，可以直接运用上面的函数。

复杂度为 $\Theta(n \log n)$。

## $\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
set<int> se;
unordered_map<int, string> name;
unordered_map<string, int> que, game;
vector<string> G;
string now, s;
void Arrive(string s, bool out_or_in) {
	if(que[s] || game[s]) {
		if(out_or_in) cout << "Error\n";
		return ;
	}
	int now_id = se.empty() ? 0 : *(-- se.end());
	se.insert(que[s] = now_id + 1), name[now_id + 1] = s;
	if(out_or_in) cout << "OK\n";
}
void Leave(string s, bool out_or_in) {
	if(!que[s]) {
		if(out_or_in) cout << "Error\n";
		return ;
	}
	se.erase(que[s]), name[que[s]] = "", que[s] = 0;
	if(out_or_in) cout << "OK\n";
}
void Start() {
	for(auto v : G) game[v] = 0, Arrive(v, 0);
	G.clear();
	int Size = min(2, (int)se.size());
	if(se.empty()) return cout << "Error\n", void();
	for(int i = 0; i < Size; i ++) {
		G.emplace_back(name[*se.begin()]);
		Leave(name[*se.begin()], 0);
		game[G[i]] = 1;
		cout << G[i] << ' ';
	}
	cout << '\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int n;
	cin >> n;
	while(n --) {
		cin >> s;
		if(s == "start") Start();
		if(s == "arrive") cin >> now, Arrive(now, 1);
		if(s == "leave") cin >> now, Leave(now, 1);
	}
	return 0;
}
```


---

## 作者：rainygame (赞：0)

~~从 T3 模拟题看得出来，出题人是真的很想模拟 CSP-J。~~

本题的最难点即为 `leave` 操作，这也是本题的精髓。分析题目后发现，如果删除时暴力枚举队列，复杂度是 $O(n^2)$ 的，不能通过这道题。

所以我们需要用其它的方法来让我们知道队列里有没有这个元素。

一个想法是使用 `set` 来简单判断。在这里，`st` 表示排队但不在游玩的人的集合、`p` 表示正在游玩的人的集合、`que` 表示排队但没在游玩的队列、`play` 表示游玩队列。流程如下：

- `start` 时先判断，如果两个队列均为空则 `Error`。然后从 `play` 队列里不断的弹出结点。弹出的同时从 `p` 里删除，并添加进 `st` 里，且加入到 `que` 的队尾。然后从 `que` 那里找前两个人。当然，因为即使 `leave` 了队列里的人还在，所以必须要判断是否在 `st` 中，如果不在则往后找，如果在则从 `st` 中删除，添加到 `p` 并添加进 `play` 队尾（注意最多只能加 $2$ 个人）。加的同时记得输出。
- `arrive` 时先判断 `p` 和 `st`，可以的话就加进 `st`，并放入 `que` 的队尾。
- `leave` 时先判断。如果可以删除就只从 `st` 里删除。

赛时代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
set<string> p;
set<string> st;
queue<string> que, play;
string opt, name;
vector<string> vec;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    while (n--){
    	cin >> opt;
    	if (opt == "start"){
    		if (play.empty() && que.empty()){
    			cout << "Error\n";
    			continue;
			}
			while (!play.empty()){
				st.insert(play.front());
				p.erase(play.front());
				que.push(play.front());
				play.pop();
			}
			vec.clear();
			for (int i(1); i<=2 && !que.empty(); ++i, que.pop()){
				if (st.find(que.front()) == st.end()){
					--i;
					continue;
				}
				st.erase(que.front());
				play.push(que.front());
				p.insert(que.front());
				vec.push_back(que.front());
			}
			for (auto i: vec) cout << i << ' ';
			cout << '\n';
		}else if (opt == "arrive"){
			cin >> name;
			if (p.find(name) != p.end() || st.find(name) != st.end()) cout << "Error\n";
			else{
				st.insert(name);
				que.push(name);
				cout << "OK\n";
			}
		}else{
			cin >> name;
			if (p.find(name) != p.end() || st.find(name) == st.end()) cout << "Error\n";
			else{
				st.erase(name);
				cout << "OK\n";
			}
		}
	}

    return 0;
}
```

但是这样的代码只有 $40$ 分。我们通过观察 WA 的测试点，发现有 `leave` 的才会 WA。

通过观察，我找到了这样一组 hack：

```
5
arrive A
arrive C
leave A
arrive A
start
```

answer：

```
OK
OK
OK
OK
C A 
```

我们发现，如果 `A` 来了又走又来的话，它在队列的位置依旧在前面。而 `st` 也有它的“档案”。于是，它就排在了前面。

对于这个问题，我的解决方案是使用 `map` 记录队列里有多少个 `A`。每次扫到就减少 $1$。直到只剩一个的时候，才允许游玩。然后维护一下，就可以了。

赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
set<string> p, st;
map<string, int> mp;
queue<string> que, play;
string opt, name;
vector<string> vec;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    while (n--){
    	cin >> opt;
    	if (opt == "start"){
    		if (play.empty() && que.empty()){
    			cout << "Error\n";
    			continue;
			}
			while (!play.empty()){
				++mp[play.front()];
				st.insert(play.front());
				p.erase(play.front());
				que.push(play.front());
				play.pop();
			}
			vec.clear();
			for (int i(1); i<=2 && !que.empty(); ++i, --mp[que.front()], que.pop()){
				if (mp[que.front()] != 1 || st.find(que.front()) == st.end()){
					--i;
					continue;
				}
				st.erase(que.front());
				play.push(que.front());
				p.insert(que.front());
				cout << que.front() << ' ';
			}
			cout << '\n';
		}else if (opt == "arrive"){
			cin >> name;
			if (p.find(name) != p.end() || st.find(name) != st.end()) cout << "Error\n";
			else{
				st.insert(name);
				++mp[name];
				que.push(name);
				cout << "OK\n";
			}
		}else{
			cin >> name;
			if (p.find(name) != p.end() || st.find(name) == st.end()) cout << "Error\n";
			else{
				st.erase(name);
				cout << "OK\n";
			}
		}
	}

    return 0;
}
```


---

## 作者：RyanLi (赞：0)

传送门：[P9518 queue](https://www.luogu.com.cn/problem/P9518)

更佳的阅读体验：[洛谷 P9518 题解](https://blog.ryanli.top/index.php/archives/48/)

---

很明显，这是一道模拟。

注意到题目名为 queue，很多人的第一反应当然是使用 `std::queue` ~~（别问我怎么知道的）~~。然而由于需要支持 `leave` 操作，从排队的队列中删除元素，因此本题并不应该使用 `std::queue` 维护排队的队列。

有没有在 `std::queue` 的基础上还能支持删除操作的容器呢？答案是肯定的，即 `std::list`。注意，接下来的「队列」总是指使用 `std::list` 维护的排队的队列，**与上文提到的 `std::queue` 无关**。

对于 `start` 操作，开始游戏后，由于正在游玩的人需要按原顺序回到队尾，因此我们使用 `std::queue` 维护正在游玩的人。当开始游戏时，先将正在游玩的人全部加入队尾，然后将队首的两人弹出队列，加入正在游玩的人。然而可能有当前队列为空或者只有一个人的情况，因此需要加一些特判。

对于 `arrive` 操作，只需要判断这个人是不是已经在队列中，如果不在就输出 `Error`，否则输出 `OK`，并加入队尾。

对于 `leave` 操作，需要判断这个人是不是在游玩、是不是在队列中两种情况。如果正在游玩或不在队列中，直接输出 `Error`，否则输出 `OK`，并从队列中找到这个元素并删除。

值得注意的是，如果对于每次 `leave` 操作都对整个 `std::list` 进行一次遍历，会消耗大量的时间。然而并不是每次 `leave` 操作都需要完整遍历一次。我们可以另外维护一个 `std::unordered_map`，用来记录某个元素是否在队列中，如果不在队列中则直接输出 `Error` 即可。事实上，这样可以省去很多无用的遍历，大大提高了效率。

---

接下来是代码：

``` cpp
#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <unordered_map>
using namespace std;

int n;
string op, x;
queue<string> last;  // 表示正在游玩的人
list<string> q;  // 队列
unordered_map<string, bool> inq;  // 表示在队列中

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> n; n; --n) {
        cin >> op;
        if (op == "start") {
            // 将上次游玩的人加入队尾
            while (!last.empty())
                q.emplace_back(last.front()), inq[last.front()] = true, last.pop();
            // 如果队列为空直接输出
            if (q.empty()) {
                cout << "Error\n";
                continue;
            } // 将队首加入正在游玩的人
            last.emplace(q.front()), inq[q.front()] = false;
            cout << q.front(), q.pop_front();
            // 如果有第二个人则继续加入
            if (!q.empty()) {
                last.emplace(q.front()), inq[q.front()] = false;
                cout << ' ' << q.front(), q.pop_front();
            } cout << '\n';
        } else if (op == "arrive") {
            cin >> x;
            // 如果正在游玩或者在队列中就直接输出 Error
            if ((!last.empty() && (last.front() == x || last.back() == x)) || inq[x]) {
                cout << "Error\n";
                continue;
            } // 加入队列
            q.emplace_back(x), inq[x] = true;
            cout << "OK\n";
        } else {
            cin >> x;
            // 如果正在游玩或者不在队列中就直接输出 Error
            if (!last.empty() && (last.front() == x || last.back() == x) || !inq[x]) {
                cout << "Error\n";
                continue;
            } // 从队列中删除
            q.erase(find(q.begin(), q.end(), x)), inq[x] = false;
            cout << "OK\n";
        }
    } return 0;
}
```



---

## 作者：Kedit2007 (赞：0)

看一眼数据范围，发现题目要求我们使用 $O(\log n)$ 的时间处理每一次操作。那么首先分析一下每一次操作需要做什么事。

- `start`：从一个容器中找到开头的元素并移出容器，即能够找到并取出关键字最大/最小的元素；
- `arrive`：查找一个容器中是否存在某个元素；将一个元素放入容器
- `leave`：查找一个容器中是否存在某个元素，若存在则将其移除。

在队列中的先后顺序可以通过给容器中的每个元素加上时间戳，并将容器中的元素按时间戳排序实现。观察上列需求，可以发现 `set` 能够满足这些需求，只需以时间戳为关键字放进 `set`，由于 `set` 有序，就能通过它的 `begin` 找到开头的人。

这里我采用了 `set< pair<int, string> >` 存储这个队列，但是这产生了一个问题：查询一个元素是否在队中比较难实现。那怎么办呢？再开一个 `map<string, int>` 记录人对应的时间戳就好啦！

尽管这样做可能有些麻烦，但是每个操作都只需要 $O(\log n)$ 的时间，应对此题绰绰有余。

### 参考代码

```cpp
int main()
{
	int q;
	cin >> q;
	int cnt = 0;
	string a, b;
	map<string, int> person;
	set<pair<int, string>> que;
	
	auto arrive = [&](string s)
	{
		que.insert({cnt, s});
		person[s] = cnt;
		cnt++;
	};
	
	auto leave = [&](string s)
	{
		que.erase(que.find({person[s], s}));
		person.erase(person.find(s));
	};
	
	while (q--)
	{
		string opr;
		cin >> opr;
		if (opr == "start")
		{
			if (a != "")
			{
				arrive(a);
				if (b != "")
				{
					arrive(b);
				}
			}
			if (que.size() == 0)
			{
				cout << "Error" << '\n';
				continue;
			}
			a = que.begin()->second;
			leave(a);
			if (que.size() != 0)
			{
				b = que.begin()->second;
				leave(b);
			}
			cout << a << ' ' << b << '\n';
		}
		else if (opr == "leave")
		{
			string s;
			cin >> s;
			if (person.find(s) != person.end())
			{
				leave(s);
				cout << "OK" << '\n';
			}
			else
			{
				cout << "Error" << '\n';
			}
		}
		else if (opr == "arrive")
		{
			string s;
			cin >> s;
			if (a == s || b == s || person.find(s) != person.end())
			{
				cout << "Error" << '\n';
			}
			else
			{
				arrive(s);
				cout << "OK" << '\n';
			}
		}
	}
}
```

---

## 作者：Night_sea_64 (赞：0)

本题是个大模拟，同时考察了队列、链表等简单数据结构。

队列：从后面加入，从前面弹出，一定满足“先进先出”。这题因为有 `leave` 操作，所以只用队列解决不了问题。

链表：可以从任意位置，用 $O(1)$ 的时间插入、弹出。能够用在这道题。我是手写的链表，需要记录 last 和 next，即一个元素的上一个和下一个分别是什么。

但是链表不支持随机访问，就是想找到一个值，必须从两端向中间挨个找。这是我们不想要的。那怎么办？用 STL 的 map！

map 可以用 $O(\log n)$ 的时间，用任何东西作为下标，去寻找对应的值。在这道题中，用 map 维护对于每一个人（用名字作为下标）的位置。写法见下面代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
int n,head=1,tail=0;
string p1,p2;
struct node{string name;int last,next;}a[100010];
map<string,int>pos;
int push(string s)//进队尾
{
    if(pos[s]||p1==s||p2==s)return -1;
    tail++;
    a[tail-1].next=tail;
    a[tail]={s,tail-1,tail+1};
    pos[s]=tail;
    return 0;
}
int del(string s)//离开队列
{
    int p=pos[s];
    if(!p||p1==s||p2==s)return -1;
    if(p==head)head=a[p].next;
    else if(p==tail)tail=a[p].last;
    a[a[p].last].next=a[p].next;
    a[a[p].next].last=a[p].last;
    pos[s]=0;
    return 0;
}
int play()//进去玩
{
    string s=a[head].name;
    //cout<<s<<endl;
    int res=del(s);
    if(res==-1)return -1;
    if(p1=="")p1=s;
    else p2=s;
    return 0;
}
int back()//玩完回到队尾
{
    if(p1!="")
    {
        string s=p1;
        p1="";
        push(s);
    }
    if(p2!="")
    {
        string s=p2;
        p2="";
        push(s);
    }
    return 0;
}
int main()
{
    cin>>n;
    while(n--)
    {
        string op;
        cin>>op;
        if(op=="start")
        {
            back();
            if(play()==-1)cout<<"Error"<<endl;
            else if(play()==-1)cout<<p1<<endl;
            else cout<<p1<<" "<<p2<<endl;
        }
        if(op=="arrive")
        {
            string s;
            cin>>s;
            if(push(s)==-1)cout<<"Error"<<endl;
            else cout<<"OK"<<endl;
        }
        if(op=="leave")
        {
            string s;
            cin>>s;
            if(del(s)==-1)cout<<"Error"<<endl;
            else cout<<"OK"<<endl;
        }
    }
    return 0;
}
```

注：这是我小号 @A_Legendary_Coder 提交的代码。

---

## 作者：Argvchs (赞：0)

## 1. 题解

我们可以用 `list` 模拟队列，在更新队列的同时维护一个 `unordered_map` 记录元素出现的位置。

为了方便，我们用 $\mathrm{A1}$ 表示排队队列，$\mathrm{A2}$ 表示游玩队列。

对于操作 `start`，先将 $\mathrm{A2}$ 的元素放入 $\mathrm{A1}$ 的队尾，然后将 $\mathrm{A1}$ 队头的元素放入 $\mathrm{A2}$，如果 $\mathrm{A1}$ 为空则输出 `Error`。

```cpp
while (!A2.empty()) {
    string x = A2.front();
    A2.pop_front();
    S2.erase(x);
    A1.push_back(x);
    S1[x] = --A1.end();
}
if (A1.empty()) {
    cout << "Error\n";
    continue;
}
int cnt = 0;
while (!A1.empty() && cnt < 2) {
    string x = A1.front();
    A1.pop_front();
    S1.erase(x);
    A2.push_back(x);
    S2[x] = --A2.end(), ++cnt;
    cout << x << ' ';
}
cout << '\n';
```

对于操作 `arrive`，如果 $x$ 在 $\mathrm{A1}$ 或 $\mathrm{A2}$ 中则输出 `Error`，否则将 $x$ 放到 $\mathrm{A1}$ 的队尾，并输出 `OK`。

```cpp
if (S1.contains(x) || S2.contains(x)) {
    cout << "Error\n";
    continue;
}
A1.push_back(x);
S1[x] = --A1.end();
cout << "OK\n";
```

对于操作 `leave`，如果 $x$ 不在 $\mathrm{A1}$ 中则输出 `Error`，否则根据记录的位置将 $x$ 在 $\mathrm{A1}$ 删除，并输出 `OK`。

```cpp
if (!S1.contains(x)) {
    cout << "Error\n";
    continue;
}
A1.erase(S1[x]);
S1.erase(x);
cout << "OK\n";
```

## 2. Code

```cpp
#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
int n;
string op;
list<string> A1, A2;
unordered_map<string, list<string>::iterator> S1, S2;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while (n--) {
        cin >> op;
        if (op == "start") {
            while (!A2.empty()) {
                string x = A2.front();
                A2.pop_front();
                S2.erase(x);
                A1.push_back(x);
                S1[x] = --A1.end();
            }
            if (A1.empty()) {
                cout << "Error\n";
                continue;
            }
            int cnt = 0;
            while (!A1.empty() && cnt < 2) {
                string x = A1.front();
                A1.pop_front();
                S1.erase(x);
                A2.push_back(x);
                S2[x] = --A2.end(), ++cnt;
                cout << x << ' ';
            }
            cout << '\n';
        } else if (op == "arrive") {
            string x;
            cin >> x;
            if (S1.contains(x) || S2.contains(x)) {
                cout << "Error\n";
                continue;
            }
            A1.push_back(x);
            S1[x] = --A1.end();
            cout << "OK\n";
        } else {
            string x;
            cin >> x;
            if (!S1.contains(x)) {
                cout << "Error\n";
                continue;
            }
            A1.erase(S1[x]);
            S1.erase(x);
            cout << "OK\n";
        }
    }
    return 0;
}
```

---

