# PFAST Inc.

## 题目描述

When little Petya grew up and entered the university, he started to take part in АСМ contests. Later he realized that he doesn't like how the АСМ contests are organised: the team could only have three members (and he couldn't take all his friends to the competitions and distribute the tasks between the team members efficiently), so he decided to organize his own contests PFAST Inc. — Petr and Friends Are Solving Tasks Corporation. PFAST Inc. rules allow a team to have unlimited number of members.

To make this format of contests popular he organised his own tournament. To create the team he will prepare for the contest organised by the PFAST Inc. rules, he chose several volunteers (up to 16 people) and decided to compile a team from them. Petya understands perfectly that if a team has two people that don't get on well, then the team will perform poorly. Put together a team with as many players as possible given that all players should get on well with each other.

## 样例 #1

### 输入

```
3 1
Petya
Vasya
Masha
Petya Vasya
```

### 输出

```
2
Masha
Petya
```

## 样例 #2

### 输入

```
3 0
Pasha
Lesha
Vanya
```

### 输出

```
3
Lesha
Pasha
Vanya
```

# 题解

## 作者：CarroT1212 (赞：2)

*1500 评蓝，不愧是谷民。

首先看到 $1 \le n \le 16$，很容易想到二进制枚举。

于是我们就可以枚举能参赛的人分别是谁，每枚举出一组人就扫一遍有敌对关系的人，看看这几对人有没有同时出现在枚举出的人中，有的话就直接退出，因为这组人不满足条件。如果都没有出现就尝试更新答案，最后的答案就是所有满足条件的解中的最大人数。

另外是一些细节问题：

二进制枚举记录每个人有没有被选择时，由于后面看是否有敌对关系的时候需要直接根据字符串进行查询，直接用数组开桶记录还需要到输入的字符串中一个个找看看所找的字符串到底在哪个位置，比较麻烦，还会影响程序效率，我们就可以使用 map 记录（`map <string,bool> mp;`）。

使用 map 还有一个好处：map 有自动排序功能，这样我们记录答案时就不用再费心思排序一遍，只用在记录的时候按它排序的顺序记录就可以了。

------------

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rnt register long long
using namespace std;
const ll N=27,M=407;
ll n,m,maxn=-1;
string a[N],b[M][2];
map <string,bool> mp;
vector <string> v; //答案人数不固定，可使用 vector 记录
void dfs(ll flr,ll at) {
	if (flr>n) {
		for (rnt i=1;i<=m;i++) if (mp[b[i][0]]&&mp[b[i][1]]) return; //选中的人是否有敌对关系
		if (at>maxn) { //可以更新答案
			v.clear();
			for (auto i:mp) if (i.second) v.push_back(i.first);
			maxn=at;
		}
		return;
	}
	mp[a[flr]]=1;
	dfs(flr+1,at+1);
	mp[a[flr]]=0;
	dfs(flr+1,at);
}
int main() {
	cin>>n>>m;
	for (rnt i=1;i<=n;i++) cin>>a[i];
	for (rnt i=1;i<=m;i++) cin>>b[i][0]>>b[i][1];
	dfs(1,0);
	cout<<maxn<<endl;
	for (auto i:v) cout<<i<<endl;
	return 0;
}
```

---

## 作者：404Not_Found (赞：2)

看到 $n \leq 16$ 的数据，不是搜索就是状压。~~因为这是一道蓝题所以~~我选了状压。

思路很简单，暴力枚举子集，筛去不合法的选最大即可。**这里每个状态的第 $i$ 位为 $1$ 表示第 $i$ 个位置的人合法。**

关于如何存储两个人之间的关系，一开始当然想到的是并查集，但这里是不能在一个集合里，带权并查集也不会写。后面又想到用 map，但这里是二维状态也不会搞（瞟了眼题解发现嵌套一下就可以了。后来又想到哈希，但是数组开不下。最后发现其实用编号代替就好了）。

最后，**“输出的名字按字典序排列”**，一定要记得 sort 啊！

时间复杂度为 $O(2^nn^2)$，能通过本题。

#  Code

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int g[20][20];
string s[20];
int n,m;
int hashs(string tmp)//求编号
{
    for(int i=0;i<n;i++)
        if(s[i]==tmp) return i;
}
int count_one(int x)//统计二进制下一的个数
{
    int tot=0;
    for(;x;x&=x-1,tot++);
    return tot;
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>s[i];
    sort(s,s+n);//记得排序！！！
    for(int i=1;i<=m;i++)
    {
        string a,b;
        cin>>a>>b;
        int x=hashs(a),y=hashs(b);
        g[x][y]=g[y][x]=1;
    }
    int ans=0;
    for(int i=0;i<(1<<n);i++) 
    {
        int flag=1;
        for(int j=0;j<n;j++)
            if(i&(1<<j))
                for(int k=j+1;k<n;k++)
                    if((i&(1<<k))&&g[j][k]==1)
                    {
                        flag=0;
                        break;
                    }
        if(flag==1)
        {
            if(count_one(i)>count_one(ans))
            ans=i;
        }
    }
    cout<<count_one(ans)<<endl;
    for(int i=0;i<n;i++)
        if(ans&(1<<i)) cout<<s[i]<<endl;
    return 0;
}
```
感谢观看。

---

## 作者：Kyl_in_2024 (赞：1)

~~有没有人是因为题号进来的。~~

**前言**

一开始没有看到数据范围，于是错误的以为一个人只会和一个人发生矛盾……结果可想而知。

**思路**

众所周知：$1 \le n \le 16$ 的数据范围可以用 $O(2^{n})$ 算法，所以我们可以直接二进制枚举每个人来不来然后判断。二进制枚举很好写，但是位数判断太麻烦了，所以我用的是 `dfs`。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[18];
bool v[18];
int q1[500],q2[500];
int n,m,ansk=-1;
bool ans[18];
void check(){
	for(int i=1;i<=m;i++){
		if(v[q1[i]]&&v[q2[i]]) return ;
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(v[i]) sum++;
	}
	if(sum>ansk){
		ansk=sum;
		for(int i=1;i<=n;i++) ans[i]=v[i];
	}
}
void dfs(int i){
	if(i==n+1){
		check();
		return ;
	}
	v[i]=1;
	dfs(i+1);
	v[i]=0;
	dfs(i+1);
}
map<string,int>mp;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) mp[a[i]]=i;
	for(int i=1;i<=m;i++){
		string t1,t2;
		cin>>t1>>t2;
		q1[i]=mp[t1];
		q2[i]=mp[t2];
	}
	dfs(1);
	cout<<ansk<<"\n";
	for(int i=1;i<=n;i++){
		if(ans[i]) cout<<a[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：Sexy_Foxy (赞：1)

## 题意：

给你一堆字符串，再给出哪个字符串不能和哪个字符串一起在车上，求最多能有多少个字符串在车上。

## 解题思路：

首先，看懂题意后首先可能会想到 **并查集** 算法，但是看了看美丽的数据范围（$1≤n≤16,0≤m≤n\times(n-1)/2$) 以后，就想到了暴力，但具体怎么个暴力法，本蒟蒻接下来会一一讲解。

### 第一步：

对于每个字符串，它只有上车和不上车两种选择，很容易就像到了二进制枚举，再结合数据范围 （$1≤n≤16$） ，时间复杂度只有 $O(2^n)=2^{16}=65536$ ，完全不会超时，那么第一步完成。

### 第二步：

想到了具体方法又怎么实现呢？如果对每个字符串都存储其仇人数量，不仅会耗费大量空间，在枚举时还会有很多不必要的判断，导致时间复杂度上升。虽然这种方法也能过，但是并不是最优解。有没有更有的办法呢？有的！

首先，假设当前为第 $i$ 次判断，则当前能上车的人数为 **$i\bmod2$的值**
$+$**第$i÷2$次判断时上车的人数** 。然后，判断每对不能一起在车上的字符串是否一起上车，这样，只用遍历一次仇人对数$m$求可以完成判断了。最后，输出答案，结束。

### 第三步：

前两步想清楚了还不行，信息是要打代码的。

#### 定义部分：

```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int hate,name; //记录仇人的结构体
};
vector<node>can_not; //记录仇人对数
map<string,int>people; //记录字符串编号，方便枚举
string name[18];
int n,m;
int all[65600]; //第二步说的当前判断能上车的人数
vector<string>print; //最后输出的字符串
```

#### 输入+预处理：

```
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++)
{
	cin>>name[i];
	people[name[i]]=i-1; //记录编号
}
for(int i=1;i<=m;i++)
{
	string x,y;
	cin>>x>>y;
	node xy;
	xy.name=people[x],xy.hate=people[y]; //存入结构体
	can_not.push_back(xy); //存入记录仇人的数组中
}
```

#### 二进制枚举：

```
int ans=0;
for(int i=1;i<(1<<n);i++) //(1<<n)表示2的n次方
{
	all[i]=((i%2)+all[i/2]); //第二步有讲解
	bool can=true;
	for(int j=0;j<can_not.size();j++)
	{
		if((i>>can_not[j].name)&1&&(i>>can_not[j].hate)&1) //判断仇人是否一起上车
		{
			can=false;
			break;
		}
	}
	if(can&&all[i]>all[ans]) //贪心求最多
	{
		ans=i;
	}
}
```

#### 输出答案：

```
printf("%d\n",all[ans]); //输出最多能有多少人
for(int i=1;i<=n;i++)
{
	if((ans>>people[name[i]])&1) //判断谁要上车
	{
		print.push_back(name[i]);
	}
}
sort(print.begin(),print.end()); //按字典序排序
for(int i=0;i<print.size();i++)
{
	cout<<print[i]<<endl; //输出人名
}
return 0; //完结撒花

```

## 完整的Code：

接下来时不带注释的完整代码（~~方便某些人使用 **CV** 算法~~）：

```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int hate,name;
};
vector<node>can_not;
map<string,int>people;
string name[18];
int n,m;
int all[65600];
vector<string>print;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		cin>>name[i];
		people[name[i]]=i-1;
	}
	for(int i=1;i<=m;i++)
	{
		string x,y;
		cin>>x>>y;
		node xy;
		xy.name=people[x],xy.hate=people[y];
		can_not.push_back(xy);
	}
	int ans=0;
	for(int i=1;i<(1<<n);i++)
	{
		all[i]=((i%2)+all[i/2]);
		bool can=true;
		for(int j=0;j<can_not.size();j++)
		{
			if((i>>can_not[j].name)&1&&(i>>can_not[j].hate)&1)
			{
				can=false;
				break;
			}
		}
		if(can&&all[i]>all[ans])
		{
			ans=i;
		}
	}
	printf("%d\n",all[ans]);
	for(int i=1;i<=n;i++)
	{
		if((ans>>people[name[i]])&1)
		{
			print.push_back(name[i]);
		}
	}
	sort(print.begin(),print.end());
	for(int i=0;i<print.size();i++)
	{
		cout<<print[i]<<endl;
	}
	return 0;
}
```

## 后记：

此题解为本蒟蒻的第一篇题解，若有错误请私聊，谢谢！！！

### qwq

---

## 作者：xiaomuyun (赞：1)

- [Luogu 传送门](https://www.luogu.com.cn/problem/CF114B)
- [CodeForces 传送门](https://codeforces.com/problemset/problem/114/B)

## 思路分析

因为 $1\le n\le 16$，所以可以考虑 $\mathcal{O}(2^n)$ 枚举参加的方案。存敌对关系的部分我选择了 `map<pair<string,string>,bool>`，不过当然也可以用 `map` 做哈希代替每个名字然后用二维 `bool` 数组维护每个敌对关系。每次 `dfs` 出一个方案 $\mathcal{O}(n^2)$ 检查答案是否可行即可，因为 $n$ 很小，所以不用太担心时间复杂度。

然后字典序的话，因为 `algorithm` 库的 `sort` 函数可以直接给 `string` 数组按照字典序排序，所以直接用 `sort` 即可。

## 代码实现

```cpp
#include<algorithm>
#include<iostream>
#include<utility>
#include<string>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
int n,m,mx=0;
string s[20],res[20],t[20];
map<pair<string,string>,bool> flag;
void dfs(int x,string a[],int len){
	if(x>n){
		if(len<=mx) return ;//怎么样都不是最优解了，直接return即可
		for(int i=1;i<=len;++i){
			for(int j=i+1;j<=len;++j){
				if(flag[make_pair(a[i],a[j])]==1) return ;//如果存在敌对关系说明答案不可行
			}
		}
		mx=len;
		for(int i=1;i<=n;++i) res[i]=a[i];
		return ;
	}
	dfs(x+1,a,len);
	a[++len]=s[x];//选或不选
	dfs(x+1,a,len);
	return ;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) cin>>s[i];
	for(int i=1;i<=m;++i){
		string a,b;
		cin>>a>>b;
		flag[make_pair(a,b)]=flag[make_pair(b,a)]=1;
	}
	dfs(1,t,0);
	printf("%d\n",mx);//输出答案
	sort(res+1,res+1+mx);//直接排序
	for(int i=1;i<=mx;++i) cout<<res[i]<<'\n';
	return 0;
}
```

---

## 作者：HMZHMZHMZ (赞：1)

## 题意
给定两个个正整数 $ n $ ， $ m $ ，表示有 $ n $ 个人可以参加比赛，$ m $ 对人之间有敌对关系，两个有敌对关系之间的人不能同时参加比赛，问最多有多少人可以参赛。

## 思路

发现 $ n \leq 16 $ ，自然想到搜索。考虑枚举最多有多少个人能参赛，对于每种情况都深搜一次即可，然后判断是否可行 ， $ n ^ 2 $ 的复杂度就能过。

注意最后不仅要输出最大人数，还要输出人名，并按照字典序排序。

复杂度是 $ O ( n ^ 3 \times 2 ^ n ) $ ，显然能过。(如果开 ` map ` 存每个名字的编号则会多一个 $ \log n $ ，不过还是能过的。)

## 代码

自认为写的挺清晰的，就不加注释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
bool flag;
string id[N];
vector<string> v;
map<string,int> mp;
int ck[N][N],n,m,used[N];
inline bool check(){
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=n;++j){
            if(ck[i][j]&&used[i]&&used[j]) return 0;
        }
    }
    for(register int i=1;i<=n;++i) if(used[i]) v.push_back(id[i]);
    return 1;
}
void dfs(int x,int tot){
    if(tot<0) return ;
    if(x>n){
        if(tot==0) flag=check();
        return ;
    }
    used[x]=1;
    dfs(x+1,tot-1);
    if(flag) return ;
    used[x]=0;
    dfs(x+1,tot);
    if(flag) return ;
}
inline bool cmp(string a,string b){
    return a<b;
}
int main(){
    cin>>n>>m;
    for(register int i=1;i<=n;++i){
        cin>>id[i];
        mp[id[i]]=i;
    }
    for(register int i=1;i<=m;++i){
        string x,y;
        cin>>x>>y;
        ck[mp[x]][mp[y]]=ck[mp[y]][mp[x]]=1;
    }
    for(register int i=n;i>=1;--i){
        v.clear();
        dfs(1,i);
        if(flag){
            printf("%d\n",i);
            sort(v.begin(),v.end(),cmp);
            for(register int j=0;j<i;++j) cout<<v[j]<<endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：WinterRain208 (赞：1)

CF114B 【PFAST Inc.】

看到晦涩难懂的题面我绝望了。

看到美丽的数据范围我又笑了。

$n<=16$

那明显可以暴搜，$dfs$枚举子集即可，我在判断最优解上和输出上被卡了$n$次。

#### $UPDATE1.9$

写的太水了，做一些补充，在代码上添加一些注释。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=16+5;

string a[N],x,y;
int n,m,M=-1;
map < string , map < string , int > > mm; //敌对关系我们用邻接矩阵来存
bool vis[N];//判断是否选择

void dfs(int deep,int mod){//深搜
	if(deep>n+1)return;
	if(deep==n+1){
		int tot=0,f=1;
		F(i,1,n)tot+=vis[i];
		F(i,1,n)//判断是否符合没有敌对关系
			F(j,i+1,n)
				if(vis[i]&&vis[j])
					if(mm[a[i]][a[j]]){
						f=0;
						break;
					}
		if(f){
			if(mod){
				int tot=0;
				F(i,1,n)tot+=vis[i];
				if(tot!=M)return;//如果非最优解则跳过
				printf("%d\n",M);
				string res[N];
				F(i,1,17)res[i]="0";
				int pos=1;
				F(i,1,n)
					if(vis[i])res[pos++]=a[i];
				sort(res+1,res+pos);//字典序输出，用维克多也可以
				pos=1;
				while(res[pos]!="0"){
					cout<<res[pos]<<endl;
					pos++;//输出
				}
				exit(0);//任意解，直接结束程序
			}
			else if(mod==0)
				M=max(M,tot);//打擂台
		}
	}
	vis[deep]=true;
	dfs(deep+1,mod);//继续下一层
	vis[deep]=false;//回溯搜索
	dfs(deep+1,mod);
}
int main(){
	scanf("%d%d",&n,&m);
	F(i,1,n)
		cin>>a[i];
	F(i,1,m){
		cin>>x>>y;
		mm[x][y]=mm[y][x]=1;//邻接矩阵记录
	}
	dfs(1,0);//状态1求解
	dfs(1,1);//状态2输出
    //这个部分可以优化，不用两次搜，但数据允许我就懒得写了
    return 0;
}

```

一道暴力出奇迹的题目。

$wtrl$

---

## 作者：Igallta (赞：0)

这道题我们注意到数据范围，$1 \leqslant n \leqslant 16$ 所以这道题爆搜就算是 $\Omicron(2^n)$、$\Omicron(n^6)$ 这样的满级复杂度也可以水过去！所以我认为评黄都多了……

回到正题。

我们只需要枚举每个人去还是不去就可以了。

这个人去了之后看有哪些人不去了，进行标记即可。

对于我是怎么记录这些人的：我按照输入的先后顺序进行记录。

比如输入 `a b c`，那么我会将 `a` 记作 $1$，`b` 记作 $2$，以此类推。（这里使用 `map` 进行双向记录）

对于敌对关系，我选用了 `unordered_set` 进行存储。（因为它比较快，我还是害怕我的代码会 TLE）

对于 dfs，我选用了数组去记录状态。$0$ 代表可以去但是不去；$1$ 代表有敌对关系的人参加了比赛，不参加；$2$ 代表可以去而且去了。

我的状态数组是函数的形参。类似这样：`dfs(int a,int b[])`。

dfs 终止条件：$i > n$。（这里的 $i$ 指的是遍历到第几位了）

终止之后先统计数组中 $2$ 的个数，如果大于 $ans$，那么就先清空答案数组，然后记录 $2$ 的那些人就行了。

注意答案数组记录的是字符串，也就是说最后把答案数组 sort 一下就可以了。（sort 可以排字典序）

然后输出 $ans$ 和答案数组就行了。

---

## 作者：bigclever (赞：0)

## 思路：
可以发现 $1 \le n \le 16$，那么我们可以暴力枚举每个人到底是选还是不选，枚举出一种方案后，判断该方案中有没有敌对关系的两个人。如果没有，就更新答案。时间复杂度最坏情况下 $O(2^nmn)$，可以通过此题。

**注意**：输出的名字要按字典序排列，我采用的解决方法是存答案时用 set。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
string s[20],a[400],b[400];
map<string,int> id;//给每个人映射一个编号
bool vis[20];
set<string> cho;//用set可以实现自动排序
bool check(){//判断选取的人中有没有敌对关系的两个人
	for(int i=1;i<=m;i++)
		if(vis[id[a[i]]]&&vis[id[b[i]]])return false;
	return true;
}
void dfs(int k,int cnt){
	if(k>n){
		if(cnt>ans&&check()){
			ans=cnt,cho.clear();//更新最优解
			for(int i=1;i<=n;i++)
				if(vis[i])cho.insert(s[i]);
		}
		return;
	}
    //选或不选两种情况各枚举一遍
	vis[k]=true,dfs(k+1,cnt+1);
	vis[k]=false,dfs(k+1,cnt);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i],id[s[i]]=i;
	for(int i=1;i<=m;i++)cin>>a[i]>>b[i];
	dfs(1,0),cout<<ans<<endl;
	for(auto i:cho)cout<<i<<endl;
	return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 分析题目
根据题意中 $1 \leq n \leq 16$ 得知暴力搜索的 $O(2^n)$ 的时间复杂度是在可接受范围以内的。

那么考虑题目中 **有敌对关系的人** 如何处理。

建一个 map 存储当前搜索中选了那些人，在到达搜索边界时判断当前答案是否符合要求。如符合题意，则判断人数与 $ans$ 之间的大小关系。最后输出答案数和选择的人即可。

### 温馨提示

如果用的是 map 存储敌对关系的人。那么如果一个人与多个人是有敌对关系的，就会出错。因为这会将 map 里的值 **覆盖** ，从而导致结果出错。

所以代码中存储敌对关系用到的是普通二维数组。

### 代码

```cpp
#include<iostream>

#include<vector>

#include<unordered_map>

#include<algorithm>

using namespace std;
const int N = 1e5;
int n, m, res;
string s[N], x, y;
string a[N][2];
unordered_map < string, int > vis;
vector < string > b;
void dfs(int id, int sum, vector < string > & ans) {
    if (id == n + 1) {
        for(int i=1;i<=m;i++){
            if(vis[a[i][0]]+vis[a[i][1]]==2) return;
            //如果两个相互敌对的人存在答案中，即标记数组中两人的值相加是等于2的。
        }
        if (res < sum) {
            b.clear();
            res = sum;
            for (int i = 0; i < ans.size(); i++) {
                if (vis[ans[i]] == 1)//这里也是一个易错点，要记得判断是否在标记数组中。
                    b.push_back(ans[i]);
            }
        }
        return;
    }
    vector < string > QwQ = ans;
    dfs(id + 1, sum, QwQ);
    vis[s[id]] = 1;
    QwQ.push_back(s[id]);
    dfs(id + 1, sum + 1, QwQ);
    vis[s[id]] = 0;
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    vector < string > ans;
    dfs(1, 0, ans);
    cout << res << '\n';
    sort(b.begin(), b.end());//按字典序排
    for (int i = 0; i < b.size(); i++) {
        cout << b[i] << '\n';
    }
    return 0;
}
```


---

## 作者：HadrianZhang (赞：0)

# 思路

注意到 $n≤16$，暴力二进制枚举即可。

检查的话，建立一个字符串到下标的映射，然后逐条规则检查是否矛盾。

注意输出要按字典序，所以在输入之后就要排序，再建立映射。

时间复杂度 $O(2^nm)$，可以通过本题。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'
int n,m,ma;
bool vis[20];
string s[20];
vector<int>vec,ans;
vector<pair<string,string>>v;
unordered_map<string,int>p;
bool check()
{
	for(int i=0;i<m;i++)
	{
		string a=v[i].first,b=v[i].second;
		if(vis[p[a]]&&vis[p[b]]) return 0;
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
		p[s[i]]=i;
	for(int i=1;i<=m;i++)
	{
		string a,b;
		cin>>a>>b;
		v.push_back({a,b});
	}
	for(int i=0;i<(1<<n);i++)
	{
		int cnt=0;
		vec.clear();
		memset(vis,0,sizeof vis);
		for(int j=0;j<n;j++)
			if((i>>j)&1) vis[j+1]=1,cnt++,vec.push_back(j+1);
		if(check()&&cnt>ma) ma=cnt,ans=vec;
	}
	cout<<ma<<endl;
	for(int i=0;i<ans.size();i++)
		cout<<s[ans[i]]<<endl;
	return 0;
}

---

## 作者：Su_Zipei (赞：0)

观察数据，数据范围只有$16$，可以暴力枚举哪一个在集合里边，然后暴力判断即可，挺暴力的一个题，通过状压或者搜索都可以实现。

不过要注意通过搜索实现的时候对于每个人的标记要多层标记，不能只是赋值成$1,0$，因为一个人可能会被多个人限制。

```cpp
/*
#include<map>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=30;
string s[N],ans[N],q[N];
map<string,int> mp;
int ban[N][N],res,tot;
int n,m,vis[N];
void dfs(int u){
	if(u==n+1){
		if(tot>res){
			res=tot;
			for(int i=1;i<=tot;i++)
				ans[i]=q[i];
		}
		return;
	}
	dfs(u+1);
	if(!vis[u]){
		for(int i=1;i<=n;i++)
			if(ban[u][i])vis[i]++;
		q[++tot]=s[u];
		dfs(u+1);
		--tot;
		for(int i=1;i<=n;i++)
			if(ban[u][i])vis[i]--;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		cin >> s[i];
		mp[s[i]]=i;
	}
	for(int i=1;i<=m;i++){
		string now1,now2;
		cin >> now1 >> now2;
		int u=mp[now1],v=mp[now2];
		ban[u][v]=ban[v][u]=1;
	}
	dfs(1);
	cout << res << '\n';
	sort(ans+1,ans+res+1);
	for(int i=1;i<=res;i++)
		cout << ans[i] << '\n';
	return 0;
}

```

---

## 作者：_iridescent (赞：0)

### 思路

可以考虑使用位运算的方法来枚举所有可能的团队组合。

对于 $n$ 个志愿者，可以用一个 $n$ 位的二进制数来表示一个团队，其中每一位表示对应志愿者是否在团队中，对于每一个可能的团队，检查其中的每一对志愿者是否存在冲突，如果存在冲突，则标记该团队为无效团队。

最后，我们可以通过从 $0$ 到 $2^n-1$ 的二进制数进行枚举，可以得到所有可能的团队组合，下面是代码核心部分的解析，如果还有疑问可以再看看结尾部分的代码。

* 外层循环遍历所有可能的组合，从空团队开始，逐步尝试添加志愿者。

* 内层循环用于检查当前团队是否符合条件，包括团队成员之间是否有不和谐关系。

* 如果团队有效且人数超过之前记录的最大团队人数，则更新最大团队人数和团队成员名字。
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define endl '\n'
using namespace std;
int n,m,maxs;
string mem[205];// 总成员列表
string en[205][2];// 敌对关系
string mt[205];// 最大团队
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>mem[i];
    for(int i=1;i<=m;i++)cin>>en[i][0]>>en[i][1];
    for(int i=0;i<(1<<n);i++){
        string t[205];// 当前团队
        bool fl=true;// 冲突标记
        int nows=0;// 当前成员数量
        for(int j=1;j<=n;j++){
            if(i&(1<<(j-1)))t[++nows]=mem[j];
        }
        for(int j=1;j<=nows;j++){// 检查是否有冲突
            for(int k=j+1;k<=nows;k++){
                for(int l=1;l<=m;l++){
                	// 如果存在冲突，更新标记
                    if((t[j]==en[l][0]&&t[k]==en[l][1])||(t[j]==en[l][1]&&t[k]==en[l][0])){
                        fl=false;
                        break;
                    }
                }
                if(!fl)break;
            }
            if(!fl)break;
        }
        if(fl&&nows>maxs){// 更新最大团队
            maxs=nows;
            for(int j=1;j<=nows;j++)mt[j]=t[j];
        }
    }
    sort(mt+1,mt+maxs+1);// 注意要用字典序输出
    cout<<maxs<<endl;
    for(int i=1;i<=maxs;i++)cout<<mt[i]<<endl;
    return 0;
}



```

---

## 作者：_ayaka_ (赞：0)

### 思路
很简单的一道题。

首先 $0\le n\le16$，$O(2^n)$ 可过，所以考虑暴力枚举（~~不用状压是因为黄题不配~~）。

只需要用深搜选择每个点取不取，如果取就判定一下取过的有没有跟这个点冲突的就可以了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, h[200][200], vis[200], cnt;
map<string, int> q;
string s[200], x, y, ans[200], c[200];
void dfs(int d, int k) {
	if (d == n + 1) {
		if (k > cnt) {
			cnt = k;
			for (int i = 1; i <= cnt; i++) ans[i] = c[i];
		}
		return;
	}
	dfs(d + 1,k);
	for (int i = 1; i <= n; i++) {
		if (vis[i]&&h[i][d]) {
			return ;
		}
	}
	c[k+1] = s[d];
	vis[d]=1;
	dfs(d + 1,k+1);
	vis[d]=0; 
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		q[s[i]] = i;
	}
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		h[q[x]][q[y]] = 1;
		h[q[y]][q[x]] = 1;
	}
	dfs(1, 0);
	cout<<cnt<<"\n";
	sort(ans+1,ans+cnt+1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

把敌对关系连边会发现要找最大独立集。

无向图最大独立集好像是 np 的，但是看数据范围 $1\le n\le 16$ 告诉我们直接暴力就可以。

所以我们枚举选择的集合然后 check 能不能满足所有要求即可。

给代码，用了一些优化枚举的方法，~~虽然没什么用就是了~~。[跑得很快](https://www.luogu.com.cn/record/146835019)，目前居于最优解第二，人菜。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n,m,ans=0,cnt[(1<<16)+5],a[400][2];
string s[20],tx,ty;
map<string,int>mp;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	sort(s+1,s+n+1);//在一开始就排好序方便后面直接输出
	for(int i=1;i<=n;i++)mp[s[i]]=i;
	for(int i=1;i<=m;i++){
		cin>>tx>>ty;
		a[i][0]=mp[tx]-1;
		a[i][1]=mp[ty]-1;
	}
	for(int i=0;i<(1<<n);i++){
		cnt[i]=cnt[i>>1]+(i&1);//用递推的方法能让 popcount 变成线性
		if(cnt[i]<=cnt[ans])continue;//答案更劣可以直接跳过循环枚举
		for(int j=0;j<=m;j++){
			if(j&&(i&(1<<a[j][0]))&&(i&(1<<a[j][1])))break;
			if(j==m)ans=i;
		}
	}
	cout<<cnt[ans]<<'\n';
	for(int i=1;i<=n;i++)if(ans&(1<<(i-1)))cout<<s[i]<<'\n';
	return 0;
} 
```

---

## 作者：RioFutaba (赞：0)

# 题意
有 $n$ 个人，给出他们的名字。他们会有 $m$ 个冲突，选出一些人使他们互不冲突，按字典序输出他们的名字。

数据范围：$1 \le n \le 16$，$1 \le m \le \frac{n \times (n-1)}{2}$。
# 思路

因为 $n \le 16$，所以可以使用回溯算法枚举，再检查一下是否有冲突。

每个人只有选或者不选两种情况，所以开一个 $res$ 数组记录，$res[i]=0$ 表示不选，$res[i]=1$ 表示选。检查时枚举所有人，如果有两个人都被选且他们之间有冲突，那么这种选择就不合法。否则统计答案。

最后输出记得排序。

具体实现的一些细节已经写在注释里了（为了方便进行了离散化）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=16+5;
int n,m,tot,ac;//ac记录最多的人数 
string a[maxn];//编号对应的名字 
map<string,int> id;//用map储存名字对应的编号 
bool f[maxn][maxn],res[maxn],ans[maxn];//f[i][j]表示i和j是否有冲突 
bool check()
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(res[i] && res[j] && f[i][j]) return 0;//都被选上且有冲突 
	return 1;
}
void solve(int cur,int cnt)
{
	if(cur>n)
	{
		if(cnt>ac && check())
		{
			for(int i=1;i<=n;i++) ans[i]=res[i];//统计答案 
			ac=cnt;
		}
		return ;
	}
	res[cur]=1;
	solve(cur+1,cnt+1);
	res[cur]=0;
	solve(cur+1,cnt);//选或不选都试一下 
}	
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin >> s;
		id[s]=++tot;//记录编号 
		a[tot]=s;//记录名字 
	}
	for(int i=1;i<=m;i++)
	{
		string s,t;
		cin >> s >> t;
		f[id[s]][id[t]]=f[id[t]][id[s]]=true;//记录冲突 
	}
	solve(1,0);//开始dfs 
	cout << ac << endl;//输出人数 
	vector<string> v;
	for(int i=1;i<=n;i++) if(ans[i]) v.push_back(a[i]);//将答案扔进一个vector里 
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++) cout << v[i] << endl;//排序后输出 
	return 0;
}
```
总体来说这题是一道不错的 dfs 练习题，适合新手。

---

