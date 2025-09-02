# Facetook Priority Wall

## 题目描述

Facetook 是一个知名的社交网站，它将推出一个名为 Facetook Priority Wall 的新功能。这一功能将根据优先级因子对你朋友的所有帖子进行排序。

优先级因子将受到三种行为的影响：
1. ```"X posted on Y's wall"``` (15 分), 
2. ```"X commented on Y's post"``` (10 分), 
3. ```"X likes Y's post"``` (5 分).

$X$ 和 $Y$ 是两个不同的名字。每一种行为都会使 $X$ 和 $Y$ 之间的优先级因子增加对应分数 ($X$ 和 $Y$ 之间的优先级因子与 $Y$ 和 $X$ 之间的优先级因子相同) 。

给定 $n$ 个上述格式的行为（没有行为序号和行为分数），你要将所有除自己名字以外的名字按照优先级因子打印出来。

## 样例 #1

### 输入

```
ahmed
3
ahmed posted on fatma's wall
fatma commented on ahmed's post
mona likes ahmed's post
```

### 输出

```
fatma
mona
```

## 样例 #2

### 输入

```
aba
1
likes likes posted's post
```

### 输出

```
likes
posted
```

# 题解

## 作者：xyx404 (赞：3)

## 思路：
定义一个 `unordered_set` 用于标记出现过那些人，定义名字为 $se$。

定义一个 `unordered_map` 记录每个人所获得的分数，键为字符串类型，值为整形，定义名字为 $person$。

定义结构体用于存每个人的分数，此结构体排序用。

观察题目所给出的操作的输入格式，发现操作的标志一定是在这一行的第二个字符串，而这一行字符串的数量一定大于三，所以我们可以先输入前三个字符串，然后判断第二个字符串是什么操作。

如果第二个字符串等于 `likes` 那么第三个字符串就是第二个人的名字。

如果第二个字符串为 `posted` 或 `commented` 时，那么第二个人名的位置就在第四个字符串，我们把他输入进来。

在输入找到第二个人的名字后，我们用 `erase` 把第二个人名后面多余的 `'s` 删除，使这个字符串只有人名，然后判断第一个人名和第二个人名中有没有淘淘，因为只有和淘淘互动了，他跟淘淘的因子分数才会增加，然后再判断下这些人名有没有在 `se` 里面出现过，如果没有出现过就把他加入到里面，最后把这些操作里的最后一个字符串输入进来就行了。

我们用创建一个 $it$ 用于历遍 $se$，使他等于 `se.begin()`，之后我们进入循环每次让 `it++` 循环条件为 `it!=se.end()`，在循环过程中我们把每个人的名字以及分数存进结构体。

在循环结束后，我们用 `sort` 进行排序，排序函数为当分数一样时按名字的字典序排序，否则按分数的大小排序。

排序完后，我们输出，当现在输出的这个人的名字不是淘淘的名字时我们就输出。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int n;
unordered_set<string>se;
unordered_map<string,int>person;
struct node{
	string name;
	int soccer;
}ren[110];
bool cmp(node x,node y){ 
	if(x.soccer==y.soccer){// 当分数一样时按名字的字典序排序 
		return x.name<y.name;
	}
	return x.soccer>y.soccer;// 按分数的大小排序
}
int main(){
	string x;cin>>x;
	int n;cin>>n;
	while(n--){
		string a,b,c;
		cin>>a>>b>>c;// 先输入前三个字符串 
		if(b=="likes"){
			c.erase(c.size()-2);string Y=c;// 用 erase 删掉 's
			if(a==x||Y==x){
				if(a!=x){
					person[a]+=5;
				}
				if(Y!=x){
					person[Y]+=5;
				}
			}
			if(!se.count(a))se.insert(a);if(!se.count(Y))se.insert(Y);
			cin>>c;
		}
		else if(b=="commented"){
			cin>>c;c.erase(c.size()-2);string Y=c;// 用 erase 删掉 's
			if(a==x||Y==x){
				if(a!=x){
					person[a]+=10;
				}
				if(Y!=x){
					person[Y]+=10;
				}
			}
			if(!se.count(a))se.insert(a);if(!se.count(Y))se.insert(Y);
			cin>>c;
		}
		else if(b=="posted"){
			cin>>c;c.erase(c.size()-2);string Y=c;// 用 erase 删掉 's
			if(a==x||Y==x){
				if(a!=x){
					person[a]+=15;
				}
				if(Y!=x){
					person[Y]+=15;
				}
			}
			if(!se.count(a))se.insert(a);if(!se.count(Y))se.insert(Y);
			cin>>c;
		}
	}
	auto it=se.begin();
	for(int i=1;it!=se.end();it++,i++){// 存进结构体 
		ren[i].name=*it;
		ren[i].soccer=person[*it];
	}
	sort(ren+1,ren+1+se.size(),cmp);// 排序 
	for(int i=1;i<=se.size();i++){
		if(ren[i].name!=x)cout<<ren[i].name<<"\n";// 输出
	}
	return 0;
}
```

---

## 作者：Mzh2012 (赞：3)

## 题目意思

Facetook 是一个知名的社交网站这个网站有三种操作分别是以下三种。

1.  ```X posted on Y's wall```

1. ```X commented on Y's post```

1. ```X likes Y's post```

如果第一种操作之中有你的参与，那么参与第一种操作的另外一个人加 $15$ 分。

如果第二种操作之中有你的参与，那么参与第二种操作的另外一个人加 $10$ 分。

如果第三种操作之中有你的参与，那么参与第三种操作的另外一个人加 $5$ 分。

## 思路
用一个 ```map```，这个 ```map``` 的键是人名，值是这个人名获得的分数。

对于每次操作，获取参与这个操作的两个人，如果这两个人之中有你，那么看一下这是第几种操作，并让这个操作的另外一个人加上对应的分数即可。

最后用一个结构体数组存 ```map``` 的键和值，最后排序输出就行。


```cpp
#include<bits/stdc++.h>

using namespace std;

map<string,int> m;
struct djfak{
	string name;
	int fen;
}arr[1000005];

bool cmp(djfak a,djfak b){//排序函数 
	if(a.fen==b.fen) return a.name<b.name;//如果分数相同按照名字的字典序排序。
	return a.fen>b.fen;
}

int main(){
	string taotao;//你的名字
	cin>>taotao;
	int n;
	cin>>n;
	while(n--){
		string a,b,c,d,e,f;
		cin>>a>>b;
		if(b=="likes"){
			cin>>d>>e;
		}else{
			cin>>f>>d>>e;
		}
		//a第一个人名   b互动的类型    d第二个人名 
		d.erase(d.size()-1);//删除最后两个字母 
		d.erase(d.size()-1);//应为's是多余的 
		if(a==taotao){//如果第一个人是你
			if(b=="posted") m[d]+=15;
			else if(b=="likes") m[d]+=5;
			else m[d]+=10;
		}else if(d==taotao){//如果第二个人是你
			if(b=="posted") m[a]+=15;
			else if(b=="likes") m[a]+=5;
			else m[a]+=10;
		}else{m[a]+=0,m[d]+=0;}
	}
	int k = 0;
	for(auto i:m) arr[k].name = i.first,arr[k].fen = i.second,k++;
	sort(arr,arr+k,cmp);//按题目意思排个序 
	for(int i = 0;i<k;i++){
		cout<<arr[i].name<<endl;//输出 
	}

	return 0;
}

```

---

## 作者：Jerrlee✅ (赞：1)

~~正好上课讲到这一题了，顺一篇题解~~
## 题意
有个网站叫 Facetook，如果你在某人的 wall 上面发帖（~~话说这啥意思？~~），你和那个人就会得到 $15$ 分。

如果在某人的帖子下评论，两人加 $10$ 分。

点赞各加 $5$ 分。

以下面的形式输入给你：

- `X posted on Y's wall.`

- `X commented on Y's post.`

- `X likes Y's post.`

**和你有关系的操作对于你加分**。

将输入中出现的人按**对于你的加分**排序，同分按字典序排序。
## 思路
注意一点：为了简洁，我们认为**和你没关系的不加分！**

但也记得标记为 $0$ 分，最后不会漏输出他。

------------

用 $\texttt{map}$ 存分数和名字（便于字典序排序），$\texttt{cmp}$ 手写。加几分特判即可。
## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
int n;
map<string,int> pnts;
vector<pair<string,int> >v;
bool cmp(const pair<string,int>&a,const pair<string,int>&b){
    if(a.second!=b.second) return a.second>b.second;
    return a.first<b.first;
}
int main(){
    string st,s,a,b,o;
    cin>>st>>n;
    while(n--){
        cin>>a>>o;
        if(o!="likes") cin>>s;
        cin>>b;
        b.erase(b.length()-2); //把 's 过滤掉
        cin>>s;
        if(a!=st&&pnts.find(a)==pnts.end()) pnts[a]=0;
        if(b!=st&&pnts.find(b)==pnts.end()) pnts[b]=0; //这个人出现了就要输出，记得标记！
        if(b==st) swap(a,b); //a 评论/发帖/点赞 b 和 b 评论/发帖/点赞 a 加分一样，不妨换过来便于加分
        if(a==st)
            if(o=="posted") pnts[b]+=15;
            else if(o=="commented") pnts[b]+=10;
            else if(o=="likes") pnts[b]+=5;
    }
    for(map<string,int>::iterator it=pnts.begin();it!=pnts.end();it++) v.push_back(make_pair(it->first,it->second));
    sort(v.begin(),v.end(),cmp);
    for(int i=0;i<v.size();i++) cout<<v[i].first<<endl;
}
```
[AC记录](https://www.luogu.com.cn/record/61942084)

---

## 作者：小杨小小杨 (赞：1)

## 题意
给你你自己的名字，和 $n$ 句话，每一句话中的两个名字中，如果有一个是自己的名字，那么，两个人都按以下方式加分：   
如果是 X posted on Y's wall. 形式的，那么两者各加15分。   
如果是 X commented on Y's post. 形式的，那么两者各加10分。      
如果是 X likes Y's post. 形式的，那么两者各加5分。   
问你：以上出现的名字中，除了自己外，把其他人按分数从大到小排序，若分数一致，那么就按名字字典序从小到大排序。
## 思路
暴力啊。听说好多大佬都用了 map 去做，但本蒟蒻实在太蒻了，不会啊，只好用一种奇奇怪怪的方式来代替 map 了。  
首先读入都会叭，一行行读入就行了。然后暴力枚举出两个名字，判断是否有任何一个名字是自己的名字，如果有，那么就按上面的情况去增加分数。本蒟蒻是这么累加的：首先，开一个结构体数组，把当前的两个名字全都保存在结构体数组的一个变量里，把应该加的分数保存在另一个变量里。如果两个名字中没有一个是自己的名字，就加上零分。全部做完后，把整一个结构体数组按名字字典序排序，那么所有相同名字的加分项就在一起了。最后用另一个结构体数组保存，若这个名字和上一个不一样了，那么就是下一个人了，不然就在上一个人的分数中加上这个分数。最后在双关键排序，输出。  
~~多简单一道题啊，我调了三天~~
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string myname,doit,name1,name2;
int i,top,tot,k,kk,m,n,j,mm;
struct Node{//结构体
	string names;
	int x;
}f[501],h[101];//f一定要开200以上
bool cmp(Node x,Node y){return x.names<y.names;}//第一次排序排名字
bool cmp1(Node x,Node y){return x.x>y.x||x.x==y.x&&x.names<y.names;}//双关键排序
int main(){
	cin>>myname;
	scanf("%d",&mm);getchar();
	for (i=1;i<=mm;i++){
		getline(cin,doit);n=doit.length();//一行行读入
		name1="";//清空
		for (j=0;j<=n;j++)
			if (doit[j]==' ') break;
			else name1+=doit[j];//取出第一个名字
		j++;k=j;
		for (j=j;j<=n;j++) 
			if (doit[j]==' ') break;
		kk=j-1;m=kk-k+1;
		if (doit.substr(k,m)=="posted"){//判断句型
			name2="";
			for (j=kk+2;j<=n;j++)
				if (doit[j]==' ') break;//前面还有一个单词
			for (j=j+1;j<=n;j++)
				if (doit[j]=='\'') break;
				else name2+=doit[j];//取出第二个名字（'\''是'的意思）
			f[++top].names=name1;//保存第一个名字
			f[++top].names=name2;//保存第二个名字
			if (name2!=myname&&name1!=myname) continue;//是否有自己的名字
			f[top-1].x=15;//第一个名字的应加分数（一定要减一！）
			f[top].x=15;//第二个名字的应加分数
		}
		else if (doit.substr(k,m)=="commented"){
			name2="";
			for (j=kk+2;j<=n;j++)
				if (doit[j]==' ') break;//前面还有一个单词
			for (j=j+1;j<=n;j++)
				if (doit[j]=='\'') break;//取出第二个名字
				else name2+=doit[j];
			f[++top].names=name1;//保存第一个名字
			f[++top].names=name2;//保存第二个名字
			if (name2!=myname&&name1!=myname) continue;//是否有自己的名字
			f[top-1].x=10;//第一个名字的应加分数
			f[top].x=10;//第二个名字的应加分数
		}
		else if (doit.substr(k,m)=="likes"){
			name2="";
			for (j=kk+2;j<=n;j++)
				if (doit[j]=='\'') break;//取出第二个名字
				else name2+=doit[j];
			f[++top].names=name1;//保存第一个名字
			f[++top].names=name2;//保存第二个名字
			if (name2!=myname&&name1!=myname) continue;//是否有自己的名字
			f[top-1].x=5;//第一个名字的应加分数
			f[top].x=5;//第二个名字的应加分数
		}
	}
	sort(f+1,f+top+1,cmp);//第一次排序，排名字
	tot=1;
	h[1].names=f[1].names;h[1].x=f[1].x;//预处理第一个
	for (i=2;i<=top;i++)
		if (f[i].names!=f[i-1].names) 
        h[++tot].names=f[i].names,h[tot].x=f[i].x;
		else h[tot].x+=f[i].x;//判断并累加
	sort(h+1,h+tot+1,cmp1);//第二次排序，双关键
	for (i=1;i<=tot;i++)
		if (h[i].names!=myname)//不是自己
			cout<<h[i].names<<endl;//输出
	return 0;
}

```


---

## 作者：Jayfeather2012 (赞：0)

## 思路
定义一个 map 标记出现的朋友和他对印的优先级因子。  
对于每次输入，若 $X$ 或 $Y$ 是我，那么就根据题意，增加我和另一个人的优先级因子，若不是，就把 $X$ 或 $Y$ 插入 map 中，利用 map 会去重的特性，就可以统计出我的所有朋友和我的优先级因子。  
最后，将朋友和朋友对应的优先级因子搬入结构体，根据优先级因子的大小和朋友名字的字典序进行排序后输出。  
具体细节看代码吧~~
## 代码

```
#include <bits/stdc++.h>
using namespace std;
map < string,int > mp;//定义map 
string x,y,s,t,w;
int n,m;
struct Node{
    string name;
    int p;
}a[1000005];
bool cmp(Node x,Node y){//排序函数 
    if(x.p!=y.p)return x.p>y.p;//先按优先级因子大小排 
    return x.name<y.name;//优先级因子大小相同，按名字字典序排 
}
int point(string s){//根据题意计算优先级因子的增加值 
    if(s=="likes")return 5;
    if(s=="commented")return 10;
    return 15;
}
int main() {
    cin>>s>>n;
    while(n--){
        cin>>x>>t;//X和动词 
        if(t!="likes")cin>>w;//若非likes输入on
        cin>>y>>w;//Y和post
        y.erase(y.size()-2);//删's 
        if(x==s)mp[y]+=point(t);
        else if(y==s)mp[x]+=point(t);
        //是和我交流，增加优先级因子 
        else {
        	mp.insert({x,0});
        	mp.insert({y,0});
		}
		//不是和我交流，插入名字
    }
    for(auto g:mp){
    	a[++m].name=g.first;
    	a[m].p=g.second;//搬入结构体 
    }
    sort(a+1,a+m+1,cmp);//排序 
    for(int i=1;i<=m;++i)cout<<a[i].name<<"\n";//输出 
	return 0;
}
```

---

## 作者：PDAST (赞：0)

## 题意
有一个社交网站，叫 facetook，上面可以进行三种操作：
+ 在某人的墙上发帖；
+ 评论某人的帖子；
+ 点赞某人的帖子。

当你进行了以上操作后，你与被操作人的亲密度分别会增加一定数值，发帖为 $15$ 点，评论为 $10$ 点，点赞为 $5$ 点，求 $N$ 次操作后所有人与你的亲热度排名。
## 思路
纯粹的模拟题，每次只要输入一行，分成几段，去掉人名后的 `'s `，把与“我”有关联的操作加入统计，最后进行排序，输出答案即可。
## 代码
老师要求要在四十行内，请原谅。
~~~cpp
#include<bits/stdc++.h>
using namespace std;
string myname,nameset[1001],s;
map<string,bool>name;
map<string,int>mp;
int n,k;
bool cmp(string a,string b) {
	if(mp[a]==mp[b])return a<b;
	return mp[a]>mp[b];
}
void doit(int pls,string st[]){
	st[4]=st[4].substr(0,st[4].size()-2);
	if(st[4]==myname)swap(st[1],st[4]);
	if(!name[st[1]])name[st[1]]=1,nameset[++k]=st[1];
	if(!name[st[4]])name[st[4]]=1,nameset[++k]=st[4];
	if(st[1]==myname)mp[st[4]]+=pls;
}
int main() {
	cin>>myname>>n,getchar();
	name[myname]=1;
	for(int i=1; i<=n; i++) {
		getline(cin,s);
		int t[11]= {-1,0,0,0,0,0,0,0,0,0,0},cnt=0;
		string st[6];
		s+=" ";
		for(int j=0; j<s.size(); j++)if(s[j]==' ')t[++cnt]=j;
		for(int j=1; j<=cnt; j++)st[j]=s.substr(t[j-1]+1,t[j]-t[j-1]-1);
		if(st[2]=="posted")doit(15,st);
		else if(st[2]=="commented")doit(10,st);	
		else if(st[2]=="likes") {
			st[3]=st[3].substr(0,st[3].size()-2);
			if(st[3]==myname)swap(st[1],st[3]);
			if(!name[st[1]])name[st[1]]=1,nameset[++k]=st[1];
			if(!name[st[3]])name[st[3]]=1,nameset[++k]=st[3];
			if(st[1]==myname)mp[st[3]]+=5;
		}
	}
	sort(nameset+1,nameset+k+1,cmp);
	for(int i=1; i<=k; i++)cout<<nameset[i]<<"\n";
}
~~~

---

## 作者：Peaky (赞：0)

按照惯例应该现有[传送门](https://www.luogu.com.cn/problem/CF75B)。

提议大概是先记录每个人的名字和以及和“我”的亲密度，一开始要注意把每个人和“我”的亲密度都归零，然后判断每个人的行为，按照行为加上亲密度，最后将按亲密度高低和字典序进行排序。

然后就是按照惯例附上蒟蒻的代码：
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
map<string,int> mp,turn;
struct Node{
	string name;
	int k;
}node[N];
bool cmp(Node x,Node y){
	if(x.k==y.k) return x.name<y.name;
	return x.k>y.k;
}
int main(){
	turn["posted"]=15;
	turn["commented"]=10;
	turn["likes"]=5;
	string name;
	int k,top=0;
	cin>>name>>k;
	while(k--){
		string name1,op,name2,q;
		cin>>name1>>op;
		if(op!="likes"){
			string tot;
			cin>>tot;
		}
		cin>>name2>>q;
		name2=name2.substr(0,name2.size()-2);
		if(name1==name||name2==name){
			mp[name1]+=turn[op];
			mp[name2]+=turn[op];
		}
		mp[name1]+=0,mp[name2]+=0;
	}
	for(auto m:mp) node[++top]={m.x,m.y};
	sort(node+1,node+top+1,cmp);
	for(int i=1;i<=top;i++){
		if(node[i].name==name) continue;
		cout<<node[i].name<<endl;
	}
	return 0;
}
```


---

## 作者：Walrus (赞：0)

# [CF75B](https://codeforces.com/problemset/problem/75/B)
CF 上评分才 $1500$，一道普通字符串模拟。这里给一个看起来比较蒻但是比较清晰的方法。

## 题意
先给你一个**自己**的名字，接着会有一些信息。

简单概括一下操作。

一共分为 $3$ 种：

- `"X posted on Y's wall"`。
- `"X commented on Y's post"`。
- `"X likes Y's post"`。

相信读过题的人都知道**优先级因子**是个啥。

有个关键点，题目是要求**与自己的优先级因子从大到小的顺序**，所以出现两种情况。

- 上述信息与自己有关联，则将自己和对方的优先级因子加上对应值。
- 上述信息与自己没关联，不做任何加值操作，但要记录**出现的人名**。

我这里给出一个不用加 `getchar` 的方法。

我们直接观察操作，识别到通过**第二段字符串**能明确是哪种操作，所以直接把人名留下，把其它的直接过滤即可。当然，优先级因子的值肯定要用 `map` 记录。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

map<string, int> mp;
map<string, int>::iterator it;

int n;

string name, a, b, op, gc;

struct Name {
	string name;
	int pts;
	bool operator < (const Name &a) const {return pts == a.pts ? name < a.name : pts > a.pts;}//排序规则
} s[105];

signed main() {
	cin >> name;
	cin >> n;
	while(n--) {
		a = "", b = "";
		cin >> a >> op;
		if(op == "posted") {
			cin >> gc, cin >> gc;
			for(int i = 0;i < gc.size() - 2;i++)
				b += gc[i];//人名后面的所有格也不要。（这里的所有格指的是英语中的东西。）
			if(a == name || b == name) {
				if(a == name)
					mp[b] += 15;
				else
					mp[a] += 15;
			}
			else
				mp[a] += 0, mp[b] += 0;
			cin >> gc;//没用的东西直接过滤，下面同理。
		}
		else if(op == "commented") {
			cin >> gc, cin >> gc;
			for(int i = 0;i < gc.size() - 2;i++)
				b += gc[i];
			if(a == name || b == name) {
				if(a == name)
					mp[b] += 10;
				else
					mp[a] += 10;
			}
			else
				mp[a] += 0, mp[b] += 0;
			cin >> gc;
		}
		else {
			cin >> gc;
			for(int i = 0;i < gc.size() - 2;i++)
				b += gc[i];
			if(a == name || b == name) {
				if(a == name)
					mp[b] += 5;
				else
					mp[a] += 5;
			}
			else
				mp[a] += 0, mp[b] += 0;
			cin >> gc;
		}
	}
	
	int t = 0;
	
	for(it = mp.begin(); it != mp.end(); it++) {
		s[++t].name = (*it).first, s[t].pts = (*it).second;
	}//map 两个关键字用结构体再存一遍，便于排序。
	
	
	sort(s + 1, s + 1 + t);
	
	for(int i = 1;i <= t;i++)
		cout << s[i].name << '\n';
}
```





---

## 作者：YFF1 (赞：0)

# 思路分析：
先记录每个人的名字和以及和“我”的亲密度，一开始要注意把每个人和“我”的亲密度都归零，然后判断每个人的行为，按照行为加上亲密度，最后将按亲密度高低和字典序进行排序。
# 代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,t=0;
string myname,s,s2,s3,s4,c;
struct node{
	string name;
	int score;
}a[20005];
map<string,int>mp;
bool cmp(node a,node b){
	if(a.score==b.score)return a.name<b.name;
	return a.score>b.score;
}
int main () {
	cin>>myname;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s>>s2;
		if(s2=="likes")cin>>s3>>s4;
		else cin>>c>>s3>>s4;
		s3.erase(s3.size()-1);
		s3.erase(s3.size()-1);
		if(s==myname){
			if(s2=="posted")mp[s3]+=15;
			else if(s2=="likes")mp[s3]+=5;
			else mp[s3]+=10;	
		}
		else if(s3==myname){
			if(s2=="posted")mp[s]+=15;
			else if(s2=="likes")mp[s]+=5;
			else mp[s]+=10;
		}
		else {
			mp[s]+=0;
			mp[s3]+=0;
		}
	}	
	for(auto i:mp){
		t++;
		a[t].name=i.first;
		a[t].score=i.second;
	}
	sort(a+1,a+1+t,cmp);
	for(int i=1;i<=t;i++)cout<<a[i].name<<endl;
	return 0;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Facetook Priority Wall](https://www.luogu.com.cn/problem/CF75B)
## 思路分析
用 `map` 记录下当前出现的名字是否出现过，若出现过，是第几个。再用结构体记录第 $i$ 个名字的优先级因子的分数和它的名字。最后按照分数为第一关键字排序，名字为第二关键字排序即可。

PS：代码有注释。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=201;
string s,ss;
map<string,int>mp;
int n,cnt=1;
struct node{int x;string s;}a[N];
bool cmp(node a,node b){return a.x!=b.x?a.x>b.x:a.s<b.s;}
int main(){
//	freopen("1.txt","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>s>>n;mp[s]=1;
	a[1]={0,s};getline(cin,ss);
	for(R i=1; i<=n; i++){
		getline(cin,ss);
		string nam1="",nam2="";
		int x=0;//当前回合可获得的分数
		R j=0;
		while(ss[j]!=' ')nam1+=ss[j++];//记录第一个人的名字
		if(ss[j]==' ')j++;
		if(ss[j]=='p')x=15,j+=10;
		else if(ss[j]=='c')x=10,j+=13;
		else x=5,j+=6;
		while(ss[j]!=' ')nam2+=ss[j++];//记录第二个人的名字
		nam2.erase(nam2.size()-2,2);//由于记录下了形如 Y's 的字符串，所以要删除最后两位，使其变为第二个人的名字
		if(!mp[nam1])a[++cnt]={0,nam1},mp[nam1]=cnt;
		if(!mp[nam2])a[++cnt]={0,nam2},mp[nam2]=cnt;
//		cout<<nam1<<' '<<nam2<<'\n';
		if(nam1==s||nam2==s)
			a[mp[nam1]].x+=x,a[mp[nam2]].x+=x;//加分
	}
//	cout<<cnt<<'\n';
	sort(a+2,a+cnt+1,cmp);
	for(R i=2; i<=cnt; i++)
		cout<<a[i].s<<'\n';
	return 0;
}

```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF75B)

一道模拟题。

用一个 `map` 存储每个人的优先级因子，然后存进 `vector` 里进行排序。难点在于分辨 $X$ 和 $Y$ 与当前是什么操作。

不过需要注意，只要出现了名字就需要输出，且我们认为与你没关系的人不加分。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
string name;
int n, cnt;
map <string, int> mp;
vector <pair <string, int>> ans; 
bool cmp(const pair <string, int> &x, const pair <string, int> &y) { // 排序
    if (x.second != y.second) return x.second > y.second;
    return x.first < y.first; 
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> name >> n;
    cin.get(); // 接下来要 getline
    for (int i = 1; i <= n; i++) {
        int j;
        string s, x, y, op;
        getline(cin, s);
        for (j = s.size() - 8; s[j] != ' '; j--) y += s[j]; 
        reverse(y.begin(), y.end()); // 判断 Y
        for (j = 0; s[j] != ' '; j++) x += s[j]; // 判断 X
        for (j++; s[j] != ' '; j++) op += s[j]; // 判断是什么操作
        if (x != name and mp.find(x) == mp.end()) mp[x] = 0; 
        if (y != name and mp.find(y) == mp.end()) mp[y] = 0;
        // 只要出现了就要输出
        if (y == name) {
            if (op == "posted") mp[x] += 15;
            else if (op == "commented") mp[x] += 10;
            else mp[x] += 5;
        }
        if (x == name) {
            if (op == "posted") mp[y] += 15;
            else if (op == "commented") mp[y] += 10;
            else mp[y] += 5;
        }
    }
    for (auto v : mp) ans.push_back(make_pair(v.first, v.second));
    sort(ans.begin(), ans.end(), cmp);
    for (auto v : ans) cout << v.first  << "\n";
    return 0;
}
```


---

## 作者：HMZHMZHMZ (赞：0)

## 题意
给定你一个名字和 $ n $ 句话。每句话中含有两个人的名字以及某一种操作，操作方法如下。
1. 形如 ` X posted on Y's wall ` 的操作，将 $ x , y $ 之间的优先因子加 $ 15 $ 分。
2. 形如 ` X commented on Y's post ` 的操作，将 $ x , y $ 之间的优先因子加 $ 10 $ 分。
3. 形如 ` X likes Y's post ` 的操作，将 $ x , y $ 之间的优先因子加 $ 5 $ 分。

输出 $ m $ 行（ $ m $ 是 $ n $ 句话中出现的名字的个数）。每一行包含一个名字。以分数为第一关键字，字典序为第二关键字排序。

## 思路
首先我们发现，当操作中两个名字都不是你时，这个操作显然无效，所以只用考虑与你有关的操作。我们可以开一个 ` map ` ，来存一个名字是否出现。再开一个 ` map ` ，来存每个人的优先因子分数即可，细节不多。

## 代码

``` cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,cnt;
map<string,bool> mp;//存名字是否出现
map<string,int> pts;//存优先因子分数
string me,nam[N],id1,typ,ul,id2,s;//nam存所有的名字
inline int read(){
    int s=0,f=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') f|=ch=='-',ch=getchar();
    while(ch<='9'&&ch>='0'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return f?-s:s;
}
inline int llread(){
    ll s=0,f=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') f|=ch=='-',ch=getchar();
    while(ch<='9'&&ch>='0'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return f?-s:s;
}
inline bool cmp(string a,string b){//按照题目要求排序，分数为第一关键字，字典序为第二关键字排序
    if(pts[a]==pts[b]) return a<b;
    else return pts[a]>pts[b];
}
int main(){
    cin>>me>>n;
    while(n--){
        cin>>id1>>typ;
        if(typ!="likes") cin>>ul;//如果读入的typ不为like，那么后面有一个没有用的 on，要读入掉
        cin>>s>>ul;//最后面还有一个wall或者post，也没有用处，用ul读入掉
        id2="";
        for(register int i=0;i<s.size();++i){//找到第二个人的名字
            if(s[i]>'z'||s[i]<'a') break;
            id2+=s[i];
        }
        if(!mp[id1]) nam[++cnt]=id1,mp[id1]=1;
        if(!mp[id2]) nam[++cnt]=id2,mp[id2]=1;
        if(id1!=me&&id2!=me) continue;//判断与我有没有关系
        if(typ=="posted") pts[id2]+=15,pts[id1]+=15;//加分
        if(typ=="commented") pts[id2]+=10,pts[id1]+=10;
        if(typ=="likes") pts[id2]+=5,pts[id1]+=5;
    }
    sort(nam+1,nam+cnt+1,cmp);//排序
    for(register int i=1;i<=cnt;++i) if(me!=nam[i]) cout<<nam[i]<<endl;
    return 0;
}
```


---

## 作者：Jerrywang09 (赞：0)

# 先说几句

有点讨厌的模拟。难度应该是 普及-。

# 解题思路

先输入自己的名字。在输入数量。

**注意：因为下面要使用 getline，所以，输入完数量 $n$ 后要 `cin.get()`。**

之后，用 getline 输入 $n$ 个字符串。

对于每个字符串，用 vector 动态数组 $a$ 存储每个分离出来的单词。
也可以用 istringstream。

我们知道，$a_1$ 是执行的操作。建立 map 以确定人与分数的关系。

## 1.posted

$a_3$ 里的名字有所有格，要把最后两位 `'s` 去掉。

如果 $a_0$ 是我，或者 $a_3$ 是我，就相对应地计分。

## 2.commented

和上面情况的处理方法一样。

## 3.likes

需要注意，
like，第二个人名应该是 $a_2$。其余的处理方法不变。

## 4.排序

排序需要自己写一个自定义排序函数。如果分数相同，比较姓名字典序。否则比较分数大小。

## 5.有点小问题

如果运行目前的程序，一定输入样例 $2$ 后，没有输出。

怎么回事？因为那两个人一分不得。

所以，我们需要“装模做样”地调用一下两个人名所对应的键值，这样 map 里就会增加人数。详见代码中注释打感叹号的部分。

这么修改过后，需要注意，不要输出自己的信息。

# 奉上代码

千万不要抄，小心棕名！

```cpp
// 75B Facetook Priority Wall
#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b)
{
	if(a.second==b.second)
		return a.first<b.first;
	return a.second>b.second;
}

int main()
{
	string me; cin>>me;
	int n; cin>>n; cin.get();
	map<string, int> m;
	for(int k=0; k<n; k++)
	{
		string s; getline(cin, s);
		s+=' ';
		vector<string> a;
		string cur;
		for(int i=0; i<s.size(); i++)
		{
			if(s[i]!=' ')
				cur+=s[i];
			else
			{
				a.push_back(cur);
				cur.clear();
			}
		}
		
		string o=a[1];
		if(o=="posted")
		{
			a[3].pop_back();
			a[3].pop_back();
			m[a[0]]; m[a[3]];
			if(a[0]==me)
				m[a[3]]+=15;
			if(a[3]==me)
				m[a[0]]+=15;
		}
		else if(o=="commented")
		{
			a[3].pop_back();
			a[3].pop_back();
			m[a[0]]; m[a[3]];
			if(a[0]==me)
				m[a[3]]+=10;
			if(a[3]==me)
				m[a[0]]+=10;
		}
		else
		{
			a[2].pop_back();
			a[2].pop_back();
			m[a[0]]; m[a[2]];
			if(a[0]==me)
				m[a[2]]+=5;
			if(a[2]==me)
				m[a[0]]+=5;
		}
	}
	
	pair<string, int> p[m.size()]; int k=0;
	for(auto x:m)
		if(x.first!=me)
			p[k++]=x;
		
	sort(p, p+k, cmp);
	
	for(auto x:p)
		cout<<x.first<<endl;
	
	return 0;
}
```

---

