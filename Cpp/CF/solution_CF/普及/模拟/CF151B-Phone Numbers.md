# Phone Numbers

## 题目描述

Nvodsk 的冬天刺骨般的冷！于是一行 $n$ 个朋友们会坐出租车，点一个披萨，然后给女生打电话。这个城市中的电话由三组数字组成（如 12-34-56）。每个朋友都有一本大小为 $s_{i}$（此为电话号码的数量）的电话簿。出租车司机的电话号由六个相同的数字构成（如 22-22-22），披萨外卖的电话则由六个递减的数字构成（如 98-73-21），剩下的号码都是女生的电话。

现在你朋友的电话簿都交到了你手里。计算一下当你想做某件事时最好去找谁（有着最多相应类型的电话号码的人）。

如果一个人的电话簿中同一个电话号码出现了两次，你也需要计数两次。也就是说，你需要考虑每个号码出现在电话簿中的次数。

## 说明/提示

第一个样例中有四个朋友。Fedorov 的电话簿包含一个出租车司机的电话号码和一个披萨外卖的电话号码，Melnikov 的电话簿只有 $3$ 个女孩的电话号码，而Rogulenko 的电话簿则有 $6$ 个出租车司机的电话号码和一个披萨外卖的电话号码，Kaluzhin 的电话簿有 $2$ 个出租车司机的电话号码和一个披萨外卖的电话号码。

因此，如果你想要打出租车，显然你应该给 Rogulenko 打电话，如果你想要定个披萨，你可以给 Rogulenko、Fedorov、Kaluzhin 中的任何一个打电话（他们每个人都只有一个电话号码）。Melnikov 则有最多的女生的电话号码。

## 样例 #1

### 输入

```
4
2 Fedorov
22-22-22
98-76-54
3 Melnikov
75-19-09
23-45-67
99-99-98
7 Rogulenko
22-22-22
11-11-11
33-33-33
44-44-44
55-55-55
66-66-66
95-43-21
3 Kaluzhin
11-11-11
99-99-99
98-65-32
```

### 输出

```
If you want to call a taxi, you should call: Rogulenko.
If you want to order a pizza, you should call: Fedorov, Rogulenko, Kaluzhin.
If you want to go to a cafe with a wonderful girl, you should call: Melnikov.
```

## 样例 #2

### 输入

```
3
5 Gleb
66-66-66
55-55-55
01-01-01
65-43-21
12-34-56
3 Serega
55-55-55
87-65-43
65-55-21
5 Melnik
12-42-12
87-73-01
36-04-12
88-12-22
82-11-43
```

### 输出

```
If you want to call a taxi, you should call: Gleb.
If you want to order a pizza, you should call: Gleb, Serega.
If you want to go to a cafe with a wonderful girl, you should call: Melnik.
```

## 样例 #3

### 输入

```
3
3 Kulczynski
22-22-22
65-43-21
98-12-00
4 Pachocki
11-11-11
11-11-11
11-11-11
98-76-54
0 Smietanka
```

### 输出

```
If you want to call a taxi, you should call: Pachocki.
If you want to order a pizza, you should call: Kulczynski, Pachocki.
If you want to go to a cafe with a wonderful girl, you should call: Kulczynski.
```

# 题解

## 作者：FQR_ (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF151B)

这是一道模拟题。我将分步骤讲解。

___

### Part 1 表示每一个人

可以使用结构体来表示每一个人。
```cpp
struct s
{
	string name;int a,b,c;
}a[105];
```
其中， $name$ 表示这个人的名字， $a , b , c$ 分别表示出租车司机电话号码、披萨外卖电话号码、女生电话号码的数量。

___

### Part 2 模拟部分

用 $b$ 数组表示电话号码。 $b_0-b_5$ 存储这个电话号码的每一个数字。

接下来，判断这个电话号码是什么号码，并将对应数量加1。

```cpp
int n;
cin>>n;
for(int k=0;k<n;k++)
{
	char b[10];
	int t;
	cin>>t>>a[k].name;
	for(int i=0;i<t;i++)
	{
		char ch;
		cin>>b[0]>>b[1]>>ch>>b[2]>>b[3]>>ch>>b[4]>>b[5];
		if(b[0]==b[1]&&b[1]==b[2]&&b[2]==b[3]&&b[3]==b[4]&&b[4]==b[5]) a[k].a++;//全部相等，是出租车司机电话号码
		else if(b[0]>b[1]&&b[1]>b[2]&&b[2]>b[3]&&b[3]>b[4]&&b[4]>b[5])a[k].b++;//这六个数字递减，是披萨外卖电话号码
		else a[k].c++;//否则是女生电话号码
	}
}
```

___

### Part 3 输出
这是最让人头疼的部分。

首先，找出每种电话号码最多的数量是多少。
```cpp
int maxa=0,maxb=0,maxc=0;
for(int i=0;i<t;i++)
{
	maxa=max(maxa,a[i].a);
	maxb=max(maxb,a[i].b);
	maxc=max(maxc,a[i].c);
}
```

接下来，我将以出租车为例讲解。
```cpp
bool aaa=1;
cout<<"If you want to call a taxi, you should call: ";
for(int i=0;i<n;i++)
{
	if(a[i].a==maxa)
	{
		if(aaa) cout<<a[i].name,aaa=0;//如果是第一个输出的名字，要把aaa变为0
		else cout<<", "<<a[i].name;//不是第一个输出的名字，要输出逗号和空格
	}
}
cout<<'.'<<endl;
```
布尔变量 $aaa$ 表示是否为第一个要输出的名字。

遍历每一个出租车号码数量，如果和 $maxa$ 相等，就是最大的。

输出名字时，还要判断是否为第一个输出的。如果不是第一个输出的名字，还要在前面输出一个逗号和一个空格。

最后别忘了输出句号！

其他两个电话号码同理，给出整个输出部分的代码：
```cpp
int maxa=0,maxb=0,maxc=0;
for(int i=0;i<n;i++)
{
	maxa=max(maxa,a[i].a);
	maxb=max(maxb,a[i].b);
	maxc=max(maxc,a[i].c);
}
bool aaa=1,bbb=1,ccc=1;
cout<<"If you want to call a taxi, you should call: ";
for(int i=0;i<n;i++)
{
	if(a[i].a==maxa)
	{
		if(aaa) cout<<a[i].name,aaa=0;
		else cout<<", "<<a[i].name;
	}
}
cout<<'.'<<endl;
cout<<"If you want to order a pizza, you should call: ";
for(int i=0;i<n;i++)
{
	if(a[i].b==maxb)
	{
		if(bbb) cout<<a[i].name,bbb=0;
		else cout<<", "<<a[i].name;
	}
}
cout<<'.'<<endl;
cout<<"If you want to go to a cafe with a wonderful girl, you should call: ";
for(int i=0;i<n;i++)
{
	if(a[i].c==maxc)
	{
		if(ccc) cout<<a[i].name,ccc=0;
		else cout<<", "<<a[i].name;
	}
}
cout<<'.'<<endl;
```

___

### Part 4 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct s
{
	string name;int a,b,c;
}a[105];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for(int k=0;k<n;k++)
	{
		char b[10];
		int t;
		cin>>t>>a[k].name;
		for(int i=0;i<t;i++)
		{
			char ch;
			cin>>b[0]>>b[1]>>ch>>b[2]>>b[3]>>ch>>b[4]>>b[5];
			if(b[0]==b[1]&&b[1]==b[2]&&b[2]==b[3]&&b[3]==b[4]&&b[4]==b[5]) a[k].a++;
			else if(b[0]>b[1]&&b[1]>b[2]&&b[2]>b[3]&&b[3]>b[4]&&b[4]>b[5])a[k].b++;
			else a[k].c++;
		}
	}
	
	int maxa=0,maxb=0,maxc=0;
	for(int i=0;i<n;i++)
	{
		maxa=max(maxa,a[i].a);
		maxb=max(maxb,a[i].b);
		maxc=max(maxc,a[i].c);
	}
	bool aaa=1,bbb=1,ccc=1;
	cout<<"If you want to call a taxi, you should call: ";
	for(int i=0;i<n;i++)
	{
		if(a[i].a==maxa)
		{
			if(aaa) cout<<a[i].name,aaa=0;
			else cout<<", "<<a[i].name;
		}
	}
	cout<<'.'<<endl;
	cout<<"If you want to order a pizza, you should call: ";
	for(int i=0;i<n;i++)
	{
		if(a[i].b==maxb)
		{
			if(bbb) cout<<a[i].name,bbb=0;
			else cout<<", "<<a[i].name;
		}
	}
	cout<<'.'<<endl;
	cout<<"If you want to go to a cafe with a wonderful girl, you should call: ";
	for(int i=0;i<n;i++)
	{
		if(a[i].c==maxc)
		{
			if(ccc) cout<<a[i].name,ccc=0;
			else cout<<", "<<a[i].name;
		}
	}
	cout<<'.'<<endl;
	return 0;
}

```

---

## 作者：WinterRain208 (赞：4)

CF151B 【Phone Numbers】

这题没什么好说的，就是中等码量的模拟题。

提醒大家几个注意事项：

首先，按数位计算！！ $WA+1$

其次，空格逗号格式不能少！！ $WA+1$

都注意好了这题没什么难度，直接上代码了，含调试，请见谅。

## $UGLY CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e5+5;

struct peo{
	string name;
	int tot,girl,pizza,taxi;
}a[105]; 
int n;

bool judge(int x,int y,int z){
	if(x/10>x%10&&x%10>y/10&&y/10>y%10&&y%10>z/10&&z/10>z%10)return true;
	return false;
}

bool judge2(int x,int y,int z){
	if(x/10==x%10&&x%10==y/10&&y/10==y%10&&y%10==z/10&&z/10==z%10)return true;
	return false;
}
int main(){
	scanf("%d",&n);
	F(i,1,n){
		scanf("%d",&a[i].tot);
		cin>>a[i].name;
		a[i].girl=a[i].taxi=a[i].pizza=0;
		F(j,1,a[i].tot){
			int x,y,z;
			char k1,k2;
			cin>>x>>k1>>y>>k2>>z;
			//cout<<x<<" "<<y<<" "<<z<<endl;
			if(judge2(x,y,z))a[i].taxi++;
			else if(judge(x,y,z))a[i].pizza++;
			else a[i].girl++;
		}
	}
	int P=-1,T=-1,G=-1;
	F(i,1,n){
		P=max(P,a[i].pizza);
		T=max(T,a[i].taxi);
		G=max(G,a[i].girl);
	}
	//cout<<P<<" "<<T<<" "<<G<<endl;
	string pos;
	printf("If you want to call a taxi, you should call: ");
	int i=1;
	for(i=1;i<=n;i++)
		if(a[i].taxi==T){
			cout<<a[i].name;
			pos=a[i].name;
			break;
		}	
	for(i;i<=n;i++)
		if(a[i].taxi==T&&a[i].name!=pos)
			cout<<", "<<a[i].name;
	puts(".");
	printf("If you want to order a pizza, you should call: ");
	i=1;
	for(i=1;i<=n;i++)
		if(a[i].pizza==P){
			cout<<a[i].name;
			pos=a[i].name;
			break;
		}	
	for(i;i<=n;i++)
		if(a[i].pizza==P&&a[i].name!=pos)
			cout<<", "<<a[i].name;
	puts(".");
	printf("If you want to go to a cafe with a wonderful girl, you should call: ");
	i=1;
	for(i=1;i<=n;i++)
		if(a[i].girl==G){
			cout<<a[i].name;
			pos=a[i].name;
			break;
		}	
	for(i;i<=n;i++)
		if(a[i].girl==G&&a[i].name!=pos)
			cout<<","<<a[i].name;
	puts(".");
    return 0;
}
/*
If you want to call a taxi, you should call: Rogulenko.
If you want to order a pizza, you should call: Fedorov, Rogulenko, Kaluzhin.
If you want to go to a cafe with a wonderful girl, you should call: Melnikov.
*/

```

请不要复制粘贴，改代码需修改一个字符才能$AC$。

$wtrl$。

---

## 作者：松鼠的星星 (赞：2)

普通的模拟题，每次遇到比当前记录的还优的就清空

注意判断是按位判断，还有输出格式

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 3;
vector<string> name[MAX];
int num[MAX];
/*
0:taxi
1:pizza
2:girl
*/
int n;
bool istaxi(string s)
{
    char tmp = s[0];
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] != tmp && s[i] != '-')
        {
            return false;
        }
    }
    return true;
}
bool ispizza(string s)
{
    char tmp = s[0];
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] != '-')
        {
            if (s[i] >= tmp)
            {
                return false;
            }
            tmp = s[i];
        }
    }
    return true;
}
void print()
{
    cout << "If you want to call a taxi, you should call: ";
    for (int i = 0; i < name[0].size(); i++)
    {
        cout << name[0][i];
        if (i == name[0].size() - 1)
        {
            cout << '.' << endl;
        }
        else
        {
            cout << ", ";
        }
    }

    cout << "If you want to order a pizza, you should call: ";
    for (int i = 0; i < name[1].size(); i++)
    {
        cout << name[1][i];
        if (i == name[1].size() - 1)
        {
            cout << '.' << endl;
        }
        else
        {
            cout << ", ";
        }
    }

    cout << "If you want to go to a cafe with a wonderful girl, you should call: ";
    for (int i = 0; i < name[2].size(); i++)
    {
        cout << name[2][i];
        if (i == name[2].size() - 1)
        {
            cout << '.' << endl;
        }
        else
        {
            cout << ", ";
        }
    }
}
int main()
{
    memset(num, -1, sizeof(num));
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m;
        string nowname;
        string s;
        int cnt[MAX];
        memset(cnt, 0, sizeof(cnt));
        cin >> m >> nowname;
        for (int j = 0; j < m; j++)
        {
            cin >> s;
            if (istaxi(s))
            {
                cnt[0]++;
            }
            else if (ispizza(s))
            {
                cnt[1]++;
            }
            else
            {
                cnt[2]++;
            }
        }
        for (int i = 0; i < MAX; i++)
        {
            if (cnt[i] > num[i])
            {
                num[i] = cnt[i];
                name[i].clear();
            }
            if (cnt[i] == num[i])
            {
                name[i].push_back(nowname);
            }
        }
    }
    print();
    return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
在一座城市中，每个人的电话号码都是由六位整数组成的，例如 11-45-14。

现在有 $n$ 个人，第 $i$ 个人有 $s_i$ 个人的电话号码。已知：

- 出租车司机的电话号码由六个相同的数字构成（如 66-66-66）。
- 披萨外卖的电话号码由六个递减的数字构成（如 65-43-21）。
- 其他的电话号码都是女生的。

现在给出这 $n$ 个人所拥有的电话号码。众所周知，找一个拥有某种事情相关的人的电话号码最多的人办这件事总会很靠谱。你需要求出你在办某件事的时候应该找哪些人。

**数据范围：$1\leqslant n\leqslant 100$，$0\leqslant s_i\leqslant 100$。**
## Solution
这题是一道较为简单的模拟题。

我们利用 scanf 的特性，按照格式输入没个电话号码的六个数字，然后按照题目给出的规则将每个电话号码归入题目给出的类型中，同时统计每个人所拥有某种类型的电话号码的数量。

统计完以后，分别按照拥有某种类型的电话号码的数量降序排列，然后找出拥有和最多数量相同的人，最后再按照输入顺序输出即可。
## Code
```cpp
int n, num[107], cnt;
struct node {
	string name;
	int x[107][7], taxi, pizza, girl, id;
}a[107], ans1[107], ans2[107], ans3[107];

ib cmp1(const node& tmp1, const node& tmp2) {return tmp1.taxi > tmp2.taxi;}
ib cmp2(const node& tmp1, const node& tmp2) {return tmp1.pizza > tmp2.pizza;}
ib cmp3(const node& tmp1, const node& tmp2) {return tmp1.girl > tmp2.girl;}
ib cmpid(const node& tmp1, const node& tmp2) {return tmp1.id < tmp2.id;}

int main() {
	n = Rint;
	F(i, 1, n) {
		num[i] = Rint, a[i].id = i; cin >> a[i].name;
		F(j, 1, num[i]) scanf("%1d%1d-%1d%1d-%1d%1d", &a[i].x[j][1], &a[i].x[j][2], &a[i].x[j][3], &a[i].x[j][4], &a[i].x[j][5], &a[i].x[j][6]);
	}
	F(i, 1, n) {
		F(j, 1, num[i]) {
			int fl1 = 1, fl2 = 1;
			F(k, 1, 6) if(a[i].x[j][k] != a[i].x[j][1]) {fl1 = 0; break;}
			F(k, 2, 6) if(a[i].x[j][k] >= a[i].x[j][k - 1]) {fl2 = 0; break;}
			if(fl1) a[i].taxi++;
			else if(fl2) a[i].pizza++;
			else a[i].girl++;
		}
	}
	sort(a + 1, a + n + 1, cmp1);
	int tmp = a[1].taxi;
	sort(a + 1, a + n + 1, cmpid);
	printf("If you want to call a taxi, you should call: ");
	F(i, 1, n) if(a[i].taxi == tmp) ans1[++cnt] = a[i];
	F(i, 1, cnt) cout << ans1[i].name << (i == cnt ? ".\n" : ", ");
	sort(a + 1, a + n + 1, cmp2);
	printf("If you want to order a pizza, you should call: ");
	tmp = a[1].pizza, cnt = 0;
	sort(a + 1, a + n + 1, cmpid);
	F(i, 1, n) if(a[i].pizza == tmp) ans2[++cnt] = a[i];
	F(i, 1, cnt) cout << ans2[i].name << (i == cnt ? ".\n" : ", ");
	sort(a + 1, a + n + 1, cmp3);
	printf("If you want to go to a cafe with a wonderful girl, you should call: ");
	tmp = a[1].girl, cnt = 0;
	sort(a + 1, a + n + 1, cmpid);
	F(i, 1, n) if(a[i].girl == tmp) ans3[++cnt] = a[i];
	F(i, 1, cnt) cout << ans3[i].name << (i == cnt ? ".\n" : ", ");
	return 0;
}
```

---

## 作者：UnknownPeople (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF151B)  
本题作为绿题还是很有水分的。
## 分析
- 这道题唯一的难点在于将电话号码分类，为了~~为难做题人~~增加难度，出题人特地在电话号码中加入了`-`，但只需要再对它用一点小技巧就可以轻松处理。  
- 其他的如判断整个字符串是否都相同，判断字符串是否降序，都是非常基础的字符串知识了。~~不会的自己去主题库看。~~

上代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int maxc[4];
string name[105];
int cnt[4][105];
int change(string s){
	string t;
	for(int i=0;i<s.size();i++)
		if(s[i]!='-')
			t.push_back(s[i]);
	/*
	简单的去除字符串中多余字符的小技巧 
	*/
	char c=t[0];
	for(int i=0;i<t.size();i++)
		if(t[i]!=c){
			c++;
			break;
		}
	if(c==t[0])
		return 1;//个人习惯，请谅解 
	for(int i=1;i<t.size();i++)
		if(t[i]>=t[i-1])
			return 3;
	return 2;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int m;
		cin>>m>>name[i];
		while(m--){
			string num;
			cin>>num;
			cnt[change(num)][i]++;
		}
		for(int j=1;j<4;j++)
			maxc[j]=max(maxc[j],cnt[j][i]);
	}
	cout<<"If you want to call a taxi, you should call: ";
	int c=0;
	for(int i=1;i<=n;i++)
		if(cnt[1][i]==maxc[1]){//如果是拥有电话最多的朋友就输出，下同 
			if(c)
				cout<<", ";
			cout<<name[i];
			c++;
		}
	cout<<".\nIf you want to order a pizza, you should call: ";
	c=0;
	for(int i=1;i<=n;i++)
		if(cnt[2][i]==maxc[2]){
			if(c)
				cout<<", ";
			cout<<name[i];
			c++;
		}
	c=0;
	cout<<".\nIf you want to go to a cafe with a wonderful girl, you should call: ";
	for(int i=1;i<=n;i++)
		if(cnt[3][i]==maxc[3]){
			if(c)
				cout<<", ";
			cout<<name[i];
			c++;
		}
	cout<<".";
	return 0;
}
```
~~个人感觉这道题配不上绿题，最多一道橙题。~~

---

## 作者：mysterys (赞：1)

# 前言
感觉这题并没有绿，黄差不多吧。

总体来说，这是一道非常简洁的题目。
# 思路
1. 开 $n$ 个结构体存每一个人的信息：girl，pizza，taxi。
2. 一边输入，一边维护每个人的信息。
3. 在维护信息的同时处理最大值。
4. 暴力寻找对应的人，输出名字即可。**注意**，可能存在多个最大值，这时要都输出。
5. 如何判断逗号：开个变量统计一下当前是否是第一个输出的即可。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
#define ll long long
struct node{
	string name;
	int taxi,girl,pizza;
}a[105];
int n,maxtaxi,maxgirl,maxpizza;
inline void check(int id,string s){
	bool flag1=0,flag2=0;
	char lst=' ';
	for(int i=0;i<s.length();i++){
		if(s[i]=='-') continue;
		if(lst!=' '){
			if(s[i]!=lst) flag1=1;
			if(s[i]>=lst) flag2=1;
		}
		lst=s[i];
	}
	if(flag1&&flag2){
		a[id].girl++;
	}else if(flag1){
		a[id].pizza++;
	}else a[id].taxi++;
}
signed main(){
	cin.tie(nullptr)->ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		int k;
		cin>>k>>a[i].name;
		for(int j=1;j<=k;j++){
			string s;
			cin>>s;
			check(i,s);
		}
		maxtaxi=max(maxtaxi,a[i].taxi);
		maxgirl=max(maxgirl,a[i].girl);
		maxpizza=max(maxpizza,a[i].pizza);
	}
	cout<<"If you want to call a taxi, you should call: ";
	bool flag=false;
	for(int i=1;i<=n;i++){
		if(a[i].taxi==maxtaxi){
			if(flag) cout<<", ";
			cout<<a[i].name;
			flag=true;
		}
	}
	cout<<'.'<<endl;
	cout<<"If you want to order a pizza, you should call: ";
	flag=false;
	for(int i=1;i<=n;i++){
		if(a[i].pizza==maxpizza){
			if(flag) cout<<", ";
			cout<<a[i].name;
			flag=true;
		}
	}
	cout<<'.'<<endl;
	cout<<"If you want to go to a cafe with a wonderful girl, you should call: ";
	flag=false;
	for(int i=1;i<=n;i++){
		if(a[i].girl==maxgirl){
			if(flag) cout<<", ";
			cout<<a[i].name;
			flag=true;
		}
	}
	cout<<'.';
	return 0;
}
```

---

## 作者：songtaoran (赞：1)

这题一看就是大模拟。  
注意：  
+ **输出格式**！！！  
+ 出租车的相等指的是**所有位都相等**，而不是类似 12-12-12 这种，否则会 WA on #33。  

我的思路是使用三个 map 分别维护：  
+ 这个人电话号码是披萨外卖的个数。
+ 这个人电话号码是出租车司机的个数。
+ 这个人电话号码是女生电话的个数。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, m, a, b, c, maxtaxi = 0, maxgirl = 0, maxpizza = 0;
string s[110];
map<string, ll> pizza;
map<string, ll> taxi;
map<string, ll> girl;
int main(){
	cin >> n;
	for(ll i = 1; i <= n; i++){
		maxtaxi = maxgirl = maxpizza = 0;
		scanf("%lld", &m);
		cin >> s[i];
		for(ll j = 1; j <= m; j++){
			scanf("%lld-%lld-%lld", &a, &b, &c);
			if(a == b && b == c && a / 10 == a % 10) taxi[s[i]]++;
			else if(a / 10 > a % 10 && a % 10 > b / 10 && b / 10 > b % 10 && b % 10 > c / 10 && c / 10 > c % 10)
				pizza[s[i]]++;
			else girl[s[i]]++;
		}
	}
	for(ll i = 1; i <= n; i++){
		maxtaxi = max(maxtaxi, taxi[s[i]]);
		maxgirl = max(maxgirl, girl[s[i]]);
		maxpizza = max(maxpizza, pizza[s[i]]);
	}
	bool flag1 = 0, flag2 = 0, flag3 = 0;
	printf("If you want to call a taxi, you should call: ");
	for(ll i = 1; i <= n; i++)
		if(taxi[s[i]] == maxtaxi){
			if(!flag1){
				cout << s[i]; flag1 = 1;
			}else cout << ", " << s[i];
		}
	printf(".\nIf you want to order a pizza, you should call: ");
	for(ll i = 1; i <= n; i++)
		if(pizza[s[i]] == maxpizza){
			if(!flag2){
				cout << s[i]; flag2 = 1;
			}else cout << ", " << s[i];
		}
	printf(".\nIf you want to go to a cafe with a wonderful girl, you should call: ");
	for(ll i = 1; i <= n; i++)
		if(girl[s[i]] == maxgirl){
			if(!flag3){
				cout << s[i]; flag3 = 1;
			}else cout << ", " << s[i];
		}
	printf(".");
	return 0;
}
```
看在我写了 1.46KB 代码的份上，给我点个赞吧~~~

---

## 作者：风中の菜鸡 (赞：1)

题意简化

给你 $n$ 个人所拥有的电话号码 $($ 一定为 $xx-xx-xx$ 的格式 $)$ 按一定规则计数，需要你输出拥有符合一定规则的电话号码数量最多的人，有多个人就都要输出。

思路

纯模拟。

每输入一个电话号码就判断一下它是谁的电话号码，开个结构体计数。再找出在所有人中拥有某种类型的电话号码数最多的数量。然后把他们的编号存在一个数组中。最后按规则输出即可。$($ 若有多个中间需要用逗号隔开，具体处理方法在代码中有解释 $)$ 

代码

虽然看起来不好写，但实现代码还是不难的。（有详细注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ans_taxi[101],ans_girl[101],ans_pizza[101];//存每种类型的电话数量最多拥有者的编号 
int lt,lg,lp;//上述数组的长度 (依次对应) 
struct frd{
	string name;
	int num_girl,num_taxi,num_pizza;//这个人拥有的每种电话类型的数量 
}f[101];
bool check_taxi(string s){
	if(s[0]==s[1]&&s[1]==s[3]&&s[3]==s[4]&&s[4]==s[6]&&s[6]==s[7])
		return true;
	return false;
}//判断这个电话号码是不是出租车司机的 
bool check_pizza(string s){
	if(s[0]>s[1]&&s[1]>s[3]&&s[3]>s[4]&&s[4]>s[6]&&s[6]>s[7])
		return true;
	return false;
}//判断这个电话号码是不是披萨店的 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int sl=0;
		cin>>sl>>f[i].name;
		for(int j=1;j<=sl;j++){
			string ss;
			cin>>ss;
			//计数 
			if(check_pizza(ss)==true)
				f[i].num_pizza++;
			if(check_taxi(ss)==true)
				f[i].num_taxi++;
			if(check_taxi(ss)==false&&check_pizza(ss)==false)
				f[i].num_girl++;
		}
	}
	int max_taxi=0,max_girl=0,max_pizza=0;
	for(int i=1;i<=n;i++){//找每种电话类型最多的数量 
		max_taxi=max(max_taxi,f[i].num_taxi);
		max_girl=max(max_girl,f[i].num_girl);
		max_pizza=max(max_pizza,f[i].num_pizza);
	}
	for(int i=1;i<=n;i++){//存每种电话类型最多拥有者编号 
		if(f[i].num_girl==max_girl) ans_girl[++lg]=i;
		if(f[i].num_taxi==max_taxi) ans_taxi[++lt]=i;	
		if(f[i].num_pizza==max_pizza) ans_pizza[++lp]=i;	
	}
	//输出 
	cout<<"If you want to call a taxi, you should call:";
	for(int i=1;i<lt;i++){//只输出到lt-1位，最后一位单独处理(为了处理多人满足条件中间用逗号隔开,下同) 
		cout<<' '<<f[ans_taxi[i]].name<<',';
	}
	cout<<' '<<f[ans_taxi[lt]].name<<'.'<<endl;
	cout<<"If you want to order a pizza, you should call:";
	for(int i=1;i<lp;i++){
		cout<<' '<<f[ans_pizza[i]].name<<',';
	}
	cout<<' '<<f[ans_pizza[lp]].name<<'.'<<endl;
	cout<<"If you want to go to a cafe with a wonderful girl, you should call:";
	for(int i=1;i<lg;i++){
		cout<<' '<<f[ans_girl[i]].name<<',';
	}
	cout<<' '<<f[ans_girl[lg]].name<<'.'<<endl;	
	return 0;
}
```



---

## 作者：__Cartesian__Tree__ (赞：1)

显然本题是一道大模拟。~~（其实也不大）~~

首先，由于每个人与其他人的电话号码没有关系，只是比对最大值，所以我们可以一边输入一边处理。

具体的实现，我用 vector 实现存储名单，并在每个人输入完所有号码后更新。

具体细节可见代码(已 AC):

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> taxi;//最大值名单 
vector<string> pizza;
vector<string> girl;
int max_taxi = -1, max_pizza = -1, max_girl = -1;//当前最大值 
int main(){
	int n;
	cin>>n;
	for (int i = 1; i <= n; i++){
		int len;
		string name;
		cin>>len>>name;
		int _taxi = 0, _pizza = 0, _girl = 0;//每种的个数 
		char trash;
		for (int j = 1; j <= len; j++){//读入号码 
			trash = getchar();
			while (!isdigit(trash)) trash = getchar();//用来读入没用的换行符 
			char a, b, c, d, e, f;
			a = trash;//此时trash已经读到数字，这是第一个字符，赋值给a 
			scanf("%c-%c%c-%c%c", &b, &c, &d, &e, &f);//用scanf格式化输入剩下字符 
			if (a == b && b == c && c == d && d == e && e == f){//taxi
				_taxi++;
				continue;
			}
			if (a > b && b > c && c > d && d > e && e > f){//pizza
				_pizza++;
				continue;
			}
			_girl++;//girl
		}
		//开始判断 
		if (_taxi > max_taxi){//比当前最大值大，清空名单并重新赋值，加入 
			taxi.clear();
			taxi.push_back(name);
			max_taxi = _taxi;
		}
		else if (_taxi == max_taxi){//跟当前最大值一样，加入 
			taxi.push_back(name);
		}
		//以下同理 
		if (_pizza > max_pizza){
			pizza.clear();
			pizza.push_back(name);
			max_pizza = _pizza;
		}
		else if (_pizza == max_pizza){
			pizza.push_back(name);
		}
		if (_girl > max_girl){
			girl.clear();
			girl.push_back(name);
			max_girl = _girl;
		}
		else if (_girl == max_girl){
			girl.push_back(name);
		}
	} 
	//开始输出 
	for (int i = 0; i < taxi.size(); i++){
		if (taxi.size() == 1){
			cout << "If you want to call a taxi, you should call: " << taxi[i] << '.' << endl;
			break;
		}	
		if (i == 0)cout << "If you want to call a taxi, you should call: " << taxi[i] << ", ";
		else if (i != taxi.size() - 1)cout << taxi[i] << ", "; 
		else cout << taxi[i] << '.' << endl;
	}
	for (int i = 0; i < pizza.size(); i++){
		if (pizza.size() == 1){
			cout << "If you want to order a pizza, you should call: " << pizza[i] << '.' << endl;
			break;
		}	
		if (i == 0)cout << "If you want to order a pizza, you should call: " << pizza[i] << ", ";
		else if (i != pizza.size() - 1)cout << pizza[i] << ", "; 
		else cout << pizza[i] << '.' << endl;
	}
	for (int i = 0; i < girl.size(); i++){
		if (girl.size() == 1){
			cout << "If you want to go to a cafe with a wonderful girl, you should call: " << girl[i] << '.' << endl;
			break;
		}	
		if (i == 0)cout << "If you want to go to a cafe with a wonderful girl, you should call: " << girl[i] << ", ";
		else if (i != girl.size() - 1)cout << girl[i] << ", "; 
		else cout << girl[i] << '.' << endl;
	}
    return 0;//完美return 
}

```


---

## 作者：codeLJH114514 (赞：1)

[$\colorbox{skyblue}{\color{#fff}{\text{题目传送门}}}$](https://www.luogu.com.cn/problem/CF151B)

## Problem

某人有 $n$ 个朋友，TA 们各有 $m_i$ 个电话号码，问每一种电话号码都是谁最多？

电话号码的格式为：$x_1x_2-x_3x_4-x_5x_6$，`ab-cd-ef`。

电话号码有三种：

1. 司机型：六个数字都一样：$xx-xx-xx$，`xx-xx-xx`。
1. 披萨型：六个数字从右向左 **严格递增**。
1. 女生型：既不是司机型也不是披萨型。

如果有几个人的数量一样则并列输出。（用输入顺序进行排序。）

## Data Range

$1 \leqslant n \leqslant 100$，$1 \leqslant m_i \leqslant 100$，$1 \leqslant |s_i| \leqslant 20$，$s_i$ 为第 $i$ 个朋友的姓名。

## Sulotion 

### Step1 : 电话号码的存储。

我们不妨使用一个类来表示一个电话号码。

代码如下：

```cpp
// 函数功能：返回x的十位是否是大于x的个位。（仅限于两位数，用于判断是否是披萨型电话号码。）
bool isLeap(int x) {
    return x / 10 > x % 10;
}
// 函数功能：返回a的个位是否是大于b的十位。（仅限于两位数，用于判断是否是披萨型电话号码。）
bool isLeap(int a, int b) { 
    return a % 10 > b / 10;
}
// 函数功能：返回x的十位是否和个位相等。（仅限于两位数，用于判断是否是司机型电话号码。）
bool isEqual(int x) { 
    return x / 10 == x % 10;
}
// 类功能：存储一个电话号码。
class PhoneNumber {
    public:
        int a, b, c;
        // 输入一个电话号码。
        PhoneNumber(istream& in) {
            char ch;
            in >> a >> ch >> b >> ch >> c;
        }
        // 根据_a,_b,_c来构造一个电话号码。
        PhoneNumber(int _a, int _b, int _c) {
            a = _a, b = _b, c = _c;
        }
        // 使用一个字符串来构造一个电话号码。
        PhoneNumber(string Phone) {
            stringstream ss;
            ss << Phone;
            char ch;
            ss >> a >> ch >> b >> ch >> c;
        }
        // 默认的初始化电话号码为 00-00-00。
        PhoneNumber() {
            a = b = c = 0;
        }
        // 判断这个电话号码是否是披萨型电话号码。
        bool isPizza() {
            return isLeap(a) and isLeap(b) and isLeap(c) and isLeap(a, b) and isLeap(b, c);
        }
        // 判断这个电话号码是否是司机型电话号码。
        bool isTaxi() {
            return isEqual(a) and isEqual(b) and isEqual(c) and a == b and b == c;
        }
        // 判断这个电话号码是否是女生型电话号码。
        bool isGirl() {
            return not isPizza() and not isTaxi();
        }
};
```

我们就完成了电话号码的存储。

### Step2 : 朋友们的存储。

还是用一个类来存。

```cpp
// 类功能：存储一个朋友。
class Friend {
    public:
        vector<PhoneNumber> v;
        string name;
        // 输入一个朋友。
        Friend(istream& cin) {
            int n;
            cin >> n >> name;
            v.resize(n);
            for (int i = 0; i < n; i++)
                v[i] = PhoneNumber(cin);
        }
        // 朋友的默认初始化。
        Friend() {
            v.clear();
        }
        // 函数功能：返回一个朋友有多少个女生型电话号码。
        int HasGirlFriend() {
            int res = 0;
            for (auto i : v)
                if (i.isGirl())
                    res += 1;
            return res;
        }
        // 函数功能：返回一个朋友有多少个司机型电话号码。
        int HasTaxiPhones() {
            int res = 0;
            for (auto i : v)
                if (i.isTaxi())
                    res += 1;
            return res;
        }
        // 函数功能：返回一个朋友有多少个披萨型电话号码。
        int HasPizza() {
            int res = 0;
            for (auto i : v)
                if (i.isPizza())
                    res += 1;
            return res;
        }
        string Format() {return name;}
} f[maxn]; // 朋友们
```

### Step3 : 查找最大值。

这里我使用了一个最大值的类来存，你可以使用任何方法均可以。

```cpp
// 类功能：存储答案。
class Maximum {
    public:
        int girl_friends, taxi_phones, pizzas; // 存储每种类型最多的电话号码数量。
        Maximum(): girl_friends(0), taxi_phones(0), pizzas(0) {}
        // 尝试更新数量。
        void Max(int x) {
            int hsGF, hsPz, hsTp;
            hsGF = f[x].HasGirlFriend();
            hsPz = f[x].HasPizza();
            hsTp = f[x].HasTaxiPhones();
            if (girl_friends < hsGF)
                girl_friends = hsGF;
            if (pizzas < hsPz)
                pizzas = hsPz;
            if (taxi_phones < hsTp)
                taxi_phones = hsTp;
        }
};
```

### Step4 : 查找所有符合条件的朋友并输出。

这里我还是使用了一个类。（因为这样~~显得我很懂OOP~~很方便，只需调用格式化的方法即可。）

## Code

完整代码：

```cpp
#include <bits/stdc++.h>
#define maxn 128
using namespace std; 
// 函数功能：返回x的十位是否是大于x的个位。（仅限于两位数，用于判断是否是披萨型电话号码。）
bool isLeap(int x) {
    return x / 10 > x % 10;
}
// 函数功能：返回a的个位是否是大于b的十位。（仅限于两位数，用于判断是否是披萨型电话号码。）
bool isLeap(int a, int b) { 
    return a % 10 > b / 10;
}
// 函数功能：返回x的十位是否和个位相等。（仅限于两位数，用于判断是否是司机型电话号码。）
bool isEqual(int x) { 
    return x / 10 == x % 10;
}
// 类功能：存储一个电话号码。
class PhoneNumber {
    public:
        int a, b, c;
        // 输入一个电话号码。
        PhoneNumber(istream& in) {
            char ch;
            in >> a >> ch >> b >> ch >> c;
        }
        // 根据_a,_b,_c来构造一个电话号码。
        PhoneNumber(int _a, int _b, int _c) {
            a = _a, b = _b, c = _c;
        }
        // 使用一个字符串来构造一个电话号码。
        PhoneNumber(string Phone) {
            stringstream ss;
            ss << Phone;
            char ch;
            ss >> a >> ch >> b >> ch >> c;
        }
        // 默认的初始化电话号码为 00-00-00。
        PhoneNumber() {
            a = b = c = 0;
        }
        // 判断这个电话号码是否是披萨型电话号码。
        bool isPizza() {
            return isLeap(a) and isLeap(b) and isLeap(c) and isLeap(a, b) and isLeap(b, c);
        }
        // 判断这个电话号码是否是司机型电话号码。
        bool isTaxi() {
            return isEqual(a) and isEqual(b) and isEqual(c) and a == b and b == c;
        }
        // 判断这个电话号码是否是女生型电话号码。
        bool isGirl() {
            return not isPizza() and not isTaxi();
        }
};
// 类功能：存储一个朋友。
class Friend {
    public:
        vector<PhoneNumber> v;
        string name;
        // 输入一个朋友。
        Friend(istream& cin) {
            int n;
            cin >> n >> name;
            v.resize(n);
            for (int i = 0; i < n; i++)
                v[i] = PhoneNumber(cin);
        }
        // 朋友的默认初始化。
        Friend() {
            v.clear();
        }
        // 函数功能：返回一个朋友有多少个女生型电话号码。
        int HasGirlFriend() {
            int res = 0;
            for (auto i : v)
                if (i.isGirl())
                    res += 1;
            return res;
        }
        // 函数功能：返回一个朋友有多少个司机型电话号码。
        int HasTaxiPhones() {
            int res = 0;
            for (auto i : v)
                if (i.isTaxi())
                    res += 1;
            return res;
        }
        // 函数功能：返回一个朋友有多少个披萨型电话号码。
        int HasPizza() {
            int res = 0;
            for (auto i : v)
                if (i.isPizza())
                    res += 1;
            return res;
        }
        string Format() {return name;}
} f[maxn]; // 朋友们
// 类功能：存储一个朋友列表，用于方便的输出许多朋友。
class FriendsList {
    public:
        vector<Friend> v;
        FriendsList() {
            v.clear();
        }
        // 返回一个字符串，按照题目的要求格式化。
        string Format() {
            string s;
            for (int i = 0; i < v.size(); i++)
                s += v[i].Format() + (i == v.size() - 1 ? ".\n" : ", ");
            return s;
        }
        // 加入一个朋友。
        void Append(int idx) {
            v.emplace_back(f[idx]);
        }
} GF, TP, PZ; // 三个朋友列表分别表示女孩型电话号码的答案，司机型电话号码的答案，披萨型电话号码的答案。
// 类功能：存储答案。
class Maximum {
    public:
        int girl_friends, taxi_phones, pizzas; // 存储每种类型最多的电话号码数量。
        Maximum(): girl_friends(0), taxi_phones(0), pizzas(0) {}
        // 尝试更新数量。
        void Max(int x) {
            int hsGF, hsPz, hsTp;
            hsGF = f[x].HasGirlFriend();
            hsPz = f[x].HasPizza();
            hsTp = f[x].HasTaxiPhones();
            if (girl_friends < hsGF)
                girl_friends = hsGF;
            if (pizzas < hsPz)
                pizzas = hsPz;
            if (taxi_phones < hsTp)
                taxi_phones = hsTp;
        }
};
int n;
Maximum maximum; // 最大值。
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        f[i] = Friend(cin); // 输入所有f[i]。
        maximum.Max(i); // 尝试更新。
    }
    for (int i = 1; i <= n; i++) { // 找到所有符合条件的朋友们。
        if (f[i].HasGirlFriend() == maximum.girl_friends)
            GF.Append(i);
        if (f[i].HasPizza() == maximum.pizzas)
            PZ.Append(i);
        if (f[i].HasTaxiPhones() == maximum.taxi_phones)
            TP.Append(i);
    }
    cout << "If you want to call a taxi, you should call: " << TP.Format(); // 格式化朋友列表并输出
    cout << "If you want to order a pizza, you should call: " << PZ.Format(); // 同上
    cout << "If you want to go to a cafe with a wonderful girl, you should call: " << GF.Format(); // 同上
    return 0;
}
```

拒绝抄袭题解，共创美好洛谷。

---

## 作者：bbbzzx (赞：1)

这题就是一道大模拟，难点在于输出部分，统计部分还是挺简单的。输出部分可以用一个字符串来统计。
```cpp
string a="";
a+="bbbzzx";
cout<<a;
```
以上代码可以直接将 "bbbzzx" 这个字符串接到字符串 $a$ 后面，所以接下来就好办了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,taxi=-1,pizza=-1,girl=-1;
string str1,str2,str3;
int mian()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int t=0,p=0,g=0;
		string name;
		cin>>m>>name;
		for(int i=1;i<=m;i++)
		{
			int a,b,c;
			char ch;
			cin>>a>>ch>>b>>ch>>c;
			if(a==b&&b==c&&a==c&&a%11==0)
				t++;//是否是出租车司机 
			else
			if(a/10>a%10 && a%10>b/10 && b/10>b%10 && b%10>c/10 && c/10>c%10)
				p++;//是否是披萨店 
			else
				g++;//是女孩 
		}//这个循环是统计部分 
		if(t>taxi)
		{
			str1=" "+name;
			taxi=t;
		}
		else
		if(t==taxi)
			str1+=", "+name;
		if(p>pizza)
		{
			str2=" "+name;
			pizza=p;
		}
		else
		if(p==pizza)
			str2+=", "+name;
		if(g>girl)
		{
			str3=" "+name;
			girl=g;
		}
		else
		if(g==girl)
			str3+=", "+name;
		//三个字符串统计人名 
	}
	cout<<"If you want to call a taxi, you should call:"<<str1<<"."<<endl;
	cout<<"If you want to order a pizza, you should call:"<<str2<<"."<<endl;
	cout<<"If you want to go to a cafe with a wonderful girl, you should call:"<<str3<<"."<<endl;
	//以上三行是输出，别忘了最后的句号。 
	return 0; 
}
```
代码加了防抄袭，勿抄谢谢。

---

## 作者：jijidawang (赞：1)

大佬们的题解都好强啊（Orz）

简单的模拟题，注意细节即可 .

题解里都是用整数类型存储电话号码的，其实字符串类型更简单一些，因为字符串格式、长度一定，所以可以写出这样的判断代码：
```cpp
inline bool isTaxi(string str)
{
	return (str[0]==str[1])&&(str[0]==str[3])&&(str[0]==str[4])&&(str[0]==str[6])&&(str[0]==str[7]);
}
inline bool isPizza(string str)
{
	return (str[0]>str[1])&&(str[1]>str[3])&&(str[3]>str[4])&&(str[4]>str[6])&&(str[6]>str[7]);
}
```

我是用了一个 `vector` 来存储出租车司机电话最多的人，披萨外卖电话最多的人和女孩电话最多的人。要是有更优解就 `clear` 掉 .

完整代码：

```cpp
using namespace std;
vector<string> taxi,pizza,girl; // 记录目前最优解
int n,nowTaxi=-1,nowPizza=-1,nowGirl=-1; // 目前最优解对应的电话号码数量，初始 -1 是为了避免所有人都没有一种电话号码的情况
// xx-xx-xx
// 01234567
inline bool isTaxi(string str)
{
	return (str[0]==str[1])&&(str[0]==str[3])&&(str[0]==str[4])&&(str[0]==str[6])&&(str[0]==str[7]);
}
inline bool isPizza(string str)
{
	return (str[0]>str[1])&&(str[1]>str[3])&&(str[3]>str[4])&&(str[4]>str[6])&&(str[6]>str[7]);
}
int main()
{
	scanf("%d",&n); string Pn,name;
	for (int i=0,s;i<n;i++)
	{
		scanf("%d",&s); cin>>name; int taxiCount=0,pizzaCount=0,girlCount=0;
		for (int j=0;j<s;j++)
		{
			cin>>Pn;
			if (isTaxi(Pn)) ++taxiCount;
			else if (isPizza(Pn)) ++pizzaCount;
			else ++girlCount;
		} // 记录
		if (taxiCount==nowTaxi) taxi.push_back(name);
		if (taxiCount>nowTaxi){taxi.clear(); taxi.push_back(name); nowTaxi=taxiCount;}
		if (pizzaCount==nowPizza) pizza.push_back(name);
		if (pizzaCount>nowPizza){pizza.clear(); pizza.push_back(name); nowPizza=pizzaCount;}
		if (girlCount==nowGirl) girl.push_back(name);
		if (girlCount>nowGirl){girl.clear(); girl.push_back(name); nowGirl=girlCount;}
        // 这里一定要先判断 == 再判断 <，以 Taxi 举例，如果先判断 < 如果 < 成立的话执行 nowTaxi=taxiCount 那么此时 == 一定成立，这个人就会被插入两次 /
	} int l1=taxi.size(),l2=pizza.size(),l3=girl.size();
	printf("If you want to call a taxi, you should call: ");
	for (int i=0;i<l1-1;i++) cout<<taxi[i]<<", ";
	cout<<taxi[l1-1]<<".\n";
	printf("If you want to order a pizza, you should call: ");
	for (int i=0;i<l2-1;i++) cout<<pizza[i]<<", ";
	cout<<pizza[l2-1]<<".\n";
	printf("If you want to go to a cafe with a wonderful girl, you should call: ");
	for (int i=0;i<l3-1;i++) cout<<girl[i]<<", ";
	cout<<girl[l3-1]<<'.'; // 注意输出格式
    return 0;
}
```

---

## 作者：FiraCode (赞：0)

这是一道模拟题。

先建立 $3$ 个数组：
```cpp
int c[1210][3];//存储第i每个号码三种的个数
char st[210], name[1210][25];//名字
```

然后判断这个电话号码应该放在哪里
```cpp
int type() {
	int i, lst = 0;
	bool f1, f2;
	f1 = f2 = true;
	for(i = 1; i < 8; i++) {
		if(i % 3 == 2)
			continue;
		if(st[i] != st[lst])//号码不相等
			f1 = false;
		if(st[i] >= st[lst])//号码不递减
			f2 = false;
		lst = i;
	}
	return f1 + 2 * f2;
}
```

然后处理读入：
```cpp
m0 = m1 = m2 = 0;
for(i = 1; i <= n; ++i) {
    scanf("%d%s", &nm, name[i]);
    while(nm--) {
        scanf("%s", st);//读入号码
        c[i][type()]++;//把号码对应的类型+1
    }
}
```

然后对于 $c_{i,0},c_{i,1},c_{i,2}$ 取个最大值，然后对于每个数，若他等于对应的最大值，就输出他的名字。

完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int c[1145][3];
char st[114], name[1145][25];
int type() {
	int i, lst = 0;
	bool f1, f2;
	f1 = f2 = true;
	for(i = 1; i < 8; i++) {
		if(i % 3 == 2)
			continue;
		if(st[i] != st[lst])
			f1 = false;
		if(st[i] >= st[lst])
			f2 = false;
		lst = i;
	}
	return f1 + 2 * f2;
}
int main() {
	int n, nm, i, m0, m1, m2;
	bool first;
	scanf("%d", &n);
	m0 = m1 = m2 = 0;
	for(i = 1; i <= n; ++i) {
		scanf("%d%s", &nm, name[i]);
		while(nm--) {
			scanf("%s", st);
			c[i][type()]++;
		}
	}
	for(i = 1; i <= n; ++i)
		m0 = max(m0, c[i][0]);
	for(i = 1; i <= n; ++i)
		m1 = max(m1, c[i][1]);
	for(i = 1; i <= n; ++i)
		m2 = max(m2, c[i][2]);
	first = true;
	printf("If you want to call a taxi, you should call: ");
	for(i = 1; i <= n; ++i)
		if(c[i][1] == m1) {
			if(first)
				first = false;
			else
				printf(", ");
			printf("%s", name[i]);
		}
	printf(".\n");
	first = true;
	printf("If you want to order a pizza, you should call: ");
	for(i = 1; i <= n; ++i)
		if(c[i][2] == m2) {
			if(first)
				first = false;
			else
				printf(", ");
			printf("%s", name[i]);
		}
	printf(".\n");
	first = true;
	printf("If you want to go to a cafe with a wonderful girl, you should call: ");
	for(i = 1; i <= n; ++i)
		if(c[i][0] == m0) {
			if(first)
				first = false;
			else
				printf(", ");
			printf("%s", name[i]);
		}
	printf(".\n");
	return 0;
}
```

---

## 作者：tanghairong (赞：0)

一道不是很大的模拟，没什么思维难度。

有几个注意点：

- 注意 - 号的处理。我直接输入一个字符串 $k$ 然后忽略 $k[2]$ 和 $k[5]$。

- 注意输出的格式。

	1. 空格（在 ```call:``` 的后面有一个空格，对于每个人名，逗号后都有一个空格）。
    
   1. 需要有一个标记变量判定是不是第一个人，如果不是就要在前面输出一个逗号加一个空格。
   
   1. 句号。
   
- 如果你跟我一样三次用的是同一个标记的话，记得每次把标记归位

其他的，就没什么好说的了，按照要求模拟即可。

code：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[105],b[105],c[105];
string name[105];
int main(){
    int n,maxa=0,maxb=0,maxc=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num>>name[i];
        while(num--){
            string k;
            cin>>k;
                if(k[0]==k[1]&&k[1]==k[3]&&k[3]==k[4]&&k[4]==k[6]&&k[6]==k[7])a[i]++;
                else if(k[0]>k[1]&&k[1]>k[3]&&k[3]>k[4]&&k[4]>k[6]&&k[6]>k[7])b[i]++;
                else c[i]++;
        }
        maxa=max(maxa,a[i]);
        maxb=max(maxb,b[i]);
        maxc=max(maxc,c[i]);
    }
    int bj=0;
    cout<<"If you want to call a taxi, you should call: ";
    for(int i=1;i<=n;i++){
        if(a[i]==maxa){
            if(bj==0)cout<<name[i],bj=1;
            else cout<<", "<<name[i];
        }
    }
    printf(".\nIf you want to order a pizza, you should call: ");
    bj=0;
    for(int i=1;i<=n;i++){
        if(b[i]==maxb){
            if(bj==0)cout<<name[i],bj=1;
            else cout<<", "<<name[i];
        }
    }
    printf(".\nIf you want to go to a cafe with a wonderful girl, you should call: ");
    bj=0;
    for(int i=1;i<=n;i++){
        if(c[i]==maxc){
            if(bj==0)cout<<name[i],bj=1;
            else cout<<", "<<name[i];
        }
    }
    printf(".\n");
    return 0;
}
```

---

## 作者：End_of_time (赞：0)

一道有些水的题目，可以当作新手上路的练习

[Click Here](https://www.luogu.com.cn/problem/CF151B)

这道题坑点不多，主要是**输出格式**和**数位判断**。

我们来一步步看：



# 1.存储

首先，用一个结构体存储每个人的信息（每种电话号码的数量）

```cpp
const int N = 1e2 + 1;
struct Telephone {
	int s, taxi, pizza, girl;
	string name;
} t[N];
```
意思应该很明白了。


# 2.统计电话类别

然后，我们可以在输入时进行电话类别的统计。

```cpp
for(register int i = 1; i <= n; ++ i) {
		cin >> t[i].s >> t[i].name;
		for(register int j = 1; j <= t[i].s; ++ j) {
			string tel;
			cin >> tel;
			int A = tel[0] - '0', B = tel[1] - '0', C = tel[3] - '0', D = tel[4] - '0', E = tel[6] - '0', F = tel[7] - '0';
			if(A == B && B == C && C == D && D == E && E == F) ++ t[i].taxi;
			else if(A > B && B > C && C > D && D > E && E > F) ++ t[i].pizza;
			else ++ t[i].girl;
		}
	}
```
可以读入一个字符串，像我这样分离出来，这样处理会少一些代码量。

不过其实也可以直接用 char 来比较。

# 3.输出

最后就是 ~~万恶~~ 善良的输出了

```cpp
cout << "If you want to call a taxi, you should call: ";
	int Max = INT_MIN, Cnt = 0, tCnt = 1;
	for(register int i = 1; i <= n; ++ i) 
		if(t[i].taxi > Max) Max = t[i].taxi;
        
	for(register int i = 1; i <= n; ++ i)  
		if(t[i].taxi == Max) Cnt ++;
        
	for(register int i = 1; i <= n; ++ i)
		if(t[i].taxi == Max) {
			if(tCnt != Cnt) cout << t[i].name << ", ";
			else cout << t[i].name << ".";
			++ tCnt;
		}

//其他两个的与这个大体相同，不放了
```

我输出的思路是，先找到这里面的最大值，然后**再找一遍有几个最大值**（这样方便后面输出判断）。

最后输出时，判断这是不是最大值。如果是，再判断是不是最后一个。（代码看起来有些麻烦）


# 4.完整代码
```cpp
#include<iostream>
#include<climits>
using namespace std;
const int N = 1e2 + 1;
int n;
struct Telephone {
	int s, taxi, pizza, girl;
	string name;
} t[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(register int i = 1; i <= n; ++ i) {
		cin >> t[i].s >> t[i].name;
		for(register int j = 1; j <= t[i].s; ++ j) {
			string tel;
			cin >> tel;
			int A = tel[0] - '0', B = tel[1] - '0', C = tel[3] - '0', D = tel[4] - '0', E = tel[6] - '0', F = tel[7] - '0';
			if(A == B && B == C && C == D && D == E && E == F) ++ t[i].taxi;
			else if(A > B && B > C && C > D && D > E && E > F) ++ t[i].pizza;
			else ++ t[i].girl;
		}
	} cout << "If you want to call a taxi, you should call: ";
	int Max = INT_MIN, Cnt = 0, tCnt = 1;
	for(register int i = 1; i <= n; ++ i) 
		if(t[i].taxi > Max) Max = t[i].taxi;
	for(register int i = 1; i <= n; ++ i)  
		if(t[i].taxi == Max) Cnt ++;
	for(register int i = 1; i <= n; ++ i)
		if(t[i].taxi == Max) {
			if(tCnt != Cnt) cout << t[i].name << ", ";
			else cout << t[i].name << ".";
			++ tCnt;
		}
	cout << "\nIf you want to order a pizza, you should call: ";
	Max = INT_MIN, Cnt = 0, tCnt = 1;
	for(register int i = 1; i <= n; ++ i) 
		if(t[i].pizza > Max) Max = t[i].pizza;
	for(register int i = 1; i <= n; ++ i)  
		if(t[i].pizza == Max) Cnt ++;
	for(register int i = 1; i <= n; ++ i)
		if(t[i].pizza == Max) {
			if(tCnt != Cnt) cout << t[i].name << ", ";
			else cout << t[i].name << ".";
			++ tCnt;
		}
	cout << "\nIf you want to go to a cafe with a wonderful girl, you should call: ";
	Max = INT_MIN, Cnt = 0, tCnt = 1;
	for(register int i = 1; i <= n; ++ i) 
		if(t[i].girl > Max) Max = t[i].girl;
	for(register int i = 1; i <= n; ++ i)  
		if(t[i].girl == Max) Cnt ++;
	for(register int i = 1; i <= n; ++ i)
		if(t[i].girl == Max) {
			if(tCnt != Cnt) cout << t[i].name << ", ";
			else cout << t[i].name << ".";
			++ tCnt;
		}
	return 0;
}
```
（第一次写题解，希望管理员大大能通过awa)

---

## 作者：Southern_Dynasty (赞：0)

小模拟。~~但是我写了半个小时我太菜了~~

写一个 `struct`，记录一下每个人的电话号码数量，名字，记录的所有电话号码以及三种号码的数量。

三种号码：

$1.$ 司机号码： `xx-xx-xx`，其中六个数字全部相同。

$2.$ 外卖电话： `xx-xx-xx`，由六个递减的数字构成。

$3.$ 女生电话： `xx-xx-xx`，和前两个不一样的都是。

写个函数判断一下就行了。

坑点（至少本蒟蒻一开始没发现）：如果有多个人的电话数量是一样的，按照输入顺序挨个输出，而不是只输出最早的。

维护三个 `string` 数组和三个指针，将符合条件的朋友的名字加入数组即可完成答案的存储（当然用 `vector` 也可以，就不用维护指针了）。

最后，要注意输出格式：冒号和逗号后面有空格，而句点无空格，最后一个人的名字后面没有逗号，行末还要输出换行。

然后就做完了。

代码：

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define y1 y233
//#define int long long
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
const int N=205;
using namespace std;
inline int read(){
   	int x=0,f=1;char ch=gt();
   	while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
   	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}
	return x*f;
}
inline void print(int x){
    if(x<0)pt('-'),x=-x;
    if(x>9)print(x/10);
    pt(x%10+48);
}
inline void println(int x){
	print(x);
	pt(10);
}
int n,cnt1,cnt2,cnt3,tot1,tot2,tot3;
struct Person{
	int s,mp1,mp2,mp3;
	string name,id[N];
}a[N];
string ans1[N],ans2[N],ans3[N];
inline bool check1(string s){
	if((s[0]==s[1])&&(s[1]==s[3])&&(s[3]==s[4])&&(s[4]==s[6])&&(s[6]==s[7]))return 1;
	else return 0;
}
inline bool check2(string s){
	if((s[0]>s[1])&&(s[1]>s[3])&&(s[3]>s[4])&&(s[4]>s[6])&&(s[6]>s[7]))return 1;
	else return 0;
}
inline bool check3(string s){
	return !(check1(s)||check2(s));
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i].s=read();
		cin>>a[i].name;
		for(int j=1;j<=a[i].s;++j){
			cin>>a[i].id[j];
			if(check1(a[i].id[j]))a[i].mp1++;
			if(check2(a[i].id[j]))a[i].mp2++;
			if(check3(a[i].id[j]))a[i].mp3++;
		}
	}
	for(int i=1;i<=n;++i)if(cnt1<a[i].mp1)cnt1=a[i].mp1;
	for(int i=1;i<=n;++i)if(cnt2<a[i].mp2)cnt2=a[i].mp2;
	for(int i=1;i<=n;++i)if(cnt3<a[i].mp3)cnt3=a[i].mp3;
	for(int i=1;i<=n;++i)
		if(a[i].mp1==cnt1)ans1[++tot1]=a[i].name;
	for(int i=1;i<=n;++i)
		if(a[i].mp2==cnt2)ans2[++tot2]=a[i].name;
	for(int i=1;i<=n;++i)
		if(a[i].mp3==cnt3)ans3[++tot3]=a[i].name;
	cout<<"If you want to call a taxi, you should call: ";
	for(int i=1;i<=tot1;++i){
		cout<<ans1[i];
		if(i!=tot1)cout<<", ";
	}
	cout<<".\n";
	cout<<"If you want to order a pizza, you should call: ";
	for(int i=1;i<=tot2;++i){
		cout<<ans2[i];
		if(i!=tot2)cout<<", ";
	}
	cout<<".\n";
	cout<<"If you want to go to a cafe with a wonderful girl, you should call: ";
	for(int i=1;i<=tot3;++i){
		cout<<ans3[i];
		if(i!=tot3)cout<<", ";
	}
	cout<<".";
	return 0;
}
```


---

## 作者：_Kouki_ (赞：0)

### 题目思路
这题就是大模拟。   

枚举每个人女孩，出租车，披萨人的电话个数。   
重点是电话号码的判断。

其次要注意输出时的**空格，逗号和句点**。   
眼睛得看仔细了！

下面就到了代码部分。   
基本注释写的满满的。   
### 题目代码
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int M_Car,M_Piz,M_Gir;         //汽车，披萨，好康女孩 的最大值
string N_Car[110],N_Piz[110],N_Gir[110];//用来存姓名的
int l1,l2,l3;//这个是用来 存储同样值的人名个数 
int n;//py
int main()
{
    scanf("%d",&n);//输入
    for(int i=1;i<=n;++i){//循环
        int s;//电话数
        string name;//此人人名
        scanf("%d",&s);//输入
        cin>>name;//再输
        int S_Car=0,S_Piz=0,S_Gir=0;//显而易见这是统计不同电话的个数
        for(int j=1;j<=s;++j){//循环
            string res;//电话号码
            cin>>res;//输入
            int tmp[10],lt=0;//tmp[] 用来存数字，lt 和上面的l1,l2,l3差不多
            for(int k=1;k<res.size();++k){//循环
                if(res[k]=='-') continue;//不是数字
                tmp[++lt]=res[k]-'0';//是数字存进来
            }
            bool f1=0,f2=0;//f1判断递减 f2判断完全相同
            for(int k=2;k<=lt;++k){//循环
                if(tmp[k-1]<=tmp[k]){//不行了
                    f1=1;
                }
                if(tmp[k-1]!=tmp[k]){//不行了
                    f2=1;
                }
            }if(!f2) S_Car++; else//这里的
            if(!f1) S_Piz++; else//顺序
            S_Gir++;//十分关键
        }
        if(M_Car==S_Car) {
            N_Car[++l1]=name;
        }
        if(M_Piz==S_Piz) {
            N_Piz[++l2]=name;
        }
        if(M_Gir==S_Gir) {
            N_Gir[++l3]=name;
        }
        //这里都是加相同值的人名
        if(M_Car<S_Car) {
            l1=0;
            M_Car=S_Car;
            N_Car[++l1]=name;
        }
        if(M_Piz<S_Piz) {
            l2=0;
            M_Piz=S_Piz;
            N_Piz[++l2]=name;
        }
        if(M_Gir<S_Gir) {
            l3=0;
            M_Gir=S_Gir;
            N_Gir[++l3]=name;
        }
        //不同了，打擂台，换掉，清空所有人名，加如当前人名
    }
    printf("If you want to call a taxi, you should call:");
    for(int i=1;i<=l1;++i){
        printf(" ");
        cout<<N_Car[i];
        if(i!=l1)printf(",");else printf(".\n");
    }
    printf("If you want to order a pizza, you should call:");
    for(int i=1;i<=l2;++i){
        printf(" ");
        cout<<N_Piz[i];
        if(i!=l2)printf(",");else printf(".\n");
    }
    printf("If you want to go to a cafe with a wonderful girl, you should call:");
    for(int i=1;i<=l3;++i){
        printf(" ");
        cout<<N_Gir[i];
        if(i!=l3)printf(",");else printf(".\n");
    }
    //以上是输出没甚么好说的
    return 0;
    //完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。
}
```

---

## 作者：ckk11288 (赞：0)

**算法**：**模拟**

**难点**：输出格式与题面理解。

**实现**：使用结构体完成数据存储，用另外三个数组输出答案。

**具体步骤**：在输入过程中判断类型并完成统计，算出最大值。接着依照题意用答案数组存储答案，最后输出。

**注意**：输出格式真的很重要，请仔细阅读题目。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int pizza,taxi,girl;//数组用途
	char name[101];//人名
}a[101];
int n,m;
string ans1[101],ans2[101],ans3[101];
int cnt1,cnt2,cnt3; //答案数组以及存储计数变量
int check(string x){
	if(x[0]>x[1]&&x[1]>x[3]&&x[3]>x[4]&&x[4]>x[6]&&x[6]>x[7])
	{
		return 1;//pizza
	}
	else if(x[0]==x[1]&&x[1]==x[3]&&x[3]==x[4]&&x[4]==x[6]&&x[6]==x[7])
	{
		return 0;//taxi
    }
	else return 2;//girl
}//check函数判断电话号码类型
int main()
{
	int maxg=0,maxt=0,maxp=0;//最大值变量
	scanf("%d",&n);
	for(int k=1;k<=n;k++)
	{
		scanf("%d%s",&m,a[k].name);
		for(int i=1;i<=m;i++)
		{
			string b;
			cin>>b;
			if(check(b)==1)	a[k].pizza++,maxp=max(maxp,a[k].pizza);
			else if(check(b)==0)a[k].taxi++,maxt=max(maxt,a[k].taxi);
			else a[k].girl++,maxg=max(maxg,a[k].girl);//统计，计算每种号码类型的最大值
		}
	}
	for(int k=1;k<=n;k++)
	{
		if(a[k].girl==maxg)++cnt1,ans1[cnt1]=a[k].name;
		if(a[k].pizza==maxp)++cnt2,ans2[cnt2]=a[k].name;
		if(a[k].taxi==maxt)++cnt3,ans3[cnt3]=a[k].name;
	}//存储答案
	cout<<"If you want to call a taxi, you should call: ";
	cout<<ans3[1];
	for(int i=2;i<=cnt3;++i)
	cout<<", "<<ans3[i];
	cout<<"."<<endl;
	cout<<"If you want to order a pizza, you should call: ";
	cout<<ans2[1];
	for(int i=2;i<=cnt2;++i)
	cout<<", "<<ans2[i];
	cout<<"."<<endl;
	cout<<"If you want to go to a cafe with a wonderful girl, you should call: ";
	cout<<ans1[1];
	for(int i=2;i<=cnt1;++i)
	cout<<", "<<ans1[i];
	cout<<"."<<endl;
	//输出 
	return 0;
}
```

---

## 作者：ylinxin2010 (赞：0)

## CF151B题解
这题首先只要枚举就行了

判断是哪种情况再对应的计数器 $+1$

依次比较 $m1, m2, m3$ 求出最大值

最后当条件满足就输出(还要判断是否要逗号，并且不要忘记句号)

接下来——上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	bool f=true;
	string name[n+5];
	int a[n+5]={0},b[n+5]={0},c[n+5]={0},m1=0,m2=0,m3=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x>>name[i]; 
		for(int j=1;j<=x;j++)
		{
			string ph;
			cin>>ph;
			if(ph[0]>ph[1]&&ph[1]>ph[3]&&ph[3]>ph[4]&&ph[4]>ph[6]&&ph[6]>ph[7])
				a[i]++;
			else if(ph[0]==ph[1]&&ph[1]==ph[3]&&ph[3]==ph[4]&&ph[4]==ph[6]&&ph[6]==ph[7])
				b[i]++;
			else
				c[i]++;
		}
		if(a[i]>m1)
			m1=a[i];
		if(b[i]>m2)
			m2=b[i];
		if(c[i]>m3)
			m3=c[i];
	}	
	cout<<"If you want to call a taxi, you should call: ";
	for(int i=1;i<=n;i++)
	{
		if(m2==b[i])
		{
			if(f)
			{
				cout<<name[i];
				f=false;
			}
			else
				cout<<", "<<name[i];
		}
	}
	f=true;
	cout<<"."<<endl;
	cout<<"If you want to order a pizza, you should call: ";
	for(int i=1;i<=n;i++)
	{
		if(m1==a[i])
		{
			if(f)
			{
				cout<<name[i];
				f=false;
			}
			else
				cout<<", "<<name[i];
		}
	}
	f=true;
	cout<<"."<<endl;
	cout<<"If you want to go to a cafe with a wonderful girl, you should call: ";
	for(int i=1;i<=n;i++)
	{
		if(m3==c[i])
		{
			if(f)
			{
				cout<<name[i];
				f=false;
			}
			else
				cout<<", "<<name[i];
		}
	}
	cout<<".";
	return 0;
}
```
author：ylinxin2010

---

