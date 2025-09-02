# Game

## 题目描述

Kostya 在玩一个游戏，他在游戏内成立了公会，包括他在内，工会有 $k$ 名成员。

## 说明/提示

对于 $100\%$ 的数据，保证
$1 \le k \le 100$；
$1 \le n \le 50$；
$0 \le m \le 50$；
$1 \le q \le 500$。

## 样例 #1

### 输入

```
2 3 2 5
desolator
refresher
perseverance
vanguard: desolator 1, refresher 1
maelstorm: perseverance 2
1 desolator
2 perseverance
1 refresher
2 desolator
2 perseverance
```

### 输出

```
1
vanguard 1
2
desolator 1
maelstorm 1
```

# 题解

## 作者：2023gdgz01 (赞：6)

这是一道很经典的模拟题。

由于数据范围很小，我们能很容易地想到模拟法。

- 用 $a_{i,j}$ 表示第 $i$ 号成员拥有第 $j$ 号基础神器的数量。

- 用 $b_{i,j}$ 表示第 $i$ 号成员拥有第 $j$ 号高级神器的数量。

- 用 $c_{i,j}$ 表示第 $i$ 号高级神器合成所需第 $j$ 号基础神器的数量。

为了方便，我们使用 `map<string, int>` 对应神器名称和其编号。

最后输出时只需将该成员拥有的所有种类的神器的名称和数量存为 `pair` 后排序即可。

本题输入比较麻烦，需要小心处理。

代码如下：

```cpp
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

bool flag;
int k, n, m, q, p, x, num, a[105][55], b[105][55], c[55][55];
string art, temp, s[55], name[55];
map<string, int> box;
pair<string, int> ans[205];

int main()
{
	cin >> k >> n >> m >> q;
	for (register int i = 1; i <= n; ++i) {
		cin >> s[i];
		box[s[i]] = i; //存储基础神器。
	}
	for (register int i = 1; i <= m; ++i) {
		cin >> name[i];
		name[i] = name[i].substr(0, name[i].size() - 1); //去掉冒号。
		box[name[i]] = i; //存储高级神器。
		while (true) {
			cin >> art >> num;
			c[i][box[art]] = num; //更新该高级神器的合成方法。
			if (getchar() != ',') //读入该高级神器的合成方法直至换行。
				break;
		}
	}
	while (q--) {
		cin >> x >> temp;
		++a[x][box[temp]]; //更新该成员的基础神器。
		for (register int i = 1; i <= m; ++i) { //依次检查每种高级神器是否可合成（题目中说若可合成高级神器，立即合成）
			flag = true;
			for (register int j = 1; j <= n; ++j)
				if (a[x][j] < c[i][j]) {
					flag = false;
					break;
				}
			if (flag) { //若可合成，
				for (register int j = 1; j <= n; ++j)
					a[x][j] -= c[i][j]; //更新基础神器数量。
				++b[x][i]; //更新高级神器数量。
			}
		}
	}
	for (register int i = 1; i <= k; ++i) { //遍历输出。
		num = 0;
		for (register int j = 1; j <= n; ++j) { //遍历基础神器。
			if (a[i][j]) { //若数量不为零
				++num;
				ans[num] = make_pair(s[j], a[i][j]); //加入 pair
			}
		}
		for (register int j = 1; j <= m; ++j) { //同上，遍历高级神器。
			if (b[i][j]) {
				++num;
				ans[num] = make_pair(name[j], b[i][j]);
			}
		}
        //排序并输出。
		sort(ans + 1, ans + num + 1);
		cout << num << "\n";
		for (register int j = 1; j <= num; ++j)
			cout << ans[j].first << " " << ans[j].second << "\n";
	}
	return 0;
}
```

[AC 链接](https://www.luogu.com.cn/record/134828723)

---

## 作者：OrientDragon (赞：1)

# 分析

大模拟题。

对于每次购买之后，由于

> 第 $i$ 次购买后，这个人有**不超过一次**的合成机会。

所以可以暴力枚举要合成 $1 \sim m$ 中的哪些物品。

两个小 trick：

1. 字符串要**映射到整数上**，对整数进行操作，不然会很慢；
2. 这道题在最后统计答案的时候，可以用 `a[x][idx]` 来表示第 $x$ 个人有几个编号为 `idx` 的物品，把第 $x$ 个人的物品塞入 `map` 中（自动排序），然后输出。

# 代码

```cpp
// C. Game
#include<bits/stdc++.h>
using namespace std;

const int N=105;
int k,n,m,q,tot[N],a[N][N],need[N][N],cnt[N][N];
string name[N],fre[N];
map<string,int>idx;
map<string,int>kids[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>k>>n>>m>>q;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		fre[i]=s;
		idx[s]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>name[i];
		name[i]=name[i].substr(0,name[i].size()-1);
		idx[ name[i] ]=n+i;
		int k=0;
		while(1){
			string t;
			int c_cnt;
			cin>>t>>c_cnt;
			need[i][++k]=idx[t];
			cnt[i][k]=c_cnt;
			if(getchar()!=',')break;
		}
		tot[i]=k;
	}
	while(q--){
		int x;
		string buy;
		cin>>x>>buy;
		a[x][ idx[buy] ]++;
		for(int i=1;i<=m;i++){
			bool flag=1;
			for(int j=1;j<=tot[i];j++)
				if(a[x][ need[i][j] ] < cnt[i][j]){
					flag=0;
					break;
				}
			if(!flag)continue;
			for(int j=1;j<=tot[i];j++)
				a[x][ need[i][j] ] -= cnt[i][j];
			a[x][ idx[ name[i] ] ]++;
			break;
		}
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			if(!a[i][j])continue;
			kids[i][ fre[j] ]+=a[i][j];
		}
		for(int j=n+1;j<=n+m;j++){
			if(!a[i][j])continue;
			kids[i][ name[j-n] ]+=a[i][j];
		}
		cout<<kids[i].size()<<'\n';
		for(auto kx:kids[i])
			cout<<kx.first<<' '<<kx.second<<'\n';
	}
}
```

---

## 作者：tallnut (赞：0)

这道大模拟六的嘞。
# 思路 v1.0
## 读入
~~读入就是一个小毒瘤。~~

先用 `getline()` 函数读取一整行存起来，然后依次分离高级神器名称、每一项基础神器的名称和数量。

细节很多。
## 存储
### 基础神器的名称
一个数组存起来即可。
### 高级神器如何合成的记录
写一个结构体，存储高级神器名称和一个 `map<string,int>`，表示合成所需的基础神器名称与数量的对应关系。（当然，这个做法有不合理之处，后文会讲到）
### 每个成员拥有的神器信息
用 `map` 套数组（即 `map<string,int> record[N]`），数组表示每一个人，`map<string,int>` 表示他拥有的每个神器及其数量。
## 处理合并
在每次购买结束后枚举一遍每个人、每种高级神器，对每种高级神器扫一遍数组，判断最多能买几个高级神器。
## 结果
你惊喜地发现 $\text{TLE}$ 了。

你非常不服气，就给它加了一个珂爱的火车头，成功再次 $\text{TLE}$ 了。

你疯狂地卡常，还是没有卡过。

（当然，如果有大佬按照这个方法过了，当我没说。）
## TLE 代码
[TLE 记录](https://www.luogu.com.cn/record/140088150)。
```
#include <iostream>
#include <map>
#include <vector>
using namespace std;
const short N = 110;
short k,m,n,q,tmpn;
string tmps,tmps2,tmps3;
char tmpc;
//记录每个成员的神器
map<string,short> memberrecord[110];
//记录基础神器的名字
string basicname[110];
//记录高级神器的合成信息
struct senior
{
	string name;
	map<string,short> art;
} seniorinfo[110];
//字符串转数字
inline short toshort(const string& s)
{
	short ans = 0;
	for (short i = s.size() - 1,j = 1;i >= 0;i--,j *= 10)
		ans += (s[i] - '0') * j;
	return ans;
}
inline short min(short a,short b) { return (a > b) ? b : a; }
int main()
{
	//读入信息
    cin >> k >> n >> m >> q;
    //基础神器
    for (short i = 1;i <= n;i++)
    	cin >> basicname[i];
    //高级神器
    for (short i = 1;i <= m;i++)
    {
    	//忽略换行
    	tmpc = getchar();
    	while (tmpc == '\n')
    		tmpc = getchar();
    	//获取整条高级神器信息
    	getline(cin,tmps);
    	//加上最开头的字母
    	tmps = tmpc + tmps;
    	//分离出高级神器名字
    	short j = 0;
    	for (;tmps[j] != ':';j++)
    		tmps2 += tmps[j];
    	seniorinfo[i].name = tmps2;
    	tmps2 = "";
    	//跳过冒号
    	j++;
    	//跳过空格
    	for (;tmps[j] == ' ';j++);
    	//读入每一条构成信息
    	while (j < tmps.size())
    	{
    		//分离出基础神器名字
    		for (;tmps[j] != ' ';j++)
    			tmps2 += tmps[j];
    		//跳过空格
    		for (;tmps[j] == ' ';j++);
    		//分离出基础神器数量
    		for (;j < tmps.size() && tmps[j] != ',';j++)
    			tmps3 += tmps[j];
    		//转为整型
    		seniorinfo[i].art[tmps2] = toshort(tmps3);
    		tmps2 = "";
    		tmps3 = "";
    		//跳过逗号
    		j++;
    		//跳过空格
    		for (;j < tmps.size() && tmps[j] == ' ';j++);
		}
	}
	//购买信息
	while (q--)
	{
		cin >> tmpn >> tmps;
		memberrecord[tmpn][tmps]++;
		//处理合并（必须在读入的过程中进行合并）
		for (short i = 1;i <= k;i++)
		{
			//枚举每一种高级神器
			for (short j = 1;j <= m;j++)
			{
				//枚举每一项基础神器，取能够买的最小值
				short buynum = 1e4;
				for (auto p = seniorinfo[j].art.begin();p != seniorinfo[j].art.end();p++)
					buynum = min(buynum,memberrecord[i][p->first] / p->second);
				//减少基础神器
				for (auto p = seniorinfo[j].art.begin();p != seniorinfo[j].art.end();p++)
					memberrecord[i][p->first] -= buynum * p->second;
				//增加高级神器
				memberrecord[i][seniorinfo[j].name] += buynum;
			}
		}
	}
	//输出
	for (short i = 1;i <= k;i++)
	{
		short cnt = 0;
		for (auto p = memberrecord[i].begin();p != memberrecord[i].end();p++)
			if (p->second > 0) cnt++;
		cout << cnt << '\n';
		for (auto p = memberrecord[i].begin();p != memberrecord[i].end();p++)
			if (p->second > 0) cout << p->first << ' ' << p->second << '\n';
	}
}
```
# 思路 v2.0
经过观察数据，我发现，在后来的测试点中人名一般很长，会有几十个字符。

于是我就想出了 $\text{TLE}$ 的解决办法——**把字符串压缩为整型，节约时间和空间。**

怎么压缩呢？我采取的措施是把基础神器名字数组和高级神器名字数组分别排序，然后把字符串转换为其下标。

~~我写到这篇题解才发现排序这一步根本没必要。~~

那么问题来了——把字符串转为整型后，如何转回去呢？

我们可以把字符串与整型的对应关系存在两个 `map` 中。之所以用两个 `map`，是因为一个是 `map<string,int>`，另一个是 `map<int,string>`。这样把同样的东西存两遍可以加快访问速度。

于是我们就可以把存储名字的 `string` 全部替换为 `int` 了，大大加快了时间。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/140091974)，代码中有注释。

~~不得不说这份代码跑得真是慢死了，连 1.03s 都跑出来了。~~
```
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 110;
int k,m,n,q,tmpn;
string tmps,tmps2,tmps3;
char tmpc;
//记录每个成员的神器
map<int,int> memberrecord[N];
//记录基础神器的名字
string basicname[N];
//记录基础和高级神器与该神器的对应值
//记录两份一样的对应关系，不过一个是根据int查string，另一个是根据string查int，方便查找
map<int,string> list_is;
map<string,int> list_si;
//记录高级神器的合成信息
struct senior
{
	string name;
	int name_id;
	vector<pair<int,int> > basics;
} seniorinfo[N];
bool cmp(const senior& sx,const senior& sy) { return sx.name < sy.name; }
//字符串转数字
inline int toint(const string& s)
{
	int ans = 0;
	for (int i = s.size() - 1,j = 1;i >= 0;i--,j *= 10)
		ans += (s[i] - '0') * j;
	return ans;
}
inline int min(int a,int b) { return (a > b) ? b : a; }
//把基础神器的名字转换为一个整型
inline void process_basic()
{
	sort(basicname + 1,basicname + n + 1);
	for (int i = 1;i <= n;i++)
	{
		list_is[i] = basicname[i];
		list_si[basicname[i]] = i;
	}
}
//把高级神器的名字转换为一个整型
inline void process_senior()
{
	sort(seniorinfo + 1,seniorinfo + m + 1,cmp);
	for (int i = 1;i <= m;i++)
	{
		//+n为了避免与basic部分重合
		list_is[i + n] = seniorinfo[i].name;
		list_si[seniorinfo[i].name] = i + n;
	}
}
int main()
{
	//读入信息
    scanf("%d%d%d%d",&k,&n,&m,&q);
    //基础神器
    for (int i = 1;i <= n;i++)
    	cin >> basicname[i];
    process_basic();
    //高级神器
    for (int i = 1;i <= m;i++)
    {
    	//忽略换行
    	tmpc = getchar();
    	while (tmpc == '\n')
    		tmpc = getchar();
    	//获取整条高级神器信息
    	getline(cin,tmps);
    	//加上最开头的字母
    	tmps = tmpc + tmps;
    	//分离出高级神器名字
    	int j = 0;
    	for (;tmps[j] != ':';j++)
    		tmps2 += tmps[j];
    	seniorinfo[i].name = tmps2;
    	tmps2 = "";
    	//跳过冒号
    	j++;
    	//跳过空格
    	for (;tmps[j] == ' ';j++);
    	//读入每一条构成信息
    	while (j < tmps.size())
    	{
    		//分离出基础神器名字
    		for (;tmps[j] != ' ';j++)
    			tmps2 += tmps[j];
    		//跳过空格
    		for (;tmps[j] == ' ';j++);
    		//分离出基础神器数量
    		for (;j < tmps.size() && tmps[j] != ',';j++)
    			tmps3 += tmps[j];
    		//转为整型
    		seniorinfo[i].basics.push_back({list_si[tmps2],toint(tmps3)});
    		tmps2 = "";
    		tmps3 = "";
    		//跳过逗号
    		j++;
    		//跳过空格
    		for (;j < tmps.size() && tmps[j] == ' ';j++);
		}
	}
	process_senior();
	//购买信息
	while (q--)
	{
		scanf("%d",&tmpn);
		cin >> tmps;
		memberrecord[tmpn][list_si[tmps]]++;
		//处理合并（必须在读入的过程中进行合并）
		for (int i = 1;i <= k;i++)
		{
			//枚举每一种高级神器
			for (int j = 1;j <= m;j++)
			{
				//枚举每一项基础神器，取能够买的最小值
				int buynum = 10000;
				for (auto p = seniorinfo[j].basics.begin();p != seniorinfo[j].basics.end();p++)
					buynum = min(buynum,memberrecord[i][p->first] / (p->second));
				//减少基础神器
				for (auto p = seniorinfo[j].basics.begin();p != seniorinfo[j].basics.end();p++)
					memberrecord[i][p->first] -= buynum * (p->second);
				//增加高级神器
				memberrecord[i][list_si[seniorinfo[j].name]] += buynum;
			}
		}
	}
	//输出
	for (int i = 1;i <= k;i++)
	{
		int cnt = 0;
		for (auto p = memberrecord[i].begin();p != memberrecord[i].end();p++)
			if (p->second > 0) cnt++;
		printf("%d\n",cnt);
		for (auto p = memberrecord[i].begin();p != memberrecord[i].end();p++)
			if (p->second > 0)
			{
				cout << list_is[p->first];
				printf(" %d\n",p->second);
			}
	}
}
```
最后，orz 一下 2023gdgz01 大佬，代码写的比我短 $114514$ 倍，跑得还比我快 $114514$ 倍。

---

