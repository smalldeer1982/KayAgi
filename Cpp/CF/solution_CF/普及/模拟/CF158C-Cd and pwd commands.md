# Cd and pwd commands

## 题目描述

Vasya is writing an operating system shell, and it should have commands for working with directories. To begin with, he decided to go with just two commands: cd (change the current directory) and pwd (display the current directory).

Directories in Vasya's operating system form a traditional hierarchical tree structure. There is a single root directory, denoted by the slash character "/". Every other directory has a name — a non-empty string consisting of lowercase Latin letters. Each directory (except for the root) has a parent directory — the one that contains the given directory. It is denoted as "..".

The command cd takes a single parameter, which is a path in the file system. The command changes the current directory to the directory specified by the path. The path consists of the names of directories separated by slashes. The name of the directory can be "..", which means a step up to the parent directory. «..» can be used in any place of the path, maybe several times. If the path begins with a slash, it is considered to be an absolute path, that is, the directory changes to the specified one, starting from the root. If the parameter begins with a directory name (or ".."), it is considered to be a relative path, that is, the directory changes to the specified directory, starting from the current one.

The command pwd should display the absolute path to the current directory. This path must not contain "..".

Initially, the current directory is the root. All directories mentioned explicitly or passed indirectly within any command cd are considered to exist. It is guaranteed that there is no attempt of transition to the parent directory of the root directory.

## 样例 #1

### 输入

```
7
pwd
cd /home/vasya
pwd
cd ..
pwd
cd vasya/../petya
pwd
```

### 输出

```
/
/home/vasya/
/home/
/home/petya/
```

## 样例 #2

### 输入

```
4
cd /a/b
pwd
cd ../a/b
pwd
```

### 输出

```
/a/b/
/a/a/b/
```

# 题解

## 作者：Withershine (赞：3)

大模拟，但是有坑点。

## 思路
依照题意模拟。用一个字符串 $out$ 记录在进行了 $i$ 次操作后如果要输出输出的东西，字符串 $in$ 和 $s$ 来分别记录输入的操作及操作类型。

由于输出的第一个字符一定是 `/`，所以可以直接将 $out$ 的初始化定为 `out = "/"`。这样子可以省去很多麻烦。又因为输出的最后一个字符也一定是 `/`，而输入的字符串 $in$ 最后一定不带 `/`，所以可以直接在后面加上一个 `/`，像 `in = in + '/'` 这样。

当然，要特判绝对路径的情况，这个时候的 $in$ 的第一个字符就是 `/`，没必要再加。**即使是绝对路径也会有删除操作，这里需要注意！！！**

遍历一遍输入的 $in$，用一个变量 $last$ 来记录对于当前`in[i] = '/'` 时的上一个 `/` 的位置。调用函数 `check(last , i)` 来操作。

传入的其实就是两个 `/` 的位置，每次都对这两个位置间的字符串进行操作。特判当长度为二时是否是删除操作，是的话就调用函数 `del()`。不是的话就将这一段加入到 $out$ 中，调用函数 `add(l , r)`，其中 $l$ 为上面的 $last$，$r$ 为上面的 $i$。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<stdio.h>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n;
string s , in , out;
inline void del()
{
    ll len_out = out.size();
    if(len_out == 1)
    {
        return ;
    }
    ll L = 0 , R = 0;
    fo(i , len_out - 1 , 0)
    {
        if(out[i] == '/' && R == 0)
        {
            R = i;
            continue;
        }
        if(out[i] == '/' && R != 0)
        {
            L = i;
            break;
        }
    }
    // printf("del : L = %lld R =  %lld\n" , L , R);
    out.erase(L + 1 , R);//从L + 1开始就不需要加回‘/’了
    // cout << "out = " << out << endl;
}
inline void add(ll L , ll R)
{
    string kkk;
    fr(i , L + 1 , R)
    {
        kkk += in[i];
    }
    out += kkk;
    // cout << "out = " << out << endl;
}
inline void check(ll l , ll r)
{
    if(r - l - 1 == 2)
    {
        if(in[l + 1] == '.' && in[r - 1] == '.')
        {
            del();
        }
        else
        {
            add(l , r);
        }
    }
    else
    {
        add(l , r);
    }
}
signed main()
{
    n  = read();
    out = "/";
    while(n--)
    {
        cin >> s;
        if(s == "pwd")
        {
            cout << out;
            puts("");
        }
        else if(s == "cd")
        {
            cin >> in;
            in = in + '/';
            if(in[0] == '/')
            {
                out = "/";
            }
            else
            {
                in = '/' + in;
            }
            ll len = in.size() , last = 0;
            fr(i , 0 , len - 1)
            {
                if(in[i] == '/')
                {
                    // cout << in;
                    // puts("");
                    // printf("check : l = %lld r =  %lld\n" , last , i);
                    check(last , i);
                    last = i;
                }
            }
        }
    }
    system("pause");
    return 0;
}
```
## 总结
其实模拟方法有很多，这个是最朴素的一种，一开始思路就这样想，没有优化就交了。

---

## 作者：JerryMao (赞：3)

传送门和题意 @IvanZhang2009 已经讲过了,我就不在讲了。

这题其实还可以用 `stl` 做，用 `vector<string>` 记录每一层文件夹，把读入里面每两个 `/` 之间的内容分离开，然后压进 `vector<string>` 里，输出的时候把这里面的输出就好了，输出的时候再加 `/`。

sb的我一开始 `cd` 忘记清空 vector 了，WA 了两发。

代码
```cpp
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin>>n;
	while(n--){
		string op;
		cin>>op;
		if(op=="cd"){
			string s;
			cin>>s;
			if(s[0]=='/') v.clear();
			s+='/';
			if(s[0]=='/') s.erase(s.begin());
			int i=0,j=0;
			for(i=0;i<s.size();i++){
				string t="";
				for(j=i;j<s.size();j++){
					if(s[j]=='/') break;
					t+=s[j];
				}
				if(t=="..") v.pop_back();
				else v.push_back(t);
				i=j;
			}
		}
		if(op=="pwd"){
			cout<<'/';
			rep(i,v.size()){
				cout<<v[i]<<'/';
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：IvanZhang2009 (赞：2)

传送门 [洛谷](https://www.luogu.com.cn/problem/CF158C) [cf](http://codeforces.com/problemset/problem/158/C)
### 题外话
《关于我没看见“路径有相对路径和绝对路径”而认为加上 ``/`` 是本题的难点之一这件事》
## 题意
你需要实现类似 $\texttt{Unix}$ / $\texttt{Linux}$ 下的 $\texttt{cd}$ 和 $\texttt{pwd}$ 命令。

一开始，用户处于根目录 ``/`` 下。

对于 $\texttt{cd}$ 命令，它的作用是跳转到某个路径。路径有相对路径和绝对路径，相对路径以文件夹名开头，表示当前目录下的文件夹，绝对路径以 ``/`` 开头，表示根目录下的文件夹。同时，``..`` 文件夹表示上一层文件夹。

对于 $\texttt{pwd}$ 命令，你需要输出当前所在的绝对路径。

保证输入数据中所有的文件夹都存在。

## 解法
这是一道明摆着的模拟题。考虑用一个字符串 ``s`` 来存储当前文件夹。

每次输入分两种情况：

1、$\texttt{pwd}$：直接输出当前的 ``s`` 加上一个 ``/``。

2、$\texttt{cd}$：依次循环找出每一组开头为 ``/`` 的字符串，如果是 ``/..`` ，则通过一个函数来回到上一个文件夹，否则将这个字符串加到 ``s`` 后面。需要注意的是 $\texttt{cd}$ 后输入的路径是相对路径还是绝对路径（本蒟蒻跌在此坑）。

## 代码
代码主要部分：
```cpp
int n;
string s;
void del(){  //回到上一个文件夹
	if(!s.size())return;
	int x=s.size();
	while(x>0&&s[x]!='/')x--;
	s=s.substr(0,x);
}
void Main() {
	string t;
	cin>>t;
	if(t=="pwd")cout<<s<<'/'<<endl;  //分类讨论
	else{
		cin>>t;
		if(t[0]!='/')t='/'+t;
		else s="";  //绝对路径，将原字符串清空
		if(t[t.size()-1]!='/')t+="/";  //末尾加上/，防止漏算
		string st="/";
		for(int i=1;i<(int)t.size();i++){
			if(t[i]=='/'){  //分离出每一个小路径
				if(st=="/..")del();  //判断是否是返回
				else s+=st;
				st="";
			}
			st+=t[i];
		}
	}
}
void TC() {
	ull t = 1;
	cin>>t;
	while ( t-- ) {
		Main();
	}
}
```

---

## 作者：qingchenMC (赞：0)

## 思路

按题意模拟即可。

建立一个字符串 `curlj` 用于存储当前路径。

输入一个操作，如果是 `cwd` 就输出当前路径字符串。

如果是 `cd`，读入操作字符串。

如果操作字符串第一个字符是 `/`，也就是说这是一个绝对路径，那么清空当前路径，并将这个斜杠删掉。

在操作字符串的最后一位加上斜杠，方便处理。

从左到右遍历操作字符串，用一个变量记录斜杠上一次出现的坐标。如果遇到斜杠，就把这个变量坐标开始，到现在坐标的这一段字符串截取下来，执行对应操作。如果是文件名就在当前路径后面添加上，如果是 `..` 就在当前路径从后往前找一个斜杠，删掉他后面的内容。注意要在当前路径最后面补上斜杠。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

string curlj="/";

int main(){
	int T;
	cin>>T;
	while(T--){
		string op;
		cin>>op;
		if(op=="pwd"){
			if(curlj[curlj.size()-1]!='/'){
				curlj+='/';
			}
			cout<<curlj<<endl;
		}
		else{
			string opt;
			cin>>opt;
				if(opt[0]=='/'){
					curlj="/";
					string optt;
					for(int i=1;i<opt.size();i++){
						optt+=opt[i];
					}
					opt=optt;
				}
				opt+='/';
				int poss=0;
				for(int i=0;i<opt.size();i++){
					if(opt[i]=='/'){
						string tmp;
						for(int j=poss;j<i;j++){
							tmp+=opt[j];
						}
						poss=i+1;
						if(tmp==".."){
							int pos;
							for(int k=curlj.size()-2;k>=0;k--){
								if(curlj[k]=='/'){
									pos=k-1;
									break;
								}
							}
							string tmp;
							for(int k=0;k<=pos;k++){
								tmp+=curlj[k];
							}
							tmp+='/';
							curlj=tmp;
						}
						else{
							curlj+=tmp;
							curlj+='/';
						}
					}
				}
		}
	}
	return 0;
}
//https://codeforces.com/contest/158/submission/304403206
```

---

## 作者：nxd_oxm (赞：0)

# 题意
题目说给我们一串命令，让我们模拟终端，输出对应的输出。

命令如下：
- cd

	- 后面会给一串地址，表示将要去到的地址。
    
   - 我们定义 ``/`` 为根目录。
   
   - 地址分为绝对路径和相对路径。绝对路径是以 ``/`` 开头的一串地址，表示直接回到根目录，也就是就到达这串地址。相对路径是直接以文件夹名开头的地址，表示在当前文件夹下继续打开。
   
   - 在地址中，``..`` 表示回到上一级。
   
   - 题目不会给不存在的地址，比如在根文件夹下再回到上一级。
   
- pwd

   - 输出当前所在地址（记得前面加上根目录 ``/``）。

## 样例解释：

### 样例输入 #1

```
7
pwd
cd /home/vasya
pwd
cd ..
pwd
cd vasya/../petya
pwd
```

### 样例输出 #1

```
/
/home/vasya/
/home/
/home/petya/
```

**分析**

``pwd``：输出当前目录，也就是根目录 ``/``。

``cd /home/vasya``：注意是绝对路径，所以直接来到 ``/home/vasya/``。

``pwd``：输出当前目录。

``cd ..``：回到上一级，也就是 ``/home/``。

``pwd``：输出当前目录。

``cd vasya/../petya``：比较复杂，首先观察到是相对路径，所以来到当前文件夹下 ``vasya``。然后再回到上一级，所以又回到了 ``home``。最后来到 ``petya``，所以最后停留在 ``/home/petya/``。

``pwd``：输出当前目录。

# 思路
模拟。

首先这里关于 ``cd`` 命令的只有三种情况:

- 继续向下。
- 回到上一级。
- 回到根目录。

根据只需要回到上一级或清空，很容易想到用栈。

这里需要手动栈可能好一点，因为要输出整个栈，用STL的话不好输出。

那就用栈存储每一级目录，首先判断是绝对路径还是相对路径，绝对路径的话就先清空栈。然后依次往后读取，用 ``/`` 分割每一层路径，遇到 ``..`` 就出栈，最后遇到 ``pwd`` 时，输出整个栈即可。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
string s[10001];
int n,top=0;
void pushs(string x){
	s[++top]=x; 
}
string tops(){
	return s[top];
}
void pops(){
	if(top>0){
		top--;
	}
}
signed main(){
	cin>>n;
	f(p,1,n){
		string f;
		cin>>f;
		if(f=="pwd"){
			cout<<"/";
			f(i,1,top){
				cout<<s[i]<<"/";
			}
			cout<<endl;
		}else{
			string add;
			cin>>add;
			if(add[0]=='/'){//绝对路径
				top=0;
				string nows="";
				bool have=0;
				f(i,1,add.size()-1){
					if(add[i]!='/'){
						have=1;
						nows+=add[i];
					}else{
						if(nows==".."){
							pops();
							nows="";
							continue;
						}
						pushs(nows);
						nows="";
					}
				}
				if(have){
					if(nows==".."){
						pops();
						continue;
					}
					pushs(nows);
				}
			}else{//相对路径
				string nows="";
				bool have=0;
				f(i,0,add.size()-1){
					if(add[i]!='/'){
						have=1;
						nows+=add[i];
					}else{
						if(nows==".."){
							pops();
							nows="";
							continue;
						}
						pushs(nows);
						nows="";
					}
				}
				if(have){
					if(nows==".."){
						pops();
						continue;
					}
					pushs(nows);
				}
			}
		}
	} 
	return 0;
}

```

---

## 作者：andyli (赞：0)

记录一个字符串数组 $a$ 存储当前路径，对于 `cd` 命令，使用 `split('/')` 分割并依次处理每一部分，遇到 `..` 就删除 $a$ 的末尾元素，否则将目录名添加到 $a$ 的末尾。注意如果使用绝对路径表示应当先清空 $a$。  

```python
a = []
for _ in range(int(input())):
    s = input().split(' ')
    if len(s) == 1:
        for s in a:
            print(f'/{s}', end='')
        print('/')
    else:
        s = s[1]
        if s[0] == '/': # 绝对路径
            a = []
            s = s[1:]
        for t in s.split('/'):
            if t == '..':
                a.pop()
            else:
                a += t,
```

---

