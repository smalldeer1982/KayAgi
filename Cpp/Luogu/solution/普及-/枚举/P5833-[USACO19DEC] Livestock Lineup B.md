# [USACO19DEC] Livestock Lineup B

## 题目描述

每天，Farmer John 都要给他的 $8$ 头奶牛挤奶。她们的名字分别是 Bessie，Buttercup，Belinda，Beatrice，Bella，Blue，Betsy，和 Sue。

不幸的是，这些奶牛相当难以伺候，她们要求 Farmer John 以一种符合 $N$ 条限制的顺序给她们挤奶。每条限制的形式为“$X$ 必须紧邻着 $Y$ 挤奶”，要求奶牛 $X$ 在挤奶顺序中必须紧接在奶牛 $Y$ 之后，或者紧接在奶牛 $Y$ 之前。

请帮助 Farmer John 求出一种满足所有限制的奶牛挤奶顺序。保证这样的顺序是存在的。如果有多种顺序都满足要求，请输出字典序最小的一种。也就是说，第一头奶牛需要是所有可能排在任意合法奶牛顺序的第一位的奶牛中名字字典序最小的。在所有合法的以这头字典序最小的奶牛为首的奶牛顺序中，第二头奶牛需要是字典序最小的，以此类推。

## 说明/提示

$1 \leq N \leq 7$。

供题：Brian Dean

## 样例 #1

### 输入

```
3
Buttercup must be milked beside Bella
Blue must be milked beside Bella
Sue must be milked beside Beatrice```

### 输出

```
Beatrice
Sue
Belinda
Bessie
Betsy
Blue
Bella
Buttercup```

# 题解

## 作者：Yellow_Lemon_Tree (赞：13)

先输入，然后字典序排序，由于n<=7，就把所有可能全排一遍，然后判断是否符合规则，符合输出，不符合继续，我用了STL。

不多说，上题解！
```cpp
#include<bits/stdc++.h>
using namespace std;
vector <string> cows,st_a,st_b; 
int n;
int find(string c)
{
	for(int i=0;i<8;i++)
	{
		if(cows[i]==c) return i;
	}
	return -1;
}
bool sati()
{
	for(int i=0;i<n;i++)
	{
		if(abs(find(st_a[i])-find(st_b[i]))!=1) return false;
	}
	return true;
}
int main()
{
	cows.push_back("Beatrice");
	cows.push_back("Belinda");
	cows.push_back("Bella");
	cows.push_back("Bessie");
	cows.push_back("Betsy");
	cows.push_back("Blue");
	cows.push_back("Buttercup");
	cows.push_back("Sue");
    cin>>n;
    string a,b,t;
    for(int i=0;i<n;i++)
    {
    	cin>>a;
    	cin>>t;
    	cin>>t;
    	cin>>t;
    	cin>>t;
    	cin>>b;
    	st_a.push_back(a);
    	st_b.push_back(b);
	}
	do{
		if(sati()){
			for(int i=0;i<8;i++) cout<<cows[i]<<endl;
			break;
		}
	}
	while(next_permutation(cows.begin(),cows.end()));
return 0;
}

```
希望能过！

记得点个赞！

---

## 作者：Skyjoy (赞：8)

开始水第一篇题解！

这道题我用一种没有思维难度的解法：用$next$$_$$permutation$函数模拟字典序从小到大的情况，然后用$map$存放序号，判断顺序是否符合要求就可以了！

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[10]={"Beatrice","Belinda","Bella","Bessie","Betsy","Blue","Buttercup","Sue"},sen[10][10];
int n,cnt,flag;
map<string,int>m;
int main(){
	for(int i=0;i<8;i++){
		m[s[i]]=i;
	}
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<6;j++){
			cin>>sen[i][j];
		}
	}
	while(cnt<=43200){
		flag=0;
		cnt++;
		for(int i=0;i<n;i++){
			if(abs(m[sen[i][0]]-m[sen[i][5]])!=1){
				flag=1;
				break;
			}
		}
		if(!flag){
			break;
		}
		next_permutation(s,s+8);
		for(int i=0;i<8;i++){
			m[s[i]]=i;
		}
	}
	for(int i=0;i<8;i++){
		cout<<s[i]<<endl;
	}
	return 0;
} 
```
# 多练题，少颓废，就能有进步（别想歪）！

---

## 作者：虐题者 (赞：5)

这道题开始的思路就是全排列，由于只有8头牛，所以不会超时。

先展示一个全排列模板：

```cpp
#include<iostream>
using namespace std;
int n,a[1000];
bool used[1000];
void dfs(int x) {
	if(x==n+1) {
		for(int i=1; i<=n; i++) cout<<a[i]<<" ";
		cout<<endl;
		return;
	}
	for(int i=1; i<=n; i++)
		if(!used[i]) {
			a[x]=i;
			used[i]=true;
			dfs(x+1);
			used[i]=false;
		}
}
int main() {
	cin>>n;
	dfs(1);
	return 0;
}

```


------------

相信大家都会这个模板，然后，因为n只能是8，所以把n设为常量：
```cpp
const int n=8;
```


------------
将八头牛的名字肉眼字典序排列，写到一个常量数组内。



------------

m代表m条限制的顺序，输入m后，定义两个string数组s1和s2，表示"X must be milked beside Y"中的X和Y：
```cpp
string s1[20],s2[20];

.....
for(int i=1;i<=m;i++) {
	string s;
	cin>>s1[i];
	cin>>s>>s>>s>>s; //四个单词不要
	cin>>s2[i];
}
```


------------

之后，将全排列的终止条件花括号内，进行改动。

定义一个string数组代表牛的全排列，将牛的全排列带入条件，判断条件成不成立，如果成立，直接输出(字典序一定最小):

```cpp
if(x==n+1) {
	int yyy=1;
	for(int i=1;i<=n;i++) {
		sss[i]=ss[a[i]];
	} 
	for(int i=1;i<=m;i++) {
		int i1=0,i2=0;
		for(int j=1;j<=n;j++) {
			if(sss[j]==s1[i]) i1=j;
			if(sss[j]==s2[i]) i2=j;
			if(i1&&i2) break;
		}
		if(abs(i1-i2)!=1) {
			yyy=0;
			break;
		}
	}
	if(ffss&&yyy) {
		for(int i=1;i<=n;i++) cout<<sss[i]<<endl;
	}
	if(ffss&&yyy) ffss=0;
	return;
}
```
完整代码:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
using namespace std;

int m,a[20],ffss=1;
const int n=8;
long long tot;
bool used[20];
string s1[20],s2[20];
string sss[20];
string ss[20]={" ","Beatrice","Belinda","Bella","Bessie","Betsy","Blue","Buttercup","Sue"};

void dfs(int x) {
	if(x==n+1) {
		int yyy=1;
		for(int i=1;i<=n;i++) {
			sss[i]=ss[a[i]];
		} 
		for(int i=1;i<=m;i++) {
			int i1=0,i2=0;
			for(int j=1;j<=n;j++) {
				if(sss[j]==s1[i]) i1=j;
				if(sss[j]==s2[i]) i2=j;
				if(i1&&i2) break;
			}
			if(abs(i1-i2)!=1) {
				yyy=0;
				break;
			}
		}
		if(ffss&&yyy) {
			for(int i=1;i<=n;i++) cout<<sss[i]<<endl;
		}
		if(ffss&&yyy) ffss=0;
		return;
	}
	for(int i=1;i<=n;i++) {
		if(!used[i]) {
			a[x]=i;
			used[i]=true;
			dfs(x+1);
			used[i]=false;
		}
	}
}

int main() {
	//freopen("lineup.in","r",stdin);
	//freopen("lineup.out","w",stdout);
   //在USACO中千万不要忘了文件读写
	scanf("%d",&m);
	for(int i=1;i<=m;i++) {
		string s;
		cin>>s1[i];
		cin>>s>>s>>s>>s;
		cin>>s2[i];
	} dfs(1);
	return 0;
}

```


---

## 作者：chenningxuan (赞：3)

就是一道全排列的水题，我用了STL里的next_permutation，也可以手写递归（就是因为懒）
```
#include<bits/stdc++.h>
using namespace std;

vector<string> cows,beside_a,beside_b;
int N;

int where(string c)
{
	for(int i=0;i<8;i++) 
		if(cows[i]==c) return i;
	return -1;
}

bool satisfies_constraints(void) 
{
	for(int i=0;i<N;i++)
		if(abs(where(beside_a[i])-where(beside_b[i]))!=1) return false;
	return true;
}

int main(void)
{
	cin>>N;
	cows.push_back("Beatrice");
	cows.push_back("Belinda");
	cows.push_back("Bella");
	cows.push_back("Bessie");
	cows.push_back("Betsy");
	cows.push_back("Blue");
	cows.push_back("Buttercup");
	cows.push_back("Sue");
	string a,b,t;
	for(int i=0;i<N;i++) {
		cin>>a;
		cin>>t;
		cin>>t;
		cin>>t;
		cin>>t;
		cin>>b;
		beside_a.push_back(a);
		beside_b.push_back(b);
	}
	do{
		if(satisfies_constraints()) {
			for(int i=0;i<8;i++) cout<<cows[i]<<"\n";
			break;
		}
	}while(next_permutation(cows.begin(),cows.end()));
	return 0;
}

```


---

## 作者：Invisible_Blade (赞：3)

先用 map <string,int> 存储8头牛名字的字典序:

mp["Beatrice"]=1,mp["Belinda"]=2;

mp["Bella"]=3,mp["Bessie"]=4;
    
mp["Betsy"]=5,mp["Blue"]=6;
	
mp["Buttercup"]=7,mp["Sue"]=8;

然后用 map <int,string> 用来存储字典序对应的牛名字.

t[1]="Beatrice";t[2]="Belinda";

t[3]="Bella";t[4]="Bessie";

t[5]="Betsy";t[6]="Blue";

t[7]="Buttercup";t[8]="Sue";


------------

然后用邻阶矩阵和一个一维数组存储牛与牛之间的关系.

int f[N][N],vis[N],du[N];

du[i]表示第i个点的度,即有几条边与i结点相连,这个用来判断一个点是否在一条链中,非则就是一个孤立的点.

for(re i=1;i<=n;++i){

		string x,y,a,b,c,d;
		cin>>x>>a>>b>>c>>d>>y;
		++du[mp[x]],++du[mp[y]];
		f[mp[x]][mp[y]]=f[mp[y]][mp[x]]=1;
}

这里说明一下,题目的输入要求里只有第一个和第六个是牛的名字,所以用x,y代表这两头牛,用a,b,c,d跳过这些没用的.



------------
tot来记录有几头牛已经挤奶了.vis[i]表示第i个牛有没有挤奶过

if(!vis[i]&&du[i]!=2)用来判断一个点在没有访问过的前提下,那么第一个没有被访问过的,且它不是一条链中间的点,就是字典序最小的点,记录为now.
先把now对应的名字输出,++tot,然后看它的du[now]是否为1,如果是1,就说明它是一条链的开头,进行dfs搜索它所在的链,否则du[now]为0,说明它是个孤立的点.

while(tot<8){

	for(re i=1;i<=8;++i)
		if(!vis[i]&&du[i]!=2){now=i;break;}
	cout<<t[now]<<endl;
	++tot,vis[now]=1;
		if(du[now]==1)dfs(now);
	}

以下是dfs的打法,就是在矩阵中找到与其相邻的点一直搜,搜到一个先输出在搜下一个.

inline void dfs(int x){

	for(re i=1;i<=8;++i)
		if(f[x][i]&&i!=x&&vis[i]==0){
			vis[i]=1;++tot;
			cout<<t[i]<<endl;
			dfs(i);
			break;
		}
	}



------------
所以总代码如下:
```
#include <map>
#include <cstdio>
#include <string>
#include <iostream>
#define re register int
using namespace std;
const int N=50;
map <string,int> mp;
map <int,string> t;
int n,tot,now;
int f[N][N],vis[N],du[N];
inline void dfs(int);
int main(){
//	freopen("lineup.in","r",stdin);
//	freopen("lineup.out","w",stdout);
	mp["Beatrice"]=1,mp["Belinda"]=2;
	mp["Bella"]=3,mp["Bessie"]=4;
	mp["Betsy"]=5,mp["Blue"]=6;
	mp["Buttercup"]=7,mp["Sue"]=8;
	t[1]="Beatrice";t[2]="Belinda";
	t[3]="Bella";t[4]="Bessie";
	t[5]="Betsy";t[6]="Blue";
	t[7]="Buttercup";t[8]="Sue";
	scanf("%d",&n);
	for(re i=1;i<=n;++i){
		string x,y,a,b,c,d;
		cin>>x>>a>>b>>c>>d>>y;
		++du[mp[x]],++du[mp[y]];
		f[mp[x]][mp[y]]=f[mp[y]][mp[x]]=1;
	}
	while(tot<8){
		for(re i=1;i<=8;++i)
			if(!vis[i]&&du[i]!=2){now=i;break;}
		cout<<t[now]<<endl;
		++tot,vis[now]=1;
		if(du[now]==1)dfs(now);
	}
	return 0;
}
inline void dfs(int x){
	for(re i=1;i<=8;++i)
		if(f[x][i]&&i!=x&&vis[i]==0){
			vis[i]=1;++tot;
			cout<<t[i]<<endl;
			dfs(i);
			break;
		}
}
```


---

## 作者：guoxinyugz (赞：2)

可以作为搜索的练习题。

其实这题本质上就是求满足条件的**全排列**，

由于数据范围较小，可以**暴力搜索出一个数列再判断**。

此题比较让人难受的是字典序。所以我们要确定好每个名字对应什么数，每个数对应什么名字。

```
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n;
char a[25];
int b[10],c[10];
int x[10],y[10];
bool ok=0;
int f1()//名字转换为数
{
	if(strcmp(a,"Beatrice\0")==0) return 1;
	if(strcmp(a,"Belinda\0")==0) return 2;
	if(strcmp(a,"Bella\0")==0) return 3;
	if(strcmp(a,"Bessie\0")==0) return 4;
	if(strcmp(a,"Betsy\0")==0) return 5;
	if(strcmp(a,"Blue\0")==0) return 6;
	if(strcmp(a,"Buttercup\0")==0) return 7;
	if(strcmp(a,"Sue\0")==0) return 8;
}
void f2(int p)//数转换为名字
{
	if(p==1) printf("Beatrice\n");
	else if(p==2) printf("Belinda\n");
	else if(p==3) printf("Bella\n");
	else if(p==4) printf("Bessie\n");
	else if(p==5) printf("Betsy\n");
	else if(p==6) printf("Blue\n");
	else if(p==7) printf("Buttercup\n");
	else printf("Sue\n");
}
bool che()//检查数列是否符合条件
{
	for(int i=1;i<=n;i++)
		if(x[b[i]]-x[c[i]]!=1 && x[b[i]]-x[c[i]]!=-1)
			return 0;
	for(int i=1;i<=8;i++)
		f2(y[i]);
	return 1;
}
void g(int p)//搜索
{
	if(p>8)//判断
	{
		if(che()) ok=1;
		return; 
	}
	for(int i=1;i<=8 && !ok;i++)//枚举
		if(!x[i])
		{
			x[i]=p;
			y[p]=i;
			g(p+1);
			x[i]=0;
		}
}
int main()
{
	freopen("lineup.in","r",stdin);
	freopen("lineup.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a);
		b[i]=f1();
		scanf("%s%s%s%s%s",a,a,a,a,a);//过滤没用的单词
		c[i]=f1();
	}
	g(1);
   return 0;
}

```


---

## 作者：zimindaada (赞：2)

[题解 P5833 【[USACO19DEC]Livestock Lineup牲畜阵容】](https://www.luogu.com.cn/problem/P5833)

题意：已知$8$头奶牛，每头奶牛有一个名字。给定一个$N$，以及已知$N$头奶牛之间排列的关系，求所有符合要求的排列中，名字字典序最小的一个排列

这一道题我用的很奇怪的方法，有点想复杂了。其实可以用全排列直接算一遍的（我同学说是这么做的）

我用的是一个双向链表$lb$数组存奶牛之间的关系，再用$de$数组存每个奶牛的度（或者说是有几个和别的牛在一起的要求）。

然后从字典序小的往后遍历，如果度为$0$，则这个牛就是无拘无束的，可以直接排。如果度为$1$，就要排完了这个后，按照链表以这个牛为头的顺序，依次放下去。这个很容易证明是对的。如果先遍历到了链表的另一头，则这个方法肯定比从另一头开始字典序小，毕竟这一头的字典序比另一头小。度为2的不用管，因为他一定在某个链中间，这个链被排好了他也一定就被排好了。

另外，在往下搜的过程中，必须要打$vis$标记，这样才能保证你搜完了链表的一头以后不会再从另一头搜一遍……

如果还有看不懂的，看代码吧，注释很详细。
```cpp
//Code by zimindaada in 20191220
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
int n;
char beat[] = "Beatrise", beli[] = "Belinde", bell[] = "Bella", bess[] = "Bessie", \
    bets[] = "Betsy", blue[] = "Blue", butt[] = "Buttercup";//因为cmp不能直接用"Bessie"来做参数所以搞了这个愚蠢的玩意儿……
inline bool cmp(char a[], char b[]){//我不太会用char数组，所以打了一个奇怪的cmp来代替==
    int l = strlen(b);
    for(int i = 0; i < l; ++i){
        if(a[i] != b[i]) return 0;
    }
    return 1;
}
inline int convert(char t[]){//为了方便，把名字按顺序转换成数字
    if(cmp(t, beat)) return 1;
    else if(cmp(t, beli)) return 2;
    else if(cmp(t, bell)) return 3;
    else if(cmp(t, bess)) return 4;
    else if(cmp(t, bets)) return 5;
    else if(cmp(t, blue)) return 6;
    else if(cmp(t, butt)) return 7;
    else return 8;
}
int de[10];//每个牛的度（或者说是每个牛已经和几个牛确定了关系）
int lb[10][2];//双向链表
bool vis[10];//vis标记
inline string back(int t){//从数字转换回字符串的函数
    if(t == 1) return "Beatrise";
    else if(t == 2) return "Belinde";
    else if(t == 3) return "Bella";
    else if(t == 4) return "Bessie";
    else if(t == 5) return "Betsy";
    else if(t == 6) return "Blue";
    else if(t == 7) return "Buttercup";
    else return "Sue";
}

//核心函数//
void dfs(int fa, int x){//fa代表上一个,x代表目前的
    //首先因为前面已经被选了，所以它必须被选
    cout << back(x) << endl;
    for(int i = 1; i <= de[x]; ++i){
        if(lb[x][i] != fa && !vis[lb[x][i]]){//确保搜到的不是上一个
            vis[lb[x][i]] = 1;
            dfs(x, lb[x][i]);
        }
    }
}

int main(){
    scanf("%d",&n);
    char s1[15], s2[15];//输入用变量
    for(int i = 1; i <= n; ++i){
        scanf("%s must be milked beside %s",s1, s2);//输入
        int x1 = convert(s1), x2 = convert(s2);
        lb[x1][++de[x1]] = x2; lb[x2][++de[x2]] = x1;//链表存
    }
    
    //核心代码//
    for(int i = 1; i <= 8; ++i){//遍历一遍八头牛
    
        //由字典序定义，前面越小字典序小，所以尽可能让更前面的更小
        if(vis[i]) continue;//如果遍历/dfs过了一遍，就跳过
        
        if(de[i] == 0){//如果没有关系
            //因为遍历到它，说明当前最好的方案就是选他，
            cout << back(i) << endl;//就可以直接放。
            vis[i] = 1;//记得打标记
        }else if(de[i] == 1){//如果有1个关系
            vis[i] = 1;
            //同上，但是因为它是一个链表的头，
            dfs(-1,i);//所以要用dfs遍历一遍链表（用for或while也行）
        }
    }
    return 0;
}
```
注：该代码有防抄措施，在题解非核心代码上的做了修改！

---

## 作者：Akoasm_X (赞：1)

**感觉有些麻烦**

不过还是做出来了

思路：用next_permutation不断变换顺序，同时判断是否符合条件
符合条件就会输出，结束程序
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m=1;
string a[10]={"0","Bessie","Buttercup","Belinda","Beatrice","Bella","Blue","Betsy","Sue" };//赋初值 
string t[10][10];
int find(string t)
{
	for(int i=1;i<=8;i++)
		if( a[i]==t )
			return i;
}
bool judge()
{
	for(int i=1;i<=n;i++)
	{
		if( abs( find(t[i][1])-find(t[i][6]) ) != 1)//相邻 
			return false;
	}
	return true;
}
//欢迎指出如何优化这两个函数 
int main()
{
//	freopen("lineup.in","r",stdin);
//	freopen("lineup.out","w",stdout);
	for(int i=1;i<=8;i++)
		m*=i;//算方案数，不算也行 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=6;j++)
			cin>>t[i][j];
		//比较懒，直接就这样存了 
		//其实t[][2]......t[][5]是没用的
		//只有t[][1]和t[][6]是有用的 
	}
	sort(a+1,a+9);//一定要按照最小字典序排一遍 
	while(m--) 
	{
		if(judge())//先判断 
		{
			for(int j=1;j<=8;j++)
				cout<<a[j]<<endl;
			return 0;
		}
		next_permutation(a+1,a+9);//换到下一个 
	} 
	return 0;
}
```


---

