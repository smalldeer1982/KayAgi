# [GCJ 2010 #1B] File Fix-it

## 题目描述

在 Unix 计算机中，数据存储在目录中。存在一个根目录，根目录下可以包含若干名称不同的目录。这些目录下还可以包含更多的目录，依此类推。

一个目录可以通过其名称和父目录（即直接包含它的目录）唯一确定。这通常通过路径来编码，路径由若干部分组成，每一部分前面都有一个正斜杠（'/'）。最后一部分是该目录的名称，其余部分描述其父目录的路径。例如，考虑如下路径：
```
/home/gcj/finals
```
该路径指的是名为 "finals" 的目录，它位于 "/home/gcj" 所描述的目录下，而 "/home/gcj" 又指的是名为 "gcj" 的目录，位于 "/home" 所描述的目录下。在这个路径中，只有一部分，意味着它指的是根目录下名为 "home" 的目录。

要创建一个目录，可以使用 mkdir 命令。你需要指定一个路径，mkdir 会创建该路径描述的目录，但前提是其父目录已经存在。例如，如果你想从零开始创建 "/home/gcj/finals" 和 "/home/gcj/quals" 这两个目录，你需要四条命令：
```
mkdir /home
mkdir /home/gcj
mkdir /home/gcj/finals
mkdir /home/gcj/quals
```
给定你计算机上已经存在的所有目录，以及你想要新建（如果尚未存在）的目录集合，你需要用多少条 mkdir 命令？

## 说明/提示

**限制条件**

- $1 \leqslant T \leqslant 100$。
- 任意路径长度不超过 100 个字符。
- 已存在目录列表和待创建目录列表中不会有重复路径，但同一个路径可能在两者中各出现一次（见下方示例 case #2）。
- 如果某个目录已在你计算机上存在，则其父目录也必然在列表中，除非父目录是根目录。
- 输入文件总长度不超过 100,000 字节。

**小数据范围（12 分，测试集 1 - 可见）**

- $0 \leqslant N \leqslant 10$。
- $1 \leqslant M \leqslant 10$。

**大数据范围（14 分，测试集 2 - 隐藏）**

- $0 \leqslant N \leqslant 100$。
- $1 \leqslant M \leqslant 100$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
0 2
/home/gcj/finals
/home/gcj/quals
2 1
/chicken
/chicken/egg
/chicken
1 3
/a
/a/b
/a/c
/b/b```

### 输出

```
Case #1: 4
Case #2: 0
Case #3: 4```

# 题解

## 作者：ShaDouBuShi123 (赞：2)

# 这里是 [P13393 [GCJ 2010 #1B] File Fix-it](https://www.luogu.com.cn/problem/P13393) 的题解。

无意间发现一道落单的橙题，赶紧来发一下题解。

首先这道题的题目还是非常好理解的，大致如下：
1. 首先我们需要存储一些目录信息。
2. 题目还会要求我们建立亿点目录，每次建立都需要一次 [mkdir](https://baike.baidu.com/item/MKDIR/9500968) 指令。
3. 我们需要统计出来最少要执行多少次 `mkdir` 指令。
4. 题目有  $T$  组数据，有多少组上述过程就执行多少次。

看似很简单，但是需要注意的一点是，目录只能一个一个建立：例如需要建立两个目录，分别为 `/Windows/System32/config/` 和 `/Windows/Syswow64/config`，而且硬盘刚刚惨遭格式化，指令如下：

```
mkdir /Windows
mkdir /Windows/System32
mkdir /Windows/Syswow64
mkdir /Windows/System32/config
mkdir /Windows/Syswow64/config
```
不难看出这一特点，还有，当 `Windows` 文件夹已经存在时，不需要再次建立，而两个 `config` 文件夹存在于不同的父文件夹中时，它们需要两次创建，另外 `/` 文件夹属于根目录，所以在下面的代码中没啥处理。

明白了关键点，这一道题目就为一道简单的字符串题和模拟题。

直接上代码：

```python
T=int(input())#有几个case
ptr=1
for i in range(1,T+1):
    temp=input()
    temp=temp.split()#其实split函数的空格可以不写,但本人就是要写^_^
    N=int(temp[0])
    M=int(temp[1])
    ptr+=1
        
    have=[]#这是已经有了的
    for j in range(N):
        temp=input()
        path=temp.strip(' ')
        ptr+=1
        parts=path.split('/')[1:]
        for k in range(1,len(parts)+1):#记得+1,含头不含尾
            have.append('/' + '/'.join(parts[:k]))#这段类似语法糖(?)反正蛮方便的省了一个for
        
    res=0
    creating=[]#这是题目所求要建立的，为了方便理解与have分开(好像也不是)
    for j in range(M):
        temp=input()
        path=temp.strip(' ')
        ptr+=1
        if (path in have)or(path in creating):#目录正在创建或已存在就别管它
            continue
        parts=path.split('/')[1:]#路径全部分离(真棒)
        current=''
        for k in parts:#一层一层地分析
            current+='/'+k
            if (current not in have)and(current not in creating):#没有又没有创建，建它
                res+=1
                creating.append(current)
        
    print("Case #"+str(i)+": "+str(res))#打印空格注意

```

以上就是这篇题解的全部内容，希望对大家有所帮助！

---

## 作者：DFs_YYDS (赞：2)

一种类似于字典树的解法。
# 题目大意
给你一个树形的结构，先给你 $n$ 个从根节点到叶子节点的路径以供创建这棵树。随后再给你 $m$ 个路径，问你要创建出这些路径需要增加多少节点。
# 具体思路
这题十分有八分跟字典树一样，但是要简单一点。

先像正常的树一样定义，但是记录子节点的要改为 `map`。接着，建立的时候把路径分成多个字符串一个一个往下找，没有了就创建一个继续找。

询问的时候也是一样，只要在建立新节点时把 $ans$ 加 $1$ 即可。
# 完整代码
看上去很长，实际上很好理解，两个函数几乎一样。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,idx,ans;
struct o{
	string name;//没什么用。 
	map<string,int> k;
}a[1000005];
void clean(){//清空函数。 
	for(int i=1;i<=idx;i++)a[i].k.clear();
	idx=1,ans=0;
}
void it(string x){
	//拆分路径。 
	string s[105],w="";
	int id=0;
	x+='/';//在末尾加上/方便统计。 
	for(int i=1;i<x.size();i++){
		if(x[i]=='/')s[++id]=w;
		else w+=x[i];
	}
	//向下遍历 
	int p=1;
	for(int i=1;i<=id;i++){
		if(a[p].k.count(s[i])==0)a[p].k[s[i]]=(++idx);//如果没有就建立一个。 
		p=a[p].k[s[i]];
	}
}
void qt(string x){
	string s[105],w="";
	int id=0;
	x+='/';
	for(int i=1;i<x.size();i++){
		if(x[i]=='/')s[++id]=w;
		else w+=x[i];
	}
	int p=1;
	for(int i=1;i<=id;i++){
		if(a[p].k.count(s[i])==0)a[p].k[s[i]]=(++idx),ans++;//建立并增加答案。 
		p=a[p].k[s[i]];
	}
}
int main(){
	cin>>t;
	for(int w=1;w<=t;w++){
		clean();
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			string x;
			cin>>x;
			it(x);
		}
		for(int i=1;i<=m;i++){
			string x;
			cin>>x;
			qt(x);
		}
		cout<<"Case #"<<w<<": "<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：yongqian123 (赞：1)

## 题目分析
看到“目录”，立刻想到可以用多叉树的方法做（多叉树有模板）。

### 多叉树模板‌
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll _p = 100;
vector<string> vec;
class node{
private:
	string father;
public:
	map<string, node*> sons;
	node(string _father): father(_father){}
	void insert(ll x){
		if (x >= vec.size()) return;
		string dir = vec[x];
		if (sons.find(dir) == sons.end()) sons[dir] = new node(dir);
	}
};
class tree{
private:
	node* root;
public:
	tree(){root = new node("");}
	void insert(){
		node* tmp = root;
		for (string& dir : vec){
			if (tmp->sons.find(dir) == tmp->sons.end()) tmp->sons[dir] = new node(dir);
			tmp = tmp->sons[dir];
		}
	}
};
signed main(){
  ;
  return 0;
}

```

现在我们可以看到，我们还需要：
- 分割目录的函数 `split`；
- 计算命令数量的函数 `tree::count`。

### `split` 函数
想到 `getline` 函数可以获取到特定字符，于是结合 `stringstream` 读取目录，存到 `vec` 里。

```cpp
void split(){
	vec.clear();
	char p[_p];
	scanf("%s", p);
	stringstream ss(p);
	string s;
	while (getline(ss, s, '/')) if (!s.empty()) vec.push_back(s);
}

```

### `node::insert` `tree::count` 函数
一边建树一边计算。

```cpp
ll insert(ll x){
	if (x >= vec.size()) return 0;
	string dir = vec[x];
	ll cnt = 0;
	if (sons.find(dir) == sons.end()) sons[dir] = new node(dir), cnt = 1;
	return cnt + sons[dir]->insert(x + 1);
}

```

```cpp
ll count(){
	return root->insert(0);
}

```

### 主函数
用 $ans$ 统计答案。

```cpp
signed main(){
	ll T;
	cin >> T;
	for (ll Ti = 1; Ti <= T; Ti++){
		ll N, M;
		scanf("%lld%lld", &N, &M);
		tree tr;
		for (ll i = 0; i < N; i++) split(), tr.insert();
		ll ans = 0;
		for (ll i = 0; i < M; i++) split(), ans += tr.count();
		printf("Case #%lld: %lld\n", Ti, ans);
	}return 0;
}

```

## 完整答案
结合一下即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define io ios::sync_with_stdio(0), cin.tie(), cout.tie()
const ll _p = 100;
vector<string> vec;
class node{
private:
	string father;
public:
	map<string, node*> sons;
	node(string _father): father(_father){}
	ll insert(ll x){
		if (x >= vec.size()) return 0;
		string dir = vec[x];
		ll cnt = 0;
		if (sons.find(dir) == sons.end()) sons[dir] = new node(dir), cnt = 1;
		return cnt + sons[dir]->insert(x + 1);
	}
};
class tree{
private:
	node* root;
public:
	tree(){root = new node("");}
	void insert(){
		node* tmp = root;
		for (string& dir : vec){
			if (tmp->sons.find(dir) == tmp->sons.end()) tmp->sons[dir] = new node(dir);
			tmp = tmp->sons[dir];
		}
	}
	ll count(){return root->insert(0);}
};
void split(){
	vec.clear();
	char p[_p];
	scanf("%s", p);
	stringstream ss(p);
	string s;
	while (getline(ss, s, '/')) if (!s.empty()) vec.push_back(s);
}
signed main(){
	ll T;
	cin >> T;
	for (ll Ti = 1; Ti <= T; Ti++){
		ll N, M;
		scanf("%lld%lld", &N, &M);
		tree tr;
		for (ll i = 0; i < N; i++) split(), tr.insert();
		ll ans = 0;
		for (ll i = 0; i < M; i++) split(), ans += tr.count();
		printf("Case #%lld: %lld\n", Ti, ans);
	}return 0;
}

```

---

## 作者：lcliruiyan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13393)

## 题目大意
虽然题目有点长，但是实际上是给出一些字符串，询问每一个字符串是否已经出现过。如果没有出现过，就将答案增加 $1$。

## 题目思路
看到题目要求和数据范围，很容易就能想到，可以用模拟的方法来做。考虑使用 $map$ 来存储每个字符串是否已经出现过。

再仔细看题目，就会发现，要存储和查找的字符串都是从第一个字符开始，到下一个斜杠结束的。因此，我们可以用一个数组保存每一个斜杠的位置。若第 $i$ 个斜杠在字符串 $s$ 中的位置为 $a_i$ ，那么，每一个要查找的字符串就是 $s$ 从 $0$  到 $a_i-1$ 的子串。

要截取子串，最简单的方法当然是用 $substr$ 函数了。

截完子串之后，如果当前子串不在 $map$ 中，就要标记当前子串出现过，并将答案加 $1$。

有些细节需要特别注意：

-  由于题目有多组数据，所以在每一组数据输入前必须初始化 $map$。但是 $map$ 不能在每次询问时清空。因为同一组数据中，之前建好的文件目录是一直保留的。
-  用 $a$ 数组存储斜杠出现的位置时，要把字符串最后一个字符的下一个位置也存下来，因为还需要判断整个字符串是否已经出现过。
-  使用 $substr$ 时要注意，函数的第二个参数传递的是截取子串的长度，不是子串的右端点位置，不要写错了。
-  输出时要记得加上 `Case`。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[105],cur;
string s;
int main()
{
    cin>>T;
    for(int t=1;t<=T;t++)
    {
        int ans=0;
        cin>>n>>m;
        map<string,int>ma;
        for(int i=1;i<=n;i++)
            cin>>s,ma[s]=1;
        for(int i=1;i<=m;i++)
        {
            memset(a,0,sizeof(a));
            cur=0;
            cin>>s;
            for(int j=1;j<s.size();j++)
                if(s[j]=='/')a[++cur]=j;
            a[++cur]=s.size();
            for(int j=1;j<cur;j++)
            {
                string ns=s.substr(0,a[j]);
                if(ma[ns]==1)continue;
                else ans++,ma[ns]=1;
            }
            if(ma[s]==1)continue;
            else ans++,ma[s]=1;
        }
        printf("Case #%d: %d\n",t,ans);
    }
    return 0;
}
```

---

## 作者：LiHen_Yan (赞：1)

## P13393 [GCJ 2010 #1B] File Fix-it 题解


### Problem
给你 $n$ 个已经有的目录，要建 $m$ 个目录，需要几次操作？

### Solution
注意到 $n,m\leq100$，直接暴力模拟就行，但是太难写了，有没有更快更好写的做法呢？

有的兄弟，有的。

看到这个目录的结构，如果什么都没有的时候你需要从根目录开始建，如果你要建的目录的前几个已经有了，你就可以直接用，如果你学过数据结构，那很容易就能看出来，这不是我们字典树吗。

然后就好搞了，按 `/` 划分字符串，把每个目录结构插入到字典树中，后面 $m$ 个插入的时候算答案即可。

代码很好写就不贴了。

---

## 作者：Sunny_Boybgfcxc (赞：0)

# P13393 [GCJ 2010 #1B] File Fix-it
[更好的阅读体验](https://www.luogu.com.cn/article/6740q8z1)
## 题意简述
&nbsp;&nbsp;给出计算机中除根目录外 $n$ 个已存在的目录，问一共需要执行多少次 mkdir 指令才能创建出给出的 $m$ 个目录。
## 解题思路
&nbsp;&nbsp;本题直接模拟。  
&nbsp;&nbsp;为了方便处理，对于每一个目录，如果该目录已存在，那么执行次数为 $0$。否则执行次数加一，将该目录标记为存在，再以同样的方式处理其上级目录。  
&nbsp;&nbsp;具体思路结合代码展示。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,bool>mp;
string x;
int t,n,m,ans=0;
int work(string x){
	if(mp[x]==1||x=="")return 0;//注意，当x为空串时应当直接退出
	else{
		mp[x]=true;
		int f=x.rfind("/");
		x.erase(f,x.size()-f);//转到上一级目录
		return work(x)+1;//操作次数加一
	}
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    for(int l=1;l<=t;l++){
        mp.clear();//多测不清空，含泪见祖宗
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){//初始化
			cin>>x;
			while(x.rfind("/")!=-1){
				mp[x]=true;
				x.erase(x.rfind("/"),x.size()-x.rfind("/"));
			}
		}
		for(int i=1;i<=m;i++){
			cin>>x;
			ans+=work(x);//累计答案
		}
		cout<<"Case #"<<l<<": "<<ans<<'\n';
	}
	return 0;
} 
```
[AC记录](https://www.luogu.com.cn/record/226812087)

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13393)  
即给定一组已存在的目录和一组需要创建的目录，计算最少需要多少条 `mkdir` 命令才能创建所有目标目录。每个 `mkdir` 命令只能创建单个目录（即父目录必须已存在）。

### 题目分析
我们需要创建每个缺失的目录，且必须按从根到叶的顺序创建。把每个目录（包括给定的和待创建的）拆分成多个形如 `xxx` 的字符串（`/aa/ba/ca/da` 拆解成 `aa`，`ba`，`ca` 和 `da`），判断需要创建的目录是否在已创建的目录中即可。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int ti;

vector<string>fen(string s){//拆分路径
	vector<string> p;
    stringstream ss(s);
    string pa;
    while (getline(ss, pa,'/')) {
        if(!pa.empty())p.push_back(pa);
    }
    return p;
}

void f(int t){
	int n,m;
	cin>>n>>m;
	set<string>lj;//已有的路径
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		vector<string>p=fen(s);
		string cur="";
		for(auto pa:p){
			cur+="/"+pa;
			lj.insert(cur);
		}
	}
	int ans=0;
	for(int i=0;i<m;i++){
		string s;
		cin>>s;
		vector<string>p=fen(s);
		string cur="";
		for(auto pa:p){
			cur+="/"+pa;
			if(lj.find(cur)==lj.end()){//判断是否创建
                    ans++;
                    lj.insert(cur);//加入已有的路径
            }
		}
	}
    cout<<"Case #"<<t<<": "<<ans<<endl;
}

signed main()
{
	fst
	cin>>ti;
	for(int i=1;i<=ti;i++){
		f(i);
	}
	return 0;
}
```

---

