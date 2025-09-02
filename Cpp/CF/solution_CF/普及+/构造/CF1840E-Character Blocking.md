# Character Blocking

## 题目描述

You are given two strings of equal length $ s_1 $ and $ s_2 $ , consisting of lowercase Latin letters, and an integer $ t $ .

You need to answer $ q $ queries, numbered from $ 1 $ to $ q $ . The $ i $ -th query comes in the $ i $ -th second of time. Each query is one of three types:

- block the characters at position $ pos $ (indexed from $ 1 $ ) in both strings for $ t $ seconds;
- swap two unblocked characters;
- determine if the two strings are equal at the time of the query, ignoring blocked characters.

Note that in queries of the second type, the characters being swapped can be from the same string or from $ s_1 $ and $ s_2 $ .

## 说明/提示

Let's look at the strings $ s_1 $ and $ s_2 $ after each of the $ q $ queries. Blocked characters will be denoted in red.

First example input:

( $ codeforces $ , $ codeblocks $ ) $ \rightarrow $ ( $ codeforces $ , $ codeblocks $ ) $ \rightarrow $ ( $ code\color{red}{f}orces $ , $ code\color{red}{b}locks $ ) $ \rightarrow $ ( $ code\color{red}{fo}rces $ , $ code\color{red}{bl}ocks $ ) $ \rightarrow $ ( $ code\color{red}{for}ces $ , $ code\color{red}{blo}cks $ ) $ \rightarrow $ ( $ code\color{red}{for}c\color{red}{e}s $ , $ code\color{red}{blo}c\color{red}{k}s $ ) $ \rightarrow $ ( $ code\color{red}{for}c\color{red}{e}s $ , $ code\color{red}{blo}c\color{red}{k}s $ ) $ \rightarrow $ ( $ codef\color{red}{or}c\color{red}{e}s $ , $ codeb\color{red}{lo}c\color{red}{k}s $ )

Second example input:

( $ cool $ , $ club $ ) $ \rightarrow $ ( $ cuol $ , $ clob $ ) $ \rightarrow $ ( $ cuol $ , $ cbol $ ) $ \rightarrow $ ( $ c\color{red}{u}ol $ , $ c\color{red}{b}ol $ ) $ \rightarrow $ ( $ c\color{red}{u}ol $ , $ c\color{red}{b}ol $ ) $ \rightarrow $ ( $ cuol $ , $ cbol $ )

## 样例 #1

### 输入

```
2
codeforces
codeblocks
5 7
3
1 5
1 6
1 7
1 9
3
3
cool
club
2 5
2 1 2 2 3
2 2 2 2 4
1 2
3
3```

### 输出

```
NO
YES
NO
YES
NO```

# 题解

## 作者：AlicX (赞：11)

### 前言

此题主要考验模拟能力以及细节的处理。

~~考场写的时候严重降智，把等于和不等于搞混了。~~

## Solution

发现此题不能够每进行一次操作变更新一次，于是考虑用 $cnt$ 维护 $s1$ 和 $s2$ 的不相同的字母个数，询问时，只需要判断 $cnt$ 的值是多少就可以了。

- 对于操作一，直接进行修改，注意 $cnt$ 的加减。唯一的细节就是记录下这次操作的时间，因为 $t$ 秒后需要更新。

- 对于操作二，分四种情况讨论，每次交换前都需要判断交换前的字母是否相等，并将 $cnt$ 进行加减，然后进行交换，显然地，交换后也依然需要更新 $cnt$。

- 对于操作三，判断此时 $cnt$ 的值是否为零，但是要在判断前将 $t$ 秒前的操作恢复。

### AC Code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+10,INF=1e9;
int n,t;
int p[N]; bool st[N];
string s1,s2;
void work(){ 
	memset(st,false,sizeof st); 
	memset(p,0,sizeof p); 
	cin>>s1>>s2; 
	cin>>t>>n; int cnt=0; 
	for(int i=0;i<s1.size();i++) if(s1[i]!=s2[i]) cnt++; 
	for(int i=1;i<=n;i++){ 
		int opt;
		int a,b,c,d;
		cin>>opt; 
		if(i>t&&st[i-t]){
			if(s1[p[i-t]-1]!=s2[p[i-t]-1]) cnt++;  
		}
		if(opt==1){ 
			cin>>a; st[i]=true; p[i]=a; 
			if(s1[a-1]!=s2[a-1]) cnt--;  		 
		} else if(opt==2){
			cin>>a>>b>>c>>d;
			if(a==1){
				if(c==1){
					if(s1[b-1]==s2[b-1]) cnt++;
					if(s1[d-1]==s2[d-1]) cnt++;
					swap(s1[b-1],s1[d-1]); 
					if(s1[b-1]==s2[b-1]) cnt--;
					if(s1[d-1]==s2[d-1]) cnt--;
				} else{
					if(s1[b-1]==s2[b-1]) cnt++; 
					if(s2[d-1]==s1[d-1]) cnt++; 
					swap(s1[b-1],s2[d-1]); 
					if(s1[b-1]==s2[b-1]) cnt--; 
					if(s2[d-1]==s1[d-1]) cnt--; 
				}
			} else{
				if(c==1){
					if(s1[b-1]==s2[b-1]) cnt++;
					if(s1[d-1]==s2[d-1]) cnt++;
					swap(s2[b-1],s1[d-1]);
					if(s1[b-1]==s2[b-1]) cnt--;
					if(s1[d-1]==s2[d-1]) cnt--;
				} else{
					if(s1[b-1]==s2[b-1]) cnt++;
					if(s2[d-1]==s1[d-1]) cnt++;
					swap(s2[b-1],s2[d-1]);
					if(s1[b-1]==s2[b-1]) cnt--;
					if(s2[d-1]==s1[d-1]) cnt--;
				}
			} 
		}
		else{
			if(!cnt) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
}
signed main(){
	int T; cin>>T;
	while(T--) work();
	return 0;
} 

```

---

## 作者：luqyou (赞：4)

# 题意

给定两个字符串 $s1,s2$，维护以下操作：

- 给定 $pos$，锁定 $s1_{pos}$ 和 $s2_{pos}$。

- 给定 $op1,pos1,op2,pos2$，若 $op1=1$ 表示 $pos1$ 代表的是 $s1$ 的位置，否则代表的是 $s2$ 的位置；若 $op2=1$ 表示 $pos2$ 代表的是 $s1$ 的位置，否则代表的是 $s2$ 的位置。然后将这两个位置的字符交换。保证交换的字符没有被锁定。

- 查询 $s1$ 和 $s2$ 是否相等。被锁定的字符不算在内。

# 思路

我们使用一个 set 维护两个字符串字符不同的位置。

对于操作 $1$，锁定期间将这个操作放入队列并在 set 中删除这个位置，每次循环读入操作的时候判断队首操作是否过期，如果被过期则判断字符是否不同，若不同则在 set 中重新加入这个位置。

对于操作 $2$，交换之后判断两个位置的字符是否相等来加入或删除位置即可。

对于操作 $3$，若 set 为空则为 ```Yes```，否则为 ```No```。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct bl{//锁定操作结构体
	int tm,pos;
};
void solve(){
	string s1,s2;
	cin>>s1>>s2;
	s1=" "+s1;
	s2=" "+s2;
	int n=s1.size(),t,q;
	cin>>t>>q;
	set<int> s;
	queue<bl> blocks;
	for(int i=1;i<=n;i++){
		if(s1[i]!=s2[i]){
			s.insert(i);
		}
	}
	/*cout<<"debug:";
	for(set<int>::iterator it=s.begin();it!=s.end();it++){
		cout<<*it<<" ";
	}
	cout<<endl;*/
	for(int i=1;i<=q;i++){
		if(blocks.size()){//判断队首锁定操作是否过期
			int t1=blocks.front().tm,t2=blocks.front().pos;
			if(i-t1>=t){
				if(s1[t2]!=s2[t2]){
					s.insert(t2);
				}
				blocks.pop();
			}
		}
		int op;
		cin>>op;
		if(op==1){//操作1
			int p;
			cin>>p;
			if(s1[p]!=s2[p]){
				s.erase(p);
				blocks.push((bl){i,p});
			}
		}
		if(op==2){//操作2
			int t1,p1,t2,p2;
			cin>>t1>>p1>>t2>>p2;
			if(t1==1){
				if(t2==1){
					swap(s1[p1],s1[p2]);
				}
				if(t2==2){
					swap(s1[p1],s2[p2]);
				}
			}
			if(t1==2){
				if(t2==1){
					swap(s2[p1],s1[p2]);
				}
				if(t2==2){
					swap(s2[p1],s2[p2]);
				}
			}
			if(s1[p1]==s2[p1]){
				s.erase(p1);
			}
			else{
				s.insert(p1);
			}
			if(s1[p2]==s2[p2]){
				s.erase(p2);
			} 
			else{
				s.insert(p2);
			}
		}
		if(op==3){//操作3
			if(s.size()){
				cout<<"NO"<<endl;
			}
			else{
				cout<<"YES"<<endl;
			}
		}
		/*cout<<"debug:"<<s1<<" "<<s2<<endl;
		cout<<"debug:";
		for(set<int>::iterator it=s.begin();it!=s.end();it++){
			cout<<*it<<" ";
		}
		cout<<endl;*/
	}
}
int main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}
```

---

## 作者：Flanksy (赞：3)

#### 分块

------------

看到题目名称里的 Blocking，感觉像是某种提示（然而并不是），从而写了一份分块代码。

题目要求实现的操作：

- 同时封锁两个字符串的某一位，并在 $t$ 秒后复原。
- 交换两个字符，这两个字符可能在同一字符串，也可能不在。
- 询问两个字符串是否相同，忽略被封锁的位。

由于是分块，所以先把字符串割开，因为给出的两个字符串位数相等，使用 $same_i$ 表示两个字符串的第 $i$ 块是否相同，回答询问时如果存在一块 $same_i \neq 1$，说明不相同，否则相同。

对于交换操作，直接交换即可。每次交换后维护本次操作影响的块的 $same$ 值。

对于封锁操作，先记录两个字符串封锁前指定位的信息放入队列，然后将指定位设为相同的字符即可。同样地，在每次操作后维护影响的块的 $same$ 值。

在每次执行操作前查看队首信息，如果封锁时间结束，将指定位还原成封锁前的情况，然后维护影响到的块的 $same$ 值。

分块使用结构体实现，时间复杂度近似为 $O(q \sqrt{|S|})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int LEN=pow(200005,1/2.5)+1;//固定块长 
inline int father(int x){return (x-1)/LEN+1;}
struct StringBlock{
	string s[200005/LEN+5];
	int blocknum;
	void start(const string &x){//初始化 
		for(int i=1;i<=blocknum;i++) s[i].clear();
		int sum=LEN,cnt=0;
		for(int i=0;x[i]!='\0';i++){
			if(++sum>LEN) sum=1,++cnt;
			s[cnt].push_back(x[i]);
		}
		blocknum=cnt;
	}
	auto &pos(int x){//直接控制字符串第 x 位 
		const int blo=father(x);//找到所属块,注意string下标从0开始 
		return s[blo][x-(blo-1)*LEN-1];
	}
}s[3];
struct Time{int i,p;char x,y;};
bool same[200005/LEN+5];
int t,q;
void solution(){
	for(int i=1;i<=2;i++){
		static string x;
		cin>>x;
		s[i].start(x);
	}
	const int n=s[1].blocknum;//首先处理出 same 数组 
	for(int i=1;i<=n;i++) same[i]=s[1].s[i]==s[2].s[i];
	cin>>t>>q;
	queue<Time> blocked;//存储封锁信息 
	for(int i=1;i<=q;i++){
		static int x,opt,pos;
		cin>>opt;
		if(!blocked.empty()&&blocked.front().i==i){
			auto now=blocked.front();
			s[1].pos(now.p)=now.x;
			s[2].pos(now.p)=now.y;
			blocked.pop(),pos=father(now.p);
			same[pos]=s[1].s[pos]==s[2].s[pos];
		}
		if(opt==1){
			cin>>x,pos=father(x);//封锁时注意维护 same 
			blocked.push(Time{i+t,x,s[1].pos(x),s[2].pos(x)});
			s[1].pos(x)='#',s[2].pos(x)='#';
			same[pos]=s[1].s[pos]==s[2].s[pos];
		}
		else if(opt==2){
			static int b1,b2,p1,p2,x1,x2;
			cin>>x1>>p1>>x2>>p2;
			b1=father(p1),b2=father(p2);
			swap(s[x1].pos(p1),s[x2].pos(p2));
			same[b1]=s[1].s[b1]==s[2].s[b1];
			same[b2]=s[1].s[b2]==s[2].s[b2];
		}
		else{
			bool found=1;
			for(int i=1;i<=n;i++) if(!same[i]) found=0;
			cout<<(found ? "YES":"NO")<<'\n';
		}
	}
}
int T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--) solution();
	return 0;
}
```


---

## 作者：escapist404 (赞：2)

### Statement

给你两个字符串。

操作有：

* 忽视两个字符串的同一位置一段时间。
* 交换某两个未被忽视的字符（可以跨越字符串）。
* 查询字符串未被忽视的部分是否相等。

### Solution

考虑字符串哈希。

对每个字符设置一个 hash 值 $\mathrm{ref}$，对每个位置设置一个 hash 值 $\mathrm{base}$。

字符串的 hash 值为 $\sum_{i=0}^{len} ( \mathrm{ref}_{s_i} \cdot \mathrm{base}_i)$。

操作一即钦定 $s_1$ 的某一位置等于 $s_0$，开一个队列维护这个操作，到了一定时间就撤销即可。

操作二即模拟 hash 值的变化，见代码。

操作三即判断 hash 值是否相等。

单个测试点时间复杂度 $\mathcal{O}(q)$。

### Code

```cpp
#include <bits/stdc++.h>

using i64 = long long;

const i64 mask = (1 << 20) - 1;

void solve() {
	std::mt19937 rnd(time(0));
	std::vector<i64> ref(26);
	for (i64& i : ref) i = (rnd() & mask);

	std::string s[2];
	std::cin >> s[0] >> s[1];

	std::vector<i64> base(s[0].size());
	for (i64& i : base) i = rnd() & mask;

	i64 hash[2] = {0, 0};

	auto hash_char = [&ref](const char ch) { return ref[ch - 'a']; };

	auto get_hash = [&hash_char, &ref, &base](std::string s, i64& v) {
		v = 0;
		for (int i = 0; i < (int)s.size(); ++i) v += hash_char(s[i]) * base[i];
	};

	get_hash(s[0], hash[0]);
	get_hash(s[1], hash[1]);

	int q, t;
	std::cin >> t >> q;

	std::queue<std::pair<i64, int>> queue;

	for (int i = 0; i < q; ++i) {
		if (queue.size()) {
			auto x = queue.front();
			if (x.second == i) {
				queue.pop();
				hash[1] -= x.first;
			}
		}

		int opt;
		std::cin >> opt;

		if (opt == 1) {
			int pos;
			std::cin >> pos;
			--pos;
			hash[1] += (hash_char(s[0][pos]) - hash_char(s[1][pos])) * base[pos];
			queue.push({(hash_char(s[0][pos]) - hash_char(s[1][pos])) * base[pos], i + t});
		} else if (opt == 2) {
			int is[2], pos[2];
			std::cin >> is[0] >> pos[0] >> is[1] >> pos[1];
			--is[0], --is[1], --pos[0], --pos[1];

			hash[is[0]] +=
				(hash_char(s[is[1]][pos[1]]) - hash_char(s[is[0]][pos[0]])) * base[pos[0]];
			hash[is[1]] +=
				(hash_char(s[is[0]][pos[0]]) - hash_char(s[is[1]][pos[1]])) * base[pos[1]];

			std::swap(s[is[0]][pos[0]], s[is[1]][pos[1]]);
		} else {
			if (hash[0] == hash[1])
				std::cout << "YES" << '\n';
			else
				std::cout << "NO" << '\n';
		}
	}
}

int main() {
	int tt;
	std::cin >> tt;
	while (tt--) solve();
	return 0;
}
```

---

## 作者：sz_jinzikai (赞：1)

[洛谷传送门](/problem/CF1840E) &[CF 传送门](//codeforces.com/problemset/problem/1840/E)
# 题目大意
给你两个字符串。

操作有 $3$ 种：
1. 忽视两个字符串的同一位置一段时间。
1. 交换某两个未被忽视的字符（可以跨越字符串）。
1. 查询字符串未被忽视的部分是否相等。

# 思路
本题纯模拟即可，只要随时维护一个变量 $now$，表示现在两个字符串中有几个字符不一样。
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
using namespace std;
int T, t, q, op, block[200005], a, b, c, d, now; //定义变量
string s[2]; //定义变量
bool flag; //定义变量
int main () { //定义主函数
	cin >> T; //输入数据组数
	while (T --) { //多组数据的通用写法
		cin >> s[0] >> s[1] >> t >> q; //输入
		for (int i = 0; i < q; ++ i)
			block[i] = 0; //多组数据要清空
		now = 0; //多组数据要归零
		for (int i = 0; i < s[0].size (); ++ i)
			now += s[0][i] != s[1][i]; //计算初始时有多少不同
		for (int i = 0; i < q; ++ i) {
			cin >> op; //输入类别
			now += block[i] && s[0][block[i] - 1] != s[1][block[i] - 1]; //判断是否有解锁任务
			if (op < 2) { //如果是第 1 种
				cin >> a; //输入锁定位置
				if (i + t < q) //如果解锁时还没做完所有任务
					block[i + t] = a; //记录应该解锁哪个位置
				now -= s[0][a - 1] != s[1][a - 1]; //计算现在有没有少了不同
			} else if (op < 3) { //如果是第 2 种
				cin >> a >> b >> c >> d; //输入
				-- a, -- b, -- c, -- d; //转换成 0 开始
				now += s[0][b] == s[1][b]; //计算现在相差不同
				now += s[0][d] == s[1][d]; //计算现在相差不同
				swap (s[a][b], s[c][d]); //交换位置
				now -= s[0][b] == s[1][b]; //计算现在相差不同
				now -= s[0][d] == s[1][d]; //计算现在相差不同
			} else //如果是第 3 种
				cout << (now ? "NO\n" : "YES\n"); //判断还有没有不同
		}
	}
	return 0; //结束程序
}
```

---

## 作者：NKL丶 (赞：1)

## Description

给定两个等长度的由小写字母构成的字符串 $s_1,s_2$，然后给出两个数 $t,q$，进行 $q$ 次操作，每次操作有如下选择：（$|s|,t,q \le 2 \times 10^5$）

- 锁定两个字符串的某个位置上的字母，过了 $t$ 次询问后解锁。
- 交换任意两个没有被锁定的字符。（可以同一个串内交换）
- 查询两个字符串是否相同。（忽略锁定的字母）  

多组询问。（$T \le 10^4$）

## Solution

考虑字符串哈希，对两个字符串做一遍哈希后，操作一和二可以变为在哈希值上进行加减（操作一额外记录解锁的时刻），操作三直接比较哈希值是否相等即可。

注意在处理操作二的时候别忘记交换原字符串的字符。

## [Code](https://www.luogu.com.cn/paste/zysnigut)

---

## 作者：SuperBeetle (赞：0)

感觉题解都好长，我除了码风长了~~亿~~一点，其他都很短

其实和第一篇题解差不多，就模拟即可，每次拿一个变量去记录不同的数量，如果为0，就输出 YES，否则输出 NO

上代码！

```cpp
#include <bits/stdc++.h>
#define IAKIOI ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define UPB(x,y,z) upper_bound(x + 1, x + y + 1, z) - x
#define LWB(x,y,z) lower_bound(x + 1, x + y + 1, z) - x
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define pre(i, l, r) for (int i = r; i >= l; i--)
#define UNQIUE(x, y) unqiue(x + 1, x + y + 1)
#define SORT(x, y) sort(x + 1,x + y + 1)
#define pf push_front 
#define pb push_back 
#define IT iterator
#define endl '\n';

const int N = 2e5 + 1, M = 5e4 + 1, INF = 0x3f3f3f3f;
const double ecnts = 1e-6;

#define int long long

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef double db;

void read(int &x) {
	int f = 1, y = 0;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		y = y * 10 + c - '0';
		c = getchar();
	}
	x = y * f;
}

void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

inline int max(int x, int y) {return x > y ? x : y;}
inline int min(int x, int y) {return x < y ? x : y;}

inline void swap(int &x, int &y) {int t = x;x = y, y = t;}
inline int pow(int x, int y) {
	int ans = 1;
	while (y) {
		if (y & 1) ans *= x;
		x *= x, y = y >> 1;
	}
	return ans;
}

string s[2];
int a[N];
bool f[N];

void solve() {
	memset(a, 0, sizeof a); //记住清空
	memset(f, 0, sizeof f);
	cin >> s[0] >> s[1];
	int cnt = 0; //记不相等的数量
	int n = s[0].size();
	s[0] = ' ' + s[0], s[1] = ' ' + s[1];
	rep(i, 1, n) cnt += (s[0][i] != s[1][i]);
	int t, q;
	cin >> t >> q;
	rep(p, 1, q) {
		int op;
		cin >> op;
		if (p > t && f[p - t]) { //如果没越界，且t秒前有字符被封锁了
			if (s[0][a[p - t]] != s[1][a[p - t]]) cnt++;
			f[p - t] = 0;
		}
		if (op == 1) {
			int x;
			cin >> x;
			a[p] = x;
			f[p] = 1;
			if (s[0][x] != s[1][x]) cnt--; //原本不相同，但被封了，就少了一个不相同的
		}
		else if (op == 2) {
			int opt1, opt2, x, y;
			cin >> opt1 >> x >> opt2 >> y;
			opt1--, opt2--; //在这里卡了好久，因为越界了TwT
			if (s[0][x] == s[1][x]) cnt++; //如果这个是相等的，但要换走了，就+1
			if (s[0][y] == s[1][y]) cnt++;//同上
			swap(s[opt1][x], s[opt2][y]);//交换
			if (s[0][x] == s[1][x]) cnt--;//同上面
			if (s[0][y] == s[1][y]) cnt--;
		}
		else {
			if (!cnt) puts("YES");//如果没有不同的输出YES
			else puts("NO");//否则输出NO
		}
	}
}

signed main() {
	IAKIOI;
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1840E)
## 思路
操作 $1$、$2$ 容易在常数时间复杂度完成，操作 $1$ 后续的解除操作也可以使用队列存储完成。但操作 $3$ 直接对比两个串的时间复杂度过高，所以考虑使用 set 存下所有两个字符串不相等的位置。

## 具体过程
首先进行预处理，将两个字符串中不相等的位置加入 set 中。

每次操作开始前判断队首的解除时间是否等于当前时间，如果是则弹出队首元素，接触式如果两个字符串对应位置不相等则在 set 中加入这个位置
- 操作 $1$：在队尾加入锁定的位置和解除时间，如果 set 中有这个位置，则在 set 中删除此位置。
- 操作 $2$：首先进行交换，交换后判定两个位置是否产生了新的不同或相同并在 set 中进行对应操作。
- 操作 $3$：判断 set 中是否还存在元素，是则说明两个字符串不相等，否则说明相等。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = (st); i <= (ed); ++i)
#define RFOR(st, ed, i) for (int i = (ed); i >= (st); --i)
#define FIND(set, key) (set.find(key) != set.end())
#define fir first
#define sec second

// #define debug

typedef long long ll;
typedef double dou;
typedef pair<int, int> pii;

const int maxlen = 2e5 + 10;

int t;
	string s[3];
	int ti, q;
		int op, op1, pos1, op2, pos2;

//bool flag[maxlen];
int len;
queue<pii> que;
set<int> diff;

void work_q (int nti) {
	if (!que.empty() && que.front().sec == nti) {
		int id = que.front().fir;
		que.pop();
		if (s[1][id - 1] != s[2][id - 1]) {
			diff.insert(id);
		}
	}
	
	scanf("%i", &op);
	if (op == 1) {
		scanf("%i", &pos1);
		
		que.push({pos1, nti + ti});
		if (FIND(diff, pos1)) {
			diff.erase(pos1);
		}
	}else if (op == 2) {
		scanf("%i%i%i%i", &op1, &pos1, &op2, &pos2);
		
		swap(s[op1][pos1 - 1], s[op2][pos2 - 1]);
		if (s[1][pos1 - 1] == s[2][pos1 - 1] && FIND(diff, pos1)) {
			diff.erase(pos1);
		}else if (s[1][pos1 - 1] != s[2][pos1 - 1] && !FIND(diff, pos1)) {
			diff.insert(pos1);
		}
		if (s[1][pos2 - 1] == s[2][pos2 - 1] && FIND(diff, pos2)) {
			diff.erase(pos2);
		}else if (s[1][pos2 - 1] != s[2][pos2 - 1] && !FIND(diff, pos2)) {
			diff.insert(pos2);
		}
	}else {
		if (diff.empty()) {
			printf("YES\n");
		}else {
			printf("NO\n");
		}
	}
	return;
}
void work_t () {
	while (!que.empty()) {
		que.pop();
	}
	diff.clear();
	
	cin >> s[1];
	cin >> s[2];
	
	len = s[1].size();
	FOR (0, len - 1, i) {
		if (s[1][i] != s[2][i]) {
			diff.insert(i + 1);
		}
	}
	
	scanf("%i%i", &ti, &q);
	FOR (1, q, i) {
		work_q(i);
	}
	return;
}
int main () {
	scanf("%i", &t);
	while (t--) {
		work_t();
	}
	return 0;
}
```

---

## 作者：Imken (赞：0)

题意的话，题目还是写得比较清楚的，不赘述了。

看到题目，因为操作太简单了，先考虑朴素拿 `string` 暴力，大概是这样的：

- 操作 $1$：使用 pair 数组 ${\rm mark} _ t = (pos, c)$，存储时间 $t$ 坐标 $pos$ 需要修改成字符 $c$，然后在每一次询问的时候更新就行。然后在原字符串对应坐标上改成一个字符集之外的字符。
- 操作 $2$：直接交换就行。
- 操作 $3$：直接比较就行。

但是 `string` 判断相等的时间复杂度有些太高了。怎么优化这个比较呢？

然后就应该不难想到字符串哈希了！

- 对于操作 $1$，在两个 hash 上减去对应字符的 hash 值（相当于修改成空字符），并记录下需要改回去的时间；
- 对于操作 $2$，在原字符串的 hash 值上直接减去这两位对应的值，然后交换之后再加回去对应的值（参见实现）。
- 对于操作 $3$，直接比较 hash 值即可。

注：这里的实现似乎并不是传统意义上的字符串哈希。我们给每一位随机赋一个位权，虽然某种程度上不太严谨，但是在 `u128` 范围内撞上的概率很小（而且看起来很难被卡），基本上可以忽略不计。参见下面的实现。

三个操作都可以在 $O(1)$ 的时间复杂度内完成，还是非常高效的！

具体实现思路跟暴力差不多，详细实现见代码：

```cpp
inline void solve()
{
	mt19937 rnd(time(0) * 46536);
	string s[2];
	u128 hsh[2] = { 0, 0 };
	cin >> s[0] >> s[1];
	int len = s[1].length();
	vector<u128> w(len + 1);
	for (int i = 0; i <= len; i++)
		w[i] = rnd() * rnd() * rnd();
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < len; i++)
			hsh[j] = hsh[j] + s[j][i] * w[i];

	int t, q, opt, pos;
	cin >> t >> q;
	vector<u128> add[2] = { vector<u128>(q + 1, 0), vector<u128>(q + 1, 0) };
	for (int tt = 1; tt <= q; tt++) {
		for (int i = 0; i <= 1; i++)
			hsh[i] = hsh[i] + add[i][tt];
		cin >> opt;
		if (opt == 1) {
			cin >> pos;
			pos--;
			for (int i = 0; i <= 1; i++) {
				hsh[i] = hsh[i] - s[i][pos] * w[pos];
				if (tt + t <= q)
					add[i][tt + t] += s[i][pos] * w[pos];
			}
		} else if (opt == 2) {
			int src1, src2;
			int pos1, pos2;
			cin >> src1 >> pos1 >> src2 >> pos2;
			pos1--, pos2--, src1--, src2--;
			hsh[src1] = hsh[src1] - w[pos1] * s[src1][pos1];
			hsh[src2] = hsh[src2] - w[pos2] * s[src2][pos2];
			swap(s[src1][pos1], s[src2][pos2]);
			hsh[src1] = hsh[src1] + w[pos1] * s[src1][pos1];
			hsh[src2] = hsh[src2] + w[pos2] * s[src2][pos2];
		} else if (opt == 3) {
			if (hsh[0] == hsh[1])
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}
```

---

