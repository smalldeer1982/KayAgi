# Dictionary

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2012autumn/tasks/icpc2012autumn_a



# 题解

## 作者：RioFutaba (赞：1)

## 题意
给定 $n$ 个字符串，判断是否有一种字典序使得它们按这种字典序排序。当 $s$ 为 $t$ 的前缀时，$s$ 应当排在 $t$ 前面。
## 解法
如果 $s \le t$，要么 $s$ 是 $t$ 的前缀，或者有一个最小的 $i$，使得 $s_i < t_i$。  
用图论解决这个问题。  
找到这个 $i$，$s_i$ 向 $t_i$ 连一条边。由此构成一个有向图，$u$ 到 $v$ 有边代表 $u<v$。显然的，如果图中有环，那么环里的字母都大于且小于彼此，这样是无解的。

那么建完图之后暴力枚举从某个字母是否有一条路径能回到它自己，如果有则无解。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=5e2+5;
int n,e[26][26];
string a[maxn];
bool is,vis[26];
void fd(int fa,int u,bool o){//o是为了防止刚进去就被判到环
    if(u==fa && o){
        is=1;//找到环了
        return ;
    }
    for(int i=0;i<26;i++)
        if(!vis[i] && e[u][i]) 
            vis[i]=1,fd(fa,i,1);//往前走
}
bool solve(){
	memset(e,0,sizeof(e));
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){
        string s=a[i],t=a[i+1];
        bool f=1;
        for(int i=0;i<min((int)s.length(),(int)t.length());i++)
            if(s[i]!=t[i]){
            	e[s[i]-'a'][t[i]-'a']=1,f=0;//加边
            	break;
            }
        if(f && s.length()>t.length()) return 0;//s不等于t且t是s前缀
    }
    for(int i=0;i<26;i++){
        is=0;
        memset(vis,0,sizeof(vis));
        fd(i,i,0);
        if(is) return 0;
    }
    return 1;
}
int main(){
    while(scanf("%d",&n)){
    	if(!n) break;
    	if(solve()) puts("yes");
    	else puts("no");
    }
    return 0;
}
```

---

## 作者：__Hacheylight__ (赞：1)


题意：给你n个字符串，让你判断这些单词是否属于一种顺序（自行定义）

这一看就是一道拓扑排序裸题，但我们今天要讲一讲别的算法

解析：

先读入，判断Si]和S[i+1]在哪里不相同，
我们那Sample Input 1 的第一个举例
```cpp
4
cba
cab
b
a
```

a数组表示i字符在字典中是排在j之前（1）还是之后（0）

初始都为0

首先判断S[1]和S[2]，在第2位不同，a['b']['a']=1
判断S[2]和S[3]，第1位不同，a['c']['a']=1
同理 a['b]['a']=1



之后跑floyd。

如果 a[i][i]=1,即出现环 out "no" 
else out "yes” ;

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n;
string s[505];
bool f[30][30];
bool fulfill(string a,string b)
{
	int mn=min(a.size(),b.size());
	for (int i=0;i<mn;++i) if (a[i]!=b[i]) return f[a[i]-'a'][b[i]-'a']=true;
	if (a.size()>b.size()) return false;
	return true;
}
int main()
{
	while (cin>>n && n)
	{
		memset(f,0,sizeof(f));
		for (int i=0;i<n;++i) cin>>s[i];
		for (int i=0;i<n-1;++i)
		{
			if (!fulfill(s[i],s[i+1]))
			{
				cout<<"no\n";
				goto ends;
			}
		}
		for (int k=0;k<30;++k) for (int i=0;i<30;++i) for (int j=0;j<30;++j) f[i][j]=f[i][j]|(f[i][k]&f[k][j]);
		for (int i=0;i<30;++i) for (int j=0;j<30;++j) if (f[i][j] && f[j][i])
		{
			cout<<"no\n";
			goto ends;
		}
		cout<<"yes\n";
		ends:;
	}
	return 0;
}

```

---

## 作者：Jeremiahy (赞：0)

## 题意

给定 $n$ 个单词，判断是否属于某种词典序，给定的单词在词典上是从前往后的顺序，需要注意的是，一个单词的前缀应出现在这个单词之前。

# 分析

这是一道裸的拓扑排序题。

具体操作如下：

1. 设 $string_1$ 排在 $string_2$ 之前，那么扫描这两个单词，第一处不一样的地方（设下标为 $j$），就从 $string_{1,j}$ 向 $string_{2,j}$ 连一条有向边，表示大于关系；如果 $string_2$ 是 $string_1$ 的前缀，就判断输出 ```no```。

1. 在上述遍历过程中，统计出来图中顶点的数量。

1. 然后进行拓扑排序，如果 $A$ 序列的长度小于图中点的数量，就输出 ```no```，否则输出 ```yes```。

另外，有一个坑点是，如果发现某个单词的前缀排在它之后了，不要立刻 ```break```，要把本组数据输入完。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int ver[100005], nxt[100005], head[100005], tot, deg[100005], cnt, n, a[100005];//建图必备变量及题目变量
int have[28], is, num;//have记录是否存在这个顶点（用来统计点的数量），is判断是否存在某个单词的前缀在它后面，num记录顶点数
string s[505];

void add(int x, int y) {
	ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
	deg[y]++;
}

void topsort() {
	queue<int> q;
	for (register int i = 1; i <= 27; i++)
		if (deg[i] == 0 && have[i])
			q.push(i);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		a[++cnt] = x;
		for (register int i = head[x]; i; i = nxt[i]) {
			int y = ver[i];
			if (--deg[y] == 0)
				q.push(y);
		}
	}
}

signed main() {
    while (cin >> n && n) {
    	is = 0, tot = 0, cnt = 0, num = 0;//初始化
    	memset(have, 0, sizeof(have));
    	memset(ver, 0, sizeof(ver));
    	memset(head, 0, sizeof(head));
    	memset(deg, 0, sizeof(deg));
    	memset(nxt, 0, sizeof(nxt));
		for (register int i = 1; i <= n; i++) {
			cin >> s[i];
			if (i != 1) {
				bool flag = 0;//记录是否存在不一样的地方
				for (register int j = 0; j < min(s[i].length(), s[i - 1].length()); j++)
					if (s[i][j] != s[i - 1][j]) {
						flag = 1;
						have[s[i - 1][j] - 'a' + 1] = have[s[i][j] - 'a' + 1] = 1;
						add(s[i - 1][j] - 'a' + 1, s[i][j] - 'a' + 1);
						break;
					}
				if (!flag && s[i].length() < s[i - 1].length())//某单词前缀排在它之后了
					is = 1;
			}
		}
		if (is) {
			puts("no");
			continue;
		}	
		topsort();
		for (register int i = 1; i <= 27; i++)//统计顶点数
			if (have[i])
				num++;
		if (cnt < num)
			puts("no");
		else
			puts("yes");
	}
    return 0;
}
```


---

