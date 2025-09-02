# [CCC 2022 J4] Good Groups

## 题目背景

请注意：这道题是 [CCO 2022 S2  Good Groups](https://www.luogu.com.cn/problem/P8396) 的弱化版

管理备注：似乎没有弱化

## 题目描述

一个班级会被分成 $g$ 个组，每个组有三个人，这种分组方式可能会违反两种规定：

1. 一些学生必须在同一小组；
2. 一些学生必须不在同一小组。

现在校长找到了你，问学生一共违反了多少个规定。

## 说明/提示

### 样例2解释：

1. $\rm A$ 和 $\rm B$ 必须在同一组，这一点违反了。
2. $\rm G$ 和 $\rm L$ 必须在同一组，这一点违反了。
3. $\rm J$ 和 $\rm K$ 必须在同一组，这一点没有违反。
4. $\rm D$ 和 $\rm F$ 必须不在同一组，这一点违反了。
5. $\rm D$ 和 $\rm G$ 必须不在同一组，这一点没有被违反。

以上 $5$ 条共违反 $3$ 条，所以输出 $3$。

对于 $25\%$ 的数据：$1\le g\le 50 , 1\le x\le 50,y=0$

对于另外 $60\%$ 的数据：$1\le g\le 50 , 1\le x\le 50,1\le
 y\le 50$
 
对于 $100\%$ 的数据：$1\le g\le 10^5,1\le x\le 10^5,1\le y\le 10^5$

## 样例 #1

### 输入

```
1
ELODIE CHI
0
2
DWAYNE BEN ANJALI
CHI FRANCOIS ELODIE```

### 输出

```
0```

## 样例 #2

### 输入

```
3
A B
G L
J K
2
D F
D G
4
A C G
B D F
E H I
J K L```

### 输出

```
3```

# 题解

## 作者：LYqwq (赞：4)

$\textsf{update on 2022/6/20 发现题目链接错了，修复。}$

---

[题目传送门](https://www.luogu.com.cn/problem/P8403)

# 题目大意

一个班级被分成 $g$ 个组，每组三个人，现有一些约束：

- 某对学生必须在同一小组。
- 某对学生必须不在同一小组。

现给出分组方案，以及约束条件若干条，求有多少条约束不成立。

# 思路

[双倍经验](https://www.luogu.com.cn/problem/P8396)。

既然涉及到分组，那么我的第一反应就是并查集。

使用并查集记录学生的分组情况，然后对所有约束条件一一判断，若有不成立的条件，就计入答案。

但还有一个问题：学生的名字为字符串，不是数字。

于是就需要将这些字符串转化为数字。

考虑用 `map` 记录所有名字的下标，如果第一次遇到某个名字 $s$，`m[s]` 一定为 $0$，这种情况给 $s$ 分配下一个未使用的下标即可。注意下标不能使用 $0$，否则每次都会重新分配下标。

但这种方法直接交上去会 [TLE](https://www.luogu.com.cn/record/77331562)，吸氧才能 [AC](https://www.luogu.com.cn/record/77331596)。

作为一个非不吸氧 A 题不可的人，我决定再考虑一下字符串哈希。

可是很多种 hash 方法都会 WA 几个点。

于是将并查集范围开到 $10^7$，试图减少 hash 冲突...

还是一片红......

最终得到，使用 [BKDR hash](https://blog.csdn.net/m0_50194941/article/details/120089879) 可过此题。

上面那篇文章中说到，`need` 取 $2^n-1$ 比较好，那么我们就取 $2^6-1$ 吧，也就是 $63$。

代码是这样的：

```cpp
int hs(string s){
    unsigned int res=0;
    for(int i=0; i<s.size(); i++)
        res=(res*63)^s[i];
    return res%(int)1e7; // 最后需要mod1e7，
}
```

再交一发，这题就[没了](https://www.luogu.com.cn/record/77333648)。

# 代码

```cpp
#include <iostream>
using namespace std;
const int N=1e5+5;
int x,y,g,ans;
string n1[N][2],n2[N][2],a,b,c;

template<class T=int>
class set{
    public:
        set(int n=1e5){f=new T[l=n+5]; clear();}
        ~set(){delete[] f;}
        T find(T x){return f[x]==x ? x : f[x]=find(f[x]);}
        void merge(T x,T y){f[find(x)]=find(y);}
        void clear(){for(int i=0; i<l; i++) f[i]=i;}
    private:
        T *f;
        int l;
};
set<int> s(1e7); // 并查集(构造函数传范围)

// 字符串哈希
int hs(string s){
    unsigned int res=0;
    for(int i=0; i<s.size(); i++)
        res=res*63+s[i]; // BKDR 哈希
    return res%(int)1e7;
    // res需要作为数组下标，为了防止哈希冲突，将数组开到了 1e7
}

int main(){
    scanf("%d",&x); // 约束 1 个数
    for(int i=1; i<=x; i++) cin >> n1[i][0] >> n1[i][1];
    scanf("%d",&y); // 约束 2 个数
    for(int i=1; i<=y; i++) cin >> n2[i][0] >> n2[i][1];
    scanf("%d",&g); // 组数
    for(int i=1; i<=g; i++){
        cin >> a >> b >> c; // a,b,c 在同一组
        s.merge(hs(a),hs(b)); // 将其合并
        s.merge(hs(a),hs(c));
    }
    for(int i=1; i<=x; i++) // 判断是否违反约束 1
        if(s.find(hs(n1[i][0]))!=s.find(hs(n1[i][1]))) ans++;
    for(int i=1; i<=y; i++) // 同上，约束 2
        if(s.find(hs(n2[i][0]))==s.find(hs(n2[i][1]))) ans++;
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：Dream_weavers (赞：4)

## 题意

一个班被分成了 $g$ 组，每组 $3$ 个人，肯能会违反两种规定：

- 一些学生必须在同一组

- 一些学生必须不在同一组

求有多少学生违反了规定。

## 思路

根据 $g$ 中的每组学生来建**无向图**（图是不连通的）。每组中三个人都两两建一条无向边，代表他们两个人被分到了一个组。建完图再看 $x$ 和 $y$，两个同学之间判断是否存在或是否不存在一条边，如果没有满足条件就累加统计，最后输出答案。

建图建议用 stl 的 map，因为 map 的 key 可是字符串。

## 代码

ps：此解法的时间复杂度、空间复杂度都很高，建议开 O2
，否则会 TLE 几个点。

[不开 O2](https://www.luogu.com.cn/record/77303329)

[开 O2](https://www.luogu.com.cn/record/77303387) 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct node{
	string s1,s2;
}xx[N],yy[N];
map <pair<string,string>,int> mp;
inline void makes(string s1,string s2){
	mp[make_pair(s1,s2)]=1,mp[make_pair(s2,s1)]=1;
}
int x,y,g,tot;
int main(){
	cin>>x;
	for(int i=1;i<=x;i++)cin>>xx[i].s1>>xx[i].s2;
	cin>>y; 
	for(int i=1;i<=y;i++)cin>>yy[i].s1>>yy[i].s2;
	cin>>g;
	for(int i=1;i<=g;i++){
		string s1,s2,s3;
		cin>>s1>>s2>>s3;
		makes(s1,s2),makes(s1,s3),makes(s2,s3);
	}
	for(int i=1;i<=x;i++){
		string s1=xx[i].s1,s2=xx[i].s2;
		if(mp[make_pair(s1,s2)]!=1)tot++;
	}
	for(int i=1;i<=y;i++){
		string s1=yy[i].s1,s2=yy[i].s2;
		if(mp[make_pair(s1,s2)]==1)tot++;
	}
	cout<<tot;
	return 0;
}

```

---

## 作者：yeshubo_qwq (赞：2)

简单模拟。

首先读入规定，也就是哪些人必须在一起，哪些人不能在一起。

然后读入小组，并将小组内的三个人的组别全部赋值为小组的编号。

最后根据小组编号，累加不符合的规定即可。

注意名字是字符串，做到**三个人的组别全部赋值为小组的编号**时无法直接用名字做下标，可以用 STL 中的 map。

代码：

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
namespace P{
	int t1,t2,t3,i;
	string n1[2][100005],n2[2][100005];
	string a,b,c;
	map <string,int> g;
	void solve(){
		cin>>t1;
		for (i=1;i<=t1;i++)
			cin>>n1[0][i]>>n1[1][i];
		cin>>t2;
		for (i=1;i<=t2;i++)
			cin>>n2[0][i]>>n2[1][i];
		cin>>t3;
		for (i=1;i<=t3;i++){
			cin>>a>>b>>c;
			g[a]=g[b]=g[c]=i;
		}
		int ans=0;
		for (i=1;i<=t1;i++)
			if (g[n1[0][i]]!=g[n1[1][i]])
				ans++;
		for (i=1;i<=t2;i++)
			if (g[n2[0][i]]==g[n2[1][i]])
				ans++;
		cout<<ans;
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	return P::solve(),0;
}


```


---

## 作者：GI录像机 (赞：1)

~~这题居然不卡 unordered_map~~

## 思路梗概：

看到字符串，第一反应就是把字符串唯一映射成整数便于处理。

然后我们发现，两个学生在一个小组和两个学生不在一个小组两个规定都与顺序无关，我们就可以存到第一个人对应的 vector 容器里面，便于后面暴力。

对于每个分组的每个人，枚举与他有关的所有规定，判断是否与另外两人吻合。这样的做法是线性的，因为每个规定只会判断一次。

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
string reads() {
	string s;
	char c = getchar();
	while (c == ' ' || c == '\n')c = getchar();
	while (c != ' ' && c != '\n') {
		s += c;
		c = getchar();
	}
	return s;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e6 + 10;
int x, y, g, tot, ans;
vector<int>a[N], u[N];
unordered_map<string, int>mp;
string name1, name2, name3;
signed main() {
	x = read();
	for (int i = 1; i <= x; i++) {
		name1 = reads(), name2 = reads();
		if (!mp[name1])mp[name1] = ++tot;
		if (!mp[name2])mp[name2] = ++tot;
		a[mp[name1]].push_back(mp[name2]);
	}
	y = read();
	for (int i = 1; i <= y; i++) {
		name1 = reads(), name2 = reads();
		if (!mp[name1])mp[name1] = ++tot;
		if (!mp[name2])mp[name2] = ++tot;
		u[mp[name1]].push_back(mp[name2]);
	}
	g = read();
	for (int i = 1; i <= g; i++) {
		name1 = reads(), name2 = reads(), name3 = reads();
		if (mp[name1]) {
			for (int i = 0; i < a[mp[name1]].size(); i++) if (a[mp[name1]][i] != mp[name2] && a[mp[name1]][i] != mp[name3])ans++;
			for (int i = 0; i < u[mp[name1]].size(); i++) if (u[mp[name1]][i] == mp[name2] || u[mp[name1]][i] == mp[name3])ans++;
		}
		if (mp[name2]) {
			for (int i = 0; i < a[mp[name2]].size(); i++) if (a[mp[name2]][i] != mp[name1] && a[mp[name2]][i] != mp[name3])ans++;
			for (int i = 0; i < u[mp[name2]].size(); i++) if (u[mp[name2]][i] == mp[name1] || u[mp[name2]][i] == mp[name3])ans++;
		}
		if (mp[name3]) {
			for (int i = 0; i < a[mp[name3]].size(); i++) if (a[mp[name3]][i] != mp[name2] && a[mp[name3]][i] != mp[name1])ans++;
			for (int i = 0; i < u[mp[name3]].size(); i++) if (u[mp[name3]][i] == mp[name2] || u[mp[name3]][i] == mp[name1])ans++;
		}
	}
	write(ans);
	return 0;
}
```


---

