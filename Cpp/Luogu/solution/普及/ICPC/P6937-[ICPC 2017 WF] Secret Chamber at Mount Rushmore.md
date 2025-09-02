# [ICPC 2017 WF] Secret Chamber at Mount Rushmore

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/i8ay281j.png)

到现在你可能已经听说过在拉什莫尔山上有一个壮观的石雕，展示了四位著名的美国总统。然而，很少有人知道这个纪念碑中包含一个秘密的房间。这听起来像是好莱坞电影的情节，但这个房间确实存在。它位于亚伯拉罕·林肯的头部后面，设计用作存放重要历史美国文件和文物的记录大厅。历史学家声称大厅的建设在 1939 年停止，未完成的房间直到 1990 年代末才被触及，但这并不是全部真相。

在 1982 年，著名考古学家 S. Dakota Jones 秘密访问了该纪念碑，发现房间实际上已经完成，但被保密。这似乎很可疑，在一些调查之后，她发现了一个隐藏的保险库和一些文件。不幸的是，这些文件没有任何意义，都是乱码。她怀疑它们是用密码写的，但尽管她付出了所有努力，她也无法解码。

本周早些时候，当她在该地区参加 ACM-ICPC 世界总决赛时，Jones 博士终于在 SDSM&T 的 Connolly Hall 发现了解码文件的关键。她找到了一份包含字母翻译列表的文件。有些字母可能有多个翻译，而其他字母可能没有翻译。通过对乱码文件中的单个字母反复应用这些翻译，她可能能够解码它们以获得历史美国文件，如《独立宣言》和《宪法》。她需要你的帮助。

你被给定了字母的可能翻译和一对原始和解码单词的列表。你的任务是验证每对单词是否匹配。如果两个单词长度相同，并且第一个单词的每个字母都可以通过使用可用的翻译零次或多次转换为第二个单词的对应字母，则两个单词匹配。

## 说明/提示

时间限制：1 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
9 5
c t
i r
k p
o c
r o
t e
t f
u h
w p
we we
can the
work people
it of
out the
```

### 输出

```
yes
no
no
yes
yes
```

## 样例 #2

### 输入

```
3 3
a c
b a
a b
aaa abc
abc aaa
acm bcm
```

### 输出

```
yes
no
yes
```

# 题解

## 作者：yangjinqian (赞：8)

### 题目大意：
给出 $m$ 种字母转换关系，再有 $n$ 个询问，判断给定的字符串 $s$ 是否能转换成字符串 $t$ 。

### 思路：
用 map 把每种字母转换关系映射进来，由于一个字符可能会有多种转换关系，所以 map 定义的第二个要写成 `vector<char>` 。

接下来判断的时候，先判断两个字符串长度是否相等，否则输出 `no` ，是则循环 dfs 。

dfs 的时候可以用一个变量记录是否转换到当前字符，别忘了还有一个标记数组。而当前字符如果为 `char(0)` 就是递归边界。接下来就枚举 map 里的 `vector` 每次只要当前要转换的字符没被标记过就 dfs 这个字符。

### 参考文献 
dfs:
```cpp
void dfs(char x, char y){
	if (x == y){
		flag = 1;
		return;
	}
	v[int(x)] = 1;
	if (x == char(0)) return;
	for (int i = 0; i < a[x].size(); i++)
		if (!v[int(a[x][i])])
			dfs(a[x][i], y);
}
```

map 定义： `map<char, vector<char>> a;`

### 最终代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int n, m;
bool flag = 0;
string s1, s2;
int v[N];
map<char, vector<char>> a;
void dfs(char x, char y){
	if (x == y){
		flag = 1;
		return;
	}
	v[int(x)] = 1;
	if (x == char(0)) return;
	for (int i = 0; i < a[x].size(); i++)
		if (!v[int(a[x][i])])
			dfs(a[x][i], y);
}
int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		char b, c;
		cin >> b >> c;
		a[b].push_back(c);
	}
	while (m--){
		cin >> s1 >> s2;
		if (s1.size() != s2.size()){
			cout << "no" << endl;
			continue;
		}
		bool k = 0;
		for (int i = 0; i < s1.size(); i++)
			if (s1[i] != s2[i]){
				dfs(s1[i], s2[i]);
				if (!flag) k = 1;
				flag = 0;
				memset(v, 0, sizeof v);
			}
		if (!k) cout << "yes";
		else cout << "no";
		puts("");
	}
	return 0;
}
```

---

## 作者：ljh789789 (赞：4)

# P6937题解

## 题目分析

### [题目传送门](https://www.luogu.com.cn/problem/P6937)

P6937 [ICPC2017 WF] Secret Chamber at Mount Rushmore：
### 题目大意

一共有 $m$ 种字母单项转换关系，提出 $n$ 个询问：是否能给定的字符串 $s$ 转换为字符串 $t$ 。

### 数据规模
 $1 \le m \le 500，1 \le n \le 50$ ，输入的字符及字符串均由小写字母组成

## 思路讲解

在讲解思路之前，我们得先了解几个图论知识：1.如果节点 $i$ 与节点 $k$ 连接,节点 $k$ 与节点 $j$ 连接，那么节点 $i$ 就与节点 $j$ 连接； 2.节点 $i$ 肯定是能连向自己的。

众所周知，弗洛伊德 $floyd/floyed$ 是一种时效很差却写法简单的一种算法（时间复杂度 $O( n \times n \times n )$ / $O(n^3)$ ) ，其思路如下：

- **先枚举一个支点/连接点 $k$ ， $1 \le k \le n$ ，这里很重要，初学者很容易写错;**
- 再枚举两个待连接或已连接的两个节点 $i$ ，$j$ ， $1 \le i \le n,1 \le j \le n$ ;
- 判断（根据题目而定），针对这一题来说，定义 $bool$ 类型二维数组 $f[i][j]$ 表示节点 $i$ 是否能与节点 $j$ 转换，枚举 $k$ ，$i$ ，$j$ ，判断 $f[i][k]$ , $f[k][j]$ 的值是否为真值1（是否可以转换），把 $f[i][j]$修改为真值1即可。过程中，还需要特殊判断 $i=j$ 的情况，这一道题就可以AC了。

具体代码如下：

```cpp
for(int k=1;k<=26;k++)
for(int i=1;i<=26;i++)
for(int j=1;j<=26;j++){
	if(i==j)f[i][j]=1;
	if(f[i][k]&&f[k][j])f[i][j]=1;
}
```


划重点：这一道题的数据范围很小，$n \times n \times n=26 \times 26 \times 26=17,576$ ,所以用 $floyd$ 是肯定不会超时TLE的，

## 代码

注释代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=550;
int m,n;
bool f[maxn][maxn];//标记两个节点是否可以交换 
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}//快读，当然，cin和scanf也行 
char read_char(){
	char ch=getchar();
	while(!islower(ch))ch=getchar();//islower是STL模版里的，作用是判断是否是小写字母 
	return ch;
}//字符读入要strong一点 
int main(){
	m=read(),n=read();//scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++){
		char a=read_char(),b=read_char();//strong 
		f[a-'a'+1][b-'a'+1]=1;//记录 
	}
	for(int k=1;k<=26;k++)//k一定要写在最外层 
	for(int i=1;i<=26;i++)
	for(int j=1;j<=26;j++){
		if(i==j)f[i][j]=1;//自己肯定能和自己交换 
		if(f[i][k]&&f[k][j])f[i][j]=1;
	}//重点：Floyd 
	for(int i=1;i<=n;i++){
		string s1,s2;
		bool flg=0;//开关flag 
		cin>>s1>>s2;
		if(s1.size()!=s2.size()){printf("no\n");continue;}//长度不同，肯定不行 
		for(int i=0;i<s1.size();i++)//逐位判断 
			if(!f[s1[i]-'a'+1][s2[i]-'a'+1]){flg=1;break;}
		if(flg)printf("no\n");
		else printf("yes\n");
	}
	return 0;//世界的毁灭 
} 
```
高清无注释版：~~方便大家复制~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=550;
int m,n;
bool f[maxn][maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}
char read_char(){
	char ch=getchar();
	while(!islower(ch))ch=getchar();
	return ch;
}
int main(){
	m=read(),n=read();
	for(int i=1;i<=m;i++){
		char a=read_char(),b=read_char();
		f[a-'a'+1][b-'a'+1]=1;
	}
	for(int k=1;k<=26;k++)
	for(int i=1;i<=26;i++)
	for(int j=1;j<=26;j++){
		if(i==j)f[i][j]=1;
		if(f[i][k]&&f[k][j])f[i][j]=1;
	}
	for(int i=1;i<=n;i++){
		string s1,s2;
		bool flg=0;
		cin>>s1>>s2;
		if(s1.size()!=s2.size()){printf("no\n");continue;}
		for(int i=0;i<s1.size();i++)
			if(!f[s1[i]-'a'+1][s2[i]-'a'+1]){flg=1;break;}
		if(flg)printf("no\n");
		else printf("yes\n");
	}
	return 0;
} 
```

---

## 作者：yueyan_WZF (赞：2)

做这道题时肯定会读到“单向”“小写字母 a 转化为小写字母 b”这些吧，是不是有点熟悉，如果还没想起来，就看看[这道题](https://www.luogu.com.cn/problem/B3611)。

唉？是不是很相似？没错，这道题就是把传递闭包里的节点换成了字母。

于是，我们就该请来这道题的重要嘉宾——弗洛伊德。

（来看它的[例题](https://www.luogu.com.cn/problem/B3647)）

知道了思路，代码实现起来就不难了。

### AC code

```
#include<bits/stdc++.h>
using namespace std;
int m,n;
int f[550][550];
void floyd(){ //简单的floyd 
	for(int k=1;k<=26;k++){
		for(int i=1;i<=26;i++){
			for(int j=1;j<=26;j++){
				if(i==j){ //自己肯定能变成自己 
					f[i][j]=1;
				}
				if(f[i][k]==1&&f[k][j]==1){
					f[i][j]=1;
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&m,&n);
	while(m--){
		char a,b;
		cin>>a>>b;
		f[a-'a'+1][b-'a'+1]=1; //直接转换 
	}
	floyd();
	while(n--){
		string a,b;
		cin>>a>>b;
		int p=0;
		if(a.size()!=b.size()){ //特判一下，如果这两个字符串连字符数量都不一样 ，那肯定不能。 
			printf("no\n");
			continue;
		}
		else{
			for(int i=0,j=0;i<a.size();i++,j++){
				if(f[a[i]-'a'+1][b[j]-'a'+1]!=1){
					printf("no\n");
					p=1;
					break;
				}
			}
			if(p==0){ //判断ta还纯不纯洁。 
				printf("yes\n");
			}
		}
	}
} 
```

码风不太好，请见谅。

---

## 作者：lyas145 (赞：2)

题目在[这里](https://www.luogu.com.cn/problem/P6937)。

## 解题思路
首先研究一下样例，先看看 $c$ 是怎么变的吧。  
```
c --> t --> e
      |---> f
```
从上图可以看出 $c$ 能变成 $t$、$e$、$f$，我们肯定是想用个方法能直接判断 $c$ 能否变成其他字母。这种变化关系很像一个有向图，并且只有 $26$ 个字母，范围也很小……

**Floyd！**

于是我们可以用 Floyd 把上图的变化关系变成下图这样。  
```
c -+--> t
   |--> e
   +--> f
```
所以我们可以先把这些字母的变化关系搞成一个图，然后跑 Floyd。对于每个字符串 $t$，挨个判断它的每一个字符是否符合条件。

然后就没了，代码里也有些注释。

## 码儿
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=55;
int n,q;
int z[26][26];
char a[N],b[N];
void Floyd() {     //这是 Floyd 代码。
	for (int k=0;k<26;k++) {
		for (int i=0;i<26;i++) {
			for (int j=0;j<26;j++) {
				z[i][j]=min(z[i][j],z[i][k]+z[k][j]);
			}
		}
	}
}
int main() {
	scanf("%d%d",&n,&q);
	memset(z,0x3f,sizeof z);
	for (int i=1;i<=n;i++) {
		char x[2],y[2];
		scanf("%s%s",x,y);
		z[x[0]-'a'][y[0]-'a']=0;//建边（单向）
//为啥边权是 0？因为这样的话，就能保证如果一个字母能变成另一个字母，那么它们之间的边的权值一定是 0。
	}
	for (int i=0;i<26;i++) {z[i][i]=0;}
//可以不变成其他字母，做好自己。
	Floyd();
	while (q--) {
		scanf("%s%s",a,b);
		int la,lb;
		la=strlen(a);
		lb=strlen(b);
		if (la!=lb) {puts("no");continue;}
//如过长度都不相等，那么字符串 s 一定变不成字符串 t。
		for (int i=0;i<la;i++) {
			if (z[a[i]-'a'][b[i]-'a']) {puts("no");goto A;}
//如果边权不是 0，那么就变不成了。
		}
		puts("yes");
		A:;
	}
	return 0;
}
```  
感谢观看！

---

## 作者：Pollococido (赞：1)

### 题目大意

[自己看](https://www.luogu.com.cn/problem/P6937)。

### 思路

读题，注意关键句**每一种转换关系表示为，可以从小写字母 $a$ 转化为小写字母 $b$，转换关系单向且不重复**。我们用单向的箭头表示 $a$ 可以转换到 $b$，既然这样，一堆这样的东西不就是一张有向图吗？详见下图

![](https://cdn.luogu.com.cn/upload/image_hosting/a179q2cp.png)我们只要遍历两个字符串，若有不相等的字符，只要 dfs 搜索第一个字符是否直接或间接连接到第二个字符就可以了。

### 代码

```cpp
/*
	@Date: 2024/11/30 10:43:36
	@Author: Genius(I'm a fool)
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define maxn 2000010
#define mod 10000000007
#define pair pair<int, int>
#define make make_pair
int n, m;
char x, y;
string s1, s2;
vector<char> g[510];  // 存图
map<char, bool> Mp;	  // 记录每个字符是否出现
bool flg;

inline long long read() {
	long long x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

void write(long long x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
	return;
}
void dfs(char f, char t) {
	if (f == t) {
		flg = true;
		return;
	}  // 如果转换到了就是 true
	Mp[f] = true;		   // 当前字符无法在转换(转换了也没用)
	for (auto c : g[f]) {  // 遍历每一个能连到的字符
		if (!Mp[c]) dfs(c, t);	// 如果能转换就转换
	}
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		g[x].push_back(y);	// 注意：单向转换，所以连单向边
	}
	while (m--) {
		cin >> s1 >> s2;
		if (s1.length() != s2.length()) {
			cout << "no" << endl;
			continue;
		}  // 长度不一定不行
		if (s1 == s2) {
			cout << "yes" << endl;
			continue;
		}  // 完全相等一定行
		int length = s1.length();
		bool can = true;  // 默认是可以的
		for (int i = 0; i < length; i++) {
			if (s1[i] != s2[i]) {
				dfs(s1[i], s2[i]);
				if (!flg) can = false;	// 任何一位不行就是不行
				flg = false;
				Mp.clear();
				// 复原，为了下一次搜索
			}
		}
		cout << (can ? "yes" : "no") << endl;
	}
	return 0;
}
```

---

## 作者：chl090410 (赞：1)

## The Solution to P6937 [ICPC2017 WF] Secret Chamber at Mount Rushmore

### 题目大意

一共有 $m$ 种字母的转换关系，每一种转换关系表示为，可以从小写字母 $a$ 转化为小写字母 $b$，转换关系单向且不重复。现在给定 $n$ 组询问，每一组询问字符串 s 是否能通过转换关系变为 $t$。

### 分析

我们可以把每个字母看成一个点，而字母间的转换关系可以看成两个点间的一条有向边，因为字母只有 $26$ 个，所以我们可以使用 [Floyd](https://oi-wiki.org/graph/shortest-path/) 算法求出任意两点间是否连通。

对于每个询问，我们分以下两种情况讨论。

- 两个字符串长度不相等，此时无论怎样转换，都无法使两个字符串相等。所以直接输出 ```no```。

- 两个字符串长度相等，此时依次遍历两个字符串的每一位，判断第一个字符串的每一位是否与第二个字符串的对应位置的字符连通。若有任何一位不连通，就输出 ```no```，否则输出 ```yes```。

### 下面附上完整代码:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int d[55][55],n,m,t;
char c,c1;
string s,s1;
signed main(){
	cin>>m>>n;
	for(int i=1;i<=30;i++){
		for(int j=1;j<=30;j++){
			d[i][j]=21474836;
		}
	}
	for(int i=1;i<=30;i++){
		d[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		cin>>c>>c1;
		d[c-'a'+1][c1-'a'+1]=1;
	}
	for(int k=1;k<=30;k++){
		for(int i=1;i<=30;i++){
			for(int j=1;j<=30;j++){
				if(d[i][j]>d[i][k]+d[k][j] && i!=j && j!=k){
					d[i][j]=d[i][k]+d[k][j];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		cin>>s>>s1;
		if(s.length()!=s1.length()){
			cout<<"no"<<endl;
			continue;
		}else{
			int len=s.length();
			for(int j=0;j<s.length();j++){
				if(d[s[j]-'a'+1][s1[j]-'a'+1]==21474836){
					cout<<"no"<<endl;
					t=1;break;
				}
			}
			if(t!=1)	cout<<"yes"<<endl;
			t=0;
		}
	}
	return 0;
}


---

## 作者：char_phi (赞：1)

~~[宣传博客](https://www.cnblogs.com/charphi/p/16753460.html)~~

简要题意：告诉你可以从哪些字符转化为哪些字符，然后再问你某一个字符串能否转化为另一个字符串。

这里提供两种做法：爆搜和传递闭包。

# 算法一 爆搜

刚开始看到数据范围第一个念头就是爆搜，于是五分钟打完过了样例就交了。

然后就 $\text{RE}$ 爆系统栈了。

仔细想了一下，应该是出现了环导致死递归了，就比如这种情况：

```
a -> b
b -> c
c -> a
```

他们三个形成了一个环，然后就会在这个环里无限递归，所以这样就会 $\text{RE}$。

要解决也不难，直接开一个 $\text{vis}$ 数组标识当前点是否访问过，然后访问到某个点时就标记为 $\text{true}$，这样就不会在环里死递归了。

然后记得每次递归之前都要 $\text{memset}$ 一遍。

代码：

```cpp
#include <iostream>
#include <map>
#include <cstring>
#define GMY (520&1314)
#define FBI_OPENTHEDOOR(x, y) freopen(#x ".in", "r", stdin), freopen(#y ".out", "w", stdout);
#define re register int
#define char_phi signed
#define N 35
#define M 505
#define LENGTH 55
using namespace std;
inline void Fastio_setup(){ios::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);}

/*
	
*/

int m, Q, star_cnt, lena, lenb;
char vis[N];
char st[LENGTH], ed[LENGTH];
int head[N];

struct star{int v, nxt;};

struct star e[M<<1];

map<char, int> mp;

inline void star_add(int u, int v){e[++ star_cnt].v=v, e[star_cnt].nxt=head[u], head[u]=star_cnt;}

char dfs(int x, int faer, int target){
	vis[x] = true;
	if (x == target)
		return true;
	for (re i = head[x] ; i ; i = e[i].nxt){
		int v = e[i].v;
		if (v == faer or vis[v] == true)
			continue;
		if (dfs(v, x, target) == true)
			return true;
	}
	return false;
}

inline void work(){
	scanf("%d %d", &m, &Q);
	
	for (re i = 1 ; i <= 26 ; ++ i)
		mp['a'+i-1] = i;
	
	char uu, space, vv, enter; uu = getchar();
	for (re i = 1 ; i <= m ; ++ i){
		uu = getchar(), space = getchar(), vv = getchar(), enter = getchar();
		star_add(mp[uu], mp[vv]);
	}
	
	while (Q --){
		scanf("%s %s", st+1, ed+1);
		lena = strlen(st+1), lenb = strlen(ed+1);
		
		if (lena != lenb)
			{cout << "no" << '\n'; continue;}
		
		for (re i = 1 ; i <= lena ; ++ i){
			memset(vis, false, sizeof(vis)); vis[mp[st[i]]] = true;
			if (dfs(mp[st[i]], 0, mp[ed[i]]) == false)
				{cout << "no" << '\n'; goto Continuer;}
		}
		
		cout << "yes" << '\n';
		
		Continuer:{}
	}
}
// #define IXINGMY
char_phi main(){
	#ifdef IXINGMY
		FBI_OPENTHEDOOR(a, a);
	#endif
	// Fastio_setup();
	work();
	return GMY;
}
```

# 算法二 传递闭包

因为字母只有 $26$ 个，我们开数组不会太大，所以每次 $\text{memset}$ 所耗时间几乎可以不计。但是当这题的**数据范围更大**时，对于每个询问都搜一遍的时间复杂度是 $O(Qm)$ 的，那么就会 $\text{T}$ 掉。

那么我们可以预处理出每个点之间的关系，然后 $O(1)$ 回答询问。

考虑使用传递闭包。传递闭包和 $\text{Floyd}$ 很像，也是枚举中间转移点，通过中间转移点将“关系”转移给另一个点，时间复杂度是 $O(n^3)$ 的。

最后记得初始化 `can[i][i] = true`，一个元素从自己变成自己当然是可以的。

代码：

```cpp
#include <iostream>
#include <cctype>
#include <cstring>
#include <map>
#define GMY (520&1314)
#define FBI_OPENTHEDOOR(x, y) freopen(#x ".in", "r", stdin), freopen(#y ".out", "w", stdout);
#define re register int
#define char_phi signed
#define N 35
#define M 505
#define LENGTH 55
using namespace std;
inline void Fastio_setup(){ios::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);}

/*
	
*/

int n, m, Q, lena, lenb;
char st[LENGTH], ed[LENGTH];
char can[N][N];

map<char, int> mp;

inline void Floyd(){
	for (re k = 1 ; k <= n ; ++ k)
		for (re i = 1 ; i <= n ; ++ i)
			for (re j = 1 ; j <= n ; ++ j)
				can[i][j] |= (can[i][k] & can[k][j]);
}

inline void work(){
	cin >> m >> Q; n = 26;
	
	for (re i = 1 ; i <= 26 ; ++ i)
		mp[(char)('a'+i-1)] = i, can[i][i] = true;
	
	char uu, vv;
	for (re i = 1 ; i <= m ; ++ i){
		cin >> uu >> vv;
		can[mp[uu]][mp[vv]] = true;
	}
	
	Floyd();
	
	while (Q --){
		cin >> st+1 >> ed+1; lena = strlen(st+1), lenb = strlen(ed+1);
		
		if (lena != lenb)
			{puts("no"); goto Continuer;}
		
		for (re i = 1 ; i <= lena ; ++ i)
			if (can[mp[st[i]]][mp[ed[i]]] == false)
				{puts("no"); goto Continuer;}
		
		puts("yes");
		
		Continuer:{}
	}
}
// #define IXINGMY
char_phi main(){
	#ifdef IXINGMY
		FBI_OPENTHEDOOR(a, a);
	#endif
	Fastio_setup();
	work();
	return GMY;
}
```

---

## 作者：jsisonx (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P6937)

# 题目分析
对于这种一个字母可以变换成另一个字母的题，通常要考虑有向图。考虑构造有向图，有原字母指向变换后的字母。对于每一次比较实际上是判断两点是否存在路径。这样的问题可以用深度优先搜索，从起点开始深度遍历整个图，如果能够找到终点，那么说明两点之间存在路径，否则就不存在。

注意可能会出现环，所以每次搜索到一个点时要判断一下它曾经是否出现过。

# AC 记录（附代码）

[AC 记录](https://www.luogu.com.cn/record/161319742)

---

## 作者：Flaw_Owl (赞：0)

# P6937 [ICPC2017 WF] Secret Chamber at Mount Rushmore 题解

原题链接：[P6937 [ICPC2017 WF] Secret Chamber at Mount Rushmore](https://www.luogu.com.cn/problem/P6937)

## 题目分析

题意比较简单易懂。字母 $a$ 向字母 $b$ 转化可以看作节点 $a$ 和节点 $b$ 之间有一条有向边（注意题目说转化不能反向），我们只需逐个对比字符串每一位的字母，如果不一致则沿着提前建好的图行动，看能否到达想要的节点。

然而这里有一个易错点：构建出来的图可能成环导致 MLE。解决办法也很简单：利用 `vis` 数组判断这条边是不是走过了。`vis[i][j]` 表示从节点 `i` 到节点 `j` 是否走过。

## AC 代码

```cpp
#include <iostream>
#include <cctype>
#include <vector>
#include <string.h>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 30;

struct edge
{
    int from, to;
    edge(int a, int b)
    {
        from = a;
        to = b;
    }
};

int n, T;
bool flag;
string s;

vector<edge> e[maxN];
bool vis[maxN][maxN];

bool dfs(int u, int v)
{
    if (e[u].empty())
        return false;
    for (edge f : e[u])
    {
        if (vis[f.from][f.to])
            continue;
        vis[f.from][f.to] = true;
        if (f.to == v)
            return true;
        if (dfs(f.to, v))
            return true;
    }
    return false;
}

int main()
{
    n = read();
    T = read();
    while (n--)
    {
        char ch1, ch2;
        cin >> ch1 >> ch2;
        e[ch1 - 'a'].push_back(edge(ch1 - 'a', ch2 - 'a'));
    }
    while (T--)
    {

        string s1, s2;
        cin >> s1 >> s2;
        if (s1.size() != s2.size())
        {
            printf("no\n");
            continue;
        }
        flag = false;
        for (int i = 0; i < s1.size(); i++)
            if (s1[i] != s2[i])
            {
                memset(vis, false, sizeof(vis));
                if (!dfs(s1[i] - 'a', s2[i] - 'a'))
                {
                    flag = true;
                    break;
                }
            }

        if (flag)
        {
            printf("no\n");
            continue;
        }
        printf("yes\n");
    }
}
```

---

## 作者：StarsIntoSea_SY (赞：0)

# Solution

不难发现，我们需要提前求出每一对字母之间能否从一个字母变为另一个字母，而在访问时字母都是随机的，考虑使用传递闭包（Floyd）来判断是否能变化，因为传递闭包是多元的。

在对每一位访问的字符串逐一访问是否连通，一旦出现不连通的情况就直接跳出，否则就是满足的。

特别的，如果访问的两个字符串长度不相等就一定不满足。

# Code

```cpp
#include <iostream>
#include <string.h>
using namespace std;
int f[30][30];
int n,m;
int gum(char a){return a-'a'+1;}

void init(){
	cin>>n>>m;
	while(n--){
		char a,b;
		cin>>a>>b;
		f[gum(a)][gum(b)]=1;
	}
}

void Floyd(){
	for(int i=1;i<=26;++i)
		f[i][i]=1;
	for(int t=1;t<=26;++t)
	    for(int i=1;i<=26;++i)
			for(int j=1;j<=26;++j)
				if(f[i][t]&f[t][j])
					f[i][j]=1;
}

void solve(){
	string s1,s2;
	cin>>s1>>s2;
	int l1=s1.size(),l2=s2.size();
	if(l1!=l2){
		printf("no\n"); return;
	}
	for(int i=0;i<l1;++i){
		if(!f[gum(s1[i])][gum(s2[i])]){
			printf("no\n");
			return ;
		}
	}
	printf("yes\n");
}

int main(){
	ios::sync_with_stdio(false);
	init();
	Floyd();
	while(m--) solve();
}
```

---

## 作者：Biuld (赞：0)

一道大水题

## 题意：
给你 $m$ 个 转换关系，输入两个**小写字母** $a$、$b$，代表字母 $a$ 可以转换成字母 $b$。再给出 $n$ 个询问，输入两个字符串 $s$、$t$
(注意：$s$ 和 $t$ 的长度可能**不一样**)，查询字符串 $s$ 是否可以转换成字符串 $t$。
## 分析题目:
明显，字母之间的转换是单向的，我们可以把字母之间的转换关系连成图。如 $c$ 可以转换成 $t$, 那就从 $c$ 往 $t$ 连一条**单向边**。然后我们可以通过搜索这张**单向有环图**来得出某个字母是否能转为另一个字母。因为小写字母一共就 $26$ 个，时间与空间复杂度都不会太大。
## 代码处理：
如何来显示字母之间的能否转换的关系呢，我们可以建一个二维 bool 数组，就像我代码中的 $b[30][30]$。如果 $b[x][y]$ 的值是 $1$, 说明字母 $x$ 可以转成 $y$。

如果搜到环怎么判断呢，我们可以把 $b$ 数组全设为 $0$， 如果搜到 ```b[x][y] == 0```，就更改为 $1$，表示可以从 $x$ 转为 $y$；但如果 ```b[x][y] == 1``` 呢，就说明这种情况已经搜到过了，跳出循环即可。
## 代码：
```cpp
// 码风奇怪，凑合着看
#include<bits/stdc++.h>
using namespace std;
const int N = 5e2 + 5;
const int M = 55;

int m, n;

int head[30], tot; //最多26个点，保险开到了30
struct node{
	int to, nxt;
}e[N]; //最多 N 条边
inline void add(int x, int y){ //建图
	e[++ tot].to = y;
	e[tot].nxt = head[x];
	head[x] = tot;
}

bool b[30][30];
inline void Dfs(int now, int s){ //搜索
	for(int i = head[now]; i; i = e[i].nxt){
		int v = e[i].to;
		if(!b[s][v]){ //只有当这个点没被搜过时才继续后面的操作
			b[s][v] = 1;
			Dfs(v, s);
		}
	}
}
char x, y;
int main(){
	ios::sync_with_stdio(false);
	
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i){
		cin >> x >> y;
		add(x - 'a', y - 'a'); //把字母转成数字方便处理
	}
	
	for(int i = 0; i < 26; ++ i){ //每个字符都要搜
		b[i][i] = 1; //自己肯定能转换为自己
		Dfs(i, i);
	}
	
	for(int i = 1; i <= m; ++ i){
		string s, t;
		cin >> s >> t;
		
		int l = s.length();
		int k = t.length();
		bool f = 0;
		
		if(l != k){ //如果长度不相等就肯定不能转换
			cout << "no\n";
			continue;
		}
		for(int j = 0; j < l; ++ j){
			if(!b[s[j] - 'a'][t[j] - 'a']){ //相应字母之间无法转换
				cout << "no\n";
				f = 1; break;
			}
		}
		if(!f){
			cout << "yes\n";
		}
	}
	
	return 0;
}
```
感谢观看

---

## 作者：jbjbjbjb (赞：0)

这道题大意是给你 $m$ 种转换关系和 $n$ 组数据 $s$ 和 $t$，能否通过任意次转换次数将 $s$ 转换为 $t$。
这道题因为转换关系比较多，所以要预处理每个小写字母到底能转换哪些小写字母，因为 $m$ 较小，所以可以使用 Floyd 预处理。
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[35][35];
string x,y;
int main()
{
	int n,m;
	char a,b;
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		f[a-'a'][b-'a']=1;
	}
	for(int i=0;i<=25;i++)f[i][i]=1;//每个字母可以不转换。
	for(int i=0;i<=25;i++){
		for(int j=0;j<=25;j++){
			for(int z=0;z<=25;z++){
				f[j][z]|=f[j][i]&f[i][z];//判断两个字母之间是否可以转换。
			}
		}
	}
	while(m--){
		cin>>x>>y;
		if(x.size()!=y.size()){//长度不一样直接输出no。
			printf("no\n");
			continue;
		}
		int u=0;
		for(int i=0;x[i]!='\0';i++){
			if(!f[x[i]-'a'][y[i]-'a']){//如果有不可以转换的，记录并退出循环。
				u=1;
				break;
			}
		}
		if(u)printf("no\n");
		else printf("yes\n");
	}
	return 0;
}

```

---

