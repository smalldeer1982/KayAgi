# [NEERC 2016] Hard Refactoring

## 题目描述

对于一个变量 $x$，给出一些约束条件，形如 $x \geq a$，$x \le a$ 
这些约束条件之间用```||```连接，然后你需要将这些约束条件简化，最后输出简化后的约束条件。

## 说明/提示

对于所有在这一题中出现的数字（包括 $x$），都$\ge -32768$（$-2^{15}$） 且 $\le 32767 $（$2^{15}-1$）。

## 样例 #1

### 输入

```
x >= 5 && x <= 10 ||
x >= 7 && x <= 20 ||
x <= 2 ||
x >= 21 && x <= 25 ||
x >= 8 && x <= 10 ||
x >= 100```

### 输出

```
x <= 2 ||
x >= 5 && x <= 25 ||
x >= 100```

# 题解

## 作者：peixiaorui (赞：7)

## 题意
题目要我们求一个不等式组的解集，并以最简洁的方式输出。我们可以抽象成有多个区间，题目要我们合并区间，若这些区间覆盖了 $[-2^{15},2^{15}-1]$ 则输出 `true` ，若这些区间的左端点全部都大于右端点（即 $a \le x \le b,a > b$，此情况无解），则输出 `false`。
## 思路
处理出每一个约束条件所代表的区间的左端点和右端点，如果一行只有一个约束条件，那么就将缺少的那个端点设为 $-2^{15}$ 或 $2^{15}-1$（举例：`x <= 2` 转化为左端点为 $-2^{15}$，右端点为 $2$ 的区间）。
处理出所有区间后进行排序，然后合并相交的区间（要注意因为是整数，所以 $[x,y]$ 与 $[y+1,z]$ 可以合并）。
最后把合并完的区间全部输出即可。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define of(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
const int inf=1<<15;
struct node{
	int le,ri;
};
bool cmp(node a,node b){return a.le<b.le;}
vector<node> res,ans;
int main(){
	int wrong_cnt=0;//记录有多少个左端点大于右端点的区间
	while(1){
		string xxx,op;int num;
		cin>>xxx>>op>>num;
		int le=-inf,ri=inf-1;
		if(op=="<=")ri=num;
		else le=num;//记录第一个端点
		if(!(cin>>xxx)){res.push_back({le,ri});break;}
		if(xxx=="&&"){
			cin>>xxx>>op>>num;
			ri=num;//题目保证第二个条件一定是右端点
			if(le>ri)wrong_cnt++;
			if(!(cin>>xxx)){res.push_back({le,ri});break;}
		}
		res.push_back({le,ri});//记录区间
	}
	if(wrong_cnt==res.size()){cout<<"false";return 0;}//如果所有区间都是非法的，输出false
	sort(res.begin(),res.end(),cmp);
	int le=res[0].le,ri=res[0].ri;
	fo(i,1,res.size()-1){
		if(res[i].le>res[i].ri)continue;
		if(res[i].le>ri+1){
			ans.push_back({le,ri});
			le=res[i].le,ri=res[i].ri;
			continue;
		}
		ri=max(ri,res[i].ri);
	}
	ans.push_back({le,ri});//排序并合并区间
	if(ans[0].le==-inf&&ans[0].ri==inf-1){cout<<"true";return 0;}//如果区间覆盖了[-32768,32767]输出false
	fo(i,0,ans.size()-1){
		if(ans[i].ri==inf-1)cout<<"x >= "<<ans[i].le;
		else if(ans[i].le==-inf)cout<<"x <= "<<ans[i].ri;
		else cout<<"x >= "<<ans[i].le<<" && x <= "<<ans[i].ri;
		if(i!=ans.size()-1)cout<<" ||";
		cout<<endl;
	}//输出
	return 0;
}
```


---

## 作者：RBI_GL (赞：4)



### 思路：

简单模拟，数字区间为 $[2^{15},2^{15}]$，全取为 ```true``` ，全不取为 ```false``` 。否则按最简表达式给出范围。

对于输入给的表达式，读取其表示的区间 $[l, r]$ ，若 $l <= r$ ，则将其在一维数轴上 $[l, r]$ 每个数 $+1$ 。

对结果判断，$[2^{15},2^{15}]$
区间的每个数字判断其是否能够取到，并合并区间，打印若干段不连续区间即可。

对于如何快速对区间修改及单点查询，通过树状数组即可。


注意处理好输入输出格式问题。

-------


### Code：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int BASE = 32769;
const int N = 70005;
int bin[N];
inline int lowbit(int x) {
	return x & -x;
}
void add(int x, int w) {
	for(int i=x; i<N; i+=lowbit(i)) bin[i] += w;
}
int sum(int x) {
	int ret = 0;
	for(int i=x; i; i-=lowbit(i)) ret += bin[i];
	return ret;
}
void update(int x, int y, int w) {
	add(x, w),add(y+1, -w);
}
int main() {

	char x[2], op[5], eop0, eop1;
	int lmt, lft, rgt;
	while(true) {
		lft = -32768,rgt = 32767;
		scanf(" %s %s %d", x, op, &lmt);
		if(op[0] == '<') rgt = lmt;
		else lft = lmt;
		if(cin>>eop0>>eop1) {
			if(eop0 == '&') {
				scanf(" %c %s %d", &x, op, &lmt);
				if(op[0] == '<') rgt = min(lmt, rgt);
				else lft = max(lft, lmt);
			}
			if(lft <= rgt) update(lft + BASE, rgt + BASE, 1);
			if(eop0 == '&') {
				if(cin>>eop0>>eop1);
				else break;
			}
		} else {
			if(lft <= rgt) update(lft + BASE, rgt + BASE, 1);
			break;
		}
	}
	int cnt = 0;
	lft = -BASE;
	bool flg = false;
	for(int i=1, val; i<=BASE + 32767; i++) {
		val = sum(i);
		cnt += (val > 0 ? 1 : 0);
		if(lft == -BASE && val) lft = i-BASE;
		if(lft != -BASE && val == 0) {
			if(flg) printf(" ||\n");
			if(lft == 1-BASE) printf("x <= %d", i-BASE-1);
			else printf("x >= %d && x <= %d", lft, i-BASE-1);
			lft = -BASE;
			flg = true;
		}
	}
	if(cnt == 0) printf("false\n");
	else if(cnt == 32768*2) printf("true\n");
	else if(lft != -BASE) {
		if(flg) printf(" ||\n");
		printf("x >= %d", lft);
	}
	return 0;
}
```

---

## 作者：Flaw_Owl (赞：2)

# P6123 [NEERC2016] Hard Refactoring 题解

原题链接：[P6123 [NEERC2016] Hard Refactoring](https://www.luogu.com.cn/problem/P6123)

## 题目分析

这是一个分析下来很简单，细节多到抓狂的题目。

类似思路：[P5568 [SDOI2008] 校门外的区间](https://www.luogu.com.cn/problem/P5568)。该题的区间操作和细节更加复杂。但某种程度上可以作为本题的升级版。

数轴上的区间操作考虑使用**线段树**进行无脑解决。只需将区间范围内全部置 $1$，在最后扫一边区间，找到一段连续的为 $1$ 的区间并输出即可。

下面分部分地给出代码和分析。

### 负数的处理

题目中的数据范围为 $-2^{15} \leq x \leq 2^{15} - 1$。为了处理负数范围内的问题，我们将数据整体**向右移动 $2^{15}+1$**，使得最小值置于 $1$ 上。

在程序实现中表现为创建一个**数据补正**。

```cpp
const int cor = (1 << 15) + 1; // 作为数据补正，整体向右移动 cor
```

### 线段树板子

线段树中没有什么额外的操作，此处 lazy-tag 为将区间内全部置 $1$，具体可以看代码实现。

```cpp
#define ll long long

const int maxN = 2 * cor + 5;  // 为了防止超数组引用范围，适当扩大数组

ll tree[maxN << 2];
ll tag[maxN << 2];
ll ans[maxN << 2]; // 最终答案的区间
ll ls(ll p) { return p << 1; }
ll rs(ll p) { return p << 1 | 1; }

void push_up(ll p)
{
    tree[p] = tree[ls(p)] + tree[rs(p)];
}

void build(ll p, ll pl, ll pr)
{
    tag[p] = 0;
    if (pl == pr)
        return;
    ll mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addTag(ll p, ll pl, ll pr)
{
    tag[p] = 1;
    tree[p] = pr - pl + 1;
}

void push_down(ll p, ll pl, ll pr)
{
    if (tag[p])
    {
        ll mid = (pl + pr) >> 1;
        addTag(ls(p), pl, mid);
        addTag(rs(p), mid + 1, pr);
        tag[p] = 0;
    }
}

void update(ll L, ll R, ll p, ll pl, ll pr)
{
    if (L <= pl && R >= pr)
    {
        addTag(p, pl, pr);
        return;
    }
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if (L <= mid)
        update(L, R, ls(p), pl, mid);
    if (R > mid)
        update(L, R, rs(p), mid + 1, pr);
    push_up(p);
}

void query(ll L, ll R, ll p, ll pl, ll pr)
{
    push_down(p, pl, pr);
    push_up(p);
    if (pr - pl + 1 == tree[p])
    {
        for (int i = pl; i <= pr; i++)
            ans[i] = 1;
        return;
    }
    if (pl == pr)
        return;
    ll mid = (pl + pr) >> 1;
    if (L <= mid)
        query(L, R, ls(p), pl, mid);
    if (R > mid)
        query(L, R, rs(p), mid + 1, pr);
}
```

### 题目的输入

题目的输入非常复杂，因为它存在三种情况：

1. 单个约束条件 + `||`
2. 两个约束条件 + `||`
3. 作为结束的条件，后面没有 `||`

其中，两个约束条件是包含单个约束条件的情况下中间用 `&&` 连接。

读入整体是一个循环，直到结束才退出循环。

首先处理第三种情况，如何判断它最后“没有 `||`”？其实就是看是否没有读入了。我们用 `temp` 指代一个字符串。可以这么判断：

```cpp
if(!(cin >> temp))
    break;
```

此时如果条件没有结束，又有几种情况。

- 如果 `temp == "||"`，就代表一种情况的结束，直接跳过即可。

```cpp
if (temp == "||")
    continue;
```

- 反之，就代表此刻正在读入一种情况。下面就要判断是单条件还是双条件。但首先，我们上面提到过**单条件和双条件前半段是一样的**，我们可以先进行读入。

```cpp
cin >> ch >> x;
x += cor;
```

其中，`ch` 代表读入的符号，`x` 是当前的数字（也代表可能的左端点，因为现在不知道是单条件还是双条件所以说是“可能的”）。并且要记得加上补正。

观察样例，我们发现：如果接下来再读入一个字符串是 `||`（代表情况结束）或者没有任何读入（代表读入结束），都可以说明这是一个单条件的情况。

```cpp
if (!(cin >> temp) || temp == "||")
    {
        if (ch == "<=")
            update(1, x, 1, 1, N);
        else if (ch == ">=")
            update(x, N, 1, 1, N);
    }
```

如果是 `&&`，就代表这是一个双条件情况，我们还要再进行一次读入：

```cpp
if (temp == "&&")
    {
        cin >> temp >> ch >> y;
        y += cor;
        update(x, y, 1, 1, N);
    }
```

### 题目的输出

这里的输出，我们遍历整个 `ans` 数组，找到一段连续为 $1$ 的序列，并按照题目的格式输出其左右端点。

但是这边又有一个问题：我们最后一个条件是不需要输出 `||` 的，而其他都需要。

~~将思维逆转过来！~~ 我们与其将 `||` 看作一次输出之后的内容，不如看成**一次输出之前的内容**，也就是说：**只有第一次输出不需要输出 `||`**，其他时候都要，这样就好输出了。

同时也要注意，题目不允许输出任何额外的空格和换行。以及，还有两种特殊的输出情况：全都是 $1$ 或者全部是 $0$。

## 参考代码

截止到目前，我们终于完成了这道细节满满的题。下面给出参考代码。

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

const int cor = (1 << 15) + 1; // 作为数据补正，整体向右移动 cor
const int maxN = 2 * cor + 5;  // 为了防止超数组引用范围，适当扩大数组
const int N = 2 * (1 << 15);   // 实际的区间长度

ll tree[maxN << 2];
ll tag[maxN << 2];
ll ans[maxN << 2]; // 最终答案的区间
ll ls(ll p) { return p << 1; }
ll rs(ll p) { return p << 1 | 1; }

void push_up(ll p)
{
    tree[p] = tree[ls(p)] + tree[rs(p)];
}

void build(ll p, ll pl, ll pr)
{
    tag[p] = 0;
    if (pl == pr)
        return;
    ll mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addTag(ll p, ll pl, ll pr)
{
    tag[p] = 1;
    tree[p] = pr - pl + 1;
}

void push_down(ll p, ll pl, ll pr)
{
    if (tag[p])
    {
        ll mid = (pl + pr) >> 1;
        addTag(ls(p), pl, mid);
        addTag(rs(p), mid + 1, pr);
        tag[p] = 0;
    }
}

void update(ll L, ll R, ll p, ll pl, ll pr)
{
    if (L <= pl && R >= pr)
    {
        addTag(p, pl, pr);
        return;
    }
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if (L <= mid)
        update(L, R, ls(p), pl, mid);
    if (R > mid)
        update(L, R, rs(p), mid + 1, pr);
    push_up(p);
}

void query(ll L, ll R, ll p, ll pl, ll pr)
{
    push_down(p, pl, pr);
    push_up(p);
    if (pr - pl + 1 == tree[p])
    {
        for (int i = pl; i <= pr; i++)
            ans[i] = 1;
        return;
    }
    if (pl == pr)
        return;
    ll mid = (pl + pr) >> 1;
    if (L <= mid)
        query(L, R, ls(p), pl, mid);
    if (R > mid)
        query(L, R, rs(p), mid + 1, pr);
}

string temp, ch;
int x, y;

int main()
{
    build(1, 1, N);
    while (true)
    {
        if (!(cin >> temp))
            break;
        if (temp == "||")
            continue;
        cin >> ch >> x;
        x += cor;
        if (!(cin >> temp) || temp == "||")
        {
            if (ch == "<=")
                update(1, x, 1, 1, N);
            else if (ch == ">=")
                update(x, N, 1, 1, N);
        }
        if (temp == "&&")
        {
            cin >> temp >> ch >> y;
            y += cor;
            update(x, y, 1, 1, N);
        }
    }
    query(1, N, 1, 1, N);
    bool check = true;
    bool spe = true;
    for (int i = 1; i <= N; i++)
    {
        int x, y;
        if (ans[i])
        {
            check = false;
            x = y = i;
            while (ans[y] && y < N)
                y++;
            if (spe)
                spe = false;
            else
                printf(" ||\n");
            if (x == 1 && y != N)
                printf("x <= %d", y - cor - 1);
            else if (x != 1 && y == N)
                printf("x >= %d", x - cor);
            else if (x == 1 && y == N)
                printf("true");
            else
                printf("x >= %d && x <= %d", x - cor, y - cor - 1);
            i = y;
        }
    }
    if (check)
        printf("false\n");
    return 0;
}
```

---

## 作者：LG2458664 (赞：1)

这道题其实就是要把给出的区间合并成最简形式。

## 思路

下文中开始和结束分别指每个区间的最小值和最大值，即输入时给出的两个整数。

输入时提取每个区间的开始和结束的值，如果区间只有一个端点，由于只考虑`int` 的情况，所以用这两个数补全。

可以用贪心的思想求解：将所有给出的区间按开始的值从小到大排序，记录连续区间的开始和结束，遍历所有区间，如果遇到可以与前一个区间合并的，则更新结尾；否则用当前区间重置开始和结束。如一个区间涵盖所有数字则输出 `true`，如没有合法的区间则输出 `false`。

题目可能会给出最小值大于最大值的不合法情况，需要特判。输出时，注意省略补全的数字。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool op,ng;
char s[100];
int len,num,c,flag,bst=-32768,ben=-32768; //连续区间的最小值和最大值需要初始化为-32768 
struct exp{ //存储约束的信息 
    int st,en;
    bool operator<(exp e2)const{
        if(st!=e2.st) return st<e2.st;
        return en<e2.en;
    }
}ex[1000];
bool isdigit(char c){ //判断一个字符是否为数字 
    return (c>='0'&&c<='9');
}
void print(int st,int en,bool f){
	if(f) printf("||\n"); 
	if(st==-32768&&en==32767) printf("true ");  
	else if(st==-32768) printf("x <= %d ",en);
	else if(en==32767) printf("x >= %d ",st);
	else printf("x >= %d && x <= %d ",st,en);
}
int main(){
    while(1){
        gets(s);
        flag=op=num=0,len=strlen(s),ex[c].st=-32768,ex[c].en=32767;
        for(int i=0;i<len;i++){
            if(s[i]=='<') flag=false;
            if(s[i]=='>') flag=true;
            if(s[i]=='-') ng=true; 
            if(isdigit(s[i])) num=num*10+(s[i]-'0')*(ng?-1:1),op=true;
            if(i&&!isdigit(s[i])&&isdigit(s[i-1])){ 
                if(flag) ex[c].st=num,ng=num=0;
                else ex[c].en=num,ng=num=0;
                op=false;
            }
        }
        if(op){
            if(flag) ex[c].st=num,num=0;
            else ex[c].en=num,num=0;
        }
        c++;
        if(s[len-1]!='|') break;
    }
    sort(ex,ex+c);
    flag=op=false;
    for(int i=0;i<c;i++){
        if(i&&ben+1<ex[i].st){
            flag=false;
            if(bst<=ben){
				print(bst,ben,op);
				op=true;
			}
        }
        if(!flag){
            bst=ex[i].st,flag=true;
        }
        ben=max(ben,ex[i].en);
    }
    if(bst<=ben) print(bst,ben,op);
    else if(!op) printf("false");
    return 0;
}
`````
求互关！

---

## 作者：LLqm_rYZ (赞：1)

## 题目大意

给出若干个端点为整数的闭区间，求其交集并用最简单表示方法输出。

## 分析

题目的样例可以看出相邻两个整数如果分别为两个区间的端点，则其可以合并，即本题只考虑整数就可以，再加上数据范围只有 $2^{16}$，那么第一个蹦出来的想法就是差分，事实证明差分是可行的且比较好理解。

具体实现是在初始全为 $0$ 的数组 $a$ 上把每个区间内位置上的数都 $+1$，最后不为 $0$ 的位置就是被包含的数，体现在差分数组 $d$ 上就是把左端点 $+1$，右端点的下一个位置 $-1$，最后将 $d$ 进行前缀和得到原数组 $a$，再遍历这个数组找到每段连续不为 $0$ 的区间按照格式输出。

需要注意的问题：
+ 因为数据范围有负数所以将其整体平移 $2^{15}+1$ 从位置 $1$ 开始存储在 $d$ 中。
+ 输入时区间只有一个端点时，如果无左端点，默认为 $-2^{15}$，如果无右端点，默认为 $2^{15}-1$。
+ 输出时寻找端点前左端点默认为 $-2^{15}$，右端点默认为 $2^{15}-1$，若只找到一个端点（另一端点为默认值）则不输出另一端点，可以发现这样的区间最多两个且分别在头和尾。
+ `true` 和 `false` 的情况，在 $a$ 中进行计数，若为 $0$ 则输出 `false`，若为 $2^{16}$ 则输出 `true`。

## 代码

因符号之间有空格可以直接 `cin`，但我不想写太多判断就 `getline` 后取出数字。
```cpp
int get(int &i){	//i为'<'或'>'的下标
	i+=3;
	int res=0,f=1;
	if(str[i]=='-')f=-1,i++;
	while(isdigit(str[i])){
		res*=10;
		res+=str[i++]-'0';
	}
	return res*f;
}
```
一行行处理区间，注意特判区间为空的情况。
```cpp
while(getline(cin,str)){
	len=str.size(),lef=-INF,rig=INF-1;//默认值
	for(int i=0;i<len;i++)
		if(str[i]=='>') lef=get(i);
		else if(str[i]=='<') rig=get(i);
	if(lef>rig)continue;//如果此区间为空，则跳过
	d[lef+INF+1]++,d[rig+INF+2]--;//差分操作
}
```
在 $d$ 上前缀和得到 $a$，同时计数，之后特判 `true` 和 `false` 的情况。
```cpp
for(int i=1;i<=2*INF;i++){//直接在d上前缀和，之后得到a，同时计数
	d[i]+=d[i-1];
	if(d[i])cnt++;
}
if(!cnt) cout<<"false";//特判
else if(cnt==2*INF) cout<<"true";
```
最后找左右端点输出区间。
```cpp
lef=1,rig=INF+INF;//默认值，寻找端点
for(int i=1;i<=2*INF+1;i++){
	if(!d[i-1]&&d[i]) lef=i;//找到左端点
	if(d[i-1]&&!d[i]){//找到右端点
		rig=i-1;//当前位置为0，右端点是前一个位置
		if(ed)cout<<"||\n";//若之前有输出过，才输出"||"
		if(lef==1) cout<<"x <= "<<rig-INF-1<<" ";//无左端点时
		else cout<<"x >= "<<lef-INF-1<<" && x <= "<<rig-INF-1<<" ";
		ed=1,lef=1,rig=INF+INF;//默认值，继续寻找下一个区间
	}
}
if(lef>1&&rig==INF+INF){//有左端点且没有右端点只会发生在最后，所以在循环外判断
	if(ed)cout<<"||\n";
	cout<<"x >= "<<lef-INF-1<<" ";
}
```

### AC完整代码

[评测记录](https://www.luogu.com.cn/record/125575505)

```cpp
#include<iostream>
#include<string>

using namespace std;

const int N=(1<<17),INF=(1<<15);

string str;
int d[N];

int get(int &i){
	i+=3;
	int res=0,f=1;
	if(str[i]=='-')f=-1,i++;
	while(isdigit(str[i])){
		res*=10;
		res+=str[i++]-'0';
	}
	return res*f;
}

int main(){
	int len,lef,rig,cnt=0,ed=0;
	while(getline(cin,str)){
		len=str.size(),lef=-INF,rig=INF-1;//默认值
		for(int i=0;i<len;i++)
			if(str[i]=='>') lef=get(i);
			else if(str[i]=='<') rig=get(i);
		if(lef>rig)continue;//如果此区间为空，则跳过
		d[lef+INF+1]++,d[rig+INF+2]--;//差分操作
	}
	for(int i=1;i<=2*INF;i++){//直接在d上前缀和，之后得到a，同时计数
		d[i]+=d[i-1];
		if(d[i])cnt++;
	}
	if(!cnt) cout<<"false";//特判
	else if(cnt==2*INF) cout<<"true";
	else{
		lef=1,rig=INF+INF;//默认值，寻找端点
		for(int i=1;i<=2*INF+1;i++){
			if(!d[i-1]&&d[i]) lef=i;//找到左端点
			if(d[i-1]&&!d[i]){//找到右端点
				rig=i-1;//当前位置为0，右端点是前一个位置
				if(ed)cout<<"||\n";//若之前有输出过，才输出"||"
				if(lef==1) cout<<"x <= "<<rig-INF-1<<" ";//无左端点时
				else cout<<"x >= "<<lef-INF-1<<" && x <= "<<rig-INF-1<<" ";
				ed=1,lef=1,rig=INF+INF;//默认值，继续寻找下一个区间
			}
		}
		if(lef>1&&rig==INF+INF){//有左端点且没有右端点只会发生在最后，所以在循环外判断
			if(ed)cout<<"||\n";
			cout<<"x >= "<<lef-INF-1<<" ";
		}
	}
	cout<<endl;
	return 0;
}
```




---

## 作者：biology (赞：1)

## 题目简述

题目给出一些对 $x$ 的约束，要求以最简形式输出：$x$ 的取值在哪些范围内，可以满足至少一个限制。

这道题其实就是要把给出的区间合并成最简形式。

## 思路
下文中“开始”和“结束”分别指每个区间的最小值和最大值，即输入时给出的两个整数。

输入时提取每个区间的开始和结束的值，如果区间只有一个端点，由于只考虑 $-32768\le x \le32767$ 的情况，所以用这两个数补全。

可以用贪心的思想求解：将所有给出的区间按开始的值从小到大排序，记录连续区间的开始和结束，遍历所有区间，如果遇到可以与前一个区间合并的，则更新结尾；否则用当前区间重置开始和结束。如一个区间涵盖所有数字则输出 `true`，如没有合法的区间则输出 `false`。

题目可能会给出最小值大于最大值的不合法情况，需要特判。

输出时，注意省略补全的数字。

时间复杂度 $O(n \log n)$，瓶颈是排序的过程；空间复杂度 $O(n)$。详见代码

## 代码实现

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool op,ng;
char s[100];
int len,num,c,flag,bst=-32768,ben=-32768; //连续区间的最小值和最大值需要初始化为-32768 
struct exp{ //存储约束的信息 
    int st,en;
    bool operator<(exp e2)const{
        if(st!=e2.st) return st<e2.st;
        return en<e2.en;
    }
}ex[1000];
bool isdigit(char c){ //判断一个字符是否为数字 
    return (c>='0'&&c<='9');
}
void print(int st,int en,bool f){
	if(f) printf("||\n"); //注意换行时要打印"||" 
	if(st==-32768&&en==32767) printf("true "); //20~22行，省略补全的数字 
	else if(st==-32768) printf("x <= %d ",en);
	else if(en==32767) printf("x >= %d ",st);
	else printf("x >= %d && x <= %d ",st,en);
}
int main(){
    while(1){
        gets(s);
        flag=op=num=0,len=strlen(s),ex[c].st=-32768,ex[c].en=32767;
        for(int i=0;i<len;i++){
            if(s[i]=='<') flag=false;
            if(s[i]=='>') flag=true;
            if(s[i]=='-') ng=true; //判断是否为复数 
            if(isdigit(s[i])) num=num*10+(s[i]-'0')*(ng?-1:1),op=true;
            if(i&&!isdigit(s[i])&&isdigit(s[i-1])){ //记录信息 
                if(flag) ex[c].st=num,ng=num=0;
                else ex[c].en=num,ng=num=0;
                op=false;
            }
        }
        if(op){
            if(flag) ex[c].st=num,num=0;
            else ex[c].en=num,num=0;
        }
        c++;
        if(s[len-1]!='|') break; //判断是不是最后一行 
    }
    sort(ex,ex+c);
    flag=op=false;
    for(int i=0;i<c;i++){
        if(i&&ben+1<ex[i].st){ //无法与上一个相连 
            flag=false;
            if(bst<=ben){ //特判不合法情况 
				print(bst,ben,op);
				op=true;
			}
        }
        if(!flag){
            bst=ex[i].st,flag=true;
        }
        ben=max(ben,ex[i].en);
    }
    if(bst<=ben) print(bst,ben,op);
    else if(!op) printf("false"); //如果没有合法的区间则输出false 
    return 0;
}
```
**谢谢观看**！！如果有误，请指出。

---

## 作者：Octopus_hsfzy (赞：0)

这道题呢，数据范围挺小的，只有 $x\in[−32768,32767]$。并且，本题还要求区间修改。

所以，我们可以用**差分**解决这道题。

之后的步骤就很简单了，在输入时先判断其合法性，若合法，通过差分的方式进行一次区间修改即可。特别地，如果类似于 $x\ge a$ 或者 $x\le a$ 的合法语句，就要从边界情况 $32767$ 或 $-32768$ 开始进行区间修改操作。

若还不会差分，请先去观看[差分板题——P2367 语文成绩](https://www.luogu.com.cn/problem/solution/P2367)。

输出前，先对差分数组进行前缀和。先判断输出 true 和 false 的情况，很简单，若前缀和数组里全是非 $0$ 数，输出 true；若前缀和数组里全为 $0$，输出 false。

若为正常输出，进行以下操作：在从 $-32768$ 到 $32767$ 的区间里枚举，按照题意输出，当然，边界情况（$-32768$ 和 $32767$）需要输出时特判。

---

## 作者：heyZZZ (赞：0)

题意：

把给定的区间合并成**最简**的形式。

思路：

可以用**贪心**的思想解此题：

1. 将所有给出的区间按小值的值从小到大排序。
2. 如果一个区间可以与上一个区间合并的，合并区间。

特判：
1. 如一个区间为 $[-2^{15},2^{15}]$ 则输出 `true`。
2. 如没有合法的区间（即第一个数 $>$ 第一个数）则输出 `false`。
3. 输出时，省略补全的数字。

代码楼上楼下都已经写的很明白了，我就不赘述了。

---

## 作者：WisNourx_ (赞：0)

题目应该挺好懂的吧，就是求区间交和输出边界。

把值域抽象成数轴，每个区间被覆盖相当于做一次差分，将每一段连续的被覆盖的区间边界输出即可。

细节：

1.判 `true` 和判 `false` 要特判，还有对于只有大于或只有小于的条件也要特判。

2.值有可能为负数，要加上一个偏移量 $delta$，最后输出时再减去。

3.当出现 $x \ge l$，$x \le r$ 但是 $l >r$ 时，这种情况可以直接不用处理（无解）。

[代码](https://www.luogu.com.cn/paste/91vbking)（有点丑）

---

