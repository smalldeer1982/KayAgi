# Keyboard

## 题目描述

你有一个长方形的键盘，共 $n$ 行，每行 $n$ 个键。每个键可以打出小写字母，在按下 Shift 键时也可以打出大写字母。键盘上每个键是一个边长为 $1$ 的正方形，相邻的键之间没有空隙。

你想用一只手吃辣条，另一只手编程，所以你得尝试只用一只手打字。但是当打字时按得键离 Shift 键太远（欧几里得距离大于 $x$）时，你就不得不用到另一只手。 请计算出使用另一只手的最小次数。

## 样例 #1

### 输入

```
2 2 1
ab
cd
1
A
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2 2 1
ab
cd
1
e
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 2 1
ab
cS
5
abcBA
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3 9 4
qwertyuio
asdfghjkl
SzxcvbnmS
35
TheQuIcKbRoWnFOXjummsovertHeLazYDOG
```

### 输出

```
2
```

# 题解

## 作者：Superiority (赞：3)

## 大体思路
不是很难，可能代码会稍微长一点而已。

题目其实已经把思路告诉你了的，给大家简化一下如下：

- 如果键盘中没有 `S` 也即是 `Shift` 是肯定无解。

- 如果键盘上没要需要的按键也肯定无解。

- 如果要打大写字母且 `Shift` 键与这个要打的大写字母的小写字母距离的欧几里得距离大于 $x$ 就必须用右手。

再简单科普一下欧几里得距离。

欧几里得也称欧式距离，其实就是求两点之间距离的公式，可以看一下[这里](https://oi-wiki.org/geometry/distance/)。

$$ |AB| = \sqrt{(x_2-x_1)^2+(y_2-y_1)^2} $$

代表 $A$ 点到 $B$ 点的距离，$(x_1,x_2)$ 代表 $A$ 点的坐标 $(y_1,y_2)$ 则是 $B$ 的坐标。

代码就不给了哈，其实就上面的思路，注意一下坑就行了。

---

## 作者：Fuxh_18 (赞：2)

## 思路

这是一道简单的模拟题。

### 无法打出的条件

若是小写字母：键盘上无此字母。

若是大写字母：
1. 键盘上无此字母。
1. 键盘上无 Shift。

### 方法
输入时，将能够打出的小写字母存入**桶**，再计算出每个键盘上的字母所对应的大写字母与 Shift 的**最小**（可能有多个相同字母或 Shift）欧几里得距离（无法打出值则为 $0$）。在输入文本时，依次判断字母能否打出，若是大写字母，还需判断欧几里得距离是否大于 $x$。

这里将欧几里得距离的公式贴上

$d=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[31][31];
int n,m,x,shx[1001],shy[1001],tot,lit[301],a,ans;
double big[301];
int main(){
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			if(mp[i][j]=='S'){ //存入所有 Shift 的位置 
				shx[++tot]=i;
				shy[tot]=j;
			}
			else{
				lit[mp[i][j]]=1; //标记有此字母 
			}
		}
	}
	//处理能打出的大写字母 
	if(tot){ //含有 Shift 键才能打出大写字母 
		for(int i=1;i<=n;i++){ //方法：枚举 
			for(int j=1;j<=m;j++){
				if(mp[i][j]=='S') continue; //不处理 Shift 键 
				double L=INT_MAX;
				for(int k=1;k<=tot;k++){
					double l=sqrt(((double)shx[k]-(double)i)*((double)shx[k]-(double)i)+((double)shy[k]-(double)j)*((double)shy[k]-(double)j));
					L=min(L,l);
				}
				if(big[mp[i][j]-'a'+'A'])
					big[mp[i][j]-'a'+'A']=min(big[mp[i][j]-'a'+'A'],L);
				else
					big[mp[i][j]-'a'+'A']=L;
			}
		}
	}
	cin>>a;
	for(int i=1;i<=a;i++){
		char b;
		cin>>b;
		if(b>='a'&&b<='z')
			if(lit[b]) continue; //能打出，继续判断 
			else{ //无法打出，直接输出-1，结束程序 
				cout<<-1;
				return 0;
			}
		if(!big[b]){
			cout<<-1;
			return 0;
		}
		if(big[b]>x) ans++; //判断是否需要另一只手，更新答案 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaofeng_and_xiaoyu (赞：2)

一道不错的黄题，但坑点太多了。

思路如下

首先，看范围 $30$，一眼 DFS。

其次，字符存储，想到了 map。

把所有字符初始化为 $-1$。

读入，顺便将所有键盘上的字符一一记录，把对应的小写字符记录为 $0$。（小写不用计算距离）

先将 ‘S’ 的位置判断出来，然后计算各个位置与它最近的欧几里得距离，可以单手的话更改为 $0$，否则不动。

然后对所有字母判断，如果小写为 $0$ 说明出现，而大写为 $-1$ 说明在范围内未更新，需要用第二只手。

然后读入要打的字符串，如果为 $-1$ 说明没有更新，所以键盘上没有，输出 $-1$。

否则累加，最后把答案输出。

这是一份代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char q[35][35];
int a,b,l;
double gxlen[35][35];
double pdlen(int x,int y,int xx,int yy){
	return double(sqrt(1.0*abs(x-xx)*abs(x-xx)+1.0*abs(y-yy)*abs(y-yy)));
}
bool s[35][35],pd[35][35],pdshift=0;
map<char,int>m;
void cl(int x,int y,int sx,int sy){
	if(pdlen(x,y,sx,sy)>l)return;
	if(x<0||y<0||x>a||y>b)return;
	if(pd[x][y]&&gxlen[x][y]<=pdlen(x,y,sx,sy))return;
	if(q[x][y]>='a'&&q[x][y]<='z'){
		m[char(q[x][y]-('a'-'A'))]=0;
		cout<<q[x][y]<<' ';
	}
	gxlen[x][y]=pdlen(x,y,sx,sy);
	pd[x][y]=1;
	cl(x+1,y,sx,sy);
	cl(x,y+1,sx,sy);
	cl(x-1,y,sx,sy);
	cl(x,y-1,sx,sy);
}
int main(){
    cin>>a>>b>>l;
    for(char i='a';i<='z';i++)m[i]=-1;
    for(char i='A';i<='Z';i++)m[i]=-1;
    memset(s,0,sizeof(s));
    for(int i=0;i<a;i++){
    	for(int j=0;j<b;j++){
    		cin>>q[i][j];
    		if(q[i][j]!='S')m[q[i][j]]=0;
    		else s[i][j]=1;
		}
	}
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(s[i][j]){pdshift=1;break;}
		}
	}
	if(!pdshift){
		cout<<-1<<endl;
		return 0;
	}
	int ans=0;
	for(int i=0;i<=a;i++){
		for(int j=0;j<=b;j++){
			if(s[i][j]){
				cl(i,j,i,j);
			}
		}
	}
	for(char i='a';i<='z';i++){
		if(m[i]==0&&m[i-('a'-'A')]==-1){
			m[i-('a'-'A')]=1;
		}
	}
//	for(char i='a';i<='z';i++)cout<<m[i]<<' ';
//	cout<<endl;
//	for(char i='A';i<='Z';i++)cout<<m[i]<<' ';
//	cout<<endl;
	int lenx;
	cin>>lenx;
	string x;
	cin>>x;
	for(int i=0;i<lenx;i++){
		if(m[x[i]]==-1){
			cout<<-1;
			return 0;
		}else{
			ans+=m[x[i]];
		}
	}
	cout<<ans;
    return 0;
}
```
接下来串一下坑点：

1.欧几里得距离，返回的 double 有精度误差！

所以交了几发 MLE。

2.没有 shift 要判断，但没有 shift 只有小写也要判断！

[最终结果](https://codeforces.com/problemset/submission/88/226581012)

---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门：](https://www.luogu.com.cn/problem/CF88B)

**题意**：

如果你能打出这一行字符，那么输出用右手的最小使用次数。如果无法全部打出时，则输出 $-1$。

**分析**：

### 无解的情况

当有大写字符无 `Shift` 时，无解。

当键盘上没有要打的字时，无解。

### 右手次数

因为同时按，当两点欧几里得距离**大于** $x$ 时，需要用右手。

---

## 作者：boluo2014 (赞：1)

这题居然也能评黄？我感觉橙最多了。

### 思路
思路比较简单，主要就是搞定这个 `Shift`。此时有一些很显然的结论：

第一，如果文中有大写字母但是没有 `Shift` 肯定不行，不吃辣条也不行。并且，有的字符没有也不行。

第二，如果文中没有大写字母，那一定可以。直接输出 $0$。

第三，可以用一个二维的数组，对周围进行 dfs，标记所有可以到的位置都是 $1$。由于数据不大，是可以的。

第四，在搜索的过程中，由于数据比较小，不需要剪枝或差分。
### 代码（有注释）
第一部分：
```
bool cx[28];//是否出现
int n,m,x;
char a[31][31];
bool bj[31][31];//大写时能不能用Shift的标记
bool mhd(double fx,double fy,double tx,double ty);
bool Have_Shift=false;
int dfs(int x,int y,int fx,int fy);//x,y是当前坐标，fx,fy是初始坐标
bool use[28];//某个字符是否需要用到右手
int dir[4][2]={0,1,1,0,0,-1,-1,0};
```
第二部分：
```
cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cin>>a[i][j];
            if(a[i][j]=='S')
            {
                dfs(i,j,i,j);//标记
                Have_Shift=true;
            }
            else
            {
                cx[a[i][j]-'a'+1]=true;//出现过了
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(bj[i][j])
            {
                use[a[i][j]-'a'+1]=true;
            }
        }
    }
    string s;
    int len;
    cin>>len;
    cin>>s;
    bool Have_Big=false;
    bool yesno=true;
    for(i=0;i<len;i++)
    {
        if(s[i]>='a'&&s[i]<='z')
        {
            if(!cx[s[i]-'a'+1])//没出现过
            {
                yesno=false;
                break;
            }
        }
        else
        {
            Have_Big=true;
        }
    }
    if(Have_Big&&!Have_Shift)//有大写但是没有Shift
    {
        yesno=false;
    }
    if(!yesno)
    {
        cout<<"-1"<<endl;//不能了。
        return 0;
    }
```
第三部分：
```
bool mhd(double fx,double fy,double tx,double ty)
{
    double Biaojun=1.0*x;//注意精度，相当于类型转换
    double s=sqrt((fx-tx)*(fx-tx)+(fy-ty)*(fy-ty));//公式
    if(s>Biaojun)
    {
        return false;
    }
    return true;
}
int dfs(int x,int y,int fx,int fy)
{
    int dx,dy,i;
    for(i=0;i<4;i++)//4个方向
    {
        dx=x+dir[i][0];
        dy=y+dir[i][1];
        if(dx>=1&&dy>=1&&dx<=n&&dy<=m)
        {
            if(mhd(x,y,dx,dy)&&!bj[dx][dy])
            {
                bj[dx][dy]=true;
                dfs(x,y,dx,dy);
            }
        }
    }
}

```

一些简单的部分请自己写，思考一下哦！

---

## 作者：syf159 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF88B)

## 分析

题目简述：我有一个键盘，想要单手打字，当打大写字母时，需要按下 Shift 键。当字母与 Shift 键的距离大于 $x$ 时，计入答案。

我们可以通过数组 $shiftx$ 和 $shifty$ 记录下每个 Shift 键的坐标，然后进行预处理，枚举每一个键到 Shift 键的最短距离，再进行计算即可。

有以下几种情况需要输出 $-1$：

当目标字符为小写时：键盘上没有此字符；

当目标字符为大写时：

1. 键盘上没有此字符；
2. 没有 Shift 键。

附上欧几里得距离计算公式：$\sqrt{(x_1 - x_2) ^ 2 + (y_1 - y_2) ^ 2}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;
double dis[105];
char board[35][35];
int shiftx[2005],shifty[2005],shift_cnt=0;
bool shift_check;
bool check[35];
double cal_dis(int xa1,int ya1,int xa2,int ya2)//计算欧几里得距离 
{
	return sqrt((((double)(abs(xa1-xa2))*(double)(abs(xa1-xa2)))+((double)(abs(ya1-ya2))*(double)(abs(ya1-ya2)))));
}
void my_memset()//放入极大值 
{
	for(int i=1; i<=26; i++)
	{
		dis[i]=1000000;
	}
}
void work_dis()//计算字符与 shift 键的距离 
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(board[i][j]=='S') continue;
			int t=board[i][j]-'a'+1;
			double minn=1000000;
			for(int k=1; k<=shift_cnt; k++)
			{
				minn=min(minn,cal_dis(i,j,shiftx[k],shifty[k]));
			}
			dis[t]=min(dis[t],minn); 
		}
	}
	return ;
}
int q;
char que;
int ans;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	my_memset();
	cin>>n>>m>>x;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			cin>>board[i][j];
			if(board[i][j]=='S') shiftx[++shift_cnt]=i,shifty[shift_cnt]=j,shift_check=true;//记录 shift 键的位置 
			else check[board[i][j]-'a'+1]=true;
		}
	}
	if(shift_check) work_dis();
	cin>>q;
	while(q--)
	{
		cin>>que;
		if(que>='A'&&que<='Z')
		{
			if(!check[que-'A'+1])//特殊判断2 
			{
				cout<<"-1";
				return 0;
			}
			if(!shift_check)//特殊判断3 
			{
				cout<<"-1";
				return 0;
			} 
			if(dis[que-'A'+1]>x) ans++;
		}
		else
		{
			if(!check[que-'a'+1])//特殊判断1 
			{
				cout<<"-1";
				return 0;
			}
		}
	}
	cout<<ans;
	
	return 0;
}
```

---

## 作者：Jayfeather2012 (赞：0)

## 思路
一道模拟~~  
我们定义一个 map 存字符是否可打出与是否需要右手。  
根据题意，先遍历键盘，扫出所有 Shift 并存入数组中，再遍历一遍键盘，对于每个非 Shift 键，标记此小写字符可打出，对于它对应的大写字母，判断是否有一个 Shift 键与它的距离小于 $x$，若有，标记其可打出且不需右手，若没有，标记其可打出且需右手。  
最后根据信息判断文本能否打出并统计需要右手的次数。  
具体细节看代码吧！
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pp pair<int,int>
using namespace std;
int n,m,q,t,ans;
long double f,x[905],y[905];
string s;
char a[35][35];
map<char,int>mp;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>f;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
			if(a[i][j]=='S'){
            //是Shift键，存储其位置
				x[++t]=i;
				y[t]=j;
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			long double xx=i,yy=j;
            if(a[i][j]=='S')continue;
            //是Shift,不进行下面操作
			mp[a[i][j]]=1;
            //标记小写字母可打出
            if(mp[a[i][j]-'a'+'A']==1||!t)continue;
            //若已标记其可打出且不需右手或没有Shift键，不进行下面操作
			for(int k=1;k<=t;++k){
				if(sqrt(((xx-x[k])*(xx-x[k]))+((yy-y[k])*(yy-y[k])))<=f){
                //若距离小于等于x，标记其可打出且不需右手
					mp[a[i][j]-'a'+'A']=1;
					break;
				}
			}
			if(!mp[a[i][j]-'a'+'A'])mp[a[i][j]-'a'+'A']=2;
            //若距离都大于x，标记其不可打出且不需右手
		}
	}
	cin>>q>>s;
	for(int i=0;i<q;++i){
		if(mp[s[i]]==0){
			cout<<-1<<"\n";
			return 0;
            //不能打出输出-1并结束
		}
		if(mp[s[i]]==2)++ans;
        //若需要右手，增加需要右手的次数
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qingchenMC (赞：0)

## 思路

是一道模拟，但是需要注意的地方还挺多的，所以有一定难度。

按题意模拟即可。具体步骤：

1. 输入键盘布局后，求出每个键离最近的 `Shift` 的距离是多少。由于字符串长度较大，所以我们要尽量减少查询每个字符的时间复杂度。我们进行预处理后，只需要 $O(nm)$ 的时间就可以判断一个大写字符是否能打出。

2. 遍历要输出的字符串，如果是小写字母只需检查键盘上有没有这个字母就行。如果是大写字母，先判断键盘上是否有 `Shift`（这个操作其实只需要一遍，在循环外面就判断好了，要不然每碰到一个大写字母就得遍历一遍），要是有就遍历键盘，找到所有的这个字母。要是没有就输出 $-1$。

> **注意：这里中文题目其实没有说清楚：同一个键是可以出现多次的，所以我们必须遍历整个键盘，找到所有的目标字母。**

&emsp;&emsp;找到所有的这个字母后，取得该字母距离 `Shift` 的最小距离，如果大于 $x$，将计数器加一。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,m,x,q,cnt,hass;
string t;
char mp[32][32];
double tos[32][32];

double get_dis(int x1,int y1,int x2,int y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main(){
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			tos[i][j]=114514;
			cin>>mp[i][j];
		}
	}
	cin>>q>>t;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='S'){
				hass=1;
				for(int x=1;x<=n;x++){
					for(int y=1;y<=m;y++){
						if(mp[x][y]!='S'){
							tos[x][y]=min(tos[x][y],get_dis(i,j,x,y));
						}
					}
				}
			}
		}
	}
	
	for(int i=0;i<t.size();i++){
		if(t[i]>='a'&&t[i]<='z'){
			bool flag=0;
			for(int x=1;x<=n;x++){
				for(int y=1;y<=m;y++){
					if(mp[x][y]==t[i]){
						flag=1;
						break;
					}
				}
			}
			if(!flag){
				cout<<-1;
				return 0;
			}
		}
		else{
			if(!hass){
				cout<<-1;
				return 0;
			}
			bool flag=0;
			double mind=114514;
			for(int x=1;x<=n;x++){
				for(int y=1;y<=m;y++){
					if(mp[x][y]==t[i]-'A'+'a'){
						flag=1;
						mind=min(mind,tos[x][y]);
					}
				}
			}
			if(!flag){
				cout<<-1;
				return 0;
			}
			if(mind>x){
				cnt++;
			}
		}
	}
	cout<<cnt;
	return 0;
}
//https://codeforces.com/contest/88/submission/302593744
```

---

## 作者：jixiyue114514 (赞：0)

## **思路**
本题不是很难，只是代码会长一点。

题目其实已经给你思路了，给大家概括一下：

1. 如果键盘中没有 `S` 键（即 `Shift` 键）并且要打大写字母时，此题无解。
1. 如果需要使用键盘上没有的键也是无解。
2. 如果要打大写字母且 `S` 键与这个要打的大写字母的距离超过欧几里得距离（也称欧式距离）时，就必须使用右手。

简单科普一下欧几里得距离。[具体请看这里](https://oi-wiki.org/geometry/distance/)。
$$
|AB|=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}
$$
代表 $A$ 点到 $B$ 点的距离，$(x_1,y_1)$ 代表 $A$ 点的坐标，$(x_2,y_2)$ 代表 $B$ 点的坐标。

代码不给，注意这几点这道题就不难了。

---

## 作者：nxd_oxm (赞：0)

题好，但是要注意一些细节。
# 题意
就是给你一个键盘，需要输出一个字符串。

首先判断是否都能打出来，如果不能，输出 ``-1``，如果能，且是大写，就要用 ``Shift`` 键和对应的一个键来打出。因为要同时按，所以当两者距离大于 $x$ 的时候，就得用两只手。问最小的使用两只手的次数。
# 思路
很明显的贪心题。

我们分两种情况考虑：

- 小写
  - 如果是小写，则只需要判断有这个键没有就行了。
- 大写
  - 首先，键盘上可能有重复的键。
  - 其次，和小写一样，是要判断是否存在这个键的。
  - 因为我们要让使用两只手的次数最少，则我们要找到这个键其中的一个与另外一个 ``Shift`` 键的距离最短的情况。如果最短的情况距离还是大于 $x$，那就只能使用两只手，$ans$ 记录。如果是小于等于 $x$ 的，就不用记录。

那就有一个问题，我们如何找到最短的呢？

首先我们如果直接在字符串里找，是大写就用两重循环枚举计算最小值，太麻烦了，而且时间复杂度肯定超了。

我们不妨换一种思路，因为对于每个大写字母需不需要用两只手不是根据它在字符串中的位置决定的，而是键盘决定的，所以可以直接预处理。

有两种思路，第一是用 $26$ 个字母去找 ``Shift``，有就计算距离，更新最小值，用 ``map`` 存起来。第二是用 ``Shift`` 去找所有字母，找到就更新。两者均可，我用的第二种。

两种方法可能第一种稍微快一些，但都能过。

最后输出最小次数即可。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=INT_MAX-1;
long double jl(int a,int b,int c,int d){
	//计算欧几里得距离
	return sqrt((a-c)*(a-c)*1.0+(b-d)*(b-d)*1.0); 
}
char key[101][101];
long double mp[125];
bool have[125];
int main(){
	int n,m,x;
	cin>>n>>m>>x;
	for(int a=1;a<=122;a++){
		mp[a]=inf;
	}
	//输入，并标记键盘上是否有这个键 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>key[i][j];
			have[key[i][j]]=1;
		}
	}
	//用键盘上的每一个Shift更新所有的键 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(key[i][j]=='S'){
				for(int x=1;x<=n;x++){
					for(int y=1;y<=m;y++){
						if(key[x][y]!='S'){
							mp[key[x][y]]=min(mp[key[x][y]],jl(i,j,x,y));
						}
					}
				}
			}
		}
	}
	int u,ans=0;
	string q;
	cin>>u;
	cin>>q;
	//逐个查看需要打印的字符串需不需要使用另一只手 
	for(int i=0;i<u;i++){
		if(q[i]>='A'&&q[i]<='Z'){
			if(mp[q[i]-'A'+'a']==inf){//没有这个键 
				cout<<-1;
				return 0;
			}else{
				//如果最近的距离是大于x的，则需要另一只手 
				if(mp[q[i]-'A'+'a']>x){
					ans++;
				}
			}
		}else{
			//若是小写，只需要判断是否有这个字符 
			if(!have[q[i]]){
				cout<<-1;
				return 0;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：NKL丶 (赞：0)

看完题目之后的第一反应便是暴力，读入一个字符便在键盘内寻找一次（先找一次小写字母，然后找$shift$键），如果一只手按不了$shift$便ans++，如果不符合条件便输出$-1$。  
但是字符串的长度（$5 \times 10^5$）意味着暴力是不可行的。（极限时间复杂度为$5 \times 10^5 \times 30^4$，妥妥的$TLE$）  
这时候便需要考虑优化，我们可以进行预处理。对于一个小写字母（例如$a$），我们便现在键盘内找字母$a$，找到一个$a$，便再寻找一次键盘，寻找$shift$，计算距离，以此来寻找打出来$A$的最优方法。  
这样子的话时间复杂度为$26 \times 30^4$，不会有问题。  
$\color{red}\texttt{PS:一定要留意没有shift和某个小写字母的情况。}$  
直接讲的话难以理解，直接附上代码，里面有注释，方便理解
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,len,vis[27],ans;
double dis[27],x;//一定要定义为double，避免精度误差
char map[35][35];
double diss(int x,int y,int xx,int yy){return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));}//计算欧几里得距离的函数
string a;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m>>x;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>map[i][j];
            if(map[i][j]>='a')vis[map[i][j]-'a'+1]=1;//重点：记录该小写字母是否出现过，用于查看是否为-1的情况
        }
    }
    for(char g='a';g<='z';g++)//a到z遍历一遍
    {
        dis[g-'a'+1]=55;//初始值，避免没有shift的情况，将结果设为一定比x大的数字
        for(int i=1;i<=n;i++)//遍历一遍键盘
            for(int j=1;j<=m;j++)
                if(map[i][j]==g)//找到了g
                    for(int k=1;k<=n;k++)//再次遍历一遍键盘
                        for(int h=1;h<=m;h++)
                            if(map[k][h]=='S')dis[g-'a'+1]=min(dis[g-'a'+1],diss(i,j,k,h));//如果找到了shift键，更新最小值（该字符距离某个shift键的最短距离）
    }
    cin>>len>>a;//字符串
    for(int i=0;i<len;i++)
    {
        if((a[i]<='Z'&&dis[a[i]-'A'+1]==55)||(a[i]>='a'&&!vis[a[i]-'a'+1]))//不合法的处理，没有shift键但是要大写，或是没有这个小写字符
        {
            cout<<-1;
            return 0;//直接退出
        }
        if(a[i]<='Z'&&dis[a[i]-'A'+1]>x)ans++;//手短，ans++
    }
    cout<<ans;
    return 0;
}
```


---

