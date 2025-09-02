# [ICPC 2018 WF] Comma Sprinkler

## 题目描述

正如实践会告诉你的那样，英语中逗号的使用规则复杂、令人沮丧且常常模棱两可。许多人，甚至是英语母语者，在实践中会忽略它们，并应用自定义规则，或者根本不使用规则。

逗号洒水器博士通过制定一套规则解决了这个问题，这些规则在句子中洒上逗号，既不含糊也不简单。在这个问题中，你将帮助洒水器博士编写一个算法来自动应用她的规则。

洒水器博士为现有文本添加逗号的规则如下：

如果文本中的某个单词前面有逗号，则找到该单词在文本中的所有出现位置，并在每个出现位置前加上逗号，除非该出现位置是句子的第一个单词或已经有逗号在前。

如果文本中的某个单词后面有逗号，则找到该单词在文本中的所有出现位置，并在每个出现位置后加上逗号，除非该出现位置是句子的最后一个单词或已经有逗号在后。

重复应用规则 1 和规则 2，直到无法再使用它们添加新的逗号为止。

例如，考虑以下文本：

please sit spot. sit spot, sit. spot here now here.

因为在第二个句子中，spot 后面有逗号，所以在第三个句子中的 spot 后面也应加上逗号（但不是第一个句子，因为它是该句子的最后一个单词）。此外，因为在第二个句子中，sit 前面有逗号，所以在第一个句子中的该单词前也应加上逗号（但不在第二个句子开头的 sit 前加逗号，因为它是该句子的第一个单词）。最后，注意到一旦在第三个句子中的 spot 后加上逗号，here 的第一个出现位置前就有逗号。因此，也在 here 的其他出现位置前加上逗号。没有更多逗号可以添加，所以最终结果是：

please, sit spot. sit spot, sit. spot, here now, here.

## 说明/提示

时间限制：8 秒，内存限制：1024 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
please sit spot. sit spot, sit. spot here now here.
```

### 输出

```
please, sit spot. sit spot, sit. spot, here now, here.
```

## 样例 #2

### 输入

```
one, two. one tree. four tree. four four. five four. six five.
```

### 输出

```
one, two. one, tree. four, tree. four, four. five, four. six five.
```

# 题解

## 作者：70CentsApple (赞：2)

# [P6942 Comma Sprinkler](https://www.luogu.com.cn/problem/P6942)
## 思考
因为每个单词需不需要加逗号是可以预先处理出来的，所以可以考虑读入的时候判重，第二次遇到的时候只需要添加第一次添加它时候分配给它的下标。

可以用并查集维护添加逗号的情况：并查集是一种用于管理元素分组的数据结构。它支持两种操作：**查找**（Find）和**合并**（Union）。查找操作用于确定元素所属的组，而合并操作用于将两个组合并为一个。
可以看这道 [并查集模板题](https://www.luogu.com.cn/problem/P3367) 来学习并查集。

在这个问题中，如果一个单词后面有逗号，那么所有与它**右边相邻**的单词**前面**也应该加逗号。这就是并查集可以解决的问题：通过合并操作将属于同一组的符号情况连接在一起。


------------

接下来的部分建议结合代码使用：

记 `cnt` 为判重后的单词的数量。

`comma` 数组开两倍的 `cnt`：奇数代表**后面**加逗号的情况，偶数代表**前面**加逗号的情况；

循环遍历两遍输入的每个单词的下标：
- 第一个循环：如果后缀符号是**逗号或没有后缀符号**，就把**当前**单词**后面**的符号和**下一个**单词**前面**的符号进行合并（绑成一组）。
```cpp
merge(words_idx[i]*2+1, words_idx[i+1]*2);
```
- 第二个循环：如果后缀符号是**逗号**，就标记相应集合（这时候已经被第一个循环绑成了一组），表示该位置需要在后面添加逗号。
```cpp
comma[find(words_idx[i]*2+1)] = true;
```

## 代码
_不要直接提交哦 ovo_
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = l0ng l0ng;
vector<ll> fa;

ll inline find(ll k) {
	return (fa[k] == k )? k : fa[k] = find(fa[k]);
}
void merge(ll x,ll y){
	fa[find(x)] = find(y);
}

int signed main() {
	string str;
	vector<string> unique_words;
	unordered_map<string, int> words_vis;
	vector<int> words_idx;
	vector<char> suffix_arr; // suffix_arr 记录每个单词的后缀
	ll cnt(0); // 储存 **不同** 的单词数目
	while (cin>>str) {
		// 获取后缀
		const char suffix = str[str.size()-1];
		if(suffix == '\r' or suffix == '\n')
			break;
		else if (suffix == '.' or suffix == ',')
			str=str.substr(0,str.size()-1), suffix_arr.emplace_back(suffix);
		else
			suffix_arr.emplace_back('~'); // 随便插入一个后缀占位
		
		if (words_vis.count(str)) // 已经遇过这个单词
			words_idx.emplace_back(words_vis[str]); // 存放它分配的下标
		else { // 第一次遇到这个单词
			words_idx.emplace_back(cnt);
			words_vis[str] = cnt++; // 分配一个下标
			unique_words.emplace_back(str);
		}
	}
	ll n = suffix_arr.size()-1;
	vector<bool> comma(cnt*2, false);
	fa.resize(cnt*2);
	for (ll i=0; i<cnt*2;i++) fa[i] = i; // 初始化并查集
	for (ll i=0; i<=n-1;i++)
		if (suffix_arr[i] != '.')
			merge(words_idx[i]*2+1, words_idx[i+1]*2);
	for (ll i=0; i<=n-1;i++)
		if (suffix_arr[i] == ',')
			comma[find(words_idx[i]*2+1)] = true;
	for (ll i=0; i<=n; i++) {
		cout << unique_words[words_idx[i]];
		if (suffix_arr[i] == '.') // 句号优先
			cout << '.';
		else if (comma[find(words_idx[i]*2+1)]) // 如果后面应该加逗号
			cout << ',';
		cout << ' ';
	}
	return (0-0);
}
```

---

## 作者：huangmingyi (赞：1)

### 思路
这题可以枚举后面有逗号或前面有逗号的用一个数组 $\operatorname{vis1}$ 来统计。前面有逗号的用一个数组 $\operatorname{vis2}$ 来统计    
```
	if(s[i-1]==',' and a[i][0]>='a' && a[i][0]>='z' || s[i+1]==',' and a[i][0]>='a' && a[i][0]>='z'){
		vis1[s[i][0]-'a']=true;
	}else if(s[i-1]==','  and a[i][0]>='A' && a[i][0]>='Z' || s[i+1]==',' and a[i][0]>='A' && a[i][0]>='Z'){
		vis2[s[i][0]-'A']=true;
	}
```


输出时先判断后面是不是空格，是的话就再输出一个逗号；如果这个是空格要先判断前面是不是被前面有逗号的用一个数组标记，是的话就再输出一个逗号。
## 注意：用字符串就用 getline ！！！

---

## 作者：lin_A_chu_K_fan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6942)
# 题意
给你一段由句子组成的文本，句子中有些单词间有逗号，然后让你按如下规则添加逗号：直到再也不能添加为止：

> 若一个单词的前面/后面有逗号，则让所有非句首/句尾的这个单词前面/后面都加上逗号。
# 思路
这题可以，前面有逗号和后面有逗号的单词分别用数组存起来，然后在输出时先看后面是不是空格，是的话输出 `,`，如果这个是空格要先判断它前面是不是被前面有逗号的用一个数组标记过，是的话输出 `,`。

为了维护社区秩序（实际上是懒），代码就不放了（吧），求关~

---

## 作者：U•ェ•*U (赞：0)

[我的CSDN原文地址（转载请标明！）](https://blog.csdn.net/LZXLSMLTZLLM/article/details/135716660)

## 题意

给你若干句子，每个句子里有些单词间有逗号，让你做无限次这种操作，如果一个词前/后面有逗号，所有非开头/结尾的这个词前/后面都加上逗号，最后输出结果句子。

## 分析
WF 里面最简单一题，就是一个 dfs 就可以了，已经访问过的点可以**不再访问**。

把每个词拆成两个节点，代表这个词前面或后面有逗号，然后如果两个词直接没有句号，就互相连边，最后跑一个搜索就可以了。

## 部分关键代码（防抄袭）：
```cpp
void add(int c, int d) {
	mp1[cnt[0]][0] . a = d;
	mp1[cnt[0]][0] . b = head[c][0];
	head[c][0] = cnt[0] ++;
	mp1[cnt[1]][1] . a = c;
	mp1[cnt[1]][1] . b = head[d][1];
	head[d][1] = cnt[1] ++;
}
void dfs(int x, int flag) {
	vis[x][flag] = 1， flag[x][flag] ++;
	for (int i = head[x][flag]; ~i; i = mp1[i][flag] . b) {
		int to = mp1[i][flag] . a;
		if (vis[to][flag ^ 1]) continue;
		dfs(to, flag ^ 1);
	}
}
```


---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P6942)

------------
# 思路：
签到题，类似于 ```BFS``` 用两个队列维护每种单词前或后是否有逗号向前或后扩展，需要注意如果有句号挡着是不能扩展过去的，不过样例有。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
char s[1000005];
map<string, int> StoI;
vector<string> ItoS;
vector<int> result;
struct Node {
    int to, nx;
} E[N][2];
int head[N][2],tol[2] = {0, 0},tag[N][2],vis[N][2],tot;
void add(int fr, int to) {
    E[tol[0]][0].to = to;
    E[tol[0]][0].nx = head[fr][0];
    head[fr][0] = tol[0]++;
    E[tol[1]][1].to = fr;
    E[tol[1]][1].nx = head[to][1];
    head[to][1] = tol[1]++;
}
void dfs(int x, int flag) {
    vis[x][flag] = 1;
    tag[x][flag]++;
    for (int i = head[x][flag]; ~i; i = E[i][flag].nx) {
        int to = E[i][flag].to;
        if (vis[to][flag ^ 1])continue;
        dfs(to, flag ^ 1);
    }
}
int main() {
    int cnt = 0;
    memset(head, -1, sizeof(head));
    while (1) {
        s[cnt++] = getchar();
        if (s[cnt - 1] == -1 || s[cnt - 1] == '\n') {
            s[cnt - 1] = 0;
            break;
        }
    }
    int sLen = strlen(s);
    string tmp;
    ItoS.push_back(".");
    for (int i = 0; i < sLen; ++i) {
        if (s[i] == ' ' || s[i] == '.' || s[i] == ',') {
            if (!tmp.empty()) {
                if (StoI.find(tmp) == StoI.end()) {
                    ++tot;
                    StoI[tmp] = tot;
                    ItoS.push_back(tmp);
                }
                int Id = StoI[tmp];
                result.push_back(Id);
            }
            if (s[i] == '.')result.push_back(0);
            else if (s[i] == ',')result.push_back(-1);
            tmp.clear();
        }else tmp += s[i];
    }
    for (int i = 0, len = result.size(); i < len; ++i) {
        if (i >= 1 && result[i - 1] > 0 && result[i] > 0) {
            add(result[i - 1], result[i]);
        } else if (i >= 2 && result[i - 2] > 0 && result[i] > 0 && result[i - 1] == -1) {
            add(result[i - 2], result[i]);
            tag[result[i - 2]][0]++;
            tag[result[i]][1]++;
        }
    }
    for (int i = 1; i <= tot; ++i) {
        if (!vis[i][0] && tag[i][0])dfs(i, 0);
        if (!vis[i][1] && tag[i][1])dfs(i, 1);
    }
    for (int i = 0, len = result.size(), ok = 0; i < len; ++i) {
        if (i && result[i - 1] > 0 && result[i] > 0 && (tag[result[i - 1]][0] || tag[result[i]][1]))printf(",");
        if (result[i] < 0)printf(",");
        else if (result[i] == 0)printf(".");
        else {
            if (i)printf(" ");
            string& tmp = ItoS[result[i]];
            for (int j = 0, len = tmp.length(); j < len; ++j)printf("%c", tmp[j]);
        }
    }
    return 0;
}
```
完结撒花~

---

