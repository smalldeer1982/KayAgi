# [CERC2017] Hidden Hierarchy

## 题目描述

假设你正在开发一个简单的以输入文字为基础的文件夹浏览器。你的工作之一就是要构建一个导航目录来显示这些文件夹的上下关系。通常而言，这些文件夹很可能是互相嵌套的——比如，某个文件夹下还有一个文件夹，当然也可能会包含某些文件。因此，这些文件夹会形成一种树状结构。在这个目录中，最顶端的那个文件夹称之为根目录。如果文件夹d中直接含有文件夹e，那么我们称之为文件夹d是文件夹e的父文件夹，而文件夹e是文件夹d的子文件夹。每个文件都有一个用字节数来表示的大小。一个文件夹的大小是被直接或不直接包含于其中的所有文件的大小之和。

所有的文件和文件夹（除根目录外）都有一个名字——一个只由小写字符和点（“."）组成并且只由小写字母开头的字符串。包含于同一个父目录下的文件或文件夹的名字必定各不相同。而且，路径与文件是一一对应的。生成路径的规则如下：

- 根目录路径是“/”
- 文件夹d的路径是从根目录开始，沿着文件夹的父子关系，顺次往下，在每个文件夹名字前添加一个“/”，相互连接，并在路径的最末尾添加一个“/”。
- 文件f的路径是由它的父文件夹的路径加上文件名得到的。

通过打印根目录，我们能够显示文件夹的上下父子关系。打印文件夹d时，我们输出一个“md pd sd”形式的字符串。其中，pd是文件夹d的路径，sd是文件夹d的大小，md是文件夹d的扩展标记。如果文件夹d包含其他文件夹，我们可以选择是否展开它。如果我们要展开文件夹d，我们就要以字典序打印它里面包含的所有文件和文件夹。如果我们不打开文件夹d，那么我们就可以忽略其中的内容。

如果d是一个空文件夹（即没有包含任何文件或文件夹），那么md就仅仅是一个空字符。当我们要展开这个文件夹的时候，md是一个“-”，而如果我们不展开这个文件夹的是md是一个“+”。

现在，输入一列文件和一个限制性整数t。请你打印（按照前述展开打印方法）所有的大小不小于t的文件夹。并且，打印的文件夹总数一定是最小的。保证不存在空文件夹即整个文件夹上下关系都可从输入的文件路径中推断得出。注意，大小不小于t的文件夹必须要被打印，但不一定要展开。根目录不论多大都要被打印。

## 样例 #1

### 输入

```
9
/sys/kernel/notes 100
/cerc/problems/a/testdata/in 1000000
/cerc/problems/a/testdata/out 8
/cerc/problems/a/luka.cc 500
/cerc/problems/a/zuza.cc 5000
/cerc/problems/b/testdata/in 15
/cerc/problems/b/testdata/out 4
/cerc/problems/b/kale.cc 100
/cerc/documents/rules.pdf 4000
10000```

### 输出

```
- / 1009727
- /cerc/ 1009627
/cerc/documents/ 4000
- /cerc/problems/ 1005627
- /cerc/problems/a/ 1005508
/cerc/problems/a/testdata/ 1000008
+ /cerc/problems/b/ 119
+ /sys/ 100
```

## 样例 #2

### 输入

```
8
/b/test/in.a 100
/b/test/in.b 1
/c/test/in.a 100
/c/test/in.b 1
/c/test/pic/in.a.svg 10
/c/test/pic/in.b.svg 10
/a/test/in.a 99
/a/test/in.b 1
101
```

### 输出

```
- / 322
+ /a/ 100
- /b/ 101
/b/test/ 101
- /c/ 121
+ /c/test/ 121```

## 样例 #3

### 输入

```
2
/a/a/a 100
/b.txt 99
200
```

### 输出

```
+ / 199
```

# 题解

## 作者：loceaner (赞：9)

挺长时间不见，这个题竟然变成普及/提高-了？



# [题意]

这个题大概意思是linux目录，n条记录，每条记录代表一个目录下有个大小为val文件
 
然后根目录为“/”；

现在给个t问对于这个目录下的所有文件大小

如果大于t那么“-”展开，

如果小于t那么“+"折叠

如果是底层目录了，那么输出""一个空格，

后面都要跟着目录信息，和目录的大小；

如果是”-“，则进入到子目录中循环操作，目录按字典序输出

# [思路]
就是模拟了，节点存储用map容器里面价格set

考虑到超时问题，一律用scanf不用cincout，string转化char输出

string调用”.c_str“函数

把串截开，用charss[i+1]赋值0s就是i+1前面的内容；

目录就是一颗数，dfs遍历下去把文件大小计算出来

然后第二次dfs输出

```cpp

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2e5+7;

map<string,set<string> >mp;
map<string,ll> mp_size;
ll t;
void dfs1(string str) {
	for(auto next_str:mp[str]) {
		dfs1(next_str);
		mp_size[str]+=mp_size[next_str];
	}
}
void dfs2(string str) {
	if(mp[str].size()==0) {
		printf("  %s %lld\n",str.c_str(),mp_size[str]);// 空
		return ;
	}
	bool flag=true;
	for( auto next_str: mp[str]) // 循环遍历当前目录下的所有目录 看是不是存在子目录 >t
		if(mp_size[next_str]>=t)
			flag=false;
	if(flag) { // 没有 直接输出 +
		printf("+ %s %lld\n",str.c_str(),mp_size[str]);
	} else { // 又有的话 下一层
		printf("- %s %lld\n",str.c_str(),mp_size[str]);
		for(auto next_str:mp[str])
			dfs2(next_str);
	}
}
int main() {
	int n;
	scanf("%d",&n);
	mp_size.clear();
	for(int i=1; i<=n; i++) {
		char s[MAXN];
		ll val;
		scanf("%s%lld",s,&val);
		string fa="//";
		for(int i=0; s[i]; i++) {
			if(s[i]=='/') {
				char temp=s[i+1];
				s[i+1]=0;
				mp[fa].insert(s);
				fa=s;
				s[i+1]=temp;
			}
		}
		mp_size[fa]+=val;
	}
	scanf("%lld",&t);
	dfs1("//");
	dfs2( *(mp["//"].begin()) );
	return 0;
}
```


---

## 作者：xxxalq (赞：0)

# 题意简述：

给你一个文件夹，让你输出每一个内存大于等于 $t$ 的子文件夹和文件。

# 思路分析：

一道模拟题，由每一个文件的唯一路径可以推出，用一个 map 存储路径和对应的文件大小，用另一个 map 存储每一个文件夹的子文件夹和子文件。这样整个文件夹就成了一棵树，dfs 从根节点搜索，如果有儿子节点就继续搜索，没有就输出。

# 代码（注释详解）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,t,s;
string a;
map<string,ll>mem;//存储每个节点所占内存 
map<string,set<string> >son;//存储每个节点的儿子节点 
void dfs(string str){//dfs
	if(son[str].empty()){//没有儿子节点 
		cout<<str<<" "<<mem[str]<<"\n";//直接输出 
		return;
	}
	if(mem[str]<t){//无需展开 
		cout<<"+ ";
	}else{
		cout<<"- ";//需要展开 
	}
	cout<<str<<" "<<mem[str]<<"\n";//输出 
	if(mem[str]<t){//无需展开直接结束 
		return;
	}
	for(set<string>::iterator it=son[str].begin();it!=son[str].end();it++){
		dfs(*it);//遍历儿子节点dfs 
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	//提高字符串读入速度 
	cin>>n;
	while(n--){
		cin>>a;
		cin>>s;
		int m=a.size(),last=0;
		for(int i=1;i<m;i++){
			if(a[i]=='/'){
				mem[a.substr(0,last+1)]+=s;
				son[a.substr(0,last+1)].insert(a.substr(0,i+1));
				last=i;
				//连带路径存储 
			}
		}
		a[m]='/';
		mem[a]+=s;
		son[a.substr(0,last+1)].insert(a);//存最后一个节点 
	}
	cin>>t;
	dfs("/");//从根节点开始dfs 
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

我们可以使用树这个数据结构来表示文件夹的层次关系。

每个节点代表一个文件夹，包含其路径、大小和子文件夹列表。

我们首先创建一个根节点，并逐个处理输入的文件信息构建整个树。

1. 创建一个根节点（root），路径设置为 ``/``，大小设置为 $0$。

2. 对于每个输入的文件信息，将其路径按照 ``/`` 进行分割，得到各级文件夹名称的数组。

3. 从根节点开始，依次查找匹配的子文件夹，如果找到则将当前节点更新为该子文件夹；如果没找到则创建新的子文件夹节点，并将当前节点更新为该子文件夹。

4. 更新当前节点的大小，如果当前节点是文件夹节点则增加其大小，如果是文件则直接将文件大小相加。

5. 遍历完所有文件信息后，树的构建完成。

6. 使用深度优先搜索（DFS）遍历树的节点，并按要求输出文件夹的展开状态以及路径和大小。

当然，我们可以用 ``map`` 这个 ``STL`` 库容器小小的减少一下代码量。

### 完整代码：
```cpp
#include <bits/stdc++.h>
#define  ll long long
using namespace std;
string s;
int n, f, t;
map<string, ll> folderSize;
map<string, set<string>> fileTree;
inline void mount(string name) {
    string father = "/", curr;
    for (size_t i = 1; i < name.size(); i++) {
        if (name[i] == '/') {
            fileTree[father].insert(curr);
            folderSize[father] += f;
            father = father + curr + '/';
            curr = "";
        }
        else {
            curr += name[i];
        }
    }
    folderSize[father] += f;
}
inline void printTree(string name) {
    if (fileTree[name].size() == 0) {
        // 没法展开
        printf("  %s %lld\n", name.c_str(), folderSize[name]);
        return;
    }
    bool flag = false;
    for (auto conn : fileTree[name]) {
        // 找子文件夹, 有没有>=t的
        if (folderSize[name + conn + '/'] >= t) {
            flag = true;
            break;
        }
    }
    if (flag) {
        printf("- %s %lld\n", name.c_str(), folderSize[name]);
        for (auto conn : fileTree[name]) {
            printTree(name + conn + '/');
        }
        // 去print
    }
    else {
        // 只输出当前
        printf("+ %s %lld\n", name.c_str(), folderSize[name]);
    }
}
int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin >> n;
    while (n--) {
        cin >> s >> f;
        mount(s);
    }
    cin >> t;
    // printDepthTree("/", 0);
    printTree("/");
    system("pause");
    return 0;
}
```


---

