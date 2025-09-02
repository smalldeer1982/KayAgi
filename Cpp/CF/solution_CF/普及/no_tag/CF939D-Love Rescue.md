# Love Rescue

## 题目描述

Valya and Tolya are an ideal pair, but they quarrel sometimes. Recently, Valya took offense at her boyfriend because he came to her in t-shirt with lettering that differs from lettering on her pullover. Now she doesn't want to see him and Tolya is seating at his room and crying at her photos all day long.

This story could be very sad but fairy godmother (Tolya's grandmother) decided to help them and restore their relationship. She secretly took Tolya's t-shirt and Valya's pullover and wants to make the letterings on them same. In order to do this, for one unit of mana she can buy a spell that can change some letters on the clothes. Your task is calculate the minimum amount of mana that Tolya's grandmother should spend to rescue love of Tolya and Valya.

More formally, letterings on Tolya's t-shirt and Valya's pullover are two strings with same length $ n $ consisting only of lowercase English letters. Using one unit of mana, grandmother can buy a spell of form $ (c_{1},c_{2}) $ (where $ c_{1} $ and $ c_{2} $ are some lowercase English letters), which can arbitrary number of times transform a single letter $ c_{1} $ to $ c_{2} $ and vise-versa on both Tolya's t-shirt and Valya's pullover. You should find the minimum amount of mana that grandmother should spend to buy a set of spells that can make the letterings equal. In addition you should output the required set of spells.

## 说明/提示

In first example it's enough to buy two spells: ('a','d') and ('b','a'). Then first letters will coincide when we will replace letter 'a' with 'd'. Second letters will coincide when we will replace 'b' with 'a'. Third letters will coincide when we will at first replace 'b' with 'a' and then 'a' with 'd'.

## 样例 #1

### 输入

```
3
abb
dad
```

### 输出

```
2
a d
b a```

## 样例 #2

### 输入

```
8
drpepper
cocacola
```

### 输出

```
7
l e
e d
d c
c p
p o
o r
r a
```

# 题解

## 作者：chufuzhe (赞：2)

首先，要使两个字符串相同，字符串的每一位肯定是相同的，所以可以一位一位的处理，如果不一样，就把其中一个全部变为另一个，每一位处理一遍，最小花费就是操作的次数，操作步骤就是每次操作的两个字符。

那怎么判断两个字符一不一样呢？我们可以运用并查集。一开始，每个字符都是自己为一个集合。每把一个字符变成另一个字符，就把这个字符加入变成的字符的集合中。如果两个字符在一个集合中，就是一样的，反之则不一样。‘’

```cpp
#include<bits/stdc++.h>
using namespace std;
char c1[100005], c2[100005];
char s1[100005], s2[100005];
char fa[205]; //f[i]表示ASCII为i的字符的父亲
void init(){ //初始化
	for(int i = 0; i < 26; i++)
		fa[i + 97] = char(i + 97); //自己为一个集合
	return ;
}
int find(int x){ //找祖先
    if(fa[x]==x) return x; //找到祖先了
    fa[x]=find(fa[x]); //防止并查集退化成一条链
    return fa[x]; //返回祖先
}
bool query(char x, char y){ //判断x和y在不在一个集合中
	return find(x)==find(y); //1表示在，0表示不在
}
void merge(char x, char y){ //合并x和y的集合
	fa[find(x)] = fa[y];
	return ;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, cnt = 0;
	cin >> n; //输入
	for(int i = 1; i <= n; i++)
		cin >> c1[i];
	for(int i = 1; i <= n; i++)
		cin >> c2[i];
	init(); //初始化
	for(int i = 1; i <= n; i++){
		if(!query(c1[i], c2[i])){ //判断两个字符一不一样
			merge(c1[i], c2[i]); //合并
			cnt++; //记录答案
			s1[cnt] = c1[i];
			s2[cnt] = c2[i];
		}
	}
	cout << cnt << endl; //输出
	for(int i = 1; i <= cnt; i++)
		cout << s1[i] << ' ' << s2[i] << endl;
	return 0;
}

```


---

## 作者：ahawzlc (赞：2)

思路：并查集

----

读入数据，题目中要求对字符串 A 中字母进行变换，使其与字符串 B 相同。

首先我们可以知道，如果字母 a 可以转换成字母 b，字母 b 可以转换成字母 c ，那么字母 a 可以转换成字母 c 。

啊，并查集```find()```的气息。

那么我们只需要遍历一遍两个字符串，如果两个字符串当前位置的字符不在一个集合内，那么把它们合并到一个集合里，并且记录答案，最后输出**记录了几次答案**以及**记录的答案**就能过掉这个题了。

Codeing Time

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int N=100005;
int n,t;
char ans[N][2],a[N],b[N];
map<char,char> f;
char find(char x) {
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
bool merge(char x,char y) {
	x=find(x);
	y=find(y);
	if(x!=y) f[x]=y;
	else return 0;
	return 1;
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(char i='a';i<='z';i++) f[i]=i;
	for(int i=1;i<=n;i++) {
		if(merge(a[i],b[i])) {
			ans[++t][0]=b[i];
			ans[t][1]=a[i];
		}
	}
	cout<<t<<endl;
	for(int i=1;i<=t;i++) cout<<ans[i][1]<<' '<<ans[i][0]<<endl;
	return 0;
}

```

~~被黄学长拿来当考试题的题能不是好题吗~~

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF939D)

## 题意
给定两个长度均为 $n$ ，全由小写字母构成的字符串 $S$ 和 $T$，你可以对它们进行若干次改变字母的魔法，每个 ($c_1,c_2$) 魔法可以任意次数地将字母 $c_1$  和 $c_2$ 互相转化,只能让一个变为另外一个。你的任务是计算将两个字符串变为相同最少使用多少个魔法，并输出所需的魔法组合。

## 思路
当我们需要判断两个字符是否一样，我们可以运用并查集的思路来进行解答。实现很简单，把每个字符都是自己为一个集合。当我们用魔法把一个字符变成另一个字符时，就把这个字符加入变成的字符的集合中，最后我们看如果两个字符在一个集合中就是一样的，不再一个集合里就是不一样的。
### 注意事项
集合拥有互异性，确定性，无序性，需要考虑是否有重复。

---

## 作者：Horadrim (赞：0)

看其他3篇题解都用的并查集，这次来一种新的思路。

### 思路
首先看题，我们不难发现，要使两个字符串完全相同，必然要把不同的字母变成相同的字母 ~~（这不是废话吗）~~。所以我们发现在两个字符串中同一位置的2个字母不同就建边，说明要修改。之后记录次数，依次输出即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
vector <int> v[100011];
char x[100011],y[100011];
int t[100001],cnt,l,ans,s;
void dfs (int u) {
	l++;
	for (int i=0;i<v[u].size();i++) {
		if (t[v[u][i]]==0) {
			s++;
			x[s]=char(u+96);
			y[s]=char(v[u][i]+96);
			t[v[u][i]]=cnt;
			dfs(v[u][i]);
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	cin>>a>>b;
	for (int i=0;i<n;i++) {
		if (a[i]!=b[i]) {
			v[a[i]-96].push_back(b[i]-96);
			v[b[i]-96].push_back(a[i]-96);
		}
	}//建边
	for (int i=1;i<=26;i++) {
		if (t[i]==0) {
			cnt++;
			t[i]=cnt;
			l=0;
			dfs(i);		
			ans+=l-1;
		}
	}//dfs遍历、标记
	cout<<ans<<'\n';
	for (int i=1;i<=ans;i++) cout<<x[i]<<" "<<y[i]<<'\n';//输出
	
    return 0;
}
```


---

## 作者：pipiispig (赞：0)

###
CF的题果然好玩,蒟蒻第一样竟以为是线性DP，结果仔细一读发现可以用并查集来做，还挺简单（好玩）的；

因为这个题实在是没什么可以说的，代码实现复杂度极低，所以我就简单的说下思路吧-->连边，就是判断一个字符和一个字符直接是不是可以直接或间接转化，也就是是不是在一个并查集里，如果不在的话就连一条边，sum++就ok了；

```
#include<iostream>
#include<cstdio>
using namespace std;
int fa[30];
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}//并查集；
int sum;
char ans1[200],ans2[200];
char s1[100001],s2[100001]; 
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<=26;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		cin>>s1[i];
	}
	for(int j=1;j<=n;j++)
	{
		cin>>s2[j];
	}
	for(int i=1;i<=n;i++)
	{
		int xx=find(s1[i]-'a');
		int yy=find(s2[i]-'a');//吧字符转化为int类型;
		if(xx!=yy)
		{
			sum++;
			ans1[sum]=s1[i];
			ans2[sum]=s2[i];
			fa[xx]=yy;
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++)
	{
		cout<<ans1[i]<" "<<ans2[i]<<endl; //评测应该是开sp了；
	}
	return 0;	
}
```

---

