# [COCI 2022/2023 #2] Prijateljice

## 题目描述

Leona 和 Zoe 拿到了一些单词。他们打算用这些单词玩一个游戏：

在每一个回合中，两人轮流说单词。这个单词需要满足以下要求：

它比前一个单词的字典序大，且开头字母必须和前一个字母相同，或在字母表上正好在前一个单词的开头字母的后面一个。

Leona 先说，他会选择字典序最小的单词说出来。轮到谁时，他说不出单词了，他就输了。

两人在玩这个游戏时，都会采用最优策略，也就是说，选择符合条件的单词中字典序最小的那个。

现在他们想知道，谁会赢呢。

## 说明/提示

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$20$|$n,m\le100$，每个单词的长度不超过 $10$|
|$2$|$30$|$n,m\le1000$|
|$3$|$60$|无|

**本题满分 $110$ 分。**

## 样例 #1

### 输入

```
2 1
avokado
dabar
brazil```

### 输出

```
Zoe```

## 样例 #2

### 输入

```
3 3
ananas
atlas
banana
albatros
cikla
nogomet
```

### 输出

```
Leona```

## 样例 #3

### 输入

```
2 2
hrvatska
zastava
bijeli
galeb```

### 输出

```
Leona```

# 题解

## 作者：Gaoyx (赞：3)

 这是本蒟蒻的第一篇题解，有错误请指出。

小知识 ： sort 排序字符串默认是按字典序排序的。

思路 ： 将 Leona 和 Zoe 的单词排好序后，每次寻找 Leona 和 Zoe 是否有单词可说，若没有就输出赢家，
若有就继续循环。

附代码：

```
#include<bits/stdc++.h>
using namespace std;
int n , m;
string l[100001], z[100001];
int lmi = 2, zmi = 1;
/*
	lmi：lmi每次存Leona说出单词位置，再从lmi找到n,
	因为lmi之前要比现在说出单词要小，所以没必要找。 
	zmi: 同理。 
*/
int ansl = 1, ansz = 1;
/*
	ansl：记入Leona是否还能说出单词。 
	ansz：记入Zoe是否还能说出单词。 
*/
string nowl, nowz;
/*
	nowl：记入Leona说出的单词的最后一个。 
	nowz：记入Zoe出的单词的最后一个。 
*/
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		cin >> l[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin >> z[i];
	}
	sort(l+1,l+n+1);
	sort(z+1,z+m+1);// 排序 
	nowl = l[1];
	while(ansl&&ansz)//其中一个没有答案就跳出 
	{
		ansl = ansz = 0;
		for(int i=zmi;i<=m;i++)
		{
			char w = nowl[0] + 1;
			if((z[i][0] == nowl[0]&&z[i] > nowl)||(w == z[i][0]))
			{
				nowz = z[i];//如果Zoe可以说就更新nowz，zmi，ansz。 
				zmi = i + 1;
				ansz = 1;
				break;
			}
		}
		if(!ansz)
		{
			ansl = 1;
			break;
		}
		for(int i=lmi;i<=n;i++)
		{
			char w = nowz[0] + 1;
			if((l[i][0] == nowz[0]&&l[i] > nowz)||(l[i][0] == w))
			{
				nowl = l[i];//如果Leona可以说就更新nowl，lmi，ansl。 
				lmi = i + 1;
				ansl = 1;
				break;
			}
		}
		if(!ansl)
		{
			ansz = 1;
			break;
		}
	}
	if(!ansz) cout << "Leona";
	else cout << "Zoe";
	return 0;//功德圆满 
} 
```


---

## 作者：Tjaweiof (赞：2)

# [COCI2022-2023#2] Prijateljice 题解
[题目传送门](https://www.luogu.com.cn/problem/P9738)

利用双指针模拟说单词的过程，因为每次说出来的单词都要比前一个单词的字典序大，所以每次操作完指针不用变成 $1$。另外，需要加一点特判：当指针大于单词数时，这个人就输了。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt1, cnt2;
string a[100002], b[100002];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int j = 1; j <= m; j++){
        cin >> b[j];
    }
    cnt1 = 1;
    cnt2 = 1;
    while (true){
        while (b[cnt2] < a[cnt1] && cnt2 <= m){
            cnt2++;
        }
        if (b[cnt2][0] > a[cnt1][0] + 1 || cnt2 > m){
            cout << "Leona";
            return 0;
        }
        while (b[cnt2] > a[cnt1] && cnt1 <= n){
            cnt1++;
        }
        if (b[cnt2][0] + 1 < a[cnt1][0] || cnt1 > n){
            cout << "Zoe";
            return 0;
        }
    }
    return 0;
}
```
**此代码时间复杂度 $O(n+m)$，空间复杂度 $O(n+m)$，完美过关！**

---

## 作者：lichenzhen (赞：2)

## 题目大意
Leona 和 Zoe 玩游戏，轮流说单词，说的单词必须比上一个单词字典序大，且以相同字母或下一个字母开头。Leona 先开始，直到有一方没有符合要求的单词为止。

给出他们有的单词，求最终谁会获胜。

## 题目解法
一道比较简单的模拟题，按照题意模拟。

因为题目描述里说明是按照字典序输入的，所以我们就按照这个顺序进行循环，寻找符合条件的单词，没有符合条件的单词直接跳出。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[100010],b[100010],na,nb;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	int ab=2,bb=1,jg=-1,f1=0,f2=0; 
	na=a[1];
	while(1){
		f1=0;
		for(int i=bb;i<=m;i++){//寻找Zoe符合条件的单词
			bool f=b[i]>na;
			if((na[0]==b[i][0]&&f==1)||b[i][0]==na[0]+1){
				nb=b[i];
				f1=1;
				bb=i+1;
				break;
			}
		}
		if(f1==0){
			jg=1;
			break;
		}
		f2=0;
		for(int i=ab;i<=n;i++){//寻找Leona符合条件的单词
			bool f=a[i]>nb;
			if((nb[0]==a[i][0]&&f==1)||a[i][0]==nb[0]+1){
				na=a[i];
				f2=1;
				ab=i+1;
				break;
			}
		}
		if(f2==0){
			jg=0;
			break;
		}
	}
	if(jg==0) cout<<"Zoe";
	else cout<<"Leona";
}
```

---

## 作者：yydfj (赞：2)

这是本蒟蒻第四十一次写的题解，如有错误点请好心指出！

因为两人都会选符合条件的单词中字典序最小的那一个，所以先给所有单词标记好是谁拥有的，并合在一起按字典序排序，用 string 可以自动按字典序比较。

根据题意，Leona 会先说出字典序最小的单词，然后按排好序的单词中找 Zoe 会说出的单词，依次轮回即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	string s;//用string可以自动按字典序比较
	int id;//1指Leona拥有的单词，2指Zoe拥有的单词
}a[200005];
bool cmp(node x,node y){return x.s<y.s;}
int n,m,k=1,bz,bz1;//k表示当前属于谁的回合
string s1;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) cin>>a[i].s,a[i].id=1;
	for(int i=n+1;i<=n+m;i++) cin>>a[i].s,a[i].id=2;
	stable_sort(a+1,a+n+m+1,cmp);
	for(int i=1;i<=n+m;i++)
	if(a[i].id==k)
	{
		if(!bz) s1=a[i].s,bz=bz1=1;
		else if(s1[0]==a[i].s[0]||(s1[0]<'z'&&s1[0]+1==a[i].s[0])) s1=a[i].s,bz1=1;
		if(bz1)//改变回合
		{
			if(k==1) k=2;
			else k=1;
			bz1=0;
		}
	}
	if(k==1) printf("Zoe");
	else printf("Leona");
	return 0;
}
```

---

## 作者：Lyrith_with_xQ (赞：1)

首先，[读题!](https://www.luogu.com.cn/problem/P9738)

思路
-
我们可以使用双指针的方法模拟 Leona 和 Zoe 取单词的过程，如果某个时刻 Leona 的单词中没有符合要求的单词了，则 Zoe 胜，否则 Leona 胜。

因为他们每次优先取字典序最小的单词，所以要提前把他们的单词排个序。

代码
-
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
string a[100005],b[100005];

bool check(string m,string t)//查询上一个字符串是m时字符串t是否符合要求
{
	if(m>=t)return false;
	else if(m[0]!=t[0]&&m[0]!=(t[0]-1))return false;
	else return true;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(a+1,a+n+1);//对两个字符串组进行排序，保证取到的是字典序最小的字符串
	sort(b+1,b+m+1);
	for(int i=1/*第一轮Leona一定会取字符串组a中第一个字符串*/,j=1;i<=n||j<=m;)
	{
		while(j<=m&&!check(a[i],b[j]))j++;//在Zoe的字符串组中找符合要求的字符串
		if(j>m)//未找到，Leona赢了
		{
			cout<<"Leona";
			return 0;
		}
		i++;//Leona的字符串组中第i个字符串选过了，不能再选
		while(i<=n&&!check(b[j],a[i]))i++;//在Leona的字符串组中找符合要求的字符串
		if(i>n)//未找到，Zoe赢了
		{
			cout<<"Zoe";
			return 0;
		}
		j++;//Zoe的字符串组中第j个字符串选过了，不能再选
	}
	return 0;
}
```
性能分析
-
时间复杂度：$O(n \log n+m \log m)$。

空间复杂度：$O(n+m)$。

单个测试点最高用时：$78$ ms。

可以通过本题。

---

## 作者：WsW_ (赞：1)

### 思路
用 `string` 类型存单词，可以很方便地比较字典序大小。  

先将两人能用的单词分别排序，然后查找**字典序大于上一个说出的单词，且字典序最小**的单词即可。  
我们可以直接用库函数二分 `upper_bound` 进行查找。

设 $|S|$ 为所有单词的总长度，时间复杂度为 $O(|S| \log (n+m))$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int len[2];
string s[2][100001];
string lst;
bool now;//0 表示 Leona，1 表示 Zoe
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>len[0]>>len[1];
	for(int i=1;i<=len[0];i++)cin>>s[0][i];
	for(int i=1;i<=len[1];i++)cin>>s[1][i];
	sort(s[0]+1,s[0]+len[0]+1);//对两人的单词分别排序
	sort(s[1]+1,s[1]+len[1]+1);
	lst=s[0][1];//由 Leona 开始说出自己字典序最小的单词
	while(1){
		now^=1;//轮换成另一个人
		int x=upper_bound(s[now]+1,s[now]+len[now]+1,lst)-s[now];
		if(x>len[now]||s[now][x][0]-lst[0]>1){
			if(now)cout<<"Leona";//Zoe 输，则 Leona 赢
			else cout<<"Zoe";
			break;
		}
		lst=s[now][x];//更新上一个说的单词
	}
	return 0;
}
```
---
### 优化
假设某个人说了排序后的第 $i$ 个单词，那么下一次说的单词必然在 $i$ 之后。  
于是可以给两个人各一个指针，指针记录上一次说的是啥。  
下一次只需要**指针后移**直到**发现无解**或者**找到符合要求的单词**即可。

时间复杂度为 $O(|S|+n\log n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int len[2];
string s[2][100001];
string lst;
int p[2];
bool now;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>len[0]>>len[1];
	for(int i=1;i<=len[0];i++)cin>>s[0][i];
	for(int i=1;i<=len[1];i++)cin>>s[1][i];
	sort(s[0]+1,s[0]+len[0]+1);
	sort(s[1]+1,s[1]+len[1]+1);
	p[0]=1;//一开始 Leona 说了一个单词，所以他的指针初始为1
	lst=s[0][1];
	while(1){
		now^=1;
		while(++p[now]<=len[now]&&s[now][p[now]]<=lst);
        //指针后移
		int x=p[now];
		if(x>len[now]||s[now][x][0]-lst[0]>1){
			if(now)cout<<"Leona";
			else cout<<"Zoe";
			break;
		}
		lst=s[now][x];
	}
	return 0;
}
```

---

## 作者：TruchyR (赞：1)

## Part 1 思路
这里是一个不想要双指针的人。  
首先，把 Leona 和 Zoe 的单词放在一起排序（记得记录是谁的单词）。  
然后找到第一张 Leona 的卡片，开始模拟：  
- 每次从上一个人选的单词开始向后遍历，寻找第一个己方的单词。  
- 如果找不到，那么这个人就输了。  
如果找得到，但是不符合首字母要求，那么这个人也输了。  
- 否则继续模拟直到得出结果。  

## Part 2 代码
记得要判断相同的单词，虽然不加也可以过。  
```
#include<bits/stdc++.h>
#define MX 200005
using namespace std;
int n,m;
struct eg{string a;int b,t;}p[MX];
//eg.a:字符串 eg.b:0/1表示是谁的单词 eg.t:0~25表示首字母。
bool cmp(eg xx,eg yy){return xx.a<yy.a;}
int dfs(int l,int op){
	int u=l,lst=p[l].t;
	while(p[u].b!=op && u<=n+m || p[u].a==p[l].a) u++;
	if(u>n+m) return (op^1); //找不到
	int nw=p[u].t;
	if(nw-lst>1) return (op^1); //不符合要求
	return dfs(u,op^1);
}
signed main(){
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		p[i].b=0;
		cin>>p[i].a;
	}
	for(int i=1;i<=m;i++){
		p[i+n].b=1;
		cin>>p[i+n].a;
	}
	sort(p+1,p+1+n+m,cmp);
	for(int i=1;i<=n+m;i++)//寻找第一个 Leona 的单词。
		p[i].t=(p[i].a[0]-'a');
	int o=1;
	while(p[o].b) o++;
	o=dfs(o,1);
	if(!o) cout<<"Leona";
	else cout<<"Zoe";
	return 0;
}
```


---

## 作者：tallnut (赞：1)

这题其实就是一道大模拟，但是细节很多，~~我交了整整 23 次才弄好！！！~~

# 思路
使用 $i,j$ 两个变量对着存储所有字符串的数组扫一遍，如果在循环过程中超出 $n,m$ 的范围则判定出赢家，结束程序。

具体来说，内部需要两个 while 循环，如果当前的 $i,j$ 仍然不符合条件则继续循环。

但是有几个坑点：
1. 如果内部的 while 循环根本没执行，说明当前的字符串就可以，这种情况下仍然需要 $i \gets i + 1$（$i$ 换成 $j$ 同理），否则可能陷入死循环。
2. 在第一点的基础上，需要两个布尔变量来记录是否更新，走到一次 for 循环的末尾时才执行 $i \gets i + 1$ 的操作。
3. 有可能前面的 for 循环未能输出答案，这时我们需要在 main() 末尾再加一条判断语句。

# 代码
[AC 记录](https://www.luogu.com.cn/record/129374405)。
```
#include <iostream>
using namespace std;
int n,m,tmp,i,j;
bool moved1,moved2;
string a[100001],b[100001];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (i = 1;i <= n;i++)
		cin >> a[i];
	for (i = 1;i <= m;i++)
		cin >> b[i];
	for (i = 1,j = 1;i <= n && j <= m;)
	{
		//Zoe
		tmp = b[j][0] - a[i][0];
		moved1 = false;
		while (tmp >= 2 || b[j] < a[i])
		{
			moved1 = true;
			j++;
			if (j > m)
			{
				cout << "Leona";
				return 0;
			}
			tmp = b[j][0] - a[i][0];
		}
		//Leona
		tmp = a[i][0] - b[j][0];
		moved2 = false;
		while (tmp >= 2 || a[i] < b[j])
		{
			moved2 = true;
			i++;
			if (i > n)
			{
				cout << "Zoe";
				return 0;
			}
			tmp = a[i][0] - b[j][0];
		}
		if (!moved1) j++;
		if (!moved2) i++;
	}
	if (i > n) cout << "Zoe";
	else cout << "Leona";
}
```

---

## 作者：fillemomo (赞：1)

## 思路
定义一个结构体，存储字符串 $s$，并拿到一个编号 $id$。

$id$ 为 $1$ 表示这张牌是 Leona 的，为 $2$ 表示这张牌是 Zoe 的

~~~
struct node
{
	string s;
	int id;
}a[1000005];
~~~

然后 sort 排序，定义一个函数，让排序结果按照字典序从小到大排

~~~
inline bool cmp(node a,node b)
{
	return a.s<b.s;
}
~~~

定义一个变量为 $k$，代表现在是谁出牌，$1$ 为 Leona，$2$ 为 Zoe。

循环遍历后，如果发现当前的牌的 $id$ 与当前出牌人对应的 $id$ 相等，判断这个字符串是否合法，如果合法，则变换回合

```
for(int i=1;i<=n+m;i++)
{
	if(a[i].id==k)
	{
		if(!bz) s1=a[i].s,bz=bz1=1;
		else if(s1[0]==a[i].s[0]||(s1[0]<'z'&&s1[0]+1==a[i].s[0])) s1=a[i].s,bz1=1;
		if(bz1)
		{
			if(k==1) k=2;
			else k=1;
			bz1=0;
		}
	}
}
```
如果当前的回合为 $1$，代表 Leona 没牌出了，Zoe 赢了。否则如果当前的回合为 $2$，代表 Zoe 没牌出了，Leona 赢了。

## [AC](https://www.luogu.com.cn/record/129225628)代码
```
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void RP()
{
	long long CSP_RP=0;
	while(1) CSP_RP+=1e18;
}
struct node
{
	string s;
	int id;
}a[1000005];
inline bool cmp(node a,node b)
{
	return a.s<b.s;
}
int n,m,k=1,bz,bz1;
string s1;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].s;
		a[i].id=1;
	}
	for(int i=n+1;i<=m+n;i++)
	{
		cin>>a[i].s;
		a[i].id=2;
	}
	stable_sort(a+1,a+n+m+1,cmp);
	for(int i=1;i<=n+m;i++)
	{
		if(a[i].id==k)
		{
			if(!bz) s1=a[i].s,bz=bz1=1;
			else if(s1[0]==a[i].s[0]||(s1[0]<'z'&&s1[0]+1==a[i].s[0])) s1=a[i].s,bz1=1;
			if(bz1)
			{
				if(k==1) k=2;
				else k=1;
				bz1=0;
			}
		}
	}
	if(k==1) puts("Zoe");
	else puts("Leona");
	

	return 0;
}
```

---

## 作者：UniGravity (赞：0)

## Solution P9738 [COCI2022-2023#2] Prijateljice

[Luogu传送门](https://www.luogu.com.cn/problem/P9738)  

一开始读错题了（小丑.jpg）

### 思路分析
每次说的单词字典序要最小，分别对两人的单词排序后按题意模拟即可。

由于字典序只升不降，每次选出最小的单词。

至于找出最小的单词，我这里用的是 `vector`，先排序再查找，可以做到 $O(n\log n)$。

### 完整代码
这题挺简单的，具体实现看代码吧。
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector< string > leona, zoe;

bool cmp(string x, string y) {
	return x > y;
}

int main() {
    cin >> n >> m;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        leona.push_back(s);
    }
    for (int i = 1; i <= m; i++) {
        cin >> s;
        zoe.push_back(s);
    }
    sort(leona.begin(), leona.end(), cmp);
    sort(zoe.begin(), zoe.end(), cmp);
    
    string lst = leona.back();
    leona.pop_back();
    
    string now;
    
    while (true) {
    	while (zoe.size() && zoe.back() <= lst) {
    		zoe.pop_back();
		}
		if (zoe.size() <= 0) {
		    puts("Leona");
		    return 0;
		}
		now = zoe.back();
		if (now <= lst || now[0] - lst[0] > 1) {
			puts("Leona");
			return 0;
		}
		lst = now;
		
    	while (leona.size() && leona.back() <= lst) {
    		leona.pop_back();
		}
		if (leona.size() <= 0) {
		    puts("Zoe");
		    return 0;
		}
		now = leona.back();
		if (now <= lst || now[0] - lst[0] > 1) {
			puts("Zoe");
			return 0;
		}
		lst = now;
	}
    return 0;
}
```

---

## 作者：Crasole (赞：0)

## 题意

Leona 和 Zoe 有一些单词，两人轮流说单词，每次说的单词要满足以下条件：

- 字典序比上一个大。

- 开头字母必须和前一个字母相同，或在字母表上正好在前一个单词的开头字母的后面一个。

两人每次都会说满足条件的字典序最小的单词，如果谁已经没有满足条件的单词，那么他就输了。

问：谁能赢。

## 思路

因为每次说的单词字典序要最小，所以我们可以先给单词排序，然后按照题意模拟即可。

每次用 $l\_last$ 和 $z\_last$ 来分别记录两人说的上一个单词，再用 $ls$ 和 $zs$ 来表示两人本轮是否说了单词。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 4;
int n, m; 
bool ls, zs;
string l_s[N], z_s[N], l_last = " ", z_last = " ";
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> l_s[i];
	for(int j = 1; j <= m; j++)
		cin >> z_s[j];
   //排序
	sort(l_s + 1, l_s + n + 1);
	sort(z_s + 1, z_s + m + 1);
	int i = 1, j = 1;
	while(1) {
		ls = zs = 0;
		for(; i <= n; i++)
			if(z_last == " ") {//Leona先手，做特判
				ls = 1, l_last = l_s[i];
           //记录说过得单词，并标记为说过
				break;
			}
			else 
				if(l_s[i] >= z_last && 
            (l_s[i][0] == z_last[0] || 
            l_s[i][0] == z_last[0] + 1)){
          //判断是否满足条件
					ls = 1, l_last = l_s[i];
					break;
				}
		if(!ls) {//判断是否说过
			cout << "Zoe\n";
			break;
		}
		for(; j <= m; j++)
			if(z_s[j] >= l_last && 
            (z_s[j][0] == l_last[0] || 
            z_s[j][0] == l_last[0] + 1)){
				zs = 1, z_last = z_s[j];
				break;
			}
			//同上	
		if(!zs) {
			cout << "Leona\n";
			break;
		}
	}
	return 0;
} 
```

---

## 作者：linyukun (赞：0)

## 1. 前言
本文的分析会比较通俗，自己要多去思考，麻烦一定 _仔细全部看完_，有异议、不懂或认为可以优化请私信反馈呢。  

## 2. 题目解析：
首先，这是一道比较纯的模拟题，按十分详细的题目要求，我们分析一下。  
自然，可以按照题面原意模拟，但不妨尝试一个崭新且易懂的思路。  
那就是：**将所有单词全部排序后依次查询输出**。  主要的操作如下：  
* 将 $1 \sim ( n + m )$ 的单词统一存储并排序。  
* 从前往后依次找，不用担心字典序了。
* 合法就更新结果，在首字母差距过大时就直接跳出。
* 最后的答案就是记录的“最后报数人”。

## 3. 提示要点：
* 注意存储空间的输入，是 $1 \sim ( n + m )$。
* $k$ **并不从 $1$ 开始**，而是**第一个人报的单词的下一个**。
* 找到第一个报的单词，它被报了，所以**要存入 $last$**，而且**它的下一个才是 $k$**。
* 存储 $last$ ，**上一个单词并不是 $k - 1$**。
* 判断 $k \le ( n + m ) $，否则会发生越界问题。

## 4. 代码写作：
理论存在，实践开始。  

代码理有详细的注释幺~
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k=1,l=1,last;
struct aaa{
	string s;
	int num;
}a[200010];
/*
n:第一个人的数量
m:第二个人的数量
k:第几个单词
l:上一个报的人（1=L，2=Z）
last:上一个报的单词序号
a:总的单词数组
s:单词本身
num:单词属于谁
*/
bool cmp(aaa a,aaa b){
	return a.s<b.s;//默认字典序
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i].s;
    	a[i].num=1;
	}
	for(int i=n+1;i<=n+m;i++){//这里是因为前n个已经被占用
    	cin>>a[i].s;
    	a[i].num=2;
	}
	sort(a+1,a+1+n+m,cmp);//排序
	while(a[k].num==2)k++;//找到第一个报出的单词
	last=k;
	k++;//跳下一个开始找
	while(a[k].s[0]-a[last].s[0]<2&&k<=n+m){//首字母不能相差大于1 && 不能越界
		if(l==1&&a[k].num==2){
			//若可合法报出，改变“上一个报的人”，更新“上一个报的单词序号”。
			l=2;
			last=k;
		}
		else if(l==2&&a[k].num==1){
			//同理
			l=1;
			last=k;
		}
		k++;
	}
	//谁报出最后一个就胜利
	if(l==1){
		cout<<"Leona";
	}
	else{
		cout<<"Zoe";
	}
    return 0;
}
```

## 5. 总结鸣谢：
**本题是一道考验耐心思维的模拟，难度适中，细节较多。**  
**另：还有感谢管理大大的的审核。**

---

