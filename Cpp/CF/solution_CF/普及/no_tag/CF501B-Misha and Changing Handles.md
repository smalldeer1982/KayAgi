# Misha and Changing Handles

## 题目描述

Misha hacked the Codeforces site. Then he decided to let all the users change their handles. A user can now change his handle any number of times. But each new handle must not be equal to any handle that is already used or that was used at some point.

Misha has a list of handle change requests. After completing the requests he wants to understand the relation between the original and the new handles of the users. Help him to do that.

## 样例 #1

### 输入

```
5
Misha ILoveCodeforces
Vasya Petrov
Petrov VasyaPetrov123
ILoveCodeforces MikeMirzayanov
Petya Ivanov
```

### 输出

```
3
Petya Ivanov
Misha MikeMirzayanov
Vasya VasyaPetrov123
```

# 题解

## 作者：一只大龙猫 (赞：3)

看到题解区大部分用的是并查集或模拟链表的方法，这里提供一种使用队列的方法。

我们可以创建多个队列，使每个队列储存每个干员改名的过程，越旧的名字离队头越近。队头为每个人最初的姓名，队尾为当前的姓名。例如，样例输入对应的队列如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ylwpnv9y.png)

（图有点丑，请见谅……）

每输入一对新的名字，我们就遍历一遍，看看是否有队列的队尾是新输入的改名前的名字。如果找到了这样的一个队列，那么就把改名后的名字插入队尾；如果没有找到，那么就说明这是一个新的干员，我们在一个新的队列中插入改名前和改名后的名字就行了。

最后输出时，直接输出每个队列的队头和队尾就行了。

代码如下。

```cpp
#include<iostream>
#include<string>
#include<queue>
using namespace std;
int n,m;
queue<string> q[1001];
void ins(string s1,string s2){
	for(int i=1;i<=m;i++){
		if(q[i].back()==s1){
			q[i].push(s2);
			return;
		}
	}
	m++;
	q[m].push(s1);
	q[m].push(s2);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		string s1,s2;
		cin>>s1>>s2;
		ins(s1,s2);
	}
	cout<<m<<endl;
	for(int i=1;i<=m;i++){
		cout<<q[i].front()<<" "<<q[i].back()<<endl;
	}
	return 0;
}
```

时间复杂度为 $O(n^2)$，对于这道题还是绰绰有余的。

---

## 作者：rainbow_cat (赞：2)

（注：这道题可以使用暴力求解，但在这里我写一个并查集。）
#### 处理： 
```cpp
map<string,int>mp;
```
构建：   
```cpp
if(!mp[x[i]])mp[x[i]]=++idx;
if(!mp[y[i]])mp[y[i]]=++idx;
```

## 主要思路：并查集
怎么并查集？这应该很清晰吧，对于每次输入把名字 $x,y$ 进行合并。最后查看有多少个集合就行了：
```cpp
merge(mp[x[i]],mp[y[i]]);//合并
```
```cpp
for(int i=1;i<=idx;i++)
     if(get(i)==i)ans++;//查找集合数量		
```
接下来，我们只需要从后往前便利每个 $y$，因为最终的名字一定是在最后修改的，然后看他的原名有没有被输出过，如果有就不处理，否则输出他的原名与他现在的名字：
```cpp
if(!pd[find(get(mp[y[i]]))])
{
    cout<<x[find(get(mp[y[i]]))]<<' '<<y[i]<<'\n';
    pd[find(get(mp[y[i]]))]=1;
}
```
### 大坑：
我一直以为只需要输出 `x[get(mp[y[i]])/2+1]` 但是！当你把 `mp[y[i]]` 输出后会发现有些之前出现的名字已经被编号过了：
```
1 2
3 4
4 5
2 6
7 8
```
所以自然不能这么做。    
**由于时间复杂度较为宽松，我们引入了暴力函数用于查找其根节点：**
```cpp
int find(int xx){for(int i=1;i<=n;i++)if(mp[x[i]]==xx)return i;}
```
所以本题就可以直接做了：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int>mp;//map
const int maxn=10010;
int father[maxn],n,m,ans,idx;
string x[maxn],y[maxn];
bool pd[maxn];
void init(){for(int i=1;i<=10000;i++)father[i]=i;}//初始化很重要
int get(int xx)
{
	if(father[xx]==xx)return xx;
	return father[xx]=get(father[xx]);
}//路径压缩的查找
void merge(int x,int y){if(get(x)!=get(y))father[get(y)]=get(x);}//合并
int find(int xx)
{
	for(int i=1;i<=n;i++)if(mp[x[i]]==xx)return i;
}
int main()
{
	ios::sync_with_stdio(0);//节省时间
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	init();
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		if(!mp[x[i]])mp[x[i]]=++idx;
		if(!mp[y[i]])mp[y[i]]=++idx;
		merge(mp[x[i]],mp[y[i]]);//处理map加合并
	}
	for(int i=1;i<=idx;i++)
		if(get(i)==i)ans++;	//父亲为自己的点是根节点
	cout<<ans<<'\n';
	for(int i=n;i>=1;i--)//倒序便利，以你为最后出现的一定是最后修改名字
	{
		if(!pd[find(get(mp[y[i]]))])
		{
			cout<<x[find(get(mp[y[i]]))]<<' '<<y[i]<<'\n';
			pd[find(get(mp[y[i]]))]=1;//标记
		}
	}
	return 0;
}
```

---

## 作者：X2H_tato (赞：2)

## 题目思路：

既然前后改的都是名字，也就是字符串，可以考虑map，map里面也是pair，几乎完全符合题目要求哎；**由于最后只要输出最初的名字和最后的名字，可以考虑以每一次的新名字作为关键字，把旧名字当成键值，之后如果这个人又改了名字，也就是说新名字变成了旧名字，可以直接在map中查找，找到了就把新的新名字作为关键字，此时的键值改成原来那个新名字的键值，也就是之前的旧名字；**
总的来说就是：名字1--->名字2；名字2--->名字3；map[名字2]=名字1，mp[名字3]=mp[名字2]

### 上代码：

```
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
 
using namespace std;
map<string,string>mp;
 
int main(void)
{
    int n;
    string str1,str2;
    scanf("%d",&n);
    while(n--)
    {
        cin>>str1>>str2;
        if(mp.find(str1)==mp.end())
        {
            mp[str2]=str1;
        }
        else
        {
            mp[str2]=mp[str1];
            mp.erase(str1);//记得把之前的给撤销掉
        }
 
    }
    int num=mp.size();
    printf("%d\n",num);
    map<string,string>::iterator it;
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<it->second<<" "<<it->first<<endl;
    }
    return 0;
}

```



---

## 作者：追梦之鲸 (赞：1)

[Link](https://www.luogu.com.cn/problem/CF501B)

这题可以用并查集来做。

#### 思路

可能有些人看着这题不像并查集，没关系，我们把题面换一下试试：

给你一个数 $n$。接下来有 $n$ 行每行有两个字符串（名字）$str1$ 和 $str2$，表示 $str1$ 是 $str2$ 的儿子，问一共有几个家族，然后输出各个家族的最晚的后代和最早的祖先。

是不是有那味了？

然后我们需要维护一个 $fa$ 数组来装父亲和一个 $son$ 数组来装儿子。我们很（bu）明（rong）显（yi）的看出来最早的祖先都没有父亲，最晚的后代都没有儿子（如果看不出来可以自己模拟一下），所以我们可以把所有人都枚举一遍，看看他是否有儿子，如果没有就说明他是最晚的后代，再查询一下他的祖先都存起来就完事了。


#### Code
```c
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define ri register
#define P(a) putchar(a+48)
#define I(a) isdigit(a)
#define G() getchar()
char hc;int ei;
template <class O>
inline void read(ri O &ie){hc=G();ei=1;ie=0;for(;!I(hc);hc=G())if(hc=='-')ei=-1;for(;I(hc);hc=G())ie=ie*10+(hc^48);ie*=ei;return;}
template <class T>
inline void write(ri T iee){ri int tt=1;while(iee>=tt){tt*=10;}tt/=10;while(iee){P(iee/tt);iee%=tt;tt/=10;}return;}
const int MAX=1e+9;
const int N=2e+6+4;
const int MOD=1e+6+3;
unordered_map<string ,string > fa;
unordered_map<string ,string > son;
set<string> c;
string a,b,q[1002],p[1002];
int n,m;
string find(ri string x){
    if(fa[x]=="")return x;
    else return find(fa[x]);//其实这里可以不用路径压缩，因为没个家族只有一个最小的后代
}
signed main(){
    read(n);
    for(ri int i=1;i<=n;i++){
        cin>>a>>b;
        c.insert(a);
        c.insert(b);
        fa[a]=b;
        son[b]=a;
    }
    set<string>::iterator it;
    for(it=c.begin();it!=c.end();it++){
        if(son[*it]==""){
            q[++m]=*it;
            p[m]=find(*it);
        }
    }printf("%d\n",m);
    for(ri int i=1;i<=m;i++)cout<<q[i]<<' '<<p[i]<<'\n';
	return 0;
}
```

---

## 作者：きりと (赞：1)

### 题目大意

见中文翻译。

### 解题思路

给定干员的改名顺序，那么我们先要做的是判断总共有几个干员。我们把每一次修改操作中第一个名字称作 $a$ ，第二个名字称作 $b$ ，那么显然，当输入的 $a$ 之前没出现过，那么这就是一个新的干员。

所以我们可以开一个 $map$ ，来记录每个名字是否出现过。

然后，我们可以再开两个 $map$ 分别用来记 第 $i$ 个干员的初始​名 和 每个初始名所对应的当前名，每次操作更新当前名即可，这步也可以用结构体或链表实现。

然后一个个输出即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,string> q;
map<string,bool> f;
map<string,string> x;
signed main()
{
	int n;
	cin>>n;
	string a,b;
	int cnt=0;
	while(n--)
	{
		cin>>a>>b;
		if(!f[a])
		{
			cnt++;
			q[cnt]=a;
			x[a]=b;			
		}
		else
		{
			for(int i=cnt;i>=1;i--)
			{
				if(x[q[i]]==a)
				{
					x[q[i]]=b;
				}
			}
		}
		f[b]=1;
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		cout<<q[i]<<" "<<x[q[i]]<<endl;
	}
	return 0;
}
```



---

## 作者：AveMarina (赞：1)

## 使用map模拟一个链表
~~我其实不太清除这到底是个什么~~

## 题意解析
看起来和**并查集**一样所以这里就用并查集的思路描述好了。（其实我一开始也是这么想的）给出一个字符串，且这个字符串是 __第一次出现__，将该字符串与若干个字符串合并，最后要我们输出第一次出现的字符串的个数以及所以这种字符串的 __祖宗__。
#### 会不会有任意两个字符串有共同父节点：
答案是不会，因为翻译没给出这个条件...原文片段：handle new is not used and has not been used by anyone.那么考虑到所有字符串都只有一个父节点，我们就可以**把这些个字符串看成是一个链表**，__头节点是干员原名，尾节点是干员现在的名字。__ 
#### 解决方案：
我们只需要判断下 __当前这个字符串是不是第一次出现，如果是第一次出现，将其作为头结点，如果不是第一次出现，将其添加到链表尾部即可__。这里我采用的map模拟链表，效率略低。~~数组模拟好久没用不怎么会了。~~

## 正题
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;
vector<string > vec;
map<string, string > mp;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int n;
	string a, b;
	cin >> n;
	while (n--) {
		cin >> a >> b;	
		// 如果这个字符串还没有子节点，那么这个字符串就肯定是头结点，将其保存起来方便遍历 
		if (mp[a] == "") vec.push_back(a); 
		// 将b添加到节点尾部 
		mp[a] = b;
		// 因为我们的map是字符串到字符串的映射，所以这里标记链表尾也用的字符串 
		mp[b] = "114514";
	}
	string res;
	int vLen = vec.size();
	cout << vLen << endl;
	for (int i = 0; i < vLen; i++) {
		cout << vec[i] << ' ';
		// 遍历当前链表，最后尾部的字符串就是干员现在的名字 
		while (mp[vec[i]] != "114514") res = mp[vec[i]], vec[i] = mp[vec[i]];
		cout << res << endl;
	}
	return 0;
}
```
~~话说这个题为什么没有题解啊，是因为太水了么~~

---

## 作者：wuyixiang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF501B)

题目大意：$n$ 次操作，表示名字为 $old$ 的人更改为 $new$，求更改完后每个人的初始名字与当前名字。

由于题目还需要输出人数，所以我想到了 $\operatorname{map}$，不仅可以直接记录，还可以输出长度以及填入删除等。那么这就好做了：每一次变换，将原来的 $old$ 删除（因为最后不会有这个名字了），$new$ 标记，并记录之前的 $old$ 名字，最后直接迭代器搜索即可。时间复杂度 $O(n^2)$，不用担心，最后直接输出即可。

## AC Code

```cpp
#include <iostream>
#include <map>
using namespace std;
map<string,string>mp;
map<string,int>mp2;//一个存储换过的上一个名字，一个存储是不是现在使用的名字
int main()
{
    int n;
    string s,s2;
    map<string,int>::iterator kk;//迭代器
    cin >> n;
    while(n --)
    {
        cin >> s >> s2;
        mp[s2] = s,mp2[s2] = 1,mp2.erase(s);//删除旧的，标记新的，并记录原来的名字
    }
    cout << mp2.size() << endl;//输出长度
    for(kk = mp2.begin();kk != mp2.end();kk ++)
    {
        string t = kk -> first;
        while(mp[t] != "")t = mp[t];//查找
        cout << t << " " << kk -> first << endl;//输出
    }
} 
```

---

## 作者：_ajthreac_ (赞：0)

让你 $O(n^2)$ 的题就 $O(n^2)$ 做嘛.jpg

容易发现根据题目要求，一个人的信息只有初始名字和当前名字是有用的。我们可以使用 `pair<string, string>` 储存这两个信息，读入一个操作时先找一下有没有当前叫这个名字的，如果有就把他的名字修改成新名字，如果没有就添加这个人。

核心代码如下：
```cpp
vector<pair<string, string> > p;
int n;
int main(){
  ios::sync_with_stdio(false);
  cin>>n;
  while(n--){
    string old, nw; cin>>old>>nw;
    bool ff=0;
    for(auto &i: p){
      if(i.y==old)i.y=nw, ff=1;//找到了，修改当前名字
    }
    if(!ff)p.pub(mkp(old, nw));//找不到，添加这个人
  }
  cout<<p.size()<<endl;
  for(auto i: p)cout<<i.x<<" "<<i.y<<endl;
  return 0;
}
```

---

