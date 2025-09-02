# 题目信息

# [ABC285D] Change Usernames

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc285/tasks/abc285_d

あなたの運営する Web サービスには $ N $ 人のユーザがいます。

$ i $ 番目のユーザの現在のユーザ名は $ S_i $ ですが、$ T_i $ への変更を希望しています。  
ここで、$ S_1,\ldots,S_N $ は相異なり、$ T_1,\ldots,T_N $ も相異なります。

ユーザ名を変更する順序を適切に定めることで、以下の条件を全て満たすように、全てのユーザのユーザ名を希望通り変更することができるか判定してください。

- ユーザ名の変更は $ 1 $ 人ずつ行う
- どのユーザもユーザ名の変更は一度だけ行う
- ユーザ名の変更を試みる時点で他のユーザが使っているユーザ名に変更することはできない

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ S_i,T_i $ は英小文字からなる $ 1 $ 文字以上 $ 8 $ 文字以下の文字列
- $ S_i\ \neq\ T_i $
- $ S_i $ は相異なる
- $ T_i $ は相異なる

### Sample Explanation 1

$ 1 $ 番目のユーザの現在のユーザ名は `b` であり、`m` への変更を希望しています。 $ 2 $ 番目のユーザの現在のユーザ名は `m` であり、`d` への変更を希望しています。 まず、$ 2 $ 番目のユーザのユーザ名を `m` から `d` に変更し、 その後 $ 1 $ 番目のユーザのユーザ名を `b` から `m` に変更することで、条件を満たしながら変更することができます。 最初の時点では $ 2 $ 番目のユーザのユーザ名が `m` なので、$ 1 $ 番目のユーザのユーザ名を同じ `m` に変更することはできません。

### Sample Explanation 2

$ 1 $ 番目のユーザの現在のユーザ名は `a` であり、`b` への変更を希望しています。 $ 2 $ 番目のユーザの現在のユーザ名は `b` であり、`c` への変更を希望しています。 $ 3 $ 番目のユーザの現在のユーザ名は `c` であり、`a` への変更を希望しています。 条件を満たしながらユーザ名の変更を行うことはできません。

## 样例 #1

### 输入

```
2
b m
m d```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
a b
b c
c a```

### 输出

```
No```

## 样例 #3

### 输入

```
5
aaa bbb
yyy zzz
ccc ddd
xxx yyy
bbb ccc```

### 输出

```
Yes```

# AI分析结果

### 题目中文重写
你运营的 Web 服务中有 $N$ 名用户。

第 $i$ 名用户当前的用户名是 $S_i$，但希望将其更改为 $T_i$。这里，$S_1,\ldots,S_N$ 各不相同，$T_1,\ldots,T_N$ 也各不相同。

请判断是否可以通过适当地确定用户名更改的顺序，使得所有用户的用户名都能按照他们的期望进行更改，同时满足以下所有条件：
- 用户名的更改一次只能对一个用户进行。
- 每个用户只能更改一次用户名。
- 在尝试更改用户名时，不能将用户名更改为其他用户正在使用的用户名。

### 综合分析与结论
这些题解主要围绕判断是否能按要求完成用户名更改展开，核心在于判断图中是否存在环。不同题解采用了多种方法，包括模拟处理、深搜、拓扑排序、Tarjan 算法、并查集等。
- **思路对比**：多数题解将问题转化为图论问题，通过判断图中是否有环来确定是否能完成更改；FFTotoro 的题解则采用模拟处理的方式，逐步处理能更换用户名的用户。
- **算法要点**：拓扑排序是最常用的算法，通过记录入度，不断将入度为 0 的节点加入队列进行处理；深搜通过递归检查是否进入环；Tarjan 算法用于求强连通分量判断环；并查集则根据节点的“父亲”关系判断环。
- **解决难点**：主要难点在于处理字符串节点，多数题解使用 `map` 进行字符串到数字的映射，方便后续处理。

### 所选题解
- **FFTotoro（5星）**：
    - **关键亮点**：思路简单好想，不使用图论和并查集，通过模拟处理能更换用户名的用户，逐步推进，避免了复杂算法的使用。
- **zajasi（4星）**：
    - **关键亮点**：使用深搜解决问题，通过分类讨论和回溯，判断是否进入环，代码逻辑清晰。
- **Fire_flame（4星）**：
    - **关键亮点**：提供了拓扑排序和深搜两种解法，代码实现规范，对于不同基础的读者都有参考价值。

### 关键思路或技巧
- **字符串映射**：使用 `map` 或 `unordered_map` 将字符串映射为数字，方便处理图的节点。
- **拓扑排序**：通过记录节点的入度，将入度为 0 的节点加入队列，不断更新入度，判断是否能遍历完所有节点。
- **深搜判环**：在深搜过程中，记录节点的状态，判断是否进入环。

### 可拓展之处
同类型题包括判断任务执行顺序是否存在冲突、判断依赖关系是否存在循环等。类似算法套路包括图的遍历、拓扑排序、Tarjan 算法、并查集等。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：涉及任务的先后顺序和拓扑排序。
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：使用 Tarjan 算法求强连通分量。
- [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)：可使用并查集解决矛盾关系。

### 个人心得摘录与总结
- **FFTotoro**：看到考场上好多人用拓扑排序等较高级的算法感到震撼，自己采用了简单好想的算法，体现了不局限于常规思路，勇于尝试新方法的精神。
- **zajasi**：赛后看同学代码发现是拓扑排序，但自己觉得用深搜更合适，说明对问题有自己的思考和理解。

### 重点代码及核心思想
#### FFTotoro
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,c=0; cin>>n;
  vector<pair<string,string> > a(n);
  vector<bool> b(n);
  map<string,int> x,y;
  for(int i=0;i<n;i++){
    cin>>a[i].first>>a[i].second;
    x[a[i].first]=y[a[i].second]=i+1; // 建立 map 映射，方便“找人”
  }
  set<int> d;
  for(int i=0;i<n;i++){
    if(!x[a[i].second]){
      if(y[a[i].first])d.emplace(y[a[i].first]-1); // 放进列表
      b[i]=true; x[a[i].first]=0; c++;
    }
  } // 第一轮扫描全部的人
  while(1){
    if(c==n){
      cout<<"Yes\n";
      return 0;
    } // 处理完了
    set<int> q;
    for(int i:d){
      if(!b[i]&&!x[a[i].second]){
        if(y[a[i].first])q.emplace(y[a[i].first]-1); // 放进列表
        x[a[i].first]=0; c++;
      }
    } // 把可以处理的拿出来处理
    if(q.empty()&&c<n){
      cout<<"No\n";
      return 0;
    } // 列表空了且还没处理完
    d=q; // 更新列表
  }
  return 0;
}
```
**核心思想**：先找出能更换用户名的用户，将其处理并更新相关信息，然后不断找出与这些用户原用户名有冲突的用户，继续处理，直到所有人都处理完或无法继续处理。

#### zajasi
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a[100010],b[100010];
map<string,int> m;
int h[100010];
map<string,int> id;
void dfs(int x,int dep){
    if(dep>n){//出现环
        cout<<"No";//更改不了这个人，再见
        exit(0);
    }
    if(m[b[x]]){//发现有人阻碍更改
        int y=id[b[x]];
        dfs(y,dep+1);//调查阻碍更改的人
        if(m[b[x]]){//发现还是不行
            cout<<"No";
            exit(0);
        }
        else{//阻碍更改的人没威胁了
            m[a[x]]--;
            m[b[x]]++;//更改
            a[x]=b[x];
            h[x]=1;
            return;
        }        
    }
    else{//没人阻碍更改
        m[a[x]]--;
        m[b[x]]++;//直接更改
        a[x]=b[x];
        h[x]=1;
        return;
    }
}
main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        m[a[i]]++;
        id[a[i]]=i;//记录位置和次数
    }
    for(int i=1;i<=n;i++){
        if(h[i]==0){//没有更改过
            dfs(i,0);//尝试更改
        }
    }
    cout<<"Yes";
    return 0;
}
```
**核心思想**：使用深搜，对于每个未更改过的用户，判断是否有其他人阻碍其更改，如果有则继续深搜阻碍的人，若进入环则无法更改，否则进行更改。

#### Fire_flame（拓扑排序）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5, MR = 1e6 + 5;
int n, cnt, num, res, head[MAXN], in[MAXN];
unordered_map<string, int>mp;
struct edge{
	int from, to, nxt;
}e[MR];
void add_edge(int u, int v){
	e[++ cnt] = {u, v, head[u]};
	head[u] = cnt;
} 
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i ++){
		string u, v;
		cin>>u>>v;
		if(!mp[u])mp[u] = ++num;
		if(!mp[v])mp[v] = ++num;
		in[mp[v]] ++;
		add_edge(mp[u], mp[v]);
	}
	queue<int>q;
	for(int i = 1;i <= num;i ++){
		if(in[i] == 0)q.push(i);
	}
	while(!q.empty()){
		int t = q.front();
		res ++;
		q.pop();
		for(int i = head[t];i;i = e[i].nxt){
			int v = e[i].to;
			in[v] --;
			if(in[v] == 0)q.push(v);
		}
	}
	if(res == num)puts("Yes");
	else puts("No");
	return 0;
}
```
**核心思想**：将问题转化为图论问题，使用 `unordered_map` 进行字符串到数字的映射，记录节点的入度，将入度为 0 的节点加入队列，不断更新入度，若能遍历完所有节点则无环，否则有环。

---
处理用时：62.65秒