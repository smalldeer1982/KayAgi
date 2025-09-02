# Perfect Keyboard

## 题目描述

Polycarp wants to assemble his own keyboard. Layouts with multiple rows are too complicated for him — his keyboard will consist of only one row, where all $ 26 $ lowercase Latin letters will be arranged in some order.

Polycarp uses the same password $ s $ on all websites where he is registered (it is bad, but he doesn't care). He wants to assemble a keyboard that will allow to type this password very easily. He doesn't like to move his fingers while typing the password, so, for each pair of adjacent characters in $ s $ , they should be adjacent on the keyboard. For example, if the password is abacaba, then the layout cabdefghi... is perfect, since characters a and c are adjacent on the keyboard, and a and b are adjacent on the keyboard. It is guaranteed that there are no two adjacent equal characters in $ s $ , so, for example, the password cannot be password (two characters s are adjacent).

Can you help Polycarp with choosing the perfect layout of the keyboard, if it is possible?

## 样例 #1

### 输入

```
5
ababa
codedoca
abcda
zxzytyz
abcdefghijklmnopqrstuvwxyza```

### 输出

```
YES
bacdefghijklmnopqrstuvwxyz
YES
edocabfghijklmnpqrstuvwxyz
NO
YES
xzytabcdefghijklmnopqrsuvw
NO```

# 题解

## 作者：Limit (赞：4)

# 前置芝士

1. [图的遍历](https://baike.baidu.com/item/图遍历/6590947?fr=aladdin):通过DFS或者BFS遍历全图.
2. [前向星](https://baike.baidu.com/item/前向星/8737279?fr=aladdin):用来存边,但是在本题用也可以用一个二维数组解决.

# 具体做法

先从判断YES和NO开始,可以发现如果一个字母与三个及以上不同的字母相邻时肯定是不合法的,每个字母与左右的字母连一条边以后如果产生一个长度大于2的环也是不合法的.所以最终合法的图中没有环,没有一个点连出两条以上的边,自然可以发现这就是一堆链了,所以可以从出度为1或0的点开始遍历,如果可以遍历全图自然就没有环了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
int N,M,T,tot;
int out[114541];//出度
char s[114514];//字符串
bool visit[114514];//遍历时不可以遍历两次同一个点,所以需要记录一下
int answer[114514];//记录答案
//链式前向星
struct Edge
{
	int next,to;
}edge[114514];
#define FOR(now) for(int _i_=head[now];_i_;_i_=edge[_i_].next)
#define SON edge[_i_].to
int cnt=0;
int head[1111];
bool p[233][233];//判断两字母是否相邻
void AddEdge(int form,int to)//加边
{
	edge[++cnt].to=to;
	edge[cnt].next=head[form];
	head[form]=cnt;
}
void DFS(int now)//DFS遍历
{
	if(visit[now])//如果访问过就不再访问
	{
		return;
	}
	visit[now]=1;//修改为已经访问
	answer[++tot]=now;//记录答案
	FOR(now)
	{
		DFS(SON);
	}
}
void work()
{
//注意初始化
	REP(i,'a','z')
	{
		out[i]=0;
		head[i]=0;
	}
	REP(i,'a','z')
	REP(j,'a','z')
	{
		p[i][j]=0;
	}
	cnt=0;
	tot=0;
	cin>>s;
	N=strlen(s)-1;
	REP(i,1,N)
	{
		if(!p[s[i]][s[i-1]])//如果原来没有相邻
		{
			//连边
			AddEdge(s[i],s[i-1]);
			AddEdge(s[i-1],s[i]);
			//两字母出度都++
			out[s[i]]++;
			out[s[i-1]]++;
			if(max(out[s[i]],out[s[i-1]])>2)//如果出度大于2了就是NO
			{
				printf("NO\n");
				return;
			}
			p[s[i]][s[i-1]]=p[s[i-1]][s[i]]=1;//改为已经相邻
		}
	}
	REP(i,'a','z')
	{
		visit[i]=0;
	}
	REP(i,'a','z')//遍历全图
	{
		if(!visit[i])
		{
			if(out[i]<=1)//从出度为0,1的位置开始
			DFS(i);
		}
	}
	REP(i,'a','z')//如果有没有遍历到的点就是NO
	{
		if(!visit[i])
		{
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
	REP(i,1,tot)printf("%c",answer[i]);//输出答案
	printf("\n");
}
int main()
{
	scanf("%d",&T);
	REP(i,1,T)
	work();
	return 0;
}

```

---

## 作者：lemonfor (赞：4)

我们可以开一个数组来模拟这个排列，当我们进行到某一位时，检测左右的是否与下一个相同，不相同则继续往后扫，相同则说明不合法，结束就行了。
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define _ 0
#define INF 0x3f3f3f
#define int long long
#define re register
#define drep(i ,l ,r) for(re int i = (l) ; i >= (r) ; -- i)
#define rep(i ,l ,r) for(re int i = l ; i <= r ; ++ i)
using namespace std;
char s[1000];
bool used[30] ,flag;
int t ,tmp ,qwq[100] ,l;
int read() {
    char cc = getchar() ; int cn = 0 ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
    return flus * cn;
}
signed main() {
    t = read();
    while(t --) {
        memset(used ,0 ,sizeof used) ,memset(qwq ,0x3f ,sizeof qwq) ,scanf("%s" ,&s);
        l = strlen(s) ,flag = 0 ,tmp = 30;
        rep(i ,0 ,l - 1) s[i] -= 'a';used[qwq[tmp] = s[0]] = 1;
        rep(i ,1 ,l - 1) 
        if((qwq[tmp + 1] >= INF && !used[s[i]]) || qwq[tmp + 1] == s[i]) 
        qwq[++ tmp] = s[i] ,used[s[i]] = 1;//判断右边
        else if((qwq[tmp - 1] >= INF && !used[s[i]]) || qwq[tmp - 1] == s[i]) 
        qwq[-- tmp] = s[i] ,used[s[i]] = 1;//左边
        else {puts("NO");flag = 1;break;}//不合法
        if(!flag) {
            puts("YES");
            rep(i ,0 ,99) if(qwq[i] < INF) printf("%c" ,qwq[i] + 'a');//先输出用过的
            rep(i ,0 ,25) if(!used[i]) printf("%c" ,i + 'a');//输出没用过的
            printf("\n");
        }
    }
    return ~~(0^_^0);
}
```

---

## 作者：Konnyaku_ljc (赞：3)

##### 题意——
给出一段序列s，你需要构造一个序列a，使得序列s中两两相邻的字母在序列a中两两相邻，a中包含26个字母并且不能重复，若能输出YES和序列a，若不能，输出NO。  

##### 解释——
那么，我们只需要对序列s从头进行排列，相邻的放上一个字母在两边，当放不下时，输出NO。  
小小的模拟，以下是代码详情及解释
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int t,r,l;
string s;//原始序列s 
char a[60];//构造序列a 
bool b[1000],bo;
//查询字母是否使用过以及是否结束 
int main()
{
	cin >> t;//数据组数 
	while (t--)
	{
		cin >> s;
		bo = 0;
		memset (b,0,sizeof(b));
		for ( int i = 0; i <= 59; i++ ) a[i] = '1';
		int mid = 30,l=30,r=30;//清零 
		a[30] = s[0] , b[s[0]-'a'+1] = 1;//初始化 
		for ( int i = 1; i < s.size(); i++ )
		{
			if ( b[s[i]-'a'+1] && a[mid-1] != s[i] )
			    if (a[mid+1] != s[i] && a[mid] != s[i] )
			    {
			        cout << "NO" << endl , bo = 1;
				    break;
				    //如果这个字母已被使用并且前后都不是，凉凉 
			    }
		    else if ( a[mid-1] == s[i] ) 
			{ 
			    mid--; continue;
			}
		    else if ( a[mid+1] == s[i] ) 
			{
			    mid++; continue;
			}
			else if ( a[mid] == s[i] ) continue;
			//mid改变，继续 
			if ( a[mid+1] == '1' ) mid++,a[mid] = s[i];
		    else if ( a[mid-1] == '1' ) mid--,a[mid] = s[i];
		    //字母没被使用，找一个位置存上 
		    else 
			{
			    cout << "NO" << endl , bo = 1;
				break;
				//没有位置给他，凉凉 
			}
		    l = min(l,mid) , r= max(r,mid);
		    b[s[i]-'a'+1] = 1;
		    //最左边与最右边取最值，标记使用过 
		}
		if (bo) continue;//结束了 
		cout << "YES" << endl;
		for ( int i = l; i <= r; i++ ) cout << a[i];
		//输出密码的 
		for ( int i = 1; i <= 26; i++ ) 
		{
			if (!b[i]) cout << char(i-1+'a');
		}//输出剩下的 
		cout << endl;
	}
	return 0; 
}
```


---

## 作者：linyihdfj (赞：1)

## C.Perfect Keyboard ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16436837.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1303/C)
### 题目分析： ###
这种题很显然要先考虑转化为图上的问题。

很显然我们可以在 $S$ 中相邻的两个字符之间连边，表示这两个字符必须相邻。

判断无解的条件也很明显了：

1. 某个点的度数大于等于 $3$，因为一条连边表示一个相邻关系，不可能同时与三个字符相邻。
2. 出现大于等于 $3$ 的环，这个也是相当显然的自己手推一下就知道不可能

那么剩下的就是一条条的链了，那么就按顺序扫过这一条链，到了某个节点就输出这个节点代表的字母就好了，为了避免重复输出应该记一个数组表示这个字母有没有输出过。

也需要注意一点：要从度数为 $1$ 的点开始扫，因为度数为 $2$ 意味着一种中间的关系，显然只能一边边地输出无法从中间扩展。
### 代码详解： ###

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50;
int head[MAXN],cnt,du[MAXN],edge[MAXN][MAXN];
bool vis[MAXN],flag,use[MAXN];
void dfs(int now,int from){
	vis[now] = true;
	for(int i=0; i<26; i++){
		if(i == from || !edge[now][i] || now == i) continue;
		if(vis[i]){
			flag = true;
			return;
		}
		dfs(i,now);
	}
}
void get_ans(int now,int from){
	if(!vis[now])
		cout<<char(now + 'a');
	vis[now] = true;
	for(int i=0; i<26; i++){
		if(vis[i] || i == from || !edge[now][i] || now == i)	continue;
		get_ans(i,now);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(edge,0,sizeof(edge));
		memset(vis,false,sizeof(vis));
		memset(use,false,sizeof(use));
		memset(du,0,sizeof(du));
		cnt = 0;
		flag = false;
		int mx = 0;
		string s;
		cin>>s;
		for(int i=0; i<s.size() - 1; i++){
			if(!edge[s[i]-'a'][s[i+1]-'a']){
				du[s[i]-'a']++;
				du[s[i+1]-'a']++;
				mx = max(mx,max(du[s[i]-'a'],du[s[i+1]-'a']));
			}
			edge[s[i]-'a'][s[i+1]-'a'] = true;
			edge[s[i+1]-'a'][s[i]-'a'] = true;
			use[s[i] - 'a'] = true;
			use[s[i+1] - 'a'] = true;
		}
		for(int i=0; i<26; i++){
			if(!vis[i]){
				dfs(i,i);
			}
			if(flag)
				break;
		}
		if(flag || mx >= 3){
			printf("NO\n");
		}
		else{
			printf("YES\n");
			memset(vis,false,sizeof(vis));
			for(int i=0; i<26; i++){
				if(du[i] == 1)
					get_ans(i,i);
			}
			for(int i=0; i<26; i++){
				if(!vis[i])
					cout<<char(i + 'a');
			}
			printf("\n");
		}
	}
	return 0;
}
```


因为可能含有大量的重边而且点的数量很少所以可以考虑使用邻接矩阵。
  
输出的时候也要注意可能有的点没有出现那么就在最后输出这些没有出现的点。
  
所谓有大小大于等于三的环也可以理解为无向图上的有环，也就是如果从当前节点可以到达一个曾经访问过但不是其父亲的点那么就意味着有环。

---

## 作者：gyh20 (赞：1)

在最后的字母表中，每个字母至多和两个字母相邻。

记录下每个字母需要和那两个字母相邻(大于 $2$ 直接判不可能)

之后做一个类似拓扑排序的东西

先把所有没有出现的字母存入答案。

**注意:以下的相邻代表在给出的字符串中相邻并且没有在答案中出现过**

$1.$找到一个只需要和一个字母相邻的字母，并存入答案。

$2.$加入这个相邻的字母，并找到与它相邻的字母。

$3.$如果存在两个相邻的字母，则输出 $-1$

$4.$如果还有没有使用的字母，重复步骤 $1$
```cpp
#include<cstdio>
#include<cstring>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int n,a[32],b[32];
char s[100002],ans[32];
bool v[32];
inline int find(){
	for(re int i=1;i<=26;++i)if(!v[i])if((!b[i]&&!v[i])||(v[a[i]]&&!v[i]))return i;
	return 27;
}
signed main(){
	v[0]=1;
	int t=read();
	while(t--){
		scanf("%s",s+1);
		n=strlen(s+1);
		bool ia=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(v,0,sizeof(v));
		v[0]=1;
		for(re int i=1;i<n;++i){
			if(!a[s[i]-'a'+1]||a[s[i]-'a'+1]==s[i+1]-'a'+1){
				a[s[i]-'a'+1]=s[i+1]-'a'+1;
			}
			else if(!b[s[i]-'a'+1]||b[s[i]-'a'+1]==s[i+1]-'a'+1){
				b[s[i]-'a'+1]=s[i+1]-'a'+1;
			}
			
			else{
				ia=1;
				puts("NO");
				break;
			}
			if(!a[s[i+1]-'a'+1]||a[s[i+1]-'a'+1]==s[i]-'a'+1){
				a[s[i+1]-'a'+1]=s[i]-'a'+1;
			}
			else if(!b[s[i+1]-'a'+1]||b[s[i+1]-'a'+1]==s[i]-'a'+1){
				b[s[i+1]-'a'+1]=s[i]-'a'+1;
			}
			
			else{
				ia=1;
				puts("NO");
				break;
			}
		}
		if(ia)continue;
		int k,tot=0;
		while((k=find())<27){
			while(1){
				v[k]=1;
				ans[++tot]=k;
				if(v[a[k]]&&v[b[k]])break;
				if(!v[a[k]]&&!v[b[k]]){
				ia=1;
				puts("NO");
				break;
			}
				if(!v[a[k]])k=a[k];
				else k=b[k];
			}
			if(ia)break;
		}
		for(re int i=1;i<=26;++i){
			if(!v[i]){
				ia=1;
				puts("NO");
				break;
			}
		}
		if(ia)continue;
		puts("YES");
		for(re int i=1;i<=26;++i)putchar(ans[i]+'a'-1);
		putchar('\n');
	}
}
```



---

## 作者：skydogli (赞：1)

这道题还蛮有意思的。

可以使用爆搜通过，但是直接构造键盘是可以的。具体来说，假设当前处理到$s_i$，键盘位置为$\text x$，表示键盘上字母的数组为$\text k$

- 如果$s_i=k_x$，那么无需处理

- 否则，如果$s_i=k_{x-1}$或$k_{x+1}$，将x跳到对应位置即可。

- 否则，如果$s_i$出现过，那么说明键盘上已有该字符且和当前位置不相邻，那么显然无解。

- 否则，如果$k_{x-1}$或$k_{x+1}$上没有字母，那么将$\text x$跳到相应位置，并将这个位置的字符赋为$s_i$

- 否则，同样无解。

可以简单证明一下：

- 当$s_i$出现过时，显然要按下键盘上$s_i$所在位置的按键，方案唯一。

- 当$s_i$未出现，那么显然要在当前位置的相邻位置作为这个字符的键位，而只有在一开始，出现第$2$种字母时，才会出现当前位置左右都是空白的情况，这时选左边或右边都是等价的，其他时候，方案是唯一的。

所以为了满足要求，每次都只有唯一可能的一种方案，我们判断是否可行即可。

为了防止向左访问负数下标，我们一开始的下标可以设得比26大一点。

另外，最后要在构造的键盘后面随意输出所有未出现过的字母。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MN 200005
#define LL long long
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
inline void chkmax(int &a,int b){if(a<b)a=b;}
inline void chkmin(int &a,int b){if(a>b)a=b;}
inline int read(){
	   int a=0,fh=1;char c=getchar();
	   while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	   while('0'<=c&&c<='9'){
		   a=a*10+c-48;
		   c=getchar();
	   }
	   return a*fh;
}
char ch[MN];
int T;
int vis[26],use[26];
char ans[75];
int main(){
	scanf("%d",&T);
	while(T--){
		memset(ans,0,sizeof(ans));
		memset(vis,0,sizeof(vis));
		memset(use,0,sizeof(use));
		int n;
		scanf("%s",ch+1);
		int loc=30;
		n=strlen(ch+1);
		string S;S.clear();		
		for(int i=1;i<=n;++i)vis[ch[i]-'a']=1;
		for(int i=0;i<26;++i)if(!vis[i])S+=char(i+'a');
		ans[loc]=ch[1];
		use[ch[1]-'a']=1;
		bool flag=0;
		for(int i=2;i<=n;++i){
			if(ch[i]==ans[loc])continue;
			else if(ans[loc-1]==ch[i]||ans[loc+1]==ch[i]){
				if(ans[loc-1]==ch[i])loc--;
					else loc++;
			}
			else if(use[ch[i]-'a']){flag=1;break;}
			else if(!ans[loc-1]){loc--;ans[loc]=ch[i];use[ch[i]-'a']=1;}
			else if(!ans[loc+1]){loc++;ans[loc]=ch[i];use[ch[i]-'a']=1;}
			else {flag=1;break;}
		}
		if(flag==1)puts("NO");
			else {
				puts("YES");
				for(int i=0;i<73;++i)
					if(ans[i])putchar(ans[i]);
				cout<<S<<endl;
			}
	//	for(int i=1;i<=n;++i)ch[i]=0;
	}
	return 0;
}
```


---

## 作者：Bai_R_X (赞：0)

## 思路
将相邻的两个字符映射为一条边，构成一张图。若有一个字符有超过两个的不同字符，那明显无解，因为最多的相邻数为 $2$。然后我们对任意相邻数小于 $2$ 的字符进行搜索，因为环无解，这样搜索只有环才可能有未访问过的字符，有未访问的也无解。每次搜索记录字符，最后输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,i,cnt[256];
bool vis[256],mp[256][256];
string s,ans;
void add(int u,int v)
{
	mp[u][v]=1;
}
void dfs(int u,int fa)
{
	if(vis[u])return ;
	ans.push_back(u);
	vis[u]=1;
	for(int i='a';i<='z';i++)
	{
		if(!mp[u][i]||i==fa)continue;
		dfs(i,u);
	} 
}
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>s;
		memset(cnt,0,sizeof(cnt));
		memset(vis,0,sizeof(vis));
		memset(mp,0,sizeof(mp));
		ans.clear();
		for(i=0;i<s.size()-1;i++)
		{
			if(mp[s[i]][s[i+1]])continue;
			add(s[i],s[i+1]);
			add(s[i+1],s[i]); 
			cnt[s[i]]++;
			cnt[s[i+1]]++;
			if(cnt[s[i]]>2||cnt[s[i+1]]>2)
			{
				cout<<"NO"<<endl;
				goto exit;
			}
		}
		for(i='a';i<='z';i++)
		{
			if(vis[i])continue;
			if(cnt[i]<2)dfs(i,0);
		}
		for(i='a';i<='z';i++)
		{
			if(!vis[i])
			{
				cout<<"NO"<<endl;
				goto exit;
			}
		}
		cout<<"YES"<<endl<<ans<<endl;
exit:
		;
	}
	return 0;
}
```

---

