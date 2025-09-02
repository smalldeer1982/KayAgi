# [ICPC 2020 Shanghai R] Gitignore

## 题目描述

你的 git 项目（你不需要熟悉 git 来解决这个问题）中有一些文件应该被忽略同步。你需要计算 .gitignore 文件中所需的最小行数。

形式上，你的项目是一个文件夹。一个文件夹可以包含文件和子文件夹。没有空文件夹（即没有任何文件或子文件夹的文件夹）。最初，git 软件会同步项目中的所有文件。然而，你可以在设置中指定一些文件和文件夹（即 .gitignore）来排除它们的同步。在 .gitignore 中的每一行，你可以指定一个文件或一个文件夹中的所有文件。你不能忽略整个项目文件夹（即 .gitignore 中的空行）。

你将得到项目中所有文件的路径，以及它们是否应该被忽略。你的任务是计算 .gitignore 的最小行数。

## 说明/提示

在第一个示例测试用例中，.gitignore 文件包含 2 行：一个文件夹行 `data/` 和一个文件名 `model`。

在第二个示例测试用例中，.gitignore 文件包含 3 行文件：`data/train`、`data/test` 和 `model`。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
3 0
data/train
data/test
model
3 1
data/train
data/test
model
data/sample```

### 输出

```
2
3```

# 题解

## 作者：BetterGodPig (赞：3)

一道比较有思维的模拟题，首先贪心地考虑，如果一个文件夹可以直接整个删除，那么就没必要把里面的子文件一个一个删除。

那么可以考虑使用 `map` 将所有不能被删的标记出来，再依次将每个串从外层到内层处理，如果可以删就直接删去，并且打上打上标记避免重复删。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n,m;
const int maxn = 105;
string s[maxn];
map<string,int> mp,vis;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>T;
    while(T --> 0){
        mp.clear();vis.clear();
        cin>>n>>m;
        for(int i(1);i <= n;++i){
            cin>>s[i];//can be ignored
        }
        for(int i(1);i <= m;++i){
            string str,tmp = "";
            cin>>str; register int len = str.length();
            for(int j(0);j < len;++j){
                if(str[j] == '/'){
                    mp[tmp] = 1;
                }
                tmp += str[j];
            }
        }
        int ans = 0;
        for(int i(1);i <= n;++i){
            bool f = 1; string tmp = "";
            register int len = s[i].length();
            for(int j(0);j < len;++j){
                if(s[i][j] == '/'){
                    if(mp[tmp]) f = 1;
                    else{
                        if(vis[tmp]) f = 0;
                        vis[tmp] = 1;
                        break;
                    }
                }
                tmp += s[i][j];
            }
            ans += int(f);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：Storm_Lightning (赞：2)

## 思路

对于一个大文件夹，

- 一个大文件夹里的文件都要删除，则全部同步删除。

- 如果不行，则一个一个往下删。

### 数据结构

使用映射 map 即可！

## 代码

代码洛谷题解满天飞，就不粘了！！！

---

## 作者：UncleSam_Died (赞：2)

### 解题思路
显然，对于这些文件，我们可以考虑如果某一个文件夹内的所有文件都要删除，那么删除整个文件夹，否则的话，把其中需要删除的文件依次删除即可。

---

## 作者：chen_zhe (赞：2)

以下内容转载自官方题解：

当一个文件夹内（包括所有子文件夹内）所有文件都需要排除时，则可贪心地排除这个文件夹；否则单独排除直接位于这个文件夹内需要排除的文件，并递归求解子文件夹。

---

## 作者：zhaojiadong2022 (赞：2)

当一个文件夹内（包括所有子文件夹内）所有文件都需要排除时，则可贪心地排除这个文件夹；否则单独排除直接位于这个文件夹内需要排除的文件，并递归求解子文件夹。

也就是说：用  ```map```  和贪心特别容易做出此题。
```
#include <bits/stdc++.h>
using namespace std;
int T;
int n,m;
const int maxn = 105;
string s[maxn];
map<string,int> mp,vis;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>T;
    while(T --> 0){
        mp.clear();vis.clear();
        cin>>n>>m;
        for(int i(1);i <= n;++i){
            cin>>s[i];//can be ignored
        }
        for(int i(1);i <= m;++i){
            string str,tmp = "";
            cin>>str; register int len = str.length();
            for(int j(0);j < len;++j){
                if(str[j] == '/'){
                    mp[tmp] = 1;
                }
                tmp += str[j];
            }
        }
        int ans = 0;
        for(int i(1);i <= n;++i){
            bool f = 1; string tmp = "";
            register int len = s[i].length();
            for(int j(0);j < len;++j){
                if(s[i][j] == '/'){
                    if(mp[tmp]) f = 1;
                    else{
                        if(vis[tmp]) f = 0;
                        vis[tmp] = 1;
                        break;
                    }
                }
                tmp += s[i][j];
            }
            ans += int(f);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/135298672)

---

## 作者：DFM_O (赞：1)

## [P9831 题目](https://www.luogu.com.cn/problem/P9831)

### 解题思路
很明显是用贪心算法解决的题目。

如果一个文件夹内需要忽略所有文件时，我们就可以把这一整个文件夹整体忽略，否则将此文件夹里需要忽略的文件依次忽略。

用映射 `map` 解决即可。

### Code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
struct op
{
	string s;
}a[101];
signed main()
{
	int t;
    scanf("%d",&t);
    for(int ii=1;ii<=t;ii++)
	{
		int n,m,c=0,i=0;
        scanf("%d%d",&n,&m);
        int N=n;
        while(N--)
            cin>>a[++i].s;
        map<string,bool> mapp;
        while(m--)
		{
            string s1,s2="";
            cin>>s1;
            for(i=0;i<s1.size();i++)
			{
                if(s1[i]=='/')
                    mapp[s2]=true;
                s2+=s1[i];
            }
        }
        map<string,bool> v;
        i=0;
        while(n--)
		{
			i++;
			string s1="";
            bool pd=true;
            for(int j=0;j<a[i].s.size();j++)
			{
				int pd2=false;
                if(a[i].s[j]=='/')
				{
                    if(mapp[s1]==true)
						pd=true;
                    else
					{
                        if(v[s1])
							pd=false;
	                 	v[s1]=true;
                        pd2=true;
                    }
                    if(pd2)
                    	break;
                }
                s1+=a[i].s[j];
            }
            if(pd)
            	c++;
        }
        printf("%d\n",c);
    }
    return 0;
}
```

---

