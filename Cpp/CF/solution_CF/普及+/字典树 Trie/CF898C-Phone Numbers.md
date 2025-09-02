# Phone Numbers

## 题目描述

Vasya有几本电话簿，他记录了他的朋友的电话号码。他的每个朋友可以有一个或几个电话号码。
Vasya决定组织有关朋友电话号码的信息。您将获得n个字符串 - 来自Vasya电话簿的所有条目。每个条目都以朋友的名字开头。然后跟随当前条目中的电话号码数量，然后是电话号码本身。有可能几部相同的电话被记录在同一记录中。
Vasya还认为，如果电话号码a是电话号码b的后缀（即，电话号码b以a结尾），并且两个电话号码都由Vasya写成同一个人的电话号码，则记录a并且没有城市代码，它是不被考虑在内的。
任务是输出有关Vasya朋友电话号码的组织信息。两个不同的人可能有相同的号码。如果一个人有两个数字x和y，并且x是y的后缀（即y以x结尾），那么您不应该输出数字x。如果Vasya电话簿中的朋友的号码以相同的格式记录多次，则有必要将其记录一次。
阅读样例以更好地理解输出的语句和格式。

## 样例 #1

### 输入

```
2
ivan 1 00123
masha 1 00123
```

### 输出

```
2
masha 1 00123 
ivan 1 00123 
```

## 样例 #2

### 输入

```
3
karl 2 612 12
petr 1 12
katya 1 612
```

### 输出

```
3
katya 1 612 
petr 1 12 
karl 1 612 
```

## 样例 #3

### 输入

```
4
ivan 3 123 123 456
ivan 2 456 456
ivan 8 789 3 23 6 56 9 89 2
dasha 2 23 789
```

### 输出

```
2
dasha 2 23 789 
ivan 4 789 123 2 456 
```

# 题解

## 作者：Strelizia_Qy (赞：3)

**题目分析：**

本题用 Trie 字典树做，主要有以下几个要点：

- 注意到题目说的是**后缀**，所以在建树时要反着建。

- 名字处理比较麻烦，可以用 **map** 搞定。

- 因为有不止一个人，所以要开结构体，给每个人都建一棵树。

- 输出也是一个重点，详见代码。


------------
献上 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+5;
int n,names_cnt=0;
map<string,int>names_vis;//在输入时记录这个名字是否在之前出现过 
map<int,string>names;//记录每个编号对应的名字 
map<string,int>names_num;//与上面相反，记录每个名字对应的编号 
struct node
{
	int cnt=0;
	int tag[maxn];//记录在字典树中此字符被经过几次 
	int pos[maxn];//记录有多少个电话号码以此字符结束 
	int ch[maxn][10];//字典树 
	int this_num=1;//此人当前电话号码总数 
	string all[maxn];//存储该名字下所有电话号码
}a[21];
void ins(int m,string number)//建树 
{
	int p=0,len=number.size();
	for(int i=len-1;i>=0;i--)//因为是“后缀 ”，所以反着存 
	{
		int x=number[i]-'0';
		if(!a[m].ch[p][x])a[m].ch[p][x]=++a[m].cnt;
        //如果没出现过，开新的节点
		p=a[m].ch[p][x];
		a[m].tag[p]++;//经过次数++
	}
	a[m].pos[p]++;//以此字符结尾次数++
}
int find1(int m)//查找此人（处理后）剩余电话号码的数量 
{
	int ans=0;
	for(int i=0;i<=a[m].cnt;i++)
	{
		if(a[m].tag[i]==1&&a[m].pos[i]) ans++;
		//如果该字符仅被经过一次，且有号码以该字符结尾，OK 
		else if(a[m].tag[i]&&a[m].pos[i]&&a[m].tag[i]==a[m].pos[i])ans++;
		//重点：如果被经过次数与结尾次数一致，说明有重复的号码，增加一个 
	}
	return ans;
}
void find2(int m)//输出此人（处理后）剩余的所有电话号码 
{
	for(int j=1;j<=a[m].this_num-1;j++)//遍历所有号码 
	{
		int p=0,len=a[m].all[j].size();
		for(int i=len-1;i>=0;i--)
		{
			int x=a[m].all[j][i]-'0';
			p=a[m].ch[p][x];
		}
		if(a[m].tag[p]==1&&a[m].pos[p]) cout<<a[m].all[j]<<" ";
		else if(a[m].tag[p]&&a[m].pos[p]&&a[m].tag[p]==a[m].pos[p])cout<<a[m].all[j]<<" ";
		//判断条件同上 
	}
}
int main()
{
	names_vis.clear();
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string s;
		int k;
		cin>>s>>k;
		if(!names_vis[s])//如果这个名字没出现过 
		{
			names_vis[s]++;//标记 
			names[++names_cnt]=s;//存储编号 
			names_num[s]=names_cnt;//再反向存一次，方便后面操作 
		}
		for(int j=1;j<=k;j++)
		{
			string x;
			cin>>x;
			bool flag=0;
			int m=names_num[s];
			for(int l=0;l<=a[m].this_num-1;l++)//查重标记 
				if(a[m].all[l]==x)
					flag=1;
			if(flag==0)//如果第一次出现 
			{
				a[names_num[s]].all[a[names_num[s]].this_num]=x;
				//存入此人下的数组 
				a[names_num[s]].this_num++;
			}
			ins(names_num[s],x);//将这个电话号码加入树中 
		}
	}
	cout<<names_cnt<<endl;//先输出名字总数 
	for(int i=1;i<=names_cnt;i++)
	{
		cout<<names[i]<<" ";//输出人名 
		cout<<find1(i)<<" ";//输出电话号码数 
		find2(i);//输出电话号码 
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：笙歌 (赞：3)

字典树？？？

不会就暴力吧。~~反正数据范围小~~

话不多说上pascal(过程详见注释)：
```pascal
var
        u,o,t,x,i,j,namcnt,fff,k,cnthz,l:longint;
        s1,s:string;
        pd:boolean;
        nam,b:array[0..500]of string;
        a,check:array[0..500,0..500]of string;
        c,cntcheck:array[0..500]of longint;
        p:array[0..1000]of boolean;
begin
        readln(u);
        for o:=1 to u do begin
            readln(s);
            s:=s+' ';
            t:=pos(' ',s);
            x:=0;
            while t<>0 do begin
                inc(x);
                if x=1 then begin
                   s1:=copy(s,1,t-1);
                   pd:=true;
                   for i:=1 to namcnt do if nam[i]=s1 then begin
                       pd:=false;
                       break;
                   end;//名字判重
                   if pd then begin
                      inc(namcnt);//即namcnt++
                      nam[namcnt]:=s1;
                      i:=namcnt;
                   end;
                end;//第一个空格前面即为名字
                if x>2 then begin
                   inc(c[i]);
                   a[i,c[i]]:=copy(s,1,t-1);
                end;
                delete(s,1,t);
                t:=pos(' ',s);//每次找空格copy前面的一段，找完delete
            end;//第3个空格以后为电话号码
        end;//合并所有名字并存入a[名字代号][第几个电话]=号码数组
        //nam[]存所有名字
        {for i:=1 to namcnt do begin
            write(nam[i],' ',c[i],' ');
            for j:=1 to c[i] do write(a[i,j],' ');
            writeln;
        end;}
        //调试跳过
        writeln(namcnt);//不重复的名字个数
        for i:=1 to namcnt do begin
            for j:=1 to c[i]-1 do begin
                for k:=j+1 to c[i] do begin
                    if (((length(a[i,j])=length(a[i,k])) and (a[i,j]>a[i,k]))
                    or (length(a[i,j])>length(a[i,k]))) then begin
                       a[i,0]:=a[i,j];
                       a[i,j]:=a[i,k];
                       a[i,k]:=a[i,0];
                    end;
                end;
            end;//每个人的所有电话冒泡排序，由小到大（位数少到位数多）
            fillchar(p,sizeof(p),true);
            for j:=0 to 100 do for k:=0 to 100 do check[j,k]:='';
            fillchar(cntcheck,sizeof(cntcheck),0);
            cntcheck[i]:=1;
            check[i,cntcheck[i]]:=a[i,1];//每个人初始化一次
            for j:=2 to c[i] do begin
                if a[i,j]=a[i,j-1] then continue;
                inc(cntcheck[i]);
                check[i,cntcheck[i]]:=a[i,j];
            end;//电话号码去重，去重后放进check[][]数组
            for j:=0 to 100 do b[j]:='';
            cnthz:=0;//初始化
            for j:=cntcheck[i] downto 1 do begin
                l:=length(check[i,j]);
                for k:=2 to l do begin
                    inc(cnthz);
                    b[cnthz]:=copy(check[i,j],k,l-k+1);
                end;
            end;//求出每个不重复号码的后缀（不包括本身）存入b数组
            fillchar(p,sizeof(p),true);
            fff:=cntcheck[i];//fff即为多少个满足题意的电话号码
            for j:=1 to cntcheck[i] do begin
                for k:=1 to cnthz do begin
                    if check[i,j]=b[k] then begin
                       p[j]:=false;
                       dec(fff);//即fff--
                       break;
                    end;
                end;
            end;
            write(nam[i],' ',fff,' ');
            for j:=1 to cntcheck[i] do if p[j] then write(check[i,j],' ');
            writeln;//完美输出
        end;
end.
```

---

## 作者：Aisaka_Taiga (赞：2)

应某人的邀请来做了这个题目。

很普通的字典树，看完题目不难想到可以每一个人开一棵字典树建立查询，对于后缀的问题，我们可以插入的时候倒序枚举，就可以很好的解决这个问题了。

这道题目难在对于数据的输出。

1. 电话号是可能重复的，这个时候要特判电话号经过当前点的数量是不是大于 $1$ 且与以当前点为末尾的字符串数量相等，如果相等则此人电话号数量加一或者输出电话号。

2. 用 `map` 来处理可以很好的解决人名与编号的问题，需要开两个，一个表示当前人名对应的编号，一个表示当前编号对应的人名，通过判断当前人名是否有对应的编号来判断是否出现过。

3. 在遍历的时候我们可以直接把所有的电话号都给存起来方便后面查询，重复的不存。

调了两个小时的代码（或许用结构体更方便？）：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 10010;
int n, ncnt;//ncnt是一共多少个人名 
map<string,int>nnum;//人名对应的编号 
map<int,string>names;//编号对应的人名 
int cnt[21], tag[21][N], pos[21][N], t[21][N][10], num[21]; 
string a[21][N];//第一维都是表示第i个人，a是当前人所有的电话号 

inline void add(int x, string s)//插入字符串 
{
	int p = 0, len = s.size();
	for(int i = len - 1; i >= 0; i --)//后缀，倒序插入 
	{
		int c = s[i] - '0';
		if(!t[x][p][c])t[x][p][c] = ++ cnt[x];
		p = t[x][p][c];
		tag[x][p] ++;//记录当前点经过的电话号数量 
	}
	pos[x][p] ++;//记录当前电话号的末尾 
}

inline int ask(int x)//询问当前人的电话号数量 
{
	int res = 0;//最终答案数目 
	for(int i = 0; i <= cnt[x]; i ++)//遍历每一个点 
	{
		if(tag[x][i] == 1 && pos[x][i]) res ++;//如果当前人的当前点只有一个电话号经过并且是末尾那就直接加一 
		else if(tag[x][i] && pos[x][i] && tag[x][i] == pos[x][i]) res ++;//这个是处理有两个电话号重复的地方 
	}
	return res; 
}

inline void print(int x)//打印当前人的所有电话号 
{
	for(int j = 1; j <= num[x]; j ++)//枚举所有电话号 
	{
		int p = 0, len = a[x][j].size();
		for(int i = len - 1; i >= 0; i --)//倒序遍历 
		{
			int c = a[x][j][i] - '0';
			p = t[x][p][c];
		}
		if(tag[x][p] == 1 && pos[x][p]) cout << a[x][j] << " ";//如果要是只有一个电话号到过这里并且是末尾就输出 
		else if(tag[x][p] && pos[x][p] && tag[x][p] == pos[x][p]) cout << a[x][j] << " ";//处理重复的串。 
	}
}

signed main()
{
	cin >> n;
	int nnn = n; 
	while(nnn --)
	{
		string s;
		int k;
		cin >> s >> k;
		if(!nnum[s])//如果要是当前人名没出现过 
		{
			names[++ ncnt] = s;//存一下，标记出现过 
			nnum[s] = ncnt;//存对应人名的编号 
		}
		for(int i = 1; i <= k; i ++)//枚举当前人的电话号 
		{
			string x;
			cin >> x;
			int flag = 0, m = nnum[s];//flag是标记当前电话号是否合法 ，m是当前人名的编号 
			for(int l = 0; l <= num[m]; l ++)//枚举每一个电话 
				if(a[m][l] == x) flag = 1;//如果有一样的就标记不合法 
			if(flag == 0)//是合法的电话号 
				a[m][++ num[m]] = x;//存入当前的人名下面 
			add(m, x);//插入当前号码 
		}
	}
	cout << ncnt << endl;//输出人名数量 
	for(int i = 1; i <= ncnt; i ++)
	{
		cout << names[i] << " " << ask(i) << " ";//输出当前人的人名和电话号数量 
		print(i);//打印电话号码 
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Jur_Cai (赞：2)

Trie 的板子题，没什么好讲的，只要倒着存每一个电话号码，就转化为判断前缀了。名字用 map 存一下，每个人下面建一棵树，最后 dfs 输出就好了，详见代码。

不会判断前缀的可以先做[这道题](https://www.luogu.com.cn/problem/UVA11362)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
int num=0;
struct node {
	int son[15],flag,sum;//flag表示是否为电话号码的结尾 
	node() {
		flag=sum=0;
		memset(son,0,sizeof(son));
	}
}trie[25][2005];//数组一定要开的足够大，RE了好几次 
inline void insert(int p,char* x) {
	int l=strlen(x),u=0,tf=1;
	for(int i=l-1;i>=0;i--)	{
		int v=x[i]-'0';
		if(!trie[p][u].son[v]) trie[p][u].son[v]=++num,tf=0;
		if(trie[p][u].flag) trie[p][u].flag=0,trie[p][0].sum--; 
		u=trie[p][u].son[v];
	}
	if(!tf) trie[p][u].flag=1,trie[p][0].sum++;//判断自己是否为某一串前缀 
}
char tmp[50];
int len=0;
inline void print() {
	putchar(' ');
	for(int i=len;i>=1;i--) putchar(tmp[i]);
}
void dfs(int p,int u) {
	if(trie[p][u].flag) return print();
	for(int i=0;i<=9;i++) 
		if(trie[p][u].son[i]) {
			tmp[++len]=i+'0';
			dfs(p,trie[p][u].son[i]);
			len--;
		}
}
map<string,int> mp;
int cnt=0;
string nm;
char s[50];
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		cin>>nm;
		if(mp.find(nm)==mp.end()) mp[nm]=++cnt;
		int m,p=mp[nm];
		scanf("%d",&m);
		for(int i=1;i<=m;i++) {
			scanf("%s",s);
			insert(p,s); //建树 
		}
	}
	cout<<mp.size()<<endl;
	for(map<string,int>::iterator i=mp.begin();i!=mp.end();i++) {
		int p=i->second;
		cout<<i->first<<" "<<trie[p][0].sum;
		dfs(p,0);//遍历Trie输出 
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Fido_Puppy (赞：1)

## 题目

[CF898C Phone Numbers](https://www.luogu.com.cn/problem/CF898C)

## Sol

那么就正式进入了。 首先， 看题目得看重点。 有没有关注到那个 1<=n<=20 ， 相信小盆友们都能猜到我要干什么了。

### 没错， 暴力！

那么暴力的思路还是很明显的， 枚举字符串的后缀就行辣。 其实就是一边删电话号码， 一边去掉第一个数字。

用什么来存呢。

**事实证明， MAP 又回来了。**

那么代码也很容易就能写出了。

**NOTICE：**

- C++ 中的字符串下标是从 0 开始的。
- C++ 中从第 pos 个字符开始， 删 k 个字符：$\texttt{s.erase(pos,k);}$

## Code

```cpp
#include <iostream>
#include <cstring>
#include <map>
using namespace std;
map <string, int> b, c;
string name[21], a[21][101];
int d[21];
int n;
int main () {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> name[i] >> d[i];
		if (c[name[i]] == 0) {
			c[name[i]] = i;
			for(int j = 1; j <= d[i]; j++) cin >> a[i][j], ++b[a[i][j]];
			for(int j = 1; j <= d[i]; j++) {
				if (b[a[i][j]] == 0) continue;
				string s = a[i][j];
				int t = s.size();
				for(int k = 1; k < t; k++) {
					s.erase(0, 1);
					if (b[s] != 0) b[s] = 0;
				}
			}
			int K = d[i];
			d[i] = 0;
			for(int j = 1; j <= K; j++) {
				if (b[a[i][j]] != 0) a[i][++d[i]] = a[i][j], b[a[i][j]] = 0;
			}
		}
		else {
			int T = d[c[name[i]]];
			d[c[name[i]]] += d[i];
			for(int j = 1; j <= T; j++) ++b[a[c[name[i]]][j]];
			for(int j = T + 1; j <= d[c[name[i]]]; j++) cin >> a[c[name[i]]][j], ++b[a[c[name[i]]][j]];
			for(int j = 1; j <= d[c[name[i]]]; j++) {
				if (b[a[c[name[i]]][j]] == 0) continue;
				string s = a[c[name[i]]][j];
				int t = s.size();
				for(int k = 1; k < t; k++) {
					s.erase(0, 1);
					if (b[s] != 0) b[s] = 0;
				}
			}
			int K = d[c[name[i]]];
			d[c[name[i]]] = 0;
			for(int j = 1; j <= K; j++) {
				if (b[a[c[name[i]]][j]] != 0)
					a[c[name[i]]][++d[c[name[i]]]] = a[c[name[i]]][j], b[a[c[name[i]]][j]] = 0;
			}
		}
	}
	int M = 0;
	for(int i = 1; i <= n; i++) if (c[name[i]] == i) ++M;
	cout << M << endl;
	for(int i = 1; i <= n; i++) {
		if (c[name[i]] == i) {
			cout << name[i] << " " << d[i] << " ";
			for(int j = 1; j <= d[i]; j++) cout << a[i][j] << " ";
			cout << endl;
		}
	}
	return 0;
}
```

完结撒花！

---

## 作者：乘风破浪ing (赞：1)

	这题数据规模小，暴力存储+字典树就能A（本人蒟蒻不会指针）
    belong[x][y]指第x个人的字典树中第y号节点是第几个答案
    a[x][y][z]指第x个人的第y个电话号码，z是具体号码
    ren[][]用来存名字
    #include<cstdio>
	#include<cstring>
	using namespace std;
	char ming[10],b[11],a[21][201][11],ren[21][11];
	int renshu=0,longren[21],jishu[21],ch[21][2000][10],belong[21][2000];
	int panduanren(){//判断这是第几个人
	int len=strlen(ming);
	if(renshu==0){
		renshu=1;
		longren[1]=len;
		for(int i=0;i<len;i++)	
			ren[1][i]=ming[i];
		return 1;//返回记录的位置 
	}
	bool flag;
	for(int i=1;i<=renshu;i++){
		if(longren[i]==len){//longren是指名字长短
			flag=1;
			for(int j=0;j<len;j++){
				if(ming[j]!=ren[i][j]){
					flag=0;
					break;
				}
			}
			if(flag){
				return i;
			}
		}
	}
	//如果能够到这里，说明这个人没记录过 
	renshu++;
	longren[renshu]=len;
	for(int i=0;i<len;i++){	ren[renshu][i]=ming[i];} 
	return renshu;
	}

	void build(int x) {//x是指第几个人
	int len=strlen(b);
	int u=1,huanwei=0;
	bool kaiwei=0;//判断有没有新的分支 
	for(int i=len-1;i>=0;i--){//后缀 
		int c=b[i]-'0';
		if(!ch[x][u][c]){
			kaiwei=1;
			++ch[x][0][0];//计数，相当于tot	
			ch[x][u][c]=ch[x][0][0];
		}
		u=ch[x][u][c];
		if(belong[x][u]!=0)	{//如果之前有点在这 
			huanwei=belong[x][u];//替代原先的点 
			belong[x][u]=0;//重置为0 
		}
	}
	if(huanwei!=0){//遇到了belong 
		belong[x][u]=huanwei;
		for(int o=0;o<len;o++){
			a[x][belong[x][u]][o]=b[o];
		}
	}
	else{//没遇到belong 
		if(kaiwei){//开了位置 
			belong[x][u]=++jishu[x];
			for(int o=0;o<len;o++)
				a[x][belong[x][u]][o]=b[o];
		}
		//没有遇到belong并且没开新的位置的话，这个点就不要了 
	}
	}

	int main(){
	for(int i=0;i<=20;i++)	ch[i][0][0]=1;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ming);
		int weizhi=panduanren();//找这个人的记录的位置
		int m;
		scanf("%d",&m);
		for(int j=1;j<=m;j++){
			scanf("%s",b);
			build(weizhi);
		}
	}
	printf("%d\n",renshu);
	for(int i=1;i<=renshu;i++){
		printf("%s %d ",ren[i],jishu[i]);	
		for(int j=1;j<=jishu[i];j++)
		printf("%s ",a[i][j]);
		printf("\n");
	}
	}

---

## 作者：enyyyyyyy (赞：0)

- 思路：

  看一眼好似很普通的字典树，可以给每一个人开一棵字典树来遍历，如果不会的可以看[字典树](https://www.luogu.com.cn/problem/P3375)， $1\le n\le 20$ 看似可以暴力，暴力思路是枚举所有字符串的后缀，由此可以使用 `map`，那正解也更明确了。

- 字典树：

  对于每次失配之后，我都不会从头重新开始枚举，而是根据我已经得知的数据，从某个特定的位置开始匹配；而对于模式串的每一位，都有唯一的“特定变化位置”，这个在失配之后的特定变化位置可以帮助我们利用已有的数据不用从头匹配，从而节约时间。

 ```cpp
long long n,m,ne[1000050];
char s[1000050],p[1000050];
int main(){
	cin>>s+1>>p+1;
	n=strlen(s+1),m=strlen(p+1);
	for(int i=2,j=0;i<=m;i++){
		while(j&&p[i]!=p[j+1])j=ne[j];
		if(p[i]==p[j+1])++j;
		ne[i]=j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j&&s[i]!=p[j+1])j=ne[j];
		if(s[i]==p[j+1])++j;
		if(j==m){
			cout<<i-m+1<<endl;
			j=ne[j];
		}
	}
	for(int i=1;i<=m;i++)cout<<ne[j]<<" ";
	return 0;
}
```
- 输入处理：

 ```cpp
void op() {//输入处理
	st s;
	cin >> s;
	ll n = read();
	for (int i = 0; i < n; i++) {
		string s2;
		cin >> s2;
		mp[s].insert(s2);//加入字典树
	}
}

```

- 主要程序

 ```cpp
void op2() {//主要程序
	print(mp.size()), printf("\n");
	for (auto k : mp) {
		auto i = k.first;
		cout << i, printf(" ");
		auto j = k.second;
		for (auto x : j) {
			for (size_t y = 1; y < x.size(); y++) {
				if (j.count(string(x.begin() + y, x.end())) == 1) {//统计
					j.erase(string(x.begin() + y, x.end()));//清空
				}
			}
		}
		print( j.size()), printf(" ");
		for (auto i : j) {
			cout << i, printf(" ");
		}
		printf("\n");
	}
}

```
- 主程序：

 ```cpp
int main() {
	t = read();
	while (t--) op();
	op2();
	return 0;
}
```

- 代码如下：

 ```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
typedef string st;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll t;
map<st, set<st>> mp;//set默认按键值升序
void op() {//输入处理
	st s;
	cin >> s;
	ll n = read();
	for (int i = 0; i < n; i++) {
		string s2;
		cin >> s2;
		mp[s].insert(s2);
	}
}
void op2() {//主要程序
	print(mp.size()), printf("\n");
	for (auto k : mp) {
		auto i = k.first;
		cout << i, printf(" ");
		auto j = k.second;
		for (auto x : j) {
			for (size_t y = 1; y < x.size(); y++) {
				if (j.count(string(x.begin() + y, x.end())) == 1) {//统计
					j.erase(string(x.begin() + y, x.end()));//清空
				}
			}
		}
		print( j.size()), printf(" ");
		for (auto i : j) {
			cout << i, printf(" ");
		}
		printf("\n");
	}
}
int main() {
	t = read();
	while (t--) op();
	op2();
	return 0;
}
```




---

## 作者：Maysoul (赞：0)

## 简化题意：

题目不好读，但很好懂。

给出 $n$ 个朋友的名字，每个朋友有 $m$ 个电话号，对于每个朋友，如果存在一个电话号 $s_{1}$ 是  $s_{2}$ 的后缀，则将 $s_{1}$ 省去。

特别的，如果存在多个 $s_{1}$ 是  $s_{2}$ 的后缀，那么应保留一个 $s_{1}$。

输出有几个朋友，和他们的电话号。

## 简述思路：

对于多个字符串寻找前缀的题目，我们自然而然的就想到 Trie 树。

而这题的要求是后缀，实际只需要将字符串反转，就可以变换成前缀问题。

而每一个朋友都是独立的，互不干扰，因此我们可以对每一个朋友都建立一棵 Trie，将每个朋友的电话号都插入到 Trie 里。

然后在 Trie 里找后缀即可，注意如果找到了两个字符串完全相同，那么无论是否构成后缀都应该保留这个字符串。而对于多个相同的字符串我们只需保留一次，这时候特判标记是否为 $1$ 即可。

在一开始，我们可以将整个电话簿装入一个 `map`，以便于对每一个朋友进行操作。

处理完一个朋友之后，注意要清空 Trie。

## Code:

```cpp
//2023/7/29
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans;
unordered_map<string,vector<string>> mp;//用map存放朋友
struct Trietree{
	int cnt=0;
	int flag=0;
	int child[10]={0};
}trie[2*MAXN];
int tcnt=0;
inline bool insert(string &s)
{
	bool flag=1;
	int rootid=0;
	for (int i=s.length()-1;i>=0;i--){//倒序枚举，后缀转前缀
		char c=s[i];
		int cid=c-'0';
		if(trie[rootid].child[cid]==0) trie[rootid].child[cid]=++tcnt;
		trie[rootid].cnt++;
		rootid=trie[rootid].child[cid];
	}
	if(trie[rootid].cnt){//如果构成后缀
		if(trie[rootid].flag==1) flag=1;//如果完全相同
		flag=0;
	}
	trie[rootid].cnt++;
	trie[rootid].flag++;
	return flag;
}
bool cmp(string aa,string bb)
{
	return aa.size()>bb.size();
}
vector<string> vec;//存放当前答案
inline void sweep()
{
	for (int i=0;i<=tcnt;i++){
		memset(trie[i].child,0,sizeof(trie[i].child));
		trie[i].cnt=0;
		trie[i].flag=0;
	}
	tcnt=0;
	vec.clear();
}
int main()
{
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n,k;
	cin>>n;
	string s,str;
	for (int i=1;i<=n;i++){
		cin>>s;
		cin>>k;
		for (int j=1;j<=k;j++){
			cin>>str;
			mp[s].push_back(str);
		}
	}
	cout<<mp.size()<<'\n';
	for (pair<string,vector<string>> pr:mp){
		string name=pr.first;
		sort(pr.second.begin(),pr.second.end(),cmp);
		for(string i:pr.second){
			if(insert(i)) vec.push_back(i);
		}
		cout<<name<<" "<<vec.size()<<" ";
		for (string i:vec){
			cout<<i<<" ";
		}
		sweep();
		cout<<'\n';
	}
}
```


---

## 作者：冷却心 (赞：0)

## 题意

有 $n$ 个条目，每个条目由名称和 $k_i$ 个字符串组成。如果在一个条目中，一个字符串是另一个字符串的 **后缀**，那么把它删除。

输出修改后 $n$ 个条目的名称，个数与各个字符串。

**名称可能重复，要放到同一个条目中**。

## 解法

一道 Trie 的应用。

后缀可以把字符串倒过来改为前缀来处理。

楼下其他巨佬求总长度都是 **在插入时直接统计字符串数量**，鄙人想到一种更为方便的办法：插入时不需要管这个结点是否组成字符串，只要在求长度时 进行 DFS 统计, 遍历一遍 Trie, 因为 如果这个字符串不是某一个字符串的后缀，那么这个结点 **一定没有子结点**，所以如果这个结点没有子结点，那么 ````len ++````。

输出同样是一个 DFS。同样的，如果这个结点没有子结点，那么就将以这个结点结尾的字符串输出。_（因为是倒过来存 Trie，所以输出也要倒过来）_。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define	Fcin \
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 25;
const LL MAXS = 1e4 + 10;
LL n;

// Trie 类 Fri是 Friend
class Fri{
	private:
		LL SIZE, nxt[MAXS][30], L = 0;
		bool has[MAXS];
		
		// 统计字符串个数
		void tongji(LL now){
			bool flag = true;
			for (LL i = 0; i <= 9; i ++){
				if (nxt[now][i]){
					flag = false;
					tongji(nxt[now][i]);
				}
			}
			// 如果这个结点没有子节点，那么它一定不是任意一个字符串的后缀
			if (flag)
				++ L;
			return ;
		}
	
	public:
		string name;
		// 返回长度
		LL size(){
			L = 0;
			tongji(0);
			return L;
		}
		
		// 插入
		void insert(string str){
			LL len = str.size();
			// 当前结点
			LL now = 0;
			
			// 倒过来存
			for (LL i = len - 1; i >= 0; i --){
				LL ch = str[i] - '0';
				
				// 如果这个结点没有字符为 str[i] 的 边，那么加入一条边
				if (!nxt[now][ch])
					nxt[now][ch] = ++ SIZE;
				now = nxt[now][ch];
			}
			return ;
		}
		
		void output(LL now, string res){
			bool flag = true;
			
			for (LL i = 0; i <= 9; i ++){
				if (nxt[now][i]){
					flag = false;
					// 因为是倒过来存，所以倒过来输出
					string s = (char)(i + '0') + res;
					output(nxt[now][i], s);
				}
			}
			
			// 与统计函数同理
			if (flag)
				cout << res << " ";
		}
	
}fri[N];
map<string, int> mp;
int main(){
	Fcin;
	
	LL len = 0;
	cin >> n;
	LL k;
	string str;
	for (LL i = 1; i <= n; i ++){
		cin >> str;
		LL ind;
		
		// 给名字去重
		if (!mp.count(str)){
			ind = ++ len;
			mp[str] = len;
		}
		else 
			ind = mp[str];
		fri[ind].name = str;
		cin >> k;
		for (LL j = 1; j <= k; j ++){
			cin >> str;
			fri[ind].insert(str);
		}
	}
	
	// 输出
	cout << len << "\n";
	for (auto it : mp){
		LL p = it.second;
		cout << it.first << " " << fri[p].size() << " ";
		fri[p].output(0, "");
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：Swiftie_wyc22 (赞：0)

这应该是我绿题里面目前写的最长的代码了。这题的思路不难，但是写起来代码会很长。

官方题解的思路是用 map 保存电话薄，过程中进行相同名字的去重、去后缀等操作（题解中用 set）。map 肯定是要用的（花了一上午现学），要先学会 map 再来做这道题。

## map

下面简单介绍一下本题中用到的 map。


map 是映射表，定义方法是：


```cpp
map<type1, type2> m;
```

`type1` 是键，`type2` 是值，合在一起组成键值对。可以通过键访问值，用法是：

```cpp
map<string, int>m;
m["tom"] = 1;
m["tony"] = 2;
cout << m["tom"] << endl; // 输出的是 1

```


我们也可以用迭代器遍历 map，用 `i->first`、`i->second` 访问 map 的键和值。

查找键：用在这道题里就是查找是否有重复的人名，用法是:

```cpp
m.find(内容);
```

find 函数有返回值，返回值要用相应的迭代器接收，我们这里只需要知道如果返回值等于 `m.end()` 就是没有找到键就可以。

还是奉劝不会 map 的同学，先学会 map 的各种操作再来。
可以到这里学习：

<http://www.cplusplus.com/reference/map/map/>

## 解题思路

这里我们需要定义的映射表是由字符串和一个字符串数组构成的，字符串中存储的是人名（键），数组中存储每一个电话。

对于每一次输入的人名，如果是新的，那么就创建新的，然后输入完 $x$ 个电话，进行自身判重；如果不是新的，那么每输一个电话，进行判重与去后缀。

对于输入的电话号码 $\text{v}$，既要判断 $\text{v}$ 是不是先前电话号码的后缀，也要判断先前号码是不是 $\text{v}$ 的后缀！

删除掉的电话号码用 `--------` 代替。

## 完整代码

两个函数可以合并，代码比较冗长，码风很奇特请谅解。

```cpp
#include <bits/stdc++.h>
#define DEBUG cout<<"debug"<<endl
using namespace std;
map < string , vector<string> > m;
int n;

void calc(string name, string v)
{
	
		// 相互都不能是后缀
		// 标记用----- 
	for (int i = 0; i < m[name].size(); i++)
	{
		if (m[name][i] == "--------") continue;
		if (m[name][i] == v)
			return;
			
			
			
			
		if (v.size() == 1 && m[name][i].size() > 1)
			if (m[name][i][m[name][i].size() - 1] == v[0])
			{
				return;
			}
		if (m[name][i].size() == 1 && v.size() > 1)
			if (v[v.size() - 1] == m[name][i][0])
			{
				m[name][i] = "--------";
				continue;
			}	
			
			
		if (m[name][i].size() == v.size())
			if (m[name][i] == v)
				return;
			else
				continue;
				
			
			
		if (m[name][i].size() > v.size())
		{
			int k = m[name][i].size() - v.size();
//			if (m[name][i].substr(k, v.size() - 1) == v) // should i -1?
			if (m[name][i].substr(k, v.size()) == v)
				return;
		}
		else
		{
//			DEBUG;
//			cout << "i=" << i << endl;
			int k = v.size() - m[name][i].size();
			// 原有数据中有 v 的后缀
//			if (v.substr(k, m[name][i].size() - 1) == m[name][i]) // should i -1?
			if (v.substr(k, m[name][i].size()) == m[name][i])
			{
				m[name][i] = "--------";
			}
			
		}
	}
	m[name].push_back(v);
}
void selfcheck(string name)
{
	for (int i = 0; i < m[name].size(); i++)
	{
		if (m[name][i] == "--------") continue;
		for (int j = i + 1; j < m[name].size();j++)
		{
			if (m[name][j] == "--------") continue;
			
			if (m[name][i] == m[name][j])
			{
				m[name][j] = "--------";
				continue;
			}
			
			if (m[name][i].size() == m[name][j].size())
				if (m[name][i] == m[name][j])
					m[name][j] = "--------";
			
			
			if (m[name][j].size() == 1)
				if (m[name][i][m[name][i].size() - 1] == m[name][j][0])
				{
					m[name][j] = "--------";
					continue;
				}
			if (m[name][i].size() == 1)
				if (m[name][j][m[name][j].size() - 1] == m[name][i][0])
				{
					m[name][i] = "--------";
					continue;
				}
				
				
				
			
			if (m[name][i].size()>m[name][j].size())
			{
				int k = m[name][i].size() - m[name][j].size();
				
				if (m[name][i].substr(k, m[name][j].size()) == m[name][j])
					m[name][j] = "--------";
			}
			else
			{
				int k = m[name][j].size() - m[name][i].size();
				
				if (m[name][j].substr(k, m[name][i].size()) == m[name][i])
				{
					m[name][i] = "--------";
				}
			}
		}
	}
} 

int main()
{
	ios::sync_with_stdio(false);
	string name; int x;
	string t;
	
	cin >> n;
	while (n--)
	{
		cin >> name; cin >> x;
		
		if (m.find(name) == m.end())
		{
			for (int i = 1; i <= x; i++)
			{
				cin >> t;
				m[name].push_back(t);
			}
			selfcheck(name); // 自检O(n^2); 
		}
		else
		{
//			DEBUG;
			for (int i = 1; i <= x; i++)
			{
				cin >> t;
				calc(name, t);
			}
		}
		
		
		
//		for (int jj = 0; jj < m[name].size(); jj++)
//		{
//			cout << m[name][jj] << " ";
//		}cout << endl;
	}
	

	
	cout << m.size() << endl;
	for ( map <string , vector<string> >::iterator i = m.begin(); i != m.end(); i++)
	{
		selfcheck(i -> first);
		cout << i->first << " ";
		
		int length = i->second.size();
		string output = "";
		
		for (int j = 0; j < i->second.size(); j++)
		{
			if (i->second[j] != "--------") 
//				cout << i->second[j] << " ";
				output += i->second[j] + " ";
			else
				length--;
		}
		cout << length << " " << output;
		
		
		
		cout << endl;
	}
	return 0;
}
```


蒟蒻的第一篇题解，管理员大大求过~（我没有数学公式所以没用 LaTeX）

---

