# 数据库 Database

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4467

[PDF](https://uva.onlinejudge.org/external/15/p1592.pdf)

# 题解

## 作者：hsfzLZH1 (赞：12)

题目大意是给定一个字符串组成的矩阵，问能否找到这样的行$r1$，$r2$，这样的列$c1$，$c2$，使得$s[r1][c1]==s[r2][c1]$且$s[r1][c2]=s[r2][c2]$。

如果四重循环枚举$r1$，$r2$，$c1$，$c2$，时间复杂度$O(n^2*m^2)$，显然会超时。需要寻找时间复杂度更低的算法。

一个优化速度的方法是给每个字符串分配一个ID，用一个map存储并维护每个字符串的ID值，使得相同的字符串拥有相同的ID，在比较矩阵时只需比较对应的ID值是否相等即可。

如果只枚举列数：$c1$，$c2$，然后扫描各行，对于一行，将两列的内容加入一个map中，如果当前的内容和以前的一致（在map中出现过），那么对应的map值就是上一个和该行相同的行数（$r1$），该行就是$r2$，从而求得答案。时间复杂度$O(M^2*NlgN)$，在可以接受的范围内。只需注意map的清空。

如果需要将两个不超过x的值作为map的一个元素，我们可以使用STL中的
```cpp
pair<int,int>
```
，也可以转化为一个x+1进制数字，把两个数字合并成一个数字，分离时只需进行除法和取模操作。在本题中，注意合并成的数字可能超出int的范围，需要使用long long类型。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
int n,m,id,v[10010][11];//v存储矩阵位置中字符串对应的ID值
char ch;
bool tf;
string str;
map<string,int>mp;
map<ll,int>q;
int main()
{
    while(cin>>n>>m)
    {
        mp.clear();id=0;getchar();//在此处初始化
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
        {
            str.clear();
            while(1)
            {
                ch=getchar();
                if(ch==','||ch=='\n'||ch=='\r'||ch==EOF)break;
                str.push_back(ch);
            }
            if(mp.count(str))v[i][j]=mp[str];
            else v[i][j]=mp[str]=++id;
        }//输入
        id++;tf=false;
        for(int i=1;i<=m;i++)for(int j=1;j<i;j++)
        {
            q.clear();
            for(int k=1;k<=n&&!tf;k++)if(q.count((ll)v[k][i]*id+v[k][j]))
            {
                printf("NO\n");
                printf("%d %d\n%d %d\n",q[(ll)v[k][i]*id+v[k][j]],k,j,i);
                tf=true;
            }
            else q[(ll)v[k][i]*id+v[k][j]]=k;
            if(tf)break;
        }
        if(!tf)printf("YES\n");
    }
    return 0;
}
```

---

## 作者：swl3992 (赞：5)

看到这题，直接写一个四重循环枚举可以吗？

答案是否定的，会 TLE .

 可以只枚举 c1 和 c2 ，然后从上到下扫描各行。每次碰到一个新的行 r ,把 r,c1 和 r,c2 的内容作为一个二元组 ( pair ) 存到一个 map 中。
 
 如果 map 中已经存在这个二元组，该二元组映射到的就是所要求的 r1 ,而当前行就是 r2 .
 
那么，如何表示由 c1 , c2 两列组成的二元组？

直接用两个字符串拼成一个长字符串（中间用一个其他地方不可能出现的字符分隔）显然行不通，因为速度太慢。

方法是先做一个预处理——给所有字符串分配一个编号，则整个数据库中每个单元格都变成了整数。

示例代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int cnt;	// cnt 储存当前编号
map<string,int> id;	//编号 map ,用来储存是否有过
int sheet[10005][15];	//表格数组
int ID(string s)	//分配 id
{
    if(!id.count(s))	//没有找到
    {
        id[s]=++cnt;	//分配
    }
    return id[s];
}
void solve()
{
    for(int c1=0;c1<m;c1++)
    {
        for(int c2=c1+1;c2<m;c2++)	//枚举 c1 , c2 
        {
            map<pair<int,int>,int> mp;	//判断是否存在的 map 
            for(int i=0;i<n;i++)
            {
                pair<int,int> p=make_pair(sheet[i][c1],sheet[i][c2]);	//将内容存为二元组
                if(mp.count(p))	//有过
                {
                    cout<<"NO"<<endl;	//注意此处是 NO 而不是 YES
                    cout<<mp[p]+1<<" "<<i+1<<endl;
                    cout<<c1+1<<" "<<c2+1<<endl;	//输出答案
                    return;
                }
                mp[p]=i;	//映射
            }
        }
    }
    cout<<"YES"<<endl;
}
int main()
{
    string s;
    while(getline(cin,s))
    {
        stringstream sin(s);	//字符串流
        if(!(sin>>n>>m))	//判断的同时也读入了 n 和 m
        {
            break;
        }
        cnt=0;
        id.clear();	//清空编号
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m-1;j++)
            {
                getline(cin,s,',');	//遇到逗号就停止
                sheet[i][j]=ID(s);	//取id
            }
            getline(cin,s,'\n');	//注意每行最后一个是 换行符而不是逗号
            sheet[i][m-1]=ID(s);
        }
        solve();
    }
    return 0;
}
```



---

## 作者：chino123 (赞：4)

这道题先预处理把每个字符串转化为数字再进行匹配运算能提高不少速度。

然后以列数为基准 枚举行数就能做到把答案筛选出来，只需要注意把容器初始化。

以下是代码：

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
int cnt=0,n,m,database[10002][11];
map<string,int>kafuu;
map<P,int>ans;
inline int id(string s){
	if(!kafuu.count(s))	kafuu[s]=++cnt;
	return kafuu[s];
}
int main(){
	while(cin>>n>>m){
		kafuu.clear(),cnt=0;getchar();
		for(int i=1;i<=n;i++){
			string s;
			for(int j=1;j<=m-1;j++){
				getline(cin,s,',');
				database[i][j]=id(s);
			}
			getline(cin,s,'\n');
			database[i][m]=id(s);
		}
		for(int j=1;j<=m-1;j++){
			for(int k=j+1;k<=m;k++){
				ans.clear();
				for(int t=1;t<=n;t++){
					if(ans.find(P(database[t][j],database[t][k]))!=ans.end()){
						puts("NO");
						cout<<ans[P(database[t][j],database[t][k])]<<" "<<t<<endl;
						cout<<j<<" "<<k<<endl;
						goto exit;
					}
					else ans[(P(database[t][j],database[t][k]))]=t;
				}
			}
		}
		puts("YES");
		exit:;
	}	
}
```

---

## 作者：Swiftie_wyc22 (赞：2)

这里有一个更直观的 `map` 的使用方法。

```cpp
map<pair<string,string>, tuple<int, int, int> >marks;
```

很直观，很好理解，也可以过。

这里的第一个 `pair` ，存储字符串对；第二个 `tuple`，记录字符串之前的行、列1、列2（两个字符串同一行，两个列）。

`tuple` 元组：其实就是 `pair` 的升级版，可以绑定多个元素，用 `tie()` 函数分解成各个变量。

接下来就是暴力枚举：先固定两个列，扫一遍各行，判重。这里就发现 我们的 `tuple` 其实可以优化，把三个元素变成只记录行就可以了，因为列已经固定了。


```cpp
#include <bits/stdc++.h>
#define rep(i, s, n, c) for (register int i = s; i <= n; i+=c)
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}

using namespace std;

map<pair<string, string>, tuple<int, int, int> > marks;
int n, m;
string mp[10005][15];

int main()
{
	while (~scanf("%d%d", &n, &m)) {getchar(); marks.clear();
		rep (i, 1, n, 1) {
			rep (j, 1, m - 1, 1) {
				getline(cin, mp[i][j], ',');
				
			}
			getline(cin, mp[i][m], '\n');
		}
		bool flag = true;
		
		rep (x1, 1, m, 1) {
			rep (x2, x1 + 1, m, 1) {
				if (x1 == x2) continue;
				marks.clear();
				rep (i, 1, n, 1) {
					
					pair<string, string> p = make_pair(mp[i][x1], mp[i][x2]);
					tuple<int, int, int> t = make_tuple(i, x1, x2);
					
					int r, c1, c2;
					tie(r, c1, c2) = marks[p];
					if (c1 == x1 && c2 == x2) {
						printf("NO\n");
						printf("%d %d\n%d %d\n", r, i, x1, x2);
						flag = false;
						break;
					}
					marks[p] = t;
				}
				if (!flag) break;
			}
			if (!flag) break;
		}
		if (!flag) continue;
		printf("YES\n");
	}
    return 0;
}
```


---

