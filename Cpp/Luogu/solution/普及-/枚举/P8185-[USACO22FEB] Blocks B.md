# [USACO22FEB] Blocks B

## 题目描述

为了提高词汇量，母牛贝西得到了一套四块木块，其中每块都是一个立方体，六面各写着一个字母。她正在通过将木块排成一排使得木块顶部的字母拼出单词来学习拼写。

给定 Bessie 的四个木块上的字母，以及她想拼写的单词列表，请确定列表中哪些单词可被她使用木块成功拼写。

## 样例 #1

### 输入

```
6
MOOOOO
OOOOOO
ABCDEF
UVWXYZ
COW
MOO
ZOO
MOVE
CODE
FARM```

### 输出

```
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：Ginger_he (赞：12)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/15966096.html)
# 题目描述
已知 $4$ 个长度为 $6$ 的字符串，每次给定一个字符串 $s$，现在可以从每个已知的字符串中选 $0$ 或 $1$ 个字母，问是否能组成 $s$。
# 题解
对于每次询问，我们用一个桶 $a$ 记录下 $s$ 中 $26$ 个出现的次数。然后 `dfs` 枚举从每个字符串中选出哪个字母，也用一个桶 $b$ 记录下出现的次数。若 $\displaystyle\sum_{i=1}^{26}[b_i\ge a_i]=26$，则输出 `YES`；否则输出 `NO`。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[30],b[30];
bool flag;
char s[5][10],t[5];
void dfs(int x)
{
	if(flag)
		return;
	if(x==5)
	{
		for(int i=1;i<=26;i++)
		{
			if(a[i]>b[i])
				return;
		}
		flag=1;
		return;
	}
	for(int i=1;i<=6;i++)
	{
		b[s[x][i]-'A'+1]++;
		dfs(x+1);
		b[s[x][i]-'A'+1]--;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=4;i++)
		scanf("\n%s",s[i]+1);
	for(int i=1;i<=n;i++)
	{
		memset(a,flag=0,sizeof(a));
		scanf("\n%s",t+1);
		for(int j=1;t[j];j++)
			a[t[j]-'A'+1]++;
		dfs(1);
		printf("%s\n",flag?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：苏联小渣 (赞：5)

这道题所有数字的范围很小，考虑直接爆搜。只有 $4$ 个正方体，每个正方体都有 $6$ 个面，所以我们可以一一枚举全排列。首先是对于 $4$ 个正方体的全排列，然后在这四个正方体里面又分别任意选一个字母。注意到单词长度可能为 $1,2,3,4$，所以我们搜索到每一层时都要判断目前组成单词与答案单词是否相符即可。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, jud, vis[8];
char a[8], b[8], c[8], d[8];
void dfs(int k, string st, string s2){
	if (st == s2) jud = 1;
	for (int i=1; i<=4; i++){
		if (!vis[i]){
			vis[i] = 1;
			for (int j=1; j<=6; j++){
				if (i == 1) dfs(k+1, st+a[j], s2);
				if (i == 2) dfs(k+1, st+b[j], s2);
				if (i == 3) dfs(k+1, st+c[j], s2);
				if (i == 4) dfs(k+1, st+d[j], s2);
			}
			vis[i] = 0;
		}
	}
}
int main(){
	scanf ("%d", &n);
	scanf ("%s%s%s%s", a+1, b+1, c+1, d+1);
	for (int i=1; i<=n; i++){
		memset(vis, 0, sizeof(vis));
		string s;
		cin >> s;
		jud = 0;
		dfs(0, "", s);
		if (jud == 1) puts ("YES");
		else puts ("NO");
	}
	return 0;
}

```

---

## 作者：Jorisy (赞：2)

一道暴力搜索。

比较类似于排列组合，用 $f_i$ 表示 $a_i$ 是否取过。

每次要么取，要么不取。

最后判断每次的结果只要有一个是 `true`，那结果必定是 `true`。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

string a[15],s;
bool f[15],ans;

void dfs(int dep,int x)
{
	if(dep==s.size())
	{
		//cout<<s<<' '<<x<<endl;
		ans|=(s.size()==x);//处理结果
		return;
	}
	for(int i=1;i<=4;i++)
	{
		if(f[i]) continue;
		if(a[i].find(s[x])!=string::npos)//能在 a[i] 里找到 s[x]
		{
			f[i]=1;
			dfs(dep+1,x+1);//往下搜
			f[i]=0;//回溯
		}
		dfs(dep+1,x);//不取
	}
}

int main()
{
	int n;
	cin>>n>>a[1]>>a[2]>>a[3]>>a[4];
	while(n--)
	{
		cin>>s;
		dfs(0,0);
		puts(ans?"YES":"NO");
		ans=0;
		memset(f,0,sizeof(f));//初始化
	}
 	return 0;
}
```

---

## 作者：oddy (赞：2)

## Description

给定 $4$ 个可重集，每个集里有 $6$ 个字符。现给定 $n$ 个长度不大于 $4$ 的字符串，问能否用这 $4$ 个集里（每个集至多用一个字符）的字符拼出这些字符串。

## Analysis

这道题考察了 DFS 的应用。选手需要巧妙地利用递归函数的返回值。

Tips：在用 `std::string` 的时候要注意，如果往一个 `std::string` 对象尾部加单字符要用 `push_back` 方法（而非 `+=` 运算符），因为 `push_back` 是 $\mathcal{O}(1)$ 的，而 `+=` 是 $\mathcal{O}(n)$ 的。

## Code

```cpp
#include <iostream>
#include <string>

int n;
std::string s[5], t, str;
bool vis[5];

bool dfs(int k) {
    if(k > t.size())                                              // 枚举完了，看看这次枚举的字符串和目标字符串是不是相同
        return str == t;
    for(int i = 1; i <= 4; i++) if(!vis[i]) for(auto ch : s[i]) { // 遍历每个可用集的每一个字符
        str.push_back(ch);
        vis[i] = true;
        if(dfs(k+1)) return true;                                 // 如果这个分支里有可行解，就返回真
        str.pop_back();
        vis[i] = false;
    }
    return false;                                                 // 一个可行解都没有，只好返回假
}

int main() {
    std::cin >> n;
    for(int i = 1; i <= 4; i++)
        std::cin >> s[i];
    while(n--) {
        str.clear();                                              // 每次计算前要先把枚举用的字符串和标记数组清零
        for(int i = 1; i <= 4; i++) vis[i] = false;
        std::cin >> t;
        puts(dfs(1) ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：junxis (赞：1)

# 1.题意化简
[题目传送门](https://www.luogu.com.cn/problem/P8185)

给定四个字符集，每个集合有六个字符， $n$ 次询问，每次询问给出一个字符串，请你回答：选出字符串长度个字符集中的每个里挑出一个字符，将这些字符组合后能否组成给定的字符串。

# 2.分析

由于单词长度和询问字符串长度都很小，我们直接暴力判断即可。

具体地，我们用 $exist(i,j)$ 表示第 $i$ 个字符集中是否含有字符 $j$ 。

用深搜判枚举字符串长度下所有字符集编号的排列，检查排列是否合法即可。

代码难度对于刚入门的 OIer 来说稍高。

详情见代码。

# 3.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,tmp[5];//tmp[j]存储当前询问字符串的第j位匹配第几个字符集 
char block[5][6];//字符集 
string q;//询问字符串 
bool exist[5][30],flag=0,used[5];
bool checkit()
{
	for(int i=1;i<=len;i++)
			if(!exist[tmp[i]][q[i-1]-'A'+1]) return 0;//一旦这一位的字符不在所匹配的字符集中存在，立即失败 
	return 1;
}
void dfs(int dep)//当前待匹配的是第几位 
{
	if(flag)return ;//如果已经成功，无需继续 
	if(dep>len)//询问字符串的len位全部匹配完 
	{
		if(checkit()) flag=1;//若检查发现匹配成功，将flag更新 
		return ;
	}
	for(int i=1;i<=4;i++)
	{
		if(!used[i])//如果这个字符集还没被匹配 
		{
			used[i]=1;//标记 
			tmp[dep]=i;//将第dep位的匹配字符集编号设为i 
			dfs(dep+1);//继续搜索 
			used[i]=0;//回溯时重置 
		}
	}
}
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=4;i++) scanf("%s",block[i]);
    for(int i=1;i<=4;i++)
    	for(int j=0;j<6;j++)
    		exist[i][block[i][j]-'A'+1]=1;//预处理分析中的exist数组 
	while(n--)
	{
		memset(used,0,sizeof(used));//重置标记数组 
		cin>>q;
		len=q.length();//得出字符串长度 
		flag=0;//flag存储此时是否成功匹配 
		dfs(1);//深搜 
		if(flag==1) puts("YES");
		else puts("NO");
		/*判断+输出*/
	} 
    return 0;
}
```


---

## 作者：CANTORSORT (赞：1)

因为 ~~主角~~ Bessie 只有 **$4$ 块积木**，

并且每个积木上有 **$6$ 个字母**,

于是乎，

我们可以直接用 **深搜** 解决这一问题。

总共 $4$ 层的深搜树，

除最后一层外，

每个结点都有 $6$ 个儿子，

总共有 $6^1+6^2+6^3+6^4=1554$ 个结点，

可以通过。

## Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define tep(i,a,b) for(int i=a;i>=b;--i)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b)
#define isdight(c) (c>='0'&&c<='9')
using namespace std;
int n,len;
bool vis[5],flag;
string s[5],word;
template<class T>
inline T read()
{
	T x=0,f=1;
	char c=getchar();
	while(!isdight(c))
		f=(c^'-'?1:-1),c=getchar();
	while(isdight(c))
		x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
template<class T>
void write(T x)
{
	if(x<0)
		putchar('-'),x=-x;
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
void dfs(int now)
{
	if(now>=len)
	{
		flag=1;
		return;
	}
	rep(i,1,4)
	{
		if(vis[i])
			continue;
		rep(j,0,5)
		{
			if(s[i][j]==word[now])
			{
				vis[i]=1;
				dfs(now+1);
				vis[i]=0;
				break;
			}
		}
	}
}
signed main()
{
	n=read<int>();
	rep(i,1,4)
		cin>>s[i];
	while(n--)
	{
		flag=0;
		cin>>word;
		len=word.size();
		dfs(0);
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 题目意思
有 $4$ 个 $6$ 个面正方体，然后有 $n$ 组数据，每组需拼成长度为 $1 \leq |s_i| \leq 4$ 的单词，每个正方体只能用一次，毕竟也拆不开正方体，然后合理安排其中 $|s_i|$ 个正方体摆放顺序以及摆放的各个面然后看能不能拼出单词 $s_i$。

### 解题思路
数据小，直接暴力模拟。循环方式：$4$ 重循环表示 $4$ 个正方体顺序安排，最内层判断语句判断需要组成的 $s_i$ 长度，然后取前 $|s_i|$ 个正方体第 $j$ 个并看看每个有没有包含第 $s_{i_j}$ 个字符，一旦每个都包含，就可以输出 `YES` 了，$4$ 层循环都循环完了还没有就输出 `NO`。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
bool ifin(string a, char b) {
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == b) {
      return 1;
    }
  }
  return 0;
}
string h[5];
bool r(string l) {
  for (int a = 1; a <= 4; a++) {
    for (int b = 1; b <= 4; b++) {
      for (int c = 1; c <= 4; c++) {
        for (int d = 1; d <= 4; d++) {
          if (a == b || a == c || a == d || b == c || b == d || c == d) {
            continue;
          }
          string y = "";
          if (l.size() == 1) {
            if (ifin(h[a], l[0])) {
              return 1;
            }
          } else if (l.size() == 2) {
            if (ifin(h[a], l[0])) {
              if (ifin(h[b], l[1])) {
                return 1;
              }
            }
          } else if (l.size() == 3) {
            if (ifin(h[a], l[0])) {
              if (ifin(h[b], l[1])) {
                if (ifin(h[c], l[2])) {
                  return 1;
                }
              }
            }
          } else if (l.size() == 4) {
            if (ifin(h[a], l[0])) {
              if (ifin(h[b], l[1])) {
                if (ifin(h[c], l[2])) {
                  if (ifin(h[d], l[3])) {
                    return 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
string l;
int main() {
  cin >> n;
  for (int i = 1; i <= 4; i++) {
    cin >> h[i];
  }
  while (n--) {
    cin >> l;
    if (r(l)) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}
```

---

