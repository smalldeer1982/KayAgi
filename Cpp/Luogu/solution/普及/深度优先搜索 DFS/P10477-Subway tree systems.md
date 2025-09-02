# Subway tree systems

## 题目描述

一些主要城市的地铁系统采用树状结构，即在任何两个车站之间，只有一条且仅有一条地铁线路。此外，大多数这些城市都有一个独特的中央车站。想象一下，你是这些城市中的一名游客，你想要探索整个地铁系统。你从中央车站出发，随机选择一条地铁线路，跳上地铁列车。每当你到达一个车站，你就会选择一条你尚未乘坐过的地铁线路。如果在当前车站没有其他要探索的地铁线路了，你就会乘坐第一次到达该车站的地铁线路返回，直到最终你沿着所有的线路都行驶了两次，即每个方向都行驶了一次。在那时，你回到了中央车站。之后，你所记得的探索顺序只是在任何给定时间是否向中央车站更远或更近，也就是说，你可以将你的旅程编码为一个二进制字符串，其中 0 表示乘坐一条地铁线路使你离中央车站更远一站，而 1 表示使你离中央车站更近一站。

## 样例 #1

### 输入

```
2
0010011101001011
0100011011001011
0100101100100111
0011000111010101```

### 输出

```
same
different```

# 题解

## 作者：__Sky__Dream__ (赞：11)

### [题目传送门](https://www.luogu.com.cn/problem/P10477)

## 解题思路
把 $0$ 看成 $1$，$1$ 看成 $-1$。

对于一个子树，如果从开头到某一段的和为 $0$，表示又回到了这个子树的根。

根据子树把字符串截乘小段，再排序。字符串类型方便比较两个树是否相同。

注意截成的小段递归求解时，要把开头和结尾的 $0$ 和 $1$ 去掉，才算是以这个子树的根为起点（开头本来表示进入这个根，结尾本来表示离开这个根）。

好用的 STL：`ss=s.substr(a,b)`，$a$ 为起点下标，$b$ 为长度。

对于 vector 的排序：`sort(vs,begin(),vs.end())`

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
void stl(string &s)
{
	if(s=="01") return;
	s=s.substr(1,s.size()-2);
	int st=0,cnt=0;
	vector<string>vs;
	vs.clear(); 
	for(int i=0;i<s.size();++i)
	{
		cnt+=(s[i]=='0'?1:-1);
		if(!cnt)
		{
			string ss=s.substr(st,i-st+1);
			stl(ss);
			vs.push_back(ss);
			st=i+1;
		}
	}
	sort(vs.begin(),vs.end());
	s='0';
	for(int j=0;j<vs.size();++j) s+=vs[j];
	s+='1';
	return;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		cin>>s1;
		cin>>s2;
		s1='0'+s1+'1';
		s2='0'+s2+'1';//方便后面递归
		stl(s1);
		stl(s2);
		if(s1==s2) printf("same\n");
		else printf("different\n");
	}
	return 0;
}
```

拜拜！

---

## 作者：Barewalk (赞：5)

### Description

定义树的一种遍历方式：从根节点出发，若存在未遍历过的子节点则前往子节点，否则返回父节点。用 01 串记录，分别表示进入子节点、返回父节点。给你两个 01 串，判断是否为同一棵树。

### Solution

由于遍历时 $0$ 可进入的节点不唯一，所以同一棵树不同顺序会有不同表示。因此我们需要统一进入子节点的顺序：按字典序升序排序。

考虑如何找出子树。注意到，该遍历具有两个性质：

* 一棵子树 $0$ 与 $1$ 的数量一定相等。因为每条边都会被一进一出遍历两遍。
* 一棵子树的子串一定是 $0$ 开头、$1$ 结尾，即“进入该子树根节点”、“离开根节点”。

据此，我们便可以顺利解决问题：取出开头 $0$、结尾 $1$ 之间的子串即为所有子树，依次遍历，用 $\text{num}$ 记录 $0$ 与 $1$ 数量之差，$r$ 记录该子树的根。若 $\text{num}=0$，则将这段子串提取出来，递归处理， 用 `vector` 记录，并更新 $r$。递归边界即子串为 `01`，因为它代表叶子结点，没有子树。

需要注意：由于一开始已经在根的位置，即没有“进入根节点”、“离开根节点”的部分，因此初始时需要在 01 串头尾加上 $0$ 和 $1$。

### Code

```cpp
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>

#define _rep(i,s,t) for(int i=s;i<=t;++i)
#define rep_(i,s,t) for(int i=s;i>=t;--i)

using namespace std;

int read(){
    int x=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        w=ch=='-'?-1:1,
        ch=getchar();
    while(ch>='0'&&ch<='9')                                     
        x=(x<<3)+(x<<1)+ch-'0',
        ch=getchar();
    return x*w;
}

string str(){
    string s="";
    char ch=getchar();
    while(ch=='\n')
        ch=getchar();
    while(ch!='\n')
        s+=ch,ch=getchar();
    return s;
}

void dfs(string &s){
    if(s=="01")
        return ;
    vector<string>str;
    s=s.substr(1,s.size()-2);
    //s.subster(a,b)：提取 s 中从 a 开始连续的 b 个字符
    int num=0,r=0;
    _rep(i,0,s.size()-1){
        num+=s[i]=='0'?1:-1;
        if(num==0){
            string s_tr=s.substr(r,i-r+1);
            dfs(s_tr);
            str.push_back(s_tr);
            r=i+1;
        }
    }
    s='0';
    sort(str.begin(),str.end());
    _rep(i,0,str.size()-1)
        s+=str[i];
    s+='1';
}

int main(){
    int t=read();
    while(t--){
        string s='0'+str()+'1',t='0'+str()+'1';
        dfs(s);
        dfs(t);
        puts(s==t?"same":"different");
    }
    return 0;
}
```

---

## 作者：vicissitudes (赞：3)

# Hash 总结
hash 的作用非常广，算是一种效率超级高的 DS。不过唯一缺点是可能会被卡。

作用是在 $O(1)$ 的时间内判断一个 $O(n)$ 的东西是否合法。

## 多项式哈希
一般的多项式 hash，即 $h(\lbrace a_n \rbrace) = \sum_{i = 1} a_i \times base^i$。

用于判断几段字符串是否相等，或者代替 KMP。

## 集合哈希

判断两个集合是否相等，由于集合无序，所以只要满足每个元素出现次数相等即可。

第一种同序列 hash 一样，设每个元素 $a_i$ 的 hash 值为 $base^{a_i}$，但容易被卡。

第二种可以用随机化 hash，即梅林旋转 (mt19937)，这个很难卡。

则如果 $h(\lbrace a_n \rbrace)$ 相等，我们就认为集合相等。

比如可以判断等差数列，也就是判断连续值域。

## 二维哈希
同一维哈希一样，我们把二维平面拆成一维，维护一个矩阵的哈希值采用二维前缀和。

## 树哈希

判断两棵树是否同构。

一般我们设 
$$g_u = f(\lbrace g_v | v \in son_u \rbrace)$$

$$f(s) = (c + \sum_{x \in s} h(x))$$

其中 c 为常数，一般取为 1。
这里的哈希 $h(x)$ 不建议用多项式，可以使用 xor shift 随机。如果怕被卡可以再梅林旋转。

如果 $g_u = g_v$，我们就认为子树 $u$ 和 子树 $v$ 相等。

## 随机化实现

mt19937（int 范围）

mt19937_64 （long long 范围）

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
	cout << rnd();
	return 0;
} 
```

xorshift 

```cpp
ull shift(ull x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
```

害怕被卡的就用这个：
```cpp
mt19937_64 rnd(time(0));
ull mask = rnd();
ull shift(ull x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}
```
# 本题
给你两个字符串，且一个字符串对应的是一颗树。判断这两棵树是否同构即可。

算是模板题了。管理员大大看到了可以加个 hash 的标签。

时间是线性的。

~~这题是黄？~~

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 3e3 + 10;

ull h[N];
int tot;
vector<int> vec[N];
int fa[N];

ull shift(ull x) {
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}

void dfs(int u, int fa) {
	h[u] = 1;
	for(int v : vec[u]) {
		if(v == fa) continue;
		dfs(v, u);
		h[u] += shift(h[v]);
	}
}

void init(string s) {
	int u = 1;
	for(int i = 1; i < N; i ++) vec[i].clear();
	tot = 1;
	for(char ch : s) {
		if(ch == '0') {
			tot ++;
			vec[u].push_back(tot);
			fa[tot] = u;
			u = tot;
		} else {
			u = fa[u];
		}
	}
}

void solve() {
	string s;
	tot = 0;
	cin >> s;
	init(s);
	dfs(1, 1);
	ull now = h[1];
	
	cin >> s;
	init(s);
	dfs(1, 1);
	if(now == h[1]) puts("same");
	else puts("different");
}

int main() {
	int n;
	cin >> n;
	while(n --) {
		solve();
	}
	return 0;
}
```

---

## 作者：wizardMarshall (赞：2)

前置知识：树哈希。

由于两树根是相同的，首先按照原字符串将树的形态建出来。

具体过程就是维护当前走到节点 $x$。如果下一个字符是 `0` 就新建节点 $y$ 并连边 $(x,y)$，然后将 $x$ 设为 $y$；如果下一个字符是 `1` 则将 $x$ 设为 $fa_x$。

然后计算哈希值：

$$f(x)=(\displaystyle \sum_{u \in son_x} f(u)) + (\displaystyle \prod_{u \in son_x} f(u)) +1$$

最后判断两棵树的 $f(1)$ 是否相同即可。

注意到这个式子中求和及乘积与子树大小无关，因此可以方便地维护形态相同但编号不同的树的哈希值。

## 代码

实测跑到了最优解前几位，并没有使用特别的优化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int p = 1000000007;
char s[3005];
vector <int> edge[3005];
int fa[3005];
ll c[3005];
void dfs(int x) {
    c[x] = 1;
    ll sum1 = 0, sum2 = 1;
    for (auto i : edge[x]) {
        if (i != fa[x]) {
            dfs(i);
            sum1 += c[i];sum1 %= p;
            sum2 *= c[i];sum2 %= p;
        }
    }
    c[x] += sum1;c[x] %= p;
    c[x] += sum2;c[x] %= p;
    return;
}
ll check() {
    scanf("%s", s + 1);
    int len = strlen(s + 1), now = 1, E = 1;
    for (int i = 1; i <= len; i++) {
        if (s[i] == '0') {
            edge[now].push_back(++E);
            edge[E].push_back(now);
            fa[E] = now;
            now = E;
        }else {
            now = fa[now];
        }
    }
    dfs(1);
    for (int i = 1; i <= E; i++) {
        edge[i].clear();
    }
    return c[1];
}
signed main() {
    int t;
    cin >> t;
    while (t--) {
        ll c1 = check();
        ll c2 = check();
        if (c1 == c2) {
            printf("same\n");
        }else {
            printf("different\n");
        }
    }
    return 0;
}
```

---

## 作者：liguangjun2023 (赞：2)

# 分析
1. **确定所有的子树**
	
每条线路走两遍，且未探索的线路优先探索，没有路则沿原路返回，所以用表示探索，用“１”表示返回，则每颗子树的和一定为“０”，按照此规律找到该树所有的子树序列；

2. **形成统一的子树序列**

遍历顺序不同，导致输出结果差异，所以判定两棵树相等应该以相同的顺序对各个子树排序，形成新的序列；

3. **输出结果**	

4. **注意**
- 在字符串开始补充“０”,在结束补充“１”，表示离开中心站，返回到中心站；
- 查找子树时，离开中心站和返回中心站要忽略；
- 生成新的排序后新序列时，添加上各个子树的离开中心站与返回中心站；
    

------------
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
//输出结果
string check(string  sta,string  stb){
	if(sta==stb)	
		return "same\n";
	else
		return "different\n";
} 
//找出所有子树且按升序对子树排序
void subtree(string &str){
	if(str=="01")	
		return ;
	str=str.substr(1,str.size()-2);
	int bg=0,sm=0;
	vector<string> vct;
	for(int i=0;i<str.size();i++){		
		if(str[i]=='0') 
			sm+=-1; 
		else
			sm+=1;	
		if(sm==0){	
			string tstr=str.substr(bg,i-bg+1);	
			subtree(tstr);	
			vct.push_back(tstr);			 
			bg=i+1;			
		}
	}
	sort(vct.begin(),vct.end());
	str="0";
	for(int i=0;i<vct.size();i++){
		str+=vct[i];
	}
	str+="1";
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		string sta,stb;
		cin>>sta>>stb;
		sta="0"+sta+"1", stb="0"+stb+"1"; 
		subtree(sta);
		subtree(stb);		
		cout<<check(sta,stb);			
	}
	return 0;
}

```

---

## 作者：Nostopathy (赞：2)

## solution

### 0 前言

今天上初中啦！感谢 Luogu 的同学们一路以来的支持！

### 1 思路

本题是查找子树练习题。

一条线路遍历两次，为了统一标准，没有探索过的优先探索，且最后进行排序，类似深搜的思路一条路走到底，没有路原路返回（回溯）。在去的时候每走一步计数变量加一，回来的时候每一步减一，这样当计数变量为 $0$ 时，说明回到了原点。

注意：需要在输入的字符串头加上 $\tt 1$，尾加上 $\tt 0$，表示离开与回到中心车站。但是在离开中心车站查找子树时要忽略，否则计数变量的值会出现错误。

### 2 程序


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define st string
const int maxN = 3E3+10;
int T;
st s1,s2;
void su(string &s){
	if(s=="01")return;
	s=s.substr(1,s.size()-2);
	int sum=0,sta=0;
	vector<string>vec;
	for(int i=0;i<s.size();++i){
		sum+=(s[i]=='1')*2-1;
		if(sum==0){
			string sub=s.substr(sta,i-sta+1);
			su(sub);vec.push_back(sub);
			sta=i+1;
		}
	}
	stable_sort(vec.begin(),vec.end());
	s="0";
	for(int i=0;i<vec.size();++i)s+=vec[i];
	s+="1";
}
signed main(){
	cin>>T;
	while(T --){
		cin>>s1>>s2;
		s1='0'+s1+'1';s2='0'+s2+'1';
		su(s1);su(s2);
		if(s1==s2)cout<<"same\n";
		else cout<<"different\n";
	}
	return 0;
}
```

拜拜！

---

## 作者：flying_bluecat (赞：1)

# P10477 Subway tree systems
似水不水。

大概思路：对旅途的二进制字符串进行处理，找出其中隐含的地铁树系统结构信息，然后比较两组字符串所代表的结构是否相同。

很好。很笼统是吗？具体来说，我们可能需要 2 个功能性的函数来实现：

第一个函数用于处理给定字符串中的子树结构。

首先，对传入的字符串进行预处理。如果字符串是 `01`，则直接返回，因为这可能是一种特殊的基础情况，无需进一步处理。否则，去除字符串首尾的字符（即去掉开头的 `0` 和结尾的 `1`），得到中间的核心部分，后续操作主要基于此核心部分进行。

接着，通过遍历核心部分字符串来查找子树。使用一个变量 `bal`（平衡计数）来模拟类似括号平衡的状态，遇到字符 `0` 时，`bal` 减 1，遇到字符 `1` 时，`bal` 加 1。当 `bal` 的值变为 0 时，表示找到了一个完整的子树（从当前记录的子树起始索引 `start` 到当前位置 `i` 的子字符串）。

对于找到的每个子树，递归调用 `procSub` 函数自身，对子树内部可能存在的更深层次的子树结构进行同样的处理。处理完子树内部后，将处理后的子树字符串添加到一个向量 `v` 中，并更新子树起始索引 `start`，以便继续查找下一个子树。

在找出所有子树并完成递归处理后，使用 `sort` 函数对存储子树字符串的向量 `v` 按照字典序进行升序排序。

最后，按照特定规则重构字符串。先将字符串赋值为 `0`，然后依次将排序后的子树字符串连接起来，最后添加结尾的 `1`，完成整个字符串的重新构建过程，使其具有符合后续比较要求的结构。并且通过 `const_cast` 将处理后的字符串回传给原传入的引用参数，完成对原字符串的修改。

  第二个函数用于比较两个处理后的字符串是否相同，根据比较结果返回相应的结果字符串（`same` 或者 `different`）。

我们可以通过对比两个字符串是否相等来判断，如果相等则返回 `same\n`，表示它们代表相同的系统；如果不相等，则返回 `different\n`，表示代表不同的系统。


以下是代码实现的示例：
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 比较两字符串是否相同，返回对应结果字符串（"same\n" 或 "different\n"）
string cmpStr(const string& s1, const string& s2) {
    if (s1 == s2) {
        return "same\n";
    }
    return "different\n";
}

// 处理给定字符串中的子树，排序后重构字符串
// 会修改传入的字符串
void procSub(const string& inStr) {
    string str = inStr;
    if (str == "01") {
        return;
    }
    str = str.substr(1, str.size() - 2);

    int start = 0;  // 子树起始索引
    int bal = 0;    // 平衡计数（类似括号平衡判断子树）
    vector<string> v;  // 存子树字符串

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '0') {
            bal -= 1;
        } else {
            bal += 1;
        }
        if (bal == 0) {
            string sub = str.substr(start, i - start + 1);
            procSub(sub);
            v.push_back(sub);
            start = i + 1;
        }
    }

    sort(v.begin(), v.end());

    str = "0";
    for (size_t i = 0; i < v.size(); ++i) {
        str += v[i];
    }
    str += "1";

    // 将处理后的字符串回传给原传入的引用参数
    const_cast<string&>(inStr) = str;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s1, s2;
        cin >> s1 >> s2;

        s1 = "0" + s1 + "1";
        s2 = "0" + s2 + "1";

        procSub(s1);
        procSub(s2);

        cout << cmpStr(s1, s2);
    }
    return 0;
}
```

---

## 作者：forever_nope (赞：1)

## 树的最小表示法

题目：[P10477 Subway tree systems](https://www.luogu.com.cn/problem/P10477).

题目描述：给定每一时刻是远离根（$0$）还是靠近根（$1$）。

判断两个给定的操作序列，所对应的两棵树是否同构。

容易发现，我们递归的处理，

+ 把每一棵子树的操作序列按照字典序排列即可。

> 考虑一些比较简单的证明：
>
> 一个操作序列一定唯一的对应着一棵树。
>
> 这是一个很重要的结论，但是也很好证明。
>
> 考虑到每一条边都只能来回经过两次，因此，
>
> 当我们进入一个点时，只能新开一个；
>
> 当我们退出一个点时，因为是树，因此只存在一个父亲。

然后考虑如何处理。

首先我们知道一个序列，一定开头是 $0$ 结尾是 $1$，

因为这两个是用于离开、回到根的。

因此，当我们删去这两个以后，其他的，

我们将 $0$ 视为 $1$，将 $1$ 视为 $-1$，那么，

如果一个区间前缀和是 $0$，那么这个区间就是一个完整的子树。

递归处理即可。

+ 具体的，递归的把序列分成若干个小块，
+ 去掉首位的 $0$ 和 $1$，然后扫描一遍。
+ 将每一小块递归处理后，加入一个数组。
+ 扫描完成后，将数组排序，拼接，即最小表示。
+ 刚开始的时候要加上首位的 $0$、$1$，因为我们的递归是从进入一棵树开始的。

```cpp
#include <bits/stdc++.h>

using namespace std;

int op[2] = {1, -1};

string mcs(string s) {
    int cnt = 0, k = 0;
    s = s.substr(1, s.size() - 2);
    vector<string> bucket;
    for (int i = 0; i < (int)s.size() - 1; ++i) {
        cnt += op[s[i] - '0'];
        if (cnt == 0) bucket.push_back(mcs(s.substr(k, i - k + 1))), k = i + 1;
    }
    if (k) bucket.push_back(mcs(s.substr(k)));
    else bucket.push_back(s.substr(k));
    sort(bucket.begin(), bucket.end());
    string ans;
    for (const string &i : bucket) ans += i;
    return "0" + ans + "1";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        string a, b; cin >> a >> b;
        a = mcs("0" + a + "1"), b = mcs("0" + b + "1");
        puts(a == b ? "same" : "different");
    }
    return 0;
}
```

---

## 作者：guozhetao (赞：0)

## 题目
$n$ 组数据，每组数据给定两个 $01$ 串（长度不超过 $3000$），意思如下：

- 对于每一个 $0$，代表该节点有一个子节点，并前往该子节点。
- 对于每一个 $1$，代表返回该节点的父亲节点。

求两个字符串说表示的树是否同构。

## 思路
考虑对于每一个节点进行递归处理（因为可以知道一个大问题可以拆成多个小问题进行计算）。为方便后续操作，可虚构一个根节点的父亲节点（即在字符串开头加上 $0$，结尾加上 $1$）。

对于每一个节点，我们可以获得一个字符串代表该节点的子树，首先去掉头尾的字符（即去掉通往父亲节点的边），记 $S$ 为字符串，$cnt$ 表示 $S$ 从 $0$ 到 $i$ 中 $0$ 的数量与 $1$ 的数量的差，$j$ 表示儿子的数量。容易得到以下结论：

- 对于$S_i = 0$,则 $cnt \gets cnt + 1$。
- 对于$S_i = 0$,则 $cnt \gets cnt - 1$。
- 对于 $cnt = 0$，即一个儿子已经遍历结束，则 $j \gets j + 1$，并统计前一个儿子所代表的子串进行递归。

如果全部儿子所代表的子串递归完毕，可按照字符串排序的方式排列儿子所代表的字符串，并在头尾添上 $01$。可以发现，对于两个同构的树，以上操作后获得的字符串相等。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
string a,b;
string paixu(string x) {
	//cout<<x<<endl;
	// 分离操作
	string y = x;
	int num = x.size(),cnt = 0;
	x = "";
	if(num <= 2) return y;
	for(int i = 1;i < num - 1;i++) x += y[i];
	num -= 2;
	string new_string[1505];
	int j = 1;
	for(int i = 0;i < num;i++) {
		if(x[i] == '0') cnt++,new_string[j] += '0';
		else cnt--,new_string[j] += '1';
		if(cnt == 0) {
			j++;
		}
	}
	j--;
	//递归
	for(int i = 1;i <= j;i++) new_string[i] = paixu(new_string[i]);
	//排序
	for(int i = j;i >= 1;i--) {
		for(int k = 1;k < i;k++) {
			if(new_string[k] > new_string[k + 1]) swap(new_string[k],new_string[k + 1]);
		}
	}
	for(int i = 2;i <= j;i++) new_string[1] += new_string[i];
	//cout<<("0" + new_string[1] + "1")<<endl;
	return ("0" + new_string[1] + "1");
}
signed main() {
	scanf("%lld",&T);
	while(T--) {
		cin >> a >> b;
		a = "0" + a + "1";
		b = "0" + b + "1";
		if(paixu(a) == paixu(b)) printf("same\n");
		else printf("different\n");
	}
    return 0;
}


```

---

