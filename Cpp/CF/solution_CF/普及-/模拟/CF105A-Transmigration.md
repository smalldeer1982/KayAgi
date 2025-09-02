# Transmigration

## 题目描述

In Disgaea as in most role-playing games, characters have skills that determine the character's ability to use certain weapons or spells. If the character does not have the necessary skill, he cannot use it. The skill level is represented as an integer that increases when you use this skill. Different character classes are characterized by different skills.

Unfortunately, the skills that are uncommon for the given character's class are quite difficult to obtain. To avoid this limitation, there is the so-called transmigration.

Transmigration is reincarnation of the character in a new creature. His soul shifts to a new body and retains part of his experience from the previous life.

As a result of transmigration the new character gets all the skills of the old character and the skill levels are reduced according to the $ k $ coefficient (if the skill level was equal to $ x $ , then after transmigration it becomes equal to $ [kx] $ , where $ [y] $ is the integral part of $ y $ ). If some skill's levels are strictly less than $ 100 $ , these skills are forgotten (the character does not have them any more). After that the new character also gains the skills that are specific for his class, but are new to him. The levels of those additional skills are set to $ 0 $ .

Thus, one can create a character with skills specific for completely different character classes via transmigrations. For example, creating a mage archer or a thief warrior is possible.

You are suggested to solve the following problem: what skills will the character have after transmigration and what will the levels of those skills be?

## 样例 #1

### 输入

```
5 4 0.75
axe 350
impaler 300
ionize 80
megafire 120
magicboost 220
heal
megafire
shield
magicboost
```

### 输出

```
6
axe 262
heal 0
impaler 225
magicboost 165
megafire 0
shield 0
```

# 题解

## 作者：wangjiayu19 (赞：4)

*~~这是我的第一篇题解~~*

看到这篇题目的题解，大部分dalao使用的都是 `map`

而我这个不熟悉 `map` 的蒟蒻在这里瑟瑟发抖...

因此，我讲一下这道题不用 `map` 的写法

## 思路

~~**其实就是照着题意走就行了**~~

对于每一个技能，我们都定义一个结构体：

```cpp
struct characters{
	string name;//技能名称
	double exp;//一定要注意！必须要用double 否则精度会出现问题...
	int learnt;//是否失效
}skills[55];
```

对重生后原有技能做处理：


```cpp
int n,m;
double k;
cin>>n>>m>>k;
for(int i=1;i<=n;i++){
	cin>>skills[i].name>>skills[i].exp;
	if(skills[i].exp*k<100) skills[i].learnt=-1;
    //如果经验值小于100则技能失效(learnt=-1)
	else skills[i].exp=skills[i].exp*k;
    //否则刷新经验值(exp*k)
}
```

学习新技能：

```cpp
for(int i=n+1;i<=m+n;i++){//序号要继续增长
	string x;//新技能名称
	skills[i].name=x;
}
```

 ### 但是这里要注意！如果学习了原来有的技能，经验值是不会刷新的。
 
 因此我们要判断新学习的技能之前是否学习过。
 
 ```cpp
 for(int i=n+1;i<=m+n;i++){
	string x;
	int used=0;//判断是否学习过
	cin>>x;
	for(int j=1;j<=n;j++){
		if(x==skills[j].name&&skills[j].learnt!=-1)
        //如果原有技能已失效，那么重新学习是可以的
        {
        	//如果技能原来就有
			used=1;
			skills[i].learnt=-1;
            //因为 i 还在增加 因此我们要将这个位置判断为无效
			break;
		}
	}
	if(!used) skills[i].name=x;
}
 ```
 
 接着排序。
 
 ```cpp
sort(skills+1,skills+m+n+1,cmp);
 ```
 
 `sort` 是不能排序结构体的，因此我们要写一个 `cmp` 函数：
 
 ```cpp
bool cmp(characters a,characters b){
	return a.name<b.name;
}
 ```
 
 输出：
 
 输出时一定要判断 `learnt` 是否为 $-1$ ， 如果是则不输出
 
```cpp
for(int i=1;i<=m+n;i++){
	if(skills[i].learnt!=-1) ans++;
}
cout<<ans<<endl;
for(int i=1;i<=m+n;i++){
	if(skills[i].learnt!=-1){
		cout<<skills[i].name<<' '<<floor(skills[i].exp)<<endl;
	}
}
 
```
### 然后...

![](https://cdn.luogu.com.cn/upload/image_hosting/40wzo23m.png)

## 经验差了 $1$ ，是精度的问题。

### 为什么呢？

我们来做个实验。

计算： $8700*0.94=?$

结果是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/bnx5wsoi.png)

C++ 计算这个数时，算成了 $8700*0.94=8177.999999999999$

再取整 便成了 $8177$

因此，我们定义一个纠错变量：

```cpp
double fix_tool=0.000000000001;
```

在计算时加入纠错变量，便AC了

# Code 

```cpp
#include<bits/stdc++.h>
using namespace std;
struct characters{
	string name;
	double exp;
	int learnt;
}skills[55];
bool cmp(characters a,characters b){
	return a.name<b.name;
}
int main(){
	double fix_tool=0.000000000001;
	int n,m;
	double k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>skills[i].name>>skills[i].exp;
		if(skills[i].exp*k<100) skills[i].learnt=-1;
		else skills[i].exp=skills[i].exp*k+fix_tool;
	}
	for(int i=n+1;i<=m+n;i++){
		string x;
		int used=0;
		cin>>x;
		for(int j=1;j<=n;j++){
			if(x==skills[j].name&&skills[j].learnt!=-1){
				used=1;
				skills[i].learnt=-1;
				break;
			}
		}
		if(!used) skills[i].name=x;
	}
	sort(skills+1,skills+m+n+1,cmp);
	int ans=0;
	for(int i=1;i<=m+n;i++){
		if(skills[i].learnt!=-1) ans++;
	}
	cout<<ans<<endl;
	for(int i=1;i<=m+n;i++){
		if(skills[i].learnt!=-1){
			cout<<skills[i].name<<' '<<floor(skills[i].exp)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：谦谦君子 (赞：2)

#### 说一下思路吧：算出技能继承后的值大于100的存下来，并用map标记，在新的角色中技能判断是否有标记过，没有就存下来，再排序输出就行了。

## 注意精度！！！

---

## 作者：nanatsuhi (赞：1)

题目描述可能有点不太清楚，我来稍作注释一下。

原翻译：自己看题面。

这里“继承效能”指的是一个技能继承后的经验值与原经验值之比。

即：原经验×继承效能=继承后经验

若继承后经验小于100，则该技能不会被新角色习得。

另外，新角色自己也有一些新的技能，经验值都是零。

最后把新角色的技能和对应经验按字典序输出就行啦。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    double k,x;
    string s;
    map<string,int> mp;  //技能名到经验的映射
    cin>>n>>m>>k;  //k就是继承效能
    for(int i=0;i<n;i++)
    {
        cin>>s>>x;
        x*=k;
        if(x>=100) mp[s]=int(x+1e-6); //大于一百就塞到映射表里
    }
    for(int i=0;i<m;i++)
    {
        cin>>s;
        if(!mp[s]) mp[s]=0;  //判一下这个技能有没有出现过，出现过就不经验清零
    }
    cout<<mp.size()<<endl;  //新角色的技能数
    for(auto c:mp)  //迭代输出
        cout<<c.first<<" "<<c.second<<endl; //就是名字和经验
    return 0;
}
```

---

## 作者：jxbe6666 (赞：0)

### 题意

有 $n$ 个技能，每个技能有一定的经验值，但也有一个系数，最终能留下的经验值就是经验值乘这个系数，注意要向下取整，如果能留下的经验值小于 $100$ 的话，就不能留下。当然，你也可以学习新的技能，初始经验为 $0$，技能如果有重复就取经验值高的

-----

### 思路
技能的变化一共有 $5$ 种情况：

1. 在乘上了 $k$ 后大于等于 $100$ 的。
2. 在乘上了 $k$ 后大于等于 $100$ 并且重新学习的。
3. 在乘上了 $k$ 后小于 $100$ 并且没有重新学习的。
4. 在乘上了 $k$ 后小于 $100$ 但是重新学习的。
5. 新学习的。
   
这五种情况处理分别如下：

1. 经验值乘以 $ k$ 后输出。
2. 经验值乘以 $k$ 后输出。
3. 不输出。
4. 将经验值设为零后输出。
5. 将经验值设为零后输出。

-----

### 代码

-----

```c++
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
const ll N = 1e6 + 5;
const ll M = 1e3 + 5;
ll a[N], b[N], dp[N], n, m, x, y, z, l, r, t, ans;
double k;
string s1, s2;
stack<int> _s;
queue<int> _q;
map<string, double> _m;
ll quickpower(ll x, ll y, ll mod)
{ // 快速幂
    if (y)
    {
        ll div = quickpower(x, y >> 1, mod);
        if (y & 1)
            return (div * div) % mod * x % mod;
        else
            return div * div % mod;
    }
    return 1;
}
inline ll read()
{ // 快读
    ll x = 0, y = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        y = (c == '-') ? -1 : 1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x * y;
}
inline void out(ll x)
{
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        out(x / 10);
    putchar(x % 10 + '0');
}
inline void write(ll x, char ch)
{ // 快输
    out(x);
    putchar(ch);
}
int main()
{
    n = read(), m = read();
    cin >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> s1 >> x;
        if (k * x >= 100) // 判断继承
            _m[s1] = int(k * x + 1e-7);
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> s1;
        if (!_m[s1]) // 没有就加上
            _m[s1] = 0;
    }
    cout << _m.size() << '\n'; // 输出个数
    for (auto it = _m.begin(); it != _m.end(); it++)
    {
        cout << it->first << " " << it->second << '\n'; // map 遍历
    }
    I AK IOI
}
```


---

## 作者：Allanljx (赞：0)

### 题意
有 $n$ 个技能，每个技能有一定的经验值，但也有一个系数，最终能留下的经验值就是经验值乘这个系数，注意要向下取整，如果能留下的经验值小于$100$的话，就不能留下。当然，你也可以学习新的技能，初始经验为$0$，技能如果有重复就取经验值高的。

### 思路
用结构体记录每个技能的名称和经验值以及有没有重复，用一个两层循环去重，再按字典序排序名称最后输出。

要注意一下精度，计算机是不能处理$0.99999……$，众所周知，上面这个数得一，可以证明。而 $double$ 类型精度有限，所以要加一个$0.000000000001$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum;//技能的数目
struct node
{
	string name;//技能的名称
	double num;//经验值
	bool book;//能不能取
}a[51];
bool cmp(node c,node d)//结构体排序
{
	return c.name<d.name;
}
bool compare(string aa,string bb)//判断是否相同
{
	int len1=aa.length(),len2=bb.length();
	if(len1!=len2) return 0;
	for(int i=0;i<len1;i++)
	{
		if(aa[i]!=bb[i]) return 0;
	}
	return 1;
}
int main()
{
	int n,m;
	double q;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].name>>a[i].num;
		a[i].num=a[i].num*q*1.0+0.000000000001;
		if(a[i].num<100) a[i].book=1;
	}
	for(int i=n+1;i<=m+n;i++)
	{
		cin>>a[i].name;
		a[i].num=0;
	}
	for(int i=1;i<=n+m;i++)//去重
		for(int j=i+1;j<=n+m;j++)
			if(compare(a[i].name,a[j].name)==1)
				if(a[i].num>a[j].num&&a[i].book!=1){a[j].book=1;}
				else a[i].book=1;
	sort(a+1,a+m+n+1,cmp);
	for(int i=1;i<=n+m;i++)//遍历有几个技能
	{
		if(a[i].book==1) continue;
		sum++;
	}
	cout<<sum<<endl;//技能数
	for(int i=1;i<=n+m;i++)
	{
		if(a[i].book==1) continue;
		cout<<a[i].name<<' '<<floor(a[i].num)<<endl;//向下取整
	}
	return 0;
}
```


---

