# Petya and File System

## 题目描述

Recently, on a programming lesson little Petya showed how quickly he can create files and folders on the computer. But he got soon fed up with this activity, and he decided to do a much more useful thing. He decided to calculate what folder contains most subfolders (including nested folders, nested folders of nested folders, and so on) and what folder contains most files (including the files in the subfolders).

More formally, the subfolders of the folder are all its directly nested folders and the subfolders of these nested folders. The given folder is not considered the subfolder of itself. A file is regarded as lying in a folder, if and only if it either lies directly in this folder, or lies in some subfolder of the folder.

For a better understanding of how to count subfolders and files for calculating the answer, see notes and answers to the samples.

You are given a few files that Petya has managed to create. The path to each file looks as follows:

 $ diskName $ : $ \ $ $ folder_{1} $ $ \ $ $ folder_{2} $ $ \...\ $ $ folder_{n} $ $ \ $ $ fileName $

- $ diskName $ is single capital letter from the set {C,D,E,F,G}.
- $ folder_{1} $ , ..., $ folder_{n} $ are folder names. Each folder name is nonempty sequence of lowercase Latin letters and digits from 0 to 9. ( $ n>=1 $ )
- $ fileName $ is a file name in the form of $ name $ . $ extension $ , where the $ name $ and the $ extension $ are nonempty sequences of lowercase Latin letters and digits from 0 to 9.

It is also known that there is no file whose path looks like $ diskName $ : $ \ $ $ fileName $ . That is, each file is stored in some folder, but there are no files directly in the root. Also let us assume that the disk root is not a folder.

Help Petya to find the largest number of subfolders, which can be in some folder, and the largest number of files that can be in some folder, counting all its subfolders.

## 说明/提示

In the first sample we have one folder on the "C" disk. It has no subfolders, which is why the first number in the answer is $ 0 $ . But this folder contains one file, so the second number of the answer is $ 1 $ .

In the second sample we have several different folders. Consider the "folder1" folder on the "C" disk. This folder directly contains one folder, "folder2". The "folder2" folder contains two more folders — "folder3" and "folder4". Thus, the "folder1" folder on the "C" drive has exactly $ 3 $ subfolders. Also this folder contains two files, even though they do not lie directly in the folder, but they are located in subfolders of "folder1".

In the third example we see that the names of some folders and some subfolders are identical. Consider the "file" folder, which lies directly on the "C" disk. That folder contains another "file" folder, which in turn contains another "file" folder, which contains two more folders, "file" and "file2". Thus, the "file" folder, which lies directly on the "C" disk, contains $ 4 $ subfolders.

## 样例 #1

### 输入

```
C:\folder1\file1.txt
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
C:\folder1\folder2\folder3\file1.txt
C:\folder1\folder2\folder4\file1.txt
D:\folder1\file1.txt
```

### 输出

```
3 2
```

## 样例 #3

### 输入

```
C:\file\file\file\file\file.txt
C:\file\file\file\file2\file.txt
```

### 输出

```
4 2
```

# 题解

## 作者：45dino (赞：4)

这道题调了半天……

首先，可以确定的是，如果该文件夹的子文件夹和子文件最多，该文件夹必然是第一层的文件夹（下文的“母文件夹”（就是C://后面的）

于是乎，可以用两个map存储每个母文件夹的子文件夹（set）和子文件个数（为了去重，必须记录子文件夹而不是子文件夹的个数）

首先，对于每个文件的路径，分离出母文件夹：
```
for(tmp=3;inp[tmp]!='\\';tmp++);\\注意分号
for(int j=0;j<tmp;j++)
	s[j]=inp[j];
s[tmp]=0;//0代表'\0',是一个字符串的结尾
```
分别维护两个set：
```
cnt[s]++;//每个路径只有一个文件，而且保证文件不相同
		
```
```

for(int i=strlen(inp)-1;i>tmp;i--)
	if(inp[i]=='\\')
	{
		inp[i]=0;\\上文提到'\0'是字符串的结尾，所以0后面的都被去掉了，如C:\folder1\folder2\folder3\file变成了C:\folder1\folder2\folder3;
		sub[s].insert(inp);\\把文件夹加入map；
	}
```
之后的部分就很简单了……
```
for(map<string,set<string> >::iterator i=sub.begin();i!=sub.end();i++)
	ans1=max(ans1,(int)((i->second).size()));
for(map<string,int>::iterator i=cnt.begin();i!=cnt.end();i++)
	ans2=max(ans2,i->second);
cout<<ans1<<" "<<ans2;
return 0;
```
完整程序（建议再消化一下，可以输出一些中间过程帮助理解)
```
#include<bits/stdc++.h>
using namespace std;
map<string,int> cnt;
map<string,set<string> > sub;
char s[10000],inp[10000];
int tmp,ans1,ans2;
int main()
{
	while(gets(inp))
	{
		for(tmp=3;inp[tmp]!='\\';tmp++);
		for(int j=0;j<tmp;j++)
				s[j]=inp[j];
		s[tmp]=0;
		cnt[s]++;
		for(int i=strlen(inp)-1;i>tmp;i--)
			if(inp[i]=='\\')
			{
				inp[i]=0;
				sub[s].insert(inp);
			}
	}
	for(map<string,set<string> >::iterator i=sub.begin();i!=sub.end();i++)
		ans1=max(ans1,(int)((i->second).size()));
	for(map<string,int>::iterator i=cnt.begin();i!=cnt.end();i++)
		ans2=max(ans2,i->second);
	cout<<ans1<<" "<<ans2;
	return 0;
}
```


---

## 作者：123asdf123 (赞：3)

第一篇题解。

最水的蓝题 $\cdots\cdots$

# 建文件树

直接按要求建出路径树就行了，文件也可以当做文件夹，只是里面没有子文件夹而已（反正肯定有文件夹套着的，$n\ge 1$），例如样例2：（folder,file 一律简写为 f）

![](https://cdn.luogu.com.cn/upload/image_hosting/e1ou0s5v.png)

## 处理方法：

1. 先将的前面三位盘符单独处理，我是将它们视为文件夹，提前处理。（但它们不是真正的文件夹，题目中说了：**磁盘不是文件夹！**，求解时不能拿它们计算）
2. 每次获取文件夹名，直到遇到反斜杠或到字符串结尾。提前记录上一个节点（文件夹）的编号，查找有没有这个儿子（建没建这个文件夹），如果没找到这个儿子，用 stl 的 map（方便查找儿子所对应的节点编号）来新记录它的儿子。
3. 到字符串结尾后，就回到步骤 $1$，继续处理下一个字符串。

# 求解
用一个十分简单的树形 DP。

每个节点有两个变量：这里面的文件数 $file_i$ 和文件夹数 $folder_i$。

如果这个节点没有儿子，说明它是文件，$file_i\gets1$，$folder_i\gets0$。

否则，$\begin{aligned}file_i\gets\sum_{j=sons_i}file_j\end{aligned}$，$\begin{aligned}folder_i\gets1+\sum_{j=sons_i}folder_j\end{aligned}$。

最后的答案分别就是 $folder_i$ 的最大值**减 1**（因为该文件夹不算）和 $file_i$ 的最大值。

# code
我的代码当时是随便写的，所以 $ls$ 表示 $folder$，$nls$ 表示 $file$。
```c++
#include<bits/stdc++.h>
using namespace std;
namespace abc{
	struct node{
		string s;
		int sons,ls,nls;
		map<string,int>m;
	}a[1000003];//其实不必开这么大，随便写的
	int cnt=0;
	void add(string s){//增加新节点
		cnt++;
		a[cnt].s=s;
		a[cnt].sons=0;
		a[cnt].ls=0;
		a[cnt].nls=0;
		a[cnt].m.clear();
	}
	void get(int x){//求解大小
		if(a[x].sons==0)
			a[x].nls=1;
		else
			a[x].ls=1;
		for(auto i:a[x].m){
			get(i.second);
			a[x].ls+=a[i.second].ls;
			a[x].nls+=a[i.second].nls;
		}
	}
	int main(){
		string s,ss;
		int lcnt,ls=0,nls=0;
		add("C");//提前把盘符当文件夹
		add("D");
		add("E");
		add("F");
		add("G");
		while(cin>>s){
			lcnt=s[0]-'C'+1;//因为盘符恰好对应着cnt的前5位，因此这步是求盘符对应的文件夹编号
			for(int i=3;i<s.size();i++){
				ss="";
				ss+=s[i];
				while(i<s.size()-1&&s[i+1]!='\\')
					ss+=s[++i];
				i++;//跳过这个反斜杠
				if(a[lcnt].m.find(ss)==a[lcnt].m.end()){
					add(ss);
					a[lcnt].sons++;
					a[lcnt].m[ss]=cnt;
				}
				lcnt=a[lcnt].m[ss];
			}
		}
		get(1);//求所有的大小
		get(2);
		get(3);
		get(4);
		get(5);
		for(int j=1;j<=5;j++)
			for(auto i:a[j].m){//因为最高的文件夹肯定更优，所以只用找第一层，盘符不是文件夹！
				ls=max(ls,a[i.second].ls);
				nls=max(nls,a[i.second].nls);
			}
		printf("%d %d",ls-1,nls);//记得减1
		return 0;
	}
}
int main(){
	abc::main();
	return 0;
}

```

---

## 作者：ZLCT (赞：0)

# CF66C Petya and File System
## 题意描述
给定若干条文件路径，每条路径的格式为（磁盘名：\文件夹名1\文件夹名2…\文件夹名x\文件名）。两个文件夹相同当且仅当两个文件夹的名称和路径完全相同，文件每个的路径都不同，问包含文件夹最多的文件夹包含多少文件夹，包含文件最多的文件夹包含多少文件。
## 一道神仙模拟题
这个题十分考验一个人是否会写代码，下面我挑选了三种比较好的代码写法逐一讲解。
### solution 1 by me
首先对于读入方面，由于读入时会先读如磁盘，而磁盘后会跟一个 `\`，这让我们不好区分文件夹与磁盘。于是我们读如时只保存磁盘名，对于 `:` 和 `\` 我们不进行读入。\
这里我们可以利用 c++ 一个特性，当你读如一个字符类型的变量时无论后面有什么，它只会读如一个字符，所以我们可以利用以下代码完成读如：
```cpp
char c1,c2,c3;
while(cin>>c1>>c2>>c3>>s){
    make(c1);//后续操作
}
```
那么接下来我们考虑如何进行后续操作。\
一个贪心的想法是我们最终答案肯定是磁盘名的直属文件夹。\
这个也是比较容易证明的，因为我们把所有的文件夹以及文件看作一棵树，那我们的第一个问题就是子树内非叶子节点数量，第二个问题是子树内叶子节点数量。那这两个无论哪一个都是选择根最优。\
那么我们就只需要考虑每个磁盘直属文件夹内文件夹个数和文件个数即可。\
文件个数我们方便处理，因为文件没有重复且每个路径有且仅有一个文件，所以我们可以直接将当前的磁盘直属文件夹的文件数 $+1$。\
那如何处理子文件夹呢？\
我们可以把所有的子文件夹都扔进去，但是我们需要判重，这一点可以利用 `set` 简化维护。\
那么最终的答案我们去枚举每一个的磁盘直属文件夹，分别取其中子文件夹数的最大值和文件数的最大值。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
map<string,int>g;
map<string,set<string> >f;
int ans1,ans2;
void make(char c){
    string now="";now+=c;
    int k=0;
    for(int i=0;i<s.size();++i){
        if(s[i]=='\\'){
            k=i;
            break;
        }
        now+=s[i];
    }
    g[now]++;
    for(int i=s.size()-1;i>k;--i){
        if(s[i]=='\\'){
            string st="";st+=c;
            st+=s.substr(0,i);
            f[now].insert(st);
        }
    }
}
signed main(){
    char c1,c2,c3;
    while(cin>>c1>>c2>>c3>>s){
        make(c1);
    }
    for(auto p:f){
        ans1=max(ans1,(int)p.second.size());
    }
    for(auto p:g){
        ans2=max(ans2,p.second);
    }
    cout<<ans1<<' '<<ans2<<'\n';
    return 0;
}
```
### solution by `_vb92xHWx8zQTc_34`
我们去看刚才我们对于贪心的证明，会发现如果我们能把树建出来，那么答案也就很好算了。\
那能否建出树呢？\
实际上也是好建的。我们对于每个文件夹，都向它的直属文件夹/文件连一条边，那么我们就可以树形 dp 求出每棵子树上子文件夹的叶子节点数和非叶子节点数（总节点 $-$ 叶子节点数）。\
这里其实还要注意一个小问题，对于文件来说，它后面没有 `\`，所以要特殊处理。
### code
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;
map <string,int> mp;
int cnt;
vector <int> e[500005];
int sz[500005],qwq[500005],ans1,ans2;
inline void dfs(int u)
{
	sz[u]=1;
	for(auto v:e[u])
		if(!sz[v]) dfs(v),sz[u]+=sz[v],qwq[u]+=qwq[v];
	if(sz[u]==1) ++qwq[u];
	if(u) ans1=max(ans1,sz[u]-qwq[u]),ans2=max(ans2,qwq[u]);
}
int main(int argc, char** argv) {
	string s;
	while(cin >> s)
	{
		int lst=0,flag=0;
		s+='\\';
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='\\')
			{
				if(!flag)
				{
					flag=1;
					continue;
				}
				if(!mp[s.substr(0,i+1)])
					mp[s.substr(0,i+1)]=++cnt;
				e[lst].push_back(mp[s.substr(0,i+1)]);
				lst=mp[s.substr(0,i+1)];
			}
		}
	}
	dfs(0);
	cout << ans1-1 << " " << ans2;
	return 0;
}
```
它这里没有用我的那种输入方法，于是他选择了记录一个 $flag$ 来把第一个 `\` 给跳过，这也是一种很聪明的处理。
### solution by `rng_58`
这个做法实在太神仙，于是先放出代码再一一讲解。
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

char buf[110];
vector <string> files;
bool _unique[10010];
bool folder[10010];

bool sub(int a, int b){
    int i;
    if(files[a].length() > files[b].length()) return false;
    REP(i,files[a].length()) if(files[a][i] != files[b][i]) return false;
    return true;
}

int main(void){
    int i,j;
    
    while(scanf("%s",buf) != EOF){
        string s = buf;
        for(i=4;i<s.length();i++) if(s[i] == '\\') files.push_back(s.substr(0,i+1));
        files.push_back(s);
    }
    
    sort(files.begin(),files.end());
    
    int N = files.size();
    REP(i,N) _unique[i] = folder[i] = true;
    REP(i,N-1) if(files[i] == files[i+1]) _unique[i+1] = false;
    REP(i,N) REP(j,files[i].length()) if(files[i][j] == '.') folder[i] = false;
    
    int ans1 = 0, ans2 = 0;
    REP(i,N){
        int low = i, high = N, mid;
        while(high-low > 1){
            mid = (high + low) / 2;
            if(sub(i,mid)) low = mid; else high = mid;
        }
        
        int cnt1 = 0, cnt2 = 0;
        for(j=i+1;j<=low;j++){
            if(_unique[j] && folder[j]) cnt1++;
            if(_unique[j] && !folder[j]) cnt2++;
        }
        
        ans1 = max(ans1,cnt1); ans2 = max(ans2,cnt2);
    }
    
    cout << ans1 << ' ' << ans2 << endl;
    
    return 0;
}
```
首先他先把所有的文件夹和文件都统计下来。\
接着他把所有的文件夹和文件排序，这一步是整个代码的点睛之笔，我们一步步往下看。\
接下来一步就用到了排序后的性质，对于重复的文件夹，由于它们在排序时一定会排在一起，所以我们可以直接比较当前文件夹与后面的文件夹是否相同，若重复则后面那个文件夹就不会统计在答案里。这样每个文件夹我们只保留了第一个出现的文件夹作为贡献。\
对于文件的判断，他独出心裁地通过只有文件名且文件名一定有 `.` 的特性来判断。\
接下来它就对于每个文件夹去处理其子文件夹和子文件数量。\
这里的二分相信初看时都会一头雾水，我们现在就来解释一下这一步的人类智慧。\
对于字符串的比较，c++中是默认按照字典序来比较的，也就是说比较时与字符串长度无关，只与字符串的前缀有关。\
那我们思考对于我们的文件夹路径，也恰好是这样的，只要一个文件夹路径是另一个文件夹路径的前缀，那么也就代表这个文件夹包含了另一个文件夹。\
而由于排序时是按字典序进行比较的，所以一个文件夹的子文件夹和子文件一定是与它相邻的一段区间。\
那么此时第 $i$ 个文件夹的子文件夹和子文件一定是一段区间，假设我们找到一个合法点，我们就可以二分出左右端点。\
那这个合法点如何找？这又回到了我们的排序，在排序时第 $i$ 个文件夹的子文件夹和子文件的路径一定是以第 $i$ 个文件夹的路径作为前缀，后面附加若干路径。那么在排序时后面为空的第 $i$ 个文件夹路径一定是排最前面的，也就是区间的左端点，此时我们只需要二分右端点即可。\
其余统计答案和上面两种一样，那么这份充满人类智慧的代码我们就完全理解了。
### solution by `shenmadongdong`
在看了这么多巧妙的处理后，我们最终回归本真，去以一个朴素的角度重新看待这个题。\
这个题本质上就是求两个东西：
- 一个文件夹后不同文件夹数量之和
- 一个文件夹总共出现了几次

第二个我们永远是好求的一个，因为只要出现一个文件夹，就直接把它的文件数 $+1$ 就行，这个究其原因是在于它不需要判重。\
那么我们考虑 `rng_58` 的预处理，他把所有重复的文件夹都只计算第一次出现的，我们能否也用这种思想去简单地求解第一个问题呢？
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b;
map<string,int> m,n;
int main()
{
	while(cin>>s)
	{
		int F=0;
		while(1)
		{
			int x=s.find_last_of('\\');
			if(x==2) break;
			s=s.substr(0,x);
			int f=n[s];
			m[s]+=F,n[s]++;
			a=max(a,m[s]);b=max(b,n[s]);
			if(!f) F++;
		}
	}	
	cout<<a<<" "<<b<<endl;
	return 0;
}
```
这份代码给我们了很好的解法。\
我们可以从两个方面理解这件事，第一个就是 `rng_58` 的思路，我们只要保证我们只在一个文件夹出现的第一次统计它，就一定不会算重。\
第二个方面我们可以联系上面的 solution 2，我们每次相当于都是把从一个叶子到根的路径都贡献一遍，而文件数由于叶子之间不可能相交，所以可以直接整条链 $+1$，而文件夹若我们走到了一个节点发现之前已经加过这个节点了，就说明已经走到了与之前一个叶子的 LCA，那么 LCA 上面的路径也一定把这个点代表的文件夹更新了，所以我们不需要再更新这个文件夹了。

---

## 作者：ncwzdlsd (赞：0)

## 题目

小彼佳决定算文件夹中包含的子文件夹（包括嵌套文件夹，大多数嵌套嵌套文件夹，文件夹等等）和文件夹中包含的文件（包括子文件夹中的文件）。 下面的样例可以帮助你更好的了解文件和文件夹： 每一个文件的路径如下： diskname:\folder1\folder2\…\foldern\filename diskname 是 C D E F G 五个字母中的一个 folder1，…，foldern 是文件夹名称。每个文件夹的名字是非空序列的小写拉丁字母和数字 $0$ 到 $9$ 组成的。 

请编程找到同一文件夹中包含的最多文件数量和文件夹中包含的最多的子文件夹数量。

## 题解

这道题是一道纯纯的模拟题 and 一些 STL 容器的使用练习。

为了避免不同文件重名的问题，我们选择直接用一个文件的绝对路径来表示这个文件，这样就解决了这个问题。

除此之外，子文件夹和子文件数最多的文件夹肯定是根目录下的文件夹。

意识到这两点之后，我们就可以愉快地模拟了。

具体实现，我们可以用 `map` 建立一个映射，用 `set` 来存储各文件夹的字符串信息，这样可以自动去重，非常方便。

提供一些可能会用到的操作：

```cpp
strqwq=substr(str,1,5);//substr函数，截取从1到5的字符串值
h.insert(make_pair(1,2));//向map中插入多元组
```

代码就不放了，要自己写模拟才能有收获哟！

---

## 作者：Allanljx (赞：0)

## 思路
~~输入有很大的难度~~ 用 $1$ 个三维的 map 记录第 $x$ 个磁盘，上一级的编号为 $y$ 的文件夹的编号。然后按照 map 记录的编号对于每个最高级文件夹建树：将当前文件夹连到上一级文件夹下面。第一个问题的答案是：对于每颗树将除去根节点和叶子结点的节点数取 $\max$。第二个问题的答案是：对于每颗树的叶子结点数量取 $\max$。具体输入和建树细节见代码注释。

## 代码
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define int long long
using namespace std;
map<string,int> mp[10][10000];//三维map 
int tmp,f,sum1,sum2,ans1,ans2;
int vis[10005];//是否dfs过 
string s;//文件夹或文件名称 
vector<int> t[10005];//树 
void dfs(int u)
{
	vis[u]=1;//标记访问过 
	if(t[u].size()) sum1++;//非叶子结点 
	else sum2++;//叶子结点 
	for(int i=0;i<t[u].size();i++)
	{
		dfs(t[u][i]);
	}
}
signed main()
{
	char c;
	while(c=gc)
	{
		if(c==EOF) break;//输入结束的标志 
		int x=c-'B';//哪个磁盘 
		gc;gc;//读入：和\ 
		int la=-1;//上一级文件夹的编号 
		while(1)
		{
			s.clear();
			while(c=gc)
			{
				if(c==92||c==10) break;//92是\,10是\n 
				s+=c;
			}
			if(la!=-1)//不是最高级文件夹 
			{
				if(!mp[x][la][s])//没出现过 
				{
					mp[x][la][s]=++tmp;//记录编号 
					t[la].push_back(tmp);//建树 
					la=tmp;//更新上一级文件夹的编号 
				}
				else la=mp[x][la][s];//更新上一级文件夹的编号 
			}
			else//最高级文件夹 
			{
				if(!mp[x][0][s]) mp[x][0][s]=++tmp,la=tmp;//没出现过 
				else la=mp[x][0][s];//更新上一级文件夹的编号 
			}
			if(c=='\n') break;//这一行输入完了 
		}
	}
	for(int i=1;i<=tmp;i++)
	{
		if(vis[i]) continue;//已经搜过了（不是根节点） 
		dfs(i);
		ans1=max(ans1,sum1-1/*减去根节点*/),ans2=max(ans2,sum2);
		sum1=sum2=0;
	}
	cout<<ans1<<' '<<ans2;
}
```

---

